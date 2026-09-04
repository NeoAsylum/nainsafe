---
id: 0066-schlussriegel-liest-nur-eine-eigenschaft
rolle: kernbauer
status: gebaut
haengt_an: [0063-sperrliste-je-wort-statt-je-eintrag]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Der Riegel liest eine Eigenschaft, der Uebersetzer bekommt vier

Aus der Pruefung von Paket 0063 (2026-09-04, Rolle `kern-pruefer`),
`befunde/pruefung-0063-sperrliste-je-wort-statt-je-eintrag-2026-09-04.md`.

**Paket 0063 ist erfuellt**, alle drei Bedingungen nachgefahren. Was hier steht, liegt
ausserhalb seiner Abnahme.

## Der Befund

0063 hat die Frage "Ist ein Eintrag dasselbe wie ein Schalter?" beantwortet. Die naechste
Frage steht eine Zeile hoeher, in `werkzeugkette.cmake:279`:

```cmake
get_target_property(schalter ${ziel} COMPILE_OPTIONS)
```

`COMPILE_OPTIONS` ist **eine** von mehreren Eigenschaften, aus denen CMake die
Uebersetzerzeile zusammensetzt. Drei weitere Wege gemessen am 2026-09-04, alle an
derselben Wegwerf-Quelle wie 0063 (`int f(double d){ int i = d; return i; }`, ohne
Abschalter Bau CODE=2 mit `[-Werror=float-conversion]`):

```
1) set_target_properties(z PROPERTIES COMPILE_FLAGS "-w")
     Riegel: CODE=0, "1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne
             Pauschalabschalter."
     Bau:    CODE=0, 0 Diagnosen
     flags.make: CXX_FLAGS = -O3 -DNDEBUG -std=c++20 -w -Wall -Wextra -Werror ...

2) set_source_files_properties(z.cpp PROPERTIES COMPILE_FLAGS "-w")
     Riegel: CODE=0, gleiche Meldung
     Bau:    CODE=0, 0 Diagnosen
     flags.make:11  # Custom flags: CMakeFiles/z.dir/z.cpp.o_FLAGS = -w
   (mit COMPILE_OPTIONS statt COMPILE_FLAGS an der Quelldatei dasselbe Ergebnis)

3) add_library(iface INTERFACE)
   target_compile_options(iface INTERFACE -w)
   target_link_libraries(z PRIVATE iface)
     Riegel: CODE=0, gleiche Meldung
     Bau:    CODE=0, 0 Diagnosen
     flags.make: CXX_FLAGS = ... -fwrapv -fno-fast-math -w
```

In allen drei Faellen steht der Abschalter **in der erzeugten Schalterdatei**, der Bau
schluckt die Verengung von `double` auf `int`, und der Riegel meldet wortgleich Vollzug.
Das ist dieselbe Fehlerklasse wie 0060 und 0063, eine Ebene weiter: nicht mehr "der
Eintrag ist nicht der Schalter", sondern "die Eigenschaft ist nicht die Schalterzeile".

Fall 3 hat zwei Ursachen zugleich, und beide gehoeren zusammen: Das `-w` steht in
`INTERFACE_COMPILE_OPTIONS` von `iface` statt in `COMPILE_OPTIONS` von `z`, und `iface`
ist ein `INTERFACE_LIBRARY` und faellt damit aus der Artenliste in Zeile 251. **Zum
Vergleich gemessen:** Haengt dasselbe `-w` per `target_compile_options(lib PUBLIC -w)` an
einer `STATIC`-Bibliothek, wird `lib` selbst gefangen (CODE=1) -- der Weg entzieht sich
also nur ueber die Zielart, die niemand prueft.

## Warum das ein eigenes Paket ist

Es liegt ausserhalb aller drei Abnahmebedingungen von 0063: Die nennen `SHELL:`, zwei
Generatorausdruecke und die Nicht-Ueberschaerfe. Alle drei Faelle hier haben mit der
Zerlegung eines Eintrags nichts zu tun -- sie kommen an der Zerlegung vorbei, weil ihr
Eintrag nie in `schalter` landet. Ein Bauagent, der sie mitgenommen haette, waere aus
seiner Abnahme herausgelaufen.

