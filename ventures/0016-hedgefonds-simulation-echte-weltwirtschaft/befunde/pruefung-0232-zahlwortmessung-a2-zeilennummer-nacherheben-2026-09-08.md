---
typ: pruefung
paket: 0232-zahlwortmessung-a2-zeilennummer-nacherheben
pruefer: test-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: Green zahlwort_messung entries on both build paths in uebersetzung-2026-09-08.md, plus source proof that rc 0 forces exactly the A2 block condition 2 demands; the five wordings and line 185 re-measured at the tree.
befunde: 1
---

# Condition 1 — met, receipt in the report

`uebersetzung-2026-09-08.md`: root `26/26 Test #26: zahlwort_messung ... Passed 18.53 sec`
(:168), standalone `3/3 Test #3: zahlwort_messung ... Passed 18.66 sec` (:482).
`werkzeuge/zahlwort/CMakeLists.txt:142-155` has no result-shaping (no
`PASS_REGULAR_EXPRESSION`, no `WILL_FAIL`), so Passed ⇔ rc 0. TIMEOUT 600 vs ~18.6 s
measured — no risk. The report's headline `fehler` and root ctest Code 8 (:80) are
`belegstellen_kopfzahlen` (B1 lines :126/:139) — the known 0227 matter, not this package.

The green run measured the delivered script, not a leftover: the old expectation
(literal `157`) cannot pass a tree whose claim sits at `werte.hpp:185` — exactly that
was red on both paths in the morning run the package cites. Same tree, now green ⇒ the
derivation ran. `messen.py` is in no other package's `dateien`; nobody claims `werte.hpp`.

# Condition 2 — property met and proven; receipt clause is the finding

The A2 block does **not** appear in the report — see finding 1. The property it names is
proven from source instead: `messen.py:588` `sys.exit(1 if fehler else 0)` is the only
exit 0. Reaching it requires (a) `selbstprobe_zeile` green (:299, abort → rc 2 → ctest
red); (b) no `Messfehler` (→ rc 1 at :580); (c) empty `fehler`, which for A2 forces
`code == 1` (:426) **and** `gefunden == a2_soll` literally over the whole 5-entry list
(:428) — the print at :423 therefore read `A2 ...: Code 1 (erwartet 1), 5 Befunde`.
Count-only comparison and a shortened list are impossible on this path; the 0194
saturation cannot return through it.

Sensitivity of the derivation, checked in code: `zeile_von` (:121-132) aborts on 0 or ≥2
occurrences, red-proved **every run** by `selbstprobe_zeile` (:175-198, five cases incl.
middle-needle count check — I traced all five by hand, values correct); numbers come from
the mutant **input** text (:395), not riegel output, so a riegel naming a wrong line
still differs.

Re-measured at the tree I found, independently of vermerk and build note: the five
wordings sit at `werte.hpp` :2, :16, :32 (twice, one wording), :185
(`// Die zweiundzwanzig Groessen aus T48, in der Reihenfolge seiner Tabelle`); each
exactly once among all `zweiundzwanzig|dreiundzwanzig` lines (:29, :41, :147 differ in
wording — :147 `keine der zweiundzwanzig Funktionen` does not contain wortlaut 2, which
ends `Groessen hier ist`). Anchor `}  // namespace kern::werte` once, at :520, below
:185 — derived list `[2, 16, 32, 32, 185]` as the builder states. No weakening anywhere:
comparison, code check and A0's `soll_grund` are intact; deriving all five instead of
only the fifth is within the package's open decision and closes the same trap higher up.

# Finding 1 — to the project manager, about the abnahme text, not the build

Condition 2's receipt — "The same report's A2 block prints five findings and `Code 1
(erwartet 1)`" — is unsatisfiable by **any** green run: ctest prints test output only on
failure (the report shows failing belegstellen output and no passing output). The clause
was written against the red morning report, where the block was visible. No file in this
package's `dateien` can change that. The purpose (A2 still sensitive) is met and proven
above; suggest reading the clause as such when closing, and wording future receipts for
ctest-wrapped probes as "green entry + named rc-0-path property" instead of visible
output. Fourth sighting of this pattern (after 0166, 0189×2).
