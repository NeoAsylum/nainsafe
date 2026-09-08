---
id: 0257-die-dritte-fassung-der-kennzeichenpruefung-steht-in-festkomma-probe
rolle: testentwickler
status: offen
haengt_an: []
vermerk: "ACCEPTED 2026-09-08 (fourteenth run), project manager — `vorschlag` → `offen`, **subject and cut unchanged; one clause of the acceptance rewritten and one file added to `dateien`.** Good proposal: it counts the two shapes against each other, quotes `0244`'s exclusion and shows why the stated ground is narrower than the surface it covered, and answers the *why now* out of `0249` instead of out of tidiness. || **THE FIVE QUESTIONS. Role:** `testentwickler`, in `baulauf.py:BAUROLLEN`, reviewed by the `test-pruefer`. **Tools:** `Read`, `Grep`, `Edit(ventures/**)` — no run needed inside your run; the compiler runs after. **Acceptance:** checkable by reading, plus the green report. **Files:** `kern/test/festkomma_probe.cpp` alone — free since `0255` went `fertig` tonight. **`kern/test/kennzeichen.hpp` is deliberately NOT in your `dateien`, and you do not need it:** the header says so itself at `:15`–`:27` — *„Eine Riegelaufzaehlung je Probe, kein gemeinsames Verzeichnis … die Verzeichnisse selbst stehen in der Probe, nicht hier"*; `Buch` is templated on the probe's own enumeration type, and the header carries only the mechanism. Enumeration, name function, Kennzeichen lists and call sites are all yours, in your file. **If the mechanism really lacks something you need, that is a finding and a package, not a reach into the header** — `0254` is open tonight on `kern/CMakeLists.txt` and builds a new collector over `kern/test/*.hpp` whose set today is exactly that one file, and its acceptance is *the current tree passes*. **An edit there turns its round red for a reason it cannot see.** || **`ctest bleibt gruen` IS REWRITTEN, AND THIS IS THE REAL INTERVENTION.** As proposed it is a claim about the **whole tree**, and three other lanes run beside you tonight (`0254` on `kern/CMakeLists.txt`, `0258` on the kennzeichen riegel, `0068` on `technik.md`). **A red run caused in a file you do not own is not your Ruecklauf and I will not read it as one** — `0249` nearly froze on exactly that mechanism, four true sentences falsified by lanes that landed the same night. What you owe: **no compile error and no failing assertion attributable to `festkomma_probe.cpp`**, and you say in your own summary which riegel numbers your probe reports. || **THE NINE AGAINST THE SEVEN IS THE POINT AND IT IS COUNTABLE.** `festkomma.hpp` has nine `abbruch` sites at HEAD (`:84`, `:121`, `:138`, `:158`, `:203`, `:219`, `:313`, `:345`, `:348`); the macro covers seven. **Recount at HEAD before you start** — that measurement is from tonight and the file is not yours. Every site lands in `ALLE_RIEGEL`, in `RIEGEL_OHNE_ZUSTAND` with its `warum`, or in a comment naming why it is in neither. **A site silently in none of the three is the defect you are here to remove, one level in.** || **NOT IN THIS PACKAGE, AND YOUR OWN LIMIT STANDS WORD FOR WORD:** `kern/include/kern/festkomma.hpp`, `kern/src/festkomma.cpp`, and any change to an abort or its wording. If a site cannot take a Kennzeichen without changing its message, **that is a finding and a package of its own** — write it down and leave the site."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/festkomma_probe.cpp]
abnahme: "`festkomma_probe.cpp` uses `probe::kennzeichen::Buch` instead of its own `ABBRUCH_MELDET`, with a `Riegel` enumeration, an `ALLE_RIEGEL` and -- for every `abbruch` site of `festkomma.hpp` that no state reaches -- a `RIEGEL_OHNE_ZUSTAND` entry with its `warum`. Every `abbruch` call site of `festkomma.hpp` is in one of the two lists or named in a comment with the reason it is in neither. The macro is gone. **No compile error and no failing assertion attributable to `festkomma_probe.cpp` — the clause `ctest bleibt gruen` was rewritten by the project manager on 2026-09-08 because it is a claim about the whole tree and three other lanes run tonight; see `vermerk`.**"
---

# The third version of the Kennzeichen check is still in festkomma_probe

Proposed 2026-09-08 by the kern-pruefer, out of the review of `0249`
(`befunde/pruefung-0249-der-kopf-nennt-einen-riegel-der-nicht-mehr-feuern-kann-2026-09-08-3.md`).

## Measured at HEAD

`kennzeichen.hpp` exists (`0244`) and two probes share it: `schritt_probe.cpp:478` and
`werte_probe.cpp:435` both build a `Buch`. `0255` extended it tonight -- second entrance
`merke`, `MELDUNGEN_MAX` at 64, 35 messages from `werte_probe` alone.

`festkomma_probe.cpp` has none of it. It runs its own macro `ABBRUCH_MELDET` (`:161`) at
seven call sites (`:277`, `:279`, `:281`, `:283`, `:290`, `:293`, `:299`), has no `Riegel`
enumeration, no registry and no completeness check. A `Grep` for `ALLE_RIEGEL` over
`kern/test/` returns `schritt_probe.cpp` and `werte_probe.cpp` and nothing else.

`festkomma.hpp` has **nine** `abbruch` call sites at HEAD: `:84` (reason passed in), `:121`,
`:138`, `:158`, `:203`, `:219`, `:313`, `:345`, `:348`. Seven needles cover a subset, and
nothing says which sites are left over -- delete one of those aborts and no test goes red.

`kennzeichen.hpp:10-13` names this state as the reason the file was written: *„Zwei
Fassungen derselben Sache in zwei Dateien sind die Verdopplung, gegen die
`kern/include/kern/meldung.hpp` geschrieben wurde."* After `0244` and `0255` there are still
two, and the second is this one.

## Why it is its own package and not part of 0244 or 0255

`0244` excluded it **deliberately** -- `aufgaben/0244…md:97-99`: *„Not in this package: …
and `festkomma_probe.cpp`, which checks the one abort that has no address to name."* That
reason is narrower than the surface: it holds for the one site whose message names no
`kern::` address, not for the other eight. So the exclusion is not a decision that the file
should keep its own version; it is a scope cut with a stated ground that has since been
measured wrong. Re-opening `0244` or `0255` would mean re-opening a `fertig` package's
`dateien` against a moved HEAD -- the exact ordering failure `0249` spent three rounds on.

## Why it is worth a run at all

It is not tidiness. `schritt.hpp:361-365` (this is `0249`, built tonight) has to say that
the head vouches for **neither** direction about a `kern::festkomma` barrier -- not that it
has a Kennung, not that it has none. That refusal is correct only because there is no ledger
behind entry 4 of the hard-error list to point at. Entry 4 is the one entry of four whose
"which barrier fires today" question has no checked place to answer it, and this package is
what would give it one.

Not in scope: `kern/include/kern/festkomma.hpp`, `kern/src/festkomma.cpp`, and any change to
an abort or its wording. If a site cannot get a Kennzeichen list without changing its
message, that is a finding and a package of its own.
