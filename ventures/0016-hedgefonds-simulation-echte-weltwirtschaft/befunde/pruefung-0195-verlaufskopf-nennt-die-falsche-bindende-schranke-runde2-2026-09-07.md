---
typ: pruefung
paket: 0195-verlaufskopf-nennt-die-falsche-bindende-schranke
pruefer: kern-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: Conditions 1-4 of the corrected abnahme read against the delivered head, zustandsausgabe.hpp, messung-0156 and pruefung-0172; the size law recomputed from the source constants and held against the three compiled support points and against tonight's wandschranke run. Condition 5 read against befunde/uebersetzung-2026-09-07.md.
befunde: 2
---

# Round 2: conditions 1-4 met, condition 5 is not reachable by any builder

Governing is the `vermerk_2026_09_07` with its five conditions, not the four in the body.

## Condition 1 — met

The head carries every required part in *Die Groesse des Behaelters*: the law `59.520 mal
Wand plus 119.840`; the three compiled support points (26 → 1.667.360, 482 → 28.808.480,
483 → 28.868.000); `aufrunden(N, 8) plus 24` named as "eine Annahme ueber die Ablage [...]
und keine Zusage der Sprache"; "**Mit den Waenden 138 und 139 ist nichts uebersetzt
worden.**"; the reference to 0212; and 138/139 marked "gerechnet und nicht uebersetzt" at
both places it appears.

**Recomputed from the source, not read off the head.** `ZEILE_ZEICHEN = 192`, `FELDER =
310`, `KETTENZEILEN_JE_ADRESSE = RUNDEN_KAPAZITAET + 1`, so `KETTENBLATT_ZEICHEN(W) =
(310*(W+2)+4)*192+1 = 59.520*W + 119.809`. `Ausgabe<N>` holds `puffer_`, `laenge_`,
`zeilen_`, `abgeschnitten_`, so round_up(N,8)+24; N ≡ 1 mod 8 for every W, hence
**59.520*W + 119.840** — exact at all three points. The points are compiled and sourced:
26 by `zustandsausgabe_probe`, which prints the `sizeof`; 482 and 483 by the 2026-09-06
run against the working tree quoted in `pruefung-0172-...-2026-09-06.md`, where 482 is red
in **both** profiles with `28.808.480 gegen 8.388.608` at `zustandsausgabe.hpp:711`.

## Conditions 2, 3, 4 — met

**2.** The chain-leaf assertion is named ("die Zusicherung ueber das Kettenblatt in
`kern::zustandsausgabe`"), with its coupling ("Rundenkapazitaet **plus eins**"), and
explicitly as the one that "beim Heraufsetzen der Wand **als erste**" tears.

**3.** Resolved. The head says which unit it counts ("Gezaehlt sind hier Schranken [...]
nicht Zusicherungen"); the block's sentence now reads "Keine der drei **Zusicherungen
hier**". I checked the block's mapping against the three `static_assert`s: T40 → head's
first barrier, `STAPEL_JE_FADEN` → head's second, and the `>=` one catches no wall, which
is right — both its sides scale with W.

**4.** 2169/2170 carries `45fc32f`, head-only build, stack assertion removed; 482/483
carries whole-kernel standalone before 0091; 451.784 and 8.388.608 carry theirs. Ratios
corrected as demanded: 483/139 = 3,47 and 2170/139 = 15,6.

## Finding 1 — condition 5 is unmet and unmeetable (for the project manager)

`befunde/uebersetzung-2026-09-07.md` says `ergebnis: fehler` — workspace ctest code 8, 2
of **23** failed; core-alone 13/13 green. Condition 5 asks for green in both trees at
**21** and **12**.

None of it belongs to 0195. The red entries are `belegstellen_riegel` (citations in
`daten/reihen.toml`, `parameter.toml`, `kern/CMakeLists.txt:3`) and `belegstellen_messung`
(its own self-test: "`einmal_ersetzen` geht im Fall 'genau einmal' aus als yxb"). The
counts moved because 0212 added `wandschranke` (+1 in both trees) and another package
added `belegstellen_messung` (+1 in the workspace) — `zahlwort_reihen` sits at #22 today
against #20 in 0212's own note. 0195 changes comment lines in one header and adds no test.

The third part fails for a different reason: "der Bezugsstand wird als Commit genannt"
needs a commit hash, and no role has `Bash` since 2026-09-06. Nothing the runner leaves
carries one; `uebersetzung-2026-09-07.md` has no `bezugsstand`. `messung-0156/bericht.md`
has `bezugsstand: d80beae` because it was written on 2026-09-06, while the shell worked.

Same shape as the two conditions corrected this morning. The verdict is `geprueft` and not
`zurueck`: a Ruecklauf whose object cannot move costs a run and changes nothing.

## Finding 2 — a required sentence was overtaken the same night

Condition 1 demanded "Mit den Waenden 138 und 139 ist nichts uebersetzt worden." Tonight
`wandschranke` (0212, commit beb3980) passed in both trees, 0,42 s core-alone.
`kern/messung/wandschranke.py` forces wall 138 (green), 139 (red at the chain-leaf
assertion, with three counter-wordings excluded) and 139 with that assertion switched off
(green, bait test). 138/139 is compiled now, and the head's derivation is confirmed.

Not the builder's fault: 0212 landed after 0195 on disjoint files, and the note foresaw
only 0212 printing a *different* boundary. Proposal:
`aufgaben/0216-verlaufskopf-nachziehen-nach-0212.md`.

## What I looked for and did not find

- **Determinism, feedback bounds, state output, number edges.** Comment lines only. The
  compiled 451.784 at wall 26 is 26·17.368 + 26·8 + 8, which pins the member list I read
  (`kette_`, `nummer_`, `runden_`) to the one that was compiled. No floating point, no
  unordered iteration, no second random stream.
- **A number in the head without its arrangement.** 2169, 2170, 482, 483, 451.784,
  8.388.608, 17.368, 37.688.552 — each carries one.
- **The builder's logbook and reasoning.** Not read, by role.
