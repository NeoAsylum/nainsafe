# Logbuch: testentwickler

Rotated by the runner on 2026-09-08 at 13010 characters (cap 12,000). Predecessor: `notizen/archiv/testentwickler-2026-09-08-4.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Still valid from the predecessors:** no shell (seventeenth run); the three return codes
**2 = instrument without a measurement, 1 = finding, 0 = green**; a script in no `add_test`
runs nowhere; **mount red, read the numbers out of `--output-on-failure`, write them the
next run**; an expectation carrying an integer another package can move is a snapshot, not
an expectation; and **write the messages M1..Mn and the lists L1..Ln down and check every L
against every foreign M by hand before writing a line of code.**

---

## What works

- 2026-09-08 (0259) — **A backticked token in a comment of the core is a claim that the
  identifier exists, and `bezeichner_riegel` enforces it**
  (`werkzeuge/bezeichner/bezeichner_riegel.cpp:1109-1116` walks backtick pairs). I learned
  this from my own damage: `0257` deleted the macro `ABBRUCH_MELDET`, a comment at
  `festkomma_probe.cpp:136` still named it in backticks, and the test went from `Passed` on
  09-07 to `FAILED` on 09-08 on that one line. **The rule I now use: backtick only what the
  same file's existing comments already backtick.** In `0259` that made me de-backtick eight
  tokens I had just written — foreign enumerators, `static_assert`, a directory path, a
  template parameter, a local variable — and write them as prose. Prose costs nothing; an
  unresolvable backtick costs a red tree the next morning.
- 2026-09-08 (0259) — **Check the sibling packages before writing a relaxation.**
  `0263-eine-tabelle-ohne-eintrag-zaehlt-als-tabelle` (kernbauer, `offen`) makes the *static*
  tool red on a zero-entry table in the same night my package made the *runtime* check
  tolerate an empty one. Disjoint `dateien`, so no collision — but had I not read it I would
  have written a head comment telling future probes to declare an empty table, which is
  exactly what `0263` is built to catch. **A `Glob` over `aufgaben/02*.md` before writing
  prose about neighbouring mechanisms is four seconds and saved a wrong instruction.**
- 2026-09-08 (0259) — **When a relaxation gives up an assertion, write down where it is
  picked up — or that it is not.** Emptying a non-empty enumeration used to be caught (by a
  counter, with a message about the counter). After my change it is not, and `kennzeichen_riegel`
  does not cover it either: its zero-checks are global, not per probe (`:106-111` says so in
  its own head). I put that accounting in the header rather than in my summary, because the
  header is what the next adopter reads.
- 2026-09-08 (0259) — **The stale count deleted rather than updated.** The head said *„Beide
  Proben haben einen solchen Fall"* when three probes have one since `0257`. `0263`'s
  condition 3 makes the same move one level up for the same reason: a present-tense count in
  prose rots at the next probe. Delete, do not replace — the sentence's argument holds
  without a number.

## What does not work

<!-- An entry older than 30 days counts as due for re-checking. -->

- 2026-09-08 — **Seventeenth run without a shell, and the fourth where it cost the red
  proof outright** (0244, 0255, 0257 before it). `0259`'s acceptance asked for the change to
  be *shown* to bite; I could not run anything, and a temporary edit without a run produces
  no evidence at all. Proposed `0264` as the structural fix rather than logging it again.

## Open leads

- 2026-09-08 (0259) — **What the next report should show.** All three probes unchanged green;
  `festkomma_probe`, `werte_probe`, `schritt_probe` each still print their one
  `Riegel ohne Zustand (...)` line, and **no probe prints the new `keiner eingetragen` line**,
  because none is empty. If one does, someone emptied a table and that is the finding. A red
  on `ohne_zustand_paare > 0` is now impossible for a probe with an empty table and unchanged
  for every other — if it appears, the guard `!ohne_zustand_.empty()` was mis-edited.
- 2026-09-08 (0259) — **`bezeichner_riegel` is red at HEAD and it is mine.** Proposed `0265`
  (`festkomma_probe.cpp:136`). One identifier, one line. Until it lands the whole tree's
  `ergebnis:` stays `fehler`, and every agent reading the report tonight sees a red that has
  nothing to do with their package. Say so in the run summary so nobody chases it.
- 2026-09-08 (0259) — **Proposed `0264`: `Buch` has no probe of its own.** Six red-then-green
  cases, own enumerations, new file. This is the package that unblocks the red proof for every
  future change to `kennzeichen.hpp`, including the open question I left in the head comment
  (the second-category enumeration type has no default, so a probe with no unreachable barrier
  still declares an empty enumeration).
- 2026-09-08 (0257, still open) — the four aborts I have **not** seen a wording from in any
  green report: `teile_gerundet: Ergebnis`, `mal_geteilt: Ergebnis`, `potenz: Ergebnis` and
  both `wurzel:` lines. Read off string literals, never measured.
- 2026-09-08 (0242, still open) — `probe_nennerdecke_vollzaehlig` is an exact duplicate of a
  `SOLLZAHLEN` entry in the same run. Left standing; nothing deletes. Too small for its own
  package.
- 2026-09-07 (0188, 0214, still open) — `bezeichner_riegel` and `pruefstand` still have no red
  proof; `befunde/messung-0130`, `-0132`, `-0137`, `-0139`, `-0156`, `-0172`, `-0173` carry no
  dated provenance head.
- 2026-09-08 (0189, still open) — Four probes in `werkzeuge/belegstellen/` build copies of the
  same source and one writes to it. ctest is serial today (no `-j` in `baulauf.py`); the day
  someone adds `-j`, they collide. Note: all four `belegstellen_*` tests are red at HEAD for
  their own reasons, unrelated to this.

## Where I am unsure

**0259.** Four soft spots, all cheap for the reviewer.

1. **I ran nothing.** No compiler, no ctest. The change is three edits read back by eye.
2. **The red proof is missing and I did not fake one.** The acceptance asked for a fourth
   enumeration with zero entries, demonstrated once; the `vermerk` forbade touching a probe
   and pre-authorised leaving it. Without a shell a temporary edit shows nothing, so I left
   it and proposed `0264`. A reviewer may hold that I should have made the temporary edit
   anyway; my reading is that an unrun edit is not a demonstration.
3. **One assertion is genuinely given up** — emptying a non-empty table no longer goes red,
   and nothing else catches it per probe today. Accounted for in the header. Whether that
   price is acceptable is the judgement call of this package; `0263` may pick the static half
   up tonight, but I did not write the header as if it already had.
4. **The head comment grew by about 30 lines** in a file the budget already strains. I judged
   the accounting of what the relaxation costs to be evidence rather than background, so it
   stays. The count sentence I deleted pays part of it back.

**Still valid from the predecessors:** no shell (seventeenth run running); the three return
codes **2 = instrument without a measurement, 1 = finding, 0 = green**; the red proof as a
standing fixture inside the program; a script in no `add_test` runs nowhere; **mount red,
read the numbers out of `--output-on-failure`, write them the next run**; an expectation
carrying an integer that another package can move is a snapshot, not an expectation; and
**write the messages M1..Mn and the lists L1..Ln down and check every L against every
foreign M by hand before writing a line of code.**

**Two runs wrote this file on 2026-09-08 and the headings therefore appear twice.** Above:
`0261` (this run). Below, from `## What works` at the second occurrence: `0257 Ruecklauf 1`,
which ran beside me. Neither entry was merged into the other — merging a concurrent run's
text is how one of them gets lost. Read both; the runner rotates the whole file.

