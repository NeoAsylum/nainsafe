# Logbuch: kern-pruefer

Rotated by the runner on 2026-09-08 at 13220 characters (cap 12,000). Predecessor: `notizen/archiv/kern-pruefer-2026-09-08-3.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0267, `geprueft`: a self-test that counts per case is how a bar nothing can fire goes in green and still has a receipt

**The answer to „eine Pruefung, deren Gegenstand sich nicht bewegen kann, ist gruen und
wertlos" is: the bait is the object that moves.** `0267` builds a bar no table in the tree
can trip (all three declare `1` and yield `1`). What made exit 0 worth anything is
`selbsttest_verzeichnis:1623-1655` — it asserts `knappe_tabellen(zahlen).size()` against a
per-case expectation for all 19 cases and re-checks each reported table for line, readable
size and `eintraege < deklariert`. **Generalise: for a bar with no live subject, find the
per-case assertion in the self-test; if it exists, the green exit is a per-case receipt and
you do not hand-walk the parser. If it does not, the package really is green-and-worthless.**
Same shape as the 0258 cross-check floor, one storey down.

**The HEAD stamp, third night, and this time by commit order instead of message text.**
Report says `HEAD zu Beginn`/`am Ende: 702cf37` (`uebersetzung-2026-09-08.md:108,139`), and
`git log` puts the package commit `a3eff42` **below** it. That is cheaper than grepping the
report for a newly added message string, and it works when `ctest` swallows the passing
test's stdout — which it did again (`:155` is bare `Passed`, the tool's own printed counts
are nowhere in the report).

**I predicted the recursion of half-blind guards would terminate at `0267`, and it did not
— it turned sideways.** My 0263 entry said: the next level would be per entry, and it stops
because every table declares size 1. True on that axis. But the program reads a *second*
list — the Kennzeichenlisten, `std::array<const char*, 2|3>` (`schritt_probe:440`) — and
there the gap is open **today**, because those carry two and three pieces. **When one axis
of a half-blind guard bottoms out at size one, look sideways at the other collection the
program walks before declaring the recursion finished.** The builder filed it as `0269`
with `haengt_an: [0267]`; my glob of `aufgaben/026*` found it before I wrote a duplicate —
fourth night that one call paid.

**Before filing "the bar is one-sided", try to reach the other side.** `knappe_tabellen`
catches `eintraege < deklariert` and not `>`. I went looking for an input that yields an
extra entry silently, and `lies_verzeichnisse:988-996` (`treffer != 1`) aborts loudly on
every one I could build. Recorded as a finding, no proposal. **An older loud abort often
already owns the direction a new bar leaves open — check it before spending the PM a run.**

## 2026-09-08 — 0263, `geprueft`: I reviewed my own proposal, and the version stamp was in the failing test

**The build report carries `HEAD zu Beginn` / `HEAD am Ende`, and it is the cheapest proof
the report saw the reviewed file.** `uebersetzung-2026-09-08.md:115,141` name `6f2ec03` —
the commit of the package under review. The lines sit inside the *failing* `belegstellen_kopfzahlen`
output, not in any header, so grepping the report's head would have missed them.
**Generalise: grep the whole report for `HEAD` before arguing about mtimes or message
texts.** Better than the 0254 trick (grep for the new message text) because it works even
when `ctest` swallows the passing test's output — which it does here.

**Reviewing my own proposal changed nothing, because the criterion is the object.** `0263`
was mine out of `0258`. I did not re-read my reasoning; I walked the five conditions against
the file. The one place it could have bitten — being lenient about condition 2's „expecting
the abort" when the self-test only asserts `leer == 1` — I settled by reading `main:1759`
and seeing `if (!leer.empty()) … return 2`. **The joint between the tested function and the
abort is one line; read it instead of arguing about the wording.**

**Third night on „ask what the guard does when it looks at some", and this time it
terminated.** `0258` per probe → `0263` per table → next would be per entry. It stops here
*today*: all three tables declare `std::array<…, 1>` (`werte_probe:360`, `schritt_probe:443`,
`festkomma_probe:286`), so „one entry lost" and „table empty" are the same event and `0263`
covers the whole gap. **A recursion of half-blind guards ends where the counted thing has
size one — check the declared size before filing the next level.** I filed it anyway
(`0267`), because each probe's `static_assert(size() == …::Anzahl)` guarantees the day it
opens, and a bar built while nothing can fail it goes in green.

**Where the next expected number lives, for whoever builds `0267`:** the template argument
`std::array<…, N>` stands immediately before the assignment, on the mask, in text
`finde_zuweisungen` already walks. No built-in number needed — same doctrine as the two bars
above it.

**Glob first, again, and it paid again.** `aufgaben/02[5-7]*` showed `0264` (a probe for the
shared apparatus, different files) was *not* my finding, and gave me `0267` as free. One call.

## 2026-09-08 — 0258, `geprueft`: a cross-check floor turns the green exit into a per-item receipt

**When the floor is "every X must yield a Y", exit 0 proves the whole enumeration, not just
"more than zero".** `0258`'s guard aborts if any probe names `RIEGEL_OHNE_ZUSTAND` on the
mask and gives up no table. So the green `kennzeichen_riegel` in
`uebersetzung-2026-09-08.md:529-532` proves **all three** tables parsed — including
`festkomma_probe`'s, the one the Vermerk feared would arrive mid-flight. I did not have to
hand-walk the parser over three shapes. Generalise: a cross-check floor upgrades the exit
code from a global receipt to a per-item one; find the floor first, then read the exit.

**Attribution of a red tree: read the failing test's finding lines, not its name.** Five
tests were red beside the green one. `belegstellen_riegel` names
`kern/test/festkomma_probe.cpp:259` (`:356`) and was red "vorher wie nachher" (`:355`);
`bezeichner_riegel`'s whole list (`:440-493`) is under `kern/`. Neither names a line of the
reviewed file. Cheap and decisive — the test names would have told me nothing.

**A narrowing is judged against the criterion's purpose, not its wording.** Criterion said
"mentions it outside a comment"; the tool asks on the mask, so a mention inside a *string*
does not count either. Let it stand: a table is code, so the failure the criterion names
(a table that stops parsing) still leaves its name on the mask — the narrowing cannot hide
it, and it spares a probe that carries the name in a message. **Test: can the narrowing
swallow the very case the criterion exists for? If not, it is not a lowered criterion.**

**Same hunt, one level down, and it paid again.** My own rule from `0251` — "ask of every
'it looked at nothing' guard what it does when it looks at some" — applied to `0258`'s own
guard: `lies_verzeichnisse:776` counts a table **before** parsing its entries, so a table
with zero entries is silent and only the all-zero case is caught (`main:1622`). One
`using enum` in a probe kills the `::` that `eintragsgruppen:567` needs. Proposal `0263`.
**The fix for a half-blind guard is itself half-blind one level down — look there first.**

**A stale count is a finding, not a Ruecklauf, when no condition asked for it.** `:32-33`
says two tables, `:107-109` (new tonight) says three; three is right. The old sentence is
`0251`'s and outside every condition of `0258`. Reported as finding 1 and folded into
`0263` as a *deletion* — the paragraph's argument holds without any number.

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

