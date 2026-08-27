# Einrichtung: die Fabrik in WSL2

Einmaliger Vorgang. Danach läuft die Fabrik in einem eigenen Linux-Dateisystem, von dem
aus die Windows-Platte nicht erreichbar ist — und zwar so, wie sie später auch auf einem
VPS laufen wird. Die Migration dorthin ist dann ein Kopiervorgang, keine Portierung.

**Die Reihenfolge ist wichtig.** Schritt 5 kappt den Zugriff auf die Windows-Platte;
alles, was von dort geholt werden muss, passiert vorher.

---

## 1 — WSL2 nachrüsten (Windows, als Administrator)

Auf diesem Rechner ist WSL in Version 2 vorgesehen, aber der Kernel fehlt und es ist
keine Distribution installiert.

```powershell
wsl --update
wsl --install -d Ubuntu
```

Der zweite Befehl startet Ubuntu und fragt nach Benutzername und Passwort. Dieses
Passwort brauchst du für `sudo` — notieren.

## 2 — Werkzeuge in Ubuntu (in der WSL-Shell)

```sh
sudo apt update
sudo apt install -y git python3 sqlite3 curl bubblewrap
curl -fsSL https://claude.ai/install.sh | bash
```

`bubblewrap` ist die Grundlage der Sandbox unter Linux. Fehlt sie, zeigt `/sandbox`
später nur einen Reiter „Dependencies" statt der Konfiguration.

## 3 — Claude Code anmelden

```sh
claude
```

Beim ersten Start öffnet sich ein Browser-Login. Falls WSL den lokalen Rückkanal nicht
erreicht — in WSL2 häufig —, zeigt der Browser stattdessen einen Code, den du im
Terminal einfügst. Melde dich mit dem Konto an, auf dem dein Max-Abo läuft.

Danach `/sandbox` aufrufen und prüfen, dass die Reiter **Mode**, **Overrides** und
**Config** erscheinen. Nur ein Reiter „Dependencies" heißt: `bubblewrap` fehlt noch.

## 4 — Repo holen, solange die Windows-Platte noch sichtbar ist

```sh
git clone /mnt/c/Users/adria/OneDrive/Desktop/nainsafe/nainsafe ~/fabrik
cd ~/fabrik
git log --oneline | head -5      # Historie muss vollständig sein
python3 agents/nachtlauf.py --trocken
```

Der Klon nimmt die vollständige Git-Historie mit. Das Windows-Original bleibt vorerst
liegen — lösche es erst, wenn die Fabrik in WSL nachweislich läuft.

## 5 — Die Windows-Platte abklemmen

```sh
sudo tee /etc/wsl.conf > /dev/null <<'EOF'
[automount]
enabled = false

[interop]
appendWindowsPath = false
EOF
```

Dann in PowerShell:

```powershell
wsl --shutdown
```

Beim nächsten Start existiert `/mnt/c` nicht mehr. Ein Agent kann die Windows-Platte
nicht lesen, nicht beschreiben und nicht einmal sehen — unabhängig davon, was in seinem
Prompt steht.

**Der Weg zurück bleibt offen:** Von Windows aus erreichst du die Fabrik weiterhin unter
`\\wsl$\Ubuntu\home\<dein-name>\fabrik`, auch im Explorer und in VS Code. Nur die
Richtung Linux → Windows ist gekappt, und nur die brauchen wir zu.

## 6 — Nachtlauf einrichten

```sh
crontab -e
```

Eintragen:

```cron
0 3 * * * cd ~/fabrik && /usr/bin/python3 agents/nachtlauf.py >> ops/nachtlauf.log 2>&1
```

WSL2 startet nicht von selbst mit Windows. Damit der Nachtlauf ohne offenes Terminal
läuft, einmalig eine Aufgabe im Windows-Aufgabenplaner anlegen, die bei der Anmeldung
`wsl -d Ubuntu -- /bin/true` ausführt — das startet die Distribution im Hintergrund.
Alternativ läuft die Fabrik nur, wenn du WSL ohnehin offen hast; für den Anfang genügt das.

## 7 — Sicherung

Mit dem Umzug aus OneDrive entfällt die bisherige Sicherung. Das private GitHub-Repo
übernimmt:

```sh
git push -u origin main
```

Agenten dürfen nicht pushen — `Bash(git push:*)` steht in den globalen Verboten. Der
Push ist deine Sache, oder ein eigener Cron-Eintrag außerhalb der Agentenkette:

```cron
30 3 * * * cd ~/fabrik && git push origin main >> ops/backup.log 2>&1
```

Prüfe vorher, dass das GitHub-Repo **privat** ist. `grenzen.md` und die ADRs beschreiben
deine Arbeitssituation samt Arbeitgeberbranche deutlich genug, dass sie niemanden außer
dich etwas angehen.

---

## Was danach wie geschützt ist

| Ebene | Wogegen | Durchgesetzt von |
|---|---|---|
| Werkzeugliste je Rolle | Regel-Scout schreibt Ideen | Claude Code |
| 21 globale Verbote | Push, Netzwerk, Selbstmodifikation der Regeln | Claude Code |
| 18 deny-Regeln | Lesen von Schlüsseln, Browserprofilen, `.env` | Claude Code |
| Sandbox `denyRead: ~/` | Bash-Befehle sehen nur das Projekt | Linux-Kernel |
| `automount = false` | Zugriff auf die Windows-Platte | WSL2 |
| WSL2-Dateisystem | alles übrige auf dem Rechner | Virtualisierung |

Die oberen drei Ebenen greifen sofort. Die Sandbox greift erst, sobald eine Rolle
tatsächlich `Bash` bekommt — die drei bestehenden Rollen haben es nicht. Wenn später
der Builder dazukommt, ist sie die Ebene, die zählt.
