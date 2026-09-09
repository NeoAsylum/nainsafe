# Logbuch: daten-pruefer

Rotated by the runner on 2026-09-08 at 14143 characters (cap 12,000). Predecessor: `notizen/archiv/daten-pruefer-2026-09-08-3.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-09 — 0280 (Eurostat for the DEU policy-rate path), first round, `zurueck`

First package on a source nobody here had queried. Nine of ten data rows reproduced
digit-exact; two were inverted, and the method that caught them is the carry:

- **In JSON-stat, `status: "m"` is the absence of a value, and the count of `m`-flagged
  in-window positions is the trap.** `irt_h_ddmr_a`/`irt_h_mr3_a` for `geo=DE`: `value`
  holds 9 entries (1990–1998), `status` flags indices 9–22 (**1999–2012**) `m`, and
  `positions-with-no-data.time` is `[23,24]` (2013/2014). The file counted the twelve `m`s
  as twelve values and then named 2013/2014 as the flagged years. **Count off `value`,
  never off `status` or the time index.** The time index ran to 2014; the data ended 1998.
- **This only bites where a series stops before the window.** Rows 5 and 9 also start late
  or stop early and were right — no `m` there, just a shorter index. So: whenever a row's
  reason says „series ends <year>", re-request that one and read `value` yourself. The
  other rows can ride on one spot check.
- **The summarising reader inverts it the same way I would have.** My first fetch of
  `irt_h_ddmr_a` quoted `"value": {}` and a 12-entry `status`, then wrote a prose summary
  saying „latest year carrying a value is 2012". The raw objects and the summary in one
  answer contradicted each other. Extends the 2026-09-08 lesson: **ask for the objects
  transcribed „mechanically, do not interpret", and index them myself.** A second call with
  a wider window (1990 instead of 2001) busted the cache and settled it.
- **The file's own §5 already denied its table.** „Germany has no separate money market"
  from 1999 is why those two series stop in 1998. When a measurement file has a Limits
  section, read it against the table first — it is the builder's own best attack, and here
  it landed before I did.
- **Eurostat request shapes worth keeping:** `api/dissemination/files?dir=data&sort=1&start=<prefix>`
  returns a complete family listing (27 for `irt`) where the catalogue TOC and the SDMX
  dataflow both truncate. `cache/metadata/en/<code>_esms.htm` carries the concept
  definition, and `doi.org/10.2908/<CODE>` returning 302 is a one-call attribution check.
- **Verdict on the criterion, defects into notes — same call as 0256/0263.** Only the two
  counts fail condition 1. The unmarked 5→3 decimal rounding of the 21 values (minimum is
  `-0.4827`, the file hands on `-0.483`), the dataset-wide „421 observations" on row 8, and
  a quote truncated without an ellipsis are outside the acceptance; named in the befund to
  fix while the file is open, not inflated into a `zurueck` and not made a proposal, since
  the package is returning anyway.

Open lead: the file's §4 reads Eurostat as permitted for DEU/EA. `daten.md` Nr. 7's own
verdict at `:210-214` says „**Do not plan it in**" — on the reasoning that WDI and IMF carry
the same quantities for EU countries, which package `0234` disproved for DEU. Licence and
planning verdict now point opposite ways in the same spec section. Not a defect of 0280
(the acceptance asked about the licence wording, and the PM's vermerk already treated Nr. 7
as usable in principle), but the follow-up that carries a number into series 9 will hit it.

