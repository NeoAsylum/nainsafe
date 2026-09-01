---
typ: deckungsbefund
paket: 0006-deckung-pruefjahrgang-1997
rolle: datenbauer
datum: 2026-09-01
gegenstand: 31 Sollreihen + Handelsblock, Fenster 1997-2021, Fuellung verboten (T24)
ergebnis: Fenster 1997-2021 traegt nicht
R: 19
erzwungen_von: [Reihe 11 USA (beginnt 2001), Reihe 9 USA (endet 2020)]
ohne_deckung: [Reihe 9 Deutschland, Reihe 9 China]
---

# Trägt der Prüfjahrgang 1997–2021 25 Stützstellen ohne Füllung?

**Nein.** Von den 31 Sollreihen tragen 27 das Fenster vollständig, zwei tragen es verkürzt
und **zwei tragen überhaupt nichts** — der Leitzins für Deutschland und für China existiert
in der Quelle, die die Reihenliste dafür benennt, in keinem einzigen Jahr.

Das sind zwei verschiedene Sorten Befund, und sie dürfen nicht zusammengeworfen werden:

- **Eine Reihe, die spät beginnt oder früh endet, kürzt das Fenster.** Sie führt zu einem
  kleineren R und kostet nach T40 eine Zahl im Manifest.
- **Eine Reihe ohne einen einzigen Wert kürzt nichts.** Kein Fenster ist so kurz, dass sie
  hineinpasst. Für sie steht dem Spielentwerfer nach T24 nur der andere Ausweg offen —
  Reihe streichen oder Quelle ersetzen —, und beides entscheidet er, nicht ich.

## Der eine Wert für R

**R = 19**, Fenster **2001–2020**, **20 Stützstellen** (`R = stuetzstellen − 1`, T40).

Erzwungen von genau zwei Reihen:

| Reihe | Land | was sie erzwingt | Kosten |
|---|---|---|---|
| **11** Staatsschuldenquote | USA | Reihe beginnt **2001** | Startjahr 1997 → 2001, **4 Stützstellen** |
| **9** Leitzins | USA | Reihe endet **2020** | Endjahr 2021 → 2020, **1 Stützstelle** |

25 − 4 − 1 = 20 Stützstellen, also R = 19.

**Dieser Wert gilt erst, wenn die Reihe-9-Lücke für Deutschland und China geschlossen ist.**
Solange sie offen ist, gibt es überhaupt kein zulässiges Fenster, und R ist gegen den
Wortlaut der Spezifikation nicht messbar. R = 19 ist der größte Wert, den die **messbaren**
Reihen zulassen — die Zahl, die gilt, sobald der Spielentwerfer die beiden leeren Reihen
entschieden hat.

**Wie sich R unter seinen Auswegen bewegt**, damit die Entscheidung eine Zahl neben sich hat:

| Entscheidung zu Reihe 9 | bindende Reihe | Fenster | Stützstellen | R |
|---|---|---|---:|---:|
| Reihe 9 ganz gestrichen (dann 27 Sollreihen) | 11 (USA) | 2001–2021 | 21 | **20** |
| Reihe 9 für DE/CN aus einer Quelle ergänzt, die 2001–2020 deckt | 11 (USA), 9 (USA) | 2001–2020 | 20 | **19** |
| Reihe 9 **und** Reihe 11 gestrichen (dann 23 Sollreihen) | keine | 1997–2021 | 25 | **24** |

### Gegenprobe zur Schranke `R ≤ 26` (T40)

T40 bricht den Jahrgangsbau bei `R > 26` ab, weil bei `R = 27` das Band „überlebt"
(`(R+1)×1.000 + 3.000 = 31.000`) mit dem unteren Ende des Todesbandes (31.000)
zusammenfiele. **Jeder in dieser Messung erreichbare Wert hält die Schranke**, und mit
wachsendem Abstand, weil das Fenster nur enger werden kann:

