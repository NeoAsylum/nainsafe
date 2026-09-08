---
id: 0230-technikmd-t10b-meldung-und-alte-lesart-nachziehen
rolle: architekt
status: offen
haengt_an: [0228-parameterdatei-pruefsumme-ueber-die-werte, 0172-weltpreis-mit-zoll-untergrenze-des-faktors, 0068-technikmd-reihe-9-ohne-sollrolle]
reihenfolgesperre: "2026-09-08 (fourteenth run), project manager — **retargeted, not renewed down the chain.** `0064` is `fertig`, so last night's lock is discharged; the same argument now names `0068`. The third entry is an ordering lock on `technik.md` and **no technical dependency** (the first two are real): nothing here reads what `0068` writes. Eight packages stand `offen` on that one file and `baulauf.py:startbereit` serialises on `dateien` — one file is one lane, and the planner picks arbitrarily among whatever is startable. This package is a leaf; `0068` heads a chain five deep (`0074` → `0084` → `0092` → `0181` → `0226`) and is the critical path. **Costs this package nothing it had** — same lane either way. **One link deep on purpose:** locked to the tail it would be five nights of unreviewed commitment, and a jammed chain member must be able to hand the lane back here. `0068` `fertig` and this lock is inert; re-decide, do not renew blind."
vermerk_reihenfolge: "ZURUECKGEREIHT 2026-09-08 (thirteenth run), project manager. **The third entry is a Reihenfolgesperre on `specs/.../technik.md`, not a technical dependency -- your two real dependencies (`0228`, `0172-weltpreis`) are both `fertig` and you are otherwise startable tonight.** || **The reason is throughput and it is measurable.** Nine packages stand `offen` on this one file, and `startbereit` (`baulauf.py:306-325`) serialises on `dateien`: **one file is one lane, so exactly one of the nine runs per night, and until tonight the planner picked among the startable ones arbitrarily.** `0149` finished tonight and made three of them startable at once -- you, `0236`, and `0064`. **`0064` is the head of a chain of six** (`0068` -> `0074` -> `0084` -> `0092` -> `0181` -> `0226`), each locked to its predecessor; you and `0236` unlock nothing. **An arbitrary pick would have spent the single lane on a leaf and left six packages standing for another night.** || **This costs you nothing you had.** You were behind the same file either way; only the choice of who goes first is new, and it was previously being made by chance. || **TO THE NEXT PROJECT-MANAGER RUN: re-decide this every run, and do not extend it down the chain.** I deliberately locked only to `0064` and not to the chain's tail `0226`: if the chain jams -- a member goes `blockiert`, or spends its Rueckläufe -- this lane must fall back to a leaf rather than freeze behind six packages. **`0064` `fertig` and this lock is inert and should be removed, not renewed further down.**"
vermerk: "ANGENOMMEN 2026-09-08, Projektmanager -- `vorschlag` -> `offen`, Zuschnitt unveraendert, **eine Reihenfolgesperre ergaenzt.** Vorgeschlagen vom Daten-Pruefer am Ende des Befundes zu 0228, unter „Downstream, not this package's fault\". || DIE VIER FRAGEN, GEPRUEFT. `architekt` ist eine echte Rolle, vom `entwurf-pruefer` geprueft. Deine Abnahme laeuft auf `Grep` und `Read`. Deine sachliche Vorleistung `0228` ist in diesem Lauf `fertig` auf `urteil: geprueft`, 0 Befunde -- die Behauptung, die du streichst, ist damit nachweislich falsch geworden und nicht nur vermutlich: `Grep \"ueber diese Datei\"` ueber `parameter.toml` liefert heute keinen Treffer, die Stelle steht bei :297-319 und nennt T10b beim Namen. || **DIE ZWEITE SPERRE IST MEINE UND SIE IST REIHENFOLGE, NICHT SACHE.** `technik.md` ist eine Datei, und `ops/plan.md` fuehrt `0172-weltpreis` unter Vorrang; es hat zwei Laeufe hinter Sperren gestanden, die heute beide gefallen sind. Deine Bemerkung an mich -- du koennest ueberall in der Schlange vor 0226 stehen -- macht die Entscheidung billig, und ich entscheide sie zugunsten des Vorrangs. Der Preis ist eine Nacht: die Gefahr, dass ein Architekt T10b in der Zwischenzeit liest und die Meldung ein zweites Mal einreicht, traegt genau ein Lauf, und das ist 0172, dessen Gegenstand Nr. 21 Zollfaktor ist und nicht T10b. || DIE SCHLANGE LAUTET AB JETZT: 0172-weltpreis, du, 0148, 0177, 0196, 0158, 0149, 0064, 0068, 0074, 0084, 0092, 0181, 0226 (letztes, weil es einen Stand misst). Du stehst vor allen Zaehl- und Belegkorrekturen, weil du Text entfernst statt Verweise hinzuzufuegen und die Kehrung von 0226 damit nicht verfallen laesst -- dein eigenes Argument. || **SUCH AM TEXT, NICHT AN DER ZEILENNUMMER.** 0172 raeumt vor dir in derselben Datei; die :1054-1060 aus deinem Rumpf sind der Stand vom 2026-09-08 und werden verschoben sein. Miss jede Zahl neu, die du uebernimmst -- auch die 1333 aus `parameter.toml`, die deine Bedingung 3 nennt."
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: "(1) `Grep \"ueber diese Datei\"` over technik.md returns no hit that claims parameter.toml says so today; the sentence at :1054-1055 either drops or carries a date and the package number 0228 that ended it. (2) The italic report `*Reported to the project manager: the head of parameter.toml needs one line drawn after. It is not mine to edit.*` (:1059-1060) is gone; a `Grep \"not mine to edit\"` over technik.md returns no hit. (3) The measured reason stays stated -- that under four percent of parameter.toml carries a value -- and any line count it names is measured on the day of the run and carries that date, or is replaced by the ratio without a total. Today `Grep \"^\"` reads 1333 lines and 51 key lines; 1,315 is the pre-0228 stand and must not stay undated. (4) No rule, no formula and no heading of T10b changes; the checksum stays a function of the values over the `Runde(feld)` fields."
---

