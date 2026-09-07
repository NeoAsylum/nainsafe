---
typ: technik
idee: 0016-hedgefonds-simulation-echte-weltwirtschaft
erstellt: 2026-09-01
fassung: 7, nachgebessert am 2026-09-03 gegen die drei Befunde der Runde 1 zu Paket 0011 (Abschnitt 16) und am 2026-09-04 gegen Paket 0026-klasse-2-preisbasis (T53, Abschnitt 17), dort in drei Läufen -- der zweite hat die Zahlen von T53 nachgerechnet und drei Stellen berichtigt (Umfangsliste in Abschnitt 17, zwei abgeschnittene Zahlen in T53), der dritte hat sie ein zweites Mal unabhängig gerechnet (keine Abweichung) und die Herkunft von N im durchgriff-Absatz von T53 vervollstaendigt (Reihe 1 mal Reihe 2 statt Reihe 1); die Entscheidung selbst ist unverändert; die Fassung folgt ADR 0011 und ventures/0016-.../aufgaben/0011-stack-auf-cpp.md, ausschliesslich die Stellen, die an der Sprache hängen; der Inhalt der Fassung 6 steht unverändert -- und am 2026-09-04 gegen Paket 0043-t48-groessen-gegenkraft-5 (T48 waechst von 17 auf 22 Groessen, T50 und Abschnitt 12 Punkt 3 sind geschlossen, Abschnitt 10 bekommt die Kostenzeile von Gegenkraft 5; Abschnitt 18)
preisbasis: Klasse 2 steht zu konstanten Preisen des Jahres 2015 (gemessen an Reihe 1, WDI "constant 2015 US$"); die 40 BACI-Handelsströme kommen laufend an und werden beim Jahrgangsbau mit einem Weltausfuhrpreisindex aus WDI darauf gebracht -- 0 Rechenschritte je Weltschritt, 0 zusätzliche Sollreihen, T47/T48/T50 unberührt (T53)
stack: C++20, übersetzt mit g++, Version in werkzeugkette.cmake festgenagelt, Bau über CMake, jede Fremdbibliothek als Quelltext unter fremd/ im Repo eingefroren (find_package und FetchContent verboten); Kern ohne jede Fremdabhängigkeit und ohne Gleitkommatyp; Oberfläche vertagt (ADR 0010)
ueberlauf: -fwrapv in jedem Profil, -fsanitize=undefined,address im Testprofil, __int128 für jeden Zwischenwert -- dazu geprüfte Arithmetik im Kern, nach Rechenart geschnitten (Verengung, Strichrechnung, Multiplikation ohne Division), weil -fwrapv genau die Überlaufprüfung des Sanitizers abschaltet (T7)
determinismus: i64-Festkomma mit deklarierter Skala je Größenklasse, feste Iterationsreihenfolge über Indexlisten, ein Wurzelstartwert mit abgeleiteten Strömen, Weltschritt ohne jede Ziehung
zustand: fester, allokationsfreier Wert, 310 i64 (2.480 Byte), Prüfsumme über kanonische Byteform
speicherstand: Jahrgang, Modus, Startwert, Aktionsfolge und Prüfsumme -- nicht der Zustand
kalibrierung: alle Zahlenwerte in einer Parameterdatei ausserhalb des Codes, mitgehasht
partie: R Runden, R ist eine Größe des Jahrgangs; im Prüfjahrgang 1997-2021 ist R = 24, eine Suchbotpartie kostet R × 61 = 1.464 Weltschritte
fondsvermoegen: Kasse + bewertete Positionen + bewertete Beteiligungen - Hebel, Beteiligungen zum Ausstiegswert; genau eine Funktion im Kern, gelesen von Abrechnung, Mandat, Todesart 1, Invariantentest und B (T47)
skalen: dreizehn Klassen, zwölf davon mit Zustandsadressen; jede der 310 Adressen trägt genau eine -- 3 Fondsgeld, 71 volkswirtschaftlich, 36 Raten, 22 Anteile, 22 Nominalindizes, 5 Wechselkurs, 5 Realindizes, 25 Personen, 32 Lobbydruck, 4 Instrumentenstufe, 83 Zähler, 2 Kennungen (T49)
skalenuebergaenge: genau drei, je eine benannte Funktion an genau einem Ort -- tsd_in_cent (Bewertung), lobbypunkte_aus_geld (Aktion 3), lobbypunkte_aus_schaden (Gegenkraft 5); cent_in_tsd hat keinen Aufrufer und gibt es nicht (T50)
abgeleitet: 22 Funktionen des Zustands im Kern (17 bis zum 2026-09-03, dazu die fünf aus dem Schaden in Gegenkraft 5 und dem Zollkeil), 3 im Prüfstand, abschliessend aufgezählt; ein Name in einer Formel, der weder Adresse (T15) noch Parameter (T27) noch Jahrgangskonstante (T23) noch abgeleitete Größe ist, ist ein Befund (T48)
suchbot: Zielgröße B nach T44 -- statische Ergebnisprognose des Zwischenzustands, im Zweig "überlebt" formelgleich mit der Ergebnisgröße von spiel.md, ohne freien Parameter
herkunft: jede der 310 Adressen trägt genau einen Herkunftseintrag aus fünf Arten; 136 Datenanker, 150 Entwurf, 11 Parameter, 2 Manifest, 11 Vorgabe (T45, T46) -- eine Lücke oder ein zweiter Eintrag bricht den Jahrgangsbau ab
tick_planwert: 10 Mikrosekunden je Weltschritt (Bandbreite 5 bis 30) -- geschätzt, nicht gemessen; es gibt noch keinen Kern
nachtlauf: 11.783.264 Weltschritte, 2,0 Minuten auf einem Kern beim Planwert, 9,8 Minuten im ungünstigen Fall
---

# Der Kern ist eine reine Ganzzahlfunktion ohne Ziehung -- damit ist Determinismus keine Disziplin, sondern eine Eigenschaft des Bauprofils.

Siebte Fassung, gegen `ventures/0016-.../aufgaben/0011-stack-auf-cpp.md` und **ADR 0011**.
Sie tauscht **die Bauart und sonst nichts**: Zustandsaufbau, 310 Adressen, dreizehn
Skalenklassen, Formeln, Herkunftseinträge und Jahrgangskonstanten stehen unverändert, weil
nichts davon an einer Sprache hängt. Berührt sind T1 bis T15 in Abschnitt 1 bis 4 und die
Stellen weiter hinten, die ein Sprachmerkmal beim Namen nannten.

Die Vorfassung begründete den Determinismus damit, dass er sich in Rust **vom Werkzeug**
erzwingen lasse. Der Betreiber hat am 2026-09-01 C++ entschieden, und die Überschrift oben
ist deshalb um ein Wort geändert: Was in Rust das Typsystem trug, tragen hier das Bauprofil
und drei Prüfregeln — die Gleitkommasperre (T4), die geprüfte Arithmetik (T7) und die
geordneten Behälter (T9). **Das ist der Unterschied, der beim Lesen wichtig ist:** Jede
dieser drei ist mechanisch nachweisbar, aber keine ist geschenkt. Wo die Vorfassung eine
Spracheigenschaft nannte, nennt diese eine Prüfung — und sagt dazu, was sie *nicht* deckt.

Die Abarbeitung der Prüfung zu `0001-entwurf-abnahme` steht am Ende der Datei und ist von
diesem Lauf nicht berührt. Die Abarbeitungen der ersten vier Prüfungen standen in den
Fassungen 2 bis 5 und sind dort je von der nächsten Prüfung unter deren Bedingung 5
abgenommen worden; sie stehen im Git-Verlauf und werden hier nicht wiederholt.

Die Vorgaben sind mit **T1** bis **T53** durchnummeriert. Der Builder weicht von keiner ab,
ohne dass ein ADR sie aufhebt; der Prüfer zitiert die Nummer, statt sie zu umschreiben.
**Die Nummern behalten über alle Fassungen ihre Bedeutung**, damit alle Prüfungen
zitierbar bleiben; neue Vorgaben tragen die nächsten freien Nummern und stehen dort, wo sie
inhaltlich hingehören. Die Nummerierung ist deshalb innerhalb der Abschnitte nicht
fortlaufend.

**Zwei Vorgaben tragen in dieser Fassung einen Buchstaben — T2b und T6b.** Sie sind keine
neuen Regeln, sondern die C++-Hälfte einer bestehenden: T2b sagt, was an die Stelle von
`#![forbid(unsafe_code)]` tritt, T6b schreibt die Divisionsform vor, an der die
Geschwindigkeitsmessung aus ADR 0011 hing. Ein Buchstabe statt einer neuen Nummer, damit die
Prüfungen der Runden 1 bis 6 zitierbar bleiben und niemand T2 gegen T60 nachschlagen muss.
Wirklich neu war in der Fassung 7 allein **T52** (Plattformunabhängigkeit der
Ganzzahlrechnung), und die Vorfassung brauchte sie nicht, weil Rust sie geschenkt hatte.
**T53** ist am 2026-09-04 mit Paket `0026-klasse-2-preisbasis` dazugekommen und steht hinter
T50, weil sie zu den Skalen gehört und nicht zur Sprache (Abschnitt 17).

**Die teuerste Lehre der Fassung 6, unverändert gültig: Der Abzählschritt aus T45 zählt
Adressen, und Befund 2 der Runde 6 lag zwischen zweien.** Die gemischten Skalen in
`beteiligung_wert` waren keine fehlende Adresse und keine fehlende Zahl, sondern eine
**fehlende Einheit an einer vorhandenen Größe**. Fassung 6 hat deshalb dieselbe Prüfung, die
Fassung 5 für die Herkunft von Hand ausgeführt hat, für die **Skala** ausgeführt — und dabei
gefunden, dass
T5 von sich sagt, die Bedeutung stehe „in dieser Tabelle und nirgends sonst", während **69
der 310 Adressen** in keiner ihrer Zeilen vorkamen: 25 Personengrößen, 5 Produktivitäten,
4 Regulierungsstände, 32 Druck- und Gegendruckfelder, die Sichtbarkeit des Fonds und die
beiden Kennungsfelder.

Die 32 Druckfelder sind darunter der teure Fall, und sie sind wörtlich Befund 2 ein zweites
Mal: Der anliegende Druck entsteht aus dem **Lobbybudget des Fonds** (US-Cent), der
Gegendruck aus dem **Schaden eines Sektors** (Tausend USD), und `spiel.md` verrechnet beide
in Schritt 3 gegeneinander. Ohne erklärte Einheit hätte der Bauagent zwei Skalen addiert,
die um den Faktor 100.000 auseinanderliegen — und diesmal hätte es nicht wie ein
Rechenfehler ausgesehen, sondern wie eine Gegenlobby, die nie greift.

Die Antwort sind **T49** (jede der 310 Adressen trägt genau eine Skalenklasse, abgezählt),
**T50** (die Skalengrenzen werden von benannten Funktionen an genau einem Ort überquert) und
**T48** (die abgeleiteten Größen, die keine Adresse sind, abschliessend aufgezählt — die
Menge, in der Befund 1 lag). Dieselbe Bauart wie T40, T44 und T45: nicht die fehlende Zahl
nachtragen, sondern die Stelle schliessen, an der sie fehlen konnte, und die Zusage einer
Tabelle dadurch prüfen, dass man sie einmal von Hand einlöst. Beide Summen gehen auf:
`3 + 71 + 36 + 22 + 22 + 5 + 5 + 25 + 32 + 4 + 83 + 2 = 310` neben
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

**T20 — Drei Abfragen, zwei Ausgabeformen, eine Quelle.** Jede Ebene entsteht aus
demselben Datentyp und wird entweder als Text (für Menschen und Logbücher) oder als
JSON-Zeile (für Agenten und Oberfläche) ausgegeben. Ganzzahlen bleiben Ganzzahlen; die
Skala steht im Kopf der Antwort, geteilt wird erst in der Sicht.

- **`uebersicht`** — eine Zeile je Gebiet, eine je Fonds, eine für den Markt:
  `DE | BIP 3.412 | Zins 250bp | Zoll 380bp | Haushalt -210bp | Fondsanteil 420 | Einfluss 1.700`
- **`detail <adresse>`** — ein Objekt vollständig, für **jede** adressierbare Einheit nach
  T17, nicht nur für Länder: `land.US`, `fonds`, `land.BR.instrument.zoll`,
  `land.CN.sektor.1`, `markt`.
- **`diff <von> <bis>`** — je geänderter Größe alt, neu, Änderung **und die Ursachenkette
  aus T18**, rückwärts aufgelöst bis zur auslösenden Aktion oder Gegenkraft, mit
  Verzögerung und Beitrag je Glied. Der Unterschied zweier Zustände sagt *was*, die Kette
  sagt *warum*; ausgegeben wird beides, massgeblich ist die Kette.

## 6. Maschinenschnittstelle und Partieformat

**T21 — Ein Befehl je Zeile, eine JSON-Antwort je Zeile, über Standardein- und -ausgabe.**
Kein Netzdienst, kein Anschluss, keine Zugangsdaten — damit auch keine Berührung mit
Hausregel 2. Befehle: `neu {jahrgang, modus, startwert}`, `zustand {ebene, adresse}`,
`aktionen` (die zulässigen dieser Runde), `setze {aktionen: […]}`, `runde`,
`kette {von, bis}`, `speichern {pfad}`, `laden {pfad}`, `pruefsumme`.
Jede Antwort trägt `schema_version`. Eine mitgeschriebene Sitzung ist damit von selbst
eine Testvorlage.

**T32 — Die Liste der zulässigen Aktionen hat eine kanonische Ordnung, und sie ist Teil der
Schnittstellenversion.** Sortiert wird nach `(Aktionsart 1…5, Zielkennung, Stufe)`; die
Zielkennung ist die feste Indexordnung aus T9. Grund: Maß 1 zieht nach `spiel.md` Aktionen
**ohne Zurücklegen aus der Liste der in dieser Runde zulässigen Aktionen** (T35). Wäre die
Ordnung eine Nebenwirkung der Erzeugung, hinge die Entscheidungsdichte an einer
Schleifenreihenfolge, die niemand aufgeschrieben hat. Die Ordnung ändern entwertet den
Regressionsbestand und braucht einen ADR.

**Die Liste wird einmal je Runde gegen den Rundenanfangszustand gebildet**, nicht nach jeder
gesetzten Aktion neu. Nach `spiel.md` hat keine Aktion einen Zeitpunkt innerhalb der Runde;
eine Liste, die sich zwischen zwei Steckplätzen ändert, würde genau diesen Zeitpunkt
einführen. Was ein Bündel als Ganzes betrifft — derselbe Steckplatz zweimal, Kasse
überzogen, mehr als drei Aktionen —, prüft `buendel_zulaessig(zustand, buendel)` gegen
denselben Rundenanfangszustand. Zwei Prüfungen, beide zustandsfrei innerhalb der Runde.

**Zwei Zulässigkeitsbedingungen kommen mit `spiel.md` Fassung 5 hinzu, und beide folgen aus
der Anteilsskala.** Eine Aktion 1 oder 2, nach der `fondsanteil(l, s)` über **10.000** läge,
ist unzulässig — ein Anteil über hundert Prozent ist kein Anteil, und Gegenkraft 1 und der
Preisstoß lesen genau diese Zahl. Ebenso unzulässig ist eine Aktion, nach der
`|stufen(p)| > stufen_max` wäre. Beide werden **im Bündel** geprüft, nicht je Aktion: Drei
Aufstockungen desselben Steckplatzes in einer Runde sind einzeln zulässig und zusammen nicht.
Der Invariantentest (T30 Prüfung 2, Schranke 7) prüft danach, dass die Zulässigkeitsprüfung
gehalten hat — die Prüfung schützt den Spieler, der Test schützt vor der Prüfung.

**T22 — Ein Speicherstand ist Jahrgang, Modus, Startwert, Aktionsfolge und Prüfsumme, nicht
der Zustand.** Datei: `{schema_version, jahrgang_id, modus, daten_pruefsumme,
parameter_pruefsumme, startwert, aktionen: [[runde, aktion…]], end_pruefsumme}`. Beim Laden
wird die Partie nachgerechnet und die Prüfsumme verglichen; weicht sie ab, meldet das
Programm einen Determinismusbruch, statt weiterzuspielen. Drei Gewinne auf einmal: Der
Käufer bemerkt einen Determinismusfehler zuerst, der Regressionsbestand **ist** der
Speicherordner, und eine Datei bleibt unter zwei Kilobyte. Kosten: R Weltschritte beim
Laden, bei R = 24 also 0,24 Millisekunden.

## 7. Datenschicht

**T23 — Der Jahrgang ist ein Erzeugnis, kein Programmteil.** `werkzeuge/aufbereitung`
liest die eingefrorenen Rohdateien und schreibt `jahrgang-<jahr>.bin`,
`sollreihen-<jahr>.bin` und ein `manifest.toml` mit SHA-256 je Ein- und Ausgabe, Quelle,
Lizenz und Abrufdatum. Der Bau des Spiels lädt **nichts** aus dem Netz. Der Jahrgang
enthält:

1. **Startwerte** für jede Zustandsgröße mit Datenanker; die Größen ohne Anker kommen aus
   der Tabelle „Jede Größe ohne Datenanker" in `spiel.md`, aus `parameter.toml`, aus dem
   Manifest oder aus **T46**. Welche Adresse woher kommt, entscheidet T45, und die Zuordnung
   ist dort abgezählt.

   **Zwei Startwerte entstehen aus je zwei Reihen und nicht aus einer, und beide behalten
   den Rang `Datenanker`.** Reihe 1 liefert ein BIP je Gebiet, Reihe 3 einen Kapitalstock je
   Gebiet; T15 führt von beidem **drei** je Gebiet. Dieselbe Regel bildet beide, mit den auf
   10.000 normierten Sektoranteilen aus Reihe 2:

   ```
   wertschoepfung[g][s] = mal_geteilt(bip_start[g],          sektoranteil[g][s], 10.000)
   kapitalstock[g][s]   = mal_geteilt(kapitalstock_start[g], sektoranteil[g][s], 10.000)
   ```

   Der Herkunftseintrag lautet `Datenanker(1 × 2)` beziehungsweise `Datenanker(3 × 2)`; die
   Zählung in T45 ändert sich dadurch nicht, weil beide Adressgruppen dort schon als Anker
   geführt sind. Die Regel für den Kapitalstock ist in Fassung 6 nachgetragen — `spiel.md`
   Fassung 5 verlangt sie, weil der Korbwert seit dem am Sektorkapitalstock hängt und der
   damit zum ersten Mal eine Größe ist, die jemand ausrechnen muss. Der Aufteilungsfehler
   ist derselbe wie bei der Wertschöpfung und für den Rückvergleich folgenlos, weil die
   zwölf Sektoranteil-Sollreihen aus **derselben** Normierung entstehen.

   **Die Vorgabetabelle der Fassung 4 an dieser Stelle ist gestrichen, und das ist kein
   Rückzug, sondern die Vermeidung eines Abbruchs.** Sie führte
   `land.<L>.instrument.<I>.druck` und `…​.rest` mit Startwert 0, je 16 Adressen, weil
   `spiel.md` sie damals nicht führte. `spiel.md` Fassung 4 hat alle 32 in seine Tabelle
   aufgenommen. Stünden sie hier weiter als Herkunftseintrag, trügen sie **zwei** Einträge —
   und genau das bricht den Jahrgangsbau nach T45 ab. Ihre Herkunft ist ab sofort `Entwurf`.

   Was bleibt, ist die Begründung, weil sie den Wert erzwingt statt ihn zu wählen, und weil
   ein späterer Leser sonst nicht weiss, warum dort 0 steht: Beide sind Laufzähler von
   Schritt 3, Druck entsteht nach `spiel.md` ausschliesslich durch Aktion 3, und vor Runde 1
   hat keine Aktion stattgefunden. Trüge eine der Adressen zu Partiebeginn einen Wert
   ungleich null, gäbe es eine Ursache ohne Aktion, und die Kette aus T18 könnte sie in
   Runde 1 nicht benennen. Nur die vier spielbaren Länder tragen Instrumente (T15), daher
   je 16 und nicht je 20. **Dieser Absatz ist ein Nachweis, kein Herkunftseintrag;**
2. **Sollreihen** für die 31 Reihen aus `spiel.md` plus den Handelsblock über 40 Ströme, je
   Reihe mit der Klassifikation aus T37;
3. **historische Politikpfade** für Leitzins, Zollniveau und Haushaltssaldo. Der vierte
   Hebel, Finanzmarktregulierung, hat keinen Anker und steht im Weltlauf fest auf seinem
   Startwert — was das Orakel für dieses Instrument blind macht, und das gehört in jeden
   Befund;
4. **exogene Pfade** nach T25;
5. **Konstanten des Jahrgangs**: **vierzehn Werte** — `durchgriff[Gebiet][handelbarer
   Sektor]`, also zehn in Zehntausendsteln, und **`leitzins_start[l]`**, vier in
   Basispunkten. Die vier sind die erste Stützstelle des Politikpfads aus Reihe 9, also
   keine neue Datenanforderung; sie stehen hier, weil `anleihekurs` sie über die ganze
   Partie braucht und ein Rückgriff auf „den Leitzins in Runde 1" einen Zustand voraussetzte,
   den der Zustand nicht mehr hat. Bildungsregel für `durchgriff` mit `H` = Aus- plus Einfuhr des Sektors im Startjahr
   (aus BACI über die Konkordanz in Punkt 9) und `N` = seine Wertschöpfung (aus WDI):

   ```
   durchgriff = teile_gerundet(10.000 · H, H + N)
   ```

   Der Wertebereich 0 … 10.000 gilt damit für alle nichtnegativen `H`, `N` per
   Konstruktion; eine Kappung gibt es nicht und darf es nicht geben, weil sie den Fehler
   aus Befund 3 nur verstecken würde. **Der einzige undefinierte Fall ist `H + N = 0`** —
   ein Sektor ohne Wertschöpfung und ohne Handel. Der Jahrgangsbau setzt dann
   `durchgriff = 0` (der Sektorpreis folgt vollständig dem Landespreis, was für einen
   Sektor ohne Handel die richtige Aussage ist) und **meldet den Fall im Manifest als
   Befund**, weil ein Gebiet mit einem leeren Sektor eine Datenfrage aufwirft und keine
   Rechenfrage. Er tritt im Prüfjahrgang bei keinem der fünf Gebiete auf; die Regel steht
   hier, damit der Jahrgangsbau nicht an einer Division abbricht, deren Ursache er nicht
   nennt.

   **Und der Jahrgangsbau prüft eine Bedingung an den Parametersatz, die `spiel.md`
   Fassung 5 aufstellt und die genau dieses Fenster trifft:** `anleihekurs(l)` hat den Nenner
   `leitzins[l] + aufschlag`, der Leitzins hat deshalb die Untergrenze `1 − aufschlag`, und
   der historische Politikpfad muss sie einhalten. Der Jahrgangsbau rechnet

   ```
   aufschlag_min = 1 − min über alle l und t von leitzins_pfad[l][t]
   ```

   und weist einen Parametersatz mit `aufschlag < aufschlag_min` für diesen Jahrgang als
   **unzulässig** zurück, statt später durch null zu teilen. Für 1997–2021 ist das keine
   theoretische Schranke: Deutschland folgt dem Euroraum ab Runde 3 exogen, und die EZB hat
   ihren Einlagesatz am 2014-06-11 erstmals auf −0,10 % gesenkt und bis September 2019 auf
   **−0,50 %** (`ecb.europa.eu/press/pr/date/2014/html/pr140605_3.en.html` und
   `ecb.europa.eu/stats/policy_and_exchange_rates/key_ecb_interest_rates/html/index.en.html`,
   abgerufen 2026-09-01 vom Spielentwerfer, hier übernommen). Zieht der Jahrgang den
   Einlagesatz, ist `aufschlag_min = 1 − (−50) = 51` Basispunkte; zieht er den
   Hauptrefinanzierungssatz, der ab 2016 bei 0,00 % steht, ist `aufschlag_min = 1`. **Welche
   Reihe eingebettet wird, entscheidet der Jahrgangsbau; die Schranke rechnet er in beiden
   Fällen selbst aus, statt eine Zahl zu übernehmen.** Dieselbe Untergrenze gilt im
   `spielmodus` am Instrument selbst (T51) — sonst unterliefe sie eine Lobbyaktion, die kein
   Jahrgangsbau je zu sehen bekommt;
6. **abgeleitete Kennzahlen**: die mittlere absolute Jahresänderung je Land als
   Schwankungsbreite für den Innerjahresausschlag. Mittlere absolute Abweichung, nicht
   Standardabweichung — die bräuchte eine Wurzel und damit Gleitkomma (T4);
7. **Normierung**: die drei Sektoranteile je Gebiet und Jahr werden auf 10.000 normiert,
   weil die WDI-Anteile wegen der Gütersteuern abzüglich Subventionen nicht auf 100 Prozent
   summieren. Die Normierung — Verfahren und der je Gebiet und Jahr abgeschnittene Rest —
   steht im Manifest, und der Rückvergleich vergleicht normiert gegen normiert;
8. **Brüche**: je Reihe ein Feld `exogen_ab` und ein Feld `verkettet_ab`, beide als
   Jahreszahl gespeichert und nach T40 in eine Runde umgerechnet. Für Deutschland trägt der
   Leitzins `exogen_ab = 1999`, im Prüfjahrgang also **Runde 3**, und die Wechselkursreihe
   `verkettet_ab = 1999` mit dem unwiderruflichen Umrechnungskurs;
9. **die Konkordanz HS92 → Modellsektor**, als Tabelle im Manifest und nicht im Code
   (Befund 12). Sie lautet nach `spiel.md`: Kapitel **01–24 → Sektor 1 Landwirtschaft**,
   **25–97 → Sektor 2 Industrie**. Dieselbe Tabelle erzeugt `H` aus Punkt 5, die
   Handelsstartmatrix und die 40 Sollströme des Handelsblocks — deshalb ist ihr
   Zuordnungsfehler für den Rückvergleich folgenlos, und deshalb darf es sie nur einmal
   geben. Eine zweite Kopie im Code wäre die Gelegenheit, sie auseinanderlaufen zu lassen;
10. **die Restwelt als Rest**, in beiden Größen ausdrücklich gebildet: Ihre Aggregate sind
    die Weltreihe der Weltbank minus die vier Länder; ihre Handelszeilen sind die
    Gesamtein- und -ausfuhr eines Landes im Sektor minus die Ströme zu den drei anderen.
    **Je gerichtetem Paar steht genau eine Zahl** (BACI meldet den Ausfuhrwert; ein
    getrennter Einfuhrwert würde die Invariante „Summe aller Handelsbilanzen = 0" von der
    Datenqualität abhängig machen statt von der Bauart).

Größenordnung: 5 Gebiete × 25 Jahre × rund 30 Reihen × 8 Byte = 30 kB, Handel
`40 × 25 × 8` = 8 kB. Der ausgelieferte Datenteil bleibt je Jahrgang deutlich unter
100 kB und mit allen Jahrgängen deutlich unter einem Megabyte.

**T45 — Der Jahrgangsbau zählt die Adressen ab und bricht bei einer Lücke ab.** Das ist die
architektonische Antwort auf Befund 2, und sie ist die einzige, die dessen Wiederholung
ausschliesst. Zwei Tabellenzeilen nachzutragen behebt den Fall; sie nachzutragen und die
Stelle offenzulassen, an der niemand das Fehlen bemerkt, behebt ihn nicht.

Der Jahrgangsbau führt über **alle 310 Adressen aus T15** eine Herkunftstabelle mit genau
**fünf** zulässigen Einträgen. Vier standen in Fassung 4; die fünfte ist in dieser Fassung
hinzugekommen, weil das Auszählen zwei Adressen gefunden hat, deren Wert weder in einer
Reihe noch in einem Dokument steht, sondern vom Jahrgangsbau selbst gerechnet wird.

| Eintrag | Bedeutung | Adressen | Beispiel |
|---|---|---:|---|
| `Datenanker(nr)` | eine Reihe der Reihenliste weiter unten | 136 | `land.DE.sektor.2.wertschoepfung` → Reihe 1 × 2 |
| `Entwurf` | die Tabelle „Jede Größe ohne Datenanker" in `spiel.md` nennt einen **Zahlenwert** | 150 | `land.CN.aufsichtszaehler` → 0 |
| `Parameter(schluessel)` | `parameter.toml` nach T27 | 11 | `fonds.kasse` → `startkapital` |
| `Manifest(feld)` | vom Jahrgangsbau gerechnet und im Manifest ausgewiesen | 2 | `markt.wert` → Startkorb zu Startpreisen (T33) |
| `Vorgabe(T-Nummer)` | dieses Dokument, abschliessend aufgezählt in **T46** | 11 | `restwelt.basiswechsel` → 0 (T8) |
| **Summe** | | **310** | |

**Die Vorrangregel, ohne die die Summe nicht aufgeht.** Die Entwurfstabelle in `spiel.md`
nennt für einige Zeilen keinen Zahlenwert, sondern eine **Bezugsquelle** — „aus
`parameter.toml`" bei Zustimmung, Finanzmarktregulierung, Fondskasse, Anlegerbestand und
Parametersatz-Prüfsumme, „aus dem Manifest des Jahrgangs" bei der Jahrgangskennung. Nach dem
Wortlaut der Fassung 4 trügen diese Adressen zwei Einträge und brächen den Bau ab. Es gilt
deshalb: **Der Eintrag ist die Stelle, die den Wert *bestimmt*, nicht die, die ihn
erwähnt.** Verweist die Entwurfstabelle weiter, lautet der Eintrag `Parameter(…)`
beziehungsweise `Manifest(…)`; `Entwurf` bleibt den Zeilen vorbehalten, die eine Zahl
hinschreiben. Ein Verweis ist kein zweiter Eintrag.

**Eine Adresse ohne Eintrag bricht den Jahrgangsbau ab, eine Adresse mit zwei Einträgen
ebenso.** Der zweite Fall ist der wichtigere: Er ist die Stelle, an der eine Größe zwei
Herren bekäme und die beiden Werte auseinanderlaufen könnten — derselbe Fehlertyp, den T39
für `landespreis`, T23 Punkt 9 für die BACI-Konkordanz und T47 für das Fondsvermögen schon
geschlossen haben. Er ist in dieser Fassung einmal eingetreten und behoben: die 32
Druck- und Restverzögerungsadressen, die `spiel.md` Fassung 4 aufgenommen hat und die T23
Punkt 1 weiterhin führte.

**Wie die Zahlen der dritten Spalte entstanden sind, damit sie nachzählbar sind statt
geglaubt.** Je spielbarem Land tragen 21 Adressen einen Datenanker (9 Sektorgrößen ohne den
Preis, 8 Aggregatgrößen ohne den Wechselkurs, der Wechselkurs selbst, 3 Instrumentenstände),
20 den Eintrag `Entwurf` (3 Sektorpreise, Aufsichtszähler, Einfluss, 12 Druck-, Gegendruck-
und Restverzögerungsfelder, 3 Restdauern), 2 einen Parameterschlüssel (Zustimmung,
Finanzmarktregulierung) und 1 eine Vorgabe (`basiswechsel`) — zusammen die 44 aus T15. Für
die USA fällt der Wechselkurs vom Anker in die Vorgabe (Numéraire), also `3 × 21 + 20 = 83`
Anker. Die Restwelt trägt 13 Anker, 3 `Entwurf` und 6 Vorgaben. Dazu 40 Handelsströme mit
Anker.

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

