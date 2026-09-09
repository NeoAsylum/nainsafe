---
typ: pruefung
paket: 0284-schritt-3-schreibt-den-pfadstand
pruefer: kern-pruefer
datum: 2026-09-09
urteil: zurueck
kriterium_geprueft: all seven conditions read against the tree and against befunde/uebersetzung-2026-09-09.md (HEAD e6924bf, the package's own commit); 1-5 and 7 hold, 6 does not
befunde: 3
---

# Step 3 writes, and the only full-partie test dies

**What holds.** C1: `probe_pfadstand_geht_in_die_runde` (`schritt_probe.cpp:1389`) puts 275
into `mit_pfad.pfadstand[US][Leitzins]`, asserts at compile time that it differs from
`musterwert(ZIEL)` (`:1401`) and reads the address back at `:1429`; the head names the line
that goes red at `:1354`. Not zero-filled. C2: `:1433`, plus the three abort cases at
`werte_probe.cpp:2434/2440/2446`. C3: `SUMMIERTE_FELDER = 7` (`schritt.hpp:264`),
`JAHRGANGSFELDER = 3` (`:277`), both test numbers read 10 (`schritt_probe.cpp:2221`
static_assert, `:2261` PRUEFE), `SCHLUESSELFELDER` still 7 entries (`:1974`). C4:
`schritt.hpp:150-152`, `:205` ("zehn Felder"), `:279-285`; `:179` untouched. C5:
`parameter_pruefsumme` still seven `nimm_i64` (`schritt.hpp:165-176`), signature unchanged
(`:385-386`), `pfadstand` in no file under `daten/` and not in `parameter.toml`. C7: nothing
deferred silently. Determinism of `schritt_3_politik` (`schritt.cpp:540-556`): ordered
`LAENDER_ALLE`/`INSTRUMENTE_ALLE`, no float, no unordered container, no address arithmetic.

## Befund 1 -- condition 6 fails: `verlauf_probe` aborts (kern 14/14 -> 13/14)

How to produce it:

1. `verlauf_probe.cpp:120` is `constexpr Konstanten KONSTANTEN_DER_PROBE{}` -- `pfadstand`
   all zero.
2. `ausgangslage` (`:284-285`) fills all 310 addresses with `musterwert(platz)`, cycling
   `{0, 1, -1, 10'000, -10'000, 123'456'789, I64_MAX, I64_MIN}` (`:214-222`). Most of the
   twelve path-instrument Stand addresses therefore hold something other than zero.
3. Step 3 now writes zero there, so `schrittrichtung` (`schritt.cpp:611-620`) is no longer 0
   and `politiklast` (`:633-646`) calls `werte::schaden` for the first time in a real round.
4. One of the unguarded `festkomma::plus` calls in that trunk -- `schritt.cpp:643`,
   `werte.cpp:834-835` (`handelsvolumen`, reached via `schaden(Zoll)`), `werte.cpp:1075` --
   overflows on those pattern values. `festkomma.hpp:203` throws
   `std::domain_error("plus: Summe ausserhalb von i64 (T7)")`, nothing catches it, the
   process terminates. It is one of these and not `bip` or `schritt.cpp:802`: both abort
   with their own located message first.

Report `:308-310`: `Test #9: verlauf_probe ... Subprocess aborted***Exception`, message
quoted verbatim. Before this package `richtung == 0` everywhere and `schaden` was never
reached. `ops/plan.md:9-12` records kern 14/14 green on 2026-09-08, and 0284 is the only
commit of this run that touched `kern/`.

The builder saw the boundary -- `schritt_probe.cpp:1365-1373` records that the Musterlage
carries `I64_MIN` as Staatsschuldquote for two of four countries and picks the US to dodge
it -- but `verlauf_probe.cpp` is not in `dateien:`, so he could not make the same move
there. **That conflict is the project manager's:** condition 6 demands a green
`verlauf_probe` and the file list withholds the file. Proposal `0285` exists.

The package's premise is wrong where it matters: *"All 16 pass the value-initialised
`KONSTANTEN_DER_PROBE` ... so a trailing field leaves them compiling and zero"* (package,
line 48-50) is an argument about **translation**. Once step 3 writes from the carrier, the
zero carrier is the one that moves every path address.

## Befund 2 -- 0284's own comment reddens `bezeichner_riegel`, and this one is repairable

`bezeichner_riegel` was green on 2026-09-08 (`ops/plan.md:9-11` names the three reds; it is
not among them). Now: *"1 Bezeichner in Kommentaren des Kerns loesen nicht auf:
kern/include/kern/werte.hpp (Zeile 218) genannt: daten_pruefsumme"* (report `:528-532`).
Line 218 is the new field's own doc block -- *"Bewacht wird der Inhalt stattdessen von
`daten_pruefsumme` beim Laden (T22)"* -- and `daten_pruefsumme` is a T22 concept, not a kern
identifier. `werte.hpp` **is** in `dateien:`, so unlike Befund 1 a Ruecklauf can fix this.

## Befund 3 -- step 5 went live at two sums with no located guard

`politiklast` (`schritt.cpp:643`) and `handelsvolumen` (`werte.cpp:834-835`) add through a
bare `festkomma::plus`. The tree has a standard for exactly this case and neither meets it:
`bip` (`werte.cpp:787-802`) tests on `i128` first and names country, address and summand,
and `schritt.cpp:704-709` writes down why -- *"`plus: Summe ausserhalb von i64 (T7)` nennt
weder das Land noch die Adresse"*. Until this package neither sum was reachable from a
round. Now they are, and the first full partie produces that message with no location.
Proposal `0288`.

## Not a Befund, for the project manager

`zahlwort_messung` is red because `werkzeuge/zahlwort/messen.py` holds the literal
*"Zweiundzwanzig Groessen in dreiundzwanzig Deklarationen"* while `werte.hpp:32` now
correctly reads *"vierundzwanzig"* (report `:162`, `:761`). Condition 5 forbids writing
outside `kern/`, so the builder could not have kept it green. Same class as `zahlwort_riegel`
(proposal `0286`).
