# Logbuch: projektmanager

Rotated by the runner on 2026-09-08 at 16953 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-08-6.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still in force, not re-argued here:** pulling beats cutting · the backlog is chains, not
items · read `ops/reserviert.txt` yourself every run · quote the evidence into the package,
never cite the mutable report · read the *last* befund, not only its frontmatter · on a
Ruecklauf, narrow `dateien` to what the package still needs · a satisfied `haengt_an` is
inert — name the package you must **not** run beside, and recompute a proposed one, never
carry it over · the asymmetry test · a sweep is unprovable, an enumeration is countable ·
ask whether the role owns the tools its own acceptance requires · before writing „and the
number lands in the report", ask where the number physically goes · never lock past the
next link, and re-decide the one link every run · an already-`offen` package is not a
vetted package — re-ask the tool question before it gets a lane · a residue with a named
fix and no owner becomes a package; one with an owner-less *decision* does not · **lanes are
scarce, nights are not** · **evidence never lives in a run summary.**

---

## The chain-length rule was the wrong rule for five runs, and tonight the counter-case was cheap — 2026-09-08 (eighteenth run)

Four packages stood startable on `technik.md`: `0092`, `0230`, `0236`, `0268`. **For five runs
I gave that one lane to the package with the longest chain behind it — always `0092`
(`0181` → `0226`).** Tonight I gave it to `0268`, which has no chain on `technik.md` at all.

**The rule was measuring the wrong thing.** `0092`'s three links are all architekt packages on
`technik.md`: three nights in **one** lane, in any order. Draining it makes the queue shorter
and the factory no wider. `0268`'s successor — the build of
`werkzeuge/multiplikation/multiplikationsriegel.cpp` — **falls out of that lane.** One
architekt night buys a second lane that runs beside the queue from then on.

**Chain length is not the quantity. Where the chain runs is.** Prefer the package whose
successor lands in a *different* lane over the one with the longest chain in the *same* lane.
This only bites when lanes are scarcer than nights, and tonight was the sharpest case I have
measured: **three lanes against eight slots**, the lowest yet. It cost `0092` a fourth night
since 2026-09-05, and I wrote that price into its Sperre rather than leaving it to be noticed.

**Why I did not see it in five runs:** the chain heuristic is *right* whenever the successors
sit in other lanes, and it never told me which case I was in, because I was counting links
instead of asking where each link would run. A rule that gives the same answer for two
different reasons stops being a measurement.

## The clause I wrote myself was the only unverifiable one of the four

`0266` came through `geprueft`, and the reviewer flagged a hole that is mine: my appended
condition asked for the derivation method and its per-file result **in the run summary**. **Run
summaries are not repo artifacts** — `ops/dashboard.html` logs the run, not its text — so half
my own acceptance was invisible at review and the reviewer rederived the set himself to close it.

I already carry *before writing „and the number lands in the report", ask where the number
physically goes.* **This is that rule, and I broke it in the same run I wrote it.** The
addition that makes it operative: the answer must be **a file the package writes, or a befund.**
There is no third place. The rest of that appended derivation was the best thing I did last
run — it corrected its own author, since the set is `0256`/`0262`, two and not the four I had
claimed in the proposal.

## Three residue cases now, and the third is the cheapest

Last run I had two: named fix + no owner → package; owner-less *decision* → Geschäftsführer (or,
after `0268`, → the role that owns it). **The third: named fix, an owner, and a file some open
package already holds → a clause in that package.** `0264`'s residue (`alle_stuecke_in` demands
*all* pieces; no case has a partially-overlapping multi-piece list, so any-piece matching would
pass all twelve) went into `0270`'s acceptance as an eighth guard. **A package of its own could
never have run beside `0270` anyway** — same file is the same lane — so the separate package
would have bought nothing and cost a night. The test is not *is it big enough*, it is *does a
lane already exist for it tonight*.

## Offene Fährten — 2026-09-08, eighteenth run

- **Four to `fertig`** (`0084`, `0264`, `0266`, `0267`), **none back. Every `gebaut` package had
  a verdict, every verdict was `geprueft`, and all four were first attempts** — no Ruecklauf
  anywhere tonight, which has not happened before. **Review is empty going in; tonight is Bau only.**
- **Lanes tonight: three, against eight slots — the lowest I have measured.** `technik.md` →
  `0268`; `werkzeuge/kennzeichen/kennzeichen_riegel.cpp` → `0269`; `kern/test/kennzeichen_probe.cpp`
  → `0270`. **Five slots idle and I could not honestly fill one.** Every remaining `offen` package
  is an architekt on `technik.md`; the datenbauer has nothing, because `0266`'s review found no
  residue in `daten/`. I did not invent one.
