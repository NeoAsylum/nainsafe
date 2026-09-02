---
typ: recherche
signal: signals/market/2026-08-28-microsoft-project-online-abkuendigung.md
erstellt: 2026-08-28
segmentgroesse: nicht ermittelbar (drei kommerzielle Firmendatenbanken nennen 629, 1.370 und 41.359 Kunden weltweit — Faktor 66; keine mit Laenderaufschluesselung fuer Deutschland, Microsoft veroeffentlicht keine Zahl)
anbieter_gefunden: 38 namentlich (7 Migrationswerkzeuge, davon eines vom Hersteller und kostenlos; 15 Ersatzprodukte; 16 Dienstleister, davon 5 mit deutschsprachigem Angebot)
preisspanne: 8,70-26,00 EUR je Nutzer und Monat fuer die Nachfolgelizenz (Microsoft Deutschland, offizielle Preisseite); Migrationsprojekte fuenf- bis sechsstellig
ampel: rot
---

# Microsoft schaltet Project Online am 30.09.2026 endgueltig ab; drei der vier Meilensteine des Signals sind bereits verstrichen, der letzte liegt 33 Tage voraus

**Der Kern dieses Laufs steht vorweg, weil er jede weitere Frage ueberlagert:** Das
Signal meldet einen Stichtag, der am Tag dieser Recherche **33 Tage entfernt** ist
(30.09.2026 gegen heute 2026-08-28). Von den vier Meilensteinen, die das Signal
auffuehrt, liegen drei in der Vergangenheit — Verkaufsstopp 01.10.2025, Sperrung
neuer PWA-Sites 01.04.2026, Abschaltung der SharePoint-2013-Workflows 02.04.2026.
Uebrig ist allein das Ende. Eine Idee, die aus diesem Signal entsteht, muesste
Konzeption, Angriffslaeufe, Spezifikation, Bau und Vertrieb in vier Wochen
durchlaufen — und danach gaebe es das Problem nicht mehr, weil es keine Nachlauf-,
Read-only- oder Verlaengerungsphase gibt (siehe Abschnitt 5).

Die zweite Behauptung des Signals ist ebenfalls ueberholt. Dort steht: *„Kein
unabhaengiger Drittanbieter positioniert sich bislang oeffentlich als direkter Ersatz
fuer deutsche PMOs."* Tatsaechlich tun das mindestens fuenf deutschsprachige Haeuser
mit eigenem Produkt oder eigener Landingpage, zwei davon mit kostenloser
Erstberatung — und international sind es Dutzende.

## 1. Groesse des Segments

**Nicht ermittelbar. Microsoft veroeffentlicht keine Kunden-, Tenant- oder
Nutzerzahl fuer Project Online, und die drei kommerziellen Datenbanken, die es
versuchen, widersprechen sich um den Faktor 66.**

| Quelle | genannte Zahl | Charakter |
|---|---|---|
| appsruntheworld.com | „629 entries" | kuratierte Referenzkundenliste |
| enlyft.com | „1,370 companies use Microsoft Project Online" | Technografie-Schaetzung, Datenbasis „5 years and 8 months" |
| elpdata.com | „41,359 verified companies worldwide" | Adressbestand fuer Leadgenerierung |

(alle abgerufen 2026-08-28: `appsruntheworld.com/customers-database/products/view/microsoft-project-online`,
`enlyft.com/tech/products/microsoft-project-online`, `elpdata.com/app/microsoft-project-online`)

**Keine der drei Quellen bricht auf Deutschland herunter.** Enlyft nennt nur
*„53% of Microsoft Project Online customers are in United States, 9% are in United
Kingdom and 7% are in Canada"* — Deutschland taucht in der Aufzaehlung gar nicht auf.
Elpdata gibt lediglich „190+ Countries Covered" an. Es sind ausserdem alles
Adressbestaende von Leadgenerierern, keine Marktzahlen; sie zaehlen, wen der jeweilige
Anbieter erfasst hat, nicht wen es gibt.

**Warnung zur Belastbarkeit, weil sie meine eigene Regel bestaetigt:** Die
Suchzusammenfassung nannte fuer elpdata souveraen „18,108 verified customers". Beim
Abruf der Seite selbst stand dort **41.359**. Die Zahl aus der Zusammenfassung existiert
auf der Quellseite nicht. Keine der hier genannten Zahlen darf als Segmentgroesse
weiterverwendet werden.

