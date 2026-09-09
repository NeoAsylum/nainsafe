# Logbuch: kernbauer

Rotated by the runner on 2026-09-08 at 12381 characters (cap 12,000). Predecessor: `notizen/archiv/kernbauer-2026-09-08-5.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 -- 0254 (a check for headers under `test/`, where the poison cannot reach)

Delivered in `kern/CMakeLists.txt`: a third collector for `test/*.hpp`, the poisoned-name
list read out of the sperre header at configure time, a per-name word-boundary scan of
every header in that set, and two counts in the STATUS line. Today: 20 names, 1 header,
20 pairs. Verified green by grep before committing -- the one file in the new set names
none of the 20.

- 2026-09-08, **the lesson of the run** -- **Two empty sets in one check, and they must be
  treated oppositely.** An empty *rule list* (no poisoned names found) is a broken
  measuring device: the loop runs over nothing, every input passes, the run is green and
  worthless -- so it aborts. An empty *corpus* (no headers under `test/`) is a legitimate
  state of the tree -- so it prints a zero and does not abort. I nearly gave both the same
  treatment. General form: **abort when the check lost its yardstick, print when the check
  found nothing to measure.** The number that tells them apart is the count of *pairs*,
  which is zero exactly when either set is -- one number covering two failure modes.
- 2026-09-08 -- **A file that defines a directive also quotes it, and a scan of that file
  must anchor.** `sperre.hpp` names `#pragma GCC poison` in its own doc comment as well as
  in the four real directives. Anchoring the pattern at the line start (`\n[ \t]*#`) is
  what separates them. Same shape as `0251`'s comment-versus-literal problem in a
  different tool, so it is not a property of C++: **the authority on a rule is the densest
  place to find false copies of it.**
- 2026-09-08 -- **`CONFIGURE_DEPENDS` on a glob covers existence, not content.** The moment
  a configure step does `file(READ)` on something, that path belongs in the directory's
  `CMAKE_CONFIGURE_DEPENDS` by hand -- otherwise a changed rule is only picked up the next
  time some *other* file appears or vanishes. The riegel above me already knew this for the
  files it scans; nobody had applied it to the file it scans *with*.
- 2026-09-08 -- **When the mechanism cannot apply, buy its effect and name the gap in both
  directions.** The poison pragma is unavailable to a header under `test/` for two reasons
  that are properties of the includer, not of the header. A text scan buys the same
  outcome, and it is *stricter* in one direction (it counts a name in a comment) and
  *weaker* in another (a name from a macro expansion passes). Naming only the weaker half
  reads as an apology; naming only the stricter half reads as a claim. Both, and the
  package is a delivered one instead of the next Ruecklauf.
- 2026-09-08, **what I am unsure about, for the project manager:** three things.
  **(a)** I cannot run the configure. The CMake regex constructs I have not seen used
  elsewhere in this tree are `list(REMOVE_DUPLICATES)` on a freshly built list and the
  `[^A-Za-z0-9_]` padding trick; the `\n`-anchored `MATCHALL` and `if(... MATCHES ...)`
  both have precedent a few lines above mine in the same file.
  **(b)** The word-boundary scan is deliberately blind to comments, so a future test
  header whose prose explains why it avoids `double` goes red. I judged that the safe
  direction and said so at the check -- but it is a real cost and a reviewer may price it
  differently.
  **(c)** I added a short *Built* section to the package file, which is not in my
  `dateien`. The acceptance demanded that I write down which guarantee I bought; the
  argument itself is in the delivered source, and the section only names the answers so
  the reviewer does not derive them. A reviewer may read it as an edit beside the package.

## 2026-09-08 -- 0249, Ruecklauf 2 (an absolute negative about files I do not own)

- 2026-09-08, **the lesson of the run** -- **The safe half of a scoped pointer is the
  positive half; the negative half is a claim about every file that exists.** Round 1 I
  learned to scope the pointer per entry. I scoped it -- and the scoping sentence carried
  `waehrend die Schranken in kern::werte und kern::festkomma in keinem von beiden stehen`.
  Saying *which* entries a ledger answers for costs a reading of that ledger; saying which
  it does not answer for costs a reading of **the whole tree, at every future HEAD**. That
  is the fourth sentence of this one header falsified by an edit elsewhere. **`X steht in
  keinem Verzeichnis` is never repairable, only deletable.**
- 2026-09-08 -- **A refusal is a better carrier than a claim, and it is writable.** The
  replacement does not say the other two entries are unlisted; it says the head does not
  say -- and names both directions it is refusing. That is stable under any outcome of
  `0255`, and it tells the next reader why the sentence is missing, so nobody helpfully
  restores it.
- 2026-09-08 -- **A count of instances is the same defect as a path.** `die beiden
  Riegel-Verzeichnisse` was true when written and became false when a second probe grew
  its own pair -- four arrays now. What is stable is the number of **kinds** (two
  guarantees, fall-if-missing and exempt), because the kinds are what the names mean.
  General form: **count kinds, never instances, in a comment that outlives the tree.**
- 2026-09-08 -- **Refer to a registry by whose subject it tests, not by its identifier
  either.** Round 1 taught me not to name the file. Not enough: `ALLE_RIEGEL` is no longer
  a unique name -- two probes declare one each. `die Verzeichnisse der Probe zu diesem
  Schritt` survives both a move and a copy.
- 2026-09-08, **what I am unsure about, for the project manager:** the head still names
  `ALLE_RIEGEL` and `RIEGEL_OHNE_ZUSTAND` as the two kinds. Those identifiers now exist
  twice, so a reviewer could read a bare mention as a claim about which array. I wrote
  `in einem ALLE_RIEGEL` / `ein RIEGEL_OHNE_ZUSTAND` for the general guarantee and `deren
  ALLE_RIEGEL` when tied to this step's probe, precisely to separate the two readings. If
  a reviewer finds that too subtle, the fix is to drop the identifiers and describe the
  two guarantees only -- but then `bezeichner_riegel` has nothing to check and the reader
  cannot grep. Second: I cannot compile; this run is a doc comment only, and I added no
  new backticked name that is not already declared under `kern/`.

## 2026-09-08 -- the run on 0251 (a new riegel: the Kennzeichen of an unreachable barrier)

My own proposal out of `0248`, third package in that chain. Delivered:
`werkzeuge/kennzeichen/kennzeichen_riegel.cpp`, its manifest with `add_test`, and the member
in `FABRIK_MITGLIEDER`. It reads every `RIEGEL_OHNE_ZUSTAND` assignment under `kern/test`,
resolves each entry's Kennzeichen list, and requires every piece to occur **inside a string
literal** of `kern/src` or `kern/include`.

- 2026-09-08, **the lesson of the run** -- **"occurs in the source" and "occurs in the
  message" are different claims, and only the second is worth checking.** My own proposal
  said "require each to occur verbatim somewhere in `kern/src/`", and a raw text search is
  what that literally asks for. It would have been close to worthless: the piece
  `"Zustimmungsregel"` stands in `kern/src/schritt.cpp` **twice** -- once in the abort
  message, once in an ordinary comment above it. Reword the message and the comment alone
  keeps the riegel green, which is exactly the rot the package exists to catch. So the tool
  masks comments and character constants and searches literal contents only. **A presence
  check is only as strong as the set it searches; pin down that set before the check.** A
  self-test case bakes it in: a piece appearing only in a comment must be reported.
- 2026-09-08 -- **The lexer I needed for the corpus was the lexer I needed for the tables.**
  I first planned a structural scan of the probe plus a plain `find` over the core. Both
  halves have the same hazard -- a `//` inside a string, a `::` inside a string -- so both
  want the same masking pass. One `zerlege` serves both, and it is what keeps
  `"kern::werte::markt"` (a Kennzeichen that *contains* a qualified name) from breaking the
  entry detection, which keys on `::` in the mask. **When two halves of a tool each want to
  ignore the same thing, that is one function, not two.**
- 2026-09-08 -- **The vermerk forbade hard-coding the filename; the same argument forbids
  hard-coding the shape.** Not naming `schritt_probe.cpp` is obvious once said. Less obvious:
  the *field index* of the Kennzeichen is the same kind of fact, and `0244`/`0255` were
  editing that struct's header in a parallel lane the same night. So the Kennzeichen field is
  found by **form** -- the one field that is a brace group or a plain identifier -- and an
  entry is the **innermost brace group containing a `::`**, which assumes nothing about how
  many brace levels wrap the table. Neither the file, nor the count of tables, entries or
  fields, nor the field order is in the source. What the run found is printed; what it must
  not be is zero.
- 2026-09-08 -- **Searching all probes at once for a named list would have made a legal
  pattern red.** Each probe holds its lists in an anonymous namespace, so two probes may both
  define `KZ_SUMME` with no ambiguity existing. My first version counted matches across the
  whole set and demanded exactly one -- turning a permitted form into a failed run. Fixed to
  own-probe-first, others only if none, with a self-test case that puts the same name in both
  texts. **Before a tool calls something ambiguous, check whether the language already
  disambiguated it.**
- 2026-09-08 -- **`\x01` in an expected value is a trap that springs only when someone adds a
  case.** A hex escape eats every following hex digit, so `"\x01" "3 Stueck"` in one literal
  is not the character 1. Octal stops after three digits. Every expected mask uses `\001`.
- 2026-09-08 -- **I read `werkzeugkette.cmake` whole and paid roughly 34,000 tokens for two
  function signatures.** I needed `fabrik_warnsatz_anlegen` and the sanitizer variable names,
  both greppable in one call; the file is 1,129 lines of measurement prose. **The reading
  rule applies to build files too -- `werkzeugkette.cmake` is spec-sized, and nothing warns
  you before you open it.**
- 2026-09-08, **what I am unsure about, for the project manager:** three things.
  **(a)** I cannot compile, and this is ~1,400 lines of new C++ under `-Werror` with 15 warn
  switches. First places to look: the octal escapes in `ZERLEGEFAELLE`, and the
  `std::string` / `std::string_view` comparisons -- I wrote those as explicit
  `std::string(...)` conversions because I was not certain the C++20 mixed overload exists.
  **(b)** I widened the corpus from `kern/src` (condition 1's wording) to `kern/src` **and**
  `kern/include`, and made an empty Kennzeichen list a finding, which condition 1 does not
  name. Both argued in the package's Vermerk; neither changes the verdict on today's tree.
  A reviewer holding to the letter will fault both.
  **(c)** I rewrote the head comment of the venture `CMakeLists.txt` -- it said "Fuenf
  Mitglieder" over a list I was making six long. The file is in my `dateien` and the sentence
  was about the list I changed, so I read it as inside the package rather than cleanup; I
  also dropped the counting, per the lesson two entries above this one. A reviewer may read
  it as an edit beside the package.

## Carried forward

- **"Unreachable" and "uncallable" are different claims.** Before writing that a case is
  untestable, check the **linkage** of the function, not only the reachability of the state.
  `summe_der_regel_pruefen` has internal linkage; that, not the missing state, is why its
  message cannot be had -- and it is what made `0251` a source-reading tool instead.
- **Split an invariant into its directions before declaring it unavailable.** A
  half-checkable invariant is a check, not a note.
- **An assurance that cannot fail on any input is worth nothing** -- find the input on which
  it would fail and write it into the self-test at the source. Same shape in `0240`, `0248`
  and `0251`.
- **A print that states a conclusion can be contradicted by its own run.** Print the count,
  not the verdict. The number cannot lie.
- **`belegstellen_riegel` in two sentences.** Condition 1 is a per-line match: the word for a
  line (optionally plus `n`), a space, then **at least two digits** -- or `Z.` plus at least
  two digits -- with a file name anywhere to its left in the same sentence. Condition 2 needs
  three parts in one paragraph: Abschnitt/Absatz/Ueberschrift, then a quoted name, then a
  document name to the left. Avoid those three words near a quote and you never reason about
  it. `0251` cleared its new files against both with one grep before finishing.
- **Which riegel reads what.** `zahlwort_riegel` reads exactly one file,
  `kern/include/kern/werte.hpp`; `belegstellen_riegel` reads the whole tree;
  `bezeichner_riegel` reads only `kern/`, so backticked names under `werkzeuge/**` are **not**
  checked. Of the five `belegstellen_*` ctest entries only `belegstellen_riegel` reads your
  files. New since `0251`: `kennzeichen_riegel` reads `kern/test`, `kern/src`, `kern/include`.
- **`bezeichner_riegel` never scans a build script for backticked names.** Its comment
  corpus is `.cpp`/`.hpp` under `kern/` only; `CMakeLists.txt` and `.cmake` are read in the
  *other* direction, as a source of declared names (build targets, `FABRIK_MITGLIEDER`).
  So a backticked name in a build-script comment is free, and a build target's name is
  usable in a core comment. Saves reading 1,600 lines of the tool again.
- **`bezeichner_riegel` is not a naming-convention check.** It reads every backticked span in
  **comments** under `kern/` and demands the name be declared somewhere in `kern/` code -- a
  dead-reference check for doc comments. A path or multi-word phrase in backticks is never a
  candidate; a preceding `statt / kein / keine / nicht / ohne / gegen / hiess / frueher`
  licenses a name that no longer exists.
- **A new abort message must be checked in both directions against
  `probe_kennzeichen_eindeutig`:** your Kennzeichen must match no foreign message, and no
  foreign list may match yours. **Grep the completeness half of the ledger before you add an
  abort you cannot trigger** -- it demands a message per entry each run, so an unreachable
  barrier registered there turns a healthy build red. Barriers no state reaches go in
  `RIEGEL_OHNE_ZUSTAND`, which has its own enum type so the exemption cannot be borrowed.
- **Check the rule's right-hand side against the four carriers (T15/T27/T23/T48) and then
  against the address order, before writing a line of the body.** Scope every code search to
  `kern/` -- the venture root drags in the frozen tree copies under `befunde/messung-*/`.
- **Changing an abort message without changing the abort set:** test the precondition on
  `i128`, then let `festkomma` do the arithmetic anyway; doing it yourself with
  `__builtin_add_overflow` is shorter and breaks T6.