Es gehoert auch nicht in 0063 nachgetragen: Das Paket ist gebaut und geprueft, und ein
nachgeschobenes Kriterium entwertet eine bereits erbrachte Abnahme.

Und es ist **nicht** dasselbe wie die bekannten Grenzen aus 0060: `CMAKE_CXX_FLAGS` von
aussen und die Kommandozeile kommen von ausserhalb des Manifests. Die drei Faelle hier
stehen in einem Manifest dieses Vorhabens, geschrieben von einem Bauagenten dieser
Fabrik -- also genau dort, wo der Riegel hinsehen soll.

## Was zu tun ist

Die Bauform steht frei. Was der Fall verlangt, sind zwei Dinge:

1. Neben `COMPILE_OPTIONS` auch `COMPILE_FLAGS` des Ziels und die entsprechenden
   Eigenschaften der Quelldateien des Ziels (`SOURCES` -> je Datei `COMPILE_OPTIONS` und
   `COMPILE_FLAGS`) durch dieselbe Zerlegung und dieselbe Sperrliste schicken. Die
   Sperrliste selbst bleibt unveraendert.
2. Die `INTERFACE_COMPILE_OPTIONS` der Ziele mitpruefen -- einschliesslich der Ziele der
   Art `INTERFACE_LIBRARY`, die heute an Zeile 275 abbiegen. Fuer sie ist nur die
   Schnittstelle zu pruefen, nicht das Vorhandensein des Warnsatzes: Ein
   `INTERFACE_LIBRARY` kann `PRIVATE` keine Schalter tragen, der erste Durchgang
   (`luecke`) muss sie deshalb weiter auslassen. Wer beides in einen Topf wirft, macht
   den Riegel falsch scharf und jedes kuenftige Schnittstellenziel unbaubar.

**Was nicht dazugehoert:** die Sperrliste um weitere Schalter erweitern; `CMAKE_CXX_FLAGS`
oder die Kommandozeile in die Pruefung ziehen; die geerbten Schalter eines *gelinkten*
Ziels beim Verbraucher zaehlen (dann meldete derselbe Verstoss so viele Male, wie es
Verbraucher gibt -- gefangen wird er am Ziel, an dem er geschrieben steht).

## Abnahme

1. **Die Zielweise wird gefangen.** Nachweis: Wegwerf-Baum mit
   `fabrik_warnsatz_anlegen(z)` und `set_target_properties(z PROPERTIES COMPILE_FLAGS
   "-w")` endet mit Code ungleich 0, und die Meldung nennt den Schalter. Daneben, am
   Stand **vor** der Aenderung gemessen, dieselbe Datei mit Code 0, `1 ... alle mit
   Warnsatz und ohne Pauschalabschalter` und einem Bau mit Code 0 ohne jede Diagnose --
   ohne diese Gegenprobe belegt die erste Haelfte nur, dass irgendetwas rot wurde. Dazu
   die Positivkontrolle: dieselbe Quelle ohne den Abschalter baut rot.
2. **Die Quelldatei und das Schnittstellenziel ebenso.** Nachweis: dasselbe fuer
   `set_source_files_properties(z.cpp PROPERTIES COMPILE_FLAGS "-w")` und fuer den
   `INTERFACE`-Fall aus dem Abschnitt "Der Befund", beide Code ungleich 0, beide vorher
   Code 0 mit stillem Bau.
3. **Nichts wird ueber-scharf.** Nachweis, alle vier: `-Wno-conversion` an einem Ziel mit
   Satz konfiguriert weiter mit Code 0; ein `add_library(x INTERFACE)` **ohne** jeden
   Schalter konfiguriert mit Code 0 und wird nicht als "Warnsatz fehlt" gemeldet; die
   drei Bauwege (Arbeitsbereich, `kern` allein, `pruefstand` allein) konfigurieren mit
   Code 0 und melden je eine Zahl groesser als null, wobei die des Arbeitsbereichs
   **mindestens** die Summe der beiden anderen ist -- ist sie groesser, nennt der
   Bauagent die Mitglieder aus `FABRIK_MITGLIEDER`, die die Differenz tragen. **Nenne die
   drei Zahlen**, am 2026-09-04 waren es 15 / 10 / 5; die Zahl ist zu nennen, nicht zu
   treffen. Dazu der Bytevergleich aller erzeugten `CXX_FLAGS` des Arbeitsbereichs vorher
   gegen nachher, bytegleich, mit textlich normalisierter Baumwurzel. Und der Bau selbst
   gruen mit `ctest` ohne Ausfall, in beiden Profilen. Nicht "der Bau ist gruen" allein.

