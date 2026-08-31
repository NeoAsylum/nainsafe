---
typ: spiel
idee: 0016-hedgefonds-simulation-echte-weltwirtschaft
erstellt: 2026-08-31
schleife: Der Spieler stellt je Runde bis zu drei Aktionen aus fünf Arten, die Welt rechnet ein Jahr weiter, und jede Zahländerung trägt die Kette ihrer Ursachen mit sich.
siegbedingung: Das Mandat — Fondsvermögen über einer Schwelle UND Einfluss über einer Schwelle in mindestens zwei Ländern — erreicht innerhalb von 40 Runden, ohne vorher an einer der drei Todesarten zu sterben. Ergebnis ist die Rundenzahl bis zur Erfüllung.
aktionen: 5
laender: 4 spielbar (USA, China, Deutschland, Brasilien) plus ein nicht spielbares Restwelt-Aggregat
gueter: 3 Sektoren (Rohstoffe/Agrar, Verarbeitendes Gewerbe, Dienstleistungen), davon 2 handelbar
takt: 1 Runde = 1 Jahr; Standardpartie 40 Runden (1980–2020)
gegenkraefte: 5
messbar_entscheidungsdichte: Je Runde K Stichprobenaktionen, jede von diesem Zustand aus bis Runde 40 mit fester Folgepolitik und identischem Startwert nachgespielt; Dichte = Anteil der Stichproben, deren Ergebnis um mehr als eine Runde vom Median abweicht. Schwelle 0,4 in jedem Partiedrittel.
messbar_strategievielfalt: Aktionsprofil = Mittelverteilung über die fünf Aktionsarten in Fünftelrasterung; je Profil ein Bot, der nur darin optimiert. Vielfalt = Zahl der Profile, die das Mandat in 40 Runden erfüllen. Schwelle sind mindestens 3 strukturell verschiedene, und das beste höchstens 25 Prozent schneller als das drittbeste.
messbar_optimumsverschiebung: Bestes Aktionsprofil im Fenster Runde 1–13 gegen bestes im Fenster 28–40, Abstand als Summe der absoluten Anteilsdifferenzen (0 bis 2). Schwelle 0,5.
messbar_rueckvergleich: Startjahrgang 1980, 40 Runden ohne Spieler, Politikinstrumente auf die historisch tatsächlichen Werte gesetzt; 31 Sollreihen (BIP, Sektoranteile, Verbraucherpreise, Leitzins, Wechselkurs, Staatsschuldenquote, bilaterale Ströme) aus WDI, PWT 11.0, IWF und CEPII BACI. Fehlermaß je Reihe ist der mittlere absolute prozentuale Fehler (Schwelle 20 Prozent) und die Richtungstreue (Schwelle 0,6).
---

# Ein Hedgefonds mit vier Ländern, drei Sektoren und vier Politikhebeln — und jede Zahl, die sich bewegt, sagt warum.

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

**Was für die Preisbildung gelten muss** (das Wie ist Sache des Architekten): Für die
beiden handelbaren Sektoren gibt es je einen Weltpreis, der alle Angebote und Nachfragen
räumt, und darauf je Land einen Zollkeil. Dienstleistungen haben einen Landespreis und
werden nicht gehandelt. Damit greift ein Zoll auf zwei von drei Sektoren, und der dritte
ist der Puffer, in den ein Land ausweicht — das ist der ökonomische Grund für die
Dreiteilung und zugleich ihr Datenanker.

## Die Aktionen

Fünf Arten. Jede ist diskret, keine hat einen Zeitpunkt innerhalb der Runde.

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

**Warum fünf und nicht drei.** Drei Familien — Position, Beteiligung, Lobbying — sind die
drei Strategieprofile, an denen Maß 2 gemessen wird; ohne sie gibt es nichts zu messen.
Hebel ist keine eigene Strategie, sondern die Angriffsfläche der ersten Todesart, und ohne
ihn ist Größe risikolos. Sichtbarkeit ist der Grund, warum die Gegenkräfte ein Spielfeld
sind und kein Bremsklotz: Ohne sie wäre Aufmerksamkeit eine bloße Strafe auf Erfolg, mit
ihr ist sie eine Entscheidung — laut und schnell gegen leise und langsam. Genau daraus
entsteht die Optimumsverschiebung, die Maß 3 verlangt.

