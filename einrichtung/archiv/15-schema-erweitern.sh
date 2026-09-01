#!/usr/bin/env bash
# Ergaenzt die neuen Token-Spalten in einer bestehenden state.db.
# Idempotent: vorhandene Spalten werden uebersprungen.

set -euo pipefail
cd "$HOME/fabrik"

for spalte in tokens_frisch tokens_cneu tokens_cles tokens_denken; do
  if sqlite3 state.db "PRAGMA table_info(lauf);" | grep -q "|$spalte|"; then
    echo "  $spalte schon vorhanden"
  else
    sqlite3 state.db "ALTER TABLE lauf ADD COLUMN $spalte INTEGER DEFAULT 0;"
    echo "  $spalte ergaenzt"
  fi
done

echo
echo "Spalten der Tabelle lauf:"
sqlite3 state.db "PRAGMA table_info(lauf);" | cut -d'|' -f2 | tr '\n' ' '
echo
echo
echo "Hinweis: Bestehende Laeufe haben in den neuen Spalten null -- die"
echo "Aufschluesselung beginnt mit dem naechsten Lauf."
