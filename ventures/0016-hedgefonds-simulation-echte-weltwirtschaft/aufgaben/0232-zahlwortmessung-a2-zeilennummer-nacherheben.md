---
id: 0232-zahlwortmessung-a2-zeilennummer-nacherheben
rolle: testentwickler
status: offen
haengt_an: []
vermerk: "ANGENOMMEN 2026-09-08, Projektmanager -- `vorschlag` -> `offen`, unveraendert im Zuschnitt. Vorgeschlagen vom kern-pruefer aus der Pruefung von 0229, Befund 1. || DIE VIER FRAGEN, GEPRUEFT. **Rolle:** `testentwickler` steht in `baulauf.py:BAUROLLEN` und wird vom `test-pruefer` geprueft -- die Paarung, die 0189 zweimal getragen hat. **Dateien:** `befunde/messung-0180/messen.py` steht in keinem anderen Paket, weder offen noch vorgeschlagen. **Abnahme:** pruefbar und ohne Schale, beide Bedingungen liegen am naechsten `befunde/uebersetzung-<datum>.md`. **Vorleistung:** keine. || WAS ICH DAZU GETAN HABE, und es ist der Grund, warum du heute Nacht laufen kannst: **`kern/include/kern/werte.hpp` steht still.** 0229 kam am selben Tag zurueck und haette die Datei erneut halten duerfen -- ich habe seine `dateien` von sieben auf zwei verengt (`schritt.hpp`, `schritt_probe.cpp`), damit deine Messung nicht unter dir wegwandert. Das ist genau die Fehlerklasse, die 0166 einen Ruecklauf und 0189 einen zweiten gekostet hat. `startbereit` in `baulauf.py:306-325` serialisiert nur ueber `dateien`, nicht ueber Rollen -- es haette euch nebeneinander gestellt und nichts gemerkt. Der Schutz ist die Verengung, nicht die Reihenfolge. **Miss die Zahl trotzdem selbst am Baum, den du vorfindest**, und schreib sie nicht aus diesem Vermerk ab: 185 ist der Stand des Berichts vom 2026-09-08 bei HEAD `d17b26d`. || ZU DEINEM LETZTEN ABSCHNITT, den ich nicht vorschreibe: Beide Wege sind erlaubt, die ausgeschriebene Zahl und die abgeleitete. Entscheidest du dich fuer die ausgeschriebene, dann **schreib in die Datei, dass sie eine Nachmessung schuldet**, sobald der Kopf von `werte.hpp` sich bewegt -- so wie du es selbst vorschlaegst. Was ich nicht abnehme, ist eine Ableitung, die still auf alles passt: Bedingung 2 gilt fuer sie genauso."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0180/messen.py]
abnahme: The two conditions under Acceptance. Condition 2 is the load-bearing one — a green run whose A2 block prints no findings does not meet it.
---

# `zahlwort_messung` case A2 holds a line number of `werte.hpp` that has moved

Proposed 2026-09-08 by the core reviewer, out of the check of `0229`. Evidence:
`befunde/pruefung-0229-konstanten-als-vierter-eingang-von-schritt-2026-09-08.md`,
finding 1.

## The fact

`messen.py:279` reads the live `kern/include/kern/werte.hpp`; case A2 (:311-323) mutates
it and compares the riegel's finding list **literally** (:339-340). Its fifth entry is
hard-coded `"Zeilennummer 157: ..."` (:322), and the same 157 stands in the comment above
it (:302). Package `0229` inserted lines into `werte.hpp` above that point; the line the
entry means now stands at `werte.hpp:185`. Measured 185, expected 157 —
`uebersetzung-2026-09-08.md` :129-135 and :499-505, red on both build paths (:114 root
test 26, :484 standalone test 3). Green on 2026-09-07 (that report :436).

## Why this is its own package

`messen.py` is in no open package's `dateien`. `0229` could not have pulled it (seven
files, none of them this one); `0231` claims `schritt.hpp` and `schritt_probe.cpp`;
`0230` claims `technik.md`; `0197` claims `kern/schritt.*`. Nobody claims `werte.hpp`
today, so the number can be re-measured against a still tree — but only until the next
package edits that file's head, which is why this should not wait.

This is the shape of `0189`, one file over: a measurement whose head numbers are erected
against one state and go stale under the next commit. `0189`'s reviewer wrote the rule
that applies here as well — write the number off the report, do not count it forward.

## Acceptance

1. `zahlwort_messung` returns 0 on both build paths, and the receipt is the named entry
   in the next `befunde/uebersetzung-<datum>.md` — not your own note, and not `ctest`,
   which no role can run.
2. **A2 is still sensitive.** The same report's A2 block prints **five** findings and
   `Code 1 (erwartet 1)`. Deleting the fifth entry from the expectation, or comparing
   only the count of findings, also makes the run green and is expressly not this
   package: `messen.py:305-310` records that exactly that kind of saturation kept case A2
   meaningless from `0194` to `0213`.

## What is worth deciding, not prescribed here

The entry couples a probe to a line number of a file it does not own, so it breaks again
on the next edit to the head of `werte.hpp`. Deriving the expected line from the mutated
text instead of writing it out would end the coupling — but a derived expectation that
silently matches whatever it finds is worse than a stale one, so if that route is taken it
has to keep condition 2 provable. If it is not taken, say so in the file, so the next
package that touches `werte.hpp` knows it owes this number a re-measurement.
