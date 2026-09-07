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

