---
typ: spiel
idee: 0016-hedgefonds-simulation-echte-weltwirtschaft
erstellt: 2026-09-01
schleife: Der Spieler stellt je Runde bis zu drei Aktionen aus fünf Arten, die Welt rechnet ein Jahr weiter, und jede Zahländerung trägt die Kette ihrer Ursachen mit sich.
siegbedingung: Das Mandat — Fondsvermögen über einer Schwelle UND Einfluss über einer Schwelle in mindestens zwei Ländern — erreicht innerhalb von R Runden, ohne vorher an einer der drei Todesarten zu sterben. Ergebnis ist die Rundenzahl bis zur Erfüllung.
aktionen: 5
laender: 4 spielbar (USA, China, Deutschland, Brasilien) plus ein nicht spielbares Restwelt-Aggregat
gueter: 3 Sektoren (Landwirtschaft, Industrie, Dienstleistungen), davon 2 mit Handelszeilen
takt: 1 Runde = 1 Jahr; R = 24 Runden, Startzustand 1997, Endzustand 2021, 25 Stützstellen
gegenkraefte: 5
messbar_entscheidungsdichte: Je Runde t = 1…R und je Startwert 30 gezogene Aktionsbündel; jedes ersetzt die Bot-Aktionen der Runde t, danach spielt der Heuristikbot auf dem Referenzprofil (1,1,1,1,1) bis Runde R. Dichte(t, Startwert) = Anteil der 30 Ergebnisse, die um mehr als 1.000 Milli-Runden vom Median dieser 30 abweichen; Dichte(t) = Mittel über die 50 Startwerte. Abnahme = Mittel der Dichte(t) je Partiedrittel (1-8, 9-16, 17-24) jeweils >= 0,4.
messbar_strategievielfalt: Profil = Fünftelverteilung über die fünf Aktionsarten (126 Profile), Wirkung über das Vorratsverfahren; je Profil Suchbot über 20 Startwerte, Profilergebnis = Median. Profil gewinnt, wenn sein Median <= 24.000 liegt. Strategiekern = die stärkste der drei Familien Position/Beteiligung/Lobby; die 6 Profile ohne jede Familienaktion haben keinen Kern und zählen nicht. Abnahme = alle drei Kerne stellen mindestens einen Gewinner, und das beste Klassenergebnis ist höchstens 25 Prozent besser als das schlechteste der drei.
messbar_optimumsverschiebung: Frühfenster = Runden 1-8 mit Profil p, Rest mit Referenzprofil; Spätfenster = Runden 17-24 mit Profil p, Rest mit Referenzprofil; je 126 Profile x 20 Startwerte, Median als Profilergebnis, bestes Profil je Fenster nach kleinstem Median (Gleichstand nach Profilkennung). Verschiebung = L1-Abstand der beiden Profilvektoren geteilt durch 5, Werte aus {0; 0,4; …; 2,0}. Schwelle 0,4.
messbar_rueckvergleich: Startjahrgang 1997, R = 24 Runden im Weltlauf (Fondsteilsystem abgeschaltet), Politikinstrumente exogen auf den historischen Pfaden; 16 Prüfgegenstände aus 23 freien Sollreihen plus Handelsblock, je über 25 Stützstellen ohne Füllung. Schwellen: MAPE 20 Prozent für Niveaureihen, mittlerer absoluter Fehler 300 Basispunkte für Ratenreihen, Richtungstreue 0,6 für alle. Bestanden, wenn höchstens 2 der 16 Prüfgegenstände reißen.
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

## Die Partielänge R, und warum sie hier als Buchstabe steht

Die zweite Fassung hat die Partielänge aus einer Regel abgeleitet — *die Partielänge ist
die Länge des Fensters, in dem jede Sollreihe ohne Füllung belegt ist* — und dann eine
falsche Zahl eingesetzt. Die Regel bleibt. Die Zahl ist neu, und sie ist diesmal gemessen:

| Reihe (USA) | belegt | fehlt |
|---|---|---|
| `NV.AGR.TOTL.ZS` | 1997–2021 | 1990–1996, 2022–2024 |
| `NV.IND.TOTL.ZS` | 1997–2021 | 1990–1996, 2022–2024 |

(`api.worldbank.org/v2/country/USA/indicator/<code>?date=1990:2024`, eigener Abruf am
2026-09-01. `NV.SRV.TOTL.ZS` folgt derselben Abgrenzung und damit demselben Fenster.)

