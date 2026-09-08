---
typ: pruefung
paket: 0148-zielkennung-je-aktionsart
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: all three abnahme conditions replayed against spiel.md, technik.md and the built core; every load-bearing line number, constant and quote reproduced
befunde: 3
---

# Pruefung 0148 — T32b, the target id per action kind

## How each condition was checked

**Condition 1 — five lines, each set + T9 order + derivation.** T32b table at
technik.md:1544–1550, derivations in section 24 (:4547–4574). Order claims replayed
against the build: `zustand.hpp:319,402–403` give sectors 0–11, currency from 12, bond
from 16 — exactly row 1's formula; `zustand.hpp:932–943` aborts stakes for non-playable
countries and computes country-major — row 2; the fund block carries exactly one address
each for leverage and visibility (`zustand.hpp:225,253–254`) — rows 4/5. T16
(technik.md:1258–1266) matches consequence bullet 2 verbatim (20 addresses, 19 playable).

**Condition 2 — a kind without a target has a line.** Rows 4 and 5 name the one-element
set and place 0; the bullet "carries 0, not any value" binds it to the checksum via
T22/T12. Met.

**Condition 3 — the Art-5 contradiction.** Resolved, not merely named. The three cited
passages reproduce at the stated lines (spiel.md:463, 1518, 1640); both negative counts
re-run case-insensitively (findings 2–3) confirm: no computation rule in spiel.md reads
visibility per instrument or per slot. The leftover half-sentence (spiel.md:421) is
reported to the game designer; section 12 point 4 is struck and settled
(technik.md:3019–3028). Domain-not-in-type evidence reproduces: `aktion.hpp:155,162,299,308`
(rank proof at `ZIELKENNUNG_MAX` = 65535), `aktion_probe.cpp:189` is
`{Art::Sichtbarkeit, Zielkennung{2}, 1}` as stated.

## Findings — all accuracy, none breaks a condition

1. **The line-1 derivation truncates its quote.** spiel.md:405–407 lists a *fourth*
   target class in the same sentence: "or — since 2026-09-05 — on an **exchange
   venue**". "T16 turns exactly those into twenty fixed slots" (technik.md:4551) holds
   only for the truncated quote; "not my reading but spiel.md's own sentence" (:4552)
   overstates — the full sentence buys a larger set than row 1 names. The venue
   subsection (:4650–4654) handles the gap correctly (fourth block behind bonds,
   schema_version rule), so the table row stands; the derivation should quote whole and
   point there. Wording edit, not a build.
2. **"the word *visibility* stands on ten lines" (:4598) is a case-sensitive count.**
   Case-insensitive it is twelve — capitalized `Visibility` at spiel.md:420 and 427 are
   missed. 420 is handled by the paragraph's second search; 427 is commentary, no
   computation rule. Conclusion unchanged.
3. **"three hits" for disclos·/Offenlegung/public pressure (:4603) is four**
   case-insensitively; the missed line 421 is the contradiction sentence itself.
   Conclusion unchanged.

## Searched, without result

A computation rule reading visibility per instrument/slot (both vocabularies, `-i`,
whole file); a German `Sichtbarkeit` line the English count could have missed (zero —
all visibility lines are English); a rest-of-world stake or instrument block
(`zustand.hpp:938` aborts); a second order beside the state's (every `Zielkennung`
mention in technik.md sits in T32/T32b/section 24).

Judged geprueft because the findings are count/quote accuracy in derivation prose,
repairable as text edits without touching the table or the resolution — same
materiality class as pruefung-0224 run 2. If the PM weighs finding 1 heavier, the
reasoning is above.
