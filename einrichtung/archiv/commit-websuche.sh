#!/usr/bin/env bash
# Committet die Websuche-Erweiterung und laesst den Ideator die zurueckgestellten
# Anwaltsvorschlaege erneut pruefen -- jetzt kann er ihre Fragen klaeren.
set -euo pipefail
cd "$HOME/fabrik"
export PATH="$HOME/.local/bin:/usr/local/bin:/usr/bin:/bin"

git add -A
git commit -q -F - <<'ENDE'
Websuche fuer alle Rollen

Der Ideator hatte drei Anwaltsvorschlaege vorliegen und griff nur einen auf.
Nicht aus Nachlaessigkeit: Er hatte zu den anderen beiden je eine toedliche
Frage notiert -- ob die Laender oeffentliche Verzeichnisse anerkannter
Angebote fuehren, ob ein Dienst mit Abrechnung gegenueber Pflegekassen unter
eine Zulassungspflicht nach Paragraf 302 SGB V faellt -- und konnte sie nicht
beantworten. Keine Websuche in seiner Werkzeugliste.

Das galt fuer sechs Rollen, darunter den Fit-Filter und die Linse Betrieb.
Alle achtzehn haben jetzt WebSearch und WebFetch.

Damit das die Rollentrennung nicht aufloest, steht ihr Zweck in CLAUDE.md:
Suchen, wenn eine Antwort die eigene Arbeit blockiert -- nicht, wenn sie nur
interessieren wuerde. Wer als Ideator Marktdaten erhebt, schreibt eine
zweite Fassung dessen, was der Rechercheur schon hat. Die Rollentrennung
steht im Auftrag, nicht in der Werkzeugliste; eine fehlende Faehigkeit ist
die falsche Art, sie durchzusetzen.
ENDE

GIT_SSH_COMMAND="ssh -o BatchMode=yes" git push -q origin main
echo "committet:"
git log --oneline -1

echo
echo "=== Ideator erneut -- jetzt mit Websuche ==="
python3 agents/lauf.py ideator
