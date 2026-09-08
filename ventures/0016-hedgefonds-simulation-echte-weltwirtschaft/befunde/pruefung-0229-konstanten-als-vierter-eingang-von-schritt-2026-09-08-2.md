---
typ: pruefung
paket: 0229-konstanten-als-vierter-eingang-von-schritt
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "Conditions 4, 5, 6: pass counts of `uebersetzung-2026-09-08.md` against `-09-07` entry by entry, the `static_assert` at `schritt.hpp:251` read for sizeof/padding/order, and the six purpose-built types at `schritt_probe.cpp:1171-1177`."
befunde: 1
---

# Ruecklauf 1: the barrier holds, and the tree is back to its 2026-09-07 numbers

Conditions 1–3 were graded on 2026-09-08 and are not re-opened (`vermerk_ruecklauf_1`).

## The tree I read is the tree that was compiled

`uebersetzung-2026-09-08.md:123` and `:154`: „Bezugsstand im Kommentar: d17b26d; HEAD zu
Beginn: 2f2f79f", „HEAD am Ende: 2f2f79f" — printed by `belegstellen_kopfzahlen` while
`ctest` ran. 2f2f79f is 0229's commit.

`werte.hpp` stood still, which the Ruecklauf demanded: `zustimmung_elastizitaet` is still
at 143–153, the lines `vermerk_ruecklauf_1` names, and `werte.hpp:185` is still
`// Die zweiundzwanzig Groessen aus T48` — the line `0232` re-measured. That is why
`zahlwort_messung` is green (`:168`).

## Condition 4 — met

Passing probes per manifest, 2026-09-07 → 2026-09-08: 25/26 → 25/26, 13/13, 3/3, 4/5,
1/1, 1/1, 3/3 — **identical entry for entry.** Not merely "not lower than at the start of
the run" (which was 24/26 and 2/3, my finding of this morning), but back to the state
before 0229 existed. The single failure `belegstellen_kopfzahlen` (`:175` root, `:376` on
the `werkzeuge/belegstellen` path) is red in the 2026-09-07 report as well (`:143`,
`:328`); its messages name `belegstellen_riegel.cpp`, no file of 0229.

Named entry, both build paths: `schritt_probe` ` 7/26 Passed` (`:91`) and ` 7/13 Passed`
(`:244`). Both translation units built (`:59`, `:207`).

## Condition 5 — met

`schritt.hpp:251` holds `feldzahl<Konstanten> == SUMMIERTE_FELDER + JAHRGANGSFELDER`
(7 + 2). Add a field without a `nimm_i64` line and the sum stays 9 while `feldzahl`
becomes 10 — translation error, not a green run. It is wired to `Konstanten` itself, in
`schritt.hpp`, no third file.

Read for the forbidden route: `schritt.hpp:191-257` contains no `sizeof`, no `offsetof`,
no `alignof`, no memory comparison. The count comes from the arity of an aggregate
initialiser list (`schritt.hpp:212`), which depends on the *number* of members, not on
their order or on padding. T12's constraint is kept at the watching site.

The three transcriptions of the seven fields still agree in order — `schritt.hpp:157-163`,
`schritt_probe.cpp:1022-1030`, `werte.hpp:115/119/123/127/131/141/153` — and the numeral
`7` at `schritt.hpp:244` is the fourth, held by the compiler through :251.

## Condition 6 — met

`schritt_probe.cpp:1171-1177`: `KeinFeld` 0, `EinFeld` 1, `ZweiFelder` 2, `ZahlUndReihe`
2, `NeunFelder` 9, `ZehnFelder` 10 — five distinct counts, each written out, each a
`static_assert`, and the object file was built (`:59`, `:207`), so all six held. A
detector that always answers the same number fails `KeinFeld` or `EinFeld` whatever that
number is; one saturating at `FELDSUCHE_ENDE = 32` fails all six. The application is
re-checked at run time (`:1214-1217`) inside a probe that exits non-zero on any `PRUEFE`
(`:1348`).

## Finding 1 — the brace-elision case is asserted, not measured (does not block)

`schritt.hpp:183-189` and `schritt_probe.cpp:1101-1105` claim the per-element braces are
what stops the counter from resolving arrays: without them „saehe [der Zaehler]
einundzwanzig Stellen statt neun Feldern", and `ZahlUndReihe` is called „der Fall, an dem
ein Zaehler ohne die Klammern je Stelle faellt".

`ZahlUndReihe` cannot show that. Its second field is `std::array<i64, 4>` — a class type,
and `Platzhalter` converts to any type including that one. Where an initialiser-clause can
initialise the sub-aggregate directly, brace elision does not run; it runs only where
direct initialisation is impossible, i.e. for a **raw** array member, which no type in the
set has. So the unbraced counter would most likely answer 2 here and 9 for `Konstanten`,
and every one of the six assertions would pass unchanged with the braces removed.

I have no compiler and do not claim the numbers 21 and 5 are wrong — I claim the probe
does not settle them while the two comments state them as settled. Proposal `0233` adds
the one type that would: a raw-array member, expected count written out.
