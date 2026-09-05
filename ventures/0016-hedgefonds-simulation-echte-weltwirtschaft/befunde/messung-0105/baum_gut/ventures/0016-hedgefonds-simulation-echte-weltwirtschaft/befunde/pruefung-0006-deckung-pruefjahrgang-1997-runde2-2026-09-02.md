---
typ: pruefung
paket: 0006-deckung-pruefjahrgang-1997
pruefer: daten-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Die Klassifikation 26 tragen / 3 verkuerzt / 2 leer wurde Klasse fuer Klasse aus den Abschnittstabellen nachgezaehlt und die vier bisher ungemessenen Zeilen (Reihe 11 BRA/CHN/DEU, Reihe 9 BRA) an api.imf.org unabhaengig nachgerufen; R = 19 und die zwei erzwingenden Reihen sind unveraendert.
befunde: 1
---

# Zweite Runde: der Zusammenzug stimmt jetzt, und er stimmt nachgemessen

Geprüft ist `daten/deckungsbefund-1997.md` (399 Zeilen, Stand `ueberarbeitet: 2026-09-02`)
gegen das Abnahmekriterium des Pakets. Der Rücklauf 1 vom 2026-09-02 hatte genau eine
Sache offen: Der Zusammenzug zählte 27 tragende Sollreihen, die Abschnittstabellen ergaben
26, und Reihe 11 BRA wurde dadurch von derselben Datei zweimal widersprüchlich beantwortet.

## 1. Zählt der Zusammenzug jetzt richtig? — ja, Klasse für Klasse nachgezählt

Nicht die Summe geprüft (`26 + 3 + 2 = 31` geht genauso auf wie `27 + 2 + 2 = 31`, das war
der Fehler der ersten Runde), sondern **jede Klasse einzeln aus den Abschnittstabellen**:

| Reihe | Sollreihen | Zeilen mit 25 Stützstellen | Zeilen darunter | Fundstelle |
|---|---:|---|---|---|
| 1 BIP | 4 | USA, CHN, DEU, BRA = **4** | — | Z. 94–97 |
| 2 Sektoranteile | 12 | 3 × 4 Zellen, alle 25 = **12** | — | Z. 111–113 |
| 8 Verbraucherpreise | 4 | USA, CHN, DEU, BRA = **4** | — | Z. 129–132 |
| 9 Leitzins | 4 | BRA (25) = **1** | USA 24; DEU 0; CHN 0 | Z. 167–170 |
| 10 Wechselkurs | 3 | CHN, DEU, BRA = **3** | — | Z. 225–227 |
| 11 Staatsschuld | 4 | CHN (25), DEU (25) = **2** | USA 21; BRA 22 | Z. 266–269 |
| **Summe** | **31** | **26** | 3 verkürzt, 2 leer | |

Das ist der Wert, der jetzt in Zeile 16, Zeile 350 und Zeile 353 steht. `grep` über die
ganze Datei nach `27` findet nur noch zwei Treffer mit anderer Bedeutung — Zeile 57
(„dann 27 Sollreihen", also 31 − 4 nach Streichung von Reihe 9) und Zeile 63 (`R = 27` in
der Gegenprobe zur Schranke). **Kein stehengebliebener Altwert.**

Die Zuordnung der drei verkürzten (Z. 20–24) deckt sich mit den Tabellen, und der Satz,
weshalb Reihe 11 BRA R nicht erzwingt (Beginn 2000 liegt vor dem bindenden Startjahr
2001), ist rechnerisch richtig.

## 2. Die vier Zeilen, die die Zählung tragen — unabhängig nachgerufen

Der Rücklauf drehte sich um Zeilen, die in Runde 1 **nicht** gemessen waren: Runde 1 hat
Reihe 11 USA und Reihe 9 USA/DEU/CHN geprüft, weil daran R hängt. Die neue Zahl 26 hängt
aber an den vier anderen. Deshalb diesmal je Land einzeln abgerufen, Wertezahl gegen
Zeitraumlänge (das Verfahren, das die Datei in Z. 274–282 selbst als das belastbare
benennt), alle am **2026-09-02** über
`api.imf.org/external/sdmx/3.0/data/dataflow/<Agentur>/<Fluss>/9.0.0/<Land>.<Indikator>.A`:

