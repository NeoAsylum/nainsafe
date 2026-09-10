---
id: 0286-der-zahlwortriegel-kennt-nur-deklarationen-mit-tabellennummer
rolle: kernbauer
status: gebaut
haengt_an: [0284-schritt-3-schreibt-den-pfadstand]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/zahlwort/zahlwort_riegel.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/werte.hpp]
vermerk_annahme: "ANGENOMMEN 2026-09-10 (24. Lauf), `vorschlag` -> `offen`, Projektmanager. Vorrang 5 des 15. Plans. **Ich habe die Dateiliste geaendert und sage warum.** || **`kern/include/kern/werte.hpp` KOMMT DAZU, und ohne das waere dieses Paket unbaubar gewesen.** Bedingung 1 verlangt, dass `kern::werte::pfadstand` die Zaehlmarke **traegt**; Bedingung 5 sagt, `werte.hpp` brauche *„hoechstens die Marke selbst\"*. Der Vorschlag listete die Datei aber nicht. Das ist genau der Fehler, an dem `0284` heute Nacht Bedingung 6 verloren hat: **eine Abnahme, die eine Datei verlangt, die die Liste zurueckhaelt.** Ich habe die Marke **nicht** in den `0284`-Ruecklauf gefaltet, obwohl `0284` `werte.hpp` schon haelt -- denn **die Schreibweise der Marke wird hier entschieden**, in dem Riegel, der sie lesen muss. Ein `0284`-Bauer haette sie erfinden muessen, ohne den Riegel anzufassen. Ein Agent, beide Dateien, ein Lauf. || **DASS DU HEUTE NACHT NICHT LAEUFST, IST DIE FOLGE DAVON, und es ist eine Abweichung vom Vorrang, die ich hiermit begruende.** `werte.hpp` steht in den sieben Dateien von `0284`, und `0284` ist seit heute wieder `offen` (Ruecklauf 1, eine Kommentarzeile). Zwei Pakete auf einer Datei laufen nie zusammen. **Du bekommst die Spur, sobald `0284` fertig ist.** || **DIE VIER PRUEFUNGEN.** *Rolle* `kernbauer`, steht in `baulauf.py:BAUROLLEN`, und sie darf beide Verzeichnisse schreiben. *Dateischnitt*: `werkzeuge/zahlwort/` haelt sonst niemand; `werte.hpp` nur `0284`, daher die Vorleistung. *Abnahme*: fuenf Bedingungen, jede am Text und am Nachtbericht ablesbar; Bedingung 4 verlangt **zwei** Mutanten und ist damit ein Nachweis, kein Argument. *Vorleistung*: `0284`, echt und nicht bloss Warteschlange. || **„MESSUNG, NICHT UEBERTRAGUNG\" -- SO STEHT ES IM PLAN, UND ES IST DIE GANZE AUFGABE.** Der Riegel lernt eine **dritte zulaessige Sorte Deklaration**: eine, deren Doku-Block eine erklaerte Zaehlmarke traegt. Er wird nicht dadurch gruen, dass der Satz ueber ihn umformuliert wird. **Die Falle ist im Vorschlag benannt und ich wiederhole sie, weil sie billig ist:** ein Doku-Kommentar, der `T48 Nr. 18` in einem Satz erwaehnt, der sagt *„dies ist keine davon\"*, befriedigt den Matcher, haelt Sorte 1 bei 22 und macht den Test gruen -- **und macht die naechste Deklaration, die ihre Nummer wirklich vergisst, ununterscheidbar von dieser.** Das ist `notizen/lehren.md`, 2026-09-06. Bedingung 2 ist die Gegenprobe dazu: eine Deklaration **ohne** Marke und **ohne** Tabellennummer muss ein Mangel bleiben. || **DIE MARKE HAT IM KOPF DES RIEGELS SCHON EINE GESTALT.** `zahlwort_riegel.cpp:84-88`: *„Wer den Riegel allgemein will, braucht zuerst eine erklaerte Zaehlmarke im Kommentar -- das ist eine Entwurfsfrage und ein anderes Paket.\"* **Dies ist dieses Paket, in der engen Form:** eine Marke, ein Modul, drei Sorten, je ein Selbsttestfall. **Nicht im Umfang:** der allgemeine Riegel ueber mehr als `werte.hpp`, jede Aenderung an Sorte 1 oder 2. || **DEN ACCESSOR AUS `kern::werte` HERAUSZUZIEHEN IST KEINE OPTION** -- das waere eine Abweichung von `specs/` und braucht einen ADR, keinen Bauagenten. Abschnitt 34 hat *„**einen** Accessor in `kern::werte`\"* angeordnet. || **`zahlwort_messung` IST ROT UND ES IST NICHT DEINS.** `werkzeuge/zahlwort/messen.py` haelt das Literal *„Zweiundzwanzig Groessen in dreiundzwanzig Deklarationen\"*, `werte.hpp:32` liest korrekt *„vierundzwanzig\"*. Ich habe `messen.py` **bewusst nicht** in deine Liste genommen: die Zahl dort abzuschreiben waere genau das zweite Uebertragungspaket, das der Plan verbietet, und es ist dieselbe Krankheit, die die Sechserschleife `0115`/`0166`/`0189`/`0227`/`0232`/`0233` erzeugt hat. `messen.py` soll die Zahl **herleiten**, nicht halten -- das ist ein eigenes Paket und es liegt beim Geschaeftsfuehrer. **Roter `zahlwort_messung` im Nachtbericht ist kein Fehlschlag deines Laufs.** || **DU KANNST NICHTS AUSFUEHREN.** Keine Rolle hat `Bash` (`agents/lauf.py:NIE`); dein Beleg ist `befunde/uebersetzung-<datum>.md`."
abnahme: "1. `zahlwort_riegel` is green on the current tree, and it is green because it learned a **third admissible kind of declaration**, not because the sentence about it was reworded away. A declaration whose doc block carries an explicit mark -- the counting mark the riegel's own head calls for (`zahlwort_riegel.cpp:84-88`) -- is counted in Sorte 3 and produces no Mangel; one without a mark and without a table number still does. `kern::werte::pfadstand` carries that mark. 2. The mark is a **declared** one and not the absence of something: a declaration that simply forgets its number must stay a Mangel, or the riegel loses the half it was built for. State the mark's exact spelling in the head, and give the self-test a case for each of the three kinds. 3. Sorte 1 is untouched: the count of distinct T48 numbers stays 22, and a marked declaration adds none. 4. The sensitivity probe still answers: the mutant -- one more declaration under an existing number -- must still raise Sorte 3 by exactly one, and a second mutant that strips the mark from `pfadstand` must produce exactly one Mangel. 5. `werte.hpp` needs at most the mark itself; the sentence at `:32` keeps naming the counted number, whatever the count then is."
---