CEPII BACI (HS92) beginnt 1995 und reicht bis 2024
(`cepii.fr/CEPII/en/bdd_modele/bdd_modele_item.asp?id=37`, abgerufen 2026-08-31). Der
Schnitt aus beidem ist **1997 bis 2021**, also **25 Stützstellen und R = 24 Runden**.

**Und die eigentliche Lehre steht nicht in der Zahl, sondern in ihrer Fassung.** Die
zweite Fassung hat `28` in jede abgeleitete Größe geschrieben — Ergebnisskala,
Partiedrittel, Fenstergrenzen, Kostenformeln. Eine einzige falsche Messung machte damit
zwölf Zahlen falsch. **Deshalb steht in diesem Entwurf jede abgeleitete Größe als Formel
in R, mit R = 24 eingesetzt.** Misst der Jahrgangsbau an einer Reihe, die ich nicht
geprüft habe, ein engeres Fenster — die chinesische und die brasilianische Leitzinsreihe
der neunziger Jahre sind der von `technik.md` T24 selbst benannte Verdachtsfall —, dann
ist R zu ersetzen und sonst nichts. Kein Paket ist dann zweimal zu bauen.

Der Zuschnitt kostet vier Runden und gewinnt zwei Dinge. Er schneidet **Brasiliens
Disinflation 1995–1997** ab, die in der zweiten Fassung als schärfster Punkt des
Rückvergleichs offenstand. Und er enthält weiterhin jeden Bruch, der etwas prüft: den
Euro-Beginn 1999 (Ende Runde 2), Chinas WTO-Beitritt 2001 (Ende Runde 4), 2008 (Ende
Runde 11) und den Einbruch 2020 (Ende Runde 23).

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

1. **Position.** Long oder short auf ein Land×Sektor, auf eine Währung oder auf die
   Staatsanleihe eines Landes. In festen Stufen, sofort wirksam, jederzeit auflösbar.
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
| Leitzins | ja (IWF IFS) | Für Deutschland **exogen ab 1999**, also ab Runde 3. Diese Asymmetrie ist gewollt, siehe unten. |
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
abgerufen 2026-09-01). Deutschland folgt dem Euroraum ab Runde 3 exogen, also liegt der
negative Zins **im Prüfjahrgang**. Ob die IFS-Reihe, die der Jahrgang zieht, den Einlagesatz
oder den Hauptrefinanzierungssatz führt, entscheidet der Jahrgangsbau; die Untergrenze muss
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

