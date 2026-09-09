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
pruefe "nichts Uncommittetes liegen geblieben"     bash -c "cd '$ZIEL' && S=\$(cat ops/tageslauf.sperre 2>/dev/null) && kill -0 \"\$S\" 2>/dev/null && exit 0; test -z \"\$(git status --porcelain)\""

echo

echo

pruefe "Heisser Satz unter 40.000 Zeichen"        bash -c "test \$(cat '$ZIEL/CLAUDE.md' '$ZIEL/notizen/lehren.md' | wc -c) -lt 40000"
pruefe "Kein Logbuch ueber 12.000 Zeichen"        bash -c "! find '$ZIEL/notizen' -maxdepth 1 -name '*.md' -size +12k -not -name lehren.md | grep -q ."

echo "Zeitplanung"
pruefe "Tageslauf stuendlich in der crontab"       bash -c "crontab -l | grep -q '^0 \* \* \* \* .*tageslauf.py'"
pruefe "Takt entspricht einrichtung/crontab"     bash -c "diff <(crontab -l | grep -vE '^#|^$') <(grep -vE '^#|^$' '$ZIEL/einrichtung/crontab') > /dev/null"
pruefe "Wochenlauf in der crontab"                 bash -c "crontab -l | grep -q wochenlauf.py"
pruefe "PATH-Zeile in der crontab"                 bash -c "crontab -l | grep -q '^PATH='"

echo
echo "Sicherung"
pruefe "SSH-Schluessel wird von GitHub akzeptiert" bash -c "ssh -o BatchMode=yes -T git@github.com 2>&1 | grep -q 'successfully authenticated'"
# 404 = privat, 200 = oeffentlich, alles andere (000 Netzfehler, 403 Stundenlimit)
# = unbekannt. Die alte Fassung fragte auf != 200 und bestand damit bei jedem
# Netzfehler und jedem Rate-Limit. Am 2026-09-09 stand das Repo oeffentlich,
# waehrend die Pruefung tagelang gruen meldete. Unwissen ist hier kein Bestehen.
pruefe "Repo ist privat (404; 200 oder unklar = Alarm)" bash -c "test \"\$(curl -s -o /dev/null -w '%{http_code}' -m 10 https://api.github.com/repos/NeoAsylum/nainsafe)\" = '404'"
pruefe "Kein Hilfsskript committet heimlich"    bash -c "! grep -lE '^[^#]*git (add|commit)' '$ZIEL'/einrichtung/*.sh"
pruefe "Sicherungsskript in der crontab"           bash -c "crontab -l | grep -q sichern.sh"
pruefe "Sicherungsskript pusht wirklich"           bash -c "grep -q 'git push origin' '$ZIEL/einrichtung/sichern.sh'"
pruefe "Sicherung juenger als 26 Stunden"          bash -c "test -n \"\$(find /home/adria/sicherung -name 'fabrik-*.bundle' -mmin -1560 -print -quit)\""

echo
echo "Anmeldung"
pruefe "claude antwortet headless"                 bash -c "cd '$ZIEL' && claude -p 'Antworte nur mit: bereit' --output-format text | grep -qi bereit"

echo
echo "----------------------------------------"
if [ "$FEHLT" -eq 0 ]; then
  echo "Alle $OK Bedingungen erfuellt. Der naechste Versuch startet zur vollen Stunde."
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
