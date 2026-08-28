#!/usr/bin/env bash
# Letzte Kontrolle vor der Nacht: committen, pushen, alles gegenpruefen.
set -euo pipefail
cd "$HOME/fabrik"
export PATH="$HOME/.local/bin:/usr/local/bin:/usr/bin:/bin"

git add -A
git commit -q -F - <<'ENDE'
Ideator liest die Anwaltsvorschlaege zuerst

Der Anwalt hat aus drei gescheiterten Ideen drei neue Zuschnitte gefunden,
jeder loest genau den Einwand, an dem das Original starb: Zettelfoto vom
Handwerksbetrieb zum Lohnbuero, wo Tipparbeit Herstellkosten sind statt
Feierabendlast; Haushaltsabrechnung zu Betreuungsdiensten, wo ein
Kostentraeger zahlt und aus "waere nett" ein "muss" wird; Asbestanzeige vom
mittleren in den hohen Risikobereich, wo die Anzeigepflicht real ist.

Diese Vorschlaege waeren nie angekommen -- der Ideator liest signals/ und
research/, nicht die Angriffsordner. Jetzt liest er sie zuerst.

Es ist das beste Material der Fabrik: Der Zuschnitt ist schon durch fuenf
Linsen gegangen, sein Vorgaenger ist an bekannter Stelle gestorben, und der
Anwalt hat benannt, warum die neue Fassung dort nicht stirbt. Er gibt
regelmaessig Auflagen mit, welche Einwaende mitreisen -- die gehoeren in die
offenen Fragen der neuen Idee.
ENDE

GIT_SSH_COMMAND="ssh -o BatchMode=yes" git push -q origin main
echo "committet und gepusht."
echo

echo "════════ Bereitschaft ════════"
bash einrichtung/pruefen.sh 2>&1 | tail -24

echo
echo "════════ Was heute Nacht laeuft ════════"
python3 agents/nachtlauf.py --trocken
echo
python3 agents/wochenlauf.py --trocken

echo
echo "════════ Zeitplanung ════════"
crontab -l | grep -v '^PATH=' | grep -v '^#'
