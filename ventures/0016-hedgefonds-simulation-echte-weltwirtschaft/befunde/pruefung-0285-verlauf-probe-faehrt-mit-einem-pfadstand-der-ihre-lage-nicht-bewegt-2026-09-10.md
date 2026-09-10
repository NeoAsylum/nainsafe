---
typ: pruefung
paket: 0285-verlauf-probe-faehrt-mit-einem-pfadstand-der-ihre-lage-nicht-bewegt
pruefer: kern-pruefer
datum: 2026-09-10
urteil: geprueft
kriterium_geprueft: all four conditions read off the file and the build report; the twelve carrier values recomputed by hand from `stelle_instrument` and `musterwert`
befunde: 2
---

# `verlauf_probe` carries a pfadstand its own state agrees with

## How each condition was checked

**1 — the carrier mirrors `ausgangslage`.** `pfadstand_der_probe()` (`verlauf_probe.cpp:157-169`)
fills `stand[nummer][i]` from `musterwert(stelle_instrument(Gebiet{nummer}, Instrument{i},
InstrumentFeld::Stand))`. The read side is `werte::pfadstand` (`werte.cpp:618`):
`konstanten.pfadstand[land_nummer(land)][static_cast<size_t>(instrument)]`, and
`land_nummer` (`werte.cpp:382`) is the plain enum value. Same two indices, so the carrier
answers with the value the address holds. Recomputed by hand from `land_basis` (`44l`,
`zustand.hpp:810`), `LAND_INSTRUMENTE_AB = 24`, `INSTRUMENTFELDER = 4`, `Stand = 0` and
`muster[platz % 8]`:

| land | i=0 Leitzins | i=1 Zoll | i=2 Haushalt |
|---|---|---|---|
| US | 24 → `0` | 28 → `-10'000` | 32 → `0` |
| CN | 68 → `-10'000` | 72 → `0` | 76 → `-10'000` |
| DE | 112 → `0` | 116 → `-10'000` | 120 → `0` |
| BR | 156 → `-10'000` | 160 → `0` | 164 → `-10'000` |

Six at `-10'000`, six at `0`, none at either end of `i64` — the carrier itself cannot
overflow anything. One copy of the eight patterns: `123'456'789` occurs once in the file
(`:127`). Non-determinism grep (`float`, `double`, `unordered`, `std::map`, `std::set`,
`time(`, `rand(`, `chrono`): 0 hits; `pfadstand_der_probe` is `constexpr` over ordered
index loops.

**2 — the head says why.** `:153-154` "Diese Datei prueft den Verlauf und nicht die
Rechnung einer Runde"; `:140-144` names step 5, `kern::werte::schaden`, and the
`staatsschuld` at `I64_MIN` for two of four countries (`44l+19`: US 19→`10'000`,
CN 63→`I64_MIN`, DE 107→`10'000`, BR 151→`I64_MIN`). Its side claim at `:147-149`, that
the first moved stand is the tariff of the first country, holds: address 28 is US/Zoll and
is the lowest of the six. Its claim at `:183-185` that the carrier does not move the
parameter checksum is proven green next door — `schritt_probe.cpp:2020-2021` sets
`pfadstand[0][0] = 4'711` and asserts the checksum is unchanged.

**3 — nothing weakened.** `PARTIERUNDEN = PARTIELAENGE_HOECHSTENS` (`:377`); the `schritt`
calls still come from the loop over `PARTIERUNDEN` (`:386-397`), not unrolled; `ausgangslage`
still writes `musterwert` over `platz < FELDER` (`:342-344`).

**4 — green.** `uebersetzung-2026-09-10.md`: kern subtree `9/14 verlauf_probe … Passed`,
14/14; the top-level run passes 25 of 29 and its FAILED list is 20, 25, 27, 29. The three
reds are `werte.hpp`, `festkomma.hpp` and the belegstellen head — no file of this package.
175 links per round holds: the probe compares against `sollmaskengroesse(Modus::Weltlauf)`
(`:413`), whose `static_assert` names 175 (`schreiber.cpp:160-161`).

## Finding 1 — the criterion's "twenty rounds" is 26, and that made its anti-cheat rule too low

`PARTIELAENGE_HOECHSTENS = 26` (`verlauf.hpp:208`), so `PARTIERUNDEN` is 26 and the probe
runs 26 rounds, not twenty. Condition 4 wanted "twenty rounds"; condition 3 forbade touching
`PARTIERUNDEN`. Both cannot hold, so the criterion could not be met as written — not the
builder's defect, and it does not carry a `zurueck`.

It matters beyond wording. The `vermerk_annahme` says: *"Bedingung 4 verlangt den Bericht mit
zwanzig Runden und 175 Verknuepfungen je Runde; eine Zahl darunter ist der Beleg, dass
Bedingung 3 verletzt wurde."* That sets the cheat detector six rounds too low: a builder who
had cut `PARTIERUNDEN` to 20 would have passed the stated test. `ops/plan.md:98-104` carries
the same number chain. For the project manager, not the builder.

The number's origin is in the file: `:373` says *"gruen, als der Verlauf bei zwanzig abbrach
-- ein Nachweis, der nur bis zwanzig zaehlt"*. Proposal `0293`.

## Finding 2 — no build report has ever shown a probe's printed numbers

Condition 4 asks what the report shows. It cannot show it: ctest prints stdout only for a
failing test. Grepped every `uebersetzung-2026-09-0*.md` for `Groessen: sizeof`, `Runde 1:`
and `bip der Ausgangslage` — zero hits, including 2026-09-09, when `verlauf_probe` aborted.
The green run is still a proof, but by derivation: the two numbers are `PRUEFE`d in-test
against `PARTIERUNDEN` (`:399`) and `sollmaskengroesse` (`:413`), so green plus the two
constants settles them. **Any criterion of the form "the report shows &lt;number&gt;" is
unverifiable for a passing test; phrase it as "the probe asserts &lt;number&gt; against
&lt;constant&gt;" instead.** No package: making the report carry every probe's stdout would
cost more report than it buys.

## Where I looked and found nothing

Commit `ab9f74f` is titled "(4 Dateien)" while `dateien:` names one; the two neighbouring
`kernbauer` commits carry three. Grepped the whole venture outside `befunde/` for `0285`:
only `verlauf_probe.cpp`, this package and the two packages that cite it. No source file
outside the list is annotated with this package number. `lauf.py:521-576` limits the commit
to package file, `dateien`, own logbook and `befunde/*<kennung>*`, so the fourth entry is
bookkeeping, not a foreign write. I have no tool to read the diff; if the operator wants
certainty, `git show --stat ab9f74f` answers it in one line.
