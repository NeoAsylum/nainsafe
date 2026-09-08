---
typ: pruefung
paket: 0241-negativbefunde-an-ihre-abfrage-binden
pruefer: daten-pruefer
datum: 2026-09-08
urteil: zurueck
kriterium_geprueft: Conditions 2 and 3 met and verified mechanically; condition 1 (sweep) leaves three claims that are wider than what was measured, two of them about MMKT — the code the package itself singled out
befunde: 3
---

# Condition 3 holds by count. Condition 1 leaves three claims wider than their query

## What holds

**Condition 3, verified.** `reihen.toml:623`, `[[widerspruch]] nr = 5`, field `entscheidet`
no longer carries `ungemessen` (`Grep -o` for the word: 16 hits, none on `:623`), says the
question is measured since 2026-09-08 and answers no, and points at
`daten/quellenbefund-leitzinspfad.md`. Both `spiel.md` citations on the line resolve:
`spiel.md:2759` carries "The policy rate has not been a target series since 2026-09-03"
verbatim, `spiel.md:3096` is the heading "## Offene Entwurfsfragen".

**The head-number probe is unmoved: 62.** `Grep -no 'technik\.md|spiel\.md'` over
`reihen.toml` gives 78 occurrences on **62 distinct lines**, and the duplicate map is
identical to the one I recorded on 2026-09-08 round 2: `:473` 4×, `:622` 2×, `:623` 3×,
`:1667` 2×, `:1824` 2×, `:1870` 2×, `:2013` 10×. No line inserted, deleted or shifted.

**Condition 2, both places, done.** `:90` narrows MMKT to `total: 0` for the four countries
and names `/v2/indicator/`; the Limits entry raises the outside-topic-7 gap from "not
excluded" to a worked instance. The two newly cited claims check out: `einheitenbefund-pwt-baci.md:302`
enumerates the BACI columns `v q t i j k` verbatim, `:173`–`:174` names the two PDF-locked
PWT files (554025, 554105).

## Finding 1 — the MMKT negative drops its window twice

`quellenbefund-leitzinspfad.md:90`, last sentence: "it carries nothing for USA, DEU, CHN,
BRA". `:109`–`:110`: "it carries no row for these four countries". Measured is `total: 0`
for `date=1997:2021` — stated correctly two lines above at `:90` and again at `:176`.
Unwindowed, these are a third claim, neither the one run nor "does not exist". This is
condition 1's own example, in the code the package singled out.

**Why it is not cosmetic:** `:175` calls a money market rate "the closest thing to a policy
path among all candidates named here", and `FR.INR.MMKT` is IFS line 60b, which for the USA
is populated long before 1997. The unwindowed sentence closes a door only measured shut
inside the window.

**Reproduce:** compare `:90` sentence 2 against `:90` sentence 1. **Not settled by fetch:**
`api.worldbank.org/v2/country/<ISO3|all>/indicator/FR.INR.MMKT` returned HTTP 502 on eight
attempts today (with and without `date`, `source=11`, `/v2/en/`, four-country and
single-country form) while `FR.INR.LEND` for USA answered `total: 25` normally. The 3,180
figure at `:173` is therefore not reproducible today either.

## Finding 2 — "administered PBoC benchmark lending rate" has no source

`:33` (per-country table, "the nearest candidate found") and `:137` characterise
`FR.INR.LEND` for China as the **administered PBoC benchmark lending rate**. Nothing in the
file measured that. `Grep` for `PBoC|PBOC|People's Bank` over the whole `daten/` directory
returns exactly these two lines plus `lizenzbefund-reihen.md:556`, where the People's Bank
of China is listed **`ungeprüft`**.

The World Bank's own metadata declines the identification: `/v2/indicator/FR.INR.LEND`
(retrieved 2026-09-08) gives sourceNote "Lending rate is the bank rate that usually meets
the short- and medium-term financing needs of the private sector… The terms and conditions
attached to these rates differ by country, however, limiting their comparability."
Source organization: IMF IFS. No institution and no instrument per country.

This is a claim about the outside world without a source or retrieval date — CLAUDE.md,
"Sources". It matters because way 2 at `:153` proposes exactly "CHN from `FR.INR.LEND`":
naming the PBoC benchmark makes the candidate look institutionally identified when the
queried source says only "a lending rate". Either name the query that established it or
write what WDI says.

## Finding 3 — the two files now disagree where the edit meant to prevent it

`reihen.toml:1258` says Germany is empty "in allen fuenf Zinskennungen **der Weltbank**".
The befund's parallel sentence (`:120`) says "all five" only after `:106` scopes five to
**topic 7**. After this run's own condition-2 work, `FR.INR.MMKT` is a documented World
Bank rate identifier outside those five — so "the World Bank's five interest-rate
identifiers" is a set this package just proved does not exist. The builder narrowed the
neighbouring clause on that same line ("keine der dort abgefragten Kennungen") for exactly
this reason and left this one. Scope it to topic 7; the citation is untouched by the change.

## Where I looked and found nothing

Every other negative in the file is bound: the `CHN.*.*` wildcard (`:62`–`:68`, arity
argument stated), `MFS_FMP` with its single USA control (`:83`), the 62 dataflow names
screened by name with the pagination caveat (`:84`), PWT by page description (`:92`), BACI
by column enumeration (`:93`), DEU `DISR` from `deckungsbefund-1997.md:174` (`:59`). The
coverage matrix `:114`–`:118` is internally consistent with `:120`–`:122` (widest reach 3
of 4; only BRA carries five) and with `reihen.toml:1258`. No figure changed, as claimed.
