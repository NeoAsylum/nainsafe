#!/usr/bin/env bash
# Gibt jeder Rolle Schreibrecht auf ihr eigenes Logbuch und nur auf dieses.
#
#   bash ~/fabrik/einrichtung/8-logbuecher-einrichten.sh
#
# Ergaenzt die Werkzeugliste jeder Rollendatei um Edit(notizen/<rolle>.md).
# Idempotent: mehrfaches Ausfuehren aendert nichts.

set -euo pipefail
cd "$HOME/fabrik"

python3 - <<'PY'
import re
from pathlib import Path

rollen = sorted(Path('agents/rollen').glob('*.md'))
geaendert = 0

for datei in rollen:
    name = datei.stem
    text = datei.read_text(encoding='utf-8')
    eintrag = f'  - "Edit(notizen/{name}.md)"'

    if eintrag in text:
        print(f"  {name:24} schon eingetragen")
        continue

    # Hinter die letzte Zeile der tools-Liste, also vor das schliessende ---
    kopf_ende = text.index('---', 3)
    kopf, rumpf = text[:kopf_ende], text[kopf_ende:]
    zeilen = kopf.rstrip('\n').split('\n')

    letzte_tool_zeile = max(
        i for i, z in enumerate(zeilen) if z.lstrip().startswith('- ')
    )
    zeilen.insert(letzte_tool_zeile + 1, eintrag)
    datei.write_text('\n'.join(zeilen) + '\n' + rumpf, encoding='utf-8')
    print(f"  {name:24} + Edit(notizen/{name}.md)")
    geaendert += 1

print(f"\n{geaendert} von {len(rollen)} Rollendateien ergaenzt.")
PY

echo
echo "Gegenprobe -- was jede Rolle jetzt committen darf:"
bash einrichtung/7-schreibpfade-pruefen.sh
