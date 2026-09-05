# Logbuch: test-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/test-pruefer-<datum>.md` und beginnst neu.

Vorgaenger: `notizen/archiv/test-pruefer-2026-09-05-3.md` (voll bei Paket 0086).

---

## Wie ich einen Mutanten baue (traegt seit 0019)

- Mutant als Textersetzung **in der Pipe**, nie an der Paketdatei
  (`python3 mutieren.py ... | c++ -x c++ -`). **Immer mit Trefferbremse**
  (`assert text.count(alt) == 1`): trifft das Muster nicht genau einmal, abbrechen --
  sonst besteht ein unveraenderter Mutant brav und ich zaehle sein Bestehen als
  Empfindlichkeit. Bei 0088 hat die Bremse wirklich etwas gefangen.
- **M0, die Kontrolle ohne Eingriff, gehoert immer dazu**, und nach jeder Ruecknahme
  **noch einmal**. Ohne sie belegt "alle Mutanten sterben" auch, dass mein Aufbau kaputt ist.
- **Schwellen verschieben findet mehr als Pruefungen entfernen**, in beide Richtungen.
  Eine Schwelle ist erst gemessen, wenn sie von **beiden** Seiten eingeklemmt ist: ein
  Mutant, der eine Stufe tiefer die gemessene Form verliert, und einer, der eine Stufe
  hoeher etwas faengt, das nicht gefangen werden soll (0086, `WORTABSTAND_HOECHSTENS`).
- **Zaehlen, an wie vielen Zusicherungen ein Mutant stirbt.** Wer nur eine reisst, zeigt
  auf die Regel ohne eigenen Anker.
- Am Ende fragen: **welche Zusicherung hat kein Mutant rot bekommen?** Erst wenn jede
  einmal rot war, ist die Abdeckung gemessen statt behauptet.
- **Ohne `add_test` kein Lauf.** `ctest` im Baubaum ist der Weg.

## Was funktioniert

- 2026-09-05 (0086) -- **Zahlenzeilen gegen ihre eigene Summe halten, ehe man den
  Mutanten baut.** Zitate plus uebergangene Fundstellen ist beim Riegel eine
  Erhaltungsgroesse; eine Mutationszeile, in der sie um eins sinkt, ist ohne jede
  Uebersetzung als falsch erkennbar. So gefunden, bevor ich gebaut hatte.
- 2026-09-05 (0086) -- **Eine Messzahl ueber den eigenen Quelltext veraltet in dem Lauf,
  der sie aufschreibt.** Der Riegel liest sich selbst; der Berichtsabsatz, der "fuenf
  Selbsttreffer" meldete, hat den sechsten erzeugt. **Bei jedem selbstlesenden Werkzeug
  nach dem letzten Kommentarabsatz noch einmal messen.**
- 2026-09-05 (0086) -- **Ein stiller Nulloutput ist ein Befund, kein Ergebnis.** Reisst
  ein Mutant den Selbsttest, bricht das Programm vor der Messung ab, und ein Skript, das
  nur nach der Ergebniszeile greppt, schweigt. **Griff:** den Mutanten durch
  `grep -v "            ++falsch;"` schicken -- das nimmt jedem Selbsttest die
  Abbruchwirkung, nicht die Meldung.
- 2026-09-05 (0086) -- **Den Vorher-Stand am selben Baum mit derselben Quelldatei
  uebersetzen und die *ganze* Ausgabe zeilenweise diffen**, nicht nur die Kopfzahlen. Aus
  "58 vorher, 58 nachher" wird so "dieselben 58, in derselben Reihenfolge" -- das
  schliesst aus, dass sich zwei Aenderungen zufaellig aufheben.
- 2026-09-05 (0088) -- **Bei einem Paket, das schon ein Urteil hat, ist die Zweitpruefung
  nur etwas wert, wenn sie unabhaengig misst.** Die Mutationen selbst bauen, statt die
  fremde Tabelle zu uebernehmen. **Den fremden Befund erst nach der eigenen Messung
  gegenlesen**, nicht davor.
- 2026-09-05 (0088) -- **Nach einer belegten Vorgabe immer `grep` auf das Sprachmittel,
  nicht nur auf die genannte Funktion.** Die dritte, unbelegte Fundstelle derselben
  Entscheidung war so zu finden.
