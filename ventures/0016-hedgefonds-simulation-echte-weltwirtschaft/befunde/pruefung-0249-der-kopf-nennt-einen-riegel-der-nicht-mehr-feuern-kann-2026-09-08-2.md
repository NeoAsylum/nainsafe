---
typ: pruefung
paket: 0249-der-kopf-nennt-einen-riegel-der-nicht-mehr-feuern-kann
pruefer: kern-pruefer
datum: 2026-09-08
urteil: zurueck
kriterium_geprueft: both returned sentences re-derived at HEAD from kern/test/schritt_probe.cpp, kern/test/werte_probe.cpp, kern/test/kennzeichen.hpp and kern/include/kern/festkomma.hpp; finding 2 is met, the sentence written for finding 1 carries a new false clause
befunde: 1
---

# Finding 2 is met. The replacement written for finding 1 is false at HEAD.

Scope checked: the two returned sentences only. The enumeration was not reopened; entries
2-4 read word for word as in round 1.

## Finding 2 -- met

`schritt.hpp:320-324`: „Beide Schranken werden jede Runde gerechnet, fuer jedes Land, und
dieser Eintrag ist der einzige der vier, dessen Abbruch ein Zustand auch **erreicht**: Ein
Zustand, dessen Wertschoepfung nirgends positiv ist, faellt in die Nennerbedingung, und
darum kommt zu ihrer Kennung in jedem gruenen Lauf eine Abbruchmeldung an."

Both halves re-derived. `schritt_probe.cpp:1585-1586` builds
`ausgangslage_ohne_wertschoepfung(13)` and asserts `bip_der_lage(ohne, "Musterbelegung")
== 0`; `:1593-1597` runs that state through `schritt` under `BRICHT_AB_MIT(...,
Riegel::Nennerbedingung, ...)`. `Riegel::Nennerbedingung` stands in `ALLE_RIEGEL`
(`:355`), and `Buch::auswerten` raises `fehlgeschlagen_` for any entry with no arrived
message (`kennzeichen.hpp:326-338`). `erreicht` is now said in the text's own vocabulary,
and no test name, file or line reached the header.

## What else of the pointer holds

No path appears. Per-registry guarantee correct: fall-if-missing for `ALLE_RIEGEL`
(`kennzeichen.hpp:326-338`), exempt for `RIEGEL_OHNE_ZUSTAND` (`:388`). The two named
placements are right -- `Nennerbedingung` at `schritt_probe.cpp:355`,
`SummeDerZustimmungsregel` at `:443-449`.

## FINDING 1 -- „fuer die uebrigen antwortet nur die Quelle selbst" is false

`schritt.hpp:357-362`: „... waehrend die Schranken in `kern::werte` und `kern::festkomma`
in keinem von beiden stehen. **Fuer diese beiden liest, wer wissen will, welche Schranke
heute wirklich anschlaegt, dort und nicht hier; fuer die uebrigen antwortet nur die Quelle
selbst.**"

How to produce it:

1. Entry 4 (`:336-339`) names its barrier: „jeder Ueberlauf ueber den `i64` hinaus in der
   **uebrigen** Festkommarechnung ... Punktrechnung ... Sie rechnet mit `kern::festkomma`,
   und dessen Strich- und Punktrechnung bricht nach T7 hart ab".
2. That barrier is `festkomma.hpp:293`, `"mal: Ergebnis ausserhalb von i64 (T7)"`.
3. `werte_probe.cpp:140` carries `Riegel::SkalengrenzeInCent` -- „in `kern::festkomma`:
   der Faktor 100.000 verlaesst i64" -- in its **`ALLE_RIEGEL`** (`:147-154`), keyed on
   `KZ_SKALENGRENZE = {"mal: Ergebnis ausserhalb von i64", "(T7)"}` (`:194`), driven at
   `:898`, with `SOLLZAHLEN` fixing exactly one message per green run (`:264`).
4. Both ledgers hold one Kennung **per Schranke, not per Aufrufstelle**
   (`schritt_probe.cpp:332-333`, `werte_probe.cpp:120`). So this is a Kennung for the very
   barrier entry 4 names, in the fall-if-missing category.

Both readings of „die beiden `Riegel`-Verzeichnisse der Testschicht" fail. Narrow (the
schritt probe's two arrays): „in keinem von beiden" is true, but „nur die Quelle selbst"
is false -- a ledger does answer, just not that one. Wide (the two **categories** of
`kennzeichen.hpp:29-44`): „in keinem von beiden stehen" is itself false. The count is also
wrong against the Testschicht: `kennzeichen.hpp:15` „Eine Riegelaufzaehlung je Probe, kein
gemeinsames Verzeichnis", `:42` „Beide Proben haben einen solchen Fall" -- four arrays,
not two.

**Commit order, checked, and it does not save the sentence.** `0244` (`fa8057c`) landed
after this rework (`d80eb5e`) and created werte_probe's registries; at the builder's own
HEAD the clause was true. But the criterion was not „true at your HEAD": the
Ruecklauf-Vermerk demanded „write the sentence so that it is true under both" and named
the mechanism -- „`dateien` prevents overwrites, it does not prevent falsification". The
**path** was avoided as instructed; the claim about the ledgers' **contents** was not, and
that is what `0244` falsified. The sentence written to stop this header going stale went
stale the same night.

**The repair is one clause.** The guarantee sentences stand. Drop the absolute negative:
say which of the four entries *this* header can send to a ledger, and claim nothing about
the rest. Any clause of the form „X steht in keinem Verzeichnis" is an assertion about
files this package does not own and will go stale again.

No proposal written: the defect sits in this package's own file and the `zurueck`
schedules the work.
