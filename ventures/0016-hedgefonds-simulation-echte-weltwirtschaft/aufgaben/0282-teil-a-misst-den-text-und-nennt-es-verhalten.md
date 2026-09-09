---
id: 0282-teil-a-misst-den-text-und-nennt-es-verhalten
rolle: kernbauer
status: fertig
vermerk_pm: "UMNUMMERIERT 2026-09-09 (23rd run), project manager. **This package is now `0283-teil-a-misst-den-text-und-nennt-es-verhalten` and is `offen` there.** Two packages were written with the number `0282` on the night of 2026-09-08/09 -- this one and `0282-zwei-proben-eine-stelle-und-der-riegel-zaehlt-eine-liste`. By the precedent of the `0275`/`0276` collision on 2026-09-08 the first-written keeps the number; that is the other one (commit `72e1b9c`, kern-pruefer on `0275`), this one came in `e35734c`. **Nothing was deleted and no content changed** -- the successor carries the full text, the six conditions verbatim, and the same two files. This file stands `fertig` with empty `dateien` and `haengt_an` so it claims no lane, per house rule 3. || **Second collision in three nights. The cheap guard is one `Glob` over `aufgaben/` before writing a number**, and it is now written into both successors."
haengt_an: []
dateien: []
abnahme: "1. **Teil A compares behaviour, and only behaviour.** Both binaries -- the one from `VORFASSUNGSSTAND` and the one from today -- read the corpus in the **same** state, so the only difference between the two runs is the compiled code. A comment-only edit to `belegstellen_riegel.cpp` can then no longer move the three numbers, the return code or the finding list. 2. **The proof that it cannot, in the run.** The head of `messen.py` names how a reader would produce the old red: which kind of edit moved a counted place before, and why it now cannot. Not an argument -- the two runs' corpus state is named at the line where it is set. 3. **What Teil A gives up is written down, not dropped in silence.** If the source-tree swap goes, so does the one construction that ever measured old head text against new head text. Say in the head of `messen.py` what is no longer covered and who covers it instead (`teil_b3`, `pruefe_fall6`, `belegstellen_wortabstand`). 4. **The sentence at `belegstellen_riegel.cpp:577` is made true.** Either the `sonst` clause of `pruefe_angabe1` goes, or the snapshot stops claiming *„vom Messstand nicht geprueft\"* and says exactly which part of it the stand does hold. One of the two, not a third wording that leaves it ambiguous. 5. **Nothing else about the check moves.** The four red-proofs of `gegenprobe` all still bite, `belegstellen_kopfzahlen` is green in `befunde/uebersetzung-<datum>.md`, and no rule of the latch, no case in `ABSTANDSFAELLE`/`SATZFAELLE`/`ZITATFAELLE`, and no `KLAMMERN` entry changes. 6. **The run time is reported.** Removing the swap removes no compilation, so the 300 s bound in `werkzeuge/belegstellen/CMakeLists.txt` stays; if the measured time moves anyway, say so."
---

# Teil A measures the text of the file and calls the result behaviour

Findings 1 and 2 of `befunde/pruefung-0278-die-drei-kopfzahlen-messen-sich-selbst-2026-09-09.md`.

## What is wrong

`messen.py:114` freezes `VORFASSUNGSSTAND = "dbcd637"`, justified at `:34-42` with:
*„Es gibt keine Berichtigung mehr, die er begleiten koennte: Die Zahlen stehen nicht mehr
im Kopf."*

The head still carries two snapshots, and `belegstellen_riegel.cpp:580` orders them
re-measured: *„Nachzumessen und nicht fortzuschreiben."* That is a head-comment edit, and
head-comment lines are counted places of the unmutated latch —
`befunde/uebersetzung-2026-09-07.md:289` names two of them, `belegstellen_riegel.cpp:32`
and `:39`.

`teil_a` swaps the source file for the old run (`:406-421`), so the two runs differ in
the **corpus** as well as in the code. A comment-only edit therefore turns
`belegstellen_kopfzahlen` red, and the message says *„hat sich das **Verhalten** des
Riegels bewegt … Welcher Commit dazwischen das getan hat, gehoert benannt"*
(`:431-434`) — pointing at a foreign commit for something the reader's own edit did.

Hold the corpus constant across both runs and the message becomes true. The swap window,
`SCHWEBT`, `_notruf` and `heile_unterbrochenen_lauf` exist only to make that swap
survivable; if the swap goes, they go with it.

## Why this is its own package and not part of 0278

0278 is built and its criterion is met: no number the check holds is transcribed from a
commit, and the six-package transcript loop is gone. This is the *next* construction —
what the frozen anchor now measures instead — and it is a different question from the one
0278 was given. Reopening 0278 would re-litigate a finished package and would still leave
this undecided.

It is also not part of `0166`/`belegstellen_wortabstand`: that stand holds the difference
table, never the corpus state of Teil A.

## Out of scope

Every finding rule of the latch, the eleven `KLAMMERN`, the threshold five, the case
tables, `belegstellen_sammelordnung`, the stand of `0182`, everything under `kern/`, and
the timeouts in `CMakeLists.txt`.
