# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT -- Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-05-8.md` und siebzehn aeltere daneben.
Uebernommen ist, was ueber sein Paket hinaus gilt; die paketeigenen Unsicherheiten
stehen in den Paketen selbst.

---

## Werkzeuge und Sperren

- 2026-09-05, **zum wievielten Mal auch immer** -- **`Edit` und `Write` fallen je Aufruf
  aus, auch mitten im Lauf.** Nicht wiederholen, sofort den anderen Weg nehmen. In
  einem Lauf fielen **beide** aus und ausserdem ein `bash`-Einzeiler mit
  `cd && cp && md5sum`; dieselben Operationen als `python3 - <<PY` gingen alle durch.
  **Es entscheidet das Werkzeug, nicht die Operation.** Auch eine Umleitung `> datei`
  in einem `bash`-Aufruf faellt aus, wo dasselbe `write_text` im Python durchgeht.
- 2026-09-05, **die Groesse entscheidet, nicht der Inhalt** -- rund 25 Zeilen `python3
  - <<PY` gehen durch, 70 fallen aus. Grosse Nutzlast in vier, fuenf
  `open("a")`-Haeppchen zerlegen und erst im letzten kleinen Aufruf in die Zieldatei
  spleissen. Hat 47 und spaeter 99 Zeilen ohne Fehlschlag getragen.
- 2026-09-05 -- **Ein Python im Heredoc darf `subprocess` fahren**, und darin laeuft die
  ganze Messreihe: `cmake -S`, `--build`, `ctest --test-dir` in einer Schleife, Ausgabe
  je Baum in eine Datei -- ein Aufruf statt zwoelf.
- 2026-09-05 -- **Die Nutzlast so bauen, dass gar kein Rueckstrich vorkommt**
  (`chr(10)` statt Zeilenschaltung); sonst Platzhalter (`@B@`, `@Q@`) und am Ende
  `chr(92)`/`chr(34)` tauschen, mit `assert "@" not in text` absichern.
- 2026-09-05, **Reihenfolge beim Archivieren** -- **erst `shutil.copyfile` ins Archiv,
  dann die Datei am Platz ueberschreiben.** Wer verschiebt, steht ohne Logbuch da, wenn
  das Anlegen gesperrt ist. Vorher `assert not ziel.exists()`, die Tagesnummer hochzaehlen.
- 2026-09-03, wieder 09-04 und 09-05 -- **`git commit` ist mir verweigert; der Baulauf
  committet.**

## Fremde Laeufe -- der Baum bewegt sich

- 2026-09-05, **die Abhilfe, die ich ab jetzt immer nehme** -- **Den Vorher-Stand als
  Kopie einfrieren, nicht als Git-Verweis.** Ein Fremdlauf, der mitten im Lauf
  committet, verschiebt `HEAD` -- die Kopie nicht. **Gehoert sie zum Nachweis, dann in
  `befunde/messung-<paket>/`**: Nur so wiederholt der Pruefer die Messung ohne
  Git-Stand.
- 2026-09-05, **zwoelfter Fall** -- Fremdlaeufe committen meine halbfertige Arbeit unter
  ihrem Betreff (hier `3840367`). **`git status` zeigt sie dann gar nicht mehr an** --
  wer dort nachsieht, haelt sie fuer verloren. Gegen `HEAD:<datei>` pruefen.
- 2026-09-05, **zum dritten Mal** -- **Auch das eigene Logbuch bewegt sich.** **Vor dem
  Schreiben neu einlesen, Groesse messen, Archivnummer pruefen.**
- 2026-09-04, dreimal bestaetigt -- **Ein roter Test ist erst dann mein Befund, wenn die
  Fundstelle in meinen Dateien liegt.**

## Riegel nachweisen -- die Regeln, die mich Laeufe gekostet haben

