---
typ: spiel
idee: 0016-hedgefonds-simulation-echte-weltwirtschaft
erstellt: 2026-08-31
schleife: Der Spieler stellt je Runde bis zu drei Aktionen aus fünf Arten, die Welt rechnet ein Jahr weiter, und jede Zahländerung trägt die Kette ihrer Ursachen mit sich.
siegbedingung: Das Mandat — Fondsvermögen über einer Schwelle UND Einfluss über einer Schwelle in mindestens zwei Ländern — erreicht innerhalb von 28 Runden, ohne vorher an einer der drei Todesarten zu sterben. Ergebnis ist die Rundenzahl bis zur Erfüllung.
aktionen: 5
laender: 4 spielbar (USA, China, Deutschland, Brasilien) plus ein nicht spielbares Restwelt-Aggregat
gueter: 3 Sektoren (Landwirtschaft, Industrie, Dienstleistungen), davon 2 mit Handelszeilen
takt: 1 Runde = 1 Jahr; Standardpartie 28 Runden, Startzustand 1995, Endzustand 2023
gegenkraefte: 5
messbar_entscheidungsdichte: Je Runde t 30 gezogene Aktionsbündel, jedes von diesem Zustand aus bis Runde 28 mit dem Heuristikbot auf dem Referenzprofil (1,1,1,1,1) und identischem abgeleitetem Startwert nachgespielt; Dichte(t) = Anteil der Bündel, deren Ergebnis um mehr als 1.000 Milli-Runden vom Median abweicht. Abnahme = Mittel der Dichte(t) je Partiedrittel (1-9, 10-19, 20-27) jeweils >= 0,4.
messbar_strategievielfalt: Profil = Fünftelverteilung über die fünf Aktionsarten (126 Profile), je Profil Suchbot über 20 Startwerte, Profilergebnis = Median. Profil gewinnt, wenn sein Median < 28.000 liegt. Strategiekern = die stärkste der drei Familien Position/Beteiligung/Lobby, Gleichstand nach kleinerer Kennung. Abnahme = alle drei Strategiekerne stellen mindestens einen Gewinner, und das beste Klassenergebnis ist höchstens 25 Prozent besser als das schlechteste der drei.
messbar_optimumsverschiebung: Frühfenster = Runden 1-9 mit Profil p, Rest mit Referenzprofil; Spätfenster = Runden 20-28 mit Profil p, Rest mit Referenzprofil; je 126 Profile x 20 Startwerte, Median als Profilergebnis, bestes Profil je Fenster nach kleinstem Median (Gleichstand nach Profilkennung). Verschiebung = L1-Abstand der beiden Profilvektoren, 0 bis 2. Schwelle 0,5.
messbar_rueckvergleich: Startjahrgang 1995, 28 Runden ohne Spieler, Politikinstrumente auf die historisch tatsächlichen Werte gesetzt; 31 Sollreihen (davon 27 unabhängig) plus Handelsblock, jede über volle 29 Stützstellen ohne Füllung belegt. Fehlermaß je Reihe: mittlerer absoluter prozentualer Fehler (Schwelle 20 Prozent) und Richtungstreue (Schwelle 0,6).
---

# Ein Hedgefonds mit vier Ländern, drei Sektoren und vier Politikhebeln — und jede Zahl, die sich bewegt, sagt warum.

*Zweite Fassung nach `ventures/0016-.../befunde/pruefung-entwurf-2026-08-31.md`. Die
Abarbeitung der acht Befunde steht am Ende der Datei.*

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

Innerhalb einer Runde wird **jede Zustandsgröße genau einmal geschrieben**, und die
Reihenfolge oben ist zyklenfrei. Die einzige Schleife im ganzen Modell ist die
Markträumung in Schritt 4, und sie läuft mit fester Iterationszahl. Alles, was wie eine
Rückkopplung aussieht, überquert eine Rundengrenze — siehe **Der Zustand**.

**Was für die Preisbildung gelten muss** (das Wie ist Sache des Architekten): Für die
beiden Sektoren mit Handelszeilen gibt es je einen Weltpreis, der alle Angebote und
Nachfragen räumt, und darauf je Land einen Zollkeil. Der Sektorpreis eines Landes hängt
aber **nicht vollständig** am Weltpreis, sondern nur zum Anteil `handelsanteil`, einem
exogenen Koeffizienten je Land und Sektor aus dem Jahrgang (Ausfuhr plus Einfuhr des
Sektors geteilt durch seine Wertschöpfung im Startjahr, aus BACI und WDI); der Rest folgt
dem Landespreis. Dienstleistungen haben nur einen Landespreis und keine Handelszeile.

