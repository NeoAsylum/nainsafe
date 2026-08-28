#!/usr/bin/env bash
# Zeigt je Rolle, welche Pfade sie committen darf -- abgeleitet aus ihrer
# Werkzeugliste. Nach jeder Aenderung an einer Rollendatei kurz gegenlesen:
# Was hier nicht auftaucht, kann die Rolle auch nicht in die Historie bringen.

cd "$HOME/fabrik" || exit 1

python3 - <<'PY'
import sys
sys.path.insert(0, 'agents')
from pathlib import Path
from lauf import frontmatter, schreibpfade

print(f"{'Rolle':24} Darf committen")
print("-" * 60)
for f in sorted(Path('agents/rollen').glob('*.md')):
    kopf, _ = frontmatter(f.read_text(encoding='utf-8'))
    pfade = schreibpfade(kopf.get('tools', []))
    marke = ', '.join(pfade) if pfade else '(nichts -- Rolle kann nichts festhalten!)'
    print(f"{f.stem:24} {marke}")
PY
