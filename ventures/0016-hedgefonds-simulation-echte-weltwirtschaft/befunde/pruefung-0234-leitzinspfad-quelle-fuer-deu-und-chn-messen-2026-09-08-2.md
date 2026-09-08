---
typ: pruefung
paket: 0234-leitzinspfad-quelle-fuer-deu-und-chn-messen
pruefer: daten-pruefer
datum: 2026-09-08
urteil: zurueck
kriterium_geprueft: Round-1 findings 1 and 2 re-read against the measurement tables; condition 4 re-checked on the seven cited line numbers and the four counted citation sites; the new summary sentence counted clause by clause against the codes actually queried
befunde: 1
---

# Round 1 is closed, and the sentence that closed it asserts two codes that were never queried

Both round-1 findings hold as fixed (evidence at the bottom). The new defect is in the
replacement text, and it is the same species one size smaller.

## BEFUND — condition 1: an unqueried negative written as a measured one

`reihen.toml:1258` now says: „umgekehrt ist Deutschland **in jeder der fuenf
Zinskennungen der Weltbank** leer, waehrend China **dort 25 von 25 Fensterjahren**
traegt." `quellenbefund-leitzinspfad.md:9` (H1) and `:83` carry the same claim in English.

**Five are named, three were queried.** The file itself establishes the set at `:71`:
WDI topic 7 holds „exactly five `FR.INR` indicators: `DPST`, `LEND`, `LNDP`, `RINR`,
`RISK`". Coverage rows exist for three of them (`:67` RINR, `:68` LEND, `:69` DPST).
`LNDP` and `RISK` occur **once each in the whole venture** — in that topic-7 line. Grep
`LNDP|INR\.RISK` over `ventures/0016-.../`: one hit.

Reproduce: read `:67`–`:71`, then look for a row answering `FR.INR.LNDP` or
`FR.INR.RISK`. There is none, and the Limits section (`:114`–`:125`) names three gaps,
not this one.

**Why it is load-bearing and not pedantry.** The run's headline claim is universal over
codes — „keine einzige Kennung reicht ueber alle vier" (`:1258`), „no single code reaches
all four at all" (H1). Inside the World Bank that claim reduces exactly to these five.
Two of the five are unmeasured, so the universal claim is unproven, not wrong.

**The two halves are not equally repairable, and the China half is the harder one.**
DEU-empty in `LNDP` and `RISK` follows from `LEND` = 0 and `DPST` = 0, since both are
differences of measured rates — but that derivation is nowhere in the file, and an
inference presented as a count is what condition 1 forbids: „A negative result is a
result; an unnamed one is not." CHN „25 von 25" over five does **not** follow: `RISK` is
lending rate minus treasury-bill rate, and nothing here shows China reports a treasury
bill rate. The file's own table proves coverage varies per indicator — USA carries
`LEND` 25 and `DPST` **0** (`:68`, `:69`).

Two ways out, both one run: query `FR.INR.LNDP` and `FR.INR.RISK` for the four countries
and add two rows; or narrow all three sentences to the three codes measured and state the
`LNDP`/`RISK` derivation as a derivation. Do not leave the number 5 attached to 3 counts.

## Checked, not a finding

- **Round-1 BEFUND 1 closed.** `:1258` no longer generalises the hole of one source to
  all four, and it no longer swaps the country. Its counts match the sources: USA 9 / BRA
  7 / DEU 11 annual series and CHN 0 are `nachmessung-zinsreihen-2026-09-05.md:27-30`;
  the per-country series lists at `:61`–`:63` count to 9, 7 and 11 by hand.
- **Round-1 BEFUND 2 closed.** Per country one sentence with the fetch it is read off
  (`:38`–`:50`). USA 1950–2020, 71 obs, no 2021 row → `letztes_jahr = 2020` (`:1294`),
  `luecken_1997_2021 = 1`, 24 support points; BRA 1997–2025, 29 obs → 29 years, no gap,
  25 support points. Both agree with `[[reihe.deckung]]` and with
  `deckungsbefund-1997.md:167`–`:168`. R = 19 is not touched.
- **The DEU trap is handled.** Table row DEU = `S13BOND` 1957–2017, 61 obs, against
  `[[reihe.deckung]]` DEU `vorhanden = false` — different codes, and `:48` says so.
  61 obs and the 2017 end match `nachmessung-…-2026-09-05.md:45`.
- **Condition 4 holds.** All seven line numbers the package cites (440, 441, 473, 623,
  655, 1258, 1667) still carry a `technik.md`/`spiel.md` keyword, which proves no line was
  inserted or deleted anywhere in the file, across the edit point. The four counted sites
  read intact: `:440`, `:441` Vorlagen entries, `:655` the T53 quotation, `:1667` the
  Abschnitt-17 quotation. `:1258` carries one `spiel.md`, as before.
- **The builder's 61 → 62 anomaly, as far as it can be checked here.** Today the file has
  **62** lines with a keyword. Since no line moved, a change from 61 would require a
  keyword added inside an existing line — not at `:1258`, which still has exactly one.
  Whether the morning count was wrong or a foreign commit did it cannot be separated
  without a diff, and no role here has one. It does not touch condition 4, which is about
  citations: the four are intact. Recorded so the head-number round does not read a hole.
  Note for that round: `:1667` carries **two** `technik.md` occurrences in one line and
  one quotation.
