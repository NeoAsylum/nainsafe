---
typ: pruefung
paket: 0006-deckung-pruefjahrgang-1997
pruefer: daten-pruefer
datum: 2026-09-02
urteil: zurueck
kriterium_geprueft: R und die erzwingenden Reihen unabhaengig an IMF- und Weltbank-Endpunkten nachgemessen (stimmen), aber der Befund beantwortet die Kriteriumsfrage fuer eine der 31 Sollreihen zweimal widerspruechlich
befunde: 1
---

# Prüfung 0006 — Deckung des Prüfjahrgangs 1997–2021

Geprüft wurde `daten/deckungsbefund-1997.md` (376 Zeilen) gegen das Abnahmekriterium des
Pakets, gegen T23, T24 und T40 und gegen die Reihenliste in `technik.md` Abschnitt 7.

## Was ich nachgemessen habe

Alle Abrufe am **2026-09-02**, über den HTTP-Abruf des Agenten (`curl` ist in dieser
Umgebung nicht freigegeben). Wo möglich habe ich einen **anderen Zugriff** gewählt als der
Befund, damit nicht derselbe Weg zweimal dasselbe bestätigt.

### Die beiden Zahlen, an denen das Vorhaben hängt

| Behauptung im Befund | mein Abruf | Ergebnis |
|---|---|---|
| Reihe 11 USA beginnt **2001**, 31 Werte | `api.imf.org/external/sdmx/3.0/data/dataflow/IMF.RES/WEO/9.0.0/USA.GGXWDG_NGDP.A` | **bestätigt.** Frühestes Jahr 2001, 31 Beobachtungen (2001–2031), 1997–2000 ohne Wert. 2001 = 53,485146, 2020 = **132,551502**, 2021 = **125,047912** — die beiden vom Befund als Gegenprobe genannten Zahlen (132,55 / 125,05) auf zwei Nachkommastellen |
| Reihe 9 USA endet **2020** | `…/IMF.STA/MFS_IR/9.0.0/USA.DISR_RT_PT_A_PT.A` | **bestätigt.** Reihe 1950–2020, 71 Beobachtungen, **kein Wert für 2021** |
| Reihe 9 **Deutschland** ohne jede Deckung | `…/IMF.STA/MFS_IR/9.0.0/DEU.DISR_RT_PT_A_PT.A` | **bestätigt.** Antwort trägt die Struktur, aber `"values":[]` — keine einzige Beobachtung |
| Reihe 9 **China** ohne jede Deckung | `…/IMF.STA/MFS_IR/9.0.0/CHN.DISR_RT_PT_A_PT.A` | **bestätigt.** Ebenfalls leer |
| Reihe 11 BRA beginnt **2000**, 32 Werte | `…/IMF.RES/WEO/9.0.0/BRA.GGXWDG_NGDP.A` | **bestätigt.** Frühestes Jahr 2000 (62,197623), 32 Beobachtungen, 1997–1999 ohne Wert, 2021 = 88,934272 (Befund: 88,93) |

Damit ist das Fenster nachgerechnet: Startjahr `max(1997; 2001; 2000) = 2001`, Endjahr
`min(2021; 2020) = 2020`, das sind **20 Stützstellen**, nach T40 `R = stuetzstellen − 1 =`
**19**. Erzwungen von Reihe 11 USA (Start) und Reihe 9 USA (Ende) — genau die beiden Reihen,
die der Befund nennt. **Der eine Wert für R und die Liste, die ihn erzwingt, sind richtig.**

Die drei Varianten der Ausweg-Tabelle habe ich nachgerechnet und sie stimmen: ohne Reihe 9
bindet Reihe 11 USA allein, 2001–2021 = 21 Stützstellen, R = 20; ohne Reihe 9 und Reihe 11
tragen die verbleibenden 23 Sollreihen 1997–2021 vollständig, R = 24. Auch die
Sollreihenzahlen der Varianten (31 − 4 = 27, 31 − 8 = 23) stimmen.

