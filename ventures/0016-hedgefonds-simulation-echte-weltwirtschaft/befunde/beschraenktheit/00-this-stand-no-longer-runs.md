# This stand no longer runs — its numbers stand, its scripts do not

Written 2026-09-08, package `0246`, bruchtester. **Nothing in this folder is deleted,
renamed or corrected** (house rule 3). This file is the one thing that was missing beside
the transcripts: the notice that they can no longer be reproduced from here.

## What still holds

`lauf-sanitizer-off-null.txt:1215-1216` and `lauf-sanitizer-off-gueltig.txt:210-211` are
the **last measured** boundedness numbers of this venture (2026-09-06, package `0145`):
`1 von 310` over one round and over 200 rounds, in both profiles and both sanitizer
builds. `ops/plan.md:96` carries that number as the venture's one number and rests it on
this folder. It is still the last measured number, and **no new number belongs beside it
here** — the successor stand named below predicts one but has not been run.

## What no longer holds: `lauf.sh` and `lauf-2.sh`

Both translate the same `beschraenktheit.cpp` (`lauf.sh:83-87`, `lauf-2.sh:65-66`), so
both are dead. Three independent reasons, re-checked at HEAD today by reading:

1. **It does not compile.** `kern::schritt::schritt` takes four inputs since package
   `0229` — `(vorrunde, aktionen, konstanten, modus)`, `kern/include/kern/schritt.hpp:332-333`.
   `beschraenktheit.cpp:729` calls it with three.
2. **Round 1 aborts at the parameter checksum**, once reason 1 is repaired.
   `kern/src/schritt.cpp:912-928` holds `parameter_pruefsumme(konstanten)` against
   `lies_alt(PLATZ_PARAMETERSUMME)` and calls `festkomma::abbruch` on a mismatch, before
   anything is written. This stand's `Rohling` (`beschraenktheit.cpp:115-126`) and
   `fuelle_gueltig` (:605-625) set **no** partie field, and `Zustand` value-initialises its
   310 addresses to zero (`kern/include/kern/zustand.hpp:460`). That a state which does not
   set this field dies at the binding is the repo's own statement, at
   `kern/test/schritt_probe.cpp:679-683` and :698.
   *Correction to the package text:* `0228` changed the head of `parameter.toml`; the
   check needs the carrier that `0229` added, and the reading it enforces is T10b, made
   binding by `0208`.
3. **The `null` profile aborts at the denominator condition.** Since package `0197` step 5
   computes (`kern/src/schritt.cpp:733-759`) and runs as a block for every country outside
   the address round (:985), so the mask does not spare it. `realeinkommenshub` (:625-641)
   aborts when `werte::bip(land) < 1`; `bip` sums the three `.sektor.N.wertschoepfung`
   addresses (`kern/src/werte.cpp:723-751`). `fuelle_gueltig` sets them to 3'000/3'000/4'000
   (`beschraenktheit.cpp:619-624`), so the `gueltig` profile passes the condition and the
   `null` profile does not. Its committed transcript nevertheless shows 200 green rounds
   (`lauf-sanitizer-off-null.txt:1207-1216`) — it was written before `0197`.

Reason 1 stops the translation; 2 and 3 stop the run as soon as 1 is repaired. Repairing
one of them does not bring the numbers back.

`raender.cpp` in this folder contains no call to `kern::schritt::schritt` and is built by
neither script. This notice says nothing about it.

## Where the successor is

`befunde/beschraenktheit-nach-schritt/` — `beschraenktheit-nach-schritt.cpp` and its own
`lauf.sh`, built by package `0243` on 2026-09-08 against the three reasons above.
**It has not been translated or run either**; whoever runs it first should expect to
handle a `-Werror` finding and must not mistake one for a finding about the model. Its
prediction for the `gueltig` profile stays in `bruch-2026-09-08-2.md`, where `0243` put it.
