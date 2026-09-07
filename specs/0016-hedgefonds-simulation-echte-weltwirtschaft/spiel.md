---
typ: spiel
idee: 0016-hedgefonds-simulation-echte-weltwirtschaft
erstellt: 2026-09-01
schleife: Each round the player places up to three actions from five kinds, the world computes one year forward, and every change in a number carries the chain of its causes with it.
siegbedingung: The mandate — fund assets above a threshold AND influence above a threshold in at least two countries — reached within R rounds, without first dying by one of the three ways of dying. The result is the number of rounds until fulfilment.
aktionen: 5
laender: Layer 1 — 4 policy countries (USA, China, Germany, Brazil), after package 0118 nine: plus Japan, India and Chile as backtest countries, Singapore and Saudi Arabia as play-only countries. So L = 9, L_R = 7, L_S = 2, n = 1. Layer 3 — one non-playable rest-of-world aggregate. Layer 2 see boersenplaetze.
boersenplaetze: Layer 2, B = 3·(L+1) — per territory one venue per lead sector. At L = 9 that is 30 venues of four fields each plus one position slot, hence 150 addresses; state 890, tradable venues 75. Tradable, not influenceable, no trade line, no target series.
gueter: 3 sectors (agriculture, industry, services), 2 of them with trade lines
takt: 1 round = 1 year; R = 20 rounds, start state 2001, end state 2021, 21 support points
gegenkraefte: 5
messbar_entscheidungsdichte: Per round t = 1…R and per start value 30 drawn action bundles; each replaces the bot actions of round t, after which the heuristic bot plays on the reference profile (1,1,1,1,1) until round R. Dichte(t, Startwert) = share of the 30 results that deviate from the median of these 30 by more than 1.000 milli-rounds; Dichte(t) = mean over the 50 start values. Acceptance = mean of Dichte(t) per game third (1-6, 7-13, 14-20) each >= 0,4.
messbar_strategievielfalt: Profile = fifths distribution over the five action kinds (126 profiles), effect via the stockpile procedure; per profile a search bot over 20 start values, profile result = median. A profile wins if its median lies <= 20.000. Strategy core = the strongest of the three families position/stake/lobby; the 6 profiles without any family action have no core and do not count. Acceptance = all three cores produce at least one winner, and the best class result is at most 25 percent better than the worst of the three.
messbar_optimumsverschiebung: Early window = rounds 1-6 with profile p, rest with the reference profile; late window = rounds 14-20 with profile p, rest with the reference profile; 126 profiles x 20 start values each, median as profile result, best profile per window by smallest median (ties by profile identifier). Shift = L1 distance of the two profile vectors divided by 5, values from {0; 0,4; …; 2,0}. Threshold 0,4.
messbar_rueckvergleich: Start vintage 2001, R = 20 rounds in weltlauf (fund subsystem switched off), policy instruments exogenous on the historical paths; check subjects 3·L_R + (L_R − n) + 1 out of L_R(S+3) − n free target series plus the trade block, each over 21 support points without filling — today L_R = 4, hence 16 out of 23; after package 0118 L_R = 7, hence 28 out of 41. Thresholds: MAPE 20 percent for level series, mean absolute error 300 basis points for rate series, directional accuracy 0,6 for all, formed over the transitions in which the target series moves. Passed if at most ⌊L_R/2⌋ check subjects break — today 2, after 0118 3.
---

# A hedge fund with four countries, three sectors and four policy levers — and every number that moves says why.

*Fifth version, after
`ventures/0016-.../befunde/pruefung-0001-entwurf-abnahme-runde6-2026-09-01.md` and against
`ventures/0016-.../aufgaben/0001-entwurf-abnahme.md`. Compared with the fourth version,
exactly three places are changed: the new section **What a basket is worth, what a step is
and what a bond costs** (finding 1), the **channel table**, which thereby gains an eighth
channel, and three lines in the table of quantities without a data anchor. No number of the
fourth version changes, no state address is added. The working-off of the two findings
stands at the end of the file, that of the earlier rounds below it.*

*Added on **2026-09-02** from work package `0021-schaden-gegenkraft-5`: the section
**Der Schaden in Gegenkraft 5, als Rechenvorschrift**, six lines under „Was bewusst
fehlt", five under „Offene Entwurfsfragen" and a table under „Was der Architekt neu
rechnen muss". This addendum too changes no number of the fifth version and no state
address; it fills the gap that `technik.md` section 12 point 3 reported.*

*Changed on **2026-09-03** from work package `0039-zollzeile-konjunktursockel`, after
findings 1 and 2 of the check of 2026-09-02. The **tariff line** of the damage prescription
no longer measures the whole shift of the sector price, but **only the share the tariff
wedge has in it** — way 1 of the three the finding left open. Affected are six sections
under *Der Schaden in Gegenkraft 5*, one new line under
*What must hold for price formation*, the line for channel 3, four lines under „Was bewusst
fehlt", three under „Offene Entwurfsfragen" and the follow-up table. This addendum too gets
by **without a new state address**; the number of read accesses falls from a claimed
120 to a recounted **106**. The working-off of both findings stands at the end of the file.*

*Changed on **2026-09-03** from work package `0054-partielaenge-r-entscheiden`. **R has
fallen from 24 to 20, the window from 1997–2021 to 2001–2021, the number of support points
from 25 to 21.** Series 9 (policy rate) is **no longer a target series** and keeps its two
other roles; the number of target series thus falls from 31 to **27**. The 16 check subjects
of Maß 4 and the tolerance of 2 remain **unchanged** — the four struck series were never
among them. The reasoning stands in full in the section **The game length R**, the list of
places to follow up under *Was der Architekt neu rechnen muss*. This is the case the
replacement rule of the fifth version was written for: R is replaced and nothing else.*

*Second run of the same package, likewise on **2026-09-03**. The decision stands
unchanged; added is solely the block **Nachtrag desselben Tages** under *Was der
Architekt neu rechnen muss*, because the follow-up table of the first run had not named
seven places in `technik.md` — six of them outside a T-block, among them the complete
runtime budget in its section 10. No number of this file changes as a result, no state
address, and `technik.md` remains untouched.*

*Changed on **2026-09-04** from work package `0055-zollzeile-vergleichszahl-zustand-b`, after
finding 1 of the check of 2026-09-03. Affected is **one** paragraph: the comparison number in
the section **Zwei Zustände, zwei Zahlen**, which carried a quantity of a foreign state under
the label „Zustand B". It is replaced by the number that follows from the table above it
(**8.472.000**), the table gains the one input row that was missing for that, and the
working-off stands at the end of the file. No decision, no state address, no calibration
number and none of the numbers of state A change.*

*Changed on **2026-09-05** from work package `0119-welt-in-drei-schichten`, after an objection
by the operator from the same day: a hedge fund that can hold something in only four countries
is not a global hedge fund. New is the section **Die drei Schichten der Welt** with the
second layer, the **exchange venues**; plus half a sentence in action 1, a paragraph under
*The state* (which level the 310 means), a paragraph under *Warum die Größe des Zustands
keine Verteidigung ist*, **seven** entries under „Was bewusst fehlt" — six new ones and the
first, „More than four countries and three sectors", extended instead of struck —,
five under „Offene Entwurfsfragen" and a block under „Was der Architekt neu rechnen muss".
**No number of the existing four countries, no target series, no check subject and no
error measure changes**; the reference number of the state remains **310** until 0116 and
0118, and the layer sum **890** holds for the level after both. The second layer costs
**two** new keys in `parameter.toml` and **no ninth feedback channel**.*

*Changed on **2026-09-06** from work package `0118-fuenf-weitere-laender-auswaehlen`, after the
operator's instruction of 2026-09-05 („Lass uns insofern direkt 5 weitere Länder
einplanen") and his choice of Weg A (the slots grow with `L`). New is the section
**Welche neun Länder, welche Klasse, und was Weg A kostet** under *The state*; plus two
lines in the frontmatter, the counting rule of Maß 4 in `L_R` instead of in digits, four
entries under „Was bewusst fehlt", five under „Offene Entwurfsfragen" — one of them
**closed** — and a block under „Was der Architekt neu rechnen muss". **The 310 stay in
place** until 0116 has written the derivation chain; no number in `technik.md`,
`reihen.toml` or in the core is touched. The five are **Japan, India, Chile, Singapore and
Saudi Arabia**, the first three expected as backtest countries, the last two as play-only
countries; with that `L_R = 7` and the number of check subjects grows from 16 to **28**,
the tolerance from 2 to **3**.*

*Changed on **2026-09-07** from work package `0198-realeinkommen-als-rechenvorschrift`, after
`befunde/ergebnis-0197-schritt-5-reaktion-rechnet-die-zustimmung-2026-09-07.md`: the core
builder could not build step 5 because `Realeinkommen` occurs in eight lines of `specs/` and
in none of them as a formula. New is the section **Das Realeinkommen in Gegenkraft 2, als
Rechenvorschrift** under *Die Gegenkraefte*; plus a reference in counterforce 2, the **line
for channel 2** together with its explanation, four entries under „Was bewusst fehlt", two
under „Offene Entwurfsfragen", three additions in the complaints table and a block under
„Was der Architekt neu rechnen muss". **No state address is added** — the 310 remain 310,
the 890 remain 890 —, no key in `parameter.toml`, no ninth channel; the derived quantities
from T48 grow from 22 to **25**. Two places are **corrected**: the paragraph „It costs"
under *Was die Entscheidung kostet* and the corresponding entry under „Was bewusst fehlt"
had promised the foreign tariff a path via counterforce 2 that the rule written here does
not carry.*

## The game length R, and why it stands here as a letter

The second version derived the game length from a rule — *the game length is the length
of the window in which every target series is covered without a fill* — and then plugged
in a wrong number. The third version kept the rule and plugged in a second number,
measured against **three** of the 31 series and the trade block — the three US
sector-share series and BACI. **Since 2026-09-02 all 31 are measured**, and both numbers
were too large.

### What is measured

`daten/deckungsbefund-1997.md` (package `0006-deckung-pruefjahrgang-1997`, `status: fertig`,
retrievals of 2026-09-01) retrieved each of the 31 target series and the trade block
individually. Of the 31, 26 hold the window 1997–2021 in full. Five do not, and they are
of two different kinds:

| Series | Country | Finding | Role per `technik.md` section 7 |
|---|---|---|---|
| **11** government debt ratio | USA | begins **2001** (IMF WEO) | start + target (**derived**) |
| **11** government debt ratio | BRA | begins **2000** | ditto |
| **9** policy rate | USA | ends **2020** (IMF `MFS_IR/DISR_RT_PT_A_PT`) | start + policy path + target (**set**) |
| **9** policy rate | DEU | **not a single value** | ditto |
| **9** policy rate | CHN | **not a single value** | ditto |

Add a side finding outside the target series that co-decides here: **series 12 (budget
balance), the historical policy path of the fourth instrument, likewise begins in 2001
for the USA** — two independent WEO series with the same starting year, cross-checked in
the finding against six known values. That is no retrieval uncertainty but the known
property of the WEO of carrying the fiscal statistics of the US general government only
from 2001 on.

### The decision: R = 20, window 2001–2021, 21 support points

The finding lays three ways out side by side, each with an R — 19, 20 or 24. **Chosen
is 20.** The other two fail for one reason each, and both reasons stand in the role
column of the series list: a series here is not simply "there" or "gone", it has up to
three roles — start value, policy path, target series — and a way out that strikes it
strikes only one of them.

**2001 is forced, and not by a target-series rule.** The way out to `R = 24` is called
„Reihe 9 und Reihe 11 gestrichen" in the finding. But only the *target role* of a series
can be struck, not its other two. Series 11 is also **start**: `staatsschuld[l]` is a
state address, and its start value is the first support point of this series. Series 12
is **policy path**: without it, the budget instrument in the `weltlauf` stands on
nothing. Both gaps are **leading gaps**, and the fill rule from T24 reads „Fortschreibung
des letzten bekannten Werts" — before the first support point there is none. A leading
gap cannot be filled by the rule that exists.

**`R = 24` thus demands three source replacements, and none of them is to be had.**
Individually, because they differ:

| what would have to be replaced | state after the coverage finding |
|---|---|
| series 11 **BRA** 1997–1999 | The IMF WEO begins in 2000, the World Bank (`GC.DOD.TOTL.GD.ZS`) in 2010. **No value in either checked source.** That alone settles 1997. |
| series 11 **USA** 1997–2000 | The World Bank carries the USA gap-free 1997–2021 — but it measures the debt of the **central government**, the WEO that of the **general government**, and for China and Germany it carries nothing. The way out would mean: a target series that comes, per country, from a different source with a different delineation. That is exactly the defect over which the policy rate is losing its target role right now. |
| series 12 **USA** 1997–2000 | **Not measured.** The finding found it as a side finding, not as an assignment. It would first have to be searched for. |

The first row is binding: it says no without the other two having to be decided. Writing
a number into this frontmatter that stands on data nobody has would be exactly the
mistake of the second version all over again.

**2021 is not forced.** The window ends in 2020 only because the **US policy rate** ends
there. Per `technik.md` T37 this series was **set**: in the `weltlauf` the instrument is
set to the historical value, its error is zero by construction, its directional accuracy
one, and it is none of the 16 check subjects and could become none. **All series that
decide anything hold 2021** — GDP, the twelve sector shares, consumer prices, the three
exchange rates, the trade block, plus all four debt ratios. `R = 19` thus throws away the
support point 2021 to protect a series that cannot fail. And the one thrown away is not
just any: a backtest that ends in 2020 checks the crash and never the rebound. Its last
transition is a plunge without a counterpart, and directional accuracy measures, across
the sharpest movement of the whole window, exactly one direction.

**From this follows the cut:** series 9 loses its target role and keeps start and policy
path. The target series are thus **27** — series 1 (4), series 2 (12), series 8 (4),
series 10 (3), series 11 (4) — and **all 27 hold 2001–2021 with 21 support points without
a single fill.** That is the largest window in which this sentence is true.

### What the three ways out cost Maß 4 — and why that does not decide the choice

Because the acceptance of this package demands it by name, here for each way out the
check subjects rather than just the target series:

| Way out | R | Window | Support points | Target series | Check subjects of Maß 4 |
|---|---:|---|---:|---:|---|
| series 9 **and** series 11 out of the target series — *rejected, window not reachable from data* | 24 | 1997–2021 | 25 | 23 | **16**, none struck |
| series 9 supplemented for DE/CN, all 31 stay target series — *rejected, sacrifices 2021* | 19 | 2001–2020 | 20 | 31 | **16**, none struck |
| **series 9 out of the target series — chosen** | **20** | **2001–2021** | **21** | **27** | **16**, none struck |

**In all three ways out it is sixteen, and that is the real finding of this package.**
The 16 check subjects draw on series 1, 2, 8, 10 and 14 — GDP per country (4), sector
structure per country (4), consumer prices per country (4), exchange rate per country
except the USA (3), trade block (1). Series 9 and series 11 do not appear in them and
cannot appear in them: the one is an input of the run, the other follows the set budget
balance and has only one endogenous denominator — GDP, which already has four numerators
of its own. **Exactly these two series are the ones that shortened the window.** The
acceptance rule „höchstens 2 der 16 reißen" therefore does not distinguish the three ways
out, and it was never what was at stake.

*The 16 and the 2 of this section are the state of 2026-09-03 and hold unchanged for
`L_R = 4`. Since package 0118 both stand as formulas — `3·L_R + (L_R − n) + 1` and `⌊L_R/2⌋`,
at `L_R = 7` thus 28 and 3. The choice of R does not touch this: all three ways out above
would have had the same set of countries, and the comparison stays valid as it stands.*

What was at stake are two other things, and by them the decision was made: **which window
is reachable from data at all** (that settles 24) and **what a support point is worth**
(that settles 19). What the backtest loses through the cut is therefore no check subject
either, but **resolution**: each of the sixteen is measured over 21 instead of 25 support
points, directional accuracy over 20 instead of 24 transitions. The thresholds — MAPE
20 percent, 300 basis points, directional accuracy 0.6 — stay unchanged; whether they are
easier or harder to hold over a shorter window is a measurement for the backtester and
not a decision of mine.

### What the cut costs, item by item

- **Four rounds.** The game is a sixth shorter than in the fifth version, the nightly run
  of the three Maße 17 percent cheaper (11,519,040 → 9,539,200 world steps).
- **The euro start 1999 lies before the window.** With it falls the only instrument lock
  that snaps shut *during* a game: Germany had no interest-rate lever of its own from
  round 3 on, now it has none from round 1. The asymmetry **between** the four countries
  stays — it is what the argument in *Warum vier Länder und nicht drei* stands on —, the
  transition **within** the game is gone. For Maß 3 that is the loss of one of three
  named sources; the other two, imitators (counterforce 4) and price shock (counterforce
  3), are untouched, and the shift was never grounded on the euro.
- **The exchange-rate chaining `verkettet_ab = 1999` never runs in the check vintage.**
  It stays in the specification because the play vintages before 2001 need it — but the
  check vintage no longer tests it along the way. That belongs in every finding instead
  of being booked as "one special case fewer".
- **One filled support point in the policy path.** The US policy rate has no value for
  2021. As a path — not as a target series — it is carried forward per T24 and marked
  with `gefuellt = 1`. That is **one** input year for **one** country, and it acts on the
  last transition of the US check subjects. It is disclosed, not netted away.

### What the cut keeps, and a bonus

Still inside the window: China's WTO accession (December 2001, effective from round 1),
the financial crisis of **2008** (end of round 7), the slump of **2020** (end of
round 19) and the recovery of **2021** (end of round 20). Likewise the negative euro
deposit rate from 2014, on which the bound `aufschlag_min` hangs — see
*What a basket is worth*.

And one property that neither of the two rejected values has: **20 is a multiple of 5.**
Under the stock procedure the stock vector stands at `(0,0,0,0,0)` again after every five
rounds. For every run that plays **the same** profile for a whole game — that is all 126
runs of Maß 2 and every carrier game of Maß 1 — the game therefore ends exactly on such a
point, and every action type has received exactly `12 · ai` of the 60 slots. At 24 and at
19 the game ends mid-cycle, and the actual distribution of types deviates from the
profile that Maß 2 and Maß 3 carry as an independent quantity. That is no main reason; it
is the only point at which the chosen number is **better** than the two rejected ones and
not merely less bad. (For Maß 3 it does not hold: its windows are 6 and 7 rounds long,
the profile switch does not fall on a zero point, and the deviation within a window stays
bounded instead of zero — as before.)

### And the real lesson is not in the number, but in how it is written down

The second version wrote `28` into every derived quantity — result scale, game thirds,
window bounds, cost formulas. A single wrong measurement thereby made twelve numbers
wrong. **That is why in this draft every derived quantity stands as a formula in R, with
R = 20 substituted.** This run is the test of that: against the fifth version the
measurement cost four rounds, and the draft changed by twelve substitutions and by no
rule. No package has been built twice.

**And R can fall further.** Three paths on which the `weltlauf` hangs are to this day
**not measured**: the population and employment paths (series 5 and 6) and the tariff
path (series 13, with an open licence question on top). `daten/reihen.toml` carries them
with `deckung_gemessen = false`. The substitution rule holds for them just the same: if
the vintage build measures narrower, R is to be replaced and nothing else.

## The loop

A round is a year and runs in six steps, always in this order. The fixed order is no
formality: it is the condition for the same seed and the same action sequence delivering
the same result in three months.

1. **View.** The state, and beside it the chain of the previous round: what changed,
   triggered by what, via which detour, with what delay.
2. **Actions.** The player places **up to three** actions. Three, not arbitrarily many —
   the scarcity is the source of decision density. Whoever can do everything does not
   choose.
3. **Politics.** Pending lobby pressure and counter-lobby are netted against each other
   per instrument, delays from earlier rounds that fall due take effect, instruments move
   by at most one step per round.
4. **Economy.** Production from capital stock and productivity, trade between the four
   countries and the rest of world, prices, real incomes, interest rate, exchange rate,
   public finances.
5. **Reaction.** Approval, change of government, oversight counter, imitator counter,
   investor base — the five counterforces settle up.
6. **Settlement.** Positions valued, leverage checked against the intra-year swing,
   mandate checked, chain stored as a diff.

Within a round **no state quantity is written twice**, and the order above is cycle-free.
*Which* quantities are written at all depends on the mode — in `spielmodus` all of them,
in the `weltlauf` of the backtest a declared subset (see **Maß 4**). The only loop in the
whole model is the market clearing in step 4, and it runs with a fixed iteration count.
Everything that looks like a feedback crosses a round boundary — see **The state**.

### What must hold for price formation

The how is the architect's business; what must hold stands here.

For the two sectors with trade rows there is one world price each, clearing all supplies
and demands, and on it a tariff wedge per country. A country's sector price, however,
does **not** hang entirely on the world price, but only to the share `durchgriff`:

```
preis = weltpreis_mit_zoll · durchgriff + landespreis · (10.000 − durchgriff)
        alles geteilt durch 10.000
```

Both quantities in it are now determined, and neither was in the second version:

**`landespreis` is the sector price of the same quantity from the previous round.** In
round 1 it is the vintage's start value (index 10,000). The excess function is thereby
monotone in the world price, the bisection search from `technik.md` T28 is a single pass,
and no fixed-point problem arises. In substance this is price inertia: a sector's
domestic price follows the world price with a one-year lag, and how strongly is said by
`durchgriff`.

**`durchgriff` is a model construct with a rule, not a measured share.** The second
version called it `handelsanteil` and defined it as (exports + imports) divided by the
sector's value added. That quantity leaves its value range, and not as an outlier but by
construction: exports and imports are gross flows, value added is net. For Germany 1995
it yields 2.69 in agriculture and 1.20 in industry (recomputed by the reviewer from WDI,
retrieved 2026-08-31); the weight on the country price turns negative, and the announced
mixture becomes an extrapolation with negative prices.

The rule therefore reads, with `H` = the sector's exports plus imports and `N` = its
value added, both in the start year:

```
durchgriff = teile_gerundet(10.000 · H, H + N)
```

That is strictly monotone in `H/N`, lies in the range 0 … 10,000 for all nonnegative
`H`, `N` with `H + N > 0`, and needs no cap. The two recomputed cases become
`71.94/98.71` → **7,288** for German agriculture and `915.39/1,675.41` → **5,464** for
German industry; a US industry with `H/N = 0.3` would come to 2,308. **The ordering that
carries the argument is thus preserved** — a tariff hits China's industry hard via its
high `durchgriff` and the US industry, dominated by construction and utilities, weakly —
and the value range holds.

What the coefficient thereby is **not**: a measurement of trade openness. Its numerical
value has no economic meaning; it must order countries and sectors correctly, and it
does. It is exogenous and constant over the game; China's growing trade openness is
captured by the model through the quantities, not through the price transmission. Two
named simplifications, none hidden.

Services have no trade row, no world price and only a country price.

### The tariff wedge is multiplicative, and the scale table decides that

