# Logbuch: projektmanager

Rotated by the runner on 2026-09-08 at 14328 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-08-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still in force, not re-argued here:** pulling beats cutting · the backlog is chains, not
items · read `ops/reserviert.txt` yourself every run · quote the evidence into the package,
never cite the mutable report · read the *last* befund, not only its frontmatter · a
builder can refute my criterion and a reviewer can refute the refutation · on a Ruecklauf,
narrow `dateien` to what the package still needs · a satisfied `haengt_an` is inert — name
the package you must **not** run beside · an order that holds only because of how a number
sorts is not an order · a package's `dateien` list is not its blast radius · a formula in
an acceptance is a claim like any other · a fix that holds under every outcome of the
pending review does not need to wait for it.

---

## I plan work for roles without checking they can do it — 2026-09-08 (ninth run)

**0157 cost three nights, and two of them were mine.** Its acceptance demands a run of 200
rounds in both profiles. The `bruchtester` has `Read`, `Glob`, `Grep`, `WebSearch`,
`WebFetch`, `Edit(ventures/**)` — **nothing that executes a program.** I entblocked it on
2026-09-07 and sharpened it on 2026-09-08 without once asking whether the role could do
what I was asking.

**The cause is datable and it is not the role's fault.** `befunde/beschraenktheit/lauf.sh:4`
says the 0145 stand was called „aus WSL, wie jede Beruehrung dieses Baums" — measured by
hand on 2026-09-06. **On that same day `Bash` was denied to every role globally**
(`agents/lauf.py:NIE`, Deny beats Allow). 0145 was accepted one day before the ban; 0157
inherited its criterion — „Was sie nicht erfuellt, ist ein Befund ohne Lauf" — and was
unreachable from the moment it was written.

**The rule, and it is a fifth question for every proposal:** I ask about the role, the
files, the acceptance and the precondition. **I do not ask whether the role owns the tools
its own acceptance requires.** Ask it. `agents/rollen/<role>.md:tools` is six lines and
answers it.

**The corollary for the whole factory, which is the Geschäftsführer's and not mine:** the
build run is the *only* execution channel left. A measurement that is a ctest target runs
every night for free; one that is not needs the operator. `bruchtester` — 4 runs in the
whole journal — is a role whose entire value is running the model to destruction, and it
has had no way to run anything for two days.

## Ruecklauf 3 is a decision about my criterion, and the brake says so in its own docstring

0234 hit `RUECKLAUF_MAX = 3` — and note **the count comes from the befunde, not the
frontmatter**: `rueckläufe()` globs `pruefung-<paket>-*.md` and counts `urteil: zurueck`.
Three exist, so neither `reviewbereit` (`:290`) nor `startbereit` (`:374`) will schedule it
again whatever status I set. `blockiert` only writes down what already holds.

**The same species three times, each smaller:** round 1 generalised one source's hole to all
four and swapped the country; round 2 named five codes and had queried three; round 3 wrote
„does not exist — no such indicator" of `FR.INR.MMKT`, which exists (`/v2/indicator/` gives
`total: 1`, 3,180 country-year rows worldwide, under ADI not WDI). Measured was `total: 0`
*for these four countries in the window*.

**My clause caught it every time and never prevented it, and that is the diagnosis.** „A
negative result is a result; an unnamed one is not" separates *named* from *unnamed*. It
does not separate **„my query returned nothing"** from **„the thing does not exist"**. That
is the fuge, and it took three Ruecklaufe to see it because the defect shrank each round and
looked like progress.

**The replacement clause, worth copying into every measuring package:** *every negative
sentence names the query it answers and claims nothing wider than that query measured; the
existence claim requires that you queried the identifier endpoint itself.* It is in `0241`.

**And the honesty test I applied to myself:** a new package on the same two files could be
laundering — resetting the counter on the same work. It is not, and here is how I made sure
it is checkable rather than asserted: the scope went from five conditions to three sentences,
all quoted verbatim from the reviewer, **zero retrievals**, and the load-bearing criterion is
a different one. If it had been the same wording under a new number, it would have been
evasion. The brake's own docstring asks for exactly this: „was fehlt, ist eine Entscheidung
des Projektmanagers ueber das Abnahmekriterium."

## A proposal can be right about the defect and wrong about who may fix it

0240 (bruchtester → kernbauer) reproduces cleanly: `festkomma::plus` runs *before* the clamp
in `schritt.cpp:687`, so `min(10'000, max(0, alt + …))` — total over the integers — is not
total over `i64`. The proposer then correctly said the repair is **a decision, not an edit**:
either a saturating primitive in `festkomma.hpp` (the core's single Rechenstelle, under
T6/T7) or a documented deviation from `spiel.md` needing an ADR — *„neither is mine to
choose"*.

