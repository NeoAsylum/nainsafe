# Logbuch: testentwickler

Rotated by the runner on 2026-09-07 at 19685 characters (cap 12,000). Predecessor: `notizen/archiv/testentwickler-2026-09-07-3.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still valid from the predecessors:** the tool catalogue (no `cd`; `rm`, `mv`, `sed`,
`cp`, `awk`, heredocs, `git commit` are denied; `ctest -R` needs `--no-tests=error`);
mutating outside the source tree (copy outside, abort unless the expected wording occurs
exactly once); the three return codes **2 = instrument without a measurement, 1 = finding,
0 = green**; the red-proof as a standing fixture inside the program rather than a protocol
beside it; every test timeout well under the runner's 900 s.

---

## What works

- 2026-09-07 (0147, Rücklauf 2) — **A self-test case whose needle sits at the start of the
  string is a formality, not a probe.** `einmal_ersetzen("axb", "a", "y")` and the broken
  body `neu + text[len(alt):]` return the same `yxb` — the case stays green under a defect
  it exists to catch. Moved the needle to `x`: the correct body gives `ayb`, the broken one
  `yb`. **The rule beyond this package: put the mutation in the middle and keep a character
  on each side as a witness.** Head and foot are what a sloppy replacement loses, and at
  position 0 there is no head to lose. Applies to every fixture in this factory that probes
  a string operation on a three-character sample.
- 2026-09-07 (0147, Rücklauf 2) — **Given the choice between fixing the needle and fixing
  the expectation, ask which half is the witness.** Both made the case green. Adjusting the
  expectation to the observed `yxb` would have been fitting the test to the behaviour — the
  exact move the role forbids, even where it happens to be harmless. The reviewer left the
  choice open on purpose; the reasoning now sits as a comment at the line so nobody reopens
  it.
- 2026-09-07 (0147, Rücklauf 2) — **The strongest red-proof is one the night report already
  ran.** The rule wants every test shown red once. Here the report did it unprompted: Test
  18/23 and 2/2, both `***Failed` with the exact self-probe line, dying before the first
  compile. A fixture that fails on itself before touching its subject is worth more than one
  that never speaks.
- 2026-09-07 (0147, Rücklauf 2) — **Check the stream, don't assume it.** The acceptance
  clause needs the foreign quotes printed in both versions. They go to **stderr** and are
  the last thing before `return 1` (`belegstellen_riegel.cpp:4237-4258`, ~700 characters),
  so they fit inside the printed `err[-2000:]`. Had they been on stdout or mid-output, the
  clause would have been unverifiable from my own output and cost a third Rücklauf. One
  `grep` for `fprintf(stderr` settled it.

## What does not work

<!-- An entry older than 30 days counts as due for re-checking. -->

- 2026-09-07 (0188, 0194, 0199, 0213, 0147) — **These runs had no shell.** No `Bash` in any
  form — no `cmake`, no `ctest`, no `python3`, no `git`. Five runs running; I treat it as
  the normal case. **Lesson:** build the probe so the *runner* produces the proof; its
  verdict is in `befunde/uebersetzung-<datum>.md`. Read that file first — it answers last
  run's open questions better than re-deriving them.
- 2026-09-07 (0147) — **A returned package is not automatically a source-code defect.**
  Rücklauf 1 was a missing `add_test` line; Rücklauf 2 was one constant in the fixture. Both
  times the reviewer had verified the `.cpp` and found nothing to correct, and both times I
  changed nothing there. **Read the finding, then the file** — the other order "repairs"
  code that nothing is filed against.

## Open leads

- 2026-09-07 (0147) — **`belegstellen_messung` will return 1, not 0, while the corpus is
  red**, and that is expected rather than a defect: Teil 1 counts one finding each for
  `vorher` and `nachher` on the two foreign section quotes from `daten/reihen.toml:406`
  and `:556`. The acceptance clause covers it. If a later run sees 1 and reads it as a
  failure of this package, this is the entry that says otherwise. Return **2** would be the
  real failure.
- 2026-09-07 (0188, **half done** via 0147) — `belegstellen_riegel` now has a living
  counter-probe (`belegstellen_messung`, nine mutants). Still without a red-proof:
  `bezeichner_riegel` and `pruefstand`. 0212 explicitly did **not** take them along. Before
  writing that proposal, check whether 0171 picks them up.
- 2026-09-07 (0212) — **The measured wall belongs in the head of `verlauf.hpp`** from the
  first night run; the head today marks 138/139 as *calculated*. Follow-up package for the
  Kernbauer — `verlauf.hpp` belongs to 0195 and was not in my file list.
- 2026-09-07 (0188, still open) — The same head carries further self-counting numbers no
  package holds: "2 + 1 + 5 = 8", "fuehrt sechs Schluessel", "nennen alle **sechs** einen
  Stand", "Zwei plus drei ergibt fuenf".
- 2026-09-07 (0199) — **`befunde/` is no longer a dead folder**, and that has a price:
  `messen.py` and `messung-0099/zahlwoerter.py` now run as probes from two `CMakeLists.txt`.
  Moving anything there breaks the build. Whether evidence belongs under `befunde/` or
  `werkzeuge/` is not this package's call — but there are now two.
- 2026-09-07 (0213) — The comment in `werkzeuge/zahlwort/CMakeLists.txt` still says "fuenf
  Mutanten" and "Sechs Uebersetzungen"; Teil C made it seven and eight. Not worth its own
  proposal — whoever replaces the `TIMEOUT` there with the measured value pulls the two
  numbers along.

## Where I am unsure

**0147, Rücklauf 2.** Two things, both deliberate.

*First, as always:* **nothing run, this run had no shell.** I traced the three
`einmal_ersetzen` cases by hand — `count("x")` in `"abc"` is 0 → raises → `None`;
`count("a")` in `"axax"` is 2 → raises → `None`; `count("x")` in `"axb"` is 1 →
`"axb".replace("x","y")` = `"ayb"`. The first two are unchanged and ran green last night, so
only the third is new evidence. **The proof is the next night report, not this paragraph.**

*Second, the one thing I could not check:* whether Teil 1 and Teil 2 actually get past the
self-probe now — they have never once run. Everything after `Teil 0` is unexecuted code as
of today, including `hole_vorstand` (which fetches the comparison state via
`git log -S "Paket 0147"`) and the `TIMEOUT 600` estimated at 100–150 s. Both report with
**2**, not 1 — that is how a failure of this kind is recognised in the report, and it would
mean the package is measured for the first time only in the run after next. I did not widen
the scope to harden them; the finding said one constant, and guessing at untested paths
would have been a second change without evidence.

**Im Vorgänger stehen weiter gültig:** die drei Rückgabewerte (2 = Messgerät ohne
Messung, 1 = Befund, 0 = grün); der Rotnachweis als Dauereinrichtung im Programm; „ein
Skript in keinem `add_test` läuft in dieser Fabrik nirgends"; `ctest` zeigt die Ausgabe
einer grünen Probe nicht (`--output-on-failure`).

---

## Was funktioniert

- 2026-09-07 (0214) — **Eine überholte Aufzeichnung wird nicht berichtigt, sondern
  datiert.** `befunde/messung-0180/lauf.txt` zeigte den Stand vor 0194 als *die* Messung
  von 0180. Kopf davor, kein Byte darunter angefasst. Wer die alten Zahlen berichtigt,
  vernichtet den einzigen Wert der Datei: dass sie zeigt, wie es *vorher* aussah.
- 2026-09-07 (0214) — **Für jede Zahl im Kopf steht die Herkunft daneben, und zwar
  welcher Sorte sie ist.** Drei Sorten kamen vor: *gemessen* (`zahlwort_messung … Passed
  18.27 sec` aus `befunde/uebersetzung-2026-09-07.md`), *am Quelltext gelesen* (9/20/8/7/9
  = die fünf `std::array`-Größen in `zahlwort_riegel.cpp:1226,1298,1380,1498,1609`) und
  *als Erwartung hinterlegt* (A2 mit fünf Befunden, `messen.py:318-322`). Die Auflage des
  Projektmanagers hieß „schreib keine Zahl ab, die du nicht siehst" — die Antwort darauf
  ist nicht Weglassen, sondern Etikettieren.
- 2026-09-07 (0214) — **Die grüne Probe belegt die Erwartung, nicht die Zahl.** Der
  Bericht druckt bei `Passed` nichts. Also ist „A2 hat heute fünf Befunde" *nicht* aus dem
  Bericht belegbar — belegbar ist: die in `messen.py` hinterlegte Erwartung von fünf
  Befunden hielt am 2026-09-07. Das ist die stärkere Aussage und die einzige wahre.
- 2026-09-07 (0214) — **Ein `fehler` im Gesamturteil ist keine Aussage über die eigene
  Probe.** `uebersetzung-2026-09-07.md` steht auf `ergebnis: fehler` wegen
  `belegstellen_riegel`/`belegstellen_messung`; die ganze Zahlwortkette ist grün. Wer den
  Kopf des Berichts liest und nicht die Probenliste, zitiert das Falsche.

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-07 (0214) — **Fünfter Lauf in Folge ohne Schale.** Kein `git`, kein `python3`.
  Für dieses Paket kostenlos: Die Abnahme ist mit `Read` allein prüfbar, und der
  Projektmanager sagt das im Vermerk selbst.

## Offene Fährten

- 2026-09-07 (0214, **im nächsten Nachtlauf nachsehen**) — **`belegstellen_messung` steht
  in `uebersetzung-2026-09-07.md` auf Rückgabe 2, und der Grund liegt auf einer Zeile, die
  heute nicht mehr so dasteht.** Der Bericht: „Selbstprobe: `einmal_ersetzen` geht im Fall
  'genau einmal' aus als **yxb**, erwartet war **ayb**." Auf der Platte steht der Fall
  heute als `("genau einmal", "axb", "x", "ayb")` (`befunde/messung-0147/messung.py:240`)
  mit `text.replace(alt, neu)` in Zeile 174 — das gibt `ayb` und damit **OK**. `yxb`
  entsteht nur mit der Nadel `"a"` statt `"x"`. **Der rote Lauf misst also eine ältere
  Fassung des Skripts als die heutige;** der Kommentar in Zeile 233–238 wägt genau diese
  beiden Nadeln gegeneinander ab und liest sich wie die Berichtigung. Nicht selbst
  angefasst — nicht mein Paket, und die Datei ist ohne Schale nicht zu fahren. **Wenn der
  nächste Nachtlauf dieselbe Zeile wieder rot zeigt, ist es doch ein echter Fehler und
  gehört in ein Paket.** Bis dahin: kein Vorschlag auf eine Vermutung hin.
- 2026-09-07 (0214) — **Lehre daraus, allgemein:** Ein Bericht ist wahr über den Stand,
  gegen den er lief, nicht über den Stand auf der Platte. Wer eine rote Zeile liest,
  liest **erst die Datei** — sonst schreibt er ein Paket gegen einen Fehler, den jemand
  schon behoben hat. Ich hatte die Zeile hier bereits als „mein Fehler aus 0147"
  eingetragen, bevor ich `messung.py:240` aufgeschlagen hatte.
  - **ERLEDIGT am 2026-09-07 in 0147, Rücklauf 2 — kein eigenes Paket nötig, und die
    Diagnose oben trifft die falsche Hälfte.** Der Fall stand in
    `befunde/messung-0147/messung.py:233` (nicht unter `werkzeuge/`) und lautete
    `("genau einmal", "axb", "a", "ayb")`. Beide Hälften machen ihn grün, aber sie sind
    nicht gleich viel wert: Die oben vorgeschlagene — Erwartung auf `yxb` — lässt die
    Nadel am **Anfang** stehen, und dort gibt der kaputte Rumpf `neu + text[len(alt):]`
    ebenfalls `yxb`; der Fall bliebe grün unter genau dem Fehler, für den er da ist.
    Gewählt wurde deshalb die andere: Nadel auf `x`, Erwartung `ayb` bleibt. Die
    Ersetzung sitzt damit in der **Mitte**, `a` und `b` bezeugen Kopf und Fuß, und der
    kaputte Rumpf gibt `yb` und reißt. **Die Lehre daraus ist schärfer als die oben:
    Nicht jede Berichtigung, die eine Selbstprobe grün macht, stellt sie wieder her —
    die Erwartung ans beobachtete Verhalten anzupassen ist die schwächere Hälfte und
    hier fast die falsche gewesen.**
- 2026-09-07 (0214) — `befunde/messung-0180/` trägt jetzt einen datierten Kopf,
  `messung-0130`, `-0132`, `-0137`, `-0139`, `-0156`, `-0172`, `-0173` nicht. Dieselbe
  Krankheit, siebenmal. Kein Vorschlag von mir: Ob ein Sammelpaket „jede `lauf.txt`
  bekommt einen Herkunftskopf" mehr wert ist als sieben Einzelläufe, entscheidet der
  Projektmanager, und ich habe keinen Beleg, dass eine der sieben schon einmal falsch
  zitiert wurde. 0180 hatte den (Prüfung 0213).
- 2026-09-07 (0188, weiter offen) — `bezeichner_riegel` und `pruefstand` haben weiter
  keinen Rotnachweis. 0212 nimmt sie ausdrücklich nicht mit.

## Worauf ich unsicher bin

**0214.** Zwei Dinge.

*Erstens, die einzige Zahl im Kopf, die ich selbst gezählt habe:* **9/20/8/7/9.** Sie sind
die Längen von `std::array<…, N>` an fünf Stellen in `zahlwort_riegel.cpp`, also die
Zahl, die der Riegel druckt, wenn er `.size()` druckt — nicht nachgeprüft habe ich, dass
er genau diese fünf Arrays zählt und keine Teilmenge. `pruefung-0194` nennt dieselben
fünf Zahlen unabhängig; zwei Herleitungen, dasselbe Ergebnis. Im Kopf steht ausdrücklich
„am Quelltext gelesen und nicht gemessen".

*Zweitens, eine Entscheidung:* Der Kopf ist **deutsch**, obwohl er heute geschrieben ist.
`lauf.txt` ist ein durchgehend deutsches Dokument, und ein Kopf, der die Zeilen unter sich
in einer anderen Sprache zitiert, ist schlechter lesbar als einer, der die Sprache hält
(CLAUDE.md, „die Sprache folgt dem Dokument"). Dieselbe Aufteilung wie bei 0212.

