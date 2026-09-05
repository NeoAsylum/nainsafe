# Der Anker auf der Windows-Seite

`einrichtung/fabrik-anker.cmd` ist die **Kopie zur Aufbewahrung**. Wirksam ist die Datei
unter `C:\Users\adria\fabrik-anker.cmd`, aufgerufen von der Windows-Aufgabenplanung.

## Warum es ihn gibt

Der stündliche Tageslauf steht in der crontab **innerhalb** von WSL. Fährt die VM
herunter — durch Speicherdruck des Wirts, durch Leerlauf oder durch einen Neustart —,
kann cron sich nicht selbst wecken. Der Wecker steht im Schlafzimmer.

Am 2026-09-05 gegen 20:20 ist genau das passiert. Vorzeichen war ein
`Wsl/0x8007000e` („nicht genügend Speicherressourcen") bei einem Aufruf um 20:16, den
ich als harmlos abgetan habe — WSL selbst hatte 15 GB frei, der Druck lag auf der
Windows-Seite. Eine Stunde später war die VM weg, `uptime` meldete nach dem Wecken
**0 Minuten**, ein Projektmanager-Lauf hing seit 20:02 auf `laeuft`, und die Fabrik hatte
74 Minuten nichts getan.

## Was er tut

```
wsl.exe -d Ubuntu -- bash -lc "cd /home/adria/fabrik && python3 -u agents/tageslauf.py …"
```

`wsl.exe` startet die VM, falls sie aus ist. Alles Weitere übernehmen die vorhandenen
Bremsen: `ops/tageslauf.sperre` lässt nur einen Lauf zu, ein erreichtes Budget beendet
den Versuch nach null Durchgängen, und ein geschlossenes Sitzungsfenster ebenso.

**Damit gibt es den Takt zweimal** — in der crontab und in der Aufgabenplanung. Das ist
Absicht und keine Doppelung: Der eine läuft, solange die VM lebt, der andere weckt sie.
Beide prallen an derselben Sperre ab.

## Einrichten

```powershell
$aktion    = New-ScheduledTaskAction -Execute "C:\Users\adria\fabrik-anker.cmd"
$ausloeser = New-ScheduledTaskTrigger -Once -At (Get-Date).Date `
             -RepetitionInterval (New-TimeSpan -Hours 1)
$einst     = New-ScheduledTaskSettingsSet -AllowStartIfOnBatteries `
             -DontStopIfGoingOnBatteries -StartWhenAvailable `
             -ExecutionTimeLimit (New-TimeSpan -Hours 6) -MultipleInstances IgnoreNew
Register-ScheduledTask -TaskName "Agentenfabrik" -Action $aktion `
             -Trigger $ausloeser -Settings $einst
```

## Prüfen

```powershell
Get-ScheduledTaskInfo -TaskName "Agentenfabrik"   # LastTaskResult 0 = gelaufen
```

`einrichtung/pruefen.sh` kann das **nicht** mitprüfen: Es läuft in WSL, und `/mnt/c` ist
in dieser Distro abgeklemmt. Die Aufgabenplanung ist damit der einzige Teil des Takts,
den nur der Betreiber kontrollieren kann.

## Was er nicht kann

Er hält die VM nicht am Leben, er weckt sie nur stündlich. Zwischen zwei Weckrufen kann
bis zu eine Stunde Arbeit ausfallen. Wer das nicht will, muss den Energiesparmodus des
Wirts ändern — das ist eine Entscheidung des Betreibers, keine der Fabrik.
