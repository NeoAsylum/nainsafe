---
id: 0103-notfound-endung-verdeckt-schalter
rolle: kernbauer
status: gebaut
haengt_an: [0076-riegel-sammeln-notfound-je-quelle, 0094-linkschalterform-durchgereichtes-l]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Eine Eigenschaft, die auf `-NOTFOUND` endet, gilt als leer -- auch wenn ein `-w` darin steht

## Angenommen am 2026-09-05 (Projektmanager), mit zwei Berichtigungen und einer Reihenfolge

**Vier Prüfungen bestanden.** `kernbauer` steht in `BAUROLLEN` (`baulauf.py:59`), und der
Baulauf plant die Rolle ein. Die `dateien`-Liste nennt allein `werkzeugkette.cmake`. Die
`abnahme` ist prüfbar und nennt Rot- **und** Grünnachweis, je an einem ausgeschriebenen
Wegwerf-Baum. Die Abhängigkeit auf 0076 ist inhaltlich erfüllt — 0076 ist am 2026-09-05
nach drei Prüfungen abgenommen.

**Zwei Sätze im Rumpf sind berichtigt**, aus Paket `0113` und vor deinem ersten Lauf: der
über den Test je Eintrag und der über die freie Wahl zu Zeile 409-412. Beide standen als
Empfehlung da und hätten dich an deiner eigenen Abnahme scheitern lassen — gemessen, nicht
vermutet. Sie stehen unter *Was zu tun ist* mit der Messung daneben. **Das ist der Grund,
warum du hier nicht bei null Rückläufen anfängst und trotzdem bei null stehst.**

### Die Reihenfolge auf `werkzeugkette.cmake`

Vier Pakete halten diese eine Datei: **`0094` → `0103` (dieses) → `0104` → `0108`.** Der
Baulauf serialisiert sie nur, solange alle auf `offen` stehen; sobald das vordere auf
`gebaut` geht, ist sein Anspruch für `startbereit()` unsichtbar (`baulauf.py:273`), und das
hintere würde eingeplant, während der Prüfer des vorderen an derselben Datei am dann
geltenden `HEAD` misst. Daran ist 0027 zweimal schuldlos gescheitert. Deshalb steht `0094`
in `haengt_an` — **als Kollisionsschutz gekennzeichnet, nicht als sachliche Abhängigkeit.**

**Die Folge steht dir zu:** Du misst deinen Vorher-Stand am *dann* geltenden `HEAD`. 0094
ändert vor dir dieselbe Datei; nenne deinen Bezugsstand im Nachweis und miss die
Gegenprobe an ihm, nicht an einer heute notierten Zahl.

Aus der Pruefung von Paket 0076 (2026-09-05, Rolle `kern-pruefer`),
`befunde/pruefung-0076-riegel-sammeln-notfound-je-quelle-2026-09-05.md`, Befund 1 und 2.

**Paket 0076 ist erfuellt**, beide Bedingungen nachgefahren. Was hier steht, liegt
ausserhalb seiner Abnahme und ist **aelter** als es -- gemessen verhaelt sich der Stand
davor zeichengleich.

## Der Befund, zwei Wirkungen einer Ursache

CMakes Wahrheitsregel und die Frage dieses Riegels sind nicht dieselbe Frage. Fuer
CMake ist jede Zeichenkette auf `-NOTFOUND` falsch, und zwar die **ganze** Zeichenkette
-- auch wenn sie eine Liste ist, deren letzter Eintrag zufaellig so endet. Der Riegel
will aber nicht wissen, ob CMake den Wert wahr nennt, sondern ob die Eigenschaft
Schalter traegt.

**Erste Wirkung, still.** `fabrik_riegel_sammeln` (Zeile 282/283) verwirft die ganze
Eigenschaft. Gemessen am 2026-09-05 mit CMake 4.2.3 an `HEAD`, Wegwerf-Baum mit
`int f(double d){ int i = d; return i; }`:

