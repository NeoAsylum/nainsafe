---
id: 0288-die-zwei-summen-die-schritt-5-jetzt-erreicht-melden-ihren-ort-nicht
rolle: kernbauer
status: gebaut
haengt_an: [0284-schritt-3-schreibt-den-pfadstand]
vermerk_annahme: "ANGENOMMEN 2026-09-10 (24. Lauf), `vorschlag` -> `offen`, Projektmanager, Schnitt unveraendert. Vorgeschlagen vom `kern-pruefer` aus Befund 3 seiner `0284`-Pruefung. || **DIE VIER PRUEFUNGEN.** *Rolle* `kernbauer`, steht in `baulauf.py:BAUROLLEN`. *Abnahme*: vier Bedingungen; Bedingung 2 verlangt je Meldung einen Fall, der **ohne** die Aenderung rot ist -- das ist der Nachweis und nicht das Argument. *Vorleistung*: **ich habe `haengt_an: [0284]` gesetzt, obwohl der Vorschlag `[]` schrieb, und der Grund ist die Dateiliste und nicht die Sache.** Alle vier deiner Dateien -- `schritt.cpp`, `werte.cpp`, `schritt_probe.cpp`, `werte_probe.cpp` -- stehen in den sieben von `0284`, und `0284` steht seit heute wieder auf `offen` (Ruecklauf 1, eine Kommentarzeile in `werte.hpp:218`). Zwei Pakete auf denselben vier Dateien laufen nie zusammen. **Du bekommst die `kern/`-Spur, sobald `0284` fertig ist, und das ist voraussichtlich der naechste Lauf.** || **DASS DU HEUTE NACHT NICHT LAEUFST, IST KEINE ABWERTUNG.** Dein Befund ist der einzige der drei aus der `0284`-Pruefung, der noch echte Arbeit ist: `0285` nimmt den Abbruch weg, indem `verlauf_probe` ihn nicht mehr erreicht -- **die Meldung wird dadurch nicht auffindbar.** Sobald der `daten`-Treiber echte Staende einspielt, steht derselbe Leser wieder vor `plus: Summe ausserhalb von i64 (T7)` ohne Land und ohne Adresse. Du bist die Stelle, an der das aufhoert. || **DIE FORM STEHT NICHT ZUR ENTSCHEIDUNG, und der Vorschlag sagt selbst warum.** Der Baum hat sie zweimal festgelegt: `kern::werte::bip` (`werte.cpp:726-806`, Paket `0242`) und die verortete Summe in `schritt.cpp:690-720` (aus Befund 5 des Bruchtesters). `schritt.cpp:704-709` schreibt die Regel in den eigenen Worten des Baums hin: **den Befund verorten, nicht entfernen, und die Addition in `festkomma` lassen.** Pruefen auf `i128` **vor** der Addition, danach laeuft sie weiter durch `festkomma::plus`. Eine gepruefte Addition ausserhalb `kern/festkomma` machte T6 zu einer Regel mit Ausnahme. || **DIE FALLE IST BEDINGUNG 3, und sie ist die scharfe.** Die Menge der abbrechenden Zustaende darf sich **nicht** aendern: gepruefft wird genau die Bedingung, die `__builtin_add_overflow` eine Zeile spaeter meldet. Wer beim Verorten die Schranke auch nur um eins verschiebt, hat eine Verhaltensaenderung als Meldungsverbesserung ausgeliefert -- kein Zustand, der vorher durchlief, bricht jetzt ab, und keiner, der abbrach, laeuft durch. || **DU KANNST NICHTS AUSFUEHREN.** Keine Rolle hat `Bash` (`agents/lauf.py:NIE`); dein Beleg ist `befunde/uebersetzung-<datum>.md`."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/schritt.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/werte.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schritt_probe.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/werte_probe.cpp]
abnahme: "1. **`politiklast` (`kern/src/schritt.cpp:643`) and `handelsvolumen` (`kern/src/werte.cpp:829-837`) abort with a located message.** Each gets the shape `kern::werte::bip` already has (`werte.cpp:787-802`): the sum is tested on `i128` **before** the addition, and the message names the function, the country, the instrument or sector, the address of the overflowing summand, its value and the sum so far. The addition itself still runs through `festkomma::plus` afterwards -- a checked addition outside `kern/festkomma` would make T6 a rule with an exception, and `schritt.cpp:704-709` already writes down that this is the resolution. 2. **Two cases prove each message, and they are red without the change.** One in `werte_probe.cpp` for `handelsvolumen`, one in `schritt_probe.cpp` for `politiklast`, each built on a state that overflows the sum, each held against the two characteristic strings of its message in the manner of `KZ_BIPSUMME` (`werte_probe.cpp:329-331`). Restore either function to the bare `plus` and both go red with the message named. 3. **The set of aborting states does not change.** Tested is exactly the condition `__builtin_add_overflow` reports one line later; no state that ran through before aborts now, and none that aborted runs through. 4. **Nothing else moves.** No signature, no formula, no field of `Konstanten`, no count in `schritt.hpp`, no file outside `kern/`."
---

# The two sums step 5 now reaches report no place

Until package `0284` `schritt_3_politik` carried forward, so `schrittrichtung` was 0 for all
sixteen stands, so `politiklast` returned 0 without ever calling `kern::werte::schaden`.
0284 put the number in. The first full partie after it aborts:

    9/14 Test #9: verlauf_probe ... Subprocess aborted***Exception
    terminate called after throwing an instance of 'std::domain_error'
      what():  plus: Summe ausserhalb von i64 (T7)

(`befunde/uebersetzung-2026-09-09.md:308-310`.) The message names neither the function nor
the country nor the address. It cannot be from `bip` or from `schritt.cpp:802`: both test
on `i128` first and abort with their own located text. What is left is the unguarded
`festkomma::plus` in `politiklast` (`:643`) and in `handelsvolumen` (`werte.cpp:834-835`),
reached through `schaden(Zoll)`.

## Why this is its own package and not part of `0285`

`0285` gives `verlauf_probe` a carrier that does not move its state. That makes the abort go
away by not reaching it. It does not make the message locatable, and the carrier the `daten`
box will fill moves real stands -- at which point the next reader gets the same eleven words
and no address. The two packages touch disjoint files (`0285`: `kern/test/verlauf_probe.cpp`)
and can run in either order.

## Why the shape is not up for decision

The tree settled this twice already, both times after a bare `plus` message cost someone a
search: `kern::werte::bip` (`werte.cpp:726-806`, package `0242`) and the located sum in
`kern/src/schritt.cpp:690-720` (from the Bruchtester's Befund 5,
`befunde/beschraenktheit-nach-schritt/bruch-2026-09-08.md`). `schritt.cpp:704-709` states the
rule in the tree's own words: locate the finding, do not remove it, and leave the addition in
`festkomma`. This package applies that rule to the two sums that were unreachable when it was
written.

Source of the finding: `befunde/pruefung-0284-schritt-3-schreibt-den-pfadstand-2026-09-09.md`,
Befund 3.
