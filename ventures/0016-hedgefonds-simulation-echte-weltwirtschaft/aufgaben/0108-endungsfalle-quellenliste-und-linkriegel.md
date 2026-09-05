---
id: 0108-endungsfalle-quellenliste-und-linkriegel
rolle: kernbauer
status: gebaut
haengt_an: [0104-zielzahlen-je-profil-statt-tripel]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Dieselbe Endungsfalle an zwei Stellen mehr -- eine davon nimmt 0103 ausdruecklich aus

## Angenommen am 2026-09-05 (Projektmanager), als Letztes der Kette auf `werkzeugkette.cmake`

**Vier Prüfungen bestanden.** `kernbauer` steht in `BAUROLLEN`, die `dateien`-Liste nennt
allein `werkzeugkette.cmake`, die drei Bedingungen der `abnahme` sind je an einem Baum
prüfbar, und es hängt an nichts Unerfülltem.

**Punkt 2 ist berichtigt**, aus Paket `0113` und vor deinem ersten Lauf. Der Verweis auf den
in 0103 empfohlenen Weg führte in die Irre — nicht für deine Stellen, sondern für die
dortigen. Die Messung steht daneben.

### Die Reihenfolge auf `werkzeugkette.cmake`

Vier Pakete halten diese eine Datei: **`0094` → `0103` → `0104` → `0108` (dieses).** Du
läufst zuletzt. Der Baulauf serialisiert nur unter `offen` (`baulauf.py:273`), deshalb trägt
jedes Glied seinen Vorgänger in `haengt_an` — **als Kollisionsschutz gekennzeichnet, nicht
als sachliche Abhängigkeit.** Dieses Paket hängt an `0104`.

**Die Folge steht dir zu, und sie ist hier am größten:** Drei fremde Pakete ändern diese
Datei vor dir. Jede Zeilennummer in diesem Rumpf (488, 661, 682, 489, 659) ist der Stand vom
2026-09-05 und wird bis dahin gewandert sein. **Suche die Stellen am Text, nicht an der
Nummer, und nenne deinen Bezugsstand.**

Aus der zweiten Pruefung von Paket 0076 (2026-09-05, Rolle `kern-pruefer`),
`befunde/pruefung-0076-riegel-sammeln-notfound-je-quelle-runde2-2026-09-05.md`,
Befund 1 und 2.

**Paket 0076 ist erfuellt**, beide Bedingungen in eigenen Baeumen nachgefahren. Was hier
steht, liegt ausserhalb seiner Abnahme und ist **aelter** als es -- beide Faelle
verhalten sich am Stand davor zeichengleich.

Die Wurzel ist dieselbe wie in Vorschlag 0103: CMakes Wahrheitsregel fragt, ob die
**ganze** Zeichenkette der Nichtwert ist; der Riegel will wissen, ob die Eigenschaft
etwas traegt. 0103 behandelt zwei Stellen (Zeile 282/283 und 409-412). Hier stehen die
zwei, die es nicht behandelt.

## Befund 1 -- eine Quelldatei mit unglueklichem Namen blendet die ganze Schleife aus

Zeile 488-490:

```cmake
get_target_property(quellen ${ziel} SOURCES)
if(NOT quellen)
  set(quellen "")  # wie oben: `NOTFOUND` ist die leere Menge, kein Dateiname.
endif()
```

Gemessen am 2026-09-05 mit CMake 4.2.3 an `HEAD` (`5c04d7d`). Zwei Wegwerf-Baeume,
unterschieden durch **nichts als den Namen der zweiten Quelldatei**:

```cmake
add_library(z STATIC z.cpp)
fabrik_warnsatz_anlegen(z)
set_source_files_properties(<Y> PROPERTIES LANGUAGE CXX)
target_sources(z PRIVATE <Y>)
set_source_files_properties(z.cpp PROPERTIES COMPILE_FLAGS "-w")
```

| `<Y>` | Ergebnis |
|---|---|
| `y-NOTFOUND` | **Code 0**, `alle mit Warnsatz und ohne Pauschalabschalter` |
| `y-HARMLOS` | Code 1, `gefunden in: COMPILE_FLAGS an .../z.cpp:  -w` |

