---
id: 0200-zitate-auf-uebersetzte-ueberschriften-nachziehen
rolle: testentwickler
status: fertig
abnahme_erteilt: "2026-09-07, Projektmanager, auf befunde/pruefung-0200-zitate-auf-uebersetzte-ueberschriften-nachziehen-2026-09-07.md (urteil: geprueft, 0 Befunde). Das stehende Rot ist weg: `belegstellen_riegel` ist im Bericht 2026-09-07 gruen (Test 16/21 im Arbeitsbereich, 1/1 im Alleinbau), und der ganze Baulauf meldet zum ersten Mal seit Tagen `ergebnis: ok`. Der Uebergang rot->gruen am selben Tag auf demselben Korpus ist der Rotnachweis, den kein Mutant ersetzt. Damit sind 0147, 0166, 0182, 0189 auf `belegstellen_riegel.cpp` frei und 0185 auf `reihen.toml`, 0203 auf `parameter.toml`. Der wiederkehrende Teil bleibt offen: die naechste uebersetzte Ueberschrift bricht die Zitate erneut -- das ist die Frage an den Betreiber in ops/plan.md (Empfehlung B) und keine Aufgabe fuer ein Paket."
haengt_an: []
vermerk: "ACCEPTED 2026-09-07, project manager -- `vorschlag` → `offen`, body and acceptance unchanged, BUT WITH A DIFFERENT ROLE. You asked for `rolle: uebersetzer`; that role exists, but it is not in `baulauf.py:BAUROLLEN` and in no entry of `REVIEW`. The translation run is a runner of its own outside the package model -- a package with that role is never drawn by the build run and would never get a reviewer. It would have sat there silently, and that is the tenth case of this kind. Now `testentwickler`: it is a build role, reviewed by `test-pruefer` -- the same trade that wrote this proposal -- its write boundary `Edit(ventures/**)` covers all eight files on your list, and the riegel itself is its craft. Two of your files belong to other trades (`daten/reihen.toml`, `parameter.toml`); there you touch the wording of the section citation and NOTHING else -- every other line there belongs to 0185 and 0203, which stand behind you. || That you may rename nothing in `specs/` is, with this role, no longer only an instruction but mechanical: `Edit(ventures/**)` does not reach into `specs/`. The order is the other direction -- pull the ten citations onto the wording their heading carries today. || PRIORITY 3 in ops/plan.md, and you are today the one package that frees several lanes at once, so more stands behind you than usual: on `belegstellen_riegel.cpp` the line is you, 0147, 0166, 0182, 0189 (0147 came back today partly because its criterion demands a green corpus that does not exist without you); on `daten/reihen.toml` you, then 0185; on `parameter.toml` you, then 0203. These four hang on you as an order lock and not substantively -- except 0147, where the green corpus is a real condition. While `belegstellen_riegel` is red, every build run reports `ergebnis: fehler` on 19 of 20 green tests; that is the reason for the priority. || Your before-state is the HEAD in force then; search by text, not by line number. The translation run continues and may rename an eleventh heading while you work -- your acceptance catches that, it demands the wording in force on the day of the change and not an English one. If the riegel stays red afterwards on a citation renamed after you read it, that is a finding and not a Ruecklauf: name the place and the time of day."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/adressen.md, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/aktion.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schritt.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zustand.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/schritt.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: The ctest test `belegstellen_riegel` returns 0 on the tree in force at build time, and its report shows zero unresolved Abschnittszitate — achieved by updating each of the ten citations from the report `befunde/uebersetzung-2026-09-07.md` to the wording now in force at its target, not by changing any heading in `specs/`, deleting a citation, or weakening the riegel.
---

# Pull the section citations onto the translated headings

**The situation, measured and not feared.** The translation run renames headings in
`specs/.../spiel.md` and `daten.md` (`ops/uebersetzt.txt`: "The loop", "Die
Aktionen", …). Ten citations in code and data documents still quote the German
wording; the runner report of 2026-09-07 shows ctest `belegstellen_riegel` FAILED
(Code 8) in both builds with "10 Abschnittszitat(e) finden ihre Ueberschrift nicht".
The riegel is right — this is exactly the drift it exists to catch.

**Why it is its own package.** The ten citing files belong to no open package, and
they span four owners' territory (daten, kern, parameter.toml, werkzeuge). As long as
the test is red, every venture ctest run reports `ergebnis: fehler` — a standing red
that trains everyone to ignore the one signal that may not be ignored. It also blocks
the re-measurement of 0147 (see `befunde/pruefung-0147-...-2026-09-07.md`), whose
abnahme requires a green corpus.

**Known collision, for serialisation:** `belegstellen_riegel.cpp` is also in the
`dateien` of 0147 (zurueck) and the 0115→0130 chain. The Projektmanager sequences.

**What this package must not do:** rename anything in `specs/`, drop a citation, or
touch the riegel's logic or thresholds. One citation (`daten/adressen.md` →
"Der Zustand") may target a heading whose translation is still pending; if so, quote
the wording in force on the day of the change — the abnahme is "resolves against
today's target", not "is English".

**The recurring half, for the operator, not for this package:** every future
translated heading will kill its citations again. Making the nachziehen part of each
translation run (or running the riegel inside the translation loop) is a rule change
and belongs to the Projektmanager/operator, not to a builder.

*Proposed 2026-09-07 by test-pruefer during the pruefung of 0147.*