Die Gegenprobe zu `R ≤ 26` habe ich gegen den Wortlaut von T40 gelesen: Band „überlebt"
endet bei `(R+1) × 1.000 + 3.000`, Todesband beginnt bei 31.000. 23.000 / 24.000 / 28.000
für R = 19 / 20 / 24 sind richtig gerechnet, und die Aussage „in keiner Variante erreichbar"
folgt daraus, weil das Fenster nur enger werden kann.

### Was das Kriterium nicht verlangt und ich trotzdem gemessen habe

Der Befund behauptet für 23 der 31 Sollreihen lückenlose 25 Stützstellen. Eine einzige
Innenlücke dort würde R ändern, und der Befund nennt für diese Reihen nur Randjahre. Zwei
Stichproben, beide über den vollen Zeitraum gezählt, nicht an den Rändern:

- `api.worldbank.org/v2/country/USA;CHN;DEU;BRA/indicator/NV.AGR.TOTL.ZS?date=1997:2021&format=json&per_page=200`
  — **25/25 je Land, kein Nullwert**, auch im Inneren nicht.
- `api.worldbank.org/v2/country/USA;CHN;DEU;BRA/indicator/FP.CPI.TOTL.ZG?date=1997:2021&format=json&per_page=200`
  — **25/25 je Land, kein Nullwert.**

**Einheit und Basisjahr** (die Stelle, an der Datenarbeit hier still falsch wird). Der
Befund nennt für Reihe 1 das Basisjahr 2015 und leitet daraus ab, die Reihe sei real, laufe
nach T8 bei einem Basiswechsel nicht mit und brauche keinen Wechselkursschritt. Nachgelesen
über den **Indikator-Endpunkt** statt über den Länderabruf:
`api.worldbank.org/v2/indicator/NY.GDP.MKTP.KD?format=json` — Name „GDP (constant 2015
US$)", sourceNote: „The reference year for this adjustment is 2015. This indicator is
expressed in United States dollars." **Basisjahr und Währung stimmen wie behauptet**, und
die Einordnung in T5 Klasse 2 / T8 ist damit richtig.

**Der Einheitenbruch der Reihe 10** ist die zweite Stelle, an der ich einen stillen Fehler
vermutet hätte, und der Befund macht ihn sichtbar statt ihn zu glätten. Nachgemessen
`api.worldbank.org/v2/country/DEU/indicator/PA.NUS.FCRF?date=1996:2001&format=json&per_page=50`:
1996 = 1,50477416666667, 1997 = 1,73405583333333, 1998 = 1,7596676, 1999 =
0,938283072395283, 2000 = 1,08270508132602, 2001 = 1,11653308564462. **Ziffernweise
identisch** mit der Tabelle des Befunds. Die Weltbank verkettet die Reihe tatsächlich nicht;
`verkettet_ab = 1999` aus T23 Punkt 8 wird gebraucht und steht nicht vorsorglich da.

**Der Handelsblock.** `cepii.fr/CEPII/en/bdd_modele/bdd_modele_item.asp?id=37`, abgerufen
2026-09-02: Fassung **202601**, letzte Aktualisierung **2026-01-30**, HS92 **1995–2024**,
HS96 1996–2024, HS02 2002–2024, HS07 2007–2024, HS12 2012–2024, HS17 2017–2024, HS22
2022–2024. **Alle sieben Zeilen stimmen.** 1997 und 2021 sind in HS92 enthalten, HS92
bindet in keiner Variante, und die Bemerkung, HS02 würde selbst zur bindenden Reihe, folgt
aus derselben Tabelle.

## Befund 1 — Der Zusammenzug zählt eine Reihe als tragend, die der Befund selbst als lückenhaft misst

