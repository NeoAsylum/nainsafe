---
id: 0304-die-einstellige-handelssumme-traegt-den-namen-und-nicht-die-meldung
rolle: kernbauer
status: offen
haengt_an: [0299-the-four-sums-left-in-werte-still-report-no-place]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/werte.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/werte_probe.cpp]
vermerk_annahme: "ANGENOMMEN 2026-09-11 (26. Lauf), Projektmanager, `vorschlag` -> `offen`, Zuschnitt und `abnahme` unveraendert. Vorgeschlagen vom `kern-pruefer` aus Befund 1 seiner `0288`-Pruefung. **Uebernommen aus `0303-die-einstellige-handelssumme-traegt-den-namen-und-nicht-die-meldung`; die alte Datei steht als Stummel mit `dateien: []` und beansprucht keine Spur.** Drei Pakete wurden in der Nacht auf den 2026-09-11 als `0303` geschrieben -- die vierte Nummernkollision in fuenf Naechten. **Die Nummer behaelt `0303-eine-runde-und-ihre-stuetzstelle-stehen-zweimal-verschieden`, und ausnahmsweise nicht nach der Aenderungszeit:** `ops/plan.md` nennt es als Vorrang 1 **mit dieser Nummer**, und ein umnummeriertes Vorrangpaket macht den Plan des Betreibers auf eine Datei zeigen, die es nicht gibt. || **DIE VIER PRUEFUNGEN.** *Rolle* `kernbauer`, steht in `baulauf.py:BAUROLLEN`. *Abnahme* vier Bedingungen, Bedingung 2 ist eine Rotprobe und Bedingung 3 haelt die Menge der abbrechenden Zustaende fest -- das ist die Form, die `0288` getragen hat. *Vorleistung* `0288` ist in diesem Lauf `fertig`. *Dateien* `kern/src/werte.cpp` und `kern/test/werte_probe.cpp`. || **DIE `haengt_an` IST EINE REIHENFOLGESPERRE UND KEINE FACHLICHE VORLEISTUNG. Du brauchst von `0299` nichts.** Ihr fasst beide dieselben zwei Dateien an, und eine Datei ist eine Spur. `0299` bekommt sie, weil es Vorrang 5 des 16. Plans ist und `0288` zu Ende fuehrt; es wird heute mit `0288` startbereit. **Ohne diese Sperre koenntest du `werte.cpp` in genau dem Lauf umschreiben, in dem der `kern-pruefer` `0299` daran misst** -- Bau und Pruefung rechnen getrennte `belegt`-Mengen, ein Paket unter Pruefung haelt seine Datei nicht. **Sie faellt mit `0299` auf `fertig`, nicht mit seiner Lieferung.** || **MISS AM TEXT, NICHT AN DER ZEILENNUMMER.** `0299` raeumt vor dir in derselben Datei und nimmt sich die vier uebrigen blanken Summen vor; jede Zeilenzahl in deiner `abnahme` ist am Stand vom 2026-09-11 gemessen."
abnahme: "1. **The one-place `handelsvolumen` (`kern/src/werte.cpp:911-923`) aborts with a located message.** Same shape as the two-place sibling package 0288 gave it (`pruefe_handelssumme`, `werte.cpp:475-498`): the sum is tested on `i128` **before** the addition, the addition still runs through `festkomma::plus` afterwards, and the message names the function, the Gebiet, the sector whose sum overflows the total, that sector's sum and the running sum. There is no address here -- the summand is `handelsvolumen(z, land, sektor)` and not a cell -- so the sector takes the address's place, in the manner `schritt.cpp:645-648` already writes down for `politiklast`. 2. **One case proves the message, and it is red without the change.** In `werte_probe.cpp`, built like `probe_handelsdecke` (`:2432-2535`): a state whose two sector sums each stay inside `i64` while their total does not, held against the two characteristic strings of the new message and against the absence of `\"plus: Summe\"` and of `kern::meldung::MARKE`. Restore the bare `plus` and it goes red with the message named. Because the eight cells per sector are individually settable, the edge is reachable to the unit -- carry a positive control on the edge that still computes, as `probe_handelsdecke` does. 3. **The set of aborting states does not change.** Tested is exactly the condition `__builtin_add_overflow` reports one line later; no state that ran through before aborts now, and none that aborted runs through. The two-place calls inside the loop keep their own guards and their own messages. 4. **Nothing else moves.** No signature, no formula, no file outside the two named, and the `Riegel` bookkeeping of `werte_probe.cpp` (`:180-192`, `:451`) grows by whatever the new entry needs and by nothing else."
---

# The one-place trade sum carries the name and not the message

Package 0288 gave the two-place `handelsvolumen` a located abort. The one-place
aggregation right underneath still adds through a bare `plus`:

    // kern/src/werte.cpp:918-922
    i64 summe = 0;
    for (const Sektor sektor : SEKTORLISTE_HANDELBAR) {
        summe = plus(summe, handelsvolumen(z, land, sektor));
    }

Two sector sums that each stay inside `i64` while their total does not -- `2^62` per
sector suffices, and every one of the sixteen cells is settable -- abort with
`plus: Summe ausserhalb von i64 (T7)`: no Gebiet, no sector, no numbers. Reachable through
`waehrungswert` (`werte.cpp:722`), which `werte.cpp:580` calls for a currency position.

## Why this is its own package and not part of 0288

0288's criterion cited `werte.cpp:829-837` -- the two-place body. Its guard is in place and
proved; the package is done. This is the sum one function below it, with its own summand
kind (a computed sector sum, not a cell), its own message, and its own probe.

## Why it is worth a run at all

Before 0288 the bare wording was merely uninformative. Now it is **misleading**: the located
message names `kern::werte::handelsvolumen`, so a reader who greps that name against a bare
abort concludes the abort cannot be from `handelsvolumen` -- and the gap is exactly there.
That is the same trap package 0288 was written to close, one level up.

Source of the finding: `befunde/pruefung-0288-die-zwei-summen-die-schritt-5-jetzt-erreicht-melden-ihren-ort-nicht-2026-09-11.md`,
Befund 1. Befund 2 of the same check lists the remaining bare accumulators
(`werte.cpp:745, 750, 764, 776, 992, 995, 1145`); they are not part of this package.
