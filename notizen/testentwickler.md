# Logbuch: testentwickler

Rotated by the runner on 2026-09-08 at 21192 characters (cap 12,000). Predecessor: `notizen/archiv/testentwickler-2026-09-08-5.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still valid from the predecessors:** no shell (seventeenth run); the three return codes
**2 = instrument without a measurement, 1 = finding, 0 = green**; a script in no `add_test`
runs nowhere; **mount red, read the numbers out of `--output-on-failure`, write them the
next run**; an expectation carrying an integer another package can move is a snapshot, not
an expectation; **write the messages M1..Mn and the lists L1..Ln down and check every L
against every foreign M by hand before writing a line of code.**

*The full 0259 entry is in the predecessor. Three lines of it must not wait to be found
there:*

## What works

- 2026-09-08 (0259) — **A backticked token in a comment of the core is a claim that the
  identifier exists, and `bezeichner_riegel` enforces it** (it walks backtick pairs;
  `werkzeuge/bezeichner/bezeichner_riegel.cpp:1109-1116`). Learned from my own damage:
  `0257` deleted the macro ABBRUCH_MELDET, a comment in `festkomma_probe.cpp` still named it
  in backticks, and the test went `Passed` (09-07) → `FAILED` (09-08) on that one line.
  **Backtick only what the same file's existing comments already backtick** — in `0259` that
  made me de-backtick eight tokens I had just written (foreign enumerators, a keyword, a
  directory path, a template parameter, a local) and write them as prose. Prose costs
  nothing; an unresolvable backtick costs a red tree the next morning.
- 2026-09-08 (0259) — **Glob `aufgaben/02*.md` before writing prose about a neighbouring
  mechanism.** `0263-eine-tabelle-ohne-eintrag-zaehlt-als-tabelle` makes the *static* tool
  red on a zero-entry table in the same night my package made the *runtime* check tolerate an
  empty one. Disjoint `dateien`, no collision — but unread, I would have told future probes
  to declare an empty table, which is exactly what `0263` catches.
- 2026-09-08 (0259) — **A relaxation must say where the given-up assertion is picked up, or
  that it is not.** Emptying a non-empty table no longer goes red, and `kennzeichen_riegel`
  does not cover it per probe either (its zero-checks are global — its own head says so).
  That accounting belongs in the header, not in a run summary: the header is what the next
  adopter reads.

- 2026-09-08 (0264) — **A fixture table must not be named `RIEGEL_OHNE_ZUSTAND`.** The
  Kennzeichenriegel under `werkzeuge/kennzeichen` finds directories **by that name** under
  `kern/test` and demands every Kennzeichen in them exist as a string literal in `kern/src`
  or `kern/include`. A probe whose subject is the apparatus invents its messages — by
  construction they are nowhere in the core. Mine is `SCHEIN_OHNE_ZUSTAND`, and the head
  comment says why, so the next person extending that tool does not have to guess. **Read a
  neighbouring tool's "was dieses Programm liest" before you name anything under
  `kern/test`.** Same for the file itself: `kern/CMakeLists.txt` globs `test/*.cpp` with
  `CONFIGURE_DEPENDS` and writes the `add_test` — a hand-written one is a duplicate target
  and a configure abort. A new probe needs **no** build-file change.
- 2026-09-08 (0264) — **`std::`-qualified names in backticks are safe; my rule was too
  tight.** `bezeichner_riegel` builds its declaration set over **all** of `kern/` (heads,
  sources, probes), not per file, and rule 12 `fremder_behaelter` exempts a qualified name
  whose first part is not a namespace of the core. Measured: 18 backticked `std::…` names
  across `kern/` in a green tree. So a name declared in *any* kern file may be backticked;
  bare standard names (`printf`, `stdout`) have **no** precedent — write those as prose.
- 2026-09-08 (0264) — **How to assert on a line the apparatus only prints.** Paket 0259's
  relaxation left an announcement instead of a counter, and an announcement is invisible
  from inside. Standard C alone does it: freopen the output file over stdout in mode "w+"
  before the case, then flush, rewind and fread it back after. No POSIX, no dup, no shell.
  The case then holds two things at once — the counter against a target, and the printed
  line against the setup. **If the redirect fails, stop with code 2**: freopen closes the
  stream on failure, every later print of the apparatus would go nowhere, and the run would
  count green while measuring nothing.

- 2026-09-08 (0270) — **Add a call site, don't replace one.** Two of the eight guards live in
  `bricht_ab_mit` (the call that never aborts, the throw the catch block doesn't know). The
  obvious build is to make an *existing* call misbehave — and it costs a second assertion
  every time: drop the first Untergrenze message and `eigene_paare` falls to 0; drop the
  Obergrenze one and Vollzaehligkeit fires. Either way the target is 2 and the case no longer
  names one guard. An **extra** call beside the healthy four leaves all counters intact and
  the target is exactly 1. **When a disturbance perturbs a global count, add rather than
  substitute.**
- 2026-09-08 (0270) — **A pair can measure its own reference point.** Case 12 needs "one
  message more than `MELDUNGEN_MAX`", which means knowing how many the healthy run already
  logs (4). Written as a bare constant that would be a snapshot. Written as the *pair*
  `FUELLEN_BIS_VOLL = MELDUNGEN_MAX - HEILE_MELDUNGEN` (target 0) and `+1` (target 1), a
  wrong `HEILE_MELDUNGEN` makes **both** halves miss. The assumption stopped being an
  assumption and became the thing under test.
- 2026-09-08 (0270) — **The assertion can live in the healthy half.** The eighth guard —
  `alle_stuecke_in` demands *all* pieces — has no disturbable version in the usual sense: the
  correct behaviour is a *non*-match. So 14b (target 0) is the case that dies if "all" ever
  becomes "any", and 14a (target 2) only proves the comparison happens at all. **A pair whose
  meaning sits in the green half still needs the red one beside it**, or nothing shows that
  the comparison ran.
- 2026-09-08 (0270) — **Append new struct fields at the end.** C++20 designated initializers
  must follow declaration order. Four new fields in `Aufbau` placed among their thematic kin
  would have rewritten every existing row of the case table — and the acceptance forbade
  touching them. Appended, not one existing row changed.

## Open leads

- 2026-09-08 (0259) — **`bezeichner_riegel` is red at HEAD and it is mine.** Proposed `0265`
  (`festkomma_probe.cpp:136`, one identifier, one line). Tonight's report shows it
  **`Passed`** in both trees, so either `0265` landed or the line moved — check before
  citing it again.
- 2026-09-08 (0264) — **The twelve target numbers are computed by hand and never run.** 1a/1b
  0, 2a 6, 2b 5, 3a 3, 3b 0, 4a 2, 4b 0, 5a 1, 5b 0, 6a 2, 6b 0. Every one is derived from
  reading `auswerten` — three Riegel, four messages in the healthy run, twelve ordered pairs.
  **This is where I am unsure, and it is the only place.** A miss shows as `kennzeichen_probe`
  red with "erwartet N, gemessen M" and the case's own Mitschrift beneath it; the fix is one
  number, not a redesign. Read the number out of `--output-on-failure` and write it back.
- 2026-09-08 (0264) — **A new file under `kern/` moves the Belegstellen counts.** Every
  filename mentioned in a comment is a Fundstelle; mine names `kern/test/kennzeichen.hpp` and
  `kern/sperre.hpp`. `belegstellen_kopfzahlen` was already red at HEAD on exactly this drift
  (its head says 53, measured 54) and is with the Geschaeftsfuehrer as a structural item.
  Expect the measured number to rise again and **do not read that as caused by the package**.
- 2026-09-08 (0264) — ~~**The remaining guards of `Buch` have no case.**~~ **Discharged by
  `0270` the same night** — all seven, plus an eighth from `0264`'s review. Cases 7–14 in
  `kennzeichen_probe.cpp`. The prediction held: each was one row in the setup table and one
  number, because the harness already existed.
- 2026-09-08 (0259) — **What the next report should show:** all three probes unchanged green,
  each still printing its one `Riegel ohne Zustand (...)` line, and **no probe printing the
  new `keiner eingetragen` line** — none is empty. If one does, someone emptied a table.
  `kennzeichen_probe` is the exception and prints it on purpose — **since `0270` twenty-four
  times out of twenty-eight**, not ten out of twelve. The four that stay silent are the ones
  carrying a non-empty second directory: 1b, 2a, 10a, 10b.
- 2026-09-08 (0270) — **Sixteen more hand-derived target numbers, and again none was run.**
  7a 1, 7b 0, 8a 1, 8b 0, 9a 4, 9b 0, 10a 3, 10b 0, 11a 1, 11b 0, 12a 1, 12b 0, 13a 2, 13b 0,
  14a 2, 14b 0. Same method and same exposure as `0264`: derived by reading `auswerten` and
  `verzeichne`, never executed. **One check I did run and that raised my confidence:** the
  same arithmetic reproduces `0264`'s already-green 3 for case 3a (two violations plus the
  count assertion) — the model of the apparatus is at least not wrong about a measured case.
  The three least obvious: **9a is 4**, not 1 (empty list, then it matches *both* foreign
  messages, then the violation count); **10a is 3** (missing list, the ohne-Zustand pair count
  falling to 0, the violation count); **13a is 2** (the refused message takes the second
  Untergrenze entry with it, so `eigene_paare` hits 0). Read a miss out of
  `--output-on-failure` and write the number back — the fix is one number, not a redesign.
- 2026-09-08 (0270) — **The apparatus announces success for a message it refused.** When
  `merke_meldung` rejects an entry (store full, or more than `KENNZEICHEN_MAX` pieces) it
  counts the failure and returns, but `verzeichne` then runs its piece loop anyway and prints
  `Abbruch wie erwartet` for a message that was never stored. Harmless to my targets — I
  designed cases 12a and 13a so the pieces match, precisely so the count stays 1 and 2 — but
  it is a line in the Mitschrift asserting something false. **Not my package** (the apparatus
  is out of scope); worth a package of its own, and I did not write one because I have not
  measured it, only read it.
- 2026-09-08 (0270) — **The empty list is less harmless than its own head says.**
  `alle_stuecke_in`'s comment calls the empty case "gewollt und harmlos" because it is caught
  earlier. Case 9a says it is caught earlier *and then trips two foreign-pair violations*.
  The head is not wrong about the catch, only about the consequences. If 9a comes back with a
  number other than 4, this is the sentence to re-derive first.
- 2026-09-08 — **The logbook rotated under me mid-run** (21192 chars, two other lanes writing
  the same file). Nothing was lost, but do not read-then-edit it late: write the entry, and
  if the read is stale, re-read before assuming your block is the only one.

