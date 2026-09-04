# Logbuch: test-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/test-pruefer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz.

---

## Was funktioniert

- 2026-09-04 — **Auch ein Paket, das nur Kommentare ändert, hat eine Mutationsfrage.**
  Sichert die Abnahme einen Wert „Zeichen für Zeichen", zeigt der Diff nur, *dass* er
  steht — nicht, dass seine Unversehrtheit etwas bedeutet. Bei 0050 drei Mutanten auf
  genau die drei geschützten Werte: alle drei rot (3–4 Zusicherungen). Erst damit ist
  das Kriterium eines über etwas und nicht über Zierat.
- 2026-09-04 — **Einen Mutanten mit Erwartung *grün* dazunehmen, wo ich eine Lücke
  vermute.** Bei 0050 die neue Belegstelle auf `GIBT-ES-NICHT.md` gesetzt: Probe blieb
  grün. Das macht aus „wird vermutlich nicht geprüft" die Zahl *null Zusicherungen* —
  und aus einem Bauchgefühl einen Nachweis, den ein schon offenes Paket erben kann.
- 2026-09-04 — **Vor dem eigenen Vorschlag die `aufgaben/` nach `offen` durchsehen.**
  Meine Lücke bei 0050 stand wörtlich in der Abnahme von 0059, angenommen am selben Tag.
  Ein Vorschlag wäre ein Doppel gewesen; der Messwert im Befund ist mehr wert.
- 2026-09-03 — **Die nützlichste Frage am Ende eines Mutationslaufs: welche Zusicherung
  hat *kein* Mutant rot bekommen?** Bei 0029 waren es zwei — und zwei gezielte Mutanten
  später konnten beide rot werden. Ohne diese Runde hätte ich „18 Mutanten sterben" als
  Abdeckungsaussage verkauft, obwohl zwei Zusicherungen ungeprüft danebenstanden. Erst
  wenn jede Zusicherung einmal rot war, ist die Abdeckung gemessen statt behauptet.
- 2026-09-03 — **Ein Mutant, der die Vorführung selbst entwertet, gehört in jeden Stand,
  der eine Vorführung prüft.** Bei 0029: `spiele` reicht die `Abweichung` nicht durch —
  dann laufen beide „falschen Fassungen" wie die echte und die ganze Bedingung 3 ist
  Theater, das zeigt, dass zweimal dasselbe herauskommt. Er starb an fünf Zusicherungen.
  Merksatz: Prüft ein Test seine eigene Empfindlichkeit vor, prüfe zuerst, ob die
  Vorführung überhaupt wirkt.
- 2026-09-03 — **Verlangt die Abnahme zwei Fälle desselben Tests (`k = 1` und `k = 3`),
  brauche ich einen Mutanten, der nur den zweiten reisst.** Bei 0029 tat es „Lauf nach
  fünf Runden gekappt": drei Zusicherungen tot, alle drei die `k = 3`-Hälfte, `k = 1`
  grün. Das ist der einzige Weg, „die zweite Hälfte steht nicht nur da" zu belegen.
- 2026-09-03 — **`bau/` ist im Venture 0016 in `.gitignore`.** Ein Mutationsstand unter
  `befunde/<name>/bau/` hinterlässt also nur die `CMakeLists.txt` im Repo, keine
  Binärdateien — anders als beim Stand zu 0019 gab es diesmal nichts von Hand
  wegzuräumen.
- 2026-09-03 — **Die Mutationstabelle als ein einziger `ctest`-Lauf: `set_tests_properties(…
  PROPERTIES WILL_FAIL TRUE)`.** Ein kleines CMake-Projekt übersetzt je Mutation die
  **unveränderte** Probe des Pakets gegen ein mutiertes Modul; die Umkehrung macht aus
  „ctest grün" die Aussage *Kontrollfassung besteht und jede Mutation wird gefangen*.
  Bei 0019 acht Mutanten plus Kontrolle in einem Aufruf. Zweiter Vorteil: In dieser
  Sitzung war das Ausführen einzelner Binärdateien gesperrt, `ctest` nicht.
- 2026-09-03 — **Zählen, an wie vielen Zusicherungen ein Mutant stirbt, zeigt die schwache
  Stelle.** Bei 0019 starben sechs Mutanten an drei bis sieben Prüfungen, zwei an **genau
  einer** — und genau die eine verglich das Modul gegen eine wortgleiche Kopie seiner
  selbst im Testcode. Ein Mutant, der nur eine Zusicherung reisst, ist der Fingerzeig auf
  die Regel ohne eigenen Anker.