`technik.md` T28 **names** the wedge („der Zollkeil je Gebiet auf dem Weltpreis") without
writing it down. Until 2026-09-03 that was without consequence; since the damage rule of
counterforce 5 separates the wedge from the rest of the price lift, it no longer is. What
must hold:

```
weltpreis_mit_zoll(l, s) = mal_geteilt( welt.preis.<s>, 10.000 + zollstand(l), 10.000 )
```

**The additive reading is not more poorly justified — it cannot be formed at all.** The
tariff level stands, per `technik.md` T5, in **class 3** (basis points), the world price
in **class 5** (index, start year 10,000). A sum of two classes is unknown to T5; a rate
meets a level in this model without exception as a factor, as in
`schuld = mal_geteilt(bip, staatsschuld, 10.000)`. In substance the same choice says the
same: an aggregated tariff rate per country in basis points is an ad valorem tariff,
otherwise it would not be a rate. Both point in the same direction, which is why the
determination here is a clarification and not a choice.

It stands here and not in an open question because a computation rule that points to an
unwritten formula is again just an adjective — exactly the defect that package 0021 set
out against.

### The mapping of the BACI goods codes to the two tradable sectors

Without it neither `H` nor the trade block is computable. It is a table in the vintage's
manifest and reads:

| HS92 chapter | Model sector |
|---|---|
| 01–24 | 1 agriculture |
| 25–97 | 2 industry |

**The error of this coarse mapping is part of the deal:** raw wood (44), hides (41) and
vegetable textile fibres (50–53) are counted by WDI as agriculture, by this table as
industry; processed foods (16–21) are counted by WDI as manufacturing, by this table as
agriculture. The error is the same for all five territories because the same table
applies — and it hits the target series just as it hits the model, because the backtest's
trade block arises from the **same** aggregation. What is compared is thus aggregated
against aggregated, just as with the sector shares normalised to 10,000.

## The actions

Five kinds. Each is discrete, none has a point in time within the round. The
identifiers 1 to 5 are at the same time the tie-breaking order of all Maße.

1. **Position.** Long or short on a country×sector, on a currency, on a country's
   government bond, or — since 2026-09-05 — on an **exchange venue**
   (see *Die drei Schichten der Welt*). In fixed steps, effective immediately, unwindable at any
   time. Entering and exiting moves the price against the fund, and the more strongly the
   larger its share of that market is.
2. **Stake.** A permanent share in a country×sector. It is illiquid — exiting takes two
   rounds, and its exit discount is already built into the valuation, so it is paid in
   full at entry (see *What the fund's assets are*) — and it is the only path to
   cheap lobbying: lobbying actions in a sector the fund holds a stake in cost a
   fraction.
3. **Lobbying budget.** Money on one policy instrument of one country, in one direction.
   It does not act immediately but attaches as pressure; whether it takes hold is decided
   by step 3 against the counter-lobby. Possible without a stake in the affected sector, but expensive.
4. **Leverage.** Borrowing at the country's policy rate plus a spread that rises with the
   fund's visibility. Magnifies every position and every losing streak.
5. **Visibility.** The fund publicly discloses a position or withdraws from view.
   Disclosure amplifies every lobbying budget on that matter, because it creates public
   pressure — and it feeds the supervision counter in every country the fund is present in.

**Why five and not three.** Kinds 1 to 3 are the three strategy families against which
Maß 2 is measured; without them there is nothing to measure. Leverage is not a strategy of
its own but the attack surface of the first way of dying, and without it size is riskless.
Visibility is the reason the counterforces are a playing field and not a brake:
without it, attention would be a mere penalty on success; with it, it is a
decision — loud and fast versus quiet and slow. That is exactly what produces the
shift of the optimum that Maß 3 demands.

## The state

**310** integer quantities; the line-by-line listing stands in `technik.md` T15 and is
recomputed there. The number itself is no defence — see below.

**These 310 are the status as of today and remain the reference number until package 0116
has written the address arithmetic parametrically.** The five further countries have been
chosen since 2026-09-06 (package 0118, see *Welche neun Länder*); with that the country
sum at `L = 9` stands at **740** and the state after all three layers at **890** —
computed, but not yet the reference number, because the address arithmetic must first
carry it. What this section describes is the first of three layers; the second (exchange
venues) and the computation that leads to **890** stand under *Die drei Schichten der
Welt*. Two uncommented sums in one document are the beginning of the next counting error,
which is why each of the two says which status it means.

**Per country** (four countries): three sectors with value added, capital stock,
employment and price; population and employed persons; productivity; price level and
inflation; policy rate; exchange rate against the US dollar as numéraire; government debt
and budget balance; approval of the government; supervision counter; influence; four
policy instruments, each with level, pending pressure, counter-pressure and remaining
delay; three remaining-duration counters.

**The rest of world** carries the same sector and aggregate quantities, but **no policy
instruments, no approval, no supervision counter and no influence** — the fund can
neither trade nor lobby there. It closes the circuit; without it the sum of the four
trade balances would necessarily be zero, which is false against the real data.

**Trade:** a full matrix over **five territories × four counterparts × two sectors with
trade rows = 40 flows**, the rest of world with rows of its own. Only so does the
invariant "sum of all trade balances including rest of world = 0" hold.

**The fund:** cash, positions, stakes, leverage level, global visibility, investor base,
market share, excess return of the last three rounds. Plus, per country×sector, an
imitator counter (12) and the market basket (value and return) as reference quantity.

**Influence per country** is the fund's smoothed share of the total lobby pressure in
that country, 0 to 100. It is the second half of the victory condition — and the quantity
whose acquisition wakes all the counterforces.

### The four policy instruments

| Instrument | Data anchor | Remark |
|---|---|---|
| Policy rate | yes, but **as a path, not as a target series** (since 2026-09-03, see *The game length R*) | For Germany **exogenous from 1999**; that lies before the window 2001–2021, so Germany has no interest-rate lever of its own over the whole game. This asymmetry is intended, see below. |
| Tariff level | yes, but **only aggregated per country** (WDI, with reservations) | No tariff per sector. The sector effect arises from `durchgriff` and the import shares, not from an invented sector tariff. |
| Budget balance / government spending ratio | yes (IMF WEO) | |
| Capital-flow and financial-market regulation | **no, pure model construct** | Must exist, because otherwise the supervision has no point of attack on the fund. Without a target series; in the backtest fixed at the start value, and the oracle is blind to this instrument. |

### Every quantity without a data anchor, with its start value

Acceptance condition 2 demands that every quantity is either traced back to a series from
`daten.md` or marked as a model construct with a formation rule. The anchored ones stand
in the architect's series list. Here stand **all the rest** — except for the eleven whose
provenance is `technik.md` T46 and which this table cannot know, because they follow from
comparing the series list with the address listing (US exchange rate as numéraire, five
aggregate quantities of the rest of world, five rebasing counters). **Together with T46
the enumeration is exhaustive, and only together was it ever that.** That is
observation 2 from `technik.md` section 12, accepted here rather than disputed:

| Quantity | Start value | Rule in the run |
|---|---|---|
| Sector price (per territory × sector, 15) | index 10,000 | market clearing, see above |
| World price (per tradable sector, 2) | index 10,000 | market clearing in step 4, see above |
| `landespreis` | = sector price, round 1 thus 10,000 | previous round's sector price |
| `durchgriff` (per territory × tradable sector) | constant of the vintage | `10.000·H/(H+N)`, fixed over the game |
| Approval (per country) | from `parameter.toml` | counterforce 2 |
| Supervision counter (per country) | 0 | counterforce 1 |
| Imitator counter (per country × sector) | 0 | counterforce 4 |
| Influence (per country) | 0 | smoothed share of lobby pressure |
| Lobby pressure per instrument (16) | 0 | action 3, netting in step 3 |
| Counter-pressure per instrument (16) | 0 | counterforce 5 |
| Remaining delay per instrument (16) | 0 | step 3 |
| three remaining-duration counters per country (12) | 0 | counterforces 1 and 2 |
| Financial-market regulation (level) | from `parameter.toml` | instrument like the other three |
| `markt.wert` | value of the start basket at start prices | frozen basket of amounts made of twelve baskets and four bonds, T33; valuation see *What a basket is worth* |
| `markt.rendite` | 0 | ibid. |
| Fund cash, investor base | from `parameter.toml` (start capital) | actions and settlement |
| Market share | 0 | value share of the market basket, formula under *What a basket is worth* |
| Leverage level, visibility, excess return (3) | 0 | actions 4 and 5, settlement |
| Stakes (12 shares + 12 remaining durations) | 0 | action 2 |
| Position slots (20) | 0 | action 1 |
| Game: round | 0 | bookkeeping of the run |
| Game: vintage identifier | from the vintage's manifest | fixed over the game |
| Game: parameter-set checksum | from `parameter.toml` | fixed over the game |
| Game: mandate status | 0 | step 6, mandate check |

**This table is the provenance entry for the 150 draft addresses**, and only with the
seven rows of the fourth version and the reference to T46 is it what it claims to be. The
reconciliation against the 310 addresses from `technik.md` T15 is not mine but comes from
the check of 2026-09-01: without a provenance entry there remained **32** addresses
(lobby pressure and remaining delay per instrument, added by the architect in T23
point 1) and **six** (two world prices, four game fields, for which T45 knew no
admissible entry kind). All 38 now stand here, where the table had promised them. That is
the condition on which the vintage build would otherwise abort per T45.

### What the fund's assets are, and whether the stakes belong to them

The architect returned the question (`technik.md` section 12, point 3), and it is a model
question. **They belong:**

```
fondsvermoegen = Kasse + bewertete Positionen + bewertete Beteiligungen − Hebel
```

**The reason is not taste but Maß 2.** If they did not count, action 2 would turn cash
into something that appears in neither half of the mandate; class 2 could then not pass
the first acceptance half of Maß 2 regardless of any calibration, and a Maß that fails
one of its three classes by construction measures nothing.

**Valuation is at exit value, that is, at the model value of the country×sector basket
minus the exit discount.** "Fund assets" thereby means the same thing throughout — *what
the fund is worth if it stops here* — and that is exactly what the result quantity, the
mandate and way of dying 1 need. The discount is thus paid when the stake is **built up**
and is not deducted a second time on an ordinary exit; the stake stays illiquid over the
two rounds of exit duration. The forced sale from counterforce 1 is untouched by this —
its discount is an additional penalty and comes on top.

**And the rule that secures the denominator of the fund return:** if the fund's assets
fall to zero or below, way of dying 1 (forced liquidation) takes effect in the same
round. A return on a nonpositive denominator is thus never formed.

### What a basket is worth, what a step is and what a bond costs

The fourth version decided **that** the stakes count toward the fund's assets, and
`technik.md` T47 wrote that down as a formula. That made visible that two names in it are
formed nowhere: `korbwert(l, s)` and `positionswert(p)`. Both are model decisions and
therefore stand here; with the **bond price**, which the reviewer named as the third gap
(„für die vier Anleihe-Steckplätze gibt es nicht einmal einen Preis"), they are three,
and they hang together.

#### One valuation formula, three amounts, three prices

Every valuation in the model has the same construction — **amount times price, converted
into the numéraire**:

```
wert(menge, kurs, gebiet) = mal_geteilt(menge, kurs, wechselkurs[gebiet])
```

Price and exchange rate are both indices with start value 10,000; their scale factors
cancel against each other, and the valuation needs no constant. For the USA,
`wechselkurs` stands permanently at 10,000 as the numéraire; there the formula is a pure
price valuation. Amount and price per slot kind:

| Slot kind | Amount | Price |
|---|---|---|
| Country×sector (12) | `kapitalstock[l][s]` | `sektorpreis[l][s]` |
| Currency (4) | `handelsvolumen[l]` — the country's exports plus imports over both tradable sectors, from the trade matrix | 10,000, fixed |
| Bond (4) | `schuld[l] = mal_geteilt(bip[l], staatsschuld[l], 10.000)`, with `bip[l]` = sum of the three sectors' value added | `anleihekurs[l]`, see below |

From this the four valuations from which T47 gets its two missing names:

```
korbwert(l, s)   = wert(kapitalstock[l][s], sektorpreis[l][s], l)
anleihewert(l)   = wert(schuld[l],          anleihekurs[l],    l)
waehrungswert(l) = wert(handelsvolumen[l],  10.000,            l)

stufenwert(p)    = mal_geteilt(markt(p), stufenweite, 10.000)
positionswert(p) = stufen(p) · stufenwert(p), in Fondsgeld umgerechnet
```

`markt(p)` is the basket, bond or currency value of the slot, `stufen(p)` its signed step
count from T16. The first four quantities stand in the **economy-wide scale**,
`positionswert` is per T5 **fund money** — the scale boundary thus runs exactly between
`stufenwert` and `positionswert`, and what that means stands below. The slot currency USA
stays permanently empty per T16, the formula has no effect there.

`staatsschuld[l]` is, per series list no. 11 and the class *rates* from T5, the **ratio
in basis points**, not the amount — hence the detour via `bip[l]`. A denominator of zero
occurs in none of the three rows: the exchange rate, being an index, is strictly
positive — that is a condition on the exchange-rate rule and a value-range bound the
break run checks —, the 10.000 is a literal, and the bond denominator is bounded below.

#### Why the capital stock and not value added

Both stand in the state, and the reviewer named both as candidates. It is the **capital
stock**, for three reasons, and the third decides:

1. **T33 point 3 demands a basket of amounts** to be valued at this round's prices. A
   stock is an amount, an annual flow is not. With the capital stock the frozen basket of
   amounts from T33 is a nameable quantity for the first time.
2. **A stake is a share in what a sector owns**, not in what it earns in a year. The
   yield sits in the price, not in the amount.
3. **Value added fluctuates yearly, the capital stock does not.** If a basket's value
   hung on value added, every production fluctuation would move it more strongly than any
   lobbying action — and the causal chain this game sells
   („Zoll → Importpreis → dein Bestand") would vanish in the noise of its own side
   quantities. The capital stock changes only via channel 1, that is, slowly and with
   delay; **the price change is thereby the visible part of the valuation, and that is
   exactly the number the buyer wants explained.**

A multiple on value added (a "price-earnings ratio") would be the third reading. It costs
a second free parameter without an anchor and yields the same ordering; it is therefore
not chosen.

**The capital stock per sector needs a start rule, and it is the same as for value
added.** Series list no. 3 delivers a capital stock **per territory**, the state carries
three **per territory and sector**. They arise in the start year from the sector shares
normalised to 10,000 (series 2), exactly as the three value-added figures arise from GDP
and the same shares:

```
kapitalstock[l][s] = mal_geteilt(kapitalstock[l], sektoranteil[l][s], 10.000)
```

After that it is endogenous via channel 1. That is no new mechanism but the existing one
applied a second time — and it keeps the three sector capital stocks in the rank
`Datenanker`, because both input series are anchored.

#### Why a step is a share and not an amount

`stufenweite` stands in `parameter.toml` (T27). **It is a share, in ten-thousandths, of
the market the slot hangs on, not a money amount.** A step on `US×Industrie` is thus
*`stufenweite` ten-thousandths of that basket*, and its price is what that share costs
today.

**The reason is the state, not taste.** If a step were a fixed money amount, every slot
would need its entry price just to be valued at all — twenty further addresses, a second
place for the same truth and a state that is no longer readable out of itself. As a
share, the value follows **entirely from today's state**: if I buy a step, the cash gives
up its present value and the slot takes it in, net zero; if the price then moves, the
slot moves and nothing else. With a negative step count the sign flips, and a price rise
is a loss — long and short are the same formula, as Maß 2 demands.

**Three quantities that hang on this are thereby computed as well:**

- **The fund's share in a country×sector**, in ten-thousandths:
  `|stufen| · stufenweite + anteil[l][s]`. Position and stake are shares in the **same**
  basket and add up. Absolute values, not signs — a large short moves a market as
  strongly as a large long.
- **The local footprint from counterforce 1** reads exactly this number, and so does the
  price impact from action 1 ("the more strongly the larger its share of that market
  is"). Neither needs a concept of its own any more.
- **`fonds.marktanteil`**, formed in step 6 per T33 point 4, that is, against the new
  `markt.wert`:

  ```
  korbbestand  = Σ über die 12 Körbe    mal_geteilt(korbwert(l,s), |stufen|·stufenweite + anteil[l][s], 10.000)
               + Σ über die 4 Anleihen  mal_geteilt(anleihewert(l), |stufen|·stufenweite,               10.000)
  marktanteil  = teile_gerundet(korbbestand · 10.000, markt.wert)
  ```

  Currencies do not enter — per T33 point 1 they carry no capitalisation. The
  `handelsvolumen` is the **depth** of the currency market and carries step value and
  price impact, not the market basket. `markt.wert` is a sum of positive amounts times
  positive prices and thus never zero.

**What the calibration has to hit here, and what it fails on.** Start capital and
`stufenweite` together fix how large the fund can become relative to the world. Two
conditions, both readable off the test bench: a step must be affordable out of the start
capital, and reachable step counts must be able to reach the supervision thresholds from
counterforce 1 at all. If the parameter set misses the first, class 1 never wins; if it
misses the second, no counterforce takes hold and Maß 3 falls to zero. **A third dial for
this — say, an "investable share" of the capital stock — would be redundant with the
start capital: only the ratio of the two quantities acts.** It therefore does not exist.

#### The bond price, the only new price quantity

The state carries `leitzins` and `staatsschuld` per country, but no bond price — the
reviewer rightly remarked that the four bond slots thus hang on nothing. It gets **no
address but a rule**, like `landespreis` (T39):

```
anleihekurs(l) = teile_gerundet(10.000 · (leitzins_start[l] + aufschlag), leitzins[l] + aufschlag)
```

`leitzins_start[l]` is the start year's policy rate, which the vintage carries anyway as
the first support point of the policy path (series 9); `aufschlag` is a new key in
`parameter.toml`, in basis points, and means the distance between policy rate and bond
yield.

That is the price of a perpetual bond: strictly falling in the interest rate, exactly
10,000 in the start year by construction, positive for every positive denominator,
without a cap. **The bound sits at the instrument and not at the price:** the policy rate
has a lower bound, and it is `1 − aufschlag`. The denominator is thus never zero and
never negative, and the vintage build can check it — the historical policy path must
respect it, otherwise the parameter set is inadmissible for that vintage.

**That is a real condition and not a formal one, and it hits exactly this window.** The
ECB first cut its deposit rate below zero on 2014-06-11, to **−0.10 %**, and by
September 2019 to **−0.50 %**; it stayed negative until 2022
(`ecb.europa.eu/press/pr/date/2014/html/pr140605_3.en.html` and
`ecb.europa.eu/stats/policy_and_exchange_rates/key_ecb_interest_rates/html/index.en.html`,
retrieved 2026-09-01). Germany follows the euro area exogenously over the whole game —
the 1999 break lies before the window 2001–2021 —, so the negative rate from 2014 on lies
**in the check vintage**, namely in its rounds 13 to 20. Whether the interest series the
vintage draws carries the deposit rate or the main refinancing rate is decided by the
vintage build; the lower bound must in both cases lie below the series' minimum, and
`aufschlag` is thus not freely choosable but bounded from below.

Two properties that arise for free here, and I keep them. First, the interest sensitivity
is **implicit and different per country**: at a low rate the price reacts strongly, at a
high one weakly — a German holding hangs on the interest rate, a Brazilian one barely.
That costs no parameter and distinguishes two of the four countries along one more axis.
Second, the bond is the only asset the fund can hold **without influence**; it can
therefore never win alone, because the mandate has two halves. An interest-rate bet is a
way to build capital, and never a way to win the game.

#### Where the scale boundary lies

`korbwert`, `anleihewert`, `waehrungswert`, `stufenwert`, `korbbestand`, `schuld` and
`markt.wert` are **economy-wide amounts** and stand in that scale (T5, line 109).
`positionswert`, `beteiligung_wert`, cash and leverage are **fund money** (line 108). The
conversion lies exactly on this boundary and happens **once per valuation, at the
outermost call** — that is, after the shares are netted, not before. `marktanteil` does
not cross the boundary at all: numerator and denominator both stand in the economy-wide
scale.

The second way, which the reviewer left open — carrying `korbwert` in fund money
directly — is thereby ruled out, and the reason is T33: the market basket values the same
twelve baskets, and it is an economy-wide quantity. Two scales for one basket would be
two valuations for one basket, and T47 demands „eine Bewertung, nicht zwei". **Which
function performs the conversion is the architect's business; that it stands at this spot
and only there is design.**

#### No new address

No quantity of this section is a state address. `korbwert`, `anleihewert`,
`waehrungswert`, `stufenwert`, `korbbestand`, `anleihekurs`, `schuld`, `bip` and
`handelsvolumen` are functions of the state; `stufenweite`, `aufschlag` and
`leitzins_start` are parameters or, respectively, constants of the vintage. `marktanteil`
is the only address that appears at all, and it already stands in T15.

**The 310 from `technik.md` T15 thus remain unchanged, the table *Every quantity without
a data anchor* gets no new address — only three more precise rules —, and the counting
step from T45 comes out unchanged.** That is exactly why it did not find the gap: it lay
outside the set it counts over. The counting step checks addresses; this gap was a
missing **function**, and the only remedy is that someone writes the formula down.

### Warum die Größe des Zustands keine Verteidigung ist

`agentenbau.md` names as this genre's sore point that „ein Modell mit tausenden
rückgekoppelten Größen leicht chaotisch wird, und dann trägt kein Regressionstest mehr".
What helps against that is not a small number of fields but a small number of
**fed-back channels**. Within a round there are none; across the round boundary there
are exactly eight, and they are exhaustively enumerated here:

| # | Channel | Damping |
|---:|---|---|
| 1 | profit → investment → capital stock → production → profit | one round of delay, depreciation rate |
| 2 | instrument → burden → real income → approval → change of government → instrument | instrument at most one step per round; the change is decided in step 5 and takes effect only in step 3 of the following round |
| 3 | instrument → trade → world price → damage → counter-lobby budget → instrument | counter-pressure takes effect only in the following round |
| 4 | assets → leverage → position size → price impact → assets | leverage cap, markup rises with visibility |
| 5 | visibility → supervision counter → forced sale → market share → visibility | counter is integer with an upper bound, three fixed thresholds |
| 6 | excess return → imitator counter → price → excess return | counter is integer with an upper bound |
| 7 | excess return → investor base → position size → price impact → excess return | deduction only after three rounds, fixed share per round |
| 8 | assets → lobby budget → instrument → price → valuation → assets | delay and at most one step per round; counter-pressure grows with the damage (counterforce 5); supervision grows with influence times share (counterforce 1); imitators graze off the price gain (counterforce 4) |

**Channel 8 is new in this version, and it was there the whole time.** It is the loop
this genre dies at — *whoever is ahead can lobby more, and whoever lobbies more is
further ahead* — and it stands verbatim in the idea's example („Zoll +5pp → Importpreis
→ dein Bestand Sektor 3 +8,3%"). It was missing from the table because the link
*valuation* was, until this version, not a computed step but a word; only the section
*What a basket is worth* makes it nameable. Four dampings act on it, all four already
stand in the draft, and **three of them grow with success** — that is the reason it is
damped and not merely slow. The bond variant of the same channel (lobbying the policy
rate instead of the tariff, `anleihekurs` instead of `sektorpreis`) is not a ninth
channel but the same one with a different instrument and a different price.

The shortcut `instrument → damage → counter-lobby budget → instrument`, which has stood
in counterforce 5's tariff line since 2026-09-03, is **not a ninth**: it is channel 3
without its detour via the quantity. The tariff level now enters there twice — via
`handelsvolumen` as before and via `hub(l, zoll)` newly — both times into the same link
*damage*, and both times with the same damping: the counter-pressure is written only in
step 5 and can take effect only in step 3 of the following round. No link is added and
no round boundary removed.

**Channel 2 changed its head on 2026-09-07 and has remained the same channel.** It began
with *price* as long as real income was a word; since *Das Realeinkommen in
Gegenkraft 2* it reads the **burden** from the instrument step and not the price. That
is channel 2 without its detour via the price, exactly as the tariff shortcut is
channel 3 without its detour via the quantity — one link fewer, no round boundary fewer.
The damping is the same and just as enforced: the instruments are written solely in
step 3, the change of government falls in step 5, so between cause and reset lies
exactly one round boundary. No ninth channel arises.

The price channel `sektorpreis(t−1) → landespreis → sektorpreis(t)`, by contrast, is
**not one of its own**: it is channel 3 in its price link, written out. Its damping is
the share `(10.000 − durchgriff)/10.000`, hence strictly smaller than one as long as
`durchgriff > 0`; for services with `durchgriff = 0` it is a pure carry-forward without
amplification.

**The second layer brings no ninth channel, and that has been checked, not asserted**
(see *Die drei Schichten der Welt*). Four ways lead into it, and each is an existing
channel with a different price in the sector price's place:
`sektorpreis → index → valuation → assets → lobby → instrument → sektorpreis` is **channel 8**
— the same answer that already stands there for the bond, a third time;
`leitzins → zins[b] → index → …` is the same channel in its interest-rate variant, delayed
longer by the halving; `excess return → nachahmer[b] → index → excess return` is **channel 6**;
`assets → leverage → position size → price impact → index → assets` is **channel 4**, and
`index → markt.wert → excess return → investor base → …` is **channel 7**. **What grows is the
branching, not the number of channels:** via `weltzins` an interest-rate step in one country
reaches all thirty venues instead of only the three of its anchor. The damping of this broader
path is computable and small — a step on `leitzins[A]` enters `weltzins` with the
capital-stock weight of `A`, there with `1/2` into `zielzins(b)` of a foreign anchor and then
once more with `1/2` into the halving, so with nine countries of roughly equal size with about
`1/(4·9) ≈ 2,8 Prozent` in the first round. **And the layer is a leaf:** no quantity of the
policy-country or the rest-of-world layer reads a field of an exchange venue. That is
mechanically checkable and the actual defence — a leaf cannot close a circle it does not
itself run through.

**That is the defence, and it is checkable**, unlike a field count: the break tester is
given the stipulation to run the model **200 rounds without a player**; if any quantity
leaves its value range in the process, there is one channel more, and that one is an
error. A channel that does not stand in this table is not a feature but a finding.

### Warum vier Länder und nicht drei

With three countries every tariff has exactly one diversion partner. The system's
reaction to every lobbying action is thereby single-move and predictable — Maß 1
collapses, because a choice without alternatives is no choice. With four countries there
are two diversion paths of different size, and which is the better one changes with the
state. That is the mechanism from which Maß 3 can arise at all.

The four are chosen by structural difference, not by importance: **USA** (large domestic
market, lead currency, service-heavy), **China** (industry-strong, high `durchgriff`,
managed exchange rate, strong tariff lever), **Germany** (export surplus and **no
interest-rate lever of its own** — the only asymmetry that closes one action space and
thereby forces another; since the window cut to 2001 it holds from round 1 instead of
from round 3, see *The game length R*), **Brazil** (agricultural exports, high interest
rates, volatile currency). Four countries that resemble each other would be four copies
and would cost strategy diversity instead of generating it.

**This section stays as it stands, and its argument carries all the more with nine
countries** — it says why three are too few, not why four would be enough. Which five
join is in the next section.

### Welche neun Länder, welche Klasse, und was Weg A kostet

**Directed by the operator on 2026-09-05:** *„Lass uns insofern direkt 5 weitere Länder
einplanen."* The number is decided; the selection was not. The rule for the selection is
the same as for the first four: **structural difference, not importance** — and
structural here does not mean "told differently" but **different in a quantity this
model actually computes**: `durchgriff`, sector shares, capital stock, trade volume,
debt ratio, the lower bound of the interest-rate lever, the number of a country's own
instruments.

All numbers below are values of the **start year 2001** from exactly the series the
model embeds anyway: World Bank `NV.AGR.TOTL.ZS`, `NV.IND.TOTL.ZS`, `NV.SRV.TOTL.ZS`,
`NE.TRD.GNFS.ZS`, `NY.GDP.MKTP.CD`, `PA.NUS.FCRF`, `FP.CPI.TOTL.ZG`, retrieved on
2026-09-06 via `api.worldbank.org/v2`; the debt ratios from the IMF WEO (`GGXWDG_NGDP`,
`imf.org/external/datamapper`, same retrieval). **They substantiate the choice, they do
not replace the vintage build** — the values the model computes with arise there and not
here.

#### The five, and for each the property that none of today's four carries

**Japan — the bond market is larger than the economy, and the price level falls.**
Series 11 carries **126,8** percent for Japan in the start year and **222,7** in the end
year; because `schuld[l] = mal_geteilt(bip[l], staatsschuld[l], 10.000)` is the *amount*
of the bond slot, Japan's bond market is larger than its GDP from the first move on and
more than twice as large at the end. The USA come to 53,5 and 125,0, Germany to 58,1 and
67,9. Add the second half, which no current country has: series 8 is negative for Japan
in **twelve of the twenty-one** support points (2001–2005, 2009–2012, 2016, 2020, 2021).
The check subject *Verbraucherpreise* thereby measures a **falling** price level for the
first time — to date it rises in all four countries, and an error measure that has seen
only one direction is not a tested error measure. **Conjecture, expressly unchecked and
not part of the justification:** a country with twelve deflation years should also carry
the model's lowest policy-rate path and thereby bind the bound
`aufschlag_min = 1 − min(leitzins_pfad)`. That has not been measured; it is decided at
the same retrieval Japan's class hangs on, and I write it down only so the data builder
looks for it at the retrieval.

**India — the only large agricultural sector that does not live off world trade.**
Agriculture **21,62** percent of value added, normalised 23,5 — against 13,82 in China,
4,80 in Brazil, 1,13 in the USA and 1,08 in Germany; over the whole window the share
never falls below 16,03. At the same time only **25,99** percent trade to GDP. Both
together are the property: just under a quarter of the economy hangs on a sector that
has a world price **and** a tariff wedge, but with large `N` and small `H` in
`durchgriff = 10.000·H/(H+N)`. **Brazil is the counter-case** — small `N`, large `H` —
and to date the model knows only that one. A large, *closed* agriculture is something
different from a small, open one: a foreigner's tariff lever barely reaches it, the
country's own budget and regulation levers all the more. **Checkable prediction, not a
label:** `durchgriff[IND][1]` lies below that of every current country in agriculture.
If it does not come true, that is a finding against this paragraph.

**Singapore — the upper end of the pass-through scale.** Trade **349,29** percent of
GDP, against 59,56 in Germany and 22,97 in the USA; the MAS justifies its own
monetary-policy framework with the same order of magnitude (*Monetary Policy Framework*,
mas.gov.sg, retrieved 2026-09-06). The agriculture share is **0,08** percent — there `N`
is near zero and `H` is large, so `durchgriff` runs toward its upper bound 10.000: **the
sector price is the world price.** It is exactly for this edge that the formula was
chosen (*„liegt … im Bereich 0 … 10.000 und braucht keine Kappung"*), and to date no
country comes near it. The scale of the mechanism the whole game sells runs today from
22,97 (USA) to 59,56 (Germany), that is, over a factor of **2,6**; with Japan at the
lower end (19,28) and Singapore at the upper end, over a factor of **18,1**.

**Saudi Arabia — the only constant exchange rate, and the only sector above half.**
Series 10 carries the same value 3,75 for Saudi Arabia in **every** one of the 21
support points. Industry **50,78** percent of value added, normalised 51,3 — no current
country lies above China's 44,28. Thus for the first time a *tradable* sector with world
price and tariff wedge carries the majority of an economy, and a tariff step anywhere
hits not a fringe there but the core. The constant rate is at the same time the reason
for its class, see below — it is not a side property but the sharpest one of the whole
section.

**Chile — the smallest economy with all four instruments of its own, and thereby the
cheapest influence.** GDP **71,6** billion USD in the start year, against 559,98 in
Brazil — the smallest of today's four — and 10.582 in the USA. That it carries all four
instruments itself is the expectation its class rests on, and it hangs on the same
retrieval as Japan's and India's; the size, by contrast, is measured and hangs on
nothing. That is not a statement of size but a statement about **counterforce 5**: its
damage is a quantity times a rate, and the quantity of the budget line is GDP. With the
order-of-magnitude test this draft already runs under *Offene Entwurfsfragen* — step
width 50 basis points, `gegenlobby_satz = 1`, that is, one point per 10.000 thousand
USD — the **same** instrument step generates about **5.300** counter-lobby points in the
USA and about **36** in Chile. The factor is 148 and is exactly the GDP ratio; the
calculation is an estimate only in the step width, not in the ratio. **The second
mandate half demands influence in two countries**, and whether the Lobby family can
field a winner for that at all has stood since 2026-09-03 as *„die schärfste
Kalibrierbedingung"* among the open questions. Chile answers it out of the
**construction** instead of out of the calibration: from here on there is a place where
influence is two orders of magnitude cheaper than in the USA — and because it is at the
same time the shallowest market, it is the most expensive place for capital. That is the
same trade as with the second layer, only with the signs swapped.

#### The nine side by side, in the quantities the model computes

Start year 2001. "largest share" is the largest of the three sector shares **after** the
normalisation to 10.000, that is, the number `sektorgewicht[b][s]` arises from.

| Country | GDP (bn USD) | Agri. | Ind. | Serv. | largest share | Trade (% GDP) |
|---|---:|---:|---:|---:|---:|---:|
| USA | 10.582 | 1,13 | 21,47 | 74,02 | **76,6** S | 22,97 |
| Japan | 4.439 | 1,27 | 31,34 | 67,33 | 67,4 S | **19,28** |
| Germany | 1.966 | 1,08 | 26,58 | 62,41 | 69,3 S | 59,56 |
| China | 1.355 | 13,82 | 44,28 | 41,90 | 44,3 I | 38,08 |
| Brazil | 560 | 4,80 | 22,64 | 57,71 | 67,8 S | 26,94 |
| India | 485 | **21,62** | 26,49 | 43,81 | 47,7 S | 25,99 |
| Saudi Arabia | 184 | 5,13 | **50,78** | 43,05 | 51,3 I | 63,56 |
| Singapore | 90 | **0,08** | 30,38 | 63,59 | 67,6 S | **349,29** |
| Chile | **72** | 4,06 | 28,48 | 55,65 | 63,1 S | 62,14 |

**Two spans that do not exist today, and both are mechanics and not colour.** The depth
of the markets the fund stands on orders itself by the country's capital stock —
`korbwert(l,s)` is capital stock times sector price, `schuld[l]` is GDP times debt
ratio — and the ordering of the countries is that of GDP. Today it spans from 560 to
10.582 billion, that is, over a factor of **19**; after 0118 from 72 to 10.582, over a
factor of **148**. Counterforce 3 (market narrowness) grows with the fund's share of the
market: on a scale across two orders of magnitude, "where am I big" is a decision; on
one across one, it is a constant. The second span is that of `durchgriff`, already
worked out above. **The numeric values of the capital stocks come from the PWT and not
from this table** — what stands here is the ordering, and only it carries the argument.

#### The class per country, and what it hangs on

The class is, per `technik.md` T61 rule 5, **not a choice but a derivation**: a country
is a play-only country exactly when any of its three policy-path series carries
`stufe = 4`. What stands here is therefore an **expectation with its condition**, as the
brief demands — it is decided at the retrieval per T63 step 1.

**What is the same for all nine and therefore decides no class:** series 13 (tariff
level) is locked for *every* country per `lizenzbefund-wdi.md`. The case is T26's first
case — no tariff path, constant tariff, two instead of three anchored instruments —; it
holds for today's four just the same, and a property all share distinguishes no one.

| Country | expected class | what it hangs on, and what tips it |
|---|---|---|
| **Japan** | backtest country | `MFS_IR` lists a policy rate for JPN at stage 1. If `JPN.*.A` comes up empty and no derivation without a free parameter is to be had, it is stage 4 and thus a play-only country. |
| **India** | backtest country | the same condition, one retrieval. |
| **Chile** | backtest country | the same condition, one retrieval. |
| **Singapore** | **play-only country** | Monetary policy is conducted there via the exchange rate, and the model has no instrument for the exchange rate. A bank rate is, per T60, not a policy rate, and the way from it to one would run via a spread — a free parameter, hence stage 4. **It becomes a backtest country** as soon as `MFS_IR` lists a policy rate for SGP at stage 1, or as soon as T60 stage 3 also carries a country whose interest rates are determined by world interest rates instead of by a nameable union. |
| **Saudi Arabia** | **play-only country** | Two independent reasons, and the second is the binding one. See below. |

**Singapore is the case T60 stage 3 is not meant for, and that needs saying, because the
objection suggests itself.** The MAS itself writes that domestic interest rates are
largely determined by world interest rates — that sounds exactly like stage 3, „kein
eigener geldpolitischer Hebel", and stage 3 would remain **backtest country**. The
objection still does not carry, namely at the derivation duty: stage 3 demands „welche
Union, ab welchem Jahr", because it applies stages 1 and 2 **to the union** instead of
to the country. Singapore has no answer to that — there is no union with a measured
rate, only "the world interest rates", and those are not a source but a circumlocution.
Add the sharper point: Singapore very much has a monetary-policy lever; it is just one
this model does not carry. **Stage 3 is built for a country without a lever, not for a
model without an instrument** — and the difference is not hair-splitting, it decides the
class.

**Saudi Arabia, reason 1 (can fall):** its policy rate follows the peg. Deriving it from
the US rate demands a distance, and a distance is a free parameter — per T60 thus not a
derivation but an estimate. But if `MFS_IR` lists a SAMA rate of its own at stage 1,
this reason falls away.

**Saudi Arabia, reason 2 (does not fall, and it lies not in the policy paths but in the
target series):** series 10 is **constant** for Saudi Arabia across all 21 support
points. Directional accuracy measures the share of transitions in which model and data
go in the same direction; over a constant series **every** one of the twenty transitions
carries direction zero, and an endogenously computed exchange rate hits the exact zero
practically never. The check subject *Wechselkurs SAU* would thereby break **by
construction and not from a model error** — the one case an oracle must never produce.
As a play-only country Saudi Arabia carries no target series, and the question does not
arise. **It becomes a backtest country** as soon as the model knows an exchange-rate peg
(the `wechselkurs[l]` of a pegged country is not written) *and* a policy rate at stage 1
is available.

**From this follows an addition to Maß 4, and it holds independently of Saudi Arabia:**
directional accuracy is formed only over the transitions in which the **target series**
moves. A transition without measured movement carries no direction and is not counted;
if a target series moves in no transition, the check subject has no directional accuracy
and passes on its level measure alone. That is not a new threshold but the closing of a
gap: the rule was so far written only for series with movement, and flat stretches exist
even without a peg.

**And a report to the architect, because it concerns their trade.** T61 rule 5 derives
the class **solely from the three policy-path series** and halts the vintage build when
the derivation contradicts the manifest. Reason 2 above is invisible to this rule — and
it is not the only one of its kind: T62 consequence 2 already names a second, the
missing fallback source for series 2. **Both are exclusions that lie in the target
series, and the class rule can see neither.** If `MFS_IR` lists a SAMA rate at stage 1,
rule 5 derives "backtest country", the manifest says "play-only country", and the build
aborts — correctly, because two bookkeepings diverge, but repaired in the wrong place.
That belongs to T61 and not here.

#### What nine countries count

Everything from `technik.md` T59, substituted for `L_R = 7`, `L_S = 2`, `n = 1`,
`S = 3`, `I = 4`; every number recomputed by hand once in this run and **not** copied
from the neighbouring row.

| Quantity | Formula | today (`L_R = 4`) | after 0118 (`L_R = 7`) | all nine in the backtest |
|---|---|---:|---:|---:|
| check subjects | `3·L_R + (L_R − n) + 1` | 16 | **28** | 36 |
| free target series | `L_R(S+3) − n` | 23 | **41** | 53 |
| target series | `L_R(S+4) − n` | 27 | **48** | 62 |
| flows in the trade block | `(L_R+1)·L_R·(S−1)` | 40 | **112** | 180 |
| target mask `weltlauf` | see T59 | 175 | **328** | 450 |
| tolerance of Maß 4 | `⌊L_R/2⌋` | 2 | **3** | 4 |

Recomputed in running text: check subjects `3·7 + (7−1) + 1 = 21 + 6 + 1 = 28`. Free
target series `7·6 − 1 = 41`, derived ones 7, together `7·7 − 1 = 48`. Flows
`8·7·2 = 112`. Target mask `7·27 + 22 + 112 + 2 + 3 = 328`. Tolerance `⌊7/2⌋ = 3`.

**Why the tolerance is a formula and not a number.** Were it to stay at 2, adding a
country would make the backtest **harder without a single rule of the model changing** —
a passed run could fail solely because someone adds a country. That is the same error as
a number that carries twelve others. `⌊L_R/2⌋` reproduces **exactly today's 2** at
`L_R = 4` — that is the compatibility test — and holds the share almost fixed
afterwards: 2 of 16 is 12,5 percent, 3 of 28 is 10,7, 4 of 36 is 11,1. It thus grows
more slowly than the number of subjects and never lowers the bar.

**What that costs in data, per T62.** A backtest country costs `32(R+1) + 6 = 678`
values at `R = 20`, a play-only country `5(R+1) + 33 = 138`. Three plus two gives
`3·678 + 2·138 = 2.034 + 276`, that is **2.310** values — against 3.390 if all five were
backtest countries, and 690 if all five were play-only countries. **The license
clarifications are independent of the class:** two per country, so ten new ones, which
per T62 consequence 3 belong on the same list as today's seven open ones. A cost, not a
gate.

#### The consequence of Weg A: what a player actually reaches of the board

**The operator chose Weg A on 2026-09-05** — the position slots grow with `L`, from 20
to 45, and with the exchange venues from package 0119 to **75**. Weg B (capped slots
with a selection mechanic) is thereby rejected, **and the justification for that is the
operator's decision, not a substantive one.** That belongs written down just so, lest
someone later search for a weighing that never happened.

What is open is the consequence, and it is to be computed, not asserted. Of the 75, the
USA's currency slot stays permanently empty per T16, so **74 are occupiable** (today 19
of 20). Slots are occupied **by action kind 1 alone**; lobby, leverage and visibility
occupy none, the stake has fields of its own. Under the stockpile procedure, kind `i`
gets exactly `12·ai` of the 60 slots over a full game — the allowance that *The game
length R* fixes at `R = 20`, and here it is what makes the calculation exact at all
instead of approximate.

| | today, 19 occupiable | after 0118/0119, 74 occupiable |
|---|---:|---:|
| reference profile `(1,1,1,1,1)`, 12 position actions | 12 of 19 = **63 %** | 12 of 74 = **16 %** |
| pure position profile `(5,0,0,0,0)`, 60 actions | 19 of 19 = **100 %**, every place a good three times | 60 of 74 = **81 %** |
| early window of Maß 3 (6 rounds, `a1 = 5`), 18 actions | 18 of 19 = **95 %** | 18 of 74 = **24 %** |

**The number falls hard: under the reference profile from 63 to 16 percent, that is, by
a factor of four.** The question is whether it falls below what the four Maße carry, and
the answer differs per Maß:

- **Maß 4 reads no slot.** The whole position block lies outside the target mask in the
  `weltlauf`. Untouched.
- **Maß 2 does not read the reference profile but each family's best profile.** Family
  1's best is `(5,0,0,0,0)` and reaches 81 percent of the board. The family's ceiling
  thus does not sink; what sinks is the reach of a profile that no acceptance half
  reads. Untouched.
- **Maß 3 compares two windows, and both stand under the same ceiling.** A bound that
  acts equally in both windows cannot shift one against the other. What shifts Maß 3 is
  the difference in the **kind** of place — early the shallow, unobserved venue market,
  late stake and lobby in policy countries — and the reach changes nothing about that.
  Untouched.
- **Maß 1 is the only one that reads the board directly**, and there two forces act
  against each other. *For* the density: the list of admissible actions grows with the
  board, two drawn bundles are more rarely the same bundle and more often of different
  kinds. *Against* the density: a step is a **share of that slot's market**, and
  `tiefe[b] = platzanteil · …` makes each of the 30 exchange venues shallower than any
  country×sector basket of the same anchor. **Forty percent of the board is thereby
  shallow by construction**, and an action on a shallow market moves the fund's assets
  less.

**The verdict, and it is a narrow one:** the coverage does not fall below what the four
Maße carry — three of the four do not read it at all. What falls is Maß 1's safety
margin, and which of the two forces above wins is decided not by the draft but by
`platzanteil` — and that has stood since 2026-09-05 as the sharpest open question of the
second layer anyway. So Weg A creates no new risk; it hangs an existing one higher.

**The one recommended dial: the action count per round, from three to four.** It is
recommended for the case, **not for now** — the condition stands two paragraphs on. Why
this one and not the two others the brief names:

- **The game length `R` is not free.** It is the length of the window in which every
  target series is covered without filling, and that is 2001–2021. Raising `R` demands
  data that, per the coverage finding, do not exist. **Ruled out, and from data, not
  from weighing.**
- **Merging venues would mean lowering `B`.** `B = 3·(L+1)` is a **count**, not a
  choice: a venue *is* the pair (territory, lead sector), each combination exactly once.
  Whoever lowers `B` takes away a territory's distinction by lead sector and reopens a
  package that is decided. **Not recommended.**
- **The action count is the only free one**, and the stockpile procedure survives it
  unchanged: with `vi += 4·ai` and still `−5` per action, kind `i` gets `4·ai` of 20
  slots per five rounds and `16·ai` of 80 over the game; after `5k` rounds the stockpile
  stands at `(0,0,0,0,0)` again, and `R = 20` remains a multiple of 5. The reference
  profile's reach would thereby rise from 16 to 22 percent, that of the pure position
  profile to saturation (80 actions on 74 places).

**And its price belongs with it, otherwise it is no recommendation.** Three is not an
arbitrary number: *„Drei, nicht beliebig viele — die Knappheit ist die Quelle der
Entscheidungsdichte. Wer alles tun kann, wählt nicht."* A fourth action loosens exactly
this scarcity by a third and costs the night run a third more world steps in Maß 2 and
Maß 3.

**Hence the condition, and it has a test that says whether to turn the dial.** It is
turned only if `Dichte(t)` falls below 0,4 in one third of the game **and** the dilution
is demonstrably the cause. The test already stands there and costs one additional run:
`Dichte(t)` at `B = 0` (board 45) against `B = 30` (board 75). **If the density holds
without the second layer and falls with it, the dilution is the cause and the action
count the remedy. If it falls in both cases, it is not down to the number of places, and
a fourth action does not help but conceals.**

#### What nine countries cost in the state

Computed from the constants in `kern/zustand.hpp`; the formula reproduces today's 310
exactly for `L = 4`. **The sum below is the country sum, that is, layers 1 and 3 — not
the state's total count.** That is, after the three layers, **890**: 740 plus
`5·B = 150` (*Die drei Schichten der Welt*). Two uncommented sums in one document are
the beginning of the next counting error, which is why it stands at both places.

| Block | `L = 4` | `L = 9` | |
|---|---:|---:|---|
| countries (44 per country) | 176 | 396 | 2,2× |
| trade `G·(G−1)·2` over `G = L+1` | 40 | **180** | **4,5×** |
| imitators | 12 | 27 | 2,2× |
| position slots | 20 | **45** | 2,2× |
| stakes | 24 | 54 | 2,2× |
| fixed (rest of world, fund, market, game …) | 38 | 38 | 1,0× |
| **country sum** | **310** | **740** | **2,4×** |
| exchange venues `5·B`, `B = 3·(L+1)` | (75) | **150** | |
| **state total after three layers** | (385) | **890** | |

The *countries* row works out at `9 · 58 = 522` once slots, stake fields and imitator
counters are added in (`396 + 45 + 54 + 27 = 522`) — the same 58 per policy country as
in the layer table. The two numbers in parentheses are computed for completeness and
never occur: at `L = 4` the second layer does not yet exist.

**The explosive charge remains the trade matrix**, and because of it nine is not a small
number: it grows with `G·(G−1)·2`, that is, four-and-a-half-fold, while everything else
merely about doubles. **The class separation does not defuse it** — it saves data and
checking effort, not addresses: a play-only country occupies its full country block and
its trade lines like any other. What it saves are the `112` instead of `180` flows the
**backtest** runs over.

#### What the choice decides on an open question

Since 2026-09-05 the question has stood open *„ob `3·(L+1)` die Länderwahl aus 0118
überlebt"* — it presupposes that every territory carries three distinguishable lead
sectors, and for a country with a strongly dominant sector structure the three venues
would lie close together under the `kippung` rule. **The choice decides it, and in the
formula's favour.**

The column *largest share* of the table above, descending: USA 76,6 — Germany 69,3 —
Brazil 67,8 — Singapore 67,6 — Japan 67,4 — Chile 63,1 — Saudi Arabia 51,3 — India
47,7 — China 44,3. **The most one-sided anchor of the nine is the USA, and they have
stood in the model since the first version.** No new country is more one-sided than a
current one; the two most balanced anchors of all are two of the five new ones, Saudi
Arabia and India. So the choice **improves** the binding case instead of sharpening it.

With that the question is not answered, but it has moved: whether `kippung` carries an
anchor's three venues apart is decided at the **USA** and not at one of the five new
ones — and the way out would remain, as it already says there, a different `kippung` and
not a different formula. **The case I looked for and did not find** would be a country
with a share near 100 percent; among the nine there is none.

### Welche drei Sektoren, und aus welcher Reihe jeder entsteht

| Model sector | WDI series | trade line | also contains |
|---|---|---|---|
| 1 agriculture | `NV.AGR.TOTL.ZS` (agriculture, forestry, fishing) | yes | — |
| 2 industry | `NV.IND.TOTL.ZS` (industry **including construction**) | yes | mining, manufacturing, construction, utilities |
| 3 services | `NV.SRV.TOTL.ZS` | no | — |

`NV.IND.MANF.ZS` (manufacturing) is **not** used. Thus every model sector has exactly
one source series, no part of value added disappears, and the twelve sector-share target
series remain true target series instead of model constructs.

**Two consequences, both named.** First: the three WDI shares do not sum to 100 percent,
because of taxes on products less subsidies. They are normalised to 10.000 in the
vintage, the normalisation stands in the manifest, and the backtest compares normalised
against normalised. The model thereby has no product-tax wedge; government revenue runs
via the budget balance, which is an instrument of its own anyway. Because the third
series per country is fixed by the normalisation, of the 27 target series **23 are
independent** — all 27 are disclosed nonetheless. (Until 2026-09-03 it was 31 and 27;
series 9 has not been a target series since, see *The game length R*.)

Second: Brazil's ore exports lie in sector 2 in the model, not in sector 1. „Brasilien
als Rohstoffexporteur" here means agricultural exporter. That is a loss of labelling and
not a loss of mechanics — the trade flow is the same, it just hangs on a different world
price.

### Keine verdeckte Größe

A design rule that holds everywhere: **every quantity that acts against the player is
readable in the state, together with its origin and its threshold.** The supervision
counter is visible, the imitator counter is visible, the counter-lobby budget is
visible. That is the direct answer to „the wealthy automatically hate me 100 % no matter
what": hostility here always has a counter, a reason and a distance to the next
threshold.

## Die drei Schichten der Welt

Until 2026-09-05 this design had **fused two axes into one**: where the player can move
policy, and where the fund can hold something. Both were `L = 4`. That made "more world"
look like "more countries at full price" — and a hedge fund that can hold something in only
four countries is no global hedge fund, however well the macro model underneath computes.
A real fund buys Japanese equities without bribing the Bank of Japan.

**The two axes are separated.** From here on the world has three layers.

### Die drei Schichten, mit ihren Feldern und ihren Rechten

| Layer | units | fields per unit | tradable | influenceable | in the backtest | trade row |
|---|---:|---:|---|---|---|---|
| **1 policy country** | 4, nine after 0118 | **58** = 44 + 5 slots + 6 stake fields + 3 imitator counters, plus its trade rows | yes | **yes** | **yes, if** it is a backtest country — since 0118 there are also play-only countries | yes |
| **2 exchange venue** | `B = 3·(L+1)`, at `L = 9` **30** | **4** + 1 slot | **yes** | **no** | **no** | **no** |
| **3 rest of world** | 1 | sector and aggregate quantities, no instruments | no | no | only in the trade block | yes |

**Why layer 1 exists:** It is the only place where a chain of effects *begins* — without
policy instruments there would be nothing to lobby and nothing whose consequence one could
explain. It is expensive, deep, and therefore scarce.

**Why layer 2 exists:** So that the investable universe can grow without the trade matrix
growing with it. An exchange venue is a **financial price, not an economy** — it has no
sectors, no capital stock, no employment, no public finances and no trade row. Exactly this
carries the difference between 890 and 87,788 fields.

**Why layer 3 exists:** It closes the circuit. Without it the sum of the trade balances
would necessarily be zero, which is false against the real data. All that is new from here
is that the rest of world becomes the **anchor territory of three exchange venues** — it
itself stays untradable and without instruments, but through these three venues the fund can
hold something that **no instrument in the world moves**. That is the only asset in the
model for which lobbying is of no help in principle, and it is therefore the touchstone for
the question of whether influence is worth anything at all.

### Was ein Börsenplatz trägt — vier Felder, jedes mit seinem Grund

A field without a reason is one address too many. So each field states what would break
without it.

| Field | class | start value | why it is an address and not a function |
|---|---|---|---|
| `index[b]` | 5 (index) | 10,000 | The venue needs a **memory of its own**, otherwise it is, every round, a snapshot of its anchor's sector prices — and two venues with a similar anchor would run in lockstep forever. Without this field the layer is decoration. |
| `wechselkurs[b]` | 5 (index) | 10,000 | **Without it an exchange venue is a linear combination of existing slots** — of its anchor's three sector baskets and that anchor's currency. This field and the next are the two that lift the venue out of the span of what already exists. |
| `zins[b]` | 3 (basis points) | `zielzins(b)` of the start year | The **discount channel** that no country×sector basket has: a basket is quantity times sector price, a venue is additionally discounted. Without it no interest-rate move separates venue from basket. |
| `nachahmer[b]` | integer, capped | 0 | **Counterforce 4 must reach the new layer.** Without this counter, 30 venues would be a hiding place from exactly the counterforce that carries Maß 3 — and the layer would make the game easier instead of richer. |

On top, **one position slot per venue** — "tradable" means exactly that and no more. So
**five addresses per exchange venue**.

**What an exchange venue expressly does not carry:** no policy instruments, no pressure, no
counter-pressure, no residual delay, no approval, no supervision counter, no influence, no
stake, no trade row, no target series. The stake is not missing out of thrift: by
*The actions* it is the only route to cheap lobbying, and a venue one could take a stake in
would be influenceable and thus no longer a venue but a cheap country.

### Woran ein Börsenplatz hängt, und was ihn eigenständig macht

An index that moves independently of everything is decoration; one that merely tags along is
a copy. Here is the coupling, as a computation rule and not as an adjective.

**Vintage constants per venue `b`** (not state addresses, just like `durchgriff` and
`leitzins_start`):

```
gebiet[b]           ∈ {1…L, Restwelt}        — das Ankergebiet
leitsektor[b]       ∈ {1, 2, 3}              — der Sektor, auf den der Platz gekippt ist
sektorgewicht[b][s] = normiert auf 10.000 aus sektoranteil[gebiet[b]][s],
                      der Anteil des leitsektor[b] mit (10.000 + kippung) gewichtet
tiefe[b]            = mal_geteilt( Σ_s mal_geteilt(kapitalstock[gebiet[b]][s],
                                                   sektorgewicht[b][s], 10.000),
                                   platzanteil, 10.000 )        — im Startjahr gebildet
zins_start[b]       = zielzins(b) des Startjahrs
```

**Functions of the state** (likewise not addresses, like `anleihekurs` and `landespreis`):

```
weltzins      = teile_gerundet( Σ_{l=1..L} kapitalstock[l] · leitzins[l],
                                Σ_{l=1..L} kapitalstock[l] )

zielzins(b)   = teile_gerundet( leitzins[gebiet[b]] + weltzins, 2 )   für ein Politikland
              = weltzins                                             für die Restwelt

zielkurs(b)   = teile_gerundet( wechselkurs[gebiet[b]] + 10.000, 2 )   für ein Politikland
              = 10.000                                                für die Restwelt

leitkurs(b)   = Σ_s mal_geteilt( sektorpreis[gebiet[b]][s], sektorgewicht[b][s], 10.000 )

zinsfaktor(b) = teile_gerundet( 10.000 · (zins_start[b] + aufschlag), zins[b] + aufschlag )

boersenwert(b) = wert( tiefe[b], index[b], b )
               = mal_geteilt( tiefe[b], index[b], wechselkurs[b] )
```

**Two special cases for the rest of world, both for the same reason.** It has no policy rate
and no exchange rate — it carries no policy instruments, and its aggregate quantities are a
residual. Its three venues therefore discount with the `weltzins` and quote in the
**numéraire** (`zielkurs = 10.000`). That is not a makeshift but the correct reading: a
basket that depicts the rest of the world has no currency of its own to set it against.
**Neither of the two formulas thus reads a rest-of-world address whose existence this design
cannot substantiate.**

**The write rule, exactly once per venue per round**, in step 4 (economy) — except
`nachahmer[b]`, which like every imitator counter is written in step 5:

```
zins[b]        ← teile_gerundet( zins[b]        + zielzins(b), 2 )
wechselkurs[b] ← teile_gerundet( wechselkurs[b] + zielkurs(b), 2 )
index[b]       ← teile_gerundet( mal_geteilt(leitkurs(b), zinsfaktor(b), 10.000)
                                 + index[b], 2 )
                 danach der Nachahmer- und der Stoßaufschlag nach denselben Regeln wie
                 beim Land×Sektor-Korb, mit nachahmer[b] und boersenwert(b) an der Stelle
                 von nachahmer[l][s] und korbwert(l,s)
```

**The five influences, enumerated rather than paraphrased.** What the price of a venue
depends on:

1. **The sector prices of its anchor territory**, weighted with `sektorgewicht[b]`. That is
   the pass-through of trade: a tariff step in any policy country moves the world price via
   market clearing, the world price moves the anchor's sector prices via `durchgriff`, and
   those move the venue. The chain the game sells thus reaches into the second layer.
2. **The policy rate of its anchor territory**, at half weight.
3. **The world rate**, the other half — the capital-stock-weighted mean of all `L` policy
   rates. An interest-rate step in country A thereby reaches **every** venue, including
   those anchored to B.
4. **The exchange rate of its anchor territory**, at half weight; the other half is the
   numéraire.
5. **The crowding** — imitators and the fund's own price shock.

**And what makes it stand on its own are three things, all three from rules and none from a
numeric value:**

- **The inertia.** `index[b]`, `zins[b]` and `wechselkurs[b]` move only **halfway** toward
  their target each round. A venue that has run up stays up, even when its anchor's
  fundamentals have already fallen back. That is the same price inertia that justifies
  `landespreis`, applied three times.
- **The mix.** A basket is one sector; a venue is all three with an emphasis. Spreading
  across venues is therefore something other than spreading across baskets — and spreading
  across venues **of different anchors** is something else again, because the third
  influence above — the `weltzins` — still couples them by half. **One cannot diversify
  completely, but one cannot fail to diversify entirely either.** That is exactly why
  diversification here is a decision and not a label.
- **The half peg to the numéraire.** In the steady state, the deviation of a venue quote
  from 10,000 is exactly half the deviation of its anchor currency — it swings half as far.
  The venue is thus the **quiet** way to hold a country — and the country's currency remains
  the loud one. Two slots, the same thesis, different risk.

**Four checks that work out without computation and that the vintage build can verify
mechanically:**

1. **In the start year the whole layer sits at its fixed point.** All sector prices start at
   10,000, so `leitkurs(b) = 10.000`; `zins[b] = zins_start[b] = zielzins(b)`, so
   `zinsfaktor(b) = 10.000`; all exchange rates start at 10,000, so
   `zielkurs(b) = 10.000`. All three halvings reproduce their own value, and
   `index[b] = 10.000` is the start condition, not a number that was set.
2. **The denominator of `zinsfaktor` never becomes zero.** `zins[b]` is a repeated mean of
   values none of which lies below the policy-rate floor `1 − aufschlag` — and that floor is
   already in the design, because of `anleihekurs`. So `zins[b] + aufschlag ≥ 1`. **The
   layer needs no new bound**; it inherits the existing one.
3. **The denominator of `boersenwert` never becomes zero.** `wechselkurs[b]` is a repeated
   mean of two strictly positive numbers and hence strictly positive — the same argument as
   for `wechselkurs[l]`.
4. **`index[b]` does not run away.** It is a mean of a fundamental value and itself, so it
   always lies between the running minimum and maximum of the fundamental value. The pure
   inertia share of a shock decays with `(1/2)^k`: after five rounds **3 percent** remains.

**Two new keys in `parameter.toml`, and not one more:** `kippung` (how strongly a venue is
tilted toward its lead sector) and `platzanteil` (what share of the anchor capital stock a
venue's depth is). `aufschlag` is **reused**, not doubled — a second markup would produce no
effect the first does not produce as well.

**Why these two numbers are parameters and the three halvings are literals:** a measure
reads them. `kippung` sets the distance between an anchor's three venues, and that is
precisely what Maß 2 measures; `platzanteil` sets how large the fund can become on a venue,
and Maß 3 measures that via the price shock. No measure reads the halvings — calibrating
them would give the search three axes whose effect `kippung` and `platzanteil` produce
anyway.

### Wie viele Plätze — und warum die Zahl eine Formel ist

**`B = 3 · (L + 1)`.** Per territory — the `L` policy countries and the rest of world — one
venue per lead sector. At `L = 9` that is **30**.

The number is not a choice but a count, and that is its virtue: a venue **is** the pair
`(Gebiet, Leitsektor)`. Every combination occurs exactly once, none twice.

- **Fewer — say one venue per territory, `B = L + 1 = 10`** — would leave the lead sector
  unexpressed. The venue would then be its anchor's mixture weighted by sector shares and
  nothing else, closer to a copy than this design can bear.
- **More — say two venues per cell, `B = 6·(L+1) = 60`** — would distinguish a cell's second
  venue from its first only by numeric values, no longer by kind. „Zwanzig Indizes,
  die dasselbe tun, sind ein Index", and it would cost 300 addresses instead of 150.
- **30 lies in the band 20–40** the work package prescribes, and it hits that band not by
  chance but because `3·(L+1)` lands there with the nine countries from 0118.

**What follows from this, and what expressly does not.** The formula fixes the **number**
and the **cut** of the venues — 30 cells, each with anchor territory and lead sector. Which
exchange venue by name sits in which cell it does **not** fix; that is a package of its own
and depends on the data situation. This section is that package's specification: 30 cells,
one name each, and per cell the check whether the chosen venue actually carries its cell's
lead sector.

**And the formula is the reason the layer does not stand in 0116's way:** it is written in
`L`, not in a digit. If 0116 makes the address arithmetic parametric, `5·B = 15·(L+1)` is
added as one more summand, and `L = 4` would give 75, `L = 9` gives 150.

### Was die Schicht kostet, und die drei verworfenen Wege

Computed from the constants in `kern/zustand.hpp`; the formula reproduces exactly today's
310 for `L = 4` and the 740 from package 0118 for `L = 9`.

| Path | policy countries | exchange venues | state | tradable slots | trade flows |
|---|---:|---:|---:|---:|---:|
| today | 4 | 0 | **310** | 20 | 40 |
| only more countries (0118) | 9 | 0 | 740 | 45 | 180 |
| **three layers — chosen** | 9 | **30** | **890** | **75** | **180** |
| the 30 venues as countries — rejected | 39 | 0 | 5,420 | 195 | **3,120** |
| all countries of the world — rejected | 195 | 0 | **87,788** | 975 | **76,440** |

**The explosive charge is the trade matrix.** It grows as `G·(G−1)·2` over `G = L + 1`
territories:

| policy countries | trade flows |
|---:|---:|
| 4 | 40 |
| 9 | 180 |
| 30 | 1,860 |
| 39 | 3,120 |
| 195 | **76,440** |

**The decisive number is not in the sum but in the ratio.** At the margin, an additional
policy country costs `44 + 40 + 3 + 5 + 6 = 98` fields for **five** tradable slots, so
roughly **20 fields per tradable slot**. An exchange venue costs **five** fields for **one**
slot. **Per tradable slot the venue is roughly four times cheaper than the country** — and
that is the whole justification of the layer, in one number.

**Rejected: all 195 countries of the world.** Not "later" — a different product.
**87,788 state fields, 76,440 trade flows and 195 × 19 = 3,705 licence-checked data
series** — package 0118 reckons 19 series and 2 licence points per additional country, which
here is 390 licence points. For comparison: this design carries 27 target series today. By
the count `4 · L_R` — four check subjects per backtest country — the backtest would have
**780** instead of sixteen (the same
formula that gives 16 for four countries; the symbol was corrected from `L` to `L_R` on
2026-09-06, because since package 0118 not every policy country is in the backtest — in this
rejected case it would be all 195, so `L_R = L` and the number unchanged),
market clearing would run over 76,440 flows instead of 40,
and the
runtime budget of the three self-play measures — today 9,539,200 world steps — would grow
with them. Whoever raises the question again finds the answer here instead of recomputing
it.

**Rejected: the 30 venues as full countries.** 5,420 fields instead of 890, 3,120 trade
flows instead of 180, and 30 × 19 additional data series — for the same 30 tradable slots.
What one would gain is that the venues could also be influenced; that is exactly what they
must not be, see below.

**Rejected: an exchange venue with a trade row.** It would then be not a second layer but a
cheap country — and the matrix would grow with `G²`, which is exactly the quantity the layer
exists to escape.

### Warum die Plätze handelbar sind und nicht beeinflussbar

This is not an economy measure but the statement the layer makes.

**An exchange venue feeds no supervision counter.** Counterforce 1 reads global visibility
times local footprint, and the footprint is influence times position share of the sector. On
a venue the fund has no influence and stands in no country's sector; its holding there
enters no counter. **The second layer is the place where the fund can grow large without
being watched.**

**And exactly for that reason it can never win there.** The mandate has two halves — wealth
**and** influence in at least two countries. Exchange venues deliver the first and **zero**
of the second. They are thus the same kind of object as the government bond, of which it
already stands written: *„Eine Zinswette ist ein Weg, Kapital aufzubauen, und nie ein Weg,
das Spiel zu gewinnen."* The second layer is the second such path, thirty times as wide.

**The fund can still move the venues — just not at the venues.** It lobbies an anchor's
policy rate and hits that anchor's three venues via `zielzins` and all thirty via
`weltzins`; it lobbies a tariff and, via the world price and `durchgriff`, hits its anchor's
sector prices and with them its `leitkurs`. **Effect yes, access no** — that is a sharper
statement than "uninfluenceable", and the more interesting one.

### Die Gegenkräfte auf der neuen Schicht

The five counterforces remain five. What changes is their reach, and that belongs written
out one by one, because a new surface without a counterforce is the fastest way back to the
feedback loop that kills this genre.

| Counterforce | reaches the second layer? | how |
|---|---|---|
| 1 supervision | **no, and that is decided** | No influence, no footprint, no counter. The price for this is the mandate. |
| 2 political backlash | indirectly | Via the anchor: a change of government resets its instruments, which moves `leitkurs` and `zielzins`. |
| 3 market thinness | **yes, and more strongly than in layer 1** | See below. |
| 4 imitators | **yes** | `nachahmer[b]`, the same rule as for the basket. |
| 5 counter-lobby | no | A venue has no instrument on which counter-pressure could form — the same argument as for the rest of world. |

**Counterforce 3 is the one that grows with success, and on the new layer it grows
faster.** Two mechanisms, both without a new rule:

- **Venues are shallower than countries.** `tiefe[b]` is a share `platzanteil` of the anchor
  capital stock, hence smaller than any country×sector basket of the same territory. The
  price shock from action 1 grows with the fund's share of the market — on a shallower
  market the same amount is a larger share. **The layer on which one can grow large
  unobserved is at the same time the one on which one's own size hurts fastest.**
- **The market basket gets broader.** The market return from counterforce 3 is the
  value-weighted return of **all tradable** baskets and bonds; the thirty venues belong to
  it, otherwise a tradable object outside the benchmark would be a gifted excess return. The
  bar the fund must clear thus rises with the layer — and "running broadly with the market"
  becomes even less viable than it was.

**Two counterforces thus bite on the new layer, both growing with success, and one expressly
does not.** That is the honest balance; it stands here so the break tester knows where to
look.

### Was die Schicht für die vier Maße bedeutet

**Maß 1 — decision density.** The tradable slots rise from 20 to **75**: 45 from the country
geometry at `L = 9` and 30 from this layer. The action count stays at three per round — the
operator chose path A on 2026-09-05, and the slots grow along. **The computation of how
decision density is preserved in this belongs in package 0118, and it must carry both
increases, not only the 45 from the countries.** The number it has to compute on is the 75
from this section, against today's 20. What belongs here and need not be repeated there:
each round Maß 1 draws 30 bundles from the list of **admissible actions**, and that list
grows with the slots. The open question *„Wie fein der Aktionsraum sein darf"* was so far to
be settled empirically on the prototype; with 75 slots it is **binding**, and its check form
is already there — `Dichte(t)` at `K = 30` against `K = 60`.

**Maß 2 — strategy diversity.** The 126 profiles remain 126: an exchange venue is a target
within family 1 (position), not a sixth action kind and not a fourth family. So the layer
enlarges the choice within **one** of the three families, and that is the objection one must
raise against it. **It does not hold, and the reason is the construction, not the
calibration:** venues deliver not a gram of influence, and the second half of the mandate
demands influence in two countries. Family 1 thus gets a higher ceiling for **capital** and
not a centimetre more toward the **win**. What the layer does genuinely shift is the second
acceptance half `max(Ek) ≤ 1,25 · min(Ek)` — from here on it is the sharp condition, and it
is the place where an oversized `platzanteil` calibration becomes visible.

**Maß 3 — shift of the optimum.** Here the design gains most, and at a spot where since
2026-09-03 it was openly declared weak. With the window 2001–2021 the euro transition
dropped away, the only lock that snapped shut during a game; since then Maß 3 rested on
**two** sources, imitators and the price shock, and this design has explicitly written down
that failing it would be a finding about those two. **The second layer is the third source,
and it comes from a rule rather than a number:** at the start of a game the fund has no
influence, so the unobserved, shallow, broad venue market is the efficient way to build
capital; toward the end of a game the second mandate half binds, and capital must be shifted
into stakes and lobbying pressure **in policy countries** — where it immediately wakes
supervision and the counter-lobby. That is a testable **prediction**, not a declaration of
intent: the early-window optimum `p*` should put weight on action kind 1, the late-window
optimum `q*` on 2 and 3. If it does not come true, that is a finding about this section.

**Maß 4 — backtest.** **Through this layer** it does **not** change, in any of its numbers.
*Corrected on 2026-09-06, because 0117 has since been built and the sentence no longer held
as it stood:* an exchange venue is **not a play-only country** — by T58 a play-only country
is a country with policy paths that may be estimated, and a venue has none at all. It simply
carries no target series and no trade row and appears in no check subject; the argument
below — *the layer is a pure leaf* — carries that on its own and does not need the class
assignment. So the sharpness of the backtest does not sink through the layer: it keeps
running over the same free target series and the same trade block, for a venue has no trade
row. **What does move it is the country choice from package 0118** — there the free target
series rise from 23 to 41, the check subjects from 16 to 28 and the flows of the trade block
from 40 to 112. That is the other axis and stands under *Welche neun
Länder*. Added to this is a property that is stronger than the class assignment and carries
it independently of it: **the layer is a pure leaf.** No field of the first or third layer
reads a field of an exchange venue; venue fields are read exclusively by the fund subsystem.
Since that subsystem does not run in the `weltlauf`, the second layer is **not computed at
all** there — its four fields per venue keep their start values, just as the fund block and
the imitator counters already do. After this layer the `weltlauf` costs not one world step
more than before, and the set of addresses written per mode stays fixed. The price of this
cleanliness belongs with it and stands under *And the limit of the oracle, explicitly*: for
the second layer the oracle is completely blind. There is also nothing of it to check
against — a world equity index under a free licence does not exist, that already stands
under *Was bewusst fehlt*, and `daten.md` carries not a single price series.

### Die drei Klagen, auf dieser Schicht gelesen

| Complaint from the reviews | what the second layer contributes to it |
|---|---|
| „the consequences of choices often feel intangible" | The coupling is a formula the player can trace along the chain: tariff step → world price → `durchgriff` → the anchor's sector price → `leitkurs` → `index[b]`. An action in one country visibly moves a price thirty slots away — and because `weltzins` reaches every venue, an interest-rate step has an effect one can read off **worldwide**, without anything being narrated. |
| „trying to implement the tiniest socialist policy will always result in bankruptcy" | On every venue, long and short are the same formula with the sign reversed. The layer brings no political direction with it; it cannot win in any direction on its own, because it delivers zero influence. It thus broadens the position family without rewarding any political line. |
| „no dramatic setbacks", „broad as an ocean, but deep as a puddle" | The layer is exactly the breadth the complaint misses — and it comes with a trap instead of being free: whoever grows large on the shallow venues moves the price against themselves, gathers imitators and at the same time raises the bar of the market basket on which their investor base hangs. The setback is mechanical and readable in the state, like every other one here. |

## Die Gegenkraefte

Five, each grows with success, each as a mechanism and not as an intention.

**1. Supervision.** Per country one counter that rises every round by an amount
following from global visibility times local footprint (influence times position share
in the sector) — **not from wealth alone**, or it would be nothing but a wealth tax.
Three thresholds: at the first, the instrument „Finanzmarktregulierung" moves against
the fund, independently of the fund's lobby budget and with precedence over it. At the
second, the stake is force-sold, at a discount. At the third, a market ban holds in that
country for several rounds. Grows with success, because influence and share are exactly
what the mandate demands.

**2. Political backlash via real income.** Every lobby action pushed through shifts
prices and with them real income. If real income falls, approval falls; below a
threshold the government changes, the new one resets **all** instruments toward their
historical mean and doubles the fund's lobby costs for several rounds. Grows with
success, because successful lobbying produces exactly the shift that lowers approval.
That is the idea's chain of effect, closed here into a circle instead of an arrow.
**Which number this real income is stands in the section *Das Realeinkommen in Gegenkraft
2*.** Until 2026-09-07 only the adjective stood here, and a quantity that „sinkt", without
its formation rule being written anywhere, is not a chain of effect but an arrow — the
same defect counterforce 5 was freed from on 2026-09-02, and the reason package `0197`
could not be built.

**3. Market thinness.** The fund lives on investor money, and investors compare its
return with a market return. That market return is the **value-weighted return of all
baskets and bonds tradable in the model, at model market values** — weighted by the
market, **not by the fund's holdings**. It has no data anchor of its own; its start
value is the value of the start basket at start prices, its continuation is model
(`technik.md` T33).

The power of this counterforce lies **in the price shock, not in the definition of the
benchmark**: the larger the fund's share of a market, the more strongly every entry and
exit moves the price against it, the more expensive every reallocation becomes. If the
excess return stays below zero for three rounds, a fixed share of investors withdraws,
forcing sales into a market the fund itself moves.

**And the way out belongs to it, or this would be no counterforce but a death sentence
on size:** the fund beats a broad market through **concentration and causation** — stake
and lobbying raise the value of *its* baskets more than the market average. Whoever
merely runs along broadly loses against their own cost threshold; whoever shifts the
fundamentals of their position also wins big. Exactly that is the link between the two
halves of the mandate.

**4. Imitators.** For every position that yields excess return over several rounds, an
imitator counter rises on that country×sector. Imitator capital enters as a
counter-position, raises the entry price and lowers the future return of the same
position. Every working strategy is thereby **self-consuming**. That is not balance,
that is the rule Maß 3 enforces: what was optimal in the first third is grazed bare in
the last.

**5. Counter-lobby.** Influence is relative to the sum of all lobby pressure on an
instrument. Whoever pushes something through damages another sector — and that sector's
counter-budget grows by `gegenlobby_satz` lobby points per 10.000 thousand USD of damage
suffered. The more strongly one shifts in a direction, the more expensive the next step
in the same direction becomes. The feedback that runs upward in the genre runs against
itself here. **Which number this damage is stands in the next section.** Until
2026-09-02 only the adjective stood here, and a counter-budget that grows „proportional
zu" something, without the quantity being named, is not a counterforce but an intention
— exactly the kind of sentence the head of this section stands against.

### Der Schaden in Gegenkraft 5, als Rechenvorschrift

`technik.md` T50 fixed the **unit** of the damage — economy-wide, thousand USD, scale
class 2, transition into lobby points via
`lobbypunkte_aus_schaden(tsd) = mal_geteilt(tsd, gegenlobby_satz, 10.000)` — and expressly
handed the **magnitude** back here, with the right reasoning: had the architect filled the
gap, Maß 2 would be measuring the architect's choice. It is filled here.

#### Die eine Regel

> **The damage of an instrument is the shift of the price it sets, times the quantity
> that price acts on — both measured at the round boundary.**

Four instruments, four prices, four quantities, one computational form. **„The price it
sets" is, for the tariff, the wedge and not the sector price** — the sector price arises
from world price, wedge and price inertia, and only the wedge has the instrument as its
cause. Since 2026-09-03 the tariff row therefore measures the wedge; the reasoning
stands two sections further down.

For each of the four countries `l` and each of its four instruments `i`:

```
schaden(l, i) = mal_geteilt( menge(l, i), verschiebung(l, i), 10.000 )      [Klasse 2]
```

The building blocks, all from the state and the vintage, none of them a new address:

```
hub(l, i)           = | lies_neu(land.<l>.instrument.<i>.stand)
                      − lies_alt(land.<l>.instrument.<i>.stand) |

keilhub(l, s)       = mal_geteilt( lies_neu(welt.preis.<s>), hub(l, zoll), 10.000 )

preishub_zoll(l, s) = mal_geteilt( keilhub(l, s), durchgriff(l, s), 10.000 )

handelsvolumen(l,s) = Σ über die vier Gegenüber g:
                        lies_neu(handel.<l>.<g>.<s>) + lies_neu(handel.<g>.<l>.<s>)

bip(l)              = Σ über die drei Sektoren  lies_neu(land.<l>.sektor.<s>.wertschoepfung)
schuld(l)           = mal_geteilt( bip(l), lies_neu(land.<l>.staatsschuld), 10.000 )
```

`bip` and `schuld` are numbers 9 and 10 from `technik.md` T48, taken over unchanged.
`handelsvolumen(l, s)` is the sector-wise version of number 11; its sum over the two
tradable sectors is the old quantity. None of these names is a state address — they are
functions of the state, the same construction as `korbwert` in the section *What a basket
is worth*. `durchgriff(l, s)` is not a state quantity but one of the fourteen
**vintage constants** (`technik.md` T23 point 5), fixed over the game.

**`keilhub` and `preishub_zoll` are new since 2026-09-03 and replace `preishub`.** The
previous version read the full shift of the sector price; why that was the wrong quantity
and why this one is right stands under *Warum die Zollzeile nur den Keil misst*.

Thus the four rows:

| Instrument | `verschiebung(l, i)` | Class | `menge(l, i)` | `schaden(l, i)` |
|---|---|---:|---|---|
| `zoll` | `preishub_zoll(l, s)`, per tradable sector separately | 5 | `handelsvolumen(l, s)` | `Σ` over s ∈ {1, 2}: `mal_geteilt(handelsvolumen(l,s), preishub_zoll(l,s), 10.000)` |
| `leitzins` | `hub(l, leitzins)` | 3 | `schuld(l)` | `mal_geteilt(schuld(l), hub(l,leitzins), 10.000)` |
| `haushalt` | `hub(l, haushalt)` | 3 | `bip(l)` | `mal_geteilt(bip(l), hub(l,haushalt), 10.000)` |
| `regulierung` | `hub(l, regulierung) · regulierung_last` | 10 × 3 | `bip(l)` | `mal_geteilt(bip(l), hub(l,regulierung) · regulierung_last, 10.000)` |

The third sector contributes zero in the tariff row because it has neither a trade row
nor a world price and carries `durchgriff = 0` per T28 — three reasons, each sufficient
on its own; whether one sums over two or over three sectors does not change the number.
`welt.preis.<s>` exists only for s ∈ {1, 2} anyway.

#### Warum die Zollzeile nur den Keil misst

**The decision, in one sentence:** of the shift of the sector price, **only the part the
tariff step caused** counts as damage — the rest is business cycle and does not belong
in a counterforce.

Until 2026-09-03 the full shift stood here, and that was wrong. The proof is two lines
long and comes from the price-formation rule above:

```
preis_neu − preis_alt = durchgriff/10.000 · ( weltpreis_mit_zoll_neu − preis_alt )
```

The bracketed expression splits into two summands, and only the first has a causer:

```
weltpreis_mit_zoll_neu − preis_alt
    = welt.preis_neu · (zoll_neu − zoll_alt)/10.000        ← der Zollkeilanteil
    + ( welt.preis_neu · (10.000 + zoll_alt)/10.000 − preis_alt )   ← der Sockel
```

The second summand is exactly the shift that would have occurred **had the tariff level
not moved**. By the price-inertia rule above („domestic price follows the world price
with a one-year lag") it is nonzero by construction, in every round, without any action.

**The old quantity was the absolute value of the sum, the new one is the absolute value
of the first summand**, both times `durchgriff/10.000`. The difference is therefore not
a damping but a deletion: what falls away is the summand without a causer, and what
stays, stays unchanged.

**What the base term really is: inflation, times the trade volume.** `handelsvolumen`
stands per T5 in class 2 at constant prices, `preishub` was a nominal index — their
product is the nominal appreciation of the trade flow and thus, at its core, the
country's annual sector-price increase. Before this change, the tariff row **measured
inflation** and booked it as lobby damage.

**Three reasons, and the first alone suffices.**

1. **It hits Maß 2 at its most sensitive spot, and no calibration brings it back.** The
   family Lobby is the only one of the three whose counterforce is exclusively
   counterforce 5. A base term that arises without action is the same for every profile
   and avoidable for none — it pulls the baseline out from under exactly one of the
   three classes. `gegenlobby_satz` does not help, because it scales base term and
   action response together; whoever halves the base term halves the response with it.
   And influence is the fund's **share** of total lobby pressure, so an exogenously fed
   counter-pressure shifts that share permanently. The acceptance of Maß 2 reads
   `max(Ek) ≤ 1,25 × min(Ek)` over the three classes; a handicap that exactly one class
   carries and that grows with the price level over the game is the most obvious way to
   tear it — and it would fail not on a number but on the construction.
2. **It stands against this section's own reasoning.** The value-added loss is rejected
   below with the sentence: *„It is business cycle, not reaction … without a single
   lobby action having taken place."* The tariff row had the same property, and there it
   was not the exception but the rule. Treating two quantities with the same property
   differently is not design but an oversight.
3. **It makes the setback inexplicable, and that is the first of the three complaints.**
   Step 1 shows the previous round's chain. Under the old rule it read: *counter-pressure
   on the German tariff instrument +6.570, cause: damage 32.850.000 Tsd USD, cause: the
   sector price moved* — and behind that stands no action but the world market. Exactly
   that is what "the consequences of choices often feel intangible" means: not that too
   little happens, but that what happens does not hang on the player. The design
   promises in its title that every number says why it moves. The base term could not.

**And the side effect is the second piece of evidence that the old quantity was the
wrong one.** `technik.md` T8 rebases a country's three sector prices under hyperinflation
(division by 1.000), but `welt.preis.<s>` not — it hangs on no territory. A difference
`preis_neu − preis_alt` across such a rebasing is not the price shift but the base
change; it would have silently pushed the affected country's counter-pressure to
`druck_max`. That a difference needs this, the architect already knows: T42 computes
exactly this correction out for the backtest. The damage rule did not have it. In the
check vintage 2001 the case never occurs — in the play vintages before 2001, which this
design expressly retains, it does. **The new version differences only the tariff level
(class 3, never rebased) and reads the world price as a level; T8 cannot hit it.**

#### Die beiden anderen Wege, und warum sie es nicht sind

**Way 2 — read `hub(l, zoll)` like the three other rows.** It is cheaper and also
removes the base term. It fails in two places.

First, it makes the row blind to the sector effect. `schaden(l, zoll)` would then be
`mal_geteilt(handelsvolumen(l), hub(l,zoll), 10.000)` and would hang on the country
alone. But in the section *What must hold for price formation* the design justifies the
ordering `durchgriff` establishes: *„a tariff hits China's industry hard via its high
`durchgriff` and the US industry, dominated by construction and utilities, weakly"*.
Under way 2 it hits both equally hard per unit of trade volume. That is the same
self-contradiction as under 2 above, only in the other direction.

Second, it confuses a rate with a price. A tariff rate is not a price but a wedge; what
the buyer pays is the sector price. The policy rate, by contrast, **is** the price of
money, the fiscal balance **is** the share of output, and the regulation step becomes
such a share via its load rate. This distinction already stood in the version of
2026-09-02 and holds unchanged — it is the reason the tariff row **converts** the tariff
level instead of inserting it. Exactly that is what `keilhub` does: it translates a rate
in basis points at the world-price level into a shift in index points, and only
`durchgriff` lets through what arrives domestically.

**Way 3 — keep the base term and write it down.** It fails on reason 1: a written-down
construction error remains one. The base term is nothing calibration could still turn,
and it would also be harmful for Maß 3, not merely inconsequential: it grows with the
nominal price level over the game, so it systematically makes the family Lobby more
expensive in the last third of the game — a shift of the optimum that would arise **even
with the fund switched off**. Maß 3 would then have reached its threshold with a drift
of the world instead of a property of the game. A measure that can be worked like that
no longer measures.

#### Was die Entscheidung kostet, und was sie nicht kostet

**It does not cost:** a new state address (`welt.preis.1` and `welt.preis.2` are numbers
239 and 240 in `daten/adressen.md`), a new series, a fourth scale transition, a ninth
channel or a second market clearing. And it costs **nothing in signal**: the action
share of the damage is the same as before, only the base term falls away. The
decomposition above is algebraically exact, not approximate; only the rounding paths
differ — the old row rounded once into the stored sector price and once into the damage,
the new one twice between world price and damage. A difference of a few index points, no
difference in order of magnitude.

**It costs:** the damage a *foreign* tariff does domestically. A German industrial
sector hit by an American tariff step via the world price no longer generates
counter-pressure in Germany, because `hub(DE, zoll)` is zero. That stands under *Was
bewusst fehlt*.

**Corrected on 2026-09-07, and the correction belongs to this decision.** This paragraph
promised the effect was „not severed but rerouted" — via the German sector price, real
income, approval and a change of government. **That reroute does not exist.** Once real
income was written down as a rule (*Das Realeinkommen in Gegenkraft 2*), it read the
burden of the country's **own** instrument steps, for the same reason this section
rejected the base term: the world-price share of a tariff step has no causer that can be
isolated without a second market clearing. `politiklast(DE)` is therefore zero as well,
and the foreign tariff step reaches German politics in no round. What remains of it is
economic and not political: it moves the German sector price, the trade volumes and, via
channel 1, the capital stock of the following round. The loss stands under *Was bewusst
fehlt* with its reason; a promise that two rules kept apart could not have kept is worth
less than the consistency of the two.

**One condition that follows from this and that the vintage build must check.**
`preishub_zoll` arises from two roundings. If the smallest possible tariff step is too
small, the row rounds to zero for a country×sector pair, and the counterforce is **mute
there without saying so**. What must hold, as a form and without a number:

```
mal_geteilt( mal_geteilt(welt.preis_start(s), schrittweite[zoll], 10.000),
             durchgriff(l, s), 10.000 )  ≥  1     für jedes Land×Sektor des Jahrgangs
```

The value of `schrittweite[zoll]` that satisfies this is calibration and does not stand
here; that the condition is checked is design and stands here.

#### Zwei Zustände, zwei Zahlen

The same probe as in package 0021, now on the row that had none there. The two states
differ in **exactly one** quantity, the tariff level.

| Quantity | State A (one tariff step) | State B (no action) |
|---|---:|---:|
| `handelsvolumen(DE,1)` / `(DE,2)` (Tsd USD) | 40.000.000 / 100.000.000 | the same |
| `durchgriff(DE,1)` / `(DE,2)` (vintage) | 7.288 / 5.464 | the same |
| `lies_neu(welt.preis.1)` / `(welt.preis.2)` | 11.000 / 10.400 | the same |
| `…instrument.zoll.stand`, `lies_alt` → `lies_neu` | 380 → 430 bp | 380 → 380 bp |
| `lies_alt(…sektor.1.preis)` / `(…sektor.2.preis)` — only the previous version reads it | 10.000 / 10.000 | the same |
| `hub(DE, zoll)` | 50 | **0** |
| `keilhub(DE,1)` / `(DE,2)` | 55 / 52 | 0 / 0 |
| `preishub_zoll(DE,1)` / `(DE,2)` | 40 / 28 | 0 / 0 |
| Contribution sector 1 / sector 2 | 160.000 / 280.000 | 0 / 0 |
| **`schaden(DE, zoll)`** | **440.000** | **0** |

Recomputed with `mal_geteilt` and the rounding rule from T6 (halves away from zero):
`11.000 · 50 / 10.000 = 55` exactly; `7.288 · 55 / 10.000 = 40,084 → 40`;
`5.464 · 52 / 10.000 = 28,4128 → 28`; `40.000.000 · 40 / 10.000 = 160.000`;
`100.000.000 · 28 / 10.000 = 280.000`.

**The row `lies_alt(…sektor.<s>.preis)` enters no number in the columns below it.** It
stands only for the comparison at the end of this section: the current tariff row no
longer reads `land.<l>.sektor.<s>.preis` — that is the decision —, the previous version
read it as its only state input. Its value is the start value of the price-inertia rule
above, hence round 1.

**State B is the acceptance, and it can be recomputed without any knowledge of the wedge
form.** If the tariff level does not move, `hub` is zero, hence `keilhub` zero, hence
`preishub_zoll` zero and hence `schaden(l, zoll)` **exactly zero** — for every world
price, every price inertia and every trade volume. For comparison, the same row in the
**previous version**, applied to the same state B and computed solely from the
quantities in the table above, with `mal_geteilt` and the rounding rule from T6:

```
wmz(DE,1)      = 11.000 · (10.000 + 380) / 10.000              = 11.418
preishub(DE,1) = |11.418 − 10.000| · 7.288 / 10.000 = 1.033,4384 →  1.033
Beitrag 1      = 40.000.000 · 1.033 / 10.000                   =  4.132.000
wmz(DE,2)      = 10.400 · (10.000 + 380) / 10.000 = 10.795,2   → 10.795
preishub(DE,2) = |10.795 − 10.000| · 5.464 / 10.000 =   434,388 →    434
Beitrag 2      = 100.000.000 · 434 / 10.000                    =  4.340.000
                                                     Summe     =  8.472.000
```

**8.472.000 instead of zero**, and that is more than **nineteen times** what the
deliberately taken tariff step in state A generates (440.000). Exactly this quantity
falls away with the decision, and it accrued without action, in every round and equally
for every profile. The only rounding one could place differently here is the
intermediate value `10.795,2`; it decides nothing — carried on unrounded,
`795,2 · 5.464 / 10.000 = 434,49728 → 434`, the same number.

**With this, the same sentence holds for all four rows**, and that is the real effect of
this decision: *the damage of an instrument is nonzero exactly when the instrument moved
in this round.* Before, it held for three of four.

That an instrument can move without a player action remains possible — a change of
government resets all four. That is no exception to the sentence but the same chain one
step later, and it hits all four rows equally; see *Does it grow with success?*.

#### Wer geschädigt wird, und an welche der 16 Adressen es fließt

| Instrument | who bears the damage | why this quantity |
|---|---|---|
| `zoll` | the country's two tradable sectors and their counterparts in trade, on the import as on the export side | the wedge acts on the goods that cross the border — hence the trade flow in both directions, and hence only the shift the wedge itself generates |
| `leitzins` | the state as debtor and, via its budget, all three sectors | the interest is paid on the debt stock, not on output |
| `haushalt` | the recipients of government services, i.e. all three sectors by value-added share | the balance stands in basis points **of GDP**; the quantity is therefore GDP |
| `regulierung` | the financial trade in sector 3 and, via capital costs, the rest | the state carries no financial sector; GDP is the coarsest honest quantity |

**The assignment in one sentence:** the damage is computed **per country from that
country's quantities** and settles on the instruments of the **same** country —
`land.<l>.instrument.<i>.gegendruck`, four countries times four instruments, the sixteen
addresses. Every single one is thereby derivable: whoever opens
`land.BR.instrument.leitzins.gegendruck` computes
`mal_geteilt(schuld(BR), hub(BR, leitzins), 10.000)` and then `lobbypunkte_aus_schaden`
on it.

**The rule behind it stays: a counter-lobby forms where it can act**, at its own
legislator and not at the foreign one. What it achieves there is resistance against
movement, not retaliation — see *Was bewusst fehlt*.

**Since 2026-09-03, however, this rule holds for the tariff only for the own step.**
Until then the tariff row also carried the damage a *foreign* tariff did domestically
via the world price; with the base term it falls away, for it hangs on the world price
and not on the own wedge. Bringing it back would mean isolating the general-equilibrium
share of a tariff step, and that takes a **second market clearing** per round — the
model's most expensive computation once more, for a state that does not exist. It
therefore stands under *Was bewusst fehlt*, with the path by which it arrives anyway.

#### Wie das Gegenbudget wächst und wieder vergeht

In step 5, for all sixteen addresses, exactly once per round:

```
gegendruck_neu(l, i) = min( druck_max,
                            teile_gerundet( lies_alt(land.<l>.instrument.<i>.gegendruck), 2 )
                            + lobbypunkte_aus_schaden( schaden(l, i) ) )
```

**The halving is a rule and not a calibration number**, and that is a decision against
an obvious parameter. A decay rate next to `gegenlobby_satz` would be exactly redundant
for the steady state: under constant damage `D` the counter-pressure runs toward
`2 · lobbypunkte_aus_schaden(D)`, and a free rate would only shift which of the two
numbers carries that value. The two would differ only in the transient — a calibration
dimension that shapes nothing but the transition costs the night run over a thousand
parameter sets a whole axis and gains nothing on any Maß. The statement of the halving
is substantive and checkable: *an opponent that goes one round without new damage loses
half its budget.*

**A counter-pressure without decay would be no decay but an end state.** It would run
toward `druck_max` in every country the fund touches and stay there; the strategy family
Lobby could move nothing in the last third of the game, and Maß 2 would fail not on a
calibration but on the construction. Conversely, a pure inflow without carry-over would
be too mild: whoever alternates lobbying with something else would meet a
counter-pressure of zero every second time. The halving is the smallest version that
avoids both.

#### Warum diese Lesart und nicht die beiden anderen

`technik.md` section 12 names three: **price shift times quantity**, **value-added
loss**, **valuation loss**. Chosen is the first, and the other two do not fail on taste.

**The value-added loss** — `wertschoepfung_alt − wertschoepfung_neu` — is the simpler
formula and the wrong quantity, for three reasons, of which the first suffices:

1. **It is blind to the tariff.** Class 2 stands per T5 in *Tausend USD zu konstanten
   Preisen des Basisjahrs*. Value added is thus a **real** quantity; a tariff shifts
   prices, not real quantities — at least not in the same round, for the real path runs
   via investment and capital stock and is channel 1. The tariff is the only instrument
   channel 3 names at all, and the only one with a data anchor in the trade block. A
   damage quantity that does not see it measures the wrong chain.
2. **It is business cycle, not reaction.** In a growth year it is zero for all twelve
   country×sector pairs, in the slump year 2008 or 2020 large for all twelve at once —
   without a single lobby action having taken place. Counterforce 5 would then be no
   force that *grows with success* but business-cycle noise with lobby effect, and the
   requirement from the head of this section would be missed.
3. **It cannot be assigned to any instrument.** One difference, four instruments: any
   split across the sixteen addresses would be invented.

**And the sentence that points at Maß 2:** the family Lobby is the only one of the three
whose counterforce is exclusively counterforce 5 — Position is braked by price shock and
imitators, Stake by supervision and illiquidity. A counterforce that does not answer the
player's action is none for this family, and the family without a price dominates. Maß 2
demands `max(Ek) ≤ 1,25 × min(Ek)` over the three classes; that is the same defect the
review describes from the other side as „trying to implement the tiniest socialist
policy will always result in bankruptcy", and here it falls in the other direction.

**The valuation loss** fails twice, and the first reason is the heavier one:

1. **It is a fund quantity and would couple the counterforce to failure.** If the fund
   loses, the counter-lobby grows; if it wins, it vanishes. That is the inversion of
   what a counterforce of this design must do, and it would not damp channel 8 but
   amplify it.
2. **It costs a fourth scale transition.** It stands in class 1 (US cents),
   `cent_in_tsd` expressly does not exist per T50, and retrofitting an inverse function
   is an ADR against T50 and not a sentence in `spiel.md`.

If one instead reads "valuation loss" as the change of the **sector basket** —
`korbwert(l,s)`, class 2, hence admissible under the scale rules —, then it is almost
the chosen rule, with `kapitalstock` instead of `handelsvolumen` as the quantity and an
additional term for the capital-stock change. Exactly that term is the objection: it
belongs to channel 1 and would be booked a second time in channel 3. The trade flow is
the quantity the tariff wedge touches; the capital stock is not.

#### Wo die Regel läuft, und warum Kanal 3 zyklenfrei bleibt

Computed in **step 5**, the place T50 fixes as the only call site of
`lobbypunkte_aus_schaden` — sixteen calls per round, all here. Read:

| from where | addresses | count | for which row |
|---|---|---:|---|
| step 3 | `lies_neu(land.<l>.instrument.<i>.stand)` | 16 | all four |
| step 4 | `lies_neu(welt.preis.<s>)`, s ∈ {1, 2} | 2 | `zoll` |
| step 4 | `lies_neu(handel.<a>.<b>.<s>)`, the whole trade block | 40 | `zoll` |
| step 4 | `lies_neu(land.<l>.sektor.<s>.wertschoepfung)`, for `bip` | 12 | `leitzins`, `haushalt`, `regulierung` |
| step 4 | `lies_neu(land.<l>.staatsschuld)`, for `schuld` | 4 | `leitzins` |
| previous round | `lies_alt(land.<l>.instrument.<i>.stand)` | 16 | all four |
| previous round | `lies_alt(land.<l>.instrument.<i>.gegendruck)` | 16 | all four |

`16 + 2 + 40 + 12 + 4 + 16 + 16 =` **106 read accesses**, 16 write accesses, **no new
address**. Counted are distinct addresses, not access events — the trade block therefore
stands at 40 and not 64, because a flow between two playable countries enters two
`handelsvolumen`. Every quantity read stands in `daten/adressen.md`, `welt.preis.1` and
`welt.preis.2` as numbers 239 and 240; `bip`, `schuld` and `handelsvolumen` are
functions of them and not fields, `durchgriff` is a vintage constant. The number 310
stays, and the counting step from T45 still comes out unchanged.

**The number has been wrong twice, and the correction belongs to the decision.** The
version of 2026-09-02 named 120 and counted the tariff level twice with 16, although the
tariff row did not read it at all back then — check finding 2 found that and computed
112. After this decision the tariff reads its level again, in exchange both sector-price
rows (`lies_neu` and `lies_alt`, 8 each) fall away without replacement and the two world
prices are added: `112 + 4 + 4 − 8 − 8 + 2 = 106`. Both numbers of the previous versions
are thereby superseded, and the catch-up table at the end names the same 106.

**The round boundary is the solution, not a second set of addresses.** A damage that
compared the state before the instrument step with the one after would need shadow
addresses; the comparison of `lies_neu` against `lies_alt` needs none, because the
writer keeps both levels anyway per T39.

**Channel 3, walked through:** instrument (step 3, `stand`) → trade (step 4, `handel`) →
world price (step 4, market clearing) → damage (step 5, here) →
counter-lobby budget (step 5, `gegendruck`) → instrument (step 3 of the **following
round**). Exactly one round boundary is crossed, and it is not promised but enforced:
step 3 must read `lies_alt(gegendruck)`, because the address is not yet written in this
round and `lies_neu` on it would be a hard error per T39. The damping „counter-pressure
acts only in the following round" is thereby a property every run proves.

**`welt.preis.<s>` is read but not differenced, and the difference is the whole point.**
The previous version excluded the world price with the argument that it is the same for
all territories and cannot distinguish who was hit. The argument still holds — and it
does not hit the new row, because no world-price *difference* stands there. Distinction
comes from `durchgriff(l, s)`, `handelsvolumen(l, s)` and `hub(l, zoll)`, all three
country- or country-sector-specific; the world price supplies only the **level** at
which a rate in basis points becomes a shift in index points. A level can single out no
one and is not meant to.

**And it is no ninth channel.** The tariff level now reaches the damage by two paths
instead of one: via the quantity (instrument → trade → `handelsvolumen`) as before, and
newly via the shift (instrument → `hub` → damage). Both are links of channel 3, the
second is the first without its detour. The damping is unchanged the same and unchanged
enforced: `gegendruck` is written only in step 5, `lies_neu` on it in step 3 is a hard
error per T39, so the path crosses exactly one round boundary. Within the round the
order 3 → 4 → 5 stays cycle-free.

#### Die Skalenprobe

Class 5 (price index) and class 3 (basis points) are both **ten-thousandths**, and class
2 stands at constant prices of the base year. For a real quantity `Q` and a price index
`P` the nominal value is `Q · P / 10.000`; if the price shifts by `ΔP`, the value shifts
by `Q · ΔP / 10.000`. That is the formula, character for character. For the interest row
the same computation with a rate instead of an index: debt stock times rate change in
basis points divided by 10.000 is the additional debt service of one year, in thousand
USD. **Class 2 times ten-thousandths divided by 10.000 yields class 2**, and this result
goes unchanged into `lobbypunkte_aus_schaden`. A fourth scale transition arises nowhere.

**Since 2026-09-03 the tariff row has two intermediate steps instead of one, and both
hold the class.** `keilhub` is class 5 times class 3 divided by 10.000, hence class 5
again — the shift of the tariff-laden world price in index points. `preishub_zoll` is
class 5 times class 4 (`durchgriff`, ten-thousandths) divided by 10.000, hence class 5
once more. Only the last step leaves the index world, and it is the same as in the three
other rows: class 2 times ten-thousandths divided by 10.000 is class 2. **No fourth
scale transition, and class 1 is touched nowhere** — the tariff row's classification in
the instrument table remains class 5, as in the previous version.

On overflow: the largest factor is `bip(US)`, per T5 of order `2,1 · 10^10` thousand
USD; times a shift in ten-thousandths, the intermediate result stays far below the
`i64` limit, and `mal_geteilt` computes over `i128` per T6 anyway. The tariff row stays
below that: `welt.preis` is an index of order 10^4, `hub(l, zoll)` is bounded by
`instrument_max[zoll]`, `keilhub` and `preishub_zoll` are thus index quantities
themselves; the largest product is `handelsvolumen · preishub_zoll` and, at a trade flow
of order 10^9, lies around 10^13.

#### Was Gegenkraft 5 im Weltlauf tut

**Nothing, and that is already decided.** In mode `weltlauf` the fund subsystem does
not run; of step 5 only approval and change of government run, counterforces 1, 3, 4
and 5 are not computed. `gegendruck` belongs per `technik.md` T38 to the block
*Instrumente ohne Stand* and stands there on **nein**: the address is not written and
keeps its start value 0. This computation rule is not evaluated in the weltlauf.

That is no loss but the condition of the measure. The policy instruments are exogenous
in the weltlauf; a counter-pressure would have no addressee there, and regulation, whose
damage row is the only one without a data anchor anyway, stands fixed at its start
value. The formula's inputs — instrument levels, **world prices**, trade block, value
added, government debt — all stand in the weltlauf mask (`technik.md` T38 carries the
world prices there with **ja**); the sector prices the previous version still needed
have not stood in the formula at all since 2026-09-03. The computation *could* therefore
run along. Writing it would break the mask, and an output beside it is the test stand's
business and not a design question.

**The consequence, named expressly: Maß 4 does not check this rule.** It is checked by
Maß 2 (does the family Lobby stay within the 25 percent?), by Maß 3 (does the best
profile shift between early and late window?) and by the break tester via the invariant
`0 ≤ gegendruck ≤ druck_max` from T30 check 6. Whoever changes a number of this rule
sees the effect in self-play and nowhere else.

#### Was diese Regel für Maß 2 und Maß 3 leistet

**One rate, four quantities.** `gegenlobby_satz` holds equally for all sixteen
addresses; what differs is the quantity it engages — and that stands not in
`parameter.toml` but in the vintage. The four countries are chosen above for structural
difference (*Warum vier Länder und nicht drei*), and exactly this difference now carries
a price: whoever has an export surplus has an expensive tariff row; whoever pays high
interest on high debt, an expensive interest row. **Which instrument is cheap to move
thus hangs on the country and not on a balance number.** That is the construction this
design has documented at Democracy 4: effect from loaded tables, not from programmed-in
exceptions.

**And the tariff row is the only one with structure below the country.** `schuld` and
`bip` know only the country; the tariff row computes per country **and sector**, because
`durchgriff(l, s)` and `handelsvolumen(l, s)` do. That is the reason the decision of
2026-09-03 falls on the wedge and not on the bare tariff level: a tariff whose price no
longer depends on which sector it hits would be, for Maß 2, a fourth row of the same
kind instead of one of its own.

**And the quantities move over the game.** `handelsvolumen`, `schuld` and `bip` are
endogenous quantities on a historical path, and the four breaks the cut above expressly
kept in the window — WTO accession 2001, 2008, 2020, recovery 2021 — all run through
trade, government debt or output and thus through exactly these three quantities. Since
2026-09-03 the **level** at which the rate engages moves in the tariff row as well:
`welt.preis.<s>` is just as endogenous, and the same tariff step costs more on a more
expensive world market. The cheapest lobby target of round three is therefore not
necessarily the cheapest of round twenty — a **third** source of optimum shift beside
imitators (counterforce 4) and price shock (counterforce 3), and this time one that
comes from the vintage instead of from a rule. *In which direction and how strongly* is
measured by the vintage build and then the test stand; this design does not claim it.

Added to this is the asymmetry that already stands and now has a quantity behind it:
Germany has no policy-rate lever of its own — since the window cut to 2001, over the
whole game instead of from round 3. The interest row is closed there, whatever it would
cost, and the way out leads through an instrument with a different quantity. A closed
action space that forces another — that is what the asymmetry above was chosen for, and
counterforce 5 now gives it a price instead of only a lock.

**Does it grow with success?** Yes, on two paths. The first is the intended one: an
instrument moves deliberately only through action 3, whose effect grows with the fund's
wealth (channel 8) — more success, more movement, more damage, more counter-pressure.
The second is an interlocking with counterforce 2: a change of government resets **all**
instruments toward their historical mean, thereby generates damage on all four in one
round and lays counter-pressure on all four in the following round. That is not chance
but success one step later: the change of government is itself the consequence of
successful lobbying. That this makes two penalties out of one cause stands under
*Offene Entwurfsfragen*.

### Das Realeinkommen in Gegenkraft 2, als Rechenvorschrift

`parameter.toml` fixed the **unit** — „Aenderung der Zustimmung in Zehntausendsteln je
Zehntausendstel Aenderung des Realeinkommens" — and thereby said what counterforce 2
needs: not a level but a **relative change in ten-thousandths**. The magnitude was
missing, and package `0197` could not be built for that reason
(`befunde/ergebnis-0197-schritt-5-reaktion-rechnet-die-zustimmung-2026-09-07.md`: eight
lines in `specs/` mention the quantity, every one prose or an arrow). It is filled here,
in the same place and the same form as the damage of counterforce 5.

#### Was Realeinkommen ist, und warum das BIP seine Gegenprobe ist

**As a level it already stands in the model:** real income of country `l` is `bip(l)`,
number 9 in `technik.md` T48. Class 2 stands per T5 „zu konstanten Preisen des Jahres
2015"; value added is therefore a real quantity, and its sum over the three sectors is
the country's real income of that year. That sentence is not new — the rejection of the
value-added loss two sections up rests on it.

What was missing is the other half, and it is why the word looked undefined: **real
output is blind to the prices policy sets.** A tariff step, an interest step, a
consolidation shift what an income buys, and none of that reaches `bip(l)` in the same
round — the real path runs via investment and capital stock and is channel 1.

Here that blindness is the instrument and not the defect. It gives counterforce 2 the
one thing counterforce 5 had to buy with a second market clearing and could not afford:
**the state that would have been without the action.** `bip(l)` is that counterfactual —
free, in the same round, without a second address. Hence, for each of the playable
countries:

```
realeinkommen(l)     = bip(l) − politiklast(l)                          [Klasse 2]
realeinkommenshub(l) = mal_geteilt( −politiklast(l), 10.000, bip(l) )   [Klasse 3]
```

**The reference of the change is therefore not the previous round but the same round
without policy movement.** Everything is read with `lies_neu`; the only difference of the
whole rule is taken over the instrument levels, inside `politiklast`. That is T39
answered at one place instead of four.

#### Die Belastung, vier Zeilen, ein Vorzeichen

```
politiklast(l) = Σ über die vier Instrumente i:
                   sgn( lies_neu(land.<l>.instrument.<i>.stand)
                      − lies_alt(land.<l>.instrument.<i>.stand) ) · schaden(l, i)
```

`schaden(l, i)` is number 22 in T48, taken over unchanged with all four of its rows, and
that is the whole content of the decision: **the burden a policy step puts on households
is the same number the damaged sector reads — read twice, with different treatment of
its sign.** Counterforce 5 reads its magnitude, because whoever moves something damages
someone in either direction. Counterforce 2 reads its sign, because a household is not
indifferent to the direction. Both readings stand in the same section for that reason.

| Instrument | rising level means | for the household | `menge(l,i)/bip(l)` |
|---|---|---|---|
| `zoll` | tariff up, import price up | burden | trade volume over GDP |
| `leitzins` | rate up, debt service on `schuld(l)` up | burden | the debt ratio `staatsschuld[l]/10.000` |
| `haushalt` | balance up, i.e. consolidation | burden | **1** |
| `regulierung` | one step tighter, `regulierung_last` bp of GDP per step | burden | **1** |

The fourth column is what the division by `bip(l)` newly makes visible, and it costs no
number: for the budget instrument the real-income change is **exactly the negative
instrument step in basis points**, because that row's quantity *is* `bip`; for the
interest instrument it is that step times the debt ratio; for the tariff, times the trade
openness. **The country asymmetry the design chose its nine countries for thereby prices
the political cost as well** — a highly indebted country pays for an interest step, a
trade-dependent one for a tariff step, and everyone the same for a consolidation.

**The level of the budget instrument is the balance** (series 12, IMF WEO; per
`parameter.toml` „deutlich negativ" in several countries of the check vintage), so a
rising level is consolidation. Were it read as the spending ratio, this row's sign would
flip; the design decides the balance, and the data anchor is the reason.

**And the approval rule, since it is two lines and otherwise blocks `0197` a second
time:**

```
zustimmung_neu(l) = min( 10.000,
                         max( 0,
                              lies_alt(land.<l>.zustimmung)
                              + mal_geteilt( zustimmung_elastizitaet,
                                             realeinkommenshub(l), 10.000 ) ) )
```

The two bounds are the value range of class 4 and not a bandage over a gap: 0 and 100
percent approval are attainable states, and `min` at a bound is the construction
counterforce 5 already uses at `druck_max`. Below `zustimmung_wechselschwelle` the
government changes; it sets `regierungsdruck_rest` and `lobbykosten_rest` in step 5, and
the **instruments are reset in step 3 of the following round**, because step 3 is the
only place an instrument level is written and no state quantity is written twice in a
round.

#### Warum die Belastung und nicht das Preisniveau

The package `0198` named three candidates, a fourth follows from them, and **all of them
fail on the same property: a term that moves without an action.** The reasons are already
written down in this document, one counterforce further up.

**`bip(l)` against `preisniveau[l]`** — the textbook form. It **deflates twice**: class 2
already stands at constant prices, so the quotient is not real income but real income
divided by a price index. Read as intended — value added valued at sector prices, over
the price level — it is worse, not better: in an inflationary year the numerator and the
denominator both rise, the remainder is the relative price movement, and it moves in
every round without any action. That is the base term of the tariff row again, one
counterforce further on, and its consequence is the same one 2026-09-03 named: approval
would be driven by the world market instead of by the player, exactly the reading of „the
consequences of choices often feel intangible". It is the heavier objection here, because
the drift is one-directional: real growth is the normal case, approval would saturate at
its upper bound after a few rounds, and **a counterforce whose main driver is exogenous
growth does not grow with success** — the requirement at the head of this section.

**`bip(l)` against `bevoelkerung[l]`** — real income per head. It fails on the first of
the three reasons the value-added loss failed on: **it is blind to every instrument.**
Population and value added move on channel 1 and on the vintage; a tariff step does not
appear in it at all. It costs a scale class on top (class 2 over class 8 is in no line of
T5), and the change it measures is the business cycle minus population growth.

**The terms of trade** — the third reading, and the closest to being right: the two world
prices move differently, so a country that exports industry and imports agriculture
gains. It is computable from the trade block without a second market clearing. It fails
on the base term as well, this time as noise instead of drift: world prices move every
round from market clearing, and an approval change whose cause is „agricultural world
prices rose relative to industrial ones" hangs on no action. It is named here rather than
omitted because it is the one reading that would have carried the effect of a **foreign**
instrument, and that effect is now expressly missing — see *Was bewusst fehlt*.

#### Die Zahlenprobe, an denselben zwei Zuständen

The probe of the section above, continued. State A is one German tariff step of 50 basis
points, state B the same round without an action; the two differ in exactly one quantity.
`bip(DE)` is an order-of-magnitude probe value like the trade volumes in that table, not
a measurement.

| Quantity | State A (one tariff step) | State B (no action) |
|---|---:|---:|
| `schaden(DE, zoll)` from the table above (Tsd USD) | 440.000 | 0 |
| `bip(DE)` (Tsd USD, probe value) | 3.400.000.000 | the same |
| `politiklast(DE)` | +440.000 | **0** |
| **`realeinkommenshub(DE)`** | **−1 bp** | **0** |

`440.000 · 10.000 / 3.400.000.000 = 1,294 → 1` under the rounding rule of T6, with the
sign from `sgn`. The same probe for the budget instrument needs no rounding at all: at a
step of 50 basis points, `politiklast = 3.400.000.000 · 50 / 10.000 = 17.000.000` and
`realeinkommenshub = −50`, exactly the step.

**State B is the acceptance, and it holds for all four rows without knowing any of the
forms above:** if no instrument level moves, every `sgn` is zero, hence `politiklast`
zero, hence `realeinkommenshub` **exactly zero** — for every price, every trade volume
and every debt ratio. The sentence that has held for the damage since 2026-09-03 thereby
holds for approval too: *it is nonzero exactly when an instrument moved in this round.*

**The invariant that follows, and it is the reason the signed reading is safe:** an
instrument that goes up and comes back leaves approval where it was — the two rounds
contribute `+x` and `−x` and cancel exactly if the quantity and `bip` are unchanged
between them **and neither round is clamped, that is: the unclamped sum inside the update
lies within `0…10.000` both times**. At a bound it does not cancel, and a test written
from this sentence without the premise asserts wrongly: from 9.990 with
`zustimmung_elastizitaet` 10.000, a budget step down and back up gives
`min(10.000, 9.990 + 50) = 10.000` and then 9.950. Approval measures the **net** policy
burden against the start of the game, not the churn. Oscillating is still not free, because counterforce 5 charges both moves
at full magnitude; **the two readings of the same number are what makes cycling strictly
expensive.** T6 carries this: its rounding runs „auf halbe Beträge von null weg" and is
symmetric over the sign, chosen for exactly this reason.

#### Skalen, Auflösung, und was die Regel kostet

Class 2 divided by class 2, times ten-thousandths, is a rate in ten-thousandths — class 3,
the same construction as `marktanteil` in *What a basket is worth*. **No fourth scale
transition, class 1 touched nowhere.** `mal_geteilt` computes over `i128` per T6, so the
product `politiklast · 10.000` needs no bound of its own: `politiklast` is bounded by the
largest of the four quantities times the largest possible shift, thus by a small multiple
of `bip(US)` — per T5 of order `2,1 · 10^10` thousand USD —, and the product stays around
`10^14`. `bip(l) > 0` is the denominator condition; it is a sum of positive value added
and a value-range bound the break run checks, as with `wechselkurs` in
*One valuation formula*.

**Read accesses:** 94 addresses, of which **90 are already read in step 5** by
counterforce 5 — the sixteen instrument levels at both ends, twelve value added, four
government debt, two world prices, the forty trade flows. New are **four**:
`lies_alt(land.<l>.zustimmung)`, one per playable country. As a formula in `L` that is
`2L² + 15L + 2`, thus 94 at `L = 4` and 299 at `L = 9`. **No new state address, no new
parameter key, no new vintage constant, no ninth channel.**

**One resolution condition, in form and without a number, and it is stricter than the one
counterforce 5 got in 2026-09-03.** If the smallest possible step of an instrument
produces a burden below one ten-thousandth of GDP, the row rounds to zero and the
counterforce is **mute there without saying so**:

```
mal_geteilt( schaden(l, i) bei schrittweite[i], 10.000, bip(l) )  ≥  1
                                    für jedes Land und jedes der vier Instrumente
```

The binding case is the tariff row, and it is binding by an order of magnitude: the probe
above yields 1 basis point where the budget row yields 50. That the condition is checked
at vintage build is design; the value of `schrittweite[zoll]` that satisfies it is
calibration and does not stand here.

#### Wo die Regel läuft, und was sie im Weltlauf tut

Computed in **step 5**, `L` times per round, after the instrument levels of step 3 and
the economy of step 4 stand. **Channel 2 keeps its damping and gains no link:** its head
is now the instrument step rather than the price — `Instrument → Belastung →
Realeinkommen → Zustimmung → Regierungswechsel → Instrument` —, which is channel 2
without its detour through the price, the same relation the tariff shortcut has to
channel 3. Exactly one round boundary is crossed and it is enforced, not promised: the
reset of the instruments is written in step 3 of the following round, and `lies_neu` on
`zustimmung` in step 3 would be a hard error per T39.

**Unlike counterforce 5, this rule does run in the `weltlauf`** — `technik.md` T38 carries
`zustimmung` in the mask and says:
„of step 5 only approval and change of government run" (technik.md:1379). Every input the
rule needs stands in that mask as well: instrument levels, value
added, government debt, world prices, the trade block. In the check vintage the
instruments follow their historical paths, so the burden is nonzero and approval is an
**endogenous, computed quantity in the backtest too**. The change of government is
computed and reported and writes nothing, so the exogenous policy paths stay untouched
and no check subject can move because of it.

**And the consequence, named expressly: Maß 4 does not check this rule.** Approval has no
target series — the data curator's gap 4, „no counterpart among the checked sources" —
and it is none of the check subjects, neither of today's 16 nor of the 28 after 0118. It
is checked by Maß 2 and Maß 3 in self-play,
by the per-chain unit test that `technik.md` section 9 already demands („Zoll rauf →
Einfuhr runter → Preis rauf → Realeinkommen runter → Zustimmung runter") — **that test is
buildable for the first time with this rule, and its two last arrows now hang on the
tariff step rather than on the price** —, and by the break run against
`0 ≤ zustimmung ≤ 10.000`.

**One consequence for whoever builds step 5 next:** because the rule is exactly zero
without an instrument step, a round in which step 3 carries the instruments forward moves
no approval address. A probe that counts changed quantities over such a round measures
nothing about this rule; the probe it needs is the two-state comparison above.

#### Was diese Regel für die Klagen und für Maß 2 und Maß 3 leistet

The three complaints stand row by row in *Die drei Klagen*; what this rule adds to the
first and the third stands there. Here the two that are its own.

**The sign is the answer to the second complaint.** „Trying to implement the tiniest
socialist policy will always result in bankruptcy" describes a game in which one political
direction is punished by construction. Here the direction that relieves households —
lower tariff, lower rate, larger deficit — **raises** approval and buys the political room
that the direction which burdens them spends. Whoever wants to lobby against the public
must first pay for it, or accept the change of government. That is a decision each round,
not a penalty, and it is the same argument the design makes for long and short.

**For Maß 3 it is a source of shift that costs nothing.** The four quantities of the
fourth column above — trade openness, debt ratio, one, one — move over the game on the
historical path, and so the politically cheapest instrument of round three need not be
that of round twenty. This is the same mechanism counterforce 5 has, read through the
other counterforce, and it needs no rule of its own.

**For Maß 2 it is the removal of a handicap, not a new one.** The family Lobby is the only
one whose counterforce was exclusively counterforce 5. It now has a second, and that
second one is **two-sided** — the only counterforce of the five that a player can move in
their own favour. A base term would have hit exactly this family for the second time and
in the same direction; that is why none of the three rejected readings survived.

## Wie die vier Masse berechnet werden

All four run in self-play without rendering, over the same state interface. What stands
here is a calculation rule; wherever a choice would have remained open, it is made here.
Every tie is broken by action id or profile id, never by discovery order. The median over
an even count is the smaller of the two middle values. **R = 20.**

### Die Ergebnisgröße einer Partie

An `i64` in milli-rounds, **smaller is better**, strictly ordered and without a catch-all
value:

| Outcome | Value | Range at R = 20 |
|---|---|---|
| mandate fulfilled in round r | `r × 1.000` | 1.000 … 20.000 |
| survived R rounds, mandate not fulfilled | `(R+1) × 1.000 + v + e`, see **Der Fehlbetrag** | 21.000 … 24.000 |
| died of a way of dying in round d | `30.000 + (R + 1 − d) × 1.000` | 31.000 … 50.000 |

#### Der Fehlbetrag, und wie „fehlender Einfluss" über die Länder gerechnet wird

The shortfall is `v + e`, both in per mille of the respective mandate threshold
(`schwelle_v`, `schwelle_e` from `parameter.toml`):

```
v = teile_gerundet(max(0, schwelle_v − fondsvermoegen) · 1.000, schwelle_v)

e = Summe über die zwei Länder mit dem höchsten Einfluss (Gleichstand nach LandId) von
    teile_gerundet(max(0, schwelle_e − einfluss[land]) · 1.000, schwelle_e)
```

**Two countries because the mandate demands two, and the fund's own two best because a
fund should not pay for countries it never wanted to enter.** Of the three obvious
readings — sum, mean, weaker of the two — the sum is chosen: it measures the **remaining
work**. A fund with one country at target and one at zero (0 + 1.000) and one with two
countries at half each (500 + 500) are equally far from the mandate, and that is exactly
what the sum says. The mean orders identically — it is the sum halved —; the weaker of
the two does not: it would declare the halved fund distinctly closer and thereby reward a
breadth the mandate does not demand.

**Nothing is capped, and nothing needs to be capped.** By build `einfluss` lies in
0 … 100, so each of the two summands in `e` is in 0 … 1.000 by construction and thus
`0 ≤ e ≤ 2.000`; in the band „survived" the fund is alive, so `fondsvermoegen > 0`
(otherwise way of dying 1 would have struck in the same round) and thus
`0 ≤ v ≤ 1.000`, where only rounding reaches 1.000. From this follows
`0 ≤ v + e ≤ 3.000` and the band 21.000 … 24.000 — computed, not decreed. The cap of the
third version was the substitute for a missing aggregation rule; with the rule it is
dropped, and it was harmful: it would have put every fund with less than one threshold of
total influence on the same value 1.000 — flattening the lower half of the outcome space,
precisely where Maß 3 seeks its argminimum when no profile in the window reaches the
mandate.

**With this, `spiel.md` and the bot objective `B` from `technik.md` T44 compute the same
formula in this branch** — the deviation justified there (T44 does not cap, because
capping made the bot blind in the early phase) disappears, because here too nothing is
capped. `B` stays bot-internal; the band check continues to apply only to the game
result.

**The bands remain disjoint, the upper one too:** „survived" ends at
`(R+1) × 1.000 + 3.000`, the death band begins at `31.000`; they are disjoint exactly for
`R ≤ 26`. That is **the same bound** that `technik.md` T40 already draws into the vintage
build — it remains valid unchanged, but is now tight instead of generous, and the wider
band costs no round of game length. At R = 20 the unreachable gaps are
20.001 … 20.999 and **24.001 … 30.999**; between the end of „survived" and the start of
the death band lie 7.000 milli-rounds of air.

**The edge from finding 10 is thereby closed:** the band 1.000 … 20.000 means exactly
„mandate fulfilled", the survived failure begins at 21.000, and no value carries two
meanings. The early death is worse than the late one, and by full rounds — exactly the
resolution Maß 1 needs in the last game third. A catch-all cap on the total value does
**not** exist. The range test reads: a result outside 1.000 … 50.000 is a hard error.

### Das Aktionsprofil und wie es auf Aktionen wirkt

An **action profile** is the distribution of the round budget over the five action kinds
on a fifth grid, i.e. a vector `(a1…a5)` with `ai ∈ {0…5}` and `Σai = 5`. That makes
`C(9,4) = 126` profiles. The **reference profile** is `(1,1,1,1,1)`.

The profile is a tool of the test stand, not a game quantity — the human chooses freely.
How it acts on actions was not stated in the second version, and Maß 2 and Maß 3 rest
entirely on it. **The stock procedure, binding:**

Each kind `i` keeps an integer stock `vi`, zero at game start.

1. **At the start of the round:** `vi += 3 · ai` for all five kinds. The total thus grows
   by 15 per round.
2. **For each of the round's three slots, one after another:** among the kinds that still
   have at least one admissible action this round, pick the one with the largest `vi`; on
   a tie, the smaller id. Place one action of this kind and compute
   `vi −= 5`. If no kind has an admissible action, the slot stays empty and no stock is
   charged.
3. **Which** action within the chosen kind is placed is decided by the bot: the heuristic
   bot by its fixed ranking, the search bot by search.

Three questions the reviewer rightly asked are thereby answered. The bot fills **all
three slots** as long as admissible actions exist; the bundle size is not part of the
profile. `ai = 0` does **not forbid the kind** but pushes it to the back — a hard ban
would leave profiles with zeros unable to fill their slots and would turn Maß 2 into a
comparison between three and fewer-than-three actions per round instead of between
strategies. There is never rounding and never a random draw: **after `5k` rounds the
stock vector stands at `(0,0,0,0,0)` again, and kind `i` has received exactly `3k·ai` of
the `15k` slots** — for `k = 1` that is `3·ai` of fifteen after **five** rounds, for
`k = 3` `9·ai` of forty-five after fifteen. Between two such points the deviation is
bounded. **Since `R = 20` the end of the game is itself such a point** (`k = 4`): a run
that plays the same profile for a whole game assigns `12·ai` of the 60 slots exactly by
profile — see *The game length R*.

As a check, the reference profile: rounds 1 to 5 assign the kinds
1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,5 and stand at `(0,0,0,0,0)` again afterwards —
exactly three of fifteen slots per kind, evenly distributed and deterministic.

**For the search bot** the profile fixes the kind composition of the round bundle; the 60
candidate bundles arise from the admissibility list ordered per T32, **restricted to
exactly this composition**, and drawn per T35. The search bot thus searches over targets
and steps, never over kinds.

### Maß 1 — Entscheidungsdichte

**Input:** 50 seeds, per seed one carrier game with the heuristic bot on the reference
profile.

For every round `t = 1 … R` and every seed: draw **30 action bundles**. A bundle arises
by first drawing the bundle size uniformly from `{0,1,2,3}` and then drawing that many
actions, uniformly and without replacement, from the list of actions admissible in this
round. Duplicate bundles in the sample set are **not** removed — otherwise the sample
size would depend on the state. The random seed follows from `(Jahrgang,
Parametersatz, Wurzelstartwert, t, Stichprobenindex)`.

The bundle **replaces the bot actions of round t**; round `t` is computed, then the
heuristic bot plays through to round `R` on the reference profile. The stock of the stock
procedure is carried forward for round `t` as if the bot had played the kinds of the
drawn bundle (`vi += 3·ai` at the round start, `vi −= 5` per action actually placed) —
otherwise the state of the counter after the injection would be undefined.

**Calculation:**

```
Ergebnis(t, s, k)      k = 1…30 Bündel, s = 1…50 Startwerte
Dichte(t, s) = Anteil der 30 Ergebnisse, die um mehr als 1.000 Milli-Runden
               vom Median dieser 30 abweichen
Dichte(t)    = Mittel der Dichte(t, s) über die 50 Startwerte
```

**Averaging over the seeds happens only at the end, and over densities, not over
results.** A common median over all 1.500 results of a round would be wrong: per
`technik.md` T11 different seeds produce different vintage spreads, and a median over
several worlds would drive the deviation share towards 1 without a single decision having
become denser.

**Acceptance:** the mean of `Dichte(t)` over each game third — the thirds are
`1…⌊R/3⌋`, `⌊R/3⌋+1…⌊2R/3⌋`, `⌊2R/3⌋+1…R`, at R = 20 thus **1-6, 7-13, 14-20** — each
**≥ 0,4**, not merely over the whole game. A game that lives only in the middle fails
here. If it fails, „the consequences of choices often feel intangible" has just been
measured.

**Cost.** A bundle in round `t` costs rounds `t … R`, i.e. `R + 1 − t` world steps —
Maß 1 measures the decision **of round t**, so it is counted in.

```
je Startwert:  30 · Σ(R+1−t) für t = 1…R  =  30 · R(R+1)/2  =  30 · 210 =  6.300
               zuzüglich Trägerpartie R                                 =     20
                                                                          ------
                                                                           6.320
50 Startwerte:                                                           316.000
```

### Maß 2 — Strategievielfalt

**Input:** all 126 profiles, 20 seeds each, search bot.

The profile result `E(p)` is the median of the 20 game results. A profile **wins** if
`E(p) ≤ R × 1.000 = 20.000` — that is, exactly when its median lands in the band
„mandate fulfilled".

The **strategy core** of a profile is the action kind with the largest share among the
three families `{1 Position, 2 Beteiligung, 3 Lobby}`; on a tie, the smaller id.
Leverage and visibility are amplifiers, not strategies, and do not enter the core.

**The six profiles `(0,0,0,a4,a5)` with `a4 + a5 = 5` have no strategy core.** They
contain not a single family action; assigning them class 1 via the tie rule would mean
counting a position strategy as fulfilled in which no position occurs. They run along,
their result is reported, and they enter **neither** of the two acceptance halves. That
leaves 120 profiles classified, spread over exactly three classes.

**Acceptance, both parts:**

1. **Each of the three classes provides at least one winner.**
2. Let `Ek` be the best (smallest) profile result of class `k`. Then
   `max(Ek) ≤ 1,25 × min(Ek)` must hold.

The second part is the more important one — otherwise three win but one dominates, and
that is the same defect under another name. This is the number behind „trying to
implement the tiniest socialist policy will always result in bankruptcy".

**Cost:** one search-bot game `R × (1 + 60) = 20 × 61 = 1.220`;
`126 × 20 × 1.220` = **3.074.400 world steps**.

### Maß 3 — Verschiebung des Optimums

Two separate runs per profile, each over the **full game**, so that no round is left
without a prescription. The windows are the first and last game third from Maß 1:

- **Early window:** rounds 1-6 with profile `p`, rounds 7-20 with the reference profile.
  Result `Efrüh(p)` = median over 20 seeds.
- **Late window:** rounds 1-13 with the reference profile, rounds 14-20 with profile `p`.
  Result `Espät(p)` = median over 20 seeds.

The profile switch happens at the round start; the stock of the stock procedure keeps
running across the switch and is not reset. Both runs use the search bot, inside as well
as outside the window.

`p*` = profile with the smallest `Efrüh`, `q*` = profile with the smallest `Espät`, ties
by profile id; all 126 profiles are eligible. **Shift** = `Σ|p*i − q*i| / 5`.

**Acceptance threshold 0,4.** Both vectors sum to 5, so the sum of absolute differences
is always even, and the shift takes only the values `{0; 0,4; 0,8; 1,2; 1,6; 2,0}`.
The threshold 0,5 of the second version in truth demanded 0,8, i.e. two shifted fifths;
what was meant and what is demanded is **one**.

The shift is forced not by balance but by counterforces 4 and 3: imitators graze off
every early position, the price shock devalues size. This is the number behind „already
the richest hedge fund in the game and nothing fun to do".

**Cost:** `2 × 126 × 20 × 1.220` = **6.148.800 world steps**.

**Sum of the three Maße:** `316.000 + 3.074.400 + 6.148.800` = **9.539.200 world steps**.
What the whole night run costs is in `technik.md` section 10 and not here — at this spot
the second version named a number that presupposed test-stand prescriptions it did not
itself make.

### Maß 4 — Rückvergleich

**The backtest is a `weltlauf`, not a game.** That is the answer to finding 2, and it is
a design decision, not an interpretation: a fund with zero assets divides by zero in
round 1 and, if you protect it from that, dies of investor withdrawal by round 3 at the
latest. Neither is a state in which a world machine can be checked.

In `weltlauf` mode, therefore:

- **The fund subsystem does not run.** Step 2 (actions) and step 6 (settlement) are
  dropped entirely; of step 5 only approval and change of government run. Counterforces
  1, 3, 4 and 5 are not computed; there is no return, no excess return, no investor
  base, no mandate and **no way of dying**. No field of the fund block and no imitator
  counter is written; they keep their start values.
- **The policy instruments are exogenous** and follow, round by round, the historical
  paths for policy rate, tariff level and fiscal balance. Every rule that would write an
  instrument — lobby pressure, counter-lobby, the instrument reset by a change of
  government — is not executed. A change of government is computed and reported but
  remains without effect; the oracle is blind at this spot, and that belongs in every
  finding.
- **The write rule does not become softer through this, but narrower:** in the
  `weltlauf` too, no address is written twice per round. The set of addresses written at
  all is fixed per mode and is reported alongside by the test stand.

Maß 4 thereby checks exactly what it is supposed to check: the transmission
politics → economy via steps 3 and 4. A run with invented politics would check only half
the machine; a run with a dying fund would check nothing at all.

**The 27 target series** are GDP per country (4), sector shares (12, of which 8
independent), consumer prices (4), exchange rate against USD (3), government debt ratio
(4); plus the trade block over 40 flows as a block of its own. Each over 21 support
points without filling. Per the classification from `technik.md` T37 the four government
debt ratios are **derived**, the remaining 23 **free**.

**The policy rate has not been a target series since 2026-09-03.** The class `gesetzt`
is thereby empty and is dropped. The reason is in *The game length R* and is not one of
coverage: a series that is set as input in the `weltlauf` has error zero by construction
— it cannot fail and cannot prove anything, and it still shortened the window by a year.
**What takes its place is sharper, not softer:** the policy rate remains input (series
9, role start + policy path), and that the machine reproduces it unchanged is an
**invariant**, not a threshold. If the model value deviates from the set path at any
support point, that is a hard error and not an error measure of 300 basis points. It is
still reported.

**The three error measures, per series:**

| Series | what is compared | Threshold |
|---|---|---|
| GDP (4), sector shares (12), government debt ratio (4), trade flows (40) | the **level** | MAPE over the 21 support points ≤ 20 % |
| consumer prices (4), exchange rate (3) | the **annual rate of change** in basis points | mean absolute error over the 20 transitions ≤ 300 bp |
| all | the **direction** | share of the 20 transitions with `sgn(Δmodell) = sgn(Δsoll)` ≥ 0,6 |

The second row is the consequence of `technik.md` T8: a percentage error on an index
that wanders by an order of magnitude over two decades measures the starting point and
not the machine — and a percentage error on a rate near zero explodes. The 300 basis
points, i.e. three percentage points of mean error on the annual rate, have the same
status as the 20 percent and the 0,6: a bar that was set. Should it prove unreachable,
that is a finding about the model and no reason to move it.

**The acceptance rule — `3·L_R + (L_R − n) + 1` check subjects, tolerance `⌊L_R/2⌋`.**
Today, with `L_R = 4` backtest countries and `n = 1`, that is **16 and 2**; after
package 0118 with `L_R = 7` it is **28 and 3** (see *Welche neun Länder*). **From here
on both stand as a formula and not as a digit**, for the same reason `R` stands as a
letter: a fixed 2 would make adding a country a tightening of the backtest without any
rule of the model changing. The second version named two error measures and no rule for
how to aggregate over the series; `technik.md` T37 read a total measure out of that and
returned the decision. Here it is:

1. **Only the free series are acceptance-relevant.** The four derived debt ratios are
   reported and decide nothing; since 2026-09-03 the policy rate is not even a target
   series any more, but input with an invariant check. A series that is error-free by
   construction must not soften a total measure.
2. **The check subject is not the series but the quantity.** There are sixteen today,
   and **counting is per backtest country, not per country** — per T58 a play-only
   country lies entirely outside the target mask and contributes none:

   | Check subject | Formula | today | after 0118 | aggregated from |
   |---|---|---:|---:|---|
   | GDP per backtest country | `L_R` | 4 | 7 | one series each |
   | sector structure per backtest country | `L_R` | 4 | 7 | the country's **three** share series, all three must pass |
   | consumer prices per backtest country | `L_R` | 4 | 7 | one series each |
   | exchange rate per backtest country except the numéraire | `L_R − n` | 3 | 6 | one series each |
   | trade block | `1` | 1 | 1 | `(L_R+1)·L_R·(S−1)` flows — 40 today, 112 after 0118; median of the MAPE and median of the directional accuracy; the worst fifth is reported |
   | **Sum** | `3·L_R + (L_R − n) + 1` | **16** | **28** | |

   The three share series of a country are not independent, due to the normalisation to
   10.000; kept as three counters, a single badly modelled country would use up the
   tolerance on its own. Kept as **one** counter it costs one of sixteen — and in return
   must pass in all three shares.

   **The number 16 has remained unchanged by the cut of 2026-09-03, and that is
   recounted, not assumed.** Struck are the four policy-rate series; the table above
   draws on series 1 (GDP), series 2 (sector shares), series 8
   (consumer prices), series 10 (exchange rate) and series 14 (trade block). None of the
   sixteen check subjects contains series 9, and none could: per T37 it was `gesetzt`.
   **The acceptance rule „at most 2 of the 16" thus keeps running on the same set of
   series as before, only over 21 instead of 25 support points.** What has changed is
   the denominator of the *target series* (31 → 27), not that of the *check subjects*.

3. **A check subject passes** if it holds both thresholds that apply to it. **The
   directional accuracy is formed only over the transitions in which the target series
   moves.** A transition without measured movement carries no direction and is counted
   neither as a hit nor as an error; if a target series moves in none of the twenty
   transitions, the check subject has no directional accuracy and passes on its level
   measure alone. That is not a softening but the closing of a gap: over a constant
   series every transition carries direction zero, an endogenously computed value
   virtually never hits the exact zero, and the subject would break **by construction**.
   The case is not hypothetical — it is the reason Saudi Arabia is expected to be a
   play-only country (see *Welche neun Länder*), and flat stretches exist even without a
   currency peg.
4. **The run passes if at most `⌊L_R/2⌋` check subjects break** — today two of sixteen,
   after package 0118 three of twenty-eight. Every broken one is named individually in
   the finding, with both numbers. One more is a fail, even if it breaks narrowly. **At
   `L_R = 4` the formula reproduces exactly today's 2** — that is the compatibility
   check — and after that it holds the share nearly fixed: 2 of 16 is 12,5 percent, 3
   of 28 is 10,7, 4 of 36 is 11,1. It thus grows more slowly than the number of subjects
   and never lowers the bar.

The median over the trade flows — 40 today, 112 after package 0118 — is the architect's
proposal (`technik.md`
section 12) and is hereby adopted, with its reasoning: individual small flows
— Brazil–China in agriculture — fluctuate strongly in percentage terms without the model
being wrong; a mean would break on that, a per-flow threshold faster.

**Cost:** R = 20 world steps.

**And the limit of the oracle, explicitly.** Without a target series are: **sector
prices** and **world prices** (gap 2 of the data curator), **approval** (gap 4), the
instrument **Finanzmarktregulierung**, the **market return** and, since 2026-09-03, the
**policy rate** — the last not for lack of data, but because it is input and a set value
checks nothing. Added to this, in the `weltlauf`, is the entire fund subsystem, which
does not run at all. All these quantities are visible in the state; none is covered by
the backtest. It checks the dynamics of the machine over the historical period and says
nothing about the branch the player enters.

**One filled support point, which belongs in every finding.** The US policy-rate path
ends in 2020; its twenty-first support point is the carried-forward value of 2020 and
carries `gefuellt = 1`. It is not a target point, so it does not fall under T24's
prohibition — but it is an **input**, and the last transition of the US check subjects
runs on it. The test stand reports it. It is the only filled value in the whole check
vintage.

### Die drei Klagen und was sie beantwortet

| Complaint from the reviews | Design decision |
|---|---|
| „the consequences of choices often feel intangible" | **At most three actions per round** — scarcity forces every action to be big enough to have an effect. Plus the chain as its own part of the state (steps 1 and 6) and Maß 1 as an acceptance threshold per game third instead of a wish. **Since 2026-09-03 also the counter-check:** in counterforce 5 the damage of each instrument is non-zero exactly when the instrument has moved. A chain that shows a penalty and no action behind it is the same complaint from behind — that is why the business-cycle base term of the tariff row fell. **Since 2026-09-07 the same holds for approval:** `realeinkommenshub` is nonzero exactly when an instrument moved, so no change of government can appear in the chain without an action behind it. |
| „trying to implement the tiniest socialist policy will always result in bankruptcy" | **The fund can be long and short.** Thus no political direction is dominant: whoever bets on regulation because they are short wins just as much as whoever prevents it. Plus the two-part victory condition (capital AND influence) and Maß 2, which wants to see each of the three families win individually. **Since 2026-09-07 also in the counterforce itself:** counterforce 2 reads the **sign** of the burden, so the direction that relieves households raises approval. It is the only one of the five counterforces a player can move in their own favour. |
| „no dramatic setbacks or successes", „everything is incredibly surface level" | **Three ways of dying with visible thresholds** (forced liquidation, market ban, investor withdrawal), the result scale that rates the early death worse than the late one, and Maß 3, forced by imitators and price shock. The setback is dramatic, but never arbitrary — see „Keine verdeckte Größe". The change of government is the fourth threshold of this kind, and since 2026-09-07 it has a quantity behind it instead of an adjective. |

## Was bewusst fehlt

- **More than four countries and three sectors.** The idea named twelve and six. Twelve
  countries quadruple the feedback paths without improving any Maß; six sectors do not
  exist under a free licence, and sectors split out of three would be a construct without
  a target series.
  **Classified on 2026-09-05, not struck:** The sentence applied and still applies to
  *policy countries* — the operator has decided on nine (package 0118), and that is the
  number it is to be read against from now on. For the *investable universe* it has been
  moot since package 0119: that universe grows through the second layer, which adds no
  feedback paths because it has no trade row.
  **Filled in on 2026-09-06:** The nine are the USA, China, Germany, Brazil, Japan,
  India, Chile, Singapore and Saudi Arabia. The sentence about the quadrupled feedback
  paths remains true all the same and can now be given a number — the trade matrix grows
  from 40 to 180 flows, four-and-a-half-fold, while everything else roughly doubles.
  **It is thereby the reason why there are nine and not twelve**, and no longer an
  objection to the nine.
- **A tenth policy country, and the boundary lies in the matrix, not in taste.**
  `G·(G−1)·2` with `G = L+1` yields 220 flows instead of 180 at ten countries, 312 at
  twelve. Whoever wants more investable world gets it through the second layer at five
  fields per tradable slot instead of around twenty — that is the layer's entire
  justification, and it holds against any tenth country just as against the thirtieth.
- **A second euro-area country.** Greece was the strongest candidate for the fifth place:
  its fiscal balance becomes exogenous under the programme in 2010 — round 10, exactly
  between the two windows of Maß 3 — and that would be the instrument lock that has been
  missing since the window was cut to 2001 and that this design explicitly misses. **It
  fails at one address:** the euro's exchange rate against the dollar is the **same**
  series for Germany and Greece, but the model keeps `wechselkurs[l]` per country and
  would compute two euro rates that are allowed to drift apart. The two countries would
  carry two check subjects on a single reality, and an error in the euro rate would break
  both at once. The way out would be a shared rate address per currency area — and that
  changes the address arithmetic, the target-series count and the check-subject formula
  all at once. Too expensive for a fifth country, and a package of its own should the
  euro area ever appear twice.
- **An instrument lock that snaps shut inside the window.** It has been missing since
  2026-09-03 and it stays missing. The candidate outside the euro area was Turkey (IMF
  programme 2002–2008, i.e. rounds 2 to 8); it is rejected because that window lies
  exactly over the early window of Maß 3, so the lock would sit not *between* the two
  windows but *inside* one. What would remain is a lock on a middle round — and that is
  the narrated event that stands two lines further down on this list for good reason.
  **Maß 3 must still produce the shift without such a transition**; since package 0119
  its third source is the second layer.
- **An exchange-rate regime as a model quantity.** Saudi Arabia's rate stands at 3.75
  across all 21 support points, and the model has no rule that holds a rate. A currency
  peg would be cheap to write — the `wechselkurs[l]` of a pegged country is simply not
  written, the same construction as the decommissioned addresses of a play-only country —
  and it is still not decided here: it would turn a play-only country into a backtest
  country and thereby shift `L_R`, the check subjects and the target mask. That is a
  decision about the foundation of the backtest and belongs, per T60, to the operator,
  not to this section. **What it would buy is stated here:** a pegged rate is the only
  way the model could express the difference between a loud and a mute currency, and
  Saudi Arabia is the only place where it is measurably off.
- **All 195 countries of the world.** That is not a „later" but a different product, and
  the numbers stand under *Was die Schicht kostet*: **87,788 state fields, 76,440 trade
  flows, 3,705 licence-checked data series** and 780 check subjects instead of sixteen.
  Rejected on 2026-09-05.
- **An exchange venue with a trade row, policy instruments or a stake.** Each of these by
  itself turns it into a cheap country: the trade row brings the `G²` matrix back
  (3,120 flows instead of 180), the instruments make it influenceable and thereby cancel
  the separation for whose sake the layer exists, and the stake would be the road to
  cheap lobbying in a place where there is no lobbying.
- **A supervision counter on the second layer.** The fund can grow large there
  unobserved. That is explicitly intended and dearly paid for: the layer delivers zero
  influence and can never fulfil the second half of the mandate. A half counter
  („visibility yes, influence no") would be a rule that decides nothing, because the
  footprint carries influence as a factor and would stay zero anyway.
- **A regulation channel onto `zins[b]`.** The obvious move would be for the anchor's
  Finanzmarktregulierung to drive capital away and lift the venue rate — a third lever
  into the second layer. It would cost another calibration key, and two levers into it
  exist already (the policy rate via `zielzins` and `weltzins`, the tariff via
  `leitkurs`). Should Maß 3 fail for lack of grip on the layer, this channel is the
  first addition.
- **A measured market capitalisation per exchange venue.** `tiefe[b]` is built from the
  anchor's capital stock and the sector weights, times `platzanteil`. A real
  capitalisation series would be the more correct quantity, but would hang on another
  source with its own licence question — and the ordering that matters (large anchor,
  deep venue) is delivered by the derived quantity too.
- **An inertia parameter of its own for the second layer.** A venue's `index`, `zins` and
  `wechselkurs` move exactly **half** way towards their target each round. Three
  calibratable weights would give the search three axes whose effect `kippung` and
  `platzanteil` produce anyway — and no Maß reads the halving.
- **Manufacturing as a sector of its own.** It would be the more interesting breakdown
  and even exists as a WDI series — but only as a subset of industry. A fourth sector
  „rest of industry" would have no source series of its own and would have to be formed
  as a difference. Four sectors with one uncovered, three with all of them covered: the
  choice is the second.
- **Start vintages before 2001**, and the boundary now lies four years later than in the
  fifth version. 2000 and earlier remain possible as **play vintages** and are the
  obvious content of the expansion model from the idea. They carry no US government debt
  ratio and no US fiscal path from data (IMF WEO begins in 2001 for the USA), before 1997
  additionally no US sector structure and before 1995 no trade block; a play vintage
  before 2001 takes the missing US start values from the first covered year and marks
  them as filled. That makes them play vintages, but not check vintages. This belongs
  written into the sales offer, not into a footnote.
- **A replacement for the euro transition, since 2026-09-03 and explicitly.** With the
  window 2001–2021 the only instrument lock that snapped shut during a game disappears
  (Germany loses its interest-rate lever in 1999). The obvious way out would be to put
  some other lock on a middle round — and that is exactly what I do not do: it would be
  a narrated event, and those stand two lines further down on this list for good reason.
  Events here arise from thresholds or from data, not from the wish for a turning point.
  Maß 3 must produce the shift without this transition; if it does not, that is a finding
  about the two remaining sources (imitator, price shock) and no reason to invent a lock.
- **Rebuilding the window 1997–2000 from a third source.** The table in *The game length
  R* works it through: for Brazil the years do not exist, for the USA they would exist
  only at the price of a different delimitation than for China and Germany. Four support
  points are cheaper than a target series that measures something different per country.
- **A fill rule of its own for policy paths.** The policy-rate path may be filled, the
  target series of the check vintage may not — that stands in T24 and suffices. A third
  threshold („a path may be filled to at most x percent") would be a number nobody can
  measure before the source is fixed. What holds instead: every filled support point of
  a path is named individually in the finding. With 21 support points a list is cheaper
  than a share.
- **A finer goods key than HS92 chapters.** The mapping 01–24 / 25–97 is coarse and its
  error is named above. A real HS-to-ISIC concordance would be more accurate and would
  cost another source with its own licence question — for two model sectors that is not
  worth it.
- **Quarterly and daily time steps.** With them, panic, runs and margin calls in the
  literal sense drop out — a palpable loss of genre expectation, and I name it as such.
  The reason is hard: GDP, sector structure, productivity and tariffs are available
  **annually**. Quarterly rounds would leave three of four rounds unchecked. The
  substitute for intra-year risk: leverage is checked not against the year-end level but
  against an intra-year swing that follows deterministically from the year's movement and
  the country's historical volatility range. Leverage stays dangerous without a second
  time layer coming into being.
- **A world equity index as a benchmark.** None exists under a free licence. The market
  return is therefore a model quantity without an anchor — named, not hidden.
- **A price of its own beside the sector price.** A basket is valued at the price of its
  sector, not at a share price that would be allowed to deviate from it. So there is no
  valuation bubble and no sentiment — the value of a holding follows its causal chain
  and nothing else. That is a loss of genre expectation and the price paid so that every
  change in value stays explainable.
- **Variable creditworthiness.** The `aufschlag` between policy rate and bond yield is a
  constant. A country whose debt ratio runs away pays no higher spread in the model;
  sovereign defaults and risk premia do not exist. The spread would have an anchor
  (yield series) but no target series in the state, and it would cost a ninth feedback
  channel (budget → spread → price → budget).
- **The money supply as the depth of the currency market.** It would be available from
  IMF IFS and would be the better quantity than trade volume. It costs one state address
  per country and one exogenous path, and it improves no Maß. Trade volume orders the
  four countries the same way and is already in the state.
- **Individual companies.** Only country×sector baskets. Firm-level data under a free
  licence does not exist, and what the data curator cannot obtain does not appear.
- **Derivatives, options, structured products.** Long, short, leverage. More instruments
  enlarge the action space without adding a profile that Maß 2 could distinguish.
- **Persons named by name.** Governments are roles („government of Brazil"), central
  banks are institutions. A requirement from `agentenbau.md`, and it touches precisely
  this game.
- **Election mechanics.** No parties, no coalitions, no constituencies. One approval
  quantity, a change of government when it drops below the threshold.
- **Narrated events and event cards.** They would be a content treadmill (G4) and not
  regressively checkable. Events here arise from thresholds.
- **War, climate, migration, demographics as game quantities, multiplayer.**
- **A tariff rate per sector.** It does not exist under a viable licence. The sector
  effect arises from `durchgriff` and the import shares.
- **A time-varying `durchgriff`.** It would be more correct and would cost ten more
  exogenous paths. Constant suffices, because the quantities are endogenous anyway.
- **A counter-lobby that wants to push something through itself.** `gegendruck` is a
  scalar netted against `druck` in step 3; it can **restrain movement, not demand it**.
  What counterforce 5 depicts is mobilisation, not retaliation — a damaged sector makes
  every movement of its tariff instrument more expensive, including the ones that would
  help it. Retaliatory tariffs would cost one direction per instrument and thus sixteen
  more addresses.
- **A split of the damage onto the damaged sector.** Who bears it stands there as a
  rule; it is computed per country and instrument, not per sector. The split would need
  an intermediate-inputs matrix — another source with its own licence question — and it
  would change none of the sixteen numbers in step 3.
- **A memory of the counter-lobby beyond one round.** The halving is the whole story. A
  tail spread over several rounds would cost sixteen more addresses and would only shape
  the transient.
- **Damage to the rest of world.** It has no policy instruments and thus no address at
  which a counter-lobby could form. Its price shifts remain unbooked; the rest of world
  closes the circular flow, it does not act.
- **A damage that distinguishes rise from fall.** The shift enters as an absolute value:
  every movement damages someone. The direction is already carried by the netting
  against `druck` in step 3, and a sign in the damage would pull it in a second time.
- **The business-cycle share of the price shift, since 2026-09-03 and explicitly.** A
  sector price trailing the world price shifts every round; that someone suffers from it
  is true and still no lobby damage. Whoever books price inertia as damage books
  inflation as a counterforce — the reasoning stands under *Warum die Zollzeile nur den
  Keil misst*. What is **not** missing because of this: the tariff's effect on the
  sector. It sits in `durchgriff(l, s)`, and that is the only reason the row does not
  simply read `hub(l, zoll)`.
- **The general-equilibrium share of a tariff step.** An American tariff moves the world
  price via market clearing, and with it the sector prices of all countries. This part
  of its effect enters no damage row, for it could only be measured against a state that
  does not exist: the same round with the old tariff level, that is, a **second market
  clearing** with another 40 halving steps per sector. The price would be the model's
  most expensive computation doubled, the yield a number no Maß checks.
- **The damage a foreign tariff does at home, in any counterforce.** It is the
  consequence of the previous item and falls with it. **Sharpened on 2026-09-07:** until
  then this entry said the effect merely changed counterforce — via the domestic sector
  price to real income, approval and a change of government. Since real income is a rule
  it does not, because that rule reads the country's own instrument steps and nothing
  else. The foreign tariff step therefore reaches neither the counter-lobby nor approval;
  it stays in the economy, in prices, trade volumes and the capital stock of the
  following round. Both counterforces now measure only what a causer inside the country
  did, and treating them alike is worth more than a political path that only one of the
  two could have carried.
- **The business-cycle share of real income, and it is the larger share.** Real output
  grows or shrinks every round, and approval reads none of it. Booking it would mean the
  world market deciding who governs, all countries at once and unavoidably for every
  profile — the drift version of the base term the tariff row lost on 2026-09-03, and
  this time one that would let approval saturate at its upper bound. The reasoning stands
  under *Warum die Belastung und nicht das Preisniveau*.
- **Real income per head.** `bevoelkerung[l]` stands in the state and is not read by this
  rule. It would cost a scale class that T5 does not have, and it would measure population
  growth rather than any instrument.
- **A state address for real income, and a level for the display.** The rule needs the
  quantity only as a change, and the level it would carry — `bip(l)` minus this round's
  burden — is a function of the state, computable at any time. An address would be a
  second copy of the same truth, the defect T45 excludes for addresses and T15 refused
  `landespreis` for.
- **A counter-lobby rate of its own per instrument.** One `gegenlobby_satz`, four
  quantities. Four rates would give the calibration three axes whose effect the
  quantities produce anyway — and from the vintage rather than from a number.
- **Graphics beyond table, time-series graph and chain view.** Democracy 4 sells itself
  with a 2D node surface and consists, in its simulation, entirely of loaded tables
  rather than hard-coded effects
  (positech.co.uk/democracy4/modding.html, retrieved 2026-08-31). That is the
  construction I orient myself by.

## Offene Entwurfsfragen

- **The hardest: Is the World Bank's aggregated tariff rate usable?** It is recognisably
  derived from WITS and may therefore fall under the third-party exception of the WDI
  licence. If it is locked, the backtest loses the most important of its three anchored
  instruments. That does not change the design — `technik.md` T26 has absorbed the case
  architecturally — but it halves its evidence. To be checked before anything is built.
- **The remaining WDI series under the third-party exception.** Per the architect's
  marking, the ones to check are Nr. 7 (sectoral employment, ILO estimate), Nr. 8
  (consumer prices, IMF-based), Nr. 10 (exchange rate) and Nr. 13 (tariff). For each
  series, read the field „Source" in the indicator dataset. Four retrievals and the
  question is closed — a task for the data builder, because it hangs on the vintage, not
  on the design.
- **The window is decided and this question is closed.** It was called „Bleibt das Fenster
  bei 1997–2021?" and since 2026-09-02 read „19, 20 oder 24?". **No, and 20.** The window
  is **2001–2021**, `R = 20`, 21 support points; decided on 2026-09-03 in package
  `0054-partielaenge-r-entscheiden`, justified in the section *The game length R*, carried
  through in all four measure rules and named for the architect in the catch-up table. The
  suspect case from `technik.md` T24 — the Chinese and the Brazilian policy-rate series of
  the nineties — is thereby moot: the nineties lie outside the window, and the policy rate
  is no longer a target series.

  **What emerges from the decision as new open questions is in the next two points.** They
  replace the closed one; they are not the same thing in another form: one concerns the
  procurement of an input, the other its uniformity. Neither hangs on R any more.
- **Where the policy-rate path for Germany and China comes from.** `IMF.STA/MFS_IR`
  carries not a single value for either country (coverage finding, retrievals 2026-09-01),
  and that holds for every window. The path is needed nonetheless: as `leitzins_start[l]`,
  as an exogenous path in the `weltlauf` and as the instrument's value range in the
  `spielmodus`. **This is a procurement question and a follow-up package for the data
  builder, not a design question** — and since the target role was dropped it is markedly
  smaller: under T24 an input may be filled and marked, a target series of the check
  vintage may not. Two leads already stand in our own records and are only named here, not
  checked: **Eurostat** is, per `daten.md` Nr. 7, commercially usable for EU and EFTA
  countries and thus covers the German — or rather the euro-area — side; **`FR.INR.LEND`**
  (WDI) carries China without gaps 1997–2021 per the coverage finding, but it is a bank
  lending rate, not a policy rate.
- **Whether a uniform notion of the interest rate is achievable across the four
  countries.** The coverage finding proves that `DISR_RT_PT_A_PT` measures something
  different per country — for the USA the discount rate of the Fed's discount window, for
  Brazil the rediscount rate, which is not the Selic. As a *target series* that would be
  an error which the deletion settles. As an *input* it remains an open question, and one
  that strikes through to check subjects: a Brazilian path at the wrong level drives bond
  price and interest-rate channel and with them Brazil's GDP, sector structure, consumer
  prices and exchange rate — four of the sixteen. **The design requirement for the
  follow-up package is therefore: one notion for all four countries, and if none is
  achievable, then the most plausible one per country, expressly named and carried along
  in the backtest's finding.** The data builder decides that at the sources, not I at the
  desk.
- **The numerical values of the thresholds** — mandate threshold, supervision thresholds,
  starting capital, imitator speed, step width of a position, investor withdrawal share.
  They do not belong in this design, because they are not decided but **calibrated**: the
  self-play searches for the values at which Maß 1 to 3 reach their thresholds. That is
  exactly what the measures exist for. What is fixed is the form, not the number; per T27
  the values stand in `parameter.toml`.
- **Whether a parameter set exists in which the fund is large enough and not too large.**
  New with this version, and the question is a measurement, not a decision: starting
  capital and `stufenweite` must together make one step affordable **and** let achievable
  step counts reach up to the supervision thresholds. Both at once is not guaranteed —
  the model's markets are entire sector capital stocks, and a fund that moves them is
  large. If the self-player misses the first condition, class 1 never wins; if it misses
  the second, no counterforce engages and Maß 3 falls to zero. **Both are visible on the
  test stand**, and both are a finding about the parameter set, not about the design —
  unless no admissible one exists. Then it is the design.
- **How fine the action space may be.** Too coarse, and Maß 1 finds no differences; too
  fine, and the sample of 30 bundles covers too little. To be determined empirically on
  the prototype — measurable by whether `Dichte(t)` gives the same answer at K=30 and
  K=60.
- **The load rate of the instrument „Finanzmarktregulierung", `regulierung_last`.** New
  with the damage rule, class 3, basis points of GDP per regulation step. It is the only
  number in counterforce 5 without a data-anchored counterpart — and precisely where the
  instrument table above in any case says „pure model construct", without a target series.
  The three remaining rows get by without a new number. Its value is calibrated, not
  designed; in the `weltlauf` it has no effect, because the instrument is fixed there.
- **Whether `druck` follows the same round-boundary rule as `gegendruck`.** About pending
  lobby pressure this design says only „action 3, netting in step 3"; whether it stays
  across the round, decays or is consumed is stated nowhere. That is the same kind of gap
  as the closed one, one level over, and **it is not without consequence**: influence is
  the fund's share of total lobby pressure, that is, of the ratio `druck : gegendruck`,
  and that ratio hangs on both rules. My proposal for the follow-up package is the same
  halving for the same reason; it is not decided here, because it belongs to step 3 and
  not to counterforce 5.
- **Whether `schrittweite[zoll]` exceeds the rounding threshold of the tariff row.** New
  on 2026-09-03 and the only condition that follows from the tariff-wedge decision. A
  tariff step runs through two roundings — world price level times rate, then times
  `durchgriff` — and for a country×sector pair with low `durchgriff`, `preishub_zoll` can
  fall to zero at small steps. Then the tariff row is **silent there, without reporting
  it**. The check form stands in the section; the number that satisfies it is calibration.
  The vintage build has all eight pairs on hand and can check the condition mechanically —
  it belongs in its output, not in a night run.
- **Whether one `gegenlobby_satz` carries all four rows at once, now with the opposite
  sign.** The question already stood; the decision of 2026-09-03 shifts it. The tariff row
  has become smaller by the base term — its action share is unchanged, but the gap to the
  budget row, whose quantity is the whole GDP, now lies open. Whether one rate carries
  both, or whether the Lobby family in effect has only one affordable instrument left, is
  to be seen on the test stand and not here. The design holds to a single rate, because
  four rates would give the calibration three axes whose effect the quantities produce
  anyway; if Maß 2 fails on that, it is a finding about the design and not about the
  parameters.
- **Whether the counter-lobby leaves the influence half of the mandate reachable.**
  Influence is the fund's share of the total lobby pressure on an instrument; a
  counter-pressure that runs toward `druck_max` in every country the fund touches pushes
  that share below any threshold, and the Lobby family produces no winner in Maß 2. That
  is the sharpest calibration condition that follows from this rule, and it is visible on
  the test stand. If no admissible rate exists, it is a finding about the design and not
  about the parameters.
- **Whether `gegenlobby_satz` is fine enough as an integer.** Class 9 knows no
  subdivision, so the smallest admissible value is one lobby point per 10.000 thousand
  USD. An order-of-magnitude check — expressly an estimate, because
  `schrittweite[haushalt]` is not yet fixed: at a GDP of `2.1 · 10^10` thousand USD and an
  assumed step width of 50 basis points, that is `1.05 · 10^8` thousand USD of damage and
  thus around **10.500 lobby points** at `gegenlobby_satz = 1`. Whether that fits
  `druck_max` and what the fund raises via `lobbykosten` is for the search to decide;
  since only the ratio counts in step 3, it can counter-steer via `lobbykosten`. If even
  that is not enough, the way out would be a ten-thousandths scale for `gegenlobby_satz` —
  an ADR against T5 class 9, to be decided on the test stand, not here.
- **Whether the change of government should produce damage.** Decided: yes — the reset of
  all instruments is itself the consequence of successful lobbying. What remains open is
  whether the calibration still finds a way back afterwards: counterforce 2 doubles the
  lobby costs for several rounds, counterforce 5 puts counter-pressure on all four
  instruments in the same round. Two penalties from one cause; whether that becomes a dead
  end is measured by Maß 2, not by this design.
- **Whether `platzanteil` has an admissible range.** New on 2026-09-05 and the sharpest
  condition that follows from the second layer. Too large, and the venues are deep enough
  for family 1 to build up capital there undisturbed — then the second acceptance half of
  Maß 2 (`max(Ek) ≤ 1,25 · min(Ek)`) fails, because Position leaves the other two families
  behind. Too small, and one step on a venue is either unaffordable or moves the price so
  strongly that the layer is unusable — then it is decoration and Maß 3 loses its third
  source again. Both are visible on the test stand, both are a finding about the parameter
  set — unless no admissible one exists. Then it is the design.
- **Whether `kippung` really distinguishes the three venues of an anchor.** They are
  different by construction, but whether the difference is large enough for a search bot
  to exploit it is a measurement. The check form: if, in the early window of Maß 3,
  profiles weighted toward different lead sectors reach the same result, the three venues
  of an anchor are one venue. The number is calibration; the form stands.
- **`3·(L+1)` survives the country choice from 0118, and this question is thereby
  closed.** It asked whether every territory carries three distinguishable lead sectors —
  for a country with a strongly dominant sector structure the three venues would lie close
  together under the `kippung` rule. Measured by the largest normalised sector share, the
  most one-sided of the nine anchors is the **USA** at 76.6 percent, and it has stood in
  the model since the first version; the two most balanced, at 51.3 and 47.7, are two of
  the five new ones (Saudi Arabia, India). **The choice improves the binding case instead
  of sharpening it.** What remains open is not the formula but `kippung` — and that
  already stands as its own question two points further up, now with the country attached
  on which it will be decided.
- **Whether `MFS_IR` carries a policy rate at Stufe 1 for Japan, India and Chile.** On
  this one retrieval per country hang the class of three countries and with it `L_R`, the
  number of check subjects (28 versus 16 to 22), the target series and the target mask. It
  is the cheapest open question of this package — three retrievals per T63 step 1 — and
  the one with the greatest leverage. It belongs to the data builder, not to me.
- **Whether the class rule from T61 rule 5 sees the exclusions that lie in the target
  series.** It derives the class solely from the three policy-path series. But two grounds
  for exclusion lie elsewhere: the missing fallback source for series 2 (T62 Folgerung 2)
  and — new since this package — a target series that is constant over the whole window
  and therefore cannot carry directional accuracy. If `MFS_IR` carries a SAMA rate at
  Stufe 1, rule 5 derives „Rückvergleichsland" for Saudi Arabia while the manifest must
  say „Spielland", and the vintage build aborts. The abort is right, the place is not.
  Belongs to T61.
- **Whether the tolerance `⌊L_R/2⌋` holds.** It is new on 2026-09-06 and replaces the
  fixed 2, because a fixed number turned adding a country into a tightening. It reproduces
  today's 2 and keeps the share at around eleven percent — but whether eleven percent is
  the right quota, only the backtester at the running core knows. If four of 28 break
  regularly, that is a finding about the model and not about the formula.
- **Whether the trade block is weighted correctly as *one* check subject when it grows
  from 40 to 112 flows.** The question exists already at four countries and becomes
  sharper with nine: the heaviest single subject of the backtest counts as much as the GDP
  of a single country. The aggregation via the median is the reason it does not fly apart
  anyway; whether at 112 flows it still delivers what it does at 40 is a measurement. Not
  decided in this package, because it is independent of the number of countries.
- **Where the sector weights of the three rest-of-world venues come from.** They follow
  the same rule from `sektoranteil[Restwelt][s]` of the start year. The rest of world
  arises in the vintage as a residual, and whether its sector shares fall out cleanly in
  the process is known to the vintage build, not to me. If the quantity does not fall out,
  the way out is the capital-stock-weighted mean of the `L` country shares — a rule, not
  an invented number.
- **Whether an embeddable price series exists after all.** The layer is designed without
  any target series, because `daten.md` carries none and this design already records that
  there is no world equity index under a free licence. Were the data builder to find an
  index series under a viable licence, the affected venues would be **backtest countries**
  instead of play-only countries, and Maß 4 would gain check subjects instead of losing
  none. The design does not hang on it — it would only gain. To be checked by the data
  builder, not by me.
- **Whether the thresholds of Maß 4 are reachable at all with endogenous productivity.**
  Unchanged the largest unmeasured risk of the venture. It is no longer a design question
  but a measurement by the backtester at the running core — the acceptance rule now
  stands, so the result can be judged at all.
- **Whether the change of government is reachable within `R` rounds — and it is a
  calibration probe with a ceiling, not a free dial.** `zustimmung_elastizitaet` is class
  4, so if that class's range binds, it is at most 10.000 and approval can move at most
  one-to-one with `realeinkommenshub`. The probe under *Die Zahlenprobe* gives 1 basis
  point for a tariff step and 50 for a budget step; against a distance
  `startzustimmung − zustimmung_wechselschwelle` in ten-thousandths, this decides whether
  counterforce 2 reaches its threshold at all. If it does not, the way out is the
  distance and the step widths, not a larger elasticity — that is the self-player's
  measurement and the reason `parameter.toml` calibrates the three together.
- **Which of the four instruments the resolution condition binds on, per country.** The
  form stands under *Skalen, Auflösung*; the tariff row is binding at four countries by an
  order of magnitude, and at nine it hits the two most trade-dependent ones first. Whether
  a `schrittweite[zoll]` exists that satisfies the condition for Singapore *and* keeps a
  step affordable for the fund is a measurement at the test bench. This is the stricter
  sibling of the condition package 0039 left behind, and both are checked at vintage
  build.

## Was der Architekt neu rechnen muss

Only so that it does not have to be searched for. Everything else in `technik.md` stays
valid.

### Neu aus Paket 0198 — das Realeinkommen als Rechenvorschrift

Five places, none of them a decision. I have not touched `technik.md`.

| was (`technik.md`) | is | affects |
|---|---|---|
| `Realeinkommen` occurs exactly once in your document — in the chain of effect of the unit test in section 9 — and in no formula; T48 declares such a name a finding | The prescription stands in the section *Das Realeinkommen in Gegenkraft 2*: `realeinkommen(l) = bip(l) − politiklast(l)`, and the change `realeinkommenshub(l) = mal_geteilt(−politiklast(l), 10.000, bip(l))` | T48, section 9 |
| T48 counts **22** derived quantities | **25**. New are `politiklast(l)` (class 2), `realeinkommen(l)` (class 2) and `realeinkommenshub(l)` (**class 3**, basis points). All three are functions of the state and read exclusively addresses, `schaden(l, i)` (no. 22), `bip(l)` (no. 9) and `sgn` | T48, `kern::werte` |
| Step 5 without a call count for counterforce 2 | `L` evaluations per round, all in step 5; **94 read accesses**, of which 90 are already read by counterforce 5, four are new (`lies_alt(land.<l>.zustimmung)`). As a formula `2L² + 15L + 2`, thus 94 at `L = 4` and 299 at `L = 9`. Writes: the `L` approval addresses | cost line in section 10 |
| `zustimmung_elastizitaet` has no carrier into the core — `werte::Konstanten` holds six keys and not this one, and `schritt(zustand, aktionen, modus)` has no parameter argument (T10) | Unchanged a gap, and **not one this design may close**: the widening of the signature needs an ADR. Package `0208` covers it. The rule above is written so that it needs exactly one parameter key and no second | T10, T27 |
| Approval as a written but not computed address in the `weltlauf` mask | The rule runs in the `weltlauf` — every input stands in the mask per T18 — and makes approval endogenous there. The change of government is computed and reported and **writes nothing**, so no policy path and no check subject moves | T18, T38 |

**What expressly does not change:** no state address (310 stays 310, and 890 after 0116
and 0118), no new key in `parameter.toml`, no new vintage constant, the count-off step
from T45, the three scale transitions from T50, the **eight** channels, R, the four Maße
and their thresholds.

### Neu aus Paket 0118 — neun Länder, `L_R = 7`, und die Zählregel von Maß 4

I have not touched `technik.md`, and **no number in it is wrong today**: until 0116 has
written the address arithmetic parametrically and the data builder has built the vintage,
`L = 4`, `L_R = 4` and 310 continue to hold. What has to be caught up after that:

| Place | what to do |
|---|---|
| **T59** (count in `L_R`) | The table gains the column `L_R = 7, L_S = 2` — that is the choice made in this package. Check subjects 28, free target series 41, target series 48, flows in the trade block 112, target mask `weltlauf` 328. Each number stands next to it, worked out, in the section *Welche neun Länder*. The columns `L_R = 4` and `L_R = 9` stay; they are the edges. |
| **T58** (classes) | The backtest countries are the USA, China, Germany, Brazil, Japan, India, Chile; play-only countries are Singapore and Saudi Arabia. **An expectation with a condition, not a determination** — it is decided per T63 step 1 at retrieval. Festlegung 3 (rest-of-world remainder per mode) and Festlegung 4 (Giftprobe) are genuinely needed for the first time with this package: from here on there are play-only countries. |
| **T61 rule 5** | **The one finding of this package against another trade's work.** The rule derives the class from the three policy-path series alone. Saudi Arabia is a play-only country for a reason the rule cannot see: its constant exchange-rate **target series**. If `MFS_IR` carries a SAMA policy rate at Stufe 1, the derived and the written class diverge and the vintage build aborts — correctly, but in the wrong place. T62 Folgerung 2 (series 2 without a fallback source) is the same case. Both exclusions lie in the target series and belong where the class is formed. |
| **T62** (data costs) | Three backtest countries at `32(R+1)+6 = 678` and two play-only countries at `5(R+1)+33 = 138` yield **2,310** values at `R = 20`, not the 3,390 of all five as backtest countries. The **ten** new licence points (two per country) are independent of the class and belong, per Folgerung 3, on the same list as the seven open ones. |
| **T37 / tolerance** | The number of check subjects and the tolerance stand from here on as formulas: `3·L_R + (L_R − n) + 1` and `⌊L_R/2⌋`. At `L_R = 4` they give 16 and 2, exactly today's state — that is the compatibility check, and that is why this entry changes nothing today. |
| **Directional accuracy** | It is formed only over the transitions in which the **target series** moves. A transition without measured movement counts neither as a hit nor as a miss; if a series never moves, the subject passes on its level measure alone. Without this line, every constant target series would break by construction. |
| **T16** (slots) | Unchanged from 0119: `3L + L + L + B = 75` at `L = 9`, of which 74 can be filled, because the numéraire's currency slot stays empty. This package's coverage calculation stands on the 74. |
| **T5 / value ranges** | Two edges are genuinely approached for the first time and are to be checked, not assumed: `durchgriff` runs towards 10,000 for Singapore's agriculture (share 0.08 percent, so `N ≈ 0`), and `staatsschuld[JPN]` exceeds 20,000 basis points (222.7 percent in the final year). Both stay within the value range; both belong in the invariant check, because it is the first contact. |

**What this package has expressly not touched:** the 310, the address arithmetic, the
core, `reihen.toml`, `technik.md` and the number of actions per round. The action count
stands as a **tuning knob with a condition and a check** in the section *Die Folge aus
Weg A* and has not been turned.

### Neu aus Paket 0119 — die zweite Schicht, 150 Adressen und zwei Parameter

I have not touched `technik.md`, and no number in it is wrong today: the second layer
arrives together with the nine countries from 0118, and until 0116 has written the
address arithmetic parametrically, `L = 4` and 310 continue to hold. What has to be
caught up after that:

| Place | what to do |
|---|---|
| **T15** (address roster) | A sixth block `boersenplatz`: `5 · B` addresses with `B = 3·(L+1)`, i.e. 150 at `L = 9`. Four fields per venue (`index`, `wechselkurs`, `zins`, `nachahmer`) plus one position slot. Total 890. |
| **T16** (slots) | The slot list gains a fourth kind. `3·L` country×sector + `L` currency + `L` bond + `B` exchange venue = 75 at `L = 9`. The rule „Steckplatz Währung USA bleibt leer" has no counterpart on the new kind — every venue can be filled. |
| **T5** (scale classes) | `index[b]` and `wechselkurs[b]` in class 5, `zins[b]` in class 3, `nachahmer[b]` integer with the same upper bound as `nachahmer[l][s]`. `tiefe[b]` stands on the macroeconomic scale, as does `boersenwert(b)` — the scale boundary to the fund's money lies, as before, between `stufenwert` and `positionswert`. |
| **T27** (`parameter.toml`) | Two new keys: `kippung` and `platzanteil`. `aufschlag` is reused. |
| **T33** (market basket) | The frozen quantity basket gains a third summand: `B` venues with quantity `tiefe[b]` and price `index[b]`. At `L = 9` that is 27 baskets, 9 bonds and 30 venues. Currencies stay out, venues do not — they carry a capitalisation. |
| **T47** (`marktanteil`) | Third summand in `korbbestand`, formed from `boersenwert(b)` and `|stufen| · stufenweite`; without a stake share, because there are no stakes on venues. |
| **T39** (price rules without an address) | `weltzins`, `zielzins(b)`, `zielkurs(b)`, `leitkurs(b)`, `zinsfaktor(b)` and `boersenwert(b)` are functions of the state, not addresses — the same construction as `anleihekurs` and `landespreis`. |
| **Imitator and shock rule** | **The only place where this section points at another formula instead of writing it down.** The surcharge on `index[b]` is to be the same as the one on a country×sector basket, with `nachahmer[b]` in the place of `nachahmer[l][s]` and `boersenwert(b)` in that of `korbwert(l,s)`. If, however, the existing rule reads `kapitalstock[l][s]` directly instead of through the basket value, the transfer does not hold, and then that is a finding against that line — not against the layer. The architect says which of the two cases applies. |
| **T37 / the check subjects** | **Unchanged by this layer.** An exchange venue carries no target series and no trade row and appears in no check subject; the trade block stays at `G·(G−1)·2` over the **territories**, not over the venues. *Corrected on 2026-09-06: here stood „Börsenplätze sind Spielländer (Verweis auf Paket 0117)". A venue is not a country — the line holds without the class assignment, because the layer is a leaf. The check subjects are moved not by this layer but by the country choice from package 0118: 16 → 28.* |
| **Mode `weltlauf`** | The second layer is **not computed**; its `5·B` addresses keep their start values, like the fund block and the imitator counters. The set of addresses written per mode thus stays fixed and does not grow in the `weltlauf`. The `weltlauf` costs `R` world steps, unchanged. |
| **Bound at the policy rate** | Stays as it is (`leitzins ≥ 1 − aufschlag`) and covers `zins[b]` too: `zins[b]` is a repeated mean of values above this bound. **No second bound needed.** |
| **Runtime budget (section 10)** | Per world step, `B` venues are added, at three halvings and one valuation each. No iteration, no search, no trade row — the growth is linear in `B` and hits only the three self-play measures, not the `weltlauf`. |

**The count-off step from T45 comes out even with the new block**, because each of the
`5·B` addresses has its provenance entry in the field table under *Was ein Börsenplatz
trägt*.

### Neu aus Paket 0054 — R fällt von 24 auf 20, das Fenster auf 2001–2021

I have not touched `technik.md`. **The greater part of this list is not a change but a
check:** T40 forms `R = manifest.stuetzstellen − 1` and derives everything else at
runtime, so a changed number in the manifest suffices. What stands here are the places
where `technik.md` has **written a number out**, or where a rule stands on the start year
1997.

| was (`technik.md`) | is | affects |
|---|---|---|
| Example column „bei R = 24": bands 1,000…24,000 / 25,000…28,000 / 31,000…54,000, thirds 1-8 / 9-16 / 17-24, profit threshold 24,000, search-bot game 1,464, Maß-1 cost 9,024 | **bei R = 20**: 1,000…20,000 / 21,000…24,000 / 31,000…50,000, thirds **1-6 / 7-13 / 14-20**, profit threshold **20,000**, search-bot game **1,220**, Maß-1 cost **6,320**. The formulas next to them remain correct, unchanged | T40, table of derived quantities |
| T24: „jede der **31** Sollreihen … über **25** Stützstellen ohne Füllung" | **27** target series over **21** support points. Series 9 is no longer a target series and thus drops out of the prohibition; its path may be filled and marked | T24 |
| T37: three classes, of which `gesetzt` = policy rate (4) | **two classes**: `frei` (23) and `abgeleitet` (4). The class `gesetzt` is dropped, because its only series is no longer a target series. **Instead of an error measure, an invariant holds for the policy rate:** model value ≠ set path is a hard error | T37 |
| T42: rate series are consumer prices, exchange rate, **policy rate**; `S` = 25 | rate series are consumer prices and exchange rate; `S` = **21**, transitions **20** | T42 |
| Series list no. 9, role „Start + Politikpfad + Soll (4, gesetzt)" | **„Start + Politikpfad"**. The row otherwise stays unchanged — dimension, unit, source | section 7 |
| T23 point 8: DE policy rate `exogen_ab = 1999`, „im Prüfjahrgang also Runde 3"; exchange rate `verkettet_ab = 1999` | Both break years lie **before** the window. `exogen_ab_runde = bruchjahr − startjahr + 1` becomes **≤ 0** for them, and for that the rule needs a reading: **`≤ 0` means „gilt von Runde 1 an"**, not „ungültig" and not „nie". The fields stay, because the play vintages before 2001 need them | T23 point 8, T40 |
| T23 point 5: `leitzins_start[l]` = first support point of the policy path | unchanged and correct, now the value of **2001** | T23 point 5 |
| Order of magnitude „5 Gebiete × **25** Jahre × rund 30 Reihen", trade `40 × 25 × 8` | **21** years; the estimate falls accordingly | T23, closing sentence |
| T22/T23: check vintage **1997**–2021 | **2001–2021** | everywhere the start year stands as a number |

#### Nachtrag desselben Tages: die Tabelle oben war nicht vollständig

It came about by my going through the T-numbers that **define** R or the start year. That
finds every rule and no mention. A second pass, this time over every *number* in
`technik.md` instead of every *rule*, produced seven further places; six of them stand
outside a T-block, and exactly for that reason the first pass did not see them. None is a
rule, all are written-out numbers. The two tables together are the list — **the first is
supplemented, not replaced.**

| was (`technik.md`) | is | affects |
|---|---|---|
| **Frontmatter line 12**: „im Prüfjahrgang 1997-2021 ist R = 24, eine Suchbotpartie kostet R × 61 = 1.464 Weltschritte" | „im Prüfjahrgang **2001–2021** ist **R = 20** … **20 × 61 = 1.220**" | frontmatter, key `partie` |
| T23 point 2: „**Sollreihen** für die **31** Reihen aus `spiel.md` plus den Handelsblock" | **27** series | T23 point 2 |
| Section 7, closing sentence of the series list: „Die **31** Sollreihen sind die Zeilen 1, 2, 8, **9**, 10 und 11 (4+12+4+**4**+3+4)" | „Die **27** Sollreihen sind die Zeilen 1, 2, 8, 10 und 11 (**4+12+4+3+4**)". Row 9 drops out of this enumeration, **not** out of the series list — it stays as start and policy path | section 7 |
| T30, check table no. 8: „**31** Sollreihen plus Handelsblock" | **27** | T30 |
| T43: „… fängt eine falsche Implementierung in fünf Runden statt in einer **24**-Runden-Partie" | **20**-Runden-Partie | T43 |
| Section 10, runtime budget: the whole table **and** its recount row stand on `R = 24` | row by row, in the number table below | section 10 |
| Section 13: „der Jahrgangsbau **1997** … **25** Stützstellen ohne Füllung für alle **31** Reihen … und der IFS-Leitzins ist nur durch ein Indiz gestützt" | vintage build **2001**, **21** support points, **27** series. Here more than three numbers change: the half-sentence on the IFS policy rate justifies why the package carries design risk — and as of today the policy rate is no longer a target series. **The package carries less risk than it says there** | section 13 |

**Section 10 in detail, so that it stays a substitution and does not become a
calculation.** Every row is computed afresh from R and **not** scaled from the old table:

| Row | was (R = 24) | is (R = 20) |
|---|---:|---:|
| one game, heuristic bot | 24 | **20** |
| one game, search bot | 1,464 | **1,220** |
| 1,000 games, heuristic bot | 24,000 | **20,000** |
| 1,000 games, search bot | 1,464,000 | **1,220,000** |
| decision density, K=30, one seed | 9,024 | **6,320** |
| decision density, 50 seeds | 451,200 | **316,000** |
| strategy diversity, 126 × 20 | 3,689,280 | **3,074,400** |
| shift of the optimum, two windows | 7,378,560 | **6,148,800** |
| break run, 10,000 random games | 240,000 | **200,000** |
| boundedness, 200 rounds | 200 | **200 — unchanged**, the row checks 200 set rounds and not R |
| backtest, one `weltlauf` | 24 | **20** |
| regression stock, 1,000 games | 24,000 | **20,000** |
| **night run total** | 11,783,264 | **9,759,420** |

The recount row below it thus reads: `Σ(R+1−t)` for `t = 1…20` is `210`, so
`30 × 210 = 6.300` per seed, plus 20 world steps for the carrier game gives
**6,320**; times 50 seeds **316,000**. `1.220 = 20 × 61`,
`3.074.400 = 126 × 20 × 1.220`, `6.148.800` twice that; the three Maße together
**9,539,200**, just as this document computes above. The night run is
`9.539.200 + 200.000 + 200 + 20 + 20.000 = 9.759.420`. `126 = C(9,4)` stands, it does not
hang on R. The two time columns belong to the architect: they follow from the first
column and a `ticks_je_sekunde`, which still does not exist.

**The calibration loop at the end of section 10 also stands on the old number.** A
thousand parameter sets over the full set of Maße cost `1.000 × 9.539.200` = **9.54
billion** world steps instead of 11.52, at the plan value thus around **26.5 hours on one
core and 3.3 on eight**. The shortened night version becomes `10 × 6.320` = **63,200**
for Maß 1 and `126 × 5 × 1.220` = **768,600** for Maß 2. The section's conclusion — at
full width not a night task, shortened night-capable — does not change.

**Two things I have recomputed so that you do not have to.** First, the bound `R ≤ 26`
from T40 holds with room to spare: the band „überlebt" ends at 24,000, the death band
begins at 31,000 — 7,000 milli-rounds of headroom instead of 3,000. Second, the range
test `1.000 … R × 1.000 + 30.000` remains valid and now gives **1,000 … 50,000**.

**And one place outside `technik.md` that I may only name:** `reihen.toml` carries series
9 with `t37_klasse = "gesetzt"` and `rolle_tabelle = "Start + Politikpfad + Soll
(4, gesetzt)"`. Both are wrong as of today. The file belongs to the data builder; this is
a follow-up package for that role, together with the policy-rate path for Germany and
China (see *Offene Entwurfsfragen*). Likewise named and not touched:
`daten/deckungsbefund-1997.md` keeps its name and its content — it measured the 1997
window, and that remains correct.

### Neu aus Paket 0021 — der Schaden in Gegenkraft 5

Five places, none of them a decision. I have not touched `technik.md`; package 0011 is
working in it.

| was (`technik.md`) | is | affects |
|---|---|---|
| T50: „*Wie hoch* der Schaden eines Sektors ist, bleibt Sache von `spiel.md`"; section 12 point 3 reports the gap | The prescription stands in the section *Der Schaden in Gegenkraft 5*: `mal_geteilt(menge, verschiebung, 10.000)` per country and instrument, four lines | T50, section 12 point 3 |
| `handelsvolumen(l)` over both tradable sectors together | plus the sector-wise version `handelsvolumen(l, s)`; its sum over s is the old quantity, the definition does not change | T48 no. 11 |
| `parameter.toml` without a load rate for the Finanzmarktregulierung | new key **`regulierung_last`**, class 3, basis points of GDP per regulation step, calibrated like `gegenlobby_satz` | T27 |
| `lobbypunkte_aus_schaden` with a call site, without a call count | **16 calls per round**, all in step 5; plus **106** read accesses and 16 write accesses, itemised in the section (the 120 of the 2026-09-02 version were wrong, see the Befundabarbeitung) | T50, cost line in section 10 |
| T30 check 6 checks `0 ≤ gegendruck ≤ druck_max`, without any producer holding the bound | The upper bound now stands in the design as `min(druck_max, …)`; the check stays, it is now a probe and not a hope | T30 |

**What expressly does not change:** no state address, the 310, the count-off step from
T45, the three scale transitions from T50, the eight channels, R, the four Maße and their
thresholds. The prescription reads exclusively quantities that `daten/adressen.md`
carries, and three functions from T48.

### Neu aus Paket 0039 — die Zollzeile misst nur noch den Keil

Four places, and the first is the only one where `technik.md` **gains** something instead
of being replaced. I have not touched it.

| was (`technik.md`) | is | affects |
|---|---|---|
| T28 names „der Zollkeil je Gebiet auf dem Weltpreis" without writing it down | `weltpreis_mit_zoll(l,s) = mal_geteilt(welt.preis.<s>, 10.000 + zollstand(l), 10.000)`, in the section *The tariff wedge is multiplicative*. The additive reading cannot be formed against T5 | T28 |
| `preishub(l, s)` as the difference of the sector prices | dropped; in its place come `keilhub(l, s)` and `preishub_zoll(l, s)`, both class 5. `land.<l>.sektor.<s>.preis` is **no longer read** by counterforce 5, `welt.preis.<s>` newly is | T50, T48 |
| cost line with 120 read accesses (from the 2026-09-02 version) | **106**, itemised in the read table. The 120 counted the tariff level twice with 16, although the old tariff row did not read it at all; the 112 of the check finding applied to the old row | T50, cost line in section 10 |
| `durchgriff` is needed in market clearing (step 4) alone | additionally in step 5, for `preishub_zoll`. It remains a vintage constant per T23 point 5 and does not become an address | T23 point 5, T50 |

**And one condition for the vintage build, none for you:** the expression
`mal_geteilt(mal_geteilt(welt.preis_start(s), schrittweite[zoll], 10.000), durchgriff(l,s), 10.000)`
must yield at least 1 for each of the eight country×sector pairs, otherwise the tariff
row is mute there. The number that satisfies this comes from calibration.

### Neu in Fassung 5 — acht Stellen, und keine davon ist eine Zahl

The new section *What a basket is worth* is design and needs from you an incorporation,
not a decision. What of it has to be carried into `technik.md`:

| was (`technik.md`) | is | affects |
|---|---|---|
| T47 uses `korbwert(l, s)` and `positionswert(p)`, formed nowhere | both formed, plus `anleihewert`, `waehrungswert`, `anleihekurs`, `schuld` and `handelsvolumen` | T47 |
| T33: „Modellmarktwerte", the quantity basket without a quantity | market basket = Σ of the 12 `korbwert` + Σ of the 4 `anleihewert`; the quantities are capital stock and debt, the prices sector price, bond price and exchange rate | T33 points 1 and 3 |
| scale boundary in T47 not drawn — **finding 2 of round 6** | `korbwert` stays macroeconomic, the conversion sits once per valuation at the outermost call; the second way (`korbwert` in cents) is ruled out, because T33 values the same basket | T5, T47 |
| T27: `stufenweite` without a meaning | **share in ten-thousandths of the market**, not an amount of money; plus a new key `aufschlag` in basis points | T27 |
| T23 point 5: constants of the vintage are ten `durchgriff` values | plus **`leitzins_start[l]`**, four values, first support point of the policy path from series 9 | T23 point 5 |
| series 3 delivers **one** capital stock per territory, T15 carries **three** per territory | start rule: split over the normalised sector shares, the same rule as for value added; the rank `Datenanker` stays | T23 point 1, series list no. 3 |
| „sieben rundenübergreifende Kanäle"; „gibt es einen **achten** Kanal, und der ist ein Befund" | **acht**; „einen **neunten**" | line 374 (T38 reasoning), T30 check 6 |
| policy rate without a lower bound | lower bound **`1 − aufschlag`**, checked by the vintage build against the historical policy path; it keeps the bond denominator positive | T23, T27, around T40 |

**What expressly does not change:** no number of the fourth version, no state address, R,
the result bands, the four Maße, their thresholds and all cost lines. The count-off step
from T45 comes out even, unchanged.

**And two decisions from your section 12 I accept instead of pulling them back:** the
exclusion rule for support points with `soll = 0` (T42) and the eleven seeds in T46. Both
follow from rules that already stand there; I read one line each and found none I would
set differently. Your observation 2 on the table *Every quantity without a data anchor*
is worked in above — the table now refers to T46 instead of claiming a completeness it
cannot have on its own.

---

**From here on, no governing value stands any more — only the record.** All following
sections — the completed catch-up tables of versions 3 and 4 and the
Befundabarbeitungen — are **dated evidence of completed runs**. The numbers in them stand
on the R that held at the time of their check (`R = 24`, window 1997–2021), and they are
**not** carried forward. The reason is the same one for which the chronicler changes no
old ADRs: a record adapted to the new state proves nothing any more — one could no longer
read off from it what the checker saw then and what the designer answered then. **Whoever
looks for the governing R reads above this line.** What stands below, and what has
changed about it since, is listed row by row by the catch-up table *Neu aus Paket 0054*.

---

### Aus Fassung 4 — vom Architekten am 2026-09-01 erledigt

Stands here only as evidence; all four are carried into `technik.md` version 5 and were
individually recomputed by the checker of round 6. *The numbers of this section hold for
`R = 24`; see the line above.*

| was (`technik.md`) | is | affects |
|---|---|---|
| result band „überlebt" `(R+1)×1.000 … +2.000`, 25,000 … 27,000 | **`(R+1)×1.000 … +3.000`, 25,000 … 28,000** (no more capping) | T40, band table |
| unreachable gaps 24,001 … 24,999 and **27,001** … 30,999 | 24,001 … 24,999 and **28,001** … 30,999 | T34, band check |
| T44: „Die einzige Abweichung von der Ergebnisgröße ist die Kappung" | **dropped** — the branch „überlebt" of `B` and the result quantity are now the same formula; `B`'s own numbers (`e ≤ 2.000`, 25,000 … 28,000) stay correct | T44 |
| `Fondsvermögen = Kasse + bewertete Positionen − Hebel` | **`… + bewertete Beteiligungen − Hebel`**, valued at the exit value | step „settlement", T30 check 2 (invariant test), T44 `v(z)` |

**Two things I have recomputed so that you do not have to.** First: the bound `R ≤ 26`
from T40 remains valid, unchanged — with the wider band it is now exactly the
disjointness condition instead of a generous one; the band therefore costs no round of
game length. Second: the range test `1.000 … R × 1.000 + 30.000` is untouched, because
its upper end comes from the death band.

**And three places that this version makes *lapse* rather than change:** the open
question from section 12 point 3 (stakes, decided above), the class-2 discussion in T44
(it hung on exactly this question) and the addendum in T23 point 1 — it remains correct
but is now duplicated, because the 32 addresses stand in the design table that had
promised them.

### Aus Fassung 3 — vom Architekten am 2026-09-01 erledigt

Stands here only as evidence; nothing of it is open. *The numbers of this section hold
for `R = 24`; the column „is" is the state of 2026-09-01 and not today's. What has taken
their place since stands in the catch-up table **Neu aus Paket 0054**.*

| was | is | affects |
|---|---|---|
| 28 rounds, 1995–2023, 29 support points | **R = 24**, 1997–2021, 25 support points | frontmatter, T22, T23, T24, section 10 |
| search-bot game `28 × 61 = 1.708` | **`24 × 61 = 1.464`** | frontmatter, sections 10, 12 |
| Maß 1 per seed 11,368 | **9,024** (formula corrected, see finding 11) | section 10 |
| Maß 2 4,304,160 / Maß 3 8,608,320 | **3,689,280 / 7,378,560** | section 10 |
| night run 13,789,108 | to be re-summed; the three Maße contribute **11,519,040** | frontmatter, section 10 |
| result range 1,000 … 58,000 | **1,000 … 54,000** | T34 |
| `handelsanteil` | **`durchgriff`**, new formation rule, stays in the shares class | T5, T23 point 5, T25, T28, series list no. 16 |
| `landespreis` undefined | **previous round's sector price**, start value 10,000 | T28, T15 (no new row) |
| backtest as a game | **mode `weltlauf`**, fund subsystem off, instruments exogenous | T30 check 8, T37 |
| Maß-4 acceptance open (section 12) | **16 check subjects, tolerance 2**; trade block as you proposed | T37, section 12 |
| DE `exogen_ab` in round 5 | **round 3** (1999 now lies at the end of round 2) | T23 point 8 |
| 50 seeds „Vorgabe des Prüfstands" | now set in `spiel.md`, together with the summary rule | section 10 |

Newly added and without precedent in version 2: the **stock procedure** (profile →
actions), the **HS92 concordance** and the table **Every quantity without a data
anchor**. All three are design, not architecture — they need from you only an
incorporation, not a decision.

## Befundabarbeitung — Prüfung 0039 vom 2026-09-03, Paket 0055

One finding, `Schwere: gering`, explicitly no reason for a return; the check's verdict was
`geprueft` and remains so. This work-off raises no criterion that had passed.

**Finding 1 — the comparison figure 32.850.000 does not belong to state B: fixed, on the
path that strengthens the table instead of relieving it.** The contradiction is confirmed,
and I re-measured it at both places individually instead of taking it over: the comparison
figure had been formed with a trade volume of 1.5·10^9, while the table in the same section
gives state B a total of 1.4·10^8. The number itself is correct, only for a different state.

**Why path A and not path B.** The reviewer offered both: insert the correct number, or
leave the wrong one standing and write its state next to it. Three reasons for path A, and
the first alone suffices:

1. **The comparison is meant to measure the decision, not illustrate it.** What the base
   term costs is shown only by a comparison in which the old and the new rule see **the
   same** inputs. With the number of a foreign state you compare two rules on two worlds;
   that is not an order of magnitude, it is an anecdote.
2. **The table is built as a regression case**, and a regression case with a number from a
   different state next to it is exactly the trap this package was written against — path B
   merely relabels it instead of clearing it.
3. **The 32.850.000 is not lost anywhere.** It stands with its own state in the example of
   the causal chain under *Warum die Zollzeile nur den Keil misst* and is correct there; a
   second, relabelled copy would have made the reader switch between two worlds at the very
   point where they are supposed to calculate.

Path A demands an input the table did not carry: the sector price of the previous round,
which only the previous version reads. It now stands as a row of its own with the start
value 10.000 from the price-inertia rule and is marked as what it is — the only row of the
table that enters no number in the columns below it.

**Recomputed, not copied.** The reviewer's 8.472.000 I formed step by step myself and
confirm it; the calculation stands in the section so the next reader does not have to take
it on faith. The only degree of freedom is the rounding of the intermediate value
`10.795,2`, and both readings lead to the same contribution — that stands there as well.

**What I did not do.** None of the seven quantities of state A touched, the zero for
state B has stayed the zero, the decision for path 1 and its Maß-2 justification are
untouched, the read-access count appears at no new place, and the second occurrence of
32.850.000 in the causal chain is unchanged. `technik.md`, `daten/adressen.md` and the
calibration numbers are not touched.

## Befundabarbeitung — Prüfung 0021 vom 2026-09-02, Paket 0039

Two findings, `Schwere: mittel` and `gering` respectively, neither a reason for a return.
The acceptance criterion of 0021 was met; this work-off changes nothing about that and
answers the question the reviewer left open.

**Finding 1 — the tariff row grows even when nobody does anything: fixed.** Chosen is
**path 1**, isolating the tariff-wedge share of the price shift. The decomposition is exact
and stands with its derivation in the section *Warum die Zollzeile nur den Keil misst*; it
subtracts exactly the summand that would remain if the tariff level stood still, and leaves
the action share untouched. The justification names Maß 2 as required and gives two further
reasons. Path 2 (reading `hub(l, zoll)`) and path 3 (keeping the base term) are each
rejected with a reason, path 2 additionally with the self-contradiction it would have
created against the row *Die Ordnung, die das Argument trägt*. The reviewer can now compute
`schaden(l, zoll)` for a state without an action: it is **zero**, and without having to
know the form of the tariff wedge. The check stands as a table with two states.

What I found **in addition**, and what strengthens the finding: the old quantity
differenced the sector price, and `technik.md` T8 rebases exactly that price under
hyperinflation. A difference taken across a rebasing is the base change, not the price
shift. In check vintage 1997 the case never occurs; in the play vintages before 1997 it
does. The new version it cannot hit.

**Finding 2 — the read table counts eight accesses that do not happen: fixed, with a
different number.** The counting error is confirmed: the 120 of the previous version
counted `land.<l>.instrument.<i>.stand` twice at 16, although the tariff row of that time
did not read it. The finding's 112 are correctly recomputed for the row as it then stood —
but they are not the number that holds now. After the decision the tariff reads its level
again (twice 16 instead of twice 12), in exchange both sector-price rows drop out (twice 8)
and the two world prices come in: `112 + 8 − 16 + 2 =` **106**. The read table and the
catch-up table both name this number, and the row mapping to the instrument table stands
in its own column, so that it can be recounted rather than merely followed.

**What I did not do.** I have not touched `technik.md`; what needs catching up there is in
the table *Neu aus Paket 0039*. No new state address, no new series, no calibration number.
The condition on `schrittweite[zoll]` stands as a form without a value.

**And a proposal that does not belong in this package but follows from it:** the
formulation of the tariff wedge was written down nowhere until today, although it has stood
in the market clearing since the second version. I have laid it down here because the
damage rule needs it and because T5 admits only one reading. Whether `technik.md` T28
adopts it or has another justification against it is the architect's business — if the
architect objects, it is a finding against this section and not against the tariff row.

## Befundabarbeitung — Prüfung der Runde 6 vom 2026-09-01

**Finding 1, `positionswert(p)` and `korbwert(l, s)` with no rule for how they arise —
fixed, and the finding was right.** The section *What a basket is worth, what a step is and
what a bond costs* defines both, plus `anleihewert`, `waehrungswert` and the `anleihekurs`
that the reviewer named specifically in the fifth step of their proof („für die vier
Anleihe-Steckplätze gibt es nicht einmal einen Preis"). Three decisions are packed into it,
and I name them one by one, because
each could have gone the other way:

1. **The basket hangs on the capital stock, not on value added.** The reason is not
   economics but T33: the frozen quantity basket needs a quantity, and an annual flow is
   not one. The second reason is the chain of effects — if the basket value hung on value
   added, every fluctuation in production would drown out the price change this game
   wants to explain.
2. **A step is a share, not an amount.** That is the decision that saves the state: a
   fixed money amount would require the entry price per slot, hence twenty more
   addresses. As a share, the value follows entirely from today's state, long
   and short are the same formula, and the share that counterforce 1 and the price shock
   read is the same number.
3. **The bond price is a rule, not an address** — the construction T39 already carries for
   `landespreis`. It is the price of a perpetual bond, 10,000 in the start year by
   construction, strictly falling in the interest rate and positive without a cap; the
   bound sits on the policy rate, where it belongs, and the vintage build can check it.

**The order-of-magnitude question the finding raised alongside is answered, but not the
way it asked it.** „Wie groß ein Anteil in Zehntausendsteln überhaupt sein kann"
hangs on the ratio of start capital to market size, and that ratio has exactly one
knob. A second one — an "investable share" of the capital stock — would have been
redundant with the start capital and would have given the calibration a dimension with no
effect. It is therefore not built in; instead, the **two conditions** a permissible
parameter set must satisfy stand under *Offene Entwurfsfragen*, and both can be read off
the test stand.

**And along the way a channel stood out that the finding did not demand.** Once
valuation is a computed step, it becomes visible that *wealth → lobby budget →
instrument → price → valuation → wealth* is a feedback across the round boundary — the
loop this genre dies of. It was not in the channel table. It now stands
as channel 8 with four dampings, three of which grow with success. **That is the expensive
part of this run and the only one that moves a number in `technik.md`:** T30 check 6
and the rationale for T38 speak of „sieben" and of the „achten Kanal als Befund"; both
grow by one.

**Finding 2, `beteiligung_wert` mixes thousand USD and US cents — fixed as far as it
belongs to the design, and the choice between the two paths is made.** The reviewer
assigned the finding to the architect and left two ways out open. The design decides
between them, because only one is compatible with T33: **`korbwert` stays a
macroeconomic quantity**, for the market basket values the same twelve baskets and is
itself macroeconomic. Kept `korbwert` in cents, there would be two scales for one
basket and hence two valuations for one basket — exactly what T47 rules out with „eine
Bewertung, nicht zwei". The conversion therefore sits on the boundary to the fund book
and happens **once, at the outermost call** per valuation, after the shares have been
netted. Which function performs it remains your business; where it sits is design.

The calculation error itself — factor 100,000, cash falling by a hundred thousand times
what the stake wealth rises, way of dying 1 in the same round — is thereby closed at its
root and not by a parenthesis. The reviewer is right that it would have hit Maß 2 by
construction: class 2 could not have passed the first half of the acceptance,
and on the test stand it would have looked like a balance problem.

**The three points from „Geprüft und nicht gezählt", because this run took place anyway.**
The cost statement about `B` is a line of the architect's and not a design question; I do
not touch it. The double keeping of `markt.wert` is resolved by T45's precedence rule, and
I adopt that resolution. The scale convention for `einfluss` (0…100 in the view,
ten-thousandths in storage) is explained and stays as it is — I have re-checked that
`e ≤ 2.000` holds in both units, because `schwelle_e` is stated in the same unit as
`einfluss`.

**What I did not touch:** the reviewer's report to the project manager that the
return counter stands at 3 of 3 with this round and that the table in the work package has
not been kept up since round 3. That is process control and not my role; I write
neither into the work package nor do I decide on `blockiert`.

## Befundabarbeitung — Prüfung der Runde 4 vom 2026-09-01

**Finding 1, `spiel.md` and `technik.md` contradict each other on the slot count — fixed,
and the mistake was mine.** The sentence said „über 15 Runden … `3·ai` Steckplätze" and
thereby mixed `k = 1` and `k = 3`. It now stands in the general form that T43 already
carries: after `5k` rounds `3k·ai` of `15k`, with both cases written out. The check two
paragraphs below (five rounds, three of fifteen) was right the whole time and is no longer
the contradiction to its own sentence. The reviewer reworked the calculation by hand; I
tested it against the same check and arrive at the same number.

**Finding 2, the aggregation of the missing influence is missing — fixed, but not by the
proposed route, and the difference costs two numbers.** The aggregation is adopted as the
reviewer proposes it and as T44 already writes it for `B`: sum over the two countries with
the highest influence, ties broken by `LandId`. With that, both documents compute the same
quantity the same way.

**What I did not adopt is the capping**, and that is the one place where I depart from the
cheapest route. The reviewer explicitly allowed it to stand — it is justified in T44 and
was not a finding. But the same justification strikes back: T44 rejects capping for `B`
because a fund with influence zero in both countries would sit at the capped value 1,000
and an improvement to 60 percent of the threshold would stay **invisible**. For the game
result the same holds one level up: the capping would put every fund with less than one
threshold of total influence on the same value and thereby flatten the lower half of the
outcome space — exactly where Maß 3 seeks its argminimum when no profile in the window
reaches the mandate. That is the case the finding itself names as the plausible one. I
would have built in a blindness the test stand can no longer find, because it is not an
error but a definition.

The capping is not needed anyway: `einfluss` lies in 0 … 100 by design, so every summand
is at most 1,000 by construction, and `fondsvermoegen > 0` holds for every living fund.
The bound now follows from the calculation instead of from a ceiling.
**The price is stated in „Was der Architekt neu rechnen muss" and is twice a number:**
result band 27,000 → 28,000 (T40) and gap bound 27,001 → 28,001 (T34). In return, the
capping difference between `B` and the result quantity disappears entirely — two formulas
become one, and the spot can no longer drift apart. I also reworked what the finding did
not demand: the bands stay disjoint, and T40's bound `R ≤ 26` holds unchanged.

**In addition, two points from „Geprüft und nicht gezählt", because this run took place
anyway.** The reviewer explicitly counted neither as a finding; both were addressed to me,
and both cost a decision here instead of another run.

1. **Do the twelve stakes belong to the fund's assets? Yes** — the section *What the
   fund's assets are, and whether the stakes belong to them* decides it, including
   valuation at exit value. I do not leave that open although it is not a finding: if the
   answer later came out differently, class 2 could fail the first acceptance half of
   Maß 2 by construction, and on the test stand that would look like a balance problem
   although it would be a definition.
2. **The 38 addresses without a provenance entry** (32 from T23 point 1, six without a
   permissible entry kind) now stand in the draft table that says of itself it lists „alle
   übrigen, abschließend". With that the table's promise is true again, and T45 needs no
   new entry kind.

**What I did not touch:** the reviewer's remark to the project manager that a return could
not be closed without a run of the game designer. That is a matter of process control and
not mine; this run is the answer to it.

## Befundabarbeitung — Prüfung der zweiten Fassung vom 2026-08-31

**Finding 1, check vintage 1995 not substantiated — fixed, and the finding was right.** I
retrieved the three US sector-share series myself (2026-09-01): 1997 to 2021, at both
ends as described. The window is 1997–2021, **R = 24**. The most expensive part of the
finding was not the number but its spread into twelve derived quantities; that is why
each of them now stands as a formula in R, and a further shortening of the window is a
substitution instead of a redraft. This is the third finding round on the start vintage,
but not three times the same finding: first a contradiction between frontmatter and text,
then an unsubstantiated number, now a measured one with a formulation that rules out the
error type.

**Finding 2, backtest run not executable — fixed.** Maß 4 runs in mode `weltlauf`: fund
subsystem fully switched off, no return, no way of dying, policy instruments exogenous.
Thus there is neither the zero denominator nor the death in round 3. The second gap —
`markt.wert` without a start value — is closed independently of that: the start value
stands in the table *Every quantity without a data anchor, with its start value* (value
of the start basket at start prices), and in `spielmodus` the rule „fund assets ≤ 0
triggers way of dying 1 in the same round" secures that division by zero never happens.

**Finding 3, `handelsanteil` leaves its value range — fixed, with a fourth solution.**
The reviewer named three ways out; I take none of them unchanged. The coefficient is now
called `durchgriff` and is formed as `10.000·H/(H+N)`: monotone in `H/N`, by construction
in 0…10,000, without capping, without a negative weight on the country price, without
negative prices. The ranking between countries and sectors — the only thing the argument
rests on — is preserved exactly. That its numeric value has no macroeconomic meaning is
stated explicitly right there; the renaming is meant to prevent anyone from taking it for
a measured share.

**Finding 4, profile → actions not defined — fixed.** The **stock procedure** stands
above with step, counter and tie rule: `vi += 3·ai` per round, `vi −= 5` per slot, three
slots per round, largest `vi` wins, tie broken by the smaller id. All three questions of
the finding are answered — no rounding and no drawing, `ai = 0` pushes to the back
instead of forbidding, the bundle size is not part of the profile. For the search bot it
is added how the profile restricts the 60 candidates: via the composition of kinds; the
search runs only over targets and steps.

**Finding 5, Maß 4 without an acceptance rule — fixed.** Sixteen check subjects, only the
free series, a country's three share series as **one** subject, tolerance two. The query
from `technik.md` section 12 is thereby answered (the 23 free ones decide, all 31 are
reported), and the second query on the trade block likewise: the architect's proposal is
adopted, median over the 40 flows, worst fifth reported. Added to this came a gap the
finding did not name and that concerns the same place: for price and exchange-rate series
a MAPE per T8 is not the compared measure at all; for them a mean absolute error on the
annual rate now applies.

**Finding 6, `landespreis` not defined — fixed, with the reading the reviewer calls
well-defined.** `landespreis` is the previous round's sector price, start value 10,000.
The excess function thus stays monotone in the world price, the bisection search from T28
is admissible, and no fixed-point problem arises. The quantity needs no address of its
own — it **is** the sector price, read one step earlier; the price channel this creates
is filed into the channel table above and damped.

**Finding 7, summary over the 50 start values missing — fixed.** The 50 now stand in
`spiel.md`, and the summary too: `Dichte(t, s)` against the median of **the same** 30,
then the mean over the 50 start values. The wrong path the reviewer named — a common
median over 1,500 results from different vintage spreads — is named as such and ruled
out. The total-cost figure now names only the sum of the three Maße, that is, exactly
what this draft itself fixes.

**Finding 8, six profiles without a family action — fixed, by the second variant the
reviewer called cheap.** The six profiles `(0,0,0,a4,a5)` have no strategy core, run
along, are reported, and enter neither of the two acceptance halves of Maß 2. 120
profiles are classified. For Maß 3 all 126 remain selectable — there the vector distance
measures, not the class.

**Finding 9, threshold between two attainable values — fixed.** Maß 3 now demands
**0.4**, that is, exactly one shifted fifth; the value set `{0; 0,4; …; 2,0}` stands next
to it so that the calibration sees what it is aiming at.

**Finding 10, result scale not strictly ordered — fixed.** The band „mandate fulfilled"
ends at `R × 1.000 = 24.000`, the survived failure begins at `(R+1) × 1.000 = 25.000`.
No value carries two meanings, and Maß 2 can be written as `E(p) ≤ 24.000` without the
two halves of the sentence falling apart.

**Finding 11, cost formula one round too short — fixed, and the question behind it
decided.** Maß 1 measures the decision **of round t**: the bundle is set in round `t`,
round `t` is computed, cost `R + 1 − t`. The thirds thus mean the rounds they name. New:
`t` runs to `R` instead of to `R − 1`, because the last round too decides the mandate.
Per start value 9,000 instead of the old formula, plus 24 for the carrier game.

**Finding 12, BACI concordance missing — fixed.** HS92 chapters 01–24 → sector 1, 25–97 →
sector 2, as a table in the manifest. The error of this coarse mapping is named (raw
wood, hides, textile fibres, processed food) and without consequence for the backtest,
because target series and model arise from the same aggregation. With that, `H`, the
trade block and the start matrix are computable.
