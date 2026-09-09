---
typ: pruefung
paket: 0275-eine-zahl-ohne-ihre-menge-und-eine-stille-mit-bedingung
pruefer: kern-pruefer
datum: 2026-09-08
urteil: zurueck
kriterium_geprueft: "Condition 1 recounted case by case against TABELLENFAELLE at HEAD (27/19/8/4+4/16 hold, the new set-claim does not); 2 read against gleiche_ab:1405-1441; 3 hand-traced through both new ABGLEICHFAELLE cases; 4 by line-shift arithmetic plus the build report."
befunde: 2
---

# Befund 1 — condition 1: the eight got a set, and it is the wrong one

`kennzeichen_riegel.cpp:1534-1536`:

> „Die **acht** Faelle, die es angeht -- es sind genau die acht mit einer **benannten**
> Liste --, schreiben es aus: **vier** eine Eins und **vier** eine Null."

**How to produce the error.** Count the cases of `TABELLENFAELLE` whose Kennzeichen field is
an identifier resolved as a named list:

| case | line | list | declared/marks |
|---|---|---|---|
| 1 | :1569 | `KZ_SUMME` (in `PROBE_BENANNT`, :1557) | 2/2 |
| 4 | :1585 | `KZ_ANDERSWO` (:1589) | 1/1 |
| 6 | :1598 | `KZ_DOPPELT` (:1599) | 1/1 |
| 20–27 | :1722–:1817 | `KZ_KURZ` … `KZ_RUF` | the eight |

**Eleven, not eight.** (Twelve if case 7 at :1606 counts — `KZ_A, KZ_B` — but that entry is
`lesbar: false` and no list is resolved.) Case 1 carries the word in its own title:
*„benannte Liste in derselben Probe"*.

The three extra are not a technicality. Each has a readable `deklariert`, each yields a
`Listenzahl` (`:1171-1177`), and each is measured by `knappe_listen` in the same run — they
come out 0 and leave the field on the default. The clause's own next sentence says so:
*„Die Pruefung erreichen davon nur **sechzehn**"* (`:1547`). Cases 1, 4 and 6 are among those
sixteen, and on them `listen_knapp.size() == 0` is a real measurement of a real named list,
not a vacuous one.

Condition 1 asks: *„if it keeps a number, that number is recounted against `TABELLENFAELLE`
at HEAD and true."* The number eight is true as the count of cases that write the field out
and false as the count of cases with a named list — and the clause asserts both. That is the
defect from `pruefung-0272-…`, Befund 1 (a number whose set does not hold), moved one clause
left, into the sentence two lines above the rule it breaks: *„**Die Menge steht dabei und
nicht bloss die Zahl**, weil eine Zahl ohne ihre Menge beim naechsten Fall wieder falsch
ist"* (`:1544-1545`).

**Same edit, second slip, same one-clause fix:** *„die vier Nullen sind **deren
Gegenfaelle**"* (`:1538`). Case 25 (*„die Groesse der Liste steht hinter einem `using`"*,
:1776) is a **second** counter-case to case 20's Koeder — its own comment says so
(`:1772-1774`) — and case 24 (*„zwei Eintraege, eine kurze Liste"*, :1764) has no
counter-case among the four zeros at all. The pairing is 4:4 in the prose and not in the
table.

**What in the clause does recount true, so it is not re-done:** 27 cases in the array; 19 on
the default (1–19); 8 written out (20–27); four ones (20, 22, 24, 26) and four zeros
(21, 23, 25, 27); three `lesbar: false` (7, 8, 9), so 16 reach the check. The four titles
naming the zeros match cases 21/23/25/27 exactly.

# Conditions 2, 3 and 4 hold — the return is one clause

**2 — met.** `:101-116` now carries both outcomes and conditions the silence: *„Steht `x` in
irgendeiner Zeichenkette des Kerns, schweigt `gleiche_ab`"* … *„Steht es dort nicht, kommt
ein Befund -- aber er nennt in `stueck` das Argument `x`, das der Eintrag als Kennzeichen nie
deklariert hat"*. Read against `gleiche_ab:1420-1437`: `b.stueck = s.text` at `:1435`, line
`s.zeile` at `:1434` — the described Befund is the one the code builds. The unconditional
*„kein Befund an kaputter Bindung"* is gone.

**3 — met, and the alternative was answered rather than passed over.** Two cases were added,
`ABGLEICHFAELLE` 7→8. Hand-traced against `KERNTEXT`, whose merged literal is
`"kern::schritt -- Zustimmungsregel: min(...) aus spiel.md klemmt erst hinter der Summe. Ueber den ganzen Lauf."`:

- `:2045-2047` `ERSTES("Zustimmungsregel")` → one mark, found in the merged literal → **0
  Befunde** ✓.
- `:2055-2057` `ERSTES("klemmt erst hinter dem Summe")` → one mark; the kern says *der*
  Summe, not *dem* → **1 Befund**, `stueck == "klemmt erst hinter dem Summe"` ✓, held by the
  new `stueck` field and checked at `:2111-2132`.

The package's escape clause pointed at the pre-existing case at old `:2012` (= case 3,
*„ein Stueck ist danebengeschrieben"*, now `:2032`). `:2049-2050` states why it does not
cover the case: *„Die Eins allein waere von Fall 3 nicht zu unterscheiden -- gemessen wird
deshalb der **genannte Wortlaut**"*. Not silent about which of the two answers applies.

**4 — met.** The package's four anchor lines for the explicit zeros (`:1722`, `:1745`,
`:1768`, `:1803` at HEAD `cd46bbf`) now sit at `:1736`, `:1759`, `:1782`, `:1817` — a uniform
**+14** on all four, so no case between them gained or lost a line. All 27 expectations were
re-derived from their inputs and none is lowered; the six old `ABGLEICHFAELLE` expectations
(0/0/1/2/1/1) were re-traced against `KERNTEXT` and all six hold. The `stueck` field
(`:2024`) defaults to `""`, so the old positional initializers are untouched.

