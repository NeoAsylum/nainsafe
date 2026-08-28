---
linse: recht
idee: 0009-haushaltsturnus-monatsabrechnung
datum: 2026-08-28
urteil: unklar
schwerster_einwand: Der Zahlungsabgleich, den die Idee selbst in ihre Uebersicht schreibt, ist auf dem naheliegenden Weg ein erlaubnispflichtiger Kontoinformationsdienst nach ZAG — und ohne ihn bleibt ein Rechnungsschreiber, der die volle deutsche Rechnungs-Compliance traegt, ohne die Arbeit abzunehmen, die weh tut.
grenze: G5
---

## Der Einwand

**Zuerst, was haelt — und eine Korrektur an der Idee selbst.** Die Idee fuerchtet an
Zeile 44 die falsche Norm. Der getrennte Ausweis des Arbeitskostenanteils ist **keine**
Hilfeleistung in Steuersachen: Der Betrieb schreibt seine eigene Rechnung, der Dienst ist
das Werkzeug, und die Aufteilung kommt vom Betrieb. Zwei Belege dafuer. Erstens die
Marktnorm: easybill, rechnungwerk und rechnung.de bewerben den getrennten Ausweis von
Lohn- und Materialkosten „fuer § 35a" offen als Produktfunktion — eine Funktion, die alle
etablierten deutschen Rechnungsanbieter offen bewerben, ist nicht die Stelle, an der ein
Nebengewerbe abgemahnt wird. Zweitens der Massstab des BGH: Ein Dokumentengenerator, der
aus Nutzerantworten schematisch Textbausteine zusammensetzt, ist nach BGH I ZR 113/20 vom
09.09.2021 keine Rechtsdienstleistung nach § 2 Abs. 1 RDG, weil die Pruefung des
Einzelfalls fehlt. Eine Rechnung, die Termine summiert, liegt darunter, nicht darueber.
Die Empfehlung der Idee, den Begriff „§ 35a" vorsichtshalber wegzulassen, ist also zu
vorsichtig — sie wirft den Kaufgrund des Haushalts weg, um ein Risiko zu vermeiden, das
an dieser Stelle nicht besteht. **G5 wird durch den Arbeitskostenanteil nicht getroffen.**

Die Idee kippt an vier anderen Stellen, und die erste ist eine Erlaubnispflicht, die
`grenzen.md` gar nicht auffuehrt.

**1. „Ohne Zahlungseingang seit 21 Tagen" ist ein Zahlungsdienst.** Die Uebersicht an
Zeile 51 nennt drei Haushalte ohne Zahlungseingang. Damit muss der Dienst wissen, welches
Geld angekommen ist. Der naheliegende Weg — der Kunde verbindet sein Bankkonto, der
Dienst liest die Umsaetze ueber die Online-Schnittstelle der Bank — ist ein
**Kontoinformationsdienst nach § 1 Abs. 34 ZAG** und nach § 34 ZAG bei der BaFin
registrierungspflichtig, mit laufender Aufsicht und Berufshaftpflicht. Es gibt drei
Auswege, alle teuer: ueber einen lizenzierten Aggregator (kostet Geld, also Gate, und
schafft eine Abhaengigkeit); ueber EBICS statt Online-Banking, wo der Tatbestand nach
verbreiteter Auffassung nicht greift (aber EBICS hat ein Kleinbetrieb nicht); oder
manuelle Eingabe durch den Betrieb — und dann ist genau die Arbeit wieder da, die das
Produkt abnehmen sollte. Die Idee beziffert den Verwaltungsanteil an Zeile 43 selbst auf
einen einstelligen bis niedrig zweistelligen Eurobetrag im Monat; wer davon den
Zahlungsabgleich abzieht, verkauft nichts mehr. Nebenbei ruehrt das an G1: Der
Arbeitgeber ist Finanzdienstleister, und eine Nebentaetigkeit mit BaFin-Registrierung
ist keine, die ohne Rueckfrage genehmigt wird — der `genehmigung`-Wert 5 im Frontmatter
haelt in dieser Ausbaustufe nicht.

