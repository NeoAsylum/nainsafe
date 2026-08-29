#!/usr/bin/env bash
cd "$HOME/fabrik" || exit 1
echo "=== Notiz des letzten Ideator-Laufs ==="
sqlite3 state.db "SELECT substr(notiz,1,1400) FROM lauf WHERE rolle='ideator' ORDER BY id DESC LIMIT 1;"
echo
echo "=== Logbuch des Ideators (letzte Eintraege) ==="
tail -20 notizen/ideator.md 2>/dev/null || echo "(kein Logbuch)"
