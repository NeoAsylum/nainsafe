---
typ: lizenzbefund
paket: 0014-lizenzpruefung-restliche-reihen
rolle: datenbauer
datum: 2026-09-02
ueberarbeitet: 2026-09-02 (Paket 0018-lizenzbefund-klaerungsliste)
gegenstand: Die restlichen Reihen der Reihenliste — WDI-Reihen 1, 2, 5, 6 gegen die Drittanbieter-Ausnahme, und die Lizenzen der vier Nicht-WDI-Quellen gegen einen gleichartigen Vorbehalt
zaehlbereiche: "_paket zaehlt die 11 Reihen dieses Pakets, _gesamt alle 15 Reihen mit Datenanker unter Fortschreibung der Urteile aus Paket 0005 (Reihen 7, 8, 10, 13)"
codes_abgerufen_reihen: 6 (NY.GDP.MKTP.KD, NV.AGR.TOTL.ZS, NV.IND.TOTL.ZS, NV.SRV.TOTL.ZS, SP.POP.TOTL, SL.TLF.TOTL.IN)
codes_abgerufen_gegenprobe: 2 (SL.EMP.TOTL.SP.ZS, IQ.CPA.ECON.XQ) — tragen kein Urteil und keine volle Abruf-URL; das Abnahmekriterium gilt gegen die sechs darueber
reihen_paket: 11 (1, 2, 3, 4, 5, 6, 9, 11, 12, 14, 15)
reihen_frei_paket: 4 (3, 4, 14, 15)
reihen_unklar_paket: 7 (1, 2, 5, 6, 9, 11, 12)
reihen_gesperrt_paket: 0
sollreihen_frei_paket: 0 (die Reihen 3, 4, 14, 15 tragen keine Sollreihe)
sollreihen_unklar_paket: 24 (Reihe 1: 4, Reihe 2: 12, Reihe 9: 4, Reihe 11: 4; die Reihen 5, 6, 12 tragen keine)
sollreihen_gesperrt_paket: 0
reihen_frei_gesamt: 6 (3, 4, 8, 10, 14, 15)
reihen_unklar_gesamt: 8 (1, 2, 5, 6, 7, 9, 11, 12)
reihen_gesperrt_gesamt: 1 (13, aus Paket 0005)
sollreihen_frei_gesamt: 7 (Reihe 8: 4, Reihe 10: 3 — beide aus Paket 0005)
sollreihen_unklar_gesamt: 24 (dieselben vier Reihen wie sollreihen_unklar_paket)
sollreihen_gesperrt_gesamt: 0 (Reihe 13 traegt keine Sollreihe)
pruefgegenstaende_ungefaehrdet_gesamt: 1 von 16
befund_an_projektmanager: ja
befund_an_architekt: ja
---

# Kein Fund ist gesperrt, und trotzdem ist das die teurere Antwort: 24 der 31 Sollreihen sind unklar

**Die Spalte „Verdacht" hält nirgends.** Sechs Indikatorcodes, die die Reihenliste mit
„nein" führt, wurden gemessen; **alle sechs** nennen im Feld `Source` mindestens einen
Bestand ausserhalb der Weltbank. Der Prüfbefund zu 0005 hatte drei davon stichprobenweise
gefunden — die Stichprobe war nicht zufällig günstig, sie war vollständig.

**Aber die Reihe 2 zerfällt, und das ist der wichtigste Einzelfund.** Der Prüfbefund
schliesst von `NV.AGR.TOTL.ZS` auf alle zwölf Sollreihen der Reihe 2. Gemessen nennen
`NV.IND.TOTL.ZS` und `NV.SRV.TOTL.ZS` die OECD **nicht**; ihr Feld `Source` lautet anders
als das der Landwirtschaftsreihe. Vom OECD-Problem betroffen sind damit **4 der 12**
Sollreihen, nicht zwölf. Die übrigen acht sind nicht frei, sondern auf andere Weise
unklar — sie nennen nationale Ämter und Notenbanken statt einer benannten Organisation mit
eigenen Bedingungen.

**Die beiden Gründe schliessen einander nicht aus, und darauf kommt es bei der Klärungsliste
an.** Reihe 1 und 2a tragen den Ämter-und-Notenbanken-Grund **zusätzlich** zur OECD, im ersten
Halbsatz ihres eigenen `Source`-Feldes. Kein einzelner Klärungsschritt hebt deshalb einen
Prüfgegenstand; die Rechnung dazu steht unter „Was zu tun bleibt".

**Kein Urteil lautet `gesperrt`.** Es gibt keinen zweiten Fall wie Reihe 13, wo ein
Drittanbieter seine Zustimmung ausdrücklich vorbehält. Was es gibt, sind sieben Reihen,
deren Bestände von Stellen kommen, die `daten.md` nicht positiv geprüft hat — und für drei
davon (1, 5, 6) steht mit der Penn World Table eine geprüfte Ausweichquelle schon in der
Reihenliste, für Reihe 2 **keine**.

**Die drei Nicht-WDI-Lizenzen sind der freundliche Teil.** Penn World Table: kein
Drittanbietervorbehalt, Seite im Volltext gelesen. CEPII BACI: die Etalab-Lizenz enthält das
**Gegenteil** eines Vorbehalts, nämlich eine Zusicherung, dass keine fremden Rechte
enthalten sind. IWF: ein Vorbehalt ist da, er steht im Definitionssatz des Wortes „Data",
und ich konnte ihn nicht wörtlich lesen, weil `imf.org` den Abruf erneut abweist.

---

## 1. Die sechs WDI-Codes im Überblick

Sämtliche Abrufe am **2026-09-02**, je Code über beide Endpunkte
(`…/v2/sources/2/series/<code>/metadata?format=json` mit dem Feld `Source` und
`…/v2/indicator/<code>?format=json` mit dem Feld `sourceOrganization`), beide zeichengleich.

