# Logbuch: kernbauer

Rotated by the runner on 2026-09-08 at 13570 characters (cap 12,000). Predecessor: `notizen/archiv/kernbauer-2026-09-08-4.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 -- the run on 0248 (a ledger entry for a barrier no state reaches)

My own proposal out of `0240`, back as a package. Delivered: a second category
`RIEGEL_OHNE_ZUSTAND` in `schritt_probe.cpp`, exempt from the completeness half, checked
against every foreign message, printed by name each run.

- 2026-09-08, **the lesson of the run** -- **"unreachable" and "uncallable" are different
  claims, and I had written the weaker one into my own proposal.** The package, the finding
  and my logbook all said the barrier has no message *because no state reaches it*. True,
  but not the binding reason: `summe_der_regel_pruefen` sits in the **anonymous namespace**
  of `src/schritt.cpp` -- internal linkage. Even a probe that knew the exact arguments
  could not name it. That changes the answer from "wait until step 3 computes" to "no probe
  in this file can produce that message unless the source changes". **Before writing that a
  case is untestable, check the linkage of the function, not only the reachability of the
  state.** My own `0240` lesson -- "the unreachable case still fits in the probe, one layer
  down" -- did not apply, and linkage is why. Fourth time I asked; first time the answer
  was no.
- 2026-09-08 -- **Split an invariant into its directions before declaring it unavailable.**
  The uniqueness assurance reads as one sentence but is two: *my list fits no foreign
  message*, and *no foreign list fits my message*. The first needs only the foreign
  messages, which exist; the second needs mine, which cannot. So the delivery is not
  "impossible, here is a comment" but a real check for one half plus the written price of
  the other. **A half-checkable invariant is a check, not a note.**
- 2026-09-08 -- **The new check is demonstrably not vacuous, and the proof was free.**
  `"Zustimmungsregel"`, the first of the three Kennzeichen, also stands in the
  `Nennerbedingung` message -- both riegel sit at the same rule. Shorten the list to that
  one piece and the run goes red. Same shape as the positive control in `0240`: an
  assurance that cannot fail on any input is worth nothing, so find the input on which it
  would fail and write it at the source.
- 2026-09-08 -- **A print that states a conclusion can be contradicted by its own run.** My
  first per-entry line read "auf keine der N Meldungen passend" and printed
  unconditionally -- on a violating run it would have said that while stderr said the
  opposite. Changed to print the *count* of matched messages. The number cannot lie.
- 2026-09-08 -- **An exemption needs its own lock, and the type system is the cheapest.** A
  category exempt from completeness is an obvious escape: move a reachable riegel into it
  and its missing message stops mattering. A separate enum (`RiegelOhneZustand`) shuts it --
  `bricht_ab_mit` takes `Riegel`, so an aborting site cannot file under the exempt type
  without being rewritten. Cost: one enum, no runtime check.
- 2026-09-08, **what I am unsure about, for the project manager:** I cannot compile. The
  newest shape in the file is `constexpr std::array<OhneZustand, 1>` holding a `std::span`
  onto another `constexpr` array -- well-formed (static storage, non-explicit span
  constructor), but if the build is red, look there first. Second: I routed the existing
  `liste_passt` through the new `alle_stuecke_in` so both ledgers ask the identical
  question. That is an edit to existing code in my own file and a reviewer may read it as
  beside the package; the alternative was two copies of the condition the whole assurance
  rests on -- the same trade as `ZUSTIMMUNG_AUSSERHALB` in `0240`.

## 2026-09-08 -- the run on 0249 (the head names a barrier that can no longer fire)

- 2026-09-08, **the lesson of the run** -- **"This entry is dead" is almost never true of
  the whole entry; find the clause that died.** The package (and the finding behind it)
  said the third bullet of the hard-error list names a dead barrier: since `0240`,
  `festkomma::plus` in step 5 cannot abort. True of the *addition* and of nothing else.
  The body of step 5 still reaches `kern::festkomma` through the elasticity line, and
  `realeinkommenshub` through `minus(0, last)` and `mal_geteilt`. So the repair was **a
  split, not a replacement**: `Drei weitere` became `Vier weitere`, the located barrier
  out of `kern::schritt` got its own entry, and the old one kept everything but the
  addition. Had I taken the package's wording as the whole finding, I would have deleted
  three live paths.
- 2026-09-08 -- **What went stale five times was one line, and it was not an entry.** The
  group head assigned places to entries by ordinal -- `die ersten beiden fuehren aus
  kern::werte heraus, der dritte aus kern::festkomma`. That breaks on *insertion* as well
  as on *movement*, and both happened. The structural fix is one moving fact, one place:
  each entry carries its own place, no group line. It also killed the `Anders als die
  beiden Eintraege davor` contrast (condition 3) without a separate repair -- **a
  cross-entry contrast is the same defect in another grammar.**
- 2026-09-08 -- **Answer a "where is this actually checked" condition by pointing, never
  by summarising.** Condition 5 offered the `Riegel` ledger of `schritt_probe.cpp`. I
  named it and said **nothing** about which entries it holds: `0248` was editing that file
  in the parallel lane, so any sentence about its contents would have been stale on
  landing. Pointing is order-independent; summarising is not. General form: **when two
  packages share a subject but not a file, the one that does not own the file may only
  point at it.**
- 2026-09-08 -- **`werte::bip` aborts twice on one quantity, and the header knew one.**
  The value-added sum leaves `i64` inside `bip` itself (`kern/src/werte.cpp`, the ceiling
  since `0242`); only after that does `realeinkommenshub` test `bip(l) > 0`. Entry 1 was
  worded to the second alone while entry 2 was a catch-all over its function. **Check
  whether neighbouring entries are written at the same width before you trust either.**
- 2026-09-08, **what I am unsure about, for the project manager:** two things.
  **(a)** I deleted one clause the conditions did not name -- the old entry 1 closed with
  `die Aussage ueber die eine bewegte Groesse weiter oben ist genau so falsch geworden`.
  It is true, but the new closing paragraph makes the same argument with `0240` as the
  instance, so it went as repetition. Recorded in the package's Vermerk; a reviewer may
  fault it as an edit beside the package.
  **(b)** I cannot compile, and this run touches only a doc comment, so nothing in it can
  be red at the compiler. What could bite is `belegstellen_riegel`, which reads the whole
  tree: my text has no line word before digits (`Paket 0240`, `T7` only) and none of
  Abschnitt/Absatz/Ueberschrift near the quoted `spiel.md`. Checked by reading the riegel,
  not by running it.

## 2026-09-08 -- 0249, Ruecklauf 1 (the pointer was right, its scope was not)

- 2026-09-08, **the lesson of the run** -- **A pointer is a claim about coverage, and I
  only checked that the target existed.** I answered condition 5 by pointing at the
  `Riegel` ledger and thought "pointing is order-independent, so I am safe". It is not:
  the *sentence around* the pointer said `eine Kennung je Schranke, zu jeder in jedem Lauf
  eine angekommene Meldung, sonst faellt der Lauf` -- and that is a restatement, of a
  guarantee that had just been split in two by `0248`. Three of my own four entries have
  no Kennung in that ledger at all, because it is scoped to the aborts out of
  `kern::schritt`. **Before you point at a ledger, ask it your own question: which of my
  entries does it answer for, and with what guarantee?** If the answer is "some", the
  pointer must say which.
- 2026-09-08 -- **Naming the file was the avoidable part.** `0244` lifts `Riegel`,
  `ALLE_RIEGEL`, `RIEGEL_OHNE_ZUSTAND` out of `schritt_probe.cpp` into
  `kern/test/kennzeichen.hpp`. My path would have been false the night it lands, in a file
  `0244` does not own. **`dateien` prevents overwrites, not falsification** -- so refer to
  a thing by an identifier that travels with it, never by the path that holds it today.
  Same class as the group line I removed in the first round.
- 2026-09-08 -- **`gerechnet` and `erreicht` were separated in one entry and merged in its
  neighbour.** Entry 2 says both words in one sentence; entry 1 said only `gerechnet` --
  and entry 1 is the one whose abort actually fires. **When a text builds its own
  vocabulary, check every entry against it, not only the entry you last edited.** Same
  shape as the width defect I found myself last round (`bip` aborting twice).
- 2026-09-08, **what I am unsure about, for the project manager:** the reviewer's
  finding said the ledger `is scoped to kern::schritt`. That is not exactly true --
  `StartwertSetzen` and `StartwertBinden` are `kern::zustand`. I wrote the sentence to
  claim only which of *this header's four entries* the ledger answers for, and said
  nothing about its overall scope, because the overall scope is the kind of fact that
  moves. A reviewer expecting the finding's wording verbatim may read that as a miss.

## Carried forward from the predecessor

- **`belegstellen_riegel` in two sentences.** Condition 1 is a per-line match: the word
  for a line (optionally plus `n`), a space, then **at least two digits** -- or `Z.` plus
  at least two digits -- with a file name anywhere to its left in the same sentence.
  Condition 2 needs three parts in one paragraph: Abschnitt/Absatz/Ueberschrift, then a
  quoted name, then a document name to the left. Avoid those three words near a quote and
  you never have to reason about it.
- **Which riegel reads what.** `zahlwort_riegel` reads exactly one file,
  `kern/include/kern/werte.hpp`; `belegstellen_riegel` reads the whole tree. Of the five
  `belegstellen_*` ctest entries **only `belegstellen_riegel` reads your files**, the
  other four are self-tests of that tool. Read the riegel that owns your target file
  before you choose where a new declaration goes. Measured again 2026-09-08: of the ten
  tree-reading ctest entries, exactly **two** read `kern/test/*.cpp` --
  `belegstellen_riegel` and `bezeichner_riegel`.
- **`bezeichner_riegel` is not a naming-convention check, and I believed it was.** It reads
  every backticked span in **comments** under `kern/` and demands the name inside be
  declared somewhere in `kern/` code -- a dead-reference check for doc comments. So
  inventing a plausible identifier in a comment is what turns it red; SCREAMING_CASE
  against PascalCase is not. Escapes worth knowing: a path or multi-word phrase in
  backticks is never a candidate, and an immediately preceding `statt / kein / keine /
  nicht / ohne / gegen / hiess / frueher` licenses a name that no longer exists.
- **A ledger entry for a barrier no state reaches** lives in `RIEGEL_OHNE_ZUSTAND` in
  `schritt_probe.cpp` (Paket 0248), with its own enum type so the exemption cannot be
  borrowed. It keeps one half of the uniqueness assurance -- the list must fit no foreign
  message -- and cannot have the other.
- **A new abort message must be checked in both directions against
  `probe_kennzeichen_eindeutig`:** your Kennzeichen must match no foreign message, and no
  foreign list may match yours. And **grep the completeness half of the `Riegel` ledger
  before you add an abort you cannot trigger** -- it demands a message per entry each run,
  so an unreachable barrier registered there turns a healthy build red.
- **Check the rule's right-hand side against the four carriers (T15/T27/T23/T48) and then
  against the address order, before writing a line of the body.** Scope every code search
  to `kern/` -- the venture root drags in the frozen tree copies under `befunde/messung-*/`.
- **Changing an abort message without changing the abort set:** test the precondition on
  `i128`, then let `festkomma` do the arithmetic anyway; doing it yourself with
  `__builtin_add_overflow` is shorter and breaks T6.
