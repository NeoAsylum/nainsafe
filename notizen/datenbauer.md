# Logbuch: datenbauer

Rotated by the runner on 2026-09-07 at 13257 characters (cap 12,000). Predecessor: `notizen/archiv/datenbauer-2026-09-07-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

## 2026-09-07 — 0185 return pass 2: read the riegel's source before reasoning about its numbers

Reference state `c131477`, `daten/reihen.toml` clean against it. Compiler verdict of the
day `ergebnis: fehler` — the two Leitzins citations were condition 4 and are exactly what
I was sent to fix.

**`Absaetze` is not a keyword of the Belegstellenriegel, and I nearly built a whole plan
on the belief that it is.** The keywords are the literal stems `Abschnitt`, `Absatz`,
`Ueberschrift`; the ae-plural `Absaetze` matches none of them. Measured: the grep
`Abschnitt|Absatz|Ueberschrift` over the file returns 102 hits and **line 194 is not among
them**, although it reads "Die Absaetze zum Eintrag ...". My logbook's own line — "the word
boundary is checked only on the left, so `Abschnitte` counts" — is about a *suffix*, and I
read it as covering an *umlaut plural*. It does not.

**The rule that made the rest cheap, from `belegstellen_riegel.cpp` and not from
guessing:** three citation forms are tried in order (`waehle_zitatform`). The bare-name
form needs an uppercase letter or a digit right after the keyword (`ist_namensanfang`),
the name ends at the next `,;:()[]"'` + backtick + `!?|\` or at a period followed by
blank (`ist_namensende`), never leaves its own line, and is capped at 200 characters
(`UEBERSCHRIFT_HOECHSTENS`). The third form looks for a quotation **one to five words**
past the keyword. **Consequence for anyone rewriting a sentence in this file: everything
from the sixth word after a keyword onward is invisible to the riegel.** That is why I
could rewrite the tail of the pointer sentence at 193-194 without touching a riegel
number — the words `zum Eintrag reihenliste weiter unten` are the whole window and stayed
character-identical.

**Normalisation, both sides: a trailing period, colon, comma or semicolon falls away;
case does not.** So a citation may drop the period of a bold lead-in, and must not drop a
capital.

- **Condition 3 (the pointer to the vanished counting):** rewritten, not deleted — "zaehlen
  diese beiden Mengen nicht mehr auf; der Grund steht dort." Deleting was allowed too, but
  the reader who arrives from the 0142 check file, which still quotes the counting, needs
  the bridge to the "Geschichte mit Datum" paragraph 40 lines below. Two comment lines
  replaced by two, so no count moves.
- **Condition 4 (the two Leitzins citations):** the target is `spiel.md`, and the
  translation run made its bold lead-in English. Both citations now read `Absatz The policy
  rate has not been a target series since 2026-09-03`. **Quoting is not translating** —
  the wording follows the target, so an English target gets an English quote inside a
  German sentence. The German quote was the correct one until today; that is the whole
  point of the recurring half in ops/plan.md.

**Three numbers held, measured before and after in the same session:** 1962 lines, 426
comment lines (`^#` and `^\s*#` agree), 102 riegel keywords as 78 + 17 + 7 at the same
positions in the same order. Nothing was added or removed: two comment lines replaced by
two, two word swaps inside existing strings, one append to a field that is a single line.

**Beware `-o` in `output_mode: count`.** It counted 60 where the same pattern in content
mode gives 102 — count mode counts *lines* even with `-o`. My predecessor wrote that line
down and I still walked into it once this run. Count occurrences in content mode with
`head_limit: 0`.

**Writing a number about the keywords into the file would raise it.** The field names 102
and deliberately not the three words behind the split; the split lives here instead.

## 2026-09-07 — 0217: chose (a), and the measurement that decided it

Compiler verdict of the day `ergebnis: ok`, 23/23 tests — `belegstellen_riegel` and
`belegstellen_messung` are both green again, so yesterday's two red entries are gone.

**Chose (a), and a number I measured decided it, not the one in the finding.** The probe
`\bT[0-9]+` gives 21 distinct tables: 20 cited below the head, plus **T46, which appears
nowhere in this file except in the head list itself**. The list is therefore not a stale
index of cited tables but a record of what 0009 drew on — one of its twelve entries has no
citation to be an index *of*. (b) would have had to drop T46 to stay honest, (c) would
have deleted the only trace of it.

**What I kept out of the file: the T46 sentence.** The moment a later package cites T46, a
head saying "T46 comes nowhere else" is false — 0203's disease in a new costume, a
statement someone must maintain. The head gets the rule, the logbook the measurement.

**The trap here, for whoever edits a comment in this file next.** The `PLATZHALTER`/`FEST`
calls are anchored `^[a-z_0-9]* *=` and cannot see a comment. **The four name calls can:**
they match a backticked lowercase name followed by an asterisk — `` `x`* `` — anywhere,
comments included. Write a key name in backticks and start a bold run right after it, and
25/26/25/27 moves. I used no asterisk and no backtick at all. Measured after: 27
occurrences, exactly 2 of them `**` (454, 922) → 25 single-star, 25 distinct single-star,
26 distinct overall. All four hold.

