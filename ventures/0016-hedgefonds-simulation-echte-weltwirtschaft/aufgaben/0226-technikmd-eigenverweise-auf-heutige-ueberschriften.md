---
id: 0226-technikmd-eigenverweise-auf-heutige-ueberschriften
rolle: architekt
status: offen
haengt_an: [0181-vorspann-nummernbereich-und-freie-nummer]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: "(1) `Grep \"Die Grenze des Orakels\"` over `specs/` returns no hit at all -- `spiel.md` is already clean, so the last one is `technik.md:1801`, and its replacement names a wording that a `Grep` finds on a heading or bold-lead line of the file it points into. (2) The Meldung carries the sweep as a table, one row per internal section reference in `technik.md`: line, quoted target, and the line it resolves to -- plus, for every reference that did NOT resolve, either the repair as old wording -> new wording, or a per-site reason for leaving it. (3) The sweep names the five calls it used so the reviewer repeats them instead of re-searching; the bold form `**...**` is run as a required call, not as an extra. (4) No heading is renamed and no reference is deleted to reach resolution. (5) Counts reproduce: the Meldung names what it counts (citing entries, not targets) and any number it states can be re-derived from a named call. No condition needs a shell, a build, or the next nightly report."
vermerk: "CUT 2026-09-08, project manager. Carried by me since 2026-09-07 as a one-line defect and released as a sweep, because one line is a fix and the sweep is the measurement. || THE SITE IS VERIFIED, not inherited: `Grep \"Die Grenze des Orakels\"` over `specs/` on 2026-09-08 returns exactly one hit, `technik.md:1801` -- 'exactly the four that `spiel.md` enumerates under „Die Grenze des Orakels\"'. That heading no longer exists anywhere; `spiel.md:2835` carries '**And the limit of the oracle, explicitly.**' since the translation. It stood at :1802 on 2026-09-07 and moved one line when the Vorspann was translated, which is itself the argument for resolving against the file and never against a line number. || YOU ARE LAST ON PURPOSE, and it is the same reason 0189 stands last on `belegstellen_riegel.cpp`: a sweep is measured against a stand, and every package that touches the file after it lets the measurement decay. Thirteen open packages sit in one line on `technik.md` ahead of you (0208-schritt -> 0165 -> 0172 -> 0148 -> 0177 -> 0196 -> 0158 -> 0149 -> 0064 -> 0068 -> 0074 -> 0084 -> 0092 -> 0181), 0221 branches off 0172, and several of them rewrite the very headings you will be resolving against. `haengt_an` names 0181, the deepest of them, so the order holds by dependency and not by how your number happens to sort. || USE 0224'S METHOD, DO NOT REINVENT IT. Its builder swept `spiel.md` on 2026-09-07 with four calls and found the fifth himself: `^#{1,6} ` for the heading roster; single-line italics; the SAME italics pattern with `\\n[^*]{0,60}` before the closing `*` and `multiline: true`, which caught 8 of 18 repairs and is invisible to the plain call; `„` for German quotation references; and `[^\\n*]\\*\\*[A-ZÄÖÜ][^*\\n]{10,70}\\*\\*` with `-o` for the bold form, which was NOT in that package's acceptance and turned up three more dead references (:24, :51, :302). That is a measured finding and I carry it into your acceptance as a required call. Take `[„\"]` into the character class after the opening `*` -- its absence cost 0224 a Ruecklauf with three misses. || FIVE TARGETS IN spiel.md WERE BOLD PSEUDO-HEADINGS, not `#` headings, including the one 0224's own acceptance named. A sweep that resolves only against `^#` reports false breaks. Expect the same in `technik.md`, whose 21 numbered headings are `##`. || WHY THIS FILE HAS NEVER HAD THE SWEEP: `belegstellen_riegel` scans code and toml, never specification prose. 0222 repaired this defect class in the riegel's scan set and is `fertig`; 0224 did `spiel.md`. `technik.md` is the third document and the only one still unswept -- and all 21 of its numbered headings still stand German while their bodies read English, so the count of citations that a later rename would break is not a forecast but a quantity sitting in the file. Report what you find; renaming is not your package. || SCOPE: references only. No rule, no formula, no count, no heading. Anything you find that is content rather than citation -- a claim that is wrong rather than a pointer that is dead -- you report in the Meldung and do not touch, the way 0224's builder correctly reported this very line instead of reaching into a file outside his `dateien`."
---

# technik.md's own section references have never been swept

`spiel.md` got this sweep on 2026-09-07 as package `0224`; the riegel's scan set of code
and toml got it as `0222`, now `fertig`. `technik.md` is the third specification document
and the only one where no reference has ever been resolved against the file.

## The evidence, measured 2026-09-08

- `technik.md:1801` cites „Die Grenze des Orakels". `Grep` over `specs/` finds that
  wording on exactly one line -- this one. It is not a heading anywhere.
- The section it means is `spiel.md:2835`, `**And the limit of the oracle, explicitly.**`
- On 2026-09-07 the same defect stood at `technik.md:1802`. One line of drift in one day,
  from the Vorspann translation alone.

## Why it is a sweep and not a one-line fix

`0224` set out to repair one line of `spiel.md` and found **107 internal references, 18 of
them dead**. Three more were dead in a form its acceptance had not named. The single line
that started it was 1 of 21. There is no reason to expect `technik.md` to be different,
and one reason to expect it to be worse: its 21 numbered headings are still German under
English bodies, so every citation into them is a citation into a heading that has already
been marked for renaming.

## What is known to be outside this package

`daten/reihen.toml` carries three paraphrase citations of `spiel.md` that the riegel
cannot see; they are the project manager's carry and belong to a Datenbauer, not here.
The renaming of the 21 headings is the operator's open decision in `ops/plan.md`.
