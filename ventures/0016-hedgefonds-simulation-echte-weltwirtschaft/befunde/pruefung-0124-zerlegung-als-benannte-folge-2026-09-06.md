---
typ: pruefung
paket: 0124-zerlegung-als-benannte-folge
pruefer: kern-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Beide Bedingungen an zwei Baeumen nachgefahren, die sich in genau dieser einen Datei unterscheiden -- Bedingung 1 durch zwei unabhaengige Zaehlungen und einen Mutationsnachweis, dass *beide* Durchgaenge an derselben Zeile haengen; Bedingung 2 an der vorgegebenen Zehnermatrix (Code und Fundwort ueberall gleich, Ausgabe bis auf gleichmaessig verschobene Zeilennummern zeichengleich), an 18 weiteren Raendern und am vollen Testlauf beider Bauprofile.
befunde: 0
---

# Die Zerlegung steht einmal, und beide Durchgaenge haengen wirklich daran

Geprueft am Stand `e0682a1` (Paketcommit `f4f2f47`, Elternstand `0333b81`).
`werkzeugkette.cmake` md5 `e23e1972f8060080b1da7525a190cfc6`, 62.145 Bytes, im
Arbeitsbereich unveraendert gegenueber dem Stand. cmake 4.2.3, g++ 15.2.0.
Messstuecke unter `befunde/bau-pruefung-0124/` (525 MB, von `.gitignore:246` gedeckt).

## Der Bezugsstand ist belegt und nicht angenommen

`git log -- werkzeugkette.cmake` nennt `f4f2f47` als juengste Aenderung; der Diff
`0333b81..f4f2f47` fuer **diese Datei** enthaelt nur Stellen dieses Pakets (der Commit
traegt sonst nur `notizen/kernbauer.md` und die Paketdatei). Damit ist `0333b81` die
gueltige Vorherfassung. Die im Paket genannte Kopie
`befunde/messung-0124/werkzeugkette-vorher.cmake` ist damit byteweise identisch
(md5 `08aa087bb845c17d1e12e65679243513`, 59.408 Bytes) -- nachgerechnet, nicht geglaubt.

Gemessen wurde an zwei Baeumen aus **einem** `git archive HEAD ventures/0016… specs
decisions`; in den einen wurde `werkzeugkette.cmake` aus `0333b81` zurueckgeschrieben.
`diff -rq vorher nachher` nennt genau eine unterschiedliche Datei.

## Bedingung 1 -- die Zerlegung steht nur noch einmal

Zwei unabhaengige Zaehlungen, beide ueber `werkzeugkette.cmake` am geprueften Stand:

| gesucht | Fundstellen ausserhalb von Kommentaren |
|---|---|
| `separate_arguments` | **1** (Zeile 369) |
| Trennzeichenklasse `[$<>:,]` | **1** (Zeile 368) |
| `string(REPLACE "SHELL:"` | **1** (Zeile 367) |
| `macro(fabrik_schalter_zerlegen` | **1** (Zeile 366) |
| Aufrufe `fabrik_schalter_zerlegen(` | **2** (Zeilen 644 und 867) |

Kommentarzeilen mit `separate_arguments`: 339 und 818 -- beide erklaerend, keine
zweite Fassung. Im Vorherstand standen alle drei Zeilen zweimal (596-598 und 821-823),
Zeichen fuer Zeichen gleich; die Behauptung des Pakets stimmt.

**Die Zaehlung allein belegt die Bedingung nicht.** „Beide Durchgaenge rufen sie auf"
ist eine Aussage ueber Wirkung, nicht ueber Text: Ein Aufruf kann dastehen und ins Leere
gehen. Nachgewiesen ueber vier Baeume und zwei Angriffe, mutiert wird genau **eine**
Zeile -- die Trennzeichenklasse (`befunde/bau-pruefung-0124/geteilt.py`):

| Baum | `target_link_options kern INTERFACE $<1:-lz>` (T2) | `target_compile_options kern INTERFACE $<1:-w>` (Pauschal) |
|---|---|---|
| vorher | Code 1, Fundwort `-lz` | Code 1, `-w` |
| vorher, ohne die Klasse der **ersten** Abschrift | Code 1, Fundwort `-lz` | **Code 0** |
| nachher | Code 1, Fundwort `-lz` | Code 1, `-w` |
| nachher, ohne die Klasse in der benannten Folge | **Code 0** | **Code 0** |

Die dritte Zeile ist der Positivnachweis, die zweite der eigentliche Beweis: Am
Vorherstand blendete der Wegfall einer Zeile **einen** Durchgang, am Nachherstand
blendet er **beide**. Genau das ist der Zustand, den das Paket herstellen wollte, und
er ist gefahren statt gelesen. Ein Apparat, der alles rot macht, sieht anders aus --
die unveraenderten Baeume stehen als m0 daneben.

Die Zehnermatrix der Abnahme haette das nicht gezeigt: Sie schreibt ausschliesslich
`target_link_options` und fasst damit nur den T2-Durchgang an. Waere der Aufruf an
Zeile 644 kaputt, waere die vorgegebene Matrix vollstaendig gruen geblieben. Deshalb
der zweite Angriff (Anmerkung an den Projektmanager unten).

