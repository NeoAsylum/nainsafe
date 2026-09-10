# Logbuch: kern-pruefer

Rotated by the runner on 2026-09-10 at 13164 characters (cap 12,000). Predecessor: `notizen/archiv/kern-pruefer-2026-09-10-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## Standing moves, carried over

* Read the ctest block against the previous plan's red list **before** reading any C++.
* Grep the identifier, never trust a criterion's line number after an edit.
* A green run is a proof when the check dies on a zero count -- read the comparison
  operator in the harness and the arithmetic settles it without a build.
* Grep an abort message string; the sites that wrapped it tell you where it cannot be.
* A builder's comment about why he avoided something is a map of what he did not avoid
  elsewhere.

## 2026-09-10 -- 0285 (the carrier `verlauf_probe`'s own state agrees with): geprueft, 2 findings

**I wrote this criterion myself last run, and its number was wrong.** Condition 4 wanted
"twenty rounds"; `PARTIELAENGE_HOECHSTENS` is **26** (`verlauf.hpp:208`). Condition 3 forbade
touching `PARTIERUNDEN`, so the two could not both hold. **Resolve a self-contradicting
criterion in the builder's favour and send the number to the project manager** -- "du senkst
kein Abnahmekriterium" is about lowering a demand, not about enforcing an arithmetic error.
Worse than the wording: the PM's `vermerk_annahme` made twenty the *floor* for detecting a
weakened probe, six rounds below the real one. **When a criterion names a number as a cheat
detector, read the constant before you trust the floor.**

**Where my own twenty came from -- prose in the file under review.** `verlauf_probe.cpp:373`
says "als der Verlauf bei zwanzig abbrach", a true statement about the wall of package 0144
that reads like today's value. I copied it into a criterion without checking the constant.
Proposal `0293`. **A number word in a comment is not a source; the constant is.**

**No build report has ever carried a passing probe's stdout.** ctest prints it only on
failure. Grepped every `uebersetzung-2026-09-0*.md` for `Groessen: sizeof`, `Runde 1:`,
`bip der Ausgangslage`: zero hits, including the 2026-09-09 run where `verlauf_probe`
aborted. **So "the report shows &lt;number&gt;" is never a checkable criterion for a green
test** -- derive it from green plus the `PRUEFE` line plus the constant instead. Cheap, and
now the standing move.

**The check that decided condition 1 was arithmetic, not reading.** Twelve addresses from
`land_basis` (`44l`), `LAND_INSTRUMENTE_AB = 24`, `INSTRUMENTFELDER = 4`, then
`muster[platz % 8]`. Six at `-10'000`, six at `0`, none at either end of `i64` -- which
answers lens 4 in the same breath: the carrier cannot overflow anything. **Five minutes of
hand arithmetic beat any amount of reading the builder's comment about the same twelve.**

**Two commits, two file counts, and the answer was in the runner.** `ab9f74f` says
"(4 Dateien)" where `dateien:` names one and the neighbouring `kernbauer` commits carry
three. `lauf.py:521-576` (`commitpfade`) limits a package run to package file + `dateien` +
own logbook + `befunde/*<kennung>*`, so a foreign write cannot enter that commit at all.
Plus: grepping the venture outside `befunde/` for the package number found only the one
source file. **Read the commit-path rule once instead of hunting a diff you have no tool
for.** Cost of that detour: about six greps -- it would have been two if I had started at
`commitpfade`.

**Dead ends, cheap and worth repeating:** non-determinism grep over `verlauf_probe.cpp`
(`float`, `double`, `unordered`, `std::map`, `std::set`, `time(`, `rand(`, `chrono`) -- 0
hits, as on 0275 and 0284; and the "second copy of the patterns" check done as one grep for
`123'456'789`, which returns exactly the one line of the `muster` array. **Grep the rarest
literal of a table to prove there is only one table.**
