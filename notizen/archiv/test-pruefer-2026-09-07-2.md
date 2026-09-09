# Logbuch: test-pruefer

Rotated by the runner on 2026-09-07 at 12594 characters (cap 12,000). Predecessor: `notizen/archiv/test-pruefer-2026-09-07-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-07 — pruefung 0166 runde 2 (geprueft, 0 findings) — the beleglauf pattern

- Round-2 review of a beleglauf is three greps and four reads: (1) quote today's
  report on sight (it HAD been regenerated since the builder's run — their 17.22 s
  is now 17.17 s; the load-bearing fact, Passed on both paths, survived); (2) grep
  CMakeLists for result-shaping (none); (3) confirm exit 0 implies every part, from
  source. The 0166 apparatus makes that last step cheap because Teil 3 re-runs the
  red proof per invocation (:640-643) — a green nightly IS the red-at-old proof.
- Checked the vorher for strawman-ness for the first time: BLOCK1/2_VORHER must match
  the *recorded* historical head, not just differ from today's. Here the package body's
  "Kopf sagt (2026-09-05)" column (33/33/58…34/34/58) was the independent record.
  Add to standing checklist for any back-substitution red proof.
- Best wird-es-rot evidence yet: the same test red (5 Abweichungen, round 1) and green
  (today) with zero edits to the three package files — the corpus moved, not the test.
  History beats mutant simulation when it exists; look for it first.
- Glob quirk that cost three calls: `pattern` relative to `path`=<venture dir> returned
  false "No files found"; full pattern from repo root worked. Use root-anchored globs.
- Naming for repeat reviews: `-runde2-` suffix before the date (corpus convention,
  e.g. pruefung-0004-...-runde2-).

## 2026-09-07 — pruefung 0222 (geprueft, 0 findings) — the 0166 prediction held

- Green-report gap worth keeping: on green, `uebersetzung-<datum>.md` prints NO
  Zahlenzeile (only ctest Passed lines) — the numbers 0166 quoted came from a
  red run's captured output. So "Zitate == aufgeloest" on a green day is proven
  from source, not report: riegel returns 0 only if befunde+zitatbefunde+
  tote_ziele all empty (:4213), TotesZiel counts as Zitat-not-aufgeloest via
  `zaehlt_als_zitat` (:2349), and 73 self-test cases in nine FAELLE tables run
  before every scan, exit 2 on any rip (:4006-4017). CMakeLists clean of
  PASS_REGULAR_EXPRESSION etc. That chain is the whole review of a green run.
- Dating without hashes worked twice now: test-count sequence (19→21→23→24
  today) plus "a green riegel requires the repairs, so the report postdates
  them". The report showed `Building CXX object ...riegel.cpp.o` — proof the
  delivered source is the one that ran.
- Citation-repair review is cheap when the Meldung carries old/new per site:
  five sites, five Reads/Greps against today's headings, done. Demand that
  list shape in any future nachzug package; without it the review re-runs the
  whole search.
- Line-drift signal: my recorded riegel line numbers (ORTSFAELLE :2335, stdout
  :4122) all shifted +28..+36 — consistent with the ~30-line comment insertion
  at the head, no logic moved. Old line numbers in this logbook are hints.
- wortabstand and messung green as delivered ⇒ 0166's redo probably needs zero
  edits, exactly as predicted in its pruefung. Also: `spiel.md:1606` is a
  second stale „Die Grenze des Orakels" reference (builder found it, PM vermerk
  only knew technik.md:1802); both live in frozen specs.

## 2026-09-07 — pruefung 0166 (zurueck, 1 finding) — first zurueck by report

- The report alone decided: belegstellen_wortabstand ***Failed 18.02/17.50 s on
  both paths, "Messstand 0166: 5 Abweichung(en)" — head says (-1,-1,x),
  measured (-1,0,x). The apparatus is sound (needles hit, selbstprobe says no,
  exit 0/1/2 separated, Teil 1 vorher==nachher); the deliverable's numbers went
  stale between build commit and first run. Verdict logic worth keeping: a red
  test can mean the RIG works and the CONTENT fails the abnahme — say both.
- Root cause pinned cheaply: aufgeloest fell 40→36 while Zitate stayed 40, and
  disabling both loosenings moved Zitate -1 / aufgeloest ±0 ⇒ the 0034-Stelle
  is among the unresolved. Confirmed one site: technik.md:409 is English now,
  killing the riegel's own head citation ("Zwei Adresspaare..."). Translation
  waves break citations — third occurrence; proposed 0222 (successor to 0200,
  dateien = 0200's carrier list as prior).
- Difference tables are not churn-proof either: 0166's builder replaced base
  numbers with differences because bases rot daily — the middle column rotted
  in ONE day anyway, because it depends on the one Stelle *resolving*. Any head
  number tied to corpus health inherits the corpus's volatility; the only
  stable thing is the machine re-measuring per build.
- Standing check confirmed again: quote report evidence into the befund on
  sight (file mutates daily) — did so; stream orientation checked (:4149
  stdout); missing Zahlenzeile ⇒ Messfehler/2, not silent green.
- Open: after 0222 lands, wortabstand may be green as delivered — the redo of
  0166 might need zero edits. Said so in the befund so nobody re-measures
  prematurely.

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

## 2026-09-07 — pruefung 0214 (geprueft, 0 findings)

- Byte-identity without git is provable to a useful degree: sweep the repo for every
  quotation of the file written *before* the package built (package body, earlier
  pruefungen, own archived logbook) and resolve each verbatim; then counter-probe
  that no recorded line carries a post-change wording. Bonus dating signal: ctest
  test numbers in captured output (19 → 21 → 23 across today's reports) order the
  artifacts without timestamps.
- `uebersetzung-<datum>.md` mutated three times today under one name (13.5 s/21
  tests, 18.6 s/23, 18.51 s/ok). The 0214 builder's dated in-header quote (18.27,
  `fehler`) is already unverifiable — it fits the window after 0147's
  belegstellen build, and its load-bearing half (messung green) holds in the current
  file, so no defect. But confirmed rule, third payment today: a quote of that
  report is evidence only on the day it is taken, and only if the quote itself is
  preserved. Flagged to PM in the befund; runner-side fix (per-run report names) is
  Betrieb territory, not a venture package.
- "Behauptung N → M" claims after a table insertion: verify by finding the `was`
  wording at index M (printed i+1) and checking the insertion point is below the
  unshifted cases. Cheap, exact, no run needed.

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

