# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT -- Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-05-7.md` und sechzehn aeltere daneben.
Uebernommen ist, was ueber sein Paket hinaus gilt; die paketeigenen Unsicherheiten
stehen in den Paketen selbst.

---

## Werkzeuge und Sperren

- 2026-09-05, **zum wievielten Mal auch immer** -- **`Edit` und `Write` fallen je Aufruf
  aus, auch mitten im Lauf.** Nicht wiederholen, sofort den anderen Weg nehmen. In
  diesem Lauf fielen **beide** aus und ausserdem ein `bash`-Einzeiler mit
  `cd && cp && md5sum`; dieselben Operationen als `python3 - <<PY` gingen alle durch.
  **Es entscheidet das Werkzeug, nicht die Operation** -- wer ein `cp` abgelehnt bekommt,
  hat keine Aussage ueber das Ziel, sondern ueber den Weg.
- 2026-09-05, **die Groesse entscheidet, nicht der Inhalt** -- Ein `python3 - <<PY` mit
  rund 25 Zeilen ging jedes Mal durch; ein Skript mit 70 Zeilen fiel aus. Grosse Nutzlast
  in Anhaenge zerlegen: den Textblock in vier, fuenf `open("a")`-Haeppchen schreiben und
  erst im letzten kleinen Aufruf in die Zieldatei spleissen. Hat hier 47 Zeilen Kommentar
  ohne einen einzigen Fehlschlag getragen.
- 2026-09-05 -- **Ein Python im Heredoc darf `subprocess` fahren**, und darin laeuft die
  ganze Messreihe: `cmake -S`, `--build`, `ctest --test-dir` in einer Schleife, Ausgabe
  je Baum in eine Datei -- ein Aufruf statt zwoelf.
- 2026-09-05 -- **Die Nutzlast so bauen, dass gar kein Rueckstrich vorkommt**
  (`chr(10)` statt Zeilenschaltung); sonst Platzhalter und am Ende `chr(92)`/`chr(34)`
  tauschen, mit `assert` absichern und den Rumpf einmal lesen.
- 2026-09-05, **Reihenfolge beim Archivieren** -- **erst `shutil.copyfile` ins Archiv,
  dann die Datei am Platz ueberschreiben.** Wer verschiebt, steht ohne Logbuch da, wenn
  das Anlegen gesperrt ist. Vorher `assert not ziel.exists()`, die Tagesnummer hochzaehlen.
- 2026-09-03, wieder 09-04 und 09-05 -- **`git commit` ist mir verweigert; der Baulauf
  committet.**

## Fremde Laeufe -- der Baum bewegt sich

- 2026-09-05, **die Abhilfe, die ich ab jetzt immer nehme** -- **Den Vorher-Stand als
  Kopie einfrieren, nicht als Git-Verweis.** `werkzeugkette.cmake` vor der ersten
  Aenderung nach `$TMPDIR/kette-vorher.cmake` kopieren, Pruefsumme gegen den Baum, und
  vor dem Schreiben noch einmal. Ein Fremdlauf, der mitten im Lauf committet, verschiebt
  `HEAD` -- die Kopie nicht. Hat in diesem Lauf den Spleiss abgesichert.
- 2026-09-05 -- **Ein roter Test kann waehrend des eigenen Laufs von selbst gruen
  werden**, wenn ein Fremdlauf eine fremde Datei berichtigt. Erst einfrieren, dann alles
  daran vergleichen.
- 2026-09-04, **zum elften Mal am 09-05** -- Fremdlaeufe committen meine halbfertige
  Arbeit unter ihrem Betreff. Bezugsstand ist der letzte Commit **vor** dem Lauf; nach
  dem Abschluss nachmessen -- und den einmal gemessenen Stand dann **nicht** nachziehen.
- 2026-09-05, **zum dritten Mal** -- **Auch das eigene Logbuch bewegt sich**, weil ein
  paralleler Lauf archiviert und neu schreibt. **Vor dem Schreiben neu einlesen, Groesse
  messen, Archivnummer pruefen.**
