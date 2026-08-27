#!/usr/bin/env python3
"""Fuehrt einen einzelnen Agentenlauf aus.

    python agents/lauf.py <rolle> [gegenstand]

Eine Rolle ist eine Datei unter agents/rollen/<rolle>.md. Ihr Frontmatter legt fest,
welche Werkzeuge der Lauf bekommt -- das ist die Durchsetzung der Schreibrechte aus
CLAUDE.md. Nicht der Prompt haelt einen Agenten davon ab, ins falsche Verzeichnis zu
schreiben, sondern das fehlende Werkzeug.

Der Rumpf der Rollendatei ist der Auftrag und geht unveraendert an das Modell.
"""

from __future__ import annotations

import json
import os
import shutil
import sqlite3
import subprocess
import sys
from datetime import datetime, timezone
from pathlib import Path

WURZEL = Path(__file__).resolve().parent.parent
ROLLEN = WURZEL / "agents" / "rollen"
DB = WURZEL / "state.db"
SCHEMA = WURZEL / "schema" / "state.sql"

# Berechtigungsmodus. "dontAsk" verweigert alles, was nicht ausdruecklich in der
# Werkzeugliste der Rolle steht -- ohne Rueckfrage, was im unbeaufsichtigten Lauf der
# einzig sinnvolle Umgang mit einer Rueckfrage ist.
#
# Ausdruecklich NICHT "acceptEdits": dieser Modus genehmigt Dateiaenderungen im ganzen
# Arbeitsverzeichnis und wuerde damit die Rollentrennung aufheben -- der Regel-Scout
# koennte Ideen schreiben. Aeltere Claude-Code-Versionen kennen "dontAsk" nicht; dort
# ist "default" der Ersatz (Werkzeuge ausserhalb der Liste loesen dann eine Rueckfrage
# aus, die unbeaufsichtigt ebenfalls scheitert -- gleiches Ergebnis, langsamer).
MODUS = "dontAsk"

# Zweite Verteidigungslinie: was kein Agent jemals darf, unabhaengig von seiner Rolle.
# Deny sticht Allow, auch wenn eine Rolle sich das Werkzeug in ihr Frontmatter schreibt.
NIE = [
    # Regel 1 und 2 aus CLAUDE.md -- kein Geld ausgeben, nichts nach aussen schreiben.
    "Bash(git push:*)",
    "Bash(git remote:*)",
    "Bash(gh:*)",
    "Bash(curl:*)",
    "Bash(wget:*)",
    "Bash(npm publish:*)",
    "Bash(rm:*)",
    "Bash(pip install:*)",
    # Die Fabrik schreibt die Regeln nicht um, nach denen sie beurteilt wird.
    # Ein Fit-Filter, der grenzen.md aendern koennte, hat keine Grenzen.
    #
    # Ausschliesslich Edit(), nie Write(): Claude Code prueft Dateirechte allein gegen
    # Edit()- und Read()-Regeln. Eine Write()-Pfadregel wird zwar angenommen, aber nie
    # ausgewertet -- sie sieht wie Schutz aus und ist keiner. Edit() deckt alle
    # eingebauten Werkzeuge ab, die Dateien aendern, das Anlegen neuer Dateien
    # eingeschlossen.
    "Edit(/CLAUDE.md)",
    "Edit(/grenzen.md)",
    "Edit(/quellen.yml)",
    "Edit(/agents/**)",
    "Edit(/.claude/**)",
    "Edit(/schema/**)",
    # ADRs werden ergaenzt, nie umgeschrieben.
    "Edit(/decisions/**)",
]

ZEITFORMAT = "%Y-%m-%dT%H:%M:%S"


def jetzt() -> str:
    return datetime.now(timezone.utc).strftime(ZEITFORMAT)


# ---------------------------------------------------------------- Frontmatter

def frontmatter(text: str) -> tuple[dict, str]:
    """Minimaler YAML-Frontmatter-Parser fuer die drei hier benutzten Formen:

        schluessel: wert
        schluessel:
          - listeneintrag
        schluessel:
          unterschluessel: wert     (eine Ebene, z.B. score.summe)

    Bewusst ohne PyYAML, damit ein frischer VPS ohne Paketinstallation laeuft. Ein
    Schluessel ohne Wert startet als Liste und wird zur Map, sobald eine eingerueckte
    Zuweisung folgt -- welche der beiden Formen gemeint war, zeigt erst die naechste Zeile.
    """
    if not text.startswith("---"):
        return {}, text
    _, kopf, rumpf = text.split("---", 2)
    daten: dict = {}
    offen = None  # Schluessel, unter dem eingerueckte Zeilen landen
    for zeile in kopf.splitlines():
        if not zeile.strip() or zeile.lstrip().startswith("#"):
            continue
        eingerueckt = zeile[:1].isspace()
        roh = zeile.strip()

        if roh.startswith("- "):
            if offen is not None and isinstance(daten.get(offen), list):
                daten[offen].append(roh[2:].strip().strip("\"'"))
            continue

        if ":" not in roh:
            continue
        k, _, v = roh.partition(":")
        # YAML-Semantik: " #" beginnt einen Kommentar. Die Vorlagen dokumentieren die
        # zulaessigen Werte hinter dem Feld -- ohne dieses Abschneiden waere der Status
        # einer aus der Vorlage kopierten Idee nie ein gueltiger Status.
        k, v = k.strip(), v.split(" #")[0].strip().strip("\"'")

        if eingerueckt and offen is not None:
            if isinstance(daten.get(offen), list):
                daten[offen] = {}
            daten[offen][k] = v
            continue

        if v:
            daten[k] = v
            offen = None
        else:
            daten[k] = []
            offen = k
    return daten, rumpf.lstrip("\n")


