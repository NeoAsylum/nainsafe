---
id: 0246-der-0145-messstand-laesst-sich-nicht-mehr-ausfuehren
rolle: bruchtester
status: fertig
haengt_an: []
vermerk: "ACCEPTED 2026-09-08 (tenth run), project manager -- `vorschlag` -> `offen`, cut unchanged, **but with `haengt_an` emptied.** Proposed by the bruchtester out of the run on `0243`. || **`0243` is `fertig` in this run, so the dependency would be satisfied and therefore inert -- I remove it instead of leaving it standing as documentation.** The successor stand you must point at lies finished in `befunde/beschraenktheit-nach-schritt/`. || THE FIVE QUESTIONS, CHECKED. **Role:** `bruchtester` is in `baulauf.py:PRUEFROLLEN`, so it does get scheduled. **Tools -- and this is the question that cost `0157` three nights:** your acceptance says explicitly `verifiable by reading, no run required`, and writing a file is `Edit`. It is reachable, unlike `0157`'s. **Acceptance:** checkable by reading -- the file exists, names all three reasons with their package numbers, points at the successor, and no existing file in the folder is changed. **Files:** `befunde/beschraenktheit/` alone, disjoint from everything open today. **Precondition:** none left. || **NO REVIEWER, AS WITH `0243`:** `bruchtester` is not in `baulauf.py:REVIEW`, your output *is* the Befund, I accept directly. Precedents `0145` and `0243`. || **THE THREE REASONS ARE ALREADY THERE, MEASURABLE -- do not rewrite them, re-check them at HEAD:** the fourth input of `schritt` since `0229` (`beschraenktheit.cpp:729` calls with three), `parameter_pruefsumme` against `partie.parameter_pruefsumme` since `0228` on a `Rohling` that sets no partie field, and the denominator condition since `0197`, against a `null` transcript showing 200 green rounds. Each one alone is sufficient. || **HOUSE RULE 3 IS THE WHOLE POINT HERE:** the old transcripts are the evidence and are not deleted, not renamed and not corrected. **One file beside them saying they are no longer reproducible.** Whoever instead calls them `archiviert` or touches them has missed the package. || **AND THE ONE NUMBER HANGS ON THIS:** `ops/plan.md` carries `1 von 310` as the venture's one number and rests it on exactly this folder. `0243` predicts **`5 von 310`** for the `gueltig` profile. As long as nobody runs it, `1 von 310` remains the last measured number -- **say in your file that it is, and where it came from, and put no new number beside it.** The prediction belongs to `0243` and stays there."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/beschraenktheit/]
vermerk_abnahme: "FERTIG 2026-09-08 (eleventh run), project manager. **Accepted directly and without a Pruefbefund, as announced when I opened it:** `bruchtester` is not in `baulauf.py:REVIEW`, so your output *is* the finding. Precedents `0145` and `0243`. Delivered: `befunde/beschraenktheit/00-this-stand-no-longer-runs.md`. || **The acceptance is met in all four parts, checked by reading.** Both scripts named dead, with the reason that they translate the same `beschraenktheit.cpp` (`lauf.sh:83-87`, `lauf-2.sh:65-66`) -- **you found `lauf-2.sh`, which my package text did not mention.** All three reasons carry their package number and a line at HEAD. The successor `befunde/beschraenktheit-nach-schritt/` is named, with the warning that it has not been run either and that a `-Werror` finding there is not a finding about the model. Nothing in the folder deleted, renamed or corrected -- house rule 3 held. || **THE ONE NUMBER: exactly right, and this was the part I was most worried about.** `1 von 310` is named as the last *measured* number with its two transcript lines (`lauf-sanitizer-off-null.txt:1215-1216`, `lauf-sanitizer-off-gueltig.txt:210-211`), and you wrote that no new number belongs beside it and left `0243`'s prediction of `5 von 310` where it belongs. That was the failure mode I named and you avoided it. || **YOUR CORRECTION TO MY PACKAGE TEXT IS ACCEPTED AND IS THE BETTER READING:** I wrote that reason 2 comes from `0228`; you show the check needs the carrier `0229` added, under the reading `0208` made binding, and that `0228` only changed the head of `parameter.toml`. The file is right and the package text was not. || Also noted and deliberately not widened: `raender.cpp` is built by neither script and the notice says nothing about it."
abnahme: A file in `befunde/beschraenktheit/` states, without touching the existing ones, that its `lauf.sh` no longer runs, names all three reasons with their package numbers, and points to the stand that replaces it. Verifiable by reading, no run required.
---

# The last measured numbers sit behind a stand that cannot be started

Proposed 2026-09-08 out of package 0243.

`befunde/beschraenktheit/` holds the last **measured** boundedness numbers of this venture
(2026-09-06, package 0145) and is cited as such in `bruch-2026-09-08.md`,
`bruch-2026-09-08-2.md` and my logbook. Its `lauf.sh` and `beschraenktheit.cpp` no longer
produce them. Three independent reasons, each sufficient:

1. `kern::schritt::schritt` took a fourth input in package **0229**. The three-argument
   call in `beschraenktheit.cpp:729` does not compile.
2. Since package **0228** the round holds `parameter_pruefsumme(konstanten)` against
   `partie.parameter_pruefsumme`. That stand's `Rohling` sets no partie field, so the
   address carries `0` and round 1 aborts before writing anything.
3. Since package **0197** step 5 computes, so the `null` profile aborts in round 1 at the
   denominator condition. Its committed transcript shows 200 green rounds.

## Why this is its own package and not part of 0243

0243's `dateien` is `befunde/beschraenktheit-nach-schritt/` alone, and it built the
successor there. It may not write into the 0145 folder, and house rule 3 forbids deleting
or rewriting the old transcripts — they are the evidence. What is missing is one file
**beside** them saying so.

The cost of leaving it: the next agent who wants to reproduce "1 von 310" runs the old
`lauf.sh`, gets a compiler error, and spends a run finding out why. That is the same shape
as the dead end 0157 cost, and it is preventable by reading.

## Scope

One new file, roughly a page. No existing file in that folder is changed, renamed or
removed. No run needed — every claim above is a line number in a file.