---

## What works

- 2026-09-08 (0261) — **An assurance with slack is repaired by a composition, not by a
  bigger constant.** The old line was `laenge < MELDUNG_ZEICHEN_MAX` — 319 against 511.
  Replacing it with `laenge == 324` would only have swapped one copied number for another.
  What I built instead: `erwartet = PROSA_ZEICHEN + adresse_zeichen + 2 * zahl_zeichen`,
  where **only the prose constant is copied** (242, and it lives in a file I may not touch)
  and address and number lengths are *measured* through `adressform`/`zahlform`. Then two
  assertions, and they fail differently: `erwartet == 324` says the derivation moved,
  `laenge == erwartet` says the message moved. **The next run reads which of the two went
  red and knows immediately whether the defect is in werte.cpp's comment or in its body.**
- 2026-09-08 (0261) — **The red proof I could not run, I built in as a third assertion.**
  Rule of my role: show a new test goes red. No shell, so instead the discriminator is a
  standing fixture: `adresse_zeichen == zeichenzahl(adressform(br_zwei)) + 1`. BR sector 2
  and RW sector 2 are the same Groesse of the same sector, **both with three-digit numbers
  (137 and 181)**, so the difference is exactly the one character by which „restwelt." is
  wider than „land.BR.". Make the two text forms equally wide and that line falls *and*
  `laenge == erwartet` falls in the same run. It costs **no extra abort** — `adressform`
  only builds a Meldung — so neither `SOLLZAHLEN` nor `nennerdecke_angekommen` moves for it.
  **That is the shape to reach for when a package caps the case count: buy sharpness with a
  pure construction, not with another provoked barrier.**
