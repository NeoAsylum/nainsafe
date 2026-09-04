# Auslastung

Zeitraum: letzte 7 Tage. Erzeugt 2026-09-04T16:41:58 von `agents/auslastung.py`.

Die Fabrik laeuft ueber das Abo — ihre Laeufe kosten kein Geld, aber
Kontingent. Diese Seite misst deshalb Tokens und Ergiebigkeit.

| Rolle | Laeufe | ergiebig | leer | Fehler | Tokens |
|---|---:|---:|---:|---:|---:|
| kern-pruefer | 27 | 27 | 0 | 0 | 234.429.166 |
| projektmanager | 24 | 23 | 1 | 0 | 218.665.436 |
| daten-pruefer | 39 | 39 | 0 | 0 | 216.718.606 |
| kernbauer | 33 | 30 | 2 | 1 | 211.842.467 |
| datenbauer | 33 | 30 | 1 | 2 | 199.911.855 |
| markt-analyst | 24 | 24 | 0 | 0 | 103.911.330 |
| test-pruefer | 11 | 11 | 0 | 0 | 91.743.036 |
| rechercheur | 48 | 32 | 16 | 0 | 87.237.359 |
| testentwickler | 22 | 21 | 0 | 1 | 83.428.375 |
| entwurf-pruefer | 9 | 9 | 0 | 0 | 59.676.466 |
| spielentwerfer | 7 | 6 | 1 | 0 | 53.683.853 |
| architekt | 6 | 5 | 1 | 0 | 52.508.410 |
| geschaeftsfuehrer | 13 | 12 | 1 | 0 | 33.839.688 |
| prozess-analyst | 8 | 8 | 0 | 0 | 33.053.333 |
| modell-scout | 9 | 8 | 1 | 0 | 11.929.721 |
| ideator | 10 | 9 | 1 | 0 | 11.107.040 |
| pain-scout | 12 | 11 | 1 | 0 | 8.316.481 |
| regel-scout | 11 | 11 | 0 | 0 | 8.300.078 |
| markt-scout | 13 | 12 | 1 | 0 | 7.761.398 |
| portfolio-manager | 2 | 2 | 0 | 0 | 7.669.823 |
| fit-filter | 10 | 9 | 1 | 0 | 5.347.757 |
| tech-scout | 12 | 11 | 1 | 0 | 5.162.982 |
| anwalt | 3 | 3 | 0 | 0 | 3.893.563 |
| verbesserer | 2 | 2 | 0 | 0 | 3.224.292 |
| advocatus-nachfrage | 3 | 3 | 0 | 0 | 3.074.026 |
| advocatus-wettbewerb | 3 | 3 | 0 | 0 | 2.706.855 |
| advocatus-vertrieb | 3 | 3 | 0 | 0 | 2.684.207 |
| advocatus-recht | 3 | 3 | 0 | 0 | 2.266.548 |
| advocatus-betrieb | 3 | 3 | 0 | 0 | 1.670.476 |
| digest-redakteur | 2 | 2 | 0 | 0 | 981.730 |

**Gesamt:** 405 Laeufe, 1.766.746.357 Tokens.

**Gegenwert:** 1818.89 $ zu Listenpreisen — hochgerechnet rund 7795 $ im Monat. Abgerechnet wird davon nichts, die Laeufe gehen ueber das Abo. Die Zahl sagt, was die Fabrik daraus zieht.

## Kontingent

Im laufenden 5-Stunden-Fenster: 0 Laeufe, 0 Tokens.
Schwerster Tag im Zeitraum: 2026-09-02 mit 630.164.365 Tokens.

Reisst ein Lauf das Fenster- oder Wochenkontingent, bricht er mittendrin ab und hinterlaesst `fehler` im Journal. Haeuft sich das, gehoert die Kette entzerrt — etwa indem die Scouts frueher laufen als Ideator und Fit-Filter.

## Auffaellig

- **kernbauer**: 1 von 33 Laeufen abgebrochen.
- **datenbauer**: 2 von 33 Laeufen abgebrochen.
- **testentwickler**: 1 von 22 Laeufen abgebrochen.