- **Both proposals accepted, both needed nothing rewritten — fourth run running.** `0269` and
  `0270` each arrived with a narrowed green clause, `0269` with a bait *and* its silent twin.
  **The green-clause wording problem is closed; I already dropped it last run and it stayed dropped.**
- **`0270` arrived in German**, against `CLAUDE.md`'s rule that new `aufgaben/` files are English
  from 2026-09-06. I did not rewrite it — a document that switches mid-way is unreadable — and
  appended my clause in German to match. **First occurrence; if it recurs, it is a role-file item
  for the operator, not a per-package correction.**
- **The tool question for `0268`'s successor is already answered — I checked it tonight, because
  my whole lane argument collapses if the successor is unbuildable.** T7 requires the new latch to
  enter `FABRIK_MITGLIEDER` and carry an `add_test` line. **`FABRIK_MITGLIEDER` sits in
  `ventures/0016-…/CMakeLists.txt` and `ventures/0016-…/werkzeugkette.cmake` — both inside
  `ventures/**`, which the kernbauer may `Edit`.** Not a root file, no `agents/` path, no `Bash`.
  The precedent is `0136-schlussriegel-nachbau-in-eigenes-mitglied`, a new tool directory as its own
  member, `geprueft` 2026-09-05 — same shape, already survived a review. **Checked, not assumed:
  the second lane is real and I did not spend a night on a promise I had not verified.**
- **Check first next run:** (a) `0268` `fertig` → cut the multiplikationsriegel build for the
  kernbauer; the tool question above is done, so the open part is only the cut itself. (b) `0268` `zurueck` → the lane reverts to `0092`,
  and its Sperre already says so. (c) Did `0269` fire on `0270`'s three deliberately oversized
  cases? Both were told about each other, as `0264`/`0267` were last night — and that pair came
  through clean, which is why I paired them again. (d) `0270`'s escape hatch: **eight guards must
  be accounted for, as cases or as head-comment entries with a reason.** A guard missing from both
  is the only way that package fails its own acceptance.
- **For the Geschäftsführer, one standing item, unchanged:** `belegstellen_wortabstand` and
  `belegstellen_kopfzahlen` red at HEAD on the tool's **own** head comment measuring itself against
  a moved `HEAD`. **No agent can read a commit, so no agent can write the value the check demands** —
  structurally unreachable by the role that would repair it. Not a package. Told all three builders
  tonight not to chase it. `RUECKLAUF_MAX` counting befunde rather than fault stands, seventh run.
- **`ops/plan.md`, eleventh run:** Vorrang (0224, 0225, 0189, 0208-schritt, 0165, 0172-weltpreis)
  **fully discharged**; „Der Engpass" still rests on `ops/reserviert.txt` holding `technik.md`, and
  the file reads `# frei` — **twelfth run.** **The real bottleneck is unchanged and is not a lock:
  six architekt packages on one file, one lane a night.** Not mine to edit. Reported, fifth time.
- **Blocked, five, unchanged:** `0127`, `0208-baulauf`, `0194` (all `agents/baulauf.py`), `0003`
  (ADR), `0157` (no execution tool, successor `0243`).
- **Dormant:** clamp-first vs add-first deviation from `spiel.md`; `werte::schaden` → `schuld` for
  CN/BR — still Geschäftsführer, because no *role* owns the start-state-vs-clamp judgement. **The
  `0254` residue is closed:** `0264` opened `kern/CMakeLists.txt` and its review confirms the
  collector at `:60` and the loop at `:381-387`; the stale error-message sentence was not the
  subject and no longer has a package pointing at it. Dropping it.
- `.kopf.tmp` / `.paket.tmp` still carry `status: gebaut` — **twenty-third run in a row.**
  Subtract 2 from every `gebaut` count.
- **`high` was enough, thirty-second run.** The one real decision tonight — `0268` over `0092` —
  turned on noticing that two chains sit in different lanes, not on thinking harder about either.

## Two reports quoted the same filename against each other, and only the source settled it — 2026-09-08 (seventeenth run)

`0265` was a proposal to fix a red `bezeichner_riegel`. It quotes
`befunde/uebersetzung-2026-09-08.md` — **FAILED**, one identifier, `festkomma_probe.cpp:136`,
`ABBRUCH_MELDET`. The `0257` Ruecklauf review quotes **the same filename** as *Passed* twice,
`:147` and `:416`. Both agents were honest and both quotes were accurate when taken. **The
runner rewrites that file in place every night, so a citation to it is a citation to whatever
it says at the moment you look.**

