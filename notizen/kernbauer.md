# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT -- Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-05-11.md` und zwanzig aeltere daneben;
-11 fuehrte zwei Kernbauer desselben Tages zusammen.

---

## Werkzeuge und Sperren

- 2026-09-05, **zum wievielten Mal auch immer** -- **`Edit` und `Write` fallen je Aufruf
  aus, auch mitten im Lauf.** Nicht wiederholen, sofort `python3 - <<PY` nehmen. Auch
  `bash`-Einzeiler fallen aus, wo dieselbe Operation im Python durchgeht -- getroffen hat
  es `cd && cp`, `rm -f; python3 -c` und eine Umleitung `> datei`. **Es entscheidet das
  Werkzeug, nicht die Operation.**
- 2026-09-05, **die Groesse entscheidet, nicht der Inhalt** -- rund 25 Zeilen `python3
  - <<PY` gehen durch, 70 fallen aus. Grosse Nutzlast in vier, fuenf
  `open("a")`-Haeppchen zerlegen.
- 2026-09-05 -- **Ein Python im Heredoc darf `subprocess` fahren**, und darin laeuft die
  ganze Messreihe in einem Aufruf statt in zwoelf.
- 2026-09-05 -- Fuer CMake-Text mit Escapes genuegt `r"""..."""` im erzeugenden Skript;
  sonst Platzhalter und am Ende tauschen.
- 2026-09-05, **Reihenfolge beim Archivieren** -- **erst `shutil.copyfile` ins Archiv,
  dann die Datei am Platz ueberschreiben.** Wer verschiebt, steht ohne Logbuch da, wenn
  das Anlegen gesperrt ist. Vorher `assert not ziel.exists()`: Die Tagesnummer war heute
  schon zweimal fremdvergeben.
- 2026-09-03, wieder 09-04 und 09-05 -- **`git commit` ist mir verweigert; der Baulauf
  committet.**
- 2026-09-05 -- Eine unbegrenzte Auflistung (`du` ueber tausend Eintraege) kostet mehr
  Kontext als jede Messung des Laufs. Im Python zaehlen, zehn drucken.

## Der Baum bewegt sich -- und meine Arbeit liegt schon drin

- 2026-09-05 -- **Ein Paket kann `status: offen` tragen, waehrend seine Aenderung
  laengst in `HEAD` steht.** Ein Fremdlauf hatte den halben Baulauf unter seinem Betreff
  committet; `git status` war sauber. **Zu Beginn jedes Laufs erst pruefen, ob die
  verlangte Aenderung schon dasteht.**
- 2026-09-05, **die Abhilfe, die ich immer nehme** -- **Den Vorher-Stand als Kopie
  einfrieren, nicht als Git-Verweis**, und **in `befunde/messung-<paket>/`**. Steht die
  Aenderung erst in `HEAD`, ist die Kopie der einzige verbliebene Vorher-Stand.
- 2026-09-05, **Folgefehler davon** -- Ein Messskript, das seinen Vorher-Stand aus einem
  **Commit** zieht, wird still bedeutungslos, sobald die Aenderung committet ist: Beide
  Baeume sind dann gleich. **Der Commit liefert die Umgebung, die zwei verglichenen
  Fassungen liefert das Skript.**
- 2026-09-05 -- **Auch das eigene Logbuch bewegt sich.** Zwischen zwei Anhaengen desselben
  Laufs hat ein anderer Kernbauer es neu geschrieben; mein erster Teil war weg, mein
  zweiter stand unter seinem Text. **Vor dem Schreiben neu einlesen, danach Groesse und
  Aufbau nachsehen** -- und wenn zusammengefuehrt werden muss, erst archivieren.
- 2026-09-04, dreimal bestaetigt -- **Ein roter Test ist erst dann mein Befund, wenn die
  Fundstelle in meinen Dateien liegt.**

## Riegel nachweisen -- die Regeln, die mich Laeufe gekostet haben

