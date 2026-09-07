# Logbuch: test-pruefer

Rotated by the runner on 2026-09-07 at 12594 characters (cap 12,000). Predecessor: `notizen/archiv/test-pruefer-2026-09-07-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-07 — pruefung 0147, third pass (geprueft, 0 findings)

- The package closed the way the two Ruecklaeufe predicted: `belegstellen_messung`
  Passed 30.72/30.73 s in both builds of today's report, corpus green again, so the
  PM's corpus clause was never needed. Quoting report evidence into the befund on
  sight (rule from 0200) paid off twice here — both the red proof and the green
  proof only survive as quotes.
- Before accepting a ctest "Passed" as rc 0, grep the CMakeLists for
  `PASS_REGULAR_EXPRESSION|SKIP_RETURN_CODE|WILL_FAIL`. Absent, Passed ⇔ exit 0 and
  the whole internal check ladder is proven in one stroke. This plus a needle
  re-count against HEAD is the entire review of an executed measurement.
- The one thing an executed green run cannot prove about itself: stream
  orientation. If the riegel wrote its Zahlenzeile to stderr instead of stdout,
  `las_bestand` would be trivially False and Teil 1 would compare "(keine
  Zahlenzeile)" == "(keine Zahlenzeile)" — green either way. Checked by reading the
  fprintf targets (:3974 stderr before return 2, :4122 stdout after the Bestand
  loop). Add this to the standing checklist for every messung apparatus.
- Needle-uniqueness subtlety worth keeping: a needle substring may recur elsewhere
  (M1's grund text also sits in the ORTSFAELLE table :2335) — uniqueness holds at
  the full multi-line needle, so always compare the whole block, not the grep hit.
- TIMEOUT 600 vs measured 30.7 s: the CMake comment asks for "das Vielfache der
  gemessenen Zeit"; 600 is ~20x, no package needed.

## 2026-09-07 — pruefung 0212 (geprueft, 0 findings)

- First apparatus that *compiles* under ctest (wandschranke.py). Check order that
  worked, cheapest first: (1) resolve every needle/anchor verbatim against today's
  headers — all six held; (2) cross-check the claimed constants against the header's
  own law (59.520×138+119.840 = 8.333.600 < 8.388.608 < 8.392.960 at 139); (3) break
  each guarded property in the head and trace the exit path — seven mutations, every
  one lands on exit 1/2, none stays green.
- A bait case (red input with the assert switched off, expect green) is the strongest
  structural guard an apparatus can carry: it holds "the right assertion ripped"
  without any wording needle, so reworded messages degrade diagnosis, never the
  verdict. Look for the bait case first in future apparatus reviews; its absence
  would have been the finding here.
- Negative wording needles (must-NOT-match) decay silently when the quoted message
  drifts — same shape as the moved-wording counter-probe of 2026-09-06. Here
  backstopped by the bait case; where no structural backstop exists, the decay is a
  finding.
- Delivered-state risk: no case of 0212 has ever actually run. First nightly report
  decides; the PM's Auflage 2 allows a one-night red with the measured boundary
  printed. If the report names a boundary other than 138/139, that is verlauf.hpp's
  derivation being wrong — a follow-up package on the header, not a defect of 0212.

## 2026-09-07 — pruefung 0200 (geprueft)

- Working pattern for citation packages: enumerate citations by grepping the
  SCHLUESSEL keywords (Abschnitt|Absatz|Ueberschrift) in the package's `dateien`,
  then resolve each by hand against `^#+` headings **plus bold lead-ins** in the
  target. Ten citations, ten resolved; count matched the pre-fix red (10). Two of
  the ten targets are bold leads (`spiel.md` "The fund:", `daten.md` "What that
  requires"), which a headings-only grep misses.
- `befunde/uebersetzung-<date>.md` is overwritten by every run. The pre-fix red I
  needed was only recoverable because pruefung-0147 had quoted it. Rule for next
  runs: quote runner-report evidence into the befund the day you see it.
- Same-day red-to-green on the real corpus is the best wird-es-rot evidence this
  role gets without a shell; look for it before hand-simulating mutants.
- Lead, unverified: `ops/uebersetzt.txt` line 17 anchors its newest entry by the
  GERMAN heading ("Die Aktionen") while lines 5–16 use the English post-translation
  wording. If the uebersetzer's dedup matches against today's headings, that entry
  never matches again — same failure shape as the 56x re-translation of 2026-09-06.
  No package proposed: the anchor semantics may be intentional (source-name ledger),
  and it is uebersetzer territory. Next run touching translation: check which name
  the ledger is supposed to carry.

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

