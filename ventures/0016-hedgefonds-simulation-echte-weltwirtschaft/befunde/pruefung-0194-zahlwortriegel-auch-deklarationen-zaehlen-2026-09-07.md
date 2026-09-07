---
typ: pruefung
paket: 0194-zahlwortriegel-auch-deklarationen-zaehlen
pruefer: test-pruefer
datum: 2026-09-07
urteil: zurueck
kriterium_geprueft: Red proof and green-on-Bestand verified at source and by the runner's executed ctest runs at HEAD; the clause "beide Bauprofile" has evidence only for FABRIK_SANITIZER=ON
befunde: 1
---

# Pruefung 0194 -- the Zahlwort before "Deklarationen"

## What is fulfilled, and how I checked it

**Independent count of `werte.hpp` (by hand, at source):** 22 T48 numbers in 23
declaration statements (Nr. 11 twice), 8 fields in `struct Konstanten` = 2 Jahrgang +
6 Schluessel. Line 32 claims 22 and 23; both halves correct. All 11 noun sites traced;
the mute ones (lines 6, 15, 25, 474) stay mute under the window/article rules.

**Executed evidence (runner, 2026-09-07 10:31, HEAD):**
`werkzeuge/zahlwort/bau/Testing/Temporary/LastTest.log` shows the 0194 binary
(self-test 9/20/8/7/9 cases; the 0180 state was 9/18/8/7/6 per `messung-0180/lauf.txt`).
Its Empfindlichkeitsprobe ran the exact red case of the abnahme against the real file:
"zaehlt der Riegel **24 statt 23** Deklarationen und meldet **1 statt 0** Abweichungen
der Sorte 'Deklarationen'", Sorten 1 and 2 unchanged, Nummernmenge unchanged. Bestand
green: line 32 "'dreiundzwanzig' nennt 23, gezaehlt 23". Same on the workspace path
(`bau/Testing/Temporary/LastTest.log:1156-1158`; test 19/20 Passed -- the one red test
there, `belegstellen_riegel`, is a pre-existing failure outside this package).

**Kill-switches traced (no shell this run, so traced, not built):** nail `urteil()`
green -> probe demands more Sorte-3 red, exits 2; bind Sorte 3 to `nummern.size()` ->
Bestand red (23 != 22), exits 1, and Verdrahtungsfall 9 rips; kill the declaration
count -> probe's +1 condition fails, exits 2; drop the `Deklarationen` nomen ->
Behauptungsfall 12, the `behauptungen_deklarationen == 0` guard and the probe all trip.
Verdrahtungsfaelle 8/9 run on a head with 2 numbers in 3 declarations, so swapping the
two counts cannot stay green. Old tables are purely additive (18->20, 6->9 cases;
none removed, no threshold lowered -- held against `messung-0180/lauf.txt`). The
probe's inserted comment carries none of the three nouns, so it stages no finding of
its own. `werkzeuge/zahlwort/CMakeLists.txt` untouched, as the vermerk required.

## Befund 1 -- why `zurueck`: no OFF-profile run of this state exists

The abnahme says "beide Bauprofile". Every artifact of the 0194 state is
`FABRIK_SANITIZER=ON`: both CMakeCaches (`bau/`, `werkzeuge/zahlwort/bau/`) say ON,
the Uebersetzungsberichte of 2026-09-06/07 contain no OFF run, and no messung of this
state exists. The clause is live, not formal: an OFF-only compile failure has happened
here before (`befunde/messung-0108/bauwege-isoliert.py`: "Eine davon uebersetzte im
Profil FABRIK_SANITIZER=OFF nicht"), and `-Werror` makes any profile-specific warning
fatal. The identical clause in 0180 was fulfilled by measurement (pruefung-0180, both
profiles). To produce the missing evidence -- one run, no code change expected:

    cmake -S werkzeuge/zahlwort -B <tree> -DCMAKE_BUILD_TYPE=RelWithDebInfo \
      -DCMAKE_CXX_FLAGS="-fwrapv -fno-fast-math" -DFABRIK_SANITIZER=OFF
    cmake --build <tree> && ctest --test-dir <tree>

Expected: `zahlwort_riegel` Passed with the same Nachlass (24 statt 23). If that is
green, the criterion is fulfilled without touching the package's file. I could not run
it: this session has no shell, and the runner builds ON only.

**To the Projektmanager:** no standing mechanism produces OFF evidence -- every
"beide Bauprofile" clause currently depends on a shell-bearing session. Options: an
OFF pass in the baulauf, or folding one OFF build into the 0199 Nachziehen of
`messen.py`. Where it lands is a scheduling decision, not mine.

## Where else I looked and found nothing

Weakened tests (none -- additive vs 0180), self-staged probe findings (none), the
commit's file list (not checkable without git; working tree is consistent with the
one-file `dateien` list).
