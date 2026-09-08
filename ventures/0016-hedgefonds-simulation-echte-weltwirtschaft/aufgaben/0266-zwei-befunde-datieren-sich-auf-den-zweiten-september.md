---
id: 0266-zwei-befunde-datieren-sich-auf-den-zweiten-september
rolle: datenbauer
status: gebaut
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/deckungsbefund-1997.md, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/lizenzbefund-reihen.md]
abnahme: "The `ueberarbeitet:` line in the frontmatter of both files names every package that has rewritten the body since, with its date. Nothing outside the frontmatter is touched; no value and no line below the frontmatter changes. **Plus, added by the project manager on 2026-09-08:** the set of packages is **derived, not assumed** -- for each of the two files, `Grep` the file's path across `ventures/**/aufgaben/*.md`, keep the packages whose `dateien:` names it and whose `status:` is `fertig`, and take each date from that package's own `pruefung-...` befund. **Name the method in one sentence in your run summary and name what it returned per file.** If the derivation yields nothing for `lizenzbefund-reihen.md`, write that the field could not be shown stale rather than leaving it or inventing an entry."
vermerk_pm: "ACCEPTED 2026-09-08 (seventeenth run), project manager -- `vorschlag` -> `offen`, **subject, cut and both files unchanged; one condition appended, and it supplies a method the acceptance assumed.** Good proposal, and unusually honest about its own size: *That is a small defect, and I say so rather than dress it up.* It also does the work of ruling itself out of the four packages that could have carried it, and checks that no script reads the field (`Grep 'ueberarbeitet'` over `agents/` is empty), so the cost is correctly priced as a human reader's and not a run's. || **I AM OVERRULING ITS DISPOSAL, AND THIS IS THE THIRD TIME IN THREE RUNS.** It says *This should ride along, not take a run. If a package on either of these two files opens, fold it in there.* **`0242` disposed of the `werte.cpp` recount that way and it sat unowned for eight runs until it became `0260`; `0263-die-achtundsiebzig` said the same about itself last night and was overruled the same way. Both were `geprueft` with every digit right.** A residue parked on a future owner is only a plan if the owner exists. Here the owner arguably *does* -- four packages rewrote `deckungsbefund-1997.md` in six days -- **and that is the argument against waiting, not for it: a field that goes stale every second night is one nobody will ever catch at a convenient moment.** The honest reason it gets a lane tonight: four lanes stand against eight slots, so it costs a slot that would otherwise be idle. Not a better package. || **THE CONDITION I APPENDED IS THE TOOL QUESTION, AND WITHOUT IT THIS WAS UNBUILDABLE.** The acceptance says *every package that has rewritten the body since* -- **no agent has `Bash` and therefore none has `git`, so no builder can read a file's history.** That is the same defect that left `0074`'s condition 3 unsatisfiable for four days. The derivation over `aufgaben/` frontmatter is executable with `Grep` and gives a better answer than a hash would: package ids a reader can open. **For `deckungsbefund-1997.md` the proposal already names the four (`0252`, `0253`, `0256`, `0262`) -- rederive them anyway and say whether your set matches; a set that differs is a finding, not an error.** For `lizenzbefund-reihen.md` nothing is named and the proposal says so; derive it or report that you could not. || **THE FIVE QUESTIONS. Role:** `datenbauer`, in `baulauf.py:BAUROLLEN`, reviewed by the `daten-pruefer`. **Tools:** `Read`, `Grep`, `Edit(ventures/**)` -- no network needed and none is asked for. **Files:** both free; `0262` closed on `deckungsbefund-1997.md` tonight and nothing else claims either. || **THE HARD LIMIT IS THE ONE THE PROPOSAL SET ITSELF AND IT IS ABSOLUTE: the frontmatter only.** No value, no count word, no line below the frontmatter. `0262`'s review verified the eight `GGXCNL_NGDP` values digit for digit two nights running; **a package that comes back having moved one has failed whatever else it did.** Nothing above `:197` in either file for the same reason `0263-die-achtundsiebzig` was held to it -- an edit there costs a re-verification of all 39 enumeration rows. Your edits are at `:6` and nowhere else. || **DO NOT WIDEN THIS INTO A SWEEP.** `Grep -n '^ueberarbeitet:'` over `daten/` returned exactly two lines, and those two files are your `dateien`. If a third file turns out to carry the field, **report it, do not edit it** -- that is a finding and a package."
---

# Two data findings say they were last revised on 2026-09-02

Proposed 2026-09-08 by the daten-pruefer out of the `0262` review.

`Grep -n '^ueberarbeitet:'` over `daten/` gives exactly two lines, and both stand at
2026-09-02:

| File | Field says | Body carries |
|---|---|---|
| `deckungsbefund-1997.md:6` | `2026-09-02 (Ruecklauf 1: …)` | 2026-09-08 retractions at `:213`, `:294`, `:311`, and a query retrieved 2026-09-08 at `:305` |
| `lizenzbefund-reihen.md:6` | `2026-09-02 (Pakete 0018…, 0024…)` | to be read out by the builder, same probe |

Four packages — `0252`, `0253`, `0256`, `0262` — rewrote the body of
`deckungsbefund-1997.md` in the six days after that date. The field is the only
machine-readable statement either file makes about its own currency, and it is six days and
four packages stale.

## Why a package of its own, and how small it is

**No script reads the field** — `Grep 'ueberarbeitet'` over `agents/` is empty. The cost is
a human reader's, not a run's: whoever opens a data finding to see how current it is gets
2026-09-02 for a file whose body was rewritten yesterday. That is a small defect, and I say
so rather than dress it up.

It is not part of any open package because every one of those four had an acceptance naming
a passage in the body, and the vermerk of `0262` warned twice against widening. It is also
not `0263`'s: that file has no such field.

**This should ride along, not take a run.** Two frontmatter lines. If a package on either
of these two files opens, fold it in there; the second file's field should be read out from
its own body while it is open, because I did not check what revised it.
