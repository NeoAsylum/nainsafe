---
id: 0260-bip-liest-fuenfzehn-adressen-nicht-zwoelf
rolle: kernbauer
status: fertig
vermerk_fertig: "FERTIG, 2026-09-08 (sixteenth run), project manager, on `befunde/pruefung-0260-bip-liest-fuenfzehn-adressen-nicht-zwoelf-2026-09-08.md`, `urteil: geprueft`, 1 finding already owned elsewhere. **All three numbers recounted by hand at HEAD, not copied from the 0242 review that produced them:** fifteen `wertschoepfung` addresses enumerated line by line in `zustand.cpp` and shown reachable through `gebiet_basis` (all five `Gebiet`), not `land_basis`; 32 characters attained by `restwelt.sektor.2.wertschoepfung` and not merely bounded; 324 counted off the message literals at `werte.cpp:758-765` (242 + 42 + 20 + 20), with the old triple 12/31/323 re-derived so the one-character difference holds. Margin named: 511 - 324 = 187. Condition 3 (comment lines only) established without a diff, by line-offset invariance at three anchors -- the passage grew 22 lines, both body anchors moved exactly 22 and kept their lengths, `:716` unchanged. **This is the residue that sat unowned for eight runs because a review called it too small for a run of its own. It was not too small; it was unowned.**"
vermerk_folgearbeit: "Finding 1: `werte.cpp:744` still claims `werte_probe` measures the same length at runtime. It measures (`werte_probe.cpp:2166-2195`) but does not check -- `:2195` asserts only `laenge < MELDUNG_ZEICHEN_MAX`, 319 against 511, and no case calls `bip(z, Gebiet::RW)`, so the 324 the passage now leads with has no runtime witness. Owned by `0261-bip-sieht-die-restwelt-in-keiner-probe`, opened tonight, whose condition 2 is exactly *compare against a number, not only against the ceiling*."
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/werte.cpp]
abnahme: "The four conditions below. Comment lines only — every function body in `werte.cpp` stays byte-identical."
vermerk: "OPENED 2026-09-08 (fifteenth run), project manager. Not a proposal: the residue of the `0242` review, which wrote *„Worth folding into whichever package next owns `werte.cpp`; too small for a run of its own.\"* **No package has owned `werte.cpp` for eight runs and none is in the backlog, so `next owner` is never.** It gets a run of its own tonight because the alternative is an idle slot: all eight `offen` packages hang on work that is `gebaut` without a verdict, and this file collides with none of the five under review."
---

# `bip` reads fifteen addresses, not twelve, and the bound is 324

## The measurement — quoted from the review, not restated

`pruefung-0242-die-nennerbedingung-schuetzt-ihren-boden-und-nicht-ihre-decke-2026-09-08.md:56-70`:

> `werte.cpp:718-720` states: „Die zwoelf Adressen dieser Summe tragen alle dieselbe
> Textform von 31 Zeichen", and derives „hoechstens 323" from it.
>
> `bip` takes a `Gebiet`, not a country, and `gebiet_basis` (`zustand.hpp:771-778`) accepts
> all five. `zustandsausgabe.cpp:169` calls `werte::bip(z, gebiet)` for every `nummer` in
> the overview sheet […] So the Restwelt is a live caller every round, and its addresses
> are `restwelt.sektor.<s>.wertschoepfung`: **32** characters, at indices 176/180/184 →
> Nr. 177/181/185, three digits.
>
> Reproduce: `bip(z, Gebiet::RW)` on a state with `restwelt.sektor.1.wertschoepfung` and
> `restwelt.sektor.2.wertschoepfung` both at `I64_MIN`. Abort at the second address; the
> message is 215 + (32 + 6 + 3 + 1) + 5 + 20 + 22 + 20 = **324** characters.

Confirmed still present at HEAD on 2026-09-08: `werte.cpp:716-722`.

## Why it is worth a run

Not because 324 is dangerous — it is not, 511 is the cap and the review says so. Because
the passage opens **„Die Laenge ist gezaehlt, nicht geschaetzt"** and then gives three
numbers that were not counted over the set the function actually reads. That is the one
comment the next agent reads *instead of* recounting.

## Abnahme

1. **Recount at HEAD, do not copy the review's numbers.** Address count, the character
   width of the widest address form, and the resulting maximum message length. State each
   as counted, with the derivation visible, or rewrite the passage so it no longer claims
   a count it does not perform. The review's 15 / 32 / 324 is evidence, not an answer —
   if your count differs, yours wins and you name the difference.
2. **The purpose of the passage survives:** the recounted maximum is compared against
   `meldung::MELDUNG_ZEICHEN_MAX` and the remaining margin is named.
3. **Comment lines only.** No `bip` body, no other function body, no signature changes.
   If a number cannot be made true without touching code, that is a finding and a
   package, not an edit here.
4. No compile error and no failing assertion attributable to `werte.cpp`. (Not
   `ctest bleibt gruen` — other lanes run tonight and a red caused elsewhere is not
   your Ruecklauf.)

## Not in scope, and not presumed wrong

- **`werte_probe.cpp` carries none of these numbers** — grepped 2026-09-08, no match for
  `31 Zeichen`, `zwoelf Adressen` or `32[0-9]`. You do not need that file and must not
  edit it. Line 722 claims *„`werte_probe` misst dieselbe Laenge zur Laufzeit nach"*:
  **check that by reading and say in your summary whether it holds. Do not extend the
  clause and do not repair it here** — an assertion about a file this package does not own
  is what goes stale.
- **`verlauf_probe.cpp:254`, `schritt_probe.cpp:522` and `:1584` carry the same phrase
  „zwoelf Adressen" and stay untouched.** They speak about probes that set only country
  addresses, where twelve may be correct. Nobody has measured them; do not assume they are
  wrong because this one is.
