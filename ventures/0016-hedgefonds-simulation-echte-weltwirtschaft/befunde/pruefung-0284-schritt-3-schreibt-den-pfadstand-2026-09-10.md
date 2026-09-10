---
typ: pruefung
paket: 0284-schritt-3-schreibt-den-pfadstand
pruefer: kern-pruefer
datum: 2026-09-10
urteil: geprueft
kriterium_geprueft: the one open half of condition 6 (bezeichner_riegel green) against befunde/uebersetzung-2026-09-10.md, and conditions 1-5 and 7 re-anchored line by line to prove the Ruecklauf changed nothing else
befunde: 0
---

# The comment lost the identifier, and nothing else in the file moved

## The return item is closed

`bezeichner_riegel` was red on 2026-09-09 with one finding, `werte.hpp` line 218,
`daten_pruefsumme` (report 2026-09-09 `:528-532`). Today it is `Passed` twice --
aggregate run `:99`, own tree `:453`. Nothing tonight touched
`werkzeuge/bezeichner/`, so the green comes from the file, not from the riegel.

`werte.hpp:218-223` now reads *"Bewacht wird der Inhalt stattdessen beim Laden von der
Pruefsumme, die T22 im Kopf der Partiedatei fuehrt -- dort „daten_pruefsumme" genannt,
in Anfuehrung und nicht in Rueckwaerts-Anfuehrung, weil es ein Feld jener Datei ist und
kein Name des Kerns"*. The claim is still the spec's:
`specs/.../technik.md:6073` -- *"What guards `pfadstand` instead is `daten_pruefsumme`
at load (T22)"*. Content kept, identifier claim dropped.

## The whole edit, in two numbers

`zahlwort_riegel` prints every anchor line of `werte.hpp`. Yesterday against today:

| | 2026-09-09 | 2026-09-10 |
|---|---|---|
| blob | `9e24b723` | `6d674ae9` |
| anchors 2, 6, 15, 16, 25, 32, 32, 46, 92, 185, 204 | same | same |
| `pfadstand` declaration | 265 | **268** |
| anchors after it | 269, 586 | **272, 589** |

Every anchor up to 204 identical, every anchor from 265 shifted by exactly +3. The run's
only edit to `werte.hpp` is three added lines between 204 and 265 -- the doc block of the
new field, exactly where the Ruecklauf pointed. No second edit hides in this file.

`schritt.hpp` and `schritt.cpp` did not move either: `SUMMIERTE_FELDER = 7` still at
`schritt.hpp:264`, `JAHRGANGSFELDER = 3` still at `:277`, the assert message at
`:279-285`, `schritt_3_politik` at `schritt.cpp:540-556` -- the same line numbers the
2026-09-09 review cites.

## Condition 6, the rest of it

Core tree ctest 14/14, `Code 0` (report `:293`): `schritt_probe` and `werte_probe` green.
`verlauf_probe` is green as well -- `0285` ran the same night, as planned; the expected red
did not have to be spent. The three positional `Konstanten` literals stop before the new
field: `werte.cpp:195-196`, `werte_probe.cpp:621-622`, `:1451-1459` (that third one carries
`durchgriff`, contrary to the criterion's wording, but ends there). `schritt::schritt(`
now has 17 call sites -- the 16 old ones plus the new probe's -- all compiling.

## Conditions 1-5 and 7, re-anchored

C1 `schritt_probe.cpp:1389-1433`: 275 into `mit_pfad.pfadstand[US][Leitzins]`,
`static_assert(musterwert(ZIEL) != PFADWERT_DER_PROBE)` at `:1401`, address read back at
`:1429`. C2 accessor `werte.cpp:591-619`, both bars, probe `werte_probe.cpp:2434/2440/2446`.
C3 `feldzahl<Konstanten> == 10` at `schritt_probe.cpp:2221` (static_assert) and `:2261`
(PRUEFE); the riegel counts the same ten independently (report `:123`). C5 `pfadstand`: 0
hits in `parameter.toml`, 0 under `daten/`. C7 nothing deferred.

## Where I looked and found nothing

**Determinism:** unchanged by construction -- the only edit is three comment lines.
`schritt_3_politik` iterates `LAENDER_ALLE` x `INSTRUMENTE_ALLE` in order, no float, no
unordered container, no second stream.

**Bounds:** the carrier's number goes into the address with no range check in the core.
That is not a finding: `instrument_min`/`instrument_max` are keys of `parameter.toml`, not
fields of `Konstanten`, so the core cannot hold that bound without growing the carrier and
the checksum -- which the package excludes by name. T40 puts the clamp at the caller,
check 2 bound 8 verifies after the round. **For whoever builds the `daten` driver:** it is
the last place that can name country and series for an out-of-range vintage row; after it,
the first thing that speaks is a `festkomma` abort inside step 5 (package `0288`).

## The one red on this package's file that is not a finding

`zahlwort_riegel` reports *"Funktionsdeklaration 'pfadstand' ab Zeilennummer 268 nennt
keine Nummer der Tabelle"* -- the same single finding as yesterday, only three lines
lower. The accessor carries no T48 number because it is no derived quantity; the riegel
lives under `werkzeuge/`, which condition 5 forbids the builder to write. `werte.hpp:40-48`
writes the case down and names proposal `0286`. Condition 6 does not ask for this test.
`belegstellen_wortabstand` and `multiplikationsriegel` belong to `0283` and `0290`.
