---
typ: pruefung
paket: 0237-der-nenner-der-zustimmungsregel
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "All three acceptance conditions read against the delivered code and recomputed by hand; that the new barrier actually fired at runtime is proven by the completeness half of probe_kennzeichen_eindeutig, not assumed from a green tree."
befunde: 1
---

# geprueft

## Condition 1 — the guard, and it is the precedent's guard

`schritt.cpp:625-645`. `realeinkommenshub` reads `werte::bip(rundengrenze, land)` first, then
`if (inlandsprodukt < 1)` aborts — **before** `politiklast` and before `mal_geteilt`. Same
shape as the precedent it was told to take: `werte.cpp:602` is `if (wechselkurs < 1)`. On
i64, `< 1` is exactly the negation of `spiel.md:2409` „bip(l) > 0 is the denominator
condition". No substitute value, no continuing branch (T6).

The message names the rule, the condition in the spec's words, the address
(`Meldung::adresse`) and the number; the reason is the quoted precedent sentence and no
second one. I counted it: **399 characters against `MELDUNG_ZEICHEN_MAX = 511`**
(`meldung.hpp:74-77`) — no truncation, so the country name at its tail arrives. That
mattered: the Kennzeichen sit in the first 74 characters and would have stayed green over a
cut tail.

## Condition 2 — the state, recomputed from the two constants

`startwert(platz, Wertschoepfung::Positiv)` (probe:609-615) writes `1'000'000 + platz` on
the twelve value-added addresses. Every state in the file goes through it — the only call
sites are 655, 673, 1032, 1048, 1049. Bases 0/44/88/132, `Wertschoepfung` at +0/+4/+8:

| | before | after |
|---|---|---|
| US | -10.000 | 3.000.012 |
| CN | -20.000 | 3.000.144 |
| DE | -10.000 | 3.000.276 |
| BR | -20.000 | 3.000.408 |

The left column is the state 0197 was accepted on. The right is positive and pairwise
distinct, so a swapped country block still shows. `bip_der_lage` prints all four and pairs
`LAENDER_DER_PROBE[n]` with `WERTSCHOEPFUNGSPLAETZE[n*SEKTOREN]` — country-major, correct.

## Condition 3 — both sides, and the abort demonstrably fired

Positive side probe:1424-1432 (`== LAENDER`, round runs to 14), negative side
probe:1435-1447 with Kennzeichen `{"kern::schritt", "bip(l) > 0 ist die Nennerbedingung"}`.

Not taken on trust: `Riegel::Nennerbedingung` is in `ALLE_RIEGEL` (probe:321-328,
`static_assert` against `Riegel::Anzahl`), and `probe_kennzeichen_eindeutig` goes red if no
message for a Riegel arrived (1719-1731) or if a list matches a foreign message
(1765-1774). `schritt_probe` passes in both trees — so the abort ran, with that wording,
and the wording separates it from the other six barriers.

Not hollow either: without the guard, `mal_geteilt(0, 10.000, -10.000)` returns 0, nothing
throws, and side 2 goes red with „kein Abbruch".

**The tree is green again.** `uebersetzung-2026-09-08.md` is now `ergebnis: ok` — 26/26,
13/13, 3/3, 5/5, 1/1, 1/1, 3/3, every manifest at its ceiling; the `verlauf_probe` red from
`vermerk_fuer_den_pruefer` is gone. `kern` and `schritt_probe` show „Built target" without a
recompile in that run, i.e. the sources I read are the ones the objects came from.

**The limit, and it is the accepted alternative, not a gap.** No probe here exercises the
division with a non-zero numerator: `politiklast` skips at `richtung == 0`, step 3 carries
forward, `zustimmung_elastizitaet` is 0. What is measured is the barrier; the sign of the
division it protects waits for a computing step 3. probe:1392-1399 says so.

## Finding 1 — the same start state has a second landmine, in the multiplying half

Not this package's doing and no criterion failure. Computed here because whoever makes step
3 compute hits it before he measures anything.

`werte::schaden` for `Instrument::Leitzins` is `mal_geteilt(schuld(z,l), hub(...), 10.000)`
(`werte.cpp:978`), and `schuld` is `mal_geteilt(bip(l), staatsschuld(l), 10.000)`
(`werte.cpp:707`). `Staatsschuld` is aggregate 7, address `land_basis + 12 + 7`: CN → 63,
BR → 151, both `% 8 == 7`, i.e. `muster[7] = I64_MIN`. With `bip(CN) = 3.000.144` the
product is ≈ `-2,8·10^21` and `nach_i64` aborts. It aborted before this package too
(`-20.000 · I64_MIN / 10.000 ≈ 1,8·10^19 > I64_MAX`), so no regression — but the first
probe that moves a Leitzins in CN or BR dies in `schuld`, one call short of `schaden`.

No package for it: the branch is dead today, and a package for a dormant overflow would
take a lane from live work. Written down so the next builder finds it before the compiler.

## Where I looked and found nothing

- Floating point, unordered iteration, a second random stream, time or addresses reaching
  the state update, in both changed files: none. `1'000'000 + platz` is deterministic.
- A path still building a state from `musterwert` directly: none (5 call sites, all via
  `startwert`).
- My open lead from the 0197 review — `probe_zustimmung_klemmt_statt_vortrag` starting at
  `I64_MAX` and dying in `festkomma::plus`. It does not: `hub` is 0, `plus(I64_MAX, 0)`
  does not overflow, the value clamps to 10.000 (probe:1329-1360). Lead closed.
- A guard too broad to discriminate: side 1 of the new probe exists for that and runs
  through.
