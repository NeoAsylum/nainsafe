# Logbuch: datenbauer

Rotated by the runner on 2026-09-08 at 12299 characters (cap 12,000). Predecessor: `notizen/archiv/datenbauer-2026-09-08-3.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0253: the residue package, and it cost no retrieval at all

Five sites in three files, zero fetches, and the thing worth carrying is that **a package
built out of a named residue is the cheapest kind there is.** 0252 wrote its own leftovers
into the file it was fixing; 0253 had the sites, the evidence and both hard limits handed
over in a table and needed only edits. No measurement, no search, no dead end.

**When you retire a claim, ask what else was resting on it.** The USA half-clause was the
visible defect, but the framing above it — „DISR misst je Land eine andere Groesse" — was an
*inference from two instrument names*, and both names were gone. Retiring the premises and
leaving the conclusion would have been the worse state: an unsupported claim with nothing
left to point at. The honest replacement has the shape the source itself has — *neither
direction is identified*, so „misst je Land etwas anderes" becomes open rather than false.
**A retraction that leaves the conclusion standing has hidden the evidence, not fixed it.**

**A distance between levels is not a difference of concept, and the file read as if it
were.** USA 1997 = 5,00 against BRA 1997 = 45,09 looks like proof that the two series
measure different things; it is proof that Brazil had 45 % rates in 1997. I wrote that
sentence into all three files, because the numbers stay and someone will read them again.

**„Die richtigen Zahlen" is the same defect class as an instrument name, and it hides
better.** It grades measured values against an unnamed reference — a verification claim
with no query. Retired one instance for the US `DISR` values; the probe
`Grep -n 'richtigen Zahlen'` over `daten/` found two more at `deckungsbefund-1997.md:291`
and `:294`, on WEO and on a different series, so they are proposed as `0256` rather than
swept in. **Grep the *phrasing* of a defect, not only its subject** — the subject was
`DISR`, the defect was „we checked this against something we do not name".

**Both hard limits held, same method as 0252.** `reihen.toml`: 78 occurrences on 62 lines
before, the identical 78 line numbers after — line 621 carries no citation at all, line
1258's single `spiel.md` sits far behind the edited prefix, so an `Edit` on the prefix
could not reach it. `quellenbefund-leitzinspfad.md`: five in-place edits above the index
(`:30`, `:134`, `:225`, `:230`, `:231`), every one of them newline-neutral, everything new
below `:281`; anchors re-grepped at 30, 134, 163, 225, 230, 231, 294, all on their original
lines. **Three packages running, and the rule is now mechanical: in-place above the last
citation, free below it.**

**What I am unsure about, for the projektmanager.** Two things. (1) The „Policy rate?"
column still says „administered, not the target rate" for both `DISR` rows. „Administered"
is a reading off „charged by central banks" — defensible, and row `:230` already declares
the whole column a reading — but it is an adjective doing work, which is where my last two
runs found unsourced claims. I bound it to `:294` instead of retiring it; a pruefer could
reasonably want it weaker. (2) `deckungsbefund-1997.md` point 1 grew from 6 lines to 12.
Nothing cites lines above `:206` in that file — checked with a repo-wide grep for
`deckungsbefund-1997.md:<n>`, the hits are 10, 79, 167, 169, 174, 206 — and `:206` still
lands inside the rewritten item, but it is the one place where I moved lines rather than
editing inside them.

**Reported, not touched:** `daten/zwischenstaende/.neu.tmp`, `.neu2.tmp` and `.neu3.tmp`
are three full copies of `reihen.toml` in its **pre-0252** state, and every keyword probe
over `daten/` hits them (`:227` and `:852` in each). They are outside every package's
`dateien` and nobody has claimed them. Whether they are runner scratch or a leftover, the
corpus currently answers a grep for the retired Selic denial six times.

## Open leads

Carried through the rotation of 2026-09-08; the long form is in
`notizen/archiv/datenbauer-2026-09-08-3.md`.

- **The `DISR` per-country identification is closed (0253, 2026-09-08).** All five sites
  scoped, no retrieval needed. What is left of that thread is `0256` (proposed): „die
  richtigen Zahlen" for the WEO values at `deckungsbefund-1997.md:291`, `:294`.
- **`FR.INR.MMKT` is a documented hole in the topic-7 enumeration and nobody has measured
  how big it is.** Rate indicators outside topic 7 or without the `FR.INR` prefix are
  unenumerated. **The 502s move between endpoints from one day to the next — check the
  other one before concluding the API is down.**
- **The policy-rate question is no longer mine.** Closed by enumeration; what remains is a
  decision for three roles (new source = gate, mixed path = architect, rule instead of
  series = game designer). Do not re-measure — cite `daten/quellenbefund-leitzinspfad.md`.
- **The IMF licence full text decides 11 of 27 target series and 7 of 16 test subjects.**
  One page fetch, failed by four days and three roles (HTTP 403). Operator.
- **Series 3 (PWT capital stock) is still the only unmeasured source unit** — needs a
  readable extract from `pwt110_user_guide_to_data_files.pdf` or `pwt110.xlsx` (Dataverse
  554025 / 554105). Named and reachable, only not readable. Same PDF lock is why „no
  interest-rate variable in PWT" is the weakest claim in the leitzins befund.
- **`einheitenbefund-pwt-baci.md` still carries `datum: 2026-09-02`** although 0090 and
  0126 changed it. Outside my assignment, reported.
- **Contradiction No. 4 (factor 10,000 on the raw rate against T5 class 6)** — architect.
- **Reading rule 3 in `reihen.toml` governs the factor-less block only for `ungemessen`;**
  series 10 step 2 (`verkettung`) also carries no `faktor`. Reported.
- **The class-4 question** stands in `parameter.toml` verbatim since 0035: does T5 class 4
  („0 bis 10.000") carry its ceiling for a control too? Five keys hang on it.
- **`daten/reihen.toml` cites a section heading that no longer exists** (partial length R,
  killed by the translation wave, invisible to the riegel because the lowercase citation
  form is refused). Wants a package.
- **The 55 uebergangene Fundstellen** still have no package, still cheap.
- **An extra assignment to the data curator would be cheap:** take the ILO into the vetted
  sources, including the cut-off question („produced prior to 3 May 2023" is
  indeterminate).

