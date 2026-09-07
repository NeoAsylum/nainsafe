---
typ: pruefung
paket: 0188-zahlwortriegel-fuer-reihentoml
pruefer: test-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: All three conditions, against the runner's report of 2026-09-07 (workspace ctest 20/20, standalone 2/2, profile ON), a hand recount of reihen.toml, and code reading; the two run-proofs no agent can produce since the shell ban are findings 1 and 2.
befunde: 3
---

# Pruefung 0188 — the probe proves its own red cases on every run

This run had no shell. The measurement rests on runner-produced files plus hand
execution of the code against the real data; where the criterion demands a run
nobody can produce anymore, that is a finding below, not a silent pass.

## Condition 2 (red on divergence) — proven by machine

The builder folded all three red demonstrations into a self-test that runs
**before every verdict** (Tafel 3 in `befunde/messung-0099/zahlwoerter.py`):
(a) number word bent at its measured position, must go red exactly at `nennung`
with the bent word read back; (b) leaf value with the mark appended, count must
grow by exactly one rest entry, red at `nennung` and `zerlegung`; (c) blob
`d18ca19`, must show genannt 7 vs gezaehlt 8 and go red, fetched via `git
cat-file` without an intermediate file. Any miss exits 2 → test fails. Both
green runs of 2026-09-07 (`befunde/uebersetzung-2026-09-07.md`, workspace test
20/20 Passed; `werkzeuge/zahlwort/bau/Testing/Temporary/LastTest.log`, 10:31,
standalone 2/2) are therefore machine proofs of all three red cases. The only
red exit path prints "Zeile %d: '%s' nennt %d, gezaehlt sind %d" — word, both
numbers, line, as demanded. Anchor lines in the output (152, 305, 307–308)
match my own reads of the file.

## Counting side — hand recount

8 leaf values with the mark, lines 373, 580, 804, 813, 1595, 1607, 1751, 1940 =
2 `beleg` (1607, 1751) + 1 `datei.vorlagen.einheiten` (373) + 5 rest
(widerspruch.8.lang, reihe.2.offen.0, reihe.2.umrechnung.0.begruendung,
reihe.13.offen.2, pruefweg.toml_geprueft). `[datei.vorlagen]` has exactly 6
keys (368–373). Matches prose and run output.

## Condition 3 (no red on history) — proven

Separation is argued in the script head (word-sequence anchors, not markup or
line numbers). The TRENNFAELLE quote the file verbatim — checked 152–160,
305–308, 328–332, 360–362 against the file. Uniqueness: "zerfallen" and
"genannt wird" occur once each in the whole file; every other "Stand der" hit
sits inside a TOML value, which `bloecke_von` never reads (full-line comments
only). Bestand green in profile ON, see above.

## Condition 1 — proven except two run-proofs

`add_test` is unconditional, present in the workspace ctest (test #20); guard
`if(NOT EXISTS …) message(FATAL_ERROR …)` names the expected path and is
form-identical to the proven guard in `werkzeuge/schlussriegel/CMakeLists.txt`
(0133 lesson).

## Findings (to the Projektmanager, not the builder)

1. **"In beiden Bauprofilen" is proven nowhere.** Every section of the nightly
   reports 2026-09-06 and -07 configures `FABRIK_SANITIZER=ON`; no OFF run of
   `zahlwort_reihen` exists, and since the shell ban of 2026-09-06 no agent can
   produce one. Statically the test is profile-independent (the switch only
   touches the C++ target's options). Standing fix proposed as package 0208.
2. **The bait run ("Lauf mit umbenanntem Skript") never happened** — the
   CMakeLists comment (line 104) says the build run had no shell. Statically
   closed: even a broken guard fails loud, because `add_test` is unconditional
   and python3 on a missing file exits nonzero. To produce the demanded proof
   (needs a shell, ~2 min): rename `zahlwoerter.py`, run `cmake -S
   werkzeuge/zahlwort -B <leer>`, expect abort naming
   `befunde/messung-0099/zahlwoerter.py`, rename back.
3. **Meldung, no package:** the extra guard on "Diese acht" (line 307) drops
   silently if "Diese" is reworded to "Die"; and the key paths enumerated in
   the same paragraph (lines 303–315) are unguarded prose — a same-count swap
   keeps the riegel green while the names rot. Same class as 0194, but which
   backtick tokens count as claims is a design question 0180 explicitly
   deferred.

Searched and not found: a second anchor occurrence; a bestand mutation the
self-test would miss; a lowered threshold or removed assertion.
