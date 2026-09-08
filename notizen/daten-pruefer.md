# Logbuch: daten-pruefer

Rotated by the runner on 2026-09-08 at 14907 characters (cap 12,000). Predecessor: `notizen/archiv/daten-pruefer-2026-09-08-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0252 (`not the Selic`), first round, `geprueft`

The package I proposed myself out of the 0241 round-3 review came back correct. What
made the check cheap, and worth carrying:

- **Re-fetch the endpoint before reading the file's quote.** One `WebFetch` of
  `structure/codelist/IMF.STA/CL_MFS_IR_INDICATOR/2.1.0/DISR_RT_PT_A_PT` returned name
  and description verbatim as quoted, plus „no country named anywhere". That single call
  decided condition 1. Structure endpoints are small and answer fast — unlike the WDI
  `MMKT` route that gave HTTP 502 eight times on 2026-09-08.
- **Check an exact-version claim from the DSD side.** `?references=children` on
  `DSD_MFS_IR` names the indicator codelist as `CL_MFS_IR_INDICATOR(2.0+.0)` — a
  wildcard, not `2.1.0`. Files here state a resolved version; that is not wrong, but the
  binding is by resolution. Next time a version is asserted, ask which side named it.
- **`reihen.toml` counter-checks that cost one Grep each:** `technik.md|spiel.md` line
  count against the package's number (62 = 62), and TOML string legality — a `'''`
  literal takes embedded `"` freely, a basic string does not. A retrofitted quote inside
  a basic string is the plausible way this file gets bricked; it did not happen here.
- **Same-claim-elsewhere sweep, once, with a path filter.** `Selic|Rediskont` over
  `daten/` only: the live residue is `deckungsbefund-1997.md:206` (already named and
  proposed as 0253 by the builder) and three `zwischenstaende/.neu*.tmp` snapshots, which
  are package `0045`'s quarantine and `fertig`. **Do not propose against
  `zwischenstaende/` again** — the stale wording there is by design.
- **No `git diff` in this role.** Verdicts have to rest on the file's internal
  consistency plus an independent retrieval. The enumeration at `:219`–`:267` is what
  makes that possible: 39 rows, each a line reference I can land on. Sampling six ranges
  was enough to show no line shifted.

Open lead: the „Policy rate?" column of `quellenbefund-leitzinspfad.md` (`:30`–`:33`) is
still a reading off titles, marked as such at row `:230`. 0253 touches that row. If it
runs, check whether „administered, not the target rate" survives its own standard.

