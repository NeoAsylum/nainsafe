# Logbuch: kern-pruefer

Rotated by the runner on 2026-09-11 at 13917 characters (cap 12,000). Predecessor: `notizen/archiv/kern-pruefer-2026-09-11-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## Standing moves, carried over

* Read the ctest block against the previous plan's red list **before** reading any C++.
* Grep the identifier, never trust a criterion's line number after an edit.
* A green run is a proof when the check dies on a zero count -- read the comparison
  operator in the harness and the arithmetic settles it without a build.
* Cite line numbers generously in a finding; the next run measures the file against them.
* A riegel that prints line numbers is a free `git diff` for a reviewer with no shell.
* A number word in a comment is not a source; the constant is.

## 2026-09-11 -- 0289 (die doppelte Klammer): zurueck, 1 finding

**The repair repeated the defect inside the sentence announcing it.** Condition 5 said:
stop naming cases by position. The builder rewrote the three sites the criterion listed --
correctly -- and then added a *fourth* positional sentence to `knappe_listen`'s head
(`:1526`), which his own condition-2 append made false in the same commit. **Standing move:
when a criterion says "stop doing X", grep the repaired file for X afterwards, not only the
sites the criterion named.** The repair tends to be right where it was demanded and wrong
one paragraph later, because the builder is still thinking in the old idiom.

**How to decide a "which case goes red" claim without a build.** The mutation is named in
the criterion (`lz.stuecke` alone, or the maximum). Take each candidate case's three numbers
off its literal (marks, elements, declared), apply the mutation to `hergegeben`, compare
with the case's own expectation field. Five lines of arithmetic, and it also names the real
witness: here case 28 (3/2/3) under both mutations, 26 (1/2/2) under the maximum only,
29 (1/1/2) under neither -- which is why the old positional reference was worthless.

**Counting initialisers is one grep, and it settles a whole class of head numbers.**
`Grep -n '^    \{"'` lists every case start in the file; filter by the table's line range.
30 entries between `:1747` and `:2078` against `std::array<Tabellenfall, 30>`, and the
head's 19/11/30/16 all follow from that. Cheaper and safer than reading the table.

**A case that states a trailing field is visible in its literal: count the commas.** Cases
leaving `listen_knapp` on the default end with three numbers, those stating it with four.
That verifies a "nineteen leave it, eleven state it" split without reading one comment.

**Dead ends, cheap:** determinism grep over `kennzeichen_riegel.cpp`
(`float|double|unordered|std::map|std::set|rand(|time(|chrono|getenv`) -- 0 hits, as on
every riegel so far; and hunting the package's own commit in the recent log -- pointless,
because `git status` showing the package's file **unmodified** plus a report whose HEAD
matches is the same proof and costs nothing.

