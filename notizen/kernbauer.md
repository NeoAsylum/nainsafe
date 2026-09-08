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

