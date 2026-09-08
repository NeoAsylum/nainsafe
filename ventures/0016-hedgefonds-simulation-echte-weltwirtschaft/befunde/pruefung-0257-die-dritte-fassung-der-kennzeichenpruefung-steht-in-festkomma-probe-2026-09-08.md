---
typ: pruefung
paket: 0257-die-dritte-fassung-der-kennzeichenpruefung-steht-in-festkomma-probe
pruefer: test-pruefer
datum: 2026-09-08
urteil: zurueck
kriterium_geprueft: "Structure, site accounting and per-riegel counts verified by independent recount; the no-red-attributable-to-this-file clause fails on two riegel findings naming lines 136 and 259 of the package's own file."
befunde: 2
---

# Review 0257: the mechanism is right, two comments in the delivered file turn two riegel red

## What holds (checked, not assumed)

- **Buch in, macro out.** `festkomma_probe.cpp:340` builds
  `probe::kennzeichen::Buch<Riegel, RiegelOhneZustand>`; `ABBRUCH_MELDET` survives only
  in comments (`:136`, `:501`), no definition, no call site (own grep).
- **Site accounting, recounted at HEAD.** `Grep -n abbruch festkomma.hpp`: nine call
  sites (`:84 :121 :138 :158 :203 :219 :313 :345 :348`; `:62` is the declaration) —
  matches the mapping comment `festkomma_probe.cpp:141-162` one to one. The
  three-riegel split of `:84` is complete: `nach_i64` has exactly three callers
  (`:141` teile_gerundet, `:162` mal_geteilt, `:293` mal — own grep), none missing.
  `:121` is the one `RIEGEL_OHNE_ZUSTAND` entry, with its `warum` (`:285-292`).
- **Counts are exact and forced.** 17 `BRICHT_AB_MIT` calls counted per riegel =
  `SOLLZAHLEN` exactly (2,1,1,1,3,2,2,2,2,1); `static_assert` nets on list sizes and
  ordering (`:296`, `:336-337`). Go-red property: exact per-riegel counts plus the
  eigene/fremde cross-check in `buch.auswerten()` — collapse two guards into one branch
  and the arriving message stops matching its list (mechanism verified in reviews 0244
  and 0255, same apparatus).
- **The probe itself is green.** `befunde/uebersetzung-2026-09-08.md`: compile clean,
  `festkomma_probe` Passed in the root tree (2/27) and the kern tree (13/13).

## Finding 1 — bezeichner_riegel red on `festkomma_probe.cpp:136`

Reproduce: run the bezeichner_riegel ctest (root test 22 or
`werkzeuge/bezeichner`). Output (uebersetzung-2026-09-08.md:117-121): „1 Bezeichner in
Kommentaren des Kerns loesen nicht auf: kern/test/festkomma_probe.cpp (Zeile 136),
genannt: ABBRUCH_MELDET". The package removed the macro and wrote a new history comment
naming it; the identifier no longer resolves. Caused entirely inside the package's one
owned file — not a foreign lane.

## Finding 2 — belegstellen_riegel red on `festkomma_probe.cpp:259`

Reproduce: run the belegstellen_riegel ctest (root test 17 or
`werkzeuge/belegstellen`). Result: 42 Zitate, 41 aufgeloest; the one unresolved is
„zitierend: kern/test/festkomma_probe.cpp:259" (uebersetzung-2026-09-08.md:356) — the
new comment's citation „(`festkomma.hpp`, Absatz \"Ueberlauf\" ueber `wurzel`)". Both
the previous and the current tool version report it (A vorher/nachher, Code 1), so it
is not an artifact of tonight's tool lane. Side effect: the same added citing line
shifts the corpus counts (42/54 vs the 41/53 committed in the tool's head), part of the
belegstellen_kopfzahlen drift; apportioning that drift against other lanes needs git
and is not charged here.

## Verdict

The acceptance clause as rewritten by the PM — no red „attributable to
`festkomma_probe.cpp`" — fails on both findings: each riegel names a line this package
wrote, in the one file in its `dateien`. Everything else in the acceptance is met.
The fix is two comment rewordings inside the package's own file; no new package needed,
hence `zurueck` to 0257 itself.

Searched and not found: missing abort sites (recount above), lumped or dropped riegel,
count weakening (17 registered aborts vs. formerly 7 needled sites), a stale
`fehlgeschlagen` chain (`pruefe` and `buch` share the global by reference, `main`
returns 1 on nonzero).
