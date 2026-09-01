# Auslastung

Zeitraum: letzte 7 Tage. Erzeugt 2026-09-01T16:39:29 von `agents/auslastung.py`.

Die Fabrik laeuft ueber das Abo — ihre Laeufe kosten kein Geld, aber
Kontingent. Diese Seite misst deshalb Tokens und Ergiebigkeit.

| Rolle | Laeufe | ergiebig | leer | Fehler | Tokens |
|---|---:|---:|---:|---:|---:|
| markt-analyst | 28 | 28 | 0 | 0 | 114.721.231 |
| rechercheur | 52 | 36 | 16 | 0 | 89.453.362 |
| architekt | 7 | 6 | 1 | 0 | 50.177.218 |
| prozess-analyst | 8 | 8 | 0 | 0 | 33.053.333 |
| spielentwerfer | 7 | 5 | 2 | 0 | 29.337.862 |
| entwurf-pruefer | 7 | 6 | 1 | 0 | 26.754.090 |
| ideator | 14 | 12 | 2 | 0 | 15.351.012 |
| modell-scout | 10 | 9 | 1 | 0 | 13.265.549 |
| datenbauer | 3 | 3 | 0 | 0 | 12.959.318 |
| fit-filter | 17 | 15 | 2 | 0 | 9.773.354 |
| regel-scout | 15 | 13 | 1 | 1 | 9.649.881 |
| pain-scout | 13 | 12 | 1 | 0 | 9.277.557 |
| markt-scout | 14 | 13 | 1 | 0 | 9.171.552 |
| projektmanager | 3 | 1 | 1 | 0 | 7.729.674 |
| portfolio-manager | 2 | 2 | 0 | 0 | 7.669.823 |
| daten-pruefer | 2 | 1 | 1 | 0 | 6.553.132 |
| tech-scout | 13 | 12 | 1 | 0 | 6.435.280 |
| geschaeftsfuehrer | 2 | 2 | 0 | 0 | 4.310.982 |
| kernbauer | 2 | 1 | 1 | 0 | 3.935.770 |
| anwalt | 3 | 3 | 0 | 0 | 3.893.563 |
| verbesserer | 2 | 2 | 0 | 0 | 3.224.292 |
| advocatus-nachfrage | 3 | 3 | 0 | 0 | 3.074.026 |
| advocatus-wettbewerb | 3 | 3 | 0 | 0 | 2.706.855 |
| advocatus-vertrieb | 3 | 3 | 0 | 0 | 2.684.207 |
| advocatus-recht | 3 | 3 | 0 | 0 | 2.266.548 |
| datenkurator | 1 | 1 | 0 | 0 | 2.239.339 |
| advocatus-betrieb | 3 | 3 | 0 | 0 | 1.670.476 |
| digest-redakteur | 2 | 2 | 0 | 0 | 981.730 |

**Gesamt:** 242 Laeufe, 482.321.016 Tokens.

**Gegenwert:** 713.28 $ zu Listenpreisen — hochgerechnet rund 3057 $ im Monat. Abgerechnet wird davon nichts, die Laeufe gehen ueber das Abo. Die Zahl sagt, was die Fabrik daraus zieht.

## Kontingent

Im laufenden 5-Stunden-Fenster: 27 Laeufe, 125.064.653 Tokens.
Schwerster Tag im Zeitraum: 2026-09-01 mit 125.064.653 Tokens.

Reisst ein Lauf das Fenster- oder Wochenkontingent, bricht er mittendrin ab und hinterlaesst `fehler` im Journal. Haeuft sich das, gehoert die Kette entzerrt — etwa indem die Scouts frueher laufen als Ideator und Fit-Filter.

## Auffaellig

- **regel-scout**: 1 von 15 Laeufen abgebrochen.
