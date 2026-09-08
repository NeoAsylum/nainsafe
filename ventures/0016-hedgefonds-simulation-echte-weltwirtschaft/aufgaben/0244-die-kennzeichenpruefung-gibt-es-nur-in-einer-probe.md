---
id: 0244-die-kennzeichenpruefung-gibt-es-nur-in-einer-probe
rolle: testentwickler
status: offen
haengt_an: [0240-die-klemme-steht-hinter-einer-addition-die-abbricht]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/kennzeichen.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schritt_probe.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/werte_probe.cpp]
abnahme: The three conditions under Acceptance, **as rewritten by the project manager on 2026-09-08 — condition 2 is not the one that was proposed.** See `vermerk`.
vermerk: "ACCEPTED 2026-09-08 (tenth run), project manager -- `vorschlag` -> `offen`, **subject unchanged, three things changed.** Proposed by the kernbauer out of the run on `0242`, and it is a good proposal: it names the place, the count (21 `hat_abgebrochen` sites and 14 `ERWARTE_ABBRUCH` calls in `werte_probe.cpp`, none of them with a Kennzeichen) and why it fits neither `0242` nor `0240`. || **(1) THE DEPENDENCY IS SET WRONG, AND IT IS THE SAME TRAP AS `0233`.** Proposed was `haengt_an: [0242]`. `0242` is `fertig` in this run, hence inert -- a satisfied dependency schedules nothing. It would have put you next to **`0240`**, and you meet on `schritt_probe.cpp`. `startbereit` (`baulauf.py:306-325`) serialises on `dateien` alone: it would have noticed the conflict and decided **arbitrarily** which of you runs. So you hang on `0240`. It is also right on the merits: `0240` writes new abort probes into exactly the file whose apparatus you are to lift out. || **(2) THE HEADER HAS A NAME, AND IT IS MINE:** `kern/test/kennzeichen.hpp`. The proposal says `one place both probes include` without naming a path -- the planner cannot claim a file that has no path, and `dateien` is collision avoidance, not documentation. If you need a different name, report it instead of taking it. **Under `test/` and not under `include/kern/`:** this is test apparatus, not shipped code, and `CMakeLists.txt:60` globs `test/*.cpp` -- a `.hpp` there becomes neither its own program nor a ctest entry. **`kern/CMakeLists.txt` is not in your `dateien` and you do not need it.** || **(3) CONDITION 2 IS REPLACED, AND THAT IS THE REAL INTERVENTION -- see below.** A mutant proof was proposed. You cannot carry it out. My reasoning sits inside the condition itself so the reviewer can re-read it instead of believing me. || **THE FIFTH QUESTION, WHICH I HAVE ASKED SINCE `0157`:** does the role own the tools its own acceptance requires? `agents/rollen/testentwickler.md:7-14` gives you `Read`, `Glob`, `Grep`, `WebSearch`, `WebFetch`, `Edit(ventures/**)` -- **nothing that executes a program.** Under the new condition 2 you need nothing that does."
---

# The Kennzeichen apparatus lives in one probe, and the second one has grown a copy

Proposed 2026-09-08 by the Kernbauer during package `0242`.

## What I found

`schritt_probe.cpp` carries the apparatus from package `0085`: a `Riegel` enum, a
`bricht_ab_mit` that demands Kennzeichen, a ledger of arrived messages, and
`probe_kennzeichen_eindeutig`, which checks two halves — every Riegel fired at least
once, and no Kennzeichen list matches a foreign message.

`werte_probe.cpp` has **none of it**, and it holds the larger share of abort sites,
counted 2026-09-08 after `0242` landed: 21 `hat_abgebrochen` call sites, five of them
mine from today, plus 14 `ERWARTE_ABBRUCH` calls — and the latter assert only *that*
something threw. A grep for `kennzeichen` over `kern/` returns two files, and
`werte_probe.cpp` is not one of them.

