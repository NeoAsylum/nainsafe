---
typ: pruefung
paket: 0198-realeinkommen-als-rechenvorschrift
pruefer: entwurf-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: All three acceptance conditions of 0198; every RHS name resolved against T15/T27/T23/T48, every round named in-formula, pointer and counts verified, all probe numbers recomputed from scratch.
befunde: 2
---

# Pruefung 0198 — geprueft, 2 minor findings (neither touches the acceptance)

**Condition 1 (names).** Every RHS terminal of the four formulas in *Das Realeinkommen in Gegenkraft 2* (spiel.md:2250-2302, 2406) resolved against its set: `bip(l)` = T48 no. 9 (technik.md:2086); `schaden(l,i)` = no. 22 (:2099; all four rows consistent — haushalt/regulierung have menge = bip, leitzins menge = schuld, so staatsschuld/10.000 is exact); `land.<l>.instrument.<i>.stand` and `land.<l>.zustimmung` = T15 (:1134 "political: approval"; parameter.toml:574 names the address literally); `zustimmung_elastizitaet`, `zustimmung_wechselschwelle`, `schrittweite[i]` = T27 (parameter.toml:727/743; the unit sentence quoted at spiel.md:2222 matches parameter.toml:718-719 verbatim); `sgn`/`mal_geteilt`/`min`/`max`/`lies_neu`/`lies_alt` = arithmetic machinery, enumerated in T48's remainder table (technik.md:2220; `sgn` defined :2612). The three new names are declared T48 quantities, classes 2/2/3 (T5-consistent: class 2 over class 2 times 10^4 = class 3); technik.md pickup is named architect work (spiel.md:3283-3298).

**Condition 2 (rounds).** Both ends stand inside the formulas: instrument diff `lies_neu − lies_alt`, `bip` via `lies_neu` (:2254-2256), approval via `lies_alt` in the update. The step-3 hard-error claim matches T39 (technik.md:1329-1330).

**Condition 3 (pointer + counts).** Gegenkraft 2 points at the section (spiel.md:1638) in the same construction as counterforce 5 (:1676). T48-quantity-not-address is stated with counts: 310 stays 310, 890 stays 890, T48 22 → 25 (:102-104, :2397-2398, :3295); 310 = T15 (technik.md:1107), 890 = three-layer sum (spiel.md:1155/1169).

**Numbers recomputed, none via the document's own arithmetic:** probe 440.000·10.000/3.400.000.000 = 1,294 → 1 (T6 half away from zero); the 440.000 continues the 0021 probe (spiel.md:1910); budget row gives hub −50 exact; sign direction step-up → approval falls, relief → rises (Klagen row 2) ✓; read count 94 = 32+12+4+2+40+4 rebuilt from T48's formulas plus T15's trade block 5·4·2, formula 2L²+15L+2 → 94/299 with trade term 2L(L+1) ✓; i128 bound via T5 class-2 example 21.000.000.000 ✓; elasticity ceiling (class 4 ≤ 10.000 → at most 1:1 with hub) ✓; T38 mask carries approval and every input, "computed and reported, writes nothing" is T38 (technik.md:1356-1383) ✓; Maß-4 exemption = data-curator gap 4 (daten.md:409) ✓; 16 → 28 check subjects (:93) ✓.

**Finding 1 (minor, dead quote).** spiel.md:2427 quotes T38 as „nur Zustimmung und Regierungswechsel"; technik.md:1379 reads English since the §4 translation ("of step 5 only approval and change of government run"). Substance identical, quote not greppable. Same class as 0200/0222, but the site is spiel.md prose outside belegstellen_riegel's scan set — proposal 0223.

**Finding 2 (minor, overstated invariant).** spiel.md:2372-2379: an instrument that goes up and comes back "leaves approval where it was … cancel exactly if the quantity and bip are unchanged". False at the clamps: start approval 9.990, elastizitaet 10.000, budget step down then up → min(10.000, 9.990+50) = 10.000, then 10.000−50 = 9.950 ≠ 9.990. The missing premise is approval inside 0…10.000 at both ends. The rule itself is unaffected; a Prüfstand test written from the sentence would assert wrongly. Also in 0223.

**Searched, no finding:** header count "vier Einträge unter Was bewusst fehlt" (3 new :3052/:3058/:3061 plus the sharpened :3042 — consistent); architect row 5 "mask per T18" (T18 does bind mask writes, technik.md:1291-1292); §9 test chain still says Preis → Realeinkommen (named as architect follow-up, row 1); the four damage-table rows against T48's four lines; class arithmetic of the approval update; channel-2 row and explanation (:771, :798-805); the corrected "It costs" paragraph (old promise preserved in quotes; politiklast(DE) = 0 under a foreign step follows from own-instruments-only); existence of the cited 0197 finding; the 8-line measurement's checkable parts (daten.md 1 hit, technik.md 1 hit — exact).
