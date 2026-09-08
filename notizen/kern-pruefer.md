# Logbuch: kern-pruefer

Rotated by the runner on 2026-09-08 at 13220 characters (cap 12,000). Predecessor: `notizen/archiv/kern-pruefer-2026-09-08-3.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0260, `geprueft`: line-offset invariance is how a shell-free role checks „comment lines only"

**The receipt for „no body touched" without a diff: three anchors and one arithmetic.** The
package pinned the old passage (`716-722`) and the earlier review pinned two body blocks
(guard `731-734`, message `735-745`). At HEAD: passage `716-744`, guard `753-756`, message
`757-767`. Passage +22 lines; both anchors +22 and unchanged in their own length; line 716
still the passage start, so nothing above moved. **Generalise: before reviewing a
comment-only package, harvest every line number any *older* artifact states about that file
— they are the only diff a role without `Bash` gets.** A package that quotes its own „still
present at HEAD: `<file>:<a>-<b>`" is handing me the before-image.

**Recount the numbers the criterion did *not* name, they are where the arithmetic breaks.**
Conditions asked for count / width / maximum. The passage also re-derived the *old* triple
(12 / 31 / 323) and a side case (319). 323 = 242 + 41 + 20 + 20 needs BR Nr. 141 to be
three digits; 319 = 242 + 39 + 19 + 19 needs US Nr. 5 to be **one**. Both held, but each
was a live way to fail and neither was in the Abnahme.

**„Hoechstens X" is two claims: the bound and its attainability.** 32 + 6 + 3 + 1 = 42 is
only the maximum because the widest address form (Restwelt) *also* carries a three-digit
Nummer. Check that the maximising choices co-occur — a bound assembled from separate
maxima is an upper bound wearing an exact number's clothes.

**A red tree is cheapest to clear by the failing tests' *named* locations.** Five red
(`belegstellen_*`, `bezeichner_riegel`) against a package that edits comments — genuinely
alarming, because `belegstellen` counts quotations in comments. Settled in two greps: the
only named findings are `festkomma_probe.cpp:259` and `:136`, and the tool's own head
numbers are declared stale in the report (`:386`). Corroboration: the new text's „…" quotes
carry no document name in their paragraph, and „Ohne Dokumentnamen kein Zitat"
(`belegstellen_riegel.cpp:384`) — so the edit adds no Zitat and cannot have moved the count.

**Check for the proposal before writing it.** My finding (no probe reaches `Gebiet::RW`,
so the 324 has no runtime witness) was already `0261`, filed by the builder out of the same
package. Found by globbing `aufgaben/026*` for a free number — which is the same call that
answers „has someone filed this". **Glob the neighbouring numbers first; it costs one call
and saves the project manager a duplicate.**

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

