---
typ: daten
idee: 0016-hedgefonds-simulation-echte-weltwirtschaft
erstellt: 2026-08-31
quellen_geprueft: 13
quellen_brauchbar: 6
sperrfrage: geloest
empfehlung: World Bank WDI (CC BY 4.0) as the core, IMF statistical data for interest rate, exchange rate and public finances, CEPII BACI (Etalab 2.0) for bilateral trade flows, Penn World Table 11.0 (CC BY 4.0) for productivity and price levels
---

# Yes: Four sources permit, in their exact wording, embedding the data in a sold product and shipping it with it -- and they cover the core of the model.

## The blocking question

**Solved.** The World Bank (CC BY 4.0), Penn World Table 11.0 (CC BY 4.0) and CEPII BACI
(Etalab Open Licence 2.0) expressly permit reproduction, redistribution and commercial
use; for its statistical data, the IMF in its literal wording permits selling. So no
workaround construction is needed: the game may contain the starting vintages and run
offline, and the fourth check axis from `agentenbau.md` stands open.

It hinges on two conditions that touch the design, not just the legal notice: all four
require attribution **and** the marking of changes -- and an economic model changes data
by construction (aggregation to twelve countries, conversion to integers). The notice
text must name that, not just the source.

What does **not** work is just as clear, and it was the idea's actual open question:
**UN Comtrade must not be shipped in raw form**, and neither may FRED, WTO and WITS. The
way out for the bilateral trade flows is CEPII BACI -- a cleaned version derived from
Comtrade, which stands under a free licence and, by Comtrade's own account, no longer
carries the Comtrade condition. That is the most important single find of this run.

**On the evidence:** `imf.org`, `oecd.org` and `fred.stlouisfed.org` rejected direct page
retrieval with HTTP 403, and `web.archive.org` is unreachable. Where a quotation below
comes from a verbatim search hit rather than from my own page retrieval, that is stated
alongside it. That is weaker evidence, and I mark it as such.

## Sources one by one

### 1. World Bank -- World Development Indicators — **holds**

**Licence in its literal wording:** „The Creative Commons Attribution 4.0 (CC-BY 4.0) license […]
allows users to copy, modify and distribute data in any format for any purpose, including
commercial use. Users are only obligated to give appropriate credit (attribution) and
indicate if they have made any changes, including translations."
(`datacatalog.worldbank.org/public-licenses`, retrieved 2026-08-31)

In addition, because it expressly names redistribution *in a product*: „you are free
to copy, distribute, adapt, display or include the data in other products for commercial
or noncommercial purposes at no cost"
(`data.worldbank.org/summary-terms-of-use`, retrieved 2026-08-31).

The dataset itself names „Creative Commons Attribution 4.0" as its licence
(`datacatalog.worldbank.org/search/dataset/0037712/World-Development-Indicators`,
retrieved 2026-08-31).

**Conditions:** attribution in the form „The World Bank: Dataset name: Data source (if
known)", marking of changes, and the attribution obligation must be passed on to anyone
the data is passed on to. No copyleft, no registration, no bulk prohibition.

**The restriction, and it matters:** „Some datasets and indicators are provided by
third parties, and may not be redistributed or reused without the consent of the original
data provider, or may be subject to additional terms and conditions."
(ibid.) The WDI are a **collection**, not the World Bank's own work throughout. Precisely
the three series this model additionally needs -- sectoral employment (ILO estimate),
tariff rates (from WITS/TRAINS) and parts of the price series (IMF) -- are candidates
for this exception. To do: for each series, read the „Source" field in the indicator
dataset before it is embedded. See **What is unclear**.

**Content:** over 200 countries and territories, over 1,500 indicators, 1960 to 2025,
annual resolution, annual updates (ibid.). Covers GDP, population, inflation, trade
volume, value added by coarse sector breakdown.

**Verdict:** core of the product. Best combination of licence, breadth and length.

### 2. IMF -- WEO, IFS, DOTS — **holds, with one condition to re-read**

**Licence in its literal wording:** „Users may download, extract, copy, create derivative works,
publish, distribute, and sell Data obtained from IMF Sites, including for commercial
purposes." (`imf.org/en/about/copyright-and-terms`) — **Evidence note:** direct retrieval
of the page was rejected on 2026-08-31 with HTTP 403; the sentence is evidenced via a
literal search for exactly this string, not via my own page retrieval. To be re-read in
the full text before the build.

