#!/usr/bin/env python3
"""Uebersetzt den bleibenden Bestand der Fabrik ins Englische, Datei fuer Datei.

    python3 agents/uebersetzungslauf.py [--trocken] [--stueck N]

Warum es das gibt: Die Fabrik schreibt seit dem 2026-09-06 englisch, der Bestand ist
deutsch. Ein Repo in zwei Sprachen kostet jeden Agenten in jedem Lauf einen
Uebersetzungsschritt. Uebersetzt wird deshalb, was **bleibt** -- Rollendateien, das
Regelwerk, die Spezifikationen, die ADRs.

**Was ausdruecklich nicht uebersetzt wird**, weil es sich von selbst dreht: Logbuecher
(rotieren bei 12.000 Zeichen, neue Eintraege sind englisch), Arbeitspakete und Befunde
(neue entstehen englisch, alte werden fertig und nicht mehr gelesen). Sie zu uebersetzen
waere Arbeit an etwas, das ohnehin verschwindet.

Die Reihenfolge ist nach Lesehaeufigkeit sortiert: Rollendateien werden in jedem Lauf
gelesen, ADRs fast nie.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

WURZEL = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(WURZEL / "agents"))
from lauf import jetzt, lauf  # noqa: E402

FOKUS = "0016-hedgefonds-simulation-echte-weltwirtschaft"

# Ein Abschnitt je Lauf, wenn die Datei groesser ist als das. Gemessen: spiel.md hat
# 15 Abschnitte auf zweiter Ebene, technik.md 21 -- rund 14.000 Zeichen je Stueck.
STUECK_MAX = 20_000

# Reihenfolge = Lesehaeufigkeit. Was in jedem Lauf gelesen wird, zuerst.
def bestand() -> list[Path]:
    # Nur specs/. agents/**, decisions/**, grenzen.md und agentenbau.md sperrt
    # lauf.py:NIE fuer jeden Agenten -- das sind die Dokumente, nach denen die
    # Fabrik beurteilt wird, und eine Uebersetzung ist eine Neufassung. Sie
    # bleiben Sache des Betreibers. Am 2026-09-06 nachgemessen: drei
    # Schreibversuche auf eine Rollendatei, drei identische Absagen.
    return sorted((WURZEL / "specs" / FOKUS).glob("*.md"))


_DEUTSCH = re.compile(r"\b(der|die|das|und|nicht|ist|ein|eine|wird|sich|auch|nur|"
                      r"wenn|dass|aber|oder|noch|schon|kein|keine|dieser|diese|"
                      r"dieses|werden|wurde|haben|hat|sind|bei|nach|ueber|unter)\b")


def deutsch(text: str) -> bool:
    """Ganze deutsche Funktionswoerter je 4.000 Zeichen -- keine Teilzeichenketten.

    Die erste Fassung zaehlte auch ae/oe/ue als Umlautersatz. Die stecken in true,
    value, issue, sequence: Ein fertig uebersetzter Abschnitt kam auf 13 Treffer bei
    Schwelle 12 und wurde 56-mal neu gewaehlt. Umlaute in deutschen Zitaten zaehlen
    absichtlich nicht -- Zitate bleiben deutsch, und das ist kein Zeichen fuer eine
    unuebersetzte Stelle.
    """
    probe = text[:4000].lower()
    return len(_DEUTSCH.findall(probe)) >= 10


BUCH = WURZEL / "ops" / "uebersetzt.txt"


def erledigt() -> set[str]:
    """Alles, was ein erfolgreicher Lauf schon uebersetzt hat -- nie wieder waehlen."""
    try:
        return {z.strip() for z in BUCH.read_text(encoding="utf-8").splitlines()
                if z.strip() and not z.startswith("#")}
    except OSError:
        return set()


def eintragen(wo: str) -> None:
    BUCH.parent.mkdir(parents=True, exist_ok=True)
    if not BUCH.exists():
        BUCH.write_text("# Vom Uebersetzungslauf fertig gemeldete Abschnitte. Was hier\n"
                        "# steht, wird nie wieder gewaehlt -- unabhaengig von jeder\n"
                        "# Spracherkennung. Am 2026-09-06 fehlte diese Datei, und ein\n"
                        "# englischer Abschnitt wurde 56-mal neu uebersetzt.\n",
                        encoding="utf-8")
    with BUCH.open("a", encoding="utf-8") as f:
        f.write(wo + "\n")


def offen() -> list[tuple[Path, str | None]]:
    """(Datei, Abschnitt) fuer alles, was noch deutsch ist und nicht im Buch steht."""
    fertig = erledigt()
    aufgaben = []
    for p in bestand():
        try:
            t = p.read_text(encoding="utf-8")
        except OSError:
            continue
        if not deutsch(t):
            continue
        if len(t) <= STUECK_MAX:
            if str(p.relative_to(WURZEL)) not in fertig:
                aufgaben.append((p, None))
            continue
        # Grosse Dateien abschnittsweise, erster noch deutscher Abschnitt zuerst.
        for m in re.finditer(r"(?m)^## (.+)$", t):
            anfang = m.start()
            naechste = re.search(r"(?m)^## ", t[anfang + 3:])
            ende = anfang + 3 + naechste.start() if naechste else len(t)
            wo = f"{p.relative_to(WURZEL)}#{m.group(1).strip()}"
            if wo not in fertig and deutsch(t[anfang:ende]):
                aufgaben.append((p, m.group(1).strip()))
                break
    return aufgaben


def reservieren(pfade: list[Path]) -> None:
    """Traegt die noch nicht uebersetzten Dateien fuer den Baulauf ein."""
    datei = WURZEL / "ops" / "reserviert.txt"
    datei.parent.mkdir(parents=True, exist_ok=True)
    if not pfade:
        datei.write_text("# frei\n", encoding="utf-8")
        return
    datei.write_text(
        "# Vom Uebersetzungslauf gehalten. Der Baulauf plant kein Paket ein, dessen\n"
        "# dateien-Liste eine dieser Zeilen trifft. Leer, sobald er fertig ist.\n"
        + "\n".join(sorted(str(p.relative_to(WURZEL)) for p in pfade)) + "\n",
        encoding="utf-8")


def main() -> int:
    trocken = "--trocken" in sys.argv
    stueck = 1
    if "--stueck" in sys.argv:
        stueck = int(sys.argv[sys.argv.index("--stueck") + 1])

    # **Nach jedem Abschnitt neu nachsehen.** `offen()` liefert hoechstens eine Aufgabe
    # je Datei -- es bricht nach dem ersten noch deutschen Abschnitt ab, damit zwei
    # Laeufe nicht dieselbe Datei anfassen. Die erste Fassung hat die Liste **einmal**
    # gebildet und dann `warten[:stueck]` abgearbeitet: Bei vier Dateien waren das vier
    # Abschnitte, und `--stueck 60` aenderte daran nichts. Am 2026-09-06 sah es aus, als
    # sei der Lauf gestorben; er war fertig.
    gemacht = 0
    gesehen: set[str] = set()
    while gemacht < (8 if trocken else stueck):
        warten = offen()
        reservieren(sorted({x for x, _ in warten}))
        if not warten:
            print(f"[{jetzt()}] Der bleibende Bestand ist englisch "
                  f"({gemacht} Abschnitte in diesem Lauf).")
            return 0
        if gemacht == 0:
            gesamt = sum(len(x.read_text(encoding="utf-8")) for x, _ in warten)
            print(f"[{jetzt()}] Uebersetzung: {len(warten)} Dateien mit offenen "
                  f"Abschnitten, {gesamt:,} Zeichen in ihnen")

        pfad, abschnitt = warten[0]
        rel = pfad.relative_to(WURZEL)
        wo = f"{rel}#{abschnitt}" if abschnitt else str(rel)
        if wo in gesehen:
            print(f"[{jetzt()}] {wo} zum zweiten Mal gewaehlt -- angehalten. "
                  "Der Detektor haelt einen fertigen Abschnitt fuer deutsch.")
            return 1
        gesehen.add(wo)
        if trocken:
            print(f"  wuerde uebersetzen: {wo}")
            gemacht += 1
            # Im Trockenlauf aendert sich nichts, also die naechste Datei zeigen.
            rest = [x for x in warten if x[0] != pfad]
            if not rest:
                return 0
            for pf, ab in rest[:7]:
                print(f"  wuerde uebersetzen: {pf.relative_to(WURZEL)}"
                      f"{'#' + ab if ab else ''}")
            return 0
        print(f"[{jetzt()}] {wo}")
        if lauf("uebersetzer", wo) != 0:
            print("  Lauf fehlgeschlagen -- angehalten.")
            reservieren(sorted({x for x, _ in offen()}))
            return 1
        eintragen(wo)
        gemacht += 1
    print(f"[{jetzt()}] {gemacht} Abschnitte uebersetzt, Grenze erreicht.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
