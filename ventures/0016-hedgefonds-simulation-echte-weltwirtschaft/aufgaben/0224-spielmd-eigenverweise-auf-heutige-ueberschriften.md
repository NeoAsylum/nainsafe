---
id: 0224-spielmd-eigenverweise-auf-heutige-ueberschriften
rolle: spielentwerfer
status: offen
haengt_an: []
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md]
abnahme: "(1) `Grep \"Die Grenze des Orakels\"` over `spiel.md` returns no hit, and the reference at today's spiel.md:1606 names the heading that stands in the file now, so a grep for its newly quoted words hits the heading line (today spiel.md:2835, `**And the limit of the oracle, explicitly.**`). (2) The Meldung carries the sweep as a table, one row per internal section reference of the form *Kursiv* or „Anfuehrung\" in spiel.md: line, quoted target, and the heading line it resolves to -- plus, for every reference that did NOT resolve, either the repair as old wording -> new wording, or a per-site reason for leaving it. The sweep names the call it used, so the reviewer repeats it instead of re-searching. (3) No heading is renamed back to German and no reference is deleted to reach resolution. No condition needs a shell, a build, or the next nightly report."
vermerk: "ACCEPTED 2026-09-07, project manager -- cut by me from the Meldung of 0222 and verified in this run before I wrote it. The site is real: `spiel.md:1606` reads \"stands under *Die Grenze des Orakels*\", and that heading no longer exists -- `spiel.md:2835` carries \"**And the limit of the oracle, explicitly.**\" since the translation. || I CHECKED THE NEIGHBOUR SO YOU DO NOT HAVE TO. Two lines below, :1608 cites *Was bewusst fehlt*; that one RESOLVES -- the heading still stands German at `spiel.md:2859`, although `ops/uebersetzt.txt` lists the section as translated. Do not \"repair\" it. It is also the warning for your sweep: `uebersetzt.txt` records that a section was worked, NOT that its heading changed. Resolve every reference against the file, never against that list. || WHY THE SWEEP AND NOT JUST THE ONE LINE. `belegstellen_riegel` scans code and toml; it has never read `spiel.md` prose. So the citations inside the specification are covered by no test at all, and this is the third translation wave. One line is a fix, the sweep is the measurement -- and since everything here lives in one file, it is one package either way: `spiel.md` cannot be split across two builders. Keep it to references, though. This is not a revision of any section. || THE FOUR QUESTIONS, CHECKED. `spielentwerfer` is a real role in `baulauf.py:BAUROLLEN`, reviewed by the `entwurf-pruefer` -- the pairing that just carried 0223 through with 0 findings. `haengt_an` is empty; nothing precedes you. No other open package lists `spiel.md`: 0221 is `offen` but its `dateien` is `technik.md` alone, so it collides with nothing of yours. The acceptance runs on `Grep` and `Read`. || DO NOT TOUCH `technik.md`. `technik.md:1802` carries the same dead reference (\"exactly the four that `spiel.md` enumerates under „Die Grenze des Orakels\\\"\"). It is not in your `dateien`, the file has stood in `ops/reserviert.txt` for seven days, and your role has no `Edit` reaching it. Report it in your Meldung; it is on my list and I carry it. || YOU ARE THE SECOND OF TWO LANES TONIGHT. Fifteen of nineteen open packages are frozen behind that reservation and the third free-looking one waits on a blocked package, so without you the factory builds with one agent. Quoting follows the document you cite, not the one you write in -- `spiel.md` is German under `CLAUDE.md`, but a heading that reads English today gets quoted in English."
---

# spiel.md's own section references still point at pre-translation headings

Carried out of `befunde/pruefung-0222-zitate-auf-uebersetzte-technik-abschnitte-nachziehen-2026-09-07.md`,
where the reviewer confirmed the site and marked it "new". Re-verified by the
project manager on 2026-09-07 before this package was cut.

## The evidence

- `spiel.md:1606`: "The price of this cleanliness belongs with it and stands under
  *Die Grenze des Orakels*". `Grep "Die Grenze des Orakels"` over `specs/` hits
  exactly two lines — this one and `technik.md:1802`. Neither is a heading.
- The heading it means is `spiel.md:2835`: "**And the limit of the oracle,
  explicitly.** Without a target series are: **sector …**".
- Counter-check, already done: `spiel.md:1608` cites *Was bewusst fehlt*, and that
  heading does still stand at `spiel.md:2859`. Not every reference is broken.

## Why an own package

- 0222 repaired the same defect class in the riegel's scan set (code and toml) and is
  `fertig`; its builder reported this site as outside his `dateien`, which it was.
- No test covers it: `belegstellen_riegel` does not scan `spiel.md` prose. A dead
  reference inside the specification stays invisible until a reader hits it.
- `spiel.md` is claimed by no other open package and is out of `ops/reserviert.txt`
  since 2026-09-06, so this runs tonight.

## Scope

References only — the wording that names another section. No rule, no formula, no
count, no heading is changed. Third wave of this class; whether the nachzug belongs in
the uebersetzer's own loop is the operator's open decision (`ops/plan.md`, B).
