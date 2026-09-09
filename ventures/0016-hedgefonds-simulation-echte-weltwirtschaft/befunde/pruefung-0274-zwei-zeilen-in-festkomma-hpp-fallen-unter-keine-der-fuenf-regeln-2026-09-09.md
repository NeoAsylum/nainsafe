---
typ: pruefung
paket: 0274-zwei-zeilen-in-festkomma-hpp-fallen-unter-keine-der-fuenf-regeln
pruefer: entwurf-pruefer
datum: 2026-09-09
urteil: geprueft
kriterium_geprueft: "die fuenf Bedingungen einzeln am Text von T7 und Abschnitt 35 bei HEAD nachgezogen; Regel 4 aus der Wortlaut-Vorschrift nachgebaut und gegen vier Korpuszeilen und drei feindliche Faelle gerechnet"
befunde: 2
---

# 0274 — geprueft

Both findings below fall **outside** the five conditions and are no reason to send the
package back. They are named because they are wrong numbers in a specification.

## The five conditions

| # | Where at HEAD | Result |
|---|---|---|
| 1 | T7 `:882-888` | met — the paragraph states the count only (*„42 Vorkommen in 36 Zeilen"*, 23 files); `:890` says 35 of 36, `:902` says red today. „green on its first day" survives only at `:5871` and is expressly overtaken by the dated note `:5863-5866`. |
| 2 | T7 `:890-900` | met — both lines with full path; `:356` under widened rule 4, `:99` under none, each with its reason. |
| 3 | T7 `:847-851`, sec. 35 `:6171-6205` | met — probe below. |
| 4 | T7 `:941-942` | met — *„these four sorts sort the **mapping**, not the rule set, the same warning section 33 report 2 gives for the 28"*. |
| 5 | the latch | met — untouched: `REGELNAMEN[3]` still reads *„Regel 4 static_cast<i128> auf beiden Seiten"* (`:842`), `traegt_i128_umdeutung` still `find(...) != npos` (`:626`), the head comment still cites T7 `:841-857` and `:904-921`. |

## Condition 3 — the probe

The hard half is *„does not admit `i64 * i64`"*. I implemented the rule from its wording
alone — operand run beside the `*`, strip enclosing parentheses that are not a call's
argument list, head must be `static_cast<i128>`, run carries no `?` — and ran the corpus
and the hostile cases through it:

- `:161`, `:292` — run is the cast expression, head matches on both sides.
- `:356` — left run `(static_cast<i128>(n) - 1)`, its `(` preceded by `(`, strips, head is
  the cast. Matches.
- `:99` `az - ganz * an` — left run is `ganz`. No match, as the section says.
- `static_cast<i128>(a) - b * c` — **the case that would admit `i64 * i64`.** It does not:
  the left run is `b`, because `linker_operand` (`multiplikationsriegel.cpp:446-488`) walks
  left over words, `(…)`/`[…]` groups, `<…>` before a group and `::`, and breaks at
  everything else — the `-` ends the run. „Operand run" is an implemented term of the latch
  this package's successor extends, not one the package invents.
- `(static_cast<i128>(a) > 0 ? x : y) * b` — head is the cast after stripping; only the `?`
  clause rejects it. That clause is load-bearing.

## Finding 1 — the quoted name count is one off

Section 35 `:6167` says the latch *„built **84** layout-constant and 7 `u64` names"* and
cites `befunde/uebersetzung-2026-09-09.md`. That report reads at `:193-194`: *„23 Dateien
gelesen, **85** Namen in der Liste der Layoutkonstanten, 7 in der der u64-Konstanten"*. 84
is the figure of `uebersetzung-2026-09-08.md:164`. The rest of the paragraph holds against
the 09-09 report: 29/29 failed (`:179`), 2 places (`:189`), 9 and 23 self-test cases
(`:191`), 42 in 36 (`:195`).

## Finding 2 — `zustand.hpp:777` is `:797` today

Section 35 `:6201-6203` measures *„2026-09-09"* and names `zustand.hpp:777` for
`nummer < LAENDER ? nummer * LAND_FELDER : BASIS_RESTWELT`. Wording and count are right —
`Grep` for `?` over `kern/include` and `kern/src` gives that line as the only one carrying
a `*` as well — but at HEAD it stands at **`:797`**; `:777` is
`if (nummer < 1 || nummer > SEKTOREN) {`. The number is inherited from the plain-text-latch
table T7 `:925`, which the section expressly leaves standing, so T7 now carries it twice.

**Cheapest repair, and not a package:** one sentence in the `abnahme` of `0276` —
architect, `offen`, same file, already hanging on `0274`.

## Report to the project manager

Section 35 `:6247-6249` names two successors; neither exists as a file. I wrote the latch
one as **`0289`** (`vorschlag`), because condition 5 assigns it and the nightly build stays
red at a line T7 now covers. The `kern/` one — `az - ganz * an` → `az % an` at
`festkomma.hpp:99`, derived at `:6225-6232` — I did not write: two lines for the kernbauer,
and its acceptance already stands in the section.
