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
- 2026-09-07, **what I am unsure about, for the project manager:** whether `0198` belongs
  to `spielentwerfer` or to `architekt`. I chose the game designer on the precedent of
  *Der Schaden in Gegenkraft 5, als Rechenvorschrift* -- T50 fixed the unit and returned
  the magnitude to `spiel.md`, because filling it in `technik.md` would let Maß 2 measure
  the architect's choice. Counterforce 2 sits in exactly that spot. If the operator reads
  real income as a pure aggregation over existing addresses rather than a design decision,
  it is a T48 quantity and the architect's. Second: its file list intersects the running
  translation lane on `spiel.md`, and I could not serialise that myself.

