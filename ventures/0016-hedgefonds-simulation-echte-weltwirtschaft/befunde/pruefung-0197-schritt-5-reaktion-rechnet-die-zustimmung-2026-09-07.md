---
typ: pruefung
paket: 0197-schritt-5-reaktion-rechnet-die-zustimmung
pruefer: kern-pruefer
datum: 2026-09-07
urteil: zurueck
kriterium_geprueft: condition 2 read off the probe's own printed sheet from the build run of 2026-09-07 ("1 von 310 Groessen geaendert"), condition 1 off the body of schritt_5_reaktion, the escape clause's precondition re-searched over specs/ independently
befunde: 2
---

# Condition 2 is measured, not argued: one of 310, and the cause is not the builder's

**No shell** -- `CLAUDE.md` denies Bash to every role. The measurement below is the
runner's: `befunde/uebersetzung-2026-09-07.md` and the probe sheet the build run left in
the standalone kern tree under `bau/Testing/Temporary`.

## The four conditions

**1 -- a computed value on the four approval addresses: not met.** The body of
`schritt_5_reaktion` is one statement, `schreiber.vortrag(platz)`, and its comment still
reads „Aus diesem Schritt laufen im `weltlauf` nur Zustimmung und Regierungswechsel". No
computed value, and no rule quoted from `spiel.md`.

**2 -- more than one of the 310 changes over a round: not met, and it is printed.** The
sheet of `schritt_probe`, run at 10:30 on 2026-09-07:

```
Vorrunde 0 -> Runde 1: Pruefsumme bec587d71f6905ff vorher, a28c49f74de4388a nachher;
1 von 310 Groessen geaendert (partie.runde)
```

Both start states print the same 1. The package asked for the number before and after; the
number after is the number before.

**3 -- the ascending chain: does not fall due.** The body was not changed, so it does not
take its block as a whole, and the sentence in `kern/src/schritt.cpp` about the ascending
chain still holds as written.

**4 -- the probe passes, count not lower: met, measured.** `schritt_probe: alle
Pruefungen bestanden`, `Test Passed`, and the standalone kern tree reports „100% tests
passed, 0 tests failed out of 12". The workspace tree is red at `belegstellen_riegel` and
not from this package: all ten of its complaints are headings in `specs/spiel.md` („Die
Schleife", „Die Aktionen", „Der Zustand", „Der Fonds") that the running translation has
renamed. Package `0200` holds that already.

## Finding 1 -- the missing quantity is real, and the verdict is still `zurueck`

Searched over `specs/` independently: `Realeinkommen` occurs eight times, in `daten.md`,
`spiel.md` and `technik.md`, and every one is prose or an arrow in a chain diagram. It is
no T15 address (the nine members of `Aggregat` do not include it), no T27 key, no T23
vintage constant, none of the twenty-two in T48. T48 decides who owns that: „Ein Name in
einer Formel ... ist ein Befund und keine Bauentscheidung." The rule's only quantified
form is the comment on `zustimmung_elastizitaet` in `parameter.toml`: „Aenderung der
Zustimmung in Zehntausendsteln je Zehntausendstel Aenderung des Realeinkommens." Without
the quantity there is no right-hand side, and building one anyway would have been the
invented number `CLAUDE.md` forbids. The clause *If the specification is not enough*
applied, and the run followed it.

The verdict follows `abnahme`, which decides this case in words: „a run after which
exactly one of the 310 quantities still changes over a round in weltlauf does not meet
it." That is the sheet above. `zurueck` here means *not fulfilled*, not *build it again*:
the package belongs on `blockiert` behind `0198`.

## Finding 2 -- condition 2 was unreachable the day it was written (to the project manager)

Hand-calculated, and it survives `0198`:

1. `schritt_4_wirtschaft` is one `schreiber.vortrag(platz)` for all 152 economy addresses,
   so every function of them has `lies_neu == lies_alt`, and the *change* the rule reads
   is zero.
2. `zustimmung_elastizitaet` stands at 0, its placeholder, so `mal_geteilt(x, 0, 10.000)`
   is zero.
3. Nothing in the round can read the coefficient at all. `schritt` takes the previous
   state, the action bundle and the mode; `werte::Konstanten` has no such field; and
   `kern/include/kern/schritt.hpp` says it outright -- „`parameter.toml` wird hier nicht
   gelesen, der Rahmen braucht keinen Parameter."

`zustimmung_neu = zustimmung_alt` under any body a correct specification could licence.
Three independent reasons; no run of this package could have printed anything but 1.

**It costs a run today.** `0157` stands on `offen` with `haengt_an: [0197]`, and its
condition 1 fails unless 0197 moved a second address. Reading 0197 as `geprueft` releases
it into a run whose result is already printed above -- the same reason it was blocked on
2026-09-06.

Proposal `0208` covers point 3, which blocks all six steps and not only this one.
