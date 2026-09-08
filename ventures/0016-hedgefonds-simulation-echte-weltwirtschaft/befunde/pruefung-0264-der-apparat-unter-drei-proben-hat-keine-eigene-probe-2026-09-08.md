---
typ: pruefung
paket: 0264-der-apparat-unter-drei-proben-hat-keine-eigene-probe
pruefer: test-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: "all twelve Sollzahlen re-derived from auswerten()'s source independently of the builder; presence, add_test and green run taken from the runner's report"
befunde: 0
---

# Pruefung 0264: kennzeichen_probe

## How each acceptance clause was checked

**In `add_test`, runs in the nightly.** `kern/CMakeLists.txt:60` collects `test/*.cpp`
with `CONFIGURE_DEPENDS`; the loop at :381-387 makes an executable and `add_test` per
file. The runner's report (`befunde/uebersetzung-2026-09-08.md`) shows the collector at
13 Proben (12 on 2026-09-07), `kennzeichen_probe` compiled in both builds and **Passed**
in the kern ctest (3/14) and inside the root run (28 tests; the only reds are the two
pre-adjudicated `belegstellen_*` head-drift lanes, Bezugsstand 2f2f79f vs HEAD 702cf37).

**Own enumerations.** The file's only includes are `kennzeichen.hpp` and the mandated
`kern/sperre.hpp`; `Riegel`/`RiegelOhneZustand` live in its anonymous namespace. No
`kern::werte/schritt/festkomma` name occurs.

**Counter against a target.** `kennzeichen_probe.cpp:393` compares with `==`, not `>=`;
over-counting fails too.

**The twelve Sollzahlen, re-derived from `kennzeichen.hpp` without the builder's
numbers.** Healthy run: 4 messages (2 Untergrenze via both entrances, 1 each
Ober-/Seitenwand), 12 ordered pairs = 2 own + 10 foreign, no list shares a piece with a
foreign message -> 0. Case 2a: 3x Vollzaehligkeit (:363-376) + `fremde_paare>0` +
`eigene_paare>0` (:487-488) + `ohne_zustand_paare>0` (:494-496; table non-empty, 0
messages) = 6; 2b lacks only the third verlange = 5. **The +1 differential is exactly the
assertion 0259 relaxed — its red proof.** 3a: "verletzt" sits in both Untergrenze
messages and in M_OBEN -> 2 foreign hits + `verletzungen==0` = 3. 4a: "Zugang eins"
misses M_UNTEN_ZWEI -> 1 own-pair miss + verletzungen = 2. 5a: only Obergrenze unseen =
1; the third Riegel keeps both pair counts >0, so nothing else fires. 6a: "" and nullptr
both die in `merke`'s guard (:305-313), counted, not filed = 2; 6b files them, Seitenwand
then carries 3 messages, still 0.

**Red-if-broken, by deletion test on the apparatus (mentally, no file touched):**
dropping the empty-directory print (:433-438) reddens every `tabelle_leer` case via
`zeile_steht==tabelle_leer` (:394); Vollzaehligkeit -> 5a, 2a; the foreign-pair check ->
3a; the own-pair check -> 4a; `ohne_zustand_paare>0` -> 2a; the merke guard -> 6a. Each
abnahme clause has a case that notices its mechanism's loss.

**Output routing.** The probe's verdict goes to stderr, the apparatus's announcements to
stdout, redirected per case into the Mitschrift and read back; "keiner eingetragen"
occurs in no other stdout line (entry print :478 incl. the `warum` text checked), so the
substring test cannot false-positive.

**No existing probe touched.** Commit ec1ef8c carries 3 files (probe, package file,
builder logbook); the three probes pass unchanged; `kennzeichen.hpp` is not in the
package's `dateien` and unchanged at HEAD.

## Reading applied to "jeder einmal rot und einmal gruen"

Case 1's own abnahme text specifies **gruen**; its announcement leaves no counter trace
(probe head :43-46), so no counter-red exists for it. The pair 1a/1b instead toggles the
checked property both ways: line demanded present when empty, absent when not — an
apparatus printing it always or never goes red either way. Judged sufficient; stated here
rather than silently assumed.

## Noted, no defect: one undeclared residual gap

`alle_stuecke_in` (kennzeichen.hpp:164-172) demands **all** pieces. No case carries a
multi-piece list partially overlapping a foreign message, so a regression to any-piece
matching would pass all 12 cases. The head's gap list (probe :48-56) declares seven
residuals, not this one; it costs one Aufbau row and one pair. Left to the
testentwickler/PM — below the bar for a package of its own.