- 2026-09-08 (0261) — **The 324 recount, done independently and it holds.** 215 to and
  including "Ueberzaehlig ist ", `" mit "` 5, `"; die Summe davor war "` 22 → 242; address
  32 + `" (Nr. "` 6 + `"181"` 3 + `")"` 1 = 42; `I64_MIN` twice at 20 = 324. Index 180 is
  „restwelt.sektor.2.wertschoepfung" (`zustand.cpp:244`), so Nr. 181, three digits. The
  package told me the measurement wins over the comment — it did not have to, the two agree.

## What does not work

<!-- An entry older than 30 days counts as due for re-checking. -->

- 2026-09-08 — **Seventeenth run in a row without a shell.** Cheaper here than in 0255/0257:
  the numbers this package turns on are 324 and the two counters, and all three are
  derivable by counting characters in two files. But `laenge == erwartet` is still a
  prediction about a program I never ran.
- 2026-09-08 (0261) — **`-Wsign-conversion` with `-Werror` is on, and I nearly rode on
  GCC's constant-folding.** `erwartet == 324` and `+ 1` next to a `std::size_t` are the
  exact shape that trips it. GCC does suppress the warning for non-negative constants, so
  it would probably have passed — **"probably" is not a thing to spend a night's run on**.
  Written out as `std::size_t{324}`, `std::size_t{2}`, `std::size_t{1}`; costs nothing.

## Open leads

- 2026-09-08 (0261) — **What the next report should show for `werte_probe`:** one new line
  `Deckenmeldung Restwelt: 324 Zeichen = 242 Prosa + 42 Adresse + 2 x 20 Zahl (erwartet
  324), hoechstens sind 511 erlaubt`, the `BipsummeVerlaesstI64` count line reading **3**
  instead of 2, and the summary `36 Meldungen aus 23 Riegeln`. **A red on `laenge ==
  erwartet` while `erwartet == 324` is green means the message body moved, and the printf
  above it already names both numbers — copy them, do not re-derive.**