**Conditions** (from the same source): on redistribution the data must appear unchanged
and correctly with the IMF as source; whoever **materially transforms** the data must
state that expressly; and: „If IMF Data is sold by Users as a standalone product,
sellers must inform purchasers that the Data is available free of charge from the IMF."

**Both readings of this last clause, because it is ambiguous:** (a) A game is not a
„standalone product" made of IMF data but a simulation in which the data are seeds --
then the notice does not apply. (b) The buyer receives the data bundled and pays for
it -- then the notice applies. The clause costs one sentence in the legal notice; I
choose no reading but recommend writing the sentence. It is cheaper than the question.

**Content:** WEO delivers government debt and fiscal balance in percent of GDP for nearly
all member countries, updated twice a year and **revised retroactively**; IFS delivers
policy rates, money supply and exchange rates in monthly and quarterly resolution; DOTS
delivers bilateral trade aggregates (country against country, without commodity
breakdown) in monthly and quarterly resolution. Exactly the three quantities the WDI
lack or have gaps in.

**Verdict:** second load-bearing pillar, indispensable for interest rate, exchange rate
and public finances. The revision practice is a design problem, not a licence problem:
whoever wants to run the fourth check axis against WEO series must freeze the retrieval
state, or the target value of the regression test changes away underneath the test.

### 3. CEPII -- BACI and Gravity — **holds, and unties the Comtrade knot**

**Licence in its literal wording:** „BACI is distributed under the Etalab Open Licence 2.0, which
means that any use is authorized, provided the source is mentionned."
(`cepii.fr/DATA_DOWNLOAD/baci/doc/FAQ_BACI.html`, retrieved 2026-08-31; typo in the
original)

**Conditions:** attribution („name BACI and the CEPII, ideally with a link to the
website", ibid.). The Etalab Open Licence 2.0 is compatible with CC BY 4.0 and knows
no copyleft and no bulk prohibition.

**Content:** bilateral trade flows country-country-product in HS nomenclature, annual,
geographic coverage as Comtrade, annual update from January; the latest year is still
being revised (ibid.).

**Why this is the find:** BACI is derived from UN Comtrade, and Comtrade itself writes
about derived holdings: „Transformed data from UN Comtrade is no longer
subject to copyright restrictions" and expressly names „calculating new indicators" and
„performing geographic and other aggregations" as qualifying transformations
(`uncomtrade.org/docs/faqs-on-use-and-re-dissemination/`, retrieved
2026-08-31). BACI is exactly that: harmonised, mirrored, cleaned. That renders the
idea's worry („untersagt eine davon die Weitergabe im Bulk, muss der Kern auf
Weltbank-Aggregate zurueckgeschnitten werden") moot -- the foreign-trade part may be
built in its fine-grained form.

**Verdict:** recommended for bilateral flows. Aggregated to twelve countries and six
sectors, only a fraction of the dataset remains anyway.

### 4. Penn World Table 11.0 — **holds**

**Licence in its literal wording:** „Creative Commons Attribution 4.0 International License", with
the prescribed citation „Feenstra, Robert C., Robert Inklaar and Marcel P. Timmer
(2015), 'The Next Generation of the Penn World Table' American Economic Review, 105(10),
3150-3182" (`rug.nl/ggdc/productivity/pwt/`, retrieved 2026-08-31).

**Conditions:** attribution including the citation named above, marking of changes. No
copyleft.

**Content:** 185 countries, **1950 to 2023**, annual; purchasing-power-adjusted levels of
output, capital stock, labour input, productivity and price levels. Version 11.0
published on 2025-10-07.

**Verdict:** recommended as a complement. It can do two things WDI and IMF cannot:
it reaches back to 1950 (more selectable starting vintages, hence more sellable content
under the idea's expansion model) and it delivers **productivity and price levels in
cross-country comparison** -- the quantities from which a trade model can form
comparative advantages in the first place.

### 5. Destatis — **holds, but is dispensable here**

**Licence in its literal wording:** „Data licence Germany – attribution – version 2.0"; the data
may „be copied, printed, presented, altered, processed and transmitted to third
parties", „be merged with own data and with the data of others and be combined to form new
and independent datasets" and „be integrated in internal and external business processes,
products and applications" (`govdata.de/dl-de/by-2-0`, retrieved 2026-08-31; version of
the licence text Destatis points to). Commercial and non-commercial use are treated
equally.

**Conditions:** source note with the provider's name, the addition „Data licence Germany
– attribution – Version 2.0" or „dl-de/by-2-0" and a reference to the dataset
(URI); changes are to be marked in the source note (ibid.).
Destatis itself: „© Statistisches Bundesamt (Destatis), 2026. Data licence Germany -
attribution - version 2.0" (`destatis.de/EN/Service/Legal-Notice/_node.html`, retrieved
2026-08-31).

