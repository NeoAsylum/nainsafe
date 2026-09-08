---
typ: pruefung
paket: 0233-feldzaehler-an-einer-rohen-reihe-messen
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: All five conditions re-measured at HEAD against the compiler's own answer (green `schritt_probe` object plus the seven `static_assert`s) and against `kern/src/schritt.cpp`, not against the builder's account.
befunde: 1
---

# All five conditions met; the hard-error list names two of the three modules that can abort

## What I checked, and how

Build receipt: `befunde/uebersetzung-2026-09-08.md`, `ergebnis: ok`, with
`Building CXX object kern/CMakeFiles/schritt_probe.dir/test/schritt_probe.cpp.o` in both
trees — the objects come from the sources I read. `schritt_probe` passed in both. Every
`static_assert` below is therefore an answer of the compiler, not a reading.

**1 — the raw-array case.** `ZahlUndRohreihe` (`schritt_probe.cpp:1634-1637`) is exactly
`struct { i64 eins; i64 zwei[4]; }`. Written down twice, as condition 1 asks: the
`static_assert` at `:1674-1676` (== 2) and entry five of `FELDZAHLFAELLE` (`:1736`, now
`std::array<Feldzahlfall, 7>`, driven by `.size()` at `:1754`). The compiler answered
**2**, so the counter treats a raw and a `std::array` member alike, and the elision the
old comments warned about lives only in a counter without the braces.

**2 — the two comments.** Both now name `ZahlUndRohreihe`: `schritt.hpp:194-206` and
`schritt_probe.cpp:1567-1572`. `ZahlUndReihe` keeps its assertion (`:1672`) and its bullet
is back to "eine Reihe ist ein Feld" (`:1565-1566`); nothing calls it the failing case any
more. The stronger half of the condition is met the harder way: the builder built the
counter, `ohne_klammern` (`:1687-1712`), reusing `Platzhalter` and `FELDSUCHE_ENDE` from
the header instead of copying them, and every claim about an unbraced counter now stands
on `:1714-1722` — 5 for `ZahlUndRohreihe`, 2 for `ZahlUndReihe`, **9** for `Konstanten`.
`einundzwanzig` is gone from `schritt.hpp` (grep over `kern/`: no hit) and survives only at
`:1591` and `:1722` as a number the assertion refutes.

**3 — the false sentence.** "Genau eine der 310 Groessen" is gone; grep for `310` in
`schritt.hpp` leaves four occurrences, none of them the claim. What stands at `:35-40`
holds for every start state the probe runs: step 1 sets `partie.runde` to
`vorrundennummer + 1` (`schritt.cpp:833`) and the two barriers at `:811` and `:819` make
that sum both safe and different from its input. The count is delegated, not restated —
`probe_eine_runde` counts over all 310 against `erwartet` (`schritt_probe.cpp:937-951`),
and `0027`'s argument is named at `schritt.hpp:42-48`.

**4 — the chain.** `schritt.hpp:25-29` points at `test/schritt_probe.cpp` and gives the
shape without the moving number; `probe_kette` (`:748-752`, `:763`) measures it and derives
the split from `LAENDER` rather than writing 171.

**5 — the two new paths.** `schritt.hpp:309-321` names them at bullet level, points at
`realeinkommenshub` in `kern/src/schritt.cpp` without restating the condition, and the
barrier is where it says (`schritt.cpp:625-641`, `inlandsprodukt < 1`, before
`politiklast`). The `schaden` path and its guard check out too: `politiklast` skips an
instrument with `richtung == 0` (`schritt.cpp:590-597`).

## Finding 1 — `kern::festkomma` is the third module a round can abort in, and the list says "alle"

Not a defect against any condition. The scope note of conditions 3–5 asks for it: "If the
header and the source disagree beyond these three statements, that is a finding."

`schritt.hpp:298` opens the list with "**Harte Fehler, alle** ohne Ersatzwert", and
`:309-310` adds "**Zwei weitere** sind mit dem rechnenden Rumpf von Schritt 5
dazugekommen ... Beide fuehren aus `kern::werte` heraus". The two are exact — `werte::bip`
and `werte::schaden` are the only `kern::werte` calls in the file. But the computing body
brought in a third abort source that is not `kern::werte` and is not listed:
`kern::festkomma`'s arithmetic, at five sites in step 5.

* `schritt.cpp:596` — `festkomma::plus(last, festkomma::mal(richtung, zeile))`
* `schritt.cpp:644` — `festkomma::mal_geteilt(festkomma::minus(0, last), ...)`
* `schritt.cpp:686` — `festkomma::mal_geteilt(zustimmung_elastizitaet, hub, ...)`
* `schritt.cpp:687` — `festkomma::plus(schreiber.lies_alt(platz), wirkung)`

Each ends in `[[noreturn]] abbruch` (`festkomma.hpp:199-219`, `:155-163`, `:273`). Before
`0197` no `festkomma` arithmetic ran in `schritt`: `diese_runde = vorrundennummer + 1` is
plain, guarded by the two barriers above it. So these are as new as the two that are
listed, and dead today for the *same* reason the header gives for `schaden`: step 3
carries forward, so `richtung == 0`, so `last = 0`, `hub = 0`, `wirkung = 0`, and
`plus(x, 0)` cannot overflow.

**How to see it:** read `schritt.hpp:298-321` and ask which aborts a round can produce.
The answer you get is six. `schritt.cpp:687` is not among them — and that address is the
whole subject of package `0240`. `schritt.cpp:561` already says in its own comment that
"`festkomma::minus` braeche dann ab"; the source knows, the header does not.

Not repairable inside `0233`: condition 5 asked for those two and only those two, and
`0240`'s `dateien` are `schritt.cpp` and `schritt_probe.cpp` — its builder cannot touch the
header either, which is exactly how `0197` left the false sentence of condition 3 behind.
Proposal `0245-die-harten-fehler-nennen-auch-die-festkommabrueche`, hung on `0240` so it
can point at what `0240` leaves standing.

## What I looked for and did not find

A second random stream, floating point, or unordered iteration in what this package added:
none — `ohne_klammern` is `consteval`, and the only runtime addition is the `printf` at
`:1774-1779`. A claim about an unbraced counter without an assertion behind it: none in
either file. A `ZahlUndRohreihe` counted wrongly by the braced counter (condition 1's own
escape hatch): no, it answers 2. A start state in `schritt_probe` where `partie.runde`
comes out unchanged: none — `probe_eine_runde` asserts both ends at `:952-953`, including
at `I64_MAX - 1`.
