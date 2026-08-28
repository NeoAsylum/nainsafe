#!/usr/bin/env bash
# Committet den Recherche-Fix und laesst den Ideator auf das Marktprofil los.
set -euo pipefail
cd "$HOME/fabrik"
export PATH="$HOME/.local/bin:/usr/local/bin:/usr/bin:/bin"

git add -A
git commit -q -F - <<'ENDE'
Marktprofile nicht nochmal recherchieren

Der Markt-Analyst beantwortet dieselben Fragen wie der Rechercheur, nur
systematisch statt anlassbezogen: Segmentgroesse, Zahlungsbereitschaft,
bestehende Anbieter, Kanal -- jeweils mit Quelle. Ein Rechercheur-Lauf
darauf waere rund fuenf Dollar Gegenwert fuer eine zweite Fassung derselben
Arbeit.

signals/maerkte/ ist deshalb von offene_recherchen ausgenommen. Die Profile
gehen direkt an den Ideator.
ENDE

GIT_SSH_COMMAND="ssh -o BatchMode=yes" git push -q origin main
echo "committet."

echo
echo "=== Ideator auf das Marktprofil ==="
python3 agents/lauf.py ideator

echo
echo "=== Neue Ideen ==="
grep -l "signals/maerkte" ideas/*.md 2>/dev/null | while read -r f; do
  printf '%-46s ' "$(basename "$f" .md)"
  grep -m1 '^titel:' "$f" | sed 's/titel: //'
done
