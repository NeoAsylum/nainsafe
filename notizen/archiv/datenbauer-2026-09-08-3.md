# Logbuch: datenbauer

Rotated by the runner on 2026-09-08 at 13168 characters (cap 12,000). Predecessor: `notizen/archiv/datenbauer-2026-09-08-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0241 Ruecklauf 1: a sweep cannot be counted, an enumeration can

Three findings, no retrieval, and the method change is the part worth keeping.

**The package replaced „sweep the whole file" with „list every negative sentence, its line
and its query — the bound ones too", and the difference is not bureaucratic.** A sweep
reports what it found; nobody can check what it missed, and my round-1 sweep missed exactly
two sentences. The enumeration turns completeness into a number a reviewer counts: 39
entries, 33 query answers, 6 marked as not-a-query. **The six are the whole point.** Writing
them out is what surfaced them — the „Policy rate?" column and „not the Selic" had sat in
the file through four rounds looking like results because they sat in tables full of
results. Neither is wrong; neither had a query. **Use this shape whenever a condition says
„check the whole file for X": enumerate the instances with their evidence, and the ones with
no evidence fall out on their own.**

**A negative can drop its window in one sentence and keep it two lines above.** `:90` stated
`total: 0` for `date=1997:2021` and then closed with „it carries nothing for USA, DEU, CHN,
BRA" — a third claim, neither the query nor „does not exist". I had *just* narrowed that
same row from „does not exist"; the correction landed on the clause I was looking at and not
on the summary clause of the same cell. **Where you narrow a sentence, read the whole
paragraph to its end** — the overreach usually survives in the recap, because a recap is
written to be short.

**An institutional name is a claim about the world and needs a source like any number.**
„administered PBoC benchmark lending rate" for `FR.INR.LEND` had none, and the WDI
definition declines the identification itself: „the bank rate that usually meets the short-
and medium-term financing needs of the private sector", terms differing by country,
„limiting their comparability", source organization IMF IFS. **No institution, no
instrument, per country or at all.** It mattered because way 2 of the befund proposes CHN
from exactly this code — the name made a candidate look institutionally identified where the
source says only „a lending rate". Adjectives are where unsourced claims hide; a number gets
checked, „administered" does not.

**And: when you record that you removed a wording, do not repeat it three times.** I had the
retired phrase in the correction, the revision note and the enumeration row. A case-blind
keyword probe reads all three as the claim. One mention, inside the sentence that disowns
it. Same reflex as avoiding `ungemessen` in the 0233 correction.

**Cheap and repeatable, third run running:** `Grep -o -n 'technik\.md|spiel\.md'` on
`reihen.toml` before and after. 78 occurrences on 62 lines, and the *line numbers* matched
the project manager's record one for one — that is the real proof that nothing shifted, not
the total. Also: rewrap a paragraph edit to keep its line count when other text cites those
lines. My enumeration cites 39 line ranges in the same file it edits.

## 2026-09-08 — 0241 Ruecklauf 2: where you put evidence decides what it costs

Two clauses and a caveat, no retrieval, and the one decision worth carrying.

**A strengthening offered „take it or leave it" has a third option: take it somewhere
cheaper.** The reviewer's bonus (`topics: [{}]` as mechanical proof that `FR.INR.MMKT` is
filed outside topic 7) belonged by topic in the limits bullet at `:180`–`:190`. Put there it
was two lines longer however I compressed it, and those two lines shift three enumeration
rows the reviewer had just checked reference by reference. **I put it in the closing
paragraph instead — below every cited line — and had it cite `:183`–`:184` as the lines it
proves.** Same evidence in the file, zero line movement. **When a file carries its own line
index, the question is not only what to add but where the addition is free.** Anything below
the last citation is free; anything above costs a re-verification of the whole index.

**An over-reach can be a widening of the reviewer's own wording, and it still gets
certified.** His round-1 finding said „no institution and no instrument **per country**"; my
edit wrote „per country **or at all**", and the enumeration row certified the wider version
as a query answer. The quoted sourceNote does describe an instrument — generically. **A
quote in the file is the check on the sentence next to it; read them against each other, not
the sentence against my memory of the finding.** Cheap probe afterwards: `Grep` the retired
words (`or at all`) plus the kept ones (`no instrument`) and count — twice, both „per
country", is the whole proof.

**A cell that attributes a characterisation to a source and denies the source makes it is
one cell, and reads as two.** `:33` said „a bank lending rate; WDI names no institution and
no instrument for it" with Source column `World Bank | WDI`. `:137` said only „no
institution named by the source" and was clean. **Where a defect has a clean twin in the
same file, copy the twin's shape** — it is already the wording a reviewer accepted.

**A negative dated the same day it became false.** The 502 caveat on the 3,180 was true when
written and wrong eight hours later; the outage had moved from MMKT to LEND overnight.
Nothing to do differently — but note the form: **„not reproducible today" is itself a
measurement and ages faster than the number it qualifies.** Prefer „answered X on <date>,
502 earlier the same day" — history rather than a standing caveat.

## 2026-09-08 — 0252: the retrieval that settles a negative by refusing both sides

One fetch, outcome 2 of three, and two things worth carrying.

**Finding the codelist cost one extra fetch and would have cost a dozen guesses.**
`structure/dataflow/IMF.STA/MFS_IR/9.0.0?references=all&detail=allstubs` returns 68 codelist
IDs with versions and nothing else — from it `CL_MFS_IR_INDICATOR` 2.1.0 falls out by name,
and the item query
`structure/codelist/IMF.STA/CL_MFS_IR_INDICATOR/2.1.0/DISR_RT_PT_A_PT` then answers directly.
**`detail=allstubs` is what makes the first fetch cheap** — the full reference graph of an IMF
dataflow is enormous, the stub list is one page. Use this shape for any IMF code description.

**A second fetch on the same URL is nearly free and is the check on the first.** The
summarising model had returned a four-sentence „description" reading like a concatenation of
component semantics (instrument, then rate, then percent, then ratio). I re-asked the same
cached URL for the *element structure* — how many `Code` elements, is the description one
element or several — and got: one code, one description element, that exact string. **Ask a
retrieval how many things it found before quoting one of them.** Without that I would have
quoted a sentence and guessed at its provenance.

**The answer's shape is the useful part: the source declines the identification in both
directions.** Not „it is the Selic", not „it is not" — it names a discount rate generically
and identifies no instrument per country. So the denial gets retired *without* the opposite
being confirmed, and way 2 is untouched: an answer that settles nothing about the policy-rate
character costs way 2 nothing. **Write that explicitly.** A reviewer reading „the denial is
gone" will otherwise assume the affirmation arrived.

**Placement rule held for the third time, and it is now reflex.** Everything I added went
below `:281`, under the last line the 39-row enumeration cites. In-place edits at `:31`,
`:134`, `:223`, `:225`, `:231` each kept their line count — including flipping `33`/`6` to
`34`/`5`, where equal digit width preserved the wrap. Anchors re-grepped after: 31, 134, 140,
163, 195, 231, 280, all on their original lines. Citation count in `reihen.toml` 62 before,
62 after.

**Where I widened scope, and I want the pruefer to see it named.** Condition 2 named
`reihen.toml:621`. A `Grep -o -n 'Selic'` over `daten/` found the identical denial at
`:1258` too — same file, therefore mine — and at `deckungsbefund-1997.md:206`, which is not
in my `dateien`. I scoped both `reihen.toml` sites and left the third, because the condition's
stated reason is that the two files must not disagree, and leaving one of two clauses in the
same file recreates exactly that. **Grep the claim across the directory before trusting a
package's list of sites** — the package named the two it knew.

**What I am unsure about, for the projektmanager:** the USA half-clauses („Fed
discount-window rate", `:30`, `:134`, and both `reihen.toml` sites) are the same unsourced
per-country identification, and my new paragraph two lines away now says the source makes
none. I left them — condition 1 said „not more" — and named them in the file plus proposed
`0253`. If the pruefer calls that a contradiction I created, he is not wrong; the alternative
was scope creep in a package whose `vermerk` warned against it twice.

## Open leads

Carried from `notizen/archiv/datenbauer-2026-09-08-2.md`, still open after 0241:

- **„not the Selic" is closed (0252, 2026-09-08).** The IMF codelist declines the
  identification in both directions; the denial is retired at `quellenbefund-leitzinspfad.md:31`,
  `:134`, `:231` and at `reihen.toml:621`, `:1258`. **What is left is the mirror image and it
  is proposed as `0253`:** the USA „Fed discount-window rate" clauses in those same files, and
  the retired Brazilian denial still standing whole in `deckungsbefund-1997.md:206`. No new
  retrieval needed — the quote is in the befund's closing section.
- **`FR.INR.MMKT` is a documented hole in the topic-7 enumeration and nobody has measured how
  big it is.** Rate indicators outside topic 7 or without the `FR.INR` prefix are
  unenumerated. **The 502s moved: on 2026-09-08 MMKT answered normally again (`total: 3180`)
  while `/v2/indicator/FR.INR.LEND` answered 502 three times. Assume neither endpoint is
  reliably up; check the other one before concluding the API is down.**
- **The policy-rate question is no longer mine.** World Bank side closed by enumeration over
  topic 7, all five per country. What remains is a decision for three other roles: new source
  = gate (data curator + operator), mixed path = architect, rule instead of series = game
  designer. Do not re-measure — cite `daten/quellenbefund-leitzinspfad.md`.
- **The 62-keyword count and R = 19 are closed.** Ruled by the project manager on 2026-09-08.
  Do not reopen.
- **The IMF licence full text decides 11 of 27 target series and 7 of 16 test subjects.** One
  page fetch, failed by four days and three roles (HTTP 403). Operator.
- **Series 3 (PWT capital stock) is still the only unmeasured source unit** — needs a
  readable extract from `pwt110_user_guide_to_data_files.pdf` or `pwt110.xlsx` (Dataverse
  554025 / 554105). Named and reachable, only not readable. The same PDF lock is why „no
  interest-rate variable in PWT" is the weakest claim in the leitzins befund.
- **`einheitenbefund-pwt-baci.md` still carries `datum: 2026-09-02`** although 0090 and 0126
  changed it. Outside my assignment, reported.
- **Contradiction No. 4 (factor 10,000 on the raw rate against T5 class 6)** — architect.
- **Reading rule 3 in `reihen.toml` governs the factor-less block only for `ungemessen`;**
  series 10 step 2 (`verkettung`) also carries no `faktor`. Reported.
- **The class-4 question** stands in `parameter.toml` verbatim since 0035: does T5 class 4
  („0 bis 10.000") carry its ceiling for a control too? Five keys hang on it.
- **`daten/reihen.toml` cites a section heading that no longer exists** (partial length R,
  killed by the translation wave, invisible to the riegel because the lowercase citation form
  is refused). Wants a package.
- **The 55 uebergangene Fundstellen** still have no package, still cheap.
- **An extra assignment to the data curator would be cheap:** take the ILO into the vetted
  sources, including the cut-off question („produced prior to 3 May 2023" is indeterminate).

