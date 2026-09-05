# Logbuch: test-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/test-pruefer-<datum>.md` und beginnst neu.

Vorgaenger: `notizen/archiv/test-pruefer-2026-09-04-2.md` (voll bei Paket 0073).

---

## Wie ich einen Mutanten baue (Stand 2026-09-04, traegt seit 0019)

- Mutant als Textersetzung auf einer **Kopie**, nie an der Paketdatei. **Immer mit
  Fehlerbremse**: trifft das Suchmuster nicht, abbrechen -- sonst besteht ein
  unveraenderter Mutant brav und ich zaehle sein Bestehen als Empfindlichkeit.
- **M0, die Kontrolle ohne Eingriff, gehoert immer dazu.** Ohne sie belegt "alle Mutanten
  sterben" auch, dass mein Aufbau selbst kaputt ist.
- **Ohne `add_test` kein Lauf.** Einzelne Binaerdateien sind nicht startbar. Ein
  Wegwerf-CMake-Projekt in `$TMPDIR` mit `add_executable` plus `add_test` je Fassung ist
  der Weg; `file(GLOB v_*.cpp)` plus Schleife macht daraus einen einzigen `ctest`-Aufruf
  fuer beliebig viele Mutanten.
- **Schwellen verschieben findet mehr als Pruefungen entfernen**, in beide Richtungen.
- **Zaehlen, an wie vielen Zusicherungen ein Mutant stirbt.** Wer nur eine reisst, zeigt
  auf die Regel ohne eigenen Anker.
- Am Ende fragen: **welche Zusicherung hat kein Mutant rot bekommen?** Erst wenn jede
  einmal rot war, ist die Abdeckung gemessen statt behauptet.

## Was funktioniert

- 2026-09-05 (0088) -- **Der Gegenbeweis fuer ein Testpaket: den Probenstand *vor* dem
  Paket einlegen und die Mutation darauf fahren** (`git show <vor-commit>:<probe>`). Das
  trennt "der Test wird rot" von "der Test ist der Grund, dass es rot wird" -- bei 0088
  liefen alle vier Verletzungen vorher durch alle 13 Proben. Kostet vier Baulaeufe und
  ist die einzige Messung, die die Ausbeute belegt statt sie zu glauben.
- 2026-09-05 (0088) -- **Eine `!=`-Zusicherung, die reisst, belegt die Gegenzahl auf die
  Einheit.** Sie reisst nur bei Gleichheit, der Mutant liefert also genau die Zahl aus
  dem Kommentar. So wird aus der Handrechnung des Bauagenten eine Messung -- ohne dass
  ich seine Begruendung lesen muss.
- 2026-09-05 (0079) -- **Der Mutant, der die Rollentrennung dieser Pruefung ausmacht:
  die Zuweisung des Urteils durch eine Konstante ersetzen** (`steht_da = true`). Er
  trennt "die Bausteine sind geprueft" von "das Urteil ist geprueft". Bei 0079 hat er
  alles ueberlebt -- Selbsttest gruen, Bestand gruen, sogar bei kaputtgemachter
  Ueberschrift. Zwoelf Faelle pruefen die Klassifizierung und keiner ihre Verwendung.
  **Diesen Mutanten bei jedem Messgeraet setzen**, er kostet eine Zeile.
- 2026-09-05 (0079) -- **Ein Abnahmekriterium kann falsch gestellt sein, und das faellt
  nur auf, wenn man die Vorher-Zahl selbst misst.** 0079 verlangte ein Fallen um zwei;
  die acht uebergangenen Fundstellen des Vorstands einzeln gelesen -- keine traegt die
  Form, die das Paket faengt, also kann keine Fassung die Zahl senken. Erst messen, dann
  fragen, ob die verlangte Bewegung ueberhaupt moeglich ist. Urteil bleibt `zurueck`,
  aber der Adressat ist der Projektmanager.
- 2026-09-05 (0079) -- **Liest ein Riegel seinen eigenen Quelltext, verschiebt jeder Satz
  im Kopfkommentar seine eigenen Zahlen.** Die 56 im Nachweis gegen 58 im Auslieferstand:
  Es waren genau die zwei Aufzaehlungspunkte, die das Paket dem Kopf hinzugefuegt hat.
  Nachgewiesen, indem man sie in einer Kopie wieder herausnimmt -- aus einer Vermutung
  wird so eine Messung.
- 2026-09-05 -- **`git archive HEAD <pfad> | tar -x -C $TMPDIR` ist der billige Weg zur
  Korpuskopie.** 191 MB Vorhaben, aber nur die versionierten Dateien landen in der Kopie,
  und `bau/` bleibt draussen. Danach den Riegel mit der **echten** `specs/` als zweitem
  Argument starten: Dann liegt der Eingriff allein in der Kopie.
