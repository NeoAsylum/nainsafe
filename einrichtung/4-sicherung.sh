#!/usr/bin/env bash
# Sicherung einrichten: origin auf GitHub, Push cron-sicher, lokales Bundle als Netz.
#
#   bash ~/fabrik/einrichtung/4-sicherung.sh
#
# Der Klon kam ueber /mnt/c, sein origin zeigt also auf einen Pfad, den es in der
# abgeschotteten Distro nicht mehr gibt. Ohne diese Korrektur scheitert der
# naechtliche Push jede Nacht.

set -euo pipefail

ZIEL="$HOME/fabrik"
REMOTE="https://github.com/NeoAsylum/nainsafe.git"

cd "$ZIEL"

echo "== Sicherung einrichten =="

echo
echo "[1] origin korrigieren ..."
git remote set-url origin "$REMOTE"
git remote -v | sed 's/^/    /'

echo
echo "[2] Ablage fuer lokale Buendel ..."
mkdir -p "$HOME/sicherung"
echo "    $HOME/sicherung"

echo
echo "[3] crontab neu schreiben ..."
TMP="$(mktemp)"
crontab -l 2>/dev/null | grep -v 'git push origin\|git bundle create' > "$TMP" || true

# GIT_TERMINAL_PROMPT=0 ist hier keine Feinheit, sondern Pflicht: Ohne hinterlegte
# Zugangsdaten wuerde git nach einem Passwort fragen und der Cron-Job haengt bis zum
# naechsten Neustart. Mit der Variablen bricht er sofort ab und schreibt es ins Log.
cat >> "$TMP" <<'CRON'
30 3 * * * cd /home/adria/fabrik && GIT_TERMINAL_PROMPT=0 git push origin main >> ops/backup.log 2>&1
45 3 * * * cd /home/adria/fabrik && git bundle create /home/adria/sicherung/fabrik-$(date +\%Y-\%m-\%d).bundle --all >> ops/backup.log 2>&1
CRON

crontab "$TMP"
rm -f "$TMP"
crontab -l | sed 's/^/    /'

echo
echo "[4] Push testen ..."
if GIT_TERMINAL_PROMPT=0 git push origin main 2>&1 | tail -3 | sed 's/^/    /'; then
  echo "    Push hat funktioniert -- GitHub ist als Sicherung aktiv."
else
  cat <<'HINWEIS'

    Push nicht moeglich -- es fehlen Zugangsdaten. Das lokale Buendel laeuft
    trotzdem und schuetzt vor Repo-Schaeden, aber nicht vor dem Verlust der
    ganzen Distribution.

    Einmalig einrichten, dann laeuft der naechtliche Push von selbst:

      1. Auf github.com ein Token erzeugen (Settings -> Developer settings ->
         Personal access tokens -> Fine-grained, Zugriff nur auf nainsafe,
         Recht "Contents: Read and write").
      2. In der Distro:
           git config --global credential.helper store
           cd ~/fabrik && git push origin main
         Beim Passwort das Token einfuegen. Es wird in ~/.git-credentials
         abgelegt und danach nicht mehr abgefragt.

    Vorher pruefen, dass das Repo auf GitHub PRIVAT ist: grenzen.md und die
    ADRs beschreiben deine Arbeitssituation samt Arbeitgeberbranche.

HINWEIS
fi

echo
echo "== Fertig =="
