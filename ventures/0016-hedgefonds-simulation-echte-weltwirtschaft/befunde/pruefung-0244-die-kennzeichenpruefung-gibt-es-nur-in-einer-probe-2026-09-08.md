---
typ: pruefung
paket: 0244-die-kennzeichenpruefung-gibt-es-nur-in-einer-probe
pruefer: test-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: All three conditions re-derived from the files and the runner's build report; call sites and expected counts recounted independently.
befunde: 0
---

# Pruefung 0244 — geprueft

Basis: the three `dateien`, `kern/CMakeLists.txt`, `src/werte.cpp` abort sites, and
`befunde/uebersetzung-2026-09-08.md` (ergebnis ok, 26/26 tests pass, `werte_probe` and
`schritt_probe` among them). The builder's logbook was not read.

## Condition 1 — one apparatus, two users: met

`grep kennzeichen` hits in both probe files; the definition (`Buch`, `bricht_ab_mit`,
`merke_meldung`, `liste_passt`, `auswerten`, `Angekommen`, `OhneZustand`) exists only in
`kern/test/kennzeichen.hpp` — greps for those names hit neither probe. Both instantiate it
(`schritt_probe.cpp:478`, `werte_probe.cpp:287`). One Riegel enumeration per probe: own
`enum class Riegel`, 7 entries each (`schritt_probe.cpp:341`, `werte_probe.cpp:136`), own
`RiegelOhneZustand`; `Buch` is templated over both, the tables stay in the probes.

## Condition 2 — completeness with exact counts: met

The counter is the ledger, written **only** inside the catch block of `bricht_ab_mit`
(`kennzeichen.hpp:235-244`). `probe_riegel_vollzaehlig` (`werte_probe.cpp:2070`) demands
`gezaehlt == soll.meldungen` per riegel and prints both numbers; `main` calls it after every
abort site (`:2135`); `pruefe` increments `fehlgeschlagen` (`:105`), `main` returns 1 on it
(`:2138`). Recounted independently: 14 `BRICHT_AB_MIT` sites, per riegel 6/1/2/1/1/1/2,
equal to `SOLLZAHLEN` (`:260`); `static_assert`s pin size and order. Zero `ERWARTE_ABBRUCH`
left in the file.

Red-when-broken, traced in code: a deleted site fails the exact count; a silent registered
riegel fails `bricht_ab_mit` ("kein Abbruch") and the completeness half of `auswerten`; a
generic kennzeichen list fails the foreign-match half; degeneration to zero compared pairs
is caught by `verlange(fremde_paare > 0, ...)` (`kennzeichen.hpp:439-441`).

Scope as applied: the seven registered riegel are the barriers the fourteen converted sites
reach (three in `werte.cpp`, two in `festkomma`, two in `zustand`). `src/werte.cpp` holds
further abort sites reached only via the 21 `hat_abgebrochen` calls; they are in no ledger.
I read condition 2 by its own purpose sentence ("the property the proposal wanted" — the
proposal's step 2 names the fourteen `ERWARTE_ABBRUCH` calls), not as "every abort site of
`werte.cpp`". The residual is stated at the enum (`werte_probe.cpp:130-135`) and is proposal
`0255` (exists, `status: vorschlag`). If the project manager meant the stricter reading,
`0255` is exactly the difference — his call, not a defect of this build.

The builder's three declared uncertainties (hand-derived barrier attribution, argument
evaluation order at `anleihewert`, buffer 16→32) are discharged by the green run: a wrong
barrier or count turns `werte_probe` red by construction. The buffer is a guard that still
fails loudly on overflow (`kennzeichen.hpp:488`), not a lowered assertion.

## Condition 3 — sperre gap named, not fixed: met

Re-verified in `kern/CMakeLists.txt`: globs `src/*.cpp` (`:51`) and `test/*.cpp` (`:60`),
riegel loop over exactly these two (`:123`); the third collector takes only
`include/kern/*.hpp` (`:52`). A header under `test/` is in none; the build log agrees
("10 Kernquelle(n) und 12 Probe(n) geprueft"). Fact, cost, and why the header cannot simply
bind the sperre stand in the header's head comment (`kennzeichen.hpp:51-76`).
`kern/CMakeLists.txt` untouched; the gap is proposal `0254` (exists, `dateien` names only
that file).

## Searched for and not found

Weakened checks: `probe_nennerdecke_vollzaehlig` still demands `== 2`; no threshold
lowered, no assertion removed, no test skipped. The `0251` prerequisite holds: both
`RIEGEL_OHNE_ZUSTAND` tables are findable (`schritt_probe.cpp:443`, `werte_probe.cpp:233`),
the entry type in the header.
