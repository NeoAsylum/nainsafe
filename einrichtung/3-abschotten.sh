#!/usr/bin/env bash
# Schritt 3 von 3 -- Windows-Platte abklemmen, Zeitplanung einrichten.
#
#   bash ~/fabrik/einrichtung/3-abschotten.sh
#
# ERST ausfuehren, wenn Schritt 2 durch ist UND `claude` angemeldet ist.
# Danach existiert /mnt/c nicht mehr -- was von dort geholt werden muss, muss vorher da sein.

set -euo pipefail

ZIEL="$HOME/fabrik"

echo "== 3/3  Abschotten =="

if [ ! -d "$ZIEL/.git" ]; then
  echo "FEHLER: $ZIEL fehlt. Erst Schritt 2 ausfuehren." >&2
  exit 1
fi

if ! command -v claude >/dev/null 2>&1; then
  echo "FEHLER: claude nicht im PATH." >&2
  echo "Erst Schritt 2 abschliessen und anmelden." >&2
  exit 1
fi

echo
echo "[1] Anmeldung pruefen ..."
if claude -p "Antworte nur mit: bereit" --output-format text >/tmp/claude-probe 2>&1; then
  echo "    $(head -c 80 /tmp/claude-probe)"
else
  echo "    FEHLER: claude antwortet nicht. Bist du angemeldet?" >&2
  echo "    Fuehre 'claude' aus und melde dich an, dann dieses Skript erneut." >&2
  head -3 /tmp/claude-probe >&2
  exit 1
fi

echo
echo "[2] Windows-Platte abklemmen ..."
sudo tee /etc/wsl.conf > /dev/null <<'EOF'
[automount]
enabled = false

[interop]
appendWindowsPath = false
EOF
echo "    /etc/wsl.conf geschrieben. Wirksam nach 'wsl --shutdown' in PowerShell."

echo
echo "[3] Zeitplanung ..."
PY="$(command -v python3)"
NACHT="0 3 * * * cd $ZIEL && $PY agents/nachtlauf.py >> ops/nachtlauf.log 2>&1"
WOCHE="0 7 * * 0 cd $ZIEL && $PY agents/wochenlauf.py >> ops/wochenlauf.log 2>&1"
SICHER="30 3 * * * cd $ZIEL && git push origin main >> ops/backup.log 2>&1"

TMP="$(mktemp)"
crontab -l 2>/dev/null | grep -v "agents/nachtlauf.py\|agents/wochenlauf.py\|git push origin main" > "$TMP" || true
{ echo "$NACHT"; echo "$WOCHE"; echo "$SICHER"; } >> "$TMP"
crontab "$TMP"
rm -f "$TMP"
echo "    Nachtlauf  03:00 taeglich"
echo "    Wochenlauf 07:00 sonntags"
echo "    Sicherung  03:30 taeglich (git push, nur wenn ein privates Remote gesetzt ist)"

cat <<ENDE

== Fertig ==

Jetzt in PowerShell einmal:

    wsl --shutdown

Danach ist /mnt/c weg und die Fabrik sieht nur noch sich selbst.
Von Windows aus erreichst du sie weiterhin unter:

    \\\\wsl\$\\Ubuntu\\home\\$USER\\fabrik

Der erste echte Lauf -- verbraucht Tokens, dauert einige Minuten:

    cd ~/fabrik && python3 agents/nachtlauf.py

Danach nachsehen, was dabei herauskam:

    git log --oneline -10
    ls signals/regulation/ ideas/

Noch offen, weil es dich betrifft:
  - Windows-Original in OneDrive erst loeschen, wenn die Fabrik hier laeuft.
  - Pruefen, dass das GitHub-Remote privat ist, bevor die Sicherung zum ersten Mal pusht.
  - WSL startet nicht mit Windows. Damit der Nachtlauf ohne offenes Terminal laeuft,
    im Aufgabenplaner eine Aufgabe bei Anmeldung anlegen:  wsl -d Ubuntu -- /bin/true

ENDE
