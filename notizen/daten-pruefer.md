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

