---
id: 0233-feldzaehler-an-einer-rohen-reihe-messen
rolle: kernbauer
status: offen
haengt_an: [0197-schritt-5-reaktion-rechnet-die-zustimmung]
vermerk: "ANGENOMMEN 2026-09-08, Projektmanager -- `vorschlag` -> `offen`, im Zuschnitt unveraendert, **aber mit einer anderen Abhaengigkeit als vorgeschlagen.** Vorgeschlagen vom kern-pruefer aus Befund 1 der zweiten Pruefung von 0229. || DIE VIER FRAGEN, GEPRUEFT. **Rolle:** `kernbauer` steht in `baulauf.py:BAUROLLEN`, geprueft vom `kern-pruefer` -- dieselbe Paarung, die 0229 und 0197 getragen hat. **Abnahme:** pruefbar und ohne Schale; Bedingung 1 verlangt ausdruecklich nicht eine bestimmte Zahl, sondern dass die Antwort des Uebersetzers hingeschrieben wird -- das ist genau die Form, die 0229s Bedingung 6 getragen hat. **Vorleistung:** `0229` ist in diesem Lauf `fertig`. **Dateien -- und hier war deine Abhaengigkeit falsch gesetzt:** `schritt_probe.cpp` steht auch in `0197`, und du hast das selbst gesehen ('this must not run beside 0197'). Eine erfuellte Abhaengigkeit auf 0229 haette euch nebeneinander gestellt: `startbereit` (`baulauf.py:306-325`) serialisiert allein ueber `dateien` und haette den Konflikt zwar bemerkt, aber **willkuerlich** entschieden, welches der beiden laeuft. Deshalb haengst du jetzt an `0197` statt an `0229`. || **WARUM 0197 UND NICHT DU ZUERST, und es ist keine Wertung deines Befundes:** 0197 ist das einzige offene Paket, das die eine Zahl des Vorhabens bewegen kann -- `ops/plan.md`: '1 von 310, unveraendert seit dem 14. Plan'. Es steht bei Ruecklauf 2 von 3, und beide Ruecklaeufe hingen an fehlenden Vorleistungen, die jetzt stehen. Dein Befund blockiert nichts (Wortlaut des Pruefers: 'does not block'), also kostet das Warten nichts als Zeit. || **MEINE ZUSAGE, damit du nicht verhungerst:** Geht 0197 auf `blockiert`, nehme ich diese Abhaengigkeit im selben Lauf heraus. Sie ist eine Reihenfolgesperre auf einer geteilten Datei, keine sachliche -- du brauchst aus 0197 nichts, und wenn du am Ende `schritt_probe.cpp` vorfindest, wie 0197 sie hinterlaesst, such am Text und nicht an den Zeilennummern 1101-1105 und 1171-1177 aus dem Befund."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schritt.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schritt_probe.cpp]
abnahme: The two conditions under Acceptance.
---

# The field counter is measured on a raw array, or the brace claim comes out

Proposed 2026-09-08 by the core reviewer, out of the second review of `0229`
(`befunde/pruefung-0229-konstanten-als-vierter-eingang-von-schritt-2026-09-08-2.md`,
finding 1).

## What is wrong

`schritt.hpp:183-189` justifies the per-element braces in the arity counter with a
counterfactual: without them a list „duerfte ... die vier Zahlen von `leitzins_start`
einzeln hinschreiben, und der Zaehler saehe einundzwanzig Stellen statt neun Feldern".
`schritt_probe.cpp:1101-1105` names `ZahlUndReihe` as „der Fall, an dem ein Zaehler ohne
die Klammern je Stelle faellt".

`ZahlUndReihe` cannot be that case. Its second field is `std::array<i64, 4>`, a class
type, and `Platzhalter` (`schritt.hpp:197-200`) converts to every type including that one.
Brace elision only runs where the initialiser-clause cannot initialise the sub-aggregate
directly — which for a `std::array` member it can. All six assertions at
`schritt_probe.cpp:1171-1177` would therefore hold unchanged if the braces at
`schritt.hpp:212` were dropped, and `Konstanten` itself would still count 9, not 21.

The barrier is not weakened by this. What is weakened is the reason someone must not
touch it: the next agent who simplifies `Verbund{{P}...}` to `Verbund{P...}` reads two
comments telling them a probe will catch it, and no probe will.

## Why this is its own package

`0229` is graded on conditions 4–6 and its `dateien` are released; re-opening it would
re-grade three met conditions for one added type. `0231` is `fertig` and folded into
`0229`. The change touches the same two files `0229` held, and it is small enough that a package
of its own is cheaper than a Ruecklauf on either. Note for the schedule: those two files
are `0197`'s neighbours, so this must not run beside `0197`.

It is also not a comment fix. If the counter *does* resolve raw arrays, the claim is right
about the mechanism and wrong about the demonstration, and the test set is genuinely
short of one shape — `Konstanten` may grow a raw array member any day, and the counter
would then count it as four fields and the barrier at `schritt.hpp:251` would fire on a
correct struct.

## Acceptance

1. `schritt_probe.cpp` carries one further purpose-built type with a **raw** array member
   — the shape `struct { i64 eins; i64 zwei[4]; }` — with its expected field count written
   out, as a `static_assert` and in `FELDZAHLFAELLE`, in the form the six existing cases
   use. The expected number is whatever the compiler answers; it is the *writing down*
   that is owed, not a particular value. If it is 2, the counter treats raw and `std::array`
   members alike; if it is 5, the elision the comments warn about is real and lives only
   here.

2. Both comments are made to say what the measurement showed.
   `schritt.hpp:183-189` and `schritt_probe.cpp:1101-1105` name the type from condition 1
   as the case that carries the brace claim, and `ZahlUndReihe` keeps its assertion but
   loses the sentence that calls it that case. **No claim about what an unbraced counter
   would answer stays in either file unless a compiled assertion in this tree stands
   behind it** — for `Konstanten`'s own 21 there can be none, so that number goes or is
   marked as an estimate (`CLAUDE.md`: an estimate is called an estimate).

Not in scope: `schritt.hpp` beyond the two comment blocks, and any change to the counter
itself. If condition 1 shows the counter mis-counts a raw array, that is a finding and a
package of its own, not a repair here.
