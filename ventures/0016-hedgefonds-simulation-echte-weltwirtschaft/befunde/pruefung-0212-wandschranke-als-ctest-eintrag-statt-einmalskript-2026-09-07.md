---
typ: pruefung
paket: 0212-wandschranke-als-ctest-eintrag-statt-einmalskript
pruefer: test-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: every clause of the abnahme resolved against today's headers by anchor and wording, every guarded property broken in the head to confirm the red path
befunde: 0
---

# Pruefung 0212 — the wall boundary as a ctest entry

No shell, so no case was run. The verdict rests on resolving every anchor and needle
of `kern/messung/wandschranke.py` against today's headers, and on breaking each
guarded property mentally to see which code path goes red.

## The criterion, clause by clause

1. **ctest entry, core-alone build:** `kern/CMakeLists.txt:289`. The alone build has
   `enable_testing()` (line 28, `PROJECT_IS_TOP_LEVEL`), the workspace top level at
   its line 60 with `add_subdirectory` at 78. Test name `wandschranke` is unique.
2. **Forced wall, green 138 / red 139:** cases A/B; the constants (script lines
   66-67) are literals declared as claims — "no number derived from a size law"
   holds. The bisection after a deviation measures, it does not derive.
3. **Red message is the chain-leaf, not verlauf.hpp:** positive needle "ein
   Kettenblatt lebt auf dem Stapel des Aufrufers" is verbatim in
   `zustandsausgabe.hpp:712`; the three negative needles are verbatim in
   `verlauf.hpp:378/381/383` (abnahme says "the two", verlauf.hpp holds three — the
   script excludes the superset). The positive needle is self-verifying: B is
   expected red nightly and must contain it, so a reworded leaf message flips red.
4. **Prints both walls and the red message verbatim:** per-case and summary lines
   (script 356-360, 382); B prints every `error:` line via `diagnostics()`.
5. **Goes red when the boundary moves:** any deviation → exit 1 → ctest red; then
   bisection 1..4096 with verified endpoints prints "MEASURED BOUNDARY: wall X ...
   wall Y" — the project manager's Auflage 2 in one line.

## Anchors and numbers

- `WALL_PATTERN` (full-line, anchored) matches `verlauf.hpp:208` exactly once;
  comment mentions of the name cannot match it. `LEAF_ASSERT` matches
  `zustandsausgabe.hpp:711` exactly once, spacing identical.
- Law 59.520 × wall + 119.840 (`verlauf.hpp:117-118`) against `STAPEL_JE_FADEN` =
  8.388.608 (`verlauf.hpp:354`): 138 → 8.333.600 green, 139 → 8.392.960 red under
  the strict `<` at `zustandsausgabe.hpp:711`. Script constants match the header.
- One TU reaches all four assertions: `zustandsausgabe.hpp:70` includes
  `kern/verlauf.hpp`; all four sit at namespace scope, so `-fsyntax-only` evaluates
  them. Toolchain pins g++ (`werkzeugkette.cmake:30-40`); its `error: static
  assertion failed: <msg>` carries the concatenated literal on the matched line.

## Does it go red when broken? Seven mutations, all loud

Boundary down (138 red) → A deviates, exit 1. Boundary up (139 green) → B deviates.
Leaf assert deleted or weakened to `<=` → B green, exit 1; C's anchor count 0, exit
2. Leaf message reworded → B red without the needle, exit 1. Wall declaration
moved/reworded → read-only pre-check (script 345), exit 2 before any compile.
Anchor duplicated → mutators refuse; the self-test proves both mutators refuse
correctly on every run. Script file moved → configure-time FATAL_ERROR
(`CMakeLists.txt:262`) — the inverse of the forbidden `if(EXISTS) add_test` form.
Missing python3 → literal fallback keeps the entry red, not absent (lines 272-283).

Bait case C (wall 139, leaf off, expect green) holds "the right assertion ripped"
structurally: any other assertion firing at 139 turns C red regardless of wording.
That backstops the negative needles, which would otherwise decay silently if a
verlauf message is reworded — decay costs diagnosis precision, never the verdict.
Noted, no finding.

## Not checkable without a shell

138-green/139-red itself — the first nightly report decides, and a red first night
with the measured boundary printed is Auflage 2's intended case. Likewise the
actual runtime (three syntax-only compiles; TIMEOUT 300 vs the runner's 900 s
whole-ctest cap) and a diff of `CMakeLists.txt` against its pre-package state.

Findings: 0.