**Content:** Germany, deeply broken down, mostly annual and quarterly.

**Verdict:** flawless on the licence side, but a twelve-country model needs **one** data
base with a uniform delimitation, not twelve national ones. Draw on it only if Germany
is built out as a detail case.

### 6. Our World in Data — **holds formally, but adds nothing of its own**

**Licence in its literal wording:** CC BY; „You do not need permission from us, and we do not sign
copyright release forms, provided that you cite us appropriately."
(`ourworldindata.org/faqs`, retrieved 2026-08-31)

**The restriction is the whole point:** „Most of the data on Our World in Data comes
from third-party providers (such as the WHO, UN, and World Bank) and is subject to the
license terms of those providers. You should always check their license before reusing or
republishing the data." (ibid.)

**Verdict:** no independent route. Whoever fetches economic data here in truth fetches
World Bank or IMF data and must check their conditions anyway -- so go direct right away.
Usable at most as a finding aid, not as a supplier.

### 7. Eurostat — **EU and EFTA countries only**

**Licence in its literal wording:** „Reuse of statistical data, metadata, publications, and other
dissemination tools published on this website for commercial or non-commercial purposes is
authorised provided the source is acknowledged."
(`ec.europa.eu/eurostat/en/help/copyright-notice`, retrieved 2026-08-31)

**Conditions:** attribution in the form „Source: [DOI number of the Eurostat dataset],
[access date]" (ibid.).

**The exceptions decide here, and they hit exactly this cut.** Excluded from commercial
reuse and usable only non-commercially are, among others: data for non-EU/EFTA countries
(the page names the USA, Japan and China as examples), trade data with Liechtenstein and
Switzerland as reporting country, Austrian trade data at the eight-digit CN level, and
co-publications carrying third-party copyright
(ibid.).

**Verdict, and it is scoped, not blanket.** For the model's **non-EU/EFTA countries**
Eurostat is locked -- commercial reuse is not permitted there, and that is the case the
assignment warns about: a perfect-looking licence, a gap across half the world. **For the
model's EU and EFTA countries a Eurostat series may be planned in**, under the conditions
and in the attribution form at `:200-208`. It is source no. 7 with its conditions read in
wording; using it there needs nothing further.

**Corrected 2026-09-10 (package `0287`).** Until then this section carried a blanket
„Do not plan it in", on the ground that the EU countries are covered anyway, „and there
WDI and IMF have the same quantities without a special rule". That ground is measured
false for the one quantity the critical path hangs on.
`daten/quellenbefund-leitzinspfad.md` (package `0234`, revised `0241`/`0252`/`0253`)
measured for Germany over 1997-2021: **0** window years in all five `FR.INR` interest-rate
indicators of WDI topic 7 (`DPST`, `LEND`, `LNDP`, `RINR`, `RISK`), and `FR.INR.MMKT`
returns no row at all for the four measured countries; at the IMF, `MFS_IR/9.0.0/DEU.*.A`
yields ten MFI bank rates plus `S13BOND` -- a bond yield ending 2017 -- and
`DEU.DISR_RT_PT_A_PT.A` is empty. For most quantities the old sentence holds; for the
interest-rate path it does not.

**What this verdict does not decide:** *whether* a Eurostat series is admissible for the
EU countries is answered here, *which* one is not. Package `0280`
(`daten/quellenbefund-leitzinspfad-eurostat.md`, 2026-09-09) found **no policy rate** at
Eurostat -- `irt_st_a?geo=EA` is gapless over 21/21 window years 2001-2021 but a
**euro-area money-market rate**, and `irt_lt_mcby_a?geo=DE` is gapless but a **bond
yield**. What series 9 gets, and whether the answer lies outside the vetted sources and
therefore behind a gate, is a separate decision.

### 8. OECD — **unresolved, do not plan in**

