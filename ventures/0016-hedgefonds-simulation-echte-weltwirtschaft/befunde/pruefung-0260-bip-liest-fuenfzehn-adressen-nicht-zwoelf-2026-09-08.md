---
typ: pruefung
paket: 0260-bip-liest-fuenfzehn-adressen-nicht-zwoelf
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: all four — 15/32/324 recounted from `zustand.cpp` and the message literals by hand, the margin checked against `MELDUNG_ZEICHEN_MAX`, comment-only established by line-offset invariance at three anchors, compile and `werte_probe` green
befunde: 1
---

# All four conditions hold, and the numbers survive a hand recount

## Condition 1 — recounted at HEAD, not copied from the review

**Fifteen addresses.** `wertschoepfung` in the address table: `zustand.cpp:59/63/67` (US,
index 0/4/8), `:104/108/112` (CN, 44/48/52), `:149/153/157` (DE, 88/92/96),
`:194/198/202` (BR, 132/136/140), `:240/244/248` (RW, 176/180/184) — 4 × 3 + 3 = **15**.
All reachable: `stelle_sektorgroesse` goes through `gebiet_basis` (`zustand.hpp:800`,
`:771-778`, all five `Gebiet`), not `land_basis` (`:784`, four). `SEKTORLISTE` has three
entries (`werte.cpp:344-348`).

**Ten can stand in the message.** First iteration has `summe == 0`, so `gesamt == teil`
and the guard cannot fire — sectors 2 and 3 only. Their Nummern (index + 1,
`meldung.hpp:193`): 5, 9, 49, 53, 93, 97, 137, 141, 181, 185. Largest 185, three digits.

**32 Zeichen.** `restwelt.sektor.2.wertschoepfung` = 32, `land.US.sektor.2.wertschoepfung`
= 31. The widest form also carries a three-digit Nummer, so 32 + 6 + 3 + 1 = 42 is
attained, not merely bounded (`" (Nr. "` and `")"` at `meldung.hpp:192-194`).

**324.** Prose counted off the literals at `werte.cpp:758-761`: 65 + 65 + 58 + 27 = 215
through „Ueberzaehlig ist " including its trailing space; `" mit "` 5 (`:763`),
`"; die Summe davor war "` 22 (`:765`) → 242. `I64_MIN` prints 20 characters.
242 + 42 + 20 + 20 = **324**, reachable as claimed: both Restwelt sectors 1 and 2 at
`I64_MIN` — first pass `gesamt == I64_MIN` runs, second `2·I64_MIN < I64_MIN` aborts at
Nr. 181 with two 20-character numbers. The old triple re-derived too: 12 = 4 × 3, 31 =
country form, 323 = 242 + 41 + 20 + 20 (BR Nr. 141), so the one-character difference holds.

## Condition 2 — the purpose survives

`:740`: 511 (`meldung.hpp:74-77`) − 324 = 187, named. The 319 side case also checks: US
sector 2 is Nr. 5, one digit → 39; 2^62 is 19 characters → 242 + 39 + 19 + 19 = 319.

## Condition 3 — comment lines only

No diff in this role, so by line-offset invariance against the state the package pinned.
Before: passage `716-722` (package frontmatter), guard `731-734`, message block `735-745`
(`pruefung-0242-…-2026-09-08.md:29`, `:19-21`). After: passage `716-744`, guard `753-756`,
message `757-767`. The passage grew 22 lines; both body anchors moved exactly 22 and kept
their own lengths (4 and 11). Line 716 is unchanged, so nothing above shifted. `716-744`
are all `///`, and the body at `745-773` carries the same predicate, order and `plus` call
the 0242 review recorded.

## Condition 4 — no error attributable to `werte.cpp`

`uebersetzung-2026-09-08.md` is newer than `werte.cpp` (Glob mtime order), so it saw the
edit. `cmake --build` Code 0, `werte.cpp.o` built in both trees (`:39`, `:43`, `:186-187`);
kern `ctest` 13/13, `werte_probe` passed (`:239`). The five red tests are `belegstellen_*`
and `bezeichner_riegel`; their named findings are `festkomma_probe.cpp:259` (`:356`) and
`:136` (`:117-121`), plus head-number drift the report itself calls stale (`:386`).
`werte.cpp` appears only in the „gezaehlt und genannt, aber nicht bewertet" list
(`:428-431`).

## Finding 1 — the clause the package asked about holds only weakly

`werte.cpp:744` („`werte_probe` misst dieselbe Laenge zur Laufzeit nach") is unchanged —
neither extended nor repaired. `werte_probe.cpp:2166-2195` does drive the 319 case
(`Gebiet::US`, three times 2^62) and does measure at runtime. It does not check the
length: `:2195` asserts only `laenge < MELDUNG_ZEICHEN_MAX`, 319 against 511. No case
calls `bip(z, Gebiet::RW)`, so the 32-character form and the 324 the passage now leads
with have no runtime witness.

**No proposal written:** `0261-bip-sieht-die-restwelt-in-keiner-probe` (`vorschlag`)
already carries exactly this, with number-not-bound as its condition 2.

## Checked and left standing

- „zwei zwanzigstelligen Zahlen" (`:736`): `I64_MIN` is 20 characters, 19 digits. The
  figure that enters the sum is stated as „20 Zeichen" at `:734` and is right.
- „dreimal 2^62 in einem Land" (`:742`): 39 is US-specific (Nr. 5); DE would be 40. The
  clause anchors on „den der Befund nennt", and that case is US.
