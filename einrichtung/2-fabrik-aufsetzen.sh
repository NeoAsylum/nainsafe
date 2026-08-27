#!/usr/bin/env bash
# Schritt 2 von 3 -- Werkzeuge, Claude Code und das Repo. In der Ubuntu-Shell:
#
#   bash /mnt/c/Users/adria/OneDrive/Desktop/nainsafe/nainsafe/einrichtung/2-fabrik-aufsetzen.sh
#
# Laeuft, solange /mnt/c noch eingehaengt ist -- abgeklemmt wird erst in Schritt 3.

set -euo pipefail

QUELLE="/mnt/c/Users/adria/OneDrive/Desktop/nainsafe/nainsafe"
ZIEL="$HOME/fabrik"

echo "== 2/3  Fabrik aufsetzen =="

if [ ! -d "$QUELLE/.git" ]; then
  echo "FEHLER: $QUELLE ist kein Git-Repo." >&2
  echo "Ist /mnt/c eingehaengt? Pruefe mit: ls /mnt/c" >&2
  exit 1
fi

echo
echo "[1] Systempakete ..."
sudo apt-get update -qq
sudo apt-get install -y -qq git python3 sqlite3 curl ca-certificates bubblewrap
echo "    git, python3, sqlite3, bubblewrap installiert."
echo "    (bubblewrap ist die Grundlage der Sandbox -- ohne sie keine Kernel-Isolation.)"

echo
echo "[2] Claude Code ..."
if command -v claude >/dev/null 2>&1; then
  echo "    bereits vorhanden: $(command -v claude)"
else
  curl -fsSL https://claude.ai/install.sh | bash
  export PATH="$HOME/.local/bin:$PATH"
  command -v claude >/dev/null 2>&1 || {
    echo "    Installiert, aber nicht im PATH dieser Shell." >&2
    echo "    Shell neu oeffnen oder: export PATH=\"\$HOME/.local/bin:\$PATH\"" >&2
  }
fi

echo
echo "[3] Repo klonen ..."
if [ -d "$ZIEL/.git" ]; then
  echo "    $ZIEL existiert bereits -- Klonen uebersprungen."
else
  # Das Windows-Original gehoert einem anderen Benutzer; ohne diese Ausnahme
  # verweigert git die Arbeit daran.
  git config --global --add safe.directory "$QUELLE" 2>/dev/null || true
  git clone "$QUELLE" "$ZIEL"
fi

cd "$ZIEL"
echo "    Historie:"
git log --oneline | head -5 | sed 's/^/      /'

echo
echo "[4] Trockenlauf ..."
python3 agents/nachtlauf.py --trocken | sed 's/^/    /'

cat <<'ENDE'

== Fertig. Ein Schritt bleibt, und den kann nur ein Mensch tun ==

Claude Code muss sich mit DEINEM Konto anmelden -- das laeuft ueber den Browser
und ist der einzige Teil, den kein Skript uebernehmen kann:

    cd ~/fabrik
    claude

Beim ersten Start oeffnet sich ein Browser-Login. Zeigt der Browser stattdessen
einen Code -- in WSL2 der Normalfall --, fuege ihn im Terminal ein.
Melde dich mit dem Konto an, auf dem dein Max-Abo laeuft.

Danach im laufenden Claude Code pruefen:

    /sandbox      Es muessen die Reiter Mode, Overrides und Config erscheinen.
                  Nur "Dependencies" heisst: bubblewrap fehlt noch.

Dann Claude Code beenden und Schritt 3 starten:

    bash ~/fabrik/einrichtung/3-abschotten.sh

ENDE