**Licence, literal wording as far as evidenced:** the standard licence for content from 2024-07-01
on is CC BY 4.0; for older content the OECD terms of use apply, which permit using,
copying and distributing content „for commercial and non-commercial purposes without
seeking authorisation from the OECD", with citation in the form „[OECD (year), Title,
URL]". Adaptations additionally require a disclaimer („This is an
adaptation of an original work by the OECD…").
(`oecd.org/en/about/terms-conditions.html` and
`oecd.org/en/about/oecd-open-by-default-policy.html`) — **Evidence note:** both pages
rejected direct retrieval on 2026-08-31 with HTTP 403; the wordings come from search
hits, not from my own page retrieval.

**The ambiguity, and therefore the source drops out for now:** the permission clause
quoted speaks throughout of **„written content"** -- publications and texts. Whether
statistical databases fall under that does not follow from what I could evidence. Two
readings: (a) the press release of July 2024 speaks expressly of „OECD data,
publications and analysis" becoming freely accessible -- then data is included. (b) The
terms distinguish „written content" from data, and for data something else applies that
I did not find. By this role's rule, a source without a licence quotation in its literal
wording counts as unchecked, not as permitted.

**Verdict:** unchecked. Do not take into the design. If the architect needs sectoral
depth that only the OECD has (STAN, input-output tables), that is a separate, small
clarification assignment -- no reason to hang the core on it.

### 9. UNCTAD / UNCTADstat — **contradictory, do not plan in**

**Two statements that bite each other.** On the copyright page itself stands the
UN standard clause: „None of the materials provided on this web site may be used,
reproduced or transmitted, in whole or in part, in any form or by any means, electronic or
mechanical, including photocopying, recording or the use of any information storage and
retrieval system" without written permission
(`unctadstat.unctad.org/EN/Copyright.html`, retrieved 2026-08-31); the same page at the
same time points to a Creative Commons term of use, and the UNCTAD Data Hub states
CC BY 3.0 IGO with the statement that data may be freely copied and redistributed,
provided the Data Hub is named as the source.

**Verdict:** both readings stand side by side on the same page; I choose neither. As
long as that is not resolved, the source counts as unchecked. Nor is it needed --
what UNCTAD delivers in trade data, BACI covers under a clear licence.

### 10. UN Comtrade — **negative for raw data**

**Licence in its literal wording:** „any copying, automated browsing or downloading, redistribution,
publication, or commercial exploitation of any material contained on or otherwise made
available to you on United Nations COMTRADE is strictly prohibited without the prior
written permission" (`comtrade.un.org/licenseagreement.html`, section 5 „Usage",
retrieved 2026-08-31).

**The newer practice beside it, because it sounds milder and is not:** whoever passes
original data on to non-subscribers and exceeds 100,000 records in doing so „must
pay the 'license to distribute' fee" **in addition** to an active premium subscription;
and expressly: „There is no distinction between profit and non-profit when it comes to
re-dissemination." (`uncomtrade.org/docs/faqs-on-use-and-re-dissemination/`, retrieved
2026-08-31).

**Verdict:** **negative** for embedded raw data -- a running subscription plus fee would
violate house rule 1 and would be senseless anyway for a product at 24.99 EUR.
The way out is the transformed version (CEPII BACI, no. 3), which Comtrade itself
releases. Comtrade thus remains **indirectly** the basis of the foreign-trade part,
without its conditions touching the product.

### 11. FRED (Federal Reserve Bank of St. Louis) — **negative**

**Licence in its literal wording, as far as evidenced:** series with a copyright notice belong to
third parties; before any use beyond personal use, the rights holder's permission must
be obtained, and commercial redistribution of copyrighted series is not permitted
without the rights holder's consent; users may not remove or alter proprietary notices
(`fred.stlouisfed.org/legal` and `fred.stlouisfed.org/docs/api/terms_of_use.html`) —
**Evidence note:** direct retrieval of both pages was rejected on 2026-08-31 with
HTTP 403; the terms come from search hits.

**Verdict:** **negative for embedding.** FRED is an aggregator: the licence status
hangs on the individual series, not on FRED, and must be clarified per series -- exactly
the work no agent should carry, and it would arise anew with every data update.
US quantities are delivered by WDI and IMF under a clear licence.

### 12. WTO — **negative**

