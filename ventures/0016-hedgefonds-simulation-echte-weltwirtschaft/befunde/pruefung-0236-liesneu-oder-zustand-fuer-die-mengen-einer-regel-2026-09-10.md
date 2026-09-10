---
typ: pruefung
paket: 0236-liesneu-oder-zustand-fuer-die-mengen-einer-regel
pruefer: entwurf-pruefer
datum: 2026-09-10
urteil: zurueck
kriterium_geprueft: T48's new answering sentence read against the callers the same package keeps (T33 point 2, section 22's reader table, T38/T45), and the `spiel.md` half of the `abnahme` re-quoted at HEAD
befunde: 1
---

# The sentence that answers the criterion is false for two of the four caller classes it itself names

**Where I looked.** T48 `technik.md:2415-2593`, T33 points 1–4 `:2228-2259`, section 36
`:6309-6431`, section 22 `:4860-4909` and `:4968`, T38/T39 `:1584-1644`, T45 `:1884`,
`spiel.md:2246-2306` and `:3506`, `kern/src/schritt.cpp`, `kern/include/kern/werte.hpp`.

## What holds — judge only the repair on the ruecklauf

- **The conflict is decided, not restated.** In-round quantities take the `Schreiber`, so
  `spiel.md:2270-2272` („**The reference of the change is therefore not the previous round
  but the same round without policy movement.** Everything is read with `lies_neu`; …",
  verbatim at HEAD) stays literally true and needs no deviation note. That is the
  reconcilability half of the `abnahme`, and it is met.
- **Every citation reproduces.** `schritt.cpp:566` is `schreiber.vortrag(platz)` in one
  line; the call-site comment `:588-597` is quoted word for word; `rundengrenze` goes to
  no. 22 at `:642` and to no. 9 at `:675`; the section's own check — `Grep "const Zustand&"`
  over `schritt.cpp` — gives exactly `:633, :672, :785, :909`. `spiel.md:3506` carries
  „T48 counts **22** … **25**" with the three names of report 3; section 22's twelve
  `werte_probe.cpp` call sites (`:4968`) and the 56 addresses (`:4845`) stand where section
  36 says. No package under `aufgaben/` builds the writer forms (grep `rundenschreiber`:
  only `0165`, the two-input form that *is* built), so report 1 holds.

## The finding — how to produce it

1. `technik.md:2566-2568`, new with this package: a `const Zustand&` argument of any T48
   quantity „is a state at a **round boundary**: a round that is finished and whose
   two-sided mask check of T38 has passed."
2. Same paragraph block, `:2583-2585`: „the `Zustand` forms are the route outside one —
   valuation on a finished state, the three-level output of G8, **the vintage build, the
   test bench**."
3. Section 22's reader table, `:4885`, test-bench row: „states built by hand, without a
   round". T38 (`:1619-1622`) is the writer's per-round two-sided mask check at round end;
   a hand-built state has passed none. `werte_probe.cpp` passes such states to nos. 9–11
   today.
4. T33 point 2 (`:2245`): the vintage build computes `marktkorb(start, start)` — no. 7,
   two `const Zustand&` (`werte.hpp:329`). The start state is written by the vintage build
   (`:1215`) and counted off by T45 (`:1884`), not by T38. This package keeps that call
   alive on purpose (`:2257-2259`).

Read descriptively the sentence is false for rows 3 and 4; read normatively it forbids
what `:2585` and section 22 permit. Either way the builder of no. 7's writer form — the
gap section 36 names at `:6387-6399` — must choose between two sentences of the same
document, which T48's own rule (`:2599-2603`) calls a finding and not a build decision.

**Not precision beyond the five conditions.** `0001` puts extra precision into a package,
and I applied that on `0277` and `0274`. This sits inside the one sentence the `abnahme`
asks for: after this decision the in-round quantities take no `Zustand`, so „the quantities
that take a `Zustand`" *are* the vintage build, the test bench, G8 and valuation.

**The repair is one clause**, in T48, same file, same lane: name the complete-state classes
instead of one of them — end of a finished round (T38), the vintage start state (T45), or a
state built by hand in the test bench; never the round that is running. The type argument,
the three rejected answers, T33 `:2254-2259` and the rest of section 36 stand.

## Not a finding, measured in passing

Section 36's five `werte.hpp` line numbers (`:339, :344, :356, :367, :599`) are each exactly
3 short at HEAD today — the declarations stand at `:342, :347, :359, :370, :602`. The uniform
offset says the file moved after the measurement, and this repo measures at the text. What
the numbers assert is true: nos. 9–11 have no writer form, and no. 22 still takes
`const zustand::Zustand&` beside the writer (`:602-605`). One keystroke while the file is
open, not a package.
