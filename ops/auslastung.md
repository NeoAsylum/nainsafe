# Auslastung

Zeitraum: letzte 7 Tage. Erzeugt 2026-09-02T17:01:28 von `agents/auslastung.py`.

Die Fabrik laeuft ueber das Abo — ihre Laeufe kosten kein Geld, aber
Kontingent. Diese Seite misst deshalb Tokens und Ergiebigkeit.

| Rolle | Laeufe | ergiebig | leer | Fehler | Tokens |
|---|---:|---:|---:|---:|---:|
| markt-analyst | 24 | 24 | 0 | 0 | 103.911.330 |
| daten-pruefer | 18 | 18 | 0 | 0 | 94.705.911 |
| rechercheur | 48 | 32 | 16 | 0 | 87.237.359 |
| datenbauer | 17 | 15 | 1 | 0 | 86.941.927 |
| projektmanager | 9 | 8 | 1 | 0 | 72.355.963 |
| kernbauer | 18 | 16 | 2 | 0 | 61.765.402 |
| kern-pruefer | 9 | 9 | 0 | 0 | 51.518.634 |
| prozess-analyst | 8 | 8 | 0 | 0 | 33.053.333 |
| geschaeftsfuehrer | 8 | 8 | 0 | 0 | 19.338.299 |
| testentwickler | 6 | 5 | 0 | 0 | 14.927.208 |
| modell-scout | 9 | 8 | 1 | 0 | 11.929.721 |
| ideator | 12 | 10 | 2 | 0 | 11.120.922 |
| regel-scout | 14 | 12 | 1 | 1 | 8.323.808 |
| pain-scout | 12 | 11 | 1 | 0 | 8.316.481 |
| markt-scout | 13 | 12 | 1 | 0 | 7.761.398 |
| portfolio-manager | 2 | 2 | 0 | 0 | 7.669.823 |
| fit-filter | 12 | 10 | 2 | 0 | 5.357.430 |
| test-pruefer | 1 | 1 | 0 | 0 | 5.287.927 |
| tech-scout | 12 | 11 | 1 | 0 | 5.162.982 |
| anwalt | 3 | 3 | 0 | 0 | 3.893.563 |
| verbesserer | 2 | 2 | 0 | 0 | 3.224.292 |
| advocatus-nachfrage | 3 | 3 | 0 | 0 | 3.074.026 |
| advocatus-wettbewerb | 3 | 3 | 0 | 0 | 2.706.855 |
| advocatus-vertrieb | 3 | 3 | 0 | 0 | 2.684.207 |
| advocatus-recht | 3 | 3 | 0 | 0 | 2.266.548 |
| advocatus-betrieb | 3 | 3 | 0 | 0 | 1.670.476 |
| digest-redakteur | 2 | 2 | 0 | 0 | 981.730 |
| architekt | 1 | 0 | 0 | 0 | 0 |
| spielentwerfer | 1 | 0 | 0 | 0 | 0 |

**Gesamt:** 276 Laeufe, 717.187.555 Tokens.

**Gegenwert:** 917.25 $ zu Listenpreisen — hochgerechnet rund 3931 $ im Monat. Abgerechnet wird davon nichts, die Laeufe gehen ueber das Abo. Die Zahl sagt, was die Fabrik daraus zieht.

## Kontingent

Im laufenden 5-Stunden-Fenster: 5 Laeufe, 8.926.703 Tokens.
Schwerster Tag im Zeitraum: 2026-09-02 mit 401.900.984 Tokens.

Reisst ein Lauf das Fenster- oder Wochenkontingent, bricht er mittendrin ab und hinterlaesst `fehler` im Journal. Haeuft sich das, gehoert die Kette entzerrt — etwa indem die Scouts frueher laufen als Ideator und Fit-Filter.

## Auffaellig

- **regel-scout**: 1 von 14 Laeufen abgebrochen.