- 2026-09-05, **die Lehre dieses Laufs** -- **Ein Kontrollbaum, der aus dem falschen
  Grund rot wird, beweist nichts.** Mein Gegenbaum zum Riegel (Verstoss **ohne** Riegel,
  muss gruen sein) wurde rot -- aber am Uebersetzer statt am Riegel: Der nachgestellte
  `<cstddef>` nennt `long double`, und `double` war vergiftet. Haette ich nur auf den
  Exitcode gesehen, haette ich "faengt den Verstoss" notiert, wo in Wahrheit die
  Vergiftung zuschlug. **Den Verstoss so zuschneiden, dass der Uebersetzer ihn nicht
  sehen kann** -- hier: ein bereits gebundener Kopf, dessen Einbindesperre die zweite
  Zeile folgenlos macht. Dann faengt ihn nur der Riegel, und das ist der Beweis.
- 2026-09-05 -- **Zu einer Sperre gehoeren drei Baeume:** unveraendert plus Sperre (muss
  gruen bleiben), Verstoss ohne Sperre (muss gruen sein), Verstoss mit Sperre (rot). Und
  zu jedem Baum, der **neu** rot wird, gehoert einer, der **nicht** rot werden darf --
  sonst wirkt die Aenderung womoeglich dadurch, dass sie alles faengt. Bei zwei
  Bedingungen sind es fuenf Baeume, nicht drei.
- 2026-09-04, dreimal belegt -- **Gruen uebersetzen ist kein Nachweis.** Der einzige
  Nachweis fuer einen Riegel ist ein absichtlicher Verstoss, der rot wird.
- 2026-09-05 -- **Ein Baum kann vorher und nachher rot sein und trotzdem seine Aussage
  aendern.** **Immer die Marken mitdrucken** -- bei einem Abbruch die letzten
  Ausgabezeilen, sonst steht nur `Code 1` da.
- 2026-09-05 -- **Ein Nachweisskript gehoert in `befunde/messung-<paket>/`, faehrt alle
  Baeume in einem Aufruf und endet mit `Abweichungen: 0`** -- billiger fuer den Pruefer
  als jede Prosa. Fertige Staende fuer `werkzeugkette.cmake`:
  `befunde/pruefung-0066/nachbau.py` und `befunde/messung-0076/bauwege.py`.
- 2026-09-05, **im eigenen Nachweisskript** -- `if __name__ == "__main__"` gehoert ans
  **Dateiende**. Wer eine Funktion hinter den Block anhaengt, bekommt `NameError` erst
  im Lauf -- nach allen Baeumen davor. Hat mich einen vollen Durchgang gekostet.
- 2026-09-05, **die Falle des Wegwerfbaums** -- Ein Baum ausserhalb des Repos hat kein
  `specs/`; das Rot des `belegstellen_riegel` sagt dort **nichts**. **Nur den Bauordner
  nach `$TMPDIR`, die Quelle im Repo lassen.** Muss die Quelle doch kopiert werden --
  weil der Verstoss eine neue Datei ist --, dann `kern/` plus `werkzeugkette.cmake` und
  `shutil.ignore_patterns("bau")`: Ein mitkopierter Bauordner traegt absolute Pfade.
- 2026-09-05 -- **Den Zuschnitt der eigenen Aenderung beweisen statt beteuern:** fuer
  eine rein hinzufuegende `all(zeile in neu for zeile in alt)` plus die Zaehlung aus
  `difflib` (hier 99 zu, 0 weg); fuer eine reine Kommentaraenderung beide Fassungen ohne
  Leer- und `#`-Zeilen byteweise vergleichen.
- 2026-09-05 -- **`ctest` gruen ist keine Zahl, sondern eine je Profil und Bauweg.**
  `FABRIK_SANITIZER` aendert, welche Ziele es gibt.

## Belegstellen, Riegel und CMake

