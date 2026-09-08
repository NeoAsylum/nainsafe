---
id: 0262-punkt-zwei-und-drei-des-weo-nachweises-stimmen-nicht-mit-sich-selbst
rolle: datenbauer
status: gebaut
haengt_an: []
vermerk: "ACCEPTED 2026-09-08 (sixteenth run), project manager -- `vorschlag` -> `offen`, **subject, cut and acceptance unchanged.** Good proposal: three defects, each with the probe that reproduces it in one line, and it argues *why not folded into `0256`* out of `0256`'s own scope warning rather than out of preference. That argument is correct -- `0256` is `fertig` tonight and its acceptance named the two *richtigen Zahlen* claims only. || **THE FIVE QUESTIONS. Role:** `datenbauer`, in `baulauf.py:BAUROLLEN`, reviewed by the `daten-pruefer`. **Tools:** `Read`, `Grep`, `Edit(ventures/**)`, and `WebFetch` for the optional query -- **fetch is permitted, not required**, and an outage is not a finding about you. **Acceptance:** three named sites, each checkable by reading; the eight values checkable by comparison. **Dependency:** none, and none is owed -- `0256` landed and was reviewed; you edit the passage it left. **Files:** `daten/deckungsbefund-1997.md` alone, free since `0256` went `fertig` tonight. || **DEFECT 3 IS THE ONE THAT COSTS SOMETHING, and the reviewer said so.** `0256` scoped point 3 off its values and onto *Startjahr und Wertezahl*, so the load moved to a retrieval that is named nowhere: `Grep 'GGXCNL'` over `daten/` gives one hit, `:300`, prose. **Either name the query with its retrieval date, or say in the file that this Befund does not record which query delivered the numbers.** Both close it; the second needs no network. Defects 1 and 2 are wording, one edit each. || **THE EIGHT VALUES ARE THE HARD LIMIT.** Six at `:289`-`:290`, plus -13,18 and -14,13 at `:301`. The `0256` review verified every one digit for digit against the pre-edit copy in `befunde/messung-0069/baum/`; that copy is your reference too. **A package that comes back having moved a number has failed whatever else it did.** Defect 1 is a *count word*, not a value: `:299` says six, the list has seven. || **SAY NOTHING ABOUT `quellenbefund-leitzinspfad.md`, in either direction.** `0263-die-achtundsiebzig-war-nie-achtundsiebzig` is open on that file tonight, in the lane next to yours. The only mention here is `:208`, pre-existing, in the `DISR` section -- leave it. **Insert below `:283`;** every citation into this file runs to `:214`, so edits there shift nothing and cost no re-verification."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/deckungsbefund-1997.md]
abnahme: In `deckungsbefund-1997.md` the count word at `:299` matches the number of values listed at `:289`–`:290`; the lead-in at `:283`–`:284` names the point it means without contradicting `:304`–`:305`; and the `GGXCNL_NGDP` figures at `:300`–`:301` either carry a named query with its retrieval date or the sentence is scoped to say they rest on an unnamed one. The eight values stay unchanged.
---

# Three self-contradictions in the passage `0256` just rewrote

Proposed 2026-09-08 by the daten-pruefer out of the `0256` review
(`befunde/pruefung-0256-…-2026-09-08.md`). `0256` did what it was asked — both „richtigen
Zahlen" claims are retired and the values are intact. These three sit next to that work
and were not in its acceptance.

| Site | Defect | Probe |
|---|---|---|
| `:299` | says „die **sechs** Werte"; `:289`–`:290` lists **seven** (USA 2020/2021, DEU 2010/2020, CHN 2020, BRA 2020/2021) | count them |
| `:283`–`:284` | „Zwei davon tragen …; **das dritte** hält die Einheit fest" — the unit point is number **2**; point **3** says of itself „trägt über Startjahr und Wertezahl, **nicht** über die Werte" (`:304`–`:305`) | read both |
| `:300`–`:301` | „beginnt ebenfalls 2001 und liefert 31 Werte, darunter 2009 = −13,18 und 2020 = −14,13" — no `GGXCNL_NGDP` query named in the file | `Grep -n 'GGXCNL'` over `daten/`: one hit, `:300`, prose only |

The third is the one that costs something. `0256` scoped point 3 away from its values and
onto „Startjahr und Wertezahl" — so the load of point 3 now rests entirely on a retrieval
that is nowhere named, while point 2 next to it cites its query at `:260`–`:261` with a
date. The fix is symmetrical with what `0256` already did, and the `WEO 9.0.0` path is
one substitution away from the one at `:261`.

## Why a package of its own

`0256`'s `abnahme` names the two „richtigen Zahlen" claims only, and its `vermerk` warned
twice against widening. Defects 1 and 2 are inherited or newly introduced wording, not
those claims; defect 3 is a different indicator (`GGXCNL_NGDP`, Reihe 12) and a different
question — not „is this graded correct without a reference", but „where does this number
come from at all". Folding them into `0256` would have been the scope creep it was told
to avoid.

## Limits

- **The eight values stay.** Six at `:289`–`:290`, and −13,18 / −14,13 at `:301`. A
  package that comes back having edited a number has failed whatever else it did.
- **Say nothing about `quellenbefund-leitzinspfad.md`** in either direction. It is being
  rewritten in the lane beside this one.
- **Fetch is permitted, not required.** Scoping the sentence („welche Abfrage die Zahlen
  geliefert hat, hält dieser Befund nicht fest") closes defect 3 without network. An
  outage is not a finding about this package. If you do fetch, `IMF.RES/WEO` is already
  vetted in `specs/…/daten.md` and reached under `api.imf.org` (`:404`–`:405`).
- **Insert below the last cited line where you can.** Citations into this file run to
  `:214`; edits at `:283`+ shift nothing.
