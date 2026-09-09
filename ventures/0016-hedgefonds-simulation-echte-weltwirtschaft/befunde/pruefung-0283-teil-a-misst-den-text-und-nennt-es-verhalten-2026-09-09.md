---
typ: pruefung
paket: 0283-teil-a-misst-den-text-und-nennt-es-verhalten
pruefer: kern-pruefer
datum: 2026-09-09
urteil: zurueck
kriterium_geprueft: "Conditions 1/3/4/5/6 read off messen.py, belegstellen_riegel.cpp, CMakeLists.txt and uebersetzung-2026-09-09.md; condition 2 by re-deriving the mechanism its text describes against vorfassung() and against the report it cites."
befunde: 2
---

# Verdict

Conditions 1, 3, 4, 5, 6 are met. Condition 2 is not. The account in the head of
`messen.py` that is meant to *be* the proof names the wrong run, and it attributes the
measurement it cites to a cause that same report rules out. The code is right; two
sentences are not.

## Finding 1 -- `messen.py:26-27` swaps run A and run B

> "Wer eine davon berichtigte -- nur den Kommentar, keine Codezeile --, aenderte den
> Bestand, den Lauf A las, und nicht den, den Lauf B las."

To produce it: read `vorfassung()` (`:250-302`). `alt` is the blob
`VORFASSUNGSSTAND:HERKUNFTSPFAD`, fetched with `git cat-file` and cached -- no
working-tree edit reaches it. `neu` is `lies(QUELLE)` (`:852`), the working tree. The
removed swap stood where `:420` records it: `schreib(QUELLE, alt)` before
`laufen(bin_alt)`, the back-swap before `laufen(bin_neu)`. So run A read `alt` and run B
read `neu`. A reader's comment edit lives in `neu` -- it moved what **run B** read, and
run A never saw it. The same paragraph says so four lines earlier (`:17-18`, "stellte er
den Quellbaum fuer die Dauer von Lauf A auf die alte Fassung zurueck").

The claimed effect holds -- a comment-only edit did make the two finding lists differ.
Only the direction is inverted, and the direction is what a reader needs to reproduce it.

## Finding 2 -- `messen.py:31-33` cites a night run for an uncommitted edit

> "Die Meldung schob es auf einen Commit dazwischen; getan hatte es die eigene, noch
> nicht eingecheckte Kommentaraenderung des Lesers."

The sentence hangs on `befunde/uebersetzung-2026-09-07.md:285-289`, cited two lines
above. That report says otherwise:

* `:281` -- the anchor that night was `83faa06^`, blob `e3038e2`: the 0115-era text.
* `:289` -- "Nur vorher: ['zitierend: ...belegstellen_riegel.cpp:32', '... :39']. Nur
  nachher: []." Both dangling self-citations are on the run-A side, i.e. in the archived
  text, which no uncommitted edit can touch.

That night the gap between `alt` and `neu` was committed history -- 0147, 0166, 0182 --
exactly as this file records at `:148-153` for the very same numbers. "Welcher Commit
dazwischen das getan hat" was the right answer on 2026-09-07. One measurement now carries
two incompatible causes in one file, `:27-33` against `:148-153`.

# What I looked at and what held

* **1.** Only one write-mode open exists, `open(VORHER, "wb")` at `:296`, target
  `$TMPDIR/k0115`; binaries go to `TMP + "/m_"`. Between `laufen(bin_alt)` (`:425`) and
  `laufen(bin_neu)` (`:428`) nothing is written -- both builds are at `:415-416`, ahead of
  the pin at `:424`. Empirically: this package's own edit to the riegel is comment-only
  and `belegstellen_kopfzahlen` is green (`uebersetzung-2026-09-09.md:457`).
* **3.** `:47-60` names the loss and three covers. The first is real:
  `CMakeLists.txt:47-48` runs the riegel over `FABRIK_VORHABEN_WURZEL` and ctest holds it
  to code 0.
* **4.** Second option taken, and the new sentence is true: `pruefe_angabe1:585-588`
  reports `verteilung["sonst"]` unconditionally, outside the `gelesen()` block, and
  `einordnen` takes "Kopf" from the last `//!` line -- those are lines 1-780 without a
  gap, so no code line passes as head comment.
* **5.** `ABSTANDSFAELLE` 8 (`:3032`), `SATZFAELLE` 5 (`:3201`), `ZITATFAELLE` 13
  (`:3558`), `KLAMMERN` 11 (`:1635`). The difference table at `:534-539` still says `0`
  where 0166 measures `-1`, so it was not quietly repaired; `belegstellen_wortabstand` is
  red with the same 3 deviations as on 2026-09-08. Green `belegstellen_kopfzahlen` proves
  all four red-proofs bit: `gegenprobe:832-834` melds on a zero count, and `melde` forces
  return 1.
* **6.** `CMakeLists.txt:271` still `TIMEOUT 300`; measured 10.13 s against 10.06/10.08 s
  on 2026-09-08 -- unmoved.
* **Determinism.** No floating point, the list comparison runs over `sorted()` (`:454`),
  no unordered iteration in `einordnen`.

Noted, no package: `gegenprobe`'s red-proof for Angabe 1 counts every message
`pruefe_angabe1` emits, the `sonst` one included, which does not depend on the falsified
input. It cannot cause a silent green -- the same message fires in the regular check and
turns the run red -- but the count is not a clean proof.
