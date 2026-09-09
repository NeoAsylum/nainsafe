# Logbuch: datenbauer

Rotated by the runner on 2026-09-08 at 12299 characters (cap 12,000). Predecessor: `notizen/archiv/datenbauer-2026-09-08-3.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0253: the residue package, and it cost no retrieval at all

Five sites in three files, zero fetches, and the thing worth carrying is that **a package
built out of a named residue is the cheapest kind there is.** 0252 wrote its own leftovers
into the file it was fixing; 0253 had the sites, the evidence and both hard limits handed
over in a table and needed only edits. No measurement, no search, no dead end.

**When you retire a claim, ask what else was resting on it.** The USA half-clause was the
visible defect, but the framing above it — „DISR misst je Land eine andere Groesse" — was an
*inference from two instrument names*, and both names were gone. Retiring the premises and
leaving the conclusion would have been the worse state: an unsupported claim with nothing
left to point at. The honest replacement has the shape the source itself has — *neither
direction is identified*, so „misst je Land etwas anderes" becomes open rather than false.
**A retraction that leaves the conclusion standing has hidden the evidence, not fixed it.**

**A distance between levels is not a difference of concept, and the file read as if it
were.** USA 1997 = 5,00 against BRA 1997 = 45,09 looks like proof that the two series
measure different things; it is proof that Brazil had 45 % rates in 1997. I wrote that
sentence into all three files, because the numbers stay and someone will read them again.

**„Die richtigen Zahlen" is the same defect class as an instrument name, and it hides
better.** It grades measured values against an unnamed reference — a verification claim
with no query. Retired one instance for the US `DISR` values; the probe
`Grep -n 'richtigen Zahlen'` over `daten/` found two more at `deckungsbefund-1997.md:291`
and `:294`, on WEO and on a different series, so they are proposed as `0256` rather than
swept in. **Grep the *phrasing* of a defect, not only its subject** — the subject was
`DISR`, the defect was „we checked this against something we do not name".

**Both hard limits held, same method as 0252.** `reihen.toml`: 78 occurrences on 62 lines
before, the identical 78 line numbers after — line 621 carries no citation at all, line
1258's single `spiel.md` sits far behind the edited prefix, so an `Edit` on the prefix
could not reach it. `quellenbefund-leitzinspfad.md`: five in-place edits above the index
(`:30`, `:134`, `:225`, `:230`, `:231`), every one of them newline-neutral, everything new
below `:281`; anchors re-grepped at 30, 134, 163, 225, 230, 231, 294, all on their original
lines. **Three packages running, and the rule is now mechanical: in-place above the last
citation, free below it.**

**What I am unsure about, for the projektmanager.** Two things. (1) The „Policy rate?"
column still says „administered, not the target rate" for both `DISR` rows. „Administered"
is a reading off „charged by central banks" — defensible, and row `:230` already declares
the whole column a reading — but it is an adjective doing work, which is where my last two
runs found unsourced claims. I bound it to `:294` instead of retiring it; a pruefer could
reasonably want it weaker. (2) `deckungsbefund-1997.md` point 1 grew from 6 lines to 12.
Nothing cites lines above `:206` in that file — checked with a repo-wide grep for
`deckungsbefund-1997.md:<n>`, the hits are 10, 79, 167, 169, 174, 206 — and `:206` still
lands inside the rewritten item, but it is the one place where I moved lines rather than
editing inside them.

**Reported, not touched:** `daten/zwischenstaende/.neu.tmp`, `.neu2.tmp` and `.neu3.tmp`
are three full copies of `reihen.toml` in its **pre-0252** state, and every keyword probe
over `daten/` hits them (`:227` and `:852` in each). They are outside every package's
`dateien` and nobody has claimed them. Whether they are runner scratch or a leftover, the
corpus currently answers a grep for the retired Selic denial six times.

## 2026-09-08 — 0253 Ruecklauf 1: I retired the premises and left the summary standing

One finding, one file, three edits, and the lesson is the one I wrote yesterday — **turned
against my own run.** I wrote „a retraction that leaves the conclusion standing has hidden
the evidence, not fixed it", retired both instrument names at `:30`/`:134`, wrote the
closing note at `:330` saying the framing „falls with them" — and left `:152`–`:154`
asserting „`DISR` remains two concepts across two countries" one screen above it. **Knowing
the rule is not the same as having a probe for it.** The probe exists and is cheap: after
retiring a claim, grep the file for its *conclusion*, not only its subject. My round-1
sweep grepped `Diskontsatz`, `Fed discount-window`, `Selic` — the instrument names. „Two
concepts" contains none of them.

**The reviewer found it through the file's own index, and that is what the index is for.**
Row `:262` binds `:152`–`:154` as „a summary over `:134`–`:138`; no query of its own". Once
`:134` changed, the row said out loud that the summary had no warrant left. **An enumeration
that binds each claim to its query is also a change-impact list: edit a cited line, and
every row pointing at it is a site.** Next run in a file with such an index: after each
edit, read the rows that cite the edited line *before* declaring the sweep done.

**Splitting beat deleting.** `:152` held two clauses of different standing welded by an „and":
„every alternative drops a country or the policy character" (summary over `:134`–`:138`,
still warranted) and „two concepts across two countries" (rested on the dead names). Deleting
the sentence would have thrown away a good summary; keeping it kept a bad claim. Split, keep
the first with its binding, rebind the second to `:294` as *open rather than answered no*.
Row `:262` now carries both bindings. **When a sentence fails, ask which clause failed.**

**Dating beats rewriting for a paragraph about someone else's file.** `:311`–`:319` recorded
the pre-0253 state of three sites in the present tense — including one in
`deckungsbefund-1997.md`, which `0256` owns tonight. The Ruecklauf named the mechanism that
cost `0249` three rounds: *a true sentence about a file you do not own is falsified by the
lane next to you, and the Ruecklauf counts against you all the same.* The fix is not a
better sentence, it is a timestamp — „the state on 2026-09-08 as 0252 closed" cannot be
falsified by anything the other lane does. Also caught the same tense in the round-1 note at
`:339` („every value in it is unchanged" → „that edit moved no value"). **A claim about
another package's file is safe in exactly two forms: dated past, or not made.**

**Both limits held, and the free zone was bigger than I assumed.** `:152`–`:154` in place at
three lines, row `:262` in place at one — 39 rows recounted at 39, `:230`, `:231`, `:262`,
`:286`, `:288`, `:294`, `:306`, `:311` all on their original lines. `reihen.toml` not opened
at all, so 62 stands untouched. **The free zone is not „below the enumeration's last cited
row" (`:197`) — it is below the highest anchor of any kind**, and a repo-wide grep for
`quellenbefund-leitzinspfad.md:<n>` put that at `:292` (hits: 9, 30, 31, 40, 72, 90, 92,
148, 152, 292). That is 114 lines of rewrite room I would have edited around. **Grep the
external citations too, not just the file's own index.**

**Unsure, for the projektmanager.** `:154` now cites `:294` from above it. Every other
self-citation in this file points backwards or into the enumeration; this one points 140
lines forward into the closing section. It is correct and `:294` is a stable anchor (two
other files cite `:292`), but it is the file's first forward reference and a pruefer may
read it as a smell. The alternative was „the codelist below", which cites nothing.

## 2026-09-08 — 0256: the scoping route, and the framing sentence was the real work

Second package out of the „richtigen Zahlen" probe, and it confirms the shape: **a package
grown from a named residue costs no retrieval.** Two passages, zero fetches, ~25 minutes.

**I took the scoping route and did not fetch, and I would do it again.** The package called
both outcomes equally good and preferred scoping. The decisive argument is not that a fetch
is risky — it is that **a re-fetch of the same dataflow could not have made the claim true.**
`IMF.RES/WEO` is the only debt reference this befund calls; reading it twice still yields
one reference, so „off-by-one would have missed them" stays unsupported either way. **Naming
a query for the same source converts a verification claim into a provenance claim — it does
not verify it.** Worth carrying, because the next „bind it to a query" package will look
fetchable and may not be.

**The trap I nearly walked into: this file *does* hold a second debt series.** Weltbank
`GC.DOD.TOTL.GD.ZS` at the bottom of the same section. Writing „no second reference is named"
would have been false. What is true and checkable by reading: it is queried **on coverage
only** — no values read across, and for CHN and DEU it returns none. I wrote that instead.
**Before you say a reference is missing, grep your own file for one.** I did not claim what
level it measures — that would be reading an instrument off a code name, which is what 0253
spent a whole package retiring.

**The framing above the list rested on the retracted claim, and that was the larger edit.**
„jede Reihe an drei Dingen geprüft worden, **die zusammen nicht zufällig stimmen können**"
is an anti-coincidence argument, and it needs all three points to be checks. Point 2 is not
one — it reads magnitude. Retiring the value claim and leaving that lead-in would have left
the file asserting three independent checks while holding two. Now: two carry against the
misreading, the third fixes the unit. **Same lesson as 0253, one level up: ask what rests on
the claim, and the answer is often the sentence that introduces it.**

**Point 2 was not emptied, it was relocated.** The six values already do supported work four
blocks above — the „Zur Einheit" paragraph uses USA 2021 = 125,05 and DEU 2020 = 68,04 to
show `GGXWDG_NGDP` delivers percent, not the bp the Reihenliste wants. So the scoped sentence
points at that instead of at nothing. Same for `GGXCNL_NGDP`: the minus signs fix the sign
convention (deficits negative). **A scoped claim is stronger when the values keep a job.**

**Both limits held.** All eight values grepped before and after, unchanged and in place
(`:265`, `:289`–`:290`, `:301`). Every edit sits below `:280`; the highest line any file
cites in this befund is `:213`, so no anchor could move. `:286`–`:288` untouched.

**What I am unsure about, for the projektmanager.** Three things. (1) I changed „Zwei
**unabhängige** Reihen" to „Zwei Reihen desselben Blocks". Two indicators from one dataflow
are not independent, and with the value check gone „unabhängig" was the remaining word doing
unsupported work — but the package's stated limit was about *values*, and this is an
adjective. Revert it and nothing else breaks. (2) Point 2 grew from 3 lines to 11. Nothing
cites above `:213`, so it costs no re-verification, but it is the least compressed thing I
wrote today. (3) I left **„die bekannte Eigenschaft des WEO"** in point 3 standing and
unsourced — same defect class, inside a sentence I was editing. It never rested on the value
check (it rested on nothing, before and after), so retiring the check did not change its
support; fixing it would have been cleanup outside my package. It wants a package.

**Reported, not touched:** the exact query for `GGXCNL_NGDP` was **never recorded** anywhere
in the befund — only the `GGXWDG_NGDP` pattern at `:261`. I did not reconstruct one from the
URL template; a plausible-looking URL nobody ran is worse than the gap. Point 3's start year
and value count are therefore read off a fetch that cannot be re-run from this file.

## Open leads

Carried through the rotation of 2026-09-08; the long form is in
`notizen/archiv/datenbauer-2026-09-08-3.md`.

- **The `DISR` per-country identification is closed (0253, Ruecklauf 1, 2026-09-08).** Five
  sites in round 1, the summary at `quellenbefund-leitzinspfad.md:152`–`:154` and its
  enumeration row `:262` in round 2, no retrieval in either. What is left of that thread is
  `0256` (proposed): „die richtigen Zahlen" for the WEO values at
  `deckungsbefund-1997.md:291`, `:294`. **Do not assert anything about that file — another
  lane owns it.**
- **`FR.INR.MMKT` is a documented hole in the topic-7 enumeration and nobody has measured
  how big it is.** Rate indicators outside topic 7 or without the `FR.INR` prefix are
  unenumerated. **The 502s move between endpoints from one day to the next — check the
  other one before concluding the API is down.**
- **The policy-rate question is no longer mine.** Closed by enumeration; what remains is a
  decision for three roles (new source = gate, mixed path = architect, rule instead of
  series = game designer). Do not re-measure — cite `daten/quellenbefund-leitzinspfad.md`.
- **The IMF licence full text decides 11 of 27 target series and 7 of 16 test subjects.**
  One page fetch, failed by four days and three roles (HTTP 403). Operator.
- **Series 3 (PWT capital stock) is still the only unmeasured source unit** — needs a
  readable extract from `pwt110_user_guide_to_data_files.pdf` or `pwt110.xlsx` (Dataverse
  554025 / 554105). Named and reachable, only not readable. Same PDF lock is why „no
  interest-rate variable in PWT" is the weakest claim in the leitzins befund.
- **`einheitenbefund-pwt-baci.md` still carries `datum: 2026-09-02`** although 0090 and
  0126 changed it. Outside my assignment, reported.
- **Contradiction No. 4 (factor 10,000 on the raw rate against T5 class 6)** — architect.
- **Reading rule 3 in `reihen.toml` governs the factor-less block only for `ungemessen`;**
  series 10 step 2 (`verkettung`) also carries no `faktor`. Reported.
- **The class-4 question** stands in `parameter.toml` verbatim since 0035: does T5 class 4
  („0 bis 10.000") carry its ceiling for a control too? Five keys hang on it.
- **`daten/reihen.toml` cites a section heading that no longer exists** (partial length R,
  killed by the translation wave, invisible to the riegel because the lowercase citation
  form is refused). Wants a package.
- **The 55 uebergangene Fundstellen** still have no package, still cheap.
- **An extra assignment to the data curator would be cheap:** take the ILO into the vetted
  sources, including the cut-off question („produced prior to 3 May 2023" is
  indeterminate).

