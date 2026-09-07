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

**T22 — A save is vintage, mode, seed, action sequence and checksum, not the state.**
File: `{schema_version, jahrgang_id, modus, daten_pruefsumme,
parameter_pruefsumme, startwert, aktionen: [[runde, aktion…]], end_pruefsumme}`. On
loading, the game is recomputed and the checksum compared; if it deviates, the program
reports a determinism break instead of playing on. Three wins at once: the buyer notices a
determinism error first, the regression corpus **is** the save folder, and a file stays
under two kilobytes. Cost: R world steps on loading, at R = 24 thus 0.24 milliseconds.

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
2. **Target series** for the 31 series from `spiel.md` plus the trade block over 40
   flows, per series with the classification from T37;
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

- **Check vintage 1997–2021:** `spiel.md` demands each of the 31 target series and each
  of the 40 trade flows over **25 support points without filling**, that is
  `gefuellt = 0`. A series that does not meet this is **not filled and not silently
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
listed here. The 31 target series are rows 1, 2, 8, 9, 10 and 11 (4+12+4+4+3+4); the
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
structure with named fields, never via a loop over keys (T9). The checksum of the
parameter set stands in the state and in every save. With that, calibrating is a data
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
| 9 | `bip(l)` | 2 | `Σ über die 3 Sektoren wertschoepfung[l][s]` | here |
| 10 | `schuld(l)` | 2 | `mal_geteilt(bip(l), staatsschuld[l], 10.000)` | here |
| 11 | `handelsvolumen(l, s)` | 2 | see below; the one-argument form `handelsvolumen(l)` is its sum over s ∈ {1, 2} | here |
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

**Three quantities lie outside the core** and therefore do not stand in the table:
`B(z)`, `v(z)` and `e(z)` from T44. They are test-bench quantities, belong to the
component `pruefstand` and never leave the game.

**The rule that follows from this, and the mechanical proof for it.** A name in a formula
of this document or in `spiel.md` that is neither a state address from T15 nor a
parameter key from T27 nor a vintage constant from T23 nor one of the **twenty-two**
quantities above **is a finding and not a build decision** — that is the case finding 1
describes, and the reason it was expensive: if the build agent chooses, Maß 2 measures
its choice. It is proven like the floating-point renunciation from T4: the twenty-two
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
| 2 | invariant test | sum of all trade balances including rest of world = 0; government debt(t) = government debt(t−1) − balance; **fund assets = cash + valued positions + valued stakes − leverage** (T47, against `fondsvermoegen()` and against a sum written out separately in the test, so that the test does not repeat the function under test); the three sector shares per territory sum to 10,000; no share outside 0…10,000; **the seven value-range bounds from T5/T49** (see below); every game result in one of the three bands from T34 | test developer |
| 3 | determinism test | the same seed, mode and the same action sequence yield the same checksum — twice within the run, across save and load, and compared on every target platform | test developer |
| 4 | regression corpus | stored games per T22 recompute bit-identically; in addition a checksum over the chain, so that a changed *justification* shows too; at least one game on a 1980 vintage with a base change (T8) | test developer |
| 5 | break run | 10,000 games with the random bot: no crash, no overflow, no invariant violation, no chain overflow, no double write access and no mask violation (T18, T38, T39) | break tester |
| 6 | **boundedness** | **200 rounds without a player**; if a quantity leaves its value range, there is a **ninth** feedback channel, and that is a finding. The channel table in `spiel.md` has counted **eight** since version 5 | break tester |
| 7 | the three measures | decision density, strategy diversity, optimum shift per the calculation rules in `spiel.md`, against the thresholds there: **0.4 per game third**; **three classes with one winner each at most 25 % apart**; **shift ≥ 0.4** | self-player |
| 8 | backtest | in mode `weltlauf` (T38), 31 target series plus the trade block, error measures per T42, acceptance via the **16 check subjects with tolerance 2** per T37 | backtester |

**The seven value-range bounds that check 2 checks every round.** They follow from T5, T49
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

Plus the **two equalities** from T49: `land.<L>.leitzins = land.<L>.instrument.leitzins.stand`
and `land.<L>.haushaltssaldo = land.<L>.instrument.haushalt.stand`, per round and per country.

