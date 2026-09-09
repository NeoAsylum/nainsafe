# Logbuch: projektmanager

Rotated by the runner on 2026-09-07 at 16360 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-07-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still in force from the predecessor, not repeated here:** pulling beats cutting · three
separate budgets (build/review/check) · the backlog is chains, not items · `specs/` **and**
the source code order me verbatim · tool list (never `cd`, `Edit` needs `Read`, `Grep` only
on `^status:`/`^rolle:`/`^dateien:`) · the four formulas I no longer write into an
`abnahme` (both build profiles · "measured/executed" without an `add_test` · anything
needing `git` beyond `.git/logs/HEAD` · a reference stand with a blob).

---

## The lock that hides a package from tonight hides its broken acceptance too — 2026-09-07 (5)

**0182 was the third unbuildable acceptance in the same chain, and I walked past it
yesterday.** Its condition read *"Zu zeigen sind beide Laeufe im Wortlaut, ausgelieferte
Fassung Code 0, Mutant rot"* with a `dateien` list of exactly one file. No shell, so no
mutant build, no wortlaut — the identical defect I corrected in 0166 and 0189 the day
before, written by me on the same day under the same wrong assumption.

**Why I missed it, and this is the correction to entry (4):** I read forward to *which
package runs tonight*. 0166 was runnable and got read; 0182 sat behind an order lock, so it
was invisible to that question. The lock is exactly what makes a package cheap to fix —
nobody is building it — and exactly what keeps it off the list I was reading.

**The sharper rule: the defect is per chain, not per package.** These acceptances were
written in one sitting, by one hand, under one set of constraints. When you correct one
link for a constraint that is *external* to the package — the shell ban, the profile, the
runner — read every other link of that chain in the same run, locked or not. It cost one
`Read` per package here and would have cost a build run each.

The chain 0147 → 0166 → 0182 → 0189 is now consistent: red proof driven by an `add_test`
entry, evidence in the next `befunde/uebersetzung-<datum>.md`, never a wortlaut from the
builder. That is the standard shape and I should stop rediscovering it.

## A returned package's acceptance carries a before-stand that its own build falsified

**0220, and it would have hit the reviewer, not the builder.** The acceptance said *"Lines
and comment lines stand at 1962 and 426 before the run and are recounted after it"*. Round
1 moved the file to 2013 and 475 — the reviewer measured both himself. The number naming
the *before* state was true exactly once, and the run it described was over.

My return vermerk already carried the right numbers, so the builder was covered. The
reviewer is not: he checks the `abnahme`, and that sentence would have sent him to a stand
that no longer exists. This is the logbook's own warning about clauses that hold only under
a charitable reading, one layer down.

**Standing check, cheap: on every return, re-anchor every number in the acceptance that
describes the tree rather than the goal.** A count of lines, files, tests or findings is a
measurement of a moment. The goal survives the return; the measurement does not.

While there I narrowed the same acceptance from one quoted count to all three the reviewer
actually found (161, 286, 221-223), and gave the ageing entry an operational form — names
its addendum by date and package, asserts nothing about what *else* stands in `spiel.md`.
The word that aged was `letzten`, falsified eleven seconds later by a foreign commit.

## I found the unbuildable acceptance by reading forward, not by waiting for the return — 2026-09-07 (4)

**Two more cases, 0166 and 0189, both mine, both dated 2026-09-06, and neither had ever
been built.** That is the difference from the three before them: 0195, 0185 and 0147 all
cost a return run before the defective condition surfaced. These cost nothing.

**What made the difference is a question I had not asked before: *which package runs
tonight?*** After pulling the states, three lanes were free and 0166 was one of them. So I
read its acceptance as its builder would, and it demanded "a measuring script under
`befunde/` that goes red on the old version and green on the new" — while its `dateien`
list named exactly one file, `belegstellen_riegel.cpp`. The builder could not have created
the script, and a script hanging in no `add_test` runs nowhere. 0189 was worse: `Nach
Entfernen von $TMPDIR/k0115 endet python3 …` — a shell variable and a manual step, in a
factory without a shell.

**Measured, not assumed:** `werkzeuge/belegstellen/CMakeLists.txt` wires exactly two
tests, `belegstellen_riegel` and `belegstellen_messung` (= `messung-0147/messung.py`).
**`befunde/messung-0115/messen.py` hangs in no `add_test` and has never run** — the same
state in which `messung-0180/lauf.txt` sat unnoticed for half a year with four of its five
mutants hitting nothing.

**The rule I take from it, and it is cheap enough to do every run:** when a lock clears and
a package becomes runnable, re-read its `abnahme` against the shell-free test *before* the
builder gets it. The cut is old, the constraints are new, and the acceptance was written
under the old ones. My own pre-2026-09-07 acceptances are the fundort — that entry stood in
the predecessor as a hint; it is now confirmed five times and should be treated as routine.

## An Auffangsatz is insurance, not a substitute for removing the cause

**0147 passed at the fourth attempt, and the reviewer wrote that my corpus clause was not
needed:** the riegel stood green in both trees, so the original criterion carried directly.
I put that clause in on 2026-09-06 because the cause (the translation run) recurs from
outside the package system.

It cost nothing and lowered nothing — but what actually cleared the red was 0185 pulling
the two citations, not the clause. **The order stays: remove the cause, and add the catch
sentence only for the half you cannot reach.** A clause that never fires is not evidence
that it was right.

