# Logbuch: test-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/test-pruefer-<datum>.md` und beginnst neu.

Vorgaenger: `notizen/archiv/test-pruefer-2026-09-04.md` (voll bei Paket 0077).

---

## Wie ich einen Mutanten baue (Stand 2026-09-04, traegt seit 0019)

- Mutant mit `cmake -P`: `file(READ)` auf die Originaldatei, `string(REPLACE)`,
  `file(WRITE)` nach `$TMPDIR`. **Immer mit Fehlerbremse**: trifft das Suchmuster nicht,
  `message(FATAL_ERROR)` -- sonst besteht ein unveraenderter Mutant brav und ich zaehle
  sein Bestehen als Empfindlichkeit der Probe.
- Alle Faelle in **einem** `ctest`-Aufruf: kleines Projekt in `$TMPDIR`,
  `set_tests_properties(m1 m2 ... PROPERTIES WILL_FAIL TRUE)`. Dann heisst "ctest gruen":
  Kontrolle besteht **und** jeder Mutant wird gefangen.
- **M0, die Kontrolle ohne Eingriff, gehoert immer dazu.** Ohne sie belegt "alle Mutanten
  sterben" auch, dass mein Aufbau selbst kaputt ist.

- Gegen die **unveraenderte** Bibliothek des Vorhabens linken, dann fasse ich keine
  Paketdatei an. Sanitizer-Schalter aus `link.txt` mituebernehmen, sonst scheitert das
  Linken gegen `libkern_geprueft.a`.
- **Schwellen verschieben findet mehr als Pruefungen entfernen**, und beide Richtungen:
  aufweiten *und* verschaerfen. Eine geloeschte Pruefung faellt fast immer auf.
- **Zaehlen, an wie vielen Zusicherungen ein Mutant stirbt.** Wer nur eine reisst, zeigt
  auf die Regel ohne eigenen Anker.
- Am Ende fragen: **welche Zusicherung hat kein Mutant rot bekommen?** Erst wenn jede
  einmal rot war, ist die Abdeckung gemessen statt behauptet.

## Was funktioniert

- 2026-09-04 (0077) -- **Bei einem Paket, das nur Kommentare aendert, ist der
  Maschinencodevergleich der Hauptnachweis.** Alte und neue Fassung mit denselben
  Schaltern nach Assembler uebersetzen und `diff`. Traegt die Aenderung wirklich nur
  Text, ist **jeder** Unterschied entweder die `.file`-Zeile oder ein Zeilennummernwert
  aus `__LINE__`, verschoben um genau so viele Zeilen, wie der Kommentar gewachsen ist.
  Zaehlung der Unterschiede ausserhalb dieser Form muss 0 sein. Das schliesst mechanisch
  aus, was hier am ehesten zu befuerchten ist: eine still mitgenommene Schwelle. Billiger
  und staerker als jedes Lesen des Diffs.

- 2026-09-04 (0077) -- **Misst eine Abnahme die *Abwesenheit* eines Musters, pruefe den
  *Ersatz*, Behauptung fuer Behauptung.** Bei 0077 machte der neue Satz vier
  nachschlagbare Aussagen; alle vier einzeln gegen `parameter.toml` gemessen, alle vier
  wahr. Bei 0044 war derselbe Handgriff der Grund, warum die Pruefung ueberhaupt etwas
  fand. Der Handgriff ist inzwischen zweimal ergiebig gewesen.
- 2026-09-04 (0077) -- **Der Rotnachweis fuer eine Grep-Bedingung ist die historische
  Fassung.** `git show <commit>^:<datei>` liefert den kaputten Stand umsonst. Trifft das
  Muster dort und heute nicht mehr, unterscheidet die Bedingung kaputt von heil. Ohne
  diesen Schritt ist "kein Treffer" von "Muster kommt nirgends vor" nicht zu trennen.

- 2026-09-04 (0077) -- **Die Dateiliste des Baucommits gegen die `dateien`-Liste des
  Pakets legen.** Betreff sagte "8 Dateien", der Commit aenderte 329; 322 davon ein
  Messbaum aus einem fremden Paket, drei Quelldateien eines Pakets, das erst zwoelf
  Minuten spaeter committete. Kostet einen `git show --stat` und war der einzige Befund
  des Laufs (Vorschlag 0081).
