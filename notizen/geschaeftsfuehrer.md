# Logbuch: geschaeftsfuehrer

Rotated by the runner on 2026-09-07 at 13071 characters (cap 12,000). Predecessor: `notizen/archiv/geschaeftsfuehrer-2026-09-07-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

---

## 2026-09-08, 16th run — the lock, and a new best tool

**`ops/reserviert.txt` × `^dateien:` is the best tool I have had.** It replaces the queue
arithmetic of 2026-09-07. The file is a *scheduling input* — `baulauf.py:startbereit`
counts each line as an already-scheduled package, so nothing whose `dateien:` hits it gets
planned. One `Grep "^dateien:.*technik\.md"` over `aufgaben/`, intersected with the `offen`
set, turned "it is stalled" into **15 of 19 open packages held by one line**. No report,
no finding and no role named this. Check `reserviert.txt` **first**, every run: it is four
lines long and it can silently hold the whole backlog.

**The project manager's `vermerk:` field is the richest single source about the queue.**
0208's vermerk named the reservation verbatim, the chain order, and why he set `offen` and
not `blockiert` ("you are scheduled only once it falls -- and then without a further run
of mine"). That is his reasoning, not a report about it. **Read the vermerk of the
priority-1 package before anything else.** It is cheaper than the package body.

**Zero proposals is a signal, not an absence.** My role says the `vorschlag` packages are
the best evidence I get. Today there were **0** (yesterday 8) — because the PM accepted all
of them. Do not read `0 vorschlag` as "the trades stopped proposing"; check whether the
numbers reappeared as new `offen` ids (here 0212–0225).

**What the 15th plan achieved — record it, it is the only test of this role.** All five
priorities and the entire "was quer liegt" list landed within one day: 0198 `fertig`
(geprueft, 2 minor findings), 0200 `fertig`, 0197 → `blockiert` (not `zurueck`, as
recommended), 0208-baulauf → `blockiert`, the standing red gone (`ergebnis: ok`, 25/25 and
13/13), `gebaut`-with-`geprueft` down from 3 to 1. `fertig` 147 → 169. **The pattern from
the archive holds: one statement, to the right hand, works.** The right hand for the lock
is the operator, not the PM — the PM had already done everything he could.

**I changed a recommendation and said so (B → C).** Not because B was wrong but because
the *cost changed shape*: on 2026-09-07 the translation run cost a red test, today it costs
the lock, and B does not touch a lock. Naming the old recommendation in the same paragraph
is what makes the change readable rather than a contradiction.

**A hypothesis I checked instead of writing down.** The index arithmetic said 284.520 −
275.563 = 8.957 characters of `technik.md` sit outside all 21 sections, so I concluded the
Vorspann was the untranslated remainder holding the reservation. I read lines 1–31: **it is
already English.** The arithmetic was right about the size and wrong about the cause. Cost:
one `Read` with `limit`. *Every "therefore the cause must be X" about a spec is one cheap
Read away from being checked — take it, always.*

**Without `Bash` again (16th run, as on the 15th).** The whole plan came from `Read`,
`Grep`, `Glob`. Do not go looking for tools. The working substitutes:
`ops/reserviert.txt` (the lock), `ops/uebersetzt.txt` (what the translator claims is done),
`befunde/uebersetzung-<datum>.md` (compiler and ctest verbatim, runner-made — read
`ergebnis:` in the frontmatter first, it is one line), `ops/kontingent.md` (up to two days
old — say the age), `ops/inhalt-<venture>.md` (section sizes), and `Grep "^status:"` over
`aufgaben/` with `output_mode: files_with_matches` per status. The `.tmp` files still
inflate the `gebaut` count by two (`.paket.tmp`, `.kopf.tmp`) — subtract them.

### Next run, in this order

1. **Is `ops/reserviert.txt` empty?** If yes, 0208 should have run by itself — check
   `aufgaben/0208-schritt-*.md` for `gebaut`. If no, the operator has not decided C, and it
   goes to him as the single point, **counted, not re-argued** (this is the second plan in
   a row on the translation question).
2. **Did the one number move?** 1 of 310. It may only move after 0208 is `fertig`; if it
   moves earlier the measurement is wrong. Name the old value alongside.
3. 0157 (`offen` behind blocked 0197) — did the PM set it `blockiert`? If not, it is a
   second case of the class and belongs in the plan as a class, not as an item.

---

## 2026-09-08, 17th run (second plan same day) — the lock fell by itself, and the queue emptied

**The three checks from the 16th run all paid, and two flipped the plan.** `reserviert.txt`
= `# frei`; 0208-schritt `fertig`; 0157 now `blockiert` (the PM did it). Every one of my
five priorities landed inside a day, second run in a row. **Run the "next run" list first,
literally — it is the cheapest signal in the repo.** Cost: three greps.

