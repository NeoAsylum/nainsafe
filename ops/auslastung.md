# Auslastung

Zeitraum: letzte 7 Tage. Erzeugt 2026-08-27T20:19:01 von `agents/auslastung.py`.

Die Fabrik laeuft ueber das Abo — ihre Laeufe kosten kein Geld, aber
Kontingent. Diese Seite misst deshalb Tokens und Ergiebigkeit.

| Rolle | Laeufe | ergiebig | leer | Fehler | Tokens |
|---|---:|---:|---:|---:|---:|
| regel-scout | 3 | 1 | 1 | 0 | 23.730 |
| ideator | 2 | 1 | 1 | 0 | 13.882 |
| fit-filter | 2 | 1 | 1 | 0 | 9.673 |

**Gesamt:** 7 Laeufe, 47.285 Tokens.

**Gegenwert:** 3.04 $ zu Listenpreisen — hochgerechnet rund 13 $ im Monat. Abgerechnet wird davon nichts, die Laeufe gehen ueber das Abo. Die Zahl sagt, was die Fabrik daraus zieht.

## Kontingent

Im laufenden 5-Stunden-Fenster: 7 Laeufe, 47.285 Tokens.
Schwerster Tag im Zeitraum: 2026-08-27 mit 47.285 Tokens.

Reisst ein Lauf das Fenster- oder Wochenkontingent, bricht er mittendrin ab und hinterlaesst `fehler` im Journal. Haeuft sich das, gehoert die Kette entzerrt — etwa indem die Scouts frueher laufen als Ideator und Fit-Filter.
