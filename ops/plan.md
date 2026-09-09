# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-09. Abgedeckt: seit dem zweiten Plan vom 2026-09-08.

## Wo das Vorhaben steht

**Schritt 3 rechnet.** Paket 0284 schreibt den Pfadstand in die Adressen, statt ihn
vorzutragen; damit erreicht zum ersten Mal ein Rundenlauf `werte::schaden`. **Im selben
Commit ist der Kern von 14/14 auf 13/14 gefallen:** `verlauf_probe` — die einzige Probe,
die eine ganze Partie fährt — bricht in Runde 1 ab mit `plus: Summe ausserhalb von i64
(T7)` (`befunde/uebersetzung-2026-09-09.md:308-310`). 270 Pakete, 240 fertig, 6 offen,
6 Vorschläge, 5 gebaut, 5 blockiert; Werkstattbaum 6 von 29 rot (gestern 3). Geld bindet
nicht.

## Der Engpass

**`parameter.toml` trägt in 47 von 51 Werten `# PLATZHALTER`, und einer davon schaltet die
Wirkungskette der Idee ab.**

`zustimmung_elastizitaet = 0  # PLATZHALTER` (`parameter.toml:746`). Der Kommentar
darüber sagt selbst, was das kostet: „**Bei 0 ist Gegenkraft 2 aus, und mit ihr Kanal 2 --
die Wirkungskette, die spiel.md ausdruecklich als 'die Wirkungskette der Idee'
bezeichnet**" (`:743-745`). Als Eichverfahren steht dort „Kalibriert: Selbstspieler".

Der Bruchtester hat zwei unabhängige Wege zur Null gemessen
(`aufgaben/0157-…md:6`, Befund 1): Schritt 3 trägt nur vor — **den hat 0284 heute
geschlossen** — und `zustimmung_elastizitaet = 0`. Der zweite ist mit den Mitteln der
Fabrik nicht zu schließen: Den Selbstspieler gibt es nicht, seit 0150 nennt ihn kein Paket
mehr, fünf der zehn Bau-Mitglieder (`daten`, `schnittstelle`, `konsole`, `oberflaeche`,
`werkzeuge/aufbereitung`) sind „noch nicht gebaut" (`uebersetzung-2026-09-09.md:20-24`),
und alle 16 Aufrufe von `schritt::schritt(` stehen in Proben — einen Aufrufer außerhalb
der Tests hat der Kern nicht.

## Was quer liegt

- **Dieselbe Arbeit liegt zweimal im Bestand, unter zwei Nummern mit zwei Ständen.**
  `0275-der-riegel-sieht-mal-gleich-nicht` ist `fertig`, `0276-…` mit identischem Titel ist
  `offen`. `0282-teil-a-misst-den-text-und-nennt-es-verhalten` ist `fertig`, `0283-…` ist
  `gebaut` und kam heute mit `urteil: zurueck` zurück — ein Bauer- und ein Prüferlauf für
  bereits abgenommene Arbeit. Dazu tragen zwei verschiedene Pakete die Nummer 0289 und zwei
  die Nummer 0275. **Drei Kollisionen auf zwanzig Nummern; am 2026-09-08 war es eine.**
- **Die Schleife der Kopfzahlen ist gebrochen, und die nächste ihrer Art steht bereit.**
  0278 lässt den Belegstellenriegel seine drei Zahlen selbst messen — `belegstellen_kopfzahlen`
  ist grün. `zahlwort_riegel` und `zahlwort_messung` sind aus genau demselben Grund rot:
  `werkzeuge/zahlwort/messen.py` hält den Text „Zweiundzwanzig Groessen in
  dreiundzwanzig Deklarationen" fest, während `werte.hpp:32` „vierundzwanzig" liest
  (`pruefung-0284-…-2026-09-09.md:81-85`). Vorschlag 0286 muss messen, nicht abschreiben.
- **`bezeichner_riegel` ist rot durch einen Kommentar von 0284** (`werte.hpp:218`, der
  Begriff `daten_pruefsumme` ist T22 und kein Kern-Bezeichner). Die Datei steht in
  `dateien:` — ein Rücklauf behebt es.
- **Die erste volle Partie wirft eine Meldung ohne Ort.** `politiklast`
  (`schritt.cpp:643`) und `handelsvolumen` (`werte.cpp:834-835`) addieren durch ein blankes
  `festkomma::plus`; `bip` (`werte.cpp:787-802`) zeigt den Hausstandard. Vorschlag 0288.
