# Auslastung

Zeitraum: letzte 7 Tage. Erzeugt 2026-08-30T07:35:44 von `agents/auslastung.py`.

Die Fabrik laeuft ueber das Abo — ihre Laeufe kosten kein Geld, aber
Kontingent. Diese Seite misst deshalb Tokens und Ergiebigkeit.

| Rolle | Laeufe | ergiebig | leer | Fehler | Tokens |
|---|---:|---:|---:|---:|---:|
| rechercheur | 48 | 32 | 16 | 0 | 87.237.359 |
| markt-analyst | 18 | 18 | 0 | 0 | 75.471.939 |
| modell-scout | 8 | 7 | 1 | 0 | 10.478.073 |
| ideator | 11 | 9 | 2 | 0 | 9.612.432 |
| portfolio-manager | 2 | 2 | 0 | 0 | 7.669.823 |
| pain-scout | 11 | 10 | 1 | 0 | 6.829.286 |
| regel-scout | 13 | 11 | 1 | 1 | 6.329.621 |
| markt-scout | 12 | 11 | 1 | 0 | 6.231.776 |
| tech-scout | 11 | 10 | 1 | 0 | 4.481.300 |
| fit-filter | 10 | 8 | 2 | 0 | 3.905.951 |
| anwalt | 3 | 3 | 0 | 0 | 3.893.563 |
| verbesserer | 2 | 2 | 0 | 0 | 3.224.292 |
| advocatus-nachfrage | 3 | 3 | 0 | 0 | 3.074.026 |
| advocatus-wettbewerb | 3 | 3 | 0 | 0 | 2.706.855 |
| advocatus-vertrieb | 3 | 3 | 0 | 0 | 2.684.207 |
| advocatus-recht | 3 | 3 | 0 | 0 | 2.266.548 |
| prozess-analyst | 1 | 1 | 0 | 0 | 2.218.205 |
| advocatus-betrieb | 3 | 3 | 0 | 0 | 1.670.476 |
| digest-redakteur | 2 | 2 | 0 | 0 | 981.730 |

**Gesamt:** 167 Laeufe, 240.967.462 Tokens.

**Gegenwert:** 434.78 $ zu Listenpreisen — hochgerechnet rund 1863 $ im Monat. Abgerechnet wird davon nichts, die Laeufe gehen ueber das Abo. Die Zahl sagt, was die Fabrik daraus zieht.

## Kontingent

Im laufenden 5-Stunden-Fenster: 23 Laeufe, 56.688.025 Tokens.
Schwerster Tag im Zeitraum: 2026-08-29 mit 105.362.338 Tokens.

Reisst ein Lauf das Fenster- oder Wochenkontingent, bricht er mittendrin ab und hinterlaesst `fehler` im Journal. Haeuft sich das, gehoert die Kette entzerrt — etwa indem die Scouts frueher laufen als Ideator und Fit-Filter.

## Auffaellig

- **regel-scout**: 1 von 13 Laeufen abgebrochen.
