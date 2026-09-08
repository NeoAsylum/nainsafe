---
typ: pruefung
paket: 0267-eine-tabelle-die-weniger-hergibt-als-sie-traegt
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: all five conditions walked against the file at HEAD; the green run of test 28 in `befunde/uebersetzung-2026-09-08.md` (built at HEAD 702cf37, which contains the package commit a3eff42) is a per-case receipt, because the self-test asserts `knapp.size()` per case
befunde: 1
---

# 0267 checked

## The receipt, and why the exit code carries it per case

`selbsttest_verzeichnis:1623-1655` compares `knappe_tabellen(zahlen).size()` against
`fall.knapp` for **every** one of the 19 `TABELLENFAELLE`, and then re-checks each reported
table for line, readable size and `eintraege < deklariert`. The self-test runs before any
argument is read (`main:1885-1897`, `return 2` on one miss). So exit 0 is not "it ran" — it
is "the bar fired on the bait and stayed silent on both neighbours".

`uebersetzung-2026-09-08.md:154-155` — `28/28 Test #28: kennzeichen_riegel ... Passed`, and
`:441-442` the same in the standalone tree. The report was built at `HEAD zu Beginn:
702cf37` / `HEAD am Ende: 702cf37` (`:108`, `:139`); `702cf37` is above the package commit
`a3eff42`, so the compiled binary is the reviewed file. Compile: `:40`, `:62-63`.

## Condition by condition

1. Non-zero and the four names: `main:2043-2065` returns 2, `:2052-2053` prints
   `p.name`, `tz.zeile`, `tz.deklariert`, `tz.eintraege`. All four.
2. Fallback: `knappe_tabellen:1189` skips `deklariert == NICHTS`. Case 19 (`:1511-1517`)
   puts the size behind a `using`; `deklarierte_groesse:594-597` walks back over whitespace
   only, lands on `e` of `Tabelle`, returns `NICHTS`. Expected `knapp 0`, green.
3. The three cases stand at `:1490-1495` (declares 2, one entry unqualified → `knapp 1`,
   `leer 0`, `stumm 0`), `:1500-1505` (both qualified → 0) and `:1511-1517` (no readable
   size → 0). Hand-walked the bait: `eintragsgruppen:716-737` takes innermost groups with
   `::`, so `{Zwei, …}` is not an entry (`traegt_qualifizierten_namen` finds no `::` at or
   after its `auf`), and `deklarierte_groesse` reads the last top-level template argument
   `2`. 1 < 2 → reported.
4. No count and no probe name: the expected number comes from the mask
   (`lies_verzeichnisse:962`). Grepped the whole file for `_probe` / `kern/test/` — only
   `stumme_proben`, `nennende_proben`, `als_proben` and the self-test fixtures
   `probe_a.cpp` / `probe_b.cpp` (`:1543`, `:1549`), which are texts, not tree files.
5. Two tests are red — `belegstellen_wortabstand` and `belegstellen_kopfzahlen`
   (`:161-163`). Every named line in their output is `belegstellen_riegel.cpp` measuring its
   own head comment against a moved `HEAD` (`:105`, `:112-137`, `:140`). No line of
   `kennzeichen_riegel.cpp` appears.

## That the bar cannot fire on the tree today

All three tables still declare one and yield one, each `std::array<…, 1>` with a single
entry group: `werte_probe.cpp:360-367`, `festkomma_probe.cpp:285-292`,
`schritt_probe.cpp:443-449`. The package and the review of `0263` on 2026-09-08 both pin
these tables at `werte_probe:360`, `schritt_probe:443`, `festkomma_probe:286` — the two
files whose declaration is split over two lines put the name one below, so the anchors sit
where they sat. The probes were not touched. `kennzeichen_probe.cpp` (from `0264`, in the tree at 702cf37)
carries `SCHEIN_OHNE_ZUSTAND` and names `RIEGEL_OHNE_ZUSTAND` only in a `//!` comment
(`:29`), so `nennungen` is 0 and it is not stumm. The green run confirms all of it.

## Finding 1 — the bar is one-sided, and I could not make the other side bite

`knappe_tabellen:1189` reports only `eintraege < deklariert`. A table that declares 1 and
yields 2 passes. I tried to construct a silent case and failed: an extra innermost group
with `::` would be a Kennzeichenliste, and `lies_verzeichnisse:988-996` aborts with
`treffer != 1` before any count is taken. No proposal — I have no input that reaches it.

## Where else I looked and found nothing

Determinism: no floating point, no unordered container, no address or time in the result;
the one `std::sort` (`eintragsgruppen:735`) orders by `auf`, which is unique per group.
Edges: the digit loop guards overflow before multiplying (`:654`), and `NICHTS` is
`std::size_t(-1)` (`:255`), so a wrapped number cannot read as a size. Head comment:
`:162-189` describes the new bar, and `:134`'s "vor den drei Nullpruefungen" still counts
right — `main:2068`, `:2077`, `:2087`.

The level below this one is already filed as `0269-eine-kennzeichenliste-…` with
`haengt_an: [0267]`; I wrote no duplicate.
