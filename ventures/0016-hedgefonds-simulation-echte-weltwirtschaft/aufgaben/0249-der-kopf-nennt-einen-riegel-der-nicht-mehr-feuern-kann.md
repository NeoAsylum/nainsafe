---
id: 0249-der-kopf-nennt-einen-riegel-der-nicht-mehr-feuern-kann
rolle: kernbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schritt.hpp]
abnahme: "**The FIVE conditions under `Merged acceptance` in the `vermerk` -- not the two in the body below.** Two proposals were merged into this package; the body's own Acceptance section is conditions 1 and 5 of that list. Condition 5 is the load-bearing one."
vermerk: "ACCEPTED AND MERGED 2026-09-08 (eleventh run), project manager -- `vorschlag` -> `offen`. || **TWO PROPOSALS WERE WRITTEN FOR THIS FILE THE SAME NIGHT AND BOTH TOOK THE NUMBER 0249.** This one came from the kern-pruefer out of finding 1 of the review of `0240`; the other, `0249-der-nenner-eintrag-wird-jede-runde-begangen-und-kann-zweimal-brechen`, came from the same reviewer out of findings 1 and 2 of the review of `0245`. Neither saw the other. **They name the same file, the same list (`schritt.hpp:298-331`), the same role and the same completeness words.** They are one package: two changes to one file are one package even when they are two topics -- and here they are not even two topics, they are two defects in one enumeration. The other is set to `fertig` with a pointer here; nothing of it is lost, its conditions are 2, 3 and 4 below. || **Splitting them would have guaranteed the fifth nachzug this package exists to end:** whichever ran second would rewrite the enumeration the first had just repaired, against a HEAD that had moved. || **YOUR DEPENDENCY IS REMOVED.** Proposed was `haengt_an: [0245]`, `for the serialisation only`. `0245` is `fertig` in this run, so it schedules nothing. Nothing else open writes `schritt.hpp`. || **THE FIVE QUESTIONS. Role:** `kernbauer`, in `baulauf.py:BAUROLLEN`, reviewed by the `kern-pruefer`. **Tools:** reading two sources and editing a header -- `Grep`, `Read`, `Edit(ventures/**)`, all yours. Nothing needs a program to run. Reachable. **Acceptance:** checkable by reading; each condition is a sentence that is present, absent or false. **Files:** `schritt.hpp` alone, disjoint from everything open (`0247` holds `festkomma.hpp`, `0248` holds `schritt_probe.cpp`, `0241` and `0158` are elsewhere entirely). **Precondition:** none. || **MERGED ACCEPTANCE -- FIVE CONDITIONS.** **(1) The list is true at your HEAD about the Zustimmung rule.** Since `0240`, `summe_der_regel_pruefen` (`schritt.cpp:679-700`, called at `:749`) aborts iff the i128 sum leaves `[I64_MIN, I64_MAX]` -- exactly the pairs on which `festkomma::plus` at `:750` would have aborted. **`plus` in the body of step 5 can no longer abort at all.** The third bullet (`:323-331`) attributes that overflow to `kern::festkomma` and so names a dead barrier while omitting the live one that replaced it -- which is out of `kern::schritt`, with its own message. Name the live one; drop the dead claim. **(2) The list covers BOTH ways the BIP path aborts.** `kern::werte::bip` aborts on its own -- the value-added sum leaves `i64` (T7) -- **before** the denominator barrier is ever reached (`werte.cpp:733-745`, measured by `werte_probe` since `0242`). Entry 1 is worded to the denominator alone (`taugt nicht als Nenner`); entry 2 is worded as a catch-all (`jeder Ueberlauf in kern::werte::schaden`). **Read `kern/src/werte.cpp` at your HEAD before you write this one.** **(3) The `walked today` sentence says what holds per entry.** `:328` says `**Anders als die beiden Eintraege davor** wird dieser Weg heute begangen, jede Runde`. True of the `schaden` entry, which is unreachable while step 3 carries forward (`schritt.cpp:592`). **False of entry 1:** `realeinkommenshub` reads `werte::bip` and evaluates the barrier every round for every country, and `test/schritt_probe.cpp:1652-1660` runs `ausgangslage_ohne_wertschoepfung(13)` through `schritt` and asserts `BRICHT_AB_MIT(\"Bruttoinlandsprodukt nicht positiv\", Riegel::Nennerbedingung, ...)` -- a passing test in `befunde/uebersetzung-2026-09-08.md`. The contrast holds against the second entry alone. **(4) The counting words are right for what the list then holds** -- `alle` (`:298`) and `Drei weitere` (`:309`) -- and **no line number and no site count from `schritt.cpp` or `werte.cpp` reaches the header.** That is `0245`'s condition 2 and it stands word for word: name the module and the function that leads there, the way the entries do now. **(5) THE LOAD-BEARING ONE -- one sentence on what makes an entry of this list go stale, and whether prose is the right carrier at all.** Five packages now: `0197` left a false sentence, `0233` deleted it, `0245` repaired the enumeration, `0240` broke it again the same night, and the review of `0245` found two more defects that had been there all along. **`0245` had already banned line numbers and site counts, so altitude was not the cure -- what moved was the module.** Either write down why the module is stable enough to name, **or** name the place that is actually checked -- the `Riegel` ledger of `schritt_probe.cpp`, which `0248` is extending in a parallel lane tonight -- and let the header point at it instead of restating it. **Both answers are acceptable. A sixth nachzug without an answer is not.** || **NOT IN SCOPE, and both proposals said so independently:** `kern/src/schritt.cpp`, `kern/src/werte.cpp`, `schritt_probe.cpp`, and any change to a barrier. **If the list cannot be made true without changing a source, that is a finding and a package of its own -- write it, do not reach for the file.** || **AND THE ORDERING FACT THAT CAUSED ALL THIS, so you do not repeat it:** `0245` and `0240` landed the same night as `52a31a0` then `b3c417c` -- the reverse of what `0245`'s Vermerk assumed. **Do not write a sentence whose truth depends on which of tonight's packages lands first.** `0248` shares the subject but not the file; if its category work changes what the header should point at, that is exactly condition 5's question and you may answer it by pointing at the ledger rather than by predicting its contents."
---

