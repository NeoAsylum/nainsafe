# Auslastung

Zeitraum: letzte 7 Tage. Erzeugt 2026-08-30T05:00:01 von `agents/auslastung.py`.

Die Fabrik laeuft ueber das Abo — ihre Laeufe kosten kein Geld, aber
Kontingent. Diese Seite misst deshalb Tokens und Ergiebigkeit.

| Rolle | Laeufe | ergiebig | leer | Fehler | Tokens |
|---|---:|---:|---:|---:|---:|
| rechercheur | 46 | 30 | 16 | 0 | 85.923.150 |
| markt-analyst | 18 | 18 | 0 | 0 | 75.471.939 |
| ideator | 11 | 9 | 2 | 0 | 9.612.432 |
| modell-scout | 7 | 6 | 1 | 0 | 8.656.358 |
| markt-scout | 11 | 10 | 1 | 0 | 5.745.909 |
| regel-scout | 12 | 10 | 1 | 1 | 5.618.686 |
| pain-scout | 10 | 9 | 1 | 0 | 5.442.168 |
| tech-scout | 10 | 9 | 1 | 0 | 3.995.142 |
| fit-filter | 10 | 8 | 2 | 0 | 3.905.951 |
| anwalt | 3 | 3 | 0 | 0 | 3.893.563 |
| advocatus-nachfrage | 3 | 3 | 0 | 0 | 3.074.026 |
| portfolio-manager | 1 | 1 | 0 | 0 | 3.045.451 |
| advocatus-wettbewerb | 3 | 3 | 0 | 0 | 2.706.855 |
| advocatus-vertrieb | 3 | 3 | 0 | 0 | 2.684.207 |
| advocatus-recht | 3 | 3 | 0 | 0 | 2.266.548 |
| advocatus-betrieb | 3 | 3 | 0 | 0 | 1.670.476 |
| verbesserer | 1 | 1 | 0 | 0 | 595.933 |
| digest-redakteur | 1 | 1 | 0 | 0 | 439.280 |

**Gesamt:** 156 Laeufe, 224.748.074 Tokens.

**Gegenwert:** 416.65 $ zu Listenpreisen — hochgerechnet rund 1786 $ im Monat. Abgerechnet wird davon nichts, die Laeufe gehen ueber das Abo. Die Zahl sagt, was die Fabrik daraus zieht.

## Kontingent

Im laufenden 5-Stunden-Fenster: 12 Laeufe, 40.468.637 Tokens.
Schwerster Tag im Zeitraum: 2026-08-29 mit 105.362.338 Tokens.

Reisst ein Lauf das Fenster- oder Wochenkontingent, bricht er mittendrin ab und hinterlaesst `fehler` im Journal. Haeuft sich das, gehoert die Kette entzerrt — etwa indem die Scouts frueher laufen als Ideator und Fit-Filter.

## Auffaellig

- **regel-scout**: 1 von 12 Laeufen abgebrochen.
