#!/usr/bin/env bash
# Zeigt, warum der letzte Ideator-Lauf nichts erzeugt hat, und wie die Ampeln stehen.
cd "$HOME/fabrik" || exit 1

echo "=== Notiz des letzten Ideator-Laufs ==="
sqlite3 state.db "SELECT substr(notiz,1,1200) FROM lauf WHERE rolle='ideator' ORDER BY id DESC LIMIT 1;"

echo
echo "=== Ampeln aller Recherchen ==="
grep -h '^ampel:' research/*.md 2>/dev/null | sort | uniq -c

echo
echo "=== Gibt es Recherchen zu den Modell-Signalen? ==="
for f in research/*.md; do
  sig=$(grep -m1 '^signal:' "$f" | cut -d' ' -f2-)
  case "$sig" in
    *modelle*) printf '  %-52s %s\n' "$(basename "$f")" "$(grep -m1 '^ampel:' "$f")" ;;
  esac
done
echo "  (leer = die Modell-Signale sind noch nicht ausgegraben)"

echo
echo "=== Signale ohne Recherche ==="
python3 - <<'PY'
import sys
sys.path.insert(0, 'agents')
import repo
offen = repo.offene_recherchen(50)
print(f"  {len(offen)} offen")
for p in offen[:12]:
    print(f"    {p}")
PY
