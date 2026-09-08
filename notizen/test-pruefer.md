# Logbuch: test-pruefer

Rotated by the runner on 2026-09-08 at 12763 characters (cap 12,000). Predecessor: `notizen/archiv/test-pruefer-2026-09-08-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0244 (kennzeichen apparatus lifted to header): geprueft

What worked: judging the "does it go red" question from code paths plus the runner's
green report instead of wishing for execution. For a ledger-based completeness probe the
chain is checkable statically — counter written only in the catch block, exact-count
comparison, `main` returns 1 on `fehlgeschlagen` — and the green run then discharges the
builder's own "I ran nothing" uncertainties: a wrong barrier attribution would have been
red. Recounting `BRICHT_AB_MIT` sites per riegel (6/1/2/1/1/1/2 = 14) against
`SOLLZAHLEN` took one grep and was the strongest single check.

Interpretive point worth remembering: 0244's condition 2 says "For every Riegel of
`werte.cpp` you register: a counter ...". Strictly read, ~10 abort sites in
`src/werte.cpp` (reached only via `hat_abgebrochen`) are in no ledger. I judged by the
condition's own purpose sentence (the proposal's fourteen `ERWARTE_ABBRUCH` calls) and
wrote the alternative reading into the finding for the PM — proposal 0255 is exactly the
residual. Pattern: when an acceptance criterion is ambiguous, state the reading applied
in the finding instead of silently picking one or bouncing the package.

Also useful: the runner's uebersetzung report header lines ("10 Kernquelle(n) und 12
Probe(n) geprueft") independently confirmed the sperre-gap claim of condition 3 without
reading CMake logic twice.

## 2026-09-08 — 0255 (21 hat_abgebrochen sites into the ledger): geprueft

What worked: my own previous pruefung (0244, same file, same day) was the pre-state
record — it had committed "21 hat_abgebrochen / 14 BRICHT_AB_MIT / 6-1-2-1-1-1-2" —
so "no assertion lost" was checkable without git diff. Writing tomorrow's numbers into
today's befund keeps paying; done again (see below).

New pattern worth reusing: **riegel attribution needs no source read when the pair
comparison ran green.** One-riegel-per-wording is exactly what auswerten's eigene/fremde
halves enforce — lumping or splitting wordings goes red, and exact SOLLZAHLEN counts
force all messages to arrive. Saved reading src/werte.cpp entirely (~72k tokens class
of cost avoided).

Freshness check for MERKE-style "record what a global holds" macros: walk the lines
between producer and consumer and confirm they only *read* the global. Two distant
sites (2198, 2229) were fine; a stray aborting call in between would have been the bug.

Corpus for the next pruefung on werte_probe/kennzeichen: 23 riegel + Anzahl, SOLLZAHLEN
23 entries sum 35 (14 via BRICHT_AB_MIT, 21 via MERKE), MELDUNGEN_MAX 64, ALLE_RIEGEL
generated (riegelliste, :197-206), forget-net = two static_asserts :430-431, printed
line says "vor Paket 0255 waren es 14 aus 7". Root ctest 27 (kennzeichen_riegel from
0251 landed and passes), kern 13.

## 2026-09-08 — 0257 (festkomma_probe onto Buch): zurueck

The test mechanics were flawless — nine abbruch sites recounted, nach_i64's three
callers grepped (:141/:162/:293, so three riegel for one site is complete), 17
BRICHT_AB_MIT counted against SOLLZAHLEN exactly. What sank it was neither: two
**comments** the builder wrote turned two tree riegel red, and both riegel print the
file and line themselves. bezeichner_riegel: the history comment at :136 names the
removed macro ABBRUCH_MELDET, which no longer resolves. belegstellen_riegel: the new
citation at :259 („Absatz \"Ueberlauf\" ueber wurzel") is 1 of 42 Zitate unresolved,
at both tool versions.

Pattern worth keeping: **after a package that removes or renames a name, grep the
delivered file for that name in comments** — the bezeichner riegel will, and a
green probe says nothing about it. Same for any newly written citation: it enters the
belegstellen corpus and can go red (and shifts the kopfzahlen counts as a side
effect — 42/54 vs the tool head's 41/53 tonight; I did not charge the drift, only
the unresolved citation).

Also: the PM's rewritten clause ("attributable to festkomma_probe.cpp") cut cleanly
both ways tonight — four other belegstellen failures were the moved-HEAD problem
(Bezugsstand 2f2f79f vs HEAD ceee29d) and stayed off the builder's account. Reading
the runner report's per-riegel finding lines is what makes that attribution cheap.

Corpus for the fix round: festkomma 10 riegel + Anzahl, SOLLZAHLEN sum 17,
RIEGEL_OHNE_ZUSTAND = 1 (potenz_i128, :121), printed line "vor Paket 0257 stand hier
keine". Kern ctest 13/13 green; root red only via belegstellen/bezeichner lanes.

