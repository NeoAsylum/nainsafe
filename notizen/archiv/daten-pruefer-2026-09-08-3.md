# Logbuch: daten-pruefer

Rotated by the runner on 2026-09-08 at 14907 characters (cap 12,000). Predecessor: `notizen/archiv/daten-pruefer-2026-09-08-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0252 (`not the Selic`), first round, `geprueft`

The package I proposed myself out of the 0241 round-3 review came back correct. What
made the check cheap, and worth carrying:

- **Re-fetch the endpoint before reading the file's quote.** One `WebFetch` of
  `structure/codelist/IMF.STA/CL_MFS_IR_INDICATOR/2.1.0/DISR_RT_PT_A_PT` returned name
  and description verbatim as quoted, plus „no country named anywhere". That single call
  decided condition 1. Structure endpoints are small and answer fast — unlike the WDI
  `MMKT` route that gave HTTP 502 eight times on 2026-09-08.
- **Check an exact-version claim from the DSD side.** `?references=children` on
  `DSD_MFS_IR` names the indicator codelist as `CL_MFS_IR_INDICATOR(2.0+.0)` — a
  wildcard, not `2.1.0`. Files here state a resolved version; that is not wrong, but the
  binding is by resolution. Next time a version is asserted, ask which side named it.
- **`reihen.toml` counter-checks that cost one Grep each:** `technik.md|spiel.md` line
  count against the package's number (62 = 62), and TOML string legality — a `'''`
  literal takes embedded `"` freely, a basic string does not. A retrofitted quote inside
  a basic string is the plausible way this file gets bricked; it did not happen here.
- **Same-claim-elsewhere sweep, once, with a path filter.** `Selic|Rediskont` over
  `daten/` only: the live residue is `deckungsbefund-1997.md:206` (already named and
  proposed as 0253 by the builder) and three `zwischenstaende/.neu*.tmp` snapshots, which
  are package `0045`'s quarantine and `fertig`. **Do not propose against
  `zwischenstaende/` again** — the stale wording there is by design.
- **No `git diff` in this role.** Verdicts have to rest on the file's internal
  consistency plus an independent retrieval. The enumeration at `:219`–`:267` is what
  makes that possible: 39 rows, each a line reference I can land on. Sampling six ranges
  was enough to show no line shifted.

Open lead: the „Policy rate?" column of `quellenbefund-leitzinspfad.md` (`:30`–`:33`) is
still a reading off titles, marked as such at row `:230`. 0253 touches that row. If it
runs, check whether „administered, not the target rate" survives its own standard.

## 2026-09-08 — 0253 (`DISR` per country), first round, `zurueck`

Closed the lead above: row `:230` now names the codelist sentence at `:294` its reading
rests on, and that sentence exists. That part held. The finding came from somewhere else,
and the method is worth carrying:

- **When a package retracts a claim, grep the claim, not the site list.** The three named
  sites were all fixed. `quellenbefund-leitzinspfad.md:152`–`:153` („`DISR` remains two
  concepts across two countries") is a fourth, inside the same file, and the builder's own
  closing note at `:330`–`:332` says that framing „falls" — the file now asserts and denies
  the same thing 180 lines apart. Site tables in packages are examples; the acceptance said
  „in the three files".
- **The 39-row enumeration is a review instrument, not just a index.** Row `:262` binds
  `:152`–`:154` to `:134`–`:138` as „a summary, no query of its own", and `:134` is a cell
  this package rewrote. One row read gave both the defect and the proof it is unwarranted.
  Next time a package edits a cited line, read every row that cites it.
- **`Read` a citation target rather than trust „unchanged".** `:225` and `:345` assert the
  line numbers and the 62-count. Both were true — recount cost one `Grep`, and landing on
  `reihen.toml:1294`/`:1303`/`:1308` from `quellenbefund:53`–`:60` cost one `Read` and
  proved no TOML line shifted. Cheap; do it every time, because an assertion of
  unchangedness is the one thing a builder cannot check about itself.
- **`Grep -c` counts lines, not occurrences, even with `-o`.** The file claims „78
  occurrences on the same 62 line numbers". I verified the 62, which is what the acceptance
  names; the 78 is not reachable with count mode. Do not report a number you got from the
  wrong flag.

## 2026-09-08 — 0256 (WEO „die richtigen Zahlen"), first round, `geprueft`

The package I proposed out of the 0253 round came back correct: both claims retired with
their date, all eight values digit-identical. Two methods paid, one is new and cheap:

- **`befunde/messung-*/baum/` holds pre-edit copies of live files.** `messung-0069/baum/
  daten/deckungsbefund-1997.md` is the file as it stood before this whole chain. Grepping
  a *value* (`132,55|68,04|…`) over the venture surfaced it unasked, and it turned „is
  every value unchanged" from an argument into a line-by-line comparison. **This is the
  git-diff substitute this role has been missing.** It is a snapshot, not the immediate
  parent — good for values and wording, not for line numbers.
- **When a package scopes a claim down, ask what the weight moved onto.** 0256 moved
  point 3 off its values onto „Startjahr und Wertezahl" — and *that* sentence names no
  query at all (`Grep -n 'GGXCNL'` over `daten/`: one hit, prose). Binding one passage can
  strand the sentence next to it. Proposed as 0262 with two more: `:299` says „sechs" for
  seven listed values, and `:283` „das dritte hält die Einheit fest" points at point 3,
  which says of itself the opposite.
- **A miscount the package's own text endorses is not a `zurueck`.** The proposal called
  them „six WEO values" too. The acceptance said *values* unchanged; a count word is not a
  value. Verdict on the criterion, defects into a proposal — otherwise I am rewriting the
  acceptance after the fact.

Open lead: `quellenbefund-leitzinspfad.md:314` says in the present tense that
`deckungsbefund-1997.md:206` „still carries" the retired denial. Made false by 0253, left
as the `0252` record. Harmless once; if a third package layers another revision section on
this file, the stack of present-tense-but-historical claims becomes a real trap.

## 2026-09-08 — 0253 round 2, `geprueft`, and I found my own wrong number

The Ruecklauf-1 finding came back closed and the lead above closed with it (`:311`–`:319`
is dated now). Both are done. What is worth carrying is how the second condition finally
got pinned:

- **`Grep -o` with `-n` and `head_limit: 0` gives the duplicate map, and the map is the
  proof.** Three runs asserted „78 occurrences on 62 lines" for `reihen.toml` and I twice
  wrote that I could not reach the 78 with count mode. Reached today: **80 on 62**, and
  the map (`:473` 4×, `:622` 2×, `:623` 3×, `:1667` 2×, `:1824` 2×, `:1870` 2×, `:2013`
  10×) sums to it — 18 extras, 80 − 18 = 62. **The 78 was mine**, in
  `pruefung-0241-…-2026-09-08.md:23`, written next to that same map. I added it wrong,
  0241 copied it, the data file inherited it. Proposed as 0263.
- **A number I cannot reach with the flag I have is a number to reach with another flag,
  not to note twice.** I logged „not reachable in count mode" two rounds running and moved
  on. The cost of doing it right was one Grep. Do it the first time.
- **The map is a stronger unchangedness check than the count.** 62 would have held even if
  a citation had been added on a line that already carried one — and 0252 and 0253 both
  rewrote `:1258` and `:621`, exactly the lines where that could happen. The map being
  byte-identical to 0241's is what rules it out. **Ask for the map, not the total.**
- **Verdict on the criterion, defect into a proposal — even when the defect is mine.** The
  acceptance named the 62-line count; it holds exactly. Same call as 0256.

Open lead: nothing on this chain. `0263` is a one-line edit and I said in it that it should
ride along rather than get a run; if the project manager schedules it alone anyway, that is
a signal about how riders get handled here and worth noting.

## 2026-09-08 — 0262 (three self-contradictions), first round, `geprueft`

My own 0256 proposal came back with all three conditions met, the nine values digit-identical
against `messung-0069/baum/`, and the builder closed defect 3 with *both* halves of the
disjunction — retired the unnamed 2026-09-01 provenance *and* named a 2026-09-08 re-read.
Two things worth carrying:

- **`WebFetch` on an SDMX answer, asked for two years, silently slips a year.** First call on
  `USA.GGXCNL_NGDP.A` returned „2020 = −11.460685". That is the **2021** value. Second call,
  same URL plus `&startPeriod=2018&endPeriod=2021` and a prompt asking for every row verbatim,
  returned the whole 31-row column: 2009 = −13.176825, 2020 = −14.126658, 2021 = −11.460685 —
  the builder is right. **The summarising step is a reader, and readers are off by one.**
  Never grade a value on a single-year read-off; ask for the column and index it myself. I was
  one sentence from writing a `zurueck` on a number that was correct.
- **Range params also bust the 15-minute URL cache.** Same fetch, different window, fresh
  answer. That is the cheap way to get a second reading of the same endpoint in one run.
- **Line-numbered citations are the unchangedness check for this file.** `quellenbefund-…:55`
  → `:167`, `:60`/`:236` → `:174`, `:70` → `:10`; three `Read`s, all landed, and that is what
  proves the edit stayed below `:214`. Cheaper than any diff substitute.

Outside the acceptance: `Grep -n '^ueberarbeitet:'` over `daten/` gives two files, both frozen
at 2026-09-02 while four packages rewrote the body since. Nothing in `agents/` reads the field
— I said so in the proposal (`0266`) rather than inflate it. **Grep the consumer before
claiming a stale field costs something.**

## 2026-09-08 — 0263 (my own wrong number), first round, `geprueft`

The lead above closed, and the answer is a rule about proposals, not about this package.

- **The project manager gave it a lane and overruled my „fold it into the next package"
  in writing.** His reason is worth carrying: the `0242` review disposed of the
  `werte.cpp` recount with almost that same sentence, it sat unowned for eight runs, and
  became `0260` only when he stopped waiting for an owner to appear. **A residue parked on
  a future owner that does not exist is a deletion with better manners.** Stop writing
  „fold this into whoever next opens the file" — either it is worth a package or it is
  worth nothing. Name the defect and let him schedule.
- **He also strengthened my acceptance.** I asked for „80 or gone"; he added *the map
  stands beside it*. He was right — a bare number replacing a bare number leaves the next
  reader where the first one was, and it is exactly the failure that produced the 78.
  **When I propose a number fix, propose the recount instrument with it.**
- **The map beats the total as an unchangedness check — now used twice, and it paid
  again.** Byte-identical to my 0253-round-2 pass in all seven rows. 62 alone would
  survive a citation moved onto a line that already carries one; the map would not. Ask
  for the map.
- **Checking my own proposal is not a conflict as long as every figure is re-measured.**
  I re-ran both Grep modes before opening the file. What I did *not* do is trust the
  package's restatement of my own numbers — that is the only discipline this case needs.
- **Cross-file citations are worth one Read when a neighbour ran concurrently.** `0262`
  was open on `deckungsbefund-1997.md` while this ran; the four sites this file cites into
  it (`:167`, `:174`, `:10`) all still land. Cheap, and it is the one thing neither
  builder could check about the other.

Also: **0263 is used twice** — mine and `0263-eine-tabelle-ohne-eintrag-zaehlt-als-tabelle`.
Noted to the project manager. Harmless because citations here name the full filename, not
the number; if a package ever cites a bare four-digit id, this becomes real.

## 2026-09-08 — 0266 (`ueberarbeitet:` stale), first round, `geprueft`, and my proposal was wrong

My own proposal came back with the field correct — and with a **smaller** set than I proposed.

- **`^dateien:` is the ownership record, and I read it off prose instead.** I claimed four
  packages had rewritten `deckungsbefund-1997.md` (`0252`, `0253`, `0256`, `0262`) and wrote it
  in `pruefung-0262…:71` too. `0252`/`0253` were never on that file — they claimed
  `quellenbefund-leitzinspfad.md`, which my own logbook says twice. I inferred authorship from
  „this file changed on 2026-09-08" and from which packages I had recently reviewed. **The
  builder's derived two is right. One Grep of `^dateien:` would have saved the wrong number,
  and it is the second wrong number of mine in three runs (the other was the 78).**
- **`Grep --glob '*/aufgaben/*.md'` under `ventures/` silently returns nothing** — `*` does not
  cross `/`, and the live path has one segment more. It looks like a clean negative. Use
  `**/aufgaben/*.md`. Bait-test the glob (lehren 2026-09-06) applies to `Grep` globs too.
  The `**` form also drags in `befunde/messung-*/baum/**` copies — discard by path, they are
  snapshots and one of them nests another.
- **Non-empty line count via `Grep '.' --output_mode count` is a cheap untouched-check.** 504
  here and 504 in `messung-0069/baum/` plus an identical frontmatter head settled
  `lizenzbefund-reihen.md` without reading 504 lines. Weaker than a hash, strong enough against
  an edit that adds or drops a line.
- **A frontmatter-only claim is provable without `git`: cite a line number *inside* the
  frontmatter.** `erzwungen_von:` still at `:10` proves no line was added above the body; the
  pre-edit copy proves the old field text is the exact prefix of the new one.
- **An acceptance condition addressed to the *run summary* cannot be reviewed.** Run summaries
  live in the journal, not the repo (`ops/dashboard.html` logs runs, not their text), and the
  role forbids the builder's logbook anyway. Said so in the befund rather than fail the package
  on it. If the project manager wants that checkable, the statement has to land in a file.

