---
typ: pruefung
paket: 0255-einundzwanzig-abbruchstellen-stehen-in-keinem-verzeichnis
pruefer: test-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: All three conditions re-derived from the two dateien and the runner's green report; all 21 sites inspected, per-riegel counts recounted independently against SOLLZAHLEN.
befunde: 0
---

# Pruefung 0255 — geprueft

Basis: the two `dateien`, `befunde/uebersetzung-2026-09-08.md` (ergebnis ok; `werte_probe`
Passed in root 27/27 and kern 13/13), and pruefung-0244 (same day) as pre-state record.
Builder's logbook not read; `src/werte.cpp` not needed (see condition 2).

## Condition 1 — one entry point, one record shape: met

`Buch::merke` exists (`kennzeichen.hpp:269-282`), takes the wording the site caught
itself, and rejects an empty wording as a failure (:272-280) — a missing abort cannot
green its riegel. Both entries funnel into the single store `verzeichne` (:501-535);
`bricht_ab_mit` calls it from its catch block (:231). What is stored, compared, and
printed is identical for both paths; `anzahl_zu` counts blind to the entry used (:291).

## Condition 2 — all 21 sites in the ledger, nothing lost: met

Recounted independently: 21 `PRUEFE(hat_abgebrochen(...))` sites, 21 `MERKE` lines, 1:1
(werte_probe.cpp:1532-2247). Per-riegel tally from the call sites:
1/1/1/1/1/2/1/1/2/2/1/1/1/2/2/1 for the 16 new riegel — equal to `SOLLZAHLEN`
(:399-414); old seven unchanged at 6/1/2/1/1/1/2 (14 `BRICHT_AB_MIT` sites, matches
pruefung-0244's record). `static_assert`s pin size == `Riegel::Anzahl` == 23 and
positional order (:430-431). `probe_riegel_vollzaehlig` demands `gezaehlt ==
soll.meldungen` per riegel and prints both numbers (:2272-2283); `pruefe` increments
`fehlgeschlagen`, `main` returns 1 on it (:2340-2343).

No assertion lost: every site inspected; `MERKE` sits strictly under the existing
`PRUEFE` block, negative assertions (`PRUEFE(!enthaelt(...))`) present at every site
whose comment claims one (1537, 1544, 1595, 1727, 1753, 1813, 1883, 1894, 2067-2068,
2078-2079, 2088, 2179, 2187, 2196, 2227-2228, 2241-2242). The 0242 counter still demands
`nennerdecke_angekommen == 2` (:2254). A literal pre-state diff was not available (no
shell); basis is this inspection plus 0244's committed record of the same file.

Freshness at the two distant `MERKE` (2198, 2229): everything between `PRUEFE` and
`MERKE` only reads `letzte_meldung`; `hat_abgebrochen` clears it on entry (:514).

Attribution (16 riegel behind 21 sites) is substantiated by the machine, not trusted:
one riegel per wording means each list must match every same-riegel message and no
foreign one — lumping two wordings or splitting one goes red in `auswerten`'s
eigene/fremde halves, and the run is green with all 35 messages present (exact counts
force arrival). Reading `src/werte.cpp` was therefore unnecessary for the verdict.

Red-when-broken, traced: deleted `MERKE` line → exact count red; deleted site → same
plus completeness half (`kennzeichen.hpp:330-343`); barrier deleted in src → the site's
`PRUEFE(hat_abgebrochen)` red; shortened list → foreign-pair red. Not weakened:
`MELDUNGEN_MAX` 32→64 is a loud-fail buffer (:541-547), not a threshold; the hand-written
name list gave way to generated `riegelliste()` (:197-206) with the forget-net moved to
the two `SOLLZAHLEN` asserts — equivalent trigger on a new enum entry.

## Condition 3 — both numbers printed, larger than 7/14: met

:2280-2282 prints "35 Meldungen aus 23 Riegeln … vor Paket 0255 waren es 14 aus 7";
`auswerten` prints its own totals (`kennzeichen.hpp:448-452`). On a green ctest run this
stdout never reaches the report (output-on-failure); receipt is the printing code plus
the unique rc-0 path — standing pattern since pruefung-0232-zahlwortmessung.

## Searched for and not found

Weakened or skipped tests: no threshold lowered, no `PRUEFE` removed at any of the 21
sites, root test count 27 (26 at 0244's review + `kennzeichen_riegel` from 0251, which
Passed — 0255's edit did not blind it; `RIEGEL_OHNE_ZUSTAND` unchanged, :360-367).
