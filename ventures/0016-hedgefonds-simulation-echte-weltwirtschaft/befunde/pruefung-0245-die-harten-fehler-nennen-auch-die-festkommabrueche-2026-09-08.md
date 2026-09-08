---
typ: pruefung
paket: 0245-die-harten-fehler-nennen-auch-die-festkommabrueche
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: both conditions re-derived from `kern/src/schritt.cpp` at my HEAD (after 0240 landed) -- the three named paths exist, the callers make "aus ihm heraus" exact, and no line number or site count reached the header
befunde: 2
---

# The three paths are exact; one sentence about the *other* two entries is not

## Condition 1 -- met

`schritt.hpp:309-331` now reads "**Drei weitere** ... die ersten beiden fuehren aus
`kern::werte` heraus, der dritte aus `kern::festkomma`", with a third bullet for the
overflow in the rule's fixed-point arithmetic.

Checked against `kern/src/schritt.cpp` at my HEAD (`b3c417c`, i.e. **after** `0240`, which
committed after this package):

| named path | sites | verified |
|---|---|---|
| body of step 5 itself | `:741` `mal_geteilt`, `:750` `plus` | in `schritt_5_reaktion` (`:733-760`) |
| `realeinkommenshub` | `:644` `mal_geteilt(minus(...))` | one caller: `:739` |
| `politiklast`, out of it | `:596` `plus(last, mal(...))` | one caller: `realeinkommenshub:643` |

`Grep politiklast\(|realeinkommenshub\(` over `kern/src` returns exactly those two call
sites, so "und, aus ihm heraus" is not a guess. The package's own `vermerk` said *two*
paths and put `:686/:687` in `realeinkommenshub`; at HEAD those two sites sit in the body
of step 5. The builder read the source, as condition 1 demanded, and the source wins.

"Alle drei greifen erst, wenn die drei Schranken des Rahmens gehalten haben": modus
`:854`, round number `:874`/`:882`, checksum `:914` -- all before `schritt_5_reaktion` at
`:985`. The order of the list also holds: within one country the bip barrier (`:629`)
strikes before `schaden` (`:595`) before the festkomma sites.

"weder ein Produkt mit der Null noch eine Summe mit ihr laeuft ueber", by hand: while step
3 carries forward, `richtung == 0` for all four instruments, `:592` `continue`s, so `:596`
never runs and `last = 0`; `hub = mal_geteilt(minus(0,0), 10.000, bip)` = 0 with `bip >= 1`
from the barrier; `wirkung = mal_geteilt(elast, 0, 10.000)` = 0; `plus(ausgangswert, 0)`.

`0240` added `summe_der_regel_pruefen` (`:679-700`); it aborts on exactly `plus`'s
condition, so it is no new aborting state and owes no fourth entry.

## Condition 2 -- met

No line number and no site count from `schritt.cpp` in the header. The one count, "die
beiden Hilfen", names both functions -- the altitude the two `kern::werte` entries at
`:313-322` already use.

## Finding 1 -- "Anders als die beiden Eintraege davor" is wrong about the first

`schritt.hpp:328`. A reader asking which of the three is live today is told: only the
third. Reproduce the opposite: `test/schritt_probe.cpp:1652-1660` runs
`ausgangslage_ohne_wertschoepfung(13)` through `schritt` and asserts
`BRICHT_AB_MIT("Bruttoinlandsprodukt nicht positiv", Riegel::Nennerbedingung, ...)` -- that
is entry 1 firing, and `schritt_probe` passed in this run (`uebersetzung-2026-09-08.md`).
`werte::bip` is called at `:628` every round for every country and the barrier at `:629` is
evaluated every round. Only entry 2 is structurally unreachable (`:592`). The contrast
holds against the second entry alone, not against both.

## Finding 2 -- "Drei weitere" still undercounts by one, and not where I said in 0233

`werte.cpp:733-745`: `bip` aborts on its own -- "die Wertschoepfungssumme verlaesst i64
(T7)" -- before the denominator barrier is ever reached. That cause came with the computing
body of step 5 exactly like the listed three: before `0197`, `schritt` never called `bip`.
Entry 1 is worded to the denominator condition only ("taugt nicht als Nenner"), not as a
catch-all the way entry 2 is ("jeder Ueberlauf in `kern::werte::schaden`"). The gap sits at
the position the list itself claims to order: the unlisted abort strikes at the same call,
before the listed one.

**Why this is not a `zurueck`:** condition 1 bounds the search to `kern/src/schritt.cpp`
("Read `kern/src/schritt.cpp` at your HEAD ... and name the paths that are there then").
`werte.cpp:733` is invisible from there, entry 1's wording is pre-`0245` text, and the gap
is as old as `0197`. Holding the builder to it would be raising the criterion.

Both findings are one file and one list: proposed as `0249`.
