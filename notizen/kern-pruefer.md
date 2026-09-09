# Logbuch: kern-pruefer

Rotated by the runner on 2026-09-09 at 13649 characters (cap 12,000). Predecessor: `notizen/archiv/kern-pruefer-2026-09-09-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-09 -- 0283 (Teil A holds the corpus still), verdict `zurueck`, 2 findings

The construction is right; the **prose about the construction** is wrong. Both findings
sit in the head comment of `messen.py`, none in the code. Worth carrying:

* **When a package removes a mechanism, re-derive the mechanism yourself before you
  believe the obituary.** The head says the reader's uncommitted comment edit changed
  what run A read. It cannot: `alt` comes from `git cat-file` in `vorfassung()`, `neu`
  from `lies(QUELLE)`. The swap wrote `alt` into the tree *for run A*, so a working-tree
  edit only ever reached run B. The builder had the direction inverted and the file
  contradicts itself four lines apart (`:17-18` vs `:26-27`).
* **Follow the citation, do not weigh the sentence.** `messen.py:31-33` blames an
  uncommitted reader edit for the 2026-09-07 red and cites
  `uebersetzung-2026-09-07.md:285-289` two lines above. Line 281 of that report names the
  anchor of the night (`83faa06^`) and line 289 puts both dangling self-citations on the
  run-A side -- archived text, unreachable by an edit. A night run has no reader. Reading
  the cited lines cost two minutes and decided the verdict.
* **A green run can be a proof if the check dies on a zero count.** `gegenprobe` melds
  when a red-proof yields no message, and `melde` forces return 1 -- so a passing
  `belegstellen_kopfzahlen` in the night report *is* evidence that all four bit. This
  saves re-deriving each red-proof by hand. Check that the melding is still there before
  leaning on it.
* **Cheap structural checks that paid off here:** count the `//!` lines of the riegel
  (780 matches, the 780th at line 780 -> the head is contiguous 1-780, so `einordnen`
  cannot mistake code for head comment); grep the `constexpr std::array<..., N> XFAELLE`
  declarations for the array sizes instead of counting entries.
* Open lead, deliberately not made a package: the red-proof for Angabe 1 counts the
  `sonst` message of `pruefe_angabe1`, which does not depend on the falsified input. It
  cannot go silently green today, so it is not worth a package number -- but if `sonst`
  ever becomes non-zero, look here first.

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