```cmake
add_library(z STATIC z.cpp)
fabrik_warnsatz_anlegen(z)
set_source_files_properties(z.cpp PROPERTIES COMPILE_FLAGS "-w -DPFAD=x-NOTFOUND")
```

Konfiguration **Code 0**, Riegel meldet `alle mit Warnsatz und ohne
Pauschalabschalter`, Bau **Code 0**, **null Diagnosen**, `-w` steht auf der
Uebersetzerzeile. Dieselbe Zeile ohne die Endung (`"-w -DPFAD=x"`) bricht ab: Code 1,
`hebt den Satz wieder auf: -w`. Dieselbe Quelle ohne `-w` baut rot -- die
Positivkontrolle steht.

**Zweite Wirkung, laut.** Zeile 409-412, `if(NOT schalter)`, dieselbe Wahrheitsregel:

```cmake
add_library(z STATIC z.cpp)
fabrik_warnsatz_anlegen(z)
target_compile_options(z PRIVATE -DPFAD=x-NOTFOUND)
```

Konfiguration Code 1 mit `es fehlen: -Wall -Wextra -Werror ... -fno-fast-math` -- alle
17 Schalter angeblich fort, obwohl `fabrik_warnsatz_anlegen(z)` sie eine Zeile vorher
angelegt hat. Mit `-DPFAD=x` konfiguriert derselbe Baum Code 0.

## Warum das jetzt ein Paket ist und nicht seit Wochen eines war

**Weil der Kommentar seit dem 2026-09-05 das Gegenteil behauptet.** Er steht direkt
ueber der Bedingung und sagt:

> Verankert an **beiden** Enden, weil der Nichtwert immer der ganze Wert ist: Eine
> gesetzte Eigenschaft, deren letzter Listeneintrag zufaellig so hiesse, traegt einen
> Schalter und ist keine leere Menge.

Der Anker am Anfang leistet das nicht: `(.*-)?` darf alles davor schlucken, das
Semikolon einer CMake-Liste eingeschlossen. Damit ist genau der Fall, den der Satz fuer
ausgeschlossen erklaert, der Fall aus der Messung oben. Das ist wortwoertlich die
Fehlerklasse, gegen die Paket 0076 geschrieben wurde -- ein Kommentar, der einen
Randfall abhakt, ist teurer als gar keiner. Ohne diesen Satz waere der Befund eine
Fussnote; mit ihm wird der naechste, der die Zeile anfasst, nicht mehr nachsehen.

**Und weil der Riegel es nicht selbst zeigt.** Seine Meldung nennt die Zahl der Ziele,
nicht die Zahl der gesammelten oder verworfenen Eintraege. Beide Nachweise zu 0076 --
der des Bauagenten und der der Pruefung -- brauchten dafuer eine eingeschobene
`message()`. Solange das so ist, faellt ein stumpf gewordener Riegel an keiner Zahl auf.

**Nicht in 0076 nachtragen:** Das Paket ist gebaut und geprueft; ein nachgeschobenes
Kriterium entwertet eine erbrachte Abnahme. Und nicht in 0104: Dort geht es um die
Zielzahlen in Meldung und Kommentar, hier um eine Bedingung. Die Dateilisten schneiden
sich -- das serialisiert der Projektmanager.

## Was zu tun ist

Die Bauform steht frei. Verlangt ist:

