---
typ: pruefung
paket: entwurf (kein Arbeitspaket vorhanden -- siehe "Zur Lage")
pruefer: entwurf-pruefer
datum: 2026-08-31
urteil: zurueck
kriterium_geprueft: spiel.md und technik.md gegen die vier Masse aus agentenbau.md, gegen die vier Luecken aus daten.md und gegen einander -- sechs Befunde, davon vier, die den Rueckvergleich oder ein Mass unberechenbar machen
befunde: 8
---

# Pruefung des Entwurfs: spiel.md und technik.md

## Zur Lage

`ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/aufgaben/` ist leer. Es gibt
kein Arbeitspaket und damit kein aufgeschriebenes Abnahmekriterium. Geprueft habe ich
deshalb gegen das, was den beiden Bauagenten vorgegeben war:
`agents/rollen/spielentwerfer.md`, `agents/rollen/architekt.md`, `agentenbau.md` und
`specs/.../daten.md`.

**Erster Befund an den Projektmanager, nicht an die Bauagenten:** Zwei Ergebnisse liegen
im Zustand `gebaut` vor, ohne dass je ein Paket sie beauftragt hat. `baulauf.py` zieht
den Review aus `status: gebaut` in den Paketdateien; ohne Paket laeuft die Reviewstufe
fuer diese beiden Gewerke nur, weil sie hier von Hand angestossen wurde. Das ist kein
Fehler der Entwuerfe, aber es ist die Stelle, an der die naechsten beiden Gewerke
lautlos ungeprueft durchlaufen wuerden.

Nicht gelesen: `notizen/spielentwerfer.md` und `notizen/architekt.md`.

---

## Befund 1 -- Der Rueckvergleich haengt an einer Sektorgliederung, die es in den Daten nicht gibt

**Schwere:** hoch. Betrifft 12 der 31 Sollreihen, also Mass 4.

`spiel.md` waehlt drei Sektoren: **Rohstoffe/Agrar**, **Verarbeitendes Gewerbe**,
**Dienstleistungen**, und begruendet die Wahl damit, sie sei die, "die die Daten
hergeben": *"Ich waehle die Gliederung, die die Daten hergeben, und behalte dafuer die
vierte Pruefachse auf jeder Groesse, die im Spiel vorkommt. Das ist der Tausch, und er
ist nicht knapp."* (`spiel.md`, "Warum drei Sektoren und nicht sechs")

`daten.md`, Luecke 1, nennt die vier Positionen, die WDI tatsaechlich hergibt:
*"Landwirtschaft, Industrie, verarbeitendes Gewerbe, Dienstleistungen, also vier
Positionen, davon eine als Teilmenge einer anderen."*

**So erzeugt man den Fehler:** Man versucht, die drei Sektoren aus `spiel.md` aus diesen
vier Positionen zu bilden. Es gibt genau zwei Lesarten, und beide brechen:

- **Lesart A -- die Namen sind woertlich gemeint.** Sektor 2 ist das verarbeitende
  Gewerbe, also die Teilmenge. Dann hat Sektor 1 ("Rohstoffe") keine Quellreihe: Bergbau
  und Gewinnung stecken in *Industrie*, nicht in *Landwirtschaft*. Und der Rest von
  Industrie (Bergbau, Bau, Versorger) hat keinen Zielsektor -- in den vier Laendern des
  Modells sind das ueber den Zeitraum grob ein Sechstel bis ein Fuenftel der
  Wertschoepfung. Er verschwindet oder wird still irgendwohin geschlagen.
- **Lesart B -- gemeint ist Landwirtschaft / Industrie / Dienstleistungen.** Dann
  existieren die Reihen, aber zwei andere Vorgaben brechen: `spiel.md` erklaert die
  ersten beiden Sektoren fuer **handelbar** und den dritten fuer den nicht handelbaren
  Puffer -- Bau und Versorger, die dann in Sektor 2 liegen, sind nicht handelbar. Und die
  drei WDI-Anteile summieren wegen der Guetersteuern abzueglich Subventionen nicht auf
  100 Prozent, was `technik.md` T30, Pruefung 2 als Invariante verlangt
  (*"alle Anteile summieren auf 10.000"*).

