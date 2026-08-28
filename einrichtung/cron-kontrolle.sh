#!/usr/bin/env bash
# Hat cron tatsaechlich gefeuert? Prueft Logs, Journal und Daemon.
cd "$HOME/fabrik" || exit 1

echo "=== Jetzt ==="
date '+%Y-%m-%d %H:%M:%S %Z (UTC%:z)'
echo "Journal schreibt in UTC -- Cron feuert nach lokaler Zeit."

echo
echo "=== Logdateien ==="
for f in nachtlauf sensorlauf wochenlauf backup; do
  if [ -s "ops/$f.log" ]; then
    printf '  %-12s %s Zeilen, zuletzt: %s\n' "$f" \
      "$(wc -l < "ops/$f.log")" "$(tail -1 "ops/$f.log" | cut -c1-60)"
  else
    printf '  %-12s LEER oder fehlt\n' "$f"
  fi
done

echo
echo "=== Laeufe je Stunde heute (UTC) ==="
sqlite3 -column state.db "
  SELECT substr(gestartet,12,2) AS stunde_utc, count(*) AS laeufe
  FROM lauf WHERE gestartet > date('now')
  GROUP BY stunde_utc ORDER BY stunde_utc;"

echo
echo "=== cron-Daemon ==="
if pgrep -x cron >/dev/null; then
  echo "  laeuft"
else
  echo "  LAEUFT NICHT -- nichts wird ausgefuehrt"
fi

echo
echo "=== Naechste Feuerzeitpunkte (lokal) ==="
crontab -l | grep -v '^PATH=' | grep -v '^#' | while read -r zeile; do
  min=$(echo "$zeile" | awk '{print $1}')
  std=$(echo "$zeile" | awk '{print $2}')
  was=$(echo "$zeile" | grep -oE '[a-z]+\.py|git push|git bundle' | head -1)
  printf '  %-14s um %s:%s Uhr\n' "$was" "$std" "$min"
done