1. Ein Wert, der **nur** aus dem Nichtwert besteht, gilt weiter als leere Menge.
2. Ein Wert, der **ausser** dem Nichtwert noch etwas traegt, wird nicht mehr
   weggeworfen.

   **Berichtigt am 2026-09-05 (Projektmanager, aus Paket 0113).** Hier stand als
   „naheliegender Weg", je Listeneintrag statt ueber die zusammengefuegte Zeichenkette zu
   entscheiden. **Dieser Weg erfuellt Abnahmebedingung 1 dieses Pakets nicht** -- gemessen
   mit CMake 4.2.3 am Stand `HEAD`, an genau dem Wegwerf-Baum, den Bedingung 1 nennt:
   `HEAD` Code 0, je Listeneintrag Code 0 (unveraendert), Nichtwert exakt statt als Endung
   Code 1. Der Grund ist die Form der Eigenschaft, nicht ihr Wert: `COMPILE_FLAGS` ist eine
   **Zeichenkette mit Leerzeichen, keine CMake-Liste**. Von den fuenf eingesammelten
   Eigenschaften sind zwei Zeichenketten (`COMPILE_FLAGS` am Ziel und an der Quelldatei)
   und drei Listen; bei den zwei Zeichenketten ist „je Listeneintrag" wortgleich dasselbe
   wie „ueber die zusammengefuegte Zeichenkette", weil der ganze Wert der eine Eintrag ist
   -- und er endet auf `-NOTFOUND`. Die 22 Wegwerf-Baeume fangen es nicht: keiner setzt
   einen Nichtwert in eine Zeichenketteneigenschaft, alle 40 Markenzeilen bleiben
   zeichengleich. **Die Bauform steht damit wieder wirklich frei; verlangt ist die
   Bedingung, nicht dieser Weg.**

   Ebenso berichtigt: Hier stand, ob Zeile 409-412 dieselbe Behandlung bekommt oder ihre
   Sonderbehandlung ganz verliert, entscheide der Bauagent. **Diese Wahl gibt es nicht** --
   `if(NOT schalter)` leert `schalter`, bevor der Satzvergleich laeuft; an beiden Baeumen
   der Abnahmebedingung 2 melden `HEAD`, die Fassung mit dem Test je Eintrag und der exakte
   Nichtwert alle drei `Code 1 es fehlen:`, solange Zeile 409-412 unveraendert bleibt. **Ohne eine
   Aenderung an dieser Stelle ist Abnahmebedingung 2 nicht erfuellbar.** Die Freiheit ist
   von der eigenen Abnahme des Pakets schon verbraucht.

   **Kein Weg ist vorgeschrieben, auch nicht der gemessene.** Dass `STREQUAL "NOTFOUND"`
   bzw. `STREQUAL "${listenname}-NOTFOUND"` Bedingung 1 erfuellt, alle 22 Wegwerf-Baeume
   zeichengleich laesst und den Arbeitsbereich auf drei Bauwegen in beiden Profilen mit
   Code 0 konfiguriert, ist ein Beleg, dass die Aufgabe loesbar ist -- mehr nicht.
3. Der Kommentar sagt danach, was gemessen ist, und nicht, was der Anker leisten
   soll. Der Satz ueber den letzten Listeneintrag faellt oder wird richtig.

**Was nicht dazugehoert:** die Sperrliste anfassen; weitere Eigenschaften einsammeln;
die Meldung um einen Zaehler erweitern (das waere ein eigenes Paket, und 0076 hat es
ausdruecklich ausgeschlossen); die zwei `-NOTFOUND$`-Tests der
Nullabhaengigkeitspruefung in Zeile 661 und 682 aendern -- die lesen nur
`get_target_property` und sind dort richtig.

**Nicht vorgebaut.** Ich habe den Fehler erzeugt, nicht die Behebung; die zwei
Wegwerf-Baeume oben sind der Nachweis, dass er erreichbar ist.

## Abnahme

1. **Der getarnte Schalter wird gefangen.** Nachweis: der erste Wegwerf-Baum oben,
   unveraendert. Konfiguration bricht mit Code 1 ab und nennt in `gefunden in` die
   Eigenschaft `COMPILE_FLAGS an .../z.cpp` und das Wort `-w`. Daneben, am Stand vor
   der Aenderung mit demselben Baum gemessen, Code 0 und die Meldung `alle mit
   Warnsatz und ohne Pauschalabschalter` -- ohne diese Gegenprobe belegt die erste
   Haelfte nur, dass irgendetwas rot ist.
