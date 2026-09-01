#!/usr/bin/env bash
# Setzt die Effizienzmassnahmen um und archiviert das ueberlaufene Logbuch.
#
#   bash ~/fabrik/einrichtung/14-sparsam.sh
#
# Anlass: Das Wochenkontingent ist fast erschoepft. Der Rechercheur verbrauchte
# 66 Prozent davon -- 43 Laeufe, 16 davon leer -- und sein Logbuch war auf 180.254
# Zeichen gewachsen, die er bei jedem Lauf mitliest.

set -euo pipefail
cd "$HOME/fabrik"

mkdir -p notizen/archiv

echo "=== Ueberlaufene Logbuecher archivieren (Grenze 12.000 Zeichen) ==="
heute=$(date +%Y-%m-%d)
for f in notizen/*.md; do
  case "$f" in *lehren.md|*VORLAGE.md) continue;; esac
  z=$(wc -c < "$f")
  if [ "$z" -gt 12000 ]; then
    name=$(basename "$f" .md)
    mv "$f" "notizen/archiv/$name-$heute.md"
    printf '  %-24s %8s Zeichen -> archiv/\n' "$name" "$z"
  fi
done

echo
echo "=== Sensorik von dreimal auf einmal taeglich ==="
PY_BIN="$(command -v python3)"
CLAUDE_DIR="$(dirname "$(command -v claude)")"
TMP="$(mktemp)"
crontab -l 2>/dev/null | grep -v 'sensorlauf.py' > "$TMP" || true
# 09:00 bleibt, 15:00 und 21:00 entfallen. Die Scouts sind billig, aber jedes
# zusaetzliche Signal zieht einen Rechercheurlauf nach sich -- und der kostet.
echo "0 9 * * * cd $HOME/fabrik && $PY_BIN agents/sensorlauf.py >> ops/sensorlauf.log 2>&1" >> "$TMP"
crontab "$TMP"
rm -f "$TMP"
crontab -l | grep -v '^PATH=' | sed 's/^/  /'

echo
echo "=== Neue Grundlast ==="
gesamt=0
for f in CLAUDE.md notizen/lehren.md grenzen.md; do
  z=$(wc -c < "$f"); gesamt=$((gesamt + z))
done
echo "  Grundlast je Lauf: $gesamt Zeichen (~$((gesamt / 4)) Tokens)"
groesstes=$(for f in notizen/*.md; do
  case "$f" in *lehren.md|*VORLAGE.md) continue;; esac
  echo "$(wc -c < "$f") $(basename "$f")"
done | sort -rn | head -1)
echo "  Groesstes Logbuch: $groesstes"
