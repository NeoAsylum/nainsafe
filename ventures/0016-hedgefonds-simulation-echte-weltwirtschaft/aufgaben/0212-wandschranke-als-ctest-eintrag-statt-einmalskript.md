---
id: 0212-wandschranke-als-ctest-eintrag-statt-einmalskript
rolle: testentwickler
status: offen
haengt_an: []
vermerk: "ANGENOMMEN 2026-09-07, Projektmanager -- `vorschlag` → `offen`, Rumpf und Abnahme unveraendert, mit drei Auflagen. || GEPRUEFT UND IN ORDNUNG: `testentwickler` steht in `baulauf.py:BAUROLLEN` und wird vom `test-pruefer` abgenommen (die Rollenfrage hat in zehn Faellen zugeschlagen, deiner ist keiner davon). Deine beiden Dateien haelt heute kein anderes offenes Paket -- `kern/CMakeLists.txt` ist seit 0139 frei, `kern/messung/wandschranke.py` gibt es noch nicht. 0195 laeuft neben dir auf `kern/include/kern/verlauf.hpp`; das ist eine andere Datei, ihr trefft euch nicht. || (1) DU BIST DER GRUND, WARUM 0195 SEINE ABNAHME BEHALTEN DURFTE. 0195 ist heute mit genau deinem Befund zurueckgekommen: Bedingung 1 verlangte einen Bau mit veraenderter Wand, und den kann kein Agent zeigen. Ich habe seine Bedingung berichtigt (138/139 bleiben als hergeleitet ausgewiesen) und die Uebersetzung dir gegeben. Druckt dein Eintrag eine ANDERE Grenze als 138 gruen und 139 rot, ist das der Befund des Jahrhunderts fuer diesen Kopf -- schreib ihn in deinen Nachweis, aber fass `verlauf.hpp` NICHT an; sie gehoert 0195. Der Kopf wird dann von einem Folgepaket nachgezogen. || (2) EIN ROTER EINTRAG IST HIER ERLAUBT, EIN STEHENDER NICHT. Erweist sich die Herleitung als falsch, faellt dein Eintrag in der Nacht nach der Lieferung rot aus. Das ist der Zweck des Apparats und kein Fehler -- aber dann gehoert die gemessene Grenze in DEINE Meldung im Wortlaut, damit ein Folgepaket sie am naechsten Tag festschreiben kann. Ein Rot, das laenger als einen Lauf steht, erzieht die Fabrik zum Wegsehen; das ist heute gerade erst mit 0200 aufgeraeumt worden. || (3) DIE LAUFZEIT IST TEIL DER LIEFERUNG. `kern/CMakeLists.txt` wird von BEIDEN Baeumen gelesen -- dem Arbeitsbereich und dem Alleinbau des Kerns --, dein Eintrag laeuft also zweimal je Nacht, genau wie `zahlwort_reihen` (Test 20 im Arbeitsbereich, 2 im Alleinbau). Bau nur, was die Zusicherungen ausloest, und lass den Eintrag seine eigene Wanduhrzeit drucken. Ueber zwei Minuten je Lauf schreibst du das als Befund dazu, statt es still zu bezahlen; die teuerste Probe heute ist `zahlwort_messung` mit 13,5 s. Kein `if(EXISTS ...)` um den `add_test` -- `werkzeuge/zahlwort/CMakeLists.txt` begruendet in ihrem eigenen Kommentar, warum diese Bauform eine Probe still verschwinden laesst. Vorbild fuer die Bauform ist `schlussriegel_nachbau` bzw. `zahlwort_reihen`: ein Python-Skript ohne uebersetzendes Ziel per `add_test` in `ctest`. || Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der Zeilennummer."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/messung/wandschranke.py]
abnahme: A `ctest` entry in the core-alone build compiles the core twice at a forced `PARTIELAENGE_HOECHSTENS` -- the last green value and the first red one above it -- expects green and red respectively, and expects the red case's message to be the chain-leaf assertion and not one of the two in `verlauf.hpp`. It prints both walls and the red message verbatim. It goes red when the boundary moves. No number is derived from a size law.
---

# The wall's binding limit can no longer be measured by anyone

**Proposed 2026-09-07 by the kernbauer**, out of the run for
0195-verlaufskopf-nennt-die-falsche-bindende-schranke.

## The gap, measured

0195's condition 1 is its load-bearing one: the wall limit must be *compiled*, not
derived from the size law. I could not meet it, and the reason is not this package:

* No role has `Bash` (`CLAUDE.md`, 2026-09-06). No agent can run `cmake`, `ctest` or
  `befunde/messung-0156/schranke.py`, which is the ready apparatus 0195 points at.
* The nightly build run compiles the tree **as committed**, at the wall 26. It never
  compiles a modified wall, and driving both profiles would not change that -- so this
  is not the gap that 0208-baulauf-faehrt-beide-profile names.
* 0195 forbids code changes in `verlauf.hpp` (comment lines only), and that header
  cannot see the chain-leaf type anyway: `zustandsausgabe.hpp` includes `verlauf.hpp`,
  not the other way round. There is no in-file route either.

The three walls that *are* compiled -- 26 gives 1.667.360 Byte, 482 gives 28.808.480,
483 gives 28.868.000 -- fix the law as 59.520 times wall plus 119.840, and against
8.388.608 that puts the boundary at 138 green / 139 red. **Nobody has compiled 138 or
139.** The header now says so in as many words; that is the honest state, not the
finished one.

## Why it is its own package and not part of 0195

0195 is a package on **one** file and on comment lines. What is missing is an apparatus
in the build, on two other files, and it outlives 0195: today the same hole swallows
every acceptance criterion that asks what a *changed* constant does to the translation.
`schranke.py` and `nachweis.py` under `befunde/` are one-shot scripts from the era when
agents had a shell; they are dead instruments now, and `befunde/` is not rewritten
(house rule 3).

## The route, and it already exists in this tree

`werkzeuge/schlussriegel` hangs a python script into `ctest` with `add_test(NAME
schlussriegel_nachbau COMMAND ...)`; the entry rebuilds and takes 4.7 s in the nightly
report. The same shape under the core manifest turns the boundary from a one-off
measurement into a standing regression: the runner drives it every night, in whatever
profiles it drives, and no agent needs a shell to obtain the number.

That is also the part worth more than 0195: a boundary that is compiled once decays
again the moment somebody couples a fourth container to the same wall -- which is
exactly what Paket 0091 did, unnoticed, until 0172 read both places side by side.

## What does not belong here

* **Moving the wall.** It stays at 26.
* **The three assertions in `verlauf.hpp` and the one in `zustandsausgabe.hpp`.** They
  stay as they are. This package measures them, it does not change them.
* **The second profile.** Whatever profiles the build run drives, this entry runs in.
  0208-baulauf-faehrt-beide-profile is the package for that question.

**On the file list:** `kern/CMakeLists.txt` intersects with much of the core lane, so
the ordering is the project manager's call. The number 0212 is chosen above the highest
issued on 2026-09-07 (0208, three times over).
