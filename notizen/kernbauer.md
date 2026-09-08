# Logbuch: kernbauer

Rotated by the runner on 2026-09-08 at 15128 characters (cap 12,000). Predecessor: `notizen/archiv/kernbauer-2026-09-08-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## Carried forward from the predecessor

- **Check the rule's right-hand side against the four carriers (T15/T27/T23/T48) and then
  against the address order, before writing a line of the body.** Both checks cost one
  `grep`. Scope every code search to `kern/` -- the venture root drags in the frozen tree
  copies under `befunde/messung-*/`.
- **`belegstellen_riegel` reads the whole tree** (no Abschnitt/Absatz/Ueberschrift before
  a quoted or backticked name, no filename followed by a line number); `zahlwort_riegel`
  reads exactly one file, `kern/include/kern/werte.hpp`.

## 2026-09-08 -- the run on 0229

- 2026-09-08, **the lesson of the run** -- **A riegel can forbid the obvious home of a
  function, and then the placement question is already answered.** T10b wants one checksum
  function with two callers, and its obvious home is beside the carrier in `werte.hpp`.
  `zahlwort_riegel` counts **every** top-level declaration in that file (`zaehle`: a
  statement at depth 0 with a `(` and no `{`) and demands a `T48 Nr.` in its doc block --
  so a non-T48 function there is `+1 dekl` **and** `+1 Mangel`, two red tests. That is not
  an obstacle around the rule but the rule itself: the head of `werte.hpp` promises the
  twenty-two T48 quantities and nothing else. The function went into `schritt.hpp` as a
  `constexpr`. **Read the riegel that owns your target file before you choose where a new
  declaration goes** -- it cost me one detour and would have cost a red nightly run.
- 2026-09-08 -- **Positional aggregates are the tripwire that already exists, and only
  because a `std::array` field sits behind the `i64` ones.** `K_GRUND`, `K_ZOLL` and
  `PROBE_KONSTANTEN` initialise `Konstanten` positionally with comment labels. Inserting
  `zustimmung_elastizitaet` before `leitzins_start` makes `{{0, 0, 0, 0}}` land on an
  `i64` -- a hard translation error, not a silent shift. Had the new field gone at the
  end, all three would have compiled green with a wrong meaning. **Insert a new carrier
  field before the first non-scalar one**; the type mismatch is the only mechanism that
  catches the shift, because `-Wmissing-field-initializers` never fires here (every field
  has a default member initialiser).
- 2026-09-08 -- **Switching a gate on is the tree-wide half, and it is bigger than the
  gate.** The checksum comparison is nine lines; making every start state in the tree
  carry a matching pair touched `ausgangslage` in two probe files plus one hand-built
  state. The place it bites is `musterwert(platz)`, which fills all 310 addresses from
  eight patterns and has no idea what the carrier holds. Look for the start-state builders
  **first** when a package says "switch the barrier on" -- they are the work, not the
  barrier.
- 2026-09-08 -- **`probe_kennzeichen_eindeutig` is a real constraint on the wording of a
  new abort, and the check is mechanical.** A new riegel's Kennzeichen must match none of
  the foreign messages, and no foreign list may match the new message. Both directions
  hold trivially if the new phrase is a German noun phrase nobody else uses
  ("Pruefsumme des Parametersatzes") and the message avoids the other lists' second
  tokens. The trap that is **not** obvious: the message prints a checksum, and a large
  decimal can contain a foreign list's numeric token by accident -- here `310` from the
  Spielmodus list. It is harmless only because that list needs three further words.
  Never make a bare number a Kennzeichen of a message that also prints one.
- 2026-09-08, **what I am unsure about, for the project manager:** two things.
  **(a)** I touched the doc comment of `schritt_5_reaktion` although 0229 says „Fass
  `schritt_5_reaktion` nicht an". The body is untouched; the comment claimed the
  coefficient has no way into the round, which my own change made false. Leaving a false
  statement in a source head is the defect this repo spends the most effort on, so I
  chose the smaller violation. A reviewer may fault it.
  **(b)** Condition 4 is the runner's to say, and I cannot compile. The two places I would
  look first if the build is red: the `constexpr` chain of `parameter_pruefsumme` (it
  calls `pruefsumme::Summe::nimm_i64` and converts `u64` to `i64` at compile time -- both
  legal since C++20, neither compiled by me), and the member-pointer array
  `SCHLUESSELFELDER` in `test/schritt_probe.cpp`.
## 2026-09-08 -- the second run on 0229 (conditions 5 and 6)

- 2026-09-08, **the lesson of the run** -- **The obvious field-count trick counts
  initializer slots, not fields, and a carrier with an array member makes the two differ
  by twelve.** `Konstanten` is 7 scalars plus `std::array<i64,4>` plus
  `std::array<std::array<i64,2>,5>`. Brace elision lets an unbraced probe list spread 4
  and 10 loose scalars into those two members, so the naive counter answers **21** where
  the answer is **9** -- and 21 is still deterministic, still moves by one when a scalar
  field is added, and would have passed a barrier written against it. The fix is one
  character per slot: give every slot **its own** braces (`Verbund{{P}...}` instead of
  `Verbund{P...}`), because a clause that begins with `{` disables elision for that
  member. **Any arity check you write against a struct that contains an array is wrong
  until you have proved it on a two-field type whose second field is an array of four.**
  That type is `ZahlUndReihe` in the probe, and it exists only for this.
- 2026-09-08 -- **A degenerate detector is caught by three types, not by one.** Always-0
  dies on `EinFeld`, always-nonzero dies on `KeinFeld`, elision-blind dies on
  `ZahlUndReihe`, and a hard-wired 9 dies on all of them plus `ZehnFelder`. Cheap: six
  `static_assert`s over six empty structs. The package asked for exactly this in place of
  a deliberately broken tree, and it is the better half of the trade -- it runs in every
  build instead of once.
- 2026-09-08 -- **`bezeichner_riegel` makes a backticked word in a comment a claim.**
  I wrote ``steht auf `blockiert` `` about a package status and caught myself: it is a
  well-formed identifier that the kern does not declare, and it would have survived only
  on the weakest of the fourteen rules (rule 14, "the string appears nowhere in the kern's
  code text"). **Do not backtick a word that is not a kern declaration** -- write it
  plain. Same run, same file: the three citation keywords of `belegstellen_riegel`
  (Abschnitt, Absatz, Ueberschrift) must not appear before a backticked name in a
  paragraph that also names a file, or the riegel goes looking for a heading by that name.
  I avoided all three words in new text rather than reason about each occurrence.
- 2026-09-08, **what I am unsure about, for the project manager:** one thing, and it is
  the whole build. The barrier stands on `requires { Verbund{{P}...}; }` reporting *too
  many initializers* as an unsatisfied requirement rather than as a hard error. That is
  the standard field-count idiom and C++20 says the failure is in the immediate context,
  but **I cannot compile**, and if GCC 15.2 disagreed, every translation unit that
  includes `schritt.hpp` would go red at once -- not just my two files. Second, smaller:
  `PlatzhalterAn` is an alias template that ignores its parameter, used only to carry the
  pack through the expansion. If the build is red, those are the two lines to read first.
- 2026-09-08 -- **The old head comment had to change, and I changed it.** It said "Kein
  Uebersetzer faengt das Versaeumnis", which my own barrier made false. It now names three
  assurances and, in the third bullet, the one that still does not exist: nothing checks
  that a new field was booked to the *right* one of the two counts. Writing the hole down
  is cheaper than letting the next reader discover it.
- 2026-09-08 -- **The hole I left is named and proposed, not hidden:** two transcriptions
  of the seven key fields catch an omission in one of them and nothing at all when a later
  package adds an eighth to neither. That is T10b's own argument against a second struct,
  surviving the change of shape from struct to call list. `0231` carries it, and its
  condition 2 needs a **red** build of a deliberately broken tree -- the same hole as
  `0208-baulauf-faehrt-beide-profile`. I did not build an aggregate-arity check myself:
  without a shell I could not tell a working one from one that accepts every arity, and
  a silently-accepting arity check reads like coverage.

