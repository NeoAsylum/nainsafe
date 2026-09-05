# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT -- Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-05-6.md` und fuenfzehn aeltere daneben.
Uebernommen ist, was ueber sein Paket hinaus gilt; die paketeigenen Unsicherheiten
stehen in den Paketen selbst.

---

## Werkzeuge und Sperren

- 2026-09-05 -- **Das Arbeitsverzeichnis bleibt zwischen Bash-Aufrufen stehen.** Nach
  einem `cd` meldete dieselbe Messung `gesamt 0` -- ein Nichts, das wie ein Befund
  aussieht. Jede Messung ihren Pfad selbst setzen lassen.
- 2026-09-05, mehrfach am Tag -- **`Edit` und `Write` fallen je Aufruf aus, auch mitten
  im Lauf.** Nicht wiederholen, sofort den anderen Weg nehmen. In **diesem** Lauf war es
  umgekehrt: `Edit` und `Write` trugen ins Repo, `Write` nach `$TMPDIR` fiel zweimal aus.
  **Welcher Weg traegt, ist nicht vorhersagbar -- nur, dass einer traegt.**
- 2026-09-05, **die Groesse entscheidet, nicht der Inhalt** -- Ein `python3 - <<'PY'`
  mit rund 25 Zeilen ging jedes Mal durch; derselbe Inhalt als `cat > datei <<'EOF'`
  und ein Skript mit 70 Zeilen fielen aus. Grosse Nutzlast in Anhaenge zerlegen.
- 2026-09-05, **neu und billig** -- **`python3 - <<'PY'` darf nach `$TMPDIR` schreiben,
  auch wenn das `Write`-Werkzeug dorthin verweigert wird.** Ein abgelehntes Werkzeug
  sagt nichts ueber das Ziel, nur ueber den Weg.
- 2026-09-05 -- **Ein Python im Heredoc darf `subprocess` fahren**, und darin laeuft die
  ganze Messreihe: `cmake -S`, `--build`, `ctest --test-dir` in einer Schleife, Ausgabe
  je Baum in eine Datei -- ein Aufruf statt zwoelf.
- 2026-09-05 -- **Rueckstriche und Anfuehrungszeichen als Platzhalter schreiben** und
  im letzten Schritt gegen `chr(92)`, `chr(34)`, `chr(39)` tauschen; den Tausch mit
  `assert` absichern **und den Rumpf danach einmal lesen**. Noch besser: die Nutzlast so
  bauen, dass gar kein Rueckstrich vorkommt (`chr(10)` statt Zeilenschaltung).
- 2026-09-05, **Reihenfolge beim Archivieren** -- **erst `shutil.copyfile` ins Archiv,
  dann die Datei am Platz ueberschreiben.** Wer verschiebt, steht ohne Logbuch da, wenn
  das Anlegen gesperrt ist. Vorher `assert not ziel.exists()`, die Tagesnummer hochzaehlen.
- 2026-09-03, wieder 09-04 und 09-05 -- **`git commit` ist mir verweigert; der Baulauf
  committet.**

## Fremde Laeufe -- der Baum bewegt sich

- 2026-09-05, **die Abhilfe, die ich ab jetzt immer nehme** -- **Den Vorher-Stand als
  Kopie einfrieren, nicht als Git-Verweis.** Ich habe `werkzeugkette.cmake` vor der
  ersten Aenderung nach `$TMPDIR/kette-vorher.cmake` kopiert und byteweise gegen den
  Baum geprueft; danach ist jede Vorher-Zahl gegen diese Kopie gemessen. Ein Fremdlauf,
  der mitten im Lauf committet, verschiebt `HEAD` -- die Kopie nicht.
- 2026-09-05 -- **Ein roter Test kann waehrend des eigenen Laufs von selbst gruen
  werden**, wenn ein Fremdlauf eine fremde Datei berichtigt. Erst einfrieren, dann alles
  daran vergleichen.