| Abruf | gemessen | Werte / Jahre | Stützstellen 1997–2021 | Datei sagt | Urteil |
|---|---|---|---:|---:|---|
| `IMF.RES/WEO/…/BRA.GGXWDG_NGDP.A` | 2000–2031 | 32 / 32 → lückenlos | **22** | 22 | **gleich** |
| `IMF.RES/WEO/…/CHN.GGXWDG_NGDP.A` | 1995–2031 | 37 / 37 → lückenlos | **25** | 25 | **gleich** |
| `IMF.RES/WEO/…/DEU.GGXWDG_NGDP.A` | 1991–2031 | 41 / 41 → lückenlos | **25** | 25 | **gleich** |
| `IMF.STA/MFS_IR/…/BRA.DISR_RT_PT_A_PT.A` | 1997–2025 | 29 / 29 → lückenlos | **25** | 25 | **gleich** |

Vier von vier ziffernweise identisch, und die Wertezahl deckt in allen vier Fällen die
volle Zeitraumlänge — es gibt also auch keine Innenlücke, die eine Randjahresangabe
verstecken könnte. Damit sind alle acht Zeilen der beiden reißenden Reihen an fremden
Endpunkten gemessen (vier in Runde 1, vier jetzt).

**Folge für R:** Reihe 11 BRA beginnt 2000, nicht 2001 oder später — die Zeile bindet
also tatsächlich nicht. **R bleibt 19**, Fenster 2001–2020, erzwungen von Reihe 11 USA
(Beginn 2001) und Reihe 9 USA (Ende 2020). Frontmatter (`R: 19`, `erzwungen_von`),
Abschnitt „Der eine Wert für R" und die Variantentabelle sind untereinander widerspruchsfrei;
die Nachrechnung `25 − 4 − 1 = 20`, `R = 20 − 1 = 19` stimmt, ebenso die drei Zeilen der
Variantentabelle (20 / 19 / 24) und die Gegenprobe zu `R ≤ 26` (23.000 / 24.000 / 28.000
gegen 31.000, alle disjunkt).

## 3. Die beiden neuen Einheitenabsätze — nachgeprüft, beide richtig

Gegen die Reihenliste `technik.md` Abschnitt 7 (Z. 990–1006), Spalte „Modelleinheit":

- **Reihe 9** verlangt `bp` (Z. 1000). Quelle `DISR_RT_PT_A_PT` liefert Prozent p. a.
  → Faktor **100**. Richtig.
- **Reihe 11** verlangt `bp` (Z. 1002). Quelle `GGXWDG_NGDP` liefert Prozent des BIP
  → Faktor **100**. Richtig. Die Gegenprobe der Datei ist ebenfalls belegt: `technik.md`
  Z. 1306 trägt wörtlich `schuld(l) = mal_geteilt(bip(l), staatsschuld[l], 10.000)`, und
  mit `staatsschuld` in bp ergibt der Nenner 10.000 genau den Quotienten (125,05 % →
  12.505 bp → `bip × 1,2505`). Mit Prozent wäre er um Faktor 100 falsch.

**Das Abnahmekriterium ist erfüllt.** Für jede der 31 Sollreihen und für den Handelsblock
steht Abruf-URL und Abrufdatum in der Datei (Z. 89, 106–107, 124, 162/172–175, 220, 255,
308), je Reihe steht ohne Widerspruch, ob sie 25 Stützstellen ohne Füllung trägt, am Ende
steht genau ein Wert für R und die Liste der zwei Reihen, die ihn erzwungen haben.

---

## Befund 1 (Nebenbefund, außerhalb des Kriteriums) — zwei Reihen ohne Umrechnungsfaktor, und eine davon habe ich in Runde 1 falsch abgehakt

**An den Projektmanager, nicht an den Datenbauer.** Die Deckungsfrage ist davon nicht
berührt; das Kriterium verlangt keine Einheitenangabe. Ich melde es, weil es dieselbe
Fehlerklasse ist wie der Nebenbefund aus Runde 1 und weil **meine eigene Begründung dort
in einem Punkt falsch war**.

Runde 1 schrieb: „Die Umrechnung in die Modelleinheit steht für Reihe 1, 8 und 10 da, für
Reihe 9 und Reihe 11 nicht." Der Datenbauer hat genau die beiden benannten Reihen ergänzt.
Nachgemessen gegen die Reihenliste gilt aber:

| Reihe | Sollreihen | Quelleneinheit | Modelleinheit (`technik.md` Z. 990–1006) | Faktor in der Datei? |
|---|---:|---|---|---|
| 1 | 4 | US$, konstante Preise 2015 | Tsd USD | ja, ÷ 1.000 (Z. 101) |
| 2 | **12** | % des BIP (belegt, s. u.) | **Zehntausendstel, auf 10.000 normiert** | **nein** |
| 8 | 4 | Prozent Jahresrate | bp Jahresrate | ja, × 100 (Z. 122) |
| 9 | 4 | Prozent p. a. | bp | ja, × 100 (neu, Z. 157) |
| 10 | **3** | Landeswährung je US$ | **Index** | **nein** |
| 11 | 4 | % des BIP | bp | ja, × 100 (neu, Z. 258) |

