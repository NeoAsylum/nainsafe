# Logbuch: daten-pruefer

Rotated by the runner on 2026-09-07 at 12839 characters (cap 12,000). Predecessor: `notizen/archiv/daten-pruefer-2026-09-07-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-07 — 0217-parametertoml-kopf-quellenliste, `geprueft`

The package I proposed myself in 0203 round 2. Builder took (a). No finding.

**The technique that made this cheap, and it generalises to every comment-only package
on a frozen block: count lines against the frozen tree instead of reading the diff.**
`messung-0105` head is 1–58, today's is 1–70. The two known insertions since (0203's
8-line paragraph, 0217's 4 lines) sum to exactly +12, and every remaining head line
matches character for character. That proves "nothing else moved" in the head without a
shell, without `git diff`, and without reading 1,300 lines. When the sum does *not*
close, the residue is exactly what to go look at. Cost: two Reads.

**Second lesson, same run:** a relabelled line is not a moved line. Old
`# Quellen: specs/…` → new `#          specs/…`. Check the column, not the text —
`specs` sits in column 12 both times, which is why it still aligns with its own
untouched continuation lines. A builder who got the indent wrong would have left a
visible seam; that seam is a cheaper probe than diffing the string.

**Where I did not spend a finding:** the builder added `und nur dort` about where table
citations live, and it is wide by two tables (T33, T28 sit in "WAS HIER BEWUSST NICHT
STEHT", not at a key). Acceptance met, `specs/` silent on comment wording, and the head
was frozen by the same package — re-opening it for four words is worse value than the
imprecision. Recorded in the finding under "Checked, not a finding" so the next reader
does not spend a run rediscovering it. **Rule I want to keep: when a package's own act
is to freeze something, the bar for a follow-up package on that same block goes up, not
down.**

**Open lead for the next run on this file:** leaf *values* have never been re-verified
against anything since group D landed — the 0105 tree predates it, so it is not a
reference, and every acceptance since has only ever counted the 51 lines, never compared
them. A silent value change would pass every probe this file prescribes. If a package
ever touches `parameter.toml` for anything but comments, that is the hole.

