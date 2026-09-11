# Logbuch: projektmanager

Rotated by the runner on 2026-09-11 at 15581 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-11-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-11, 26th run — 8 startable lanes, and the one that jams

**The number to carry: eight mutually non-overlapping packages stand `offen` and
startable tonight.** `GLEICHZEITIG` is 8. Every earlier run I have a record of managed
three. The cause is not that I cut better — it is that seven `geprueft` findings landed
in one night and freed seven different files. Do not read it as a method that repeats.

The eight: `0303` (technik.md), `0306` (werkzeuge/aufbereitung/**), `0307` (spiel.md),
`0299` (kern werte), `0305` (zahlwort_riegel), `0310` (parameter.toml), `0298`
(messung-0180/messen.py), `0289` (kennzeichen_riegel, Ruecklauf 1).

**`0236` is the jam, and it is a missing *review*, not a missing build.** It has stood
`gebaut` since 2026-09-10 — the architect answered Ruecklauf 1 the same day — and got no
review on 2026-09-11. Six packages hang behind it: `0181`, `0226`, `0230`, `0276` on
`technik.md`, and `0292` → `0295` on `multiplikationsriegel.cpp`, which is one of the
three red bolts. **Next run: check this first.** If it is still `gebaut` unreviewed, that
is a runner question for the Geschäftsführer, not a backlog question for me — the build
side has eight lanes and the review side is dropping packages.

**Lesson, and it cost `0302` a night it did not have to lose: check the proposal's first
condition against the proposing role's own write rights.** `0302` came from the
`kern-pruefer` with `rolle: kernbauer` and condition 1 *"It needs a sentence in `spiel.md`
or an ADR"* — a file no kernbauer may write. The proposer saw the conflict and named it in
his own body; he could not resolve it, because splitting is my move and not his. This is
the **second** class of defect that the four checks miss (the first was `rolle: builder`,
2026-09-02): the role exists, the files are clean, the dependency is met — and the
acceptance still demands a file the role's tools withhold. **Add it to the four: does the
named role have write rights to every file the `abnahme` requires?** Cost of missing it is
a whole run, either as an invented number or as a `blockiert`.

**On the numbering: I broke the mtime rule on purpose, once.** Three packages were written
as `0303`. The predecessor's rule is "the first written keeps the number". I gave `0303`
to `eine-runde-und-ihre-stuetzstelle` instead, because `ops/plan.md` names it as Vorrang 1
**by that number** — renumbering it makes the operator's plan point at a file that does not
exist. The other two are `0304` and `0305`, old files stubbed with `dateien: []`. **Rule
for next time: a package the current plan names by number does not get renumbered.**

**What I could not resolve, written down so I do not re-derive it.** The bottleneck
`werkzeuge/aufbereitung` cannot be built whole, and for two independent reasons I measured:
(1) T23 says it reads "the frozen raw files" — **there are none in the repo**, no `.csv`,
no raw directory, and no role can fetch one; (2) the byte form of `jahrgang-<jahr>.bin` is
in **no** section of `specs/` — `Grep` over `technik.md` gives the filename exactly once,
at T23 `:1752`, without a format. So `0306` takes the format-free half: T23 point 5
(`durchgriff`) and point 7 (normalisation), both complete integer rules, both testable on
written-out numbers. After it the member exists, has a manifest and falls out of the
skip list — and what remains is one spec decision and one procurement, both nameable as
gates. **Do not let a later package quietly invent that format.**

**Small mechanism worth keeping:** a new member needs no root `CMakeLists.txt` edit.
`ventures/<venture>/CMakeLists.txt:77` already lists `werkzeuge/aufbereitung` in
`FABRIK_MITGLIEDER` and `:86-91` adds any member whose own manifest exists. So a new-member
package is a **perfectly free lane** — four new files in an empty directory, zero
collisions. Three such members are left (`konsole`, `oberflaeche`, `werkzeuge/aufbereitung`)
and each is a free lane for whoever cuts it. **But warn the builder about the Warnsatz
bolt**: 32 compiling targets today, all with the warning set; a new target without it turns
the nightly report red.

**On the effort step: `high` was enough for this run.** The work was ledger work —
eight verdicts, one Ruecklauf, five proposals, two renumberings, two new packages. The one
decision that needed judgement (splitting `0302`) took reading two role files, not deeper
thinking. No complaint to record.

