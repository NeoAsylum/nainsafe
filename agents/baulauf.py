#!/usr/bin/env python3
"""Faehrt die Bauphase: Arbeitspakete statt Rollen.

    python3 agents/baulauf.py [venture] [--trocken] [--gleichzeitig N]

Der Unterschied zu allen frueheren Ketten: Hier steht nicht fest, welche Rolle wann
laeuft. Es steht fest, welche **Arbeitspakete** offen sind; die Rolle ergibt sich aus
dem Paket.

Damit wird "zwei Backend-Entwickler" zu dem, was es hier sein muss. Zwei Agenten mit
derselben Rollendatei, die dieselben Dateien lesen, produzieren dieselbe Arbeit zweimal
oder schreiben sich gegenseitig ueber -- die Fabrik hat das beim Markt-Analysten schon
einmal gelernt. Zwei Agenten mit **zwei verschiedenen Paketen** arbeiten wirklich
parallel. Die Zahl der gleichzeitigen Bauagenten ist deshalb keine Rollenfrage, sondern
eine Frage des Rueckstands.

Ablauf je Lauf:

  1. projektmanager       zerlegt und entblockiert -- immer zuerst, sonst laufen die
                          Bauagenten leer
  2. Bau                  alle offenen Pakete ohne offene Abhaengigkeit, parallel
  3. Pruefung             selbstspieler, rueckvergleicher, bruchtester auf ihren Paketen
  4. geschaeftsfuehrer    schreibt ops/plan.md fuer den Betreiber
"""

from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from lauf import WURZEL, frontmatter, jetzt, lauf  # noqa: E402
from nachtlauf import phase  # noqa: E402

BAUROLLEN = {"datenbauer", "kernbauer", "oberflaechenbauer", "auslieferer",
             "testentwickler"}
PRUEFROLLEN = {"selbstspieler", "rueckvergleicher", "bruchtester"}

# Zwei Pakete, die dieselbe Datei anfassen, duerfen nicht gleichzeitig laufen. Das ist
# der Grund fuer das Feld `dateien` im Paket -- ohne diese Pruefung ueberschreiben sich
# zwei Bauagenten, und der Verlust faellt erst Tage spaeter auf.
GLEICHZEITIG = 4


def pakete(venture: str) -> list[dict]:
    ordner = WURZEL / "ventures" / venture / "aufgaben"
    if not ordner.is_dir():
        return []
    alle = []
    for d in sorted(ordner.glob("*.md")):
        kopf, _ = frontmatter(d.read_text(encoding="utf-8"))
        if not kopf:
            continue
        kopf["_id"] = kopf.get("id") or d.stem
        kopf["_dateien"] = {s.strip() for s in
                            str(kopf.get("dateien", "")).strip("[]").split(",") if s.strip()}
        kopf["_haengt"] = {s.strip() for s in
                           str(kopf.get("haengt_an", "")).strip("[]").split(",") if s.strip()}
        alle.append(kopf)
    return alle


def startbereit(alle: list[dict], rollen: set[str]) -> list[dict]:
    """Offene Pakete der genannten Rollen, deren Abhaengigkeiten fertig sind --
    und die sich nicht in denselben Dateien treffen."""
    fertig = {p["_id"] for p in alle if p.get("status") == "fertig"}
    dran, belegt = [], set()
    for p in alle:
        if p.get("status") != "offen" or p.get("rolle") not in rollen:
            continue
        if p["_haengt"] - fertig:
            continue
        if p["_dateien"] & belegt:
            continue  # kollidiert mit einem schon eingeplanten Paket
        belegt |= p["_dateien"]
        dran.append(p)
    return dran


def main(venture: str, trocken: bool = False, gleichzeitig: int = GLEICHZEITIG) -> int:
    alle = pakete(venture)
    offen = [p for p in alle if p.get("status") == "offen"]
    fertig = [p for p in alle if p.get("status") == "fertig"]
    blockiert = [p for p in alle if p.get("status") == "blockiert"]

    print(f"[{jetzt()}] Baulauf {venture} -- {len(fertig)} fertig, {len(offen)} offen, "
          f"{len(blockiert)} blockiert")

    bau = startbereit(alle, BAUROLLEN)[:gleichzeitig]
    pruef = startbereit(alle, PRUEFROLLEN)[:gleichzeitig]

    if trocken:
        print("  1. projektmanager")
        print(f"  2. Bau        {len(bau)} Pakete gleichzeitig")
        for p in bau:
            print(f"       {p.get('rolle'):18} {p['_id']}")
        print(f"  3. Pruefung   {len(pruef)} Pakete")
        for p in pruef:
            print(f"       {p.get('rolle'):18} {p['_id']}")
        print("  4. geschaeftsfuehrer")
        if not alle:
            print()
            print("  Es gibt noch keine Arbeitspakete. Der erste Lauf legt sie an --")
            print("  der Projektmanager liest specs/ und zerlegt sie.")
        return 0

    fehler = 0

    # Immer zuerst: ohne Rueckstand laufen die Bauagenten leer.
    if lauf("projektmanager", venture) != 0:
        fehler += 1
        print("  projektmanager fehlgeschlagen -- Kette laeuft weiter.")

    alle = pakete(venture)
    bau = startbereit(alle, BAUROLLEN)[:gleichzeitig]
    if bau:
        fehler += phase("Bau", [(p["rolle"], p["_id"]) for p in bau])

    alle = pakete(venture)
    pruef = startbereit(alle, PRUEFROLLEN)[:gleichzeitig]
    if pruef:
        fehler += phase("Pruefung", [(p["rolle"], p["_id"]) for p in pruef])

    if lauf("geschaeftsfuehrer", venture) != 0:
        fehler += 1

    uebrig = len([p for p in pakete(venture) if p.get("status") == "offen"])
    print(f"[{jetzt()}] Baulauf beendet, {fehler} Fehler. {uebrig} Pakete offen.")
    plan = WURZEL / "ops" / "plan.md"
    if plan.exists():
        print(f"  Bericht fuer den Betreiber: {plan.relative_to(WURZEL)}")
    return 0 if fehler == 0 else 1


if __name__ == "__main__":
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    n = GLEICHZEITIG
    if "--gleichzeitig" in sys.argv:
        n = int(sys.argv[sys.argv.index("--gleichzeitig") + 1])
    if args:
        v = args[0]
    else:
        vs = sorted(p.name for p in (WURZEL / "ventures").iterdir() if p.is_dir())
        if len(vs) != 1:
            sys.exit("Aufruf: python3 agents/baulauf.py <venture>\n"
                     "Vorhanden: " + (", ".join(vs) or "keins"))
        v = vs[0]
    sys.exit(main(v, "--trocken" in sys.argv, n))