Build report `befunde/uebersetzung-2026-09-08.md` carries no HEAD line this time; the
recompile fingerprint places it after the package: exactly two sources rebuild — `:36`
`kennzeichen_riegel.cpp.o` and `:42` `belegstellen_riegel.cpp.o`, the night's two changed
files, the second being `0278`'s. `kennzeichen_riegel` **Passed** in both runs (`:148`,
`:441`); `kennzeichen_probe` Passed (`:225`). The two red tests are
`belegstellen_wortabstand` (`:74`) and `multiplikationsriegel` (`:150`); neither block names
this file, and both belong to `0278` and `0274`.

# Befund 2 — one element, two marks: the inflation the file argues against has no door shut

Not part of the criterion; it is the gap next to it. Proposal written as `0279`.

`:1166-1170` names the failure mode this counting rule exists to prevent:

> „Wer stattdessen die Teile zaehlte, kaeme auf drei und laege damit **zu hoch**. Die
> Schranke unten fragt nach `gelesen < deklariert`; eine zu hohe Zahl meldet nichts, wo etwas
> fehlt. Der Fehler waere also nicht ein roter Lauf an heilem Text, sondern ein gruener an
> kaputtem."

The second half of the third blind spot is written and now held for **one element → one
mark** (`{ERSTES("x"), "b"}`, 2 declared, 2 marks, wrong wording). It is not written for
**one element → two or more marks**. `stuecke_aus` (`:985-1000`) walks every `MARKE` between
the braces with no notion of parentheses, and `lz.stuecke = e.kennzeichen.size() - vorher`
(`:1177`) is that mark count. So:

    constexpr std::array<const char*, 3> KZ = {VERBINDE("a", "b"), "c"};

declares three, yields **three** marks from **two** elements, `3 >= 3`, `knappe_listen`
silent — a genuinely short list passing green. That is worse than the outcome the head
describes: there the wording is unbound, here a missing element is hidden as well. The
reasoning at `:1166-1170` is already in the file; only the door through a call argument is
not, and no case holds it.

# Where I looked and found nothing

- **Determinism of the new cases:** both new `ABGLEICHFAELLE` entries are `constexpr
  string_view`; `selbsttest_abgleich` iterates the array by index (`:2083`) and `gleiche_ab`
  iterates `eintraege`/`wortlaut` by index — no unordered container, no float, no address in
  a result.
- **Whether the new bar can fire:** it can. Case 8 is red the moment `zerlege` learns the
  element boundary, and `:2053-2054` says so. Not a green-and-worthless check.
- **Stale numbers elsewhere in the head:** `:118` *„alle drei aufgeloesten Listen"* — nothing
  under `kern/test` was touched by this commit, so the three stand from
  `pruefung-0269-…`. `:43-44` (57 `abbruch(` / 26 / 10) is untouched by this change.
- **A `lesbar: false` case being quietly counted into the sixteen:** cases 7, 8, 9 are the
  only three, `selbsttest_verzeichnis:1875-1877` continues before `knappe_listen` is reached.
  Correctly empty.
