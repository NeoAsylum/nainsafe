#!/usr/bin/env bash
set -euo pipefail
cd "$HOME/fabrik"
export PATH="$HOME/.local/bin:/usr/local/bin:/usr/bin:/bin"

python3 -m py_compile agents/*.py && rm -rf agents/__pycache__

git add -A
git commit -q -F - <<'ENDE'
Sparsamer: Notbremse, Logbuchgrenze, halbe Deckel

Das Wochenkontingent war fast erschoepft. Die Ursachen, gemessen:

Der Rechercheur verbrauchte 210 der 316 Dollar Gegenwert -- 66 Prozent --
bei 43 Laeufen, von denen 16 leer blieben. Sein Logbuch war auf 180.254
Zeichen gewachsen und wurde bei jedem seiner Laeufe mitgelesen: 45.000
Tokens, bevor er irgendetwas tat.

Vier Massnahmen:

Erstens die Logbuchgrenze, aus dem Vorschlag des Verbesserers: 12.000
Zeichen statt 30 Zeilen. Die alte Regel mass die falsche Groesse und
belohnte Zusammenziehen statt Streichen -- 213 Zeilen wurden zu 51, ohne
dass ein Eintrag entfiel. Anders als vorgeschlagen wird beim Erreichen der
Grenze archiviert, nicht gekuerzt: Hausregel 3 gilt auch fuer Logbuecher,
und der Verbesserer nannte selbst als staerksten Einwand, dass sein
Vorschlag Wissen vernichten kann.

Zweitens die Deckel: 15 auf 5 Recherchen, 10 auf 4 Kandidaten. Nicht aus
Sparsamkeit -- der Ideator meldete am selben Tag, dass jede vorliegende
Recherche rot oder verarbeitet ist. Der Engpass war nie ihre Zahl.

Drittens die Sensorik von dreimal auf einmal taeglich. Die Scouts sind
billig, aber jedes zusaetzliche Signal zieht einen Rechercheurlauf nach.

Viertens eine Notbremse in lauf.py: Ab 120 Dollar Gegenwert am Tag startet
kein Lauf mehr. Am 28.08. erzeugte ein einzelner Tag 95 Laeufe und 253
Dollar, ohne dass irgendetwas gewarnt haette -- es gab keine Stelle, an der
die Fabrik von selbst haette anhalten koennen.

Dazu laeuft der Rechercheur jetzt auf effort medium statt high, mit dem
ausdruecklichen Auftrag, nach den sechs Fragen aufzuhoeren.
ENDE

GIT_SSH_COMMAND="ssh -o BatchMode=yes" git push -q origin main
echo "committet:"
git log --oneline -1
echo
echo "=== Was ein Nachtlauf jetzt umfasst ==="
python3 agents/nachtlauf.py --trocken
