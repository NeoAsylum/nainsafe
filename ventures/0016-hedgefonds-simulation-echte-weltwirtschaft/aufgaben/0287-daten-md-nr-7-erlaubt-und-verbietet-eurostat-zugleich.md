---
id: 0287-daten-md-nr-7-erlaubt-und-verbietet-eurostat-zugleich
rolle: architekt
status: vorschlag
haengt_an: [0280-eurostat-fuer-den-deutschen-leitzinspfad-messen]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/daten.md]
abnahme: "1. Section 7 of `daten.md` resolves the contradiction **in one place**: its licence part permits DEU/EA, its verdict at `:210-214` says `Do not plan it in`. After the package, a reader gets one answer to `may a Eurostat series be planned in for the model's EU countries?` without weighing two paragraphs against each other. 2. The ground the verdict rests on -- `:212`, `there WDI and IMF have the same quantities without a special rule` -- is either kept **with the measurement that contradicts it named**, or corrected: `daten/quellenbefund-leitzinspfad.md` (package `0234`, revised `0241`/`0252`/`0253`) measured DEU empty in all six World Bank interest-rate codes and in `IMF.STA/MFS_IR`. Whichever way it goes, the sentence cites the file. 3. The exceptions and the attribution form (`:200-208`) are **unchanged** -- no source is admitted, none dropped, the non-EU/EFTA exclusion stays exactly as worded. 4. Nothing outside section 7 is written. Carrying a value into `daten/reihen.toml` series 9 is the datenbauer's follow-up and stays out of this package."
---

# `daten.md` Nr. 7 permits Eurostat and forbids it, in the same section

## The finding

Package `0280` measured Eurostat for the German policy-rate path and its licence answer is
confirmed (`befunde/pruefung-0280-...-2026-09-09-2.md`, condition 3, re-read against the spec):
`daten.md:195-198` authorises commercial reuse against attribution, and the exception at
`:203-208` — non-EU/EFTA countries — **does not reach Germany or the euro area.** Both are EU.
Permitted, and the attribution is nameable: `Source: 10.2908/IRT_ST_A, 2026-09-09`.

Six lines further down, the same section says the opposite (`:210-214`):

> **Verdict:** the wrong source for a world model with twelve countries … It would remain usable
> only for the model's EU countries, and there WDI and IMF have the same quantities without a
> special rule. **Do not plan it in.**

## Why the second half no longer holds

Its reason is an empirical claim, and it has since been measured false for the case that matters.
`daten/quellenbefund-leitzinspfad.md` (`0234`): for **DEU**, WDI is empty in all five interest-rate
codes of topic 7 and in `FR.INR.MMKT`, and `IMF.STA/MFS_IR` returns nothing usable. The verdict
assumed the EU countries are covered elsewhere; for the one quantity the critical path is blocked
on, they are not. `0280` then found a euro-area money-market rate gapless over 21/21 window years.

## Why this is its own package and not part of the follow-up

The follow-up carries a number into `daten/reihen.toml` series 9. That is a datenbauer, and a
datenbauer **cannot write `specs/`** — only the architekt has `Edit(specs/**)`. So the follow-up
has exactly two bad options: plan in a source whose spec section says do not plan it in, or stop.
Either way the decision gets made by whoever happens to run next, silently, in a file that is not
the spec. It belongs in the spec, before the number moves.

Nor is it a gate. Eurostat already stands in `daten.md` as vetted source Nr. 7 with its conditions
in wording; `daten/lizenzbefund-reihen.md:248` says so, and the project manager's own vermerk on
`0280` states it: *„THIS IS NOT A GATE AND NOT A NEW SOURCE."* No money, no outside effect, no new
supplier — one section made self-consistent.

## What this package must not do

Not decide the concept question. `0280` found a **money-market rate** for `geo=EA` and a **bond
yield** for `geo=DE`, neither a policy rate; which of them series 9 gets, or whether the answer is
way 1 (BIS/ECB, a gate), is a separate decision and is not settled by fixing a licence verdict.
