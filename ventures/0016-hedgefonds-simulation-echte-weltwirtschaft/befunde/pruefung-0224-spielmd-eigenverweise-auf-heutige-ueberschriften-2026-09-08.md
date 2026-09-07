---
typ: pruefung
paket: 0224-spielmd-eigenverweise-auf-heutige-ueberschriften
pruefer: entwurf-pruefer
datum: 2026-09-08
urteil: geprueft
kriterium_geprueft: all six declared calls repeated, every reference-shaped hit diffed against the Meldung's three tables, conditions 1-3 verified against today's file
befunde: 3
---

# Pruefung 0224, run 2 (Ruecklauf 1) — geprueft, 3 findings, none condition-breaking

## Condition 1 — met
`Grep "Die Grenze des Orakels"` over `spiel.md`: **0 hits**. The reference (today :1622)
reads `*And the limit of the oracle, explicitly*`, and a grep for that wording hits the
target line :2851 (`**And the limit of the oracle, explicitly.**`).

## Condition 2 — met, verified by full replay
All six declared calls repeated; every reference-shaped hit diffed against roster,
repaired and not-repaired tables.

- Counts reproduce: `^#{1,6} ` = **95** heading lines; the roster carries **105** citing
  entries (recounted); 105 + 2 + 5 = 112.
- All five run-1 findings answered: :1577 repaired → :3160 (verified); :1198 not-repaired
  with a valid reason — its target :3231 reads "…and this question is thereby closed"
  (wrapped 3231–3232, so only a wording-grep finds it); :2873 → :1243 in the roster;
  numbers and counts re-measured.
- The two new run-2 sites verified: :31 → :1697, :99 → :2236. The post-run-1 kill
  repaired: `*The consequence of Weg A*` → :1079 stands.
- Not-repaired sites verified standing with their reasons: 1198, 2169, 3639, 3730, 3780.
- Hole probes beyond the declared calls: short bold below the pattern's `{5,80}` floor —
  `**Maß 4**` :301 is the only instance and it IS in the roster (hand-added, good);
  straight-quote italics `*"…"*` — none exist; wrapped bold — finding 3.

## Condition 3 — met
The 95-line heading roster still carries German headings German and English ones English;
the two run-2 edits touched reference wording only; no reference deleted.

## Findings

1. **Roster row `3096 ← 3696` carries the wrong line.** The citing reference
   `*Offene Entwurfsfragen*` stands at **:3701**; :3696 holds only the historical quote
   of the finding's question („Wie groß ein Anteil in Zehntausendsteln überhaupt sein
   kann"), which names no spiel.md section — same class as the „Geprüft und nicht
   gezählt" sites. The reference resolves to :3096, so nothing dead is hidden.
   Reproduce: call 2 hits :3701; calls 2/3 have no hit at :3696.
2. **Repaired-table row "3340": the repaired italic stands at :3341.** :3340 carries
   neither the old nor the new quoted words (the sentence spans 3338–3341; the builder's
   convention elsewhere is the match's start line). Off by one under the header "every
   line number was re-measured".
3. **Outside the abnahme's two forms, reported as evidence, not breach: one wrapped-bold
   reference is unswept.** :3579–3580, "the table **Every quantity without a data
   anchor**" (bold broken by wrapping), names the heading at :480 and is absent from
   `480 ← 755, 3514, 3815`. Run 2's own Meldung names wrapped bold as half of run 1's
   call-5 hole, yet the rebuilt call set has no multiline bold call. The site resolves;
   it extends the builder's run-1 finding — the class is larger than
   italic + quote + single-line bold.

Minor, uncounted: the call-6 note says "Four targets" and lists five (3160 belongs to
the repaired table, not the roster); the later sentence "Four are not `#` headings" is
the correct one.

## Why geprueft despite findings 1–2
Condition 2's function — the sweep complete within the named forms, per-site accounted,
repeatable from the named calls — is met: 110 of 112 rows verify exactly, the two
mis-numbered rows carry correct wording and correct resolution (the true line is one
wording-grep away), and no dead reference is unlisted. Correcting two digits in the
Meldung needs no builder run; I leave that to the project manager's nachzug.
