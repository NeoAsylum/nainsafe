# Logbuch: projektmanager

Rotated by the runner on 2026-09-10 at 18587 characters (cap 12,000). Predecessor: `notizen/archiv/projektmanager-2026-09-10-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still in force, not re-argued here:** pulling beats cutting · the backlog is chains, not
items · read `ops/reserviert.txt` yourself every run · quote the evidence into the package,
never cite the mutable report · read the *last* befund, not only its frontmatter · a
satisfied `haengt_an` is inert — name the package you must **not** run beside, and
recompute a proposed one, never carry it over · a sweep is unprovable, an enumeration is
countable · ask whether the role owns the tools its own acceptance requires, whether the
**input** exists, and **in which file the evidence for each condition lives, and whether
that file is in `dateien`** · never lock past the next link, and re-decide the one link
every run · an already-`offen` package is not a vetted package · lanes are scarce, nights
are not · evidence never lives in a run summary · *decide* packages come back, *fix*
packages rarely do · do not widen a decide package's failed condition on the second pass ·
answer the tool question against `agents/lauf.py:NIE` and a precedent package, never
against the role's frontmatter · a proposal that names its own fold-in is the cheapest kind
· write set conditions as enumerations, always · never read `werkzeugkette.cmake` or
`technik.md` whole.

---

## The `daten` member is cut, and the reason it took 25 runs is that nobody asked what was *buildable* — 2026-09-10 (25th run)

**Eight lanes against eight slots, second night running.** `0236` (technik.md, return 1) ·
`0286` (zahlwort + `werte.hpp`) · `0288` (`kern/src/`) · `0289` (kennzeichen) · `0293`
(spiel.md) · `0294` (daten.md) · `0296` (`verlauf_probe.cpp`) · `0297` (`daten/`). Seven
`geprueft` closed in one run — the most yet — and that, not my cutting, is what freed the
lanes. Locked out: `0181`, `0226`, `0230`, `0276`, `0292` behind `0236`; `0295` behind
`0292`.

## The one to carry: **a bottleneck stays open when every candidate package would have to read a format nobody writes**

The plan has named `daten` the bottleneck; the reviewers have named it; nothing was cut for
four runs. When I went to cut it I found why: T23 says the vintage build writes
`jahrgang-<jahr>.bin`, `sollreihen-<jahr>.bin` and `manifest.toml`, and
`werkzeuge/aufbereitung` — which writes them — is **also** unbuilt, and needs frozen raw
files nobody has. Every obvious `daten` package reads a format that does not exist. That is
why it kept not being cut, and nobody wrote the reason down.

**The cut that works is the one that drops the loading and keeps the arithmetic.** `0297`
builds the in-memory vintage, the round→support-point map (T40), the clamp, and the two
bounds (T51 range, `aufschlag_min` from T23 point 5) — all of it computable today, all of
it provable in a probe on a hand-built vintage. The load path is a successor and needs
`werkzeuge/aufbereitung` first, and `0297` says so by name.

**Generalisation: before cutting into an unbuilt member, ask what its inputs are and
whether anything in the tree produces them.** If not, cut the half that computes and name
the half that loads. A package that needs a format nobody writes is blocked, not small.
This is the *input* question I already ask, applied one level up — to a whole member rather
than to a package.

## The evidence-in-`dateien` check paid for itself a third night, and this time before the cut

`0297`'s conditions all prove out in `daten/test/jahrgang_probe.cpp`, which is in its own
`dateien`. I wrote that into the `vermerk` explicitly. Two nights ago `0284` lost a
condition to exactly this and the reviewer handed the conflict to me by name. **Three
instances, three nights: it is a standing check now, not an incident.**

Second application in the same cut: `0286` runs tonight on `kern/include/kern/werte.hpp`
and will shift its lines, so `0297`'s acceptance names **symbols** (`Konstanten::pfadstand`,
`kern::werte::pfadstand`, `zustand::PFADINSTRUMENTE`) and no line number under `kern/`.

## The shared-clause soft lane again, and this time it is a *line-number* lane

`0292` writes six section-33 line numbers from `technik.md` into a C++ file. `0236` edits
T48, which sits **above** section 33; any insertion there moves `0292`'s numbers after it
greps them. Their `dateien` are disjoint and the collision rule would have run them
together. `0292` measured the mechanism itself under `0290` (+36 lines between two greps of
one run) and could not defend against it — re-grepping protects against stale numbers, not
against a second agent moving the file the same night. **Locked `0292` behind `0236`.**

Generalisation, sharper than last run's: **a package that writes a file and a package that
reads line numbers out of it are one lane**, even though only one of them writes.

## Five packages carried number 0293 — fourth collision in five nights

`weg-5a` keeps it (first written; the five files' mtimes give the order). `daten-md-head-count`
→ `0294`, `die-verteilung` → `0295`, `die-zwanzig` → `0296`. `drei-verweise` needed no
number: it asked to be folded in and I folded it into `0289` as condition 5. Old files
`fertig` with a pointer and **empty `dateien`/`haengt_an` so they claim no lane**, nothing
deleted.

**I have now written „one `Glob` over `aufgaben/` before you write a number" into the
successors four nights running and it keeps happening. Stop writing it.** It is a missing
mechanism, not proposer carelessness — a check in `baulauf.py` or a line in the proposing
roles' own files. That goes to the Geschäftsführer as a decision item, not to me again.

## A correction that was mine

`0285`'s acceptance made twenty rounds the floor; `PARTIELAENGE_HOECHSTENS` is 26
(`verlauf.hpp:208`). My threshold sat six rounds too low, and a builder who cut
`PARTIERUNDEN` to 20 would have passed it while killing a quarter of what the probe
measures. I took the number from the file's own head comment instead of measuring it at the
constant — the exact thing that file forbids four paragraphs above (`:32-37`). It is
`0296` now, and I wrote the failure into that package rather than only here. **Read the
constant, never the prose that describes it.**

## What I did worse than last run

**My `vermerk_annahme` fields are far over the 4,000-character package budget** — several
are 3–4 kB on their own, and I wrote nine of them. The evidence in them is load-bearing
(CLAUDE.md: never cut the evidence), but the framing around it is not: I restate the four
checks, the no-`Bash` line and the measure-at-the-text line in every single package.
**Those three are true of every package and belong in the role file or `lehren.md`, not
nine times in one run's output.** Next run: cut the boilerplate, keep the measurements.

Also: I read `befunde/uebersetzung-2026-09-10.md` **whole** — 688 lines — to learn four
test names. `Grep "FAILED"` with context would have cost a twentieth. The reading rule
covers `specs/` and `befunde/`; the nightly build report is just as big and I had no rule
for it. **Now I do: grep the build report, never read it.**

## Offene Fährten — 2026-09-10, 25th run

- **Check first next run: `0297`.** Its failure mode is a package that ships a `Jahrgang`
  type and a green probe **without the two bounds** — condition 5 is the whole point and
  the cheapest thing to skip. The tell: a silent clamp instead of a message naming country
  and series satisfies condition 4 and kills condition 5. Second tell: `instrument_min` /
  `instrument_max` appearing as fields of `Konstanten` rather than as arguments — that
  grows the carrier and the checksum, which `werte.hpp` excludes by name.
- **`0236` is return 1 of 3 and the repair is one clause in T48.** Do not let it widen into
  a second pass over section 36. Same discount that held for `0277`, `0284`, `0283`.
- **`0293` (weg-5a) is the one that travels.** Its result goes plan → Geschäftsführer →
  operator gate. Its failure mode is condition 2: filling Weg 5a with „could also" instead
  of deciding it.
- **Freed and deliberately uncut:** nothing. For the first time in four runs there is no
  free lane I chose not to fill.
- **For the Geschäftsführer — three items.** (1) **`daten` is cut, but only its computing
  half.** The loading half needs `werkzeuge/aufbereitung`, which needs frozen raw files
  that are not in the repo — that is a data-acquisition question and probably a gate, not a
  package. **It is the next thing that will stall.** (2) **The number collision needs a
  mechanism**, fourth night; four warnings in successor files have not worked. (3) **Series
  9 unchanged on the critical path**: `deckung_urteil = "reisst"`
  (`daten/reihen.toml:1256`); China still has no policy-rate route inside the vetted set.
- **`zahlwort_messung` is red and still nobody owns it** — `werkzeuge/zahlwort/messen.py`
  expects *„Zweiundzwanzig Groessen in dreiundzwanzig Deklarationen"* against a correct
  *„vierundzwanzig"* in `werte.hpp`. Refused to fold into `0286` again: `messen.py` should
  **derive** the number, and that is the Geschäftsführer's call.
- **Blocked, five, unchanged:** `0127`, `0208-baulauf`, `0194` (all `agents/baulauf.py` —
  operator's), `0003` (ADR), `0157` (re-checked: still the tool question, still no role
  that executes a program).
- **Uncut and named for the fifth run:** `technik.md:5473-5480`, Report 1 addressed to me —
  no check measures boundedness over 200 rounds. Still a sixth package on a lane that has
  five. **`0297` moves it closer**: once the vintage hands real levels into the round, the
  question stops being hypothetical.
- **Dormant:** clamp-first vs add-first deviation from `spiel.md`; `werte::schaden` →
  `schuld` for CN/BR.
- **Standing:** `RUECKLAUF_MAX` counts befunde rather than fault, fourteenth run.
- `.kopf.tmp` / `.paket.tmp` still carry `status: gebaut` — **thirtieth run in a row.**
  Subtract 2 from every `gebaut` count.
- **`high` was enough, thirty-ninth run.** The hard call — that `daten` was cuttable at all
  — turned on one `Glob` over `daten/` and six lines of `CMakeLists.txt`, not on depth.

