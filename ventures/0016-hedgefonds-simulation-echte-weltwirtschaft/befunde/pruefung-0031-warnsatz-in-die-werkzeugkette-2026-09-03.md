---
typ: pruefung
paket: 0031-warnsatz-in-die-werkzeugkette
pruefer: kern-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Alle vier Bedingungen einzeln nachgemessen -- Fundstellenzaehlung ohne Ignorierliste, Byte-Vergleich beider Vorfassungen gegen die neue Stelle, Alleinbau und Arbeitsbereichsbau beider Kaesten in zwei Bauprofilen, und die tatsaechlich erzeugte Schalterzeile aus `flags.make` gegen einen Verstoss gehalten.
befunde: 1
nachfolgepaket: 0045-warnsatzriegel-fuer-kuenftige-mitglieder
---

# Pruefung 0031 -- `FABRIK_STRENGE` in der Werkzeugkette

Geprueft am 2026-09-03. Gelesen wurden das Arbeitspaket mit seiner Abnahme, die drei
Bau-Dateien und die Vorfassungen aus `95903a6^`. Das Logbuch des Bauagenten ist
nicht gelesen.

## Wonach ich gesucht habe

Der Warnsatz ist keine Kosmetik, sondern der Traeger von `-fwrapv`s Nachbarn: Ohne
`-Wfloat-equal`, `-Wdouble-promotion` und `-Wconversion` faellt die Gleitkommadisziplin
des Kerns auf die Sperre in `sperre.hpp` allein zurueck. Ein Umzug, der ihn still
verliert, kostet Determinismus, nicht Ordnung. Ich habe deshalb nicht gefragt, ob der
Satz *dasteht*, sondern ob er bei jedem der drei Bauwege am Ziel *ankommt*.

## Bedingung 1 -- genau eine Fundstelle

Zwei Messungen, weil die erste die falsche Antwort geben kann:

- Ignorierlisten-treues Werkzeug ueber das Vorhaben: 6 Zeilen.
- POSIX-Suche ueber denselben Baum, **einschliesslich der Bauverzeichnisse**:
  dieselben 6 Zeilen. Unter `kern/bau` und `pruefstand/bau` liegt keine Kopie.

Genau **eine** davon steht in einer Bau-Datei: `werkzeugkette.cmake:107`. Die
uebrigen fuenf sind Prosa -- viermal `aufgaben/0031-…md`, einmal `rueckstand.md` --,
und alle fuenf zitieren das Kriterium selbst.

**Zur Auslegung, und sie ist nicht die des Bauagenten, sondern meine eigene:** Woertlich
gelesen ist Bedingung 1 unerfuellbar, weil ihr eigener Wortlaut das Suchmuster enthaelt.
Sie war in dem Augenblick verletzt, in dem sie geschrieben wurde. Genau davor warnt
`kern/CMakeLists.txt` in den Zeilen 7 bis 13 -- eine Datei, die ihre eigenen Suchmuster
zitiert, laesst sie nie leer ausgehen. Ich lese die Bedingung deshalb als "genau eine in
einer Bau-Datei, und die in `werkzeugkette.cmake`", was der Nebensatz der Bedingung
selbst sagt. Das ist keine Senkung: Die schaerfere Frage -- gibt es irgendwo eine zweite
wirksame Fassung -- ist mit Nein beantwortet, und zwar auch dort, wo die Ignorierliste
nicht hinsieht.

## Bedingung 3 -- wortgleich verschoben

Mit `diff` gegen beide Vorfassungen, nicht nach Augenschein:

- `95903a6^:kern/CMakeLists.txt` Zeilen 50-56 gegen `werkzeugkette.cmake` Zeilen
  107-113: **bytegleich**, keine Ausgabe.
- `95903a6^:pruefstand/CMakeLists.txt` Zeilen 39-45 gegen dieselbe Stelle:
  **bytegleich**, keine Ausgabe.

15 Schalter, nachgezaehlt. Damit ist nebenbei belegt, dass die Abschrift vom
2026-09-02 vollstaendig war -- die Diagnoseluecke war eine Moeglichkeit, kein
eingetretener Schaden.

Der Umfang stimmt auch: `git diff --stat 95903a6^ 95903a6` beruehrt im Vorhaben genau
die drei Dateien aus der `dateien`-Liste. Der Diff von `werkzeugkette.cmake` enthaelt
ausser der Verschiebung nur die eine Aenderung, die Schritt 3 verlangt -- der Verweis
"siehe `kern/CMakeLists.txt`" in Zeile 20/21 zeigte nach dem Umzug auf sich selbst und
lautet jetzt "begruendet beim Warnsatz am Ende dieser Datei". Kein Wert geaendert, kein
`-Wpedantic` dazugekommen, kein zweites Bauprofil -- also nichts von dem, was der
Abschnitt "Was nicht dazugehoert" ausschliesst.

