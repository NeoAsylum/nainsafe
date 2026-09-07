---
typ: pruefung
paket: 0147-belegstellenriegel-ortsfrage-mit-anker
pruefer: test-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: belegstellen_messung Passed (rc 0) in both builds of the delivery-day nightly report, all nine needles re-verified character-wise against today's HEAD, and no ctest property weakens what Passed means
befunde: 0
---

# Geprueft: the measurement ran and returned 0

## The decisive evidence, quoted because the report is overwritten daily

`befunde/uebersetzung-2026-09-07.md` (delivery-day nightly, `ergebnis: ok`):

    18/23 Test #18: belegstellen_messung ....... Passed 30.72 sec   (workspace)
     2/2  Test  #2: belegstellen_messung ....... Passed 30.73 sec   (standalone)
    17/23 Test #17: belegstellen_riegel ........ Passed  1.03 sec
     1/2  Test  #1: belegstellen_riegel ........ Passed  1.03 sec

"Passed" means exit 0 and nothing weaker: `werkzeuge/belegstellen/CMakeLists.txt:100-115`
sets no `PASS_REGULAR_EXPRESSION`, `SKIP_RETURN_CODE` or `WILL_FAIL`, so rc 1 (Befund)
and rc 2 (nicht gemessen) would both show Failed. Return 0 per `messung.py:651-655`
requires everything the abnahme names: each of the nine mutants rc 2 with exactly one
ripped case, the right case by name, no foreign table, Bestand unread (Teil 2,
messung.py:583-596); vorher and nachher both green on today's corpus with GLEICH in
Rueckgabewert, Zahlenzeile, Befundteil and Fehlerkanal (Teil 1, :557-567). The riegel
itself green in both builds means the corpus clause added by the PM is not needed —
the original criterion holds directly, and there are no foreign citations to name.

## The report speaks about today's tree

Re-counted all nine needles character-wise against HEAD: M1 `belegstellen_riegel.cpp:2297-2299`,
M2 `:2300-2302`, M3 `:2303-2304`, M4 `:2308` (the only
`return Ortsurteil{Ortsausgang::Nachschlagen` in the file), M5 `:2316`; `WAHL_ALT`
reproduces the `waehle_zitatform` body `:2751-2772` verbatim, including the single
space before `wahl.roh` at `:2764`. Each hits exactly once.

## Wird es rot? Executed, not argued

Same-day red-to-green on the real corpus: the previous nightly (quoted in
`pruefung-0147-...-2026-09-07-2.md`) had this exact test `***Failed` in both builds with
"ROT Selbstprobe: einmal_ersetzen ... yxb, erwartet war ayb" while `messung.py:233` held
the wrong constant. The one-line fix — needle now `"x"`, `messung.py:240`; arithmetic:
`"axb".replace("x","y") == "ayb"` — flipped it green. The apparatus demonstrably fails
when its subject is broken.

## Weakening checked, none found

- Mutant expectations unchanged: `erwartet_rc` 2 for all nine, one expected case each,
  `eigen` table pinned, `Bestand gelesen` expected False. No threshold lowered.
- Stream orientation is real, not degenerate — the one thing a green run cannot prove
  about itself: the self-test closing line goes to **stderr** before `return 2`
  (`:3974-3984`), the Zahlenzeile to **stdout** only after the Bestand loop
  (`:4116-4129`). So `las_bestand = ZAHLENMARKE in aus` genuinely separates "died at
  self-test" from "read the Bestand", and Teil 1 compares a line that exists.
- CMake: `FATAL_ERROR` instead of silent `if(EXISTS)` (`:75-81`); missing Python turns
  the test red instead of dropping it (`:83-94`); TIMEOUT 600 under the runner's 900.
- The `.cpp` is untouched by this rework; the only content change since the last review
  is the one constant plus its justifying comment (`messung.py:233-240`).

Residual, no action: the CMake comment invites replacing TIMEOUT 600 with a multiple of
the first measured time; measured today 30.7 s, so 600 already is one (~20x).