**Verwertbar ist allein die Groessenstruktur, und sie ist eindeutig:**

- enlyft: *„19% are small (<50 employees), 32% are medium-sized and 48% are large
  (>1000 employees)"*
- appsruntheworld: 9,38 % ueber 10.000 Beschaeftigte, 23,37 % zwischen 1.001 und 10.000;
  Branchenschwerpunkte *„Aerospace and Defense, Government and Banking and Financial
  Services"*; namentlich RTX Corporation, Lockheed Martin, NSW Government, American Express
- elpdata: 40 % Mid-Market (500-4.999), 25 % Enterprise (5.000+)

**Der einzige belastbare Hinweis auf den deutschsprachigen Raum ist eine
Referenzkundenliste, und sie zeigt dasselbe Bild.** Das Beratungshaus Holert nennt als
eigene Kunden im Kontext dieser Abschaltung: *„KPT, Rohde & Schwarz, KUKA, Amer Sports,
KWS, LAPP, Stadtreinigung Hamburg, Accompio, Frischli, Swoboda and SteelcoBelimed
(Miele)"* (`holert.com/en/blog/microsoft-project-online-ends-alternatives`, abgerufen
2026-08-28). Das sind Konzerne und grosse Mittelstaendler mit Einkaufsabteilung und
Lieferantenpruefung.

Auch die deutschsprachige Fachpresse nennt keine Zahl: weder The Project Group
(`theprojectgroup.com/blog/project-online-ende-2026/`) noch Campana & Schott
(`campana-schott.com/de/de/unternehmen/publikationen/detail/microsoft-stellt-project-online-ein-was-sie-jetzt-wissen-sollten`),
beide abgerufen 2026-08-28. Das Signal selbst nennt ebenfalls keine.

## 2. Wer es heute bedient

**Dicht besetzt, in drei Schichten. Ich habe deutsch und englisch, ueber Produkt-,
Migrations- und Archivformulierungen gesucht; jede Suche brachte neue Namen, keine
brachte eine Luecke.**

**Schicht 1 — Der Hersteller selbst, mit drei Wegen und einem kostenlosen Werkzeug.**
Microsoft nennt Project Server Subscription Edition (behaelt die gewohnte
PWA-Oberflaeche), Planner mit Premium-Funktionen und Dynamics 365 Project Operations.
Dazu kommt der **kostenlose Project/Planner Accelerator** auf Power-Platform-Basis —
in der offiziellen Microsoft-Q&A ausdruecklich als empfohlener Migrationsweg genannt:
*„Importing .mpp is not available in Planner's main UI and the recommended instead is
using Planner Power App/Accelerator for migrating"*
(`learn.microsoft.com/en-us/answers/questions/5846989/...`, abgerufen 2026-08-28).
Dieselbe Antwort raeumt ein: *„Unfortunately, there is no native and automatic path to
migrate from PWA to Planner Premium"* — und verweist die Fragenden dann namentlich an
**FluentPro** und **Sensei Project Solutions**. Der Hersteller macht die Drittanbieter
also selbst zur offiziellen Antwort.

**Schicht 2 — Migrationswerkzeuge (7 namentlich).** FluentPro FluentBooks (Desktop,
Ziel Project Server), FluentPro Project Migrator (Cloud, Ziel Planner Premium,
Dynamics 365 Project Operations, Asana, Trello, monday.com, Smartsheet), Gantt2Plan
(ausschliesslich fuer diesen einen Migrationspfad gebaut, mappt Enterprise Custom
Fields auf Planner-Spalten), ShareGate, EZImport, Project Data Suite von WACG Inc.
(`projectmigration.io`), sowie der genannte Microsoft-Accelerator. **FluentPro gibt
an, „over 1000 organizations" migriert zu haben** (`fluentpro.com/project-online-migration/`,
abgerufen 2026-08-28) und bietet zusaetzlich *„Managed Cloud Migration Services where
all work is done for you"*.

