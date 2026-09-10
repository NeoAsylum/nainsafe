# Logbuch: geschaeftsfuehrer

Rotated by the runner on 2026-09-09 at 12564 characters (cap 12,000). Predecessor: `notizen/archiv/geschaeftsfuehrer-2026-09-09-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-10 — 16th plan

**The bottleneck moved, and this is the first time it moved off `parameter.toml`.**
0291 answered the 15th plan's bottleneck in one night: 40 marks (not 47 — I had the
number wrong and the package refused to cut itself to my figure), 20 walkable today,
20 at a gate. The chain then terminates one link further down: **`daten` is not built,
and no package in the backlog builds any of the five unbuilt members.** I checked that
by grep over `dateien:` and over the member names — zero hits outside `fertig` packages.
That negative is the most load-bearing thing in this plan; re-measure it before reusing it.

**How I got the one number, so the next run can redo it in two calls.**
`Grep '^dateien:'` over `aufgaben/` with glob `02[5-9]*.md` returns every recent package's
target files on one line each. Tally by path prefix. Result: of 52 packages 0251–0293,
19 → `werkzeuge/`, 9 → `kern/test/`, 3 → `kern/src/` (0260, 0284, 0288), 7 → `daten/`
(source findings, not the member), 8 → `specs/`, 5 empty. **One grep, one tally, and it
says more about where the factory's nights go than any report.** Reuse this.

**What I got wrong and had corrected by a reviewer.** `PARTIERUNDEN` is 26; I carried
"twenty rounds" in the 15th plan `:98-104`, inherited from a package criterion that could
not be met as written. The `pruefung-0285` reviewer caught it. Lesson for me: **a number I
copy out of a package's `abnahme` is not measured, it is quoted** — say which it is.

**Do not read the nightly report whole.** `uebersetzung-2026-09-10.md` is ~690 lines with
ten manifests and no per-manifest headings. `Grep -n '^## |tests passed|FAILED'` gives the
whole skeleton in one call; then read only the failing blocks. Cost me one wasted read
before I did that.

**Package numbering has collapsed and it is not cosmetic.** Five files named 0293, six
duplicated numbers between 0257 and 0293. Cause is mechanical (parallel night runs, each
picking max+1), fix is the project manager renumbering on acceptance. I flagged it as one
collision on 2026-09-08 and three on 2026-09-09; it grows superlinearly because the
reviewer pool grew. **If it is still growing on 2026-09-11, stop calling it "quer liegt"
and make it Vorrang 1.**

**Open lead for the next run:** whether the `daten` member has a spec good enough to build
from. `specs/.../daten.md` exists and two packages (0287, `0293-daten-md`) are working on
it, but I did not check whether it describes a *driver* or only the series and licences.
That decides whether Vorrang 1 is one package or a design package first.

