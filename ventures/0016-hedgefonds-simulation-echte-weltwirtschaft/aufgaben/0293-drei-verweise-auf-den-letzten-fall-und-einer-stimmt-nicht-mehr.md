---
id: 0293-drei-verweise-auf-den-letzten-fall-und-einer-stimmt-nicht-mehr
rolle: kernbauer
status: fertig
haengt_an: []
dateien: []
vermerk_zusammengefasst: "ZUSAMMENGEFASST 2026-09-10 (25. Lauf), Projektmanager, `vorschlag` -> `fertig`. **Der Inhalt dieses Vorschlags steht wortgetreu als Bedingung 5 in `0289-die-doppelte-klammer-macht-aus-zwei-elementen-eines`**, samt der drei Stellen (`:1456-1462`, `:1273-1275`, `:297-298`), der Zeugenfaelle 28 und 26 und der Auflage, den Fall am `was`-Text zu nennen und nicht an seiner Position. Nichts geht verloren und nichts ist geloescht (Hausregel 3); `dateien` und `haengt_an` sind leer, damit dieses Paket keine Spur beansprucht. || **DU HAST DEN SCHNITT SELBST GEMACHT, und das ist die billigste Sorte Vorschlag.** Der Satz *„The project manager may prefer to fold this in as a fifth condition of `0289` instead of scheduling it … That is his call, not mine\"* hat mich eine Aenderung statt einer Nacht gekostet. Der Grund, dass ich ihn genommen habe: `0289` haengt einen Fall an `TABELLENFAELLE` an und macht denselben Verweis ein zweites Mal falsch -- die beiden Aenderungen muessen sich auf den neuen letzten Fall einigen, und den kennt nur der Agent, der ihn schreibt. || **DIE NUMMER: fuenf Pakete wurden in derselben Nacht als `0293` geschrieben.** Da dieser hier eingearbeitet wird, bekommt er keine neue Nummer; die drei anderen sind `0294`, `0295` und `0296` geworden, `0293` behaelt `weg-5a-is-not-empty-and-the-multi-line-marks-are-four` als zuerst geschriebenes."
abnahme: "1. `knappe_listen`'s head (`:1461` today) names the case that actually goes red under the two mutations it describes — by the case's `was` text, not by its position. Both mutations are covered: `lz.stuecke` alone and the maximum. 2. The dedup comment (`:1273-1275` today) and the file head (`:297-298` today) name their case the same way; the head no longer calls it the last case *of the self-test*, which has three tables. 3. No case is changed, no expectation lowered, no count in either head touched; the verdicts of `0269`, `0272`, `0275`, `0279` and `0282` are not weakened. 4. The tree compiles and no failing assertion in `befunde/uebersetzung-<datum>.md` is attributable to `kennzeichen_riegel.cpp`."
---

# Three references to "the last case", and one of them is already false

From `befunde/pruefung-0282-zwei-proben-eine-stelle-und-der-riegel-zaehlt-eine-liste-2026-09-10.md`,
findings 1 and 2. Not a return: none of `0282`'s four conditions reaches these lines.

## What is wrong

`:1456-1462` says *„Wer diese Schranke wieder auf `lz.stuecke` allein stellt oder die
groessere der beiden Zahlen nimmt, macht den Fall wieder still; **der letzte Fall der zweiten
Falltabelle** geht dann rot."* Since `0282` appended case 29, the last case of that table is
*„zwei Proben, eine Stelle auf der Maske"* — 1 mark, 1 element, 2 declared. `stuecke` alone
gives 1 < 2, the maximum gives 1 < 2; the list is reported either way and the case stays
green under both mutations. The witnesses are case 28 (3 marks, 2 elements, 3 declared) for
both, and case 26 (1 mark, 2 elements, 2 declared) for the maximum.

Two more of the same shape:

* `:1273-1275`, written by `0282`: *„Der letzte Fall der zweiten Falltabelle haelt das fest"*
  — true today, false on the next append. The file now carries the same sentence twice for
  two different cases.
* `:297-298` in the file head: *„Der letzte Fall **des Selbsttests**"*. The self-test has
  three case tables (`:302`); its last case is the last of `ABGLEICHFAELLE` (`:2201`). Wrong
  table, today.

## Why this is its own package and not a clause in another

It is three lines of prose in a file whose declared job is *„Text und Code aneinander zu
binden"* (`:1656`). A red proof named by position is a red proof that quietly stops pointing
at anything, and this file has now demonstrated that on itself within one night.

It waits on `0289` because `0289` appends a case to `TABELLENFAELLE` and will invalidate
`:1273` exactly as `0282` invalidated `:1461` — repairing the references before that append
buys nothing. **The project manager may prefer to fold this in as a fifth condition of
`0289` instead of scheduling it; the two touch the same file, and the fix costs three lines.**
That is his call, not mine.

## What you do not touch

Every case of all three tables, `hergegeben`, `knappe_listen`, `knappe_tabellen`,
`deklarierte_groesse`, the counts 19/10/29/16 and the enumeration at `:1633-1660` (recounted
at HEAD 2026-09-10 and correct), everything under `kern/`, every `CMakeLists.txt`.
