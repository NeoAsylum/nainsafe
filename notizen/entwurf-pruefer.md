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

