---
typ: pruefung
paket: 0092-abschnitt-18-zwei-zaehlfehler
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: Section 18 laid line by line against my own grep of werte.hpp (condition 1) and the remainder count recounted in T48's table (condition 2); both match with no unnamed place left.
befunde: 0
---

# Pruefung 0092 — section 18's two counts, measured at the current tree

Judged against the two conditions in `aufgaben/0092-abschnitt-18-zwei-zaehlfehler.md`.
Measured at the working tree with HEAD `cd46bbf` (three commits after the builder's
`e5a8ce8`); `werte.hpp` is unmodified in `git status`, and my measurement reproduces the
builder's table exactly, so the drift since `e5a8ce8` is nil for these terms.

## Condition 1 — section 18 names the werte.hpp places completely: fulfilled

The condition's premise has moved: package `0152` carried the number over on 2026-09-06,
so `grep -c "siebzehn"` is **0** today, not 5. Section 18 point 1 (`technik.md:3772-3793`)
handles this by reporting both states, and both check out:

- **Historical:** five „siebzehn" lines (2, 16, 28, 33, 115) plus the derived ordinal
  („keine achtzehnte Groesse") — matches the enumeration the condition demands, place by
  place (header line, T48 rule in the head's wording, proof paragraph, `Konstanten`
  reasoning, block heading).
- **Current, the part I could measure:** I ran
  `Grep -n -i "siebzehn|zweiundzwanzig|dreiundzwanzig"` on
  `kern/include/kern/werte.hpp` myself. Result: `siebzehn` 0; `zweiundzwanzig`
  case-insensitive 7 lines — **2, 16, 29, 32, 41, 147, 185** — case-sensitive 6 (line 32
  opens its sentence with capital `Z`); `dreiundzwanzig` 2 lines — **32, 39**. That is
  line-for-line the table in section 18, including every „which" annotation (2 header,
  16 T48 rule, 29 „Unten stehen zweiundzwanzig", 41 `Konstanten` reasoning, 147 inside
  `struct Konstanten`, 185 block heading). **No line in my grep output is unnamed in the
  section.**
- The side claim checks too: `T48 Nr. 18`–`Nr. 22` declared at `werte.hpp:382, 406,
  425, 442, 478` — confirmed by `Grep -n "T48 Nr\."` (all 22 numbers present once;
  Nr. 11 twice for its two arities, which T48 prescribes).

Both readings of the condition are therefore met: the numbers are grep-confirmable *and*
the enumeration leaves no remainder.

## Condition 2 — the remainder count agrees three ways: fulfilled

- Section 18, condition 1 of 0043 (`technik.md:3728-3732`): **twenty-two**.
- T48 (`technik.md:2551`): „the **twenty-two names in the ten lines below**".
- The table itself (`technik.md:2555-2566`): ten data rows (2557-2566); counted name by
  name — 2 + 1 + 1(`stufen` once, two arities in one row) + 1 + 1 + 4 + 1 + 1 + 2 + 8
  = **22**. The 22 names match the package's own enumeration one for one.

No „twelve"/„zwoelf" survives anywhere in section 18 (full read, 3702-3810).

## What I looked for and did not find

- Leftover old count in the corrected section: none.
- A place in `werte.hpp` carrying the number that section 18's table omits: none (the
  union of all three greps is {2, 16, 29, 32, 39, 41, 147, 185}, all named).
- A mismatch between the section's citation `technik.md:2555-2566` and today's table
  position: none — the table sits exactly there at HEAD.
- Boundary violations: the correction note (`:3704-3708`) claims only this section's own
  report changed; T48's count sentence at 2551 is the pre-existing text the original
  finding already quoted, and 0043's four acceptance conditions are explicitly untouched.

The builder's note to the project manager — that the `werte.hpp` follow-up package is
already built by `0152` and needs no cut — is consistent with what I measured (0×
„siebzehn", declarations 18-22 present). That decision is the project manager's, not
part of this acceptance.
