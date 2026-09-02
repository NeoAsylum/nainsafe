# Auslastung

Zeitraum: letzte 7 Tage. Erzeugt 2026-09-02T17:46:34 von `agents/auslastung.py`.

Die Fabrik laeuft ueber das Abo — ihre Laeufe kosten kein Geld, aber
Kontingent. Diese Seite misst deshalb Tokens und Ergiebigkeit.

| Rolle | Laeufe | ergiebig | leer | Fehler | Tokens |
|---|---:|---:|---:|---:|---:|
| markt-analyst | 24 | 24 | 0 | 0 | 103.911.330 |
| daten-pruefer | 20 | 20 | 0 | 0 | 101.385.127 |
| datenbauer | 17 | 16 | 1 | 0 | 93.971.403 |
| rechercheur | 48 | 32 | 16 | 0 | 87.237.359 |
| projektmanager | 10 | 9 | 1 | 0 | 79.287.471 |
| kernbauer | 19 | 16 | 2 | 0 | 61.765.402 |
| kern-pruefer | 10 | 10 | 0 | 0 | 59.434.825 |
| prozess-analyst | 8 | 8 | 0 | 0 | 33.053.333 |
| testentwickler | 7 | 6 | 0 | 0 | 21.118.464 |
| geschaeftsfuehrer | 9 | 9 | 0 | 0 | 21.044.922 |
| test-pruefer | 2 | 2 | 0 | 0 | 15.935.623 |
| modell-scout | 9 | 8 | 1 | 0 | 11.929.721 |
| ideator | 12 | 10 | 2 | 0 | 11.120.922 |
| spielentwerfer | 2 | 1 | 0 | 0 | 9.830.496 |
| regel-scout | 14 | 12 | 1 | 1 | 8.323.808 |
| pain-scout | 12 | 11 | 1 | 0 | 8.316.481 |
| architekt | 2 | 0 | 1 | 0 | 8.190.806 |
| markt-scout | 13 | 12 | 1 | 0 | 7.761.398 |
| portfolio-manager | 2 | 2 | 0 | 0 | 7.669.823 |
| fit-filter | 12 | 10 | 2 | 0 | 5.357.430 |
| tech-scout | 12 | 11 | 1 | 0 | 5.162.982 |
| anwalt | 3 | 3 | 0 | 0 | 3.893.563 |
| verbesserer | 2 | 2 | 0 | 0 | 3.224.292 |
| advocatus-nachfrage | 3 | 3 | 0 | 0 | 3.074.026 |
| advocatus-wettbewerb | 3 | 3 | 0 | 0 | 2.706.855 |
| advocatus-vertrieb | 3 | 3 | 0 | 0 | 2.684.207 |
| advocatus-recht | 3 | 3 | 0 | 0 | 2.266.548 |
| advocatus-betrieb | 3 | 3 | 0 | 0 | 1.670.476 |
| digest-redakteur | 2 | 2 | 0 | 0 | 981.730 |

**Gesamt:** 286 Laeufe, 782.310.823 Tokens.

**Gegenwert:** 975.08 $ zu Listenpreisen — hochgerechnet rund 4179 $ im Monat. Abgerechnet wird davon nichts, die Laeufe gehen ueber das Abo. Die Zahl sagt, was die Fabrik daraus zieht.

## Kontingent

Im laufenden 5-Stunden-Fenster: 15 Laeufe, 74.049.971 Tokens.
Schwerster Tag im Zeitraum: 2026-09-02 mit 467.024.252 Tokens.

Reisst ein Lauf das Fenster- oder Wochenkontingent, bricht er mittendrin ab und hinterlaesst `fehler` im Journal. Haeuft sich das, gehoert die Kette entzerrt — etwa indem die Scouts frueher laufen als Ideator und Fit-Filter.

## Auffaellig

- **regel-scout**: 1 von 14 Laeufen abgebrochen.