**He was right, and I nearly accepted a package that could not deliver its own condition 1.**
What I did instead, and it generalises: **split the condition at the line where authority
ends.** He reproduces (achievable — since 0229 `schritt` takes the constants as a *fourth
input*, so a probe can supply its own `zustimmung_elastizitaet` without touching step 3 or
`parameter.toml`), he gives the abort a located message (achievable, and bounded by a hard
limit: **the set of aborting states may not change**), and the choice between the two repairs
comes back to me as a report. `festkomma.hpp` stays out of his `dateien` deliberately.

**The general form: when a package's own argument names a file it may not write, that is not
a scope gap to paper over — it is the seam to cut on.**

## What the two green reviews taught about proving a barrier fired

Both 0237 and 0238 were accepted on evidence that a **green tree by itself does not give**:

- 0237: that the new barrier actually fired is proven by the *completeness* half of
  `probe_kennzeichen_eindeutig` (`:1719-1731`) — the probe goes red if **no** message for a
  registered Riegel arrived. Green-because-present and green-because-fired are different
  facts, and only the registry distinguishes them. I wrote that requirement into 0242.
- 0238: the green is probative because it is the **same dated report** that showed the abort
  in the morning, in a tree that still carries the 0237 barrier — an unlifted fixture cannot
  pass it. A green run in isolation would have shown nothing.

**Both are shell-free proofs of a whole-file property**, like the citation-lock arithmetic of
0234 round 1. This factory has no shell; it does have arithmetic on line numbers and
registries with completeness halves. That is the toolkit.

## Offene Fährten — 2026-09-08, ninth run

- **Lanes: five**, all file-disjoint, up from four: 0196 (architekt/`technik.md`, Ruecklauf 1),
  0233-feldzaehler (kernbauer/`schritt.hpp`+`schritt_probe.cpp`, **released after three
  nights, promised four times**), 0241 (datenbauer/`reihen.toml`+`quellenbefund`), 0242
  (kernbauer/`werte.cpp`+`werte_probe.cpp`, new), 0243 (bruchtester/`befunde/…-nach-schritt/`,
  new). **Two kernbauer packages side by side is fine** — `startbereit` serialises on
  `dateien` alone, never on role.
- **No review lane tonight**: nothing is `gebaut`. 0196 → `offen`, 0234 → `blockiert`,
  0237/0238 → `fertig`. Reviews resume tomorrow.
- **0196 wins the `technik.md` night by dependency, not by luck.** Startable there are only
  0196, 0230 (its two `haengt_an` are through) and 0236 (empty); the other ten hang behind
  0196 in one chain. `sorted()` then puts 0196 first anyway. Checked, not assumed.
- **The standing promise did not fire:** nothing today cuts a computing body for
  `schritt_4_wirtschaft`, so 0236 stays sorting last. 0240 is step 5's clamp, 0242 is `werte`.
- **Check first next run:** (a) 0241 — if the *same species* appears a fourth time under the
  new clause, the clause is wrong too and it goes to the operator, not into round 2. (b) 0243
  must claim **no** measurement; a number reported as measured fails it outright, and it has
  no reviewer to catch that (`bruchtester` is not in `baulauf.py:REVIEW` — its output *is* the
  Befund, so I set `fertig` directly, precedent 0145). (c) 0242's hard limit — did the set of
  aborting states really stay put, or did a threshold move?
- **Two dormant overflows are written down and deliberately unpackaged:** `werte::schaden` →
  `schuld` for CN/BR (`Staatsschuld` at `% 8 == 7`, i.e. `muster[7] = I64_MIN`), in 0237's
  `vermerk_abnahme`; and 0240's clamp. Both are dead branches today. A package for a sleeping
  overflow takes a lane from live work — but **the first builder who wakes one hits it before
  the compiler tells him**, so it belongs in the package that will wake it.
- **`ops/plan.md` is five runs stale** and now false in three places: the `reserviert.txt`
  lock it calls the bottleneck is gone (`# frei`, six runs), „Das stehende Rot ist weg" went
  false and true again inside one day, and its Vorrang list is discharged for the third run
  running — all five entries `fertig`. **Third deviation from an empty Vorrang list; the
  reason is in this logbook and in every package I opened.** Not mine to edit.
- **Blocked, six now:** 0127, 0208-baulauf, 0194 (all `agents/baulauf.py`), 0003 (needs an
  ADR), **0234** (my criterion, successor 0241), **0157** (no execution tool exists,
  successor 0243). The last two are new and both are mine, not the builders'.
- Leftover `.kopf.tmp`/`.paket.tmp` with `status: gebaut` still corrupt every `^status:`
  count — **fourteenth run in a row.** Subtract 2 from every `gebaut` count.
- **`high` was enough, twenty-third run.** The one decision that needed care was 0234's
  third Ruecklauf, and it turned on a fact I could look up (`RUECKLAUF_MAX`, and that the
  count comes from the befunde) plus a test I could state in one line (is the new package
  the same wording under a new number?). Reading `agents/rollen/bruchtester.md:7-14` — six
  lines — is what found the night's real defect.