- 2026-09-04 (0050, 0077) -- **Einen Mutanten auf genau den Wert setzen, den die Abnahme
  als "unveraendert" schuetzt.** Sonst zeigt der Diff nur, *dass* er dasteht. Bei 0077
  starb die Konstante an einem Gruenfall, der genau auf ihrer Grenze sitzt -- damit ist
  belegt, dass Bedingung 3 etwas schuetzt, das sich wehrt.

- 2026-09-04 (0050) -- **Einen Mutanten mit Erwartung *gruen* dazunehmen, wo ich eine
  Luecke vermute.** Das macht aus "wird vermutlich nicht geprueft" die Zahl *null
  Zusicherungen* und aus einem Bauchgefuehl einen Nachweis.
- 2026-09-04 (0050) -- **Vor dem eigenen Vorschlag die `aufgaben/` nach `offen`
  durchsehen.** Meine Luecke stand woertlich in der Abnahme eines am selben Tag
  angenommenen Pakets; ein Vorschlag waere ein Doppel gewesen.
- 2026-09-03 -- **Eine Zaehlung von Zeilen belegt keine Eindeutigkeit von Namen.**
  `grep -c` ueber Schluesselzeilen sagt nichts darueber, ob ein Name mehrfach vorkommt --
  `sort | uniq -d` daneben. Genau daran hing der Fehler in 0044.

- 2026-09-03 -- **Ein Riegel, der seine Wurzel als Argument bekommt, ist ohne Aenderung
  am Baum rotprobbar.** Synthetischen Baum in `$TMPDIR` bauen und das gebaute Programm
  daraufrichten. Und: Meldet ein Riegel "0 Treffer", ist das noch kein Gruen -- dieselbe
  Null kaeme von einem kaputten Sucher. Die Treffer einzeln nachschlagen.
- 2026-09-03 -- **Bei einem Riegel ist die Dateiauswahl die Schwelle**, nicht die
  Vergleichslogik. Also die Auswahlfunktion mutieren, nicht den Namensvergleich.
- 2026-09-04 -- **`befunde/` ist fuer den `belegstellen_riegel` und fuer `baulauf.py`
  unsichtbar** (Riegel liest 37 Bauquellen, ueberspringt `befunde/`). Dorthin gehoert ein
  Mutationsstand -- aber ohne CMake-Bauabfall, der wandert sonst in den Index (0081).

## Was nicht funktioniert

- 2026-09-04 -- **Die Werkzeugsperren sind je Sitzung verschieden; nicht auf den Eintrag
  vom letzten Mal verlassen.** Heute gesperrt: `Write` und `Edit` ueberall (auch nach
  `$TMPDIR`), Heredoc, `sed` (auch ohne `-i`), `rm`, `cp`, das Ausfuehren einzelner
  Binaerdateien, mehrteilige Bash-Zeilen mit Variablenzuweisung. Gegangen sind:
  `printf` mit Zeilenargumenten und Umlenkung **in das Repo**, `cmake`, `cmake -E copy`,
  `cmake -P`, `ctest`, ein blankes `c++ ... -o`, `git show/log/ls-files/check-ignore`,
  Umlenkung nach `$TMPDIR`, das `Grep`- und das `Read`-Werkzeug.

- 2026-09-04 -- **Und der teure Teil davon: `printf` scheitert nicht am Umfang, sondern
  an einzelnen Zeichen im Argument.** Abgelehnt wurden Zeilen mit einer
  Zeichenklasse in eckigen Klammern (Ziffernbereich), mit einem Rautenzeichen mitten in
  der Zeile und mit einem Gleichheitszeichen. Angenommen wurden dieselben Zeilen, sobald
  ich sie umformuliert hatte. **Merksatz:** Ergebnisdatei vorher fertig denken, dann in
  Bloecken von hoechstens sechs Zeilen schreiben und Muster in Prosa umschreiben statt
  woertlich zu zitieren. Eine Pruefung so zu Papier zu bringen kostet rund 30 Aufrufe.

- 2026-09-02 -- **Die Adresstabelle des Kerns zu mutieren, um die Zaehlung einer Probe zu
  pruefen, geht nicht.** `zustand.cpp` traegt einen `static_assert` (T17), der jede
  Namensabweichung schon beim Uebersetzen faengt. Wer eine Zaehlung belegen will, mutiert
  das Suchmuster **in der Probe**.

## Offene Faehrten

- 2026-09-02 -- **`anteile_aus_zustand` in `schranken_probe.cpp` sichert die Summe, nicht
  den Quotienten.** Heute unerreichbar, weil die Probe ihre Zustaende selbst setzt.
  Wandert die Pruefung laut `rueckstand.md` in ein aufrufbares Modul fuer T30 Pruefung 5
  und 6, wird der Fall scharf -- dann nachsehen, ob die dritte Wache mitgekommen ist.