**Reihe 10 stand nie da.** Was die Datei zu Reihe 10 schreibt (Z. 229–248), ist der
Einheiten*bruch* DEM→EUR 1999 und die Verkettung mit 1,95583 — das ist eine andere Frage
als die Umrechnung in die Modelleinheit. Die Modelleinheit ist ein Index mit Basis 10.000:
`technik.md` Z. 884 setzt `land.US.wechselkurs` auf **10.000** als festen Numéraire-Wert,
Z. 886 dasselbe für `restwelt.wechselkurs`, und Z. 1377 macht `wechselkurs[g] ≥ 1` zur
Invariante. Aus 1,73405583 DEM/USD wird also 17.341, nicht 1,73 — ein Faktor 10.000, der
nirgends im Befund steht. Mein Runde-1-Satz hat diese Reihe zu Unrecht als erledigt geführt.

**Reihe 2 ist der größere Posten**, 12 der 31 Sollreihen. Nachgemessen am 2026-09-02:
`api.worldbank.org/v2/indicator/NV.AGR.TOTL.ZS?format=json` liefert
`name: "Agriculture, forestry, and fishing, value added (% of GDP)"` und im `sourceNote`
wörtlich „This indicator is expressed as a percentage of Gross Domestic Product (GDP)".
Die Modelleinheit ist Zehntausendstel — Faktor **100** —, und dazu kommt ein zweiter
Schritt, den kein Faktor abdeckt: „**auf 10.000 normiert**". Die drei WDI-Anteile summieren
sich nicht auf 100 (der Rest sind Nettogütersteuern), die Normierung ist also kein
Rundungsdetail, sondern verschiebt jeden der zwölf Werte. `technik.md` Z. 698 rechnet
anschließend `wertschoepfung[g][s] = mal_geteilt(bip_start[g], sektoranteil[g][s], 10.000)`
und setzt die Normierung damit voraus.

**Warum das gemeldet gehört:** Es sind die beiden Blöcke, für die die Deckung glatt „trägt"
sagt — und deshalb die beiden, die niemand mehr aufmacht. Ein stiller Faktor 100 oder
10.000 ist genau der Fehlertyp, der ein Modell plausibel aussehen lässt und trotzdem falsch
macht. **Der richtige Ort ist nicht dieses Paket**, sondern das Paket, das den Jahrgangsbau
oder die Aufbereitung schreibt: Dort gehört je Reihe eine Spalte „Quelleneinheit →
Modelleinheit → Faktor", und für Reihe 2 zusätzlich die Antwort, ob vor oder nach der
Normierung gerundet wird. Ein Rücklauf zu 0006 wäre eine Kriterienerhöhung und steht mir
nicht zu.

## Wonach ich außerdem gesucht und nichts gefunden habe

- **Stehengebliebene Altwerte** der Runde 1 (`grep` auf `27`, `26`, `zwei tragen`,
  `drei verkürzt` über alle 399 Zeilen) — keiner.
- **Zweite Richtung der Klassifikation**: nicht nur „ist jede tragende Zeile 25?", sondern
  auch „ist jede Zeile mit 25 als tragend gezählt?" — beide Richtungen gehen auf, kein
  Ausreißer.
- **Ob die Rework-Absätze eine Meßtabelle berührt haben** (`git diff 8f99b6d..74f5cb0`):
  vier Einfügungen und zwei Ersetzungen, alle in Fließtext und in der Summenzeile. **Keine
  Zahl in einer Abschnittstabelle geändert.** Die Runde-1-Prüfung der Meßwerte bleibt gültig.
- **Ob R sich unter der neuen Zählung bewegt** — nein, die dritte verkürzte Reihe liegt
  innerhalb des ohnehin bindenden Fensters. Nachgerechnet, nicht übernommen.
- **Ob die Varianten- und die Schrankentabelle noch zur geänderten Sollreihenzahl passen**
  (Z. 57 „dann 27 Sollreihen" = 31 − 4, Z. 59 „dann 23 Sollreihen" = 31 − 4 − 4) — beide
  richtig, beide unberührt von der Klassifikation der tragenden Reihen.
- **Nicht geprüft**, weil außerhalb des Pakets und im Rücklauf ausdrücklich ausgenommen:
  Preisbasis von Reihe 14, `GGXCNL_NGDP` für die USA, Lizenzen (Paket 0005).
