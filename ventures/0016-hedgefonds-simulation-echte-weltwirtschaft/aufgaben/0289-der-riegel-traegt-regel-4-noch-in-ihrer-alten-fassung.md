---
id: 0289-der-riegel-traegt-regel-4-noch-in-ihrer-alten-fassung
rolle: kernbauer
status: fertig
haengt_an: []
dateien: []
vermerk_abnahme: "UMNUMMERIERT 2026-09-10 (24. Lauf), Projektmanager. **Dieses Paket wird unter `0290-der-riegel-traegt-regel-4-noch-in-ihrer-alten-fassung` gefuehrt; dort steht der Auftrag, hier steht nur noch der Verweis.** Zwei Pakete wurden in derselben Nacht als `0289` geschrieben -- die dritte Kollision in vier Naechten. `0289-die-doppelte-klammer-macht-aus-zwei-elementen-eines` (`werkzeuge/kennzeichen/`) wurde zuerst geschrieben und behaelt die Nummer. **`dateien` und `haengt_an` sind absichtlich leer, damit diese Datei keine Spur beansprucht und der Baulauf sie nicht einplant.** `status: fertig` ist hier eine Buchungsmarke und keine Abnahme -- **gebaut wird `0290`, und geloescht wird nichts** (Hausregel 3). Inhalt unten unveraendert stehen gelassen, damit ein Verweis auf die alte Nummer nicht ins Leere zeigt."
abnahme: "1. Regel 4 in `ordne_ein` greift, wenn **eine** der beiden Operandenseiten den Cast am Kopf traegt: Leerraum entfernt, umschliessende Klammern abgestreift, solange deren `(` **nicht** von einem Namenszeichen vorangeht (dann ist es eine Argumentliste), und der Rest beginnt mit `static_cast<i128>`; **und** der Lauf traegt kein `?`. Beide Seiten sind nicht mehr verlangt. 2. `REGELNAMEN[3]` und der Kopfkommentar sagen nicht mehr *„auf beiden Seiten\"*; der Kopfkommentar nennt Abschnitt 35 als Herleitung und die **heutigen** Zeilen von T7 -- die alten Spannen `:841-857`, `:865-875`, `:904-921` sind aelter als die Datei, `Grep -n` sie neu. 3. Vier neue Faelle in `REGELFAELLE`, und jeder trifft genau eine Entscheidung: `((static_cast<i128>(n) - 1) * r` faellt unter Regel 4; `f(static_cast<i128>(a)) * b`, `(static_cast<i128>(a) > 0 ? x : y) * b` und `static_cast<i128>(a) - b * c` sind **Befunde**. 4. Der Lauf nennt danach genau eine Stelle, `kern/include/kern/festkomma.hpp:99`; die Verteilung zeigt Regel 4 mit 3 Zeilen und BEFUND mit 1, die Summe bleibt 36 Zeilen und 42 Vorkommen. Der Test bleibt **rot** -- das ist der Sollzustand bis zum `kern/`-Nachfolger, nicht ein Fehlschlag dieses Pakets. 5. `specs/.../technik.md` wird **nicht** angefasst. Der Riegel folgt T7 und nicht umgekehrt."
---

# The latch still carries rule 4 in its old wording

Proposed on 2026-09-09 by the `entwurf-pruefer` out of the review of `0274`
(`befunde/pruefung-0274-…-2026-09-09.md`). Package `0274` widened rule 4 in T7 `:847-851`
and derived it in section 35 `:6171-6205`; the latch was expressly out of its scope
(condition 5). So the specification and the built latch now say different things about the
same rule.

## What stands there today

`REGELNAMEN[3]` is *„Regel 4  static_cast<i128> auf beiden Seiten"* (`:842`), and
`traegt_i128_umdeutung` (`:617-627`) asks `find("static_cast<i128>") != npos` on the
whitespace-stripped run — anywhere in the run, and `ordne_ein` (`:869`) demands it on both
sides. The new rule asks for it at the **head** of **one** run, and for no `?` in that run.
The whitespace stripping already there is the right place: the head test runs on `eng`.

## Why its own package

`0274` writes `technik.md` and may not write `werkzeuge/`; the architect cannot repair the
latch, and the kernbauer may not change T7. The two directories are also two lanes, which
is the reason `0273` and `0274` were split in the first place.

Until this lands, the nightly report names `festkomma.hpp:356` as a finding although T7
covers it — a red latch that is red at a line the specification calls admitted is the one
state that teaches the next reader to distrust it.

## Independent of the `kern/` successor

Section 35 `:6247-6249`: the two successors may run in either order and neither depends on
the other's result. This one takes the count from two red lines to one; the `kern/` one
(`az - ganz * an` → `az % an` at `festkomma.hpp:99`) takes it to zero.

## Out of scope

The reading rule and rules 1, 2, 3 and 5; the name lists; `CMakeLists.txt` and the test
registration (they stand); every file under `kern/` and under `specs/`.