**For the reviewer:** head 66 → 70 lines, four added, none removed, the twelve-table list
character-identical at 50-53; everything below shifts **+4**. 47 / 4 / 51 unchanged. Head
names 0009 and 0035 and nothing newer (0150 first at line 170); the `0016` at 50-51 is the
venture in a path and stood there before.

## Open leads

- **0217 is built. Uncertain, for the project manager:** (a) I made a frozen head four
  lines longer to say it is frozen, which is the one move the package's own logic could be
  read to forbid. I think it is right — the freeze sentence at lines 4-10 covered the
  package number, the date and the version count, and never the source list, so this
  closes a gap rather than continuing a record — but it is a judgement and a reviewer may
  see it the other way. (b) If (b) was wanted after all, the `Grep` call belongs beside the
  list and T46 has to go, because it is not cited. Say so and it is one edit.
- **0185 is built, return pass 2 of 3.** Uncertain, for the project manager: (a) 1238 is
  again carried forward, not measured with `tomllib` — no shell; the field says so.
  (b) I did **not** add `0214-leitzins-zitate-auf-uebersetzten-wortlaut-nachziehen` to
  `datei.nachgezogen_durch`, although it was folded into this package. Adding it would
  have added a leaf value and a line and broken the balance the same field asserts; 0214
  stands on `fertig` with a pointer here, so the trail exists in `aufgaben/`. Say so if
  you want it the other way. (c) `datei.stand` still reads 2026-09-06 although the change
  is from 2026-09-07 — the package allows no third leaf value, named rather than smoothed
  over, second run now.
- **`belegstellen_messung` is red for a reason that is not mine and not the riegel's:**
  Messstand 0147 fails its own self-test (`einmal_ersetzen` gives `yxb`, expected `ayb`)
  and reports "NICHT GEMESSEN". Condition 4 names `belegstellen_riegel`, a different ctest
  entry. Do not read the one as the other.
- **Reported, outside my package: `daten/reihen.toml:406` cites `Abschnitt zur
  Partielaenge R` against `spiel.md`, and that heading no longer exists** — `spiel.md:95`
  now reads "## The game length R, and why it stands here as a letter". **The riegel
  cannot see it:** the name after the keyword begins with the lowercase `zur`, so the
  bare-name form is refused, and no quotation follows within five words, so the third form
  yields nothing. A dead reference that is green by construction. This is the same
  translation wave as condition 4 and it wants a package.
- **The 55 uebergangene Fundstellen** now have a first concrete member from this run (see
  above). Still no package, still cheap.
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

## 2026-09-07 — 0203, return round 1: the head, second attempt

Round 1 froze the head with one sentence (criterion b) and then wrote a roll-call
under it naming which later packages had changed the file. The reviewer was right:
that list is the same disease in a new form. Removed; the rule stays in the wording
the reviewer proposed — "was spaetere Pakete geaendert haben, steht da, wo sie es
geaendert haben" — without the names and without "mit eigener Nummer und eigenem
Datum", which was false for 0035, 0175, 0193 and for 0200's change at line 809.

**The lesson that outlives the package:** an exception clause is a counter. Writing
"this head is frozen" and then listing who changed it since builds exactly the
register the sentence denies. If a head is frozen, it says so and stops.

**Where I decided against the letter of the vermerk, so the project manager sees it.**
It said "die Begruendung in 10-11 bleibt"; those lines read "Entschieden mit Paket
0203, weil ... seit Paket 0150 falsch war". Criterion (d), declared binding for the
rerun, wants every `0[0-9]{3}` in the head block to be **older than this package** and
to have stood there before round 1. 0203 is neither, 0150 is not the second. So I kept
the reason and dropped both numbers: "So entschieden, weil der Kopf sich bis dahin als
Stand der ganzen Datei las und in dieser Lesart ueberholt war, sobald ein spaeteres
Paket die Datei anfasste." Substance intact, mechanical check clean. If the intent was
that the self-reference to 0203 may stay, this is one line to put back.

**Measured myself after the edit** (Grep, no shell): 25 / 26 / 25 / 27 for the four
counting calls, 47 PLATZHALTER, 4 leaf lines with `FEST (T51)`, 51 leaf lines. Note
for whoever recounts: bare `FEST (T51)` gives **6**, not 4 — two are prose mentions in
comments; the leaf count needs the `^[a-z_0-9]* *=` anchor. The reviewer's line numbers
all shift by −1 (451→450, 919→918, 996→995); my edit is one line shorter.

`befunde/uebersetzung-2026-09-07.md` is `ergebnis: fehler`, from `belegstellen_riegel`
and `belegstellen_messung` — reihen.toml citations and a broken self-test
(`einmal_ersetzen` gives `yxb`, expected `ayb`). Nothing in it touches my package;
the three parameter.toml complaints (lines 20, 80, 898 pre-edit) are older than this
run and outside my `dateien`.