- **Der Nachtbericht wird weiter an Ort und Stelle überschrieben** (`git status`:
  `M …/uebersetzung-2026-09-09.md`). Der 0284-Befund zitiert ihn viermal mit Zeilennummer;
  morgen früh stimmt keine davon. Zweiter Plan mit diesem Punkt.
- **0274, 0279 und 0280 stehen `gebaut` mit `urteil: geprueft`.** Ein Lauf des
  Projektmanagers macht sie `fertig`.

## Was der Betreiber entscheiden muss

**Es steht dieselbe Frage an wie am 2026-09-07 und 2026-09-08 —
`0208-baulauf-faehrt-beide-profile`, dritter Plan.** Kein Agent darf `agents/**` schreiben
(`agents/lauf.py:NIE`), also kannst nur du das tun. Keine Geldfrage; der Preis ist
Maschinenzeit: ein zweiter `cmake`/`ctest`-Durchgang je Manifest mit
`-DFABRIK_SANITIZER=OFF`, zehn Manifeste, nachts.

- **A — so lassen.** Jede Abnahme mit der Formel „in beiden Bauprofilen" bleibt
  unerfüllbar; sie hat 0194 auf `blockiert` gekostet.
- **B — du fährst die Änderung selbst ein.** Vorbild ist Paket 0131.

**Empfehlung B, unverändert.** Neu ist nur, dass mir die Klasse ein zweites Mal von der
Hand gemeldet wurde: `0157` schließt mit „**Aufzuloesen ist dieses Paket nicht von einem
Agenten** … Gemeldet an den Geschaeftsfuehrer" — seine Bedingung verlangt einen Lauf über
200 Runden, und seit dem Shell-Verbot vom 2026-09-06 kann keine Rolle ein Programm
ausführen. **0157 selbst kostet dich nichts:** sein Nachfolger 0243 ist `fertig`, das Paket
ist überholt, und es zu schließen ist Sache des Projektmanagers.

## Vorrang

1. **0285** — macht `verlauf_probe` wieder grün, eine Datei, Weg vollständig beschrieben.
   Bis das steht, misst nichts im Bestand eine ganze Partie.
2. **Rücklauf 0284** — eine Kommentarzeile in `werte.hpp:218`; sie holt `bezeichner_riegel`
   zurück und schließt das größte Paket der Woche ab.
3. **Wie die 47 Platzhalter zu ihren Werten kommen** — *neu anzulegen*, Rolle
   `spielentwerfer`. „Kalibriert: Selbstspieler" steht in 47 Kommentaren und ist seit dem
   2026-09-06 unerreichbar. Solange das offen ist, rechnet die Runde und trifft null.
4. **0274, 0279, 0280 auf `fertig`** — ein Lauf des Projektmanagers, drei Pakete.
5. **0286**, gebaut als **Messung, nicht als Übertragung** — genau der Zug, der 0278 heute
   grün gemacht hat. Kein zweites Übertragungspaket dieser Art.

**Nicht einplanen:** 0208 (Betreiber, siehe oben). **Vorher zu klären:** ob 0276 und 0283
noch Arbeit sind oder Doppelgänger von 0275 und 0282.

## Die eine Zahl

**Nicht mehr messbar — und das ist Fortschritt.** Seit dem 14. Plan stand sie auf **1 von
310**: eine Runde `weltlauf` bewegte genau `partie.runde`. 0284 hat Schritt 3 zum Schreiben
gebracht und im selben Commit die einzige Probe getötet, die eine ganze Partie zählt.

0285 sagt voraus, was danach herauskommt: sechs der zwölf pfadgestützten Instrumentenstände
bewegen sich in Runde 1, also **7 von 310** (`aufgaben/0285-…md:19-21`). **Das ist eine
Vorhersage, keine Messung**, und sie kommt zustande, indem Schritt 3 eine Null hineinschreibt,
die niemand befüllt — der Treiber für `pfadstand` gehört in `daten` und ist nicht gebaut.
Der Satz des Portfolio-Managers vom 2026-09-06 hält: „**Die Fabrik baut den Prüfapparat
einer Simulation, die noch nicht rechnet.**" Sie rechnet jetzt. Sie trifft nur weiterhin
null.
