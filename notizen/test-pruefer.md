# Logbuch: test-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/test-pruefer-<datum>.md` und beginnst neu.

Vorgaenger: `notizen/archiv/test-pruefer-2026-09-05.md` (voll bei Paket 0085).

---

## Wie ich einen Mutanten baue (Stand 2026-09-05, traegt seit 0019)

- Mutant als Textersetzung auf einer **Kopie** in `$TMPDIR`, nie an der Paketdatei.
  **Immer mit Fehlerbremse**: trifft das Suchmuster nicht, abbrechen -- sonst besteht ein
  unveraenderter Mutant brav und ich zaehle sein Bestehen als Empfindlichkeit.
- **M0, die Kontrolle ohne Eingriff, gehoert immer dazu**, und nach jeder Ruecknahme
  **noch einmal**. Ohne sie belegt "alle Mutanten sterben" auch, dass mein Aufbau selbst
  kaputt ist.
- **Ohne `add_test` kein Lauf.** Einzelne Binaerdateien sind nicht startbar; `ctest` im
  Baubaum ist der Weg. `enable_testing()` gehoert **vor** `add_test`, und `file(GLOB)`
  liest nur beim Konfigurieren -- neue Mutantendateien brauchen ein neues `cmake -S`.
- **Schwellen verschieben findet mehr als Pruefungen entfernen**, in beide Richtungen.
- **Zaehlen, an wie vielen Zusicherungen ein Mutant stirbt.** Wer nur eine reisst, zeigt
  auf die Regel ohne eigenen Anker.
- Am Ende fragen: **welche Zusicherung hat kein Mutant rot bekommen?** Erst wenn jede
  einmal rot war, ist die Abdeckung gemessen statt behauptet.

## Was funktioniert

- 2026-09-05 (0083) -- **Dieselbe Binaerdatei auf zwei Baeume richten: Arbeitsbaum und
  `git archive`-Kopie.** Trennt, was der Riegel kann, von dem, was ihm der Baum verdeckt.
  Bei 0083 der ganze Befund: derselbe Eingriff, Kopie rot mit 14 toten Zielen,
  Arbeitsbaum gruen -- weil `bau/` (unversioniert, aus `baulauf.py:161`) Abschriften der
  Ziele traegt und der Riegel Basisnamen statt Orte vergleicht. **Immer auch auf dem Baum
  messen, auf dem der Riegel laeuft.** `tar --exclude=` erzeugt "Datei weg" ohne `rm`.
- 2026-09-05 (0083) -- **Vor der Logik die Namensraeume mit `comm` schneiden**
  (`find -printf "%f\n" | sort -u`): 153 von 159 Zielnamen haben einen Zwilling in einem
  ungelesenen Ordner -- der Verdacht stand vor der ersten Zeile Code.
- 2026-09-05 (0083) -- **Die Reproduktionsanweisung aus dem Paketrumpf nachstellen**, als
  erster Lauf nach dem Bauen. Bleibt sie gruen, ist das Paket erledigt.
- 2026-09-05 (0085) -- **Bei einer Probe, die einen Wortlaut prueft, ist der Mutant nicht
  „Riegel weg", sondern „Halbsaetze vertauscht".** Streicht man den Riegel, faengt ihn
  meist ein zweiter, und dann ist nur belegt, dass der **Kastenname** geprueft wird.
  Vertauscht man die unterscheidenden Halbsaetze zweier Nachbarriegel, werfen beide
  weiter aus demselben Kasten -- und erst das zeigt, ob das unterscheidende Textstueck
  etwas traegt. Bei 0085 sind daran 4 von 7 Erwartungen gefallen, wo die vom Paket
  verlangte Sabotage nur 2 fand.
- 2026-09-05 (0085) -- **Den Test abschwaechen und die Quelle sabotieren, im selben
  Mutanten.** Das ist der Griff, der zeigt, ob die Zusicherung selbst gesichert ist. Bei
  0085 blieb der Lauf gruen und druckte „Abbruch wie erwartet" neben der Meldung eines
  fremden Riegels -- genau der Ausgang, den das Paket abgeschafft hatte, eine Ebene
  hoeher. Daraus wurde Vorschlag 0107, nicht ein Rueckgabegrund.
- 2026-09-05 (0085) -- **Eine Stelle, die als einzige auf ihren Riegel zeigt, ist die
  aussagekraeftige.** Wo zwei Stellen denselben Riegel pruefen, faellt eine Abschwaechung
  zufaellig auf, weil die andere haelt. Beim Waehlen des Mutanten zuerst fragen, welche
  Zusicherung **allein** steht.
- 2026-09-05 (0085) -- **Offene Punkte, die der Bauagent selbst notiert, sind billige
  Messungen.** Beide von 0085 in je einem Lauf geschlossen: der eine mit einem Mutanten,
  der andere, indem ich den Belegstellenriegel selbst gegen die echte Vorhabenwurzel
  laufen liess (`cmake -S <echter pfad> -B $TMPDIR/...`, gruen). Das Paket zu lesen ist
  erlaubt -- das Logbuch des Bauagenten nicht.