## Der Zustand

Rund 150 ganzzahlige Größen. Klein genug, dass die Rückkopplung beherrschbar bleibt
(Kriterium 3 aus `agentenbau.md`), groß genug, dass die Maße etwas zu messen finden.

**Je Land** (vier Länder): drei Sektoren mit Wertschöpfung, Kapitalstock, Beschäftigung
und Preis; Bevölkerung und Erwerbstätige; Produktivität; Preisniveau und Inflation;
Leitzins; Wechselkurs gegen den US-Dollar als Numéraire; Staatsschuld und Haushaltssaldo;
Zustimmung zur Regierung; vier Politikinstrumente, jedes mit Stand, anliegendem Druck,
Gegendruck und Restverzögerung.

**Die vier Politikinstrumente**, und für jedes steht hier, ob es in Daten verankert ist —
weil der Rückvergleich genau daran hängt:

| Instrument | Datenanker | Bemerkung |
|---|---|---|
| Leitzins | ja (IWF IFS) | Für Deutschland **exogen**: kein nationaler Hebel ab 1999, davor Bundesbank. Diese Asymmetrie ist gewollt, siehe unten. |
| Zollniveau | ja, aber **nur aggregiert je Land** (WDI, mit Vorbehalt) | Kein Zoll je Sektor. Die Sektorwirkung entsteht aus den unterschiedlichen Importanteilen, nicht aus einem erfundenen Sektorzoll. |
| Haushaltssaldo / Staatsausgabenquote | ja (IWF WEO) | |
| Kapitalverkehrs- und Finanzmarktregulierung | **nein, reines Modellkonstrukt** | Muss existieren, weil die Aufsicht sonst keinen Angriffspunkt auf den Fonds hat. Ohne Sollreihe. |

**Handel:** vier Länder mal fünf Gegenüber (drei Länder plus Restwelt) mal zwei handelbare
Sektoren. Das Restwelt-Aggregat schließt den Kreislauf und hat kein eigenes Politikmodell;
ohne es wäre die Summe der vier Handelsbilanzen zwangsläufig null, was gegen die echten
Daten falsch ist.

**Der Fonds:** Kasse, Positionen, Beteiligungen, Hebelstand, globale Sichtbarkeit,
Einfluss je Land, Anlegerbestand, laufende und historische Überrendite.

**Einfluss je Land** ist der geglättete Anteil des Fonds am gesamten Lobbydruck in diesem
Land, 0 bis 100. Er ist die zweite Hälfte der Siegbedingung — und die Größe, deren Erwerb
sämtliche Gegenkräfte weckt.

### Warum vier Länder und nicht drei

Der Auftrag verlangt die kleinste Fassung, an der die Maße laufen, und ich muss jede
zusätzliche Einheit gegen sie verteidigen. Hier die Verteidigung: Bei drei Ländern hat
jeder Zoll genau einen Ausweichpartner. Die Reaktion des Systems auf jede Lobbyaktion ist
damit einzügig und vorhersehbar — Maß 1 kollabiert, weil eine Wahl ohne Alternativen keine
Wahl ist. Bei vier Ländern gibt es zwei Umlenkungspfade unterschiedlicher Größe, und
welcher der bessere ist, ändert sich mit dem Zustand. Das ist der Mechanismus, aus dem
Maß 3 überhaupt entstehen kann.

Die vier sind nach struktureller Verschiedenheit gewählt, nicht nach Bedeutung: **USA**
(großer Binnenmarkt, Leitwährung, dienstleistungsschwer), **China** (verarbeitendes
Gewerbe, gemanagter Wechselkurs, starker Zollhebel), **Deutschland** (Exportüberschuss und
**kein eigener Zinshebel ab 1999** — die einzige Asymmetrie, die einen Aktionsraum
schließt und damit einen anderen erzwingt), **Brasilien** (Rohstoffexport, hohe Zinsen,
volatile Währung). Vier Länder, die sich gleichen, wären vier Kopien und kosteten
Strategievielfalt statt sie zu erzeugen.

