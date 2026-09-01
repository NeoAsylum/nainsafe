#!/usr/bin/env bash
# Committet Anwalt, Verbesserer und weg.py -- und laesst den Anwalt auf die
# drei wartenden Kandidaten los, damit der Wochenlauf am Sonntag arbeiten kann.
set -euo pipefail
cd "$HOME/fabrik"
export PATH="$HOME/.local/bin:/usr/local/bin:/usr/bin:/bin"

git add -A
git commit -q -F - <<'ENDE'
Anwalt, Verbesserer, Nachvollziehbarkeit: ein Einwand ist kein Todesurteil

Bisher toetete jeder mehrheitliche Einwand eine Idee sofort. In fast jeder
Angriffsdatei steht aber ein Abschnitt "Was ihn entkraeften wuerde", den
niemand gelesen hat -- bei den bisherigen Ideen fuenfmal.

Der Anwalt der Idee laeuft nach den fuenf Skeptikern und prueft jeden
Einwand: entkraeftet, loesbar, teuer oder unloesbar, jeweils mit Weg und
Preis. Der Portfolio-Manager zaehlt danach nur noch die Einwaende, die
stehen geblieben sind. Unternehmertum heisst, jeden Tag Probleme zu loesen;
ein Einwand ist der Anfang einer Aufgabe, nicht ihr Ende.

Zwei Einwaende bleiben unverhandelbar: Recht mit G5 oder G6, und Vertrieb
ohne benennbaren Kanal. Loest der Anwalt sie durch einen anderen Zuschnitt,
ist das per Definition eine neue Idee -- sie geht in den Abschnitt "Andere
Idee daraus" und von dort an den Ideator. Das ist der wertvollste Ertrag
einer gescheiterten Idee: ein Zuschnitt, der schon durch fuenf Linsen ging.

weg.py macht den Weg nachvollziehbar. Mit Ideen-ID zeigt es den kompletten
Pfad von Signal ueber Recherche, Filter und Angriffe bis zum Urteil, mit
Kosten. Ohne Argument zeigt es das Muster: in welchem Schritt Ideen sterben,
an welcher Grenze, unter welcher Linse -- und wie viele Einwaende selbst
einen Weg heraus nennen.

Der Verbesserer schliesst den Regelkreis. Woechentlich, genau ein Vorschlag,
auf Basis von weg.py, kontingent.py und den Logbuechern. Er aendert nichts
selbst: Regeln aendert nur der Betreiber. Vier Ebenen in fester Reihenfolge,
die erste ist die ergiebigste -- etwas wird spaet geprueft, das frueh
pruefbar waere.
ENDE

GIT_SSH_COMMAND="ssh -o BatchMode=yes" git push -q origin main
echo "committet:"
git log --oneline -1

echo
echo "=== Anwalt auf die wartenden Kandidaten ==="
python3 agents/angriffslauf.py