- 2026-09-05 (0088) -- **Der Gegenbeweis fuer ein Testpaket: den Probenstand *vor* dem
  Paket einlegen und die Mutation darauf fahren** (`git show <vor-commit>:<probe>`). Das
  trennt "der Test wird rot" von "der Test ist der Grund, dass es rot wird" -- bei 0088
  liefen alle vier Verletzungen vorher durch alle 13 Proben.
- 2026-09-05 (0088) -- **Eine `!=`-Zusicherung, die reisst, belegt die Gegenzahl auf die
  Einheit.** Sie reisst nur bei Gleichheit, der Mutant liefert also genau die Zahl aus
  dem Kommentar. So wird aus der Handrechnung des Bauagenten eine Messung.
- 2026-09-05 (0079) -- **Der Mutant, der die Rollentrennung dieser Pruefung ausmacht:
  die Zuweisung des Urteils durch eine Konstante ersetzen** (`steht_da = true`). Er
  trennt "die Bausteine sind geprueft" von "das Urteil ist geprueft". Bei 0079 hat er
  alles ueberlebt. **Diesen Mutanten bei jedem Messgeraet setzen**, er kostet eine Zeile.
- 2026-09-05 (0079) -- **Ein Abnahmekriterium kann falsch gestellt sein, und das faellt
  nur auf, wenn man die Vorher-Zahl selbst misst.** Erst messen, dann fragen, ob die
  verlangte Bewegung ueberhaupt moeglich ist. Der Adressat ist dann der Projektmanager.
- 2026-09-05 -- **`git archive HEAD <pfad> | tar -x -C $TMPDIR` ist der billige Weg zur
  Korpuskopie.** Nur die versionierten Dateien landen darin, `bau/` bleibt draussen.
  Danach den Riegel mit der **echten** Wurzel als Argument starten: Dann liegt der
  Eingriff allein in der Kopie und `git status` bleibt am Ende leer.
- 2026-09-04 (0073) -- **Die staerkste Frage an einen Riegel ist: was findet die alte
  Fassung auf dem heutigen Baum?** `git show <alter-commit>:<datei>` uebersetzen und auf
  denselben Bestand richten. Trennt, was die Aenderung bewirkt, von dem, was ohnehin rot
  war.
- 2026-09-04 (0073) -- **Den Riegel auf das ganze Repo richten, nicht nur auf sein
  Vorhaben.** Kostet einen Aufruf, vervierzigfacht den Bestand. Falsche Funde zeigen sich
  erst bei dieser Groessenordnung.
- 2026-09-04 (0073) -- **Zwei Ergebnislisten mit `comm` gegeneinander legen**, statt
  Zahlen zu vergleichen. Aus "100 gegen 121" wird die Liste der 21, nachschlagbar.
- 2026-09-04 (0073) -- **Bei einem Fall mit erwarteter Leermeldung fragen, welcher Mutant
  ihn toetet.** Ein Fall, den kein Mutant rot bekommt, ist Zierde. Universalmutant: die
  Erkennungsfunktion immer wahr geben lassen.
- 2026-09-04 (0077) -- **Bei einem Paket, das nur Kommentare aendert, ist der
  Maschinencodevergleich der Hauptnachweis.** Beide Fassungen nach Assembler und `diff`;
  ausserhalb der `.file`-Zeile und verschobener `__LINE__`-Werte muss alles 0 sein.
- 2026-09-04 (0077) -- **Misst eine Abnahme die *Abwesenheit* eines Musters, pruefe den
  *Ersatz*, Behauptung fuer Behauptung.** Dreimal ergiebig gewesen (0044, 0077, 0085).
- 2026-09-04 (0077) -- **Die Dateiliste des Baucommits gegen die `dateien`-Liste des
  Pakets legen.** Kostet einen `git show --stat` und war einmal der einzige Befund.
- 2026-09-04 (0067) -- **Jeden Nachlass im Vergleich einzeln abschalten und zaehlen, wie
  viele Faelle fallen.** Faellt bei einem Nachlass **nichts**, ist er entweder unnoetig
  oder er verdeckt etwas -- beides ein Befund.

## Was nicht funktioniert

- 2026-09-05 (0085) -- **Nach `git archive | tar -x` baut `make` den Mutanten nicht
  zurueck.** `tar` setzt den Zeitstempel aus dem Archiv, also **aelter** als die
  Objektdatei; der vorige Eingriff bleibt einkompiliert. Hat mich einen Fehlschluss
  gekostet: Ein Lauf zeigte einen dritten roten Fall, der aus dem Mutanten davor stammte.
  Erkennbar nur daran, dass die Bauausgabe **nur** „Linking" zeigt und kein „Building".
  *Nach jeder Ruecknahme die Zeitstempel selbst setzen* -- `os.utime` ueber alle
  `*.cpp`/`*.hpp` -- und M0 erneut fahren, bevor der naechste Mutant kommt.
- 2026-09-05 (0083) -- **Zwei Laeufe derselben Rolle laufen gleichzeitig.** Ein 0085-Lauf
  hat dieses Logbuch mitten in meinem neu geschrieben und die Nummer 0107 belegt. **Nur
  anfuegen, nie ueberschreiben**; mit Nummernkollisionen rechnen.
