---
id: 0301-das-partieformat-hat-noch-keinen-schreiber
rolle: kernbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/schnittstelle/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/schnittstelle/include/schnittstelle/partie.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/schnittstelle/src/partie.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/schnittstelle/test/partie_probe.cpp]
abnahme: "1. **The member builds.** `schnittstelle/CMakeLists.txt` exists, so the root `CMakeLists.txt:86-92` stops skipping it, and the next nightly report lists `schnittstelle` among the built members instead of among the five that are not. Its probe is a `ctest` entry named `partie_probe`. The root file is **not** edited -- it already adds any member that has a `CMakeLists.txt`. 2. **A record type carries the eight T22 fields and no ninth**: `schema_version`, `jahrgang_id`, `modus`, `daten_pruefsumme`, `parameter_pruefsumme`, `startwert`, `aktionen` as pairs of round and `kern::aktion::Aktion`, `end_pruefsumme`. One case enumerates the eight field names and fails if a field is added without being enumerated. 3. **`schreibe(partie)` returns the record as one line of JSON**, field order exactly the order of condition 2, no whitespace outside strings, integers without thousands separators. One case holds the whole returned line against a written-out expected string for a hand-built record with two actions -- byte for byte, not a substring search. 4. **The same record written twice gives the same bytes**, and one case proves the writer reads nothing outside its argument: two records differing in exactly one field give lines differing in exactly that field's value. 5. **`parameter_pruefsumme` is the real one.** The field is filled by `kern::schritt::parameter_pruefsumme(konstanten)` in at least one case, not by a literal, so the format carries the checksum the core computes rather than a number beside it. 6. **A record with an empty action sequence writes `\"aktionen\":[]`** and stays valid -- that is the save of a game before round 1 and the case that a length-prefix format would have failed."
---

# T22 names the save format, and nothing writes it

`technik.md` section 6, **T22**: *A save is vintage, mode, seed, action sequence and
checksum, not the state.* The file shape is written out there in full, and the three wins
it buys are written out too -- the buyer notices a determinism error first, the regression
corpus **is** the save folder, and a file stays under two kilobytes.

`schnittstelle/` does not exist. It is one of the five members the nightly report lists as
"noch nicht gebaut" (`befunde/uebersetzung-2026-09-10.md:20-24`), and the plan of
2026-09-10 names those five as the bottleneck.

## What this package builds, and the half it deliberately leaves

**It builds the writer. It does not build the reader.**

The parse half and the recompute-on-load half of T22 -- *on loading, the game is recomputed
and the checksum compared; if it deviates, the program reports a determinism break instead
of playing on* -- are a second package and a larger one. A JSON **writer** for a fixed
eight-field schema is a bounded afternoon; a JSON **parser** that has to reject malformed
input is not, and `Grep` over `kern/` on 2026-09-11 found no JSON anywhere in the tree, so
neither half can borrow one.

Cutting it the other way round would not work: a reader with nothing to read is untestable.
The writer's output is the reader's fixture.

## Why the inputs exist

The question that kept `daten` uncut for four runs -- does anything in the tree produce this
member's input? -- is answered here without a gap:

- `kern::aktion::Aktion` and its canonical order: built, green.
- `kern::schritt::parameter_pruefsumme(konstanten)`: built, `schritt.hpp`, `constexpr`.
- `kern::zustand::pruefsumme_von(zustand)`: built, `zustand.hpp`, supplies `end_pruefsumme`.
- `jahrgang_id`, `modus`, `daten_pruefsumme`, `startwert`: **carried, not computed.** The
  format transports them; filling them is the vintage's job (`0297`, `gebaut`) and the
  `neu` command's. That is what makes this package independent of the vintage.

## Not in scope

Parsing, loading, the determinism-break message, the T21 command loop, standard input, and
any other reply than the save record. A builder who writes a parser here has written two
packages and will be sent back for the second one.

## Vermerk des Projektmanagers -- 2026-09-11

**Lane:** `schnittstelle/` has no files at all, so this package collides with nothing, now
or tonight. It needs no edit to the shared root `CMakeLists.txt` -- lines 86-92 add any
member whose own `CMakeLists.txt` exists, which is why a new member is the cheapest lane in
the repo and why two of them are cut in the same run.

**Role:** `kernbauer`, because no role file names a directory and its permit is
`Edit(ventures/**)`; the precedent is `0297`, where `datenbauer` opened `daten/` the same
way. If the Geschaeftsfuehrer means `schnittstelle` to belong to another gewerk, this is the
run to say so -- the member is opened exactly once.

The evidence for all six conditions lives in `schnittstelle/test/partie_probe.cpp` except
condition 1, whose evidence is the next nightly report; both are named above.
