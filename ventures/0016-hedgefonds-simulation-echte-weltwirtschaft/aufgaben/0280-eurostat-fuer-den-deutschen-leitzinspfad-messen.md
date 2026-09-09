---
id: 0280-eurostat-fuer-den-deutschen-leitzinspfad-messen
rolle: datenbauer
status: gebaut
haengt_an: []
vermerk_pm: "CREATED 2026-09-09 (22nd run), project manager. **This is the one lead of the critical path that no package has ever queried, and `spiel.md` names it by hand.** `spiel.md:3128-3132`, under *Offene Entwurfsfragen*: *„Two leads already stand in our own records and are only named here, not checked: **Eurostat** is, per `daten.md` Nr. 7, commercially usable for EU and EFTA countries and thus covers the German -- or rather the euro-area -- side.\"* Package `0234` measured the procurement question on 2026-09-08 and its verdict is *„not reachable within the vetted sources\"* -- but `grep -i eurostat` over `daten/quellenbefund-leitzinspfad.md` gives **zero hits**. It queried IMF and the World Bank. The lead `spiel.md` wrote down was never tried. || **THIS IS NOT A GATE AND NOT A NEW SOURCE.** Eurostat stands in `daten.md` as Nr. 7 with its conditions in wording, and `daten/lizenzbefund-reihen.md:248` says so. Way 1 of `daten/quellenbefund-leitzinspfad.md:160-162` (BIS, ECB portal, national central banks) *is* a gate and is **not yours** -- do not go there, not even to compare. **You measure; you embed nothing.** || **YOU CLOSE AT MOST ONE OF THE TWO COUNTRY GAPS, AND THAT IS THE PACKAGE, NOT A SHORTFALL.** `daten.md` Nr. 7 excludes non-EU/EFTA countries from commercial reuse, so Eurostat cannot answer China. China's remaining route inside the vetted sources is a concept compromise (`FR.INR.LEND` covers CHN 25/25 window years but is a bank lending rate) and that is an architect's decision, way 2. Say this in your file so the next reader does not expect the whole problem solved. || **DO NOT GUESS DATASET CODES.** Enumerate them from Eurostat's own catalogue and record what the catalogue says. A code named from memory that happens to exist is indistinguishable from research and is forbidden by CLAUDE.md. || **Two lanes run beside you, neither in `daten/`:** `0277` (architekt, `technik.md`) and `0275-eine-zahl`/`0279` (kernbauer, `werkzeuge/kennzeichen/`)."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/quellenbefund-leitzinspfad-eurostat.md]
abnahme: "1. The file enumerates every request made: dataset code as the catalogue names it, country, requested window, HTTP status, and the **count of window years actually returned** -- one row each, countable, no summary sentence in place of a row. A retrieval date stands on every row. 2. It states for DEU/euro area, over the window **2001-2021** (`R = 20`, 21 support points, package `0054`), whether a policy rate is obtainable, and names which rate concept the found series measures -- deposit facility, main refinancing operation, money-market rate or something else -- read off the catalogue's own description and quoted, not inferred from the name. 3. It states whether `daten.md` Nr. 7 permits the found series for this product, citing the wording, and whether the attribution required by the licence is nameable. If the answer is no, that closes the package as well. 4. **`ergebnis: nicht erreichbar` is an accepted outcome** -- but only with condition 1 met for every attempt, including the failed ones, and with the reason per attempt (404, empty, window short, concept wrong). An unreachable source with an enumerated trail is a result; a verdict without the trail is not. 5. Nothing outside this one new file is written: not `daten/reihen.toml`, not `daten/quellenbefund-leitzinspfad.md`, not `specs/`. Carrying the number into series 9 is the follow-up package and is named at the end of your file."
---

# Eurostat for the German policy-rate path — the lead nobody queried

## Why this is worth a night

Step 3 of the round carries forward and therefore the whole computing trunk of step 5
multiplies by nought (`ops/plan.md`, *Der Engpass*). Package `0277` decides the **route** a
path value takes into the round. This package is the other half: **whether there is a value
to send down it.** `daten/reihen.toml:1256`, series 9:

> `deckung_urteil = "reisst -- DEU und CHN tragen in dieser Quelle keinen einzigen Wert,
> USA endet 2020"`

The path is needed three times over (`spiel.md:3123-3125`): as `leitzins_start[l]`, as the
exogenous path in the `weltlauf`, and as the instrument's value range in the `spielmodus`.

## What is already measured, so you do not redo it

`daten/quellenbefund-leitzinspfad.md`, package `0234`, revised by `0241`, `0252`, `0253`:
`IMF.STA/MFS_IR` returns nothing for CHN in any frequency; DEU is empty in all five World
Bank interest-rate codes of topic 7 (`FR.INR.DPST`, `FR.INR.LEND`, `FR.INR.LNDP`,
`FR.INR.RINR`, `FR.INR.RISK`, each queried singly) and in `FR.INR.MMKT`; USA runs
1950–2020 without 2021, BRA 1997–2025 gapless in the window. **The widest reach of any
single code covers three of four countries and measures no policy rate.**

**Its own list of ways out** (`:158-169`) names three, and Eurostat is in none of them —
because that file only ever looked at two source families. `spiel.md` names it; nobody
followed it up.

## The one thing that could make this package worthless

Answering from what you know about Eurostat rather than from what a request returned. The
value of `0234` is its enumeration, not its verdict; the same holds here. **A row per
request, or the package is not done.**
