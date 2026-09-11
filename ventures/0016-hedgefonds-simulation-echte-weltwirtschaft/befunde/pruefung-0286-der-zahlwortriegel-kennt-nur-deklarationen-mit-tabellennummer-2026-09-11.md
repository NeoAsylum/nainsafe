---
typ: pruefung
paket: 0286-der-zahlwortriegel-kennt-nur-deklarationen-mit-tabellennummer
pruefer: kern-pruefer
datum: 2026-09-11
urteil: geprueft
kriterium_geprueft: "All five conditions traced to source lines plus the green ctest line of 2026-09-11; the declaration and number counts of `werte.hpp` recounted by hand."
befunde: 2
---

# The green run itself proves the Markenprobe ran

## Condition 1 -- green, and green through a third kind

`uebersetzung-2026-09-11.md`: `zahlwort_riegel .... Passed 0.06 sec` (test #27, and #1 of
the `werkzeuge/zahlwort` tree). Blobs in the same report: `werte.hpp` `e6edd482`, riegel
`44b53174`, HEAD `475f971` -- both files clean in `git status`, so the report measures
today's text.

Green *through the third kind*, not through rewording: `ZAEHLMARKE` at `:259`, the branch
at `:899-919`, exit 1 for the Mangel via `:1033` + `:2134`. The cheap trap named in the
package was not taken -- a grep for `T48 Nr. [0-9]+` over `werte.hpp` returns 24 hits, none
of them between `:257` and the `pfadstand` declaration at `:273`.

## Condition 2 -- declared, and each kind has a case

`dok.find(ZAEHLMARKE)` (`:899`) requires the wording; "weder noch" stays a Mangel (`:909`,
`:916-917`). The head states the spelling at `:56` -- character-identical to `:259`. Cases:
number only `ZAEHLTEXT_EINFACH` (`:1601`), mark only `ZAEHLTEXT_MIT_MARKE` (`:1673`),
neither `ZAEHLTEXT_OHNE_NUMMER` (`:1628`, expects `maengel=1`), plus the contradiction
`ZAEHLTEXT_MARKE_UND_NUMMER` (`:1684`). Nine cases, `std::array<Zaehlfall, 9>`.

## Condition 3 -- 22, recounted by hand

24 declaration lines in `namespace kern::werte` (`:273` `pfadstand`, then `:300, 305, 310,
315, 319, 324, 334, 343, 347, 352, 364, 375, 388, 404, 414, 432, 448, 471, 495, 514, 530,
567, 607`). 23 `T48 Nr. <n>` sit in their doc blocks, one per declaration except
`pfadstand`; Nr. 11 twice (`:354`, `:367`), so 22 distinct. The 24th hit, `:154`, is a field
comment inside `struct Konstanten` and does not count -- the case `ZAEHLTEXT_NUMMER_IM_FELD`
(`:1658`) holds that. `werte.hpp:32` reads "Zweiundzwanzig Groessen in vierundzwanzig
Deklarationen"; both halves match the count.

## Condition 4 -- the exit code carries the proof

Mutant 1: `deklarationen_nachher == vorher + 1` (`:1202`), maengel unchanged (`:1207`),
return 2 at `:2030`. Mutant 2: `marken` down by exactly one (`:1351`), `maengel_nachher ==
maengel_vorher + 1` (`:1356`), return 2 at `:2056`.

The chain that settles it without a build: `marken == 0` would mean `pfadstand` carries no
mark, hence a Mangel, hence exit 1 -- so green implies `marken >= 1`, hence
`mp.gegenstand == true`, hence the probe was **not** skipped and passed. Green also implies
`befunde` empty (`:2117-2121`), so `maengel_vorher == 0` and "one more" is exactly one.

## Condition 5 -- werte.hpp

Functionally the mark alone (`:257`); the head gained prose about it (`:40-49`). `:32` names
the counted number, verified above.

## Finding 1 -- the printed `marken` count cannot reach the night report

`:677-681` says the count is printed "damit der Fall der Marke im Nachtbericht sichtbar ist
und nicht bloss nicht mehr meckert". ctest prints stdout only on failure, so the summary at
`:2074-2088` appears in the report exactly when the riegel is red. Evidence in this very
report: `zahlwort_riegel .... Passed` with no output, while the two failing tests print
theirs in full. Non-blocking -- no condition asks for it -- but the sentence promises a
visibility the mechanism does not deliver.

## Finding 2 -- the Markenprobe takes the first occurrence in the whole file

`ohne_zaehlmarke` (`:1299`) searches `text`, not the counted namespace region. How to
produce the failure: write the mark's exact wording into `werte.hpp`'s own head -- `:48`
today says "erklaerter Zaehlmarke im Kommentar" and quoting it exactly is the obvious next
edit, since the riegel's head does so at `:56`. The mutant then strips the head quote,
`pfadstand` keeps its mark, `nach.marken + 1 != bestand.marken` at `:1351` holds, and the
riegel exits **2** on a correct file -- with the message "der Riegel liest ihren Wortlaut
nicht dort, wo er ihn zu lesen glaubt", which is the wrong diagnosis. Proposal `0303`.

## Where I looked and found nothing

Non-determinism grep over `zahlwort_riegel.cpp` (`float`, `double`, `unordered`,
`std::map`, `rand(`, `time(`, `chrono`, `reinterpret_cast`, `uintptr`): 0 hits; `nummern`
is a `std::set`. The mutant of `mit_weiterer_stelligkeit` (`:1082-1084`) inserts a doc block
with a number and no mark, so it cannot bring its own Mangel -- which is what `:1207`
demands. `0298` already owns the missing Teil-C mutant of the Markenprobe and the `A2`
wording; not re-proposed.
