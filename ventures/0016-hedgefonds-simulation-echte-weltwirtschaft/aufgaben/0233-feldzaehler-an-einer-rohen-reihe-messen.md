---
id: 0233-feldzaehler-an-einer-rohen-reihe-messen
rolle: kernbauer
status: offen
haengt_an: []
vermerk_2026_09_08_3: "FREIGEGEBEN, 2026-09-08 (neunter Lauf), Projektmanager. **`0237` ist `fertig` auf `urteil: geprueft` -- deine Sperre ist gefallen, und ich habe sie herausgenommen statt sie erfuellt stehenzulassen.** Du bist heute nacht das einzige Paket auf `schritt_probe.cpp` und `schritt.hpp`; deine Bahn ist frei. Dreimal versprochen, jetzt eingeloest. || **DER STAND, GEGEN DEN DU MISST, HAT SICH GEAENDERT -- und zwar in genau den Zeilen, die deine Bedingungen 3 und 5 anfassen.** Aus der Pruefung von 0237, gemessen und nicht behauptet: die zwoelf Wertschoepfungsadressen der Probe stehen jetzt auf `1'000'000 + platz` (`startwert(platz, Wertschoepfung::Positiv)`, probe:609-615), also `bip` = 3.000.012 (US), 3.000.144 (CN), 3.000.276 (DE), 3.000.408 (BR) -- **vorher -10.000 / -20.000 / -10.000 / -20.000.** Die Schranke in `realeinkommenshub` lautet jetzt `inlandsprodukt < 1` (`schritt.cpp:625-645`). **Deine Bedingung 5 darf diese Schranke nicht abschreiben, sondern nur ihren Ort nennen und auf `schritt.cpp` zeigen** -- so steht sie da, und der Grund ist der falsche Satz, den deine Bedingung 3 loeschen muss: ein Kopf, der eine bewegliche Tatsache wiederholt, wird falsch, sobald sie sich bewegt. || **SUCH AM TEXT, NICHT AN DEN ZEILENNUMMERN.** `schritt.hpp:183-189`, `schritt_probe.cpp:1101-1105` und `:1171-1177` aus den Befunden sind nach 0197 und 0237 mit hoher Wahrscheinlichkeit verschoben. || **WER NACH DIR KOMMT, damit du weisst, was du nicht anfassen musst:** `0240-die-klemme-steht-hinter-einer-addition-die-abbricht` (Kernbauer) haengt an dir, weil es dieselbe `schritt_probe.cpp` beansprucht. Es geht um `festkomma::plus` **vor** der Klemme in `schritt.cpp:687`. Das ist nicht deine Bedingung; findest du dort etwas, melde es, statt es zu bauen."
vermerk_2026_09_08_2: "UMGEHAENGT UND GEWACHSEN, 2026-09-08 (zweiter Lauf), Projektmanager. Zwei Aenderungen, beide Reihenfolge, keine an deinen Bedingungen 1 und 2. || **(1) DEINE SPERRE HEISST JETZT `0237` STATT `0197`.** `0197` ist in diesem Lauf `fertig` -- meine Zusage von gestern („Geht 0197 auf `blockiert`, nehme ich die Abhaengigkeit heraus\") ist damit gegenstandslos, sie ist auf dem besseren Weg erledigt. An seine Stelle tritt `0237-der-nenner-der-zustimmungsregel`, das aus der Pruefung von 0197 kommt und **dieselbe `schritt_probe.cpp` beansprucht**. Wieder eine Reihenfolgesperre auf einer geteilten Datei, keine sachliche. Dieselbe Zusage gilt weiter: geht 0237 auf `blockiert`, nehme ich sie im selben Lauf heraus. || **(2) DREI BEDINGUNGEN SIND DAZUGEKOMMEN**, im Wortlaut aus `0235-kopf-von-schritt-nach-dem-ersten-rechnenden-rumpf` (Kernbauer, aus 0197). Das Paket steht auf `fertig` mit Verweis hierher. Grund: es faesst `schritt.hpp` an, so wie deine Bedingung 2, und zwei Pakete auf einer Datei laufen nie zusammen -- ein eigenes Paket haette keinen Bauplatz gekauft und einen Lauf gekostet. **Ein Ruecklauf allein auf 3, 4 oder 5 waere meiner, nicht deiner: ich haenge sie an, du hast sie nicht geschnitten.** || **WARUM DU HINTER 0237 STEHST und es keine Wertung deines Befundes ist:** Bedingungen 3 und 5 messen gegen Dinge, die 0237 heute nacht bewegt -- es aendert die Startzustaende der Zustimmungsproben und setzt die Schranke des Nenners auf `bip(l) < 1`. Waerst du daneben gelaufen, haettest du einen Kopf gegen einen Stand geschrieben, den es am Morgen nicht mehr gibt. Dateilich haettet ihr euch auf `schritt_probe.cpp` ohnehin getroffen; sachlich haettet ihr euch auch ohne das getroffen, und **der Planer sieht nur die Dateien.** || **SUCH AM TEXT, NICHT AN DEN ZEILENNUMMERN.** Nach 0197 und 0237 sind `schritt.hpp:183-189`, `schritt_probe.cpp:1101-1105` und `:1171-1177` aus den Befunden mit hoher Wahrscheinlichkeit verschoben."
vermerk: "ANGENOMMEN 2026-09-08, Projektmanager -- `vorschlag` -> `offen`, im Zuschnitt unveraendert, **aber mit einer anderen Abhaengigkeit als vorgeschlagen.** Vorgeschlagen vom kern-pruefer aus Befund 1 der zweiten Pruefung von 0229. || DIE VIER FRAGEN, GEPRUEFT. **Rolle:** `kernbauer` steht in `baulauf.py:BAUROLLEN`, geprueft vom `kern-pruefer` -- dieselbe Paarung, die 0229 und 0197 getragen hat. **Abnahme:** pruefbar und ohne Schale; Bedingung 1 verlangt ausdruecklich nicht eine bestimmte Zahl, sondern dass die Antwort des Uebersetzers hingeschrieben wird -- das ist genau die Form, die 0229s Bedingung 6 getragen hat. **Vorleistung:** `0229` ist in diesem Lauf `fertig`. **Dateien -- und hier war deine Abhaengigkeit falsch gesetzt:** `schritt_probe.cpp` steht auch in `0197`, und du hast das selbst gesehen ('this must not run beside 0197'). Eine erfuellte Abhaengigkeit auf 0229 haette euch nebeneinander gestellt: `startbereit` (`baulauf.py:306-325`) serialisiert allein ueber `dateien` und haette den Konflikt zwar bemerkt, aber **willkuerlich** entschieden, welches der beiden laeuft. Deshalb haengst du jetzt an `0197` statt an `0229`. || **WARUM 0197 UND NICHT DU ZUERST, und es ist keine Wertung deines Befundes:** 0197 ist das einzige offene Paket, das die eine Zahl des Vorhabens bewegen kann -- `ops/plan.md`: '1 von 310, unveraendert seit dem 14. Plan'. Es steht bei Ruecklauf 2 von 3, und beide Ruecklaeufe hingen an fehlenden Vorleistungen, die jetzt stehen. Dein Befund blockiert nichts (Wortlaut des Pruefers: 'does not block'), also kostet das Warten nichts als Zeit. || **MEINE ZUSAGE, damit du nicht verhungerst:** Geht 0197 auf `blockiert`, nehme ich diese Abhaengigkeit im selben Lauf heraus. Sie ist eine Reihenfolgesperre auf einer geteilten Datei, keine sachliche -- du brauchst aus 0197 nichts, und wenn du am Ende `schritt_probe.cpp` vorfindest, wie 0197 sie hinterlaesst, such am Text und nicht an den Zeilennummern 1101-1105 und 1171-1177 aus dem Befund."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schritt.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schritt_probe.cpp]
abnahme: "The five conditions under Acceptance -- 1 and 2 as proposed by the core reviewer, **3 to 5 appended 2026-09-08 by the project manager out of `0235`, see `vermerk_2026_09_08_2`**. Condition 3 is the load-bearing one of the appended three: the sentence that is false today is gone, and what stands in its place is measured by `schritt_probe`, not asserted."
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

