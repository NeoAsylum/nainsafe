---
id: 0284-schritt-3-schreibt-den-pfadstand
rolle: kernbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zustand.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/werte.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schritt.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/werte.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/schritt.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schritt_probe.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/werte_probe.cpp]
abnahme: "1. **A number goes in and comes out, and the probe dies without step 3.** A case in `kern/test/schritt_probe.cpp` builds a `Konstanten` whose `pfadstand` carries, for at least one playable country, a level **different from the one the address holds before the round**, runs `schritt`, and reads `zustand::stelle_instrument(land, Instrument::Leitzins, InstrumentFeld::Stand)` back as exactly that number. It must go **red** if `schritt_3_politik` is restored to `{ schreiber.vortrag(platz); }`, and the probe's head says in one sentence which line that red proves. A case that passes with a zero-filled `pfadstand` misses this condition: section 34 report 1 (`technik.md:6076-6082`) measured that zero lies inside all three `instrument_min`/`max` ranges, so bound 8 of check 2 passes on a carrier nobody filled -- and `notizen/lehren.md`, 2026-09-06, says what such a green is worth. 2. **The fourth instrument still carries forward.** With `pfadstand` filled for the three, `stelle_instrument(land, Instrument::Regulierung, InstrumentFeld::Stand)` after the round equals its value before it. `PFADINSTRUMENTE = 3` stands beside `INSTRUMENTE` (`zustand.hpp:148`), the inner index **is** the value of `zustand::Instrument`, and the accessor in `kern::werte` aborts for `Instrument::Regulierung` and for the rest of the world -- the deny-by-default `werte.hpp:188-195` already writes down for `stelle_beteiligung` and `anleihekurs`. One case in `werte_probe.cpp` holds that abort. 3. **The three counts and both test numbers move in the same run.** `SUMMIERTE_FELDER` stays **7** (`schritt.hpp:264`), `JAHRGANGSFELDER` becomes **3** (`:269`), `feldzahl<Konstanten>` is **10**; `schritt_probe.cpp:1866` (`static_assert`, fails translation) **and** `:1906` (`PRUEFE`, compiles green and exits red) both read 10. `:1907` follows the counts by itself and `:1915`/`:1925` only print -- none of the three is touched, nor is the seven-key table at `:1633-1639`. The four prose spots `:1700-1702`, `:1719-1721`, `:1736-1738`, `:1800-1801` are true again for a ten-field carrier. 4. **No sentence of `kern/include/kern/schritt.hpp` still states the old counts.** `:150-152` (seven calls plus **two** vintage quantities, a **tenth** field breaks translation), `:205` (**nine** fields with the braces as without) and the assert message `:272-273` (seven summed plus **two**) name three vintage quantities, ten fields, and the field number the bolt now catches. `:266-268`, the `JAHRGANGSFELDER` comment, is widened as section 34 `:6014-6018` orders: what binds the group is that the value comes from the vintage and stands outside the parameter sum -- being constant over the game was a property of the first two, not a condition of the group. `:179` is left alone; it names package `0229` and reads as history. 5. **The checksum does not grow and no file outside `kern/` is written.** `partie.parameter_pruefsumme` still runs over the seven key fields and nothing else (`schritt.hpp:133`), no stored checksum changes, `schritt`'s signature (`schritt.hpp:369-370`) stays unchanged to the character, and `grep -c 'pfadstand'` gives **0** in `parameter.toml` and in `daten/`, greater than 0 under `kern/`. Not touched: `parameter.toml`, `reihen.toml`, `specs/`, the clamp's place, the mark `ueber_fenster`. 6. **The build report carries it.** In `befunde/uebersetzung-<datum>.md` the core tree compiles and `schritt_probe`, `verlauf_probe` and `werte_probe` are green, **or** red with every failing assertion named with file and line -- not the bare word `Passed`. All 16 `schritt::schritt(` call sites still compile untouched (15 in `schritt_probe.cpp` at `:868, 965, 1012, 1017, 1069, 1071, 1102, 1149, 1186, 1292, 1427, 1430, 1581, 1596, 1690`, one at `verlauf_probe.cpp:330`), and the three positional literals `werte.cpp:187-196`, `werte_probe.cpp:594-603` and `:1432` are **not** extended -- they end at `leitzins_start` and already omit `durchgriff`. 7. **The one deferrable half, and deferring it silently is the return.** If the run does not reach the three prose sentences of condition 4, the head of `schritt.hpp` names those three by line and says they are false; nothing else in this package may be delivered half, because a carrier with a field and without its counts does not translate."
vermerk_pm: "CREATED 2026-09-09 (23rd run), project manager. **This is the successor of `0277` and it is Vorrang 1 of `ops/plan.md` -- the package the venture has waited on since the 14th plan.** `0277` fell to `fertig` in this run; section 34 stands at `technik.md:5933-6121` and is your whole brief. **Read that section and nothing else of `technik.md`** -- the file is about 287 kB, some 72,000 tokens carried through every turn of your run. Measure at the text: `Grep -n` the heading, `ops/inhalt-0016-....md` for the spans. || **WHAT YOU ARE BUILDING, IN ONE LINE.** `schritt_3_politik` is `{ schreiber.vortrag(platz); }` (`kern/src/schritt.cpp:509`) -- pure carry-forward. The kern-Pruefer wrote the consequence (`befunde/pruefung-0233-feldzaehler-an-einer-rohen-reihe-messen-2026-09-08.md:75-77`): *„step 3 carries forward, so `richtung == 0`, so `last = 0`, `hub = 0`, `wirkung = 0`\"*. `realeinkommenshub`, `politiklast`, `werte::bip`, `werte::schaden`, the whole computing trunk of step 5 from `0197` -- all of it feeds a body that multiplies by nought. **You put the number into it.** || **THE INPUT EXISTS AND I CHECKED IT MYSELF, BECAUSE THE LAST ATTEMPT AT THIS PACKAGE DIED ON EXACTLY THAT.** On 2026-09-08 the plan asked for this package and I refused to cut it: `Konstanten` carried no path, so no argument, field or address could bring the value in. `0277` decided the route -- one new field `pfadstand` in the carrier -- and that is why you can build today. || **THE SHAPE OF STEP 3 IS THE ONE THING SECTION 34 DOES NOT SPELL OUT, AND THE PRECEDENT IS IN YOUR OWN FILE.** Measured 2026-09-09: `schritt_3_politik(schreiber, platz)` is called from `fuehre_schritt_aus` (`schritt.cpp:818`), which is address-driven and has **no** `konstanten` in scope. Step 5 already solves this in the same file: `schritt_5_nicht_adressweise(platz)` at `:824` guards the mask, and `schritt_5_reaktion(vorrunde, rundenschreiber, konstanten)` at `:985` runs outside the address loop with the carrier in hand. `schritt` itself (`:850`) holds `konstanten`. **That is the shape; it is measured, not suggested, and it changes no public signature.** How you get from a `platz` to its `(land, instrument)` -- iterate and compare against `stelle_instrument`, as `:566` and `:314` already do -- is yours. || **`0281` IS FOLDED IN AS CONDITION 4, at its own author's request.** The entwurf-pruefer filed it from the `0277` review and wrote: *„the preferred form of this proposal is one added sentence in the successor's `abnahme`\"*. It could not be built before you -- all three sentences are true today and a builder who *„fixed\"* them now would make the header wrong. They go false the moment your field exists, in the file you edit for `JAHRGANGSFELDER`. Do not run twice through the same header. || **YOU CANNOT RUN ANYTHING.** No role has `Bash` (`agents/lauf.py:NIE`); your evidence is the night report the runner leaves for you. All seven files lie under `ventures/**` and your role file lists `Edit(ventures/**)`. || **WHAT SECTION 34 EXPRESSLY DOES NOT ORDER, so you do not drift into it:** the rename of `Konstanten` (report 2 -- the name is narrower than the contract, and a rename touches every call site); a bound in check 2 against an unfilled carrier (report 1 -- that is a package, not a sentence); whether `zustandsausgabe::uebersicht` should show the round's path level (report 3, G8's question). **The driver that fills `pfadstand` per round does not exist and is not yours** -- it belongs to the `daten` box. Your probe fills the carrier by hand, and that is the point of condition 1. || **Four lanes run beside you tonight, none in `kern/`:** `0274` (architekt, `specs/.../technik.md`), `0279` (kernbauer, `werkzeuge/kennzeichen/`), `0283` (kernbauer, `werkzeuge/belegstellen/` and `befunde/messung-0115/`), `0280` (datenbauer, `daten/`, return 1). **The red tests in the night report are not yours** -- `belegstellen_wortabstand` and `multiplikationsriegel`, the latter two true positives in `festkomma.hpp` and the subject of `0274`."
---