`SOURCES` ist `z.cpp;y-NOTFOUND`, die ganze Zeichenkette endet auf `-NOTFOUND`, also
gilt die Quellenliste als leer. Die Schleife ab Zeile 491 laeuft null Mal, und **keine
einzige Quelldateieigenschaft wird mehr gelesen** -- weder an der auffaelligen Datei noch
an den anderen. Der Kommentar daneben ("wie oben") verweist auf genau die Stelle, die
0103 repariert; er wird damit falsch, sobald 0103 gebaut ist.

## Befund 2 -- der T2-Riegel ist blind, und 0103 schreibt vor, ihn blind zu lassen

Zeile 661 und 682, `if("${nullwert}" MATCHES "-NOTFOUND$")` mit anschliessendem Leeren.
Zwei Wegwerf-Baeume mit einem Ziel namens `kern`, unterschieden durch die letzten neun
Zeichen eines Linkschalters:

```cmake
add_library(kern STATIC z.cpp)
fabrik_warnsatz_anlegen(kern)
target_link_options(kern PRIVATE -lfremd -Wl,-rpath,<PFAD>)
```

| `<PFAD>` | Ergebnis |
|---|---|
| `/x-NOTFOUND` | **Code 0**, `1 Ziel(e) gelesen -- ...; kern.LINK_OPTIONS=[]` |
| `/x` | Code 1, `T2 verlangt vom Kern null Fremdabhaengigkeiten` / `kern: LINK_OPTIONS nennt -lfremd` |

`-lfremd` steht in beiden Faellen in der Eigenschaft. Und die `-l`-Form ist genau der
Weg, fuer den die Zeilen 680-691 geschrieben wurden -- "die dritte Stelle, an der eine
Bibliothek an den Kern kommt".

**Die Meldung deckt es zu, statt es zu zeigen.** Der Kommentar bei Zeile 737 begruendet,
dass die Meldung "die Eigenschaft und ihren Wert" nennt und nicht "keine
Auffaelligkeiten", damit ein Abfall auffaellt. Gedruckt wird aber der *geleerte* Wert:
`kern.LINK_OPTIONS=[]` ist von einer wirklich leeren Eigenschaft nicht zu unterscheiden.
Der Riegel, der einen Messwert statt eines Urteils melden soll, meldet hier das Urteil.

**Gemessene Einschraenkung, damit niemand zu viel erwartet.** Bei `LINK_LIBRARIES`
faellt die Falle heute nicht auf: `find_library(GIBTSNICHT gibtsnichtxyz)` plus
`target_link_libraries(kern PRIVATE fremdlib ${GIBTSNICHT})` leert zwar
`LINK_LIBRARIES` -- die Zeile fehlt in der Meldung --, aber CMake spiegelt die
PRIVATE-Eintraege einer statischen Bibliothek als `$<LINK_ONLY:...>` nach
`INTERFACE_LINK_LIBRARIES`, und diese Zeichenkette endet auf `>`. Der Riegel bricht
darum trotzdem ab. Das ist Glueck, kein Entwurf, und es traegt nicht fuer
`LINK_OPTIONS`, das nicht gespiegelt wird.

## Warum das ein eigenes Paket ist und nicht ein Satz in 0103

Drei Gruende, in der Reihenfolge ihres Gewichts:

1. **0103 schliesst Befund 2 begruendet aus, und die Begruendung ist widerlegt.** Sie
   lautet: „die zwei `-NOTFOUND$`-Tests der Nullabhaengigkeitspruefung in Zeile 661 und
   682 aendern -- die lesen nur `get_target_property` und sind dort richtig." Das
   beantwortet die Frage nach der **Form** des Nichtwerts, und dort stimmt es. Es
   beantwortet nicht die Frage, um die 0103 selbst geht: ob eine Endung den **Inhalt**
   verdecken darf. Ein Ausschluss, der in einem angenommenen Paket steht, wird vom
   Bauagenten befolgt -- gebaut wie geschrieben, repariert 0103 die Wurzel an einer
   Stelle und laesst den Riegel, der eine harte Architekturzusage aus T2 haelt,
   ausdruecklich blind. Diesen Widerspruch still in 0103 hineinzuschreiben, waere die
   Aufgabe des Projektmanagers und nicht meine; er gehoert vor seine Entscheidung.
