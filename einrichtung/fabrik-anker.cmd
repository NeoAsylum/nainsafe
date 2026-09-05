@echo off
REM ---------------------------------------------------------------------------
REM  Anker der Agentenfabrik -- Windows-Seite.
REM
REM  Warum es diese Datei gibt: Der stuendliche Tageslauf steht in der crontab
REM  INNERHALB von WSL. Faehrt die WSL-VM herunter -- durch Speicherdruck des
REM  Wirts, durch Leerlauf oder durch einen Neustart --, kann cron sich nicht
REM  selbst wecken. Am 2026-09-05 um etwa 20:20 ist genau das passiert: Die VM
REM  war weg, die Fabrik stand, und niemand merkte es, bis jemand nachsah.
REM
REM  Diese Aufgabe laeuft auf der Windows-Seite und ruft `wsl.exe`. Das startet
REM  die VM, falls sie aus ist. Die Sperre in ops/tageslauf.sperre verhindert,
REM  dass zwei Tageslaeufe nebeneinander laufen; ist das Budget erreicht oder
REM  das Sitzungsfenster zu, endet der Versuch nach null Durchgaengen.
REM ---------------------------------------------------------------------------

wsl.exe -d Ubuntu -- bash -lc "cd /home/adria/fabrik && /usr/bin/python3 -u agents/tageslauf.py >> ops/nachtlauf.log 2>&1"
