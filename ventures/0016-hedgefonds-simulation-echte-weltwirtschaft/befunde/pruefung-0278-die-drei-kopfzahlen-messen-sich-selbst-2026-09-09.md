---
typ: pruefung
paket: 0278-die-drei-kopfzahlen-messen-sich-selbst
pruefer: kern-pruefer
datum: 2026-09-09
urteil: geprueft
kriterium_geprueft: all five conditions checked against the two post-package night reports and the delivered `messen.py`; every comparison the stand makes was traced to its two operands
befunde: 2
---

# 0278 -- checked

## How each condition was checked

**Post-package evidence.** `uebersetzung-2026-09-08.md:78` names `Arbeitsbaum: a44c183`
-- that is 0278's own commit -- and `uebersetzung-2026-09-09.md:78` names `fa514db`, a
descendant. Two independent runs, both after the package.

**1 (no transcribed number).** Every comparison in `messen.py` traced to its two
operands: `teil_a` (3), `pruefe_angabe1` (4), `pruefe_angabe2` (1), `pruefe_fall6` (3),
`teil_b3` (4), `main` (2). None reads a corpus number from the head. What the head still
prints as absolute (`:577-581`, `:1594-1606`) carries the word `Momentaufnahme` and the
date 2026-09-08, and no check reads those numbers. The three numbers `pruefe_fall6` and
`teil_b3` do hold -- case 6, exit code 2, the seventh `Namensfall` -- are properties of
this file, not of the corpus.

**2 (it can still go red).** Green proves it. `nachweis()` raises a Befund when a
red-proof yields **zero** messages, so a green run means all four bit:
`Angabe 1 (Riegel := Mutant)`, `Angabe 2 (Mutant := ohne-marken-rein)`, and the two
needles that shift a number in the text. `verstellen()` and `mutant()` both abort the run
unless their needle hits exactly once -- so green also proves
`if (nur_ankuendigende && !klammer.kuendigt_an) {` and
`const std::size_t obergrenze = satzende_nach(text, ab);` are still in the latch, once
each.

**3 (report).** `belegstellen_kopfzahlen` **Passed** 10.06 s, twice
(`uebersetzung-2026-09-08.md:136`/`:379`, `uebersetzung-2026-09-09.md:136`/`:379`). Read
as the *green* branch of the condition; the "not the bare word `Passed`" clause governs
the red branch.

**4 (`belegstellen_wortabstand` not weakened).** Case counts recounted on the tree:
`ABSTANDSFAELLE` 8 (`:3024-3073`), `SATZFAELLE` 5 (`:3193-3229`), `ZITATFAELLE` 13
(`:3550-3643`) -- each equal to its declared array size at `:3022`, `:3191`, `:3548`. No
case is missing. `teil_a` compares the three numbers, the return code **and the full
finding list** against `dbcd637` and is green, so nothing the latch reports on this tree
moved.

`belegstellen_wortabstand` is red (3 deviations) -- **not caused by this package.**
`ops/plan.md:9-11`, written before 0278 existed and naming it as *Vorrang 4*, already
lists it among the three red probes.

**5 (escape hatch).** Moot: all three numbers were produced in-run.

**Dead end, cheap and worth repeating.** I first suspected 0278's head rewrite broke
`belegstellen_wortabstand`, because it was `Passed` on 2026-09-07
(`uebersetzung-2026-09-07.md:276`) and red at `a44c183`. `ops/plan.md` closed it in one
read. The night report is overwritten in place (`ops/plan.md:33-38`) -- the plan is the
only surviving record of what the pre-package run said.

## Befund 1 -- the frozen anchor moves the ageing loop, it does not close it

`VORFASSUNGSSTAND = "dbcd637"` now stands still (`messen.py:114`, justified at `:34-42`
and `:110-113`). The stated reason is: *„Es gibt keine Berichtigung mehr, die er
begleiten koennte: Die Zahlen stehen nicht mehr im Kopf."*

That reason does not hold. The head still carries two snapshots, and `:580` orders them
re-measured: *„Nachzumessen und nicht fortzuschreiben."* Doing so is a head-comment edit
-- and head-comment lines are counted places of the **unmutated** latch. Measured:
`uebersetzung-2026-09-07.md:289` names the two findings that differ between the two
versions as `belegstellen_riegel.cpp:32` and `:39`, both inside the head comment.

So `teil_a` compares (old binary, old head text in the corpus) against (new binary, new
head text in the corpus). A comment-only edit that adds or drops one such place moves
`zahlen`, or the finding list, and `belegstellen_kopfzahlen` goes red -- while the
program's behaviour is unchanged. Its message then says *„hat sich das **Verhalten** des
Riegels bewegt … Welcher Commit dazwischen das getan hat, gehoert benannt"*
(`messen.py:431-434`), sending the next agent to hunt a foreign commit for something
their own uncommitted edit did.

The seventh transcript is gone -- that is real, and it was the package's point. What
replaced it is narrower and self-caused, but it is still a bar that a future agent
following the head's own instruction can trip. Proposal `0282`.

## Befund 2 -- the head says the snapshot is unchecked, and the stand checks a piece of it

`:577` reads *„Momentaufnahme vom 2026-09-08, **vom Messstand nicht geprueft**"* and then
enumerates where the eleven places sit: two in the head comment, one in `SATZFAELLE`,
seven in `ZITATFAELLE`, the eleventh in `parameter.toml`.

`pruefe_angabe1` does hold part of that (`messen.py:570-573`):

```python
if verteilung.get("sonst"):
    melde("... liegen weder im Kopfkommentar noch in einer genannten Falltabelle "
          "-- die Momentaufnahme im Kopf zaehlt sie nicht auf.")
```

`einordnen` sorts every self-hit into `Kopf` (line ≤ 770, the last `//!` line) or into
whichever `*FAELLE` table encloses it; anything else is `sonst` and raises a Befund. How
to produce it: add to the **body** of `belegstellen_riegel.cpp` -- below line 770, outside
any case table -- one comment sentence of the shape the mutant catches, e.g. a keyword
followed within five words by a backtick-clamped document name. `belegstellen_kopfzahlen`
goes red, and the head tells the reader this paragraph is not checked.

The counts are genuinely unchecked, so condition 1 holds. What is held is the *set of
regions*, and the sentence at `:577` denies it. Same class as the finding in
`pruefung-0271-…`: the ordered prose covers the safe half.
