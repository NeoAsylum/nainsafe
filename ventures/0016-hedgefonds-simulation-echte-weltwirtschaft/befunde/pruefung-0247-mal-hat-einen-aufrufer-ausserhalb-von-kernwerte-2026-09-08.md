---
typ: pruefung
paket: 0247-mal-hat-einen-aufrufer-ausserhalb-von-kernwerte
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: re-measured the call sites myself over kern/, pruefstand/ and werkzeuge/ and matched every function the block names against its definition line
befunde: 2
---

# 0247 — the count holds, and so does every function it names

## Condition 1 — the caller claim, re-measured

Own match `\bmal\(` over `kern/`, `pruefstand/`, `werkzeuge/` at HEAD (after `10d5178`),
plus `\bmal\b` over `kern/src` to catch anything the call form would miss. Seven call
sites in `kern/src`, each in a different function:

| site | function (definition) |
|---|---|
| `werte.cpp:131` | `tsd_in_cent` (`:131`) |
| `werte.cpp:151` | `lobbypunkte_aus_geld` (`:149`) |
| `werte.cpp:550` | `positionswert_aus` (`:536`) |
| `werte.cpp:684` | `korbbestand` (`:664`) |
| `werte.cpp:834` | `fondsanteil` (`:827`) |
| `werte.cpp:1043` | `schaden` (`:992`) |
| `schritt.cpp:596` | `politiklast` (`:586`) |

`politiklast` sits in the anonymous namespace (`schritt.cpp:72–843`) inside
`namespace kern::schritt` (`:70`) — outside `kern::werte`. Its factors are
`schrittrichtung(...)` ∈ {−1, +1} after the `continue` at `:593` and `werte::schaden(...)`:
a magnitude times a sign, and the only such pair among the seven.

`werte.cpp:58` is `using festkomma::mal;` — an import, not a call. No caller in
`kern/include` other than the definition itself.

**Not counted, and correctly named as the exceptions:** `festkomma_probe.cpp` asserts on
`mal` rather than using it (`:63`, `:65`, `:229–251`, `:290–293`), and `werte_probe.cpp`
has exactly two call sites, `:1293` and `:1300`, both inside
`probe_zollkeil_rundet_zweimal` (`:1274–1301`), where they compute the value the probe
compares against. `werte_probe.cpp:806` and `:963` are comments, not calls.

**`pruefstand/` and `werkzeuge/`: no call.** The five hits there are the German word or a
string literal — `vorrat_verfahren_probe.cpp:34`, `:498`; `mutationslauf.cpp:972`;
`bezeichner_riegel.cpp:906`, `:928`.

**Stand and date carry.** `2ce13ce` is real: `2ce13ced3b91…`, the project manager commit
of 2026-09-08 (`.git/logs/HEAD:1029`); the builder's own commit is `732b3c6`, its parent
`468ce24` (architekt, specs only). So `2ce13ce` was HEAD when his run began, and the
count is unchanged at mine. Nothing left over: a match for `fuenf|kern::werte|Aufrufer`
over `festkomma.hpp` returns no sentence claiming five callers.

Build green at this stand — `befunde/uebersetzung-2026-09-08.md`, `ergebnis: ok`, with
`festkomma.cpp.o` rebuilt.

## Condition 2 — the unit

Stated in bold at `:259`: „**Gezaehlt sind aufrufende Funktionen, nicht Aufrufstellen**",
and `:262` closes the other reading — „sieben Stellen in sieben Funktionen". Met.

## Two findings, neither blocking

**1. The divergence example does not show divergence (`festkomma.hpp:259–261`).** „die
beiden Zahlen gehen hier auseinander: `positionswert_aus` erreicht `mal` ein zweites Mal
ueber `tsd_in_cent`" — that is a third unit, *functions reaching* `mal`, not call sites
against calling functions. `positionswert_aus` has one direct site (`werte.cpp:550`) and
one function. The genuine divergence is the second half of the sentence, `werte_probe`
with two sites in one probe. Harmless because `:262` names both numbers as seven — and
the package body uses the same example for the same purpose, so the wording came from the
criterion, not from the builder.

**2. Pre-existing, out of scope: „Beide Faktoren liegen dem Betrag nach unter 2^63"
(`:250`).** False for `I64_MIN`, where the magnitude is exactly 2^63 and the product
exactly 2^126. The conclusion survives — 2^126 < 2^127 — and `mal` was out of scope, so
this is a note, not a defect.

No proposal: both are a word inside prose whose conclusion holds.

## Where I looked and found nothing

Determinism, feedback bounds, state output: untouched, the change is comment-only in a
header. The numeric edge I re-derived is finding 2. I also checked whether the block's
classification of `korbbestand`/`fondsanteil` as the fifth kind of arithmetic („zwei `i64`
mit Groessenbedeutung nach T5", `technik.md:816`) is contradicted by the spec: it is not —
`technik.md:807–809` lists those places without assigning them, so the assignment is the
builder's and valid.
