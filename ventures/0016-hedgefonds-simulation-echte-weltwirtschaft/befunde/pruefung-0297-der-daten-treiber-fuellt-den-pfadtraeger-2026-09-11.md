---
typ: pruefung
paket: 0297-der-daten-treiber-fuellt-den-pfadtraeger
pruefer: daten-pruefer
datum: 2026-09-11
urteil: geprueft
kriterium_geprueft: "each of the seven conditions re-derived from the four files in `dateien`, the two build reports, `reihen.toml`, `parameter.toml` and T23 P5/P8, T40, T51, §9, §34"
befunde: 2
---

# 0297 — the seven conditions, and what I held each against

1. `uebersetzung-2026-09-11.md`: the skip list (`:20-22`) names `konsole`, `oberflaeche`,
   `werkzeuge/aufbereitung` and **not** `daten`; `cmake -S` `:16` and `--build` `:30` code 0;
   Warnsatz bolt `:24` **32** targets, all with the set — against **29** on
   `uebersetzung-2026-09-10.md:25`, +3 = `daten`, `daten_geprueft`, `jahrgang_probe`.
   `PROJECT_IS_TOP_LEVEL` block at `daten/CMakeLists.txt:23-34`.
2. `reihen.toml`: series 9 `"Leitzins"` (`:1228`), 13 `"Zollniveau, aggregiert"` (`:1575`),
   12 `"Haushaltssaldo"` (`:1503`), **all three `modelleinheit = "bp"`** (`:1230,1505,1577`),
   and the only three carrying `rolle = […"politikpfad"]` (grep: 3 hits). Same triple in
   `werte.hpp:206-207` and `technik.md:6142-6144`. Regulierung and RW are excluded by field
   width, not by a caller check. `runden()` forms R (`jahrgang.cpp:142`), no literal.
3. `leitzins_start()` = `stelle(land, Leitzins, 0)` (`:203-206`); no second member.
4. `fuelle_pfadstand` writes `[l][i]` in the declaration order of `werte.hpp:235-236`, read
   back through `kern::werte::pfadstand`. Round 1 → support point 0, beyond R → the last.
   Sentence at `jahrgang.hpp:168-178`. **See finding 1.**
5. `Wertebereiche` is an argument (`jahrgang.hpp:96-103,226`); `instrument_min/max` are keys
   of `parameter.toml` (`:1109,1132,1149`), no member of `Konstanten`, and `grep pfadstand
   parameter.toml` = 0 as §34 `:6196` demands. `pruefe_wertebereich` counts and names, never
   assigns — the path still reads 3300/3340 after (`jahrgang_probe.cpp:292`). `aufschlag_min`
   takes the minimum over all l and t of the **policy-rate row alone** (`:216-231`), with
   `festkomma::minus` against overflow. Recomputed: −50 → 51, 0 → 1, and `parameter.toml:1262`
   closes the same circle (`-50 >= 1 - 51 = -50`).
6. `jahrgang_probe` green in all three trees it is configured in: `daten/bau` #1,
   `schnittstelle/bau` #16, workspace run (31 tests against yesterday's 30). No
   `float`/`double`/`reinterpret_cast`/`new`/`delete` under `daten/` (grep: 0).
   `PFADINSTRUMENTE == 3` and `LAENDER == 4` are proved by the green probe, not assumed.
7. `parameter.toml` and `daten/reihen.toml` both sit **before** the four package files in
   mtime order (`Glob` sorts ascending) — untouched. `grep '0297\|daten::Jahrgang'` over
   `kern/` = 0 hits.

The three red tests in the workspace run were the same three on 2026-09-10 (`:211-213`), all
name files outside `daten/`, and `multiplikationsriegel` read **23 files on both days** — it
does not see `jahrgang_probe.cpp`. Not this package.

## Finding 1 — round `t` enters the series as `t−1` here and as `t` in the spec

`stuetzstelle_zu_runde` (`jahrgang.cpp:182-191`) returns `min(runde−1, R)`. `technik.md` says
`min(t, R)` in the **only two places that name this accessor**: §9 `:2740` („in `daten`, in the
one accessor that answers ‚value of path P in round `t`': `t` enters the series as
`min(t, R)`", owner *data builder*) and §34 `:6132`. §9 `:2735` fixes the same reading: „At
R = 24 the support points cover rounds 0 … 24, so rounds 25 … 200 are outside the window".

Condition 4 says the opposite („Runde 1 gibt die erste Stuetzstelle"), and it has T40 behind
it: `exogen_ab_runde = bruchjahr − startjahr + 1` (`:1049`) makes 1999 **round 3** in a window
from 1997 (T23 point 8, `:1864`), i.e. index = round − 1. **The spec carries both maps, one
year apart.** The builder obeyed his criterion — that is why this is `geprueft` and a finding
to the project manager, not a `zurueck`.

What it costs, in the probe's own numbers (`STUETZSTELLEN = 5`, `R = 4`): round 4 → index 3 →
US policy rate 530, round 5 → index 4 → **540**, round 6 → 540. `ueber_fenster(5)` is already
true (`:145`, exactly §9 `:2741`) while the path still *moves*: the freeze §9 `:2732` demands
(„frozen at their **last value**") starts a round late, and the frozen value is not the last
one played. Support point R — the window's last year — is then read by no in-window round at
all. In the backtest that is a one-year offset on every reported policy series.

Proposal written: `0303-eine-runde-und-ihre-stuetzstelle-stehen-zweimal-verschieden.md`
(`architekt`, `technik.md`). The data builder cannot decide it: both contradicting sentences
are in `specs/`.

## Finding 2 — an unset support point is a zero and nothing marks it

`pfad_{}` is value-initialised (`jahrgang.hpp:240`) and `setze` is optional, so a gap inside
`stuetzstellen_` is indistinguishable from a measured 0. The class comment guards the case
*beyond* `stuetzstellen_` (`:128-132`), not this one. §34 report 1 (`:6154-6157`) already
measured the dangerous half: zero lies inside all three ranges of `parameter.toml`, so
`pruefe_wertebereich` stays clean on a carrier nobody filled — while the rule it names („the
accessor either returns a support point or the vintage build aborts at the gap") has no
carrier in this type. Outside the acceptance (the loading way is expressly not in this
package), so named and not inflated; it belongs to the package that writes
`jahrgang-<jahr>.bin` in `werkzeuge/aufbereitung`, which does not exist yet.

## Where I looked and found nothing

Units and base across the three series (all `bp`; `aufschlag_min` reads the rate row alone —
the one place tariff bp could have been mixed into a rate bound); the order of the two carrier
indices; overflow on `1 − min` at the smallest `i64`; a second store of `leitzins_start`; a
silent capping instead of a report; a read past the field at `runde = 1'000'000`; writes
outside `daten/`; licence — no source is touched, `reihen.toml` only cited.
