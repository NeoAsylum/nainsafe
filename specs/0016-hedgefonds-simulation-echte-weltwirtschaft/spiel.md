---
typ: spiel
idee: 0016-hedgefonds-simulation-echte-weltwirtschaft
erstellt: 2026-09-01
schleife: Der Spieler stellt je Runde bis zu drei Aktionen aus fünf Arten, die Welt rechnet ein Jahr weiter, und jede Zahländerung trägt die Kette ihrer Ursachen mit sich.
siegbedingung: Das Mandat — Fondsvermögen über einer Schwelle UND Einfluss über einer Schwelle in mindestens zwei Ländern — erreicht innerhalb von R Runden, ohne vorher an einer der drei Todesarten zu sterben. Ergebnis ist die Rundenzahl bis zur Erfüllung.
aktionen: 5
laender: Schicht 1 — 4 Politikländer (USA, China, Deutschland, Brasilien), nach Paket 0118 neun: dazu Japan, Indien und Chile als Rückvergleichsländer, Singapur und Saudi-Arabien als Spielländer. Also L = 9, L_R = 7, L_S = 2, n = 1. Schicht 3 — ein nicht spielbares Restwelt-Aggregat. Schicht 2 siehe boersenplaetze.
boersenplaetze: Schicht 2, B = 3·(L+1) — je Gebiet ein Platz je Leitsektor. Bei L = 9 sind das 30 Plätze zu je vier Feldern plus einem Positionssteckplatz, also 150 Adressen; Zustand 890, handelbare Plätze 75. Handelbar, nicht beeinflussbar, ohne Handelszeile, ohne Sollreihe.
gueter: 3 Sektoren (Landwirtschaft, Industrie, Dienstleistungen), davon 2 mit Handelszeilen
takt: 1 Runde = 1 Jahr; R = 20 Runden, Startzustand 2001, Endzustand 2021, 21 Stützstellen
gegenkraefte: 5
messbar_entscheidungsdichte: Je Runde t = 1…R und je Startwert 30 gezogene Aktionsbündel; jedes ersetzt die Bot-Aktionen der Runde t, danach spielt der Heuristikbot auf dem Referenzprofil (1,1,1,1,1) bis Runde R. Dichte(t, Startwert) = Anteil der 30 Ergebnisse, die um mehr als 1.000 Milli-Runden vom Median dieser 30 abweichen; Dichte(t) = Mittel über die 50 Startwerte. Abnahme = Mittel der Dichte(t) je Partiedrittel (1-6, 7-13, 14-20) jeweils >= 0,4.
messbar_strategievielfalt: Profil = Fünftelverteilung über die fünf Aktionsarten (126 Profile), Wirkung über das Vorratsverfahren; je Profil Suchbot über 20 Startwerte, Profilergebnis = Median. Profil gewinnt, wenn sein Median <= 20.000 liegt. Strategiekern = die stärkste der drei Familien Position/Beteiligung/Lobby; die 6 Profile ohne jede Familienaktion haben keinen Kern und zählen nicht. Abnahme = alle drei Kerne stellen mindestens einen Gewinner, und das beste Klassenergebnis ist höchstens 25 Prozent besser als das schlechteste der drei.
messbar_optimumsverschiebung: Frühfenster = Runden 1-6 mit Profil p, Rest mit Referenzprofil; Spätfenster = Runden 14-20 mit Profil p, Rest mit Referenzprofil; je 126 Profile x 20 Startwerte, Median als Profilergebnis, bestes Profil je Fenster nach kleinstem Median (Gleichstand nach Profilkennung). Verschiebung = L1-Abstand der beiden Profilvektoren geteilt durch 5, Werte aus {0; 0,4; …; 2,0}. Schwelle 0,4.
messbar_rueckvergleich: Startjahrgang 2001, R = 20 Runden im Weltlauf (Fondsteilsystem abgeschaltet), Politikinstrumente exogen auf den historischen Pfaden; Prüfgegenstände 3·L_R + (L_R − n) + 1 aus L_R(S+3) − n freien Sollreihen plus Handelsblock, je über 21 Stützstellen ohne Füllung — heute L_R = 4, also 16 aus 23; nach Paket 0118 L_R = 7, also 28 aus 41. Schwellen: MAPE 20 Prozent für Niveaureihen, mittlerer absoluter Fehler 300 Basispunkte für Ratenreihen, Richtungstreue 0,6 für alle, gebildet über die Übergänge, in denen sich die Sollreihe bewegt. Bestanden, wenn höchstens ⌊L_R/2⌋ Prüfgegenstände reißen — heute 2, nach 0118 3.
---

# Ein Hedgefonds mit vier Ländern, drei Sektoren und vier Politikhebeln — und jede Zahl, die sich bewegt, sagt warum.

*Fünfte Fassung, nach
`ventures/0016-.../befunde/pruefung-0001-entwurf-abnahme-runde6-2026-09-01.md` und gegen
`ventures/0016-.../aufgaben/0001-entwurf-abnahme.md`. Geändert sind gegenüber der vierten
Fassung genau drei Stellen: der neue Abschnitt **Was ein Korb wert ist, was eine Stufe ist
und was eine Anleihe kostet** (Befund 1), die **Kanaltabelle**, die dadurch einen achten
Kanal bekommt, und drei Zeilen in der Tabelle der Größen ohne Datenanker. Keine Zahl der
vierten Fassung ändert sich, keine Zustandsadresse kommt hinzu. Die Abarbeitung der zwei
Befunde steht am Ende der Datei, die der früheren Runden darunter.*

*Nachgetragen am **2026-09-02** aus Arbeitspaket `0021-schaden-gegenkraft-5`: der Abschnitt
**Der Schaden in Gegenkraft 5, als Rechenvorschrift**, sechs Zeilen unter „Was bewusst
fehlt", fünf unter „Offene Entwurfsfragen" und eine Tabelle unter „Was der Architekt neu
rechnen muss". Auch dieser Nachtrag ändert keine Zahl der fünften Fassung und keine
Zustandsadresse; er füllt die Lücke, die `technik.md` Abschnitt 12 Punkt 3 gemeldet hat.*

*Geändert am **2026-09-03** aus Arbeitspaket `0039-zollzeile-konjunktursockel`, nach
Befund 1 und 2 der Prüfung vom 2026-09-02. Die **Zollzeile** der Schadensvorschrift misst
nicht mehr die ganze Verschiebung des Sektorpreises, sondern **allein den Anteil, den der
Zollkeil daran hat** — Weg 1 von den dreien, die der Befund offengelassen hat. Betroffen
sind sechs Abschnitte unter *Der Schaden in Gegenkraft 5*, eine neue Zeile unter *Was für
die Preisbildung gelten muss*, die Zeile zu Kanal 3, vier Zeilen unter „Was bewusst
fehlt", drei unter „Offene Entwurfsfragen" und die Nachziehtabelle. Auch dieser Nachtrag
kommt **ohne neue Zustandsadresse** aus; die Zahl der Lesezugriffe fällt von behaupteten
120 auf nachgezählte **106**. Die Abarbeitung beider Befunde steht am Ende der Datei.*

*Geändert am **2026-09-03** aus Arbeitspaket `0054-partielaenge-r-entscheiden`. **R ist von
24 auf 20 gefallen, das Fenster von 1997–2021 auf 2001–2021, die Stützstellenzahl von 25 auf
21.** Reihe 9 (Leitzins) ist **keine Sollreihe mehr** und behält ihre beiden anderen Rollen;
die Sollreihenzahl fällt damit von 31 auf **27**. Die 16 Prüfgegenstände von Maß 4 und die
Toleranz 2 bleiben **unverändert** — die vier gestrichenen Reihen waren nie darunter. Die
Begründung steht vollständig im Abschnitt **Die Partielänge R**, die Liste der nachzuziehenden
Stellen unter *Was der Architekt neu rechnen muss*. Dies ist der Fall, für den die
Ersetzungsregel der fünften Fassung geschrieben war: R ist ersetzt und sonst nichts.*

*Zweiter Lauf desselben Pakets, ebenfalls am **2026-09-03**. Die Entscheidung steht
unverändert; nachgetragen ist allein der Block **Nachtrag desselben Tages** unter *Was der
Architekt neu rechnen muss*, weil die Nachziehtabelle des ersten Laufs sieben Stellen in
`technik.md` nicht genannt hatte — sechs davon außerhalb eines T-Blocks, darunter das
vollständige Laufzeitbudget in dessen Abschnitt 10. Keine Zahl dieser Datei ändert sich
dadurch, keine Zustandsadresse, und `technik.md` ist weiterhin nicht angefasst.*

*Geändert am **2026-09-04** aus Arbeitspaket `0055-zollzeile-vergleichszahl-zustand-b`, nach
Befund 1 der Prüfung vom 2026-09-03. Betroffen ist **ein** Absatz: die Vergleichszahl im
Abschnitt **Zwei Zustände, zwei Zahlen**, die eine Größe eines fremden Zustands unter der
Beschriftung „Zustand B" führte. Sie ist durch die Zahl ersetzt, die aus der Tabelle darüber
folgt (**8.472.000**), die Tabelle bekommt die eine Eingabezeile dazu, die dafür fehlte, und
die Abarbeitung steht am Ende der Datei. Keine Entscheidung, keine Zustandsadresse, keine
Kalibrierzahl und keine der Zahlen von Zustand A ändern sich.*

*Geändert am **2026-09-05** aus Arbeitspaket `0119-welt-in-drei-schichten`, nach einem Einwand
des Betreibers vom selben Tag: Ein Hedgefonds, der nur in vier Ländern etwas halten kann, ist
kein globaler Hedgefonds. Neu ist der Abschnitt **Die drei Schichten der Welt** mit der
zweiten Schicht, den **Börsenplätzen**; dazu ein Halbsatz in Aktion 1, ein Absatz unter
*Der Zustand* (welchen Stand die 310 meint), ein Absatz unter *Warum die Größe des Zustands
keine Verteidigung ist*, **sieben** Einträge unter „Was bewusst fehlt" — sechs neue und der
erste, „Mehr als vier Länder und drei Sektoren", ergänzt statt gestrichen —,
fünf unter „Offene Entwurfsfragen" und ein Block unter „Was der Architekt neu rechnen muss".
**Keine Zahl der bestehenden vier Länder, keine Sollreihe, kein Prüfgegenstand und kein
Fehlermaß ändert sich**; die Bezugszahl des Zustands bleibt bis 0116 und 0118 die **310**, und
die Schichtensumme **890** gilt für den Stand nach beiden. Die zweite Schicht kostet **zwei**
neue Schlüssel in `parameter.toml` und **keinen neunten Rückkopplungskanal**.*