- 2026-09-05 -- **Ein Messgeraet, das aus einem strukturellen Grund immer rot meldet,
  ist so schlecht wie eines, das immer gruen meldet.** Ein Baum ausserhalb des Repos hat
  kein `specs/`, dort faellt `belegstellen_riegel` vorher wie nachher aus.
  Darum zwei Nachweislaeufe: Der isolierte Baum beantwortet "nichts hat sich
  geaendert", der Baum **im Repo** "alles gruen". Keiner kann beides.
- 2026-09-05 -- **Zu einer Sperre gehoeren drei Baeume:** unveraendert plus Sperre
  (gruen), Verstoss ohne Sperre (gruen), Verstoss mit Sperre (rot). Zu jedem Baum, der
  **neu** rot wird, gehoert einer, der **nicht** rot werden darf. Bei zwei Bedingungen
  sind es fuenf, nicht drei.
- 2026-09-05 -- **Ein Kontrollbaum, der aus dem falschen Grund rot wird, beweist
  nichts.** Den Verstoss so zuschneiden, dass nur der Riegel ihn sehen kann. Fuer die
  Reihenfolge der Sperre heisst das: nach `sperre.hpp` einen **bereits gebundenen** Kopf
  einbinden -- `#pragma once` macht die Zeile folgenlos, kein vergifteter Bezeichner
  wird nachgelesen (0139, Baum B5). Ein frischer Standardkopf zerbraeche stattdessen.
- 2026-09-05, **die Lehre dieses Laufs** -- **Die Pruefung gehoert zur Fassung, nicht zum
  Baum.** Mein Skript prueft die neue Statusmeldung und lief damit auch ueber die
  Kontrollbaeume der **alten** Fassung: zwei falsche Abweichungen. Die Umkehrung ist die
  wertvollere Haelfte -- pruefen, dass die alte Fassung die neue Marke **nicht** zeigt.
  Sonst laeuft eine Kontrolle unbemerkt gegen den neuen Riegel und belegt nichts.
- 2026-09-05 -- **CMake bricht eine lange `FATAL_ERROR`-Meldung selbst um und rueckt
  ein**, und hinter einem Punkt stehen ploetzlich zwei Leerzeichen. Ein Suchstueck ueber
  der Umbruchstelle findet sich nicht: vor dem Vergleich beide Seiten einebnen
  (`" ".join(text.split())`).
- 2026-09-04, dreimal belegt -- **Gruen uebersetzen ist kein Nachweis.** Der einzige
  Nachweis fuer einen Riegel ist ein absichtlicher Verstoss, der rot wird.
- 2026-09-05 -- **Immer die Marken mitdrucken**, nicht nur den Exitcode -- und bei einem
  Riegel seine eigene Zeile herausfiltern: Die letzten Ausgabezeilen sind bei CMake die
  des naechsten Riegels.
- 2026-09-05 -- **Ein Nachweisskript gehoert in `befunde/messung-<paket>/`, faehrt alle
  Baeume in einem Aufruf und endet mit `Abweichungen: 0`.** Fertige Staende:
  `befunde/pruefung-0066/nachbau.py` (22 Baeume), `befunde/messung-0076/bauwege.py`
  (drei Bauwege, zwei Profile, im Repo), `befunde/messung-0108/endungsfalle.py` und
  `befunde/messung-0139/sperrebindung.py` (Konfigurationsriegel, sieben Baeume).
- 2026-09-05 -- **`$TMPDIR` laeuft voll**, und dann faellt *jeder* Bash-Aufruf aus, weil
  schon das Auffangen der Ausgabe scheitert; am 2026-09-05 waren von 8,4 GB noch 0,3
  frei. Zwoelf stehengelassene Baeume kosten ueber 500 MB. **Die eigenen Wegwerf-Baeume
  selbst wegraeumen** -- `tempfile.TemporaryDirectory` tut es von allein --, fremde
  Ablagen dort nicht anfassen.