| R | Ende Band „überlebt" | Beginn Todesband | disjunkt? |
|---:|---:|---:|---|
| 19 | 20.000 + 3.000 = 23.000 | 31.000 | ja, 8.000 Luft |
| 20 | 21.000 + 3.000 = 24.000 | 31.000 | ja, 7.000 Luft |
| 24 (Entwurfsannahme) | 25.000 + 3.000 = 28.000 | 31.000 | ja, 3.000 Luft |

Die Schranke ist in keiner Variante dieses Befunds erreichbar und wird nicht zum Thema.

## Reihe für Reihe

Abgerufen am **2026-09-01**. Geprüft ist jeweils die Reihe, die nach der Reihenliste in
`technik.md` Abschnitt 7 tatsächlich eingebettet wird — nicht ein Näherungswert. Wo das
nicht gelang, steht es in der Zeile.

Der direkte Netzabruf per `curl` war in diesem Lauf nicht verfügbar (Berechtigung
verweigert); alle Abrufe liefen über den HTTP-Abruf des Agenten. Das ändert die URLs nicht,
nur den Weg.

### Reihe 1 — BIP, konstante Preise (4 Sollreihen)

Quelle WDI, Indikator `NY.GDP.MKTP.KD` (konstante Preise **2015** US$).
`api.worldbank.org/v2/country/USA;CHN;DEU;BRA/indicator/NY.GDP.MKTP.KD?date=1997:2021&format=json&per_page=200`,
abgerufen 2026-09-01.

| Land | erstes Jahr | letztes Jahr | Lücken 1997–2021 | Stützstellen |
|---|---:|---:|---:|---:|
| USA | 1997 | 2021 | 0 | 25 |
| CHN | 1997 | 2021 | 0 | 25 |
| DEU | 1997 | 2021 | 0 | 25 |
| BRA | 1997 | 2021 | 0 | 25 |

**Trägt.** Zur Einheit: Das Basisjahr ist 2015 und gilt für alle vier Länder gleich — die
Reihe ist real, läuft also nach T8 bei einem Basiswechsel nicht mit, und die Umrechnung in
die Modelleinheit Tsd USD ist eine Division durch 1.000 ohne Wechselkursschritt.

### Reihe 2 — Wertschöpfungsanteil je Sektor (12 Sollreihen)

Quelle WDI, drei Indikatoren, je vier Länder. Abrufe 2026-09-01:
`api.worldbank.org/v2/country/USA;CHN;DEU;BRA/indicator/NV.AGR.TOTL.ZS?date=1997:2021&format=json&per_page=200`
sowie dieselbe URL mit `NV.IND.TOTL.ZS` und `NV.SRV.TOTL.ZS`.

| Indikator | USA | CHN | DEU | BRA | Lücken |
|---|---:|---:|---:|---:|---:|
| `NV.AGR.TOTL.ZS` | 25 | 25 | 25 | 25 | 0 |
| `NV.IND.TOTL.ZS` | 25 | 25 | 25 | 25 | 0 |
| `NV.SRV.TOTL.ZS` | 25 | 25 | 25 | 25 | 0 |

Alle zwölf: erstes Jahr 1997, letztes Jahr 2021, keine Lücke. **Tragen.**

Das deckt sich mit der Prüfung der drei US-Anteilsreihen, die `spiel.md` am 2026-09-01
selbst vorgenommen hat, und bestätigt sie für die anderen drei Länder mit.

### Reihe 8 — Verbraucherpreise (4 Sollreihen)

Quelle WDI, `FP.CPI.TOTL.ZG` (Jahresrate in Prozent — die Modelleinheit bp Jahresrate ist
eine Multiplikation mit 100, kein Reihenwechsel).
`api.worldbank.org/v2/country/USA;CHN;DEU;BRA/indicator/FP.CPI.TOTL.ZG?date=1997:2021&format=json&per_page=200`,
abgerufen 2026-09-01.

| Land | erstes Jahr | letztes Jahr | Lücken | Stützstellen |
|---|---:|---:|---:|---:|
| USA | 1997 | 2021 | 0 | 25 |
| CHN | 1997 | 2021 | 0 | 25 |
| DEU | 1997 | 2021 | 0 | 25 |
| BRA | 1997 | 2021 | 0 | 25 |