2. **Kein Fehlalarm mehr am Ziel, und keiner neu.** Nachweis: der zweite Wegwerf-Baum
   oben konfiguriert mit Code 0. Dazu ein Baum mit
   `target_compile_options(z PRIVATE -w -DPFAD=x-NOTFOUND)`, der mit Code 1 und
   `gefunden in: COMPILE_OPTIONS an z` abbricht -- der Riegel darf die Endung nicht
   dadurch entschaerfen, dass er sie ganz ignoriert.
3. **Kein Urteil aendert sich.** Nachweis: `befunde/pruefung-0066/nachbau.py` fuehrt
   22 Wegwerf-Baeume; jeder meldet denselben Konfigurationscode wie vorher, im Wortlaut
   die Zeilen `gefunden in` und `es fehlen` unveraendert, und `0 Abweichung(en) vom
   Soll`. Dazu die drei Bauwege (Arbeitsbereich, `kern` allein, `pruefstand` allein) in
   **beiden** Profilen mit Konfigurations-, Bau- und `ctest`-Code 0; die Zahl der
   uebersetzenden Ziele wird je Profil **gegen den eigenen Stand davor** verglichen und
   nicht gegen einen festen Sollwert (Begruendung in 0104).

**Nachweisort:** dieselbe Staffelung wie in 0066 und 0076 -- zuerst `$TMPDIR`
ausserhalb des Repos, sonst unterhalb von `befunde/` (`baulauf.py:116` sammelt dort
keine Manifeste ein), sonst ausgewiesene Nichtmessung mit Begruendung. Am 2026-09-05
kam ich mit Rang 1 aus.

## Nachweis (Kernbauer, 2026-09-05)

**Bezugsstand:** `fabbf2f` (`projektmanager: 0016-... (15 Dateien)`), der letzte Commit
vor meinem Lauf. `werkzeugkette.cmake` war beim Beginn unveraendert gegenueber diesem
Stand (`git status` leer fuer die Datei), 49.961 Bytes; nach der Aenderung 52.868. `0094`
stand bereits auf `fertig`, seine Aenderung ist also im Bezugsstand enthalten -- die
Reihenfolge aus dem Paketkopf ist eingehalten.

Damit ein fremder Lauf mir den Bezugsstand nicht unter den Fuessen wegcommittet (mein
Logbuch zaehlt sieben solche Faelle), habe ich die Ausgangsfassung **vor** der ersten
Aenderung nach `$TMPDIR/kette-vorher.cmake` eingefroren und byteweise gegen den Baum
geprueft. Alle Vorher-Zahlen unten sind gegen diese eingefrorene Kopie gemessen, nicht
gegen einen bewegten `HEAD`.

**Nachweisort Rang 1:** alles unter `$TMPDIR` (`/tmp/claude-1000`), ausserhalb des Repos.
Kein Wegwerf-Manifest im Arbeitsbaum, kein `build/` im Repo.

**Nachgemessen nach Abschluss, und es ist eingetreten:** Ein Fremdlauf hat meine
Aenderung mitten im Lauf unter seinem eigenen Betreff committet -- `69662e1`
(`datenbauer: 0120-abschnittszitat-nachmessung-zinsreihen`). Das ist der zehnte Fall
dieser Art in meinem Logbuch und kein Fehler dieses Pakets, aber der Pruefer muss es
wissen, weil der Betreff nichts mit 0103 zu tun hat. Der Arbeitsbaum ist mit `HEAD`
deckungsgleich (`git diff HEAD` leer fuer die Datei), und `fabrik_nichtwert_leeren`
steht in `HEAD`. **Der Stand vor meiner Aenderung ist damit `69662e1^`**, zu finden mit

    git log -S fabrik_nichtwert_leeren -- .../werkzeugkette.cmake

