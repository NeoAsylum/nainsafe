# Auslastung

Zeitraum: letzte 7 Tage. Erzeugt 2026-09-06T08:32:20 von `agents/auslastung.py`.

Die Fabrik laeuft ueber das Abo — ihre Laeufe kosten kein Geld, aber
Kontingent. Diese Seite misst deshalb Tokens und Ergiebigkeit.

| Rolle | Laeufe | ergiebig | leer | Fehler | Tokens |
|---|---:|---:|---:|---:|---:|
| kern-pruefer | 66 | 60 | 0 | 6 | 689.434.490 |
| testentwickler | 286 | 50 | 0 | 236 | 675.516.528 |
| kernbauer | 416 | 64 | 2 | 350 | 600.284.587 |
| projektmanager | 166 | 41 | 3 | 122 | 420.096.633 |
| test-pruefer | 160 | 42 | 0 | 118 | 368.198.781 |
| datenbauer | 168 | 47 | 1 | 120 | 327.445.002 |
| daten-pruefer | 53 | 51 | 0 | 2 | 321.895.683 |
| architekt | 138 | 19 | 2 | 117 | 141.347.188 |
| spielentwerfer | 10 | 9 | 1 | 0 | 102.643.113 |
| entwurf-pruefer | 20 | 18 | 0 | 2 | 93.908.648 |
| bruchtester | 4 | 4 | 0 | 0 | 62.542.774 |
| markt-analyst | 9 | 9 | 0 | 0 | 57.783.092 |
| geschaeftsfuehrer | 18 | 12 | 2 | 4 | 38.250.504 |
| prozess-analyst | 8 | 8 | 0 | 0 | 33.053.333 |
| portfolio-manager | 2 | 2 | 0 | 0 | 11.860.073 |
| modell-scout | 3 | 3 | 0 | 0 | 6.349.119 |
| verbesserer | 2 | 2 | 0 | 0 | 5.773.054 |
| regel-scout | 3 | 3 | 0 | 0 | 4.078.422 |
| pain-scout | 3 | 3 | 0 | 0 | 4.020.988 |
| rechercheur | 4 | 4 | 0 | 0 | 3.338.649 |
| markt-scout | 3 | 3 | 0 | 0 | 2.972.492 |
| ideator | 2 | 2 | 0 | 0 | 2.812.353 |
| fit-filter | 3 | 3 | 0 | 0 | 1.944.865 |
| tech-scout | 3 | 3 | 0 | 0 | 1.918.353 |
| digest-redakteur | 2 | 2 | 0 | 0 | 1.191.102 |

**Gesamt:** 1552 Laeufe, 3.978.659.826 Tokens.

**Gegenwert:** 3523.34 $ zu Listenpreisen — hochgerechnet rund 15100 $ im Monat. Abgerechnet wird davon nichts, die Laeufe gehen ueber das Abo. Die Zahl sagt, was die Fabrik daraus zieht.

## Kontingent

Im laufenden 5-Stunden-Fenster: 32 Laeufe, 204.828.273 Tokens.
Schwerster Tag im Zeitraum: 2026-09-05 mit 1.547.102.809 Tokens.

Reisst ein Lauf das Fenster- oder Wochenkontingent, bricht er mittendrin ab und hinterlaesst `fehler` im Journal. Haeuft sich das, gehoert die Kette entzerrt — etwa indem die Scouts frueher laufen als Ideator und Fit-Filter.

## Auffaellig

- **kern-pruefer**: 6 von 66 Laeufen abgebrochen.
- **testentwickler**: 236 von 286 Laeufen abgebrochen.
- **kernbauer**: 350 von 416 Laeufen abgebrochen.
- **projektmanager**: 122 von 166 Laeufen abgebrochen.
- **test-pruefer**: 118 von 160 Laeufen abgebrochen.
- **datenbauer**: 120 von 168 Laeufen abgebrochen.
- **daten-pruefer**: 2 von 53 Laeufen abgebrochen.
- **architekt**: 117 von 138 Laeufen abgebrochen.
- **entwurf-pruefer**: 2 von 20 Laeufen abgebrochen.
- **geschaeftsfuehrer**: 4 von 18 Laeufen abgebrochen.
