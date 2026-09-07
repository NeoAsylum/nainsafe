#!/usr/bin/env python3
"""Abschnittsverzeichnis der Vorgaben -- damit kein Agent mehr ganze Vorgaben liest.

Am 2026-09-07 gemessen: 98 Prozent des Eingangs jedes Laufs sind Cache-Lesen, im
Schnitt 39 Wiederholungen desselben Kontexts. Die Rechnung eines Laufs ist also
**Kontextgroesse mal Zuege**. Wer `technik.md` (292 kB, rund 73.000 Token) einmal
ganz liest, zahlt sie nicht einmal, sondern neununddreissig Mal.

`spiel.md` und `technik.md` zusammen sind 566 kB. Dieses Verzeichnis ist rund 4 kB
und nennt zu jedem Abschnitt die Zeilenspanne. Damit liest ein Agent gezielt den
einen Abschnitt, den er braucht.

Kostet null Token: reines Skript, wie `agents/auslastung.py`. Liegt unter `ops/`,
nicht unter `specs/` -- dort wuerde der Uebersetzer es aufgreifen und der
Belegstellen-Riegel muesste es mitpruefen, beides ohne Nutzen.

Aufruf:  python3 agents/inhalt.py
"""
import os
import re
from pathlib import Path

WURZEL = Path(__file__).resolve().parent.parent
UEBERSCHRIFT = re.compile(r"^## (.+)$")
NZ = chr(10)


def punkte(zahl: int) -> str:
    """1234567 -> 1.234.567. Nur auf Zahlen anwenden, nie auf Ueberschriften:
    ein Punkt statt eines Kommas mitten im Titel waere eine stille Faelschung."""
    return f"{zahl:,}".replace(",", ".")


def abschnitte(text: str) -> list[tuple[str, int, int, int]]:
    """(Ueberschrift, erste Zeile, letzte Zeile, Zeichen) je `## `-Abschnitt."""
    zeilen = text.splitlines()
    marken = []
    for i, z in enumerate(zeilen, 1):
        m = UEBERSCHRIFT.match(z)
        if m:
            marken.append((i, m.group(1).strip()))
    ergebnis = []
    for n, (zeile, titel) in enumerate(marken):
        ende = marken[n + 1][0] - 1 if n + 1 < len(marken) else len(zeilen)
        zeichen = sum(len(z) + 1 for z in zeilen[zeile - 1:ende])
        ergebnis.append((titel, zeile, ende, zeichen))
    return ergebnis


def verzeichnis(ordner: Path) -> str:
    zeilen = [
        f"# Abschnitte der Vorgaben -- {ordner.name}",
        "",
        "Erzeugt von `agents/inhalt.py`. **Nicht von Hand aendern**, jeder Tageslauf",
        "ueberschreibt die Datei.",
        "",
        "## Wozu das hier da ist",
        "",
        "Lies **nie** eine Vorgabe ganz. Der Kontext eines Laufs wird in jedem Zug",
        "erneut gesendet -- am 2026-09-07 gemessen: im Schnitt 39 Mal. Wer `technik.md`",
        "ganz liest, traegt rund 73.000 Token durch jeden folgenden Zug.",
        "",
        "**Die Ueberschrift ist der Anker, nicht die Zeilennummer.** Der Uebersetzer",
        "schreibt `technik.md` laufend um und verschiebt dabei jede Zeile darunter.",
        "Die Spannen hier sind Minuten alt; sie sagen dir, wie **gross** ein Abschnitt",
        "ist, nicht mehr verlaesslich, wo er steht. So greifst du sicher zu:",
        "",
        "```",
        'Grep(pattern="^## <Ueberschrift>", path=<datei>, output_mode="content", -n=true)',
        "Read(datei, offset=<gefundene Zeile>, limit=<Zeilen laut Tabelle>)",
        "```",
        "",
        "Steht die erwartete Ueberschrift nicht in der ersten gelesenen Zeile, ist die",
        "Datei unter dir verrutscht -- dann `Grep` erneut, statt weiterzulesen.",
        "",
        "Brauchst du nur eine Stelle, ist `Grep` mit `-n` billiger als jedes Lesen.",
        "",
    ]
    for datei in sorted(ordner.glob("*.md")):
        text = datei.read_text(encoding="utf-8", errors="replace")
        teile = abschnitte(text)
        zeilen.append(f"## {datei.name} -- {punkte(len(text))} Zeichen, "
                      f"{len(teile)} Abschnitte")
        zeilen.append("")
        if not teile:
            zeilen.append("Keine `## `-Ueberschriften; die Datei ist kurz genug am Stueck.")
            zeilen.append("")
            continue
        zeilen.append("| Abschnitt | Zeilen | Zeichen |")
        zeilen.append("|---|---|---|")
        for titel, von, bis, zeichen in teile:
            zeilen.append(f"| {titel} | {von}-{bis} | {punkte(zeichen)} |")
        zeilen.append("")
    return NZ.join(zeilen) + NZ


def main() -> int:
    geschrieben = 0
    for ordner in sorted((WURZEL / "specs").iterdir()):
        if not ordner.is_dir() or not list(ordner.glob("*.md")):
            continue
        ziel = WURZEL / "ops" / f"inhalt-{ordner.name}.md"
        neu = verzeichnis(ordner)
        alt = ziel.read_text(encoding="utf-8") if ziel.exists() else None
        if neu != alt:
            # Atomar: Acht Bauagenten koennen gleichzeitig hier stehen. Ein direktes
            # write_text hinterliesse dem Naechsten eine halb geschriebene Datei.
            temp = ziel.with_suffix(f".md.{os.getpid()}")
            temp.write_text(neu, encoding="utf-8")
            os.replace(temp, ziel)
            geschrieben += 1
            print(f"  {ziel.relative_to(WURZEL)} -- {punkte(len(neu))} Zeichen")
    return geschrieben


if __name__ == "__main__":
    main()
