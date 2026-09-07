---
typ: pruefung
paket: 0185-standschwaeche-paketkennung-je-commit
pruefer: daten-pruefer
datum: 2026-09-07
urteil: zurueck
kriterium_geprueft: Condition 2 met -- 1956 lines, 420 comment lines and all sixteen patterns recounted against the working tree, reference state checked in .git/logs/HEAD. Condition 1 fails -- the counting half-sentence names five commits after ce59b8b; measured today there are seven.
befunde: 1
---

# Check of package 0185 -- the count over `technik.md` was carried forward, not remeasured

Checked is `daten/reihen.toml` in the working tree, identical with commit `daef750`
(`datenbauer: 0185-...`). The builder's logbook and report are not read; read are the
package, the file, `technik.md`, the packages 0051/0116/0117/0141/0154 and
`.git/logs/HEAD`.

**No shell this run**, so no `git log`. Everything below is measured with `Read`/`Grep`
on files that are in the tree, `.git/logs/HEAD` included. Where that is weaker than
`git log`, it is said so.

## Condition 2 -- the self-measurement: **met**

Recounted against the working tree, not taken from the field:

- Lines `1956`, comment lines `420` (`^` and `^#`). The field says 1938 → 1956 and
  403 → 420; the before-values are the ones the check of package 0170 recorded
  independently on 2026-09-06. Decomposition 6 + 11 + 1 = 18 = 1956 − 1938 holds.
- **All sixteen patterns, counted singly:** 6; 29 lines / 54 occurrences / 27 edge lines
  for `[']{3}`; 114 for `^\[\[`, by type 19 + 9 + 23 + 20 + 39 + 2 + 2 = 114, no eighth
  type; 19, 19, 19, 152, 20, 28; 21 and 28; 20 and 2. Every one is what the field says.
- **Reference state.** `b705e3f` is line 837 of `.git/logs/HEAD` and was `HEAD` when the
  run began. Blob `7911881` is the one the check of package 0170 measured for this file.
  The field names the missing `git hash-object` as its own weakness instead of hiding it.
- `datei.nachgezogen_durch` now has 16 entries, index 15 is this package; 1237 → 1238.
  No value of the vorlage table is touched.

## Condition 1 -- **not met**

The corrected half-sentence reads (lines 228-237):

> „Zwoelf haben technik.md geaendert und Abschnitt 7 nicht, fuenf davon nach ce59b8b.
> Alle fuenf sind benannt ... Zwei plus drei ergibt fuenf. Bis zum 2026-09-07 stand hier
> nur die zweite Haelfte; **die beiden Zahlen selbst waren und sind richtig**."

The five named commits are right, and their package attribution and times check out
against `.git/logs/HEAD`: `ce59b8b` 03:43:21, `a127600` 04:25:34, `9e46cfa` 05:51:37,
all three `architekt: 0051-t46-gebietspraefix-entscheiden` on 2026-09-05; `1f763e9`
= 0116, `565259c` = 0117, `95fb409` = 0141, and `technik.md` carries their sections 19,
20 and 21 at lines 3271, 3473 and 3836.

**But there are not five commits after `ce59b8b`. There are seven.** Two more landed on
2026-09-06, both after `95fb409`, both changing `technik.md`, neither touching section 7:

| Commit | `.git/logs/HEAD` | local time | what |
|---|---|---|---|
| `c3f6a8d` | line 738 | 2026-09-06 06:30:28 | `architekt: 0154-t60-sperrzahl-zwoelf-statt-dreizehn`; its `dateien` is `[technik.md]` alone, `status: fertig`. T60 sits at `technik.md:3648`, inside section 20 (3473-3836). |
| `7d4e8c8` | line 770 | 2026-09-06 11:14:34 | `uebersetzer: specs/.../technik.md#1. Stack`. Section 1 at `technik.md:89` is English today; section 7 at line 1448 is still German. |

Measured today the numbers are **21 / 7 / 14 / seven**, not nineteen / seven / twelve /
five. The half-sentence therefore covers five of seven -- the same defect the package
exists to remove, one commit class smaller. And the sentence written *today* claims the
numbers are still right.

The order was explicit: *"Nicht fortschreiben, sondern zaehlen ... am Verlauf neu zu
messen. Die Zahlen dieses Vorschlags sind ein Hinweis, kein Bezugsstand."* The "fuenf"
in the acceptance formula is such a hint, not a fact. This is not a false expectation in
the formula -- the binding sentence is "Beide Halbsaetze stimmen mit dem Verlauf
ueberein ... nachgemessen ... nicht behauptet", and it does not.

**How to produce the error.** Grep `.git/logs/HEAD` for `commit: architekt:` and for
`commit: uebersetzer:`; take the entries after line 719 (`95fb409`); read
`aufgaben/0154-...md` line 6 (`dateien: [.../technik.md]`) and `technik.md:89`. Then
count.

**It was measurable without a shell.** The field itself reads `.git/logs/HEAD` for the
reference state; the same file carries the answer.

**Under-count, not over-count.** I eliminated the other commits between lines 719 and
841 by role and file claim, not by `git log`. If one of them also touched `technik.md`,
the true number is higher than seven -- never five.

## What is not a finding

- **Formatting.** The ragged line 257 and the third weakness point staying third are
  style; `specs/` is silent, so the builder's choice stands.
- **The second weakness point itself is right.** It now names the condition under which
  the package identifier carries ("nur ... wenn sie aus verschiedenen Paketen stammen"),
  keeps "den ersten Fall faengt die Kennung ohnehin nicht", and backs it with the three
  0051 commits and their times -- all three confirmed above. Were it not for condition 1
  as a whole, this half is done.
- **Units, base years, gaps, licence.** No leaf value of any series is touched; no
  `faktor`, `basisjahr`, `t37_klasse`, `modelleinheit`, `lizenzbeleg`, `namensnennung`.
  Looked for, nothing found.
- **Reproducibility.** Every count above was run twice with the same pattern and gave the
  same number. The `[']{3}` occurrence list was compared line by line, not by total.
- **The belegstellen riegel.** Not runnable without a shell. Its three numbers in
  `pruefweg.toml_geprueft` are unchecked this run; said, not glossed over.

## Follow-up

The remeasurement fixes today and ages again with the next commit to `technik.md` -- it
already aged twice within one day. That is a separate question and has its own proposal:
`aufgaben/0207-standzaehlung-ueber-technikmd-ohne-messdatum.md`.