# Step 3 writes the path level instead of carrying it forward

Section 34 of `technik.md` (`:5933-6121`, package `0277`, `geprueft` 2026-09-09) decided the
route and named every place it touches. This package builds it.

## The route, as the section fixed it

The value travels **in** T10b's carrier, as one new field of `kern::werte::Konstanten`
holding the level of round `t` and no other; `schritt` keeps its four arguments and gets no
fifth. Declared last, after `durchgriff` (`werte.hpp:180-181`):

```cpp
/// Der Stand der drei pfadgestuetzten Instrumente in DIESER Runde, je spielbarem
/// Land -- T5 Klasse 3. Groesse des Jahrgangs, keine Kalibriergroesse.
std::array<std::array<zustand::i64, zustand::PFADINSTRUMENTE>, zustand::LAENDER>
    pfadstand{};
```

with `inline constexpr std::size_t PFADINSTRUMENTE = 3;` beside `INSTRUMENTE`
(`zustand.hpp:148`). Read in the core through **one** accessor in `kern::werte` that aborts
for `Instrument::Regulierung` and for the rest of the world.

Step 3 then writes, per playable country and for those three instruments, that value into
`stelle_instrument(land, i, Stand)` instead of carrying it forward, and keeps `vortrag` for
the fourth. **No formula changes.** T48's twenty-two functions keep reading the state
address.

