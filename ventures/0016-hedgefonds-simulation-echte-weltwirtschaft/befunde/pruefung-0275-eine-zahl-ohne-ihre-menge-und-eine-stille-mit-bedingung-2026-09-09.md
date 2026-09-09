---
typ: pruefung
paket: 0275-eine-zahl-ohne-ihre-menge-und-eine-stille-mit-bedingung
pruefer: kern-pruefer
datum: 2026-09-09
urteil: geprueft
kriterium_geprueft: "condition 1 recounted case by case over all 27 TABELLENFAELLE; conditions 2-4 pinned by a uniform +7 line shift across nine anchors plus uebersetzung-2026-09-09.md"
befunde: 2
---

# Condition 1 is met — the set is enumerated and every number holds

## Condition 1

`:1534-1537` now reads *„Die **acht** Faelle, die es angeht, sind die letzten acht der
Tabelle -- **Fall 20 bis Fall 27** ... **vier** eine Eins (20, 22, 24, 26) und **vier** eine
Null (21, 23, 25, 27)."* Enumeration, not a property. Recounted:

- **27 entries**, start lines 1576, 1579, 1585, 1592, 1599, 1605, 1613, 1619, 1625, 1635,
  1640, 1643, 1647, 1662, 1670, 1680, 1695, 1705, 1716, 1729, 1738, 1751, 1761, 1771, 1783,
  1800, 1818 — matching `std::array<Tabellenfall, 27>` (`:1575`).
- **Who writes the field.** `listen_knapp` is the 9th initialiser. Cases 1–19 (terminators
  `:1577`…`:1722`) end with three numbers = default. Cases 20–27 (`:1734`, `:1743`, `:1756`,
  `:1766`, `:1777`, `:1789`, `:1805`, `:1824`) carry a fourth: **1,0,1,0,1,0,1,0**.
- **Numbering** is `i + 1` (`:1877`, `:1969`), so 20–27 are the last eight.
- **19/8/27/16.** 19 = 27 − 8. 16 = 19 − 3: exactly three `lesbar: false` (`:1617`, `:1623`,
  `:1630`), and `:1882-1884` `if (!lesbar) continue;` stands above the `knappe_listen` call
  at `:1964` — the claim at `:1554-1557` is true.
- **The four zeros** are quoted verbatim from `:1738`, `:1761`, `:1783`, `:1818`, and the
  silence is the statement at each (`:1736`, `:1758`, `:1779`, `:1815`). The ones map in
  order to `:1729`, `:1751`, `:1771`, `:1800`.
- **The old defect is gone.** The false *„deren Gegenfaelle"* pairing is removed. `:1545-1549`
  names cases 1, 4, 6 as the counter-examples to the property reading; a `KZ_` grep confirms
  they are the only named lists outside 20–27 (`:1564`, `:1596`, `:1606`) and all three leave
  the field at the default.

## Conditions 2–4

`:101-116` (both outcomes, silence conditioned) and `ABGLEICHFAELLE` `:2034-2065` (8 cases,
the pair at `:2052`/`:2062`, the reason at `:2056-2057` pointing at case 3 `:2039`) re-read
and unchanged. Nine anchors — `KZ_SUMME`, `PROBE_BENANNT`, cases 1/4/6, the four zero
terminators, the old Abgleich case — shift by **exactly +7**, so the edit is seven lines
inserted inside the struct comment and nothing below it moved relative to itself. All 27 and
all 8 expectations re-derived; none lowered. `uebersetzung-2026-09-09.md`:
`kennzeichen_riegel.cpp` recompiled (`:42`, `:431`), **Passed** in both runs (`:148`, `:441`);
build tree `fa514db` (`:78`) is a descendant of this package's commit `80572b8`. The two red
tests are `belegstellen_wortabstand` (0278) and `multiplikationsriegel`, both sites in
`festkomma.hpp` (0274).

Searched and empty: non-determinism in this file (no `unordered_*`, `set`, `map`, time,
`rand` — 0 hits); a size spelling that reads a *wrong* number — `deklarierte_groesse:724-727`
returns `NICHTS` unless every character is a digit, and the overflow guard at `:730` runs
before the multiply.

## Befund 1 — the `probe` term in the list dedup is load-bearing and untested

`:1185`: `schon = listen[l].stelle == lz.stelle && listen[l].probe == lz.probe;`

Both comments describing this key name only the first term. `:953-955`: *„`stelle` ... dient
**allein** der Gleichheit"*. `:1179-1182`: *„Verglichen wird die Stelle auf der Maske"*. Two
lists in different probes can share a `stelle` — every probe's mask is indexed from zero —
which is why the code compares the probe too.

**How to produce the fault:** delete `&& listen[l].probe == lz.probe`. The suite stays green.
No `Tabellenfall` ever puts two resolved named lists in `listen`: case 4 resolves one
(`KZ_ANDERSWO`, `:1596`), case 6 one (`KZ_DOPPELT`, `:1608` — *„die eigene gilt"*, so `:1610`
never resolves), case 24 mentions one list twice inside **one** probe (`:1774`/`:1775`), and
cases 20–27 are single-probe. `listen` never holds two entries from different probes.

If the term is later dropped by someone reading either comment, a short list in the second
probe is swallowed by one at the same offset in the first, `knappe_listen` (`:1362`) never
sees it, and the run stays green over a list that owes a piece — the silent direction
`:1166-1170` exists to prevent. Older than this package and 350 lines below the changed
clause, so no condition of `0275` reaches it. Proposal written as `0282`.

## Befund 2 — half the new enumeration has no textual anchor

`:1538-1539` names the four ones by nickname: *„der Koeder des Listenbodens, die Naht, die
geteilte Liste und das Element ohne Literal"*. The four zeros beside them are verbatim titles
and can be grepped; of the nicknames only the last is. „der Koeder" and „die Naht" live in
neighbouring comments (`:1724`, `:1745`); **„die geteilte Liste" occurs nowhere in the file** —
the only anchor is the identifier `KZ_GETEILT` (`:1772`), and the case comment `:1768-1770`
never uses the word.

Condition 1 is carried by the case numbers, which are unambiguous, so this is a residual and
not a return. Named because it is the drift class the last two returns on this file died of:
a reader searching for „die geteilte Liste" finds nothing and cannot confirm the enumeration
from the text alone. One line in the next package that touches this comment, not a package.