**Licence in its literal wording:** „Unrestricted official WTO documents and legal texts are free for
public use"; other materials may be used non-commercially if the WTO is named and
informed; „Commercial use of materials from the website requires written
permission from the WTO." No Creative Commons licence is offered.
(`wto.org/english/info_e/copyrights_permissions_e.htm`, retrieved 2026-08-31)

**Verdict:** **negative.** Written permission is not a path an agent run may take
(house rule 2). That closes the most obvious tariff source -- see the gap
below.

### 13. WITS (World Bank Integrated Trade Solution) — **negative**

**Licence in its literal wording:** WITS passes through its suppliers' conditions. On UN Comtrade:
data „may not be re-disseminated in any form without written permission of the United
Nations Statistics Division (UNSD)". On the WTO database: „re-dissemination by third parties
… must be approved by the WTO Secretariat prior to such re-dissemination", and
publications may not be finer than the six-digit HS level. For UNCTAD TRAINS a separate
term of use applies.
(`wits.worldbank.org/WITS/wits/registration/PrintTermsAndCondition.htm`, retrieved
2026-08-31)

**Verdict:** **negative.** That WITS runs under the World Bank's roof does not transfer
the World Bank's CC-BY licence to third-party holdings. Important for the next stage:
World Bank origin is **no** carte blanche; the licence hangs on the dataset, not on the
sender.

## The proposal

**Four sources, with a division of labour:**

| Role in the model | Source | Licence |
|---|---|---|
| GDP, population, inflation, trade volume, coarse sector structure | World Bank WDI | CC BY 4.0 |
| policy rate, exchange rate, government debt, fiscal balance, trade aggregates | IMF (IFS, WEO, DOTS) | own conditions, commercial sale permitted |
| bilateral trade flows by commodity | CEPII BACI | Etalab Open Licence 2.0 |
| productivity, capital stock, price levels, starting vintages from 1950 | Penn World Table 11.0 | CC BY 4.0 |

**What that requires -- attribution, concretely.** All four licences demand it, and three
of four additionally demand the marking of changes. Aggregating to twelve countries and
six sectors and converting to integers is a change. Hence in three places:

1. **A file `LIZENZEN.md` next to the shipped data file**, with, per source: name,
   licence designation, link to the licence text, link to the dataset, retrieval date of
   the data state used and the prescribed citation (for PWT the Feenstra-Inklaar-Timmer
   reference in its literal wording).
2. **In the game itself, on a „Datenquellen" (data sources) page**, reachable from the
   main menu -- not only in a text file, because a buyer looks for the mapping where they
   see the numbers.
3. **One sentence on the processing**, to this effect: *The source data were aggregated
   to twelve countries and six sectors and converted to integer units for the simulation.
   The sources bear no responsibility for this processing.* For the OECD version of this
   notice there would be a prescribed wording -- for the four chosen sources there is
   none; the sense suffices.

**Plus the IMF sentence**, because of the ambiguous clause above: *The IMF statistical
data used are available free of charge from the IMF.* A sentence that closes an open
question is cheaper than the question.

**What is expressly not needed:** no registration, no subscription, no inquiry, no fee --
hence no gate template under house rule 1 for the data. The venture's only known expense
remains the Steam Direct fee from the idea.

**And one construction condition that follows from the licences:** the shipped data state
must be **frozen and stamped with its retrieval date**. Not because of the licence, but
because of the fourth check axis: the IMF revises WEO series retroactively, BACI revises
the latest year in each release, the World Bank updates annually. A regression test
against a target series that changes underneath it is no test. The annual data-update run
from the idea's calculation thus produces a new, independently versioned vintage -- not
an overwrite of the old one.

## What the model needs and what is missing

The idea names twelve countries, six sectors, quarterly rounds and five policy
instruments. Ordered by that:

**Evidenced as available under a load-bearing licence:**

| Quantity | Source | Resolution |
|---|---|---|
| GDP per country | WDI (from 1960), PWT (from 1950) | annual |
| population, employed persons | WDI, PWT | annual |
| inflation / consumer prices | WDI, IMF IFS | annual / monthly |
| policy rate, money supply, exchange rate | IMF IFS | monthly, quarterly |
| government debt, fiscal balance | IMF WEO | annual |
| total trade volume | WDI | annual |
| bilateral trade flows, country-country | IMF DOTS | quarterly |
| bilateral trade flows by commodity | CEPII BACI | annual |
| productivity, capital stock, price level | PWT 11.0 (185 countries, 1950-2023) | annual |

