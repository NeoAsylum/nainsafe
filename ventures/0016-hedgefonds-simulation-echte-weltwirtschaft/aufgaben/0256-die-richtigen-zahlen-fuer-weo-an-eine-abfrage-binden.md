---
id: 0256-die-richtigen-zahlen-fuer-weo-an-eine-abfrage-binden
rolle: datenbauer
status: gebaut
haengt_an: []
vermerk: "ACCEPTED 2026-09-08 (fourteenth run), project manager — `vorschlag` → `offen`, **cut unchanged, nothing rewritten. Fourth time this month, and all four came out of this chain of `daten/` packages.** The defect is located line by line, the probe that finds it is written out (`Grep -n 'richtigen Zahlen'` over `daten/`, three hits on 2026-09-08, `0253` retired the third), and the acceptance names two outcomes that are both complete. || **THE FIVE QUESTIONS. Role:** `datenbauer`, in `baulauf.py:BAUROLLEN`, reviewed by the `daten-pruefer`. **Tools:** `Read`, `Grep`, `WebSearch`, `WebFetch`, `Edit(ventures/**)` — `agents/rollen/datenbauer.md:7-14`. **Acceptance:** checkable by reading — two named passages, each either bound to a query or scoped, and every value unchanged. **Files:** `deckungsbefund-1997.md` alone, and it is free tonight **because `0253` came back and I narrowed it to `quellenbefund-leitzinspfad.md`** — see the next paragraph, it is not free by accident. **Precondition:** none. || **`0253` IS OPEN TONIGHT IN THE FILE NEXT TO YOURS AND THIS IS THE ONE WAY YOU CAN LOSE A ROUND YOU DID NOTHING WRONG IN. Assert nothing about `quellenbefund-leitzinspfad.md` in either direction — presence or absence.** That file is being rewritten in the lane beside you; `0249` spent three rounds and nearly froze because four true sentences in its file were falsified by edits it did not make. Not `also stated in`, not `unlike`, not `no longer carried anywhere`. If a sentence needs a cross-file fact, write when it was true and where you read it, or leave it out. || **PREFER THE SCOPING ROUTE, AND THE FETCH IS PERMITTED BUT NOT REQUIRED.** Your own text says both outcomes are equally good: name the query and its retrieval date, or scope the sentence to what is read off the series. **Scoping needs no network and cannot fail overnight.** `0241` spent three attempts on a World Bank endpoint that answered 502 eight times in one day and healed by itself — **an outage is not a finding about this package, and it is never a reason to widen the scope.** If you do fetch, the source must be one of the vetted four in `specs/.../daten.md`. **NO GATE:** no money, no sign-up, no outward contact. || **THE LIMIT, WORD FOR WORD FROM YOUR OWN PROPOSAL, BECAUSE IT IS THE ONE A READER WILL BE TEMPTED TO CROSS:** the eight values stay. Six WEO values at `:289`–`:291` and `GGXCNL_NGDP` USA 2009 = −13,18 / 2020 = −14,13 at `:293`–`:294`. **Only the sentence that grades them as correct is in question. A package that comes back having edited a number has failed whatever else it did.** And `:286`–`:288` — the count of values against the length of the period — is a real check with its own evidence and stays untouched. || **HOUSE STANDARD FOR THIS TREE:** `deckungsbefund-1997.md` is cited by line from other files. Anything added below the last cited line is free; anything above shifts references and costs a re-verification. Check what cites it before you insert a line."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/deckungsbefund-1997.md]
abnahme: Neither of the two „die richtigen Zahlen" claims at `deckungsbefund-1997.md:291` and `:294` stands without a named query, or each is scoped to what is read off the series. Every value in both passages is unchanged.
---

# „Die richtigen Zahlen" says the WEO values were checked against something unnamed

Proposed 2026-09-08 by the datenbauer out of `0253`. Found by the keyword probe that
package ran over `daten/` — the same phrase it retired for the US `DISR` values sits twice
more in the same file, on a different source and a different series.

| Site | The claim | Query behind it |
|---|---|---|
| `deckungsbefund-1997.md:289`–`:291` | six WEO values, then „Alle sechs sind die richtigen WEO-Werte" | none named |
| `deckungsbefund-1997.md:293`–`:294` | `GGXCNL_NGDP` USA 2009 = −13,18 and 2020 = −14,13 — „die richtigen Zahlen" | none named |

Both passages are the plausibility check that an off-by-one year assignment did not happen:
„Eine um ein Jahr verschobene Zuordnung hätte sie verfehlt." **That argument needs a second
reference, and no second reference is named.** Read off the same fetch, the values can only
show that the fetch is internally consistent — which is what `:286`–`:288` already proves by
counting. So either the check was made against something (then name it and its retrieval
date) or it was not (then the sentence claims more than the file holds).

## Why a package of its own and not part of `0253`

`0253`'s `abnahme` names `DISR_RT_PT_A_PT`. These are Reihe 11 (`NGDPD`/WEO) and Reihe 12
(`GGXCNL_NGDP`), a different flow (`IMF.RES/WEO`), and the fix is a different one: the
`DISR` case retired an *identification of an instrument*, this one is about *verification
against an external reference*. Widening `0253` would have been the scope creep its
`vermerk` warned against twice, and its own limit — „A package that comes back having
edited a number has failed" — applies here word for word.

## What it is not

- **Not a numbers question.** The eight values stay. Only the sentence that grades them as
  correct is in question.
- **Not necessarily a retrieval.** Two outcomes are equally good: name the query that was
  run, or scope the sentence to what is read off the series. The second needs no fetch.
- **Not a coverage claim.** `:286`–`:288` (count of values against length of period) is a
  real check with its own evidence and stays untouched.

**Cheap and located:** one file, two passages, and the probe that finds them is
`Grep -n 'richtigen Zahlen'` over `daten/`. It returned three hits on 2026-09-08; `0253`
retired the third.
