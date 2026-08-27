#!/usr/bin/env bash
# Prueft, ob die Fabrik unbeaufsichtigt laufen kann.
#
#   bash ~/fabrik/einrichtung/pruefen.sh
#
# Jede Zeile ist eine Bedingung, deren Ausfall dazu fuehrt, dass nachts nichts
# passiert -- meistens lautlos. Nach jedem Eingriff ins System hier gegenpruefen.

ZIEL="$HOME/fabrik"
OK=0
FEHLT=0

# Denselben PATH herstellen, den die crontab setzt. Ohne das prueft dieses Skript
# die interaktive Shell statt der Umgebung, in der die Fabrik tatsaechlich laeuft --
# und meldet ein "claude fehlt", das es um 03:00 gar nicht gibt.
export PATH="$HOME/.local/bin:/usr/local/bin:/usr/bin:/bin"

pruefe() {
  local name="$1"; shift
  if "$@" >/dev/null 2>&1; then
    printf '  \033[32mOK\033[0m    %s\n' "$name"
    OK=$((OK + 1))
  else
    printf '  \033[31mFEHLT\033[0m %s\n' "$name"
    FEHLT=$((FEHLT + 1))
  fi
}

echo "== Kann die Fabrik ohne dich laufen? =="
echo

echo "Umgebung"
pruefe "systemd laeuft (sonst kein cron)"          pidof systemd
pruefe "cron-Daemon laeuft"                        pgrep -x cron
pruefe "Anker haelt die Distro offen"              pgrep -f 'sleep infinity'
pruefe "claude auffindbar"                         command -v claude

echo
echo "Abschottung"
pruefe "/mnt/c ist NICHT eingehaengt"              bash -c '! mountpoint -q /mnt/c'
pruefe "kein Windows-Interop"                      bash -c '! command -v powershell.exe'

echo
echo "Repo"
pruefe "Repo vorhanden"                            test -d "$ZIEL/.git"
pruefe "git-Identitaet gesetzt"                    bash -c "cd '$ZIEL' && test -n \"\$(git config user.email)\""
pruefe "origin zeigt nicht mehr auf /mnt/c"        bash -c "cd '$ZIEL' && ! git remote get-url origin | grep -q '^/mnt/'"
pruefe "nichts Uncommittetes liegen geblieben"     bash -c "cd '$ZIEL' && test -z \"\$(git status --porcelain)\""

echo
echo "Zeitplanung"
pruefe "Nachtlauf in der crontab"                  bash -c "crontab -l | grep -q nachtlauf.py"
pruefe "Wochenlauf in der crontab"                 bash -c "crontab -l | grep -q wochenlauf.py"
pruefe "PATH-Zeile in der crontab"                 bash -c "crontab -l | grep -q '^PATH='"

echo
echo "Sicherung"
pruefe "SSH-Schluessel wird von GitHub akzeptiert" bash -c "ssh -o BatchMode=yes -T git@github.com 2>&1 | grep -q 'successfully authenticated'"
pruefe "Repo ist NICHT oeffentlich lesbar"         bash -c "test \"\$(curl -s -o /dev/null -w '%{http_code}' -m 10 https://api.github.com/repos/NeoAsylum/nainsafe)\" != '200'"
pruefe "Push-Eintrag in der crontab"               bash -c "crontab -l | grep -q 'git push origin'"

echo
echo "Anmeldung"
pruefe "claude antwortet headless"                 bash -c "cd '$ZIEL' && claude -p 'Antworte nur mit: bereit' --output-format text | grep -qi bereit"

echo
echo "----------------------------------------"
if [ "$FEHLT" -eq 0 ]; then
  echo "Alle $OK Bedingungen erfuellt. Der naechste Lauf startet um 03:00."
else
  echo "$OK erfuellt, $FEHLT offen. Solange etwas offen ist, laeuft nachts"
  echo "moeglicherweise nichts -- und zwar ohne Fehlermeldung."
fi

echo
echo "Letzte Laeufe:"
sqlite3 -column "$ZIEL/state.db" \
  'SELECT gestartet, rolle, ergebnis, tokens_in+tokens_out FROM lauf ORDER BY id DESC LIMIT 5;' \
  2>/dev/null | sed 's/^/  /' || echo "  (kein Journal)"

exit "$FEHLT"
