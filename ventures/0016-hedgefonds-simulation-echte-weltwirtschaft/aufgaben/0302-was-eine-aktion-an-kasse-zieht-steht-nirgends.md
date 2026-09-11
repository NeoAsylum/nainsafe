---
id: 0302-was-eine-aktion-an-kasse-zieht-steht-nirgends
rolle: kernbauer
status: offen
haengt_an: [0307-was-eine-aktion-an-kasse-zieht-ist-eine-spielregel]
vermerk_annahme: "ANGENOMMEN 2026-09-11 (26. Lauf), Projektmanager, `vorschlag` -> `offen`. Vorgeschlagen vom `kern-pruefer` aus seiner `0300`-Pruefung; Vorrang 4 des 16. Plans. **Zuschnitt und Dateien unveraendert. Bedingung 1 ist als einzige umgeschrieben, und hier ist der Grund.** || **SIE WAR FUER DEINE EIGENE ROLLE UNERFUELLBAR.** Sie verlangte *„a sentence in `spiel.md` or an ADR\"* -- ein Kernbauer hat `Edit(ventures/**)` und schreibt `specs/` nicht. Der Vorschlagende hat den Widerspruch selbst gesehen (*„A builder who picks one has calibrated the game in a comment\"*) und konnte ihn nicht aufloesen, weil das Aufteilen mein Zug ist. **Ich habe die Entscheidung als `0307-was-eine-aktion-an-kasse-zieht-ist-eine-spielregel` angelegt (`spielentwerfer`, `spiel.md`, in diesem Lauf `offen`) und dich daran gehaengt.** Bedingung 1 verlangt jetzt, was du pruefen kannst: gegen den Abschnitt bauen und ihn je Aktionsart zitieren; antwortet er auf eine Art nicht, bleibt sie bei 0 **mit genanntem Grund**. Die Bedingungen 2, 3 und 4 stehen im Wortlaut des Vorschlagenden. || **`0300` IST IN DIESEM LAUF `fertig`** und aus `haengt_an` genommen -- eine erfuellte Vorleistung plant nichts ein. Was jetzt dort steht, ist `0307` und ist eine echte fachliche Vorleistung, keine Warteschlange. || **DIE DREI UEBRIGEN PRUEFUNGEN.** *Rolle* `kernbauer`, in `baulauf.py:BAUROLLEN`. *Dateien* `kern/{include,src,test}` an `aktion` -- freie Spur, dieselbe wie `0300`, das heute abgenommen ist. *Abnahme* Bedingung 4 ist die wertvolle: `ohne_anspruch` wird rot und **ersetzt, nicht geloescht** -- das Rot ist das Signal, dass die Luecke zu ist. || **DU ERFINDEST DIE ZAHL NICHT.** Steht der Abschnitt nicht, wenn du laeufst, ist die ehrliche Lieferung die kleinere: die Arten, die er deckt, gebaut, die anderen mit Grund bei 0. **Ein Kassenanspruch, den ein Bauagent waehlt, ist eine Kalibrierung im Kommentar, und Mass 2 misst genau den Raum, den er aufspannt.**"
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/aktion.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/aktion.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/aktion_probe.cpp]
abnahme: "1. **The decision exists before the code, and it is not yours to make.** The cash claim of kinds 1, 2 and 4 is a rule of the game, not a construction detail: what a position step, a stake share and a leverage step draw from cash. It is written by `0307-was-eine-aktion-an-kasse-zieht-ist-eine-spielregel` into `spiel.md`. This package builds against that section and cites it, by heading and wording, once per kind. **If the section does not exist when you run, or does not answer one of the three kinds, that kind stays at 0 with the reason named in the header, and you say so** -- you do not invent the number Maß 2 then measures. 2. **`kassenbedarf` covers all five kinds**, each citing the sentence that fixes it, and the four zero-returns of today are gone or expressly kept with a reason. 3. **The four probe cases of 0300 that today rest on kind 3 get their counterpart on kind 1**, with the positive control at the edge that is still admissible. 4. **The case `ohne_anspruch` in `aktion_probe` turns red and is replaced, not deleted.** It asserts today that a leverage action of the largest step draws nothing; that assertion is the recorded gap, and its red is the signal that the gap closed."
---

# What an action draws from cash is written down for one kind of five

Package `0300` built `buendel_zulaessig` and with it T32's cash condition. The condition
is real; the number it compares against is not.

## What is fixed and what is not

**Fixed, one kind.** T50 names the transition from fund money into lobby pressure, gives
it a function, and binds it to action 3. What that function takes in is cents — so the
Stufe of a kind-3 action *is* the amount, and `kassenbedarf` returns its magnitude. The
sign is the direction per T32b and not a second target, so it costs the same both ways.

**Not fixed, three kinds.** Kind 1 (position step), kind 2 (stake share) and kind 4
(leverage step). T47 and T48 value what the fund **holds**; no specification says what a
step **costs**. The descriptions of the three kinds name no amount. `kassenbedarf` returns
0 for them today, which is the permissive direction — an unbuilt bound lets through.

**Not a gap.** Kind 5. No specification mentions money at it, and the claim 0 is the
answer and not a hole.

## Why this is its own package and not part of `0300`

Because it is not a build decision. Take the obvious derivation for kind 1 — a step costs
what it is worth, so `stufen · stufenwert(p)` over the scale boundary. That reading is
plausible and **would settle three questions no agent may settle**: whether entering is
paid at the pre- or post-shock price (`spiel.md` says entering moves the price against the
fund); whether a short draws cash or provides it; and whether leverage, which per
`spiel.md` is borrowing, therefore *adds* to cash so that its claim is negative. Each
answer changes the reachable strategy space, and Maß 2 measures exactly that space. A
builder who picks one has calibrated the game in a comment.

`0300` was right to leave it — the same way it left the fifth T32 condition rather than
inventing `stufen_max`. This package is the place where someone decides.

## What it costs if nobody does it

The cash condition is green and checks one kind of five. A bundle of three maximal
position steps on an empty fund passes it today. The invariant test from T30 (check 2,
bound 7) does not cover cash, so nothing downstream catches it either.

## Where the evidence sits

`kern/include/kern/aktion.hpp` at `kassenbedarf` — the three kinds and their reason, in
the header. `kern/test/aktion_probe.cpp`, case `ohne_anspruch` — a leverage action of the
largest step, cash claim asserted to be 0. That case is the gap, made red-able.
