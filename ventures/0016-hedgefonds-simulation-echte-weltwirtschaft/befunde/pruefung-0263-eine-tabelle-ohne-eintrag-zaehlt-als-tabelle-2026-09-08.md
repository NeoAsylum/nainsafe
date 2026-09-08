---
typ: pruefung
paket: 0263-eine-tabelle-ohne-eintrag-zaehlt-als-tabelle
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "All five conditions read at HEAD 6f2ec03; self-test case 14 is the input on which the new bar fails, and the green ctest run is itself the per-table receipt."
befunde: 2
---

# 0263 — geprueft

## Condition 1 — non-zero on an empty table, message names probe and line

`main:1758-1780`: `leere_tabellen(zahlen)` non-empty → `return 2`, printing `p.name` and
`p.tabellen[…].zeile` per table (`:1766-1767`). The row is recorded in
`lies_verzeichnisse:818-821`, **before** the entry loop at `:823`, so a table with zero
groups still stands in `zahlen`. `tz.eintraege = gruppen.size()` comes from
`eintragsgruppen` at `:811`; a `return false` inside the entry loop aborts the run anyway,
so count and pushed entries cannot diverge on a green path. The guard sits ahead of all
three zero checks (`:1782`, `:1791`, `:1801`) — the precise message reaches the reader first.

## Condition 2 — bait and the neighbour that must stay silent

Case 14 (`:1269-1273`): `RIEGEL_OHNE_ZUSTAND = {{ {Eins, "n", "w", {"alpha"}} }}`, expects
`leer` 1. Walked by hand: `finde_zuweisungen` returns the outer `{`, `gruppen_in` yields
four groups, and `traegt_qualifizierten_namen` searches `m.find("::", g.auf)` — the only
`::` in that text (`std::array`) sits *before* every `g.auf`, so no group qualifies,
`eintragsgruppen` is empty, `tz.eintraege = 0`. Case 15 (`:1277-1281`) is the same text
with `R::` and expects `leer` 0. Case 16 (`:1287-1294`) puts two tables in **one** probe
and expects `leer` 1 with `stumm` 0 — that is what shows the bar means the table and not
the probe. `selbsttest_verzeichnis:1388-1399` additionally asserts the reported table
carries a line; `zerlege` starts at `zl = 1` (`:343`), so a line is never 0 for real content.

## Condition 3 — the count is deleted, not replaced

`:32-33` now reads „seither steht das erste Verzeichnis nicht mehr allein". No number, and
the argument (find by name, not by path) still carries through `:33-37`. Nothing says „drei".

## Condition 4 — no built-in count, no probe file name

Grepped the file for `_probe`, `.cpp`, `.hpp`: only the synthetic `probe_a.cpp`,
`probe_b.cpp`, `kern_a.cpp` of the self-test (`:1320`, `:1325`, `:1458`) and the extension
test `:1528`. `TABELLE` stands once (`:761`); the tree is reached through
`VERZEICHNISBAUM = "test"` (`:1620`).

## Condition 5 — green at HEAD, and the report is stamped

`uebersetzung-2026-09-08.md`: build Code 0 (`:32`), `kennzeichen_riegel` Passed in the whole
tree (`:157`) and in its own (`:446`). The report stamps `HEAD zu Beginn: 6f2ec03` and
`HEAD am Ende: 6f2ec03` (`:115`, `:141`) — the commit of this package, so it saw the
reviewed file. Two red tests, `belegstellen_wortabstand` and `belegstellen_kopfzahlen`;
their finding lines name `belegstellen_riegel.cpp`, `SATZFAELLE`, `ZITATFAELLE`,
`NAMENSFAELLE`, `spiel.md` (`:118-140`) and are declared measured at the older stand
`2f2f79f` (`:142`). No line of `kennzeichen_riegel.cpp` in that output.

**The green run is the receipt.** Exit 0 is reachable only past `:1759`, so a passing
`kennzeichen_riegel` proves each of the three tables at HEAD — `werte_probe:361`,
`schritt_probe:443`, `festkomma_probe:286`, all three confirmed by grep — yielded at least
one entry. With case 14 as the input on which it fails, the pair is complete.

## Finding 1 — three illustrative „drei" remain, outside condition 3

`:107-109`, `:947` and `:1728` still read „Fallen … drei Verzeichnisse auf zwei". These are
scenarios, not assertions of the present stock, and condition 3 named `:32-33` alone.
Recorded, no Ruecklauf.

## Finding 2 — the same blindness one level further down

`leere_tabellen` fires at **zero** entries per table. A table yielding *fewer* entries than
it holds stays silent: no number reaches zero, no probe is stumm, no table is empty. Not
reachable today — all three tables declare `std::array<…, 1>` (`werte_probe:360`,
`schritt_probe:443`, `festkomma_probe:286`), so „one entry lost" and „table empty" are the
same event. It becomes reachable the day `RiegelOhneZustand::Anzahl` grows, which each
probe's own `static_assert(RIEGEL_OHNE_ZUSTAND.size() == …Anzahl)` (`werte_probe:371`)
guarantees. Proposal `0267`.
