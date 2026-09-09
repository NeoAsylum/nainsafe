# Logbuch: kernbauer

Rotated by the runner on 2026-09-09 at 20392 characters (cap 12,000). Predecessor: `notizen/archiv/kernbauer-2026-09-09-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-09 -- 0284 (step 3 writes the path level)

Seven files, all delivered: `PFADINSTRUMENTE = 3` in `zustand.hpp`, the `pfadstand` field
and the one accessor in `kern::werte`, `JAHRGANGSFELDER` 2 -> 3, `feldzahl<Konstanten>`
9 -> 10 at both test spots, `schritt_3_politik` now sets the three and carries the fourth
forward, `probe_pfadstand_geht_in_die_runde` and `probe_pfadstand_zugang` new.

- 2026-09-09, **the lesson of the run** -- **Turning a carry-forward into a computation
  moves every probe that was green *because* nothing moved, and the blast radius is not in
  the file you edit.** Step 3 writing meant six instrument stands moved in every round of
  every probe whose carrier was value-initialised. That woke `politiklast` ->
  `werte::schaden` -> `schuld(l) = mal_geteilt(bip(l), staatsschuld(l), 10.000)` on the
  pattern layout, where `staatsschuld` is `I64_MIN` for CN and BR -- a hard abort in
  `festkomma`, two levels away from anything I touched. **Before switching a step from
  vortrag to setze, follow the first consumer of the moved address, not the address.**
  In `schritt_probe` I fixed it inside my claim by filling the probe's `pfadstand` from
  `musterwert`, so the carrier agrees with the state and nothing moves; every older count
  in that file survives untouched, and the new probe carries the moving case alone.
- 2026-09-09 -- **Two things break outside my `dateien`, both measured, both filed.**
  (a) `verlauf_probe.cpp:120` has its own value-initialised carrier over the same pattern
  layout and dies exactly as above; I cannot edit it -> **Vorschlag 0285**. (b) The
  accessor is a public function in `kern::werte` with no T48 number, and
  `zahlwort_riegel` reads exactly `werte.hpp` and gives exit 1 for "eine Deklaration nennt
  keine Nummer der Tabelle" (`zahlwort_riegel.cpp:824-834`) -> **Vorschlag 0286**. I chose
  the honest red over the cheap green: a doc line naming `T48 Nr. 18` in a sentence saying
  "this is not one of them" would satisfy the matcher and blind the check for every future
  declaration that simply forgets its number.
- 2026-09-09 -- **The zahlwort latch has a second trigger that the design text walked
  straight into.** A field of `struct Konstanten` must cite either `T23 Punkt 5` or start
  a line with `/// Schluessel `, else it "faellt in keine der zwei Sorten" and the latch is
  red too. Section 34's proposed comment for `pfadstand` cites neither. I added `T23 Punkt
  5`, which makes it the **third** Jahrgangskonstante -- so `werte.hpp:81` had to go from
  "die zwei Jahrgangskonstanten" to "die drei" (cardinal, equality-checked), while the
  ordinals at `:167` and my `:204` are checked with `<=` and hold. **A spec that quotes
  source text has not been run past the latches that read that source.**
- 2026-09-09 -- **Checked before writing, same rule as the day before:**
  `belegstellen_riegel` counts a Fundstelle at `Abschnitt`/`Ueberschrift`/`Absatz` next to
  a document name. My first draft of the `werte.hpp` head said "Abschnitt 34 von
  `technik.md`" -- exactly that pattern, in a file that carried no Belegstelle. Rewritten
  to "Der Entwurf zu Paket `0277`". Lane 0283 is measuring those counts tonight.
- 2026-09-09, **what I am unsure about, for the project manager:** four things.
  **(a) I cannot compile.** The riskiest new code is `pfadstand_der_probe()` in
  `schritt_probe.cpp` -- a `constexpr` function over two `constexpr std::array`s that must
  fold at compile time for `KONSTANTEN_DER_PROBE`; if it does not, the file fails to
  translate rather than going red.
  **(b) Predicted numbers, so a divergence is visible instead of arguable.** `schritt_probe`
  green: chain 175 links, twelve of them with cause `Jahrgang`, `0 von 16 Staenden bewegt`
  in the old probe, and `probe_pfadstand_geht_in_die_runde` printing stand `0 -> 275` with
  exactly one moved address. `werte_probe` green with 24 Riegel and 38 Meldungen (35 + 2
  for `PfadstandOhneReihe` + 1 for the third `GroesseNurBeiSpielbarenLaendern` site).
  `verlauf_probe` **red** with a `festkomma` abort in round 1. `zahlwort_riegel` **red**
  with one Mangel naming `pfadstand`. If anything else is red, distrust this line.
  **(c)** `schritt_3_politik` writes nothing if its address is in neither loop. That is
  deliberate -- the round-end check names the unwritten address -- but it is the one branch
  a reviewer may want as an abort instead.
  **(d)** `probe_pfadstand_geht_in_die_runde` picks US/Leitzins because CN and BR carry
  `I64_MIN` as debt ratio. That is a property of the probe's layout, not of the model, and
  it is written into the head so nobody measures it twice.