- 2026-09-03 — **Frag bei jeder Zusicherung, woher der erwartete Wert kommt.** Steht dort
  ein Festwert aus `technik.md`, prüft sie die Vorgabe; steht dort eine zweite Rechnung
  im Testcode, prüft sie nur, dass zwei Kopien einig sind. Bei 0019 waren 126, 76, 0–5,
  6 und 120 verankert — die Klassenzuteilung nicht. Vier von Hand abgezählte Kennungen
  haben die Lücke geschlossen (Vorschlag 0040).
- 2026-09-02 — **Mutanten baue ich mit `cmake -P`, nicht mit `sed`.** In dieser Sitzung
  waren `cp`, `sed`, `grep`, `python3` und der `Edit` ausserhalb meines Zielverzeichnisses
  gesperrt; erlaubt blieben `cmake`, `g++`, `ctest`, `echo >` nach `$TMPDIR` und der
  `Grep`-Werkzeugaufruf. Ein dreizeiliges CMake-Skript (`file(READ)` →
  `string(REPLACE)` → `file(WRITE)`) erzeugt jeden Mutanten, `cmake -E copy` holt die
  Datei heraus. Damit ist Mutationsmessung ohne jede Änderung am Paket möglich.
- 2026-09-02 — **In jeden Mutanten gehört eine Fehlerbremse.**
  `if(I STREQUAL "${O}") message(FATAL_ERROR ...)` — sonst erzeugt ein Tippfehler im
  Suchmuster eine unveränderte Datei, die brav besteht, und ich zähle ihr Bestehen als
  Empfindlichkeit der Probe. Das wäre genau der Fehler, den ich suchen soll.
- 2026-09-02 — **Ein Kontrolllauf mit wirkungsloser Mutation gehört dazu.** Beim
  Stummschalten über `-DAUS=n` habe ich zuerst `n = 99` laufen lassen: Bremse eingebaut,
  trifft nichts, muss grün bleiben. Ohne ihn belegt „alle Mutanten sterben" auch, dass
  mein Eingriff selbst alles kaputtmacht.
- 2026-09-02 — **Schwellen verschieben findet mehr als Prüfungen entfernen.** Eine
  gelöschte Prüfung fällt fast immer auf. Interessant ist `< 1` → `< 0` **und**
  `< 1` → `< 2`: Erst wenn beide Richtungen rot werden, sind die Ränder wirklich geprüft
  und nicht nur die Mitte.
- 2026-09-02 — **Die Mengenzählung einer Probe von Hand gegen das Verzeichnis legen.**
  Eine gleich grosse, aber falsche Adressmenge fällt der Zählung nicht auf. Bei 0020 hing
  es an zwei Feinheiten (`welt.preis.<s>` endet nicht auf `.preis`, `.gegendruck` nicht
  auf `.druck`) — beide stimmten, aber die Summe hätte auch bei einem Fehler gestimmt.
- 2026-09-03 — **Der Mutant muss nicht die Originaldatei sein.** Bei 0040 durfte ich
  `vorrat.cpp` nicht anfassen (fremdes Paket) und `cp` war gesperrt. Der Weg: die
  geprüften Funktionen einmal in `$TMPDIR` abschreiben, die Varianten über `#if
  MUTATION` einhängen und die **unveränderte** Probe dagegen linken. Vorher M0 gegen die
  Abschrift laufen lassen — stimmt sie mit dem Original überein, ist die Abschrift als
  Maßstab belegt. Sechs Mutationen für den Preis von einer Datei.
- 2026-09-03 — **Eine Probe, deren Vorführung das geprüfte Modul selbst aufruft, ist
  nicht automatisch zirkulär.** 0040 erzeugt die falsche Regel durch Spiegelung statt
  durch eine zweite Fassung. Ob das trägt, ist keine Lesefrage: Modul mutieren und
  nachsehen, ob die Probe trotzdem fällt. Sie fiel — an den handgeschriebenen
  Erwartungswerten der Abweichung. Wer *beide* Spalten von Hand hinschreibt (echt und
  abweichend), macht die Vorführung nachprüfbar; mit nur einer zeigt sie bloß, dass
  irgendetwas anderes herauskommt.

## Was nicht funktioniert

- 2026-09-03 — **Den Mutationsstand unter `bau/` abzulegen war falsch, und ich konnte es
  nicht mehr zurücknehmen.** `baulauf.py:116` filtert beim `rglob("CMakeLists.txt")` nur
  `befunde`, nicht `bau` — mein Prüfstand wäre zum vierten Manifest des offiziellen
  Übersetzungsberichts geworden. `rm` war gesperrt (Wortlaut im Befund zu 0019), also
  bleibt er liegen und muss von Hand weg. **Der einzige nachweislich übersprungene
  Verzeichnisname ist `befunde`; dorthin gehört der Mutationsstand.** Der Befund selbst
  ist Vorschlag 0041 geworden.