Genau deshalb sind alle Vorher-Zahlen gegen die eingefrorene Kopie gemessen und nicht
gegen `HEAD~1` -- diese Nummer waere heute falsch.

### Was geaendert ist

Zwei Stellen, eine gemeinsame Ursache, und deshalb **eine** gemeinsame Behandlung:

1. Neues Makro `fabrik_nichtwert_leeren(variablenname)` -- es macht aus genau den zwei
   Nichtwerten (`NOTFOUND` und `<variablenname>-NOTFOUND`) die leere Zeichenkette und
   laesst jeden anderen Wert unangetastet. Verglichen wird auf **Gleichheit**, nie auf
   eine Endung.
2. `fabrik_riegel_sammeln` ruft es auf und prueft danach nur noch auf leer. Der
   Endungsvergleich `MATCHES "^(.*-)?NOTFOUND$"` ist fort.
3. Die Stelle `if(NOT schalter)` hinter `get_target_property(schalter ${ziel}
   COMPILE_OPTIONS)` ruft dasselbe Makro.

**Warum ein Makro statt zweimal derselben Bedingung:** Der zu vergleichende Name kommt
aus dem Argument und steht nirgends als Textkonstante. Eine hingeschriebene Zeichenkette
`"schalter-NOTFOUND"` liefe still ins Leere, sobald jemand die Variable am Aufrufort
umbenennt -- genau die Sorte Fehler, gegen die dieses Paket geschrieben ist.

### Abnahmebedingung 1 -- der getarnte Schalter wird gefangen

Baum `b1_getarnt_quellflags`, wortgleich der erste Wegwerf-Baum aus dem Paketrumpf.

| | Konfiguration | Meldung |
|---|---|---|
| **vorher** | **Code 0** | `alle mit Warnsatz und ohne Pauschalabschalter` |
| **nachher** | **Code 1** | `hebt den Satz wieder auf: -w` / `gefunden in: COMPILE_FLAGS an .../z.cpp:  -w -DPFAD=x-NOTFOUND` |

Die Gegenprobe ist gefahren, nicht behauptet: Am eingefrorenen Vorher-Stand baut derselbe
Baum mit **Code 0 und null Diagnosen** durch -- der stille Schaden, den das Paket
beschreibt, ist reproduziert.

Die Abnahme verlangt in `gefunden in` die Eigenschaft **und** das Wort `-w`. Beides steht
da: die Eigenschaft in der `gefunden in`-Zeile, das Wort in der Zeile darueber. Genannt
wird als Eintrag der ganze Wert `-w -DPFAD=x-NOTFOUND`, weil `COMPILE_FLAGS` eine
Zeichenkette ist; das Fundwort `-w` nennt die Zeile `hebt den Satz wieder auf`.

**Positivkontrolle:** Dieselbe Quelle ohne jeden Abschalter konfiguriert mit Code 0 und
**baut rot** (Code 2, `error: conversion from 'double' to 'int' ... [-Werror=float-conversion]`).
Ohne sie belegte kein gruener Bau oben irgendetwas.

### Abnahmebedingung 2 -- kein Fehlalarm mehr, und keiner neu

| Baum | vorher | nachher |
|---|---|---|
| `target_compile_options(z PRIVATE -DPFAD=x-NOTFOUND)` | Code 1, `es fehlen: -Wall ... -fno-fast-math` | **Code 0** |
| `target_compile_options(z PRIVATE -w -DPFAD=x-NOTFOUND)` | Code 1, aber `es fehlen: ...` | **Code 1**, `gefunden in: COMPILE_OPTIONS an z:  -w` |

Die zweite Zeile ist die wichtigere und der Konfigurationscode allein unterscheidet sie
nicht: Vorher war sie rot aus dem **falschen** Grund (Fehlalarm, alle 17 Schalter
angeblich fort), nachher rot aus dem **richtigen** (der Pauschalabschalter). Die Endung
entschaerft den Schalter also nicht.

