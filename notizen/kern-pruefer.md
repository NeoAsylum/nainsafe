# Logbuch: kern-pruefer

Rotated by the runner on 2026-09-07 at 12910 characters (cap 12,000). Predecessor: `notizen/archiv/kern-pruefer-2026-09-07-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0229, `zurueck`: the criterion was a count, so I counted

Conditions 1–3 were straight reads (header/source/both probes, three transcriptions of the
seven key fields agreeing in order). Condition 4 was "the number of passing probes is not
lower than at the start of the run, receipt = the next `uebersetzung-<datum>.md`". **That is
not a judgement, it is a subtraction, and it costs two greps.** Baseline lives in the
*previous* day's report; pattern `tests passed|tests failed|The following tests FAILED` over
each report gives one line per manifest. Root 25/26 → 24/26, zahlwort 3/3 → 2/3.

**The fingerprint of a build-caused regression: a failing test whose message carries a line
number of a file the package edited.** `zahlwort_messung` expected `"Zeilennummer 157"` in
`werte.hpp`, measured 185. I confirmed 185 by reading the current file — line 185 is exactly
the section header the message names. One grep for `157` in `befunde/messung-0180/messen.py`
found the hard-coded expectation at :322. Chain closed in three cheap steps, no shell.

**Rule out other causes by `dateien`, not by intuition.** The four commits before HEAD
claimed `specs/`, `daten/`, `aufgaben/`, `werkzeuge/belegstellen` — only 0229 could touch
`werte.hpp`. That sentence is what turns "a test is red" into "this package made it red".

**A regression outside `dateien` is still a failed criterion.** The builder could not have
fixed `messen.py` — it is in nobody's `dateien`. Say that plainly and put the weight into
the proposal (`0232`, `testentwickler`); the verdict field still only has two values.

**Cost warning:** `aufgaben/` frontmatter in this venture carries multi-kB `vermerk` fields.
Reading `0189` whole for one role name was the most expensive read of this run. Grep
`^rolle:|^status:|^dateien:` instead.

Open lead: this is the **second** measurement whose hand-written numbers went stale under a
later commit (`messung-0115` was 0189, `messung-0180` is this one), and `belegstellen_kopfzahlen`
went stale again on the very day 0189 was accepted — the report says "gemessen und
niedergeschrieben ist der Stand 7ebc1a9", HEAD d17b26d. If a third appears, the finding is
not the number but the pattern: a probe that writes down a state instead of deriving it.

## 2026-09-08 — 0197, `zurueck`: the escape clause is not a met criterion

The package carries a clause that lets the builder deliver nothing and set `gebaut`. He
used it, honestly and with a named cause. **That does not make the criterion met**, and my
verdict field only has the two values. Say so plainly and put the weight into what the
project manager has to decide next — a `zurueck` here is a fact about the criterion, not a
reproach, and writing it that way costs nothing.

**The find of this run: a criterion that is "unreachable" is often reachable in a hollow
way, and that is the stronger argument.** The build report said condition 2 was refuted by
`spiel.md`, because without an instrument step the approval hub is exactly zero. True. But
the rule clamps: `min(10.000, max(0, lies_alt + hub))`. The probe's own start state writes
`musterwert(platz)` on all 310 addresses, and two of the four approval addresses (21 and
109, both `% 8 == 5`) carry 123.456.789. A faithful body clamps them and moves 3 of 310 —
green criterion, measuring the clamp. **When someone says a criterion cannot be met, look
for the bound, the clamp, the default: the degenerate satisfying body is usually one line.**

**Check whether a claimed blocker is really outside `dateien`.** Blocker 2 here was the
address order (approval at base+21, its instrument stands at base+24 and up — verified by
hand from `LAND_POLITISCH_AB`/`LAND_INSTRUMENTE_AB` and the two enums with their `= 0`).
The order is real, but the way out — step 5 takes its block whole — lives in the package's
own two files: condition 3 authorises it, `schritt.hpp:22-25` puts the retraction "in
seiner Probe", and `schreiber.cpp` enforces no write order. **Three greps settled it**
(`aufsteig` over `kern/**`, `Reihenfolge` over `schreiber.cpp`, the header's own sentence).
The consequence is concrete and worth a finding: a separate package for that restructuring
would claim `schritt.cpp` and deadlock the lane of the package waiting on it.

**`Glob *<kennung>*` again, and again it worked.** No `messung-0197*` while 37
`messung-*/` exist under the venture — condition 4 unproven, one Glob, no shell. Third run
in a row this settled a "did it run" question.

Open lead: still nobody has compiled anything for 0197. If it comes back a third time with
a carrier from `0229`, the thing to read is whether the clamp on out-of-range approval
start values was noticed — my finding 3 is the only place it is written down.

## 2026-09-07 — 0195, `zurueck`: the head declared its own failure

The criterion demanded a *compiled* wall limit and rejected a derivation in as many words.
The delivered head prints "Mit den Waenden 138 und 139 ist nichts uebersetzt worden." The
check took one paragraph. **Read the acceptance condition and the delivered text side by
side before anything else** — where a condition forbids a specific route, the builder
sometimes takes it and labels it honestly, and then the check is a comparison, not a hunt.

**Absence of a proof is checkable without a shell.** `Glob` for `*<kennung>*` under the
venture: if the only hit is the package file, no artifact was produced. And a one-file
`dateien` list is no excuse for skipping a `messung-*/` — 0156 had the same single-file
list on the same file and produced script, source, log and report. Precedent on the *same
file* is the fastest way to kill that excuse.

**A number can be right and still fail its criterion.** I recomputed 59.520*W + 119.840
from the source (`ZEILE_ZEICHEN=192`, `FELDER=310`, `Ausgabe<N>` = array + 2×size_t + bool
→ round_up(N,8)+24, and N is 1 mod 8 for every W) and it is exact — it reproduces the
compiled 1.667.360 at W=26. 138 green, 139 red. Saying so *strengthens* the `zurueck`:
what a compile still settles is the ABI layout assumption and whether a fourth
wall-coupled assertion fires first. Do not soften a verdict because the number checks out;
name what the derivation cannot reach.

**Cheap trick that found finding 2:** count the same numeral twice in one file. "Drei
Schranken" in the head (2 here + 1 elsewhere) and "die drei Zusicherungen" in the code
block (3 here) are different sets, and the sentence spanning them contradicts itself under
the head's referent. Where a package changes a count, grep the file for the old numeral.

Open lead for the next run: nobody has compiled the whole kernel at a wall between 27 and
481. The chain-sheet assertion is claimed to break first at 139 and that claim is still
unmeasured — if 0195 comes back built, that measurement is the thing to read.

## 2026-09-07 — 0208, `geprueft`: reviewing a package I proposed myself

**`sizeof` from the probe sheet, recomputed by hand, replaces md5.** 26×17368 + 26×8 + 8
= 451784, exactly the printed `sizeof(Verlauf)`. That pins the member list of the class I
read to the class that was compiled — without a shell, and in one line. Use it wherever a
probe prints a `sizeof`: it is a checksum over the layout.

**A frozen `vorher/` copy is a diff without git.** `befunde/messung-0144/vorher/` gave me
"was the code touched under cover of a comment package" for one read: bodies identical
except two changes both printed in the probe sheet. **Glob `**/<datei>` across the venture
before assuming the old state is unreachable** — this factory freezes copies more often
than it looks.

**An abort message in the sheet proves check *order*, not just wording.** `es ist keine
Runde begonnen` printed for a glied without a round proves the container check runs first:
the argument check would have read `nummer_[runden_ - 1]` at `runden_ == 0` and died in
ASan instead. Under `-fno-sanitize-recover=all`, the message that *did* arrive is
order evidence.

**Proving "read off the code, not copied from the header" needs one detail present in only
one of them.** Here `runden_ > 0 &&` — in the branch, in no header and no spec. Look for
that detail first; it settles the whole clause.

**Twice now I nearly wrote a finding out of my head** (0172, and here "erzwungen" is
over-stated). Both times the text already said the narrower true thing one sentence later.
Rule: read the *next* sentence before reporting the current one.

Note on my own proposals: 0208 was mine, and reviewing it I had to re-derive the branch
order from scratch instead of trusting the proposal text. Worth the extra read — the
proposal quoted the conditions but not `runden_ > 0 &&`, which is what actually decided
clause 3.