### Warum drei Sektoren und nicht sechs

Weil es sechs nicht gibt. Der Datenkurator hat es geprüft: Unter freier Lizenz liefert die
Weltbank die grobe Gliederung, und feinere liegen bei OECD (ungeklärt) und Eurostat (für
Nicht-EU-Länder gesperrt). Sechs Sektoren wären ein Modellkonstrukt, das aus drei
aufgeteilt wird — und dann bezöge sich der Rückvergleich nur auf die aggregierte Ebene.
Ich wähle die Gliederung, die die Daten hergeben, und behalte dafür die vierte Prüfachse
auf jeder Größe, die im Spiel vorkommt. Das ist der Tausch, und er ist nicht knapp.

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
mit der Marktrendite — die aus den echten Daten kommt. Der Vergleich ist relativ, und
darin liegt die Kraft: Je größer der Fonds, desto größer sein Anteil am Markt, desto mehr
**ist** er der Markt, desto schwerer schlägt er ihn. Formal fällt die erreichbare
Überrendite mit dem Marktanteil, weil Ein- und Ausstieg den Preis gegen ihn bewegen.
Bleibt die Überrendite drei Runden unter null, ziehen Anleger ab — und das erzwingt
Verkäufe in einen Markt, den der Fonds selbst bewegt. Diese Gegenkraft braucht keine
Erzählung; sie folgt aus der Größe allein.

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

Alle vier laufen im Selbstspiel ohne Darstellung über dieselbe Zustandsschnittstelle. Eine
Partie sind 40 Jahresrunden auf rund 150 ganzzahligen Größen — billig genug, um sie
millionenfach zu fahren, und das ist der einzige Vorsprung dieser Fabrik.

**Ergebnisgröße jeder Partie ist eine Zahl**, nicht ein Ja/Nein: die Rundenzahl bis zur
Mandatserfüllung, oder bei Nichterfüllung 40 plus der Fehlbetrag. Ein binäres Ergebnis
gäbe den Maßen zu wenig Signal.

**Entscheidungsdichte.** Ziehe in Runde t eine Stichprobe von K legalen Aktionen. Spiele
die Partie von t aus für jede Stichprobenaktion bis Runde 40 durch, mit fester Folgepolitik
und identischem Zufallsstartwert. Dichte(t) = Anteil der Stichproben, deren Ergebnis um
mehr als eine Runde vom Median abweicht. Abnahmeschwelle: **≥ 0,4 in jedem Partiedrittel**,
nicht nur im Mittel — ein Spiel, das nur in der Mitte lebt, fällt hier durch. Fällt es
durch, ist „the consequences of choices often feel intangible" gerade gemessen worden.

**Strategievielfalt.** Ein Aktionsprofil ist die Verteilung der eingesetzten Mittel über
die fünf Aktionsarten, in Fünftel gerastert. Je Profil spielt ein Bot, der nur innerhalb
dieses Profils optimiert. Vielfalt = Zahl der Profile, die das Mandat in 40 Runden
erfüllen. Abnahmeschwelle: **mindestens drei strukturell verschiedene Profile gewinnen,
und das beste ist höchstens 25 Prozent schneller als das drittbeste.** Der zweite Teil ist
der wichtigere — sonst gewinnen drei, aber eines dominiert, und das ist derselbe Defekt
unter anderem Namen.

**Verschiebung des Optimums.** Bestimme das beste Aktionsprofil im Fenster Runde 1–13 und
im Fenster 28–40, jeweils indem das Profil im einen Fenster eingefroren und im anderen
frei ist. Verschiebung = Summe der absoluten Anteilsdifferenzen zwischen beiden Profilen,
0 bis 2. Abnahmeschwelle: **≥ 0,5**. Erzwungen wird sie nicht durch Balance, sondern durch
Gegenkraft 4 und 3: Nachahmer grasen jede frühe Position ab, Marktenge entwertet Größe.