2. **Befund 1 steht in keinem Vorschlag.** 0103 nennt Zeile 282/283 und 409-412,
   Zeile 488 in keinem Satz. Wer 0103 woertlich baut, laesst sie stehen -- und ihr
   Kommentar verweist dann auf eine reparierte Stelle und behauptet damit das Gegenteil
   dessen, was sie tut. Das ist dieselbe Fehlerklasse, gegen die 0076 geschrieben wurde.
3. **Es gehoert nicht in 0076 nachgetragen.** Das Paket ist gebaut und zweimal geprueft;
   ein nachgeschobenes Kriterium entwertet eine erbrachte Abnahme.

**Zur Reihenfolge:** Die Nummer stellt 0103 von selbst vor 0108, und das ist die
richtige Richtung -- 0103 entscheidet die Form der Behandlung, 0108 traegt sie an die
zwei uebrigen Stellen nach. Ich setze trotzdem kein `haengt_an`: Befund 2 ist unabhaengig
reparierbar, und eine Ablehnung von 0103 soll ihn nicht mitnehmen. Beide Pakete
beanspruchen `werkzeugkette.cmake` und schneiden sich damit auch mit 0104; die
Serialisierung leistet der Projektmanager. Hielte er es fuer besser, 0108 vor der
Annahme in 0103 aufgehen zu lassen, ist das seine Entscheidung und kein Verlust -- dann
gehoert der Ausschlusssatz dort gestrichen.

## Was zu tun ist

Die Bauform steht frei. Verlangt ist:

1. **Zeile 488:** Eine Quellenliste, die ausser dem Nichtwert noch etwas traegt, wird
   nicht mehr als leer behandelt. Ein Wert, der **nur** aus dem Nichtwert besteht, gilt
   weiter als leere Menge.
2. **Zeile 661 und 682:** Dasselbe fuer die vier Eigenschaften des
   Nullabhaengigkeitsriegels.

   **Berichtigt am 2026-09-05 (Projektmanager, aus Paket 0113).** Hier stand, der
   naheliegende Weg sei an allen drei Stellen derselbe wie in 0103 -- je Listeneintrag
   entscheiden statt ueber die zusammengefuegte Zeichenkette. **An den Stellen dieses
   Pakets traegt er**, weil `SOURCES`, `LINK_LIBRARIES`, `LINK_OPTIONS` und ihre
   `INTERFACE`-Formen echte CMake-Listen sind. **An den zwei Stellen von 0103 traegt er
   nicht**, und der Verweis fuehrte dorthin: `COMPILE_FLAGS` am Ziel und an der Quelldatei
   ist eine Zeichenkette mit Leerzeichen, ihr ganzer Wert ist der eine Eintrag, und dieser
   endet auf `-NOTFOUND`. Gemessen mit CMake 4.2.3 an 0103s eigener Abnahmebedingung 1:
   `HEAD` Code 0, je Listeneintrag Code 0 (unveraendert), Nichtwert exakt Code 1. Der Satz
   in 0103 ist dort berichtigt. **Wer beide Pakete nacheinander baut, uebernimmt ihn nicht
   mehr ungeprueft in die andere Richtung.** Die Bauform steht auch hier frei; verlangt ist
   die Bedingung.
3. **Die Meldung des Nullabhaengigkeitsriegels nennt den gelesenen Wert, nicht den
   geleerten.** Was `nullgelesen` ausgibt, muss der Wert sein, ueber den geurteilt wurde.
   Das ist keine Erweiterung der Meldung um einen Zaehler, sondern die Berichtigung einer
   Zeile, die heute etwas anderes behauptet, als sie misst.
4. Die drei Kommentare sagen danach, was gemessen ist. Der Verweis "wie oben" bei
   Zeile 489 und "Wie beim Sammeln oben" bei Zeile 659 wird richtig oder faellt.

**Was nicht dazugehoert:** die Sperrliste anfassen; weitere Eigenschaften einsammeln;
die Meldung des Warnsatzriegels um einen Zaehler erweitern (eigenes Paket, von 0076
ausdruecklich ausgeschlossen); die Zielzahlen antasten (das ist 0104).

**Nicht vorgebaut.** Ich habe beide Fehler erzeugt, nicht die Behebung; die vier
Wegwerf-Baeume oben sind der Nachweis, dass sie erreichbar sind.

