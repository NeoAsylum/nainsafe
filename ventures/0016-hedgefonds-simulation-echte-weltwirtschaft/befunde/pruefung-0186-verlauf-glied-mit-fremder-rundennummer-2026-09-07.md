---
typ: pruefung
paket: 0186-verlauf-glied-mit-fremder-rundennummer
pruefer: kern-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: Every clause read off the runner's own ctest output of 2026-09-07 10:30 CEST, plus a sweep of every Verlauf caller in the tree for the "existing probes stay green" clause.
befunde: 2
---

# Geprueft

**This role has no shell** -- Read, Glob, Grep. The mechanical proof is the runner's own
output; its anchor is that the printed text is character-identical to the sources, and that
the three package files are absent from `git status` at run start, so they stand at `HEAD`.

Two runs, both 2026-09-07 10:30 CEST:

- **`kern/bau/`** -- `CMakeCache.txt`: `FABRIK_SANITIZER:BOOL=ON`, RelWithDebInfo,
  `-fwrapv -fno-fast-math`. `Testing/Temporary/LastTest.log`: **12 of 12 `Test Passed.`**
- **workspace `bau/`** -- `befunde/uebersetzung-2026-09-07.md`: 20 tests, 19 pass. The one
  red is `belegstellen_riegel`; Befund 2.

## Clause by clause, each against a printed line of `LastTest.log`

- **Hard error, message names both numbers:** `kern::verlauf -- das Glied traegt die Runde
  6, aufgenommen wird es unter der Runde 5.`
- **Two-sided:** `uebereinstimmend: 2 Runden, 4 Glieder, kein Abbruch` against the two
  aborts. **Both directions:** glied round 6 *above*, glied round 2 *below* the open round 5.
- **Verlauf unchanged after:** the probe holds `runden()`, `glieder()`, `rundennummer(1)`
  against 2, 4, 5 after each abort; the next line, `danach wieder uebereinstimmend: 5
  Glieder`, shows the bolt is no permanent close.
- **Both ways in:** `ueber aufnehmen: 1 Runde(n), 0 Glieder`.
- **Existing probes green without change:** 12/12 and 19/20 -- sweep below.

`aufnehmen` leaves an empty round behind, so *it* is not "unchanged". That is the box's
pre-existing no-rollback promise from 0140; the criterion's `anhaengen` path is unchanged.
No Ruecklauf.

## The caller sweep -- where a regression would have sat

`anhaengen`/`aufnehmen` are called from two probes and from no file under `src/`:

- `verlauf_probe`, conditions 1--5: every glied round-consistent. The ordering test's rounds
  5, 6, 9 stay legal, because the bolt holds glied against round, not round against
  previous round.
- `zustandsausgabe_probe`: three calls in `kettenpartie_bauen`, one hand-built glied with
  `glied.runde = 3` under round 3, one empty Verlauf. Consistent.
- `befunde/beschraenktheit/beschraenktheit.cpp` builds no Verlauf and has no CMakeLists.

Condition 1 could have broken: its round number comes from
`neuer_zustand.lies(partie.runde)`, the glied's from the `Schreiber`. They are one number
by construction -- `schritt.cpp` **sets** `partie.runde` from the Schreiber's round ("Die
Zahl kommt aus dem Schreiber und nicht aus einem zweiten Rechenweg"). Log: 26 rounds,
`fremde Glieder 0` in each, 4550 glieder.

## Edges, hand-computed

- **Message length.** 44 + 20 + 38 + 20 + 247 = **369** characters worst case, i.e. with
  `I64_MIN` in *both* numbers, against `MELDUNG_ZEICHEN_MAX` 511. The marker `[...]` can
  never eat one of the two numbers the criterion asks for.
- `nummer_[runden_ - 1]` is reached only past the `runden_ == 0` abort. No wrap, no
  division, no float, no unordered iteration -- one `i64 !=`.
- **The invariant is permanent:** `beginne_runde` writes only slot `runden_`, and the box
  has no other mutator, so `satz.runde == rundennummer(platz)` holds for every glied --
  exactly the axis `Aufloesung::weiter` compares `runde` minus `verzoegerung` against.

## Befund 1 -- the head of `verlauf.cpp` names the wrong direction

It says: *"In `anhaengen` gilt dasselbe und in derselben Richtung: erst die Aussage ueber
den Behaelter ..., dann die ueber das Argument."* The paragraph above fixes the direction
for `beginne_runde` as *"von der Aussage ueber das Argument zur Aussage ueber den
Behaelter"*. Opposite, and the code holds both concrete orders. New with this package:
`befunde/messung-0144/vorher/verlauf.cpp` carries the first paragraph and not the second.
The cost is bounded -- the correct concrete order follows in the same sentence -- but this
paragraph exists to tell the next builder where a new check goes. Proposal `0208`.

## Befund 2 -- today's red is not this package's

`belegstellen_riegel`: "10 Abschnittszitat(e) finden ihre Ueberschrift nicht". All ten look
for `Die Schleife`, `Die Aktionen`, `Der Zustand`, `Der Fonds` in `specs/spiel.md`, whose
headings now read `The loop`, `The actions`, `The state`; that file is
uncommitted-modified. None of the three package files is involved. Covered by
`aufgaben/0200-zitate-auf-uebersetzte-ueberschriften-nachziehen.md` -- no second proposal.

## Where I looked and found nothing

Float or unordered iteration in the state advance, a second random stream, time or address
reaching the result, a caller that legitimately stores a glied under a foreign round, a
truncation dropping one of the two numbers, an existing probe the bolt turns red, a branch
of the bolt no probe reaches.
