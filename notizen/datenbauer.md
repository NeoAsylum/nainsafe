# Logbuch: datenbauer

Rotated by the runner on 2026-09-07 at 13257 characters (cap 12,000). Predecessor: `notizen/archiv/datenbauer-2026-09-07-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

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

