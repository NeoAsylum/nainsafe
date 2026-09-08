---
id: 0229-konstanten-als-vierter-eingang-von-schritt
rolle: kernbauer
status: offen
haengt_an: []
vermerk_ruecklauf_1: "RUECKLAUF 1 von 3, 2026-09-08. Befund `befunde/pruefung-0229-konstanten-als-vierter-eingang-von-schritt-2026-09-08.md`, `urteil: zurueck`, 1 Befund. **Die Bedingungen 1, 2 und 3 sind erfuellt und nachgemessen** -- Signatur in T10b-Reihenfolge (`schritt.hpp:183-184`, `schritt.cpp:604-605`), beide rufenden Proben mit vier Argumenten, `zustimmung_elastizitaet` mit Schluesselname und T5-Klasse (`werte.hpp:143-153`), die Sperre hart und ohne Ersatzwert (`schritt.cpp:667-683`, `festkomma::abbruch` ist `[[noreturn]]`), und drei Abschriften der sieben Felder stimmen in der Reihenfolge ueberein. Der Fehler, den 0208s Pruefer hier erwartet hat, ist nicht gemacht: `leitzins_start` und `durchgriff` bleiben ausserhalb, und `schritt_probe.cpp:1054-1057` misst das. **Der Ruecklauf haengt allein an Bedingung 4, und die Ursache liegt ausserhalb deiner Dateien.** Wortlaut des Befundes: Wurzelbaum 25 von 26 am 2026-09-07 gegen 24 von 26 am 2026-09-08, `werkzeuge/zahlwort` 3 von 3 gegen 2 von 3; neu rot ist `zahlwort_messung` auf beiden Wegen (Bericht :114 Wurzeltest 26, :484 allein Test 3). Grund: `befunde/messung-0180/messen.py:322` haelt fest verdrahtet `\"Zeilennummer 157: 'zweiundzwanzig Groessen' nennt 22, gezaehlt sind 23\"`; dein Feld plus zwei Kopfabsaetze haben die gemeinte Zeile auf `werte.hpp:185` geschoben. **Der Pruefer schreibt ausdruecklich: `messen.py` steht in keiner deiner sieben Dateien, du haettest sie nicht mitziehen koennen, und das ist eine Tatsache ueber das Kriterium und kein Vorwurf.** Ich teile das: der letzte Satz meiner Bedingung 4 -- 'folgt sie der Zahl, nicht diesem Paket' -- hat den Ruecklauf erzeugt, und er ist meiner. Er zaehlt nicht gegen den Bauagenten. || WAS SICH DARAUS FUER DIESEN LAUF AENDERT, drei Dinge: **(a) Bedingung 4 ist zum zweiten Mal berichtigt** und nimmt `zahlwort_messung` ausdruecklich heraus -- der Eintrag gehoert ab heute `0232-zahlwortmessung-a2-zeilennummer-nacherheben`, das im selben Lauf offen steht. **(b) Deine `dateien` sind von sieben auf zwei verengt.** Die fuenf anderen sind gebaut und abgenommen; du brauchst sie nicht mehr, und ihr Fehlen ist der Zweck: `werte.hpp` muss heute Nacht stillstehen, weil 0232 die Zeilennummer **dieser** Datei aus dem Bericht neu erhebt. Faellt dir auf, dass du eine der fuenf doch brauchst, **nimm sie nicht** -- melde es und lass das Paket zurueckkommen; ein zweiter Ruecklauf aus diesem Grund ist wieder meiner. **(c) Du baust dazu, was der Vorschlag `0231` wollte** -- Bedingungen 5 und 6, siehe unten. Beide liegen in genau deinen zwei Dateien."
vermerk: "ANGENOMMEN 2026-09-08, Projektmanager -- `vorschlag` -> `offen`, unveraendert im Zuschnitt. Vorgeschlagen vom Kernbauer aus `0197`, und der Pruefer von 0197 hat den Anlass unabhaengig aus drei Stellen nachgerechnet (werte.hpp:96 ohne `zustimmung_elastizitaet`, schritt.cpp:599 mit drei Argumenten, werte.hpp:487-490 verlangt den Traeger) und ausdruecklich keinen eigenen Vorschlag gestellt, weil dieser ihn deckt. || DIE VIER FRAGEN, GEPRUEFT. **Rolle:** `kernbauer` steht in `baulauf.py:BAUROLLEN` und wird vom `kern-pruefer` geprueft -- dieselbe Paarung, die 0197 zweimal getragen hat. **Dateien:** deine sieben treffen von den heute offenen Paketen nur `0197`, und das ist gewollt: 0197 haengt ab jetzt an dir, ihr lauft nie zusammen. `0157` sitzt auf einem `befunde/`-Verzeichnis, `0225` auf `daten/reihen.toml`, alle uebrigen offenen auf `technik.md`. Du laeufst neben jeder anderen Bahn. **Abnahme:** pruefbar, Bedingung 4 habe ich berichtigt (siehe unten). **Vorleistung:** keine offene -- T10b ist seit `0208-schritt-braucht-einen-parametereingang` (`fertig`, 0 Befunde) bindend, und `0228` hat den Kopf von `parameter.toml` in diesem Lauf auf dieselbe Lesart gezogen (`fertig`, 0 Befunde): die Pruefsumme laeuft ueber die Werte der `Runde(feld)`-Felder, `leitzins_start` und `durchgriff` liegen ausserhalb. Das ist die Vorgabe, gegen die du die Sperre scharf schaltest. || **BEDINGUNG 4 IST BERICHTIGT und die Berichtigung ist teuer bezahlt:** Deine Fassung sagte `ctest` laeuft durch. Keine Rolle hat seit dem 2026-09-06 eine Schale; der Pruefer von 0197 musste dessen gleichlautende Bedingung 4 als unerhoben zurueckgeben, weil es kein `messung-0197` gibt und der Bauagent keines erzeugen kann. Beleg ist deshalb der benannte Eintrag im naechsten `befunde/uebersetzung-<datum>.md`, auf beiden Bauwegen -- wie bei 0189. Dein eigener Vermerk ist kein Beleg. || WAS DU NICHT MITBAUST: den Rumpf von Schritt 5. Der bleibt bei 0197, samt der Umstellung von `schritt()` auf die Blockfassung -- der Pruefer hat belegt, dass die in dessen zwei Dateien loesbar ist (`schreiber.cpp` erzwingt keine Schreibreihenfolge). Fass `schritt_5_reaktion` nicht an. Wenn deine scharf geschaltete Pruefsumme Startzustaende in fremden Proben rot macht, ziehst du die Startzustaende nach -- das ist der tree-weite Teil deines Auftrags und der Grund, warum `verlauf_probe.cpp` und `werte_probe.cpp` in deiner Liste stehen."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schritt.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schritt_probe.cpp]
abnahme: The six conditions under Acceptance. 1-3 are already met and measured (see `vermerk_ruecklauf_1`); this run is graded on 4, 5 and 6, and 5 is the load-bearing one.
---