**Warum das ein Befund und keine Feinheit ist:** `daten.md` hat genau diesen Fall
vorhergesehen und eine Vorgabe gemacht -- entweder die Sektorzahl auf das absenken, was
WDI hergibt, *"oder die feineren Sektoren als Modellkonstrukt fuehren, das aus den groben
aufgeteilt wird -- dann bezieht sich die vierte Pruefachse nur auf die aggregierte Ebene,
und das gehoert offen gesagt."* Der Entwurf hat den zweiten Weg genommen und das
Gegenteil hingeschrieben. Der Satz "der Tausch ist nicht knapp" traegt nicht.

**Was fehlt:** je Modellsektor die WDI-Reihe, aus der er entsteht, und die Regel fuer den
Rest der Industrie. Danach ist zu entscheiden, ob die 12 Sektoranteil-Sollreihen
Sollreihen bleiben oder als Modellkonstrukt gekennzeichnet werden.

---

## Befund 2 -- Der Startjahrgang 1980 ist im Frontmatter entschieden, im Text offen, und die beiden Dokumente zusammen schliessen ihn aus

**Schwere:** hoch. Betrifft den Handelsblock von Mass 4.

`spiel.md` legt im Frontmatter fest: `takt: 1 Runde = 1 Jahr; Standardpartie 40 Runden
(1980-2020)` und `messbar_rueckvergleich: Startjahrgang 1980, 40 Runden ohne Spieler`.
Derselbe Text sagt unter "Offene Entwurfsfragen": *"Startjahr 1980 oder 2000. […] Zu
entscheiden, wenn die tatsaechlichen Reihenlaengen je Land vermessen sind."* Das
Frontmatter entscheidet, was der Text offenlaesst. Die Rolle verlangt das Gegenteil: "Du
entscheidest, statt zu sammeln" -- aber dann an einer Stelle, nicht an zweien
verschieden.

**So erzeugt man den Fehler, und er ist rechenbar:** BACI (HS92) beginnt **1995**
(cepii.fr/CEPII/en/bdd_modele/bdd_modele_item.asp?id=37 und
cepii.fr/DATA_DOWNLOAD/baci/doc/baci_webpage.html, abgerufen 2026-08-31). Ein Jahrgang
1980 laesst die Jahre 1980 bis 1994 ohne bilaterale Stroeme -- 15 von 40 Jahren, also
0,375. `technik.md` T24 setzt die Grenze: *"Eine Sollreihe, die zu mehr als einem
Fuenftel gefuellt ist, gilt als nicht belastbar."* 0,375 > 0,2.