**Schicht 3 — Ersatzprodukte, die sich ausdruecklich als Project-Online-Nachfolger
positionieren (15 namentlich):** TPG ProjectPowerPack (The Project Group, Muenchen),
CS PPM Power Suite (Campana & Schott, Frankfurt), edison365, Altus PPM (Hersteller
Sensei), Projectum xPM (Hersteller Context&), Wellingtone Accelerator+, BrightWork 365,
Onplana, OnePlan, Epicflow, Zeno.PM, Tempo, Celoxis, Smartsheet, Adobe Workfront.

**Dienstleister mit fertiger Landingpage zu genau diesem Stichtag (16):**
deutschsprachig The Project Group, Campana & Schott, Holert, Medialine, IT-HAUS;
international Wellingtone, Sensei Project Solutions, Advaiya, Velosio, Inetum, Easy8,
ClonePartner, apps4rent, Advisicon, msprojectpros.com, msprojectmigration.com. Dazu
das Fachmagazin projektmagazin.de mit einem eigenen Alternativen-Artikel.

**Zwei Saettigungsindikatoren aus meinem Logbuch treffen hier zu, beide in der
schaerfsten Form:** Die zwei groessten deutschen PPM-Beratungshaeuser **verschenken
die Erstberatung**. Campana & Schott: *„Wir bieten eine kostenlose Erstberatung an, um
die aktuelle Umgebung zu analysieren, geeignete Alternativen zu bewerten und eine
Roadmap zu entwickeln."* TPG bietet eine *„kostenlose Sprechstunde"* unter dem Betreff
„POL Retirement Sprechstunde". Holert hat ein eigenes *„Project Online SOS Kit"*
geschnuert. Und mehrere Anbieter haben eigene Domains ausschliesslich fuer diesen
Uebergang registriert (`gantt2plan.com`, `projectmigration.io`,
`msprojectmigration.com`) — dasselbe Ueberangebots-Muster wie die fuenf
EUDR-Fachportale.

## 3. Was heute dafuer gezahlt wird

**Lizenzseite, offizielle deutsche Microsoft-Preisseite**
(`microsoft.com/de-de/microsoft-365/planner/microsoft-planner-plans-and-pricing`,
abgerufen 2026-08-28):

- Microsoft Planner: *„Enthalten in Microsoft 365"* — also 0,00 EUR
- Planner Plan 1 (die Premium-Funktionen, Nachfolger von Project for the web):
  *„8,70 € Benutzer/Monat, jährliche Abrechnung"*
- Planner und Project Plan 3: *„26,00 € Benutzer/Monat, jährliche Abrechnung"*

International liegen Project Plan 3 bei 30 USD und Project Plan 5 bei 55 USD je Nutzer
und Monat (`thedigitalprojectmanager.com/tools/microsoft-project-pricing/`, abgerufen
2026-08-28). Die Desktop-Dauerlizenzen kosten laut deutscher Microsoft-Seite
*„1.659,00 €"* (Project Professional 2024) bzw. *„929,00 €"* (Project Standard 2024).

