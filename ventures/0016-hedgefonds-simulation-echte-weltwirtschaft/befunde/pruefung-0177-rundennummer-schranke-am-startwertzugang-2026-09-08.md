---
typ: pruefung
paket: 0177-rundennummer-schranke-am-startwertzugang
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: Both conditions replayed against technik.md, spiel.md, kern sources and bruch-2026-09-06.md; every load-bearing claim reproduced, 2 wording findings, neither touches a condition.
befunde: 2
---

# Pruefung 0177 — round-number bound at the start-value entry

## Condition 1 — met

**Answer "at both", with reasoning.** T18b (technik.md:1411–1432): the entry checks
the four `partie` addresses, bound `0 ≤ runde ≤ I64_MAX − 1`; `schritt`'s check stays
and covers a disjoint cause (incoming value vs. value the round makes). Derivation in
section 25 (:4698–4830): coordinate/operand cut with an applicability test (:4760–4762).

**Error-case reporter named.** :1430 "In the error case the entry reports", with
mechanism (reached first; can name provenance per T45; `schritt` names the address).

**Consequence for T30 check 3** at :4778–4809, replayed against sources:
- T22 (:1590–1596): the save is "vintage, mode, seed, action sequence and checksum,
  not the state", recomputed on load — so loading is indeed no state path.
- `aktionen: [[runde, aktion…]]` exists (:1592); "inadmissible save, not determinism
  break" repeats section 24's existing item 3 (:4654–4655) — no new rule invented.
- T45 counts provenance, not value (:19, :1728) — "only open way in" holds.

**Measured claims reproduced** (against the cited finding, not the builder's notes):
- `befunde/raender/bruch-2026-09-06.md`: situations 2/4 enter silently and die in
  `schritt` (:61, :106); situation 5 runs I64_MAX−1 through, situation 3 rejects the
  state it leaves (:107, :110–113) — both ends of the bound are measured.
- Address 307 in the abort messages (:75, :81); partie block = 4 addresses
  (technik.md:1484–1485).
- Code: `schreiber.cpp:206` (`welche_runde < 0`); `schritt.hpp:280` (negative +
  largest int64); `zustandsausgabe.cpp:206` prints *Partie | Runde* unchecked;
  `Startbelegung::setze` (zustand.cpp:904–935) has the foreign-write bar and a
  delegated index check — "third hard error" is accurate.
- Check 6: 200 steps past window, `ueber_fenster` (:2465–2469); check 2's eight
  bounds (:2441) — the not-`0…R` reasoning holds.
- `bricht_ab_mit` holds two text pieces per message (finding :240–241).

## Condition 2 — met

- Quote now whole, matched character-wise against spiel.md:405–407 including
  "— since 2026-09-05 —" and the parenthetical (technik.md:4572–4574).
- Fourth class referred to *What the fifth country and the exchange venues change*
  (:4577–4579; subsection at :4667).
- Old sentence gone: `own sentence` → 0 hits in technik.md; replacement splits
  attribution (kind-1 membership = sentence's, twenty places = T16's) (:4579–4581).
- T32b table row 1 untouched (:1569); size column still counts three blocks,
  consistent with the amended derivation.

## Findings — 2, wording only, neither reverses the verdict

**1. Section 25's measurement sentence is falsified by the package's own T18b.**
:4712–4713 claims "`partie.runde` does not occur in this document at all — … zero
hits before this section. Its bound stands twice in the core and nowhere in the
specs." Reproduce: `Grep -n "partie\.runde" technik.md` → :1420, :1426, both before
section 25; the bound now stands in the spec at :1420–1421. True when measured,
false since the same commit. One-clause fix (past tense / "before this package").

**2. T18b's pointer promises bounds that section 25 expressly declines.** :1422–1423
says "the bounds of the other three … are in section 25"; section 25 keeps them
deliberately open (:4772–4776) and report 3 (:4827–4830) tells the PM the three
addresses carry no bound. A reader sent for three bounds finds a refusal. One-clause
fix.

Both fit the pattern by which condition 2 reached this package: append to the next
package on `technik.md` (0196). Two clauses carry no own package.

## Searched, found nothing

spiel.md `partie.` dot-notation (0 hits — the block is English "game: …"); no
spiel.md passage demanding a check the entry cut forbids; T22's checksum-deviation
sentence vs. the new inadmissible-save rule — different failure modes, no clash.