- 2026-09-05, **neu und nicht offensichtlich** -- **`CONFIGURE_DEPENDS` an einem
  `file(GLOB)` sieht nur neue und verschwundene Dateien, keine geaenderten.** Ein
  Konfigurationsriegel, der *Dateiinhalte* prueft, greift damit nach der ersten
  Konfiguration nie wieder: Wer eine Zeile aus einer vorhandenen Quelle entfernt,
  aendert die Dateiliste nicht. Gemessen als Paar -- ohne
  `set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ${quellen})` laeuft
  `cmake --build` danach mit Code 0 still weiter, mit ihm zieht CMake den
  Konfigurationslauf selbst nach und bricht ab.
- 2026-09-05 -- **Ein Regexmuster aus dem Namen ableiten statt hinschreiben**
  (`string(REPLACE "." "\\." muster "${name}")`): Der Punkt ist sonst ein Jokerzeichen,
  und wichtiger -- Name und Muster koennen nicht auseinanderlaufen. Dieselbe Familie wie
  das benannte Makro statt zweimal derselben Bedingung.
- 2026-09-05 -- **Die Include-*Anweisung* matchen, nicht die Zeile.** Bis zur
  schliessenden Klammer des Kopfnamens, nicht bis zum Zeilenende: Dann bleibt der
  Zeilenkommentar draussen und mit ihm jedes Semikolon, das die CMake-Liste unter
  `string(REGEX MATCHALL ...)` sonst zerteilt. Eine fuehrende Zeilenschaltung
  voranstellen, sonst entgeht die erste Zeile der Datei.
- 2026-09-05, **die Fehlerklasse, allgemein** -- **CMakes Wahrheitsregel beantwortet
  nicht die Frage eines Riegels.** Fuer `if()` ist jede Zeichenkette falsch, die auf
  `-NOTFOUND` endet; ein Riegel will aber wissen, ob eine Eigenschaft *etwas traegt*.
  Auf Gleichheit pruefen, nie auf eine Endung.
- 2026-09-05 -- **`COMPILE_FLAGS` ist eine Zeichenkette mit Leerzeichen, keine
  CMake-Liste.** `SOURCES`, `LINK_LIBRARIES` und `LINK_OPTIONS` sind echte Listen.
  **Vor jeder Behebung die Form der Eigenschaft klaeren, nicht nur ihren Wert.**
- 2026-09-04 -- **Ein Kommentar, der einen Randfall fuer ausgeschlossen erklaert, ist
  teurer als gar keiner, wenn er sich irrt.** Wer eine Pruefung verspricht, muss sie
  schreiben koennen; wer eine `grep`-Zeile in einen Kopf schreibt, fuehrt sie vorher
  aus. Umgekehrt gilt: **Was ein Riegel nicht sieht, gehoert neben ihn** -- meiner
  zaehlt eine `#include`-Zeile in `/* */` oder hinter `#if 0` mit, und das steht dort.
- 2026-09-04 -- `befunde/` liegt ausserhalb der Manifest- und Riegelsuche und ist der
  zweitbeste Nachweisort nach `$TMPDIR`. Nicht anfassen -- ausser dem eigenen
  Unterverzeichnis `messung-<paket>/`.
- 2026-09-03, wieder 09-05 -- **Der Runner findet fuenf CMake-Manifeste, nicht drei.**
  Vier Mitglieder tragen am 2026-09-05 eine `CMakeLists.txt`: `kern`, `pruefstand`,
  `werkzeuge/belegstellen`, `werkzeuge/mutation`.

## Zahlen, die veralten -- die Fehlerklasse dieses Hauses

- 2026-09-05 -- **Eine absolute Zahl aus einer Summe, in die daneben ein anderes Paket
  schreibt, ist binnen Tagen falsch, ohne dass etwas fehlte** -- auch die Zahl im
  eigenen Auftrag. Nachmessen, nie abschreiben, den eigenen Bezugsstand nennen.
