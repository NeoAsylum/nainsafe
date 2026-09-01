#!/usr/bin/env python3
"""Fuehrt die Konzeptionsphase fuer eine Idee durch -- Gate 1 bis Gate 2.

    python3 agents/konzeptlauf.py <idee-id> [--trocken] [--ab <stufe>]

Die Phase beginnt, wenn der Betreiber eine Idee an Gate 1 auf `erkundung` gesetzt hat,
und liefert den Entwurf, aus dem gebaut wird. Ergebnis ist `specs/<idee-id>/` mit drei
Dokumenten:

  1. datenkurator        allein und zuerst -- er beantwortet eine binaere Sperrfrage
  2. spielentwerfer      braucht zu wissen, welche Daten es ueberhaupt gibt
  3. architekt           braucht den Entwurf
  4. entwurf-pruefer     prueft beide, blind fuer ihre Begruendungen

Stufe 1 laeuft ausdruecklich allein: Faellt die Lizenzfrage negativ aus, ist jede
weitere Konzeptionsarbeit verschwendet.

Die wirtschaftliche und rechtliche Pruefung -- Oekonom, Vertriebsplaner,
Compliance-Pruefer, Urlaubstester, Antrags-Vorbereiter, Konzept-Judge -- lag hier bis
zum 2026-08-31 als Stufen 4 bis 6. Der Betreiber hat sie in den Hintergrund gestellt;
die Rollendateien liegen unter `agents/rollen/archiv/`. Danach uebernimmt
`agents/baulauf.py`.
"""

from __future__ import annotations

import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import repo  # noqa: E402
from lauf import WURZEL, frontmatter, jetzt, lauf  # noqa: E402
from nachtlauf import phase  # noqa: E402

# (Name der Stufe, Rollen, die darin parallel laufen)
STUFEN: list[tuple[str, list[str]]] = [
    ("Daten", ["datenkurator"]),
    ("Entwurf", ["spielentwerfer"]),
    ("Technik", ["architekt"]),
    # Der Entwurf wird geprueft wie jedes Bauwerk -- und zwar hier, weil ein Fehler im
    # Entwurf sich in jedem Paket danach vervielfaeltigt. Teuerster Fund, billigste
    # Pruefung.
    ("Review", ["entwurf-pruefer"]),
    # Oekonom, Vertriebsplaner, Compliance-Pruefer, Urlaubstester, Antrags-Vorbereiter
    # und Konzept-Judge liegen seit dem 2026-08-31 unter agents/rollen/archiv/. Der
    # Betreiber hat entschieden: gebaut wird, die wirtschaftliche Betrachtung tritt in
    # den Hintergrund. Die Dateien bleiben -- zurueckholen heisst zurueckschieben.
]

# Wie oft der Entwurf zurueckgehen darf, bevor nicht mehr er das Problem ist, sondern
# das Abnahmekriterium.
#
# Diese Bremse hat am 2026-09-01 gefehlt, und sie hat 95 Dollar gekostet. Die Regel
# stand im Arbeitspaket -- durchsetzen konnte sie nur der Projektmanager, und der laeuft
# im Baulauf, der nie lief, weil der Entwurf zurueckgewiesen war. Verklemmung durch
# Konstruktion. Eine Regel, die nur an der Stelle steht, die sie nicht erreicht, ist
# keine Regel.
#
# Der zweite Grund, warum Geld allein nicht reicht: Die Schleife blieb brav unter der
# Tagesgrenze. Sie war nicht zu teuer, sie war ergebnislos -- Befunde stagnierten bei
# zwei, waehrend die Dokumente von 23 auf 242 kB wuchsen.
RUECKLAUF_MAX = 3


def entwurfsurteile(idee_id: str) -> list[dict]:
    """Alle Urteile des Entwurfspruefers, aeltestes zuerst."""
    ordner = WURZEL / "ventures" / idee_id / "befunde"
    if not ordner.is_dir():
        return []
    treffer = []
    for d in ordner.glob("pruefung-*.md"):
        kopf, _ = frontmatter(d.read_text(encoding="utf-8"))
        if kopf.get("pruefer") == "entwurf-pruefer":
            treffer.append((d.stat().st_mtime, kopf))
    return [k for _, k in sorted(treffer)]


# Was am Ende dastehen soll. Fehlt etwas, sagt der Lauf es -- der Judge liest sonst
# eine Luecke, ohne sie zu bemerken.
ERWARTET = {
    "datenkurator": "daten.md",
    "spielentwerfer": "spiel.md",
    "architekt": "technik.md",
}


def status(idee_id: str) -> str | None:
    datei = WURZEL / "ideas" / f"{idee_id}.md"
    if not datei.exists():
        return None
    kopf, _ = frontmatter(datei.read_text(encoding="utf-8"))
    return kopf.get("status")


def sperrfrage_negativ(idee_id: str) -> bool:
    """Hat der Datenkurator die Sperrfrage negativ beantwortet?"""
    d = WURZEL / "specs" / idee_id / "daten.md"
    if not d.exists():
        return False
    kopf, _ = frontmatter(d.read_text(encoding="utf-8"))
    return str(kopf.get("sperrfrage", "")).strip() == "negativ"


