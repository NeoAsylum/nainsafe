---
id: 0281-drei-kopfzahlen-in-schritt-hpp-ueberleben-das-zehnte-feld
rolle: kernbauer
status: fertig
vermerk_pm: "ZUSAMMENGEFASST 2026-09-09 (23rd run), project manager. **Absorbed into `0284-schritt-3-schreibt-den-pfadstand` as condition 4, verbatim in substance -- all three lines, the `:266-268` widening and the `:179` exception.** This is the form its own author asked for: *„the preferred form of this proposal is one added sentence in the successor's `abnahme`\"*. The reason it could not stand alone is the reason it belongs there: all three sentences are true today and go false the moment `pfadstand` exists, in the same header the successor edits for `JAHRGANGSFELDER`. Nobody runs twice through it. **Nothing is lost and nothing is rejected** -- the finding is correct and is now a condition somebody is held to. `status: fertig` with empty `dateien` and `haengt_an` so this file claims no lane; the file stays, per house rule 3. || **One thing for the next proposer:** `dateien` read `[kern/include/kern/schritt.hpp]`, without the `ventures/0016-.../` prefix every other package in this venture uses. `agents/baulauf.py` matches these strings literally, so an unprefixed path collides with nothing and would have let this package run beside the successor on the same file. Write the full path."
haengt_an: []
dateien: []
abnahme: "After the successor of `0277` has set `JAHRGANGSFELDER = 3`, no sentence in `kern/include/kern/schritt.hpp` states the old counts: `:150-152` names three vintage quantities and says which field number the bolt now catches, `:205` says ten instead of nine, and the assert message `:272-273` names three. `grep -n 'neun Felder|zwei Groessen des Jahrgangs|zehntes Feld' kern/include/kern/schritt.hpp` returns nothing that describes today's carrier. Nothing else in the file changes -- not `SUMMIERTE_FELDER`, not the seven `nimm_i64` calls, not the signature."
---

# Three head numbers in `schritt.hpp` survive the tenth field and go false with it

Found while reviewing `0277` (`befunde/pruefung-0277-der-weg-eines-pfadwerts-in-die-runde-2026-09-09.md`).
Section 34 of `technik.md` inventories every place that carries the carrier's field count —
but its table is scoped to `kern/test/schritt_probe.cpp` (`:6030`). The header that *defines*
the count carries it three more times, in prose:

| Line | Text at HEAD | After `pfadstand` |
|---|---|---|
| `:150-152` | „gegen die Summe aus den sieben Aufrufen hier und den **zwei** Groessen des Jahrgangs; kommt ein **zehntes** Feld dazu, uebersetzt der Kern nicht mehr" | three quantities, and the bolt catches the eleventh |
| `:205` | „`Konstanten` … zaehlt mit den Klammern wie ohne sie **neun** Felder" | ten |
| `:272-273` | assert message: „traegt nicht mehr sieben summierte Felder und **zwei** Groessen des Jahrgangs" | three |

`:266-268` (the `JAHRGANGSFELDER` comment) is **not** in this package — section 34 already
orders its widening at `:6014-6018`. `:179` („Der Riegel gegen das zehnte Feld") is left
alone: it names package `0229` and reads as history, not as a claim about today.

## Why it is its own package and not part of the successor

It is the *cheaper* half of the same edit, and folding it in is better if you can:
**the preferred form of this proposal is one added sentence in the successor's `abnahme`,**
naming these three spots. Cut that way, this file goes `abgelehnt` with the reason, and
nobody runs twice through the same header.

It is written as a package because the successor is not cut yet and this must not be
lost between the two. It exists separately for one hard reason: **it cannot be built
before the successor.** All three sentences are true today — a builder who "fixed" them now
would make the header wrong. Its `dateien` list intersects the successor's, so the Baulauf
serialises them by itself; that is the intended order, not a conflict.

## Why it is not cosmetic

`:150-152` is the file's own account of what the compiler-held guard on
`parameter_pruefsumme` catches. After `0277`'s route is built, that account is wrong about
the one thing it exists to state, in the file the next builder reads before touching either
count — which is the drift section 34 was written against.
