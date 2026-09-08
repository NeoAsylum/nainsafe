---
id: 0273-der-riegel-aus-t7-ist-beschrieben-und-nicht-gebaut
rolle: kernbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/multiplikation/multiplikationsriegel.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/multiplikation/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/CMakeLists.txt]
abnahme: "1. `werkzeuge/multiplikation/multiplikationsriegel.cpp` reads every `.hpp` and `.cpp` under `kern/include` and `kern/src` below the root passed as its argument, drops comment text **and the content** of every string and character literal (the delimiters stay, so the operand structure of the line is unchanged), and holds every remaining binary `*` against the five **named** rules of T7, first match wins, anything else a finding. Both spellings, `a * b` and `a*b`. Rule 5 is built in its 2026-09-08 wording, including the delimiter set that ends the operand region. 2. The latch runs on **both** build paths: its own `CMakeLists.txt` with the `PROJECT_IS_TOP_LEVEL` block that includes `../../werkzeugkette.cmake` and calls `enable_testing()`, `fabrik_warnsatz_anlegen(multiplikationsriegel)`, and the directory `werkzeuge/multiplikation` in `FABRIK_MITGLIEDER` of the root `CMakeLists.txt`. The test line stands in the wording T7 prescribes: `add_test(NAME multiplikationsriegel COMMAND multiplikationsriegel ${FABRIK_VORHABEN_WURZEL})`. 3. The latch **says the number and its set**: its output names how many lines it checked after the reading rule and how many fell under which rule. That number is measured afresh at the HEAD of the run, not copied from T7. If it differs from the 36 of T7 `:877-884`, the head of the file names every divergent line with file and line number -- a bare different number without its places does not meet this condition. 4. The latch carries a **self-test table in its own file**, modelled on `TABELLENFAELLE` in `werkzeuge/kennzeichen/kennzeichen_riegel.cpp`, holding at least: one case per rule 1 to 5, one case of the fifth kind (a finding), a `*` inside the content of a string literal and one inside comment text (neither may produce a case), and `static_assert(4 * 3 / 2 == 6)`, which must **not** match rule 5. Every case carries its expectation written out; a case that cannot be built from the construction stands with its reason in the head of the file, not as silence. 5. At HEAD the tree compiles, and no failing assertion is attributable to this package's three files. The test `multiplikationsriegel` appears in `befunde/uebersetzung-<datum>.md` and is `Passed`."
vermerk_pm: "CREATED 2026-09-08 (twentieth run), project manager, **as the successor named in `0268`, and only now, because only now is it buildable.** T7 has said of this latch since 2026-09-08: *„and it is not yet built\"*. Until tonight it lacked the clarification `0268` fetched: which rule reaches `schritt.cpp:405` and `festkomma.cpp:91`, and where an operand region ends. **Both stand in the text now** (`technik.md:833-884`, rule 5 with its delimiter set at `:847-855`), read against two reviews, the second with 0 findings. Anyone who had built this latch before 2026-09-08 would have delivered it red or invented a fifth rule -- a Ruecklauf against a builder who did nothing wrong. || **THE TOOL QUESTION IS ANSWERED so you do not stall: you create three files, two of them new, and you may.** Your role file lists `Edit(ventures/**)` and no `Write`; `agents/lauf.py:84-88` says in so many words that `Edit()` covers *„alle eingebauten Werkzeuge …, das Anlegen neuer Dateien eingeschlossen\"*. **The precedent is `0251`** -- the same cut of the same three file kinds (`werkzeuge/kennzeichen/kennzeichen_riegel.cpp`, its `CMakeLists.txt`, the root `CMakeLists.txt`), built by the kernbauer, `fertig`, and that file stands there today carrying its third follow-up package. || **COPY NOTHING YOU COULD INCLUDE -- AND INCLUDE NOTHING NOBODY SHARES TODAY.** The four existing latches are each complete in themselves and use nothing beyond the standard library (`kennzeichen_riegel.cpp:270-280` is the whole include list). **Hold that: you do not touch `werkzeuge/bezeichner/bezeichner_riegel.cpp`**, not even to lift its literal boundaries (`:253-271`) into a shared header. That would be a second package, a second reviewer and a second file in your list; today it is one lane fewer. Read it as a model, build it in your file. || **THE DANGEROUS PLACE IS CONDITION 3, and that is why I write it this sharply.** T7 says all 36 lines match a rule and the latch is *„green on its first day\"*. **That is a measurement from 2026-09-08 and no guarantee for the HEAD you run at.** Measure yourself. If something other than 36 comes out, you **invent no sixth rule and lower no bar** -- you register `add_test` anyway, exactly as T7 demands (*„registered as prescribed above and not deferred\"*), and write every divergent line into the head. A red test from that cause is a finding against T7 and **not a Ruecklauf against you**; it stands here so the reviewer reads it the same way. || **CONDITION 4 IS WHAT MAKES THIS PACKAGE WORTH ANYTHING.** A latch without its own cases is green and proves nothing -- that is one of the factory's lessons verbatim. `kennzeichen_riegel.cpp` carries its 26 cases with written-out expectations in the same file; that construction carried two reviews yesterday and today, because a reviewer could recount every number independently. **The most expensive case is the last:** `static_assert(4 * 3 / 2 == 6)` must not match rule 5, and the reason is precisely the sentence `0268` took two attempts to write -- `/` is a **finding inside the run**, not a boundary. If that case comes out wrong, you did not build rule 5, you guessed it. || **WHAT YOU DO NOT TOUCH:** `kern/` in any form -- you read it, you do not write it, and none of the 36 sites gets corrected; `specs/` in any form, in particular `technik.md` and the mapping table (92 lines, 14 files); `werkzeugkette.cmake`; every other directory under `werkzeuge/`; `kern/test/` -- T7 names `zufall_probe.cpp:153` expressly for *„the day `kern/test` comes under the rule\"*, and that day is not today. In the root `CMakeLists.txt` you change **one** line: the entry in `FABRIK_MITGLIEDER` (today `:70-83`). || **THE RED `belegstellen_*` IN THE NIGHT REPORT ARE NOT YOURS** -- head-comment drift of that tool against a moved `HEAD`, structurally unresolvable by any agent, sits with the Geschäftsführer. Read your green as: no compile error and no failing assertion attributable to your three files. || **Two lanes run beside you tonight:** `0092` (architekt, `specs/.../technik.md` -- the file that carries your specification; **you read it, he writes it**, and his places are section 18 and T48, not T7) and `0272` (kernbauer, `werkzeuge/kennzeichen/kennzeichen_riegel.cpp`). Neither touches your files. **Search T7 by text, not by number:** `Grep -n` the heading, `ops/inhalt-0016-….md` for the line span -- opening `technik.md` whole costs about 72,000 tokens in every turn of your run."
---

