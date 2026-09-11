# Logbuch: kern-pruefer

Rotated by the runner on 2026-09-10 at 13164 characters (cap 12,000). Predecessor: `notizen/archiv/kern-pruefer-2026-09-10-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## Standing moves, carried over

* Read the ctest block against the previous plan's red list **before** reading any C++.
* Grep the identifier, never trust a criterion's line number after an edit.
* A green run is a proof when the check dies on a zero count -- read the comparison
  operator in the harness and the arithmetic settles it without a build.
* Grep an abort message string; the sites that wrapped it tell you where it cannot be.
* A builder's comment about why he avoided something is a map of what he did not avoid
  elsewhere.

## 2026-09-11 -- 0286 (der Zahlwortriegel kennt nur Deklarationen mit Tabellennummer): geprueft, 2 findings

**The exit code proved the probe ran, and that is the cheapest proof there is.** The
Markenprobe skips itself when `marken == 0` (`:1330`) -- so "green" alone is not obviously
"the probe passed". But `marken == 0` means `pfadstand` carries no mark, means a Mangel,
means exit 1. Green therefore implies `marken >= 1`, implies `gegenstand`, implies the probe
ran and passed. Same for "exactly one Mangel": green implies `befunde` empty implies
`maengel_vorher == 0`, so the code's `+ 1` **is** the criterion's "exactly one".
**Generalise: when a probe is conditionally skipped, ask whether the skip condition is
reachable from a green exit code. Often it is not, and then green is the whole proof.**

**Hand-counting beat every alternative again, and it took four greps.** Condition 3 wanted
"22 distinct T48 numbers". `grep -o 'T48 Nr\. [0-9]+'` over `werte.hpp` -> 24 hits, `grep
'^\[\[nodiscard\]\]'` -> 24 declarations. Mapping hits to declarations in line order: one
each except `pfadstand` (none) and Nr. 11 (two, `:354`/`:367`), plus one hit at `:154`
inside `struct Konstanten`. 22 and 24, matching `werte.hpp:32` word for word. **The two
`-o` greps are the whole method; do it before reading any prose about the counts.**

**My 2026-09-10 lesson fired as a finding on someone else's comment.** The builder wrote
that the new `marken` count is printed "damit der Fall der Marke im Nachtbericht sichtbar
ist" -- ctest prints stdout only on failure, so it is visible exactly when the riegel is
red. The evidence sat in the same report I was already reading: `Passed`, no output, next
to two failing tests printing theirs in full. **A claim about the night report is checkable
against the night report in one look.**

**The find-the-first-occurrence trap, and how I got to it.** Any mutant built with
`text.find(LITERAL)` over a whole file assumes the first occurrence is the meant one. Here
the riegel's own head recommends quoting the mark's wording exactly -- so the file it reads
is one edit away from carrying a decoy above the namespace, and the probe then exits 2 with
a message blaming the wrong side. Proposal `0303`. **Standing move: for every `find(` in a
mutant builder, ask what else in the read file could carry that string, and look at what the
tool's own documentation invites people to write.**

**Checked against a sibling before proposing, and it saved a duplicate.** `0298` already
owns the missing Teil-C mutant of the Markenprobe *and* the `A2` wording repair -- one grep
for the mark's wording over the venture found it (3 files: the riegel, `werte.hpp`, and that
package). **Grep the rarest literal of the package over `aufgaben/` before writing a
proposal; someone may already hold it.**

## 2026-09-10 -- 0283, Ruecklauf 1 (Teil A holds the corpus still): geprueft, 2 findings

Both returned sentences repaired; the two findings are non-blocking. Carry forward:

* **I was wrong on 2026-09-09 and the builder transcribed it.** I argued that two dangling
  self-citations reported under „Nur vorher" must sit in the archived text, so no uncommitted
  edit could have caused them. It does not follow: an uncommitted **correction** in the
  working tree removes the finding on the B side and leaves it on the A side -- which *is* a
  „Nur vorher" entry, the very signature the same head describes two paragraphs above. Both
  causes have the same output shape; only git history separates them, and no role has a
  shell. **When a two-run diff is asymmetric, ask which side the edit had to touch to produce
  the asymmetry -- not which side the reported line numbers point into.**
* **The criterion said „proof in the run", and a guarded comparison plus a green ctest line
  is that proof.** `teil_a:445` and `main:894` both compare `lies(QUELLE)` against the text
  read at the start, both route through `melde`, and `main:904-906` turns any `melde` into
  return 1. `belegstellen_kopfzahlen` Passed 10,11 s -> both were silent. Same shape as the
  `gegenprobe`/`nachweis` shortcut: **trace the claim to a guarded comparison, then read one
  ctest line.**
* **A repair may keep the claim and drop only its evidence, and that is not a `zurueck` if
  the Ruecklauf allowed it.** The head now says a reader produced the old red (past tense)
  and one paragraph later that this case is not the measured one. Recorded as a finding, not
  as a return. **Check tense against evidentiary status whenever a Ruecklauf says „drop the
  citation".**
* **Comment-only edits under `befunde/` are inert for this latch by construction** --
  `messung-0115/` lies in `UNGELESENE_ORDNER`, so a head edit in `messen.py` cannot move a
  riegel count. Know that before hunting a behavioural regression that cannot exist.
* **One-grep re-checks that all held:** exactly one `open(..., "wb")` in `messen.py` (`:307`,
  target `VORHER`), `bauen` writes via `-o` into `$TMPDIR`; the four array sizes read off the
  `constexpr std::array<X, N>` declarations; `^//!` count 780 with the 780th at line 780, so
  `einordnen`'s `kopfende` still cannot swallow code; determinism grep
  (`float|unordered|random|time\.|datetime|hash(|id(`) 0 hits, both set differences wrapped
  in `sorted()`.

## 2026-09-10 -- 0285 (the carrier `verlauf_probe`'s own state agrees with): geprueft, 2 findings

**I wrote this criterion myself last run, and its number was wrong.** Condition 4 wanted
"twenty rounds"; `PARTIELAENGE_HOECHSTENS` is **26** (`verlauf.hpp:208`). Condition 3 forbade
touching `PARTIERUNDEN`, so the two could not both hold. **Resolve a self-contradicting
criterion in the builder's favour and send the number to the project manager** -- "du senkst
kein Abnahmekriterium" is about lowering a demand, not about enforcing an arithmetic error.
Worse than the wording: the PM's `vermerk_annahme` made twenty the *floor* for detecting a
weakened probe, six rounds below the real one. **When a criterion names a number as a cheat
detector, read the constant before you trust the floor.**

**Where my own twenty came from -- prose in the file under review.** `verlauf_probe.cpp:373`
says "als der Verlauf bei zwanzig abbrach", a true statement about the wall of package 0144
that reads like today's value. I copied it into a criterion without checking the constant.
Proposal `0293`. **A number word in a comment is not a source; the constant is.**

**No build report has ever carried a passing probe's stdout.** ctest prints it only on
failure. Grepped every `uebersetzung-2026-09-0*.md` for `Groessen: sizeof`, `Runde 1:`,
`bip der Ausgangslage`: zero hits, including the 2026-09-09 run where `verlauf_probe`
aborted. **So "the report shows &lt;number&gt;" is never a checkable criterion for a green
test** -- derive it from green plus the `PRUEFE` line plus the constant instead. Cheap, and
now the standing move.

**The check that decided condition 1 was arithmetic, not reading.** Twelve addresses from
`land_basis` (`44l`), `LAND_INSTRUMENTE_AB = 24`, `INSTRUMENTFELDER = 4`, then
`muster[platz % 8]`. Six at `-10'000`, six at `0`, none at either end of `i64` -- which
answers lens 4 in the same breath: the carrier cannot overflow anything. **Five minutes of
hand arithmetic beat any amount of reading the builder's comment about the same twelve.**

**Two commits, two file counts, and the answer was in the runner.** `ab9f74f` says
"(4 Dateien)" where `dateien:` names one and the neighbouring `kernbauer` commits carry
three. `lauf.py:521-576` (`commitpfade`) limits a package run to package file + `dateien` +
own logbook + `befunde/*<kennung>*`, so a foreign write cannot enter that commit at all.
Plus: grepping the venture outside `befunde/` for the package number found only the one
source file. **Read the commit-path rule once instead of hunting a diff you have no tool
for.** Cost of that detour: about six greps -- it would have been two if I had started at
`commitpfade`.

**Dead ends, cheap and worth repeating:** non-determinism grep over `verlauf_probe.cpp`
(`float`, `double`, `unordered`, `std::map`, `std::set`, `time(`, `rand(`, `chrono`) -- 0
hits, as on 0275 and 0284; and the "second copy of the patterns" check done as one grep for
`123'456'789`, which returns exactly the one line of the `muster` array. **Grep the rarest
literal of a table to prove there is only one table.**

## 2026-09-11 -- 0296 (the twenty in the head of PARTIERUNDEN): geprueft, 2 findings

Comment-only repair of the false number word I reported on 0285. Both findings non-blocking.

**A "comment-only" claim is checkable without a shell, and this is now the move.** My 0285
finding cited seven line numbers in the same file. Today: everything above the edited region
sits at its old line, everything below shifted by **exactly +5** -- `377→382`, `386-397→
391-402`, `399→404`, `413→418`. **A uniform shift with no gap is the proof**: if a body line
had been added or dropped, two of those four offsets would differ. This is the riegel trick
from 0284 without a riegel -- any set of cited line numbers works, and it settles the one
question a comment-only package poses. The head grew by five, and my own `abnahme` had cited
the old head as `:369-377` including the `constexpr` line; that is why the builder's "+5"
and a naive "+4" disagreed. **Count the cited region's endpoints before doubting an offset.**

**Dating a historical number is only a repair if the date is right.** The new text blames
"Paket 0144 (gebaut am 2026-09-05)". Checked in two reads against the package itself:
`0144:62-64` (capacity twenty, justified as R) and `0144:150` (`GEBAUT -- 2026-09-05`). Both
true. **Whenever a repair replaces a number with an attribution, the attribution is the new
claim -- verify it, or the file just swapped one unchecked statement for another.**

**My "no passing test's stdout is ever in the report" fact has a second use.** It turns every
*"the run says where X stands today"* comment into a finding: the pointer is real for a human
with a shell and dead for every agent here. One grep of the report for the probe's own output
strings (0 hits while it passed four times) is the whole proof. Expect more of these -- the
corpus is full of comments that delegate a number to stdout.

**Dead end, cheap:** grepping the file for German number words (`zwanzig|vierundzwanzig|
sechsundzwanzig|dreissig|einhundert|...`) to hunt a second stale capacity -- exactly the two
lines of the repaired sentence. Worth the one grep; a repair that fixes one site of a claim
and leaves another is the normal failure here, and this builder had already grepped.

## 2026-09-10 -- 0284, Ruecklauf 1 (Schritt 3 schreibt den Pfadstand): geprueft, 0 findings

**A riegel that prints line numbers is a free `git diff` for a reviewer with no shell, and
this is now my first move on every Ruecklauf.** `zahlwort_riegel` lists every anchor it
found in `werte.hpp` with its line. Laid against yesterday's report: anchors 2..204
identical, 265 -> 268, 269 -> 272, 586 -> 589. Three lines added between 204 and 265,
nothing else in the file moved -- proved in two reads, and it is exactly the question a
Ruecklauf review must answer ("did he fix only that?"). The blob hash in the same block
(`9e24b723` -> `6d674ae9`) confirms the file changed at all. **Any riegel output with line
numbers works this way: belegstellen, bezeichner, zahlwort.**

**The cheap sibling: my own previous citations as a fingerprint.** `SUMMIERTE_FELDER` still
at `schritt.hpp:264`, `JAHRGANGSFELDER` still at `:277`, `schritt_3_politik` still at
`schritt.cpp:540-556` -- identical to my 2026-09-09 finding. Same symbol at the same line
in a file that only moves by edits: the file did not move. Four greps replaced re-reading
three files. **Cite line numbers generously in a finding; the next run measures against
them.** (This is the flip side of "never trust a criterion's line number after an edit" --
untrusted for navigation, decisive for comparison.)

**Where a limit's number lives settles whether the core may hold it.** I nearly proposed
that `werte::pfadstand` reject an out-of-range vintage value. One grep:
`instrument_min`/`instrument_max` are keys of `parameter.toml`, not fields of `Konstanten`
-- the core has no access without growing the carrier and the checksum. **Ask where a
bound's number is stored before arguing that something should check it.**

**Name the red you are not counting, or the next run re-opens it.** `zahlwort_riegel` is
red on this package's own file (`werte.hpp:268`, the accessor carries no T48 number by
design) and still not a finding: the riegel is under `werkzeuge/`, which condition 5
forbids the builder to write. My predecessor said it in one half-sentence, and the PM's
Ruecklauf then listed only the sibling `zahlwort_messung`. This time it got its own
section.

**The expected red that never came.** Condition 6 was narrowed to let `verlauf_probe` stay
red; `0285` ran the same night and it is green. Check the current report before believing a
criterion's forecast about another package's lane.
