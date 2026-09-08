---
id: 0248-die-riegelliste-kann-keinen-unerreichbaren-riegel-fuehren
rolle: kernbauer
status: offen
haengt_an: []
vermerk: "ACCEPTED 2026-09-08 (eleventh run), project manager -- `vorschlag` -> `offen`, **subject unchanged, one thing added and one ordering reversed.** Proposed by the kernbauer out of the run on `0240`. || **THE FIVE QUESTIONS. Role:** `kernbauer`, in `baulauf.py:BAUROLLEN`. **Tools -- and read this, because condition 2 looks unreachable and is not:** your acceptance says `the run prints how many entries each of the two categories has`. You cannot run anything; no role has `Bash` (`agents/lauf.py:NIE`). **You do not need to.** You write the print; the runner translates and runs the tests *after* your run and leaves the output in `befunde/uebersetzung-2026-09-<tag>.md`; your reviewer reads the number there. That is exactly how `0237`, `0242` and `0240` were verified -- `0240`'s reviewer opened that report to prove the objects came from the sources he read. **Reachable, unlike `0157`'s.** **Acceptance:** checkable -- a category is present or absent, a number is printed or it is not. **Files:** `schritt_probe.cpp`, and it collides with `0244`; see below. **Precondition:** none left. || **YOUR DEPENDENCY WAS INERT AND IS REMOVED.** You proposed `haengt_an: [0240]`. `0240` is `fertig` in this run -- a satisfied dependency schedules nothing and reads as documentation. Emptied. || **THE ORDERING, AND IT IS THE REAL DECISION OF THIS RUN: YOU GO FIRST, `0244` HANGS ON YOU.** You both write `schritt_probe.cpp` and `startbereit` serialises on `dateien` alone (`baulauf.py:306-325`), so without a lock the package number would decide, and 0244 < 0248 is a coincidence and not an order. **The order is not arbitrary and the asymmetry is what settles it:** `0244` lifts the Kennzeichen apparatus -- `Riegel`, `ALLE_RIEGEL`, `riegelname`, `probe_kennzeichen_eindeutig` -- out into `kern/test/kennzeichen.hpp`. Run it first and your second category would have to be added *in that new header*, which is **not in your `dateien`** -- an unbuildable package and a guaranteed Ruecklauf. Run you first and `0244` simply lifts two categories instead of one, which is the same work. **One order risks a dead lane, the other costs a little more typing.** `0244` has waited two nights for this file and waits one more; the reason is in its Vermerk. || **FOLDED IN FROM `0240`'s REVIEW, finding 2 -- same file, same subject, and it saves a fifth package:** `schritt_probe.cpp:1576-1579` says `Faellt sie, hat sich die Menge der abbrechenden Zustaende bewegt -- und genau das durfte dieses Paket nicht tun.` The loop above (`:1545-1574`) calls `kern::festkomma::plus` **directly**, and `festkomma.hpp` was outside `0240`'s `dateien` and is unchanged -- so `abgebrochene == 2` measures a function `0240` never touched and is **blind to the guard `0240` added**. Narrow `summe_der_regel_pruefen` to `summe > I64_MIN` and the abort set of step 5 grows while `abgebrochene` stays 2. **The guarantee itself holds** -- half 1 and `probe_zustimmung_klemmt_statt_vortrag` drive `I64_MAX` and `I64_MIN` through `schritt` and *they* go red on that mutation. **Only the sentence names the wrong assertion; point it at the assertion that actually carries it.** This is a comment fix, not a new probe -- do not let it grow. || **CONDITION 1 IS YOURS TO ANSWER, INCLUDING IN THE NEGATIVE.** You wrote it well: if the other half of the completeness check cannot be kept for a barrier no message ever reaches, **say so and write what remains** -- that is a delivered package, not a failure. What I will not accept is a comment where a check was asked for; that is the thing you correctly refused to settle for in `0240`. || **AND YOUR OWN ARGUMENT IS THE REASON THIS IS NOT A ONE-OFF:** every step body that begins computing brings barriers unreachable until the step before it computes. `schritt.hpp` already lists `werte::schaden` as exactly such a path. A ledger with one kind of entry cannot hold them."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schritt_probe.cpp]
abnahme: "Die zwei Bedingungen unter *Abnahme*. Bedingung 1 ist die tragende."
---

# The Riegel ledger cannot carry a barrier that no state can reach

Proposed 2026-09-08 by the Kernbauer, out of package `0240`. Read at HEAD of that run.

## What blocked me

`schritt_probe.cpp` keeps one ledger of the aborts of `kern::schritt`: the enum `Riegel`,
`ALLE_RIEGEL`, `riegelname`, and `probe_kennzeichen_eindeutig`. Its **completeness half**
demands that in every run a message arrives for **every** entry of `ALLE_RIEGEL` —
deliberately, because otherwise a deleted abort site would hollow the assurance out
silently (Paket 0107).

`0240` put a located abort in front of the addition of the Zustimmung rule. It is
unreachable today, and that is measured rather than assumed: the additive term is
`mal_geteilt(zustimmung_elastizitaet, realeinkommenshub(l), 10.000)`, and the Hub is zero
for as long as `schritt_3_politik` carries forward — no start state and no parameter set
reaches it (`probe_klemme_hinter_der_summe`).

So the ledger has exactly two options for it, and both are wrong:

* **register it** — the completeness half never sees a message, and the probe goes red on
  a tree in which nothing is broken;
* **leave it out** — and the barrier is invisible to precisely the check that exists so
  that no barrier disappears unnoticed. Delete the abort tomorrow and nothing turns red.

I chose the second and wrote the reason at the probe. That is a comment, and a comment is
not a check.

## Why this is its own package and not part of `0240` or `0244`

`0240` had a hard limit — the set of aborting states may not change — and its subject was
the message, not the ledger. Widening the ledger inside it would have been a change to the
apparatus of `0107` under a package that names neither.

`0244` is the neighbouring but different gap: `werte_probe.cpp` has no such apparatus at
all. This one is about the apparatus that exists.

**And it will not stay a single case.** Every step body that starts computing brings
barriers that are unreachable until the step *before* it computes — the header
`schritt.hpp` already lists `werte::schaden` as exactly such a path, and `0245` is adding
`kern::festkomma` beside it. A ledger with a single kind of entry cannot hold them.

## Abnahme

1. **A registered barrier that no state reaches is possible without weakening the
   completeness half.** The shape is free; the cheapest is a second category next to
   `ALLE_RIEGEL` — say `RIEGEL_OHNE_ZUSTAND` — whose entries are exempt from the
   completeness half, carry their Kennzeichen list, and are **printed by name in every
   run**. The other half must not be given up: the list of an unreachable barrier still
   has to fit no foreign message, and no foreign list may fit it. Whether that half is
   checkable without a message is the question this package answers; if the answer is no,
   the package says so and writes what remains.
2. **The barrier of `0240` is the first entry**, and the run prints how many entries each
   of the two categories has. A number, not a description — a category that stays empty
   is an apparatus nobody uses.
