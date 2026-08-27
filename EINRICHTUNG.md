# Einrichtung: die Fabrik in WSL2

Einmaliger Vorgang. Danach läuft die Fabrik in einem eigenen Linux-Dateisystem, von dem
aus die Windows-Platte nicht erreichbar ist — und zwar so, wie sie später auch auf einem
VPS laufen wird. Die Migration dorthin ist dann ein Kopiervorgang, keine Portierung.

Drei Skripte, drei Stellen, an denen ein Mensch gebraucht wird. Die Aufteilung folgt
genau diesen Stellen: Adminrechte, Benutzeranlage, Anmeldung.

| Skript | Wo | Was dich kostet |
|---|---|---|
| [1-wsl-installieren.ps1](einrichtung/1-wsl-installieren.ps1) | PowerShell als Admin | ein UAC-Klick |
| [2-fabrik-aufsetzen.sh](einrichtung/2-fabrik-aufsetzen.sh) | Ubuntu-Shell | Benutzername und Passwort |
| [3-abschotten.sh](einrichtung/3-abschotten.sh) | Ubuntu-Shell | vorher einmal im Browser anmelden |

**Die Reihenfolge ist nicht beliebig.** Skript 3 kappt den Zugriff auf die Windows-Platte;
alles, was von dort geholt werden muss, passiert vorher.

---

## Stand

Schritt 1 ist auf diesem Rechner **erledigt**: WSL-Kernel aktualisiert, Ubuntu
installiert (Version 2, gestoppt). Weiter bei Schritt 2.

## Schritt 2 — Benutzer anlegen, dann Skript

```powershell
wsl -d Ubuntu
```

Beim ersten Start fragt Ubuntu nach Benutzername und Passwort. Das Passwort brauchst du
für `sudo` — notiere es, es steht in keinem dieser Skripte. Danach, in der Ubuntu-Shell:

```sh
bash /mnt/c/Users/adria/OneDrive/Desktop/nainsafe/nainsafe/einrichtung/2-fabrik-aufsetzen.sh
```

Das Skript installiert `git`, `python3`, `sqlite3` und `bubblewrap`, holt Claude Code,
klont das Repo nach `~/fabrik` und macht einen Trockenlauf. `bubblewrap` ist die
Grundlage der Sandbox — ohne sie bleibt die Kernel-Isolation aus.

## Schritt 3 — Anmelden (das kann kein Skript)

```sh
cd ~/fabrik
claude
```

Beim ersten Start öffnet sich ein Browser-Login. Zeigt der Browser stattdessen einen
Code — in WSL2 der Normalfall, weil der lokale Rückkanal nicht erreichbar ist —, füge
ihn im Terminal ein. Melde dich mit dem Konto an, auf dem dein Max-Abo läuft.

Dann im laufenden Claude Code `/sandbox` aufrufen: Es müssen die Reiter **Mode**,
**Overrides** und **Config** erscheinen. Nur ein Reiter „Dependencies" heißt, dass
`bubblewrap` fehlt.

Danach Claude Code beenden und abschotten:

```sh
bash ~/fabrik/einrichtung/3-abschotten.sh
```

Das Skript prüft zuerst, ob die Anmeldung wirklich funktioniert — es setzt einen echten
Testaufruf ab, statt sich auf die Anwesenheit einer Datei zu verlassen. Erst danach
schreibt es `/etc/wsl.conf` und richtet die Zeitplanung ein.

Zum Schluss in PowerShell:

```powershell
wsl --shutdown
```

Beim nächsten Start existiert `/mnt/c` nicht mehr. Ein Agent kann die Windows-Platte
nicht lesen, nicht beschreiben und nicht einmal sehen — unabhängig davon, was in seinem
Prompt steht.

**Der Weg zurück bleibt offen:** Von Windows aus erreichst du die Fabrik weiterhin unter
`\\wsl$\Ubuntu\home\<dein-name>\fabrik`, auch im Explorer und in VS Code. Nur die
Richtung Linux → Windows ist gekappt, und nur die brauchen wir zu.

---

## Danach

Der erste echte Lauf verbraucht Tokens und dauert einige Minuten:

```sh
cd ~/fabrik && python3 agents/nachtlauf.py
git log --oneline -10
ls signals/regulation/ ideas/
```

Drei Dinge bleiben deine Sache:

- **Das Windows-Original in OneDrive** erst löschen, wenn die Fabrik in WSL nachweislich
  läuft. Bis dahin ist es dein Rückweg.
- **Prüfen, dass das GitHub-Remote privat ist**, bevor die Sicherung zum ersten Mal
  pusht. `grenzen.md` und die ADRs beschreiben deine Arbeitssituation samt
  Arbeitgeberbranche deutlich genug, dass sie niemanden außer dich etwas angehen.
## Zwei Fallen, die Autonomie lautlos verhindern

Beide sehen im Test wie Erfolg aus und führen dazu, dass nachts nichts passiert.

**1. Ohne systemd kein cron.** WSL startet standardmäßig kein systemd; PID 1 ist
`init(Ubuntu)`, und der cron-Daemon läuft schlicht nicht. Die crontab-Einträge stehen
dann korrekt in der Datei und werden nie ausgeführt. Deshalb steht in `/etc/wsl.conf`:

```ini
[boot]
systemd=true
```

Prüfen lässt es sich so — beide Zeilen müssen etwas melden:

```sh
pidof systemd && pgrep -x cron
```

**2. WSL beendet die Distro, sobald kein Prozess mehr läuft.** Ein Autostart, der nur
`wsl -d Ubuntu -- /bin/true` ausführt, startet sie und lässt sie Sekunden später wieder
herunterfahren — mit ihr systemd und cron. Es braucht einen Anker-Prozess. Im
Autostart-Ordner liegt dafür `agentenfabrik-wsl.vbs`:

```vbs
CreateObject("WScript.Shell").Run "wsl.exe -d Ubuntu -- sleep infinity", 0, False
```

Solange der schlafende Prozess läuft, bleibt die Distro oben. Zu finden unter
`%APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup` — dort auch wieder löschbar,
wenn die Fabrik einmal ruhen soll.

Beides greift bei **Anmeldung**, nicht beim Hochfahren: Meldest du dich ab, steht die
Fabrik. Für einen Rechner, an dem du täglich arbeitest, genügt das; wenn nicht, ist das
der Punkt, an dem sich der VPS lohnt.

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
tatsächlich `Bash` bekommt — die acht bestehenden Rollen haben es nicht. Wenn später der
Builder dazukommt, ist sie die Ebene, die zählt.
