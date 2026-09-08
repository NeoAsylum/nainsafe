---
typ: pruefung
paket: 0249-der-kopf-nennt-einen-riegel-der-nicht-mehr-feuern-kann
pruefer: kern-pruefer
datum: 2026-09-08
urteil: zurueck
kriterium_geprueft: each of the five merged conditions re-derived from kern/src/schritt.cpp, kern/src/werte.cpp and kern/test/schritt_probe.cpp at HEAD; 1-4 hold, 5's answer is false for the header's own entry 2
befunde: 2
---

# Conditions 1-4 hold. Condition 5's answer is false at HEAD.

## What I checked

**(1) live barrier named, dead claim dropped -- met.** `summe_der_regel_pruefen`
(`schritt.cpp:679-700`) returns iff the `i128` sum lies in `[I64_MIN, I64_MAX]`; it is
called at `:749`, one line before `festkomma::plus` at `:750`. That is exactly `plus`'s
abort condition, so `plus` of this rule cannot abort. Entry 2 says this and locates it in
`kern::schritt`. Entry 4 is scoped to the **uebrige** festkomma arithmetic, and those sites
exist: `mal_geteilt` in the body (`:741`), `minus`+`mal_geteilt` in `realeinkommenshub`
(`:644`), `plus`+`mal` in `politiklast` (`:596`). I re-derived its path list from the
callers rather than from the package text.

**(2) both BIP aborts -- met.** `werte.cpp:731-746` aborts when the value-added sum leaves
`i64` (T7); `schritt.cpp:628-641` reads `bip`, then aborts on `bip < 1` out of
`kern::schritt`. Entry 1 names both, in that order, conditions left at their site.

**(3) liveness per entry -- met.** The false group contrast is gone; each entry carries its
own statement and entry 1 is no longer called dormant.

**(4) counting words -- met.** Four bullets follow `Vier weitere`. `die drei Schranken des
Rahmens` (`:311`) is right: `schritt()` has three entry barriers -- Modus `:855`,
Rundennummer `:874`/`:882`, Pruefsumme `:914` -- and the first group's fourth bullet
(`Schreiber`) is not one. No line number and no site count from either source reaches
the header.

## Finding 1 -- the pointer sentence is false for the barrier this package exists to name

`schritt.hpp:348-351`: „das haelt das `Riegel`-Verzeichnis in `kern/test/schritt_probe.cpp`
-- eine Kennung je Schranke, zu jeder in jedem Lauf eine angekommene Meldung, sonst faellt
der Lauf. **Wer wissen will, welche Schranke heute wirklich anschlaegt, liest dort und
nicht hier.**"

How to produce the error:

1. Take entry 2's barrier, `summe_der_regel_pruefen`.
2. Follow the instruction into `schritt_probe.cpp`. `enum class Riegel` (`:346-355`) holds
   seven values; none is this one. `ALLE_RIEGEL` (`:357-360`) holds those seven, and the
   completeness loop (`:2159-2171`) runs over that array alone.
3. Absence there is the signal that file's own comment (`:396-397`) reserves for a barrier
   that vanished unnoticed.
4. It sits in a **second** registry with its own type, `RIEGEL_OHNE_ZUSTAND` (`:432-464`),
   "von der Vollzaehligkeit ausgenommen" (`:2218-2221`), for which no message ever arrives
   and the run does **not** fall -- `summe_der_regel_pruefen` has internal linkage and
   cannot be called from the probe (`:413-417`).

Both readings fail. Narrow (`das Riegel-Verzeichnis` = `ALLE_RIEGEL`): the guarantee is
true, the pointer sends the reader to the half that excludes entry 2. Wide (both
registries): `zu jeder ... eine angekommene Meldung, sonst faellt der Lauf` is false.

**This does not rest on the commit order.** `0248` landed after this package (`10d5178`
after `b407546`), but at the builder's own HEAD `summe_der_regel_pruefen` had no Kennung at
all -- that is why `0248` exists. And entry 1's first barrier (`kern::werte::bip`), entry 3
(`kern::werte::schaden`) and entry 4 (`kern::festkomma`) have no Kennung in either registry:
this ledger is scoped to `kern::schritt`. For three of four entries the instruction answers
nothing.

Condition 5 asked to point at the ledger *instead of restating it*. The header points and
restates, and the restatement is what went stale -- the same failure one level up.

## Finding 2 -- the one entry whose abort fires is the one that does not say so

`:311-313` promises every entry says „ob ein Zustand sie heute erreicht". Entries 2, 3, 4
answer. Entry 1 says only „Beide Schranken werden jede Runde gerechnet, fuer jedes Land",
and in this text's own vocabulary `gerechnet` is not `erreicht` (entry 2 separates them in
one sentence). Its Nennerbedingung abort is the only one of the four that fires:
`Riegel::Nennerbedingung` is in `ALLE_RIEGEL`, so `schritt_probe.cpp:1786` yields an
arrived message in every green run.

## Searched, nothing found

Determinism: the package changes a doc comment only, no code. `werte::schaden`'s two
non-overflow aborts (`werte.cpp:999`, `:1049`) are unreachable from step 5 -- `politiklast`
iterates `INSTRUMENTE_ALLE`, `schritt_5_reaktion` `LAENDER_ALLE`, guard is `g >= LAENDER`;
they owe the list no entry. Build green at HEAD: `uebersetzung-2026-09-08.md`,
`ergebnis: ok`, `Built target schritt_probe`.
