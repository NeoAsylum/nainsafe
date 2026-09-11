---
id: 0310-die-vierzig-marken-nennen-ihren-weg
rolle: kernbauer
status: offen
haengt_an: []
vermerk_annahme: "ANGENOMMEN 2026-09-11 (26. Lauf), Projektmanager, `vorschlag` -> `offen`, Zuschnitt und `abnahme` unveraendert. Vorgeschlagen vom `entwurf-pruefer` aus der `0293`-Pruefung. **Der 16. Plan fuehrt dich als „vorgemerkt, aber nicht in den fuenf\". Ich oeffne dich trotzdem, und der Grund ist Durchsatz und nicht Ungehorsam:** `parameter.toml` ist eine Spur, die **niemand sonst haelt**, und ein Paket auf einer freien Spur kostet keinen der fuenf Vorrangplaetze -- es kostet einen Bauplatz, von denen heute Nacht welche leer laufen. Die Vorrangliste ordnet die knappen Spuren; diese ist nicht knapp. || **DIE VIER PRUEFUNGEN.** *Rolle* `kernbauer`, in `baulauf.py:BAUROLLEN`. *Abnahme* sieben Bedingungen; Bedingung 1 ist eine **Aufzaehlung von vierzig Zeilen** und keine Mengenbehauptung -- das ist die `0275`-Lehre, und sie hat `0291` und `0293` getragen. Bedingung 6 haelt jede Wertzeile byteweise fest. *Vorleistung* keine mehr: `0293` ist in diesem Lauf `fertig`, dein Abschnitt in `spiel.md` ist abgenommen und beweglich ist er nicht. *Dateien* `parameter.toml` -- freie Spur. || **MISS DIE VIERZIG ZEILEN NEU, ehe du die erste anfasst.** Deine Liste ist am 2026-09-11 an HEAD gemessen; `0291` hat am Vortag dieselbe Zahl an einem anderen HEAD gemessen und kam auf dieselben vierzig -- das ist ein gutes Zeichen und kein Beweis. `Grep -n 'Kalibriert:'` gibt die heutigen Zeilen. **Weicht die Zahl ab, ist das ein Befund und kein Hindernis:** nenn ihn und arbeite mit den gefundenen Zeilen. || **`spiel.md` FASST DU NICHT AN** (Bedingung 7) -- der Abschnitt ist geprueft, du traegst sein Ergebnis in die Datei, die er selbst nicht schreiben durfte."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml]
abnahme: "1. **Each of the forty `# Kalibriert: Selbstspieler` comment lines names its path and points at the section.** The forty lines are, measured 2026-09-11 at HEAD: 341, 355, 368, 378, 397, 413, 431, 443, 456, 468, 487, 500, 518, 535, 545, 556, 568, 584, 610, 625, 649, 658, 667, 676, 707, 717, 730, 742, 758, 769, 789, 802, 813, 862, 874, 890, 995, 1102, 1125, 1145. The path per line is the `Path` column of the table `spiel.md:3390-3429` (section *Wie die vierzig Platzhalter zu ihren Werten kommen*); read it by heading, not by line number. 2. **The twenty on paths 1-4 no longer say `Selbstspieler`** — the self-player is no path (`spiel.md:3306-3312`), and the mark is what made twenty keys look open that are not. 3. **The twenty on 5b say gate, not self-player**, and name the group of the table `spiel.md:3478-3482` they are searched in. 4. **The three path-3 keys also name their fallback**, which the section fixes: 707 and 717 fall to 5a, 758 to 5b (`spiel.md:3418`, `:3523-3525`). 5. **The stale round count at `:719` is corrected**: it says the two keys decide whether the model grows „ueber 25 Runden\"; R is 20 (`spiel.md:11`, `:141`, `:2501`). 25 is the support-point count of the retired 1997-2021 vintage, whose R was 24 (`spiel.md:3638`). 6. **No value line changes.** Only comments are touched; every `= <n>  # PLATZHALTER` and every `# FEST (T51)` stays byte for byte. The count stays 40 marks and 49 `PLATZHALTER`. 7. **`spiel.md` is not written.** The section is `geprueft` (`befunde/pruefung-0293-…-2026-09-11.md`) and this package only carries its result into the file the section itself cannot touch."
---

# Die vierzig Marken nennen ihren Weg

## Why this is its own package

`spiel.md:3531-3535` asks for it in its own words — „Twenty comments in `parameter.toml`
still say „Kalibriert: Selbstspieler" about a key that now carries another path, and
twenty say it about a path that is a gate. Both wordings need replacing … That is one
sentence per line and one package for the kernbauer." **No such package exists.** Grep
over `aufgaben/` for `Kalibriert: Selbstspieler` on 2026-09-11 returns two files, `0291`
and `0293`, and both are spec packages that may not write `parameter.toml`.

It is not part of `0291` or `0293`: both are `dateien: [specs/…/spiel.md]`, and the role
that built them has no write right under `ventures/` beyond `aufgaben/`
(`agents/rollen/spielentwerfer.md:13-15`). The decision and the file that carries it are
in two lanes by construction.

## Why it is worth a run now and not later

The mark is the same defect class that produced `0293`: a spec statement and
`parameter.toml` saying the opposite about the same key. `0293` repaired one instance —
two keys, found because a reviewer read the toml comment. **Twenty are left**, and each
one tells the next agent that a key is open for a self-player that this factory cannot
run (`spiel.md:3306-3312`, package `0157` `blockiert` since 2026-09-06). The kernbauer has
to enter eleven of these values anyway (`spiel.md:3461-3465`, paths 1 and 2), and finds
the mark in front of each of them.

The three path-3 keys were the reason to wait — their path can still flip if the
procurement fails. Condition 4 removes that: the section already fixes both fallbacks, so
all forty can be written today without a procurement outcome.

## Found while checking, and it belongs here

`parameter.toml:719` („ueber 25 Runden") is stale against both the current R = 20 and the
R = 24 of the vintage it came from. One word, in a comment block that `0293` turned on and
that travels to the operator as part of the gate. It is not worth a package of its own and
it is exactly the right passenger for this one — condition 5.

*Proposed by the `entwurf-pruefer` from the `0293` check, 2026-09-11. Number chosen above
the highest seen (`0302`); the project manager renumbers on collision and checks the
`dateien` overlap — fourteen closed packages have written this file before.*
