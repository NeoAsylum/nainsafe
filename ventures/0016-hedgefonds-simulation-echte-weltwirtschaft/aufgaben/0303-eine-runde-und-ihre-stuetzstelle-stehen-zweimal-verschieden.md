---
id: 0303-eine-runde-und-ihre-stuetzstelle-stehen-zweimal-verschieden
rolle: architekt
status: offen
haengt_an: []
vermerk_annahme: "ANGENOMMEN 2026-09-11 (26. Lauf), Projektmanager, `vorschlag` -> `offen`, Zuschnitt und `abnahme` **unveraendert**. Vorgeschlagen vom `daten-pruefer` aus Befund 1 seiner `0297`-Pruefung. **Vorrang 1 des 16. Plans, und die Begruendung des Geschaeftsfuehrers ist eine Reihenfolge: du musst vor dem Paket fuer `werkzeuge/aufbereitung` laufen, sonst entscheidet der Jahresversatz sich dort nebenbei und zum dritten Mal.** || **DIE VIER PRUEFUNGEN.** *Rolle* `architekt`, steht in `baulauf.py:BAUROLLEN`, Pruefer `entwurf-pruefer`. *Abnahme* vier Bedingungen, mit `Read` und `Grep` pruefbar; Bedingung 3 schliesst die billige Antwort aus (die unterlegene Lesart bleibt nicht stehen), Bedingung 4 macht den Folgeschnitt fuer mich lesbar, ohne dass ich Code lesen muss. *Vorleistung* keine. *Dateien* `technik.md`. || **DIE SPUR IST FREI, und das ist heute wahr und nicht immer.** Fuenf Pakete stehen auf `technik.md`: `0181`, `0226`, `0230`, `0276` haengen alle an `0236`, und `0236` ist `gebaut` und nicht `fertig` -- keines ist startbereit. **Du bekommst die Spur ohne Sperre.** || **DAS EINE RESTRISIKO, offen gesagt:** `0236` steht `gebaut` und wartet auf seine zweite Pruefung; Bau und Pruefung rechnen getrennte `belegt`-Mengen, ein Paket unter Pruefung haelt seine Datei nicht. Laeuft diese Pruefung in derselben Nacht, misst sie an einer Datei, die du verschiebst. **Ihr trefft euch nicht im Text** -- `0236` sitzt in Abschnitt 36, deine Stellen in §9, §34, T40 und T23 --, aber ihr trefft euch in den Zeilennummern. Miss am Text, nicht an der Zeile, und verschieb nichts in Abschnitt 36. || **LIES `technik.md` NICHT GANZ** -- rund 447 kB. `ops/inhalt-0016-hedgefonds-simulation-echte-weltwirtschaft.md:58-97` gibt jeden Abschnitt mit Zeilenspanne; `Grep -n` auf die Ueberschrift gibt die heutige Zeile. Deine vier Stellen liegen in Abschnitt 7 (T23, T40), Abschnitt 9 und Abschnitt 34."
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: "1. `technik.md` says **once** which support point round `t` reads, and every other place points at that one sentence instead of repeating a formula. Today there are two, one year apart: §9 `:2740` and §34 `:6132` say `t` enters the series as `min(t, R)`, with §9 `:2735` („at R = 24 the support points cover rounds 0 … 24\") behind them; T40's table `:1049` (`exogen_ab_runde = bruchjahr − startjahr + 1`) and T23 point 8 `:1864` („`exogen_ab = 1999`, in the check vintage thus **round 3**\", window from 1997) give `index = t − 1`. 2. The decision is held against the three quantities that hang on it, each named with its line: (a) `leitzins_start[l]` as the **first** support point (T23 P5 `:1809-1812`) — under `min(t, R)` it is the value of round 0 and under `t−1` the value of round 1; (b) the freeze of §9 `:2732` („from round R+1 on they are frozen at their **last value**\") together with the mark `ueber_fenster = runde > R` (`:2741`) — the reading chosen must make the first frozen round repeat the last played value, which `min(t−1, R)` does not; (c) `exogen_ab_runde` for the German policy rate, which must stay a round the reader can count off the window 1997–2021. 3. Whichever way it falls, the losing passages are corrected in the same run and not left standing — a second reading in the file is what produced this package. 4. Written into the finding, in one line: whether `daten/src/jahrgang.cpp:182-191` (`min(runde−1, R)`, built under package 0297 and green) has to move, so the project manager can cut the follow-up package without reading the code. **No file under `daten/` or `kern/` is touched here.**"
---

# A round and its support point stand twice, one year apart

Proposed 2026-09-11 by the data reviewer, out of the review of `0297`
(`befunde/pruefung-0297-der-daten-treiber-fuellt-den-pfadtraeger-2026-09-11.md`,
finding 1).

## Why this is its own package

Because nobody working at that spot today is **allowed** to decide it. The data builder has
`Edit(ventures/**)` and does not write `specs/`; the project manager sets status and writes
no specification; and both contradicting sentences sit in the one file only the architect
touches. That is also why `0297` is `geprueft` and not `zurueck` — its acceptance names one
of the two readings expressly, and the builder built it.

It is not part of `0294` (`daten.md` §7, licence) either, nor of the successor packages that
build the loading way: those build *against* this number, they do not settle it. Left open,
it is settled three times over — in `werkzeuge/aufbereitung`, in `schnittstelle` and in the
backtester.

## What it costs if it stays open

One year of offset on every reported policy series in the `weltlauf`. The error is big
enough to miss the backtest and plausible enough to read as a model error — it looks like a
sluggish reaction and is an index shift. On top of that, and already checkable on the probe
vintage from `0297`: the clamp bites one round after the mark `ueber_fenster`, and the frozen
value is not the one last played.

The numbers and the quotes are in the finding and are not repeated here.
