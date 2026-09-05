# Auslastung

Zeitraum: letzte 7 Tage. Erzeugt 2026-09-05T06:25:04 von `agents/auslastung.py`.

Die Fabrik laeuft ueber das Abo — ihre Laeufe kosten kein Geld, aber
Kontingent. Diese Seite misst deshalb Tokens und Ergiebigkeit.

| Rolle | Laeufe | ergiebig | leer | Fehler | Tokens |
|---|---:|---:|---:|---:|---:|
| kernbauer | 42 | 39 | 2 | 1 | 331.555.898 |
| kern-pruefer | 36 | 36 | 0 | 0 | 327.420.521 |
| testentwickler | 33 | 32 | 0 | 1 | 317.525.015 |
| projektmanager | 31 | 28 | 3 | 0 | 305.499.019 |
| test-pruefer | 22 | 22 | 0 | 0 | 256.198.843 |
| datenbauer | 35 | 32 | 1 | 2 | 227.693.163 |
| daten-pruefer | 40 | 40 | 0 | 0 | 224.892.472 |
| markt-analyst | 22 | 22 | 0 | 0 | 101.023.067 |
| architekt | 12 | 10 | 2 | 0 | 81.153.975 |
| entwurf-pruefer | 11 | 11 | 0 | 0 | 69.535.834 |
| spielentwerfer | 7 | 6 | 1 | 0 | 53.683.853 |
| rechercheur | 10 | 10 | 0 | 0 | 38.745.166 |
| geschaeftsfuehrer | 14 | 12 | 2 | 0 | 35.984.180 |
| prozess-analyst | 8 | 8 | 0 | 0 | 33.053.333 |
| modell-scout | 6 | 6 | 0 | 0 | 10.731.865 |
| ideator | 5 | 5 | 0 | 0 | 8.143.516 |
| portfolio-manager | 2 | 2 | 0 | 0 | 7.669.823 |
| regel-scout | 6 | 6 | 0 | 0 | 7.409.066 |
| pain-scout | 6 | 6 | 0 | 0 | 7.266.113 |
| markt-scout | 6 | 6 | 0 | 0 | 5.830.195 |
| tech-scout | 6 | 6 | 0 | 0 | 3.952.837 |
| fit-filter | 5 | 5 | 0 | 0 | 3.398.182 |
| verbesserer | 2 | 2 | 0 | 0 | 3.224.292 |
| digest-redakteur | 2 | 2 | 0 | 0 | 981.730 |

**Gesamt:** 369 Laeufe, 2.462.571.958 Tokens.

**Gegenwert:** 2160.63 $ zu Listenpreisen — hochgerechnet rund 9260 $ im Monat. Abgerechnet wird davon nichts, die Laeufe gehen ueber das Abo. Die Zahl sagt, was die Fabrik daraus zieht.

## Kontingent

Im laufenden 5-Stunden-Fenster: 22 Laeufe, 293.664.309 Tokens.
Schwerster Tag im Zeitraum: 2026-09-04 mit 764.109.349 Tokens.

Reisst ein Lauf das Fenster- oder Wochenkontingent, bricht er mittendrin ab und hinterlaesst `fehler` im Journal. Haeuft sich das, gehoert die Kette entzerrt — etwa indem die Scouts frueher laufen als Ideator und Fit-Filter.

## Auffaellig

- **kernbauer**: 1 von 42 Laeufen abgebrochen.
- **testentwickler**: 1 von 33 Laeufen abgebrochen.
- **datenbauer**: 2 von 35 Laeufen abgebrochen.