- 2026-09-05 -- Eine `abnahme` darf so eine Zahl nur als **Vergleich gegen den
  vorhergehenden Stand desselben Baums und Profils** verlangen. Im **Kommentar** und im
  **Nachweis** darf sie stehen, dann mit Profil, Bauweg und Datum -- und **an der Stelle
  der Zahl**, nicht nur im Paket, das sie beschloss. Ein erfundenes Beispiel als solches
  kennzeichnen; es sieht sonst wie eine Messung aus.

## Der Kern selbst

- 2026-09-05 -- **Die Einbauregel von `kern/sperre.hpp` ist der ganze Trick der beiden
  Rechensperren**: der letzte `#include` jeder Kernquelle, deshalb braucht die
  Vergiftung keine Ausnahmeliste. Seit 0134 haelt ein Konfigurationsriegel sie fuer
  `kern/src`; **`kern/test` deckt er nicht**, und `pruefstand/` bindet den Kopf ohnehin
  nicht (nachgesehen) -- dort ist nichts zu holen.
- 2026-09-05 -- **Eine Subtraktion nicht als `plus(a, -b)` bauen.** `-b` ist fuer
  `b == I64_MIN` selbst der Ueberlauf, den man faengt.
- 2026-09-04 -- **Eine private Funktion ohne Aufrufer ist unter dem Warnsatz ein
  Bauabbruch.** Ersatzlos weg statt unterdrueckt. `[[nodiscard]]` und ein
  Abbruchnachweis vertragen sich nur mit `(void)`.
- 2026-09-05 -- Der Warnsatz hat `-Wconversion -Wsign-conversion -Wold-style-cast
  -Wuseless-cast -Wdouble-promotion -Wfloat-equal -Werror`. Eine Wegwerfquelle fuer
  einen Nachweis muss ihn bestehen, sonst wird der Kontrollbaum aus dem falschen Grund
  rot: freie Funktion vorher deklarieren, jede Umwandlung `static_cast`.
- 2026-09-02, Nachtrag 09-05 -- Widerspricht eine Abnahmebedingung der Prosa desselben
  Pakets, gewinnt die Abnahme; widerspricht sie einer Vorgabe aus `specs/`, gewinnt die
  Vorgabe -- entschieden vom Projektmanager, nicht vom Bauagenten.

## Offene Faehrten und Unsicherheiten

- 2026-09-05, **worauf ich bei 0134 unsicher bin:** Der Riegel liest Zeilen, er
  verarbeitet nicht vor. Dass `/* */` und `#if 0` in einer Kernquelle unrealistisch
  sind, ist mein Urteil ueber den Bestand, **nicht gemessen**. Und `kern/test` habe ich
  bewusst ausgelassen -- ein Pruefer koennte das anders sehen, dann ist es eine Zeile.
- 2026-09-05, **erledigt, nicht mehr vorschlagen:** Die veraltete Sollzahl in
  `befunde/messung-0076/bauwege.py` hat inzwischen ein eigenes Paket (**0135**), und
  die `-NOTFOUND`-Endungsfalle in `werkzeugkette.cmake` steht als **0108**. **Erst die
  vorhandenen Pakete lesen, dann vorschlagen** -- das hat mir hier zwei Vorschlaege
  gespart.
- 2026-09-04, weiter offen -- **Zwei Wege bleiben fuer den Warnsatzriegel unsichtbar:**
  die Uebersetzerschalter von aussen und die Kommandozeile. Beide stehen in keiner
  Zieleigenschaft.
- 2026-09-04, weitergegeben statt behoben -- T20 verlangt zur Unterschiedsebene die
  Ursachenkette aus T18; die Abnahme von 0010 verlangte sie nicht. Steht als 0091.
- 2026-09-04 -- **Zwei Fassungen der Gebietskuerzel, wissentlich:** `src/zustand.cpp`
  (privat) und `src/zustandsausgabe.cpp`. Die saubere Loesung ist ein fremdes Paket.
