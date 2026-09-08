---
typ: pruefung
paket: 0158-pruefung-6-modus-und-fensterregel
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: zurueck
kriterium_geprueft: Both acceptance conditions checked at today's line numbers against T30, T38, sections 7/10/28, plus grep-counts over kern/, daten/ and parameter.toml.
befunde: 1
---

# Review 0158 — run 1

Line numbers are as of 2026-09-08; the translator shifts them, anchor on the quoted
wording.

## Finding 1 — the delivered passage contradicts the bounds table it points at (condition 1)

Reproduce:

1. `Grep -n "seven bounds"` in `technik.md` → one hit, `:2477`: "Check 6 runs in mode
   `weltlauf`, and that decides three of its **seven** bounds away."
2. Twelve lines later, `:2489`: "Of the **101** addresses of the **eight** bounds, 65 lie
   outside it."
3. Sum the address column of the bounds table under "The eight value-range bounds that
   check 2 checks every round" (`:2457-2466`): 5+22+5+4+1+32+(12+20)+16 = **117**, eight
   rows. 101 is the sum of bounds 1–7 only.

Both counts are carried over from the source finding
(`befunde/beschraenktheit/bruch-2026-09-06.md`: "101 Adressen der sieben
Wertebereichsschranken"), which predates bound 8 — added by Paket 0172, section 23
(`:4636`), which entered the file before 0158 in the queue. So the passage says "seven
bounds" and "eight bounds" within twelve lines, and its reconciliation does not close
against the table 20 lines above. A reader who recounts cannot tell whether 65 is stale
too.

**What is not stale — verified, so the Ruecklauf changes nothing else:** 65 = 1 + 32 + 32
is correct. Per T38's mask table (`:1476-1490`): market basket (2, incl. `markt.wert`),
instruments without level (48, incl. the 32 druck/gegendruck) and fund (52, incl. the
12+20 of bound 7) are outside the `weltlauf` mask; bound 8's 16 addresses are the
instrument levels, block "instrument level (4)" × 4 countries, **inside** the mask
(`:1478`). Exactly three bounds blind. Correct counts: eight bounds, 117 addresses, 65
outside.

## Condition 1 otherwise — checked, holds

- Mode named in the T30 check-6 row itself (`:2449`): "200 rounds in mode `weltlauf`
  (T38)", with the decision reference to section 28. Losing reading beside it with its
  price (`:2484-2485`).
- Blindness stated at T30: bounds 5/6/7 measure only the start assignment (`:2492-2496`);
  the "why not cosmetics" attributions match the table rows.
- Where else they can break (`:2498-2504`): check 2 runs every round of every run; 5/6/7
  break in spielmodus runs (checks 1, 4, 5, 7); the 200-round gap is named and routed to
  the PM as report 1 (section 28, `:5188-5195`), not silently closed.

## Condition 2 — checked, holds

Table `:2521-2524` gives both duties an origin and an owner, mirroring the Responsible
column of the T30 duty table: the freeze arises in `daten`, in the one path accessor, as
`min(t, R)`, owner data builder; the mark `ueber_fenster` is derived (`runde > R`), data
builder forms it, break tester carries it into check 6's finding. Window arithmetic
25…200 = 176 is self-consistent with freeze-from-R+1 and `runde > R`; the divergence from
the finding's 175 is named in the text (`:2519`), not hidden.

## Cross-references and committed checks — reproduced

- "section 7, point 1" for druck solely via action 3: `:1641`, inside point 1 (point 2
  begins `:1647`); druck start value 0 confirmed `:1633`.
- "counting table in section 10" for gegendruck from step 5: `:2928`, `:2938`.
- "R arises on loading the vintage per T40": T40 heading `:884` says exactly that.
- Section 28's own check: `grep -c 'ueber_fenster'` over `kern/`, `daten/`,
  `parameter.toml` → 0, 0, 0 today. Word count in `technik.md` before the run = 2 (old
  T30 line + `:4964` from 0177) matches section 28's claim.

## Why zurueck and not geprueft-with-a-note

Condition 1 demands the blindness statement stand at T30. The statement as delivered
carries two counts that contradict each other and the table above them — the exact
plausible-wrong-number failure this factory has paid for before. The fix is two words
(`seven` → `eight` at `:2477`, `101` → `117` at `:2489`); a Ruecklauf is cheaper than a
proposal package.