Damit ist der Handelsblock -- einer der beiden Bloecke, aus denen Mass 4 besteht -- beim
im Frontmatter gesetzten Jahrgang von der eigenen Datenregel als nicht belastbar
gekennzeichnet, bevor die erste Zeile Code geschrieben ist. Keines der beiden Dokumente
zieht diesen Schluss. `spiel.md` nennt das Problem ("CEPII BACI beginnt spaeter als
1980"), ohne die Jahreszahl zu nennen, und `technik.md` erklaert die Entscheidung fuer
billig ("keine Zeile Code haengt daran") -- billig ist sie technisch, entschieden ist sie
inhaltlich bereits.

---

## Befund 3 -- Die Zahl, mit der der Entwurf Kriterium 3 verteidigt, ist um rund den Faktor zwei falsch

**Schwere:** mittel. Betrifft die einzige quantitative Verteidigung gegen "chaotisch".

`spiel.md`, "Der Zustand": *"Rund 150 ganzzahlige Groessen. Klein genug, dass die
Rueckkopplung beherrschbar bleibt (Kriterium 3 aus `agentenbau.md`), gross genug, dass
die Masse etwas zu messen finden."*

**So erzeugt man den Fehler:** Man zaehlt die Aufzaehlung, die zwei Absaetze darunter
steht. Je Land: 3 Sektoren mal 4 Felder = 12; Bevoelkerung und Erwerbstaetige = 2;
Produktivitaet = 1; Preisniveau und Inflation = 2; Leitzins = 1; Wechselkurs = 1;
Staatsschuld und Haushaltssaldo = 2; Zustimmung = 1; 4 Instrumente mal 4 Felder = 16.
Summe **38 je Land, mal vier Laender = 152** -- und damit ist die Grenze schon
ueberschritten, *bevor* Restwelt, Handel (40), Weltpreise, Aufsichtszaehler,
Nachahmerzaehler (12), Kasse, 20 Positionssteckplaetze, Beteiligungen und Einfluss je
Land gezaehlt sind. `technik.md` T15 zaehlt denselben Entwurf sauber durch und kommt auf
**rund 294**, das Frontmatter dort auf 300.

Kein Dokument erwaehnt die Abweichung. Die Zahl 150 ist nicht dekorativ: Sie ist das
einzige Argument des Entwurfs gegen den wunden Punkt, den `agentenbau.md` fuer genau
dieses Genre benennt (*"ein Modell mit tausenden rueckgekoppelten Groessen wird leicht
chaotisch, und dann traegt kein Regressionstest mehr"*). 294 ist immer noch weit von
"tausenden" entfernt -- der Entwurf faellt daran nicht. Aber die Verteidigung ist eine
andere, als die dasteht, und sie muss neu geschrieben werden, statt sich auf eine Zahl zu
stuetzen, die der eigene Text widerlegt.

---

## Befund 4 -- Gegenkraft 3 steht auf einer Groesse, die es unter den freigegebenen Quellen nicht gibt

**Schwere:** hoch. Betrifft eine der fuenf Gegenkraefte und die dritte Todesart.

`spiel.md`, Gegenkraft 3 (Marktenge): *"Anleger vergleichen seine Rendite mit der
Marktrendite -- die aus den echten Daten kommt."* Daran haengt die Todesart
Anlegerabzug: *"Bleibt die Ueberrendite drei Runden unter null, ziehen Anleger ab."*

**So erzeugt man den Fehler:** Man sucht die Reihe in `daten.md`. Die Tabelle "Belegt
verfuegbar unter tragfaehiger Lizenz" enthaelt keine Rendite- und keine Indexreihe, und
die vier Luecken des Datenkurators nennen diese auch nicht -- er wurde nach einem
Aktienindex nie gefragt. `technik.md` hat den Fund gemacht (Reihenliste, Zeile 18:
*"keine unter freier Lizenz"* -- die Indexreihen der Weltbank stammen von S&P und fallen
mit hoher Wahrscheinlichkeit unter die Drittanbieter-Ausnahme) und einen Ausweg
vorgeschlagen: die Marktrendite als wertgewichtete Rendite aller im Modell handelbaren
Koerbe. Er entscheidet ihn ausdruecklich nicht, sondern legt ihn dem Spielentwerfer vor
(Abschnitt 12).

Das ist das richtige Verhalten des Architekten -- und genau deshalb endet die
Entwurfsphase mit einer offenen Frage, die keine der beiden Rollen mehr aufgreift. Der
Vorschlag ist zudem nicht folgenlos: Eine Marktrendite, die sich aus den Koerben
berechnet, in denen der Fonds selbst steht, macht die Ueberrendite bei wachsendem
Marktanteil rechnerisch gegen null -- das verstaerkt Gegenkraft 3, kann aber die
Todesart Anlegerabzug fuer einen grossen Fonds unausweichlich machen, unabhaengig von
seinem Koennen. Das ist eine Entwurfsentscheidung, keine Auslegung, und sie ist offen.

**Zusatz, weil er die Luecke betrifft:** `daten.md` nennt unter "Nicht geprueft, weil
nicht beauftragt" ausdruecklich V-Dem fuer die Zustimmungsgroesse -- ein Aktienindex
steht dort nicht. Die Luecke ist also nicht bekannt gewesen; sie ist neu.

---

## Befund 5 -- Mass 2 und Mass 3 sind Absichtserklaerungen, keine Rechenvorschriften

**Schwere:** hoch. Der Selbstspieler kann beide spaeter nicht erfinden.

**Mass 2, Strategievielfalt.** Die Schwelle lautet: *"mindestens drei **strukturell
verschiedene** Profile gewinnen, und das beste ist hoechstens 25 Prozent schneller als
das drittbeste."* "Strukturell verschieden" ist nirgends definiert. Bei
Fuenftelrasterung ueber fuenf Aktionsarten gibt es 126 Profile, von denen viele sich um
genau ein Fuenftel unterscheiden. Ob (3,1,1,0,0) und (3,1,0,1,0) "strukturell
verschieden" sind, entscheidet ueber Bestehen oder Durchfallen des Masses -- und die
Antwort steht nirgends. Der zweite Halbsatz ("25 Prozent") ist rechenbar, der erste
nicht, und `spiel.md` nennt selbst den zweiten "den wichtigeren". Das rettet ihn nicht:
Die Zaehlung der drei geht der Abstandspruefung voraus.

**Mass 3, Optimumsverschiebung.** *"Bestimme das beste Aktionsprofil im Fenster Runde
1-13 und im Fenster 28-40, jeweils indem das Profil im einen Fenster eingefroren und im
anderen frei ist."* Zwei Luecken:

- Was **"frei"** bedeutet, steht nicht da. Frei innerhalb der 126 Profile? Frei je Runde
  neu? Frei im Sinne des Suchbots? Jede Lesart ergibt eine andere Zahl.
- Die Runden **14 bis 27** liegen in keinem der beiden Fenster. Was der Bot dort tut,
  ist nicht festgelegt -- und ueber ein Drittel der Partie entscheidet mit, welcher
  Zustand das zweite Fenster ueberhaupt erreicht.

**So faellt das auf, ohne den Code zu kennen:** `technik.md` rechnet die
Optimumsverschiebung mit 12.297.600 Weltschritten, also **exakt dem Doppelten** der
Strategievielfalt (2 x 126 Profile x 20 Startwerte x 2.440). Diese Zahl setzt eine ganz
bestimmte Lesart voraus -- je Fenster ein Durchlauf ueber alle 126 Profile mit dem
Suchbot -- und benennt sie nicht. Waere "frei" als freie Suche ueber Profile *innerhalb*
der Partie gemeint, laege der Aufwand um Groessenordnungen hoeher, und die Aussage
"Nachtlauf 3,4 Minuten" fiele mit. Zwei Dokumente, die stillschweigend dieselbe
unausgesprochene Lesart brauchen, haben sie nicht festgelegt, sondern geraten.

**Kleiner, aber derselben Art -- Mass 1:** *"Ziehe in Runde t eine Stichprobe von K
legalen **Aktionen**"*, waehrend die Entscheidung des Spielers nach `spiel.md` ein
Buendel von **bis zu drei** Aktionen ist (und `technik.md` den Suchbot folgerichtig
"Kandidatenbuendel" bewerten laesst). Ob die Stichprobe eine Aktion variiert und zwei aus
der Folgepolitik nimmt oder ganze Buendel zieht, aendert das Mass -- und dass Knappheit
die Quelle der Entscheidungsdichte sei, ist die tragende Begruendung des Entwurfs fuer
die Drei-Aktionen-Regel. Ebenfalls offen: welches Profil der Heuristikbot als "feste
Folgepolitik" fahrt; er ist nach `technik.md` profilgesteuert.

---

## Befund 6 -- Die Deckelung der Ergebnisgroesse ist falsch begruendet und greift in Mass 1 ein

**Schwere:** mittel.

`technik.md`, Abschnitt 9: *"Nicht erfuellt = 40.000 + min(60.000, fehlbetrag) […] Die
Deckelung haelt die Skala vergleichbar; ohne sie zoege eine einzige Bankrottpartie jeden
Median."*

**So erzeugt man den Fehler:** Man prueft die Begruendung an ihrer eigenen Groesse. Ein
Median ist von Bauart wegen unempfindlich gegen einen einzelnen Extremwert -- eine
Bankrottpartie verschiebt ihn um hoechstens einen Rangplatz. Die genannte Gefahr besteht
fuer ein arithmetisches Mittel, und ein solches kommt in `spiel.md` an keiner Stelle vor.

Die Deckelung hat eine Wirkung, aber die entgegengesetzte: Mass 1 zaehlt *"den Anteil der
Stichproben, deren Ergebnis um mehr als eine Runde vom Median abweicht"*. Alle tief
scheiternden Stichproben liegen nach der Deckelung auf **exakt** 100.000 und
unterscheiden sich damit weder voneinander noch vom Median, sobald der Median selbst am
Deckel liegt. Die gemessene Entscheidungsdichte sinkt also genau dort, wo Scheitern haeufig
ist -- im letzten Partiedrittel, fuer das `spiel.md` die Schwelle ausdruecklich einzeln
verlangt.

Dazu die Zustaendigkeit: Die Deckelung steht nicht in `spiel.md`. Sie ist eine Aenderung
an einem Mass, das dem Spielentwerfer gehoert, und sie ist als "genaue Lesart"
bezeichnet. Bei der Marktrendite hat derselbe Text die Entscheidung korrekt
zurueckgegeben (Abschnitt 12); hier nicht.

---

## Kleinere Befunde

**7. `spiel.md`, "Handel": "vier Laender mal fuenf Gegenueber (drei Laender plus
Restwelt) mal zwei handelbare Sektoren".** Die Klammer nennt vier Gegenueber, der Faktor
sagt fuenf. `technik.md` T15 baut stattdessen 5 Gebiete x 4 Gegenueber x 2 = 40 und gibt
damit der Restwelt eigene Handelszeilen, was `spiel.md` nicht sagt (dort hat die Restwelt
nur "kein eigenes Politikmodell"). Beide Wege enden zufaellig bei 40; die Invariante aus
T30, Pruefung 2 (*"Summe aller Handelsbilanzen einschliesslich Restwelt = 0"*) haelt nur
in der Fassung des Architekten.

**8. `technik.md` T15, Zeile "vier Laender plus Restwelt (ohne Instrumente, ohne
Zustimmung): 4 x 41 + 20 = 184".** Der Klammerzusatz nennt 17 wegfallende Felder (16
Instrumentfelder plus Zustimmung), 41 - 17 = 24, nicht 20. Vier weitere Felder fallen
also weg, ohne benannt zu sein -- vermutlich Aufsichtszaehler, Einfluss, Basiswechsel und
eines mehr. Die Gesamtsumme 294 haengt an der 20. Folgenlos fuer das Modell, aber T15 ist
die Vorgabe, gegen die der Kernbauer die Zustandsstruktur baut, und sie muss zaehlbar
sein.