**2. Der Wechsel der Umsatzsteuerlage ist ein Dilemma, kein Feature.** Die Zielgruppe
sind Betriebe mit einer bis zehn Kraeften; ein erheblicher Teil davon duerfte
Kleinunternehmer nach § 19 UStG sein (Vermutung, ungeprueft — die Recherche belegt nur
„rund 80 % unter 500.000 EUR Jahresumsatz"). Ein Dienst, der monatlich automatisch
Rechnungen erzeugt, entscheidet damit monatlich ueber den Steuerausweis. Weist er
Umsatzsteuer aus, wo keine geschuldet ist, schuldet der Betrieb den ausgewiesenen Betrag
trotzdem — § 14c Abs. 2 UStG. Bei 42 Haushalten und rund 100 EUR im Monat sind das
knapp fuenfstellige Betraege im Jahr, je Kunde, still, bis der Steuerberater es merkt.
Der Ausweg waere, dass der Dienst den Statuswechsel ueberwacht und warnt — und **das
ist die Wertung**, die § 5 StBerG dem Nichtberater verwehrt. Warnen ist unzulaessig,
nicht warnen erzeugt den Schaden. Genau diese Zange hat Idee 0007 zerlegt, dort beim
Kontieren; hier trifft sie den Kern, weil das Produkt ohne Rechnung nichts ist.

**3. Rechnungen an Verbraucher haben Pflichtinhalte, die dieses Produkt schuldet.** Bei
Leistungen im Zusammenhang mit einem Grundstueck — und die Reinigung einer Wohnung ist
eine — besteht die Pflicht zur Rechnungsstellung binnen sechs Monaten **auch gegenueber
Privatpersonen**, § 14 Abs. 2 Satz 1 Nr. 1 UStG. Solche Rechnungen brauchen den Hinweis
auf die zweijaehrige Aufbewahrungspflicht des privaten Empfaengers, § 14 Abs. 4 Nr. 9
i. V. m. § 14b Abs. 1 Satz 5 UStG; wer die Rechnung nicht oder zu spaet ausstellt,
begeht eine Ordnungswidrigkeit nach § 26a UStG mit bis zu 5.000 EUR. Dazu ein Detail,
das die Uebersicht selbst falsch macht: Gegenueber einem Verbraucher tritt Verzug nach
30 Tagen nur ein, wenn **in der Rechnung** darauf besonders hingewiesen wurde
(§ 286 Abs. 3 BGB). Eine Anzeige „ohne Zahlungseingang seit 21 Tagen" suggeriert einen
Anspruchsstand, den es ohne diesen Satz nicht gibt. Und § 35a Abs. 5 Satz 3 EStG
verlangt neben der Rechnung die **unbare Zahlung** — ein Produkt, das im Feld
„Zahlungsweg" `bar` speichert und daneben trotzdem einen Arbeitskostenanteil ausweist,
erzeugt eine Rechnung, die aussieht wie ein Steuerbeleg und keiner ist.

**4. Die Pflicht, die ein Nebengewerbe nicht mehr abschuetteln kann.** Wer Rechnungen
erzeugt, wird zum Vorsystem der Buchhaltung seines Kunden. Ausgangsrechnungen sind seit
dem 01.01.2025 acht Jahre aufzubewahren (§ 147 AO, § 14b UStG i. d. F. des Vierten
Buerokratieentlastungsgesetzes), unveraendert und nach GoBD revisionssicher. Das ist
keine Erlaubnispflicht, aber es ist eine **Bindung ueber acht Jahre**, die kein
Haftungsausschluss aufhebt: Stellt der Betreiber den Dienst nach zwei Jahren ein, hat
jeder Kunde ein Betriebspruefungsproblem, das er nicht selbst verursacht hat. Ein
Terminplaner darf sterben. Ein Rechnungsschreiber darf es nicht. Das ist der Preis
dafuer, dass die Idee ihren Wert genau in die Rechnung legt und nicht in den Kalender.

**Dazu, ohne selbst toedlich zu sein: Auftragsverarbeitung mit ungewoehnlichem
Risikoprofil.** Der Betreiber wird Auftragsverarbeiter (Art. 28 DSGVO) und braucht mit
**jedem** Kunden einen Vertrag, Unterauftragsverarbeiter offengelegt, Verzeichnis nach
Art. 30 Abs. 2, Loeschkonzept, Meldung an den Verantwortlichen nach Art. 33 Abs. 2. Der
Unterschied zu einem gewoehnlichen Werkzeug liegt im Datensatz: gespeichert werden
Adressen von Privatwohnungen samt Wochentag, Turnus und Zugangsweg — also eine Liste,
wann welche Wohnung leer ist. Das hebt die Anforderungen aus Art. 32 vom Formalen ins
Reale und macht eine Panne zu einem Fall des Art. 34, also der Benachrichtigung jedes
einzelnen Haushalts. Zwei Nebenfunde: Ein freies Textfeld fuer den Absagegrund faengt
Gesundheitsdaten nach Art. 9 ein („Krankenhaus", „krank") — also geschlossene Auswahl
statt Freitext. Und die Einsatzdaten (Datum, Dauer, ausfuehrende Kraft, Zeile 52) liegen
in einem Gewerbe, das in § 2a SchwarzArbG steht und der Aufzeichnungspflicht nach
§ 17 MiLoG unterliegt (belegt in `research/...`, Abschnitt 5e). Der Dienst fuehrt damit
eine Schattenaufzeichnung, die keine ist — er speichert Dauer, nicht Beginn und Ende.
Wird sie im Verkauf als Arbeitszeitnachweis angeboten, ist sie unvollstaendig und der
Betrieb haftet fuer die Luecke.

## Was ihn entkraeften wuerde

Es gibt einen Zuschnitt, der haelt. Fuenf Bedingungen, alle notwendig:

1. **Kein Zugriff auf Bankdaten, in keiner Ausbaustufe.** Der Zahlungsstand wird vom
   Betrieb gesetzt oder aus einer Datei importiert, die er selbst exportiert hat. Damit
   entfaellt § 1 Abs. 34 ZAG. Ob das Produkt ohne diese Funktion noch gekauft wird, ist
   eine Nachfragefrage — sie zu bejahen ist die Bedingung dafuer, dass die Idee legal
   ueberhaupt existieren darf.
2. **Der Umsatzsteuerstatus ist eine Eingabe, nie ein Ergebnis.** Der Betrieb setzt
   Kleinunternehmer ja/nein und den Steuersatz; das Produkt warnt nicht, prognostiziert
   nicht und beobachtet keine Umsatzgrenze. Kein Satz im Produkt, der eine
   steuerliche Folge behauptet.
3. **Der Arbeitskostenanteil bleibt eine Zahl des Betriebs — aber er darf so heissen.**
   Kein voreingestellter Prozentsatz, kein Hilfetext „meist 100 %", keine Pruefung, ob
   der Abzug beim Haushalt zulaessig ist. Das Wort § 35a darf in der Rechnungsvorlage
   stehen, weil die Marktnorm es hergibt; die *Bewertung* darf es nicht.
4. **Mahnen ja, einziehen nein.** Der Betrieb mahnt im eigenen Namen — das ist keine
   Einziehung fremder Forderungen nach § 2 Abs. 2 RDG. Sobald der Dienst im eigenen
   Namen einzieht, Forderungen abtreten laesst oder Verzugszinsen und Mahnkosten selbst
   berechnet, ist es Inkasso mit Registrierungspflicht nach § 10 RDG. Der
   Verbraucherhinweis nach § 286 Abs. 3 BGB gehoert in die Rechnungsvorlage, sonst ist
   die Faelligkeitsanzeige irrefuehrend.
5. **Der Ausstieg wird vor dem Einstieg gebaut.** Vollstaendiger, jederzeitiger Export
   aller Rechnungen in einem lesbaren Format, vertraglich zugesagt, plus die Ansage an
   den Kunden, dass die Aufbewahrung ueber acht Jahre seine Pflicht bleibt und er
   exportieren muss. Ohne das ist die Abschaltung des Dienstes ein Schaden bei jedem
   Kunden gleichzeitig.

**Was das Urteil auf `widerlegt` drehen wuerde:** wenn die Nachfragepruefung ergibt,
dass der Zahlungsabgleich der eigentliche Kaufgrund ist. Dann ist der zulaessige
Zuschnitt unverkaeuflich und der verkaeufliche erlaubnispflichtig. Auf `haelt` drehen
wuerde es, wenn Bedingung 1 und 2 unstreitig sind und ein Musterexport nachgewiesen ist.
Beides kann ich aus der Idee nicht klaeren — deshalb `unklar`.

**Fuer den Anwalt, drei Fragen, zehn Minuten:**
(a) Ist das Einlesen von Kontoumsaetzen zum Rechnungsabgleich ueber einen lizenzierten
Drittanbieter fuer den Betreiber selbst erlaubnisfrei, oder wird er Mitanbieter eines
Kontoinformationsdienstes nach § 1 Abs. 34 ZAG?
(b) Ist eine Warnung „Sie naehern sich der Kleinunternehmergrenze" bereits Hilfeleistung
in Steuersachen nach § 5 StBerG, oder faellt sie unter die zulaessige Information?
(c) Traegt eine Haftungsbegrenzung auf das Entgelt, wenn ein Fehler des Steuerausweises
eine Steuerschuld nach § 14c Abs. 2 UStG ausloest, die das Jahresentgelt um
Groessenordnungen uebersteigt — oder ist der richtige Steuerausweis Kardinalpflicht
i. S. d. § 307 Abs. 2 Nr. 2 BGB?

## Quellen

- Idee `ideas/0009-haushaltsturnus-monatsabrechnung.md`, Zeilen 13, 36, 43, 44, 51, 52,
  gelesen 2026-08-28.
- `research/2026-08-28-vertikale-software-privathaushalts-reinigungsfirmen.md`,
  Abschnitt 5e (§ 2a SchwarzArbG, § 28a Abs. 4 SGB IV, § 17 MiLoG fuer das
  Gebaeudereinigungsgewerbe), gelesen 2026-08-28.
- `ideas/0007-marktplatz-csv-in-buchhaltungsformat.md`, `ablehnungsgrund`, und
  `ideas/0002-ki-kennzeichnung-nachweisakte.md`, `ablehnungsgrund`, gelesen 2026-08-28.
- **Heute per Suche bestaetigt, jeweils ueber Sekundaerquellen, nicht am Gesetzestext:**
  § 35a Abs. 5 Satz 3 EStG (Rechnung, unbare Zahlung, Aufteilung nach Arbeits- und
  Materialkosten) — `easybill.de`, `rechnungwerk.de`, `kostenlose-erechnung.de`,
  abgerufen 2026-08-28. § 14 Abs. 2 Satz 1 Nr. 1, § 14 Abs. 4 Nr. 9, § 14b Abs. 1
  Satz 5, § 26a UStG — `lstn.niedersachsen.de`, `ihk.de/stuttgart`,
  `deubner-steuern.de`, abgerufen 2026-08-28. § 1 Abs. 34, § 34 ZAG und die
  EBICS-Abgrenzung — `bafin.de` (Merkblatt ZAG), `paytechlaw.com`, `payment-law.eu`,
  abgerufen 2026-08-28. BGH I ZR 113/20 vom 09.09.2021 — `bundesgerichtshof.de`,
  `lto.de`, `brak.de`, abgerufen 2026-08-28. Acht Jahre Aufbewahrung seit 01.01.2025
  (BEG IV, § 147 AO / § 14b UStG) — `haufe.de`, `lexware.de`, abgerufen 2026-08-28.
- **Normen aus Kenntnis, in diesem Lauf nicht gegen die amtliche Fassung geprueft**
  (der Abruf von gesetze-im-internet.de war erneut nicht moeglich, WebFetch verweigert):
  § 2 Abs. 1 und Abs. 2, § 10 RDG; § 5, § 6 Nr. 3 und Nr. 4 StBerG; § 14c Abs. 2,
  § 19 UStG; § 286 Abs. 3, § 288, § 307 Abs. 2 Nr. 2 BGB; Art. 9, 28, 30 Abs. 2, 32,
  33 Abs. 2, 34, 82 DSGVO. Vor einer Gate-Vorlage nachzuschlagen.
- **Vermutung, ungeprueft:** dass ein erheblicher Teil der Zielgruppe Kleinunternehmer
  nach § 19 UStG ist. Aus der Betriebsgroesse geschlossen; die Recherche belegt nur die
  Umsatzhuelle. Waere vor Gate 1 an fuenf Betriebswebseiten billig zu pruefen — wer
  keine Umsatzsteuer ausweist, sagt es meist im Impressum oder auf der Preisseite.
- **Vermutung, ungeprueft:** dass Reinigungsleistungen in der Privatwohnung
  umsatzsteuerlich als grundstuecksbezogene Leistung gelten und damit unter die
  Sechsmonatsfrist des § 14 Abs. 2 UStG fallen. Die Quellen nennen die Regel allgemein
  fuer Grundstuecksleistungen, nicht ausdruecklich fuer die Unterhaltsreinigung.
</content>
</invoke>
