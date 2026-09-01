#!/usr/bin/env bash
# Gibt allen Rollen Websuche.
#
#   bash ~/fabrik/einrichtung/13-websuche-ergaenzen.sh
#
# Anlass: Der Ideator hatte drei Anwaltsvorschlaege vorliegen und nur einen
# aufgegriffen. Nicht aus Nachlaessigkeit -- er hatte je Vorschlag eine toedliche
# Frage notiert und wollte sie klaeren, bevor er schreibt. Klaeren konnte er sie
# nicht: keine Websuche in seiner Werkzeugliste.
#
# Das galt fuer mehrere Rollen. Jede kann auf eine Frage stossen, an der ihre
# Arbeit haengen bleibt; keine sollte deshalb raten muessen. Wofuer die Suche
# gedacht ist und wofuer nicht, steht in CLAUDE.md -- eine fehlende Faehigkeit ist
# die falsche Art, Rollengrenzen durchzusetzen.
#
# Idempotent.

set -euo pipefail
cd "$HOME/fabrik"

python3 - <<'PY'
from pathlib import Path

WERKZEUGE = ["WebSearch", "WebFetch"]

for datei in sorted(Path("agents/rollen").glob("*.md")):
    text = datei.read_text(encoding="utf-8")
    kopf_ende = text.index("---", 3)
    kopf, rumpf = text[:kopf_ende], text[kopf_ende:]
    zeilen = kopf.rstrip("\n").split("\n")

    neu = [w for w in WERKZEUGE if f"  - {w}" not in kopf]
    if not neu:
        print(f"  {datei.stem:22} schon vorhanden")
        continue

    # Vor die erste Edit-Zeile, damit Lesewerkzeuge oben stehen.
    ziel = next((i for i, z in enumerate(zeilen) if z.strip().startswith('- "Edit(')),
                len(zeilen))
    for w in reversed(neu):
        zeilen.insert(ziel, f"  - {w}")
    datei.write_text("\n".join(zeilen) + "\n" + rumpf, encoding="utf-8")
    print(f"  {datei.stem:22} + {', '.join(neu)}")
PY

echo
echo "Gegenprobe -- Rollen ohne Websuche:"
fehlend=0
for f in agents/rollen/*.md; do
  grep -q '^  - WebSearch' "$f" || { echo "  $(basename "$f" .md)"; fehlend=1; }
done
[ "$fehlend" -eq 0 ] && echo "  keine"