**Rückvergleich.** Startjahrgang 1980, 40 Runden ohne Spieler (Fonds mit Nullvermögen,
keine Aktionen), und — das ist der schärfere Teil — **die Politikinstrumente werden auf die
historisch tatsächlichen Werte gesetzt**. Das ist möglich, weil drei der vier Instrumente
einen Datenanker haben, und es prüft genau die Übertragung Politik → Wirtschaft, also die
Wirkungskette selbst. Ein Lauf mit erfundener Politik prüfte nur die halbe Maschine.

31 Sollreihen: BIP je Land (4), Sektoranteile (12), Verbraucherpreise (4), Leitzins (4),
Wechselkurs gegen USD (3), Staatsschuldenquote (4); dazu die bilateralen Ströme als
eigener Block. Zwei Fehlermaße je Reihe: mittlerer absoluter prozentualer Fehler über
40 Jahre (Schwelle 20 Prozent) und Richtungstreue, also der Anteil der Jahre mit richtigem
Vorzeichen der Änderung (Schwelle 0,6). Die Richtungstreue ist das wichtigere Maß — ein
Modell, das die Wendepunkte trifft, ist ein Simulationsmodell; eines, das nur die Niveaus
trifft, ist eine Interpolation.

**Und die Grenze des Orakels, ausdrücklich:** Sektorpreise und Zustimmung haben **keine
Sollreihe** (Lücken 2 und 4 des Datenkurators). Der Rückvergleich deckt sie nicht. Er
prüft die Dynamik der Maschine über den historischen Zeitraum und sagt nichts über den
Ast, den der Spieler betritt.

### Die drei Klagen und was sie beantwortet

| Klage aus den Rezensionen | Entwurfsentscheidung |
|---|---|
| „the consequences of choices often feel intangible" | **Höchstens drei Aktionen je Runde** — Knappheit zwingt jede Aktion, groß genug zum Wirken zu sein. Dazu die Kette als eigener Zustandsteil (Schritt 1 und 6) und die Entscheidungsdichte als Abnahmeschwelle statt als Wunsch. |
| „trying to implement the tiniest socialist policy will always result in bankruptcy" | **Der Fonds kann long und short sein.** Damit ist keine politische Richtung dominant: Wer auf Regulierung setzt, weil er short steht, gewinnt genauso wie wer sie verhindert. Dazu die zweiteilige Siegbedingung (Kapital UND Einfluss), die eine reine Geldstrategie ausschließt. |
| „no dramatic setbacks or successes", „everything is incredibly surface level" | **Drei Todesarten mit sichtbaren Schwellen** (Zwangsliquidation, Marktverbot, Anlegerabzug) und die Optimumsverschiebung, erzwungen durch Nachahmer und Marktenge. Der Rückschlag ist dramatisch, aber nie willkürlich — siehe „Keine verdeckte Größe". |

## Was bewusst fehlt

- **Mehr als vier Länder und drei Sektoren.** Die Idee nannte zwölf und sechs. Sechs
  Sektoren gibt es nicht unter freier Lizenz, zwölf Länder vervierfachen die
  Rückkopplungswege ohne ein Maß zu verbessern. Breite kommt später und nur dort, wo die
  Maße sie überleben.
- **Quartals- und Tagestakt.** Damit fallen Panik, Runs und Margin Calls im Wortsinn weg —
  ein spürbarer Verlust an Genre-Erwartung, und ich nenne ihn als solchen. Der Grund ist
  hart: BIP, Sektorstruktur, Produktivität und Zoll liegen **jährlich** vor. Quartalsrunden
  ließen drei von vier Runden ungeprüft und machten die stärkste Achse zu drei Vierteln
  blind. Ersatz für das Innerjahresrisiko: Der Hebel wird nicht gegen den Jahresendstand
  geprüft, sondern gegen einen Innerjahresausschlag, der deterministisch aus der
  Jahresbewegung und der historischen Schwankungsbreite des Landes folgt. Hebel bleibt
  gefährlich, ohne dass eine zweite Zeitschicht entsteht.
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
  Sektorwirkung entsteht aus Importanteilen.
