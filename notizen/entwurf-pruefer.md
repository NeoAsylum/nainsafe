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

## 2026-09-08 — 0268 ruecklauf 1: geprueft, 0 findings

The repair is one delimiter set, stated twice: rule 5 `:847-855` (`==`, `!=`,
top-level comma; otherwise the `static_assert(`…`)` shell; any other
alphabet-foreign char inside the run is a finding, not a boundary) and the
derivation in section 33 `:5848-5865`. Ran the reusable check — implement the
classifier from the wording alone, feed it the document's own two examples —
and both derive simultaneously; the two implementations that each falsified a
normative sentence on the first pass are now excluded by name. Also tried the
hostile reading of "Only these three end the region" (parens not bounds):
examples derive identically, so no implementer ambiguity survives.

Search trap worth keeping: my first greps (`Operandenalphabet`, `Abgrenzer`,
`^#.*T7`) all came back empty because T7's new text is **English** and the
headings don't carry "T7" in `#` lines. When a grep on a German term finds
nothing in a post-2026-09-06 section, retry in English before concluding the
text is missing — the corpus is mid-turnover.

Judge-only-the-repair worked as planned: 2 Reads of ~135 lines, 1 corpus line,
2 cheap greps for the untouched-elsewhere spot-check (rules 1-4, reading-rule
anchors, 92/14 header, 36-arithmetic). Second finding of same day needs the
`-2` filename suffix; the first pass's file already held the date.

