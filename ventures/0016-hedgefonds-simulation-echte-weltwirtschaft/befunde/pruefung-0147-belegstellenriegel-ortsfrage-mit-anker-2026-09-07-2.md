---
typ: pruefung
paket: 0147-belegstellenriegel-ortsfrage-mit-anker
pruefer: test-pruefer
datum: 2026-09-07
urteil: zurueck
kriterium_geprueft: read the executed belegstellen_messung run in today's runner report and re-verified all nine needles character-wise against HEAD; the stand dies in its own Teil-0 probe with Rueckgabe 2 -- still nothing measured
befunde: 2
---

# Zurueck again: the stand ran, and it cannot measure -- one wrong constant

## Finding 1 -- the selbstprobe expects the wrong string, every run exits 2

`befunde/messung-0147/messung.py:233`: `("genau einmal", "axb", "a", "ayb")`.
`einmal_ersetzen(text, alt, neu)` replaces the needle, so
`einmal_ersetzen("axb", "a", "y")` returns `"yxb"`. The probe expects `"ayb"` --
that is the result for needle `"x"`. One typo'd constant, `selbstprobe()` counts a
deviation, `messe()` raises `Messfehler`, the stand exits 2 before compiling
anything.

Not simulated -- executed: `befunde/uebersetzung-2026-09-07.md`, Test 18/23
(workspace) and Test 2/2 (standalone), both `***Failed`:

    ROT Selbstprobe: `einmal_ersetzen` geht im Fall 'genau einmal' aus als yxb, erwartet war ayb.
    Messstand 0147: NICHT GEMESSEN -- der Auswerter misst nicht. [...] Rueckgabe 2.

So the abnahme's measurements ("je einzeln nachgewiesen", "beide im selben Aufruf
gemessen") have still never run; the nine mutants have never been compiled.
Reproduce: any ctest run of `werkzeuge/belegstellen`, or evaluate
`"axb".replace("a", "y")`. The fix is one constant -- needle `"x"` (the intent: the
neighbour cases probe "fehlt"/"zweimal", this one the single hit) or expectation
`"yxb"`. The builder chooses; I repair nothing.

What did hold: the wiring failed **loudly**. The probe ran on both build paths and
turned the report red instead of silently green -- exactly the failure mode the
CMake comments promise. Verified: `add_test` without silent `if(EXISTS)`
(`FATAL_ERROR` instead, CMakeLists.txt:75-81), `--vorhaben`/`--uebersetzer` from
CMake, TIMEOUT 600 below the runner's 900.

## Finding 2 -- the corpus is red again: the predicted eleventh heading

`belegstellen_riegel` FAILED in both builds today: "2 Abschnittszitat(e) finden ihre
Ueberschrift nicht" -- `daten/reihen.toml:406` and `:556` cite the lead-in "Der
Leitzins ist seit dem 2026-09-03 keine Sollreihe", and `specs/.../spiel.md:2447`
carries that passage since today in English ("The policy rate has not been a target
series since 2026-09-03."). This is the case the 0200 vermerk foretold: a heading
renamed after 0200's fix is "a finding and not a Ruecklauf". Consequence for 0147:
the clause "Der Riegel bleibt auf dem dann geltenden Korpus gruen" is falsified
today, and even with finding 1 fixed, Teil 1 returns 1 (both versions red on this
corpus). Not a defect of this package. Proposal written:
`aufgaben/0214-leitzins-zitate-auf-uebersetzten-wortlaut-nachziehen.md`.

## Also verified, nothing found

* All nine needles hit today's HEAD exactly once, compared character-wise including
  indentation: M1-M4 `belegstellen_riegel.cpp:2297-2308`, M5 `:2316`, M6-M9 = the
  whole `waehle_zitatform` body `:2751-2772` (0200 touched the file after the last
  static check, so this needed redoing).
* The auswerter's patterns match the riegel's real output: closing line `:3975`,
  `Ortsfall %zu:`/`Formfall %zu:` at `:2370-2403` and `:2850-2896`.
* No weakening: rc 1 and rc 2 are both red under ctest; strict `git()` for
  measurement inputs (`log -S`, `show`), lenient only for report decoration
  (`rev-parse HEAD`, `status`, `log --oneline`); no threshold, expectation or old
  case touched -- the `.cpp` is unchanged by this rework.
