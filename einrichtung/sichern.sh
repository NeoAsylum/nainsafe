#!/bin/sh
# Push und Bundle, nachholend statt auf die Minute.
#
# Vorher standen beide als feste Uhrzeit in der crontab (03:30 und 03:45). Am
# 2026-09-03 schlief der Windows-Wirt von 21:30 bis 15:00 durch; cron holt nichts
# nach, also fehlten Push und Bundle dieses Tages ersatzlos. Dieses Skript laeuft
# stuendlich und prueft selbst, ob heute schon gesichert wurde -- ein Bundle je Tag,
# egal zu welcher Stunde die Maschine wach ist.
set -eu
cd /home/adria/fabrik

GIT_SSH_COMMAND="ssh -o BatchMode=yes" git push origin main || echo "Push fehlgeschlagen"

ZIEL="/home/adria/sicherung/fabrik-$(date +%Y-%m-%d).bundle"
if [ ! -f "$ZIEL" ]; then
    git bundle create "$ZIEL" --all
    echo "Bundle erzeugt: $ZIEL"
fi
