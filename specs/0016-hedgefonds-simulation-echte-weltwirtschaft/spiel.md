---
typ: spiel
idee: 0016-hedgefonds-simulation-echte-weltwirtschaft
erstellt: 2026-09-01
schleife: Der Spieler stellt je Runde bis zu drei Aktionen aus fünf Arten, die Welt rechnet ein Jahr weiter, und jede Zahländerung trägt die Kette ihrer Ursachen mit sich.
siegbedingung: Das Mandat — Fondsvermögen über einer Schwelle UND Einfluss über einer Schwelle in mindestens zwei Ländern — erreicht innerhalb von R Runden, ohne vorher an einer der drei Todesarten zu sterben. Ergebnis ist die Rundenzahl bis zur Erfüllung.
aktionen: 5
laender: Schicht 1 — 4 Politikländer (USA, China, Deutschland, Brasilien), nach Paket 0118 neun; Schicht 3 — ein nicht spielbares Restwelt-Aggregat. Schicht 2 siehe boersenplaetze.
boersenplaetze: Schicht 2, B = 3·(L+1) — je Gebiet ein Platz je Leitsektor. Bei L = 9 sind das 30 Plätze zu je vier Feldern plus einem Positionssteckplatz, also 150 Adressen; Zustand 890, handelbare Plätze 75. Handelbar, nicht beeinflussbar, ohne Handelszeile, ohne Sollreihe.
gueter: 3 Sektoren (Landwirtschaft, Industrie, Dienstleistungen), davon 2 mit Handelszeilen
takt: 1 Runde = 1 Jahr; R = 20 Runden, Startzustand 2001, Endzustand 2021, 21 Stützstellen
gegenkraefte: 5
messbar_entscheidungsdichte: Je Runde t = 1…R und je Startwert 30 gezogene Aktionsbündel; jedes ersetzt die Bot-Aktionen der Runde t, danach spielt der Heuristikbot auf dem Referenzprofil (1,1,1,1,1) bis Runde R. Dichte(t, Startwert) = Anteil der 30 Ergebnisse, die um mehr als 1.000 Milli-Runden vom Median dieser 30 abweichen; Dichte(t) = Mittel über die 50 Startwerte. Abnahme = Mittel der Dichte(t) je Partiedrittel (1-6, 7-13, 14-20) jeweils >= 0,4.
messbar_strategievielfalt: Profil = Fünftelverteilung über die fünf Aktionsarten (126 Profile), Wirkung über das Vorratsverfahren; je Profil Suchbot über 20 Startwerte, Profilergebnis = Median. Profil gewinnt, wenn sein Median <= 20.000 liegt. Strategiekern = die stärkste der drei Familien Position/Beteiligung/Lobby; die 6 Profile ohne jede Familienaktion haben keinen Kern und zählen nicht. Abnahme = alle drei Kerne stellen mindestens einen Gewinner, und das beste Klassenergebnis ist höchstens 25 Prozent besser als das schlechteste der drei.
messbar_optimumsverschiebung: Frühfenster = Runden 1-6 mit Profil p, Rest mit Referenzprofil; Spätfenster = Runden 14-20 mit Profil p, Rest mit Referenzprofil; je 126 Profile x 20 Startwerte, Median als Profilergebnis, bestes Profil je Fenster nach kleinstem Median (Gleichstand nach Profilkennung). Verschiebung = L1-Abstand der beiden Profilvektoren geteilt durch 5, Werte aus {0; 0,4; …; 2,0}. Schwelle 0,4.
messbar_rueckvergleich: Startjahrgang 2001, R = 20 Runden im Weltlauf (Fondsteilsystem abgeschaltet), Politikinstrumente exogen auf den historischen Pfaden; 16 Prüfgegenstände aus 23 freien Sollreihen plus Handelsblock, je über 21 Stützstellen ohne Füllung. Schwellen: MAPE 20 Prozent für Niveaureihen, mittlerer absoluter Fehler 300 Basispunkte für Ratenreihen, Richtungstreue 0,6 für alle. Bestanden, wenn höchstens 2 der 16 Prüfgegenstände reißen.
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
*Warum die Größe des Zustands keine Verteidigung ist*, acht Zeilen unter „Was bewusst fehlt",
fünf unter „Offene Entwurfsfragen" und ein Block unter „Was der Architekt neu rechnen muss".
**Keine Zahl der bestehenden vier Länder, keine Sollreihe, kein Prüfgegenstand und kein
Fehlermaß ändert sich**; die Bezugszahl des Zustands bleibt bis 0116 und 0118 die **310**, und
die Schichtensumme **890** gilt für den Stand nach beiden. Die zweite Schicht kostet **zwei**
neue Schlüssel in `parameter.toml` und **keinen neunten Rückkopplungskanal**.*

## Die Partielänge R, und warum sie hier als Buchstabe steht

Die zweite Fassung hat die Partielänge aus einer Regel abgeleitet — *die Partielänge ist
die Länge des Fensters, in dem jede Sollreihe ohne Füllung belegt ist* — und dann eine
falsche Zahl eingesetzt. Die dritte Fassung hat die Regel behalten und eine zweite Zahl
eingesetzt, die an **drei** der 31 Reihen und am Handelsblock gemessen war — den drei
US-Sektoranteilsreihen und BACI. **Seit dem 2026-09-02 sind alle 31 gemessen**, und beide
Zahlen waren zu groß.

### Was gemessen ist

`daten/deckungsbefund-1997.md` (Paket `0006-deckung-pruefjahrgang-1997`, `status: fertig`,
Abrufe vom 2026-09-01) hat jede der 31 Sollreihen und den Handelsblock einzeln abgerufen.
Von den 31 tragen 26 das Fenster 1997–2021 vollständig. Fünf nicht, und sie sind zwei
verschiedene Sorten:

| Reihe | Land | Befund | Rolle nach `technik.md` Abschnitt 7 |
|---|---|---|---|
| **11** Staatsschuldenquote | USA | beginnt **2001** (IWF WEO) | Start + Soll (**abgeleitet**) |
| **11** Staatsschuldenquote | BRA | beginnt **2000** | dito |
| **9** Leitzins | USA | endet **2020** (IWF `MFS_IR/DISR_RT_PT_A_PT`) | Start + Politikpfad + Soll (**gesetzt**) |
| **9** Leitzins | DEU | **kein einziger Wert** | dito |
| **9** Leitzins | CHN | **kein einziger Wert** | dito |

Dazu ein Nebenbefund außerhalb der Sollreihen, der hier mitentscheidet: **Reihe 12
(Haushaltssaldo), der historische Politikpfad des vierten Instruments, beginnt für die USA
ebenfalls 2001** — zwei unabhängige WEO-Reihen mit demselben Startjahr, im Befund gegen
sechs bekannte Werte gegengeprüft. Das ist keine Ausleseunsicherheit, sondern die bekannte
Eigenschaft des WEO, die Finanzstatistik des US-Gesamtstaats erst ab 2001 zu führen.

### Die Entscheidung: R = 20, Fenster 2001–2021, 21 Stützstellen

Der Befund legt drei Auswege mit je einem R daneben — 19, 20 oder 24. **Gewählt ist 20.**
Die beiden anderen fallen aus je einem Grund, und beide Gründe stehen in der Rollenspalte
der Reihenliste: Eine Reihe ist hier nicht einfach „da" oder „weg", sie hat bis zu drei
Rollen — Startwert, Politikpfad, Sollreihe —, und ein Ausweg, der sie streicht, streicht nur
eine davon.

**2001 ist erzwungen, und nicht von einer Sollreihenregel.** Der Ausweg zu `R = 24` heißt
im Befund „Reihe 9 und Reihe 11 gestrichen". Streichen kann man aber nur die *Sollrolle*
einer Reihe, nicht ihre beiden anderen. Reihe 11 ist auch **Start**: `staatsschuld[l]` ist
eine Zustandsadresse, und ihr Startwert ist die erste Stützstelle dieser Reihe. Reihe 12 ist
**Politikpfad**: Ohne sie steht das Haushaltsinstrument im Weltlauf auf nichts. Beide Lücken
sind **Anfangslücken**, und die Füllregel aus T24 lautet „Fortschreibung des letzten
bekannten Werts" — vor der ersten Stützstelle gibt es keinen. Eine Anfangslücke ist von der
Regel, die es gibt, nicht füllbar.

**`R = 24` verlangt damit drei Quellenersetzungen, und keine davon ist zu haben.** Einzeln,
weil sie sich unterscheiden:

| was ersetzt werden müsste | Stand nach dem Deckungsbefund |
|---|---|
| Reihe 11 **BRA** 1997–1999 | IWF WEO beginnt 2000, die Weltbank (`GC.DOD.TOTL.GD.ZS`) 2010. **In beiden geprüften Quellen kein Wert.** Das allein erledigt 1997. |
| Reihe 11 **USA** 1997–2000 | Die Weltbank trägt die USA lückenlos 1997–2021 — aber sie misst die Schuld des **Zentralstaats**, das WEO die des **Gesamtstaats**, und für China und Deutschland trägt sie nichts. Der Ausweg hieße: eine Sollreihe, die je Land aus einer anderen Quelle mit einer anderen Abgrenzung kommt. Das ist genau der Mangel, an dem der Leitzins gerade seine Sollrolle verliert. |
| Reihe 12 **USA** 1997–2000 | **Nicht gemessen.** Der Befund hat sie als Nebenbefund gefunden, nicht als Auftrag. Sie wäre erst noch zu suchen. |

Die erste Zeile ist bindend: Sie sagt nein, ohne dass die beiden anderen entschieden sein
müssen. Eine Zahl in dieses Frontmatter zu schreiben, die auf Daten steht, die niemand hat,
wäre genau der Fehler der zweiten Fassung noch einmal.

**2021 ist nicht erzwungen.** Das Fenster endet nur deshalb 2020, weil der **US-Leitzins**
dort endet. Diese Reihe war nach `technik.md` T37 **gesetzt**: Im Weltlauf wird das
Instrument auf den historischen Wert gesetzt, ihr Fehler ist null per Konstruktion, ihre
Richtungstreue eins, und sie ist keiner der 16 Prüfgegenstände und konnte keiner werden. **Alle
Reihen, die etwas entscheiden, tragen 2021** — BIP, die zwölf Sektoranteile, die
Verbraucherpreise, die drei Wechselkurse, der Handelsblock, dazu alle vier Schuldenquoten.
`R = 19` wirft also die Stützstelle 2021 weg, um eine Reihe zu schützen, die nicht
durchfallen kann. Und die weggeworfene ist nicht irgendeine: Ein Rückvergleich, der 2020
endet, prüft den Einbruch und nie die Rückkehr. Sein letzter Übergang ist ein Sturz ohne
Gegenstück, und die Richtungstreue misst über die schärfste Bewegung des ganzen Fensters
genau eine Richtung.