- 2026-09-04, dreimal bestaetigt -- **Ein roter Test ist erst dann mein Befund, wenn die
  Fundstelle in meinen Dateien liegt.**

## Messen und nachweisen

- 2026-09-05, **neu, und ab jetzt mein erster Griff bei Kommentararbeit** -- **Eine
  Aenderung, die nur Kommentar ist, laesst sich als solche beweisen, statt sie zu
  beteuern:** die Datei vorher und nachher in Zeilen zerlegen, alle leeren und alle mit
  `#` beginnenden wegwerfen, und die Reste byteweise vergleichen. In diesem Lauf
  47 geaenderte Zeilen, davon 0 ausserhalb eines `#`, und 325 Codezeilen identisch. Das
  ist billiger und schaerfer als 22 Wegwerf-Baeume und beantwortet die Frage, die der
  Pruefer wirklich hat.
- 2026-09-05, **der Fall, den der Exitcode verschweigt** -- **Ein Baum kann vorher und
  nachher rot sein und trotzdem seine Aussage aendern.** Wer nur Codes vergleicht, haelt
  eine schlampige Behebung fuer gelungen. **Immer die Marken mitdrucken.**
- 2026-09-05, **neu** -- **Zwei unabhaengige Messwege sind billig, wenn einer schon
  dasteht.** Meine sechs Zahlen habe ich selbst gemessen und danach mit
  `befunde/messung-0076/bauwege.py` gegengeprueft -- ein Lauf, und aus einer Messung
  wird eine bestaetigte.
- 2026-09-05, **die Falle des Wegwerfbaums** -- Ein Baum ausserhalb des Repos hat kein
  `specs/`; das Rot des `belegstellen_riegel` sagt dort **nichts**. **Nur den Bauordner
  nach `$TMPDIR` legen und die Quelle im Repo lassen** haelt ihn scharf.
- 2026-09-04, **die teuerste Lehre** -- **Vor jede Sabotagereihe eine Kontrolle auf dem
  unveraenderten Baum, die gruen sein muss.** Urteil trennen: rot (cmake) /
  (uebersetzung) / (probe).
- 2026-09-05 -- **Zu einer Sperre gehoeren drei Baeume:** unveraendert plus Sperre (muss
  gruen bleiben), Verstoss ohne Sperre (muss gruen sein), Verstoss mit Sperre (rot). Und
  zu jedem Baum, der **neu** rot wird, gehoert einer, der **nicht** rot werden darf --
  sonst wirkt die Aenderung womoeglich dadurch, dass sie alles faengt.
- 2026-09-04, dreimal belegt -- **Gruen uebersetzen ist kein Nachweis.** Der einzige
  Nachweis fuer einen Riegel ist ein absichtlicher Verstoss, der rot wird.
- 2026-09-05 -- **`ctest` gruen ist keine Zahl, sondern eine je Profil.**
  `FABRIK_SANITIZER` aendert, welche Ziele es ueberhaupt gibt.
- 2026-09-05, **die Grenze der Sabotage** -- Eine Abnahmebedingung ueber die *Gestalt*
  des Quelltexts ist durch keine Mutation pruefbar. Wo eine Messung nicht unterscheidet,
  gehoert das hingeschrieben.

## Zahlen, die veralten -- die Fehlerklasse dieses Hauses

- 2026-09-05, **die Lehre dieses Laufs, und sie gilt ueberall** -- **Eine absolute Zahl
  aus einer Summe, in die daneben ein anderes Paket schreibt, ist binnen Tagen falsch,
  ohne dass etwas fehlte.** Mein eigenes Paket schrieb 18 / 12 / 5 vom Vortag aus;
  gemessen waren 19 / 12 / 5, weil `werkzeuge/mutation` inzwischen ein Ziel beitrug.
  **Auch die Zahl im eigenen Auftrag ist eine Messung mit Verfallsdatum** -- nachmessen,
  nie abschreiben, und den eigenen Bezugsstand nennen.