Der Koeffizient ist der Grund, warum die Sektorgliederung des Datenkurators tragbar ist:
Ein Zoll trifft Chinas Industrie über ihren hohen `handelsanteil` hart und die
US-Industrie, in der Bau und Versorger dominieren, schwach — ohne dass dafür ein
Sektorzoll erfunden werden muss, den es unter freier Lizenz nicht gibt. Er ist exogen und
über die Partie konstant; damit bildet das Modell Chinas wachsende Handelsoffenheit über
die Mengen ab, nicht über die Preisübertragung. Das ist eine benannte Vereinfachung.

## Die Aktionen

Fünf Arten. Jede ist diskret, keine hat einen Zeitpunkt innerhalb der Runde. Die
Kennungen 1 bis 5 sind zugleich die Gleichstandsordnung aller Maße.

1. **Position.** Long oder short auf ein Land×Sektor, auf eine Währung oder auf die
   Staatsanleihe eines Landes. In festen Stufen, sofort wirksam, jederzeit auflösbar.
   Der Ein- und Ausstieg bewegt den Preis gegen den Fonds, und zwar umso stärker, je
   größer sein Anteil an diesem Markt ist.
2. **Beteiligung.** Ein dauerhafter Anteil an einem Land×Sektor. Sie ist illiquide — der
   Ausstieg dauert zwei Runden und kostet einen Abschlag — und sie ist der einzige Weg zu
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

Rund **300** ganzzahlige Größen. Die Zahl selbst ist keine Verteidigung — siehe unten.

**Je Land** (vier Länder): drei Sektoren mit Wertschöpfung, Kapitalstock, Beschäftigung
und Preis; Bevölkerung und Erwerbstätige; Produktivität; Preisniveau und Inflation;
Leitzins; Wechselkurs gegen den US-Dollar als Numéraire; Staatsschuld und Haushaltssaldo;
Zustimmung zur Regierung; Aufsichtszähler; Einfluss; vier Politikinstrumente, jedes mit
Stand, anliegendem Druck, Gegendruck und Restverzögerung.

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
Nachahmerzähler (12) und der Marktwert aller handelbaren Körbe als Bezugsgröße der
Marktrendite.

**Einfluss je Land** ist der geglättete Anteil des Fonds am gesamten Lobbydruck in diesem
Land, 0 bis 100. Er ist die zweite Hälfte der Siegbedingung — und die Größe, deren Erwerb
sämtliche Gegenkräfte weckt.

### Die vier Politikinstrumente

| Instrument | Datenanker | Bemerkung |
|---|---|---|
| Leitzins | ja (IWF IFS) | Für Deutschland **exogen ab 1999**, also ab Runde 5. Diese Asymmetrie ist gewollt, siehe unten. |
| Zollniveau | ja, aber **nur aggregiert je Land** (WDI, mit Vorbehalt) | Kein Zoll je Sektor. Die Sektorwirkung entsteht aus `handelsanteil` und den Importanteilen, nicht aus einem erfundenen Sektorzoll. |
| Haushaltssaldo / Staatsausgabenquote | ja (IWF WEO) | |
| Kapitalverkehrs- und Finanzmarktregulierung | **nein, reines Modellkonstrukt** | Muss existieren, weil die Aufsicht sonst keinen Angriffspunkt auf den Fonds hat. Ohne Sollreihe; im Rückvergleich fest auf dem Startwert, und das Orakel ist für dieses Instrument blind. |

### Warum die Größe des Zustands keine Verteidigung ist

`agentenbau.md` nennt als wunden Punkt dieses Genres, dass „ein Modell mit tausenden
rückgekoppelten Größen leicht chaotisch wird, und dann trägt kein Regressionstest mehr".
Dagegen hilft nicht eine kleine Zahl von Feldern, sondern eine kleine Zahl von
**rückgekoppelten Kanälen**. Innerhalb einer Runde gibt es keine; über die Rundengrenze
gibt es genau sieben, und sie sind hier abschließend aufgezählt:

