---
typ: pruefung
paket: 0223-realeinkommen-abschnitt-zwei-textstellen
pruefer: entwurf-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: both acceptance conditions checked by the named calls — the T38 quote grep hits technik.md:1379 inside the T38 block, and the repaired cancellation sentence carries the bounds premise that the counterexample 9.990 → +50 → −50 → 9.950 fails
befunde: 0
---

# Pruefung 0223 — two sentences in *Das Realeinkommen in Gegenkraft 2*

## Condition 1 — the T38 quote matches technik.md today

Call: `Grep -n "only approval and change of government"` over `specs/0016-…/`.

Hits: spiel.md:2432 (the site under review), technik.md:1379, plus spiel.md:2151 and
spiel.md:2719 (other sites, same current wording, outside this package).

- spiel.md:2432 quotes „of step 5 only approval and change of government run"
  (technik.md:1379).
- technik.md:1379 reads: "dropped, of step 5 only approval and change of government run,
  and in step 3 the policy" — the quoted words are a contiguous substring on that one
  line.
- Line 1379 lies inside the T38 block: `Grep -n "T38"` puts the heading **T38 — The mode
  is a property of the run…** at technik.md:1341; the next rule heading (T19) starts at
  1385, so the paragraph 1378–1383 is T38's. The line reference `(technik.md:1379)` in
  the quote is today's line.

Condition 1 is met.

## Condition 2 — the cancellation sentence carries its bounds premise

Read spiel.md:2372-2383. The sentence now states: the two rounds cancel exactly if
quantity and `bip` are unchanged "**and neither round is clamped, that is: the unclamped
sum inside the update lies within `0…10.000` both times**", and it carries the
counterexample with its numbers.

Checked against the update rule at spiel.md:2298-2302:
`zustimmung_neu = min(10.000, max(0, lies_alt(zustimmung) + mal_geteilt(elastizitaet,
hub, 10.000)))` — so "unclamped sum inside the update" names exactly the argument of
`max(0, …)`/`min(10.000, …)`, and `0…10.000` is exactly the clamp pair.

Counterexample against the stated premise, step by step: start 9.990,
`zustimmung_elastizitaet` 10.000, budget step down → hub +50 (per the probe at
spiel.md:2362-2364, a 50-bp budget step gives |hub| = 50 at elastizitaet 10.000) →
unclamped sum 9.990 + 50 = **10.040**, outside `0…10.000` → first round is clamped →
the premise "both times inside" is violated → the sentence no longer claims
cancellation for this path. (The path indeed does not cancel: clamp to 10.000, then
−50 → 9.950 ≠ 9.990.) A test encoded from the sentence as written now asserts nothing
about clamped paths.

Condition 2 is met.

## What else I looked at, without finding

- The premise wording does not contradict the rule: it restates the clamp construction
  of spiel.md:2298-2302, no formula, count, or read-access number changed (spot-checked
  the four formulas block 2297-2303 and the read-access paragraph 2397-2402 for edits —
  untouched).
- The other two sites quoting T38's sentence (spiel.md:2151, 2719) already carry today's
  English wording; nothing left stale by this fix.
- Scope check: package `dateien` lists only spiel.md; both edits sit in the named lines
  2372-2383 and 2430-2432.

0 findings.
