# Logbuch: kernbauer

Rotated by the runner on 2026-09-10 at 14777 characters (cap 12,000). Predecessor: `notizen/archiv/kernbauer-2026-09-10-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-10 -- 0288 (two unlocated sums, and what it takes to reach one of them)

Four files. `kern/src/werte.cpp`: new `pruefe_handelssumme` in the anonymous namespace, called
before each of the eight partial additions of the two-argument `handelsvolumen`.
`kern/src/schritt.cpp`: new `summe_der_last_pruefen`, called in `politiklast` after the product
was hoisted into `beitrag`. Plus one case per message in `werte_probe` (`probe_handelsdecke`,
both ends, own Riegel and Sollzahl) and `schritt_probe` (`probe_decke_der_politiklast`).

- 2026-09-10, **the lesson of the run** -- **A first partial sum can never overflow, so a
  probe for a summing latch needs two summands that the state can actually produce.** For
  `handelsvolumen` that is free: its eight summands are addresses. For `politiklast` it is
  the whole difficulty -- the summands are `mal_geteilt(menge, hub, 10.000)` over the four
  instruments, and only a moved instrument stand contributes at all. So the carrier has to
  move **two** stands of one country, and it can only move the three that have a path (T61).
  The tariff line drops out (it reads a world price and dies on the sample layout, measured
  by 0284), which leaves exactly leitzins and haushalt -- and both are payable because their
  quantities are the same number: `land.US.staatsschuld` carries 10.000 basis points on this
  layout, so `schuld(US) == bip(US)`.
- 2026-09-10 -- **The three numbers this construction rests on, measured, so the next run
  does not measure them again.** `bip(US)` on `ausgangslage` is **3.000.012** (its three
  addresses 0, 4 and 8 carry `1.000.000 + platz`). `musterwert` is **0** on both
  `land.US.instrument.leitzins.stand` (24) and `.haushalt.stand` (32) -- both indices are
  divisible by eight -- so the hub is the path value itself and the sign is a plus. The path
  values are multiples of 10.000, so the line divides out exactly: 1,5e16 gives 4,5e18 per
  line (the sum still fits), 2e16 gives 6,0e18 (it does not).
- 2026-09-10 -- **No `datei.cpp` with a line number in a core comment, ever.**
  `belegstellen_riegel` reads every build source except `bau` and `befunde` and counts a file
  name with a line number after it as a finding; three absolute counts in its own head are
  asserted nightly by `belegstellen_kopfzahlen`, which is green. A bare pattern hit moves
  those counts too, so I cited functions and packages only. Same reason not to write a
  paragraph that holds a document name, one of the words Abschnitt/Absatz/Ueberschrift **and**
  a quoted heading -- that is a Zitat and shifts the second count. Quoting `spiel.md` without
  those words is safe; `bip` has done it since 0242.
- 2026-09-10, **what I am unsure about, for the project manager:** four things.
  **(a) I cannot compile.** The riskiest new line is `satz.pfadstand[l][...] = pfadwert;` in
  `schritt_probe` -- a copy of a `constexpr` carrier into a mutable local, which package 0284
  already does one probe above.
  **(b) Predicted, so a divergence is visible instead of arguable:** both probes green,
  `werte_probe` printing `Riegel "Handelssumme verlaesst i64": 2 Meldung(en), erwartet 2` and
  `Handelsdecke: 295 Zeichen`, `schritt_probe` printing `Politiklast: je Zeile
  4500018000000000000, Summe 9000036000000000000`. Reverting either function to the bare
  `plus` must turn exactly the new case red, at `!enthaelt(..., "plus: Summe")`.
  **(c) The 176 and the 297** in the head of `pruefe_handelssumme` are hand counts. Nothing
  asserts them -- the probe prints the measured length beside the 297 and asserts only that it
  stays below the buffer. Prints it something other than 295, the count is off and the comment
  needs the correction, not the code.
  **(d) The `politiklast` pair brackets the ceiling, it does not pin it.** One unit of path
  value moves the contribution by about 300, because the summands there are computed and not
  addresses. That stands in the probe head. The one-unit bracket exists only at
  `handelsvolumen` and at `bip`.
- 2026-09-10 -- **Left over, proposed as `0299`:** five more unguarded sums in `kern::werte`
  (`marktkorb`, `korbbestand`, the one-argument `handelsvolumen`, `fondsvermoegen`, the tariff
  line of `schaden`). Same defect, no finding behind it, and at seven copies the checked
  precondition stops being a shape and becomes a building block for `festkomma` -- that
  decision is condition 4 of the proposal and not mine to take in passing.

## 2026-09-10 -- 0286 (the counting mark, and a second mutant for it)

Two files. `werkzeuge/zahlwort/zahlwort_riegel.cpp`: constant `ZAEHLMARKE =
"Zaehlmarke: keine Groesse aus T48"`, `Zaehlung::marken`, the declaration branch of
`zaehle` turned into `traegt_nummer == traegt_marke -> Mangel` (two wordings), `zaehlbild`
gained `marken=`, `ZAEHLFAELLE` 7 -> 9, plus `ohne_zaehlmarke`/`markenprobe` and a head
section on the three kinds. `kern/include/kern/werte.hpp`: the mark in `pfadstand`'s doc
block, and the head sentence at `:46` that claimed the riegel only knows numbered
declarations.

- 2026-09-10, **the lesson of the run** -- **The third kind cannot be proved by the probe
  that was already there.** The first mutant moves a *number*; the mark shows itself in a
  Mangel that **stays away**, and an absent Mangel looks identical when the riegel reads no
  mark at all and excuses every declaration without a number. So a second mutant, the other
  direction: take the mark out of the text, demand exactly one Mangel more, counts
  unchanged. That is condition 4's second half, and it is the only thing in the tree that
  separates "reads the mark" from "excuses everything".
- 2026-09-10 -- **`traegt_nummer == traegt_marke` is the file's own idiom, one level up.**
  `felder_aus_traeger` already writes `ist_jahrgang == ist_schluessel` for the same job:
  the admissible kinds must partition, so *neither* and *both* are each a Mangel. Both
  matters here beyond symmetry -- without it, adding the mark next to a wrong number would
  be a way to silence the number.
- 2026-09-10 -- **The Markenprobe reports without a subject instead of failing.** `marken
  == 0` is a legitimate header (every declaration numbered), and 2 would be wrong there. It
  is also required for compatibility: `messen.py` case A3 runs the riegel against the
  pre-0155 `werte.hpp`, which has no mark, and expects code 1.
- 2026-09-10 -- **Checked before writing: what else reads these two files.**
  `belegstellen_riegel`, `bezeichner_riegel` and `kennzeichen_riegel` read the whole venture
  minus `bau` and `befunde`, so both files are in their corpus. In `werte.hpp` I kept the
  new prose free of the three plural nouns the riegel counts (`Groessen`,
  `Jahrgangskonstante[n]`, `Deklarationen`) except at `:46`, where `Deklarationen` was
  already a Fundstelle without a claim and stays one -- so the Sorte-3 picture in the
  probe's output keeps its three entries (lines 25, 32, 46).
- 2026-09-10 -- **Where I did *not* touch `messen.py`'s mutants, deliberately.** All five
  Teil-B strings and both Teil-C strings are untouched, and the two new `ZAEHLFAELLE` cases
  do not tear under any of them (M3 inserts at most one number in each; M1/M2/M4/M5 never
  reach `zaehle`). `ordne_zu` demands a bijection, so an extra torn case would have been a
  red `zahlwort_messung` caused by me.
- 2026-09-10, **what I am unsure about, for the project manager:** four things.
  **(a) Predicted numbers, so a divergence is visible instead of arguable.**
  `zahlwort_riegel` **green**, code 0. Header line: `22 Nummern der Tabelle in 24
  Funktionsdeklarationen, 1 davon mit Zaehlmarke statt Nummer`. Self-test: `9 Faelle zur
  Zerlegung, 20 zur Zahlbehauptung, 8 zum Urteil, 9 zu den Zaehlungen und 9 zur
  Verdrahtung`. Empfindlichkeitsprobe unchanged (24 -> 25, line 32 `kardinal 24 gegen 25 ->
  rot`). Markenprobe: `genau ein Mangel mehr da (1 statt 0)`.
  **(b) I cannot compile.** The one line I would look at first is the ternary inside the
  Mangel message: two string literals of different length in a conditional expression. That
  is a composite pointer type `const char*` and is well-formed, but it is the only new
  construct in the file that is not already in it elsewhere.
  **(c) `zahlwort_messung` stays red, and its reason has not moved.** It aborts in Teil A
  on the `A2` literal `**Zweiundzwanzig Groessen in dreiundzwanzig Deklarationen`, which
  `werte.hpp:32` has said `vierundzwanzig` since `0284` -- explicitly not this package.
  What my change *would* fix once it gets there: A0 and the closing Gegenprobe, both of
  which want code 0 on today's tree and got 1.
  **(d) The Markenprobe has no mutant of its own.** Teil C proves the two halves of the
  Empfindlichkeitsprobe and nothing proves the new one red. Written up as proposal `0298`,
  with the dependency on the `A2` repair named -- a C3 added today would sit behind an
  abort and never fire.

