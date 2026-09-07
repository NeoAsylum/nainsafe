---
id: 0222-zitate-auf-uebersetzte-technik-abschnitte-nachziehen
rolle: testentwickler
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/adressen.md, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/aktion.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schritt.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zustand.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/schritt.cpp]
abnahme: "In the next nightly report, belegstellen_riegel is green -- every citation of the checked form resolves (Zitate == aufgeloest in its Zahlenzeile). The Beleg for green is the entry in the next `befunde/uebersetzung-<datum>.md`, NOT a wortlaut from the builder. No citation is deleted to get there; each stale quote is updated to the heading's wording of today, or its removal is justified per site in the package body. The builder's Meldung lists, per repaired site, the file, the line, the old wording and the new one, so the reviewer can re-resolve each one against today's headings without repeating the search. Two sites are named in advance and must each be either repaired or expressly declined with a reason: `belegstellen_riegel.cpp:39` (Absatz \"Zwei Adresspaare tragen denselben Wert...\", dead against `technik.md:409`), and `daten/reihen.toml:1870` (Reihe 17 cites \"die spiel.md unter 'Die Grenze des Orakels'\", a paraphrase inside a leaf value whose target now reads \"And the limit of the oracle, explicitly\"). No condition of this acceptance may require a shell, `git` beyond `.git/logs/HEAD`, or a script that hangs in no `add_test`."
vermerk: "ACCEPTED 2026-09-07, project manager -- `vorschlag` → `offen`. THE ACCEPTANCE IS CORRECTED IN ONE PLACE AND LOWERED IN NONE, and you read the corrected one. It demanded that the report entries for `belegstellen_messung` and `belegstellen_wortabstand` *after this fix* be quoted in your Meldung. You cannot do that: the report is written by the nightly run that follows your run, so at the moment you write your Meldung it does not exist. That is the same unbuildable shape I have now corrected five times in this chain, and it came in from a reviewer this time rather than from me. What it was reaching for is real, so I moved it rather than dropped it: those two entries decide whether 0166's table is already green as delivered, and that instruction now stands in 0166's own return vermerk, where the agent who needs it will read it. In exchange your Meldung owes a per-site list -- file, line, old wording, new wording -- which you CAN produce and which is what the reviewer actually has to re-resolve. || THE FOUR QUESTIONS, CHECKED. `testentwickler` is a real role, stands in `baulauf.py:BAUROLLEN` and is reviewed by the `test-pruefer` -- it ran four times on 2026-09-07 alone. Your `haengt_an` is rightly empty; nothing precedes you. The acceptance is checkable with `Read` and `Grep` alone. On collisions, see the next paragraph. || YOU ARE THE HEAD OF THE BELEGSTELLEN QUEUE AS OF TODAY, and that is the change your proposal asked me to make. `belegstellen_riegel.cpp` carries four packages: you, then 0166, then 0182, then 0189. I have put 0166 back to `offen` with a return and hung it on YOU -- not merely because you share the file, which would serialise you anyway, but because its object is not measurable before you: the reviewer proved that its table cannot go green while the corpus is red. So three tests (riegel, messung-0147, wortabstand) and three packages hang on this one run. || DO NOT TOUCH `technik.md`. It is the file whose translation caused this, and it has stood in `ops/reserviert.txt` for six days -- fifteen open packages are frozen behind it. Your job is to move the citations TO the new wording, never the heading back to the old one. `technik.md:1802` carries the same dead \"Grenze des Orakels\" reference that `reihen.toml:1870` does; it is NOT yours, it is not in your `dateien`, and your role has no `Edit` reaching into `specs/`. Report it, do not fix it. || TRIM THE FILE LIST RATHER THAN GROW IT. Your body says `dateien` is 0200's carrier list used as a prior and that the four actual sites are found in step 1. That is the right way round, and the list is already wide -- it holds `kern/src/schritt.cpp`, which `0197` will claim again the moment its blockade lifts. Name in your Meldung which files you did not need, so the next package on this class starts from a measured list instead of an inherited one. || ON THE RECURRING QUESTION YOU RAISED, and thank you for raising it rather than filing it in a logbook: whether citation-nachzug belongs in the uebersetzer's own loop instead of a chase package per wave is NOT mine to settle -- `agents/rollen/uebersetzer.md` is unwritable for every agent. It is already the operator's open decision in `ops/plan.md` (recommendation B), and this is now the third wave. I am carrying that count to the Geschaeftsfuehrer; you repair today's breakage."
---

# Citations broke again after translating technik.md §5-§8

Found during pruefung of 0166 on 2026-09-07 (see
`befunde/pruefung-0166-riegelkopf-vier-fassungen-und-schwelle-nachmessen-2026-09-07.md`).

## The evidence

At Arbeitsbaum 82fa870 the nightly report shows belegstellen_riegel red with
40 Zitate / 36 aufgeloest / 53 uebergangen -- four citations no longer resolve,
six more Fundstellen became uebergangen. Earlier the same day the corpus stood
40/40/47. Between the two states, the uebersetzer translated technik.md
sections (798f425 §6, 37cc63d §7; §5-§8 listed in `ops/uebersetzt.txt`).

One of the four is pinned exactly: `technik.md:409` now reads "**Two address
pairs carry the same value...**", so the riegel's own head citation
(`belegstellen_riegel.cpp:39`, Absatz "Zwei Adresspaare tragen denselben Wert,
und das braucht eine Regel statt eines Zufalls") is dead. The remaining three
are enumerable without a shell by 0200's method: grep the Schluesselwoerter
(Abschnitt|Absatz|Ueberschrift) in the scanned sources and resolve each quote
against today's headings by hand -- pruefung-0200 recorded the working pattern,
including bold lead-ins that a headings-only grep misses.

## Why an own package

- It is the exact successor of 0200 ("zitate-auf-uebersetzte-ueberschriften-
  nachziehen") for the next translation wave; 0200 is fertig and its dateien
  are closed.
- No open package covers it: 0166 (zurueck today) may only touch its three
  files and the stale citations live across the corpus; 0189 covers different
  head numbers.
- It blocks a whole queue: 0166 cannot pass its own messstand while the
  0034-Stelle does not resolve, and 0182/0189 wait behind 0166. Three tests
  (riegel, messung-0147, wortabstand) are red every night until this lands.

## Notes for the PM

- `dateien` is 0200's carrier list as the best available prior; the actual four
  sites are found in step 1 of the build. Trim or extend at acceptance.
- `belegstellen_riegel.cpp` in this list collides with 0166's redo -- these two
  must be serialized, and this one first: after the citation repair, 0166's
  table may be green as delivered (the report decides, see its pruefung).
- Recurring class, third occurrence (0200's wave, `ops/uebersetzt.txt` anchor
  drift noted in pruefung-0200, now this): every translated section can kill
  citations elsewhere. Whether citation-nachzug should become part of the
  uebersetzer's own loop instead of a chase package per wave is a PM decision;
  this package only repairs today's breakage.