Anmerkung ohne Folge fuers Urteil: `95903a6` ist der Commit, den `nachtbereitschaft.sh`
am 2026-09-03 versehentlich aus dem ganzen Arbeitsbereich gebildet hat, und sein Betreff
gehoert zu einer anderen Aenderung (`notizen/lehren.md`, 2026-09-03). Der *Inhalt* an
diesen drei Dateien ist davon unberuehrt und oben nachgemessen.

## Bedingung 2 -- beide Kaesten, beide Bauwege, beide Bauprofile

Alle Bauverzeichnisse ausserhalb des Repos neu angelegt, also ohne warmen Zwischenstand.
Der Uebersetzer ist g++ 15.2.0 und damit genau die in `werkzeugkette.cmake` als geprueft
festgenagelte Version; die Abweichungswarnung erscheint nicht.

Alleinbau, der Weg von `baulauf.py`:

- `cmake -S kern -B …` und `cmake -S pruefstand -B …` konfigurieren beide fehlerfrei.
- `cmake --build` uebersetzt beide durch.
- `ctest`: kern **7/7 Passed**, pruefstand **2/2 Passed**.

Arbeitsbereich, derselbe Stand: konfiguriert, gebaut, `ctest` **9/9 Passed**.

Freigabeprofil (`-DCMAKE_BUILD_TYPE=Release`), weil unter Optimierung Warnungen
dazukommen, die im Vorgabeprofil nie erscheinen -- und mit `-Werror` ist das der
Unterschied zwischen gruen und rot: kern **7/7 Passed**, pruefstand **2/2 Passed**. Die
Schalterzeile traegt dort zusaetzlich `-O3 -DNDEBUG`, sonst dieselbe.

Zuletzt die beiden Bauverzeichnisse **im** Baum, die `baulauf.py` wirklich benutzt:
`kern/bau` und `pruefstand/bau` bauen durch und sind 7/7 und 2/2 gruen.

### Die Gefahr, die Bedingung 2 benennt, ist mechanisch ausgeschlossen

Die Bedingung sagt selbst, warum ein gruener Bau hier nicht genuegt: Laege die
`set()`-Reihenfolge falsch, waere `${FABRIK_STRENGE}` beim Alleinbau leer und der Bau
**trotzdem gruen** -- lautlos ohne Warnschalter. Der gruene Bau ist also kein Nachweis.
Der Nachweis ist die Zeile `CXX_FLAGS` in der von CMake erzeugten `flags.make`, denn sie
zeigt, was am Ziel wirklich ankommt. Gemessen an drei Stellen:

- `kern.dir/flags.make` aus dem Alleinbau,
- `pruefstand.dir/flags.make` aus dem Alleinbau,
- `pruefstand/CMakeFiles/pruefstand.dir/flags.make` aus dem Arbeitsbereichsbau.

Alle drei tragen dieselben 15 Schalter in derselben Reihenfolge, dazu `-std=c++20` und
`-fwrapv -fno-fast-math`. Der Alleinbau bindet die Werkzeugkette im
`PROJECT_IS_TOP_LEVEL`-Block ein, der Arbeitsbereichsbau vererbt sie ueber
`add_subdirectory` -- beide Wege liefern nachweislich denselben Satz.

## Bedingung 4 -- der absichtliche Verstoss

**Wie ich sie geprueft habe und warum anders als der Bauagent.** Der Nachweis des
Bauagenten fuehrt beide Fehlermeldungen im Wortlaut, und die Dateien sind weg: Weder
`kern/src/warnsatzprobe.cpp` noch `pruefstand/src/warnsatzprobe.cpp` existiert, `git
status` zeigt keine von beiden, unter `kern/src/` liegen die sechs bekannten Quellen und
unter `pruefstand/src/` nur `vorrat.cpp` und `vorrat_verfahren.cpp`. Ich darf keine Datei
des Pakets anlegen und habe die Probe deshalb **nicht** im Baum wiederholt -- die Warnung
des Projektmanagers beschreibt genau den Schaden, den ein Abbruch dabei anrichtet.

Stattdessen die Kette in vier Gliedern, jedes einzeln gemessen:

1. Eine neue Datei unter `src/` landet ohne Zutun in der Bibliothek. `file(GLOB …
   CONFIGURE_DEPENDS … /src/*.cpp)` in `kern/CMakeLists.txt:47` und
   `pruefstand/CMakeLists.txt:46`.
2. Diese Bibliothek bekommt den Warnsatz. `target_compile_options(… PRIVATE
   ${FABRIK_STRENGE} …)` in `kern/CMakeLists.txt:53` und `pruefstand/CMakeLists.txt:52`.
3. Der Satz, der dort **tatsaechlich ankommt**, ist der aus `werkzeugkette.cmake` -- die
   `flags.make`-Messung oben, fuer beide Kaesten und beide Bauwege.