Die vollständige Tabelle — 310 Zeilen aus Adresse, Herkunft und Startwert — wird ins
Manifest geschrieben. Damit ist die Abnahmebedingung 2 des Arbeitspakets **maschinell
beantwortbar**, statt vier Dokumente nebeneinanderzulegen: Wer sie prüfen will, liest eine
Datei, die der Jahrgangsbau gar nicht erst hätte schreiben können, wenn eine Zeile fehlte.

Der Preis ist 310 Vergleiche, einmal je Datenlauf und nicht je Partie. Die naheliegende
Alternative — Startwert null, wenn nichts dasteht — wäre die teure gewesen: Sie hätte
Befund 2 der dritten Prüfung in eine Zahl verwandelt, die niemand mehr hinterfragt, und
zwar in genau die Zahl, die dort zufällig richtig ist.

**T46 — Die elf Adressen, deren Herkunft dieses Dokument ist, abschliessend.** Fassung 4
hat `Vorgabe(T-Nummer)` eingeführt und mit „derzeit allein T23 Punkt 1" beschrieben. Das war
falsch, und der Fehler ist erst beim Auszählen aufgefallen: Nach der Aufnahme der 32
Adressen in `spiel.md` hat T23 Punkt 1 gar keine Adresse mehr — dafür haben elf andere seit
jeher keinen zulässigen Eintrag gehabt, ohne dass es jemandem aufgefallen wäre. Sie stehen
hier mit Startwert, Grund und Regel im Lauf:

| Adresse | Zahl | Startwert | Grund und Regel im Lauf |
|---|---:|---:|---|
| `gebiet.<G>.basiswechsel`, alle fünf Gebiete | 5 | 0 | Zähler der Neubasierungen nach **T8**. Vor Runde 1 hat keine stattgefunden; im Lauf erhöht ihn allein die Regel aus T8. Keine Reihe kann ihn tragen, weil er eine Eigenschaft des Modells ist und nicht der Welt |
| `land.US.wechselkurs` | 1 | 10.000 | Der US-Dollar ist der Numéraire (**T5**). Reihe 10 trägt drei Länder, die USA definitionsgemäß nicht. Der Wert ist über die ganze Partie fest und wird je Runde mit der Ursache `Vortrag` geschrieben (T18) — dieselbe Bauart wie der dauerhaft leere Steckplatz aus T16 |
| `restwelt.leitzins`, `restwelt.staatsschuld`, `restwelt.haushaltssaldo` | 3 | 0 | Die Restwelt hat nach `spiel.md` keine Politikinstrumente, keine Regierung und keinen Aufsichtszähler; sie hat folglich auch keine Notenbank und keinen Haushalt. Diese drei Adressen und die nächste existieren nur, weil T15 der Restwelt denselben Aggregatblock gibt wie einem Land. **Keine Modellregel liest sie**, alle vier werden je Runde mit der Ursache `Vortrag` fortgeschrieben, damit die Sollmaske aus T38 aufgeht |
| `restwelt.wechselkurs` | 1 | 10.000 | Ebenso ungelesen, aber mit anderem Startwert: Die Restwelt rechnet im Numéraire, und ein Kurs eines Währungsaggregats gegen den Dollar hat keine Bedeutung. 10.000 statt 0, damit eine versehentliche Verwendung nicht durch null teilt, sondern die Zahl unverändert lässt |
| `restwelt.inflation` | 1 | 0 | Reihe 8 (Verbraucherpreise) trägt vier Länder, die Restwelt nicht. Im Lauf ist die Größe endogen wie überall — Jahresrate von `restwelt.preisniveau`, das Reihe 15 verankert. Nur ihr Startwert hat keine Quelle |

**Die erste Zeile nennt fünf Adressen und keine Schreibweise.** `gebiet.<G>.` ist die
Sammelschreibweise aus **T17b** und löst hier zu `land.US.basiswechsel`,
`land.CN.basiswechsel`, `land.DE.basiswechsel`, `land.BR.basiswechsel` und
`restwelt.basiswechsel` auf — laufende Nummern 44, 88, 132, 176 und 198 in
`daten/adressen.md`. Das ist keine Ausnahme von T17, sondern seine Anwendung: Fünf Zeilen
einzeln aufzuführen, wo sie sich nur im Gebiet unterscheiden, bläht die Tabelle und sagt
nichts mehr.

**Zwei Auflagen, ohne die die vier Restweltadressen eine stille Annahme wären.** Erstens:
Auf sie ist **ausser dem Vortrag selbst kein Lesezugriff zulässig**. Der `Schreiber` führt
sie in einer Liste `nur_vortrag`; ein `lies_alt` oder `lies_neu` darauf aus einer anderen
Ursache als `Vortrag{adresse}` ist ein harter Fehler, kein Bericht, und der Bruchtester
prüft es in Prüfung 5 und 6 mit. Sonst wüchse eine Modellregel auf einer Zahl, die niemand
gesetzt hat. Zweitens: Fällt später eine Regel an, die eine davon braucht, ist das ein ADR
und keine Zeile Code — dann bekommt die Adresse einen Datenanker oder eine begründete
Bildungsregel.

**Warum T46 überhaupt gebraucht wird und die Adressen nicht einfach entfallen.** Sie zu
streichen wäre die sauberere Architektur und ist ausgeschlossen: `spiel.md` nennt **310**
Größen und verweist für die Aufstellung hierher. 306 hier und 310 dort wäre ein Widerspruch
in einer Zahl, also genau der Fall, den Abnahmebedingung 3 ausschliesst — und ändern darf
ich `spiel.md` nicht. Vier Adressen, die nie gelesen werden, kosten 32 Byte und einen Test;
ein Widerspruch zwischen den beiden Dokumenten kostet einen Lauf.

**T24 — Lücken werden gekennzeichnet, nicht stillschweigend gefüllt — und der Prüfjahrgang
duldet keine.** Je Reihe, Land und Jahr ein Flag `gefuellt`. Die Füllregel steht im
Manifest (Fortschreibung des letzten bekannten Werts, lineare Ganzzahlinterpolation
zwischen Stützstellen), und **gefüllte Jahre zählen im Fehlermaß des Rückvergleichs nicht
mit**, sondern werden gezählt und ausgewiesen.

Zwei Schwellen:

- **Prüfjahrgang 1997–2021:** `spiel.md` verlangt jede der 31 Sollreihen und jeden der 40
  Handelsströme über **25 Stützstellen ohne Füllung**, also `gefuellt = 0`. Eine Reihe, die
  das nicht erfüllt, wird **nicht gefüllt und nicht stillschweigend übernommen**, sondern
  als Befund an den Spielentwerfer gemeldet, samt der beiden Auswege, die ihm zustehen:
  Reihe streichen oder Fenster kürzen. Nach T40 kostet die zweite Wahl nur eine Zahl im
  Manifest.
- **Spieljahrgänge:** Eine Sollreihe, die zu mehr als einem Fünftel gefüllt ist, gilt als
  nicht belastbar und wird im Befund als solche markiert.

**Der Verdachtsfall ist enger geworden, aber nicht geschlossen.** Fassung 2 hat hier die
chinesischen und brasilianischen Leitzinsreihen der neunziger Jahre genannt; `spiel.md`
Fassung 3 hat den Fall gegen `FR.INR.LEND` geprüft (China 1995–2023 lückenlos, Brasilien
ab 1997) und damit ein Indiz, keinen Beweis. `FR.INR.LEND` ist eine andere Reihe als der
IFS-Leitzins, und `imf.org` weist den Abruf mit HTTP 403 ab. Der Jahrgangsbau prüft es an
der Reihe, die tatsächlich eingebettet wird. **Das ist unverändert die wahrscheinlichste
Stelle, an der das Vorhaben an Daten scheitert** — nur ist sie jetzt billig, weil sie
niemanden mehr zwingt, ein Paket zweimal zu bauen.

**T25 — Die Grenze zwischen exogen und endogen ist die Grenze der Aussagekraft des
Orakels, und deshalb ist sie eng gezogen.**

| Größe | im Spiel | Begründung |
|---|---|---|
| Bevölkerung, Erwerbstätige | **exogen**, Pfad aus Daten | Demografie ist nach `spiel.md` ausdrücklich keine Spielgröße |
| Restwelt-Nachfrageniveau | **exogen**, Pfad aus Daten | Randbedingung des Modells; der Rückvergleich prüft die Restwelt folglich nicht |
| `durchgriff` | **exogen und konstant**, Konstante des Jahrgangs | so von `spiel.md` festgelegt, samt der dort benannten Vereinfachung: Chinas wachsende Handelsoffenheit bildet das Modell über Mengen ab, nicht über die Preisübertragung |
| Produktivität | **endogen**, nur Startwert aus PWT | Würde sie jährlich aus den Daten gelesen, wäre das BIP im Rückvergleich eine Wiedergabe der Sollreihe und der Test prüfte sich selbst |
| Preise, Zinswirkung, Handel, Staatsfinanzen, Zustimmung | **endogen** | das ist die Maschine, die geprüft werden soll |
| Politikinstrumente | im `spielmodus` endogen, im `weltlauf` auf die historischen Pfade gesetzt | so verlangt es `spiel.md` — mit der Folge aus T37 und der Maske aus T38 |

**T51 — Jedes Politikinstrument hat eine Schrittweite und einen Wertebereich, beide aus
`parameter.toml`, und der Wertebereich gilt in beiden Modi.** `spiel.md` sagt „Instrumente
bewegen sich um höchstens einen Schritt je Runde" und nennt für die Finanzmarktregulierung
keine Einheit; seit T5 Klasse 10 gibt es eine, und damit lässt sich der Satz aufschreiben:

| Instrument | Klasse | ein Schritt | Wertebereich |
|---|---|---|---|
| Leitzins | 3 Raten | `schrittweite[leitzins]` bp | `instrument_min[leitzins] … instrument_max[leitzins]`, und **`instrument_min[leitzins] ≥ 1 − aufschlag`** |
| Zollniveau | 3 Raten | `schrittweite[zoll]` bp | `0 … instrument_max[zoll]` |
| Haushaltssaldo | 3 Raten | `schrittweite[haushalt]` bp | `instrument_min … instrument_max` |
| Finanzmarktregulierung | 10 Instrumentenstufe | **1 Stufe** | `0 … regulierung_stufen` |

Nach jeder Bewegung in Schritt 3 gilt `stand = min(max(stand ± schritt, min), max)`; die
Kappung trägt die Ursache des auslösenden Drucks und nicht `Vortrag`, damit die Kette aus
T18 sagt, *dass* gekappt wurde. **Im `weltlauf` gilt die Schrittweite nicht** — der
historische Pfad ist dort die Wahrheit und darf in einem Jahr weiter springen —, **der
Wertebereich schon**: Verlässt der Pfad ihn, ist das ein Befund des Jahrgangsbaus und kein
stilles Kappen einer Sollgröße.

Die Zeile, an der das hängt, ist die zweite Spalte des Leitzinses. Ohne sie kann eine
Lobbyaktion den Zins unter `−aufschlag` drücken, und `anleihekurs` teilt in derselben Runde
durch null oder wechselt das Vorzeichen. Der Jahrgangsbau prüft die Bedingung gegen den
historischen Pfad (T23 Punkt 5), das Instrument prüft sie gegen den Spieler, und der
Invariantentest prüft sie gegen beide (T30 Prüfung 2). Drei Prüfungen für eine Schranke ist
nicht zu viel: Sie ist die einzige Stelle des Modells, an der ein Kurs unendlich wird.

**T26 — Ein gesperrter oder fehlender Datenanker ändert das Programm nicht, nur das
Manifest.** Drei Fälle, alle nach demselben Muster: Der Jahrgang trägt ein Modellkonstrukt,
das Manifest sagt es, der Befund wiederholt es.

| Fall | Ersatz | Folge für das Orakel |
|---|---|---|
| Aggregierter Zollsatz fällt unter die Drittanbieter-Ausnahme (die schwerste offene Frage aus `spiel.md`) | kein Zollpfad; der Weltlauf läuft mit konstantem Zoll | zwei statt drei verankerte Instrumente |
| Sektorale Beschäftigung (Reihe 7) gesperrt | Aufteilung nach Wertschöpfungsanteil | Startwert wird Modellkonstrukt, keine Sollreihe betroffen |
| **Spieljahrgang vor 1995 braucht eine Handelsmatrix, BACI beginnt 1995** | IWF-DOTS-Aggregate je Länderpaar, aufgeteilt nach den WDI-Sektoranteilen des Ausfuhrlandes | die Startmatrix ist ein Modellkonstrukt; Spieljahrgänge tragen ohnehin keinen Handelsblock im Rückvergleich (`spiel.md`) |

Der dritte Fall betrifft nach der Verschiebung auf 1997 nicht nur die Jahrgänge vor 1995,
sondern auch 1995 und 1996: Sie sind nach `spiel.md` Spiel-, aber keine Prüfjahrgänge und
tragen als US-Startwert die Sektorstruktur von 1997, gekennzeichnet als `gefuellt`.
Lizenz- und Deckungsrisiko sind damit eine Eigenschaft der Datenschicht, nie eine des Kerns.

### Die Reihenliste, die `spiel.md` vom Architekten verlangt

Damit der Datenbauer je Reihe das Feld „Source" prüfen kann. Quelle nach `daten.md`;
„Verdacht" heisst Drittanbieter-Ausnahme der Weltbank. Die Nummern 7, 8, 10 und 13, die
`spiel.md` zur Prüfung benennt, sind unverändert.

| Nr | Größe | Dimension | Modelleinheit | Quelle | Rolle | Verdacht |
|---:|---|---|---|---|---|---|
| 1 | BIP, konstante Preise | 4 + RW | Tsd USD | WDI / PWT | Start + Soll (4, frei) | nein |
| 2 | Wertschöpfungsanteil je Sektor: `NV.AGR.TOTL.ZS`, `NV.IND.TOTL.ZS`, `NV.SRV.TOTL.ZS` | (4+RW) × 3 | Zehntausendstel, auf 10.000 normiert | WDI | Start + Soll (12, frei, 8 unabhängig) | nein |
| 3 | Kapitalstock | 4 + RW | Tsd USD | PWT | Start | nein |
| 4 | Produktivität (TFP) | 4 + RW | Index | PWT | nur Start (T25) | nein |
| 5 | Bevölkerung | 4 + RW | Personen | WDI / PWT | exogener Pfad | nein |
| 6 | Erwerbstätige | 4 + RW | Personen | WDI / PWT | exogener Pfad | nein |
| 7 | Beschäftigung je Sektor | (4+RW) × 3 | Personen | WDI (ILO) | Start | **ja** |
| 8 | Verbraucherpreise | 4 | bp Jahresrate | WDI / IWF IFS | Start + Soll (4, frei) | **ja** (IWF-gestützt) |
| 9 | Leitzins | 4 | bp | IWF IFS | Start + Politikpfad + Soll (4, **gesetzt**) | nein |
| 10 | Wechselkurs gegen USD | 3 | Index | IWF IFS / WDI | Start + Soll (3, frei) | prüfen |
| 11 | Staatsschuldenquote | 4 | bp | IWF WEO | Start + Soll (4, **abgeleitet**) | nein |
| 12 | Haushaltssaldo | 4 | bp | IWF WEO | Start + Politikpfad | nein |
| 13 | Zollniveau, aggregiert | 4 | bp | WDI (aus WITS) | Start + Politikpfad | **ja, entscheidend** |
| 14 | Bilaterale Ströme nach HS92, aggregiert über die Konkordanz aus T23 Punkt 9 | 5 × 4 × 2 | Tsd USD | CEPII BACI | Start + Sollblock (frei) | nein |
| 15 | Preisniveau im Ländervergleich | 4 + RW | Index | PWT | Start (Numéraire) | nein |
| 16 | `durchgriff` | 5 × 2 | Zehntausendstel | BACI + WDI, abgeleitet nach T23 Punkt 5 | Konstante des Jahrgangs | nein |
| 17 | Sektorpreise | (4+RW) × 3 | Index | **keine** | endogen, kein Soll | — |
| 18 | Zustimmung | 4 | Zehntausendstel | **keine** | aus `parameter.toml` | — |
| 19 | Marktkorbwert und Marktrendite | 1 + 1 | Tsd USD / bp | **keine** | Startwert nach T33, endogen, kein Soll | — |

`NV.IND.MANF.ZS` (verarbeitendes Gewerbe) wird nach `spiel.md` **nicht** verwendet und ist
deshalb hier nicht aufgeführt. Die 31 Sollreihen sind die Zeilen 1, 2, 8, 9, 10 und 11
(4+12+4+4+3+4); der Handelsblock aus Zeile 14 kommt als eigener Block hinzu. Die vier
Größen ohne Datenanker sind die Zeilen 17, 18, 19 und das Instrument
Finanzmarktregulierung — genau die vier, die `spiel.md` unter „Die Grenze des Orakels"
aufzählt.

**Und hier steht die Zeile, deren Fehlen T46 nötig gemacht hat.** Die Spalte „Dimension"
ist zu lesen, wie sie dasteht: Zeile 8 trägt **4**, nicht 4 + RW; die Zeilen 9, 11 und 12
tragen **4**, Zeile 10 trägt **3**. Daraus folgt, dass elf Zustandsadressen von keiner Reihe
gedeckt sind — der US-Wechselkurs (Numéraire), fünf Aggregatgrößen der Restwelt und die fünf
Neubasierungszähler. Sie stehen in **T46**. Bis Fassung 4 stand das nirgends, weil niemand
die Dimensionen gegen T15 gelegt hat; die Prüfung der Runde 4 hat Bedingung 2 für erfüllt
erklärt und dabei auf dieselbe Lücke geschaut wie ich.

**T27 — Die Kalibrierdatei liegt ausserhalb des Codes, und jeder Schlüssel trägt eine
Skalenklasse.** Sämtliche Zahlenwerte, die `spiel.md` ausdrücklich der Kalibrierung
überlässt — Mandatsschwelle (`schwelle_v` und `schwelle_e`), drei Aufsichtsschwellen,
Nachahmergeschwindigkeit, Anlegerabzugsanteil, Startkapital, Startzustimmung, Startstand der
Finanzmarktregulierung, `ausstiegsabschlag` und `zwangsabschlag` (T47), Verzögerungen,
Elastizitäten — stehen in `parameter.toml`.

**Elf Schlüssel bekommen in dieser Fassung eine Einheit oder gibt es neu**, weil T49 und T50
sie sonst nicht einordnen könnten. Ein Parameterschlüssel ohne Klasse ist derselbe Fehler
wie eine Adresse ohne Klasse:

| Schlüssel | Klasse (T5) | Bedeutung | woher |
|---|---|---|---|
| `stufenweite` | 4 Anteile | Anteil des Marktes je Positionsstufe, **kein Geldbetrag** | `spiel.md` Fassung 5 |
| `stufen_max` | 11 Zähler | Betragsgrenze der Stufenzahl je Steckplatz | T16 |
| `ausstiegsabschlag`, `zwangsabschlag` | 4 Anteile | Abschläge auf den Beteiligungswert | T47 |
| `aufschlag` | 3 Raten | Abstand Leitzins ↔ Anleiherendite, `≥ aufschlag_min` (T23 Punkt 5) | **neu**, `spiel.md` Fassung 5 |
| `lobbykosten` | 1 Fondsgeld | US-Cent je Lobbypunkt, `≥ 1` | T50 |
| `beteiligungsrabatt` | 4 Anteile | Preisnachlass auf den Lobbypunkt bei Beteiligung, `1 … 10.000` | **neu**, T50 |
| `gegenlobby_satz` | 9 Lobbydruck | Lobbypunkte je 10.000 Tausend USD Schaden | **neu**, T50 |
| `druck_max` | 9 Lobbydruck | Obergrenze für Druck und Gegendruck je Instrument | **neu**, T5 Klasse 9 |
| `regulierung_stufen` | 10 Instrumentenstufe | Zahl der Stufen der Finanzmarktregulierung | **neu**, T5 Klasse 10 |
| `schrittweite[i]`, `instrument_min[i]`, `instrument_max[i]` | wie das Instrument | Bewegung je Runde und Wertebereich | **neu**, T51 |

`leitzins_start[l]` steht **nicht** hier, sondern im Jahrgang (T23 Punkt 5): Es ist keine
Kalibriergröße, sondern eine Messung. Die Zahl der Adressen mit Herkunft
`Parameter(schluessel)` bleibt bei elf (T45) — neue Schlüssel sind keine neuen Adressen.

Alle Werte werden als Dezimalzeichenketten in skalierte Ganzzahlen gelesen (T4)
und in eine Struktur mit benannten Feldern gefüllt, nie über eine Schleife über Schlüssel
(T9). Die Prüfsumme des Parametersatzes steht im Zustand und in jedem Speicherstand. Damit
ist Kalibrieren eine Datenänderung, die kein Übersetzen braucht — genau die Bauart, die
`spiel.md` an Democracy 4 belegt hat, und die Voraussetzung dafür, dass ein Agent über
Nacht tausend Parametersätze durchsucht (Abschnitt 10).

## 8. Markträumung und die beiden Renditen

**T28 — Feste Iterationszahl statt Konvergenzabbruch.** Der Weltpreis je handelbarem
Sektor wird durch **genau 40 Halbierungsschritte** über einem festen Preisintervall
gesucht, nicht bis zu einer Schranke. Ein Abbruch nach Genauigkeit macht die Laufzeit vom
Zustand abhängig und die Zahl der Schritte zu einem stillen Teil des Ergebnisses; eine
feste Zahl macht beides messbar und begrenzt. 40 Halbierungen über einem Intervall von
sechs Größenordnungen lösen bis unter ein Zehntausendstel auf — mehr Auflösung, als die
Preisskala aus T5 überhaupt darstellt.

Innerhalb jedes Halbierungsschritts stehen, in dieser Reihenfolge, der Zollkeil je Gebiet
auf dem Weltpreis und daraus der wirksame Sektorpreis als Mischung

```
preis = teile_gerundet(weltpreis_mit_zoll · durchgriff
                       + landespreis · (10.000 − durchgriff),  10.000)
```

mit `landespreis = lies_alt(gebiet.<G>.sektor.<s>.preis)` nach T39, Präfix nach T17b, in
Runde 1 also dem Startwert 10.000. Angebot und Nachfrage werden auf diesem Preis gebildet.

**Damit ist die Zulässigkeit der Halbierung belegt statt behauptet** — und das ist die
Behebung von Befund 6, nicht nur seine Beantwortung. Beide Gewichte sind nichtnegativ
(`durchgriff` liegt nach T23 Punkt 5 in 0 … 10.000), `landespreis` steht fest, während die
Halbierung läuft, und `preis` ist deshalb monoton wachsend im Weltpreis. Die
Überschussfunktion erbt diese Monotonie, es entsteht keine Fixpunktaufgabe, und ein Durchlauf
genügt. Die zweite Lesart des Prüfers — `landespreis` als räumender Inlandspreis derselben
Runde — hätte genau das zerstört; sie ist mit T39 nicht nur verworfen, sondern nicht mehr
formulierbar.

Dienstleistungen haben keine Handelszeile, keinen Weltpreis und `durchgriff = 0`; ihr
Sektorpreis ist die reine Fortschreibung des Vorrundenpreises durch die inländische
Räumung.

**T29 — Ganzzahlige Potenzen und Wurzeln über Newton auf `i128`.** Wo die
Produktionsfunktion einen Exponenten wie 1/3 braucht, wird `wurzel(x, n)` mit fester
Schrittzahl verwendet; Exponenten sind auf Brüche kleiner ganzer Zahlen beschränkt. Keine
Reihenentwicklung, kein Logarithmus, keine Tabelleninterpolation.

**T33 — Marktrendite und Fondsrendite werden über einen eingefrorenen Mengenkorb
gerechnet.** `spiel.md` hat die Auslegung entschieden: wertgewichtete Rendite aller
handelbaren Körbe zu Modellmarktwerten, gewichtet nach dem Markt und **nicht** nach dem
Bestand des Fonds. Die Regel, in Schritt 6 der Runde und nur im `spielmodus`:

1. Der **Marktkorb** umfasst die 12 Land×Sektor-Körbe und die 4 Staatsanleihen, jeweils zu
   Modellmarktwerten. Währungen tragen keine Marktkapitalisierung und gehen nicht ein; ihre
   Wirkung steckt in der Umrechnung der übrigen Körbe in den Numéraire. **Seit `spiel.md`
   Fassung 5 sind Menge und Kurs benannt**, und damit ist der Korb eine Rechnung statt einer
   Umschreibung — die Mengen sind Kapitalstock und Staatsschuld, die Kurse Sektorpreis,
   Anleihekurs und Wechselkurs (T48):

   ```
   marktkorb(m, k) = Σ über die 12 Land×Sektor  wert_(m,k)(kapitalstock[l][s], sektorpreis[l][s], l)
                   + Σ über die  4 Anleihen     wert_(m,k)(schuld(l),          anleihekurs(l),    l)
   ```

   `m` und `k` sagen, aus welcher Runde die Menge und aus welcher der Kurs gelesen wird;
   beide Summen laufen über die Indexordnung aus T9. Der Wert steht in der
   **volkswirtschaftlichen** Skala (T5 Klasse 2) und überquert keine Skalengrenze.
2. `markt.wert` trägt den Wert dieses Korbs am Ende der Vorrunde. **In Runde 1 ist es der
   Startwert aus dem Jahrgang** — der Wert des Startkorbs zu Startpreisen, vom Jahrgangsbau
   als `marktkorb(start, start)` gerechnet und im Manifest ausgewiesen. Damit ist die zweite
   Hälfte von Befund 2 der zweiten Prüfung geschlossen, unabhängig vom Modus.
3. Bewerte den **Mengenkorb der Vorrunde** zu den Preisen dieser Runde:
   `W_neu = marktkorb(alt, neu)`, also Mengen über `lies_alt` und Kurse über `lies_neu`
   (T39). `markt.rendite = teile_gerundet((W_neu − markt.wert) · 10.000, markt.wert)` in
   Basispunkten.
4. Erst danach wird `markt.wert = marktkorb(neu, neu)` gesetzt.

Mengenwachstum erzeugt damit keine Scheinrendite. **`markt.wert` ist nie null** — er ist
eine Summe positiver Mengen mal positiver Kurse, und beide Wertebereiche prüft der
Invariantentest (T30 Prüfung 2). Damit sieht die Division in Punkt 3 nie einen Nenner null,
ohne dass irgendwo ein Sonderfall stünde; das ist dieselbe Bauart wie Schritt (c) vor (d)
weiter unten.

