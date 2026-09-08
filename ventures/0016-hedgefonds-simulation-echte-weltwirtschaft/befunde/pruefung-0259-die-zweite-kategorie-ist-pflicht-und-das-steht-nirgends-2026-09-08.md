---
typ: pruefung
paket: 0259-die-zweite-kategorie-ist-pflicht-und-das-steht-nirgends
pruefer: test-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: guard and empty-case print verified by reading auswerten(); three probes green per runner report at HEAD 6f2ec03; demonstration clause discharged via declared proposal 0264
befunde: 0
---

# Pruefung 0259 — geprueft

**Object.** `kern/test/kennzeichen.hpp` alone. 0263's `dateien` names only
`werkzeuge/kennzeichen/kennzeichen_riegel.cpp`, so the header at HEAD `6f2ec03` is this
package's delivery.

**Criterion 1 — empty second category no longer reddens.** `auswerten()` guards the
counter: `if (!ohne_zustand_.empty()) verlange(ohne_zustand_paare > 0, ...)`
(`kennzeichen.hpp:494-496`). With an empty span the entry loop at :440 never runs, the
counter stays 0, and nothing else in `auswerten` reads the second category. Red-before is
on record in the package's own "Measured at HEAD" (unconditional `verlange` at the
then-:445), verified by the PM at acceptance.

**Criterion 2 — non-empty unchanged.** The `verlange` inside the guard is the old
condition verbatim. For a non-empty directory the guard is true and the empty-case print
does not fire, so the executed path — and the probes' output — is identical to before.
The guarded failure (non-empty directory, no arrived message → `ohne_zustand_paare == 0`)
still goes red.

**Criterion 3 — empty case printed.** :433-439 prints `keiner eingetragen ...` exactly
when the span is empty, in every run, inside `auswerten`.

**Criterion 4 — three probes unchanged green.** Runner report
`befunde/uebersetzung-2026-09-08.md`: kern ctest 13/13 Passed, `schritt_probe`,
`werte_probe`, `festkomma_probe` among them. Root-ctest reds are
`belegstellen_wortabstand`/`belegstellen_kopfzahlen`, both on `belegstellen_riegel.cpp`'s
own head comment (Bezugsstand 2f2f79f vs HEAD) — not attributable to the header, per the
vermerk's attribution rule. Untouched: `dateien` names only the header, no probe cites
0259, and `kennzeichen_riegel` (reads the probes' tables from source) Passed. None of the
three is empty: array sizes 1/1/1 (`schritt_probe.cpp:443`, `werte_probe.cpp:360`,
`festkomma_probe.cpp:286`).

**Demonstration clause ("einmal vorgefuehrt, nicht stehengelassen").** Nothing left
standing: the header holds no fourth enumeration or demo apparatus (whole file read). An
*executed* demonstration was structurally impossible under the vermerk's own rules —
builders have no shell, the runner runs only the committed tree, and an executable empty
case lives in a probe TU, which the vermerk forbade editing. The builder took the branch
the vermerk sanctioned ("that is a finding and a package"): proposal
`aufgaben/0264-der-apparat-unter-drei-proben-hat-keine-eigene-probe.md`
(`status: vorschlag`, `haengt_an: 0259`), whose case (1) is exactly this red/green
demonstration. I read 0264 only after forming the mechanical verdict, to establish the
clause's discharge — not as the builder's reasoning.

**Searched, not found:** weakening beyond the sanctioned one (`fremde_paare`,
`eigene_paare`, `verletzungen` checks unchanged, :487-497); leftover demo apparatus; the
stale sentence „Beide Proben haben einen solchen Fall" (gone from :43); dead names in
comments (bezeichner_riegel Passed); new unresolved citations (41/41 resolved — the 0257
stray is gone).

**Residual, for the PM, not charged:** the lost assertion (last entry removed vs. empty
born) is documented honestly at :65-72; its replacement is split across 0263 (landed) and
proposed 0264. Until 0264 runs, the empty branch at :433/:494 has never executed anywhere.