Bounds 1 and 5 are the two that without a test would go wrong silently instead of loudly:
a negative exchange rate turns every profit into a loss, and a market basket beyond the
overflow bound does crash per T7, but only in `tsd_in_cent` and thus at a place where
nobody looks for the cause.

**Check 6 runs past the end of the vintage window, and that needs a rule.**
The exogenous paths from T25 carry only R+1 support points. From round R+1 on they are
**frozen at their last value**, not carried forward, and the run is marked
`ueber_fenster`. Freezing is the sharper choice here: if a quantity runs away afterwards,
it is the model and not the input. Cost: 200 world steps.

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
vintage is simply not 25,000. At R = 24 it is 25,000, thus unchanged.

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

The price stands in T40 and T34 and is twice a number (band end 27,000 → 28,000, gap
boundary 27,001 → 28,001). The bound remains: `v ≤ 1.000` as long as the fund lives
(at `fondsvermoegen ≤ 0` way of dying 1 takes hold in the same round, T33 and T47; only
the rounding reaches the 1,000), and `e ≤ 2.000`, thus `25.000 ≤ B ≤ 28.000` in the
running case — above the band „mandate fulfilled" (up to 24,000) and below the death band
(from 31,000). **From that follows a property a valuation must have and that cannot be
seen in it: the bot never prefers death.** The worst running state stands at 28,000, the
best death at 31,000. Despite the formula identity, `B` remains a **bot-internal**
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
`R × (1 + 60) = 1.464` stays unchanged — and exactly for this a static valuation is
needed. A playout to round R per candidate would cost
`60 · Σ(R+1−t) + R = 60 · 300 + 24 = 18.024` world steps per game, twelve times as much,
and would overturn section 10.

**The three bots:**

- **Zufallsbot(startwert)** — admissible actions uniformly, draw per T35, without a
  profile. For checks 5 and 6.
- **Heuristikbot(profil)** — kinds per the stock procedure (T43), within a kind by a
  fixed, documented ranking. No playouts, hence cheap. **On the reference profile
  `(1,1,1,1,1)` it is the „feste Folgepolitik" of Maß 1.**
- **Suchbot(profil, kandidaten=60, tiefe=1)** — 60 candidates per T41, each computed one
  world step ahead and **statically valued per T44**; chosen is the smallest
  `B`, ties per T44 and never by order of discovery. There is no continuation by the
  heuristic bot at depth 1. Cost per game `R × 61`, at R = 24 thus
  **1,464** world steps.

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

| Class | Series | Count | Meaning |
|---|---|---:|---|
| `frei` | GDP (4), sector shares (12), consumer prices (4), exchange rate (3) | 23 (19 independent), plus the trade block | checks the machine, decides the acceptance |
| `gesetzt` | policy rate (4) | 4 | input of the run, error zero by construction; is reported, decides nothing |
| `abgeleitet` | government debt ratio (4) | 4 | numerator follows the set budget balance, only the denominator is endogenous; is reported, decides nothing |

**The acceptance runs over 16 check subjects with tolerance 2**, so set by `spiel.md`
version 3; my query from version 2 is thereby answered and struck from section 12. The
check subject is not the series but the quantity:

| Check subject | Count | aggregated from |
|---|---:|---|
| GDP per country | 4 | one series each |
| sector structure per country | 4 | the country's three share series, **all three** must pass |
| consumer prices per country | 4 | one series each |
| exchange rate per country except USA | 3 | one series each |
| trade block | 1 | 40 flows, median of the MAPE and median of the directional accuracy; the worst fifth is reported |
| **Sum** | **16** | |

A check subject passes if it holds both thresholds that apply to it. The run is passed if
at most two of the sixteen are breached; each breached one is named individually, with
both numbers. Reported are all 31 series plus the 40 flows; the sixteen
decide.

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

Everything on **one** core. With eight cores the night run falls to around
**15 seconds** at the plan value and to around **1.2 minutes** in the unfavourable case.
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
would lie at **2.5 to 9.8 hours** on one core. It would then be not daily but
occasional — and the calibration loop would be impossible even in the shortened version.
That is the number the choice from T1 hangs on. It has become smaller through the shorter
game, but the gap is the same: the factor decides, not the game length.

**At the buyer's** a round costs one world step: 10 microseconds. The memory footprint is
2.5 kB of state, under 1 MB of vintages and a few hundred kB of chain history. The
product runs on anything and needs no server — the idea's cost calculation (no cost per
customer) holds.

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
