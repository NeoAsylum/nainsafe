---
typ: pruefung
paket: 0279-ein-element-zwei-marken-und-die-kurze-liste-bleibt-still
pruefer: kern-pruefer
datum: 2026-09-09
urteil: geprueft
kriterium_geprueft: "case 28 hand-traced with its red proof computed, the 28/19/9/16 counts re-derived by one terminator grep, the report's green tied to a recompile of the file at a descendant HEAD"
befunde: 2
---

# 0279 — the element count beside the mark count

## What I checked, and how

**1 — it counts elements.** `lz.elemente = felder_von(liste.maske, listengruppe).size()`
(`:1254`); `hergegeben` (`:1019-1022`) returns the smaller of marks and elements;
`knappe_listen:1452` compares that against `deklariert`. `felder_von` (`:851-891`) splits
`[g.auf+1, g.zu)` at commas of depth 0 over `(){}[]`, trims, drops empty fields — a trailing
comma does not raise the count. Both numbers survive; `main:2586-2590` prints declared, marks
and elements. `min` can only lower, so no list caught before goes silent now.

**2 — the head names the exception.** `:1225-1235` at the count itself, `:118-131` and
`:265-273` in the file header. *„eine zu hohe Zahl meldet nichts"* (`:1220-1223`) no longer
stands alone.

**3 — case 28 (`:1931-1938`) bites.** Hand-trace of `KZ_RUF_ZWEI = {VERBINDE("alpha",
"beta"), "gamma"}`, declared 3: `stuecke_aus` leaves 3 marks, `felder_von` 2 fields (the inner
comma sits at depth 1), `hergegeben` = 2 < 3 → one report; the case writes `listen_knapp = 1`
and `selbsttest_verzeichnis:2079` compares exactly. Drop `elemente`, or take the larger of the
two, and it is `3 >= 3` → 0 ≠ 1 → red. The mechanism it kills is named at `:1923-1925` and
`:1440-1446`.

**4 — counts and untouched cases.** Grep `(, [0-9]+)+\},$`: 28 entries in `TABELLENFAELLE`,
19 with three trailing numbers, 9 with four; the nine are the last nine, values
1,0,1,0,1,0,1,0,1 → ones at 20/22/24/26/28, zeros at 21/23/25/27, exactly as `:1617-1629`
claims. Three `lesbar: false` (`:1703`, `:1709`, `:1716`), all among the 19 → 16 reach the
check. Cases 20–27 carry the values earlier reviews recorded (26 = `"R::Eins=beta"`/1,
27 = `"R::Eins=alpha;beta"`/0). `uebersetzung-2026-09-09.md`: the file recompiled (`:41`),
HEAD `e6924bf` — a descendant of the package commit `d7d90a3` —, test 28 `Passed` (`:177`,
`:593`), and the string `kennzeichen_riegel` occurs in no failure block of that report.
The three resolved lists in the tree are 3, 2, 2 marks and 3, 2, 2 elements, as `:135` says.

Determinism, searched and empty: no float in the count, no `unordered_`/`map`/`set`, no time,
one `std::sort` over distinct `auf` (`:840`).

## Befund 1 — the doubled brace under-counts, and it reddens healthy text

`finde_zuweisungen:665-670` sets `auf` to the **first** `{` after `=`. For the idiomatic
`std::array` form

    constexpr std::array<const char*, 2> KZ = {{"a", "b"}};

`felder_von` meets the second `{` at depth 0, raises the depth, and the comma inside is never
a separator: one field, `elemente = 1` against `stuecke = 2`, `hergegeben` = 1 < 2 — **a
complete list reported as short**. Only the fully wrapped form breaks; `{{A}, {B}}` still
counts 2. No tree list carries it today, so it is latent — but it is the direction this file
calls disqualifying at `:1801` and `:1846` (*„eine Schranke, die daran rot wird, faerbt einen
heilen Baum"*), and the doubled brace is this tree's own spelling for every other
`std::array`: `TABELLENFAELLE = {{`, `ZERLEGEFAELLE = {{`, `RIEGEL_OHNE_ZUSTAND = {{` in all
three probes. No case covers it. Proposal `0289`.

Not part of the criterion — condition 1 asks for an element count and there is one. It is the
gap next to it.

## Befund 2 — two of the five conjuncts in the report check cannot fire

`selbsttest_verzeichnis:2094-2095` tests each reported list with `lz.probe.empty() ||
lz.name.empty() || lz.zeile == 0 || lz.deklariert == NICHTS || hergegeben(lz) >=
lz.deklariert`. `knappe_listen:1452` returns exactly the indices with `deklariert != NICHTS`
**and** `hergegeben < deklariert`, so the last two terms are false by construction on every
input. Delete both and the suite stays green. The message under them advertises five things
and can only ever fail on three. Same shape as `0275`'s Befund 2, one level down.

## For the project manager

`0282`'s vermerk still names the counts *19/8/27/16* and the enumeration at `:1534-1549`.
After this package they are 19/9/28/16 at `:1613-1644`.
