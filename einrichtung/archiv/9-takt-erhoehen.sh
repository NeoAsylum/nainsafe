#!/usr/bin/env bash
# Erhoeht die Taktung: Sensorik mehrmals taeglich statt nur nachts.
#
#   bash ~/fabrik/einrichtung/9-takt-erhoehen.sh
#
# Die Vollkette laeuft weiter einmal nachts -- sie erzeugt Kandidaten, und mehr
# Kandidaten als der Betreiber am Sonntag sehen kann sind wertlos. Was sich lohnt,
# ist haeufigere Sensorik: Signale koennen liegen bleiben, bis die Kette sie abholt,
# und ein Markt-Scout, der viermal am Tag schaut, findet Abkuendigungen frueher.

set -euo pipefail
ZIEL="$HOME/fabrik"
PY="$(command -v python3)"
CLAUDE_DIR="$(dirname "$(command -v claude)")"

TMP="$(mktemp)"
crontab -l 2>/dev/null | grep -v \
  'nachtlauf.py\|wochenlauf.py\|git push origin\|git bundle create\|sensorlauf.py\|^PATH=' \
  > "$TMP" || true

cat >> "$TMP" <<CRON
PATH=$CLAUDE_DIR:/usr/local/bin:/usr/bin:/bin
# Vollkette: sammeln, ausgraben, verdichten, angreifen
0 3 * * * cd $ZIEL && $PY agents/nachtlauf.py >> ops/nachtlauf.log 2>&1
# Nur Sensorik, dreimal ueber den Tag verteilt -- Signale duerfen liegen bleiben
0 9,15,21 * * * cd $ZIEL && $PY agents/sensorlauf.py >> ops/sensorlauf.log 2>&1
# Vorstand
0 7 * * 0 cd $ZIEL && $PY agents/wochenlauf.py >> ops/wochenlauf.log 2>&1
# Sicherung
30 3 * * * cd $ZIEL && GIT_SSH_COMMAND="ssh -o BatchMode=yes" git push origin main >> ops/backup.log 2>&1
45 3 * * * cd $ZIEL && git bundle create $HOME/sicherung/fabrik-\$(date +\%Y-\%m-\%d).bundle --all >> ops/backup.log 2>&1
CRON

crontab "$TMP"
rm -f "$TMP"

echo "Neue Zeitplanung:"
crontab -l | grep -v '^#' | sed 's/^/  /'
echo
echo "Damit laufen die vier Sensoren viermal taeglich statt einmal."
echo "Nach ein paar Tagen gegenpruefen, ob die Zusatzlaeufe noch Neues finden:"
echo "  python3 agents/auslastung.py && cat ops/auslastung.md"
echo "Eine Rolle, die dort mit vielen Laeufen und null ergiebigen steht, laeuft zu oft."
