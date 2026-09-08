---
typ: pruefung
paket: 0268-t7-regelsatz-klassifiziert-zwei-zeilen-des-heutigen-korpus-nicht
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: Ran both normative examples through the amended rule-5 wording as an implementer would; both derive simultaneously from the stated delimiter set.
befunde: 0
---

# Review of 0268, ruecklauf 1 — the delimiter sentence

Second pass. The first (`pruefung-0268-...-2026-09-08.md`, `urteil: zurueck`) found one
defect: rule 5 named an operand alphabet but no boundary for the region it scans, and the
document's own two examples could not both be derived. The amended acceptance criterion
demands exactly that boundary, testable by simultaneous derivation of both examples. I
judged only the repair, plus a spot-check that nothing else moved.

## The repair, and where it stands

Rule 5, `technik.md:847-855`: the region is the run around the `*`, bounded by the nearest
delimiter — `==`, `!=`, or the top-level comma before the message — and otherwise by
`static_assert(` and its closing `)`. Any other alphabet-foreign character inside the run —
`/`, for instance — is *„a **finding**, not a boundary"* (`:852-853`). Section 33 carries
the derivation at `:5848-5865` and names the repair at `:5814-5817`.

## The probe: implement the classifier from the wording alone

1. **`schritt.cpp:405`** — re-read at HEAD this run:
   `static_assert(4 * (12 + 9 + 1) + 22 + 40 + 2 == 152, "T38: ...");`. Reading rule drops
   the string content, delimiters stay (`:865-875`). Region from the `*`: left bound
   `static_assert(`, right bound the nearest delimiter `==` → `4 * (12 + 9 + 1) + 22 + 40 + 2`.
   Every character is in the alphabet, no identifier, `*` in a `static_assert` condition →
   **rule 5 matches.** Consistent with the normative sentence at `:882-883` (all 36 match,
   405 under rule 5).
2. **`static_assert(4 * 3 / 2 == 6)`** — region by the same procedure: `4 * 3 / 2`. `/` is
   neither in the alphabet nor in the delimiter set → finding inside the run, **no rule-5
   match.** Consistent with `:5861-5862`.

Both first-pass implementations are now excluded by the text: whole-assert-as-region fails
because `==` ends the region before `152, ""`; maximal-alphabet-run fails because `/` may
not act as a boundary. The sentence that separates the `=` of `==` from the `/` — the one
the first pass found missing — stands at `:5854-5856`. I also tried the hostile reading of
*„Only these three end the region"* (excluding the assert's own parentheses as bounds):
both examples derive identically under it, since their left bound is the opening
parenthesis either way.

## Untouched-elsewhere spot-check

Section 33 claims *„Nothing else in this section or in T7 was touched"* (`:5816-5817`).
Checked against the first pass: rules 1-4 wording (`:841-846`) unchanged; reading rule with
its `bezeichner_riegel` anchors `:222`, `:228-233`, `:253-271` unchanged (`:865-875`,
`:5842-5846`, `:5871-5874`); reference quantity 92−56+2−2=36 and the `add_test`
consequence — green on day one, registered, not deferred — unchanged (`:877-884`); mapping
table header still 92 lines in 14 files (`:905`). Only `dateien:`-listed `technik.md` was
written.

## Not re-checked

Everything the first pass cleared and the repair did not touch: the two-answers structure,
the named-rule/named-reading form (no tolerated single names), the corpus verification of
`festkomma.cpp:90-91`. Evidence in the first finding.

Nothing found. The acceptance criterion, including the 2026-09-08 amendment, is met.
