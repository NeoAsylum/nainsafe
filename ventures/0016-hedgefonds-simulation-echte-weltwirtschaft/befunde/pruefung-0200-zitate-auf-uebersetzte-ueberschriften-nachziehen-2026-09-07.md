---
typ: pruefung
paket: 0200-zitate-auf-uebersetzte-ueberschriften-nachziehen
pruefer: test-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: located all ten citations, resolved each by hand against today's specs wording, and confirmed the runner's post-fix ctest report shows belegstellen_riegel green in both builds
befunde: 0
---

# Geprueft: ten citations, ten current targets, riegel green

**The criterion and how it was checked.** This role has no shell; the executable
evidence is the runner-generated report `befunde/uebersetzung-2026-09-07.md`,
regenerated after the fix: ctest `belegstellen_riegel` **Passed** in the venture build
(test 16/21, 1.03 s) and in the standalone build (1/1, 0.99 s), ctest Code 0 both
times. The green path in `belegstellen_riegel.cpp` (`return 0`, line 4180) is
reachable only with all three finding lists (`befunde`, `zitatbefunde`, `tote_ziele`)
empty — "zero unresolved Abschnittszitate" follows from Passed, it is not assumed.

**Does it turn red when broken? Measured, same day.** Before the fix the same report
showed FAILED (Code 8), "10 Abschnittszitat(e) finden ihre Ueberschrift nicht"
(quoted in `befunde/pruefung-0147-belegstellenriegel-ortsfrage-mit-anker-2026-09-07.md`,
Finding 2 — the report file itself is overwritten each run). A red-to-green
transition on the real corpus, on exactly the property under test, is the strongest
wird-es-rot evidence this pruefung can have.

**The ten citations, each resolved by hand against today's wording:**

| citing | quotes | target in force today |
|---|---|---|
| `kern/include/kern/aktion.hpp:10`, `:82`, `:401`; `parameter.toml:787` | "The actions" | `spiel.md:385` `## The actions` |
| `kern/include/kern/schritt.hpp:7`; `kern/src/schritt.cpp:122`; `belegstellen_riegel.cpp:33` | "The loop" | `spiel.md:262` `## The loop` |
| `daten/adressen.md:5` | "The state" | `spiel.md:417` `## The state` |
| `kern/include/kern/zustand.hpp:227` | "The fund" | `spiel.md:448` bold lead `**The fund:**` |
| `daten/reihen.toml:468` | 'What that requires -- attribution, concretely' | `daten.md:333` bold lead |

Ten found, ten resolve, none deleted — every one still carries keyword, quotation and
target file, so the riegel still counts it. The five German targets named in the 0147
pruefung ("Der Zustand", "Die Aktionen", "Die Schleife", "Der Fonds", "Was dafuer zu
tun ist -- Namensnennung, konkret") are all covered by this set.

**Weakening searched, not found.** `SCHLUESSEL` is still the four German keywords
(line 1488, no English keyword added or removed); case sensitivity kept ("Gross- und
Kleinschreibung zaehlt", line 4257); the zero-citation abort (line 4150) and the
floor `AUFGELOEST_MINDESTENS = 16` (line 2470) are intact, the floor's written
rationale dated 2026-09-05, before this package. No heading in `specs/` was renamed
by the builder: mechanically impossible (`Edit(ventures/**)` does not reach `specs/`);
the renames are the uebersetzer's, ledgered in `ops/uebersetzt.txt`.

**Limits of this pruefung.** (1) No diff without a shell: that `reihen.toml` and
`parameter.toml` were touched only on the citation wording is checked by reading
those lines, not by diffing; any collateral edit there falls to the 0185/0203
reviews, which own every other line of those files. (2) The uebersetzer keeps
running; the report is green as of its last regeneration. If a later rename kills a
citation again, that is the recurring half already flagged in the package body — a
new finding with place and time, not a 0200 defect.
