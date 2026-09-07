---
typ: pruefung
paket: 0214-lauf-txt-traegt-den-stand-vor-0194
pruefer: test-pruefer
datum: 2026-09-07
urteil: geprueft
kriterium_geprueft: Header fields resolved one by one against today's sources; byte-identity of the recording checked against every pre-0214 quotation of the old file in the repo.
befunde: 0
---

# Pruefung 0214 — geprueft

## The acceptance criterion, piece by piece

**Dated header naming HEAD 584326c.** Lines 1–35 of `lauf.txt`: "Kopf angelegt am
2026-09-07, Paket 0214", stand "HEAD 584326c", full hash retained in the recorded
banner (line 38).

**The two packages, with the claims the abnahme names.** 0194: "der Riegel zaehlt
eine dritte Sorte (Deklarationen)", A2 gains the Deklarationen line. 0213: "die
Empfindlichkeitsprobe vergleicht je Fundstelle", A2 expects 5. Both present; 0199
added as a third, which the abnahme permits.

**Pointer to the living evidence.** Lines 27–28 name `befunde/uebersetzung-<datum>.md`
as "der lebende Beleg".

**Every recorded line byte-identical.** No git access in this role, so the check ran
over every quotation of the pre-0214 file that exists in documents written before the
build: package 0214's body (HEAD 584326c, "9 Fundstellen der zwei Nomen", 9/18/8/7/6,
A2 code 1 with 4 findings, no Deklarationen line), pruefung-0194 (9/18/8/7/6),
pruefung-0199 (HEAD stamp, A2 code 1), pruefung-0213 ("zwei Nomen", A2 4 findings).
All resolve verbatim in the recorded section. Counter-probe: no recorded line carries
any post-0194 wording ("drei Nomen", 20-case table, Teil C), and the recording's ctest
numbering (test 19) predates today's 21 (report seen by pruefung-0199) and 23 (seen by
pruefung-0213) — a refreshed recording would carry today's numbers.

## Every number in the header, against its source

- "der drei Nomen": `zahlwort_riegel.cpp:1847`, verbatim.
- Self-test 9/20/8/7/9 at lines 1226/1298/1380/1498/1609: the five `std::array` sizes
  are exactly 9, 20, 8, 7, 9 at exactly those lines; header honestly marks them "am
  Quelltext gelesen und nicht gemessen".
- A2 five findings incl. "Zeilennummer 32: 'dreiundzwanzig Deklarationen' nennt 23,
  gezaehlt sind 24": `messen.py:318-322`, verbatim.
- Teil C, two mutants of the probe: `messen.py:446-477`.
- M2/M3/M5 today 6/4/6 (expected rip-sets in `messen.py:354-405`) vs recorded 4/1/3
  (lines 62/64/68 of the recording).
- "aus 17 wurde durch 0194 die 19": case 19 of BEHAUPTUNGSFAELLE is "mehrdeutige Form
  ueber ein Beiwort hinweg" (riegel line 1341, printed as i+1), M1's expected wording;
  0194 inserted its two Deklarationen cases at positions 12–13, shifting old 17 to 19
  while old "Behauptung 3" (line 1303) stayed at 3. Both match the recording's M1 set.

## One observation, no defect

The header quotes the 2026-09-07 report as `Passed 18.27/18.34` with Gesamturteil
`fehler` wegen belegstellen. The current file of that name says `ergebnis: ok`,
zahlwort_messung Passed 18.51/18.67 — the report is overwritten per run and changed
at least three times today (13.5 s / 21 tests at pruefung-0199, 18.6 s / 23 at
pruefung-0213, now 18.51). The header's quote is dated, its load-bearing claim (the
messung runs green under today's expectations) is confirmed by the current report,
and the drift direction is harmless. Noted for the PM without a package: any sentence
citing `uebersetzung-<datum>.md` ages within hours because the filename is reused
same-day; the dated-quote convention is currently the only guard.

## What I looked for and did not find

An edited or dropped recorded line (quote sweep above); a today-claim without a
source path; a header claim that would survive the state being otherwise (each was
mutation-tested against its cited source); an ambiguous header/recording boundary
(the `###` box closes before the original `===` banner).
