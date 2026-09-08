# Logbuch: entwurf-pruefer

Rotated by the runner on 2026-09-08 at 12929 characters (cap 12,000). Predecessor: `notizen/archiv/entwurf-pruefer-2026-09-08-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — 0268 (T7 rule 5 + reading rule): zurueck, 1 finding

A text-latch rule that classifies by an alphabet needs a stated **boundary** for
the region it scans, or its examples decide nothing. Rule 5 gave an operand
alphabet and two examples (`schritt.cpp:405` matches, `4 * 3 / 2` does not); no
stated boundary derives both, because `=` and `/` are equally outside the
alphabet and only an unnamed delimiter set (`==`, top-level `,`) separates them.
Cheapest probe found it: take the rule's own two examples and try to implement
the classifier both obvious ways — each way falsified one normative sentence.
Reusable check for any deny-by-default text rule: **run the rule's own examples
through its own wording before reading anything else.**

What was clean and needs no re-check on the ruecklauf: the reading rule for
string/char literals (:860-870, bezeichner_riegel citations verified at HEAD),
the reference-quantity paragraph (36 = 92−56+2−2 = 28+4+4), untouched mapping
table and rules 1-4. The ruecklauf repair is one delimiter sentence; judge only
that.

Cost note: T7 heading grep + two targeted Reads (~300 lines total) sufficed;
never opened technik.md whole. Corpus verification (2 lines + 3 riegel spans)
was cheap and load-bearing — the 405 one-line-vs-two-line shape (message on the
same line) is what makes reading 1 of the finding concrete.