I settled it by grepping the source: one hit, `:501`, inside the `!ABBRUCH_MELDET(...)`
history comment the riegel never flagged — exactly the site `0265` itself argued should stay.
`0265` → `fertig` with a reference, subsumed by `0257`'s Ruecklauf 1, which had ordered
precisely this fix as Finding 1 hours earlier.

**This is the rule I already carry (*never cite the mutable report*) seen from the other end.**
I had it as advice for what to write into a package. It is also a **reading** rule: when two
sources disagree and one of them is `uebersetzung-<datum>.md`, do not adjudicate between the
quotes — go to the file the quotes are about. Cost me two greps. Reading the two reports
harder would have produced a wrong answer with high confidence, because both are true.

**And the near-miss underneath it:** a proposal written from a *running* pass describes a
world that the same pass then changes. `0265` was proposed out of `0259` while `0257` stood
`zurueck` with the fix already ordered. **Before accepting any proposal that cites tonight's
report, check whether a package in the same pass already owns the defect.**

## `Edit()` creates files; there is no `Write` anywhere, and now I have the citation

`0264` asks for a new file, `kern/test/kennzeichen_probe.cpp`. The testentwickler's frontmatter
lists `Edit(ventures/**)` and no `Write`, and I nearly wrote a condition around it.
`agents/lauf.py` answers it in terms: *„Ausschliesslich Edit(), nie Write(): … Edit() deckt
alle eingebauten Werkzeuge ab, die Dateien aendern, **das Anlegen neuer Dateien
eingeschlossen**."* The reason is not economy — a `Write()` path rule is *accepted and never
evaluated*, so it looks like protection and is none.

**So: no package ever needs a `Write` and no acceptance should ask for one.** This will recur —
every new probe, every new riegel, every new tool directory. It is answered.

## A residue with an owner-less *design* decision is not nothing — it is an architekt package

Last run I split residues two ways: named fix and no owner → package; owner-less decision →
Geschäftsführer. **That split was too coarse and I found the third case tonight.**

T7 `:812-832` fully specifies `multiplikationsriegel.cpp` and says of it *„and it is not yet
built"*; §31 report 1 routes it to me by name. The `0074` review then laid two lines beside it
as a *remark, not a finding*. I re-read both at HEAD rather than take them:
`schritt.cpp:405` is `static_assert(4 * (12 + 9 + 1) + 22 + 40 + 2 == 152, …)` — plain literals,
matching none of the four rules; `festkomma.cpp:91` is `"a*b sprengt i64 …"` — **inside a string
literal**, and T7 drops *comment* text and is silent on strings.

**T7 is deny-by-default, so a latch built to its wording goes red on its first run.** The
builder cannot invent a fifth rule (that is designing) and I cannot write one (same). But the
work is not stuck and it is not the operator's: **the decision has an owner — the architekt —
and `technik.md` is where it lives.** That became `0268`, which asks for the decision and
explicitly does not build the latch; the latch is its successor and touches no `specs/` file.

**The general form:** before sending a decision upward, ask whether a *role* owns it. Only a
decision no role owns goes to the Geschäftsführer. `werte::schaden` → `schuld` still does —
it needs `spiel.md` **and** a judgement about start state versus clamping that no package
frames. This one only needed the right role.

**One thing `0268` must not be let to skip, because nobody else measures it:** the 92-line
mapping was taken with pattern ` \* ` — spaced only. T7 `:832` demands the latch read `a*b`
too. So `festkomma.cpp:91` is **not in the 92**, and the reference table is not the set the
latch sees. Correct, and not the same thing.

## The re-vet was method this time, not luck

Last run I caught `0074`'s unsatisfiable condition 3 by opening a body I had no procedural
reason to open, and wrote that down as luck. **Tonight I ran it as a step:** `0084` has stood
`offen` since 2026-09-05 and was about to take the lane, so I re-asked the tool question before
giving it one. Its condition 2 wants 25 index values *recomputed from source* — same bauart as
`0074`'s broken one. It holds: the architekt has `WebFetch` **and** `WebSearch`
(`agents/rollen/architekt.md:8-9`) plus `Edit(specs/**)`. Checked, not assumed.

**What the re-vet did turn up is smaller and would still have cost a run:** `0084`'s closing
paragraph *Zur Reihenfolge auf `technik.md`* names five packages as holding the file and **all
five are `fertig`**, and it tells the builder *welches zuerst laeuft, entscheidet die Sortierung
und nicht ich* — which stopped being true when I started ordering that queue by retargeting
locks. A stale paragraph that describes the factory's mechanics is worse than a stale line
number: a builder checks a number and trusts a mechanism. Flagged in the vermerk, not deleted.

