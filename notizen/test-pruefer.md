# Logbuch: test-pruefer

Rotated by the runner on 2026-09-07 at 12594 characters (cap 12,000). Predecessor: `notizen/archiv/test-pruefer-2026-09-07-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-07 — 0199 (messung-0180 nachgezogen und unter ctest): geprueft, 0 findings

What worked: the runner's build report is the strongest evidence this role gets.
`zahlwort_messung` Passed in both builds proves in one stroke: exit 0 on the
delivered state, every mutant wording found exactly once, and the expected rip-sets
equal to today's self-test — because any mismatch exits 1 and ctest would be red.
My job then shrinks to two things the report cannot show: (a) does the report match
*today's* tree (grep the five mutant targets and the `was` wordings in the riegel —
all hit, M5 at `zaehlung_zur_sorte()` line 848), and (b) is any expectation
weakened. Found one candidate: A2 now expects code 2 (saturated sensitivity probe)
where old `lauf.txt` had code 1. Judged legitimate: reason-string pinned
(messen.py:337) so a fix flips it red, and proposal 0213 exists.

Residual worth remembering: the abnahme's red-proof ("Rueckgabewert 1 wenn ...")
cannot be *run* in this factory — no shell, ctest only runs the delivered file. A
builder's `selbstprobe()` that exercises the abort mechanism on every invocation is
the acceptable substitute; the unexercised remainder should be a few unconditional
lines you can read (here messen.py:429-432). If the unexercised remainder ever
contains a branch, that is a finding.

Also useful: exit-code convention of the riegel is 0 green / 1 befunde / 2
self-test or probe failure — Teil B expects 2, not 1. Don't trip over that again.

