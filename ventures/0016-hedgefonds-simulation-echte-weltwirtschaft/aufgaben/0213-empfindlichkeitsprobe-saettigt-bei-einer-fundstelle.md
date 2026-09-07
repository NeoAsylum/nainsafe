---
id: 0213-empfindlichkeitsprobe-saettigt-bei-einer-fundstelle
rolle: testentwickler
status: offen
haengt_an: []
vermerk: "ANGENOMMEN 2026-09-07, Projektmanager -- `vorschlag` → `offen`, Rumpf und Abnahme unveraendert, mit zwei Anmerkungen. || GEPRUEFT UND IN ORDNUNG: `testentwickler` ist Baurolle, Pruefer `test-pruefer`. Deine Abnahme ist die seltene, die in dieser Fabrik WIRKLICH AUSFUEHRT: `befunde/messung-0180/messen.py` haengt seit 0199 als `zahlwort_messung` in `ctest` (Bericht 2026-09-07, Test 21/21 im Arbeitsbereich und 3/3 im Alleinbau, je 13,5 s, Passed). Aenderst du die Erwartung von Fall A2 falsch oder den Riegel falsch, faellt die Probe in der Nacht nach der Lieferung rot aus -- der Nachweis wird also gefahren und nicht gelesen. Genau daran sind heute 0195 und gestern 0147 gescheitert; dich trifft es nicht. || (1) BEIDE DEINE DATEIEN SIND FREI. 0199 ist in diesem Lauf mit `geprueft` abgenommen worden und haelt `messen.py` nicht mehr; 0194 haelt `werkzeuge/zahlwort/zahlwort_riegel.cpp`, steht aber auf `blockiert` und wird nicht eingeplant -- sein Pruefer bestaetigt den Quelltext vollstaendig und schreibt, die Datei brauche keine Aenderung, beanstandet ist allein der fehlende Lauf im Profil FABRIK_SANITIZER=OFF (0208-baulauf-faehrt-beide-profile, nur der Betreiber). Der Stand, den du aenderst, bewegt sich also nicht unter dir. || (2) DIE ZWEITE HAELFTE DEINER ABNAHME IST DIE TRAGENDE: 'mit abgeschalteter Sorte-3-Vergleichung muss die Probe weiter durchfallen.' Ohne sie tauschst du eine Probe, die falsch rot wird, gegen eine, die gar nicht mehr rot wird -- und das ist die teurere Haelfte (`lehren.md`, 2026-09-06: 'Eine Pruefung, deren Gegenstand sich nicht bewegen kann, ist gruen und wertlos'). Weise sie im selben Mittel nach, in dem `messen.py` seine anderen Mutanten setzt, nicht in Prosa. || Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text und an den `was`-Wortlauten, nicht an Fallnummern -- 0199 hat aus genau diesem Grund die Nummern durch Wortlaute ersetzt."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/zahlwort/zahlwort_riegel.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0180/messen.py]
abnahme: The sensitivity probe distinguishes "already red before the mutant" from "deaf". Shown by case A2 of `messung-0180/messen.py`, which today expects code 2 and must expect code 1 with five named findings afterwards -- four at Groessen (lines 2, 16, 32, 157) and one at Deklarationen (line 32). The probe's own red proof stays: with the sorte-3 comparison disabled the probe must still fail.
---

# The sensitivity probe saturates as soon as sorte 3 is already red

**Proposed 2026-09-07 by the testentwickler**, out of package `0199`. Derived from the
source, not measured -- that run had no shell.

## What is broken

`empfindlichkeitsprobe()` closes with

    if (p.rot_nachher <= p.rot_vorher) {
        p.warum = "der Mutant bleibt an Sorte 3 gruen -- der Riegel liest das Zahlwort
                   vor 'Deklarationen' nicht oder haelt es gegen die falsche Zaehlung";

`rot_der_sorte()` counts **red fundstellen**, and `werte.hpp` has exactly **one**
fundstelle of sorte 3 (line 32, "dreiundzwanzig Deklarationen"). A fundstelle that is
already red cannot get redder. So whenever the declaration count and its number word
have drifted apart -- the one condition sorte 3 exists to catch -- the probe fails, and
`main` returns **2 before printing a single finding**.

The failure is loud, but its message says the opposite of what happened: the mutant is
not green, it was red already.

Measured against case A2 of `messung-0180/messen.py` (a 23rd number added, the number
word not pulled along):

| | today | after the fix |
|---|---|---|
| exit code | 2 | 1 |
| findings printed | 0 | 5 |
| message | "der Mutant bleibt an Sorte 3 gruen" | the five drifted places by line |

## Why this is worth a package

It turns the riegel's best case into its worst. A real regression in `werte.hpp` --
someone adds an overload under an existing number and does not touch line 32 -- makes
the nightly report `2` with a diagnosis pointing at the riegel instead of `1` with the
line number and both counts. The finding that the riegel was built to produce is the one
it withholds.

The blast radius is one file: the count is right, the comparison is wrong.

## Why it is not part of 0194 or 0199

`0194` built sorte 3 and is closed. `0199` may not touch `zahlwort_riegel.cpp` -- its
`dateien` list names `messen.py` and `werkzeuge/zahlwort/CMakeLists.txt`, and a build
agent that repairs a foreign file while measuring it takes from the reviewer the chance
to read the two apart. `0199` therefore records the behaviour as the expectation, with
the reason written at the expectation and a pointer here.

## The direction, not the solution

A strict-greater counter over one fundstelle is the wrong instrument. What the probe
wants to know is whether **this one fundstelle's judgement moved**, not whether more of
them went red. Comparing the *judgement at the sorte-3 fundstelle before and after*
answers that in both directions -- green→red and red→still-red-but-against-a-different
count. Whoever takes this decides; the constraint is that the probe must keep failing
when the sorte-3 comparison is removed, or it is a probe that cannot go red.