Der Preiskanal `Sektorpreis(t−1) → landespreis → Sektorpreis(t)` ist dagegen **kein eigener**:
Er ist Kanal 3 in seinem Preisglied, ausgeschrieben. Seine Dämpfung ist der Anteil
`(10.000 − durchgriff)/10.000`, also strikt kleiner als eins, solange `durchgriff > 0`;
für Dienstleistungen mit `durchgriff = 0` ist er eine reine Fortschreibung ohne
Verstärkung.

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
(Exportüberschuss und **kein eigener Zinshebel ab Runde 3** — die einzige Asymmetrie, die
einen Aktionsraum schließt und damit einen anderen erzwingt), **Brasilien** (Agrarexport,
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
Reihe je Land durch die Normierung festliegt, sind von den 31 Sollreihen **27
unabhängig** — ausgewiesen werden trotzdem alle 31.

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
Wer etwas durchsetzt, schädigt einen anderen Sektor — und dessen Gegenbudget wächst
proportional zum erlittenen Schaden. Je stärker man in eine Richtung verschiebt, desto
teurer wird der nächste Schritt in dieselbe Richtung. Die Rückkopplung, die im Genre nach
oben läuft, läuft hier gegen sich selbst.

## Wie die vier Masse berechnet werden

Alle vier laufen im Selbstspiel ohne Darstellung über dieselbe Zustandsschnittstelle. Was
hier steht, ist eine Rechenvorschrift; wo eine Wahl offenbliebe, ist sie hier getroffen.
Jeder Gleichstand wird nach Aktions- beziehungsweise Profilkennung gebrochen, nie nach
Auffindereihenfolge. Der Median über eine gerade Anzahl ist der kleinere der beiden
mittleren Werte. **R = 24.**

### Die Ergebnisgröße einer Partie

Ein `i64` in Milli-Runden, **kleiner ist besser**, streng geordnet und ohne Sammelwert:

| Ausgang | Wert | Bereich bei R = 24 |
|---|---|---|
| Mandat in Runde r erfüllt | `r × 1.000` | 1.000 … 24.000 |
| R Runden überlebt, Mandat nicht erfüllt | `(R+1) × 1.000 + v + e`, siehe **Der Fehlbetrag** | 25.000 … 28.000 |
| an einer Todesart in Runde d gestorben | `30.000 + (R + 1 − d) × 1.000` | 31.000 … 54.000 |

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
`0 ≤ v + e ≤ 3.000` und das Band 25.000 … 28.000 — nachgerechnet und nicht verordnet. Die
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
breitere Band kostet keine Runde Partielänge. Bei R = 24 sind die unerreichbaren Lücken
24.001 … 24.999 und **28.001 … 30.999**.

**Die Kante aus Befund 10 ist damit geschlossen:** Das Band 1.000 … 24.000 heißt genau
„Mandat erfüllt", der überlebte Misserfolg beginnt bei 25.000, und kein Wert trägt zwei
Bedeutungen. Der frühe Tod ist schlechter als der späte, und zwar um volle Runden — genau
die Auflösung, die Maß 1 im letzten Partiedrittel braucht. Eine Sammelkappe auf den
Gesamtwert gibt es **nicht**. Der Bereichstest lautet: ein Ergebnis ausserhalb
1.000 … 54.000 ist ein harter Fehler.

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
`1…⌊R/3⌋`, `⌊R/3⌋+1…⌊2R/3⌋`, `⌊2R/3⌋+1…R`, bei R = 24 also **1-8, 9-16, 17-24** —
jeweils **≥ 0,4**, nicht nur über die ganze Partie. Ein Spiel, das nur in der Mitte lebt,
fällt hier durch. Fällt es durch, ist „the consequences of choices often feel intangible"
gerade gemessen worden.

**Kosten.** Ein Bündel in Runde `t` kostet die Runden `t … R`, also `R + 1 − t`
Weltschritte — Maß 1 misst die Entscheidung **der Runde t**, deshalb wird sie mitgerechnet.

```
je Startwert:  30 · Σ(R+1−t) für t = 1…R  =  30 · R(R+1)/2  =  30 · 300 =  9.000
               zuzüglich Trägerpartie R                                 =     24
                                                                          ------
                                                                           9.024
50 Startwerte:                                                           451.200
```

### Maß 2 — Strategievielfalt

**Eingabe:** alle 126 Profile, je 20 Startwerte, Suchbot.

Das Profilergebnis `E(p)` ist der Median der 20 Partieergebnisse. Ein Profil **gewinnt**,
wenn `E(p) ≤ R × 1.000 = 24.000` — also genau dann, wenn es im Median im Band „Mandat
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

**Kosten:** eine Suchbotpartie `R × (1 + 60) = 24 × 61 = 1.464`;
`126 × 20 × 1.464` = **3.689.280 Weltschritte**.

### Maß 3 — Verschiebung des Optimums

Zwei getrennte Läufe je Profil, jeder über die **volle Partie**, damit keine Runde ohne
Vorgabe bleibt. Die Fenster sind das erste und das letzte Partiedrittel aus Maß 1:

- **Frühfenster:** Runden 1-8 mit Profil `p`, Runden 9-24 mit dem Referenzprofil.
  Ergebnis `Efrüh(p)` = Median über 20 Startwerte.
- **Spätfenster:** Runden 1-16 mit dem Referenzprofil, Runden 17-24 mit Profil `p`.
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

**Kosten:** `2 × 126 × 20 × 1.464` = **7.378.560 Weltschritte**.

**Summe der drei Maße:** `451.200 + 3.689.280 + 7.378.560` = **11.519.040 Weltschritte**.
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

**Die 31 Sollreihen** sind BIP je Land (4), Sektoranteile (12, davon 8 unabhängig),
Verbraucherpreise (4), Leitzins (4), Wechselkurs gegen USD (3), Staatsschuldenquote (4);
dazu der Handelsblock über 40 Ströme als eigener Block. Jede über 25 Stützstellen ohne
Füllung. Nach der Klassifikation aus `technik.md` T37 sind die vier Leitzinsreihen
**gesetzt** (Eingabe des Laufs, Fehler null per Konstruktion) und die vier
Staatsschuldenquoten **abgeleitet**.

**Die drei Fehlermaße, je Reihe:**

| Reihen | verglichen wird | Schwelle |
|---|---|---|
| BIP (4), Sektoranteile (12), Staatsschuldenquote (4), Handelsströme (40) | das **Niveau** | MAPE über die 25 Stützstellen ≤ 20 % |
| Verbraucherpreise (4), Wechselkurs (3), Leitzins (4) | die **Jahresänderungsrate** in Basispunkten | mittlerer absoluter Fehler über die 24 Übergänge ≤ 300 bp |
| alle | die **Richtung** | Anteil der 24 Übergänge mit `sgn(Δmodell) = sgn(Δsoll)` ≥ 0,6 |

Die zweite Zeile ist die Folge von `technik.md` T8: Ein prozentualer Fehler auf einem
Index, der über zwei Jahrzehnte um eine Größenordnung wandert, misst den Anfang und nicht
die Maschine — und ein prozentualer Fehler auf einer Rate nahe null explodiert. Die 300
Basispunkte, also drei Prozentpunkte mittlerer Fehler auf der Jahresrate, haben denselben
Status wie die 20 Prozent und die 0,6: eine gesetzte Latte. Erweist sie sich als
unerreichbar, ist das ein Befund über das Modell und kein Anlass, sie zu verschieben.

**Die Abnahmeregel — 16 Prüfgegenstände, Toleranz 2.** Die zweite Fassung nannte zwei
Fehlermaße und keine Regel, wie über die Reihen zusammengefasst wird; `technik.md` T37 hat
daraus ein Gesamtmaß gelesen und die Entscheidung zurückgegeben. Hier ist sie:

1. **Abnahmerelevant sind nur die freien Reihen.** Die vier gesetzten Leitzinsreihen und
   die vier abgeleiteten Schuldenquoten werden berichtet und entscheiden nichts. Eine
   Reihe, die per Konstruktion fehlerfrei ist, darf kein Gesamtmaß mildern.
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

3. **Ein Prüfgegenstand besteht**, wenn er beide für ihn geltenden Schwellen einhält.
4. **Der Lauf ist bestanden, wenn höchstens zwei der sechzehn Prüfgegenstände reißen.**
   Jeder gerissene wird im Befund einzeln benannt, mit beiden Zahlen. Drei reißende sind
   ein Durchfallen, auch wenn sie knapp reißen.

Der Median über die 40 Handelsströme ist der Vorschlag des Architekten (`technik.md`
Abschnitt 12) und wird hiermit übernommen, mit seiner Begründung: Einzelne kleine Ströme
— Brasilien–China in der Landwirtschaft — schwanken prozentual stark, ohne dass das Modell
falsch wäre; ein Mittel ginge daran kaputt, eine Je-Strom-Schwelle schneller.

**Kosten:** R = 24 Weltschritte.

**Und die Grenze des Orakels, ausdrücklich.** Ohne Sollreihe sind: **Sektorpreise**
und **Weltpreise** (Lücke 2 des Datenkurators), **Zustimmung** (Lücke 4), das Instrument
**Finanzmarktregulierung** und die **Marktrendite**. Dazu kommt im Weltlauf das gesamte
Fondsteilsystem, das gar nicht läuft. Alle diese Größen sind im Zustand sichtbar, keine ist
vom Rückvergleich gedeckt. Er prüft die Dynamik der Maschine über den historischen
Zeitraum und sagt nichts über den Ast, den der Spieler betritt.

### Die drei Klagen und was sie beantwortet

| Klage aus den Rezensionen | Entwurfsentscheidung |
|---|---|
| „the consequences of choices often feel intangible" | **Höchstens drei Aktionen je Runde** — Knappheit zwingt jede Aktion, groß genug zum Wirken zu sein. Dazu die Kette als eigener Zustandsteil (Schritt 1 und 6) und Maß 1 als Abnahmeschwelle je Partiedrittel statt als Wunsch. |
| „trying to implement the tiniest socialist policy will always result in bankruptcy" | **Der Fonds kann long und short sein.** Damit ist keine politische Richtung dominant: Wer auf Regulierung setzt, weil er short steht, gewinnt genauso wie wer sie verhindert. Dazu die zweiteilige Siegbedingung (Kapital UND Einfluss) und Maß 2, das jede der drei Familien einzeln gewinnen sehen will. |
| „no dramatic setbacks or successes", „everything is incredibly surface level" | **Drei Todesarten mit sichtbaren Schwellen** (Zwangsliquidation, Marktverbot, Anlegerabzug), die Ergebnisskala, die den frühen Tod schlechter bewertet als den späten, und Maß 3, erzwungen durch Nachahmer und Preisstoß. Der Rückschlag ist dramatisch, aber nie willkürlich — siehe „Keine verdeckte Größe". |

## Was bewusst fehlt

- **Mehr als vier Länder und drei Sektoren.** Die Idee nannte zwölf und sechs. Zwölf Länder
  vervierfachen die Rückkopplungswege ohne ein Maß zu verbessern; sechs Sektoren gibt es
  unter freier Lizenz nicht, und aus drei aufgeteilte wären ein Konstrukt ohne Sollreihe.
- **Das verarbeitende Gewerbe als eigener Sektor.** Es wäre die interessantere Gliederung
  und ist als WDI-Reihe sogar vorhanden — aber nur als Teilmenge der Industrie. Ein
  vierter Sektor „übrige Industrie" hätte keine eigene Quellreihe und müsste als Differenz
  gebildet werden. Vier Sektoren mit einem ungedeckten, drei mit lauter gedeckten: die
  Wahl ist die zweite.
- **Startjahrgänge vor 1997**, und die Grenze liegt jetzt zwei Jahre später als in der
  zweiten Fassung. 1995 und früher bleiben als **Spieljahrgänge** möglich und sind der
  naheliegende Inhalt des Erweiterungsmodells aus der Idee. Sie tragen keinen Handelsblock
  im Rückvergleich (BACI beginnt 1995) und keine US-Sektorstruktur aus Daten; ein
  Spieljahrgang vor 1997 übernimmt als US-Startwert die Struktur von 1997 und kennzeichnet
  sie als gefüllt. Damit sind sie Spiel-, aber keine Prüfjahrgänge. Das gehört ins
  Kaufangebot geschrieben, nicht in eine Fußnote.
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
- **Bleibt das Fenster bei 1997–2021?** Geprüft habe ich die drei US-Sektoranteilsreihen
  (eigener Abruf 2026-09-01) und BACI. Offen bleibt der Verdachtsfall aus `technik.md`
  T24, die chinesische und die brasilianische **Leitzinsreihe** der neunziger Jahre: Sie
  stammt nach der Reihenliste aus IWF IFS, und `imf.org` weist den Abruf mit HTTP 403 ab
  (eigener Versuch 2026-09-01, dasselbe Verhalten, das `daten.md` schon meldet).

  **Ein Ersatzbeleg, der die Frage verkleinert, ohne sie zu schließen:** Die nächstliegende
  frei abrufbare Zinsreihe, `FR.INR.LEND` (Sollzins der Banken, WDI), trägt China lückenlos
  1995–2023 und Brasilien **1997**–2023 — 1995 und 1996 fehlen
  (`api.worldbank.org/v2/country/CHN;BRA/indicator/FR.INR.LEND?date=1995:2023`, abgerufen
  2026-09-01). Der Verdachtsfall zeigt damit genau an derselben Stelle dieselbe Kante wie
  die US-Sektoranteile, und der Schnitt auf 1997 räumt beide zugleich ab. Das ist ein
  Indiz, kein Beweis: `FR.INR.LEND` ist eine andere Reihe als der IFS-Leitzins. Zu prüfen
  bleibt sie beim Jahrgangsbau. **Misst der Jahrgangsbau ein engeres Fenster, ist R zu
  ersetzen und sonst nichts**; jede abgeleitete Zahl dieses Entwurfs steht als Formel in R
  daneben.
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
- **Ob die Schwellen von Maß 4 mit endogener Produktivität überhaupt erreichbar sind.**
  Unverändert das größte ungemessene Risiko des Vorhabens. Es ist keine Entwurfsfrage
  mehr, sondern eine Messung des Rückvergleichers am laufenden Kern — die Abnahmeregel
  steht jetzt, also lässt sich das Ergebnis überhaupt beurteilen.

## Was der Architekt neu rechnen muss

Nur damit es nicht gesucht werden muss. Alles Übrige an `technik.md` bleibt gültig.

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

### Aus Fassung 4 — vom Architekten am 2026-09-01 erledigt

Steht nur noch als Nachweis hier; alle vier sind in `technik.md` Fassung 5 nachgeführt und
vom Prüfer der Runde 6 einzeln nachgerechnet worden.

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

Steht nur noch als Nachweis hier; nichts davon ist offen.

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