| # | Kanal | Dämpfung |
|---:|---|---|
| 1 | Gewinn → Investition → Kapitalstock → Produktion → Gewinn | eine Runde Verzögerung, Abschreibungsrate |
| 2 | Preis → Realeinkommen → Zustimmung → Regierungswechsel → Instrument → Preis | Instrument höchstens ein Schritt je Runde |
| 3 | Instrument → Handel → Weltpreis → Schaden → Gegenlobbybudget → Instrument | Gegendruck wirkt erst in der Folgerunde |
| 4 | Vermögen → Hebel → Positionsgröße → Preisstoß → Vermögen | Hebelobergrenze, Aufschlag steigt mit Sichtbarkeit |
| 5 | Sichtbarkeit → Aufsichtszähler → Zwangsverkauf → Marktanteil → Sichtbarkeit | Zähler ganzzahlig mit Obergrenze, drei feste Schwellen |
| 6 | Überrendite → Nachahmerzähler → Preis → Überrendite | Zähler ganzzahlig mit Obergrenze |
| 7 | Überrendite → Anlegerbestand → Positionsgröße → Preisstoß → Überrendite | Abzug erst nach drei Runden, fester Anteil je Runde |

**Das ist die Verteidigung, und sie ist prüfbar**, anders als eine Feldzahl: Der
Bruchtester bekommt die Auflage, das Modell **200 Runden ohne Spieler** laufen zu lassen;
verlässt dabei eine Größe ihren Wertebereich, gibt es einen achten Kanal, und der ist ein
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
`handelsanteil`, gemanagter Wechselkurs, starker Zollhebel), **Deutschland**
(Exportüberschuss und **kein eigener Zinshebel ab Runde 5** — die einzige Asymmetrie, die
einen Aktionsraum schließt und damit einen anderen erzwingt), **Brasilien** (Agrarexport,
hohe Zinsen, volatile Währung). Vier Länder, die sich gleichen, wären vier Kopien und
kosteten Strategievielfalt, statt sie zu erzeugen.

### Welche drei Sektoren, und aus welcher Reihe jeder entsteht

Der Datenkurator hat vier WDI-Positionen genannt, von denen eine Teilmenge einer anderen
ist. Die Zuordnung ist deshalb ausdrücklich diese und keine andere:

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
**nicht nach dem Bestand des Fonds**. Sie hat keinen eigenen Datenanker; ihre Startwerte
stammen aus den Daten, ihre Fortschreibung ist Modell. Das steht in der Liste der
ankerlosen Größen, siehe *Die Grenze des Orakels*.

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
mittleren Werte.

### Die Ergebnisgröße einer Partie

Ein `i64` in Milli-Runden, **kleiner ist besser**, streng geordnet und ohne Sammelwert:

| Ausgang | Wert | Bereich |
|---|---|---|
| Mandat in Runde r erfüllt | `r × 1.000` | 1.000 … 28.000 |
| 28 Runden überlebt, Mandat nicht erfüllt | `28.000 + Fehlbetrag`, Fehlbetrag = fehlendes Vermögen plus fehlender Einfluss, je in Promille der eigenen Schwelle, **je Teil bei 1.000 begrenzt** | 28.000 … 30.000 |
| an einer Todesart in Runde d gestorben | `30.000 + (29 − d) × 1.000` | 31.000 … 58.000 |

Der frühe Tod ist damit schlechter als der späte, und zwar um volle Runden — genau die
Auflösung, die Maß 1 im letzten Partiedrittel braucht. Eine Sammelkappe auf den
Gesamtwert gibt es **nicht**; siehe Befund 6.

### Das Referenzprofil

Ein **Aktionsprofil** ist die Verteilung des Rundenbudgets über die fünf Aktionsarten in
Fünftelrasterung, also ein Vektor `(a1…a5)` mit `ai ∈ {0…5}` und `Σai = 5`. Das sind
`C(9,4) = 126` Profile. Das **Referenzprofil** ist `(1,1,1,1,1)`. Es ist die „feste
Folgepolitik" von Maß 1 und die Füllung außerhalb der Fenster von Maß 3 — dieselbe
Vorgabe an beiden Stellen, damit die Maße vergleichbar bleiben.

### Maß 1 — Entscheidungsdichte

Für jede Runde `t = 1 … 27`: Ziehe **30 Aktionsbündel**. Ein Bündel entsteht, indem zuerst
die Bündelgröße gleichverteilt aus `{0,1,2,3}` gezogen wird und dann so viele Aktionen
ohne Zurücklegen gleichverteilt aus der Liste der in dieser Runde zulässigen Aktionen.
Doppelte Bündel im Stichprobensatz werden **nicht** entfernt — sonst hinge die
Stichprobengröße vom Zustand ab. Der Zufallsstartwert folgt aus `(Jahrgang, Parametersatz,
Wurzelstartwert, t, Stichprobenindex)`.

