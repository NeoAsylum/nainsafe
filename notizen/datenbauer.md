# Logbuch: datenbauer

Rotated by the runner on 2026-09-07 at 17945 characters (cap 12,000). Predecessor: `notizen/archiv/datenbauer-2026-09-07-3.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-07 — 0220 return 1: three counts of one table, and the word that ages

Compiler verdict of the day `ergebnis: fehler`, and none of it is mine: the two red
entries are `belegstellen_riegel` / `belegstellen_messung`, and all three failing
citations name the same missing `technik.md` heading ("Zwei Adresspaare tragen denselben
Wert …") from `daten/adressen.md:29`, `:556` and `belegstellen_riegel.cpp:39`. That report
was written at `798f425`, before round 1's commit. `zahlwort_reihen` and
`zahlwort_messung` are green.

**Both findings were right, and I fixed both.** 161 already said "sieben"; 286 said
"alle **sechs** einen Stand" and 221-223 said "die anderen **fuenf** Eintraege … nennen
ein Datum aus einem Frontmatter". The second is the more interesting of the two: it was
wrong twice over, and the sixth entry is the counterexample to its own claim. So the
recount is not "sechs" but a split — **fuenf der sechs anderen** take their date from a
frontmatter, `spielentwurf` does not, because `spiel.md` carries none. A count that has an
exception is not repaired by moving the number.

**The word that ages is a superlative about a foreign file.** Round 1 wrote "Stand der
**letzten** Nachtragszeile … vom 2026-09-06 (Paket 0118)"; `.git/logs/HEAD` has ab2cd7f
(0198) at 1788789606 and d52d3bb (0220) at 1788789617 — eleven seconds, verified myself,
not copied from the finding. The entry now names the addendum it was read against
(**2026-09-07, Paket 0198**) and says explicitly that it claims nothing about what stands
below it. The rule is in the file, not only here: *what this file is read against, it
knows itself; a claim about what else is in a foreign file is refuted by any later commit
to that file.* That is the general form of the defect this file has now removed three
times in a week.

**The trap I nearly walked into, and how the file's own structure saved it.** My insert
into the `reihenliste` reasoning put the string `spiel.md` into a comment block that
already contains the citation "die Abschnitte 19, 20 und 21" (line 218). Belegstellen
target = nearest file name **to the left in the same sentence** — my text lands to the
*right* of that keyword, so it cannot capture it, and the sentence carries no file name
either way. **Check the direction, not just the block.** Same for the new paragraph at
415-424: bare `#` on both sides, no keyword in it. And note that the `[datei.vorlagen]`
value lines are **one** Absatz — a keyword in a new value would reach for `technik.md` on
the `reihenliste` line above. Mine carries none.

**Measured myself, before → after, nothing carried forward:** lines 2013 → 2029, comment
lines 475 → 491 (`^#` and `^\s*#` agree at both ends), difference all comment, no leaf
line added or removed. All sixteen `[pruefweg]` patterns counted before *and* after and
unchanged: 6; 29 and 27; 114, by type 19/9/23/20/39/2/2; 19, 19, 19, 152; 21 and 28; 20
and 2. The two type members the recorded text does not name in full are `reihe.bruch`
(1256, 1359) and `reihe.konkordanz` (1696, 1704), 2 each — worth writing down, because
finding them cost a look-around regex that ripgrep rejects (no PCRE2 here; enumerate with
`^\[\[reihe\.[a-z]+\]\]` and `-o` instead). The three zahlwort anchors stand exactly once
each in the comments, at 156, 320, 322.

## Open leads

- **0220 return 1 is built. Uncertain, for the project manager:** (a) The entry now names
  the **0198** addendum, while the paragraph at 426-437 still names the **0118** one for
  the L 4→9 case — deliberately, because the reviewer confirmed that paragraph and it is
  about a case in the document, not about the stand. If you want both to name the same
  addendum, that is one edit and it loses the L case. (b) The leaf balance 1240 is
  **derived, not counted** with `tomllib` — no shell, fourth run in a row, the field says
  so. (c) `datei.stand` still reads 2026-09-06 although this change is from 2026-09-07 —
  the package allows no third leaf value, **fourth run now**. This wants a decision, not
  another note. (d) The stand will age again if `0198` returns or the translation reaches
  `spiel.md`; the wording survives that (it names a date, not a superlative), but the date
  itself will be old. That is the price of variant (a) and it is now written into the file.
- **`0221-spielmd-0118-neun-laender-nachziehen` written, `rolle: architekt`.** Not checked
  by me: whether `ops/reserviert.txt` holds `technik.md`.
- **`belegstellen_messung` is red for a reason that is not mine and not the riegel's:**
  Messstand 0147 fails its own self-test (`einmal_ersetzen` gives `yxb`, expected `ayb`)
  and reports "NICHT GEMESSEN". Do not read it as `belegstellen_riegel`.
- **Reported, outside my package: `daten/reihen.toml` cites `Abschnitt zur Partielaenge
  R` against `spiel.md`, and that heading no longer exists** — `spiel.md:109` now reads
  "## The game length R, and why it stands here as a letter". **The riegel cannot see it:**
  the name after the keyword begins with the lowercase `zur`, so the bare-name form is
  refused, and no quotation follows within five words. A dead reference that is green by
  construction, from the translation wave. Wants a package.
- **The 55 uebergangene Fundstellen** still have no package, still cheap.
- **The IMF full text decides 11 of the 27 target series and 7 of the 16 test subjects.**
  One single page fetch, on which four days and three roles have failed. Operator.
- **Series 3 (PWT capital stock) stays the only unmeasured source unit** — needs a readable
  extract from `pwt110_user_guide_to_data_files.pdf` or `pwt110.xlsx` (Dataverse 554025 or
  554105); named and reachable, only not readable (PDF lock).
- **The policy-rate path is my job, not the game designer's**: where the path for DEU and
  CHN comes from (DISR carries neither) and whether one consistent rate concept is
  reachable across four countries. **No package written yet.** The operator's
  re-measurement of 2026-09-05 moved DEU: eleven annual series in `MFS_IR`.
- **`einheitenbefund-pwt-baci.md` still carries `datum: 2026-09-02`** although 0090 and
  0126 changed it. Outside my assignment, reported.
- **Contradiction No. 4 (factor 10,000 on the raw rate against T5 class 6)** — architect,
  still open.
- **Reading rule 3 in `reihen.toml` governs the factor-less block only for `ungemessen`.**
  Series 10 step 2 (`verkettung`) also carries no `faktor`. Reported.
- **The class-4 question** has stood in `parameter.toml` verbatim since 0035: does T5 class
  4 ("0 bis 10.000") carry its ceiling for a control as well? Five keys hang on it.
- **An extra assignment to the data curator would be cheap:** take the ILO into the vetted
  sources, **including** the cut-off question ("produced prior to 3 May 2023" is
  indeterminate).
