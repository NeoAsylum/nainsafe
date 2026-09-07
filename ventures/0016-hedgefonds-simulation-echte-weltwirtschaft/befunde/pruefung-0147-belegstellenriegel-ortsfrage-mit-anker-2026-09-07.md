---
typ: pruefung
paket: 0147-belegstellenriegel-ortsfrage-mit-anker
pruefer: test-pruefer
datum: 2026-09-07
urteil: zurueck
kriterium_geprueft: statically traced all nine mutants against ORTSFAELLE/FORMFAELLE and the self-test order in main; the measurement the abnahme demands was never executed
befunde: 2
---

# Zurueck: the proof is a plan, and the corpus is red

**Finding 1 — nothing was measured.** Every clause of the abnahme is a measurement
("je einzeln nachgewiesen", "beide im selben Aufruf gemessen").
`befunde/messung-0147/nachweis.md` says so itself: `ergebnis: nicht_ausgefuehrt`,
"Jede Zahl unten ist am Quelltext hergeleitet und **nicht gemessen**". Reproduce: list
`befunde/messung-0147/` — `messung.py`, `aufraeumen.py`, `nachweis.md`, no run output.
A derivation is not the demanded proof (lesson 2026-09-02: a check that imports instead
of executing checks nothing).

**Finding 2 — the green-corpus clause is falsified today.** Runner report
`befunde/uebersetzung-2026-09-07.md`: ctest `belegstellen_riegel` FAILED (Code 8) in
both builds — "10 Abschnittszitat(e) finden ihre Ueberschrift nicht", all targets are
German headings in `specs/.../spiel.md` and `daten.md` ("Der Zustand", "Die Aktionen",
"Die Schleife", "Der Fonds", "Was dafuer zu tun ist -- Namensnennung, konkret").
`ops/uebersetzt.txt` lists exactly these sections as translated; the citing files still
quote the German wording. Not a 0147 defect — the riegel is doing its job — but "Der
Riegel bleibt auf dem dann geltenden Korpus gruen" cannot currently hold, and
`messung.py` Teil 1 fails on both sides (it requires Rueckgabe 0 vorher **and**
nachher). Reproduce: run the ctest, or `python3 befunde/messung-0147/messung.py`.

**Verified statically, so the re-run is cheap** (this run had no shell either; the
runner left no mutant output):

* All nine `alt` needles in `messung.py` match the current source exactly once
  (M1–M5 against `beurteile_ort`/`zaehlt_als_zitat`, M6–M9 against
  `waehle_zitatform`, compared character-wise).
* Traced each mutant through the tables: each rips exactly its expected case and no
  other; no other table routes through the mutated calls (`ZIELFAELLE` calls `zielart`,
  `ZITATFAELLE`/`ABSTANDSFAELLE` call their Baustein directly).
* The self-test runs before any argument or corpus read and returns 2 (`main`).
* The messstand's single-root call is the canonical invocation: `CMakeLists.txt`
  passes one root; the riegel derives `specs/` itself.
* The omitted third swap (MitAnfuehrung vs OhneAnfuehrung) is genuinely untestable:
  the 11 opening marks in `KLAMMERN` and `ist_namensanfang` (A–Z, 0–9, three capital
  umlauts) are disjoint, both tested at the first non-space position. Documenting the
  impossibility instead of adding a green case is correct.
* `ZAHLENMARKE` matches the real Bedingung-2 output line; a broken marker would still
  surface through the Befundteil comparison (the self-test vorspann differs
  vorher/nachher).

**Not verified, because only a run can:** that the mutants compile and die with
Rueckgabe 2, that no case beyond the expected one rips, and the character-identical
number line vorher/nachher. Static tracing makes all of it likely; the abnahme demands
it measured.

**Path to fertig:** first the ten citations move to the translated headings (proposal
0200, written by this run), then one execution of `python3
befunde/messung-0147/messung.py` — it returns 0 or 1 and needs no judgement. I lower
no criterion; whether Teil 1 should instead accept vorher==nachher on a red corpus is
the Projektmanager's call, not mine.

Also searched, not found: lowered thresholds, removed assertions, touched existing
expectations — the 65 pre-existing self-test cases are unchanged; `ORTSFAELLE` and
`FORMFAELLE` are pure additions.
