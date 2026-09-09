---
typ: pruefung
paket: 0277-der-weg-eines-pfadwerts-in-die-runde
pruefer: entwurf-pruefer
datum: 2026-09-09
urteil: geprueft
kriterium_geprueft: The repair to condition 2 re-measured at the corpus (both test numbers, all four prose spots, the three constants), and the four conditions ruled met on 2026-09-08 spot-checked at their cited lines to confirm nothing else moved.
befunde: 0
---

# The inventory is complete for `schritt_probe.cpp`; three comments in `schritt.hpp` are not in it, and that is a package

## The repair, re-measured before reading the section

Section 34 now sits at `technik.md:5933-6121`. Every place its new inventory names exists
at the cited line, verified with one `grep -n 'feldzahl'` over
`kern/test/schritt_probe.cpp` and three reads:

| Section says | At HEAD |
|---|---|
| `:1866` `static_assert(ohne_klammern::feldzahl<Konstanten> == 9)`, translation fails | confirmed, `:1866`; its message `:1868` is inside the same statement |
| `:1906` `PRUEFE(... == 9)`, compiles green, exits red | confirmed, `:1906`; comment `:1902-1905` reads as quoted |
| `:1907` follows the new counts by itself, `:1915`/`:1925` only print | confirmed: `:1907-1908` holds `feldzahl` against `SUMMIERTE_FELDER + JAHRGANGSFELDER`, `:1915` and `:1925` are `printf` arguments |
| four prose spots false with the field | confirmed: `:1700-1702`, `:1719-1721`, `:1736-1738`, `:1800-1801`, each quoted word for word |
| `:1633-1639` seven-key table untouched | confirmed: seven `i64` member pointers, `std::array<Schluesselfeld, 7>` at `:1632` |

The count 10 itself: `pfadstand` is a `std::array`, and `:1736-1738` states from measurement
that a `std::array` occupies one slot with the braces as without — so `ohne_klammern` and
`kern::schritt::feldzahl` both go 9 → 10, which is what makes `:1866` a translation failure
and not a silent pass. `SUMMIERTE_FELDER = 7` (`schritt.hpp:264`), `JAHRGANGSFELDER = 2`
(`:269`), assert at `:271`.

## The other four, spot-checked at their lines

Signature `schritt.hpp:369-370` still four `const` arguments, unchanged (1). §28 `:5482-5489`
reads as quoted, clamp sentence intact, cited at `:6052` (3). T61 `:4348-4350` names series 9,
12, 13 and „the fourth instrument … has no series, its value comes per T45 from
`parameter.toml`" — the table `:6062-6067` maps exactly that (4). `grep 'pfadstand|PFADINSTRUMENTE'`
over the venture: two hits, this package and my previous finding — no `kern/`, no
`parameter.toml`; `grep 'schritt::schritt('` over `kern/` still 16, 15 + `verlauf_probe.cpp` (5).

## The residual, and why it is not a second Rücklauf

`kern/include/kern/schritt.hpp` states the old counts in three places the section does not
name, all in the file the successor edits to set `JAHRGANGSFELDER = 3`:

- `:150-152` — „gegen die Summe aus den sieben Aufrufen hier und den **zwei** Groessen des
  Jahrgangs; kommt ein **zehntes** Feld dazu, uebersetzt der Kern nicht mehr." Both halves
  false afterwards; a tenth field then compiles.
- `:205` — „`Konstanten` … zaehlt mit den Klammern wie ohne sie **neun** Felder."
- `:272-273` — the assert's own message: „traegt nicht mehr sieben summierte Felder und
  **zwei** Groessen des Jahrgangs."

Not a finding against condition 2: the condition asks that the new numbers stand in the
section, and they do (7 / 3 / 10); the section's table is scoped to
`kern/test/schritt_probe.cpp` by its own header, so it is silent, not wrong. Nothing here
goes red — `:1866` and `:1906` were findings because they break the build, these are
comments. `0001-entwurf-abnahme` puts precision beyond the five conditions into a package,
not into another round, and this lane is the one the venture waits on.

Filed as `aufgaben/0281-drei-kopfzahlen-in-schritt-hpp-ueberleben-das-zehnte-feld.md`,
`status: vorschlag`. It must not run **before** the successor: today all three sentences are
true. `:179` („Der Riegel gegen das zehnte Feld") I did not raise — it names package 0229 and
reads as history. The `JAHRGANGSFELDER` comment `:266-268` is already covered by the section
at `:6014-6018`.
