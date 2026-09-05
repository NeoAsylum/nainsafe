#!/bin/sh
# Haelt die WSL-VM wach, indem er nie endet.
#
# WSL2 faehrt die VM herunter, wenn sie leer laeuft. Solange die Fabrik arbeitet, ist
# sie das nie -- aber zwischen zwei Tageslaeufen, bei erreichtem Budget oder
# geschlossenem Sitzungsfenster stehen nur noch systemd und cron. Dieser Prozess ist die
# Zusicherung, dass immer etwas laeuft.
#
# Er kostet nichts: `sleep infinity` belegt keinen Rechenkern und wenige Kilobyte.
#
# Gestartet aus der crontab (@reboot), also nach jedem Start der VM neu. Wer nachsehen
# will, ob er lebt:  pgrep -af fabrik-anker
exec sleep infinity
