---
typ: pruefung
paket: 0182-sammelstellen-sortierung-dauerhaft-gedeckt
pruefer: test-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: assertion read at source, red-and-green proven by the executed ctest entry in uebersetzung-2026-09-07.md (quoted below), messen.py attacked with six break-it scenarios -- none stays green
befunde: 0
---

# Pruefung 0182 -- verdict: geprueft, 0 findings

## The assertion (read, not trusted)

`belegstellen_riegel.cpp:4131-4154`: after **both** `sammle_dateien` calls and their
error checks, before the set-building pass, over both lists (`Bestand`, `Vorgaben`).
On violation: stderr message naming list, Platz and both paths, `return 2`.
`erste_unordnung` (:1343) hand-rolls `is_sorted_until` with `vor_in_byteordnung` and
deliberately does not call the sort it guards. Direction correct: rips iff
`vor_in_byteordnung(liste[i], liste[i-1])`.

## Red and green: executed, quoted on sight (the report mutates daily)

`befunde/uebersetzung-2026-09-07.md`, both build paths:

```
20/25 Test #20: belegstellen_sammelordnung .......   Passed    5.59 sec   (root, "out of 25")
 4/4 Test  #4: belegstellen_sammelordnung .......   Passed    5.63 sec   (standalone, "out of 4")
```

CMakeLists carries no `PASS_REGULAR_EXPRESSION|WILL_FAIL|SKIP_RETURN_CODE`, so Passed
⇔ messen.py rc 0. Traced in `messung-0182/messen.py`: rc 0 has exactly one path —
selbstprobe 0 failures, both needles hit exactly once, delivered version silent at the
assertion, mutant passes the selftest and then rips with the message, `Zuerst an Platz`,
and rc 2. There is no `return 0` that skips any of it. Green therefore IS the executed
red proof on yesterday's tree.

## Wird es rot, wenn man es kaputtmacht — six scenarios, traced in code

1. Assertion deleted or reworded → `MARKE_QUELLE` count ≠ 1 → Messfehler, rc 2.
2. Sort removed in the delivered tree → message on delivered run → rc 1 (riegel's own
   test additionally red).
3. Assertion made toothless (e.g. `erste_unordnung` always `size()`) → mutant stays
   green → rc 1, both readings named.
4. Evaluator neutered (`meldet_unordnung` constant) → selbstprobe positive or negative
   case rips → rc 2.
5. `einmal_ersetzen` weakened to prefix-replace → middle-needle case `axb`/`x` rips.
6. Mutant rips at the selftest instead of the assertion → Messfehler, rc 2.

## No-drift clauses

- ctest entries: root 24 → 25 (sequence 19→21→23→24 recorded in the pruefungen of
  2026-09-07, today 25); standalone 3 → 4. Exactly one more.
- `belegstellen_riegel` Passed 1.02/1.03 s → Rueckgabewert 0 unchanged;
  `belegstellen_wortabstand` Passed 16.80/17.13 s → the six Kopfzahlen hold;
  `belegstellen_messung` Passed 30.53/30.32 s.
- `ORDNUNGSFAELLE` still `std::array<Ordnungsfall, 8>` (:1384), matching the 8 cases
  recorded in `pruefung-0130-belegstellenriegel-berichtsreihenfolge-festnageln-2026-09-06.md`
  — no selftest case added, Selbsttestzeile numbers unmoved.
- `add_test` without `if(EXISTS)`; missing file is FATAL_ERROR (CMakeLists:180-187);
  TIMEOUT 120 < 900.

## Two disclosed interpretations, both examined and accepted

1. "Gruen" read as *the assertion stays silent*, an rc 1 of the delivered version
   printed but not judged: correctly scoped — rc 1 is the riegel's finding about the
   corpus, and judging it would recreate the 0166 misattribution. The loophole is
   closed: a delivered rc 2 **without** the message stays Messfehler.
2. Mutant staying green → rc 1 naming both readings (dead assertion vs. accidentally
   sorted filesystem): matches the abnahme's Grenze paragraph; the report shows it did
   not occur.

## Remark for the Projektmanager (no befund)

Measured runtime, to be carried into the vermerk on `fertig`: **5.59 s root / 5.63 s
standalone** (builder could only derive ~8 s — no shell at build time). Standalone
Belegstellenbau now 54.11 s, previously 49.5 s — proportionate.
