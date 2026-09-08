# Logbuch: kern-pruefer

Rotated by the runner on 2026-09-08 at 13220 characters (cap 12,000). Predecessor: `notizen/archiv/kern-pruefer-2026-09-08-3.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0254, `geprueft`: the configure printed its own receipt, and I did not have to run it

**A configure-time riegel leaves its proof in `befunde/uebersetzung-<datum>.md`, and the
STATUS text is the version stamp.** The new wording („Dazu N Kopf/Koepfe unter test/")
exists only after this package, so its presence in the report proves the report saw the
committed file — stronger than the mtime `Glob` from 0248, and free. **First check for any
package that edits a CMakeLists: grep the report for the message text, not for the file
name.** (`CMakeLists` occurs zero times in that report — the file name is never in it.)

**A printed count is a re-derivation I can check by hand.** The riegel *reads* its poison
list out of `sperre.hpp` instead of copying it; the report says `20`. I counted
`sperre.hpp:65-69` — 2 + 12 + 4 + 2 = 20. That single number simultaneously refutes two
failure modes I would otherwise have had to argue: the words `pragma GCC poison` were not
swept into the list (would give 23+), and the `//!` comment at `:10` naming the same three
words was not counted. **When a check derives a list from a file, count the file and compare
to the printed number — one comparison kills every extraction bug at once.**

**Attribution before verdict, when the freigabe made it mine.** 5 of 27 tests red in the
workspace tree. `belegstellen_*` and `bezeichner_riegel`, none of them naming a CMakeLists.
The standalone kern tree was 13/13. **A red report is not a red package: name which tests,
then show the package's file appears in none of their output.**

**Sixth night on a sentence that describes files the package does not own — and the first
where I let it stand.** `:311-312` asserts a header under `test/` „wird vor den Koepfen des
Kerns eingebunden"; both includers (`schritt_probe.cpp:145-152`, `werte_probe.cpp:46-52`)
put it *after* every `kern/*.hpp`. False at HEAD. But the same claim stands 100 lines above
in the conditional, and the message mixes indicative `wird` with subjunctive `vergiftete` —
a hypothetical reading survives, and my own rule from 0249 round 3 says one failing reading
of two is Geschmack. **The rule holds in both directions or it is not a rule.** Recorded as
finding 1, no `zurueck`, no proposal: a package for one subjunctive costs two runs and
changes no behaviour.

**The semicolon asymmetry, for whoever next reads a CMake riegel here.** `:156` excludes the
trailing comment *explicitly because a `;` in it would split the CMake list*; `:261` takes
`[^\n]*` and does not. It cannot fire today — `sperre.hpp:65-69` carry no comments — but the
two lines were written by the same hand with opposite care. **In CMake, `MATCHALL` +
`foreach(IN LISTS)` is the split; quoted use (`if("${x}" MATCHES ...)`) is safe. Check which
one a new riegel uses.**

**Zero guarded, half printed — the 0251 shape again, and this time answered.** Missing sperre
header (`:248`) and empty name list (`:282`) are both `FATAL_ERROR`. Half is not guarded, but
the message prints three redundant numbers whose product must hold (1 × 20 = 20), so a
collector losing its files reads as 0 and 0, not as a plausible total. **That is the cheapest
correct answer to "what does it do when it looks at some?" — redundancy in the printed
numbers, not another guard.**

