---
id: 0249-der-kopf-nennt-einen-riegel-der-nicht-mehr-feuern-kann
rolle: kernbauer
status: gebaut
ruecklauf: 1
haengt_an: []
vermerk_ruecklauf_1: "RUECKLAUF 1 of 3, project manager, 2026-09-08 (twelfth run), on `befunde/pruefung-0249-der-kopf-nennt-einen-riegel-der-nicht-mehr-feuern-kann-2026-09-08.md`, `urteil: zurueck`, 2 findings. `gebaut` -> `offen`. **The scope is two sentences and almost everything you built stands.** || **DISCHARGED, RE-DERIVED BY THE REVIEWER FROM THE SOURCES AND NOT FROM YOUR TEXT -- TOUCH NONE OF IT.** Conditions 1-4 hold. Your `Vier weitere` split (Vermerk (a)) was accepted on its merits: entry 2 names the live barrier in `kern::schritt`, entry 4 keeps the *uebrige* festkomma arithmetic and its three call sites verify (`mal_geteilt` `:741`, `realeinkommenshub` `:644`, `politiklast` `:596`). Both BIP aborts are named in the right order (`werte.cpp:731-746`, `schritt.cpp:628-641`). `die drei Schranken des Rahmens` (`:311`) is right -- Modus `:855`, Rundennummer `:874`/`:882`, Pruefsumme `:914`. No line number and no site count reached the header. Your deletion (c) was not challenged. || **FINDING 1 -- THE POINTER YOU ADDED FOR CONDITION 5 IS FALSE FOR THE VERY BARRIER THIS PACKAGE EXISTS TO NAME.** `schritt.hpp:348-351`: `das haelt das Riegel-Verzeichnis in kern/test/schritt_probe.cpp -- eine Kennung je Schranke, zu jeder in jedem Lauf eine angekommene Meldung, sonst faellt der Lauf. Wer wissen will, welche Schranke heute wirklich anschlaegt, liest dort und nicht hier.` **Both readings fail.** Narrow (`das Riegel-Verzeichnis` = `ALLE_RIEGEL`, `:357-360`, seven values, completeness loop `:2159-2171`): the guarantee is true but you send the reader to the half that **excludes entry 2** -- `summe_der_regel_pruefen` sits in the second registry `RIEGEL_OHNE_ZUSTAND` (`:432-464`), `von der Vollzaehligkeit ausgenommen` (`:2218-2221`), for which no message ever arrives and the run does **not** fall. Wide (both registries): `zu jeder ... eine angekommene Meldung, sonst faellt der Lauf` is simply false. **And it answers nothing for three of your four entries:** `kern::werte::bip`, `kern::werte::schaden` and `kern::festkomma` have no Kennung in either registry, because that ledger is scoped to `kern::schritt`. **This does not rest on commit order** -- the reviewer checked; at your own HEAD `summe_der_regel_pruefen` had no Kennung at all. || **WHAT TO WRITE INSTEAD, AND POINTING IS STILL THE RIGHT ANSWER -- IT IS THE SCOPE THAT IS WRONG, NOT THE MOVE.** Say what the ledger actually guarantees and for which entries: one registry carries the fall-if-missing guarantee, a second exists for barriers no state reaches and is exempt from it, and the ledger covers the barriers of `kern::schritt` only. Then `liest dort und nicht hier` must be scoped to the entries it can answer, or dropped. **Condition 5 asked you to point *instead of* restating; you pointed *and* restated, and the restatement is what went stale -- the same failure one level up.** || **AND A HAZARD THE REVIEWER COULD NOT SEE, WHICH IS MINE TO GIVE YOU: DO NOT NAME THE LEDGER'S FILE.** `0244` is open and lifts `Riegel`, `ALLE_RIEGEL`, `RIEGEL_OHNE_ZUSTAND` and `probe_kennzeichen_eindeutig` **out of `kern/test/schritt_probe.cpp` into `kern/test/kennzeichen.hpp`.** Our `dateien` lists are disjoint, so the planner may well run us the same night -- **and a path in your sentence would be false the moment that package lands.** Name the ledger by what it is, not by which file holds it today. This is the third time a sentence of this header has been falsified by an edit in a file the package did not own; `dateien` prevents overwrites, it does not prevent falsification. **Do not predict `0244`'s outcome either -- write the sentence so that it is true under both.** || **FINDING 2 -- the one entry whose abort actually fires is the one that does not say so.** `:311-313` promises every entry says `ob ein Zustand sie heute erreicht`. Entries 2, 3 and 4 answer; entry 1 says only `Beide Schranken werden jede Runde gerechnet, fuer jedes Land`, and **in this text's own vocabulary `gerechnet` is not `erreicht`** -- entry 2 separates the two in one sentence. **The fact you need, already measured, do not re-derive it:** entry 1's Nennerbedingung abort is the only one of the four that fires. `Riegel::Nennerbedingung` is in `ALLE_RIEGEL`, so `schritt_probe.cpp:1786` yields an arrived message in every green run. Say that in entry 1. || **NOT IN SCOPE, unchanged from the first round and it still holds:** `kern/src/schritt.cpp`, `kern/src/werte.cpp`, `schritt_probe.cpp`, and any change to a barrier. `schritt.hpp` alone. **Two sentences. Do not reopen the enumeration.**"
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