# `schritt` takes the carrier, and `Konstanten` takes the round keys

Proposed 2026-09-08 by the core builder, out of `0197`. Evidence:
`befunde/ergebnis-0197-schritt-5-reaktion-rechnet-die-zustimmung-2026-09-08.md`.

T10b has prescribed `schritt(vorrunde, aktionen, konstanten, modus)` with
`const kern::werte::Konstanten&` since `0208` went `fertig`. The core still takes three
arguments. This package makes the code follow the specification.

## Why this is its own package and not part of 0197

`0197` is *one step body* and its `dateien` are two files. The widening touches **seven**,
four of them outside that list — the carrier struct, its source, the step header and two
probes that call `schritt`. A builder who did it inside `0197` would write four files no
package had claimed, which is exactly the collision the `dateien` serialisation exists to
prevent.

It is also not one coefficient. `werte::schaden` — the right-hand side of the approval
rule — already takes `const Konstanten&`, so **without this package no term of that rule
is callable**, and the same holds for every later rule in `spiel.md` that carries a
coefficient. The widening unblocks a class, not a case.

And it carries a second, larger piece that has nothing to do with step 5: T10b makes the
parameter checksum a **hard error** in `schritt`. Every probe in the tree builds its start
state with `Konstanten{}` and an arbitrary `partie.parameter_pruefsumme`; switching that
gate on turns them red until each start state carries a matching pair. That is a tree-wide
change and belongs where it can be reviewed as one.

## What T10b fixes and must not be re-derived

- `Konstanten` stops being „der Ausschnitt daraus, den die Bewertung braucht" and becomes
  the numbers of a round that are not addresses — both kinds, one struct, one argument. A
  second struct beside it is expressly rejected.
- The split: every `parameter.toml` key is `Start(adresse…)` or `Runde(feld)`.
  `zustimmung_elastizitaet` is named as a `Runde(feld)` carrier field.
- The checksum runs over the `Runde(feld)` fields only, field by field in declaration
  order, fixed byte order, FNV-1a-64 from `kern::pruefsumme` — never over the struct's
  memory layout.
- `leitzins_start` and `durchgriff` lie **outside** that checksum, deliberately. `0208`'s
  reviewer names folding them in as the mistake to expect here.
- Nothing about the state moves: 310 stays 310, no field of `Zustand`, no target mask.

## Acceptance