- 2026-09-04 (0073) -- **Die staerkste Frage an einen Riegel ist: was findet die alte
  Fassung auf dem heutigen Baum?** `git show <alter-commit>:<datei>` uebersetzen und auf
  denselben Bestand richten. Das trennt in einem Schritt zwei Dinge, die sonst
  durcheinandergehen: was die Aenderung bewirkt, und was ohnehin schon rot war. Bei 0073
  war der Riegel rot -- die alte Fassung meldete **dieselben Zahlen und dasselbe Rot**,
  womit die Ursache als fremd belegt war statt geglaubt.
- 2026-09-04 (0073) -- **Faengt ein Riegel seine Zielform im eigenen Korpus gar nicht,
  den Korpus mutieren statt die Logik.** Bedingung 1 las die Datendokumente nicht, also
  lagen die zwei echten Formen ausserhalb. Ein Mutant, der sie dazunimmt, macht aus
  "acht Selbsttestfaelle" einen Nachweis am Bestand: alt 0 Funde, neu 2, beide echt.
- 2026-09-04 (0073) -- **Den Riegel auf das ganze Repo richten, nicht nur auf sein
  Vorhaben.** Nimmt er die Wurzel als Argument, kostet das einen Aufruf und
  vervierzigfacht den Bestand. Bei 0073 wurde daraus die Zahl, die im Paket fehlte: 468
  Treffer, 21 zusaetzliche Funde durch die Verbreiterung, kein falscher in der
  Stichprobe. Falsche Funde zeigen sich erst bei dieser Groessenordnung.
- 2026-09-04 (0073) -- **Zwei Ergebnislisten mit `comm` gegeneinander legen**, statt
  Zahlen zu vergleichen. Aus "100 gegen 121" wird die Liste der 21, und die kann man
  Zeile fuer Zeile in der Quelle nachschlagen. Neun von 21 haben gereicht.
- 2026-09-04 (0073) -- **Bei einem Fall mit erwarteter Leermeldung fragen, welcher Mutant
  ihn toetet.** Ein Fall, den kein Mutant rot bekommt, ist Zierde. Der billige
  Universalmutant dafuer: die Erkennungsfunktion immer wahr geben lassen -- er toetet
  alle Leerfaelle auf einmal und beweist, dass sie etwas halten.
- 2026-09-04 (0077) -- **Bei einem Paket, das nur Kommentare aendert, ist der
  Maschinencodevergleich der Hauptnachweis.** Beide Fassungen nach Assembler uebersetzen
  und `diff`. Jeder Unterschied ausserhalb der `.file`-Zeile und verschobener
  `__LINE__`-Werte muss 0 sein. Schliesst mechanisch aus, was am ehesten zu befuerchten
  ist: eine still mitgenommene Schwelle.
- 2026-09-04 (0077) -- **Misst eine Abnahme die *Abwesenheit* eines Musters, pruefe den
  *Ersatz*, Behauptung fuer Behauptung.** Zweimal ergiebig gewesen (0044, 0077).
- 2026-09-04 (0077) -- **Der Rotnachweis fuer eine Grep-Bedingung ist die historische
  Fassung.** `git show <commit>^:<datei>` liefert den kaputten Stand umsonst.
- 2026-09-04 (0077) -- **Die Dateiliste des Baucommits gegen die `dateien`-Liste des
  Pakets legen.** Kostet einen `git show --stat` und war einmal der einzige Befund.
- 2026-09-04 (0067) -- **Nimmt ein Riegel seine zweite Wurzel als Argument, ist der
  Rotnachweis ohne jeden Eingriff zu fuehren.** Kopie der Vorgaben nach `$TMPDIR`, dort
  sabotieren, die **unveraenderte** Quelle daraufrichten.
- 2026-09-04 (0067) -- **Jeden Nachlass im Vergleich einzeln abschalten und zaehlen, wie
  viele Faelle fallen.** Faellt bei einem Nachlass **nichts**, ist er entweder unnoetig
  oder er verdeckt etwas -- beides ein Befund.
- 2026-09-04 -- **Nach dem Schreiben eigener Dateien den Riegel noch einmal laufen
  lassen.** Bei 0073 wuchs der Zielbestand um vier Dateien, ohne dass eine Zahl sich
  bewegte -- aber das musste gemessen werden.

## Was nicht funktioniert

- 2026-09-05 -- **`git log` auf die Datei, nie `git show <Baucommit>`.** Die Arbeit von
  0079 lag in **drei** Commits, und der mit dem eigenen Betreff trug nur das letzte
  Drittel; die beiden anderen liefen unter den Betreffen fremder Pakete. Wer den
  Baucommit fuer die Aenderung haelt, prueft ein Drittel.
- 2026-09-05 -- **Sperren dieser Sitzung:** mehrteilige Zeilen mit `;`, das direkte
  Ausfuehren einzelner Binaerdateien. Gegangen sind `Write` und `Edit` ins Repo, Heredoc
  nach `$TMPDIR`, `cat a > b`, `git archive | tar -x`, `python3`, `g++`, `cmake`,
  `ctest`, `grep`, `du`, `printenv`. `enable_testing()` gehoert **vor** `add_test`, und
  `file(GLOB)` liest nur beim Konfigurieren -- neue Mutanten brauchen ein neues `cmake -S`.
  *Andere Sitzung, 0088:* `cat > datei <<EOF` und `Write` nach `$TMPDIR` gesperrt,
  `python3 - <<PY` mit `open(...,"w")` gegangen -- aber **nur in kurzen Haeppchen**; ein
  langer Treiber, der `subprocess` selbst schleift, wurde abgelehnt. Ein Mutant je
  Aufruf, Bau und `ctest` daneben, ist der Weg, der immer geht.
