---
typ: pruefung
paket: 0253-disr-je-land-identifikation-nachziehen
pruefer: daten-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: The Ruecklauf-1 finding is closed at `:152`-`:154` and in row `:262`; a DISR sweep over all three files finds no per-country identification without a query; `reihen.toml` recounted at 62 lines with the duplicate map byte-identical to 2026-09-08.
befunde: 0
---

# Ruecklauf 1 is closed, and the 62-line probe is now pinned line by line

## The finding of round 1 is gone, and the split is warranted

`:152`-`:154` read „`DISR` remains two concepts across two countries". It now reads:

> The anchor the package named is not beaten: every alternative reached by the queries
> above drops a country or the policy character. Whether `DISR` itself is two concepts
> across two countries is open, not answered — the codelist at `:294` identifies none per
> country.

Both clauses check out against what they name. Clause 1 against `:134`-`:138`: `S13BOND`
absent for CHN and BRA, `MMRT` BRA 1964–1981, `FR.INR.LEND` and `FR.INR.RINR` DEU absent —
every row drops a country or carries **no** in the „Policy rate?" column. Clause 2 against
`:294`, read in place: „The interest rate charged by central banks on loans to commercial
banks", generic, no country. „Open, not answered" is what that supports and not more.

Row `:262` carries both bindings and matches the new wording verbatim, in one line, so the
39 rows keep their references. Spot-checked 20 of 39 by landing on the cited range: `9`,
`30`–`33`, `35`–`37`, `39`–`40`, `51`–`52`, `56`, `59`–`61`, `62`–`68`, `70`–`73`, `82`,
`83`, `84`, `90`, `91`, `92`, `93`, `128`–`130`, `134`–`138`, `140`–`150`, `173`–`176`,
`177`–`179` — every one lands on its sentence. Table rows `:229`–`:267` = 39.

## Condition 2: 62, and where the 18 duplicates sit

`Grep -no 'technik\.md|spiel\.md'` over `reihen.toml`: **80 occurrences on 62 distinct
lines.** Duplicates `:473` 4×, `:622` 2×, `:623` 3×, `:1667` 2×, `:1824` 2×, `:1870` 2×,
`:2013` 10× — 18 extras, 80 − 18 = 62, and count mode returns 62 independently. **The map
is byte-identical to the one recorded for 0241 on 2026-09-08**, so no citation was added,
removed or shifted. `:1258` still carries exactly one `spiel.md` although 0252 and 0253
both rewrote that string; `:621`, the line 0253 edited, carries none and neighbours
`:622`/`:623` are unmoved.

## The per-country sweep, over all three files and not the named sites

`Grep -n 'Diskontfenster|discount-window|discount window|Rediskont|Selic|PBoC|Fed-Diskont'`
over the three files. Every live hit is a dated retraction or a quoted history:
`quellenbefund:148` („Until 2026-09-08 this file called…"), `:282`, `:300`-`:301`,
`:312`, `:325`, `:338`-`:339`; `deckungsbefund-1997.md:213`-`:214` („**Zurückgezogen in
Paket 0253**"); `reihen.toml:621` („Zurueckgezogen sind damit zwei Zuschreibungen ohne
Abfrage") and `:1258`. Then `Grep -o 'DISR'` over the target file, all 31 hits: `:30`,
`:31`, `:134` scoped; `:43`-`:80` are coverage and series listings; `:163` is way 2;
`:308` denies the identification; the rest are enumeration rows and revision prose. **No
identification of the instrument for a single country stands anywhere without its query.**

`:311`-`:319` is dated as the package was told: it names the day it describes and says
outright that it asserts nothing about `deckungsbefund-1997.md`'s present content.
`:338`-`:341` speaks of that file only in the past tense with the date on it — the second
option the Ruecklauf allowed, not an assertion about the other lane's present state.

## One defect, not against the criterion, proposed as 0263

`:347` says „78 occurrences on the same 62 line numbers". Measured today: 80. **The 78 is
my own arithmetic, not this package's** — `pruefung-0241-…-2026-09-08.md:23` states it
beside a duplicate map that sums to 80, and `aufgaben/0241:141` copied it forward. The
acceptance names the 62-line count, which holds exactly; a wrong companion number in prose
is not a failed criterion. Proposed as
`aufgaben/0263-die-achtundsiebzig-war-nie-achtundsiebzig.md`.

## What I did not check

Whether `CL_MFS_IR_INDICATOR` 2.1.0 still answers as quoted — the package forbids the
re-fetch and I did it on 2026-09-08 for `0252`. Coverage figures and values: no number in
either file moved, and none was in scope.