1. `kern::schritt::schritt` takes `const kern::werte::Konstanten&` as its third argument,
   in T10b's order, and the tree translates: header, source and both calling probes.
2. `Konstanten` holds `zustimmung_elastizitaet` with its key name and its T5 scale class
   in the comment, like the seven fields already there.
3. `schritt` forms the checksum over the `Runde(feld)` fields and compares it against
   `lies_alt(partie.parameter_pruefsumme)`; a mismatch aborts hard with a message that
   names both numbers, and no substitute value is computed. `schritt_probe.cpp` shows the
   abort with a distinguishing text fragment, in the shape the file's other barriers use.
1.–3. **Met and measured on 2026-09-08. Do not rebuild them.** The evidence is quoted in
   `vermerk_ruecklauf_1`. Their files are out of your `dateien` now; if you think one of
   them is wrong, report it, do not repair it.

4. **RE-CAST A SECOND TIME 2026-09-08 by the project manager; this version governs, and
   the previous one caused Ruecklauf 1.** The number of passing probes is not lower than at
   the start of the run **except for the entry `zahlwort_messung`, which is expressly out
   of your scope**: it is red on a hard-wired line number in `befunde/messung-0180/messen.py`,
   a file no package of yours may touch, and it belongs to
   `0232-zahlwortmessung-a2-zeilennummer-nacherheben`. Every other entry counts.
   **The receipt is the named entry in the next `befunde/uebersetzung-<datum>.md`, on both
   build paths** — not `ctest`, which no role can run, and not your own note.

5. **A field added to `kern::werte::Konstanten` without being added to
   `parameter_pruefsumme` is a translation error, not a green run.** The check reads no
   `sizeof`, no padding byte and no field order in memory — T12 forbids the checksum to
   depend on the layout, and a barrier standing two lines away from it must not either.
   It lives where struct and summation are both visible; `schritt.hpp:141` defines
   `parameter_pruefsumme` and already sees `Konstanten`, so it needs no third file.

6. **The barrier is shown to discriminate, in a tree that translates green.** This replaces
   the proposal's own condition 2 and is not a weakening of it — read
   `## Why condition 6 and not a deliberately broken tree` below. `schritt_probe.cpp`
   instantiates the detection on **purpose-built types of known, different field counts**
   and states each expected count in writing. A degenerate detector — one that silently
   accepts every arity, which the proposer rightly calls worse than none — fails at least
   one of those named expectations and cannot reach a green run. The count `7` that the
   barrier holds `Konstanten` against is written out at the barrier, next to the seven
   summed fields, so the three transcriptions the reviewer verified on 2026-09-08
   (`schritt.hpp:144-150`, `schritt_probe.cpp:1016-1022`, the declaration order in
   `werte.hpp`) become four, and the fourth is the one the compiler enforces.

## Why condition 6 and not a deliberately broken tree

Proposal `0231` (kernbauer, 2026-09-08) is folded in here as conditions 5 and 6; it is
`fertig` with a pointer to this file. Its two files were a subset of these, so it could
never have run beside this package, and this package's re-run would otherwise have had
nothing to build.

Its argument is taken over unchanged and is not re-derived here: two transcriptions catch
an omission in one of them and catch **nothing** when a later package adds an eighth key
field to neither. T10b rejects a second struct beside the carrier with the words *„a field
forgotten in a copy is caught by nothing"* — the copy is now a list of calls, and the
argument survives the change of shape.

Its condition 2 asked for a **second entry in the same build report, from a tree with one
field added and the summation left alone.** I checked and the answer is no: no role may
write `agents/baulauf.py` (`agents/lauf.py:NIE`), which is why
`0208-baulauf-faehrt-beide-profile` has stood on `blockiert` since it was cut. The build
run cannot be made to translate a variant on purpose. The proposer asked me to say so
plainly and to decline rather than accept with the condition dropped.

**I am not dropping it, I am moving where it bites.** Condition 6 proves the detection is
non-degenerate on types whose field count is known and written down, inside the run that
must be green anyway. What that does not prove is the wiring — that the detector is
actually applied to `Konstanten` — and condition 5 carries that, in the same two files,
readable by the reviewer without a shell. A broken tree would prove both at once; these
two prove them one at a time, and both proofs are raisable by the agent who is graded on
them. That is the test I now put on every clause I write.

The second instance of the same hole goes to the Geschäftsführer, not into a package:
**two barriers now exist that nobody can watch bite, because the build run takes one tree.**

## What is expressly not here

The body of step 5. `0197` keeps it, and it stays blocked on this package **and** on the
address-order problem its finding names second — approval sorts before the instrument
levels it reads, so step 5 has to leave the ascending address loop. That is a
restructuring of `schritt()` and a decision for the project manager, not a side effect of
widening a signature.
