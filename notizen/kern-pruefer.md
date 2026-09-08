# Logbuch: kern-pruefer

Rotated by the runner on 2026-09-08 at 13671 characters (cap 12,000). Predecessor: `notizen/archiv/kern-pruefer-2026-09-08-4.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 -- 0273 (multiplikationsriegel, new latch): geprueft, 2 findings

**A criterion can contradict itself, and the vermerk is where the contradiction is resolved.**
Condition 5 demanded the test be `Passed`; condition 3 plus `vermerk_pm` ordered a red with the
divergent lines named, and the red happened. Both cannot hold. The vermerk is **not** the
builder's Begruendung -- it is the commissioning note, it is part of what I am told to read,
and here it addressed the reviewer by name. I judged on it and wrote the contradiction as a
finding **to the project manager**. Test: would a `zurueck` be workable? The package forbade
touching `specs/` and `kern/` and forbade a sixth rule -- the builder could not have made it
green. **A Ruecklauf whose object cannot move is the mirror of lesson 2026-09-06 and just as
worthless.**

**A latch package is checked against the corpus, not against the latch.** The decisive work
was not reading the 1,350 lines of C++ -- it was four independent recounts on the tree:
`Glob` for the file count (23), `Grep` for `constexpr u64` outside `test/` (exactly 7,
matching the run, with the function declarations correctly excluded by the `(`-check), the
hand-trace of the one real rule-5 site, and the two red sites read in their own file. Every
number the run printed had a cheap outside check. **Do those first; the source only explains
a number that already disagrees.**

**Where to hunt in a text latch: the shape of the trigger, not the rules.** The rules were
right. The gap was one level below them -- `ist_binaeres_mal` requires whitespace or a name
character on **both** sides, so `wert *= b` is invisible and does not even raise the line
count. Same class, checked and empty: `)*x` / `x*(` (0 matches on the tree). **Ask of every
text latch: which spellings of the thing does the trigger not have a case for, and grep each
one against the real tree.** That is where Befund 2 came from; proposal `0275`.

**Dead end:** I looked for a false positive where rule 1 excuses a real `i64 * i64` by
swallowing a call argument into the operand region. T7 `:816` names `positionswert` as the
danger; `werte.cpp:550` runs through `mal()` and the file's only ` * ` is a `static_assert`.
Correctly empty, and cheap -- one grep of one file that the spec itself pointed at.

## 2026-09-08 -- 0271 (kennzeichen_riegel, the wrong number): geprueft, 2 findings

**The build report can name its own HEAD, and this one does.** `uebersetzung-<datum>.md:106`
carries *„HEAD zu Beginn: bff08ee"* and `:137` *„HEAD am Ende"*. That is stronger and cheaper
than yesterday's recompile-fingerprint trick — **look for the HEAD line first**, and fall back
to reading which sources recompiled only if it is absent. Both were there today and agreed.

**A count package is checked by recounting, and by asking what pins the count.** The four
numbers (19/7/26/16) took one `Read` of the table plus a grep for `lesbar: false`. The better
question came after: *can the new case's numbers drift while green?* Here they cannot —
`deklariert` for `<const char*, 2>` is squeezed to exactly 2 by two **older** cases (one needs
> 1, the other ≤ 2), so the head's quoted message is pinned by the case set as a whole. Ask
that of every "the text now matches the code" package: which other case closes the interval.

**The finding that pays is at the edge of the sentence the package ordered.** Condition 2 said
"an element that is not a string literal yields no mark". The builder wrote exactly that, so
the condition holds — but `stuecke_aus` collects every mark between the braces with no notion
of element boundaries, so `{ERSTES("x"), "b"}` gives two marks, reports **nothing**, and binds
the wrong wording. The ordered sentence covers the safe half and denies the dangerous one.
**When a package orders a piece of prose, check the prose against the code, not against the
package** — the criterion can be met and the sentence still be false.

**Dead end:** I looked for a stale count elsewhere in the file (`fuenfundzwanzig`,
`achtzehn`) and for another file asserting the case count. Nothing — one grep, correctly
empty, and worth repeating because it is cheap.

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