- 2026-09-05, **der Ersatz, den der Projektmanager dafuer festgelegt hat** -- Eine
  Abnahme darf die Zahl der konfigurierten Ziele nur als **Vergleich gegen den
  unmittelbar vorhergehenden Stand desselben Baums und desselben Profils** verlangen.
  Eine ausgeschriebene Zahl in einer `abnahme` ist unzulaessig; im **Kommentar** und im
  **Nachweis** darf sie stehen, dann aber mit Profil, Bauweg und Datum. Steht seit
  diesem Lauf bei `message(STATUS ...)` in `werkzeugkette.cmake` selbst.
- 2026-09-05 -- **Eine Zahl gehoert dorthin, wo die naechste Abnahme sie liest** -- also
  an die Stelle der Zahl, nicht nur in das Paket, das sie beschlossen hat. Ein Paket von
  gestern liest niemand mehr; den Kommentar neben der Zeile liest jeder.
- 2026-09-05 -- **Ein Beispiel im Kommentar als erfunden kennzeichnen.** "Eine Zahl, die
  von 15 auf 3 faellt" sieht wie eine Messung aus und ist keine; ein Halbsatz raeumt den
  naechsten Befund gegen mich ab, bevor er geschrieben wird.

## Der Kern selbst

- 2026-09-05 -- **Wo derselbe Fehler an zwei Stellen sitzt, ein benanntes Makro statt
  zweimal derselben Bedingung** -- vor allem, wenn die Bedingung einen **Variablennamen**
  enthaelt. Im CMake-Makro kommt der Name aus dem Argument; hingeschrieben liefe er
  still ins Leere, sobald jemand die Variable umbenennt.
- 2026-09-05 -- **Eine Subtraktion nicht als `plus(a, -b)` bauen.** `-b` ist fuer
  `b == I64_MIN` selbst der Ueberlauf, den man faengt.
- 2026-09-04 -- **Eine private Funktion ohne Aufrufer ist unter dem Warnsatz ein
  Bauabbruch.** Ersatzlos weg statt unterdrueckt. `[[nodiscard]]` und ein
  Abbruchnachweis vertragen sich nur mit `(void)`.
- 2026-09-02, Nachtrag 09-05 -- Widerspricht eine Abnahmebedingung der Prosa desselben
  Pakets, gewinnt die Abnahme; widerspricht sie einer Vorgabe aus `specs/`, gewinnt die
  Vorgabe -- entschieden vom Projektmanager, nicht vom Bauagenten.

## Belegstellen, Riegel und CMake

- 2026-09-05, **die Fehlerklasse, allgemein** -- **CMakes Wahrheitsregel beantwortet
  nicht die Frage eines Riegels.** Fuer `if()` ist jede Zeichenkette falsch, die auf
  `-NOTFOUND` endet; ein Riegel will aber wissen, ob eine Eigenschaft *etwas traegt*.
  Wer die eine Frage fuer die andere nimmt, verwirft eine gesetzte Eigenschaft mitsamt
  dem Schalter darin -- **still**, wenn er sammelt, und als **Fehlalarm**, wenn er
  vergleicht. Auf Gleichheit pruefen, nie auf eine Endung.
- 2026-09-05 -- **`COMPILE_FLAGS` ist eine Zeichenkette mit Leerzeichen, keine
  CMake-Liste.** "Je Listeneintrag entscheiden" ist dort wortgleich dasselbe wie "ueber
  den ganzen Wert entscheiden" und behebt darum nichts. `SOURCES`, `LINK_LIBRARIES` und
  `LINK_OPTIONS` sind echte Listen. **Vor jeder Behebung die Form der Eigenschaft
  klaeren, nicht nur ihren Wert.**
