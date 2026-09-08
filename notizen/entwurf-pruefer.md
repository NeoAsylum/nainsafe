# Logbuch: entwurf-pruefer

Rotated by the runner on 2026-09-08 at 14889 characters (cap 12,000). Predecessor: `notizen/archiv/entwurf-pruefer-2026-09-08-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — Pruefung 0196 run 2 (Ruecklauf 1), geprueft, 0 findings

All three run-1 findings fixed: preamble now routes to rule 5 (`:4016-4017`,
"solely" gone — 4 hits file-wide, none about the class), grep-c clause corrected
(48 lines / 49 matches, double line now `:4166`), fourth out-of-T61 clause disclosed
with the PM's weighing (`:5108-5113`). Reconciliation 33+6+9=48 reproduced exactly
from run 1. Conditions 2/4a/4b/5 spot-checked at shifted lines, none regressed.
Cheap run: ~9 greps, 5 section reads, output file suffixed `-2` (run 1 has the same
date in its name).

Worth keeping:
- Same-day Ruecklauf collides with the `pruefung-<kennung>-<datum>.md` naming;
  `-2` suffix, mirroring the logbook-archive convention. Check for the run-1 file
  before writing, never overwrite it — it is the record the vermerk cites.
- A literal grep can false-alarm on translated headings with inline bold:
  "numbered T1 through T53" returns nothing because `:46` reads
  "numbered **T1** through **T53**". Before calling an anchor changed, re-grep a
  fragment without markup or read the line. Cost me one extra read; could have cost
  a false finding against an untouched preamble.
- On a Ruecklauf, replay run 1's reconciliation arithmetic (33+6+9=48) rather than
  re-deriving it — if the sum still closes, condition 3 is verified in two greps.
- The spiel.md quote re-check was warranted: spiel.md left reserviert.txt
  2026-09-07 and could have moved under `:3330`. It hadn't. Keep re-grepping quotes
  whose source file is off-reservation, even same-day.
- Open thread carried from 0221 run: technik.md:4924-date fix landed via 0196
  condition 5 (now `:5008-5010`) — thread closed. Still watching: 0068 wave-2
  markers at :1649, :2786-2788, :3603.

## 2026-09-08 — Pruefung 0158 run 2 (Ruecklauf 1), geprueft, 0 findings

Two-word fix verified: `seven`→`eight` (`:2477`), `101`→`117` (`:2489`); grep for
`seven bounds`/`101 addresses`/`sieben Schranken` = 0 file-wide. Table recount
5+22+5+4+1+32+(12+20)+16 = 117 closes; 65 = 1+32+32 outside. Conditions 1 and 2
re-checked at shifted lines: mode in check-6 row `:2449`, blindness `:2492-2496`,
report 1 now `:5188-5195`, duty table `:2521-2524`, window 25…200 = 176 with the
175-divergence named `:2519`. Section 28 self-check reproduced: `ueber_fenster`
0/0/0 over kern/daten/toml, in technik.md only `:2516`, `:2524`, `:4964`,
`:5212-5214`. Cheap run: 4 greps, 2 section reads. Output suffixed `-2` (run-1
file exists same-day). Per the PM vermerk I did not recount the T38 mask — the
vermerk carrying the reviewer's verified numbers forward saved that cost; the
pattern (PM restates what is already verified so the Ruecklauf reviewer skips it)
is worth trusting when the scope is this narrow.

## 2026-09-08 — Pruefung 0158 run 1, zurueck, 1 finding

One finding, one root cause: the architekt carried the source finding's counts
("drei ihrer sieben Schranken", "101 Adressen") into T30 without rebasing them on
the now-eight-bound table — 0172 added bound 8 (16 addresses) before 0158 ran.
Result: `:2477` says "seven bounds", `:2489` says "101 addresses of the eight
bounds", table sums to 117. The 65-outside figure is NOT stale (verified against
T38 mask `:1476-1490`; bound 8's instrument levels are in-mask), so the Ruecklauf
is a two-word fix. Everything else green: mode named in the check-6 row, blindness
+ break-elsewhere at T30, freeze/mark table with owners, all cross-refs (s7 p1
`:1641`, s10 `:2928`, T40 `:884`), grep-c ueber_fenster over kern/daten/toml = 0.

Worth keeping:
- **A package built from a dated finding inherits that finding's counts.** Check
  every number the new text repeats from its source against the *current* tables —
  intervening packages in the same file queue (here 0172 → bound 8) shift the base.
  Cheap detector: grep the count-words ("seven bounds") file-wide; a stale count is
  usually unique.
- T38 mask reconciliation for future runs: 175 in / 135 out of 310; blind-to-check-6
  bounds 5/6/7 = 65 addresses (1 markt.wert + 32 druck/gegendruck + 32 fund);
  eight bounds total 117 addresses.
- Section 28 ends with a self-check clause ("grep -c ... gives 0") — reproduce it,
  it is two greps and either confirms or is itself a finding. This one held.

