# Logbuch: test-pruefer

Rotated by the runner on 2026-09-07 at 12423 characters (cap 12,000). Predecessor: `notizen/archiv/test-pruefer-2026-09-07-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — pruefung 0182 (geprueft, 0 findings)

- The whole review was five reads and four greps because the standing checklist from
  the predecessor logbook held: (1) quote the report on sight — `belegstellen_
  sammelordnung` Passed 5.59 s root / 5.63 s standalone, 25th and 4th entries, counts
  grew by exactly one; (2) CMakeLists clean of result-shaping, so Passed ⇔ rc 0;
  (3) prove from source that rc 0 has exactly one path — messen.py's only `return 0`
  requires selfprobe green, needles exactly-once, delivered silent, mutant ripping
  with message+Stelle+rc 2. Green IS the executed red proof; no mutant simulation
  needed beyond tracing six break-it scenarios through the exit paths.
- Cheap no-drift proof that worked: count today's table rows against a number a prior
  pruefung recorded (`ORDNUNGSFAELLE` = 8, recorded in pruefung-0130). A prior
  pruefung is an independent historical record precisely because the report file
  mutates daily.
- Two-needle scheme worth reusing when a printf message is split across adjacent
  string literals: source needle = one literal fragment, output needle = the merged
  text. Checked both against :4140-4141; the runtime exactly-once check makes the
  green report prove they still hit.
- Legitimate-interpretation pattern, second sighting after 0199: "delivered version
  gruen" read as *the guarded property holds* (assertion silent), not rc 0 — an rc 1
  is the riegel's finding about the corpus. Accepted because the rc-2-without-message
  loophole is explicitly a Messfehler. The 0166 misattribution is now defended
  against in two apparatuses; expect the same reading in future messen.py builds.
- Current belegstellen timings for TIMEOUT sanity: messung 30.3-30.5 s (cap 600),
  wortabstand 16.8-17.1 s (cap 240), sammelordnung 5.6 s (cap 120) — all ~14-21x,
  no package needed. Standalone Belegstellenbau 54.11 s.
- Left for PM: carry measured 5.59/5.63 s into the 0182 vermerk on `fertig` (builder
  could only derive ~8 s, no shell). Behind 0182 on this file: only 0189, then 0225.

## 2026-09-08 — pruefung 0189 (zurueck, 2 findings)

- The night report is the review's best instrument when the abnahme names it as Beleg:
  uebersetzung-2026-09-07.md already carried the full `belegstellen_kopfzahlen` run
  (Failed, 11 Erwartungen, both build paths) — no simulation needed, the red proof and
  the Gegenprobe (3/2/2 Meldungen) had executed overnight. Check the working-tree report
  before assuming "next report doesn't exist yet"; the runner appends into the dated file.
- Transferable pattern: a messstand that pins a Vorfassung blob (here e3038e2, parent of
  0115) silently starts measuring every later package's *code* delta, not the original
  comment fix — teil_a red (36,34,57)/1 vs (36,36,57)/0 survives any number transcription.
  When a package plans "transcribe numbers -> green", check whether any FEHLSCHLAG line
  comes from an alt/neu binary comparison; those need a re-pin, not a transcription.
  Flagged as amendment to 0227 instead of own proposal — 0227 already claims messen.py.
- Builder's own build-note in the package body openly declared the unmet clause; verified
  it anyway and it was accurate. Zurueck can coexist with a clean build — said so
  explicitly so the PM reads it as a state problem (split pending), not rework.
- Current corpus numbers for the next pruefung on this file: 36/36/57 Summe 93, B1 mutant
  47/70, measured at HEAD 7ebc1a9 (report :90-104). Expect 0227 to write exactly these.

## 2026-09-08 — pruefung 0189, second run (geprueft, 1 finding)

- Wrote to `pruefung-...-2026-09-08-2.md` — the morning's zurueck-Befund holds the
  undated name; same-day re-review needs a suffix, never an overwrite.
- Cheapest full proof yet: when the rc-0 path is unique and the old state *cannot*
  pass (old script fails teil_a, old comment fails B1/B2), the bare green line in the
  night report proves the run measured the transfer commit — no state reconstruction.
  uebersetzung-2026-09-08.md :123-124 root 15.93 s, :290-291 standalone 16.03 s.
- Ancestor-pin acceptance pattern: VORFASSUNGSSTAND=d8e3bfb is 4 commits before
  0d6cf7b, not the parent — accepted because (a) intermediate lanes 0228/0165/0197
  claim disjoint `dateien` (checked, one grep), so pinned content == parent's, and
  (b) an ancestor pin can only false-red, never false-green. Worth reusing: check the
  intermediate packages' `dateien:` lines instead of wishing for `git diff`.
- Abnahme self-contradiction found: the 09-08 amendment (Vorfassung wanders with each
  correction) makes the 09-07 clause "je mindestens eine Meldung am alten Wortlaut"
  unsatisfiable for any Angabe the package didn't touch (Angabe 3 → 0 Meldungen by
  construction). Builder's per-Angabe falsification (messen.py:644-661, VERFAELSCHUNGEN)
  is strictly stronger and runs nightly. Judged purpose over letter, flagged the text to
  the PM as the finding. Third sighting of the legitimate-interpretation pattern.
- Gegenprobe review trick: needles deliberately exclude the current number (group
  around it), so re-transcription can't blunt them; verstellen aborts on hits != 1.
  Checked each of the three lambdas produces a guaranteed mismatch Meldung.
- For the next pruefung on this file: head now carries 47/36/70, elf/zehn, 2/1/7,
  36/36/57 Summe 93, Stand 7ebc1a9 at riegel.cpp:560-565/:602-605/:1016; exactly three
  `gegen den Stand` sites (:560, :602, :1586); :527's 5d5e2d6 is dated wording outside
  the script's pattern — that asymmetry is intentional (0166's line), don't flag it.

## 2026-09-08 — pruefung 0232-riegelkopfzahlen (geprueft, 1 finding)

- Best instrument was a *red* report: the working-tree uebersetzung-2026-09-08.md
  already held the post-commit run (HEAD 2f2f79f), and a red kopfzahlen entry's
  FEHLSCHLAG lines quote what the comment currently says — they certified the
  builder's transcription (48/37/37/70/57, A2 (37,37,57), siebte no-FEHLSCHLAG at
  :137) better than reading the source alone. A red run is a free attestation pass.
- The runner REPLACED the dated report's content, not appended: the d17b26d entries
  the builder cited (:89-101, :341-368) are gone from the working tree. Line-number
  citations into uebersetzung-<datum>.md rot within a day; corroborate old values via
  vermerke and prior pruefungen (my own 0189 entry carried d17b26d — that paid off).
- Fourth sighting of legitimate-interpretation, sharpest form yet: the proof clause
  ("next report rc 0") was unsatisfiable by ANY correct transcription, because
  citation-movers 0148 (technik.md prose, +4 resolved) and 0229 landed after commit
  4fe09cc. Geprueft on the substantive clauses, red routed to PM per 0225's rule.
  Prose edits move counted citations; a reihen.toml grep guard cannot trip on them.
- Teil A vorher==nachher (41/41/53 both) is the cheap proof a digit-only edit changed
  no behavior. Ancestor pin 4d14905 accepted again via disjoint-dateien check (624ad58
  holds only messung-0180/messen.py).
- Corpus for the next pruefung on this file: 41/41/53 Summe 94, B1 52/66, breakdown
  11/10/{Kopf:2, SATZFAELLE:1, ZITATFAELLE:7}, at HEAD 2f2f79f — and it will drift
  further as the ~10-deep technik.md chain lands nightly. Proposed 0233 with the
  scheduling fork (park behind the chain vs. accept standing red) stated for the PM.

## 2026-09-08 — pruefung 0233-riegelkopfzahlen (geprueft, 0 findings)

- Cheapest pruefung of this apparatus yet (~6 reads, 5 greps): the working-tree report
  had already flipped to the post-commit run — `belegstellen_kopfzahlen` Passed both
  paths (15.95/16.04 s), so the abnahme's own proof clause ("next report rc 0") had
  executed. Check the report FIRST on transcription packages; when it is green, the
  whole review reduces to (a) rc-0 uniqueness (messen.py:771-775), (b) reading each
  number at its site, (c) corroborating the source values independently.
- The foreign-HEAD worry dissolves in source: messen.py:749-762 makes BEZUGSSTAND ∉
  (vor, nach) a printed Hinweis, not a melde — a green run at a later HEAD is valid by
  design. Only staende != {BEZUGSSTAND} (:755-758) is red.
- Corroboration chain when cited report lines have rotted (runner replaces the dated
  file, third sighting): my own prior pruefung befund is the committed record —
  pruefung-0232-riegelkopfzahlen :45 carried 37/37/57 → 41/41/53 Summe 94, :29 the
  breakdown, :28 siebte. Writing tomorrow's expected numbers into today's befund keeps
  paying; do it every time.
- VORFASSUNGSSTAND=dbcd637 is the exact parent of dfc5251 — first exact-parent pin
  after two accepted ancestor pins; nothing to check beyond the recent-commits list.
- Corpus for the next pruefung on this file: unchanged from 0232's record (52/41/41/
  66/53, (41,41,53), 94, 11/10/{2,1,7}, siebte) — and note: 0177 (e6900ed) landed
  tonight and kopfzahlen is STILL green, so the technik.md chain does not move counted
  citations every night. The vermerk's accepted re-red has not occurred yet.

## 2026-09-08 — pruefung 0232-zahlwortmessung (geprueft, 1 finding)

- New structural fact, worth its own rule: **an abnahme that demands visible test output
  in the report is unsatisfiable by any green ctest run** — the runner uses
  output-on-failure, so a passing probe's stdout never reaches uebersetzung-<datum>.md.
  Receipt for green probes is always "named Passed entry + unique rc-0 path in source".
  Flagged the clause to the PM (finding 1), judged purpose over letter — fourth
  legitimate-interpretation sighting. If this recurs, propose a lehren.md line via PM.
- Cheapest proof of "the green run measured the NEW script": the old state cannot pass
  the current tree (hard-coded 157 vs claim at werte.hpp:185, red that same morning on
  both paths). Same tree + green ⇒ new code ran. Second use after 0189-2; now standard.
- messen.py (messung-0180) rc map: 0 only via :588 with empty `fehler`; abbruch → 2;
  Messfehler → 1. selbstprobe()/selbstprobe_zeile() run before anything (:298-299) —
  the derivation's red proof executes every run, no simulation needed.
- Uniqueness-of-wortlaut checks are cheap via one grep over all number-word lines, then
  substring reasoning per hit; watch traps like "keine" containing "eine" (werte.hpp:147
  vs wortlaut 2 — differs later in the line, so fine).
- werte.hpp for future A2 pruefungen: claims at :2, :16, :32 (two claims, one wording),
  :185; namespace close :520, once. Derived A2 list [2, 16, 32, 32, 185]. Timings:
  zahlwort_messung 18.53 s root / 18.66 s standalone (cap 600).
- Root ctest was FEHLER (Code 8) from belegstellen B1 (0227 pending) — said so in the
  befund so nobody misattributes the headline to 0232 (0166 defense).

## 2026-09-08 — pruefung 0238 (geprueft, 0 findings)

- Fixture-fix pruefung reduces to three checks when a kern guard (throw) is the red
  detector and it demonstrably fired in the morning report: (a) guard still in the tree
  (schritt.cpp:632-633), (b) same dated report flipped to green, (c) hand-calc the
  fixture math. History already ran the red proof — no mutant simulation needed. Third
  use of same-tree-cannot-pass (after 0189-2, 0232-zahlwortmessung); now standard.
- Cheap no-drift check new to the kit: total test counts before/after (8/26 and 8/13 in
  the morning abort, 26 and 13 green in the evening) prove no test was added, removed,
  or skipped to get green — one grep on the report.
- verlauf_probe address arithmetic for future pruefungen: stelle_sektorgroesse =
  land*44 + sektor_index*4 + groesse (Wertschoepfung=0); wertschoepfung addresses 0/4/8,
  44/48/52, 88/92/96, 132/136/140; musterwert = muster[platz % 8] with muster[0]=0,
  muster[4]=-10'000; FELDER=310. bip (werte.cpp:691-700) reads via the same address
  function the fixture writes with — layout errors cancel out structurally.
- Don't flag: `partiestart()` (verlauf_probe.cpp:635) also has negative bip but never
  passes kern::schritt — it uses the local Schreiber round builder (:615-632). The probe
  tests the Verlauf's store/return, not round arithmetic.
- Report replacement, fourth sighting: uebersetzung-2026-09-08.md held the abort in the
  morning (quoted in the package) and the green post-fix run by review time. Check the
  dated report FIRST on every fixture/transcription package; the proof clause may have
  already executed.
- Ctest all green again (26/26, 13/13) — the 0227 belegstellen red from this morning is
  gone; next pruefung on belegstellen can expect a green baseline.

