---
typ: pruefung
paket: 0283-teil-a-misst-den-text-und-nennt-es-verhalten
pruefer: kern-pruefer
datum: 2026-09-10
urteil: geprueft
kriterium_geprueft: "Both returned sentences re-read against `uebersetzung-2026-09-07.md:281-289` verbatim, the corpus check re-derived from the code, and its silence proven by the green `belegstellen_kopfzahlen` (10,11 s) in `uebersetzung-2026-09-10.md:421`."
befunde: 2
---

Ruecklauf 1 of 3. Conditions 1, 3, 4, 5, 6 were settled by the project manager; I
re-checked that the repair did not move them. Condition 2 is the object.

## Ruecklauf finding 1 -- repaired

`messen.py:25-29` now: *„… aenderte den Arbeitsbaum, und den las im Tauschfenster
allein **Lauf B**: Lauf A lief ueber den archivierten Wortlaut aus
`VORFASSUNGSSTAND`, den keine Aenderung im Arbeitsbaum erreicht."*

Re-derived from the code, not from the sentence: `vorfassung()` (`:261-313`) takes
`alt` from `git cat-file` and caches it; `neu` is `lies(QUELLE)` (`:863`); the removed
swap wrote `alt` into QUELLE for run A (`teil_a:431` records it). A working-tree edit
therefore reached run B only. Direction correct.

## Ruecklauf finding 2 -- repaired

Followed the citation instead of weighing the sentence.
`uebersetzung-2026-09-07.md:281` = Blob `e3038e23…` aus `83faa06^`; `:285/:286` = Code 1
(36, 34, 57) gegen Code 0 (36, 36, 57); `:289` = *„Nur vorher: ['zitierend: …:32',
'… :39']. Nur nachher: []"*. `messen.py:34-44` quotes all four correctly and assigns the
2026-09-07 red to committed history (0147, 0166, 0182) -- the same cause the file
already held at `:159-164`. The two irreconcilable causes in one file are gone.

## Condition 2's *Nachweis im Lauf* -- checked, not argued

The corpus state is named where it is set: `teil_a:428-434`, a comment on the **absence**
of a write. It is verified twice at runtime, `:445` and `:894`, both through `melde`,
and `main:904-906` turns any `melde` into return 1. `belegstellen_kopfzahlen` Passed
10,11 s (`uebersetzung-2026-09-10.md:421`) -- so both checks were silent, and the corpus
really stood still across the two runs.

## Mechanism untouched

Exactly one write-mode open: `open(VORHER, "wb")` (`:307`); `bauen` writes to
`$TMPDIR/m_*` via `-o` (`:377-379`). Array sizes: `KLAMMERN` 11 (`:1635`),
`ABSTANDSFAELLE` 8 (`:3032`), `SATZFAELLE` 5 (`:3201`), `ZITATFAELLE` 13 (`:3558`).
Condition 4 stands in its second form: `belegstellen_riegel.cpp:584-591` names what the
stand holds, `pruefe_angabe1`'s `sonst` clause is in place (`messen.py:596-599`).
`TIMEOUT 300` (`CMakeLists.txt:271`) against 10,11 s. `belegstellen_wortabstand` still
red with the same 3 deviations (`uebersetzung-2026-09-10.md:403, 404, 413`) -- foreign.

**Determinism:** grep over `messen.py` for `float|unordered|random|time\.|datetime|
.keys()|.values()|hash(|id(` -- 0 hits. Both set differences are wrapped in `sorted()`
(`:465-469`). `einordnen`'s `kopfende` re-derived: 780 `^//!` lines in the riegel, the
780th at line 780 -> the head is contiguous 1-780, no stray marker below it.

## Befund 1 -- the head still claims an event it has no record of

`messen.py:22` heads the paragraph *„**Wie ein Leser damit das alte Rot erzeugt hat.**"*
and `:30-32` stays in the past tense. `:34` then says *„**Gemessen ist der Tausch, nicht
dieser Fall.**"* -- the head asserts a historical event and one paragraph later withdraws
the only evidence for it. No instance is on record anywhere I looked. The **mechanism**
I confirmed from the code, so nothing false is said about the machine; the tense claims
history. The Ruecklauf expressly allowed *„die Richtung richtigstellen und den Beleg
fallen lassen"*, which is what happened -- so this does not fail condition 2. A
subjunctive fixes it; that is below a package number.

## Befund 2 -- the inference at `:38-41` is not airtight, and it is mine

`:38-41` argues: both places stood under *„Nur vorher"*, hence in the archived text,
hence no uncommitted change caused them. That does not follow. An uncommitted
**correction** in the working tree removes the finding on the B side and leaves it on the
A side -- which is a *„Nur vorher"* entry, exactly the signature `:22-32` describes two
paragraphs above. Both causes produce the same output shape; only git history separates
them, and no role has a shell. The wording is transcribed from my own 0278/0283 review
and I had it wrong. The conclusion is not affected: the cause it names was already the
file's standing account at `:159-164` (0189-era text, outside this package). **Do not
lean on this inference** -- cite `:159-164` instead.
