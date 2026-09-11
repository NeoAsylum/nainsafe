---
typ: pruefung
paket: 0294-daten-md-head-count-and-the-mmkt-window-after-0287
pruefer: entwurf-pruefer
datum: 2026-09-11
urteil: geprueft
kriterium_geprueft: all three conditions read against `daten.md:6` and `:193-237`; every figure of the new MMKT clause re-derived from the cited report, and the cut itself proved by the +2 line shift against the `0287` finding's own recorded grep
befunde: 0
---

# `geprueft` — 3 of 3, and no finding

## Condition 1 — the MMKT negative carries its window

`daten.md:221-229` read; the clause now stands as

> `FR.INR.MMKT` -- an identifier filed outside WDI carrying 3,180 country-year rows
> worldwide -- returns no row for the four measured countries **in 1997-2021, the only
> window queried for it** (ibid. `:183-190`, careful form `:188`)

Every element re-derived from the cited report at today's lines:

- filed outside WDI (Africa Development Indicators), `total: 1`, 3,180 country-year rows
  worldwide — `daten/quellenbefund-leitzinspfad.md:183-185` ✓, proven a second time at
  `:272-278` (`pages: 3180`, `topics: [{}]`).
- careful form `:188` = „It carries nothing for these four countries in the window" ✓.
- „the only window queried for it" is the report's own wording at `:108-110`, and its
  enumeration row `:247` names the query behind it: that code over `date=1997:2021`,
  `total: 0` ✓.
- `:211-214` is the Ruecklauf 1 that restored this window twice ✓.

The unwindowed form is gone from the whole spec: `grep -n MMKT` over
`specs/0016-…/` → one hit, `:223`, the sentence above.

## Condition 2 — head figure and section 7 give one answer

`:6` now reads `quellen_brauchbar: 6 unrestricted; no. 7 Eurostat additionally, but
commercially only for EU and EFTA countries`. That is the criterion's second branch: it
says in one clause what it counts. Against the verdict at `:210-215` — locked for
non-EU/EFTA, „may be planned in" for EU and EFTA — same answer, same country classes,
same source number. The six are sections 1–6, whose headings all read *holds*; the „four
sources" of the document title `:11` is the narrower count of what covers the core and
predates this package.

## Condition 3 — nothing else written, `:195-208` untouched

- **Word for word.** `daten/quellenbefund-leitzinspfad-eurostat.md:135-147` quotes both
  spans (licence text, exception list) on 2026-09-09; both quotes still hit exactly
  today's `:195-198` and `:203-208`. Exception list intact — non-EU/EFTA,
  Liechtenstein/Switzerland, Austrian 8-digit CN, third-party copyright.
- **Line arithmetic as proof of the cut.** `grep -n Eurostat daten.md` today →
  6, 193, 200, 211, 213, **231, 234, 413**.
  `pruefung-0287-…-2026-09-10.md:18` recorded 193, 200, 211, 213, **229, 232, 411** the
  day before. Nothing moved at or above `:213`; everything below shifted by exactly +2.
  The two added lines therefore sit inside the corrected-history paragraph — the MMKT
  clause. No insertion or deletion anywhere else in the file.
- The rest of that paragraph is unchanged in wording (five topic-7 codes
  `DPST/LEND/LNDP/RINR/RISK`, `MFS_IR/9.0.0/DEU.*.A` ten MFI rates plus `S13BOND`,
  `DEU.DISR_RT_PT_A_PT.A` empty).
- `grep -n` for `0287|0293|0294` in `daten.md` → one hit, `:217`, the `0287` mark. No new
  package mark was written. Gap 1 at `:413` carries its 2026-09-10 wording unchanged.

## What I searched for and did not find

- **A downstream document still carrying the unwindowed negative.**
  `daten/reihen.toml:1258` — series 9, the open item — already reads „FR.INR.MMKT traegt
  denselben Namensanfang von ausserhalb des Themas … fuer die vier Laender im Fenster
  1997 bis 2021 allerdings leer". Spec, report and series file now agree. Nothing is left
  over, so no proposal.
- **A script reading `quellen_brauchbar` as an integer**, which prose would break.
  `Grep quellen_brauchbar` over the repo: no reader anywhere; only
  `agents/rollen/datenkurator.md:80` (the template, `<Anzahl …>`) and copies of the
  document itself. The criterion admitted this branch expressly.
- **„unrestricted" as a claim about source 6.** Our World in Data's licence holds; its
  restriction is the third-party terms of the underlying data, not a scope carve-out like
  Eurostat's. The word is the criterion's own — judging it would be judging the criterion.

No proposal this run.
