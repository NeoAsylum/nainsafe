"""Legt die zwei Mutanten zu Paket 0105 an: dieselbe Quelle, je eine Zeile entschaerft.

Warum Mutanten und nicht der Stand von vorher: Die Fassung unter `baum/` traegt die vier
neuen Faelle in `ZITATFAELLE` gar nicht -- sie koennte nicht zeigen, dass *diese Tabelle*
die Regel deckt, sondern nur, dass irgendetwas anders ist. Ein Mutant ist deshalb der
**ausgelieferte Stand mit genau einer entschaerften Zeile**.

Warum **zwei**: Die Regel besteht aus zwei Haelften, und ein einziger Mutant koennte
nicht zeigen, dass die Tabelle beide misst.

  `ohne_grenze`   Die Grenze am Zeilenende faellt ganz weg. Innerhalb eines Absatzes
                  steigen die Zeilennummern, `>=` ist damit immer wahr -- und
                  `heimatzeile` bleibt gelesen, sonst wuerde der Uebersetzer rot statt
                  des Tests.
  `grenze_am_wort` Die Grenze bleibt, haengt aber an der Zeile des **Schluesselworts**
                  statt an der des **Namens**. Das ist der naheliegende Fehlgriff: Wer
                  ihn tut, verliert die Form, bei der das Wort am Zeilenende steht.

                  Gegriffen wird `i - 1` und nicht `i`, und das ist gemessen: `i` zeigt
                  auf das Leerzeichen, zu dem `haenge_zeile_an` den Umbruch macht, und
                  dieses Leerzeichen traegt bereits die Nummer der **neuen** Zeile.
                  `zeile_bei(i)` ist damit dieselbe Zeile wie `zeile_bei(j)` -- ein
                  Mutant, der nichts aendert, und er lief am 2026-09-05 gruen durch.
                  Erst `i - 1` trifft das letzte Zeichen des Schluesselworts.

Der Lauf bricht ab, wenn ein Wortlaut nicht **genau einmal** vorkommt: Ein Mutant, der
still nichts geaendert hat, wiese die Regel als gedeckt aus, obwohl niemand sie gemessen
hat.

Aufruf: python3 mutiere.py
"""

import pathlib
import sys

HIER = pathlib.Path(__file__).resolve().parent
QUELLE = HIER.parent.parent / "werkzeuge" / "belegstellen" / "belegstellen_riegel.cpp"

MUTANTEN = [
    ("ohne_grenze",
     "absatz.zeile_bei(ende) == heimatzeile",
     "absatz.zeile_bei(ende) >= heimatzeile"),
    ("grenze_am_wort",
     "const std::size_t heimatzeile = absatz.zeile_bei(j);",
     "const std::size_t heimatzeile = absatz.zeile_bei(i - 1);"),
]


def main():
    text = QUELLE.read_text(encoding="utf-8")
    for name, vorher, nachher in MUTANTEN:
        anzahl = text.count(vorher)
        if anzahl != 1:
            print("Abbruch: '%s' kommt %d mal vor, erwartet war genau einmal."
                  % (vorher, anzahl))
            return 1
        ziel = HIER / "mutant" / name / "belegstellen_riegel.cpp"
        ziel.parent.mkdir(parents=True, exist_ok=True)
        ziel.write_text(text.replace(vorher, nachher), encoding="utf-8")
        print("Mutant geschrieben:", ziel)
        print("  %s  ->  %s" % (vorher, nachher))
    return 0


if __name__ == "__main__":
    sys.exit(main())
