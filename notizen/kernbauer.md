# Logbuch: kernbauer

Rotated by the runner on 2026-09-08 at 15370 characters (cap 12,000). Predecessor: `notizen/archiv/kernbauer-2026-09-08-6.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 -- 0260 (recount the length passage above `bip`; comment lines only)

Delivered in `kern/src/werte.cpp`: the passage above `bip` rewritten, four paragraphs
with the derivation visible. Counted at HEAD: **15** addresses the function can read
(three per call, five `Gebiet` values), **10** of them nameable in the message, widest
text form **32** characters (the Restwelt), maximum message **324** characters, margin
187 against 511. No function body touched.

- 2026-09-08, **the lesson of the run** -- **A set of numbers that agrees with itself is
  not a counted set, and agreement is exactly what lets a miscount survive.** The old
  passage said twelve addresses, 31 characters, at most 323 -- and all three are
  *correct together* for the four countries: 215 + (31 + 6 + 3 + 1) + 5 + 20 + 22 + 20 =
  323 exactly. Nothing in the passage was arithmetically wrong, so nothing in it invited
  a recount; the defect was one level up, in **which set was counted**. General form:
  when a comment states several numbers that check out against each other, the thing
  still worth testing is the *domain*, and it is the one thing internal consistency can
  never show. The whole error here is one character wide.
- 2026-09-08 -- **Count over the signature, not over the callers.** The review reached 15
  by naming a live caller that passes every Gebiet. True, and it goes stale the day that
  caller changes -- the same defect I paid for in `0249`. `bip` takes a `Gebiet` and
  `stelle_sektorgroesse` serves all five: that argument holds at every future HEAD and
  costs one reading. I wrote the comment from the signature and named no caller.
- 2026-09-08 -- **The read set and the reportable set are different sets, and a length
  bound needs the second.** `bip` reads 15 addresses but can only ever *name* 10: the
  first partial sum is the summand itself and never leaves `i64`, so sector 1 has no
  abort. Giving only 15 leaves the "largest number is 185" step underived; giving only 10
  answers a question nobody asked. Both, one sentence each.
- 2026-09-08 -- **`werte_probe` measures the 319 case and asserts it is under 511.** That
  is 192 characters of slack -- an assurance that cannot fail on any message this
  function can build. It holds in the weak sense the clause claims (the same case *is*
  measured at runtime, printed, and checked for the truncation mark) and is worth nothing
  as a guard on the new maximum, which no probe reaches because no probe ever calls
  `bip` with `Gebiet::RW`. Proposed as `0261`.
- 2026-09-08 -- **`zahlwort_riegel` reads exactly one file and it is not this one.**
  `PRUEFLING` at `zahlwort_riegel.cpp:179` is `kern/include/kern/werte.hpp`. Number words
  in a `werte.cpp` comment are unconstrained -- I wrote "fuenfzehn" and "zehn" freely.
  Confirmed rather than assumed, because my carried-forward note said the same and a note
  is a hint.
- 2026-09-08 -- **A dotted address form belongs in quotes, not in backticks.**
  `bezeichner_riegel` reads backticked spans under `kern/` and resolves them as names;
  „restwelt.sektor.N.wertschoepfung" in backticks would be read as a path or split at the
  dots. Same reason I did not backtick `teil`: it is a local, and I do not know that the
  riegel finds locals. Everything I did backtick -- `Gebiet`, `stelle_sektorgroesse`,
  `Meldung::adresse`, `I64_MIN`, `i64`, `bip` -- is declared under `kern/`.
- 2026-09-08 -- **Checked and correct, so nobody recheck it:** `verlauf_probe.cpp:249`
  and `:254` say „zwoelf Adressen" and are **right** -- `ausgangslage` loops over
  `LAENDER`. The two in `schritt_probe.cpp` remain unmeasured; I did not look.
- 2026-09-08, **what I am unsure about, for the project manager:** three things.
  **(a)** The passage also carried „der Landesname am Ende geht nicht verloren". There is
  no Landesname in that message -- it ends with the running sum. The acceptance asked
  about three numbers, not about this clause, but it sat inside the sentences I was
  rewriting, so I replaced it with what actually arrives last. A reviewer holding to the
  letter will call it a fourth change.
  **(b)** The acceptance forbade repairing the `werte_probe` clause. I kept that sentence
  byte-identical and on its own line, but I put the 319 sentence in front of it and made
  that one self-contained („dreimal 2^62 in einem Land"), so „dieselbe Laenge" still has
  a referent. My reading is that the clause is the sentence about the probe and I did not
  touch it; a reviewer could read the added parenthetical as extending it.
  **(c)** I cannot compile. This run is comment lines only, so the exposure is the riegel
  and not the compiler -- and `bezeichner_riegel` is already red at HEAD for a reason that
  is not mine (`ABBRUCH_MELDET` under `kern/test`), which means a red there tonight does
  not separate my names from that one by itself.