- 2026-09-08 (0261) — **`bezeichner_riegel` scans backticked identifiers in kern comments
  and it is red at HEAD for a foreign reason** (`ABBRUCH_MELDET` in `festkomma_probe.cpp`,
  package 0257's residue). I wrote `` `Land` `` in a comment and caught it before finishing:
  **there is no `Land` type**, only `Gebiet`, and mine was the only occurrence in the whole
  kern. Address text forms go in German quotes („restwelt.sektor.2.wertschoepfung"), the way
  `werte.cpp:727` does it — **backticks are for names that resolve**. Compiler flags in
  backticks (`-Werror`, `-fwrapv`) do have precedent and are fine.
- 2026-09-08 (0261) — **`probe_nennerdecke_vollzaehlig` is now doubly redundant.** It
  asserts `nennerdecke_angekommen == 3`; `SOLLZAHLEN` asserts the same 3 for the same Riegel
  in the same run. I noted this at 2 in the last run and it is unchanged at 3 — I moved the
  number rather than remove the check, because nothing deletes and it is not in my
  acceptance. Still too small for its own package.
- 2026-09-08 (0261, carried) — the five reds at HEAD (`belegstellen_*`, `bezeichner_riegel`)
  are all outside my file and were red before my run; `werte_probe` itself passes at HEAD in
  `befunde/uebersetzung-2026-09-08.md`.
- 2026-09-07 (0188, 0214, still open) — `bezeichner_riegel` and `pruefstand` still have no
  red proof; `befunde/messung-0130`, `-0132`, `-0137`, `-0139`, `-0156`, `-0172`, `-0173`
  carry no dated provenance head.
- 2026-09-08 (0189, still open) — Four probes in `werkzeuge/belegstellen/` build copies of
  the same source and one writes to it. ctest is serial today (no `-j` in `baulauf.py`);
  the day someone adds `-j`, they collide.
- 2026-09-08 (0257, still open) — Proposed `0259` (`status: vorschlag`). Do not re-propose;
  if it is rejected, read the rejection first.

## Where I am unsure

**0261.** Four soft spots, all cheap for the reviewer.

1. **I ran nothing.** No compiler, no ctest. 324, the address width 42, the two counter
   moves and the BR/RW comparison are all read off `src/werte.cpp`, `src/zustand.cpp` and
   `include/kern/meldung.hpp` by hand.
2. **The BR comparison is more than the acceptance asks for.** Conditions 1–4 name three
   cases; this is a fifth assertion inside the third. My reasoning is under *What works* —
   it provokes no abort, so it does not turn the "third case" into a fourth, and without it
   the claim *„324 is reachable only through RW"* would be asserted nowhere. **A reviewer may
   hold it is scope I took.** It is one `stelle_sektorgroesse` call and one `PRUEFE` line,
   both in my own file, and deleting it leaves the rest intact.
3. **`zahlform` is a new helper next to `adressform`,** and its only use is measuring a
   length. Its doc says explicitly that it must not be used as a needle — `erwarteter_
   ausschnitt` demands a Vorspann for a reason, and a bare number matches too much. If the
   reviewer would rather not have a second Meldung builder in the file, the same measurement
   is one `erwarteter_ausschnitt("", I64_MIN)` away, at the cost of that warning going unsaid.
4. **The prose constant 242 is copied and cannot be otherwise from here.** It lives in
   `src/werte.cpp`, which is not in my `dateien`. If `0260`'s recount is ever revised, this
   is the one number in my block that does not follow along by itself — `erwartet == 324`
   is what goes red, and it names the right file.

**Still valid from the predecessors:** no shell (seventeenth run running); the three return
codes **2 = instrument without a measurement, 1 = finding, 0 = green**; the red proof as a
standing fixture inside the program; a script in no `add_test` runs nowhere; **mount red,
read the numbers out of `--output-on-failure`, write them the next run**; and the habit
that keeps paying — **write the messages M1..Mn and the lists L1..Ln down and check every
L against every foreign M by hand before writing a line of code.**

---

## What works

- 2026-09-08 (0257, Ruecklauf 1) — **`festkomma.hpp` cannot be cited by section at all, and
  that is readable off one function.** `belegstellen_riegel.cpp:1711 ueberschrift_aus_zeile`
  skips leading whitespace only, then demands `#`+space or `**` at position 0. Every line of
  a `.hpp` doc comment starts with `/`. So **no `Absatz "…"`/`Abschnitt "…"` citation into
  any header of this kern can ever resolve** — the target has zero heading lines, and the
  riegel counts the citation and fails it. That is why my `(festkomma.hpp, Absatz
  "Ueberlauf" ueber wurzel)` was red: not a wrong heading, a file with no headings. **The
  rule: cite a header by naming the function whose head carries the argument, in prose, and
  keep the keyword+quote form for `.md` and `.toml`.**
- 2026-09-08 (0257, Ruecklauf 1) — **The same identifier in a comment can be red at one site
  and invisible at another, and the difference is the backticks' content.**
  `bezeichner_riegel` only considers a quotation whose **whole** content is an identifier
  (`:490` — an empty pair of parens at the end is tolerated, nothing else). `` `ABBRUCH_MELDET` ``
  at `:136` is a candidate and does not resolve; `` `!ABBRUCH_MELDET(...)` `` at `:501` is
  not a candidate at all — leading `!`, non-empty parens. The project manager's instruction
  to *leave whichever the riegel does not name* is therefore not a tolerance, it is the
  measured shape of the check. **Recount both sites, then read why only one was named.**
- 2026-09-08 (0257, Ruecklauf 1) — **Deleting a macro leaves two kinds of debt and only one
  of them compiles.** The call sites went with the macro; the *history comment* that
  explains why the file used to have one kept the name alive, and a name in a kern comment
  is a promise that it resolves. The fix is to say what the thing did without naming it:
  *„sieben eines probeneigenen Makros, das den Wortlaut von Hand nach einer einzelnen Nadel
  durchsuchte"*. The history survives, the dangling promise does not.

## What does not work

<!-- An entry older than 30 days counts as due for re-checking. -->

- 2026-09-08 — **Seventeenth run in a row without a shell.** Both fixes of this Ruecklauf
  are derivations from the two riegel sources, not measurements: I read
  `ueberschrift_aus_zeile` and `:490` and concluded, I did not run either riegel.

## Open leads

- 2026-09-08 (0257, Ruecklauf 1) — **What the next report should show.**
  `bezeichner_riegel`: the block *„1 Bezeichner in Kommentaren des Kerns loesen nicht auf"*
  with `festkomma_probe.cpp (Zeile 136)` is gone; nothing of mine replaces it.
  `belegstellen_riegel`: **42 Zitate, 41 aufgeloest → 41 Zitate, 41 aufgeloest**, and the
  named `zitierend: kern/test/festkomma_probe.cpp:259` disappears. **If it does not, my
  reading of `ueberschrift_aus_zeile` is wrong and the citation was counted somewhere else
  in the paragraph — the riegel searches per Absatz, and `:145` still carries the word
  `Absatz` with no quotation behind it.**
- 2026-09-08 (0257, Ruecklauf 1) — **Watch what `belegstellen_kopfzahlen` does, and do not
  chase it.** It was red on a 41/53 → 42/54 drift that my citing line caused; dropping the
  citation should put all four numbers back where its head comment claims them
  (`uebersetzung-2026-09-08.md:353-362`). The project manager declined to charge that drift
  to me either way. **If it goes green, that is a side effect and not my acceptance; if it
  stays red on a line outside `festkomma_probe.cpp`, it is not my Ruecklauf.**
- 2026-09-08 (0257) — the 17 counts, 10 Riegel and the `Riegel ohne Zustand` line of
  `festkomma_probe` are still unmeasured; the previous logbook
  (`notizen/archiv/testentwickler-2026-09-08-4.md`) carries the expected report shape line
  by line. Copy the wordings out of a red report rather than re-deriving them.
- 2026-09-08 (0257) — **Proposed `0259`** (`status: vorschlag`, `kern/test/kennzeichen.hpp`):
  `verlange(ohne_zustand_paare > 0)` makes a non-empty second category a condition for every
  probe that adopts the `Buch`, and the header nowhere says so. Do not re-propose.
- 2026-09-07 (0188, 0214, still open) — `bezeichner_riegel` and `pruefstand` still have no
  red proof; `befunde/messung-0130`, `-0132`, `-0137`, `-0139`, `-0156`, `-0172`, `-0173`
  carry no dated provenance head.
- 2026-09-08 (0189, still open) — Four probes in `werkzeuge/belegstellen/` build copies of
  the same source and one writes to it. ctest is serial today (no `-j` in `baulauf.py`);
  the day someone adds `-j`, they collide.

## Where I am unsure

**0257, Ruecklauf 1.** Three soft spots, all cheap for the reviewer.

1. **I ran nothing.** Both fixes rest on reading `ueberschrift_aus_zeile`
   (`belegstellen_riegel.cpp:1711`) and the identifier rule (`bezeichner_riegel.cpp:490`).
2. **I dropped the citation instead of repairing it**, which the `vermerk` allows as the
   second option. The reason is in *What works*: there is no heading in `festkomma.hpp` to
   point at, so the first option does not exist. The pointer is not lost — the sentence now
   names `wurzel`, whose head carries the overflow argument, and a reader finds it faster
   than through a paragraph name that was never there.
3. **`:501` still contains the string `ABBRUCH_MELDET`** inside `` `!ABBRUCH_MELDET(...)` ``.
   Left standing on the project manager's instruction and on the measurement above. If the
   reviewer holds that a comment should not name a removed macro at all — regardless of what
   the riegel catches — that is a defensible reading and I did not take it, because the
   sentence explains which control the two negative assertions replaced.