Jedes Bündel wird gesetzt, dann läuft die Partie mit dem Heuristikbot auf dem
Referenzprofil bis Runde 28 durch. `Dichte(t)` = Anteil der 30 Ergebnisse, die um **mehr
als 1.000 Milli-Runden** vom Median der 30 abweichen.

Abnahme: Mittel der `Dichte(t)` über jedes Partiedrittel — Runden 1-9, 10-19, 20-27 —
jeweils **≥ 0,4**, nicht nur über die ganze Partie. Ein Spiel, das nur in der Mitte lebt,
fällt hier durch. Fällt es durch, ist „the consequences of choices often feel intangible"
gerade gemessen worden.

Kosten je Startwert: `30 × Σ(28−t)` für `t = 1…27` = **11.340 Weltschritte**.

### Maß 2 — Strategievielfalt

Je Profil `p` spielt der **Suchbot** über **20 Startwerte** eine volle Partie; das
Profilergebnis `E(p)` ist der Median der 20 Ergebnisse. Ein Profil **gewinnt**, wenn
`E(p) < 28.000` — also wenn es das Mandat im Median erfüllt.

„Strukturell verschieden" ist hier definiert und nicht mehr offen: Der **Strategiekern**
eines Profils ist die Aktionsart mit dem größten Anteil unter den drei Familien
`{1 Position, 2 Beteiligung, 3 Lobby}`, bei Gleichstand die kleinere Kennung. Hebel und
Sichtbarkeit sind Verstärker, keine Strategien, und gehen in den Kern nicht ein. Es gibt
damit genau drei Klassen.

Abnahme, beide Teile:

1. **Jede der drei Klassen stellt mindestens einen Gewinner.**
2. Sei `Ek` das beste Profilergebnis der Klasse `k`. Dann muss
   `max(Ek) ≤ 1,25 × min(Ek)` gelten.

Der zweite Teil ist der wichtigere — sonst gewinnen drei, aber eines dominiert, und das
ist derselbe Defekt unter anderem Namen. Das ist die Zahl hinter „trying to implement the
tiniest socialist policy will always result in bankruptcy".

Kosten: `126 × 20 × 1.708` = **4.304.160 Weltschritte**.

### Maß 3 — Verschiebung des Optimums

Zwei getrennte Läufe je Profil, jeder über die **volle Partie**, damit keine Runde ohne
Vorgabe bleibt:

- **Frühfenster:** Runden 1-9 mit Profil `p`, Runden 10-28 mit dem Referenzprofil.
  Ergebnis `Efrüh(p)` = Median über 20 Startwerte.
- **Spätfenster:** Runden 1-19 mit dem Referenzprofil, Runden 20-28 mit Profil `p`.
  Ergebnis `Espät(p)` = Median über 20 Startwerte.

`p*` = Profil mit kleinstem `Efrüh`, `q*` = Profil mit kleinstem `Espät`, Gleichstand nach
Profilkennung. **Verschiebung** = `Σ|p*i − q*i| / 5`, also der L1-Abstand der beiden
Anteilsvektoren, Wertebereich 0 bis 2. Abnahmeschwelle **≥ 0,5**.

Beide Läufe verwenden den Suchbot, innerhalb wie außerhalb des Fensters; „frei" bedeutet
also: frei innerhalb des jeweils gesetzten Profils, nie frei über Profile hinweg. Erzwungen
wird die Verschiebung nicht durch Balance, sondern durch Gegenkraft 4 und 3: Nachahmer
grasen jede frühe Position ab, der Preisstoß entwertet Größe. Das ist die Zahl hinter
„already the richest hedge fund in the game and nothing fun to do".

Kosten: `2 × 126 × 20 × 1.708` = **8.608.320 Weltschritte**.

### Maß 4 — Rückvergleich

Startjahrgang **1995**, 28 Runden ohne Spieler (Fonds mit Nullvermögen, keine Aktionen),
und — das ist der schärfere Teil — **die Politikinstrumente werden auf die historisch
tatsächlichen Werte gesetzt**. Das prüft die Übertragung Politik → Wirtschaft, also die
Wirkungskette selbst; ein Lauf mit erfundener Politik prüfte nur die halbe Maschine.