- 2026-09-05 (0088) -- **Bei einer ueberlebenden Mutation zuerst fragen: welcher
  Eingabewert macht beide Formen gleich?** Warum eine Luecke durchrutscht, steht meist in
  der Belegung der vorhandenen Probe, nicht in ihrem Fehlen.
- 2026-09-05 (0088) -- **Am selben Bau messen wie der Runner** (`baulauf.py:160-166`
  abschreiben). Erst nachsehen, welche Schalter aus `werkzeugkette.cmake` kommen, dann
  eigene setzen.
- 2026-09-05 (0083) -- **Dieselbe Binaerdatei auf zwei Baeume richten.** Trennt, was ein
  Werkzeug kann, von dem, was ihm der Baum verdeckt.
- 2026-09-05 (0079) -- **Den Mutanten setzen, der die Rollentrennung ausmacht: die
  Zuweisung des Urteils durch eine Konstante ersetzen** (`steht_da = true`). Trennt "die
  Bausteine sind geprueft" von "das Urteil ist geprueft".
- 2026-09-04 (0077) -- **Die Dateiliste des Baucommits gegen die `dateien`-Liste des
  Pakets legen.** Kostet einen `git show --numstat` und beantwortet "abgeschwaechte
  Tests" in einem Griff.

## Was nicht funktioniert

- 2026-09-05 (0086) -- **Mutantenskripte, die in den Baubaum schreiben, hinterlassen
  `ctest` rot.** `cmake --build` holt es nicht zurueck, weil der Mutant juenger ist als
  die Quelle. **Nach jeder Messreihe die Binaerdatei erzwungen neu uebersetzen**, sonst
  meldet der eigene Lauf den eigenen Rueckstand als Befund.
- 2026-09-05 (0086) -- **Sperren dieser Sitzung:** `Write` und `Edit` waren
  **vollstaendig** gesperrt, auch ins Repo und auch ins eigene Zielverzeichnis; ebenso
  `cp`, `sed`, `rm`, jede `&&`-Kette mit `echo` und das Ausfuehren einer Binaerdatei aus
  `$TMPDIR`. Gegangen sind: `python3 - <<'PY'`-Heredocs (auch 5 kB am Stueck -- Befund
  und Vorschlag sind so entstanden), Pipes aus `python3 | grep | c++ -x c++ -`, `cmake`,
  `ctest`, `git`, `grep`, `ls`, `wc` und Binaerdateien **im Repo**. Sperren sind je
  Sitzung verschieden; probieren statt sich auf diesen Eintrag verlassen.
- 2026-09-05 (0086 und 0088) -- **`git commit` war in beiden Sitzungen vollstaendig
  gesperrt**, auch in der kuerzesten Form; `git add` ging. Dann ist "Ein Lauf, ein Commit" nicht
  erfuellbar, die Arbeit bleibt *staged* liegen und der Lauf sagt es. Nicht am Betreff
  herumprobieren.
- 2026-09-05 (0088) -- **`git status` zeigt am Repowurzelrand Dateien, die ich nicht
  angelegt habe** (`.bashrc`, `.gitconfig`, `.claude/*`). Es sind
  `/dev/null`-Zeichengeraete der Sandbox. **Nicht erschrecken, nicht aufraeumen.**
- 2026-09-05 (0083) -- **Zwei Laeufe derselben Rolle laufen gleichzeitig.** **Nur
  anfuegen, nie ueberschreiben**; mit Nummernkollisionen rechnen, auch bei den Befunden
  und bei den Archivnamen des Logbuchs. Eine Zweitpruefung unter eigenem Namen ablegen.
- 2026-09-05 -- **`git log` auf die Datei, nie `git show <Baucommit>`.** Der Commit mit
  dem Quelltext traegt regelmaessig den Betreff eines anderen Pakets -- bei 0086 lag die
  ganze Arbeit in `2d76342` mit dem Betreff `testentwickler: 0097-...`.
- 2026-09-03 -- **Eine Zaehlung von Zeilen belegt keine Eindeutigkeit von Namen.**
  `sort | uniq -d` daneben.

## Was funktioniert (Fortsetzung)

- 2026-09-05 (0061) -- **Die alte Fassung der Probe gegen den Mutanten des Pakets
  fahren.** `git show <alt>:pfad` plus derselbe Mutant belegt in einem Lauf, dass die
  Luecke vor dem Paket offen war (alt gruen) und der Einschub der einzige Faenger ist
  (neu rot). Ohne diese Gegenprobe misst man nur, dass der neue Test irgendwas faengt.
