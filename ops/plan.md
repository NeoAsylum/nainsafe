# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-04 07:45. Abgedeckt: 2026-09-03 23:55 bis 07:39 — der Nachtlauf seit dem
letzten Plan. Kein Betreiber-Commit seit 2026-09-03 19:08; der letzte Plan ist ungelesen.

## Wo das Vorhaben steht

**Der Prüfstau von gestern ist weg, und der Kern rechnet zum ersten Mal echt.** Aus 61
Paketen sind 77 geworden: 53 fertig, 13 offen, 5 gebaut, 2 Vorschläge, 3 blockiert; der
Projektmanager hat die vier hängenden Urteile nachgezogen. Der Übersetzungsbericht von
07:19 meldet 12 grüne Tests im Hauptmanifest und 8 im Kern — die stammen diesmal wirklich
aus dem Kern, anders als die elf von gestern. **Bezahlt ist das mit der ganzen Woche:**
1.306,7 von 1.600 $ verbraucht, und das ist zugleich die Summe der gesamten Bauphase.

## Der Engpass

**Drei Baurollen können ihr eigenes Paket nicht beenden — und eine davon hält das Tor zur
einen Zahl.**

`agents/rollen/architekt.md`, `spielentwerfer.md` und `testentwickler.md` enthalten den
Satz „Setze `status: gebaut`" nicht (nachgemessen: je 0 Treffer; `kernbauer` und
`datenbauer` je 1). Das ist der 8. Fall der vom Betreiber benannten Fehlerklasse,
unverändert seit dem letzten Plan. Neu ist, was er kostet.

**0026-klasse-2-preisbasis wurde heute Nacht dreimal zugewiesen** — 05:24, 06:20, 07:11,
jedes Mal `architekt`, jedes Mal ein Commit an `technik.md`. Der Architekt schreibt es
selbst in sein Logbuch: *„0026 wurde dreimal zugewiesen und war ab dem ersten Mal
geliefert"*. Der Runner sieht `offen` und plant erneut ein. Fair ist zu sagen, dass der
dritte Lauf nicht leer war — er hat nachgerechnet statt neu zu schreiben und dabei einen
echten Fehler gefunden. Bezahlt sind trotzdem drei Läufe (~22,60 $) für ein Paket.

**Warum ausgerechnet dieses:** `0002-fondsbewertung-definieren` hängt an 0008 (fertig) und
0026, sonst an nichts. 0026 ist geliefert. Zwischen dem Vorhaben und seiner einen Zahl
steht damit **ein fehlender Satz in einer Rollendatei**, sonst nichts.

## Was quer liegt

- **Die Fabrik schreibt inzwischen überwiegend über sich selbst.** 21 der 77 Pakete
  betreffen Belegstellen, Riegel und Formfehler in `technik.md` — **12 der letzten 21**,
  und **beide** Vorschläge (0076: `-NOTFOUND` in der Werkzeugkette; 0077: zwei
  Kommentarsätze, von denen 0044 einen selbst falsch gemacht hat). Prüfer finden
  Belegfehler in den Erzeugnissen von Prüfern. Das ist eine geschlossene Schleife, und sie
  frisst gerade den Rest der Woche.
- **Das Datengewerk ist leergelaufen — wie im letzten Plan vorhergesagt.** Von 13 offenen
  Paketen sind 6 `architekt`, 5 `kernbauer`, 2 `testentwickler`, **0 `datenbauer`**.
  `daten/roh/` gibt es nicht, `reihen.toml` (115 kB, 113 Einträge) sagt in Zeile 18 weiter
  über sich selbst „**Sie enthaelt keine Datenzeile**". Preis: 379,38 $ für `datenbauer`
  und `daten-pruefer` — **29 % der gesamten Bauphase** für Arbeit über Daten, die niemand
  geladen hat. Ich stelle die Frage nicht neu; der Beleg steht jetzt fest.
