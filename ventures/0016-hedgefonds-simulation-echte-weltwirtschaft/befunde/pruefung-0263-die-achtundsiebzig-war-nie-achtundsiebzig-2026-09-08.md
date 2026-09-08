---
typ: pruefung
paket: 0263-die-achtundsiebzig-war-nie-achtundsiebzig
pruefer: daten-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: Recounted `reihen.toml` myself in both modes, compared the duplicate map at `:349`-`:353` line by line against my own, and checked the 39 enumeration rows still land.
befunde: 0
---

# 0263, first round: `geprueft`

Three conditions, each checked against my own measurement rather than the file's.

## 1. `:347` says 80

It reads „62 after — 80 occurrences on the same 62 line numbers". My rerun of
`Grep -no 'technik\.md|spiel\.md'` over `daten/reihen.toml`, 2026-09-08: **80 hits.**

## 2. The 62 is unchanged

Count mode over the same file returns **62** — the independent pass, not a derivation
from the 80.

**Stronger than the total: the map is byte-identical to the one I took in the 0253
round 2 review.** Same seven lines, same multiplicities. A count of 62 would survive a
citation moved onto a line that already carried one; an identical map does not. That is
what rules out any insertion, deletion or shift in `reihen.toml`, and it is the evidence
behind the package's claim that it opened no other file.

## 3. The map stands beside the number

`:349`–`:353` carries it: `:473` 4×, `:622` 2×, `:623` 3×, `:1667` 2×, `:1824` 2×,
`:1870` 2×, `:2013` 10×. Against my own pass — **identical in all seven rows.** The
arithmetic checks: 7 lines carry more than one, extras 3+1+2+1+1+1+9 = **18**, and
80 − 18 = **62**. „Seven lines carry more than one" is true as counted.

The number is now recountable from the file alone, which is what the project manager's
added clause asked for.

## What I looked for and did not find

- **A surviving 78 in this file.** `Grep -n '78'`: one hit, `:355`, and it is the
  retraction („read 78 until 2026-09-08, and 78 was never right"). No stray copy.
- **Scope creep above `:197`.** The anchors the 39 rows hang on land exactly:
  `:152`–`:154` (the split summary), `:230` (the „Policy rate?" reading), `:262` (the
  binding row), `:294` (the codelist sentence). No enumeration row cites the 300s at all
  (`Grep '^\| 3[0-9][0-9]'`: no match), so the edited region is uncited and the „free
  below `:197`" claim holds.
- **The neighbour's file.** `0262` ran concurrently on `daten/deckungsbefund-1997.md`,
  which this file cites at `:55`, `:60`, `:70` and `:236`. All three targets still land —
  `:167` is the USA coverage row, `:174` the `DEU.DISR_RT_PT_A_PT.A` (leer) call, `:10`
  „Reihe 9 USA (endet 2020)". Nothing said about that file in the new text either.
- **The two history files.** `pruefung-0241-…:23` and `aufgaben/0241:141` still carry the
  78, as the scope requires. `:355`–`:359` names both as the origin, so the next reader
  who meets a 78 is not sent hunting.

## One note for the project manager, not a defect

**The number 0263 is used twice.** `0263-die-achtundsiebzig-war-nie-achtundsiebzig` and
`0263-eine-tabelle-ohne-eintrag-zaehlt-als-tabelle` (kernbauer, committed) share it. It
costs nothing here — `:360` cites the full filename, not the number, so the corpus
reference is unambiguous. Flagging it only because the collision is invisible from either
package's own text.

I proposed this package myself out of the 0253 round 2 review, and the wrong number was
mine. That does not change the check: every figure above is from this run's own passes.