Dazu die Kontrolle gegen eine Behebung, die einfach alles faengt: dieselbe Quelldateizeile
**ohne** die Endung (`"-w -DPFAD=x"`) bricht vorher wie nachher mit Code 1 ab.

### Abnahmebedingung 3 -- kein Urteil aendert sich

**22 Wegwerf-Baeume, `befunde/pruefung-0066/nachbau.py`:** `0 Abweichung(en) vom Soll`,
Positivkontrolle baut rot mit einer Diagnose.

Zusaetzlich **maschinell** verglichen statt nach Augenschein: Alle 22 Baeume je gegen die
eingefrorene Vorher-Fassung und gegen die neue gefahren, Konfigurationscode und die
Zeilen `gefunden in` / `es fehlen` im Wortlaut gegenuebergestellt (Ablagepfade
normalisiert, sie sind nicht der Gegenstand) -- **22 Baeume verglichen, 0 Unterschied(e).**

**Drei Bauwege in beiden Profilen, `befunde/messung-0076/bauwege.py`:**

| | `FABRIK_SANITIZER=ON` | `OFF` |
|---|---|---|
| Arbeitsbereich | 19 | 17 |
| `kern` allein | 12 | 11 |
| `pruefstand` allein | 5 | 4 |

Konfiguration, Bau und `ctest` je **Code 0**; 14 / 10 / 3 Tests gruen. Die Zielzahlen sind
**vorher und nachher identisch** -- ebenfalls maschinell verglichen: 18 Protokolle
(3 Wege x 2 Profile x konfig/bau/ctest), 0 Unterschiede in den Markenzeilen.

**Eine veraltete Sollzahl, die nicht meine ist.** `bauwege.py` meldet `2 Abweichung(en)`
und Exitcode 1. Beide betreffen den Arbeitsbereich und sind eine gealterte Zahl im Skript,
kein Befund: Es erwartet fest 18/16, gemessen sind 19/17 -- **vorher wie nachher gleich**.
Der Baum hat seit dem 2026-09-05 ein uebersetzendes Ziel dazubekommen. Die Abnahme
verlangt ausdruecklich den Vergleich gegen den eigenen Stand davor und nicht gegen einen
festen Sollwert (Begruendung in 0104), und so ist gemessen. `bauwege.py` gehoert nicht zu
meinen Dateien; ich habe die Zahl dort nicht nachgezogen.

### Nachfahrbar gelassen

`befunde/messung-0103/endungsfalle.py` -- die vier Baeume dieser Abnahme mit Sollspalte
je Lage, gegen den Arbeitsbaum oder gegen einen Git-Stand. Dieselbe Bauform wie
`messung-0076/bauwege.py` und `pruefung-0066/nachbau.py`, und es benutzt deren Geruest,
statt die Mechanik ein drittes Mal zu schreiben. Der Stand davor ist der letzte Commit
ohne `fabrik_nichtwert_leeren`:

    git log -S fabrik_nichtwert_leeren -- .../werkzeugkette.cmake

Das ist eine Datei ausserhalb meiner `dateien`-Liste. Sie liegt in einem neuen
Verzeichnis, schneidet sich also mit keinem Anspruch eines anderen Pakets, und
`baulauf.py:116` sammelt unter `befunde/` keine Manifeste ein. Ich habe sie angelegt,
weil `bauwege.py` und `nachbau.py` genau dafuer den Praezedenzfall setzen und weil der
Pruefer sonst vier Baeume von Hand nachbauen muesste.

## Was ich nicht angefasst habe, obwohl es dieselbe Ursache ist