**Daraus folgt der Schnitt:** Reihe 9 verliert ihre Sollrolle und behält Start und
Politikpfad. Die Sollreihen sind damit **27** — Reihe 1 (4), Reihe 2 (12), Reihe 8 (4),
Reihe 10 (3), Reihe 11 (4) —, und **alle 27 tragen 2001–2021 mit 21 Stützstellen ohne eine
einzige Füllung.** Das ist das größte Fenster, in dem dieser Satz stimmt.

### Was die drei Auswege Maß 4 kosten — und warum das die Wahl nicht trifft

Weil die Abnahme dieses Pakets es namentlich verlangt, hier für jeden Ausweg die
Prüfgegenstände statt nur der Sollreihen:

| Ausweg | R | Fenster | Stützstellen | Sollreihen | Prüfgegenstände von Maß 4 |
|---|---:|---|---:|---:|---|
| Reihe 9 **und** Reihe 11 aus den Sollreihen — *verworfen, Fenster nicht aus Daten erreichbar* | 24 | 1997–2021 | 25 | 23 | **16**, keiner gestrichen |
| Reihe 9 für DE/CN ergänzt, alle 31 bleiben Sollreihen — *verworfen, opfert 2021* | 19 | 2001–2020 | 20 | 31 | **16**, keiner gestrichen |
| **Reihe 9 aus den Sollreihen — gewählt** | **20** | **2001–2021** | **21** | **27** | **16**, keiner gestrichen |

**In allen drei Auswegen sind es sechzehn, und das ist der eigentliche Befund dieses
Pakets.** Die 16 Prüfgegenstände speisen sich aus Reihe 1, 2, 8, 10 und 14 — BIP je Land
(4), Sektorstruktur je Land (4), Verbraucherpreise je Land (4), Wechselkurs je Land außer
USA (3), Handelsblock (1). Reihe 9 und Reihe 11 kommen darin nicht vor und können darin
nicht vorkommen: Die eine ist Eingabe des Laufs, die andere folgt dem gesetzten
Haushaltssaldo und hat nur einen endogenen Nenner — das BIP, das schon vier eigene Zähler
hat. **Genau diese beiden Reihen haben das Fenster gekürzt.** Die Abnahmeregel „höchstens 2
der 16 reißen" unterscheidet die drei Auswege also nicht, und sie war nie das, was auf dem
Spiel stand.

Was auf dem Spiel stand, sind zwei andere Dinge, und nach ihnen ist entschieden: **welches
Fenster aus Daten überhaupt erreichbar ist** (das erledigt 24) und **was eine Stützstelle
wert ist** (das erledigt 19). Was der Rückvergleich durch den Schnitt verliert, ist deshalb
auch kein Prüfgegenstand, sondern **Auflösung**: Jeder der sechzehn wird über 21 statt 25
Stützstellen gemessen, die Richtungstreue über 20 statt 24 Übergänge. Die Schwellen — MAPE
20 Prozent, 300 Basispunkte, Richtungstreue 0,6 — bleiben unverändert; ob sie über ein
kürzeres Fenster leichter oder schwerer zu halten sind, ist eine Messung des
Rückvergleichers und keine Entscheidung von mir.

### Was der Schnitt kostet, einzeln

- **Vier Runden.** Die Partie ist ein Sechstel kürzer als in der fünften Fassung, der
  Nachtlauf der drei Maße um 17 Prozent billiger (11.519.040 → 9.539.200 Weltschritte).
- **Der Euro-Beginn 1999 liegt vor dem Fenster.** Damit fällt die einzige Instrumentensperre,
  die *während* einer Partie zuschnappt: Deutschland hatte ab Runde 3 keinen eigenen
  Zinshebel mehr, jetzt hat es von Runde 1 an keinen. Die Asymmetrie **zwischen** den vier
  Ländern bleibt — sie ist das, worauf das Argument in *Welche vier Länder* steht —, der
  Übergang **innerhalb** der Partie ist weg. Für Maß 3 ist das der Verlust einer von drei
  benannten Quellen; die beiden anderen, Nachahmer (Gegenkraft 4) und Preisstoß
  (Gegenkraft 3), sind unberührt, und die Verschiebung war nie auf den Euro gestützt.
- **Die Wechselkursverkettung `verkettet_ab = 1999` läuft im Prüfjahrgang nie.** Sie bleibt
  in der Spezifikation, weil die Spieljahrgänge vor 2001 sie brauchen — aber der
  Prüfjahrgang testet sie nicht mehr mit. Das gehört in jeden Befund, statt als „ein
  Sonderfall weniger" gebucht zu werden.
- **Eine gefüllte Stützstelle im Politikpfad.** Der US-Leitzins hat für 2021 keinen Wert.
  Als Pfad — nicht als Sollreihe — wird er nach T24 fortgeschrieben und mit `gefuellt = 1`
  gekennzeichnet. Das ist **ein** Eingabejahr für **ein** Land, und es wirkt auf den letzten
  Übergang der US-Prüfgegenstände. Es wird ausgewiesen, nicht verrechnet.

### Was der Schnitt behält, und eine Zugabe

Im Fenster liegen weiterhin: Chinas WTO-Beitritt (Dezember 2001, wirksam ab Runde 1), die
Finanzkrise **2008** (Ende Runde 7), der Einbruch **2020** (Ende Runde 19) und die Erholung
**2021** (Ende Runde 20). Ebenso der negative Euro-Einlagesatz ab 2014, an dem die Schranke
`aufschlag_min` hängt — siehe *Was ein Korb wert ist*.

Und eine Eigenschaft, die keiner der beiden verworfenen Werte hat: **20 ist ein Vielfaches
von 5.** Nach dem Vorratsverfahren steht der Vorratsvektor nach je fünf Runden wieder auf
`(0,0,0,0,0)`. Für jeden Lauf, der eine ganze Partie lang **dasselbe** Profil spielt — das
sind alle 126 Läufe von Maß 2 und jede Trägerpartie von Maß 1 —, endet die Partie deshalb
genau auf einem solchen Punkt, und jede Aktionsart hat exakt `12 · ai` der 60 Steckplätze
bekommen. Bei 24 und bei 19 endet die Partie mitten im Zyklus, und die tatsächliche
Artenverteilung weicht vom Profil ab, das Maß 2 und Maß 3 als unabhängige Größe führen. Das
ist kein Hauptgrund; es ist der einzige Punkt, an dem die gewählte Zahl **besser** ist als
die beiden verworfenen und nicht bloß weniger schlecht. (Für Maß 3 gilt er nicht: Seine
Fenster sind 6 und 7 Runden lang, der Profilwechsel fällt nicht auf einen Nullpunkt, und die
Abweichung innerhalb eines Fensters bleibt beschränkt statt null — wie bisher.)

### Und die eigentliche Lehre steht nicht in der Zahl, sondern in ihrer Fassung

Die zweite Fassung hat `28` in jede abgeleitete Größe geschrieben — Ergebnisskala,
Partiedrittel, Fenstergrenzen, Kostenformeln. Eine einzige falsche Messung machte damit
zwölf Zahlen falsch. **Deshalb steht in diesem Entwurf jede abgeleitete Größe als Formel
in R, mit R = 20 eingesetzt.** Dieser Lauf ist die Probe darauf: Die Messung hat gegenüber
der fünften Fassung vier Runden gekostet, und der Entwurf hat sich um zwölf Substitutionen
geändert und um keine Regel. Kein Paket ist zweimal gebaut worden.

**Und R kann weiter fallen.** Drei Pfade, an denen der Weltlauf hängt, sind bis heute
**nicht gemessen**: die Bevölkerungs- und Erwerbstätigenpfade (Reihen 5 und 6) und der
Zollpfad (Reihe 13, dazu mit offener Lizenzfrage). `daten/reihen.toml` führt sie mit
`deckung_gemessen = false`. Die Ersetzungsregel gilt für sie genauso: Misst der Jahrgangsbau
enger, ist R zu ersetzen und sonst nichts.

## Die Schleife

Eine Runde ist ein Jahr und läuft in sechs Schritten, immer in dieser Reihenfolge.
Die feste Reihenfolge ist keine Formsache: Sie ist die Bedingung dafür, dass derselbe
Startwert und dieselbe Aktionsfolge in drei Monaten dasselbe Ergebnis liefern.

1. **Ansicht.** Der Zustand, und daneben die Kette der Vorrunde: was sich geändert hat,
   ausgelöst wodurch, über welchen Umweg, mit welcher Verzögerung.
2. **Aktionen.** Der Spieler stellt **bis zu drei** Aktionen. Drei, nicht beliebig viele —
   die Knappheit ist die Quelle der Entscheidungsdichte. Wer alles tun kann, wählt nicht.
3. **Politik.** Anliegender Lobbydruck und Gegenlobby werden je Instrument gegeneinander
   verrechnet, fällige Verzögerungen aus früheren Runden greifen, Instrumente bewegen sich
   um höchstens einen Schritt je Runde.
4. **Wirtschaft.** Produktion aus Kapitalstock und Produktivität, Handel zwischen den vier
   Ländern und der Restwelt, Preise, Realeinkommen, Zins, Wechselkurs, Staatsfinanzen.
5. **Reaktion.** Zustimmung, Regierungswechsel, Aufsichtszähler, Nachahmerzähler,
   Anlegerbestand — die fünf Gegenkräfte rechnen ab.
6. **Abrechnung.** Positionen bewertet, Hebel gegen den Innerjahresausschlag geprüft,
   Mandat geprüft, Kette als Diff gespeichert.

Innerhalb einer Runde wird **keine Zustandsgröße zweimal geschrieben**, und die
Reihenfolge oben ist zyklenfrei. *Welche* Größen überhaupt geschrieben werden, hängt vom
Modus ab — im Spielmodus alle, im Weltlauf des Rückvergleichs eine erklärte Teilmenge
(siehe **Maß 4**). Die einzige Schleife im ganzen Modell ist die Markträumung in
Schritt 4, und sie läuft mit fester Iterationszahl. Alles, was wie eine Rückkopplung
aussieht, überquert eine Rundengrenze — siehe **Der Zustand**.

### Was für die Preisbildung gelten muss

Das Wie ist Sache des Architekten; was gelten muss, steht hier.

Für die beiden Sektoren mit Handelszeilen gibt es je einen Weltpreis, der alle Angebote
und Nachfragen räumt, und darauf je Land einen Zollkeil. Der Sektorpreis eines Landes
hängt aber **nicht vollständig** am Weltpreis, sondern nur zum Anteil `durchgriff`:

```
preis = weltpreis_mit_zoll · durchgriff + landespreis · (10.000 − durchgriff)
        alles geteilt durch 10.000
```

Beide Größen darin sind jetzt bestimmt, und beide waren es in der zweiten Fassung nicht:

**`landespreis` ist der Sektorpreis derselben Größe aus der Vorrunde.** In Runde 1 ist es
der Startwert des Jahrgangs (Index 10.000). Damit ist die Überschussfunktion monoton im
Weltpreis, die Halbierungssuche aus `technik.md` T28 ist ein einziger Durchlauf, und es
entsteht keine Fixpunktaufgabe. Inhaltlich ist das Preisträgheit: Der Inlandspreis eines
Sektors folgt dem Weltpreis mit einem Jahr Verzögerung, und wie stark, sagt `durchgriff`.

