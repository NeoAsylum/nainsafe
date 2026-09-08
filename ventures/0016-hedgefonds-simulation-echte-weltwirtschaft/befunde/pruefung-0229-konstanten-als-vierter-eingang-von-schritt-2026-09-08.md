---
typ: pruefung
paket: 0229-konstanten-als-vierter-eingang-von-schritt
pruefer: kern-pruefer
datum: 2026-09-08
urteil: zurueck
kriterium_geprueft: Conditions 1-3 read off header, source and both probes; condition 4 counted line by line out of befunde/uebersetzung-2026-09-08.md against the 2026-09-07 report.
befunde: 1
---

# Conditions 1-3 hold. Condition 4 is measured red, and this package's own edit is why.

## Condition 1 — met

`schritt.hpp:183-184` and `schritt.cpp:604-605` both read
`schritt(const Zustand&, const Aktionsbuendel&, const Konstanten&, Modus)` — T10b's order.
Both calling probes pass four arguments (`schritt_probe.cpp:617, 698, 743, 748, 799, 801,
832, 879, 920, 1073`; `verlauf_probe.cpp:284`). The tree translates:
`uebersetzung-2026-09-08.md` builds `schritt_probe`, `verlauf_probe`, `werte_probe` with
Code 0 on both build paths (root :74-79, kern alone :224-229).

## Condition 2 — met

`werte.hpp:143-153`: key name `zustimmung_elastizitaet`, "T5 Klasse 4 (Anteile,
Zehntausendstel)", bound `>= 0`, in the shape of the seven fields above it.

## Condition 3 — met

`schritt.cpp:667-683`: `parameter_pruefsumme(konstanten)` against
`rundenschreiber.lies_alt(PLATZ_PARAMETERSUMME)`; on mismatch a `Meldung` naming **both**
numbers and the address, then `festkomma::abbruch` — `[[noreturn]]` (`festkomma.hpp:62`),
so no substitute value is reachable. Probe: `schritt_probe.cpp:1072`
`BRICHT_AB_MIT("fremder Parametersatz", Riegel::Parametersatz, {"kern::schritt",
"Pruefsumme des Parametersatzes"})`, called from main at :1192, and `Riegel::Parametersatz`
stands in the list at :192 that the 0107 probe holds against the emitted messages.

Three transcriptions of the seven key fields agree in order: `schritt.hpp:144-150`,
`schritt_probe.cpp:1016-1022`, and the declaration order in `Konstanten` (`werte.hpp:115,
119, 123, 127, 131, 141, 153`). `zustimmung_elastizitaet` is last in all three,
`leitzins_start`/`durchgriff` follow it and stay out — `schritt_probe.cpp:1054-1057`
measures that they do not move the sum. The mistake 0208's reviewer expected is not made.

**Determinism (my question 1).** Integers only. `parameter_pruefsumme` is `constexpr` and
sums through `pruefsumme::Summe::nimm_i64`, which decomposes the *value* by shifts
(`pruefsumme.hpp:132-139`), not the memory image. No float, no unordered iteration, no
address in the result. `static_cast<i64>` of the u64 sum can be negative; its state address
carries `Skalenklasse::Kennung` (`zustandsausgabe.hpp:359`) and no bound, and the number is
printed (`zustandsausgabe.cpp:209`) — the gate is diagnosable from the state output alone.
The header's error order (`schritt.hpp:173-182`) holds: the `Schreiber` ctor stands between
the round check and the checksum and can abort itself (`schreiber.cpp:203-207`,
`welche_runde < 1`), but `schritt.cpp:629` already excludes that case.

## Finding 1 — the probe count fell by one, caused by this package

| tree | 2026-09-07 | 2026-09-08, HEAD d17b26d |
|---|---|---|
| root | 25 of 26 | 24 of 26 |
| werkzeuge/zahlwort | 3 of 3 | 2 of 3 |

New red on both paths: `zahlwort_messung` (report :114 root test 26, :484 standalone
test 3). How it is produced:

1. `befunde/messung-0180/messen.py:279` reads the **live** `kern/include/kern/werte.hpp`.
2. Case A2 (:311-323) appends a declaration and compares the finding list literally
   (:339-340). Its fifth entry is hard-coded `"Zeilennummer 157: 'zweiundzwanzig Groessen'
   nennt 22, gezaehlt sind 23"` (:322).
3. 0229 inserted the `zustimmung_elastizitaet` field plus two head paragraphs above that
   point. The line it means, `// Die zweiundzwanzig Groessen aus T48 ...`, now stands at
   `werte.hpp:185` — 28 lines lower. Measured 185, expected 157 (report :129-135, :499-505).

Nothing else moved `werte.hpp`: the four commits before `d17b26d` claim `specs/`,
`daten/reihen.toml`, `aufgaben/` and `werkzeuge/belegstellen`. The same test was green on
2026-09-07 (that report :436, 3 of 3). The other red entry, `belegstellen_kopfzahlen`, was
already red on 2026-09-07 and is not counted against this package.

`befunde/messung-0180/messen.py` is **not** in 0229's `dateien`, so the builder could not
have pulled it along. This is a fact about the criterion, not a reproach: condition 4 says
the count governs. Proposal `0232` carries the repair.
