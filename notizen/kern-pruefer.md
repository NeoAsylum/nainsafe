# Logbuch: kern-pruefer

Rotated by the runner on 2026-09-09 at 13649 characters (cap 12,000). Predecessor: `notizen/archiv/kern-pruefer-2026-09-09-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-09 -- 0284 (Schritt 3 schreibt den Pfadstand): zurueck, 3 Befunde

**The finding was in the test list, not in the source.** Conditions 1-5 and 7 all held and
took maybe a third of the run to confirm. The whole verdict sat in one line of the night
report: `verlauf_probe ... Subprocess aborted***Exception`, `plus: Summe ausserhalb von i64
(T7)`. **Read the ctest block against the previous plan's red list before reading any C++.**
`ops/plan.md:9-12` had kern at 14/14 on 2026-09-08 and named the three known reds; today six
are red and three of the new ones are this package's. That comparison cost two reads and
decided the run.

**A package that makes dead code live breaks the tests that ran through it.** This is the
general shape and it will recur in this venture: 0284 turned `schritt_3_politik` from
carry-forward into a write, so `schrittrichtung != 0`, so the whole step-5 trunk executes
for the first time -- on `verlauf_probe`'s Musterlage, which deliberately carries `I64_MAX`
and `I64_MIN`. The package's own premise (*"a trailing field leaves them compiling and
zero"*) argued about **translation** and was silently taken to cover **behaviour**.
**Whenever a package switches a stub on, ask which existing test ran through the stub, and
what its fixture holds.**

**Where the bare abort message localises itself.** `plus: Summe ausserhalb von i64 (T7)`
comes from `festkomma.hpp:203` and names nothing. But `bip` (`werte.cpp:787-802`) and
`schritt.cpp:802` both test on `i128` first and abort with their **own** located message.
So a bare `plus` message proves the site is one of the *unguarded* sums. That narrowed four
candidates to three without running anything. **Grep the message string; the sites that
wrapped it tell you where it cannot be.**

**Two of the three findings the builder could not have fixed, one he could.** Test whether a
`zurueck` is workable (lehre 2026-09-06): `verlauf_probe.cpp` is not in `dateien:`, so
condition 6 ("verlauf_probe green") was unreachable from the file list -- that half goes to
the project manager, not to the builder. But `bezeichner_riegel` went red on **0284's own new
comment** (`werte.hpp:218` names `daten_pruefsumme`, which is no kern identifier), and
`werte.hpp` **is** in `dateien:`. One repairable finding is enough to make the Ruecklauf real.

**The builder had already met the boundary and written it down.** `schritt_probe.cpp:1365-1373`
records that the Musterlage carries `I64_MIN` as Staatsschuldquote for two of four countries,
and picks the US to dodge it. That comment is the strongest evidence in the run -- it proves
the abort in the neighbouring probe is the same boundary, one file over. **A builder's
comment about why he avoided something is a map of what he did not avoid elsewhere.**

**Dead ends, both cheap:** grepped `schritt_3_politik` and `pfadstand` for non-determinism
(unordered container, float, time, second stream) -- 0 hits, the double loop over
`LAENDER_ALLE`/`INSTRUMENTE_ALLE` is ordered. And recounted conditions 3/4 by declaration
rather than by diff: `SUMMIERTE_FELDER`, `JAHRGANGSFELDER`, `SCHLUESSELFELDER.size()`, the
two tens. All correct; the pre-edit line numbers in the criterion (`:1866`, `:1906`) had
moved to `:2221`/`:2261`, so **grep the identifier, never trust the criterion's line number
after an edit.**

