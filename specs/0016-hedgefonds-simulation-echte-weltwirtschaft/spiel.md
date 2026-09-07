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

Fünf, jede wächst mit dem Erfolg, jede als Mechanismus und nicht als Absicht.

**1. Aufsicht.** Je Land ein Zähler, der jede Runde um einen Betrag steigt, der aus
globaler Sichtbarkeit mal lokalem Fußabdruck (Einfluss mal Positionsanteil am Sektor)
folgt — **nicht aus dem Vermögen allein**, sonst wäre er nur eine Vermögenssteuer. Drei
Schwellen: Bei der ersten bewegt sich das Instrument „Finanzmarktregulierung" gegen den
Fonds, unabhängig von dessen Lobbybudget und mit Vorrang davor. Bei der zweiten wird die
Beteiligung zwangsverkauft, mit Abschlag. Bei der dritten gilt ein Marktverbot in diesem
Land für mehrere Runden. Wächst mit dem Erfolg, weil Einfluss und Anteil genau das sind,
was das Mandat verlangt.

**2. Politische Gegenreaktion über das Realeinkommen.** Jede durchgesetzte Lobbyaktion
verschiebt Preise und damit Realeinkommen. Sinkt das Realeinkommen, sinkt die Zustimmung;
unter einer Schwelle wechselt die Regierung, die neue setzt **alle** Instrumente in
Richtung ihres historischen Mittels zurück und verdoppelt die Lobbykosten des Fonds für
mehrere Runden. Wächst mit dem Erfolg, weil erfolgreiches Lobbying genau die Verschiebung
erzeugt, die die Zustimmung senkt. Das ist die Wirkungskette der Idee, hier als Kreis
geschlossen statt als Pfeil.

**3. Marktenge.** Der Fonds lebt von Anlegergeld, und Anleger vergleichen seine Rendite
mit einer Marktrendite. Diese Marktrendite ist die **wertgewichtete Rendite aller im
Modell handelbaren Körbe und Anleihen zu Modellmarktwerten** — gewichtet nach dem Markt,
**nicht nach dem Bestand des Fonds**. Sie hat keinen eigenen Datenanker; ihr Startwert ist
der Wert des Startkorbs zu Startpreisen, ihre Fortschreibung ist Modell (`technik.md`
T33).

Die Kraft dieser Gegenkraft liegt **im Preisstoß, nicht in der Definition des
Vergleichsmaßstabs**: Je größer der Fondsanteil an einem Markt, desto stärker bewegt jeder
Ein- und Ausstieg den Preis gegen ihn, desto teurer wird jede Umschichtung. Bleibt die
Überrendite drei Runden unter null, zieht ein fester Anteil der Anleger ab, was Verkäufe
in einen Markt erzwingt, den der Fonds selbst bewegt.

**Und der Ausweg gehört dazu, sonst wäre es keine Gegenkraft, sondern ein Todesurteil auf
Größe:** Der Fonds schlägt einen breiten Markt durch **Konzentration und Ursache** —
Beteiligung und Lobbying heben den Wert *seiner* Körbe stärker als den Marktdurchschnitt.
Wer nur breit mitläuft, verliert gegen die eigene Kostenschwelle; wer die Fundamentaldaten
seiner Position verschiebt, gewinnt auch groß. Genau das ist die Verbindung zwischen den
beiden Hälften des Mandats.

**4. Nachahmer.** Für jede Position, die über mehrere Runden Überrendite bringt, steigt
ein Nachahmerzähler auf diesem Land×Sektor. Nachahmerkapital tritt als Gegenposition auf,
hebt den Einstiegspreis und senkt die künftige Rendite derselben Position. Damit ist jede
funktionierende Strategie **selbstverbrauchend**. Das ist nicht Balance, das ist die Regel,
die Maß 3 erzwingt: Was im ersten Drittel optimal war, ist im letzten abgegrast.

**5. Gegenlobby.** Einfluss ist relativ zur Summe allen Lobbydrucks auf ein Instrument.
Wer etwas durchsetzt, schädigt einen anderen Sektor — und dessen Gegenbudget wächst um
`gegenlobby_satz` Lobbypunkte je 10.000 Tausend USD erlittenen Schadens. Je stärker man in
eine Richtung verschiebt, desto teurer wird der nächste Schritt in dieselbe Richtung. Die
Rückkopplung, die im Genre nach
oben läuft, läuft hier gegen sich selbst. **Welche Zahl dieser Schaden ist, steht im
nächsten Abschnitt.** Bis zum 2026-09-02 stand hier nur das Adjektiv, und ein Gegenbudget,
das „proportional zu" etwas wächst, ohne dass die Größe benannt wäre, ist keine Gegenkraft,
sondern eine Absicht — genau die Sorte Satz, gegen die der Kopf dieses Abschnitts sich
richtet.

### Der Schaden in Gegenkraft 5, als Rechenvorschrift

`technik.md` T50 hat die **Einheit** des Schadens festgelegt — volkswirtschaftlich, Tausend
USD, Skalenklasse 2, Übergang in Lobbypunkte über
`lobbypunkte_aus_schaden(tsd) = mal_geteilt(tsd, gegenlobby_satz, 10.000)` — und die **Höhe**
ausdrücklich hierher zurückgegeben, mit der richtigen Begründung: Füllte der Architekt die
Lücke, misst Maß 2 seine Wahl. Sie ist hier gefüllt.

#### Die eine Regel

> **Der Schaden eines Instruments ist die Verschiebung des Preises, den es setzt, mal der
> Menge, auf die dieser Preis wirkt — beides an der Rundengrenze gemessen.**

Vier Instrumente, vier Preise, vier Mengen, eine Rechenform. **„Der Preis, den es setzt" ist
beim Zoll der Keil und nicht der Sektorpreis** — der Sektorpreis entsteht aus Weltpreis,
Keil und Preisträgheit, und nur der Keil hat das Instrument als Ursache. Seit dem 2026-09-03
misst die Zollzeile deshalb ihn; die Begründung steht zwei Abschnitte weiter unten.

Für jedes der vier Länder `l` und jedes seiner vier Instrumente `i`:

```
schaden(l, i) = mal_geteilt( menge(l, i), verschiebung(l, i), 10.000 )      [Klasse 2]
```

Die Bausteine, alle aus dem Zustand und dem Jahrgang, keiner eine neue Adresse:

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

`bip` und `schuld` sind die Nummern 9 und 10 aus `technik.md` T48, unverändert übernommen.
`handelsvolumen(l, s)` ist die sektorweise Fassung der Nummer 11; ihre Summe über die beiden
handelbaren Sektoren ist die alte Größe. Keiner dieser Namen ist eine Zustandsadresse — es
sind Funktionen des Zustands, dieselbe Bauart wie `korbwert` im Abschnitt *Was ein Korb wert
ist*. `durchgriff(l, s)` ist keine Zustandsgröße, sondern eine der vierzehn
**Jahrgangskonstanten** (`technik.md` T23 Punkt 5), über die Partie fest.

**`keilhub` und `preishub_zoll` sind seit dem 2026-09-03 neu und ersetzen `preishub`.** Die
Vorfassung las die volle Verschiebung des Sektorpreises; warum das die falsche Größe war und
warum diese die richtige ist, steht unter *Warum die Zollzeile nur den Keil misst*.

Damit die vier Zeilen:

| Instrument | `verschiebung(l, i)` | Klasse | `menge(l, i)` | `schaden(l, i)` |
|---|---|---:|---|---|
| `zoll` | `preishub_zoll(l, s)`, je handelbarem Sektor einzeln | 5 | `handelsvolumen(l, s)` | `Σ` über s ∈ {1, 2}: `mal_geteilt(handelsvolumen(l,s), preishub_zoll(l,s), 10.000)` |
| `leitzins` | `hub(l, leitzins)` | 3 | `schuld(l)` | `mal_geteilt(schuld(l), hub(l,leitzins), 10.000)` |
| `haushalt` | `hub(l, haushalt)` | 3 | `bip(l)` | `mal_geteilt(bip(l), hub(l,haushalt), 10.000)` |
| `regulierung` | `hub(l, regulierung) · regulierung_last` | 10 × 3 | `bip(l)` | `mal_geteilt(bip(l), hub(l,regulierung) · regulierung_last, 10.000)` |

Der dritte Sektor trägt in der Zollzeile null, weil er weder eine Handelszeile noch einen
Weltpreis hat und nach T28 `durchgriff = 0` trägt — drei Gründe, von denen jeder einzeln
genügt; ob man über zwei oder über drei Sektoren summiert, ändert die Zahl nicht.
`welt.preis.<s>` gibt es ohnehin nur für s ∈ {1, 2}.

#### Warum die Zollzeile nur den Keil misst

**Die Entscheidung, in einem Satz:** Von der Verschiebung des Sektorpreises zählt als
Schaden **allein der Teil, den der Zollschritt verursacht hat** — der Rest ist Konjunktur
und gehört nicht in eine Gegenkraft.

Bis zum 2026-09-03 stand hier die volle Verschiebung, und das war falsch. Der Nachweis ist
zwei Zeilen lang und stammt aus der Preisbildungsregel oben:

```
preis_neu − preis_alt = durchgriff/10.000 · ( weltpreis_mit_zoll_neu − preis_alt )
```

Der Klammerausdruck zerfällt in zwei Summanden, und nur der erste hat einen Verursacher:

```
weltpreis_mit_zoll_neu − preis_alt
    = welt.preis_neu · (zoll_neu − zoll_alt)/10.000        ← der Zollkeilanteil
    + ( welt.preis_neu · (10.000 + zoll_alt)/10.000 − preis_alt )   ← der Sockel
```