**Wo.** `daten/deckungsbefund-1997.md` Zeile 15 („Von den 31 Sollreihen tragen **27** das
Fenster vollständig, **zwei** tragen es verkürzt und zwei tragen überhaupt nichts") und
Zeile 332 (Zusammenzug, Summenzeile: „**27 von 31 tragen**").

**Wie man den Fehler erzeugt.** Nur aus dem Dokument, ohne Netzabruf:

1. Zeile 251 lesen: Reihe 11, **BRA**, erstes Jahr **2000**, „Lücken 1997–2021: 1997–1999,
   3 Jahre", **22 Stützstellen**. Diese Sollreihe trägt 1997–2021 also **nicht**.
2. Die 31 Sollreihen aus den Abschnittstabellen abzählen, wie viele 25 Stützstellen tragen:
   Reihe 1 = 4, Reihe 2 = 12, Reihe 8 = 4, Reihe 10 = 3 (alle vollständig); Reihe 9 = **1**
   (nur BRA; USA hat 24, DEU und CHN je 0); Reihe 11 = **2** (nur CHN und DEU; USA hat 21,
   BRA hat 22).
3. Summe: `4 + 12 + 4 + 3 + 1 + 2 =` **26**, nicht 27. Verkürzt sind **drei** Reihen
   (Reihe 9 USA mit 24, Reihe 11 USA mit 21, Reihe 11 BRA mit 22), nicht zwei; leer bleiben
   zwei. Richtig heisst der Satz **26 / 3 / 2**.

**Warum es nicht auffällt.** `27 + 2 + 2` ergibt 31, genau wie `26 + 3 + 2`. Die Probe, die
ein Leser als erstes macht, geht auf. Die ausgelassene Reihe ist Reihe 11 BRA, und sie ist
die einzige der fünf nicht tragenden, die den Wert für R **nicht** erzwingt — 2000 liegt vor
dem ohnehin bindenden Startjahr 2001. Genau deshalb fällt sie aus der Zählung heraus, ohne
eine andere Zahl des Dokuments zu stören.

**Warum das das Abnahmekriterium verfehlt.** Das Kriterium verlangt, dass „für jede der 31
Sollreihen … im Befund steht, ob sie 1997 bis 2021 ohne Füllung 25 Stützstellen trägt".
Für Reihe 11 BRA steht **beides** darin: die Abschnittstabelle sagt nein, der Zusammenzug
zählt sie unter die 27, die ja sagen. Eine Frage, die ein Dokument zweimal widersprüchlich
beantwortet, ist von ihm nicht beantwortet. Dass ausgerechnet die Summenzeile falsch ist,
wiegt schwerer als ihre Stelle im Text vermuten lässt: Der Zusammenzug ist der Teil, den der
Spielentwerfer liest, wenn er nach T24 zwischen „Reihe streichen" und „Fenster kürzen"
entscheidet. Erwägt er, Reihe 11 zu streichen, muss er wissen, dass sie für **zwei** der
vier Länder reisst und nicht für eines.

**Was den Befund repariert.** Zwei Zahlen in zwei Zeilen — 27 → 26 und „zwei tragen es
verkürzt" → „drei tragen es verkürzt". **R bleibt 19**, die Liste der erzwingenden Reihen
bleibt unverändert, und keine andere Tabelle des Dokuments ist berührt. Das ist kein
Neubau des Pakets.

## Nebenbefunde — kein Grund für das Urteil, gehören dem Projektmanager

1. **Der Befund wendet seine eigene Einheitenprüfung auf die beiden Reihen nicht an, die er
   selbst als reissend meldet.** Für Reihe 1 („Division durch 1.000"), Reihe 8
   („Multiplikation mit 100") und Reihe 10 (Verkettung 1999) steht die Umrechnung in die
   Modelleinheit ausdrücklich da. Für Reihe 9 und Reihe 11 steht sie nirgends, obwohl die
   Reihenliste für beide **bp** verlangt und beide Quellen in **Prozent** liefern
   (`GGXWDG_NGDP` = % des BIP, `DISR_RT_PT_A_PT` = Prozent p. a.) — also je ein Faktor 100.
   Folgenlos für die Deckungsfrage, aber es sind genau die zwei Reihen, die der
   Spielentwerfer als nächstes anfasst, und ein stiller Faktor 100 ist der Fehlertyp, der ein
   Modell plausibel aussehen lässt und trotzdem falsch macht.
2. **Reihe 14 ist die einzige Reihe ohne Angabe zur Preisbasis, und sie ist die, bei der es
   klemmt.** BACI führt „thousands of **current** USD", Reihe 1 konstante Preise 2015; T5
   führt beide in Klasse 2, und T23 Punkt 5 stellt sie in `durchgriff = teile_gerundet(10.000
   · H, H + N)` mit `H` aus BACI und `N` aus WDI in **einen Bruch**. Der Abschnitt zu Reihe 14
   nennt die Nomenklatur, die Jahresabdeckung und die Nullstrom-Frage, aber die Preisbasis
   nicht. Das ist derselbe offene Punkt, den ich am 2026-09-02 als Befund 1 zu Paket 0007
   gemeldet habe; ich nenne ihn hier nur, weil dieses Paket die zweite Stelle ist, an der er
   hätte auffallen müssen, und weil der Jahrgangsbau ihn nicht mehr umgehen kann.
3. **Der Nebenbefund zu Reihe 12 im Befund selbst ist berechtigt und sollte nicht verloren
   gehen.** Der Haushaltssaldo (`GGXCNL_NGDP`, Politikpfad, keine Sollreihe) beginnt für die
   USA ebenfalls 2001. T24 verlangt für ihn keine 25 Stützstellen, aber wer das Fenster bei
   1997 halten will, hat für ein Instrument vier blinde Anfangsjahre. Das gehört in die
   Entscheidungsvorlage des Spielentwerfers, nicht in die Deckungstabelle.

## Wonach ich gesucht und nichts gefunden habe

- **Stille Füllung.** Keine der reissenden Reihen ist im Befund interpoliert, fortgeschrieben
  oder durch eine andere ersetzt worden; die Ersatzreihe `FR.INR.LEND` wird ausdrücklich als
  entwertetes Indiz geführt und nicht eingesetzt. T24 ist eingehalten.
- **Eine Reihe ausserhalb von `daten.md`.** `api.imf.org` ist derselbe Anbieter wie der in
  `daten.md` geprüfte IWF, nur der aktuelle Zugang; WDI und BACI stehen dort. Keine neue
  Quelle im Bestand.
- **Grenzüberschreitung des Pakets.** Der Befund wählt kein Fenster, streicht keine Reihe,
  setzt keinen Status und lädt nichts herunter. Die beiden Auswege aus T24 bleiben beim
  Spielentwerfer.
- **Eine härtere bindende Reihe als die beiden genannten.** Zwei Innenlücken-Stichproben über
  den vollen Zeitraum (NV.AGR, FP.CPI, je 4 Länder) blieben leer; ich habe keine dritte Reihe
  gefunden, die das Fenster über 2001–2020 hinaus verkürzt.
- **Ein Rechenfehler in R oder in der Schranke `R ≤ 26`.** Fenster, Stützstellenzahl,
  `R = stuetzstellen − 1`, die drei Varianten und die drei Bandgrenzen sind einzeln
  nachgerechnet und stimmen.

## Reproduzierbarkeit

Der Befund trägt Abrufdatum 2026-09-01 an jeder Reihe und benennt Datenflüsse mit Fassung
(`IMF.RES/WEO` 9.0.0, Stand 2025-09-30; `IMF.STA/MFS_IR` 9.0.0; BACI 202601, Stand
2026-01-30). Meine Wiederholung am 2026-09-02 lieferte an sechs unabhängig geprüften Stellen
dieselben Zahlen, an zwei davon ziffernweise. **Der Befund ist wiederholbar.** Die
Einschränkung, die er selbst nennt — Sammelabfragen über mehrere Länder sind im kompakten
SDMX-JSON nicht sicher auszuzählen —, habe ich bestätigt gefunden: Meine Einzelabrufe je
Land waren eindeutig, ein Auszählen einzelner Jahreswerte innerhalb einer langen Reihe war
es nicht. Für die Randjahre, auf die es hier ankommt, reicht der Abgleich „Zahl der Werte
gegen Länge des Zeitraums", und der geht bei allen vier nachgemessenen Reihen auf.
