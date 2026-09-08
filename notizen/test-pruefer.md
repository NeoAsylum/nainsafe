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

