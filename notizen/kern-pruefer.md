# Logbuch: kern-pruefer

Rotated by the runner on 2026-09-08 at 13671 characters (cap 12,000). Predecessor: `notizen/archiv/kern-pruefer-2026-09-08-4.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 -- 0269 (kennzeichen_riegel, short characteristic list): geprueft, 2 findings

**The cheapest proof that a build report is the right one.** Condition 6 said "at HEAD", and
`uebersetzung-<datum>.md` carries no commit. Do not guess from the file's git status: read the
`cmake --build` block and see **which sources recompiled**. On 2026-09-08 exactly three did
(`kennzeichen_riegel.cpp`, `belegstellen_riegel.cpp`, `kennzeichen_probe.cpp`) -- the night's
three changed files. A report that recompiles the package's file is post-package. Cost: one
`Read` of 40 lines instead of an argument.

**Ask whether the new bar can fire today, separately from whether it is correct.** Lehre
2026-09-06 ("eine Pruefung, deren Gegenstand sich nicht bewegen kann, ist gruen und wertlos")
is a question about the *tree*, not the program. Here: grep the three real lists, read their
declared sizes, ask what one deletion does. 3/3, 2/2, 2/2 -- and dropping an element is legal
C++ (the rest is value-initialized), so the bar bites. `knappe_tabellen` from 0267 cannot,
and the package said so itself. Both are fine; the difference has to be *stated*, not assumed.

**The one case worth hand-tracing was named in the package.** Condition 3 was the whole work,
and only one self-test pair (22/23) separates mark-counting from part-counting. Tracing that
pair through `zerlege`/`hinter_fuellsel` took five minutes and covered the package's core.
Where a package names its own load-bearing condition, trace that one by hand and read the
rest.

**Dead end:** I hunted for a false positive on the real tree for half the run. There is none --
the build report already proves it empirically, and I should have read the report first and
then looked for gaps the report *cannot* show (unnamed blind spots, wrong numbers in prose).
That is where both findings came from.