**Trägt.** Die Reihenliste markiert sie als Verdachtsfall der Drittanbieter-Ausnahme
(IWF-gestützt); das ist eine Lizenzfrage und gehört zu Paket 0005, nicht hierher. Die
**Deckung** ist vollständig.

### Reihe 9 — Leitzins (4 Sollreihen) — **die Reihe, an der es reißt**

Die Reihenliste nennt IWF IFS. Der alte IFS-Zugang existiert nicht mehr, und der neue führt
keinen Datenfluss namens IFS:

| Weg | Ergebnis | Datum |
|---|---|---|
| `dataservices.imf.org/REST/SDMX_JSON.svc/CompactData/IFS/A.US+CN+DE+BR.FPOLM_PA?startPeriod=1997&endPeriod=2021` | **DNS-Fehler**, Host existiert nicht mehr | 2026-09-01 |
| `imf.org/external/datamapper/api/v1/GGXWDG_NGDP/USA/CHN/DEU/BRA` | **HTTP 403** | 2026-09-01 |
| `imf.org/external/datamapper/api/v1/indicators` | **HTTP 403** | 2026-09-01 |
| `data.imf.org/en/Resource-Pages/IMF-API` | **HTTP 403** | 2026-09-01 |
| `api.imf.org/external/sdmx/3.0/structure/dataflow/IMF.STA?format=sdmx-json` | **erreichbar**, aber **kein Datenfluss `IFS`** darin | 2026-09-01 |

