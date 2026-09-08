---
typ: technik
idee: 0016-hedgefonds-simulation-echte-weltwirtschaft
erstellt: 2026-09-01
fassung: 7, reworked on 2026-09-03 against the three findings of round 1 on package 0011 (section 16) and on 2026-09-04 against package 0026-klasse-2-preisbasis (T53, section 17), there in three runs -- the second recomputed the numbers of T53 and corrected three places (the scope list in section 17, two truncated numbers in T53), the third computed them a second time independently (no deviation) and completed the origin of N in the durchgriff paragraph of T53 (series 1 times series 2 instead of series 1); the decision itself is unchanged; the version follows ADR 0011 and ventures/0016-.../aufgaben/0011-stack-auf-cpp.md, exclusively the places that hang on the language; the content of version 6 stands unchanged -- and on 2026-09-04 against package 0043-t48-groessen-gegenkraft-5 (T48 grows from 17 to 22 quantities, T50 and section 12 point 3 are closed, section 10 gets the cost line of counterforce 5; section 18)
preisbasis: class 2 stands at constant prices of the year 2015 (measured by series 1, WDI "constant 2015 US$"); the 40 BACI trade flows arrive at current prices and are brought onto that basis at vintage build with a world export price index from WDI -- 0 computation steps per world step, 0 additional target series, T47/T48/T50 untouched (T53)
stack: C++20, compiled with g++, version pinned in werkzeugkette.cmake, build via CMake, every third-party library frozen as source under fremd/ in the repo (find_package and FetchContent forbidden); core without any third-party dependency and without a floating-point type; user interface deferred (ADR 0010)
ueberlauf: -fwrapv in every profile, -fsanitize=undefined,address in the test profile, __int128 for every intermediate value -- plus checked arithmetic in the core, cut by kind of operation (narrowing, addition and subtraction, multiplication without division), because -fwrapv switches off exactly the sanitizer's overflow check (T7)
determinismus: i64 fixed point with a declared scale per scale class, fixed iteration order via index lists, one root start value with derived streams, world step without any draw
zustand: a fixed, allocation-free value, 310 i64 (2.480 bytes), checksum over the canonical byte form
speicherstand: vintage, mode, start value, action sequence and checksum -- not the state
kalibrierung: all numeric values in a parameter file outside the code, included in the hash
partie: R rounds, R is a quantity of the vintage; in the check vintage 1997-2021, R = 24, one search-bot game costs R × 61 = 1.464 world steps
fondsvermoegen: cash + valued positions + valued stakes - leverage, stakes at exit value; exactly one function in the core, read by settlement, mandate, way of dying 1, the invariant test and B (T47)
skalen: thirteen classes, twelve of them with state addresses; each of the 310 addresses carries exactly one -- 3 fund money, 71 macroeconomic, 36 rates, 22 shares, 22 nominal indices, 5 exchange rate, 5 real indices, 25 persons, 32 lobby pressure, 4 instrument stage, 83 counters, 2 ids (T49)
skalenuebergaenge: exactly three, one named function each at exactly one place -- tsd_in_cent (valuation), lobbypunkte_aus_geld (action 3), lobbypunkte_aus_schaden (counterforce 5); cent_in_tsd has no caller and does not exist (T50)
abgeleitet: 22 functions of the state in the core (17 up to 2026-09-03, plus the five from the damage in counterforce 5 and the tariff wedge), 3 in the test bench, exhaustively enumerated; a name in a formula that is neither an address (T15) nor a parameter (T27) nor a vintage constant (T23) nor a derived quantity is a finding (T48)
suchbot: target quantity B per T44 -- a static outcome forecast of the intermediate state, in the "überlebt" branch formula-identical to the outcome quantity of spiel.md, without a free parameter
herkunft: each of the 310 addresses carries exactly one origin entry from five kinds; 136 data anchor, 150 design, 11 parameter, 2 manifest, 11 prescription (T45, T46) -- a gap or a second entry aborts the vintage build
tick_planwert: 10 microseconds per world step (range 5 to 30) -- estimated, not measured; there is no core yet
nachtlauf: at R = 20 9.759.420 world steps, 1,6 minutes on one core at the plan value, 8,1 minutes in the unfavourable case (package 0064; the key `partie` above still stands on R = 24 and is caught up by its own package, see section 29)
---

# The core is a pure integer function without a draw -- which makes determinism not a discipline but a property of the build profile.

Seventh version, against `ventures/0016-.../aufgaben/0011-stack-auf-cpp.md` and **ADR 0011**.
It swaps **the way of building and nothing else**: state layout, 310 addresses, thirteen
scale classes, formulas, origin entries and vintage constants stand unchanged, because none
of them hangs on a language. Touched are T1 to T15 in sections 1 to 4 and the places
further back that named a language feature by name.

The previous version justified determinism by saying that in Rust it can be enforced **by
the tooling**. The operator decided C++ on 2026-09-01, and the heading above is therefore
changed by one word: what the type system carried in Rust is carried here by the build
profile and three check rules — the floating-point lock (T4), the checked arithmetic (T7)
and the ordered containers (T9). **This is the difference that matters when reading:** each
of these three is mechanically verifiable, but none comes for free. Where the previous
version named a language property, this one names a check — and says what it does *not*
cover.

The working-off of the check on `0001-entwurf-abnahme` stands at the end of the file and is
untouched by this run. The working-offs of the first four checks stood in versions 2 to 5
and were each accepted there by the next check under its condition 5; they are in the Git
history and are not repeated here.

The prescriptions are numbered **T1** through **T53**. The builder deviates from none of
them unless an ADR lifts it; the reviewer cites the number instead of paraphrasing it.
**The numbers keep their meaning across all versions**, so that all checks stay citable;
new prescriptions take the next free numbers and stand where they belong by content. The
numbering is therefore not consecutive within the sections.

**Two prescriptions carry a letter in this version — T2b and T6b.** They are not new
rules but the C++ half of an existing one: T2b says what takes the place of
`#![forbid(unsafe_code)]`, T6b prescribes the division form on which the speed measurement
from ADR 0011 hung. A letter instead of a new number, so that the checks of rounds 1 to 6
stay citable and nobody has to look up T2 against T60. Genuinely new in version 7 was only
**T52** (platform independence of the integer arithmetic), and the previous version did not
need it because Rust had given it for free. **T53** was added on 2026-09-04 with package
`0026-klasse-2-preisbasis` and stands after T50 because it belongs to the scales and not to
the language (section 17).

**The most expensive lesson of version 6, valid unchanged: the counting step from T45
counts addresses, and finding 2 of round 6 lay between two of them.** The mixed scales in
`beteiligung_wert` were not a missing address and not a missing number, but a
**missing unit on an existing quantity**. Version 6 therefore ran the same check that
version 5 had run by hand for the origin, for the **scale** — and in doing so found that
T5 says of itself that the meaning stands „in dieser Tabelle und nirgends sonst", while **69
of the 310 addresses** appeared in none of its rows: 25 person quantities, 5 productivities,
4 regulation levels, 32 pressure and counter-pressure fields, the visibility of the fund and
the two id fields.

Among these, the 32 pressure fields are the expensive case, and they are literally finding 2
a second time: the applied pressure arises from the fund's **lobby budget** (US cents), the
counter-pressure from a **sector's damage** (thousand USD), and `spiel.md` nets the two
against each other in step 3. Without a declared unit, the build agent would have added two
scales that lie a factor of 100.000 apart — and this time it would not have looked like a
computation error, but like a counter-lobby that never bites.

The answer is **T49** (each of the 310 addresses carries exactly one scale class, counted),
**T50** (the scale boundaries are crossed by named functions at exactly one place) and
**T48** (the derived quantities that are not addresses, exhaustively enumerated — the set
in which finding 1 lay). The same way of building as T40, T44 and T45: not adding the
missing number, but closing the place where it could go missing, and testing a table's
promise by redeeming it once by hand. Both sums come out even:
`3 + 71 + 36 + 22 + 22 + 5 + 5 + 25 + 32 + 4 + 83 + 2 = 310` alongside
`136 + 150 + 11 + 2 + 11 = 310`.

## 1. Stack

**T1 — Core, data layer, interface, test bench and tools in C++20**, compiled with
`g++`, built via CMake, compiler identification and version pinned in `werkzeugkette.cmake`,
**every third-party library frozen in the repo per T3**. The operator decided this on
2026-09-01 (**ADR 0011**); this version records that decision and replaces the Rust version
of the previous drafts.

**The candidates, measured against this venture's criteria.** The previous versions argued
*for* a language instead of choosing *among* alternatives; that is the finding from which
ADR 0010 and this role's table obligation arose. The four measured rows come from
`ventures/0016-…/messung-stack/BEFUND.md` (2026-09-01, produced by
`agents/stackmessung.py`): the same fixed-point task, four agents, four languages.

| Language | Determinism mechanically enforceable | Agent hits the spec | ns/measurement step | Standalone program at the buyer | Memory-safe |
|---|---|---|---:|---|---|
| **C++20 (chosen)** | **yes, but composite** — three check rules instead of three language properties (T4, T7, T9) | **first attempt** | **947** | **yes** | **no** |
| Rust | yes, from the tooling — `overflow-checks`, `clippy::float_arithmetic`, `BTreeMap` | first attempt | 494 | yes | yes |
| Java | partially — floating point not forbiddable, `HashMap` shuffled | first attempt | **316** | no, needs a JRE | yes |
| Python | no | yes, but without a compile run | 50,383 | no | yes |
| Go | no — `float64` not forbiddable, map order deliberately shuffled | *not measured* | *not measured* | yes | yes |
| C# | no — only by discipline | *not measured* | *not measured* | with runtime | yes |

Go and C# are **not measured**; their rows come from ADR 0010 and are argument, not
number. They stay in the table so that it is visible what was checked and what was not.

**What the measurement decided, and what it did not.** All four implementations hit the
same checksum `1163237642073673` on the first attempt, including the rounding of half
amounts away from zero for negative values. **That leaves the "agent reliability" column
empty for this domain** — it was the Rust version's main argument and no longer carries.
Python drops out on speed (factor 53.2 against C++ in this measurement, computed as
50,383 / 947); among the three compiled languages speed is indifferent, because 11.78
million world steps are minutes everywhere (section 10).
Java, at 316 ns, is the fastest and falls out anyway: a runtime environment next to
a Steam title is a shipping problem that no amount of compute time outweighs.

**The objection to the choice belongs here, and there are two.** *First:* in the
measurement C++ was 1.92 times slower than Rust and 3.0 times slower than Java (947 / 494
and 947 / 316, both computed in this run). That is a property of **this implementation**,
not of the language — **T6b** now says what caused it and how the core does it differently.
*Second, and this is the lasting price:* C++ has no memory safety. In a factory without
human code review that is a failure class of its own, and it shows up at the buyer
instead of in the compile run. The countermeasures are the address sanitizer in the
test profile (T7), the warning set with `-Werror` and the core's pointer freedom (**T2b**) —
they cover paths, not all cases. This stands here so that it does not surprise anyone later.

**What must be settled now and what can be deferred.** The question costs nothing and
saves the most, so it stands here spelled out:

| Decision | now or later | Reason |
|---|---|---|
| Language and compiler of the core | **now** | Every line of core hangs on it; a switch later is a rebuild. |
| Integer discipline (T4, T6, T7) | **now** | Not retrofittable: it is the precondition of every regression test. |
| Module direction (T13) | **now** | It is at the same time the collision cut of the work packages (section 13). |
| User interface | **later** (ADR 0010) | The model never asks the view anything; it is replaceable as long as the core stands. It is decided once it is known what it must show. |
| Parameter-file reader | **later** | It sits in `daten`, not in the core; T3 names the requirement, not the product. |
| Parallelising the test bench | **later** | T39 demands result equality with one and with many cores — that binds the procedure, not the library. |

**T2 — The module `kern` has zero third-party dependencies.** No logging kit, no
random-number library, no time, no input and output. A module without dependencies cannot
have its result changed by any outside version update. **The standard library is not a
third-party dependency** — it comes with the compiler that `werkzeugkette.cmake` pins.

*How this is enforced, since C++ has no `[dependencies]` section that could stay empty.*
The equivalent is a property of the core's `CMakeLists.txt`, and it is provable with
**three** pattern matches. Two run over this one file: the first looks for every directive
that pulls in outside code or adds another source directory, the second for every library
linked to `kern`. The third runs over **all remaining** `CMakeLists.txt` of the venture
and looks there for `link_libraries(` and
`target_link_libraries(kern` — the two forms by which a dependency can be attached to
`kern` from outside without a single line standing in its own file (T13).
**All three must come up empty.** Their exact wording belongs in the acceptance criterion of
the respective package and expressly not in the checked file: a file that quotes its own
search patterns never lets them come up empty.

*Why the third match belongs here and is not caution:* Two matches over
`kern/CMakeLists.txt` check the file and not the property. `link_libraries(fremd)`
one level up applies to every target created after it, hence also to `kern` from
`add_subdirectory(kern)`; and since CMake 3.13 — 3.22 is required —
`target_link_libraries(kern PRIVATE fremd)` may stand in a *different* directory than the
one where `kern` was created. In both cases the first two matches stay empty, and the
core links a third-party library anyway: T2 formally satisfied, substantively broken. It is
the same gap that T13 closes on the **header side** with the ban on `include_directories()`
— it has a twin form on the link side, and T13 now closes that one too.

**T2b — What takes the place of `#![forbid(unsafe_code)]`.** The attribute does not exist
in C++, and that is the price from ADR 0011: memory safety is here a **check rule instead
of a language property**. Three things take its place, all mechanical, all anchored in the
build profile instead of in an understanding:

1. **The warning set with `-Werror`:** `-Wall -Wextra -Wconversion -Wsign-conversion -Wshadow
   -Wold-style-cast -Wcast-qual -Wuseless-cast -Wdouble-promotion -Wfloat-equal
   -Wnull-dereference -Wformat=2`. Whatever the compiler recognises as doubtful is thereby
   a build abort and not a line that drowns in the log. **`-Wpedantic` is deliberately not
   among them:** it warns about `__int128`, and `__int128` is mandatory per T6. A
   warning switch that nags about a requirement gets turned off or ignored — both are
   worse than not setting it.
2. **The address sanitizer in the test profile** (T7, measure 2). It is the only one of the
   three that *finds* memory errors instead of making them *harder*.
3. **Pointer freedom as a grep rule:**
   `grep -rnE 'reinterpret_cast|const_cast|\bnew\b|\bdelete\b|\basm\b' kern/` returns nothing.
   The core gets by without raw pointers and without memory management of its own — fixed
   sizes and `std::array` instead of raw arrays (T15). That is not hardening but a
   consequence of the data model: a state without pointers has no place where a pointer
   could be wrong.

**T3 — The dependencies outside the core are exhaustively enumerated, and as a
requirement, not as a product.** Which library satisfies a requirement is decided by the
respective package; that there is *no further one* is decided by this rule.

| Module | Requirement | Status |
|---|---|---|
| `daten` | reader for `parameter.toml` and the vintage files, **without floating point** (T4) | open; the requirement rules out every reader that goes through `double` |
| `schnittstelle` | write and read the protocol format | open; the format stands in T17, not in a library |
| `pruefstand` | parallelism across games | open; section 9 binds the **result equality** with one and with thirty-two cores, not the means — `std::thread` and `<execution>` both satisfy it |
| `werkzeuge` | file checksums for the vintage build | open; may be a third-party library, because the product is checked and not the way |
| `oberflaeche` | — | **deferred** (ADR 0010) |

**Every library actually used needs an ADR with a licence quotation**, and none of them
may enter the core (T2). The earlier list in this rule named six third-party libraries
by name; it is struck without replacement, because it fixed a choice nobody had to
make — and because its user-interface row had been deferred since ADR 0010 anyway.

**And every library used lives in the repo, not on the machine of whoever compiles.**
This is the successor of `cargo vendor`, and it was at first missing in the rewrite to
C++: the sentence of the previous version had two halves — toolchain pinned,
dependencies frozen — and only the first became `werkzeugkette.cmake`.
Concretely, in place of the second: the source lives under `fremd/<name>/`, version
and commit id stand in its ADR, and it is compiled along via
`add_subdirectory(fremd/<name>)`. **`find_package()`, `FetchContent`, `ExternalProject`
and `pkg_check_modules` are banned in the whole venture** — they tie the build to whatever
happens to be installed on the machine at hand. The ban is the actual rule and
not an addendum to T23: a `find_package(… REQUIRED)` **downloads nothing**, so it does
not violate „der Bau lädt nichts aus dem Netz" and still does exactly the damage
that `cargo vendor` ruled out.

*Why this costs nothing today and still stands here now:* The venture has zero
actual third-party dependencies — T2 bans them in the core, and all five rows of the table
above stand on "open" or "deferred". So nothing is broken; something is unguarded.
The promise behind it is the backtest: two compilations three months apart
must produce the same program, otherwise T31 checks against a regression baseline that
nobody can restore identically — and the parameter reader from the first table row is
exactly the sort of library whose version change shifts a number by one digit without
anything aborting. A rule before the first library costs a paragraph;
the same rule after the first library costs a rebuild.

**Expressly not chosen:** A game engine (Godot, Unity, Unreal) — it brings a frame
loop, a timeline and a numeric world of its own, that is exactly the three sources
of non-reproducibility that are to be excluded here; the game needs
tables, history graphs and a chain view. A web UI (Electron, Tauri) —
JavaScript has no integer type, and an accidental `/` silently produces a
floating-point number. Python — see the calculation in section 10. The Steamworks SDK —
not needed for the first title (no achievements, no cloud saves), hence one dependency and
one account fewer. **A test framework** (GoogleTest, Catch2) — the tests are standalone
programs with `static_assert` and return value, invoked by CTest; that costs no
dependency and turns half of the checks into compile errors instead of
runtime messages.

## 2. Der deterministische Kern

**T4 — No floating-point number in the core, in the data layer and in the protocol.** No
`float`, no `double`, no `long double`, no `sqrt`, no `pow`, no `log`, no `exp`.

**The lock is a compile error, not a resolution.** Rust would have had
`#![deny(clippy::float_arithmetic)]` here; the C++ equivalent is `#pragma GCC poison`
in `kern/include/kern/sperre.hpp`. From that line on, a poisoned identifier is a hard error
of the preprocessor. Whoever writes `double` in the core gets no numeric error in
round 400 but a red compile run. Poisoned are `float` and `double`
(`long double` is two tokens and thus covered along), the root, power, logarithm and
exponential functions in all three suffix forms, and the string converters `atof`,
`strtod`, `strtof`, `strtold`.

**The placement rule, and it is the whole trick:** `sperre.hpp` is the **last** line of the
include block of every core source and stands in **no** `.hpp`. The poisoning applies from
the place where it stands to the end of the translation unit — a standard header included
after it breaks on it, because `<string>`, say, declares a `std::to_string` for
`double`. A lock in a header would therefore not protect the core but halt
the build.

Proof, two lines: `grep -c 'include "kern/sperre.hpp"' kern/src/*.cpp` returns exactly `1`
for every source, and `grep -rnE 'float|double' kern/` hits only `sperre.hpp`
itself. The parameter file, too, is read without floating point — decimal strings are
split directly into scaled integers, never via a floating-point detour; the same lock
applies in `daten`.

**T5 — Every size class has a declared scale.** The type is `i64` everywhere — in the core
an alias for `std::int64_t`, so that the width depends on the target system at no point —,
the meaning stands in this table and nowhere else:

| # | Class | Unit | Example | Range |
|---:|---|---|---|---|
| 1 | Fund money (cash, **position value**, **stake value**, leverage, investor stock) | US cents | 4,200,000,000 = 42 million USD | ±9.2·10^16 USD |
| 2 | Macroeconomic amounts (GDP, value added, capital stock, trade flow, **basket value**, market-basket value) | thousand USD at constant prices **of the year 2015**; whatever arrives in a different price basis is brought onto it at vintage build per **T53** | 21,000,000,000 = 21 trillion USD | ample |
| 3 | Rates (interest, inflation, tariff, budget balance, debt ratio, return, excess return, **`aufschlag`**) | basis points (1 bp = 0.01 %) | 250 = 2.50 % | ±2 million % |
| 4 | Shares (sector share, market share, influence, approval, **visibility**, **stake share**, `durchgriff`, **`stufenweite`**) | ten-thousandths | 10,000 = 100 % | 0 to 10,000 |
| 5 | Nominal indices (sector prices, world prices, price level, **`anleihekurs`**) | index, start year = 10,000 | 12,500 = +25 % | > 0, see T8 and T50 |
| 6 | Exchange rate | index against USD, start year = 10,000 | 8,000 = appreciation by 25 % | ≥ 1, see T8 and T50 |
| 7 | **Real indices (productivity)** | index, start year = 10,000, **never rebased** | 11,200 = +12 % | > 0 |
| 8 | **Persons** (population, labour force, employment per sector) | persons | 82,000,000 | 0 … 10^10 |
| 9 | **Lobby pressure** (applied pressure, counter-pressure) | lobby points | 1,500 | 0 … `druck_max` |
| 10 | **Instrument tier** (financial-market regulation alone) | tier | 3 | 0 … `regulierung_stufen` |
| 11 | Counters and remaining durations (supervision, imitators, remaining delay, the three remaining durations, `basiswechsel`, round, mandate level, position step) | count resp. rounds | 3 = three rounds | 0 … upper bound from `parameter.toml`; position step `−stufen_max … +stufen_max` |
| 12 | **Ids** (vintage id, parameter-set checksum) | bit pattern without magnitude meaning | — | any `i64`; **any arithmetic except equality is an error** |
| 13 | Result of a game (**no state address**) | milli-rounds | 12,000 = round 12.0 | see T34 |

**Five classes are new in this version, and they are not new out of love of order.** T5
says of itself that the meaning stands „in this table and nowhere else"; in this run I have
redeemed that promise for the first time against all 310 addresses and found 69 that
appeared in none of its rows. Which ones they are and how the mapping comes out stands in
**T49**; what the new classes mean, here:

- **Persons (8).** 25 addresses. Without a class of their own, a build agent could have
  carried the labour force in thousands or in persons, and productivity would have hung on
  the factor 1,000.
- **Real indices (7).** 5 addresses. The separation from class 5 is no nicety but a rule:
  on a rebasing, T8 divides the **nominal** quantities of a territory by
  1,000. Productivity is real and must not move along; if it stood in class 5, a Brazilian
  base change would lower productivity by three orders of magnitude.
- **Lobby pressure (9).** 32 addresses, and the reason stands above in the preamble:
  `druck` comes from the fund's budget, `gegendruck` from a macroeconomic damage, and
  step 3 nets the two against each other. The common unit is the **lobby point**; the two
  transitions into it stand in T50.
- **Instrument tier (10).** 4 addresses. Three of the four instruments stand in basis
  points, because their historical policy path comes in basis points; financial-market
  regulation has no anchor per `spiel.md` and therefore no natural unit. It gets a tier
  scale, and „at most one step per round" means **one tier** there, for the other three
  `schrittweite[instrument]` basis points from `parameter.toml`.
- **Ids (12).** 2 addresses. The ban on arithmetic is the actual content: a checksum that
  accidentally gets into a sum produces a number that no check notices, because it lies
  in no value range.

**Two existing classes are widened, and this too is no tidying step:**
**fund money (1)** and **macroeconomic amounts (2)** now carry `positionswert` and
`korbwert` explicitly, on both sides of the boundary. That is finding 2 of round 6 at its
root — the two names stood in a formula in T47, but in no class.

Influence and approval appear to the player as 0 to 100 (that is what `spiel.md` calls
them); stored they are in ten-thousandths, so that the counterforces can still calculate
below one visible point. The conversion takes place in the view.

The coefficient has been called **`durchgriff`** since `spiel.md` version 3, no longer
`handelsanteil`. It stays in the shares class — unlike its predecessor it now holds that
class's range by construction; the formation rule stands in T23 point 5.

**`stufenweite` has stood in the shares class and not in the fund-money class since
`spiel.md` version 5**, and that is the decision finding 2 hung on: a step is
*`stufenweite` ten-thousandths of the market* the slot hangs on, not an amount of money.
With that, the share that counterforce 1 and the price shock read is the same number as
the one the position value arises from, and the state needs no twenty entry prices.

**The base year of class 2 is 2015, and since this version it stands there as a year
instead of as „the base year".** Until 2026-09-04 the row named a base year without naming
one; for 56 of the 71 addresses it was thereby undetermined what they refer to, and a
build agent would have had to choose it. Chosen is **2015**, because it is the only base
year **measured** in this venture: series 1 carries, at the World Bank endpoint, in the
field `Unitofmeasure` the wording „constant 2015 US$" (two endpoints, cross-checked
character-identical, `daten/einheitenbefund-pwt-baci.md` section 6, retrieved 2026-09-02),
and the value added of all five territories arises from it per T23 point 1. A different
base year would have meant converting the only measured series in order to hit two
unmeasured ones.

**Which class-2 address arrives in which price basis, and what happens to it, stands in
T53** — by name for the 40 trade flows from BACI, which as the only ones arrive measured
in a **different** basis.

**Between the fund scale and the macroeconomic scale lies the factor 100,000** (1 thousand
USD = 100,000 US cents). Where it is crossed, **T50** says — and it is crossed in only
**one direction**, which is why `cent_in_tsd` no longer exists in this version.

**T49 — Each of the 310 addresses carries exactly one scale class, and the mapping is
counted off.** That is T45 one level deeper, for the same reason and with the same
procedure: next to the provenance table, the vintage build keeps a **scale table** over all
310 addresses; an address without a class and one with two classes abort the build. Both
tables are written into the manifest, and both must sum to 310.

**Per playable country**, the 44 from T15 by class:

| Class | Addresses | which |
|---|---:|---|
| 2 macroeconomic | 6 | 3 value-added figures, 3 sector capital stocks |
| 8 persons | 5 | 3 sector employments, population, labour force |
| 5 nominal indices | 4 | 3 sector prices, price level |
| 7 real indices | 1 | productivity |
| 3 rates | 7 | inflation, policy rate, government debt, budget balance, 3 instrument levels (policy rate, tariff, budget) |
| 6 exchange rate | 1 | exchange rate |
| 4 shares | 2 | approval, influence |
| 9 lobby pressure | 8 | 4 applied pressures, 4 counter-pressures |
| 10 instrument tier | 1 | level of financial-market regulation |
| 11 counters | 9 | supervision counter, 4 remaining delays, 3 remaining durations, `basiswechsel` |
| **Sum** | **44** | as T15 |

**The rest of world** carries 22 of these: 6 macroeconomic, 5 persons, 4 nominal indices,
1 real index, 4 rates, 1 exchange rate, 1 counter — it has no instruments, no approval,
no supervision counter, no influence and no remaining durations.

**The whole decomposition**, against the same 310:

```
Klasse  1 Fondsgeld           Kasse, Hebelstand, Anlegerbestand                  =   3
Klasse  2 volkswirtschaftlich 4×6 + 6 + 40 Handelsströme + markt.wert            =  71
Klasse  3 Raten               4×7 + 4 + markt.rendite + 3 Überrenditen           =  36
Klasse  4 Anteile             4×2 + Sichtbarkeit + Marktanteil + 12 Beteiligungsanteile = 22
Klasse  5 Nominalindizes      4×4 + 4 + 2 Weltpreise                             =  22
Klasse  6 Wechselkurs         4 + 1                                              =   5
Klasse  7 Realindizes         4 + 1                                              =   5
Klasse  8 Personen            4×5 + 5                                            =  25
Klasse  9 Lobbydruck          4×8                                                =  32
Klasse 10 Instrumentenstufe   4×1                                                =   4
Klasse 11 Zähler              4×9 + 1 + 12 Nachahmer + 20 Stufen + 12 Restdauern
                              + Runde + Mandatsstand                             =  83
Klasse 12 Kennungen           Jahrgangskennung, Parametersatz-Prüfsumme          =   2
                                                                                   ---
                                                                                   310
```

Counter-checked against the group decomposition from T15 (`198 + 56 + 52 + 4`) and against
the provenance decomposition from T45 (`136 + 150 + 11 + 2 + 11`). **Three independent
partitions of the same set, all three computed by hand** — a number that arises only once
is unsubstantiated, even if it is right.

**Two address pairs carry the same value, and that needs a rule instead of a coincidence.**
`land.<L>.leitzins` and `land.<L>.instrument.leitzins.stand` are the same quantity, as are
`land.<L>.haushaltssaldo` and `land.<L>.instrument.haushalt.stand`; T15 carries both
because `spiel.md` enumerates both. Binding is therefore: **written is the instrument
level, in step 3; the aggregate quantity is taken over from the level in step 4 with
`lies_neu` and carries the cause `Instrument{l, i}`.** The invariant test (T30 check 2)
checks the equality every round. Without this rule there would be two masters over one
number — the same error type that T39 has already closed for `landespreis`, T23 point 9
for the BACI concordance and T47 for the fund's assets. That the pair exists at all is an
observation about `spiel.md` and stands in section 12; it blocks nothing.

**T50 — There are exactly three scale transitions, each has a named function and exactly
one call site.** A transition without a name is the error kind that finding 2 of round 6
hung on; a name without a binding to a place is the same error one week later.

| # | from | to | Function | sole call site |
|---:|---|---|---|---|
| 1 | macroeconomic (2) | fund money (1) | `tsd_in_cent(x) = x · 100.000` | outermost call of `positionswert` and `beteiligung_wert` (T47) |
| 2 | fund money (1) | lobby pressure (9) | `lobbypunkte_aus_geld(cent, rabatt) = mal_geteilt(cent, 10.000, lobbykosten · rabatt)` | action 3, step 2 |
| 3 | macroeconomic (2) | lobby pressure (9) | `lobbypunkte_aus_schaden(tsd) = mal_geteilt(tsd, gegenlobby_satz, 10.000)` | counterforce 5, step 5 |

`lobbykosten` (US cents per lobby point, ≥ 1), `gegenlobby_satz` (lobby points per 10.000
thousand USD of damage) and `beteiligungsrabatt` (ten-thousandths; `rabatt` is 10.000
without and `beteiligungsrabatt` with a stake in the affected sector, so
`1 ≤ beteiligungsrabatt ≤ 10.000`) stand per T27 in `parameter.toml` and are calibrated,
not designed. A smaller rebate value means more points for the same money — that is the
„fraction" that `spiel.md` promises action 3 with a stake. **The rebate sits on the price
of a lobby point, not on the number of points** — otherwise `einfluss`, per `spiel.md` the
fund's share of the total lobby pressure, would no longer be comparable across countries.

***How high* a sector's damage is, `spiel.md` decided on 2026-09-03, and the sentence that
left it open here until 2026-09-04 is thereby closed.** It read: *„Wie hoch der Schaden
eines Sektors ist, bleibt Sache von `spiel.md` und des Bauagenten; T50 legt nur fest, in
welcher Einheit er ankommt."* Handing it back was right — had I filled the gap, Maß 2
would have measured my choice —, and it is answered: the section *Der Schaden in
Gegenkraft 5, als Rechenvorschrift* in `spiel.md` gives the one rule („the shift of the
price the instrument sets, times the quantity that price acts on") and the four rows to
go with it. It stands as **number 22** in T48; the build agent chooses nothing at this
place any more. What T50 fixes unchanged is solely the unit in which it arrives here:
class 2, thousand USD. The scale check for it `spiel.md` carries itself — class 2 times
ten-thousandths divided by 10.000 is class 2 again, in all four rows and across both
intermediate steps of the tariff row, **so no fourth scale transition arises.** This table
stays at three.

**`cent_in_tsd` does not exist.** Version 5 named the inverse function next to
`tsd_in_cent`; it has **no caller** in this model, and the reason is a property of the
design and no coincidence: the fund acts on the world exclusively via **shares in
ten-thousandths** (price shock from action 1, footprint in counterforce 1, imitator
counter), never via an amount of money. A conversion function without a caller is a
standing invitation to use it somewhere it does not belong; it is therefore struck.
If a rule turns up later that needs it, that is an ADR.

**Where the transitions are enforced.** All three functions and all derived quantities
from T48 stand in the module `kern::werte`; `tsd_in_cent` and the two lobby conversions
are private there. A hit of `grep -rn 'tsd_in_cent\|lobbypunkte_aus' kern/` outside this
one module is a finding — the same construction as the floating-point proof from T4, and
just as mechanical.

**T53 — What class 2 means for a series that arrives in current prices: it is deflated at
vintage build, with a named deflator from an already admitted source, onto the 2015
basis.** The core sees none of this. This is the decision package 0002 has been waiting
for since 2026-09-02.

**Where each of the 71 class-2 addresses arrives, measured and counted off.** The
decomposition is the one from T49 (`4×6 + 6 + 40 Handelsströme + markt.wert`), cut by
price basis instead of by territory:

| Addresses | Count | Series | Source | Price basis, as measured | what happens |
|---|---:|---|---|---|---|
| value added, 5 territories × 3 | 15 | 1 via T23 P1 | WDI `NY.GDP.MKTP.KD` | **constant, 2015** (measured 2026-09-02, two endpoints) | nothing — it *is* the basis |
| sector capital stock, 5 × 3 | 15 | 3 via T23 P1 | PWT 11.0 | **unmeasured** (PDF lock) | **declared non-decision**, below |
| trade flows | 40 | 14 | CEPII BACI, field `v` | **current** (measured 2026-09-02, „in thousands current USD") | **deflator**, below |
| `markt.wert` | 1 | 19 | none, T33 | follows its inputs (12 `korbwert` + 4 `anleihewert`) | nothing |
| **Sum** | **71** | | | | as T49 |

Recomputed: `15 + 15 + 40 + 1 = 71`, and `15 + 15` is the `4×6 + 6 = 30` from T49, split
by quantity instead of by territory. **Exactly one row is measured in a basis other than
2015**, and it carries 40 of the 71 addresses.

**The number that decides — the price share alone breaks the threshold.** T42 measures the
trade block with the MAPE against the threshold 2,000 (= 20 %). The model carries the
trade flow real (`spiel.md` expressly rests counterforce 5's damage rule on this:
*„`handelsvolumen` stands per T5 in class 2 at constant prices"*), the target series comes
nominal. How large the error is that this **alone** produces was unmeasured until today;
it no longer is. World exports in current and in constant 2015 prices, both from the
World Bank, their quotient is a USD export price index with basis 2015 = 10,000:

```
https://api.worldbank.org/v2/country/WLD/indicator/NE.EXP.GNFS.CD   "Exports of goods and services (current US$)"
https://api.worldbank.org/v2/country/WLD/indicator/NE.EXP.GNFS.KD   "Exports of goods and services (constant 2015 US$)"
                                                                     beide abgerufen 2026-09-04
```

| Year | 97 | 98 | 99 | 00 | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| Index | 7,417 | 7,021 | 6,911 | 6,849 | 6,594 | 6,738 | 7,485 | 8,246 | 8,755 | 9,281 | 10,133 | 11,232 | 10,045 |

| Year | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| Index | 10,682 | 11,989 | 11,840 | 11,798 | 11,592 | **10,000** | 9,570 | 10,022 | 10,553 | 10,254 | 10,158 | 11,549 |

A model that hits the quantities **error-free** starts on the BACI value of 1997 and runs
on in real terms; the target series runs with the index. Its error per support point is
thus `|1 − r(t)| / r(t)` with `r(t) = Index(t)/Index(1997)`, and the mean over the 25
support points of the check vintage is **2,203 ten-thousandths against a threshold of
2,000**. At the right edge alone it is 3,578 (2021: `r = 1,5571`). **The check subject
trade block thus fails before the model has made a single error** — the price drift alone
uses up the error budget not in part but **entirely, and with 10 percent overshoot**
(2,203 against 2,000). Nothing is left for model quality.

Three caveats belong in the same place as the number. *First*, this is the **world**
aggregate index and not the deflator of the 40 bilateral flows; it has the right order of
magnitude and is measured, it is no prediction of the actual MAPE. *Second*, 2,203 is the
**systematic share**, on top of which the model error still comes, not off it. *Third*,
the argument carries even at a smaller number: a threshold that is meant to measure model
quality and loses its budget to a price drift nobody has modelled measures something
other than what it stands there for.

**The four ways side by side, with price.** The price stands in computation steps per
world step and in additional target series, because those are the two quantities this
venture can perish on:

| Way | Computation steps per world step | additional target series | further price | Result |
|---|---:|---:|---|---|
| **1 Deflate (chosen)** | **0** | **0** | one-off 1,040 conversions per vintage build; **+1 series** (no. 20, 2 indicator codes, 1 territory, 25 numbers), **no new source** | trade block remains a check subject, T47/T48/T50 untouched |
| 2 Change class | 0 in this document | 0 | T5 **+1 row**, T49 decomposition anew (71 → 31 + 40), T8 to recount — **and a decision in `spiel.md` of 2026-09-03 reopened** | not my decision, see below |
| 3 Restrict Maß 4 | 0 | 0 | 16 → **15** check subjects at unchanged tolerance 2, hence a *sharper* test on the rest; 40 of the 71 addresses without any check; channel 3 without a historical anchor | cheapest build, dearest loss |
| 4 Change source (IMF DOTS) | — | — | **not quantifiable**: T26 admits DOTS only for play vintages before 1997, the check vintage starts 1997, and the price basis of DOTS is unmeasured (HTTP 403 in five attempts from three roles) | trades a measured difficulty for an unmeasured one |

**Why way 1 and not way 3**, although both cost zero in the core: way 3 does not mean
„restrict" but **strike**. At an error share of 2,203 against 2,000 there is no
restriction that would leave the trade block still checking anything — a threshold of its
own above 2,203 would be a threshold every model passes. The block carries 40 of the 71
class-2 addresses and is the only historical anchor of **channel 3** (instrument → trade →
world price → damage → counter-pressure) that `spiel.md` carries among its eight channels.
Way 1 buys it for 25 numbers from a source that is already integrated anyway.

**Why not way 2, and this is no price argument.** On 2026-09-03 `spiel.md` struck the
business-cycle base term from counterforce 5 and expressly rested the striking on
`handelsvolumen` being real per T5 class 2 — the base term *was* inflation times the
trade volume. Setting class 2 nominal brings it back. **What is played stands in
`spiel.md`; I do not contradict it there.** Way 2 is thus not expensive but not mine.

**The deflator, named, with source and in integers.** It becomes a series of the vintage,
no program part (T23), and no target series — it is compared against nothing:

```
preisindex_handel[t] = teile_gerundet( ausfuhr_laufend[t] · 10.000, ausfuhr_konstant[t] )

handel_konstant[a][b][s][t] = mal_geteilt( handel_laufend[a][b][s][t],
                                           10.000, preisindex_handel[t] )
```

`ausfuhr_laufend` is `NE.EXP.GNFS.CD`, `ausfuhr_konstant` is `NE.EXP.GNFS.KD`, both for
the territory `WLD`, both World Bank — hence **source no. 1 from `daten.md`**, the same
licence, the same citation duty, no fifth source and no case for the data curator. Both
computations run through T6; `ausfuhr_laufend[t] · 10.000` reaches about 2.8 · 10^17 at
2.8 · 10^13 USD and thus stays within `i64`. The factor 1 from the units finding remains
untouched: it is the **order of magnitude**, the deflator is the **price basis**, and the
two are two questions to the same row.

**A self-test that costs two lines and carries the whole mapping:**
`preisindex_handel[2015] = 10.000` **exactly**. It holds not by convention but because the
two series carry the same value in the base year (21,272,611,247,725.1 —
character-identical in both retrievals). If it deviates, the two indicator codes do
**not** carry the same basis, and the vintage build aborts instead of asserting a price
basis it does not have. That is the same construction as the count-off checks from T45
and T49: a promise that proves itself.

**The conversion hits the target series and the start matrix, and with the same index.**
Per T23 point 9, **one** concordance produces the trade start matrix, the 40 target flows
and `H` from point 5; correspondingly, **one** index deflates all three. Deflating a
target series and not the start matrix would be the error T23 point 9 already rules out
for the concordance. For the check vintage the factor onto the start year is
`10.000 / 7.417 = 1,34825`.

**Series 16 (`durchgriff`) is thereby co-decided, and it was the second half of the
contradiction.** `H` comes per T23 point 5 from the same deflated matrix. `N` is the
sector's value added and arises per T23 point 1 from **two** series —
`wertschoepfung[g][s] = mal_geteilt(bip_start[g], sektoranteil[g][s], 10.000)`, that is,
series 1 times the sector share from series 2. **The price basis of `N` hangs on series 1
alone**, because series 2 is a share in ten-thousandths without a price basis. Both sides
thereafter stand in constant 2015 prices, and the quotient carries no price share any
more. **The move has a property no other deflator cut would have:**
because *one* index acts on *all* 40 flows, every `H` is multiplied by the same factor,
hence `H/N` for all territories and sectors by the same one — and
`durchgriff = 10.000 · H/(H+N)` is strictly monotonic in `H/N`. **The ordering across
countries and sectors thus stays exactly preserved**, and it is the only thing `spiel.md`
demands of this quantity (*„Its numerical value has no economic meaning; it must order
countries and sectors correctly"*). The **amount** shifts, namely upward: on the two
cases `spiel.md` works through, the factor 1.34825 acts as `7.288 → 7.837` and
`5.464 → 6.189`. Both numbers are **recomputations on `spiel.md`'s example values from
WDI 1995 and not the values of the vintage** — they show the size of the shift, not its
result. The order agriculture before industry holds in both versions.

**A per-exporter deflator would be more precise and is not to be had — measured, not
presumed.** `NE.EXP.GNFS.KD` exists for the People's Republic of China in the window
1997–2021 **for 2015 alone**; the other 24 support points are `null` (retrieved
2026-09-04, queried one by one, because a first bulk query contradicted itself). For
Brazil, Germany and the USA the series is complete. The choice of the world index is thus
**forced and not preferred**, and that belongs here because otherwise it looks like
convenience. What remains is the distance between the world index and the true bilateral
deflators; it is **unmeasured** and the honest residual of this way. It is second order
against the 2,203 the way removes — that it *is* small, I do not claim.

**Series 3 (PWT capital stock, 15 addresses): declared non-decision.** Neither unit nor
base year is measured; four PDF retrievals from three directories arrived unreadable
(`daten/einheitenbefund-pwt-baci.md` sections 3 and 4). I decide **nothing** here, because
any choice would be a guess, and instead write down the three parts that carry the
decision:

- **The missing number:** unit and base year of the capital-stock variables in PWT 11.0.
  It costs **one** readable excerpt from `pwt110_user_guide_to_data_files.pdf` (Dataverse
  id 554025) or from the label sheet of `pwt110.xlsx` (554105).
- **The addressee:** the data builder, and through them the operator — the lock is the
  toolchain and not the source. It is the second lock of this kind next to the IMF full
  text.
- **The consequence, and it is ordered by size.** The **unit** is the heavy part: if the
  capital stock stands in millions instead of thousand USD, the factor is 1,000 and not
  1 — three orders of magnitude, silently. The **base year** is the light one: a
  difference between 2015 and 2017 or 2021 shifts all 15 addresses by the **same** factor,
  on the order of a few percent. Neither hits **any target series** — series 3 is `Start`
  per the series list and carries no check subject —, so it acts not on Maß 4 but via
  `korbwert` on `marktkorb` and `fondsvermoegen`. A common factor on all 12 baskets
  cancels out in `fonds.marktanteil` and is calibrated along in `startkapital` and
  `stufenweite`; **what it does not do is cancel out in `marktkorb`**, for there 12
  baskets stand next to 4 `anleihewert`, which come from series 1 and do not move along.
  The mix of the 16 market values thus shifts, and with it the ratio of basket to bond
  slots.
- **As long as this is open**, `art = "ungemessen"` at series 3 in `daten/reihen.toml`
  remains correct, and the vintage build may insert **no** factor for it. T24 marks gaps
  instead of filling them; that is the case here.

**The consequence for package 0002, written out because it hangs on it: T47, T48 and T50
remain untouched.** Not a word, not a formula, not a row in any of their tables changes,
and the reason is a property of the chosen way and no promise:

- **T47** computes exclusively on state quantities. The deflation lies in
  `werkzeuge/aufbereitung` and is finished before the core sees the first number. `wert`,
  `korbwert`, `anleihewert`, `waehrungswert`, `markt`, `stufenwert`, `positionswert`,
  `beteiligung_wert` and `fondsvermoegen` stand unchanged.
- **T48** carries `handelsvolumen(l)` as class 2. Until now that was an assertion and is
  now a fact — precisely for that reason the row does **not** change.
- **T50** counts three scale transitions. A deflator is none: it leads from class 2 to
  class 2, and it runs outside the core. Three remain.

**`kern::werte` can thus be built unchanged, and package 0002 can go back to `offen`
unchanged.** Its five readers from T47 point 3 see the same number as before; what has
changed is what it **means**. That is the whole purpose of this way: the correction sits
at the only place in the venture where it does not touch the most expensive building
block.

**T6 — Exactly one rounding rule, `/` on state quantities is forbidden, and a denominator
of zero is a hard error.** All divisions run through `teile_gerundet(zaehler, nenner)`
with rounding **of half amounts away from zero**.

**The rule stays, its justification changes language.** The previous versions justified it
with Rust's division behaviour. C++ has behaved the same way since C++11: for integer
operands `/` yields the algebraic quotient with the fractional part cut off, i.e. it
truncates **towards zero** (ISO/IEC 14882, `[expr.mul]`; before C++11 it was
implementation-dependent for negative operands, which is why the language standard from
T1 binds here as well and is not just a convenience). The same objection thus holds
unchanged: truncating towards zero is asymmetric across the sign — for a fund that per
`spiel.md` is expressly meant to be able to go long **and** short, it would silently
favour one direction and distort Maß 2.

Equally binding: `mal_geteilt(a, b, c)` computes `a·b/c` via an **`__int128`**
intermediate (ADR 0011, measure 3); the naive form overflows at amounts in cents times
shares in ten-thousandths. An overflow test after the fact would come too late for that —
the product would already be formed and, per T7, silently wrapped.

**Notation for the rest of the document:** `i128` stands everywhere as shorthand for
`__int128`, just as the alias of the same name stands for it in the core. `__int128` is
an extension of the type system, not of the language mode — it stays available under
`-std=c++20`, and `-Wpedantic` is switched off per T2b for exactly this reason.

**T6b — The division form is prescribed: sign first, then exactly one unsigned 128-bit
division on the absolute values.** That is, `betrag()` on numerator and denominator, one
`unsigned __int128` quotient, the remainder as `az − ganz·an` instead of as a second
operation, the round-up condition as `rest ≥ an − rest` instead of as `2·rest ≥ an`, and
the sign at the end.

That is no matter of taste but the answer to the speed objection from T1. The 947 ns of
the measurement are **one** implementation, not the language, and ADR 0011 presumes a
missing `__int128` as the cause. That is not so: the measured C++ version uses `__int128`
(`messung-stack/cpp/schritt.cpp`, lines 21–31). The provable difference lies one level
lower, and it stands in the artefact instead of in the presumption — `objdump -d`
executed in this run over the two stored programs:

| Implementation | Division form | Calls into the compiler runtime |
|---|---|---|
| `messung-stack/cpp/schritt` | divide signed **and** take the remainder | `__divmodti4` |
| `messung-stack/rust/schritt` | sign first, then divide absolute values | `__udivti3` |

A 128-bit division is no instruction on x86-64 but a call into the compiler's runtime
library, and the **unsigned** form is the cheaper one: the signed one first normalises
the signs and then calls the same unsigned routine. On top of that, the C++ version has
an additional 128-bit product for `rest_betrag * 2`, which the form prescribed here does
not need — and which, per the own remark in `festkomma.hpp`, could itself overflow at a
denominator near the `i128` limit.

**What I do not claim with this:** I have not re-measured the faster form; the gap of
1.92 might also hang on it only in part. The prescription stands regardless, because it
is the smaller computation under any compiler and because it clears away the overflow in
the round-up condition at the same time. **The question is decided not here but by
`ticks_je_sekunde` from the first test-bench finding** (section 9, reporting duty).

Mechanical proof: `objdump -d` over the core library must **not** contain `__divti3` and
`__divmodti4`; allowed is solely `__udivti3`. The 64-bit divisions of the counters and
remaining durations produce no such call and do not disturb the check.

**`nenner == 0` aborts and never silently becomes zero.** Finding 2 of the second review
arose at exactly this place: a backtest with a fund without assets needed those assets as
a denominator. A silent substitute value would have turned the error into a wrong number
instead of an abort; the fix belongs per T38 into the mode and not into the division
rule, but the rule remains the wall such an error runs into.

**T7 — Overflow never silently produces a wrong number.** The requirement keeps its
number and its sense; its means changes with the language. Rust would have settled it
with `overflow-checks = true` in the release profile — **one** setting. In C++ it is four
measures, three of them from ADR 0011 and one that is missing there.

**Measure 1 — `-fwrapv` in every profile.** With it, signed integer overflow is
**defined** as wrap-around in two's complement. For the real danger is not the overflow
but what an optimiser concludes from its supposed impossibility: without `-fwrapv` it may
throw away comparisons that „cannot happen", and a numeric error becomes a dropped
program branch. The switch stands in `werkzeugkette.cmake` and not only in the runner — a
determinism switch that holds only in the night run is none.

**Measure 2 — `-fsanitize=undefined,address` in the test profile**, with
`-fno-sanitize-recover=all`, so that a hit becomes an abort and not a message that a
green test run overwrites. The test bench runs over this. Because a sanitizer only finds
what it has compiled itself, the core is compiled a **second time** for the checks
(`kern_geprueft`); if the checks linked the unchecked library, the measure would secure
the test code and not the code at stake.

> **And here ADR 0011 is to be contradicted, in exactly one point.** It says there that
> an overflow that is unintended despite `-fwrapv` becomes, through measure 2, „im
> Nachtlauf laut statt still". **That is not so.** Since GCC 8, `-fwrapv` switches off
> the check `-fsanitize=signed-integer-overflow` — the sanitizer reports only *undefined*
> behaviour, and `-fwrapv` has just defined the overflow. The two measures cancel each
> other out at this one place; exactly for this reason the Linux kernel removed its UBSan
> overflow checks again after it had set `-fno-strict-overflow`.
>
> **What measure 2 therefore really delivers — and it is still a lot:** it covers the
> address sanitizer and the remaining UB classes (shift widths, alignment, array bounds,
> null pointers). That is exactly the failure class that C++ per T1 has open against
> Rust, and it is the reason to keep the measure unchanged. It is only **not** the answer
> to overflow as which ADR 0011 introduces it.

**Measure 3 — `__int128` for every intermediate value** of a multiply-divide, never an
overflow test after the fact (T6, T6b).

**Measure 4 — checked arithmetic in the core. It closes the gap that measure 2 leaves
open, and without it the venture would have no substitute for `overflow-checks = true`.**
Three forms, all independent of the compiler, because they check expressly instead of
relying on undefined behaviour. They are cut by the **kind of operation** and not by
place, so that no kind is left lying between them: the narrowing of every 128-bit
intermediate (1), addition and subtraction on `i64` (2), multiplication without a
following division (3).

1. **The narrowing from `__int128` to `i64` is the checkpoint.** Every value returning
   from a 128-bit intermediate into a state address passes through a guard that checks
   against `I64_MIN`/`I64_MAX` and on violation **aborts** instead of capping. Because T6
   routes every multiply-divide through `__int128` anyway, by far the largest part of all
   overflow opportunities lies exactly on this path — the check is thus no patchwork but
   sits at the bottleneck.
2. **What does not run through `__int128` — additions and subtractions on `i64` — uses
   `__builtin_add_overflow` and `__builtin_sub_overflow`.** They compute in unbounded
   precision and report whether the result fits into the target type; `-fwrapv` does not
   touch them, because they trigger no undefined behaviour but query one.
3. **A multiplication without a following division, too, runs through `__int128` and the
   guard from 4.1**, namely through `mal(a, b)` in `kern/include/kern/festkomma.hpp`,
   built like `mal_geteilt`: product as `i128`, return through `intern::nach_i64`. The
   intermediate cannot itself overflow there, because `|a·b| ≤ 2^126`, i.e. about
   `8,5·10^37`, stays below the `i128` limit `1,7·10^38` — the same argument that
   `potenz` in the same file already makes.

**Point 3 is added in this version, and the gap before it was no formality.** The
enumeration named „Additionen und Subtraktionen" and thereby left the **bare
multiplication of two `i64`** lying between the measures: measure 3 covers the
multiplication *with* a following division, 4.1 the narrowing of a 128-bit value, 4.2
addition and subtraction — and measure 1 makes their overflow precisely **defined**, that
is, silent. `overflow-checks = true` of the previous version covered every kind of
operation with *one* setting; here, a piece of content would have vanished with the
change of construction. The path into the error stands in the document itself:
`tsd_in_cent(x) = x · 100.000` (T50) has no division, no 128-bit intermediate and no
addition, `positionswert` computes `stufen · stufenwert` (T48) just as bare before it,
and the result goes per T47 straight into the fund's assets — that is, into settlement,
mandate, way of dying 1 and the bot target quantity `B`. The invariant
`0 < markt.wert < 9,2·10^13` (T30 check 2) catches **one** caller of these, at the round
end and not on the fund side; a detector after the fact is not the promise that T7 gives
in its heading.

**Why `mal` and not `__builtin_mul_overflow`:** both close the gap. The `i128` path has
the same abort path as 4.1 instead of a second one, keeps the whole of multiplicative
arithmetic under *one* rule, and `mal` stands next to `mal_geteilt` in the file that T6
designates as the core's only computation site anyway.

**The prescription holds for every multiplication, not for a list of places.** The world
step already multiplies bare in the price mix (T28), plus `fondsanteil`, `anleihekurs`
and `lobbypunkte_aus_geld` (T48, T50), and every new formula brings more; an enumeration
would here be the form that silently goes wrong at the next addition. The proof is
therefore a **mapping**, and I have carried it out once in this run:
`grep -rn ' \* ' kern/src kern/include` yields **52 lines** today, and each falls into
one of four admitted kinds — address arithmetic on `Index`/`std::size_t` (`zustand.hpp`,
`zustand.cpp`), unsigned arithmetic in `zufall.hpp` and `pruefsumme.hpp` (the two
exceptions below), an `i128` intermediate inside `festkomma.hpp`, or running text in a
comment. A fifth kind — two `i64` with magnitude meaning per T5 — does **not** occur
today, because `kern::werte` is not yet built; exactly there it arises. Such a hit
outside `festkomma.hpp` is a finding. `kern/test` does not stand under the rule but
checks it; six further hit lines come in there, of which two are real multiplications of
the form `static_cast<i64>(platz) * 10`, with which a check builds itself its input
values from a loop index.

**The abort is an exception and no `std::abort`**, and that for two mechanical reasons:
in compile-time evaluation a `throw` makes the expression no constant — a `static_assert`
that hits the abort path is thereby a **compile error** instead of an uncheckable case;
and CTest cannot book a signal as an expected result, whereas a check catches an
exception and attests it. What is not attestable is not built in this factory. Silent
the abort still is not: it has no return value that anyone accidentally computes on.

**Two places wrap deliberately, and they are the exception to T7:** the checksum from T12
and the random generator from T11. Both compute on **unsigned** types, whose wrap-around
has always been defined in C++ and whose computation rule expressly demands it. They get
no guard — a guard there would be no protection but an error.

The costs are a few percent and are priced into section 10.

**Sources on measure 2**, both retrieved 2026-09-02:
the GCC documentation on `-fsanitize=signed-integer-overflow` and `-fno-sanitize-recover`
(<https://gcc.gnu.org/onlinedocs/gcc/Instrumentation-Options.html>) — it describes the
check, **does not mention the interaction with `-fwrapv`**, which is why it stands here;
the evidence for the switch-off is the kernel patch „ubsan: remove overflow checks"
(<https://lkml.iu.edu/hypermail/linux/kernel/2102.1/03333.html>): *„Since GCC 8.0
-fsanitize=signed-integer-overflow doesn't work with -fwrapv. -fwrapv makes signed overflows
defines and GCC essentially disables ubsan checks."* The overflow builtins from measure 4
are described in
<https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html>.

**T52 — The same action sequence yields the same state on every target platform, and in
C++ that is a requirement instead of a matter of course.** *New in version 7.*

Why the requirement still holds at all: the save is unchanged **start value plus action
sequence** and not the state (frontmatter, **T22**). A save written on one machine and
loaded on another is therefore **recomputed** — if the computation runs differently
there, the save is silently a different one. T30 check 3 therefore compares the checksums
across the target platforms; that stays.

Rust had the property as a gift, because its integer types have the same width
everywhere. C++ does not have it as a gift, and the four places where it gets lost are
named:

1. **Only fixed-width types from `<cstdint>`** in every value that reaches a state
   address or enters a formula: `std::int64_t`, `std::uint64_t`, `std::uint8_t`.
   **`int`, `long`, `unsigned` and `std::size_t` are forbidden there.** `long` is 32 bits
   under Windows and 64 bits under Linux — that is the classic trap and the only one of
   these four that silently produces a wrong number instead of a warning.
2. **No `char` in a computation.** Whether `char` is signed is decided by the target
   architecture. Where a byte is meant, `std::uint8_t` stands.
3. **No value from `sizeof` or from an alignment** in a formula of the core.
4. **Shift operations** are admissible, and the random generator needs them. They are
   harmless here **because** T1 fixes C++20: since C++20, two's-complement
   representation is prescribed and right-shifting negative values is defined as
   arithmetic shifting. Under an older language standard both would be
   implementation-dependent. That is the second reason the language standard from T1
   binds and is no convenience — the first stands in T6.

**Observation on ADR 0011, reported and not decided by me:** the ADR's first argument
reads that cross-platform reproducibility falls away *if* the save stores the state
instead of the action sequence. But the ADR does not order this switch in its
consequences, and neither does my work package. **Until it is ordered, the requirement
holds** — which is why T52 stands here instead of a struck paragraph. The switch would be
a relief, not a necessity: the four rules above are mechanical and cost the build agent
nothing it does not pay anyway.

**T40 — The game length R is a quantity of the vintage, no constant of the code, and no
number derived from it stands as a literal anywhere.** That is the architectural answer
to finding 1, and it is the only one that avoids its actual price: the wrong number was
cheap, its spread into twelve derived quantities was expensive.

`R = manifest.stuetzstellen − 1` is formed when the vintage is loaded. From R and nothing
else arise at run time:

| Derived quantity | Formula | at R = 24 |
|---|---|---|
| result band „mandate fulfilled" | `1.000 … R × 1.000` | 1,000 … 24,000 |
| result band „survived" | `(R+1) × 1.000 … (R+1) × 1.000 + 3.000` | 25,000 … 28,000 |
| result band „way of dying" | `30.000 + 1.000 … 30.000 + R × 1.000` | 31,000 … 54,000 |
| game thirds (Maß 1, window of Maß 3) | `1…⌊R/3⌋`, `⌊R/3⌋+1…⌊2R/3⌋`, `⌊2R/3⌋+1…R` | 1-8, 9-16, 17-24 |
| profit threshold Maß 2 | `E(p) ≤ R × 1.000` | 24,000 |
| search-bot game | `R × (1 + 60)` | 1,464 |
| cost of Maß 1 per seed | `30 · R(R+1)/2 + R` | 9,024 |
| `exogen_ab_runde` per series | `bruchjahr − startjahr + 1` | DE policy rate: 1999 − 1997 + 1 = 3 |

**A bound belongs with this, because the result scale of `spiel.md` carries a genuine
literal at one place** — the 30,000 from which the ways of dying count. The vintage build
aborts at `R > 26` instead of producing a scale in which one value carries two meanings.

**The bound has stood unchanged at `R ≤ 26` since version 5, but has been tight instead
of generous since, and it has been recomputed there.** `spiel.md` version 4 struck the
capping of the shortfall; the band „survived" thereby ends at `(R+1) × 1.000 + 3.000`
instead of at `+ 2.000`. The lowest reachable value of the death band is
`30.000 + (R + 1 − R) × 1.000 = 31.000`, independent of R. The two bands are thus
disjoint exactly when `(R+1) × 1.000 + 3.000 < 31.000`, that is `R < 27`. At `R = 26`
„survived" ends at 30,000 and leaves 999 milli-rounds of air; at `R = 27` its upper end
would coincide with the lower end of the death band. **The wider band thus costs no round
of game length** — the same bound, but without reserve.

For the window 1997–2021 this is without consequence, and `spiel.md` lets the window only
become narrower, never wider. It is a wall, not a restriction — but it is one that must
be visible before the build and not after.

**T8 — Price level and exchange rate are carried and rebased.** The check vintage begins
per `spiel.md` version 3 in the year **1997**, long after the Plano Real; there the
rebasing never triggers. It stays nevertheless, because `spiel.md` expressly keeps the
vintages before 1997 as **play vintages**, and Brazil struck about twelve zeros between
1980 and 1994. Rule: if a country's price index exceeds 100,000 times its start value,
index, exchange rate and all nominal quantities of that country are divided by 1,000 and
the counter `basiswechsel` is incremented.

**Which quantities those are has been countable since T49 and therefore stands here
instead of in an interpretation: exactly five per territory** — the three sector prices,
the price level (class 5) and the exchange rate (class 6). Nothing else. The
macroeconomic amounts stand per T5 class 2 **at constant prices of the year 2015**, are
hence real and do not move along — and they do not move along for a **second**,
independent reason that can stand here since T53: class 2 is expressed in constant **US
dollars**, so it has no dimension in the local currency at all that a currency reform of
the host country could hit. For the 40 trade flows this holds only since T53 brings them
onto the same basis at vintage build; before, they arrived in current prices, and this
paragraph asserted a property for them that they did not have. Productivity stands in
class 7 and must not (otherwise a Brazilian base change would lower productivity by three
orders of magnitude); rates, shares, persons, lobby points and counters have no currency
dimension; the fund money stands in US cents, that is, in the numéraire, and is untouched
by a currency reform of the host country. „All nominal quantities of that country" was,
until version 5, a wording the build agent would have had to interpret; it is five
addresses, and they stand here by name.

Because it never takes hold in the check vintage, it would be unchecked code.
**Obligation on the test developer:** at least one game in the regression baseline (T31)
runs on a 1980 play vintage and passes through a base change. A branch the night run
never enters is a branch nobody knows.

**The backtest runs, for prices and exchange rates, on annual rates of change in basis
points, not on levels.** A percentage error on a level that wanders by an order of
magnitude over two decades measures the beginning and not the machine. `spiel.md` adopted
this requirement in version 3 and quantified it (300 bp); the computation rule stands in
T42, including the correction that a rebasing within the series forces.

**T9 — Fixed order, no hashing containers.** Countries, sectors, instruments and trade
pairs are dense index lists: **`std::array` of fixed length**, addressed via own index
types `LandId`, `SektorId`, `InstrumentId` — each an `enum class : std::uint8_t` or a
wrapper type over `std::uint8_t`, so that two kinds of index do not silently mix. A bare
`int` as an index is a finding.

**Forbidden in the core are `std::unordered_map` and `std::unordered_set`.** Their
iteration order depends on hash value, insertion order and standard library and is thus
exactly what T9 rules out. If a mapping is needed, it is **`std::map`** or
**`std::set`** — the ordered counterpart to Rust's `BTreeMap`, with an iteration order
that is a property of the key and not one of the memory.

**Two traps that C++ sets in addition and Rust does not:**

- **`std::sort` is not stable.** Where sorting happens — the test bench does it in
  T39 —, either `std::stable_sort` is to be used, or the sort must go by a key that
  orders the elements **uniquely**. A sort with ties is otherwise an order the compiler
  chooses.
- **The evaluation order of function arguments is unspecified.** As long as the core's
  argument expressions are free of side effects, this is without consequence — and
  exactly for that reason it is a requirement: **no argument expression in the core
  changes anything.** No `++i` and no assignment inside a call.

The six steps of the round run in the order from `spiel.md`, section „The loop", and this
order stands as a named constant list in the code, so that a reordering becomes visible.

**T10 — The world step does not draw.** Per `spiel.md` every rule is a threshold, a
counter or a computation; the intra-year swing too follows „deterministically from the
year's movement and the historical volatility range". So:
`schritt(zustand, aktionen, modus)` is a **pure function without a randomness argument**.
That is the cheapest way to satisfy requirement 1, and it makes the backtest an exactly
repeatable computation.

**What of that sentence is normative — decided 2026-09-08, package `0208`.** Normative is
**the absence of a randomness argument**, and nothing else about the argument list. The
three names are the illustration of the rule about randomness; they were written down
before any step needed a number. The touchstone: an added `const` argument that carries
no drawn number leaves purity, exact repeatability and requirement 1 exactly where they
are — a randomness argument would not. Whoever **removes** an argument, or adds one that
is not `const`, needs an ADR; whoever adds a `const` carrier that T10b covers does not.
The binding signature stands in T10b.

**T10b — The round takes the numbers that are not addresses as an argument, and there is
exactly one carrier.**

```
schritt(vorrunde, aktionen, konstanten, modus) -> (neuer_zustand, kette_dieser_runde)
```

with `konstanten` a `const kern::werte::Konstanten&`. The reason for the widening in one
line: T48 calls a name in a formula legitimate if it is a state address (T15), a
parameter key (T27), a vintage constant (T23) or one of its own twenty-two quantities —
and of those four kinds, two had no route into the round at all. A step body could read
the state and nothing else, so every rule in `spiel.md` that carries a coefficient was
unbuildable for want of a route, not for want of a rule. Measured in `0208`:
`zustimmung_elastizitaet` is a key of `parameter.toml`, `werte::Konstanten` does not hold
it, and `schritt` had no argument through which it could arrive.

**The carrier is not new, only its top link was missing.** `kern::werte::Konstanten`
already holds six T27 keys and the two T23 vintage constants `leitzins_start` and
`durchgriff`, and every derived quantity that needs one already takes it as
`const Konstanten&`. What widens is its contract: it stops being „der Ausschnitt daraus,
den die Bewertung braucht" and becomes **the numbers of a round that are not addresses** — both
kinds, one struct, one argument. A second struct beside it is rejected: it would need a
per-field copy between the two, and a field forgotten in a copy is caught by nothing.

**Which key belongs in it — the split, in the construction of T45.** Every key of
`parameter.toml` is exactly one of two kinds:

| Entry | Where it acts | Example |
|---|---|---|
| `Start(adresse…)` | the vintage build writes it into a state address; the round reads the address, never the key | `startkapital` → `fonds.kasse`, `fonds.anlegerbestand` |
| `Runde(feld)` | a rule reads it while a round runs; it is a field of the carrier | `stufenweite`, `zustimmung_elastizitaet` |

**A key without an entry aborts the vintage build, a key with two entries likewise, and a
carrier field that is neither a `Runde(feld)` key nor a T23 vintage constant aborts as
well.** The two-entry case is the important one, for the reason T45 already gives for
addresses: it is the spot where a quantity gets two masters. The count-off runs where
T45's runs and over the same file — **51 keys** by that file's own count-off of
2026-09-06, against the 310 addresses. It is the mechanism for the gap the calibration
file names itself and leaves open: „Zwei Fehler sind hier moeglich … eine Wirkung zu viel
(ein Regler ohne Modellregel) oder eine zu wenig (eine Modellregel ohne Regler)."
Answered by an abort instead of by a reading, once the sixth step stands.

**The tie to the state, and it is what makes the widening safe.** `Konstanten` is
default-initialised to zeros, and the calibration file says what a set at its bounds
does: „`druck_max = 1`, `gegenlobby_satz = 0`, `hebel_max = 0` und `nachahmer_max = 0`
schalten Lobbyismus, Gegenlobby, Hebel und Nachahmer praktisch ab." A round handed such a
set computes a dead world and reports nothing. Therefore: **`schritt` forms the checksum
over the `Runde(feld)` fields of the carrier and compares it with
`lies_alt(partie.parameter_pruefsumme)`; a mismatch is a hard error and no substitute
value, like the wrong read access in T39.** Construction as in T12 — field by field in
declaration order, fixed byte
order, FNV-1a-64 from `kern::pruefsumme` — never over the memory layout of the struct.

**And therefore the parameter checksum is a function of the values, not of the file
text.** The vintage build writes `partie.parameter_pruefsumme` with the **same** function:
one function, two callers, the construction of T47. `parameter.toml` notes today that the
checksum is computed „ueber diese Datei"; that reading is superseded here, for a measured
reason — the file is 1,315 lines of which 51 are key lines, so under four percent of it
carries a value. Over the file text every comment edit of the data builder would turn the
whole regression corpus red without a number having moved, and the core, which reads no
file (T2), could not check the number at all. *Reported to the project manager: the head
of `parameter.toml` needs one line drawn after. It is not mine to edit.*

**The vintage constants are tied one step weaker, and that is named and not hidden.** The
state holds `partie.jahrgang_id`, an identity and not a checksum of the vintage's
content; the content checksum is `daten_pruefsumme` and lies in the save (T22), outside
the core. The round can therefore prove that its parameter set belongs to its state, and
cannot prove the same of `leitzins_start` and `durchgriff`. That is enough because both
come out of the same vintage build that writes the start state, so a mismatched pair
cannot arise from a build — only from a hand-edited save, and that the checksum
comparison on loading catches one step later. The stronger tie is a vintage checksum in
the state, hence a 311th address, hence an ADR.

**What expressly does not change.** No state address (310 stays 310), no field of
`Zustand`, no target mask (T38), no save format: T22 already records `parameter_pruefsumme`
and `daten_pruefsumme` and recomputes the game on loading, so the parameter set has always
been an input to that recomputation — only the code did not say so. The carrier arrives as
a reference, so the cost line of section 10 does not move.

**T11 — Randomness exists at only two places, and it hangs on one root seed.**
First, the spread of the start vintages (a game should not always begin identically);
second, the bots and samples of the test bench. The generator is written in-house —
SplitMix64 for derivation, xoshiro256\*\* for generation, twenty lines, fixed in the
repo, **no third-party library** (T2): a version jump of a foreign randomness kit would
otherwise devalue every saved game.

**`<random>` from the standard library is excluded too, and the reason is sharper than
the general one.** The standard fixes the *generators* (`std::mt19937` yields the same
sequence everywhere), but **not the distributions**: what `std::uniform_int_distribution`
makes of a bit sequence is left to the standard library and differs between libstdc++ and
libc++. A save that rested on a distribution would thereby be bound to a
standard-library version instead of to a computation rule. The reduction to a value range
is therefore written out in the core and is part of the checked code.

Every stream is **derived**, not carried forward:

```
strom = splitmix64(wurzelstartwert, jahrgang_id, parameter_pruefsumme,
                   zweck_id, runde, index)
```

A running stream would have the property that a single new draw anywhere shifts all later
draws and thereby turns the whole regression baseline red without anything substantive
having changed. That is the requirement on which the difference between „improving" and
„changing" later hangs. The `zweck_id` is a named enumeration (`JAHRGANGSSTREUUNG`,
`ZUFALLSBOT`, `BUENDELZIEHUNG`, `SUCHBOT_KANDIDATEN`) and is never written via a number.

**In mode `weltlauf` not a single stream is drawn** (T38): there are no bots, no samples
and no vintage spread. The backtest is thereby not only reproducible but seed-free.

**T12 — Canonical byte form and checksum.** `Zustand` is put into bytes via an expressly
written function (fixed field order, `i64` in little-endian), **never via the memory
layout of the struct**. Over this runs FNV-1a-64, likewise implemented in the core. This
checksum is the currency of all regression tests.

**In C++ the shortcut is especially near at hand and therefore expressly forbidden:** a
`memcpy` over the struct or a `reinterpret_cast` to `unsigned char*` are two lines and
yield a checksum that takes along the padding bytes between the fields and the byte order
of the target system. Padding bytes have no fixed content — the same game would yield two
checksums on the same machine. The byte form is written field by field, and the
`reinterpret_cast` stands on the grep list from T2b anyway.

## 3. Trennung von Modell und Darstellung

**T13 — The component direction is the separation, and CMake enforces it.**

```
kern            (keine Abhängigkeit)      Zustand, Regeln, Kette, Festkomma, Zufall, Prüfsumme
  ^
daten           -> kern                   Jahrgang laden, Sollreihen, Parameterdatei
  ^
schnittstelle   -> kern, daten            Protokoll, drei Zustandsebenen, Partieformat
  ^          ^
konsole      pruefstand                   Binärprogramme: Text und Protokoll / Bots und Maße
  ^
oberflaeche  -> schnittstelle             Binärprogramm (vertagt, ADR 0010)
werkzeuge/aufbereitung -> daten           einmal je Jahrgang: Rohdaten -> Jahrgang
```

Each component is its own CMake target with its own directory; the arrows are
`target_link_libraries`, and the visibility of the header directories follows them.
**Whatever is not linked does not find the headers** — `kern` knows neither screen nor
file nor clock, and that the model never asks the view for anything is thus not an
agreement but fails at the compiler as soon as someone tries.

*The difference from the former version, so it does not go unnoticed:* Its build tool
would have enforced the direction, because a component without an entry in the dependency
list is not even found. CMake enforces it only as long as the header directories are
assigned **`PRIVATE`** or cleanly `PUBLIC`; a global `include_directories()` at workspace
level would silently lift the separation without any build failing. **`include_directories()`
is therefore banned throughout the venture**; header directories are assigned exclusively
via `target_include_directories` on the respective target.

**The same holds on the link side, and that is the second half of the same thought.** A
`link_libraries()` without a target applies to every target created afterwards in the
directory and its subdirectories, and since CMake 3.13 `target_link_libraries(<ziel> …)`
may stand in a different `CMakeLists.txt` than the one in which `<ziel>` is created. Both
attach a dependency to a component without touching its own file — the header side loses
the separation that way, the link side the zero dependency of the core from T2.
**`link_libraries()` is therefore banned throughout the venture, and
`target_link_libraries(<ziel> …)` stands exclusively in the `CMakeLists.txt` of the
directory in which `<ziel>` is created with `add_library` or `add_executable`.** With that
the dependency list of a component is again readable in exactly one place, and the third
pattern match from T2 has something to check against.

These are the two places where this build approach needs a check rule where the old one
had a tool property.

**Within `kern` there is one module whose cut is a requirement and not a matter of taste:
the namespace `kern::werte` with the header `kern/include/kern/werte.hpp`.**
There and only there stand the derived quantities from T48 and the three scale transitions
from T50; `tsd_in_cent`, `lobbypunkte_aus_geld` and `lobbypunkte_aus_schaden` live in the
sub-namespace `kern::werte::intern` and are thereby marked as not public.

The public interface of this module is thus **the same list** that T48 enumerates — a
reviewer lays the declarations in `werte.hpp` outside `intern` against the table and is
done. That is the mechanical proof that finding 1 of round 6 would have needed and that
the counting step from T45 could not deliver, because it counts addresses and not
functions.

*The limit of this proof belongs with it:* `intern` is a marking, not a lock — C++ has no
`pub` for the functions of a namespace. A call from outside compiles. The lock is
therefore the grep rule from T50: a hit of
`grep -rn 'tsd_in_cent\|lobbypunkte_aus' kern/` outside this one module is a finding. Two
weak proofs at the same spot are cheaper here than one strong proof the language does not
offer.

**T14 — The text interface is part of the product, not a tool.** `konsole` plays the game
completely — state in three levels, actions, saving, loading. It is at once the
interface through which agents play (requirement 3), and the fallback path in case
the graphical interface ever jams. What `oberflaeche` shows must be derivable from the
output of `konsole`; if it is not, it belongs in the core.

## 4. Datenmodell

**T15 — `Zustand` is a value of fixed size without memory allocation: 310 `i64`, i.e.
2,480 bytes.** Fixed fields, `std::array` of fixed length, **no `std::vector`, no
`std::string`, no pointer, no `std::unique_ptr`**. Copying is thereby a memory move of
2.5 kB (about 200 nanoseconds) — the precondition for the test bench starting millions
of replays from intermediate states.

**Two `static_assert`s make this a checked property instead of a description**, and both
belong in the same header as the type:

- `static_assert(std::is_trivially_copyable_v<Zustand>)` — it fails the moment somebody
  builds in a `std::vector` or a custom copy constructor. That is the cheapest guard of
  the whole data model: it defends not the size but the property from which the size
  follows.
- `static_assert(sizeof(Zustand) == 2480)` — it fails on padding bytes and on any address
  count other than 310. Together with T12 that means: the struct *is* free of padding,
  and the byte form is still written field by field. The belt does not replace the
  braces — the checksum must not hang on the memory layout even when the layout happens
  to fit.

Five territories (USA, China, Germany, Brazil, rest of world), three sectors, two of them
with trade rows, four policy instruments. **Every row names its origin in `spiel.md` so
that the sum can be recounted:**

| Group | Fields | Count | Origin in `spiel.md` |
|---|---|---:|---|
| per sector (3×) | value added, capital stock, employment, sector price | 12 | "The state", per country |
| aggregate | population, labour force, productivity, price level, inflation, policy rate, exchange rate, government debt, budget balance | 9 | ibid. |
| political | approval, supervision counter, influence | 3 | ibid. |
| instruments (4×) | level, pending pressure, counter-pressure, remaining delay | 16 | ibid. |
| remaining durations | `marktverbot_rest`, `lobbykosten_rest`, `regierungsdruck_rest` | 3 | counterforce 1 (third threshold) and counterforce 2 |
| bookkeeping | `basiswechsel` | 1 | T8; origin per T46 |
| **per playable country** | | **44** | |
| **four playable countries** | | **176** | |
| **rest of world** | sectors 12 + aggregate 9 + `basiswechsel` 1; **no** instruments, approval, supervision, influence, remaining durations | **22** | "The rest of world" |
| trade | territory × counterpart × tradable sector = 5 × 4 × 2 | 40 | "Trade" |
| world prices | per tradable sector | 2 | "What must hold for price formation" |
| imitator counters | country × sector = 4 × 3 | 12 | "The fund" |
| market basket | `markt.wert`, `markt.rendite` | 2 | "The fund", market return; rule in T33 |
| fund, aggregate | cash, leverage level, visibility, investor stock, market share | 5 | "The fund" |
| fund, excess return | last three rounds | 3 | ibid. |
| position slots | 12 country×sector, 4 currency, 4 bond | 20 | ibid., T16 |
| stakes | 12 country×sector × (share, remaining exit duration) | 24 | action 2 |
| game | round, vintage id, parameter-set checksum, mandate status | 4 | — |
| **sum** | | **310** | |

Recount: `4 × 44 + 22 = 198` for the territories, `40 + 2 + 12 + 2 = 56` for the world,
`5 + 3 + 20 + 24 = 52` for the fund, `4` for the game. `198 + 56 + 52 + 4 = 310`.
`spiel.md` names the same number and points here for the breakdown. **The same 310
addresses are split up a second time in T45, this time by their origin** — the two sums
run over the same set and must both come out; that the second did not in version 4 is
the reason for T46.

**The rest of world carries four addresses that no rule reads** (`leitzins`,
`wechselkurs`, `staatsschuld`, `haushaltssaldo`). They stand here because the aggregate
block is built the same for all five territories — uniform addressing per T17, the same
reasoning as the permanently empty slot from T16. Their treatment stands in T46, and so
does their write rule (`Vortrag`, no other read access).

**`landespreis` gets no row, and that is the remedy of finding 6, not its
circumvention.** Per `spiel.md` the quantity is the previous round's sector price. It
therefore has no address of its own but a **read access** of its own — see T39. A field
for it would be a second copy of the same number and thus an opportunity to let the two
drift apart.

**T16 — Positions are slots, not a list.** There are exactly twenty possible positions;
a position is a signed step count on a fixed slot, zero means "none". That removes every
question about maximum count, ordering and merging, and the state stays comparable
(T12).

**One slot is permanently empty:** the currency USA. The US dollar is the numéraire; a
position on it would be directed against itself. The slot remains for the uniform
addressing (T17); the admissibility check never offers it (T32). 19 of the 20 slots are
playable; whoever counts 20 counts addresses, not possibilities.

**T17 — Every quantity has a stable address.** `land.DE.sektor.2.preis`,
`land.BR.instrument.zoll.stand`, `fonds.position.CN.1`, `handel.DE.CN.1`, `markt.rendite`.
These addresses appear in the log, in the chain, in the test templates and in the
interface. They are part of the interface version: whoever renames one invalidates the
regression corpus and needs an ADR.

**T17b — The address tree has no node `gebiet`, and `gebiet.<G>.` is a collective
notation of this document.** Four places use a prefix `gebiet.…` where a statement holds
for all five territories at once. It is **not an address**: it appears in no log, no
chain, no test template and no interface, and per T20 there is no `detail gebiet.US`. It
is resolved as follows, and the resolution is complete:

| `<G>` stands for | resolved prefix | addresses |
|---|---|---:|
| one of the four playable countries | `land.US.`, `land.CN.`, `land.DE.`, `land.BR.` | 4 × 44 = 176 |
| the rest of world | `restwelt.` — without a code, neither `gebiet.RW.` nor `land.RW.` | 22 |
| **together** | | **198** |

The 198 are the same number as the territory column of the recount for T15
(`4 × 44 + 22 = 198` for the territories). The spelling of the placeholder follows the
rule this document already uses for `land.<L>.` against `land.<l>.`: **upper case** means
"any territory" in running text, **lower case** means "the value of this function
argument" (T48, `landespreis(g, s)`). Both cases resolve the same way.

**Why this direction and not the reverse** — four reasons, each carrying on its own:

1. **T17 enumerates the address form itself** and writes `land.DE.sektor.2.preis` and
   `land.BR.instrument.zoll.stand`; a node `gebiet` does not occur there. T20 likewise
   names `land.US` and `land.CN.sektor.1` for `detail`.
2. **T45 would contradict T46 within the same section.** The row `Vorgabe(T-Nummer)`
   gives as its example, verbatim, „`restwelt.basiswechsel` → 0 (T8)" — one of the eleven
   addresses that T46 points to conclusively a few paragraphs later. One of the two
   places would have to be wrong, and neither is.
3. **The rest of world carries no code in its prefix.** `RW` occurs solely in the 40
   trade addresses (`handel.RW.US.1`), there as a component between two dots and not as
   a block prefix. A `gebiet.RW.` would give the rest of world a second spelling without
   simplifying any rule.
4. **The price would be not five addresses but 198.** Per T15, `basiswechsel` is a field
   of the territory block just like `leitzins` and `preisniveau`. Whoever names it
   `gebiet.US.basiswechsel` must name `gebiet.US.leitzins` along with it — otherwise one
   and the same block carries two prefixes. Carried to the end, the reverse direction
   renames 198 of the 310 addresses, thereby invalidates the regression corpus per T17
   and needs an ADR. The gain would be zero: the same quantities under other names.

**The two consequences, both looked up and both fitting — no "presumably".**
`daten/adressen.md` lists the five `basiswechsel` rows as `land.US.basiswechsel`,
`land.CN.basiswechsel`, `land.DE.basiswechsel`, `land.BR.basiswechsel` and
`restwelt.basiswechsel`, running numbers 44, 88, 132, 176 and 198. That is exactly the
resolution of the T46 row; the register stays **unchanged**, and its markers do not hang
on it either — under *Was hier offen bleibt und hier nicht entschieden wird* it works
out itself that both conceivable answers yield the same marks. What remains to be added
there is the answer alone; that is work on the register and belongs in a package of its
own. `gebietspraefix()` in `kern/src/zustand.cpp` appends `land.`, the territory code
and a dot for the four playable countries, and `restwelt.` for the rest of world; the
comment above the function says so verbatim. That is the machine version of this rule —
**fitting, no change to the core and no ADR.**

**The four occurrences, conclusively.** Each is resolved by the rule; none is an
exception:

| Place | Form | resolves to |
|---|---|---|
| **T28**, paragraph on the price mix, „mit `landespreis` = … nach T39" | `lies_alt(gebiet.<G>.sektor.<s>.preis)` | 15 addresses — 5 territories × 3 sector prices |
| **T39**, last paragraph, "With that `landespreis` has its place" | `lies_alt(gebiet.<G>.sektor.<s>.preis)` | the same 15 |
| **T46**, first table row | `gebiet.<G>.basiswechsel`, all five territories | 5 addresses — running numbers 44, 88, 132, 176, 198 |
| **T48**, number 13, `landespreis(g, s)` | `lies_alt(gebiet.<g>.sektor.<s>.preis)` | the same 15, `g` as argument |

The 15 are counted off against `daten/adressen.md`, not computed: running numbers 4, 8,
12, 48, 52, 56, 92, 96, 100, 136, 140, 144, 180, 184 and 188 carry a sector price.

**Two of the four places wrote `gebiet.sektor.preis` up to this version** — without
placeholders, that is, without saying which territory and which sector is meant. They
now carry them. The address set remains 310 and the table in T46 row for row as it was:
this ruling changes no address; it says what a notation means.

**The count before and after the rule, so that nobody has to recount it** — for "four
places" above and the result of a full-text search are not the same number, and without
this paragraph every reader must resolve the difference themselves. **Counted as fixed
text, not as an expression** (`grep -oF`; the dot is a dot and not a wildcard), and the
three patterns stand in the table with an **escaped** dot (`gebiet\.`). Together these
two ensure that no line of this paragraph is itself a hit: it nowhere names the
unescaped form, not even as a counter-example. The numbers of the column "now" therefore
hold for the document including itself.

| Pattern | before this ruling | now |
|---|---:|---:|
| `gebiet\.<G>\.` | 1 | 8 |
| `gebiet\.<g>\.` | 1 | 2 |
| `gebiet\.` — the loosest form, everything together | 4 | 17 |

**The 17 was recounted on 2026-09-05 and stood one too low in version `a127600`.** This
paragraph then still carried the unescaped form as a counter-example („statt …") and was
thereby itself the eighteenth hit, which the table did not count. It no longer names it;
the count now is 17, and the breakdown below comes out.

**Before: four, and they were exactly the four T-numbers of the table above:** T39 and
T28 in the short form without placeholders, T46 as the `<G>` row, T48 as the `<g>`
formula. To be looked up in the version before this ruling,
`git show ce59b8b^:specs/0016-…/technik.md`.

**After: seventeen, and none of them is a fifth place.** Ten carry a placeholder:
**five** stand in T17b itself (the heading and the four rows of the occurrence table),
the other **five** are spread over the same four T-numbers as before — T46 carries two,
the table row and the paragraph that points from there to this rule. The remaining
**seven** all stand in T17b and are **counter-examples, not uses**: three times
`gebiet\.US` and twice `gebiet\.RW\.` in the reasoning why these addresses do not exist,
once `gebiet\.sektor` as a citation of the old short form, and once `gebiet\.` with an
ellipsis in the opening sentence. `4 → 17`, of which `13` are new: `5 + 1` in T17b and
T46 with placeholder, `7` as counter-examples. **No exception.**

**T18 — The chain is generated, not reconstructed — and every quantity of the target
mask is written exactly once per round.** The fields of `Zustand` are not writable
outside the core; inside, nobody writes directly but through
`Schreiber::setze(adresse, wert, ursache, verzoegerung, beitrag)`. Every call appends an
`Ursachensatz`:

| Field | Content |
|---|---|
| `runde` | in which round written |
| `ziel` | address per T17 |
| `alt`, `neu` | values in the quantity's scale |
| `ursache` | `Aktion{nr}` \| `Instrument{land,instr}` \| `Gegenkraft{art}` \| `Markträumung{sektor}` \| `Vortrag{adresse}` \| `Jahrgang` |
| `verzoegerung` | how many rounds lay between cause and effect |
| `beitrag` | this cause's share of the change, in per mille |

The `Schreiber` keeps a bit field over all 310 addresses. **A second write to the same
address in the same round is a hard error**, not an overwriting value. An address that
does not change is written anyway, with the cause `Vortrag` — "unchanged" is a statement
and not a gap.

That is the machine version of the requirement from `spiel.md` and at the same time the
cheapest way to make the claim there about **eight** round-spanning feedback channels
checkable: a feedback within the round necessarily produces a second write and dies
here, instead of arising unnoticed as a ninth channel.

**Eight instead of seven since `spiel.md` version 5**, and the increase is the yield of
finding 1: channel 8 is *Vermögen → Lobbybudget → Instrument → Kurs → Bewertung →
Vermögen*. It was there the whole time; its link „Bewertung" only became a computed step
when T47 and the section *What a basket is worth* wrote down the valuation formulas.
That is the reason why a missing **function** is more expensive than a missing number:
it hides a feedback channel. Cost:
40 bytes per round, one bit test per write.

**T18b — The start-value entry is the second write path, and the bound of the round
number stands at both ends of it.** Before round 1 the state is not written by the
`Schreiber` but by a **start-value entry** (`kern::zustand::Startbelegung`), the
counterpart of T18: no `Ursachensatz`, no bit field, no mask — a start value has no cause
in the model, it is the beginning every later cause refers to. It has therefore also had
no value range, and that is the gap this rule closes.

**The entry checks the four addresses of the `partie` block and no others** — round
number, vintage id, parameter-set checksum, mandate status (T15; the last two rows of
T38's mask table). For `partie.runde` (address 307) the bound is
`0 ≤ runde ≤ I64_MAX − 1`. The remaining 306 are checked by their reader and once per
round by T30 check 2; **the entry does not repeat the eight bounds**. The derivation of
that cut and the consequence for T22 are in section 25; **the bounds of the other three it
deliberately holds open** — it prescribes *that* they get one and leaves *which* to the
package that touches them.

**The check in `schritt` stays, and it is not the same check.** The round increments
`partie.runde` itself: a round on `I64_MAX − 1` leaves `I64_MAX` behind, and the next one
dies on the state its predecessor produced (measured,
`befunde/raender/bruch-2026-09-06.md`, situation 5). The entry covers the value that comes
in, `schritt` the value the round makes — disjoint causes, not one check written twice.
**In the error case the entry reports.** It is reached first, and it is the only one of the
two that can name where the value came from (the provenance row of T45); `schritt`'s
message names the address. Never both for one value.

**T39 — There are two read accesses, and the wrong one dies immediately.** The
`Schreiber` holds the previous round's state (`alt`, immutable) and the emerging state
(`neu`):

- `lies_alt(adresse)` — the value at the end of the previous round. Always available.
- `lies_neu(adresse)` — this round's value. **If the address has not yet been written in
  this round, that is a hard error**, not a silent fallback to `alt`.

The silent fallback would be the more dangerous convenience: it makes the result depend
on the order of the six steps without it standing anywhere that it does. With the abort,
the cycle-freedom of the round order is no longer a promise but a property that every
run proves — including the one at the buyer's.

With that `landespreis` has its place: in the market clearing (T28) it is
`lies_alt(gebiet.<G>.sektor.<s>.preis)`, prefix per T17b. In round 1 that is the start
value of the vintage, per `spiel.md` the index 10,000.

**T38 — The mode is a property of the run, not of the state — and it brings a target
mask with it.** That is the remedy of finding 2 on the architecture side.

`spiel.md` knows two modes: `spielmodus` and `weltlauf`. The mode is **not** in the
state. Two reasons, both compelling: it would be a 311th field and would contradict a
number that `spiel.md` names; and it describes not the world but the way of computing
it. It is an argument of `schritt` (T10), stands in the header of the save (T22) and in
every finding. Whoever recomputes a game in the wrong mode gets not a wrong number but a
checksum break on loading.

**The mode is not the only argument of this kind, and a step builder looks here first.**
Since `0208` the round carries a second one: `const kern::werte::Konstanten&`, the
parameter keys and vintage constants that the rules name beside the addresses. Same test,
same reason — it describes not the world but how it is computed, it is no 311th field,
and it stands in the save header as `parameter_pruefsumme`. Where a key of `parameter.toml`
belongs, how the carrier is tied to `partie.parameter_pruefsumme` and what T10's signature
sentence does and does not bind: **T10b**.

To each mode belongs a **target mask**: the set of addresses written per round in this
mode. At the end of the round the `Schreiber` checks in both directions — every address
of the mask written exactly once, no address outside the mask touched. Either is a hard
error, not a report.

| Block | Addresses | in `weltlauf` |
|---|---:|---|
| per playable country: sectors (12), aggregate (9), approval (1), instrument level (4), `basiswechsel` (1) | 27 × 4 = 108 | **yes** |
| per playable country: supervision counter (1), influence (1), instruments without level (12), remaining durations (3) | 17 × 4 = 68 | no |
| rest of world | 22 | **yes** |
| trade | 40 | **yes** |
| world prices | 2 | **yes** |
| imitator counters | 12 | no |
| market basket | 2 | no |
| fund (aggregate 5, excess return 3, slots 20, stakes 24) | 52 | no |
| game: round, vintage id, parameter-set checksum | 3 | **yes** |
| game: mandate status | 1 | no |

Recount: `108 + 22 + 40 + 2 + 3 = 175` in the mask, `68 + 12 + 2 + 52 + 1 = 135`
outside, `175 + 135 = 310`. The mask `spielmodus` covers all 310.

What lies outside the mask keeps its start value — `spiel.md` demands it so. In the
weltlauf the fund thus does not start with zero wealth; it is **not computed at all**:
no wealth, no return, no excess return, no investor withdrawal, no manner of death. The
denominator from finding 2 does not arise, instead of being caught. The test bench
reports the mask size in every finding.

The mode acts at exactly four places and nowhere else — steps 2 and 6 of the round are
dropped, of step 5 only approval and change of government run, and in step 3 the policy
instruments come from the vintage instead of from the lobby pressure. The change of
government is computed and reported but writes nothing; that the oracle is blind at this
point belongs in every finding per `spiel.md` and therefore stands in the finding
template, not in a footnote.

**T19 — The chain does not belong in the state.** `schritt` returns
`(neuer_zustand, kette_dieser_runde)`; the session collects the chains in a `Verlauf`.
That keeps `Zustand` small and comparable, and the test bench can throw the chains away
when it only counts results. The recording capacity per round is fixed; reaching it is a
hard error and not a silent truncation — a truncated chain would be a lie to the buyer.

## 5. Die drei Zustandsebenen (G8)

**T20 — Three queries, two output forms, one source.** Each level arises from the same
data type and is emitted either as text (for humans and logbooks) or as a JSON line (for
agents and the interface). Integers stay integers; the scale is stated in the header of
the answer, division happens only in the view.

- **`uebersicht`** — one line per territory, one per fund, one for the market:
  `DE | BIP 3.412 | Zins 250bp | Zoll 380bp | Haushalt -210bp | Fondsanteil 420 | Einfluss 1.700`
- **`detail <adresse>`** — one object in full, for **every** addressable unit per T17,
  not only for countries: `land.US`, `fonds`, `land.BR.instrument.zoll`,
  `land.CN.sektor.1`, `markt`.
- **`diff <von> <bis>`** — per changed quantity: old, new, change, **and the cause chain
  from T18**, resolved backwards to the triggering action or counterforce, with delay and
  contribution per link. The difference of two states says *what*, the chain says *why*;
  both are output, the chain is what counts.

## 6. Maschinenschnittstelle und Partieformat

**T21 — One command per line, one JSON reply per line, over standard input and output.**
No network service, no port, no credentials — and therefore no contact with house rule 2.
Commands: `neu {jahrgang, modus, startwert}`, `zustand {ebene, adresse}`,
`aktionen` (those admissible this round), `setze {aktionen: […]}`, `runde`,
`kette {von, bis}`, `speichern {pfad}`, `laden {pfad}`, `pruefsumme`.
Every reply carries `schema_version`. A recorded session is thereby, by itself, a test
template.

**T32 — The list of admissible actions has a canonical order, and it is part of the
interface version.** Sorting is by `(Aktionsart 1…5, Zielkennung, Stufe)`; the target id is
the fixed index order from T9. Reason: per `spiel.md`, Maß 1 draws actions **without
replacement from the list of actions admissible in this round** (T35). Were the order a
side effect of generation, the decision density would hang on a loop order that nobody
wrote down. Changing the order devalues the regression corpus and needs an ADR.

**The list is built once per round against the round-start state**, not anew after every
placed action. Per `spiel.md` no action has a point in time within the round; a list that
changes between two slots would introduce exactly that point in time. What concerns a
bundle as a whole — the same slot twice, cash overdrawn, more than three actions — is
checked by `buendel_zulaessig(zustand, buendel)` against the same round-start state. Two
checks, both stateless within the round.

**Two admissibility conditions are added with `spiel.md` version 5, and both follow from
the share scale.** An action 1 or 2 after which `fondsanteil(l, s)` would lie above
**10,000** is inadmissible — a share above one hundred percent is not a share, and
counterforce 1 and the price shock read exactly this number. Likewise inadmissible is an
action after which `|stufen(p)| > stufen_max` would hold. Both are checked **on the
bundle**, not per action: three top-ups of the same slot in one round are individually
admissible and jointly not. The invariant test (T30 check 2, bound 7) checks afterwards
that the admissibility check held — the check protects the player, the test protects
against the check.

**T32b — What the target id runs over, per kind — five lines, and the kind without a
target has one too.** The Zielkennung is the **place of the target in the order in which
`Zustand` already addresses it** (T15, T17), never a place in this round's admissible
list. The list is rebuilt every round (paragraph above), and a save replays actions by
number (T22): an id that moved when admissibility moved would make yesterday's save a
different game today.

| Kind | The set its Zielkennung runs over | Size | today | The T9 order on it — and where that order already stands |
|---|---|---|---:|---|
| 1 Position | the position slots of T16 | `LAENDER·(SEKTOREN+2)` | 20 | the ordinal of `Steckplatz`: sectors `land·SEKTOREN + sektor`, then currency `STECKPLATZ_WAEHRUNG_ERSTER + land`, then bond `STECKPLATZ_ANLEIHE_ERSTER + land` |
| 2 Stake | country × sector, playable countries only | `LAENDER·SEKTOREN` | 12 | `land·SEKTOREN + sektor` — the address arithmetic of the stake block (T15 row *stakes*) |
| 3 Lobby budget | country × policy instrument | `LAENDER·INSTRUMENTE` | 16 | `land·INSTRUMENTE + instrument` — the instrument block inside the country block (T15 row *instruments*) |
| 4 Leverage | the single address `fonds.hebelstand` | 1 | 1 | a one-element set, and the place of its only element is **0** |
| 5 Visibility | the single address `fonds.sichtbarkeit` | 1 | 1 | likewise **0**; the contradiction in `spiel.md` is resolved in section 24 |

Three consequences, each of which would otherwise be guessed later:

- **A kind without a target carries 0, not "any value".** Every action goes into the save
  and thereby into the checksum (T22, T12); an unread field with two possible values makes
  two files out of one game.
- **Kind 1's set has twenty places, its admissible list nineteen.** The permanently empty
  currency slot USA keeps its place in the order and is never offered (T16). Place count is
  not possibility count.
- **The domain is checked where the list is built and where an action arrives from outside
  (T21 `setze`, T22 load) — not in the type that carries the order.** That type orders; it
  compares at the edges of its value range and must keep doing so.

Derivation of each line, the resolution at kind 5, and what the fifth country and the
exchange venues change: section 24.

**T22 — A save is vintage, mode, seed, action sequence and checksum, not the state.**
File: `{schema_version, jahrgang_id, modus, daten_pruefsumme,
parameter_pruefsumme, startwert, aktionen: [[runde, aktion…]], end_pruefsumme}`. On
loading, the game is recomputed and the checksum compared; if it deviates, the program
reports a determinism break instead of playing on. Three wins at once: the buyer notices a
determinism error first, the regression corpus **is** the save folder, and a file stays
under two kilobytes. Cost: R world steps on loading, at R = 20 and the plan value of 10 µs
thus 0.20 milliseconds.

## 7. Datenschicht

**T23 — The vintage is a product, not a program part.** `werkzeuge/aufbereitung`
reads the frozen raw files and writes `jahrgang-<jahr>.bin`,
`sollreihen-<jahr>.bin` and a `manifest.toml` with SHA-256 per input and output, source,
licence and retrieval date. The build of the game loads **nothing** from the net. The
vintage contains:

1. **Start values** for every state quantity with a data anchor; the quantities without
   an anchor come from the table *Every quantity without a data anchor* in `spiel.md`,
   from `parameter.toml`, from the manifest or from **T46**. Which address comes from
   where is decided by T45, and the assignment is counted off there.

   **Two start values arise from two series each, not from one, and both keep the rank
   `Datenanker`.** Series 1 delivers one GDP per territory, series 3 one capital stock
   per territory; T15 carries **three** of each per territory. The same rule forms both,
   with the sector shares from series 2 normalised to 10,000:

   ```
   wertschoepfung[g][s] = mal_geteilt(bip_start[g],          sektoranteil[g][s], 10.000)
   kapitalstock[g][s]   = mal_geteilt(kapitalstock_start[g], sektoranteil[g][s], 10.000)
   ```

   The provenance entry reads `Datenanker(1 × 2)` resp. `Datenanker(3 × 2)`; the count
   in T45 does not change through this, because both address groups are already carried
   there as anchors. The rule for the capital stock is added in version 6 — `spiel.md`
   version 5 demands it, because the basket value has hung on the sector capital stock
   since then, which is thereby for the first time a quantity someone must compute. The
   split error is the same as for value added and without consequence for the backtest,
   because the twelve sector-share target series arise from **the same** normalisation.

   **The prescription table of version 4 at this spot is struck, and that is not a
   retreat but the avoidance of an abort.** It carried
   `land.<L>.instrument.<I>.druck` and `…​.rest` with start value 0, 16 addresses each, because
   `spiel.md` did not carry them back then. `spiel.md` version 4 has taken all 32 into
   its table. Were they still carried here as a provenance entry, they would carry
   **two** entries — and exactly that aborts the vintage build per T45. Their provenance
   is `Entwurf` from now on.

   What stays is the justification, because it forces the value instead of choosing it,
   and because a later reader otherwise does not know why 0 stands there: both are
   running counters of step 3, pressure arises per `spiel.md` solely through action 3,
   and before round 1 no action has taken place. Did one of the addresses carry a
   non-zero value at game start, there would be a cause without an action, and the chain
   from T18 could not name it in round 1. Only the four playable countries carry
   instruments (T15), hence 16 each and not 20 each. **This paragraph is a proof, not a
   provenance entry;**
2. **Target series** for the `L_R(S+5) − n` reported series from `spiel.md` plus the trade
   block over `(L_R+1)·L_R·(S−1)` flows — today **31** and **40** —, per series with the
   classification from T37. The vintage carries all 31, because `gesetzt` and `abgeleitet`
   are reported; **target series in the narrow sense are `L_R(S+4) − n` = 27** since the
   cut of 2026-09-03. The wording belongs to `0068`, the count in `L_R` to section 26;
3. **historical policy paths** for policy rate, tariff level and budget balance. The
   fourth lever, financial-market regulation, has no anchor and stands fixed in the
   `weltlauf` at its start value — which makes the oracle blind for this instrument, and
   that belongs in every finding;
4. **exogenous paths** per T25;
5. **constants of the vintage**: **fourteen values** — `durchgriff[Gebiet][handelbarer
   Sektor]`, that is ten in ten-thousandths, and **`leitzins_start[l]`**, four in basis
   points. The four are the first support point of the policy path from series 9, so no
   new data requirement; they stand here because `anleihekurs` needs them over the whole
   game and a recourse to "the policy rate in round 1" would presuppose a state the
   state no longer has. Formation rule for `durchgriff` with `H` = exports plus imports
   of the sector in the start year (from BACI via the concordance in point 9) and
   `N` = its value added (from WDI):

   ```
   durchgriff = teile_gerundet(10.000 · H, H + N)
   ```

   The value range 0 … 10,000 thereby holds for all non-negative `H`, `N` by
   construction; a cap does not exist and must not exist, because it would only hide the
   error from finding 3. **The only undefined case is `H + N = 0`** — a sector without
   value added and without trade. The vintage build then sets `durchgriff = 0` (the
   sector price follows the country price completely, which for a sector without trade
   is the right statement) and **reports the case in the manifest as a finding**,
   because a territory with an empty sector raises a data question, not a computation
   question. It occurs in the check vintage for none of the five territories; the rule
   stands here so that the vintage build does not abort at a division whose cause it
   does not name.

   **And the vintage build checks a condition on the parameter set that `spiel.md`
   version 5 establishes and that hits exactly this window:** `anleihekurs(l)` has the
   denominator `leitzins[l] + aufschlag`, the policy rate therefore has the lower bound
   `1 − aufschlag`, and the historical policy path must keep to it. The vintage build
   computes

   ```
   aufschlag_min = 1 − min über alle l und t von leitzins_pfad[l][t]
   ```

   and rejects a parameter set with `aufschlag < aufschlag_min` as **inadmissible** for
   this vintage, instead of dividing by zero later. For 1997–2021 that is no theoretical
   bound: Germany follows the euro area exogenously from round 3, and the ECB first cut
   its deposit rate to −0.10 % on 2014-06-11 and by September 2019 to
   **−0.50 %** (`ecb.europa.eu/press/pr/date/2014/html/pr140605_3.en.html` and
   `ecb.europa.eu/stats/policy_and_exchange_rates/key_ecb_interest_rates/html/index.en.html`,
   retrieved 2026-09-01 by the game designer, adopted here). If the vintage draws the
   deposit rate, `aufschlag_min = 1 − (−50) = 51` basis points; if it draws the main
   refinancing rate, which stands at 0.00 % from 2016, `aufschlag_min = 1`. **Which
   series is embedded is decided by the vintage build; the bound it computes itself in
   both cases, instead of adopting a number.** The same lower bound holds in the
   `spielmodus` at the instrument itself (T51) — otherwise a lobby action that no
   vintage build ever gets to see would slip under it;
6. **derived key figures**: the mean absolute annual change per country as the swing
   width for the intra-year swing. Mean absolute deviation, not standard deviation —
   that would need a root and with it floating point (T4);
7. **normalisation**: the three sector shares per territory and year are normalised to
   10,000, because the WDI shares do not sum to 100 percent owing to taxes less
   subsidies on products. The normalisation — the procedure and the remainder cut off
   per territory and year — stands in the manifest, and the backtest compares normalised
   against normalised;
8. **breaks**: per series a field `exogen_ab` and a field `verkettet_ab`, both stored as
   a year and converted into a round per T40. For Germany the policy rate carries
   `exogen_ab = 1999`, in the check vintage thus **round 3**, and the exchange-rate
   series `verkettet_ab = 1999` with the irrevocable conversion rate;
9. **the concordance HS92 → model sector**, as a table in the manifest and not in code
   (finding 12). Per `spiel.md` it reads: chapters **01–24 → sector 1 agriculture**,
   **25–97 → sector 2 industry**. The same table produces `H` from point 5, the trade
   start matrix and the 40 target flows of the trade block — that is why its assignment
   error is without consequence for the backtest, and that is why it may exist only
   once. A second copy in code would be the opportunity to let them drift apart;
10. **the rest of world as a remainder**, formed explicitly in both quantities: its
    aggregates are the World Bank's world series minus the four countries; its trade
    rows are a country's total imports and exports in the sector minus the flows to the
    three others. **Per directed pair stands exactly one number** (BACI reports the
    export value; a separate import value would make the invariant "sum of all trade
    balances = 0" depend on data quality instead of on the construction).

Order of magnitude: 5 territories × 25 years × around 30 series × 8 bytes = 30 kB, trade
`40 × 25 × 8` = 8 kB. The shipped data part stays well under 100 kB per vintage and with
all vintages well under one megabyte.

**T45 — The vintage build counts off the addresses and aborts at a gap.** That is the
architectural answer to finding 2, and it is the only one that rules out its repetition.
Adding two table rows fixes the case; adding them and leaving open the spot at which
nobody notices an absence does not fix it.

The vintage build keeps, over **all 310 addresses from T15**, a provenance table with
exactly **five** admissible entries. Four stood in version 4; the fifth has come in with
this version, because the counting-off found two addresses whose value stands neither in
a series nor in a document but is computed by the vintage build itself.

| Entry | Meaning | Addresses | Example |
|---|---|---:|---|
| `Datenanker(nr)` | a series from the series list further down | 136 | `land.DE.sektor.2.wertschoepfung` → series 1 × 2 |
| `Entwurf` | the table *Every quantity without a data anchor* in `spiel.md` names a **numeric value** | 150 | `land.CN.aufsichtszaehler` → 0 |
| `Parameter(schluessel)` | `parameter.toml` per T27 | 11 | `fonds.kasse` → `startkapital` |
| `Manifest(feld)` | computed by the vintage build and reported in the manifest | 2 | `markt.wert` → start basket at start prices (T33) |
| `Vorgabe(T-Nummer)` | this document, exhaustively enumerated in **T46** | 11 | `restwelt.basiswechsel` → 0 (T8) |
| **Sum** | | **310** | |

**The precedence rule without which the sum does not come out.** The draft table in
`spiel.md` names for some rows not a numeric value but a **source of reference** — "from
`parameter.toml`" for approval, financial-market regulation, fund cash, investor stock
and parameter-set checksum, "from the vintage's manifest" for the vintage id. By the
wording of version 4 these addresses would carry two entries and abort the build. It
therefore holds: **the entry is the place that *determines* the value, not the one that
mentions it.** Where the draft table refers onward, the entry reads `Parameter(…)` resp.
`Manifest(…)`; `Entwurf` stays reserved for the rows that write down a number. A
reference is not a second entry.

**An address without an entry aborts the vintage build, an address with two entries
likewise.** The second case is the more important one: it is the place at which a
quantity would get two masters and the two values could drift apart — the same error
type that T39 has already closed for `landespreis`, T23 point 9 for the BACI concordance
and T47 for the fund's assets. It has occurred once in this version and is fixed: the 32
pressure and remaining-delay addresses that `spiel.md` version 4 took in and that T23
point 1 continued to carry.

**How the numbers of the third column came about, so that they can be recounted instead
of believed.** Per playable country 21 addresses carry a data anchor (9 sector
quantities without the price, 8 aggregate quantities without the exchange rate, the
exchange rate itself, 3 instrument levels), 20 the entry `Entwurf` (3 sector prices,
supervision counter, influence, 12 pressure, counter-pressure and remaining-delay
fields, 3 remaining durations), 2 a parameter key (approval, financial-market
regulation) and 1 a prescription (`basiswechsel`) — together the 44 from T15. For the
USA the exchange rate falls from anchor into prescription (numéraire), hence
`3 × 21 + 20 = 83` anchors. The rest of world carries 13 anchors, 3 `Entwurf` and 6
prescriptions. Plus 40 trade flows with an anchor.

```
Datenanker  83 + 13 + 40                                            = 136
Entwurf     4×20 + 3 + 2 + 12 + 1 + 6 + 24 + 20 + 2                 = 150
            (Länder, RW-Sektorpreise, Weltpreise, Nachahmer,
             markt.rendite, Fondsaggregate, Beteiligungen,
             Positionen, Runde und Mandatsstand)
Parameter   4×2 + Fondskasse + Anlegerbestand + Prüfsummenfeld      =  11
Manifest    markt.wert + Jahrgangskennung                           =   2
Vorgabe     T46                                                     =  11
                                                                      ---
                                                                      310
```

The complete table — 310 rows of address, provenance and start value — is written into
the manifest. With that, acceptance condition 2 of the work package is **answerable by
machine**, instead of laying four documents side by side: whoever wants to check it
reads one file that the vintage build could not even have written if a row were missing.

The price is 310 comparisons, once per data run and not per game. The obvious
alternative — start value zero where nothing stands — would have been the expensive one:
it would have turned finding 2 of the third check into a number nobody questions any
more, and into exactly the number that happens to be right there.

**T46 — The eleven addresses whose provenance is this document, exhaustively.** Version 4
introduced `Vorgabe(T-Nummer)` and described it with „derzeit allein T23 Punkt 1". That
was wrong, and the error only surfaced at the counting-off: after the intake of the 32
addresses into `spiel.md`, T23 point 1 has no address left at all — while eleven others
have never had an admissible entry, without anyone noticing. They stand here with start
value, reason and rule in the run:

| Address | Count | Start value | Reason and rule in the run |
|---|---:|---:|---|
| `gebiet.<G>.basiswechsel`, all five territories | 5 | 0 | Counter of the rebasings per **T8**. Before round 1 none has taken place; in the run only the rule from T8 raises it. No series can carry it, because it is a property of the model and not of the world |
| `land.US.wechselkurs` | 1 | 10,000 | The US dollar is the numéraire (**T5**). Series 10 carries three countries, the USA by definition not. The value is fixed over the whole game and is written each round with the cause `Vortrag` (T18) — the same construction as the permanently empty slot from T16 |
| `restwelt.leitzins`, `restwelt.staatsschuld`, `restwelt.haushaltssaldo` | 3 | 0 | The rest of world per `spiel.md` has no policy instruments, no government and no supervision counter; consequently it has no central bank and no budget either. These three addresses and the next one exist only because T15 gives the rest of world the same aggregate block as a country. **No model rule reads them**, all four are carried forward each round with the cause `Vortrag` so that the target mask from T38 comes out |
| `restwelt.wechselkurs` | 1 | 10,000 | Likewise unread, but with a different start value: the rest of world computes in the numéraire, and a rate of a currency aggregate against the dollar has no meaning. 10,000 instead of 0, so that an accidental use does not divide by zero but leaves the number unchanged |
| `restwelt.inflation` | 1 | 0 | Series 8 (consumer prices) carries four countries, the rest of world not. In the run the quantity is endogenous as everywhere — the annual rate of `restwelt.preisniveau`, which series 15 anchors. Only its start value has no source |

**The first row names five addresses and no notation.** `gebiet.<G>.` is the collective
notation from **T17b** and resolves here to `land.US.basiswechsel`,
`land.CN.basiswechsel`, `land.DE.basiswechsel`, `land.BR.basiswechsel` and
`restwelt.basiswechsel` — running numbers 44, 88, 132, 176 and 198 in
`daten/adressen.md`. That is no exception to T17 but its application: listing five rows
singly where they differ only in the territory bloats the table and says nothing any
more.

**Two conditions without which the four rest-of-world addresses would be a silent
assumption.** First: apart from the carry-forward itself, **no read access to them is
admissible**. The `Schreiber` carries them in a list `nur_vortrag`; a `lies_alt` or
`lies_neu` on them from a cause other than `Vortrag{adresse}` is a hard error, not a
report, and the break tester checks it along in checks 5 and 6. Otherwise a model rule
would grow on a number nobody has set. Second: should a rule later arise that needs one
of them, that is an ADR and not a line of code — then the address gets a data anchor or
a justified formation rule.

**Why T46 is needed at all and the addresses do not simply fall away.** Striking them
would be the cleaner architecture and is ruled out: `spiel.md` names **310** quantities
and refers here for the listing. 306 here and 310 there would be a contradiction in a
number, so exactly the case that acceptance condition 3 rules out — and I may not change
`spiel.md`. Four addresses that are never read cost 32 bytes and one test; a
contradiction between the two documents costs a run.

**T24 — Gaps are marked, not silently filled — and the check vintage tolerates none.**
Per series, country and year a flag `gefuellt`. The filling rule stands in the manifest
(carry-forward of the last known value, linear integer interpolation between support
points), and **filled years do not count in the error measure of the backtest** — they
are counted and reported.

Two thresholds:

- **Check vintage 1997–2021:** `spiel.md` demands each of the `L_R(S+5) − n` reported
  series — today **31**, of them `L_R(S+4) − n` = 27 target series since the cut of
  2026-09-03 — and each of the `(L_R+1)·L_R·(S−1)` trade flows, today **40**, over
  **25 support points without filling**, that is
  `gefuellt = 0`. The window and the 25 are the follow-up of the same cut and belong to
  `0064-technikmd-r-nachzug-ausserhalb-der-t-bloecke`, not here. A series that does not meet this is **not filled and not silently
  adopted** but reported as a finding to the game designer, together with the two ways
  out that are theirs: strike the series or shorten the window. Per T40 the second
  choice costs only a number in the manifest.
- **Play vintages:** a target series filled to more than one fifth counts as not
  reliable and is marked as such in the finding.

**The suspect case has become narrower, but not closed.** Version 2 named here the
Chinese and Brazilian policy-rate series of the nineties; `spiel.md` version 3 checked
the case against `FR.INR.LEND` (China 1995–2023 gapless, Brazil from 1997) and with that
holds an indication, not a proof. `FR.INR.LEND` is a different series from the IFS
policy rate, and `imf.org` rejects the retrieval with HTTP 403. The vintage build checks
it on the series that is actually embedded. **That is unchanged the most probable spot
at which the venture fails on data** — only it is now cheap, because it no longer forces
anyone to build a package twice.

**T25 — The boundary between exogenous and endogenous is the boundary of the oracle's
power of statement, and that is why it is drawn tight.**

| Quantity | in the game | Justification |
|---|---|---|
| Population, labour force | **exogenous**, path from data | demography per `spiel.md` is expressly not a game quantity |
| Rest-of-world demand level | **exogenous**, path from data | boundary condition of the model; the backtest consequently does not check the rest of world |
| `durchgriff` | **exogenous and constant**, constant of the vintage | so fixed by `spiel.md`, together with the simplification named there: China's growing trade openness the model maps via quantities, not via price transmission |
| Productivity | **endogenous**, only the start value from PWT | were it read from the data each year, GDP in the backtest would be a replay of the target series and the test would check itself |
| Prices, interest effect, trade, public finances, approval | **endogenous** | that is the machine that is to be checked |
| Policy instruments | endogenous in the `spielmodus`, set to the historical paths in the `weltlauf` | so `spiel.md` demands — with the consequence from T37 and the mask from T38 |

**T51 — Every policy instrument has a step width and a value range, both from
`parameter.toml`, and the value range holds in both modes.** `spiel.md` says "instruments
move by at most one step per round" and names no unit for the financial-market
regulation; since T5 class 10 there is one, and with that the sentence can be written
down:

| Instrument | Class | one step | Value range |
|---|---|---|---|
| Policy rate | 3 rates | `schrittweite[leitzins]` bp | `instrument_min[leitzins] … instrument_max[leitzins]`, and **`instrument_min[leitzins] ≥ 1 − aufschlag`** |
| Tariff level | 3 rates | `schrittweite[zoll]` bp | `0 … instrument_max[zoll]` |
| Budget balance | 3 rates | `schrittweite[haushalt]` bp | `instrument_min … instrument_max` |
| Financial-market regulation | 10 instrument tier | **1 tier** | `0 … regulierung_stufen` |

After every movement in step 3, `stand = min(max(stand ± schritt, min), max)` holds; the
capping carries the cause of the triggering pressure and not `Vortrag`, so that the
chain from T18 says *that* capping happened. **In the `weltlauf` the step width does not
hold** — the historical path is the truth there and may jump further within a year —,
**the value range does**: if the path leaves it, that is a finding of the vintage build
and no silent capping of a target quantity.

The row this hangs on is the second column of the policy rate. Without it a lobby action
can push the rate below `−aufschlag`, and `anleihekurs` divides by zero in the same
round or flips its sign. The vintage build checks the condition against the historical
path (T23 point 5), the instrument checks it against the player, and the invariant test
checks it against both (T30 check 2). Three checks for one bound is not too many: it is
the only place in the model at which a price becomes infinite.

**T26 — A locked or missing data anchor does not change the program, only the
manifest.** Three cases, all on the same pattern: the vintage carries a model construct,
the manifest says so, the finding repeats it.

| Case | Substitute | Consequence for the oracle |
|---|---|---|
| Aggregated tariff rate falls under the third-party exception (the gravest open question from `spiel.md`) | no tariff path; the `weltlauf` runs with a constant tariff | two instead of three anchored instruments |
| Sectoral employment (series 7) locked | split by value-added share | start value becomes a model construct, no target series affected |
| **A play vintage before 1995 needs a trade matrix, BACI begins 1995** | IMF DOTS aggregates per country pair, split by the WDI sector shares of the exporting country | the start matrix is a model construct; play vintages carry no trade block in the backtest anyway (`spiel.md`) |

The third case, after the shift to 1997, concerns not only the vintages before 1995 but
also 1995 and 1996: per `spiel.md` they are play but not check vintages and carry as US
start value the sector structure of 1997, marked as `gefuellt`. Licence and coverage
risk are thereby a property of the data layer, never one of the core.

### Die Reihenliste, die `spiel.md` vom Architekten verlangt

So that the data builder can check the field „Source" per series. Source per `daten.md`;
"Suspect" means the World Bank's third-party exception. The numbers 7, 8, 10 and 13 that
`spiel.md` names for checking are unchanged.

| Nr | Quantity | Dimension | Model unit | Source | Role | Suspect |
|---:|---|---|---|---|---|---|
| 1 | GDP, constant prices | 4 + RW | thousand USD | WDI / PWT | start + target (4, frei) | no |
| 2 | Value-added share per sector: `NV.AGR.TOTL.ZS`, `NV.IND.TOTL.ZS`, `NV.SRV.TOTL.ZS` | (4+RW) × 3 | ten-thousandths, normalised to 10,000 | WDI | start + target (12, frei, 8 independent) | no |
| 3 | Capital stock | 4 + RW | thousand USD | PWT | start | no |
| 4 | Productivity (TFP) | 4 + RW | index | PWT | start only (T25) | no |
| 5 | Population | 4 + RW | persons | WDI / PWT | exogenous path | no |
| 6 | Labour force | 4 + RW | persons | WDI / PWT | exogenous path | no |
| 7 | Employment per sector | (4+RW) × 3 | persons | WDI (ILO) | start | **yes** |
| 8 | Consumer prices | 4 | bp annual rate | WDI / IMF IFS | start + target (4, frei) | **yes** (IMF-based) |
| 9 | Policy rate | 4 | bp | IMF IFS | start + policy path + target (4, **gesetzt**) | no |
| 10 | Exchange rate against USD | 3 | index | IMF IFS / WDI | start + target (3, frei) | check |
| 11 | Government-debt ratio | 4 | bp | IMF WEO | start + target (4, **abgeleitet**) | no |
| 12 | Budget balance | 4 | bp | IMF WEO | start + policy path | no |
| 13 | Tariff level, aggregated | 4 | bp | WDI (from WITS) | start + policy path | **yes, decisive** |
| 14 | Bilateral flows per HS92, aggregated via the concordance from T23 point 9 | 5 × 4 × 2 | thousand USD | CEPII BACI | start + target block (frei) | no |
| 15 | Price level in country comparison | 4 + RW | index | PWT | start (numéraire) | no |
| 16 | `durchgriff` | 5 × 2 | ten-thousandths | BACI + WDI, derived per T23 point 5 | constant of the vintage | no |
| 17 | Sector prices | (4+RW) × 3 | index | **none** | endogenous, no target | — |
| 18 | Approval | 4 | ten-thousandths | **none** | from `parameter.toml` | — |
| 19 | Market-basket value and market return | 1 + 1 | thousand USD / bp | **none** | start value per T33, endogenous, no target | — |

`NV.IND.MANF.ZS` (manufacturing) is per `spiel.md` **not** used and is therefore not
listed here. The `L_R(S+5) − n` reported series are rows 1, 2, 8, 9, 10 and 11 — at
`L_R = 4`, `S = 3`, `n = 1` that is 4+12+4+4+3+4 = **31**. Row 9 (policy rate, class
`gesetzt`) has carried no target role since the cut of 2026-09-03, so `L_R(S+4) − n` =
**27** of them are target series; the whole table above counts in `L_R = 4` and moves with
the horizon in section 26, the wording of row 9 with `0068`. The
trade block from row 14 comes in as a block of its own. The four quantities without a
data anchor are rows 17, 18, 19 and the instrument financial-market regulation —
exactly the four that `spiel.md` enumerates under „Die Grenze des Orakels".

**And here stands the row whose absence made T46 necessary.** The column "Dimension" is
to be read as it stands: row 8 carries **4**, not 4 + RW; rows 9, 11 and 12 carry **4**,
row 10 carries **3**. From that it follows that eleven state addresses are covered by no
series — the US exchange rate (numéraire), five aggregate quantities of the rest of
world and the five rebasing counters. They stand in **T46**. Until version 4 that stood
nowhere, because nobody had laid the dimensions against T15; the check of round 4
declared condition 2 fulfilled and in doing so looked at the same gap as I did.

**T27 — The calibration file lies outside the code, and every key carries a scale
class.** All numeric values that `spiel.md` expressly leaves to calibration — the
mandate threshold (`schwelle_v` and `schwelle_e`), three supervision thresholds,
imitator speed, investor-withdrawal share, start capital, start approval, start level of
the financial-market regulation, `ausstiegsabschlag` and `zwangsabschlag` (T47), delays,
elasticities — stand in `parameter.toml`.

**Eleven keys get a unit in this version or are new**, because T49 and T50 could not
place them otherwise. A parameter key without a class is the same error as an address
without a class:

| Key | Class (T5) | Meaning | from where |
|---|---|---|---|
| `stufenweite` | 4 shares | share of the market per position step, **not a money amount** | `spiel.md` version 5 |
| `stufen_max` | 11 counters | magnitude bound on the step count per slot | T16 |
| `ausstiegsabschlag`, `zwangsabschlag` | 4 shares | discounts on the stake value | T47 |
| `aufschlag` | 3 rates | spread policy rate ↔ bond yield, `≥ aufschlag_min` (T23 point 5) | **new**, `spiel.md` version 5 |
| `lobbykosten` | 1 fund money | US cents per lobby point, `≥ 1` | T50 |
| `beteiligungsrabatt` | 4 shares | price discount on the lobby point with a stake, `1 … 10.000` | **new**, T50 |
| `gegenlobby_satz` | 9 lobby pressure | lobby points per 10.000 thousand USD damage | **new**, T50 |
| `druck_max` | 9 lobby pressure | upper bound for pressure and counter-pressure per instrument | **new**, T5 class 9 |
| `regulierung_stufen` | 10 instrument tier | number of tiers of the financial-market regulation | **new**, T5 class 10 |
| `schrittweite[i]`, `instrument_min[i]`, `instrument_max[i]` | as the instrument | movement per round and value range | **new**, T51 |

`leitzins_start[l]` stands **not** here but in the vintage (T23 point 5): it is not a
calibration quantity but a measurement. The number of addresses with provenance
`Parameter(schluessel)` stays at eleven (T45) — new keys are not new addresses.

All values are read as decimal strings into scaled integers (T4) and filled into a
structure with named fields, never via a loop over keys (T9). **That structure is
`kern::werte::Konstanten`, and since `0208` it is an argument of `schritt`** — this is
the one route by which a key of this file reaches a rule of the round. Which keys stand
in it and which instead determine a start address at vintage build, and how the count-off
catches a key that does neither or both, stands in **T10b**. The checksum of the
parameter set stands in the state and in every save; it is formed over the values of the
carrier, not over the text of the file (T10b). With that, calibrating is a data
change that needs no compiling — exactly the construction that `spiel.md` has evidenced
on Democracy 4, and the precondition for an agent searching a thousand parameter sets
overnight (section 10).

## 8. Markträumung und die beiden Renditen

**T28 — Fixed iteration count instead of convergence cutoff.** The world price per
tradable sector is found by **exactly 40 bisection steps** over a fixed price interval,
not until a bound is met. A cutoff by accuracy makes the runtime depend on the state and
the number of steps a silent part of the result; a fixed count makes both measurable and
bounded. 40 bisections over an interval of six orders of magnitude resolve to below one
ten-thousandth — more resolution than the price scale from T5 can represent at all.

Within each bisection step come, in this order, the tariff wedge per territory on the
world price and from it the effective sector price as a blend

```
preis = teile_gerundet(weltpreis_mit_zoll · durchgriff
                       + landespreis · (10.000 − durchgriff),  10.000)
```

with `landespreis = lies_alt(gebiet.<G>.sektor.<s>.preis)` per T39, prefix per T17b, in
round 1 therefore the start value 10,000. Supply and demand are formed on this price.

**With that the admissibility of the bisection is proven instead of asserted** — and that
is the resolution of finding 6, not merely its answer. Both weights are non-negative
(`durchgriff` lies per T23 point 5 in 0 … 10,000), `landespreis` stands fixed while the
bisection runs, and `preis` is therefore monotonically increasing in the world price. The
excess function inherits this monotonicity, no fixed-point problem arises, and one pass
suffices. The reviewer's second reading — `landespreis` as the clearing domestic price of
the same round — would have destroyed exactly that; with T39 it is not merely rejected
but no longer expressible.

Services have no trade line, no world price and `durchgriff = 0`; their sector price is
the pure carry-forward of the previous round's price through the domestic clearing.

**T29 — Integer powers and roots via Newton on `i128`.** Where the production function
needs an exponent like 1/3, `wurzel(x, n)` with a fixed step count is used; exponents are
restricted to fractions of small integers. No series expansion, no logarithm, no table
interpolation.

**T33 — Market return and fund return are computed over a frozen quantity basket.**
`spiel.md` has decided the interpretation: value-weighted return of all tradable baskets
at model market values, weighted by the market and **not** by the fund's holdings. The
rule, in step 6 of the round and only in `spielmodus`:

1. The **market basket** comprises the 12 country×sector baskets and the 4 government
   bonds, each at model market values. Currencies carry no market capitalisation and do
   not enter; their effect sits in the conversion of the other baskets into the numéraire.
   **Since `spiel.md` version 5, quantity and price are named**, and with that the basket
   is a calculation instead of a paraphrase — the quantities are capital stock and
   government debt, the prices sector price, bond price and exchange rate (T48):

   ```
   marktkorb(m, k) = Σ über die 12 Land×Sektor  wert_(m,k)(kapitalstock[l][s], sektorpreis[l][s], l)
                   + Σ über die  4 Anleihen     wert_(m,k)(schuld(l),          anleihekurs(l),    l)
   ```

   `m` and `k` say from which round the quantity and from which the price is read; both
   sums run over the index order from T9. The value stands on the **macroeconomic** scale
   (T5 class 2) and crosses no scale boundary.
2. `markt.wert` carries the value of this basket at the end of the previous round. **In
   round 1 it is the start value from the vintage** — the value of the start basket at
   start prices, computed by the vintage build as `marktkorb(start, start)` and reported
   in the manifest. With that the second half of finding 2 of the second review is
   closed, independent of the mode.
3. Value the **quantity basket of the previous round** at this round's prices:
   `W_neu = marktkorb(alt, neu)`, that is, quantities via `lies_alt` and prices via
   `lies_neu` (T39). `markt.rendite = teile_gerundet((W_neu − markt.wert) · 10.000, markt.wert)`
   in basis points.
4. Only afterwards is `markt.wert = marktkorb(neu, neu)` set.

Quantity growth thus produces no spurious return. **`markt.wert` is never zero** — it is
a sum of positive quantities times positive prices, and both value ranges are checked by
the invariant test (T30 check 2). With that the division in point 3 never sees a zero
denominator without a special case standing anywhere; that is the same construction as
step (c) before (d) further down.

**The fund return arises in the same order, and the order is the rule:** (a) value the
positions, (a') value the stakes, (b) form the fund assets, (c) if they are **zero or
below**, `spiel.md` way of dying 1 takes hold in the same round and the game ends without
return formation, (d) only otherwise is the return formed: change of the fund assets
against the previous round, **adjusted for investor inflows and outflows of this round**
— otherwise fresh investor money would count as performance and the investor withdrawal
from counterforce 3 would reinforce itself. The excess return is the difference of the
two quantities in basis points and stands in the state for three rounds.

Step (c) before (d) is no fine point: it is the reason why `teile_gerundet` in this model
never sees a zero denominator without a special case being checked anywhere.

**T47 — The fund assets are exactly one function, and every valuation in it crosses the
scale boundary exactly once, at the outermost call.** `spiel.md` version 5 forms
`korbwert` and `positionswert`, which version 4 had only used (finding 1 of round 6), and
decides on which side of the boundary `korbwert` stands (finding 2). Here stands where
the computing is done.

**The market values, all on the macroeconomic scale** (T5 class 2); `wert` is the one
valuation formula from which all three slot kinds arise:

```
wert(menge, kurs, g) = mal_geteilt(menge, kurs, wechselkurs[g])

korbwert(l, s)   = wert(kapitalstock[l][s], sektorpreis[l][s], l)
anleihewert(l)   = wert(schuld(l),          anleihekurs(l),    l)
waehrungswert(l) = wert(handelsvolumen(l),  10.000,            l)

markt(p)         = korbwert | anleihewert | waehrungswert, je nach Steckplatzart
stufenwert(p)    = mal_geteilt(markt(p), stufenweite, 10.000)
```

**The two fund values, in US cents** (T5 class 1) — and exactly here lies the boundary:

```
positionswert(p)       = 0                                        falls stufen(p) = 0
                       = tsd_in_cent(stufen(p) · stufenwert(p))   sonst

beteiligung_wert(l, s) = tsd_in_cent(
                           mal_geteilt(mal_geteilt(korbwert(l, s), anteil[l][s], 10.000),
                                       10.000 − ausstiegsabschlag, 10.000))

fondsvermoegen(z) = kasse
                  + Σ über die 20 Steckplätze  positionswert(p)
                  + Σ über die 12 Land×Sektor  beteiligung_wert(l, s)
                  − hebelstand
```

Both sums run over the index order from T9, never over a set. `korbwert(l, s)` is the
same value that the market basket from point 1 of this section also uses — **one
valuation, not two**, otherwise market return and fund assets could price the same basket
differently.

**That is the resolution of finding 2, and it stands at the root and not in a
parenthesis.** The version-5 formula consisted of two `mal_geteilt` with unitless shares,
hence was scale-preserving: what went in in thousand USD came out in thousand USD and was
booked as US cents — factor 100,000, the cash falls by a hundred thousand times what the
stake assets rise, way of dying 1 in the same round, class 2 of Maß 2 hopeless by
construction. `tsd_in_cent` around the outermost call closes that.

**Of the two paths the reviewer left open, the other one is ruled out, and the reasoning
is not mine.** To carry `korbwert` in cents right away would mean carrying the same
basket on two scales, for T33 values the same twelve baskets macroeconomically — two
valuations for one basket, hence exactly what the paragraph above rules out. `spiel.md`
version 5 decides that under *Where the scale boundary lies* and assigns to me only
**which function** does it. It is `tsd_in_cent` from T50, and in this document it has
exactly the two call sites that stand above.

**The order of the roundings is binding, because it changes the result.**
`stufen(p) · stufenwert(p)` and `mal_geteilt(markt(p), stufen(p) · stufenweite, 10.000)`
differ by up to `|stufen(p)|` units. Binding is the first form, because `spiel.md` writes
it that way; the second would be more accurate and invalidates every regression corpus
that arose with the first. Whoever wants it needs an ADR, not a better reason.

**Two value-range bounds belong with this, otherwise the formula is only right in fair
weather.** First, `wert` divides by `wechselkurs[g]`: a zero denominator is per T6 an
abort, a **negative** denominator would be worse — it would flip the sign of every
valuation without anything aborting. `wechselkurs[g] ≥ 1` is therefore an invariant (T30
check 2), not an expectation. Second, `tsd_in_cent` is the only place where an `i64` can
overflow: `x · 100.000` leaves the range from `|x| > 9,2 · 10^13` thousand USD on. The
largest value that can arrive there is bounded by the whole market basket; with a world
capital stock on the order of `4 · 10^11` thousand USD — roughly three to four times a
world gross domestic product of around `10^11` thousand USD, as an order of magnitude and
not as a measurement — a good two orders of magnitude lie in between. The vintage build
checks `marktkorb(start, start) < 9,2 · 10^13`, the invariant test checks `markt.wert`
each round against the same bound. With that the overflow is not merely improbable but
ruled out and checked.

**What bounds the share scale from below, and why that is a condition on the
self-player.** `stufenweite` is integer and at least 1; one step therefore costs at least
one ten-thousandth of the basket it hangs on. The sixteen market values of a vintage lie
far apart — the capital stock of services in the USA against Brazil's agriculture — and
**the same** `stufenweite` value holds for all of them. The vintage build therefore
reports the smallest and the largest of the sixteen start market values in the manifest.
That is the number the self-player needs before it searches for `startkapital` and
`stufenweite`: a step on the largest basket must be affordable (otherwise class 1 never
wins), and reachable step counts must reach the supervision thresholds (otherwise no
counterforce takes hold and Maß 3 falls to zero) — the two conditions `spiel.md` sets up
under *Offene Entwurfsfragen*, here furnished with the number they are read off from.

Four properties that bind this version, all from `spiel.md`:

1. **`ausstiegsabschlag` is a key from `parameter.toml`** (T27), not a literal, and lies
   in ten-thousandths. The discount thus sits in the valuation and is paid at
   **build-up**: on entry the cash gives up the full basket share, the fund assets fall
   in the same round by the discount. On an ordinary exit it is **not deducted a second
   time**; the stake stays illiquid over the two rounds that `restdauer[l][s]` counts.
2. **The forced sale from counterforce 1 deducts `zwangsabschlag` in addition** — a
   second parameter key, an additional penalty, not a replacement of the first.
3. **`fondsvermoegen` has exactly one call site per purpose and no second computation
   path.** It is read by the settlement (step 6), the mandate check, way of dying 1, the
   invariant test from T30 check 2 and by `v(z)` in T44. That all five see the same
   number is the reason why "fund assets" means the same thing throughout — *what the
   fund is worth if it stops here*.
4. **It is not a state address.** The state holds cash, slots, shares and leverage; the
   assets are their function. A field for it would be a second copy of the same number —
   the same error type that T39 has already closed for `landespreis` and T23 point 9 for
   the BACI concordance. The 310 from T15 therefore do not change.

**What a call costs, this time counted out instead of estimated.** Version 5 spoke of
„wenigen Dutzend Operationen"; the reviewer of round 6 called that too small under
*geprüft und nicht gezählt* and was right. In the worst case — all twenty slots occupied,
all twelve stakes non-zero:

| Part | Calls | Operations |
|---|---:|---:|
| `bip(l)` | 4 | 8 additions |
| `schuld(l)` | 4 | 4 `mal_geteilt` |
| `anleihekurs(l)` | 4 | 4 additions, 4 `teile_gerundet` |
| `anleihewert(l)` | 4 | 4 `mal_geteilt` |
| `handelsvolumen(l)` | 4 | 64 additions |
| `waehrungswert(l)` | 3 | 3 `mal_geteilt` |
| `korbwert(l, s)` | 12 | 12 `mal_geteilt` |
| `stufenwert(p)` | 20 | 20 `mal_geteilt` |
| `positionswert(p)` | 20 | 40 multiplications |
| `beteiligung_wert(l, s)` | 12 | 24 `mal_geteilt`, 12 multiplications |
| two sums | 1 | 32 additions |
| **Total** | | **around 230, of which 71 `i128` divisions** |

Against 7,500 operations per world step that is **a good three percent**, not three per
mille. The plan value of 10 µs has bandwidth up to 30 and the reserve reckons with 50; no
line of section 10 moves. Two prescriptions push the actual price far below that:
`positionswert` breaks off at `stufen(p) = 0` before `markt(p)` is computed at all (most
slots are empty most of the time), and **`korbwert(l, s)` is computed once per call of
`fondsvermoegen` into a field of twelve and read from there by slot and stake** — not to
save time, but because "one valuation, not two" would otherwise be only a sentence and
not a property of the code.

**T48 — The derived quantities are functions of the state, not addresses, and they are
exhaustively enumerated.** That is the architectural answer to finding 1 of round 6, and
it is the only one that rules out its repetition. Adding two formulas fixes the case; to
fix it and leave open the set in which nobody notices an absence does not fix it. T45
enumerates **addresses** and therefore could not find the gap — `korbwert` was never one
of the 310. This table is the set in which it lay.

| # | Name | Class (T5) | Definition | stands in |
|---:|---|---:|---|---|
| 1 | `wert(menge, kurs, g)` | 2 | `mal_geteilt(menge, kurs, wechselkurs[g])` | T47 |
| 2 | `korbwert(l, s)` | 2 | `wert(kapitalstock[l][s], sektorpreis[l][s], l)` | T47 |
| 3 | `anleihewert(l)` | 2 | `wert(schuld(l), anleihekurs(l), l)` | T47 |
| 4 | `waehrungswert(l)` | 2 | `wert(handelsvolumen(l), 10.000, l)` | T47 |
| 5 | `markt(p)` | 2 | case distinction over the three slot kinds from T16 | T47 |
| 6 | `stufenwert(p)` | 2 | `mal_geteilt(markt(p), stufenweite, 10.000)` | T47 |
| 7 | `marktkorb(m, k)` | 2 | Σ 12 `korbwert` + Σ 4 `anleihewert`, quantities from `m`, prices from `k` | T33 |
| 8 | `korbbestand(z)` | 2 | see below | T47 |
| 9 | `bip(l)` | 2 | `Σ über die 3 Sektoren wertschoepfung[l][s]`; **two read forms**, see no. 22 | here |
| 10 | `schuld(l)` | 2 | `mal_geteilt(bip(l), staatsschuld[l], 10.000)`; **two read forms**, see no. 22 | here |
| 11 | `handelsvolumen(l, s)` | 2 | see below; the one-argument form `handelsvolumen(l)` is its sum over s ∈ {1, 2}; **two read forms**, see no. 22 | here |
| 12 | `anleihekurs(l)` | 5 | see below | here |
| 13 | `landespreis(g, s)` | 5 | `lies_alt(gebiet.<g>.sektor.<s>.preis)` | T39 |
| 14 | `fondsanteil(l, s)` | 4 | `\|stufen(l, s)\| · stufenweite + anteil[l][s]` | here |
| 15 | `positionswert(p)` | 1 | `tsd_in_cent(stufen(p) · stufenwert(p))`, 0 at `stufen = 0` | T47 |
| 16 | `beteiligung_wert(l, s)` | 1 | basket share minus `ausstiegsabschlag`, then `tsd_in_cent` | T47 |
| 17 | `fondsvermoegen(z)` | 1 | cash + positions + stakes − leverage | T47 |
| 18 | `hub(l, i)` | **that of the instrument**: 3 for tariff, policy rate and budget, 10 for the regulation | `\|lies_neu(land.<l>.instrument.<i>.stand) − lies_alt(dieselbe Adresse)\|` | here |
| 19 | `keilhub(l, s)` | 5 | `mal_geteilt(welt.preis.<s>, hub(l, zoll), 10.000)` | here |
| 20 | `preishub_zoll(l, s)` | 5 | `mal_geteilt(keilhub(l, s), durchgriff(l, s), 10.000)` | here |
| 21 | `weltpreis_mit_zoll(g, s)` | 5 | `mal_geteilt(welt.preis.<s>, 10.000 + zollstand(g), 10.000)` | T28 |
| 22 | `schaden(l, i)` | 2 | `mal_geteilt(menge, verschiebung, 10.000)`, four lines, see below | here |

**Numbers 18 to 22 were added on 2026-09-04 with package `0043-t48-groessen-gegenkraft-5`**,
from packages 0021 (the damage prescription) and 0039 (the tariff line now measures only
the wedge). They are the case T48 was built for, a second time: the design introduced
five names in formulas, and its own catch-up table reported none of them. Number 21 is
the older case — T28 **names** the tariff wedge ("the tariff wedge per territory on the
world price") and computes with `weltpreis_mit_zoll` in its price formula without ever
forming it; that was without consequence as long as no second place needed it, and since
number 19 it no longer is.

**Number 18 is the only quantity of the table without a single class, and that is no
oversight.** `hub` is scale-*preserving*: it forms the absolute value of a difference of
two levels of **the same** address, and the class of the result is that of the address.
T49 does not give the four instrument levels of a country the same class — tariff, policy
rate and budget stand in basis points (3), the financial-market regulation in steps (10).
An invented common class would be, here, the error kind T5 is built against; the correct
statement is the one about the mapping, not the one about the value.

**Number 21 holds for all five territories, and for the rest of world `zollstand` is
zero.** The reason stands in the data and is not a choice: T23 point 5 carries
`durchgriff` with **5 × 2 = 10** values (series list no. 16), so the rest of world takes
part in the price transmission and needs a tariff-laden world price; instruments it has
none per T15, so a `zollstand(RW)` is not an address but the zero. I decide that here
instead of handing it back, for the same reason as the eleven start values in T46: it is
not a choice between two sensible numbers but the only assignment with which the formula
is total at all over its written domain ("per territory"). If the game designer considers
it wrong, it is one line.

**Number 21 does not check its factor, and that is decided rather than omitted — package
`0172`, 2026-09-08.** `10.000 + zollstand(g)` is non-negative because `zollstand` is
bounded at the instrument: T51 gives the tariff the range `0 … instrument_max[zoll]`, and
since this package that bound is **bound 8 of T30 check 2**. With `welt.preis.<s> > 0`
from bound 2 it follows that `weltpreis_mit_zoll(g, s) ≥ welt.preis.<s> > 0`, without a
line in this function. The reasoning, the measured counter-case and the third premise of
T28 that hangs on it stand in section 23.

The four that until now stood nowhere:

```
bip(l)               = Σ über die 3 Sektoren  wertschoepfung[l][s]

handelsvolumen(l, s) = Σ über die 4 Gegenüber g   handel[l][g][s] + handel[g][l][s]
handelsvolumen(l)    = Σ über die 2 handelbaren Sektoren s   handelsvolumen(l, s)

anleihekurs(l)       = teile_gerundet(10.000 · (leitzins_start[l] + aufschlag),
                                      leitzins[l] + aufschlag)

korbbestand(z)       = Σ über die 12 Körbe     mal_geteilt(korbwert(l, s),  fondsanteil(l, s), 10.000)
                     + Σ über die  4 Anleihen  mal_geteilt(anleihewert(l),  |stufen(p)| · stufenweite, 10.000)
```

**`handelsvolumen` has had two forms since 2026-09-03, and they are one quantity.** The
per-sector one is the defined one, the one-argument one its sum over the two tradable
sectors — not two definitions of the same name, but one definition and its aggregation.
That is the condition under which the tariff line of counterforce 5 can compute per
sector without number 4 (`waehrungswert(l) = wert(handelsvolumen(l), 10.000, l)`)
changing: there the one-argument form still stands, and it still means the same. The
third sector appears in neither of the two — it has no trade line.

`handelsvolumen` reads **both directions** per pair; the assignment of the dense
counterpart index to the territory index is the fixed mapping from T9 and stands in the
code as a named table, not as arithmetic on indices.

The five from counterforce 5 and the tariff wedge, in computation order:

```
hub(l, i)            = | lies_neu(land.<l>.instrument.<i>.stand)
                       − lies_alt(land.<l>.instrument.<i>.stand) |

keilhub(l, s)        = mal_geteilt(welt.preis.<s>, hub(l, zoll), 10.000)
preishub_zoll(l, s)  = mal_geteilt(keilhub(l, s), durchgriff(l, s), 10.000)

weltpreis_mit_zoll(g, s) = mal_geteilt(welt.preis.<s>, 10.000 + zollstand(g), 10.000)

schaden(l, zoll)        = Σ über s ∈ {1, 2}  mal_geteilt(handelsvolumen(l, s), preishub_zoll(l, s), 10.000)
schaden(l, leitzins)    = mal_geteilt(schuld(l), hub(l, leitzins),  10.000)
schaden(l, haushalt)    = mal_geteilt(bip(l),    hub(l, haushalt),  10.000)
schaden(l, regulierung) = mal_geteilt(bip(l),    hub(l, regulierung) · regulierung_last, 10.000)
```

**`schaden` is one function with four lines and not four functions**, because its result
in all four cases is class 2 and its arity the same. The sum over the sectors stands
**inside** the tariff line; outwardly it too yields one number per country and
instrument, and that is the number the third scale transition from T50 accepts.
`regulierung_last` is the parameter key from T27 (class 3, basis points of GDP per
regulation step); the product `hub(l, regulierung) · regulierung_last` is steps times
basis points per step, hence class 3 — the same class as the shift of the two middle
lines, and therefore all four compute over the same denominator 10.000. The denominator
of `anleihekurs` is per T51 never zero and never negative. **`fonds.marktanteil` is not a
derived quantity but an address**, written in step 6 as
`mal_geteilt(korbbestand(z), 10.000, markt.wert)` — `spiel.md` writes there
`teile_gerundet(korbbestand · 10.000, markt.wert)`; that is the same number, but the
naive form overflows per T6, and therefore the `i128` form is binding.

**Number 22 takes exactly one state input, and it is the `Schreiber` — decided
2026-09-08, package `0165`.** `spiel.md` writes the three quantities of the damage rows
with `lies_neu` (section *Die eine Regel*: `bip`, `schuld`, `handelsvolumen`) and books
the addresses they read as written in **step 4**, while the damage itself runs in step 5.
Numbers 9, 10 and 11 therefore read **the state emerging in this round**, and that state
exists nowhere as a `Zustand`: the writer releases one only through `rundenende()`, after
the target-mask check, and in step 5 the round is not over. A second `Zustand` argument
beside the writer can therefore only ever be the **previous** round's — it reads
`lies_alt` on 56 addresses where `spiel.md` prescribes `lies_neu`. Therefore:

**Numbers 9, 10 and 11 each get a second read form that takes a
`const schreiber::Schreiber&` and reads every address of its formula through
`lies_neu`.** The `Zustand` forms stay unchanged and keep every reader they have. Number
22 takes the writer, the carrier of T10b and the two indices, and nothing else:

```
schaden(rundenschreiber, konstanten, l, i)
```

**Two read forms are not two quantities**, the same construction as the two arities of
number 11: one definition, two routes to its addresses. The table therefore still counts
**twenty-two** quantities; the declarations in `werte.hpp` outside `intern` rise from
**twenty-three to twenty-six**, and whoever lays header against table counts a name once
and its forms beside it. Why not a read access on the writer's state, which readers the
`Zustand` forms have, and what it costs: section 22.

**Three quantities lie outside the core** and therefore do not stand in the table:
`B(z)`, `v(z)` and `e(z)` from T44. They are test-bench quantities, belong to the
component `pruefstand` and never leave the game.

**The rule that follows from this, and the mechanical proof for it.** A name in a formula
of this document or in `spiel.md` that is neither a state address from T15 nor a
parameter key from T27 nor a vintage constant from T23 nor one of the **twenty-two**
quantities above **is a finding and not a build decision** — that is the case finding 1
describes, and the reason it was expensive: if the build agent chooses, Maß 2 measures
its choice. **Two of the four kinds reach a step body only through the carrier of T10b**,
and until `0208` through nothing at all: a name from T27 or T23 was legitimate here while
being unreachable there. Whoever finds one in a formula reads T10b before writing the
rule. It is proven like the floating-point renunciation from T4: the twenty-two
names are the public interface of the module `kern::werte` (T13), and laying the
declarations in `kern/include/kern/werte.hpp` outside `namespace intern` against this
table is a check of two minutes. **I have run it once by hand in this run**, in the only
form possible before the build: every formula from `spiel.md` and from this document laid
name by name against the four sets.

**And this time the list that was checked against is printed with it** — that is the
condition under which the check yields the same result a second time. Collected with
`rg -o '\b[a-z][a-z0-9_]{2,}\('` over `spiel.md`, then every hit assigned individually.
What remained were the five above; the **twenty-two names in the ten lines below** are
**not** derived quantities, and why they are not stands next to them. Whoever repeats the
collection may keep exactly these remainders and no further one:

| Name in `spiel.md` | not a derived quantity, but |
|---|---|
| `menge(l, i)`, `verschiebung(l, i)` | **column headings of the damage table**, see the paragraph below |
| `zollstand(g)` | `land.<g>.instrument.zoll.stand` in function notation; zero for the rest of world (no. 21) |
| `stufen(p)`, `stufen(l, s)` | the position step of the slot, `fonds.position.<l>.<s>` — an address from T15, T5 class 11, likewise in function notation. It already stood unregistered in the formulas of numbers 14 and 15 before this package; the collection found it as well |
| `durchgriff(l, s)` | vintage constant, T23 point 5, ten values |
| `welt.preis_start(s)` | start value of the vintage, T23; stands only in one calibration condition |
| `regulierung_last`, `druck_max`, `stufenweite`, `aufschlag` | parameter keys, T27 |
| `lobbypunkte_aus_schaden(tsd)` | third scale transition, T50; **private** in `kern::werte` and therefore not in this table |
| `gegendruck_neu(l, i)` | the value of `land.<l>.instrument.<i>.gegendruck` written in step 5, hence an address |
| `wmz(l, s)`, `preishub(l, s)` | names of the **discarded** former version of the tariff line. They stand only in the counterexample with which `spiel.md` demonstrates what the decision of 2026-09-03 removed (8.472.000 instead of zero without any action) — evidence, not a prescription |
| `mal_geteilt`, `teile_gerundet`, `lies_neu`, `lies_alt`, `min`, `max`, `sgn`, `wurzel` | arithmetic machinery and access form, T6, T29, T39 |

**`menge` and `verschiebung` explicitly get no function, and the reason is T5 itself.**
Both are, in `spiel.md`, the column headings of a table with four rows, not two
quantities: `verschiebung` stands for the tariff line in class 5 and for the three others
in class 3, hence has no uniform result one could declare — exactly the property T5
demands of a quantity. `menge` is always class 2 but fails on **arity**: in the tariff
line it is `handelsvolumen(l, s)` and thus one number per sector, in the three others
`schuld(l)` or `bip(l)` and thus one per country. A common function would have to invent
either a class or an argument. **Therefore `schaden(l, i)` is formed**, and the case
distinction lies inside it — the same construction as `markt(p)` (no. 5), which likewise
distinguishes the three slot kinds from T16 on the inside instead of giving three names
outward.

## 9. Test- und Prüfstandsaufbau

**T30 — Eight checks, one call.** `nacht` runs them in order and aborts with a non-zero
return value as soon as a threshold from `spiel.md` is breached. What does not run in one
call does not run at night.

| # | Check | Subject | Responsible |
|---:|---|---|---|
| 1 | unit tests per effect chain | every arrow from `spiel.md` singly, on a minimal state: tariff up → imports down → price up → real income down → approval down. Plus the stock invariant from T43, checked for `k = 1` (five rounds) **and** `k = 3` (fifteen), so that the mix-up from finding 3 shows in the code too | test developer |
| 2 | invariant test | sum of all trade balances including rest of world = 0; government debt(t) = government debt(t−1) − balance; **fund assets = cash + valued positions + valued stakes − leverage** (T47, against `fondsvermoegen()` and against a sum written out separately in the test, so that the test does not repeat the function under test); the three sector shares per territory sum to 10,000; no share outside 0…10,000; **the eight value-range bounds from T5, T49 and T51** (see below); every game result in one of the three bands from T34 | test developer |
| 3 | determinism test | the same seed, mode and the same action sequence yield the same checksum — twice within the run, across save and load, and compared on every target platform | test developer |
| 4 | regression corpus | stored games per T22 recompute bit-identically; in addition a checksum over the chain, so that a changed *justification* shows too; at least one game on a 1980 vintage with a base change (T8) | test developer |
| 5 | break run | 10,000 games with the random bot: no crash, no overflow, no invariant violation, no chain overflow, no double write access and no mask violation (T18, T38, T39) | break tester |
| 6 | **boundedness** | **200 rounds in mode `weltlauf`** (T38) — that is what „ohne Spieler" means, decided in section 28; if a quantity leaves its value range, there is a **ninth** feedback channel, and that is a finding. The channel table in `spiel.md` has counted **eight** since version 5. **Bounds 5, 6 and 7 measure only the start assignment in this check**, see below | break tester |
| 7 | the three measures | decision density, strategy diversity, optimum shift per the calculation rules in `spiel.md`, against the thresholds there: **0.4 per game third**; **three classes with one winner each at most 25 % apart**; **shift ≥ 0.4** | self-player |
| 8 | backtest | in mode `weltlauf` (T38), `L_R(S+5) − n` reported series (today 31, of them `L_R(S+4) − n` = 27 target series) plus the trade block, error measures per T42, acceptance via **`3·L_R + (L_R − n) + 1` check subjects with tolerance `⌊L_R/2⌋`**, today **16 and 2**, per T37 | backtester |

**The eight value-range bounds that check 2 checks every round.** They follow from T5, T49
and T51 and stand here together so that the test developer does not have to gather them
from twelve table rows. Each is a **hard error**, not a report:

| # | Bound | Addresses | why it is not mere cosmetics |
|---:|---|---:|---|
| 1 | `wechselkurs[g] ≥ 1` | 5 | denominator of every valuation (T47); zero aborts, negative silently flips every sign |
| 2 | nominal indices `> 0` | 22 | denominator of the rate formation in T42 and factor of every valuation |
| 3 | `produktivitaet[g] > 0` | 5 | factor of the production function |
| 4 | `leitzins[l] + aufschlag ≥ 1` | 4 | denominator of `anleihekurs`; the bound sits at the instrument (T51) |
| 5 | `0 < markt.wert < 9,2 · 10^13` | 1 | denominator of `markt.rendite` and `marktanteil`, overflow bound of `tsd_in_cent` (T47) |
| 6 | `0 ≤ druck, gegendruck ≤ druck_max` | 32 | class 9; without an upper bound, channel 8 is unbounded |
| 7 | `0 ≤ fondsanteil(l, s) ≤ 10.000`, `\|stufen(p)\| ≤ stufen_max` | 12 + 20 | a share above 100 % is not a share; the admissibility check from T32 keeps it in bounds, the test checks that it does |
| 8 | `instrument_min[i] ≤ land.<l>.instrument.<i>.stand ≤ instrument_max[i]` | 16 | T51 gives all four instruments a value range and step 3 caps against it — nothing checked the result. For the tariff `instrument_min[zoll]` is fixed at 0, and that is the premise T28's bisection uses without naming it (section 23) |

Plus the **two equalities** from T49: `land.<L>.leitzins = land.<L>.instrument.leitzins.stand`
and `land.<L>.haushaltssaldo = land.<L>.instrument.haushalt.stand`, per round and per country.

Bounds 1, 5 and 8 are the three that without a test would go wrong silently instead of
loudly: a negative exchange rate turns every profit into a loss; a market basket beyond
the overflow bound does crash per T7, but only in `tsd_in_cent` and thus at a place where
nobody looks for the cause; and a tariff level below −10,000 basis points turns the wedge
factor of number 21 negative, which no reader of it notices — measured, section 23.

**Check 6 runs in mode `weltlauf`, and that decides three of its eight bounds away.**
„200 Runden ohne Spieler" named no mode until now, and the two readings differ measurably
(`befunde/beschraenktheit/bruch-2026-09-06.md`, findings 2 and 3). It is the `weltlauf`:
that is the mode without a player (T38); it is the only one that runs today —
`kern::schritt::schritt` aborts on `Modus::Spielmodus` because steps 2 and 6 have no
package (`kern/src/schritt.cpp`, the `switch` over the mode); and a boundedness check
whose inputs are constant after the window asks the sharper question — if a quantity runs
away there, it is the model. The other reading is not wrong, it is dearer: it makes check
6 unrunnable instead of blind, and it ties it to two unbuilt steps.

**The price, and it does not go away once the six steps are built.** The target mask
`weltlauf` writes 175 of the 310 addresses, the other 135 keep their start value (T38). Of
the 117 addresses of the eight bounds, **65 lie outside it**: `markt.wert` (bound 5, 1
address, block market basket), the 32 pressures and counter-pressures (bound 6, block
instruments without level), the 32 fund shares and position tiers (bound 7, block fund).
In check 6 these three bounds measure the **start assignment** and nothing else — in round
200 those 65 carry the value of round 0, not because the model leaves them alone but
because the mode does not touch them. Bound 6 and bound 7 are exactly the two whose column
*why it is not mere cosmetics* speaks of an unbounded channel 8 and of shares above 100 %,
and bound 5 of the overflow.

**Where the three can break instead.** Check 2 evaluates the bounds in every round of every
run, so 5, 6 and 7 break wherever a `spielmodus` game runs — a bot or a player places
actions, and step 2 is dropped in the `weltlauf`. Among the eight checks that is check 1
(unit tests, on a minimal state), check 4 (regression corpus), **check 5 (10,000 bot games,
the broadest of them)** and check 7. **What none of them does is 200 rounds:** they run
over `R` = 24. A runaway that needs a long horizon — in the fund block, in channel 8, in the
basket value — is checked by nobody, and that is report 1 of section 28, not a rule here.

**And the other reading would not have bought bound 6 in full either.** With an empty
action bundle the 16 `druck` addresses never leave 0, because pressure arises solely
through action 3 (section 7, point 1), and `gegendruck` is formed in step 5 from `hub` and
from its own previous value (the counting table in section 10), so it moves only if an
instrument moved — which without lobby pressure it does not. 16 of bound 6's 32 addresses
stay at their start value in **both** readings.

**Check 6 runs past the end of the vintage window, and that rule now has an owner.**
The exogenous paths from T25 carry only R+1 support points. From round R+1 on they are
**frozen at their last value**, not carried forward, and the run is marked
`ueber_fenster`. Freezing is the sharper choice here: if a quantity runs away afterwards,
it is the model and not the input. Cost: 200 world steps. At R = 24 the support points
cover rounds 0 … 24, so rounds **25 … 200 are outside the window — 176 of 200**; the
finding names 175 because it begins freezing one round later.

| What | Where it arises | Responsible |
|---|---|---|
| **the freeze** | in `daten`, in the one accessor that answers „value of path P in round `t`": `t` enters the series as `min(t, R)`. Not at the caller — the second caller who forgets the clamp reads behind the end of the series, and that is exactly the failure the finding names | data builder |
| **the mark `ueber_fenster`** | a property of the run, not of the state — the same construction as the mode in T38, and no 311th field. It is **derived**, `runde > R`, not latched by the accessor, so that a round which reads no path at all is marked too. `R` is available there: it arises on loading the vintage per T40 | data builder forms it; **break tester** carries it into the finding of check 6, beside the mask size that T38 already requires there |

Neither exists today: there is no freezing and no marking in `kern/` or `daten/`, and the
word occurs only in this file. That is without consequence only as long as the `daten` box
of T13 is unbuilt — there are then no support points to run past. **Whoever feeds the
target series in without building the rule with them gets a carry-forward into nothing or
a read behind the end of the series.** By which route a path value reaches the round —
through T10b's carrier or beside it — is not decided here; that is report 2 of section 28.

**T31 — The regression corpus is never silently regenerated.** A deliberately changed
model value turns check 4 red — that is the purpose. Renewal runs via a call of its own,
which writes a **deviation report**: which game, which quantity, old and new value, which
chain links changed. This report is the subject of the check, not the new corpus.

**T34 — The result quantity is an `i64` in milli-rounds; the scale belongs to `spiel.md`.**
The three-part table stands there and is **not** repeated here, not interpreted and not
capped. What the architecture is entitled to is exclusively:

- type `i64`, unit milli-rounds, **smaller is better**;
- the order is strictly total: on an equal result value the profile id decides, on an
  equal profile the sample index — never the order of discovery;
- the median over an even count is the smaller of the two middle values
  (so `spiel.md`);
- **the range check is the band check.** `spiel.md` demands: a result outside
  `1.000 … R × 1.000 + 30.000` — at R = 24 thus 1,000 … 54,000 — is a hard error.
  The check is sharper and involves no decision of its own, because it follows from the
  same table: the value must lie in **one of the three bands** from T40. The gaps between
  them (24,001 … 24,999 and **28,001 … 30,999** at R = 24) are unreachable; a value there
  is a computation error and not an outlier. The check costs two comparisons and finds
  exactly the edge that finding 10 found at the scale itself. Since `spiel.md` version 4
  the upper gap begins at 28,001 and no longer at 27,001, because the capping of the
  shortfall has been dropped (T40); the range `1.000 … R × 1.000 + 30.000` is untouched by
  that, because its upper end comes from the death band.

**T35 — The draw rule for Maß 1, written out, because otherwise it hangs on the random
generator.** `spiel.md` prescribes: bundle size uniformly from `{0,1,2,3}`, then that many
actions without replacement, uniformly from the list of admissible actions, duplicates in
the sample set stay. That is unambiguous up to the procedure, and a different procedure
yields a different sample. Binding is therefore:

1. `s = splitmix64(wurzelstartwert, jahrgang_id, parameter_pruefsumme, BUENDELZIEHUNG, t, i)`
   per T11; `s` is carried forward as xoshiro state, and only within this one
   draw.
2. `n = naechster(s) mod 4`. If `n` is greater than the length `m` of the admissibility
   list, `n = m` holds.
3. The list stands in the canonical order from T32. Partial Fisher-Yates:
   for `k = 0 … n−1` let `j = k + (naechster(s) mod (m − k))`, swap `L[k]` and `L[j]`.
   The bundle is the first `n` entries.
4. Before being placed the bundle is sorted by action id. Per `spiel.md` no action has a
   time within the round; the sort ensures that the draw order does not touch the result.
   If the bundle violates `buendel_zulaessig` (T32), it is cut to the largest admissible
   prefix — not redrawn, because a rejection loop would make the number of draws
   state-dependent.
5. **The stock carry-forward of the injected round** follows `spiel.md`: `vi += 3·ai` at
   the round start with the `ai` of the reference profile, then `vi −= 5` per action of
   kind `i` actually placed. With a bundle smaller than three the stock drifts, and that
   is intended — the carrier game then plays on with the state the injection left behind,
   not with a straightened one.

`naechster(s) mod k` is biased as soon as `k` is not a divisor of 2^64. For `m ≤ 2^32` the
bias lies below 2^-32 and is thus smaller than any effect Maß 1 measures; it is named here
instead of fixed, for the same reason as in point 4.

**T43 — The stock procedure is a component of the test bench, and it has an invariant
that makes it testable.** `spiel.md` fixes it (stock `vi`, `vi += 3·ai` per round, three
slots, `vi −= 5` per slot, largest `vi` wins, tie by smaller id, `ai = 0` does not forbid
but pushes to the back). The architecture is entitled to two things, and both stand
here:

- **The admissibility it checks against is the list from T32** — formed once per round
  against the round-start state, and while stepping across the three slots shortened only
  by the entries incompatible with the bundle. No world step, no intermediate
  computation.
- **The invariant a unit test runs against:** if in five consecutive rounds all five
  kinds are admissible throughout, the stock vector stands at `(0,0,0,0,0)` again
  afterwards, and each kind `i` has received exactly `3·ai` of the fifteen slots. That
  holds for **all 126 profiles** — I have computed it through for all 126, and the check
  of the reference profile that `spiel.md` itself gives (`1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 |
  3,4,5`) falls out of it character-identically. With that the procedure is not merely
  described but has a test that catches a wrong implementation in five rounds instead of
  in a 24-round game with a median over twenty seeds.
- **The same invariant in general form — and since `spiel.md` version 4 it stands
  word-for-word identical in both documents:** after `5k` rounds the stock vector stands
  at `(0,0,0,0,0)` again, and kind `i` has received `3k·ai` of the `15k` slots. For
  `k = 1` that is five rounds and `3·ai` of fifteen — exactly the case that `spiel.md`
  computes as a check two paragraphs further down. For `k = 3` it is fifteen rounds and
  `9·ai` of forty-five. The sentence that in versions 2 and 3 of `spiel.md` said „über 15
  Runden … `3·ai`" and mixed both cases is replaced there; the spot that was a finding
  three times is closed, and I have laid both sentences side by side in this run.
  Binding for the build remains this invariant; the unit test from T30 check 1 checks
  `k = 1` and `k = 3`, so that the mix-up shows even if someone carries it into the
  implementation from an older version.

**T41 — How the profile restricts the search bot's candidates.** That was the half of
finding 4 that belonged to me: T35 wrote out the draw rule only for Maß 1. Binding is:

1. The stock procedure (T43) delivers the kind sequence of the round's three slots.
   The search bot searches **over targets and steps, never over kinds** (`spiel.md`).
2. For candidate `c = 0 … 59` and slot `j = 1,2,3`: `Lj` is the sublist of the
   admissible actions of the slot's kind in canonical order (T32), shortened by the
   entries incompatible with the already chosen `x1 … xj−1`. Drawn is
   `xj = Lj[naechster(s) mod |Lj|]` with
   `s = splitmix64(…, SUCHBOT_KANDIDATEN, runde, c)`.
3. A slot without an admissible kind is dropped; otherwise `|Lj| ≥ 1` always holds,
   because the stock procedure chooses only among kinds with at least one admissible action.

**Exactly three draws per candidate, exactly 60 candidates, no rejection loop, no counting
of a product space.** Duplicate candidates stay — as in Maß 1 —, they cost one world step
and change no result. The price is thereby fixed at `1 + 60` world steps per round,
regardless of how large the admissibility list currently is; that is the same reasoning
as with T28 and the reason the calculation in section 10 holds up at all.

**T44 — The search bot's objective is the result forecast of the intermediate state, and
it is derived, not invented.** T41 said **which** 60 candidates arise, but not **by what**
one is chosen among them; the tie-breaker presupposed a comparison quantity that no
sentence named. As long as it is missing, Maß 2 measures the choice of the build agent
instead of the game, and Maß 3 measures it twice.

After exactly one world step the game is as a rule still running; the result quantity of
`spiel.md`, however, is defined only at game end. What is needed is therefore a **static**
valuation `B(z)` of the intermediate state, and it answers the question the result
quantity itself asks: *What would this game yield if it ended here?*

```
B(z) =  r × 1.000                      das Mandat ist in Runde r erfüllt
        30.000 + (R + 1 − d) × 1.000   in Runde d an einer Todesart gestorben
        (R + 1) × 1.000 + v(z) + e(z)  sonst — die Partie läuft weiter
```

**All three lines have been, since `spiel.md` version 4, word-for-word the result quantity
from `spiel.md`, only computed on `z` instead of on the game end.** In version 4 of this
document the third line still carried the literal `25.000`; it now stands as a formula in
R, because T40 tolerates no derived number as a literal and `(R+1) × 1.000` on a different
vintage is simply not 25,000. At R = 20 it is **21,000** — the literal of version 4 would
be wrong today, and that is the whole point of the formula.

- `v(z) = teile_gerundet(max(0, schwelle_v − fondsvermoegen(z)) · 1.000, schwelle_v)` —
  missing assets in per mille of their threshold. `fondsvermoegen` is the function from
  **T47** and thus, since `spiel.md` version 4, includes the stakes valued at exit
  value; a second computation path does not exist.
- `e(z)` = sum over the **two countries with the highest influence** (tie by
  `LandId`) of `teile_gerundet(max(0, schwelle_e − einfluss[land]) · 1.000, schwelle_e)` —
  missing influence in per mille of its threshold. Two countries, because the mandate
  demands two. `spiel.md` version 4 has adopted the same rule for the result quantity;
  both documents now compute the shortfall with **one** formula.

Both thresholds already stand in `parameter.toml` (T27, mandate threshold). **`B` thus has
no free parameter** — no weighting, no calibration value of its own, nothing a build agent
could choose. Exactly that is the answer to the objection: Maß 2 no longer measures the
bot's choice, because at this spot no choice remains.

**And `B` is bound to `spiel.md`, not placed beside it.** If the design names the
comparison quantity itself, its version trumps this one, and T44 shrinks to the
calculation rule for it. If the result quantity changes, `B` changes with it, without
anyone having to keep two places in step.

**Since `spiel.md` version 4 there is no deviation left between `B` and the result
quantity, and that is the actual news of this version.** Version 4 of this document had
to exempt a cap here: `spiel.md` then bounded each of the two parts at 1,000 per mille,
and for a valuation function that would have been fatal — a fund that at game start has
influence zero in both countries would sit at a capped 1,000, and an improvement of the
first country from 0 to 60 percent of the threshold would remain **invisible**. The game
designer let the same reasoning apply one level up and **struck the cap entirely**. With
that both documents compute letter-identically in this branch, and the spot can no longer
drift apart.

The price stands in T40 and T34 and is twice a number: the band end went from
`(R+1) × 1.000 + 2.000` to `(R+1) × 1.000 + 3.000`, the lower edge of the gap above it
one milli-round with it — at R = 20 thus 23,000 → 24,000 and 23,001 → 24,001. The bound
remains: `v ≤ 1.000` as long as the fund lives
(at `fondsvermoegen ≤ 0` way of dying 1 takes hold in the same round, T33 and T47; only
the rounding reaches the 1,000), and `e ≤ 2.000`, thus
`(R+1) × 1.000 ≤ B ≤ (R+1) × 1.000 + 3.000` in the running case — at R = 20
**`21.000 ≤ B ≤ 24.000`**, above the band „mandate fulfilled" (up to `R × 1.000`, at
R = 20 thus 20,000) and below the death band (from 31,000, which per T40 does not hang on
R). **From that follows a property a valuation must have and that cannot be
seen in it: the bot never prefers death.** The worst running state stands at
`(R+1) × 1.000 + 3.000`, the best death at 31,000 — at R = 20 that is 24,000 against
31,000, and per T40 the two bands stay disjoint up to `R ≤ 26`. Despite the formula identity, `B` remains a **bot-internal**
quantity: it is never reported as a game result, and the band check from T34 does not
apply to it, because it stands on an intermediate state and not on a game end.

**Why this does not structurally kill the lobby path** — the question on which a pure
asset valuation would have failed: influence is per `spiel.md` the smoothed share of the
fund **in a country's total lobby pressure**, not the effect of the instrument. Action 3
applies the pressure in the same round; it thus raises `einfluss` already within the one
world step the bot computes ahead — damped by the smoothing, but non-zero and monotone in
the budget deployed. The cash outflow raises `v`, the pressure lowers `e`, and which
effect prevails is decided by the state and not by the construction of the valuation.
Class 3 **can** thus produce winners; whether it does is the question Maß 2 is meant to
ask, and not the one it answers before it runs.

**The same check for the two other classes, because a class checked alone proves
nothing.** Class 1 (position) acts directly on `fondsvermoegen` and thus on `v`;
unproblematic. **Class 2 (stake) hung on a question that `spiel.md` version 4 has
decided: the twelve stakes count towards the fund assets** (T47), valued at exit value.
Action 2 thus acts on `v` like action 1, only illiquid and reduced by the exit discount,
and `B` treats both alike. Version 4's discussion — of what would happen if they did not
count — is thereby moot and struck; it had a single purpose, namely to keep the question
visible until it is answered.

A second path of class 2 stays invisible at depth 1, and this point stands: a stake
cheapens, per `spiel.md`, the lobbying in the same sector, and thus pays off only in a
later round. That is not a flaw of the valuation but the price of one move of lookahead —
and with that the first concrete argument for depth 2, which section 12 keeps open.

**Order and ties.** Chosen is the candidate with the smallest `B`. On a tie the
lexicographically smallest sequence of the bundle's action ids in the canonical order
from T32 decides, then the smaller candidate index `c` from T41 — never the order of
discovery. Duplicate candidates (T41 expressly allows them) carry the same id sequence
and the same `B`; their tie falls to `c` and is thereby decided.

**Depth.** At depth 1, `B` is evaluated on the state after the one world step, and there
is **no** continuation by the heuristic bot — the phrase „Nachspiel mit dem
Heuristikbot als Fortsetzung" from version 3 was misleading at this spot and is the
reason the finding could arise. At depth `d > 1` the value of an inner node is the
minimum of `B` over its 60 candidates, recursively to depth `d`;
the game has a single player, so there is no counter-move and no maximum.

**Costs, corrected in this version.** Version 5 said „rund zwanzig
Ganzzahloperationen, also drei Promille" and thereby counted only `v` and `e` themselves —
the reviewer of round 6 objected to that under *geprüft und nicht gezählt* and was right.
`v(z)` calls `fondsvermoegen(z)`, and per the count in T47 that is around **230**
operations, 71 of them `i128` divisions; plus one division for `v`, four comparisons and
two divisions for `e`. Together **around 240 integer operations** against 7,500 per
world step, thus a good **three percent** instead of three per mille. In the search bot
they occur 60 times per round, against 61 world steps — there too around three percent.
The plan value of 10 µs has bandwidth up to 30, the reserve calculates with 50, and the
shortcut on empty slots (T47) lowers the actual value further. The cost calculation
`R × (1 + 60)` — at R = 20 thus **1.220** world steps — stays unchanged in its form, and
exactly for this a static valuation is needed. A playout to round R per candidate would
cost `60 · Σ(R+1−t) + R`, with `Σ(R+1−t) = R(R+1)/2`, at R = 20 thus
`60 · 210 + 20 = 12.620` world steps per game, **around ten times** as much
(12.620 / 1.220 = 10,3), and would overturn section 10.

**The three bots:**

- **Zufallsbot(startwert)** — admissible actions uniformly, draw per T35, without a
  profile. For checks 5 and 6.
- **Heuristikbot(profil)** — kinds per the stock procedure (T43), within a kind by a
  fixed, documented ranking. No playouts, hence cheap. **On the reference profile
  `(1,1,1,1,1)` it is the „feste Folgepolitik" of Maß 1.**
- **Suchbot(profil, kandidaten=60, tiefe=1)** — 60 candidates per T41, each computed one
  world step ahead and **statically valued per T44**; chosen is the smallest
  `B`, ties per T44 and never by order of discovery. There is no continuation by the
  heuristic bot at depth 1. Cost per game `R × 61`, at R = 20 thus
  **1,220** world steps.

**T36 — What the test bench hard-wires for Maß 2 and 3.**

- **Profile list.** The 126 profiles are generated in lexicographically ascending order
  of `(a1…a5)` and numbered **zero-based**. The **profile id** is this index and the
  tie-breaker from `spiel.md`; it is part of the interface version (T17). Two fixed
  values as anchors for the test, both computed through: the reference profile
  `(1,1,1,1,1)` carries **id 76**, and the ids **0 to 5** are exactly the six profiles
  `(0,0,0,a4,a5)`.
- **Strategy core, four-valued.** The action kind with the largest share among
  `{1 position, 2 stake, 3 lobby}`, tie by smaller id; leverage and visibility do not
  enter. **If all three are zero, the core is `ohne`** — not 1. That is finding 8, and it
  can only be fixed at this spot: a three-valued core forces the tie-breaker to assert a
  position strategy in which no position occurs. Profiles with core `ohne` run along,
  their result is reported, and they enter neither of the two acceptance halves of Maß 2;
  120 are classified. The core is computed once per profile and stored with the profile
  list, not anew per run.
- **Window logic of Maß 3.** Both runs go over the full game; the windows are per T40 the
  first and the last game third, outside them the reference profile holds, and the search
  bot runs inside as outside. The profile switch happens at the round start;
  **the stock runs on across the switch and is not reset**
  (`spiel.md`). A run thus costs the same as an ordinary search-bot game, and the
  calculation in section 10 holds. For Maß 3 all 126 profiles are selectable, including
  the six without a core — there the vector distance measures, not the class.
- **What `B` from T44 is not, in either measure.** The profile result `E(p)`, the win
  comparison against `R × 1.000` and the argminima `p*` and `q*` run exclusively over the
  **result quantity** from `spiel.md`, never over `B`. `B` steers the bot within the game
  and does not leave it. Both measures therefore hang on T44 — that is why its absence
  was a severe finding —, but neither of the two computes with it.

**T37 — The backtest reports per target series whether it can check anything at all — and
`spiel.md` has decided which ones decide.** In the `weltlauf` the policy instruments are
set to the historically actual values. The model's policy-rate series is thereby the
target series by construction; its error is zero and its directional accuracy one,
without the model having achieved anything.

**Every count in this block is a formula in `L_R`, `S` and `n` (T59), no longer a digit —
changed 2026-09-08, package `0221`.** `L_R` is the number of backtest countries, `S = 3`
the sectors, `n = 1` while the numéraire country is a backtest country. Substituting
today's `L_R = 4` returns every number this block carried before, digit for digit; that is
the compatibility check, and it is why this change moves nothing today. **Which reading
binds, and until when, stands in section 26** — it is `L_R = 4` and not the nine countries
of `spiel.md`.

| Class | Series | Count | today (`L_R = 4`) | Meaning |
|---|---|---|---:|---|
| `frei` | GDP (`L_R`), sector shares (`L_R·S`), consumer prices (`L_R`), exchange rate (`L_R − n`) | `L_R(S+3) − n`, of them `L_R(S+2) − n` independent, plus the trade block | 23 (19 independent) | checks the machine, decides the acceptance |
| `gesetzt` | policy rate (`L_R`) | `L_R` | 4 | input of the run, error zero by construction; is reported, decides nothing |
| `abgeleitet` | government debt ratio (`L_R`) | `L_R` | 4 | numerator follows the set budget balance, only the denominator is endogenous; is reported, decides nothing |

**The acceptance runs over `3·L_R + (L_R − n) + 1` check subjects with tolerance
`⌊L_R/2⌋`.** So set by `spiel.md`: version 3 wrote the two as the digits 16 and 2, the
addendum of 2026-09-06 replaced them by exactly these two formulas: *"The number of check
subjects and the tolerance stand from here on as formulas: `3·L_R + (L_R − n) + 1` and
`⌊L_R/2⌋`"* (`spiel.md`, section *Was der Architekt neu rechnen muss*, table row **T37 /
tolerance**, read 2026-09-08). At `L_R = 4` they give **16 and 2**, at `L_R = 7` **28 and
3**. My query from
version 2 is thereby answered and struck from section 12. The check subject is not the
series but the quantity:

| Check subject | Count | today | aggregated from |
|---|---|---:|---|
| GDP per country | `L_R` | 4 | one series each |
| sector structure per country | `L_R` | 4 | the country's `S` share series, **all of them** must pass |
| consumer prices per country | `L_R` | 4 | one series each |
| exchange rate per country except the numéraire | `L_R − n` | 3 | one series each |
| trade block | `1` | 1 | `(L_R+1)·L_R·(S−1)` flows, today 40, median of the MAPE and median of the directional accuracy; the worst fifth is reported |
| **Sum** | `3·L_R + (L_R − n) + 1` | **16** | |

A check subject passes if it holds both thresholds that apply to it. The run is passed if
at most `⌊L_R/2⌋` of them are breached — today two of sixteen —; each breached one is
named individually, with both numbers. Reported are all `L_R(S+5) − n` series plus the
flows, today **31**. **Of those 31, `L_R(S+4) − n` = 27 are target series** since the cut
of 2026-09-03 (`spiel.md`, package `0054`: series 9 lost its target role and keeps its two
others). The word "target series" for all 31 is the **second wave** and is deliberately
not repaired here — it belongs to `0068-technikmd-reihe-9-ohne-sollrolle`; section 26 says
why.

**T42 — The three error measures, written out, because `spiel.md` puts numbers on them
and does not compute them.** Everything in integers via `teile_gerundet` (T6). `S` is the
number of support points (25 in the check vintage), `V` the set of usable support points.

**Level series** (GDP, sector shares, government debt ratio, 40 trade flows) —
mean absolute percentage error in ten-thousandths, threshold **2,000 (= 20 %)**:

```
MAPE = Mittel über t ∈ V von  teile_gerundet(|modell(t) − soll(t)| · 10.000, |soll(t)|)
```

**`V` excludes two sorts of support point, both counted and reported:** those with
`gefuellt = 1` (as T24 already has it) and those with `soll(t) = 0`. The second case is
real for a bilateral agricultural flow between two countries, and a zero denominator is
per T6 an abort. If a flow has fewer than half its support points usable, it counts as
not checkable, does not enter the trade block's median and is reported as such. The rule
changes no threshold; it defines a case that `spiel.md` does not know, after the pattern
T24 already prescribes for filled years.

**Rate series** (consumer prices, exchange rate, policy rate) — mean absolute error on
the annual rate of change, threshold **300 bp**:

```
rate(t) = teile_gerundet((wert(t) − wert(t−1)) · 10.000, wert(t−1))          in bp
MAE     = Mittel über t = 2 … S von |rate_modell(t) − rate_soll(t)|
```

**A rebasing per T8 is factored out before the rate formation:** if `basiswechsel` rises
by `d` between `t−1` and `t`, `wert(t)` is multiplied by `1.000^d` for this one rate.
Without this line a base change would report a plunge of 99.9 percent as model error. In
the check vintage it never occurs — it stands here because T8 itself demands that no
branch stay unchecked, and the 1980 regression game takes it
along.

**Directional accuracy** (all series) — share of the `S−1` transitions with the same
sign, in ten-thousandths, threshold **6,000 (= 0.6)**:

```
treue = teile_gerundet(#{t : sgn(Δmodell(t)) = sgn(Δsoll(t))} · 10.000, S − 1)
```

`sgn` is the three-valued sign function on integers; "both unchanged" thus counts as a
hit and "one unchanged, one not" as a miss. That follows from the notation in `spiel.md`
and is not an interpretation — on integers there is no other.

**Parallelism without giving up determinism:** every playout is a pure function of
(vintage, parameter set, mode, seed, policy, round, sample index); the derived random
seed follows from exactly this tuple (T11). Results are placed into a pre-sized array
**at their index**, never appended. Every aggregation runs over the sorted array. The
test bench thus delivers the same result with one core and with
thirty-two.

**Reporting duty:** every finding carries `ticks_gesamt`, `sekunden`, `ticks_je_sekunde`,
the mode and the size of the target mask. The estimate of the next section is thereby
replaced within one night by a measurement — and stays measured.

## 10. Was das Modell an Rechenzeit kostet

A world step comprises an estimated 7,500 elementary integer operations; the lion's share
is carried by the market clearing (2 sectors × 40 halvings, T28) and the recording of the
chain (T18). Expensive within that are the `i128` divisions from T6. **Plan value: 10
microseconds per step**, bandwidth 5 to 30. The column "unfavourable" reckons with 50
microseconds, five times the plan value — a reserve, not an expectation.

**The valuation from T47 does not change this estimate, and this time the number is counted
rather than rounded.** A full call of `fondsvermoegen` costs, per the table in T47, around
230 integer operations, 71 of them `i128` divisions; it occurs in `spielmodus` once per
world step in step 6 and in the search bot additionally per candidate. That is a good three
percent of a world step, not the three per mille of version 5 — and still deep inside the
bandwidth of 5 to 30 µs that the plan value carries anyway. **In the `weltlauf` it does not
occur at all**, because the fund subsystem per T38 does not run; the backtest is untouched
by the correction. No row of the table below moves.

**Counterforce 5 costs per round 106 read accesses, 16 write accesses and 16 calls of the
third scale transition, and this number too is counted.** The breakdown is in `spiel.md` in
the section *Wo die Regel läuft, und warum Kanal 3 zyklenfrei bleibt*; it is recounted
here and agrees:

| from where | addresses read | count |
|---|---|---:|
| step 3 | `lies_neu(land.<l>.instrument.<i>.stand)`, 4 countries × 4 instruments | 16 |
| step 4 | `lies_neu(welt.preis.<s>)`, s ∈ {1, 2} | 2 |
| step 4 | `lies_neu(handel.<a>.<b>.<s>)`, the whole trade block | 40 |
| step 4 | `lies_neu(land.<l>.sektor.<s>.wertschoepfung)`, for `bip`, 4 × 3 | 12 |
| step 4 | `lies_neu(land.<l>.staatsschuld)`, for `schuld` | 4 |
| previous round | `lies_alt(land.<l>.instrument.<i>.stand)`, for `hub` | 16 |
| previous round | `lies_alt(land.<l>.instrument.<i>.gegendruck)`, for the decay | 16 |
| | **Sum** | **106** |

`16 + 2 + 40 + 12 + 4 + 16 + 16 = 106`. **Counted are distinct addresses, not access
operations**, and at exactly one row that makes a difference: the trade block stands at
**40** and not at 64. 64 would be the number of operations — four countries times two
sectors times eight flows per `handelsvolumen(l, s)` —, but a flow between two playable
countries enters two of them. The 40 are the block in full: per T15
`Gebiet × Gegenüber × handelbarer Sektor = 5 × 4 × 2`, and the four `handelsvolumen`
together touch every ordered pair of territories, because at least one playable country
takes part in every pair. The 16 write accesses are the sixteen `gegendruck` addresses, the
16 calls those of the third scale transition from T50 — one per address, all in step 5, and
that is at the same time the proof of its "exactly one call site".

**On the table above this has no effect.** 106 read accesses and 16 multiplications are,
against the estimated 7,500 integer operations of a world step, around one and a half
percent, and counterforce 5 was already running in that estimate; new is not the work but
that it is counted out. **Two earlier numbers are thereby superseded**: the 120 of the
version of 2026-09-02 (it counted the tariff state twice although the tariff row of that
time did not read it at all) and the 112 of the check finding of 2026-09-02 (correctly
computed, but for the old tariff row). The path from one to the other:
`112 + 8 − 16 + 2 = 106` — the tariff state comes in with `lies_neu` and `lies_alt`, both
sector price rows drop without replacement, the two world prices take their place.

**The plan value is unchanged: estimated and not measured.** My logbook demands reading
the measured `ticks_je_sekunde` first on the next run; it still does not exist. Under
`ventures/0016-…/kern/` there now stand fixed point, random, checksum, state and writer,
but no world step and no test bench run — measured is thus the arithmetic, not the loop.
That remains the biggest uncertainty of this section, and it stands in
section 12.

The basis is the **R = 24-round game** from `spiel.md` version 3. All rows are computed in
this run.

| Run | world steps | at 10 µs | unfavourable (50 µs) |
|---|---:|---:|---:|
| one game, heuristic bot | 24 | 0.24 ms | 1.2 ms |
| one game, search bot (60 candidates, 1 move ahead) | 1,464 | 15 ms | 73 ms |
| **1,000 games, heuristic bot** | 24,000 | **0.24 s** | 1.2 s |
| **1,000 games, search bot** | 1,464,000 | **15 s** | 1.2 min |
| decision density, K=30, one seed | 9,024 | 0.090 s | 0.45 s |
| **decision density, 50 seeds** | **451,200** | 4.5 s | 23 s |
| **strategy diversity, 126 profiles × 20 seeds** | **3,689,280** | 37 s | 3.1 min |
| **shift of the optimum, two windows** | **7,378,560** | 1.2 min | 6.1 min |
| **break run, 10,000 random games** | **240,000** | 2.4 s | 12 s |
| **boundedness, 200 rounds** | **200** | 2 ms | 10 ms |
| **backtest, one `weltlauf`** | **24** | 0.24 ms | 1.2 ms |
| **regression stock, 1,000 games** | **24,000** | 0.24 s | 1.2 s |
| **night run total** | **11,783,264** | **2.0 min** | **9.8 min** |

The rows one by one, so that the sum can be recounted: `Σ(R+1−t)` for `t = 1…24` is
`300`, so `30 × 300 = 9.000` per seed, plus 24 world steps for the carrier game gives
**9,024**; times 50 seeds **451,200**. `126 = C(9,4)`, `1.464 = 24 × 61`,
`3.689.280 = 126 × 20 × 1.464`, `7.378.560` twice that. The three Maße together are
**11,519,040**, just as `spiel.md` computes it. The night run adds break run, boundedness,
backtest and regression stock:
`11.519.040 + 240.000 + 200 + 24 + 24.000 = 11.783.264`. The two rows "1,000 games" are
comparison values and do not enter the sum.

Everything on **one** core. With eight cores the night run falls to an eighth: at R = 20
(9,759,420 world steps) to around **12 seconds** at the plan value and to around
**1.0 minute** in the unfavourable case. **The table above still stands on `R = 24`** —
its catch-up is the row *Abschnitt 10, Laufzeitbudget* of the catch-up table in `spiel.md`
and belongs to a package of its own, not to this one; section 29 says so.
What is used to parallelise is per T3 open and immaterial for this document: bound per
section 9 is that a run delivers the same result with one core and with thirty-two, not
the means by which that is achieved.

**The answer to the question this section is meant to answer: yes, the test bench can run
daily — and hourly.** The bottleneck is not compute time but the token budget of the
agents who read the findings.

**The calibration loop.** A thousand parameter sets over the full set of Maße (11,519,040
steps per set) cost 11.52 billion world steps, that is **32.0 hours on one core and 4.0
hours on eight** — not a night task. Night-capable is the shortened version: Maß 1 with 10
instead of 50 seeds (90,240) and Maß 2 with 5 instead of 20 (922,320), Maß 3 not at all,
because the shift of the optimum only becomes interesting once Maß 1 and 2 hold. Together
**1,012,560 steps per parameter set**, for a thousand sets thus **21 minutes on eight
cores**. The instruction to the self-player is therefore: search roughly with the
shortened version, recompute the ten best sets with the full one.

**The counter-calculation that carries the stack choice:** the same world step costs in
Python between 0.75 and 3 milliseconds, that is 75 to 300 times as much. The night run
would lie at **2.0 to 8.1 hours** on one core (9,759,420 world steps at R = 20 times 0.75
and 3 milliseconds). It would then be not daily but
occasional — and the calibration loop would be impossible even in the shortened version.
That is the number the choice from T1 hangs on. It has become smaller through the shorter
game, but the gap is the same: the factor decides, not the game length.

**At the buyer's** a round costs one world step: 10 microseconds. The memory footprint is
2.5 kB of state, under 1 MB of vintages and a few hundred kB of chain history. The
product runs on anything and needs no server — the idea's cost calculation (no cost per
customer) holds.

## 11. Auslieferung, und wo Geld anfängt

**Windows x86-64 first**, Linux alongside (the same program, a different target id),
**macOS not in version one**: notarization by Apple costs 99 USD per year and would be an
expense under house rule 1. Likewise: a hosted build environment is **not** the default
path — building and checking happen in the factory's night run, on the operator's
machine. Whoever wants a hosted chain writes a gate template.

Platform equality is not asserted but checked: check 3 compares the checksums from the
Windows and the Linux run of the same games.

From `daten.md` follows a delivery requirement: `LIZENZEN.md` next to the vintage files,
a page „Datenquellen" in the main menu, one sentence on the processing („Die Ausgangsdaten
wurden aggregiert und in ganzzahlige Einheiten umgerechnet; die Quellen verantworten diese
Bearbeitung nicht"), and the note that the IMF data are available free of charge from the
IMF. All three places are generated from the vintage's manifest (T23), not maintained by
hand — otherwise they diverge from the truth at the first data-update run.

## 12. Was ich nicht entschieden habe

The queries of versions 2 and 4 — acceptance over 31 or 23 series, aggregation of the
trade block, stakes in the fund assets — are answered by `spiel.md` versions 3 and 4 and
stand in T37 and T47; they are struck here, because an answered question in this list
only costs space. What remains open:

- **Two spots in ADR 0011 that I cannot decide myself. Neither blocks anything, both
  belong to the operator.** *First:* measure 2 of the ADR is meant to make unintended
  overflows „laut statt still"; it cannot, because `-fwrapv` from measure 1 switches off
  exactly this sanitizer check (evidence in T7). I closed the gap with a fourth measure
  instead of changing the ADR — that is my decision; whether the ADR is brought up to
  date is not. *Second:* the first argument of the ADR presupposes that the saved game
  will in future store the **state** instead of the action sequence; the consequences of
  the ADR do not order this switch. Until then T22 holds unchanged, and from it follows
  T52. If the switch is ordered, T52 becomes cheaper, but not superfluous.
- **The plan value of 10 microseconds per world step is still an estimate.** The core now
  exists in parts — fixed point, random, checksum, state, writer — but no world step, and
  thus still no measured `ticks_je_sekunde`. If the measured value lies above 50 µs,
  section 10 no longer carries, and then the market clearing must be built differently
  than over 40 halving steps. That is the only number in this document that a check
  during the build can overturn — and since T6b, it additionally carries the question
  whether the division form explains the gap from the stack measurement.
- **Whether the search bot at depth 1 is strong enough for Maß 2 to measure the game and
  not the bot.** *What* it searches for has been decided since T44 and has no free
  parameter left; open is only *how far*. Recomputed for R = 20: depth 2 costs per game
  `R × (1 + 60 × 61)`, that is `20 × 3.661 = 73.220`
  instead of 1,220 world steps, Maß 2 and 3 together `3 × 126 × 20 × 73.220` =
  **554 million**, that is 1.5 hours
  on one core and **around 12 minutes on eight** at the plan value, in the unfavourable
  case around 58 minutes on eight. That does not burst the night run, it relocates it. Depth 2 is
  thus not an exclusion but a decision the self-player may take if Maß 2 finds no winner
  in all three classes at depth 1.
- **The numeric values of all thresholds and elasticities.** Per T27 they stand in the
  parameter file and are searched for by the self-player, not set by me.
- **The concrete ranking in the heuristic bot** within a kind. A modelling question for
  the self-player; the architecture demands only that it is fixed, documented and
  tie-free.
- **The exclusion rule for support points with `soll = 0` (T42) I decided, not left
  open** — it follows the pattern T24 already sets for filled years, and without it the
  backtest aborts at a bilateral zero flow. It changes no threshold. If the game designer
  holds it to be wrong, it is one line in T42 and nothing else.
- **The eleven start values in T46 I likewise decided instead of handing back**, and the
  reason is the same: each of them follows from a rule that already stands (numéraire,
  counter without history, aggregate block without government), none is a choice between
  two sensible numbers. A hand-back would have cost a run of the game designer and
  yielded the same eleven numbers. If it holds one to be wrong, it is a table row.
- **The thirteen scale classes and the three transitions I decided instead of handing
  back**, for the same reason as the eleven start values: a unit is not a game question.
  For two of them the latitude is nevertheless larger than for the rest, and I name them
  so they do not pass as self-evident — the **lobby point** (T50; any other common unit
  for pressure and counter-pressure would do as well, but there has to be one) and the
  **instrument tier** of the financial-market regulation (T5 class 10; it could just as
  well stand in ten-thousandths, then „ein Schritt" would mean a different number). Both
  are one line each, should the game designer want them otherwise.

**Four observations on `spiel.md` that I report instead of changing** (the role forbids
me to contradict the design; none blocks the build). **Point 3 has been settled since
2026-09-04 and remains standing struck through**, because a deleted observation no
longer shows that the hand-back worked:

1. The result scale carries a true literal in the 30,000, and the band „überlebt" pushes
   against it since the capping was dropped, as soon as `R ≥ 27` — the bound is now tight
   instead of generous, recomputed in T40. For 1997–2021 this has no consequence, and
   `spiel.md` only lets the window become narrower. T40 pulls the bound at `R ≤ 26` into
   the vintage build, so that it does not first show up in a result distribution.
2. **Two address pairs carry the same value.** `land.<L>.leitzins` stands in the
   aggregate block *and* as instrument level, `land.<L>.haushaltssaldo` likewise;
   `spiel.md` lists both, T15 carries both, and the target mask from T38 writes both. The
   cleaner version would have one address per pair and come to **302 instead of 310**
   (four countries times two pairs; the rest of world has no instruments) — that is one
   line in `spiel.md` and therefore not mine. As long as it stands, the write-and-read
   rule from T49 applies, and the equality check in T30 check 2. **It blocks nothing;
   unregulated it would be the error type „zwei Herren über eine Zahl", regulated it
   costs 64 bytes and one test.**
3. **~~„Schaden" in counterforce 5 is a quantity without a computation rule.~~ Settled on
   2026-09-03 by `spiel.md`, recorded here on 2026-09-04.** The point asked which of the
   three numbers — price shift times quantity, value-added loss, valuation loss — is
   meant. `spiel.md` chose **the first** and refuted the other two individually (the
   value-added loss is blind to the tariff, because class 2 is real; the valuation loss
   would book channel 1 a second time in channel 3). The rule stands in the section *Der
   Schaden in Gegenkraft 5, als Rechenvorschrift*, the quantity as number 22 in T48, the
   unit unchanged in T50. **The path via the hand-back was the cheaper one:** had I
   filled the number, my choice would stand in Maß 2, and the tariff row would have
   received the error that `spiel.md` found in itself on 2026-09-03 and removed — until
   then it measured inflation and booked it as lobby damage. Having handed back and
   waited one run prevented a wrong quantity here and cost no time.
4. **~~`fonds.sichtbarkeit` is an address, action 5 speaks of a position.~~ Settled on
   2026-09-08 in section 24, out of `spiel.md` itself.** The point asked whether visibility
   is one global number or one per slot. `spiel.md` answers it in *The state*, subsection
   *The consequence of Weg A* (line 1089 as of 2026-09-08): "Slots are occupied **by action
   kind 1 alone**; lobby, leverage and visibility occupy none, the stake has fields of its
   own." The reading held to here —
   a share in ten-thousandths (T5 class 4) that action 5 raises or lowers by one parameter
   step — thereby stands, and T32b line 5 is its consequence: kind 5 has no target. What is
   left over is not an address question but a rule that `spiel.md` describes and nowhere
   computes; it is reported in section 24 to the game designer.

## 13. Hinweis für den Projektmanager

The component cut from T13 is at the same time the collision cut for work packages: two
packages open at the same time must not meet in the same component. The natural order is
`kern` (state, fixed point, randomness, checksum, writer with T18/T38/T39)
→ `daten` and `schnittstelle` in parallel → `konsole` → tests and `pruefstand` →
`oberflaeche`. The vintage (`werkzeuge/aufbereitung`) can run in parallel from the start,
because it is built only against T5, T23 through T26, T40, **T45/T46** and **T49/T51** and
needs nothing from the core. Since this version it carries two more checks, which cannot
tip the venture but do spare a late abort: the scale table over all 310 addresses (T49)
and the lower bound `aufschlag ≥ aufschlag_min` against the historical policy-rate path
(T23 point 5).

**Two packages are to be pulled forward, because they carry design risk and not build
effort:** the vintage build 1997 (T24 says it can fail — 25 support points without filling
for all 31 series and all 40 trade flows are a claim, not a fact, and the IFS policy rate
is supported by only one indication) and the check of the four WDI suspect series 7, 8, 10
and 13 for the third-party exception. Both resolve against data, not against code.

**What has become cheaper compared to version 2:** per T40 a narrower window costs a
number in the manifest and no second package. The vintage build therefore no longer has to
be finished *before* the core, only before the first backtest — it stays in front anyway,
because it can tip the venture and not merely delay it.

---

**From here to the end of section 16 no governing value stands any more — only the
record.** Sections 14, 15 and 16 are dated workings-off of finished checks; their numbers
stand on the state that held at the time of that check — `R = 24`, window 1997–2021, the
three Maße 11,519,040 world steps, the night run 11,783,264 — and they are **not** carried
forward. A record adapted to today proves nothing any more: one could no longer read off it
what the checker saw then and what the architect answered then. **Whoever looks for the
governing R reads T40 and section 10, not here.** The record ends with section 16; from
section 17 on every section is the scope of a package and governs. Marked on 2026-09-08 by
package `0064`, condition 3.

---

## 14. Befundabarbeitung — die vier früheren Prüfungen

**Done and in the git history.** Version 2 answered the eight findings of the first
check, version 3 the twelve of the second, version 4 the three of the third, version 5 the
two of the fourth (round 4). Each of these workings-off was expressly accepted by the
respectively next check under its condition 5; the check of round 6 says it for version 5
verbatim: „Beide Befunde der Vorrunde sind beantwortet, je mit einer der drei
zulässigen Antworten … Beide habe ich gegen die Sache nachgeprüft, nicht gegen die
Behauptung."

Dragging them along here would cost every reader a hundred lines and would bring nothing
that `git log -p specs/0016-…/technik.md` does not say more precisely. Nothing is deleted:
all four workings-off stand unchanged in the version history.

What **lives on** from them stands not in a working-off list but in the prescriptions
that arose from them — T38 to T43 carry the twelve answers of the second check as a rule
instead of a report, T44 and T45 the three of the third, T46 and T47 the two of the
fourth, and each names, at its place, the finding that forced it.

## 15. Befundabarbeitung — Prüfung der Runde 6 vom 2026-09-01 und `spiel.md` Fassung 5

Two findings. The reviewer assigned them to two trades: finding 1 to the game designer,
finding 2 to me. Both are worked off individually, because the role demands it and
because the first one moves eight places here.

**Finding 1, `positionswert(p)` and `korbwert(l, s)` have no formation rule — fixed, on
the side it belonged to, and taken up here in full.** `spiel.md` version 5 forms both
names, along with `anleihewert`, `waehrungswert` and the `anleihekurs` that the reviewer
had named specifically in the fifth step of his proof. I worked off the eight places that
the design lists under *Was der Architekt neu rechnen muss*; here is where each one
landed:

| from `spiel.md` version 5 | incorporated into | recalculated or proven |
|---|---|---|
| `korbwert`, `positionswert` and five further names are formed | **T47**, enumerated in **T48** (new) | 17 functions in the core, 3 in the test bench; four (`bip`, `handelsvolumen`, `anleihekurs`, `korbbestand`) had stood nowhere until today and now stand in T48. *State of this working-off (2026-09-01); since 2026-09-04 there are 22, see section 18* |
| market basket with quantity and price instead of „Modellmarktwerten" | **T33** points 1 to 4 | `marktkorb(m, k)`, quantities via `lies_alt`, prices via `lies_neu` (T39) |
| scale boundary once per valuation, at the outermost call | **T47**, **T5**, **T50** (new) | `tsd_in_cent` with exactly two call sites; `cent_in_tsd` struck, because it has no caller |
| `stufenweite` is a share, new key `aufschlag` | **T5** classes 4 and 3, **T27** | eleven parameter keys with a scale class, five of them new; the 11 addresses with origin `Parameter` remain 11 |
| `leitzins_start[l]` as a constant of the vintage | **T23** point 5 | fourteen vintage constants instead of ten, without a new data requirement (first support point of series 9) |
| capital stock per sector from the normalised shares | **T23** point 1 | `Datenanker(3 × 2)`, the same rule as for value added; T45 still counts 136 anchors |
| „sieben Kanäle" → acht, „achter Kanal" → neunter | **T18**, **T30** check 6 | two places, both wording |
| policy-rate lower bound `1 − aufschlag` | **T51** (new), **T23** point 5, **T30** check 2 | `aufschlag_min = 1 − min(leitzins_pfad)`; at the ECB deposit rate (−50 bp) that is **51 bp**, at the main refinancing rate **1 bp** |

**And one thing I did beyond taking it up, because it belongs to exactly this finding.**
The reviewer writes: „T45s Abzählschritt findet sie nicht, weil sie **keine
Zustandsadresse** ist." That is the actual content of the finding, and it would not have
been answered by two formulas added after the fact. **T48** therefore enumerates the set
in which the gap lay — the functions of the state —, gives it a rule („ein Name, der
weder Adresse noch Parameter noch Jahrgangskonstante noch abgeleitete Größe ist, ist ein
Befund") and a mechanical proof (the public interface of `kern::werte` against the
table). I carried out that proof by hand in this run, in the only form possible before
the build; the four names that fell out of it stand above.

**Finding 2, `beteiligung_wert` delivers thousand USD and is booked as US cents — fixed,
and the finding was right.** The formula of version 5 consisted of two `mal_geteilt`
with unitless shares and was therefore scale-preserving; between input and output,
however, lies the factor 100,000 from T5. The fix stands in **T47**: `tsd_in_cent`
around the outermost call, the same bracket at `positionswert`, and both written down as
**T50**, so that the conversion has a name and a place instead of an opportunity.

**The choice between the two ways I did not make but took over.** `spiel.md` version 5
decides it under *Wo die Skalengrenze liegt*: `korbwert` stays macroeconomic, because
T33 values the same basket and „eine Bewertung, nicht zwei" would otherwise be just a
sentence. What was left to me was which function does it and where it stands — and the
answer to both stands in T47 and T50.

**The reviewer's numerical check, recalculated with the fix.** Basket 21,000,000,000
(thousand USD), `anteil = 20`, `ausstiegsabschlag = 0`: inside, `21.000.000.000 · 20 /
10.000 = 42.000.000` thousand USD, which is 42 billion USD and thus exactly 0.2 % of
21 trillion USD; after `tsd_in_cent`, **4,200,000,000,000 cents**. The cash hands over
the same amount, the fund assets remain unchanged, way of dying 1 does not trigger. The
fund with 42 million USD from the example cannot buy this stake — that is now, correctly,
an **admissibility question** (cash overdrawn, T32) and not an end of the game, and it is
exactly the calibration condition that `spiel.md` poses under *Offene Entwurfsfragen*.

**The same error type a second time, at a place that was no finding — and that is the
expensive part of this run.** Finding 2 was a quantity with two scales. I therefore laid
T5 against all 310 addresses, just as version 5 laid T45 against all 310, and found **69
addresses without a scale class**. Among them the 32 pressure and counter-pressure
fields, and those are literally finding 2 over again: `druck` arises from the fund's
lobby budget (US cents), `gegendruck` from a sector's damage (thousand USD), and
`spiel.md` step 3 offsets the two against each other. **The difference from the first
time is that it would not have looked like an arithmetic error but like a counter-lobby
that never bites** — that is, like a balance problem that the self-player would have
tried for weeks to calibrate away. The answer is the five new classes in **T5**, the
enumerated assignment in **T49** and the three named transitions in **T50**.

**The three points from „Geprüft und nicht gezählt", because the reviewer addressed them
to this run.**

1. **The cost statement for `B` was too small — the reviewer is right, and it is now
   counted out.** Not „rund zwanzig Operationen, drei Promille" but around 240, of which
   71 are `i128` divisions, so a good three percent of a world step. Brought up to date
   in **T44**, in **T47** (with the count per part) and in **section 10**. It was one
   line and not a run, as the reviewer wrote; the counting nevertheless produced two
   prescriptions that save computing time and at the same time honour a promise — the
   shortcut at `stufen(p) = 0` and computing the twelve `korbwert` once per call.
2. **`markt.wert` with origin `Manifest` despite being mentioned in the design table.**
   The precedence rule from T45 resolves it, the reviewer let it drop, the game designer
   took over the resolution. No change.
3. **`einfluss` as 0…100 in `spiel.md`, in ten-thousandths in memory.** Stays as it is,
   and since this version additionally stands in T49 as class 4 — the convention is thus
   no longer explained only in a paragraph, but counted out in a table.

**What I did not decide, because it is not my role:** the reviewer's report to the
project manager that the return counter stands at 3 of 3 with round 6 and that the table
in the work package has not been brought up to date since round 3. I neither write into
the work package nor judge on `blockiert`. What I can contribute is the state of
affairs: finding 2 of this round was a scale mixture that was fatal for class 2 of
measure 2, so not an accuracy finding; it is fixed, and the error type is closed with
T48, T49 and T50 at three places instead of one.

**What this version did not change:** R stays 24, the 310 addresses stay 310, the origin
decomposition stays `136 + 150 + 11 + 2 + 11`, the target mask 175 of 310, the result
bands, the four measures and their thresholds, the three measures cost 11,519,040 world
steps and the night run 11,783,264. I recalculated every sum of this document in this
run — including the ones I did not touch, because a version in which the cost
calculation goes untouched is exactly the one in which it gets left undone. Newly
recalculated are the scale decomposition (`3 + 71 + 36 + 22 + 22 + 5 + 5 + 25 + 32 + 4 +
83 + 2 = 310`, per country `6 + 5 + 4 + 1 + 7 + 1 + 2 + 8 + 1 + 9 = 44`), the operation
count of `fondsvermoegen` (230) and the lower bound `aufschlag_min` (51 bp).

## 16. Befundabarbeitung — Prüfung zu Paket `0011-stack-auf-cpp`, Runde 1 vom 2026-09-03

Three findings, all in this file, all **fixed**. No dissent, no „anders gelöst": the
reviewer is right in all three cases, and in all three the error was the same — in
translating from Rust to C++, a promise was carried along from the way of building, though it
did not hang on it at all. What the reviewer expressly does not carry as a finding has not
been touched.

**Finding 1, the replacement for `overflow-checks` does not reach the bare multiplication —
fixed.** Measure 4 has received a third point: every multiplication of two `i64` without a
following division runs through `mal(a, b)` in `festkomma.hpp`, that is, through `__int128`
and the guard from 4.1. The measure's enumeration has at the same time been switched from
place to **kind of arithmetic** — narrowing, addition and subtraction, multiplication without
division — because an enumeration by places becomes incomplete again with the next addition,
and exactly that had happened. Two things that did not stand in the finding and belong with
it: I did not take `__builtin_mul_overflow` and say in T7 why (one abort path instead of
two); and the proof is a mapping instead of a list, executed once in this run —
`grep -rn ' \* ' kern/src kern/include` gives 52 lines today in four permitted kinds, none
of them an `i64` quantity multiplication, because `kern::werte` is not yet built.

**Finding 2, `cargo vendor` is struck rather than recast — fixed.** T3 has received the
successor: source code of every third-party library under `fremd/<name>/`, version and
commit id in the ADR, integration via `add_subdirectory`; `find_package()`, `FetchContent`,
`ExternalProject` and `pkg_check_modules` are forbidden. T1 names the prescription at the
place of the old sentence and points to T3, so that the translated promise has both halves
there again. The reviewer's remark that `find_package` **downloads nothing** and therefore
passes T23 by, I have written into the prescription itself — it is the reason why a ban on
downloading is not enough here.

**Finding 3, the enforcement of T2 reads only `kern/CMakeLists.txt` — fixed, in both
places.** T13 forbids `link_libraries()` across the whole venture and binds
`target_link_libraries(<ziel> …)` to the `CMakeLists.txt` of the directory in which `<ziel>`
is created — the twin form of the ban on `include_directories()` already standing there, as
the reviewer sketched it. T2 has received a **third** pattern match, which runs over all
remaining `CMakeLists.txt` and searches for `link_libraries(` and
`target_link_libraries(kern`; without it the ban would be an agreement. The two belong
together: T13 says what must not be, T2 says how one sees it.

**Checked against today's tree, not merely asserted.** The three new bans are no retroactive
condemnation of what has been built:
`grep -rnE 'link_libraries|include_directories|find_package|FetchContent' --include=CMakeLists.txt .`
gives **six** lines across the whole venture — four `target_include_directories` and two
`target_link_libraries(${name} PRIVATE …)`
for test targets, each in the file in which its target is created. No hit on
`link_libraries(`, `include_directories(` or `find_package(`. Packages 0004 and 0031 have
therefore already built this way; this version writes down what until now was habit.

**Two messages to the project manager, because they lie outside my directory and I change
nothing there.** First: `festkomma.hpp` has no `mal(a, b)` today — it is the single line of
code that this rework entails, and it belongs in its own small package together with a test
for the abort case. Second: the acceptance of package 0004, condition 3, spells out the two
pattern matches over `kern/CMakeLists.txt` verbatim and therefore does not know the third.
The reviewer saw this and said expressly that the gap belongs closed in the prescription;
here it is closed. Whether 0004 is brought up to date is not the architect's decision.

**What this rework has not changed:** not a word on the stack table, on T6, T6b, T2b, T9,
measures 1 to 3, the 310 addresses, the formulas, the Maße or the cost calculations. The
scope is one point in T7, one paragraph in T3 with a half-sentence in T1, and one paragraph
each in T2 and T13 — that is the return and not an eighth version.

## 17. Paket `0026-klasse-2-preisbasis` — Umfang, und was ausdrücklich liegen bleibt

**This package is delivered.** Two runs on 2026-09-04, commits `77a84e8` and `d26eb3e`.
A third run on the same day got it assigned again because `status: offen` stands in the
package; it decided nothing anew but recomputed — below under "Third run".
**Whoever finds 0026 scheduled again reads this section first.**

**No return.** The package carries `Rückläufe: 0`, and under
`ventures/0016-…/befunde/` lies no check of this trade with `urteil: zurueck`. So there is
no finding to work off; this section records the scope instead, because condition 5 of the
acceptance bounds it.

**Two runs, one package.** The first run (2026-09-04 05:24, commit `77a84e8`) delivered the
decision; the second (2026-09-04, the same day) recomputed it and corrected three numbers.
The reason for the second run does not lie with the trade: after delivery the package still
stood on `status: offen` and was therefore scheduled again
(`rueckstand.md`, „Was der Geschäftsführer entscheiden lassen muss", point 2 — the missing
sentence „Setze `status: gebaut`" in the role file `architekt`). **What the second run
changed in substance stands below under "Corrected"; the decision itself is unchanged.**

**Six places are touched and no others.** The list is counted against the hunks of
`git show 77a84e8 -- specs/0016-…/technik.md` and not written from memory — a statement of
scope that does not cover its own diff misses exactly the condition it is meant to prove:

1. the class-2 row in **T5** together with the two paragraphs behind it (base year 2015,
   reference to T53),
2. the new prescription **T53** behind T50,
3. the paragraph in **T8** that justifies the enumeration of the re-based quantities,
4. this section,
5. the **preamble** before section 1: „T1 bis T52" becomes „T1 bis T53"; the sentence about
   the letter numbers named T53 as its example of a still-free number and now names T60,
   because T53 is taken; one paragraph places T53. This place is **forced**, not chosen: a
   preamble that lets the prescriptions end at T52 contradicts the prescription that stands
   four sections further on,
6. the **frontmatter**: the line `fassung`, because it otherwise states the file's version
   wrongly, and the new key `preisbasis`, because the header lines carry the load-bearing
   determinations and since T53 the price basis is one of them.

**Corrected in the second run, without touching the decision:** The first run did not list
places 5 and 6 and wrote „vier Stellen und sonst keine" over a list of six. In addition, two
numbers in T53 that were truncated instead of rounded and thereby violated the only rounding
rule of this document (T6): the error at the right edge is 3,577.80 and now stands as
**3,578** instead of 3,577, and `r(2021) = 11.549/7.417 = 1,55710` now stands as **1.5571**
instead of 1.5570. The headline value **2,203** (exactly 2,202.98) was rounded correctly and
is unchanged; the argument hangs on neither of the two corrected numbers — the threshold
lies at 2,000 and the headline value above it. All numbers from T53 were computed afresh in
the second run — the 25 support points of the index, the MAPE, the start factor
10,000/7,417 = 1.34825, the two `durchgriff` cases (7,288 → 7,837 and 5,464 → 6,189), the
sum 15 + 15 + 40 + 1 = 71 and the `i64` headroom (2.8 · 10^17 against 9.2 · 10^18) — and
they reproduce except for the two places named.

**Third run, 2026-09-04 — recomputed rather than decided anew.** The 25 support points of
the index table in T53 have been computed a second time through
`10.000 · |7.417 − Index(t)| / Index(t)`, without looking at the second run's intermediate
values: sum **55,074.54** ten-thousandths, mean **2,202.98** → 2,203, right edge 2021
**3,577.80** → 3,578, `r(2021) = 11.549/7.417 = 1,557098`, start factor
`10.000/7.417 = 1,348254`. The two `durchgriff` cases reproduce via `H/N` as **7,836.99** →
7,837 and **6,189.15** → 6,189, the sum as `15 + 15 + 40 + 1 = 71`, the `i64` headroom as
2.8 · 10^17 against 9.2 · 10^18. **All numbers from T53 have thus been computed in two
independent runs**, and none has changed.

**What the third run found nonetheless — one place, and it sits at the transition to
`reihen.toml`.** T53 named only series 1 for `N`; per T23 point 1 the value added is
series 1 **times** the sector share from series 2. `daten/reihen.toml` carries at series 16,
the other way round, `abgeleitet aus Reihe 14 (H) und Reihe 2 (N)` and does not name
series 1. Two documents thus gave two different and both incomplete answers to the same
question, and the question is exactly the one the price basis hangs on. T53 now names both
series and says which of them carries the price basis; the counterpart belongs in the
transfer from message 2. The paragraph's argument does not change — series 2 carries no
price basis.

**State of the three messages on 2026-09-04, looked up rather than presumed.** Message 1
has arrived: `0002` stands on `status: offen` again and carries `haengt_an: [0008, 0026]`;
0008 is `fertig`. Message 2 has arrived **half**: the next architect package on the series
list has been created as `0068`, **but the series-list row 20 and the transfer to
`daten/reihen.toml` have not** — a search over all package files for „Reihe 20",
„Ausfuhrpreisindex" and „Deflator" finds nothing besides 0025 and 0026 themselves. As long
as that stays so, `reihen.toml` continues to carry, at series 14, the contradiction that
T53 resolved, and at series 16 the incomplete origin from above. Message 3 (the readable
PWT excerpt) is still open.

Not touched: T42, T37, T47, T48, T50, T23, the series list, the 310 addresses, the four
Maße, the cost calculations and the stack table. The third run touched none of them; it
worked inside the six places enumerated above (T53, this section, the line `fassung`) and
opened no seventh.

**What belonged here and still does not stand here — the series list.** T53 names a new
series of the vintage, and the series list in section 7 does not carry it. That is
deliberate: condition 5 expressly takes the open questions from `rueckstand.md` points 6
and 7 out of this package, and one of them — the `frei` in the column "Role" — sits in
exactly this table. Two packages on one table are the collision case the scoping is meant
to avoid. **The row therefore stands here, ready for the next architect package:**

| Nr | Quantity | Dimension | Model unit | Source | Role | Suspect |
|---:|---|---|---|---|---|---|
| 20 | Export price index of the world, from `NE.EXP.GNFS.CD` and `NE.EXP.GNFS.KD` | 1 | ten-thousandths, 2015 = 10,000 | WDI | conversion of the vintage per T53, **no target** | no |

It does **not** change the sentences under the table: the 31 target series remain rows 1,
2, 8, 9, 10 and 11, the trade block remains a block of its own, and the four quantities
without a data anchor remain rows 17, 18, 19 and the financial-market regulation. Series 20
is a conversion quantity, not a checked one.

**Three messages, because they lie outside my directory.**

1. **To the project manager, on package 0002 (`kern::werte`, fund valuation):** Its
   unblocking sentence demanded *„eine Entscheidung des Architekten zur Klasse-2-Frage,
   schriftlich in `technik.md` oder in einem ADR"*. It stands in T53. **T47, T48 and T50
   are untouched** — scope and acceptance of 0002 need no change; it can go back to `offen`
   unchanged. Via 0002, 0010 (state output) hangs on this too.
2. **To the project manager, two new packages:** the series-list row 20 above (architect,
   together with `rueckstand.md` points 6 and 7, because same table) and the transfer to
   `daten/reihen.toml` (data builder): series 14 gets the deflator step and loses the entry
   in the field `offen` that carries the contradiction; series 16 gets the answer that `H`
   and `N` carry the same price basis per T53; series 20 is added. Series 3 stays
   `art = "ungemessen"`.
3. **To the data builder, and through them to the operator:** unit and base year of the
   PWT capital stock remain unmeasured, and the lock is the toolchain — four PDF retrievals
   from three directories arrived unreadable. It costs **one** readable excerpt from
   Dataverse 554025 or 554105. The consequence is ordered by size in T53: the unit is the
   heavy part (factor 1 against 1,000), the base year the light one, and neither touches a
   target series.

**What this package expressly did not decide.** The size of the damage in counterforce 5
belongs to `spiel.md` and to package 0021. Whether series 1 switches to PWT is carried in
`daten/reihen.toml` as `quellenwahl = "offen"` and stays so; if it switches, the measured
base year moves with it, and T53 is the place where that would have to be brought up to
date. And the residual quantity of the chosen way — the distance between the world export
index and the true bilateral deflators of the 40 flows — is unmeasured and stands in T53
as such.

## 18. Paket `0043-t48-groessen-gegenkraft-5` — Umfang und die Meldung an den Projektmanager

Four conditions, four places. Changed are **T48** (five quantities, the sector-wise form
of number 11, the remainder table), **T50** (the sentence left open is closed),
**section 10** (the cost line with its read table) and **section 12 point 3** (the gap is
one no longer). Plus the line `abgeleitet:` in the frontmatter, which named 17.

**The brief spoke of five names, meant as of 2026-09-03 — there are six, and one of them
is older than the package.** The brief's text names `hub`, `preishub`, `menge`,
`verschiebung` and `schaden`. In between, package **0039** ran: `preishub(l, s)` no longer
exists; `keilhub(l, s)` and `preishub_zoll(l, s)` have taken its place. Five names thereby
became six, of which two did not become quantities (`menge`, `verschiebung`, reasoning in
T48) and four did. The fifth newcomer, `weltpreis_mit_zoll`, comes from neither of the two
packages but from T28 of this document: the price formula of the market clearing has
computed with it all along; formed it never was. What found it was not the reading of the
brief's table but the collection over `spiel.md` that T48 now prints alongside — the brief
would not have surfaced it.

**The acceptance conditions, one by one:**

1. **The name list leaves no remainder.** The collection, its assignment and the twelve
   permitted remainders stand in T48. Two names in it are the awkward case and are
   therefore listed explicitly: `wmz` and `preishub` still stand in `spiel.md`, but only
   in the counterexample with which the design demonstrates the discarded former version.
   Whoever takes them for prescriptions carries two dead quantities forward; whoever
   passes over them silently leaves the next reviewer the same doubt. They therefore
   stand in the remainder table.
   **The collection has, in passing, found an older gap** that belongs to none of the
   three packages: `stufen(p)` has stood in the formulas of numbers 14 and 15 since
   version 5 without T48 ever saying what it is. It is an address in function notation
   and now stands as such in the remainder table — evidence that the mechanical
   collection finds what the reading of a brief's table does not.
2. **`handelsvolumen`** stands as number 11 in the sector-wise form, the one-argument one
   next to it as its sum over s ∈ {1, 2}. Number 4 (`waehrungswert`) continues to read
   the one-argument form and does not change.
3. **T50 and section 12 point 3** point to the section in `spiel.md`. The old sentence
   stands next to it verbatim in both places, so that the checks that quoted it remain
   quotable.
4. **The cost line** names 106 read accesses, 16 write accesses and 16 calls, with the
   read table beneath it and the sum written out. I recounted it in this run instead of
   copying it; the one line that is not self-explanatory is the 40 of the trade block,
   and why they are not 64 stands there.

**To the project manager — which of the new quantities needs an interface in
`kern::werte`.** This is the statement from which the follow-up package is cut; it is not
mine.

| Quantity | Interface in `kern::werte`? |
|---|---|
| `hub(l, i)` (no. 18) | **yes**, public. Arguments country and instrument, result `i64` |
| `keilhub(l, s)` (no. 19) | **yes**, public |
| `preishub_zoll(l, s)` (no. 20) | **yes**, public |
| `weltpreis_mit_zoll(g, s)` (no. 21) | **yes**, public — and its reader is the market clearing (T28), not counterforce 5 |
| `schaden(l, i)` (no. 22) | **yes**, public, with the case distinction over the four instruments inside |
| `handelsvolumen(l, s)` (no. 11) | **change of form to an existing one.** Today `werte.hpp` has `handelsvolumen(z, land)`; both arities are needed, the one-argument formed from the two-argument |
| `menge(l, i)`, `verschiebung(l, i)` | **no**, and that is a prescription, not an oversight. Reasoning in T48 |
| `regulierung_last` | **no** — parameter key per T27. It belongs in `parameter.toml` (data builder) and in the struct `Konstanten` in `werte.hpp`, where `gegenlobby_satz` and `lobbykosten` already stand |

**Three places that follow from this, and none of them is mine.** All three are
mechanical and none is a question:

1. **`kern/include/kern/werte.hpp` says „siebzehn" in three places** — in the header line
   (`//! kern::werte -- die siebzehn abgeleiteten Groessen aus T48`), in the paragraph on
   the mechanical proof („Unten stehen siebzehn") and in the heading of the second block.
   After this package it is twenty-two. That is core-builder work, and it is exactly the
   proof T48 prescribes: whoever lays the header against the table finds the five missing
   declarations. **As long as they are missing, the proof is not fulfilled** — the header
   is thereby incomplete today, and not wrong.
2. **The acceptance of package 0002** names the number seventeen verbatim. It was right
   at the time it was fulfilled: 0002 stood on `fertig` on 2026-09-04, before this
   package ran — the sequence the project manager ordered for that purpose has held.
   Whoever reads it later needs this paragraph, otherwise the fulfilled acceptance looks
   like a violated one.
3. **`regulierung_last` is missing from `parameter.toml`.** Follow-up package of the data
   builder, already named in this package's brief and not touched here.

**Where I am unsure, and it stands here rather than only in the logbook.** Number 21 is
the only place where I decided something instead of reporting it: `zollstand(RW) = 0`.
The way there is documented — ten `durchgriff` values for five territories, no
instruments for the rest of world —, but the domain of `weltpreis_mit_zoll` is written
out nowhere, neither in T28 nor in `spiel.md`; I read it out of the word „je Gebiet" and
out of the number ten. If the market clearing in truth runs only over the four playable
countries, my line is superfluous and not wrong. This is the place where I would follow a
reviewer without objection.

## 19. Die Länderzahl als Parameter — Paket `0116`

**What is decided here and what is not.** This section decides **nothing** about the number
of countries. `L = 4` stays, and the reasoning for it is in `spiel.md`; it is not up for
debate. All that is decided is whether a further country is later a **procedure with known
steps** or a rebuild with an open end. Three things belong to that: the formula behind every
number written out today (T54, T55), the question of where a country's identity lives (T56),
and the list of what does **not** grow along (T57).

**The core is further along here than this document.** `LAENDER`, `GEBIETE`,
`SEKTOREN`, `INSTRUMENTE` and `SEKTOREN_HANDELBAR` are each a `constexpr` in
`kern/include/kern/zustand.hpp`; the block starts are **computed** from them
(`BASIS_RESTWELT = LAENDER * LAND_FELDER`) and held against the group table in T15 by a
chain of `static_assert`. `daten/reihen.toml`, too, carries a `dimension` per series and
writes it as `"4 + RW"`, that is, as a quantity and not as a constant. What is missing is the
opposite direction: in `specs/` the derived numbers stand as **literals**, and nowhere does
one place state which formula yields which. Whoever adds a country must today recompute them
one by one and pull the prose along. That is exactly what T55 fixes.

### T54 — Three shape quantities, and everything else follows from them

| Symbol | Meaning | today | Constant in the core |
|---|---|---:|---|
| `L` | playable countries | 4 | `LAENDER` |
| `S` | sectors | 3 | `SEKTOREN` |
| `I` | policy instruments | 4 | `INSTRUMENTE` |

Two further quantities are **derived and not a choice of their own**: the number of
territories is `L + 1` — the rest of world is always exactly one, however many countries are
modelled —, and the number of tradable sectors appears in the formulas below as `S − 1`.

**A warning belongs with `S − 1`, and it is not a formality.** The core carries
`SEKTOREN_HANDELBAR` as a constant of its **own**, not as an arithmetic expression. That at
`S = 3` it has the same value as `S − 1` is a fact about today's sector list and not a rule:
whoever introduces a fourth sector decides its tradability themselves and then puts the
constant where `S − 1` stands here. **For the number of countries, which is what this
section is about, the difference has no consequence** — the number of tradable sectors does
not depend on `L`.

### T55 — The derivation chain

Every row names its reference in this document, so that the formula can be laid against the
place that writes the number out today.

| Quantity | Formula in `L`, `S`, `I` | `L=4` | `L=9` | Reference |
|---|---|---:|---:|---|
| Fields per playable country | `4S + 4I + 16` | 44 | 44 | T15 |
| Fields of the rest of world | `4S + 10` | 22 | 22 | T15 |
| Territory block together | `L(4S+4I+16) + 4S + 10` | 198 | 418 | T15, T17b |
| Trade flows | `(L+1)·L·(S−1)` | **40** | 180 | T15, „Handel" |
| World prices | `S − 1` | 2 | 2 | T15 |
| Imitator counters | `L·S` | 12 | 27 | T15 |
| Position slots | `L·(S+2)` | **20** | 45 | T16 |
| Stakes | `2·L·S` | 24 | 54 | T15, action 2 |
| remainder untouched by `L` | `5S + 23` | 38 | 38 | T57 |
| **State total** | `L(4S+4I+16) + (L+1)L(S−1) + L(S+2) + 3LS + 5S + 23` | **310** | **740** | T15 |
| Target mask `weltlauf`, per country | `4S + I + 11` | 27 | 27 | T38 |
| **Target mask `weltlauf`** | `L(4S+I+11) + (4S+10) + (L+1)L(S−1) + (S−1) + 3` | **175** | 450 | T38 |
| **outside the target mask** | `L(3I+5) + L(S+2) + 3LS + 11` | **135** | 290 | T38 |
| Target series | `L·(S+4) − 1` | **27** | 62 | series list for T23, `reihen.toml` |

**Recomputation in prose, every number substituted by hand once.** Per country
`4·3 + 4·4 + 16 = 44`, rest of world `4·3 + 10 = 22`, together `4·44 + 22 = 198`. Trade
`5·4·2 = 40`, world prices `2`, imitators `4·3 = 12`, market basket `2` — the world thus `56`.
Slots `4·5 = 20`, stakes `2·4·3 = 24`, fund aggregate and excess return `5 + 3 = 8`
— the fund thus `52`. Game `4`. Sum `198 + 56 + 52 + 4 = 310`, the same decomposition as in
T15. Target mask `4·27 + 22 + 40 + 2 + 3 = 175`, outside `4·17 + 20 + 24 + 12 + 11 = 135`,
and both together again the address count from T15. Target series `4·7 − 1 = 27`.

**Why the `L = 9` column stands alongside, although this section changes no country count.**
It is not a stipulation but the only test that proves anything. Today `L = I = 4` holds
— and therefore every confusion of `L` and `I` is **invisible** at today's values:
`4S + 4I + 16` and `4S + 4L + 16` both yield 44. Only at `L ≠ I` do the two formulas come
apart. The column's values are laid against an **independently** produced calculation that
the operator wrote down on 2026-09-05 in package `0118-fuenf-weitere-laender-auswaehlen`:
country block 396, trade 180, imitators 27, slots 45, stakes 54, fixed remainder
38, state 740, target series 62. All eight numbers agree with the formulas. That is the
counter-calculation that a number computed only once does not have.

**Two pairs of numbers look the same at `L = 4` and are not.** Both are exactly the
kind of trap this table is written against:

- **40 against 40.** The 40 trade flows grow with `(L+1)·L·(S−1)`; the **40
  halving steps** of the market clearing from T28 are a precision prescription and grow with
  nothing at all. Whoever takes the two for the same quantity turns a country change into a
  change to the solution procedure.
- **27 against 27.** The 27 target series grow with `L(S+4) − 1`, the 27 mask addresses per
  country from T38 with `4S + I + 11` — that is, not with `L` at all. At `L = 9` it is 62
  against an unchanged 27. **Read the first formula in `L_R`, not in `L`** (T59 switches
  exactly three rows of this table, and this is one of them): under the nine countries of
  `spiel.md` it is `L_R = 7`, hence 48 target series, again against an unchanged 27.

**Where the 27 target series come from, and why the series list says 31.** The count is taken
against `daten/reihen.toml`, as of 2026-09-05: `sollreihen_gesamt = 27`, split across series 1
(GDP, `L`), series 2 (sector shares, `L·S`), series 8 (consumer prices, `L`), series 10
(exchange rate, `L − 1`, because the US dollar is the numéraire) and series 11 (government
debt ratio, `L`). That yields `L(S+4) − 1`. The prose below the series list in section 7 still
says 31 and counts series 9 (policy rate) with four target series; the series lost its target
role in package `0054` (`sollreihen = 0`, empty `t37_klasse`), and the prose has not been
pulled along. **That is no contradiction to this formula but the open work of package
`0068-technikmd-reihe-9-ohne-sollrolle`**, which stands behind this package in the same file.
I do not touch the passage; it belongs to that package. **Addition of 2026-09-08, package
`0221`:** the passage now carries the two counts beside each other — 31 reported,
`L_R(S+4) − n` = 27 target series — because the same passage had to be read in `L_R` for
the country count. The repair 0068 owes is the **wording** of row 9 and of the sentence
below the series list, and it is untouched.

### T56 — The identity of a country remains a named enumeration

**Chosen is the first of the two possibilities: `Gebiet` and `Steckplatz` remain
named enumerations.** They are **not** replaced by a bare index plus abbreviation table.
The one place where a country is entered is
**`kern/include/kern/zustand.hpp`**.

Four reasons, measured on 2026-09-05 and not presumed:

1. **The enumeration already *is* the index.** `enum class Gebiet : std::uint8_t` carries the
   values 0 to 4, the address arithmetic computes exclusively with `LAENDER` and `GEBIETE`,
   and the abbreviation table already exists — twice, see the end of this section:
   `GEBIET_KUERZEL` in `kern/src/zustand.cpp` and a second one of the same name in
   `kern/src/zustandsausgabe.cpp`. So
   there are not two procedures to choose between, but one index **with** a naming layer
   against the same index **without** it. The rebuild would put no calculation right that is
   wrong today.
2. **A wrong index is a valid value, a wrong name is not.** `Steckplatz{37}`
   compiles; `Steckplatz::Anleihe_BX` does not. This venture catches its errors mechanically
   — `static_assert` on the block boundaries, target mask per round, bitfield against the
   second write access. Trading a compile-time check for a run-time one runs against this
   way of building.
3. **The names carry the tests.** Counted in `kern/`: `Gebiet::<Kürzel>` stands on 42 lines
   of source (`werte.cpp` 25, `schritt.cpp` 6, `schreiber.cpp` 5, `zustand.cpp` 5,
   `zustandsausgabe.hpp` 1) and on **141** lines in the tests (`werte_probe.cpp` 109,
   `schreiber_probe.cpp` 22, `zustand_probe.cpp` 9, `zustandsausgabe_probe.cpp` 1). The
   weight lies with the tests, and there the name is the statement: `Gebiet::DE` says what is
   being checked, `Gebiet{2}` does not. A rebuild would replace 183 readable lines with 183
   that require a lookup, without moving a single number.
4. **T17 makes the address part of the interface version.** `fonds.position.CN.1`
   and `handel.DE.CN.1` carry the abbreviation in their text. A country's identity is thus
   named already anyway; an enumeration whose names follow the addresses is the rendering of
   the same thing that the compiler can check.

**The price of this choice, written out because it is real.** At `L = 5`,
`enum class Steckplatz` gains five further values (`Sektor_XX_1` to `_3`, `Waehrung_XX`,
`Anleihe_XX`), and because the slots are grouped by kind, the ordinal values of the currency
and bond slots shift. That is manual work, and manual work drifts.

**Against that stands the rule that makes this choice viable in the first place: the formula
guards the enumeration.** In `zustand.hpp`, one `static_assert` against T55 belongs next to
each affected constant — `STECKPLAETZE == LAENDER * (SEKTOREN + 2)`,
`LAND_FELDER == 4 * SEKTOREN + 4 * INSTRUMENTE + 16`, `RESTWELT_FELDER == 4 * SEKTOREN + 10`,
and `STECKPLATZ_WAEHRUNG_ERSTER` as well as `STECKPLATZ_ANLEIHE_ERSTER` against
`LAENDER * SEKTOREN` and `LAENDER * (SEKTOREN + 1)` respectively. A forgotten entry then
breaks compilation instead of silently shifting an address. **Without these assertions the
choice would be wrong** — they are the reason a hand-kept list remains admissible here.

**For "the one place" to hold literally, two files must become one — the list stands twice
today.** `GEBIET_KUERZEL` sits in `kern/src/zustand.cpp` for address building; a **second
version of the same name with the same content** sits in `kern/src/zustandsausgabe.cpp`,
whose comment there calls itself „Zweite Fassung derselben Liste" and names the reason: the
first one is private and belongs to a foreign translation unit. A sixth region therefore
needs an abbreviation in **both**. Nothing binds the two at translation time — both are
declared with their size given as `GEBIETE`. What binds them is `zustandsausgabe_probe` at
**run time**: it reads each region's abbreviation out of that region's own trade address
(`handel.<von>.<nach>.<sektor>`) through `index_zu_adresse` and goes red as soon as one of
the two lists is re-sorted. A missing sixth abbreviation is caught no earlier than there.

**The table belongs next to the enumeration in the header, and then there is one of it.**
With `GEBIET_KUERZEL` in `kern/include/kern/zustand.hpp` the reason for the copy — private,
foreign file — falls away, and `zustandsausgabe.cpp` uses that table instead of repeating
it. That is the way chosen here: consolidate, not keep twice. Whoever keeps the second
version instead owes the country procedure an explicit second step, with the run-time probe
as its only cover.

**The assertion bites only with a derived size.** The form is
`constexpr std::array GEBIET_KUERZEL = {…}` — class template argument deduction, no size in
the type — with `static_assert(GEBIET_KUERZEL.size() == GEBIETE)` beside it. **Give the size
instead, and the same line compares `GEBIETE` with `GEBIETE`: true by construction, unable
to fail however few initialisers stand in the braces, and the sixth entry is
value-initialised to a null pointer.** That is how one builds the very error it is meant to
catch — `GEBIETE = 6`, `LAENDER = 5`, both abbreviation tables untouched. Derived, `.size()`
is 5 against `GEBIETE` 6 and the build stops. (Whether the warning set flags the short
initialiser list is not measured; the choice does not rest on it.)

After that, the complete procedure for a further country in the core is: one value in
`Gebiet` before `RW`, `RW` one higher, `LAENDER` one higher, one abbreviation in
`GEBIET_KUERZEL`, `S + 2` values in `Steckplatz` — all in one file, all guarded by
`static_assert`. **That sentence is the target, not today's state: it holds from the moment
the second version is gone.** The data work that falls due alongside is in
`0141-pruefliste-fuenftes-land` and is the larger item.

Three things — the assertions, the move, and the removal of the second version — are
**design, not execution**, and each needs a core-builder package. I write no code.

### T57 — What stays the same at `L = 5`

Of the state addresses, **38 are untouched by `L`** (`5S + 23`, at `S = 3` thus 38) — and
that is the same number that package `0118` independently lists as „fest":

| stays the same | number | why |
|---|---:|---|
| rest-of-world block | `4S + 10` = 22 | The rest of world is by definition **one**: the world minus the model countries. A further country shrinks its content, not its address count |
| fund aggregate | 5 | cash, leverage level, visibility, investor holdings, market share are properties of the fund, not of the map |
| excess return | 3 | three rounds of memory, tied to the death condition |
| market basket | 2 | one basket, one value, one return — independent of what it is formed over |
| world prices | `S − 1` = 2 | one per tradable sector, not per country |
| game | 4 | round, vintage id, parameter-set checksum, mandate level |

Outside the state, likewise unchanged — and here lies the actual point:
**the ways of dying**, the **three actions per round**, the **game length `R`**, the thirteen
scale classes from T5, the five origin kinds from T45, the 40 halving steps from T28 and
the four Maße from `agentenbau.md`. They are tied to game balance, scale order or measurement
procedure — nowhere to the country geometry. One more country is no event for them.

**A correction belongs here, and it concerns the slots.** The brief for
`0116` lists the twenty slots under what does *not* grow along. By T15 and T16 they are
`L·(S+2)` — `L·S` country×sector, `L` currency, `L` bond —, that is, **geometric and
growing**; and on 2026-09-05 in `0118` the operator explicitly chose „Weg A": the
slots grow with `L`, at `L = 9` to 45. Both statements are from the same day; the
younger one prevails. **What truly does not grow along at the slots is the number of actions
per round** — and exactly from that arises the question of decision density that `0118` has
to answer. The address count is geometry, the scarcity is balance; this section
separates the two and decides only the first.

The same thing in halves: **the fund block grows along by half.** Of its 52 addresses, 8 are
`L`-free (aggregate 5, excess return 3), 44 are geometry (slots `L(S+2)`, stakes
`2LS`). "The fund block does not grow" would be right for the smaller half and wrong for the
larger.

### What this section has not touched

Nothing. It is **exclusively descriptive**: it carries no number into an existing
section, changes no table, no `static_assert` and no line of source. The
formulas are laid against the existing places and agree with them; the one
deviation — 27 against 31 for the target series — is named above and belongs to package
`0068`. The number of countries itself, the selection of a further country and the rebuild of
the core are packages of their own and not decided here.

## 20. Zwei Länderklassen und der geschätzte Politikpfad — Paket `0117`

**What is decided here and what is not.** This section selects **no** country, searches for
**no** interest-rate series, changes **no** line of the core and does not touch today's four
countries. Three things are decided: what the two classes are and how the exemption from the
check subjects can be held **mechanically** (T58); how the sixteen check subjects are to be
counted parametrically (T59); and in what order a missing policy path is to be replaced,
together with the marking that keeps an estimate recognisable as an estimate (T60,
T61).

**The occasion stands in the data, not in the future.** `daten/reihen.toml` carries series 9
(policy rate) with `deckung_urteil = "reisst -- DEU und CHN tragen in dieser Quelle keinen
einzigen Wert, USA endet 2020"`. The question of the estimated policy path is thus no
provision for a future fifth country but an open question about two of today's four — and
exactly for that reason it needs a rule that is not decided case by case.

### T58 — The two classes, and what "exempt" means mechanically

| Class | policy path | data series | in the `weltlauf` | in the check subjects |
|---|---|---|---|---|
| **Backtest country** | from a measured or derived source (T60 stage 1–3) | all from a measured source | runs, inside the target mask | **yes** — GDP, sector structure, prices, exchange rate count |
| **Play-only country** | may be estimated (T60 stage 4) | for the `spielmodus`, not for the backtest | **shut down**, entirely outside the target mask | **no** — none of its quantities enters an error measure |

**Today's four countries — USA, China, Germany, Brazil — are backtest countries**,
all four, and this section changes nothing about that. Their sixteen check subjects per T37
remain what they are.

**Why the mere exemption from the error measures does not suffice — that is the one finding
of this section.** The brief describes the exemption as a property of the *evaluation*: the
play-only country's GDP enters no error measure. That is not enough. The model is coupled:
step 4 computes GDP, prices and exchange rate from the policy path, the market clearing forms
world prices from them, and the world prices stand in the GDP of **every other territory**. A
play-only country that computes along endogenously with an invented policy rate thereby
shifts the GDP of Germany — a check subject — without ever being measured itself. `spiel.md`
already has the sentence for it:
*„Ein Lauf mit erfundener Politik prüfte nur die halbe Maschine."* The exemption must
therefore sit in the **run**, not in the evaluation.

Three ways, measured against this venture's criteria:

| | **A shutdown** (chosen) | **B exogenous guidance** | **C mere masking** |
|---|---|---|---|
| What the play-only country does in the `weltlauf` | nothing; its addresses lie outside the target mask | it runs along, but each of its quantities comes from measured data every round | it computes endogenously with the estimated path |
| Does the estimated path act on a check subject? | no | no, as long as **every** one of its remaining series is measured | **yes**, via trade and world prices |
| What proves it? | two-sided mask check per round (T38) and a poison test | looked up series by series, anew per vintage | not at all |
| Data cost per play-only country | start values and the estimated path, both only for the `spielmodus` | support points for GDP, sector shares, prices, rate — almost a backtest country | like B |
| Cost at the vintage | the rest-of-world remainder is formed once per mode | once | once |
| stored backtest results | stay valid | expire with every new play-only country | expire likewise |
| what the backtest gains | nothing | one more measured territory in the trade block | nothing |

**A is chosen**, and the reason is the third row: only there is the exemption a check and not
an argument. B is not worse on the merits — it even makes the backtest more
precise — but per play-only country it costs almost the data work of a backtest country and
devalues the stored results of the backtest with every addition, that is, the dearest
good of this venture. C is the way the brief text literally describes, and it
leaks.

**Four stipulations, more than that A does not need:**

1. **One place for the set.** `aktive_gebiete(modus)` returns, in the `spielmodus`, all
   territories; in the `weltlauf`, the backtest countries and the rest of world. **Every**
   loop over territories — market clearing, trade, price transmission, invariant check, state
   output — runs over this one set. A second place where the set is formed is an error of the
   same family as the double concordance from T23 point 9.
2. **Outside the mask, not per Vortrag.** In the `weltlauf` all addresses of a play-only
   country and all trade rows it takes part in lie **outside** the target mask
   from T38. They keep their start value and are not written — the same construction by
   which the fund block is already today not computed in the `weltlauf` instead of being
   caught. The two-sided mask test turns that into a hard error every round: whoever writes
   is found out.
3. **The rest-of-world remainder gets a mode.** T23 point 10 forms the rest of world today as
   "world series minus the four countries" and its trade rows as "total imports and exports
   minus the flows to the three others". With two classes the rule reads: in the `weltlauf`
   minus the **backtest countries**, in the `spielmodus` minus **all policy countries**. The
   rest-of-world block (`4S + 10`, so 22) and the rest-of-world trade rows (`2·L_R·(S−1)`, at
   `L_R = 4` so 16) thus carry two values per vintage, together 38 addresses; the trade rows
   between rest of world and play-only country exist only in the `spielmodus`. **Without this
   second remainder the world of the `weltlauf` shrinks by the mass of the play-only
   country** — `handel.DE.RW.*` would lose the share that today goes there — and the trade
   block is a check subject. The data side would then shift exactly what stipulation 2
   protects on the computation side.
4. **The poison test, because the mask covers only the write side.** "No address outside the
   mask touched" catches the write access; a rule that only **reads** a play-only-country
   address stays invisible. The test bench therefore runs a `weltlauf` twice per vintage: once
   ordinarily, once with all play-only-country addresses at an absurd value (value-range edge
   per T5/T49). **Both runs must be bit-identical in all mask addresses.** If one deviates, a
   rule reads what it may not read. Cost: one additional run over `R`
   world steps per vintage, so nothing against the three self-play measures.

**The change of class is a direction and a procedure.** If the policy path of a play-only
country is later measured (T60 stage 1) or derived without a free parameter (stage 2), it
becomes a backtest country: `L_R` grows by one, the check subjects by four, its series enter
the target mask, and the stored backtest results are rebuilt **once**, because the
rest-of-world remainder changes. The opposite direction — a backtest country becomes a
play-only country — is not a data procedure, see T60.

### T59 — The count, parametric in the number of backtest countries

`L_R` is the number of backtest countries, `L_S` that of the play-only countries, and
`L = L_R + L_S` is the country count from T54. `n` is 1 if the numéraire country (today the
USA) is a backtest country, otherwise 0; today `n = 1`.

| Quantity | Formula | today (`L_R = 4`) | `L_R = 4`, `L_S = 5` | `L_R = 7`, `L_S = 2` | `L_R = 9` | Reference |
|---|---|---:|---:|---:|---:|---|
| GDP per country | `L_R` | 4 | 4 | 7 | 9 | T37, series 1 |
| Sector structure per country | `L_R` | 4 | 4 | 7 | 9 | T37, series 2 |
| Consumer prices per country | `L_R` | 4 | 4 | 7 | 9 | T37, series 8 |
| Exchange rate per country except the numéraire | `L_R − n` | 3 | 3 | 6 | 8 | T37, series 10 |
| Trade block | `1` | 1 | 1 | 1 | 1 | T37, series 14 |
| **Check subjects** | `3·L_R + (L_R − n) + 1` | **16** | **16** | **28** | **36** | T37 |
| Tolerance | `⌊L_R/2⌋` | 2 | 2 | 3 | 4 | T37, Maß 4 |
| Flows in the trade block | `(L_R+1)·L_R·(S−1)` | 40 | 40 | 112 | 180 | series 14, `handelsblock_stroeme` |
| free target series | `L_R(S+3) − n` | 23 | 23 | 41 | 53 | `zaehlregel_t37` |
| derived target series | `L_R` | 4 | 4 | 7 | 9 | series 11 |
| **Target series** | `L_R(S+4) − n` | **27** | **27** | **48** | **62** | T55, `sollreihen_gesamt` |
| reported series (target + `gesetzt`) | `L_R(S+5) − n` | 31 | 31 | 55 | 71 | T37, section 7 series list |
| **Target mask `weltlauf`** | `L_R(4S+I+11) + (4S+10) + (L_R+1)L_R(S−1) + (S−1) + 3` | **175** | **175** | **328** | **450** | T38, T55 |

**Recomputation in running text, every number substituted once by hand.**
Check subjects today `3·4 + (4−1) + 1 = 12 + 3 + 1 = 16`, with seven backtest countries
`3·7 + 6 + 1 = 21 + 6 + 1 = 28`, with nine
`3·9 + 8 + 1 = 27 + 8 + 1 = 36`. Tolerance `⌊4/2⌋ = 2`, `⌊7/2⌋ = 3`, `⌊9/2⌋ = 4`.
Flows `5·4·2 = 40`, `8·7·2 = 112` and `10·9·2 = 180`. Free target series
`4·6 − 1 = 23`, `7·6 − 1 = 41` and `9·6 − 1 = 53`, derived 4, 7 and 9, together
`4·7 − 1 = 27`, `7·7 − 1 = 48` and `9·7 − 1 = 62`. Reported series `4·8 − 1 = 31`,
`7·8 − 1 = 55` and `9·8 − 1 = 71`. Target mask `4·27 + 22 + 40 + 2 + 3 = 175`,
`7·27 + 22 + 112 + 2 + 3 = 328` and `9·27 + 22 + 180 + 2 + 3 = 450`.

**The column `L_R = 7, L_S = 2` is added on 2026-09-08 from package `0221` and is the one
`spiel.md` asks for**, in its follow-up table for the architect: *"The table gains the
column `L_R = 7, L_S = 2` — that is the choice made in this package. Check subjects 28,
free target series 41, target series 48, flows in the trade block 112, target mask
`weltlauf` 328"* (section *Was der Architekt neu rechnen muss*, entry **T59**, read
2026-09-08). All five numbers are recomputed above from the formulas and agree; they are
not copied. **The column is an expectation with a condition and not today's state** —
Japan, India and Chile become backtest countries only if their policy rate is at stage 1
or derivable without a free parameter, decided per T63 step 1 at retrieval. Section 26
carries the horizon; the columns `L_R = 4` and `L_R = 9` stay, they are the edges.

**Two rows are new here and are not from `spiel.md`.** *Tolerance* stood only in T37 and
as a digit, and a table that carries the check-subject count without the tolerance invites
exactly the split reading this package closes. *Reported series* is the row that names 31
as a quantity of its own: 31 is the count of all reported series, 27 that of the target
series, and the two were the same number until the cut of 2026-09-03 struck series 9. Both
rows follow from formulas already standing here, neither adds a decision.

**An additional play-only country leaves every row of this table unchanged**, because `L_S`
appears in no formula — that is the column `L_R = 4, L_S = 5` against the column `today`, row
by row the same number. It changes only when `L_R` changes; that is why the
columns `L_R = 7` and `L_R = 9` stand beside it, in which every row moves that is meant to
move.
The brief text says at one point „Ein Spielland ändert die Zahl, nicht
die Struktur"; the acceptance condition of the same package demands the opposite and is the
sharper statement. The formula decides the point: the count hangs on `L_R`, a play-only
country raises `L`.

**The short form `4·L_R` is right and still must not be the binding one.** At `n = 1`
the `−1` of the numéraire and the `+1` of the trade block cancel, and `16 = 4·4`,
`36 = 4·9`. But the two terms have nothing to do with each other: were one trade block kept
per tradable sector instead of one overall, or were the numéraire country a play-only
country, the cancellation would fall away. Second case, computed through: `L_R = 3` without
the USA would give `3·3 + 3 + 1 = 13`, not 12. That is the same trap as "40 against 40" and
"27 against 27" in T55, only one level up.

**In T55 exactly three rows switch from `L` to `L_R`, and no other.** "Target series" becomes
`L_R(S+4) − n`. "Target mask `weltlauf`" becomes the formula from the table above. "Outside
the target mask" is no longer a formula in one variable but the difference *state total
(in `L`)* minus *target mask (in `L_R`)*. All remaining rows count **geometry** and stay
at `L`: a play-only country occupies its full country block, its trade rows, its
slots, stakes and imitator counters — in the state it is a country like any other.
"Target mask `weltlauf`, per country" also stays untouched, because it is a per-country
quantity and knows no class. At `L_S = 0` all three rows pass over into their present form;
that is the compatibility test.

**The class separation saves checking effort and data, not addresses.** At `L = 9` with five
play-only countries the state stays at the 740 from T55, the mask at 175 — so 565
addresses lie outside instead of the 290 with nine backtest countries. The 275 addresses of
difference decompose into `5 × 27 = 135` mask addresses of the five play-only countries and
`180 − 40 = 140` trade flows, together 275; two ways, the same number. What a country costs
in the state stands in `spiel.md`: 58 fields per policy country plus its trade rows,
independent of the class.

**Two counter-calculations that do not know these formulas.** `spiel.md` counts, for the case
of all 195 countries, „`4 · L` — vier Prüfgegenstände je Rückvergleichsland" and arrives at
780; substituting 195 into the formula above gives `3·195 + 194 + 1 = 780`. And the work
package `0118-fuenf-weitere-laender-auswaehlen` of 2026-09-05 independently puts both class
choices side by side: nine backtest countries would give 62 target series and 36 check
subjects, four plus five play-only countries 27 and 16. All four numbers agree with the
formulas.

**What the count does not contain.** `S` and `I` do not appear in the check-subject formula.
A fourth sector creates no new check subject — it makes the check subject
*sector structure* harder, because per T37 all of the country's share series must pass. A
fifth instrument creates none at all. That is the difference from T55, where `S` and `I`
stand in almost every row, and it is the reason this table is its own and not a
further row in T55.

**Computing time.** The class separation does not make the test bench cheaper. Maß 4 is
**one** run over `R` world steps per vintage, now over `L_R + 1` instead of `L + 1`
territories; the test bench's budget is carried by the self-play measures 1 to 3, and those
run in the `spielmodus` over all `L`. What becomes cheaper is the data procurement and the
number of series that must be licence-checked per vintage — not the night.

### T60 — The ranking for a missing policy path

Guessing comes last. The stages are to be tried in this order, and the stage reached decides
the class of the country:

| Stage | What is tried | Class | Derivation in plain text |
|---:|---|---|---|
| **1** | another code **of the same already cleared source for the same quantity** | backtest country | no; `codes` and `code_herkunft` suffice |
| **2** | a **derived** series from an already licence-cleared source | backtest country | **yes**, recomputable |
| **3** | **no path of its own**, because the country has no monetary-policy lever | backtest country | **yes**: which union, from which year |
| **4** | an **estimated** path | **play-only country** | **yes**, with every free parameter named |

**Stage 1 demands the same quantity, and that is no formality.** Today's code
`DISR_RT_PT_A_PT` is per `reihen.toml` a choice from package 0006
(`code_herkunft = "gewaehlt-0006, in specs/ nicht genannt"`), not a necessity — another code
of the same data flow is therefore the first reach. But a code that **measures something
else** is not stage 1, at best the input of a derivation per stage 2.
Without this addition any substitute quantity could be declared stage 1, and the ranking
would be without effect. The case is at hand: `daten/nachmessung-zinsreihen-2026-09-05.md`
names for Germany `S13BOND_RT_PT_A_PT` (yield of government bonds, 1957–2017) and puts the
question expressly to this section. **The answer is no.** A government-bond yield is a
market price; series 9 feeds a policy path in step 3, and an instrument that the market
sets is not one. As the **input of a derivation** per stage 2 the series remains usable —
but then with a derivation, with the gap 2018–2021 in the window and under the bound of the
next paragraph.

**The boundary between stage 2 and stage 4, so that stage 2 does not become a back door.** A
**derivation** contains no parameter that is adjusted against the result of the model; an
**estimate** contains one. Whoever chooses a spread because GDP hits better with it has
not derived but calibrated the model against itself — and the backtest then measures
that choice. The rule is machine-checkable, because the marking per T61 carries the number
of free parameters along: `> 0` rules out stage 2.

**This document draws the same boundary once already, and at exactly this quantity.** T27
records: `leitzins_start[l]` stands **not** in `parameter.toml` but in the vintage —
*"not a calibration quantity but a measurement"*. The obvious way from a
bond yield to a policy rate would run via `aufschlag`, and `aufschlag` is a
calibration quantity: class 3, from `parameter.toml`, carried in T27 as *"spread policy rate
↔ bond yield"* and varied by the night run over a thousand parameter sets. A path formed
this way is therefore not merely "estimated" — it is **estimated in a circle**: T23 point 5
computes `aufschlag_min = 1 − min(leitzins_pfad)`, but the path would come from `aufschlag`.
**A derivation that runs through a parameter-set key is none.**

**Stage 2 is an unchecked conjecture and not a source.** In the room as candidates stand the
WDI interest series `FR.INR.RINR`, `FR.INR.LEND` and `FR.INR.DPST`. They are **no policy
rates**, and **nothing about them is checked**: not the coverage, not the country list, not
the third-party situation. I have expressly **not** looked them up in this run — searching
for interest series does not belong to this package per the brief. One point can be sharpened
without a search, and it weighs more than the conjecture itself: **the assumption "from the
WDI, hence CC BY 4.0" says nothing about a single series.** In `reihen.toml` eight series
from the WDI are embedded (1, 2, 5, 6, 7, 8, 10, 13), all eight with
`lizenz_beleg_typ = "feld_source"` — the decision is made at the code's field `Source`, not
at the catalogue. The result for these eight: five times `unklar` (1, 2, 5, 6, 7), twice
`frei` (8, 10) and **once `gesperrt`** — series 13, the tariff level, and with that of all
things one of the three policy paths. Whoever goes stage 2 via the WDI has not shortened the
licence question, only postponed it.

**Stage 3 is an answer and not a gap — but it delivers a number.** For a country without a
monetary-policy lever of its own, "no path of its own" is right; Germany expressly carries
that per `spiel.md` as a design feature, and `reihen.toml` already carries it with
`exogen_ab = 1999` and the break „Euroraum -- Deutschland folgt ab 1999 exogen der gemeinsamen
Geldpolitik". **What is missing is the authorship, not the value:** step 3 still needs
a number, and that is the union's rate. Stage 3 therefore means exactly: stages 1 and 2 are
applied **to the union** instead of to the country. If the union carries a measured rate,
the country remains a backtest country; if the union's rate must be estimated, the country
falls to stage 4. A country fully pegged to a foreign currency, whose instrument is constant
over the whole window, is likewise stage 3 — a constant is a measured fact.

**Stage 4 makes the country a play-only country**, with a deposited derivation per T61 and
with the shutdown per T58.

**The first application case is not future countries but China and Germany.** For
Germany the first reach is stage 1 on the union — whether the same data flow carries a
territory for the euro area is unchecked and the cheapest open question of this topic. For
China, `CHN.*.A` delivers **zero** annual series in the window per the re-measurement of
2026-09-05; stage 1 fails there within `MFS_IR`, stage 3 does not apply, and stage 2 remains.

**Hence a lock, and it is the reason this rule needs one at all.**
**No data package makes one of today's four countries a play-only country.** If stages 1
to 3 fail for China or Germany, that is not a finding about a series but a
decision about the foundation of the backtest: `L_R` would fall from 4 to 3, the
check subjects from 16 to `3·3 + (3−1) + 1 = 12`, the target series from 27 to
`3·7 − 1 = 20`, and Maß 4 would be measured against a different world than before. **Both
numbers compute with `n = 1`**, because the USA in this case remain backtest country and
numéraire; the `n = 0` case, which the short form in T59 computes through, is a different one
and does not apply here. That belongs to the operator, not to the vintage build. The vintage
build **aborts** (T61) instead of silently rewriting the class.

**And the reverse holds too:** a target series carries exclusively stage 1. Whoever needs a
derivation or an estimate for a target series no longer has a target series but an
estimate that looks like a measurement — the one case that is worse than a missing
series. The marking duty in T61 is bookkeeping for the policy paths; for the
target series it is a prohibition.

### T61 — The marking in `reihen.toml`

**The field that an estimated series carries is called `stufe` and stands in a new block
`[[reihe.herkunft]]`.** The three series with `politikpfad` in `rolle` are series 9 (policy
rate), series 12 (budget balance) and series 13 (tariff level); the fourth instrument,
financial-market regulation, has no series, its value comes per T45 from `parameter.toml`.
They carry **condition a of the class rule and nothing beyond it** — since package `0196` the
class is formed from two sorts of series, and rule 5 below is the only place that says which.
The block is nevertheless mandatory for **every** series, and rule 1 says why.

```toml
[[reihe.herkunft]]
land            = "CHN"      # Kürzel wie in [[reihe.deckung]]
stufe           = 2          # 1…4 nach T60; das Feld, das eine Schaetzung kenntlich macht
quelle          = "WDI, FR.INR.LEND"
abrufdatum      = "2026-09-06"
freie_parameter = 0          # > 0 ist nach T60 keine Ableitung, sondern eine Schaetzung
herleitung      = """
Pflicht ab Stufe 2. Klartext, so vollstaendig, dass die Reihe daraus
nachgerechnet werden kann: Eingangsreihen, Rechenweg, Fenster, Luecken.
"""
```

**Five rules, all mechanical:**

1. **No series without origin.** The three policy-path series carry exactly one block per
   country — they all have `dimension = "4"`, at `L = 4` that is `3 × 4 = 12`. Each of the
   remaining sixteen series carries exactly one block with `land = "alle"`, as
   `[[reihe.deckung]]` already knows it; together **28**. If one is missing, **the vintage
   build aborts** — the same construction as the provenance table from T45, and for the same
   reason: a tacit "measured" for a missing field would be exactly the lie against which this
   rule is written. An optional field would not have prevented it but produced it.
2. **Derivation duty.** `stufe ≥ 2` without a non-empty `herleitung` aborts.
3. **Parameter lock.** `stufe = 2` with `freie_parameter > 0` aborts (T60).
4. **Target-series lock.** A series with `soll` in `rolle` and `stufe ≥ 2` aborts. Only
   rule 1 gives this lock teeth: without the mandatory block per series it would be effective
   only against whoever enters their estimate voluntarily.
5. **Double bookkeeping over the class — and the class is formed from two sorts of series.**
   The manifest of the vintage carries `rueckvergleichslaender = [...]` written out. From
   `reihen.toml` the same set follows derived. **A country is a backtest country exactly when
   all three conditions below hold, and a play-only country otherwise.** Each names the sort
   of series it is measured in, because the three do not lie in the same block:

   | | Condition | measured in | read from |
   |---|---|---|---|
   | **a** | none of its three `politikpfad` series carries `stufe = 4` | the policy-path series | `[[reihe.herkunft]]`, one block per country (rule 1) |
   | **b** | each of its target series carries the whole window at stage 1 | the target series | rule 4, and `[[reihe.deckung]]` for this country |
   | **c** | each of its target series with `t37_klasse = "frei"` moves in at least one transition | the target series | their values over the window |

   **If derivation and manifest do not agree, the vintage build aborts.** The derivation alone
   would be the more convenient construction and the wrong one: it would let one row in a data
   series shift the foundation of the backtest without it showing up anywhere. The lock from
   T60 is exactly this check.

**a was the whole of this rule until package `0196`; b and c are added there.** The finding is
the game designer's, from the run to `0118`: both grounds *„lie in the target series, and the
class rule can see neither"*. **A country's target series are its `S + 4`** — `S + 3` for the
numéraire country, whose exchange rate against USD is none —, so `L_R(S + 4) − n` in the
vintage, 27 at `L_R = 4` (T37, T59). They are series 1, 2 (three of them), 8, 10 and 11.

**On b — the stage stands once, the coverage stands per country.** A target series carries its
origin block with `land = "alle"` (rule 1); its `stufe` therefore holds for all countries at
once and is 1 by rule 4. Per country is the **coverage**: `[[reihe.deckung]]` must carry the
`R + 1` support points of the window without a gap — the class *full, no filling* of T62, which
marks exactly these five series with it. A country whose stage-1 source yields no value there,
or not the whole window, has no target series there. Whether a substitute source may be brought
in is a licence question, and for series 2 T62 conclusion 2 answers it: **there is none.** That
is the older of the two grounds — it stood in T62 before this rule could see it.

**On c — a constant target series breaks its check subject by construction.** Directional
accuracy (T42) counts the transitions in which model and target series carry the same sign.
Over a series constant across the window each of the `R` transitions carries direction zero,
and an endogenously computed value practically never hits the exact zero. `spiel.md` names case
and country: *„series 10 is **constant** for Saudi Arabia across all 21 support points"*
(`spiel.md`, section *Welche neun Länder, welche Klasse, und was Weg A kostet*, subsection *The
class per country, and what it hangs on*, read 2026-09-08). The condition runs over the `frei`
target series alone, because only they form check subjects (T37); a constant `abgeleitet`
series is reported and decides nothing, and a country excluded over it would be a country lost
without a check protected.

**And c falls away by itself where the model gains a rule.** It bites because the model
computes the quantity freely — it holds no exchange rate. `spiel.md` keeps the peg open as the
operator's decision; the `wechselkurs[l]` of a pegged country would simply not be written, the
same construction as the shutdown in T58. Where an address is held that way, model and target
series stand still together. **c therefore reads in full: constant over the window *and* the
address compared against it is written in the `weltlauf`.**

**Where the class is formed, and why the order is not free.** T62 footnote 1 makes the window
requirement of these five series hold *„Only if the country becomes a backtest country"* and
states that *„The target role arises with the class, not with the country"*. Read as a
condition that is a circle: the role follows the class, and the class now follows the series
that carry the role. Read as an order it is none, and the order is what this rule owes:

1. origin and coverage blocks per rule 1;
2. **the class per this rule**, over the *candidate* target series — the set the country would
   carry as a backtest country, asked before it is one;
3. the comparison against the manifest, and the abort;
4. the roles from the class (T58, T62 footnote 1);
5. rules 2, 3, 4.

**Rule 4 thereby becomes a net behind a net:** after step 2 no country reaches step 5 with an
estimated target series. It stays, because it is the invariant of T60 and not a filter, and an
invariant that can no longer be breached is the cheapest kind.

**What the build reports on divergence:** the country, both classes, and **which of a, b, c
produced the derived one, with the series it was measured on**. Without that last half whoever
reads an abort searches the policy paths — where in the cases b and c nothing is wrong. That is
the whole of the finding this rule answers: *„The abort is right, the place is not."*

**The probe, written out, because it is the case the rule was rewritten for.** Saudi Arabia,
and `MFS_IR` lists a SAMA policy rate at stage 1 (T63 step 1; that retrieval is open and
belongs to the data builder):

| | old wording | this wording |
|---|---|---|
| a | satisfied — no `stufe = 4` | satisfied |
| b | not asked | satisfied |
| c | not asked | **fails**, series 10 |
| derived class | backtest country | **play-only country** |
| manifest (`spiel.md`, T58) | play-only country | play-only country |
| the build | **aborts**, naming the policy paths | runs |

The two bookkeepings agree, and they agree on the ground `spiel.md` gives. The probe decides
nothing about Japan, India and Chile: their a hangs on the same retrieval, their b and c on the
coverage of a vintage not yet built (section 26, conditions 2 and 3).

The class thus stands written in one place and computed in a second, and the
build halts where they diverge — the same construction as the second write access in T39
and the fund's assets in T47.

### What this section has not touched, and what stays open

**Not touched.** T37 keeps its sixteen check subjects, its tolerance 2 and its
class table word for word; the formula stands here and not there, so that
`0068-technikmd-reihe-9-ohne-sollrolle` finds its reference point unchanged. That the
row `gesetzt` in the class table of T37 has been empty since package 0054 is known and
likewise belongs to 0068. **Overtaken on 2026-09-08 by package `0221`, and the sentence
stays as the record of what *this* section did:** T37 now carries the same formulas this
section wrote, and 16 and 2 stand there as their evaluation at `L_R = 4`, not as digits.
The reference point 0068 needs is thereby unchanged in **value** and changed in **form**;
what 0068 owes is the wording of the `gesetzt` row, and that is untouched (section 26). Section 7, T55 and the numbers 310 and 740 remain standing: the
extent of the state is just now in motion through the three layers in `spiel.md` and belongs
to 0118/0119, and this section does not need it — its formulas count check subjects and
target series, not addresses. `reihen.toml` is **not** changed; T61 describes a block that
a data package enters.

**Three reports to the project manager, because they belong to other trades.** First:
`spiel.md` carries, in the table of the three layers, for layer 1 in the column *im
Rückvergleich* „ja, als Rückvergleichsland" without exception. With the two classes that
becomes „ja, **wenn** Rückvergleichsland". That is one line in `spiel.md` and not mine.
Second: T58 stipulation 3 (rest-of-world remainder per mode) and stipulation 4 (poison test)
are design and each need a package — vintage build and test bench — as soon as the first
play-only country is actually entered. Before that it would be code written ahead of need.

**Third, and it is a follow-up I leave lying with open eyes:** the preamble before
section 1 says „Die Vorgaben sind mit **T1** bis **T53** durchnummeriert". Right would be,
since package 0116, T57, and after this section **T61**; the next free number is T62. The
same preamble and section 17 moreover carry **T60** as an example of a *still free* number —
from here on it is one no longer. **I touch neither place, and not out of
caution:** the work packages `0082` and `0084` bind their acceptance expressly to
„der Vorspann unberührt bleibt — er ist mit 0026 abgenommen". Whoever brings it up to date
takes the acceptance criterion away from two running packages. That is a package of its own,
and it should run after 0082 and 0084.

**A collision of the acceptance with itself, named openly.** Condition 4 demands that
`git diff` show changes exclusively in `technik.md`. The run changes two further files, both
forced by rules that stand above this package: the status line in the work package (without
it the runner schedules the same package again) and the role's logbook (CLAUDE.md). The
purpose of the condition — no number outside `technik.md` moves, no second trade is
touched — is met; the sharper measurement for it is that this section is a pure
appendix and removes or changes **no** existing line.

**Which stipulation had to fall now and which is deferred.** What had to fall now was the
choice between A, B and C: it decides whether the exemption sits in the run or in the
evaluation, and that cannot be retrofitted without devaluing every stored backtest.
Likewise the marking, because an unmarked estimate can afterwards no longer be
distinguished from a measurement. Deferred are the choice of countries (0118), the
choice of codes and the estimation procedure itself — each of these is a data question, and
none of them changes anything about these three prescriptions.

## 21. Was ein fünftes Land an Daten mitbringt — Paket `0141`

**What is decided here and what is not.** This section selects **no** country (that is
`0118`), does **not** change the country count, loads no data and assesses no license. It
describes the effort; it does not incur it. Two things are decided: the countable list of
what a further country brings in series, windows and license questions (T62), and what
holds when the embedded policy-rate code does not list a country (T63). The section is a
pure appendix; it removes and changes no line of the existing text.

### T62 — The list per data series

**Three window classes, and they follow from the role of the series, not from its number.** `A`
is the start year of the vintage, `R` the round count; a vintage carries `R+1` support points
for the years `A … A+R`.

| Class | Requirement | Prescription |
|---|---|---|
| **full, no filling** | `R+1` support points, `gefuellt = 0` | T24, first threshold |
| **full, filling marked** | `R+1` support points; gaps are filled and disclosed, but enter no error measure | T24, T25 |
| **start year** | exactly one support point, the year `A` | T25 |

**The list is written in `R` because the window has two values in this repo.** This
document uses the check vintage 1997–2021 throughout, so `A = 1997`, `R = 24`, 25
support points. `daten/reihen.toml` measures the first US value of series 11 in the year 2001
and judges *„verkuerzt — 1997 bis 2000 fehlen, kostet vier Stuetzstellen und erzwingt das
Startjahr 2001"*, so `A = 2001`, `R = 20`, 21 support points. The choice between the two
ways out — drop the series or shorten the window — belongs to the game designer under T24 and
costs a number in the manifest under T40. **This section does not resolve the point**; where a
number stands below, it stands for both readings.

| No | Quantity | new at `L: 4 → 5` | Source, embedded code | Window | License status | does a further country move the verdict? |
|---:|---|---:|---|---|---|---|
| 1 | GDP, constant prices | 1 | WDI `NY.GDP.MKTP.KD`, fallback PWT | full, no filling¹ | unklar | **yes** — offices and central banks |
| 2 | Value-added share per sector | 3 | WDI `NV.AGR.TOTL.ZS`, `NV.IND.TOTL.ZS`, `NV.SRV.TOTL.ZS` | full, no filling¹ | unklar | **yes** — offices and central banks, **no fallback source** |
| 3 | Capital stock | 1 | PWT, code not fixed anywhere | start year | frei | no |
| 4 | Productivity (TFP) | 1 | PWT, code not fixed anywhere | start year | frei | no |
| 5 | Population | 1 | WDI `SP.POP.TOTL`, fallback PWT | full, filling marked | unklar | **yes** — offices (the field names no central bank) |
| 6 | Labor force | 1 | WDI `SL.TLF.TOTL.IN`, fallback PWT | full, filling marked | unklar | no — ILO |
| 7 | Employment per sector | 3 | WDI (ILO) `SL.AGR.EMPL.ZS`, `SL.IND.EMPL.ZS`, `SL.SRV.EMPL.ZS` | start year | unklar | no — ILO |
| 8 | Consumer prices | 1 | WDI `FP.CPI.TOTL.ZG`, fallback IMF IFS | full, no filling¹ | frei² | no — IMF |
| 9 | Policy rate | 1 | IMF `IMF.STA/MFS_IR 9.0.0`, code `DISR_RT_PT_A_PT` | full, filling marked | unklar | no — IMF; **code choice per country, see T63** |
| 10 | Exchange rate against USD | 1³ | WDI `PA.NUS.FCRF`, fallback IMF IFS | full, no filling¹ | frei² | no — IMF |
| 11 | Government debt ratio | 1 | IMF `IMF.RES/WEO 9.0.0`, `GGXWDG_NGDP` | full, no filling¹ | unklar | no — IMF |
| 12 | Fiscal balance | 1 | IMF `IMF.RES/WEO 9.0.0`, `GGXCNL_NGDP` | full, filling marked | unklar | no — IMF |
| 13 | Tariff level, aggregated | 1 | WDI (from WITS) `TM.TAX.MRCH.WM.AR.ZS` | full, filling marked | **gesperrt**⁴ | no — WITS, UNCTAD, WTO |
| 14 | Bilateral flows by HS92 | **20 flows** | CEPII BACI, version 202601 | full, no filling¹ | frei | no — Etalab |
| 15 | Price level in country comparison | 1 | PWT, code not fixed anywhere | start year | frei | no |
| 16 | `durchgriff` | 2, derived | from series 14, 1 and 2 per T23 point 5 | no procurement of its own | inherited | inherits from 1 and 2 |
| 17 | Sector prices | — | none | endogenous | — | — |
| 18 | Approval | 1 key value | `parameter.toml` | no procurement | — | — |
| 19 | Market basket value and market return | — | not kept per country | — | — | — |

¹ **Only if the country becomes a backtest country.** As a play-only country the start year
suffices for these series: T58 shuts down its addresses in the `weltlauf`; they keep their
start value and are not written. The target role arises with the class, not with the country.

² `frei` per `daten/lizenzbefund-wdi.md`, because the `Source` field names the IMF as third
party and its terms permit commercial sale. `reihen.toml` sets a second number against this
one in `zaehlung.lizenz.gegenrechnung`: the IMF license text is unread after five attempts
from three roles (HTTP 403), and taking „ein Suchauszug genügt
nicht" seriously there too, this `frei` is an `unklar` as well. Both readings stand
side by side; **a further country moves neither of them.**

³ Only if the fifth country is not the numéraire country. Series 10 carries dimension 3 and
not 4 because the numéraire has no rate of its own — that is the term `n` from T59.

⁴ Equally locked for **all** countries; per `lizenzbefund-wdi.md` the only case in which the
named third party expressly reserves its consent. A fifth country changes nothing about this
and inherits the case: of its three policy-path series, one has no data anchor from the
outset. T26 first case holds unchanged — no tariff path, constant tariff, two instead of three
anchored instruments.

**The count, and it is the actual subject of this package.** A fifth country brings
**18 country series and 20 trade flows**, together **38**. The country series are
`12 + 2S`, so 18 at `S = 3`; the new flows are `2(L+1)(S−1)`, so 20 at `L = 4` and `S = 3`
— the difference `(L+2)(L+1)(S−1) − (L+1)L(S−1)` from the trade formula in T55.

| Window class | Series and flows | which |
|---|---:|---|
| full, no filling | **27** | the seven new target series (1, 2×3, 8, 10, 11) and the 20 flows |
| full, filling marked | **5** | the exogenous paths 5 and 6, the policy paths 9, 12, 13 |
| start year | **6** | 3, 4, 7×3, 15 |
| test | **38** | `27 + 5 + 6` |

The seven target series are `S + 4` — exactly the increase T59 computes from the other side
with `L_R(S+4) − n`. The check subjects grow by four (`3 + 1` for a country that is not
the numéraire), as T58 already states under the class change.

**What follows in values, per class.** A **backtest country** costs
`32(R+1) + 6` values: 32 series over the full window, six start values. A **play-only country**
costs `5(R+1) + 33`: the five paths over the full window, 33 start values (7 series +
20 flows + 6). Inserted:

| | `R = 24` (window from 1997) | `R = 20` (window from 2001) |
|---|---:|---:|
| backtest country | **806** | **678** |
| play-only country | **158** | **138** |
| the same without the locked series 13 | 781 / 133 | 657 / 117 |

**Counter-calculation, by source instead of by window class, for `R = 24` and backtest country.**
WDI twelve series: six target series (1, 2×3, 8, 10) at 25 each, three full paths (5, 6, 13) at
25 each, three start values (7) — `150 + 75 + 3 = 228`. IMF three series (9, 11, 12) at 25 each — 75.
PWT three start values (3, 4, 15) — 3. BACI 20 flows at 25 each — 500. Sum
`228 + 75 + 3 + 500 = 806`, the same number over a different split, and `12 + 3 + 3 = 18`
country series.

**A trap, because it is the same family as "40 against 40" and "27 against 27" in T55: 38
against 38.** The 38 series and flows of this list and the 38 state addresses untouched by
`L` from T57 are the same number and have nothing to do with each other. T57 computes
`5S + 23` and does not depend on `L`; this list computes `12 + 2S + 2(L+1)(S−1)` and does.
At `L = 5` it is 42 against an unchanged 38. Whoever takes the two for the same quantity takes
the data cost of a further country for constant, and it is not.

**What a fifth country moves in the license status — and what it does not.** Of the 19 series,
exactly **three** hang, in the `Source` field, on the national offices and central banks of the
reporting countries: series 1 and series 2 (*„Country official statistics, National Statistical Organizations and/or
Central Banks"* and *„National Statistical Offices (NSOs); National Accounts data
files, Central Banks"* respectively) and series 5, which names the offices alone. All others name
named organizations — IMF, ILO, OECD, WITS/UNCTAD/WTO, CEPII, PWT — whose terms are
independent of the country list. A fifth country therefore brings **exactly two** new bodies
to check, its statistical office and its central bank. They join the eight of today's
model countries, of which per `lizenzbefund-reihen.md` exactly one is checked (Destatis);
after that it is ten bodies and one check.

Three conclusions, and the third is the one against which I corrected myself:

1. **A fifth country can improve no license verdict.** The three affected series already
   stand at `unklar`.
2. **It can worsen one.** If the country's office or central bank refuses commercial
   redistribution, its values in series 1, 2 and 5 are locked. Series 1 and
   series 5 have, with the PWT, a checked free fallback source. **Series 2 has none** —
   `quellenwahl_grund` says why: the PWT delivers no sectoral value added, finer
   breakdowns exist only at the OECD (unresolved) and at Eurostat (locked for the non-EU
   countries of the model). Series 2 carries `S` of the seven new target series. It is thus the
   only place in the whole list where a country's origin hard-excludes the
   backtest.
3. **Still, this is no selection criterion for `0118`.** Seven of today's eight bodies are
   unchecked. A criterion that demands from a fifth country a check nobody has done for
   today's model countries does not measure the country's cleanliness but
   who was checked. The two new bodies belong on the same list as the seven open ones
   (`lizenzbefund-reihen.md`, clarification 4) and are dealt with together with them or not at all.
   **A cost, not a gate.**

### T63 — The policy rate when the embedded code does not list the country

**Chosen is a substitute procedure: no substitute source in advance and no exclusion criterion.**
The rule for every country whose policy rate is needed:

1. **First query `LAND.*.A`, do not assume the chosen code.** One query on
   `IMF.STA/MFS_IR 9.0.0`. If the country lists a code that measures a **policy rate**, that is
   stage 1 under T60 and the case is closed.
2. Otherwise, in order, stage 2 (derivation without a free parameter), stage 3 (no lever of
   its own — stages 1 and 2 on the union instead of the country), stage 4.
3. If it stays at stage 4, the country is a **play-only country** under T58. It is thereby not
   excluded but classified. For today's model countries the lock from T60 additionally
   applies: the vintage build aborts instead of silently rewriting their class.

**Why step 1 is no formality.** `DISR_RT_PT_A_PT` stands in `reihen.toml` with
`code_herkunft = "gewaehlt-0006, in specs/ nicht genannt"` — a choice, not a property of the
data flow. How far code and data flow lie apart is measured, not presumed:
`daten/nachmessung-zinsreihen-2026-09-05.md` finds, in the window 1997–2021, **eleven**
annual series for Germany and the chosen code **not** among them, **zero** series for China,
nine for the USA and seven for Brazil. A finding "the code does not carry for this country" is
therefore at first a statement about the choice from package 0006 and not yet one about the source.
For a fifth country the distinction costs one query; skipping it costs a
country that need not have been discarded at all.

**Why no substitute source is fixed in advance.** Introducing a second interest-rate source
would mean taking, for **one** series, a further source into the license check, into `namensnennung` and into the
manifest — and license work is, per T62, the most expensive item of the whole list.
The price is measured: of the eight series embedded in the WDI, five are `unklar` and one
`gesperrt`. The obvious WDI candidates `FR.INR.RINR`, `FR.INR.LEND` and `FR.INR.DPST`
are moreover, under T60, no policy rates but at best input to a derivation, and the
route via a government bond yield is already barred there: it ran via `aufschlag`,
a key from `parameter.toml`, and a derivation via a parameter-set key is not
one. **As long as `MFS_IR` carries for a country, it is the cheapest route; where it does not,
stage 4 is cheaper than a ninth source.**

**Why no exclusion criterion — this is the argument that carries the choice.** Series 9 has,
since package 0054, been **no target series** (`sollreihen = 0`, `t37_klasse` empty) and stands in none of the
sixteen check subjects; the exhaustive enumeration in `reihen.toml` under
`zaehlung.pruefgegenstaende` lists GDP, sector structure, consumer prices, exchange rate and the
trade block — the policy rate it does not list. Excluding a country over a missing policy
rate would thus protect a quantity the backtest does not measure at all. What a
missing policy rate really costs is one anchored instrument in the `spielmodus` — and that is
exactly what the play-only country class is built for: its quantities are shut down in the
`weltlauf` and act via trade and world prices on no check subject.

**The exclusion barrier stands elsewhere, and it is sharper.** A fifth country as a
**backtest country** needs its `S + 4` = seven target series at stage 1 — by the
inversion in T60, a target series carries stage 1 exclusively. The policy rate is none of them.
The one series on which a country can fail at this and which at the same time has no fallback
source is series 2 (T62, conclusion 2). **Whoever seeks an exclusion criterion for `0118` finds
it there and not at the policy rate.**

**What the choice entails mechanically — nothing new, and that is intended.** T61
rule 1 counts the origin blocks as `3L + 16`, so 28 at `L = 4`. A fifth country makes
that **31**: three further blocks, one each for the policy-path series 9, 12 and 13. If one is
missing, the vintage build aborts under rule 1. If one carries `stufe = 4`, the country is a
play-only country under rule 5 and must stand so in the manifest too, otherwise the build halts. T63 thus
needs no lock of its own; it only says in which order the stages are to be tried
and that the result is a class and not a verdict on the admissibility of the country.

### What this section did not touch

**Nothing.** No country chosen, the country count unchanged, no line of the existing text
removed or changed, no table updated, `reihen.toml` untouched. The state quantity from
T55 and the statement about today's model countries stand unmoved: `grep -c` yields 44 and
7 lines respectively before and after this run. The window is **not** decided — the
list is written in `R`, and both readings carry their number.

**Three reports, because they belong to other trades.** First: the two additional bodies
belong in the enumeration under clarification 4 in `daten/lizenzbefund-reihen.md`. That is a
data package and not an architect's line. Second: the brief text for `0141` names the window
„ab 2001", this document uses 1997–2021 throughout. Both are documented, the choice belongs
to the game designer under T24, and I therefore have not made it. Third: the
preamble follow-up from section 20 grows by one line — correct would now be **T63**, the
next free number is T64. I do not touch the preamble for the same reason as there:
`0082` and `0084` bind their acceptance to it remaining untouched.

**Which stipulation had to fall now and which is deferred.** What had to fall now was the
question from T63 whether a missing policy rate **excludes** or the **class decides**. It
must fall before `0118` because it changes the search space of the country selection by orders
of magnitude: as an exclusion criterion all that would remain is what a single IMF code lists
a policy rate for — it does not for two of today's model countries; as a class question every
country is selectable, and the policy rate alone decides whether it costs 806 or 158 values.
Deferred are the choice of the country, the choice of its codes, the estimation procedure of
stage 4 and the window. None of these changes anything about T62 or T63.

## 22. Der Schadenseingang — Paket `0165`

**What is decided here and what is not.** Decided is which state numbers 9, 10 and 11
read when number 22 calls them, and by which route it arrives. Not decided is anything
about the damage rule itself: the four rows, their quantities, their shifts and the number
106 stay as `spiel.md` writes them, and no address is added, removed or reclassified. The
decision stands at T48 number 22; this section carries the evidence for it, the two
answers rejected and the reports.

### The finding, in the numbers of `spiel.md`

The brief reported number 22 as built with **two** state inputs,
`schaden(z, rundenschreiber, konst, l, i)`, and asked what ties them together. Nothing
does, and the count-off `spiel.md` prints for itself says why it also cannot be made to.
Section *Wo die Regel läuft* books the reads of the damage:

| read as | addresses | comes today through |
|---|---:|---|
| `lies_neu(land.<l>.instrument.<i>.stand)`, written in step 3 | 16 | `hub` — the writer ✓ |
| `lies_neu(welt.preis.<s>)`, written in step 4 | 2 | `keilhub` — the writer ✓ |
| `lies_neu(handel.<a>.<b>.<s>)`, written in step 4 | 40 | `handelsvolumen` — a `Zustand` ✗ |
| `lies_neu(land.<l>.sektor.<s>.wertschoepfung)`, written in step 4 | 12 | `bip` — a `Zustand` ✗ |
| `lies_neu(land.<l>.staatsschuld)`, written in step 4 | 4 | `schuld` — a `Zustand` ✗ |
| `lies_alt(…instrument.<i>.stand)`, `lies_alt(…gegendruck)` | 32 | `hub`, counterforce 5 ✓ |

`74` of the `106` are `lies_neu`, and **56 of those 74 arrive today through a `Zustand`.**
The damage runs in step 5; those 56 addresses are written in step 4 of the **same** round.
So the state the three quantities have to read is the one emerging in this round — and no
`Zustand` in step 5 carries it. `Schreiber` keeps it as `neu` and releases it only through
`rundenende()`, after the two-sided mask check of T38. The only `Zustand` a step-5 caller
holds is `vorrunde`, the argument of `schritt` per T10b.

**The two inputs are therefore not merely unbound; the second one has no correct value.**
That is one step worse than the brief assumed, and it changes which answer is available:
whatever `z` a caller passes, three of the four damage rows read the world before step 4.
All four are affected — the tariff row through `handelsvolumen`. `spiel.md` writes of
channel 3 that the tariff level reaches the damage „by two paths instead of one", and the
older of the two runs instrument → trade → `handelsvolumen`; read from the previous round,
that path carries nothing.

### Why the cheap answer is not available

Answer 3 of the brief — leave two inputs and write down which state is meant — asks for a
sentence that cannot be written true. „`z` is the state emerging in this round" names no
object that exists in step 5; „`z` is the previous round" contradicts the 56 rows above.
A binding sentence over a pair of which one member has no correct value binds nothing.

**And the precedent the built version cites does not carry.** Its header calls the
two-input form „dieselbe Bauart wie `marktkorb`". Number 7 takes two states **because they
are meant to differ** — quantities via `lies_alt`, prices via `lies_neu` per T33; the
difference is the quantity's whole content. Number 22's two inputs are meant to be the
same round. A construction whose point is a difference is no precedent for a pair that
must not differ.

### Why not answer 2, with the readers

Answer 2 — move numbers 9, 10 and 11 wholly onto the writer — fails on readers that have
no writer and cannot get one, and this is the list checked against (state of
2026-09-08):

| Reader | where | reads | why a `Zustand` and not a writer |
|---|---|---|---|
| `waehrungswert(l)`, no. 4 | `kern/src/werte.cpp:628` | `handelsvolumen(z, l)` | valuation, called on a finished state |
| `anleihewert(l)`, no. 3 | `kern/src/werte.cpp:581` | `schuld(mengen, l)` | the **quantity** side of `marktkorb`, deliberately `lies_alt` per T33 |
| state output, country level (G8) | `kern/src/zustandsausgabe.cpp:169` | `bip(z, l)` | displays a saved or finished game; there is no round and no writer |
| test bench | `kern/test/werte_probe.cpp`, `kern/test/zustandsausgabe_probe.cpp` | all three | states built by hand, without a round |

The third row alone settles it: the three-level state output of G8 must be able to print a
loaded game, and a loaded game has no writer. Answer 2 would have to invent one.

### Why not a read access on the writer's state

The obvious cheap form of answer 1 — the `Schreiber` hands out its emerging state as
`const Zustand&`, and numbers 9 to 11 stay as they are — is the one form that must not be
built, and the built writer says so itself:

> `neu` beginnt als Abschrift von `alt`. … Auf das Leserecht wirkt die Abschrift nicht —
> `lies_neu` entscheidet am Bitfeld und nicht am Wert.
> (`kern/include/kern/schreiber.hpp`, box above `class Schreiber`)

A bare reference to `neu` reads past the bit field. An address not yet written in this
round then yields its previous-round value **silently** — exactly the fallback T39 forbids
in words („kein stiller Rueckgriff auf `alt`"), and reintroduced at the one place the
order 4 → 5 has to hold. The route must therefore be `lies_neu` itself, and that means a
form of each quantity that takes the writer.

### What is prescribed

1. Numbers 9, 10 and 11 each get a **second form** taking `const schreiber::Schreiber&`,
   with the same name, the same arity and the same class as the `Zustand` form, and every
   address of the formula read through `lies_neu`. The existing `Zustand` signatures are
   **unchanged**; no reader of the table above is touched.
2. Number 22 becomes `schaden(rundenschreiber, konstanten, l, i)`. It calls the writer
   forms of 9, 10 and 11 and the already-writer-based 18, 19 and 20, and holds no
   `Zustand` at all.
3. **The duplication is pinned by a check and not by care.** For a writer in which every
   address of the formula has been written with the value a state `z` carries, both forms
   return the same number, bit for bit — one test per quantity, over the countries and
   sectors, and it fails the moment the two bodies drift apart. That is a cheaper proof
   than a shared implementation would be, and a shared one is not available: the two
   forms differ precisely in the access that has to differ.
4. **The T39 abort is the yield, not the cost.** Reading through `lies_neu` turns
   „counterforce 5 runs after the market clearing" from a promise into a property every
   run proves: called before step 4, number 22 dies at the first unwritten address instead
   of returning a plausible number from the previous round. `spiel.md` argues the same way
   for the round boundary of channel 3 — „not promised but enforced".

### The count-off after this section

**Twenty-two quantities, twenty-six declarations** in `werte.hpp` outside `intern`,
counted 2026-09-08: twenty-three today, plus one each for numbers 9, 10 and 11. The
quantity count does not move, and the mechanical proof of T48 stays runnable with one
added rule — a name is counted once, its forms beside it. That rule is not new; number 11
has needed it since 2026-09-03 for its two arities, and this is the same case with the
read access in place of the arity.

**A blank address in the Definition column of T48 does not mean `Zustand`.** It means the
table does not decide the access, and where the access changes the number, the entry at
the quantity does — this is now written out for numbers 9 to 11, and it was already the
case for number 19, whose blank `welt.preis.<s>` is read through the writer because
`hub` forces it, and for number 21, whose blank is a `Zustand` for the stated reason that
the market clearing has not yet written a world price.

### Cost, and what does not change

**No new address (310 stays 310), no new field, no target mask changed, no save format
touched, and no new read.** The same 56 addresses are read as today, by the same formulas
in the same order; only the route changes. Each of those reads gains the bit test that
`lies_neu` performs anyway — the same order of magnitude T18 prices for the write side at
„one bit test per write". The cost line of section 10 does not move, and the 106 read
accesses of `spiel.md` stay 106.

**No ADR, and the reason is checkable.** T10's touchstone from `0208` — removing an
argument needs one — protects a **signature sentence that stands in a specification**,
and answers which part of T10 binds. `schaden(z, rundenschreiber, konst, l, i)` stands in
no specification; it stands in `werte.hpp`, chosen by the build agent of `0152` and
reported by it as the one decision it had to make without cover. T48 has never bound C++
argument lists: number 13 and numbers 18 to 20 take a writer, numbers 1 to 12 a state, and
the table's Definition column names neither. Closing that gap for number 22 is what this
package is, and the place for it is the document that carries the decisions of this trade.
*Whoever reads T10's touchstone as general rather than as a statement about `schritt` gets
a different answer here; then this section is the ADR text and someone with write access
to `decisions/` has to copy it. I do not have it.*

### Reports

1. **To the project manager — the built version must move, and it is small.** Affected:
   one declaration and one definition of number 22, three new declarations and definitions
   for numbers 9 to 11, and **twelve call sites in `kern/test/werte_probe.cpp`**;
   `schaden` has **no** caller in `kern/src` today (checked 2026-09-08 over `kern/**.cpp`).
2. **The existing test currently proves the opposite of what it looks like.**
   `probe_schaden_zollzeile` passes as `z` the very state the writer was constructed from
   and writes only instrument levels and world prices into the round, so `handelsvolumen`,
   `bip` and `schuld` read values that did not move. The numbers 440.000, 3.000, 6.000 and
   2.100 are right and stay right; what the test does not show is the case in which step 4
   moved the trade block. **A test whose subject cannot move is green and worthless** —
   the writer forms turn that into a case the test must set up explicitly.
3. **To the game designer, and it needs no answer for this section:** `spiel.md` writes
   `lies_neu(land.<l>.staatsschuld)` and books it as written in step 4. It is in the target
   mask of T38 in both modes, so the read is satisfiable; whether the debt ratio is in fact
   written before step 5 in every mode is a property of the step order and not of this
   decision.

## 23. Die Untergrenze des Zollfaktors — Paket `0172`

**The decision: way 1, the bound sits at the instrument.** `zollstand` gets no new number
and number 21 gets no abort. The value range T51 already prescribes for the instrument
becomes **bound 8 of T30 check 2**, and the positivity of number 21 is *derived* from two
bounds that are checked every round instead of being guarded a second time in the
quantity itself.

**The measured case, and what happens to it now.** From the review of package `0152`
(`befunde/pruefung-0152-werte-zweiundzwanzig-statt-siebzehn-2026-09-06.md`, section
*Ränder*), against an unchanged `werte.cpp`; both assertions hold, the run is green:

```
zollstand(DE) = -12'000, welt.preis.1 = 11'000  ->  weltpreis_mit_zoll = -2'200
zollstand(DE) = -10'000, welt.preis.1 = 11'000  ->  weltpreis_mit_zoll =      0
```

Recomputed here as arithmetic and not taken over: `11.000 · (10.000 − 12.000) / 10.000 =
−2.200` and `11.000 · 0 / 10.000 = 0`. Both states are, from this section on, a **hard
error of check 2** in the round in which they arise, reported at the address
`land.DE.instrument.zoll.stand` and not at number 21. Number 21 keeps computing them
character for character as T48 writes it: a state that check 2 rejects does not need a
second guard in each of its readers. Bound 8 has exactly the status of the seven existing
ones and no more — where check 2 runs is T30's business and is unchanged here.

**Why the bound sits at the instrument and not at the quantity — three reasons, and the
second corrects the brief.**

1. **It is already there, and only the check was missing.** Three places carry it today:
   T51's table row (`0 … instrument_max[zoll]`), `parameter.toml` under
   `[instrument.zoll]` (`instrument_min = 0  # FEST (T51)`), and the capping of step 3
   (`stand = min(max(stand ± schritt, min), max)`). Only the third one *acts*, it acts in
   `spielmodus` only, and it is a single line whose failure is invisible in the result —
   which is the error kind check 2 exists for. This section therefore adds no number; it
   moves an existing prescription to the one place that tests it.
2. **The precedent way 2 rests on says the opposite of what it was cited for.** The
   package brief names number 1, `wechselkurs[g] ≥ 1`, as the case in which the derived
   quantity aborts by itself. It is not: the paragraph on the order of the roundings
   (section 8, *Two value-range bounds belong with this*) writes „`wechselkurs[g] ≥ 1` is
   therefore an invariant (T30 check 2), not an expectation", and for exactly the reason
   that applies here — a sign flip that nothing notices. The one existing precedent for
   this defect kind was decided the way this section decides it.
3. **Cost, and it is a factor of 400.** T28 forms the tariff wedge **inside** each
   bisection step, so the readers of number 21 are 40 bisections × 2 tradable sectors ×
   5 territories = **400 per round**, not one per market clearing as the brief assumed.
   `zollstand` is written in step 3 and stands fixed through the whole of step 4; a check
   inside number 21 would repeat the identical comparison 400 times per round on an input
   that changes once. Bound 8 costs 16 addresses × 2 comparisons per round.

**Why the row is written over all four instruments and not over the tariff alone.** The
brief asks for `zollstand ≥ 0`, which is 4 addresses. T51 prescribes a value range for
**all four** instruments and says it holds in both modes; check 2 checked none of them.
Writing the tariff row alone would leave the identical hole open for policy rate, budget
and regulation and cost the same, because the bound is one comparison pair against
`instrument_min[i]`/`instrument_max[i]`, which `parameter.toml` carries per instrument
anyway. The generic form is therefore one row instead of four and no further decision:
every one of the four ranges is already written in T51. **This is the one place where
this section goes wider than its brief**; whoever considers the widening wrong strikes
three of the sixteen addresses, and the case the package asked for stands unaffected.

**What the bound buys beyond the sign: T28's admissibility proof has a third premise.**
T28 proves the bisection admissible from two premises, both named there — `durchgriff`
lies in 0 … 10.000, and `landespreis` stands fixed while the bisection runs. The third is
not named. The derivative of the blended price with respect to the trial world price is

```
d preis / d welt.preis  =  durchgriff · (10.000 + zollstand(g))  /  10^8
```

and it is non-negative only for `zollstand(g) ≥ −10.000`. At exactly −10.000 that
territory's sector price stops depending on the world price at all, and the excess
function loses the strict part of its monotonicity; below it, that territory's excess
*falls* in the world price while the others rise, and the bisection returns a price that
is not a clearing price. It does so **silently**: T28 runs a fixed 40 steps and has no
convergence test that could fail, so the wrong price is deterministic and reproducible,
which is the property that would carry it into the regression corpus. That is the sharper
statement of the damage than "an index becomes negative" — the gap does not hit a value,
it hits a proof. Bound 8 makes the third premise as checked as the first.

**The domain of number 21 stays open, and the two specifications are not merely silent
but at odds.** The find belongs to the core reviewer, from the review of `0152`:
`spiel.md` writes the formula as `weltpreis_mit_zoll(l, s)`, T48 as
`weltpreis_mit_zoll(g, s)`. This section does not decide that; the reservation at the end
of section 18 stands unchanged and is untouched. What can be said here at no cost:
**the two spellings coincide in value as long as `zollstand(RW) = 0` stands.** The rest
of world's row is then the identity `weltpreis_mit_zoll(RW, s) = welt.preis.<s>`, and the
four-country reading needs exactly that number for the rest of world's price mix, because
T28 blends over five territories (15 `landespreis` addresses per T39, the row in the
`<G>` table of section 4). The wording differs, the number does not. Which of the two is
binding is a question about `spiel.md` and thus the game designer's. Bound 8 does not
hang on the answer: the tariff has 4 addresses either way, and the rest of world has no
instrument address per T15.

### Reports

1. **To the test developer — check 2 grows by one bound**, and it is the only one of the
   eight that runs over the instrument levels: 16 addresses, two comparisons each, against
   `instrument_min[i]` and `instrument_max[i]` from `parameter.toml`. **Bound 4
   (`leitzins[l] + aufschlag ≥ 1`) stays**, although it now follows from bound 8 together
   with the parameter condition `instrument_min[leitzins] ≥ 1 − aufschlag`: a redundant
   check is not thereby a wrong one, and striking it is its own package.
2. **To the vintage build — the `weltlauf` is the mode in which this can actually
   happen.** In `spielmodus` step 3's capping makes a negative tariff unreachable if it is
   built correctly. In the `weltlauf` the instrument levels come from the historical path
   (series 13, tariff level aggregated, WDI/WITS); T51 says the value range holds there
   too and a path that leaves it is „a finding of the vintage build". Bound 8 checks the
   state per round in both modes and therefore catches such a path as well; whether the
   vintage build additionally checks it *before* the run stays where T51 put it. **The
   upper half of the bound stands on a placeholder:** `instrument_max[zoll]` is marked
   `PLATZHALTER` in `parameter.toml`, which notes there that too narrow a value lets the
   historical path leave the range. Until calibration, a red bound 8 on the upper side is
   a question to the parameter and not to the model; on the lower side it never is,
   because `instrument_min[zoll]` is fixed.
3. **To the core builder — no change in `kern/src`.** `weltpreis_mit_zoll`
   (`kern/src/werte.cpp:903`) stays as it is, including its reservation comment, which
   names the **domain** and not the value range and is therefore not closed by this
   section. The core builder's work from this package is nil; the work is the test
   developer's, item 1.

## 24. Die Zielkennung je Aktionsart — Paket `0148`

T32 said what is sorted by and left open **which set** the target id runs over per kind.
Package `0146` built the order and expressly did not fill that gap. T32b fills it: five
lines, and the derivation of each stands here.

### The one root of all five lines

**The Zielkennung is not a new order — it is an existing one, named.** T9 demands a fixed
index order and forbids anything whose iteration order is a property of the memory. For
each of the three kinds that have a target, the state already carries exactly one such
order, and T55/T56 guard it with `static_assert`s against the block boundaries. Writing a
second order beside it would be the same mistake T15 refuses for `landespreis`: a second
copy of one number is an opportunity to let the two drift apart. So each line below names
an order that is already checked, and none invents one.

### Line by line

**1 Position.** `spiel.md`, *The actions*, the sentence whole: long or short "on a
country×sector, on a currency, on a country's government bond, or — since 2026-09-05 — on
an **exchange venue** (see *Die drei Schichten der Welt*)". **Four target classes, and this
document holds three of them.** T16 turns those three into twenty fixed slots, T55 into
`LAENDER·(SEKTOREN+2)`. The order is the slot ordinal — grouped by kind, country-major
inside each group. The fourth class has no slot here yet; where its slots go when the layer
arrives stands in *What the fifth country and the exchange venues change* below, and until
then the table's size column counts three blocks and not four. What `spiel.md`'s sentence
settles is that this set belongs to kind 1 and to **no** other kind; that it has exactly
twenty places is T16's statement, not the sentence's, and the two are not interchangeable.

**2 Stake.** `spiel.md`: "A permanent share in a country×sector." T15 books 24 addresses
as `LAENDER·SEKTOREN` stakes of two fields. The pair is **one** target with two fields, not
two targets: the remaining exit duration is bookkeeping of the exit that the settlement
writes, not something the action chooses. The rest of world carries no stake block —
neither T15 nor the address arithmetic knows one — so the set runs over playable countries,
`0 … LAENDER-1`, exactly as T9's index rule prescribes for every loop over countries.

**3 Lobby budget.** `spiel.md`: "Money on one policy instrument of one country, in one
direction." The target is the **pair**; the direction is the sign of the Stufe and not part
of the id, otherwise the same target would carry two ids and the order would have a tie
that T32 forbids. The set is `LAENDER·INSTRUMENTE`; the rest of world has no instruments
(T15) and therefore no place in it. The order is the instrument block's own order inside
the country block.

**4 Leverage.** The state carries `fonds.hebelstand`, one address in the fund's aggregate
block (T15). Leverage occupies no slot and has no per-country address; the set has one
element and the place of that element is 0.

**5 Visibility.** Same shape, `fonds.sichtbarkeit` — and the contradiction the package
names is resolved below rather than left standing.

### Kind 5 — the contradiction, resolved out of `spiel.md` itself

The brief: *The actions* has the fund "publicly disclose a position" and says disclosure
"amplifies every lobbying budget on that matter", while the state carries a single number.
Either visibility has no target, and "on that matter" is without object — or it has one,
and the addresses for it are missing.

**Three passages of `spiel.md`, each a reading site and each global** (line numbers as of
2026-09-08):

1. *The state*, line 463: "cash, positions, stakes, leverage level, **global** visibility,
   investor base" — the word stands in the state's own list.
2. Counterforce 1, line 1640: the counter rises by an amount "following from global
   visibility **times local footprint** (influence times position share in the sector)".
   The locality of the effect is produced **at the reading site**, out of quantities that
   have addresses of their own. That is precisely what a target on the action would
   duplicate.
3. *Die drei Schichten der Welt*, line 1518: "An exchange venue feeds no supervision
   counter. Counterforce 1 reads global visibility …" — a second reading site, same
   reading, written after the layer was added.

**And the counter-check, which is what makes this a resolution and not a preference:** the
word *visibility* stands on ten lines of `spiel.md` (419, 463, 510, 774, 775, 1089, 1518,
1640, 2671, 2939; measured 2026-09-08). **Not one of them is a computation rule that reads
visibility per instrument or per slot.** The amplification of lobby budgets appears in the
action's description and in no rule of step 3. A negative count is worth only its search
term, so it was run a second time on the effect's own vocabulary — *disclos·*,
*Offenlegung*, *public pressure*: three hits, of which line 420 is the action description
itself and the other two (240, 1235) speak of disclosed data series. Together with line 1089 — "lobby, leverage
and visibility occupy none" — the state and the rules say the same thing, and only the
description says otherwise.

**Therefore: kind 5 has no target, T32b line 5 stands, and the number 310 is untouched.**

**What is left over belongs to the game designer and is reported, not decided here.** The
half-sentence describes an effect no rule computes. Two ways out, both his: it is dropped
as a leftover of the description — then nothing here changes — or it becomes a rule, and
then the cost depends on the reading. Global (visibility enters step 3 the way it enters
counterforce 1): no address, no change to T32b. Per instrument: `LAENDER·INSTRUMENTE` = 16
new addresses, the number 310, and an ADR on line 5. **The third reading — one address per
slot, twenty addresses, the old section 12 point 4 — is the only one the sentence would
*not* buy**, because it speaks of lobby budgets and not of slots.

### Where the domain is checked, and why not in the type

Three places, in the order in which an action can reach the core:

1. **The generation of the admissible list** (T32, first half) — the only place where the
   domain is *produced*. Everything else compares against it.
2. **T21 `setze`** — an id outside its kind's domain is a rejected command with a reason.
3. **T22 load** — the same, reported as an inadmissible save and **not** as a determinism
   break, because that is what it is.

**Not in the type that carries the order**, and for two reasons that can be checked rather
than believed. First, the rank proof of T32 consists of assertions that compare at the
edges of the value range, `ZIELKENNUNG_MAX` against 0 (`kern/include/kern/aktion.hpp`); a
type that refused every value above 19 would refuse its own proof. Second, the probe corpus
already holds a triple outside its domain: `kern/test/aktion_probe.cpp:189` is
`{Art::Sichtbarkeit, Zielkennung{2}, 1}` (measured 2026-09-08). That line is **right** as
an ordering test and **inadmissible** as a game action, and both stay true only as long as
the ordering type carries no domain. The other eleven entries of that list happen to lie
inside their domains; that is coincidence and does not become a rule here.

### What the fifth country and the exchange venues change

- **The lines are formulas, so the numbers change and the lines do not.** At `L = 5` the
  three sets become 25, 15 and 20; the `static_assert`s T56 demands already guard the
  constants they are made of. That is the whole reason they are written as formulas.
- **But the ids change their meaning, and that is not visible from T56.** At `L = 5`,
  Zielkennung 12 of kind 1 is no longer the currency USA but a sector slot. Per T32 the
  canonical order is part of the interface version: **the package that raises `LAENDER`
  raises `schema_version`** (T21, T22). Without that, an old save replays with silently
  different targets — the cheapest way in this whole document to lose the regression
  corpus.
- **The exchange-venue layer is not in this document** (`spiel.md`, *Die drei Schichten der
  Welt*: `5·B` addresses, one position slot per venue). When it arrives, its slots belong
  **behind** the bond block as a fourth block. Any other position renumbers every existing
  slot id, which per T32 needs an ADR and devalues the corpus. That is a rule for the
  package that brings the layer, not an address decision taken here.

### Reports

1. **To the game designer — one half-sentence, above.** "Amplifies every lobbying budget on
   that matter" is an effect without a rule. Global, per instrument, or struck: the choice
   is his, and only the middle one touches this document.
2. **To the core builder — no code in this package, and one comment.** The admissible-list
   generation (T32 first half, its own package) reads the five lines. `kern::aktion` stays
   as built, expressly including `ZIELKENNUNG_MAX` and `aktion_probe.cpp:189`. The header
   comment there reports the domain as missing from the specs; it may now cite T32b
   instead. That is one comment, not a rebuild.
3. **To the project manager — the `schema_version` sentence must travel with the
   fifth-country package.** It follows from T32b, not from T56, and whoever reads only T56
   will not see it.

## 25. Where the value range of an address is checked — Paket `0177`

The question is not about one address: does the value range of a quantity belong to the
place at which it enters the state, or to the place that reads it? It becomes unavoidable
as soon as there is a way from outside in — the `daten` box of T13, the save of T22. T18b
answers it; the derivation stands here.

### The measurement this comes from

`zustand::Startbelegung::setze` takes every `i64` for `partie.runde`. Measured 2026-09-06
(`befunde/raender/bruch-2026-09-06.md`, finding 2, situations 2 and 4): the −1 and the
smallest `int64_t` go into the state without a word and are read back from it unchanged.
The impossible round number is noticed one step later, in `kern::schritt::schritt`.

**And `partie.runde` did not occur in this document at all before this package** — measured
2026-09-08, zero hits before this section. Its bound stood twice in the core and nowhere in
the specs: `kern/src/schreiber.cpp:206` (`welche_runde < 0`) and the two hard errors of
`schritt.hpp` (negative, and largest `int64_t`). Two copies of one bound is the error type
T39 closed for `landespreis` and T45 for the double provenance entry — except that here
neither copy was the master, because there was none. **T18b is that master since `0177`**,
and the two sentences above are the measurement, not the state.

### Why not "the entry checks everything"

That is the counter-calculation, and without it this section would be a rule that costs
more than it carries. `Startbelegung` is expressly the way to set *all* 310 quantities. A
value-range check per address would be a second copy of the eight bounds of T30 check 2 at
a place that owns none of them — 117 addresses, and two places to drift apart. Those eight
have a place and it is the right one: the invariant test, once per round, in both modes.

### Why not "the reader alone", which is the state today

Because `schritt` is not the only reader and has not been for some time:

- `kern/src/zustandsausgabe.cpp` prints the slot under *Partie | Runde* without checking
  it — all three levels of T20.
- The checksum (T12) takes it along like every other quantity. **That is the expensive
  one.** A checksum is a *name* for a state. A state that cannot exist but has a name is
  comparable, citable and reproducible, and every check that compares names answers green
  on it.

Between entry and the first `schritt` there is therefore a state output showing a number
that is not a round, and a checksum over it.

### The cut: the entry checks coordinates, not operands

**The rule in one sentence: the start-value entry checks exactly those addresses on which
the readability of the other 306 depends, and those are the four of the `partie` block.**

The eight bounds of check 2 all have the same victim — a number comes out wrong. A negative
exchange rate turns every profit into a loss, a market basket past the overflow bound
crashes in `tsd_in_cent`, a share above 10,000 is not a share. They are **operands**: they
stand in a formula, the formula computes something false, and the invariant test finds it
in the round in which it happens.

`partie.runde` stands in no formula. It is the **coordinate** under which every
`Ursachensatz` is filed (T18, field `runde`), the number the diff level of T20 subtracts
between two points in time, and the number the round increments. A wrong operand produces a
wrong result; a wrong coordinate produces a result that cannot be filed. The same holds for
the other three: the vintage id says which data the numbers came from, the parameter-set
checksum which rules were computed (T10b), the mandate status whether the game is still
running. Four comparisons once per game, against 310.

**The test that makes this applicable to the next address instead of merely quotable:**
does a value outside the range make a number wrong, or does it make every number
unattributable? First case — the reader and check 2. Second case — the entry as well.

**Why the bound is not `0 … R`.** R is the game length of the vintage (T40), not a property
of the address. Check 6 deliberately runs 200 rounds past the vintage window and marks the
run `ueber_fenster`; a bound at R would turn the boundedness check into a hard error at
exactly the place where it is supposed to measure. The bound is what the round's own
arithmetic can carry: `0 ≤ runde ≤ I64_MAX − 1`. The upper end sits where it is measured to
sit — situation 5 of the finding runs a round on `I64_MAX − 1` through to the end, situation
3 rejects the state it leaves.

**The other three keep their bound open here, and that is deliberate.** The narrow cut is
`partie.runde` — the one address whose bound is measured and already stands twice in the
core. What the rule prescribes for the other three is *that* they get one; *which* one is
written by the package that touches them. Three bounds invented here without a measurement
behind them would be the kind of number this document does not write.

### The consequence for saving and loading — T30 check 3

Two halves, and they point in opposite directions.

**Loading is not a way into the state, so the finding's premise does not hold for this
address.** Per T22 a save is `{schema_version, jahrgang_id, modus, daten_pruefsumme,
parameter_pruefsumme, startwert, aktionen, end_pruefsumme}` — **not the state**. On loading
the game is recomputed from the vintage and the checksum compared. `partie.runde` therefore
never arrives from a file as a state value; it is produced by the vintage build through the
entry and thereafter by the round. The entry check has one caller, not two.

**The one live way in is the vintage build itself.** `partie.runde` carries the provenance
`Entwurf` (T45): its start value is a number in the draft table of `spiel.md`. T45 counts
provenance and does **not** check the value — an address with exactly one entry passes,
whatever that entry says. That is the gap T18b closes, and today it is the only one open.

**The save does carry a round number all the same, in another place, and that one does come
from outside.** `aktionen: [[runde, aktion…]]` — one round index per action record, an
arbitrary number in a file. Its check belongs at T22 load and it is **not** the check from
T18b: the field must equal the round the replay is currently in. A deviation is an
**inadmissible save with a reason, not a determinism break** — the same rule T32b already
fixed for the Zielkennung (section 24, *Where the domain is checked*, item 3), and for the
same reason. A determinism break says "the same input gave a different result", which is a
statement about the program; a save whose action list is not replayable is a statement about
the file. Reporting the second as the first sends the buyer hunting for a platform
difference that is not there.

**What check 3 gains from T18b**, so that nobody reads more into it than stands here: check
3 compares checksums, and a checksum (T12) runs over all 310 `i64` without interpretation.
T18b does not make the comparison sharper. It makes the set over which check 3 compares
exactly the set of states that can exist. That is worth naming, and it is not the same thing
as finding an error.

### Reports

1. **To the core builder — one place, two comparisons, and a follow-up package.**
   `Startbelegung::setze` gets a third hard error beside the index and the foreign write: a
   value outside the address's range, for the four addresses of the `partie` block, for
   `partie.runde` the bound above. **Nothing in `schritt.cpp` and nothing in
   `schreiber.cpp` is struck** — the bars there cover the value the round makes, not the
   value that comes in. No code in this package; the file list under `kern/` belongs to the
   follow-up.
2. **To the test developer — the message has to say which of the two fired.** The three
   messages of the round are distinguished today by their wording; the finding prints them
   in full, and `bricht_ab_mit` holds two text pieces per message (measured, same finding).
   A fourth message from the entry that differs only in the address number would make the
   difference between "start value rejected" and "the previous round's state" unreadable in
   precisely the situation in which someone is looking for it. One of the two held pieces
   should be the one that separates the two places.
3. **To the project manager — the rule has three addresses without a bound.** Vintage id,
   parameter-set checksum and mandate status are in the class and carry no measured bound
   today. That is this package's cut, not an omission; whoever writes the package for one of
   them writes its bound with it.

## 26. One reading of the country count — Paket `0221`

**What this answers, in one line.** `spiel.md` decided nine countries on 2026-09-06
(`L = 9`, `L_R = 7`, `L_S = 2`, `n = 1`); `technik.md` carried the four-country reading as
digits — 16 check subjects, tolerance 2, 31 series — and named no horizon, so the two
documents contradicted each other with neither saying so. Measured by the Datenbauer on
2026-09-07 while building `0220`.

### The reading is `L_R = 4`, and that is `spiel.md`'s own sentence

Not because the nine are in doubt, but because the same addendum that decided them says:

> *"I have not touched `technik.md`, and **no number in it is wrong today**: until 0116 has
> written the address arithmetic parametrically and the data builder has built the vintage,
> `L = 4`, `L_R = 4` and 310 continue to hold."*

(`spiel.md`, section *Was der Architekt neu rechnen muss*, entry *Neu aus Paket 0118*, read
2026-09-08.)

**The horizon, named, because "until 0116" is not a date.** `L_R` leaves 4 when all three
of these have happened, and not before:

| # | Condition | whose | today |
|---|---|---|---|
| 1 | the address arithmetic stands parametrically in `L` — package `0116`, T54/T55 | architect | open |
| 2 | the vintage is built for nine countries — 2,310 values, ten new licence points (T62) | data builder | open |
| 3 | the class of Japan, India and Chile is **derived** at retrieval, per T61 rule 5 / T63 step 1, not assumed | data builder | open |

Condition 3 is why 28 and 3 must not be written as digits today. `spiel.md` calls its own
class assignment *"An expectation with a condition, not a determination"* (`spiel.md`,
section *Was der Architekt neu rechnen muss*, table row **T58 / classes**, read 2026-09-08):
a country is a play-only country already when one of its three policy-path series carries
`stufe = 4` — since package `0196` that is one of three grounds, not the only one. If
`MFS_IR` comes up empty for one of the three, `L_R` is 6, the check subjects are
`3·6 + 5 + 1 = 24` and not 28, and the tolerance stays 3. **A digit written today would be
a determination `spiel.md` expressly withheld.**

### Why a formula and not a second column of digits

Because the count then has **one** place. T59 already counted in `L_R`, T37 counted in
digits, and the two agreed only at `L_R = 4` with no mechanism to keep agreeing — that is
how the divergence of 2026-09-06 could sit unnoticed for two days. From here every count of
the backtest — check subjects, tolerance, free, derived, reported and target series, flows,
target mask — stands as a formula in `L_R`, `S`, `I` and `n` in T59, and every other place
carries either the same formula or its evaluation with the value of `L_R` written beside
it. Moving `L_R` is then one substitution, not a search.

### Which wave the numbers answer

Two waves ran into the same numbers; this package answers **the first**.

| Wave | what it says | answered here |
|---|---|---|
| 1 — the country count (`0118`, 2026-09-06) | `L_R` goes 4 → 7: check subjects 16 → 28, tolerance 2 → 3, target series 27 → 48, flows 40 → 112, target mask 175 → 328 | **yes** — as formulas, plus the `L_R = 7, L_S = 2` column in T59 |
| 2 — series 9 without a target role (`0054`, 2026-09-03) | 31 was the count of the target series and is now that of the **reported** series; 27 are target series | **no** — marked at each place, repaired by `0068` |

Wave 2 is marked and not repaired on purpose: `0068-technikmd-reihe-9-ohne-sollrolle` is
open and holds it as its subject, and doing its work would leave its review nothing to
check. What this package added at those places is a count beside a count, never a struck
word.

### What is deliberately left standing

- **`daten/reihen.toml` is not touched.** Its follow-up is a Datenbauer package over
  `zaehlung.pruefgegenstaende` (`gesamt = 16`, `toleranz = 2`, `beleg = "technik.md T37"`)
  and `zaehlung.sollreihen_gesamt = 27`, plus the comment above each. Their `beleg` is this
  block, so that file can only follow, never lead; and two files written by two roles under
  one `dateien` list make both unplannable.
- **The geometry stays at four.** The 310 and 740, `LAENDER·INSTRUMENTE = 16`, the
  dimensions `4 + RW` in the series list of section 7 — all of that counts addresses, not
  check subjects, and belongs to `0116`. `spiel.md` holds the 310 expressly in place until
  then.
- **The window 1997–2021 and the 25 support points** in T24 are the follow-up of the R cut
  and belong to `0064`.
- **The directional-accuracy addition** `spiel.md` asks for — form it only over the
  transitions in which the target series moves — is **not** written into T42 here. It is
  needed by a target series that never moves, and the only one named is the Saudi exchange
  rate, which under the binding reading is not a target series at all. It falls due with
  condition 1 above, and it is a threshold rule, not a count.

### The check this section can be held to

`Grep` for `16`, `2`, `31` and `27` in T37 and in section 7 finds each of them either as
the evaluation of a named formula with `L_R = 4` beside it, or with the sentence that names
the wave it belongs to. **No number of the nine-country reading stands in this file as
today's state**, and no number of the four-country reading stands without its horizon.

## 27. The class is formed from two sorts of series — Paket `0196`

**What this answers, in one line.** T61 rule 5 derived the country class from the three
policy-path series alone; two grounds for exclusion lie in the **target series**, and the rule
could see neither. Reported 2026-09-06 by the game designer in the run to `0118`, confirmed by
the design reviewer, and left lying twice because both trades write elsewhere. The whole
answer stands in T61 rule 5 and is not repeated here.

**What was decided, and it is one thing.** Not *whether* the two grounds bind — `spiel.md`
had already named both — but **where the class is formed**: before the target roles are
assigned, over the candidate target series, in five ordered steps. T62 footnote 1 reads as a
circle (the role follows the class, the class follows the series that carry the role) and
dissolves into an order. That is the sentence the finding needed and neither of the two
reporting trades could write.

**Three reports, because they belong to other trades.**

1. **To the game designer:** the open question *„Whether the class rule from T61 rule 5 sees
   the exclusions that lie in the target series"* is answered and can be struck. Its own
   sentence — *„Belongs to T61"* — is now redeemed.
2. **To the game designer, second:** the addition to Maß 4 that `spiel.md` asks for
   (directional accuracy only over the moving transitions) is by this rule no longer
   **reachable**: after step 2 of the order no target series of a built vintage is constant
   over the window. It remains right as the closing of a gap, and section 26 keeps it lying
   for condition 1 there. It is not written into T42, here as little as there.
3. **To the data builder:** `daten/reihen.toml` needs **no** new field. Condition c is
   measured on the values, b on `[[reihe.deckung]]`, a on `[[reihe.herkunft]]` — all three
   blocks exist. What is new is only that the vintage build reads the coverage of the target
   series *before* it assigns the class.

**What is deliberately left standing.** T62 conclusion 2 and T63 are unchanged: T63 step 3
(stage 4 → play-only country) stays a sufficient condition and stays true; it was never an
exclusive one. Rule 4 stays word for word, now unreachable. The class of a single country
stays in `spiel.md`, and the retrieval that decides Japan, India and Chile stays the data
builder's. The peg as a model quantity stays the operator's decision — condition c is written
so that it stops firing on its own once the peg exists, and that is the only place where this
section takes a future into account.

**Four clauses outside T61 that this package moved, three of them named in its acceptance and
the fourth caused by it.** Section 25's measurement paragraph and the T18b pointer are the two
corrections from the review of `0177`; the `spiel.md` quote in section 26 got its read date
from the review of `0221`. The fourth is mine and was not in the acceptance: section 26 stated
the old rule 5 as *„exactly when"*, which this package makes false — it now reads „already
when", with the ground count beside it. Whoever calls that overreach strikes half a sentence. The
project manager weighed it on 2026-09-08 and let it stand (review of `0196`, finding 3): it is
disclosed here in the same form as the three above — place, old wording, cause — and that
disclosure, not the acceptance list, is what makes such a clause checkable.

**The check this section can be held to.** `T6[0-2]` on this file, measured with the same
call before and after the run: `grep -c` counts **lines** and gives **33** at the start, **48**
at the end. All fifteen new lines lie in T61 rule 5 (six) and in this section (nine); outside
those two places the count is unchanged. A tool that counts **matches** instead of lines gives
one more at either end, **49** today, because one line carries two of them. No number outside
T61 has moved.

## 28. Check 6 names its mode — Paket `0158`

The decision and the two reports it produces. The rule itself stands where it is read, under
T30 in section 9; this section carries only what does not belong in a rule.

**Decided: check 6 is the `weltlauf`.** Three grounds, in the order of their weight —
„ohne Spieler" is the definition of that mode (T38); it is the only mode that runs today;
and constant inputs after the window make a runaway attributable to the model. The losing
reading stands written beside it with its price, because a decision whose alternative is
not stated cannot be reopened by anyone but its author.

**What this package deliberately does not decide:** whether the `spielmodus` gets built,
and when. That is a package of the project manager's, and the decision above is written so
that it survives either answer — bounds 5, 6 and 7 stay outside check 6's reach in the
`weltlauf` even after steps 2 and 6 exist.

**Report 1 to the project manager — no check measures boundedness over a long horizon.**
Bounds 5, 6 and 7 are reachable only in a `spielmodus` run, and every such run is `R` = 24
rounds long (checks 1, 4, 5, 7). Check 6 is the only one with 200 rounds and is blind to
exactly those three. So the question *does the fund block, channel 8 or the basket value run
away over 200 rounds* is asked by nobody. Whether the answer is a second boundedness run in
the `spielmodus`, a longer bot game in check 5, or the deliberate acceptance of the gap, is a
package and not a sentence here. **The gap is named, not closed** — a green check-6 report
today says nothing about these three bounds, and that sentence belongs in the report.

**Report 2 to whoever builds the `daten` box — the route of a path value into the round is
open.** T10b binds one carrier for the numbers of a round that are not addresses, and an
exogenous path value at round `t` is such a number. Whether it travels in that carrier, whose
`Runde(feld)` fields the round checksums against `partie.parameter_pruefsumme`, or beside it,
is a signature question that T10b's own rule already governs (a `const` carrier needs no ADR,
a removed or non-`const` argument does). It is not decided here, because this package may not
widen `schritt`. What **is** decided here and binds that package: the clamp `min(t, R)` sits
in the accessor, once, and not at each caller.

**What is deliberately left standing.** The bounds table under T30 is untouched — the three
affected rows keep their wording, because the blindness is a property of the check and not of
the bound. T38's mask table, its 175/135 split and the eight bounds themselves are untouched.
Check 5 keeps its 10,000 games and its `R` rounds; making it longer would be report 1's
package, not this one.

**The check this section can be held to.** `ueber_fenster` had two occurrences in this file
before the run, both in it and none anywhere else in the venture, and after the run it has
more — that is the point. The number that must hold instead: `grep -c 'ueber_fenster'` over
`kern/`, `daten/` and `parameter.toml` gives **0** before and after; this package writes a
rule, not code.

## 29. Der R-Nachzug ausserhalb der T-Blöcke — Paket `0064`

**What this answers, in one line.** `spiel.md` cut `R` from 24 to 20 on 2026-09-03
(package `0054`, window 2001–2021, 21 support points) and named the places in this file in
two catch-up tables. Ten governing places stood in **neither** table; nine of them lie
outside a T-block or in a T-block no table row names. Nine are substituted here, one is
disputed.

### The nine substitutions, each computed from `R = 20` and not scaled

| # | Where | now stands | computed from |
|---:|---|---|---|
| 1 | frontmatter, key `nachtlauf` | 9,759,420 world steps, 1.6 / 8.1 min | `9.539.200 + 200.000 + 200 + 20 + 20.000`; times 10 and 50 µs |
| 2 | T22, save cost | 0.20 ms | `R` world steps × 10 µs |
| 4 | T44, third line of `B` | 21,000 | `(R+1) × 1.000` |
| 5 | T44, band of the running case | `21.000 ≤ B ≤ 24.000`, mandate band to 20,000, gap edge 23,001 → 24,001 | `(R+1) × 1.000` + `e ≤ 2.000`, `R × 1.000`; death band 31,000 does not hang on R |
| 6 | T44, cost note | 1,220 and `60 · 210 + 20 = 12.620`, ten times | `R × 61`; `Σ(R+1−t) = R(R+1)/2 = 210` |
| 7 | search-bot bullet | 1,220 | `R × 61` |
| 8 | section 10, eight cores | 12 s and 1.0 min | 9,759,420 ÷ 8 × 10 resp. 50 µs |
| 9 | section 10, counter-calculation to Python | 2.0 to 8.1 hours | 9,759,420 × 0.75 and 3 ms |
| 10 | section 12, depth 2 | `20 × 3.661 = 73.220`, 554 million, 1.5 h / 12 min / 58 min | `R × (1 + 60 × 61)`; `3 × 126 × 20 × 73.220 = 553.543.200` |

Two numbers the proposal did not name and this run computed: depth 2 on eight cores is
**12 minutes** at the plan value (5,535 s ÷ 8) and **58 minutes** in the unfavourable case
(27,677 s ÷ 8), replacing 14 minutes and 1.2 hours.

### Place 3 — disputed, not carried out

The proposal wanted T37's sentence *„Berichtet werden alle 31 Reihen plus die 40 Ströme"*
set to **27**. It stays at 31, on three grounds. **First:** since package `0221`
(2026-09-08) the sentence counts the **reported** series and says so — 31 is
`L_R(S+5) − n`, the target series are `L_R(S+4) − n` = 27 and stand named beside it in the
same sentence. **Second:** neither number is formed from `R`; both are formed from `L_R`,
`S` and `n`, so the R cut does not touch them. **Third:** the residual wording *„target
series" for all 31* is expressly the property of `0068-technikmd-reihe-9-ohne-sollrolle`;
section 26 assigns it there and says why. Writing 27 into that spot would take a review
from `0068` and would contradict T59.

### The second pass over every number — what stays, and why

`Grep` over the whole file for `24`, `25`, `1.464`, `9.024`, `18.024`, `87.864`,
`11.519.040`, `11.783.264`, `31` and `1997`. `18.024` and `87.864` have no occurrence left.
Every remaining one falls into one of four groups:

| Group | Reason | Where |
|---|---|---|
| **A — catch-up table of `spiel.md`, own package** | named in one of the two tables, thus deliberately not this package's | frontmatter key `partie` (1.464, R = 24); T40's example column „bei R = 24" (24,000 / 25,000…28,000 / thirds / 1,464 / 9,024 / `1999 − 1997 + 1`); T24 (25 support points, window); T42 (`S` = 25); T43 (24-round game); T34 range test (54,000); section 10's whole table **and** its recount row (24, 1,464, 9,024, 11,519,040, 11,783,264) and the calibration loop; section 13 (1997, 25, 31); the order-of-magnitude line `5 × 25 × 30` and `40 × 25 × 8`; „For the window 1997–2021 this is without consequence" in T40 and in section 12 point 1 |
| **B — record or quote of an older version** | sections 14 to 16, marked under condition 3 above | §15 „R stays 24 … 11,519,040 … 11,783,264 … 25 support points"; §12's struck query „acceptance over 31 or 23 series"; T44 „in version 4 the third line still carried the literal `25.000`"; T8's Brazil passage („per `spiel.md` version 3 in the year 1997"); the shift 1995 → 1997 in T25 |
| **C — not formed from R** | the R cut cannot move them | death band 31,000 (`30.000 + 1.000`, independent of R per T40); the 31 reported / 27 target series (formed from `L_R`, `S`, `n` — see place 3); 25 person addresses and the scale decomposition; 24 stake addresses (`2·L·S`); HS92 chapters 01–24 / 25–97; 24 `mal_geteilt` in `beteiligung_wert`; `3·6 + 5 + 1 = 24` check subjects at `L_R = 6`; the Maß-3 threshold 25 %; cross-references to sections 24 and 25; source-line counts; the commit time 05:24 |
| **D — measured, with a retrieval date** | a re-measurement is a data job, not arithmetic in R | the trade-block price drift over „the 25 support points of the check vintage" (2,203 ten-thousandths) and the 1997 base of that index; `NE.EXP.GNFS.KD` for China, „the other 24 support points are `null`" (retrieved 2026-09-04); „Brazil from 1997" in the `FR.INR.LEND` case. Their window is the old one; whoever re-cuts it must query, not scale |

### Five reports to the project manager — found, and expressly not touched

1. **Three places carry R = 24 that arose after 2026-09-04 and stand in no list** — neither
   in the two catch-up tables nor among the ten. All three from package `0158`: section 9
   *„they run over `R` = 24"*, section 28 report 1 *„every such run is `R` = 24"*, and
   section 9 *„At R = 24 the support points cover rounds 0 … 24, so rounds 25 … 200 are
   outside the window — 176 of 200"*. At R = 20 the last one is rounds 0 … 20 and
   **180 of 200**; the neighbouring 175/176 question stays as section 28 leaves it.
2. **T34's two unreachable gaps** — *„24,001 … 24,999 and 28,001 … 30,999 at R = 24"* — are
   formed from R, stand in neither table and in neither list. At R = 20 they are
   20,001 … 20,999 and 24,001 … 30,999.
3. **Section 21 declares a question open that `spiel.md` decided.** It writes *„The choice
   between the two ways out … belongs to the game designer"* and *„This section does not
   resolve the point"*. It was resolved on 2026-09-03: `spiel.md` frontmatter, *„R = 20
   rounds, start state 2001, end state 2021, 21 support points"*, and the section *The
   decision: R = 20, window 2001–2021, 21 support points*, which calls 2001 **forced**. The
   section's two-column table stays useful; the sentence that the choice is open does not.
4. **A scope contradiction over T24, and only the project manager can settle it.** T24 says
   *„The window and the 25 are the follow-up of the same cut and belong to `0064`"*, and
   section 26 repeats it. But T24 is a **row of the first catch-up table**, and this
   package defines its scope as exactly the places that stand in neither table; condition 1
   does not list T24. I have therefore not touched it. Whoever settles it moves one
   sentence, not a number.
5. **Most rows of the two catch-up tables have no package at all.** Only
   `0068` holds one row. Section 10's table, the frontmatter key `partie`, T40's example
   column, T34, T42, T43 and section 13 are named in `spiel.md` and owned by nobody. As long
   as that is so, this file states two different `R` in its own frontmatter — key `partie`
   24, key `nachtlauf` 20 — and that is visible on purpose.

**And one name collision, noticed while counting and outside every scope here:** `S` means
the three **sectors** in T37 and T59, and the **support points** (25, per the table above
21) in T42. Two quantities, one letter, four hundred lines apart.

### The check this section can be held to

`Grep` for `18.024` and `87.864` in this file gives **zero** hits. `Grep` for `1.464` and
`9.024` gives hits only in the frontmatter key `partie`, in T40's example column and in
section 10's table and recount row — that is, exclusively in group A. Every hit of `24` and
`25` outside those places falls into B, C or D above, or is one of the five reports.
