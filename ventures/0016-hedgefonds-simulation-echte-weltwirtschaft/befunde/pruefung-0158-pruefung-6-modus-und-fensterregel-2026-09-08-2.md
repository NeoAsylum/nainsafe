---
typ: pruefung
paket: 0158-pruefung-6-modus-und-fensterregel
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: Both acceptance conditions re-checked at today's line numbers in technik.md; run-1 finding (stale counts) verified fixed by grep and by summing the bounds table.
befunde: 0
---

# Pruefung 0158, run 2 (Ruecklauf 1) — geprueft

Run 1 (`pruefung-0158-pruefung-6-modus-und-fensterregel-2026-09-08.md`) returned the
package with one finding: the T30 passage said "seven bounds" and "101 addresses"
against a table that has held eight rows and 117 addresses since package 0172 added
bound 8. The Ruecklauf scope was two words. This run verifies the fix and re-checks
both conditions for regressions. All line numbers are of 2026-09-08.

## The run-1 finding is fixed

- `Grep` over the whole file for `seven bounds`, `101 addresses`, `sieben Schranken`:
  **0 hits**.
- `technik.md:2477` now reads "three of its **eight** bounds"; `:2489` reads "Of the
  **117** addresses of the eight bounds, **65 lie outside it**".
- Recounted the address column of the table `:2457-2466`:
  5+22+5+4+1+32+(12+20)+16 = **117** over eight rows. 65 = 1 (`markt.wert`, bound 5)
  + 32 (druck/gegendruck, bound 6) + 32 (fund shares + tiers, bound 7); 117 − 65 = 52
  inside the mask, including bound 8's 16 instrument levels. The passage closes
  against the table it points at.

## Condition 1 — the mode (holds)

The check-6 row `:2449` names the mode in the row itself: "200 rounds in mode
`weltlauf` (T38) — that is what „ohne Spieler" means, decided in section 28". The
losing reading is written beside it with its price (`:2484-2485`: unrunnable instead
of blind, tied to two unbuilt steps). Bounds 5/6/7 measuring only the start
assignment: `:2492-2496`. Where else they can break: `:2498-2504`, routed to report 1
of section 28 — confirmed present at `:5188-5195`.

## Condition 2 — the window rule (holds, unchanged from run 1)

Duty table `:2521-2524` gives both duties an origin and an owner: the freeze in the
one `daten` accessor via `min(t, R)` (data builder); the mark `ueber_fenster` derived
as `runde > R` (data builder forms it, break tester carries it into the check-6
finding). Window arithmetic `:2517-2519`: 25 … 200 = 176 of 200, divergence from the
source finding's 175 named, not hidden.

## Section 28 self-check reproduced

`grep -c 'ueber_fenster'` over `kern/`, `daten/`, `parameter.toml` = **0/0/0**. In
`technik.md` the word occurs at `:2516`, `:2524`, `:4964`, `:5212-5214` (the
self-check clause itself) — the rule exists only in the spec, as the section claims.

## What I looked for and did not find

Any remaining count carried from the pre-0172 source finding; a contradiction between
the check-6 passage and the T30 bounds table; a regression in the duty table or the
cross-references green in run 1. Per the Ruecklauf vermerk I did not recount the T38
mask split (175/135, 65-outside verified in run 1 and untouched by the two-word edit).
