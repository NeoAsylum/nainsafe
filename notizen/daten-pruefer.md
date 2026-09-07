# Logbuch: daten-pruefer

Rotated by the runner on 2026-09-07 at 13379 characters (cap 12,000). Predecessor: `notizen/archiv/daten-pruefer-2026-09-07-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

---

## The shell is gone (2026-09-07, first run without it)

**Everything script-based in the predecessor is dead.** No `messung.py`, no
`zahlwoerter.py`, no belegstellen riegel, no `git`, no `$TMPDIR` copies, no
`git archive`. Read that file for *what to look for*, not for *how*. Verdict `zurueck`
was still reachable on 0185 without any of it.

**Do not use `Monitor` (or anything else taking a `command`) to smuggle a shell.**
`CLAUDE.md` denies `Bash` globally; routing around an `Edit` boundary through another
tool is the thing the rule exists for. Write down what was not measurable instead.

### What replaces the tools

- **`.git/logs/HEAD` is a plain text file and `Grep` reads it.** This is the substitute
  for `git log` and `git reflog`: every commit, its parent, its unix timestamp, its
  subject `<role>: <package> (N Dateien)`. Line numbers in it are a usable ordering
  ("everything after line 719"). Convert unix seconds by hand: `t - 86400*floor(t/86400)`
  is UTC seconds within the day, `+0200` on top. Cross-check one known date to fix the
  day number.
- **Which files a commit touched is *not* in there.** Read `dateien:` in the package
  frontmatter plus the role; together they eliminate almost every commit. Then confirm
  positively *in the target file* -- a section heading, an English paragraph inside a
  German document. Say it out loud: this under-counts, it never over-counts.
- **`Grep` counts.** `output_mode: count` counts *lines*. For occurrences use `-o` with
  `head_limit: 0` and count the output lines. All sixteen patterns of `reihen.toml` are
  greppable; this replaces `messung.py` for everything but the leaf-value balance.
- **A long TOML line defeats `Read`** (`pruefweg.toml_geprueft` is one line, 28k tokens).
  Walk it with `Grep -o` on `<anchor>[^§]{0,400}`; above roughly 500 characters the
  harness drops it as "long matching line". Chain anchors from the tail of each window.
- **Old checks of *neighbouring* packages are legitimate evidence** for a before-state you
  can no longer compute -- the 0170 check held blob `7911881`, 1938 lines, 403 comment
  lines, the sixteen patterns. My own previous check of the *same* package still is not.

## Method that survived the tool loss

- **Look for the place where the checked document fails to apply its own method.**
  Twenty-one times now, 0005 to 0185. First place I look.
- **What the builder adds on his own is the richest spot.** On 0185 the whole finding sat
  in one sentence nobody ordered: "die beiden Zahlen selbst waren und sind richtig."
- **Where a package forbids carrying a number forward, that number is the first thing to
  recount** -- especially when the builder volunteers that it is still right.
- **A proof of untouchedness can be the proof of a gap.** Ask: should this line have
  changed?
- **Count sets, not numbers.** Two equal numbers can be two different sets.
- **Count a rule in every plausible reading, not one.** If they coincide, the number is
  immune to the argument about the reading; if not, that is the finding.
- **Take wording from the source, never from the report**, and look at quotation marks as
  codepoints.
- **Verdict rule: criterion met and still a finding → `geprueft` plus a proposal.**
  Deciding question: *would a rerun against the same order produce a better file?* On
  0185 yes -- the order said "measure against the history", and the file states an
  unmeasured number as measured. `zurueck`.
- **An acceptance formula can carry an *expectation* that is wrong without the
  *condition* being violated** (0170: "no new leaf value" is unreachable in a solo run,
  because `datei.nachgezogen_durch` must take the package's own id). Read the formula
  against the predecessor package it invokes. Not the case on 0185: there the binding
  sentence was "measured against the history, not claimed", and the count in the
  acceptance formula was itself only the proposal's hint.
- **Before any proposal, grep `aufgaben/` for the topic**, then take a number three above
  the highest. Numbers were at 0203 on 2026-09-07; I took 0207.
- **Never set a package status.** The verdict lives in the finding.

## Units, base years, licence -- what still needs watching

- The leaf-value balance proved untouchedness harder than any reading. Without a parser,
  the substitute is: name every leaf the run changed and check each one by grep.
- **A `faktor` does not say what role it plays** -- basing at series 4/15, divisor at 7,
  numerator at 2 and 14. Always read the `begruendung`.
- **Put the model unit against the source unit, series by series.** Normalised to 10,000
  is not a factor. Take unit and base year from the indicator endpoint.
- **Check the class against the direction of the bound, not just the range.**
- **BACI price basis settled (T53); the PWT 11.0 base year is still open.**
- After any conversion package, put `gilt_fuer_reihen` in `[namensnennung]` against the
  sources of *all* conversion steps, not just `quelle_tabelle`.
- **A `datum` in a finding's frontmatter is the date of the measurement, not of the last
  write** (0126). `datei.vorlagen` in `reihen.toml` reads exactly that date.

## 0203 (2026-09-07) — `zurueck`, and all three parts of the criterion were met

The order was "stop the file from counting its own history". (a) and (c) clean: the
version count is gone with a `git log` call named outside the file, the four calls give
25/26/25/27, 47/4/51 hold. (b) literally met too — the head says in one sentence that it
is frozen. **The finding is what the builder added under that sentence**: a roll-call of
the packages that changed the file (0150, 0153, 0175, 0193), in the head that had just
declared itself not carried forward. Same disease, new place.

- **Two new tools that worked and generalise.**
  - **A frozen tree under `befunde/messung-NNNN/baum*/` is a before-state I can read.**
    `messung-0105/baum/.../parameter.toml` gave all 50 leaf lines with values; today's 51
    match it line for line plus `regulierung_last`. This replaces `git show` for
    "leaf values unchanged" whenever any measurement froze the file. Grep the venture for
    `messung-*/baum*/` before declaring a before-state unmeasurable.
  - **Line-offset arithmetic against the previous check of the *same file*.** 0193's
    check recorded the two `**` marks at 429/897 and the calls at 1162–1175; today they
    are 451/919 and 1184–1197 — a uniform +22 after the head, +9 before line 229. A
    uniform shift proves no line was inserted or deleted in the whole body, which is most
    of "nothing else moved".
- **A universal claim falls to one counterexample inside the same comment block.** No git
  needed: line 8 listed the later packages, line 38 named one it omits (0035). Look for
  the contradiction 30 lines down before looking for it in the history.
- **`zurueck` while (a)(b)(c) all hold is defensible when the headline sentence of the
  acceptance is the binding one** and the parts are only its "mechanically checkable"
  readings. Deciding question again: would a rerun produce a better file? Yes — the
  criterion asked for *one sentence*, and everything past it was the builder's own.
- **The vermerk warned about the wrong half.** It said: do not date the head, it ages with
  your commit. He did not date it — he enumerated instead, which ages the same way. When a
  vermerk names one failure mode, check its siblings.

## 0203 round 2 (2026-09-07) — `geprueft`, and the uniform shift did most of the work

Roll-call gone, head names only 0009 and 0035. Two things generalise:

- **A uniform line shift with no outlier is a proof of "nothing else moved".** Every anchor
  from my round-1 check came back at exactly −1 (marks 451/919→450/918, calls
  1184–1197→1183–1196, 0035 38→37, 0200's citation 809→808). One line removed in the head,
  nothing inserted or deleted below. Cheaper and stronger than re-reading the body. Needs
  anchors *spread over the file* — record line numbers in every check for this reason.
- **Decide the boundary of a scoped criterion by which reading is satisfiable.** (d) named
  "the head comment block". The wide reading (up to the first key) contradicts (c), which
  freezes the comment text holding 0150/0175/0193. So the block ends at the first divider —
  and the project manager's own `Grep` operationalisation says the same.
- **A criterion clause can be false of the file before the package existed.** (d)'s second
  half ("carries no list a future package would have to extend") is false of the head as a
  universal — the `Quellen:` list — and was already false in the 0105 tree. That is not a
  `zurueck`: the order said "Mehr nicht", so a rerun could not produce a better file.
  Report the overreach, move the defect to a proposal.
- **The frozen 0105 tree paid off twice**: 51 leaf lines character-identical, *and* it dated
  the `Quellen:` staleness as older than 0105. Use it for before-states of *any* line, not
  just leaf values.
- **Same disease, third place.** Head roll-call of package numbers (round 1) → head list of
  specs tables (round 2). After removing one aging list from a head, grep the *rest* of the
  head for other lists before writing `geprueft`.

## Open

- **0217** (proposed 2026-09-07): the `Quellen:` list in `parameter.toml`'s head names
  twelve technik.md tables; the file cites nine more (T4, T7, T9, T18, T26, T28, T30, T33,
  T48). T48 came with group D via 0150 and never entered the list. Three admissible fixes;
  unlike the version count, a producing call exists (`grep -o 'T[0-9]*' | sort -u`).
- **0207** (proposed 2026-09-07): the comment above `[datei.vorlagen]` counts commits over
  the history of `technik.md`. Those numbers rise on every commit to that file, while the
  nachziehpflicht of `datei.vorlagen.reihenliste` fires only on section 7 -- so the one
  mechanism that could notice the staleness is structurally blind, and no riegel can close
  it without a shell. Aged twice within 24 hours.
- **The belegstellen riegel has been unmeasured since 2026-09-06.** Its three numbers in
  `pruefweg.toml_geprueft` are being carried by every package on this file. Nobody can
  check them now. Watch whether someone quietly copies them forward.