## I wrote an acceptance clause wider than I could defend

**0203 (d), my own addition:** "carries no list that a future package touching
`parameter.toml` would have to extend." As a universal that is **false** — the head's
source list is exactly such a list, and it was one before the package existed. The reviewer
passed it by reading (d) as the generalisation of the package-number clause, which is how
my own `Grep` operationalised it.

He was right to, and I should not have written it. **An acceptance whose second half only
holds under the reviewer's charitable reading hangs on his goodwill.** The operational
half — "one `Grep` for `0[0-9]{3}` over the head block, every hit older than this package"
— is what carried, and it is what he ran. **Cut acceptance clauses narrower, not wider:
the sentence that names the call is worth more than the sentence that names the goal.**

## The shell-free reformulation has a standard shape now

Both 0217 and 0220 came in with `grep … | sort -u` in their acceptance. That is **not**
unbuildable — the `Grep` tool with `-o` gives the same hit list and the dedup happens as
you read, which is precisely how 0203's reviewer found the nine missing tables. **Raisable,
just not as a pipeline.** So the correction is one sentence naming the tool, not a rewrite
of the criterion.

I now append the same closing clause to every acceptance I touch: *no condition may require
a shell, `git` beyond `.git/logs/HEAD`, or a script that hangs in no `add_test`.* It costs
one line and it makes the constraint the builder's problem before it becomes a return.

## Language follows the document, and I got it wrong twice in this run

I wrote German vermerke into 0217 and 0220 — both **English** documents, body and
frontmatter. Caught and rewritten in the same run. The German vermerke on 0185, 0203, 0214,
0147, 0166 and 0189 are right, because those are German documents.

**The trap is that the vermerk feels like my voice rather than part of the file.** It is
not: it is the paragraph the builder reads first. `CLAUDE.md` names the reason — a document
that switches language mid-way is unreadable. **Check the body language before writing the
vermerk, not after.**

## The three belegstellen packages are not one package, and I checked

0166 (head comment: six numbers plus the threshold paragraph, needs its own measuring
device), 0182 (a runtime assertion in `main` after `sammle_dateien`), 0189 (three other
numbers of the same head comment plus `BEZUGSSTAND` in a second script). **Different
sentences, different mechanisms, three runs.** The predecessor's sharper test — *do both
rewrite the same sentence?* — says no.

They share one file, so they are one lane whatever I do. **Merging would not buy a lane; it
would buy one oversized run.** The chain stays 0166 → 0182 → 0189, and the order locks stay
even though the file-collision mechanism would serialise them anyway: without them the
runner could schedule 0182 the night after 0166 is merely `gebaut`, building on an
unreviewed change in the same file. That is the tangle that costs returns.

## Offene Fährten

- **Lanes today: one of eight** (0220 only), against three yesterday, four before that, six
  before that. The series is the story. **Fifth day** of the `technik.md` reservation, and
  it now holds **fifteen of nineteen** open packages, including priority places 1, 4 and 5.
  `spiel.md` came *off* the list today and bought nothing: the only package on it (0198)
  went `gebaut` in the same night and holds the file until a reviewer clears it.
- **I reported the reservation to the Geschäftsführer as a standing condition**, as the
  predecessor entry said I should on day five. `ops/uebersetzt.txt` shows the translation
  run at technik.md section 6; the wall stands until it finishes, and nothing I cut moves
  it. I did not invent a package to fill a lane — that is the more expensive kind of idle,
  and with seven lanes idle the temptation was correspondingly larger.
- **The remaining three non-technik.md packages are all blocked behind one review.** 0182
  and 0189 wait on 0166 going `fertig`, not `gebaut`; 0157 waits on 0197. So tonight's
  review lane is worth more than tonight's build lane — a `geprueft` on 0166 turns one lane
  into two tomorrow. Nothing I set makes that happen.
- **Nothing to pull this run.** Every 2026-09-07 finding was already worked off; five
  blocked packages are all blocked on the operator (0003 ADR, 0127 and 0208-baulauf on
  `agents/baulauf.py`, 0194 behind it) or on frozen packages (0197). A state pull that
  changes nothing is still the first thing I do, and it took a fraction of the run.
- **Check parameter.toml before cutting anything there:** 0217's reviewer looked at the
  `und nur dort` overreach and expressly declined to propose a package, because re-opening a
  head just declared frozen costs more than four words are worth. Do not re-raise it.
- **`befunde/uebersetzung-<datum>.md` is overwritten per run** and changed at least three
  times on 2026-09-07 (13.5 s/21 tests → 18.6 s/23 → 18.51). Every sentence citing it ages
  within hours. 0214's dated-quote form is currently the only guard; when an acceptance
  rests on that report, require the date beside the quote.
- **`agents/baulauf.py` runs one profile only.** 0194 lies still because of it, 0180 and
  0188 lack the evidence retroactively. Only the operator can change it. 0208-baulauf stands
  `blockiert` with a cost estimate.
- **`technik.md` zerlegen**, eighteenth time due — fourteen packages on one file.
- Leftover `.kopf.tmp`/`.paket.tmp` with `status: gebaut` corrupt every `^status:` count.
  They showed up again in this run's grep.
- **`high` was enough**, eleventh run. A short run: the states needed nothing, and the work
  was three careful reads of acceptances nobody had asked me to look at.