**Projektseite.** Onplana rechnet fuer ein PMO mit 200 Nutzern und 100 aktiven
Projekten vor: Training 80.000 USD, Integrations-Nacharbeit 60.000 USD,
Migrationswerkzeuge 15.000 USD, Parallelbetrieb 24.000 USD, Bereinigung und Archivierung
5.000 USD, abzueglich 42.000 USD Lizenzersparnis ueber drei Jahre — **netto rund
142.000 USD**; Dauer *„6 to 10 weeks for a portfolio of 50 to 200 projects"*, bei ueber
500 Projekten *„3–4 months"*; Schulungsaufwand *„4–8 hours per active user"*
(`onplana.com/migration/project-online-complete-guide`, abgerufen 2026-08-28).
**Als Anbieterrechnung zu lesen** — Onplana verkauft die Zielplattform und hat ein
Interesse an hohen Vergleichszahlen. Die Groessenordnung deckt sich aber mit Advaiya
(*„6-12 Monate für komplexe Migrationen"*, externe Beratung empfohlen) und mit Holerts
Gegenpol fuer einfache Faelle (*„etwa drei Stunden"* Testumgebung, Migration *„oft
innerhalb weniger Tage"*, Festpreispaket „Smart Start").

Onplana selbst nennt als eigenen Preis *„per-seat pricing starts at $7/seat/month"* und
*„ENTERPRISE @ $29 vs $55/seat"*.

**Die Werkzeugpreise sind durchweg nicht oeffentlich.** FluentPro, Gantt2Plan und
projectmigration.io arbeiten alle mit „Request pricing" bzw. Telefonnummer. Das ist
selbst ein Befund: Wer den Preis nicht nennt, verkauft ein Projekt, kein Produkt.

## 4. Die heutige Notloesung

**Sie ist Microsoft-Bordmittel und kostet nichts ausser der Zeit der eigenen IT.**

Der Datenexport, den jeder Betroffene vor dem 30.09.2026 machen muss, laeuft ueber
*„native export tools"* fuer MPP-Dateien, *„PowerShell scripts for bulk exports"* und
optional Drittanbieterwerkzeuge (`advaiya.com/project-online-data-after-microsoft-shuts-it-down/`,
abgerufen 2026-08-28). Fuer Altprojekte lautet die Standardanleitung: als MPP
exportieren und in einer SharePoint-Dokumentbibliothek oder auf einem Fileshare
ablegen (Wellingtone, *„How to Archive Projects in Microsoft Project Online"*, abgerufen
2026-08-28).

**Die zweite Notloesung ist, gar nicht zu migrieren, sondern auszuweichen:** Project
Server Subscription Edition behaelt die gewohnte PWA-Oberflaeche und ist von der
Abschaltung ausdruecklich **nicht** betroffen. Fuer einen Betrieb mit eigener
Infrastruktur ist das der Weg mit dem geringsten fachlichen Bruch.

**Die dritte ist, den Verlust hinzunehmen.** Wie viele das tun, ist nicht ermittelbar.

Die Schwaeche der Notloesung ist bekannt und benannt: *„A pure file export usually
solves only half the problem, because structure and relationships are lost and the data
cannot be analyzed anywhere afterwards."* Genau diese Luecke besetzen aber bereits
Altus PPM und Projectum xPM, indem sie die Daten strukturiert in Dataverse uebernehmen
und mit Power BI auswertbar halten.

## 5. Was dagegen spricht

**(a) Das Zeitfenster ist geschlossen, und danach gibt es keins mehr.** 33 Tage bis zur
Abschaltung. Und anders als bei anderen Microsoft-Einstellungen folgt danach nichts:
*„There will be no grace period or read-only access after the retirement date"* —
keine 90 oder 180 Tage Nur-Lese-Zugriff, wie sie Microsoft sonst gelegentlich gewaehrt.
Die betroffene Universitaet Toronto formuliert es fuer ihre eigenen Nutzer so:
*„September 30, 2026: Service retirement. Access to Project Online data permanently
removed"*, mit der internen Frist *„Complete migration and decommission Project Online
before September 29, 2026"* (`easi.its.utoronto.ca/project-online-retiring-september-30-2026/`,
abgerufen 2026-08-28). **Ein Markt, der an einem Datum endet, das vor der ersten
Auslieferung liegt, ist kein Markt.** Das ist der Unterschied zu allen bisherigen
Abkuendigungssignalen: Bei SAP ByDesign fehlte die Frist ganz, hier ist sie da — und
schon vorbei.

**(b) Der Hersteller hat die Luecke selbst geschlossen, wieder.** Dasselbe Muster wie
bei ByDesign (Release 26.02, E-Rechnung) und Build Apps (`.mtar`-Konverter): Der
kostenlose Project/Planner Accelerator auf Power-Platform-Basis ist genau der
Migrationsweg, den Microsoft in der eigenen Q&A empfiehlt. Der Rest ist an zwei
Partner delegiert, die Microsoft namentlich nennt.

**(c) Der Kundenbestand laeuft ueber einen Partnerkanal, und der ist alarmiert.**
Jeder Bestandskunde von Project Online hat ein Systemhaus im Vertrag oder ist gross
genug, eines zu beauftragen. Fuenf deutschsprachige Haeuser, sechzehn insgesamt, haben
fertige Landingpages; zwei verschenken die Erstberatung. Wer heute noch nicht migriert
hat, hat entweder schon einen Partner oder wird in den verbleibenden Wochen von einem
der sechzehn eingesammelt.

