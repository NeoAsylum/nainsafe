#!/usr/bin/env bash
# Zeigt alle gescheiterten Laeufe mit Begruendung.
cd "$HOME/fabrik" || exit 1
sqlite3 -line state.db "SELECT id, rolle, gegenstand, substr(notiz,1,400) AS notiz
                        FROM lauf WHERE ergebnis IN ('fehler','abgebrochen');"
