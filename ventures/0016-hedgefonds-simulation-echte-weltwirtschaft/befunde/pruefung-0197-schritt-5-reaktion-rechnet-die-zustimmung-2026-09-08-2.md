---
typ: pruefung
paket: 0197-schritt-5-reaktion-rechnet-die-zustimmung
pruefer: kern-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "All four conditions in the 2026-09-08 re-cast: 1 and 3 read against spiel.md:2266-2318 and probe_kette, 2 recomputed by hand on the four start values, 4 from uebersetzung-2026-09-08.md (all 8 manifests green)."
befunde: 3
---

# Judgement: the criterion is met, and the divisor is not guarded

## How each condition was checked

**1 — computed value, rule in its own wording.** `schritt.cpp:667` writes
`setze(platz, zustimmung_neu, Ursache::gegenkraft(2), 0, 1000)`; no `vortrag` on the four.
The three lines at `schritt.cpp:529-539` are a character-by-character transcription of
`spiel.md:2278-2280`, `:2267` and `:2314-2318` (`Σ`→`Summe`, `·`→`*`, `−`→`-`).

**2 — clamp against carry-forward, recomputed by hand.** Start values
`{10.001, -1, I64_MAX, I64_MIN}` (`schritt_probe.cpp:1210`). With `richtung == 0` on all
16 stands, `last = 0`, `hub = 0`, `wirkung = 0`, so the body reduces to
`min(10.000, max(0, start))` → `{10.000, 0, 10.000, 0}` = `SCHRANKE` (`:1212`), and no
address keeps its start value. `auf_der_schranke == 4`, `stehen_geblieben == 0`
(`:1240-1241`), per-address print with `index_zu_adresse` at `:1233`. The reason every
additive term is zero is quoted from `spiel.md:2383-2384` at `:1197-1203`.
`probe_zustimmung_ohne_instrumentenschritt` and the forward guard
(`zustimmung_vor_instrument == 16`, now `:1173`) both stay.

**3 — the ascending chain retracted.** `probe_kette` splits the assertion:
links `0..170` `Vortrag`, ascending, pairwise distinct; links `171..174` `Gegenkraft`
number 2 on `ZUSTIMMUNGSPLAETZE[rang]` (`:665-735`), plus the mask-completeness loop at
`:754-771` that catches a double naming across the two halves. Head of `schritt.cpp`
retracted at `:31-39`.

**4 — receipt.** `befunde/uebersetzung-2026-09-08.md`: `schritt.cpp.o` and
`schritt_probe.cpp.o` rebuilt, `schritt_probe` Passed in both manifests that carry it,
and every manifest at 100 % (26/26, 13/13, 3/3, 5/5, 1/1, 1/1, 3/3). No count can be
lower than at the start of the run because every count is at its ceiling.

## 1. `realeinkommenshub` divides by `bip(l)` with no lower bound — a negative GDP flips the sign silently

`schritt.cpp:615-616` calls `mal_geteilt(minus(0, last), 10.000, werte::bip(...))`.
`festkomma.hpp:155-158` aborts only on `c == 0`; `werte.cpp:691-700` sums three addresses
and returns whatever comes out. `spiel.md:2409` names `bip(l) > 0` as the denominator
condition. The code comment at `schritt.cpp:608-610` answers `bip == 0` and is silent on
`bip < 0` — while the same codebase writes the argument out for the identical shape:
`werte.cpp:596-606` guards `wechselkurs < 1`, "der **negative** Nenner ist der
gefaehrlichere Fall, weil er das Vorzeichen jeder Bewertung drehte, ohne dass irgendetwas
abbraeche." Here nothing aborts: a policy burden would *raise* approval.

**How to produce it — it is already in the delivered probe.** `musterwert(p) =
muster[p % 8]`, `muster[0] = 0`, `muster[4] = -10.000`. `stelle_sektorgroesse` puts
`Wertschoepfung` at country base `+0, +4, +8`; country bases are `0, 44, 88, 132`. So
`bip(US) = 0 + (-10.000) + 0 = -10.000`, `bip(CN) = -20.000`, `bip(DE) = -10.000`,
`bip(BR) = -20.000`. **Every round in `schritt_probe` divides by a negative GDP and stays
green, because the numerator is zero.** Proposal `0237`.

## 2. The multiplying half of the rule is executed by no probe

`politiklast` skips `schaden` whenever `richtung == 0` (`schritt.cpp:592-594`), and
`schritt_3_politik` carries forward, so `richtung` is 0 for all 16 pairs in every probe.
`werte::schaden`, `festkomma::mal(richtung, zeile)` and the `plus` accumulation are never
run. Consequence with a date on it: `schaden` takes the `Schreiber` and reads with
`lies_neu`; whether any of its reads lands outside the `weltlauf` mask (a hard T39 error)
is unmeasured. Second consequence: `probe_zustimmung_klemmt_statt_vortrag` starts an
address at `I64_MAX`, so the first round with a non-zero `hub` aborts in
`festkomma::plus` at `schritt.cpp:659` instead of clamping. Folded into `0237`.

## 3. A section banner that this package refuted

`schritt_probe.cpp:611` still reads „die Kette hat 175 Glieder, und jedes ist ein
Vortrag". Four are `Gegenkraft`. The doc comment three lines below it is correct; the
banner is the sentence a reader greps for. In `dateien`, one line.
