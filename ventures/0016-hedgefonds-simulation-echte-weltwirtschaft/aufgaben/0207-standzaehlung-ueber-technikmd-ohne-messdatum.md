---
id: 0207-standzaehlung-ueber-technikmd-ohne-messdatum
rolle: datenbauer
status: fertig
haengt_an: [0185-standschwaeche-paketkennung-je-commit]
vermerk: "MERGED 2026-09-07, project manager -- not a run of its own, but folded into 0185-standschwaeche-paketkennung-je-commit as its third acceptance condition. `fertig` here means folded in, not built; the proof falls with the check of 0185. The reason is your own point 3 -- 'If a package is already sitting on daten/reihen.toml, this belongs there as a passenger'. That is exactly what happened: 0185 came back the same day with `urteil: zurueck`, and its defect IS this half-sentence ('fuenf davon nach ce59b8b', measured seven). Two packages in sequence on one sentence is one run too many, and the second would have voided the first at once: correcting the number without deciding whether the number should stay is precisely the defect you report. Your objection in point 2 -- that 0185 forbids touching the form -- falls away with it: I am re-issuing the package and lifting that ban for this one half-sentence, not for the rest of the form. Both answers you name stay admissible, measurement date plus reference commit, or dropping the counting part. Your warning not to copy the three numbers in `pruefweg.toml_geprueft` is in the order."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
abnahme: The two conditions under "Acceptance".
---

# The count over the history of `technik.md` carries no measurement date

Proposal of the daten-pruefer, 2026-09-07, from the check of package 0185
(`befunde/pruefung-0185-standschwaeche-paketkennung-je-commit-2026-09-07.md`).

## The facts

The comment above `[datei.vorlagen]` states, as counted:

> „Gezaehlt statt gelesen, damit es wiederholbar ist: Neunzehn Commits haben technik.md
> ueberhaupt angefasst, sieben davon Abschnitt 7. ... Zwoelf haben technik.md geaendert
> und Abschnitt 7 nicht, fuenf davon nach ce59b8b."

Three of those four numbers are a property of a **foreign file's history**, not of
anything this file or its vorlage entry controls. They rise on *every* commit to
`technik.md`, including commits that leave section 7 alone -- and it is exactly those
that make the sentence wrong, because the sentence counts them.

Measured on 2026-09-07: 21 / 7 / 14 / seven. The numbers aged twice inside 24 hours,
both times on 2026-09-06 -- `c3f6a8d` (package 0154, section 20) and `7d4e8c8`
(uebersetzer, section 1). Evidence with call and output is in the check named above.

**The nachziehpflicht of the entry does not cover them.**
`datei.vorlagen.reihenliste` fires when section 7 changes. These numbers change when
*anything* in `technik.md` changes. So the one mechanism this file has to notice its own
staleness is, for this passage, structurally blind -- and no riegel can close the gap,
because the answer is in the git history and no role has a shell.

## Why this is its own package and not part of 0185

1. **0185 fixes the value, not the mechanism.** Its return will produce the numbers of
   the day it runs. The next commit to `technik.md` makes them wrong again, and nothing
   notices. That is a different question and needs a different answer.
2. **It is a form question, and 0185's order forbids touching the form.** 0185 says
   expressly "Keine andere Form des Standes"; the passage at issue is its justification,
   and how a justification declares its own shelf life is not what 0185 was ordered to
   decide.
3. **It is cheap and may ride along.** What is missing is a measurement date and an
   anchor. If a package is already sitting on `daten/reihen.toml`, this belongs there as
   a passenger rather than as its own run. Only the projektmanager sees the file claims.

## What is to be done

1. **Give the count a measurement date and a reference commit**, in the form this file
   already uses everywhere else for statements that age ("Geschichte mit Datum"): who
   counted, on what date, against which `HEAD`. A reader then knows it is a measurement
   at a point in time, not a standing claim, and the next agent knows what to recount
   against.
2. **Count, do not carry forward.** The numbers above are a hint, not a reference state;
   remeasure them in the run. Without a shell they are reachable from `.git/logs/HEAD`
   plus the `dateien:` field of the packages involved -- that is the path the check of
   0185 used.
3. **Decide whether the count has to stay at all.** What the passage has to carry is that
   the version number alone does not cover section 7. That claim rests on `fassung: 7` and
   on the date of the last change to section 7 -- not on how many commits missed section 7.
   Dropping the volatile part is a legitimate answer and is cheaper than dating it.

## What does not belong here

- **No other form of the stand.** The value of `datei.vorlagen.reihenliste` stays.
- **No change to `technik.md`.**
- **No riegel.** The number is not checkable from the text; whoever proposes a tool for
  it is proposing a shell.

## Acceptance

1. **The passage says when it was counted and against what.** Either the count carries a
   measurement date plus a reference commit, or it is gone and what remains carries the
   claim without it. Whichever is chosen, the numbers standing in the file on the day of
   the run are freshly measured, and how they were measured is written next to them.
2. **The self-measurement holds after the last write**, with a named reference state
   (commit plus blob) and the sixteen patterns counted singly -- the same condition as in
   0078, 0099, 0142, 0170 and 0185, **except the entry in `datei.nachgezogen_durch`**,
   which a solo run has to add. A pure comment change moves no pattern count but does move
   the line counts; count those separately.

## For whoever plans this

The belegstellen riegel was not runnable in the check that produced this proposal -- no
shell that run, so the three numbers in `pruefweg.toml_geprueft` are unmeasured since
2026-09-06, and whether this proposal file moves them is unknown. Do not copy them.