## Vermerk des Kernbauers, 2026-09-08

Built. `schritt.hpp` alone; no source touched. Three things the reviewer should weigh.

**(a) `Drei weitere` became `Vier weitere`, not `Drei` repaired.** Condition 1 said the
third entry names a dead barrier. Only its *addition* is dead: the body of step 5 still
reaches `kern::festkomma` through the elasticity line, and `realeinkommenshub` through
sign flip and division. So the located barrier out of `kern::schritt` is a **fourth**
entry, and the old third keeps everything except the addition. The group line that
assigned modules to entries (`die ersten beiden fuehren aus kern::werte heraus, der
dritte aus kern::festkomma`) is gone -- that line is what went stale, and every entry now
carries its own place.

**(b) Condition 5 answered by pointing, not by predicting.** The header names the `Riegel`
ledger of `kern/test/schritt_probe.cpp` and says nothing about which entries it holds --
`0248` is editing it in the parallel lane, and any sentence about its contents would be
the sixth nachzug on the day it lands.

**(c) One clause deleted beside the conditions.** The old first entry ended `-- die
Aussage ueber die eine bewegte Groesse weiter oben ist genau so falsch geworden`. True,
but it is the same argument the new closing paragraph now makes with a fresher instance
(`0240`), so it went as repetition. If the reviewer wants it back, it belongs in the
closing paragraph, not in an entry.

## Vermerk des Kernbauers, Ruecklauf 1, 2026-09-08

Two sentences, `schritt.hpp` alone. Nothing of the enumeration reopened.

**Finding 1 -- the pointer.** The ledger is now named by what it is (`Riegel`-Verzeichnisse
der Testschicht, `ALLE_RIEGEL`, `RIEGEL_OHNE_ZUSTAND`) and **no path appears**, so `0244`'s
move cannot falsify it. The guarantee is stated per registry, not once for both: message
required in every run for the first, exempt and never-arriving for the second. And the
answer is scoped per entry -- only the two aborts out of `kern::schritt` have a Kennung at
all; `liest dort und nicht hier` now holds for those two, and the other two are sent to the
source.

**What I did not claim, deliberately.** I wrote nothing about the ledger's overall scope
("`kern::schritt` only" is not quite true -- `StartwertSetzen` and `StartwertBinden` are
`kern::zustand`). The header states only which of *its own four entries* the ledger
answers for, which is what condition 5 needs and is stable under both `0244` outcomes.

**Finding 2 -- entry 1.** `erreicht` now said in the text's own vocabulary, with the state
that walks in (value added nowhere positive) and the consequence in the ledger (a message
arrives every green run). No test name, no file, no line.
