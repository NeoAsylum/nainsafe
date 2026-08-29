#!/usr/bin/env bash
# Uebersicht ueber alle Marktprofile: Segment, Groesse, Luecke, Potenzial.
cd "$HOME/fabrik" || exit 1

printf '%-44s %-8s %s\n' "Segment" "Potenzial" "zugeschnittene Anbieter"
printf '%s\n' "--------------------------------------------------------------------------------"
for f in signals/maerkte/*.md; do
  [ -e "$f" ] || continue
  seg=$(grep -m1 '^segment:' "$f" | sed 's/segment: //' | cut -c1-42)
  pot=$(grep -m1 '^potenzial:' "$f" | sed 's/potenzial: //')
  anb=$(grep -m1 '^anbieter_zugeschnitten:' "$f" | sed 's/anbieter_zugeschnitten: //' | cut -c1-30)
  printf '%-44s %-8s %s\n' "$seg" "$pot" "$anb"
done

echo
echo "Verteilung:"
grep -h '^potenzial:' signals/maerkte/*.md 2>/dev/null | sort | uniq -c

echo
echo "Noch offen:"
python3 - <<'PY'
import sys
sys.path.insert(0, 'agents')
import repo
offen = repo.offene_segmente()
print(f"  {len(offen)} von {len(repo.segmentliste())} Segmenten")
for s in offen:
    print(f"    {s}")
PY