**The withdrawal is the entry that matters.** I put the translation question to the
operator twice; today its only remaining reason (the lock) was gone, so I withdrew it
instead of re-arguing. *A question whose cause has disappeared must be visibly withdrawn,
not silently dropped* — otherwise the operator spends his two hours on a dead item. Same
paragraph, one sentence, no defence.

**New best tool: `urteil:` across today's findings.** One grep, `^urteil:` over
`befunde/*2026-09-08*`, 40 lines, and the whole day's review verdicts are in front of me.
It found the sharpest item without reading a single package: `0189 ... urteil: zurueck`
against a `fertig` package. That turned out to be run 1 of 2 (the `-2` file is `geprueft`)
— **so always glob for the `-2`/`-3` variant before concluding anything from a verdict.**
The dead end was worth it: chasing it found the real thing below.

**The find of the day, and how it arrived.** `uebersetzung-2026-09-08.md` is *overwritten
in place*. Two `geprueft` findings from today quote it as `ergebnis: ok` / "Passed";
the file now reads `fehler` / `***Failed***`, and `git status` shows it modified in the
working tree. Both reviewers were right when they wrote. **Whenever a finding's line
numbers do not match the file it cites, suspect the file was rewritten, not the reviewer.**
My first instinct was the reviewer had fabricated. That would have been a false accusation
in a plan the operator reads.

**Counting method that worked.** `Grep "^status: fertig"` with `output_mode:
files_with_matches, head_limit: 0` prints `Found N files` as the first line of the
persisted preview — an exact count for ~25 kB of output I never read. `head_limit: 1`
does NOT give the total (it prints `Found 1 file`). Use `0`, read the preview header only.
Totals today: 253 packages, 231 `fertig`, 4 `offen`, 3 `vorschlag`, 3 `gebaut`, 5
`blockiert`. The two `.tmp` files still inflate `gebaut` — subtract them.

**Where the bottleneck actually was, and why "which role owns the open list" found it.**
Six of the seven open+proposed packages are `architekt` on `technik.md` — one lane. Then
one grep, `^dateien:.*kern/src/schritt\.cpp`, returned 8 files, **none of them open or
proposed**. That is the plan: the round's own source has no scheduled work. *Grep the
backlog for the file that carries the one number; if nothing open touches it, that is the
bottleneck, whatever else looks urgent.*

**A loop I could only see by counting.** 0115, 0166, 0189, 0227, 0232, 0233 — six finished
packages, same two files, all transcribing the belegstellen head numbers; red again this
morning because "Die Zahlen sind damit aelter als der Baum". `Grep "^dateien:.*<file>"`
counts a maintenance loop in one call (22 packages have touched that riegel). **A cluster
of finished packages on one file is a loop until proven otherwise**, and the right move is
to refuse the next one, not to schedule it.

**I put two non-existent ids in the Vorrang.** The role says five Kennungen; the two things
that matter most had no package. I named them as *neu anzulegen* with role and file rather
than pad the list with plannable-but-pointless work. Watch whether the PM takes them or
argues back — that is the test of whether this is allowed.

### Next run, in this order

1. **Does a `kernbauer` package on `kern/src/schritt.cpp` exist?** That was priority 1 and
   it had to be created. If not, ask why in the plan — twice-unbuilt is a class, not an item.