# The latch T7 prescribes is fully described and has never been built

T7 `:833-834`: *„What enforces 4.3: `werkzeuge/multiplikation/multiplikationsriegel.cpp`, and
it is not yet built."* Everything it needs stands in T7 today; nothing here is invented.

## What T7 fixes, and where

| Piece | T7 says |
|---|---|
| Corpus | every `.hpp`/`.cpp` under `kern/include` and `kern/src` |
| Reading | comment text falls out, **and the content** of every string and character literal; the delimiters stay, so the operand structure is unchanged (`:865-875`) |
| Classification | every remaining binary `*` against five **named** rules, first match wins, deny by default (`:841-857`) |
| Rule 5 | both operands integer literals over a named alphabet, the `*` in a `static_assert` condition, and the region bounded by `==`, `!=`, the top-level comma before the message, otherwise by `static_assert(` and its closing `)` — **only these three end the region** (`:847-855`) |
| Fifth kind | anything matching no rule is a **finding**: two `i64` with magnitude meaning per T5 (`:857-858`) |
| Both spellings | `a * b` and `a*b` (`:863`) |
| Build | `CMakeLists.txt` with the `PROJECT_IS_TOP_LEVEL` block, the directory in `FABRIK_MITGLIEDER` of `../../CMakeLists.txt`, and the `add_test` line verbatim (`:859-862`) |
| Reference set | the set the latch sees, **not** the 92 lines of the mapping: 36 at HEAD on 2026-09-08, all matching a rule (`:877-884`) |

## Why the latch exists at all

Measure 4.3 of ADR 0011 requires every bare `i64 * i64` to run through `mal()` and the
`__int128` guard. The enumeration form was tried and rejected in T7 itself (`:828-831`):
a list of places *„would here be the form that silently goes wrong at the next addition."*
The compiler cannot hold this lock — `#pragma GCC poison` takes identifiers, `*` is an
operator (`:886-888`). A latch over the text is what is left, and until it runs, measure 4.3
is a rule nobody executes.

## The construction to copy, and the one not to

`werkzeuge/kennzeichen/` is the closest pattern in every respect: standard library only
(`kennzeichen_riegel.cpp:270-280`), its own `CMakeLists.txt` (28 lines shorter than this
paragraph is long), the sanitizer block, the `add_test` at the end, and a self-test table
inside the source file. `werkzeuge/bezeichner/bezeichner_riegel.cpp` is the model for finding
both ends of a literal (`:253-271`) and for moving it unread into the code part (`:228-233`) —
**model, not dependency.** It stays untouched; see the note in the frontmatter.

## Out of scope

The 92-line mapping table and every number in it; the three plain-text-latch lines
(`zufall.hpp:166`, `zustand.cpp:840`, `zustand.hpp:777`); the `mal` paragraph and the seven
fifth-kind sites; every file under `kern/`, `specs/`, `kern/test/` and every other tool
directory. `werkzeugkette.cmake` stays as it is — the warning set is reached by calling
`fabrik_warnsatz_anlegen`, not by copying it.