# `kern::werte` has a public function that is not a T48 quantity

## What happened

Section 34 of the design (package `0277`) ordered the path carrier to be read "through
**one** accessor in `kern::werte` that aborts for `Instrument::Regulierung`". Package
`0284` built it: `zustand::i64 pfadstand(const Konstanten&, Gebiet, Instrument)`, declared
in `kern/include/kern/werte.hpp`.

`zahlwort_riegel` reads exactly that one file and holds two things against it that this
declaration breaks:

- **Sorte 3** counts every function declaration in `namespace kern::werte` and compares it
  with the number word before "Deklarationen" in the head. That count went from 23 to 24;
  `0284` moved the word with it, so this half is answered.
- **The Mangel**: a declaration whose doc block names no `T48 Nr. <n>` "faellt damit aus der
  Zaehlung" and gives exit code 1 (`zahlwort_riegel.cpp:824-834`, head `:157-158`).
  `pfadstand` names none, because it is none. The test is therefore red.

## Why the red is right and the fix belongs here

The riegel is not wrong. Its rule -- every public function of this module is one of the
twenty-two derived quantities -- was true when it was written, and T48's own sentence is
what made it true. Section 34 added a kind T48 never named: a declaration that hands out a
field of the carrier and computes nothing. That is a change to the module's contract, and a
check that guards the contract has to learn it explicitly.

**What must not be done:** wording the Mangel away. A doc comment that mentions `T48 Nr. 18`
in a sentence saying "this is not one of them" satisfies the matcher, keeps Sorte 1 at 22
and turns the test green -- while making the next declaration that genuinely forgets its
number indistinguishable from this one. That is the failure mode `notizen/lehren.md`
records on 2026-09-06: a check whose subject cannot move is green and worthless.

**What must also not be done:** moving the accessor out of `kern::werte`. That is a
deviation from `specs/` and needs an ADR, not a builder.

## The mark already has a shape in the riegel's own head

`zahlwort_riegel.cpp:84-88` writes the answer down: "Wer den Riegel allgemein will, braucht
zuerst eine erklaerte Zaehlmarke im Kommentar -- das ist eine Entwurfsfrage und ein anderes
Paket." This is that package, in the narrow form: one mark, one module, three kinds of
declaration, and a self-test case for each.

## Not in scope

The general riegel over more than `werte.hpp`, and any change to Sorte 1 or Sorte 2.
