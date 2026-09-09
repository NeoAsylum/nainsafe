---
id: 0286-der-zahlwortriegel-kennt-nur-deklarationen-mit-tabellennummer
rolle: kernbauer
status: vorschlag
haengt_an: [0284-schritt-3-schreibt-den-pfadstand]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/zahlwort/zahlwort_riegel.cpp]
abnahme: "1. `zahlwort_riegel` is green on the current tree, and it is green because it learned a **third admissible kind of declaration**, not because the sentence about it was reworded away. A declaration whose doc block carries an explicit mark -- the counting mark the riegel's own head calls for (`zahlwort_riegel.cpp:84-88`) -- is counted in Sorte 3 and produces no Mangel; one without a mark and without a table number still does. `kern::werte::pfadstand` carries that mark. 2. The mark is a **declared** one and not the absence of something: a declaration that simply forgets its number must stay a Mangel, or the riegel loses the half it was built for. State the mark's exact spelling in the head, and give the self-test a case for each of the three kinds. 3. Sorte 1 is untouched: the count of distinct T48 numbers stays 22, and a marked declaration adds none. 4. The sensitivity probe still answers: the mutant -- one more declaration under an existing number -- must still raise Sorte 3 by exactly one, and a second mutant that strips the mark from `pfadstand` must produce exactly one Mangel. 5. `werte.hpp` needs at most the mark itself; the sentence at `:32` keeps naming the counted number, whatever the count then is."
---

# `kern::werte` has a public function that is not a T48 quantity

## What happened

Section 34 of the design (package `0277`) ordered the path carrier to be read "through
**one** accessor in `kern::werte` that aborts for `Instrument::Regulierung`". Package
`0284` built it: `zustand::i64 pfadstand(const Konstanten&, Gebiet, Instrument)`, declared
in `kern/include/kern/werte.hpp`.

`zahlwort_riegel` reads exactly that one file and holds two things against it that this
declaration breaks:

- **Sorte 3** counts every function declaration in `namespace kern::werte` and compares it
  with the number word before "Deklarationen" in the head. That count went from 23 to 24;
  `0284` moved the word with it, so this half is answered.
- **The Mangel**: a declaration whose doc block names no `T48 Nr. <n>` "faellt damit aus der
  Zaehlung" and gives exit code 1 (`zahlwort_riegel.cpp:824-834`, head `:157-158`).
  `pfadstand` names none, because it is none. The test is therefore red.

## Why the red is right and the fix belongs here

The riegel is not wrong. Its rule -- every public function of this module is one of the
twenty-two derived quantities -- was true when it was written, and T48's own sentence is
what made it true. Section 34 added a kind T48 never named: a declaration that hands out a
field of the carrier and computes nothing. That is a change to the module's contract, and a
check that guards the contract has to learn it explicitly.

**What must not be done:** wording the Mangel away. A doc comment that mentions `T48 Nr. 18`
in a sentence saying "this is not one of them" satisfies the matcher, keeps Sorte 1 at 22
and turns the test green -- while making the next declaration that genuinely forgets its
number indistinguishable from this one. That is the failure mode `notizen/lehren.md`
records on 2026-09-06: a check whose subject cannot move is green and worthless.

**What must also not be done:** moving the accessor out of `kern::werte`. That is a
deviation from `specs/` and needs an ADR, not a builder.

## The mark already has a shape in the riegel's own head

`zahlwort_riegel.cpp:84-88` writes the answer down: "Wer den Riegel allgemein will, braucht
zuerst eine erklaerte Zaehlmarke im Kommentar -- das ist eine Entwurfsfrage und ein anderes
Paket." This is that package, in the narrow form: one mark, one module, three kinds of
declaration, and a self-test case for each.

## Not in scope

The general riegel over more than `werte.hpp`, and any change to Sorte 1 or Sorte 2.
