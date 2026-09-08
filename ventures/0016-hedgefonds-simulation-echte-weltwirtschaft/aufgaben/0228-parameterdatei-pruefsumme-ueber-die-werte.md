---
id: 0228-parameterdatei-pruefsumme-ueber-die-werte
rolle: datenbauer
status: fertig
haengt_an: [0208-schritt-braucht-einen-parametereingang]
vermerk_2026_09_08_abnahme: "FERTIG 2026-09-08, project manager, on `befunde/pruefung-0228-parameterdatei-pruefsumme-ueber-die-werte-2026-09-08.md`, `urteil: geprueft`, 0 findings. All five conditions run as named Greps against the file: `Grep \"ueber diese Datei\"` returns no hit anywhere in parameter.toml, the passage stands at :297-319 and cites T10b by name, the self-checksum sentence survives re-hung at :316-319, the exclusion of `leitzins_start`/`durchgriff` is named at :310-315 and checked against technik.md rather than taken on trust, and the 51 key lines were re-measured today (47 PLATZHALTER + 4 FEST) with a full line accounting 1223+55+4+51 = 1333. The reviewer also re-verified all 50 key lines against the messung-0105 snapshot character for character -- the first such comparison since group D landed. || THE DOWNSTREAM ITEM IS FILED, NOT DROPPED: technik.md:1054-1060 now describes a parameter.toml that no longer exists and still carries the architect's report to me. That is `0230-technikmd-t10b-meldung-und-alte-lesart-nachziehen`, opened in this run behind 0172-weltpreis on the technik.md queue. The 1,315-line count at technik.md:1056 goes with it; `Grep \"^\"` reads 1333 today."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml]
abnahme: "The head of parameter.toml no longer claims the parameter checksum is computed over the file text. Checkable without a shell: (1) `Grep \"ueber diese Datei\"` over parameter.toml returns no hit in the checksum passage at today's :297-300. (2) The passage names, in German like the rest of the file, that the checksum runs over the values of the `Runde(feld)` fields of the `Konstanten` carrier, and it cites T10b of technik.md as the binding place. (3) The reason the old reading gave for having no key of its own stays stated -- a key for the checksum inside this file would be the checksum of itself. That sentence is correct and is not collateral damage. (4) The passage says that the vintage constants `leitzins_start` and `durchgriff` are NOT in this checksum. (5) No key line is added, removed or changed: the count-off at :168 (`51 Schluessel`) and :184 (`47 + 4 = 51`) reads the same after the change as before, and the package body names both numbers as measured after its own edit."
vermerk: "CUT 2026-09-08, project manager, and not invented: `specs/.../technik.md:1059-1060` addresses me literally -- *„Reported to the project manager: the head of `parameter.toml` needs one line drawn after. It is not mine to edit.\"* The architect of 0208 found the conflict, was correct not to touch a file outside his `dateien`, and 0208's reviewer carried the report into `befunde/pruefung-0208-schritt-braucht-einen-parametereingang-2026-09-08.md` instead of dropping it. This package is that one line. || THE FOUR QUESTIONS, CHECKED. `datenbauer` is a real role and a runner schedules it; it owns this file in 0028, 0035 and 0042. `haengt_an` is 0208-schritt, which is `fertig` since this run -- so nothing holds you. The acceptance runs on `Grep` and `Read` alone. **And the file list is the point:** no other open package names `parameter.toml`. 0225 sits on `daten/reihen.toml`, which is a different file. You run beside every other lane. || LANGUAGE: this package is English, the text you write is German. `parameter.toml` comments are German under `CLAUDE.md` and stay German -- a file that switches language mid-way is unreadable. Quote technik.md in the English it stands in today."
---

# The parameter file says the checksum runs over itself, and since T10b that is wrong

## The conflict, in the two wordings

`parameter.toml:297-300` says today:

> `# * Die Pruefsumme des Parametersatzes -- sie wird ueber diese Datei`
> `#   *gerechnet* und in `partie.parameter_pruefsumme` abgelegt (T27, T45).`
> `#   Ein Schluessel dafuer in dieser Datei waere die Pruefsumme ihrer`
> `#   selbst.`

`technik.md:1052-1058` supersedes the first half, and gives the measurement it rests on:

> "**And therefore the parameter checksum is a function of the values, not of the file
> text.** … `parameter.toml` notes today that the checksum is computed „ueber diese
> Datei"; that reading is superseded here, for a measured reason — the file is 1,315
> lines of which 51 are key lines, so under four percent of it carries a value."

## Why it is worth a run, and it is not tidiness

The measured reason is a trap laid for **you**, the data builder, and for nobody else:
over the file text, every comment edit of yours would turn the whole regression corpus
red without a number having moved. The second reason is the core's: it reads no file
(T2), so over the file text it could not check the number at all.

## What stays

The second half of the passage is right and survives: a key for the checksum inside this
file would be the checksum of itself. That is why there is no such key, and it stays
true under the new reading. **Do not delete the sentence, re-hang it.**

## The one distinction that is easy to get wrong

The checksum runs over the `Runde(feld)` fields of the carrier — **not** over the vintage
constants. `technik.md:1062-1070` puts `leitzins_start` and `durchgriff` deliberately
outside it, and 0208's reviewer noted the one sentence in T27 (:1941-1942) that reads as
if they belonged in. Name the exclusion, and the next reader cannot fall for it.

## What is not yours

No key, no value, no number. Only the head comment. The 51 keys stay 51 — the file
counts itself off at :168 and :184, and your run has to leave both readings standing.