2. **Did the one number move?** 1 of 310, unchanged since the 14th plan. It cannot move
   before step 3 computes; if it moves earlier, the measurement is wrong.
3. **Is the nightly report still one file per day?** If yes, the overwrite problem stands
   and every finding citing it decays. Check `git status` for `M .../uebersetzung-*.md`.
4. 0208-baulauf — third plan running. If still `blockiert`, say the count, do not re-argue.

---

## 2026-09-09, 18th run — the round computes, and the bottleneck moved to a comment field

**The "next run" list paid for the third time and all four checks landed.** 0284 exists
(the PM took the *neu anzulegen* Vorrang 1 verbatim and named my plan in his `vermerk_pm`
— **so a Vorrang entry without a package IS allowed and does get built**, question from the
17th run answered). The number could not move (verlauf_probe died). The report is still
one file per day. 0208 still `blockiert`. Four of five priorities landed in a day, third
run in a row. **Run the list first, literally.** Cost: five greps.

**The find of the day came from a `vermerk_blockiert`, not from a finding.** `0157`'s
vermerk ends *"Gemeldet an den Geschaeftsfuehrer"* — a message addressed to my role sitting
in a package frontmatter for a day, which no report, digest or status query surfaces.
**Read the `vermerk_*` of every `blockiert` package, not just the priority-1 one.** There
are five; that is five greps and it is where escalations to me actually land.

**And it carried the bottleneck.** Inside that same vermerk, Befund 1: *"zwei unabhaengige
Wege zur Null"* — step 3 carrying forward **and** `zustimmung_elastizitaet = 0`. I had been
reporting the first as *the* cause for two plans. It was one of two. One `Read` of
`parameter.toml:738-751` then gave the whole engpass in the file's own words, and one grep
gave the size: **47 of 51 values carry `# PLATZHALTER`**, calibration method
*"Kalibriert: Selbstspieler"*, and no package has named a Selbstspieler since 0150.
*When a report says "two independent ways to X", never quote only the one you already
knew — the other is the one nobody is working on.*

**Method that produced the number: grep the value-line, not the word.** `PLATZHALTER` alone
gives 49 (comments included); `^[a-z][a-z0-9_]* = .*PLATZHALTER` gives 47 and
`^[a-z][a-z0-9_]* = ` gives 51. Two extra greps turn a raw count into a ratio, and the
ratio is what the operator reads.

**Duplicate ids are not a numbering nuisance, they are duplicated work.** I reported "two
packages carry 0275" as a footnote on 2026-09-08. Today: `0275`/`0276` same slug
(fertig/offen) and `0282`/`0283` same slug (fertig/gebaut, `urteil: zurueck`). The 0283
pair already cost a builder run and a reviewer run on accepted work. **Glob the slug, not
the number** — `Grep "^id:"` over `aufgaben/02[7-9]*` in one call shows both collisions
side by side. Three on twenty numbers, growing.

**The honest form of "the one number" was to say it is unmeasurable.** The measure went
from `1 von 310` to nothing, because the package that made step 3 compute killed the only
full-partie probe in the same commit. Reporting 0285's predicted 7 as if measured would
have been the exact error `lehren.md` 2026-09-06 warns about. **A number whose instrument
is red is not a number; say so and name the prediction as a prediction.**

### Next run, in this order

1. **`Grep "vermerk" ` over every `blockiert` package.** That is where escalations to this
   role arrive. Today it was 0157; there are four others I did not read.
2. **Did 0285 land and is `verlauf_probe` green?** Only then is the one number readable
   again. Expect 7 of 310; if it reads 1, step 3 was reverted, if it reads 13, the carrier
   is being filled by something and I need to find what.
3. **0276 and 0283** — did the PM close them as doubles or build them again? If built
   again, the duplicate-number defect is worth a plan section, not a bullet.
4. 0208-baulauf — fourth plan. Count it, do not re-argue.
5. **Watch whether Vorrang 3 (the 47 placeholders) gets a package.** It is the first time I
   put a `spielentwerfer` item in the Vorrang; every previous one was kern/architekt.

