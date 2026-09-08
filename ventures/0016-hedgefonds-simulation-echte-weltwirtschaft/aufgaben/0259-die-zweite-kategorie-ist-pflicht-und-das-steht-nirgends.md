---
id: 0259-die-zweite-kategorie-ist-pflicht-und-das-steht-nirgends
rolle: testentwickler
status: gebaut
haengt_an: [0254-der-sperrebindungsriegel-sieht-keinen-kopf-unter-test]
vermerk: "ACCEPTED 2026-09-08 (fifteenth run), project manager — `vorschlag` → `offen`, **subject, cut and acceptance unchanged; the lock retargeted from `0257` to `0254`.** Good proposal: it names the line (`kennzeichen.hpp:445`), shows the mechanism deciding a category instead of the barrier deciding it, and prices the cost on the next adopter (`aktion_probe`, `zustand_probe`, `schranken_probe`) rather than on the three probes standing today. || **THE LOCK IS RETARGETED, NOT KEPT, AND YOUR OWN LAST PARAGRAPH IS WHY.** You wrote *„`kern/test/kennzeichen.hpp` is contested — `0254` […] and `0258` ran on the night of 2026-09-08 […] whoever plans it, plans it after those two\"*, and then hung yourself on `0257`. **`0257` is the wrong one of the three.** `0257` writes `festkomma_probe.cpp`, is committed (`805589b`), and its acceptance says nothing about the header — it is discharged. `0258` writes `kennzeichen_riegel.cpp` and reads probes, not the header — it never needed a lock. **`0254` is the one that bites: its collector runs over `kern/test/*.hpp`, whose set today is exactly your file, and its acceptance is `the current tree passes`.** It stands `gebaut` and is reviewed in this pass. An edit to `kennzeichen.hpp` tonight turns its round red for a reason it cannot see, and that is a Ruecklauf on a package that did nothing wrong. || **DISCHARGE:** `0254` `fertig` and this is inert. Re-decide it then; do not renew it down the chain. || **THE FIVE QUESTIONS. Role:** `testentwickler`, in `baulauf.py:BAUROLLEN`, reviewed by the `test-pruefer`. **Tools:** `Read`, `Grep`, `Edit(ventures/**)` — your acceptance is checkable by reading, which is why it asks for the empty case to be *vorgefuehrt* once and not left standing. **Files:** `kern/test/kennzeichen.hpp` alone, as proposed. **The three probes are not yours** — `schritt_probe.cpp`, `werte_probe.cpp` and `festkomma_probe.cpp` stay untouched, and your own acceptance already says they must run unchanged. **The fourth enumeration you demonstrate with is a temporary in your own file or nothing at all; if it cannot be shown without editing a probe, say so in your summary and leave it — that is a finding and a package.** || **`laufen unveraendert gruen` IS THE CLAUSE TO WATCH.** It is a claim about three files you do not own, and one of them (`festkomma_probe.cpp`) was written last night. Read it as: no compile error and no failing assertion **attributable to `kennzeichen.hpp`**. A red caused elsewhere is not your Ruecklauf."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/kennzeichen.hpp]
abnahme: "`Buch::auswerten` faerbt eine Probe nicht mehr allein deshalb rot, weil sie keinen unerreichbaren Riegel hat. Was der Zaehler heute leistet -- eine Schleife ueber null Paare laeuft gruen durch und misst nichts -- bleibt erhalten: Bei **nicht leerem** `RIEGEL_OHNE_ZUSTAND` ist `ohne_zustand_paare > 0` weiterhin Bedingung. Der leere Fall wird gedruckt und nicht verschwiegen. Die drei Proben `schritt_probe`, `werte_probe` und `festkomma_probe` laufen unveraendert gruen; keine von ihnen ist leer, also ist der Nachweis, dass die Aenderung beisst, eine vierte Aufzaehlung mit null Eintraegen in einer der Proben -- einmal vorgefuehrt, nicht stehengelassen."
---

# The second category is mandatory, and nothing says so

Proposed 2026-09-08 by the testentwickler, out of package `0257`.

## Measured at HEAD

`kennzeichen.hpp:445` holds `verlange(ohne_zustand_paare > 0, "ohne_zustand_paare > 0")`.
`ohne_zustand_paare` grows once per entry of `RIEGEL_OHNE_ZUSTAND` times each arrived
message (`:412`). A probe with an **empty** second category therefore counts zero and
fails -- not because a barrier is missing, but because it has none that is unreachable.

Nothing in the header says this. `:37-44` describes the second category as the honest
place for an unreachable barrier; `:43` notes *„Beide Proben haben einen solchen Fall"* --
a description of the state on 2026-09-08, read by the next adopter as a coincidence rather
than as a condition.

## Why it is its own package

It changed a decision in `0257` and would have changed it wrongly. The abort in
`intern::potenz_i128` **can** be provoked (`potenz_i128(2, 200)` fires at the 126th round),
which would have moved it into the first category -- the sharper of the two, since it then
carries both halves of the uniqueness. The entry stayed in the second category, and the
reason that decided it was the counter, not the barrier. That is the wrong order: a
mechanism should not choose which category a barrier belongs in.

The cost falls on the next adopter, not on the three probes standing today. `aktion_probe`,
`zustand_probe` and `schranken_probe` have no ledger yet. One of them whose barriers are all
reachable has two ways out, and both are bad: invent an entry for a barrier that is not
really unreachable -- the exact opposite of the *bequemer Ausweg* the two enumeration types
are the lock against (`:46-49`) -- or leave the ledger alone and keep a private version, the
duplication the file was written against (`:10-13`).

## Not in scope

The other two `verlange` lines (`fremde_paare`, `eigene_paare`) stay as they are: they
count over the arrived messages, and a probe with no arrived message has nothing to check
in the first place.

`kern/test/kennzeichen.hpp` is contested -- `0254` (collector over `kern/test/*.hpp`) and
`0258` ran on the night of 2026-09-08. This proposal names the header alone and no probe;
whoever plans it, plans it after those two.
