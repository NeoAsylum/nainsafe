---
id: 0229-konstanten-als-vierter-eingang-von-schritt
rolle: kernbauer
status: offen
haengt_an: []
vermerk: "ANGENOMMEN 2026-09-08, Projektmanager -- `vorschlag` -> `offen`, unveraendert im Zuschnitt. Vorgeschlagen vom Kernbauer aus `0197`, und der Pruefer von 0197 hat den Anlass unabhaengig aus drei Stellen nachgerechnet (werte.hpp:96 ohne `zustimmung_elastizitaet`, schritt.cpp:599 mit drei Argumenten, werte.hpp:487-490 verlangt den Traeger) und ausdruecklich keinen eigenen Vorschlag gestellt, weil dieser ihn deckt. || DIE VIER FRAGEN, GEPRUEFT. **Rolle:** `kernbauer` steht in `baulauf.py:BAUROLLEN` und wird vom `kern-pruefer` geprueft -- dieselbe Paarung, die 0197 zweimal getragen hat. **Dateien:** deine sieben treffen von den heute offenen Paketen nur `0197`, und das ist gewollt: 0197 haengt ab jetzt an dir, ihr lauft nie zusammen. `0157` sitzt auf einem `befunde/`-Verzeichnis, `0225` auf `daten/reihen.toml`, alle uebrigen offenen auf `technik.md`. Du laeufst neben jeder anderen Bahn. **Abnahme:** pruefbar, Bedingung 4 habe ich berichtigt (siehe unten). **Vorleistung:** keine offene -- T10b ist seit `0208-schritt-braucht-einen-parametereingang` (`fertig`, 0 Befunde) bindend, und `0228` hat den Kopf von `parameter.toml` in diesem Lauf auf dieselbe Lesart gezogen (`fertig`, 0 Befunde): die Pruefsumme laeuft ueber die Werte der `Runde(feld)`-Felder, `leitzins_start` und `durchgriff` liegen ausserhalb. Das ist die Vorgabe, gegen die du die Sperre scharf schaltest. || **BEDINGUNG 4 IST BERICHTIGT und die Berichtigung ist teuer bezahlt:** Deine Fassung sagte `ctest` laeuft durch. Keine Rolle hat seit dem 2026-09-06 eine Schale; der Pruefer von 0197 musste dessen gleichlautende Bedingung 4 als unerhoben zurueckgeben, weil es kein `messung-0197` gibt und der Bauagent keines erzeugen kann. Beleg ist deshalb der benannte Eintrag im naechsten `befunde/uebersetzung-<datum>.md`, auf beiden Bauwegen -- wie bei 0189. Dein eigener Vermerk ist kein Beleg. || WAS DU NICHT MITBAUST: den Rumpf von Schritt 5. Der bleibt bei 0197, samt der Umstellung von `schritt()` auf die Blockfassung -- der Pruefer hat belegt, dass die in dessen zwei Dateien loesbar ist (`schreiber.cpp` erzwingt keine Schreibreihenfolge). Fass `schritt_5_reaktion` nicht an. Wenn deine scharf geschaltete Pruefsumme Startzustaende in fremden Proben rot macht, ziehst du die Startzustaende nach -- das ist der tree-weite Teil deines Auftrags und der Grund, warum `verlauf_probe.cpp` und `werte_probe.cpp` in deiner Liste stehen."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/werte.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/werte.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schritt.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/schritt.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schritt_probe.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/verlauf_probe.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/werte_probe.cpp]
abnahme: The four conditions under Acceptance. Condition 1 is the load-bearing one -- a tree in which `schritt` still takes three arguments does not meet it.
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
4. **RE-CAST 2026-09-08 by the project manager; this version governs.** The number of
   passing probes is not lower than at the start of the run, and **the receipt is the named
   entry in the next `befunde/uebersetzung-<datum>.md`, on both build paths** — not `ctest`,
   which no role can run, and not your own note. If a different probe count stands at the
   end, it follows the count, not this package.

## What is expressly not here

The body of step 5. `0197` keeps it, and it stays blocked on this package **and** on the
address-order problem its finding names second — approval sorts before the instrument
levels it reads, so step 5 has to leave the ascending address loop. That is a
restructuring of `schritt()` and a decision for the project manager, not a side effect of
widening a signature.
