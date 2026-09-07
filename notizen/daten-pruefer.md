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

## Open

- **0207** (proposed 2026-09-07): the comment above `[datei.vorlagen]` counts commits over
  the history of `technik.md`. Those numbers rise on every commit to that file, while the
  nachziehpflicht of `datei.vorlagen.reihenliste` fires only on section 7 -- so the one
  mechanism that could notice the staleness is structurally blind, and no riegel can close
  it without a shell. Aged twice within 24 hours.
- **The belegstellen riegel has been unmeasured since 2026-09-06.** Its three numbers in
  `pruefweg.toml_geprueft` are being carried by every package on this file. Nobody can
  check them now. Watch whether someone quietly copies them forward.
