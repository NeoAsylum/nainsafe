---
typ: pruefung
paket: 0199-messung-0180-misst-den-stand-vor-0194
pruefer: test-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: Runner report 2026-09-07 shows `zahlwort_messung` Passed (exit 0) in both builds; mutant wordings and expected `was` texts cross-checked statically against today's riegel source.
befunde: 0
---

# Pruefung 0199 -- the counter-probe hits the delivered state again, and it runs

## The acceptance criterion, piece by piece

**"`messen.py` laeuft am ausgelieferten Stand ... 0 am Bestand."** Proven by the
runner, not by me: `befunde/uebersetzung-2026-09-07.md` lists `zahlwort_messung` as
test 21/21 of the workspace build (Passed, 13.50 s) and 3/3 of the standalone build
(Passed, 13.55 s). ctest says Passed only on exit 0, and the target sets no
result-overriding property (only `TIMEOUT 600`).

**"Teil B setzt fuenf Mutanten, jeder findet seinen Wortlaut genau einmal."**
Enforced at run time: `einmal_ersetzen` (messen.py:100) aborts unless the count is
exactly 1, and every `Messfehler` lands in the handler at messen.py:429 -> exit 1 ->
ctest red; the green run is the proof. Statically confirmed the report matches
today's tree: all five target sites exist in `zahlwort_riegel.cpp` -- M1 line 543,
M2 574, M3 666, M4 490 (full multi-line block), M5 848-853 in
`zaehlung_zur_sorte()`, i.e. Weg 1 of the package, not the stilllegen path.

**"die erwarteten Fallnummern sind die des heutigen Selbsttests."** The script now
expects `was` part-wordings, as the vermerk directed. `ordne_zu` (messen.py:210)
demands a bijection both ways -- too few ripped and "eine fremde Tabelle misst mit"
are separate failures -- plus M5's guard that no non-Verdrahtung table rips.
Spot-checked the wordings against today's tables (riegel 1172, 1210, 1479, 1494,
1512); the message form `Selbsttest <Tabelle>, Fall <n> (<was>):` on stderr (riegel
1119, 1226, 1269, 1398, 1525) matches the parser regex (messen.py:203).

**"1, wenn man einen Mutanten auf einen Wortlaut umstellt, den es nicht gibt."**
Not shown by a separate run -- nothing in this factory can execute a deliberately
broken copy (no shell; ctest runs only the delivered file). What stands instead:
`selbstprobe()` (messen.py:118) exercises the abort mechanism on every invocation,
missing-wording and found-twice cases included, and the path from `Messfehler` to
`SystemExit(1)` is four unconditional lines (messen.py:429-432). I read them, I
could not run them. That is the strongest proof this execution path allows; noted
so nobody mistakes it for a demonstrated red run.

## What I looked for beyond the criterion

- **Weakened expectations**, the gravest finding of this role: one candidate. A2
  expects code 2 where the pre-0194 `lauf.txt` shows code 1 with findings. Judged
  not a weakening: the riegel's sensitivity probe genuinely saturates (one sorte-3
  site, already red, cannot get redder), the expectation pins the reason string
  ("der Mutant bleibt an Sorte 3 gruen" must appear, messen.py:337), so a fix flips
  the case red and forces the five named findings back in -- and that fix is filed
  as `aufgaben/0213-empfindlichkeitsprobe-saettigt-bei-einer-fundstelle.md`
  (exists, `status: vorschlag`).
- **Silent-skip paths in CMake:** none. `if(NOT EXISTS) -> FATAL_ERROR`
  (CMakeLists.txt:130), the forbidden `if(EXISTS) add_test()` form is absent, and
  the Python fallback keeps a missing interpreter red instead of invisible.
- **Table coverage:** five tables, five mutants, each shown to rip exactly its
  expected set in the green run.
- Minor, no package needed: `befunde/messung-0180/lauf.txt` is a pre-0194 record;
  it carries its own HEAD stamp (584326c) and is recognizably historical.