---

## Wonach ich gesucht und was ich nicht gefunden habe

Damit diese Pruefung von einer, die nicht stattfand, unterscheidbar ist:

- **Die fuenf Gegenkraefte, einzeln gegen "Mechanismus statt Hoffnung".** Alle fuenf
  nennen den Weg, ueber den sie greifen, und alle fuenf wachsen tatsaechlich mit dem
  Erfolg: Aufsicht ueber Sichtbarkeit mal lokalem Fussabdruck (ausdruecklich *nicht* ueber
  das Vermoegen, was den haeufigsten Fehler dieses Genres vermeidet), Gegenreaktion ueber
  Realeinkommen -> Zustimmung -> Regierungswechsel, Marktenge ueber den Marktanteil,
  Nachahmer ueber einen Zaehler je Land x Sektor, Gegenlobby ueber ein Budget proportional
  zum erlittenen Schaden. Verlangt waren drei. **Kein Befund** -- ausser der
  Datenverankerung von Nummer 3, siehe Befund 4.
- **Die Groesse gegen "die kleinste Fassung".** Vier Laender, drei Sektoren, fuenf
  Aktionsarten, vier Instrumente sind je einzeln gegen die Masse verteidigt, und die
  Abschnitte "Was bewusst fehlt" nennen zwoelf Auslassungen mit Grund, darunter die
  teuerste (Quartalstakt) mit ausdruecklicher Nennung des Verlusts. Vier gekoppelte
  Simulationsebenen liegen nicht vor. **Kein Befund.**