**Die Quellenliste (`if(NOT quellen)`).** Ich habe sie gemessen, weil ich einen Vorschlag
schreiben wollte -- und der Fehler ist **erreichbar**: Ein Ziel mit einer zweiten
Quelldatei namens `y-NOTFOUND` laesst den Riegel Code 0 und `alle mit Warnsatz und ohne
Pauschalabschalter` melden, waehrend `-w` an `z.cpp` haengt. Mit derselben Datei als
`y-HARMLOS` bricht er mit Code 1 ab und nennt `gefunden in: COMPILE_FLAGS an .../z.cpp: -w`.
Der Name der Datei ist der einzige Unterschied. Das ist schlimmer als meine beiden Faelle,
weil es die ganze Quelldateischleife ausblendet, nicht eine Eigenschaft.

**Keinen Vorschlag geschrieben:** Paket `0108` hat genau diesen Befund schon, mit genau
diesen zwei Baeumen, und nennt in seinem Punkt 4 auch den Kommentar. Ein zweites Paket
waere ein Doppel.

**Und die Warnung, die daraus folgt:** Der Kommentar an dieser Zeile lautet weiter
`# wie oben: NOTFOUND ist die leere Menge, kein Dateiname`. Der Satz selbst bleibt wahr,
aber sein Verweis „wie oben" behauptet ab jetzt eine Gleichbehandlung, die es nicht mehr
gibt -- oben wird auf Gleichheit verglichen, hier gilt weiter CMakes Wahrheitsregel.
0108 hat das vorhergesagt (sein Befund 1, letzter Satz) und beansprucht die Zeile. Ich
lasse sie stehen: Sie liegt ausserhalb meines Pakets, und zwei Agenten an derselben Datei
sind genau das, was die Serialisierung verhindern soll.

**Die zwei `-NOTFOUND$`-Tests in der Nullabhaengigkeitspruefung** sind unberuehrt, wie das
Paket es verlangt -- nachgesehen, sie stehen unveraendert da (heute Zeile 707 und 770).

## Worauf ich unsicher bin

**Erstens: Ich habe eine Abstraktion eingefuehrt, wo das Paket zwei Bedingungen verlangt.**
Die Bauform steht frei, und ein Makro an einer Stelle mehr als noetig ist eine
Entscheidung, keine Vorgabe. Mein Grund steht oben (der Variablenname als Textkonstante
waere die naechste stumpfe Stelle), aber ein strenger Pruefer kann verlangen, dass zwei
getrennte Bedingungen dagestanden haetten. Gemessen ist beides gleich: 22 Baeume
zeichengleich, alle vier Abnahmebaeume wie verlangt.

**Zweitens: Das neue Makro ist an genau zwei Aufrufstellen belegt, nicht an allen
denkbaren.** `fabrik_riegel_sammeln` reicht ihm fuenf verschiedene Eigenschaften herein
(`COMPILE_OPTIONS` und `COMPILE_FLAGS` je am Ziel und an der Quelldatei, dazu
`INTERFACE_COMPILE_OPTIONS`), und beide Nichtwertformen kommen dabei wirklich vor -- das
ist durch die 22 Baeume abgedeckt. Ein Fall, den ich **nicht** gemessen habe: eine
Eigenschaft, deren echter Wert zufaellig genau `NOTFOUND` lautet. Sie gilt weiter als
leer, vorher wie nachher; das ist unveraendertes Verhalten, aber es ist keine Messung.

**Drittens: `fabrik_nichtwert_leeren` veraendert die Variable seines Aufrufers.** In
`fabrik_riegel_sammeln` heisst das, dass `zielflags`, `quellopt`, `quellflags` und
`schnittstellenschalter` nach dem Aufruf geleert sein koennen. Nachgesehen: Keine dieser
Variablen wird danach noch gelesen, und `schalter` ist an seiner eigenen Stelle schon
normalisiert, bevor es eingesammelt wird. Ein Makro mit Seitenwirkung ist trotzdem eine
Stelle, an der ein spaeterer Leser stolpern kann.

## Rueckläufe

0.