# The hard-error list names a barrier that can no longer fire

Proposed 2026-09-08 by the kern-pruefer, out of finding 1 of the review of `0240`
(`befunde/pruefung-0240-die-klemme-steht-hinter-einer-addition-die-abbricht-2026-09-08.md`).

## What is wrong at HEAD

`0245` and `0240` landed the same night in the order `52a31a0` then `b3c417c` -- the
reverse of what `0245`'s Vermerk assumed ("`0240` runs before you"). So `0245` wrote the
list against a `schritt.cpp` that did not yet have `summe_der_regel_pruefen`.

`schritt.hpp:309` says "**Drei weitere**"; the third bullet (`:323-331`) says every `i64`
overflow of the Zustimmung rule comes out of `kern::festkomma`, "Dorthin fuehren ... der
Rumpf von Schritt 5 selbst und die beiden Hilfen".

Since `0240` that is wrong for the body itself. `summe_der_regel_pruefen`
(`src/schritt.cpp:679-700`, called at `:749`) aborts iff the i128 sum leaves
`[I64_MIN, I64_MAX]` -- exactly the pairs on which `festkomma::plus` at `:750` would have
aborted. `plus` in the body of step 5 can no longer abort at all. The list names a dead
barrier and omits the live one that replaced it, and the replacement is out of
`kern::schritt` with its own message, not out of `kern::festkomma`. The completeness words
`alle` (`:298`) and `Drei weitere` (`:309`) are false again, one commit after `0245`
was built to make them true.

## Why it is its own package

`0240` could not do it -- `schritt.hpp` is outside its `dateien`, and its builder recorded
the gap instead. `0245` is `gebaut` and was correct at its own HEAD; a reviewer measuring
it against that HEAD passes it, and the gap falls between the two packages. `0248` is the
neighbouring but different one: the probe's `Riegel` ledger, not the header.

`haengt_an` is `0245` for the serialisation only: both write this file, and `0245` may
still come back `zurueck`.

## Acceptance

1. **The list is true at your HEAD.** The barrier in front of the addition of the
   Zustimmung rule is named at the same altitude as the entries already there -- module
   and path, no line number and no site count (`0245`'s condition 2 stands word for word).
   The counting word at `:309` is right for what the list then holds, and no entry claims
   a path that cannot fire. Read `kern/src/schritt.cpp` at your HEAD before you write.

2. **Say in one sentence what makes an entry of this list go stale, and whether prose is
   the right carrier.** Four packages now: `0197` left a false sentence, `0233` deleted it,
   `0245` repaired the enumeration, `0240` broke it the same night -- and `0245` had
   already banned line numbers and site counts, so altitude was not the cure. What moved
   was the module. Either write down why the module is stable enough to name, or name the
   place that *is* checked -- the `Riegel` ledger of `schritt_probe.cpp` and the category
   `0248` proposes -- and let the header point at it instead of restating it. Both answers
   are acceptable; a fifth nachzug without an answer is not.

Not in scope: `kern/src/schritt.cpp`, `schritt_probe.cpp`, and the barriers themselves. If
the list cannot be made true without changing the source, that is a finding and a package
of its own.
