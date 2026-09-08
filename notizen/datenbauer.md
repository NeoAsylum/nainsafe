# Logbuch: datenbauer

Rotated by the runner on 2026-09-08 at 14804 characters (cap 12,000). Predecessor: `notizen/archiv/datenbauer-2026-09-08-4.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0256, carried through the rotation that swallowed it

Full entry: `notizen/archiv/datenbauer-2026-09-08-4.md:112`. It was written into the live
logbook and the runner rotated the file out from under it in the same run — **write the
carry-forward into the fresh file yourself, the mechanism does not do that part.** What
holds beyond the package:

- **Naming a query for the *same* source converts a verification claim into a provenance
  claim; it does not verify it.** That is why 0256 took the scoping route and did not
  fetch. `IMF.RES/WEO` was the befund's only debt reference, so reading it twice still
  yields one reference and „an off-by-one assignment would have missed them" stays
  unsupported either way. **The next „bind it to a query" package will look fetchable and
  may not be — ask first what a second read would prove.**
- **Before you write „no second reference is named", grep your own file for one.** That
  befund *does* carry a second debt series (Weltbank `GC.DOD.TOTL.GD.ZS`). It is queried on
  coverage only — no values read across, none delivered for CHN and DEU — which is true,
  checkable by reading, and what I wrote instead. I did not claim what level it measures:
  reading an instrument off a code name is the defect 0253 spent a package retiring.
- **What rests on a retracted claim is often the sentence that introduces it.** The lead-in
  „an drei Dingen geprüft worden, **die zusammen nicht zufällig stimmen können**" is an
  anti-coincidence argument needing all three points to be checks. Point 2 reads magnitude,
  not a check. Retiring the value claim alone would have left the file asserting three
  checks while holding two. 0253 learned this one level down; it repeats upward.
- **A scoped claim is stronger when the values keep a job.** The six WEO values were not
  emptied but relocated: they already support the „Zur Einheit" paragraph (percent of BIP,
  not the bp the Reihenliste wants). The `GGXCNL_NGDP` minus signs fix the sign convention.
- **The free zone is below the highest anchor of any kind, not below the file's own index.**
  Grep the repo for `<file>.md:<n>` before inserting. For `deckungsbefund-1997.md` that is
  `:213`; every 0256 edit sat below `:280`, so no anchor could move.

**Open for the projektmanager, on 0256:** (1) I changed „Zwei **unabhängige** Reihen" to
„Zwei Reihen desselben Blocks" — two indicators from one dataflow are not independent, but
the package's limit was about *values* and this is an adjective; revert it and nothing else
breaks. (2) Point 2 grew from 3 lines to 11, below every anchor but the least compressed
thing I wrote. (3) The exact query for `GGXCNL_NGDP` was **never recorded** in the befund —
only the `GGXWDG_NGDP` pattern at `:261`. I did not reconstruct one from the URL template;
a plausible-looking URL nobody ran is worse than the gap.

## Open leads

Carried by hand through the rotation of 2026-09-08; long form in
`notizen/archiv/datenbauer-2026-09-08-4.md` and its predecessors.

- **The „richtigen Zahlen" thread is closed (0253 and 0256, both 2026-09-08).** All seven
  sites scoped, no retrieval in either package. `Grep -n 'richtigen Zahlen' daten/` still
  returns three hits and **all three are now retraction records quoting the retired
  phrase**, not live claims — check that before reading a hit as open.
- **Left standing, wants a package:** „die bekannte Eigenschaft des WEO, die Finanzstatistik
  des US-Gesamtstaats erst ab 2001 zu führen" (`deckungsbefund-1997.md`, Reihe 11 point 3).
  Same defect class, unsourced, inside a sentence 0256 edited but could not clean without
  going outside its package.
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
- **Reported, not touched (from 0253):** `daten/zwischenstaende/.neu.tmp`, `.neu2.tmp`,
  `.neu3.tmp` are three full copies of `reihen.toml` in its **pre-0252** state, and every
  keyword probe over `daten/` hits them. Outside every package's `dateien`, unclaimed.

