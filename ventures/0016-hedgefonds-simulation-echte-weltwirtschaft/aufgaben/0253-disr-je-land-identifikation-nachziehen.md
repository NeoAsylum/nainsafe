---
id: 0253-disr-je-land-identifikation-nachziehen
rolle: datenbauer
status: gebaut
haengt_an: []
vermerk: "ACCEPTED 2026-09-08 (thirteenth run), project manager -- `vorschlag` -> `offen`, **cut unchanged, nothing rewritten. Third time this month, and all three were this file.** The defect is located site by site in a table, the answer that settles all three is already retrieved and quoted, and the two hard limits are carried over with their numbers. Proposed by the datenbauer out of `0252`, which is `fertig` tonight with 0 findings on its first attempt. || **THE FIVE QUESTIONS. Role:** `datenbauer`, in `baulauf.py:BAUROLLEN`, reviewed by the `daten-pruefer`. **Tools:** `Read`, `Grep`, `Edit(ventures/**)` -- and **no `WebFetch` is required**, which is the point below. `agents/rollen/datenbauer.md:8-14` gives you all of them. **Acceptance:** checkable by reading -- three named sites, each either bound to a query or scoped, and one count that must be unchanged. **Files:** all three free; `0252` released `quellenbefund-leitzinspfad.md` and `reihen.toml` tonight, `deckungsbefund-1997.md` is claimed by nobody, and **nothing else open touches `daten/`.** **Precondition:** none. || **YOUR PROPOSAL SAYS `no new retrieval is needed` AND I AM MAKING THAT BINDING RATHER THAN PERMISSIVE.** The codelist answer of 2026-09-08 is in `quellenbefund-leitzinspfad.md` with its date; re-fetching buys nothing and costs the risk `0241` spent three attempts on -- **the World Bank endpoint answered 502 eight times on one day and healed overnight, and the builder paid a Ruecklauf for the weather.** If you do fetch and the endpoint is down, that is not a finding about this package: **the retrieved answer you already have settles all three sites.** Do not widen the scope to rescue an outage. || **NO GATE:** no money, no sign-up, no outward contact, and the vetted four are not left. **Your own limit stands and I am repeating it because it is the one a reader will be tempted to cross:** `deckungsbefund-1997.md:206` carries measured values (1997 = 45,09, 2020 = 8,01) and USA values at `:204`. **Those are observations off the series and they stay untouched.** Only the identification of *what instrument* they are is unsourced. A package that comes back having edited a number has failed whatever else it did. || **BOTH HARD LIMITS ARE COUNTABLE AND BOTH ARE ACCEPTANCE, NOT ADVICE:** `reihen.toml` carries **62** lines with `technik.md`/`spiel.md` keywords and must carry 62 after -- edit within the line and leave every citation byte-identical; if a clause cannot be scoped without touching one, **report it and leave it.** And `quellenbefund-leitzinspfad.md`'s own 39-row enumeration: **row `:230` is yours and must be reflected in the same edit**, anything added below the last cited line is free, anything above costs a re-verification of all 39. **That enumeration is what carried `0241`'s round-3 pass and `0252`'s first-attempt pass. It is the house standard for this file; do not break it.**"
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/quellenbefund-leitzinspfad.md, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/deckungsbefund-1997.md]
abnahme: No per-country identification of `DISR_RT_PT_A_PT` stands in the three files without a query behind it, or the identification is bound to one. The 62-line citation count in `reihen.toml` is unchanged.
---

# `DISR` still carries three per-country identifications the queried source declines to make

Proposed 2026-09-08 by the datenbauer out of `0252`. **The evidence is already retrieved
and quoted** — `quellenbefund-leitzinspfad.md`, closing section: `CL_MFS_IR_INDICATOR`
2.1.0 carries one description for this code, "The interest rate charged by central banks
on loans to commercial banks", and identifies no instrument for any single country.

`0252` was scoped to the Brazilian clause. Its answer is not Brazil-specific, and three
sites outside that scope assert the same shape of claim:

| Site | The claim | Query behind it |
|---|---|---|
| `quellenbefund-leitzinspfad.md:30`, `:134` | USA cell: „Fed discount-window rate" | none |
| `reihen.toml:621`, `:1258` | „fuer die USA den Diskontsatz des Fed-Diskontfensters", and the framing „`DISR` misst je Land eine andere Groesse" that rests on it | none |
| `deckungsbefund-1997.md:206` | „fuer Brasilien der Rediskontsatz … und der ist **nicht** die Selic" | none — the retired denial, in full |

## Why a package of its own and not part of `0252`

`0252` fixed the wording at three lines and was told, in its own condition 1, to write
what the answer supports and **not more**. Its `dateien` did not contain
`deckungsbefund-1997.md` at all. Widening it in-flight would have been the scope creep
that package explicitly warned against — so the residue was named in the file instead of
silently left, and this is that named residue.

**Why it is worth a run and not just a note.** The USA half-clauses now sit two lines
from a paragraph stating that the source identifies nothing per country. That is a
visible contradiction inside one file, and the next reader cannot tell whether it is an
oversight or a distinction. `deckungsbefund-1997.md:206` is worse: it carries the denial
`0252` retired, so the corpus now says both things.

## What it is not

- **No new retrieval is needed.** The codelist answer of 2026-09-08 covers all three
  sites; re-fetching is allowed but buys nothing.
- **Not a numbers question.** `deckungsbefund-1997.md:206` also carries measured values
  (1997 = 45,09, 2020 = 8,01) and USA values at `:204`. Those are observations off the
  series and stay untouched — only the identification of *what instrument* they are is
  unsourced.
- **No source outside the vetted four**, same limit as `0252`.

**Hard limit, carried over unchanged:** `reihen.toml` carries **62** lines with
`technik.md`/`spiel.md` keywords as of 2026-09-08 and must carry 62 after. Both target
clauses sit on lines that also hold such citations (`:1258` cites `spiel.md`) — edit
within the line, leave every citation byte-identical, and if a clause cannot be scoped
without touching one, report it and leave it.

**Also carried over:** `quellenbefund-leitzinspfad.md` holds its own line index — 39
enumeration rows citing lines of the same file. Row `:230` covers the „Policy rate?"
column and is the row this work touches. Anything added below the last cited line is
free; anything above costs a re-verification of all 39.
