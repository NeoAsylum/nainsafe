#!/usr/bin/env bash
# Testet, ob der naechtliche Push funktioniert -- unter genau den Bedingungen,
# unter denen cron ihn ausfuehrt: ohne Terminal, ohne Rueckfragen.
#
#   bash ~/fabrik/einrichtung/6-push-testen.sh

set -uo pipefail

ZIEL="$HOME/fabrik"
cd "$ZIEL"

echo "== Push testen =="

echo
echo "[1] Erreicht der Schluessel GitHub? ..."
AUSGABE="$(ssh -o BatchMode=yes -o StrictHostKeyChecking=yes -T git@github.com 2>&1 || true)"
echo "$AUSGABE" | sed 's/^/    /'

if echo "$AUSGABE" | grep -q "successfully authenticated"; then
  echo "    -> Schluessel akzeptiert."
elif echo "$AUSGABE" | grep -qi "permission denied"; then
  echo
  echo "    -> Der Schluessel ist bei GitHub noch nicht eingetragen."
  echo "       Oeffentlichen Teil erneut anzeigen:"
  echo "         cat ~/.ssh/fabrik_ed25519.pub"
  echo "       Eintragen unter https://github.com/NeoAsylum/nainsafe/settings/keys"
  exit 1
fi

echo
echo "[2] Push ..."
if GIT_SSH_COMMAND="ssh -o BatchMode=yes" git push origin main 2>&1 | sed 's/^/    /'; then
  echo
  echo "    Push erfolgreich. Die naechtliche Sicherung um 03:30 laeuft ab jetzt."
else
  echo
  echo "    Push fehlgeschlagen. Haeufigste Ursachen:"
  echo "      - Repository existiert nicht -> auf GitHub anlegen, PRIVAT"
  echo "      - Deploy Key ohne Schreibrecht -> 'Allow write access' ankreuzen"
  exit 1
fi

echo
echo "[3] Sichtbarkeit pruefen ..."
CODE="$(curl -s -o /dev/null -w '%{http_code}' -m 10 https://api.github.com/repos/NeoAsylum/nainsafe)"
if [ "$CODE" = "200" ]; then
  echo "    ACHTUNG: Das Repository ist OEFFENTLICH lesbar (HTTP 200)."
  echo "    grenzen.md und die ADRs beschreiben deine Arbeitssituation samt"
  echo "    Arbeitgeberbranche. Auf privat stellen:"
  echo "      https://github.com/NeoAsylum/nainsafe/settings -> Danger Zone"
  exit 1
else
  echo "    Nicht oeffentlich lesbar (HTTP $CODE) -- so soll es sein."
fi

echo
echo "== Fertig =="