**Damit ist die Sackgasse aus `daten.md` und `spiel.md` bestätigt — aber sie ist umgehbar:**
`api.imf.org` antwortet, nur `imf.org` und `data.imf.org` nicht. IFS ist seit der Umstellung
in Teiltabellen zerlegt; die Zinsen liegen in **`IMF.STA/MFS_IR` („Monetary and Financial
Statistics, Interest Rate", Fassung 9.0.0)**. Die Nachfolgereihe des IFS-Leitzinses heißt
dort **`DISR_RT_PT_A_PT`** (Diskontsatz).

Abruf `api.imf.org/external/sdmx/3.0/data/dataflow/IMF.STA/MFS_IR/9.0.0/*.DISR_RT_PT_A_PT.A`,
abgerufen 2026-09-01 — **70 Länder tragen die Reihe**, darunter USA und BRA:

| Land | Reihe vorhanden? | erstes Jahr | letztes Jahr | Lücken 1997–2021 | Stützstellen |
|---|---|---:|---:|---:|---:|
| USA | ja | 1950 | **2020** | **2021 fehlt** | **24** |
| BRA | ja | **1997** | 2025 | 0 | 25 |
| DEU | **nein** | — | — | alle 25 | **0** |
| CHN | **nein** | — | — | alle 25 | **0** |

Einzelabrufe zur Gegenprobe, alle 2026-09-01, Pfad
`api.imf.org/external/sdmx/3.0/data/dataflow/IMF.STA/MFS_IR/9.0.0/<Schlüssel>?format=sdmx-csv`:
`USA.DISR_RT_PT_A_PT.A`, `BRA.DISR_RT_PT_A_PT.A`, `DEU.DISR_RT_PT_A_PT.A` (leer),
`CHN.DISR_RT_PT_A_PT.A` (leer), `DEU.*.A`, `CHN.*.A`, `USA.*.A`, `BRA.*.A`, `U2.*.A` (leer).

**Deutschland und China stehen in der Länderliste dieser Reihe nicht**, und auch kein
Euroraum-Aggregat (`U2`, `EA`, `XM`, `EMU` geprüft, keines vorhanden). Deutschland trägt in
`MFS_IR` ausschließlich harmonisierte Bankzinssätze (`HENBD_…`, `HENBL_…`, `HEOADAM_…`,
`HEANBLCCO_…`, `S13BOND_…`) — Kredit- und Einlagenzinsen der Geschäftsbanken und eine
Anleiherendite, **kein Leitzins**. China trägt in `MFS_IR` überhaupt keine Jahresreihe.

**Was der Ersatzbeleg aus `spiel.md` beweist und was nicht.** `spiel.md` hat den
Verdachtsfall gegen `FR.INR.LEND` (Sollzins der Banken, WDI) geprüft und daraus geschlossen,
der Schnitt auf 1997 räume China und Brasilien zugleich ab. Nachgemessen
(`api.worldbank.org/v2/country/USA;CHN;DEU;BRA/indicator/FR.INR.LEND?date=1997:2021&format=json&per_page=200`,
abgerufen 2026-09-01):

| Land | Stützstellen 1997–2021 |
|---|---:|
| USA | 25 |
| CHN | 25 |
| BRA | 25 |
| **DEU** | **0** |

Der Ersatzbeleg deckt **drei von vier Ländern** und genau das vierte nicht, das auch in der
echten Reihe fehlt. Er war nie ein Beweis — `FR.INR.LEND` ist ein Bankzins und kein
Leitzins —, und er ist jetzt auch als Indiz entwertet: Die Kante, an der er gemessen wurde
(1995/1996 bei CHN und BRA), ist nicht die Kante, an der die Sache scheitert.

**Zwei Dinge, die zur Entscheidung gehören und keine Deckungsfrage sind:**

1. **`DISR` ist kein einheitlicher Begriff über Länder hinweg.** Für die USA ist es der
   Diskontsatz des Fed-Diskontfensters (nachgerechnet: 1997 = 5,00, 2000 = 6,00,
   2008 = 0,50, 2019 = 2,25, 2020 = 0,25 — die richtigen Zahlen), für Brasilien der
   Rediskontsatz (1997 = 45,09, 2020 = 8,01), und der ist **nicht** die Selic. Eine
   Sollreihe, die je Land eine andere Größe misst, misst im Rückvergleich je Land etwas
   anderes. Das ist eine Entwurfsfrage, keine Datenfrage, und sie gehört dem Spielentwerfer.
2. **Bei Fensterbeginn 2001 verliert Deutschland sein Zinsinstrument vollständig.**
   T23 Punkt 8 setzt für den deutschen Leitzins `exogen_ab = 1999`; nach T40 ist
   `exogen_ab_runde = bruchjahr − startjahr + 1`. Bei `startjahr = 1997` ergibt das Runde 3,
   bei `startjahr = 2001` ergibt es **Runde −1** — der Bruch liegt **vor** dem Fenster.
   Deutschland folgt dann über die ganze Partie exogen dem Euroraum, und der Weltlauf hat
   für eines der vier spielbaren Länder ein Instrument weniger zu prüfen. Kein Fehler, aber
   eine Folge des kürzeren Fensters, die niemand bestellt hat.

### Reihe 10 — Wechselkurs gegen USD (3 Sollreihen)

Quelle WDI, `PA.NUS.FCRF` (Landeswährung je US$, Jahresdurchschnitt).
`api.worldbank.org/v2/country/CHN;DEU;BRA/indicator/PA.NUS.FCRF?date=1997:2021&format=json&per_page=200`,
abgerufen 2026-09-01.

| Land | erstes Jahr | letztes Jahr | Lücken | Stützstellen |
|---|---:|---:|---:|---:|
| CHN | 1997 | 2021 | 0 | 25 |
| DEU | 1997 | 2021 | 0 | 25 |
| BRA | 1997 | 2021 | 0 | 25 |

**Trägt — aber mit einem Einheitenbruch, der keine Lücke ist und deshalb hier ausdrücklich
steht**, damit ihn niemand für eine hält. Nachgemessen
(`api.worldbank.org/v2/country/DEU/indicator/PA.NUS.FCRF?date=1996:2001&format=json&per_page=50`,
abgerufen 2026-09-01):

| Jahr | Wert | Währung |
|---:|---:|---|
| 1997 | 1,73405583333333 | DEM je USD |
| 1998 | 1,7596676 | DEM je USD |
| 1999 | 0,938283072395283 | EUR je USD |
| 2000 | 1,08270508132602 | EUR je USD |

Die Weltbank verkettet die Reihe **nicht** — sie wechselt 1999 die Einheit. Auf Niveaus
gelesen fällt der Kurs um 47 Prozent, ohne dass sich etwas bewegt hätte. T23 Punkt 8 fängt
das mit `verkettet_ab = 1999` und dem unwiderruflichen Umrechnungskurs 1,95583 ab; die
Messung bestätigt, dass dieses Feld gebraucht wird und nicht bloß vorsorglich dasteht.

**Bei Fensterbeginn 2001 liegt der Bruch vor dem Fenster** und die Verkettung entfällt —
dieselbe Verschiebung, die beim Leitzins ein Instrument kostet, spart hier einen Sonderfall.
Für jedes Fenster, das 1997, 1998 oder 1999 enthält, wird sie gebraucht.

### Reihe 11 — Staatsschuldenquote (4 Sollreihen) — **kürzt das Fenster**

Quelle IWF WEO, Indikator `GGXWDG_NGDP` (Bruttoschuld des Gesamtstaats in % des BIP),
Datenfluss `IMF.RES/WEO`, Fassung 9.0.0, Stand der Reihe laut Antwort **2025-09-30**.
Einzelabrufe
`api.imf.org/external/sdmx/3.0/data/dataflow/IMF.RES/WEO/9.0.0/<Land>.GGXWDG_NGDP.A?format=sdmx-csv`
für USA, CHN, DEU, BRA, alle abgerufen 2026-09-01.

| Land | erstes Jahr | letztes Jahr | Lücken 1997–2021 | Stützstellen |
|---|---:|---:|---:|---:|
| **USA** | **2001** | 2031 | **1997–2000, 4 Jahre** | **21** |
| CHN | 1995 | 2031 | 0 | 25 |
| DEU | 1991 | 2031 | 0 | 25 |
| **BRA** | **2000** | 2031 | **1997–1999, 3 Jahre** | **22** |

**Die USA sind die bindende Reihe des ganzen Befunds.** Sie erzwingen allein den Sprung des
Startjahrs von 1997 auf 2001 und kosten vier der 25 Stützstellen.

**Wie das nachgeprüft ist, weil daran die Zahl hängt.** Der kompakte SDMX-JSON-Aufbau ist
über einen Textabruf nicht sicher auszuzählen — zwei Lesungen derselben Sammelabfrage haben
sich widersprochen (erste: USA ab 2000; zweite: USA ab 1995). Deshalb ist je Land **einzeln**
abgerufen und jede Reihe an drei Dingen geprüft worden, die zusammen nicht zufällig stimmen
können:

1. **Zahl der Werte gleich Länge des Zeitraums.** USA: 2001–2031 sind 31 Jahre, 31 Werte
   geliefert. CHN: 1995–2031 sind 37 Jahre, 37 Werte. DEU: 1991–2031 sind 41 Jahre,
   41 Werte. BRA: 2000–2031 sind 32 Jahre, 32 Werte.
2. **Werte gegen bekannte Zahlen.** USA 2020 = 132,55 und 2021 = 125,05; DEU 2010 = 81,03
   und 2020 = 68,04; CHN 2020 = 70,13; BRA 2020 = 96,01 und 2021 = 88,93. Alle sechs sind
   die richtigen WEO-Werte. Eine um ein Jahr verschobene Zuordnung hätte sie verfehlt.
3. **Zweite Reihe desselben Blocks.** `GGXCNL_NGDP` (Haushaltssaldo, Reihe 12) für die USA
   beginnt **ebenfalls 2001** und liefert 31 Werte, darunter 2009 = −13,18 und 2020 = −14,13
   — die richtigen Zahlen. Zwei unabhängige Reihen mit demselben Startjahr sind kein
   Auslesefehler, sondern die bekannte Eigenschaft des WEO, die Finanzstatistik des
   US-Gesamtstaats erst ab 2001 zu führen.

Punkt 3 ist zugleich ein **Nebenbefund außerhalb der 31 Sollreihen**: Reihe 12
(Haushaltssaldo) ist nach der Reihenliste ein historischer Politikpfad und keine Sollreihe,
T24 verlangt für sie also keine 25 Stützstellen. Sie beginnt für die USA aber an derselben
Stelle, und ein Politikpfad mit vier fehlenden Anfangsjahren macht das erste Fünftel des
Weltlaufs für dieses Instrument blind. Wer das Fenster bei 1997 halten will, muss das
mitentscheiden.

**Die Weltbank ist hier kein Ausweg**, obwohl sie näher läge:
`api.worldbank.org/v2/country/USA;CHN;DEU;BRA/indicator/GC.DOD.TOTL.GD.ZS?date=1997:2021&format=json&per_page=200`,
abgerufen 2026-09-01, liefert USA 25, BRA 12 (erst ab 2010), **CHN 0, DEU 0**. Das ist
deutlich schlechter als WEO und deckt zwei Länder gar nicht. Die Wahl der Reihenliste ist
richtig; sie reicht nur nicht bis 1997.

### Reihe 14 — Handelsblock, 40 Ströme (eigener Block)

Nicht Strom für Strom abgerufen, sondern nach Vorgabe des Pakets über die Jahresabdeckung
von BACI. `cepii.fr/CEPII/en/bdd_modele/bdd_modele_item.asp?id=37`, abgerufen 2026-09-01:

| Nomenklatur | erstes Jahr | letztes Jahr |
|---|---:|---:|
| **HS92** (die verwendete, T23 Punkt 9) | **1995** | 2024 |
| HS96 | 1996 | 2024 |
| HS02 | 2002 | 2024 |
| HS07 | 2007 | 2024 |
| HS12 | 2012 | 2024 |
| HS17 | 2017 | 2024 |
| HS22 | 2022 | 2024 |

Fassung **202601**, letzte Aktualisierung laut Seite **2026-01-30**.

**1997 ist enthalten**, 2021 ebenso. HS92 deckt jedes Fenster ab 1995 und bindet in keiner
Variante dieses Befunds. Die Nomenklaturwahl HS92 ist auch die einzige, die das kann —
HS02 begänne erst 2002 und würde selbst zur bindenden Reihe.

**Eine Einschränkung, die die Jahresabdeckung nicht abdeckt und die kein Abruf schließt.**
Dass BACI das Jahr 1997 führt, heißt nicht, dass jeder der 40 Ströme in jedem Jahr eine
Zeile hat. BACI meldet je gerichtetem Land-Land-Produkt-Paar nur beobachtete Ströme; ein
Paar ohne Zeile bedeutet **gemessene Null**, nicht **fehlender Wert**. Das ist für T24 ein
Unterschied, den der Jahrgangsbau entscheiden muss und der hier nicht entschieden wird:
Eine Null ist keine Lücke und darf nicht als `gefuellt` gekennzeichnet werden, sonst zählt
der Rückvergleich echte Nullhandelsjahre aus dem Fehlermaß heraus. Nach der Aggregation
über die Konkordanz — Kapitel 01–24 auf Sektor 1, 25–97 auf Sektor 2 — ist ein Nullstrom
zwischen zwei der fünf Gebiete allerdings unwahrscheinlich; der einzige Kandidat wäre die
Landwirtschaft in einem kleinen Paar, und `spiel.md` nennt Brasilien–China genau dort als
prozentual stark schwankend. **Zu messen ist das erst beim Jahrgangsbau, an der fertig
aggregierten Matrix**, nicht am Rohbestand — nach dem Zuschnitt dieses Pakets ausdrücklich
nicht mein Auftrag.

## Zusammenzug

| Reihe | Sollreihen | trägt 1997–2021? | frühestes gemeinsames Startjahr | spätestes gemeinsames Endjahr |
|---|---:|---|---:|---:|
| 1 BIP | 4 | ja | 1997 | 2021 |
| 2 Sektoranteile | 12 | ja | 1997 | 2021 |
| 8 Verbraucherpreise | 4 | ja | 1997 | 2021 |
| **9 Leitzins** | 4 | **nein** | — (DE, CN leer) | **2020** (USA) |
| 10 Wechselkurs | 3 | ja (Einheitenbruch 1999) | 1997 | 2021 |
| **11 Staatsschuld** | 4 | **nein** | **2001** (USA) | 2021 |
| **Summe** | **31** | **27 von 31 tragen** | | |
| 14 Handelsblock | 40 Ströme | ja | 1995 | 2024 |

## Was ich nicht getan habe

- **Nichts gefüllt.** T24 verbietet es für den Prüfjahrgang; keine der reißenden Reihen ist
  interpoliert, fortgeschrieben oder durch eine andere ersetzt worden.
- **Keine Reihe gestrichen und kein Fenster gewählt.** Beide Auswege stehen dem
  Spielentwerfer zu. Dieser Befund nennt die Zahl, die jeder Ausweg kostet, und sonst nichts.
- **Nichts heruntergeladen und nichts eingebettet.** Dieses Paket erzeugt diese Textdatei.
- **Keine Lizenz geprüft.** Das ist Paket 0005.
- **Keine Quelle außerhalb von `daten.md` gemessen.** `api.imf.org` ist kein neuer Anbieter,
  sondern der aktuelle Zugang zu dem in `daten.md` bereits geprüften IWF; WDI, BACI und PWT
  stehen dort ebenfalls. Die Reihen 3, 4 und 15 (PWT) sind keine Sollreihen und deshalb
  nicht gemessen; PWT 11.0 reicht nach `daten.md` von 1950 bis 2023 und kann in keinem hier
  betrachteten Fenster binden.

## Namensnennung der in diesem Befund benutzten Quellen

Gehört nach der Lizenz ins Produkt, nicht nur hierher; sie steht hier, damit der
Jahrgangsbau sie nicht neu zusammensuchen muss.

- **Weltbank:** „The World Bank: World Development Indicators" — CC BY 4.0, Änderungen sind
  zu kennzeichnen (`datacatalog.worldbank.org/public-licenses`, nach `daten.md`).
- **IWF:** Quelle IWF, unverändert und korrekt zu nennen; materielle Transformation ist
  auszuweisen. Datenflüsse `IMF.RES/WEO` 9.0.0 (Stand 2025-09-30) und `IMF.STA/MFS_IR`
  9.0.0.
- **CEPII BACI:** „BACI: International Trade Database at the Product-Level (CEPII)",
  Etalab Open Licence 2.0, Quellenangabe mit Link. Fassung 202601, Stand 2026-01-30.

## Was der nächste Lauf wissen muss

- **`api.imf.org` trägt, `imf.org` und `data.imf.org` nicht.** Der Pfad ist
  `api.imf.org/external/sdmx/3.0/data/dataflow/<Agentur>/<Fluss>/<Fassung>/<Schlüssel>`,
  Schlüssel in der Reihenfolge `LAND.INDIKATOR.FREQUENZ`, Ländercode ISO-3, Platzhalter `*`.
  Die Strukturabfrage liegt unter `…/structure/dataflow/<Agentur>` beziehungsweise
  `…/structure/datastructure/<Agentur>`.
- **`startPeriod` und `endPeriod` werden ignoriert** — die Antwort enthält immer die ganze
  Reihe. Wer ein Fenster misst, muss den Zeitraum selbst abzählen.
- **Sammelabfragen über mehrere Länder sind nicht sicher auszählbar.** Der kompakte
  SDMX-JSON-Aufbau kodiert Reihen als Indexschlüssel; zwei Lesungen derselben Antwort haben
  sich in diesem Lauf widersprochen. Je Land einzeln abrufen und die Wertezahl gegen die
  Zeitraumlänge prüfen.
- **`format=csv` und `format=sdmx-csv` werden von `api.imf.org` nicht bedient**; die Antwort
  bleibt JSON.
