#!/usr/bin/env bash
# Bereitet den Push per SSH vor. Erzeugt den Schluessel, hinterlegt den Hostkey
# von GitHub und stellt origin um. Uebrig bleibt genau ein Schritt fuer dich:
# den oeffentlichen Schluessel bei GitHub eintragen.
#
#   bash ~/fabrik/einrichtung/5-schluessel.sh

set -euo pipefail

ZIEL="$HOME/fabrik"
KEY="$HOME/.ssh/fabrik_ed25519"
SSH_URL="git@github.com:NeoAsylum/nainsafe.git"

echo "== Push per SSH vorbereiten =="

echo
echo "[1] Schluessel ..."
mkdir -p "$HOME/.ssh"
chmod 700 "$HOME/.ssh"
if [ -f "$KEY" ]; then
  echo "    vorhanden: $KEY"
else
  # Ohne Passphrase: Ein Cron-Job kann keine eingeben. Der Schluessel liegt dafuer
  # nur in dieser Distro und ist als Deploy Key auf ein einziges Repo begrenzt.
  ssh-keygen -t ed25519 -f "$KEY" -N "" -C "agentenfabrik-wsl" >/dev/null
  echo "    erzeugt: $KEY"
fi

echo
echo "[2] Hostkey von GitHub hinterlegen ..."
# Ohne diesen Schritt fragt ssh beim ersten Verbinden nach Bestaetigung -- und ein
# Cron-Job, den niemand bestaetigt, haengt bis zum naechsten Neustart.
ssh-keyscan -t ed25519 github.com 2>/dev/null >> "$HOME/.ssh/known_hosts"
sort -u -o "$HOME/.ssh/known_hosts" "$HOME/.ssh/known_hosts"
echo "    github.com in known_hosts"

echo
echo "[3] ssh-Konfiguration ..."
if ! grep -qs 'Host github.com' "$HOME/.ssh/config" 2>/dev/null; then
  cat >> "$HOME/.ssh/config" <<CONF
Host github.com
    User git
    IdentityFile $KEY
    IdentitiesOnly yes
CONF
  chmod 600 "$HOME/.ssh/config"
  echo "    ~/.ssh/config ergaenzt"
else
  echo "    bereits konfiguriert"
fi

echo
echo "[4] origin auf SSH umstellen ..."
cd "$ZIEL"
git remote set-url origin "$SSH_URL"
git remote get-url origin | sed 's/^/    /'

echo
echo "[5] crontab auf SSH anpassen ..."
TMP="$(mktemp)"
crontab -l 2>/dev/null | grep -v 'git push origin' > "$TMP" || true
echo '30 3 * * * cd /home/adria/fabrik && GIT_SSH_COMMAND="ssh -o BatchMode=yes" git push origin main >> ops/backup.log 2>&1' >> "$TMP"
crontab "$TMP"
rm -f "$TMP"
echo "    BatchMode=yes -- scheitert sofort statt zu warten, falls etwas fehlt"

cat <<ENDE

========================================================================
 Ein Schritt bleibt fuer dich. Diesen Text vollstaendig kopieren:
========================================================================

ENDE
cat "$KEY.pub"
cat <<'ENDE'

========================================================================

 Einfuegen unter:
   https://github.com/NeoAsylum/nainsafe/settings/keys
   -> "Add deploy key"
   -> Title: Agentenfabrik WSL
   -> Key: den Text von oben
   -> [x] Allow write access      <- wichtig, sonst kann er nicht pushen
   -> "Add key"

 Ein Deploy Key gilt nur fuer dieses eine Repository. Faellt die Distro
 jemals in fremde Haende, ist nicht dein GitHub-Konto betroffen, sondern
 nur dieses Repo -- deshalb Deploy Key statt Konto-Schluessel.

 Falls das Repository NeoAsylum/nainsafe noch gar nicht existiert: erst
 anlegen, als PRIVAT. grenzen.md und die ADRs beschreiben deine
 Arbeitssituation samt Arbeitgeberbranche.

 Danach testen mit:
   bash ~/fabrik/einrichtung/6-push-testen.sh

ENDE