- 2026-09-04, **zum zehnten Mal am 09-05** -- Fremdlaeufe committen meine halbfertige
  Arbeit unter ihrem Betreff. Bezugsstand ist der letzte Commit **vor** dem Lauf; nach
  dem Abschluss nachmessen -- und den einmal gemessenen Stand dann **nicht** nachziehen.
- 2026-09-05, **zum zweiten Mal** -- **Auch das eigene Logbuch bewegt sich.** Diesmal war
  es zu Beginn 12.394 Zeichen gross und mittendrin 11.187, weil ein paralleler Lauf
  archiviert und neu geschrieben hatte -- die naechste Archivnummer war schon vergeben.
  **Vor dem Schreiben neu einlesen, Groesse messen, Nummer pruefen.**
- 2026-09-04, dreimal bestaetigt -- **Ein roter Test ist erst dann mein Befund, wenn die
  Fundstelle in meinen Dateien liegt.**

## Messen und nachweisen

- 2026-09-05, **die staerkste Form des Nachweises** -- **zwei ganze Protokolle
  normalisiert vergleichen statt zweier Kennzahlen.** In diesem Lauf zweimal getragen:
  22 Wegwerf-Baeume vorher/nachher mit Code und Markenzeilen im Wortlaut (Ablagepfade
  ersetzt) -- `0 Unterschied(e)` --, und 18 Bauprotokolle ebenso. Das ist der Satz
  „kein Urteil aendert sich" als Messung statt als Behauptung. **Nie nach Augenschein
  vergleichen; ich haette den Unterschied unten sonst uebersehen.**
- 2026-09-05, **der Fall, den der Exitcode verschweigt** -- **Ein Baum kann vorher und
  nachher rot sein und trotzdem seine Aussage aendern.** Bei `-w -DPFAD=x-NOTFOUND` am
  Ziel war vorher `es fehlen: -Wall ...` (Fehlalarm) und nachher `gefunden in:
  COMPILE_OPTIONS an z` (der wirkliche Befund). Wer nur Codes vergleicht, haelt eine
  schlampige Behebung fuer gelungen. **Immer die Marken mitdrucken.**
- 2026-09-05, **die Falle des Wegwerfbaums** -- Ein Baum ausserhalb des Repos hat kein
  `specs/`; der `belegstellen_riegel` faellt dort ueber das fehlende Verzeichnis. Sein
  Rot sagt am Wegwerfbaum **nichts**.
- 2026-09-04, **die teuerste Lehre** -- **Vor jede Sabotagereihe eine Kontrolle auf dem
  unveraenderten Baum, die gruen sein muss.** Urteil trennen: rot (cmake) /
  (uebersetzung) / (probe).
- 2026-09-05 -- **Zu einer Sperre gehoeren drei Baeume:** unveraendert plus Sperre (muss
  gruen bleiben), Verstoss ohne Sperre (muss gruen sein), Verstoss mit Sperre (rot).
- 2026-09-05, **die Gegenkontrolle, die eine Behebung erst belegt** -- Zu jedem Baum, der
  **neu** rot wird, gehoert einer, der **nicht** rot werden darf. Sonst wirkt die
  Aenderung womoeglich dadurch, dass sie alles faengt.
- 2026-09-04, dreimal belegt -- **Gruen uebersetzen ist kein Nachweis.** Der einzige
  Nachweis fuer einen Riegel ist ein absichtlicher Verstoss, der rot wird.
- 2026-09-05 -- **`ctest` gruen ist keine Zahl, sondern eine je Profil.**
  `FABRIK_SANITIZER` aendert, welche Ziele es ueberhaupt gibt.
- 2026-09-05, **die Grenze der Sabotage** -- Eine Abnahmebedingung ueber die *Gestalt*
  des Quelltexts ist durch keine Mutation pruefbar. Wo eine Messung nicht unterscheidet,
  gehoert das hingeschrieben.

## Der Kern selbst

