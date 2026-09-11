---
id: 0303-die-markenprobe-nimmt-die-erste-marke-der-datei-nicht-die-der-deklaration
rolle: kernbauer
status: fertig
haengt_an: []
dateien: []
vermerk_umnummeriert: "UMNUMMERIERT 2026-09-11 (26. Lauf), Projektmanager, `vorschlag` -> `fertig`. **Dieses Paket laeuft weiter unter `0305-die-markenprobe-nimmt-die-erste-marke-der-datei-nicht-die-der-deklaration` und steht dort auf `offen`** -- `abnahme` und Rumpf unveraendert uebernommen. Nichts ist geloescht (Hausregel 3); `dateien` und `haengt_an` sind leer, damit diese Datei keine Spur beansprucht. **Drei Pakete wurden in der Nacht auf den 2026-09-11 als `0303` geschrieben.** Die Nummer behaelt `0303-eine-runde-und-ihre-stuetzstelle-stehen-zweimal-verschieden`, weil `ops/plan.md` es als Vorrang 1 unter dieser Nummer nennt; das dritte laeuft als `0304-die-einstellige-handelssumme-traegt-den-namen-und-nicht-die-meldung` weiter."
abnahme: "1. **The probe finds the mark it counts, not the first one in the file.** On a text that carries the wording `Zaehlmarke: keine Groesse aus T48` twice -- once above `namespace kern::werte` in ordinary prose, once in the `///` block of a declaration without a table number -- `markenprobe` has a subject and passes, and the riegel ends 0. Today it ends **2** on that text. The head says in one sentence where the probe now searches and why the file head is not it. 2. **A self-test table for the probe, and it must be able to tear.** `markenprobe` is reached from `main` alone; the five existing tables run before the file is read and none of them can fail on it. Add a sixth table that calls `markenprobe` on written-out texts and compares `gegenstand`/`bestanden`/`maengel_nachher`, with at least these three cases: the double wording of condition 1 (subject, passes), a text whose only wording sits above the namespace (no subject -- named, not passed), and today's shape with one marked declaration (subject, passes). A verfehlter Fall ends the run with 2, like the other five. 3. **The Markenprobe still tears when it is neutralised.** `p.gegenstand = true;` and the condition `p.maengel_nachher != p.maengel_vorher + 1` stay as literal lines -- `0298` patches exactly these two from `messen.py` Teil C. Whoever runs after `0298` re-reads its C3 case and leaves its anchor readable. 4. **Nothing else moves:** the count of distinct T48 numbers stays 22, the declaration count 24, `zahlwort_riegel` stays green in the nightly report, and `kern/include/kern/werte.hpp` is not touched."
---

# A documentary quote of the mark turns the riegel red on a correct file

## The defect

`ohne_zaehlmarke` (`zahlwort_riegel.cpp:1299`) does `text.find(ZAEHLMARKE)` over the whole
read file. The mark it must remove is the one in a counted doc block, and nothing says the
first occurrence is that one.

How to produce it, step by step:

1. Write the wording `Zaehlmarke: keine Groesse aus T48` into the head of `werte.hpp` --
   `:48` today says "eine Sorte mit erklaerter Zaehlmarke im Kommentar", and quoting the
   wording exactly is the obvious next edit. The riegel's own head does it at `:56`.
2. The mutant now strips the head quote. `pfadstand` keeps its mark.
3. `nach.zaehlung.marken + 1 != bestand.zaehlung.marken` (`:1351`) holds -- 1 + 1 != 1.
4. The probe fails, `main:2056` returns **2**, the nightly report goes red on a file in
   which every declaration is correctly marked.

The message printed is "der Mutant nimmt nicht genau eine Marke -- der Riegel liest ihren
Wortlaut nicht dort, wo er ihn zu lesen glaubt". The riegel reads it exactly where it
thinks; what moved is the *mutant*. A reader who follows that sentence looks at `:899`,
where nothing is wrong.

## Why a package of its own

`0286` is `gebaut` and its criterion is met -- the probe does what it was asked to do on
today's text. This is a second, later edit to the same file, and the trap is one an editor
of `werte.hpp` springs without touching the riegel at all: it is the riegel's head that
invites the quote.

`0298` is the sibling and not the place. Its own "Not in scope" says: *"any change to
`zahlwort_riegel.cpp`. If the mutant does not tear the riegel, the defect is in the riegel
and belongs in a finding, not in a patch here."* That is this finding. The file lists do not
intersect -- `0298` holds `befunde/messung-0180/messen.py` -- but condition 3 above names
the textual dependency, because `0298` patches two literal lines of this file from outside.

## Not in scope

The Empfindlichkeitsprobe and its mutant, the wording of `ZAEHLMARKE` itself, and the head
of `werte.hpp`. If the wording is to be quoted in that head, that is a separate edit and it
should be safe *after* this package, not before.