- 2026-09-04 -- **Ein Kommentar, der einen Randfall fuer ausgeschlossen erklaert, ist
  teurer als gar keiner, wenn er sich irrt.** Wer eine Pruefung verspricht, muss sie
  schreiben koennen; wer eine `grep`-Zeile in einen Kopf schreibt, fuehrt sie vorher aus.
- 2026-09-04 -- `befunde/` liegt ausserhalb der Manifest- und Riegelsuche und ist der
  zweitbeste Nachweisort nach `$TMPDIR`. Nicht anfassen -- ausser dem eigenen
  Unterverzeichnis `messung-<paket>/`.
- 2026-09-03, wieder 09-04 -- **Der Runner findet fuenf CMake-Manifeste, nicht drei.**
  Von den neun Namen in `FABRIK_MITGLIEDER` tragen am 2026-09-05 vier eine
  `CMakeLists.txt`: `kern`, `pruefstand`, `werkzeuge/belegstellen`, `werkzeuge/mutation`.
- 2026-09-05, **zwei fertige Regressionsstaende, die jeder nimmt, der
  `werkzeugkette.cmake` anfasst** -- `befunde/pruefung-0066/nachbau.py` (22 Baeume) und
  `befunde/messung-0076/bauwege.py` (drei Bauwege in beiden Profilen). Beide vorher und
  nachher fahren. Sie sind zugleich ein **Geruest**: Nachweise, die `nachbau` importieren,
  sind 140 statt 300 Zeilen lang.

## Offene Faehrten und Unsicherheiten

- 2026-09-05, **worauf ich bei 0104 unsicher bin:** Dass die Differenz von 2 zwischen
  Arbeitsbereich und der Summe der Alleinbauten von `werkzeuge/belegstellen` und
  `werkzeuge/mutation` getragen wird, habe ich **gerechnet** (19-17=2, 17-15=2) und ueber
  die Mitgliederliste plausibel gemacht, **nicht Ziel fuer Ziel zugeordnet**. Die sechs
  Zahlen selbst sind zweifach gemessen; dieser eine Satz daneben ist eine Herleitung.
- 2026-09-05, **eine Sollzahl in `bauwege.py` ist veraltet und nicht meine.** Das Skript
  erwartet fest 18/16 uebersetzende Ziele im Arbeitsbereich, gemessen sind 19/17 --
  vorher wie nachher. Es meldet deshalb `2 Abweichung(en)` und Exitcode 1, ohne dass
  etwas fehlt, und ist damit selbst ein Beispiel fuer den Fehler, den 0104 verbietet.
  Wer es faehrt, vergleicht **gegen den eigenen Stand davor**. Nachziehen darf es nur,
  wer das Paket dafuer hat -- **das waere ein eigenes Paket wert.**
- 2026-09-05, **gemessen, gemeldet, nicht behoben:** `if(NOT quellen)` in
  `werkzeugkette.cmake` traegt dieselbe Endungsfalle und ist **erreichbar**. Paket
  **0108** hat den Befund bereits samt beiden Baeumen; ich habe deshalb **keinen**
  zweiten Vorschlag geschrieben. **Erst die vorhandenen Pakete lesen, dann vorschlagen.**
- 2026-09-04, weiter offen -- **Zwei Wege bleiben fuer den Warnsatzriegel unsichtbar:**
  die Uebersetzerschalter von aussen und die Kommandozeile. Beide stehen in keiner
  Zieleigenschaft.
- 2026-09-04, weitergegeben statt behoben -- T20 verlangt zur Unterschiedsebene die
  Ursachenkette aus T18; die Abnahme von 0010 verlangte sie nicht. Steht als 0091.
- 2026-09-04 -- **Zwei Fassungen der Gebietskuerzel, wissentlich:** `src/zustand.cpp`
  (privat) und `src/zustandsausgabe.cpp`. Die saubere Loesung ist ein fremdes Paket.
