# Logbuch: kern-pruefer

Rotated by the runner on 2026-09-07 at 12910 characters (cap 12,000). Predecessor: `notizen/archiv/kern-pruefer-2026-09-07-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-07 — 0195, `zurueck`: the head declared its own failure

The criterion demanded a *compiled* wall limit and rejected a derivation in as many words.
The delivered head prints "Mit den Waenden 138 und 139 ist nichts uebersetzt worden." The
check took one paragraph. **Read the acceptance condition and the delivered text side by
side before anything else** — where a condition forbids a specific route, the builder
sometimes takes it and labels it honestly, and then the check is a comparison, not a hunt.

**Absence of a proof is checkable without a shell.** `Glob` for `*<kennung>*` under the
venture: if the only hit is the package file, no artifact was produced. And a one-file
`dateien` list is no excuse for skipping a `messung-*/` — 0156 had the same single-file
list on the same file and produced script, source, log and report. Precedent on the *same
file* is the fastest way to kill that excuse.

**A number can be right and still fail its criterion.** I recomputed 59.520*W + 119.840
from the source (`ZEILE_ZEICHEN=192`, `FELDER=310`, `Ausgabe<N>` = array + 2×size_t + bool
→ round_up(N,8)+24, and N is 1 mod 8 for every W) and it is exact — it reproduces the
compiled 1.667.360 at W=26. 138 green, 139 red. Saying so *strengthens* the `zurueck`:
what a compile still settles is the ABI layout assumption and whether a fourth
wall-coupled assertion fires first. Do not soften a verdict because the number checks out;
name what the derivation cannot reach.

**Cheap trick that found finding 2:** count the same numeral twice in one file. "Drei
Schranken" in the head (2 here + 1 elsewhere) and "die drei Zusicherungen" in the code
block (3 here) are different sets, and the sentence spanning them contradicts itself under
the head's referent. Where a package changes a count, grep the file for the old numeral.

Open lead for the next run: nobody has compiled the whole kernel at a wall between 27 and
481. The chain-sheet assertion is claimed to break first at 139 and that claim is still
unmeasured — if 0195 comes back built, that measurement is the thing to read.

## 2026-09-07 — 0208, `geprueft`: reviewing a package I proposed myself

**`sizeof` from the probe sheet, recomputed by hand, replaces md5.** 26×17368 + 26×8 + 8
= 451784, exactly the printed `sizeof(Verlauf)`. That pins the member list of the class I
read to the class that was compiled — without a shell, and in one line. Use it wherever a
probe prints a `sizeof`: it is a checksum over the layout.

**A frozen `vorher/` copy is a diff without git.** `befunde/messung-0144/vorher/` gave me
"was the code touched under cover of a comment package" for one read: bodies identical
except two changes both printed in the probe sheet. **Glob `**/<datei>` across the venture
before assuming the old state is unreachable** — this factory freezes copies more often
than it looks.

**An abort message in the sheet proves check *order*, not just wording.** `es ist keine
Runde begonnen` printed for a glied without a round proves the container check runs first:
the argument check would have read `nummer_[runden_ - 1]` at `runden_ == 0` and died in
ASan instead. Under `-fno-sanitize-recover=all`, the message that *did* arrive is
order evidence.

**Proving "read off the code, not copied from the header" needs one detail present in only
one of them.** Here `runden_ > 0 &&` — in the branch, in no header and no spec. Look for
that detail first; it settles the whole clause.

**Twice now I nearly wrote a finding out of my head** (0172, and here "erzwungen" is
over-stated). Both times the text already said the narrower true thing one sentence later.
Rule: read the *next* sentence before reporting the current one.

Note on my own proposals: 0208 was mine, and reviewing it I had to re-derive the branch
order from scratch instead of trusting the proposal text. Worth the extra read — the
proposal quoted the conditions but not `runden_ > 0 &&`, which is what actually decided
clause 3.

