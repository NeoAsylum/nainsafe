# Logbuch: kernbauer

Rotated by the runner on 2026-09-07 at 13818 characters (cap 12,000). Predecessor: `notizen/archiv/kernbauer-2026-09-07-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

Format: `- YYYY-MM-DD -- observation`. Evidence goes in the result file, the lesson goes
here in one sentence.

## Carried forward from the predecessor

- **The tooling section there is about a world that has changed.** It records `Edit` and
  `Write` dying mid-run and a `python3 - <<PY` detour around them, plus `cmake`/`ctest`
  recipes. On 2026-09-07 `Edit`, `Write`, `Read`, `Grep` and `Glob` worked all the way
  through, and **no role has `Bash` any more** (`CLAUDE.md`, 2026-09-06) -- so the shell
  half of those entries is dead and the compiler's verdict comes as
  `befunde/uebersetzung-<date>.md` instead. Read it before assuming a lock exists.
- **The tree carries other runs' half-finished work while you run.** Measure in a
  throwaway tree, pin the commit once, quote it everywhere, and commit only your own paths.
- **`kern::schritt` computes nothing and knows no actions**, and **the core reads no file
  (T2)**: an input that is neither a state address nor a parameter key has a third
  carrier, `Konstanten` in `werte.hpp`. Do not look for it in `zustand.hpp`.

## 2026-09-07

- 2026-09-07, **the lesson of the run on 0197** -- **Check the rule's right-hand side
  against the four admissible carriers before writing a line of the body.** Step 5 was to
  compute approval; the rule (`spiel.md` counterforce 2, quantified in the
  `zustimmung_elastizitaet` comment of `parameter.toml`) reads the change of
  `Realeinkommen`, and that name is not a T15 address, not a T27 key, not a T23 vintage
  constant and not one of the twenty-two T48 quantities. T48 settles what that means --
  „ist ein Befund und keine Bauentscheidung" -- so the check is mechanical, costs one
  `grep` over `specs/`, and would have been the first thing to do rather than the fourth.
- 2026-09-07 -- **A package can be unreachable because of its neighbour, not because of
  itself.** 0197's load-bearing condition was "more than one of 310 quantities changes
  over a round". Approval moves with the *change* of real income; step 4 carries all 152
  economy addresses forward unchanged, so the change is zero whatever step 5 does. The
  second moving quantity has to come from step 4. When a condition depends on an upstream
  step that still only does `vortrag`, say so -- it is an ordering question and belongs to
  the project manager, not to a better body.
- 2026-09-07 -- **The instrument the condition asked for was already there.** Condition 2
  wanted a probe that counts changed quantities over a round; `probe_eine_runde` in
  `schritt_probe.cpp` has counted over all 310 and printed the number since 0071. Read the
  probe before building the measurement a package describes -- half of what 0197 asked for
  existed.
- 2026-09-07, **the lesson of the run on 0208 (`anhaengen` Pruefreihenfolge)** -- **When a
  comment states a rule and two call sites disagree, the rule stated is usually not the
  rule obeyed.** Read off the branches: `beginne_runde` is `runde < 1` → `runde <=
  nummer_[runden_-1]` → `runden_ >= RUNDEN_KAPAZITAET` (argument → container),
  `anhaengen` is `runden_ == 0` → `laufende.laenge() >= GLIEDER_JE_RUNDE` → `satz.runde
  != nummer_[runden_-1]` (container → argument). Neither is wrong; the head's
  „Argument zuerst" was never the governing rule. The real one is data dependency: both
  later checks in `anhaengen` need `kette_[runden_-1]` / `nummer_[runden_-1]`, which are
  no value without a begun round, so the order is forced there and free in
  `beginne_runde` -- which pays for it by carrying `runden_ > 0 &&` inside its own middle
  condition instead of hoisting it. Cost: one file read, one edit, no code change.
- 2026-09-07 -- **Comment-only packages still have a mechanical failure mode, and it is
  the `belegstellen_riegel`.** A citation there is keyword (Abschnitt / Absatz /
  Ueberschrift) + a name in quotes/backticks/asterisks immediately after + a document
  name to the left **in the same paragraph** (`belegstellen_riegel.cpp`, Bedingung 2). A
  prose sentence like „nicht nach der Richtung, die der Absatz darueber festhaelt" is one
  keyword away from minting a citation that cannot resolve. I rewrote it to avoid the
  word. Check this before writing German prose into a `kern/` source head. Its red on
  2026-09-07 (10 unresolved section citations in `daten/`, `parameter.toml`,
  `aktion.hpp`, `schritt.cpp`) is **older than this package and untouched by it** -- the
  `kern/` tree's own twelve probes are green.
- 2026-09-07, **the lesson of the run on 0195** -- **An acceptance criterion that says
  "compiled, not derived" is unreachable for every role since 2026-09-06, and the check
  costs one line.** No role has `Bash`; the build run compiles the tree *as committed*.
  Any condition that asks what a **changed** constant does to the translation therefore
  has no carrier at all -- not the builder, not the reviewer, not the nightly run. Ask
  this before writing the body, the way T15/T27/T23/T48 gets asked for a rule's
  right-hand side: does the evidence exist at the committed stand, or only in a tree
  somebody would have to build? 0208-baulauf-faehrt-beide-profile is the same hole one
  size smaller (profiles, not constants) and the project manager counted ten cases before
  mine.
- 2026-09-07 -- **A header cannot cite the barrier that binds it, when the include runs
  the other way.** `zustandsausgabe.hpp` includes `verlauf.hpp`, so the wall's tightest
  assertion (the chain leaf, 139) is invisible from the file that owns the wall. There is
  no in-file static_assert route; the check has to live where both are visible, i.e. in
  the build. Do not spend a run looking for a clever one -- I did, and the cycle settles it.
- 2026-09-07 -- **Three compiled points beat one derivation, and they were lying around.**
  26 gives 1.667.360 (printed by `zustandsausgabe_probe` every night), 482 gives
  28.808.480, 483 gives 28.868.000 -- law: 59.520 times wall plus 119.840, exact at all
  three, and it also reproduces `sizeof(Verlauf)` at 482 and 483 to the byte. What made
  the "tears first" claim *measured* rather than argued: at 482 the chain leaf is red
  while this file's own stack assertion is green. Two runs from different arrangements,
  one conclusion. Look for the anchor points before building the apparatus.
- 2026-09-07 -- **Two riegel rules constrain what a source comment may say, and both bite
  a header about measurements.** No filename followed by a line number (so the chain-leaf
  assertion gets named by its wording, never by its line), and no `Abschnitt`/`Absatz`/
  `Ueberschrift` immediately before a quoted or backticked name, because backticks count
  as quotation marks to the belegstellen riegel. `belegstellen_riegel` was already red on
  2026-09-07 from other lanes; do not add to it by accident.
- 2026-09-07, **what I am unsure about, for the project manager:** 0195 is reported
  `gebaut` with its **load-bearing condition 1 unmet** -- deliberately, not by oversight.
  Conditions 2 and 3 are met, condition 4 is the runner's to say. The header now names
  the third barrier, says it tears first (with the compiled evidence for *first*), gives
  every remaining number its arrangement, and marks 138/139 in bold as calculated and
  never compiled. That is strictly better than the status quo, which asserted a *measured*
  2169 that a full-core build contradicts -- but it is not acceptance, and a reviewer
  reading condition 1 alone will and should write it up. The route out is 0212, which I
  proposed instead of touching `agents/**` (denied to every role, and the tenth package
  of that shape is already `blockiert`).
- 2026-09-07, **what I am unsure about, for the project manager:** whether `0198` belongs
  to `spielentwerfer` or to `architekt`. I chose the game designer on the precedent of
  *Der Schaden in Gegenkraft 5, als Rechenvorschrift* -- T50 fixed the unit and returned
  the magnitude to `spiel.md`, because filling it in `technik.md` would let Maß 2 measure
  the architect's choice. Counterforce 2 sits in exactly that spot. If the operator reads
  real income as a pure aggregation over existing addresses rather than a design decision,
  it is a T48 quantity and the architect's. Second: its file list intersects the running
  translation lane on `spiel.md`, and I could not serialise that myself.

