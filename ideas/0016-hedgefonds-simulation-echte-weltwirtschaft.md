---
id: 0016-hedgefonds-simulation-echte-weltwirtschaft
titel: Hedgefonds-Simulation auf echten Weltwirtschaftsdaten, mit nachvollziehbarer Wirkungskette
status: entwurf
erstellt: 2026-08-31
geaendert: 2026-08-31
rolle: ideator

quelle: signals/maerkte/2026-08-31-volkswirtschafts-und-politiksimulation.md

segment: Kaeufer von Politik- und Wirtschaftssimulationen auf Steam (Tag "Political Sim", 26921) im englischsprachigen Raum -- rund 2,9 Mio gemessene Kaeufe der sieben Kerntitel des Tags, Preisbereitschaft belegt zwischen 28,99 und 59,99 EUR
problem: Ueber drei unabhaengige Titel hinweg beklagen Rezensenten nicht fehlenden Inhalt, sondern eine Wirkungskette, der sie nicht glauben -- "the consequences of choices often feel intangible" (Democracy 4), "everything is incredibly surface level" (Geo-Political Simulator 2026), "already the richest hedge fund in the game ($5 trillion) and nothing fun to do" (Hedge Fund Tycoon, 2.349 Minuten Spielzeit)
loesung: Rundenbasierte Simulation der echten Weltwirtschaft, in der der Spieler ein Hedgefonds ist und ueber Positionen, Beteiligungen und Lobbybudgets Regulierung verschiebt -- und in der jede Zahlenaenderung als vollstaendige Ursachenkette abrufbar ist, weil dieselbe Kette der Regressionstest der Entwicklung ist
zahlungsgrund: wunsch

suchraum: endkunden
preis: 24,99          # EUR Grundspiel, einmalig; Lebenswert je Kaeufer 49,98 EUR nach Capitalism-Lab-Muster
kunden_noetig: 170    # Kaeufer je Monat, dauerhaft, bei 29,40 EUR netto Lebenswert
kunden_erreichbar: 121 # Kaeufer je Monat (ein Promille von 2,9 Mio ueber 24 Monate)

ablehnungsgrund: null

score:
  zwang: null
  erreichbar: null
  ruhe: null
  marge: null
  genehmigung: null
  summe: null
---

## Belege

### Die toedliche Frage, vorab geklaert: Ist der Zuschnitt besetzt?

Nein. Vier Titel fassen ihn an, keiner liefert ihn. Alle Bewertungszahlen am
2026-08-31 ueber `store.steampowered.com/appreviews/<appid>?json=1&num_per_page=0&language=all&purchase_type=all`
abgerufen.

