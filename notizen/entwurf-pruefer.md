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