**Four gaps. Each is a design requirement for the game designer, not a side note:**

1. **Six sectors do not exist under a free licence.** WDI delivers the coarse breakdown
   -- agriculture, industry, manufacturing, services, that is four positions, one of
   them a subset of another. Finer breakdowns sit with the OECD (unresolved, no. 8) and
   Eurostat (locked for non-EU countries, no. 7).
   **Requirement:** either lower the sector count to what WDI yields (practically four),
   or carry the finer sectors as a **model construct** that is split out of the coarse
   ones -- then the fourth check axis refers only to the aggregated level, and that
   belongs said openly.
2. **Sectoral prices are missing entirely.** Neither WDI nor PWT delivers sectoral price
   indices in cross-country comparison. PWT delivers price levels per country as a
   whole. **Requirement:** sector prices are an endogenous model quantity without a
   start value from data and **without a target series** -- the backtest cannot check
   them.
3. **Tariffs -- the instrument the game revolves around -- are the weakest spot.** The
   three usual sources (WTO, WITS, UNCTAD TRAINS) are all locked or unresolved. WDI
   carries an aggregated applied tariff rate per country, but it is recognisably derived
   from WITS and could therefore fall under the third-party exception. **Requirement:**
   if only one tariff rate per country is available instead of one per country and
   sector, then the instrument „Zoll auf Sektor 3" is a model construct without a data
   anchor. That is playable, but it is something other than the remaining quantities,
   and the design should not make it look as if it were the same.
4. **Government approval**, the quantity through which the idea's chain of effect runs
   („Realeinkommen -0,4% -> Zustimmung Regierung -1,2"), has **no** counterpart among
   the checked sources. It is a pure model quantity. That is permissible -- but it
   thereby lies outside what the fourth check axis can check, and that is exactly the
   boundary `agentenbau.md` describes.

**And one resolution gap that hits the game design directly:** the idea reckons in
**quarterly rounds**. Only interest rate, exchange rate and the DOTS trade flows are
available quarterly or finer; GDP, population, sector structure, productivity and tariff
are **annual**. The target series of the fourth check axis are thus predominantly annual.
Two paths, both to be decided, and not by me: annual rounds instead of quarterly rounds
-- then the backtest fits exactly, but 60 rounds become 60 years. Or quarterly rounds
with the backtest only on year-ends -- then three of four rounds remain unchecked.
`agentenbau.md` demands the measures in the design, not in the aftermath; this belongs
among them.

## What is unclear

- **Which WDI series fall under the third-party exception.** The World Bank licence is
  unambiguous; the reach of its exception is not. Presumably affected are the
  ILO-modelled employment by sector, the tariff rate derived from WITS and
  IMF-based price series. **To do before the build, not before the evaluation:** for
  each series to be embedded, read the „Source" field in the indicator dataset. Those
  are manageably few series once the game designer has named them -- which is why it is
  their groundwork, not mine.
- **The IMF wording is evidenced only via a literal search**, because `imf.org` rejects
  retrieval with HTTP 403. The same holds for OECD and FRED. The IMF sentence is the only
  one of these the proposal rests on -- it belongs confirmed from the full text before
  the build, say from another network or by the operator.
- **Whether the IMF clause on the „standalone product" applies to a game.** Both readings
  stand above. I recommend the notice sentence because it closes the question instead of
  deciding it. No legal advice.
- **OECD: „written content" or data too?** Unresolved, see no. 8. Only relevant if
  sectoral depth beyond the WDI breakdown is needed.
- **UNCTADstat contradicts itself on its own copyright page.** Unresolved, see no. 9.
  Without consequence for the proposal.
- **The question of personal data arises with none of the four sources** -- they are
  country aggregates throughout. The condition from `agentenbau.md` („echte Institutionen ja,
  echte lebende Personen nein") thus touches not the choice of data but only what names
  the game invents. That is a matter for the game designer and the compliance checker.
- **Not checked, because not commissioned and not needed:** World Bank WITS alternatives
  for tariff data (say the ITC's MacMap), V-Dem or similar policy datasets for the
  approval quantity. Both would be a small add-on assignment if the game designer does
  not want to carry gaps 3 and 4 as a model construct.
