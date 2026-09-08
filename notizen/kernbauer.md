# Logbuch: kernbauer

Rotated by the runner on 2026-09-08 at 12937 characters (cap 12,000). Predecessor: `notizen/archiv/kernbauer-2026-09-08-7.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 -- 0267 (a table that yields less than it carries)

Delivered in `kennzeichen_riegel.cpp`: `finde_zuweisungen` now returns `Zuweisung{name, auf}`
instead of the brace index alone, `deklarierte_groesse` reads the last template argument
before the name (`NICHTS` when unreadable), `Tabellenzahl::deklariert` beside `eintraege`,
`knappe_tabellen` as the new floor, the abort in `main` between the `leere_tabellen` block
and the three zero-checks, and three self-test cases (16 -> 19) plus a `knapp` column on all
nineteen. Recounted at HEAD: three tables, each declaring `1` and yielding one, so the new
set is empty -- and the bar is **satisfied, not dormant**: all three sizes parse.

- 2026-09-08, **the lesson of the run** -- **A bar built while nothing can fail it is cheap
  exactly when the thing it measures is bound to something that grows on its own.** The
  worthless-green rule (`lehren.md` 2026-09-06) does not turn on whether the check fires
  today; it turns on whether its subject *can move*. Here each probe carries
  `static_assert(RIEGEL_OHNE_ZUSTAND.size() == ...::Anzahl)`, so the declared size is welded
  to the enumeration: the day a second stateless barrier is found, the table declares two
  **in the same run** that opens the gap. General form: **before calling a green check
  worthless, find what would move its subject. If that mover is mechanical and already in
  the tree, the check is a bait; if there is no mover, it is decoration.**
- 2026-09-08 -- **Widen the finder's return value rather than re-derive its rule downstream.**
  The declared size sits *before* the name, and `finde_zuweisungen` only handed back the
  brace. Walking back from the brace over `whitespace = whitespace` would have been a second
  copy of the `Name = {` rule -- the identical failure mode I paid for in `0258` with the two
  countings. Returning both indices cost one struct and two call-site edits, and the rule
  stays in one place. **When a caller needs a position the finder passed through, take it out
  of the finder.**
- 2026-09-08 -- **The fallback is the load-bearing half, not the concession.** `NICHTS` (no
  readable size) is deliberately not a finding: `using Tabelle = std::array<T, 2>;` is valid
  C++, and a bar that reddens on a legal change of form gets deleted by someone who never
  learns what it stood for. The third new case is the bait text with **only** the declaration
  form changed -- everything else identical, still short -- which is the only shape that shows
  the silence comes from the unreadable size and not from the text.
- 2026-09-08 -- **Two floors that overlap at zero is right, and it needs saying once.** A
  table declaring 1 and yielding 0 is both `leer` and `knapp`. `main` aborts on the older one
  first because its message names the `using enum`, which is the usual cause; the self-test
  records the overlap on cases 14 and 16 rather than hiding it by making the sets disjoint.
  **Disjointness bought by an extra condition is a condition that can be wrong later.**
- 2026-09-08 -- **`-Wconversion -Wsign-conversion -Wshadow -Wold-style-cast -Werror` is the
  warning set here** (`werkzeugkette.cmake:108-113`). Checked before writing: `wert * 10` and
  `(NICHTS - 9) / 10` follow the file's existing `i + 1` pattern (non-negative constants, no
  warning), the digit accumulation casts explicitly, and no new local shadows a namespace-scope
  name. Overflow is caught *before* the multiply, not measured after -- `NICHTS` means "not
  readable", so a wrapped number would be readable and wrong.
- 2026-09-08, **what I am unsure about, for the project manager:** three things.
  **(a)** I cannot compile. Riskiest edit: the nineteen `TABELLENFAELLE` initialisers all grew
  a trailing `, 0` (or `, 1`), and `{..., 0, 0, 0}` does not say which zero is which. Second
  place to look: the backward `<`/`>` matcher in `deklarierte_groesse` -- it is the only loop
  in this file that runs backwards over a range it did not itself bound.
  **(b)** The acceptance says the size is read "in the text before the assignment". I
  implemented "the last argument of the angle-bracket list immediately before the **name**",
  which is narrower than the written words -- `constexpr Tabelle NAME = {` yields `NICHTS`
  even though a `2` stands in the text two lines up. That narrowing *is* condition 2 as I read
  it, and case 19 asserts it, but a reviewer holding to the letter will call it a miss.
  **(c)** `0264` runs in the lane beside me and adds a fourth table under `kern/test`. If it
  declares a size larger than the entries it yields, my new bar reddens the tree tonight on
  foreign work. Per the package I report that rather than soften the bar -- but the red would
  land in my review, not in `0264`'s.

## 2026-09-08 -- 0269 (a characteristic list that yields less than it carries)

Same shape as `0267`, one object over: the **named** `KENNZEICHEN_*` list. Delivered in
`kennzeichen_riegel.cpp`: `struct Listenzahl` (probe, name, mask position, line, pieces,
declared), a fifth out-parameter `listen` on `lies_verzeichnisse` filled at the resolution
site, `knappe_listen` as the new floor, the abort in `main` behind `knappe_tabellen`, and
six self-test cases (19 -> 25). Recounted at HEAD: three resolved lists, 3/3, 2/2, 2/2 --
the bar is satisfied, not dormant, and unlike `0267`'s it stands open **today**, because
every list in the tree already carries more than one piece.

- 2026-09-08, **the lesson of the run** -- **When you port a bar to a neighbouring object,
  the counting rule is the work; the bar is the easy half.** For the table an entry was a
  brace group and the count was unambiguous. For a list the unit is a *mark*, and `zerlege`
  merges adjacent literals because the language does. The naive one-literal-one-element rule
  counts **too high** -- and this bar asks `read < declared`, so too high means **silent on a
  broken list**: a green run on damaged text, not a red one on healthy text. General form:
  **before porting a threshold, work out which direction the wrong counting rule errs in. If
  it errs toward silence, the naive rule does not merely misreport -- it deletes the bar.**
  The one case that separates the two readings is the only one worth writing: three literals,
  two marks, three declared. Under the correct reading it fires; under the naive one, `3 >= 3`
  and nothing happens.
- 2026-09-08 -- **A new expectation column with a default beats eighteen hand-edits I cannot
  compile.** `Tabellenfall` grew `listen_knapp = 0` as a defaulted last member; the eighteen
  rows it does not concern stay byte-identical, and the six that do write all nine fields.
  My own note from `0267` said the nineteen trailing `, 0` were the riskiest edit of that run
  -- `{..., 0, 0, 0, 0}` says even less than three zeros did. The default **is** the
  expectation: the self-test checks the field on every case. **Aggregate NSDMI is how you add
  an assertion to a table without touching rows that were already right.**
- 2026-09-08 -- **`Zuweisung fund` replaced three parallel locals, it did not add a fourth.**
  The resolution loop kept `quelle`/`stelle` beside `gefunden`; I needed the name position
  too, and the honest move was to keep the whole `Zuweisung` the finder already returns
  rather than carry a third index alongside. Same rule as `0267`: take the position out of
  the finder. It reads better and it is one fewer thing that can drift.
- 2026-09-08 -- **Two entries may name one list, and then it is one list.** Deduplicated on
  (probe, mask position) -- exact identity, not a heuristic; name and line both fail, because
  two lists can share a line. This is not an exception that weakens the bar: it cannot hide a
  distinct list, and without it the header would print a count of objects that do not exist.
  Case 24 holds it. **A report that counts one thing twice states a number that is false, and
  this repo pays for false numbers.**
- 2026-09-08 -- **The zero overlaps again, and again I did not buy disjointness.** A named
  list declaring 2 and yielding 0 is now caught by `knappe_listen` (code 2) instead of
  `gleiche_ab`'s `leere_liste` (code 1). Stated once in the head comment and left alone.
  `leere_liste` stays reachable exactly where condition 2 puts it: embedded lists and
  unreadable declarations. **An extra condition to keep two bars disjoint is a condition that
  can be wrong later.**
- 2026-09-08, **what I am unsure about, for the project manager:** three things.
  **(a)** I cannot compile. Riskiest edits, in order: the trailer `fprintf` in `main` embeds
  `` `{"eine lange " "Meldung", "b"}` `` inside a split string literal -- escaping there is
  the one place a slip would not be obvious by eye; then the argument lists of the four new
  `fprintf` calls (I counted specifiers against arguments by hand, all match); then the
  aggregate-init assumption that eight initialisers for a nine-member aggregate with a
  trailing NSDMI is valid C++20. If that last one is wrong, all eighteen old rows fail at
  once and loudly, which is the good failure.
  **(b)** The line I report is the **name's** line, not the brace's -- `knappe_tabellen`
  reports the brace's. Deliberate: the declared size stands before the name, so that is the
  line the reader must reconcile with the contents. A reviewer holding to symmetry with the
  table floor will call it an inconsistency. It is one; I think it is the right one.
  **(c)** `0270` runs in the lane beside me on `kern/test/kennzeichen_probe.cpp` and builds
  deliberately oversized lists. I checked: that file's table is deliberately **not** named
  `RIEGEL_OHNE_ZUSTAND` (its own head comment, line 29), and its only mention of the name is
  in a `//!` comment, which never reaches the mask. So its lists are never resolved and my
  bar cannot see them. That is a fact about tonight, not a guarantee -- if `0270` introduces
  a `RIEGEL_OHNE_ZUSTAND` there, the bar reads it.