**Die Fondsrendite entsteht in derselben Reihenfolge, und die Reihenfolge ist die Regel:**
(a) Positionen bewerten, (a') Beteiligungen bewerten, (b) Fondsvermögen bilden, (c) ist es
**null oder kleiner**, greift nach `spiel.md` Todesart 1 in derselben Runde und die Partie
endet ohne Renditebildung, (d) erst sonst wird die Rendite gebildet: Änderung des
Fondsvermögens gegenüber der Vorrunde, **bereinigt um Anlegerzu- und -abflüsse dieser
Runde** — sonst zählte frisches Anlegergeld als Leistung und der Anlegerabzug aus
Gegenkraft 3 verstärkte sich selbst. Die Überrendite ist die Differenz beider Größen in
Basispunkten und steht für drei Runden im Zustand.

Schritt (c) vor (d) ist keine Feinheit: Er ist der Grund, warum `teile_gerundet` in diesem
Modell nie einen Nenner null sieht, ohne dass irgendwo ein Sonderfall geprüft würde.

**T47 — Das Fondsvermögen ist genau eine Funktion, und jede Bewertung darin überquert die
Skalengrenze genau einmal, am äussersten Aufruf.** `spiel.md` Fassung 5 bildet `korbwert`
und `positionswert`, die Fassung 4 nur verwendet hatte (Befund 1 der Runde 6), und
entscheidet, auf welcher Seite der Grenze `korbwert` steht (Befund 2). Hier steht, wo
gerechnet wird.

**Die Marktwerte, alle in der volkswirtschaftlichen Skala** (T5 Klasse 2); `wert` ist die
eine Bewertungsformel, aus der alle drei Steckplatzarten entstehen:

```
wert(menge, kurs, g) = mal_geteilt(menge, kurs, wechselkurs[g])

korbwert(l, s)   = wert(kapitalstock[l][s], sektorpreis[l][s], l)
anleihewert(l)   = wert(schuld(l),          anleihekurs(l),    l)
waehrungswert(l) = wert(handelsvolumen(l),  10.000,            l)

markt(p)         = korbwert | anleihewert | waehrungswert, je nach Steckplatzart
stufenwert(p)    = mal_geteilt(markt(p), stufenweite, 10.000)
```

**Die beiden Fondswerte, in US-Cent** (T5 Klasse 1) — und genau hier liegt die Grenze:

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

Beide Summen laufen über die Indexordnung aus T9, nie über eine Menge. `korbwert(l, s)` ist
derselbe Wert, den auch der Marktkorb aus Punkt 1 dieses Abschnitts verwendet — **eine
Bewertung, nicht zwei**, sonst könnten Marktrendite und Fondsvermögen denselben Korb
verschieden ansetzen.

**Das ist die Behebung von Befund 2, und sie steht an der Wurzel und nicht in einer
Klammer.** Die Formel der Fassung 5 bestand aus zwei `mal_geteilt` mit einheitenlosen
Anteilen, war also skalenerhaltend: Was in Tausend USD hineinging, kam in Tausend USD
heraus und wurde als US-Cent verbucht — Faktor 100.000, Kasse fällt um das
Hunderttausendfache dessen, was das Beteiligungsvermögen steigt, Todesart 1 in derselben
Runde, Klasse 2 von Maß 2 von Bauart wegen chancenlos. `tsd_in_cent` um den äussersten
Aufruf schliesst das.

**Von den beiden Wegen, die der Prüfer offengelassen hat, ist der andere ausgeschlossen,
und die Begründung ist nicht meine.** `korbwert` gleich in Cent zu führen hiesse, denselben
Korb in zwei Skalen zu führen, denn T33 bewertet dieselben zwölf Körbe volkswirtschaftlich —
zwei Bewertungen für einen Korb, also genau das, was der Absatz darüber ausschliesst.
`spiel.md` Fassung 5 entscheidet das unter *Wo die Skalengrenze liegt* und weist mir nur
noch zu, **welche Funktion** es tut. Es ist `tsd_in_cent` aus T50, und sie hat in diesem
Dokument genau die zwei Aufruforte, die oben stehen.

**Die Reihenfolge der Rundungen ist verbindlich, weil sie das Ergebnis ändert.**
`stufen(p) · stufenwert(p)` und `mal_geteilt(markt(p), stufen(p) · stufenweite, 10.000)`
unterscheiden sich um bis zu `|stufen(p)|` Einheiten. Verbindlich ist die erste Form, weil
`spiel.md` sie so schreibt; die zweite wäre genauer und macht jeden Regressionsbestand
ungültig, der mit der ersten entstanden ist. Wer sie will, braucht einen ADR, keinen
besseren Grund.

**Zwei Wertebereichsschranken gehören dazu, sonst ist die Formel nur bei gutem Wetter
richtig.** Erstens teilt `wert` durch `wechselkurs[g]`: Ein Nenner null ist nach T6 ein
Abbruch, ein **negativer** Nenner wäre schlimmer — er drehte das Vorzeichen jeder Bewertung,
ohne dass irgendetwas abbräche. `wechselkurs[g] ≥ 1` ist deshalb eine Invariante (T30
Prüfung 2), keine Erwartung. Zweitens ist `tsd_in_cent` die einzige Stelle, an der ein `i64`
überlaufen kann: `x · 100.000` verlässt den Bereich ab `|x| > 9,2 · 10^13` Tausend USD. Der
grösste Wert, der dort ankommen kann, ist durch den ganzen Marktkorb beschränkt; bei einem
Weltkapitalstock in der Größenordnung von `4 · 10^11` Tausend USD — grob das Drei- bis
Vierfache eines Weltbruttoinlandsprodukts von rund `10^11` Tausend USD, als Größenordnung
und nicht als Messung — liegen gut zwei Größenordnungen dazwischen. Der Jahrgangsbau prüft
`marktkorb(start, start) < 9,2 · 10^13`, der Invariantentest prüft `markt.wert` je Runde
gegen dieselbe Schranke. Damit ist der Überlauf nicht bloß unwahrscheinlich, sondern
ausgeschlossen und geprüft.

**Was die Anteilsskala nach unten begrenzt, und warum das eine Auflage an den Selbstspieler
ist.** `stufenweite` ist ganzzahlig und mindestens 1; eine Stufe kostet deshalb mindestens
ein Zehntausendstel des Korbs, an dem sie hängt. Die sechzehn Marktwerte eines Jahrgangs
liegen weit auseinander — der Kapitalstock der Dienstleistungen in den USA gegen die
Landwirtschaft Brasiliens —, und **derselbe** `stufenweite`-Wert gilt für alle. Der
Jahrgangsbau weist deshalb den kleinsten und den grössten der sechzehn Startmarktwerte im
Manifest aus. Das ist die Zahl, die der Selbstspieler braucht, bevor er `startkapital` und
`stufenweite` sucht: Eine Stufe auf dem grössten Korb muss bezahlbar sein (sonst gewinnt
Klasse 1 nie), und erreichbare Stufenzahlen müssen die Aufsichtsschwellen erreichen (sonst
greift keine Gegenkraft und Maß 3 fällt auf null) — die beiden Bedingungen, die `spiel.md`
unter *Offene Entwurfsfragen* aufstellt, hier mit der Zahl versehen, an der man sie abliest.

Vier Eigenschaften, die diese Fassung binden, alle aus `spiel.md`:

1. **`ausstiegsabschlag` ist ein Schlüssel aus `parameter.toml`** (T27), kein Literal, und
   liegt in Zehntausendsteln. Der Abschlag steckt damit im Wertansatz und ist beim
   **Aufbau** bezahlt: Die Kasse gibt beim Einstieg den vollen Korbanteil ab, das
   Fondsvermögen fällt in derselben Runde um den Abschlag. Beim gewöhnlichen Ausstieg wird
   er **nicht ein zweites Mal** abgezogen; illiquide bleibt die Beteiligung über die zwei
   Runden, die `restdauer[l][s]` zählt.
2. **Der Zwangsverkauf aus Gegenkraft 1 zieht `zwangsabschlag` zusätzlich ab** — ein zweiter
   Parameterschlüssel, eine zusätzliche Strafe, keine Ersetzung des ersten.
3. **`fondsvermoegen` hat genau einen Aufrufort je Zweck und keinen zweiten Rechenweg.**
   Gelesen wird sie von der Abrechnung (Schritt 6), der Mandatsprüfung, Todesart 1, dem
   Invariantentest aus T30 Prüfung 2 und von `v(z)` in T44. Dass alle fünf dieselbe Zahl
   sehen, ist der Grund, warum „Fondsvermögen" durchgehend dasselbe heisst — *was der Fonds
   wert ist, wenn er hier aufhört*.
4. **Sie ist keine Zustandsadresse.** Der Zustand hält Kasse, Steckplätze, Anteile und
   Hebel; das Vermögen ist deren Funktion. Ein Feld dafür wäre eine zweite Kopie derselben
   Zahl — derselbe Fehlertyp, den T39 für `landespreis` und T23 Punkt 9 für die
   BACI-Konkordanz schon geschlossen haben. Die 310 aus T15 ändern sich deshalb nicht.

**Was ein Aufruf kostet, diesmal ausgezählt statt geschätzt.** Fassung 5 sprach von „wenigen
Dutzend Operationen"; der Prüfer der Runde 6 hat das unter *geprüft und nicht gezählt* als
zu klein bezeichnet und recht damit. Im ungünstigsten Fall — alle zwanzig Steckplätze
belegt, alle zwölf Beteiligungen ungleich null:

| Teil | Aufrufe | Operationen |
|---|---:|---:|
| `bip(l)` | 4 | 8 Additionen |
| `schuld(l)` | 4 | 4 `mal_geteilt` |
| `anleihekurs(l)` | 4 | 4 Additionen, 4 `teile_gerundet` |
| `anleihewert(l)` | 4 | 4 `mal_geteilt` |
| `handelsvolumen(l)` | 4 | 64 Additionen |
| `waehrungswert(l)` | 3 | 3 `mal_geteilt` |
| `korbwert(l, s)` | 12 | 12 `mal_geteilt` |
| `stufenwert(p)` | 20 | 20 `mal_geteilt` |
| `positionswert(p)` | 20 | 40 Multiplikationen |
| `beteiligung_wert(l, s)` | 12 | 24 `mal_geteilt`, 12 Multiplikationen |
| zwei Summen | 1 | 32 Additionen |
| **Summe** | | **rund 230, davon 71 `i128`-Divisionen** |

Gegen 7.500 Operationen je Weltschritt sind das **gut drei Prozent**, nicht drei Promille.
Der Planwert von 10 µs hat Bandbreite bis 30 und die Reserve rechnet mit 50; keine Zeile
von Abschnitt 10 bewegt sich. Zwei Vorgaben senken den tatsächlichen Preis weit darunter:
`positionswert` bricht bei `stufen(p) = 0` ab, bevor `markt(p)` überhaupt gerechnet wird
(die meisten Steckplätze sind die meiste Zeit leer), und **`korbwert(l, s)` wird je Aufruf
von `fondsvermoegen` einmal in ein Feld von zwölf gerechnet und von Steckplatz und
Beteiligung daraus gelesen** — nicht, um Zeit zu sparen, sondern weil „eine Bewertung, nicht
zwei" sonst nur ein Satz wäre und keine Eigenschaft des Codes.

**T48 — Die abgeleiteten Größen sind Funktionen des Zustands, keine Adressen, und sie sind
abschliessend aufgezählt.** Das ist die architektonische Antwort auf Befund 1 der Runde 6,
und sie ist die einzige, die dessen Wiederholung ausschliesst. Zwei Formeln nachzutragen
behebt den Fall; ihn zu beheben und die Menge offenzulassen, in der niemand ein Fehlen
bemerkt, behebt ihn nicht. T45 zählt **Adressen** ab und konnte die Lücke deshalb nicht
finden — `korbwert` war nie eine der 310. Diese Tabelle ist die Menge, in der er lag.

| # | Name | Klasse (T5) | Definition | steht in |
|---:|---|---:|---|---|
| 1 | `wert(menge, kurs, g)` | 2 | `mal_geteilt(menge, kurs, wechselkurs[g])` | T47 |
| 2 | `korbwert(l, s)` | 2 | `wert(kapitalstock[l][s], sektorpreis[l][s], l)` | T47 |
| 3 | `anleihewert(l)` | 2 | `wert(schuld(l), anleihekurs(l), l)` | T47 |
| 4 | `waehrungswert(l)` | 2 | `wert(handelsvolumen(l), 10.000, l)` | T47 |
| 5 | `markt(p)` | 2 | Fallunterscheidung über die drei Steckplatzarten aus T16 | T47 |
| 6 | `stufenwert(p)` | 2 | `mal_geteilt(markt(p), stufenweite, 10.000)` | T47 |
| 7 | `marktkorb(m, k)` | 2 | Σ 12 `korbwert` + Σ 4 `anleihewert`, Mengen aus `m`, Kurse aus `k` | T33 |
| 8 | `korbbestand(z)` | 2 | siehe unten | T47 |
| 9 | `bip(l)` | 2 | `Σ über die 3 Sektoren wertschoepfung[l][s]` | hier |
| 10 | `schuld(l)` | 2 | `mal_geteilt(bip(l), staatsschuld[l], 10.000)` | hier |
| 11 | `handelsvolumen(l, s)` | 2 | siehe unten; die einstellige Fassung `handelsvolumen(l)` ist ihre Summe über s ∈ {1, 2} | hier |
| 12 | `anleihekurs(l)` | 5 | siehe unten | hier |
| 13 | `landespreis(g, s)` | 5 | `lies_alt(gebiet.<g>.sektor.<s>.preis)` | T39 |
| 14 | `fondsanteil(l, s)` | 4 | `\|stufen(l, s)\| · stufenweite + anteil[l][s]` | hier |
| 15 | `positionswert(p)` | 1 | `tsd_in_cent(stufen(p) · stufenwert(p))`, 0 bei `stufen = 0` | T47 |
| 16 | `beteiligung_wert(l, s)` | 1 | Korbanteil abzüglich `ausstiegsabschlag`, dann `tsd_in_cent` | T47 |
| 17 | `fondsvermoegen(z)` | 1 | Kasse + Positionen + Beteiligungen − Hebel | T47 |
| 18 | `hub(l, i)` | **die des Instruments**: 3 für Zoll, Leitzins und Haushalt, 10 für die Regulierung | `\|lies_neu(land.<l>.instrument.<i>.stand) − lies_alt(dieselbe Adresse)\|` | hier |
| 19 | `keilhub(l, s)` | 5 | `mal_geteilt(welt.preis.<s>, hub(l, zoll), 10.000)` | hier |
| 20 | `preishub_zoll(l, s)` | 5 | `mal_geteilt(keilhub(l, s), durchgriff(l, s), 10.000)` | hier |
| 21 | `weltpreis_mit_zoll(g, s)` | 5 | `mal_geteilt(welt.preis.<s>, 10.000 + zollstand(g), 10.000)` | T28 |
| 22 | `schaden(l, i)` | 2 | `mal_geteilt(menge, verschiebung, 10.000)`, vier Zeilen, siehe unten | hier |

**Nummer 18 bis 22 sind am 2026-09-04 mit Paket `0043-t48-groessen-gegenkraft-5`
dazugekommen**, aus den Paketen 0021 (die Schadensvorschrift) und 0039 (die Zollzeile misst
nur noch den Keil). Sie sind der Fall, für den T48 gebaut wurde, ein zweites Mal: Der Entwurf
hat fünf Namen in Formeln eingeführt und seine eigene Nachziehtabelle meldete davon keinen.
Nummer 21 ist der ältere Fall — T28 **nennt** den Zollkeil („der Zollkeil je Gebiet auf dem
Weltpreis") und rechnet in seiner Preisformel mit `weltpreis_mit_zoll`, ohne ihn je zu
bilden; das war folgenlos, solange keine zweite Stelle ihn brauchte, und ist es seit Nummer 19
nicht mehr.

**Nummer 18 ist die einzige Größe der Tabelle ohne eine einzige Klasse, und das ist kein
Versehen.** `hub` ist skalen*erhaltend*: Es bildet den Betrag einer Differenz zweier Stände
**derselben** Adresse, und die Klasse des Ergebnisses ist die der Adresse. T49 gibt den vier
Instrumentenständen eines Landes nicht dieselbe Klasse — Zoll, Leitzins und Haushalt stehen
in Basispunkten (3), die Finanzmarktregulierung in Stufen (10). Eine erfundene gemeinsame
Klasse wäre hier die Fehlerart, gegen die T5 gebaut ist; die richtige Aussage ist die über
die Abbildung und nicht die über den Wert.

**Nummer 21 gilt für alle fünf Gebiete, und für die Restwelt ist `zollstand` null.** Der
Grund steht in den Daten und ist keine Wahl: T23 Punkt 5 führt `durchgriff` mit **5 × 2 = 10**
Werten (Reihenliste Nr. 16), die Restwelt nimmt an der Preisübertragung also teil und braucht
einen zollbelasteten Weltpreis; Instrumente hat sie nach T15 keine, ein `zollstand(RW)` ist
deshalb keine Adresse, sondern die Null. Ich entscheide das hier, statt es zurückzugeben, aus
demselben Grund wie die elf Startwerte in T46: Es ist keine Wahl zwischen zwei sinnvollen
Zahlen, sondern die einzige Belegung, mit der die Formel über ihren angeschriebenen
Definitionsbereich („je Gebiet") überhaupt total ist. Hält der Spielentwerfer sie für falsch,
ist es eine Zeile.

Die vier, die bisher nirgends standen:

```
bip(l)               = Σ über die 3 Sektoren  wertschoepfung[l][s]

handelsvolumen(l, s) = Σ über die 4 Gegenüber g   handel[l][g][s] + handel[g][l][s]
handelsvolumen(l)    = Σ über die 2 handelbaren Sektoren s   handelsvolumen(l, s)

anleihekurs(l)       = teile_gerundet(10.000 · (leitzins_start[l] + aufschlag),
                                      leitzins[l] + aufschlag)

korbbestand(z)       = Σ über die 12 Körbe     mal_geteilt(korbwert(l, s),  fondsanteil(l, s), 10.000)
                     + Σ über die  4 Anleihen  mal_geteilt(anleihewert(l),  |stufen(p)| · stufenweite, 10.000)
```

**`handelsvolumen` hat seit dem 2026-09-03 zwei Fassungen, und sie sind eine Größe.** Die
sektorweise ist die gebildete, die einstellige ihre Summe über die beiden handelbaren
Sektoren — nicht zwei Definitionen desselben Namens, sondern eine Definition und ihre
Aggregation. Das ist die Bedingung, unter der die Zollzeile von Gegenkraft 5 je Sektor
rechnen kann, ohne dass Nummer 4 (`waehrungswert(l) = wert(handelsvolumen(l), 10.000, l)`)
sich ändert: Dort steht weiterhin die einstellige Fassung, und sie bedeutet weiterhin
dasselbe. Der dritte Sektor kommt in keiner der beiden vor — er hat keine Handelszeile.

`handelsvolumen` liest **beide Richtungen** je Paar; die Zuordnung des dichten
Gegenüber-Index zum Gebietsindex ist die feste Abbildung aus T9 und steht im Code als
benannte Tabelle, nicht als Rechnung auf Indizes.

Die fünf aus Gegenkraft 5 und dem Zollkeil, in Rechenreihenfolge:

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

**`schaden` ist eine Funktion mit vier Zeilen und nicht vier Funktionen**, weil ihr Ergebnis
in allen vier Fällen Klasse 2 ist und ihre Stelligkeit dieselbe. Die Summe über die Sektoren
steht **innerhalb** der Zollzeile; nach aussen gibt auch sie eine Zahl je Land und
Instrument, und das ist die Zahl, die der dritte Skalenübergang aus T50 entgegennimmt.
`regulierung_last` ist der Parameterschlüssel aus T27 (Klasse 3, Basispunkte des BIP je
Regulierungsstufe); das Produkt `hub(l, regulierung) · regulierung_last` ist Stufen mal
Basispunkte je Stufe, also Klasse 3 — dieselbe Klasse wie die Verschiebung der beiden
mittleren Zeilen, und deshalb rechnen alle vier über denselben Nenner 10.000. Der Nenner von `anleihekurs` ist nach T51
nie null und nie negativ. **`fonds.marktanteil` ist keine abgeleitete Größe, sondern eine
Adresse**, in Schritt 6 geschrieben als `mal_geteilt(korbbestand(z), 10.000, markt.wert)` —
`spiel.md` schreibt dort `teile_gerundet(korbbestand · 10.000, markt.wert)`; das ist dieselbe
Zahl, aber die naive Form läuft nach T6 über, und deshalb ist die `i128`-Form verbindlich.

**Drei Größen liegen ausserhalb des Kerns** und stehen deshalb nicht in der Tabelle: `B(z)`,
`v(z)` und `e(z)` aus T44. Sie sind Prüfstandsgrößen, gehören dem Baustein `pruefstand` und
verlassen die Partie nie.

**Die Regel, die daraus folgt, und der mechanische Nachweis dazu.** Ein Name in einer Formel
dieses Dokuments oder in `spiel.md`, der weder eine Zustandsadresse aus T15 noch ein
Parameterschlüssel aus T27 noch eine Jahrgangskonstante aus T23 noch eine der
**zweiundzwanzig** Größen oben ist, **ist ein Befund und keine Bauentscheidung** — das ist
der Fall, den Befund 1 beschreibt, und der Grund, warum er teuer war: Wählt der Bauagent,
misst Maß 2 seine Wahl. Nachgewiesen wird es wie der Gleitkommaverzicht aus T4: Die
zweiundzwanzig Namen sind die öffentliche Schnittstelle des Moduls `kern::werte` (T13), und
die Deklarationen in `kern/include/kern/werte.hpp` ausserhalb von `namespace intern` gegen
diese Tabelle gelegt sind eine Prüfung von zwei Minuten. **Ich habe
sie in diesem Lauf einmal von Hand ausgeführt**, in der einzigen Form, die vor dem Bau
möglich ist: jede Formel aus `spiel.md` und aus diesem Dokument Name für Name gegen die vier
Mengen gelegt.

**Und diesmal ist die Liste, gegen die geprüft wurde, mit abgedruckt** — das ist die
Bedingung, unter der die Prüfung ein zweites Mal dasselbe ergibt. Erhoben mit
`rg -o '\b[a-z][a-z0-9_]{2,}\('` über `spiel.md`, danach jeder Treffer einzeln zugeordnet.
Übrig blieben die fünf oben; die **zweiundzwanzig Namen in den zehn Zeilen unten** sind
**keine** abgeleiteten Größen, und warum sie es nicht sind, steht daneben. Wer die Erhebung
wiederholt, darf genau diese Reste behalten und keinen weiteren:

| Name in `spiel.md` | keine abgeleitete Größe, sondern |
|---|---|
| `menge(l, i)`, `verschiebung(l, i)` | **Spaltenüberschriften der Schadenstabelle**, siehe den Absatz unten |
| `zollstand(g)` | `land.<g>.instrument.zoll.stand` in Funktionsschreibweise; für die Restwelt null (Nr. 21) |
| `stufen(p)`, `stufen(l, s)` | die Positionsstufe des Steckplatzes, `fonds.position.<l>.<s>` — eine Adresse aus T15, T5 Klasse 11, ebenfalls in Funktionsschreibweise. Sie stand schon vor diesem Paket unregistriert in den Formeln der Nummern 14 und 15; die Erhebung hat sie mitgefunden |
| `durchgriff(l, s)` | Jahrgangskonstante, T23 Punkt 5, zehn Werte |
| `welt.preis_start(s)` | Startwert des Jahrgangs, T23; steht nur in einer Kalibrierbedingung |
| `regulierung_last`, `druck_max`, `stufenweite`, `aufschlag` | Parameterschlüssel, T27 |
| `lobbypunkte_aus_schaden(tsd)` | dritter Skalenübergang, T50; **privat** in `kern::werte` und deshalb nicht in dieser Tabelle |
| `gegendruck_neu(l, i)` | der in Schritt 5 geschriebene Wert von `land.<l>.instrument.<i>.gegendruck`, also eine Adresse |
| `wmz(l, s)`, `preishub(l, s)` | Namen der **verworfenen** Vorfassung der Zollzeile. Sie stehen allein im Gegenbeispiel, mit dem `spiel.md` vorrechnet, was die Entscheidung vom 2026-09-03 beseitigt hat (8.472.000 statt null ohne jede Aktion) — ein Beleg, keine Vorschrift |
| `mal_geteilt`, `teile_gerundet`, `lies_neu`, `lies_alt`, `min`, `max`, `sgn`, `wurzel` | Rechenwerk und Zugriffsform, T6, T29, T39 |

**`menge` und `verschiebung` bekommen ausdrücklich keine Funktion, und der Grund ist T5
selbst.** Beide sind in `spiel.md` die Spaltenüberschriften einer Tabelle mit vier Zeilen,
nicht zwei Größen: `verschiebung` steht für die Zollzeile in Klasse 5 und für die drei
übrigen in Klasse 3, hat also kein einheitliches Ergebnis, das man deklarieren könnte —
genau die Eigenschaft, die T5 einer Größe abverlangt. `menge` ist immer Klasse 2, scheitert
aber an der **Stelligkeit**: In der Zollzeile ist sie `handelsvolumen(l, s)` und damit eine
Zahl je Sektor, in den drei übrigen `schuld(l)` beziehungsweise `bip(l)` und damit eine je
Land. Eine gemeinsame Funktion müsste sich entweder eine Klasse oder ein Argument
ausdenken. **Gebildet wird deshalb `schaden(l, i)`**, und die Fallunterscheidung liegt in
ihr — dieselbe Bauart wie `markt(p)` (Nr. 5), das die drei Steckplatzarten aus T16 ebenso
innen unterscheidet, statt drei Namen nach aussen zu geben.

## 9. Test- und Prüfstandsaufbau

**T30 — Acht Prüfungen, ein Aufruf.** `nacht` läuft der Reihe nach und bricht mit einem
Rückgabewert ungleich null ab, sobald eine Schwelle aus `spiel.md` gerissen ist. Was nicht
in einem Aufruf läuft, läuft nachts nicht.

| # | Prüfung | Gegenstand | Verantwortlich |
|---:|---|---|---|
| 1 | Einheitstests je Wirkungskette | jeder Pfeil aus `spiel.md` einzeln, auf einem Minimalzustand: Zoll rauf → Einfuhr runter → Preis rauf → Realeinkommen runter → Zustimmung runter. Dazu die Vorratsinvariante aus T43, geprüft für `k = 1` (fünf Runden) **und** `k = 3` (fünfzehn), damit die Verwechslung aus Befund 3 auch im Code auffällt | Testentwickler |
| 2 | Invariantentest | Summe aller Handelsbilanzen einschliesslich Restwelt = 0; Staatsschuld(t) = Staatsschuld(t−1) − Saldo; **Fondsvermögen = Kasse + bewertete Positionen + bewertete Beteiligungen − Hebel** (T47, gegen `fondsvermoegen()` und gegen eine im Test getrennt hingeschriebene Summe, damit der Test nicht die geprüfte Funktion wiederholt); die drei Sektoranteile je Gebiet summieren auf 10.000; kein Anteil ausserhalb 0…10.000; **die sieben Wertebereichsschranken aus T5/T49** (siehe darunter); jedes Partieergebnis in einem der drei Bänder aus T34 | Testentwickler |
| 3 | Determinismustest | derselbe Startwert, Modus und dieselbe Aktionsfolge ergeben dieselbe Prüfsumme — zweimal im Lauf, über Speichern und Laden hinweg, und auf jeder Zielplattform verglichen | Testentwickler |
| 4 | Regressionsbestand | gespeicherte Partien nach T22 rechnen bitgleich nach; zusätzlich eine Prüfsumme über die Kette, damit auch eine geänderte *Begründung* auffällt; mindestens eine Partie auf einem Spieljahrgang 1980 mit Basiswechsel (T8) | Testentwickler |
| 5 | Bruchlauf | 10.000 Partien mit dem Zufallsbot: kein Absturz, kein Überlauf, keine Invariantenverletzung, kein Kettenüberlauf, kein doppelter Schreibzugriff und keine Maskenverletzung (T18, T38, T39) | Bruchtester |
| 6 | **Beschränktheit** | **200 Runden ohne Spieler**; verlässt eine Größe ihren Wertebereich, gibt es einen **neunten** Rückkopplungskanal, und der ist ein Befund. Die Kanaltabelle in `spiel.md` zählt seit Fassung 5 **acht** | Bruchtester |
| 7 | Die drei Maße | Entscheidungsdichte, Strategievielfalt, Optimumsverschiebung nach den Rechenvorschriften in `spiel.md`, gegen die dortigen Schwellen: **0,4 je Partiedrittel**; **drei Klassen mit je einem Gewinner bei höchstens 25 % Abstand**; **Verschiebung ≥ 0,4** | Selbstspieler |
| 8 | Rückvergleich | im Modus `weltlauf` (T38), 31 Sollreihen plus Handelsblock, Fehlermaße nach T42, Abnahme über die **16 Prüfgegenstände mit Toleranz 2** nach T37 | Rückvergleicher |

**Die sieben Wertebereichsschranken, die Prüfung 2 je Runde prüft.** Sie folgen aus T5, T49
und T51 und stehen hier zusammen, damit der Testentwickler sie nicht aus zwölf
Tabellenzeilen zusammensuchen muss. Jede ist ein **harter Fehler**, kein Bericht:

| # | Schranke | Adressen | warum sie nicht bloß Kosmetik ist |
|---:|---|---:|---|
| 1 | `wechselkurs[g] ≥ 1` | 5 | Nenner jeder Bewertung (T47); null bricht ab, negativ dreht still jedes Vorzeichen |
| 2 | Nominalindizes `> 0` | 22 | Nenner der Ratenbildung in T42 und Faktor jeder Bewertung |
| 3 | `produktivitaet[g] > 0` | 5 | Faktor der Produktionsfunktion |
| 4 | `leitzins[l] + aufschlag ≥ 1` | 4 | Nenner von `anleihekurs`; die Schranke sitzt am Instrument (T51) |
| 5 | `0 < markt.wert < 9,2 · 10^13` | 1 | Nenner von `markt.rendite` und `marktanteil`, Überlaufschranke von `tsd_in_cent` (T47) |
| 6 | `0 ≤ druck, gegendruck ≤ druck_max` | 32 | Klasse 9; ohne Obergrenze ist Kanal 8 unbeschränkt |
| 7 | `0 ≤ fondsanteil(l, s) ≤ 10.000`, `\|stufen(p)\| ≤ stufen_max` | 12 + 20 | ein Anteil über 100 % ist kein Anteil; die Zulässigkeitsprüfung aus T32 hält ihn ein, der Test prüft, dass sie es tut |

Dazu die **zwei Gleichheiten** aus T49: `land.<L>.leitzins = land.<L>.instrument.leitzins.stand`
und `land.<L>.haushaltssaldo = land.<L>.instrument.haushalt.stand`, je Runde und je Land.

Schranke 1 und 5 sind die beiden, die ohne Test still falsch würden statt laut: Ein
negativer Wechselkurs macht aus jedem Gewinn einen Verlust, und ein Marktkorb jenseits der
Überlaufschranke stürzt zwar nach T7 ab, aber erst in `tsd_in_cent` und damit an einer
Stelle, an der niemand die Ursache sucht.

**Prüfung 6 läuft über das Ende des Jahrgangsfensters hinaus, und das braucht eine Regel.**
Die exogenen Pfade aus T25 tragen nur R+1 Stützstellen. Ab Runde R+1 werden sie **auf ihrem
letzten Wert eingefroren**, nicht fortgeschrieben, und der Lauf wird als `ueber_fenster`
gekennzeichnet. Einfrieren ist hier die schärfere Wahl: Läuft eine Größe danach weg, ist es
das Modell und nicht die Eingabe. Kosten: 200 Weltschritte.

**T31 — Der Regressionsbestand wird nie stillschweigend neu erzeugt.** Ein bewusst
geänderter Modellwert macht Prüfung 4 rot — das ist der Zweck. Die Erneuerung läuft
über einen eigenen Aufruf, der einen **Abweichungsbericht** schreibt: welche Partie,
welche Größe, alter und neuer Wert, welche Kettenglieder sich geändert haben. Dieser
Bericht ist der Gegenstand der Prüfung, nicht der neue Bestand.

**T34 — Die Ergebnisgröße ist ein `i64` in Milli-Runden; die Skala gehört `spiel.md`.**
Die dreiteilige Tabelle steht dort und wird hier **nicht** wiederholt, nicht ausgelegt und
nicht gedeckelt. Was der Architektur zusteht, ist ausschliesslich:

- Typ `i64`, Einheit Milli-Runden, **kleiner ist besser**;
- die Ordnung ist strikt total: Bei gleichem Ergebniswert entscheidet die Profilkennung,
  bei gleichem Profil der Stichprobenindex — nie die Auffindereihenfolge;
- der Median über eine gerade Anzahl ist der kleinere der beiden mittleren Werte
  (so `spiel.md`);
- **die Bereichsprüfung ist die Bandprüfung.** `spiel.md` verlangt: ein Ergebnis ausserhalb
  `1.000 … R × 1.000 + 30.000` — bei R = 24 also 1.000 … 54.000 — ist ein harter Fehler.
  Geprüft wird schärfer und ohne eigene Entscheidung, weil es aus derselben Tabelle folgt:
  Der Wert muss in **einem der drei Bänder** aus T40 liegen. Die Lücken dazwischen
  (24.001 … 24.999 und **28.001 … 30.999** bei R = 24) sind unerreichbar; ein Wert dort ist
  ein Rechenfehler und kein Ausreisser. Die Prüfung kostet zwei Vergleiche und findet genau
  die Kante, die Befund 10 an der Skala selbst gefunden hat. Die obere Lücke beginnt seit
  `spiel.md` Fassung 4 bei 28.001 und nicht mehr bei 27.001, weil die Kappung des
  Fehlbetrags entfallen ist (T40); der Bereich `1.000 … R × 1.000 + 30.000` ist davon
  unberührt, weil sein oberes Ende aus dem Todesband kommt.

**T35 — Die Ziehregel für Maß 1, ausgeschrieben, weil sie sonst am Zufallserzeuger hängt.**
`spiel.md` gibt vor: Bündelgröße gleichverteilt aus `{0,1,2,3}`, dann so viele Aktionen
ohne Zurücklegen gleichverteilt aus der Liste der zulässigen Aktionen, Doppelte im
Stichprobensatz bleiben. Das ist eindeutig bis auf das Verfahren, und ein anderes Verfahren
ergibt eine andere Stichprobe. Verbindlich ist deshalb:

1. `s = splitmix64(wurzelstartwert, jahrgang_id, parameter_pruefsumme, BUENDELZIEHUNG, t, i)`
   nach T11; `s` wird als xoshiro-Zustand fortgeschrieben, und zwar nur innerhalb dieser
   einen Ziehung.
2. `n = naechster(s) mod 4`. Ist `n` größer als die Länge `m` der Zulässigkeitsliste, gilt
   `n = m`.
3. Die Liste steht in der kanonischen Ordnung aus T32. Partielles Fisher-Yates:
   für `k = 0 … n−1` sei `j = k + (naechster(s) mod (m − k))`, tausche `L[k]` und `L[j]`.
   Das Bündel sind die ersten `n` Einträge.
4. Das Bündel wird vor dem Setzen nach Aktionskennung sortiert. Nach `spiel.md` hat keine
   Aktion einen Zeitpunkt innerhalb der Runde; die Sortierung stellt sicher, dass die
   Ziehreihenfolge das Ergebnis nicht berührt. Verletzt es `buendel_zulaessig` (T32), wird
   es auf das größte zulässige Anfangsstück gekürzt — nicht neu gezogen, weil eine
   Verwerfungsschleife die Zahl der Ziehungen zustandsabhängig machte.
5. **Die Vorratsfortschreibung der eingespeisten Runde** folgt `spiel.md`: `vi += 3·ai` am
   Rundenanfang mit dem `ai` des Referenzprofils, dann `vi −= 5` je tatsächlich gesetzter
   Aktion der Art `i`. Bei einem Bündel kleiner als drei driftet der Vorrat, und das ist
   gewollt — die Trägerpartie spielt danach mit dem Zustand weiter, den die Einspeisung
   hinterlassen hat, nicht mit einem zurechtgesetzten.

`naechster(s) mod k` ist verzerrt, sobald `k` kein Teiler von 2^64 ist. Die Verzerrung
liegt bei `m ≤ 2^32` unter 2^-32 und ist damit kleiner als jede Wirkung, die Maß 1 misst;
sie wird hier benannt statt behoben, aus demselben Grund wie in Punkt 4.

**T43 — Das Vorratsverfahren ist ein Baustein des Prüfstands, und es hat eine Invariante,
die es testbar macht.** `spiel.md` legt es fest (Vorrat `vi`, `vi += 3·ai` je Runde, drei
Steckplätze, `vi −= 5` je Steckplatz, größtes `vi` gewinnt, Gleichstand nach kleinerer
Kennung, `ai = 0` verbietet nicht, sondern schiebt ans Ende). Der Architektur stehen zwei
Dinge zu, und beide stehen hier:

- **Die Zulässigkeit, gegen die es prüft, ist die Liste aus T32** — einmal je Runde gegen
  den Rundenanfangszustand gebildet, beim Fortschreiten über die drei Steckplätze nur um
  die mit dem Bündel unverträglichen Einträge gekürzt. Kein Weltschritt, keine
  Zwischenrechnung.
- **Die Invariante, gegen die ein Einheitstest läuft:** Sind in fünf aufeinanderfolgenden
  Runden alle fünf Arten durchgehend zulässig, so steht der Vorratsvektor danach wieder auf
  `(0,0,0,0,0)`, und jede Art `i` hat genau `3·ai` der fünfzehn Steckplätze bekommen. Das
  gilt für **alle 126 Profile** — ich habe es für alle 126 durchgerechnet, und die von
  `spiel.md` selbst angegebene Probe des Referenzprofils (`1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 |
  3,4,5`) fällt dabei zeichengleich heraus. Damit ist das Verfahren nicht nur beschrieben,
  sondern hat einen Test, der eine falsche Implementierung in fünf Runden fängt statt in
  einer 24-Runden-Partie mit Median über zwanzig Startwerte.
- **Dieselbe Invariante in allgemeiner Form — und seit `spiel.md` Fassung 4 steht sie in
  beiden Dokumenten wörtlich gleich:** Nach `5k` Runden steht der Vorratsvektor wieder auf
  `(0,0,0,0,0)`, und Art `i` hat `3k·ai` der `15k` Steckplätze bekommen. Für `k = 1` sind
  das fünf Runden und `3·ai` von fünfzehn — genau der Fall, den `spiel.md` zwei Absätze
  darunter als Probe rechnet. Für `k = 3` sind es fünfzehn Runden und `9·ai` von
  fünfundvierzig. Der Satz, der in den Fassungen 2 und 3 von `spiel.md` „über 15 Runden
  … `3·ai`" sagte und beide Fälle mischte, ist dort ersetzt; die Stelle, die dreimal
  Befund war, ist geschlossen, und ich habe beide Sätze in diesem Lauf nebeneinandergelegt.
  Verbindlich für den Bau bleibt diese Invariante; der Einheitstest aus T30 Prüfung 1 prüft
  `k = 1` und `k = 3`, damit die Verwechslung auch dann auffällt, wenn jemand sie aus einer
  älteren Fassung in die Implementierung übernimmt.

**T41 — Wie das Profil die Kandidaten des Suchbots einschränkt.** Das war die Hälfte von
Befund 4, die mir gehörte: T35 schrieb die Ziehregel nur für Maß 1 aus. Verbindlich ist:

1. Das Vorratsverfahren (T43) liefert für die Runde die Artenfolge der drei Steckplätze.
   Der Suchbot sucht **über Ziele und Stufen, nie über Arten** (`spiel.md`).
2. Für Kandidat `c = 0 … 59` und Steckplatz `j = 1,2,3`: `Lj` ist die Teilliste der
   zulässigen Aktionen der Art des Steckplatzes in kanonischer Ordnung (T32), gekürzt um
   die mit den schon gewählten `x1 … xj−1` unverträglichen Einträge. Gezogen wird
   `xj = Lj[naechster(s) mod |Lj|]` mit
   `s = splitmix64(…, SUCHBOT_KANDIDATEN, runde, c)`.
3. Ein Steckplatz ohne zulässige Art entfällt; `|Lj| ≥ 1` gilt sonst immer, weil das
   Vorratsverfahren nur unter Arten wählt, die mindestens eine zulässige Aktion haben.

**Genau drei Ziehungen je Kandidat, genau 60 Kandidaten, keine Verwerfungsschleife, keine
Zählung eines Produktraums.** Doppelte Kandidaten bleiben — wie in Maß 1 —, sie kosten ein
Weltschritt und ändern kein Ergebnis. Der Preis ist damit fest bei `1 + 60` Weltschritten je
Runde, unabhängig davon, wie groß die Zulässigkeitsliste gerade ist; das ist dieselbe
Begründung wie bei T28 und der Grund, warum die Rechnung in Abschnitt 10 überhaupt trägt.

**T44 — Die Zielgröße des Suchbots ist die Ergebnisprognose des Zwischenzustands, und sie
ist abgeleitet, nicht erfunden.** T41 sagte, **welche** 60 Kandidaten entstehen, aber nicht,
**wonach** unter ihnen gewählt wird; der Gleichstandsbrecher setzte eine Vergleichsgröße
voraus, die kein Satz benannte. Solange sie fehlt, misst Maß 2 die Wahl des Bauagenten
statt das Spiel, und Maß 3 misst sie zweimal.

Nach genau einem Weltschritt läuft die Partie in aller Regel noch; die Ergebnisgröße von
`spiel.md` ist aber erst am Partieende definiert. Gebraucht wird also eine **statische**
Bewertung `B(z)` des Zwischenzustands, und sie beantwortet die Frage, die die Ergebnisgröße
selbst stellt: *Was ergäbe diese Partie, wenn sie hier endete?*

```
B(z) =  r × 1.000                      das Mandat ist in Runde r erfüllt
        30.000 + (R + 1 − d) × 1.000   in Runde d an einer Todesart gestorben
        (R + 1) × 1.000 + v(z) + e(z)  sonst — die Partie läuft weiter
```

**Alle drei Zeilen sind seit `spiel.md` Fassung 4 wörtlich die Ergebnisgröße aus `spiel.md`,
nur auf `z` gerechnet statt auf das Partieende.** Die dritte Zeile trug in Fassung 4 dieses
Dokuments noch das Literal `25.000`; sie steht jetzt als Formel in R, weil T40 keine
abgeleitete Zahl als Literal duldet und `(R+1) × 1.000` bei einem anderen Jahrgang eben
nicht 25.000 ist. Bei R = 24 ist es 25.000, also unverändert.

- `v(z) = teile_gerundet(max(0, schwelle_v − fondsvermoegen(z)) · 1.000, schwelle_v)` —
  fehlendes Vermögen in Promille seiner Schwelle. `fondsvermoegen` ist die Funktion aus
  **T47** und damit seit `spiel.md` Fassung 4 einschliesslich der zum Ausstiegswert
  bewerteten Beteiligungen; einen zweiten Rechenweg gibt es nicht.
- `e(z)` = Summe über die **zwei Länder mit dem höchsten Einfluss** (Gleichstand nach
  `LandId`) von `teile_gerundet(max(0, schwelle_e − einfluss[land]) · 1.000, schwelle_e)` —
  fehlender Einfluss in Promille seiner Schwelle. Zwei Länder, weil das Mandat zwei verlangt.
  `spiel.md` Fassung 4 hat dieselbe Regel für die Ergebnisgröße übernommen; beide Dokumente
  rechnen den Fehlbetrag jetzt mit **einer** Formel.

Beide Schwellen stehen bereits in `parameter.toml` (T27, Mandatsschwelle). **`B` hat damit
keinen freien Parameter** — keine Gewichtung, keinen eigenen Kalibrierwert, nichts, was ein
Bauagent wählen könnte. Genau das ist die Antwort auf den Einwand: Maß 2 misst nicht mehr
die Wahl des Bots, weil an dieser Stelle keine Wahl mehr besteht.

**Und `B` ist an `spiel.md` gebunden, nicht daneben gestellt.** Benennt der Entwurf die
Vergleichsgröße selbst, sticht seine Fassung diese hier, und T44 schrumpft auf die
Rechenvorschrift dazu. Ändert sich die Ergebnisgröße, ändert sich `B` mit ihr, ohne dass
jemand zwei Stellen nachführen müsste.

**Es gibt seit `spiel.md` Fassung 4 keine Abweichung mehr zwischen `B` und der
Ergebnisgröße, und das ist die eigentliche Nachricht dieser Fassung.** Fassung 4 dieses
Dokuments musste hier eine Kappung ausnehmen: `spiel.md` begrenzte damals jeden der beiden
Teile bei 1.000 Promille, und für eine Bewertungsfunktion wäre das tödlich gewesen — ein
Fonds, der zu Partiebeginn in beiden Ländern Einfluss null hat, säße bei gekappten 1.000,
und eine Verbesserung des ersten Landes von 0 auf 60 Prozent der Schwelle bliebe
**unsichtbar**. Der Spielentwerfer hat dieselbe Begründung eine Ebene höher gelten lassen
und die Kappung **ganz gestrichen**. Damit rechnen beide Dokumente in diesem Zweig
buchstabengleich, und die Stelle kann nicht mehr auseinanderlaufen.

Der Preis steht in T40 und T34 und ist zweimal eine Zahl (Bandende 27.000 → 28.000,
Lückengrenze 27.001 → 28.001). Die Schranke bleibt: `v ≤ 1.000`, solange der Fonds lebt
(bei `fondsvermoegen ≤ 0` greift Todesart 1 in derselben Runde, T33 und T47; die 1.000
erreicht nur die Rundung), und `e ≤ 2.000`, also `25.000 ≤ B ≤ 28.000` im laufenden Fall —
oberhalb des Bandes „Mandat erfüllt" (bis 24.000) und unterhalb des Todesbandes (ab 31.000).
**Daraus folgt eine Eigenschaft, die eine Bewertung haben muss und die man ihr nicht ansieht:
Der Bot zieht den Tod nie vor.** Der schlechteste laufende Zustand steht bei 28.000, der
beste Tod bei 31.000. `B` bleibt trotz der Formelgleichheit eine **botinterne** Größe: Sie
wird nie als Partieergebnis berichtet, und die Bandprüfung aus T34 gilt für sie nicht, weil
sie auf einem Zwischenzustand steht und nicht auf einem Partieende.

**Warum das den Lobbyweg nicht strukturell erschlägt** — die Frage, an der eine reine
Vermögensbewertung gescheitert wäre: Einfluss ist nach `spiel.md` der geglättete Anteil des
Fonds **am gesamten Lobbydruck** eines Landes, nicht die Wirkung des Instruments. Aktion 3
legt den Druck in derselben Runde an; sie hebt `einfluss` also schon in dem einen
Weltschritt, den der Bot vorausrechnet — gedämpft durch die Glättung, aber ungleich null und
monoton im eingesetzten Budget. Der Kassenabfluss hebt `v`, der Druck senkt `e`, und welche
Wirkung überwiegt, entscheidet der Zustand und nicht die Bauart der Bewertung. Klasse 3
**kann** damit Gewinner stellen; ob sie es tut, ist die Frage, die Maß 2 stellen soll, und
nicht die, die es beantwortet, bevor es läuft.

**Dieselbe Prüfung für die beiden anderen Klassen, weil eine einzeln geprüfte Klasse nichts
beweist.** Klasse 1 (Position) wirkt unmittelbar auf `fondsvermoegen` und damit auf `v`;
unproblematisch. **Klasse 2 (Beteiligung) hing an einer Frage, die `spiel.md` Fassung 4
entschieden hat: Die zwölf Beteiligungen zählen zum Fondsvermögen** (T47), bewertet zum
Ausstiegswert. Damit wirkt Aktion 2 auf `v` wie Aktion 1, nur illiquide und um den
Ausstiegsabschlag verringert, und `B` behandelt beide gleich. Die Erörterung der Fassung 4 —
was geschähe, wenn sie nicht dazuzählten — ist damit gegenstandslos und gestrichen; sie
hatte einen einzigen Zweck, nämlich die Frage sichtbar zu halten, bis sie beantwortet ist.

Ein zweiter Weg der Klasse 2 bleibt bei Tiefe 1 unsichtbar, und dieser Punkt bleibt
bestehen: Eine Beteiligung verbilligt nach `spiel.md` das Lobbying im selben Sektor, zahlt
sich also erst in einer späteren Runde aus. Das ist kein Fehler der Bewertung, sondern der
Preis eines Zuges Vorausschau — und damit das erste konkrete Argument für die Tiefe 2, die
Abschnitt 12 offen hält.

**Ordnung und Gleichstand.** Gewählt wird der Kandidat mit dem kleinsten `B`. Bei
Gleichstand entscheidet die lexikographisch kleinste Folge der Aktionskennungen des Bündels
in der kanonischen Ordnung aus T32, danach der kleinere Kandidatenindex `c` aus T41 — nie
die Auffindereihenfolge. Doppelte Kandidaten (T41 lässt sie ausdrücklich zu) tragen dieselbe
Kennungsfolge und denselben `B`; ihr Gleichstand fällt auf `c` und ist damit entschieden.

**Tiefe.** Bei Tiefe 1 wird `B` auf dem Zustand nach dem einen Weltschritt ausgewertet, und
es gibt **keine** Fortsetzung durch den Heuristikbot — die Wendung „Nachspiel mit dem
Heuristikbot als Fortsetzung" aus Fassung 3 war an dieser Stelle irreführend und ist der
Grund, warum der Befund entstehen konnte. Bei Tiefe `d > 1` ist der Wert eines
Zwischenknotens das Minimum von `B` über seine 60 Kandidaten, rekursiv bis zur Tiefe `d`;
das Spiel hat einen einzigen Spieler, es gibt also keinen Gegenzug und kein Maximum.

**Kosten, in dieser Fassung berichtigt.** Fassung 5 nannte „rund zwanzig
Ganzzahloperationen, also drei Promille" und zählte damit nur `v` und `e` selbst — der
Prüfer der Runde 6 hat das unter *geprüft und nicht gezählt* beanstandet und recht damit.
`v(z)` ruft `fondsvermoegen(z)`, und das sind nach der Auszählung in T47 rund **230**
Operationen, davon 71 `i128`-Divisionen; dazu eine Division für `v`, vier Vergleiche und
zwei Divisionen für `e`. Zusammen **rund 240 Ganzzahloperationen** gegen 7.500 je
Weltschritt, also gut **drei Prozent** statt drei Promille. Im Suchbot fallen sie 60-mal je
Runde an, gegen 61 Weltschritte — auch dort rund drei Prozent. Der Planwert von 10 µs hat
Bandbreite bis 30, die Reserve rechnet mit 50, und die Abkürzung bei leeren Steckplätzen
(T47) senkt den tatsächlichen Wert weiter. Die Kostenrechnung `R × (1 + 60) = 1.464` bleibt
unverändert — und genau dafür braucht es eine statische Bewertung. Ein Nachspiel bis Runde R
je Kandidat kostete `60 · Σ(R+1−t) + R = 60 · 300 + 24 = 18.024` Weltschritte je Partie, das
Zwölffache, und würfe Abschnitt 10 um.

**Die drei Bots:**

- **Zufallsbot(startwert)** — zulässige Aktionen gleichverteilt, Ziehung nach T35, ohne
  Profil. Für Prüfungen 5 und 6.
- **Heuristikbot(profil)** — Arten nach dem Vorratsverfahren (T43), innerhalb einer Art
  nach einer festen, dokumentierten Rangfolge. Keine Nachspiele, also billig. **Er ist auf
  dem Referenzprofil `(1,1,1,1,1)` die „feste Folgepolitik" von Maß 1.**
- **Suchbot(profil, kandidaten=60, tiefe=1)** — 60 Kandidaten nach T41, jeder um einen
  Weltschritt vorausgerechnet und **statisch bewertet nach T44**; gewählt wird das kleinste
  `B`, Gleichstand nach T44 und nie nach Auffindereihenfolge. Eine Fortsetzung durch den
  Heuristikbot gibt es bei Tiefe 1 nicht. Kosten je Partie `R × 61`, bei R = 24 also
  **1.464** Weltschritte.

**T36 — Was der Prüfstand zu Maß 2 und 3 fest verdrahtet.**

- **Profilliste.** Die 126 Profile werden in lexikographisch aufsteigender Ordnung von
  `(a1…a5)` erzeugt und **nullbasiert** durchnummeriert. Die **Profilkennung** ist dieser
  Index und der Gleichstandsbrecher aus `spiel.md`; sie ist Teil der Schnittstellenversion
  (T17). Zwei Festwerte als Anker für den Test, beide durchgerechnet: Das Referenzprofil
  `(1,1,1,1,1)` trägt die **Kennung 76**, und die Kennungen **0 bis 5** sind genau die sechs
  Profile `(0,0,0,a4,a5)`.
- **Strategiekern, vierwertig.** Aktionsart mit dem größten Anteil unter `{1 Position,
  2 Beteiligung, 3 Lobby}`, Gleichstand nach kleinerer Kennung; Hebel und Sichtbarkeit gehen
  nicht ein. **Sind alle drei null, ist der Kern `ohne`** — nicht 1. Das ist Befund 8, und
  er lässt sich nur an dieser Stelle beheben: Ein dreiwertiger Kern zwingt den
  Gleichstandsbrecher, eine Positionsstrategie zu behaupten, in der keine Position vorkommt.
  Profile mit Kern `ohne` laufen mit, ihr Ergebnis wird berichtet, und sie gehen in keine
  der beiden Abnahmehälften von Maß 2 ein; klassifiziert sind 120. Der Kern wird einmal je
  Profil berechnet und mit der Profilliste abgelegt, nicht je Lauf neu.
- **Fensterlogik von Maß 3.** Beide Läufe gehen über die volle Partie; die Fenster sind
  nach T40 das erste und das letzte Partiedrittel, ausserhalb gilt das Referenzprofil, und
  der Suchbot fährt innerhalb wie ausserhalb. Der Profilwechsel geschieht am Rundenanfang;
  **der Vorrat läuft über den Wechsel hinweg weiter und wird nicht zurückgesetzt**
  (`spiel.md`). Damit kostet ein Lauf dasselbe wie eine gewöhnliche Suchbotpartie, und die
  Rechnung in Abschnitt 10 trägt. Für Maß 3 sind alle 126 Profile wählbar, auch die sechs
  ohne Kern — dort misst der Vektorabstand und nicht die Klasse.
- **Was `B` aus T44 in beiden Maßen nicht ist.** Das Profilergebnis `E(p)`, der
  Gewinnvergleich gegen `R × 1.000` und die Argminima `p*` und `q*` laufen ausschliesslich
  über die **Ergebnisgröße** aus `spiel.md`, nie über `B`. `B` steuert den Bot innerhalb der
  Partie und verlässt sie nicht. Beide Maße hängen deshalb an T44 — das ist der Grund,
  warum sein Fehlen ein schwerer Befund war —, aber keines von beiden rechnet mit ihr.

**T37 — Der Rückvergleich weist je Sollreihe aus, ob sie überhaupt etwas prüfen kann — und
`spiel.md` hat entschieden, welche entscheiden.** Im Weltlauf werden die Politikinstrumente
auf die historisch tatsächlichen Werte gesetzt. Damit ist die Leitzinsreihe des Modells per
Konstruktion die Sollreihe; ihr Fehler ist null und ihre Richtungstreue eins, ohne dass das
Modell irgendetwas geleistet hätte.

| Klasse | Reihen | Zahl | Bedeutung |
|---|---|---:|---|
| `frei` | BIP (4), Sektoranteile (12), Verbraucherpreise (4), Wechselkurs (3) | 23 (19 unabhängig), dazu der Handelsblock | prüft die Maschine, entscheidet die Abnahme |
| `gesetzt` | Leitzins (4) | 4 | Eingabe des Laufs, Fehler null per Konstruktion; wird berichtet, entscheidet nichts |
| `abgeleitet` | Staatsschuldenquote (4) | 4 | Zähler folgt dem gesetzten Haushaltssaldo, nur der Nenner ist endogen; wird berichtet, entscheidet nichts |

**Die Abnahme läuft über 16 Prüfgegenstände mit Toleranz 2**, so von `spiel.md` Fassung 3
gesetzt; meine Rückfrage aus Fassung 2 ist damit beantwortet und aus Abschnitt 12
gestrichen. Prüfgegenstand ist nicht die Reihe, sondern die Größe:

| Prüfgegenstand | Zahl | zusammengefasst aus |
|---|---:|---|
| BIP je Land | 4 | je eine Reihe |
| Sektorstruktur je Land | 4 | die drei Anteilsreihen des Landes, **alle drei** müssen bestehen |
| Verbraucherpreise je Land | 4 | je eine Reihe |
| Wechselkurs je Land ausser USA | 3 | je eine Reihe |
| Handelsblock | 1 | 40 Ströme, Median des MAPE und Median der Richtungstreue; das schlechteste Fünftel wird ausgewiesen |
| **Summe** | **16** | |

Ein Prüfgegenstand besteht, wenn er beide für ihn geltenden Schwellen einhält. Der Lauf ist
bestanden, wenn höchstens zwei der sechzehn reissen; jeder gerissene wird einzeln benannt,
mit beiden Zahlen. Berichtet werden alle 31 Reihen plus die 40 Ströme, entscheiden tun die
sechzehn.

**T42 — Die drei Fehlermaße, ausgeschrieben, weil `spiel.md` sie beziffert und nicht
rechnet.** Alles in Ganzzahlen über `teile_gerundet` (T6). `S` ist die Zahl der
Stützstellen (im Prüfjahrgang 25), `V` die Menge der verwertbaren Stützstellen.

**Niveaureihen** (BIP, Sektoranteile, Staatsschuldenquote, 40 Handelsströme) —
mittlerer absoluter prozentualer Fehler in Zehntausendsteln, Schwelle **2.000 (= 20 %)**:

```
MAPE = Mittel über t ∈ V von  teile_gerundet(|modell(t) − soll(t)| · 10.000, |soll(t)|)
```

**`V` schliesst zwei Sorten Stützstelle aus, beide gezählt und ausgewiesen:** die mit
`gefuellt = 1` (so schon T24) und die mit `soll(t) = 0`. Der zweite Fall ist bei einem
bilateralen Agrarstrom zwischen zwei Ländern real, und ein Nullnenner ist nach T6 ein
Abbruch. Hat ein Strom weniger als die Hälfte verwertbarer Stützstellen, gilt er als nicht
prüfbar, geht in den Median des Handelsblocks nicht ein und wird als solcher berichtet. Die
Regel ändert keine Schwelle; sie definiert einen Fall, den `spiel.md` nicht kennt, nach dem
Muster, das T24 für gefüllte Jahre schon vorgibt.

**Ratenreihen** (Verbraucherpreise, Wechselkurs, Leitzins) — mittlerer absoluter Fehler auf
der Jahresänderungsrate, Schwelle **300 bp**:

```
rate(t) = teile_gerundet((wert(t) − wert(t−1)) · 10.000, wert(t−1))          in bp
MAE     = Mittel über t = 2 … S von |rate_modell(t) − rate_soll(t)|
```

**Eine Neubasierung nach T8 wird vor der Ratenbildung herausgerechnet:** Steigt
`basiswechsel` zwischen `t−1` und `t` um `d`, wird `wert(t)` für diese eine Rate mit
`1.000^d` multipliziert. Ohne diese Zeile meldete ein Basiswechsel einen Absturz um 99,9
Prozent als Modellfehler. Im Prüfjahrgang tritt sie nie ein — sie steht hier, weil T8 selbst
verlangt, dass kein Zweig ungeprüft bleibt, und die Regressionspartie von 1980 sie
mitnimmt.

**Richtungstreue** (alle Reihen) — Anteil der `S−1` Übergänge mit gleichem Vorzeichen, in
Zehntausendsteln, Schwelle **6.000 (= 0,6)**:

```
treue = teile_gerundet(#{t : sgn(Δmodell(t)) = sgn(Δsoll(t))} · 10.000, S − 1)
```

`sgn` ist die dreiwertige Vorzeichenfunktion auf Ganzzahlen; „beide unverändert" zählt
damit als Treffer und „einer unverändert, einer nicht" als Fehlschlag. Das folgt aus der
Schreibweise in `spiel.md` und ist keine Auslegung — auf Ganzzahlen gibt es keine andere.

**Parallelität ohne Preisgabe des Determinismus:** Jedes Nachspiel ist eine reine Funktion
von (Jahrgang, Parametersatz, Modus, Startwert, Politik, Runde, Stichprobenindex); der
abgeleitete Zufallsstartwert folgt aus genau diesem Tupel (T11). Ergebnisse werden in ein
vorab bemessenes Feld **an ihrem Index** abgelegt, nie angehängt. Jede Zusammenfassung läuft
über das sortierte Feld. Damit liefert der Prüfstand mit einem Kern und mit
zweiunddreissig dasselbe Ergebnis.

**Berichtspflicht:** Jeder Befund trägt `ticks_gesamt`, `sekunden`, `ticks_je_sekunde`, den
Modus und die Größe der Sollmaske. Die Schätzung des nächsten Abschnitts wird damit binnen
einer Nacht durch eine Messung ersetzt — und bleibt gemessen.

## 10. Was das Modell an Rechenzeit kostet

Ein Weltschritt umfasst geschätzt 7.500 elementare Ganzzahloperationen; den Löwenanteil
tragen die Markträumung (2 Sektoren × 40 Halbierungen, T28) und das Mitschreiben der
Kette (T18). Teuer sind darin die `i128`-Divisionen aus T6. **Planwert: 10 Mikrosekunden
je Schritt**, Bandbreite 5 bis 30. Die Spalte „ungünstig" rechnet mit 50 Mikrosekunden,
also dem Fünffachen des Planwerts — eine Reserve, keine Erwartung.

**Die Bewertung aus T47 ändert diese Schätzung nicht, und diesmal ist die Zahl gezählt statt
gerundet.** Ein voller Aufruf von `fondsvermoegen` kostet nach der Tabelle in T47 rund 230
Ganzzahloperationen, davon 71 `i128`-Divisionen; er fällt im `spielmodus` einmal je
Weltschritt in Schritt 6 an und im Suchbot zusätzlich je Kandidat. Das sind gut drei Prozent
eines Weltschritts, nicht die drei Promille der Fassung 5 — und weiterhin tief innerhalb der
Bandbreite 5 bis 30 µs, die der Planwert ohnehin trägt. **Im `weltlauf` fällt er gar nicht
an**, weil das Fondsteilsystem nach T38 nicht läuft; der Rückvergleich ist von der
Korrektur nicht berührt. Keine Zeile der Tabelle unten bewegt sich.

**Gegenkraft 5 kostet je Runde 106 Lesezugriffe, 16 Schreibzugriffe und 16 Aufrufe des
dritten Skalenübergangs, und auch diese Zahl ist gezählt.** Die Aufschlüsselung steht in
`spiel.md` im Abschnitt *Wo die Regel läuft, und warum Kanal 3 zyklenfrei bleibt*; sie ist
hier nachgezählt und stimmt überein:

| woher | gelesene Adressen | Zahl |
|---|---|---:|
| Schritt 3 | `lies_neu(land.<l>.instrument.<i>.stand)`, 4 Länder × 4 Instrumente | 16 |
| Schritt 4 | `lies_neu(welt.preis.<s>)`, s ∈ {1, 2} | 2 |
| Schritt 4 | `lies_neu(handel.<a>.<b>.<s>)`, der ganze Handelsblock | 40 |
| Schritt 4 | `lies_neu(land.<l>.sektor.<s>.wertschoepfung)`, für `bip`, 4 × 3 | 12 |
| Schritt 4 | `lies_neu(land.<l>.staatsschuld)`, für `schuld` | 4 |
| Vorrunde | `lies_alt(land.<l>.instrument.<i>.stand)`, für `hub` | 16 |
| Vorrunde | `lies_alt(land.<l>.instrument.<i>.gegendruck)`, für den Zerfall | 16 |
| | **Summe** | **106** |

`16 + 2 + 40 + 12 + 4 + 16 + 16 = 106`. **Gezählt sind unterschiedliche Adressen, nicht
Zugriffsvorgänge**, und an genau einer Zeile macht das einen Unterschied: Der Handelsblock
steht mit **40** und nicht mit 64. 64 wäre die Zahl der Vorgänge — vier Länder mal zwei
Sektoren mal acht Strömen je `handelsvolumen(l, s)` —, aber ein Strom zwischen zwei
spielbaren Ländern geht in zwei davon ein. Die 40 sind der Block vollständig: nach T15
`Gebiet × Gegenüber × handelbarer Sektor = 5 × 4 × 2`, und die vier `handelsvolumen`
zusammen berühren jedes geordnete Gebietspaar, weil an jedem Paar mindestens ein spielbares
Land beteiligt ist. Die 16 Schreibzugriffe sind die sechzehn `gegendruck`-Adressen, die 16
Aufrufe die des dritten Skalenübergangs aus T50 — je Adresse einer, sämtlich in Schritt 5,
und das ist zugleich der Nachweis für dessen „genau ein Aufrufort".

**Auf die Tabelle oben wirkt das nicht.** 106 Lesezugriffe und 16 Multiplikationen sind
gegen die geschätzten 7.500 Ganzzahloperationen eines Weltschritts rund anderthalb Prozent,
und Gegenkraft 5 lief in dieser Schätzung schon mit; neu ist nicht die Arbeit, sondern dass
sie abgezählt ist. **Zwei frühere Zahlen sind damit abgelöst**: die 120 der Fassung vom
2026-09-02 (sie zählte den Zollstand doppelt, obwohl die damalige Zollzeile ihn gar nicht
las) und die 112 des Prüfbefunds vom 2026-09-02 (richtig gerechnet, aber für die alte
Zollzeile). Der Weg von der einen zur anderen: `112 + 8 − 16 + 2 = 106` — der Zollstand
kommt mit `lies_neu` und `lies_alt` hinzu, beide Sektorpreiszeilen fallen ersatzlos weg, die
zwei Weltpreise treten an ihre Stelle.

**Der Planwert ist unverändert geschätzt und nicht gemessen.** Mein Logbuch verlangt, beim
nächsten Lauf zuerst den gemessenen `ticks_je_sekunde` zu lesen; es gibt ihn weiterhin
nicht. Unter `ventures/0016-…/kern/` stehen inzwischen Festkomma, Zufall, Prüfsumme,
Zustand und Schreiber, aber kein Weltschritt und kein Prüfstandslauf — gemessen ist damit
die Arithmetik, nicht die Schleife. Das bleibt die größte Unsicherheit dieses Abschnitts,
und sie steht in Abschnitt 12.

Grundlage ist die **R = 24-Runden-Partie** aus `spiel.md` Fassung 3. Alle Zeilen sind in
diesem Lauf gerechnet.

| Lauf | Weltschritte | bei 10 µs | ungünstig (50 µs) |
|---|---:|---:|---:|
| eine Partie, Heuristikbot | 24 | 0,24 ms | 1,2 ms |
| eine Partie, Suchbot (60 Kandidaten, 1 Zug voraus) | 1.464 | 15 ms | 73 ms |
| **1.000 Partien, Heuristikbot** | 24.000 | **0,24 s** | 1,2 s |
| **1.000 Partien, Suchbot** | 1.464.000 | **15 s** | 1,2 min |
| Entscheidungsdichte, K=30, ein Startwert | 9.024 | 0,090 s | 0,45 s |
| **Entscheidungsdichte, 50 Startwerte** | **451.200** | 4,5 s | 23 s |
| **Strategievielfalt, 126 Profile × 20 Startwerte** | **3.689.280** | 37 s | 3,1 min |
| **Optimumsverschiebung, zwei Fenster** | **7.378.560** | 1,2 min | 6,1 min |
| **Bruchlauf, 10.000 Zufallspartien** | **240.000** | 2,4 s | 12 s |
| **Beschränktheit, 200 Runden** | **200** | 2 ms | 10 ms |
| **Rückvergleich, ein Weltlauf** | **24** | 0,24 ms | 1,2 ms |
| **Regressionsbestand, 1.000 Partien** | **24.000** | 0,24 s | 1,2 s |
| **Nachtlauf gesamt** | **11.783.264** | **2,0 min** | **9,8 min** |

Die Zeilen im Einzelnen, damit die Summe nachzählbar ist: `Σ(R+1−t)` für `t = 1…24` ist
`300`, also `30 × 300 = 9.000` je Startwert, zuzüglich 24 Weltschritte für die
Trägerpartie ergibt **9.024**; mal 50 Startwerte **451.200**. `126 = C(9,4)`,
`1.464 = 24 × 61`, `3.689.280 = 126 × 20 × 1.464`, `7.378.560` das Doppelte davon. Die drei
Maße zusammen sind **11.519.040**, so wie `spiel.md` es rechnet. Der Nachtlauf addiert
Bruchlauf, Beschränktheit, Rückvergleich und Regressionsbestand:
`11.519.040 + 240.000 + 200 + 24 + 24.000 = 11.783.264`. Die beiden Zeilen „1.000 Partien"
sind Vergleichswerte und gehen nicht in die Summe ein.

Alles auf **einem** Kern. Mit acht Rechenkernen fällt der Nachtlauf auf rund
**15 Sekunden** beim Planwert und auf rund **1,2 Minuten** im ungünstigen Fall. Womit
parallelisiert wird, ist nach T3 offen und für dieses Dokument gleichgültig: Gebunden ist
nach Abschnitt 9, dass ein Lauf mit einem und mit zweiunddreissig Kernen dasselbe Ergebnis
liefert, nicht das Mittel, mit dem das erreicht wird.

**Die Antwort auf die Frage, die dieser Abschnitt beantworten soll: Ja, der Prüfstand kann
täglich laufen — und stündlich.** Der Engpass ist nicht die Rechenzeit, sondern das
Tokenbudget der Agenten, die die Befunde lesen.

**Die Kalibrierschleife.** Tausend Parametersätze über den vollen Maßsatz (11.519.040
Schritte je Satz) kosten 11,52 Milliarden Weltschritte, also **32,0 Stunden auf einem Kern
und 4,0 Stunden auf acht** — keine Nachtaufgabe. Nachtfähig ist die verkürzte Fassung:
Maß 1 mit 10 statt 50 Startwerten (90.240) und Maß 2 mit 5 statt 20 (922.320), Maß 3 gar
nicht, weil die Verschiebung des Optimums erst interessant ist, wenn Maß 1 und 2 halten.
Zusammen **1.012.560 Schritte je Parametersatz**, für tausend Sätze also **21 Minuten auf
acht Kernen**. Die Vorgabe an den Selbstspieler lautet deshalb: grob mit der verkürzten
Fassung suchen, die zehn besten Sätze mit der vollen nachrechnen.

**Die Gegenrechnung, die die Stackwahl trägt:** Derselbe Weltschritt kostet in Python
zwischen 0,75 und 3 Millisekunden, also das 75- bis 300-fache. Der Nachtlauf läge bei
**2,5 bis 9,8 Stunden** auf einem Kern. Er wäre damit nicht täglich, sondern gelegentlich —
und die Kalibrierschleife wäre auch in der verkürzten Fassung unmöglich. Das ist die Zahl,
an der die Wahl aus T1 hängt. Sie ist durch die kürzere Partie kleiner geworden, aber der
Abstand ist derselbe: Der Faktor entscheidet, nicht die Partielänge.

**Beim Käufer** kostet eine Runde einen Weltschritt: 10 Mikrosekunden. Der Speicherbedarf
sind 2,5 kB Zustand, unter 1 MB Jahrgänge und wenige hundert kB Kettenverlauf. Das
Produkt läuft auf allem und braucht keinen Server — die Kostenrechnung der Idee (keine
Kosten je Kunde) hält.

## 11. Auslieferung, und wo Geld anfängt

**Windows x86-64 zuerst**, Linux gleich mit (dasselbe Programm, andere Zielkennung),
**macOS nicht in Fassung eins**: Beglaubigung durch Apple kostet 99 USD im Jahr und wäre
eine Ausgabe nach Hausregel 1. Ebenso: Eine gehostete Bauumgebung ist **nicht** der
Vorgabeweg — gebaut und geprüft wird im Nachtlauf der Fabrik, auf dem Rechner des
Betreibers. Wer eine gehostete Kette will, schreibt eine Gate-Vorlage.

Die Plattformgleichheit wird nicht behauptet, sondern geprüft: Prüfung 3 vergleicht die
Prüfsummen aus dem Windows- und dem Linux-Lauf derselben Partien.

Aus `daten.md` folgt eine Auslieferungsauflage: `LIZENZEN.md` neben den Jahrgangsdateien,
eine Seite „Datenquellen" im Hauptmenü, ein Satz zur Bearbeitung („Die Ausgangsdaten wurden
aggregiert und in ganzzahlige Einheiten umgerechnet; die Quellen verantworten diese
Bearbeitung nicht") und der Hinweis, dass die IWF-Daten beim IWF kostenfrei erhältlich sind.
Alle drei Stellen werden aus dem Manifest des Jahrgangs erzeugt (T23), nicht von Hand
gepflegt — sonst weichen sie beim ersten Datenaktualisierungslauf von der Wahrheit ab.

## 12. Was ich nicht entschieden habe

Die Rückfragen der Fassungen 2 und 4 — Abnahme über 31 oder 23 Reihen, Zusammenfassung des
Handelsblocks, Beteiligungen im Fondsvermögen — sind von `spiel.md` Fassung 3 und 4
beantwortet und stehen in T37 und T47; sie sind hier gestrichen, weil eine beantwortete
Frage in dieser Liste nur noch Platz kostet. Offen bleibt:

- **Zwei Stellen in ADR 0011, die ich nicht selbst entscheiden kann. Beide blockieren
  nichts, beide gehören dem Betreiber.** *Erstens:* Massnahme 2 des ADR soll unbeabsichtigte
  Überläufe „laut statt still" machen; sie kann das nicht, weil `-fwrapv` aus Massnahme 1
  genau diese Sanitizer-Prüfung abschaltet (Beleg in T7). Ich habe die Lücke mit einer
  vierten Massnahme geschlossen statt den ADR zu ändern — das ist meine Entscheidung, die
  Frage, ob der ADR nachgeführt wird, nicht. *Zweitens:* Das erste Argument des ADR setzt
  voraus, dass der Spielstand künftig den **Zustand** speichert statt der Aktionsfolge; die
  Folgen des ADR ordnen diesen Wechsel nicht an. Bis dahin gilt T22 unverändert, und daraus
  folgt T52. Wird der Wechsel angeordnet, wird T52 billiger, aber nicht überflüssig.
- **Der Planwert von 10 Mikrosekunden je Weltschritt ist weiterhin geschätzt.** Den Kern
  gibt es inzwischen in Teilen — Festkomma, Zufall, Prüfsumme, Zustand, Schreiber —, aber
  keinen Weltschritt, also weiterhin keinen gemessenen `ticks_je_sekunde`. Liegt der
  gemessene Wert über 50 µs, trägt Abschnitt 10 nicht mehr, und dann ist die Markträumung
  anders zu bauen als über 40 Halbierungsschritte. Das ist die einzige Zahl dieses
  Dokuments, die eine Prüfung im Bau umwerfen kann — und seit T6b hängt an ihr zusätzlich
  die Frage, ob die Divisionsform den Abstand aus der Stackmessung erklärt.
- **Ob der Suchbot mit Tiefe 1 stark genug ist, damit Maß 2 das Spiel misst und nicht den
  Bot.** *Wonach* er sucht, ist seit T44 entschieden und hat keinen freien Parameter mehr;
  offen ist allein, *wie weit*. Neu gerechnet für R = 24: Tiefe 2 kostet je Partie
  `24 × (1 + 60 × 61) = 87.864`
  statt 1.464 Weltschritte, Maß 2 und 3 zusammen **664 Millionen**, also 1,8 Stunden auf
  einem Kern und **rund 14 Minuten auf acht** beim Planwert, im ungünstigen Fall 1,2 Stunden
  auf acht. Das sprengt den Nachtlauf nicht, es verlegt ihn. Tiefe 2 ist damit kein
  Ausschluss, sondern eine Entscheidung, die der Selbstspieler treffen darf, wenn Maß 2 mit
  Tiefe 1 keinen Gewinner in allen drei Klassen findet.
- **Die Zahlenwerte sämtlicher Schwellen und Elastizitäten.** Sie stehen nach T27 in der
  Parameterdatei und werden vom Selbstspieler gesucht, nicht von mir gesetzt.
- **Die konkrete Rangfolge im Heuristikbot** innerhalb einer Art. Modellierungsfrage des
  Selbstspielers; die Architektur verlangt nur, dass sie fest, dokumentiert und
  gleichstandsfrei ist.
- **Die Ausschlussregel für Stützstellen mit `soll = 0` (T42) habe ich entschieden, nicht
  offengelassen** — sie folgt dem Muster, das T24 für gefüllte Jahre schon setzt, und ohne
  sie bricht der Rückvergleich an einem bilateralen Nullstrom ab. Sie ändert keine Schwelle.
  Hält der Spielentwerfer sie für falsch, ist sie eine Zeile in T42 und sonst nichts.
- **Die elf Startwerte in T46 habe ich ebenso entschieden statt zurückgegeben**, und der
  Grund ist derselbe: Jeder von ihnen folgt aus einer Regel, die schon dasteht (Numéraire,
  Zähler ohne Vorgeschichte, Aggregatblock ohne Regierung), keiner ist eine Wahl zwischen
  zwei sinnvollen Zahlen. Eine Rückgabe hätte einen Lauf des Spielentwerfers gekostet und
  dieselben elf Zahlen ergeben. Hält er eine für falsch, ist es eine Tabellenzeile.
- **Die dreizehn Skalenklassen und die drei Übergänge habe ich entschieden statt
  zurückgegeben**, aus demselben Grund wie die elf Startwerte: Eine Einheit ist keine
  Spielfrage. Bei zweien ist der Spielraum trotzdem grösser als bei den übrigen, und ich
  nenne sie, damit sie nicht als selbstverständlich durchgehen — der **Lobbypunkt** (T50;
  jede andere gemeinsame Einheit für Druck und Gegendruck täte es auch, aber irgendeine muss
  es geben) und die **Instrumentenstufe** der Finanzmarktregulierung (T5 Klasse 10; sie
  könnte ebenso in Zehntausendsteln stehen, dann hiesse „ein Schritt" eine andere Zahl).
  Beide sind je eine Zeile, falls der Spielentwerfer sie anders will.

**Vier Beobachtungen an `spiel.md`, die ich melde statt zu ändern** (die Rolle verbietet
mir, dem Entwurf zu widersprechen; keine blockiert den Bau). **Punkt 3 ist seit dem
2026-09-04 erledigt und bleibt durchgestrichen stehen**, weil eine gelöschte Beobachtung
nicht mehr zeigt, dass die Rückgabe funktioniert hat:

1. Die Ergebnisskala trägt in der 30.000 ein echtes Literal, und das Band „überlebt" stösst
   seit dem Wegfall der Kappung dagegen, sobald `R ≥ 27` — die Schranke ist jetzt scharf
   statt grosszügig, in T40 nachgerechnet. Für 1997–2021 ist das folgenlos, und `spiel.md`
   lässt das Fenster nur enger werden. T40 zieht die Schranke bei `R ≤ 26` in den
   Jahrgangsbau, damit sie nicht erst in einer Ergebnisverteilung auffällt.
2. **Zwei Adresspaare tragen denselben Wert.** `land.<L>.leitzins` steht im Aggregatblock
   *und* als Instrumentenstand, `land.<L>.haushaltssaldo` ebenso; `spiel.md` zählt beide
   auf, T15 führt beide, und die Sollmaske aus T38 schreibt beide. Die sauberere Fassung
   hätte je Paar eine Adresse und käme auf **302 statt 310** (vier Länder mal zwei Paare;
   die Restwelt hat keine Instrumente) — das ist eine Zeile in `spiel.md` und deshalb nicht
   meine. Solange sie dasteht, gilt die Schreib- und Leseregel aus T49 und die
   Gleichheitsprüfung in T30 Prüfung 2. **Es blockiert nichts; ungeregelt wäre es der
   Fehlertyp „zwei Herren über eine Zahl", geregelt kostet es 64 Byte und einen Test.**
3. **~~„Schaden" in Gegenkraft 5 ist eine Größe ohne Rechenvorschrift.~~ Erledigt am
   2026-09-03 durch `spiel.md`, nachgetragen hier am 2026-09-04.** Der Punkt hat gefragt,
   welche der drei Zahlen — Preisverschiebung mal Menge, Wertschöpfungsverlust,
   Bewertungsverlust — gemeint ist. `spiel.md` hat **die erste** gewählt und die beiden
   anderen einzeln widerlegt (der Wertschöpfungsverlust ist gegenüber dem Zoll blind, weil
   Klasse 2 real ist; der Bewertungsverlust buchte Kanal 1 ein zweites Mal in Kanal 3). Die
   Vorschrift steht im Abschnitt *Der Schaden in Gegenkraft 5, als Rechenvorschrift*, die
   Größe als Nummer 22 in T48, die Einheit unverändert in T50. **Der Weg über die Rückgabe
   war der billigere:** Hätte ich die Zahl gefüllt, stünde in Maß 2 meine Wahl, und die
   Zollzeile hätte den Fehler bekommen, den `spiel.md` am 2026-09-03 an sich selbst gefunden
   und beseitigt hat — sie maß bis dahin die Inflation und buchte sie als Lobbyschaden.
   Zurückgegeben und einen Lauf gewartet zu haben, hat hier eine falsche Größe verhindert
   und keine Zeit gekostet.
4. **`fonds.sichtbarkeit` ist eine Adresse, Aktion 5 spricht von einer Position.**
   `spiel.md` lässt den Fonds „eine Position öffentlich offenlegen", der Zustand führt aber
   nur **eine** globale Sichtbarkeit und kein Offenlegungsmerkmal je Steckplatz. Ich lese das
   als Anteil in Zehntausendsteln (T5 Klasse 4), den Aktion 5 um einen Parameterschritt hebt
   oder senkt — das ist die einzige Lesart, die ohne neue Adressen auskommt. Meint der
   Entwurf eine Offenlegung je Steckplatz, kostet das zwanzig Adressen und damit die Zahl
   310; dann ist es keine Zeile mehr, sondern ein ADR.

## 13. Hinweis für den Projektmanager

Der Bausteinschnitt aus T13 ist zugleich der Kollisionsschnitt für Arbeitspakete: Zwei
gleichzeitig offene Pakete dürfen sich nicht im selben Baustein treffen. Die natürliche
Reihenfolge ist `kern` (Zustand, Festkomma, Zufall, Prüfsumme, Schreiber mit T18/T38/T39)
→ `daten` und `schnittstelle` parallel → `konsole` → Tests und `pruefstand` →
`oberflaeche`. Der Jahrgang (`werkzeuge/aufbereitung`) kann von Beginn an parallel laufen,
weil er nur gegen T5, T23 bis T26, T40, **T45/T46** und **T49/T51** gebaut wird und nichts
vom Kern braucht. Er trägt seit dieser Fassung zwei Prüfungen mehr, die das Vorhaben nicht
kippen, aber einen späten Abbruch ersparen: die Skalentabelle über alle 310 Adressen (T49)
und die Untergrenze `aufschlag ≥ aufschlag_min` gegen den historischen Leitzinspfad (T23
Punkt 5).

**Zwei Pakete sind vorzuziehen, weil sie Entwurfsrisiko tragen und nicht Bauaufwand:** der
Jahrgangsbau 1997 (T24 sagt, dass er scheitern kann — 25 Stützstellen ohne Füllung für alle
31 Reihen und alle 40 Handelsströme sind eine Behauptung, keine Tatsache, und der
IFS-Leitzins ist nur durch ein Indiz gestützt) und die Prüfung der vier WDI-Verdachtsreihen
7, 8, 10 und 13 auf die Drittanbieter-Ausnahme. Beide klären sich gegen Daten, nicht gegen
Code.

**Was gegenüber Fassung 2 billiger geworden ist:** Ein engeres Fenster kostet nach T40 eine
Zahl im Manifest und kein zweites Paket. Der Jahrgangsbau muss deshalb nicht mehr *vor* dem
Kern fertig sein, sondern nur vor dem ersten Rückvergleich — er bleibt trotzdem vorn, weil
er das Vorhaben kippen kann und nicht nur verzögern.

## 14. Befundabarbeitung — die vier früheren Prüfungen

**Erledigt und im Git-Verlauf.** Fassung 2 hat die acht Befunde der ersten Prüfung
beantwortet, Fassung 3 die zwölf der zweiten, Fassung 4 die drei der dritten, Fassung 5 die
zwei der vierten (Runde 4). Jede dieser Abarbeitungen ist von der jeweils nächsten Prüfung
unter deren Bedingung 5 ausdrücklich abgenommen worden; die Prüfung der Runde 6 sagt es für
Fassung 5 wörtlich: „Beide Befunde der Vorrunde sind beantwortet, je mit einer der drei
zulässigen Antworten … Beide habe ich gegen die Sache nachgeprüft, nicht gegen die
Behauptung."

Sie hier weiterzuschleppen kostete jeden Leser hundert Zeilen und brächte nichts, was
`git log -p specs/0016-…/technik.md` nicht genauer sagt. Gelöscht ist nichts: Alle vier
Abarbeitungen stehen unverändert in der Versionsgeschichte.

Was aus ihnen **fortwirkt**, steht nicht in einer Abarbeitungsliste, sondern in den
Vorgaben, die daraus entstanden sind — T38 bis T43 tragen die zwölf Antworten der zweiten
Prüfung als Regel statt als Bericht, T44 und T45 die drei der dritten, T46 und T47 die zwei
der vierten, und jede nennt an ihrer Stelle den Befund, der sie erzwungen hat.

## 15. Befundabarbeitung — Prüfung der Runde 6 vom 2026-09-01 und `spiel.md` Fassung 5

Zwei Befunde. Der Prüfer hat sie zwei Gewerken zugewiesen: Befund 1 dem Spielentwerfer,
Befund 2 mir. Beide sind einzeln abgearbeitet, weil die Rolle es verlangt und weil der
erste hier acht Stellen bewegt.

**Befund 1, `positionswert(p)` und `korbwert(l, s)` haben keine Entstehungsregel —
behoben, auf der Seite, der er gehörte, und hier vollständig aufgenommen.** `spiel.md`
Fassung 5 bildet beide Namen, dazu `anleihewert`, `waehrungswert` und den `anleihekurs`, den
der Prüfer im fünften Schritt seines Nachweises eigens benannt hatte. Ich habe die acht
Stellen abgearbeitet, die der Entwurf unter *Was der Architekt neu rechnen muss* auflistet;
hier steht, wo jede gelandet ist:

| aus `spiel.md` Fassung 5 | eingearbeitet in | nachgerechnet oder nachgewiesen |
|---|---|---|
| `korbwert`, `positionswert` und fünf weitere Namen werden gebildet | **T47**, aufgezählt in **T48** (neu) | 17 Funktionen im Kern, 3 im Prüfstand; vier (`bip`, `handelsvolumen`, `anleihekurs`, `korbbestand`) standen bis heute nirgends und stehen jetzt in T48. *Stand dieser Abarbeitung (2026-09-01); seit dem 2026-09-04 sind es 22, siehe Abschnitt 18* |
| Marktkorb mit Menge und Kurs statt „Modellmarktwerten" | **T33** Punkt 1 bis 4 | `marktkorb(m, k)`, Mengen über `lies_alt`, Kurse über `lies_neu` (T39) |
| Skalengrenze je Bewertung einmal, am äussersten Aufruf | **T47**, **T5**, **T50** (neu) | `tsd_in_cent` mit genau zwei Aufruforten; `cent_in_tsd` gestrichen, weil ohne Aufrufer |
| `stufenweite` ist ein Anteil, neuer Schlüssel `aufschlag` | **T5** Klassen 4 und 3, **T27** | elf Parameterschlüssel mit Skalenklasse, davon fünf neu; die 11 Adressen mit Herkunft `Parameter` bleiben 11 |
| `leitzins_start[l]` als Konstante des Jahrgangs | **T23** Punkt 5 | vierzehn Jahrgangskonstanten statt zehn, ohne neue Datenanforderung (erste Stützstelle von Reihe 9) |
| Kapitalstock je Sektor aus den normierten Anteilen | **T23** Punkt 1 | `Datenanker(3 × 2)`, dieselbe Regel wie bei der Wertschöpfung; T45 zählt unverändert 136 Anker |
| „sieben Kanäle" → acht, „achter Kanal" → neunter | **T18**, **T30** Prüfung 6 | zwei Stellen, beide Wortlaut |
| Leitzins-Untergrenze `1 − aufschlag` | **T51** (neu), **T23** Punkt 5, **T30** Prüfung 2 | `aufschlag_min = 1 − min(leitzins_pfad)`; beim EZB-Einlagesatz (−50 bp) sind das **51 bp**, beim Hauptrefinanzierungssatz **1 bp** |

**Und eine Sache habe ich über die Aufnahme hinaus getan, weil sie zu genau diesem Befund
gehört.** Der Prüfer schreibt: „T45s Abzählschritt findet sie nicht, weil sie **keine
Zustandsadresse** ist." Das ist der eigentliche Inhalt des Befundes, und er wäre mit zwei
nachgetragenen Formeln nicht beantwortet gewesen. **T48** zählt deshalb die Menge auf, in
der die Lücke lag — die Funktionen des Zustands —, gibt ihr eine Regel („ein Name, der
weder Adresse noch Parameter noch Jahrgangskonstante noch abgeleitete Größe ist, ist ein
Befund") und einen mechanischen Nachweis (die öffentliche Schnittstelle von `kern::werte`
gegen die Tabelle). Ich habe den Nachweis in diesem Lauf von Hand geführt, in der einzigen
Form, die vor dem Bau möglich ist; die vier Namen, die dabei herausfielen, stehen oben.

**Befund 2, `beteiligung_wert` liefert Tausend USD und wird als US-Cent verbucht — behoben,
und der Befund war richtig.** Die Formel der Fassung 5 bestand aus zwei `mal_geteilt` mit
einheitenlosen Anteilen und war damit skalenerhaltend; zwischen Ein- und Ausgabe liegt aber
der Faktor 100.000 aus T5. Die Behebung steht in **T47**: `tsd_in_cent` um den äussersten
Aufruf, dieselbe Klammer bei `positionswert`, und beides als **T50** festgeschrieben, damit
die Umrechnung einen Namen und einen Ort hat statt einer Gelegenheit.

**Die Wahl zwischen den beiden Wegen habe ich nicht getroffen, sondern übernommen.**
`spiel.md` Fassung 5 entscheidet sie unter *Wo die Skalengrenze liegt*: `korbwert` bleibt
volkswirtschaftlich, weil T33 denselben Korb bewertet und „eine Bewertung, nicht zwei" sonst
nur ein Satz wäre. Mir blieb, welche Funktion es tut und wo sie steht — und die Antwort
auf beides steht in T47 und T50.

**Die Zahlenprobe des Prüfers, mit der Behebung nachgerechnet.** Korb 21.000.000.000 (Tsd
USD), `anteil = 20`, `ausstiegsabschlag = 0`: innen `21.000.000.000 · 20 / 10.000 =
42.000.000` Tausend USD, das sind 42 Mrd USD und damit genau 0,2 % von 21 Bio USD; nach
`tsd_in_cent` **4.200.000.000.000 Cent**. Die Kasse gibt denselben Betrag ab, das
Fondsvermögen bleibt unverändert, Todesart 1 greift nicht. Der Fonds mit 42 Mio USD aus dem
Beispiel kann diese Beteiligung nicht kaufen — das ist jetzt richtigerweise eine
**Zulässigkeitsfrage** (Kasse überzogen, T32) und kein Partieende, und es ist genau die
Kalibrierbedingung, die `spiel.md` unter *Offene Entwurfsfragen* stellt.

**Derselbe Fehlertyp ein zweites Mal, an einer Stelle, die kein Befund war — und das ist der
teure Teil dieses Laufs.** Befund 2 war eine Größe mit zwei Skalen. Ich habe deshalb T5
gegen alle 310 Adressen gelegt, so wie Fassung 5 T45 gegen alle 310 gelegt hat, und **69
Adressen ohne Skalenklasse** gefunden. Darunter die 32 Druck- und Gegendruckfelder, und die
sind wörtlich Befund 2 noch einmal: `druck` entsteht aus dem Lobbybudget des Fonds
(US-Cent), `gegendruck` aus dem Schaden eines Sektors (Tausend USD), und `spiel.md` Schritt 3
verrechnet beide gegeneinander. **Der Unterschied zum ersten Mal ist, dass es nicht wie ein
Rechenfehler ausgesehen hätte, sondern wie eine Gegenlobby, die nie greift** — also wie ein
Balanceproblem, das der Selbstspieler wochenlang wegzukalibrieren versucht hätte. Die
Antwort sind die fünf neuen Klassen in **T5**, die abgezählte Zuordnung in **T49** und die
drei benannten Übergänge in **T50**.

**Die drei Punkte aus „Geprüft und nicht gezählt", weil der Prüfer sie an diesen Lauf
adressiert hat.**

1. **Die Kostenaussage zu `B` war zu klein — der Prüfer hat recht, und sie ist jetzt
   ausgezählt.** Nicht „rund zwanzig Operationen, drei Promille", sondern rund 240, davon 71
   `i128`-Divisionen, also gut drei Prozent eines Weltschritts. Nachgeführt in **T44**, in
   **T47** (mit der Auszählung je Teil) und in **Abschnitt 10**. Es war eine Zeile und kein
   Lauf, wie der Prüfer schrieb; die Auszählung hat trotzdem zwei Vorgaben erzeugt, die
   Rechenzeit sparen und zugleich eine Zusage einlösen — die Abkürzung bei `stufen(p) = 0`
   und die einmalige Berechnung der zwölf `korbwert` je Aufruf.
2. **`markt.wert` mit Herkunft `Manifest` trotz Erwähnung in der Entwurfstabelle.** Die
   Vorrangregel aus T45 löst das, der Prüfer hat es fallen lassen, der Spielentwerfer hat die
   Auflösung übernommen. Keine Änderung.
3. **`einfluss` als 0…100 in `spiel.md`, in Zehntausendsteln im Speicher.** Bleibt, wie es
   ist, und steht seit dieser Fassung zusätzlich in T49 als Klasse 4 — die Konvention ist
   damit nicht mehr nur in einem Absatz erklärt, sondern in einer Tabelle abgezählt.

**Was ich nicht entschieden habe, weil es nicht meine Rolle ist:** die Meldung des Prüfers
an den Projektmanager, dass der Rücklaufzähler mit Runde 6 bei 3 von 3 steht und die Tabelle
im Arbeitspaket seit Runde 3 nicht nachgeführt ist. Ich schreibe weder in das Arbeitspaket
noch urteile ich über `blockiert`. Was ich beitragen kann, ist die Sachlage: Befund 2 dieser
Runde war eine Skalenmischung mit Todesfolge für Klasse 2 von Maß 2, also kein
Genauigkeitsbefund; er ist behoben, und der Fehlertyp ist mit T48, T49 und T50 an drei
Stellen geschlossen statt an einer.

**Was diese Fassung nicht geändert hat:** R bleibt 24, die 310 Adressen bleiben 310, die
Herkunftszerlegung bleibt `136 + 150 + 11 + 2 + 11`, die Sollmaske 175 von 310, die
Ergebnisbänder, die vier Maße und ihre Schwellen, die drei Maße kosten 11.519.040
Weltschritte und der Nachtlauf 11.783.264. Ich habe alle Summen dieses Dokuments in diesem
Lauf erneut nachgerechnet — auch die, die ich nicht angefasst habe, weil eine Fassung, in
der die Kostenrechnung nicht angefasst wird, genau die ist, in der man es unterlässt. Neu
nachgerechnet sind die Skalenzerlegung (`3 + 71 + 36 + 22 + 22 + 5 + 5 + 25 + 32 + 4 + 83 +
2 = 310`, je Land `6 + 5 + 4 + 1 + 7 + 1 + 2 + 8 + 1 + 9 = 44`), die Operationszahl von
`fondsvermoegen` (230) und die Untergrenze `aufschlag_min` (51 bp).

## 16. Befundabarbeitung — Prüfung zu Paket `0011-stack-auf-cpp`, Runde 1 vom 2026-09-03

Drei Befunde, alle in dieser Datei, alle **behoben**. Kein Widerspruch, kein „anders gelöst":
Der Prüfer hat in allen drei Fällen recht, und in allen drei war der Fehler derselbe — beim
Übersetzen von Rust nach C++ ist eine Zusage von der Bauart mitgenommen worden, die an ihr gar
nicht hing. Was der Prüfer ausdrücklich nicht als Befund führt, ist nicht angefasst.

**Befund 1, der Ersatz für `overflow-checks` erreicht die blanke Multiplikation nicht —
behoben.** Massnahme 4 hat einen dritten Punkt bekommen: Jede Multiplikation zweier `i64`
ohne folgende Division läuft über `mal(a, b)` in `festkomma.hpp`, also über `__int128` und den
Wächter aus 4.1. Die Aufzählung der Massnahme ist zugleich vom Ort auf die **Rechenart**
umgestellt — Verengung, Strichrechnung, Multiplikation ohne Division —, denn eine Aufzählung
nach Stellen wird beim nächsten Zusatz wieder unvollständig, und genau das war passiert. Zwei
Dinge, die nicht im Befund standen und dazugehören: Ich habe `__builtin_mul_overflow` nicht
genommen und sage in T7, warum (ein Abbruchpfad statt zweier); und der Nachweis ist eine
Zuordnung statt einer Liste, in diesem Lauf einmal ausgeführt —
`grep -rn ' \* ' kern/src kern/include` gibt heute 52 Zeilen in vier zugelassenen Arten, keine
davon eine `i64`-Größenmultiplikation, weil `kern::werte` noch nicht gebaut ist.

**Befund 2, `cargo vendor` ist gestrichen statt neu gefasst — behoben.** T3 hat den Nachfolger
bekommen: Quelltext jeder Fremdbibliothek unter `fremd/<name>/`, Fassung und Commit-Kennung im
ADR, Einbindung über `add_subdirectory`; `find_package()`, `FetchContent`, `ExternalProject`
und `pkg_check_modules` sind verboten. T1 nennt die Vorgabe am Ort des alten Satzes und
verweist auf T3, damit die übersetzte Zusage dort wieder beide Hälften hat. Den Hinweis des
Prüfers, dass `find_package` **nichts herunterlädt** und deshalb an T23 vorbeigeht, habe ich
in die Vorgabe selbst geschrieben — er ist der Grund, warum ein Verbot des Ladens hier nicht
genügt.

**Befund 3, die Erzwingung von T2 liest nur `kern/CMakeLists.txt` — behoben, an beiden
Stellen.** T13 verbietet `link_libraries()` im ganzen Vorhaben und bindet
`target_link_libraries(<ziel> …)` an die `CMakeLists.txt` des Verzeichnisses, in dem `<ziel>`
angelegt wird — die Zwillingsform des dort schon stehenden Verbots von
`include_directories()`, wie der Prüfer es vorgezeichnet hat. T2 hat einen **dritten**
Mustervergleich bekommen, der über alle übrigen `CMakeLists.txt` läuft und `link_libraries(`
sowie `target_link_libraries(kern` sucht; ohne ihn wäre das Verbot eine Verabredung. Beides
gehört zusammen: T13 sagt, was nicht sein darf, T2 sagt, wie man es sieht.

**Gegen den heutigen Baum geprüft, nicht nur behauptet.** Die drei neuen Verbote sind keine
nachträgliche Verurteilung des Gebauten:
`grep -rnE 'link_libraries|include_directories|find_package|FetchContent' --include=CMakeLists.txt .`
gibt über das ganze Vorhaben **sechs** Zeilen — vier `target_include_directories` und zwei
`target_link_libraries(${name} PRIVATE …)`
für Probenziele, jede in der Datei, in der ihr Ziel entsteht. Kein Treffer auf
`link_libraries(`, `include_directories(` oder `find_package(`. Die Pakete 0004 und 0031 haben
also schon so gebaut; diese Fassung schreibt hin, was bisher Gewohnheit war.

**Zwei Meldungen an den Projektmanager, weil sie ausserhalb meines Verzeichnisses liegen und
ich dort nichts ändere.** Erstens: `festkomma.hpp` hat heute kein `mal(a, b)` — es ist die
einzige Zeile Code, die diese Nachbesserung nach sich zieht, und sie gehört in ein eigenes
kleines Paket samt Probe für den Abbruchfall. Zweitens: Die Abnahme von Paket 0004,
Bedingung 3, schreibt die zwei Mustervergleiche über `kern/CMakeLists.txt` wörtlich aus und
kennt den dritten deshalb nicht. Der Prüfer hat das gesehen und ausdrücklich gesagt, die
Lücke gehöre in die Vorgabe geschlossen; hier ist sie geschlossen. Ob 0004 nachgeführt wird,
entscheidet nicht der Architekt.

**Was diese Nachbesserung nicht geändert hat:** kein Wort an der Stacktabelle, an T6, T6b,
T2b, T9, den Massnahmen 1 bis 3, den 310 Adressen, den Formeln, den Maßen oder den
Kostenrechnungen. Der Umfang ist ein Punkt in T7, ein Absatz in T3 mit einem Halbsatz in T1
und je ein Absatz in T2 und T13 — das ist der Rücklauf und keine achte Fassung.

## 17. Paket `0026-klasse-2-preisbasis` — Umfang, und was ausdrücklich liegen bleibt

**Dieses Paket ist geliefert.** Zwei Läufe am 2026-09-04, Commits `77a84e8` und `d26eb3e`.
Ein dritter Lauf am selben Tag hat es erneut zugewiesen bekommen, weil `status: offen` im
Paket steht; er hat nichts neu entschieden, sondern nachgerechnet — unten unter „Dritter
Lauf". **Wer 0026 erneut eingeplant findet, liest zuerst diesen Abschnitt.**

**Kein Rücklauf.** Das Paket führt `Rückläufe: 0`, und unter
`ventures/0016-…/befunde/` liegt keine Prüfung zu diesem Gewerk mit `urteil: zurueck`. Es gibt
also keinen Befund abzuarbeiten; dieser Abschnitt hält stattdessen den Umfang fest, weil
Bedingung 5 der Abnahme ihn begrenzt.

**Zwei Läufe, ein Paket.** Der erste Lauf (2026-09-04 05:24, Commit `77a84e8`) hat die
Entscheidung geliefert; der zweite (2026-09-04, derselbe Tag) hat sie nachgerechnet und drei
Zahlen berichtigt. Der Grund für den zweiten Lauf liegt nicht am Gewerk: Das Paket stand nach
der Lieferung weiter auf `status: offen` und wurde deshalb erneut eingeplant
(`rueckstand.md`, „Was der Geschäftsführer entscheiden lassen muss", Punkt 2 — der fehlende
Satz „Setze `status: gebaut`" in der Rollendatei `architekt`). **Was der zweite Lauf inhaltlich
geändert hat, steht unten unter „Berichtigt"; die Entscheidung selbst ist unverändert.**

**Angefasst sind sechs Stellen und sonst keine.** Die Liste ist gegen die Hunks von
`git show 77a84e8 -- specs/0016-…/technik.md` abgezählt und nicht aus dem Gedächtnis
geschrieben — eine Umfangsangabe, die den eigenen Diff nicht deckt, verfehlt genau die
Bedingung, die sie belegen soll:

1. die Klasse-2-Zeile in **T5** samt zwei Absätzen dahinter (Basisjahr 2015, Verweis auf T53),
2. die neue Vorgabe **T53** hinter T50,
3. der Absatz in **T8**, der die Aufzählung der neu basierten Größen begründet,
4. dieser Abschnitt,
5. der **Vorspann** vor Abschnitt 1: „T1 bis T52" wird zu „T1 bis T53"; der Satz über die
   Buchstabennummern nannte als Beispiel für eine noch freie Nummer T53 und nennt jetzt T60,
   weil T53 vergeben ist; ein Absatz ordnet T53 ein. Diese Stelle ist **erzwungen**, nicht
   gewählt: Ein Vorspann, der die Vorgaben bei T52 enden lässt, widerspricht der Vorgabe, die
   vier Abschnitte weiter steht,
6. das **Frontmatter**: die Zeile `fassung`, weil sie sonst den Stand der Datei falsch angibt,
   und der neue Schlüssel `preisbasis`, weil die Kopfzeilen die tragenden Festlegungen führen
   und die Preisbasis seit T53 eine davon ist.

**Berichtigt im zweiten Lauf, ohne die Entscheidung zu berühren:** Der erste Lauf zählte die
Stellen 5 und 6 nicht auf und schrieb „vier Stellen und sonst keine" über eine Liste von sechs.
Dazu zwei Zahlen in T53, die abgeschnitten statt gerundet waren und damit gegen die einzige
Rundungsregel dieses Dokuments (T6) verstiessen: der Fehler am rechten Rand ist 3.577,80 und
steht jetzt als **3.578** statt als 3.577, und `r(2021) = 11.549/7.417 = 1,55710` steht jetzt
als **1,5571** statt als 1,5570. Der Kopfwert **2.203** (exakt 2.202,98) war richtig gerundet
und ist unverändert; das Argument hängt an keiner der beiden berichtigten Zahlen, die Schwelle
liegt bei 2.000 und der Kopfwert darüber. Alle Zahlen aus T53 sind im zweiten Lauf neu gerechnet worden — die 25 Stützstellen des
Index, der MAPE, der Startfaktor 10.000/7.417 = 1,34825, die beiden `durchgriff`-Fälle
(7.288 → 7.837 und 5.464 → 6.189), die Summe 15 + 15 + 40 + 1 = 71 und der `i64`-Kopfraum
(2,8 · 10^17 gegen 9,2 · 10^18) — und reproduzieren bis auf die zwei genannten Stellen.

**Dritter Lauf, 2026-09-04 — nachgerechnet statt neu entschieden.** Die 25 Stützstellen der
Indextabelle in T53 sind ein zweites Mal durch `10.000 · |7.417 − Index(t)| / Index(t)`
gerechnet worden, ohne die Zwischenwerte des zweiten Laufs anzusehen: Summe **55.074,54**
Zehntausendstel, Mittel **2.202,98** → 2.203, rechter Rand 2021 **3.577,80** → 3.578,
`r(2021) = 11.549/7.417 = 1,557098`, Startfaktor `10.000/7.417 = 1,348254`. Die beiden
`durchgriff`-Fälle reproduzieren über `H/N` als **7.836,99** → 7.837 und **6.189,15** →
6.189, die Summe als `15 + 15 + 40 + 1 = 71`, der `i64`-Kopfraum als 2,8 · 10^17 gegen
9,2 · 10^18. **Alle Zahlen aus T53 sind damit in zwei unabhängigen Läufen gerechnet**, und
keine hat sich geändert.

**Was der dritte Lauf trotzdem gefunden hat — eine Stelle, und sie sitzt am Übergang zu
`reihen.toml`.** T53 nannte für `N` nur Reihe 1; nach T23 Punkt 1 ist die Wertschöpfung
Reihe 1 **mal** dem Sektoranteil aus Reihe 2. `daten/reihen.toml` führt bei Reihe 16
umgekehrt `abgeleitet aus Reihe 14 (H) und Reihe 2 (N)` und nennt Reihe 1 nicht. Zwei
Dokumente gaben also zwei verschiedene und beide unvollständige Antworten auf dieselbe Frage,
und die Frage ist genau die, an der die Preisbasis hängt. T53 nennt jetzt beide Reihen und
sagt, welche von ihnen die Preisbasis trägt; die Gegenseite gehört in den Übertrag aus
Meldung 2. Das Argument des Absatzes ändert sich nicht — Reihe 2 trägt keine Preisbasis.

**Stand der drei Meldungen am 2026-09-04, nachgesehen statt vermutet.** Meldung 1 ist
angekommen: `0002` steht wieder auf `status: offen` und führt `haengt_an: [0008, 0026]`,
0008 ist `fertig`. Meldung 2 ist **halb** angekommen: das nächste Architektenpaket an der
Reihenliste ist als `0068` angelegt, **die Reihenliste-Zeile 20 und der Übertrag nach
`daten/reihen.toml` aber nicht** — eine Suche über alle Paketdateien nach „Reihe 20",
„Ausfuhrpreisindex" und „Deflator" findet ausser 0025 und 0026 selbst nichts. Solange das so
bleibt, führt `reihen.toml` bei Reihe 14 weiter den Widerspruch, den T53 aufgelöst hat, und
bei Reihe 16 die unvollständige Herkunft von oben. Meldung 3 (der lesbare PWT-Auszug) ist
unverändert offen.

Nicht angefasst: T42, T37, T47, T48, T50, T23, die Reihenliste, die 310 Adressen, die vier
Maße, die Kostenrechnungen und die Stacktabelle. Der dritte Lauf hat davon nichts berührt;
er hat innerhalb der oben aufgezählten sechs Stellen gearbeitet (T53, dieser Abschnitt, die
Zeile `fassung`) und keine siebte aufgemacht.

**Was hier hingehörte und trotzdem nicht hier steht — die Reihenliste.** T53 nennt eine neue
Reihe des Jahrgangs, und die Reihenliste in Abschnitt 7 führt sie nicht. Das ist bewusst:
Bedingung 5 nimmt die offenen Fragen aus `rueckstand.md` Punkt 6 und 7 ausdrücklich aus diesem
Paket heraus, und eine davon — das `frei` in der Spalte „Rolle" — sitzt in genau dieser
Tabelle. Zwei Pakete an einer Tabelle sind der Kollisionsfall, den der Zuschnitt vermeiden
soll. **Die Zeile steht deshalb hier, fertig für das nächste Architektenpaket:**

| Nr | Größe | Dimension | Modelleinheit | Quelle | Rolle | Verdacht |
|---:|---|---|---|---|---|---|
| 20 | Ausfuhrpreisindex der Welt, aus `NE.EXP.GNFS.CD` und `NE.EXP.GNFS.KD` | 1 | Zehntausendstel, 2015 = 10.000 | WDI | Umrechnung des Jahrgangs nach T53, **kein Soll** | nein |

Sie ändert die Sätze unter der Tabelle **nicht**: Die 31 Sollreihen bleiben die Zeilen 1, 2, 8,
9, 10 und 11, der Handelsblock bleibt ein eigener Block, und die vier Größen ohne Datenanker
bleiben die Zeilen 17, 18, 19 und die Finanzmarktregulierung. Reihe 20 ist eine
Umrechnungsgröße, keine geprüfte.

**Drei Meldungen, weil sie ausserhalb meines Verzeichnisses liegen.**

1. **An den Projektmanager, zu Paket 0002 (`kern::werte`, Fondsbewertung):** Sein
   Entblockungssatz verlangte *„eine Entscheidung des Architekten zur Klasse-2-Frage,
   schriftlich in `technik.md` oder in einem ADR"*. Sie steht in T53. **T47, T48 und T50 sind
   unberührt** — Umfang und Abnahme von 0002 brauchen keine Änderung, es kann unverändert
   zurück auf `offen`. Über 0002 hängt 0010 (Zustandsausgabe) mit daran.
2. **An den Projektmanager, zwei neue Pakete:** die Reihenliste-Zeile 20 oben (Architekt,
   zusammen mit `rueckstand.md` Punkt 6 und 7, weil dieselbe Tabelle) und der Übertrag nach
   `daten/reihen.toml` (Datenbauer): Reihe 14 bekommt den Deflatorschritt und verliert den
   Eintrag im Feld `offen`, der den Widerspruch führt; Reihe 16 bekommt die Antwort, dass
   `H` und `N` nach T53 dieselbe Preisbasis tragen; Reihe 20 kommt neu hinzu. Reihe 3 bleibt
   `art = "ungemessen"`.
3. **An den Datenbauer und über ihn an den Betreiber:** Einheit und Basisjahr des
   PWT-Kapitalstocks sind weiter ungemessen, und die Sperre ist die Werkzeugkette — vier
   PDF-Abrufe aus drei Verzeichnissen kamen unlesbar an. Es kostet **einen** lesbaren Auszug
   aus Dataverse 554025 oder 554105. Die Folge ist in T53 nach Größe geordnet: Die Einheit ist
   der schwere Teil (Faktor 1 gegen 1.000), das Basisjahr der leichte, und beide treffen keine
   Sollreihe.

**Was dieses Paket ausdrücklich nicht entschieden hat.** Die Höhe des Schadens in Gegenkraft 5
gehört `spiel.md` und dem Paket 0021. Ob Reihe 1 auf PWT wechselt, ist in `daten/reihen.toml`
als `quellenwahl = "offen"` geführt und bleibt es; wechselt sie, wandert mit ihr das gemessene
Basisjahr, und T53 ist die Stelle, an der das nachzuziehen wäre. Und die Restgrösse des
gewählten Wegs — der Abstand zwischen dem Weltausfuhrindex und den wahren bilateralen
Deflatoren der 40 Ströme — ist ungemessen und steht in T53 als solche.

## 18. Paket `0043-t48-groessen-gegenkraft-5` — Umfang und die Meldung an den Projektmanager

Vier Bedingungen, vier Stellen. Geändert sind **T48** (fünf Größen, die sektorweise Fassung
von Nummer 11, die Restetabelle), **T50** (der offengelassene Satz ist geschlossen),
**Abschnitt 10** (die Kostenzeile mit ihrer Lesetabelle) und **Abschnitt 12 Punkt 3** (die
Lücke ist keine mehr). Dazu die Zeile `abgeleitet:` im Frontmatter, die 17 nannte.

**Der Auftrag sprach von fünf Namen, gemeint waren sie am 2026-09-03 — es sind sechs, und
einer davon ist älter als das Paket.** Der Auftragstext nennt `hub`, `preishub`, `menge`,
`verschiebung` und `schaden`. Dazwischen ist Paket **0039** gelaufen: `preishub(l, s)` gibt
es nicht mehr, an seine Stelle sind `keilhub(l, s)` und `preishub_zoll(l, s)` getreten. Aus
fünf Namen wurden damit sechs, von denen zwei keine Größe wurden (`menge`, `verschiebung`,
Begründung in T48) und vier eine. Der fünfte Neuzugang, `weltpreis_mit_zoll`, stammt aus
keinem der beiden Pakete, sondern aus T28 dieses Dokuments: Die Preisformel der Markträumung
rechnet seit jeher mit ihm, gebildet wurde er nie. Gefunden hat ihn nicht das Lesen der
Auftragstabelle, sondern die Erhebung über `spiel.md`, die T48 jetzt mit abdruckt — der
Auftrag hätte ihn nicht gebracht.

**Die Abnahmebedingungen, einzeln:**

1. **Die Namensliste lässt keinen Rest.** Die Erhebung, ihre Zuordnung und die zwölf
   erlaubten Reste stehen in T48. Zwei Namen darin sind der unangenehme Fall und deshalb
   ausdrücklich aufgeführt: `wmz` und `preishub` stehen in `spiel.md` noch, aber allein im
   Gegenbeispiel, mit dem der Entwurf die verworfene Vorfassung vorrechnet. Wer sie für
   Vorschriften hält, trägt zwei tote Größen nach; wer sie stillschweigend übergeht,
   hinterlässt dem nächsten Prüfer denselben Zweifel. Sie stehen deshalb in der Restetabelle.
   **Die Erhebung hat nebenbei eine ältere Lücke gefunden**, die keinem der drei Pakete
   gehört: `stufen(p)` steht seit Fassung 5 in den Formeln der Nummern 14 und 15, ohne dass
   T48 je gesagt hätte, was es ist. Es ist eine Adresse in Funktionsschreibweise und steht
   jetzt als solche in der Restetabelle — ein Beleg dafür, dass die maschinelle Erhebung
   findet, was das Lesen einer Auftragstabelle nicht findet.
2. **`handelsvolumen`** steht als Nummer 11 in der sektorweisen Fassung, die einstellige
   daneben als deren Summe über s ∈ {1, 2}. Nummer 4 (`waehrungswert`) liest weiter die
   einstellige und ändert sich nicht.
3. **T50 und Abschnitt 12 Punkt 3** verweisen auf den Abschnitt in `spiel.md`. Der alte Satz
   steht an beiden Stellen im Wortlaut daneben, damit die Prüfungen, die ihn zitiert haben,
   zitierbar bleiben.
4. **Die Kostenzeile** nennt 106 Lesezugriffe, 16 Schreibzugriffe und 16 Aufrufe, mit der
   Lesetabelle darunter und der Summe ausgeschrieben. Ich habe sie in diesem Lauf
   nachgezählt statt übernommen; die eine Zeile, die nicht selbsterklärend ist, sind die 40
   des Handelsblocks, und warum es nicht 64 sind, steht dort.

**An den Projektmanager — welche der neuen Größen eine Schnittstelle in `kern::werte`
braucht.** Das ist die Angabe, aus der das Folgepaket zugeschnitten wird; es ist nicht meins.

| Größe | Schnittstelle in `kern::werte`? |
|---|---|
| `hub(l, i)` (Nr. 18) | **ja**, öffentlich. Argumente Land und Instrument, Ergebnis `i64` |
| `keilhub(l, s)` (Nr. 19) | **ja**, öffentlich |
| `preishub_zoll(l, s)` (Nr. 20) | **ja**, öffentlich |
| `weltpreis_mit_zoll(g, s)` (Nr. 21) | **ja**, öffentlich — und ihr Leser ist die Markträumung (T28), nicht Gegenkraft 5 |
| `schaden(l, i)` (Nr. 22) | **ja**, öffentlich, mit der Fallunterscheidung über die vier Instrumente innen |
| `handelsvolumen(l, s)` (Nr. 11) | **Formänderung an einer bestehenden.** Heute steht in `werte.hpp` `handelsvolumen(z, land)`; gebraucht werden beide Stelligkeiten, die einstellige gebildet aus der zweistelligen |
| `menge(l, i)`, `verschiebung(l, i)` | **nein**, und das ist eine Vorgabe und kein Vergessen. Begründung in T48 |
| `regulierung_last` | **nein** — Parameterschlüssel nach T27. Er gehört in `parameter.toml` (Datenbauer) und in die Struktur `Konstanten` in `werte.hpp`, wo `gegenlobby_satz` und `lobbykosten` schon stehen |

**Drei Stellen, die dadurch nachziehen und die nicht mir gehören.** Sie sind alle drei
mechanisch und keine ist eine Frage:

1. **`kern/include/kern/werte.hpp` sagt an drei Stellen „siebzehn"** — in der Kopfzeile
   (`//! kern::werte -- die siebzehn abgeleiteten Groessen aus T48`), im Absatz über den
   mechanischen Nachweis („Unten stehen siebzehn") und in der Überschrift des zweiten Blocks.
   Nach diesem Paket sind es zweiundzwanzig. Das ist Kernbauer-Arbeit, und es ist genau der
   Nachweis, den T48 vorschreibt: Wer den Kopf gegen die Tabelle legt, findet die fünf
   fehlenden Deklarationen. **Solange sie fehlen, ist der Nachweis nicht erfüllt** — der Kopf
   ist damit heute unvollständig und nicht falsch.
2. **Die Abnahme von Paket 0002** nennt die Zahl siebzehn wörtlich. Sie war zum Zeitpunkt
   ihrer Erfüllung richtig: 0002 stand am 2026-09-04 auf `fertig`, bevor dieses Paket lief —
   die Reihenfolge, die der Projektmanager dafür angeordnet hat, hat gehalten. Wer sie später
   liest, braucht diesen Absatz, sonst sieht die erfüllte Abnahme wie eine verletzte aus.
3. **`regulierung_last` fehlt in `parameter.toml`.** Folgepaket des Datenbauers, im Auftrag
   dieses Pakets schon benannt und hier nicht angefasst.

**Worauf ich unsicher bin, und es steht hier statt nur im Logbuch.** Nummer 21 ist die
einzige Stelle, an der ich etwas entschieden statt gemeldet habe: `zollstand(RW) = 0`. Der
Weg dorthin ist belegt — zehn `durchgriff`-Werte für fünf Gebiete, keine Instrumente für die
Restwelt —, aber der Definitionsbereich von `weltpreis_mit_zoll` steht nirgends
ausgeschrieben, weder in T28 noch in `spiel.md`; ich habe ihn aus dem Wort „je Gebiet" und
aus der Zahl zehn gelesen. Läuft die Markträumung in Wahrheit nur über die vier spielbaren
Länder, ist meine Zeile überflüssig und nicht falsch. Das ist die Stelle, an der ich einem
Prüfer widerspruchslos folgen würde.

## 19. Die Länderzahl als Parameter — Paket `0116`

**Was hier entschieden wird und was nicht.** Über die Zahl der Länder entscheidet dieser
Abschnitt **nichts**. `L = 4` bleibt, und die Begründung dafür steht in `spiel.md`; sie steht
nicht zur Disposition. Entschieden wird allein, ob ein weiteres Land später ein **Vorgang mit
bekannten Schritten** ist oder ein Umbau mit offenem Ende. Dazu gehören drei Dinge: die Formel
hinter jeder heute ausgeschriebenen Zahl (T54, T55), die Frage, wo die Identität eines Landes
wohnt (T56), und die Liste dessen, was **nicht** mitwächst (T57).

**Der Kern ist an dieser Stelle weiter als dieses Dokument.** `LAENDER`, `GEBIETE`,
`SEKTOREN`, `INSTRUMENTE` und `SEKTOREN_HANDELBAR` sind je eine `constexpr` in
`kern/include/kern/zustand.hpp`; die Blockanfänge werden daraus **gerechnet**
(`BASIS_RESTWELT = LAENDER * LAND_FELDER`) und von einer Kette aus `static_assert` gegen die
Gruppentabelle in T15 gehalten. Auch `daten/reihen.toml` führt je Reihe eine `dimension` und
schreibt sie als `"4 + RW"`, also als Größe und nicht als Konstante. Was fehlt, ist die
Gegenrichtung: In `specs/` stehen die abgeleiteten Zahlen als **Literale**, und nirgends steht
an einer Stelle, aus welcher Formel welche entsteht. Wer ein Land hinzufügt, muss sie heute
einzeln nachrechnen und in Prosa nachziehen. Genau das behebt T55.

### T54 — Drei Formgrössen, und alles andere folgt daraus

| Zeichen | Bedeutung | heute | Konstante im Kern |
|---|---|---:|---|
| `L` | spielbare Länder | 4 | `LAENDER` |
| `S` | Sektoren | 3 | `SEKTOREN` |
| `I` | Politikinstrumente | 4 | `INSTRUMENTE` |

Zwei weitere Größen sind **abgeleitet und keine eigene Wahl**: Die Zahl der Gebiete ist
`L + 1` — die Restwelt ist immer genau eine, wie viele Länder auch modelliert werden —, und
die Zahl der handelbaren Sektoren steht in den Formeln unten als `S − 1`.

**Zu `S − 1` gehört eine Warnung, und sie ist keine Förmlichkeit.** Der Kern führt
`SEKTOREN_HANDELBAR` als **eigene** Konstante, nicht als Rechenausdruck. Dass sie bei `S = 3`
denselben Wert hat wie `S − 1`, ist eine Tatsache über die heutige Sektorliste und keine
Regel: Wer einen vierten Sektor einführt, entscheidet dessen Handelbarkeit selbst und setzt
dann die Konstante ein, wo hier `S − 1` steht. **Für die Länderzahl, um die es in diesem
Abschnitt geht, ist der Unterschied ohne Folge** — die Zahl der handelbaren Sektoren hängt
nicht von `L` ab.

### T55 — Die Ableitungskette

Jede Zeile nennt ihre Fundstelle in diesem Dokument, damit die Formel gegen die Stelle gelegt
werden kann, die die Zahl heute ausschreibt.

| Größe | Formel in `L`, `S`, `I` | `L=4` | `L=9` | Fundstelle |
|---|---|---:|---:|---|
| Felder je spielbarem Land | `4S + 4I + 16` | 44 | 44 | T15 |
| Felder der Restwelt | `4S + 10` | 22 | 22 | T15 |
| Gebietsblock zusammen | `L(4S+4I+16) + 4S + 10` | 198 | 418 | T15, T17b |
| Handelsströme | `(L+1)·L·(S−1)` | **40** | 180 | T15, „Handel" |
| Weltpreise | `S − 1` | 2 | 2 | T15 |
| Nachahmerzähler | `L·S` | 12 | 27 | T15 |
| Positionssteckplätze | `L·(S+2)` | **20** | 45 | T16 |
| Beteiligungen | `2·L·S` | 24 | 54 | T15, Aktion 2 |
| von `L` unberührter Rest | `5S + 23` | 38 | 38 | T57 |
| **Zustand gesamt** | `L(4S+4I+16) + (L+1)L(S−1) + L(S+2) + 3LS + 5S + 23` | **310** | **740** | T15 |
| Sollmaske `weltlauf`, je Land | `4S + I + 11` | 27 | 27 | T38 |
| **Sollmaske `weltlauf`** | `L(4S+I+11) + (4S+10) + (L+1)L(S−1) + (S−1) + 3` | **175** | 450 | T38 |
| **ausserhalb der Sollmaske** | `L(3I+5) + L(S+2) + 3LS + 11` | **135** | 290 | T38 |
| Sollreihen | `L·(S+4) − 1` | **27** | 62 | Reihenliste zu T23, `reihen.toml` |

**Nachrechnung im Fliesstext, jede Zahl einmal von Hand eingesetzt.** Je Land
`4·3 + 4·4 + 16 = 44`, Restwelt `4·3 + 10 = 22`, zusammen `4·44 + 22 = 198`. Handel
`5·4·2 = 40`, Weltpreise `2`, Nachahmer `4·3 = 12`, Marktkorb `2` — die Welt also `56`.
Steckplätze `4·5 = 20`, Beteiligungen `2·4·3 = 24`, Fondsaggregat und Überrendite `5 + 3 = 8`
— der Fonds also `52`. Partie `4`. Summe `198 + 56 + 52 + 4 = 310`, dieselbe Zerlegung wie in
T15. Sollmaske `4·27 + 22 + 40 + 2 + 3 = 175`, ausserhalb `4·17 + 20 + 24 + 12 + 11 = 135`,
und beide zusammen wieder die Adressenzahl aus T15. Sollreihen `4·7 − 1 = 27`.

**Warum die Spalte `L = 9` danebensteht, obwohl dieser Abschnitt keine Länderzahl ändert.**
Sie ist keine Festlegung, sondern die einzige Probe, die etwas beweist. Heute gilt `L = I = 4`
— und deshalb ist jede Verwechslung von `L` und `I` bei den heutigen Werten **unsichtbar**:
`4S + 4I + 16` und `4S + 4L + 16` liefern beide 44. Erst bei `L ≠ I` fallen die beiden Formeln
auseinander. Die Werte der Spalte sind gegen eine **unabhängig** entstandene Rechnung gelegt,
die der Betreiber am 2026-09-05 in Paket `0118-fuenf-weitere-laender-auswaehlen` aufgeschrieben
hat: Länderblock 396, Handel 180, Nachahmer 27, Steckplätze 45, Beteiligungen 54, fester Rest
38, Zustand 740, Sollreihen 62. Alle acht Zahlen stimmen mit den Formeln überein. Das ist die
Gegenrechnung, die eine einmal gerechnete Zahl nicht hat.

**Zwei Zahlenpaare sehen bei `L = 4` gleich aus und sind es nicht.** Beide sind genau die
Sorte Falle, gegen die diese Tabelle geschrieben ist:

- **40 gegen 40.** Die 40 Handelsströme wachsen mit `(L+1)·L·(S−1)`; die **40
  Halbierungsschritte** der Markträumung aus T28 sind eine Genauigkeitsvorgabe und wachsen mit
  gar nichts. Wer beide für dieselbe Größe hält, macht aus einer Länderänderung eine Änderung
  am Lösungsverfahren.
- **27 gegen 27.** Die 27 Sollreihen wachsen mit `L(S+4) − 1`, die 27 Maskenadressen je Land
  aus T38 mit `4S + I + 11` — also gar nicht mit `L`. Bei `L = 9` stehen 62 gegen unverändert
  27.

**Woher die 27 Sollreihen kommen, und warum die Reihenliste 31 nennt.** Gezählt wird an
`daten/reihen.toml`, Stand 2026-09-05: `sollreihen_gesamt = 27`, aufgeteilt auf Reihe 1 (BIP,
`L`), Reihe 2 (Sektoranteile, `L·S`), Reihe 8 (Verbraucherpreise, `L`), Reihe 10 (Wechselkurs,
`L − 1`, weil der US-Dollar der Numéraire ist) und Reihe 11 (Staatsschuldenquote, `L`). Das
ergibt `L(S+4) − 1`. Der Fliesstext unter der Reihenliste in Abschnitt 7 nennt weiterhin 31 und
zählt Reihe 9 (Leitzins) mit vier Sollreihen mit; die Reihe hat ihre Sollrolle in Paket `0054`
verloren (`sollreihen = 0`, leere `t37_klasse`), und die Prosa ist nicht mitgezogen worden.
**Das ist kein Widerspruch zu dieser Formel, sondern die offene Arbeit von Paket
`0068-technikmd-reihe-9-ohne-sollrolle`**, das hinter diesem Paket in derselben Datei steht.
Ich fasse die Stelle nicht an; sie gehört ihm.

### T56 — Die Identität eines Landes bleibt eine namentliche Aufzählung

**Gewählt ist die erste der beiden Möglichkeiten: `Gebiet` und `Steckplatz` bleiben
namentliche Aufzählungen.** Sie werden **nicht** durch einen blanken Index plus Kürzeltabelle
ersetzt. Die eine Stelle, an der ein Land eingetragen wird, ist
**`kern/include/kern/zustand.hpp`**.

Vier Gründe, nachgemessen am 2026-09-05 und nicht vermutet:

1. **Die Aufzählung *ist* schon der Index.** `enum class Gebiet : std::uint8_t` trägt die Werte
   0 bis 4, die Adressarithmetik rechnet ausschliesslich mit `LAENDER` und `GEBIETE`, und die
   Kürzeltabelle existiert bereits: `GEBIET_KUERZEL` in `kern/src/zustand.cpp`. Es stehen also
   nicht zwei Verfahren zur Wahl, sondern ein Index **mit** Namensschicht gegen denselben Index
   **ohne** sie. Der Umbau brächte keine Rechnung in Ordnung, die heute falsch wäre.
2. **Ein falscher Index ist ein gültiger Wert, ein falscher Name nicht.** `Steckplatz{37}`
   übersetzt; `Steckplatz::Anleihe_BX` nicht. Dieses Vorhaben fängt seine Fehler mechanisch ab
   — `static_assert` auf die Blockgrenzen, Sollmaske je Runde, Bitfeld gegen den zweiten
   Schreibzugriff. Eine Prüfung zur Übersetzungszeit gegen eine zur Laufzeit zu tauschen, läuft
   dieser Bauart entgegen.
3. **Die Namen tragen die Proben.** Gezählt in `kern/`: `Gebiet::<Kürzel>` steht auf 42 Zeilen
   Quelltext (`werte.cpp` 25, `schritt.cpp` 6, `schreiber.cpp` 5, `zustand.cpp` 5,
   `zustandsausgabe.hpp` 1) und auf **141** Zeilen in den Proben (`werte_probe.cpp` 109,
   `schreiber_probe.cpp` 22, `zustand_probe.cpp` 9, `zustandsausgabe_probe.cpp` 1). Der
   Schwerpunkt liegt bei den Proben, und dort ist der Name die Aussage: `Gebiet::DE` sagt, was
   geprüft wird, `Gebiet{2}` sagt es nicht. Ein Umbau ersetzte 183 lesbare Zeilen durch 183
   nachschlagepflichtige, ohne eine Zahl zu bewegen.
4. **T17 macht die Adresse zum Bestandteil der Schnittstellenversion.** `fonds.position.CN.1`
   und `handel.DE.CN.1` tragen das Kürzel im Text. Die Identität eines Landes ist damit ohnehin
   schon namentlich; eine Aufzählung, deren Namen den Adressen folgen, ist die Fassung
   derselben Sache, die der Übersetzer prüfen kann.

**Der Preis dieser Wahl, ausgeschrieben, weil er real ist.** Bei `L = 5` bekommt
`enum class Steckplatz` fünf weitere Werte (`Sektor_XX_1` bis `_3`, `Waehrung_XX`,
`Anleihe_XX`), und weil die Plätze nach Art gruppiert sind, verschieben sich die
Ordnungszahlen der Währungs- und Anleiheplätze. Das ist Handarbeit, und Handarbeit driftet.

**Dagegen steht die Regel, die diese Wahl überhaupt erst tragfähig macht: Die Formel bewacht
die Aufzählung.** In `zustand.hpp` gehört je ein `static_assert` gegen T55 neben die betroffene
Konstante — `STECKPLAETZE == LAENDER * (SEKTOREN + 2)`,
`LAND_FELDER == 4 * SEKTOREN + 4 * INSTRUMENTE + 16`, `RESTWELT_FELDER == 4 * SEKTOREN + 10`,
und `STECKPLATZ_WAEHRUNG_ERSTER` sowie `STECKPLATZ_ANLEIHE_ERSTER` gegen `LAENDER * SEKTOREN`
beziehungsweise `LAENDER * (SEKTOREN + 1)`. Ein vergessener Eintrag bricht dann die
Übersetzung, statt eine Adresse still zu verschieben. **Ohne diese Zusicherungen wäre die Wahl
falsch** — sie sind der Grund, warum eine handgeführte Liste hier zulässig bleibt.

**Damit „die eine Stelle" wörtlich stimmt, muss eine Zeile umziehen.** `GEBIET_KUERZEL` steht
heute in `kern/src/zustand.cpp`, die Aufzählung in `kern/include/kern/zustand.hpp` — ein Land
hinzuzufügen berührt also zwei Dateien. Die Tabelle gehört als `constexpr std::array` neben
die Aufzählung in den Kopf, mit `static_assert(GEBIET_KUERZEL.size() == GEBIETE)`. Danach ist
der vollständige Vorgang für ein weiteres Land im Kern: ein Wert in `Gebiet` vor `RW`, `RW` um
eins höher, `LAENDER` um eins höher, ein Kürzel in `GEBIET_KUERZEL`, `S + 2` Werte in
`Steckplatz` — alles in einer Datei, alles von `static_assert` bewacht. Die Datenarbeit, die
daneben anfällt, steht in `0141-pruefliste-fuenftes-land` und ist der grössere Posten.

Beides — die Zusicherungen und der Umzug — ist **Entwurf, nicht Ausführung**, und braucht je
ein Kernbauer-Paket. Ich schreibe keinen Code.

### T57 — Was bei `L = 5` gleich bleibt

Von den Zustandsadressen sind **38 von `L` unberührt** (`5S + 23`, bei `S = 3` also 38) — und
das ist dieselbe Zahl, die Paket `0118` unabhängig als „fest" ausweist:

| bleibt gleich | Zahl | warum |
|---|---:|---|
| Restwelt-Block | `4S + 10` = 22 | Die Restwelt ist definitionsgemäss **eine**: die Welt abzüglich der Modellländer. Ein weiteres Land verkleinert ihren Inhalt, nicht ihre Adressenzahl |
| Fondsaggregat | 5 | Kasse, Hebelstand, Sichtbarkeit, Anlegerbestand, Marktanteil sind Eigenschaften des Fonds, nicht der Landkarte |
| Überrendite | 3 | drei Runden Gedächtnis, an die Todesbedingung gebunden |
| Marktkorb | 2 | ein Korb, ein Wert, eine Rendite — unabhängig davon, worüber er gebildet wird |
| Weltpreise | `S − 1` = 2 | je handelbarem Sektor einer, nicht je Land |
| Partie | 4 | Runde, Jahrgangskennung, Parametersatz-Prüfsumme, Mandatsstand |

Ausserhalb des Zustands bleibt ebenfalls unverändert, und hier liegt der eigentliche Punkt:
**die Todesarten**, die **drei Aktionen je Runde**, die **Partielänge `R`**, die dreizehn
Skalenklassen aus T5, die fünf Herkunftsarten aus T45, die 40 Halbierungsschritte aus T28 und
die vier Maße aus `agentenbau.md`. Sie sind an Spielbalance, Skalenordnung oder Messverfahren
gebunden — an keiner Stelle an die Ländergeometrie. Ein Land mehr ist für sie kein Ereignis.

**Eine Berichtigung gehört hierher, und sie betrifft die Steckplätze.** Der Auftragstext zu
`0116` nennt die zwanzig Steckplätze unter dem, was *nicht* mitwächst. Nach T15 und T16 sind
sie `L·(S+2)` — `L·S` Land×Sektor, `L` Währung, `L` Anleihe —, also **geometrisch und
wachsend**; und der Betreiber hat am 2026-09-05 in `0118` ausdrücklich „Weg A" gewählt: Die
Steckplätze wachsen mit `L`, bei `L = 9` auf 45. Beide Aussagen stammen vom selben Tag; die
jüngere sticht. **Was an den Steckplätzen wirklich nicht mitwächst, ist die Zahl der Aktionen
je Runde** — und genau daraus entsteht die Frage nach der Entscheidungsdichte, die `0118` zu
beantworten hat. Die Adressenzahl ist Geometrie, die Knappheit ist Balance; dieser Abschnitt
trennt beides und entscheidet nur das Erste.

Gleiches in halb: **der Fondsblock wächst zur Hälfte mit.** Von seinen 52 Adressen sind 8
`L`-frei (Aggregat 5, Überrendite 3), 44 sind Geometrie (Steckplätze `L(S+2)`, Beteiligungen
`2LS`). „Der Fondsblock wächst nicht" wäre für die kleinere Hälfte richtig und für die
grössere falsch.

### Was dieser Abschnitt nicht angefasst hat

Nichts. Er ist **ausschliesslich beschreibend**: Er trägt keine Zahl in einem bestehenden
Abschnitt nach, ändert keine Tabelle, keinen `static_assert` und keine Zeile Quelltext. Die
Formeln sind gegen die bestehenden Stellen gelegt und stimmen mit ihnen überein; die eine
Abweichung — 27 gegen 31 bei den Sollreihen — ist oben benannt und gehört Paket `0068`. Die
Länderzahl selbst, die Auswahl eines weiteren Landes und der Umbau des Kerns sind eigene
Pakete und hier nicht entschieden.

## 20. Zwei Länderklassen und der geschätzte Politikpfad — Paket `0117`

**Was hier entschieden wird und was nicht.** Dieser Abschnitt wählt **kein** Land aus, sucht
**keine** Zinsreihe, ändert **keine** Zeile des Kerns und fasst die heutigen vier Länder nicht
an. Entschieden wird dreierlei: was die beiden Klassen sind und wie sich die Ausnahme von den
Prüfgegenständen **mechanisch** halten lässt (T58); wie die sechzehn Prüfgegenstände
parametrisch zu zählen sind (T59); und in welcher Reihenfolge ein fehlender Politikpfad zu
ersetzen ist, samt der Kennzeichnung, die eine Schätzung als Schätzung erkennbar hält (T60,
T61).

**Der Anlass steht in den Daten und nicht in der Zukunft.** `daten/reihen.toml` führt Reihe 9
(Leitzins) mit `deckung_urteil = "reisst -- DEU und CHN tragen in dieser Quelle keinen
einzigen Wert, USA endet 2020"`. Die Frage nach dem geschätzten Politikpfad ist damit keine
Vorsorge für ein künftiges fünftes Land, sondern eine offene Frage an zwei der heutigen vier —
und genau deshalb braucht sie eine Regel, die nicht von Fall zu Fall entschieden wird.

### T58 — Die beiden Klassen, und was „ausgenommen" mechanisch heisst

| Klasse | Politikpfad | Datenreihen | im `weltlauf` | in den Prüfgegenständen |
|---|---|---|---|---|
| **Rückvergleichsland** | aus gemessener oder abgeleiteter Quelle (T60 Stufe 1–3) | alle aus gemessener Quelle | läuft, innerhalb der Sollmaske | **ja** — BIP, Sektorstruktur, Preise, Wechselkurs zählen |
| **Spielland** | darf geschätzt sein (T60 Stufe 4) | für den `spielmodus`, nicht für den Rückvergleich | **stillgelegt**, vollständig ausserhalb der Sollmaske | **nein** — keine seiner Größen geht in ein Fehlermaß ein |

**Die heutigen vier Länder — USA, China, Deutschland, Brasilien — sind Rückvergleichsländer**,
alle vier, und dieser Abschnitt ändert daran nichts. Ihre sechzehn Prüfgegenstände nach T37
bleiben, was sie sind.

**Warum die blosse Ausnahme von den Fehlermaßen nicht genügt — das ist der eine Befund dieses
Abschnitts.** Der Auftrag beschreibt die Ausnahme als Eigenschaft der *Auswertung*: das BIP
des Spiellands geht in kein Fehlermaß ein. Das reicht nicht. Das Modell ist gekoppelt: Schritt
4 rechnet aus dem Politikpfad BIP, Preise und Wechselkurs, die Markträumung bildet daraus
Weltpreise, und die Weltpreise stehen im BIP **jedes anderen Gebiets**. Ein Spielland, das mit
einem erfundenen Leitzins endogen mitrechnet, verschiebt damit das BIP von Deutschland — einen
Prüfgegenstand — ohne je selbst gemessen zu werden. `spiel.md` hat den Satz dafür schon:
*„Ein Lauf mit erfundener Politik prüfte nur die halbe Maschine."* Die Ausnahme muss deshalb
im **Lauf** sitzen, nicht in der Auswertung.

Drei Wege, an den Kriterien dieses Vorhabens gemessen:

| | **A Stilllegung** (gewählt) | **B exogene Führung** | **C blosse Maskierung** |
|---|---|---|---|
| Was das Spielland im `weltlauf` tut | nichts; seine Adressen liegen ausserhalb der Sollmaske | es läuft mit, aber jede seiner Größen kommt je Runde aus gemessenen Daten | es rechnet endogen mit dem geschätzten Pfad |
| Wirkt der geschätzte Pfad auf einen Prüfgegenstand? | nein | nein, solange **jede** seiner übrigen Reihen gemessen ist | **ja**, über Handel und Weltpreise |
| Womit ist das belegt? | zweiseitige Maskenprüfung je Runde (T38) und eine Giftprobe | Reihe für Reihe nachgesehen, je Jahrgang neu | gar nicht |
| Datenkosten je Spielland | Startwerte und der geschätzte Pfad, beides nur für den `spielmodus` | Stützstellen für BIP, Sektoranteile, Preise, Kurs — fast ein Rückvergleichsland | wie B |
| Kosten am Jahrgang | der Restweltrest wird je Modus einmal gebildet | einmal | einmal |
| gespeicherte Rückvergleichsergebnisse | bleiben gültig | verfallen bei jedem neuen Spielland | verfallen ebenso |
| was der Rückvergleich gewinnt | nichts | ein gemessenes Gebiet mehr im Handelsblock | nichts |

**Gewählt ist A**, und der Grund ist die dritte Zeile: Nur dort ist die Ausnahme eine Prüfung
und kein Argument. B ist fachlich nicht schlechter — es macht den Rückvergleich sogar
genauer —, aber es kostet je Spielland fast die Datenarbeit eines Rückvergleichslands und
entwertet bei jedem Zuwachs die gespeicherten Ergebnisse des Rückvergleichs, also das
teuerste Gut dieses Vorhabens. C ist der Weg, den der Auftragstext wörtlich beschreibt, und
er ist undicht.

**Vier Festlegungen, mehr braucht A nicht:**

1. **Ein Ort für die Menge.** `aktive_gebiete(modus)` liefert im `spielmodus` alle Gebiete, im
   `weltlauf` die Rückvergleichsländer und die Restwelt. **Jede** Schleife über Gebiete —
   Markträumung, Handel, Preisübertragung, Invariantenprüfung, Zustandsausgabe — läuft über
   diese eine Menge. Ein zweiter Ort, an dem die Menge gebildet wird, ist ein Fehler derselben
   Familie wie die doppelte Konkordanz aus T23 Punkt 9.
2. **Ausserhalb der Maske, nicht per Vortrag.** Im `weltlauf` liegen alle Adressen eines
   Spiellands und alle Handelszeilen, an denen es beteiligt ist, **ausserhalb** der Sollmaske
   aus T38. Sie behalten ihren Startwert und werden nicht geschrieben — dieselbe Bauart, mit
   der der Fondsblock im `weltlauf` schon heute nicht gerechnet wird statt abgefangen zu
   werden. Der zweiseitige Maskentest macht daraus je Runde einen harten Fehler: Wer schreibt,
   fliegt auf.
3. **Der Restweltrest bekommt einen Modus.** T23 Punkt 10 bildet die Restwelt heute als
   „Weltreihe minus die vier Länder" und ihre Handelszeilen als „Gesamtein- und -ausfuhr minus
   die Ströme zu den drei anderen". Mit zwei Klassen lautet die Regel: im `weltlauf` minus die
   **Rückvergleichsländer**, im `spielmodus` minus **alle Politikländer**. Damit tragen der
   Restweltblock (`4S + 10`, also 22) und die Restwelt-Handelszeilen (`2·L_R·(S−1)`, bei
   `L_R = 4` also 16) je Jahrgang zwei Werte, zusammen 38 Adressen; die Handelszeilen zwischen
   Restwelt und Spielland gibt es nur im `spielmodus`. **Ohne diesen zweiten Rest schrumpft die
   Welt des `weltlauf` um die Masse des Spiellands** — `handel.DE.RW.*` verlöre den Anteil, der
   heute nach dorthin geht —, und der Handelsblock ist ein Prüfgegenstand. Die Datenseite
   verschöbe dann genau das, was Festlegung 2 auf der Rechenseite schützt.
4. **Die Giftprobe, weil die Maske nur die Schreibseite deckt.** „Keine Adresse ausserhalb der
   Maske berührt" fängt den Schreibzugriff; eine Regel, die eine Spiellandadresse nur **liest**,
   bleibt unsichtbar. Der Prüfstand fährt deshalb je Jahrgang einen `weltlauf` zweimal: einmal
   gewöhnlich, einmal mit allen Spiellandadressen auf einem absurden Wert (Wertebereichsrand
   nach T5/T49). **Beide Läufe müssen in allen Maskenadressen bitgleich sein.** Weicht eine ab,
   liest eine Regel, was sie nicht lesen darf. Kosten: ein zusätzlicher Lauf über `R`
   Weltschritte je Jahrgang, also nichts gegen die drei Selbstspielmaße.

**Der Wechsel der Klasse ist eine Richtung und ein Vorgang.** Wird der Politikpfad eines
Spiellands später gemessen (T60 Stufe 1) oder ohne freien Parameter abgeleitet (Stufe 2), wird
es ein Rückvergleichsland: `L_R` wächst um eins, die Prüfgegenstände um vier, seine Reihen
kommen in die Sollmaske, und die gespeicherten Rückvergleichsergebnisse werden **einmal** neu
gebildet, weil sich der Restweltrest ändert. Die Gegenrichtung — ein Rückvergleichsland wird
Spielland — ist kein Datenvorgang, siehe T60.

### T59 — Die Zählung, parametrisch in der Zahl der Rückvergleichsländer

`L_R` ist die Zahl der Rückvergleichsländer, `L_S` die der Spielländer, und
`L = L_R + L_S` ist die Länderzahl aus T54. `n` ist 1, wenn das Numéraireland (heute die USA)
ein Rückvergleichsland ist, sonst 0; heute ist `n = 1`.

| Größe | Formel | heute (`L_R = 4`) | `L_R = 4`, `L_S = 5` | `L_R = 9` | Fundstelle |
|---|---|---:|---:|---:|---|
| BIP je Land | `L_R` | 4 | 4 | 9 | T37, Reihe 1 |
| Sektorstruktur je Land | `L_R` | 4 | 4 | 9 | T37, Reihe 2 |
| Verbraucherpreise je Land | `L_R` | 4 | 4 | 9 | T37, Reihe 8 |
| Wechselkurs je Land ausser dem Numéraire | `L_R − n` | 3 | 3 | 8 | T37, Reihe 10 |
| Handelsblock | `1` | 1 | 1 | 1 | T37, Reihe 14 |
| **Prüfgegenstände** | `3·L_R + (L_R − n) + 1` | **16** | **16** | **36** | T37 |
| Ströme im Handelsblock | `(L_R+1)·L_R·(S−1)` | 40 | 40 | 180 | Reihe 14, `handelsblock_stroeme` |
| freie Sollreihen | `L_R(S+3) − n` | 23 | 23 | 53 | `zaehlregel_t37` |
| abgeleitete Sollreihen | `L_R` | 4 | 4 | 9 | Reihe 11 |
| **Sollreihen** | `L_R(S+4) − n` | **27** | **27** | **62** | T55, `sollreihen_gesamt` |
| **Sollmaske `weltlauf`** | `L_R(4S+I+11) + (4S+10) + (L_R+1)L_R(S−1) + (S−1) + 3` | **175** | **175** | **450** | T38, T55 |

**Nachrechnung im Fliesstext, jede Zahl in diesem Lauf einmal von Hand eingesetzt.**
Prüfgegenstände heute `3·4 + (4−1) + 1 = 12 + 3 + 1 = 16`, bei neun Rückvergleichsländern
`3·9 + 8 + 1 = 27 + 8 + 1 = 36`. Ströme `5·4·2 = 40` und `10·9·2 = 180`. Freie Sollreihen
`4·6 − 1 = 23` und `9·6 − 1 = 53`, abgeleitete 4 und 9, zusammen `4·7 − 1 = 27` und
`9·7 − 1 = 62`. Sollmaske `4·27 + 22 + 40 + 2 + 3 = 175` und `9·27 + 22 + 180 + 2 + 3 = 450`.

**Ein zusätzliches Spielland lässt jede Zeile dieser Tabelle unverändert**, weil in keiner
Formel `L_S` vorkommt — das ist die Spalte `L_R = 4, L_S = 5` gegen die Spalte `heute`, Zeile
für Zeile dieselbe Zahl. Sie ändert sich erst, wenn `L_R` sich ändert; deshalb steht die
Spalte `L_R = 9` daneben, in der jede Zeile wandert, die wandern soll.
Der Auftragstext sagt an einer Stelle „Ein Spielland ändert die Zahl, nicht
die Struktur"; die Abnahmebedingung desselben Pakets verlangt das Gegenteil und ist die
schärfere Aussage. Die Formel entscheidet den Punkt: Die Zahl hängt an `L_R`, ein Spielland
erhöht `L`.

**Die Kurzform `4·L_R` ist richtig und darf trotzdem nicht die bindende sein.** Bei `n = 1`
heben sich die `−1` des Numéraires und die `+1` des Handelsblocks auf, und `16 = 4·4`,
`36 = 4·9`. Die beiden Terme haben aber nichts miteinander zu tun: Würde je handelbarem Sektor
ein Handelsblock geführt statt einem insgesamt, oder wäre das Numéraireland ein Spielland,
fiele die Aufhebung weg. Zweiter Fall, durchgerechnet: `L_R = 3` ohne die USA ergäbe
`3·3 + 3 + 1 = 13`, nicht 12. Das ist dieselbe Falle wie „40 gegen 40" und „27 gegen 27" in
T55, nur eine Ebene höher.

**In T55 wechseln genau drei Zeilen von `L` auf `L_R`, und keine weitere.** „Sollreihen" wird
`L_R(S+4) − n`. „Sollmaske `weltlauf`" wird die Formel aus der Tabelle oben. „Ausserhalb der
Sollmaske" ist keine Formel in einer Variablen mehr, sondern die Differenz *Zustand gesamt
(in `L`)* minus *Sollmaske (in `L_R`)*. Alle übrigen Zeilen zählen **Geometrie** und bleiben
bei `L`: Ein Spielland belegt seinen vollen Länderblock, seine Handelszeilen, seine
Steckplätze, Beteiligungen und Nachahmerzähler — es ist im Zustand ein Land wie jedes andere.
Auch „Sollmaske `weltlauf`, je Land" bleibt unberührt, weil es eine Größe je Land ist und
keine Klasse kennt. Bei `L_S = 0` gehen alle drei Zeilen in ihre heutige Fassung über; das ist
die Verträglichkeitsprobe.

**Die Klassentrennung spart Prüfaufwand und Daten, keine Adressen.** Bei `L = 9` mit fünf
Spielländern bleibt der Zustand bei den 740 aus T55, die Maske bei 175 — also liegen 565
Adressen ausserhalb statt der 290 bei neun Rückvergleichsländern. Die 275 Adressen Unterschied
zerfallen in `5 × 27 = 135` Maskenadressen der fünf Spielländer und `180 − 40 = 140`
Handelsströme, zusammen 275; zwei Wege, dieselbe Zahl. Was ein Land im Zustand kostet, steht
in `spiel.md`: 58 Felder je Politikland zuzüglich seiner Handelszeilen, unabhängig von der
Klasse.

**Zwei Gegenrechnungen, die diese Formeln nicht kennen.** `spiel.md` zählt für den Fall aller
195 Länder „`4 · L` — vier Prüfgegenstände je Rückvergleichsland" und kommt auf 780; einsetzen
von 195 in die Formel oben ergibt `3·195 + 194 + 1 = 780`. Und das Arbeitspaket
`0118-fuenf-weitere-laender-auswaehlen` stellt vom 2026-09-05 unabhängig beide Klassenwahlen
nebeneinander: neun Rückvergleichsländer ergäben 62 Sollreihen und 36 Prüfgegenstände, vier
plus fünf Spielländer 27 und 16. Alle vier Zahlen stimmen mit den Formeln überein.

**Was die Zählung nicht enthält.** `S` und `I` kommen in der Prüfgegenstandsformel nicht vor.
Ein vierter Sektor erzeugt keinen neuen Prüfgegenstand — er macht den Prüfgegenstand
*Sektorstruktur* schwerer, weil nach T37 alle Anteilsreihen des Landes bestehen müssen. Ein
fünftes Instrument erzeugt gar keinen. Das ist der Unterschied zu T55, wo `S` und `I` in fast
jeder Zeile stehen, und er ist der Grund, warum diese Tabelle eine eigene ist und keine
weitere Zeile in T55.

**Rechenzeit.** Die Klassentrennung verbilligt den Prüfstand nicht. Maß 4 ist **ein** Lauf
über `R` Weltschritte je Jahrgang, jetzt über `L_R + 1` statt `L + 1` Gebiete; das Budget des
Prüfstands tragen die Selbstspielmaße 1 bis 3, und die laufen im `spielmodus` über alle `L`.
Was billiger wird, ist die Datenbeschaffung und die Zahl der Reihen, die je Jahrgang
lizenzgeprüft sein müssen — nicht die Nacht.

### T60 — Die Rangfolge für einen fehlenden Politikpfad

Geraten wird zuletzt. Die Stufen sind in dieser Reihenfolge zu versuchen, und die erreichte
Stufe entscheidet die Klasse des Landes:

| Stufe | Was versucht wird | Klasse | Herleitung im Klartext |
|---:|---|---|---|
| **1** | ein anderer Code **derselben schon geklärten Quelle für dieselbe Größe** | Rückvergleichsland | nein; `codes` und `code_herkunft` genügen |
| **2** | eine **abgeleitete** Reihe aus einer bereits lizenzgeklärten Quelle | Rückvergleichsland | **ja**, nachrechenbar |
| **3** | **kein eigener Pfad**, weil das Land keinen geldpolitischen Hebel hat | Rückvergleichsland | **ja**: welche Union, ab welchem Jahr |
| **4** | ein **geschätzter** Pfad | **Spielland** | **ja**, mit jedem freien Parameter benannt |

**Stufe 1 verlangt dieselbe Größe, und das ist keine Förmlichkeit.** Der heutige Code
`DISR_RT_PT_A_PT` ist nach `reihen.toml` eine Wahl aus Paket 0006
(`code_herkunft = "gewaehlt-0006, in specs/ nicht genannt"`), keine Notwendigkeit — ein
anderer Code desselben Datenflusses ist deshalb der erste Griff. Ein Code, der **etwas anderes
misst**, ist aber nicht Stufe 1, sondern bestenfalls Eingang einer Ableitung nach Stufe 2.
Ohne diesen Zusatz liesse sich jede Ersatzgröße zur Stufe 1 erklären, und die Rangfolge wäre
wirkungslos. Der Fall liegt vor: `daten/nachmessung-zinsreihen-2026-09-05.md` nennt für
Deutschland `S13BOND_RT_PT_A_PT` (Rendite von Staatsanleihen, 1957–2017) und stellt die Frage
ausdrücklich an diesen Abschnitt. **Die Antwort ist nein.** Eine Staatsanleiherendite ist ein
Marktpreis; Reihe 9 speist in Schritt 3 einen Politikpfad, und ein Instrument, das der Markt
setzt, ist keines. Als **Eingang einer Ableitung** nach Stufe 2 bleibt die Reihe brauchbar —
dann aber mit Herleitung, mit der Lücke 2018–2021 im Fenster und unter der Schranke des
nächsten Absatzes.

**Die Grenze zwischen Stufe 2 und Stufe 4, damit Stufe 2 keine Hintertür wird.** Eine
**Ableitung** enthält keinen Parameter, der am Ergebnis des Modells angepasst wird; eine
**Schätzung** enthält einen. Wer einen Aufschlag wählt, weil das BIP damit besser trifft, hat
nicht abgeleitet, sondern das Modell an sich selbst geeicht — und der Rückvergleich misst dann
diese Wahl. Die Regel ist maschinell prüfbar, weil die Kennzeichnung nach T61 die Zahl der
freien Parameter mitführt: `> 0` schliesst Stufe 2 aus.

**Dieses Dokument zieht dieselbe Grenze schon einmal, und zwar an genau dieser Größe.** T27
hält fest: `leitzins_start[l]` steht **nicht** in `parameter.toml`, sondern im Jahrgang —
*„keine Kalibriergröße, sondern eine Messung"*. Der naheliegende Weg von einer
Anleiherendite zu einem Leitzins liefe über `aufschlag`, und `aufschlag` ist eine
Kalibriergröße: Klasse 3, aus `parameter.toml`, in T27 als *„Abstand Leitzins ↔
Anleiherendite"* geführt und vom Nachtlauf über tausend Parametersätze variiert. Ein so
gebildeter Pfad ist deshalb nicht nur „geschätzt" — er ist **im Kreis geschätzt**: T23 Punkt 5
rechnet `aufschlag_min = 1 − min(leitzins_pfad)`, der Pfad käme aber aus `aufschlag`. **Eine
Ableitung, die über einen Parametersatzschlüssel führt, ist keine.**

**Stufe 2 ist eine ungeprüfte Vermutung und keine Quelle.** Als Kandidaten stehen im Raum die
WDI-Zinsreihen `FR.INR.RINR`, `FR.INR.LEND` und `FR.INR.DPST`. Sie sind **keine Leitzinsen**,
und **nichts an ihnen ist geprüft**: nicht die Deckung, nicht die Länderliste, nicht die
Drittanbieterlage. Ich habe sie in diesem Lauf ausdrücklich **nicht** nachgesehen — Zinsreihen
zu suchen gehört nach dem Auftrag nicht zu diesem Paket. Ein Punkt lässt sich ohne Suche
schärfen, und er wiegt schwerer als die Vermutung selbst: **Die Annahme „aus dem WDI, also
CC BY 4.0" sagt über eine einzelne Reihe nichts.** In `reihen.toml` sind acht Reihen aus dem
WDI eingebettet (1, 2, 5, 6, 7, 8, 10, 13), alle acht mit
`lizenz_beleg_typ = "feld_source"` — entschieden wird am Feld `Source` des Codes, nicht am
Katalog. Das Ergebnis für diese acht: fünfmal `unklar` (1, 2, 5, 6, 7), zweimal `frei`
(8, 10) und **einmal `gesperrt`** — Reihe 13, das Zollniveau, und damit ausgerechnet einer
der drei Politikpfade. Wer Stufe 2 über das WDI geht, hat die Lizenzfrage nicht abgekürzt,
sondern nur verschoben.

**Stufe 3 ist eine Antwort und keine Lücke — aber sie liefert eine Zahl.** Für ein Land ohne
eigenen geldpolitischen Hebel ist „kein eigener Pfad" richtig; Deutschland trägt das nach
`spiel.md` ausdrücklich als Entwurfsmerkmal, und `reihen.toml` führt es bereits mit
`exogen_ab = 1999` und dem Bruch „Euroraum -- Deutschland folgt ab 1999 exogen der gemeinsamen
Geldpolitik". **Was fehlt, ist die Urheberschaft, nicht der Wert:** Schritt 3 braucht weiter
eine Zahl, und das ist der Satz der Union. Stufe 3 heisst deshalb genau: Stufe 1 und 2 werden
**auf die Union** angewandt statt auf das Land. Trägt die Union einen gemessenen Satz, bleibt
das Land Rückvergleichsland; muss der Satz der Union geschätzt werden, fällt das Land auf
Stufe 4. Ein vollständig fremdwährungsgebundenes Land, dessen Instrument über das ganze
Fenster konstant ist, ist ebenfalls Stufe 3 — eine Konstante ist eine gemessene Tatsache.

**Stufe 4 macht das Land zum Spielland**, mit hinterlegter Herleitung nach T61 und mit der
Stilllegung nach T58.

**Der erste Anwendungsfall sind nicht künftige Länder, sondern China und Deutschland.** Für
Deutschland ist der erste Griff Stufe 1 auf die Union — ob derselbe Datenfluss ein Gebiet für
den Euroraum führt, ist ungeprüft und die billigste offene Frage dieses Themas. Für China
liefert `CHN.*.A` im Fenster nach der Nachmessung vom 2026-09-05 **null** jährliche Reihen;
Stufe 1 scheitert dort innerhalb `MFS_IR`, Stufe 3 trifft nicht zu, und es bleibt Stufe 2.

**Deshalb eine Sperre, und sie ist der Grund, warum diese Regel überhaupt eine braucht.**
**Kein Datenpaket macht eines der vier heutigen Länder zum Spielland.** Scheitern die Stufen 1
bis 3 für China oder Deutschland, ist das kein Befund über eine Reihe, sondern eine
Entscheidung über die Grundlage des Rückvergleichs: `L_R` fiele von 4 auf 3, die
Prüfgegenstände von 16 auf `3·3 + (3−1) + 1 = 12`, die Sollreihen von 27 auf `3·7 − 1 = 20`,
und Maß 4 würde an einer anderen Welt gemessen als bisher. **Beide Zahlen rechnen mit
`n = 1`**, weil die USA in diesem Fall Rückvergleichsland und Numéraire bleiben; der
`n = 0`-Fall, den die Kurzform in T59 durchrechnet, ist ein anderer und gilt hier nicht. Das
gehört dem Betreiber, nicht dem Jahrgangsbau. Der Jahrgangsbau **bricht ab** (T61), statt die
Klasse still umzuschreiben.

**Und die Umkehrung gilt auch:** Eine Sollreihe trägt ausschliesslich Stufe 1. Wer für eine
Sollreihe eine Ableitung oder eine Schätzung braucht, hat keine Sollreihe mehr, sondern eine
Schätzung, die wie eine Messung aussieht — der eine Fall, der schlimmer ist als eine fehlende
Reihe. Die Kennzeichnungspflicht in T61 ist für die Politikpfade eine Buchführung; für die
Sollreihen ist sie ein Verbot.

### T61 — Die Kennzeichnung in `reihen.toml`

**Das Feld, das eine geschätzte Reihe trägt, heisst `stufe` und steht in einem neuen Block
`[[reihe.herkunft]]`.** Über die Klasse eines Landes entscheiden allein die drei Reihen mit
`politikpfad` in `rolle` — Reihe 9 (Leitzins), Reihe 12 (Haushaltssaldo) und Reihe 13
(Zollniveau); das vierte Instrument, die Finanzmarktregulierung, hat keine Reihe, sein Wert
kommt nach T45 aus `parameter.toml`. Der Block ist trotzdem für **jede** Reihe Pflicht, und
Regel 1 sagt warum.

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

**Fünf Regeln, alle mechanisch:**

1. **Keine Reihe ohne Herkunft.** Die drei Politikpfadreihen tragen je Land genau einen
   Block — sie haben alle `dimension = "4"`, das sind bei `L = 4` also `3 × 4 = 12`. Jede der
   übrigen sechzehn Reihen trägt genau einen Block mit `land = "alle"`, wie es
   `[[reihe.deckung]]` schon kennt; zusammen **28**. Fehlt einer, **bricht der Jahrgangsbau
   ab** — dieselbe Bauart wie die Herkunftstabelle aus T45, und aus demselben Grund: Ein
   stillschweigendes „gemessen" für ein fehlendes Feld wäre genau die Lüge, gegen die diese
   Regel geschrieben ist. Ein freiwilliges Feld hätte sie nicht verhindert, sondern erzeugt.
2. **Herleitungspflicht.** `stufe ≥ 2` ohne nichtleere `herleitung` bricht ab.
3. **Parametersperre.** `stufe = 2` mit `freie_parameter > 0` bricht ab (T60).
4. **Sollreihensperre.** Eine Reihe mit `soll` in `rolle` und `stufe ≥ 2` bricht ab. Erst
   Regel 1 gibt dieser Sperre Zähne: Ohne den Pflichtblock je Reihe wäre sie nur wirksam
   gegen den, der seine Schätzung freiwillig einträgt.
5. **Doppelte Buchführung über die Klasse.** Das Manifest des Jahrgangs führt
   `rueckvergleichslaender = [...]` ausgeschrieben. Aus `reihen.toml` folgt dieselbe Menge
   abgeleitet: Ein Land ist genau dann Spielland, wenn **irgendeine** seiner drei
   Politikpfadreihen `stufe = 4` trägt. **Stimmen beide nicht überein, bricht der Jahrgangsbau
   ab.** Die Ableitung allein wäre die bequemere Bauart und die falsche: Sie liesse eine
   Zeile in einer Datenreihe die Grundlage des Rückvergleichs verschieben, ohne dass es
   irgendwo aufschlägt. Die Sperre aus T60 ist genau diese Prüfung.

Die Klasse steht damit an einer Stelle geschrieben und an einer zweiten gerechnet, und der
Bau hält an, wo sie auseinandergehen — dieselbe Bauart wie der zweite Schreibzugriff in T39
und das Fondsvermögen in T47.

### Was dieser Abschnitt nicht angefasst hat, und was offen bleibt

**Nicht angefasst.** T37 behält seine sechzehn Prüfgegenstände, seine Toleranz 2 und seine
Klassentabelle Wort für Wort; die Formel steht hier und nicht dort, damit
`0068-technikmd-reihe-9-ohne-sollrolle` seinen Bezugspunkt unverändert vorfindet. Dass die
Zeile `gesetzt` in der Klassentabelle von T37 seit Paket 0054 leer ist, ist bekannt und
gehört ebenfalls 0068. Abschnitt 7, T55 und die Zahlen 310 und 740 bleiben stehen: Der
Zustandsumfang ist durch die drei Schichten in `spiel.md` gerade in Bewegung und gehört
0118/0119, und dieser Abschnitt braucht ihn nicht — seine Formeln zählen Prüfgegenstände und
Sollreihen, nicht Adressen. `reihen.toml` ist **nicht** geändert; T61 beschreibt einen Block,
den ein Datenpaket einträgt.

**Drei Meldungen an den Projektmanager, weil sie fremden Gewerken gehören.** Erstens:
`spiel.md` führt in der Tabelle der drei Schichten für Schicht 1 in der Spalte *im
Rückvergleich* „ja, als Rückvergleichsland" ohne Ausnahme. Mit den beiden Klassen wird daraus
„ja, **wenn** Rückvergleichsland". Das ist eine Zeile in `spiel.md` und nicht meine.
Zweitens: T58 Festlegung 3 (Restweltrest je Modus) und Festlegung 4 (Giftprobe) sind Entwurf
und brauchen je ein Paket — Jahrgangsbau und Prüfstand —, sobald das erste Spielland
tatsächlich eingetragen wird. Vorher wäre es Code auf Vorrat.

**Drittens, und es ist ein Nachzug, den ich sehenden Auges liegen lasse:** Der Vorspann vor
Abschnitt 1 sagt „Die Vorgaben sind mit **T1** bis **T53** durchnummeriert". Richtig wäre seit
Paket 0116 T57 und nach diesem Abschnitt **T61**; die nächste freie Nummer ist T62. Derselbe
Vorspann und Abschnitt 17 führen ausserdem **T60** als Beispiel für eine *noch freie* Nummer —
sie ist es ab hier nicht mehr. **Ich fasse beide Stellen nicht an, und zwar nicht aus
Vorsicht:** Die Arbeitspakete `0082` und `0084` binden ihre Abnahme ausdrücklich darauf, dass
„der Vorspann unberührt bleibt — er ist mit 0026 abgenommen". Wer ihn nachzieht, nimmt zwei
laufenden Paketen ihr Abnahmekriterium weg. Das ist ein eigenes Paket, und es sollte nach 0082
und 0084 laufen.

**Eine Kollision der Abnahme mit sich selbst, offen benannt.** Bedingung 4 verlangt, `git diff`
zeige Änderungen ausschliesslich in `technik.md`. Der Lauf ändert zwei weitere Dateien, beide
durch Regeln erzwungen, die über diesem Paket stehen: die Statuszeile im Arbeitspaket (ohne
sie plant der Runner dasselbe Paket erneut ein) und das Logbuch der Rolle (CLAUDE.md). Der
Zweck der Bedingung — keine Zahl ausserhalb `technik.md` bewegt sich, kein zweites Gewerk wird
angefasst — ist erfüllt; die schärfere Messung dafür ist, dass dieser Abschnitt ein reiner
Anhang ist und **keine** Zeile des Bestands entfernt oder ändert.

**Welche Festlegung jetzt fallen musste und welche vertagt ist.** Jetzt fallen musste die
Wahl zwischen A, B und C: Sie entscheidet, ob die Ausnahme im Lauf oder in der Auswertung
sitzt, und das lässt sich nicht nachrüsten, ohne jeden gespeicherten Rückvergleich zu
entwerten. Ebenso die Kennzeichnung, weil eine ungekennzeichnete Schätzung rückwirkend nicht
mehr von einer Messung zu unterscheiden ist. Vertagt sind die Wahl der Länder (0118), die
Wahl der Codes und das Schätzverfahren selbst — jedes davon ist eine Datenfrage, und keine
davon ändert etwas an diesen drei Vorgaben.

## 21. Was ein fünftes Land an Daten mitbringt — Paket `0141`

**Was hier entschieden wird und was nicht.** Dieser Abschnitt wählt **kein** Land aus (das ist
`0118`), ändert die Länderzahl **nicht**, lädt keine Daten und bewertet keine Lizenz. Er
beschreibt den Aufwand, er treibt ihn nicht. Entschieden wird zweierlei: die abzählbare Liste
dessen, was ein weiteres Land an Reihen, Fenstern und Lizenzfragen mitbringt (T62), und was
gilt, wenn der eingebettete Leitzinscode ein Land nicht führt (T63). Der Abschnitt ist ein
reiner Anhang; er entfernt und ändert keine Zeile des Bestands.

### T62 — Die Liste je Datenreihe

**Drei Fensterklassen, und sie folgen aus der Rolle der Reihe, nicht aus ihrer Nummer.** `A`
ist das Startjahr des Jahrgangs, `R` die Rundenzahl; ein Jahrgang trägt `R+1` Stützstellen für
die Jahre `A … A+R`.

| Klasse | Anforderung | Vorgabe |
|---|---|---|
| **voll, ohne Füllung** | `R+1` Stützstellen, `gefuellt = 0` | T24, erste Schwelle |
| **voll, Füllung gekennzeichnet** | `R+1` Stützstellen; Lücken werden gefüllt und ausgewiesen, gehen aber in kein Fehlermaß ein | T24, T25 |
| **Startjahr** | genau eine Stützstelle, das Jahr `A` | T25 |

**Die Liste ist in `R` geschrieben, weil das Fenster in diesem Repo zwei Werte hat.** Dieses
Dokument führt durchgehend den Prüfjahrgang 1997–2021, also `A = 1997`, `R = 24`, 25
Stützstellen. `daten/reihen.toml` misst für Reihe 11 den ersten US-Wert im Jahr 2001 und
urteilt *„verkuerzt — 1997 bis 2000 fehlen, kostet vier Stuetzstellen und erzwingt das
Startjahr 2001"*, also `A = 2001`, `R = 20`, 21 Stützstellen. Die Wahl zwischen den beiden
Auswegen — Reihe streichen oder Fenster kürzen — steht nach T24 dem Spielentwerfer zu und
kostet nach T40 eine Zahl im Manifest. **Dieser Abschnitt löst den Punkt nicht auf**; wo unten
eine Zahl steht, steht sie für beide Lesarten.

| Nr | Größe | neu bei `L: 4 → 5` | Quelle, eingebetteter Code | Fenster | Lizenzstand | bewegt ein weiteres Land das Urteil? |
|---:|---|---:|---|---|---|---|
| 1 | BIP, konstante Preise | 1 | WDI `NY.GDP.MKTP.KD`, Rückfall PWT | voll, ohne Füllung¹ | unklar | **ja** — Ämter und Notenbanken |
| 2 | Wertschöpfungsanteil je Sektor | 3 | WDI `NV.AGR.TOTL.ZS`, `NV.IND.TOTL.ZS`, `NV.SRV.TOTL.ZS` | voll, ohne Füllung¹ | unklar | **ja** — Ämter und Notenbanken, **ohne Ausweichquelle** |
| 3 | Kapitalstock | 1 | PWT, Code nirgends festgeschrieben | Startjahr | frei | nein |
| 4 | Produktivität (TFP) | 1 | PWT, Code nirgends festgeschrieben | Startjahr | frei | nein |
| 5 | Bevölkerung | 1 | WDI `SP.POP.TOTL`, Rückfall PWT | voll, Füllung gekennzeichnet | unklar | **ja** — Ämter (das Feld nennt keine Notenbank) |
| 6 | Erwerbstätige | 1 | WDI `SL.TLF.TOTL.IN`, Rückfall PWT | voll, Füllung gekennzeichnet | unklar | nein — ILO |
| 7 | Beschäftigung je Sektor | 3 | WDI (ILO) `SL.AGR.EMPL.ZS`, `SL.IND.EMPL.ZS`, `SL.SRV.EMPL.ZS` | Startjahr | unklar | nein — ILO |
| 8 | Verbraucherpreise | 1 | WDI `FP.CPI.TOTL.ZG`, Rückfall IWF IFS | voll, ohne Füllung¹ | frei² | nein — IWF |
| 9 | Leitzins | 1 | IWF `IMF.STA/MFS_IR 9.0.0`, Code `DISR_RT_PT_A_PT` | voll, Füllung gekennzeichnet | unklar | nein — IWF; **Codewahl je Land, siehe T63** |
| 10 | Wechselkurs gegen USD | 1³ | WDI `PA.NUS.FCRF`, Rückfall IWF IFS | voll, ohne Füllung¹ | frei² | nein — IWF |
| 11 | Staatsschuldenquote | 1 | IWF `IMF.RES/WEO 9.0.0`, `GGXWDG_NGDP` | voll, ohne Füllung¹ | unklar | nein — IWF |
| 12 | Haushaltssaldo | 1 | IWF `IMF.RES/WEO 9.0.0`, `GGXCNL_NGDP` | voll, Füllung gekennzeichnet | unklar | nein — IWF |
| 13 | Zollniveau, aggregiert | 1 | WDI (aus WITS) `TM.TAX.MRCH.WM.AR.ZS` | voll, Füllung gekennzeichnet | **gesperrt**⁴ | nein — WITS, UNCTAD, WTO |
| 14 | Bilaterale Ströme nach HS92 | **20 Ströme** | CEPII BACI, Fassung 202601 | voll, ohne Füllung¹ | frei | nein — Etalab |
| 15 | Preisniveau im Ländervergleich | 1 | PWT, Code nirgends festgeschrieben | Startjahr | frei | nein |
| 16 | `durchgriff` | 2, abgeleitet | aus den Reihen 14, 1 und 2 nach T23 Punkt 5 | keine eigene Beschaffung | geerbt | erbt von 1 und 2 |
| 17 | Sektorpreise | — | keine | endogen | — | — |
| 18 | Zustimmung | 1 Schlüsselwert | `parameter.toml` | keine Beschaffung | — | — |
| 19 | Marktkorbwert und Marktrendite | — | nicht je Land geführt | — | — | — |

¹ **Nur wenn das Land Rückvergleichsland wird.** Als Spielland genügt für diese Reihen das
Startjahr: T58 legt seine Adressen im `weltlauf` still, sie behalten ihren Startwert und
werden nicht geschrieben. Die Sollrolle entsteht mit der Klasse, nicht mit dem Land.

² `frei` nach `daten/lizenzbefund-wdi.md`, weil das Feld `Source` als Drittanbieter den IWF
nennt und dessen Bedingungen den gewerblichen Verkauf erlauben. `reihen.toml` stellt dieser
Zahl in `zaehlung.lizenz.gegenrechnung` eine zweite gegenüber: Der IWF-Lizenztext ist nach
fünf Anläufen aus drei Rollen ungelesen (HTTP 403), und nimmt man „ein Suchauszug genügt
nicht" auch dort ernst, ist auch dieses `frei` ein `unklar`. Beide Lesarten stehen
nebeneinander; **ein weiteres Land bewegt keine von beiden.**

³ Nur wenn das fünfte Land nicht das Numéraireland ist. Reihe 10 trägt die Dimension 3 und
nicht 4, weil der Numéraire keinen eigenen Kurs hat — das ist der Term `n` aus T59.

⁴ Für **alle** Länder gleich gesperrt, nach `lizenzbefund-wdi.md` der einzige Fall, in dem der
genannte Drittanbieter seine Zustimmung ausdrücklich vorbehält. Ein fünftes Land ändert daran
nichts und erbt den Fall: Von seinen drei Politikpfadreihen hat eine von vornherein keinen
Datenanker. T26 erster Fall gilt unverändert — kein Zollpfad, konstanter Zoll, zwei statt drei
verankerte Instrumente.

**Die Zählung, und sie ist der eigentliche Gegenstand dieses Pakets.** Ein fünftes Land bringt
**18 Landesreihen und 20 Handelsströme** mit, zusammen **38**. Die Landesreihen sind
`12 + 2S`, bei `S = 3` also 18; die neuen Ströme sind `2(L+1)(S−1)`, bei `L = 4` und `S = 3`
also 20 — die Differenz `(L+2)(L+1)(S−1) − (L+1)L(S−1)` aus der Handelsformel in T55.

| Fensterklasse | Reihen und Ströme | welche |
|---|---:|---|
| voll, ohne Füllung | **27** | die sieben neuen Sollreihen (1, 2×3, 8, 10, 11) und die 20 Ströme |
| voll, Füllung gekennzeichnet | **5** | die exogenen Pfade 5 und 6, die Politikpfade 9, 12, 13 |
| Startjahr | **6** | 3, 4, 7×3, 15 |
| Probe | **38** | `27 + 5 + 6` |

Die sieben Sollreihen sind `S + 4` — genau der Zuwachs, den T59 mit `L_R(S+4) − n` von der
anderen Seite ausrechnet. Die Prüfgegenstände wachsen um vier (`3 + 1` für ein Land, das nicht
der Numéraire ist), wie in T58 unter dem Klassenwechsel schon steht.

**Was daraus an Werten folgt, je Klasse.** Ein **Rückvergleichsland** kostet
`32(R+1) + 6` Werte: 32 Reihen über das volle Fenster, sechs Startwerte. Ein **Spielland**
kostet `5(R+1) + 33`: die fünf Pfade über das volle Fenster, 33 Startwerte (7 Reihen +
20 Ströme + 6). Eingesetzt:

| | `R = 24` (Fenster ab 1997) | `R = 20` (Fenster ab 2001) |
|---|---:|---:|
| Rückvergleichsland | **806** | **678** |
| Spielland | **158** | **138** |
| dieselben ohne die gesperrte Reihe 13 | 781 / 133 | 657 / 117 |

**Gegenrechnung, nach Quelle statt nach Fensterklasse, für `R = 24` und Rückvergleichsland.**
WDI zwölf Reihen: sechs Sollreihen (1, 2×3, 8, 10) zu je 25, drei volle Pfade (5, 6, 13) zu je
25, drei Startwerte (7) — `150 + 75 + 3 = 228`. IWF drei Reihen (9, 11, 12) zu je 25 — 75.
PWT drei Startwerte (3, 4, 15) — 3. BACI 20 Ströme zu je 25 — 500. Summe
`228 + 75 + 3 + 500 = 806`, dieselbe Zahl über eine andere Aufteilung, und `12 + 3 + 3 = 18`
Landesreihen.

**Eine Falle, weil sie dieselbe Familie ist wie „40 gegen 40" und „27 gegen 27" in T55: 38
gegen 38.** Die 38 Reihen und Ströme dieser Liste und die 38 von `L` unberührten
Zustandsadressen aus T57 sind dieselbe Zahl und haben nichts miteinander zu tun. T57 rechnet
`5S + 23` und hängt nicht von `L` ab; diese Liste rechnet `12 + 2S + 2(L+1)(S−1)` und hängt
davon ab. Bei `L = 5` steht 42 gegen unverändert 38. Wer beide für dieselbe Größe hält, hält
die Datenkosten eines weiteren Landes für konstant, und sie sind es nicht.

**Was ein fünftes Land am Lizenzstand bewegt — und was nicht.** Von den 19 Reihen hängen
genau **drei** im Feld `Source` an den nationalen Ämtern und Notenbanken der Meldeländer:
Reihe 1 und Reihe 2 (*„Country official statistics, National Statistical Organizations and/or
Central Banks"* beziehungsweise *„National Statistical Offices (NSOs); National Accounts data
files, Central Banks"*) und Reihe 5, die allein die Ämter nennt. Alle übrigen nennen benannte
Organisationen — IWF, ILO, OECD, WITS/UNCTAD/WTO, CEPII, PWT —, deren Bedingungen von der
Länderliste unabhängig sind. Ein fünftes Land bringt deshalb **genau zwei** neue zu prüfende
Stellen mit, sein statistisches Amt und seine Notenbank. Sie treten zu den acht der heutigen
Modellländer, von denen nach `lizenzbefund-reihen.md` genau eine geprüft ist (Destatis);
danach sind es zehn Stellen und eine Prüfung.

Drei Folgerungen, und die dritte ist die, gegen die ich mich selbst korrigiert habe:

1. **Ein fünftes Land kann kein Lizenzurteil verbessern.** Die drei betroffenen Reihen stehen
   bereits auf `unklar`.
2. **Es kann eines verschlechtern.** Verweigert das Amt oder die Notenbank des Landes die
   gewerbliche Weitergabe, sind seine Werte in den Reihen 1, 2 und 5 gesperrt. Reihe 1 und
   Reihe 5 haben mit der PWT eine geprüft freie Ausweichquelle. **Reihe 2 hat keine** —
   `quellenwahl_grund` sagt warum: Die PWT liefert keine sektorale Wertschöpfung, feinere
   Gliederungen liegen nur bei der OECD (ungeklärt) und bei Eurostat (für die Nicht-EU-Länder
   des Modells gesperrt). Reihe 2 trägt `S` der sieben neuen Sollreihen. Sie ist damit die
   einzige Stelle der ganzen Liste, an der die Herkunft eines Landes den Rückvergleich hart
   ausschliesst.
3. **Trotzdem ist das kein Auswahlkriterium für `0118`.** Sieben der acht heutigen Stellen sind
   ungeprüft. Ein Kriterium, das von einem fünften Land eine Prüfung verlangt, die für die
   heutigen Modellländer niemand gemacht hat, misst nicht die Sauberkeit des Landes, sondern
   wer geprüft wurde. Die zwei neuen Stellen gehören auf dieselbe Liste wie die sieben offenen
   (`lizenzbefund-reihen.md`, Klärung 4) und werden mit ihnen zusammen erledigt oder gar nicht.
   **Kosten, kein Tor.**

### T63 — Der Leitzins, wenn der eingebettete Code das Land nicht führt

**Gewählt ist ein Ersatzverfahren: keine Ersatzquelle im Voraus und kein Ausschlusskriterium.**
Die Regel für jedes Land, dessen Leitzins gebraucht wird:

1. **Zuerst `LAND.*.A` abrufen, nicht den gewählten Code annehmen.** Ein Abruf auf
   `IMF.STA/MFS_IR 9.0.0`. Führt das Land einen Code, der einen **Politiksatz** misst, ist das
   Stufe 1 nach T60 und der Fall ist zu Ende.
2. Sonst der Reihe nach Stufe 2 (Ableitung ohne freien Parameter), Stufe 3 (kein eigener
   Hebel — Stufe 1 und 2 auf die Union statt auf das Land), Stufe 4.
3. Bleibt es bei Stufe 4, ist das Land nach T58 ein **Spielland**. Es ist damit nicht
   ausgeschlossen, sondern eingeordnet. Für die heutigen Modellländer gilt zusätzlich die
   Sperre aus T60: Der Jahrgangsbau bricht ab, statt ihre Klasse still umzuschreiben.

**Warum Schritt 1 keine Förmlichkeit ist.** `DISR_RT_PT_A_PT` steht in `reihen.toml` mit
`code_herkunft = "gewaehlt-0006, in specs/ nicht genannt"` — eine Wahl, keine Eigenschaft des
Datenflusses. Wie weit Code und Datenfluss auseinanderliegen, ist gemessen und nicht vermutet:
`daten/nachmessung-zinsreihen-2026-09-05.md` findet im Fenster 1997–2021 für Deutschland
**elf** jährliche Reihen und den gewählten Code **nicht**, für China **null** Reihen, für die
USA neun und für Brasilien sieben. Ein Befund „der Code trägt für dieses Land nicht" ist
deshalb zunächst eine Aussage über die Wahl aus Paket 0006 und noch keine über die Quelle.
Für ein fünftes Land kostet die Unterscheidung einen Abruf; sie zu überspringen kostet ein
Land, das man gar nicht hätte verwerfen müssen.

**Warum keine Ersatzquelle im Voraus festgelegt wird.** Eine zweite Zinsquelle einzuführen
hiesse, für **eine** Reihe eine weitere Quelle in die Lizenzprüfung, in `namensnennung` und ins
Manifest zu nehmen — und die Lizenzarbeit ist nach T62 der teuerste Posten der ganzen Liste.
Der Preis ist gemessen: Von den acht im WDI eingebetteten Reihen sind fünf `unklar` und eine
`gesperrt`. Die naheliegenden WDI-Kandidaten `FR.INR.RINR`, `FR.INR.LEND` und `FR.INR.DPST`
sind ausserdem nach T60 keine Leitzinsen, sondern bestenfalls Eingang einer Ableitung, und der
Weg über eine Staatsanleiherendite ist dort bereits versperrt: Er führte über `aufschlag`,
einen Schlüssel aus `parameter.toml`, und eine Ableitung über einen Parametersatzschlüssel ist
keine. **Solange `MFS_IR` für ein Land trägt, ist es der billigste Weg; trägt es nicht, ist
Stufe 4 billiger als eine neunte Quelle.**

**Warum kein Ausschlusskriterium — das ist das Argument, das die Wahl trägt.** Reihe 9 ist seit
Paket 0054 **keine Sollreihe** (`sollreihen = 0`, `t37_klasse` leer) und steht in keinem der
sechzehn Prüfgegenstände; die abschliessende Aufzählung in `reihen.toml` unter
`zaehlung.pruefgegenstaende` führt BIP, Sektorstruktur, Verbraucherpreise, Wechselkurs und den
Handelsblock — den Leitzins führt sie nicht. Ein Land wegen eines fehlenden Leitzinses
auszuschliessen, schützte also eine Größe, die der Rückvergleich gar nicht misst. Was ein
fehlender Leitzins wirklich kostet, ist ein verankertes Instrument im `spielmodus` — und genau
dafür ist die Klasse Spielland gebaut: Ihre Größen sind im `weltlauf` stillgelegt und wirken
über Handel und Weltpreise auf keinen Prüfgegenstand.

**Die Ausschlussschranke steht an anderer Stelle, und sie ist schärfer.** Ein fünftes Land als
**Rückvergleichsland** braucht seine `S + 4` = sieben Sollreihen auf Stufe 1 — nach der
Umkehrung in T60 trägt eine Sollreihe ausschliesslich Stufe 1. Der Leitzins ist keine davon.
Die eine Reihe, an der ein Land daran scheitern kann und die zugleich keine Ausweichquelle
hat, ist Reihe 2 (T62, Folgerung 2). **Wer für `0118` ein Ausschlusskriterium sucht, findet es
dort und nicht beim Leitzins.**

**Was die Wahl mechanisch nach sich zieht — nichts Neues, und das ist beabsichtigt.** T61
Regel 1 zählt die Herkunftsblöcke als `3L + 16`, bei `L = 4` also 28. Ein fünftes Land macht
daraus **31**: drei weitere Blöcke, je einer für die Politikpfadreihen 9, 12 und 13. Fehlt
einer, bricht der Jahrgangsbau nach Regel 1 ab. Trägt einer `stufe = 4`, ist das Land nach
Regel 5 ein Spielland und muss auch im Manifest so stehen, sonst hält der Bau an. T63 braucht
damit keine eigene Sperre; es sagt nur, in welcher Reihenfolge die Stufen zu versuchen sind
und dass das Ergebnis eine Klasse ist und kein Urteil über die Zulässigkeit des Landes.

### Was dieser Abschnitt nicht angefasst hat

**Nichts.** Kein Land gewählt, die Länderzahl unverändert, keine Zeile des Bestands entfernt
oder geändert, keine Tabelle nachgezogen, `reihen.toml` nicht berührt. Die Zustandsgröße aus
T55 und die Aussage über die heutigen Modellländer stehen unbewegt: `grep -c` liefert vor und
nach diesem Lauf 44 beziehungsweise 7 Zeilen. Das Fenster ist **nicht** entschieden — die
Liste ist in `R` geschrieben, und beide Lesarten tragen ihre Zahl.

**Drei Meldungen, weil sie fremden Gewerken gehören.** Erstens: Die zwei zusätzlichen Stellen
gehören in die Aufzählung unter Klärung 4 in `daten/lizenzbefund-reihen.md`. Das ist ein
Datenpaket und keine Architektenzeile. Zweitens: Der Auftragstext zu `0141` nennt das Fenster
„ab 2001", dieses Dokument führt durchgehend 1997–2021. Beides ist belegt, die Wahl gehört
nach T24 dem Spielentwerfer, und ich habe sie deshalb nicht getroffen. Drittens: Der
Vorspann-Nachzug aus Abschnitt 20 wächst um eine Zeile — richtig wäre jetzt **T63**, die
nächste freie Nummer ist T64. Ich fasse den Vorspann aus demselben Grund nicht an wie dort:
`0082` und `0084` binden ihre Abnahme darauf, dass er unberührt bleibt.

**Welche Festlegung jetzt fallen musste und welche vertagt ist.** Jetzt fallen musste die
Frage aus T63, ob ein fehlender Leitzins **ausschliesst** oder die **Klasse entscheidet**. Sie
muss vor `0118` fallen, weil sie den Suchraum der Länderauswahl um Größenordnungen ändert: Als
Ausschlusskriterium bliebe nur, wofür ein einzelner IWF-Code einen Politiksatz führt — er tut
es für zwei der heutigen Modellländer nicht; als Klassenfrage ist jedes Land wählbar, und der
Leitzins entscheidet allein, ob es 806 oder 158 Werte kostet. Vertagt sind die Wahl des
Landes, die Wahl seiner Codes, das Schätzverfahren der Stufe 4 und das Fenster. Keines davon
ändert etwas an T62 oder T63.