- **Die vier Luecken aus `daten.md`, jede einzeln.** Luecke 2 (Sektorpreise ohne
  Sollreihe) und Luecke 4 (Zustimmung ohne Anker) sind im Abschnitt "Die Grenze des
  Orakels" ausdruecklich als ungeprueft gekennzeichnet; Luecke 3 (Zoll nur aggregiert) ist
  in der Instrumententabelle mit Vorbehalt gefuehrt und als schwerste offene Frage
  benannt; die Aufloesungsluecke (Quartal gegen Jahr) ist zugunsten von Jahresrunden
  entschieden, mit Begruendung und benanntem Ersatz fuer das Innerjahresrisiko. Nur
  **Luecke 1 ist falsch beantwortet** -- Befund 1.
- **Determinismus, gegen Kriterium 3 aus `agentenbau.md`.** T4 (kein Gleitkomma, mit
  `grep`-Nachweis und `clippy::float_arithmetic` auf deny), T6 (eine Rundungsregel,
  symmetrisch ueber dem Vorzeichen -- die Begruendung ueber long/short ist richtig und
  nicht offensichtlich), T9 (Indexlisten statt streuender Behaelter), T10 (Weltschritt
  ohne Ziehung), T11 (abgeleitete statt fortgeschriebener Stroeme -- genau die
  Eigenschaft, an der spaeter "verbessern" gegen "veraendern" haengt), T12 (kanonische
  Byteform statt Speicheranordnung), T28 (feste Iterationszahl statt Konvergenzabbruch).
  Das haelt. **Kein Befund.**
