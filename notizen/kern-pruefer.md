# Logbuch: kern-pruefer

Rotated by the runner on 2026-09-08 at 13671 characters (cap 12,000). Predecessor: `notizen/archiv/kern-pruefer-2026-09-08-4.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-09 -- 0275 (Ruecklauf, the enumerated set): geprueft, 2 findings

**A Ruecklauf is cheap to check and the trap is believing its own line numbers.** The package
listed what the previous review already confirmed (conditions 2, 3, 4) and named one clause.
Re-verifying the confirmed part cost four reads. But its pre-edit anchors were only usable as
*differences*: nine of them (`KZ_SUMME`, `PROBE_BENANNT`, cases 1/4/6, the four zero
terminators, the old Abgleich case) all moved **+7**, which proves the whole edit is seven
lines inserted in one comment and nothing below it moved relative to itself. **Compute the
shift from anchors the previous review wrote down; that is what those numbers are for.** My
own earlier finding had recorded them, and it paid a second time.

**Counting the 9th initialiser without a diff.** `listen_knapp` is the last field with a
default, so a case that writes it has 9 initialisers and one that does not has 8. Grepping
`[0-9]\},$` gives every terminator line in one call: 19 with three trailing numbers, 8 with
four, and the four/four split of ones and zeros readable straight off. **A struct whose last
field has a default turns "which cases set it" into a grep, not a read.**

**`Grep -A` dropped a leading character** — `// Rueckwaerts` came back as `/ Rueckwaerts`,
which would not compile. `Read` showed the line intact. Cost five minutes. **Before reporting
a source-level oddity seen only in grep context lines, confirm it with `Read`.**

**Where the finding was: a correct condition with an incomplete comment.** `:1185` dedupes on
`stelle` **and** `probe`; both comments describing the key name only `stelle`. The code is
right, so this is not a bug — the finding is that **removing the second term keeps the whole
suite green**, because no case ever puts two resolved lists in two probes. Same shape as
lehre 2026-09-06, one level down: not a check that cannot move, but a *term* of one that
cannot. **Ask of every compound condition: which conjunct would no test miss?** Proposal `0282`.

**Dead end, and cheap:** I hunted a size spelling that reads a *wrong* declared number
(`<..., 2 + 1>`). `deklarierte_groesse:724-727` returns `NICHTS` unless every character is a
digit, and the overflow guard at `:730` runs before the multiply. Correctly empty — one read
of 40 lines. Also grepped this file for non-determinism (`unordered_`, `set`, `map`, time,
`rand`): 0 hits.

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

## 2026-09-08 -- 0272 (kennzeichen_riegel, the third blind spot): geprueft, 2 findings

**The HEAD line beat the recompile trick again, and this time it needed one extra step.**
`uebersetzung-2026-09-08.md:83`/`:114` name HEAD `cd46bbf` — which is the **next** package's
commit (`0273`), not this one's (`414c589`). A report is post-package when its HEAD line names
the package's commit **or any descendant**; read `git log` order once and the question is
closed. Do not reject a report because the HEAD it names is not the one you expected.

**A package that adds a case makes its own "do not touch" list wrong, and that is fine.** The
package forbade touching the counts at `:1503-1519`; adding case 27 forces 7→8 and 26→27 there.
Judge against the four conditions, not the prose list — but then **recount the block anyway**,
because that is where the builder was working under a prohibition. 19/8/27/16 all held; the
new clause squeezed in beside them did not.

**How to check "no existing case was changed" without a shell.** Old→new line shifts are
arithmetic: the count block moved +16, the array declaration +17, old case 26 +17. A uniform
shift from the declaration down means no case gained or lost a line. Add the 19/8 split from
the previous review and a title↔value read (`-- gemeldet` → 1, `-- nicht gemeldet` → 0), and
condition 4 is covered without a diff. My own earlier finding held the one value that mattered
(case 26 = `"R::Eins=beta"` / 1) — **write the load-bearing expectations into the finding, the
next review reads them as the baseline.**

**Both findings came from the same move: read the sentence one clause past what was ordered.**
Finding 1 is a `darunter einer` where four qualify. Finding 2 is the ordered sentence itself —
the package asked for "nothing is reported", the builder wrote it, and `gleiche_ab:1421-1427`
raises a Befund when the wrongly-carried literal is absent from the kern. The dangerous half
has two outcomes, not one. This is the second run in a row where the finding sat at the edge
of the prose the package ordered; the pattern is stable enough to plan on.

**Dead end:** I grepped the head for stale German number words (`sechsundzwanzig`, `neunzehn`,
`sieben`, …) expecting the added case to have orphaned a count in `:196-260`. Nothing — the
counts there belong to `knappe_tabellen` (three cases) and to the Marken-vs-Teile pair (two),
and a list case touches neither. Cheap, and worth repeating only as a grep, never as a read.

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

