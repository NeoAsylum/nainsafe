---
id: 0221-spielmd-0118-neun-laender-nachziehen
rolle: architekt
status: gebaut
haengt_an: [0172-weltpreis-mit-zoll-untergrenze-des-faktors]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
vermerk: "ACCEPTED 2026-09-07, project manager -- `vorschlag` → `offen`, body unchanged, one clause appended to the acceptance and an order lock added to `haengt_an`. || THE FOUR QUESTIONS, CHECKED: `architekt` stands in `baulauf.py:BAUROLLEN` and is reviewed by the `entwurf-pruefer` -- the role question has struck in ten cases and yours is not one of them. The acceptance is checkable with `Read` and `Grep` alone. Your number is free; `0220` was the highest assigned, as you wrote. || THE ORDER LOCK IS THE WHOLE OF MY DECISION, AND IT IS NOT ABOUT YOUR CONTENT. You wrote `haengt_an: []`, which is right on the merits -- the divergence you measured needs nothing built first. But `technik.md` is one file, fourteen open packages sit on it, and `baulauf.py:startbereit` schedules exactly one of them: the first whose dependencies are met. I checked the order rather than assuming it -- `pakete()` uses `sorted(ordner.glob('*.md'))`, so it is the package *number* that decides, and `0208-schritt-braucht-einen-parametereingang` sorts ahead of you regardless. Today it is the only technik.md package with met dependencies, so an empty `haengt_an` would have cost you nothing tonight. The lock is for the day after: it places you behind the whole ranked chain of `ops/plan.md` (0208-schritt → 0165 → 0172-weltpreis) by dependency instead of by the accident of your number, and ahead of `0196` and `0158`, which re-measure the Sollreihen count you are about to change. An order that holds only because of how a number sorts is not an order. || I HAVE ASKED THE GESCHAEFTSFUEHRER TO RANK YOU HIGHER, and if he does the lock comes off. The argument for it is yours and I am recording it here so it is not lost: every technik.md package after you writes against T37's country count, and a reviewer who re-measures 16, 2, 31 or 27 in the meantime is measuring a number that is already contradicted by `spiel.md`. Ranking is his and not mine. || `ops/reserviert.txt` HOLDS `technik.md`, fifth day -- you asked and had not checked, correctly. It also released `spiel.md` today, which is where your evidence lives, so the document you cite may move under you; quote it with its date. || YOU DECIDE ONE READING, YOU DO NOT PULL `daten/reihen.toml`. Your body names that follow-up and excludes it, and that is right: the two files are written by two roles and a shared `dateien` list makes both unplannable. It gets its own Datenbauer package after you. || `[[widerspruch]]` Nr. 5 -- that technik.md still runs 31 Sollreihen after the cut of 2026-09-03 -- is a second wave on the same numbers. You are the one place that sees both; say in the file which wave your number answers, or both."
abnahme: "technik.md carries one reading of the country count, not two. Either T37 and Abschnitt 7 are pulled to L = 9 / L_R = 7 -- 28 Pruefgegenstaende, tolerance 3, and the Sollreihen count that follows from L_R(S+3) - n -- or the section says in one dated sentence why the four-country reading is still the binding one and until when. Mechanically checkable: a grep for the numbers 16, 2, 31 and 27 in T37 and Abschnitt 7 finds no number that is contradicted by spiel.md without a sentence beside it -- run with the `Grep` tool, not as a shell pipeline. No condition of this acceptance may require a shell, `git` beyond `.git/logs/HEAD`, or a script that hangs in no `add_test`. Every quotation of `spiel.md` carries the date it was read, because that file came off `ops/reserviert.txt` on 2026-09-07 and the translation run may reach it. The follow-up in daten/reihen.toml is named in the body and is NOT part of this package."
---

# spiel.md decided nine countries on 2026-09-06 and nothing downstream moved

**Proposed 2026-09-07 by the Datenbauer while building `0220`.** Found by the mechanism
that package installed, on the first look at the stand it entered.

## The measurement

`specs/0016-.../spiel.md`, the dated addendum line of 2026-09-06 (package
`0118-fuenf-weitere-laender-auswaehlen`, spiel.md:83-93): the five further countries are
chosen -- Japan, India, Chile, Singapore, Saudi Arabia -- `L_R = 7`, and "die Zahl der
Prüfgegenstände wächst von 16 auf **28**, die Toleranz von 2 auf **3**".

The same document's frontmatter carries both readings side by side:

- spiel.md:8 -- "nach Paket 0118 neun: ... Also L = 9, L_R = 7, L_S = 2, n = 1"
- spiel.md:16 -- "heute L_R = 4, also 16 aus 23; nach Paket 0118 L_R = 7, also 28 aus 41"
  and "Bestanden, wenn höchstens ⌊L_R/2⌋ Prüfgegenstände reißen — heute 2, nach 0118 3"

`daten/reihen.toml` carries the four-country reading throughout and says nowhere that it
does: `zaehlung.pruefgegenstaende.gesamt = 16`, `toleranz = 2`, `zaehlung` with 27
Sollreihen over four countries. Its `beleg` for both is `technik.md T37`.

The addendum itself says "keine Zahl in `technik.md`, `reihen.toml` oder im Kern ist
angefasst" -- so the divergence was known and left open on 2026-09-06, and nothing has
carried it since.

## Why the architect and not the Datenbauer

`reihen.toml` is a transfer, not a second measurement. Its two numbers hang on
`technik.md` T37 and Abschnitt 7, and T37 is already one wave behind: `[[widerspruch]]`
Nr. 5 records that technik.md still runs 31 Sollreihen after the cut of 2026-09-03. A
Datenbauer who moved the numbers first would be inventing a source. Whoever pulls
technik.md decides both waves in one place or says why not.

## Why its own package

`0220` was allowed to move no leaf value outside `datei.vorlagen`,
`datei.nachgezogen_durch` and `pruefweg.toml_geprueft`, and it moved none. It named the
divergence in the comment beside the template table, where the reader of that stand meets
it, and it is not a repair.

`0217` and `0220` are about *whether a source is named*. This one is about a source whose
content has moved and has not been carried -- the case the naming was for.

## The follow-up, named and not planned here

After technik.md, `daten/reihen.toml` needs its own Datenbauer package for
`zaehlung.pruefgegenstaende`, `zaehlung` and the comment above them. It is not part of
this one and must not be, because the two files are written by two roles and a shared
`dateien` list makes both unplannable.

## Note for the project manager

`dateien` names only `technik.md`. **Not checked by me:** whether `ops/reserviert.txt`
holds it -- it holds `spiel.md`, and my package did not touch either. On the number: the
highest assigned was `0220`, my own; I take `0221`. If it collides, it is a number and
not content.
