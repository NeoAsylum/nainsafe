#!/usr/bin/env python3
"""Der Vorstand: der wöchentliche Lauf.

    python agents/wochenlauf.py [--trocken]

    rechnen  ->  bewerten  ->  berichten

Das Rechnen ist deterministisch und kostet keine Tokens. Bewerten heißt: Angriffe auswerten,
Kandidaten töten, höchstens eine Gate-Vorlage anlegen. Berichten heißt: eine Seite,
Sonntagmorgen.

Sinnvoll sonntags früh, damit das Ergebnis beim ersten Kaffee bereitliegt.
"""

from __future__ import annotations

import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import auslastung  # noqa: E402
import repo  # noqa: E402
from lauf import WURZEL, git, jetzt, lauf  # noqa: E402

# Der Verbesserer laeuft zuletzt: Er braucht das Urteil des Portfolio-Managers und
# die Zahlen der Woche. Sein Vorschlag geht an den Betreiber, nicht in die Fabrik --
# Regeln aendert nur ein Mensch.
KETTE = ["portfolio-manager", "verbesserer", "digest-redakteur"]


ANSI = re.compile(r"\[[0-9;]*m")


def _skriptbericht(skript: str, ziel: Path, titel: str) -> None:
    """Faengt die Ausgabe eines lesenden Skripts ab und legt sie als Datei ab.

    Der Verbesserer hatte bis zum 2026-08-30 `Bash`, um `weg.py` und `kontingent.py`
    selbst aufzurufen. Das war ein Loch: Eine Rolle mit *irgendeinem* Bash-Eintrag darf
    im Arbeitsverzeichnis schreiben -- der Sandkasten sperrt nur ausserhalb, und die
    Edit()-Sperren auf CLAUDE.md, grenzen.md und agents/ greifen bei einer Shell gar
    nicht. Nachgemessen am 2026-08-30: `echo HALLO > probe.txt` lief durch, ohne dass
    eine Verweigerung protokolliert wurde.

    Deshalb bekommt niemand mehr eine Shell. Was ein Agent an Skriptausgabe braucht,
    legt der Lauf ihm vorher hin -- deterministisch, zu null Tokens, und lesbar mit
    dem Werkzeug, das er ohnehin hat.
    """
    fertig = subprocess.run(
        ["python3", skript], cwd=WURZEL, capture_output=True, text=True,
        encoding="utf-8", errors="replace",
    )
    text = ANSI.sub("", fertig.stdout or "")
    kopf = (f"# {titel}\n\n"
            f"Erzeugt vom Wochenlauf, {jetzt()}. Quelle: `{skript}`. "
            f"Nicht von Hand aendern.\n\n")
    ziel.write_text(kopf + "```\n" + text.rstrip() + "\n```\n",
                    encoding="utf-8")


def berichte() -> None:
    """Deterministischer Vorlauf: Zahlen stehen fest, bevor ein Modell sie liest."""
    (WURZEL / "ops").mkdir(parents=True, exist_ok=True)
    auslastung.ZIEL.write_text(auslastung.bericht(7), encoding="utf-8")
    _skriptbericht("agents/weg.py", WURZEL / "ops" / "wege.md",
                   "Der Weg der Ideen -- Muster ueber alle Ideen")
    _skriptbericht("agents/kontingent.py", WURZEL / "ops" / "kontingent.md",
                   "Verbrauch und Auslastung des Kontingents")

    dateien = ["ops/auslastung.md", "ops/wege.md", "ops/kontingent.md"]
    if git("status", "--porcelain", "--", *dateien).strip():
        git("add", "--", *dateien, geduldig=True)
        subprocess.run(
            ["git", "commit", "-q", "-m", "berichte: Wochenbilanz, Ideenwege, Kontingent"],
            cwd=WURZEL, capture_output=True, text=True, encoding="utf-8",
        )
    print(f"  {', '.join(dateien)} geschrieben (0 Tokens).")


def main(trocken: bool = False) -> int:
    reif = repo.bereit_zur_bewertung()
    kandidaten = repo.ideen("kandidat")

    print(f"[{jetzt()}] Wochenlauf -- {len(kandidaten)} Kandidaten, "
          f"{len(reif)} davon vollständig geprüft")

    if trocken:
        print("  Trockenlauf, geplante Kette: berichte -> " + " -> ".join(KETTE))
        for k in reif:
            urteile = repo.angriffe(k["_id"])
            print(f"    reif: {k['_id']} ({len(urteile)} Angriffe)")
        if not reif:
            print("    Kein Kandidat vollständig geprüft -- der Portfolio-Manager")
            print("    wird diese Woche vermutlich keine Gate-Vorlage anlegen.")
        return 0

    berichte()

    fehler = 0
    for rolle in KETTE:
        if lauf(rolle) != 0:
            fehler += 1
            print(f"  {rolle} fehlgeschlagen -- Kette läuft weiter.")

    offene_gates = sorted((WURZEL / "gates").glob("*.md"))
    if offene_gates:
        print(f"[{jetzt()}] Wochenlauf beendet. {len(offene_gates)} Gate-Vorlage(n) "
              f"warten auf dich:")
        for g in offene_gates:
            print(f"    {g.relative_to(WURZEL)}")
    else:
        print(f"[{jetzt()}] Wochenlauf beendet, {fehler} Fehler. Keine offenen Gates.")
    return 0 if fehler == 0 else 1


if __name__ == "__main__":
    sys.exit(main("--trocken" in sys.argv))
