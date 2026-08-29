# Auslastung

Zeitraum: letzte 7 Tage. Erzeugt 2026-08-29T09:13:07 von `agents/auslastung.py`.

Die Fabrik laeuft ueber das Abo — ihre Laeufe kosten kein Geld, aber
Kontingent. Diese Seite misst deshalb Tokens und Ergiebigkeit.

| Rolle | Laeufe | ergiebig | leer | Fehler | Tokens |
|---|---:|---:|---:|---:|---:|
| rechercheur | 43 | 27 | 16 | 0 | 82.465.437 |
| ideator | 9 | 7 | 2 | 0 | 6.793.679 |
| markt-analyst | 4 | 4 | 0 | 0 | 6.431.909 |
| modell-scout | 5 | 4 | 1 | 0 | 4.394.435 |
| markt-scout | 9 | 8 | 1 | 0 | 4.018.796 |
| anwalt | 3 | 3 | 0 | 0 | 3.893.563 |
| pain-scout | 8 | 7 | 1 | 0 | 3.126.124 |
| advocatus-nachfrage | 3 | 3 | 0 | 0 | 3.074.026 |
| regel-scout | 10 | 8 | 1 | 1 | 3.060.012 |
| fit-filter | 8 | 6 | 2 | 0 | 2.875.126 |
| advocatus-wettbewerb | 3 | 3 | 0 | 0 | 2.706.855 |
| advocatus-vertrieb | 3 | 3 | 0 | 0 | 2.684.207 |
| tech-scout | 8 | 7 | 1 | 0 | 2.478.743 |
| advocatus-recht | 3 | 3 | 0 | 0 | 2.266.548 |
| advocatus-betrieb | 3 | 3 | 0 | 0 | 1.670.476 |

**Gesamt:** 122 Laeufe, 131.939.936 Tokens.

**Gegenwert:** 315.41 $ zu Listenpreisen — hochgerechnet rund 1352 $ im Monat. Abgerechnet wird davon nichts, die Laeufe gehen ueber das Abo. Die Zahl sagt, was die Fabrik daraus zieht.

## Kontingent

Im laufenden 5-Stunden-Fenster: 20 Laeufe, 53.022.837 Tokens.
Schwerster Tag im Zeitraum: 2026-08-28 mit 78.869.814 Tokens.

Reisst ein Lauf das Fenster- oder Wochenkontingent, bricht er mittendrin ab und hinterlaesst `fehler` im Journal. Haeuft sich das, gehoert die Kette entzerrt — etwa indem die Scouts frueher laufen als Ideator und Fit-Filter.

## Auffaellig

- **regel-scout**: 1 von 10 Laeufen abgebrochen.