- **Die Rechenzeittabelle, Zeile fuer Zeile nachgerechnet.** 23.400 = 30 x Summe(40-t)
  fuer t = 1..39; 126 = C(9,4), also die Zahl der Fuenftelverteilungen ueber fuenf Arten;
  6.148.800 = 126 x 20 x 2.440; 12.297.600 = das Doppelte; Gesamtsumme 20.056.440, mal
  10 Mikrosekunden = 3,34 Minuten, mal 50 = 16,7 Minuten. Alle Zeilen und beide Spalten
  stimmen. **Kein Befund** -- die Zahl, an der die Stackwahl haengt, traegt. (Ihre
  Gueltigkeit haengt allerdings an der ungenannten Lesart von Mass 3, siehe Befund 5.)
- **Hausregeln.** T21 (kein Netzdienst, keine Zugangsdaten), T23 (der Bau laedt nichts
  aus dem Netz), Abschnitt 11 (macOS-Beglaubigung fuer 99 USD ausdruecklich als
  Gate-Vorlage statt als Plan; gehostete Bauumgebung ebenso). T3 nennt alle
  Abhaengigkeiten unter MIT oder Apache-2.0 abschliessend. **Kein Befund.**
- **Form.** Beide Dateien erfuellen das in ihrer Rollendatei vorgeschriebene Frontmatter
  und die vorgeschriebene Abschnittsfolge vollstaendig. **Kein Befund.**

## Was ich nicht geprueft habe

- Die Lizenzaussagen in `daten.md` -- nicht mein Gegenstand, und die drei ueber
  Suchtreffer statt Seitenabruf belegten Stellen (IWF, OECD, FRED) sind dort selbst
  markiert.
- Ob die Schwellen von Mass 4 (20 Prozent MAPE, 0,6 Richtungstreue) mit endogener
  Produktivitaet ueber 40 Jahre ueberhaupt erreichbar sind. Das ist eine Modellfrage, die
  erst der Rueckvergleicher am laufenden Kern beantworten kann -- kein Entwurfsfehler,
  aber das groesste ungemessene Risiko des Vorhabens.
- Die Zahlenwerte saemtlicher Schwellen. Sie gehoeren nach `spiel.md` in die Kalibrierung
  und nach `technik.md` T27 in `parameter.toml`; das ist konsistent und richtig so.