- **Grafik über Tabelle, Verlaufsgraph und Kettenansicht hinaus.** Das Genre trägt das
  belegt — Democracy 4 verkauft sich mit einer 2D-Knotenoberfläche und besteht in seiner
  Simulation vollständig aus geladenen Tabellen statt einprogrammierter Effekte
  (positech.co.uk/democracy4/modding.html, abgerufen 2026-08-31). Das ist die Bauart, an
  der ich mich orientiere.

## Offene Entwurfsfragen

- **Die schwerste: Ist der aggregierte Zollsatz der Weltbank verwendbar?** Er ist erkennbar
  aus WITS abgeleitet und fällt damit möglicherweise unter die Drittanbieter-Ausnahme der
  WDI-Lizenz. Ist er gesperrt, verliert der Rückvergleich das wichtigste seiner drei
  verankerten Instrumente, und der Zoll wird ein Konstrukt ohne Anker. Das ändert den
  Entwurf nicht, aber es halbiert seinen Beleg. Zu prüfen, bevor gebaut wird.
- **Die übrigen WDI-Reihen unter der Drittanbieter-Ausnahme.** Der Datenkurator hat diese
  Vorarbeit mir zugewiesen: Die Größen sind oben unter „Der Zustand" benannt, betroffen
  sind vermutlich sektorale Beschäftigung (ILO-Schätzung) und Teile der Preisreihen. Je
  Reihe das Feld „Source" zu lesen ist überschaubar, sobald der Architekt die Reihenliste
  hat.
- **Startjahr 1980 oder 2000.** 1980 gibt die reichere Struktur (Volcker-Schock, Plaza,
  WTO-Beitritt Chinas 2001, 2008). Aber CEPII BACI beginnt später als 1980; vor Beginn
  müssten die bilateralen Ströme aus gröberen Aggregaten kommen, und der Handelsblock des
  Rückvergleichs wäre für die frühen Runden schwächer. Zu entscheiden, wenn die
  tatsächlichen Reihenlängen je Land vermessen sind — nicht vorher, und nicht von mir
  allein.
- **Deutschland vor und nach 1999.** D-Mark bis 1998, Euro danach, nationaler Zinshebel
  nur davor. Der Bruch ist im Modell gewollt, aber er ist auch ein Bruch in der Sollreihe
  des Rückvergleichs. Wie er behandelt wird, ohne dass das Fehlermaß ihn als Modellfehler
  liest, ist offen.
- **Die Zustimmungsgröße hat keinen Datenanker.** Zulässig, aber sie trägt die Wirkungskette
  der Idee. Ob eine Ersatzquelle (V-Dem, Weltbank-Governance) sie verankern könnte, hat der
  Datenkurator ausdrücklich nicht geprüft, weil nicht beauftragt. Ein kleiner
  Zusatzauftrag, falls die Kette ohne Anker zu schwach wirkt.
- **Die Zahlenwerte der Schwellen** — Mandatsschwelle, Aufsichtsschwellen,
  Nachahmergeschwindigkeit, Stufenweite einer Position. Sie gehören nicht in diesen
  Entwurf, weil sie nicht entschieden, sondern **kalibriert** werden: Das Selbstspiel sucht
  die Werte, bei denen Maß 1 bis 3 ihre Schwellen erreichen. Genau dafür gibt es die Maße.
  Was hier festgelegt ist, ist die Form: Mandat = Vermögen UND Einfluss in zwei Ländern,
  Aufsicht = drei Schwellen, Aktionen = höchstens drei je Runde.
- **Wie fein der Aktionsraum sein darf.** Zu grob, und Maß 1 findet keine Unterschiede; zu
  fein, und die Stichprobe wird teuer. Empirisch am Prototyp zu bestimmen.
