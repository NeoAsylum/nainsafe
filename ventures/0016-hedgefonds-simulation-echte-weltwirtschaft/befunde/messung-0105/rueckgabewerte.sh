#!/bin/sh
# Die Rueckgabewerte im Wortlaut -- Paket 0105.
#
# Warum eigens: `WILL_FAIL` beweist nur "ungleich 0". Der Riegel unterscheidet aber
# zwei Sorten Rot, und sie heissen Verschiedenes: 1 ist ein Befund am Bestand, 2 ein
# gerissener Selbsttest im Programm selbst. Ein Nachweis, der beide zusammenwirft,
# koennte einen kaputten Riegel als gefangenen Fehler ausweisen.
#
# Aufruf: rueckgabewerte.sh <riegel_vorher> <riegel_nachher> <messwurzel>
#
# Erwartet wird, je Baum und Fassung:
#
#   baum      -- die Kopie des Bezugscommits, unveraendert:   vorher 0, nachher 0
#   baum_gut  -- dieselbe Kopie mit einer richtigen Belegstelle ueber den Umbruch:
#                vorher 1 (der Befund, an dem nichts kaputt ist), nachher 0
#   baum_tot  -- dieselbe Stelle mit einer Ueberschrift, die es nicht gibt:
#                vorher 1, nachher 1 (die Lockerung laesst keine tote Stelle durch)

vorher="$1"
nachher="$2"
wurzel="$3"

erwartet_vorher="0 1 1"
erwartet_nachher="0 0 1"

gemessen_vorher=""
gemessen_nachher=""

for baum in baum baum_gut baum_tot; do
    venture="$wurzel/$baum/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
    spezifikation="$wurzel/$baum/specs/0016-hedgefonds-simulation-echte-weltwirtschaft"

    "$vorher" "$venture" "$spezifikation" > /dev/null 2>&1
    code_vorher=$?
    "$nachher" "$venture" "$spezifikation" > /dev/null 2>&1
    code_nachher=$?

    echo "$baum: vorher $code_vorher, nachher $code_nachher"
    gemessen_vorher="$gemessen_vorher $code_vorher"
    gemessen_nachher="$gemessen_nachher $code_nachher"
done

# Der Vergleich steht hier und nicht im Auge des Lesers: Ein Skript, das nur druckt,
# ist ein Bericht und kein Riegel.
fehler=0
if [ "$(echo $gemessen_vorher)" != "$erwartet_vorher" ]; then
    echo "vorher:  erwartet [$erwartet_vorher], gemessen [$(echo $gemessen_vorher)]"
    fehler=1
fi
if [ "$(echo $gemessen_nachher)" != "$erwartet_nachher" ]; then
    echo "nachher: erwartet [$erwartet_nachher], gemessen [$(echo $gemessen_nachher)]"
    fehler=1
fi

exit $fehler
