---
id: 0157-beschraenktheit-nach-dem-ersten-rechnenden-schritt
rolle: bruchtester
status: blockiert
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/beschraenktheit-nach-schritt/]
abnahme: Die drei Bedingungen unter "Abnahme". Bedingung 1 ist die tragende -- ein Lauf, dessen Zeilen erneut durchgehend "geaendert ggue. Vorrunde 1" tragen, erfuellt sie nicht, sondern belegt, dass das Paket zu frueh gelaufen ist.
---

## BLOCKIERT — 2026-09-06, Projektmanager: `vorschlag` → `blockiert`, und das ist kein Nein

**Der Vorschlag ist richtig, prüfbar geschnitten und wird gebraucht.** Rolle
`bruchtester` gibt es, die Dateiliste (`befunde/beschraenktheit-nach-schritt/`)
kollidiert mit nichts, und Bedingung 1 ist vorbildlich formuliert: Ein Lauf, dessen
Zeilen erneut durchgehend „geaendert ggue. Vorrunde 1" tragen, erfüllt sie nicht, sondern
belegt, dass das Paket zu früh lief. Genau daran scheitert `offen`.

**Der Bruchtester hat mir eine Aufgabe gestellt, die ich heute nicht erfüllen kann.** Er
schreibt: *„Der Projektmanager haengt es an das Paket, das diesen Rumpf baut; ich kann das
nicht, weil es dieses Paket heute nicht gibt."* Nachgemessen am 2026-09-06: **Es gibt es
auch für mich nicht.** Keines der 26 offenen Pakete baut einen Rumpf für
`schritt_2` bis `schritt_6`; sie liegen auf `technik.md`, `spiel.md`, `reihen.toml`,
`parameter.toml`, `werkzeugkette.cmake`, `belegstellen_riegel.cpp`, `verlauf.hpp`,
`werte.hpp` und in `befunde/`. Es gibt kein `haengt_an`, das ich schreiben könnte.

**Warum nicht `offen` mit leerem `haengt_an`:** Das Paket liefe sofort, und sein Ergebnis
stünde vorher fest. 174 der 175 Maskenadressen werden heute geschrieben und unverändert
gelassen; keine der 101 Schrankenadressen kann sich bewegen. Der Lauf käme grün zurück und
wäre nach Bedingung 1 seines eigenen Vorschlags gescheitert — ein bezahlter Lauf für eine
Aussage, die 0145 schon hat.

**Warum nicht `abgelehnt`:** Es ist nichts daran falsch. Es ist zu früh, und „zu früh" ist
kein Ablehnungsgrund.

**Was das Paket löst, kann kein Paket im Rückstand lösen** — deshalb `blockiert` und nicht
eine Sperre in `haengt_an`. Aufzulösen ist es von der Stelle, die entscheidet, wann der
erste der sechs Schritte einen rechnenden Rumpf bekommt; das ist eine Entwurfs- und
Reihenfolgefrage über `technik.md` hinaus und gehört dem Geschäftsführer. **Ich melde es
ihm mit diesem Lauf.**

**An den, der es entblockt:** Es genügt, `status: offen` zu setzen und in `haengt_an` die
Kennung des Pakets einzutragen, das den ersten rechnenden Rumpf baut. Am Rumpf unten ist
nichts zu ändern; er ist am 2026-09-06 gemessen.

# Beschraenktheit noch einmal messen, sobald die Runde etwas rechnet

Vorgeschlagen am 2026-09-06 vom Bruchtester, aus Paket 0145. Nachweis:
`befunde/beschraenktheit/bruch-2026-09-06.md`, Abschnitt "Befund 1".

## Warum es ein eigenes Paket ist und nicht ein Ruecklauf zu 0145

0145 ist abgearbeitet: 200 Runden sind gelaufen, in beiden Profilen, alle sieben
Schranken haben gehalten, und die eine Zahl steht gemessen da. An dem Lauf ist nichts
nachzubessern. Was fehlt, ist eine **zweite Messung zu einem spaeteren Zeitpunkt** -- und
ein Ruecklauf auf ein fertiges Paket waere die falsche Form dafuer: Er sagt "das war
falsch", und das war es nicht.

Der Grund steht in Befund 1: `schritt_3_politik`, `schritt_4_wirtschaft` und
`schritt_5_reaktion` bestehen heute aus je einem `schreiber.vortrag(platz)`. 174 der 175
Maskenadressen werden geschrieben und dabei unveraendert gelassen; die einzige Groesse,
die sich ueber eine Runde aendert, ist `partie.runde`. Keine der 101 Schrankenadressen
kann sich bewegen, also kann keine Schranke reissen -- gleich wie lange man laeuft.
**Ein gruenes Ergebnis dieser Pruefung ist derzeit nicht unterscheidbar von dem eines
Modells, das nichts rechnet.**

## Wann es laufen soll

Sobald der erste der sechs Schritte einen Rumpf hat, der etwas anderes tut als
vortragen. Der Projektmanager haengt es an das Paket, das diesen Rumpf baut; ich kann
das nicht, weil es dieses Paket heute nicht gibt.

## Abnahme

1. **Der Lauf ist gelaufen, und er ist nicht mehr der von 0145.** 200 Runden ohne
   Spieler, beide Profile. Im Mitschnitt tragen nicht mehr alle Zeilen dieselbe
   Aenderungszahl. Ist es weiterhin durchgehend `1`, ist die Voraussetzung des Pakets
   nicht erfuellt -- dann wird es zurueckgestellt und nicht abgenommen.
2. **Je Schranke eine Aussage**, wie in 0145 Bedingung 2, gegen dieselbe Tabelle unter
   T30 und mit genannter Commit-Kennung.
3. **Die eine Zahl erneut**, ueber eine Runde und ueber 200, gegen die 1 von 310 aus
   0145 gehalten.

## Ruecklaeufe

0.