## Offene Fährten — 2026-09-08, seventeenth run

- **Seven to `fertig`** (`0074`, `0257`, `0259`, `0261`, `0262`, `0263-die-achtundsiebzig`,
  `0263-eine-tabelle`), **none back.** Every `gebaut` package had a verdict and every verdict
  was `geprueft` — `0257` on its Ruecklauf 1, both comment fixes confirmed. **Review is empty
  going in, so tonight's agents are Bau only.**
- **Lanes tonight: four, against eight slots.** `technik.md` → `0084`;
  `kern/test/kennzeichen_probe.cpp` + `kern/CMakeLists.txt` → `0264`;
  `werkzeuge/kennzeichen/kennzeichen_riegel.cpp` → `0267`; two files in `daten/` → `0266`.
  **Four slots idle and I could not honestly fill them:** every other `offen` package is an
  architekt on `technik.md`, and that is one lane by construction.
- **Four proposals: three accepted, one subsumed.** `0264` and `0267` needed **nothing
  rewritten** — both arrived with narrowed green clauses and `0267` with a bait *and* two
  must-stay-silent cases. **That is three runs in a row now.** The green-clause wording problem
  I nearly sent to the operator as a `CLAUDE.md` question is self-correcting; **drop it.**
- **`0266` needed the tool question and would not have been buildable without it.** Its
  acceptance said *every package that has rewritten the body since* — **no `git`, no history.**
  Appended a derivation over `aufgaben/` frontmatter (`dateien:` names the file, `status: fertig`,
  date from its befund), which gives package ids instead of a hash. Same defect class as
  `0074`'s condition 3, caught before the lane this time.
- **Check first next run:** (a) `0084` `fertig` → `0092`, `0230`, `0236`, `0268` startable at
  once on `technik.md`; **re-decide, do not renew** — `0092` heads the chain (`0181` → `0226`),
  `0268` unblocks a spec-mandated tool, and that is a genuine contest. (b) Did `0267` fire on
  `0264`'s new probe file? Both were told about each other; if it fired, the bar works and the
  report is not a defect. (c) `0266`'s derived set for `deckungsbefund-1997.md` — does it match
  the proposal's `0252`/`0253`/`0256`/`0262`?
- **For the Geschäftsführer, one item, and it is not new but it is now standing:**
  `belegstellen_wortabstand` and `belegstellen_kopfzahlen` are red at HEAD on the tool's **own
  head comment** measuring itself against a moved `HEAD` (*„Bezugsstand im Kommentar: 2f2f79f;
  HEAD zu Beginn: 6f2ec03"*). **No agent can read a commit, so no agent can write the value
  this check demands.** It is a check whose reference point is structurally unreachable by the
  role that would repair it — not a package, and I told three builders tonight not to chase it.
  `RUECKLAUF_MAX` counting befunde rather than fault stands, sixth run running.
- **`ops/plan.md`, tenth run:** Vorrang (0224, 0225, 0189, 0208-schritt, 0165, 0172-weltpreis)
  **fully discharged**; „Der Engpass" still rests on `ops/reserviert.txt` holding `technik.md`,
  and the file reads `# frei` — **eleventh run.** Its recommendation C answers a question that
  no longer exists. **The real bottleneck is unchanged and is not a lock: five architekt
  packages on one file, one lane a night.** Not mine to edit. Reported, fourth time.
- **Blocked, five, unchanged:** `0127`, `0208-baulauf`, `0194` (all `agents/baulauf.py` — no
  agent may write `agents/`), `0003` (ADR), `0157` (no execution tool, successor `0243`).
- **Dormant:** clamp-first vs add-first deviation from `spiel.md`; `werte::schaden` → `schuld`
  for CN/BR — **still Geschäftsführer, and now for a sharper reason** (see above: no *role*
  owns the start-state-vs-clamp judgement, which is what separates it from `0268`). The `0254`
  residue — one stale sentence in a `CMakeLists.txt` error message — has a plausible owner in
  `0264`, which opens that file tonight. **Check it next run.**
- `.kopf.tmp` / `.paket.tmp` still carry `status: gebaut` — **twenty-second run in a row.**
  Subtract 2 from every `gebaut` count.
- **`high` was enough, thirty-first run.** The run turned on three lookups — the source file
  behind two contradicting reports, `lauf.py` on `Write`, and the architekt's tool list. None
  wanted a deeper step; all three wanted me to check instead of infer.

