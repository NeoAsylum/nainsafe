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
import re
import os
import shutil
import sqlite3
import subprocess
import time
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
    # Eine Shell umgeht jede Edit()-Sperre. Nur eine Rolle hat ueberhaupt Bash
    # (der Verbesserer, und dort nur als Aufruf benannter lesender Skripte); diese
    # Sperren sind die zweite Linie fuer den Fall, dass jemand das wieder aufweicht.
    "Bash(sed:*)",
    "Bash(tee:*)",
    "Bash(cp:*)",
    "Bash(mv:*)",
    "Bash(chmod:*)",
    "Bash(git commit:*)",
    "Bash(git checkout:*)",
    "Bash(git reset:*)",
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
    "Edit(/agentenbau.md)",
    "Edit(/quellen.yml)",
    "Edit(/agents/**)",
    "Edit(/.claude/**)",
    "Edit(/schema/**)",
    # Die Vorlage bestimmt, welche Felder eine Idee ueberhaupt hat -- wer sie aendert,
    # aendert die Bewertung. Kein Werkzeug erlaubt es heute, aber Deny sticht Allow.
    "Edit(/vorlagen/**)",
    # ADRs werden ergaenzt, nie umgeschrieben.
    "Edit(/decisions/**)",
]

ZEITFORMAT = "%Y-%m-%dT%H:%M:%S"

# ---------------------------------------------------------------- Notbremse
#
# Am 2026-08-29 war das Wochenkontingent fast erschoepft, ohne dass irgendetwas
# gewarnt haette: Ein einzelner Tag hatte 95 Laeufe und 253 Dollar Gegenwert
# erzeugt. Es gab keine Stelle, an der die Fabrik von selbst haette anhalten
# koennen.
#
# Der Gegenwert ist der beste verfuegbare Naeherungswert fuer Kontingentverbrauch
# (siehe agents/kontingent.py). Diese Grenze ist bewusst grosszuegig -- sie soll
# Ausreisser abfangen, nicht den Normalbetrieb bremsen. Ein voller Nachtlauf lag
# zuletzt bei rund 40 Dollar.
# Am 2026-09-02 zum ersten Mal an echten Zahlen geeicht, statt geraten. Der Betreiber
# hat seine Anzeige vorgelesen: Fenster 4 Prozent, Woche 21 Prozent. Die Fabrik hatte im
# selben Wochenfenster (Montag 10:00 bis Mittwoch abend) 398,8 Dollar Gegenwert
# verbraucht.
#
# Daraus folgt eine Untergrenze: 100 Prozent der Woche sind MINDESTENS 1.900 Dollar
# Gegenwert -- mindestens, weil das Gespraech mit dem Betreiber auf dasselbe Kontingent
# geht und in den 21 Prozent mit drinsteckt.
#
# Und daraus zwei Korrekturen an dem, was hier vorher stand:
#
# Erstens war die Zahl zu hoch. Ein Tag mit 391 Dollar war rund 18 Prozent der Woche;
# fuenf solche Tage sind die ganze Woche, und die hat sieben. 300 ist die Zahl, die
# durchhaelt.
#
# Zweitens war die Bremse am falschen Fenster. Bindend ist die WOCHE, nicht der Tag --
# das Fuenf-Stunden-Fenster stand bei 4 Prozent, waehrend die Woche bei 21 stand. Eine
# Tagesgrenze allein laesst sieben volle Tage zu und damit ein Vielfaches des
# Wochenlimits. Deshalb steht darunter jetzt eine zweite.
#
# Nachzueichen am 2026-09-13: Bis dahin ist das Wochenlimit um 50 Prozent erhoeht.
# Danach sind dieselben 398,8 Dollar rund 31 statt 21 Prozent, und beide Zahlen hier
# gehoeren auf zwei Drittel gesenkt -- 200 und 1.070.
TAGESGRENZE_USD = 300.0

# Die eigentliche Bremse. Gerechnet ueber sieben rollende Tage statt ueber Anthropics
# Wochenfenster (Montag 10:00): Der genaue Zuschnitt ist zweitrangig, die
# Groessenordnung nicht.
WOCHENGRENZE_USD = 1600.0


