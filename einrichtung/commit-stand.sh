#!/usr/bin/env bash
set -euo pipefail
cd "$HOME/fabrik"
export PATH="$HOME/.local/bin:/usr/local/bin:/usr/bin:/bin"

git add -A
git commit -q -F - <<'ENDE'
stand.py zeigt alle Signalarten, nicht nur die ersten vier

Die Liste der Signalordner war hartcodiert. Damit blieben ausgerechnet die
beiden neuen Arten unsichtbar -- signals/modelle und signals/maerkte, aus
denen die bisher besten Ideen stammen. Jetzt wird das Verzeichnis gelesen,
und Recherchen und Ideen stehen mit dabei.
ENDE

GIT_SSH_COMMAND="ssh -o BatchMode=yes" git push -q origin main
git log --oneline -1
