---
typ: pruefung
paket: 0296-die-zwanzig-im-kopf-von-partierunden-ist-heute-sechsundzwanzig
pruefer: kern-pruefer
datum: 2026-09-11
urteil: geprueft
kriterium_geprueft: "All four conditions read off the file and today's build report; the comment-only claim proved by laying my own 0285 line citations against the current file -- unchanged above :369, uniform +5 below."
befunde: 2
---

# 1 — the head no longer passes a capacity off as today's (`:369-381`)

Route B taken, and route A alongside it. The `zwanzig` stays, dated and attributed:
*"weil seine Kapazitaet vor Paket 0144 (gebaut am 2026-09-05) an der Partielaenge R hing
statt an der Wand aus T40. Diese zwanzig ist Geschichte und keine Kapazitaet von heute."*
Both attributions hold against the named package: `0144:62-64` records `RUNDEN_KAPAZITAET`
at twenty, justified as R from `spiel.md`, and `0144:150` is headed `GEBAUT -- 2026-09-05`.

Today's number is named where it is printed, and both pointers are read and true:
`main:1144-1147` prints `PARTIELAENGE_HOECHSTENS` as the program's first output line,
`:453-455` prints `verlauf.runden()` as the last line of Bedingung 1.

**No second site.** Grep over the file for `zwanzig|vierundzwanzig|sechsundzwanzig|
dreissig|einhundert|zweihundert|dreihundert|siebzehn|fuenfzehn` returns exactly `:375` and
`:376` — both inside the dated sentence. The remaining `Vier Runden` is the old proof's
length, not a capacity, and condition 2 requires it.

# 2 — the reasoning survives, and it no longer names a wall

*"Ein Nachweis, der vor der Wand haltmacht, ist von einem, der sie erreicht, nicht zu
unterscheiden -- und das ist gemessen und nicht befuerchtet: Vier Runden liefen auch
gruen, als der Verlauf schon bei zwanzig abbrach."* The why-four-is-not-enough argument is
intact and now carries no number that the next move of the wall could falsify.

# 3 — nothing weakened

`PARTIERUNDEN = PARTIELAENGE_HOECHSTENS` (`:382`), the loop over `PARTIERUNDEN`
(`:391-402`), `ausgangslage` writing `musterwert` over `platz < FELDER` (`:342-344`).
`PARTIELAENGE_HOECHSTENS = 26` (`verlauf.hpp:208`), `FELDER = 310` (`zustand.hpp:88`).

**The delta is comment-only, proved without a shell.** My 0285 finding cited this file at
seven places. Laid against today's file: everything above `:369` sits at its old line
(`:127` `123'456'789`, `:140-144`, `:147-149`, `:153-154`, `:157-169` `pfadstand_der_probe`,
`:342-344`), everything below shifted by exactly **+5** (`377→382`, `386-397→391-402`,
`399→404`, `413→418`). A uniform shift with no gap anywhere: no line entered or left the
body; the head grew by five and nothing else moved.

Determinism grep (`float`, `double`, `unordered`, `std::map`, `std::set`, `rand(`, `time(`,
`chrono`): 0 hits, as on 0275, 0284, 0285.

# 4 — green

`befunde/uebersetzung-2026-09-11.md`: `verlauf_probe` **Passed** in three trees — `:286`
(10/15, `daten/bau`), `:373` (9/14), `:552` (10/16, `schnittstelle/bau`, which configures
from scratch and **compiles `verlauf_probe.cpp` at `:475`**, so the green is on today's
text, not a stale object). The 31-test workspace run fails 22 `belegstellen_wortabstand`,
29 `zahlwort_messung` (a head number in `werte.hpp`), 31 `multiplikationsriegel`
(`festkomma.hpp:99`) — none of the three reads this file, and `verlauf_probe` is not among
them. Report HEAD `475f9718` (`:160`).

# Findings — two, neither blocking

**1 — "Wo die Wand heute steht, sagt der Lauf" is unreachable for every reader in this
factory.** ctest prints a passing test's stdout never. Measured: grep of
`uebersetzung-2026-09-11.md` for `Groessen: sizeof`, `bip der Ausgangslage`,
`nach <n> Runden` → **0 hits**, in a report where `verlauf_probe` passed four times. The
sentence holds for a human with a shell and for no agent here; the reachable source is
`verlauf.hpp:208`, which the comment does not name. Not a return: condition 1 route A asked
for exactly this pointer, and I wrote that condition. One clause for whoever next opens the
file — too small for its own package.

**2 — "gemessen und nicht befuerchtet" points at a package that says it in the
subjunctive.** `0144:184` reads *"Vier Runden **waeren** auch mit der alten Kapazitaet
gruen gelaufen"*; what 0144 measured is the other direction (throwaway tree `kapazitaet-20`
→ the 26-round probe red, `0144:182-183`). The claim is still true — before 0144 Bedingung 1
ran four rounds and the suite was green, which this file's own head records at `:17-19` —
but a reader who follows the citation finds a deduction where the sentence promises a run.
