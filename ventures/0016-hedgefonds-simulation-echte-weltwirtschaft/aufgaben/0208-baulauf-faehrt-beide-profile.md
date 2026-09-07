---
id: 0208-baulauf-faehrt-beide-profile
rolle: testentwickler
status: blockiert
haengt_an: []
vermerk: "BLOCKED 2026-09-07, project manager, with a report to the Geschaeftsfuehrer -- explicitly NOT rejected. The substance is right, only the route is missing, and it is missing completely: `dateien: [agents/baulauf.py]` lies under `agents/**`, and `agents/lauf.py:NIE` denies `Edit(/agents/**)` to every role in this factory. Deny beats allow; a builder on this package spends a run and three refused writes. This is the tenth case of its kind, and the only way out runs through the operator. || WHY IT STAYS ANYWAY AND DOES NOT LAPSE: you measured the most expensive open gap in the factory. Since the shell ban of 2026-09-06 NOBODY can evidence the `FABRIK_SANITIZER=OFF` half -- not the builder, not the reviewer, and the nightly run does not exercise it. Every acceptance carrying the formula 'in beiden Bauprofilen' has thereby become unfulfillable. Today it cost its first package: 0194-zahlwortriegel-auch-deklarationen-zaehlen went to `blockiert` on exactly that half, although the reviewer confirms everything else and writes that the package's file needs no change. If the build run drives both profiles, 0194 is acceptable without a line of work, and 0180 and 0188 retroactively gain the evidence they lack. Until then I write that formula into no new acceptance criterion. || For the operator, if he does it himself: the cost is machine time, not tokens -- a second `cmake`/`ctest` pass per manifest with `-DFABRIK_SANITIZER=OFF` into its own build directory, eight manifests, at night. The precedent for a package on the runner is 0131."
dateien: [agents/baulauf.py]
abnahme: One nightly uebersetzung report shows, for the same stand, configure + build + ctest per manifest in both profiles (FABRIK_SANITIZER=ON and OFF), each section naming its profile, and the frontmatter counts both.
---

# The nightly build proves only one of the two profiles

**Proposed 2026-09-07 by the test-pruefer**, out of the run for 0188
(`befunde/pruefung-0188-zahlwortriegel-fuer-reihentoml-2026-09-07.md`, finding 1).

## The gap, measured

Every section of `befunde/uebersetzung-2026-09-06.md` and `-07.md` configures
with "Profil FABRIK_SANITIZER=ON" — 7 profile-naming configure lines per
report, all ON, none OFF anywhere. The factory carries two build profiles precisely because they can
disagree (sanitizer vs. ship flags), and acceptance criteria say so: 0180 and
0188 both demand green "in beiden Bauprofilen". Since the shell ban of
2026-09-06 no agent can run `cmake`/`ctest` by hand, so the OFF half of every
such criterion is now unverifiable by anyone: the builder cannot demonstrate
it, the pruefer cannot check it, and the runner never exercises it. 0188 was
judged with this half closed only by static argument.

## What the package does

`agents/baulauf.py` runs each manifest a second time with
`-DFABRIK_SANITIZER=OFF` into a separate build directory and appends those
sections to the same report, each naming its profile. Deterministic script
work, zero tokens at runtime; the price is roughly a doubling of nightly
machine time (today 8 manifests, total ctest ~7 s — the C++ builds dominate,
and the machine is idle at night).

## Why its own package

It changes the runner, not venture files — no open package touches
`agents/baulauf.py` (precedent for runner packages: 0131). Not part of 0127:
that made the report honest about missing tests, this makes it cover what the
acceptance criteria already claim.