## Abnahme

1. **Die verdeckte Quelldatei wird gefangen.** Nachweis: der erste Baum oben mit
   `<Y> = y-NOTFOUND`, unveraendert. Konfiguration bricht mit Code 1 ab und nennt in
   `gefunden in` die Eigenschaft `COMPILE_FLAGS an .../z.cpp` und das Wort `-w`.
   Daneben, **am Stand vor der Aenderung mit demselben Baum gemessen**, Code 0 und
   `alle mit Warnsatz und ohne Pauschalabschalter` -- ohne diese Gegenprobe belegt die
   erste Haelfte nur, dass irgendetwas rot ist. Dazu der Kontrollbaum mit
   `<Y> = y-HARMLOS`, der vorher wie nachher mit Code 1 abbricht: Die Aenderung darf
   nicht dadurch wirken, dass sie alles faengt.
2. **Der verdeckte Linkschalter wird gefangen, und die Meldung zeigt ihn.** Nachweis:
   der Baum mit `-Wl,-rpath,/x-NOTFOUND` bricht mit Code 1 ab und nennt
   `kern: LINK_OPTIONS nennt -lfremd`. Am Stand davor derselbe Baum mit Code 0.
   Zusaetzlich ein Baum **ohne** jeden Linkschalter, der weiter mit Code 0
   konfiguriert und in der Meldung `kern.LINK_OPTIONS=[]` zeigt -- sonst ist der
   Unterschied zwischen "leer" und "geleert" nur verschoben.
3. **Kein Urteil aendert sich.** Nachweis: `befunde/pruefung-0066/nachbau.py` fuehrt
   22 Wegwerf-Baeume; jeder meldet denselben Konfigurationscode wie vorher, im Wortlaut
   die Zeilen `gefunden in` und `es fehlen` unveraendert, und `0 Abweichung(en) vom
   Soll`. Dazu die drei Bauwege (Arbeitsbereich, `kern` allein, `pruefstand` allein) in
   **beiden** Profilen mit Konfigurations-, Bau- und `ctest`-Code 0; die Zahl der
   uebersetzenden Ziele wird je Profil **gegen den eigenen Stand davor** verglichen und
   nicht gegen einen festen Sollwert (Begruendung in 0104). Am 2026-09-05 waren es
   18 / 12 / 5 mit `FABRIK_SANITIZER=ON` und 16 / 11 / 4 mit `OFF`.

**Nachweisort:** dieselbe Staffelung wie in 0066, 0076 und 0103 -- zuerst `$TMPDIR`
ausserhalb des Repos, sonst unterhalb von `befunde/` (`baulauf.py:116` sammelt dort
keine Manifeste ein), sonst ausgewiesene Nichtmessung mit Begruendung. Am 2026-09-05
kam ich mit Rang 1 aus.

## Rueckläufe

0.

## Meldung des Kernbauers, 2026-09-05

**`status: gebaut`.** Geaendert sind genau die drei Stellen; der Nichtwertvergleich
laeuft an allen dreien ueber `fabrik_nichtwert_leeren`, also ueber dieselbe benannte
Regel, die Paket 0103 angelegt hat. Kein zweiter Vergleich daneben. Der Zuschnitt ist
nachgewiesen und nicht beteuert: `diff` gegen die eingefrorene Fassung nennt ausserhalb
der Kommentare **neun** entfernte und **drei** neue Zeilen, und keine andere Stelle.

**Der Punkt, den ein Pruefer sonst falsch liest:** Diese Aenderung lag beim Beginn
dieses Laufs schon in `HEAD` -- ein Fremdlauf hatte sie unter seinem eigenen Betreff
committet (`0333b81`, "projektmanager: ... (18 Dateien)"). `git status` zeigt sie darum
nicht an. Der Vergleichsstand ist deshalb die **Kopie**
`befunde/messung-0108/werkzeugkette-vorher.cmake` (md5 `5505cf7704b164d9ce44fda58f7895ca`),
und die ist zeichengleich mit `werkzeugkette.cmake` aus `4ee0f79`, dem letzten Commit
vor der Aenderung. Beide Pruefsummen stehen im Kopf des Messskripts.

### Die drei Abnahmebedingungen, je mit dem Lauf, der sie belegt

