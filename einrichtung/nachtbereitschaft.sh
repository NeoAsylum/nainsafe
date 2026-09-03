#!/usr/bin/env bash
# Letzte Kontrolle vor der Nacht. Berichtet, handelt nicht.
#
# Bis zum 2026-09-03 stand hier `git add -A`, ein `git commit` mit einer **fest
# eingebauten** Botschaft und ein `git push`. Die Botschaft stammte vom 2026-08-30
# ("Ideator liest die Anwaltsvorschlaege zuerst") und war seither eingefroren. Wer
# dieses Skript aufrief -- der Name klingt nach Diagnose --, veroeffentlichte damit
# den gesamten Arbeitsbereich unter einer Beschreibung, die nichts mit dem Inhalt zu
# tun hatte. Am 2026-09-03 um 18:41 ist genau das passiert: Commit 95903a6 traegt den
# Betreff einer Aenderung aus der Suchphase und enthaelt in Wahrheit die Sperre des
# Tageslaufs, das Sicherungsskript und CMake-Arbeit eines Bauagenten.
#
# Ein Skript, das committet, heisst nicht "Bereitschaft". Das Committen macht der
# Runner (`agents/lauf.py:committen`), der die Botschaft aus dem Lauf bildet.
set -euo pipefail
cd "$HOME/fabrik"
export PATH="$HOME/.local/bin:/usr/local/bin:/usr/bin:/bin"

echo "════════ Bereitschaft ════════"
bash einrichtung/pruefen.sh 2>&1 | tail -26

echo
OFFEN="$(git status --porcelain)"
if [ -n "$OFFEN" ]; then
    echo "Uncommittet im Arbeitsbereich:"
    echo "$OFFEN" | sed 's/^/  /'
    echo
    echo "Das committet dieses Skript absichtlich nicht. Entweder gehoert es zu einem"
    echo "Lauf -- dann committet ihn der Runner --, oder es ist Handarbeit und braucht"
    echo "eine Botschaft, die zum Inhalt passt."
else
    echo "Arbeitsbereich sauber."
fi
