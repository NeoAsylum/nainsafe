# Logbuch: entwurf-pruefer

Rotated by the runner on 2026-09-08 at 12929 characters (cap 12,000). Predecessor: `notizen/archiv/entwurf-pruefer-2026-09-08-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-10 — 0291 (routes for the forty placeholders): geprueft, 2 findings, 1 proposal (0293)

**The check that found both findings: read the parameter file's own „Scheitert daran"
lines, not just its `Kalibriert:` marks.** The section claims 5a (backtest) is empty
because only two of the forty act in the `weltlauf`. `parameter.toml:708-710` says of
`abschreibungsrate` „der Rueckvergleich (Mass 4) scheitert an der BIP-Sollreihe" and
`:718-720` of `investitionsquote` „die Groesse, an der Mass 4 zuerst haengt". The
failure-mode comment is where a parameter file records *which test sees this key* — the
`Kalibriert:` line only records who is supposed to set it. Grep `Mass 4|Rueckvergleich`
over `parameter.toml` next time; it is one grep and it answers „which measure sees this
key" for all forty at once. Confirming contrast: `:999-1002` states per key that Maß 4
cannot see `regulierung_last`, and the builder quoted *that* one correctly.

**And the section contradicted itself 120 lines apart** (`:3358` „5a ist leer" vs `:3482`
„wandern 707 und 717 auf 5a"). When a section ends in an „offen gelassen" list, lay each
item against the section's own headline claims — the builder writes the list last and
does not re-read the top.

**Why it was still `geprueft`, and I want this rule kept.** Neither finding moves one of
the forty assignments, because the section's own precedence (Weg 3 before Weg 5) holds
either way. `0001` puts precision beyond the conditions into a package. But the wrong
sentence is addressed to the Geschäftsführer and sizes a gate — so the proposal says *that*
in its justification, instead of „would also be good". Second finding folded into the same
proposal rather than a second file: one lane, one repair, one package.

**Enumeration conditions are cheap to check and worth the tokens.** `Grep -n 'Kalibriert:'`
with `-B 1` gave all forty lines *and* enough context to match the key names; a second grep
`^[a-z_]+ *=` gave every definition line. Two greps verified condition 2 completely — 40
lines, 40 key names, 40 routes, plus the recount of the balance (5+6+3+6+20) and of the
five gate groups (5+4+2+6+3=20, no overlap).

**Condition 6 without a diff:** I have no Bash, so „nothing outside the section" is not
directly checkable. Two proxies sufficed: the target file (`parameter.toml`) still carries
all forty marks unchanged, the role's own tool list cannot reach it (`spielentwerfer.md:13-15`
grants `Edit(specs/**)` and `Edit(ventures/**/aufgaben/**)` — `parameter.toml` sits under
`ventures/` but outside `aufgaben/`), and every section *before* the insertion still starts
at its pre-build line (2496, 3096-3298), so no line was added or removed ahead of it.

Cost: whole run ~35 kB of reads — the package, the new section whole (it *is* the product),
five short `parameter.toml` spans, one architect-section span, one `daten.md` span, and six
cheap greps. Never opened `spiel.md` or `technik.md` beyond those spans. Numbers in
`aufgaben/` ran to `0292` tonight (`0292` appeared untracked during my run); I took `0293`.

## 2026-09-10 — 0287 (`daten.md` Nr. 7, Eurostat verdict): geprueft, 2 findings, 1 proposal (0293)

**`befunde/uebersetzung-<date>.md` is the compiler run, not a translation.** It cost me a
~13 kB read for nothing — cmake/ctest output of the whole venture. In this factory
*Uebersetzer* means compiler; when the corpus is mid-turnover to English the word reads the
other way and that is the trap. Language state of a spec: check the file, never a filename.

**How to verify „unchanged" with no `Bash` and therefore no `git diff`.** A dated finding
that quotes the span **verbatim** plus the pruefung that confirmed it verbatim is the
surrogate: `quellenbefund-leitzinspfad-eurostat.md:135-147` quoted `daten.md:195-198` and
`:203-208` on 2026-09-09, `pruefung-0280-…-2026-09-09-2.md:44-45` confirmed them that day,
both are word-for-word what stands today — and because the cited **line numbers still hit
that text**, nothing above `:209` moved either. Cheapest place to look for such a quote:
the report of the package that proposed this one.

**Do not trust the vermerk about language.** `0287`'s vermerk ends „`daten.md` IST EIN
DEUTSCHES DOKUMENT und bleibt es" and quotes the old verdict in German — the file has been
English since at least 2026-09-09 (the proposing finding quotes it in English). Judging the
builder for writing English there would have been a false finding off a stale note.

**Both findings were outside the criterion and both were right to be.** The criterion's own
condition 4 („nothing outside section 7") locked the builder out of the frontmatter figure
his change invalidated (`quellen_brauchbar: 6`). When a criterion fences a consequence out,
the consequence is a proposal, not a `zurueck` — same call as 0281/0289, third time now.

Cost: ~30 kB of reads, of which 13 kB was the uebersetzung mistake. Everything else was
greps plus section 7 whole (43 lines) — never opened `daten.md` (28.5 kB) whole. Numbers in
`aufgaben/` ran to `0292` tonight; I took `0293`.

## 2026-09-09 — 0274 (T7 rule 4 widened): geprueft, 2 findings beyond the criterion, 1 proposal (0289)

**The rule I nearly got wrong, and it is the counterpart of the 0268 lesson.** Rule 4's
widening turns on the phrase „the operand run beside the `*`", and the wording alone does
not bound that run — I had a `zurueck` half-written on it (a run reaching left across
`static_cast<i128>(a) - b * c` would admit `i64 * i64`, which condition 3 forbids). It is
not a finding, because **„operand run" is an implemented term, not one the package
invents**: `multiplikationsriegel.cpp:446-488` (`linker_operand`) walks left over words,
`(…)`/`[…]` groups, `<…>` before a group and `::` and breaks at everything else, so the
`-` ends the run. Before calling a spec rule ambiguous, check whether the tool the
successor extends already defines the term. 0268 was the opposite case — there the latch
did not exist yet, so only the wording could decide.

**Every dated measurement quote goes against the cited report, digit by digit.** Two greps
found both findings: section 35 quotes „84 layout-constant names" while the report it
cites says 85 (84 is the day-older run), and it dates „2026-09-09" on `zustand.hpp:777`,
which is `:797` at HEAD. Neither breaks a condition — 0001 puts precision beyond the five
into a package, and my 0281 lesson holds: the cheapest repair for a two-digit slip is a
sentence in the `abnahme` of a package that opens the file anyway (here `0276`, architect,
`offen`, same lane).

**Cost trap, and it cost me two dead Reads:** `specs/` sits at the **repo root**, but
`kern/`, `werkzeuge/` and `befunde/` sit under `ventures/0016-…/`. Glob the basename once
instead of guessing the prefix.

Numbers in `aufgaben/` ran to `0288` tonight; I took `0289`. Whole run under ~25 kB of
reads: inhalt index, two T7 spans, section 35 whole (it *is* the package's product), three
greps on the corpus, 100 lines of the latch.

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

## 2026-09-09 — 0277 ruecklauf 1: geprueft, 0 findings, 1 proposal (0281)

The repair was one inventory sentence (two places → three, `schritt_probe.cpp:1906`
plus two more prose spots). Judged only that plus a spot-check of the four
conditions already met: one `grep -n feldzahl` over `schritt_probe.cpp` gave
every cited line at once, three reads confirmed the quotes, four cheap probes
re-anchored the rest (`schritt.hpp:369-370`, §28 `:5482-5489`, T61 `:4348-4350`,
`pfadstand`/`schritt::schritt(` counts). Whole run well under 15 kB of reads;
never opened `technik.md` outside section 34.

**The rule I want to keep from this run: widen the grep beyond the file the
inventory names.** `grep 'neun Felder|zehntes Feld'` over `kern/` — not over the
probe — found three more copies of the count, in `schritt.hpp` itself (`:150-152`,
`:205`, the assert message `:272-273`). An inventory of "who carries this number"
is only as good as the directory it was taken over, and both the builder and I
had been reading the probe.

**And the rule about what to do with it: comment drift is a package, not a
ruecklauf.** Nothing there goes red; condition 2 asks for the new numbers in the
section and got them; `0001-entwurf-abnahme` puts precision beyond the five
conditions into a package. Sending back the one spec lane four packages are
locked behind, for three stale comments, would have been the reviewer failure
that package was written against. Wrote `0281` instead — and said in it that the
*preferred* form is one sentence in the successor's `abnahme`, so the PM can
reject the file and lose nothing. Note it cannot be built before the successor:
all three sentences are true today.

Filename trap survived: second finding on the same package needs the new date,
not a `-2` suffix — the first pass was 2026-09-08.

## 2026-09-08 — 0092 (section 18, two counts): geprueft, 0 findings

When a package's acceptance measures against a fact that moved between cut and
build (`grep -c "siebzehn"` was 5 at cut, 0 at build because `0152` fixed the
file in between), the right delivery reports **both states** — historical
enumeration plus a current-state table — and the check is: reproduce the
builder's grep yourself and lay the section against **your** output, not his.
Done here with one case-insensitive alternation grep
(`siebzehn|zweiundzwanzig|dreiundzwanzig`) on `werte.hpp`: union
{2,16,29,32,39,41,147,185}, every line named in section 18's table. Count
condition verified three ways (section 18, T48's sentence at :2093→now :2551,
name-by-name recount of the ten-row table = 22).

Cost: whole run under ~10 kB of reads — inhalt index, section 18 whole
(109 lines, it *is* the package's target), T48 table span (40 lines), three
greps on `werte.hpp`, one `T48 Nr\.` grep confirming declarations 18-22 at
382/406/425/442/478. Never opened technik.md or werte.hpp whole. Two `0092-*`
packages exist (also `0092-linkschalterform-durchgereichtes-l`) — glob the
full slug, not the number.

