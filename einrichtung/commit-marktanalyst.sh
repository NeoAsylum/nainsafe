#!/usr/bin/env bash
# Einmaliges Hilfsskript: committet den Markt-Analysten und startet seinen ersten Lauf.
set -euo pipefail
cd "$HOME/fabrik"
export PATH="$HOME/.local/bin:/usr/local/bin:/usr/bin:/bin"

git add -A
git commit -q -F - <<'ENDE'
Markt-Analyst: vom Markt zum Produkt statt vom Vorfall zur Idee

Alle bisherigen Scouts warten darauf, dass etwas passiert -- eine Pflicht
entsteht, ein Anbieter geht, jemand beschwert sich. Ideen aus Vorfaellen
scheitern regelmaessig an einer Praemisse, die erst am Ende geprueft wird:
Idee 0009 starb daran, dass die Branche das Problem laengst vertraglich
geloest hatte, Idee 0005 daran, dass niemand einen Weg zum ersten Kunden
kannte.

Der Markt-Analyst dreht die Richtung um. Er nimmt sich ein Segment aus einer
festen Liste vor und beantwortet sechs Fragen mit Zahlen: wie viele Betriebe,
was setzen sie um, welche Handarbeit kehrt wieder, was kostet sie heute, wer
bedient sie schon, und ueber welchen Kanal erreicht man sie. Zahlungs-
bereitschaft und Vertriebsweg stehen damit am Anfang statt am Ende.

Der Ideator uebernimmt beides woertlich aus dem Profil, statt es neu zu
erfinden: kosten_der_handarbeit ist die Obergrenze des Preises,
erreichbar_ueber die Antwort auf die Frage, an der zuletzt jede zweite Idee
gestorben ist. Aus einem Profil entstehen mehrere Ideen, nicht eine.

22 Segmente im Suchraum, ein Profil je Lauf. Ein sauber begruendetes
"hier ist nichts" wird ebenfalls geschrieben -- es verhindert, dass die
Fabrik dasselbe Segment in drei Monaten erneut durchleuchtet.
ENDE

GIT_SSH_COMMAND="ssh -o BatchMode=yes" git push -q origin main
echo "committet und gepusht:"
git log --oneline -1

echo
echo "=== Erster Lauf des Markt-Analysten ==="
python3 agents/lauf.py markt-analyst