| Reihe | Code | `Source` nennt ausserhalb der WB | Urteil | Sollreihen |
|---:|---|---|---|---:|
| 1 | `NY.GDP.MKTP.KD` | OECD, nationale Ämter/Notenbanken | **unklar** | 4 |
| 2a | `NV.AGR.TOTL.ZS` | OECD, nationale Ämter/Notenbanken | **unklar** | 4 |
| 2b | `NV.IND.TOTL.ZS` | nationale Ämter (NSOs), Notenbanken | **unklar** | 4 |
| 2c | `NV.SRV.TOTL.ZS` | nationale Ämter (NSOs), Notenbanken | **unklar** | 4 |
| 5 | `SP.POP.TOTL` | UN Population Division, NSOs, **Eurostat**, UN Statistics Division | **unklar** | 0 |
| 6 | `SL.TLF.TOTL.IN` | ILO (`estimates based on external database`), UN Population Division | **unklar** | 0 |

**Die Codes zu den Reihen 5 und 6 stehen nirgends in `specs/`.** Die Reihenliste nennt
Indikatorcodes ausschliesslich für Reihe 2; `grep` über `daten.md`, `spiel.md` und
`technik.md` findet keine weiteren. Ich habe sie im Indikatorverzeichnis der Weltbank
gesucht und nach der Modelleinheit der Reihenliste gewählt („Personen", jährlich). Das ist
eine Wahl, keine Vorgabe — siehe Befund 3.

---

## Reihe 1 — BIP, konstante Preise — **unklar**

**Indikatorcode:** `NY.GDP.MKTP.KD`, `IndicatorName: "GDP (constant 2015 US$)"`.
Derselbe Code, den `deckungsbefund-1997.md` (Paket 0006) misst.

**Abruf-URLs:** `https://api.worldbank.org/v2/sources/2/series/NY.GDP.MKTP.KD/metadata?format=json`
und `https://api.worldbank.org/v2/indicator/NY.GDP.MKTP.KD?format=json`.
**Abrufdatum: 2026-09-02.**

**Feld `Source` im Wortlaut:**

> Country official statistics, National Statistical Organizations and/or Central Banks;
> National Accounts data files, Organisation for Economic Co-operation and Development (OECD);
> Staff estimates, World Bank (WB)

(Der Zeilenumbruch steht im Rohtext als JSON-Escape; der Metadaten-Endpunkt gibt dieselben
drei Bestände in einer Zeile mit Semikolon.)

**Begründung — zwei Lieferantengruppen, zwei voneinander unabhängige Gründe.** Das Feld nennt
drei Bestände; die Weltbank selbst ist der dritte und unproblematisch. Die beiden anderen
tragen je einen eigenen Grund, und **jeder allein genügt für `unklar`:**

1. **Die OECD**, namentlich als Lieferant eines Bestandes („National Accounts data files").
   `daten.md` Nr. 8 führt die OECD als **„ungeklaert, nicht einplanen"** — die dort zitierte
   Erlaubnisklausel spricht von „written content", und ob statistische Datenbanken darunter
   fallen, ist offen. Nach der Regel dieser Fabrik gilt eine Quelle ohne Lizenzzitat im
   Wortlaut als ungeprüft, nicht als erlaubt. Das ist dieselbe Lage wie bei Reihe 7 (ILO):
   Der Drittanbieter verweigert nichts, er ist nur nicht geprüft.
2. **Die nationalen Ämter und Notenbanken** der Meldeländer, im ersten Halbsatz genannt
   („Country official statistics, National Statistical Organizations and/or Central Banks").
   Das sind **dieselben Stellen wie bei 2b und 2c**, nur als eine Angabe statt als zwei
   geschrieben, und es gilt derselbe Massstab: `daten.md` hat von den vier Modellländern genau
   ein statistisches Amt geprüft (Destatis, Nr. 5) und **keine einzige Notenbank**. Für die
   Ämter der drei übrigen Länder und für alle vier Notenbanken liegt nichts vor. Die Aufzählung
   der zu prüfenden Stellen steht unter Klärung 4.

**Beide Gründe stehen nebeneinander, keiner ersetzt den anderen.** Wer nur die OECD klärt,
hebt Reihe 1 nicht — Grund 2 bleibt stehen. Das ist der Unterschied zwischen der ersten und
der überarbeiteten Fassung dieser Datei; die frühere Fassung nannte hier nur die OECD, obwohl
die Übersichtstabelle oben beide Gruppen führt.

**Folge nach T26:** T26 kennt drei Fälle, und **keiner davon ist dieser.** Der allgemeine
Satz von T26 gilt weiter — das Programm ändert sich nicht, nur das Manifest —, aber einen
benannten Ersatz gibt es nicht. Einer liegt trotzdem vor, und zwar in der Reihenliste
selbst: Sie führt für Reihe 1 die Quelle **„WDI / PWT"**, und die Penn World Table ist nach
Abschnitt 3 dieses Befundes ohne Drittanbietervorbehalt. Der Wechsel ist keine Kleinigkeit
für die Datenschicht: PWT rechnet in eigenen konstanten Preisen mit eigenem Basisjahr, die
WDI-Reihe in konstanten Preisen 2015 US$. Welches Basisjahr PWT 11.0 trägt, habe ich nicht
gemessen — es gehört zur Deckung (Paket 0006), nicht hierher. **Ein Ersatz, der das
Basisjahr wechselt, ändert die Sollreihe und damit den Massstab von T42.** Wer ihn zieht,
zieht ihn vor dem Einfrieren des Jahrgangs, nicht danach.

**Sollreihen an diesem Code: 4** (BIP je Land, vier Länder). **Prüfgegenstände nach T37: 4**
(„BIP je Land").

---

## Reihe 2 — Wertschöpfungsanteil je Sektor — **unklar, aber aus zwei verschiedenen Gründen**

Drei Codes, und sie zerfallen in zwei Gruppen. Genau das hat der Prüfbefund zu 0005 nicht
sehen können, weil er nur den ersten gemessen hat.

**Abrufdatum für alle drei: 2026-09-02**, je über beide Endpunkte, je zeichengleich.

### 2a — `NV.AGR.TOTL.ZS` („Agriculture, forestry, and fishing, value added (% of GDP)")

`https://api.worldbank.org/v2/sources/2/series/NV.AGR.TOTL.ZS/metadata?format=json`,
gegengelesen gegen `https://api.worldbank.org/v2/indicator/NV.AGR.TOTL.ZS?format=json`.

**Feld `Source` im Wortlaut** — zeichengleich dasselbe wie bei Reihe 1:

> Country official statistics, National Statistical Organizations and/or Central Banks; National Accounts data files, Organisation for Economic Co-operation and Development (OECD); Staff estimates, World Bank (WB)

**Urteil: unklar**, Begründung wie dort und aus **beiden** Gründen: die OECD (`daten.md` Nr. 8,
ungeklärt) **und** die nationalen Ämter/Notenbanken des ersten Halbsatzes (von vier
Modellländern ein Amt geprüft, keine Notenbank). Jeder Grund allein genügt; die Klärung der
OECD allein hebt 2a nicht.

**Folge nach T26:** kein Fall von T26, und **keine Ausweichquelle** — siehe den Abschnitt „Was
Reihe 2 als Ganzes kostet" unten und Befund 4 dieser Datei. Die Reihenliste führt für Reihe 2
allein „WDI"; die PWT liefert keine sektorale Wertschöpfung.

**Sollreihen: 4.**

### 2b und 2c — `NV.IND.TOTL.ZS` und `NV.SRV.TOTL.ZS`

`https://api.worldbank.org/v2/sources/2/series/NV.IND.TOTL.ZS/metadata?format=json` und
`…/NV.SRV.TOTL.ZS/metadata?format=json`, beide gegengelesen gegen den Indikator-Endpunkt.

**Feld `Source` im Wortlaut — bei beiden Codes zeichengleich dasselbe:**

> Country official statistics, National Statistical Offices (NSOs);
> National Accounts data files, Central Banks;
> Staff estimates, World Bank (WB)

**Das ist ein anderer Text als bei 2a.** Die OECD kommt nicht vor; an ihrer Stelle stehen
die Notenbanken, und aus „National Statistical Organizations and/or Central Banks" ist
„National Statistical Offices (NSOs)" geworden. `IndicatorName`: „Industry, including
construction, value added (% of GDP)" beziehungsweise „Services, value added (% of GDP)".

**Urteil: unklar**, und zwar aus einem schwächeren Grund als 2a. Genannt sind keine
Organisationen mit eigenen veröffentlichten Bedingungen, sondern die amtliche Statistik der
Meldeländer. Ob ein Indikator damit im Sinne der Weltbank-Ausnahme „provided by third
parties" ist, sagt das Feld nicht, und `daten.md` hat von den vier Modellländern genau ein
statistisches Amt geprüft: **Destatis, Nr. 5, positiv** („Data licence Germany – attribution –
version 2.0", erlaubt ausdrücklich die Aufnahme in „products and applications"). Für die
Ämter der drei übrigen Länder liegt nichts vor. Ich löse das nicht auf — die Frage, ob eine
nationale Statistikbehörde hier Drittanbieter ist, ist eine Rechtsfrage und gehört dem
Betreiber.

**Folge nach T26:** kein Fall von T26, und **keine Ausweichquelle** — dieselbe Lage wie bei 2a,
ausgeführt im Abschnitt „Was Reihe 2 als Ganzes kostet" unten und in Befund 4 dieser Datei.
Die Zeile gilt für 2b und 2c gemeinsam, weil beide Codes dasselbe `Source`-Feld tragen.

**Sollreihen: 4 + 4 = 8.**

### Was Reihe 2 als Ganzes kostet — und die Rechnung, die naheliegt und nicht aufgeht

**Prüfgegenstände nach T37: 4** („Sektorstruktur je Land"), und T37 sagt dazu: *„die drei
Anteilsreihen des Landes, **alle drei** müssen bestehen"*. **Fällt allein 2a, fallen alle
vier Prüfgegenstände**, obwohl 2b und 2c unberührt blieben. Ein Code entscheidet vier der
sechzehn.

Der naheliegende Ausweg trägt nicht, und weil er naheliegt, steht er hier ausgeschrieben:
Die Reihenliste normiert die drei Anteile auf 10.000 und nennt selbst nur **8 von 12**
Sollreihen unabhängig — je Land sind also zwei der drei Anteile frei, der dritte folgt.
Daraus scheint zu folgen, dass sich der Agraranteil aus 2b und 2c bilden lässt. Er lässt
sich nicht: Die Normierung braucht die Summe der drei **Rohwerte**, und ohne den Rohwert der
Landwirtschaft gibt es sie nicht. Wer stattdessen `100 % − IND − SRV` rechnet, schiebt die
gesamte Differenz zum BIP (Gütersteuern abzüglich Subventionen, statistische Abweichung) in
den kleinsten Sektor. Wie klein der ist, steht schon im Repo:
`pruefung-entwurf-fassung2-2026-08-31.md` misst für ein Modelland **1,0322 %**. Eine
Restgrösse von wenigen Prozentpunkten auf einen Ein-Prozent-Sektor zu buchen, erzeugt keine
Sollreihe, sondern einen Fehler in der Grössenordnung der Reihe selbst.

**Und es gibt für Reihe 2 keine geprüfte Ausweichquelle.** Die Reihenliste führt als Quelle
nur „WDI". Die PWT liefert keine sektorale Wertschöpfung; `daten.md` Lücke 1 hält
ausdrücklich fest, dass feinere Gliederungen nur bei OECD (ungeklärt) und Eurostat (für die
Nicht-EU-Länder des Modells gesperrt) liegen. Reihe 2 ist damit die einzige der sieben
unklaren Reihen ohne zweiten Weg.

---

## Reihe 5 — Bevölkerung — **unklar**

**Indikatorcode:** `SP.POP.TOTL` („Population, total"), von mir gewählt, siehe Befund 3.

**Abruf-URLs:** `https://api.worldbank.org/v2/sources/2/series/SP.POP.TOTL/metadata?format=json`
und `https://api.worldbank.org/v2/indicator/SP.POP.TOTL?format=json`. **Abrufdatum:
2026-09-02**, zeichengleich.

**Feld `Source` im Wortlaut:**

> World Population Prospects, United Nations (UN), uri: https://population.un.org/wpp/, publisher: UN Population Division; Statistical databases and publications from national statistical offices, National Statistical Offices (NSOs), uri: https://unstats.un.org/home/nso_sites/, publisher: National Statistical Offices; Eurostat: Demographic Statistics, Eurostat (ESTAT), uri: https://ec.europa.eu/eurostat/data/database?node_code=earn_ses_monthly, publisher: Eurostat; Population and Vital Statistics Report (various years), United Nations (UN), uri: https://unstats.un.org, publisher: UN Statistics Division

**Begründung:** Vier fremde Bestände, jeder mit `uri` und `publisher` ausgewiesen — die
Weltbank markiert sie deutlicher als Fremdbestände als bei jeder anderen hier gemessenen
Reihe. Einer davon ist **Eurostat**, und `daten.md` Nr. 7 hat dessen Bedingungen im Wortlaut
gelesen: Von der gewerblichen Weiterverwendung ausgenommen sind unter anderem „Daten fuer
Nicht-EU/EFTA-Laender (die Seite nennt USA, Japan und China als Beispiele)" — also drei der
vier Modellländer. Ob Eurostat für diese Länder überhaupt etwas beigesteuert hat, ist die
entscheidende Frage, und **sie ist aus dem Feld nicht zu beantworten: `Source` nennt eine
Menge, keine Zuordnung.** Welcher Lieferant welchen Land-Jahr-Wert getragen hat, steht
nirgends. Das gilt für alle zusammengesetzten Reihen dieses Befundes und ist der Grund,
warum keines der Urteile schärfer ausfallen kann als `unklar`.

**Folge nach T26:** kein Fall von T26. Ersatz nach Reihenliste: **PWT** („WDI / PWT"), ohne
Drittanbietervorbehalt und bei einer Personenzahl ohne Basisjahrfrage — hier also billiger
als bei Reihe 1.

**Sollreihen: 0** (exogener Pfad). **Prüfgegenstände: 0.** Die Reihe ist trotzdem nicht
folgenlos — sie ist Startwert **und** Pfad für 4 + RW, und der Weltlauf braucht sie in jedem
Jahr.

---

## Reihe 6 — Erwerbstätige — **unklar, wie Reihe 7 und aus demselben Grund**

**Indikatorcode:** `SL.TLF.TOTL.IN` („Labor force, total"), von mir gewählt, siehe Befund 3.

**Abruf-URLs:** `https://api.worldbank.org/v2/sources/2/series/SL.TLF.TOTL.IN/metadata?format=json`
und `https://api.worldbank.org/v2/indicator/SL.TLF.TOTL.IN?format=json`. **Abrufdatum:
2026-09-02**, zeichengleich.

**Feld `Source` im Wortlaut:**

> International Labour Organization (ILO), type: estimates based on external database;
> United Nations (UN), publisher: UN Population Division;
> Staff estimates, World Bank (WB)

**Begründung:** Derselbe Drittanbieter wie Reihe 7, dieselbe Lage, dasselbe Urteil. Die ILO
steht nicht unter den in `daten.md` geprüften Quellen; sie gewährt ihren Datenbanken seit
dem 2023-05-03 im Wortlaut CC BY 4.0, mit dem Vorbehalt aus Abschnitt 4 dieses Befundes.
Beide Lesarten stehen in `lizenzbefund-wdi.md` unter Reihe 7; ich wähle auch hier keine.

**Ein Unterschied zu Reihe 7, der die Sache nicht besser macht:** Reihe 7 trägt
`type: external database` **mit** `uri` und `date accessed: January 17, 2026`. Reihe 6 trägt
`type: estimates based on external database` **ohne** beides. Es gibt hier also nicht einmal
ein Abrufdatum, an dem sich die Stichtagsfrage aus Abschnitt 4 überhaupt aufhängen liesse.

**Gegenprobe mit dem zweiten in Frage kommenden Code:** `SL.EMP.TOTL.SP.ZS`
(„Employment to population ratio, 15+, total (%) (modeled ILO estimate)", abgerufen
2026-09-02 über den Metadaten-Endpunkt) nennt

> ILO Modelled Estimates database (ILOEST), International Labour Organization (ILO), uri: https://ilostat.ilo.org/data/bulk/, publisher: ILOSTAT, type: external database, date accessed: January 17, 2026

also wortgleich das Feld der Reihe 7. **Welchen der beiden Codes der Architekt meint, ändert
das Urteil nicht** — beide Wege zur Erwerbstätigenzahl führen über die ILO.

**Folge nach T26:** kein Fall von T26. Ersatz nach Reihenliste: **PWT** („WDI / PWT"); die
Penn World Table führt Beschäftigte als `emp`. `Referenceperiod` von `SL.TLF.TOTL.IN` ist
`1990-2025` — die kürzeste aller hier gemessenen Reihen und die einzige, die nicht bis 1960
zurückreicht. Das ist eine Aussage über die Reihenlänge, nicht über Lücken je Land, und
gehört zu Paket 0006.

**Sollreihen: 0** (exogener Pfad). **Prüfgegenstände: 0.**

---

## 2. Das Feld `Source` unterscheidet — anders als `License_Type`

Alle sechs hier gemessenen Codes tragen `CC BY-4.0` und dieselbe `License_URL`. Das Feld
`License_Type` bleibt damit so wertlos, wie `lizenzbefund-wdi.md` es an sieben und der
Prüfbefund es an acht Reihen gezeigt hat.

**Die Gegenprobe, die dieses Paket schuldet**, betrifft das Feld `Source` selbst: Wenn *jede*
Reihe irgendwelche fremden Stellen nennt, unterscheidet auch dieses Feld nichts, und dann
sind die sechs Urteile oben ein Artefakt der Schreibweise. Kontrollabruf am 2026-09-02 auf
eine Reihe, die die Weltbank vollständig selbst erhebt — `IQ.CPA.ECON.XQ` („CPIA economic
management cluster average"):

> CPIA database, World Bank Group (WBG), uri: https://datacatalog.worldbank.org/int/search/dataset/0038988

**Ein Lieferant, und es ist die Weltbank selbst.** Das Feld *kann* ausdrücken, dass kein
Fremdbestand beteiligt ist. Wo es eine OECD, eine ILO, ein Eurostat nennt, ist das eine
Aussage und keine Formelzeile. `License_Type` sagt auch hier `CC BY-4.0`.

**Was der Marker `type: external database` nicht kann:** Er sieht aus wie das trennscharfe
Merkmal, trennt aber nicht frei von gesperrt — **Reihe 13, die einzige gesperrte Reihe des
Vorhabens, trägt ihn nicht.** Ein Marker, der beim härtesten Fall fehlt, taugt nicht als
Filter.

---

## 3. Die vier Nicht-WDI-Quellen — enthält ihre Lizenz einen Drittanbietervorbehalt?

Gefragt ist nicht die Erlaubnis im Ganzen (die steht in `daten.md`), sondern genau ein Satz:
ein Vorbehalt für fremde Inhalte, wie ihn die Weltbank führt („Some datasets and indicators
are provided by third parties, and may not be redistributed or reused without the consent of
the original data provider", `daten.md` Nr. 1).

### Penn World Table 11.0 — Reihen 3, 4, 15 — **kein Vorbehalt**

`daten.md` Nr. 4 zitiert nur die Lizenzzeile und schweigt zur Frage; deshalb **ein** eigener
Abruf: `https://www.rug.nl/ggdc/productivity/pwt/`, **2026-09-02**. Die Seite nennt

> Penn World Table 11.0 by Robert C. Feenstra, Robert Inklaar and Marcel P. Timmer is licensed under a Creative Commons Attribution 4.0 International License.

und die vorgeschriebene Zitierung. **Ein Satz über fremde Inhalte, fremdes Urheberrecht oder
abweichende Bedingungen für Teile des Datensatzes steht dort nicht.** Festgehalten als
Abwesenheit, nicht als Zusicherung: Die PWT ist ihrer Bauart nach aus nationalen
Volkswirtschaftlichen Gesamtrechnungen und Preiserhebungen gerechnet, sie sagt darüber nur
nichts.

**Urteil: frei.** Sollreihen: 0 (Reihen 3, 4, 15 sind Startwerte, Reihe 4 nach T25 nur
Start). Prüfgegenstände: 0. Auflage aus der Lizenz, unverändert aus `daten.md`: Namensnennung
samt der Feenstra-Inklaar-Timmer-Angabe im Wortlaut und Kennzeichnung der Änderungen.

### CEPII BACI — Reihe 14 — **das Gegenteil eines Vorbehalts**

`daten.md` Nr. 3 zitiert die Lizenzbezeichnung (Etalab Open Licence 2.0), nicht den
Lizenztext; deshalb ein Abruf auf den Lizenztext selbst
(`https://raw.githubusercontent.com/etalab/licence-ouverte/master/LO.md`, amtliches
Etalab-Verzeichnis, **2026-09-02**). Abschnitt *Droits de propriété intellectuelle*, im
Wortlaut:

> Il est garanti au « Réutilisateur » que l'« Information » ne contient pas de « Droits de propriété intellectuelle » appartenant à des tiers qui pourraient faire obstacle aux libertés qui lui sont accordées par la présente licence.

> Les éventuels « Droits de propriété intellectuelle » détenus par le « Concédant » sur l'« Information » ne font pas obstacle aux libertés qui sont accordées par la présente licence.

(Der Text liegt dort nur französisch vor; die Lizenz ist nach ihrem eigenen Schlussabschnitt
dem französischen Recht unterstellt: *„La présente licence est régie par le droit
français."*)

**Das ist die Umkehrung der Weltbank-Klausel.** Wo die Weltbank ihre Sammlung ausdrücklich
unter Vorbehalt fremder Rechte stellt, sichert Etalab dem Weiterverwender zu, dass keine
solchen Rechte im Weg stehen. Zusammen mit dem in `daten.md` Nr. 3 belegten
Comtrade-Satz zu transformierten Beständen ist Reihe 14 die einzige Reihe des Vorhabens, bei
der die Frage dieses Pakets nicht nur unbeantwortet, sondern **gegenteilig beantwortet** ist.

**Urteil: frei.** Sollreihen: 0 der 31 (der Handelsblock zählt getrennt).
**Prüfgegenstände: 1** — und nach Abschnitt 5 der einzige gesicherte. Auflage: „BACI und das
CEPII nennen, moeglichst mit Link auf die Webseite" (`daten.md` Nr. 3).

### IWF — Reihen 9, 11, 12 — **ein Vorbehalt ist da, und er ist nicht wörtlich zu belegen**

`daten.md` Nr. 2 zitiert die Erlaubnis und drei Auflagen, aber keinen Vorbehalt für fremde
Inhalte — die Frage ist dort offen. `imf.org/en/about/copyright-and-terms` hat den direkten
Abruf am 2026-08-31 (Datenkurator), am 2026-09-01 (Paket 0005), am 2026-09-02 (Daten-Prüfer)
und heute erneut mit **HTTP 403** abgewiesen. Ein Ausweichhost wurde versucht und trägt
nicht: `imfconnect.org/content/compactwithafrica/home/CopyrightandUsage.html` führt die
Bedingungen einer anderen Webseite („Users are authorized to download and/or reprint files
from the CWA Website for personal (noncommercial) use") und **nicht** den Datenabschnitt.

Was eine Wortlaut-Suche am 2026-09-02 aus derselben Seite anführt:

> The term "Data" refers to any published statistical data produced by the IMF that is not owned by a third-party.

**Wenn dieser Satz so dort steht, ist er der stillere Vorbehalt von beiden.** Die Weltbank
erlaubt und nimmt Fremdbestände aus; der IWF nimmt sie aus dem Begriff heraus, für den die
Erlaubnis überhaupt erst gilt — „Users may download … and sell **Data**". Wer nur den
Erlaubnissatz liest, sieht den Vorbehalt nicht.

**Und er ist genau so belegt, wie die Fabrik es nicht gelten lässt** — aus einem Suchauszug,
nicht aus dem Volltext. `notizen/lehren.md` (2026-08-29) hat „Beleg aus dem Suchauszug
genügt" ausdrücklich verworfen; `daten.md` selbst schreibt zum IWF „vor dem Bau im Volltext
nachzulesen".

**Urteil: unklar** für die Reihen 9, 11 und 12 — nicht, weil ein Drittanbieter etwas
verweigert, sondern weil der Lizenztext, auf dem alles ruht, nach fünf Anläufen aus drei
Rollen ungelesen bleibt. **Sollreihen: 4 (Reihe 9) + 4 (Reihe 11) = 8.** Reihe 12 trägt
keine.

**Folge nach T26:** kein Fall von T26, und **keine Ausweichquelle** für keine der drei. Die
Reihenliste führt als Quelle für Reihe 9 allein „IWF IFS", für die Reihen 11 und 12 allein
„IWF WEO" — anders als bei den Reihen 1, 5 und 6 steht dort kein zweiter Weg. Reihe 10
(„IWF IFS / WDI") hat einen, gehört aber zu Paket 0005 und trägt hier kein Urteil.

**Was das für Paket 0005 bedeutet, ohne dass ich es aufhebe:** Die Urteile `frei` zu den
Reihen 8 und 10 stützen sich auf dieselbe IWF-Erlaubnis. Der Befund hat das selbst als
„schwächsten Punkt" benannt; dieses Paket gibt dem Punkt einen Namen. Ich rechne die beiden
Reihen unten in der Zusammenfassung weiter als `frei`, weil sie nicht mein Paket sind — die
Gegenrechnung steht daneben.

---

## 4. Die ILO-Stichtagsfrage: aus dem Wortlaut nicht zu beantworten

Aus Befund 2 des Prüflaufs zu 0005. Abruf `https://www.ilo.org/rights-and-permissions`,
**2026-09-02**, direkter Seitenabruf. Die beiden Sätze stehen dort so:

> As of 3 May 2023, databases and datasets together with the accompanying referential metadata are covered by the Creative Commons CC BY 4.0 licence.

> Databases and datasets together with the accompanying referential metadata produced prior to 3 May 2023 do not automatically benefit from a Creative Commons licence.

**Welches Datum meint „produced"?** Die Seite sagt es nicht. Gesucht und **nicht gefunden**:
eine Begriffsbestimmung von „produced", eine Aussage darüber, ob eine fortlaufend
aktualisierte Datenbank mit jeder Ausgabe neu „produced" wird, und eine Aussage darüber,
welche Ausgabe eines Bestandes gedeckt ist. Es gibt keinen dieser Sätze.

**Damit ist die Frage aus dem Wortlaut nicht zu beantworten**, und die Gleichsetzung im
Befund zu 0005 („der Weltbank-Eintrag weist als Abrufstand den 2026-01-17 aus, liegt also
nach dem Stichtag") trägt nicht: `date accessed` ist der Tag, an dem die **Weltbank** den
Bestand geholt hat, und über den Tag, an dem die **ILO** ihn erzeugt hat, sagt er nichts.
Beide Lesarten bleiben offen — (a) jede Jahresausgabe ist eine eigene Erzeugung, dann ist die
im Januar 2026 geholte Ausgabe nach dem Stichtag erzeugt; (b) ILOEST als Datenbank besteht
seit weit vor 2023, dann nicht.

**Betroffen sind Reihe 6 und Reihe 7 gleichermassen**, und Reihe 6 sogar schärfer: Ihr Feld
`Source` nennt kein `date accessed`, also fehlt dort selbst das Datum, mit dem sich Lesart
(a) belegen liesse.

**Für den Zusatzauftrag an den Datenkurator**, den `lizenzbefund-wdi.md` vorschlägt: Er muss
diese Frage mitstellen, sonst kommt er mit derselben Zweideutigkeit zurück. Sie ist an die
ILO gerichtet und nicht aus einem Abruf zu beantworten.

---

## 5. Zusammenfassung

**Die drei Zeilen, die der Auftrag verlangt** — 31 Sollreihen, nach dieser Prüfung und unter
Fortschreibung der Urteile aus Paket 0005:

- **frei: 7** — Reihe 8 (Verbraucherpreise, 4) und Reihe 10 (Wechselkurs, 3), beide aus 0005.
- **unklar: 24** — Reihe 1 (4), Reihe 2 (12), Reihe 9 (4), Reihe 11 (4).
- **gesperrt: 0** — kein zweiter Fall wie Reihe 13.

**Die Gegenrechnung, weil eine Zahl ohne ihre Annahme nichts wert ist:** Die sieben freien
Sollreihen hängen an der IWF-Erlaubnis, deren Volltext niemand lesen konnte und in deren
Definitionssatz nach Abschnitt 3 ein Vorbehalt steht. Nimmt man die Regel „Suchauszug genügt
nicht" auch dort ernst, lautet die Zeile **frei: 0, unklar: 31, gesperrt: 0**. Der
Unterschied zwischen beiden Zeilen ist ein einziger Seitenabruf, den drei Rollen an vier
Tagen nicht geschafft haben.

**Und die Zahl, an der T37 hängt.** Der Rückvergleich hat 16 Prüfgegenstände; sie verteilen
sich so auf die Reihen:

| Prüfgegenstand | Zahl | Reihe | Urteil |
|---|---:|---|---|
| BIP je Land | 4 | 1 | unklar |
| Sektorstruktur je Land | 4 | 2 (alle drei Anteile) | unklar |
| Verbraucherpreise je Land | 4 | 8 | frei (0005, IWF-gestützt) |
| Wechselkurs je Land ausser USA | 3 | 10 | frei (0005, IWF-gestützt) |
| Handelsblock | 1 | 14 | **frei, Lizenz im Volltext gelesen** |

Die Reihen 9 und 11 kosten **keinen** Prüfgegenstand: T37 führt sie als `gesetzt`
beziehungsweise `abgeleitet`, sie werden berichtet und entscheiden nichts. Ihre acht
Sollreihen sind für die Abnahme ohne Gewicht.

- Fallen die unklaren WDI-Reihen 1 und 2: **8 von 16** bleiben. Eine Abnahme, die von
  sechzehn Gegenständen zwei reissen lässt, lässt dann von acht zwei reissen — dieselbe
  Toleranz auf der halben Menge, also ein anderer Test. Ob 16 auf 8 fallen darf, entscheidet
  nicht diese Rolle.
- Fällt zusätzlich die IWF-Kette: **1 von 16** bleibt, der Handelsblock.

**Der Handelsblock ist der einzige der sechzehn Prüfgegenstände, dessen Lizenzkette
vollständig im Volltext gelesen ist** — Etalab 2.0 mit Zusicherung statt Vorbehalt,
Comtrade-Transformationsklausel darüber. Das ist die stabilste Stelle des
Rückvergleichs, und sie ist zugleich die einzige, die als Einzelgegenstand zählt.

---

## Was zu tun bleibt, für den, der die Zahlen bewegen will

Keine Empfehlung, nur die Preise. Vier Klärungen — die Nummern sind die aus der ersten Fassung
und bleiben stehen, damit Verweise darauf tragen. Die Reihenfolge ist **nicht** mehr die nach
Kosten: So gelesen, kauft man den billigsten Schritt und bekommt null.

**Der Satz, der über der Liste steht: Kein einzelner der vier Schritte hebt auch nur einen
Prüfgegenstand.** Jede Reihe, an der ein Prüfgegenstand hängt, hat mehr als einen Sperrgrund.
Wer einen Gegenstand zurückwill, kauft mindestens ein Paar.

**Nach Wirkung geordnet:** das Paar 1 + 4 zuerst (8 Prüfgegenstände), dann 2 (sichert 7),
dann 3 (0).

### Das Paar: Klärung 1 **und** Klärung 4 — nur zusammen tragen sie

**Klärung 1 — OECD im Volltext** (`daten.md` Nr. 8, 403 am 2026-08-31).
**Allein: 0 Sollreihen, 0 Prüfgegenstände.** Sie hebt bei Reihe 1 und 2a nur die
OECD-Hälfte; der zweite Sperrgrund dieser beiden Codes — die nationalen Ämter und
Notenbanken des ersten Halbsatzes — bleibt unberührt stehen. Auf 2b und 2c wirkt sie gar
nicht: Deren `Source`-Feld nennt die OECD nicht.

**Klärung 4 — die nationalen Ämter *und* die Notenbanken der vier Modellländer**
(Aufzählung unten). **Allein: 8 Sollreihen (2b und 2c), 0 Prüfgegenstände.** Sie ist die
zweite Hälfte auch für Reihe 1 und 2a, nicht nur für 2b und 2c — bei 2b und 2c ist sie der
einzige Sperrgrund, bei Reihe 1 und 2a der zweite neben der OECD. Prüfgegenstände hebt sie
allein trotzdem keinen: Nach T37 müssen bei der Sektorstruktur **alle drei** Anteilsreihen
bestehen, und 2a bliebe an der OECD hängen.

**Zusammen: 16 Sollreihen und 8 Prüfgegenstände.** Die Rechnung, Posten für Posten:

| gehoben | Sollreihen | Prüfgegenstände |
|---|---:|---:|
| Reihe 1 und 2a (braucht 1 **und** 4) | 4 + 4 = 8 | 4 — die BIP-Gegenstände, aus Reihe 1 |
| Reihe 2b und 2c (braucht 4) | 4 + 4 = 8 | 4 — die Sektorstruktur-Gegenstände, erst wenn 2a, 2b **und** 2c frei sind |
| **Summe** | **16** | **8** |

Die vier BIP-Gegenstände hängen damit an derselben Doppelbedingung wie die vier
Sektorstruktur-Gegenstände. Die erste Fassung dieser Datei hat die Doppelbedingung nur bei
der Sektorstruktur aufgeschrieben und Klärung 1 die vier BIP-Gegenstände allein zugeschrieben;
das war falsch.

**Welche Stellen Klärung 4 tatsächlich meint.** Das Feld `Source` nennt zwei Lieferantenarten
nebeneinander („Country official statistics, National Statistical Organizations and/or Central
Banks" bei Reihe 1 und 2a; „National Statistical Offices (NSOs)" **und** „National Accounts
data files, Central Banks" als zwei getrennte Angaben bei 2b und 2c). Die Notenbanken sind
also ein eigener Lieferant und nicht von den Ämtern mit abgedeckt. Für die vier Modellländer
aus `spiel.md` (USA, China, Deutschland, Brasilien) sind das acht Stellen, von denen `daten.md`
**eine** geprüft hat:

| Land | statistisches Amt | Notenbank |
|---|---|---|
| Deutschland | Destatis — **geprüft**, `daten.md` Nr. 5, positiv | Deutsche Bundesbank — ungeprüft |
| USA | Bureau of Economic Analysis (BEA) — ungeprüft | Federal Reserve Board — ungeprüft |
| China | National Bureau of Statistics of China (NBS) — ungeprüft | People's Bank of China — ungeprüft |
| Brasilien | Instituto Brasileiro de Geografia e Estatística (IBGE) — ungeprüft | Banco Central do Brasil — ungeprüft |

**Sieben Abrufe, nicht drei.** Die erste Fassung nannte nur „die Statistikämter der drei
Nicht-EU-Modellländer" und ließ die vier Notenbanken samt der Bundesbank aus, die Destatis
nicht mit abdeckt.

**Zwei Einschränkungen zu dieser Tabelle, damit niemand mehr hineinliest, als drinsteht.**
Erstens ist die Zuordnung Land → Stelle **von mir benannt und nicht gemessen**: `Source`
nennt eine Menge von Lieferantenarten, keine Zuordnung, und welche Stelle welchen
Land-Jahr-Wert getragen hat, steht nirgends — dieselbe Grenze wie bei Reihe 5. Für die USA
ist die Wahl zudem nicht eindeutig, weil die Volkswirtschaftliche Gesamtrechnung dort beim
BEA liegt und nicht bei einem zentralen Statistikamt. Zweitens klärt ein positiver Befund je
Stelle die Frage nur, wenn zuvor entschieden ist, **ob eine nationale Statistikbehörde im
Sinne der Weltbank-Ausnahme überhaupt Drittanbieter ist**. Das ist eine Rechtsfrage und
gehört dem Betreiber; fällt sie mit „nein", entfällt Klärung 4 ersatzlos und Klärung 1 hebt
Reihe 1 und 2a doch allein.

### Die übrigen zwei

**Klärung 2 — IWF im Volltext** (403 an vier Tagen).
**Allein: hebt 8 Sollreihen (Reihe 9 und 11), 0 Prüfgegenstände** — T37 führt beide als
`gesetzt` beziehungsweise `abgeleitet`, sie entscheiden nichts. Der eigentliche Wert liegt
woanders und ist kein Heben, sondern ein Sichern: An demselben Text hängen die schon als
`frei` gezählten 7 Sollreihen und **7 Prüfgegenstände** der Reihen 8 und 10. Fällt er,
fallen sie — das ist die Zeile „1 von 16" in Abschnitt 5. Zusammen entscheidet der Abruf
also 15 Sollreihen und 7 Prüfgegenstände, er *gewinnt* aber keinen.

**Klärung 3 — ILO in die geprüften Quellen aufnehmen, samt der Stichtagsfrage aus
Abschnitt 4.** **Allein: 0 Sollreihen, 0 Prüfgegenstände.** Hebt Reihe 6 und Reihe 7 und gibt
den Startwerten beider Reihen ihren Datenanker zurück; keine der beiden trägt eine Sollreihe.

**Und die Probe auf die Zahlen.** 16 gehobene Sollreihen (1 + 4) plus 8 (Klärung 2) = 24 —
genau die 24 unklaren aus dem Frontmatter. Prüfgegenstände: 8 gehoben (1 + 4) plus 7 gesichert
(Klärung 2) plus der Handelsblock, der schon steht = 16.

**Was dieser Befund nicht ist:** kein Rechtsrat. Er zitiert, was die Weltbank, die Penn World
Table, Etalab und die ILO über sich selbst sagen, und hält beim IWF fest, dass sich nichts
zitieren liess. Ob das für die Einbettung in ein verkauftes Spiel genügt, entscheidet der
Betreiber.

**Was dieser Befund nicht getan hat:** Es wurde nichts heruntergeladen und nichts
eingebettet. Diese Datei ist das einzige Erzeugnis des Pakets. Die Reihenliste in
`technik.md` ist unverändert.

---

# Befund 1 — an den Architekten: die Spalte „Verdacht" ist bei sechs von sechs falsch

Nicht Aufgabe dieses Pakets, sie zu ändern, aber der Umfang steht jetzt fest. Alle sechs
gemessenen Codes, die die Spalte mit „nein" führt, nennen einen Bestand ausserhalb der
Weltbank. Zusammen mit den vier Reihen aus 0005 ist damit **keine einzige** der geprüften
WDI-Reihen ohne Fremdbestand — und die Kontrolle `IQ.CPA.ECON.XQ` zeigt, dass es solche
Reihen gibt, nur eben keine, die dieses Modell braucht. Die Spalte trennt nichts und sollte
entweder gemessene Werte tragen oder verschwinden.

# Befund 2 — an den Architekten: Reihe 2 zerfällt in zwei Gruppen, die Reihenliste führt sie als eine

`NV.AGR.TOTL.ZS` nennt die OECD, `NV.IND.TOTL.ZS` und `NV.SRV.TOTL.ZS` nicht. Die Zeile
„Start + Soll (12, frei, 8 unabhängig)" fasst damit zwei verschiedene Lizenzlagen zusammen.
Für T37 ist das folgenlos — die Alle-drei-Bedingung macht die Gruppe ohnehin unteilbar —,
für die Klärungskosten nicht: Es hängt eine einzige Frage an der OECD, nicht drei.

**Nachgetragen am 2026-09-02 (Paket 0018), damit die falsche Zelle geändert wird:** Die
Lizenzlage trägt in der Reihenliste die Spalte **„Verdacht"**, nicht die Spalte „Rolle". Das
`frei` in „Start + Soll (12, frei, 8 unabhängig)" ist die **T37-Klasse** — T37 kennt genau die
drei Klassen `frei`, `gesetzt` und `abgeleitet` und vergibt sie zeilenweise (Reihe 9
`gesetzt`, Reihe 11 `abgeleitet`, die Reihen 1, 2, 8, 10 `frei`, mit den „8 unabhängig" aus
T37s „19 unabhängig"). Wer dieses `frei` streicht oder differenziert, zerschiesst die
Verbindung zwischen Reihenliste und T37 und lässt die Spalte, die wirklich falsch ist,
unberührt. Die Sache selbst — Reihe 2 zerfällt lizenzseitig in zwei Gruppen — bleibt richtig
und belegt; sie gehört in die Spalte „Verdacht", die Befund 1 dieser Datei ohnehin trifft.

# Befund 3 — an den Architekten: die Reihenliste nennt Codes nur für Reihe 2

Zu den Reihen 1, 5, 6, 8, 10 und 13 haben zwei Pakete die Indikatorcodes selbst suchen
müssen; für 5 und 6 sind sie bis heute nirgends im Repo festgeschrieben. Ich habe
`SP.POP.TOTL` und `SL.TLF.TOTL.IN` gewählt. **Bei Reihe 6 ist die Wahl nicht eindeutig:**
Die Reihenliste sagt „Erwerbstätige", `SL.TLF.TOTL.IN` heisst „Labor force, total" und
umfasst Erwerbstätige **und** Erwerbslose. Der Code, der Erwerbstätige liefert, wäre
`SL.EMP.TOTL.SP.ZS` mal Bevölkerung — eine andere Grösse und eine andere Rechnung. Für das
Lizenzurteil ist es gleich (beide ILO), für den Jahrgangsbau nicht. Ein Code je Reihe in der
Reihenliste würde beide Fragen schliessen.

# Befund 4 — an den Projektmanager: T26 deckt vier der sieben unklaren Reihen nicht ab

T26 nennt drei Fälle: Zoll (Reihe 13), sektorale Beschäftigung (Reihe 7) und die
Handelsmatrix vor 1995. Für die Reihen 1, 2, 5, 6 gibt es keinen Eintrag. Der allgemeine
Satz von T26 gilt weiter — das Programm ändert sich nicht, nur das Manifest —, aber welches
Modellkonstrukt an die Stelle tritt, steht nirgends. Für 1, 5 und 6 nennt die Reihenliste
selbst mit PWT eine geprüfte Ausweichquelle, **für Reihe 2 gibt es keine**, und Reihe 2
trägt vier der sechzehn Prüfgegenstände. Das ist die Zeile, die T26 fehlt.

# Befund 5 — an den Projektmanager: der IWF-Volltext ist jetzt fünfmal gescheitert

2026-08-31 (Datenkurator), 2026-09-01 (Paket 0005), 2026-09-02 (Daten-Prüfer), heute zweimal
— einmal direkt, einmal über einen Ausweichhost, der die falschen Bedingungen führt. An
diesem Text hängen 15 der 31 Sollreihen und 7 der 16 Prüfgegenstände, und der Suchauszug
deutet auf einen Vorbehalt hin, den `daten.md` nicht kennt. Das ist keine Aufgabe für einen
weiteren Abruf, sondern für ein anderes Netz oder den Betreiber.