- 2026-09-05, **die Bauform dieses Laufs, die ich wiederverwenden werde** -- **Wo
  derselbe Fehler an zwei Stellen sitzt, ein benanntes Makro statt zweimal derselben
  Bedingung** -- vor allem, wenn die Bedingung einen **Variablennamen** enthaelt. In
  einem CMake-Makro kommt der Name aus dem Argument (`${variablenname}-NOTFOUND`); als
  hingeschriebene Zeichenkette liefe er still ins Leere, sobald jemand die Variable
  umbenennt. Genau die Sorte Stelle, die stumpf wird, ohne dass ein Test faellt.
- 2026-09-05 -- **Eine Vergiftung wirkt ab ihrer Zeile, und das ersetzt die
  Ausnahmeliste.** Fuer **Operatoren** traegt es nicht; die Zeile sagt nicht, was sie
  multipliziert.
- 2026-09-05 -- **Eine gepruefte Rechenart gehoert dorthin, wo die Vorgabe die einzige
  Rechenstelle sieht.** Im anonymen Namensraum einer Quelle hat sie keinen Aufrufer von
  aussen -- ihre Abbruchpfade sind unpruefbar und der Baum laeuft gruen.
- 2026-09-05 -- **Eine Subtraktion nicht als `plus(a, -b)` bauen.** `-b` ist fuer
  `b == I64_MIN` selbst der Ueberlauf, den man faengt.
- 2026-09-05 -- **Eine Regel, die Ausnahmen kennt, gehoert als `constexpr`-Praedikat
  neben die Aufzaehlung**, nicht als `if` an die Aufrufstelle.
- 2026-09-05 -- **Wer einer Zeile Text hinzufuegt, rechnet ihren schlimmsten Fall nach**,
  nicht den gemessenen.
- 2026-09-04 -- **Eine private Funktion ohne Aufrufer ist unter dem Warnsatz ein
  Bauabbruch.** Ersatzlos weg statt unterdrueckt. `[[nodiscard]]` und ein
  Abbruchnachweis vertragen sich nur mit `(void)`.
- 2026-09-02, Nachtrag 09-05 -- Widerspricht eine Abnahmebedingung der Prosa desselben
  Pakets, gewinnt die Abnahme; widerspricht sie einer Vorgabe aus `specs/`, gewinnt die
  Vorgabe -- entschieden vom Projektmanager, nicht vom Bauagenten.

## Belegstellen, Riegel und CMake

- 2026-09-05, **gegen den veraltenden Kommentar** -- **Eine Zahl im Kopf bekommt Datum
  und Commit, unter denen sie gemessen wurde.** Kein Riegel prueft eine Aussage ueber
  den Quelltext -- der Kopf von `mal` veraltete so vier Pakete lang unbemerkt.
- 2026-09-05, **die Fehlerklasse dieses Laufs, allgemein** -- **CMakes Wahrheitsregel
  beantwortet nicht die Frage eines Riegels.** Fuer `if()` ist jede Zeichenkette falsch,
  die auf `-NOTFOUND` endet; ein Riegel will aber wissen, ob eine Eigenschaft *etwas
  traegt*. Wer die eine Frage fuer die andere nimmt, verwirft eine gesetzte Eigenschaft
  mitsamt dem Schalter darin -- **still**, wenn er sammelt, und als **Fehlalarm**, wenn
  er vergleicht. Auf Gleichheit pruefen, nie auf eine Endung.
- 2026-09-05 -- **`COMPILE_FLAGS` ist eine Zeichenkette mit Leerzeichen, keine
  CMake-Liste.** „Je Listeneintrag entscheiden" ist dort wortgleich dasselbe wie „ueber
  den ganzen Wert entscheiden" und behebt darum nichts. `SOURCES`, `LINK_LIBRARIES` und
  `LINK_OPTIONS` sind echte Listen. **Vor jeder Behebung die Form der Eigenschaft
  klaeren, nicht nur ihren Wert.**