def main(idee_id: str, trocken: bool = False, ab: int = 1) -> int:
    st = status(idee_id)
    if st is None:
        sys.exit(f"Keine Idee {idee_id} unter ideas/.")
    if st != "erkundung" and not trocken:
        sys.exit(
            f"Idee {idee_id} steht auf `{st}`, nicht auf `erkundung`.\n"
            "Die Konzeptionsphase beginnt nach Gate 1, und Gate 1 setzt ein Mensch.\n"
            "Setze den Status von Hand, wenn du die Freigabe erteilt hast."
        )

    ziel = WURZEL / "specs" / idee_id
    print(f"[{jetzt()}] Konzeptlauf {idee_id} -- Ziel {ziel.relative_to(WURZEL)}")

    if trocken:
        for nr, (name, rollen) in enumerate(STUFEN, 1):
            marke = "  " if nr >= ab else "  (uebersprungen) "
            print(f"{marke}{nr}. {name:10} {', '.join(rollen)}")
        return 0

    # Konvergenzbremse vor dem ersten Token: Geht der Entwurf zum RUECKLAUF_MAX-ten Mal
    # zurueck, ist nicht der Entwerfer das Problem. Weiterschreiben hilft dann nicht.
    zurueck = [u for u in entwurfsurteile(idee_id) if u.get("urteil") == "zurueck"]
    if len(zurueck) >= RUECKLAUF_MAX:
        print()
        print(f"  ANGEHALTEN: Der Entwurf ist {len(zurueck)} Mal zurueckgegangen "
              f"(Grenze {RUECKLAUF_MAX}).")
        print("  Damit ist nicht mehr der Entwerfer das Problem, sondern das")
        print("  Abnahmekriterium. Eine weitere Schreibrunde findet dieselbe Sorte")
        print("  Befund im neu geschriebenen Material -- das ist am 2026-09-01")
        print("  vier Durchgaenge lang nachgemessen worden.")
        print()
        letzte = zurueck[-1]
        print(f"  Letztes Urteil: {letzte.get('befunde', '?')} Befunde.")
        print(f"  Zu lesen: ventures/{idee_id}/befunde/ und das Abnahmepaket.")
        print("  Der Betreiber entscheidet: Kriterium aendern, Befunde als")
        print("  Arbeitspakete an den Bau geben, oder Entwurf verwerfen.")
        return 0

    ziel.mkdir(parents=True, exist_ok=True)
    fehler = 0

    for nr, (name, rollen) in enumerate(STUFEN, 1):
        if nr < ab:
            print(f"  Stufe {nr} ({name}) uebersprungen.")
            continue

        if len(rollen) == 1:
            if lauf(rollen[0], idee_id) != 0:
                fehler += 1
                print(f"  {rollen[0]} fehlgeschlagen -- Kette laeuft weiter.")
        else:
            fehler += phase(name, [(r, idee_id) for r in rollen])

        # Nach Stufe 1: Wenn die Lizenzfrage negativ ausfaellt, hat der Rest keinen
        # Sinn. Lieber hier anhalten und den Betreiber entscheiden lassen.
        if nr == 1 and sperrfrage_negativ(idee_id):
            print()
            print("  ANGEHALTEN: Der Datenkurator meldet `sperrfrage: negativ` --")
            print("  keine Quelle erlaubt die gewerbliche Weiterverbreitung.")
            print("  Damit faellt die vierte Pruefachse weg (agentenbau.md), und der")
            print("  Grund fuer die echte Welt ebenfalls. Das ist eine Entscheidung")
            print("  des Betreibers, nicht der Kette:")
            print("    specs/%s/daten.md lesen, dann entweder erfundene Welt," % idee_id)
            print("    Daten beim Start laden, oder das Vorhaben einstellen.")
            print("  Weiter danach mit: --ab 2")
            return 0

    fehlend = [d for d in ERWARTET.values() if not (ziel / d).exists()]
    print(f"[{jetzt()}] Konzeptlauf beendet, {fehler} Fehler.")
    if fehlend:
        print(f"  FEHLT in specs/{idee_id}/: {', '.join(sorted(fehlend))}")
    vorlage = WURZEL / "gates" / f"{idee_id}-g2.md"
    if vorlage.exists():
        print(f"  Gate-2-Vorlage liegt bereit: {vorlage.relative_to(WURZEL)}")
    return 0 if fehler == 0 else 1


if __name__ == "__main__":
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    if not args:
        offen = [k["_id"] for k in repo.ideen("erkundung")]
        sys.exit("Aufruf: python3 agents/konzeptlauf.py <idee-id>\n"
                 + ("Auf `erkundung`: " + ", ".join(offen) if offen
                    else "Zurzeit steht keine Idee auf `erkundung`."))
    ab = 1
    if "--ab" in sys.argv:
        ab = int(sys.argv[sys.argv.index("--ab") + 1])
    sys.exit(main(args[0], "--trocken" in sys.argv, ab))
