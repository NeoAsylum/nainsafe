# Logbuch: entwurf-pruefer

Rotated by the runner on 2026-09-08 at 14889 characters (cap 12,000). Predecessor: `notizen/archiv/entwurf-pruefer-2026-09-08-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-08 — Pruefung 0068 run 1, geprueft, 0 findings

All four conditions verified in place; counts recomputed from `L_R` formulas (23+4=27,
16, tol 2, 31 reported), condition 4's phrase confirmed in-line at :5395 with §29
reconciled verbatim against my 0064 review (+36 uniform shift, no content line added —
the +1 span line is the blank before the new section 30 heading). Wave-2 watch thread
from 0064/0149/0196 entries is **closed**: all markers repaired, section 30 (:5400-5477)
documents them.

Worth keeping:
- **The file is now bilingual in its keywords.** Condition patterns written in German
  (`Leitzins`, `Soll`) miss translated text; sweep both (`policy rate`, `target`). Same
  lesson as number formats.
- **A quote can be genuine and un-greppable:** spiel.md :2818-2820 wraps mid-phrase;
  grep a short fragment before calling a quote fabricated (second time this bit me —
  see 0196 run-2 bold-markup case).
- **Change-record sections quoting struck wording in a "before" column are not
  condition violations** — precedent §29/§30; the record must quarantine itself
  ("outside this section"), and §30 does.
- Post-0068 anchors: row 9 :1945; sentence below list :1957-1963; T37 block
  :2805-2884 (invariant :2811-2826, class table :2836-2843, 16/2 formulas :2847-2852,
  why-sentence :2875-2884); section 17 row-20 sentence :3499; T59 label :3969; §29
  :5309-5399, first clause :5395; §30 :5400-5477. Epoch delta: 0068 build = +36 at §29
  vs my 0064-review anchors.
- Open for the PM, already routed via §30 reports (no duplicate proposal from me):
  §29's **second** check clause self-falsifies like the first did (report 4); check 8
  in section 9 does not yet name the T37 invariant (report 1); reihen.toml
  `[[widerspruch]]` no. 5 can be released (report 2).

## 2026-09-08 — Pruefung 0064 run 1, geprueft, 0 findings

All ten R-places recomputed from R = 20 via the document's own formulas; all closed.
Place 3 (T37, 31→27) was rightly refused by the builder: 31/27 are `L_R(S+5)−n` /
`L_R(S+4)−n` at L_R=4, S=3, n=1 (:1956-1959), not formed from R — my own 2026-09-04
proposal row was stale against 0221. Condition 2 sweep reproduced by grep, condition 3
marking at :3170-3182. Caveat noted (no Befund): §29's check clause ":5359 zero hits for
18.024/87.864" is self-falsified by its own enumeration (3 hits, all inside §29).

Worth keeping:
- **Grep both number formats.** Translated sections write 9,024 / 1,220 (commas),
  untranslated and frontmatter write 9.759.420 (dots). A one-format sweep over this file
  silently misses half the hits; my first two greps each caught a disjoint set.
- **Reviewing a package built from my own proposal:** the target column is just another
  claim. Condition 1's "recompute, don't compare" is what surfaces a proposal gone stale
  under intervening packages (here 0221 changed T37's ground after 2026-09-04).
- Anchors today: T22 :1598-1599; T44 :2656-2658 / :2691-2703 / :2753-2758; T35
  :2770-2771; §10 :2967-3028; §12 depth-2 :3073-3078; protocol marking :3170-3182;
  §29 :5273-5362. Tail: section 28 now ends :5272 (was :5244 after 0149; +28 from 0064's
  in-place additions plus same-day translation, not decomposed).
- 0068 wave-2 markers shifted: now :1652, :2846, ~:3682-3684. Still open; 0064 reports
  name three more 0158-era `R = 24` places (:2518 and two backticked ones) for the PM.

## 2026-09-08 — Pruefung 0149 run 1, geprueft, 0 findings

T56 rewrite verified against all three conditions: both `GEBIET_KUERZEL` locations
named with file+identifier+guard (`:3673-3674`, `:3709-3725`), derived-size assertion
demanded with the why-sentence (`:3727-3735`, greps: `static_assert(GEBIET` = 1 hit,
`std::array<const char` = 0 hits file-wide), old claim caveated as "target, not
today's state" (`:3740-3741`). Source reality confirmed: `zustandsausgabe.cpp:54,60`,
`zustand.cpp:403`. Cheap run: ~7 greps, 2 section reads.

Worth keeping:
- **Diff-conditions without git: reconcile my own prior anchors.** Condition 3 ("no
  lines changed outside T56") verified via the six line anchors recorded in tonight's
  0158 run-2 entry: 0 shift above T56 (`:2477`, `:2489`, `:2516`, `:2524`), uniform
  +28 below (`:4964→:4992`, `:5212-5214→:5240-5242`). Record absolute anchors with
  exact wording in every review — they are the next review's free diff baseline.
- **My logbook entries are NOT in epoch order.** The 0196 run-2 anchors (`:4016`,
  `:5108`) predate the 0158 build although the entry sits above it; mixing epochs gave
  a phantom -4 discrepancy until the chain 5108+47(0158 build)+28(0149)=5183 closed.
  Before reconciling, establish which build epoch an anchor was measured in.
- Epoch deltas for future reconciliation: 0158 build = +47 below section 9, 0149 =
  +28 below T56 (3661-3746). Current tail: section 28 ends `:5244`.
- Sampling limit stated in the finding: a compensating add/remove pair between `:3746`
  and `:4964` is invisible — no anchor exists in that span. If a package ever edits
  sections 20-24, take anchors there first.
- Still watching: 0068 wave-2 markers at :1649, :2786-2788, :3603 — all above T56's
  start (3661), so unshifted by 0149.

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

