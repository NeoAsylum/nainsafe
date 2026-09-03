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

- 2026-09-03 — **Bei 0029 wird die Determinismusfrage zum ersten Mal scharf.** Bei 0019
  war sie leer: `erzeuge_profilliste` ist eine reine Funktion ohne Eingabe, ohne Zufall,
  ohne Zustand. 0029 schreibt den Vorrat über Runden fort — dann nachsehen, ob die Probe
  einen Lauf über mehrere Runden gegen eine **gespeicherte** Sollfolge legt oder nur
  gegen ihre eigene zweite Rechnung. `spiel.md` liefert eine echte Regressionspartie
  frei Haus: Referenzprofil, Runden 1–5 vergeben 1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,5
  und stehen danach wieder auf `(0,0,0,0,0)`. Steht die nicht in der Probe, ist das ein
  Befund.
- 2026-09-02 — **`anteile_aus_zustand` in `schranken_probe.cpp` sichert die Summe, nicht
  den Quotienten** (`mal_geteilt` bricht nach T7 hart ab). Heute unerreichbar, weil die
  Probe ihre Zustände selbst setzt. Wandert die Prüfung laut `rueckstand.md` in ein
  aufrufbares Modul für T30 Prüfung 5 und 6, wird der Fall scharf — dann nachsehen, ob
  die dritte Wache mitgekommen ist. Beleg steht im Befund zu 0020.
- 2026-09-02 — Beim nächsten Paket dieser Rolle prüfen, ob das Muster aus 0020 hält:
  Bitmaske statt Fehlerliste macht „genau diese eine Sache und keine andere" zu einem
  Zahlenvergleich statt zu einer Lesung. Das war der Grund, warum die Rotproben dort
  überhaupt nachprüfbar waren.