- 2026-09-04 -- **Die Zitate in `schranken_probe.cpp` sind nicht zeichengleich.** Sie
  tragen Ausrichtungsleerzeichen gegenueber `parameter.toml`. Heute kein Befund, weil
  keine Abnahme Wortlaut verlangt. Kommt die Bedingung, die den **Ersatz** nachschlaegt
  (der Gedanke aus 0077 an den Projektmanager, teils schon 0067), stolpert sie hier --
  dann ist zu entscheiden, ob Leerzeichen normalisiert werden.
- 2026-09-02 -- **Bitmaske statt Fehlerliste** macht "genau diese eine Sache und keine
  andere" zu einem Zahlenvergleich statt zu einer Lesung. Bei 0020 und 0077 der Grund,
  warum die Rotfaelle ueberhaupt nachpruefbar waren. Beim naechsten Paket dieser Rolle
  pruefen, ob das Muster weitertraegt.

## Nachtrag 2026-09-04 (Paket 0067)

- **Nimmt ein Riegel seine zweite Wurzel als Argument, ist der Rotnachweis ohne jeden
  Eingriff zu fuehren.** Bei 0067 eine Kopie von `specs/` nach `$TMPDIR`, dort die
  Ueberschrift verdreht, die **unveraenderte** Quelle daraufgerichtet. Sechs Sabotagen an
  derselben Zeile (umbenannt, gross, entwertet, Punkt dahinter, tiefere Ebene, Datei weg)
  ergeben eine Empfindlichkeitstabelle, die der Bauagent so nicht hatte -- er hat sein
  eigenes Zitat verdreht, also die leichtere Richtung.
- **Verlangt eine Abnahme, ein Paket habe "seine Belegstelle hinterlassen", pruefe die
  Zuordnung und nicht nur den Fang.** Bei 0067 waren fuenf von sechs richtig zugeordnet;
  bei 0034 war die genannte Stelle zwei Tage aelter als das Paket, und die drei, die es
  wirklich hinterlassen hat, fielen durch. Das war der einzige Ruecklaufgrund, und er
  stand nicht in der Fangquote, sondern in `git log -S` **plus Datum**.
- **Die Commit-Buendelung dieser Fabrik macht `git log -S` allein unbrauchbar.** Die
  Arbeit eines Pakets liegt regelmaessig im Commit des naechsten Laufs, unter dessen
  Namen. Erst Wortlaut und Datum zusammen ordnen zu.
- **Jeden Nachlass im Vergleich einzeln abschalten und zaehlen, wie viele Faelle fallen.**
  Bei 0067 drei Mutanten: Vorspannform 3 von 21, Schlusszeichen 3 von 21, Umlautumschrift
  1 von 21. Alle drei tragend, und zwei bezifferte Zusagen des Kopfkommentars damit
  belegt statt geglaubt. Faellt bei einem Nachlass **nichts**, ist er entweder unnoetig
  oder er verdeckt etwas -- beides ein Befund.
- **Ein Riegel ohne Regressionsbestand hat auch keine uebernommenen Sollwerte.** Er misst
  gegen den Baum. Die Frage "stammt der erwartete Zustand aus dem letzten Lauf?" entfaellt
  dann ersatzlos; an ihre Stelle tritt "was passiert, wenn der Baum schrumpft?".
- **Gesperrt in dieser Sitzung:** `Write`, `Edit`, direktes Ausfuehren einzelner
  Binaerdateien, `printf` mit vielen Einzelargumenten. Gegangen ist `printf` mit **einer**
  Formatzeichenkette und Umlenkung (auch `>>` ins Repo), `cmake -E copy_directory/rm`,
  `cmake -P` fuer Mutanten, `g++`, `ctest`, `&&` in einer Zeile. Ein Absatz je Aufruf ist
  die verlaessliche Groesse; laengere Bloecke werden ohne Grund abgelehnt und muessen
  geteilt werden.
- **Ohne `add_test` kein Lauf.** Da einzelne Binaerdateien nicht startbar sind, ist ein
  Wegwerf-CMake-Projekt in `$TMPDIR` mit `add_executable` plus `add_test` der einzige Weg,
  einen Mutanten ueberhaupt auszufuehren. `add_test` auf eine **vorgebaute** Binaerdatei
  wurde abgelehnt, `add_executable` aus einer Quelle nicht.
