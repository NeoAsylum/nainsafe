#!/usr/bin/env bash
# Was jeder Lauf traegt, bevor er irgendetwas tut -- und welche Rolle wie oft laeuft.
cd "$HOME/fabrik" || exit 1

echo "=== Grundlast: wird bei JEDEM Lauf geladen ==="
printf '%-34s %9s  %8s\n' "Datei" "Zeichen" "~Tokens"
gesamt=0
for f in CLAUDE.md notizen/lehren.md grenzen.md; do
  [ -f "$f" ] || continue
  z=$(wc -c < "$f")
  gesamt=$((gesamt + z))
  printf '%-34s %9s  %8s\n' "$f" "$z" "$((z / 4))"
done
printf '%-34s %9s  %8s\n' "zusammen" "$gesamt" "$((gesamt / 4))"

echo
echo "=== Logbuecher: wird von der jeweiligen Rolle geladen ==="
printf '%-34s %9s  %8s\n' "Logbuch" "Zeichen" "~Tokens"
for f in notizen/*.md; do
  case "$f" in *lehren.md|*VORLAGE.md) continue;; esac
  z=$(wc -c < "$f")
  [ "$z" -gt 3000 ] && printf '%-34s %9s  %8s\n' "$(basename "$f")" "$z" "$((z / 4))"
done
echo "(nur Logbuecher ueber 3.000 Zeichen)"

echo
echo "=== Laeufe und Verbrauch je Rolle, letzte 7 Tage ==="
sqlite3 -column -header state.db "
  SELECT rolle,
         count(*) AS laeufe,
         sum(ergebnis='leer') AS leer,
         round(sum(kosten_eur),1) AS wert,
         round(sum(kosten_eur)/count(*),2) AS je_lauf
  FROM lauf WHERE gestartet > datetime('now','-7 days') AND ergebnis != 'laeuft'
  GROUP BY rolle ORDER BY sum(kosten_eur) DESC;"

echo
echo "=== Laeufe je Tag ==="
sqlite3 -column state.db "
  SELECT date(gestartet), count(*), round(sum(kosten_eur),1)
  FROM lauf WHERE gestartet > datetime('now','-7 days')
  GROUP BY date(gestartet);"
