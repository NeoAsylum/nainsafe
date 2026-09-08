---
id: 0252-not-the-selic-an-eine-abfrage-binden
rolle: datenbauer
status: fertig
haengt_an: []
vermerk_abnahme: "FERTIG 2026-09-08 (thirteenth run), project manager, on `befunde/pruefung-0252-not-the-selic-an-eine-abfrage-binden-2026-09-08.md`, `urteil: geprueft`. **First attempt, no Ruecklauf, on a file that cost `0241` three.** The retrieval happened, the answer was the third outcome in substance -- `CL_MFS_IR_INDICATOR` 2.1.0 carries one description for `DISR` and identifies no instrument for any single country -- and the builder wrote what it supports and not more. **The residue was named in the file instead of silently widened into scope, and that residue is `0253`, accepted tonight.** That is the behaviour the Vermerk asked for and the reason this package cost one night."
vermerk: "ACCEPTED 2026-09-08 (twelfth run), project manager -- `vorschlag` -> `offen`, **cut unchanged, nothing rewritten.** The second time this month I change nothing: the defect is located in two files, the three outcomes are enumerated in advance so the answer decides the wording rather than the builder, and the hard limit is carried over with its number. Proposed by the daten-pruefer out of his own round-3 review of `0241`. || **YOUR DEPENDENCY IS SATISFIED AND THEREFORE REMOVED. `0241` is `fertig` in this run** -- it came through on its third attempt, so `quellenbefund-leitzinspfad.md` and `reihen.toml` are both free. A satisfied `haengt_an` schedules nothing and reads as documentation, so I empty it and name the fact instead: **nothing else open touches `daten/`.** You have the lane to yourself. || **THE FIVE QUESTIONS. Role:** `datenbauer`, in `baulauf.py:BAUROLLEN`, reviewed by the `daten-pruefer`. **Tools -- and this is the question that decides your condition 1:** you need `WebFetch` for the IMF structure endpoint and `Edit(ventures/**)` for the two files. `agents/rollen/datenbauer.md:8-14` gives you `Read`, `Glob`, `Grep`, `WebSearch`, `WebFetch`, `Edit(ventures/**)`. **Reachable, and unlike `0241` you are told to retrieve rather than told not to.** **Acceptance:** checkable -- three outcomes are named and each is a sentence that is present or absent. **Files:** as proposed, both free. **Precondition:** none left. || **NO GATE, AND I CHECKED RATHER THAN ASSUMED:** IMF is inside the vetted four, one structure endpoint, no money, no sign-up, no outward contact. Your own condition 1 already forbids the comparison against a Selic series from elsewhere and calls it a gate -- **that is right, and if the structure endpoint tempts you toward one, stop and write the finding instead.** || **THE THIRD OUTCOME IS A FULL ANSWER, NOT A FAILURE, AND I AM SAYING SO IN ADVANCE BECAUSE `0241` COST THREE ATTEMPTS ON EXACTLY THIS.** `the endpoint does not answer or carries no description -> say so with the URL and the date, and the row stays marked as not a query answer` is a delivered package. **Do not widen the scope to rescue a 502.** The World Bank outage moved from MMKT to LEND overnight between `0241`'s round 2 and round 3; assume the same can happen to you and write what you measured, with the date. || **AND THE ENUMERATION IS NOW THE HOUSE STANDARD FOR THIS FILE -- do not break it.** `0241`'s round-3 pass rested on 39 rows whose line references all land on the sentence they name. **Row `:231` is yours; whatever you write at `:31` and `:134` must be reflected in it in the same edit**, or the enumeration goes stale exactly as it nearly did in round 2. A sweep is unprovable; an enumeration is countable. || **NOT YOUR BUSINESS, and your own proposal says most of it:** the twenty World Bank cells, the result line, `R = 19`, way 2 at `:163` (report what your answer implies for it, do not rewrite it), and any extension to a further source."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/quellenbefund-leitzinspfad.md, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
abnahme: The two conditions under Acceptance. One retrieval, or a written statement that the retrieval does not settle it.
---

# „not the Selic" is the last negative in the file with no query anywhere behind it

Proposed 2026-09-08 by the daten-pruefer, out of the round-3 review of `0241`
(`befunde/pruefung-0241-negativbefunde-an-ihre-abfrage-binden-2026-09-08-3.md`).

`quellenbefund-leitzinspfad.md:31` and `:134` say the Brazilian `DISR_RT_PT_A_PT` value is
the „rediscount rate, **not the Selic**". Its enumeration row (`:231`) marks it honestly as
**not a query answer**, carried from `daten/reihen.toml` `[[widerspruch]] nr = 5` — and
`reihen.toml:621` asserts it too, with no query behind it either („der Rediskontsatz, der
nicht die Selic ist"). Two files assert it, neither measured it.

**Why it is not a defect of `0241` and why the enumeration is right to keep it:** condition
1 of that package requires every negative to name the query it answers, and this row does
exactly that by naming that it has none. `0241` was also instructed not to retrieve. So
this is a remainder, not a repair.

**Why it is worth a run.** It decides the BRA cell of the „Policy rate?" column — the whole
column is what makes the result „no vetted source carries a policy rate for all four". And
way 2 at `:163` proposes `USA and BRA DISR` as the mixed path: if the Brazilian series were
the policy rate after all, way 2 costs one country less than the file says. It is the same
shape as the `FR.INR.LEND` / PBoC correction that round 1 of `0241` forced — an
institutional identification asserted about a series where the source may not make it,
except this one runs the other way, as a denial.

## Acceptance

1. **Query the IMF structure endpoint for what `DISR_RT_PT_A_PT` is** — the codelist or
   concept description behind the code in `IMF.STA/MFS_IR` 9.0.0 — and write into `:31`,
   `:134` and the enumeration row `:231` what that answer supports, **not more**. Three
   outcomes are all acceptable, and which one you write is decided by the answer:
   - the description identifies the instrument per country → the claim is bound, name the
     query;
   - it names a discount/rediscount rate generically and identifies nothing per country →
     write that, exactly as `:140`–`:150` now does for `FR.INR.LEND`, and the negative
     becomes „the source does not identify this series as the Selic or against it";
   - the endpoint does not answer or carries no description → say so with the URL and the
     date, and the row stays marked as not a query answer.

   **No source outside the vetted four**, and no comparison against a Selic series from
   elsewhere: that is a new source and therefore a gate.

2. **`reihen.toml:621` says the same thing and must not be left behind** — the two files
   disagreed once before in exactly this way (`0241`, Ruecklauf-1 finding 3). Scope that
   clause the same way you scope the befund. **Hard limit, unchanged and the reason it is
   named here:** that block carries `technik.md`/`spiel.md` citations. Leave every citation
   byte-identical; the file carries **62** lines with those keywords as of 2026-09-08 and
   must carry 62 after. If the clause cannot be scoped without touching a citation, report
   it and leave it.

No money, no sign-up, no outward contact. One endpoint.
