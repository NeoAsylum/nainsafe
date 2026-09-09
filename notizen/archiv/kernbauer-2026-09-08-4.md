# Logbuch: kernbauer

Rotated by the runner on 2026-09-08 at 12820 characters (cap 12,000). Predecessor: `notizen/archiv/kernbauer-2026-09-08-3.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 -- the run on 0247 (the caller count of `festkomma::mal`)

- 2026-09-08, **the lesson of the run** -- **I wrote this proposal myself, and my
  diagnosis in it was wrong about half the defect.** `0247` said the block named five
  functions while a match returns six sites in `werte.cpp`, and put that down to
  `positionswert_aus` reaching `mal` twice. It does not: the six sites are six distinct
  functions, and the sixth is **`werte::schaden`**, which the old block never named. So
  the sentence "alle fuenf stehen in `kern::werte`" was false twice over -- one caller
  missing *inside* the namespace, one *outside* it -- and I had only found the outside
  one. **Re-measure the whole claim, not the part the proposal flagged.** A proposal is
  a hypothesis even when you wrote it.
- 2026-09-08 -- **Where sites and callers genuinely differ here, for whoever re-measures
  next.** Not in `kern/src` -- there it is seven and seven. It is
  `probe_zollkeil_rundet_zweimal` in `werte_probe` (two sites, one function) and
  `positionswert_aus`'s second, indirect reach through `tsd_in_cent`. Both are named in
  the block now, so the next count has the divergence in front of it instead of
  rediscovering it.
- 2026-09-08 -- **The old exclusion rule did not cover the case it had to.** It excluded
  `festkomma_probe` because those calls "pruefen diese Funktion, statt sie zu benutzen".
  `werte_probe` **uses** `mal` to compute the value it compares against, so that rule
  lets it in while the headline number keeps it out. I narrowed the count to `kern/src`
  and named both probes as the exclusion, rather than leaving a rule that silently
  disagrees with its own number.
- 2026-09-08, **the two-grep method, and it costs almost nothing.** `\bmal\s*\(` does not
  match `mal_geteilt(` (the `_` blocks `\s*\(`) and cannot match inside `normal(` (no word
  boundary), so it needs no post-filtering; German prose "... mal (" is the only false
  positive and it reads as one. Then `\bmal\b` **without** the paren over the same tree
  proves there is no non-call use hiding -- a function pointer, a template argument. Here
  it turned up exactly one: `using festkomma::mal;` in `werte.cpp`. **Ripgrep has no
  look-around**; `(?!...)` is rejected outright, so do the second grep wide and read it.
- 2026-09-08, **what I am unsure about, for the project manager:** three things.
  **(a)** The stand `2ce13ce` is read off this session's git header, not
  off a command I ran. I have no shell. If HEAD moved between that header and my edit, the
  stand in the block is one commit stale; the seven callers are measured on the tree I read,
  which is what the number actually rests on.
  **(b)** I did **not** check whether `schaden`'s call existed at `f6731fe` on 2026-09-05.
  So I cannot say whether the old block was wrong when written or went wrong later, and I
  deliberately claim neither -- the block now states only what holds at my stand.
  **(c)** I cannot compile. This run touches one doc comment, so nothing in it reaches the
  compiler. `belegstellen_riegel` reads the whole tree: my text has no line-word followed by
  two or more digits and none of the three heading words near a quoted name, so neither
  condition can match. Checked by reading the riegel's rules from this logbook, not by
  running it.

## 2026-09-08 -- the run on 0240 (the clamp behind an addition that aborts)

Two carried-forward items the block further down does not have, and both held again here:
**the way to change an abort message without changing the abort set** -- test the
precondition on `i128`, then let `festkomma` do the arithmetic anyway; doing it yourself
with `__builtin_add_overflow` is shorter and breaks T6. And: of the five `belegstellen_*`
ctest entries **only `belegstellen_riegel` reads your files**, the other four are
self-tests of that tool.

- 2026-09-08, **the lesson of the run** -- **"Two conditions must both change" is a claim
  about arithmetic, and it is worth two minutes of it before you plan the run.** The
  package (and the finding behind it) said the Verdacht hangs on two independent
  conditions -- `zustimmung_elastizitaet` leaving `0` **and** an instrument stand moving --
  and offered me the first as the way in: since `0229` a probe can bring its own parameter
  set. It cannot work, and the reason is one line of algebra: the additive term is
  `mal_geteilt(zustimmung_elastizitaet, hub, 10.000)` with `hub == 0`, and **a product with
  the factor zero stays zero for every coefficient**. The two conditions are one, and it is
  the one the package forbade me. The general form: when a plan says "condition A alone
  suffices", check whether A is a *factor* of something the other condition zeroes.
- 2026-09-08 -- **The unreachable case still fits in the probe, one layer down.** The round
  cannot produce a non-zero term, but `festkomma::plus` is the exact primitive at the site,
  and the four start values are known. Twelve rows -- four start values x term `0/+1/-1`,
  each with "does it abort" and "what the rule over the integers demands" -- turn the whole
  finding from prose into printed numbers: 2 of 12 abort, and in both the rule wants 10.000
  resp. 0, i.e. a value that was never outside the range. Same move as `ohne_klammern` in
  `0233`: when a comment says what *another* execution would do, ask whether that execution
  fits in the probe. Third time now the answer was yes.
- 2026-09-08 -- **The negative half needs a positive control that is not the assertion
  itself.** "The coefficient moves nothing" is measured as: run the same start state twice,
  coefficient `0` against `I64_MAX`, count differing addresses over all 310. Exactly one
  differs, `partie.parameter_pruefsumme` -- the address carrying the coefficient. That one
  differing address is what keeps the measurement from being a tautology, and it needs its
  own precondition (`parameter_pruefsumme` of the two sets must differ) written as a check,
  not assumed -- otherwise a checksum collision would report zero and read like proof.
- 2026-09-08 -- **The Riegel ledger of `schritt_probe.cpp` cannot carry a barrier that no
  state reaches.** Its completeness half demands a message per entry each run; my new
  located abort is provably unreachable, so registering it would turn the tree red on a
  healthy build, and omitting it hides the barrier from the very check built so that no
  barrier disappears. I omitted it and wrote the reason at the probe -- a comment, not a
  check. Written up as proposal `0248`. **Grep the ledger's completeness half before you
  add an abort you cannot trigger.**
- 2026-09-08, **what I am unsure about, for the project manager:** three things.
  **(a)** I cannot compile. If the build is red, look first at the default argument
  `const kern::werte::Konstanten& satz = KONSTANTEN_DER_PROBE` on `ausgangslage_voll` and
  `ausgangslage_mit_zustimmung` -- a `constexpr` object as a default argument is legal but
  it is the newest shape in that file -- and at `SUMMENFAELLE`, where two rows make a
  `constexpr` array whose values would abort `festkomma::plus` if anything ever evaluated
  them in a constant expression. They are only read in a runtime loop.
  **(b)** I lifted `AUSSERHALB`/`SCHRANKE` out of `probe_zustimmung_klemmt_statt_vortrag`
  to namespace scope (`ZUSTIMMUNG_AUSSERHALB`, `ZUSTIMMUNG_SCHRANKE`) because both probes
  need the same four values and condition 3 is about exactly those. A reviewer may fault it
  as an edit beside the package; the alternative was a second copy of the four numbers whose
  agreement the whole condition rests on.
  **(c)** The length of the new abort message is **hand-counted, not measured**: about 418
  characters at the longest address and both numbers at 20 digits, against
  `MELDUNG_ZEICHEN_MAX` of 511. Nothing prints it, because nothing can reach it -- unlike
  `0242`, where the probe printed the measured length. If the count is wrong, the message
  truncates on the day step 3 computes and ends on `[...]`.
- 2026-09-08 -- **Outside my file list, and 0245 does not close it:** `include/kern/schritt.hpp`
  lists the hard errors of the round. `0245` (`gebaut` the same night) adds `kern::festkomma`
  as a third abort source, but the new located barrier is one of `kern::schritt`'s own, and
  the header's own list of those does not have it. Not wrong today -- it is unreachable --
  but incomplete. Noted in the package's Vermerk.

## Carried forward from the predecessor

- **Check the rule's right-hand side against the four carriers (T15/T27/T23/T48) and then
  against the address order, before writing a line of the body.** Scope every code search
  to `kern/` -- the venture root drags in the frozen tree copies under `befunde/messung-*/`.
- **Read the riegel that owns your target file before you choose where a new declaration
  goes.** `zahlwort_riegel` reads exactly one file, `kern/include/kern/werte.hpp`;
  `belegstellen_riegel` reads the whole tree.
- **`belegstellen_riegel` in two sentences.** Condition 1 is a per-line match: the word
  for a line (optionally plus `n`), a space, then **at least two digits** -- or `Z.` plus
  at least two digits -- with a file name anywhere to its left in the same sentence.
  Condition 2 needs three parts in one paragraph: Abschnitt/Absatz/Ueberschrift, then a
  quoted name, then a document name to the left. Avoid those three words near a quote and
  you never have to reason about it. Confirmed again on 2026-09-08 by reading `SCHLUESSEL`
  and `KLAMMERN` in `werkzeuge/belegstellen/belegstellen_riegel.cpp`.
- **A new abort message must be checked in both directions against
  `probe_kennzeichen_eindeutig`:** your Kennzeichen must match no foreign message, and no
  foreign list may match yours.

## 2026-09-08 -- the run on 0245 (the hard-error list of `schritt`)

- 2026-09-08, **the lesson of the run** -- **A package that names call sites by line
  number hands you a reading of the source, and the reading can be wrong even when every
  line number in it is right.** `0245` wrote "`realeinkommenshub` (`:644`, `:686`,
  `:687`)". At HEAD `:686` and `:687` are in the body of `schritt_5_reaktion`, not in
  `realeinkommenshub` -- the loop calls the helper, takes the `hub` back, and does the
  elasticity and the addition itself. Condition 1 said to read `schritt.cpp` at my HEAD;
  it paid, but not for the reason the condition gave (nothing had moved). **Read the
  source for the shape, not only to confirm the numbers.** The bullet I wrote names three
  places -- the body of step 5 itself, `realeinkommenshub`, and `politiklast` out of it.
- 2026-09-08 -- **The distinction the header did not have a slot for: dead versus
  harmless.** The two entries already there are dead paths -- `schaden` "wird nie
  betreten", the `bip` barrier holds. The `festkomma` arithmetic is **walked every
  round**: `schritt_5_reaktion` is called unconditionally in `weltlauf`, so
  `mal_geteilt`, `minus` and `plus` all execute. It cannot overflow only because
  `richtung == 0` at every instrument makes `last`, `hub` and `wirkung` zero. That is a
  different reason and I wrote it as one, in one clause, by pointing at the reason the
  entry above already carries instead of restating it -- one moving fact, one place.
- 2026-09-08 -- **What condition 2 forbids is a count, and "die beiden Hilfen" is not
  one.** I wrote no line number and no site count. Naming two functions and then saying
  "beide" is naming, not counting: it moves only when the functions do, and then the names
  are wrong anyway. Where I did drop a count deliberately: I did not write how many
  arithmetic sites there are, and did not write "vier".
- 2026-09-08 -- **The same defect one file over, and it is measurable in one grep.** The
  doc block of `festkomma::mal` claims "Heute mit fuenf Aufrufern, und alle fuenf stehen
  in `kern::werte`", measured 2026-09-05 on `f6731fe`. `politiklast` calls it. Proposal
  `0247`. Note for whoever takes it: `mal(` returns six sites in `werte.cpp` alone against
  five named functions, because `positionswert_aus` reaches `mal` twice -- once directly,
  once through `tsd_in_cent`. **Sites and callers are not the same number in this file**,
  which is why the proposal asks for the unit and not just for a fresh count.
- 2026-09-08, **what I am unsure about, for the project manager:** two things.
  **(a)** The list at `schritt.hpp:298` opens with "in der Reihenfolge, in der sie
  greifen". My third entry does not strictly follow the second in time: the `festkomma`
  arithmetic in `politiklast` fires immediately after `werte::schaden` returns, inside the
  same loop, so the two interleave rather than queue. The group's own introduction claims
  no order among the three, and rewriting the head sentence was not my package -- but a
  reviewer reading `:298` as governing all seven entries has a point.
  **(b)** I cannot compile. This run touches only a doc comment, so nothing in it can be
  red at the compiler; what can bite is `belegstellen_riegel`, which reads the whole tree.
  My bullet names a file (`kern/src/schritt.cpp`) and contains no digits at all and none
  of the three heading words, so neither of its two conditions can match. Checked by
  reading the riegel, not by running it.

