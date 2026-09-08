---
typ: pruefung
paket: 0268-t7-regelsatz-klassifiziert-zwei-zeilen-des-heutigen-korpus-nicht
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: zurueck
kriterium_geprueft: Held T7 (technik.md:833-879) and section 33 against the package abnahme, with both corpus lines and the cited bezeichner_riegel mechanics re-read at HEAD.
befunde: 1
---

# What holds — checked, with evidence

- **Both lines re-read at HEAD.** `kern/src/schritt.cpp:405` is the literal
  `static_assert` recount, `kern/src/festkomma.cpp:90-91` the two-line
  `static_assert` with `"a*b sprengt i64 ..."` as message. Matches the package.
- **`festkomma.cpp:91` — named reading exception, compliant.** technik.md:860-870
  names a kind of text (string/character literal content), no line, no file. The
  cited evidence holds at HEAD: `bezeichner_riegel.cpp:222` (`im_block`), :228-233
  (literals move unread into the code part), :253-271 (both literal ends found).
- **Two separate answers, no tolerated-name list, no line-number exemption.**
- **Reference-quantity sentence present** (technik.md:872-879): the set the latch
  sees, not the 92-line mapping. Arithmetic consistent: 92−56+2−2=36 = 28+4+4
  by-kind; section 33 report 2 correctly notes 405 moves from the 28 to rule 5.
- **`add_test` consequence addressed**: green on day one, registration not
  deferred (:879) — the finding-branch clause of the abnahme is therefore moot.
- **Untouched scope**: rules 1-4 wording matches the package's own paraphrase;
  mapping table 92 lines/14 files and by-kind split intact (:899-916); plain-text
  table, `mal` paragraph, blind-spot paragraph, wrap exceptions unchanged.

# Finding 1 — rule 5 states no operand boundary, and its own two examples cannot both be derived

Rule 5 (technik.md:847-850): both operands are integer literals — alphabet
digits, `'`, whitespace, parentheses, `+ - *`, no identifier — and the `*` stands
in a `static_assert` condition. Section 33 (:5838-5840) adds: „A character outside
the operand alphabet is a finding", and `static_assert(4 * 3 / 2 == 6)` must NOT
match „because `/` is not in it".

Where an operand *ends* is stated nowhere. Reproduce the contradiction:

1. Build the check over the whole `static_assert` state (opens at
   `static_assert(`, closes at `;`, :5832-5836): line 405's region still contains
   `== 152, ""` after the reading rule — `=`, `,`, `"` are outside the alphabet →
   405 is a finding → the latch is red on day one, contradicting :877-879 („All 36
   match a rule, `schritt.cpp:405` under rule 5").
2. Build the operand as the maximal alphabet run around the `*`: in
   `4 * 3 / 2 == 6` the right run stops before `/`, leaving `3` — a pure literal →
   the line matches rule 5, contradicting :5839.

Every implementation falsifies one of the two normative sentences. The reading
that gets both right — the run ends at a comparison operator or the condition's
top-level comma, and any *other* non-alphabet character inside it is a finding —
requires a delimiter set (`==`, `,`) the document never names; `=` and `/` are
both merely „not in the alphabet", and nothing distinguishes them. The builder
would have to invent that distinction, which is what the abnahme exists to prevent
and what :5840 itself forbids („decided in this document, not by whoever writes
the line"). Repair is one sentence in rule 5 or its section-33 half: name the
delimiters that end the operand region, and keep everything else.

# Searched, nothing found

Interaction of the reading rule with rule 5's `;`-closure (message content gone
before the scan — holds); a `*` surviving in a dropped message (impossible, content
gone); rules 1-4 wording drift against the package paraphrase; mapping numbers
touched (none); a tolerated single name anywhere in the delta (none).

No proposal package: the repair is a return of 0268 itself, not new work.