- **Hedge Fund Tycoon** (Stikcy, App 2310900, erschienen 2024-01-07, **5,89 EUR**) ist der
  naechstliegende Treffer und nennt Politik und Korruption ausdruecklich: "insider
  trading, manipulating the market, or using your connections to gain an edge"
  (store.steampowered.com/app/2310900/, abgerufen 2026-08-31). Ergebnis nach
  **31 Monaten: 24 Bewertungen, 11 positiv, 13 negativ, "Mixed".** Die negativen
  Volltexte nennen zweimal fehlende Grundfunktionen ("Game Save and Game Load is still
  in developing", 194 Min) und einmal genau den Befund des Marktprofils:
  **"Boring game, already the richest hedge fund in the game ($5 trillion) and nothing
  fun to do." (2.349 Min)** -- ein Spiel ohne Verschiebung des Optimums, also der
  Defekt, den `agentenbau.md` als berechenbar auffuehrt.
- **Wall Street Raider** (Ronin Software/Hackjack Games, App 3525620, erschienen
  2026-05-14, 25,99 EUR): **216 Bewertungen, 203 positiv, "Very Positive"**. Tiefes
  Finanzmodell, aber **erfundene Welt, keine echten Wirtschaftsdaten**; Politik nur als
  Prozessmechanik ("File harassing lawsuits to drain competitors through legal fees.
  Launch antitrust suits to break up rivals."), kein Regulierungsapparat
  (store.steampowered.com/app/3525620/, abgerufen 2026-08-31).
- **FinSim** (App 4881490, Early Access): 63 Bewertungen, 43 positiv, "Mixed".
- **The Invisible Hand** (App 628200, 2020): 692 Bewertungen, 558 positiv, "Very
  Positive" -- aber der Spieler ist ein angestellter Haendler, nicht der Fonds, und die
  Welt ist erfunden.

Damit ist die Achse, die `agentenbau.md` als staerkste bezeichnet -- **echte Daten als
Orakel** --, in diesem Zuschnitt von niemandem belegt. Der einzige Titel mit derselben
Rollenwahl kostet 5,89 EUR und ist in 31 Monaten auf 24 Bewertungen gekommen.

### Die Datenlizenz, soweit vorab klaerbar

Die Weltbank lizenziert ihre oeffentlichen Datensaetze unter **CC-BY 4.0**; die Lizenz
"allows users to copy, modify and distribute data in any format for any purpose,
**including commercial use**", einzige Auflage ist Namensnennung und Kennzeichnung von
Aenderungen (datacatalog.worldbank.org/public-licenses, abgerufen 2026-08-31). Damit ist
die Bedingung aus `agentenbau.md` -- "Die Lizenz muss gewerbliche Weiterverbreitung
erlauben" -- fuer die Kernzeitreihen (BIP, Bevoelkerung, Inflation, Handelsvolumen,
Staatsschuld) erfuellt. Was daran offen bleibt, steht unter **Offene Fragen**.

### Die sechs Fragen aus `agentenbau.md`

1. **Kann ein Bot es spielen?** Ja. Quartalsrunden, diskrete Aktionen aus drei Familien
   (Position auf Land/Sektor/Waehrung; Beteiligung an einem Sektor; Lobbybudget auf ein
   Politikinstrument). Kein Timing, kein Zielen, keine Echtzeit.
2. **Ist der Zustand die Wahrheit?** Ja. Das Spiel ist ohne Darstellung vollstaendig
   spielbar; die Oberflaeche ist Tabelle und Diagramm. Das Genre traegt das belegt:
   Democracy 4 verkauft sich mit einer 2D-Knotenoberflaeche (Steam-Tags: 2D, Minimalist)
   und besteht in seiner Simulation vollstaendig aus CSV-Dateien
   (positech.co.uk/democracy4/modding.html, abgerufen 2026-08-31).
3. **Deterministisch und reproduzierbar?** Vorgabe, nicht Hoffnung: Ganzzahlarithmetik
   (Betraege in Cent, Raten in Basispunkten, Anteile in Zehntelprozent), fester
   Zufallsstartwert, begrenzte Rueckkopplungstiefe. `agentenbau.md` nennt genau das als
   wunden Punkt der Weltsimulation -- deshalb ist die kleinste Fassung auf
   **12 Laender x 6 Sektoren** gedeckelt statt auf alle Volkswirtschaften.
4. **Ist die Qualitaet eine Zahl?** Hier faellt die Luecke mit der Staerke der Fabrik
   zusammen, und das ist der eigentliche Grund fuer diese Idee. Siehe **Rechnung**,
   unten -- dort stehen die drei Masse und die vierte Pruefachse als Formeln.
5. **Entsteht Inhalt aus Regeln?** Ja. Inhalt sind Startjahrgaenge (Datentabellen) und
   Szenarien aus Regeln -- kein handgeschriebenes Ereignisbuch, also kein Inhaltslaufband
   nach G4.
6. **Wie oft muss jemand ueber Gestaltung entscheiden?** Quartalsweise. Die Oberflaeche
   ist Tabelle und Verlaufsgraph; das eine Stueck Gestaltung, das kein Agent abnimmt,
   ist das Kapselbild -- es steht unter **Offene Fragen**.

### Der Zustand als Text (G8), drei Ebenen

- **Uebersicht**, eine Zeile je Land, zwoelf Zeilen gesamt:
  `DE | BIP 3.412 | Zins 250bp | Zoll 38bp | Haushalt -2,1% | Fondsanteil 4,2% | Einfluss 17/100`
- **Detail**, ein Land vollstaendig: sechs Sektoren mit Produktion, Preis und
  Beschaeftigung; Handelsstroeme zu den elf anderen; fuenf Politikinstrumente mit Stand,
  anliegendem Lobbydruck und Verzoegerung; alle Positionen des Fonds.
- **Veraenderung**, Diff zwischen zwei Quartalen -- und zwar als Kette, nicht als Liste:
  `Q3->Q4: Zoll +5pp (deine Lobbyaktion aus Q1, Verzoegerung 2 Quartale)`
  `  -> Importpreis Sektor 3 +2,1% -> Realeinkommen -0,4% -> Zustimmung Regierung -1,2`
  `  -> dein Bestand Sektor 3 +8,3%`

**Diese dritte Ebene ist zugleich das Produkt, der Regressionstest und die Antwort auf
die Beschwerde.** Der Spieler kauft, weil er die Kette sehen will ("the consequences
often feel intangible"); der Agent baut damit, weil die Kette der Diff ist, gegen den er
jede Aenderung prueft. Dass beides derselbe Gegenstand ist, ist der Fund des
Marktprofils: das erste Segment des Repos, in dem der ungeloeste Wunsch der Kaeufer und
die messbare Staerke der Fabrik zusammenfallen.

### Der Kanal

Valve veranstaltet ein eigenes **Steam Political Sim Fest** und fuehrt die dauerhafte
Kategorieseite `store.steampowered.com/category/political_sim`; Anmeldung laeuft ueber
Steamworks, ohne Mittler und ohne Gespraech (Marktprofil, Abschnitt 6). Das ist nach
Hausregel 2 zulaessig und nach G3 selbstbedienbar.

## Rechnung

**Preis.** Grundspiel **24,99 EUR** einmalig. Belegt am naechstgroesseren Vollprodukt
des Segments und bewusst darunter, weil dies ein Erstlingstitel ohne Reihe ist:
Wall Street Raider 25,99 EUR (2026-05-14), Democracy 4 28,99 EUR, Victoria 3 49,99 EUR,
Geo-Political Simulator 2026 59,99 EUR (alle abgerufen 2026-08-31).

**Lebenswert je Kaeufer 49,98 EUR**, also Faktor 2,0 auf das Grundspiel. Belegt am
einzigen wiederkehrenden Modell des Genres, das oeffentlich bepreist ist: Capitalism Lab
verkauft das Grundspiel fuer 19,99 USD und das Buendel mit vier Erweiterungen fuer
39,99 USD (capitalismlab.com/buy-game/ und /pricing_info/, abgerufen 2026-08-31). Die
Erweiterung ist hier der zusaetzliche Startjahrgang oder das zusaetzliche Szenario.

**Netto je Kaeufer:** 49,98 EUR brutto / 1,19 (USt, EUR-Preise auf Steam sind brutto)
= 42,00 EUR; davon 70 Prozent nach Plattformanteil = **29,40 EUR**.

**Noetig fuer 5.000 EUR:** 5.000 / 29,40 = **170 Kaeufer je Monat, dauerhaft.**

**Erreichbar**, gerechnet auf die 2,9 Mio gemessenen Kaeufe des Tags, ueber 24 Monate:

| Anteil | Kaeufer gesamt | je Monat | Monatsumsatz |
|---|---:|---:|---:|
| ein Promille | 2.900 | 121 | **3.557 EUR** |
| ein Prozent | 29.000 | 1.208 | 35.515 EUR |
| Vergleichsfall Kohortenspitze | 4.860 | 286 | 8.408 EUR |

**Ich setze das Promille an und nenne das Ergebnis unbeschoenigt: 3.557 EUR, also
71 Prozent der Schwelle.** Die Begruendung fuer den Anteil, wie G7 sie verlangt: Der
Kanal ist belegt und selbstbedienbar, was formal fuer das Prozent spraeche -- aber die
ungefilterte Startkohorte des August 2026 im selben Tag hat einen Median von
8,5 Bewertungen, also rund 255 Einheiten insgesamt. Das Prozent waere Hoffnung.

Die dritte Zeile ist der Vergleichsfall, den G7 fuer einen Ansatz oberhalb des Promille
ausdruecklich zulaesst: **Maestro's Cold War 2**, bester Titel derselben Augustkohorte,
162 Bewertungen nach 17 Monaten Early Access = rund 4.860 Einheiten = 286 je Monat. Er
selbst erreicht damit nur 1.965 EUR im Monat -- **weil er 11,69 EUR kostet.** Bei einem
Lebenswert auf dem Preisniveau der etablierten Simulationen desselben Genres traegt
derselbe Absatz 8.408 EUR. Der Hebel dieser Idee ist also nicht mehr Absatz, sondern der
Preis, und der ist am Segment belegt.

**Kosten.** Das Produkt laeuft lokal beim Kaeufer: keine Server, kein Konto, keine
Agentenkosten je Kunde nach G7. Wiederkehrender Aufwand ist die jaehrliche
Datenaktualisierung -- ein Agentenlauf **je Jahr**, nicht je Kunde. Einmalig fallen
100 USD Steam-Direct-Gebuehr je Titel an; das ist eine Ausgabe nach Hausregel 1 und damit
eine Gate-Vorlage, kein Betriebskosten-Posten. Umsatz und Marge fallen hier also
weitgehend zusammen.

### Wie die drei Masse aus `agentenbau.md` in diesem Spiel berechnet werden

`agentenbau.md` verlangt das im Entwurf, nicht in der Nachbereitung. Alle drei laufen im
Selbstspiel, ohne Darstellung, ueber dieselbe Zustandsschnittstelle:

- **Entscheidungsdichte** = Anteil der legalen Aktionen eines Zuges, die das Endvermoegen
  nach 20 Quartalen um mehr als eine Schwelle veraendern. Ein Spiel, in dem neun von zehn
  Zuegen gleichgueltig sind, faellt hier durch, und das ist die Zahl hinter
  "consequences feel intangible".
- **Strategievielfalt** = Zahl der Aktionsprofile (reine Marktposition, reine
  Beteiligung, reines Lobbying und die Mischungen), die das Ziel erreichen. Gewinnt nur
  eines, ist das Spiel geloest -- das ist die Zahl hinter "trying to implement the
  tiniest socialist policy will always result in bankruptcy".
- **Verschiebung des Optimums** = Abstand zwischen dem besten Aktionsprofil der ersten
  und dem der letzten acht Quartale. Ist er null, ist es ein Laufband -- das ist die
  Zahl hinter "already the richest hedge fund in the game and nothing fun to do".
- **Vierte Pruefachse:** Startjahrgang laden (etwa 2000), das Modell 60 Quartale ohne
  Spieler laufen lassen, die zwoelf BIP-, Inflations- und Handelsreihen gegen die
  tatsaechlichen Weltbankreihen halten, Abweichung als Fehlermass je Reihe. Das ist ein
  Regressionstest, kein Gefuehl. Seine Grenze gehoert dazu: Er prueft die Dynamik der
  Maschine ueber den historischen Zeitraum und sagt nichts ueber den Ast, den der Spieler
  betritt.

## Offene Fragen

- **Datenlizenz, gewerbliche Weiterverbreitung -- der geklaerte und der offene Teil.**
  Geklaert ist die Weltbank (CC-BY 4.0, kommerzielle Nutzung und Weiterverbreitung
  erlaubt, siehe **Belege**). Offen ist, ob die Weltbank allein reicht: **bilaterale
  Handelsstroeme** sind der Kern des Aussenhandelsteils, und die uebliche Quelle dafuer
  ist UN Comtrade, dessen Bedingungen ich nicht geprueft habe; dasselbe gilt fuer IWF
  (IFS) und OECD. Untersagt eine davon die Weitergabe im Bulk, muss der Kern auf
  Weltbank-Aggregate zurueckgeschnitten werden -- das kostet den Aussenhandelsteil in
  seiner feinen Form, nicht das Produkt. Zu klaeren, bevor gebaut wird, nicht bevor
  bewertet wird.
- **Einmalkauf gegen wiederkehrendes Modell.** Die Rechnung oben traegt beim Promille
  nur mit dem Erweiterungsmodell (Faktor 2,0 auf das Grundspiel). Das Genre belegt beide
  Formen -- Capitalism Lab mit bepreisten Erweiterungen, Eversim mit einer Jahresausgabe
  zu 59,99 EUR. **Eversim wird dafuer aber beschimpft:** "Shameless cash grab. Same game
  as last year, same price, only minor differences" (8.847 Min, Geo-Political Simulator
  2026, 49 Prozent positiv). Die Frage ist deshalb nicht ob, sondern was verkauft wird:
  ein neuer Datenjahrgang allein ist offenbar keine Erweiterung im Sinne der Kaeufer,
  ein neues Szenario mit eigenen Zielen und eigenen Instrumenten moeglicherweise schon.
  Ungeklaert.
- **Steam-Direct-Gebuehr 100 USD je Titel** -- eine Ausgabe und damit Hausregel 1. Sie
  braucht eine Gate-Vorlage, bevor irgendetwas veroeffentlicht wird.
- **Das Kapselbild.** Das Genre verlangt weniger Bildarbeit als jedes andere bisher
  geprueftes (Democracy 4 verkauft sich mit Diagrammen), aber nicht null. Wer es macht,
  ist offen -- und ein Auftrag daran waere eine Ausgabe.
- **Verbraucherrecht bei Endkunden.** Widerrufsrecht von vierzehn Tagen, Verbraucher-AGB,
  Preisangaben. Auf Steam tritt Valve als Verkaeufer gegenueber dem Endkunden auf; ob
  Valve damit die Rolle des Merchant of Record im Sinne von G7 vollstaendig ausfuellt und
  die Umsatzsteuerregistrierung im Zielland entfaellt, habe ich nicht geprueft. Das ist
  eine Frage an die Rechtslinse, keine, die diesen Entwurf traegt.
- **Bleibt das Modell mit zwoelf Laendern rueckkopplungsarm genug fuer Determinismus?**
  Ganzzahlarithmetik und gedeckelte Kopplungstiefe sind die Vorgabe; ob sie reicht, misst
  man am Prototyp und behauptet es nicht vorab. `agentenbau.md` nennt genau diesen Punkt
  als wunden Punkt der Weltsimulation.
- Aus dem Marktprofil uebernommen: der Boxleiter-Faktor 30 traegt jede Einheitenzahl
  oben; waere er 60, verdoppelten sich alle Umsatzzahlen. Und 1.022 gegen 622 Titel im
  selben Tag, je nach Sortierung, ist nicht aufgeloest.

## Warum jetzt

Vier Dinge, und die Datenlizenz ist ausdruecklich keines davon -- die Weltbank steht seit
Jahren unter CC-BY.

1. **Der Suchraum ist seit dem 2026-08-31 ueberhaupt offen.** Unterhaltung ist mit
   ADR 0008 zugelassen, `zahlungsgrund: wunsch` existiert seit heute, und die
   Genehmigungsfrage zu Finanzmaerkten und Lobbyismus hat der Betreiber am selben Tag
   entschieden (grenzen.md, Bewertungstabelle). Vor einem Jahr waere dieser Entwurf
   regelwidrig gewesen, nicht schlecht.
2. **Dass der Zuschnitt frei ist, ist erst jetzt messbar.** Hedge Fund Tycoon steht seit
   2024-01-07 im Store; erst nach 31 Monaten und 24 Bewertungen laesst sich sagen, dass
   der Versuch gescheitert ist und nicht bloss jung.
3. **Wall Street Raider erschien am 2026-05-14** und hat in gut drei Monaten
   216 Bewertungen bei "Very Positive" gesammelt -- der frische Beleg, dass ein tiefes
   Finanzmodell 2026 Kaeufer findet, und zwar ohne echte Daten und ohne Politik. Genau
   die beiden Achsen, die hier hinzukommen.
4. **Der Vorteil der Fabrik ist neu, nicht das Genre.** Ein Agentenschwarm, der eine
   Balance millionenfach durchspielt und zusaetzlich gegen echte Zeitreihen prueft, war
   fuer ein Ein-Personen-Studio bis vor kurzem nicht bezahlbar. Das ist der einzige
   Vorsprung, den dieses Unternehmen gegenueber Positech hat -- und er wirkt genau auf
   den Defekt, ueber den die Kaeufer aller drei Vergleichstitel klagen.
