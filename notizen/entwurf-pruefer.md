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

