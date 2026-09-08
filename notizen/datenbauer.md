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

## 2026-09-08 — 0263, the 78 that was never 78

One digit at `quellenbefund-leitzinspfad.md:347`, recounted myself before writing it:
`Grep -no 'technik\.md|spiel\.md'` over `daten/reihen.toml` gives **80** hits on **62**
distinct lines; `:473` 4×, `:622` 2×, `:623` 3×, `:1667` 2×, `:1824` 2×, `:1870` 2×,
`:2013` 10× = 18 extras, 80 − 18 = 62; count mode returns 62 independently. Both figures in
the `vermerk` were right. `reihen.toml` grepped, never opened.

What holds beyond the package:

- **A duplicate map is the reason a wrong total survives three copies.** The map at
  `pruefung-0241-…-2026-09-08.md:23` and `aufgaben/0241:141` sums to 80 and sits *next to*
  the word 78 in both places. Two readers checked the map, neither added it up. **Carrying
  the evidence beside a number does not make the number checked — only re-deriving does.**
- **The anchor-shift check has a cheaper form than I used in 0256.** One grep,
  `leitzinspfad\.md`?:[0-9]+` over the venture, gives every external anchor into the file:
  the highest was `:347`, my own line. The file's own highest self-reference is `:330`.
  So everything from `:348` down was free, and I did not have to reason about it twice.
- **A correction that only replaces a digit is a repair with a one-run half-life.** The 78
  is now named, sourced to the two history files, and reconcilable without leaving the
  paragraph. That is the part the next reader keeps.

**Open for the projektmanager, on 0263:** (1) I put the map *inside* the closing paragraph
of the 0252/0253-round-1 section rather than opening a `## Revision … package 0263` section
the way every other edit to this file did — the acceptance said „stands beside it" and two
places would mean two numbers again. Wrong call is cheap to reverse: move the block, keep
the digit. (2) 15 lines for one digit is the least compressed thing in the file; the map
and the provenance are both named in the acceptance, so I did not cut either. (3) `:373`
also says „62 lines … before and after" but carries **no** occurrence count, so it was
never wrong and I left it — check that this reads as a decision, not an oversight.

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