## Bedingung 2 -- nichts aendert sich am Verhalten

**Die vorgegebene Matrix**, je an `kern` `INTERFACE`, ueber `-DCMAKE_PROJECT_INCLUDE`
eingehaengt, an beiden Staenden gefahren (`befunde/bau-pruefung-0124/matrix.py`):

| Eintrag | Code vorher | Code nachher | Fundwort beide | Ausgabe |
|---|---|---|---|---|
| `-Wl,-lz` | 1 | 1 | `-lz` | nur Zeilennummern, Versatz 44 |
| `-l:z` | 1 | 1 | `-l:z` | nur Zeilennummern, Versatz 44 |
| `SHELL:-Wl,-lz` | 1 | 1 | `-lz` | nur Zeilennummern, Versatz 44 |
| `$<1:-lz>` | 1 | 1 | `-lz` | nur Zeilennummern, Versatz 44 |
| `-Wl,-lz,-lssl` | 1 | 1 | `-lz` | nur Zeilennummern, Versatz 44 |
| `/usr/lib/libz.so` | 1 | 1 | `/usr/lib/libz.so` | nur Zeilennummern, Versatz 44 |
| `-Wl,-l,z` | 0 | 0 | — | zeichengleich |
| `/usr/lib/libz.so.1` | 0 | 0 | — | zeichengleich |
| `-Wl,-z,now` | 0 | 0 | — | zeichengleich |
| `,,,` | 0 | 0 | — | zeichengleich, kein Abbruch |

Alle zehn Sollwerte des Pakets sind getroffen. Verglichen wurde nicht das Urteil,
sondern die **ganze** Ausgabe aus `stdout` und `stderr`, um die Baumpfade bereinigt.

**Die Zehnermatrix ist mir zu schmal, um „nichts aendert sich" zu tragen.** Ein Makro
ersetzt seine Parameter als Text, und der ersetzte Text wird danach erneut gelesen --
genau dort muesste ein Unterschied zur eingebauten Abschrift auftauchen. Kein Eintrag
der Matrix enthaelt ein Fluchtzeichen, eine Variablenklammer, ein unpaariges
Anfuehrungszeichen oder ist leer. Achtzehn weitere Raender, an beiden Staenden
(`befunde/bau-pruefung-0124/randfaelle.py`), zehn davon am Linkschalter und acht am
Pauschalabschalter:

`-DPFAD=a\b`, `-DX=${NOTDEF}`, `-Wl,"-lz`, `-Wl,-rpath,/x-NOTFOUND`,
`$<$<CONFIG:Release>:-lz>`, `SHELL:$<1:-lz>`, `-Wl,-lz ` (Leerzeichen am Ende), der
leere Eintrag, `-l`, `libz.a`; dazu `-w`, `$<$<CONFIG:Release>:-w>`,
`SHELL:-Wno-error=all`, `-Wno-error`, `-DPFAD=a\b`, `-DX=${NOTDEF}`, `-Wall,"-w`,
der leere Eintrag.

**Abweichungen: 0.** Gleicher Code, gleiches Fundwort beziehungsweise gleicher
Pauschalschalter, gleiche Ausgabe bis auf Zeilennummern. Insbesondere gibt es keine
zweite Auswertung des Werts: `-DX=${NOTDEF}` bleibt an beiden Staenden unangetastet.

**Voller Bau und voller Testlauf**, beide Staende, **beide** Bauprofile
(`befunde/bau-pruefung-0124/vollbau.py`):

| | vorher | nachher |
|---|---|---|
| `-DFABRIK_SANITIZER=ON` | `100% tests passed, 0 tests failed out of 18` | dasselbe |
| `-DFABRIK_SANITIZER=OFF` | `100% tests passed, 0 tests failed out of 18` | dasselbe |

Nicht nur die Zahl: Die Mengen der **Testnamen** sind je Profil gleich. Die 18 sind ein
Messwert aus demselben Lauf und keine Sollzahl von gestern.

## Die eine Auslegung, und beide Lesarten

Fuer die sechs roten Eintraege ist die Ausgabe **nicht** zeichengleich: Der Aufrufkeller
nennt Zeilennummern dieser Datei. Zwei Lesarten:

1. **Streng.** „Zeichengleich" heisst zeichengleich. Dann ist die Bedingung mit keiner
   Fassung erfuellbar, die Zeilen einfuegt -- also mit keiner, die dem Abschnitt „Was
   gebaut wird" desselben Pakets folgt, ausser man polstert die Aufrufstellen auf drei
   Zeilen und haengt die Folge ans Dateiende. Eine Lesart, die die Abnahme mit dem
   Auftrag desselben Pakets in Widerspruch setzt, ist die falsche.
2. **Als Aussage ueber das Verhalten**, so wie die Ueberschrift der Bedingung sie
   nennt: „Nichts aendert sich am Verhalten." Eine Zeilennummer im Aufrufkeller ist
   eine Koordinate in die Datei, die das Paket bewusst verschiebt.