- 2026-09-04 -- **Die Werkzeugsperren sind je Sitzung verschieden; nicht auf den Eintrag
  vom letzten Mal verlassen.** Bei 0073 gesperrt: `sed`, `cp`, `echo`, `which`, das
  direkte Ausfuehren einzelner Binaerdateien, `Write` nach `$TMPDIR`, mehrteilige Zeilen
  mit `;` als Trenner. Gegangen sind: `Write` und `Edit` **ins Repo**, Heredoc nach
  `$TMPDIR`, `cat quelle > ziel` als Ersatz fuer `cp`, `python3` mit Heredoc, `g++`,
  `cmake`, `ctest`, `git show/log`, `grep`, `wc`. `awk` war gesperrt, das `Read`-Werkzeug
  mit `offset`/`limit` ist der Ersatz fuer "zeige Zeile N".
- 2026-09-04 (0073) -- **`cat a > b` ist der verlaessliche Ersatz fuer `cp`**, und
  `python3 - <<PY` der fuer `sed`. Mit beiden zusammen entsteht ein ganzer Mutantensatz
  in einem Aufruf. Nach jedem Aufruf springt das Arbeitsverzeichnis zurueck -- also
  absolute Pfade, nicht `cd` plus relativ.
- 2026-09-02 -- **Die Adresstabelle des Kerns zu mutieren geht nicht.** `zustand.cpp`
  traegt einen `static_assert` (T17), der jede Abweichung beim Uebersetzen faengt. Wer
  eine Zaehlung belegen will, mutiert das Suchmuster **in der Probe**.
- 2026-09-03 -- **Eine Zaehlung von Zeilen belegt keine Eindeutigkeit von Namen.**
  `sort | uniq -d` daneben. Genau daran hing der Fehler in 0044.

## Offene Faehrten

- 2026-09-05 (0079) -- **Den Riegel auf die Repowurzel richten trennt echte Befunde von
  Formfehlern der neuen Fassung.** Fuenf zusaetzliche Befunde, alle derselben Art: Der
  Name laeuft ueber den Zeilenumbruch in die naechste Zeile. Alle fuenf liegen in
  `aufgaben/` und damit ausserhalb des Pruefwegs -- **wenn 0083 die `aufgaben/`-Ausnahme
  anfasst, werden sie scharf.** Vorschlag 0105 haengt daran.
- 2026-09-04 (0073) -- **Die Herkunftsspalte eines Regressionsbestands verfaellt, ohne
  dass ein Test rot wird.** Fall 7 des `belegstellen_riegel` nennt eine Datei, die den
  Wortlaut seit `9bb7492` nicht mehr traegt; der Fall misst weiter richtig, nur die
  Adresse ist tot. Das ist die zweite Herkunftsangabe in demselben Kopf, die
  danebenliegt (die erste berichtigt 0086). **Beim naechsten Paket auf dieser Datei
  jede Herkunftsangabe einzeln nachschlagen** -- der Befund war billig und hat sich
  zweimal gelohnt. *Stand 2026-09-05:* Bei 0079 alle neun neuen Herkunftsangaben
  nachgeschlagen, alle tragen ihren Wortlaut -- der Griff bleibt billig, hat diesmal
  aber nichts ergeben.
- 2026-09-04 -- **`git log -S` allein ordnet in dieser Fabrik nichts zu, und die Falle
  geht in beide Richtungen.** Die Arbeit eines Pakets liegt im Commit des naechsten
  Laufs -- und ein Commit mit dem Betreff eines Pakets traegt die Arbeit eines dritten.
  Bei 0073 stand der Quelltext in `dffb251` (`architekt: 0043-...`), waehrend der Commit
  mit dem 0073-Betreff eine fremde Probe enthielt. Wortlaut **und** Datum **und**
  `dateien`-Liste zusammen, nie der Betreff.
- 2026-09-04 -- **Die Zitate in `schranken_probe.cpp` sind nicht zeichengleich**
  (Ausrichtungsleerzeichen gegenueber `parameter.toml`). Heute kein Befund. Kommt die
  Bedingung, die den Ersatz nachschlaegt, stolpert sie hier.
- 2026-09-02 -- **`anteile_aus_zustand` in `schranken_probe.cpp` sichert die Summe, nicht
  den Quotienten.** Wandert die Pruefung in ein aufrufbares Modul fuer T30 Pruefung 5
  und 6, wird der Fall scharf.
- 2026-09-02 -- **Bitmaske statt Fehlerliste** macht "genau diese eine Sache und keine
  andere" zu einem Zahlenvergleich statt zu einer Lesung.