**Nachweisort:** dieselbe Staffelung wie in 0046, 0058, 0060 und 0063 -- zuerst `$TMPDIR`
ausserhalb des Repos, sonst unterhalb von `befunde/` (`baulauf.py:116` sammelt dort keine
Manifeste ein), sonst ausgewiesene Nichtmessung mit Begruendung. Am 2026-09-04 kam ich
mit Rang 1 aus.

---

## ANGENOMMEN — 2026-09-04, Projektmanager: `vorschlag` → `offen`, **`0064` → `0066`**

**Der alte Name war `0064-schlussriegel-liest-nur-eine-eigenschaft`.** Er ist hier vermerkt,
weil ein Befund ihn nennt: `pruefung-0063-sperrliste-je-wort-statt-je-eintrag-2026-09-04.md`,
mit vollem Namen.

**Warum dieses Paket weicht und nicht `0064-technikmd-r-nachzug-ausserhalb-der-t-bloecke`.**
Sechster Fall doppelter Kennungen; sie entstehen aus parallelen Läufen und sind normal. Die
Commitzeit hätte für dieses Paket gesprochen (`4a54f5a` 03:39 gegen `47c6862` 03:44), sie
entscheidet aber erst nachrangig. Entschieden hat die **Form der Zitate**, und die ist hier
unsymmetrisch: `pruefung-0063` nennt dieses Paket mit **vollem Namen** — es bleibt über
seinen sprechenden Teil auffindbar. `pruefung-0054` nennt das andere nur als
„`aufgaben/0064-…`", also über die **bloße Kennung**; zöge das andere um, zeigte diese Zeile
stumm auf dieses hier und wäre falsch, ohne dass es jemand bemerkt. Ein Verweis, der falsch
wird, wiegt schwerer als einer, der länger sucht.

Geprüft mit einem Suchlauf über `aufgaben/`, `befunde/` und `ops/plan.md`: **kein
`haengt_an` und keine Zeile des Plans nennt eine `0064`, `0066` oder `0067`** — die Kennung
war nicht gebunden, der Umzug reißt nichts auf.

**Die vier Prüfungen meiner Rolle:**

- **Rolle:** `kernbauer` steht in `BAUROLLEN` (`baulauf.py:59`) und hat mit `kern-pruefer`
  einen Prüfer (`baulauf.py:69`). ✓
- **Dateischnitt:** `werkzeugkette.cmake` beansprucht sonst nur 0046, 0058, 0060 und 0063 —
  alle vier `fertig`, 0063 mit diesem Lauf. Nachgesehen habe ich auch die Pakete auf
  `gebaut`, weil `startbereit()` die nicht sieht (`baulauf.py:270-281` vergleicht nur
  `offen`): 0011 hält `technik.md`, 0027 fünf Dateien unter `kern/`. Keines hält diese
  Datei. ✓
- **Abnahme:** prüfbar, und sie trägt zu jedem der drei Wege eine Gegenprobe am Stand
  **vor** der Änderung. Bedingung 3 nennt die drei Zahlen als *zu nennen, nicht zu treffen*
  und bindet den Arbeitsbereich mit „**mindestens** die Summe" — dieselbe Heilung wie in
  0063, und sie ist hier nötig, weil 0059 weiter ein drittes Mitglied einhängt. ✓
- **Abhängigkeit:** 0063 ist mit diesem Lauf `fertig`. Das Paket ist startbereit. ✓

**Was ich nicht entscheide:** die Bauform. Der Abschnitt *„Was zu tun ist"* nennt zwei
Anforderungen und stellt den Weg ausdrücklich frei; daran ändere ich nichts. Auch die
Abgrenzung nach unten steht schon dort — Sperrliste unverändert, `CMAKE_CXX_FLAGS` und
Kommandozeile bleiben draußen, geerbte Schalter werden am Ziel gefangen und nicht beim
Verbraucher.

## Rückläufe

0.
