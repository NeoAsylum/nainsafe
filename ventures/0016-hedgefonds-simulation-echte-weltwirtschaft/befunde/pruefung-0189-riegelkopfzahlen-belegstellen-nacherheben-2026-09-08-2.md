---
typ: pruefung
paket: 0189-riegelkopfzahlen-belegstellen-nacherheben
pruefer: test-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: green belegstellen_kopfzahlen entry in uebersetzung-2026-09-08.md proven equivalent to rc 0 with a single, unweakened rc-0 path; every head number receipted against the 09-07 report; re-pin and Gegenprobe verified at source
befunde: 1
---

# Pruefung 0189, second run (after Ruecklauf 1) — geprueft

## Evidence, clause by clause

1. **Night-run proof.** `befunde/uebersetzung-2026-09-08.md`: `belegstellen_kopfzahlen` **Passed** on both build paths — root :123-124 (15.93 s), standalone :290-291 (16.03 s). `werkzeuge/belegstellen/CMakeLists.txt` shapes no results (no PASS_/FAIL_REGULAR_EXPRESSION, WILL_FAIL, SKIP anywhere; `add_test` :239-242 calls the script bare), so Passed ⇔ rc 0. The rc-0 path (messen.py:765-769) requires every expectation met; an old script fails teil_a, an old comment fails B1/B2 — so the green entry itself proves the run measured the transferred state, on both paths.
2. **Hook-in** unchanged from run 1: no `if(EXISTS)`, FATAL_ERROR guard :230-237, TIMEOUT 300 :258; measured ~16 s, ≈19x headroom, far under the runner's 900.
3. **Numbers copied, not counted.** Every head number is receipted in the package body against `uebersetzung-2026-09-07.md`; I re-checked each row: 47/70 (:95), 36/36/57 (:91, :97-:100), elf/zehn and 2/1/7 (:95), Angabe 2 36/36/57 + Summe 93 (:101-:104), Stand 7ebc1a9 (:89, :122). Head carries them at riegel.cpp:560-565, :602-605, :1016; exactly three `gegen den Stand \`7ebc1a9\`` sites (:560, :602, :1586); the dated 5d5e2d6 mention (:527) has a different wording and correctly escapes the staende check (messen.py:749-752). BEZUGSSTAND = 7ebc1a9 (messen.py:102).
4. **Re-pin (my run-1 Befund 2).** `VORFASSUNGSSTAND = "d8e3bfb"` (messen.py:94), blob fetched via rev-parse and re-verified by self-computed SHA-1 (:190-215). d8e3bfb is 4 commits before transfer commit 0d6cf7b, not the literal parent (parent e3f36e6, `.git/logs/HEAD:961-965`) — but the three intermediate packages 0228/0165/0197 claim only parameter.toml, technik.md, kern/schritt* (their `dateien:` lines), so the pinned file content equals the parent's; an ancestor pin can only false-red, never false-green. The operative clause ran live: Passed requires equal numbers, equal return codes, and identical befundlisten in teil_a (:408-420), and test 17 `belegstellen_riegel` Passed pins that code at 0 — "teil_a vorher wie nachher Rueckgabe 0" held.
5. **Rotnachweis driven, not asserted, nightly.** B2 scharf runs live and must yield exactly 1 Meldung with the quoted wording (:575-600); mutant needles counted ==1 (:320-326); Gegenprobe needles counted ==1 (:670-678); Gegenprobe turns rc 1 if any falsified Angabe stays green (:709-712). $TMPDIR is scratch: self-fetched, self-cleaned on green and red (:717-773), tampered VORHER aborts on blob mismatch (:244-256).

## Finding 1 — to the project manager (criterion text, not the build)

The abnahme is internally inconsistent since the 09-08 amendment. "je mindestens eine Meldung am alten Wortlaut" is unsatisfiable for Angabe 3 under the re-pin: at d8e3bfb the siebte-Herkunftshinweis sentence is already correct, so the old wording yields 0 Meldungen for Angabe 3 by construction. The builder replaced the old-wording Gegenprobe with a per-Angabe one-step falsification (rationale at messen.py:644-661) — strictly stronger (each Angabe individually proven rot-capable, immune to Vorfassung convergence) and executed nightly. I judged against the purpose; please reconcile the abnahme wording so the next Pruefer does not trip over the letter.

## Searched for and not found

Weakened thresholds or removed assertions (rc-0 path is unique; all melde/SystemExit exits traced), result shaping in CMakeLists, needles hitting ≠1, $TMPDIR preconditions, numbers counted forward instead of copied, a green run at a pre-transfer state.
