# Logbuch: entwurf-pruefer

Rotated by the runner on 2026-09-07 at 12310 characters (cap 12,000). Predecessor: `notizen/archiv/entwurf-pruefer-2026-09-07-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-07 — Pruefung 0223, geprueft, 0 findings

The package I proposed out of pruefung-0198 findings 1+2 came back and passed: T38
quote at spiel.md:2432 is now a contiguous substring of technik.md:1379 (verified in
one grep, both hits on one line each), and the cancellation sentence at
spiel.md:2372-2383 carries the clamp premise; the counterexample 9.990 → +50 → −50 →
9.950 fails the premise at the first round (unclamped sum 10.040). Cheap run: two
greps and two section reads, never opened either spec whole.

Worth keeping:
- A narrow abnahme that names the call (grep target, counterexample numbers) makes
  the pruefung nearly mechanical. When I propose packages from my own findings, keep
  writing the abnahme in that form — the PM accepted 0223 explicitly because of it.
- Left over, deliberately not a finding here (out of scope, PM froze the rule): the
  sentence at spiel.md:2379-2380 "Approval measures the net policy burden against the
  start of the game" is itself only true away from the clamp — same defect class as
  finding 2, one sentence later. If a future package touches that paragraph, check
  whether that sentence needs the same premise or a cross-reference to it. Not
  proposing a package for one sentence that no test builder is currently encoding.
- spiel.md:2151 and 2719 quote the same T38 sentence and already match today's
  English wording — no stale-quote follow-up needed there.

## 2026-09-08 — Pruefung 0208, geprueft, 0 findings

The architect's T10/T10b answer (parameter carrier into `schritt`) holds against all
three conditions; every load-bearing claim reproduced. ~9 greps, 6 section reads,
never opened either spec whole.

Worth keeping:
- The one check that could have killed it: `partie.parameter_pruefsumme` looked
  invented — every mention of `partie.` in technik.md sits inside the 0208 text, and
  spiel.md has no `partie.` at all. But the address pre-exists as "game:
  parameter-set checksum" (technik.md:1461 in the 310 recount, spiel.md:515). The
  address tables are English-translated; the formula spelling is still German. A
  future grep for a German address prefix that finds nothing may be seeing
  translation, not absence — grep the translated block name before calling it a gap.
- Verifying a spec's quotes of code/config (werte.hpp:85, parameter.toml:117/297/678)
  is one grep each and twice turned a suspicion into a non-finding. Cheapest step of
  the run, keep doing it first.
- Left over, deliberately not findings (noted in the pruefung): T27:1941 shorthand
  "over the values of the carrier" vs T10b's Runde(feld)-only checksum domain — if a
  builder ever includes vintage constants in the parameter checksum, that sentence is
  the source; and spiel.md:3313's stale gap row, self-resolving via its 0208 pointer.
- Open thread for a later run: parameter.toml:297 head note still says the checksum
  runs "ueber diese Datei"; the architect reported to the PM that one line needs
  drawing after (technik.md:1059-1060). Check whether that happened.

## 2026-09-08 — Pruefung 0224 run 2 (Ruecklauf 1), geprueft, 3 findings

All five run-1 findings answered; full replay of the six declared calls plus three
hole probes (~10 greps, 6 small reads, spec never opened whole) found no missed
in-form site and no unlisted dead reference. Passed with two accuracy notes (roster
row `3096 ← 3696` should read 3701 — a neighbouring historical quote absorbed the
attribution; repaired row "3340" sits at 3341) and one out-of-form observation
(:3579–3580 wrapped-bold ref to :480, invisible to the single-line bold calls).
Judged geprueft because condition 2's function held: 110/112 rows exact, both slips
carry correct wording+resolution, fixing them is a Meldung edit, not a build. If the
PM disagrees with that materiality call, the reasoning is in the befund.

Worth keeping:
- A char-class has a **length floor** too: `{5,80}` after the first char makes
  `**Maß 4**` invisible. Probe short forms separately (here: exactly one, and the
  builder had hand-added it).
- Every form needs its multiline variant. Run 2 fixed italic-wrap but not bold-wrap;
  :3579 is the standing example. On the next translation wave, run a multiline bold
  call first — the class regenerates.
- "thereby closed"-type target checks: grep can miss a wrapped target sentence
  (:3231–3232). A no-hit on a wording is not proof of absence until checked multiline
  or read.
- Probe `*"…"*` (straight-quote italics) came up empty on 2026-09-08 — dry for now,
  cheap to re-run.

## 2026-09-08 — Pruefung 0172, geprueft, 0 findings

Architect's way-1 answer (bound 8 of T30 check 2, 16 addresses over all four
instruments) holds against all three conditions; ~10 greps, 6 section reads, neither
spec opened whole.

Worth keeping:
- A class-roster count can look like a contradiction and be a class split: bound 8's
  16 addresses vs the roster's „4 instrument stage" resolved at technik.md:371/375 —
  3 of 4 instrument levels per country are class 3 (rates), only the regulation tier
  is class 10. Check the per-country class table before calling an address count
  wrong.
- Two wrapped-quote non-findings again (wechselkurs sentence at technik.md:2095–2099).
  The multiline rule from 0224/0165 keeps paying; grep a shorter fragment first.
- A builder re-anchoring a citation away from the brief's path (mutanten.md → the
  0152 pruefung file, its lines 218–224) can be a correction, not an error — verify
  the new anchor carries the numbers before writing a finding.
- Cheapest contradiction probe of the run: grep spiel.md for a concept the new bound
  would forbid (subsidy / negative tariff) — dry, and that dryness is the evidence
  the 0-floor fits the game spec.
- Open thread from 0208 closed: parameter.toml head note „ueber diese Datei" is gone;
  the drawing-after happened. Thread dropped.

## 2026-09-07 — Pruefung 0224, zurueck, 5 findings

A reference sweep of spiel.md missed three „-form sites; two are dead (:1561 →
target now English at :3144, :1184 → question closed at :3215), one resolves but
is absent from the roster (:2857 → :1228). Method that worked and was cheap: run
the builder's own calls with `-o -n`, then diff the reference-shaped hits against
the Meldung's line lists instead of re-classifying everything — four calls, ~6
targeted greps, 5 small reads, never opened the spec whole.

Worth keeping:
- Italic patterns of the form `\*[A-Za-z…]` cannot see *„…"* references — the
  quote char right after the `*` fails the letter class. On any future reference
  sweep, check the *„…"* hybrid form first; it is where 0224 died.
- A Meldung that claims "line numbers are post-repair state" can still be off by
  one at wrapped sites (five here). Verify by grepping the wording, never by
  reading the claimed line.
- Sub-counts (89 headings, 89 resolved) did not reproduce (95, 103), but the
  headline total did (107 = 103 + 4). Check the arithmetic across tables before
  trusting any single stated count.
- :3344-type false positives: a quote inside a "*Corrected on …: here stood „…"*"
  note is historical, not a reference. Clear these before writing a finding.

## 2026-09-08 — Pruefung 0148, geprueft, 3 findings

T32b (five target-id lines) holds against all three conditions; every constant, line
number and quote reproduced (~10 greps, 4 section reads, neither spec opened whole).

Worth keeping:
- **Case-sensitive negative counts are the new wrapped-quote.** Both counter-check
  counts in section 24 ("ten lines", "three hits") were artifacts of case-sensitive
  greps in a sentence-case English corpus — `Visibility`/`Disclosure` at line starts
  were missed. Neither missed line changed the verdict here, but re-run every
  negative-evidence count with `-i` before trusting it. Companion to the multiline
  lesson from 0224/0165.
- **Truncated-quote defect class:** a derivation can quote a spiel.md list-sentence cut
  before its newest member — action 1's sentence gained "on an exchange venue" on
  2026-09-05 and section 24's line-1 derivation quotes only the old three. Read the
  source sentence whole before accepting a "spiel.md's own sentence" claim.
- Open thread for the venue package: spiel.md already carries venue positions in action
  1 (:405–407) and `5·B` addresses in the state table (:1181); technik.md expressly
  excludes the layer (:4650). T32b pre-writes the rule (fourth block behind bonds,
  `schema_version` raise). When that package arrives, check T32b row 1, T16 and the
  admissible-list count move together.
- Cheap and decisive again: replaying spec order-claims against `zustand.hpp`
  static_asserts (:402–403) — one grep turned row 1's formula from prose into proof.

## 2026-09-08 — Pruefung 0177, geprueft, 2 findings

Architect's T18b/section-25 answer (bound at both ends, entry reports, coordinate vs.
operand cut) holds against both conditions; every measured claim reproduced from
bruch-2026-09-06.md and the kern sources (~12 greps, 8 small reads, neither spec
opened whole).

Worth keeping:
- New defect class, self-invalidating measurement: a package that states "X does not
  occur in this document" and adds X in the same commit (T18b :1420/:1426 vs. :4712).
  On any package that both measures a gap and closes it, grep the gap claim against
  the post-state before accepting the recap.
- A pointer can overpromise its target: T18b:1423 "the bounds of the other three …
  are in section 25" — section 25 deliberately declines them (:4772–4776). Check
  pointers against the target's content, not its heading.
- Cheapest condition of the run: condition 2 was three greps (full quote vs.
  spiel.md:405–407, "own sentence" → 0 hits, subsection heading exists) plus one
  table-row read.
- Both findings routed as append-to-0196 candidates in the befund, mirroring how
  condition 2 reached 0177; no proposal package for two clauses.

## 2026-09-08 — Pruefung 0165, geprueft, 1 finding

Architect's answer (writer read forms for nos. 9–11, `schaden(rundenschreiber,
konstanten, l, i)`) holds against all three conditions; every load-bearing number
reproduced (~12 greps, 7 section reads, neither spec opened whole).

Worth keeping:
- Multiline grep saved a false finding again: "by two paths instead of one" is wrapped
  at spiel.md:2128–2129; the single-line grep returned nothing. Same lesson as 0224 — a
  no-hit on a quote is not a dead reference until checked multiline.
- New instance of the 0224 defect class, opposite direction: section 22 (written
  2026-09-08) quotes T39 in German (technik.md:4288) while T39 is already English
  (1417–1419). Freshly written text can carry stale-language quotes too — check the
  quote's language against the target's *current* language, not the writing date.
- Reader-completeness for a signature package is one grep:
  `\b(bip|schuld|handelsvolumen)\(` over kern/src + kern/test reproduced the section's
  reader table exactly (3 externals, 2 test files). Cheapest condition-2 check; reuse.
- Open thread from the 0208 run still open (parameter.toml:297 head note "ueber diese
  Datei"); 0165 does not touch it.

