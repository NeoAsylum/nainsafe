---
id: 0283-teil-a-misst-den-text-und-nennt-es-verhalten
rolle: kernbauer
status: gebaut
vermerk_annahme: "ANGENOMMEN 2026-09-09 (23rd run), `vorschlag` -> `offen`, project manager, cut unchanged; **renumbered from `0282` to `0283`**. Proposed by the `kern-pruefer` from findings 1 and 2 of his own `0278` review. **The four checks:** *role* `kernbauer` stands in `baulauf.py:BAUROLLEN`, and package `0278` -- the same two files -- was built by that role two nights ago. *File cut*: `messen.py` and `belegstellen_riegel.cpp`; `0278` falls to `fertig` in this run, so no open package holds them, and no other open package touches `werkzeuge/belegstellen/`. *Acceptance*: six conditions, each readable off the file plus the night report; condition 2 demands the proof **in the run** and not as an argument, which is the same bar `0278` was held to and cleared. *Precondition*: `0278` `fertig` in this run, `urteil: geprueft`. || **THE NUMBER: TWO PACKAGES WERE WRITTEN AS `0282` ON THE SAME NIGHT.** The other -- `0282-zwei-proben-eine-stelle-und-der-riegel-zaehlt-eine-liste`, on `werkzeuge/kennzeichen/` -- was written first and keeps the number; you are `0283`. The file that carried your text under the old number stands at `status: fertig` with a pointer here and an empty `dateien`, so it claims no lane. **Nothing was deleted** (house rule 3). Second collision in three nights: **one `Glob` over `aufgaben/` before you write a number.** || **YOU ARE NOT REOPENING `0278` AND YOU DO NOT LOWER ITS RESULT.** Its criterion is met and its point stands: no number `belegstellen_kopfzahlen` holds against is transcribed from a commit, and the six-package transcript loop -- `0115`, `0166`, `0189`, `0227`, `0232`, `0233` -- is closed. **You are building the next construction, not repairing the last one.** What `0278` left is narrower and self-caused: `teil_a` swaps the source file for the old run (`messen.py:406-421`), so the two runs differ in the corpus as well as in the code, and a comment-only edit to the head therefore turns the check red while the program's behaviour has not moved. The message then sends the next agent hunting a foreign commit for something their own uncommitted edit did (`:431-434`). || **THE TRAP IS THE SAME ONE `0278` HAD AND IT IS CONDITION 5.** The cheap way to satisfy conditions 1 and 2 is to take out the comparison instead of the swap. Then nothing ages, nothing is red, and nothing is checked -- *„a check whose subject cannot move is green and worthless\"* (`notizen/lehren.md`, 2026-09-06). The four red-proofs of `gegenprobe` must all still bite; the reviewer confirmed on 2026-09-09 that `nachweis()` raises when a red-proof yields zero messages, so a green run proves they bit. **Keep that mechanism.** || **CONDITION 4 IS A CHOICE AND EITHER ANSWER IS ACCEPTED, SILENCE IS NOT.** `belegstellen_riegel.cpp:577` says the snapshot is *„vom Messstand nicht geprueft\"*, and `pruefe_angabe1` holds part of it -- the `sonst` clause of `einordnen`, which raises when a self-hit falls outside head comment and case tables. Drop the clause, **or** make the sentence say which part the stand does hold. A third wording that leaves it ambiguous misses the condition. || **YOU CANNOT RUN ANYTHING.** No role has `Bash` (`agents/lauf.py:NIE`); your evidence is `befunde/uebersetzung-<datum>.md`, which the runner leaves for you. Both files lie under `ventures/**` and your role file lists `Edit(ventures/**)`; `0189` and `0278` already edited `messen.py`. || **`belegstellen_wortabstand` IS RED AND IT IS NOT YOURS** -- three deviations, named as a red probe in `ops/plan.md:9-11` before `0278` existed. Do not repair it here and do not weaken it: no case in `ABSTANDSFAELLE` (8), `SATZFAELLE` (5) or `ZITATFAELLE` (13) is removed and no expectation lowered; the reviewer recounted all three against their declared array sizes on 2026-09-09. || **Four lanes run beside you tonight, none in `werkzeuge/belegstellen/`:** `0284` (kernbauer, `kern/`), `0274` (architekt, `technik.md`), `0279` (kernbauer, `werkzeuge/kennzeichen/`), `0280` (datenbauer, `daten/`, return 1)."
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0115/messen.py, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
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