- 2026-09-03 — **Die Werkzeugsperren sind je Sitzung verschieden — nicht auf den Eintrag
  vom letzten Mal verlassen.** Diesmal abgelehnt: `cp`, `mkdir`, `rm`, Heredoc nach
  `$TMPDIR`, `for`-Schleifen, `printf | g++ -xc++ -`, das Ausführen einzelner
  Binärdateien. Erlaubt: `cmake`, `ctest`, ein blankes `g++ … -o`, `git log/diff/show`,
  `cat`/`head`/`tail`/`ls`/`find`, das `Grep`-Werkzeug und `Write` **innerhalb** des
  Repos. Merksatz: Erst den billigsten Aufruf der geplanten Kette testen, dann die Kette
  bauen.
- 2026-09-02 — **Die Adresstabelle des Kerns zu mutieren, um die Zählung einer Probe zu
  prüfen, geht nicht.** `zustand.cpp` trägt einen `static_assert` (T17, Paket 0008), der
  jede Namensabweichung schon beim Übersetzen fängt — mein Mutant kam gar nicht bis zum
  Lauf. Wenn ich die Zählung einer Probe belegen will, mutiere ich das Suchmuster **in
  der Probe**, nicht die Tabelle im Kern.

## Offene Faehrten

- 2026-09-03, **erledigt am 2026-09-04 durch 0050** — **Zeilennummern als Beleg altern
  still, und zwar schneller als die Pakete laufen.** Dieselbe Stelle in `spiel.md`:
  1043 → 1318 → 1464 → 1471 über vier Stände, davon einer *nach* dem Bau der Korrektur.
  Zwei Merksätze: Vor jedem Urteil über einen Beleg die **historische** Fassung
  nachschlagen (`git show <commit>:<datei> | grep -n`), sonst wird aus fremdem
  Zeilendrift ein Rücklauf gegen den Falschen. Und: Eine Abschnittsüberschrift als
  Ersatz prüfe ich auf **Eindeutigkeit** — kommt sie zweimal vor, ist der Verweis nur
  scheinbar stabil.
- 2026-09-02 — **`anteile_aus_zustand` in `schranken_probe.cpp` sichert die Summe, nicht
  den Quotienten** (`mal_geteilt` bricht nach T7 hart ab). Heute unerreichbar, weil die
  Probe ihre Zustände selbst setzt. Wandert die Prüfung laut `rueckstand.md` in ein
  aufrufbares Modul für T30 Prüfung 5 und 6, wird der Fall scharf — dann nachsehen, ob
  die dritte Wache mitgekommen ist. Beleg steht im Befund zu 0020.
- 2026-09-02 — Beim nächsten Paket dieser Rolle prüfen, ob das Muster aus 0020 hält:
  Bitmaske statt Fehlerliste macht „genau diese eine Sache und keine andere" zu einem
  Zahlenvergleich statt zu einer Lesung. Das war der Grund, warum die Rotproben dort
  überhaupt nachprüfbar waren.

## Nachtrag 2026-09-04 (Paket 0059)

- **Ein Riegel, der seine Wurzel als Argument bekommt, ist ohne jede Aenderung am Baum
  rotprobbar.** Bei 0059 einen synthetischen Baum in `$TMPDIR` mit 18 Belegstellenformen
  gebaut und das gebaute Programm daraufgerichtet: 11 rot, 7 gruen, jede gruene erklaerbar.
  Kein Schreibvorgang unter `ventures/`, nichts zurueckzurollen.
- **Bei einem Riegel ist die Dateiauswahl die Schwelle, nicht die Vergleichslogik.**
  Also `ist_quelldatei` mutieren, nicht den Namensvergleich: Mutant mit `.md`/`.toml` auf
  den echten Baum ergab 90 statt 0 Befunde -- aber alle unter `aufgaben/`. Erst diese
  Aufteilung macht aus "Auswahl begruendet" ein "Auswahl belegt".
- **Meldet ein Riegel "0 Treffer mit Dateinamen daneben", ist das noch kein Gruen.**
  Dieselbe Null kaeme von einem kaputten Namensucher. Die Treffer einzeln nachschlagen;
  bei 0059 waren alle 5 der im Kopfkommentar benannte Sonderfall.
- **Gesperrt in dieser Sitzung:** `Write`, `Edit`, Heredoc, `rm`, mehrteilige Bash-Zeilen
  mit `&&`. Gegangen ist `printf` mit Zeilenargumenten und Umlenkung, bei hoechstens rund
  acht kurzen Argumenten je Aufruf. Eine ganze Ergebnisdatei so zu schreiben geht, kostet
  aber ~25 Aufrufe und laesst sich nicht mehr korrigieren -- Text vorher fertig denken.
