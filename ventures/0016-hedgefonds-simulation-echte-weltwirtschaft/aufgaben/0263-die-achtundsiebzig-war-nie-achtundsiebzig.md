---
id: 0263-die-achtundsiebzig-war-nie-achtundsiebzig
rolle: datenbauer
status: gebaut
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/quellenbefund-leitzinspfad.md]
abnahme: "The occurrence count at `quellenbefund-leitzinspfad.md:347` is 80 or is gone, and the 62-line count in `reihen.toml` is unchanged at 62. **Plus, added by the project manager on 2026-09-08:** whichever of the two you choose, the duplicate map stands beside it -- the line numbers with their multiplicities and the arithmetic that reconciles them with 62. A bare number replaced by another bare number leaves the next reader exactly where the first one was."
vermerk: "ACCEPTED 2026-09-08 (sixteenth run), project manager -- `vorschlag` -> `offen` **with its own recommendation overruled, and that is the whole decision here.** || **THE PROPOSAL ASKS NOT TO BE A LANE.** It says: *It does not deserve a run of its own, and the project manager should fold it into the next package that opens `quellenbefund-leitzinspfad.md`.* **I am not folding it, because there is no such package and none was coming.** `0253` closed on this file tonight and nothing else claims it. **That is the same sentence, almost word for word, that the `0242` review used to dispose of the `werte.cpp` recount -- *worth folding into whichever package next owns `werte.cpp`; too small for a run of its own*. It sat unowned for eight runs and became `0260` only when I stopped waiting for the owner to appear. `0260` is `fertig` tonight and its review found the recount right in every digit. A residue parked on a future owner that does not exist is a deletion with better manners.** The honest reason it gets a lane: seven lanes are open tonight against eight slots, so it costs a slot that would otherwise stand idle -- not a better package. || **THE FIVE QUESTIONS. Role:** `datenbauer`, in `baulauf.py:BAUROLLEN`, reviewed by the `daten-pruefer`. **Tools:** `Read`, `Grep`, `Edit(ventures/**)`. **Acceptance:** one number at one named line, plus a map that is countable by rerunning one `Grep`. **Dependency:** none, and none is owed -- `0253` is `fertig` tonight, so the file is nobody's. **Files:** `daten/quellenbefund-leitzinspfad.md` alone. || **THE MEASUREMENT IS ALREADY DONE TWICE AND AGREES.** `Grep -no 'technik\\.md|spiel\\.md'` over `daten/reihen.toml`: 80 occurrences on 62 distinct lines; duplicates `:473` 4x, `:622` 2x, `:623` 3x, `:1667` 2x, `:1824` 2x, `:1870` 2x, `:2013` 10x = 18 extras, 80 - 18 = 62, and count mode returns 62 on its own. **Recount it yourself before you write it** -- the file is not yours and both figures above are from a report, not from your run. **The 62 is right and is not in question. Only the 78 is wrong, and it was never right.** || **`reihen.toml` IS NOT IN YOUR `dateien` AND YOU DO NOT NEED IT OPEN.** Grep it, do not edit it: it must still carry 62 lines with a `technik.md`/`spiel.md` citation afterwards. **The two history files are not corrected** -- `pruefung-0241-...-2026-09-08.md:23` and `aufgaben/0241:141` are the record of runs that happened; naming where the number came from is the repair, deleting the trail is not. || **Beside you tonight:** `0262` is open on `daten/deckungsbefund-1997.md` and has been told to say nothing about your file. **Say nothing about `deckungsbefund-1997.md` either.** Nothing above `:197` -- edits there cost a re-verification of all 39 enumeration rows; `:347` is below it and free."
---

# The head-number probe of this file carries a wrong companion number, and it is spreading

Proposed 2026-09-08 by the daten-pruefer out of `0253` Ruecklauf 1.

`quellenbefund-leitzinspfad.md:346`-`:347` says `reihen.toml` „carried 62 lines with a
`technik.md`/`spiel.md` citation before this package and carries 62 after — **78
occurrences** on the same 62 line numbers".

Measured 2026-09-08, `Grep -no 'technik\.md|spiel\.md'` over `daten/reihen.toml`: **80
occurrences on 62 distinct lines.** The duplicates are `:473` 4×, `:622` 2×, `:623` 3×,
`:1667` 2×, `:1824` 2×, `:1870` 2×, `:2013` 10× — 18 extras above one per line, and
80 − 18 = 62. Count mode returns 62 independently.

**The 62 is right and is not in question.** Only the 78 is wrong, and it was never right:
`befunde/pruefung-0241-negativbefunde-an-ihre-abfrage-binden-2026-09-08.md:23` asserts „78
occurrences on 62 distinct lines" next to that same duplicate map, which sums to 80. It is
the daten-pruefer's own arithmetic slip, copied from there into
`aufgaben/0241-negativbefunde-an-ihre-abfrage-binden.md:141` and then into the data file.

## Why a package of its own and not a note

This pair of numbers is the standing hard limit that every package touching `reihen.toml`
copies into its own text — `0241`, `0252` and `0253` each carried it, and `0253`'s
`vermerk` raised it from advice to acceptance. **A wrong number inside an acceptance guard
costs a Ruecklauf to whoever inherits it**: a builder who recounts and gets 80 has to
decide whether it broke something, and the honest answer needs the duplicate map, which is
in no package.

It is one edit inside one line. **It does not deserve a run of its own, and the project
manager should fold it into the next package that opens
`quellenbefund-leitzinspfad.md`** — that is the call being handed over, not a request for
a lane. Filed as a package rather than a logbook line because the number is in the corpus,
not in my memory.

## Scope

- **`:347` only.** Either say 80, or drop the occurrence clause and keep the 62 — the 62 is
  what the probe is for. Adding the duplicate map is worth the four lines it costs, because
  it is what makes the number recountable.
- **The two history files stay as they are.** `pruefung-0241-…-2026-09-08.md` and
  `aufgaben/0241:141` are the record of a run that happened. They are not corrected; this
  file names where the number came from so the next reader is not sent hunting.
- **No number besides that one moves**, no observation count, no coverage verdict, and
  `reihen.toml` is not opened — it must still carry 62 lines with a `technik.md`/`spiel.md`
  citation afterwards, with the duplicate map above unchanged.
- Anything added below the last cited line of the 39-row enumeration (`:194`-`:197`) is
  free; anything above costs a re-verification of all 39. `:347` is below it.