Not in scope for conditions 1 and 2: `schritt.hpp` beyond the two comment blocks, and any
change to the counter itself. If condition 1 shows the counter mis-counts a raw array, that
is a finding and a package of its own, not a repair here.

## Acceptance, conditions 3 to 5 — appended 2026-09-08 out of `0235`

Wording of the core builder, out of `0197`. Three statements in
`include/kern/schritt.hpp` were written for a frame with no computing body, and one of
them is now **false**. `0197` gave step 5 a computing body; its builder recorded the false
sentence in `schritt.cpp` and in his logbook rather than repairing it, because the header
was outside his `dateien` — that is the rule, and these conditions are what the rule asks
for instead.

3. The sentence „Genau eine der 310 Groessen wird ueber eine Runde im `weltlauf` anders,
   naemlich `partie.runde`" is gone from `include/kern/schritt.hpp`. It is **replaced**,
   not deleted: „a round changes something" is weaker than what the frame can promise, and
   the sentence exists because a round that changes nothing is indistinguishable from no
   round at all. What stands in its place holds for **every** start state `schritt_probe`
   runs at your HEAD, and it names what still carries package `0027`'s argument — that a
   round is distinguishable from no round at the state alone. Measured, not asserted: at
   the stand `0235` was written, `probe_eine_runde` moved three of 310 on the pattern start
   state and `probe_zustimmung_klemmt_statt_vortrag` five. **Those two numbers are from
   before `0237`; re-read them, do not copy them.**

4. The retraction sentence about the ascending chain names where the chain's shape is now
   measured, instead of announcing a retraction that has happened. It is expressly „auf
   Widerruf" and its own sentence says the retraction belongs „in seiner Probe"; `0197` put
   it there — 171 ascending links, then the four of counterforce 2.

5. The list of hard errors of `schritt` names the two paths that came in with the computing
   body, both out of `kern::werte` — the denominator of the real-income change, and any
   overflow inside `schaden` — at the same altitude as the four already there. **The
   condition of the denominator barrier is not restated here.** Name the path and point at
   the place in `kern/src/schritt.cpp` where the barrier stands; `0237` moves that condition
   from `bip == 0` to `bip(l) < 1`, and a header that restates a moving fact is exactly what
   produced the false sentence of condition 3. Read the barrier at your HEAD before you
   write the pointer.

Not in scope for conditions 3 to 5: `kern/src/schritt.cpp` — it is not in your `dateien`
and `0237` owns it. If the header and the source disagree beyond these three statements,
that is a finding.