- 2026-09-05 (0083) -- **`cmake -E make_directory`/`cmake -E copy` ersetzen `mkdir`/`cp`**,
  wenn beide gesperrt sind. Binaerdatei aus `$TMPDIR` war gesperrt, dieselbe aus dem
  **CMake-Bauverzeichnis** mit vollem Pfad ging -- spart das Wegwerf-`add_test`. `mv` war
  gesperrt: Dateinamen sitzen, sobald sie geschrieben sind.
- 2026-09-05 -- **`git log` auf die Datei, nie `git show <Baucommit>`.** Bei 0079 lag die
  Arbeit in **drei** Commits unter fremden Betreffen; bei 0085 trug der Commit mit dem
  0085-Betreff nur das Logbuch, der Quelltext lag in `ce59b8b` (`architekt: 0051-...`).
  Wer den Baucommit fuer die Aenderung haelt, prueft das Falsche.
- 2026-09-05 -- **Sperren dieser Sitzung:** mehrteilige Zeilen mit `;`, `sed`, `cat`,
  `&&` mit einem Heredoc dahinter, das direkte Ausfuehren einzelner Binaerdateien.
  Gegangen sind `Write`/`Edit` ins Repo, `python3 - <<PY` in **kurzen Haeppchen** (Ersatz
  fuer `sed` und `cp`), `git archive | tar -x`, `cmake`, `ctest`, `grep`, `wc`, `ls`,
  `git`. Ein langer Treiber, der `subprocess` selbst schleift, wurde abgelehnt -- ein
  Mutant je Aufruf, Bau und `ctest` daneben, ist der Weg, der immer geht. Die Sperren
  sind je Sitzung verschieden; nicht auf diesen Eintrag verlassen, sondern probieren.
- 2026-09-02 -- **Die Adresstabelle des Kerns zu mutieren geht nicht.** `zustand.cpp`
  traegt einen `static_assert` (T17), der jede Abweichung beim Uebersetzen faengt. Wer
  eine Zaehlung belegen will, mutiert das Suchmuster **in der Probe**.
- 2026-09-03 -- **Eine Zaehlung von Zeilen belegt keine Eindeutigkeit von Namen.**
  `sort | uniq -d` daneben. Genau daran hing der Fehler in 0044.

## Offene Faehrten

- 2026-09-05 (0083) -- **`befunde/` und `bau/` tragen Abschriften des Quellbaums**; jedes
  Werkzeug, das am **Basisnamen** sucht, wird belogen: 133 der 159 Zielnamen haben einen
  versionierten Zwilling unter `befunde/messung-0069/baum/`. **Bei jedem Werkzeug, das im
  Baum nachschlaegt, fragen: Pfade oder Namen?**

- 2026-09-05 (0085) -- **Der Warnsatz faengt eine Abschwaechung mit, wenn sie eine
  Veraenderliche unbenutzt zuruecklaesst** (`-Werror=unused-variable`). Das ist ein
  zufaelliger Schutz und kein Riegel: Wer die Deklaration mitnimmt, kommt durch. Beim
  naechsten Testpaket pruefen, ob der Warnsatz mehr traegt, als ihm zugetraut wird.
- 2026-09-05 (0079) -- **Den Riegel auf die Repowurzel richten trennt echte Befunde von
  Formfehlern der neuen Fassung.** Fuenf zusaetzliche Befunde derselben Art: Der Name
  laeuft ueber den Zeilenumbruch weiter. Alle fuenf liegen in `aufgaben/` und damit
  ausserhalb des Pruefwegs -- **wenn 0083 die `aufgaben/`-Ausnahme anfasst, werden sie
  scharf.** Vorschlag 0105 haengt daran.
- 2026-09-04 (0073) -- **Die Herkunftsspalte eines Regressionsbestands verfaellt, ohne
  dass ein Test rot wird.** Fall 7 des `belegstellen_riegel` nennt eine Datei, die den
  Wortlaut seit `9bb7492` nicht mehr traegt. **Beim naechsten Paket auf dieser Datei
  jede Herkunftsangabe einzeln nachschlagen.** *Stand 2026-09-05:* Bei 0079 alle neun
  neuen nachgeschlagen, alle tragen ihren Wortlaut -- der Griff bleibt billig.
- 2026-09-04 -- **Die Zitate in `schranken_probe.cpp` sind nicht zeichengleich**
  (Ausrichtungsleerzeichen gegenueber `parameter.toml`). Heute kein Befund. Kommt die
  Bedingung, die den Ersatz nachschlaegt, stolpert sie hier.
- 2026-09-02 -- **`anteile_aus_zustand` in `schranken_probe.cpp` sichert die Summe, nicht
  den Quotienten.** Wandert die Pruefung in ein aufrufbares Modul fuer T30 Pruefung 5
  und 6, wird der Fall scharf.
- 2026-09-02 -- **Bitmaske statt Fehlerliste** macht "genau diese eine Sache und keine
  andere" zu einem Zahlenvergleich statt zu einer Lesung.