Der zweite Summand ist genau die Verschiebung, die eingetreten wäre, **wenn der Zollstand
sich nicht bewegt hätte**. Er ist nach der Preisträgheitsregel oben („der Inlandspreis
folgt dem Weltpreis mit einem Jahr Verzögerung") von Bauart wegen von null verschieden,
in jeder Runde, ohne jede Aktion.

**Die alte Größe war der Betrag der Summe, die neue ist der Betrag des ersten Summanden**,
beide mal `durchgriff/10.000`. Der Unterschied ist also nicht eine Dämpfung, sondern eine
Streichung: Was wegfällt, ist der Summand ohne Verursacher, und was bleibt, bleibt
unverändert.

**Was der Sockel wirklich ist: die Inflation, mal dem Handelsvolumen.** `handelsvolumen`
steht nach T5 Klasse 2 zu konstanten Preisen, `preishub` war ein Nominalindex — ihr Produkt
ist die nominale Aufwertung des Handelsstroms und damit im Kern die jährliche
Sektorpreissteigerung des Landes. Die Zollzeile hat vor dieser Änderung die **Inflation
gemessen** und sie als Lobbyschaden gebucht.

**Drei Gründe, und der erste allein genügt.**

1. **Er trifft Maß 2 an seiner empfindlichsten Stelle, und keine Kalibrierung holt ihn
   zurück.** Die Familie Lobby ist die einzige der drei, deren Gegenkraft ausschließlich
   Gegenkraft 5 ist. Ein Sockel, der ohne Aktion entsteht, ist für jedes Profil derselbe
   und für kein Profil vermeidbar — er zieht die Grundlinie unter genau einer der drei
   Klassen weg. `gegenlobby_satz` hilft nicht, weil er Sockel und Aktionsantwort gemeinsam
   skaliert; wer den Sockel halbiert, halbiert die Antwort mit. Und Einfluss ist der
   **Anteil** des Fonds am gesamten Lobbydruck, also verschiebt ein exogen gespeister
   Gegendruck diesen Anteil dauerhaft. Die Abnahme von Maß 2 lautet
   `max(Ek) ≤ 1,25 × min(Ek)` über die drei Klassen; ein Handicap, das genau eine Klasse
   trägt und über die Partie mit dem Preisniveau wächst, ist die naheliegendste Art, sie zu
   reißen — und sie fiele nicht an einer Zahl, sondern an der Bauart.
2. **Er steht gegen die eigene Begründung dieses Abschnitts.** Der Wertschöpfungsverlust ist
   unten mit dem Satz verworfen: *„Er ist Konjunktur, nicht Reaktion … ohne dass eine einzige
   Lobbyaktion stattgefunden hätte."* Dieselbe Eigenschaft hatte die Zollzeile, und dort war
   sie nicht die Ausnahme, sondern die Regel. Zwei Größen mit derselben Eigenschaft
   verschieden zu behandeln ist kein Entwurf, sondern ein Versehen.
3. **Er macht den Rückschlag unerklärbar, und das ist die erste der drei Klagen.** Schritt 1
   zeigt die Kette der Vorrunde. Unter der alten Regel las sie sich: *Gegendruck auf dem
   deutschen Zollinstrument +6.570, Ursache: Schaden 32.850.000 Tsd USD, Ursache: der
   Sektorpreis hat sich bewegt* — und dahinter steht keine Aktion, sondern der Weltmarkt.
   Genau das meint „the consequences of choices often feel intangible": nicht, dass zu wenig
   passiert, sondern dass das, was passiert, nicht am Spieler hängt. Der Entwurf verspricht
   im Titel, dass jede Zahl sagt, warum sie sich bewegt. Der Sockel konnte das nicht.

**Und der Nebeneffekt ist der zweite Beleg dafür, dass die alte Größe die falsche war.**
`technik.md` T8 basiert bei Hyperinflation die drei Sektorpreise eines Landes neu (Division
durch 1.000), `welt.preis.<s>` dagegen nicht — es hängt an keinem Gebiet. Eine Differenz
`preis_neu − preis_alt` über eine solche Neubasierung hinweg ist nicht die Preisverschiebung,
sondern der Basiswechsel; sie hätte den Gegendruck des betroffenen Landes still auf
`druck_max` gelegt. Dass eine Differenz das braucht, weiß der Architekt bereits: T42 rechnet
für den Rückvergleich genau diese Korrektur heraus. Die Schadensvorschrift hatte sie nicht.
Im Prüfjahrgang 2001 tritt der Fall nie ein — in den Spieljahrgängen vor 2001, die dieser
Entwurf ausdrücklich erhält, schon. **Die neue Fassung differenziert nur den Zollstand
(Klasse 3, wird nie neu basiert) und liest den Weltpreis als Niveau; T8 kann sie nicht
treffen.**

#### Die beiden anderen Wege, und warum sie es nicht sind

**Weg 2 — `hub(l, zoll)` lesen wie die drei anderen Zeilen.** Er ist billiger und löst den
Sockel ebenfalls. Er scheitert an zwei Stellen.

Erstens macht er die Zeile blind für die Sektorwirkung. `schaden(l, zoll)` wäre dann
`mal_geteilt(handelsvolumen(l), hub(l,zoll), 10.000)` und hinge nur noch am Land. Der
Entwurf begründet aber im Abschnitt *Was für die Preisbildung gelten muss* die Ordnung, die
`durchgriff` herstellt: *„ein Zoll trifft Chinas Industrie über ihren hohen `durchgriff` hart und die
US-Industrie, in der Bau und Versorger dominieren, schwach"*. Unter Weg 2 trifft er beide je
Einheit Handelsvolumen gleich hart. Das ist derselbe Selbstwiderspruch wie unter 2 oben, nur
in die andere Richtung.

Zweitens verwechselt er eine Rate mit einem Preis. Ein Zollsatz ist kein Preis, sondern ein
Keil; was der Käufer zahlt, ist der Sektorpreis. Der Leitzins dagegen **ist** der Preis des
Geldes, der Haushaltssaldo **ist** der Anteil am Ausstoß, und die Regulierungsstufe wird mit
ihrem Lastsatz zu einem solchen Anteil. Diese Unterscheidung stand schon in der Fassung vom
2026-09-02 und gilt unverändert — sie ist der Grund, warum die Zollzeile den Zollstand
**umrechnet** statt ihn einzusetzen. Genau das leistet `keilhub`: Er übersetzt eine Rate in
Basispunkten am Weltpreisniveau in eine Verschiebung in Indexpunkten, und erst `durchgriff`
lässt davon durch, was im Inland ankommt.

**Weg 3 — den Sockel behalten und hinschreiben.** Er fällt an Grund 1: Ein hingeschriebener
Konstruktionsfehler bleibt einer. Der Sockel ist nichts, was die Kalibrierung noch drehen
könnte, und er wäre auch für Maß 3 schädlich, nicht nur folgenlos: Er wächst mit dem
nominalen Preisniveau über die Partie, verteuert die Familie Lobby also im letzten
Partiedrittel systematisch — eine Verschiebung des Optimums, die **auch bei abgeschaltetem
Fonds** entstünde. Maß 3 hätte seine Schwelle dann mit einer Drift der Welt erreicht statt
mit einer Eigenschaft des Spiels. Ein Maß, das sich so bedienen lässt, misst nicht mehr.

#### Was die Entscheidung kostet, und was sie nicht kostet

**Sie kostet nicht:** eine neue Zustandsadresse (`welt.preis.1` und `welt.preis.2` sind die
Nummern 239 und 240 in `daten/adressen.md`), eine neue Reihe, einen vierten Skalenübergang,
einen neunten Kanal oder eine zweite Markträumung. Und sie kostet **nichts an Signal**: Der
Aktionsanteil des Schadens ist derselbe wie vorher, nur der Sockel fällt weg. Die Zerlegung
oben ist algebraisch exakt und nicht ungefähr; verschieden sind allein die Rundungswege —
die alte Zeile rundete einmal in den gespeicherten Sektorpreis und einmal in den Schaden,
die neue zweimal zwischen Weltpreis und Schaden. Ein Unterschied um wenige Indexpunkte, kein
Unterschied in der Größenordnung.

**Sie kostet:** den Schaden, den ein *fremder* Zoll im Inland anrichtet. Ein deutscher
Industriesektor, den ein amerikanischer Zollschritt über den Weltpreis trifft, erzeugt in
Deutschland keinen Gegendruck mehr, weil `hub(DE, zoll)` null ist. Das steht unter *Was
bewusst fehlt*, und der Kanal ist nicht durchtrennt, sondern umgeleitet: Der fremde
Zollschritt hebt den deutschen Sektorpreis, senkt das Realeinkommen, senkt die Zustimmung
und löst über Gegenkraft 2 einen Regierungswechsel aus, der **alle vier** deutschen
Instrumente zurückstellt und damit über `hub` Schaden erzeugt. Das ist schwellengesteuert
statt stetig, und der Unterschied gehört benannt — aber es ist derselbe Weg, den der Entwurf
für Preiswirkungen ohnehin vorsieht.

**Eine Bedingung, die daraus folgt und die der Jahrgangsbau prüfen muss.** `preishub_zoll`
entsteht aus zwei Rundungen. Ist der kleinstmögliche Zollschritt zu klein, rundet die Zeile
für ein Land×Sektor-Paar auf null, und die Gegenkraft ist dort **stumm, ohne es zu sagen**.
Was gelten muss, als Form und ohne Zahl:

```
mal_geteilt( mal_geteilt(welt.preis_start(s), schrittweite[zoll], 10.000),
             durchgriff(l, s), 10.000 )  ≥  1     für jedes Land×Sektor des Jahrgangs
```

Der Wert von `schrittweite[zoll]`, der das erfüllt, ist Kalibrierung und steht nicht hier;
dass die Bedingung geprüft wird, ist Entwurf und steht hier.

#### Zwei Zustände, zwei Zahlen

Dieselbe Probe wie in Paket 0021, jetzt an der Zeile, die dort keine hatte. Beide Zustände
unterscheiden sich in **genau einer** Größe, dem Zollstand.

| Größe | Zustand A (ein Zollschritt) | Zustand B (keine Aktion) |
|---|---:|---:|
| `handelsvolumen(DE,1)` / `(DE,2)` (Tsd USD) | 40.000.000 / 100.000.000 | dieselben |
| `durchgriff(DE,1)` / `(DE,2)` (Jahrgang) | 7.288 / 5.464 | dieselben |
| `lies_neu(welt.preis.1)` / `(welt.preis.2)` | 11.000 / 10.400 | dieselben |
| `…instrument.zoll.stand`, `lies_alt` → `lies_neu` | 380 → 430 bp | 380 → 380 bp |
| `lies_alt(…sektor.1.preis)` / `(…sektor.2.preis)` — nur die Vorfassung liest ihn | 10.000 / 10.000 | dieselben |
| `hub(DE, zoll)` | 50 | **0** |
| `keilhub(DE,1)` / `(DE,2)` | 55 / 52 | 0 / 0 |
| `preishub_zoll(DE,1)` / `(DE,2)` | 40 / 28 | 0 / 0 |
| Beitrag Sektor 1 / Sektor 2 | 160.000 / 280.000 | 0 / 0 |
| **`schaden(DE, zoll)`** | **440.000** | **0** |

Nachgerechnet mit `mal_geteilt` und der Rundungsregel aus T6 (auf halbe Beträge von null
weg): `11.000 · 50 / 10.000 = 55` glatt; `7.288 · 55 / 10.000 = 40,084 → 40`;
`5.464 · 52 / 10.000 = 28,4128 → 28`; `40.000.000 · 40 / 10.000 = 160.000`;
`100.000.000 · 28 / 10.000 = 280.000`.

**Die Zeile `lies_alt(…sektor.<s>.preis)` geht in keine Zahl der Spalten darunter ein.** Sie
steht nur für den Vergleich am Ende dieses Abschnitts: Die geltende Zollzeile liest
`land.<l>.sektor.<s>.preis` nicht mehr — das ist die Entscheidung —, die Vorfassung las ihn
als ihre einzige Zustandseingabe. Ihr Wert ist der Startwert der Preisträgheitsregel oben,
also Runde 1.

**Zustand B ist die Abnahme, und er ist ohne jede Kenntnis der Keilform nachrechenbar.**
Bewegt sich der Zollstand nicht, ist `hub` null, damit `keilhub` null, damit
`preishub_zoll` null und damit `schaden(l, zoll)` **exakt null** — für jeden Weltpreis, jede
Preisträgheit und jedes Handelsvolumen. Zum Vergleich dieselbe Zeile in der **Vorfassung**,
auf denselben Zustand B angewandt und allein aus den Größen der Tabelle darüber gerechnet,
mit `mal_geteilt` und der Rundungsregel aus T6:

```
wmz(DE,1)      = 11.000 · (10.000 + 380) / 10.000              = 11.418
preishub(DE,1) = |11.418 − 10.000| · 7.288 / 10.000 = 1.033,4384 →  1.033
Beitrag 1      = 40.000.000 · 1.033 / 10.000                   =  4.132.000
wmz(DE,2)      = 10.400 · (10.000 + 380) / 10.000 = 10.795,2   → 10.795
preishub(DE,2) = |10.795 − 10.000| · 5.464 / 10.000 =   434,388 →    434
Beitrag 2      = 100.000.000 · 434 / 10.000                    =  4.340.000
                                                     Summe     =  8.472.000
```

**8.472.000 statt null**, und das ist mehr als das **Neunzehnfache** dessen, was der
absichtlich gesetzte Zollschritt in Zustand A erzeugt (440.000). Genau diese Größe fällt mit
der Entscheidung weg, und sie fiel ohne Aktion an, in jeder Runde und für jedes Profil
gleich. Die einzige Rundung, die man hier anders legen könnte, ist der Zwischenwert
`10.795,2`; sie entscheidet nichts — ungerundet weitergerechnet ergibt
`795,2 · 5.464 / 10.000 = 434,49728 → 434`, dieselbe Zahl.

**Damit gilt für alle vier Zeilen derselbe Satz**, und das ist die eigentliche Wirkung
dieser Entscheidung: *Der Schaden eines Instruments ist genau dann von null verschieden,
wenn das Instrument sich in dieser Runde bewegt hat.* Vorher galt er für drei von vier.

Dass ein Instrument sich auch ohne Aktion des Spielers bewegen kann, bleibt möglich — ein
Regierungswechsel stellt alle vier zurück. Das ist keine Ausnahme von dem Satz, sondern
dieselbe Kette eine Stufe später, und sie trifft alle vier Zeilen gleich; siehe *Wächst mit
dem Erfolg?*.

#### Wer geschädigt wird, und an welche der 16 Adressen es fließt

| Instrument | Wer trägt den Schaden | warum diese Menge |
|---|---|---|
| `zoll` | die beiden handelbaren Sektoren des Landes und ihre Gegenüber im Handel, ein- wie ausfuhrseitig | der Keil wirkt auf die Waren, die die Grenze überqueren — deshalb der Handelsstrom in beide Richtungen, und deshalb nur die Verschiebung, die der Keil selbst erzeugt |
| `leitzins` | der Staat als Schuldner und über seinen Haushalt alle drei Sektoren | der Zins wird auf den Schuldenstand gezahlt, nicht auf den Ausstoß |
| `haushalt` | die Empfänger der Staatsleistung, also alle drei Sektoren nach Wertschöpfungsanteil | der Saldo steht in Basispunkten **des BIP**; die Menge ist deshalb das BIP |
| `regulierung` | das Finanzgewerbe in Sektor 3 und über die Kapitalkosten die übrigen | der Zustand führt keinen Finanzsektor; das BIP ist die gröbste ehrliche Menge |

**Die Zuordnung in einem Satz:** Der Schaden wird **je Land aus den Größen dieses Landes**
gerechnet und legt sich auf die Instrumente **desselben** Landes —
`land.<l>.instrument.<i>.gegendruck`, vier Länder mal vier Instrumente, die sechzehn
Adressen. Damit ist jede einzelne herleitbar: Wer `land.BR.instrument.leitzins.gegendruck`
aufschlägt, rechnet `mal_geteilt(schuld(BR), hub(BR, leitzins), 10.000)` und danach
`lobbypunkte_aus_schaden` darauf.

**Die Regel dahinter bleibt: Eine Gegenlobby bildet sich dort, wo sie handeln kann**, beim
eigenen Gesetzgeber und nicht beim fremden. Was sie dort erreicht, ist Widerstand gegen
Bewegung und nicht Vergeltung — siehe *Was bewusst fehlt*.

**Seit dem 2026-09-03 gilt diese Regel für den Zoll allerdings nur noch für den eigenen
Schritt.** Bis dahin trug die Zollzeile auch den Schaden, den ein *fremder* Zoll über den
Weltpreis im Inland anrichtete; mit dem Sockel fällt er weg, denn er hängt am Weltpreis und
nicht am eigenen Keil. Ihn zurückzuholen hieße, den allgemeinen Gleichgewichtsanteil eines
Zollschritts zu isolieren, und das braucht eine **zweite Markträumung** je Runde — die
teuerste Rechnung des Modells noch einmal, für einen Zustand, den es nicht gibt. Er steht
deshalb unter *Was bewusst fehlt*, mit dem Weg, über den er trotzdem ankommt.

#### Wie das Gegenbudget wächst und wieder vergeht

In Schritt 5, für alle sechzehn Adressen, genau einmal je Runde:

```
gegendruck_neu(l, i) = min( druck_max,
                            teile_gerundet( lies_alt(land.<l>.instrument.<i>.gegendruck), 2 )
                            + lobbypunkte_aus_schaden( schaden(l, i) ) )
```

**Die Halbierung ist eine Regel und keine Kalibrierzahl**, und das ist eine Entscheidung
gegen einen naheliegenden Parameter. Ein Zerfallssatz neben `gegenlobby_satz` wäre für den
Beharrungswert exakt redundant: Bei gleichbleibendem Schaden `D` läuft der Gegendruck gegen
`2 · lobbypunkte_aus_schaden(D)`, und ein freier Satz verschöbe nur, welche der beiden
Zahlen diesen Wert trägt. Unterscheiden würden sich die beiden allein im Einschwingen —
eine Kalibrierdimension, die nur den Übergang formt, kostet den Nachtlauf über tausend
Parametersätzen eine ganze Achse und gewinnt kein Maß. Die Aussage der Halbierung ist
inhaltlich und prüfbar: *Ein Gegner, der eine Runde lang nicht neu geschädigt wird, verliert
die Hälfte seines Budgets.*

**Ein Gegendruck ohne Zerfall wäre kein Zerfall, sondern ein Endzustand.** Er liefe in jedem
Land, das der Fonds anfasst, gegen `druck_max` und bliebe dort; die Strategiefamilie Lobby
könnte im letzten Partiedrittel nichts mehr bewegen, und Maß 2 fiele nicht an einer
Kalibrierung, sondern an der Bauart. Umgekehrt wäre ein reiner Zufluss ohne Vortrag zu
mild: Wer abwechselnd lobbyiert und etwas anderes tut, träfe jedes zweite Mal auf einen
Gegendruck von null. Die Halbierung ist die kleinste Fassung, die beides vermeidet.

#### Warum diese Lesart und nicht die beiden anderen

`technik.md` Abschnitt 12 nennt drei: **Preisverschiebung mal Menge**,
**Wertschöpfungsverlust**, **Bewertungsverlust**. Gewählt ist die erste, und die beiden
anderen scheitern nicht am Geschmack.

**Der Wertschöpfungsverlust** — `wertschoepfung_alt − wertschoepfung_neu` — ist die
einfachere Formel und die falsche Größe, aus drei Gründen, deren erster genügt:

1. **Er ist gegenüber dem Zoll blind.** Klasse 2 steht nach T5 in *Tausend USD zu konstanten
   Preisen des Basisjahrs*. Die Wertschöpfung ist damit eine **reale** Größe; ein Zoll
   verschiebt Preise, nicht reale Mengen — jedenfalls nicht in derselben Runde, denn der
   reale Weg läuft über Investition und Kapitalstock und ist Kanal 1. Der Zoll ist das
   einzige Instrument, das Kanal 3 überhaupt nennt, und das einzige mit Datenanker im
   Handelsblock. Eine Schadensgröße, die ihn nicht sieht, misst die falsche Kette.
2. **Er ist Konjunktur, nicht Reaktion.** In einem Wachstumsjahr ist er für alle zwölf
   Land×Sektor-Paare null, im Einbruchsjahr 2008 oder 2020 für alle zwölf gleichzeitig groß
   — ohne dass eine einzige Lobbyaktion stattgefunden hätte. Gegenkraft 5 wäre dann keine
   Kraft, die *mit dem Erfolg wächst*, sondern ein Konjunkturrauschen mit Lobbywirkung, und
   die Auflage aus dem Kopf dieses Abschnitts wäre verfehlt.
3. **Er lässt sich keinem Instrument zuordnen.** Eine Differenz, vier Instrumente: Jede
   Aufteilung auf die sechzehn Adressen wäre erfunden.

**Und der Satz, der auf Maß 2 zeigt:** Die Familie Lobby ist die einzige der drei, deren
Gegenkraft ausschließlich Gegenkraft 5 ist — Position wird von Preisstoß und Nachahmern
gebremst, Beteiligung von Aufsicht und Illiquidität. Eine Gegenkraft, die nicht auf die
Aktion des Spielers antwortet, ist für diese Familie keine, und die Familie ohne Preis
dominiert. Maß 2 verlangt `max(Ek) ≤ 1,25 × min(Ek)` über die drei Klassen; das ist
derselbe Defekt, den die Rezension als „trying to implement the tiniest socialist policy
will always result in bankruptcy" von der anderen Seite beschreibt, und er fällt hier auf
die andere Richtung.

**Der Bewertungsverlust** scheitert zweimal, und der erste Grund ist der schwerere:

1. **Er ist eine Fondsgröße und würde die Gegenkraft an den Misserfolg koppeln.** Verliert
   der Fonds, wächst die Gegenlobby; gewinnt er, verschwindet sie. Das ist die Umkehrung
   dessen, was eine Gegenkraft dieses Entwurfs leisten muss, und würde Kanal 8 nicht
   dämpfen, sondern verstärken.
2. **Er kostet einen vierten Skalenübergang.** Er steht in Klasse 1 (US-Cent), `cent_in_tsd`
   gibt es nach T50 ausdrücklich nicht, und eine Umkehrfunktion nachzurüsten ist ein ADR
   gegen T50 und kein Satz in `spiel.md`.

Liest man „Bewertungsverlust" stattdessen als Änderung des **Sektorkorbs** — `korbwert(l,s)`,
Klasse 2, also skalenrechtlich zulässig —, dann ist er beinahe die gewählte Regel, mit
`kapitalstock` statt `handelsvolumen` als Menge und einem zusätzlichen Glied für die
Kapitalstockänderung. Genau dieses Glied ist der Einwand: Es gehört zu Kanal 1 und würde in
Kanal 3 ein zweites Mal verbucht. Der Handelsstrom ist die Menge, die der Zollkeil berührt;
der Kapitalstock ist es nicht.

#### Wo die Regel läuft, und warum Kanal 3 zyklenfrei bleibt

Gerechnet wird in **Schritt 5**, dem Ort, den T50 als einzigen Aufrufort von
`lobbypunkte_aus_schaden` festlegt — sechzehn Aufrufe je Runde, alle hier. Gelesen wird:

| woher | Adressen | Zahl | für welche Zeile |
|---|---|---:|---|
| Schritt 3 | `lies_neu(land.<l>.instrument.<i>.stand)` | 16 | alle vier |
| Schritt 4 | `lies_neu(welt.preis.<s>)`, s ∈ {1, 2} | 2 | `zoll` |
| Schritt 4 | `lies_neu(handel.<a>.<b>.<s>)`, der ganze Handelsblock | 40 | `zoll` |
| Schritt 4 | `lies_neu(land.<l>.sektor.<s>.wertschoepfung)`, für `bip` | 12 | `leitzins`, `haushalt`, `regulierung` |
| Schritt 4 | `lies_neu(land.<l>.staatsschuld)`, für `schuld` | 4 | `leitzins` |
| Vorrunde | `lies_alt(land.<l>.instrument.<i>.stand)` | 16 | alle vier |
| Vorrunde | `lies_alt(land.<l>.instrument.<i>.gegendruck)` | 16 | alle vier |

`16 + 2 + 40 + 12 + 4 + 16 + 16 =` **106 Lesezugriffe**, 16 Schreibzugriffe, **keine neue
Adresse**. Gezählt sind unterschiedliche Adressen, nicht Zugriffsvorgänge — der
Handelsblock steht deshalb mit 40 und nicht mit 64, weil ein Strom zwischen zwei spielbaren
Ländern in zwei `handelsvolumen` eingeht. Jede gelesene Größe steht in `daten/adressen.md`,
`welt.preis.1` und `welt.preis.2` als Nummern 239 und 240; `bip`, `schuld` und
`handelsvolumen` sind Funktionen daraus und keine Felder, `durchgriff` ist eine
Jahrgangskonstante. Die Zahl 310 bleibt, und der Abzählschritt aus T45 geht unverändert auf.

**Die Zahl ist zweimal falsch gewesen, und die Korrektur gehört zur Entscheidung.** Die
Fassung vom 2026-09-02 nannte 120 und zählte den Zollstand doppelt mit 16, obwohl die
Zollzeile ihn damals gar nicht las — der Prüfbefund 2 hat das gefunden und 112 gerechnet.
Nach dieser Entscheidung liest der Zoll seinen Stand wieder, dafür fallen beide
Sektorpreiszeilen (`lies_neu` und `lies_alt`, je 8) ersatzlos weg und die zwei Weltpreise
kommen hinzu: `112 + 4 + 4 − 8 − 8 + 2 = 106`. Beide Zahlen der Vorfassungen sind damit
abgelöst, und die Nachziehtabelle am Ende nennt dieselbe 106.

**Die Rundengrenze ist die Lösung, nicht ein zweiter Satz Adressen.** Ein Schaden, der den
Zustand vor dem Instrumentenschritt mit dem danach vergleicht, bräuchte Schattenadressen;
der Vergleich `lies_neu` gegen `lies_alt` braucht keine, weil der Schreiber nach T39 beide
Stände ohnehin führt.

**Kanal 3, abgegangen:** Instrument (Schritt 3, `stand`) → Handel (Schritt 4, `handel`) →
Weltpreis (Schritt 4, Markträumung) → Schaden (Schritt 5, hier) →
Gegenlobbybudget (Schritt 5, `gegendruck`) → Instrument (Schritt 3 der **Folgerunde**).
Genau eine Rundengrenze wird überquert, und sie wird nicht versprochen, sondern erzwungen:
Schritt 3 muss `lies_alt(gegendruck)` lesen, weil die Adresse in dieser Runde noch nicht
geschrieben ist und `lies_neu` darauf nach T39 ein harter Fehler wäre. Die Dämpfung
„Gegendruck wirkt erst in der Folgerunde" ist damit eine Eigenschaft, die jeder Lauf
nachweist.

**`welt.preis.<s>` wird gelesen, aber nicht differenziert, und der Unterschied ist der
ganze Punkt.** Die Vorfassung hat den Weltpreis mit dem Argument ausgeschlossen, er sei für
alle Gebiete derselbe und könne nicht unterscheiden, wen es getroffen hat. Das Argument
gilt weiterhin — und es trifft die neue Zeile nicht, weil dort keine Weltpreis*differenz*
steht. Unterschieden wird durch `durchgriff(l, s)`, `handelsvolumen(l, s)` und
`hub(l, zoll)`, alle drei land- oder landessektorspezifisch; der Weltpreis liefert allein
das **Niveau**, an dem eine Rate in Basispunkten zu einer Verschiebung in Indexpunkten wird.
Ein Niveau kann niemanden auszeichnen und soll es auch nicht.

**Und es ist kein neunter Kanal.** Der Zollstand erreicht den Schaden jetzt auf zwei Wegen
statt einem: über die Menge (Instrument → Handel → `handelsvolumen`) wie bisher und über die
Verschiebung (Instrument → `hub` → Schaden) neu. Beide sind Glieder von Kanal 3, der zweite
ist der erste ohne seinen Umweg. Die Dämpfung ist unverändert dieselbe und wird unverändert
erzwungen: `gegendruck` wird nur in Schritt 5 geschrieben, `lies_neu` darauf in Schritt 3
ist nach T39 ein harter Fehler, also überquert der Weg genau eine Rundengrenze. Innerhalb
der Runde bleibt die Ordnung 3 → 4 → 5 zyklenfrei.

#### Die Skalenprobe

Klasse 5 (Preisindex) und Klasse 3 (Basispunkte) sind beide **Zehntausendstel**, und Klasse
2 steht zu konstanten Preisen des Basisjahrs. Für eine reale Menge `Q` und einen Preisindex
`P` ist der Nominalwert `Q · P / 10.000`; verschiebt sich der Preis um `ΔP`, verschiebt sich
der Wert um `Q · ΔP / 10.000`. Das ist die Formel, Zeichen für Zeichen. Für die Zinszeile
dieselbe Rechnung mit einer Rate statt eines Index: Schuldenstand mal Ratenänderung in
Basispunkten durch 10.000 ist der zusätzliche Zinsdienst eines Jahres, in Tausend USD.
**Aus Klasse 2 mal Zehntausendstel geteilt durch 10.000 kommt Klasse 2**, und dieses
Ergebnis geht unverändert in `lobbypunkte_aus_schaden`. Ein vierter Skalenübergang entsteht
an keiner Stelle.

**Die Zollzeile hat seit dem 2026-09-03 zwei Zwischenschritte statt einem, und beide halten
die Klasse.** `keilhub` ist Klasse 5 mal Klasse 3 durch 10.000, also wieder Klasse 5 — die
Verschiebung des zollbelasteten Weltpreises in Indexpunkten. `preishub_zoll` ist Klasse 5
mal Klasse 4 (`durchgriff`, Zehntausendstel) durch 10.000, also erneut Klasse 5. Erst der
letzte Schritt verlässt die Indexwelt, und er ist derselbe wie in den drei anderen Zeilen:
Klasse 2 mal Zehntausendstel durch 10.000 ist Klasse 2. **Kein vierter Skalenübergang, und
Klasse 1 wird an keiner Stelle berührt** — die Einordnung der Zollzeile in der
Instrumententabelle bleibt Klasse 5, wie in der Vorfassung.

Zum Überlauf: Der größte Faktor ist `bip(US)`, nach T5 in der Größenordnung `2,1 · 10^10`
Tausend USD; mal einer Verschiebung in Zehntausendsteln bleibt das Zwischenergebnis
weit unter der `i64`-Grenze, und `mal_geteilt` rechnet nach T6 ohnehin über `i128`. Die
Zollzeile bleibt darunter: `welt.preis` ist ein Index in der Größenordnung 10^4,
`hub(l, zoll)` durch `instrument_max[zoll]` begrenzt, `keilhub` und `preishub_zoll` damit
selbst Indexgrößen; das größte Produkt ist `handelsvolumen · preishub_zoll` und liegt bei
einem Handelsstrom in der Größenordnung 10^9 bei rund 10^13.

#### Was Gegenkraft 5 im Weltlauf tut

**Nichts, und das ist bereits entschieden.** Im Modus `weltlauf` läuft das Fondsteilsystem
nicht; aus Schritt 5 laufen nur Zustimmung und Regierungswechsel, die Gegenkräfte 1, 3, 4
und 5 werden nicht gerechnet. `gegendruck` gehört nach `technik.md` T38 zum Block
*Instrumente ohne Stand* und steht dort auf **nein**: Die Adresse wird nicht geschrieben und
behält ihren Startwert 0. Diese Rechenvorschrift wird im Weltlauf nicht ausgewertet.

Das ist kein Verlust, sondern die Bedingung des Maßes. Die Politikinstrumente sind im
Weltlauf exogen; ein Gegendruck hätte dort keinen Adressaten, und die Regulierung, deren
Schadenszeile ohnehin die einzige ohne Datenanker ist, steht fest auf dem Startwert.
Die Eingangsgrößen der Formel — Instrumentenstände, **Weltpreise**, Handelsblock,
Wertschöpfung, Staatsschuld — stehen sämtlich in der Weltlaufmaske (`technik.md` T38 führt
die Weltpreise dort mit **ja**); die Sektorpreise, die die Vorfassung noch brauchte, stehen
seit dem 2026-09-03 gar nicht mehr in der Formel. Die Rechnung *ließe* sich also mitlaufen.
Sie zu schreiben würde die Maske brechen, und eine Ausgabe daneben ist Sache des Prüfstands
und keine Entwurfsfrage.

**Die Folge, ausdrücklich benannt: Maß 4 prüft diese Vorschrift nicht.** Geprüft wird sie
von Maß 2 (bleibt die Familie Lobby innerhalb der 25 Prozent?), von Maß 3 (verschiebt sich
das beste Profil zwischen Früh- und Spätfenster?) und vom Bruchtester über die Invariante
`0 ≤ gegendruck ≤ druck_max` aus T30 Prüfung 6. Wer eine Zahl dieser Vorschrift ändert,
sieht die Wirkung im Selbstspiel und nirgends sonst.

#### Was diese Regel für Maß 2 und Maß 3 leistet

**Ein Satz, vier Mengen.** `gegenlobby_satz` gilt für alle sechzehn Adressen gleich; was
sich unterscheidet, ist die Menge, an der er ansetzt — und die steht nicht in
`parameter.toml`, sondern im Jahrgang. Die vier Länder sind oben nach struktureller
Verschiedenheit gewählt (*Warum vier Länder und nicht drei*), und genau diese
Verschiedenheit trägt jetzt einen Preis: Wer einen Exportüberschuss hat, hat eine teure
Zollzeile; wer hohe Zinsen auf hoher Schuld zahlt, eine teure Zinszeile. **Welches Instrument
billig zu bewegen ist, hängt damit am Land und nicht an einer Balancezahl.** Das ist die
Bauart, die dieser Entwurf an Democracy 4 belegt hat: Wirkung aus geladenen Tabellen, nicht
aus einprogrammierten Ausnahmen.

**Und die Zollzeile ist die einzige mit Struktur unterhalb des Landes.** `schuld` und `bip`
kennen nur das Land; die Zollzeile rechnet je Land **und Sektor**, weil `durchgriff(l, s)`
und `handelsvolumen(l, s)` es tun. Das ist der Grund, warum die Entscheidung vom 2026-09-03
auf den Keil und nicht auf den nackten Zollstand fällt: Ein Zoll, dessen Preis nicht mehr
davon abhängt, welchen Sektor er trifft, wäre für Maß 2 die vierte Zeile derselben Sorte
statt einer eigenen.

**Und die Mengen bewegen sich über die Partie.** `handelsvolumen`, `schuld` und `bip` sind
endogene Größen auf einem historischen Pfad, und die vier Brüche, die der Zuschnitt oben
ausdrücklich im Fenster behalten hat — WTO-Beitritt 2001, 2008, 2020, Erholung 2021 —, laufen
sämtlich über Handel, Staatsschuld oder Ausstoß und damit über genau diese drei Mengen.
Seit dem 2026-09-03 bewegt sich in der Zollzeile zusätzlich das **Niveau**, an dem die Rate
ansetzt: `welt.preis.<s>` ist ebenso endogen, und derselbe Zollschritt kostet auf einem
teureren Weltmarkt mehr. Das
billigste Lobbyziel der dritten Runde ist deshalb nicht zwangsläufig das billigste der
zwanzigsten — eine **dritte** Quelle der Optimumsverschiebung neben Nachahmern (Gegenkraft
4) und Preisstoß (Gegenkraft 3), und diesmal eine, die aus dem Jahrgang kommt statt aus
einer Regel. *In welche Richtung und wie stark*, misst der Jahrgangsbau und danach der
Prüfstand; dieser Entwurf behauptet es nicht.

Dazu kommt die Asymmetrie, die schon dasteht und jetzt eine Menge hinter sich hat:
Deutschland hat keinen eigenen Zinshebel — seit dem Fensterschnitt auf 2001 über die ganze
Partie statt ab Runde 3. Die Zinszeile ist dort geschlossen,
gleich was sie kostete, und der Ausweg führt über ein Instrument mit anderer Menge. Ein
geschlossener Aktionsraum, der einen anderen erzwingt — dafür ist die Asymmetrie oben
gewählt worden, und Gegenkraft 5 gibt ihr jetzt einen Preis statt nur eine Sperre.

**Wächst mit dem Erfolg?** Ja, auf zwei Wegen. Der erste ist der gewollte: Ein Instrument
bewegt sich absichtlich nur durch Aktion 3, deren Wirkung mit dem Fondsvermögen wächst
(Kanal 8) — mehr Erfolg, mehr Bewegung, mehr Schaden, mehr Gegendruck. Der zweite ist eine
Verzahnung mit Gegenkraft 2: Ein Regierungswechsel stellt **alle** Instrumente in Richtung
ihres historischen Mittels zurück, erzeugt damit in einer Runde Schaden an allen vier und
legt in der Folgerunde auf alle vier Gegendruck. Das ist nicht Zufall, sondern der Erfolg
eine Stufe später: Der Regierungswechsel ist selbst die Folge erfolgreichen Lobbyierens.
Dass daraus zwei Strafen aus einer Ursache werden, steht unter *Offene Entwurfsfragen*.

## Wie die vier Masse berechnet werden

Alle vier laufen im Selbstspiel ohne Darstellung über dieselbe Zustandsschnittstelle. Was
hier steht, ist eine Rechenvorschrift; wo eine Wahl offenbliebe, ist sie hier getroffen.
Jeder Gleichstand wird nach Aktions- beziehungsweise Profilkennung gebrochen, nie nach
Auffindereihenfolge. Der Median über eine gerade Anzahl ist der kleinere der beiden
mittleren Werte. **R = 20.**

### Die Ergebnisgröße einer Partie

Ein `i64` in Milli-Runden, **kleiner ist besser**, streng geordnet und ohne Sammelwert:

| Ausgang | Wert | Bereich bei R = 20 |
|---|---|---|
| Mandat in Runde r erfüllt | `r × 1.000` | 1.000 … 20.000 |
| R Runden überlebt, Mandat nicht erfüllt | `(R+1) × 1.000 + v + e`, siehe **Der Fehlbetrag** | 21.000 … 24.000 |
| an einer Todesart in Runde d gestorben | `30.000 + (R + 1 − d) × 1.000` | 31.000 … 50.000 |

#### Der Fehlbetrag, und wie „fehlender Einfluss" über die Länder gerechnet wird

Der Fehlbetrag ist `v + e`, beide in Promille der jeweiligen Mandatsschwelle
(`schwelle_v`, `schwelle_e` aus `parameter.toml`):

```
v = teile_gerundet(max(0, schwelle_v − fondsvermoegen) · 1.000, schwelle_v)

e = Summe über die zwei Länder mit dem höchsten Einfluss (Gleichstand nach LandId) von
    teile_gerundet(max(0, schwelle_e − einfluss[land]) · 1.000, schwelle_e)
```

**Zwei Länder, weil das Mandat zwei verlangt, und die eigenen zwei besten, weil ein Fonds
nicht für die Länder büßen soll, die er nie betreten wollte.** Von den drei naheliegenden
Lesarten — Summe, Mittel, schwächeres der beiden — ist die Summe gewählt: Sie misst die
**verbleibende Arbeit**. Ein Fonds mit einem Land am Ziel und einem bei null (0 + 1.000)
und einer mit zwei Ländern bei je der Hälfte (500 + 500) sind gleich weit vom Mandat
entfernt, und genau das sagt die Summe. Das Mittel ordnet identisch — es ist die Summe
halbiert —, das schwächere der beiden nicht: Es erklärte den halbierten Fonds für deutlich
näher dran und belohnte damit Breite, die das Mandat nicht verlangt.

**Es wird nichts gekappt, und es muss auch nichts gekappt werden.** `einfluss` liegt nach
Bauart in 0 … 100, also ist jeder der beiden Summanden in `e` per Konstruktion in
0 … 1.000 und damit `0 ≤ e ≤ 2.000`; im Band „überlebt" lebt der Fonds, also ist
`fondsvermoegen > 0` (sonst hätte Todesart 1 in derselben Runde gegriffen) und damit
`0 ≤ v ≤ 1.000`, wobei 1.000 nur die Rundung erreicht. Daraus folgt
`0 ≤ v + e ≤ 3.000` und das Band 21.000 … 24.000 — nachgerechnet und nicht verordnet. Die
Kappung der dritten Fassung war der Ersatz für eine fehlende Aggregationsregel; mit der
Regel entfällt sie, und sie war schädlich: Sie hätte jeden Fonds mit weniger als einer
Schwelle Gesamteinfluss auf denselben Wert 1.000 gelegt — also die untere Hälfte des
Ergebnisraums geglättet, und zwar genau dort, wo Maß 3 sein Argminimum sucht, wenn im
Fenster kein Profil das Mandat erreicht.

**Damit rechnen `spiel.md` und die Botzielgröße `B` aus `technik.md` T44 in diesem Zweig
dieselbe Formel** — die dort begründete Abweichung (T44 kappt nicht, weil Kappen den Bot
in der Frühphase blind machte) verschwindet, weil hier ebenfalls nicht gekappt wird. `B`
bleibt botintern, die Bandprüfung gilt weiter nur für das Partieergebnis.

**Die Bänder bleiben disjunkt, auch das obere:** „überlebt" endet bei
`(R+1) × 1.000 + 3.000`, das Todesband beginnt bei `31.000`; disjunkt sind sie genau für
`R ≤ 26`. Das ist **dieselbe Schranke**, die `technik.md` T40 schon in den Jahrgangsbau
zieht — sie bleibt unverändert gültig, ist jetzt aber scharf statt großzügig, und das
breitere Band kostet keine Runde Partielänge. Bei R = 20 sind die unerreichbaren Lücken
20.001 … 20.999 und **24.001 … 30.999**; zwischen dem Ende von „überlebt" und dem Beginn des
Todesbandes liegen 7.000 Milli-Runden Luft.

**Die Kante aus Befund 10 ist damit geschlossen:** Das Band 1.000 … 20.000 heißt genau
„Mandat erfüllt", der überlebte Misserfolg beginnt bei 21.000, und kein Wert trägt zwei
Bedeutungen. Der frühe Tod ist schlechter als der späte, und zwar um volle Runden — genau
die Auflösung, die Maß 1 im letzten Partiedrittel braucht. Eine Sammelkappe auf den
Gesamtwert gibt es **nicht**. Der Bereichstest lautet: ein Ergebnis ausserhalb
1.000 … 50.000 ist ein harter Fehler.

### Das Aktionsprofil und wie es auf Aktionen wirkt

Ein **Aktionsprofil** ist die Verteilung des Rundenbudgets über die fünf Aktionsarten in
Fünftelrasterung, also ein Vektor `(a1…a5)` mit `ai ∈ {0…5}` und `Σai = 5`. Das sind
`C(9,4) = 126` Profile. Das **Referenzprofil** ist `(1,1,1,1,1)`.

Das Profil ist ein Werkzeug des Prüfstands, keine Spielgröße — der Mensch wählt frei. Wie
es auf Aktionen wirkt, war in der zweiten Fassung nicht gesagt, und Maß 2 und Maß 3 stehen
vollständig darauf. **Das Vorratsverfahren, verbindlich:**

Jede Art `i` führt einen ganzzahligen Vorrat `vi`, zu Partiebeginn null.

1. **Am Rundenanfang:** `vi += 3 · ai` für alle fünf Arten. Die Summe wächst damit je Runde
   um 15.
2. **Für jeden der drei Steckplätze der Runde, nacheinander:** Wähle unter den Arten, die
   in dieser Runde noch mindestens eine zulässige Aktion haben, die mit dem größten `vi`;
   bei Gleichstand die kleinere Kennung. Setze eine Aktion dieser Art und rechne
   `vi −= 5`. Hat keine Art eine zulässige Aktion, bleibt der Steckplatz leer und kein
   Vorrat wird verrechnet.
3. **Welche** Aktion innerhalb der gewählten Art gesetzt wird, entscheidet der Bot: der
   Heuristikbot nach seiner festen Rangfolge, der Suchbot durch Suche.

Drei Fragen, die der Prüfer zu Recht gestellt hat, sind damit beantwortet. Der Bot füllt
**immer drei Steckplätze**, solange zulässige Aktionen da sind; die Bündelgröße gehört
nicht zum Profil. `ai = 0` **verbietet die Art nicht**, sondern schiebt sie ans Ende — ein
hartes Verbot ließe Profile mit Nullen ihre Steckplätze nicht füllen und machte Maß 2 zu
einem Vergleich zwischen drei und weniger als drei Aktionen je Runde statt zwischen
Strategien. Es wird nie gerundet und nie gezogen: **Nach `5k` Runden steht der Vorratsvektor wieder
auf `(0,0,0,0,0)`, und Art `i` hat genau `3k·ai` der `15k` Steckplätze bekommen** — für
`k = 1` also `3·ai` von fünfzehn nach **fünf** Runden, für `k = 3` `9·ai` von
fünfundvierzig nach fünfzehn. Zwischen zwei solchen Punkten ist die Abweichung beschränkt.
**Seit `R = 20` ist das Partieende selbst ein solcher Punkt** (`k = 4`): Ein Lauf, der eine
ganze Partie lang dasselbe Profil spielt, vergibt `12·ai` der 60 Steckplätze exakt nach
Profil — siehe *Die Partielänge R*.

Zur Probe das Referenzprofil: Runden 1 bis 5 vergeben die Arten
1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,5 und stehen danach wieder auf `(0,0,0,0,0)` — je
Art genau drei von fünfzehn Steckplätzen, gleichverteilt und deterministisch.

**Für den Suchbot** legt das Profil die Artenzusammensetzung des Rundenbündels fest; die
60 Kandidatenbündel entstehen aus der nach T32 geordneten Zulässigkeitsliste,
**eingeschränkt auf genau diese Zusammensetzung**, und gezogen nach T35. Der Suchbot sucht
also über Ziele und Stufen, nie über Arten.

### Maß 1 — Entscheidungsdichte

**Eingabe:** 50 Startwerte, je Startwert eine Trägerpartie mit dem Heuristikbot auf dem
Referenzprofil.

Für jede Runde `t = 1 … R` und jeden Startwert: Ziehe **30 Aktionsbündel**. Ein Bündel
entsteht, indem zuerst die Bündelgröße gleichverteilt aus `{0,1,2,3}` gezogen wird und
dann so viele Aktionen ohne Zurücklegen gleichverteilt aus der Liste der in dieser Runde
zulässigen Aktionen. Doppelte Bündel im Stichprobensatz werden **nicht** entfernt — sonst
hinge die Stichprobengröße vom Zustand ab. Der Zufallsstartwert folgt aus `(Jahrgang,
Parametersatz, Wurzelstartwert, t, Stichprobenindex)`.

Das Bündel **ersetzt die Bot-Aktionen der Runde t**; Runde `t` wird gerechnet, danach
spielt der Heuristikbot auf dem Referenzprofil bis Runde `R` durch. Der Vorrat aus dem
Vorratsverfahren wird für Runde `t` so fortgeschrieben, als hätte der Bot die Arten des
gezogenen Bündels gespielt (`vi += 3·ai` am Rundenanfang, `vi −= 5` je tatsächlich
gesetzter Aktion) — sonst wäre der Zustand des Zählers nach der Einspeisung undefiniert.

**Rechenweg:**

```
Ergebnis(t, s, k)      k = 1…30 Bündel, s = 1…50 Startwerte
Dichte(t, s) = Anteil der 30 Ergebnisse, die um mehr als 1.000 Milli-Runden
               vom Median dieser 30 abweichen
Dichte(t)    = Mittel der Dichte(t, s) über die 50 Startwerte
```

**Über die Startwerte wird erst am Ende gemittelt, und zwar über Dichten, nicht über
Ergebnisse.** Ein gemeinsamer Median über alle 1.500 Ergebnisse einer Runde wäre falsch:
Verschiedene Startwerte erzeugen nach `technik.md` T11 verschiedene Jahrgangsstreuungen,
und ein Median über mehrere Welten triebe den Abweichungsanteil gegen 1, ohne dass eine
einzige Entscheidung dichter geworden wäre.

**Abnahme:** Mittel der `Dichte(t)` über jedes Partiedrittel — die Drittel sind
`1…⌊R/3⌋`, `⌊R/3⌋+1…⌊2R/3⌋`, `⌊2R/3⌋+1…R`, bei R = 20 also **1-6, 7-13, 14-20** —
jeweils **≥ 0,4**, nicht nur über die ganze Partie. Ein Spiel, das nur in der Mitte lebt,
fällt hier durch. Fällt es durch, ist „the consequences of choices often feel intangible"
gerade gemessen worden.

**Kosten.** Ein Bündel in Runde `t` kostet die Runden `t … R`, also `R + 1 − t`
Weltschritte — Maß 1 misst die Entscheidung **der Runde t**, deshalb wird sie mitgerechnet.

```
je Startwert:  30 · Σ(R+1−t) für t = 1…R  =  30 · R(R+1)/2  =  30 · 210 =  6.300
               zuzüglich Trägerpartie R                                 =     20
                                                                          ------
                                                                           6.320
50 Startwerte:                                                           316.000
```

### Maß 2 — Strategievielfalt

**Eingabe:** alle 126 Profile, je 20 Startwerte, Suchbot.

Das Profilergebnis `E(p)` ist der Median der 20 Partieergebnisse. Ein Profil **gewinnt**,
wenn `E(p) ≤ R × 1.000 = 20.000` — also genau dann, wenn es im Median im Band „Mandat
erfüllt" landet.

Der **Strategiekern** eines Profils ist die Aktionsart mit dem größten Anteil unter den
drei Familien `{1 Position, 2 Beteiligung, 3 Lobby}`, bei Gleichstand die kleinere
Kennung. Hebel und Sichtbarkeit sind Verstärker, keine Strategien, und gehen in den Kern
nicht ein.

**Die sechs Profile `(0,0,0,a4,a5)` mit `a4 + a5 = 5` haben keinen Strategiekern.** Sie
enthalten keine einzige Familienaktion; ihnen über den Gleichstand die Klasse 1 zuzuweisen
hieße, eine Positionsstrategie als erfüllt zu zählen, in der keine Position vorkommt. Sie
laufen mit, ihr Ergebnis wird berichtet, und sie gehen in **keine** der beiden
Abnahmehälften ein. Klassifiziert sind damit 120 Profile, verteilt auf genau drei Klassen.

**Abnahme, beide Teile:**

1. **Jede der drei Klassen stellt mindestens einen Gewinner.**
2. Sei `Ek` das beste (kleinste) Profilergebnis der Klasse `k`. Dann muss
   `max(Ek) ≤ 1,25 × min(Ek)` gelten.

Der zweite Teil ist der wichtigere — sonst gewinnen drei, aber eines dominiert, und das
ist derselbe Defekt unter anderem Namen. Das ist die Zahl hinter „trying to implement the
tiniest socialist policy will always result in bankruptcy".

**Kosten:** eine Suchbotpartie `R × (1 + 60) = 20 × 61 = 1.220`;
`126 × 20 × 1.220` = **3.074.400 Weltschritte**.

### Maß 3 — Verschiebung des Optimums

Zwei getrennte Läufe je Profil, jeder über die **volle Partie**, damit keine Runde ohne
Vorgabe bleibt. Die Fenster sind das erste und das letzte Partiedrittel aus Maß 1:

- **Frühfenster:** Runden 1-6 mit Profil `p`, Runden 7-20 mit dem Referenzprofil.
  Ergebnis `Efrüh(p)` = Median über 20 Startwerte.
- **Spätfenster:** Runden 1-13 mit dem Referenzprofil, Runden 14-20 mit Profil `p`.
  Ergebnis `Espät(p)` = Median über 20 Startwerte.

Der Profilwechsel geschieht am Rundenanfang; der Vorrat des Vorratsverfahrens läuft über
den Wechsel hinweg weiter und wird nicht zurückgesetzt. Beide Läufe verwenden den
Suchbot, innerhalb wie außerhalb des Fensters.

`p*` = Profil mit kleinstem `Efrüh`, `q*` = Profil mit kleinstem `Espät`, Gleichstand nach
Profilkennung; alle 126 Profile sind wählbar. **Verschiebung** = `Σ|p*i − q*i| / 5`.

**Abnahmeschwelle 0,4.** Beide Vektoren summieren auf 5, die Summe der Beträge ist deshalb
stets gerade, und die Verschiebung nimmt nur die Werte `{0; 0,4; 0,8; 1,2; 1,6; 2,0}` an.
Die Schwelle 0,5 der zweiten Fassung verlangte in Wahrheit 0,8, also zwei verschobene
Fünftel; gemeint war und gefordert ist **eines**.

Erzwungen wird die Verschiebung nicht durch Balance, sondern durch Gegenkraft 4 und 3:
Nachahmer grasen jede frühe Position ab, der Preisstoß entwertet Größe. Das ist die Zahl
hinter „already the richest hedge fund in the game and nothing fun to do".

**Kosten:** `2 × 126 × 20 × 1.220` = **6.148.800 Weltschritte**.

**Summe der drei Maße:** `316.000 + 3.074.400 + 6.148.800` = **9.539.200 Weltschritte**.
Was der ganze Nachtlauf kostet, steht in `technik.md` Abschnitt 10 und nicht hier — die
zweite Fassung hat an dieser Stelle eine Zahl genannt, die Vorgaben des Prüfstands
voraussetzte, die sie selbst nicht machte.

### Maß 4 — Rückvergleich

**Der Rückvergleich ist ein Weltlauf, keine Partie.** Das ist die Antwort auf Befund 2, und
sie ist eine Entwurfsentscheidung, keine Auslegung: Ein Fonds mit Nullvermögen dividiert in
Runde 1 durch null und stirbt, wenn man ihn davor bewahrt, spätestens in Runde 3 am
Anlegerabzug. Beides ist kein Zustand, in dem sich eine Weltmaschine prüfen lässt.

Im Modus `weltlauf` gilt deshalb:

- **Das Fondsteilsystem läuft nicht.** Schritt 2 (Aktionen) und Schritt 6 (Abrechnung)
  entfallen vollständig; aus Schritt 5 laufen nur Zustimmung und Regierungswechsel. Die
  Gegenkräfte 1, 3, 4 und 5 werden nicht gerechnet, es gibt keine Rendite, keine
  Überrendite, keinen Anlegerbestand, kein Mandat und **keine Todesart**. Kein Feld des
  Fondsblocks und kein Nachahmerzähler wird geschrieben; sie behalten ihre Startwerte.
- **Die Politikinstrumente sind exogen** und folgen Runde für Runde den historischen
  Pfaden für Leitzins, Zollniveau und Haushaltssaldo. Jede Regel, die ein Instrument
  schriebe — Lobbydruck, Gegenlobby, der Instrumentenrückstellung durch einen
  Regierungswechsel —, wird nicht ausgeführt. Ein Regierungswechsel wird berechnet und
  ausgewiesen, bleibt aber ohne Wirkung; das Orakel ist an dieser Stelle blind, und das
  gehört in jeden Befund.
- **Die Schreibregel wird dadurch nicht weicher, sondern schmaler:** Auch im Weltlauf wird
  keine Adresse zweimal je Runde geschrieben. Die Menge der überhaupt geschriebenen
  Adressen ist je Modus fest und wird vom Prüfstand mit ausgewiesen.

Damit prüft Maß 4 genau, was es prüfen soll: die Übertragung Politik → Wirtschaft über die
Schritte 3 und 4. Ein Lauf mit erfundener Politik prüfte nur die halbe Maschine; ein Lauf
mit einem sterbenden Fonds prüfte gar nichts.

**Die 27 Sollreihen** sind BIP je Land (4), Sektoranteile (12, davon 8 unabhängig),
Verbraucherpreise (4), Wechselkurs gegen USD (3), Staatsschuldenquote (4); dazu der
Handelsblock über 40 Ströme als eigener Block. Jede über 21 Stützstellen ohne Füllung. Nach
der Klassifikation aus `technik.md` T37 sind die vier Staatsschuldenquoten **abgeleitet**,
die übrigen 23 **frei**.

**Der Leitzins ist seit dem 2026-09-03 keine Sollreihe.** Die Klasse `gesetzt` ist damit
leer und entfällt. Der Grund steht in *Die Partielänge R* und ist keiner der Deckung: Eine
Reihe, die im Weltlauf als Eingabe gesetzt wird, hat den Fehler null per Konstruktion — sie
kann nicht durchfallen und nichts belegen, und sie hat das Fenster trotzdem um ein Jahr
gekürzt. **Was an ihre Stelle tritt, ist schärfer und nicht weicher:** Der Leitzins bleibt
Eingabe (Reihe 9, Rolle Start + Politikpfad), und dass die Maschine ihn unverändert
wiedergibt, ist eine **Invariante**, keine Schwelle. Weicht der Modellwert an irgendeiner
Stützstelle vom gesetzten Pfad ab, ist das ein harter Fehler und kein Fehlermaß von 300
Basispunkten. Ausgewiesen wird er weiterhin.

**Die drei Fehlermaße, je Reihe:**

| Reihen | verglichen wird | Schwelle |
|---|---|---|
| BIP (4), Sektoranteile (12), Staatsschuldenquote (4), Handelsströme (40) | das **Niveau** | MAPE über die 21 Stützstellen ≤ 20 % |
| Verbraucherpreise (4), Wechselkurs (3) | die **Jahresänderungsrate** in Basispunkten | mittlerer absoluter Fehler über die 20 Übergänge ≤ 300 bp |
| alle | die **Richtung** | Anteil der 20 Übergänge mit `sgn(Δmodell) = sgn(Δsoll)` ≥ 0,6 |

Die zweite Zeile ist die Folge von `technik.md` T8: Ein prozentualer Fehler auf einem
Index, der über zwei Jahrzehnte um eine Größenordnung wandert, misst den Anfang und nicht
die Maschine — und ein prozentualer Fehler auf einer Rate nahe null explodiert. Die 300
Basispunkte, also drei Prozentpunkte mittlerer Fehler auf der Jahresrate, haben denselben
Status wie die 20 Prozent und die 0,6: eine gesetzte Latte. Erweist sie sich als
unerreichbar, ist das ein Befund über das Modell und kein Anlass, sie zu verschieben.

**Die Abnahmeregel — `3·L_R + (L_R − n) + 1` Prüfgegenstände, Toleranz `⌊L_R/2⌋`.** Heute, mit
`L_R = 4` Rückvergleichsländern und `n = 1`, sind das **16 und 2**; nach Paket 0118 mit
`L_R = 7` sind es **28 und 3** (siehe *Welche neun Länder*). **Beide stehen ab hier als Formel
und nicht als Ziffer**, aus demselben Grund, aus dem `R` als Buchstabe steht: Eine feste 2
machte das Hinzufügen eines Landes zu einer Verschärfung des Rückvergleichs, ohne dass sich
eine Regel des Modells ändert. Die zweite Fassung nannte zwei
Fehlermaße und keine Regel, wie über die Reihen zusammengefasst wird; `technik.md` T37 hat
daraus ein Gesamtmaß gelesen und die Entscheidung zurückgegeben. Hier ist sie:

1. **Abnahmerelevant sind nur die freien Reihen.** Die vier abgeleiteten Schuldenquoten
   werden berichtet und entscheiden nichts; der Leitzins ist seit dem 2026-09-03 gar keine
   Sollreihe mehr, sondern Eingabe mit Invariantenprobe. Eine Reihe, die per Konstruktion
   fehlerfrei ist, darf kein Gesamtmaß mildern.
2. **Prüfgegenstand ist nicht die Reihe, sondern die Größe.** Es sind heute sechzehn, und
   **gezählt wird je Rückvergleichsland, nicht je Land** — ein Spielland liegt nach T58
   vollständig außerhalb der Sollmaske und trägt keinen:

   | Prüfgegenstand | Formel | heute | nach 0118 | zusammengefasst aus |
   |---|---|---:|---:|---|
   | BIP je Rückvergleichsland | `L_R` | 4 | 7 | je eine Reihe |
   | Sektorstruktur je Rückvergleichsland | `L_R` | 4 | 7 | die **drei** Anteilsreihen des Landes, alle drei müssen bestehen |
   | Verbraucherpreise je Rückvergleichsland | `L_R` | 4 | 7 | je eine Reihe |
   | Wechselkurs je Rückvergleichsland ausser dem Numéraire | `L_R − n` | 3 | 6 | je eine Reihe |
   | Handelsblock | `1` | 1 | 1 | `(L_R+1)·L_R·(S−1)` Ströme — heute 40, nach 0118 112; Median des MAPE und Median der Richtungstreue; das schlechteste Fünftel wird ausgewiesen |
   | **Summe** | `3·L_R + (L_R − n) + 1` | **16** | **28** | |

   Die drei Anteilsreihen eines Landes sind durch die Normierung auf 10.000 nicht
   unabhängig; als drei Zähler geführt, würde ein einzelnes falsch modelliertes Land die
   Toleranz allein aufbrauchen. Als **ein** Zähler geführt, kostet es einen von sechzehn —
   und muss dafür in allen drei Anteilen bestehen.

   **Die Zahl 16 ist durch den Schnitt vom 2026-09-03 unverändert geblieben, und das ist
   nachgezählt, nicht angenommen.** Gestrichen sind die vier Leitzinsreihen; die Tabelle
   oben speist sich aus Reihe 1 (BIP), Reihe 2 (Sektoranteile), Reihe 8
   (Verbraucherpreise), Reihe 10 (Wechselkurs) und Reihe 14 (Handelsblock). Keiner der
   sechzehn Prüfgegenstände enthält Reihe 9, und keiner könnte sie enthalten: Sie war nach
   T37 `gesetzt`. **Die Abnahmeregel „höchstens 2 der 16" läuft damit auf derselben
   Reihenmenge weiter wie vorher, nur über 21 statt 25 Stützstellen.** Verändert hat sich
   der Nenner der *Sollreihen* (31 → 27), nicht der der *Prüfgegenstände*.

3. **Ein Prüfgegenstand besteht**, wenn er beide für ihn geltenden Schwellen einhält.
   **Die Richtungstreue wird dabei nur über die Übergänge gebildet, in denen sich die
   Sollreihe bewegt.** Ein Übergang ohne gemessene Bewegung trägt keine Richtung und wird
   weder als Treffer noch als Fehler gezählt; bewegt sich eine Sollreihe in keinem der
   zwanzig Übergänge, hat der Prüfgegenstand keine Richtungstreue und besteht allein über
   sein Niveaumaß. Das ist keine Milderung, sondern das Schließen einer Lücke: Über eine
   konstante Reihe trägt jeder Übergang die Richtung null, ein endogen gerechneter Wert
   trifft die exakte Null so gut wie nie, und der Gegenstand risse **von Bauart wegen**.
   Der Fall ist nicht hypothetisch — er ist der Grund, aus dem Saudi-Arabien Spielland
   erwartet wird (siehe *Welche neun Länder*), und flache Abschnitte gibt es auch ohne
   Kursbindung.
4. **Der Lauf ist bestanden, wenn höchstens `⌊L_R/2⌋` Prüfgegenstände reißen** — heute zwei
   von sechzehn, nach Paket 0118 drei von achtundzwanzig. Jeder gerissene wird im Befund
   einzeln benannt, mit beiden Zahlen. Einer mehr ist ein Durchfallen, auch wenn er knapp
   reißt. **Die Formel reproduziert bei `L_R = 4` genau die heutige 2** — das ist die
   Verträglichkeitsprobe —, und sie hält den Anteil danach fast fest: 2 von 16 sind 12,5
   Prozent, 3 von 28 sind 10,7, 4 von 36 sind 11,1. Sie wächst also langsamer als die Zahl
   der Gegenstände und senkt die Latte nie.

Der Median über die Handelsströme — heute 40, nach Paket 0118 112 — ist der Vorschlag des
Architekten (`technik.md`
Abschnitt 12) und wird hiermit übernommen, mit seiner Begründung: Einzelne kleine Ströme
— Brasilien–China in der Landwirtschaft — schwanken prozentual stark, ohne dass das Modell
falsch wäre; ein Mittel ginge daran kaputt, eine Je-Strom-Schwelle schneller.

**Kosten:** R = 20 Weltschritte.

**Und die Grenze des Orakels, ausdrücklich.** Ohne Sollreihe sind: **Sektorpreise**
und **Weltpreise** (Lücke 2 des Datenkurators), **Zustimmung** (Lücke 4), das Instrument
**Finanzmarktregulierung**, die **Marktrendite** und seit dem 2026-09-03 der **Leitzins**
— letzterer nicht aus Datenmangel, sondern weil er Eingabe ist und ein gesetzter Wert nichts
prüft. Dazu kommt im Weltlauf das gesamte
Fondsteilsystem, das gar nicht läuft. Alle diese Größen sind im Zustand sichtbar, keine ist
vom Rückvergleich gedeckt. Er prüft die Dynamik der Maschine über den historischen
Zeitraum und sagt nichts über den Ast, den der Spieler betritt.

**Eine gefüllte Stützstelle, die in jeden Befund gehört.** Der US-Leitzinspfad endet 2020;
seine einundzwanzigste Stützstelle ist der fortgeschriebene Wert von 2020 und trägt
`gefuellt = 1`. Sie ist keine Sollstelle, also fällt sie nicht unter T24s Verbot — aber sie
ist eine **Eingabe**, und der letzte Übergang der US-Prüfgegenstände läuft auf ihr. Der
Prüfstand weist sie aus. Das ist der einzige gefüllte Wert im ganzen Prüfjahrgang.

### Die drei Klagen und was sie beantwortet

| Klage aus den Rezensionen | Entwurfsentscheidung |
|---|---|
| „the consequences of choices often feel intangible" | **Höchstens drei Aktionen je Runde** — Knappheit zwingt jede Aktion, groß genug zum Wirken zu sein. Dazu die Kette als eigener Zustandsteil (Schritt 1 und 6) und Maß 1 als Abnahmeschwelle je Partiedrittel statt als Wunsch. **Seit dem 2026-09-03 dazu die Gegenprobe:** In Gegenkraft 5 ist der Schaden jedes Instruments genau dann von null verschieden, wenn das Instrument sich bewegt hat. Eine Kette, die eine Strafe zeigt und dahinter keine Aktion, ist dieselbe Klage von hinten — deshalb ist der Konjunktursockel der Zollzeile gefallen. |
| „trying to implement the tiniest socialist policy will always result in bankruptcy" | **Der Fonds kann long und short sein.** Damit ist keine politische Richtung dominant: Wer auf Regulierung setzt, weil er short steht, gewinnt genauso wie wer sie verhindert. Dazu die zweiteilige Siegbedingung (Kapital UND Einfluss) und Maß 2, das jede der drei Familien einzeln gewinnen sehen will. |
| „no dramatic setbacks or successes", „everything is incredibly surface level" | **Drei Todesarten mit sichtbaren Schwellen** (Zwangsliquidation, Marktverbot, Anlegerabzug), die Ergebnisskala, die den frühen Tod schlechter bewertet als den späten, und Maß 3, erzwungen durch Nachahmer und Preisstoß. Der Rückschlag ist dramatisch, aber nie willkürlich — siehe „Keine verdeckte Größe". |

## Was bewusst fehlt

- **Mehr als vier Länder und drei Sektoren.** Die Idee nannte zwölf und sechs. Zwölf Länder
  vervierfachen die Rückkopplungswege ohne ein Maß zu verbessern; sechs Sektoren gibt es
  unter freier Lizenz nicht, und aus drei aufgeteilte wären ein Konstrukt ohne Sollreihe.
  **Am 2026-09-05 eingeordnet, nicht gestrichen:** Der Satz galt und gilt für
  *Politikländer* — der Betreiber hat neun entschieden (Paket 0118), und das ist die Zahl,
  gegen die er ab jetzt zu lesen ist. Für das *investierbare Universum* ist er seit
  Paket 0119 gegenstandslos: Es wächst über die zweite Schicht, die keine
  Rückkopplungswege hinzufügt, weil sie keine Handelszeile hat.
  **Am 2026-09-06 ausgefüllt:** Die neun sind USA, China, Deutschland, Brasilien, Japan,
  Indien, Chile, Singapur und Saudi-Arabien. Der Satz über die vervierfachten
  Rückkopplungswege bleibt trotzdem richtig und ist jetzt bezifferbar — die Handelsmatrix
  wächst von 40 auf 180 Ströme, viereinhalbfach, während alles andere sich gut verdoppelt.
  **Er ist damit der Grund, warum es neun sind und nicht zwölf**, und kein Einwand mehr
  gegen die neun.
- **Ein zehntes Politikland, und die Grenze liegt an der Matrix und nicht am Geschmack.**
  `G·(G−1)·2` über `G = L+1` ergibt bei zehn Ländern 220 Ströme statt 180, bei zwölf 312.
  Wer mehr investierbare Welt will, bekommt sie über die zweite Schicht zu fünf Feldern je
  handelbarem Steckplatz statt zu rund zwanzig — das ist die ganze Begründung der Schicht,
  und sie gilt gegen jedes zehnte Land genauso wie gegen das dreißigste.
- **Ein zweites Land des Euroraums.** Griechenland war der stärkste Kandidat für den fünften
  Platz: Sein Haushaltssaldo wird 2010 — Runde 10, genau zwischen den beiden Fenstern von
  Maß 3 — unter dem Programm exogen, und das wäre die Instrumentensperre, die seit dem
  Fensterschnitt auf 2001 fehlt und die dieser Entwurf ausdrücklich vermisst. **Es scheitert
  an einer Adresse:** Der Wechselkurs des Euro gegen den Dollar ist für Deutschland und
  Griechenland **dieselbe** Reihe, das Modell führt aber `wechselkurs[l]` je Land und
  rechnete zwei Euro-Kurse, die auseinanderlaufen dürfen. Die beiden Länder trügen zwei
  Prüfgegenstände auf einer einzigen Wirklichkeit, und ein Fehler im Euro-Kurs risse beide
  zugleich. Der Ausweg wäre eine gemeinsame Kursadresse je Währungsraum — und die ändert die
  Adressarithmetik, die Sollreihenzahl und die Prüfgegenstandsformel zugleich. Zu teuer für
  ein fünftes Land, und ein eigenes Paket, falls der Euroraum je zweimal vorkommen soll.
- **Eine Instrumentensperre, die innerhalb des Fensters zuschnappt.** Sie fehlt seit dem
  2026-09-03 und sie fehlt weiter. Der Kandidat außerhalb des Euroraums war die Türkei
  (IWF-Programm 2002–2008, also Runden 2 bis 8); er ist verworfen, weil das Fenster genau
  über dem Frühfenster von Maß 3 liegt und die Sperre damit nicht *zwischen* den beiden
  Fenstern läge, sondern *in* einem. Was bliebe, wäre eine Sperre auf einer mittleren Runde
  — und das ist das erzählte Ereignis, das zwei Zeilen weiter unten aus gutem Grund auf
  dieser Liste steht. **Maß 3 muss die Verschiebung weiterhin ohne einen solchen Übergang
  erzeugen**; die dritte Quelle dafür ist seit Paket 0119 die zweite Schicht.
- **Ein Wechselkursregime als Modellgröße.** Saudi-Arabiens Kurs steht über alle 21
  Stützstellen auf 3,75, und das Modell hat keine Regel, die einen Kurs hält. Eine
  Kursbindung wäre billig zu schreiben — der `wechselkurs[l]` eines gebundenen Landes wird
  nicht geschrieben, dieselbe Bauart wie die stillgelegten Adressen eines Spiellands — und
  sie ist trotzdem nicht hier entschieden: Sie machte aus einem Spielland ein
  Rückvergleichsland und verschöbe damit `L_R`, die Prüfgegenstände und die Sollmaske. Das
  ist eine Entscheidung über die Grundlage des Rückvergleichs und gehört nach T60 dem
  Betreiber, nicht diesem Abschnitt. **Was sie kaufen würde, steht dabei:** Ein gebundener
  Kurs ist die einzige Art, wie das Modell den Unterschied zwischen einer lauten und einer
  stummen Währung ausdrücken könnte, und Saudi-Arabien ist der einzige Ort, an dem er
  gemessen danebenliegt.
- **Alle 195 Länder der Welt.** Das ist kein „später", sondern ein anderes Produkt, und die
  Zahlen stehen unter *Was die Schicht kostet*: **87.788 Zustandsfelder, 76.440 Handelsströme,
  3.705 lizenzgeprüfte Datenreihen** und 780 Prüfgegenstände statt sechzehn. Verworfen am
  2026-09-05.
- **Ein Börsenplatz mit Handelszeile, Politikinstrumenten oder Beteiligung.** Jedes einzelne
  davon macht ihn zu einem billigen Land: Die Handelszeile bringt die `G²`-Matrix zurück
  (3.120 Ströme statt 180), die Instrumente machen ihn beeinflussbar und heben damit die
  Trennung auf, um derentwillen die Schicht existiert, und die Beteiligung wäre der Weg zu
  billigem Lobbying an einem Ort, an dem es kein Lobbying gibt.
- **Ein Aufsichtszähler auf der zweiten Schicht.** Der Fonds kann dort unbeobachtet groß
  werden. Das ist ausdrücklich gewollt und teuer bezahlt: Die Schicht liefert null Einfluss
  und kann die zweite Mandatshälfte nie erfüllen. Ein halber Zähler („Sichtbarkeit ja,
  Einfluss nein") wäre eine Regel, die nichts entscheidet, weil der Fußabdruck den Einfluss
  als Faktor trägt und damit ohnehin null bliebe.
- **Ein Regulierungskanal auf `zins[b]`.** Naheliegend wäre, dass die Finanzmarktregulierung
  des Ankers Kapital vertreibt und den Platzzins hebt — ein dritter Hebel in die zweite
  Schicht hinein. Er kostete einen weiteren Kalibrierschlüssel, und zwei Hebel dorthin gibt
  es schon (Leitzins über `zielzins` und `weltzins`, Zoll über `leitkurs`). Fällt Maß 3 an zu
  wenig Zugriff auf die Schicht, ist dieser Kanal der erste Nachschlag.
- **Eine gemessene Marktkapitalisierung je Börsenplatz.** `tiefe[b]` wird aus dem
  Kapitalstock des Ankers und den Sektorgewichten gebildet, mal `platzanteil`. Eine echte
  Kapitalisierungsreihe wäre die richtigere Größe, hinge aber an einer weiteren Quelle mit
  eigener Lizenzfrage — und die Ordnung, auf die es ankommt (großer Anker, tiefer Platz),
  liefert die abgeleitete Größe auch.
- **Ein eigener Trägheitsparameter für die zweite Schicht.** `index`, `zins` und
  `wechselkurs` eines Platzes gehen je Runde genau **halb** auf ihr Ziel zu. Drei
  kalibrierbare Gewichte gäben der Suche drei Achsen, deren Wirkung `kippung` und
  `platzanteil` ohnehin erzeugen — und kein Maß liest die Halbierung.
- **Das verarbeitende Gewerbe als eigener Sektor.** Es wäre die interessantere Gliederung
  und ist als WDI-Reihe sogar vorhanden — aber nur als Teilmenge der Industrie. Ein
  vierter Sektor „übrige Industrie" hätte keine eigene Quellreihe und müsste als Differenz
  gebildet werden. Vier Sektoren mit einem ungedeckten, drei mit lauter gedeckten: die
  Wahl ist die zweite.
- **Startjahrgänge vor 2001**, und die Grenze liegt jetzt vier Jahre später als in der
  fünften Fassung. 2000 und früher bleiben als **Spieljahrgänge** möglich und sind der
  naheliegende Inhalt des Erweiterungsmodells aus der Idee. Sie tragen keine
  US-Staatsschuldenquote und keinen US-Haushaltspfad aus Daten (IWF WEO beginnt für die
  USA 2001), vor 1997 zusätzlich keine US-Sektorstruktur und vor 1995 keinen Handelsblock;
  ein Spieljahrgang vor 2001 übernimmt die fehlenden US-Startwerte aus dem ersten belegten
  Jahr und kennzeichnet sie als gefüllt. Damit sind sie Spiel-, aber keine Prüfjahrgänge.
  Das gehört ins Kaufangebot geschrieben, nicht in eine Fußnote.
- **Ein Ersatz für den Euro-Übergang, seit dem 2026-09-03 und ausdrücklich.** Mit dem
  Fenster 2001–2021 fällt die einzige Instrumentensperre weg, die während einer Partie
  zuschnappte (Deutschland verliert 1999 seinen Zinshebel). Der naheliegende Ausweg wäre,
  irgendeine andere Sperre auf eine mittlere Runde zu legen — und genau das tue ich nicht:
  Das wäre ein erzähltes Ereignis, und die stehen zwei Zeilen weiter unten aus gutem Grund
  auf dieser Liste. Ereignisse entstehen hier aus Schwellen oder aus Daten, nicht aus dem
  Wunsch nach einem Wendepunkt. Maß 3 muss die Verschiebung ohne diesen Übergang erzeugen;
  tut es das nicht, ist das ein Befund über die beiden verbliebenen Quellen (Nachahmer,
  Preisstoß) und kein Anlass, eine Sperre zu erfinden.
- **Der Wiederaufbau des Fensters 1997–2000 aus einer dritten Quelle.** Die Tabelle in
  *Die Partielänge R* rechnet ihn durch: Für Brasilien gibt es die Jahre nicht, für die USA
  gäbe es sie nur um den Preis einer anderen Abgrenzung als für China und Deutschland. Vier
  Stützstellen sind billiger als eine Sollreihe, die je Land etwas anderes misst.
- **Eine eigene Füllregel für Politikpfade.** Der Leitzinspfad darf gefüllt werden, die
  Sollreihen des Prüfjahrgangs nicht — das steht in T24 und genügt. Eine dritte Schwelle
  („ein Pfad darf zu höchstens x Prozent gefüllt sein") wäre eine Zahl, die niemand messen
  kann, bevor die Quelle feststeht. Was stattdessen gilt: Jede gefüllte Stützstelle eines
  Pfades wird im Befund einzeln benannt. Bei 21 Stützstellen ist eine Liste billiger als
  ein Anteil.
- **Ein feinerer Warenschlüssel als HS92-Kapitel.** Die Zuordnung 01–24 / 25–97 ist grob
  und ihr Fehler oben benannt. Eine echte HS-nach-ISIC-Konkordanz wäre genauer und kostete
  eine weitere Quelle mit eigener Lizenzfrage — für zwei Modellsektoren steht das nicht
  dafür.
- **Quartals- und Tagestakt.** Damit fallen Panik, Runs und Margin Calls im Wortsinn weg —
  ein spürbarer Verlust an Genre-Erwartung, und ich nenne ihn als solchen. Der Grund ist
  hart: BIP, Sektorstruktur, Produktivität und Zoll liegen **jährlich** vor. Quartalsrunden
  ließen drei von vier Runden ungeprüft. Ersatz für das Innerjahresrisiko: Der Hebel wird
  nicht gegen den Jahresendstand geprüft, sondern gegen einen Innerjahresausschlag, der
  deterministisch aus der Jahresbewegung und der historischen Schwankungsbreite des Landes
  folgt. Hebel bleibt gefährlich, ohne dass eine zweite Zeitschicht entsteht.
- **Ein Weltaktienindex als Vergleichsmaßstab.** Es gibt keinen unter freier Lizenz. Die
  Marktrendite ist deshalb eine Modellgröße ohne Anker — benannt, nicht versteckt.
- **Ein eigener Kurs neben dem Sektorpreis.** Ein Korb wird mit dem Preis seines Sektors
  bewertet, nicht mit einem Aktienkurs, der davon abweichen dürfte. Damit gibt es keine
  Bewertungsblase und keine Stimmung — der Wert eines Bestandes folgt seiner
  Ursachenkette und sonst nichts. Das ist ein Verlust an Genre-Erwartung und der Preis
  dafür, dass jede Wertänderung erklärbar bleibt.
- **Veränderliche Bonität.** Der `aufschlag` zwischen Leitzins und Anleiherendite ist eine
  Konstante. Ein Land, dessen Schuldenquote davonläuft, zahlt im Modell keinen höheren
  Aufschlag; Staatspleiten und Risikoprämien gibt es nicht. Der Aufschlag hätte einen
  Anker (Renditereihen), aber keine Sollreihe im Zustand, und er kostete einen neunten
  Rückkopplungskanal (Haushalt → Aufschlag → Kurs → Haushalt).
- **Die Geldmenge als Tiefe des Währungsmarktes.** Sie läge bei IWF IFS vor und wäre die
  bessere Größe als das Handelsvolumen. Sie kostet eine Zustandsadresse je Land und einen
  exogenen Pfad, und sie verbessert kein Maß. Das Handelsvolumen ordnet die vier Länder
  gleich und steht schon im Zustand.
- **Einzelne Unternehmen.** Nur Land×Sektor-Körbe. Firmendaten unter freier Lizenz gibt es
  nicht, und was der Datenkurator nicht beschaffen kann, kommt nicht vor.
- **Derivate, Optionen, strukturierte Produkte.** Long, short, Hebel. Mehr Instrumente
  vergrößern den Aktionsraum, ohne ein Profil hinzuzufügen, das Maß 2 unterscheiden könnte.
- **Namentlich benannte Personen.** Regierungen sind Rollen („Regierung Brasilien"),
  Notenbanken sind Institutionen. Auflage aus `agentenbau.md`, und sie berührt gerade
  dieses Spiel.
- **Wahlmechanik.** Keine Parteien, keine Koalitionen, keine Wahlkreise. Eine Größe
  Zustimmung, ein Regierungswechsel bei Unterschreitung.
- **Erzählte Ereignisse und Ereigniskarten.** Sie wären ein Inhaltslaufband (G4) und
  regressiv nicht prüfbar. Ereignisse entstehen hier aus Schwellen.
- **Krieg, Klima, Migration, Demografie als Spielgröße, Mehrspieler.**
- **Ein Zollsatz je Sektor.** Es gibt ihn nicht unter tragfähiger Lizenz. Die
  Sektorwirkung entsteht aus `durchgriff` und den Importanteilen.
- **Ein zeitlich veränderlicher `durchgriff`.** Er wäre richtiger und kostete zehn weitere
  exogene Pfade. Konstant genügt, weil die Mengen ohnehin endogen sind.
- **Eine Gegenlobby, die selbst etwas durchsetzen will.** `gegendruck` ist ein Skalar, der
  in Schritt 3 gegen `druck` verrechnet wird; er kann Bewegung **hemmen, nicht verlangen**.
  Was Gegenkraft 5 abbildet, ist Mobilisierung und nicht Vergeltung — ein geschädigter
  Sektor macht jede Bewegung seines Zollinstruments teurer, auch die, die ihm helfen würde.
  Vergeltungszölle kosteten eine Richtung je Instrument und damit sechzehn weitere Adressen.
- **Eine Aufteilung des Schadens auf den geschädigten Sektor.** Wer ihn trägt, steht als
  Regel da; gerechnet wird er je Land und Instrument, nicht je Sektor. Die Aufteilung
  bräuchte eine Vorleistungsmatrix — eine weitere Quelle mit eigener Lizenzfrage —, und sie
  änderte an keiner der sechzehn Zahlen in Schritt 3 etwas.
- **Ein Gedächtnis der Gegenlobby über eine Runde hinaus.** Die Halbierung ist die ganze
  Geschichte. Ein verteilter Nachlauf über mehrere Runden kostete sechzehn weitere Adressen
  und formte nur das Einschwingen.
- **Schaden der Restwelt.** Sie hat keine Politikinstrumente und damit keine Adresse, an der
  sich eine Gegenlobby bilden könnte. Ihre Preisverschiebungen bleiben unverbucht; die
  Restwelt schließt den Kreislauf, sie handelt nicht.
- **Ein Schaden, der Anstieg und Rückgang unterscheidet.** Die Verschiebung geht als Betrag
  ein: Jede Bewegung schädigt jemanden. Die Richtung trägt bereits die Verrechnung gegen
  `druck` in Schritt 3, und ein Vorzeichen im Schaden zöge sie ein zweites Mal ein.
- **Der Konjunkturanteil der Preisverschiebung, seit dem 2026-09-03 und ausdrücklich.** Ein
  Sektorpreis, der dem Weltpreis nachläuft, verschiebt sich in jeder Runde; dass jemand
  darunter leidet, ist wahr und trotzdem kein Lobbyschaden. Wer die Preisträgheit als Schaden
  bucht, bucht die Inflation als Gegenkraft — die Begründung steht unter *Warum die Zollzeile
  nur den Keil misst*. Was dadurch **nicht** fehlt: die Wirkung des Zolls auf den Sektor. Sie
  steckt in `durchgriff(l, s)`, und das ist der einzige Grund, warum die Zeile nicht einfach
  `hub(l, zoll)` liest.
- **Der allgemeine Gleichgewichtsanteil eines Zollschritts.** Ein amerikanischer Zoll bewegt
  über die Markträumung den Weltpreis und damit die Sektorpreise aller Länder. Dieser Teil
  seiner Wirkung geht in keine Schadenszeile ein, denn er ließe sich nur gegen einen
  Zustand messen, den es nicht gibt: dieselbe Runde mit dem alten Zollstand, also eine
  **zweite Markträumung** mit noch einmal 40 Halbierungsschritten je Sektor. Der Preis wäre
  die teuerste Rechnung des Modells verdoppelt, der Ertrag eine Zahl, die kein Maß prüft.
- **Der Schaden, den ein fremder Zoll im Inland anrichtet, als eigene Zeile.** Er ist die
  Folge des Vorigen und fällt mit ihm. Er verschwindet nicht aus dem Spiel, sondern wechselt
  die Gegenkraft: Der fremde Zollschritt hebt den inländischen Sektorpreis, senkt das
  Realeinkommen und die Zustimmung und kann über Gegenkraft 2 einen Regierungswechsel
  auslösen, der alle vier Instrumente zurückstellt und damit Schaden erzeugt. Der Unterschied
  gehört benannt und ist keine Kleinigkeit: Der alte Weg war stetig, der neue ist
  schwellengesteuert und um mindestens eine Runde langsamer.
- **Ein eigener Gegenlobbysatz je Instrument.** Ein `gegenlobby_satz`, vier Mengen. Vier
  Sätze gäben der Kalibrierung drei Achsen, deren Wirkung die Mengen ohnehin erzeugen —
  und zwar aus dem Jahrgang statt aus einer Zahl.
- **Grafik über Tabelle, Verlaufsgraph und Kettenansicht hinaus.** Democracy 4 verkauft
  sich mit einer 2D-Knotenoberfläche und besteht in seiner Simulation vollständig aus
  geladenen Tabellen statt einprogrammierter Effekte
  (positech.co.uk/democracy4/modding.html, abgerufen 2026-08-31). Das ist die Bauart, an
  der ich mich orientiere.

## Offene Entwurfsfragen

- **Die schwerste: Ist der aggregierte Zollsatz der Weltbank verwendbar?** Er ist erkennbar
  aus WITS abgeleitet und fällt damit möglicherweise unter die Drittanbieter-Ausnahme der
  WDI-Lizenz. Ist er gesperrt, verliert der Rückvergleich das wichtigste seiner drei
  verankerten Instrumente. Das ändert den Entwurf nicht — `technik.md` T26 hat den Fall
  architektonisch aufgefangen —, aber es halbiert seinen Beleg. Zu prüfen, bevor gebaut
  wird.
- **Die übrigen WDI-Reihen unter der Drittanbieter-Ausnahme.** Zu prüfen sind nach der
  Kennzeichnung des Architekten Nr. 7 (sektorale Beschäftigung, ILO-Schätzung), Nr. 8
  (Verbraucherpreise, IWF-gestützt), Nr. 10 (Wechselkurs) und Nr. 13 (Zoll). Je Reihe ist
  das Feld „Source" im Indikatorendatensatz zu lesen. Vier Abrufe, und die Frage ist
  geschlossen — Aufgabe des Datenbauers, weil sie am Jahrgang hängt und nicht am Entwurf.
- **Das Fenster ist entschieden und diese Frage geschlossen.** Sie hieß „Bleibt das Fenster
  bei 1997–2021?" und lautete seit dem 2026-09-02 „19, 20 oder 24?". **Nein, und 20.** Das
  Fenster ist **2001–2021**, `R = 20`, 21 Stützstellen; entschieden am 2026-09-03 in Paket
  `0054-partielaenge-r-entscheiden`, begründet im Abschnitt *Die Partielänge R*, nachgezogen
  in allen vier Maßvorschriften und in der Nachziehtabelle für den Architekten benannt. Der
  Verdachtsfall aus `technik.md` T24 — die chinesische und die brasilianische Leitzinsreihe
  der neunziger Jahre — ist damit gegenstandslos: Die neunziger Jahre liegen außerhalb des
  Fensters, und der Leitzins ist keine Sollreihe mehr.

  **Was aus der Entscheidung als neue offene Frage hervorgeht, steht in den nächsten beiden
  Punkten.** Sie ersetzen die geschlossene, sie sind nicht dasselbe in anderer Form: Die eine
  betrifft die Beschaffung einer Eingabe, die andere ihre Einheitlichkeit. Keine von beiden
  hängt mehr an R.
- **Woher der Leitzinspfad für Deutschland und China kommt.** `IMF.STA/MFS_IR` führt für
  beide Länder keinen einzigen Wert (Deckungsbefund, Abrufe 2026-09-01), und das gilt für
  jedes Fenster. Der Pfad wird trotzdem gebraucht: als `leitzins_start[l]`, als exogener
  Pfad im Weltlauf und als Wertebereich des Instruments im Spielmodus. **Das ist eine
  Beschaffungsfrage und ein Folgepaket des Datenbauers, keine Entwurfsfrage** — und sie ist
  seit dem Wegfall der Sollrolle deutlich kleiner: Eine Eingabe darf nach T24 gefüllt und
  gekennzeichnet werden, eine Sollreihe des Prüfjahrgangs nicht. Zwei Fährten stehen schon in
  den eigenen Unterlagen und sind hier nur benannt, nicht geprüft: **Eurostat** ist nach
  `daten.md` Nr. 7 für EU- und EFTA-Länder gewerblich nutzbar und deckt damit die deutsche
  beziehungsweise die Euroraum-Seite; **`FR.INR.LEND`** (WDI) trägt China nach dem
  Deckungsbefund 1997–2021 lückenlos, ist aber ein Bankzins und kein Leitzins.
- **Ob ein einheitlicher Zinsbegriff über die vier Länder erreichbar ist.** Der
  Deckungsbefund weist nach, dass `DISR_RT_PT_A_PT` je Land etwas anderes misst — für die
  USA den Diskontsatz des Fed-Diskontfensters, für Brasilien den Rediskontsatz, der nicht die
  Selic ist. Als *Sollreihe* wäre das ein Fehler, den die Streichung erledigt. Als *Eingabe*
  bleibt er eine offene Frage, und zwar eine, die auf Prüfgegenstände durchschlägt: Ein
  brasilianischer Pfad auf dem falschen Niveau treibt Anleihekurs und Zinskanal und damit
  BIP, Sektorstruktur, Verbraucherpreise und Wechselkurs Brasiliens — vier der sechzehn.
  **Die Entwurfsvorgabe an das Folgepaket lautet deshalb: ein Begriff für alle vier Länder,
  und wenn keiner erreichbar ist, dann der je Land plausibelste, ausdrücklich benannt und im
  Befund des Rückvergleichs mitgeführt.** Zu entscheiden hat das der Datenbauer an den
  Quellen, nicht ich am Schreibtisch.
- **Die Zahlenwerte der Schwellen** — Mandatsschwelle, Aufsichtsschwellen, Startkapital,
  Nachahmergeschwindigkeit, Stufenweite einer Position, Anlegerabzugsanteil. Sie gehören
  nicht in diesen Entwurf, weil sie nicht entschieden, sondern **kalibriert** werden: Das
  Selbstspiel sucht die Werte, bei denen Maß 1 bis 3 ihre Schwellen erreichen. Genau dafür
  gibt es die Maße. Festgelegt ist die Form, nicht die Zahl; die Werte stehen nach T27 in
  `parameter.toml`.
- **Ob ein Parametersatz existiert, in dem der Fonds groß genug und nicht zu groß ist.**
  Neu mit dieser Fassung, und die Frage ist eine Messung, keine Entscheidung: Startkapital
  und `stufenweite` müssen zusammen eine Stufe bezahlbar machen **und** erreichbare
  Stufenzahlen bis an die Aufsichtsschwellen heranreichen lassen. Beides zugleich ist nicht
  garantiert — die Märkte des Modells sind ganze Sektorkapitalstöcke, und ein Fonds, der
  sie bewegt, ist groß. Verfehlt der Selbstspieler die erste Bedingung, gewinnt Klasse 1
  nie; verfehlt er die zweite, greift keine Gegenkraft und Maß 3 fällt auf null. **Beides
  ist am Prüfstand sichtbar**, und beides ist ein Befund über den Parametersatz, nicht über
  den Entwurf — es sei denn, es gibt keinen zulässigen. Dann ist es der Entwurf.
- **Wie fein der Aktionsraum sein darf.** Zu grob, und Maß 1 findet keine Unterschiede; zu
  fein, und die Stichprobe von 30 Bündeln deckt zu wenig ab. Empirisch am Prototyp zu
  bestimmen — messbar daran, ob `Dichte(t)` bei K=30 und K=60 dieselbe Antwort gibt.
- **Der Lastsatz der Finanzmarktregulierung, `regulierung_last`.** Neu mit der
  Schadensvorschrift, Klasse 3, Basispunkte des BIP je Regulierungsstufe. Er ist die einzige
  Zahl in Gegenkraft 5 ohne datenverankerte Entsprechung — und zwar genau dort, wo die
  Instrumententabelle oben ohnehin „reines Modellkonstrukt, ohne Sollreihe" sagt. Die drei
  übrigen Zeilen kommen ohne neue Zahl aus. Sein Wert wird kalibriert, nicht entworfen; im
  Weltlauf ist er ohne Wirkung, weil das Instrument dort feststeht.
- **Ob `druck` derselben Rundengrenzenregel folgt wie `gegendruck`.** Zum anliegenden
  Lobbydruck sagt dieser Entwurf nur „Aktion 3, Verrechnung in Schritt 3"; ob er über die
  Runde stehen bleibt, zerfällt oder verbraucht wird, steht nirgends. Das ist dieselbe Art
  Lücke wie die geschlossene, eine Ebene daneben, und **sie ist nicht folgenlos**: Einfluss
  ist der Anteil des Fonds am gesamten Lobbydruck, also am Verhältnis `druck : gegendruck`,
  und dieses Verhältnis hängt an beiden Regeln. Mein Vorschlag für das Folgepaket ist
  dieselbe Halbierung aus demselben Grund; entschieden ist sie hier nicht, weil sie zu
  Schritt 3 gehört und nicht zu Gegenkraft 5.
- **Ob `schrittweite[zoll]` die Rundungsschwelle der Zollzeile überschreitet.** Neu am
  2026-09-03 und die einzige Bedingung, die aus der Zollkeilentscheidung folgt. Ein
  Zollschritt läuft über zwei Rundungen — Weltpreisniveau mal Rate, dann mal `durchgriff` —,
  und für ein Land×Sektor-Paar mit niedrigem `durchgriff` kann `preishub_zoll` bei kleinen
  Schritten auf null fallen. Dann ist die Zollzeile dort **stumm, ohne es zu melden**. Die
  Prüfform steht im Abschnitt; die Zahl, die sie erfüllt, ist Kalibrierung. Der Jahrgangsbau
  hat alle acht Paare vorliegen und kann die Bedingung mechanisch prüfen — sie gehört in
  seine Ausgabe, nicht in einen Nachtlauf.
- **Ob ein `gegenlobby_satz` alle vier Zeilen zugleich trägt, jetzt mit anderem Vorzeichen.**
  Die Frage stand schon; die Entscheidung vom 2026-09-03 verschiebt sie. Die Zollzeile ist
  um den Sockel kleiner geworden — ihr Aktionsanteil ist unverändert, aber der Abstand zur
  Haushaltszeile, deren Menge das ganze BIP ist, liegt jetzt offen. Ob ein Satz beide trägt
  oder ob die Familie Lobby faktisch nur noch ein bezahlbares Instrument hat, ist am
  Prüfstand zu sehen und nicht hier. Der Entwurf hält an einem Satz fest, weil vier Sätze
  der Kalibrierung drei Achsen gäben, deren Wirkung die Mengen ohnehin erzeugen; fällt Maß 2
  daran, ist es ein Befund über den Entwurf und nicht über die Parameter.
- **Ob die Gegenlobby die Einflusshälfte des Mandats erreichbar lässt.** Einfluss ist der
  Anteil des Fonds am gesamten Lobbydruck auf ein Instrument; ein Gegendruck, der in jedem
  angefassten Land gegen `druck_max` läuft, drückt diesen Anteil unter jede Schwelle, und
  die Familie Lobby stellt in Maß 2 keinen Gewinner. Das ist die schärfste
  Kalibrierbedingung, die aus dieser Vorschrift folgt, und sie ist am Prüfstand sichtbar.
  Gibt es keinen zulässigen Satz, ist es ein Befund über den Entwurf und nicht über die
  Parameter.
- **Ob `gegenlobby_satz` als Ganzzahl fein genug ist.** Klasse 9 kennt keine
  Unterteilung, der kleinste zulässige Wert ist also ein Lobbypunkt je 10.000 Tausend USD.
  Eine Größenordnungsprobe — ausdrücklich eine Schätzung, weil `schrittweite[haushalt]` noch
  nicht feststeht: Bei einem BIP von `2,1 · 10^10` Tausend USD und einer angenommenen
  Schrittweite von 50 Basispunkten sind das `1,05 · 10^8` Tausend USD Schaden und damit
  rund **10.500 Lobbypunkte** bei `gegenlobby_satz = 1`. Ob das zu `druck_max` und zu dem
  passt, was der Fonds über `lobbykosten` aufbringt, entscheidet die Suche; da in Schritt 3
  nur das Verhältnis zählt, kann sie über `lobbykosten` gegensteuern. Reicht auch das nicht,
  wäre der Ausweg eine Zehntausendstel-Skala für `gegenlobby_satz` — ein ADR gegen T5
  Klasse 9, und zu entscheiden am Prüfstand, nicht hier.
- **Ob der Regierungswechsel Schaden erzeugen soll.** Entschieden ist: ja — die Rückstellung
  aller Instrumente ist selbst die Folge erfolgreichen Lobbyierens. Offen bleibt, ob die
  Kalibrierung danach noch einen Weg zurück findet: Gegenkraft 2 verdoppelt die Lobbykosten
  für mehrere Runden, Gegenkraft 5 legt in derselben Runde Gegendruck auf alle vier
  Instrumente. Zwei Strafen aus einer Ursache; ob daraus eine Sackgasse wird, misst Maß 2
  und nicht dieser Entwurf.
- **Ob `platzanteil` einen zulässigen Bereich hat.** Neu am 2026-09-05 und die schärfste
  Bedingung, die aus der zweiten Schicht folgt. Zu groß, und die Plätze sind tief genug, dass
  Familie 1 dort ungestört Kapital aufbaut — dann fällt die zweite Abnahmehälfte von Maß 2
  (`max(Ek) ≤ 1,25 · min(Ek)`), weil Position die anderen beiden Familien abhängt. Zu klein,
  und eine Stufe auf einem Platz ist entweder unbezahlbar oder bewegt den Preis so stark, dass
  die Schicht unbenutzbar ist — dann ist sie Dekoration und Maß 3 verliert seine dritte
  Quelle wieder. Beides ist am Prüfstand sichtbar, beides ist ein Befund über den
  Parametersatz — es sei denn, es gibt keinen zulässigen. Dann ist es der Entwurf.
- **Ob `kippung` die drei Plätze eines Ankers wirklich unterscheidet.** Sie sind per
  Konstruktion verschieden, aber ob der Unterschied groß genug ist, dass ein Suchbot ihn
  nutzt, ist eine Messung. Die Prüfform: Erreichen im Frühfenster von Maß 3 Profile mit
  Schwerpunkt auf verschiedenen Leitsektoren dasselbe Ergebnis, sind die drei Plätze eines
  Ankers ein Platz. Die Zahl ist Kalibrierung, die Form steht.
- **`3·(L+1)` überlebt die Länderwahl aus 0118, und diese Frage ist damit geschlossen.**
  Sie lautete, ob jedes Gebiet drei unterscheidbare Leitsektoren trägt — für ein Land mit
  stark beherrschender Sektorstruktur lägen die drei Plätze nach der `kippung`-Regel eng
  beieinander. Gemessen am größten normierten Sektoranteil ist der einseitigste der neun
  Anker die **USA** mit 76,6 Prozent, und die stehen seit der ersten Fassung im Modell; die
  beiden ausgeglichensten sind mit 51,3 und 47,7 zwei der fünf neuen (Saudi-Arabien,
  Indien). **Die Wahl verbessert den bindenden Fall, statt ihn zu verschärfen.** Was
  offenbleibt, ist nicht die Formel, sondern `kippung` — und das steht schon als eigene
  Frage zwei Punkte weiter oben, jetzt mit dem Land dazu, an dem sie sich entscheidet.
- **Ob `MFS_IR` für Japan, Indien und Chile einen Politiksatz auf Stufe 1 führt.** An diesem
  einen Abruf je Land hängt die Klasse dreier Länder und damit `L_R`, die Zahl der
  Prüfgegenstände (28 gegen 16 bis 22), die Sollreihen und die Sollmaske. Es ist die
  billigste offene Frage dieses Pakets — drei Abrufe nach T63 Schritt 1 — und die mit der
  größten Hebelwirkung. Sie gehört dem Datenbauer, nicht mir.
- **Ob die Klassenregel aus T61 Regel 5 die Ausschlüsse sieht, die in den Sollreihen liegen.**
  Sie leitet die Klasse allein aus den drei Politikpfadreihen ab. Zwei Ausschlussgründe
  liegen aber woanders: die fehlende Ausweichquelle für Reihe 2 (T62 Folgerung 2) und — neu
  seit diesem Paket — eine Sollreihe, die über das ganze Fenster konstant ist und deshalb
  keine Richtungstreue tragen kann. Führt `MFS_IR` einen SAMA-Satz auf Stufe 1, leitet
  Regel 5 für Saudi-Arabien „Rückvergleichsland" ab, während das Manifest „Spielland" sagen
  muss, und der Jahrgangsbau bricht ab. Der Abbruch ist richtig, die Stelle nicht. Gehört
  zu T61.
- **Ob die Toleranz `⌊L_R/2⌋` trägt.** Sie ist neu am 2026-09-06 und ersetzt die feste 2,
  weil eine feste Zahl das Hinzufügen eines Landes zu einer Verschärfung machte. Sie
  reproduziert die heutige 2 und hält den Anteil bei rund elf Prozent — aber ob elf Prozent
  die richtige Quote sind, weiß erst der Rückvergleicher am laufenden Kern. Reißen
  regelmäßig vier von 28, ist das ein Befund über das Modell und nicht über die Formel.
- **Ob der Handelsblock als *ein* Prüfgegenstand richtig gewogen ist, wenn er von 40 auf 112
  Ströme wächst.** Die Frage besteht schon bei vier Ländern und wird durch neun schärfer: Der
  schwerste Einzelgegenstand des Rückvergleichs zählt so viel wie das BIP eines einzelnen
  Landes. Die Zusammenfassung über den Median ist der Grund, warum er trotzdem nicht
  auseinanderfliegt; ob sie bei 112 Strömen noch dasselbe leistet wie bei 40, ist eine
  Messung. Nicht in diesem Paket entschieden, weil sie von der Länderzahl unabhängig ist.
- **Woher die Sektorgewichte der drei Restwelt-Plätze kommen.** Sie folgen der gleichen Regel
  aus `sektoranteil[Restwelt][s]` des Startjahrs. Die Restwelt entsteht im Jahrgang als
  Residuum, und ob ihre Sektoranteile dabei sauber anfallen, weiß der Jahrgangsbau und nicht
  ich. Fällt die Größe nicht an, ist der Ausweg der kapitalstockgewichtete Mittelwert der
  `L` Länderanteile — eine Regel, keine erfundene Zahl.
- **Ob es doch eine einbettbare Kursreihe gibt.** Die Schicht ist ohne jede Sollreihe
  entworfen, weil `daten.md` keine führt und dieser Entwurf schon festhält, dass es keinen
  Weltaktienindex unter freier Lizenz gibt. Fände der Datenbauer eine Indexreihe unter
  tragfähiger Lizenz, wären die betroffenen Plätze **Rückvergleichsländer** statt Spielländer,
  und Maß 4 gewönne Prüfgegenstände hinzu, statt keine zu verlieren. Der Entwurf hängt nicht
  daran — er gewönne nur. Zu prüfen vom Datenbauer, nicht von mir.
- **Ob die Schwellen von Maß 4 mit endogener Produktivität überhaupt erreichbar sind.**
  Unverändert das größte ungemessene Risiko des Vorhabens. Es ist keine Entwurfsfrage
  mehr, sondern eine Messung des Rückvergleichers am laufenden Kern — die Abnahmeregel
  steht jetzt, also lässt sich das Ergebnis überhaupt beurteilen.

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