def tagesverbrauch(verbindung) -> float:
    """Gegenwert aller Laeufe seit Mitternacht UTC."""
    zeile = verbindung.execute(
        "SELECT sum(kosten_eur) FROM lauf WHERE gestartet > date('now')"
    ).fetchone()
    return float(zeile[0] or 0)


def wochenverbrauch(verbindung) -> float:
    """Gegenwert der letzten sieben Tage -- die Groesse, die wirklich bindet."""
    zeile = verbindung.execute(
        "SELECT sum(kosten_eur) FROM lauf WHERE gestartet > datetime('now', '-7 days')"
    ).fetchone()
    return float(zeile[0] or 0)


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
    # timeout: Bei parallelen Laeufen schreiben mehrere Threads ins Journal. Ohne
    # Wartezeit wirft sqlite sofort "database is locked" und der Lauf verliert seinen
    # Journaleintrag, obwohl er sauber gearbeitet hat. Mit WAL aus dem Schema und
    # dieser Wartezeit serialisieren sich die Schreiber von selbst.
    verbindung = sqlite3.connect(DB, timeout=30)
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
        """UPDATE lauf SET beendet=?, tokens_in=?, tokens_frisch=?, tokens_cneu=?,
                           tokens_cles=?, tokens_denken=?, tokens_out=?,
                           kosten_eur=?, ergebnis=?, commit_hash=?, notiz=?
           WHERE id=?""",
        (
            jetzt(),
            nutzung.get("input_tokens", 0),
            nutzung.get("frisch", 0),
            nutzung.get("cache_neu", 0),
            nutzung.get("cache_gelesen", 0),
            nutzung.get("denken", 0),
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

# Git haelt beim Schreiben eine Sperre auf dem Index. Laufen mehrere Agenten
# gleichzeitig -- und das ist der Normalfall, sobald man die Auslastung hochdreht --,
# scheitert der zweite mit "index.lock: File exists" und verliert seine Arbeit, obwohl
# nichts kaputt ist. Deshalb wird jeder schreibende Git-Aufruf wiederholt.
SPERRE_VERSUCHE = 12
SPERRE_PAUSE = 2.0


def git(*args: str, geduldig: bool = False) -> str:
    """Ruft git auf. `geduldig` wartet, wenn ein anderer Lauf gerade den Index haelt."""
    for versuch in range(SPERRE_VERSUCHE if geduldig else 1):
        fertig = subprocess.run(
            ["git", *args], cwd=WURZEL, capture_output=True, text=True,
            encoding="utf-8", errors="replace",
        )
        if fertig.returncode == 0 or "index.lock" not in (fertig.stderr or ""):
            return (fertig.stdout or "").strip()
        time.sleep(SPERRE_PAUSE * (versuch + 1) / 2)
    return (fertig.stdout or "").strip()


def schreibpfade(werkzeuge: list[str]) -> list[str]:
    """Die Verzeichnisse, die eine Rolle laut ihrer Werkzeugliste anfassen darf."""
    pfade = []
    for w in werkzeuge:
        treffer = re.match(r"Edit\((.+?)\)$", w.strip())
        if treffer:
            p = treffer.group(1).lstrip("/")
            p = p.split("*", 1)[0].rstrip("/")
            if p:
                pfade.append(p)
    return pfade


def frisch_geschrieben(pfade: list[str], seit: float) -> int:
    """Wie viele Dateien in den Schreibpfaden nach `seit` veraendert wurden.

    Noetig, weil bei parallelen Laeufen ein Agent die Dateien eines anderen
    mitcommittet: `committen` nimmt ganze Verzeichnisse, nicht einzelne Dateien.
    Der zweite Lauf findet dann nichts mehr vor und meldete bisher "leer", obwohl
    er sauber gearbeitet hatte. Das verfaelscht jede Auswertung in die gefaehrliche
    Richtung -- eine produktive Rolle sieht aus, als taugte ihr Auftrag nichts.
    """
    anzahl = 0
    for p in pfade:
        ziel = WURZEL / p
        if ziel.is_file():
            kandidaten = [ziel]
        elif ziel.is_dir():
            kandidaten = [d for d in ziel.rglob("*") if d.is_file()]
        else:
            continue
        for d in kandidaten:
            try:
                if d.stat().st_mtime > seit:
                    anzahl += 1
            except OSError:
                pass
    return anzahl


def committen(rolle: str, gegenstand: str | None, lauf_id: int,
              pfade: list[str]) -> tuple[str | None, int, str | None]:
    """Committet, was der Lauf hinterlassen hat. Kein Ergebnis, kein Commit.

    Committet ausschliesslich die Pfade, die die Rolle laut Werkzeugliste beschreiben
    darf. Ein `git add -A` wuerde alles mitnehmen, was gerade sonst im Arbeits-
    verzeichnis liegt -- der Agent signierte dann fremde Aenderungen unter seinem
    Namen, und die Historie sagt nicht mehr, wer was getan hat.

    Gibt (Hash, Anzahl Dateien, Fehlermeldung) zurueck. Der Rueckgabewert von
    `git commit` wird geprueft: Scheitert er -- fehlende Identitaet, Hook, gesperrter
    Index --, liegen die Dateien zwar im Arbeitsverzeichnis, aber die Historie kennt
    sie nicht. Ohne diese Pruefung meldet der Lauf "ok" und niemand merkt es.
    """
    if not pfade:
        return None, 0, None
    geaendert = [z for z in git("status", "--porcelain", "--", *pfade).splitlines()
                 if z.strip()]
    if not geaendert:
        return None, 0, None
    git("add", "--", *pfade, geduldig=True)
    betreff = f"{rolle}: {gegenstand or 'lauf'} ({len(geaendert)} Dateien)"

    # Auch der Commit selbst wartet auf die Sperre. Zwei Agenten, die im selben
    # Moment fertig werden, sind bei hoher Auslastung der Regelfall, kein Ausnahmefall.
    for versuch in range(SPERRE_VERSUCHE):
        fertig = subprocess.run(
            ["git", "commit", "-q", "-m", betreff, "-m", f"Lauf {lauf_id}"],
            cwd=WURZEL, capture_output=True, text=True,
            encoding="utf-8", errors="replace",
        )
        if fertig.returncode == 0:
            return git("rev-parse", "--short", "HEAD"), len(geaendert), None
        meldung = ((fertig.stderr or "") + (fertig.stdout or "")).strip()
        if "index.lock" not in meldung:
            break
        time.sleep(SPERRE_PAUSE * (versuch + 1) / 2)

    return None, len(geaendert), meldung[:300] or "git commit fehlgeschlagen"


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
        # Denkaufwand je Rolle. Sammeln braucht Sorgfalt, Urteilen braucht Tiefe --
        # ohne diesen Schalter laeuft beides auf demselben Standardwert, und der ist
        # fuer die eine Haelfte verschwendet und fuer die andere zu wenig.
        "--effort", kopf.get("effort", "medium"),
        "--permission-mode", MODUS,
        "--allowedTools", *werkzeuge,
        "--disallowedTools", *NIE,
    ]

    verbindung = db()

    # Notbremse vor dem Start, nicht danach: Ein Lauf, der die Grenze reisst,
    # soll gar nicht erst beginnen.
    woche = wochenverbrauch(verbindung)
    if woche >= WOCHENGRENZE_USD:
        verbindung.close()
        print(f"  ABGEBROCHEN: Wochengrenze erreicht "
              f"({woche:.0f} von {WOCHENGRENZE_USD:.0f} $ Gegenwert in sieben Tagen).")
        print("  Das ist die Grenze, die wirklich bindet -- Anthropic rechnet")
        print("  woechentlich. Grenze in agents/lauf.py:WOCHENGRENZE_USD.")
        return 2

    heute = tagesverbrauch(verbindung)
    if heute >= TAGESGRENZE_USD:
        verbindung.close()
        print(f"  ABGEBROCHEN: Tagesgrenze erreicht "
              f"({heute:.0f} von {TAGESGRENZE_USD:.0f} $ Gegenwert).")
        print("  Die Fabrik haelt an, damit das Wochenkontingent nicht in einem Tag")
        print("  aufgebraucht wird. Grenze steht in agents/lauf.py:TAGESGRENZE_USD.")
        return 2

    lauf_id = journal_start(verbindung, rolle, gegenstand)
    begonnen = time.time()
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
        # input_tokens allein ist irrefuehrend: Es zaehlt nur den ungecachten Rest.
        # Ein Trivialaufruf meldete 2 input_tokens -- und 14.102 cache_creation plus
        # 24.432 cache_read. Alle drei gehen durchs Kontingent; wer nur input_tokens
        # journalisiert, untertreibt seinen Verbrauch um Groessenordnungen und dreht
        # die Auslastung im guten Glauben immer weiter hoch.
        eingang = (
            verbrauch.get("input_tokens", 0)
            + verbrauch.get("cache_creation_input_tokens", 0)
            + verbrauch.get("cache_read_input_tokens", 0)
        )
        nutzung = {
            "input_tokens": eingang,
            "frisch": verbrauch.get("input_tokens", 0),
            "cache_neu": verbrauch.get("cache_creation_input_tokens", 0),
            "cache_gelesen": verbrauch.get("cache_read_input_tokens", 0),
            "denken": (verbrauch.get("output_tokens_details") or {}).get(
                "thinking_tokens", 0),
            "output_tokens": verbrauch.get("output_tokens", 0),
            # Claude Code meldet total_cost_usd auch bei Abo-Anmeldung. Der Betrag
            # wird dann NICHT abgerechnet -- er ist der rechnerische Gegenwert zu
            # Listenpreisen, also das, was derselbe Lauf ueber die API gekostet haette.
            # Nuetzlich als Mass dafuer, was die Fabrik aus dem Abo zieht; keine Ausgabe.
            "kosten": roh.get("total_cost_usd", 0.0) or 0.0,
        }
        # Verweigerte Werkzeuge sind der wertvollste Fruehwarnwert ueberhaupt: Genau
        # so sah der Write()-Fehler aus, der einen ganzen Tag lang Laeufe leer laufen
        # liess, waehrend das Journal "ok" meldete.
        verweigert = roh.get("permission_denials") or []
        if verweigert:
            namen = sorted({str(d.get("tool_name", d)) for d in verweigert}) \
                if isinstance(verweigert, list) else [str(verweigert)]
            antwort = (f"[{len(verweigert)}x Werkzeug verweigert: "
                       f"{', '.join(namen)[:120]}] " + antwort)
    except (json.JSONDecodeError, AttributeError):
        antwort = (fertig.stdout or fertig.stderr or "")[:500]

    if fertig.returncode != 0:
        journal_ende(verbindung, lauf_id, "fehler", nutzung, None, antwort)
        print(f"  Fehlgeschlagen (Code {fertig.returncode}): {antwort[:200]}")
        return fertig.returncode

    pfade = schreibpfade(werkzeuge)
    commit_hash, anzahl, commit_fehler = committen(rolle, gegenstand, lauf_id, pfade)
    tokens = nutzung.get("input_tokens", 0) + nutzung.get("output_tokens", 0)

    # Nichts zu committen heisst nicht, dass nichts entstanden ist: Bei parallelen
    # Laeufen hat ein anderer Agent die Dateien schon mitgenommen.
    mitgenommen = 0
    if not anzahl and not commit_fehler:
        mitgenommen = frisch_geschrieben(pfade, begonnen)

    if commit_fehler:
        journal_ende(verbindung, lauf_id, "fehler", nutzung, None,
                     f"Commit gescheitert: {commit_fehler}")
        print(f"  {anzahl} Dateien geschrieben, aber NICHT committet ({tokens} Tokens)")
        print(f"  {commit_fehler.splitlines()[0] if commit_fehler else ''}")
        return 1

    ergebnis = "ok" if (anzahl or mitgenommen) else "leer"
    journal_ende(verbindung, lauf_id, ergebnis, nutzung, commit_hash, antwort)
    if anzahl:
        print(f"  {anzahl} Dateien, {tokens} Tokens, Commit {commit_hash}")
    elif mitgenommen:
        print(f"  {mitgenommen} Dateien geschrieben, von einem parallelen Lauf "
              f"mitcommittet ({tokens} Tokens)")
    else:
        print(f"  Nichts Neues ({tokens} Tokens) - das ist ein gueltiges Ergebnis.")
    return 0


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    sys.exit(lauf(sys.argv[1], sys.argv[2] if len(sys.argv) > 2 else None))
