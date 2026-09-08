# Logbuch: kernbauer

Rotated by the runner on 2026-09-08 at 12956 characters (cap 12,000). Predecessor: `notizen/archiv/kernbauer-2026-09-08-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## Carried forward from the predecessor

- **Check the rule's right-hand side against the four carriers (T15/T27/T23/T48) and then
  against the address order, before writing a line of the body.** Both checks cost one
  `grep`. Scope every code search to `kern/` -- the venture root drags in the frozen tree
  copies under `befunde/messung-*/`.
- **Read the riegel that owns your target file before you choose where a new declaration
  goes.** `zahlwort_riegel` reads exactly one file, `kern/include/kern/werte.hpp`, and
  demands a `T48 Nr.` in every doc block there. `belegstellen_riegel` reads the whole tree.
- **`belegstellen_riegel` in two sentences, because it is the one that bites silently.**
  Condition 1 is a per-line match: the word for a line (optionally plus `n`), a space, then
  **at least two digits** -- or `Z.` plus at least two digits -- with a file name anywhere
  to its left in the same sentence. Condition 2 needs three parts in one paragraph:
  Abschnitt/Absatz/Ueberschrift, then a quoted name, then a document name to the left.
  Avoid those three words near a quote and you never have to reason about it.
- **A new abort message must be checked in both directions against
  `probe_kennzeichen_eindeutig`:** your Kennzeichen must match no foreign message, and no
  foreign list may match yours. Cheapest way to be safe: a German noun phrase nobody else
  uses, and avoid the other lists' second tokens verbatim.

## 2026-09-08 -- the run on 0237 (the denominator of the approval rule)

- 2026-09-08, **the lesson of the run** -- **A probe start state built from a pattern
  function is a state nobody chose, and it can violate the specification for months
  without a single red test.** `musterwert(p) = muster[p % 8]` put `0` and `-10.000` on
  the twelve value-added addresses, so every round in `schritt_probe` divided by a
  **negative** GDP while `spiel.md` names `bip(l) > 0` as the denominator condition. It
  stayed green only because `schritt_3_politik` carries forward and the numerator is zero.
  The general form: **a pattern generator answers "arbitrary field values", never "a legal
  state"** -- and the moment a rule reads more than one address, those two stop being the
  same question. When a step body starts reading a derived quantity, work out by hand what
  the pattern puts on its summands. It is two minutes of arithmetic and it is the whole
  finding.
- 2026-09-08 -- **The load-bearing half of this package was not the barrier but the start
  state, and it reached a probe that does not build its state through `ausgangslage`.**
  Nine lines switch the barrier on; the rest of the run went into routing every start
  state through one function. `probe_zwei_runden_und_startwertriegel` fills its 310
  addresses by hand -- it has to, because its `Startbelegung` must stay open past two
  rounds -- and it would have died at round 1 without the same correction. **Grep the
  probe file for `Startbelegung` before you change what a start state carries**; the
  hand-built ones are the ones that break, and they are invisible from `ausgangslage`.
  Its positive control `welt.lies(0) == musterwert(0)` also had to move, because address 0
  is US agriculture value added -- the very first address is one of the twelve.
- 2026-09-08 -- **Give the twelve addresses distinct values, not one shared constant.**
  `1'000'000 + platz` makes the four GDPs 3.000.012 / 3.000.144 / 3.000.276 / 3.000.408.
  Four equal sums would have passed every assertion here while hiding a swapped country
  block; distinct ones cost one `+ platz`. Same reasoning as pinning the four approval
  addresses in 0197: a probe needs a state in which the candidate behaviours **cannot**
  agree.
- 2026-09-08 -- **The multiplying half of the rule cannot be measured from this file, and
  that is provable rather than a guess.** `politiklast` skips `kern::werte::schaden`
  unless an instrument level moved; the level comes from `schritt_3_politik`, which is
  `schreiber.vortrag(platz)`, so `lies_neu == lies_alt` at all 16 addresses **for every
  start state**. `Aktionsbuendel` is an empty struct and step 2 is skipped in `weltlauf`.
  So no start-state change can reach it -- the package asked me to say so if that was the
  answer, and it is. `werte::schaden`, `festkomma::mal(richtung, zeile)` and the `plus`
  accumulation have still never executed; the T39 question about `schaden`'s reads landing
  inside the `weltlauf` mask stays unanswered at runtime until step 3 computes.
- 2026-09-08, **what I am unsure about, for the project manager:** two things.
  **(a)** I cannot compile. If the build is red, read these first: `wertschoepfungsplaetze()`
  is a `constexpr` function with a nested range-for over two `constexpr std::array`s
  feeding a namespace-scope `constexpr` array -- legal since C++17, not compiled by me;
  and `bip_der_lage` is called inside `PRUEFE(...)`, whose macro argument contains a comma
  protected only by the call's own parentheses (correct, but it is the shape that has
  bitten this file before).
  **(b)** The head comment of the probe listed „der `spielmodus`, die negative
  Rundennummer und die nicht mehr zaehlbare" as *the* aborts. It was already incomplete
  before my run (Parametersatz, both Startbelegung riegel) and is now one shorter still.
  I added a paragraph for 0237 rather than rewrite the list -- a reviewer may fault the
  choice; the alternative was a bigger edit to a head that is not the package's subject.

## 2026-09-08 -- the run on 0242 (the ceiling of the denominator condition)

- 2026-09-08, **the lesson of the run** -- **An acceptance condition can name machinery
  that lives in another package's file. Grep for the apparatus, not for the concept,
  before you plan the run.** Condition 3 said "register the Riegel so the completeness
  half of the Kennzeichen probe covers it". That apparatus -- `Riegel`, `bricht_ab_mit`,
  the ledger, `probe_kennzeichen_eindeutig` -- exists **only** in `schritt_probe.cpp`,
  which `0240` owns; `grep -rl kennzeichen kern/` returns two files and `werte_probe.cpp`
  is not one of them. `werte_probe.cpp` proves its aborts with `hat_abgebrochen` plus
  `enthaelt(letzte_meldung, ...)` and has no completeness half at all. I built a
  one-Riegel ledger locally (`nennerdecke_angekommen`, `probe_nennerdecke_vollzaehlig`)
  and wrote the divergence up as proposal `0244`. Two minutes of grep would have told me
  this before I read the precedent in full.
- 2026-09-08 -- **The way to keep an abort set fixed while changing its message: test the
  precondition on `i128`, then let `festkomma` do the addition anyway.** Doing the
  addition myself with `__builtin_add_overflow` would have been shorter and would have
  broken T6 -- `festkomma.hpp` says in its own words that a checked addition outside it
  makes "ein Satz mit einer Ausnahme". So `bip` compares
  `static_cast<i128>(summe) + static_cast<i128>(teil)` against the two bounds *before*
  each `plus`, in the same order over the same three addresses. Same aborting states,
  different message -- which is exactly what condition 2 demanded and what let this run
  beside `0240`. `I64_MAX - teil` would not have worked: for `teil == I64_MIN` the test
  is itself the overflow it is meant to catch.
- 2026-09-08 -- **Take the ceiling's wording from the spec, not from the floor's message.**
  `spiel.md` names both ends in one sentence: `bip(l) > 0` **and** "a sum of positive
  value added and a value-range bound the break run checks". I nearly wrote "obere Seite"
  into the message, which would have been wrong -- the barrier catches both ends of `i64`,
  and the negative end is the one the probe now exercises with the longest number the
  message can carry (`I64_MIN`, twenty characters).
- 2026-09-08, **what I am unsure about, for the project manager:** two things.
  **(a)** The 319 characters in the doc block of `bip` are **hand-counted, not measured** --
  I cannot compile. The probe prints the measured length next to
  `MELDUNG_ZEICHEN_MAX`, and asserts only the bound and the absence of `meldung::MARKE`,
  so a wrong hand count shows up in the report as a number rather than as a red tree. If
  the printed value differs, the doc block is what needs correcting, not the code.
  **(b)** The local ledger in `werte_probe.cpp` is a second copy of an idea that already
  exists in `schritt_probe.cpp`. I think it is the right call under the file boundary and
  wrote `0244` to close it, but a reviewer may fault it as exactly the divergence
  `meldung.hpp` was built to prevent. The alternative was to leave condition 3 unmet.

