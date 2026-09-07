# Logbuch: datenbauer

Rotated by the runner on 2026-09-07 at 13147 characters (cap 12,000). Predecessor: `notizen/archiv/datenbauer-2026-09-07-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## Tools, since the shell went away

Since 2026-09-06 no role has `Bash`. What that leaves, measured on 2026-09-07 in
package 0185 against `daten/reihen.toml`:

- **`Grep` carries the whole self-measurement except three quantities.** Fifteen of the
  sixteen patterns run as `output_mode: count`; the sixteenth (the type enumeration
  behind `schnitt_3`) as seven separate counts. Line count is `^` in count mode, comment
  lines `^#`. Occurrences instead of lines: `-o` with `output_mode: content` — `count`
  mode counts lines even with `-o`.
- **Not measurable without a tool: the blob (`git hash-object`), the leaf-value balance
  (`tomllib`), and a run of the Belegstellenriegel.** Name them as underived instead of
  estimating; write into the field where every number came from.
- **`.git/logs/HEAD` is plain text and replaces half of `git log`.** Full commit id, unix
  time, and subject (`<rolle>: <paket>`) for every commit — so package attribution and
  the time to the second. **What it does not say: which files a commit touched.** The
  arithmetic checks out: 1788572601 +0200 is `ce59b8b`, 2026-09-05 03:43:21.
- `Read` refuses lines over ~25k tokens (`reihen.toml` line with `pruefweg.toml_geprueft`
  is one). `Grep -o` prints a match up to ~300 characters and omits longer ones — pull a
  long value in windows with `<anker>.{0,300}`.
- `imf.org` and `data.imf.org` answer the direct fetch with **HTTP 403**; `api.imf.org`
  answers. The page fetch truncates quotations at about 125 characters.

## Measure, don't assert

- **The enumeration carries the claim, not the sum.** Never assert uniqueness — write the
  list. The narrower uniqueness falls too.
- **A uniqueness claim is found by filtering, not by reading.**
- **Write every counting rule character-exact and measure it before it goes into the
  file.** `^sollreihen` finds 28, `^sollreihen = ` finds 21.
- **`grep -c` counts lines, `grep -o | wc -l` counts occurrences.** Count over names, not
  over hits — one name may carry its mark more than once.
- **Measure a line count after the last *comment* change,** not after the last leaf-value
  change — no counting pattern touches a comment line.
- **A quotation can raise a self-measurement, and so can a word.** Number words, not
  digits.
- **Whoever replaces a fallen claim writes it alongside as history,** with date and
  refutation.
- **A reviewer's proposal is re-measured like a source, including one's own work
  package.** Report, don't silently heal.
- **A reference without a line number has two parts: address and quotation** — and a
  quotation is only findable if it is character-identical, umlauts and quotation marks
  included.
- **"The same ones" is a quantity word and wants counting** (0170: three against four).
  Filter the two equated properties separately against *all* elements; the exclusive one
  carries the claim, the other stands beside it.

## A field that measures itself

- **Measure twice, before and after writing, and fetch *every* number again.** And `git
  diff HEAD`, not `git diff`: if the file is already staged, the second measures against
  the index (0170).
- **Whoever writes a number about the file into the file phrases the sentence so that it
  does not itself carry the counted pattern** — otherwise it never converges. In 0142 the
  way out was to write "denselben Abschnitt" instead of the digit.
- **A field that keeps its own balance can raise a count over the whole file without
  anyone touching the count** — that is how the 0065 count in `reihen.toml` moved from
  seven to eight through 0126.
- **An expression written into the measured file must be checked against itself** (0175).

## The Belegstellenriegel, without running it

- Call: `bau/werkzeuge/belegstellen/belegstellen_riegel <vorhabenwurzel> <vorgaben>`.
  0 green, 1 finding, 2 self-test broken.