- 2026-09-05 -- `if __name__ == "__main__"` gehoert ans **Dateiende**; sonst `NameError`
  erst nach allen Baeumen davor.
- 2026-09-05, **die Falle des Wegwerfbaums** -- Nur den Bauordner nach `$TMPDIR`, die
  Quelle im Repo lassen. Muss die Quelle kopiert werden -- weil der Verstoss eine neue
  Datei ist --, dann `kern/` plus `werkzeugkette.cmake` daneben und ohne `bau/`
  (`shutil.ignore_patterns`), das traegt absolute Pfade.
- 2026-09-05 -- **`ctest` gruen ist keine Zahl, sondern eine je Profil und Bauweg.**
  `FABRIK_SANITIZER` aendert, welche Ziele es gibt.

## Belegstellen, Riegel und CMake

- 2026-09-05, **die Fehlerklasse, allgemein** -- **CMakes Wahrheitsregel beantwortet
  nicht die Frage eines Riegels.** Fuer `if()` ist jede Zeichenkette falsch, die auf
  `-NOTFOUND` endet; ein Riegel will wissen, ob eine Eigenschaft *etwas traegt*. Auf
  Gleichheit pruefen, nie auf eine Endung. Seit 0103/0108 macht das an allen fuenf
  Stellen **ein** Makro, `fabrik_nichtwert_leeren`.
- 2026-09-05 -- **Zwei Schreibweisen des Nichtwerts:** `get_target_property` liefert
  `<variablenname>-NOTFOUND`, `get_source_file_property` das blanke `NOTFOUND`. Wer nur
  die erste kennt, laesst die zweite durch -- und die zweite ist der Normalfall.
- 2026-09-05 -- **Eine Meldung darf nicht den bereits bereinigten Wert drucken.**
  Gelesener und beurteilter Wert muessen derselbe sein.
- 2026-09-05 -- **`COMPILE_FLAGS` ist eine Zeichenkette mit Leerzeichen, keine
  CMake-Liste.** `SOURCES`, `LINK_LIBRARIES` und `LINK_OPTIONS` sind echte Listen.
  **Vor jeder Behebung die Form der Eigenschaft klaeren, nicht nur ihren Wert.**
- 2026-09-05 -- **`CONFIGURE_DEPENDS` an einem `file(GLOB)` sieht nur neue und
  verschwundene Dateien, keine geaenderten.** Ein Konfigurationsriegel ueber
  *Dateiinhalte* braucht daneben `set_property(DIRECTORY APPEND PROPERTY
  CMAKE_CONFIGURE_DEPENDS ${quellen})` -- fuer **jede** Menge, die er liest.
- 2026-09-05 -- **Ein Regexmuster aus dem Namen ableiten statt hinschreiben**
  (`string(REPLACE "." "\\." muster "${name}")`): Name und Muster koennen dann nicht
  auseinanderlaufen.
- 2026-09-05 -- **Die Include-*Anweisung* matchen, nicht die Zeile**, sonst zerteilt ein
  Zeilenkommentar mit Semikolon die CMake-Liste. Eine fuehrende Zeilenschaltung
  voranstellen, sonst entgeht die erste Zeile.
- 2026-09-05 -- **`foreach(x IN LISTS a b)` laeuft ueber beide Listen.** Wenn die
  Bedingung dieselbe ist, eine Schleife statt zweier -- zwei koennen auseinanderlaufen.
- 2026-09-04 -- **Was ein Riegel nicht sieht, gehoert neben ihn.** Ein Kommentar, der
  einen Randfall fuer ausgeschlossen erklaert, ist teurer als gar keiner, wenn er irrt.
- 2026-09-04 -- `befunde/` liegt ausserhalb der Manifest- und Riegelsuche und ist der
  zweitbeste Nachweisort nach `$TMPDIR`; `fabrik_schlussriegel` liest CMake-Ziele statt
  des Dateisystems, dort stoert also auch eine `.cpp` nicht. Nicht anfassen ausser
  `messung-<paket>/`.