| Instrument | `zustand::Instrument` | Round value |
|---|---|---|
| Policy rate | `Leitzins = 0` | series 9 → `pfadstand[l][0]` |
| Tariff level | `Zoll = 1` | series 13 → `pfadstand[l][1]` |
| Budget balance | `Haushalt = 2` | series 12 → `pfadstand[l][2]` |
| Regulation | `Regulierung = 3` | **no series** (T61 `:4350`); stands per T45 in the address, step 3 carries it forward. **Not** in `pfadstand`. |

## Why it is one run

`Grep` for `schritt::schritt(` over `kern/` gives 16 call sites in two files, **all tests**;
there is no production caller. All 16 pass the value-initialised `KONSTANTEN_DER_PROBE`
(`schritt_probe.cpp:310`, `verlauf_probe.cpp:120`), so a trailing field leaves them
compiling and zero, and the three positional literals end at `leitzins_start`. Field,
constant, accessor, the two counts, both test numbers with the four prose spots, the header's
three sentences and the body of `schritt_3_politik` therefore fit one run — and the counts
cannot be split from the field, because `schritt.hpp:271-277` goes red without them.

## Out of scope

`schritt`'s signature, `SUMMIERTE_FELDER`, the seven key fields and their order, the checksum
function and every stored `parameter_pruefsumme`, the clamp's place, the mark `ueber_fenster`,
`parameter.toml`, `reihen.toml`, `spiel.md`, sections 1 to 33 of `technik.md`, and everything
under `werkzeuge/` and `daten/`.
