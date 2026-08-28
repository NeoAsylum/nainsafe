#!/usr/bin/env bash
# Zeigt, was Claude Code im JSON-Modus tatsaechlich an Verbrauchsdaten zurueckgibt.
# Grundlage dafuer, ob das Journal die richtigen Felder erfasst.

cd "$HOME/fabrik" || exit 1

# Denselben PATH wie die crontab -- ohne das fehlt claude in einer Nicht-Login-Shell.
export PATH="$HOME/.local/bin:/usr/local/bin:/usr/bin:/bin"

claude -p 'Antworte nur mit: ok' --output-format json --model sonnet > /tmp/usage.json

python3 - <<'PY'
import json

with open('/tmp/usage.json') as f:
    d = json.load(f)

print("--- Felder auf oberster Ebene ---")
for k, v in d.items():
    kurz = str(v)
    if len(kurz) > 60:
        kurz = kurz[:57] + "..."
    print(f"  {k:28} {kurz}")

print("\n--- usage im Detail ---")
print(json.dumps(d.get("usage", {}), indent=2))

u = d.get("usage", {})
ein = u.get("input_tokens", 0)
cache_neu = u.get("cache_creation_input_tokens", 0)
cache_gelesen = u.get("cache_read_input_tokens", 0)
aus = u.get("output_tokens", 0)

print("\n--- Was das Journal bisher zaehlt ---")
print(f"  input_tokens                 {ein:>10,}")
print(f"  output_tokens                {aus:>10,}")
print(f"  Summe im Journal             {ein + aus:>10,}")

print("\n--- Was tatsaechlich durch das Kontingent geht ---")
print(f"  input_tokens                 {ein:>10,}")
print(f"  cache_creation_input_tokens  {cache_neu:>10,}")
print(f"  cache_read_input_tokens      {cache_gelesen:>10,}")
print(f"  output_tokens                {aus:>10,}")
print(f"  Summe tatsaechlich           {ein + cache_neu + cache_gelesen + aus:>10,}")

faktor = (ein + cache_neu + cache_gelesen + aus) / max(ein + aus, 1)
print(f"\n  Das Journal untertreibt um Faktor {faktor:.1f}.")
PY
