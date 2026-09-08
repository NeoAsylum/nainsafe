---
typ: pruefung
paket: 0149-t56-zweite-kuerzeltabelle-und-wirksame-zusicherung
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: all three acceptance conditions checked against technik.md T56 (lines 3661-3746), the live source files, and a six-anchor line reconciliation for the diff condition
befunde: 0
---

# Review 0149 — T56 second abbreviation table and effective assertion

Checked against the three conditions under "Abnahme" in the package. T56 found via
`ops/inhalt-0016-...md` (section 19, 3554-3790) and `Grep -n "T56"`, read 3661-3790.

## Condition 1 — both locations stand in T56: MET

- `technik.md:3673-3674` names `GEBIET_KUERZEL` in `kern/src/zustand.cpp` "and a second
  one of the same name in `kern/src/zustandsausgabe.cpp`".
- `:3709-3718` gives the second version file and identifier, quotes its comment („Zweite
  Fassung derselben Liste"), states "A sixth region therefore needs an abbreviation in
  **both**", and names the guard that covers it today: `zustandsausgabe_probe` at run
  time, mechanism included (reads each region's abbreviation from its own trade address
  via `index_zu_adresse`).
- `:3720-3725` chooses consolidation into `zustand.hpp`; the alternative (keep the copy
  → owes "an explicit second step, with the run-time probe as its only cover") is named.
- `:3737-3741` marks the one-file/all-guarded procedure as "the target, not today's
  state" — the original false claim is gone. No line numbers cited in T56.
- Reality check against source: `kern/src/zustandsausgabe.cpp:54` carries the comment
  „Zweite Fassung derselben Liste", `:60` the declaration; `kern/src/zustand.cpp:403`
  the first version. Both match T56's description including "size given as `GEBIETE`".

## Condition 2 — assertion bites at compile time: MET

- `:3727-3729` demands the derived form: `constexpr std::array GEBIET_KUERZEL = {…}`
  (CTAD, "no size in the type") with `static_assert(GEBIET_KUERZEL.size() == GEBIETE)`.
- `:3729-3733` says in one sentence why the given-size form cannot fail ("compares
  `GEBIETE` with `GEBIETE`: true by construction") and gives the error recipe
  (`GEBIETE = 6`, `LAENDER = 5`, tables untouched).
- Mechanical check: `Grep -n "static_assert(GEBIET"` over technik.md → one hit, `:3729`,
  the derived form. `Grep "std::array<const char"` over technik.md → 0 hits file-wide.
  No version of the assertion on a given-size array remains in the section.

## Condition 3 — no removed/changed lines outside T56: MET (by reconciliation)

No shell, no git diff available; verified by anchor reconciliation against my own
line measurements from tonight's 0158 run-2 review, the freshest pre-0149 epoch
(only commit 40cc0ee touched technik.md since; the file lane was locked to 0149 and
the working tree is clean):

- Above T56, 0 shift, wording intact: "eight" `:2477`, "117" `:2489`, `ueber_fenster`
  `:2516` and `:2524` — all at identical lines.
- Below T56, uniform +28, wording intact: `ueber_fenster` `:4964→:4992` and
  `:5212-5214→:5240-5242`; cross-check `:5183` ("Four clauses outside T61") closes the
  chain 5108 (pre-0158 epoch) +47 (0158 build) +28 (0149) = 5183 exactly.

Six anchors admit exactly one net +28 insertion between `:2524` and `:4964`; the new
material sits at `:3709-3745` inside T56. Residual: a compensating add/remove pair
between `:3746` and `:4964` would be invisible to sampling — no anchor exists there;
nothing suggests one, and no role but the architekt could have written the file.

## What I looked for and did not find

Old tautological assertion elsewhere (grep, 0 hits); line-number citations in T56
(none); the old "alles in einer Datei" claim stated as today's state (caveated at
`:3740-3741`); contradiction between T56's consolidation and the T55 assert list
`:3701-3707` (none — different constants).