- **Its keywords are countable:** `Abschnitt`, `Absatz`, `Ueberschrift` and the umlaut
  spelling; the word boundary is checked only on the **left**, so `Abschnitte` counts.
  `reihen.toml` holds 101 of them (2026-09-07). **A correction that leaves exactly as
  many occurrences as it found holds the four Riegel numbers fixed without starting the
  Riegel** — counted, not hoped.
- **A quotation needs three parts: keyword, then the heading in quotation marks, then a
  document name to its left.** A section number without a heading produces an
  *übergangene* Fundstelle, not a finding.
- **Condition 1 also hits `Kommentarzeilen 403`:** the pattern is Zeile(n) + blank + at
  least two digits, and it checks no word boundary to its left. A colon in between saves
  you. Same for `Z.` + digits.
- `aufgaben/` is exempt on the *citing* side; `UNGELESENE_ORDNER` (`bau`, `befunde`)
  only concerns the target side.

## File shapes

- **TOML: a bare key must come *before* all table headers.** Language rule, not tidiness.
- **In a TOML basic string, German quotation marks, accents and apostrophes are
  harmless**, straight double quotes and backslashes are not. A German wording can be
  taken over character-identically without changing the string form.
- **A new key in a file with balance fields collides with an acceptance criterion "zero
  changed lines outside the block".** Way out: name the superseded state in one's own
  block **and** write a proposal package.

## Reference state and foreign commits

- **The foreign intervention is the normal case.** Note the blob first, measure again
  afterwards, name the foreign state in the report — **and read your own report again
  afterwards.** On 2026-09-07 the runner rotated this logbook *during* the run, because a
  concurrent datenbauer run had pushed it over the cap.
- **The reference state belongs in the report as a commit id before the run starts.**
- **First measure whether the requested change is already there.**
- **Commit only your own paths.**

## Open leads

- **0185 is built.** Uncertain: the balance 1237 -> 1238 is carried forward from the
  review of package 0170 and not measured with `tomllib` myself; the field says so.
  Second, `datei.stand` still reads 2026-09-06 although the change is from 2026-09-07 —
  the package allows no third leaf value, named instead of smoothed over.
- **0170 and 0175 are built**; both carry an uncertainty named in their fields.
- **`einheitenbefund-pwt-baci.md` still carries `datum: 2026-09-02`** in its frontmatter
  although 0090 and 0126 changed it. Outside my assignment, reported.
- **The IMF full text decides 11 of the 27 target series and 7 of the 16 test subjects.**
  One single page fetch, on which four days and three roles have failed. Operator.
- **Series 3 (PWT capital stock) stays the only unmeasured source unit.** Depends on a
  readable extract from `pwt110_user_guide_to_data_files.pdf` or `pwt110.xlsx`
  (Dataverse 554025 or 554105) — named and reachable, only not readable (PDF lock).
- **The policy-rate path is my job, not the game designer's**: where the path for DEU and
  CHN comes from (DISR carries neither) and whether one consistent rate concept is
  reachable across four countries. **No package written yet.** The operator's
  re-measurement of 2026-09-05 moved DEU: eleven annual series in `MFS_IR`.
- **Contradiction No. 4 (factor 10,000 on the raw rate against T5 class 6)** — architect,
  still open.
- **Reading rule 3 in `reihen.toml` governs the factor-less block only for `ungemessen`.**
  Series 10 step 2 (`verkettung`) also carries no `faktor`. Reported.
- **The class-4 question** has stood in `parameter.toml` verbatim since 0035: does T5
  class 4 ("0 bis 10.000") carry its ceiling for a control as well? Five keys hang on it.
- **The 55 übergangene Fundstellen of the Riegel** are its written-out blind spot and
  nobody has looked at them. No package, no role, but it would be cheap.
- **An extra assignment to the data curator would be cheap:** take the ILO into the
  vetted sources, **including** the cut-off question ("produced prior to 3 May 2023" is
  indeterminate).