4. Genau diese Schalterzeile, unveraendert aus `flags.make` uebernommen, uebersetzt eine
   Uebersetzungseinheit mit einer einzigen ungenutzten Variablen **nicht**. Der
   Uebersetzer endet mit Code 1 und meldet, dass die ungenutzte Variable `ungenutzt` ein
   Fehler ist -- mit dem ausloesenden Schalter in eckigen Klammern, `-Werror=unused-variable`,
   gefolgt von der Zeile, dass alle Warnungen als Fehler behandelt werden. Das ist
   derselbe Wortlaut, den der Nachweis des Bauagenten fuer beide Kaesten fuehrt.

**Und die Gegenprobe, ohne die Glied 4 nichts beweist:** Dieselbe Uebersetzungseinheit,
uebersetzt mit dem, was uebrig bliebe, wenn `${FABRIK_STRENGE}` leer waere -- also nur
Sprachstand und Ueberlaufschalter --, endet mit **Code 0**. Der Bau waere gruen. Rot wird
er allein durch den verschobenen Satz.

Der Rest des Bauverzeichnisses stoert nicht: Unter `kern/bau` und `pruefstand/bau` liegt
je eine verwaiste Abhaengigkeitsdatei zu `warnsatzprobe.cpp`. Sie ist wirkungslos --
`build.make` nennt die Probe an keiner Stelle mehr, und beide Bauverzeichnisse bauen und
testen gruen. Beide liegen unter `bau/`, das die Ignorierliste des Vorhabens fuehrt, und
`git status` zeigt sie nicht.

## Urteil

**`geprueft`.** Alle vier Bedingungen sind erfuellt.

## Befund 1 -- kein Rueckweisungsgrund, aber ein eigenes Paket

**Der Umzug hat eine laute Fehlerform gegen eine leise getauscht, und zwar fuer die fuenf
Mitglieder aus T13, die es noch nicht gibt.**

`FABRIK_STRENGE` ist eine gewoehnliche Variable ohne `CACHE`. Ein Mitglied erreicht sie
auf genau zwei Wegen: ueber die Verzeichnisvererbung beim Arbeitsbereichsbau oder ueber
den eigenen `PROJECT_IS_TOP_LEVEL`-Block. Vergisst ein kuenftiges Mitglied diesen Block
-- oder stellt es sein `target_compile_options` versehentlich davor --, dann steht dort
`target_compile_options(x PRIVATE )` mit null Schaltern.

Gemessen, nicht gefolgert:

- Eine undefinierte `FABRIK_STRENGE` expandiert in CMake zu einer Liste der **Laenge 0**
  und zu einer leeren Zeichenkette. Kein Fehler, keine Warnung, die Konfiguration laeuft
  durch.
- Dieselbe Quelle, uebersetzt ohne den Satz, endet mit **Code 0** -- siehe die Gegenprobe
  zu Bedingung 4.

Das ergibt zusammen exakt die Signatur, gegen die dieses Paket geschrieben wurde: Der
Kasten uebersetzt gruen, prueft weniger, und der Uebersetzungsbericht sagt `ergebnis: ok`.

**Warum es der Umzug schlimmer gemacht hat und nicht besser.** Vor dem 2026-09-03 trug
jedes Mitglied seine eigene `set()`-Fassung; ein vergessener Einbindungsblock kostete die
Werkzeugkette und `enable_testing()`, und der zweite Verlust ist laut -- `ctest` meldet
dann "No tests were found!!!", genau wie es `pruefstand/CMakeLists.txt` in den Zeilen 17
bis 20 beschreibt. Der Warnsatz blieb. Jetzt faellt er mit, und ein Mitglied ohne eigene
Proben -- `konsole` und `oberflaeche` aus T13 sind Binaerprogramme -- verliert ihn
vollstaendig lautlos.

Das ist **kein Grund zur Rueckweisung**: Es steht in keiner der vier Bedingungen, es
betrifft keinen heute existierenden Kasten, und der Auftrag schliesst "ein zweites
Bauprofil einfuehren" ausdruecklich aus. Der Umzug ist trotzdem richtig -- er beseitigt
die Duplizierung, die er beseitigen sollte. Er legt nur eine zweite Luecke derselben
Familie frei, und sie gehoert repariert, **bevor** das sechste Mitglied entsteht, nicht
danach.

Vorschlag geschrieben: `aufgaben/0045-warnsatzriegel-fuer-kuenftige-mitglieder.md`.

## Was ich nicht geprueft habe

- Die drei Ueberlaufmassnahmen aus ADR 0011 inhaltlich. Dieses Paket verschiebt einen
  Schaltersatz, es rechnet nicht -- Rueckkopplungsschranken, Zustandsausgabe und
  Zahlenraender haben in ihm keine Angriffsflaeche.
- Die Grep-Regel aus Punkt 3 der Begruendung (`reinterpret_cast`, `const_cast`, `new`,
  `delete`, `asm` im Kern). Sie ist die Abnahme von Paket 0004, nicht von diesem, und der
  Umzug hat ihren Wortlaut bytegleich mitgenommen.
- Ob `baulauf.py` die Bauverzeichnisse bei seiner Suche nach `CMakeLists.txt`
  ueberspringt. Das ist Paket 0041.