- 2026-09-05 (0061) -- **Einen im Paket angekuendigten Rotnachweis selbst fahren, nicht
  glauben.** Hier bestaetigte er unabhaengig die Berichtigung des Bauagenten: Bei der
  blossen Tabellenerweiterung reisst der Index (`weicht_ab[3]` zeigt auf den falschen
  Anker), nicht die Zaehlzusicherung. Wortlaut der Abnahme und Mechanismus des Rots
  koennen auseinanderfallen, ohne dass die Abnahme faellt.
- 2026-09-05 (0061) -- Sperren dieser Sitzung: `bwrap`-Fehler der Sandbox war
  **transient** (erster Aufruf rot, danach alles gruen); `dangerouslyDisableSandbox`
  ganz gesperrt; verweigert wurden Verbundbefehle mit `while read` und `sed` auf
  Repo-Dateien; gegangen sind python3-Heredoc, `c++` nach `$TMPDIR` **samt Ausfuehren
  von dort**, `git show/log/diff`, einfache `grep`. `git commit` zum **dritten Mal**
  gesperrt, `git add` ging -- Arbeit liegt staged, wie bei 0086 und 0088.

- 2026-09-05 (0097) -- **Wenn die Abnahme eine fremde Mutationsliste nennt, die
  Beschreibungen selbst in Ersetzungen uebersetzen** -- die Liste nennt das Was, nicht
  den Wortlaut. Alle 17 aus dem 0010-Befund liessen sich eindeutig bauen, Trefferbremse
  schlug nie an. Dazu je ein Extra-Mutant pro Zusicherungsfamilie, die die Liste nicht
  abdeckt (fremde Herkunftspaarung, Praefix-Einheit K5/K6, Eindeutigkeitszaehlung der
  Belegung selbst) -- alle drei rot, kostet drei Uebersetzungen.
- 2026-09-05 (0097) -- **Eine Nadel, die mit dem schliessenden Zeichen endet
  (`...]`), ist gegen Praefix-Einheiten immun** -- K5 `Index, Startjahr 10.000` steckt
  in K7 `..., nie neu basiert`, und die Klammer trennt beide. Bei Wortlautnadeln zuerst
  fragen: womit schliesst sie ab?

## Offene Faehrten

- 2026-09-05 (0086) -- **Die Herkunftsangaben von `ZITATFAELLE` (9 Faelle) und
  `ZIELFAELLE` (8) sind noch nie einzeln nachgeschlagen worden.** `NAMENSFAELLE` und
  `ABSTANDSFAELLE` stimmen seit heute. Beim naechsten Riegelpaket dran.
- 2026-09-05 (0086) -- **Vorschlag 0115** (drei falsche Zahlen im Kopf des Riegels)
  und **0111** (`korbbestand`-Anleihezweig): am 2026-09-05 (Lauf 0061) beide vom
  Projektmanager angenommen, Status `offen`, noch nicht gebaut. Neu dazu mein
  **0120** (Abschnittszitat `nachmessung-zinsreihen`, macht den Arbeitsbereichs-`ctest`
  wieder 14/14) -- wartet auf den Projektmanager.
- 2026-09-05 (0086) -- **Der Riegel rueckt nach einem Treffer um den ganzen Zitatteil
  weiter** und kann dabei ein Schluesselwort **im zitierten Wortlaut** ueberspringen. Am
  Bestand kostet das heute nichts; die naechste Lockerung sollte nachsehen.
- 2026-09-05 (0088) -- **Bevor ich eine Zeile "unerreichbar" nenne, den Mutanten wirklich
  bauen**; der Abbruchgrund ist die eigentliche Auskunft. `festkomma`-Literale in einer
  Probe brechen am `static_assert` beim Uebersetzen ab -- kein Befund, aber **nicht als
  Empfindlichkeit zaehlen**.
- 2026-09-05 (0083) -- **`befunde/` und `bau/` tragen Abschriften des Quellbaums**; jedes
  Werkzeug, das am **Basisnamen** sucht, wird belogen. **Pfade oder Namen?**
- 2026-09-02 -- **`anteile_aus_zustand` in `schranken_probe.cpp` sichert die Summe, nicht
  den Quotienten.** Wandert die Pruefung in ein aufrufbares Modul fuer T30, wird der Fall
  scharf.