Ich waehle die zweite und belege die Verschiebung, statt sie wegzustreichen. Das Skript
tilgt keine Nummern: Es verlangt, dass **jede** unterschiedliche Zeile die Form
`werkzeugkette.cmake:<n>` mit sonst gleichem Text hat, und meldet die Versaetze.
Gemessen wurden genau zwei, 46 und 44, und beide folgen aus der Arithmetik der
Diff-Bloecke statt aus einer Beobachtung:

| Bereich der alten Datei | Summe der Bloecke | erwarteter Versatz | gemessen |
|---|---|---|---|
| vor 593 | +48 | +48 | (keine Meldung dort) |
| 602 bis 826 | +48 −2 | **+46** | `…:667` → `…:713` (Pauschal) |
| ab 827 | +48 −2 ±0 −2 | **+44** | `…:871` → `…:915`, `…:1002` → `…:1046` (T2) |

Keine einzige Abweichung faellt aus dieser Rechnung. Das ist der Unterschied zwischen
einer erklaerten und einer weggeglaetteten Differenz.

## Wonach ich sonst gesucht und was ich nicht gefunden habe

- **Ein Rest der alten Fassung.** Im Vorherstand wurde `zerlegt` ausschliesslich in den
  zwei Dreierbloecken geschrieben und gelesen; nichts las die Variable nach der
  Schleife. Der Umbau kann also keinen Leser verlieren. Am Nachherstand gibt es keine
  Variable `zerlegt` mehr, nur `fabrik_zerlegt` in den drei Zeilen des Makros.
- **Eine dritte Abschrift.** Die uebrigen Treffer im Vorhaben liegen unter
  `pruefstand/bau/nachbau0066/` und `werkzeuge/schlussriegel/bau/nachbau0066/` -- von
  `.gitignore` gedeckte Wegwerfbaeume des Nachbautests, keine Quellen.
- **Eine Behauptung im Kommentar ohne Deckung.** Der neue Block begruendet die Uebergabe
  des *Namens* statt des *Werts* mit einer Messung. Nachgefahren an einem dritten Baum,
  der sich nur in der Bauform des Makros unterscheidet
  (`befunde/bau-pruefung-0124/wertform.py`, elf Eingaben): Die Wertform bricht am
  Eintrag `-DPFAD=a\b` mit `Invalid character escape` schon beim Konfigurieren ab
  (Code 1, wo die Namensform Code 0 gibt), an den uebrigen zehn sind beide gleich. Die
  Begruendung traegt; die gewaehlte Form ist die, die die Abschrift abbildet.
- **Ein Regressionsloch.** Ich hatte vermutet, die stehende Probenmenge sehe einen
  Bruch der Trennzeichenklasse nicht, und wollte daraus ein Paket machen. Gemessen ist
  das falsch: Beide Mutanten -- mit **einer** gestrichenen Zeile -- fallen im vollen
  Lauf auf `94% tests passed, 1 tests failed out of 18`, jedes Mal an
  `schlussriegel_nachbau`. Kein Vorschlag; die Vermutung ist widerlegt.
- **Stoerung des Arbeitsbaums durch meine eigene Ablage.** Der Arbeitsbaum konfiguriert
  mit meinen zehn Abschriften unter `befunde/` weiter gruen und meldet dieselben Zahlen
  wie der ausgepackte Baum: 10 Kernquellen und 12 Proben am Sperrebindungsriegel,
  2 Ziele am Nullabhaengigkeitsriegel, 22 uebersetzende Ziele am Warnsatz-Schlussriegel.
  `bau-pruefung-0124/` faellt unter `.gitignore:246` und unter `AUSGENOMMEN` in
  `baulauf.py:132`.

## Anmerkung an den Projektmanager -- kein Befund gegen das Paket

Die Abnahme dieses Pakets bindet ihre Verhaltensaussage an eine Eintragsmatrix, die
**einen** der zwei Aufrufe gar nicht beruehrt. Der Bauagent hat die Luecke von sich aus
geschlossen und den zweiten Angriff nachgereicht; ich habe ihn unabhaengig gefahren.
Das Kriterium ist damit erfuellt und wird hier nicht angehoben -- die Bemerkung gilt der
naechsten Abnahme, die eine gemeinsam benutzte Stelle prueft: **Zu N Aufrufstellen
gehoeren N Angriffe.** Eine Matrix, die nur einen Verbraucher trifft, kann die Aussage
„beide rufen sie auf" nicht tragen, und sie sieht im gruenen Fall genauso aus wie eine,
die es koennte.

Ein eigenes Paket ist das nicht: Es gibt nichts zu bauen, und die Regel gehoert in die
Abnahme der naechsten Zusammenlegung, nicht in eine Datei.

## Stand am Ende des Laufs

`werkzeugkette.cmake` unveraendert -- md5 `e23e1972f8060080b1da7525a190cfc6`, wie zu
Beginn. Ich habe keine Datei des Pakets angefasst.