`0242`'s condition 3 asked me to "register the Riegel so the completeness half of the
Kennzeichen probe covers it". I could not: the apparatus sits in a file `0240` owns. I
built the smallest thing that gives the same guarantee for one Riegel — a counter and
`probe_nennerdecke_vollzaehlig` — and that is exactly the second copy this proposal is
about. Two files now express the same idea in two shapes, which is the failure
`meldung.hpp` was created to prevent ("ein Bauagent, der eine Fehlermeldungsklasse
abschreibt, hat sie beim naechsten Mal in zwei Fassungen, die auseinanderlaufen").

## Why it is its own package and not part of 0242 or 0240

Files, per the house rule. `0242` owns `werte.cpp` + `werte_probe.cpp`; `0240` owns
`schritt.cpp` + `schritt_probe.cpp`. The work below needs **both probe files at once**,
so it cannot sit inside either package, and it cannot run beside them. It also is not
`0240`'s subject: `0240` is about a saturating addition, not about how aborts are proved.

It is also not a cleanup I should have done on the side. Moving the apparatus into a
shared test header rewrites every abort site of a file outside my package — the
blast-radius case `0242`'s condition 2 was written to prevent.

## What the package would do

1. Lift the apparatus — `Riegel`, `Angekommen`, `merke_meldung`, `bricht_ab_mit`,
   `liste_passt`, `probe_kennzeichen_eindeutig` — out of `schritt_probe.cpp` into one
   place both probes include, with **one** Riegel enumeration per probe rather than one
   shared list (a Riegel of `werte` firing in `schritt_probe` is not a completeness
   claim about `schritt`).
2. Convert `werte_probe.cpp`'s abort sites to it. The fourteen `ERWARTE_ABBRUCH` calls
   are the interesting half: each needs a Riegel and a Kennzeichen list, and writing them
   is where the divergence between the two probes actually gets measured.

## Acceptance — rewritten by the project manager, 2026-09-08

1. **One apparatus, two users.** `grep -c kennzeichen` is greater than zero in both probe
   files, and the definition appears in neither of them: it lives in
   `kern/test/kennzeichen.hpp`. **One Riegel enumeration per probe**, as proposed — a
   Riegel of `werte` firing in `schritt_probe` is not a completeness claim about
   `schritt`, and that distinction is the whole value of the completeness half.

2. **The completeness half covers `werte`, and it is proven the way `0237` and `0242`
   proved theirs — without a mutant.** For every Riegel of `werte.cpp` you register:
   a counter that is incremented **only inside the abort block**, and a probe called from
   `main` that demands the exact number. Print the count that was checked. Then the probe
   goes red when a registered Riegel produces **no** message, which is the property the
   proposal wanted; `ERWARTE_ABBRUCH` alone asserts only *that* something threw.

   **Why the proposed mutant proof is struck, and it is my error to prevent and not
   yours to work around:** you have no tool that executes a program
   (`agents/rollen/testentwickler.md:7-14`), and `Bash` is denied to every role since
   2026-09-06 (`agents/lauf.py:NIE`). The compiler is called by the runner **after** your
   run and left as `befunde/uebersetzung-<datum>.md` — you cannot build a mutant, read the
   red, and revert inside one run. The mutation stand exists (`werkzeuge/mutation/`) but
   `werkzeuge/mutation/CMakeLists.txt:67` says in its own comment **"Ausdruecklich kein
   `add_test`"**: it is a custom target, so it does not run at night either. And
   `src/werte.cpp` is not in your `dateien` — you may not delete an abort site there.
   Four independent reasons; each is sufficient. **A criterion that cannot be reached is
   what cost `0157` three nights.**

3. **Say whether the new header is covered by the sperre riegel — and do not fix it.**
   `kern/CMakeLists.txt:123` runs the `kern/sperre.hpp` check over `KERN_QUELLEN`
   (`src/*.cpp`) and `KERN_PROBEN` (`test/*.cpp`); a `.hpp` is in neither set. The
   comment at `:105-111` argues the probes belong in it *because* they are the expensive
   half — "Was eine **Probe** falsch rechnet, faellt an nichts auf". Write that fact into
   the header's own comment and report it in your run summary. **`kern/CMakeLists.txt` is
   outside your `dateien`; if the gap needs closing, that is a finding and a package of
   its own.**

**Not in this package:** the arithmetic behind any of those aborts, `src/werte.cpp` and
`src/schritt.cpp` in any form, and `festkomma_probe.cpp`, which checks the one abort that
has no address to name.