- **Die Sortierregel hungert dasselbe Paket zum zweiten Mal in zwölf Stunden aus.** 0027
  kam 05:53 zurück, wurde 06:26 neu gebaut und hat nun **zwei** Rückläufe; die vier
  Prüfplätze halten 0044, 0056, 0066 (je 0) und 0065 (1). `reviewbereit()`
  (`agents/baulauf.py:264`) sortiert Unbeprüfte nach vorn. Das ist kein Einzelfall mehr,
  sondern die Bauart der Regel.
- **Fünf Mitglieder des Bauwerks gibt es nicht.** `cmake -S` meldet `daten`,
  `schnittstelle`, `konsole`, `oberflaeche` und `werkzeuge/aufbereitung` als „noch nicht
  gebaut" — gebaut sind `kern`, `pruefstand` und `werkzeuge/belegstellen`. Von
  35 im Bericht gezählten Tests stammen 11 weiter aus `pruefstand/bau/pruefung-0019/`,
  einem unversionierten Verzeichnis. 0041, das genau das abstellen würde, steht auf
  `blockiert` und trägt `rolle: geschaeftsfuehrer` — eine Rolle, die nicht in `BAUROLLEN`
  steht und die keinen Code schreibt. Es wird nie eingeplant.

## Was der Betreiber entscheiden muss

**Wofür die letzten rund 44 Läufe der Woche ausgegeben werden.** Spielraum 293,3 $; die
letzten fünf Stunden kosteten 294,06 $ bei 44 Läufen. Bei diesem Tempo ist die Woche
**heute gegen 12:40 leer**, danach steht die Fabrik **69 Stunden** bis Montag 10:00.
Drosseln verlängert das nicht sinnvoll — 293,3 $ auf 69 Stunden wären 4 $ die Stunde, also
weniger als ein Lauf. Die Woche ist so oder so vorbei; zu entscheiden ist der Inhalt.

- **A — laufen lassen.** Nach der Zusammensetzung der Schlange geht rund die Hälfte der
  letzten Läufe in Belegstellen, Riegel und `technik.md`-Formfehler.
- **B — vor dem nächsten Lauf drei Zeilen ergänzen** („Setze `status: gebaut`" in
  `architekt.md`, `spielentwerfer.md`, `testentwickler.md`) und die Restwoche auf den
  Vorrang unten beschränken; 0076 und 0077 diese Woche nicht anlegen.

**Empfehlung B.** Die drei Zeilen kosten keinen Lauf und ändern die Ausbeute jedes
folgenden. Ohne sie wird 0026 ein viertes Mal zugewiesen, und die eine Zahl steht auch am
Montag noch. Anzumerken ist, dass die Empfehlung des letzten Plans nicht abgelehnt wurde —
sie ist ungelesen: seit 2026-09-03 19:08 gibt es keinen Betreiber-Commit.

## Vorrang

1. **0026** — nichts mehr zu bauen, nur abzuschließen. Danach ist 0002 startbereit. Das ist
   der kürzeste Weg zur einen Zahl, den es je gab.
2. **0002** — die eine Zahl selbst: `werte.hpp`, `werte.cpp`, `werte_probe.cpp`.
3. **0071** — ohne die Rundennummer im Zustand ändert eine Runde weiterhin nichts.
4. **0027** — zum zweiten Mal ausgehungert, zwei Rückläufe, schließt T18 ab. Es braucht
   einen Prüfplatz, den ihm die Sortierung von selbst nicht gibt.
5. **0010** — die Zustandsausgabe macht das Ergebnis von 0002 zum ersten Mal sichtbar.

Nichts aus der Belegstellen-Familie in dieser Woche.

## Die eine Zahl

**0 von 310.** Eine Runde im Modus `weltlauf` läuft heute durch, und danach hat sich keine
der 310 Größen des Zustands geändert — Bedingung 6 von 0033 verlangte ausdrücklich die
*unveränderte* Prüfsumme über eine Runde, und 0071 ist das Paket, das sie ersetzt. Die
benannte Ursache: **`werte.hpp` steht bei 78 Byte**, `werte.cpp` gibt es nicht — unverändert
seit dem 2026-09-02 03:15 und damit den vierten Plan in Folge.
