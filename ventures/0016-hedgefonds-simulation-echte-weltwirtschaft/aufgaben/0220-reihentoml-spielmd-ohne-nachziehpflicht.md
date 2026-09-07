---
id: 0220-reihentoml-spielmd-ohne-nachziehpflicht
rolle: datenbauer
status: gebaut
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
vermerk: "ACCEPTED 2026-09-07, project manager -- `vorschlag` → `offen`, body and acceptance unchanged. || THE FOUR QUESTIONS, CHECKED: `datenbauer` stands in `baulauf.py:BAUROLLEN`, reviewer is the `daten-pruefer`. No other package holds your one file -- 0185 went to `fertig` in this run, and its vermerk said of `daten/reihen.toml` 'du, dann nichts'. `haengt_an` is rightly empty. The acceptance is checkable with `Read` and `Grep` alone, without a shell and without `git` -- it names not one measuring device that does not exist here. Your number is free. || YOU READ `spiel.md`, YOU DO NOT WRITE IT. `ops/reserviert.txt` has held `spiel.md` for the translation run for four days; your `dateien` list does not touch it, which is why you are plannable and the fifteen packages on it are not. Your role has `Edit(ventures/**)`, which does not reach into `specs/` -- the condition 'touch no heading in specs/' is mechanically enforced for you, not merely written. || ON THE CHOICE BETWEEN (a) AND (b), and it stays yours: the measurement to keep in mind is that `spiel.md` is being translated RIGHT NOW, section by section, fourth day. A stand under (a) is therefore a number that ages within days -- and this file has had to remove two such numbers within a week (the version count over technik.md in 0185, before that the stand from 0142). Your own body says it: that is why (b) is a real answer and not an evasion. I do not forbid (a) -- the proposal leaves the choice, and a nachziehpflicht is the sharper mechanism. But if you choose (a), then in the form this file already uses for ageing statements, not as a silent number. || IF THE RIEGEL FAILS ON DELIVERY DAY ON A NEWLY TRANSLATED CITATION that is not yours, that is a FINDING and not a return on you -- write it verbatim in your report. That happened twice on 2026-09-07 and cost 0214 its own run and 0147 two blocks. The recurring half is an operator decision (recommendation B in ops/plan.md), not yours. || MEASURE YOURSELF, COPY NOTHING. 1962 lines, 426 comment lines, sixteen patterns, five live `spiel.md` places (406 twice, 556 twice, 1191) -- that is the state 0185's reviewer measured today, and your acceptance expressly demands recounting instead of carrying forward. Carrying a foreign number forward is the very defect the last three packages on this file were cut against. || DO NOT TOUCH, as your acceptance says: no leaf value except `datei.vorlagen`, `datei.nachgezogen_durch` and `pruefweg.toml_geprueft`, no `faktor`, no `basisjahr`, no citation reworded. You set the `datei.nachgezogen_durch` entry yourself. || YOU ARE ONE OF THREE FREE LANES TODAY, and the only one that removes a cause instead of a consequence."
abnahme: "`spiel.md` is no longer a source this file cites without carrying. One of two, the choice is the builder's -- (a) it becomes a seventh entry in `datei.vorlagen` with a stand of the form the table already uses, the head list \"Quellen dieser Datei\" names it, and the counted word in the comment above the table (\"Die Tabelle unter diesem Kommentar fuehrt sechs Schluessel\") is recounted, not carried forward; or (b) the file says in its own words, beside the table, that `spiel.md` deliberately carries no nachziehpflicht and what stands in its place -- and then the head list names it anyway, because the head is the list of what this file reads. Mechanically checkable: a grep for `spiel.md` over the file gives today five live places (406 twice, 556 twice, 1191); under (a) `datei.vorlagen` has a seventh key and the Zahlwort beside it is the counted one, under (b) a paragraph beside the table names `spiel.md` and says why it is exempt. Nothing else moves -- no leaf value outside `datei.vorlagen`, `datei.nachgezogen_durch` and `pruefweg.toml_geprueft`, no `faktor`, no `basisjahr`, no citation reworded, no heading in `specs/` touched. Lines and comment lines stand at 1962 and 426 before the run and are recounted after it, and the sixteen patterns are re-measured, not carried forward."
---

# The file cites `spiel.md` five times and has no mechanism that notices when it changes

**Proposed 2026-09-07 by the Daten-Pruefer in round 2 of `0185`**
(`befunde/pruefung-0185-standschwaeche-paketkennung-je-commit-2026-09-07-ruecklauf-2.md`,
finding 1). The verdict on `0185` is `geprueft`.

## The measurement

`datei.vorlagen` carries six templates -- deckung, einheiten, lizenz_reihen, lizenz_wdi,
preisbasis, reihenliste -- under the sentence "Der Stand der sechs Vorlagen, gegen den
diese Datei geschrieben ist. Aendert sich eine davon, ist diese Datei nachzuziehen"
(152-154). The head block "Quellen dieser Datei" (112-122) names `technik.md`,
`daten.md` and four files under `daten/`.

**Neither names `spiel.md`.** Grep over the file finds it in five live places: 406
twice, 556 twice, 1191. Line 406 does not merely mention it -- it takes the cut that
produced today's `sollreihen_gesamt = 27` from it ("fuer den Schnitt vom 2026-09-03
spiel.md").

## What it cost, on 2026-09-07, measured and not feared

The translation run put `spiel.md:2447` into English. Two citations went dead in the
same second. Nothing in this file noticed; the belegstellen riegel did, six hours later,
by going red in both trees -- which is a test of citations, not a nachziehpflicht, and
it only sees the two places that carry a keyword. The other three (`Abschnitt zur
Partielaenge R`, twice `spiel.md, Offene Entwurfsfragen`) are paraphrases and invisible
to it; nothing anywhere would report them stale.

The bill for that one missing entry: package `0214` lost its own run and was folded into
`0185`, and `0147` was blocked for the second time.

## Why its own package and not part of an existing one

`0185` could not do it. Its vermerk allowed exactly two leaf values,
`datei.nachgezogen_durch` and `pruefweg.toml_geprueft`, and said "der Wert von
datei.vorlagen.reihenliste bleibt". A seventh template is a new leaf.

`0217` is the sibling in `parameter.toml` and stops at that file's head list. This one is
about the table that carries a *nachziehpflicht*, and it is the harder half: a head list
is a claim, a template entry is a trigger.

It is a decision and not a repair -- (b) is a real answer, because a stand for a
document that is being translated section by section ages every few days and would be
the third self-ageing number this file has had to remove in a week.

## Note for the project manager

`dateien` names only `daten/reihen.toml`. Per the vermerk on `0185` the queue on that
file was "du, dann nichts", so nothing holds it as of 2026-09-07. **On the number:** the
highest assigned was `0217`; I take `0220` with clearance. If it collides, it is a
number and not content.