**`durchgriff` ist ein Modellkonstrukt mit Regel, kein gemessener Anteil.** Die zweite
Fassung nannte ihn `handelsanteil` und definierte ihn als (Ausfuhr + Einfuhr) geteilt
durch die Wertschöpfung des Sektors. Diese Größe verlässt ihren Wertebereich, und zwar
nicht als Ausreißer, sondern von Bauart wegen: Aus- und Einfuhr sind Bruttoströme,
Wertschöpfung ist netto. Für Deutschland 1995 ergibt sie 2,69 in der Landwirtschaft und
1,20 in der Industrie (nachgerechnet vom Prüfer aus WDI, abgerufen 2026-08-31); das
Gewicht auf dem Landespreis wird negativ, und aus der angekündigten Mischung wird eine
Extrapolation mit negativen Preisen.

Die Regel lautet deshalb, mit `H` = Aus- plus Einfuhr des Sektors und `N` = seine
Wertschöpfung, beide im Startjahr:

```
durchgriff = teile_gerundet(10.000 · H, H + N)
```

Das ist streng monoton in `H/N`, liegt für alle nichtnegativen `H`, `N` mit `H + N > 0`
im Bereich 0 … 10.000 und braucht keine Kappung. Aus den beiden nachgerechneten Fällen
werden `71,94/98,71` → **7.288** für die deutsche Landwirtschaft und `915,39/1.675,41` →
**5.464** für die deutsche Industrie; eine US-Industrie mit `H/N = 0,3` käme auf 2.308.
**Die Ordnung, die das Argument trägt, bleibt also erhalten** — ein Zoll
trifft Chinas Industrie über ihren hohen `durchgriff` hart und die US-Industrie, in der
Bau und Versorger dominieren, schwach —, und der Wertebereich hält.

Was der Koeffizient damit **nicht** ist: eine Messung der Handelsoffenheit. Sein
Zahlenwert hat keine volkswirtschaftliche Bedeutung; er muss Länder und Sektoren richtig
ordnen, und das tut er. Er ist exogen und über die Partie konstant; Chinas wachsende
Handelsoffenheit bildet das Modell über die Mengen ab, nicht über die Preisübertragung.
Zwei benannte Vereinfachungen, keine versteckten.

Dienstleistungen haben keine Handelszeile, keinen Weltpreis und nur einen Landespreis.

### Der Zollkeil ist multiplikativ, und das entscheidet die Skalentabelle