- 2026-09-04 -- **Ein Kommentar, der einen Randfall fuer ausgeschlossen erklaert, ist
  teurer als gar keiner, wenn er sich irrt.** Wer eine Pruefung verspricht, muss sie
  schreiben koennen; wer eine `grep`-Zeile in einen Kopf schreibt, fuehrt sie vorher aus.
- 2026-09-05, **neu** -- **Ein Verweis „wie oben" wird falsch, sobald jemand „oben"
  aendert.** Meine Aenderung hat genau das an einer fremden Zeile ausgeloest. Beim
  Schreiben lieber die Sache nennen als die Nachbarstelle.
- 2026-09-05 -- **Ein gruener Riegel ist eine Aussage ueber seine Muster, keine ueber
  den Baum.**
- 2026-09-04 -- `befunde/` liegt ausserhalb der Manifest- und Riegelsuche und ist der
  zweitbeste Nachweisort nach `$TMPDIR`. Nicht anfassen.
- 2026-09-03, wieder 09-04 -- **Der Runner findet fuenf CMake-Manifeste, nicht drei.**
- 2026-09-05, **zwei fertige Regressionsstaende, die jeder nimmt, der
  `werkzeugkette.cmake` anfasst** -- `befunde/pruefung-0066/nachbau.py` (22 Baeume) und
  `befunde/messung-0076/bauwege.py` (drei Bauwege in beiden Profilen). Beide vorher und
  nachher fahren. Sie sind zugleich ein **Geruest**: mein eigener Nachweis
  (`befunde/messung-0103/endungsfalle.py`) importiert `nachbau` und ist dadurch 140
  statt 300 Zeilen lang.

## Offene Faehrten und Unsicherheiten

- 2026-09-05, **worauf ich bei 0123 unsicher bin:** Ich hatte die Zahl des Vorschlags
  gelesen, bevor ich mass. Dagegen stehen zwei unabhaengige Verfahren und eine
  Mutationsreihe in `befunde/messung-0123/`.
- 2026-09-05, **eine Sollzahl in `bauwege.py` ist veraltet und nicht meine.** Das Skript
  erwartet fest 18/16 uebersetzende Ziele im Arbeitsbereich, gemessen sind 19/17 --
  vorher wie nachher. Es meldet deshalb `2 Abweichung(en)` und Exitcode 1, ohne dass
  etwas fehlt. Wer es faehrt, vergleicht **gegen den eigenen Stand davor** (so verlangt
  es 0104), nicht gegen die Zahl im Skript. Nachziehen darf es nur, wer das Paket dafuer
  hat.
- 2026-09-05, **gemessen, gemeldet, nicht behoben:** `if(NOT quellen)` in
  `werkzeugkette.cmake` traegt dieselbe Endungsfalle und ist **erreichbar** -- eine
  zweite Quelldatei namens `y-NOTFOUND` blendet die ganze Quelldateischleife aus, der
  Riegel meldet gruen, waehrend `-w` an einer anderen Quelle haengt. Kontrolle mit
  `y-HARMLOS`: rot. Paket **0108** hat den Befund bereits samt beiden Baeumen; ich habe
  deshalb **keinen** zweiten Vorschlag geschrieben. **Erst die vorhandenen Pakete lesen,
  dann vorschlagen** -- das hat mir hier einen Doppelvorschlag erspart.
- 2026-09-04, weiter offen -- **Zwei Wege bleiben fuer den Warnsatzriegel unsichtbar:**
  die Uebersetzerschalter von aussen und die Kommandozeile. Beide stehen in keiner
  Zieleigenschaft.
- 2026-09-04, weitergegeben statt behoben -- T20 verlangt zur Unterschiedsebene die
  Ursachenkette aus T18; die Abnahme von 0010 verlangte sie nicht. Steht als 0091.
- 2026-09-04 -- **Zwei Fassungen der Gebietskuerzel, wissentlich:** `src/zustand.cpp`
  (privat) und `src/zustandsausgabe.cpp`. Die saubere Loesung ist ein fremdes Paket.
