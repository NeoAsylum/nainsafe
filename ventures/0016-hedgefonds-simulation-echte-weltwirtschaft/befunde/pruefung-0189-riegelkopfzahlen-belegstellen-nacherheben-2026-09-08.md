---
typ: pruefung
paket: 0189-riegelkopfzahlen-belegstellen-nacherheben
pruefer: test-pruefer
datum: 2026-09-08
urteil: zurueck
kriterium_geprueft: Every clause of the 2026-09-07 abnahme held against CMakeLists.txt, messen.py, belegstellen_riegel.cpp and the executed night-run entry in befunde/uebersetzung-2026-09-07.md
befunde: 2
---

# 0189: hook-in is real and red-proven; the numbers are missing, and 0227 as proposed cannot turn the entry green

## Fulfilled, and how checked

- `add_test` `belegstellen_kopfzahlen`: CMakeLists.txt:239-242, no `if(EXISTS)` around it, missing file breaks configure with FATAL_ERROR (:230-237), TIMEOUT 300 < 900 (:258). Measured 15.51 s on both build paths — ample.
- No `$TMPDIR` precondition, proven by execution: the night run prints "Vorfassung: gefehlt und ist geholt worden -- Blob e3038e2..." (uebersetzung-2026-09-07.md:86 root, :281 Alleinbau). The script fetches the pinned blob itself and verifies it by self-computed SHA-1 (messen.py:168-239); cleanup in aufraeumen() (messen.py:691).
- Red proof driven, not asserted: mutants are inline replacements with exactly-once needle counting (messen.py:262-294); both needles hit once today (riegel.cpp:2554, :2011). B2 scharf ripped live, Code 2, exactly the wording the comment cites (report :105-106). Gegenprobe at the old wording: Angabe 1: 3, Angabe 2: 2, Angabe 3: 2 Meldungen, each >= 1 (report :121).

## Befund 1 — two abnahme clauses unmet (the zurueck)

- "Der Kopfkommentar ... nennt die nacherhobenen Zahlen": riegel.cpp untouched; :560-565 and :602-605 still carry the 2026-09-06 numbers "gegen den Stand `5d5e2d6`"; BEZUGSSTAND = "5d5e2d6" (messen.py:80). Measured last night: 36/36/57, Summe 93; B1 mutant 47 Zitate / 70 uebergangen (report :90-104).
- "laeuft im Nachtlauf mit Rueckgabe 0 durch": the named entry exists and is ***Failed***, 11 Erwartungen nicht erfuellt (report :85, :125, :143; standalone identical :280-328).

The builder declared this and without a shell could not have produced the numbers; the split into 0227 is the right shape. Zurueck is against the paket state, not the build quality.

## Befund 2 — 0227's Beleg "derselbe Eintrag mit Rueckgabe 0" is unreachable as proposed

3 of the 11 FEHLSCHLAG lines come not from stale comment numbers but from teil_a (report :92-94): vorher (36,34,57) Code 1 with two extra befunde `zitierend: ...riegel.cpp:32/:39`, nachher (36,36,57) Code 0. The pinned Vorfassung (parent of 0115, blob e3038e2) now differs from today's binary by the *code* of 0147/0166/0182, not only by 0115's comment fix — 34 vs 36 aufgeloest is behaviour, not text. Transcribing numbers and moving BEZUGSSTAND (0227 steps 2-3) touches none of the three; the next report fails again and keeps misattributing: "Die Berichtigung bewegt die drei Zahlen des Riegels".

For the Projektmanager: 0227 needs one more step, inside its existing `dateien` — re-pin BAUCOMMIT_0115/VORFASSUNG_BLOB (messen.py:73-76) to the parent of the transcription commit, restoring teil_a's original meaning (the Berichtigung must not move the numbers). Amendment to 0227, not a new package; noted here instead of a proposal to avoid a second claim on messen.py.

## Searched, nothing found

- Weakened tests: none — no threshold lowered, no assertion removed; the stand gained checks (needle count, blob verification, SIGTERM restore, heile_unterbrochenen_lauf) over its never-run predecessor.
- Patterns the script needs still exist in today's riegel: "Zitate der geprueften Form gefunden" (:4228), "Selbsttest Abstand" (:3076/:3092/:3119), Aufschluesselung wording (:1574), ZAEHLZEILE guard exercised live (B1/B2 entschaerft reached the Bestand).
- Timeout sum 600+240+120+300 = 1260 > 900: acknowledged in CMakeLists.txt:252-257; real sum measured last night 68.6 s. No package needed.