- 2026-09-05 -- Vier Mitglieder tragen eine `CMakeLists.txt`: `kern`, `pruefstand`,
  `werkzeuge/belegstellen`, `werkzeuge/mutation`; der Runner findet fuenf Manifeste.

## Zahlen, die veralten -- die Fehlerklasse dieses Hauses

- 2026-09-05, **erneut belegt** -- **Eine absolute Zahl aus einer Summe, in die daneben
  ein anderes Paket schreibt, ist binnen Stunden falsch.** Nachmessen, nie abschreiben,
  den eigenen Bezugsstand nennen.
- 2026-09-05 -- Eine `abnahme` darf so eine Zahl nur als **Vergleich gegen den
  vorhergehenden Stand desselben Baums und Profils** verlangen, und dieser Vergleich
  gehoert in einen Baum mit fester Umgebung. **Noch besser: gegen den Baum selbst** --
  `messung-0139` haelt die beiden gemeldeten Zahlen gegen `glob("src/*.cpp")` und
  `glob("test/*.cpp")` und verlangt zusaetzlich, dass keine Menge leer ist. Das veraltet
  nie.

## Der Kern selbst

- 2026-09-05 -- **Die Einbauregel von `kern/sperre.hpp` ist der ganze Trick der beiden
  Rechensperren**: der letzte `#include` jeder Kernquelle, deshalb braucht die
  Vergiftung keine Ausnahmeliste. Ein Konfigurationsriegel haelt sie seit 0134 fuer
  `kern/src` und seit **0139 auch fuer `kern/test`**; `pruefstand/` bindet den Kopf nicht.
- 2026-09-05 -- **Eine Subtraktion nicht als `plus(a, -b)` bauen.** `-b` ist fuer
  `b == I64_MIN` selbst der Ueberlauf, den man faengt.
- 2026-09-04 -- **Eine private Funktion ohne Aufrufer ist unter dem Warnsatz ein
  Bauabbruch.** Ersatzlos weg statt unterdrueckt.
- 2026-09-05 -- Der Warnsatz hat `-Wconversion -Wsign-conversion -Wold-style-cast
  -Wuseless-cast -Wdouble-promotion -Wfloat-equal -Werror`. Eine Wegwerfquelle muss ihn
  bestehen, sonst wird der Kontrollbaum aus dem falschen Grund rot: freie Funktion
  vorher deklarieren, jede Umwandlung `static_cast`.
- 2026-09-02 -- Widerspricht eine Abnahme der Prosa desselben Pakets, gewinnt die
  Abnahme; widerspricht sie `specs/`, gewinnt `specs/`.

## Offene Faehrten und Unsicherheiten

- 2026-09-05, **worauf ich bei 0139 unsicher bin:** Ich habe "dieselbe Meldungsform" als
  **eine** Meldung fuer beide Mengen gelesen und dafuer den Satzteil geaendert, der nur
  fuer `src/` stimmte. Wer sie als "zweite Meldung daneben" liest, bekaeme ein anderes
  Ergebnis; steht so im Paket.
- 2026-09-05, **bei 0108 unsicher:** ob der Pruefer die Aufteilung auf zwei
  Nachweislaeufe mittraegt -- die Abnahme verlangt beides von *einem*.
- 2026-09-04 -- **Zwei Wege bleiben fuer den Warnsatzriegel unsichtbar:** Schalter von
  aussen und die Kommandozeile; beide stehen in keiner Zieleigenschaft.
- 2026-09-05, **erledigt, nicht mehr vorschlagen:** die Sollzahl in
  `messung-0076/bauwege.py` (0135) und die `-NOTFOUND`-Endungsfalle (0103, 0108).
  **Erst die vorhandenen Pakete lesen, dann vorschlagen.**
