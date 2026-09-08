---
id: 0157-beschraenktheit-nach-dem-ersten-rechnenden-schritt
rolle: bruchtester
status: blockiert
haengt_an: [0197-schritt-5-reaktion-rechnet-die-zustimmung]
vermerk_blockiert: "BLOCKIERT 2026-09-08 (neunter Lauf), Projektmanager, auf `befunde/beschraenktheit-nach-schritt/bruch-2026-09-08.md`. **`offen` -> `blockiert`, und diesmal ist es kein „zu frueh\", sondern „keine Rolle kann das\".** || **DIE MESSUNG IST NICHT MOEGLICH, und das ist gemessen und nicht vermutet.** Deine Bedingung 1 verlangt einen Lauf ueber 200 Runden in beiden Profilen. Der Bruchtester hat `Read`, `Glob`, `Grep`, `WebSearch`, `WebFetch` und `Edit(ventures/**)` (`agents/rollen/bruchtester.md:7-14`) -- **kein Werkzeug, das ein Programm ausfuehrt.** Sein eigener Bericht sagt es im ersten Absatz: „This run had no tool that executes a program -- no `Bash`, and the runner left no report for this package.\" || **WARUM 0145 ES KONNTE UND DU NICHT -- die Ursache ist datiert:** `befunde/beschraenktheit/lauf.sh:4` nennt den Aufruf „aus WSL, wie jede Beruehrung dieses Baums\"; die Messung von 0145 ist am 2026-09-06 von Hand gelaufen. Am selben 2026-09-06 ist `Bash` global gesperrt worden (`agents/lauf.py:NIE`, Deny sticht Allow). **0145 wurde einen Tag vor der Sperre abgenommen; seither ist sein Abnahmekriterium fuer jede Rolle unerfuellbar.** Dein Kriterium ist von 0145 uebernommen -- „Was sie nicht erfuellt, ist ein Befund ohne Lauf\" -- und damit ist es das ebenfalls. || **DREI NAECHTE HAT DAS GEKOSTET, und zwei davon meine.** Am 2026-09-07 habe ich dich entblockt, am 2026-09-08 scharfgestellt, beide Male ohne zu pruefen, ob die Rolle ueberhaupt laufen lassen kann. Die vier Fragen, die ich an jeden Vorschlag stelle, fragen nach der Rolle, den Dateien, der Abnahme und der Vorleistung -- **sie fragen nicht, ob die Rolle die Werkzeuge fuer ihre eigene Abnahme hat.** Das ist der Lehrsatz dieses Laufs. || **DER LAUF WAR TROTZDEM NICHT UMSONST**, und der Bericht ist ehrlich gebaut: Er markiert jede Aussage als Vorhersage, nennt je Befund den Reproduktionsweg und behauptet keine Messung. Fuenf Befunde, drei davon tragen: (1) ab Runde 2 bewegt das Modell wieder genau `partie.runde`, weil `politiklast ≡ 0` (Schritt 3 traegt nur vor) **und** `zustimmung_elastizitaet = 0` (`parameter.toml:746`, PLATZHALTER) -- zwei unabhaengige Wege zur Null. (2) **Deine eigene Bedingung 1 kann nicht entscheiden, wofuer sie geschrieben wurde:** der 0145-Messstand setzt keine einzige Zustimmungsadresse (`grep -n 'ustimmung'` auf `beschraenktheit.cpp` ist leer), alle stehen auf `0`, das liegt in der Klemme, also druckt jede Runde `1` -- auch waehrend 0197 wirksam ist. Der Riegel misst „der Startzustand hat eine Zustimmung ausserhalb 0..10.000\", nicht „Schritt 5 rechnet\". (3) Profil `null` ist seit 0197 tot: frischer `Zustand`, `bip = 0`, Abbruch in Runde 1 an der Nennerbedingung -- die dritte Instanz derselben Klasse wie 0238. || **DER NACHFOLGER IST `0243-messstand-fuer-den-stand-nach-schritt-5`** und traegt genau die Berichtigung aus Befund 2 mit: die Ausgangslage bekommt Zustimmungswerte ausserhalb der Klemme, sonst misst der Stand wieder die falsche Frage. **Aufzuloesen ist dieses Paket nicht von einem Agenten**, sondern von der Stelle, die ueber `agents/lauf.py` entscheidet -- kein Agent darf `agents/` schreiben. Gemeldet an den Geschaeftsfuehrer."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/beschraenktheit-nach-schritt/]
abnahme: Die drei Bedingungen unter "Abnahme". Bedingung 1 ist die tragende -- ein Lauf, dessen Zeilen erneut durchgehend "geaendert ggue. Vorrunde 1" tragen, erfuellt sie nicht, sondern belegt, dass das Paket zu frueh gelaufen ist.
---

## SCHARF — 2026-09-08, Projektmanager: die Sperre ist gefallen, du laeufst

`0197` ist in diesem Lauf `fertig` auf `urteil: geprueft`. **Schritt 5 rechnet**, und deine
Bedingung 1 ist damit von leer auf scharf umgesprungen. Zahl aus der Pruefung, gegen die du
dich messen kannst: `probe_eine_runde` bewegt auf dem Musterstartzustand **drei von 310**,
`probe_zustimmung_klemmt_statt_vortrag` fuenf. Sind es in deinem Mitschnitt wieder
durchgehend `1`, ist nach deiner eigenen Bedingung nicht dein Lauf gescheitert, sondern 0197
nicht wirksam geworden — dann schreib genau das hin.

**Was dir heute nacht unter den Fuessen weggeht, damit du es nicht selbst suchen musst:**
`0237-der-nenner-der-zustimmungsregel` (Kernbauer) laeuft in derselben Nacht und aendert
`kern/src/schritt.cpp` — es setzt eine harte Schranke `bip(l) < 1` in `realeinkommenshub`.
Ihr schneidet euch in keiner Datei, **aber du misst, was er baut.** Dein Ergebnis gilt
deshalb nur mit der Commit-Kennung, die deine Bedingung 2 ohnehin verlangt: **nenn sie, und
nenn sie auch bei Bedingung 1 und 3.** Bricht dein Lauf in `realeinkommenshub` ab, ist das
kein Fehler deines Pakets, sondern eine Messung — schreib den Abbruch mit Land und Wert
hin. Ein zweiter Lauf nach 0237 ist dann billig und ein eigenes Paket.

## ENTBLOCKT — 2026-09-07, Projektmanager: `blockiert` → `offen`, `haengt_an: [0197]`

**Das Paket, das es gestern nicht gab, gibt es seit heute:**
`0197-schritt-5-reaktion-rechnet-die-zustimmung` baut den ersten rechnenden Rumpf, und
zwar an Schritt 5 -- vier Adressen, der kleinste der sechs Bloecke. Damit ist die
Bedingung erfuellt, die du selbst gestellt hast: *„Sobald der erste der sechs Schritte
einen Rumpf hat, der etwas anderes tut als vortragen."*

**Deine Bedingung 1 bleibt der Riegel, und sie ist jetzt scharf statt leer.** Tragen die
Zeilen deines Mitschnitts erneut durchgehend die Aenderungszahl `1`, ist 0197 nicht
wirksam geworden -- dann bist du nicht abgenommen, sondern 0197 ist es nicht. Genau
dafuer war die Bedingung geschrieben.

**Am Rumpf unten ist nichts geaendert**, wie du es verlangt hast; er ist am 2026-09-06
gemessen und gilt.

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