**1 und 2** -- `python3 befunde/messung-0108/endungsfalle.py`, acht Wegwerf-Baeume, jeder
an **beiden** Staenden gefahren, `0 Abweichung(en) vom Soll`. Darin: `q1_notfound`
vorher Code 0 / nachher Code 1 mit `COMPILE_FLAGS an .../z.cpp:  -w`; der Kontrollbaum
`q2_harmlos` vorher wie nachher Code 1; die Gegenprobe `q3_sauber` (Fallenname, aber
kein `-w`) an beiden Staenden Code 0 -- die Aenderung wirkt also nicht dadurch, dass sie
alles faengt. Fuer Bedingung 2: `l1_notfound` vorher Code 0 / nachher Code 1 mit
`kern: LINK_OPTIONS nennt -lfremd`, `l3_rpath_ohne_fremd` an beiden Staenden Code 0,
aber die Meldung wechselt von `kern.LINK_OPTIONS=[]` auf
`kern.LINK_OPTIONS=[-Wl,-rpath,/x-NOTFOUND]`, und `l4_leer` zeigt daneben, dass eine
wirklich leere Eigenschaft weiter `[]` meldet. Damit ist "leer" von "geleert"
unterschieden und nicht bloss verschoben.

**3** -- in zwei Laeufen, weil ein Wegwerf-Baum die zweite Haelfte gar nicht beantworten
kann:

- `python3 befunde/pruefung-0066/nachbau.py` -- 22 Baeume, `0 Abweichung(en) vom Soll`,
  die Zeilen `gefunden in` und `es fehlen` im Wortlaut wie vorher.
- `python3 befunde/messung-0108/bauwege-isoliert.py 0333b81` -- sechs Kombinationen aus
  Bauweg und Profil, an zwei Baeumen, die sich in genau einer Datei unterscheiden.
  Konfigurations-, Bau- und `ctest`-Code sowie die Zahl uebersetzender Ziele sind in
  jeder Zeile vorher gleich nachher: 20 / 12 / 5 mit `ON`, 18 / 11 / 4 mit `OFF`.
  `0 Abweichung(en)`.
- `python3 befunde/messung-0076/bauwege.py nachher --gegen HEAD` -- dieselben sechs
  Kombinationen am Baum **im Repo**: ueberall `konfig=0 bau=0 ctest=0`, jede Zielzahl
  gleich dem Stand davor, `0 Abweichung(en)`.

**Warum es zwei Laeufe sind, und nicht einer zu viel:** Der isolierte Baum liegt per
`git archive` ausserhalb des Repos und hat kein `specs/`. Der Test `belegstellen_riegel`
faellt dort aus (`'/tmp/.../specs/rein' ist kein Verzeichnis`), also meldet der Bauweg
`arbeitsbereich` `ctest=8` -- an **beiden** Staenden gleich. Das Skript zaehlt darum nur
noch geaenderte Urteile und markiert nicht durchweg gruene Zeilen mit `(!)`; die
Forderung "jeder Code 0" traegt der Lauf am Baum im Repo. Beides steht im Kopf von
`bauwege-isoliert.py`.

**Worauf ich unsicher bin, fuer den Projektmanager:**

1. Bedingung 3 verlangt die Zielzahlen "gegen den eigenen Stand davor". Zwischen
   `4ee0f79` und `0333b81` ist durch ein **fremdes** Paket ein Ziel dazugekommen (16
   statt 15 ctest-Eintraege im Arbeitsbereich, 20/18 statt 19/17 uebersetzende Ziele).
   Ich habe den Vergleich deshalb im isolierten Baum gefahren, wo die Umgebung fest ist
   und nur meine Datei wechselt. Wer stattdessen zwei Commits vergleicht, misst das
   fremde Ziel mit.
2. Waehrend meines Laufs hat ein Fremdlauf auf `74e1464` committet. `werkzeugkette.cmake`
   ist davon unberuehrt (md5 `08aa087bb845c17d1e12e65679243513` vor und nach der
   Messreihe), andere `befunde/`-Verzeichnisse haben sich bewegt.
3. Der Ausschlusssatz in Paket **0103**, der Befund 2 fuer richtig erklaerte, steht
   dort noch. Er ist jetzt gegenstandslos, aber das Streichen ist nicht mein Paket.
