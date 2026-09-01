#!/usr/bin/env bash
# Committet Dashboard und Token-Aufschluesselung, haengt die Erzeugung an die Laeufe.
set -euo pipefail
cd "$HOME/fabrik"
export PATH="$HOME/.local/bin:/usr/local/bin:/usr/bin:/bin"

# Dashboard nach jedem Lauf neu erzeugen -- kostet nichts und ist dann immer aktuell.
PY_BIN="$(command -v python3)"
TMP="$(mktemp)"
crontab -l 2>/dev/null | grep -v 'dashboard.py' > "$TMP" || true
echo "*/30 * * * * cd $HOME/fabrik && $PY_BIN agents/dashboard.py > /dev/null 2>&1" >> "$TMP"
crontab "$TMP"
rm -f "$TMP"

git add -A
git commit -q -F - <<'ENDE'
Dashboard und Token-Aufschluesselung

Gerechnet wird jetzt in Tokens, nicht in Gegenwert. Dafuer musste das Journal
erst genauer werden: Es speicherte nur eine Eingangssumme, und die taeuscht in
beide Richtungen -- ein Lauf mit sieben Millionen Tokens kann leichter sein als
einer mit 39.000, weil Cache-Lesen anders zaehlt als frisch gesendeter Kontext.
Vier Spalten dazu: frisch, Cache-Erzeugung, Cache-Lesen, Denkanteil. Bestehende
Laeufe haben sie nicht; die Aufschluesselung beginnt mit dem naechsten.

ops/dashboard.html zeigt alles auf einer Seite: Kennzahlen, Tagesbremse,
Tokenarten, Verlauf je Tag, den Trichter von Signal bis Gate-Vorlage, Verbrauch
und Leerlaufquote je Rolle, Todesursachen nach Grenze und Linse, offene und
zuletzt verworfene Ideen, die letzten Laeufe, Logbuchgroessen und die Grundlast.

Die Seite ist eigenstaendig: kein Netz, keine Bibliotheken, alle Diagramme als
SVG im Dokument, hell und dunkel. Sie liest nichts aus dem Netz und schickt
nichts dorthin -- das Journal enthaelt den Stand der Firma.

Ein Cron-Eintrag erzeugt sie alle 30 Minuten neu.
ENDE

GIT_SSH_COMMAND="ssh -o BatchMode=yes" git push -q origin main
echo "committet:"
git log --oneline -1
echo
echo "Dashboard oeffnen unter:"
echo "  \\\\wsl\$\\Ubuntu\\home\\$USER\\fabrik\\ops\\dashboard.html"
