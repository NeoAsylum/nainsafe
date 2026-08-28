#!/usr/bin/env bash
# Archiviert Recherchen, damit sie neu erstellt werden.
#
#   bash ~/fabrik/einrichtung/12-recherchen-erneuern.sh <muster> [<muster> ...]
#
# Nach einer Aenderung an der Ampel-Definition sind die alten Urteile nach der alten
# Regel entstanden. Geloescht wird nichts -- die alte Fassung wandert nach
# research/ueberholt/ und bleibt nachlesbar. Danach gilt das Signal wieder als offen
# und wird beim naechsten Lauf neu ausgegraben.

set -euo pipefail
cd "$HOME/fabrik"

if [ $# -eq 0 ]; then
  echo "Kein Muster angegeben. Beispiel:"
  echo "  bash einrichtung/12-recherchen-erneuern.sh poolservice reinigungsfirmen"
  exit 1
fi

mkdir -p research/ueberholt
verschoben=0

for muster in "$@"; do
  for datei in research/*"$muster"*.md; do
    [ -e "$datei" ] || continue
    ziel="research/ueberholt/$(basename "$datei" .md)-$(date +%Y%m%d).md"
    mv "$datei" "$ziel"
    echo "  $(basename "$datei") -> ueberholt/"
    verschoben=$((verschoben + 1))
  done
done

echo
echo "$verschoben Recherchen archiviert."
python3 - <<'PY'
import sys
sys.path.insert(0, 'agents')
import repo
offen = repo.offene_recherchen(50)
print(f"{len(offen)} Signale gelten jetzt als offen.")
PY
