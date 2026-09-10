# Logbuch: kernbauer

Rotated by the runner on 2026-09-09 at 20392 characters (cap 12,000). Predecessor: `notizen/archiv/kernbauer-2026-09-09-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-10 -- 0284, return 1 of 3 (one comment line)

The PM narrowed the return to Befund 2: `bezeichner_riegel` red on `werte.hpp:218`, which
named `daten_pruefsumme` in backticks. One edit, one file, nothing else touched.

- 2026-09-10, **the lesson of the run** -- **Backticks in a kern comment are a claim, and
  a T22 file-record field is not a kern name.** `bezeichner_riegel` builds its candidate set
  from Rueckwaerts-Anfuehrung alone (`bezeichner_riegel.cpp:478`, head `:70-114`); no rule of
  the fourteen can catch `daten_pruefsumme` -- rule 14 `fremdwort` is out because the name
  carries an underscore, and the other thirteen would each be a lie. **The fix is markup, not
  wording:** the house already quotes foreign text with `„..."` (`pruefsumme.hpp:31,63,67`,
  `zufall.hpp:30,57`), so the term now stands in Anfuehrung with one clause saying why it is
  not in Rueckwaerts-Anfuehrung. The name stays greppable, which a paraphrase would have cost.
- 2026-09-10 -- **Checked both neighbouring latches before writing, and neither fires.**
  (a) `belegstellen_riegel` needs three parts in one Absatz -- a **named file**, a
  Gliederungswort, the heading in quotes (head `:21-45`). My new `„..."` names no file, so it
  is no Zitat; the riegel stays green. (b) `zahlwort_riegel` counts Fundstellen of
  *Groessen* / *Jahrgangskonstante* / *Deklarationen*; my three added lines carry none of the
  three nouns and no number word, so every count in its report is unmoved.
- 2026-09-10, **what I am unsure about, for the project manager:** two things.
  **(a) Predicted numbers.** `bezeichner_riegel` **green**, `0 Bezeichner ... loesen nicht
  auf`, and the Nachlass list one entry shorter at `werte.hpp` -- the per-rule tally
  (`abgelegter_name 4; bauziel 9; dateiname 17; ...`) **unchanged**, because the line falls out
  of the Befunde and not into a rule. `schritt_probe`, `werte_probe` green as on 2026-09-09.
  `verlauf_probe` red is the Sollzustand (0285). `zahlwort_riegel`, `zahlwort_messung`,
  `multiplikationsriegel`, `belegstellen_wortabstand` red and not mine (0286, 0288, 0274).
  **(b)** The accessor declaration moved from `werte.hpp:265` to `:268` -- three lines of
  comment. `zahlwort_riegel`'s Mangel will name the new number; that is the same Mangel,
  not a second one.

## 2026-09-10 -- 0283, return 1 of 3 (two sentences in the head of `messen.py`)

Docstring only. `messen.py:22-41` rewritten, nothing else in either file touched --
no code line, no `belegstellen_riegel.cpp` edit, no case table, no `KLAMMERN`, no
timeout. The mechanism the return told me to leave alone is untouched, so the 10.13 s
of `belegstellen_kopfzahlen` (green, `befunde/uebersetzung-2026-09-09.md:457`) should
not move; a docstring compiles to the same bytes of work.

- 2026-09-10, **the lesson of the run** -- **A measured red and the red you can
  reproduce are two different claims, and one paragraph carried both.** The head cited
  the 2026-09-07 night as proof that an uncommitted comment edit turned Teil A red. That
  night's two dangling citations stood under *„Nur vorher"*
  (`uebersetzung-2026-09-07.md:289`), i.e. in the blob of the then-anchor `83faa06^`
  (`:281`) -- a working-tree edit cannot reach an archived blob. The evidence proved the
  swap, not the scenario. I split the paragraph: the scenario is now stated as a recipe
  with the corpus side named (Lauf B reads the working tree, Lauf A the archived text),
  and the 2026-09-07 numbers stand where they belong, as the measured instance whose
  cause was committed history (0147/0166/0182) -- which is also what `:148-153` of the
  same file has said all along. The two now agree instead of contradicting.
- 2026-09-10 -- **The direction was reversed and it was the only thing a reader needed.**
  `:26-27` said the edit moved what Lauf A read. `vorfassung()` caches the blob from
  `git cat-file` (`:290`, one write, `open(VORHER, "wb")` at `:296`), `neu` is
  `lies(QUELLE)`; under the removed swap `schreib(QUELLE, alt)` stood before
  `laufen(bin_alt)`. So Lauf A got `alt`, Lauf B the tree. Four lines above, `:17-18`
  had it right. **A head that says the same thing twice can be half wrong, and the
  reviewer will find the half.**
- 2026-09-10 -- **Checked before writing:** the `gelesen()` needles of Teil B read
  `text` = `lies(QUELLE)`, the riegel's head, never this docstring (`:551`, `:573`,
  `:665`, `:682`). Editing `messen.py`'s own head therefore cannot move a Teil-B
  expectation. And `befunde/` is in `UNGELESENE_ORDNER`, so the two new `"` quotations
  are not counted places.
- 2026-09-10, **what I am unsure about, for the project manager:** two things.
  **(a)** I cannot run it. The only way this run breaks the file is a syntax error in
  the docstring; the new text carries `*„Nur vorher"*` and `*„Welcher Commit
  dazwischen"*`, single `"` each, never three in a row, so `"""` cannot terminate early.
  If `belegstellen_kopfzahlen` is red with a `SyntaxError`, it is that and nothing else.
  **(b)** The head grew by about 11 lines. Condition 3 wants what Teil A gave up written
  down and condition 2 wants the proof named, and both now sit in the same section; if a
  reviewer reads that as padding, the cut belongs in the older *„Was damit entfaellt"*
  block (`:57-73`), not in the evidence.

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