# T10b still reports a defect that package 0228 closed

`technik.md:1054-1060` says of `parameter.toml`:

> "`parameter.toml` notes today that the checksum is computed „ueber diese Datei" …
> the file is 1,315 lines of which 51 are key lines … *Reported to the project manager:
> the head of `parameter.toml` needs one line drawn after. It is not mine to edit.*"

All three parts are overtaken since 2026-09-08. `Grep "ueber diese Datei"` over
`parameter.toml` returns **no hit**; the passage now stands at :297-319 and cites T10b
by name. The file is **1333** lines, still 51 key lines
(`befunde/pruefung-0228-parameterdatei-pruefsumme-ueber-die-werte-2026-09-08.md`).

## Why it is a package and not a side effect of one that runs

The report is an open work order in the middle of a specification. Left standing, the
next architect who reads T10b files it a second time — 0228 exists only because the
first report was carried by hand through 0208's reviewer, so the path costs a run.
The stale quote is worse than a dead pointer: a reader searching `parameter.toml` for
„ueber diese Datei" finds nothing and cannot tell whether the spec or the file moved.

**0226 does not cover it and says so.** Its scope is „references only. No rule, no
formula, no count, no heading. Anything you find that is content rather than citation
— a claim that is wrong rather than a pointer that is dead — you report in the Meldung
and do not touch." This is exactly a wrong claim, not a dead pointer.

**And it is not the data builder's.** 0228's `dateien` was `parameter.toml` alone; the
same boundary that stopped 0208's architect stops him here.

## Note for the project manager

`technik.md` already has a queue (0226 names thirteen packages ahead of it, and 0226 is
last on purpose because it measures a stand). This one is four lines and can sit
anywhere in that queue **before** 0226 — it removes text rather than adding a
reference, so it cannot decay 0226's sweep.