31 Sollreihen, davon 27 unabhängig: BIP je Land (4), Sektoranteile (12, davon 8
unabhängig), Verbraucherpreise (4), Leitzins (4), Wechselkurs gegen USD (3),
Staatsschuldenquote (4); dazu der Handelsblock als eigener Block. Zwei Fehlermaße je
Reihe: mittlerer absoluter prozentualer Fehler über 28 Runden (Schwelle 20 Prozent) und
Richtungstreue, also der Anteil der Jahre mit richtigem Vorzeichen der Änderung (Schwelle
0,6). Die Richtungstreue ist das wichtigere Maß — ein Modell, das die Wendepunkte trifft,
ist ein Simulationsmodell; eines, das nur die Niveaus trifft, ist eine Interpolation.

**Warum 1995 und warum 28 Runden.** Die Regel, aus der beide Zahlen folgen: *Die
Partielänge ist die Länge des Fensters, in dem jede Sollreihe ohne Füllung belegt ist.*
CEPII BACI (HS92) beginnt **1995** und reicht bis 2024
(`cepii.fr/CEPII/en/bdd_modele/bdd_modele_item.asp?id=37`, abgerufen 2026-08-31); die
übrigen Reihen sind länger. Ein Jahrgang 1980 ließe 15 von 40 Runden ohne bilaterale
Ströme — nach `technik.md` T24 („mehr als ein Fünftel gefüllt gilt als nicht belastbar")
wäre der Handelsblock als nicht belastbar zu kennzeichnen, bevor die erste Zeile Code
steht. Der Endzustand 2023 statt 2024 lässt ein Jahr Abstand zum jüngsten, für
Sektoranteile regelmäßig unvollständigen WDI-Jahrgang.

Der Zuschnitt ist kein bloßer Verzicht. Er schneidet **Brasiliens Hyperinflation vor dem
Plano Real** ab, an der jede prozentuale Fehlerrechnung zerbrochen wäre, und er enthält
trotzdem den Euro-Beginn 1999 (Runde 5), Chinas WTO-Beitritt 2001 (Runde 7), 2008
(Runde 14) und 2020 (Runde 26). Und er hat eine Eigenschaft, die 1980 nicht hätte: Maß 4
prüft **jede Runde der Standardpartie**, nicht fünf Achtel davon.

**Und die Grenze des Orakels, ausdrücklich.** Ohne Sollreihe sind: **Sektorpreise**
(Lücke 2 des Datenkurators), **Zustimmung** (Lücke 4), das Instrument
**Finanzmarktregulierung** und die **Marktrendite**. Vier Größen, alle im Zustand
sichtbar, keine vom Rückvergleich gedeckt. Er prüft die Dynamik der Maschine über den
historischen Zeitraum und sagt nichts über den Ast, den der Spieler betritt.

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
- **Startjahrgänge vor 1995.** 1980 und früher bleiben als **Spieljahrgänge** möglich und
  sind der naheliegende Inhalt des Erweiterungsmodells aus der Idee. Sie tragen dann
  keinen Handelsblock im Rückvergleich und sind damit Spiel-, aber keine Prüfjahrgänge.
  Das gehört ins Kaufangebot geschrieben, nicht in eine Fußnote.
- **Quartals- und Tagestakt.** Damit fallen Panik, Runs und Margin Calls im Wortsinn weg —
  ein spürbarer Verlust an Genre-Erwartung, und ich nenne ihn als solchen. Der Grund ist
  hart: BIP, Sektorstruktur, Produktivität und Zoll liegen **jährlich** vor. Quartalsrunden
  ließen drei von vier Runden ungeprüft. Ersatz für das Innerjahresrisiko: Der Hebel wird
  nicht gegen den Jahresendstand geprüft, sondern gegen einen Innerjahresausschlag, der
  deterministisch aus der Jahresbewegung und der historischen Schwankungsbreite des Landes
  folgt. Hebel bleibt gefährlich, ohne dass eine zweite Zeitschicht entsteht.
- **Ein Weltaktienindex als Vergleichsmaßstab.** Es gibt keinen unter freier Lizenz. Die
  Marktrendite ist deshalb eine Modellgröße ohne Anker — benannt, nicht versteckt.
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
  Sektorwirkung entsteht aus `handelsanteil` und den Importanteilen.
- **Ein zeitlich veränderlicher `handelsanteil`.** Er wäre richtiger und kostete vier
  weitere exogene Pfade. Konstant genügt, weil die Mengen ohnehin endogen sind.
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
- **Die übrigen WDI-Reihen unter der Drittanbieter-Ausnahme.** Der Architekt hat die
  Reihenliste geliefert; zu prüfen sind nach seiner Kennzeichnung Nr. 7 (sektorale
  Beschäftigung, ILO-Schätzung), Nr. 8 (Verbraucherpreise, IWF-gestützt), Nr. 10
  (Wechselkurs) und Nr. 13 (Zoll). Je Reihe ist das Feld „Source" im Indikatorendatensatz
  zu lesen. Vier Abrufe, und die Frage ist geschlossen — Aufgabe des Datenbauers, weil sie
  am Jahrgang hängt und nicht am Entwurf.
- **Brasiliens Disinflation 1995-1997 ist der schärfste Punkt des Rückvergleichs.** 1995
  liegt nach dem Plano Real, aber die Inflationsrate fällt in den ersten drei Runden noch
  um eine Größenordnung. Reißt die BR-Preisreihe das MAPE-Maß **allein** auf den Runden 1
  bis 3, ist das gesondert zu berichten und nicht durch eine Schwellenänderung zu glätten.
  Auflage an den Rückvergleicher, keine Entwurfsfrage.
- **Die Zahlenwerte der Schwellen** — Mandatsschwelle, Aufsichtsschwellen,
  Nachahmergeschwindigkeit, Stufenweite einer Position, Anlegerabzugsanteil. Sie gehören
  nicht in diesen Entwurf, weil sie nicht entschieden, sondern **kalibriert** werden: Das
  Selbstspiel sucht die Werte, bei denen Maß 1 bis 3 ihre Schwellen erreichen. Genau dafür
  gibt es die Maße. Festgelegt ist die Form, nicht die Zahl.
- **Wie fein der Aktionsraum sein darf.** Zu grob, und Maß 1 findet keine Unterschiede; zu
  fein, und die Stichprobe von 30 Bündeln deckt zu wenig ab. Empirisch am Prototyp zu
  bestimmen — messbar daran, ob `Dichte(t)` bei K=30 und K=60 dieselbe Antwort gibt.

## Befundabarbeitung — Prüfung vom 2026-08-31

**Befund 1, Sektorgliederung ohne Quellreihe — behoben.** Die drei Modellsektoren sind
jetzt Landwirtschaft, Industrie (einschließlich Bau), Dienstleistungen mit je genau einer
benannten WDI-Reihe; `NV.IND.MANF.ZS` bleibt ungenutzt, nichts verschwindet, die
Normierung auf 10.000 steht im Manifest, und von 31 Sollreihen sind 27 unabhängig. Der
Einwand gegen Lesart B — Bau und Versorger sind nicht handelbar — ist über den exogenen
Koeffizienten `handelsanteil` je Land und Sektor gelöst: „handelbar" heißt, dass ein Sektor
Handelszeilen hat, nicht dass sein Preis vollständig am Weltpreis hängt. Der Satz „der
Tausch ist nicht knapp" ist gestrichen; er trug nicht.

**Befund 2, Startjahrgang an zwei Stellen verschieden — behoben.** Frontmatter und Text
sagen dasselbe: 1995, 28 Runden, Endzustand 2023. Die Entscheidung ist an einer Regel
aufgehängt (Partielänge = ungefülltes Fenster aller Sollreihen) und an einer geprüften
Zahl: BACI HS92 beginnt 1995 (cepii.fr, abgerufen 2026-08-31). 1980 fällt als Prüfjahrgang
weg und bleibt als Spieljahrgang für das Erweiterungsmodell erhalten, ausdrücklich ohne
Handelsblock im Rückvergleich.

**Befund 3, die Zahl 150 — behoben, aber anders als verlangt.** Die Zahl ist auf rund 300
berichtigt. Die Verteidigung gegen „chaotisch" steht jetzt nicht mehr auf der Feldzahl,
sondern auf der abschließenden Liste der **sieben** rundenübergreifenden
Rückkopplungskanäle mit je benannter Dämpfung, plus einer Beschränktheitsprüfung über 200
Runden für den Bruchtester. Eine Feldzahl ist keine Aussage über Chaos; eine Kanalzahl ist
eine, und sie ist widerlegbar.

**Befund 4, Marktrendite ohne Datenreihe — anders gelöst.** Ich übernehme die Auslegung des
Architekten (wertgewichtete Rendite aller handelbaren Körbe und Anleihen), aber nicht seine
Gewichtung: gewichtet wird nach **Modellmarktwerten**, nicht nach dem Bestand des Fonds.
Damit tritt die von ihm selbst benannte Folge nicht ein, dass die Überrendite eines großen
Fonds rechnerisch gegen null geht. Gegenkraft 3 wirkt stattdessen über den Preisstoß beim
Handeln, der mit dem Marktanteil wächst — und der Ausweg für einen großen Fonds ist
benannt: Konzentration und Ursache statt Breite. Die Marktrendite steht jetzt in der Liste
der Größen ohne Datenanker, zusammen mit Sektorpreisen, Zustimmung und
Finanzmarktregulierung.

**Befund 5, Maß 2 und 3 als Absichtserklärungen — behoben.** „Strukturell verschieden" ist
über den Strategiekern definiert (stärkste der drei Familien, Gleichstand nach kleinerer
Kennung, genau drei Klassen). „Frei" in Maß 3 ist ersetzt: Beide Fenster laufen über die
volle Partie, außerhalb des Fensters gilt das Referenzprofil `(1,1,1,1,1)`, die Runden 10
bis 19 sind damit nicht mehr unbestimmt. Maß 1 zieht **ganze Bündel**, nicht einzelne
Aktionen, mit angegebener Ziehregel; die feste Folgepolitik ist der Heuristikbot auf
demselben Referenzprofil. Die Lesart, die `technik.md` stillschweigend brauchte, ist damit
ausgesprochen — und sie ist genau die, die seine Rechnung voraussetzte: 2 × 126 × 20 ×
Partiekosten.

**Befund 6, Deckelung der Ergebnisgröße — behoben, mit anderer Lösung als der
zurückgewiesenen.** Die Deckelung bei 40.000 + min(60.000, …) entfällt; ihre Begründung
(„sonst zöge eine Bankrottpartie jeden Median") traf auf einen Median nicht zu. An ihre
Stelle tritt eine dreiteilige, streng geordnete Skala, in der der Tod in Runde d den Wert
`30.000 + (29 − d) × 1.000` trägt. Damit unterscheiden sich scheiternde Partien
voneinander um volle Runden, statt auf einem Wert zusammenzufallen — genau dort, wo Maß 1
im letzten Drittel sonst blind geworden wäre. Die Skala gehört zu diesem Entwurf und nicht
in die Architektur.

**Befund 7, Handelsmatrix vier gegen fünf Gegenüber — behoben.** Die Fassung des
Architekten ist die richtige und steht jetzt hier: fünf Gebiete × vier Gegenüber × zwei
Sektoren mit Handelszeilen = 40 Ströme, die Restwelt mit eigenen Zeilen. Nur so hält die
Invariante „Summe aller Handelsbilanzen = 0". Der widersprüchliche Klammerzusatz ist weg.

**Befund 8 ist nicht mein Gewerk** (Feldzählung in `technik.md` T15). Was der Entwurf dazu
vorgibt, steht unter *Der Zustand*: Die Restwelt trägt keine Politikinstrumente, keine
Zustimmung, keinen Aufsichtszähler und keinen Einfluss — vier Streichungen mehr als der
Klammerzusatz nannte. Der Architekt zählt danach neu.

**Zwei Rückfragen aus `technik.md`, Abschnitt 12, hiermit beantwortet.** Der Umgang mit dem
deutschen Bruch 1999 (verkettete Wechselkurs-Indexreihe, Feld `exogen_ab` am Leitzins)
entspricht dem Entwurf und wird übernommen; er liegt jetzt in Runde 5 statt Runde 19 und
ist damit eine frühe, historisch verankerte Schließung eines Aktionsraums. Das Startjahr
ist oben entschieden und damit keine offene Architekturfrage mehr.

**Eine Folge für den Architekten, die er nicht kennen kann:** Die Partielänge fällt von 40
auf 28 Runden. Eine Partie kostet damit 28 Weltschritte mit dem Heuristikbot und
`28 + 60 × 28 = 1.708` mit dem Suchbot; die Rechenzeittabelle in Abschnitt 10 ist auf
dieser Grundlage neu zu rechnen. Die drei Maße kosten zusammen rund 13,5 Millionen
Weltschritte statt der bisherigen 19,6 Millionen.