*Geändert am **2026-09-06** aus Arbeitspaket `0118-fuenf-weitere-laender-auswaehlen`, nach der
Anweisung des Betreibers vom 2026-09-05 („Lass uns insofern direkt 5 weitere Länder
einplanen") und seiner Wahl von Weg A (die Steckplätze wachsen mit `L`). Neu ist der Abschnitt
**Welche neun Länder, welche Klasse, und was Weg A kostet** unter *Der Zustand*; dazu zwei
Zeilen im Frontmatter, die Zählregel von Maß 4 in `L_R` statt in Ziffern, vier Einträge unter
„Was bewusst fehlt", fünf unter „Offene Entwurfsfragen" — davon eine **geschlossen** — und ein
Block unter „Was der Architekt neu rechnen muss". **Die 310 bleiben stehen**, bis 0116 die
Ableitungskette geschrieben hat; keine Zahl in `technik.md`, `reihen.toml` oder im Kern ist
angefasst. Die fünf sind **Japan, Indien, Chile, Singapur und Saudi-Arabien**, die ersten drei
als Rückvergleichsland erwartet, die letzten beiden als Spielland; damit ist `L_R = 7` und die
Zahl der Prüfgegenstände wächst von 16 auf **28**, die Toleranz von 2 auf **3**.*

## The game length R, and why it stands here as a letter

The second version derived the game length from a rule — *the game length is the length
of the window in which every target series is covered without a fill* — and then plugged
in a wrong number. The third version kept the rule and plugged in a second number,
measured against **three** of the 31 series and the trade block — the three US
sector-share series and BACI. **Since 2026-09-02 all 31 are measured**, and both numbers
were too large.

### What is measured

`daten/deckungsbefund-1997.md` (package `0006-deckung-pruefjahrgang-1997`, `status: fertig`,
retrievals of 2026-09-01) retrieved each of the 31 target series and the trade block
individually. Of the 31, 26 hold the window 1997–2021 in full. Five do not, and they are
of two different kinds:

| Series | Country | Finding | Role per `technik.md` section 7 |
|---|---|---|---|
| **11** government debt ratio | USA | begins **2001** (IMF WEO) | start + target (**derived**) |
| **11** government debt ratio | BRA | begins **2000** | ditto |
| **9** policy rate | USA | ends **2020** (IMF `MFS_IR/DISR_RT_PT_A_PT`) | start + policy path + target (**set**) |
| **9** policy rate | DEU | **not a single value** | ditto |
| **9** policy rate | CHN | **not a single value** | ditto |

Add a side finding outside the target series that co-decides here: **series 12 (budget
balance), the historical policy path of the fourth instrument, likewise begins in 2001
for the USA** — two independent WEO series with the same starting year, cross-checked in
the finding against six known values. That is no retrieval uncertainty but the known
property of the WEO of carrying the fiscal statistics of the US general government only
from 2001 on.

### The decision: R = 20, window 2001–2021, 21 support points

The finding lays three ways out side by side, each with an R — 19, 20 or 24. **Chosen
is 20.** The other two fail for one reason each, and both reasons stand in the role
column of the series list: a series here is not simply "there" or "gone", it has up to
three roles — start value, policy path, target series — and a way out that strikes it
strikes only one of them.

**2001 is forced, and not by a target-series rule.** The way out to `R = 24` is called
„Reihe 9 und Reihe 11 gestrichen" in the finding. But only the *target role* of a series
can be struck, not its other two. Series 11 is also **start**: `staatsschuld[l]` is a
state address, and its start value is the first support point of this series. Series 12
is **policy path**: without it, the budget instrument in the `weltlauf` stands on
nothing. Both gaps are **leading gaps**, and the fill rule from T24 reads „Fortschreibung
des letzten bekannten Werts" — before the first support point there is none. A leading
gap cannot be filled by the rule that exists.

**`R = 24` thus demands three source replacements, and none of them is to be had.**
Individually, because they differ:

| what would have to be replaced | state after the coverage finding |
|---|---|
| series 11 **BRA** 1997–1999 | The IMF WEO begins in 2000, the World Bank (`GC.DOD.TOTL.GD.ZS`) in 2010. **No value in either checked source.** That alone settles 1997. |
| series 11 **USA** 1997–2000 | The World Bank carries the USA gap-free 1997–2021 — but it measures the debt of the **central government**, the WEO that of the **general government**, and for China and Germany it carries nothing. The way out would mean: a target series that comes, per country, from a different source with a different delineation. That is exactly the defect over which the policy rate is losing its target role right now. |
| series 12 **USA** 1997–2000 | **Not measured.** The finding found it as a side finding, not as an assignment. It would first have to be searched for. |

The first row is binding: it says no without the other two having to be decided. Writing
a number into this frontmatter that stands on data nobody has would be exactly the
mistake of the second version all over again.

**2021 is not forced.** The window ends in 2020 only because the **US policy rate** ends
there. Per `technik.md` T37 this series was **set**: in the `weltlauf` the instrument is
set to the historical value, its error is zero by construction, its directional accuracy
one, and it is none of the 16 check subjects and could become none. **All series that
decide anything hold 2021** — GDP, the twelve sector shares, consumer prices, the three
exchange rates, the trade block, plus all four debt ratios. `R = 19` thus throws away the
support point 2021 to protect a series that cannot fail. And the one thrown away is not
just any: a backtest that ends in 2020 checks the crash and never the rebound. Its last
transition is a plunge without a counterpart, and directional accuracy measures, across
the sharpest movement of the whole window, exactly one direction.

**From this follows the cut:** series 9 loses its target role and keeps start and policy
path. The target series are thus **27** — series 1 (4), series 2 (12), series 8 (4),
series 10 (3), series 11 (4) — and **all 27 hold 2001–2021 with 21 support points without
a single fill.** That is the largest window in which this sentence is true.

### What the three ways out cost Maß 4 — and why that does not decide the choice

Because the acceptance of this package demands it by name, here for each way out the
check subjects rather than just the target series:

| Way out | R | Window | Support points | Target series | Check subjects of Maß 4 |
|---|---:|---|---:|---:|---|
| series 9 **and** series 11 out of the target series — *rejected, window not reachable from data* | 24 | 1997–2021 | 25 | 23 | **16**, none struck |
| series 9 supplemented for DE/CN, all 31 stay target series — *rejected, sacrifices 2021* | 19 | 2001–2020 | 20 | 31 | **16**, none struck |
| **series 9 out of the target series — chosen** | **20** | **2001–2021** | **21** | **27** | **16**, none struck |

**In all three ways out it is sixteen, and that is the real finding of this package.**
The 16 check subjects draw on series 1, 2, 8, 10 and 14 — GDP per country (4), sector
structure per country (4), consumer prices per country (4), exchange rate per country
except the USA (3), trade block (1). Series 9 and series 11 do not appear in them and
cannot appear in them: the one is an input of the run, the other follows the set budget
balance and has only one endogenous denominator — GDP, which already has four numerators
of its own. **Exactly these two series are the ones that shortened the window.** The
acceptance rule „höchstens 2 der 16 reißen" therefore does not distinguish the three ways
out, and it was never what was at stake.

*The 16 and the 2 of this section are the state of 2026-09-03 and hold unchanged for
`L_R = 4`. Since package 0118 both stand as formulas — `3·L_R + (L_R − n) + 1` and `⌊L_R/2⌋`,
at `L_R = 7` thus 28 and 3. The choice of R does not touch this: all three ways out above
would have had the same set of countries, and the comparison stays valid as it stands.*

What was at stake are two other things, and by them the decision was made: **which window
is reachable from data at all** (that settles 24) and **what a support point is worth**
(that settles 19). What the backtest loses through the cut is therefore no check subject
either, but **resolution**: each of the sixteen is measured over 21 instead of 25 support
points, directional accuracy over 20 instead of 24 transitions. The thresholds — MAPE
20 percent, 300 basis points, directional accuracy 0.6 — stay unchanged; whether they are
easier or harder to hold over a shorter window is a measurement for the backtester and
not a decision of mine.

### What the cut costs, item by item

- **Four rounds.** The game is a sixth shorter than in the fifth version, the nightly run
  of the three Maße 17 percent cheaper (11,519,040 → 9,539,200 world steps).
- **The euro start 1999 lies before the window.** With it falls the only instrument lock
  that snaps shut *during* a game: Germany had no interest-rate lever of its own from
  round 3 on, now it has none from round 1. The asymmetry **between** the four countries
  stays — it is what the argument in *Welche vier Länder* stands on —, the transition
  **within** the game is gone. For Maß 3 that is the loss of one of three named sources;
  the other two, imitators (counterforce 4) and price shock (counterforce 3), are
  untouched, and the shift was never grounded on the euro.
- **The exchange-rate chaining `verkettet_ab = 1999` never runs in the check vintage.**
  It stays in the specification because the play vintages before 2001 need it — but the
  check vintage no longer tests it along the way. That belongs in every finding instead
  of being booked as "one special case fewer".
- **One filled support point in the policy path.** The US policy rate has no value for
  2021. As a path — not as a target series — it is carried forward per T24 and marked
  with `gefuellt = 1`. That is **one** input year for **one** country, and it acts on the
  last transition of the US check subjects. It is disclosed, not netted away.

### What the cut keeps, and a bonus

Still inside the window: China's WTO accession (December 2001, effective from round 1),
the financial crisis of **2008** (end of round 7), the slump of **2020** (end of
round 19) and the recovery of **2021** (end of round 20). Likewise the negative euro
deposit rate from 2014, on which the bound `aufschlag_min` hangs — see *Was ein Korb wert
ist*.

And one property that neither of the two rejected values has: **20 is a multiple of 5.**
Under the stock procedure the stock vector stands at `(0,0,0,0,0)` again after every five
rounds. For every run that plays **the same** profile for a whole game — that is all 126
runs of Maß 2 and every carrier game of Maß 1 — the game therefore ends exactly on such a
point, and every action type has received exactly `12 · ai` of the 60 slots. At 24 and at
19 the game ends mid-cycle, and the actual distribution of types deviates from the
profile that Maß 2 and Maß 3 carry as an independent quantity. That is no main reason; it
is the only point at which the chosen number is **better** than the two rejected ones and
not merely less bad. (For Maß 3 it does not hold: its windows are 6 and 7 rounds long,
the profile switch does not fall on a zero point, and the deviation within a window stays
bounded instead of zero — as before.)

### And the real lesson is not in the number, but in how it is written down

The second version wrote `28` into every derived quantity — result scale, game thirds,
window bounds, cost formulas. A single wrong measurement thereby made twelve numbers
wrong. **That is why in this draft every derived quantity stands as a formula in R, with
R = 20 substituted.** This run is the test of that: against the fifth version the
measurement cost four rounds, and the draft changed by twelve substitutions and by no
rule. No package has been built twice.

**And R can fall further.** Three paths on which the `weltlauf` hangs are to this day
**not measured**: the population and employment paths (series 5 and 6) and the tariff
path (series 13, with an open licence question on top). `daten/reihen.toml` carries them
with `deckung_gemessen = false`. The substitution rule holds for them just the same: if
the vintage build measures narrower, R is to be replaced and nothing else.

## The loop

A round is a year and runs in six steps, always in this order. The fixed order is no
formality: it is the condition for the same seed and the same action sequence delivering
the same result in three months.

1. **View.** The state, and beside it the chain of the previous round: what changed,
   triggered by what, via which detour, with what delay.
2. **Actions.** The player places **up to three** actions. Three, not arbitrarily many —
   the scarcity is the source of decision density. Whoever can do everything does not
   choose.
3. **Politics.** Pending lobby pressure and counter-lobby are netted against each other
   per instrument, delays from earlier rounds that fall due take effect, instruments move
   by at most one step per round.
4. **Economy.** Production from capital stock and productivity, trade between the four
   countries and the rest of world, prices, real incomes, interest rate, exchange rate,
   public finances.
5. **Reaction.** Approval, change of government, oversight counter, imitator counter,
   investor base — the five counterforces settle up.
6. **Settlement.** Positions valued, leverage checked against the intra-year swing,
   mandate checked, chain stored as a diff.

Within a round **no state quantity is written twice**, and the order above is cycle-free.
*Which* quantities are written at all depends on the mode — in `spielmodus` all of them,
in the `weltlauf` of the backtest a declared subset (see **Maß 4**). The only loop in the
whole model is the market clearing in step 4, and it runs with a fixed iteration count.
Everything that looks like a feedback crosses a round boundary — see **Der Zustand**.

### What must hold for price formation

The how is the architect's business; what must hold stands here.

For the two sectors with trade rows there is one world price each, clearing all supplies
and demands, and on it a tariff wedge per country. A country's sector price, however,
does **not** hang entirely on the world price, but only to the share `durchgriff`:

```
preis = weltpreis_mit_zoll · durchgriff + landespreis · (10.000 − durchgriff)
        alles geteilt durch 10.000
```

Both quantities in it are now determined, and neither was in the second version:

**`landespreis` is the sector price of the same quantity from the previous round.** In
round 1 it is the vintage's start value (index 10,000). The excess function is thereby
monotone in the world price, the bisection search from `technik.md` T28 is a single pass,
and no fixed-point problem arises. In substance this is price inertia: a sector's
domestic price follows the world price with a one-year lag, and how strongly is said by
`durchgriff`.

**`durchgriff` is a model construct with a rule, not a measured share.** The second
version called it `handelsanteil` and defined it as (exports + imports) divided by the
sector's value added. That quantity leaves its value range, and not as an outlier but by
construction: exports and imports are gross flows, value added is net. For Germany 1995
it yields 2.69 in agriculture and 1.20 in industry (recomputed by the reviewer from WDI,
retrieved 2026-08-31); the weight on the country price turns negative, and the announced
mixture becomes an extrapolation with negative prices.

The rule therefore reads, with `H` = the sector's exports plus imports and `N` = its
value added, both in the start year:

```
durchgriff = teile_gerundet(10.000 · H, H + N)
```

That is strictly monotone in `H/N`, lies in the range 0 … 10,000 for all nonnegative
`H`, `N` with `H + N > 0`, and needs no cap. The two recomputed cases become
`71.94/98.71` → **7,288** for German agriculture and `915.39/1,675.41` → **5,464** for
German industry; a US industry with `H/N = 0.3` would come to 2,308. **The ordering that
carries the argument is thus preserved** — a tariff hits China's industry hard via its
high `durchgriff` and the US industry, dominated by construction and utilities, weakly —
and the value range holds.

What the coefficient thereby is **not**: a measurement of trade openness. Its numerical
value has no economic meaning; it must order countries and sectors correctly, and it
does. It is exogenous and constant over the game; China's growing trade openness is
captured by the model through the quantities, not through the price transmission. Two
named simplifications, none hidden.

Services have no trade row, no world price and only a country price.

### The tariff wedge is multiplicative, and the scale table decides that

`technik.md` T28 **names** the wedge („der Zollkeil je Gebiet auf dem Weltpreis") without
writing it down. Until 2026-09-03 that was without consequence; since the damage rule of
counterforce 5 separates the wedge from the rest of the price lift, it no longer is. What
must hold:

```
weltpreis_mit_zoll(l, s) = mal_geteilt( welt.preis.<s>, 10.000 + zollstand(l), 10.000 )
```

**The additive reading is not more poorly justified — it cannot be formed at all.** The
tariff level stands, per `technik.md` T5, in **class 3** (basis points), the world price
in **class 5** (index, start year 10,000). A sum of two classes is unknown to T5; a rate
meets a level in this model without exception as a factor, as in
`schuld = mal_geteilt(bip, staatsschuld, 10.000)`. In substance the same choice says the
same: an aggregated tariff rate per country in basis points is an ad valorem tariff,
otherwise it would not be a rate. Both point in the same direction, which is why the
determination here is a clarification and not a choice.

It stands here and not in an open question because a computation rule that points to an
unwritten formula is again just an adjective — exactly the defect that package 0021 set
out against.

### The mapping of the BACI goods codes to the two tradable sectors

Without it neither `H` nor the trade block is computable. It is a table in the vintage's
manifest and reads:

| HS92 chapter | Model sector |
|---|---|
| 01–24 | 1 agriculture |
| 25–97 | 2 industry |

**The error of this coarse mapping is part of the deal:** raw wood (44), hides (41) and
vegetable textile fibres (50–53) are counted by WDI as agriculture, by this table as
industry; processed foods (16–21) are counted by WDI as manufacturing, by this table as
agriculture. The error is the same for all five territories because the same table
applies — and it hits the target series just as it hits the model, because the backtest's
trade block arises from the **same** aggregation. What is compared is thus aggregated
against aggregated, just as with the sector shares normalised to 10,000.

## The actions

Five kinds. Each is discrete, none has a point in time within the round. The
identifiers 1 to 5 are at the same time the tie-breaking order of all Maße.

1. **Position.** Long or short on a country×sector, on a currency, on a country's
   government bond, or — since 2026-09-05 — on an **exchange venue**
   (see *Die drei Schichten der Welt*). In fixed steps, effective immediately, unwindable at any
   time. Entering and exiting moves the price against the fund, and the more strongly the
   larger its share of that market is.
2. **Stake.** A permanent share in a country×sector. It is illiquid — exiting takes two
   rounds, and its exit discount is already built into the valuation, so it is paid in
   full at entry (see *Was das Fondsvermögen ist*) — and it is the only path to
   cheap lobbying: lobbying actions in a sector the fund holds a stake in cost a
   fraction.
3. **Lobbying budget.** Money on one policy instrument of one country, in one direction.
   It does not act immediately but attaches as pressure; whether it takes hold is decided
   by step 3 against the counter-lobby. Possible without a stake in the affected sector, but expensive.
4. **Leverage.** Borrowing at the country's policy rate plus a spread that rises with the
   fund's visibility. Magnifies every position and every losing streak.
5. **Visibility.** The fund publicly discloses a position or withdraws from view.
   Disclosure amplifies every lobbying budget on that matter, because it creates public
   pressure — and it feeds the supervision counter in every country the fund is present in.

**Why five and not three.** Kinds 1 to 3 are the three strategy families against which
Maß 2 is measured; without them there is nothing to measure. Leverage is not a strategy of
its own but the attack surface of the first way of dying, and without it size is riskless.
Visibility is the reason the counterforces are a playing field and not a brake:
without it, attention would be a mere penalty on success; with it, it is a
decision — loud and fast versus quiet and slow. That is exactly what produces the
shift of the optimum that Maß 3 demands.

## The state

**310** integer quantities; the line-by-line listing stands in `technik.md` T15 and is
recomputed there. The number itself is no defence — see below.

**These 310 are the status as of today and remain the reference number until package 0116
has written the address arithmetic parametrically.** The five further countries have been
chosen since 2026-09-06 (package 0118, see *Which nine countries*); with that the country
sum at `L = 9` stands at **740** and the state after all three layers at **890** —
computed, but not yet the reference number, because the address arithmetic must first
carry it. What this section describes is the first of three layers; the second (exchange
venues) and the computation that leads to **890** stand under *Die drei Schichten der
Welt*. Two uncommented sums in one document are the beginning of the next counting error,
which is why each of the two says which status it means.

**Per country** (four countries): three sectors with value added, capital stock,
employment and price; population and employed persons; productivity; price level and
inflation; policy rate; exchange rate against the US dollar as numéraire; government debt
and budget balance; approval of the government; supervision counter; influence; four
policy instruments, each with level, pending pressure, counter-pressure and remaining
delay; three remaining-duration counters.

**The rest of world** carries the same sector and aggregate quantities, but **no policy
instruments, no approval, no supervision counter and no influence** — the fund can
neither trade nor lobby there. It closes the circuit; without it the sum of the four
trade balances would necessarily be zero, which is false against the real data.

**Trade:** a full matrix over **five territories × four counterparts × two sectors with
trade rows = 40 flows**, the rest of world with rows of its own. Only so does the
invariant "sum of all trade balances including rest of world = 0" hold.

**The fund:** cash, positions, stakes, leverage level, global visibility, investor base,
market share, excess return of the last three rounds. Plus, per country×sector, an
imitator counter (12) and the market basket (value and return) as reference quantity.

**Influence per country** is the fund's smoothed share of the total lobby pressure in
that country, 0 to 100. It is the second half of the victory condition — and the quantity
whose acquisition wakes all the counterforces.

### The four policy instruments

| Instrument | Data anchor | Remark |
|---|---|---|
| Policy rate | yes, but **as a path, not as a target series** (since 2026-09-03, see *The game length R*) | For Germany **exogenous from 1999**; that lies before the window 2001–2021, so Germany has no interest-rate lever of its own over the whole game. This asymmetry is intended, see below. |
| Tariff level | yes, but **only aggregated per country** (WDI, with reservations) | No tariff per sector. The sector effect arises from `durchgriff` and the import shares, not from an invented sector tariff. |
| Budget balance / government spending ratio | yes (IMF WEO) | |
| Capital-flow and financial-market regulation | **no, pure model construct** | Must exist, because otherwise the supervision has no point of attack on the fund. Without a target series; in the backtest fixed at the start value, and the oracle is blind to this instrument. |

### Every quantity without a data anchor, with its start value

Acceptance condition 2 demands that every quantity is either traced back to a series from
`daten.md` or marked as a model construct with a formation rule. The anchored ones stand
in the architect's series list. Here stand **all the rest** — except for the eleven whose
provenance is `technik.md` T46 and which this table cannot know, because they follow from
comparing the series list with the address listing (US exchange rate as numéraire, five
aggregate quantities of the rest of world, five rebasing counters). **Together with T46
the enumeration is exhaustive, and only together was it ever that.** That is
observation 2 from `technik.md` section 12, accepted here rather than disputed:

| Quantity | Start value | Rule in the run |
|---|---|---|
| Sector price (per territory × sector, 15) | index 10,000 | market clearing, see above |
| World price (per tradable sector, 2) | index 10,000 | market clearing in step 4, see above |
| `landespreis` | = sector price, round 1 thus 10,000 | previous round's sector price |
| `durchgriff` (per territory × tradable sector) | constant of the vintage | `10.000·H/(H+N)`, fixed over the game |
| Approval (per country) | from `parameter.toml` | counterforce 2 |
| Supervision counter (per country) | 0 | counterforce 1 |
| Imitator counter (per country × sector) | 0 | counterforce 4 |
| Influence (per country) | 0 | smoothed share of lobby pressure |
| Lobby pressure per instrument (16) | 0 | action 3, netting in step 3 |
| Counter-pressure per instrument (16) | 0 | counterforce 5 |
| Remaining delay per instrument (16) | 0 | step 3 |
| three remaining-duration counters per country (12) | 0 | counterforces 1 and 2 |
| Financial-market regulation (level) | from `parameter.toml` | instrument like the other three |
| `markt.wert` | value of the start basket at start prices | frozen basket of amounts made of twelve baskets and four bonds, T33; valuation see *What a basket is worth* |
| `markt.rendite` | 0 | ibid. |
| Fund cash, investor base | from `parameter.toml` (start capital) | actions and settlement |
| Market share | 0 | value share of the market basket, formula under *What a basket is worth* |
| Leverage level, visibility, excess return (3) | 0 | actions 4 and 5, settlement |
| Stakes (12 shares + 12 remaining durations) | 0 | action 2 |
| Position slots (20) | 0 | action 1 |
| Game: round | 0 | bookkeeping of the run |
| Game: vintage identifier | from the vintage's manifest | fixed over the game |
| Game: parameter-set checksum | from `parameter.toml` | fixed over the game |
| Game: mandate status | 0 | step 6, mandate check |

**This table is the provenance entry for the 150 draft addresses**, and only with the
seven rows of the fourth version and the reference to T46 is it what it claims to be. The
reconciliation against the 310 addresses from `technik.md` T15 is not mine but comes from
the check of 2026-09-01: without a provenance entry there remained **32** addresses
(lobby pressure and remaining delay per instrument, added by the architect in T23
point 1) and **six** (two world prices, four game fields, for which T45 knew no
admissible entry kind). All 38 now stand here, where the table had promised them. That is
the condition on which the vintage build would otherwise abort per T45.

### What the fund's assets are, and whether the stakes belong to them

The architect returned the question (`technik.md` section 12, point 3), and it is a model
question. **They belong:**

```
fondsvermoegen = Kasse + bewertete Positionen + bewertete Beteiligungen − Hebel
```

**The reason is not taste but Maß 2.** If they did not count, action 2 would turn cash
into something that appears in neither half of the mandate; class 2 could then not pass
the first acceptance half of Maß 2 regardless of any calibration, and a Maß that fails
one of its three classes by construction measures nothing.

**Valuation is at exit value, that is, at the model value of the country×sector basket
minus the exit discount.** "Fund assets" thereby means the same thing throughout — *what
the fund is worth if it stops here* — and that is exactly what the result quantity, the
mandate and way of dying 1 need. The discount is thus paid when the stake is **built up**
and is not deducted a second time on an ordinary exit; the stake stays illiquid over the
two rounds of exit duration. The forced sale from counterforce 1 is untouched by this —
its discount is an additional penalty and comes on top.

**And the rule that secures the denominator of the fund return:** if the fund's assets
fall to zero or below, way of dying 1 (forced liquidation) takes effect in the same
round. A return on a nonpositive denominator is thus never formed.

### What a basket is worth, what a step is and what a bond costs

The fourth version decided **that** the stakes count toward the fund's assets, and
`technik.md` T47 wrote that down as a formula. That made visible that two names in it are
formed nowhere: `korbwert(l, s)` and `positionswert(p)`. Both are model decisions and
therefore stand here; with the **bond price**, which the reviewer named as the third gap
(„für die vier Anleihe-Steckplätze gibt es nicht einmal einen Preis"), they are three,
and they hang together.

#### One valuation formula, three amounts, three prices

Every valuation in the model has the same construction — **amount times price, converted
into the numéraire**:

```
wert(menge, kurs, gebiet) = mal_geteilt(menge, kurs, wechselkurs[gebiet])
```

Price and exchange rate are both indices with start value 10,000; their scale factors
cancel against each other, and the valuation needs no constant. For the USA,
`wechselkurs` stands permanently at 10,000 as the numéraire; there the formula is a pure
price valuation. Amount and price per slot kind:

| Slot kind | Amount | Price |
|---|---|---|
| Country×sector (12) | `kapitalstock[l][s]` | `sektorpreis[l][s]` |
| Currency (4) | `handelsvolumen[l]` — the country's exports plus imports over both tradable sectors, from the trade matrix | 10,000, fixed |
| Bond (4) | `schuld[l] = mal_geteilt(bip[l], staatsschuld[l], 10.000)`, with `bip[l]` = sum of the three sectors' value added | `anleihekurs[l]`, see below |

From this the four valuations from which T47 gets its two missing names:

```
korbwert(l, s)   = wert(kapitalstock[l][s], sektorpreis[l][s], l)
anleihewert(l)   = wert(schuld[l],          anleihekurs[l],    l)
waehrungswert(l) = wert(handelsvolumen[l],  10.000,            l)

stufenwert(p)    = mal_geteilt(markt(p), stufenweite, 10.000)
positionswert(p) = stufen(p) · stufenwert(p), in Fondsgeld umgerechnet
```

`markt(p)` is the basket, bond or currency value of the slot, `stufen(p)` its signed step
count from T16. The first four quantities stand in the **economy-wide scale**,
`positionswert` is per T5 **fund money** — the scale boundary thus runs exactly between
`stufenwert` and `positionswert`, and what that means stands below. The slot currency USA
stays permanently empty per T16, the formula has no effect there.

`staatsschuld[l]` is, per series list no. 11 and the class *rates* from T5, the **ratio
in basis points**, not the amount — hence the detour via `bip[l]`. A denominator of zero
occurs in none of the three rows: the exchange rate, being an index, is strictly
positive — that is a condition on the exchange-rate rule and a value-range bound the
break run checks —, the 10.000 is a literal, and the bond denominator is bounded below.

#### Why the capital stock and not value added

Both stand in the state, and the reviewer named both as candidates. It is the **capital
stock**, for three reasons, and the third decides:

1. **T33 point 3 demands a basket of amounts** to be valued at this round's prices. A
   stock is an amount, an annual flow is not. With the capital stock the frozen basket of
   amounts from T33 is a nameable quantity for the first time.
2. **A stake is a share in what a sector owns**, not in what it earns in a year. The
   yield sits in the price, not in the amount.
3. **Value added fluctuates yearly, the capital stock does not.** If a basket's value
   hung on value added, every production fluctuation would move it more strongly than any
   lobbying action — and the causal chain this game sells
   („Zoll → Importpreis → dein Bestand") would vanish in the noise of its own side
   quantities. The capital stock changes only via channel 1, that is, slowly and with
   delay; **the price change is thereby the visible part of the valuation, and that is
   exactly the number the buyer wants explained.**

A multiple on value added (a "price-earnings ratio") would be the third reading. It costs
a second free parameter without an anchor and yields the same ordering; it is therefore
not chosen.

**The capital stock per sector needs a start rule, and it is the same as for value
added.** Series list no. 3 delivers a capital stock **per territory**, the state carries
three **per territory and sector**. They arise in the start year from the sector shares
normalised to 10,000 (series 2), exactly as the three value-added figures arise from GDP
and the same shares:

```
kapitalstock[l][s] = mal_geteilt(kapitalstock[l], sektoranteil[l][s], 10.000)
```

After that it is endogenous via channel 1. That is no new mechanism but the existing one
applied a second time — and it keeps the three sector capital stocks in the rank
`Datenanker`, because both input series are anchored.

#### Why a step is a share and not an amount

`stufenweite` stands in `parameter.toml` (T27). **It is a share, in ten-thousandths, of
the market the slot hangs on, not a money amount.** A step on `US×Industrie` is thus
*`stufenweite` ten-thousandths of that basket*, and its price is what that share costs
today.

**The reason is the state, not taste.** If a step were a fixed money amount, every slot
would need its entry price just to be valued at all — twenty further addresses, a second
place for the same truth and a state that is no longer readable out of itself. As a
share, the value follows **entirely from today's state**: if I buy a step, the cash gives
up its present value and the slot takes it in, net zero; if the price then moves, the
slot moves and nothing else. With a negative step count the sign flips, and a price rise
is a loss — long and short are the same formula, as Maß 2 demands.

**Three quantities that hang on this are thereby computed as well:**

- **The fund's share in a country×sector**, in ten-thousandths:
  `|stufen| · stufenweite + anteil[l][s]`. Position and stake are shares in the **same**
  basket and add up. Absolute values, not signs — a large short moves a market as
  strongly as a large long.
- **The local footprint from counterforce 1** reads exactly this number, and so does the
  price impact from action 1 ("the more strongly the larger its share of that market
  is"). Neither needs a concept of its own any more.
- **`fonds.marktanteil`**, formed in step 6 per T33 point 4, that is, against the new
  `markt.wert`:

  ```
  korbbestand  = Σ über die 12 Körbe    mal_geteilt(korbwert(l,s), |stufen|·stufenweite + anteil[l][s], 10.000)
               + Σ über die 4 Anleihen  mal_geteilt(anleihewert(l), |stufen|·stufenweite,               10.000)
  marktanteil  = teile_gerundet(korbbestand · 10.000, markt.wert)
  ```

  Currencies do not enter — per T33 point 1 they carry no capitalisation. The
  `handelsvolumen` is the **depth** of the currency market and carries step value and
  price impact, not the market basket. `markt.wert` is a sum of positive amounts times
  positive prices and thus never zero.

**What the calibration has to hit here, and what it fails on.** Start capital and
`stufenweite` together fix how large the fund can become relative to the world. Two
conditions, both readable off the test bench: a step must be affordable out of the start
capital, and reachable step counts must be able to reach the supervision thresholds from
counterforce 1 at all. If the parameter set misses the first, class 1 never wins; if it
misses the second, no counterforce takes hold and Maß 3 falls to zero. **A third dial for
this — say, an "investable share" of the capital stock — would be redundant with the
start capital: only the ratio of the two quantities acts.** It therefore does not exist.

#### The bond price, the only new price quantity

The state carries `leitzins` and `staatsschuld` per country, but no bond price — the
reviewer rightly remarked that the four bond slots thus hang on nothing. It gets **no
address but a rule**, like `landespreis` (T39):

```
anleihekurs(l) = teile_gerundet(10.000 · (leitzins_start[l] + aufschlag), leitzins[l] + aufschlag)
```

`leitzins_start[l]` is the start year's policy rate, which the vintage carries anyway as
the first support point of the policy path (series 9); `aufschlag` is a new key in
`parameter.toml`, in basis points, and means the distance between policy rate and bond
yield.

That is the price of a perpetual bond: strictly falling in the interest rate, exactly
10,000 in the start year by construction, positive for every positive denominator,
without a cap. **The bound sits at the instrument and not at the price:** the policy rate
has a lower bound, and it is `1 − aufschlag`. The denominator is thus never zero and
never negative, and the vintage build can check it — the historical policy path must
respect it, otherwise the parameter set is inadmissible for that vintage.

**That is a real condition and not a formal one, and it hits exactly this window.** The
ECB first cut its deposit rate below zero on 2014-06-11, to **−0.10 %**, and by
September 2019 to **−0.50 %**; it stayed negative until 2022
(`ecb.europa.eu/press/pr/date/2014/html/pr140605_3.en.html` and
`ecb.europa.eu/stats/policy_and_exchange_rates/key_ecb_interest_rates/html/index.en.html`,
retrieved 2026-09-01). Germany follows the euro area exogenously over the whole game —
the 1999 break lies before the window 2001–2021 —, so the negative rate from 2014 on lies
**in the check vintage**, namely in its rounds 13 to 20. Whether the interest series the
vintage draws carries the deposit rate or the main refinancing rate is decided by the
vintage build; the lower bound must in both cases lie below the series' minimum, and
`aufschlag` is thus not freely choosable but bounded from below.

Two properties that arise for free here, and I keep them. First, the interest sensitivity
is **implicit and different per country**: at a low rate the price reacts strongly, at a
high one weakly — a German holding hangs on the interest rate, a Brazilian one barely.
That costs no parameter and distinguishes two of the four countries along one more axis.
Second, the bond is the only asset the fund can hold **without influence**; it can
therefore never win alone, because the mandate has two halves. An interest-rate bet is a
way to build capital, and never a way to win the game.

#### Where the scale boundary lies

`korbwert`, `anleihewert`, `waehrungswert`, `stufenwert`, `korbbestand`, `schuld` and
`markt.wert` are **economy-wide amounts** and stand in that scale (T5, line 109).
`positionswert`, `beteiligung_wert`, cash and leverage are **fund money** (line 108). The
conversion lies exactly on this boundary and happens **once per valuation, at the
outermost call** — that is, after the shares are netted, not before. `marktanteil` does
not cross the boundary at all: numerator and denominator both stand in the economy-wide
scale.

The second way, which the reviewer left open — carrying `korbwert` in fund money
directly — is thereby ruled out, and the reason is T33: the market basket values the same
twelve baskets, and it is an economy-wide quantity. Two scales for one basket would be
two valuations for one basket, and T47 demands „eine Bewertung, nicht zwei". **Which
function performs the conversion is the architect's business; that it stands at this spot
and only there is design.**

#### No new address

No quantity of this section is a state address. `korbwert`, `anleihewert`,
`waehrungswert`, `stufenwert`, `korbbestand`, `anleihekurs`, `schuld`, `bip` and
`handelsvolumen` are functions of the state; `stufenweite`, `aufschlag` and
`leitzins_start` are parameters or, respectively, constants of the vintage. `marktanteil`
is the only address that appears at all, and it already stands in T15.

**The 310 from `technik.md` T15 thus remain unchanged, the table *Every quantity without
a data anchor* gets no new address — only three more precise rules —, and the counting
step from T45 comes out unchanged.** That is exactly why it did not find the gap: it lay
outside the set it counts over. The counting step checks addresses; this gap was a
missing **function**, and the only remedy is that someone writes the formula down.

### Warum die Größe des Zustands keine Verteidigung ist

`agentenbau.md` nennt als wunden Punkt dieses Genres, dass „ein Modell mit tausenden
rückgekoppelten Größen leicht chaotisch wird, und dann trägt kein Regressionstest mehr".
Dagegen hilft nicht eine kleine Zahl von Feldern, sondern eine kleine Zahl von
**rückgekoppelten Kanälen**. Innerhalb einer Runde gibt es keine; über die Rundengrenze
gibt es genau acht, und sie sind hier abschließend aufgezählt:

| # | Kanal | Dämpfung |
|---:|---|---|
| 1 | Gewinn → Investition → Kapitalstock → Produktion → Gewinn | eine Runde Verzögerung, Abschreibungsrate |
| 2 | Preis → Realeinkommen → Zustimmung → Regierungswechsel → Instrument → Preis | Instrument höchstens ein Schritt je Runde |
| 3 | Instrument → Handel → Weltpreis → Schaden → Gegenlobbybudget → Instrument | Gegendruck wirkt erst in der Folgerunde |
| 4 | Vermögen → Hebel → Positionsgröße → Preisstoß → Vermögen | Hebelobergrenze, Aufschlag steigt mit Sichtbarkeit |
| 5 | Sichtbarkeit → Aufsichtszähler → Zwangsverkauf → Marktanteil → Sichtbarkeit | Zähler ganzzahlig mit Obergrenze, drei feste Schwellen |
| 6 | Überrendite → Nachahmerzähler → Preis → Überrendite | Zähler ganzzahlig mit Obergrenze |
| 7 | Überrendite → Anlegerbestand → Positionsgröße → Preisstoß → Überrendite | Abzug erst nach drei Runden, fester Anteil je Runde |
| 8 | Vermögen → Lobbybudget → Instrument → Kurs → Bewertung → Vermögen | Verzögerung und höchstens ein Schritt je Runde; Gegendruck wächst mit dem Schaden (Gegenkraft 5); Aufsicht wächst mit Einfluss mal Anteil (Gegenkraft 1); Nachahmer grasen den Kursgewinn ab (Gegenkraft 4) |

**Kanal 8 ist neu in dieser Fassung, und er war die ganze Zeit da.** Er ist die Schleife,
an der dieses Genre stirbt — *wer vorn liegt, kann mehr lobbyieren, und wer mehr lobbyiert,
liegt weiter vorn* —, und er steht wörtlich im Beispiel der Idee („Zoll +5pp → Importpreis
→ dein Bestand Sektor 3 +8,3%"). In der Tabelle fehlte er, weil das Glied *Bewertung* bis zu
dieser Fassung kein gerechneter Schritt war, sondern ein Wort; erst der Abschnitt *Was ein
Korb wert ist* macht ihn benennbar. Vier Dämpfungen greifen an ihm, alle vier stehen schon
im Entwurf, und **drei davon wachsen mit dem Erfolg** — das ist der Grund, warum er
gedämpft ist und nicht bloß langsam. Die Anleihevariante desselben Kanals (Lobby auf den
Leitzins statt auf den Zoll, `anleihekurs` statt `sektorpreis`) ist kein neunter Kanal,
sondern derselbe mit anderem Instrument und anderem Kurs.

Die Abkürzung `Instrument → Schaden → Gegenlobbybudget → Instrument`, die seit dem
2026-09-03 in der Zollzeile von Gegenkraft 5 steht, ist **kein neunter**: Sie ist Kanal 3
ohne seinen Umweg über die Menge. Der Zollstand geht dort jetzt zweimal ein — über
`handelsvolumen` wie bisher und über `hub(l, zoll)` neu —, beide Male in dasselbe Glied
*Schaden*, und beide Male mit derselben Dämpfung: Der Gegendruck wird nur in Schritt 5
geschrieben und kann erst in Schritt 3 der Folgerunde wirken. Es kommt kein Glied hinzu und
keine Rundengrenze weg.

Der Preiskanal `Sektorpreis(t−1) → landespreis → Sektorpreis(t)` ist dagegen **kein eigener**:
Er ist Kanal 3 in seinem Preisglied, ausgeschrieben. Seine Dämpfung ist der Anteil
`(10.000 − durchgriff)/10.000`, also strikt kleiner als eins, solange `durchgriff > 0`;
für Dienstleistungen mit `durchgriff = 0` ist er eine reine Fortschreibung ohne
Verstärkung.

**Die zweite Schicht bringt keinen neunten Kanal, und das ist nachgegangen und nicht
behauptet** (siehe *Die drei Schichten der Welt*). Vier Wege führen in sie hinein, und jeder
ist ein vorhandener Kanal mit einem anderen Kurs an der Stelle des Sektorpreises:
`sektorpreis → index → Bewertung → Vermögen → Lobby → Instrument → sektorpreis` ist **Kanal 8**
— dieselbe Auskunft, die für die Anleihe schon dasteht, ein drittes Mal;
`leitzins → zins[b] → index → …` ist derselbe Kanal in seiner Zinsvariante, um die Halbierung
länger verzögert; `Überrendite → nachahmer[b] → index → Überrendite` ist **Kanal 6**;
`Vermögen → Hebel → Positionsgröße → Preisstoß → index → Vermögen` ist **Kanal 4**, und
`index → markt.wert → Überrendite → Anlegerbestand → …` ist **Kanal 7**. **Was wächst, ist die
Verzweigung und nicht die Zahl der Kanäle:** Über `weltzins` erreicht ein Zinsschritt in einem
Land alle dreißig Plätze statt nur die drei seines Ankers. Die Dämpfung dieses breiteren Wegs
ist ausrechenbar und klein — ein Schritt auf `leitzins[A]` geht mit dem Kapitalstockgewicht
von `A` in `weltzins` ein, dort mit `1/2` in `zielzins(b)` eines fremden Ankers und dann noch
einmal mit `1/2` in die Halbierung, bei neun Ländern etwa gleicher Größe also mit rund
`1/(4·9) ≈ 2,8 Prozent` in der ersten Runde. **Und die Schicht ist ein Blatt:** Keine Größe der
Politikland- oder der Restweltschicht liest ein Feld eines Börsenplatzes. Das ist mechanisch
prüfbar und die eigentliche Verteidigung — ein Blatt kann keinen Kreis schließen, den es nicht
selbst durchläuft.

**Das ist die Verteidigung, und sie ist prüfbar**, anders als eine Feldzahl: Der
Bruchtester bekommt die Auflage, das Modell **200 Runden ohne Spieler** laufen zu lassen;
verlässt dabei eine Größe ihren Wertebereich, gibt es einen Kanal mehr, und der ist ein
Fehler. Ein Kanal, der nicht in dieser Tabelle steht, ist kein Feature, sondern ein
Befund.

### Warum vier Länder und nicht drei

Bei drei Ländern hat jeder Zoll genau einen Ausweichpartner. Die Reaktion des Systems auf
jede Lobbyaktion ist damit einzügig und vorhersehbar — Maß 1 kollabiert, weil eine Wahl
ohne Alternativen keine Wahl ist. Bei vier Ländern gibt es zwei Umlenkungspfade
unterschiedlicher Größe, und welcher der bessere ist, ändert sich mit dem Zustand. Das ist
der Mechanismus, aus dem Maß 3 überhaupt entstehen kann.

Die vier sind nach struktureller Verschiedenheit gewählt, nicht nach Bedeutung: **USA**
(großer Binnenmarkt, Leitwährung, dienstleistungsschwer), **China** (industriestark, hoher
`durchgriff`, gemanagter Wechselkurs, starker Zollhebel), **Deutschland**
(Exportüberschuss und **kein eigener Zinshebel** — die einzige Asymmetrie, die
einen Aktionsraum schließt und damit einen anderen erzwingt; seit dem Fensterschnitt auf
2001 gilt sie von Runde 1 an statt ab Runde 3, siehe *Die Partielänge R*), **Brasilien** (Agrarexport,
hohe Zinsen, volatile Währung). Vier Länder, die sich gleichen, wären vier Kopien und
kosteten Strategievielfalt, statt sie zu erzeugen.

**Dieser Abschnitt bleibt unverändert stehen, und sein Argument trägt bei neun Ländern erst
recht** — es sagt, warum drei zu wenig sind, nicht warum vier genug wären. Welche fünf
dazukommen, steht im nächsten Abschnitt.

### Welche neun Länder, welche Klasse, und was Weg A kostet

**Angewiesen vom Betreiber am 2026-09-05:** *„Lass uns insofern direkt 5 weitere Länder
einplanen."* Die Zahl ist entschieden, die Auswahl war es nicht. Die Regel für die Auswahl ist
dieselbe wie bei den ersten vier: **strukturelle Verschiedenheit, nicht Bedeutung** — und
strukturell heißt hier nicht „anders erzählt", sondern **an einer Größe anders, die dieses
Modell wirklich rechnet**: `durchgriff`, Sektoranteile, Kapitalstock, Handelsvolumen,
Schuldenquote, die Untergrenze des Zinshebels, die Zahl der eigenen Instrumente.

Alle Zahlen unten sind Werte des **Startjahrs 2001** aus genau den Reihen, die das Modell
ohnehin einbettet: Weltbank `NV.AGR.TOTL.ZS`, `NV.IND.TOTL.ZS`, `NV.SRV.TOTL.ZS`,
`NE.TRD.GNFS.ZS`, `NY.GDP.MKTP.CD`, `PA.NUS.FCRF`, `FP.CPI.TOTL.ZG`, abgerufen am 2026-09-06
über `api.worldbank.org/v2`; die Schuldenquoten aus dem IWF-WEO (`GGXWDG_NGDP`,
`imf.org/external/datamapper`, gleicher Abruf). **Sie belegen die Wahl, sie ersetzen den
Jahrgangsbau nicht** — die Werte, mit denen das Modell rechnet, entstehen dort und nicht hier.

#### Die fünf, und je die Eigenschaft, die keines der vier heutigen trägt

**Japan — der Anleihemarkt ist größer als die Volkswirtschaft, und das Preisniveau fällt.**
Reihe 11 trägt für Japan **126,8** Prozent im Startjahr und **222,7** im Endjahr; weil
`schuld[l] = mal_geteilt(bip[l], staatsschuld[l], 10.000)` die *Menge* des
Anleihe-Steckplatzes ist, ist Japans Anleihemarkt vom ersten Zug an größer als sein BIP und am
Ende mehr als doppelt so groß. Die USA kommen auf 53,5 und 125,0, Deutschland auf 58,1 und
67,9. Dazu die zweite Hälfte, die kein heutiges Land hat: Reihe 8 ist für Japan in **zwölf der
einundzwanzig** Stützstellen negativ (2001–2005, 2009–2012, 2016, 2020, 2021). Der
Prüfgegenstand *Verbraucherpreise* misst damit zum ersten Mal ein **fallendes** Preisniveau —
bis heute steigt es in allen vier Ländern, und ein Fehlermaß, das nur eine Richtung gesehen
hat, ist kein geprüftes Fehlermaß. **Vermutung, ausdrücklich ungeprüft und nicht Teil der
Begründung:** Ein Land mit zwölf Deflationsjahren dürfte auch den niedrigsten Leitzinspfad des
Modells tragen und damit die Schranke `aufschlag_min = 1 − min(leitzins_pfad)` binden. Das ist
nicht nachgemessen; es entscheidet sich am selben Abruf, an dem Japans Klasse hängt, und ich
schreibe es nur hin, damit der Datenbauer beim Abruf danach sieht.

**Indien — der einzige große Landwirtschaftssektor, der nicht vom Welthandel lebt.**
Landwirtschaft **21,62** Prozent der Wertschöpfung, normiert 23,5 — gegen 13,82 in China, 4,80
in Brasilien, 1,13 in den USA und 1,08 in Deutschland; über das ganze Fenster fällt der Anteil
nie unter 16,03. Zugleich nur **25,99** Prozent Handel am BIP. Beides zusammen ist die
Eigenschaft: Ein knappes Viertel der Volkswirtschaft hängt an einem Sektor, der einen Weltpreis
**und** einen Zollkeil hat, aber mit großem `N` und kleinem `H` in
`durchgriff = 10.000·H/(H+N)`. **Brasilien ist der Gegenfall** — kleines `N`, großes `H` —, und
bis heute kennt das Modell nur den. Eine große, *geschlossene* Landwirtschaft ist etwas
anderes als eine kleine, offene: Der Zollhebel eines Fremden erreicht sie kaum, der eigene
Haushalts- und Regulierungshebel dafür umso mehr. **Überprüfbare Vorhersage, kein Etikett:**
`durchgriff[IND][1]` liegt unter dem jedes heutigen Landes in der Landwirtschaft. Trifft sie
nicht ein, ist das ein Befund gegen diesen Absatz.

**Singapur — das obere Ende der Durchgriffsskala.** Handel **349,29** Prozent des BIP, gegen
59,56 in Deutschland und 22,97 in den USA; die MAS begründet ihren eigenen geldpolitischen
Rahmen mit derselben Größenordnung (*Monetary Policy Framework*, mas.gov.sg, abgerufen
2026-09-06). Der Landwirtschaftsanteil beträgt **0,08** Prozent — dort ist `N` nahe null und
`H` groß, also läuft `durchgriff` gegen seine Obergrenze 10.000: **der Sektorpreis ist der
Weltpreis.** Genau für diesen Rand ist die Formel gewählt worden (*„liegt … im Bereich
0 … 10.000 und braucht keine Kappung"*), und bis heute nähert sich ihm kein Land. Die Skala des
Mechanismus, den das ganze Spiel verkauft, reicht heute von 22,97 (USA) bis 59,56
(Deutschland), also über den Faktor **2,6**; mit Japan am unteren (19,28) und Singapur am
oberen Ende über den Faktor **18,1**.

**Saudi-Arabien — der einzige konstante Wechselkurs, und der einzige Sektor über der Hälfte.**
Reihe 10 trägt für Saudi-Arabien in **jeder** der 21 Stützstellen denselben Wert 3,75.
Industrie **50,78** Prozent der Wertschöpfung, normiert 51,3 — kein heutiges Land liegt über
Chinas 44,28. Damit trägt zum ersten Mal ein *handelbarer* Sektor mit Weltpreis und Zollkeil
die Mehrheit einer Volkswirtschaft, und ein Zollschritt irgendwo trifft dort nicht einen
Randbereich, sondern den Kern. Der konstante Kurs ist zugleich der Grund seiner Klasse, siehe
unten — er ist keine Nebeneigenschaft, sondern die schärfste des ganzen Abschnitts.

**Chile — die kleinste Volkswirtschaft mit allen vier eigenen Instrumenten, und damit der
billigste Einfluss.** BIP **71,6** Milliarden USD im Startjahr, gegen 559,98 in Brasilien — dem
kleinsten der heutigen vier — und 10.582 in den USA. Dass es alle vier Instrumente selbst führt,
ist die Erwartung, die seine Klasse trägt, und sie hängt am selben Abruf wie die von Japan und
Indien; die Größe dagegen ist gemessen und hängt an nichts. Das ist keine Größenangabe, sondern eine
Aussage über **Gegenkraft 5**: Ihr Schaden ist eine Menge mal einer Rate, und die Menge der
Haushaltszeile ist das BIP. Mit der Größenordnungsprobe, die dieser Entwurf unter *Offene
Entwurfsfragen* schon führt — Schrittweite 50 Basispunkte, `gegenlobby_satz = 1`, also ein
Punkt je 10.000 Tausend USD —, erzeugt **derselbe** Instrumentenschritt in den USA rund
**5.300** Gegenlobbypunkte und in Chile rund **36**. Der Faktor ist 148 und ist exakt das
BIP-Verhältnis; die Rechnung ist eine Schätzung nur in der Schrittweite, nicht im Verhältnis.
**Die zweite Mandatshälfte verlangt Einfluss in zwei Ländern**, und ob die Familie Lobby dafür
überhaupt einen Gewinner stellen kann, steht seit dem 2026-09-03 als *„die schärfste
Kalibrierbedingung"* unter den offenen Fragen. Chile beantwortet sie aus der **Bauart** statt
aus der Kalibrierung: Es gibt ab hier einen Ort, an dem Einfluss zwei Größenordnungen billiger
ist als in den USA — und weil er zugleich der flachste Markt ist, ist er der teuerste Ort für
Kapital. Das ist derselbe Tausch wie bei der zweiten Schicht, nur mit vertauschten Vorzeichen.

#### Die neun nebeneinander, an den Größen, die das Modell rechnet

Startjahr 2001. „größter Anteil" ist der größte der drei Sektoranteile **nach** der Normierung
auf 10.000, also die Zahl, aus der `sektorgewicht[b][s]` entsteht.

| Land | BIP (Mrd. USD) | Landw. | Ind. | Dienstl. | größter Anteil | Handel (% BIP) |
|---|---:|---:|---:|---:|---:|---:|
| USA | 10.582 | 1,13 | 21,47 | 74,02 | **76,6** D | 22,97 |
| Japan | 4.439 | 1,27 | 31,34 | 67,33 | 67,4 D | **19,28** |
| Deutschland | 1.966 | 1,08 | 26,58 | 62,41 | 69,3 D | 59,56 |
| China | 1.355 | 13,82 | 44,28 | 41,90 | 44,3 I | 38,08 |
| Brasilien | 560 | 4,80 | 22,64 | 57,71 | 67,8 D | 26,94 |
| Indien | 485 | **21,62** | 26,49 | 43,81 | 47,7 D | 25,99 |
| Saudi-Arabien | 184 | 5,13 | **50,78** | 43,05 | 51,3 I | 63,56 |
| Singapur | 90 | **0,08** | 30,38 | 63,59 | 67,6 D | **349,29** |
| Chile | **72** | 4,06 | 28,48 | 55,65 | 63,1 D | 62,14 |

**Zwei Spannen, die es heute nicht gibt, und beide sind Mechanik und keine Buntheit.** Die
Tiefe der Märkte, auf denen der Fonds steht, ordnet sich nach dem Kapitalstock des Landes —
`korbwert(l,s)` ist Kapitalstock mal Sektorpreis, `schuld[l]` ist BIP mal Schuldenquote —, und
die Ordnung der Länder ist die des BIP. Heute spannt sie von 560 bis 10.582 Milliarden, also
über den Faktor **19**; nach 0118 von 72 bis 10.582, über den Faktor **148**. Gegenkraft 3
(Marktenge) wächst mit dem Anteil des Fonds am Markt: Auf einer Skala über zwei Größenordnungen
ist „wo bin ich groß" eine Entscheidung, auf einer über eine ist es eine Konstante. Die zweite
Spanne ist die des `durchgriff`, oben schon gerechnet. **Die Zahlenwerte der Kapitalstöcke
kommen aus der PWT und nicht aus dieser Tabelle** — was hier steht, ist die Ordnung, und nur
sie trägt das Argument.

#### Die Klasse je Land, und woran sie hängt

Die Klasse ist nach `technik.md` T61 Regel 5 **keine Wahl, sondern eine Ableitung**: Ein Land
ist genau dann Spielland, wenn irgendeine seiner drei Politikpfadreihen `stufe = 4` trägt. Was
hier steht, ist deshalb eine **Erwartung mit ihrer Bedingung**, wie es der Auftrag verlangt —
entschieden wird sie am Abruf nach T63 Schritt 1.

**Was für alle neun gleich ist und deshalb keine Klasse entscheidet:** Reihe 13 (Zollniveau)
ist nach `lizenzbefund-wdi.md` für *jedes* Land gesperrt. Der Fall ist T26 erster Fall — kein
Zollpfad, konstanter Zoll, zwei statt drei verankerte Instrumente —, er gilt für die heutigen
vier genauso, und eine Eigenschaft, die alle teilen, unterscheidet niemanden.

| Land | erwartete Klasse | woran sie hängt, und was sie kippt |
|---|---|---|
| **Japan** | Rückvergleichsland | `MFS_IR` führt für JPN einen Politiksatz auf Stufe 1. Fällt `JPN.*.A` leer und ist keine Ableitung ohne freien Parameter zu haben, ist es Stufe 4 und damit Spielland. |
| **Indien** | Rückvergleichsland | dieselbe Bedingung, ein Abruf. |
| **Chile** | Rückvergleichsland | dieselbe Bedingung, ein Abruf. |
| **Singapur** | **Spielland** | Die Geldpolitik wird dort über den Wechselkurs geführt, und das Modell hat für den Wechselkurs kein Instrument. Ein Bankzins ist nach T60 kein Leitzins, und der Weg von ihm zu einem Politiksatz führte über einen Aufschlag — einen freien Parameter, also Stufe 4. **Es wird Rückvergleichsland**, sobald `MFS_IR` für SGP einen Politiksatz auf Stufe 1 führt, oder sobald T60 Stufe 3 auch ein Land trägt, dessen Zinsen von den Weltzinsen bestimmt werden statt von einer benennbaren Union. |
| **Saudi-Arabien** | **Spielland** | Zwei unabhängige Gründe, und der zweite ist der bindende. Siehe unten. |

**Singapur ist der Fall, für den T60 Stufe 3 nicht gedacht ist, und das gehört gesagt, weil der
Einwand naheliegt.** Die MAS schreibt selbst, die heimischen Zinsen seien weitgehend von den
Weltzinsen bestimmt — das klingt genau nach Stufe 3, „kein eigener geldpolitischer Hebel", und
Stufe 3 bliebe **Rückvergleichsland**. Der Einwand trägt trotzdem nicht, und zwar an der
Herleitungspflicht: Stufe 3 verlangt „welche Union, ab welchem Jahr", weil sie Stufe 1 und 2
**auf die Union** anwendet statt auf das Land. Singapur hat darauf keine Antwort — es gibt
keine Union mit einem gemessenen Satz, sondern nur „die Weltzinsen", und die sind keine Quelle,
sondern eine Umschreibung. Hinzu kommt der schärfere Punkt: Singapur hat sehr wohl einen
geldpolitischen Hebel; er ist nur einer, den dieses Modell nicht führt. **Stufe 3 ist für ein
Land ohne Hebel gebaut, nicht für ein Modell ohne Instrument** — und der Unterschied ist keine
Wortklauberei, er entscheidet die Klasse.

**Saudi-Arabien, Grund 1 (kann fallen):** Sein Politiksatz folgt der Bindung. Ihn aus dem
US-Satz abzuleiten verlangt einen Abstand, und ein Abstand ist ein freier Parameter — nach T60
also keine Ableitung, sondern eine Schätzung. Führt `MFS_IR` aber einen eigenen SAMA-Satz auf
Stufe 1, fällt dieser Grund weg.

**Saudi-Arabien, Grund 2 (fällt nicht, und er liegt nicht in den Politikpfaden, sondern in den
Sollreihen):** Reihe 10 ist für Saudi-Arabien über alle 21 Stützstellen **konstant**.
Richtungstreue misst den Anteil der Übergänge, in denen Modell und Daten in derselben Richtung
gehen; über eine konstante Reihe trägt **jeder** der zwanzig Übergänge die Richtung null, und
ein endogen gerechneter Wechselkurs trifft die exakte Null so gut wie nie. Der Prüfgegenstand
*Wechselkurs SAU* risse damit **von Bauart wegen und nicht aus einem Modellfehler** — der eine
Fall, den ein Orakel niemals produzieren darf. Als Spielland trägt Saudi-Arabien keine
Sollreihe, und die Frage stellt sich nicht. **Es wird Rückvergleichsland**, sobald das Modell
eine Kursbindung kennt (der `wechselkurs[l]` eines gebundenen Landes wird nicht geschrieben)
*und* ein Politiksatz auf Stufe 1 vorliegt.

**Daraus folgt eine Ergänzung an Maß 4, und sie gilt unabhängig von Saudi-Arabien:** Die
Richtungstreue wird nur über die Übergänge gebildet, in denen sich die **Sollreihe** bewegt.
Ein Übergang ohne gemessene Bewegung trägt keine Richtung und wird nicht gezählt; bewegt sich
eine Sollreihe in keinem Übergang, hat der Prüfgegenstand keine Richtungstreue und besteht
allein über sein Niveaumaß. Das ist keine neue Schwelle, sondern das Schließen einer Lücke: Die
Regel stand bisher nur für Reihen mit Bewegung geschrieben, und flache Abschnitte gibt es auch
ohne Kursbindung.

**Und eine Meldung an den Architekten, weil sie sein Gewerk betrifft.** T61 Regel 5 leitet die
Klasse **allein aus den drei Politikpfadreihen** ab und hält den Jahrgangsbau an, wenn die
Ableitung dem Manifest widerspricht. Grund 2 oben ist für diese Regel unsichtbar — und er ist
nicht der einzige seiner Art: T62 Folgerung 2 nennt bereits einen zweiten, die fehlende
Ausweichquelle für Reihe 2. **Beide sind Ausschlüsse, die in den Sollreihen liegen, und die
Klassenregel kann keinen von beiden sehen.** Führt `MFS_IR` einen SAMA-Satz auf Stufe 1, leitet
Regel 5 „Rückvergleichsland" ab, das Manifest sagt „Spielland", und der Bau bricht ab — richtig,
weil zwei Buchführungen auseinandergehen, aber an der falschen Stelle behoben. Das gehört zu
T61 und nicht hierher.

#### Was neun Länder zählen

Alles aus `technik.md` T59, eingesetzt für `L_R = 7`, `L_S = 2`, `n = 1`, `S = 3`, `I = 4`; jede
Zahl in diesem Lauf einmal von Hand nachgerechnet und **nicht** aus der Nachbarzeile
abgeschrieben.

| Größe | Formel | heute (`L_R = 4`) | nach 0118 (`L_R = 7`) | alle neun im Rückvergleich |
|---|---|---:|---:|---:|
| Prüfgegenstände | `3·L_R + (L_R − n) + 1` | 16 | **28** | 36 |
| freie Sollreihen | `L_R(S+3) − n` | 23 | **41** | 53 |
| Sollreihen | `L_R(S+4) − n` | 27 | **48** | 62 |
| Ströme im Handelsblock | `(L_R+1)·L_R·(S−1)` | 40 | **112** | 180 |
| Sollmaske `weltlauf` | siehe T59 | 175 | **328** | 450 |
| Toleranz von Maß 4 | `⌊L_R/2⌋` | 2 | **3** | 4 |

Nachgerechnet im Fließtext: Prüfgegenstände `3·7 + (7−1) + 1 = 21 + 6 + 1 = 28`. Freie
Sollreihen `7·6 − 1 = 41`, abgeleitete 7, zusammen `7·7 − 1 = 48`. Ströme `8·7·2 = 112`.
Sollmaske `7·27 + 22 + 112 + 2 + 3 = 328`. Toleranz `⌊7/2⌋ = 3`.

**Warum die Toleranz eine Formel ist und keine Zahl.** Bliebe sie bei 2, machte das Hinzufügen
eines Landes den Rückvergleich **härter, ohne dass sich eine einzige Regel des Modells ändert**
— ein bestandener Lauf könnte allein dadurch durchfallen, dass jemand ein Land aufnimmt. Das
ist derselbe Fehler wie eine Zahl, die zwölf andere trägt. `⌊L_R/2⌋` reproduziert bei `L_R = 4`
**genau die heutige 2** — das ist die Verträglichkeitsprobe — und hält den Anteil danach fast
fest: 2 von 16 sind 12,5 Prozent, 3 von 28 sind 10,7, 4 von 36 sind 11,1. Sie wächst also
langsamer als die Zahl der Gegenstände und senkt die Latte nie.

**Was das an Daten kostet, nach T62.** Ein Rückvergleichsland kostet bei `R = 20`
`32(R+1) + 6 = 678` Werte, ein Spielland `5(R+1) + 33 = 138`. Drei plus zwei ergibt
`3·678 + 2·138 = 2.034 + 276`, also **2.310** Werte — gegen 3.390, wenn alle fünf
Rückvergleichsländer wären, und 690, wenn alle fünf Spielländer wären. **Die Lizenzstellen
sind von der Klasse unabhängig:** zwei je Land, also zehn neue, die nach T62 Folgerung 3 auf
dieselbe Liste gehören wie die sieben offenen von heute. Kosten, kein Tor.

#### Die Folge aus Weg A: was ein Spieler vom Brett überhaupt erreicht

**Der Betreiber hat am 2026-09-05 Weg A gewählt** — die Positionssteckplätze wachsen mit `L`,
von 20 auf 45, und mit den Börsenplätzen aus Paket 0119 auf **75**. Weg B (gedeckelte
Steckplätze mit Auswahlmechanik) ist damit verworfen, **und die Begründung dafür ist die
Entscheidung des Betreibers, keine fachliche.** Das gehört so hingeschrieben, damit niemand
später eine Abwägung sucht, die es nicht gab.

Offen ist die Folge, und sie ist zu rechnen und nicht zu behaupten. Von den 75 bleibt der
Währungssteckplatz der USA nach T16 dauerhaft leer, also sind **74 besetzbar** (heute 19 von
20). Steckplätze belegt **allein Aktionsart 1**; Lobby, Hebel und Sichtbarkeit belegen keinen,
die Beteiligung hat ihre eigenen Felder. Nach dem Vorratsverfahren bekommt Art `i` über eine
volle Partie genau `12·ai` der 60 Steckplätze — die Zugabe, die *Die Partielänge R* an `R = 20`
festhält, und hier ist sie das, was die Rechnung überhaupt exakt macht statt ungefähr.

| | heute, 19 besetzbar | nach 0118/0119, 74 besetzbar |
|---|---:|---:|
| Referenzprofil `(1,1,1,1,1)`, 12 Positionsaktionen | 12 von 19 = **63 %** | 12 von 74 = **16 %** |
| reines Positionsprofil `(5,0,0,0,0)`, 60 Aktionen | 19 von 19 = **100 %**, jeder Platz gut dreimal | 60 von 74 = **81 %** |
| Frühfenster von Maß 3 (6 Runden, `a1 = 5`), 18 Aktionen | 18 von 19 = **95 %** | 18 von 74 = **24 %** |

**Die Zahl fällt hart: unter dem Referenzprofil von 63 auf 16 Prozent, also um den Faktor
vier.** Die Frage ist, ob sie unter das fällt, was die vier Maße tragen, und die Antwort ist
je Maß eine andere:

- **Maß 4 liest keinen Steckplatz.** Der ganze Positionsblock liegt im `weltlauf` außerhalb der
  Sollmaske. Unberührt.
- **Maß 2 liest nicht das Referenzprofil, sondern je Familie ihr bestes Profil.** Das beste der
  Familie 1 ist `(5,0,0,0,0)` und erreicht 81 Prozent des Bretts. Die Decke der Familie sinkt
  also nicht; was sinkt, ist die Reichweite eines Profils, das keine Abnahmehälfte liest.
  Unberührt.
- **Maß 3 vergleicht zwei Fenster, und beide stehen unter derselben Decke.** Eine Schranke, die
  in beiden Fenstern gleich wirkt, kann das eine nicht gegen das andere verschieben. Was Maß 3
  verschiebt, ist der Unterschied in der **Art** des Platzes — früh der flache, unbeobachtete
  Platzmarkt, spät Beteiligung und Lobby in Politikländern —, und daran ändert die Reichweite
  nichts. Unberührt.
- **Maß 1 ist das einzige, das das Brett unmittelbar liest**, und dort wirken zwei Kräfte
  gegeneinander. *Für* die Dichte: Die Liste der zulässigen Aktionen wächst mit dem Brett, zwei
  gezogene Bündel sind seltener dasselbe Bündel und häufiger von verschiedener Art. *Gegen* die
  Dichte: Eine Stufe ist ein **Anteil des Marktes dieses Steckplatzes**, und
  `tiefe[b] = platzanteil · …` macht jeden der 30 Börsenplätze flacher als jeden
  Land×Sektor-Korb desselben Ankers. **Vierzig Prozent des Bretts sind damit von Bauart wegen
  flach**, und eine Aktion auf einem flachen Markt bewegt das Fondsvermögen weniger.

**Das Urteil, und es ist ein enges:** Die Deckung fällt nicht unter das, was die vier Maße
tragen — drei von vieren lesen sie gar nicht. Was fällt, ist der Sicherheitsabstand von Maß 1,
und welche der beiden Kräfte oben gewinnt, entscheidet nicht der Entwurf, sondern
`platzanteil` — und der steht seit dem 2026-09-05 ohnehin als schärfste offene Frage der
zweiten Schicht da. Weg A schafft also kein neues Risiko, er hängt ein vorhandenes höher.

**Die eine empfohlene Stellschraube: die Aktionszahl je Runde, von drei auf vier.** Sie ist
empfohlen für den Fall, **nicht für jetzt** — die Bedingung steht zwei Absätze weiter. Warum
diese und nicht die beiden anderen, die der Auftrag nennt:

- **Die Partielänge `R` ist nicht frei.** Sie ist die Länge des Fensters, in dem jede Sollreihe
  ohne Füllung belegt ist, und das ist 2001–2021. `R` zu erhöhen verlangt Daten, die es nach
  dem Deckungsbefund nicht gibt. **Scheidet aus, und zwar aus Daten und nicht aus Abwägung.**
- **Plätze zusammenzufassen hieße, `B` zu senken.** `B = 3·(L+1)` ist eine **Abzählung** und
  keine Wahl: Ein Platz *ist* das Paar (Gebiet, Leitsektor), jede Kombination genau einmal. Wer
  `B` senkt, nimmt einem Gebiet die Unterscheidung nach Leitsektor und öffnet ein Paket wieder,
  das entschieden ist. **Nicht empfohlen.**
- **Die Aktionszahl ist die einzige freie**, und das Vorratsverfahren überlebt sie unverändert:
  Mit `vi += 4·ai` und weiterhin `−5` je Aktion bekommt Art `i` je fünf Runden `4·ai` von 20
  Steckplätzen und über die Partie `16·ai` von 80; nach `5k` Runden steht der Vorrat wieder auf
  `(0,0,0,0,0)`, und `R = 20` bleibt ein Vielfaches von 5. Die Reichweite des Referenzprofils
  stiege damit von 16 auf 22 Prozent, die des reinen Positionsprofils auf Sättigung (80
  Aktionen auf 74 Plätze).

**Und ihr Preis gehört dazu, sonst ist es keine Empfehlung.** Drei ist keine beliebige Zahl:
*„Drei, nicht beliebig viele — die Knappheit ist die Quelle der Entscheidungsdichte. Wer alles
tun kann, wählt nicht."* Eine vierte Aktion lockert genau diese Knappheit um ein Drittel und
kostet den Nachtlauf in Maß 2 und Maß 3 ein Drittel mehr Weltschritte.

**Deshalb die Bedingung, und sie hat eine Probe, die sagt, ob man drehen soll.** Gedreht wird
nur, wenn `Dichte(t)` in einem Partiedrittel unter 0,4 fällt **und** die Verdünnung nachweislich
die Ursache ist. Die Probe steht schon da und kostet einen zusätzlichen Lauf: `Dichte(t)` bei
`B = 0` (Brett 45) gegen `B = 30` (Brett 75). **Hält die Dichte ohne die zweite Schicht und
fällt sie mit ihr, ist die Verdünnung die Ursache und die Aktionszahl das Mittel. Fällt sie in
beiden Fällen, liegt es nicht an der Zahl der Plätze, und eine vierte Aktion hilft nicht,
sondern verdeckt.**

#### Was neun Länder im Zustand kosten

Gerechnet aus den Konstanten in `kern/zustand.hpp`; die Formel reproduziert für `L = 4` exakt
die heutigen 310. **Die Summe unten ist die Ländersumme, also Schicht 1 und Schicht 3 — nicht
die Gesamtzahl des Zustands.** Die ist nach den drei Schichten **890**: 740 plus `5·B = 150`
(*Die drei Schichten der Welt*). Zwei unkommentierte Summen in einem Dokument sind der Anfang
des nächsten Zählfehlers, deshalb steht es an beiden.

| Block | `L = 4` | `L = 9` | |
|---|---:|---:|---|
| Länder (44 je Land) | 176 | 396 | 2,2× |
| Handel `G·(G−1)·2` über `G = L+1` | 40 | **180** | **4,5×** |
| Nachahmer | 12 | 27 | 2,2× |
| Positionssteckplätze | 20 | **45** | 2,2× |
| Beteiligungen | 24 | 54 | 2,2× |
| fest (Restwelt, Fonds, Markt, Partie …) | 38 | 38 | 1,0× |
| **Ländersumme** | **310** | **740** | **2,4×** |
| Börsenplätze `5·B`, `B = 3·(L+1)` | (75) | **150** | |
| **Zustand gesamt nach drei Schichten** | (385) | **890** | |

Die Zeile *Länder* geht mit `9 · 58 = 522` auf, wenn man Steckplätze, Beteiligungsfelder und
Nachahmerzähler dazunimmt (`396 + 45 + 54 + 27 = 522`) — dieselbe 58 je Politikland wie in der
Schichtentabelle. Die beiden Zahlen in Klammern sind der Vollständigkeit halber gerechnet und
kommen nie vor: Bei `L = 4` gibt es die zweite Schicht noch nicht.

**Der Sprengsatz bleibt die Handelsmatrix**, und ihretwegen ist neun keine kleine Zahl: Sie
wächst mit `G·(G−1)·2`, also viereinhalbfach, während alles andere sich gut verdoppelt. **Die
Klassentrennung entschärft sie nicht** — sie spart Daten und Prüfaufwand, keine Adressen: Ein
Spielland belegt seinen vollen Länderblock und seine Handelszeilen wie jedes andere. Was sie
spart, sind die `112` statt `180` Ströme, über die der **Rückvergleich** läuft.

#### Was die Wahl an einer offenen Frage entscheidet

Seit dem 2026-09-05 steht die Frage offen, *„ob `3·(L+1)` die Länderwahl aus 0118 überlebt"* —
sie setzt voraus, dass jedes Gebiet drei unterscheidbare Leitsektoren trägt, und für ein Land
mit stark beherrschender Sektorstruktur lägen die drei Plätze nach der `kippung`-Regel eng
beieinander. **Die Wahl entscheidet sie, und zwar zugunsten der Formel.**

Die Spalte *größter Anteil* der Tabelle oben, absteigend: USA 76,6 — Deutschland 69,3 —
Brasilien 67,8 — Singapur 67,6 — Japan 67,4 — Chile 63,1 — Saudi-Arabien 51,3 — Indien 47,7 —
China 44,3. **Der einseitigste Anker der neun ist die USA, und die stehen seit der ersten
Fassung im Modell.** Kein neues Land ist einseitiger als ein heutiges; die beiden
ausgeglichensten Anker überhaupt sind zwei der fünf neuen, Saudi-Arabien und Indien. Die Wahl
**verbessert** den bindenden Fall also, statt ihn zu verschärfen.

Damit ist die Frage nicht beantwortet, aber sie ist umgezogen: Ob `kippung` die drei Plätze
eines Ankers auseinanderträgt, entscheidet sich an den **USA** und nicht an einem der fünf
neuen — und der Ausweg bliebe, wie es dort schon steht, eine andere `kippung` und keine andere
Formel. **Der Fall, den ich gesucht und nicht gefunden habe**, wäre ein Land mit einem Anteil
nahe 100 Prozent; den gibt es unter den neun nicht.

### Welche drei Sektoren, und aus welcher Reihe jeder entsteht

| Modellsektor | WDI-Reihe | Handelszeile | enthält auch |
|---|---|---|---|
| 1 Landwirtschaft | `NV.AGR.TOTL.ZS` (Landwirtschaft, Forst, Fischerei) | ja | — |
| 2 Industrie | `NV.IND.TOTL.ZS` (Industrie **einschließlich Bau**) | ja | Bergbau, verarbeitendes Gewerbe, Bau, Versorger |
| 3 Dienstleistungen | `NV.SRV.TOTL.ZS` | nein | — |

`NV.IND.MANF.ZS` (verarbeitendes Gewerbe) wird **nicht** verwendet. Damit hat jeder
Modellsektor genau eine Quellreihe, kein Teil der Wertschöpfung verschwindet, und die
zwölf Sektoranteil-Sollreihen bleiben echte Sollreihen statt Modellkonstrukte.

**Zwei Folgen, beide benannt.** Erstens: Die drei WDI-Anteile summieren wegen der
Gütersteuern abzüglich Subventionen nicht auf 100 Prozent. Sie werden im Jahrgang auf
10.000 normiert, die Normierung steht im Manifest, und der Rückvergleich vergleicht
normiert gegen normiert. Das Modell hat damit keinen Gütersteuerkeil; die Staatseinnahmen
laufen über den Haushaltssaldo, der ohnehin ein eigenes Instrument ist. Weil die dritte
Reihe je Land durch die Normierung festliegt, sind von den 27 Sollreihen **23
unabhängig** — ausgewiesen werden trotzdem alle 27. (Bis zum 2026-09-03 waren es 31 und 27;
Reihe 9 ist seither keine Sollreihe mehr, siehe *Die Partielänge R*.)

Zweitens: Brasiliens Erzausfuhr liegt im Modell in Sektor 2, nicht in Sektor 1. „Brasilien
als Rohstoffexporteur" heißt hier Agrarexporteur. Das ist ein Verlust an Kennzeichnung und
kein Verlust an Mechanik — der Handelsstrom ist derselbe, er hängt nur an einem anderen
Weltpreis.

### Keine verdeckte Größe

Eine Entwurfsregel, die überall gilt: **Jede Größe, die gegen den Spieler wirkt, ist im
Zustand ablesbar, samt ihrer Herkunft und ihrer Schwelle.** Der Aufsichtszähler ist
sichtbar, der Nachahmerzähler ist sichtbar, das Gegenlobbybudget ist sichtbar. Das ist die
direkte Antwort auf „the wealthy automatically hate me 100 % no matter what": Feindschaft
hat hier immer einen Zähler, einen Grund und einen Abstand zur nächsten Schwelle.

## Die drei Schichten der Welt

Until 2026-09-05 this design had **fused two axes into one**: where the player can move
policy, and where the fund can hold something. Both were `L = 4`. That made "more world"
look like "more countries at full price" — and a hedge fund that can hold something in only
four countries is no global hedge fund, however well the macro model underneath computes.
A real fund buys Japanese equities without bribing the Bank of Japan.

**The two axes are separated.** From here on the world has three layers.

### Die drei Schichten, mit ihren Feldern und ihren Rechten

| Layer | units | fields per unit | tradable | influenceable | in the backtest | trade row |
|---|---:|---:|---|---|---|---|
| **1 policy country** | 4, nine after 0118 | **58** = 44 + 5 slots + 6 stake fields + 3 imitator counters, plus its trade rows | yes | **yes** | **yes, if** it is a backtest country — since 0118 there are also play-only countries | yes |
| **2 exchange venue** | `B = 3·(L+1)`, at `L = 9` **30** | **4** + 1 slot | **yes** | **no** | **no** | **no** |
| **3 rest of world** | 1 | sector and aggregate quantities, no instruments | no | no | only in the trade block | yes |

**Why layer 1 exists:** It is the only place where a chain of effects *begins* — without
policy instruments there would be nothing to lobby and nothing whose consequence one could
explain. It is expensive, deep, and therefore scarce.

**Why layer 2 exists:** So that the investable universe can grow without the trade matrix
growing with it. An exchange venue is a **financial price, not an economy** — it has no
sectors, no capital stock, no employment, no public finances and no trade row. Exactly this
carries the difference between 890 and 87,788 fields.

**Why layer 3 exists:** It closes the circuit. Without it the sum of the trade balances
would necessarily be zero, which is false against the real data. All that is new from here
is that the rest of world becomes the **anchor territory of three exchange venues** — it
itself stays untradable and without instruments, but through these three venues the fund can
hold something that **no instrument in the world moves**. That is the only asset in the
model for which lobbying is of no help in principle, and it is therefore the touchstone for
the question of whether influence is worth anything at all.

### Was ein Börsenplatz trägt — vier Felder, jedes mit seinem Grund

A field without a reason is one address too many. So each field states what would break
without it.

| Field | class | start value | why it is an address and not a function |
|---|---|---|---|
| `index[b]` | 5 (index) | 10,000 | The venue needs a **memory of its own**, otherwise it is, every round, a snapshot of its anchor's sector prices — and two venues with a similar anchor would run in lockstep forever. Without this field the layer is decoration. |
| `wechselkurs[b]` | 5 (index) | 10,000 | **Without it an exchange venue is a linear combination of existing slots** — of its anchor's three sector baskets and that anchor's currency. This field and the next are the two that lift the venue out of the span of what already exists. |
| `zins[b]` | 3 (basis points) | `zielzins(b)` of the start year | The **discount channel** that no country×sector basket has: a basket is quantity times sector price, a venue is additionally discounted. Without it no interest-rate move separates venue from basket. |
| `nachahmer[b]` | integer, capped | 0 | **Counterforce 4 must reach the new layer.** Without this counter, 30 venues would be a hiding place from exactly the counterforce that carries Maß 3 — and the layer would make the game easier instead of richer. |

On top, **one position slot per venue** — "tradable" means exactly that and no more. So
**five addresses per exchange venue**.

**What an exchange venue expressly does not carry:** no policy instruments, no pressure, no
counter-pressure, no residual delay, no approval, no supervision counter, no influence, no
stake, no trade row, no target series. The stake is not missing out of thrift: by
*The actions* it is the only route to cheap lobbying, and a venue one could take a stake in
would be influenceable and thus no longer a venue but a cheap country.

### Woran ein Börsenplatz hängt, und was ihn eigenständig macht

An index that moves independently of everything is decoration; one that merely tags along is
a copy. Here is the coupling, as a computation rule and not as an adjective.

**Vintage constants per venue `b`** (not state addresses, just like `durchgriff` and
`leitzins_start`):

```
gebiet[b]           ∈ {1…L, Restwelt}        — das Ankergebiet
leitsektor[b]       ∈ {1, 2, 3}              — der Sektor, auf den der Platz gekippt ist
sektorgewicht[b][s] = normiert auf 10.000 aus sektoranteil[gebiet[b]][s],
                      der Anteil des leitsektor[b] mit (10.000 + kippung) gewichtet
tiefe[b]            = mal_geteilt( Σ_s mal_geteilt(kapitalstock[gebiet[b]][s],
                                                   sektorgewicht[b][s], 10.000),
                                   platzanteil, 10.000 )        — im Startjahr gebildet
zins_start[b]       = zielzins(b) des Startjahrs
```

**Functions of the state** (likewise not addresses, like `anleihekurs` and `landespreis`):

```
weltzins      = teile_gerundet( Σ_{l=1..L} kapitalstock[l] · leitzins[l],
                                Σ_{l=1..L} kapitalstock[l] )

zielzins(b)   = teile_gerundet( leitzins[gebiet[b]] + weltzins, 2 )   für ein Politikland
              = weltzins                                             für die Restwelt

zielkurs(b)   = teile_gerundet( wechselkurs[gebiet[b]] + 10.000, 2 )   für ein Politikland
              = 10.000                                                für die Restwelt

leitkurs(b)   = Σ_s mal_geteilt( sektorpreis[gebiet[b]][s], sektorgewicht[b][s], 10.000 )

zinsfaktor(b) = teile_gerundet( 10.000 · (zins_start[b] + aufschlag), zins[b] + aufschlag )

boersenwert(b) = wert( tiefe[b], index[b], b )
               = mal_geteilt( tiefe[b], index[b], wechselkurs[b] )
```

**Two special cases for the rest of world, both for the same reason.** It has no policy rate
and no exchange rate — it carries no policy instruments, and its aggregate quantities are a
residual. Its three venues therefore discount with the `weltzins` and quote in the
**numéraire** (`zielkurs = 10.000`). That is not a makeshift but the correct reading: a
basket that depicts the rest of the world has no currency of its own to set it against.
**Neither of the two formulas thus reads a rest-of-world address whose existence this design
cannot substantiate.**

**The write rule, exactly once per venue per round**, in step 4 (economy) — except
`nachahmer[b]`, which like every imitator counter is written in step 5:

```
zins[b]        ← teile_gerundet( zins[b]        + zielzins(b), 2 )
wechselkurs[b] ← teile_gerundet( wechselkurs[b] + zielkurs(b), 2 )
index[b]       ← teile_gerundet( mal_geteilt(leitkurs(b), zinsfaktor(b), 10.000)
                                 + index[b], 2 )
                 danach der Nachahmer- und der Stoßaufschlag nach denselben Regeln wie
                 beim Land×Sektor-Korb, mit nachahmer[b] und boersenwert(b) an der Stelle
                 von nachahmer[l][s] und korbwert(l,s)
```

**The five influences, enumerated rather than paraphrased.** What the price of a venue
depends on:

1. **The sector prices of its anchor territory**, weighted with `sektorgewicht[b]`. That is
   the pass-through of trade: a tariff step in any policy country moves the world price via
   market clearing, the world price moves the anchor's sector prices via `durchgriff`, and
   those move the venue. The chain the game sells thus reaches into the second layer.
2. **The policy rate of its anchor territory**, at half weight.
3. **The world rate**, the other half — the capital-stock-weighted mean of all `L` policy
   rates. An interest-rate step in country A thereby reaches **every** venue, including
   those anchored to B.
4. **The exchange rate of its anchor territory**, at half weight; the other half is the
   numéraire.
5. **The crowding** — imitators and the fund's own price shock.

**And what makes it stand on its own are three things, all three from rules and none from a
numeric value:**

- **The inertia.** `index[b]`, `zins[b]` and `wechselkurs[b]` move only **halfway** toward
  their target each round. A venue that has run up stays up, even when its anchor's
  fundamentals have already fallen back. That is the same price inertia that justifies
  `landespreis`, applied three times.
- **The mix.** A basket is one sector; a venue is all three with an emphasis. Spreading
  across venues is therefore something other than spreading across baskets — and spreading
  across venues **of different anchors** is something else again, because the third
  influence above — the `weltzins` — still couples them by half. **One cannot diversify
  completely, but one cannot fail to diversify entirely either.** That is exactly why
  diversification here is a decision and not a label.
- **The half peg to the numéraire.** In the steady state, the deviation of a venue quote
  from 10,000 is exactly half the deviation of its anchor currency — it swings half as far.
  The venue is thus the **quiet** way to hold a country — and the country's currency remains
  the loud one. Two slots, the same thesis, different risk.

**Four checks that work out without computation and that the vintage build can verify
mechanically:**

1. **In the start year the whole layer sits at its fixed point.** All sector prices start at
   10,000, so `leitkurs(b) = 10.000`; `zins[b] = zins_start[b] = zielzins(b)`, so
   `zinsfaktor(b) = 10.000`; all exchange rates start at 10,000, so
   `zielkurs(b) = 10.000`. All three halvings reproduce their own value, and
   `index[b] = 10.000` is the start condition, not a number that was set.
2. **The denominator of `zinsfaktor` never becomes zero.** `zins[b]` is a repeated mean of
   values none of which lies below the policy-rate floor `1 − aufschlag` — and that floor is
   already in the design, because of `anleihekurs`. So `zins[b] + aufschlag ≥ 1`. **The
   layer needs no new bound**; it inherits the existing one.
3. **The denominator of `boersenwert` never becomes zero.** `wechselkurs[b]` is a repeated
   mean of two strictly positive numbers and hence strictly positive — the same argument as
   for `wechselkurs[l]`.
4. **`index[b]` does not run away.** It is a mean of a fundamental value and itself, so it
   always lies between the running minimum and maximum of the fundamental value. The pure
   inertia share of a shock decays with `(1/2)^k`: after five rounds **3 percent** remains.

**Two new keys in `parameter.toml`, and not one more:** `kippung` (how strongly a venue is
tilted toward its lead sector) and `platzanteil` (what share of the anchor capital stock a
venue's depth is). `aufschlag` is **reused**, not doubled — a second markup would produce no
effect the first does not produce as well.

**Why these two numbers are parameters and the three halvings are literals:** a measure
reads them. `kippung` sets the distance between an anchor's three venues, and that is
precisely what Maß 2 measures; `platzanteil` sets how large the fund can become on a venue,
and Maß 3 measures that via the price shock. No measure reads the halvings — calibrating
them would give the search three axes whose effect `kippung` and `platzanteil` produce
anyway.

### Wie viele Plätze — und warum die Zahl eine Formel ist

**`B = 3 · (L + 1)`.** Per territory — the `L` policy countries and the rest of world — one
venue per lead sector. At `L = 9` that is **30**.

The number is not a choice but a count, and that is its virtue: a venue **is** the pair
`(Gebiet, Leitsektor)`. Every combination occurs exactly once, none twice.

- **Fewer — say one venue per territory, `B = L + 1 = 10`** — would leave the lead sector
  unexpressed. The venue would then be its anchor's mixture weighted by sector shares and
  nothing else, closer to a copy than this design can bear.
- **More — say two venues per cell, `B = 6·(L+1) = 60`** — would distinguish a cell's second
  venue from its first only by numeric values, no longer by kind. „Zwanzig Indizes,
  die dasselbe tun, sind ein Index", and it would cost 300 addresses instead of 150.
- **30 lies in the band 20–40** the work package prescribes, and it hits that band not by
  chance but because `3·(L+1)` lands there with the nine countries from 0118.

**What follows from this, and what expressly does not.** The formula fixes the **number**
and the **cut** of the venues — 30 cells, each with anchor territory and lead sector. Which
exchange venue by name sits in which cell it does **not** fix; that is a package of its own
and depends on the data situation. This section is that package's specification: 30 cells,
one name each, and per cell the check whether the chosen venue actually carries its cell's
lead sector.

**And the formula is the reason the layer does not stand in 0116's way:** it is written in
`L`, not in a digit. If 0116 makes the address arithmetic parametric, `5·B = 15·(L+1)` is
added as one more summand, and `L = 4` would give 75, `L = 9` gives 150.

### Was die Schicht kostet, und die drei verworfenen Wege

Computed from the constants in `kern/zustand.hpp`; the formula reproduces exactly today's
310 for `L = 4` and the 740 from package 0118 for `L = 9`.

| Path | policy countries | exchange venues | state | tradable slots | trade flows |
|---|---:|---:|---:|---:|---:|
| today | 4 | 0 | **310** | 20 | 40 |
| only more countries (0118) | 9 | 0 | 740 | 45 | 180 |
| **three layers — chosen** | 9 | **30** | **890** | **75** | **180** |
| the 30 venues as countries — rejected | 39 | 0 | 5,420 | 195 | **3,120** |
| all countries of the world — rejected | 195 | 0 | **87,788** | 975 | **76,440** |

**The explosive charge is the trade matrix.** It grows as `G·(G−1)·2` over `G = L + 1`
territories:

| policy countries | trade flows |
|---:|---:|
| 4 | 40 |
| 9 | 180 |
| 30 | 1,860 |
| 39 | 3,120 |
| 195 | **76,440** |

**The decisive number is not in the sum but in the ratio.** At the margin, an additional
policy country costs `44 + 40 + 3 + 5 + 6 = 98` fields for **five** tradable slots, so
roughly **20 fields per tradable slot**. An exchange venue costs **five** fields for **one**
slot. **Per tradable slot the venue is roughly four times cheaper than the country** — and
that is the whole justification of the layer, in one number.

**Rejected: all 195 countries of the world.** Not "later" — a different product.
**87,788 state fields, 76,440 trade flows and 195 × 19 = 3,705 licence-checked data
series** — package 0118 reckons 19 series and 2 licence points per additional country, which
here is 390 licence points. For comparison: this design carries 27 target series today. By
the count `4 · L_R` — four check subjects per backtest country — the backtest would have
**780** instead of sixteen (the same
formula that gives 16 for four countries; the symbol was corrected from `L` to `L_R` on
2026-09-06, because since package 0118 not every policy country is in the backtest — in this
rejected case it would be all 195, so `L_R = L` and the number unchanged),
market clearing would run over 76,440 flows instead of 40,
and the
runtime budget of the three self-play measures — today 9,539,200 world steps — would grow
with them. Whoever raises the question again finds the answer here instead of recomputing
it.

**Rejected: the 30 venues as full countries.** 5,420 fields instead of 890, 3,120 trade
flows instead of 180, and 30 × 19 additional data series — for the same 30 tradable slots.
What one would gain is that the venues could also be influenced; that is exactly what they
must not be, see below.

**Rejected: an exchange venue with a trade row.** It would then be not a second layer but a
cheap country — and the matrix would grow with `G²`, which is exactly the quantity the layer
exists to escape.

### Warum die Plätze handelbar sind und nicht beeinflussbar

This is not an economy measure but the statement the layer makes.

**An exchange venue feeds no supervision counter.** Counterforce 1 reads global visibility
times local footprint, and the footprint is influence times position share of the sector. On
a venue the fund has no influence and stands in no country's sector; its holding there
enters no counter. **The second layer is the place where the fund can grow large without
being watched.**

**And exactly for that reason it can never win there.** The mandate has two halves — wealth
**and** influence in at least two countries. Exchange venues deliver the first and **zero**
of the second. They are thus the same kind of object as the government bond, of which it
already stands written: *„Eine Zinswette ist ein Weg, Kapital aufzubauen, und nie ein Weg,
das Spiel zu gewinnen."* The second layer is the second such path, thirty times as wide.

**The fund can still move the venues — just not at the venues.** It lobbies an anchor's
policy rate and hits that anchor's three venues via `zielzins` and all thirty via
`weltzins`; it lobbies a tariff and, via the world price and `durchgriff`, hits its anchor's
sector prices and with them its `leitkurs`. **Effect yes, access no** — that is a sharper
statement than "uninfluenceable", and the more interesting one.

### Die Gegenkräfte auf der neuen Schicht

The five counterforces remain five. What changes is their reach, and that belongs written
out one by one, because a new surface without a counterforce is the fastest way back to the
feedback loop that kills this genre.

| Counterforce | reaches the second layer? | how |
|---|---|---|
| 1 supervision | **no, and that is decided** | No influence, no footprint, no counter. The price for this is the mandate. |
| 2 political backlash | indirectly | Via the anchor: a change of government resets its instruments, which moves `leitkurs` and `zielzins`. |
| 3 market thinness | **yes, and more strongly than in layer 1** | See below. |
| 4 imitators | **yes** | `nachahmer[b]`, the same rule as for the basket. |
| 5 counter-lobby | no | A venue has no instrument on which counter-pressure could form — the same argument as for the rest of world. |

**Counterforce 3 is the one that grows with success, and on the new layer it grows
faster.** Two mechanisms, both without a new rule:

- **Venues are shallower than countries.** `tiefe[b]` is a share `platzanteil` of the anchor
  capital stock, hence smaller than any country×sector basket of the same territory. The
  price shock from action 1 grows with the fund's share of the market — on a shallower
  market the same amount is a larger share. **The layer on which one can grow large
  unobserved is at the same time the one on which one's own size hurts fastest.**
- **The market basket gets broader.** The market return from counterforce 3 is the
  value-weighted return of **all tradable** baskets and bonds; the thirty venues belong to
  it, otherwise a tradable object outside the benchmark would be a gifted excess return. The
  bar the fund must clear thus rises with the layer — and "running broadly with the market"
  becomes even less viable than it was.

**Two counterforces thus bite on the new layer, both growing with success, and one expressly
does not.** That is the honest balance; it stands here so the break tester knows where to
look.

### Was die Schicht für die vier Maße bedeutet

**Maß 1 — decision density.** The tradable slots rise from 20 to **75**: 45 from the country
geometry at `L = 9` and 30 from this layer. The action count stays at three per round — the
operator chose path A on 2026-09-05, and the slots grow along. **The computation of how
decision density is preserved in this belongs in package 0118, and it must carry both
increases, not only the 45 from the countries.** The number it has to compute on is the 75
from this section, against today's 20. What belongs here and need not be repeated there:
each round Maß 1 draws 30 bundles from the list of **admissible actions**, and that list
grows with the slots. The open question *„Wie fein der Aktionsraum sein darf"* was so far to
be settled empirically on the prototype; with 75 slots it is **binding**, and its check form
is already there — `Dichte(t)` at `K = 30` against `K = 60`.

**Maß 2 — strategy diversity.** The 126 profiles remain 126: an exchange venue is a target
within family 1 (position), not a sixth action kind and not a fourth family. So the layer
enlarges the choice within **one** of the three families, and that is the objection one must
raise against it. **It does not hold, and the reason is the construction, not the
calibration:** venues deliver not a gram of influence, and the second half of the mandate
demands influence in two countries. Family 1 thus gets a higher ceiling for **capital** and
not a centimetre more toward the **win**. What the layer does genuinely shift is the second
acceptance half `max(Ek) ≤ 1,25 · min(Ek)` — from here on it is the sharp condition, and it
is the place where an oversized `platzanteil` calibration becomes visible.

**Maß 3 — shift of the optimum.** Here the design gains most, and at a spot where since
2026-09-03 it was openly declared weak. With the window 2001–2021 the euro transition
dropped away, the only lock that snapped shut during a game; since then Maß 3 rested on
**two** sources, imitators and the price shock, and this design has explicitly written down
that failing it would be a finding about those two. **The second layer is the third source,
and it comes from a rule rather than a number:** at the start of a game the fund has no
influence, so the unobserved, shallow, broad venue market is the efficient way to build
capital; toward the end of a game the second mandate half binds, and capital must be shifted
into stakes and lobbying pressure **in policy countries** — where it immediately wakes
supervision and the counter-lobby. That is a testable **prediction**, not a declaration of
intent: the early-window optimum `p*` should put weight on action kind 1, the late-window
optimum `q*` on 2 and 3. If it does not come true, that is a finding about this section.

**Maß 4 — backtest.** **Through this layer** it does **not** change, in any of its numbers.
*Corrected on 2026-09-06, because 0117 has since been built and the sentence no longer held
as it stood:* an exchange venue is **not a play-only country** — by T58 a play-only country
is a country with policy paths that may be estimated, and a venue has none at all. It simply
carries no target series and no trade row and appears in no check subject; the argument
below — *the layer is a pure leaf* — carries that on its own and does not need the class
assignment. So the sharpness of the backtest does not sink through the layer: it keeps
running over the same free target series and the same trade block, for a venue has no trade
row. **What does move it is the country choice from package 0118** — there the free target
series rise from 23 to 41, the check subjects from 16 to 28 and the flows of the trade block
from 40 to 112. That is the other axis and stands under *Welche neun
Länder*. Added to this is a property that is stronger than the class assignment and carries
it independently of it: **the layer is a pure leaf.** No field of the first or third layer
reads a field of an exchange venue; venue fields are read exclusively by the fund subsystem.
Since that subsystem does not run in the `weltlauf`, the second layer is **not computed at
all** there — its four fields per venue keep their start values, just as the fund block and
the imitator counters already do. After this layer the `weltlauf` costs not one world step
more than before, and the set of addresses written per mode stays fixed. The price of this
cleanliness belongs with it and stands under *Die Grenze des Orakels*: for the second layer
the oracle is completely blind. There is also nothing of it to check against — a world
equity index under a free licence does not exist, that already stands under *Was
bewusst fehlt*, and `daten.md` carries not a single price series.

### Die drei Klagen, auf dieser Schicht gelesen

| Complaint from the reviews | what the second layer contributes to it |
|---|---|
| „the consequences of choices often feel intangible" | The coupling is a formula the player can trace along the chain: tariff step → world price → `durchgriff` → the anchor's sector price → `leitkurs` → `index[b]`. An action in one country visibly moves a price thirty slots away — and because `weltzins` reaches every venue, an interest-rate step has an effect one can read off **worldwide**, without anything being narrated. |
| „trying to implement the tiniest socialist policy will always result in bankruptcy" | On every venue, long and short are the same formula with the sign reversed. The layer brings no political direction with it; it cannot win in any direction on its own, because it delivers zero influence. It thus broadens the position family without rewarding any political line. |
| „no dramatic setbacks", „broad as an ocean, but deep as a puddle" | The layer is exactly the breadth the complaint misses — and it comes with a trap instead of being free: whoever grows large on the shallow venues moves the price against themselves, gathers imitators and at the same time raises the bar of the market basket on which their investor base hangs. The setback is mechanical and readable in the state, like every other one here. |

## Die Gegenkraefte

Five, each grows with success, each as a mechanism and not as an intention.

**1. Supervision.** Per country one counter that rises every round by an amount
following from global visibility times local footprint (influence times position share
in the sector) — **not from wealth alone**, or it would be nothing but a wealth tax.
Three thresholds: at the first, the instrument „Finanzmarktregulierung" moves against
the fund, independently of the fund's lobby budget and with precedence over it. At the
second, the stake is force-sold, at a discount. At the third, a market ban holds in that
country for several rounds. Grows with success, because influence and share are exactly
what the mandate demands.

**2. Political backlash via real income.** Every lobby action pushed through shifts
prices and with them real income. If real income falls, approval falls; below a
threshold the government changes, the new one resets **all** instruments toward their
historical mean and doubles the fund's lobby costs for several rounds. Grows with
success, because successful lobbying produces exactly the shift that lowers approval.
That is the idea's chain of effect, closed here into a circle instead of an arrow.

**3. Market thinness.** The fund lives on investor money, and investors compare its
return with a market return. That market return is the **value-weighted return of all
baskets and bonds tradable in the model, at model market values** — weighted by the
market, **not by the fund's holdings**. It has no data anchor of its own; its start
value is the value of the start basket at start prices, its continuation is model
(`technik.md` T33).

The power of this counterforce lies **in the price shock, not in the definition of the
benchmark**: the larger the fund's share of a market, the more strongly every entry and
exit moves the price against it, the more expensive every reallocation becomes. If the
excess return stays below zero for three rounds, a fixed share of investors withdraws,
forcing sales into a market the fund itself moves.

**And the way out belongs to it, or this would be no counterforce but a death sentence
on size:** the fund beats a broad market through **concentration and causation** — stake
and lobbying raise the value of *its* baskets more than the market average. Whoever
merely runs along broadly loses against their own cost threshold; whoever shifts the
fundamentals of their position also wins big. Exactly that is the link between the two
halves of the mandate.

**4. Imitators.** For every position that yields excess return over several rounds, an
imitator counter rises on that country×sector. Imitator capital enters as a
counter-position, raises the entry price and lowers the future return of the same
position. Every working strategy is thereby **self-consuming**. That is not balance,
that is the rule Maß 3 enforces: what was optimal in the first third is grazed bare in
the last.

**5. Counter-lobby.** Influence is relative to the sum of all lobby pressure on an
instrument. Whoever pushes something through damages another sector — and that sector's
counter-budget grows by `gegenlobby_satz` lobby points per 10.000 thousand USD of damage
suffered. The more strongly one shifts in a direction, the more expensive the next step
in the same direction becomes. The feedback that runs upward in the genre runs against
itself here. **Which number this damage is stands in the next section.** Until
2026-09-02 only the adjective stood here, and a counter-budget that grows „proportional
zu" something, without the quantity being named, is not a counterforce but an intention
— exactly the kind of sentence the head of this section stands against.

### Der Schaden in Gegenkraft 5, als Rechenvorschrift

`technik.md` T50 fixed the **unit** of the damage — economy-wide, thousand USD, scale
class 2, transition into lobby points via
`lobbypunkte_aus_schaden(tsd) = mal_geteilt(tsd, gegenlobby_satz, 10.000)` — and expressly
handed the **magnitude** back here, with the right reasoning: had the architect filled the
gap, Maß 2 would be measuring the architect's choice. It is filled here.

#### Die eine Regel

> **The damage of an instrument is the shift of the price it sets, times the quantity
> that price acts on — both measured at the round boundary.**

Four instruments, four prices, four quantities, one computational form. **„The price it
sets" is, for the tariff, the wedge and not the sector price** — the sector price arises
from world price, wedge and price inertia, and only the wedge has the instrument as its
cause. Since 2026-09-03 the tariff row therefore measures the wedge; the reasoning
stands two sections further down.

For each of the four countries `l` and each of its four instruments `i`:

```
schaden(l, i) = mal_geteilt( menge(l, i), verschiebung(l, i), 10.000 )      [Klasse 2]
```

The building blocks, all from the state and the vintage, none of them a new address:

```
hub(l, i)           = | lies_neu(land.<l>.instrument.<i>.stand)
                      − lies_alt(land.<l>.instrument.<i>.stand) |

keilhub(l, s)       = mal_geteilt( lies_neu(welt.preis.<s>), hub(l, zoll), 10.000 )

preishub_zoll(l, s) = mal_geteilt( keilhub(l, s), durchgriff(l, s), 10.000 )

handelsvolumen(l,s) = Σ über die vier Gegenüber g:
                        lies_neu(handel.<l>.<g>.<s>) + lies_neu(handel.<g>.<l>.<s>)

bip(l)              = Σ über die drei Sektoren  lies_neu(land.<l>.sektor.<s>.wertschoepfung)
schuld(l)           = mal_geteilt( bip(l), lies_neu(land.<l>.staatsschuld), 10.000 )
```

`bip` and `schuld` are numbers 9 and 10 from `technik.md` T48, taken over unchanged.
`handelsvolumen(l, s)` is the sector-wise version of number 11; its sum over the two
tradable sectors is the old quantity. None of these names is a state address — they are
functions of the state, the same construction as `korbwert` in the section *What a basket
is worth*. `durchgriff(l, s)` is not a state quantity but one of the fourteen
**vintage constants** (`technik.md` T23 point 5), fixed over the game.

**`keilhub` and `preishub_zoll` are new since 2026-09-03 and replace `preishub`.** The
previous version read the full shift of the sector price; why that was the wrong quantity
and why this one is right stands under *Warum die Zollzeile nur den Keil misst*.

Thus the four rows:

| Instrument | `verschiebung(l, i)` | Class | `menge(l, i)` | `schaden(l, i)` |
|---|---|---:|---|---|
| `zoll` | `preishub_zoll(l, s)`, per tradable sector separately | 5 | `handelsvolumen(l, s)` | `Σ` over s ∈ {1, 2}: `mal_geteilt(handelsvolumen(l,s), preishub_zoll(l,s), 10.000)` |
| `leitzins` | `hub(l, leitzins)` | 3 | `schuld(l)` | `mal_geteilt(schuld(l), hub(l,leitzins), 10.000)` |
| `haushalt` | `hub(l, haushalt)` | 3 | `bip(l)` | `mal_geteilt(bip(l), hub(l,haushalt), 10.000)` |
| `regulierung` | `hub(l, regulierung) · regulierung_last` | 10 × 3 | `bip(l)` | `mal_geteilt(bip(l), hub(l,regulierung) · regulierung_last, 10.000)` |

The third sector contributes zero in the tariff row because it has neither a trade row
nor a world price and carries `durchgriff = 0` per T28 — three reasons, each sufficient
on its own; whether one sums over two or over three sectors does not change the number.
`welt.preis.<s>` exists only for s ∈ {1, 2} anyway.

#### Warum die Zollzeile nur den Keil misst

**The decision, in one sentence:** of the shift of the sector price, **only the part the
tariff step caused** counts as damage — the rest is business cycle and does not belong
in a counterforce.

Until 2026-09-03 the full shift stood here, and that was wrong. The proof is two lines
long and comes from the price-formation rule above:

```
preis_neu − preis_alt = durchgriff/10.000 · ( weltpreis_mit_zoll_neu − preis_alt )
```

The bracketed expression splits into two summands, and only the first has a causer:

```
weltpreis_mit_zoll_neu − preis_alt
    = welt.preis_neu · (zoll_neu − zoll_alt)/10.000        ← der Zollkeilanteil
    + ( welt.preis_neu · (10.000 + zoll_alt)/10.000 − preis_alt )   ← der Sockel
```

The second summand is exactly the shift that would have occurred **had the tariff level
not moved**. By the price-inertia rule above („domestic price follows the world price
with a one-year lag") it is nonzero by construction, in every round, without any action.

**The old quantity was the absolute value of the sum, the new one is the absolute value
of the first summand**, both times `durchgriff/10.000`. The difference is therefore not
a damping but a deletion: what falls away is the summand without a causer, and what
stays, stays unchanged.

**What the base term really is: inflation, times the trade volume.** `handelsvolumen`
stands per T5 in class 2 at constant prices, `preishub` was a nominal index — their
product is the nominal appreciation of the trade flow and thus, at its core, the
country's annual sector-price increase. Before this change, the tariff row **measured
inflation** and booked it as lobby damage.

**Three reasons, and the first alone suffices.**

1. **It hits Maß 2 at its most sensitive spot, and no calibration brings it back.** The
   family Lobby is the only one of the three whose counterforce is exclusively
   counterforce 5. A base term that arises without action is the same for every profile
   and avoidable for none — it pulls the baseline out from under exactly one of the
   three classes. `gegenlobby_satz` does not help, because it scales base term and
   action response together; whoever halves the base term halves the response with it.
   And influence is the fund's **share** of total lobby pressure, so an exogenously fed
   counter-pressure shifts that share permanently. The acceptance of Maß 2 reads
   `max(Ek) ≤ 1,25 × min(Ek)` over the three classes; a handicap that exactly one class
   carries and that grows with the price level over the game is the most obvious way to
   tear it — and it would fail not on a number but on the construction.
2. **It stands against this section's own reasoning.** The value-added loss is rejected
   below with the sentence: *„It is business cycle, not reaction … without a single
   lobby action having taken place."* The tariff row had the same property, and there it
   was not the exception but the rule. Treating two quantities with the same property
   differently is not design but an oversight.
3. **It makes the setback inexplicable, and that is the first of the three complaints.**
   Step 1 shows the previous round's chain. Under the old rule it read: *counter-pressure
   on the German tariff instrument +6.570, cause: damage 32.850.000 Tsd USD, cause: the
   sector price moved* — and behind that stands no action but the world market. Exactly
   that is what "the consequences of choices often feel intangible" means: not that too
   little happens, but that what happens does not hang on the player. The design
   promises in its title that every number says why it moves. The base term could not.

**And the side effect is the second piece of evidence that the old quantity was the
wrong one.** `technik.md` T8 rebases a country's three sector prices under hyperinflation
(division by 1.000), but `welt.preis.<s>` not — it hangs on no territory. A difference
`preis_neu − preis_alt` across such a rebasing is not the price shift but the base
change; it would have silently pushed the affected country's counter-pressure to
`druck_max`. That a difference needs this, the architect already knows: T42 computes
exactly this correction out for the backtest. The damage rule did not have it. In the
check vintage 2001 the case never occurs — in the play vintages before 2001, which this
design expressly retains, it does. **The new version differences only the tariff level
(class 3, never rebased) and reads the world price as a level; T8 cannot hit it.**

#### Die beiden anderen Wege, und warum sie es nicht sind

**Way 2 — read `hub(l, zoll)` like the three other rows.** It is cheaper and also
removes the base term. It fails in two places.

First, it makes the row blind to the sector effect. `schaden(l, zoll)` would then be
`mal_geteilt(handelsvolumen(l), hub(l,zoll), 10.000)` and would hang on the country
alone. But in the section *What must hold for price formation* the design justifies the
ordering `durchgriff` establishes: *„a tariff hits China's industry hard via its high
`durchgriff` and the US industry, dominated by construction and utilities, weakly"*.
Under way 2 it hits both equally hard per unit of trade volume. That is the same
self-contradiction as under 2 above, only in the other direction.

Second, it confuses a rate with a price. A tariff rate is not a price but a wedge; what
the buyer pays is the sector price. The policy rate, by contrast, **is** the price of
money, the fiscal balance **is** the share of output, and the regulation step becomes
such a share via its load rate. This distinction already stood in the version of
2026-09-02 and holds unchanged — it is the reason the tariff row **converts** the tariff
level instead of inserting it. Exactly that is what `keilhub` does: it translates a rate
in basis points at the world-price level into a shift in index points, and only
`durchgriff` lets through what arrives domestically.

**Way 3 — keep the base term and write it down.** It fails on reason 1: a written-down
construction error remains one. The base term is nothing calibration could still turn,
and it would also be harmful for Maß 3, not merely inconsequential: it grows with the
nominal price level over the game, so it systematically makes the family Lobby more
expensive in the last third of the game — a shift of the optimum that would arise **even
with the fund switched off**. Maß 3 would then have reached its threshold with a drift
of the world instead of a property of the game. A measure that can be worked like that
no longer measures.

#### Was die Entscheidung kostet, und was sie nicht kostet

**It does not cost:** a new state address (`welt.preis.1` and `welt.preis.2` are numbers
239 and 240 in `daten/adressen.md`), a new series, a fourth scale transition, a ninth
channel or a second market clearing. And it costs **nothing in signal**: the action
share of the damage is the same as before, only the base term falls away. The
decomposition above is algebraically exact, not approximate; only the rounding paths
differ — the old row rounded once into the stored sector price and once into the damage,
the new one twice between world price and damage. A difference of a few index points, no
difference in order of magnitude.

**It costs:** the damage a *foreign* tariff does domestically. A German industrial
sector hit by an American tariff step via the world price no longer generates
counter-pressure in Germany, because `hub(DE, zoll)` is zero. That stands under *Was
bewusst fehlt*, and the channel is not severed but rerouted: the foreign tariff step
raises the German sector price, lowers real income, lowers approval and, via
counterforce 2, triggers a change of government that resets **all four** German
instruments and thereby generates damage via `hub`. That is threshold-driven instead of
continuous, and the difference deserves naming — but it is the same path the design
provides for price effects anyway.

**One condition that follows from this and that the vintage build must check.**
`preishub_zoll` arises from two roundings. If the smallest possible tariff step is too
small, the row rounds to zero for a country×sector pair, and the counterforce is **mute
there without saying so**. What must hold, as a form and without a number:

```
mal_geteilt( mal_geteilt(welt.preis_start(s), schrittweite[zoll], 10.000),
             durchgriff(l, s), 10.000 )  ≥  1     für jedes Land×Sektor des Jahrgangs
```

The value of `schrittweite[zoll]` that satisfies this is calibration and does not stand
here; that the condition is checked is design and stands here.

#### Zwei Zustände, zwei Zahlen

The same probe as in package 0021, now on the row that had none there. The two states
differ in **exactly one** quantity, the tariff level.

| Quantity | State A (one tariff step) | State B (no action) |
|---|---:|---:|
| `handelsvolumen(DE,1)` / `(DE,2)` (Tsd USD) | 40.000.000 / 100.000.000 | the same |
| `durchgriff(DE,1)` / `(DE,2)` (vintage) | 7.288 / 5.464 | the same |
| `lies_neu(welt.preis.1)` / `(welt.preis.2)` | 11.000 / 10.400 | the same |
| `…instrument.zoll.stand`, `lies_alt` → `lies_neu` | 380 → 430 bp | 380 → 380 bp |
| `lies_alt(…sektor.1.preis)` / `(…sektor.2.preis)` — only the previous version reads it | 10.000 / 10.000 | the same |
| `hub(DE, zoll)` | 50 | **0** |
| `keilhub(DE,1)` / `(DE,2)` | 55 / 52 | 0 / 0 |
| `preishub_zoll(DE,1)` / `(DE,2)` | 40 / 28 | 0 / 0 |
| Contribution sector 1 / sector 2 | 160.000 / 280.000 | 0 / 0 |
| **`schaden(DE, zoll)`** | **440.000** | **0** |

Recomputed with `mal_geteilt` and the rounding rule from T6 (halves away from zero):
`11.000 · 50 / 10.000 = 55` exactly; `7.288 · 55 / 10.000 = 40,084 → 40`;
`5.464 · 52 / 10.000 = 28,4128 → 28`; `40.000.000 · 40 / 10.000 = 160.000`;
`100.000.000 · 28 / 10.000 = 280.000`.

**The row `lies_alt(…sektor.<s>.preis)` enters no number in the columns below it.** It
stands only for the comparison at the end of this section: the current tariff row no
longer reads `land.<l>.sektor.<s>.preis` — that is the decision —, the previous version
read it as its only state input. Its value is the start value of the price-inertia rule
above, hence round 1.

**State B is the acceptance, and it can be recomputed without any knowledge of the wedge
form.** If the tariff level does not move, `hub` is zero, hence `keilhub` zero, hence
`preishub_zoll` zero and hence `schaden(l, zoll)` **exactly zero** — for every world
price, every price inertia and every trade volume. For comparison, the same row in the
**previous version**, applied to the same state B and computed solely from the
quantities in the table above, with `mal_geteilt` and the rounding rule from T6:

```
wmz(DE,1)      = 11.000 · (10.000 + 380) / 10.000              = 11.418
preishub(DE,1) = |11.418 − 10.000| · 7.288 / 10.000 = 1.033,4384 →  1.033
Beitrag 1      = 40.000.000 · 1.033 / 10.000                   =  4.132.000
wmz(DE,2)      = 10.400 · (10.000 + 380) / 10.000 = 10.795,2   → 10.795
preishub(DE,2) = |10.795 − 10.000| · 5.464 / 10.000 =   434,388 →    434
Beitrag 2      = 100.000.000 · 434 / 10.000                    =  4.340.000
                                                     Summe     =  8.472.000
```

**8.472.000 instead of zero**, and that is more than **nineteen times** what the
deliberately taken tariff step in state A generates (440.000). Exactly this quantity
falls away with the decision, and it accrued without action, in every round and equally
for every profile. The only rounding one could place differently here is the
intermediate value `10.795,2`; it decides nothing — carried on unrounded,
`795,2 · 5.464 / 10.000 = 434,49728 → 434`, the same number.

**With this, the same sentence holds for all four rows**, and that is the real effect of
this decision: *the damage of an instrument is nonzero exactly when the instrument moved
in this round.* Before, it held for three of four.

That an instrument can move without a player action remains possible — a change of
government resets all four. That is no exception to the sentence but the same chain one
step later, and it hits all four rows equally; see *Does it grow with success?*.

#### Wer geschädigt wird, und an welche der 16 Adressen es fließt

| Instrument | who bears the damage | why this quantity |
|---|---|---|
| `zoll` | the country's two tradable sectors and their counterparts in trade, on the import as on the export side | the wedge acts on the goods that cross the border — hence the trade flow in both directions, and hence only the shift the wedge itself generates |
| `leitzins` | the state as debtor and, via its budget, all three sectors | the interest is paid on the debt stock, not on output |
| `haushalt` | the recipients of government services, i.e. all three sectors by value-added share | the balance stands in basis points **of GDP**; the quantity is therefore GDP |
| `regulierung` | the financial trade in sector 3 and, via capital costs, the rest | the state carries no financial sector; GDP is the coarsest honest quantity |

**The assignment in one sentence:** the damage is computed **per country from that
country's quantities** and settles on the instruments of the **same** country —
`land.<l>.instrument.<i>.gegendruck`, four countries times four instruments, the sixteen
addresses. Every single one is thereby derivable: whoever opens
`land.BR.instrument.leitzins.gegendruck` computes
`mal_geteilt(schuld(BR), hub(BR, leitzins), 10.000)` and then `lobbypunkte_aus_schaden`
on it.

**The rule behind it stays: a counter-lobby forms where it can act**, at its own
legislator and not at the foreign one. What it achieves there is resistance against
movement, not retaliation — see *Was bewusst fehlt*.

**Since 2026-09-03, however, this rule holds for the tariff only for the own step.**
Until then the tariff row also carried the damage a *foreign* tariff did domestically
via the world price; with the base term it falls away, for it hangs on the world price
and not on the own wedge. Bringing it back would mean isolating the general-equilibrium
share of a tariff step, and that takes a **second market clearing** per round — the
model's most expensive computation once more, for a state that does not exist. It
therefore stands under *Was bewusst fehlt*, with the path by which it arrives anyway.

#### Wie das Gegenbudget wächst und wieder vergeht

In step 5, for all sixteen addresses, exactly once per round:

```
gegendruck_neu(l, i) = min( druck_max,
                            teile_gerundet( lies_alt(land.<l>.instrument.<i>.gegendruck), 2 )
                            + lobbypunkte_aus_schaden( schaden(l, i) ) )
```

**The halving is a rule and not a calibration number**, and that is a decision against
an obvious parameter. A decay rate next to `gegenlobby_satz` would be exactly redundant
for the steady state: under constant damage `D` the counter-pressure runs toward
`2 · lobbypunkte_aus_schaden(D)`, and a free rate would only shift which of the two
numbers carries that value. The two would differ only in the transient — a calibration
dimension that shapes nothing but the transition costs the night run over a thousand
parameter sets a whole axis and gains nothing on any Maß. The statement of the halving
is substantive and checkable: *an opponent that goes one round without new damage loses
half its budget.*

**A counter-pressure without decay would be no decay but an end state.** It would run
toward `druck_max` in every country the fund touches and stay there; the strategy family
Lobby could move nothing in the last third of the game, and Maß 2 would fail not on a
calibration but on the construction. Conversely, a pure inflow without carry-over would
be too mild: whoever alternates lobbying with something else would meet a
counter-pressure of zero every second time. The halving is the smallest version that
avoids both.

#### Warum diese Lesart und nicht die beiden anderen

`technik.md` section 12 names three: **price shift times quantity**, **value-added
loss**, **valuation loss**. Chosen is the first, and the other two do not fail on taste.

**The value-added loss** — `wertschoepfung_alt − wertschoepfung_neu` — is the simpler
formula and the wrong quantity, for three reasons, of which the first suffices:

1. **It is blind to the tariff.** Class 2 stands per T5 in *Tausend USD zu konstanten
   Preisen des Basisjahrs*. Value added is thus a **real** quantity; a tariff shifts
   prices, not real quantities — at least not in the same round, for the real path runs
   via investment and capital stock and is channel 1. The tariff is the only instrument
   channel 3 names at all, and the only one with a data anchor in the trade block. A
   damage quantity that does not see it measures the wrong chain.
2. **It is business cycle, not reaction.** In a growth year it is zero for all twelve
   country×sector pairs, in the slump year 2008 or 2020 large for all twelve at once —
   without a single lobby action having taken place. Counterforce 5 would then be no
   force that *grows with success* but business-cycle noise with lobby effect, and the
   requirement from the head of this section would be missed.
3. **It cannot be assigned to any instrument.** One difference, four instruments: any
   split across the sixteen addresses would be invented.

**And the sentence that points at Maß 2:** the family Lobby is the only one of the three
whose counterforce is exclusively counterforce 5 — Position is braked by price shock and
imitators, Stake by supervision and illiquidity. A counterforce that does not answer the
player's action is none for this family, and the family without a price dominates. Maß 2
demands `max(Ek) ≤ 1,25 × min(Ek)` over the three classes; that is the same defect the
review describes from the other side as „trying to implement the tiniest socialist
policy will always result in bankruptcy", and here it falls in the other direction.

**The valuation loss** fails twice, and the first reason is the heavier one:

1. **It is a fund quantity and would couple the counterforce to failure.** If the fund
   loses, the counter-lobby grows; if it wins, it vanishes. That is the inversion of
   what a counterforce of this design must do, and it would not damp channel 8 but
   amplify it.
2. **It costs a fourth scale transition.** It stands in class 1 (US cents),
   `cent_in_tsd` expressly does not exist per T50, and retrofitting an inverse function
   is an ADR against T50 and not a sentence in `spiel.md`.

If one instead reads "valuation loss" as the change of the **sector basket** —
`korbwert(l,s)`, class 2, hence admissible under the scale rules —, then it is almost
the chosen rule, with `kapitalstock` instead of `handelsvolumen` as the quantity and an
additional term for the capital-stock change. Exactly that term is the objection: it
belongs to channel 1 and would be booked a second time in channel 3. The trade flow is
the quantity the tariff wedge touches; the capital stock is not.

#### Wo die Regel läuft, und warum Kanal 3 zyklenfrei bleibt

Computed in **step 5**, the place T50 fixes as the only call site of
`lobbypunkte_aus_schaden` — sixteen calls per round, all here. Read:

| from where | addresses | count | for which row |
|---|---|---:|---|
| step 3 | `lies_neu(land.<l>.instrument.<i>.stand)` | 16 | all four |
| step 4 | `lies_neu(welt.preis.<s>)`, s ∈ {1, 2} | 2 | `zoll` |
| step 4 | `lies_neu(handel.<a>.<b>.<s>)`, the whole trade block | 40 | `zoll` |
| step 4 | `lies_neu(land.<l>.sektor.<s>.wertschoepfung)`, for `bip` | 12 | `leitzins`, `haushalt`, `regulierung` |
| step 4 | `lies_neu(land.<l>.staatsschuld)`, for `schuld` | 4 | `leitzins` |
| previous round | `lies_alt(land.<l>.instrument.<i>.stand)` | 16 | all four |
| previous round | `lies_alt(land.<l>.instrument.<i>.gegendruck)` | 16 | all four |

`16 + 2 + 40 + 12 + 4 + 16 + 16 =` **106 read accesses**, 16 write accesses, **no new
address**. Counted are distinct addresses, not access events — the trade block therefore
stands at 40 and not 64, because a flow between two playable countries enters two
`handelsvolumen`. Every quantity read stands in `daten/adressen.md`, `welt.preis.1` and
`welt.preis.2` as numbers 239 and 240; `bip`, `schuld` and `handelsvolumen` are
functions of them and not fields, `durchgriff` is a vintage constant. The number 310
stays, and the counting step from T45 still comes out unchanged.

**The number has been wrong twice, and the correction belongs to the decision.** The
version of 2026-09-02 named 120 and counted the tariff level twice with 16, although the
tariff row did not read it at all back then — check finding 2 found that and computed
112. After this decision the tariff reads its level again, in exchange both sector-price
rows (`lies_neu` and `lies_alt`, 8 each) fall away without replacement and the two world
prices are added: `112 + 4 + 4 − 8 − 8 + 2 = 106`. Both numbers of the previous versions
are thereby superseded, and the catch-up table at the end names the same 106.

**The round boundary is the solution, not a second set of addresses.** A damage that
compared the state before the instrument step with the one after would need shadow
addresses; the comparison of `lies_neu` against `lies_alt` needs none, because the
writer keeps both levels anyway per T39.

**Channel 3, walked through:** instrument (step 3, `stand`) → trade (step 4, `handel`) →
world price (step 4, market clearing) → damage (step 5, here) →
counter-lobby budget (step 5, `gegendruck`) → instrument (step 3 of the **following
round**). Exactly one round boundary is crossed, and it is not promised but enforced:
step 3 must read `lies_alt(gegendruck)`, because the address is not yet written in this
round and `lies_neu` on it would be a hard error per T39. The damping „counter-pressure
acts only in the following round" is thereby a property every run proves.

**`welt.preis.<s>` is read but not differenced, and the difference is the whole point.**
The previous version excluded the world price with the argument that it is the same for
all territories and cannot distinguish who was hit. The argument still holds — and it
does not hit the new row, because no world-price *difference* stands there. Distinction
comes from `durchgriff(l, s)`, `handelsvolumen(l, s)` and `hub(l, zoll)`, all three
country- or country-sector-specific; the world price supplies only the **level** at
which a rate in basis points becomes a shift in index points. A level can single out no
one and is not meant to.

**And it is no ninth channel.** The tariff level now reaches the damage by two paths
instead of one: via the quantity (instrument → trade → `handelsvolumen`) as before, and
newly via the shift (instrument → `hub` → damage). Both are links of channel 3, the
second is the first without its detour. The damping is unchanged the same and unchanged
enforced: `gegendruck` is written only in step 5, `lies_neu` on it in step 3 is a hard
error per T39, so the path crosses exactly one round boundary. Within the round the
order 3 → 4 → 5 stays cycle-free.

#### Die Skalenprobe

Class 5 (price index) and class 3 (basis points) are both **ten-thousandths**, and class
2 stands at constant prices of the base year. For a real quantity `Q` and a price index
`P` the nominal value is `Q · P / 10.000`; if the price shifts by `ΔP`, the value shifts
by `Q · ΔP / 10.000`. That is the formula, character for character. For the interest row
the same computation with a rate instead of an index: debt stock times rate change in
basis points divided by 10.000 is the additional debt service of one year, in thousand
USD. **Class 2 times ten-thousandths divided by 10.000 yields class 2**, and this result
goes unchanged into `lobbypunkte_aus_schaden`. A fourth scale transition arises nowhere.

**Since 2026-09-03 the tariff row has two intermediate steps instead of one, and both
hold the class.** `keilhub` is class 5 times class 3 divided by 10.000, hence class 5
again — the shift of the tariff-laden world price in index points. `preishub_zoll` is
class 5 times class 4 (`durchgriff`, ten-thousandths) divided by 10.000, hence class 5
once more. Only the last step leaves the index world, and it is the same as in the three
other rows: class 2 times ten-thousandths divided by 10.000 is class 2. **No fourth
scale transition, and class 1 is touched nowhere** — the tariff row's classification in
the instrument table remains class 5, as in the previous version.

On overflow: the largest factor is `bip(US)`, per T5 of order `2,1 · 10^10` thousand
USD; times a shift in ten-thousandths, the intermediate result stays far below the
`i64` limit, and `mal_geteilt` computes over `i128` per T6 anyway. The tariff row stays
below that: `welt.preis` is an index of order 10^4, `hub(l, zoll)` is bounded by
`instrument_max[zoll]`, `keilhub` and `preishub_zoll` are thus index quantities
themselves; the largest product is `handelsvolumen · preishub_zoll` and, at a trade flow
of order 10^9, lies around 10^13.

#### Was Gegenkraft 5 im Weltlauf tut

**Nothing, and that is already decided.** In mode `weltlauf` the fund subsystem does
not run; of step 5 only approval and change of government run, counterforces 1, 3, 4
and 5 are not computed. `gegendruck` belongs per `technik.md` T38 to the block
*Instrumente ohne Stand* and stands there on **nein**: the address is not written and
keeps its start value 0. This computation rule is not evaluated in the weltlauf.

That is no loss but the condition of the measure. The policy instruments are exogenous
in the weltlauf; a counter-pressure would have no addressee there, and regulation, whose
damage row is the only one without a data anchor anyway, stands fixed at its start
value. The formula's inputs — instrument levels, **world prices**, trade block, value
added, government debt — all stand in the weltlauf mask (`technik.md` T38 carries the
world prices there with **ja**); the sector prices the previous version still needed
have not stood in the formula at all since 2026-09-03. The computation *could* therefore
run along. Writing it would break the mask, and an output beside it is the test stand's
business and not a design question.

**The consequence, named expressly: Maß 4 does not check this rule.** It is checked by
Maß 2 (does the family Lobby stay within the 25 percent?), by Maß 3 (does the best
profile shift between early and late window?) and by the break tester via the invariant
`0 ≤ gegendruck ≤ druck_max` from T30 check 6. Whoever changes a number of this rule
sees the effect in self-play and nowhere else.

#### Was diese Regel für Maß 2 und Maß 3 leistet

**One rate, four quantities.** `gegenlobby_satz` holds equally for all sixteen
addresses; what differs is the quantity it engages — and that stands not in
`parameter.toml` but in the vintage. The four countries are chosen above for structural
difference (*Warum vier Länder und nicht drei*), and exactly this difference now carries
a price: whoever has an export surplus has an expensive tariff row; whoever pays high
interest on high debt, an expensive interest row. **Which instrument is cheap to move
thus hangs on the country and not on a balance number.** That is the construction this
design has documented at Democracy 4: effect from loaded tables, not from programmed-in
exceptions.

**And the tariff row is the only one with structure below the country.** `schuld` and
`bip` know only the country; the tariff row computes per country **and sector**, because
`durchgriff(l, s)` and `handelsvolumen(l, s)` do. That is the reason the decision of
2026-09-03 falls on the wedge and not on the bare tariff level: a tariff whose price no
longer depends on which sector it hits would be, for Maß 2, a fourth row of the same
kind instead of one of its own.

**And the quantities move over the game.** `handelsvolumen`, `schuld` and `bip` are
endogenous quantities on a historical path, and the four breaks the cut above expressly
kept in the window — WTO accession 2001, 2008, 2020, recovery 2021 — all run through
trade, government debt or output and thus through exactly these three quantities. Since
2026-09-03 the **level** at which the rate engages moves in the tariff row as well:
`welt.preis.<s>` is just as endogenous, and the same tariff step costs more on a more
expensive world market. The cheapest lobby target of round three is therefore not
necessarily the cheapest of round twenty — a **third** source of optimum shift beside
imitators (counterforce 4) and price shock (counterforce 3), and this time one that
comes from the vintage instead of from a rule. *In which direction and how strongly* is
measured by the vintage build and then the test stand; this design does not claim it.

Added to this is the asymmetry that already stands and now has a quantity behind it:
Germany has no policy-rate lever of its own — since the window cut to 2001, over the
whole game instead of from round 3. The interest row is closed there, whatever it would
cost, and the way out leads through an instrument with a different quantity. A closed
action space that forces another — that is what the asymmetry above was chosen for, and
counterforce 5 now gives it a price instead of only a lock.

**Does it grow with success?** Yes, on two paths. The first is the intended one: an
instrument moves deliberately only through action 3, whose effect grows with the fund's
wealth (channel 8) — more success, more movement, more damage, more counter-pressure.
The second is an interlocking with counterforce 2: a change of government resets **all**
instruments toward their historical mean, thereby generates damage on all four in one
round and lays counter-pressure on all four in the following round. That is not chance
but success one step later: the change of government is itself the consequence of
successful lobbying. That this makes two penalties out of one cause stands under
*Offene Entwurfsfragen*.

## Wie die vier Masse berechnet werden

All four run in self-play without rendering, over the same state interface. What stands
here is a calculation rule; wherever a choice would have remained open, it is made here.
Every tie is broken by action id or profile id, never by discovery order. The median over
an even count is the smaller of the two middle values. **R = 20.**

### Die Ergebnisgröße einer Partie

An `i64` in milli-rounds, **smaller is better**, strictly ordered and without a catch-all
value:

| Outcome | Value | Range at R = 20 |
|---|---|---|
| mandate fulfilled in round r | `r × 1.000` | 1.000 … 20.000 |
| survived R rounds, mandate not fulfilled | `(R+1) × 1.000 + v + e`, see **Der Fehlbetrag** | 21.000 … 24.000 |
| died of a way of dying in round d | `30.000 + (R + 1 − d) × 1.000` | 31.000 … 50.000 |

#### Der Fehlbetrag, und wie „fehlender Einfluss" über die Länder gerechnet wird

The shortfall is `v + e`, both in per mille of the respective mandate threshold
(`schwelle_v`, `schwelle_e` from `parameter.toml`):

```
v = teile_gerundet(max(0, schwelle_v − fondsvermoegen) · 1.000, schwelle_v)

e = Summe über die zwei Länder mit dem höchsten Einfluss (Gleichstand nach LandId) von
    teile_gerundet(max(0, schwelle_e − einfluss[land]) · 1.000, schwelle_e)
```

**Two countries because the mandate demands two, and the fund's own two best because a
fund should not pay for countries it never wanted to enter.** Of the three obvious
readings — sum, mean, weaker of the two — the sum is chosen: it measures the **remaining
work**. A fund with one country at target and one at zero (0 + 1.000) and one with two
countries at half each (500 + 500) are equally far from the mandate, and that is exactly
what the sum says. The mean orders identically — it is the sum halved —; the weaker of
the two does not: it would declare the halved fund distinctly closer and thereby reward a
breadth the mandate does not demand.

**Nothing is capped, and nothing needs to be capped.** By build `einfluss` lies in
0 … 100, so each of the two summands in `e` is in 0 … 1.000 by construction and thus
`0 ≤ e ≤ 2.000`; in the band „survived" the fund is alive, so `fondsvermoegen > 0`
(otherwise way of dying 1 would have struck in the same round) and thus
`0 ≤ v ≤ 1.000`, where only rounding reaches 1.000. From this follows
`0 ≤ v + e ≤ 3.000` and the band 21.000 … 24.000 — computed, not decreed. The cap of the
third version was the substitute for a missing aggregation rule; with the rule it is
dropped, and it was harmful: it would have put every fund with less than one threshold of
total influence on the same value 1.000 — flattening the lower half of the outcome space,
precisely where Maß 3 seeks its argminimum when no profile in the window reaches the
mandate.

**With this, `spiel.md` and the bot objective `B` from `technik.md` T44 compute the same
formula in this branch** — the deviation justified there (T44 does not cap, because
capping made the bot blind in the early phase) disappears, because here too nothing is
capped. `B` stays bot-internal; the band check continues to apply only to the game
result.

**The bands remain disjoint, the upper one too:** „survived" ends at
`(R+1) × 1.000 + 3.000`, the death band begins at `31.000`; they are disjoint exactly for
`R ≤ 26`. That is **the same bound** that `technik.md` T40 already draws into the vintage
build — it remains valid unchanged, but is now tight instead of generous, and the wider
band costs no round of game length. At R = 20 the unreachable gaps are
20.001 … 20.999 and **24.001 … 30.999**; between the end of „survived" and the start of
the death band lie 7.000 milli-rounds of air.

**The edge from finding 10 is thereby closed:** the band 1.000 … 20.000 means exactly
„mandate fulfilled", the survived failure begins at 21.000, and no value carries two
meanings. The early death is worse than the late one, and by full rounds — exactly the
resolution Maß 1 needs in the last game third. A catch-all cap on the total value does
**not** exist. The range test reads: a result outside 1.000 … 50.000 is a hard error.

### Das Aktionsprofil und wie es auf Aktionen wirkt

An **action profile** is the distribution of the round budget over the five action kinds
on a fifth grid, i.e. a vector `(a1…a5)` with `ai ∈ {0…5}` and `Σai = 5`. That makes
`C(9,4) = 126` profiles. The **reference profile** is `(1,1,1,1,1)`.

The profile is a tool of the test stand, not a game quantity — the human chooses freely.
How it acts on actions was not stated in the second version, and Maß 2 and Maß 3 rest
entirely on it. **The stock procedure, binding:**

Each kind `i` keeps an integer stock `vi`, zero at game start.

1. **At the start of the round:** `vi += 3 · ai` for all five kinds. The total thus grows
   by 15 per round.
2. **For each of the round's three slots, one after another:** among the kinds that still
   have at least one admissible action this round, pick the one with the largest `vi`; on
   a tie, the smaller id. Place one action of this kind and compute
   `vi −= 5`. If no kind has an admissible action, the slot stays empty and no stock is
   charged.
3. **Which** action within the chosen kind is placed is decided by the bot: the heuristic
   bot by its fixed ranking, the search bot by search.

Three questions the reviewer rightly asked are thereby answered. The bot fills **all
three slots** as long as admissible actions exist; the bundle size is not part of the
profile. `ai = 0` does **not forbid the kind** but pushes it to the back — a hard ban
would leave profiles with zeros unable to fill their slots and would turn Maß 2 into a
comparison between three and fewer-than-three actions per round instead of between
strategies. There is never rounding and never a random draw: **after `5k` rounds the
stock vector stands at `(0,0,0,0,0)` again, and kind `i` has received exactly `3k·ai` of
the `15k` slots** — for `k = 1` that is `3·ai` of fifteen after **five** rounds, for
`k = 3` `9·ai` of forty-five after fifteen. Between two such points the deviation is
bounded. **Since `R = 20` the end of the game is itself such a point** (`k = 4`): a run
that plays the same profile for a whole game assigns `12·ai` of the 60 slots exactly by
profile — see *The game length R*.

As a check, the reference profile: rounds 1 to 5 assign the kinds
1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,5 and stand at `(0,0,0,0,0)` again afterwards —
exactly three of fifteen slots per kind, evenly distributed and deterministic.

**For the search bot** the profile fixes the kind composition of the round bundle; the 60
candidate bundles arise from the admissibility list ordered per T32, **restricted to
exactly this composition**, and drawn per T35. The search bot thus searches over targets
and steps, never over kinds.

### Maß 1 — Entscheidungsdichte

**Input:** 50 seeds, per seed one carrier game with the heuristic bot on the reference
profile.

For every round `t = 1 … R` and every seed: draw **30 action bundles**. A bundle arises
by first drawing the bundle size uniformly from `{0,1,2,3}` and then drawing that many
actions, uniformly and without replacement, from the list of actions admissible in this
round. Duplicate bundles in the sample set are **not** removed — otherwise the sample
size would depend on the state. The random seed follows from `(Jahrgang,
Parametersatz, Wurzelstartwert, t, Stichprobenindex)`.

The bundle **replaces the bot actions of round t**; round `t` is computed, then the
heuristic bot plays through to round `R` on the reference profile. The stock of the stock
procedure is carried forward for round `t` as if the bot had played the kinds of the
drawn bundle (`vi += 3·ai` at the round start, `vi −= 5` per action actually placed) —
otherwise the state of the counter after the injection would be undefined.

**Calculation:**

```
Ergebnis(t, s, k)      k = 1…30 Bündel, s = 1…50 Startwerte
Dichte(t, s) = Anteil der 30 Ergebnisse, die um mehr als 1.000 Milli-Runden
               vom Median dieser 30 abweichen
Dichte(t)    = Mittel der Dichte(t, s) über die 50 Startwerte
```

**Averaging over the seeds happens only at the end, and over densities, not over
results.** A common median over all 1.500 results of a round would be wrong: per
`technik.md` T11 different seeds produce different vintage spreads, and a median over
several worlds would drive the deviation share towards 1 without a single decision having
become denser.

**Acceptance:** the mean of `Dichte(t)` over each game third — the thirds are
`1…⌊R/3⌋`, `⌊R/3⌋+1…⌊2R/3⌋`, `⌊2R/3⌋+1…R`, at R = 20 thus **1-6, 7-13, 14-20** — each
**≥ 0,4**, not merely over the whole game. A game that lives only in the middle fails
here. If it fails, „the consequences of choices often feel intangible" has just been
measured.

**Cost.** A bundle in round `t` costs rounds `t … R`, i.e. `R + 1 − t` world steps —
Maß 1 measures the decision **of round t**, so it is counted in.

```
je Startwert:  30 · Σ(R+1−t) für t = 1…R  =  30 · R(R+1)/2  =  30 · 210 =  6.300
               zuzüglich Trägerpartie R                                 =     20
                                                                          ------
                                                                           6.320
50 Startwerte:                                                           316.000
```

### Maß 2 — Strategievielfalt

**Input:** all 126 profiles, 20 seeds each, search bot.

The profile result `E(p)` is the median of the 20 game results. A profile **wins** if
`E(p) ≤ R × 1.000 = 20.000` — that is, exactly when its median lands in the band
„mandate fulfilled".

The **strategy core** of a profile is the action kind with the largest share among the
three families `{1 Position, 2 Beteiligung, 3 Lobby}`; on a tie, the smaller id.
Leverage and visibility are amplifiers, not strategies, and do not enter the core.

**The six profiles `(0,0,0,a4,a5)` with `a4 + a5 = 5` have no strategy core.** They
contain not a single family action; assigning them class 1 via the tie rule would mean
counting a position strategy as fulfilled in which no position occurs. They run along,
their result is reported, and they enter **neither** of the two acceptance halves. That
leaves 120 profiles classified, spread over exactly three classes.

**Acceptance, both parts:**

1. **Each of the three classes provides at least one winner.**
2. Let `Ek` be the best (smallest) profile result of class `k`. Then
   `max(Ek) ≤ 1,25 × min(Ek)` must hold.

The second part is the more important one — otherwise three win but one dominates, and
that is the same defect under another name. This is the number behind „trying to
implement the tiniest socialist policy will always result in bankruptcy".

**Cost:** one search-bot game `R × (1 + 60) = 20 × 61 = 1.220`;
`126 × 20 × 1.220` = **3.074.400 world steps**.

### Maß 3 — Verschiebung des Optimums

Two separate runs per profile, each over the **full game**, so that no round is left
without a prescription. The windows are the first and last game third from Maß 1:

- **Early window:** rounds 1-6 with profile `p`, rounds 7-20 with the reference profile.
  Result `Efrüh(p)` = median over 20 seeds.
- **Late window:** rounds 1-13 with the reference profile, rounds 14-20 with profile `p`.
  Result `Espät(p)` = median over 20 seeds.

The profile switch happens at the round start; the stock of the stock procedure keeps
running across the switch and is not reset. Both runs use the search bot, inside as well
as outside the window.

`p*` = profile with the smallest `Efrüh`, `q*` = profile with the smallest `Espät`, ties
by profile id; all 126 profiles are eligible. **Shift** = `Σ|p*i − q*i| / 5`.

**Acceptance threshold 0,4.** Both vectors sum to 5, so the sum of absolute differences
is always even, and the shift takes only the values `{0; 0,4; 0,8; 1,2; 1,6; 2,0}`.
The threshold 0,5 of the second version in truth demanded 0,8, i.e. two shifted fifths;
what was meant and what is demanded is **one**.

The shift is forced not by balance but by counterforces 4 and 3: imitators graze off
every early position, the price shock devalues size. This is the number behind „already
the richest hedge fund in the game and nothing fun to do".

**Cost:** `2 × 126 × 20 × 1.220` = **6.148.800 world steps**.

**Sum of the three Maße:** `316.000 + 3.074.400 + 6.148.800` = **9.539.200 world steps**.
What the whole night run costs is in `technik.md` section 10 and not here — at this spot
the second version named a number that presupposed test-stand prescriptions it did not
itself make.

### Maß 4 — Rückvergleich

**The backtest is a `weltlauf`, not a game.** That is the answer to finding 2, and it is
a design decision, not an interpretation: a fund with zero assets divides by zero in
round 1 and, if you protect it from that, dies of investor withdrawal by round 3 at the
latest. Neither is a state in which a world machine can be checked.

In `weltlauf` mode, therefore:

- **The fund subsystem does not run.** Step 2 (actions) and step 6 (settlement) are
  dropped entirely; of step 5 only approval and change of government run. Counterforces
  1, 3, 4 and 5 are not computed; there is no return, no excess return, no investor
  base, no mandate and **no way of dying**. No field of the fund block and no imitator
  counter is written; they keep their start values.
- **The policy instruments are exogenous** and follow, round by round, the historical
  paths for policy rate, tariff level and fiscal balance. Every rule that would write an
  instrument — lobby pressure, counter-lobby, the instrument reset by a change of
  government — is not executed. A change of government is computed and reported but
  remains without effect; the oracle is blind at this spot, and that belongs in every
  finding.
- **The write rule does not become softer through this, but narrower:** in the
  `weltlauf` too, no address is written twice per round. The set of addresses written at
  all is fixed per mode and is reported alongside by the test stand.

Maß 4 thereby checks exactly what it is supposed to check: the transmission
politics → economy via steps 3 and 4. A run with invented politics would check only half
the machine; a run with a dying fund would check nothing at all.

**The 27 target series** are GDP per country (4), sector shares (12, of which 8
independent), consumer prices (4), exchange rate against USD (3), government debt ratio
(4); plus the trade block over 40 flows as a block of its own. Each over 21 support
points without filling. Per the classification from `technik.md` T37 the four government
debt ratios are **derived**, the remaining 23 **free**.

**The policy rate has not been a target series since 2026-09-03.** The class `gesetzt`
is thereby empty and is dropped. The reason is in *The game length R* and is not one of
coverage: a series that is set as input in the `weltlauf` has error zero by construction
— it cannot fail and cannot prove anything, and it still shortened the window by a year.
**What takes its place is sharper, not softer:** the policy rate remains input (series
9, role start + policy path), and that the machine reproduces it unchanged is an
**invariant**, not a threshold. If the model value deviates from the set path at any
support point, that is a hard error and not an error measure of 300 basis points. It is
still reported.

**The three error measures, per series:**

| Series | what is compared | Threshold |
|---|---|---|
| GDP (4), sector shares (12), government debt ratio (4), trade flows (40) | the **level** | MAPE over the 21 support points ≤ 20 % |
| consumer prices (4), exchange rate (3) | the **annual rate of change** in basis points | mean absolute error over the 20 transitions ≤ 300 bp |
| all | the **direction** | share of the 20 transitions with `sgn(Δmodell) = sgn(Δsoll)` ≥ 0,6 |

The second row is the consequence of `technik.md` T8: a percentage error on an index
that wanders by an order of magnitude over two decades measures the starting point and
not the machine — and a percentage error on a rate near zero explodes. The 300 basis
points, i.e. three percentage points of mean error on the annual rate, have the same
status as the 20 percent and the 0,6: a bar that was set. Should it prove unreachable,
that is a finding about the model and no reason to move it.

**The acceptance rule — `3·L_R + (L_R − n) + 1` check subjects, tolerance `⌊L_R/2⌋`.**
Today, with `L_R = 4` backtest countries and `n = 1`, that is **16 and 2**; after
package 0118 with `L_R = 7` it is **28 and 3** (see *Welche neun Länder*). **From here
on both stand as a formula and not as a digit**, for the same reason `R` stands as a
letter: a fixed 2 would make adding a country a tightening of the backtest without any
rule of the model changing. The second version named two error measures and no rule for
how to aggregate over the series; `technik.md` T37 read a total measure out of that and
returned the decision. Here it is:

1. **Only the free series are acceptance-relevant.** The four derived debt ratios are
   reported and decide nothing; since 2026-09-03 the policy rate is not even a target
   series any more, but input with an invariant check. A series that is error-free by
   construction must not soften a total measure.
2. **The check subject is not the series but the quantity.** There are sixteen today,
   and **counting is per backtest country, not per country** — per T58 a play-only
   country lies entirely outside the target mask and contributes none:

   | Check subject | Formula | today | after 0118 | aggregated from |
   |---|---|---:|---:|---|
   | GDP per backtest country | `L_R` | 4 | 7 | one series each |
   | sector structure per backtest country | `L_R` | 4 | 7 | the country's **three** share series, all three must pass |
   | consumer prices per backtest country | `L_R` | 4 | 7 | one series each |
   | exchange rate per backtest country except the numéraire | `L_R − n` | 3 | 6 | one series each |
   | trade block | `1` | 1 | 1 | `(L_R+1)·L_R·(S−1)` flows — 40 today, 112 after 0118; median of the MAPE and median of the directional accuracy; the worst fifth is reported |
   | **Sum** | `3·L_R + (L_R − n) + 1` | **16** | **28** | |

   The three share series of a country are not independent, due to the normalisation to
   10.000; kept as three counters, a single badly modelled country would use up the
   tolerance on its own. Kept as **one** counter it costs one of sixteen — and in return
   must pass in all three shares.

   **The number 16 has remained unchanged by the cut of 2026-09-03, and that is
   recounted, not assumed.** Struck are the four policy-rate series; the table above
   draws on series 1 (GDP), series 2 (sector shares), series 8
   (consumer prices), series 10 (exchange rate) and series 14 (trade block). None of the
   sixteen check subjects contains series 9, and none could: per T37 it was `gesetzt`.
   **The acceptance rule „at most 2 of the 16" thus keeps running on the same set of
   series as before, only over 21 instead of 25 support points.** What has changed is
   the denominator of the *target series* (31 → 27), not that of the *check subjects*.

3. **A check subject passes** if it holds both thresholds that apply to it. **The
   directional accuracy is formed only over the transitions in which the target series
   moves.** A transition without measured movement carries no direction and is counted
   neither as a hit nor as an error; if a target series moves in none of the twenty
   transitions, the check subject has no directional accuracy and passes on its level
   measure alone. That is not a softening but the closing of a gap: over a constant
   series every transition carries direction zero, an endogenously computed value
   virtually never hits the exact zero, and the subject would break **by construction**.
   The case is not hypothetical — it is the reason Saudi Arabia is expected to be a
   play-only country (see *Welche neun Länder*), and flat stretches exist even without a
   currency peg.
4. **The run passes if at most `⌊L_R/2⌋` check subjects break** — today two of sixteen,
   after package 0118 three of twenty-eight. Every broken one is named individually in
   the finding, with both numbers. One more is a fail, even if it breaks narrowly. **At
   `L_R = 4` the formula reproduces exactly today's 2** — that is the compatibility
   check — and after that it holds the share nearly fixed: 2 of 16 is 12,5 percent, 3
   of 28 is 10,7, 4 of 36 is 11,1. It thus grows more slowly than the number of subjects
   and never lowers the bar.

The median over the trade flows — 40 today, 112 after package 0118 — is the architect's
proposal (`technik.md`
section 12) and is hereby adopted, with its reasoning: individual small flows
— Brazil–China in agriculture — fluctuate strongly in percentage terms without the model
being wrong; a mean would break on that, a per-flow threshold faster.

**Cost:** R = 20 world steps.

**And the limit of the oracle, explicitly.** Without a target series are: **sector
prices** and **world prices** (gap 2 of the data curator), **approval** (gap 4), the
instrument **Finanzmarktregulierung**, the **market return** and, since 2026-09-03, the
**policy rate** — the last not for lack of data, but because it is input and a set value
checks nothing. Added to this, in the `weltlauf`, is the entire fund subsystem, which
does not run at all. All these quantities are visible in the state; none is covered by
the backtest. It checks the dynamics of the machine over the historical period and says
nothing about the branch the player enters.

**One filled support point, which belongs in every finding.** The US policy-rate path
ends in 2020; its twenty-first support point is the carried-forward value of 2020 and
carries `gefuellt = 1`. It is not a target point, so it does not fall under T24's
prohibition — but it is an **input**, and the last transition of the US check subjects
runs on it. The test stand reports it. It is the only filled value in the whole check
vintage.

### Die drei Klagen und was sie beantwortet

| Complaint from the reviews | Design decision |
|---|---|
| „the consequences of choices often feel intangible" | **At most three actions per round** — scarcity forces every action to be big enough to have an effect. Plus the chain as its own part of the state (steps 1 and 6) and Maß 1 as an acceptance threshold per game third instead of a wish. **Since 2026-09-03 also the counter-check:** in counterforce 5 the damage of each instrument is non-zero exactly when the instrument has moved. A chain that shows a penalty and no action behind it is the same complaint from behind — that is why the business-cycle base term of the tariff row fell. |
| „trying to implement the tiniest socialist policy will always result in bankruptcy" | **The fund can be long and short.** Thus no political direction is dominant: whoever bets on regulation because they are short wins just as much as whoever prevents it. Plus the two-part victory condition (capital AND influence) and Maß 2, which wants to see each of the three families win individually. |
| „no dramatic setbacks or successes", „everything is incredibly surface level" | **Three ways of dying with visible thresholds** (forced liquidation, market ban, investor withdrawal), the result scale that rates the early death worse than the late one, and Maß 3, forced by imitators and price shock. The setback is dramatic, but never arbitrary — see „Keine verdeckte Größe". |

## Was bewusst fehlt

- **More than four countries and three sectors.** The idea named twelve and six. Twelve
  countries quadruple the feedback paths without improving any Maß; six sectors do not
  exist under a free licence, and sectors split out of three would be a construct without
  a target series.
  **Classified on 2026-09-05, not struck:** The sentence applied and still applies to
  *policy countries* — the operator has decided on nine (package 0118), and that is the
  number it is to be read against from now on. For the *investable universe* it has been
  moot since package 0119: that universe grows through the second layer, which adds no
  feedback paths because it has no trade row.
  **Filled in on 2026-09-06:** The nine are the USA, China, Germany, Brazil, Japan,
  India, Chile, Singapore and Saudi Arabia. The sentence about the quadrupled feedback
  paths remains true all the same and can now be given a number — the trade matrix grows
  from 40 to 180 flows, four-and-a-half-fold, while everything else roughly doubles.
  **It is thereby the reason why there are nine and not twelve**, and no longer an
  objection to the nine.
- **A tenth policy country, and the boundary lies in the matrix, not in taste.**
  `G·(G−1)·2` with `G = L+1` yields 220 flows instead of 180 at ten countries, 312 at
  twelve. Whoever wants more investable world gets it through the second layer at five
  fields per tradable slot instead of around twenty — that is the layer's entire
  justification, and it holds against any tenth country just as against the thirtieth.
- **A second euro-area country.** Greece was the strongest candidate for the fifth place:
  its fiscal balance becomes exogenous under the programme in 2010 — round 10, exactly
  between the two windows of Maß 3 — and that would be the instrument lock that has been
  missing since the window was cut to 2001 and that this design explicitly misses. **It
  fails at one address:** the euro's exchange rate against the dollar is the **same**
  series for Germany and Greece, but the model keeps `wechselkurs[l]` per country and
  would compute two euro rates that are allowed to drift apart. The two countries would
  carry two check subjects on a single reality, and an error in the euro rate would break
  both at once. The way out would be a shared rate address per currency area — and that
  changes the address arithmetic, the target-series count and the check-subject formula
  all at once. Too expensive for a fifth country, and a package of its own should the
  euro area ever appear twice.
- **An instrument lock that snaps shut inside the window.** It has been missing since
  2026-09-03 and it stays missing. The candidate outside the euro area was Turkey (IMF
  programme 2002–2008, i.e. rounds 2 to 8); it is rejected because that window lies
  exactly over the early window of Maß 3, so the lock would sit not *between* the two
  windows but *inside* one. What would remain is a lock on a middle round — and that is
  the narrated event that stands two lines further down on this list for good reason.
  **Maß 3 must still produce the shift without such a transition**; since package 0119
  its third source is the second layer.
- **An exchange-rate regime as a model quantity.** Saudi Arabia's rate stands at 3.75
  across all 21 support points, and the model has no rule that holds a rate. A currency
  peg would be cheap to write — the `wechselkurs[l]` of a pegged country is simply not
  written, the same construction as the decommissioned addresses of a play-only country —
  and it is still not decided here: it would turn a play-only country into a backtest
  country and thereby shift `L_R`, the check subjects and the target mask. That is a
  decision about the foundation of the backtest and belongs, per T60, to the operator,
  not to this section. **What it would buy is stated here:** a pegged rate is the only
  way the model could express the difference between a loud and a mute currency, and
  Saudi Arabia is the only place where it is measurably off.
- **All 195 countries of the world.** That is not a „later" but a different product, and
  the numbers stand under *Was die Schicht kostet*: **87,788 state fields, 76,440 trade
  flows, 3,705 licence-checked data series** and 780 check subjects instead of sixteen.
  Rejected on 2026-09-05.
- **An exchange venue with a trade row, policy instruments or a stake.** Each of these by
  itself turns it into a cheap country: the trade row brings the `G²` matrix back
  (3,120 flows instead of 180), the instruments make it influenceable and thereby cancel
  the separation for whose sake the layer exists, and the stake would be the road to
  cheap lobbying in a place where there is no lobbying.
- **A supervision counter on the second layer.** The fund can grow large there
  unobserved. That is explicitly intended and dearly paid for: the layer delivers zero
  influence and can never fulfil the second half of the mandate. A half counter
  („visibility yes, influence no") would be a rule that decides nothing, because the
  footprint carries influence as a factor and would stay zero anyway.
- **A regulation channel onto `zins[b]`.** The obvious move would be for the anchor's
  Finanzmarktregulierung to drive capital away and lift the venue rate — a third lever
  into the second layer. It would cost another calibration key, and two levers into it
  exist already (the policy rate via `zielzins` and `weltzins`, the tariff via
  `leitkurs`). Should Maß 3 fail for lack of grip on the layer, this channel is the
  first addition.
- **A measured market capitalisation per exchange venue.** `tiefe[b]` is built from the
  anchor's capital stock and the sector weights, times `platzanteil`. A real
  capitalisation series would be the more correct quantity, but would hang on another
  source with its own licence question — and the ordering that matters (large anchor,
  deep venue) is delivered by the derived quantity too.
- **An inertia parameter of its own for the second layer.** A venue's `index`, `zins` and
  `wechselkurs` move exactly **half** way towards their target each round. Three
  calibratable weights would give the search three axes whose effect `kippung` and
  `platzanteil` produce anyway — and no Maß reads the halving.
- **Manufacturing as a sector of its own.** It would be the more interesting breakdown
  and even exists as a WDI series — but only as a subset of industry. A fourth sector
  „rest of industry" would have no source series of its own and would have to be formed
  as a difference. Four sectors with one uncovered, three with all of them covered: the
  choice is the second.
- **Start vintages before 2001**, and the boundary now lies four years later than in the
  fifth version. 2000 and earlier remain possible as **play vintages** and are the
  obvious content of the expansion model from the idea. They carry no US government debt
  ratio and no US fiscal path from data (IMF WEO begins in 2001 for the USA), before 1997
  additionally no US sector structure and before 1995 no trade block; a play vintage
  before 2001 takes the missing US start values from the first covered year and marks
  them as filled. That makes them play vintages, but not check vintages. This belongs
  written into the sales offer, not into a footnote.
- **A replacement for the euro transition, since 2026-09-03 and explicitly.** With the
  window 2001–2021 the only instrument lock that snapped shut during a game disappears
  (Germany loses its interest-rate lever in 1999). The obvious way out would be to put
  some other lock on a middle round — and that is exactly what I do not do: it would be
  a narrated event, and those stand two lines further down on this list for good reason.
  Events here arise from thresholds or from data, not from the wish for a turning point.
  Maß 3 must produce the shift without this transition; if it does not, that is a finding
  about the two remaining sources (imitator, price shock) and no reason to invent a lock.
- **Rebuilding the window 1997–2000 from a third source.** The table in *The game length
  R* works it through: for Brazil the years do not exist, for the USA they would exist
  only at the price of a different delimitation than for China and Germany. Four support
  points are cheaper than a target series that measures something different per country.
- **A fill rule of its own for policy paths.** The policy-rate path may be filled, the
  target series of the check vintage may not — that stands in T24 and suffices. A third
  threshold („a path may be filled to at most x percent") would be a number nobody can
  measure before the source is fixed. What holds instead: every filled support point of
  a path is named individually in the finding. With 21 support points a list is cheaper
  than a share.
- **A finer goods key than HS92 chapters.** The mapping 01–24 / 25–97 is coarse and its
  error is named above. A real HS-to-ISIC concordance would be more accurate and would
  cost another source with its own licence question — for two model sectors that is not
  worth it.
- **Quarterly and daily time steps.** With them, panic, runs and margin calls in the
  literal sense drop out — a palpable loss of genre expectation, and I name it as such.
  The reason is hard: GDP, sector structure, productivity and tariffs are available
  **annually**. Quarterly rounds would leave three of four rounds unchecked. The
  substitute for intra-year risk: leverage is checked not against the year-end level but
  against an intra-year swing that follows deterministically from the year's movement and
  the country's historical volatility range. Leverage stays dangerous without a second
  time layer coming into being.
- **A world equity index as a benchmark.** None exists under a free licence. The market
  return is therefore a model quantity without an anchor — named, not hidden.
- **A price of its own beside the sector price.** A basket is valued at the price of its
  sector, not at a share price that would be allowed to deviate from it. So there is no
  valuation bubble and no sentiment — the value of a holding follows its causal chain
  and nothing else. That is a loss of genre expectation and the price paid so that every
  change in value stays explainable.
- **Variable creditworthiness.** The `aufschlag` between policy rate and bond yield is a
  constant. A country whose debt ratio runs away pays no higher spread in the model;
  sovereign defaults and risk premia do not exist. The spread would have an anchor
  (yield series) but no target series in the state, and it would cost a ninth feedback
  channel (budget → spread → price → budget).
- **The money supply as the depth of the currency market.** It would be available from
  IMF IFS and would be the better quantity than trade volume. It costs one state address
  per country and one exogenous path, and it improves no Maß. Trade volume orders the
  four countries the same way and is already in the state.
- **Individual companies.** Only country×sector baskets. Firm-level data under a free
  licence does not exist, and what the data curator cannot obtain does not appear.
- **Derivatives, options, structured products.** Long, short, leverage. More instruments
  enlarge the action space without adding a profile that Maß 2 could distinguish.
- **Persons named by name.** Governments are roles („government of Brazil"), central
  banks are institutions. A requirement from `agentenbau.md`, and it touches precisely
  this game.
- **Election mechanics.** No parties, no coalitions, no constituencies. One approval
  quantity, a change of government when it drops below the threshold.
- **Narrated events and event cards.** They would be a content treadmill (G4) and not
  regressively checkable. Events here arise from thresholds.
- **War, climate, migration, demographics as game quantities, multiplayer.**
- **A tariff rate per sector.** It does not exist under a viable licence. The sector
  effect arises from `durchgriff` and the import shares.
- **A time-varying `durchgriff`.** It would be more correct and would cost ten more
  exogenous paths. Constant suffices, because the quantities are endogenous anyway.
- **A counter-lobby that wants to push something through itself.** `gegendruck` is a
  scalar netted against `druck` in step 3; it can **restrain movement, not demand it**.
  What counterforce 5 depicts is mobilisation, not retaliation — a damaged sector makes
  every movement of its tariff instrument more expensive, including the ones that would
  help it. Retaliatory tariffs would cost one direction per instrument and thus sixteen
  more addresses.
- **A split of the damage onto the damaged sector.** Who bears it stands there as a
  rule; it is computed per country and instrument, not per sector. The split would need
  an intermediate-inputs matrix — another source with its own licence question — and it
  would change none of the sixteen numbers in step 3.
- **A memory of the counter-lobby beyond one round.** The halving is the whole story. A
  tail spread over several rounds would cost sixteen more addresses and would only shape
  the transient.
- **Damage to the rest of world.** It has no policy instruments and thus no address at
  which a counter-lobby could form. Its price shifts remain unbooked; the rest of world
  closes the circular flow, it does not act.
- **A damage that distinguishes rise from fall.** The shift enters as an absolute value:
  every movement damages someone. The direction is already carried by the netting
  against `druck` in step 3, and a sign in the damage would pull it in a second time.
- **The business-cycle share of the price shift, since 2026-09-03 and explicitly.** A
  sector price trailing the world price shifts every round; that someone suffers from it
  is true and still no lobby damage. Whoever books price inertia as damage books
  inflation as a counterforce — the reasoning stands under *Warum die Zollzeile nur den
  Keil misst*. What is **not** missing because of this: the tariff's effect on the
  sector. It sits in `durchgriff(l, s)`, and that is the only reason the row does not
  simply read `hub(l, zoll)`.
- **The general-equilibrium share of a tariff step.** An American tariff moves the world
  price via market clearing, and with it the sector prices of all countries. This part
  of its effect enters no damage row, for it could only be measured against a state that
  does not exist: the same round with the old tariff level, that is, a **second market
  clearing** with another 40 halving steps per sector. The price would be the model's
  most expensive computation doubled, the yield a number no Maß checks.
- **The damage a foreign tariff does at home, as a row of its own.** It is the
  consequence of the previous item and falls with it. It does not vanish from the game
  but changes counterforce: the foreign tariff step lifts the domestic sector price,
  lowers real income and approval, and via counterforce 2 can trigger a change of
  government that resets all four instruments and thereby produces damage. The
  difference deserves naming and is no small thing: the old path was continuous, the new
  one is threshold-driven and at least one round slower.
- **A counter-lobby rate of its own per instrument.** One `gegenlobby_satz`, four
  quantities. Four rates would give the calibration three axes whose effect the
  quantities produce anyway — and from the vintage rather than from a number.
- **Graphics beyond table, time-series graph and chain view.** Democracy 4 sells itself
  with a 2D node surface and consists, in its simulation, entirely of loaded tables
  rather than hard-coded effects
  (positech.co.uk/democracy4/modding.html, retrieved 2026-08-31). That is the
  construction I orient myself by.

## Offene Entwurfsfragen

- **The hardest: Is the World Bank's aggregated tariff rate usable?** It is recognisably
  derived from WITS and may therefore fall under the third-party exception of the WDI
  licence. If it is locked, the backtest loses the most important of its three anchored
  instruments. That does not change the design — `technik.md` T26 has absorbed the case
  architecturally — but it halves its evidence. To be checked before anything is built.
- **The remaining WDI series under the third-party exception.** Per the architect's
  marking, the ones to check are Nr. 7 (sectoral employment, ILO estimate), Nr. 8
  (consumer prices, IMF-based), Nr. 10 (exchange rate) and Nr. 13 (tariff). For each
  series, read the field „Source" in the indicator dataset. Four retrievals and the
  question is closed — a task for the data builder, because it hangs on the vintage, not
  on the design.
- **The window is decided and this question is closed.** It was called „Bleibt das Fenster
  bei 1997–2021?" and since 2026-09-02 read „19, 20 oder 24?". **No, and 20.** The window
  is **2001–2021**, `R = 20`, 21 support points; decided on 2026-09-03 in package
  `0054-partielaenge-r-entscheiden`, justified in the section *The game length R*, carried
  through in all four measure rules and named for the architect in the catch-up table. The
  suspect case from `technik.md` T24 — the Chinese and the Brazilian policy-rate series of
  the nineties — is thereby moot: the nineties lie outside the window, and the policy rate
  is no longer a target series.

  **What emerges from the decision as new open questions is in the next two points.** They
  replace the closed one; they are not the same thing in another form: one concerns the
  procurement of an input, the other its uniformity. Neither hangs on R any more.
- **Where the policy-rate path for Germany and China comes from.** `IMF.STA/MFS_IR`
  carries not a single value for either country (coverage finding, retrievals 2026-09-01),
  and that holds for every window. The path is needed nonetheless: as `leitzins_start[l]`,
  as an exogenous path in the `weltlauf` and as the instrument's value range in the
  `spielmodus`. **This is a procurement question and a follow-up package for the data
  builder, not a design question** — and since the target role was dropped it is markedly
  smaller: under T24 an input may be filled and marked, a target series of the check
  vintage may not. Two leads already stand in our own records and are only named here, not
  checked: **Eurostat** is, per `daten.md` Nr. 7, commercially usable for EU and EFTA
  countries and thus covers the German — or rather the euro-area — side; **`FR.INR.LEND`**
  (WDI) carries China without gaps 1997–2021 per the coverage finding, but it is a bank
  lending rate, not a policy rate.
- **Whether a uniform notion of the interest rate is achievable across the four
  countries.** The coverage finding proves that `DISR_RT_PT_A_PT` measures something
  different per country — for the USA the discount rate of the Fed's discount window, for
  Brazil the rediscount rate, which is not the Selic. As a *target series* that would be
  an error which the deletion settles. As an *input* it remains an open question, and one
  that strikes through to check subjects: a Brazilian path at the wrong level drives bond
  price and interest-rate channel and with them Brazil's GDP, sector structure, consumer
  prices and exchange rate — four of the sixteen. **The design requirement for the
  follow-up package is therefore: one notion for all four countries, and if none is
  achievable, then the most plausible one per country, expressly named and carried along
  in the backtest's finding.** The data builder decides that at the sources, not I at the
  desk.
- **The numerical values of the thresholds** — mandate threshold, supervision thresholds,
  starting capital, imitator speed, step width of a position, investor withdrawal share.
  They do not belong in this design, because they are not decided but **calibrated**: the
  self-play searches for the values at which Maß 1 to 3 reach their thresholds. That is
  exactly what the measures exist for. What is fixed is the form, not the number; per T27
  the values stand in `parameter.toml`.
- **Whether a parameter set exists in which the fund is large enough and not too large.**
  New with this version, and the question is a measurement, not a decision: starting
  capital and `stufenweite` must together make one step affordable **and** let achievable
  step counts reach up to the supervision thresholds. Both at once is not guaranteed —
  the model's markets are entire sector capital stocks, and a fund that moves them is
  large. If the self-player misses the first condition, class 1 never wins; if it misses
  the second, no counterforce engages and Maß 3 falls to zero. **Both are visible on the
  test stand**, and both are a finding about the parameter set, not about the design —
  unless no admissible one exists. Then it is the design.
- **How fine the action space may be.** Too coarse, and Maß 1 finds no differences; too
  fine, and the sample of 30 bundles covers too little. To be determined empirically on
  the prototype — measurable by whether `Dichte(t)` gives the same answer at K=30 and
  K=60.
- **The load rate of the instrument „Finanzmarktregulierung", `regulierung_last`.** New
  with the damage rule, class 3, basis points of GDP per regulation step. It is the only
  number in counterforce 5 without a data-anchored counterpart — and precisely where the
  instrument table above in any case says „pure model construct", without a target series.
  The three remaining rows get by without a new number. Its value is calibrated, not
  designed; in the `weltlauf` it has no effect, because the instrument is fixed there.
- **Whether `druck` follows the same round-boundary rule as `gegendruck`.** About pending
  lobby pressure this design says only „action 3, netting in step 3"; whether it stays
  across the round, decays or is consumed is stated nowhere. That is the same kind of gap
  as the closed one, one level over, and **it is not without consequence**: influence is
  the fund's share of total lobby pressure, that is, of the ratio `druck : gegendruck`,
  and that ratio hangs on both rules. My proposal for the follow-up package is the same
  halving for the same reason; it is not decided here, because it belongs to step 3 and
  not to counterforce 5.
- **Whether `schrittweite[zoll]` exceeds the rounding threshold of the tariff row.** New
  on 2026-09-03 and the only condition that follows from the tariff-wedge decision. A
  tariff step runs through two roundings — world price level times rate, then times
  `durchgriff` — and for a country×sector pair with low `durchgriff`, `preishub_zoll` can
  fall to zero at small steps. Then the tariff row is **silent there, without reporting
  it**. The check form stands in the section; the number that satisfies it is calibration.
  The vintage build has all eight pairs on hand and can check the condition mechanically —
  it belongs in its output, not in a night run.
- **Whether one `gegenlobby_satz` carries all four rows at once, now with the opposite
  sign.** The question already stood; the decision of 2026-09-03 shifts it. The tariff row
  has become smaller by the base term — its action share is unchanged, but the gap to the
  budget row, whose quantity is the whole GDP, now lies open. Whether one rate carries
  both, or whether the Lobby family in effect has only one affordable instrument left, is
  to be seen on the test stand and not here. The design holds to a single rate, because
  four rates would give the calibration three axes whose effect the quantities produce
  anyway; if Maß 2 fails on that, it is a finding about the design and not about the
  parameters.
- **Whether the counter-lobby leaves the influence half of the mandate reachable.**
  Influence is the fund's share of the total lobby pressure on an instrument; a
  counter-pressure that runs toward `druck_max` in every country the fund touches pushes
  that share below any threshold, and the Lobby family produces no winner in Maß 2. That
  is the sharpest calibration condition that follows from this rule, and it is visible on
  the test stand. If no admissible rate exists, it is a finding about the design and not
  about the parameters.
- **Whether `gegenlobby_satz` is fine enough as an integer.** Class 9 knows no
  subdivision, so the smallest admissible value is one lobby point per 10.000 thousand
  USD. An order-of-magnitude check — expressly an estimate, because
  `schrittweite[haushalt]` is not yet fixed: at a GDP of `2.1 · 10^10` thousand USD and an
  assumed step width of 50 basis points, that is `1.05 · 10^8` thousand USD of damage and
  thus around **10.500 lobby points** at `gegenlobby_satz = 1`. Whether that fits
  `druck_max` and what the fund raises via `lobbykosten` is for the search to decide;
  since only the ratio counts in step 3, it can counter-steer via `lobbykosten`. If even
  that is not enough, the way out would be a ten-thousandths scale for `gegenlobby_satz` —
  an ADR against T5 class 9, to be decided on the test stand, not here.
- **Whether the change of government should produce damage.** Decided: yes — the reset of
  all instruments is itself the consequence of successful lobbying. What remains open is
  whether the calibration still finds a way back afterwards: counterforce 2 doubles the
  lobby costs for several rounds, counterforce 5 puts counter-pressure on all four
  instruments in the same round. Two penalties from one cause; whether that becomes a dead
  end is measured by Maß 2, not by this design.
- **Whether `platzanteil` has an admissible range.** New on 2026-09-05 and the sharpest
  condition that follows from the second layer. Too large, and the venues are deep enough
  for family 1 to build up capital there undisturbed — then the second acceptance half of
  Maß 2 (`max(Ek) ≤ 1,25 · min(Ek)`) fails, because Position leaves the other two families
  behind. Too small, and one step on a venue is either unaffordable or moves the price so
  strongly that the layer is unusable — then it is decoration and Maß 3 loses its third
  source again. Both are visible on the test stand, both are a finding about the parameter
  set — unless no admissible one exists. Then it is the design.
- **Whether `kippung` really distinguishes the three venues of an anchor.** They are
  different by construction, but whether the difference is large enough for a search bot
  to exploit it is a measurement. The check form: if, in the early window of Maß 3,
  profiles weighted toward different lead sectors reach the same result, the three venues
  of an anchor are one venue. The number is calibration; the form stands.
- **`3·(L+1)` survives the country choice from 0118, and this question is thereby
  closed.** It asked whether every territory carries three distinguishable lead sectors —
  for a country with a strongly dominant sector structure the three venues would lie close
  together under the `kippung` rule. Measured by the largest normalised sector share, the
  most one-sided of the nine anchors is the **USA** at 76.6 percent, and it has stood in
  the model since the first version; the two most balanced, at 51.3 and 47.7, are two of
  the five new ones (Saudi Arabia, India). **The choice improves the binding case instead
  of sharpening it.** What remains open is not the formula but `kippung` — and that
  already stands as its own question two points further up, now with the country attached
  on which it will be decided.
- **Whether `MFS_IR` carries a policy rate at Stufe 1 for Japan, India and Chile.** On
  this one retrieval per country hang the class of three countries and with it `L_R`, the
  number of check subjects (28 versus 16 to 22), the target series and the target mask. It
  is the cheapest open question of this package — three retrievals per T63 step 1 — and
  the one with the greatest leverage. It belongs to the data builder, not to me.
- **Whether the class rule from T61 rule 5 sees the exclusions that lie in the target
  series.** It derives the class solely from the three policy-path series. But two grounds
  for exclusion lie elsewhere: the missing fallback source for series 2 (T62 Folgerung 2)
  and — new since this package — a target series that is constant over the whole window
  and therefore cannot carry directional accuracy. If `MFS_IR` carries a SAMA rate at
  Stufe 1, rule 5 derives „Rückvergleichsland" for Saudi Arabia while the manifest must
  say „Spielland", and the vintage build aborts. The abort is right, the place is not.
  Belongs to T61.
- **Whether the tolerance `⌊L_R/2⌋` holds.** It is new on 2026-09-06 and replaces the
  fixed 2, because a fixed number turned adding a country into a tightening. It reproduces
  today's 2 and keeps the share at around eleven percent — but whether eleven percent is
  the right quota, only the backtester at the running core knows. If four of 28 break
  regularly, that is a finding about the model and not about the formula.
- **Whether the trade block is weighted correctly as *one* check subject when it grows
  from 40 to 112 flows.** The question exists already at four countries and becomes
  sharper with nine: the heaviest single subject of the backtest counts as much as the GDP
  of a single country. The aggregation via the median is the reason it does not fly apart
  anyway; whether at 112 flows it still delivers what it does at 40 is a measurement. Not
  decided in this package, because it is independent of the number of countries.
- **Where the sector weights of the three rest-of-world venues come from.** They follow
  the same rule from `sektoranteil[Restwelt][s]` of the start year. The rest of world
  arises in the vintage as a residual, and whether its sector shares fall out cleanly in
  the process is known to the vintage build, not to me. If the quantity does not fall out,
  the way out is the capital-stock-weighted mean of the `L` country shares — a rule, not
  an invented number.
- **Whether an embeddable price series exists after all.** The layer is designed without
  any target series, because `daten.md` carries none and this design already records that
  there is no world equity index under a free licence. Were the data builder to find an
  index series under a viable licence, the affected venues would be **backtest countries**
  instead of play-only countries, and Maß 4 would gain check subjects instead of losing
  none. The design does not hang on it — it would only gain. To be checked by the data
  builder, not by me.
- **Whether the thresholds of Maß 4 are reachable at all with endogenous productivity.**
  Unchanged the largest unmeasured risk of the venture. It is no longer a design question
  but a measurement by the backtester at the running core — the acceptance rule now
  stands, so the result can be judged at all.

## Was der Architekt neu rechnen muss

Nur damit es nicht gesucht werden muss. Alles Übrige an `technik.md` bleibt gültig.

### Neu aus Paket 0118 — neun Länder, `L_R = 7`, und die Zählregel von Maß 4

`technik.md` habe ich nicht angefasst, und **keine Zahl darin ist heute falsch**: Bis 0116 die
Adressarithmetik parametrisch geschrieben und der Datenbauer den Jahrgang gebaut hat, gilt
weiter `L = 4`, `L_R = 4` und 310. Was danach nachzuziehen ist:

| Stelle | was zu tun ist |
|---|---|
| **T59** (Zählung in `L_R`) | Die Tabelle bekommt die Spalte `L_R = 7, L_S = 2` — das ist die Wahl aus diesem Paket. Prüfgegenstände 28, freie Sollreihen 41, Sollreihen 48, Ströme im Handelsblock 112, Sollmaske `weltlauf` 328. Jede Zahl steht im Abschnitt *Welche neun Länder* eingesetzt daneben. Die Spalten `L_R = 4` und `L_R = 9` bleiben, sie sind die Ränder. |
| **T58** (Klassen) | Die Rückvergleichsländer sind USA, China, Deutschland, Brasilien, Japan, Indien, Chile; Spielländer sind Singapur und Saudi-Arabien. **Erwartung mit Bedingung, nicht Festlegung** — entschieden wird sie nach T63 Schritt 1 am Abruf. Die Festlegungen 3 (Restweltrest je Modus) und 4 (Giftprobe) werden mit diesem Paket zum ersten Mal wirklich gebraucht: Es gibt ab hier Spielländer. |
| **T61 Regel 5** | **Der eine Befund dieses Pakets gegen ein fremdes Gewerk.** Die Regel leitet die Klasse allein aus den drei Politikpfadreihen ab. Saudi-Arabien ist aus einem Grund Spielland, den sie nicht sehen kann: seine konstante Wechselkurs-**Sollreihe**. Führt `MFS_IR` einen SAMA-Politiksatz auf Stufe 1, gehen die abgeleitete und die geschriebene Klasse auseinander und der Jahrgangsbau bricht ab — richtig, aber an der falschen Stelle. T62 Folgerung 2 (Reihe 2 ohne Ausweichquelle) ist derselbe Fall. Beide Ausschlüsse liegen in den Sollreihen und gehören dorthin, wo die Klasse gebildet wird. |
| **T62** (Datenkosten) | Drei Rückvergleichsländer zu `32(R+1)+6 = 678` und zwei Spielländer zu `5(R+1)+33 = 138` ergeben **2.310** Werte bei `R = 20`, nicht die 3.390 aller fünf als Rückvergleichsland. Die **zehn** neuen Lizenzstellen (zwei je Land) sind von der Klasse unabhängig und gehören nach Folgerung 3 auf dieselbe Liste wie die sieben offenen. |
| **T37 / Toleranz** | Die Zahl der Prüfgegenstände und die Toleranz stehen ab hier als Formel: `3·L_R + (L_R − n) + 1` und `⌊L_R/2⌋`. Bei `L_R = 4` ergeben sie 16 und 2, also genau den heutigen Stand — das ist die Verträglichkeitsprobe, und deshalb ändert dieser Eintrag heute nichts. |
| **Richtungstreue** | Sie wird nur über die Übergänge gebildet, in denen sich die **Sollreihe** bewegt. Ein Übergang ohne gemessene Bewegung zählt weder als Treffer noch als Fehler; bewegt sich eine Reihe nie, besteht der Gegenstand allein über sein Niveaumaß. Ohne diese Zeile risse jede konstante Sollreihe von Bauart wegen. |
| **T16** (Steckplätze) | Unverändert gegenüber 0119: `3L + L + L + B = 75` bei `L = 9`, davon 74 besetzbar, weil der Währungssteckplatz des Numéraires leer bleibt. Die Deckungsrechnung dieses Pakets steht auf den 74. |
| **T5 / Wertebereiche** | Zwei Ränder werden zum ersten Mal wirklich angefahren und sind zu prüfen, nicht anzunehmen: `durchgriff` läuft für Singapurs Landwirtschaft gegen 10.000 (Anteil 0,08 Prozent, also `N ≈ 0`), und `staatsschuld[JPN]` überschreitet 20.000 Basispunkte (222,7 Prozent im Endjahr). Beides bleibt im Wertebereich; beides gehört in die Invariantenprobe, weil es die erste Berührung ist. |

**Was dieses Paket ausdrücklich nicht angefasst hat:** die 310, die Adressarithmetik, den Kern,
`reihen.toml`, `technik.md` und die Zahl der Aktionen je Runde. Die Aktionszahl steht als
**Stellschraube mit Bedingung und Probe** im Abschnitt *Die Folge aus Weg A* und ist nicht
gedreht.

### Neu aus Paket 0119 — die zweite Schicht, 150 Adressen und zwei Parameter

`technik.md` habe ich nicht angefasst, und keine Zahl darin ist heute falsch: Die zweite
Schicht kommt zusammen mit den neun Ländern aus 0118, und bis 0116 die Adressarithmetik
parametrisch geschrieben hat, gilt weiter `L = 4` und 310. Was danach nachzuziehen ist:

| Stelle | was zu tun ist |
|---|---|
| **T15** (Adressaufstellung) | Ein sechster Block `boersenplatz`: `5 · B` Adressen mit `B = 3·(L+1)`, also 150 bei `L = 9`. Vier Felder je Platz (`index`, `wechselkurs`, `zins`, `nachahmer`) plus ein Positionssteckplatz. Gesamt 890. |
| **T16** (Steckplätze) | Die Steckplatzliste bekommt eine vierte Art. `3·L` Land×Sektor + `L` Währung + `L` Anleihe + `B` Börsenplatz = 75 bei `L = 9`. Die Regel „Steckplatz Währung USA bleibt leer" hat auf der neuen Art keine Entsprechung — jeder Platz ist besetzbar. |
| **T5** (Skalenklassen) | `index[b]` und `wechselkurs[b]` in Klasse 5, `zins[b]` in Klasse 3, `nachahmer[b]` ganzzahlig mit Obergrenze wie `nachahmer[l][s]`. `tiefe[b]` steht in der volkswirtschaftlichen Skala, `boersenwert(b)` ebenfalls — die Skalengrenze zum Fondsgeld liegt wie gehabt zwischen `stufenwert` und `positionswert`. |
| **T27** (`parameter.toml`) | Zwei neue Schlüssel: `kippung` und `platzanteil`. `aufschlag` wird wiederverwendet. |
| **T33** (Marktkorb) | Der eingefrorene Mengenkorb bekommt einen dritten Summanden: `B` Plätze mit Menge `tiefe[b]` und Kurs `index[b]`. Bei `L = 9` sind das 27 Körbe, 9 Anleihen und 30 Plätze. Währungen bleiben draußen, Plätze nicht — sie tragen eine Kapitalisierung. |
| **T47** (`marktanteil`) | Dritter Summand in `korbbestand`, gebildet aus `boersenwert(b)` und `|stufen| · stufenweite`; ohne Beteiligungsanteil, weil es auf Plätzen keine Beteiligung gibt. |
| **T39** (Kursregeln ohne Adresse) | `weltzins`, `zielzins(b)`, `zielkurs(b)`, `leitkurs(b)`, `zinsfaktor(b)` und `boersenwert(b)` sind Funktionen des Zustands, keine Adressen — dieselbe Bauart wie `anleihekurs` und `landespreis`. |
| **Nachahmer- und Stoßregel** | **Die einzige Stelle, an der dieser Abschnitt auf eine fremde Formel zeigt, statt sie hinzuschreiben.** Der Aufschlag auf `index[b]` soll derselbe sein wie der auf einen Land×Sektor-Korb, mit `nachahmer[b]` an der Stelle von `nachahmer[l][s]` und `boersenwert(b)` an der von `korbwert(l,s)`. Liest die vorhandene Regel jedoch `kapitalstock[l][s]` unmittelbar statt über den Korbwert, trägt die Übertragung nicht, und dann ist das ein Befund gegen diese Zeile — nicht gegen die Schicht. Der Architekt sagt, welcher der beiden Fälle vorliegt. |
| **T37 / die Prüfgegenstände** | **Durch diese Schicht unverändert.** Ein Börsenplatz trägt keine Sollreihe und keine Handelszeile und kommt in keinem Prüfgegenstand vor; der Handelsblock bleibt bei `G·(G−1)·2` über die **Gebiete**, nicht über die Plätze. *Berichtigt am 2026-09-06: Hier stand „Börsenplätze sind Spielländer (Verweis auf Paket 0117)". Ein Platz ist kein Land — die Zeile trägt ohne die Klassenzuordnung, weil die Schicht ein Blatt ist. Bewegt werden die Prüfgegenstände nicht von dieser Schicht, sondern von der Länderwahl aus Paket 0118: 16 → 28.* |
| **Modus `weltlauf`** | Die zweite Schicht wird **nicht gerechnet**; ihre `5·B` Adressen behalten ihre Startwerte, wie der Fondsblock und die Nachahmerzähler. Die Menge der je Modus geschriebenen Adressen ist damit weiterhin fest und wächst im Weltlauf nicht. Der Weltlauf kostet unverändert `R` Weltschritte. |
| **Schranke am Leitzins** | Bleibt, wie sie ist (`leitzins ≥ 1 − aufschlag`), und deckt `zins[b]` mit ab: `zins[b]` ist ein wiederholtes Mittel von Werten oberhalb dieser Schranke. **Keine zweite Schranke nötig.** |
| **Laufzeitbudget (Abschnitt 10)** | Je Weltschritt kommen `B` Plätze zu je drei Halbierungen und einer Bewertung hinzu. Keine Iteration, keine Suche, keine Handelszeile — der Zuwachs ist linear in `B` und trifft nur die drei Selbstspielmaße, nicht den Weltlauf. |

**Der Abzählschritt aus T45 geht mit dem neuen Block auf**, weil jede der `5·B` Adressen
ihren Herkunftseintrag in der Feldtabelle unter *Was ein Börsenplatz trägt* hat.

### Neu aus Paket 0054 — R fällt von 24 auf 20, das Fenster auf 2001–2021

`technik.md` habe ich nicht angefasst. **Der größte Teil dieser Liste ist keine Änderung,
sondern eine Probe:** T40 bildet `R = manifest.stuetzstellen − 1` und leitet alles Weitere
zur Laufzeit ab, also genügt eine geänderte Zahl im Manifest. Was hier steht, sind die
Stellen, an denen `technik.md` eine Zahl **ausgeschrieben** hat oder eine Regel auf dem
Startjahr 1997 steht.

| war (`technik.md`) | ist | betrifft |
|---|---|---|
| Beispielspalte „bei R = 24": Bänder 1.000…24.000 / 25.000…28.000 / 31.000…54.000, Drittel 1-8 / 9-16 / 17-24, Gewinnschwelle 24.000, Suchbotpartie 1.464, Maß-1-Kosten 9.024 | **bei R = 20**: 1.000…20.000 / 21.000…24.000 / 31.000…50.000, Drittel **1-6 / 7-13 / 14-20**, Gewinnschwelle **20.000**, Suchbotpartie **1.220**, Maß-1-Kosten **6.320**. Die Formeln daneben sind unverändert richtig | T40, Tabelle abgeleiteter Größen |
| T24: „jede der **31** Sollreihen … über **25** Stützstellen ohne Füllung" | **27** Sollreihen über **21** Stützstellen. Reihe 9 ist keine Sollreihe mehr und fällt damit aus dem Verbot; ihr Pfad darf gefüllt und gekennzeichnet werden | T24 |
| T37: drei Klassen, davon `gesetzt` = Leitzins (4) | **zwei Klassen**: `frei` (23) und `abgeleitet` (4). Die Klasse `gesetzt` entfällt, weil ihre einzige Reihe keine Sollreihe mehr ist. **Statt eines Fehlermaßes gilt für den Leitzins eine Invariante:** Modellwert ≠ gesetzter Pfad ist ein harter Fehler | T37 |
| T42: Ratenreihen sind Verbraucherpreise, Wechselkurs, **Leitzins**; `S` = 25 | Ratenreihen sind Verbraucherpreise und Wechselkurs; `S` = **21**, Übergänge **20** | T42 |
| Reihenliste Nr. 9, Rolle „Start + Politikpfad + Soll (4, gesetzt)" | **„Start + Politikpfad"**. Die Zeile bleibt sonst unverändert — Dimension, Einheit, Quelle | Abschnitt 7 |
| T23 Punkt 8: DE-Leitzins `exogen_ab = 1999`, „im Prüfjahrgang also Runde 3"; Wechselkurs `verkettet_ab = 1999` | Beide Bruchjahre liegen **vor** dem Fenster. `exogen_ab_runde = bruchjahr − startjahr + 1` wird für sie **≤ 0**, und dafür braucht die Regel eine Lesart: **`≤ 0` heißt „gilt von Runde 1 an"**, nicht „ungültig" und nicht „nie". Die Felder bleiben, weil die Spieljahrgänge vor 2001 sie brauchen | T23 Punkt 8, T40 |
| T23 Punkt 5: `leitzins_start[l]` = erste Stützstelle des Politikpfads | unverändert richtig, jetzt der Wert von **2001** | T23 Punkt 5 |
| Größenordnung „5 Gebiete × **25** Jahre × rund 30 Reihen", Handel `40 × 25 × 8` | **21** Jahre; die Schätzung fällt entsprechend | T23, Schlusssatz |
| T22/T23: Prüfjahrgang **1997**–2021 | **2001–2021** | überall, wo das Startjahr als Zahl steht |

#### Nachtrag desselben Tages: die Tabelle oben war nicht vollständig

Sie ist entstanden, indem ich die T-Nummern durchgegangen bin, die R oder das Startjahr
**definieren**. Das findet jede Regel und keine Erwähnung. Ein zweiter Durchgang, diesmal
über jede *Zahl* in `technik.md` statt über jede *Regel*, hat sieben weitere Stellen
ergeben; sechs davon stehen außerhalb eines T-Blocks, und genau deshalb hat der erste
Durchgang sie nicht gesehen. Keine ist eine Regel, alle sind ausgeschriebene Zahlen. Die
beiden Tabellen zusammen sind die Liste — **die erste ist ergänzt, nicht ersetzt.**

| war (`technik.md`) | ist | betrifft |
|---|---|---|
| **Frontmatter Z. 12**: „im Prüfjahrgang 1997-2021 ist R = 24, eine Suchbotpartie kostet R × 61 = 1.464 Weltschritte" | „im Prüfjahrgang **2001–2021** ist **R = 20** … **20 × 61 = 1.220**" | Frontmatter, Schlüssel `partie` |
| T23 Punkt 2: „**Sollreihen** für die **31** Reihen aus `spiel.md` plus den Handelsblock" | **27** Reihen | T23 Punkt 2 |
| Abschnitt 7, Schlusssatz der Reihenliste: „Die **31** Sollreihen sind die Zeilen 1, 2, 8, **9**, 10 und 11 (4+12+4+**4**+3+4)" | „Die **27** Sollreihen sind die Zeilen 1, 2, 8, 10 und 11 (**4+12+4+3+4**)". Zeile 9 fällt aus dieser Aufzählung, **nicht** aus der Reihenliste — sie bleibt als Start und Politikpfad | Abschnitt 7 |
| T30, Prüfungstabelle Nr. 8: „**31** Sollreihen plus Handelsblock" | **27** | T30 |
| T43: „… fängt eine falsche Implementierung in fünf Runden statt in einer **24**-Runden-Partie" | **20**-Runden-Partie | T43 |
| Abschnitt 10, Laufzeitbudget: die ganze Tabelle **und** ihre Nachzählzeile stehen auf `R = 24` | Zeile für Zeile in der Zahlentabelle darunter | Abschnitt 10 |
| Abschnitt 13: „der Jahrgangsbau **1997** … **25** Stützstellen ohne Füllung für alle **31** Reihen … und der IFS-Leitzins ist nur durch ein Indiz gestützt" | Jahrgangsbau **2001**, **21** Stützstellen, **27** Reihen. Hier ändert sich mehr als drei Zahlen: Der Halbsatz zum IFS-Leitzins begründet, warum das Paket Entwurfsrisiko trägt — und der Leitzins ist seit heute keine Sollreihe mehr. **Das Paket trägt weniger Risiko, als dort steht** | Abschnitt 13 |

**Abschnitt 10 im Einzelnen, damit es eine Substitution bleibt und keine Rechnung.** Jede
Zeile ist aus R neu gerechnet und **nicht** aus der alten Tabelle skaliert:

| Zeile | war (R = 24) | ist (R = 20) |
|---|---:|---:|
| eine Partie, Heuristikbot | 24 | **20** |
| eine Partie, Suchbot | 1.464 | **1.220** |
| 1.000 Partien, Heuristikbot | 24.000 | **20.000** |
| 1.000 Partien, Suchbot | 1.464.000 | **1.220.000** |
| Entscheidungsdichte, K=30, ein Startwert | 9.024 | **6.320** |
| Entscheidungsdichte, 50 Startwerte | 451.200 | **316.000** |
| Strategievielfalt, 126 × 20 | 3.689.280 | **3.074.400** |
| Optimumsverschiebung, zwei Fenster | 7.378.560 | **6.148.800** |
| Bruchlauf, 10.000 Zufallspartien | 240.000 | **200.000** |
| Beschränktheit, 200 Runden | 200 | **200 — unverändert**, die Zeile prüft 200 gesetzte Runden und nicht R |
| Rückvergleich, ein Weltlauf | 24 | **20** |
| Regressionsbestand, 1.000 Partien | 24.000 | **20.000** |
| **Nachtlauf gesamt** | 11.783.264 | **9.759.420** |

Die Nachzählzeile darunter lautet damit: `Σ(R+1−t)` für `t = 1…20` ist `210`, also
`30 × 210 = 6.300` je Startwert, zuzüglich 20 Weltschritte für die Trägerpartie ergibt
**6.320**; mal 50 Startwerte **316.000**. `1.220 = 20 × 61`,
`3.074.400 = 126 × 20 × 1.220`, `6.148.800` das Doppelte davon; die drei Maße zusammen
**9.539.200**, so wie dieses Dokument es oben rechnet. Der Nachtlauf ist
`9.539.200 + 200.000 + 200 + 20 + 20.000 = 9.759.420`. `126 = C(9,4)` bleibt stehen, es
hängt nicht an R. Die beiden Zeitspalten gehören dem Architekten: Sie folgen aus der
ersten Spalte und einem `ticks_je_sekunde`, den es weiterhin nicht gibt.

**Auch die Kalibrierschleife am Ende von Abschnitt 10 steht auf der alten Zahl.** Tausend
Parametersätze über den vollen Maßsatz kosten `1.000 × 9.539.200` = **9,54 Milliarden**
Weltschritte statt 11,52, beim Planwert also rund **26,5 Stunden auf einem Kern und 3,3 auf
acht**. Die verkürzte Nachtfassung wird `10 × 6.320` = **63.200** für Maß 1 und
`126 × 5 × 1.220` = **768.600** für Maß 2. Der Schluss des Abschnitts — in voller Breite
keine Nachtaufgabe, verkürzt nachtfähig — ändert sich dadurch nicht.

**Zwei Dinge, die ich nachgerechnet habe, damit du es nicht musst.** Erstens hält die
Schranke `R ≤ 26` aus T40 mit Abstand: Das Band „überlebt" endet bei 24.000, das Todesband
beginnt bei 31.000, 7.000 Milli-Runden Luft statt 3.000. Zweitens bleibt der Bereichstest
`1.000 … R × 1.000 + 30.000` gültig und ergibt jetzt **1.000 … 50.000**.

**Und eine Stelle außerhalb von `technik.md`, die ich nur benennen darf:** `reihen.toml`
führt Reihe 9 mit `t37_klasse = "gesetzt"` und `rolle_tabelle = "Start + Politikpfad + Soll
(4, gesetzt)"`. Beides ist ab heute falsch. Die Datei gehört dem Datenbauer; das ist ein
Folgepaket für ihn, zusammen mit dem Leitzinspfad für Deutschland und China (siehe *Offene
Entwurfsfragen*). Ebenso benannt und nicht angefasst: `daten/deckungsbefund-1997.md` behält
seinen Namen und seinen Inhalt — er hat das Fenster 1997 gemessen, und das bleibt richtig.

### Neu aus Paket 0021 — der Schaden in Gegenkraft 5

Fünf Stellen, keine davon eine Entscheidung. `technik.md` habe ich nicht angefasst; Paket
0011 arbeitet darin.

| war (`technik.md`) | ist | betrifft |
|---|---|---|
| T50: „*Wie hoch* der Schaden eines Sektors ist, bleibt Sache von `spiel.md`"; Abschnitt 12 Punkt 3 meldet die Lücke | Die Vorschrift steht im Abschnitt *Der Schaden in Gegenkraft 5*: `mal_geteilt(menge, verschiebung, 10.000)` je Land und Instrument, vier Zeilen | T50, Abschnitt 12 Punkt 3 |
| `handelsvolumen(l)` über beide handelbaren Sektoren zusammen | dazu die sektorweise Fassung `handelsvolumen(l, s)`; ihre Summe über s ist die alte Größe, die Definition ändert sich nicht | T48 Nr. 11 |
| `parameter.toml` ohne Lastsatz für die Finanzmarktregulierung | neuer Schlüssel **`regulierung_last`**, Klasse 3, Basispunkte des BIP je Regulierungsstufe, kalibriert wie `gegenlobby_satz` | T27 |
| `lobbypunkte_aus_schaden` mit Aufrufort, ohne Aufrufzahl | **16 Aufrufe je Runde**, sämtlich in Schritt 5; dazu **106** Lesezugriffe und 16 Schreibzugriffe, aufgeschlüsselt im Abschnitt (die 120 der Fassung vom 2026-09-02 waren falsch, siehe Befundabarbeitung) | T50, Kostenzeile in Abschnitt 10 |
| T30 Prüfung 6 prüft `0 ≤ gegendruck ≤ druck_max`, ohne dass ein Erzeuger die Grenze hielte | Die Obergrenze steht jetzt im Entwurf als `min(druck_max, …)`; die Prüfung bleibt, sie ist nun eine Probe und keine Hoffnung | T30 |

**Was sich ausdrücklich nicht ändert:** keine Zustandsadresse, die 310, der Abzählschritt
aus T45, die drei Skalenübergänge aus T50, die acht Kanäle, R, die vier Maße und ihre
Schwellen. Die Vorschrift liest ausschließlich Größen, die `daten/adressen.md` führt, und
drei Funktionen aus T48.

### Neu aus Paket 0039 — die Zollzeile misst nur noch den Keil

Vier Stellen, und die erste ist die einzige, an der `technik.md` etwas **hinzubekommt** statt
ersetzt zu werden. Angefasst habe ich sie nicht.

| war (`technik.md`) | ist | betrifft |
|---|---|---|
| T28 nennt „der Zollkeil je Gebiet auf dem Weltpreis", ohne ihn hinzuschreiben | `weltpreis_mit_zoll(l,s) = mal_geteilt(welt.preis.<s>, 10.000 + zollstand(l), 10.000)`, im Abschnitt *Der Zollkeil ist multiplikativ*. Die additive Lesart ist gegen T5 nicht bildbar | T28 |
| `preishub(l, s)` als Differenz der Sektorpreise | entfällt; an seine Stelle treten `keilhub(l, s)` und `preishub_zoll(l, s)`, beide Klasse 5. `land.<l>.sektor.<s>.preis` wird von Gegenkraft 5 **nicht mehr gelesen**, `welt.preis.<s>` neu | T50, T48 |
| Kostenzeile mit 120 Lesezugriffen (aus der Fassung vom 2026-09-02) | **106**, aufgeschlüsselt in der Lesetabelle. Die 120 zählten den Zollstand doppelt mit 16, obwohl die alte Zollzeile ihn gar nicht las; die 112 des Prüfbefunds galten für die alte Zeile | T50, Kostenzeile in Abschnitt 10 |
| `durchgriff` wird allein in der Markträumung (Schritt 4) gebraucht | zusätzlich in Schritt 5, für `preishub_zoll`. Es bleibt eine Jahrgangskonstante nach T23 Punkt 5 und wird keine Adresse | T23 Punkt 5, T50 |

**Und eine Bedingung für den Jahrgangsbau, keine für dich:** Der Ausdruck
`mal_geteilt(mal_geteilt(welt.preis_start(s), schrittweite[zoll], 10.000), durchgriff(l,s), 10.000)`
muss für jedes der acht Land×Sektor-Paare mindestens 1 ergeben, sonst ist die Zollzeile dort
stumm. Die Zahl, die das erfüllt, kommt aus der Kalibrierung.

### Neu in Fassung 5 — acht Stellen, und keine davon ist eine Zahl

Der neue Abschnitt *Was ein Korb wert ist* ist Entwurf und braucht von dir eine Aufnahme,
keine Entscheidung. Was daraus in `technik.md` nachzuführen ist:

| war (`technik.md`) | ist | betrifft |
|---|---|---|
| T47 verwendet `korbwert(l, s)` und `positionswert(p)`, gebildet werden sie nirgends | beide gebildet, dazu `anleihewert`, `waehrungswert`, `anleihekurs`, `schuld` und `handelsvolumen` | T47 |
| T33: „Modellmarktwerte", der Mengenkorb ohne Menge | Marktkorb = Σ der 12 `korbwert` + Σ der 4 `anleihewert`; die Mengen sind Kapitalstock und Schuld, die Kurse Sektorpreis, Anleihekurs und Wechselkurs | T33 Punkt 1 und 3 |
| Skalengrenze in T47 nicht gezogen — **Befund 2 der Runde 6** | `korbwert` bleibt volkswirtschaftlich, die Umrechnung liegt je Bewertung einmal am äußersten Aufruf; der zweite Weg (`korbwert` in Cent) ist ausgeschlossen, weil T33 denselben Korb bewertet | T5, T47 |
| T27: `stufenweite` ohne Bedeutung | **Anteil in Zehntausendsteln des Marktes**, kein Geldbetrag; dazu ein neuer Schlüssel `aufschlag` in Basispunkten | T27 |
| T23 Punkt 5: Konstanten des Jahrgangs sind zehn `durchgriff`-Werte | dazu **`leitzins_start[l]`**, vier Werte, erste Stützstelle des Politikpfads aus Reihe 9 | T23 Punkt 5 |
| Reihe 3 liefert **einen** Kapitalstock je Gebiet, T15 führt **drei** je Gebiet | Startregel: Aufteilung über die normierten Sektoranteile, dieselbe Regel wie bei der Wertschöpfung; der Rang `Datenanker` bleibt | T23 Punkt 1, Reihenliste Nr. 3 |
| „sieben rundenübergreifende Kanäle"; „gibt es einen **achten** Kanal, und der ist ein Befund" | **acht**; „einen **neunten**" | Z. 374 (T38-Begründung), T30 Prüfung 6 |
| Leitzins ohne Untergrenze | Untergrenze **`1 − aufschlag`**, vom Jahrgangsbau gegen den historischen Politikpfad geprüft; sie hält den Anleihenenner positiv | T23, T27, T40-Umfeld |

**Was sich ausdrücklich nicht ändert:** keine Zahl der vierten Fassung, keine
Zustandsadresse, R, die Ergebnisbänder, die vier Maße, ihre Schwellen und alle
Kostenzeilen. Der Abzählschritt aus T45 geht unverändert auf.

**Und zwei Entscheidungen aus deinem Abschnitt 12 nehme ich an statt sie zurückzuholen:**
die Ausschlussregel für Stützstellen mit `soll = 0` (T42) und die elf Startwerte in T46.
Beide folgen aus Regeln, die schon dastehen; ich habe je eine Zeile gelesen und keine
gefunden, die ich anders setzen würde. Deine Beobachtung 2 zur Tabelle *Größen ohne
Datenanker* ist oben eingearbeitet — die Tabelle verweist jetzt auf T46, statt eine
Abschließlichkeit zu behaupten, die sie allein nicht haben kann.

---

**Ab hier steht kein geltender Wert mehr, sondern das Protokoll.** Alle folgenden
Abschnitte — die erledigten Nachziehtabellen der Fassungen 3 und 4 und die
Befundabarbeitungen — sind **datierte Nachweise abgeschlossener Läufe**. Die Zahlen darin
stehen auf dem R, das zum Zeitpunkt ihrer Prüfung galt (`R = 24`, Fenster 1997–2021), und
sie werden **nicht** nachgezogen. Der Grund ist derselbe, aus dem der Chronist keine alten
ADRs ändert: Ein Protokoll, das man an den neuen Stand anpasst, belegt nichts mehr — man
könnte an ihm nicht mehr ablesen, was der Prüfer damals gesehen und der Entwerfer damals
geantwortet hat. **Wer nach dem geltenden R sucht, liest oberhalb dieser Linie.** Was
unterhalb steht und was sich seither daran geändert hat, führt die Nachziehtabelle *Neu aus
Paket 0054* Zeile für Zeile auf.

---

### Aus Fassung 4 — vom Architekten am 2026-09-01 erledigt

Steht nur noch als Nachweis hier; alle vier sind in `technik.md` Fassung 5 nachgeführt und
vom Prüfer der Runde 6 einzeln nachgerechnet worden. *Die Zahlen dieses Abschnitts gelten
für `R = 24`; siehe die Linie darüber.*

| war (`technik.md`) | ist | betrifft |
|---|---|---|
| Ergebnisband „überlebt" `(R+1)×1.000 … +2.000`, 25.000 … 27.000 | **`(R+1)×1.000 … +3.000`, 25.000 … 28.000** (keine Kappung mehr) | T40, Bandtabelle |
| unerreichbare Lücken 24.001 … 24.999 und **27.001** … 30.999 | 24.001 … 24.999 und **28.001** … 30.999 | T34, Bandprüfung |
| T44: „Die einzige Abweichung von der Ergebnisgröße ist die Kappung" | **entfällt** — der Zweig „überlebt" von `B` und die Ergebnisgröße sind jetzt dieselbe Formel; `B`s eigene Zahlen (`e ≤ 2.000`, 25.000 … 28.000) bleiben richtig | T44 |
| `Fondsvermögen = Kasse + bewertete Positionen − Hebel` | **`… + bewertete Beteiligungen − Hebel`**, bewertet zum Ausstiegswert | Schritt „Abrechnung", T30 Prüfung 2 (Invariantentest), T44 `v(z)` |

**Zwei Dinge, die ich nachgerechnet habe, damit du es nicht musst.** Erstens: Die Schranke
`R ≤ 26` aus T40 bleibt unverändert gültig — mit dem breiteren Band ist sie jetzt genau die
Disjunktheitsbedingung statt einer großzügigen; das Band kostet also keine Runde
Partielänge. Zweitens: Der Bereichstest `1.000 … R × 1.000 + 30.000` ist unberührt, weil
sein oberes Ende aus dem Todesband kommt.

**Und drei Stellen, die durch diese Fassung *entfallen* statt sich zu ändern:** die offene
Frage aus Abschnitt 12 Punkt 3 (Beteiligungen, oben entschieden), die Klasse-2-Erörterung
in T44 (sie hing an genau dieser Frage) und der Nachtrag in T23 Punkt 1 — er bleibt
richtig, ist aber jetzt doppelt, weil die 32 Adressen in der Entwurfstabelle stehen, die
sie zugesagt hatte.

### Aus Fassung 3 — vom Architekten am 2026-09-01 erledigt

Steht nur noch als Nachweis hier; nichts davon ist offen. *Die Zahlen dieses Abschnitts
gelten für `R = 24`; die Spalte „ist" ist der Stand vom 2026-09-01 und nicht der heutige.
Was seither an ihre Stelle getreten ist, steht in der Nachziehtabelle **Neu aus Paket
0054**.*

| war | ist | betrifft |
|---|---|---|
| 28 Runden, 1995–2023, 29 Stützstellen | **R = 24**, 1997–2021, 25 Stützstellen | Frontmatter, T22, T23, T24, Abschnitt 10 |
| Suchbotpartie `28 × 61 = 1.708` | **`24 × 61 = 1.464`** | Frontmatter, Abschnitt 10, 12 |
| Maß 1 je Startwert 11.368 | **9.024** (Formel korrigiert, siehe Befund 11) | Abschnitt 10 |
| Maß 2 4.304.160 / Maß 3 8.608.320 | **3.689.280 / 7.378.560** | Abschnitt 10 |
| Nachtlauf 13.789.108 | neu zu summieren; die drei Maße tragen **11.519.040** | Frontmatter, Abschnitt 10 |
| Ergebnisbereich 1.000 … 58.000 | **1.000 … 54.000** | T34 |
| `handelsanteil` | **`durchgriff`**, neue Bildungsregel, bleibt Klasse Anteile | T5, T23 Punkt 5, T25, T28, Reihenliste Nr. 16 |
| `landespreis` undefiniert | **Sektorpreis der Vorrunde**, Startwert 10.000 | T28, T15 (keine neue Zeile) |
| Rückvergleich als Partie | **Modus `weltlauf`**, Fondsteilsystem aus, Instrumente exogen | T30 Prüfung 8, T37 |
| Maß-4-Abnahme offen (Abschnitt 12) | **16 Prüfgegenstände, Toleranz 2**; Handelsblock nach deinem Vorschlag | T37, Abschnitt 12 |
| DE `exogen_ab` in Runde 5 | **Runde 3** (1999 liegt jetzt am Ende von Runde 2) | T23 Punkt 8 |
| 50 Startwerte „Vorgabe des Prüfstands" | jetzt in `spiel.md` gesetzt, samt Zusammenfassungsregel | Abschnitt 10 |

Neu hinzugekommen und ohne Vorbild in Fassung 2: das **Vorratsverfahren** (Profil →
Aktionen), die **HS92-Konkordanz** und die Tabelle **Größen ohne Datenanker**. Alle drei
sind Entwurf, nicht Architektur — sie brauchen von dir nur eine Aufnahme, keine
Entscheidung.

## Befundabarbeitung — Prüfung 0039 vom 2026-09-03, Paket 0055

Ein Befund, `Schwere: gering`, ausdrücklich kein Rücklaufgrund; das Urteil der Prüfung war
`geprueft` und bleibt es. Diese Abarbeitung hebt kein bestandenes Kriterium an.

**Befund 1 — die Vergleichszahl 32.850.000 gehört nicht zu Zustand B: behoben, auf dem Weg,
der die Tabelle stärkt statt sie zu entlasten.** Der Widerspruch ist bestätigt, und ich habe
ihn an beiden Stellen einzeln nachgemessen statt ihn zu übernehmen: Die Vergleichszahl war
mit einem Handelsvolumen von 1,5·10^9 gebildet, die Tabelle im selben Abschnitt gibt Zustand B
zusammen 1,4·10^8. Die Zahl selbst ist richtig, nur für einen anderen Zustand.

**Warum Weg A und nicht Weg B.** Der Prüfer bot beides an: die richtige Zahl einsetzen, oder
die falsche stehen lassen und ihren Zustand danebenschreiben. Drei Gründe für Weg A, und der
erste allein genügt:

1. **Der Vergleich soll die Entscheidung messen, nicht illustrieren.** Was der Sockel kostet,
   zeigt nur ein Vergleich, in dem alte und neue Vorschrift **dieselben** Eingaben sehen. Mit
   der Zahl eines fremden Zustands vergleicht man zwei Regeln auf zwei Welten; das ist keine
   Größenordnung, sondern eine Anekdote.
2. **Die Tabelle ist als Regressionsfall gebaut**, und ein Regressionsfall mit einer Zahl aus
   einem anderen Zustand daneben ist genau die Falle, gegen die dieses Paket geschrieben ist —
   Weg B beschriftet sie nur um, statt sie zu räumen.
3. **Die 32.850.000 geht nirgends verloren.** Sie steht mit ihrem eigenen Zustand im Beispiel
   der Ursachenkette unter *Warum die Zollzeile nur den Keil misst* und ist dort richtig; eine
   zweite, umbeschriftete Kopie hätte den Leser an der Stelle, an der er rechnen soll, zwischen
   zwei Welten wechseln lassen.

Weg A verlangt eine Eingabe, die die Tabelle nicht führte: den Sektorpreis der Vorrunde, den
allein die Vorfassung liest. Er steht jetzt als eigene Zeile mit dem Startwert 10.000 aus der
Preisträgheitsregel und ist als das gekennzeichnet, was er ist — die einzige Zeile der
Tabelle, die in keine Zahl der Spalten darunter eingeht.

**Nachgerechnet, nicht abgeschrieben.** Die 8.472.000 des Prüfers habe ich Schritt für
Schritt selbst gebildet und bestätige sie; die Rechnung steht im Abschnitt, damit der nächste
Leser sie nicht glauben muss. Der einzige Freiheitsgrad ist die Rundung des Zwischenwerts
`10.795,2`, und beide Lesarten führen auf denselben Beitrag — das steht dort ebenfalls.

**Was ich nicht getan habe.** Keine der sieben Größen von Zustand A angefasst, die Null für
Zustand B ist die Null geblieben, die Entscheidung für Weg 1 und ihre Maß-2-Begründung sind
unberührt, die Zahl der Lesezugriffe kommt an keiner neuen Stelle vor, und die zweite
Fundstelle von 32.850.000 in der Ursachenkette ist unverändert. `technik.md`,
`daten/adressen.md` und die Kalibrierzahlen sind nicht angefasst.

## Befundabarbeitung — Prüfung 0021 vom 2026-09-02, Paket 0039

Zwei Befunde, beide `Schwere: mittel` beziehungsweise `gering`, keiner ein Rücklaufgrund.
Das Abnahmekriterium von 0021 war erfüllt; diese Abarbeitung ändert daran nichts und
beantwortet die Frage, die der Prüfer offengelassen hat.

**Befund 1 — die Zollzeile wächst auch dann, wenn niemand etwas tut: behoben.** Gewählt ist
**Weg 1**, den Zollkeilanteil der Preisverschiebung zu isolieren. Die Zerlegung ist exakt und
steht mit ihrer Herleitung im Abschnitt *Warum die Zollzeile nur den Keil misst*; sie zieht
genau den Summanden ab, der übrig bliebe, wenn der Zollstand stehen bliebe, und lässt den
Aktionsanteil unberührt. Die Begründung nennt Maß 2 wie verlangt und führt zwei weitere
Gründe. Weg 2 (`hub(l, zoll)` lesen) und Weg 3 (den Sockel behalten) sind einzeln mit Grund
verworfen, Weg 2 zusätzlich mit dem Selbstwiderspruch, den er gegen Zeile *Die Ordnung, die
das Argument trägt* erzeugt hätte. Der Prüfer kann `schaden(l, zoll)` jetzt für einen
Zustand ohne Aktion ausrechnen: Er ist **null**, und zwar ohne dass er die Form des
Zollkeils kennen müsste. Die Probe steht als Tabelle mit zwei Zuständen.

Was ich dabei **zusätzlich** gefunden habe und was den Befund verstärkt: Die alte Größe
differenzierte den Sektorpreis, und `technik.md` T8 basiert genau den bei Hyperinflation
neu. Eine Differenz über eine Neubasierung hinweg ist der Basiswechsel und nicht die
Preisverschiebung. Im Prüfjahrgang 1997 tritt der Fall nie ein, in den Spieljahrgängen vor
1997 schon. Die neue Fassung kann er nicht treffen.

**Befund 2 — die Lesetabelle zählt acht Zugriffe, die nicht stattfinden: behoben, mit
anderer Zahl.** Der Zählfehler ist bestätigt: Die 120 der Vorfassung zählten
`land.<l>.instrument.<i>.stand` zweimal mit 16, obwohl die damalige Zollzeile ihn nicht las.
Die 112 des Befunds sind für die damalige Zeile richtig nachgerechnet — sie sind aber nicht
die Zahl, die jetzt gilt. Nach der Entscheidung liest der Zoll seinen Stand wieder (zweimal
16 statt zweimal 12), dafür fallen beide Sektorpreiszeilen weg (zweimal 8) und die beiden
Weltpreise kommen hinzu: `112 + 8 − 16 + 2 =` **106**. Die Lesetabelle und die
Nachziehtabelle nennen beide diese Zahl, und die Zeilenzuordnung zur Instrumententabelle
steht in einer eigenen Spalte, damit sie nachzählbar ist statt nachvollziehbar.

**Was ich nicht getan habe.** `technik.md` habe ich nicht angefasst; was dort nachzuziehen
ist, steht in der Tabelle *Neu aus Paket 0039*. Keine neue Zustandsadresse, keine neue Reihe,
keine Kalibrierzahl. Die Bedingung an `schrittweite[zoll]` steht als Form ohne Wert.

**Und ein Vorschlag, der nicht in dieses Paket gehört, aber aus ihm folgt:** Die Fassung des
Zollkeils war bis heute nirgends aufgeschrieben, obwohl sie seit der zweiten Fassung in der
Markträumung steht. Ich habe sie hier festgelegt, weil die Schadensvorschrift sie braucht
und weil T5 nur eine Lesart zulässt. Ob `technik.md` T28 sie übernimmt oder eine andere
Begründung dagegen hat, ist Sache des Architekten — widerspricht er, ist es ein Befund gegen
diesen Abschnitt und nicht gegen die Zollzeile.

## Befundabarbeitung — Prüfung der Runde 6 vom 2026-09-01

**Befund 1, `positionswert(p)` und `korbwert(l, s)` ohne Entstehungsregel — behoben, und der
Befund war richtig.** Der Abschnitt *Was ein Korb wert ist, was eine Stufe ist und was eine
Anleihe kostet* bildet beide, dazu `anleihewert`, `waehrungswert` und den `anleihekurs`, den
der Prüfer im fünften Schritt seines Nachweises eigens benannt hat („für die vier
Anleihe-Steckplätze gibt es nicht einmal einen Preis"). Drei Entscheidungen stecken darin,
und ich nenne sie einzeln, weil
jede anders hätte ausfallen können:

1. **Der Korb hängt am Kapitalstock, nicht an der Wertschöpfung.** Grund ist nicht die
   Volkswirtschaftslehre, sondern T33: Der eingefrorene Mengenkorb braucht eine Menge, und
   ein Jahresstrom ist keine. Der zweite Grund ist die Wirkungskette — hinge der Korbwert an
   der Wertschöpfung, überdeckte jede Produktionsschwankung die Kursänderung, die dieses
   Spiel erklären will.
2. **Eine Stufe ist ein Anteil, kein Betrag.** Das ist die Entscheidung, die den Zustand
   rettet: Ein fester Geldbetrag verlangte je Steckplatz den Einstandspreis, also zwanzig
   weitere Adressen. Als Anteil folgt der Wert vollständig aus dem heutigen Zustand, long
   und short sind dieselbe Formel, und der Anteil, den Gegenkraft 1 und der Preisstoß lesen,
   ist dieselbe Zahl.
3. **Der Anleihekurs ist eine Regel, keine Adresse** — die Bauart, die T39 für `landespreis`
   schon trägt. Er ist der Kurs einer ewigen Anleihe, im Startjahr per Konstruktion 10.000,
   streng fallend im Zins und ohne Kappung positiv; die Schranke sitzt am Leitzins, wo sie
   hingehört, und der Jahrgangsbau kann sie prüfen.

**Die Frage nach der Größenordnung, die der Befund mitstellte, ist beantwortet, aber nicht
so, wie er sie stellte.** „Wie groß ein Anteil in Zehntausendsteln überhaupt sein kann"
hängt am Verhältnis von Startkapital zu Marktgröße, und dieses Verhältnis hat genau einen
Regler. Ein zweiter — ein „investierbarer Anteil" des Kapitalstocks — wäre mit dem
Startkapital redundant gewesen und hätte der Kalibrierung eine Dimension ohne Wirkung
gegeben. Er ist deshalb nicht eingebaut; stattdessen stehen die **zwei Bedingungen** unter
*Offene Entwurfsfragen*, die ein zulässiger Parametersatz erfüllen muss, und beide sind am
Prüfstand ablesbar.

**Und ein Kanal ist dabei aufgefallen, den der Befund nicht verlangt hat.** Sobald die
Bewertung ein gerechneter Schritt ist, wird sichtbar, dass *Vermögen → Lobbybudget →
Instrument → Kurs → Bewertung → Vermögen* eine Rückkopplung über die Rundengrenze ist — die
Schleife, an der dieses Genre stirbt. Sie stand nicht in der Kanaltabelle. Sie steht jetzt
als Kanal 8 mit vier Dämpfungen, von denen drei mit dem Erfolg wachsen. **Das ist der teure
Teil dieses Laufs und der einzige, der eine Zahl in `technik.md` bewegt:** T30 Prüfung 6
und die Begründung zu T38 sprechen von „sieben" und vom „achten Kanal als Befund"; beides
wird um eins größer.

**Befund 2, `beteiligung_wert` mischt Tausend USD und US-Cent — behoben, soweit er dem
Entwurf gehört, und die Wahl zwischen den beiden Wegen ist getroffen.** Der Prüfer hat den
Befund dem Architekten zugewiesen und zwei Auswege offengelassen. Der Entwurf entscheidet
zwischen ihnen, weil nur einer mit T33 verträglich ist: **`korbwert` bleibt eine
volkswirtschaftliche Größe**, denn der Marktkorb bewertet dieselben zwölf Körbe und ist
selbst volkswirtschaftlich. Führte man `korbwert` in Cent, gäbe es zwei Skalen für einen
Korb und damit zwei Bewertungen für einen Korb — genau das, was T47 mit „eine Bewertung,
nicht zwei" ausschließt. Die Umrechnung liegt deshalb auf der Grenze zum Fondsbuch und
findet je Bewertung **einmal am äußersten Aufruf** statt, nachdem die Anteile verrechnet
sind. Welche Funktion sie leistet, bleibt deine Sache; wo sie steht, ist Entwurf.

Der Rechenfehler selbst — Faktor 100.000, Kasse fällt um das Hunderttausendfache dessen, was
das Beteiligungsvermögen steigt, Todesart 1 in derselben Runde — ist damit an seiner Wurzel
geschlossen und nicht durch eine Klammer. Der Prüfer hat recht damit, dass er Maß 2 von
Bauart wegen getroffen hätte: Klasse 2 hätte die erste Abnahmehälfte nicht bestehen können,
und im Prüfstand hätte es wie ein Balanceproblem ausgesehen.

**Die drei Punkte aus „Geprüft und nicht gezählt", weil dieser Lauf ohnehin stattfand.**
Die Kostenaussage zu `B` ist eine Zeile des Architekten und keine Entwurfsfrage; ich rühre
sie nicht an. Die Doppelführung von `markt.wert` löst T45s Vorrangregel, und ich übernehme
die Auflösung. Die Skalenkonvention bei `einfluss` (0…100 in der Sicht, Zehntausendstel im
Speicher) ist erklärt und bleibt, wie sie ist — ich habe nachgerechnet, dass `e ≤ 2.000` in
beiden Einheiten gilt, weil `schwelle_e` in derselben steht wie `einfluss`.

**Was ich nicht angefasst habe:** die Meldung des Prüfers an den Projektmanager, dass der
Rücklaufzähler mit dieser Runde bei 3 von 3 steht und die Tabelle im Arbeitspaket seit
Runde 3 nicht nachgeführt ist. Das ist Ablaufsteuerung und nicht meine Rolle; ich schreibe
weder in das Arbeitspaket noch entscheide ich über `blockiert`.

## Befundabarbeitung — Prüfung der Runde 4 vom 2026-09-01

**Befund 1, `spiel.md` und `technik.md` widersprechen sich in der Steckplatzzahl — behoben,
und der Fehler war meiner.** Der Satz sagte „über 15 Runden … `3·ai` Steckplätze" und
mischte damit `k = 1` und `k = 3`. Er steht jetzt in der allgemeinen Form, die T43 schon
trägt: nach `5k` Runden `3k·ai` von `15k`, mit beiden Fällen ausgeschrieben. Die Probe zwei
Absätze darunter (fünf Runden, drei von fünfzehn) war die ganze Zeit richtig und ist jetzt
nicht mehr der Widerspruch zum eigenen Satz. Der Prüfer hat den Rechenweg von Hand
nachgerechnet, ich habe ihn gegen dieselbe Probe geprüft und komme auf dieselbe Zahl.

**Befund 2, die Aggregation des fehlenden Einflusses fehlt — behoben, aber nicht auf dem
vorgeschlagenen Weg, und der Unterschied kostet zwei Zahlen.** Die Aggregation ist
übernommen, wie der Prüfer sie vorschlägt und wie T44 sie für `B` schon schreibt: Summe
über die zwei Länder mit dem höchsten Einfluss, Gleichstand nach `LandId`. Beide Dokumente
rechnen dieselbe Größe damit gleich.

**Nicht übernommen habe ich die Kappung**, und das ist die eine Stelle, an der ich vom
billigsten Weg abweiche. Der Prüfer hat sie ausdrücklich stehen lassen dürfen — sie ist in
T44 begründet und war kein Befund. Aber dieselbe Begründung schlägt zurück: T44 verwirft
das Kappen für `B`, weil ein Fonds bei Einfluss null in beiden Ländern auf dem gekappten
Wert 1.000 säße und eine Verbesserung auf 60 Prozent der Schwelle **unsichtbar** bliebe.
Für das Partieergebnis gilt das eine Ebene höher: Die Kappung legte jeden Fonds mit
weniger als einer Schwelle Gesamteinfluss auf denselben Wert und glättete damit die untere
Hälfte des Ergebnisraums — genau dort, wo Maß 3 sein Argminimum sucht, wenn im Fenster kein
Profil das Mandat erreicht. Das ist der Fall, den der Befund selbst als den plausiblen
benennt. Ich hätte damit eine Blindheit eingebaut, die der Prüfstand nicht mehr findet,
weil sie kein Fehler ist, sondern eine Definition.

Gebraucht wird die Kappung ohnehin nicht: `einfluss` liegt nach Bauart in 0 … 100, also ist
jeder Summand per Konstruktion höchstens 1.000, und `fondsvermoegen > 0` gilt für jeden
lebenden Fonds. Die Schranke folgt jetzt aus der Rechnung statt aus einer Deckelung.
**Der Preis steht in „Was der Architekt neu rechnen muss" und ist zweimal eine Zahl:**
Ergebnisband 27.000 → 28.000 (T40) und Lückengrenze 27.001 → 28.001 (T34). Dafür entfällt
der Kappungsunterschied zwischen `B` und der Ergebnisgröße vollständig — zwei Formeln
werden zu einer, und die Stelle kann nicht mehr auseinanderlaufen. Nachgerechnet habe ich
auch, was der Befund nicht verlangte: Die Bänder bleiben disjunkt, und T40s Schranke
`R ≤ 26` gilt unverändert.

**Dazu zwei Punkte aus „Geprüft und nicht gezählt", weil dieser Lauf ohnehin stattfand.**
Der Prüfer hat beide ausdrücklich nicht als Befund gezählt; beide waren an mich adressiert,
und beide kosten hier eine Entscheidung statt eines weiteren Laufs.

1. **Gehören die zwölf Beteiligungen zum Fondsvermögen? Ja** — der Abschnitt *Was das
   Fondsvermögen ist* entscheidet es samt Bewertung zum Ausstiegswert. Ich lasse das nicht
   offen, obwohl es kein Befund ist: Fiele die Antwort später anders aus, könnte Klasse 2
   die erste Abnahmehälfte von Maß 2 von Bauart wegen nicht bestehen, und das sähe im
   Prüfstand aus wie ein Balanceproblem, obwohl es eine Definition wäre.
2. **Die 38 Adressen ohne Herkunftseintrag** (32 aus T23 Punkt 1, sechs ohne zulässige
   Eintragsart) stehen jetzt in der Entwurfstabelle, die von sich sagt, sie führe „alle
   übrigen, abschließend". Damit ist die Zusage der Tabelle wieder wahr, und T45 braucht
   keine neue Eintragsart.

**Was ich nicht angefasst habe:** die Bemerkung des Prüfers an den Projektmanager, dass ein
Rücklauf ohne Lauf des Spielentwerfers nicht schließbar war. Das ist eine Frage der
Ablaufsteuerung und nicht meine; dieser Lauf ist die Antwort darauf.

## Befundabarbeitung — Prüfung der zweiten Fassung vom 2026-08-31

**Befund 1, Prüfjahrgang 1995 nicht belegt — behoben, und der Befund war richtig.** Ich
habe die drei US-Sektoranteilsreihen selbst abgerufen (2026-09-01): 1997 bis 2021, an
beiden Enden wie beschrieben. Das Fenster ist 1997–2021, **R = 24**. Der teuerste Teil des
Befundes war nicht die Zahl, sondern ihre Verbreitung in zwölf abgeleitete Größen; deshalb
steht jede davon jetzt als Formel in R, und ein weiteres Kürzen des Fensters ist eine
Substitution statt einer Neufassung. Das ist die dritte Befundrunde zum Startjahrgang, aber
nicht dreimal derselbe Befund: erst ein Widerspruch zwischen Frontmatter und Text, dann
eine unbelegte Zahl, jetzt eine gemessene mit einer Fassung, die den Fehlertyp ausschließt.

**Befund 2, Rückvergleichslauf nicht durchführbar — behoben.** Maß 4 läuft im Modus
`weltlauf`: Fondsteilsystem vollständig abgeschaltet, keine Rendite, keine Todesart,
Politikinstrumente exogen. Damit gibt es weder den Nenner null noch den Tod in Runde 3. Die
zweite Lücke — `markt.wert` ohne Startwert — ist unabhängig davon geschlossen: Der
Startwert steht in der Tabelle *Größen ohne Datenanker* (Wert des Startkorbs zu
Startpreisen), und im Spielmodus sichert die Regel „Fondsvermögen ≤ 0 löst Todesart 1 in
derselben Runde aus", dass nie durch null geteilt wird.

**Befund 3, `handelsanteil` verlässt seinen Wertebereich — behoben, mit einer vierten
Lösung.** Der Prüfer nannte drei Auswege; ich nehme keinen davon unverändert. Der
Koeffizient heißt jetzt `durchgriff` und wird als `10.000·H/(H+N)` gebildet: monoton in
`H/N`, per Konstruktion in 0…10.000, ohne Kappung, ohne negatives Gewicht auf dem
Landespreis, ohne negative Preise. Die Rangfolge zwischen Ländern und Sektoren — das
Einzige, was das Argument trägt — bleibt exakt erhalten. Dass sein Zahlenwert keine
volkswirtschaftliche Bedeutung hat, steht ausdrücklich dabei; die Umbenennung soll
verhindern, dass ihn jemand für einen gemessenen Anteil hält.

**Befund 4, Profil → Aktionen nicht definiert — behoben.** Das **Vorratsverfahren** steht
oben mit Schritt, Zähler und Gleichstandsregel: `vi += 3·ai` je Runde, `vi −= 5` je
Steckplatz, drei Steckplätze je Runde, größtes `vi` gewinnt, Gleichstand nach kleinerer
Kennung. Alle drei Fragen des Befundes sind beantwortet — nicht runden und nicht ziehen,
`ai = 0` schiebt ans Ende statt zu verbieten, die Bündelgröße gehört nicht zum Profil. Für
den Suchbot ist ergänzt, wie das Profil die 60 Kandidaten einschränkt: über die
Artenzusammensetzung, gesucht wird nur über Ziele und Stufen.

**Befund 5, Maß 4 ohne Abnahmeregel — behoben.** Sechzehn Prüfgegenstände, nur die freien
Reihen, die drei Anteilsreihen eines Landes als **ein** Gegenstand, Toleranz zwei. Die
Rückfrage aus `technik.md` Abschnitt 12 ist damit beantwortet (die 23 freien entscheiden,
alle 31 werden berichtet), und die zweite Rückfrage zum Handelsblock ebenfalls: Der
Vorschlag des Architekten wird übernommen, Median über die 40 Ströme, schlechtestes Fünftel
ausgewiesen. Dazu kam eine Lücke, die der Befund nicht nannte und die dieselbe Stelle
betrifft: Für Preis- und Wechselkursreihen ist ein MAPE nach T8 gar nicht das verglichene
Maß; für sie gilt jetzt ein mittlerer absoluter Fehler auf der Jahresrate.

**Befund 6, `landespreis` nicht definiert — behoben, mit der Lesart, die der Prüfer als
wohldefiniert bezeichnet.** `landespreis` ist der Sektorpreis der Vorrunde, Startwert
10.000. Damit bleibt die Überschussfunktion monoton im Weltpreis, die Halbierung aus T28
ist zulässig, und es entsteht keine Fixpunktaufgabe. Die Größe braucht keine eigene Adresse
— sie **ist** der Sektorpreis, einen Schritt früher gelesen; der daraus entstehende
Preiskanal ist oben in die Kanaltabelle eingeordnet und gedämpft.

**Befund 7, Zusammenfassung über die 50 Startwerte fehlt — behoben.** Die 50 stehen jetzt
in `spiel.md`, und die Zusammenfassung auch: `Dichte(t, s)` gegen den Median **derselben**
30, dann Mittel über die 50 Startwerte. Der vom Prüfer benannte Fehlweg — ein gemeinsamer
Median über 1.500 Ergebnisse aus verschiedenen Jahrgangsstreuungen — ist als solcher
benannt und ausgeschlossen. Die Gesamtkostenzahl nennt nur noch die Summe der drei Maße,
also genau das, was dieser Entwurf selbst festlegt.

**Befund 8, sechs Profile ohne Familienaktion — behoben, durch die vom Prüfer als billig
bezeichnete zweite Variante.** Die sechs Profile `(0,0,0,a4,a5)` haben keinen
Strategiekern, laufen mit, werden berichtet und gehen in keine der beiden Abnahmehälften
von Maß 2 ein. Klassifiziert sind 120 Profile. Für Maß 3 bleiben alle 126 wählbar — dort
misst der Vektorabstand, nicht die Klasse.

**Befund 9, Schwelle zwischen zwei erreichbaren Werten — behoben.** Maß 3 verlangt jetzt
**0,4**, also genau ein verschobenes Fünftel; die Wertemenge `{0; 0,4; …; 2,0}` steht
daneben, damit die Kalibrierung sieht, worauf sie zielt.

**Befund 10, Ergebnisskala nicht streng geordnet — behoben.** Das Band „Mandat erfüllt"
endet bei `R × 1.000 = 24.000`, der überlebte Misserfolg beginnt bei `(R+1) × 1.000 =
25.000`. Kein Wert trägt zwei Bedeutungen, und Maß 2 kann als `E(p) ≤ 24.000` geschrieben
werden, ohne dass die beiden Hälften des Satzes auseinanderfallen.

**Befund 11, Kostenformel eine Runde zu kurz — behoben, und die dahinterstehende Frage
entschieden.** Maß 1 misst die Entscheidung **der Runde t**: Das Bündel wird in Runde `t`
gesetzt, Runde `t` wird gerechnet, Kosten `R + 1 − t`. Die Drittel meinen damit die Runden,
die sie nennen. Neu: `t` läuft bis `R` statt bis `R − 1`, weil auch die letzte Runde über
das Mandat entscheidet. Je Startwert 9.000 statt der alten Formel, plus 24 Trägerpartie.

**Befund 12, BACI-Konkordanz fehlt — behoben.** HS92-Kapitel 01–24 → Sektor 1, 25–97 →
Sektor 2, als Tabelle im Manifest. Der Fehler dieser Grobzuordnung ist benannt (Rohholz,
Häute, Spinnstoffe, verarbeitete Nahrungsmittel) und folgenlos für den Rückvergleich, weil
Sollreihe und Modell aus derselben Aggregation entstehen. Damit sind `H`, der Handelsblock
und die Startmatrix berechenbar.
