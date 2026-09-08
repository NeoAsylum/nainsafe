---
typ: pruefung
paket: 0266-zwei-befunde-datieren-sich-auf-den-zweiten-september
pruefer: daten-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: derivation over `dateien:`/`status:` rerun from scratch for both files, dates read out of the four pruefung befunde, and frontmatter-only confinement shown by every cited line number still landing
befunde: 0
---

# 0266, first round: the derived set is two, not the four the proposal assumed

## The derivation, rerun independently

`Grep '^dateien:.*(deckungsbefund-1997|lizenzbefund-reihen)\.md'` over `ventures/**/aufgaben/*.md`
(snapshot copies under `befunde/messung-*/baum/` discarded) gives the complete claim set:

| File | Packages naming it in `dateien:` | `status` | date from its `pruefung-…` |
|---|---|---|---|
| `deckungsbefund-1997.md` | `0006` (the originating package, `paket:` field) | fertig | — |
| | `0256-die-richtigen-zahlen-…` | fertig | 2026-09-08 |
| | `0262-punkt-zwei-und-drei-…` | fertig | 2026-09-08 |
| | `0266` (this one) | gebaut | — (excluded by the `fertig` rule) |
| `lizenzbefund-reihen.md` | `0014` (originating) | fertig | — |
| | `0018-lizenzbefund-klaerungsliste` | fertig | 2026-09-02 |
| | `0024-notenbanken-unter-reihe-2b` | fertig | 2026-09-02 |

Dates come from the `datum:` in each package's own pruefung befund, not from its filename; all
four read `urteil: geprueft`. `deckungsbefund-1997.md:6` now names exactly `0256` and `0262`,
each at 2026-09-08.

**The set differs from the proposal, and the file is right.** I proposed this package claiming
four packages had rewritten the body — `0252`, `0253`, `0256`, `0262` — and wrote the same in
`pruefung-0262-…-2026-09-08.md:71`–`:73`. `0252` and `0253` name
`daten/quellenbefund-leitzinspfad.md` in `dateien:` and have never had a claim on this file.
**The wrong number is mine, the builder's two is correct.** It survives only in the proposal
body (`aufgaben/0266…:23`) and in that earlier befund, both historical records; no data file
carries it.

**`lizenzbefund-reihen.md` is correct unedited.** The derivation returns `0018` and `0024`, and
the field has named both at 2026-09-02 since 2026-09-02. Nothing to add — this is the
"already current" case, not the "yields nothing" case of the appended condition.

## Frontmatter only — how that is shown without `git`

- Field structure against the pre-edit copy `befunde/messung-0069/baum/daten/deckungsbefund-1997.md`:
  twelve frontmatter lines, same field order, every line character-identical except `:6`, whose old
  text is the exact prefix of the new one. The Ruecklauf-1 entry was appended to, not replaced.
- No line was added or removed: `erzwungen_von:` still stands at `:10`, inside the frontmatter.
- Every line-numbered citation into the body still lands: `:167` (USA `letztes_jahr` **2020**, **24**
  Stützstellen), `:174` (`DEU.DISR_RT_PT_A_PT.A` (leer)) — the two `quellenbefund-leitzinspfad.md`
  cites — and the whole `0262` passage at its post-edit numbers: lead-in `:283`–`:284`, values
  `:289`–`:290`, „sieben" at `:296` and `:300`, `:302`–`:303`, retirement `:304`, re-read
  `:305`–`:308`, „Startjahr und Wertezahl" `:312`–`:313`.
- All nine values digit-identical with the list recorded in `pruefung-0262…:18`–`:20` and `:57`:
  132,55 · 125,05 · 81,03 · 68,04 · 70,13 · 96,01 · 88,93 · −13,18 · −14,13, plus −13,176825 /
  −14,126658 at `:308`. No value moved.
- `lizenzbefund-reihen.md` is untouched: 504 non-empty lines here and 504 in the `messung-0069`
  copy, frontmatter head identical.
- `ueberarbeitet` occurs once in the file, and `Grep -n '^ueberarbeitet:'` over `daten/` still
  returns exactly two files. No third file gained the field.

## What I could not check, and where I found nothing

The appended condition also asks for the method and its per-file result **in the run summary**.
Run summaries are not repo artifacts — `ops/dashboard.html` logs the run, not its text — so that
half is invisible at review; I rederived the set myself instead. Flagged for the project manager.

`0234` cites the deckungsbefund but is `abgelehnt` and claims `quellenbefund-leitzinspfad.md`;
`0241`, `0253`, `0263` claim that file too. None belongs in either field.
