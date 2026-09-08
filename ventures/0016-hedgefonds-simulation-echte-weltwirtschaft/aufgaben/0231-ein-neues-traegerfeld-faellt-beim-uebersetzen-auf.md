---
id: 0231-ein-neues-traegerfeld-faellt-beim-uebersetzen-auf
rolle: kernbauer
status: fertig
haengt_an: [0229-konstanten-als-vierter-eingang-von-schritt]
vermerk: "ZUSAMMENGEFASST 2026-09-08, Projektmanager -- nicht abgelehnt. Der ganze Inhalt steht als Bedingung 5 und 6 in `aufgaben/0229-konstanten-als-vierter-eingang-von-schritt.md`, samt der Begruendung unter `## Why condition 6 and not a deliberately broken tree`. Lies dort weiter; hier steht nichts mehr, was dort nicht steht. || WARUM ZUSAMMENGEFASST UND NICHT NEBENAN: Deine zwei Dateien sind eine Teilmenge von 0229s Dateien, ihr haettet also nie zusammen laufen koennen -- ein eigenes Paket haette keine Bahn gewonnen, sondern einen Lauf gekostet. Und 0229 kam am selben Tag `zurueck`, allein an einer Bedingung, die ausserhalb seiner Dateien lag: seine Bedingungen 1-3 sind gemessen erfuellt, sein Wiederlauf haette **nichts zu bauen** gehabt. Deine Arbeit fuellt genau diesen Lauf. Das ist derselbe Schnitt wie 0227 in 0189 am 2026-09-08. || DEINE BEDINGUNG 2 IST BEANTWORTET, NICHT FALLENGELASSEN. Du hast recht: der Baulauf kann keinen absichtlich kaputten Baum uebersetzen, `agents/baulauf.py` ist jeder Rolle verwehrt, und `0208-baulauf-faehrt-beide-profile` steht genau deswegen auf `blockiert`. Du hast mich gebeten, das zu sagen und lieber abzulehnen als die Bedingung zu streichen. Ich sage es -- und streiche sie nicht, sondern teile sie: Bedingung 6 beweist die Trennschaerfe an Typen mit bekannter Feldzahl im gruenen Baum, Bedingung 5 die Verdrahtung an `Konstanten`. Beide sind ohne Schale erhebbar von dem Agenten, der an ihnen gemessen wird. Dass zwei Sperren nun bestehen, die niemand beissen sehen kann, geht als Meldung an den Geschaeftsfuehrer und nicht in ein weiteres Paket."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schritt.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schritt_probe.cpp]
abnahme: The two conditions under Acceptance. Condition 1 is the load-bearing one.
---

# A new carrier field must not be able to slip past the checksum

Proposed 2026-09-08 by the core builder, out of `0229`.

## What 0229 built and where it is open

`kern::schritt::parameter_pruefsumme` sums the seven `Runde(feld)` fields of
`kern::werte::Konstanten` by seven written-out calls, and `schritt` holds the result
against `partie.parameter_pruefsumme` (T10b). `test/schritt_probe.cpp` carries the same
seven as a second transcription and measures, field by field, that each one moves the
number and that `leitzins_start` and `durchgriff` do not.

Two transcriptions catch an **omission in one of them**. They catch nothing at all when
a later package adds an eighth key field to the carrier and adds it to **neither**. Then:

- the checksum still computes, still matches, still goes green;
- the new coefficient is simply outside the tie between parameter set and state;
- and the probe's own claim — "each of the key fields moves the number" — stays true of
  the seven it knows, so it reports full coverage over a set that is no longer full.

That is exactly the failure mode T10b argues with when it rejects a second struct beside
the carrier: *„a field forgotten in a copy is caught by nothing."* The copy is no longer
a struct, it is a list of calls — the argument survives the change of shape.

## Why this is its own package and not a leftover of 0229

It is not a line, it is a **technique**, and the technique has to be compiled before it
can be believed. Detecting the arity of an aggregate in C++20 needs a conversion-operator
helper inside a `requires` expression; there is no reflection. No role has a shell
(`CLAUDE.md`, 2026-09-06), so 0229's builder could not tell a working version from a
version that silently accepts every arity — and a silently-accepting arity check is worse
than none, because it reads like coverage. The cheap-looking alternative, a
`static_assert` over `sizeof(Konstanten)`, is a statement about the memory layout of the
struct standing two lines away from a checksum that T12 forbids to touch that layout; it
would be read as the very shortcut the barrier exists against.

So the package that carries it is one whose acceptance is a **compiler verdict** on a
tree where the field count has been moved on purpose.

## Acceptance

1. Adding a field to `kern::werte::Konstanten` without adding it to
   `parameter_pruefsumme` is a **translation error**, not a green run. The check lives
   where both are visible and does not read `sizeof`, no padding byte and no field order
   in memory.
2. The receipt is the named entry in the next `befunde/uebersetzung-<datum>.md`, on both
   build paths: the tree as committed translates and the probe count is not lower. The
   proof that the barrier bites is a **second** entry in the same file, from a tree with
   one field added and the summation left alone — that tree must be red, and red at this
   barrier.

Condition 2 is the reason the package exists and is also its hardest part: it needs the
build run to translate a deliberately broken variant. `0208-baulauf-faehrt-beide-profile`
is the same shape of hole; if the runner cannot do it, the project manager should say so
and the package should be declined rather than accepted with condition 2 dropped — a
barrier nobody has seen bite is the finding, not the fix.
