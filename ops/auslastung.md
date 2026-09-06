# Auslastung

Zeitraum: letzte 7 Tage. Erzeugt 2026-09-06T05:00:01 von `agents/auslastung.py`.

Die Fabrik laeuft ueber das Abo — ihre Laeufe kosten kein Geld, aber
Kontingent. Diese Seite misst deshalb Tokens und Ergiebigkeit.

| Rolle | Laeufe | ergiebig | leer | Fehler | Tokens |
|---|---:|---:|---:|---:|---:|
| testentwickler | 284 | 50 | 0 | 234 | 673.558.072 |
| kern-pruefer | 64 | 58 | 0 | 6 | 662.482.454 |
| kernbauer | 415 | 64 | 2 | 349 | 598.608.230 |
| projektmanager | 163 | 40 | 3 | 120 | 411.691.796 |
| test-pruefer | 158 | 40 | 0 | 118 | 362.101.317 |
| datenbauer | 166 | 47 | 1 | 118 | 324.162.260 |
| daten-pruefer | 51 | 49 | 0 | 2 | 307.616.937 |
| architekt | 137 | 19 | 2 | 116 | 139.681.686 |
| entwurf-pruefer | 18 | 16 | 0 | 2 | 88.852.672 |
| spielentwerfer | 10 | 8 | 1 | 0 | 77.484.190 |
| bruchtester | 4 | 4 | 0 | 0 | 62.542.774 |
| markt-analyst | 9 | 9 | 0 | 0 | 57.783.092 |
| geschaeftsfuehrer | 17 | 12 | 2 | 3 | 35.984.180 |
| prozess-analyst | 8 | 8 | 0 | 0 | 33.053.333 |
| modell-scout | 3 | 3 | 0 | 0 | 6.349.119 |
| portfolio-manager | 1 | 1 | 0 | 0 | 4.624.372 |
| regel-scout | 3 | 3 | 0 | 0 | 4.078.422 |
| pain-scout | 3 | 3 | 0 | 0 | 4.020.988 |
| rechercheur | 4 | 4 | 0 | 0 | 3.338.649 |
| markt-scout | 3 | 3 | 0 | 0 | 2.972.492 |
| ideator | 2 | 2 | 0 | 0 | 2.812.353 |
| verbesserer | 1 | 1 | 0 | 0 | 2.628.359 |
| fit-filter | 3 | 3 | 0 | 0 | 1.944.865 |
| tech-scout | 3 | 3 | 0 | 0 | 1.918.353 |
| digest-redakteur | 1 | 1 | 0 | 0 | 542.450 |

**Gesamt:** 1531 Laeufe, 3.870.833.415 Tokens.

**Gegenwert:** 3408.05 $ zu Listenpreisen — hochgerechnet rund 14606 $ im Monat. Abgerechnet wird davon nichts, die Laeufe gehen ueber das Abo. Die Zahl sagt, was die Fabrik daraus zieht.

## Kontingent

Im laufenden 5-Stunden-Fenster: 44 Laeufe, 388.961.001 Tokens.
Schwerster Tag im Zeitraum: 2026-09-05 mit 1.547.102.809 Tokens.

Reisst ein Lauf das Fenster- oder Wochenkontingent, bricht er mittendrin ab und hinterlaesst `fehler` im Journal. Haeuft sich das, gehoert die Kette entzerrt — etwa indem die Scouts frueher laufen als Ideator und Fit-Filter.

## Auffaellig

- **testentwickler**: 234 von 284 Laeufen abgebrochen.
- **kern-pruefer**: 6 von 64 Laeufen abgebrochen.
- **kernbauer**: 349 von 415 Laeufen abgebrochen.
- **projektmanager**: 120 von 163 Laeufen abgebrochen.
- **test-pruefer**: 118 von 158 Laeufen abgebrochen.
- **datenbauer**: 118 von 166 Laeufen abgebrochen.
- **daten-pruefer**: 2 von 51 Laeufen abgebrochen.
- **architekt**: 116 von 137 Laeufen abgebrochen.
- **entwurf-pruefer**: 2 von 18 Laeufen abgebrochen.
- **geschaeftsfuehrer**: 3 von 17 Laeufen abgebrochen.