# ---------------------------------------------------------------- Journal

def db() -> sqlite3.Connection:
    """Oeffnet die Zustandsdatenbank und legt bei Bedarf das Schema an.

    Geprueft wird das Schema, nicht die Datei: Eine leere oder halb angelegte state.db
    kommt in der Praxis vor (abgebrochener Lauf, versehentliches sqlite3-Oeffnen) und
    wuerde bei einer reinen Dateipruefung stumm zu Folgefehlern fuehren.
    """
    verbindung = sqlite3.connect(DB)
    vorhanden = verbindung.execute(
        "SELECT count(*) FROM sqlite_master WHERE type='table' AND name='lauf'"
    ).fetchone()[0]
    if not vorhanden:
        verbindung.executescript(SCHEMA.read_text(encoding="utf-8"))
        verbindung.commit()
    return verbindung


def journal_start(verbindung, rolle: str, gegenstand: str | None) -> int:
    # Laeufe, die beim letzten Mal hart abgebrochen wurden -- Distro heruntergefahren,
    # Rechner aus, Prozess gekillt -- stehen sonst fuer immer auf "laeuft" und
    # verfaelschen Kostenbericht und Digest. Zwei Stunden liegen weit ueber dem
    # laengsten zulaessigen Timeout (1800s), koennen also keinen echten Lauf treffen.
    verbindung.execute(
        """UPDATE lauf SET ergebnis = 'abgebrochen', beendet = ?
           WHERE ergebnis = 'laeuft' AND gestartet < datetime('now', '-2 hours')""",
        (jetzt(),),
    )
    zeiger = verbindung.execute(
        "INSERT INTO lauf (gestartet, rolle, gegenstand) VALUES (?,?,?)",
        (jetzt(), rolle, gegenstand),
    )
    verbindung.commit()
    return zeiger.lastrowid


def journal_ende(verbindung, lauf_id: int, ergebnis: str, nutzung: dict,
                 commit_hash: str | None, notiz: str | None) -> None:
    verbindung.execute(
        """UPDATE lauf SET beendet=?, tokens_in=?, tokens_out=?, kosten_eur=?,
                           ergebnis=?, commit_hash=?, notiz=? WHERE id=?""",
        (
            jetzt(),
            nutzung.get("input_tokens", 0),
            nutzung.get("output_tokens", 0),
            nutzung.get("kosten", 0.0),
            ergebnis,
            commit_hash,
            (notiz or "")[:500],
            lauf_id,
        ),
    )
    verbindung.commit()


# ---------------------------------------------------------------- Git

def git(*args: str) -> str:
    fertig = subprocess.run(
        ["git", *args], cwd=WURZEL, capture_output=True, text=True, encoding="utf-8"
    )
    return (fertig.stdout or "").strip()


def committen(rolle: str, gegenstand: str | None,
              lauf_id: int) -> tuple[str | None, int, str | None]:
    """Committet, was der Lauf hinterlassen hat. Kein Ergebnis, kein Commit.

    Gibt (Hash, Anzahl Dateien, Fehlermeldung) zurueck. Der Rueckgabewert von
    `git commit` wird geprueft: Scheitert er -- fehlende Identitaet, Hook, gesperrter
    Index --, liegen die Dateien zwar im Arbeitsverzeichnis, aber die Historie kennt
    sie nicht. Ohne diese Pruefung meldet der Lauf "ok" und niemand merkt es.
    """
    geaendert = [z for z in git("status", "--porcelain").splitlines() if z.strip()]
    if not geaendert:
        return None, 0, None
    git("add", "-A")
    betreff = f"{rolle}: {gegenstand or 'lauf'} ({len(geaendert)} Dateien)"
    fertig = subprocess.run(
        ["git", "commit", "-q", "-m", betreff, "-m", f"Lauf {lauf_id}"],
        cwd=WURZEL, capture_output=True, text=True, encoding="utf-8",
    )
    if fertig.returncode != 0:
        meldung = ((fertig.stderr or "") + (fertig.stdout or "")).strip()
        return None, len(geaendert), meldung[:300] or "git commit fehlgeschlagen"
    return git("rev-parse", "--short", "HEAD"), len(geaendert), None


# ---------------------------------------------------------------- Lauf