**(d) Das Kundenprofil schliesst ein Nebengewerbe aus.** 48 % der Kunden haben mehr als
1.000 Beschaeftigte, die Branchenschwerpunkte sind Luft- und Raumfahrt, Verteidigung,
oeffentlicher Sektor und Banken, die deutschen Referenzen heissen Rohde & Schwarz, KUKA,
Miele und Stadtreinigung Hamburg. Das ist dieselbe Absage wie bei beaufsichtigten
Kunden: Einkauf, Lieferantenpruefung, Auslagerungsanforderungen — unabhaengig von der
Produktqualitaet.

**(e) Der Auftragsgegenstand ist Beratung, nicht Software.** Sechs bis zehn Wochen fuer
50-200 Projekte, vier bis acht Stunden Schulung je aktivem Nutzer, Change Management,
Integrations-Nacharbeit. Das Werkzeug ist der kleinste Posten der Rechnung
(15.000 von 142.000 USD nach Onplanas eigener Aufstellung, also gut 10 %). Ein Markt,
dessen Wertschoepfung in Schulung und Scope-Klaerung liegt, ist mit zwei Stunden pro
Woche unerreichbar.

**(f) Selbst die Restnische ist besetzt.** Die naheliegendste Kleinstidee — ein
guenstiges, lesbares Archiv der Project-Online-Daten fuer Kunden, denen eine
sechsstellige Migration zu teuer ist — wird von mindestens vier Seiten bedient: von
Microsofts eigenem MPP-Export plus PowerShell (kostenlos), von Wellingtones
kostenloser Archivierungsanleitung, von ShareGate fuer die SharePoint-Inhalte und von
Altus PPM und Projectum xPM, die die Daten strukturiert in Dataverse uebernehmen.

**(g) Das Segment ist nicht bezifferbar.** Drei Datenbanken, Faktor 66 Unterschied,
keine Laenderaufschluesselung, keine Herstellerzahl, keine Zahl in der
deutschsprachigen Fachpresse und keine im Signal. Nach meiner eigenen Regel ist das
Fehlen nach zehn Quellen der Befund, nicht die Suchluecke.

## Offen geblieben

- **Die Zahl der betroffenen Organisationen in Deutschland.** Nicht ermittelt und mit
  den verfuegbaren Mitteln vermutlich nicht ermittelbar. Der Ideator darf keine der drei
  kursierenden Weltzahlen (629 / 1.370 / 41.359) als Marktgroesse verwenden; sie sind
  Adressbestaende von Leadgenerierern und widersprechen sich um Faktor 66.
- **Ob es nach dem 30.09.2026 doch eine informelle Nur-Lese-Phase gibt.** Eine Quelle
  erwaehnt ein moegliches *„informal ~90-day read-only window"* ohne vertragliche Zusage.
  Ich konnte das nicht verifizieren, weil der zugehoerige Diskussionsfaden im Microsoft
  Community Hub nicht abrufbar war. Selbst wenn es die Phase gaebe, aendert sie an der
  Bewertung nichts — sie waere nur Zeit zum Exportieren, nicht zum Verkaufen.
- **Die Preise saemtlicher Migrationswerkzeuge.** FluentPro, Gantt2Plan und
  projectmigration.io nennen keine; alle drei arbeiten mit Angebot auf Anfrage. Die
  angegebene Preisspanne betrifft deshalb nur die Lizenzseite, nicht die Werkzeugseite.
- **Der Microsoft-Originalbeitrag** (`techcommunity.microsoft.com/blog/plannerblog/microsoft-project-online-is-retiring-what-you-need-to-know/4450558`)
  liess sich auch in diesem Lauf nicht laden — WebFetch bekam nur den Seitentitel. Das
  Signal hatte dasselbe Problem. Alle Termine sind hier deshalb ueber Sekundaerquellen
  belegt, darunter mit der Universitaet Toronto und der offiziellen Microsoft-Q&A auf
  learn.microsoft.com zwei, die den Wortlaut zitieren bzw. selbst betroffen sind.
- **Wie viele Kunden am 2026-08-28 noch nicht migriert sind.** Keine Quelle nennt eine
  Restquote. Fuer die Bewertung ist das ohne Belang: Auch eine grosse Restmenge waere
  in 33 Tagen von keinem neuen Anbieter mehr erreichbar.