`technik.md` T28 **nennt** den Keil („der Zollkeil je Gebiet auf dem Weltpreis"), ohne ihn
hinzuschreiben. Bis zum 2026-09-03 war das folgenlos; seit die Schadensvorschrift von
Gegenkraft 5 den Keil vom übrigen Preishub trennt, ist es das nicht mehr. Was gelten muss:

```
weltpreis_mit_zoll(l, s) = mal_geteilt( welt.preis.<s>, 10.000 + zollstand(l), 10.000 )
```

**Die additive Lesart ist nicht schlechter begründet, sondern gar nicht bildbar.** Der
Zollstand steht nach `technik.md` T5 in **Klasse 3** (Basispunkte), der Weltpreis in
**Klasse 5** (Index, Startjahr 10.000). Eine Summe zweier Klassen kennt T5 nicht; eine Rate
trifft ein Niveau in diesem Modell ausnahmslos als Faktor, wie in
`schuld = mal_geteilt(bip, staatsschuld, 10.000)`. Inhaltlich sagt dieselbe Wahl dasselbe:
Ein aggregierter Zollsatz je Land in Basispunkten ist ein Wertzoll, sonst wäre er keine
Rate. Beides zeigt in dieselbe Richtung, deshalb ist die Festlegung hier eine Klarstellung
und keine Wahl.

Sie steht hier und nicht in einer offenen Frage, weil eine Rechenvorschrift, die auf eine
ungeschriebene Formel zeigt, wieder nur ein Adjektiv ist — genau der Mangel, gegen den
Paket 0021 angetreten ist.

### Die Zuordnung der BACI-Warencodes zu den zwei handelbaren Sektoren

Ohne sie ist weder `H` noch der Handelsblock berechenbar. Sie ist eine Tabelle im
Manifest des Jahrgangs und lautet:

| HS92-Kapitel | Modellsektor |
|---|---|
| 01–24 | 1 Landwirtschaft |
| 25–97 | 2 Industrie |

**Der Fehler dieser Grobzuordnung gehört dazu:** Rohholz (44), Häute (41) und pflanzliche
Spinnstoffe (50–53) zählt WDI zur Landwirtschaft, diese Tabelle zur Industrie;
verarbeitete Nahrungsmittel (16–21) zählt WDI zum verarbeitenden Gewerbe, diese Tabelle
zur Landwirtschaft. Der Fehler ist für alle fünf Gebiete derselbe, weil dieselbe Tabelle
gilt — und er trifft die Sollreihe genauso wie das Modell, weil der Handelsblock des
Rückvergleichs aus **derselben** Aggregation entsteht. Verglichen wird damit aggregiert
gegen aggregiert, so wie bei den auf 10.000 normierten Sektoranteilen auch.

## Die Aktionen

Fünf Arten. Jede ist diskret, keine hat einen Zeitpunkt innerhalb der Runde. Die
Kennungen 1 bis 5 sind zugleich die Gleichstandsordnung aller Maße.

1. **Position.** Long oder short auf ein Land×Sektor, auf eine Währung, auf die
   Staatsanleihe eines Landes oder — seit dem 2026-09-05 — auf einen **Börsenplatz**
   (siehe *Die drei Schichten der Welt*). In festen Stufen, sofort wirksam, jederzeit auflösbar.
   Der Ein- und Ausstieg bewegt den Preis gegen den Fonds, und zwar umso stärker, je
   größer sein Anteil an diesem Markt ist.
2. **Beteiligung.** Ein dauerhafter Anteil an einem Land×Sektor. Sie ist illiquide — der
   Ausstieg dauert zwei Runden, und ihr Ausstiegsabschlag steckt bereits im Wertansatz, ist
   beim Einstieg also sofort bezahlt (siehe *Was das Fondsvermögen ist*) — und sie ist der einzige Weg zu
   billigem Lobbying: Lobbyaktionen in einem Sektor, an dem der Fonds beteiligt ist,
   kosten einen Bruchteil.
3. **Lobbybudget.** Geld auf ein Politikinstrument eines Landes, in eine Richtung. Wirkt
   nicht sofort, sondern legt sich als Druck an; ob es greift, entscheidet Schritt 3 gegen
   die Gegenlobby. Ohne Beteiligung im betroffenen Sektor möglich, aber teuer.
4. **Hebel.** Kreditaufnahme zum Leitzins des Landes plus einem Aufschlag, der mit der
   Sichtbarkeit des Fonds steigt. Vergrößert jede Position und jede Verlustserie.
5. **Sichtbarkeit.** Der Fonds legt eine Position öffentlich offen oder zieht sich zurück.
   Offenlegung verstärkt jedes Lobbybudget in dieser Sache, weil sie öffentlichen Druck
   erzeugt — und sie füttert den Aufsichtszähler in jedem Land, in dem der Fonds steht.

**Warum fünf und nicht drei.** Die Arten 1 bis 3 sind die drei Strategiefamilien, an denen
Maß 2 gemessen wird; ohne sie gibt es nichts zu messen. Hebel ist keine eigene Strategie,
sondern die Angriffsfläche der ersten Todesart, und ohne ihn ist Größe risikolos.
Sichtbarkeit ist der Grund, warum die Gegenkräfte ein Spielfeld sind und kein Bremsklotz:
Ohne sie wäre Aufmerksamkeit eine bloße Strafe auf Erfolg, mit ihr ist sie eine
Entscheidung — laut und schnell gegen leise und langsam. Genau daraus entsteht die
Optimumsverschiebung, die Maß 3 verlangt.

## Der Zustand

**310** ganzzahlige Größen; die Aufstellung Zeile für Zeile steht in `technik.md` T15 und
ist dort nachgerechnet. Die Zahl selbst ist keine Verteidigung — siehe unten.

**Diese 310 sind der Stand von heute und bleiben die Bezugszahl, bis Paket 0116 die
Adressarithmetik parametrisch geschrieben und Paket 0118 die fünf weiteren Länder gewählt
hat.** Was dieser Abschnitt beschreibt, ist die erste von drei Schichten; die zweite
(Börsenplätze) und die Rechnung, die auf **890** führt, stehen unter *Die drei Schichten der
Welt*. Zwei unkommentierte Summen in einem Dokument sind der Anfang des nächsten Zählfehlers,
deshalb steht an jeder von beiden, welchen Stand sie meint.

**Je Land** (vier Länder): drei Sektoren mit Wertschöpfung, Kapitalstock, Beschäftigung
und Preis; Bevölkerung und Erwerbstätige; Produktivität; Preisniveau und Inflation;
Leitzins; Wechselkurs gegen den US-Dollar als Numéraire; Staatsschuld und Haushaltssaldo;
Zustimmung zur Regierung; Aufsichtszähler; Einfluss; vier Politikinstrumente, jedes mit
Stand, anliegendem Druck, Gegendruck und Restverzögerung; drei Restdauerzähler.

**Die Restwelt** trägt dieselben Sektor- und Aggregatgrößen, aber **keine
Politikinstrumente, keine Zustimmung, keinen Aufsichtszähler und keinen Einfluss** — der
Fonds kann dort weder handeln noch lobbyieren. Sie schließt den Kreislauf; ohne sie wäre
die Summe der vier Handelsbilanzen zwangsläufig null, was gegen die echten Daten falsch
ist.

**Handel:** eine volle Matrix über **fünf Gebiete × vier Gegenüber × zwei Sektoren mit
Handelszeilen = 40 Ströme**, die Restwelt mit eigenen Zeilen. Nur so hält die Invariante
„Summe aller Handelsbilanzen einschließlich Restwelt = 0".

**Der Fonds:** Kasse, Positionen, Beteiligungen, Hebelstand, globale Sichtbarkeit,
Anlegerbestand, Marktanteil, Überrendite der letzten drei Runden. Dazu je Land×Sektor ein
Nachahmerzähler (12) und der Marktkorb (Wert und Rendite) als Bezugsgröße.

**Einfluss je Land** ist der geglättete Anteil des Fonds am gesamten Lobbydruck in diesem
Land, 0 bis 100. Er ist die zweite Hälfte der Siegbedingung — und die Größe, deren Erwerb
sämtliche Gegenkräfte weckt.

### Die vier Politikinstrumente

| Instrument | Datenanker | Bemerkung |
|---|---|---|
| Leitzins | ja, aber **als Pfad, nicht als Sollreihe** (seit 2026-09-03, siehe *Die Partielänge R*) | Für Deutschland **exogen ab 1999**; das liegt vor dem Fenster 2001–2021, Deutschland hat also über die ganze Partie keinen eigenen Zinshebel. Diese Asymmetrie ist gewollt, siehe unten. |
| Zollniveau | ja, aber **nur aggregiert je Land** (WDI, mit Vorbehalt) | Kein Zoll je Sektor. Die Sektorwirkung entsteht aus `durchgriff` und den Importanteilen, nicht aus einem erfundenen Sektorzoll. |
| Haushaltssaldo / Staatsausgabenquote | ja (IWF WEO) | |
| Kapitalverkehrs- und Finanzmarktregulierung | **nein, reines Modellkonstrukt** | Muss existieren, weil die Aufsicht sonst keinen Angriffspunkt auf den Fonds hat. Ohne Sollreihe; im Rückvergleich fest auf dem Startwert, und das Orakel ist für dieses Instrument blind. |

### Jede Größe ohne Datenanker, mit ihrem Startwert

Die Abnahmebedingung 2 verlangt, dass jede Größe entweder auf eine Reihe aus `daten.md`
zurückgeführt oder als Modellkonstrukt mit Entstehungsregel gekennzeichnet ist. Die
verankerten stehen in der Reihenliste des Architekten. Hier stehen **alle übrigen** — bis
auf die elf, deren Herkunft `technik.md` T46 ist und die diese Tabelle nicht kennen kann,
weil sie aus dem Vergleich der Reihenliste mit der Adressaufstellung folgen (US-Wechselkurs
als Numéraire, fünf Aggregatgrößen der Restwelt, fünf Neubasierungszähler). **Mit T46
zusammen ist die Aufzählung abschließend, und nur zusammen war sie es je.** Das ist
Beobachtung 2 aus `technik.md` Abschnitt 12, hier angenommen statt bestritten:

| Größe | Startwert | Regel im Lauf |
|---|---|---|
| Sektorpreis (je Gebiet × Sektor, 15) | Index 10.000 | Markträumung, siehe oben |
| Weltpreis (je handelbarem Sektor, 2) | Index 10.000 | Markträumung in Schritt 4, siehe oben |
| `landespreis` | = Sektorpreis, Runde 1 also 10.000 | Sektorpreis der Vorrunde |
| `durchgriff` (je Gebiet × handelbarem Sektor) | Konstante des Jahrgangs | `10.000·H/(H+N)`, über die Partie fest |
| Zustimmung (je Land) | aus `parameter.toml` | Gegenkraft 2 |
| Aufsichtszähler (je Land) | 0 | Gegenkraft 1 |
| Nachahmerzähler (je Land × Sektor) | 0 | Gegenkraft 4 |
| Einfluss (je Land) | 0 | geglätteter Anteil am Lobbydruck |
| Lobbydruck je Instrument (16) | 0 | Aktion 3, Verrechnung in Schritt 3 |
| Gegendruck je Instrument (16) | 0 | Gegenkraft 5 |
| Restverzögerung je Instrument (16) | 0 | Schritt 3 |
| drei Restdauerzähler je Land (12) | 0 | Gegenkraft 1 und 2 |
| Finanzmarktregulierung (Stand) | aus `parameter.toml` | Instrument wie die anderen drei |
| `markt.wert` | Wert des Startkorbs zu Startpreisen | eingefrorener Mengenkorb aus zwölf Körben und vier Anleihen, T33; Bewertung siehe *Was ein Korb wert ist* |
| `markt.rendite` | 0 | ebd. |
| Fondskasse, Anlegerbestand | aus `parameter.toml` (Startkapital) | Aktionen und Abrechnung |
| Marktanteil | 0 | Wertanteil am Marktkorb, Formel unter *Was ein Korb wert ist* |
| Hebelstand, Sichtbarkeit, Überrendite (3) | 0 | Aktionen 4 und 5, Abrechnung |
| Beteiligungen (12 Anteile + 12 Restdauern) | 0 | Aktion 2 |
| Positionssteckplätze (20) | 0 | Aktion 1 |
| Partie: Runde | 0 | Buchführung des Laufs |
| Partie: Jahrgangskennung | aus dem Manifest des Jahrgangs | fest über die Partie |
| Partie: Parametersatz-Prüfsumme | aus `parameter.toml` | fest über die Partie |
| Partie: Mandatsstand | 0 | Schritt 6, Mandatsprüfung |

**Diese Tabelle ist der Herkunftseintrag für die 150 Entwurfsadressen**, und erst mit den
sieben Zeilen der vierten Fassung und dem Verweis auf T46 ist sie das, was sie von sich
behauptet. Der
Abgleich gegen die 310 Adressen aus `technik.md` T15 stammt nicht von mir, sondern aus der
Prüfung vom 2026-09-01: Ohne Herkunftseintrag blieben dort **32** Adressen (Lobbydruck und
Restverzögerung je Instrument, vom Architekten in T23 Punkt 1 nachgetragen) und **sechs**
(zwei Weltpreise, vier Partiefelder, für die T45 keine zulässige Eintragsart kannte). Alle
38 stehen jetzt hier, wo die Tabelle sie zugesagt hatte. Das ist die Bedingung, an der der
Jahrgangsbau nach T45 sonst abbräche.

### Was das Fondsvermögen ist, und ob die Beteiligungen dazugehören

Der Architekt hat die Frage zurückgegeben (`technik.md` Abschnitt 12, Punkt 3), und sie ist
eine Modellfrage. **Sie zählen dazu:**

```
fondsvermoegen = Kasse + bewertete Positionen + bewertete Beteiligungen − Hebel
```

**Der Grund ist kein Geschmack, sondern Maß 2.** Zählten sie nicht, verwandelte Aktion 2
Kasse in etwas, das in keiner Hälfte des Mandats vorkommt; Klasse 2 könnte die erste
Abnahmehälfte von Maß 2 dann unabhängig von jeder Kalibrierung nicht bestehen, und ein Maß,
das eine seiner drei Klassen von Bauart wegen durchfallen lässt, misst nichts.

**Bewertet wird zum Ausstiegswert, also zum Modellwert des Land×Sektor-Korbs abzüglich des
Ausstiegsabschlags.** Damit heißt „Fondsvermögen" durchgehend dasselbe — *was der Fonds
wert ist, wenn er hier aufhört* —, und genau das brauchen die Ergebnisgröße, das Mandat und
Todesart 1. Der Abschlag ist damit beim **Aufbau** der Beteiligung bezahlt und wird beim
gewöhnlichen Ausstieg nicht ein zweites Mal abgezogen; illiquide bleibt sie über die zwei
Runden Ausstiegsdauer. Der Zwangsverkauf aus Gegenkraft 1 ist davon unberührt — sein
Abschlag ist eine zusätzliche Strafe und kommt oben drauf.

**Und die Regel, die den Nenner der Fondsrendite sichert:** Fällt das Fondsvermögen auf null
oder darunter, greift Todesart 1 (Zwangsliquidation) in derselben Runde. Eine Rendite auf
einen nichtpositiven Nenner wird damit nie gebildet.

### Was ein Korb wert ist, was eine Stufe ist und was eine Anleihe kostet

Die vierte Fassung hat entschieden, **dass** die Beteiligungen zum Fondsvermögen zählen, und
`technik.md` T47 hat das als Formel hingeschrieben. Damit wurde sichtbar, dass zwei Namen
darin nirgends gebildet werden: `korbwert(l, s)` und `positionswert(p)`. Beide sind
Modellentscheidungen und stehen deshalb hier; mit dem **Anleihekurs**, den der Prüfer als
dritte Lücke benannt hat („für die vier Anleihe-Steckplätze gibt es nicht einmal einen
Preis"), sind es drei, und sie hängen zusammen.

#### Eine Bewertungsformel, drei Mengen, drei Kurse

Jede Bewertung im Modell hat dieselbe Bauart — **Menge mal Kurs, umgerechnet in den
Numéraire**:

```
wert(menge, kurs, gebiet) = mal_geteilt(menge, kurs, wechselkurs[gebiet])
```

Kurs und Wechselkurs sind beide Indizes mit Startwert 10.000; ihr Skalenfaktor kürzt sich
gegeneinander weg, und die Bewertung braucht keine Konstante. Für die USA steht
`wechselkurs` als Numéraire dauerhaft auf 10.000; dort ist die Formel eine reine
Kursbewertung. Menge und Kurs je Steckplatzart:

| Steckplatzart | Menge | Kurs |
|---|---|---|
| Land×Sektor (12) | `kapitalstock[l][s]` | `sektorpreis[l][s]` |
| Währung (4) | `handelsvolumen[l]` — Aus- plus Einfuhr des Landes über beide handelbaren Sektoren, aus der Handelsmatrix | 10.000, fest |
| Anleihe (4) | `schuld[l] = mal_geteilt(bip[l], staatsschuld[l], 10.000)`, mit `bip[l]` = Summe der drei Wertschöpfungen | `anleihekurs[l]`, siehe unten |

Daraus die vier Bewertungen, aus denen T47 seine beiden fehlenden Namen bekommt:

```
korbwert(l, s)   = wert(kapitalstock[l][s], sektorpreis[l][s], l)
anleihewert(l)   = wert(schuld[l],          anleihekurs[l],    l)
waehrungswert(l) = wert(handelsvolumen[l],  10.000,            l)

stufenwert(p)    = mal_geteilt(markt(p), stufenweite, 10.000)
positionswert(p) = stufen(p) · stufenwert(p), in Fondsgeld umgerechnet
```

`markt(p)` ist der Korb-, Anleihe- oder Währungswert des Steckplatzes, `stufen(p)` seine
vorzeichenbehaftete Stufenzahl aus T16. Die ersten vier Größen stehen in der
**volkswirtschaftlichen Skala**, `positionswert` ist nach T5 **Fondsgeld** — die Skalengrenze
verläuft also genau zwischen `stufenwert` und `positionswert`, und was das heißt, steht
unten. Der Steckplatz Währung USA bleibt nach T16 dauerhaft leer, die Formel ist dort ohne
Wirkung.

`staatsschuld[l]` ist nach Reihenliste Nr. 11 und der Klasse *Raten* aus T5 die **Quote in
Basispunkten**, nicht der Betrag — deshalb der Umweg über `bip[l]`. Ein Nenner null tritt
in keiner der drei Zeilen auf: Der Wechselkurs ist als Index strikt positiv — das ist eine
Bedingung an die Wechselkursregel und eine Wertebereichsgrenze, die der Bruchlauf prüft —,
die 10.000 ist ein Literal, und der Anleihenenner ist unten beschränkt.

#### Warum der Kapitalstock und nicht die Wertschöpfung

Beide stehen im Zustand, und der Prüfer hat beide als Kandidaten benannt. Es ist der
**Kapitalstock**, aus drei Gründen, und der dritte entscheidet:

1. **T33 Punkt 3 verlangt einen Mengenkorb**, den man zu den Preisen dieser Runde bewertet.
   Ein Bestand ist eine Menge, ein Jahresstrom ist keine. Mit dem Kapitalstock ist der
   eingefrorene Mengenkorb aus T33 zum ersten Mal eine benennbare Größe.
2. **Eine Beteiligung ist ein Anteil an dem, was ein Sektor besitzt**, nicht an dem, was er
   in einem Jahr erwirtschaftet. Der Ertrag steckt im Kurs, nicht in der Menge.
3. **Die Wertschöpfung schwankt jährlich, der Kapitalstock nicht.** Hinge der Wert eines
   Korbs an der Wertschöpfung, bewegte ihn jede Produktionsschwankung stärker als jede
   Lobbyaktion — und die Wirkungskette, die dieses Spiel verkauft
   („Zoll → Importpreis → dein Bestand"), verschwände im Rauschen ihrer eigenen
   Nebengrößen. Der Kapitalstock ändert sich nur über Kanal 1, also langsam und mit
   Verzögerung; **damit ist die Kursänderung der sichtbare Teil der Bewertung, und das ist
   genau die Zahl, die der Käufer erklärt haben will.**

Ein Vielfaches auf die Wertschöpfung („Kurs-Gewinn-Verhältnis") wäre die dritte Lesart. Sie
kostet einen zweiten freien Parameter ohne Anker und liefert dieselbe Ordnung; sie ist
deshalb nicht gewählt.

**Der Kapitalstock je Sektor braucht eine Startregel, und es ist dieselbe wie bei der
Wertschöpfung.** Reihenliste Nr. 3 liefert einen Kapitalstock **je Gebiet**, der Zustand
führt drei **je Gebiet und Sektor**. Sie entstehen im Startjahr aus den auf 10.000
normierten Sektoranteilen (Reihe 2), also genau so, wie aus BIP und denselben Anteilen die
drei Wertschöpfungen entstehen:

```
kapitalstock[l][s] = mal_geteilt(kapitalstock[l], sektoranteil[l][s], 10.000)
```

Danach ist er endogen über Kanal 1. Das ist kein neuer Mechanismus, sondern der schon
vorhandene, ein zweites Mal angewandt — und es hält die drei Sektorkapitalstöcke im Rang
`Datenanker`, weil beide Eingangsreihen verankert sind.

#### Warum eine Stufe ein Anteil ist und kein Betrag

`stufenweite` steht in `parameter.toml` (T27). **Sie ist ein Anteil in Zehntausendsteln des
Marktes, an dem der Steckplatz hängt, kein Geldbetrag.** Eine Stufe auf `US×Industrie` ist
also *`stufenweite` Zehntausendstel dieses Korbs*, und ihr Preis ist, was dieser Anteil heute
kostet.

**Der Grund ist der Zustand, nicht der Geschmack.** Wäre eine Stufe ein fester Geldbetrag,
brauchte jeder Steckplatz seinen Einstandspreis, um überhaupt bewertbar zu sein — zwanzig
weitere Adressen, ein zweiter Ort für dieselbe Wahrheit und ein Zustand, der nicht mehr aus
sich heraus lesbar ist. Als Anteil folgt der Wert **vollständig aus dem heutigen Zustand**:
Kaufe ich eine Stufe, gibt die Kasse ihren heutigen Wert ab und der Steckplatz nimmt ihn
auf, netto null; bewegt sich danach der Kurs, bewegt sich der Steckplatz und sonst nichts.
Bei negativer Stufenzahl kehrt sich das Vorzeichen um, und ein Kursanstieg ist ein Verlust —
long und short sind dieselbe Formel, wie es Maß 2 verlangt.

**Drei Größen, die daran hängen, sind damit ebenfalls gerechnet:**

- **Der Anteil des Fonds an einem Land×Sektor**, in Zehntausendsteln:
  `|stufen| · stufenweite + anteil[l][s]`. Position und Beteiligung sind Anteile an
  **demselben** Korb und addieren sich. Beträge, nicht Vorzeichen — ein großer Short bewegt
  einen Markt so stark wie ein großer Long.
- **Der lokale Fußabdruck aus Gegenkraft 1** liest genau diese Zahl, und der Preisstoß aus
  Aktion 1 ebenfalls („umso stärker, je größer sein Anteil an diesem Markt ist"). Beide
  brauchen keinen eigenen Begriff mehr.
- **`fonds.marktanteil`**, gebildet in Schritt 6 nach T33 Punkt 4, also gegen den neuen
  `markt.wert`:

  ```
  korbbestand  = Σ über die 12 Körbe    mal_geteilt(korbwert(l,s), |stufen|·stufenweite + anteil[l][s], 10.000)
               + Σ über die 4 Anleihen  mal_geteilt(anleihewert(l), |stufen|·stufenweite,               10.000)
  marktanteil  = teile_gerundet(korbbestand · 10.000, markt.wert)
  ```

  Währungen gehen nicht ein — nach T33 Punkt 1 tragen sie keine Kapitalisierung. Das
  `handelsvolumen` ist die **Tiefe** des Währungsmarktes und trägt Stufenwert und
  Preisstoß, nicht den Marktkorb. `markt.wert` ist eine Summe positiver Mengen mal positiver
  Kurse und damit nie null.

**Was die Kalibrierung dabei zu treffen hat, und woran sie scheitert.** Startkapital und
`stufenweite` legen zusammen fest, wie groß der Fonds gegenüber der Welt werden kann. Zwei
Bedingungen, beide am Prüfstand ablesbar: Eine Stufe muss aus dem Startkapital bezahlbar
sein, und erreichbare Stufenzahlen müssen die Aufsichtsschwellen aus Gegenkraft 1 überhaupt
erreichen können. Verfehlt der Parametersatz die erste, gewinnt Klasse 1 nie; verfehlt er
die zweite, greift keine Gegenkraft und Maß 3 fällt auf null. **Ein dritter Regler dafür —
etwa ein „investierbarer Anteil" des Kapitalstocks — wäre mit dem Startkapital redundant:
Nur das Verhältnis beider Größen wirkt.** Es gibt ihn deshalb nicht.

#### Der Anleihekurs, die einzige neue Kursgröße

Der Zustand führt je Land `leitzins` und `staatsschuld`, aber keinen Anleihekurs — der
Prüfer hat zu Recht bemerkt, dass die vier Anleihesteckplätze damit an nichts hängen. Er
bekommt **keine Adresse, sondern eine Regel**, wie `landespreis` auch (T39):

```
anleihekurs(l) = teile_gerundet(10.000 · (leitzins_start[l] + aufschlag), leitzins[l] + aufschlag)
```

`leitzins_start[l]` ist der Leitzins des Startjahrs, den der Jahrgang als erste Stützstelle
des Politikpfads ohnehin trägt (Reihe 9); `aufschlag` ist ein neuer Schlüssel in
`parameter.toml`, in Basispunkten, und bedeutet den Abstand zwischen Leitzins und
Anleiherendite.

Das ist der Kurs einer ewigen Anleihe: streng fallend im Zins, im Startjahr per
Konstruktion genau 10.000, positiv für jeden positiven Nenner, ohne Kappung. **Die Schranke
sitzt am Instrument und nicht am Kurs:** Der Leitzins hat eine Untergrenze, und sie ist
`1 − aufschlag`. Damit ist der Nenner nie null und nie negativ, und der Jahrgangsbau kann
sie prüfen — der historische Politikpfad muss sie einhalten, sonst ist der Parametersatz
für diesen Jahrgang unzulässig.

**Das ist eine echte Bedingung und keine formale, und sie trifft genau dieses Fenster.** Die
EZB senkte ihren Einlagesatz am 2014-06-11 erstmals unter null auf **−0,10 %** und bis
September 2019 auf **−0,50 %**; negativ blieb er bis 2022
(`ecb.europa.eu/press/pr/date/2014/html/pr140605_3.en.html` und
`ecb.europa.eu/stats/policy_and_exchange_rates/key_ecb_interest_rates/html/index.en.html`,
abgerufen 2026-09-01). Deutschland folgt dem Euroraum über die ganze Partie exogen — der
Bruch 1999 liegt vor dem Fenster 2001–2021 —, also liegt der negative Zins ab 2014
**im Prüfjahrgang**, und zwar in dessen Runden 13 bis 20. Ob die Zinsreihe, die der Jahrgang
zieht, den Einlagesatz oder den Hauptrefinanzierungssatz führt, entscheidet der
Jahrgangsbau; die Untergrenze muss
in beiden Fällen unter dem Minimum der Reihe liegen, und `aufschlag` ist damit nicht frei
wählbar, sondern nach unten gebunden.

Zwei Eigenschaften, die dabei geschenkt entstehen und die ich behalte. Erstens ist die
Zinsempfindlichkeit **implizit und länderverschieden**: Bei niedrigem Zins reagiert der
Kurs stark, bei hohem schwach — ein deutscher Bestand hängt am Zins, ein brasilianischer
kaum. Das kostet keinen Parameter und unterscheidet zwei der vier Länder um eine weitere
Achse. Zweitens ist die Anleihe die einzige Anlage, die der Fonds **ohne Einfluss** halten
kann; sie kann deshalb nie allein gewinnen, weil das Mandat zwei Hälften hat. Eine
Zinswette ist ein Weg, Kapital aufzubauen, und nie ein Weg, das Spiel zu gewinnen.

#### Wo die Skalengrenze liegt

`korbwert`, `anleihewert`, `waehrungswert`, `stufenwert`, `korbbestand`, `schuld` und
`markt.wert` sind **volkswirtschaftliche Beträge** und stehen in deren Skala (T5, Zeile 109).
`positionswert`, `beteiligung_wert`, Kasse und Hebel sind **Fondsgeld** (Zeile 108). Die
Umrechnung liegt genau auf dieser Grenze und findet **je Bewertung einmal statt, am äußersten
Aufruf** — also nachdem die Anteile verrechnet sind, nicht davor. `marktanteil` überquert die
Grenze gar nicht: Zähler und Nenner stehen beide in der volkswirtschaftlichen Skala.

Der zweite Weg, den der Prüfer offengelassen hat — `korbwert` gleich in Fondsgeld führen —
ist damit ausgeschlossen, und der Grund ist T33: Der Marktkorb bewertet dieselben zwölf
Körbe, und er ist eine volkswirtschaftliche Größe. Zwei Skalen für einen Korb wären zwei
Bewertungen für einen Korb, und T47 verlangt „eine Bewertung, nicht zwei". **Welche
Funktion die Umrechnung leistet, ist Sache des Architekten; dass sie an dieser Stelle und
nur dort steht, ist Entwurf.**

#### Keine neue Adresse

Keine Größe dieses Abschnitts ist eine Zustandsadresse. `korbwert`, `anleihewert`,
`waehrungswert`, `stufenwert`, `korbbestand`, `anleihekurs`, `schuld`, `bip` und
`handelsvolumen` sind Funktionen des Zustands; `stufenweite`, `aufschlag` und
`leitzins_start` sind Parameter beziehungsweise Konstanten des Jahrgangs. `marktanteil` ist
die einzige Adresse, die überhaupt vorkommt, und sie steht schon in T15.

**Die 310 aus `technik.md` T15 bleiben damit unverändert, die Tabelle *Größen ohne
Datenanker* bekommt keine neue Adresse — nur drei genauere Regeln —, und der Abzählschritt
aus T45 geht unverändert auf.** Genau deshalb hat er die Lücke auch nicht gefunden: Sie lag
außerhalb der Menge, über die er zählt. Der Abzählschritt prüft Adressen; diese Lücke war
eine fehlende **Funktion**, und dagegen hilft nur, dass jemand die Formel hinschreibt.

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

Bis zum 2026-09-05 hatte dieser Entwurf **zwei Achsen zu einer verschmolzen**: wo der Spieler
Politik verschieben kann, und wo sein Fonds etwas halten kann. Beides war `L = 4`. Damit sah
„mehr Welt" aus wie „mehr Länder zum vollen Preis" — und ein Hedgefonds, der nur in vier
Ländern etwas halten kann, ist kein globaler Hedgefonds, gleichgültig wie gut das Makromodell
darunter rechnet. Ein echter Fonds kauft japanische Aktien, ohne die Bank of Japan zu
bestechen.

**Die beiden Achsen werden getrennt.** Die Welt hat ab hier drei Schichten.

### Die drei Schichten, mit ihren Feldern und ihren Rechten

| Schicht | Einheiten | Felder je Einheit | handelbar | beeinflussbar | im Rückvergleich | Handelszeile |
|---|---:|---:|---|---|---|---|
| **1 Politikland** | 4, nach 0118 neun | **58** = 44 + 5 Steckplätze + 6 Beteiligungsfelder + 3 Nachahmerzähler, dazu seine Handelszeilen | ja | **ja** | **ja**, als Rückvergleichsland | ja |
| **2 Börsenplatz** | `B = 3·(L+1)`, bei `L = 9` **30** | **4** + 1 Steckplatz | **ja** | **nein** | **nein** | **nein** |
| **3 Restwelt** | 1 | Sektor- und Aggregatgrößen, keine Instrumente | nein | nein | nur im Handelsblock | ja |

**Warum es Schicht 1 gibt:** Sie ist der einzige Ort, an dem eine Wirkungskette *beginnt* —
ohne Politikinstrumente gäbe es nichts zu lobbyieren und nichts, dessen Folge man erklären
könnte. Sie ist teuer, tief und deshalb knapp.

**Warum es Schicht 2 gibt:** Damit das investierbare Universum wachsen kann, ohne dass die
Handelsmatrix mitwächst. Ein Börsenplatz ist ein **Finanzpreis, keine Volkswirtschaft** — er
hat keine Sektoren, keinen Kapitalstock, keine Beschäftigung, keine Staatsfinanzen und keine
Handelszeile. Genau daran hängt der Unterschied zwischen 890 und 87.788 Feldern.

**Warum es Schicht 3 gibt:** Sie schließt den Kreislauf. Ohne sie wäre die Summe der
Handelsbilanzen zwangsläufig null, was gegen die echten Daten falsch ist. Neu ab hier ist nur,
dass die Restwelt **Ankergebiet dreier Börsenplätze** wird — sie selbst bleibt unhandelbar und
ohne Instrumente, aber der Fonds kann über diese drei Plätze eine Sache halten, die **kein
Instrument der Welt bewegt**. Das ist die einzige Anlage im Modell, bei der Lobbyismus
prinzipiell nicht hilft, und sie ist deshalb der Prüfstein für die Frage, ob Einfluss überhaupt
etwas wert ist.

### Was ein Börsenplatz trägt — vier Felder, jedes mit seinem Grund

Ein Feld, das keinen Grund hat, ist eine Adresse zuviel. Deshalb steht je Feld dabei, was
ohne es kaputtginge.

| Feld | Klasse | Startwert | Warum es eine Adresse ist und keine Funktion |
|---|---|---|---|
| `index[b]` | 5 (Index) | 10.000 | Der Platz braucht ein **eigenes Gedächtnis**, sonst ist er in jeder Runde eine Momentaufnahme der Sektorpreise seines Ankers — und zwei Plätze mit ähnlichem Anker liefen für immer im Gleichschritt. Ohne dieses Feld ist die Schicht Dekoration. |
| `wechselkurs[b]` | 5 (Index) | 10.000 | **Ohne ihn ist ein Börsenplatz eine Linearkombination vorhandener Steckplätze** — aus den drei Sektorkörben seines Ankers und dessen Währung. Dieses Feld und das nächste sind die beiden, die den Platz aus dem Aufspann des Bestehenden herausholen. |
| `zins[b]` | 3 (Basispunkte) | `zielzins(b)` des Startjahrs | Der **Diskontkanal**, den kein Land×Sektor-Korb hat: Ein Korb ist Menge mal Sektorpreis, ein Platz ist zusätzlich abgezinst. Ohne ihn trennt keine Zinsbewegung Platz und Korb. |
| `nachahmer[b]` | ganzzahlig, gedeckelt | 0 | **Gegenkraft 4 muss die neue Schicht erreichen.** Ohne diesen Zähler wären 30 Plätze ein Versteck vor genau der Gegenkraft, die Maß 3 trägt — und die Schicht machte das Spiel leichter statt reicher. |

Dazu **ein Positionssteckplatz je Platz** — „handelbar" heißt genau das und nicht mehr. Also
**fünf Adressen je Börsenplatz**.

**Was ein Börsenplatz ausdrücklich nicht trägt:** keine Politikinstrumente, keinen Druck,
keinen Gegendruck, keine Restverzögerung, keine Zustimmung, keinen Aufsichtszähler, keinen
Einfluss, keine Beteiligung, keine Handelszeile, keine Sollreihe. Die Beteiligung fehlt nicht
aus Sparsamkeit: Sie ist nach *Die Aktionen* der einzige Weg zu billigem Lobbying, und ein
Platz, an dem man sich beteiligen könnte, wäre beeinflussbar und damit kein Platz mehr,
sondern ein billiges Land.

### Woran ein Börsenplatz hängt, und was ihn eigenständig macht

Ein Index, der sich unabhängig von allem bewegt, ist Dekoration; einer, der nur mitläuft, ist
eine Kopie. Hier ist die Kopplung, als Rechenvorschrift und nicht als Adjektiv.

**Jahrgangskonstanten je Platz `b`** (keine Zustandsadressen, wie `durchgriff` und
`leitzins_start` auch):

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

**Funktionen des Zustands** (ebenfalls keine Adressen, wie `anleihekurs` und `landespreis`):

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

**Zwei Sonderfälle der Restwelt, beide aus demselben Grund.** Sie hat keinen Leitzins und
keinen Wechselkurs — sie trägt keine Politikinstrumente, und ihre Aggregatgrößen sind ein
Residuum. Ihre drei Plätze zinsen deshalb mit dem `weltzins` ab und notieren im **Numéraire**
(`zielkurs = 10.000`). Das ist keine Verlegenheitslösung, sondern die richtige Lesart: Ein
Korb, der den Rest der Welt abbildet, hat keine eigene Währung, gegen die man ihn stellen
könnte. **Keine der beiden Formeln liest damit eine Restweltadresse, deren Existenz dieser
Entwurf nicht belegen kann.**

**Die Schreibregel, je Platz genau einmal je Runde**, in Schritt 4 (Wirtschaft) — außer
`nachahmer[b]`, der wie jeder Nachahmerzähler in Schritt 5 geschrieben wird:

```
zins[b]        ← teile_gerundet( zins[b]        + zielzins(b), 2 )
wechselkurs[b] ← teile_gerundet( wechselkurs[b] + zielkurs(b), 2 )
index[b]       ← teile_gerundet( mal_geteilt(leitkurs(b), zinsfaktor(b), 10.000)
                                 + index[b], 2 )
                 danach der Nachahmer- und der Stoßaufschlag nach denselben Regeln wie
                 beim Land×Sektor-Korb, mit nachahmer[b] und boersenwert(b) an der Stelle
                 von nachahmer[l][s] und korbwert(l,s)
```

**Die fünf Einflüsse, aufgezählt statt umschrieben.** Woran der Preis eines Platzes hängt:

1. **Die Sektorpreise seines Ankergebiets**, gewichtet mit `sektorgewicht[b]`. Das ist der
   Durchgriff des Handels: Ein Zollschritt in irgendeinem Politikland bewegt über die
   Markträumung den Weltpreis, der Weltpreis über `durchgriff` die Sektorpreise des Ankers,
   und die den Platz. Die Kette, die das Spiel verkauft, reicht damit bis in die zweite
   Schicht.
2. **Der Leitzins seines Ankergebiets**, zur Hälfte.
3. **Der Weltzins**, zur anderen Hälfte — der kapitalstockgewichtete Mittelwert aller
   `L` Leitzinsen. Ein Zinsschritt in Land A erreicht damit **jeden** Platz, auch die mit
   Anker B.
4. **Der Wechselkurs seines Ankergebiets**, zur Hälfte; die andere Hälfte ist der Numéraire.
5. **Der Andrang** — Nachahmer und der eigene Preisstoß des Fonds.

**Und was ihn eigenständig macht, sind drei Dinge, alle drei aus Regeln und keines aus einem
Zahlenwert:**

- **Die Trägheit.** `index[b]`, `zins[b]` und `wechselkurs[b]` gehen je Runde nur **halb** auf
  ihr Ziel zu. Ein Platz, der hochgelaufen ist, bleibt oben, auch wenn die Fundamentaldaten
  seines Ankers schon zurückgefallen sind. Das ist dieselbe Preisträgheit, mit der
  `landespreis` begründet ist, dreimal angewandt.
- **Die Mischung.** Ein Korb ist ein Sektor, ein Platz ist alle drei mit einem Schwerpunkt.
  Über Plätze zu streuen ist deshalb etwas anderes, als über Körbe zu streuen — und über
  Plätze **verschiedener Anker** zu streuen ist wieder etwas anderes, weil der dritte Einfluss
  oben — der `weltzins` — sie trotzdem zur Hälfte koppelt. **Vollständig diversifizieren kann man nicht, gar nicht
  diversifizieren aber auch nicht.** Genau deshalb ist Diversifikation hier eine
  Entscheidung und kein Etikett.
- **Die halbe Bindung an den Numéraire.** Im Beharrungswert liegt die Abweichung eines
  Platzkurses von 10.000 bei genau der Hälfte der Abweichung seiner Ankerwährung — er schwankt
  halb so weit. Der Platz ist damit die **ruhige** Art, ein Land zu halten —
  und die Währung des Landes bleibt die laute. Zwei Steckplätze, dieselbe These, verschiedenes
  Risiko.

**Vier Proben, die ohne Rechnung aufgehen und die der Jahrgangsbau mechanisch prüfen kann:**

1. **Im Startjahr steht die ganze Schicht auf ihrem Fixpunkt.** Alle Sektorpreise starten bei
   10.000, also ist `leitkurs(b) = 10.000`; `zins[b] = zins_start[b] = zielzins(b)`, also ist
   `zinsfaktor(b) = 10.000`; alle Wechselkurse starten bei 10.000, also ist
   `zielkurs(b) = 10.000`. Alle drei Halbierungen bilden ihren eigenen Wert ab, und
   `index[b] = 10.000` ist die Startbedingung, nicht eine gesetzte Zahl.
2. **Der Nenner von `zinsfaktor` wird nie null.** `zins[b]` ist ein wiederholtes Mittel aus
   Werten, die alle nicht unter der Leitzins-Untergrenze `1 − aufschlag` liegen — und die
   steht schon im Entwurf, wegen `anleihekurs`. Also ist `zins[b] + aufschlag ≥ 1`. **Die
   Schicht braucht keine neue Schranke**, sie erbt die vorhandene.
3. **Der Nenner von `boersenwert` wird nie null.** `wechselkurs[b]` ist ein wiederholtes
   Mittel zweier strikt positiver Zahlen und damit strikt positiv — dasselbe Argument wie für
   `wechselkurs[l]`.
4. **`index[b]` läuft nicht weg.** Es ist ein Mittel aus einem Fundamentalwert und sich
   selbst, liegt also stets zwischen dem laufenden Minimum und Maximum des Fundamentalwerts.
   Der reine Trägheitsanteil eines Stoßes klingt mit `(1/2)^k` ab: nach fünf Runden sind
   **3 Prozent** übrig.

**Zwei neue Schlüssel in `parameter.toml`, und keiner mehr:** `kippung` (wie stark ein Platz
auf seinen Leitsektor gekippt ist) und `platzanteil` (welcher Anteil des Ankerkapitalstocks
die Tiefe eines Platzes ist). `aufschlag` wird **wiederverwendet**, nicht verdoppelt — ein
zweiter Aufschlag erzeugte keine Wirkung, die der erste nicht auch erzeugt.

**Warum diese beiden Zahlen Parameter sind und die drei Halbierungen Literale:** Ein Maß liest
sie. `kippung` setzt den Abstand zwischen den drei Plätzen eines Ankers, und genau den misst
Maß 2; `platzanteil` setzt, wie groß der Fonds auf einem Platz werden kann, und das misst
Maß 3 über den Preisstoß. Die Halbierungen liest kein Maß — sie zu kalibrieren gäbe der Suche
drei Achsen, deren Wirkung `kippung` und `platzanteil` ohnehin erzeugen.

### Wie viele Plätze — und warum die Zahl eine Formel ist

**`B = 3 · (L + 1)`.** Je Gebiet — die `L` Politikländer und die Restwelt — ein Platz je
Leitsektor. Bei `L = 9` sind das **30**.

Die Zahl ist keine Wahl, sondern eine Abzählung, und das ist ihr Vorzug: Ein Platz **ist**
das Paar `(Gebiet, Leitsektor)`. Jede Kombination kommt genau einmal vor, keine zweimal.

- **Weniger — etwa ein Platz je Gebiet, `B = L + 1 = 10`** — ließe den Leitsektor
  unausgedrückt. Der Platz wäre dann die nach Sektoranteilen gewichtete Mischung seines
  Ankers und sonst nichts, also näher an einer Kopie, als dieser Entwurf verträgt.
- **Mehr — etwa zwei Plätze je Zelle, `B = 6·(L+1) = 60`** — unterschiede den zweiten Platz
  einer Zelle vom ersten nur noch durch Zahlenwerte, nicht durch die Art. „Zwanzig Indizes,
  die dasselbe tun, sind ein Index", und es kostete 300 Adressen statt 150.
- **30 liegt im Band 20–40**, das das Arbeitspaket vorgibt, und trifft es nicht zufällig,
  sondern weil `3·(L+1)` bei den neun Ländern aus 0118 dort landet.

**Was daraus folgt und was ausdrücklich nicht.** Die Formel legt die **Zahl** und den
**Zuschnitt** der Plätze fest — 30 Zellen, jede mit Ankergebiet und Leitsektor. Welcher
Börsenplatz namentlich in welcher Zelle sitzt, legt sie **nicht** fest; das ist ein eigenes
Paket und hängt an der Datenlage. Dieser Abschnitt ist dessen Pflichtenheft: 30 Zellen, je
ein Name, und je Zelle die Probe, ob der gewählte Platz den Leitsektor seiner Zelle
tatsächlich trägt.

**Und die Formel ist der Grund, warum die Schicht 0116 nicht im Weg steht:** Sie ist in `L`
geschrieben, nicht in einer Ziffer. Setzt 0116 die Adressarithmetik parametrisch, kommt
`5·B = 15·(L+1)` als ein weiterer Summand hinzu, und `L = 4` ergäbe 75, `L = 9` ergibt 150.

### Was die Schicht kostet, und die drei verworfenen Wege

Gerechnet aus den Konstanten in `kern/zustand.hpp`; die Formel reproduziert für `L = 4` exakt
die heutigen 310 und für `L = 9` die 740 aus Paket 0118.

| Weg | Politikländer | Börsenplätze | Zustand | handelbare Plätze | Handelsströme |
|---|---:|---:|---:|---:|---:|
| heute | 4 | 0 | **310** | 20 | 40 |
| nur mehr Länder (0118) | 9 | 0 | 740 | 45 | 180 |
| **drei Schichten — gewählt** | 9 | **30** | **890** | **75** | **180** |
| die 30 Plätze als Länder — verworfen | 39 | 0 | 5.420 | 195 | **3.120** |
| alle Länder der Welt — verworfen | 195 | 0 | **87.788** | 975 | **76.440** |

**Der Sprengsatz ist die Handelsmatrix.** Sie wächst mit `G·(G−1)·2` über `G = L + 1`
Gebiete:

| Politikländer | Handelsströme |
|---:|---:|
| 4 | 40 |
| 9 | 180 |
| 30 | 1.860 |
| 39 | 3.120 |
| 195 | **76.440** |

**Die entscheidende Zahl steht nicht in der Summe, sondern im Verhältnis.** Ein zusätzliches
Politikland kostet am Rand `44 + 40 + 3 + 5 + 6 = 98` Felder für **fünf** handelbare
Steckplätze, also rund **20 Felder je handelbarem Platz**. Ein Börsenplatz kostet **fünf**
Felder für **einen** Steckplatz. **Der Platz ist je handelbarem Steckplatz rund viermal
billiger als das Land** — und das ist die ganze Begründung der Schicht, in einer Zahl.

**Verworfen: alle 195 Länder der Welt.** Nicht „später", sondern ein anderes Produkt.
**87.788 Zustandsfelder, 76.440 Handelsströme und 195 × 19 = 3.705 lizenzgeprüfte
Datenreihen** — Paket 0118 rechnet 19 Reihen und 2 Lizenzstellen je zusätzlichem Land, das
sind hier 390 Lizenzstellen. Zum Vergleich: Dieser Entwurf führt heute 27 Sollreihen. Der
Rückvergleich hätte nach der Zählung `4 · R` **780** Prüfgegenstände statt sechzehn (dieselbe
Formel, die für vier Länder 16 ergibt), die Markträumung liefe über 76.440 Ströme statt 40,
und das
Laufzeitbudget der drei Selbstspielmaße — heute 9.539.200 Weltschritte — wüchse mit ihnen.
Wer die Frage erneut stellt, findet hier die Antwort, statt sie neu zu rechnen.

**Verworfen: die 30 Plätze als vollwertige Länder.** 5.420 Felder statt 890, 3.120
Handelsströme statt 180, und 30 × 19 zusätzliche Datenreihen — für dieselben 30 handelbaren
Steckplätze. Man bekäme dafür, dass man die Plätze auch beeinflussen könnte; genau das soll
man aber nicht, siehe unten.

**Verworfen: ein Börsenplatz mit Handelszeile.** Er wäre dann keine zweite Schicht, sondern
ein billiges Land — und die Matrix wüchse mit `G²`, also genau der Größe, wegen der die
Schicht überhaupt existiert.

### Warum die Plätze handelbar sind und nicht beeinflussbar

Das ist keine Sparmaßnahme, sondern die Aussage der Schicht.

**Ein Börsenplatz füttert keinen Aufsichtszähler.** Gegenkraft 1 liest globale Sichtbarkeit
mal lokalen Fußabdruck, und der Fußabdruck ist Einfluss mal Positionsanteil am Sektor. Auf
einem Platz hat der Fonds keinen Einfluss und steht in keinem Sektor eines Landes; sein
Bestand dort geht in keinen Zähler ein. **Die zweite Schicht ist der Ort, an dem der Fonds
groß werden kann, ohne beobachtet zu werden.**

**Und genau deshalb kann er dort nie gewinnen.** Das Mandat hat zwei Hälften — Vermögen
**und** Einfluss in mindestens zwei Ländern. Börsenplätze liefern die erste und **null** von
der zweiten. Sie sind damit dieselbe Art Gegenstand wie die Staatsanleihe, von der schon
dasteht: *„Eine Zinswette ist ein Weg, Kapital aufzubauen, und nie ein Weg, das Spiel zu
gewinnen."* Die zweite Schicht ist der zweite solche Weg, dreißigmal so breit.

**Der Fonds kann die Plätze trotzdem bewegen — nur nicht bei ihnen.** Er lobbyiert den
Leitzins eines Ankers und trifft dessen drei Plätze über `zielzins` und alle dreißig über
`weltzins`; er lobbyiert einen Zoll und trifft über Weltpreis und `durchgriff` die Sektorpreise
seines Ankers und damit dessen `leitkurs`. **Wirkung ja, Zugriff nein** — das ist eine
schärfere Aussage als „unbeeinflussbar" und die interessantere.

### Die Gegenkräfte auf der neuen Schicht

Die fünf Gegenkräfte bleiben fünf. Was sich ändert, ist ihre Reichweite, und die gehört einzeln
hingeschrieben, weil eine neue Fläche ohne Gegenkraft der schnellste Weg zurück zu der
Rückkopplung ist, die dieses Genre tötet.

| Gegenkraft | erreicht die zweite Schicht? | wie |
|---|---|---|
| 1 Aufsicht | **nein, und das ist entschieden** | Kein Einfluss, kein Fußabdruck, kein Zähler. Der Preis dafür ist das Mandat. |
| 2 Politische Gegenreaktion | mittelbar | Über den Anker: Ein Regierungswechsel stellt dessen Instrumente zurück, das bewegt `leitkurs` und `zielzins`. |
| 3 Marktenge | **ja, und stärker als in Schicht 1** | Siehe unten. |
| 4 Nachahmer | **ja** | `nachahmer[b]`, dieselbe Regel wie beim Korb. |
| 5 Gegenlobby | nein | Ein Platz hat kein Instrument, an dem sich Gegendruck bilden könnte — dasselbe Argument wie bei der Restwelt. |

**Gegenkraft 3 ist die, die mit dem Erfolg wächst, und sie wächst auf der neuen Schicht
schneller.** Zwei Mechanismen, beide ohne neue Regel:

- **Plätze sind flacher als Länder.** `tiefe[b]` ist ein Anteil `platzanteil` des
  Ankerkapitalstocks, also kleiner als jeder Land×Sektor-Korb desselben Gebiets. Der Preisstoß
  aus Aktion 1 wächst mit dem Anteil des Fonds am Markt — auf einem flacheren Markt ist
  derselbe Betrag ein größerer Anteil. **Die Schicht, auf der man unbeobachtet groß werden
  kann, ist zugleich die, auf der die eigene Größe am schnellsten wehtut.**
- **Der Marktkorb wird breiter.** Die Marktrendite aus Gegenkraft 3 ist die wertgewichtete
  Rendite **aller handelbaren** Körbe und Anleihen; die dreißig Plätze gehören dazu, sonst
  wäre ein handelbarer Gegenstand außerhalb des Vergleichsmaßstabs eine geschenkte
  Überrendite. Die Latte, über die der Fonds springen muss, steigt also mit der Schicht — und
  „breit mitlaufen" wird noch weniger tragfähig, als es war.

**Zwei Gegenkräfte greifen damit auf der neuen Schicht, beide wachsen mit dem Erfolg, und eine
greift ausdrücklich nicht.** Das ist die ehrliche Bilanz; sie steht so hier, damit der
Bruchtester weiß, wo er zu suchen hat.

### Was die Schicht für die vier Maße bedeutet

**Maß 1 — Entscheidungsdichte.** Die handelbaren Steckplätze steigen von 20 auf **75**: 45 aus
der Ländergeometrie bei `L = 9` und 30 aus dieser Schicht. Die Aktionszahl bleibt bei drei je
Runde — der Betreiber hat am 2026-09-05 Weg A gewählt, die Steckplätze wachsen mit. **Die
Rechnung, wie die Entscheidungsdichte dabei erhalten bleibt, gehört in Paket 0118, und sie muss
beide Zuwächse tragen, nicht nur die 45 aus den Ländern.** Die Zahl, auf der sie zu rechnen
hat, ist die 75 aus diesem Abschnitt, gegen die 20 von heute. Was hier dazugehört und dort
nicht wiederholt werden muss: Maß 1 zieht je Runde 30 Bündel aus der Liste der **zulässigen
Aktionen**, und diese Liste wächst mit den Steckplätzen. Die offene Frage *„Wie fein der
Aktionsraum sein darf"* war bisher empirisch am Prototyp zu klären; mit 75 Plätzen ist sie
**bindend**, und ihre Prüfform steht schon da — `Dichte(t)` bei `K = 30` gegen `K = 60`.

**Maß 2 — Strategievielfalt.** Die 126 Profile bleiben 126: Ein Börsenplatz ist ein Ziel
innerhalb der Familie 1 (Position), keine sechste Aktionsart und keine vierte Familie. Die
Schicht vergrößert also die Auswahl **einer** der drei Familien, und das ist der Einwand, den
man dagegen erheben muss. **Er trägt nicht, und der Grund ist die Bauart und nicht die
Kalibrierung:** Plätze liefern kein Gramm Einfluss, und die zweite Hälfte des Mandats verlangt
Einfluss in zwei Ländern. Familie 1 bekommt damit eine höhere Decke für **Kapital** und
keinen Zentimeter mehr für den **Sieg**. Was die Schicht dagegen wirklich verschiebt, ist die
zweite Abnahmehälfte `max(Ek) ≤ 1,25 · min(Ek)` — sie ist ab hier die scharfe Bedingung, und
sie ist der Ort, an dem eine zu große `platzanteil`-Kalibrierung sichtbar wird.

**Maß 3 — Verschiebung des Optimums.** Hier gewinnt der Entwurf am meisten, und zwar an einer
Stelle, an der er seit dem 2026-09-03 offen ausgewiesen schwach war. Mit dem Fenster 2001–2021
ist der Euro-Übergang weggefallen, die einzige Sperre, die während einer Partie zuschnappte;
seither trugen Maß 3 **zwei** Quellen, Nachahmer und Preisstoß, und dieser Entwurf hat
ausdrücklich hingeschrieben, dass ein Scheitern daran ein Befund über diese beiden wäre. **Die
zweite Schicht ist die dritte Quelle, und sie kommt aus einer Regel statt aus einer Zahl:** Am
Partieanfang hat der Fonds keinen Einfluss, also ist der unbeobachtete, flache, breite
Platzmarkt der effiziente Weg, Kapital aufzubauen; gegen Partieende bindet die zweite
Mandatshälfte, und Kapital muss in Beteiligungen und Lobbydruck **in Politikländern**
umgeschichtet werden — wo es sofort Aufsicht und Gegenlobby weckt. Das ist eine überprüfbare
**Vorhersage** und keine Absichtserklärung: Das Frühfensteroptimum `p*` sollte Gewicht auf
Aktionsart 1 tragen, das Spätfensteroptimum `q*` auf 2 und 3. Trifft sie nicht ein, ist das
ein Befund über diesen Abschnitt.

**Maß 4 — Rückvergleich.** Er ändert sich **nicht**, und zwar in keiner seiner Zahlen.
Börsenplätze sind nach Paket 0117 **Spielländer** — *als Verweis geschrieben, nicht als
nachgemessene Tatsache: 0117 ist heute noch nicht gebaut.* Sie zählen damit nicht in den
sechzehn Prüfgegenständen, und die Schärfe des Rückvergleichs sinkt nicht: Er läuft weiter über
dieselben 23 freien Sollreihen und denselben Handelsblock aus 40 Strömen, denn ein Platz hat
keine Handelszeile. Dazu tritt eine Eigenschaft, die stärker ist als die Klassenzuordnung und
sie unabhängig davon trägt: **Die Schicht ist ein reines Blatt.** Kein Feld der ersten oder
dritten Schicht liest ein Feld eines Börsenplatzes; gelesen werden Platzfelder ausschließlich
vom Fondsteilsystem. Da dieses im `weltlauf` nicht läuft, wird die zweite Schicht dort **gar
nicht gerechnet** — ihre vier Felder je Platz behalten ihre Startwerte, so wie der Fondsblock
und die Nachahmerzähler es schon tun. Der Weltlauf kostet nach dieser Schicht keinen
Weltschritt mehr als vorher, und die Menge der je Modus geschriebenen Adressen bleibt fest.
Der Preis dieser Sauberkeit gehört dazu und steht unter *Die Grenze des Orakels*: Für die
zweite Schicht ist das Orakel vollständig blind. Es gibt zu ihr auch nichts, wogegen es prüfen
könnte — einen Weltaktienindex unter freier Lizenz gibt es nicht, das steht schon unter *Was
bewusst fehlt*, und `daten.md` führt keine einzige Kursreihe.

### Die drei Klagen, auf dieser Schicht gelesen

| Klage aus den Rezensionen | was die zweite Schicht dazu beiträgt |
|---|---|
| „the consequences of choices often feel intangible" | Die Kopplung ist eine Formel, die der Spieler in der Kette nachlesen kann: Zollschritt → Weltpreis → `durchgriff` → Sektorpreis des Ankers → `leitkurs` → `index[b]`. Eine Handlung in einem Land bewegt sichtbar einen Preis dreißig Steckplätze weiter — und weil `weltzins` alle Plätze erreicht, hat ein Zinsschritt eine Wirkung, die man **weltweit** ablesen kann, ohne dass irgendetwas erzählt würde. |
| „trying to implement the tiniest socialist policy will always result in bankruptcy" | Auf jedem Platz ist long und short dieselbe Formel mit umgekehrtem Vorzeichen. Die Schicht bringt keine politische Richtung mit; sie kann in keiner Richtung allein gewinnen, weil sie null Einfluss liefert. Sie verbreitert damit die Familie Position, ohne eine politische Linie zu belohnen. |
| „no dramatic setbacks", „broad as an ocean, but deep as a puddle" | Die Schicht ist genau die Breite, die die Klage vermisst — und sie ist mit einer Falle versehen, statt gratis zu sein: Wer auf den flachen Plätzen groß wird, bewegt den Preis gegen sich, sammelt Nachahmer und hebt zugleich die Latte des Marktkorbs, an der sein Anlegerbestand hängt. Der Rückschlag ist mechanisch und im Zustand ablesbar, wie jeder andere hier auch. |

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

**Die Abnahmeregel — 16 Prüfgegenstände, Toleranz 2.** Die zweite Fassung nannte zwei
Fehlermaße und keine Regel, wie über die Reihen zusammengefasst wird; `technik.md` T37 hat
daraus ein Gesamtmaß gelesen und die Entscheidung zurückgegeben. Hier ist sie:

1. **Abnahmerelevant sind nur die freien Reihen.** Die vier abgeleiteten Schuldenquoten
   werden berichtet und entscheiden nichts; der Leitzins ist seit dem 2026-09-03 gar keine
   Sollreihe mehr, sondern Eingabe mit Invariantenprobe. Eine Reihe, die per Konstruktion
   fehlerfrei ist, darf kein Gesamtmaß mildern.
2. **Prüfgegenstand ist nicht die Reihe, sondern die Größe.** Es sind sechzehn:

   | Prüfgegenstand | Zahl | zusammengefasst aus |
   |---|---:|---|
   | BIP je Land | 4 | je eine Reihe |
   | Sektorstruktur je Land | 4 | die **drei** Anteilsreihen des Landes, alle drei müssen bestehen |
   | Verbraucherpreise je Land | 4 | je eine Reihe |
   | Wechselkurs je Land ausser USA | 3 | je eine Reihe |
   | Handelsblock | 1 | 40 Ströme, Median des MAPE und Median der Richtungstreue; das schlechteste Fünftel wird ausgewiesen |
   | **Summe** | **16** | |

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
4. **Der Lauf ist bestanden, wenn höchstens zwei der sechzehn Prüfgegenstände reißen.**
   Jeder gerissene wird im Befund einzeln benannt, mit beiden Zahlen. Drei reißende sind
   ein Durchfallen, auch wenn sie knapp reißen.

Der Median über die 40 Handelsströme ist der Vorschlag des Architekten (`technik.md`
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
- **Ob `3·(L+1)` die Länderwahl aus 0118 überlebt.** Die Formel setzt voraus, dass jedes
  Gebiet drei unterscheidbare Leitsektoren trägt. Für ein Land, dessen Sektorstruktur stark
  von einem Sektor beherrscht wird, liegen die drei Plätze nach der `kippung`-Regel eng
  beieinander. Zu sehen ist das erst an den fünf gewählten Ländern; der Ausweg wäre nicht eine
  andere Formel, sondern eine andere `kippung`.
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
| **T37 / die 16 Prüfgegenstände** | **Unverändert.** Börsenplätze sind Spielländer (Verweis auf Paket 0117, dort zu setzen), tragen keine Sollreihe und keine Handelszeile. Der Handelsblock bleibt bei `G·(G−1)·2` über die **Gebiete**, nicht über die Plätze. |
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