def claude_pfad() -> str:
    for name in ("claude", "claude.cmd", "claude.exe"):
        pfad = shutil.which(name)
        if pfad:
            return pfad
    # cron und der Windows-Aufgabenplaner starten mit einem kargen PATH, in dem die
    # ueblichen Installationsorte von Claude Code nicht vorkommen. Ohne diesen Zweig
    # scheitert jeder naechtliche Lauf stumm, waehrend er von Hand einwandfrei laeuft.
    for kandidat in (
        Path.home() / ".local" / "bin" / "claude",
        Path.home() / ".claude" / "local" / "claude",
        Path("/usr/local/bin/claude"),
    ):
        if kandidat.is_file():
            return str(kandidat)
    sys.exit("claude nicht gefunden - Claude Code installieren oder PATH pruefen.")


def pruefe_umgebung() -> None:
    """Prueft vor dem ersten Token, was den Lauf am Ende wertlos machen wuerde.

    Eine fehlende Git-Identitaet faellt sonst erst auf, wenn der Agent fertig
    recherchiert hat: Die Dateien liegen da, der Commit scheitert, die Tokens sind weg.
    """
    if not git("config", "user.email") or not git("config", "user.name"):
        sys.exit(
            "Keine Git-Identitaet gesetzt -- jeder Commit wuerde scheitern und der Lauf\n"
            "waere umsonst. Einmalig im Repo setzen:\n"
            '  git config user.name "<Name>"\n'
            '  git config user.email "<Mail>"'
        )


def lauf(rolle: str, gegenstand: str | None = None) -> int:
    datei = ROLLEN / f"{rolle}.md"
    if not datei.exists():
        sys.exit(f"Unbekannte Rolle: {rolle} (erwartet {datei})")
    pruefe_umgebung()

    kopf, auftrag = frontmatter(datei.read_text(encoding="utf-8"))
    werkzeuge = kopf.get("tools") or []
    if not werkzeuge:
        sys.exit(f"Rolle {rolle} definiert keine Werkzeuge - das waere ein Blankoscheck.")

    if gegenstand:
        auftrag += f"\n\n## Gegenstand dieses Laufs\n\n{gegenstand}\n"

    befehl = [
        claude_pfad(), "-p", auftrag,
        "--output-format", "json",
        "--model", kopf.get("modell", "sonnet"),
        "--permission-mode", MODUS,
        "--allowedTools", *werkzeuge,
        "--disallowedTools", *NIE,
    ]

    verbindung = db()
    lauf_id = journal_start(verbindung, rolle, gegenstand)
    print(f"[{jetzt()}] Lauf {lauf_id}: {rolle}" + (f" -> {gegenstand}" if gegenstand else ""))

    try:
        fertig = subprocess.run(
            befehl, cwd=WURZEL, capture_output=True, text=True,
            encoding="utf-8", errors="replace", timeout=int(kopf.get("timeout", 1800)),
        )
    except subprocess.TimeoutExpired:
        journal_ende(verbindung, lauf_id, "fehler", {}, None, "Zeitueberschreitung")
        print(f"  Zeitueberschreitung nach {kopf.get('timeout', 1800)}s")
        return 1

    nutzung: dict = {}
    antwort = ""
    try:
        roh = json.loads(fertig.stdout)
        antwort = roh.get("result", "") or ""
        verbrauch = roh.get("usage") or {}
        nutzung = {
            "input_tokens": verbrauch.get("input_tokens", 0),
            "output_tokens": verbrauch.get("output_tokens", 0),
            # Claude Code meldet total_cost_usd auch bei Abo-Anmeldung. Der Betrag
            # wird dann NICHT abgerechnet -- er ist der rechnerische Gegenwert zu
            # Listenpreisen, also das, was derselbe Lauf ueber die API gekostet haette.
            # Nuetzlich als Mass dafuer, was die Fabrik aus dem Abo zieht; keine Ausgabe.
            "kosten": roh.get("total_cost_usd", 0.0) or 0.0,
        }
    except (json.JSONDecodeError, AttributeError):
        antwort = (fertig.stdout or fertig.stderr or "")[:500]

    if fertig.returncode != 0:
        journal_ende(verbindung, lauf_id, "fehler", nutzung, None, antwort)
        print(f"  Fehlgeschlagen (Code {fertig.returncode}): {antwort[:200]}")
        return fertig.returncode

    commit_hash, anzahl, commit_fehler = committen(rolle, gegenstand, lauf_id)
    tokens = nutzung.get("input_tokens", 0) + nutzung.get("output_tokens", 0)

    if commit_fehler:
        journal_ende(verbindung, lauf_id, "fehler", nutzung, None,
                     f"Commit gescheitert: {commit_fehler}")
        print(f"  {anzahl} Dateien geschrieben, aber NICHT committet ({tokens} Tokens)")
        print(f"  {commit_fehler.splitlines()[0] if commit_fehler else ''}")
        return 1

    ergebnis = "ok" if anzahl else "leer"
    journal_ende(verbindung, lauf_id, ergebnis, nutzung, commit_hash, antwort)
    if anzahl:
        print(f"  {anzahl} Dateien, {tokens} Tokens, Commit {commit_hash}")
    else:
        print(f"  Nichts Neues ({tokens} Tokens) - das ist ein gueltiges Ergebnis.")
    return 0


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    sys.exit(lauf(sys.argv[1], sys.argv[2] if len(sys.argv) > 2 else None))
