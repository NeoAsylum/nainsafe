---
typ: recherche
signal: signals/market/2026-08-28-lexware-preiserhoehung-september-2026.md
erstellt: 2026-08-28
segmentgroesse: OnPremise nicht direkt ermittelbar; selbst gerechneter Korridor 250.000-300.000 Unternehmen (600.000+ Lexware-Kundenunternehmen abzueglich 300.000-350.000 Cloud-Nutzer, Einheiten gemischt); einzige belegte Teilzahl: "mehr als 4.500" bereits auf PostgreSQL migrierte pro-/premium-Kunden
anbieter_gefunden: 31 namentlich (1 Hersteller mit eigenem Ausweichprodukt, 17 Fachhaendler von rund 350, 6 Ersatzprodukte, 3 Migrationswege, 4+ Datenzugriffs-/Add-on-Haeuser mit zusammen ueber 30 bepreisten Werkzeugen)
preisspanne: 130,80-2.140,00 EUR/Jahr netto Listenpreis ab 01.09.2026; Drittanbieter-Werkzeuge 79-449 EUR einmalig, LX Connect 990-2.190 EUR/Jahr
ampel: gelb
---

# Lexware hebt zum 01.09.2026 die Listenpreise der OnPremise-Linien um 7,3 bis 12,8 Prozent an — das sind 2,50 bis 13,50 EUR netto im Monat, und dieselbe Erhoehung am selben Kalendertag gab es 2024 schon einmal, ohne messbare Reaktion

**Der Kern vorweg, weil er die Bewertung des Signals umdreht:** Das Signal meldet eine
Preiserhoehung ohne Zahl. Die Zahl ist ermittelbar, und sie ist klein. Die alten Preise
stehen am 2026-08-28 noch im Herstellershop, die neuen in der Fachhaendler-Liste; die
Differenz betraegt je nach Produkt **30,00 bis 162,00 EUR netto im Jahr**, im Monat
**2,50 bis 13,50 EUR**. Und der Vorgang ist kein Ereignis, sondern ein Turnus: Zum
**01.09.2024** — demselben Kalendertag, mit derselben Begruendung — gab es die
Vorgaengererhoehung. Die Preise von damals sind exakt die Preise, die der Hersteller
heute noch verlangt.

Damit ist die tragende Vermutung des Signals — eine Preiserhoehung erzeuge eine
wechselbereite Nutzergruppe — an einem realen Praezedenzfall pruefbar. Sie haelt nicht
stand (Abschnitt 4 und 5).

Zwei Behauptungen des Signals sind ausserdem zu korrigieren:

1. *„Eine Moeglichkeit, den bisherigen Vertragspreis dauerhaft zu sichern, gibt es nicht."*
   Richtig fuer den Listenpreis. Praktisch aber neutralisieren die Fachhaendler die
   Erhoehung vollstaendig — das Erfolgsbuero bietet **15 % im ersten Jahr und 5 %
   dauerhaft**, ibeq bot 2024 **10 %**. Beides ist mehr bzw. gleich viel wie die
   Erhoehung selbst.
2. *„Kein Drittanbieter positioniert sich bislang oeffentlich als Umsteige-Ziel."*
   Das trifft fuer die Preiserhoehung zu, fuer das Segment nicht: sevdesk bewirbt eine
   **kostenlose, automatisierte** Migration ueber den Partner SyncFast, desk4 wirbt
   woertlich mit „Datenmitnahme aus Lexware, Sage, Bueroplus, SAP etc.", und der
   Hersteller selbst haelt mit Lexware Office ein Produkt bereit, das **billiger** ist
   als jede Desktop-Linie.

Was das Signal dagegen nicht sieht und was in diesem Segment tatsaechlich passiert,
steht in Abschnitt 5 unter (f): der Datenbankwechsel von Sybase auf PostgreSQL.

## 1. Groesse des Segments

**Die Zahl der OnPremise-Kunden veroeffentlicht der Hersteller nicht. Es gibt einen
Korridor, aber er beruht auf einer Subtraktion zweier Zahlen mit unterschiedlichen
Einheiten und ist deshalb nur als Groessenordnung verwendbar.**

| Angabe | Quelle | Charakter |
|---|---|---|
| „600.000+ Unternehmen" Kunden der Marke Lexware, Umsatz „ca. 200 Mio. € (Geschaeftsjahr 2023)", „ca. 500" Mitarbeiter im Lexware-Bereich | `the-playbook.de/de/firmen/lexware/`, Seitenstand „Last Updated: Sun Mar 08 2026", abgerufen 2026-08-28 | Marktdatenbank, keine Primaerquelle genannt |
| „rund 300.000 aktiven Nutzern der Cloud-Plattform" | dieselbe Quelle | dito |
| Lexware Office: „ueber 350.000 Unternehmen" (2025) | `de.wikipedia.org/wiki/Lexware`, abgerufen 2026-08-28 | Enzyklopaedie |
| „Ueber eine Million Nutzer setzen die Business- und Cloudloesungen [...] ein"; Umsatz 297 Mio. EUR (2022/23); 350 Partnerstandorte | dieselbe Quelle | Herstellerangabe, uebernommen |
| „ueber eine Million" Kunden | `sgb-it.de/wp/lexware-zahlen-und-fakten/`, abgerufen 2026-08-28 | Fachhaendlerseite, ohne Stichtag |

**Selbst gerechneter Korridor, Rechnung offengelegt:** 600.000 Kundenunternehmen minus
300.000 bis 350.000 Cloud → **250.000 bis 300.000 OnPremise-Unternehmen**. Die
Einschraenkung ist hart und darf nicht wegfallen: der Minuend zaehlt *Unternehmen*, der
Subtrahend in einer der beiden Quellen *aktive Nutzer*. Nach meiner eigenen Regel aus
dem Reinigungslauf ersetzt eine Nachbargroesse die fehlende Zahl nur, wenn sie dieselbe
Einheit zaehlt — hier tut sie es nicht durchgaengig. Der Korridor taugt fuer die
Aussage „sechsstellig", nicht fuer eine Kalkulation.

**Die einzige belegte Teilzahl, und sie stammt vom Hersteller selbst** (weitergegeben
ueber einen Gold-Partner): *„Bereits heute arbeiten mehr als 4.500 Kunden der pro- und
premium-Produktlinien erfolgreich mit der neuen Datenbank."*
(`sgb-it.de/wp/lexware-datenbank-migration-naechste-phase-startet-ab-juni-2026/`,
abgerufen 2026-08-28). Das ist der bereits migrierte Teil der beiden obersten Linien,
nicht deren Gesamtbestand — als **Untergrenze** fuer die pro-/premium-Kohorte
verwendbar, sonst nichts.

**Was es nicht gibt:** keine Aufschluesselung Desktop/Cloud vom Hersteller, keine Zahl
je Produktlinie, keine Zahl in der Fachpresse, keine im Signal. Auch der
Haufe-Group-Konzernumsatz (562 Mio. EUR im GJ 2024/25) hilft nicht, weil er die
Verlagsseite einschliesst.

**Verwertbar ist die Strukturaussage, und sie ist eindeutig:** *„Lexware verfolgt eine
Zwei-Saeulen-Strategie: klassische On-Premise-Desktop-Software fuer bestehende Kunden
einerseits, und eine moderne Cloud-/SaaS-Plattform fuer die wachsende Zielgruppe der
Selbststaendigen und Kleinstunternehmen andererseits."* (the-playbook.de, abgerufen
2026-08-28). Desktop ist ausdruecklich die Bestandssaeule, Cloud die Wachstumssaeule.

## 2. Wer es heute bedient

**Dicht besetzt, in fuenf Schichten. Ich habe deutsch und englisch gesucht, ueber
Preis-, Wechsel-, Migrations-, Alternativen- und Datenzugriffsformulierungen; jede
Suche brachte neue Namen, keine brachte eine Luecke.**

**Schicht 1 — Der Hersteller, mit einem billigeren eigenen Ausweichprodukt.**
`lexware.de/buchhaltungssoftware/` zeigt am 2026-08-28 **ausschliesslich Lexware Office**
(Cloud) zu 7,90 / 12,90 / 21,90 / 32,90 EUR netto im Monat; `shop.lexware.de/buchhaltungssoftware`
leitet per 301 genau dorthin um. Die Desktop-Preise stehen nur noch auf den
Einzelproduktseiten des Shops. Wer wegen 2,50 EUR im Monat unzufrieden ist, findet beim
selben Anbieter ein Produkt fuer 7,90 EUR — die Abwanderung faengt der Hersteller selbst
auf. Dazu die eigene Importseite `lexware.de/funktionen/datenimport/` („Mit wenigen
Klicks", CSV-Vorlage, ueber 150 Partner-Apps) und ein Partnerverzeichnis
`lexware.de/partner/` mit **ueber 150 Erweiterungen** in elf Kategorien (alle abgerufen
2026-08-28).

**Schicht 2 — Der Fachhandel, und er ist die eigentliche Antwort auf dieses Signal.**
Wikipedia nennt **350 Partnerstandorte** in Deutschland (abgerufen 2026-08-28).
Namentlich mit eigener Seite zu genau diesem Stichtag oder zum Vorgaengerstichtag 2024:
**LexSHOP** (lexshop.org, fuehrt die vollstaendige neue Preisliste), **lex-blog.de /
TAS LEX-Partner.Net**, **25help**, **Erfolgsbuero Dilly**, **SGB-IT** (Gold Partner),
**ibeq**, **Lutz Consulting**, **sysolution**, **CMO.de**, **Netmicro**, **Lern-Ware**,
**BOME.net**, **lexpro.de**, **Main-Business**, **shop-lexhandel**, **Helmrich**,
**enespa** (alle abgerufen 2026-08-28).

Zwei Saettigungsindikatoren aus meinem Logbuch treffen hier in der schaerfsten Form:
Die Haendler **verschenken die Beratung und unterbieten den Listenpreis**. Erfolgsbuero
Dilly: *„15% Rabatt im ersten Jahr"*, *„5% dauerhafter Rabatt"*, *„Kostenlose Umstellung
der Abrechnung"* (`erfolgsbuero.de/lexware-preiserhoehungen/`). ibeq zur Erhoehung 2024:
*„10% Rabatt beim ibeq Fachhandel – sowohl fuer Bestands- als auch fuer Neukunden"*
(`ibeq.com/lexware-preisanpassung-zum-01-09-2024/`). 25help empfiehlt, *„vor dem Stichtag
zu pruefen, welche Lizenzen und Module sie tatsaechlich benoetigen, und bei Bedarf ein
Down- oder Upgrade beim Fachhandel oder direkt bei Lexware anzufragen"*. Alle drei
abgerufen 2026-08-28.

**Schicht 3 — Ersatzprodukte (6 namentlich).** sevdesk, Lexware Office (Konzernschwester),
Buchhaltungsbutler, FastBill, Lido (mit DATEV), desk4. Genannt in mehreren
konkurrierenden „Lexware-Alternative"-Vergleichen des Jahres 2026 (lido.app,
softwareabc24.de, topalternative24.com, vorlage-kostenlos.de, taxandbytes.de), alle
abgerufen 2026-08-28 — nach meinem Logbuch Saettigungsindikator (9)/(11): mehrere
konkurrierende Vergleiche desselben Jahres, meist vom Wettbewerber selbst geschrieben.

**Schicht 4 — Migrationswege (3).** **SyncFast** (Betreiber laut Impressum zrapp.group)
migriert automatisiert zwischen deutschen Buchhaltungsprogrammen; sevdesk bewirbt das
als *„komplett kostenlos"*, inklusive *„3 Monate kostenlos testen PLUS 50 % Rabatt auf
die erste Laufzeit"* (`sevdesk.de/lexware-office-alternative/`, `syncfast.de`, abgerufen
2026-08-28). **desk4** wirbt mit *„Lexware, Sage, Bueroplus, SAP, COS und jedes andere
Warenwirtschaftssystem"* und *„kostenloses Erstgespraech"*
(`desk4.de/informationen/datenmitnahme/`). **erechnung-tool.de** hat eine fertige
Landingpage fuer die eingestellte buero-easy-Reihe mit *„Festpreis nach kostenlosem
Analyse-Gespraech"*.

**Schicht 5 — Datenzugriff und Zusatzwerkzeuge, und das ist die Schicht, in der dieses
Segment tatsaechlich Geld ausgibt.** Ein ganzes Handwerk lebt von Add-ons fuer die
Lexware-Desktop-Produkte:

- **LX Connect** (Co-Orga GmbH, `lxconnect.de`, abgerufen 2026-08-28) — Data Warehouse
  und Web-API fuer Lexware Pro & Premium, ausdruecklich als Antwort auf die
  PostgreSQL-Umstellung: *„Mit PostgreSQL endet der direkte Zugriff auf die
  Lexware-Datenbank."* Verfuegbarkeit „Herbst 2026", 14 Tage Test.
- **LX Data Warehouse** (ueber LexSHOP; Produktseite lieferte am 2026-08-28 HTTP 410)
- **Explorer/LX und ODBC/LX**, **DBB/LX**, **Report/LX**, **FormDesigner/LX**,
  **Phone/LX** (ibeq, `ibeq.com`)
- **LxTools** (CMO.de), Toolreihen von **lex-blog.de**, **BOME.net**, **lexpro.de**,
  **Main-Business**, **Lutz Consulting**
- ein quelloffenes Projekt: `github.com/FubarDevelopment/Lexware` („Datenbank-Zugriff
  fuer Lexware")

Allein die Kategorie `lexshop.org/produkt-kategorie/lexware-tools/` fuehrt **24 bepreiste
Produkte auf der ersten Seite** (abgerufen 2026-08-28), mit Paginierung.

## 3. Was heute dafuer gezahlt wird

**Der Vergleich alt/neu, aus zwei unabhaengigen Quellen belegt.** Die Spalte „bisher"
stammt aus dem Herstellershop `shop.lexware.de` (abgerufen 2026-08-28, also vier Tage
vor dem Stichtag) **und** deckt sich Cent-genau mit der Preisliste ab 01.09.2024
(`lex-blog.de/2024/07/09/neue-lexware-preise-09-2024/`, abgerufen 2026-08-28). Die
Spalte „ab 01.09.2026" stammt aus der Fachhaendlerliste `lexshop.org/preiserhoehung/`
(abgerufen 2026-08-28). Alle Angaben netto.

| Produkt | bisher EUR/Jahr | ab 01.09.2026 | Δ EUR/Jahr | Δ % | Δ EUR/Monat |
|---|---|---|---|---|---|
| buchhaltung (basis) | 262,80 | 292,80 | +30,00 | +11,4 | +2,50 |
| buchhaltung plus | 334,80 | 364,80 | +30,00 | +9,0 | +2,50 |
| buchhaltung pro | 694,80 | 760,80 | +66,00 | +9,5 | +5,50 |
| buchhaltung premium | 838,80 | 934,80 | +96,00 | +11,4 | +8,00 |
| warenwirtschaft pro | 658,80 | 742,80 | +84,00 | +12,8 | +7,00 |
| warenwirtschaft premium | 838,80 | 934,80 | +96,00 | +11,4 | +8,00 |
| lohn+gehalt (basis) | 346,80 | 382,80 | +36,00 | +10,4 | +3,00 |
| lohn+gehalt plus | 478,80 | 514,80 | +36,00 | +7,5 | +3,00 |
| lohn+gehalt pro | 826,80 | 886,80 | +60,00 | +7,3 | +5,00 |
| lohn+gehalt premium | 1.042,80 | 1.144,80 | +102,00 | +9,8 | +8,50 |
| financial office (basis) | 478,80 | 526,80 | +48,00 | +10,0 | +4,00 |
| financial office plus | 658,80 | 724,80 | +66,00 | +10,0 | +5,50 |
| financial office pro | 1.078,80 | 1.186,80 | +108,00 | +10,0 | +9,00 |
| financial office premium | 1.438,80 | 1.600,80 | +162,00 | +11,3 | +13,50 |

**Spanne der Erhoehung: +7,3 % bis +12,8 %, in Geld 30,00 bis 162,00 EUR netto im Jahr.**

**Die Listenpreise insgesamt ab 01.09.2026** reichen von 130,80 EUR/Jahr (kassenbuch,
bueroeasy start) bis 2.140,00 EUR/Jahr (neue Steuerkanzlei); die Beraterversionen liegen
bei 874,80 bzw. 1.486,80 EUR (lexshop.org, abgerufen 2026-08-28).

**Zum Vergleich das Ausweichprodukt desselben Herstellers:** Lexware Office kostet
7,90 / 12,90 / 21,90 / 32,90 EUR netto im Monat, also **94,80 bis 394,80 EUR im Jahr**
(`lexware.de/buchhaltungssoftware/`, abgerufen 2026-08-28). Der Wettbewerber sevdesk:
Rechnung 9,90, Buchhaltung 22,90, Buchhaltung Pro 30,90 EUR/Monat bei Jahreszahlung
(`sevdesk.de/lexware-office-alternative/`, abgerufen 2026-08-28).

**Und die eigentlich interessante Zahlungsbereitschaft, weil sie bereits an Dritte
fliesst:** Fuer Zusatzwerkzeuge zu genau diesen Desktop-Produkten zahlt dieses Segment
oeffentlich bepreiste Betraege.

- Einmalpreise im LexSHOP (abgerufen 2026-08-28): LXArchiv 79,00 · BackupLX Pro
  89,00–149,00 · File2Lex 118,80 · MahnExpressLX / KundenUmsatzLX / LagerbewertungLX /
  PreisanpassungLX je 129,00–259,00 · Woo2LX 139,00 · AnschriftManagerLX 159,00 ·
  KStKTr-Auswertung LX 159,00–299,00 · Explorer/LX & ODBC/LX bis 245,00 ·
  InventurLX 249,00–429,00 · EingangsbelegsNr LX 299,00 · Stuecklisten-Bundle
  299,00–449,00.
- **Abo-Preise: LX Connect 99 EUR/Monat (990 EUR/Jahr) fuer das Data Warehouse,
  159 EUR/Monat (1.590 EUR/Jahr) fuer die API, 219 EUR/Monat (2.190 EUR/Jahr) fuer
  „Komplett", je Lexware-Installation** (`lxconnect.de/preise`, abgerufen 2026-08-28).

Das ist die belastbarste Zahl dieses Laufs: **Ein Drittanbieter verlangt fuer den
blossen Datenzugang zu Lexware mehr, als Lexware fuer die Software selbst nimmt** — und
er baut das Produkt gerade.

## 4. Die heutige Notloesung

**Sie heisst: zahlen. Und der Praezedenzfall zeigt, dass sie funktioniert.**

Zum **01.09.2024** hob Lexware die Preise am selben Kalendertag, mit derselben
Begruendung (*„gestiegene Kosten in den Bereichen Personal, Hosting, Zahlungsabwicklung
und Kundenservice"*) und in derselben Groessenordnung an. Die damals eingefuehrten
Preise sind exakt die Preise, die der Hersteller am 2026-08-28 noch verlangt. Es ist
ein Zweijahresturnus, kein Bruch.

**Der billigste Nachfragetest, den es gibt, faellt in beiden Jahren gleich aus.** Der
Thread zur Erhoehung 2026 auf lex-forum.net, der zentralen deutschsprachigen
Lexware-Community, wurde am **08.07.2026 um 17:47** eroeffnet und hat **eine Antwort und
keinen einzigen inhaltlichen Nutzerkommentar**. Der Thread zur Erhoehung 2024, eroeffnet
am **09.07.2024 um 14:40**, hat ebenfalls **eine Reaktion und keinen Kommentar**; ein
Wechsel zu einem anderen Anbieter wird in keinem der beiden erwogen
(`lex-forum.net/t/lexware-preise-neue-konditionen-ab-01-09-2026/22327` und
`.../15504`, beide abgerufen 2026-08-28). Zwei identische Ereignisse im Abstand von zwei
Jahren, null Aufschrei.

**Die zweite Notloesung kostet nichts und ist besser als die Erhoehung:** den
Fachhaendler wechseln. 15 % im ersten Jahr und 5 % dauerhaft (Erfolgsbuero) bzw. 10 %
(ibeq) uebertreffen die Erhoehung von 7,3–12,8 % ganz oder weitgehend. Der Kunde zahlt
danach **weniger als vorher** — ohne Datenmigration, ohne Schulung, ohne Risiko.

**Die dritte ist ein Downgrade** innerhalb derselben Produktfamilie, wofuer es
Anleitungen des Fachhandels gibt (Lern-Ware fuehrt ein eigenes PDF „Downgrade von
Lexware financial office auf ein Einzelprogramm"). 25help empfiehlt genau das.

**Was ausdruecklich keine Notloesung ist: einfach nicht verlaengern.** Wer das
Abonnement nicht verlaengert oder nicht zahlt, verliert Funktionen — Lern-Ware
beschreibt die Funktionssperren, die *„zum 31.03.2026 aktiv"* werden, fuer Financial
Office Standard/Plus/Pro/Premium, Business Plus und Bueroservice komplett
(`lex.lern-ware.de/a-funktionssperren-bei-lexware-software-2025-ab-31-maerz-2026/`,
abgerufen 2026-08-28). Die Nutzung der Version 2026 ist ausserdem laengstens bis zum
31.01.2027 moeglich. Das Abo ist faktisch alternativlos — was den Zwang zum Zahlen
erhoeht, nicht den Zwang zum Wechseln.

**Der Aufwand der Alternative kennt nur eine belegte Zahl, und sie ist gross:** Eine
Migration von Lexware Desktop in die Cloud wird mit *„5–10 Werktagen"* fuer
Datenuebernahme, Schnittstellenanpassung und Schulung angesetzt (Suchtreffer-Zusammenfassung,
Quellseite nicht gegengeprueft — nur als Groessenordnung zu lesen). Gegen 30 EUR
Mehrkosten im Jahr steht damit ein Projekt von mehreren Personentagen. Die Rechnung geht
fuer niemanden auf.

## 5. Was dagegen spricht

**(a) Die Erhoehung ist zu klein, um irgendetwas auszuloesen.** 2,50 bis 13,50 EUR netto
im Monat, im Median rund 5 EUR. Nach meiner Logbuchregel aus dem Office-2021-Lauf ist ein
Stichtag, an dem fuer den Anwender nichts Sichtbares passiert, schwaecher als gar keine
Frist. Hier passiert etwas Sichtbares — eine Rechnung steigt um den Preis von zwei
Kaffees. Das ist keine Kaufentscheidung, das ist eine Buchung.

**(b) Es ist derselbe Vorgang wie 2024, und 2024 ist nichts passiert.** Gleicher
Kalendertag, gleiche Begruendung, gleiche Groessenordnung, gleiche Fachhandelsreaktion,
gleiche Nullreaktion der Community. Nach meiner eigenen Regel („Gab es dasselbe Ereignis
schon einmal — und was ist damals passiert?") ist das die belastbarste Antwort auf
Frage 4, die ein Ausstiegs- oder Preissignal ueberhaupt bekommen kann.

**(c) Der Kanal ist besetzt und alarmiert — und er unterbietet die Erhoehung.** Rund 350
Fachhaendler, siebzehn davon namentlich mit einer Seite zu genau diesem Stichtag. Zwei
von ihnen dokumentieren Rabatte, die groesser sind als die Preiserhoehung selbst. Jeder
Lexware-OnPremise-Kunde ist entweder bereits bei einem Haendler oder wird in den
verbleibenden Wochen von einem eingesammelt. Ein Nebengewerbe hat gegen einen
Vertriebskanal aus 350 Haeusern, die die Beratung verschenken, kein Argument.

**(d) Der Hersteller faengt die Abwanderung selbst auf, und zwar nach unten.** Lexware
Office kostet 94,80 bis 394,80 EUR im Jahr, die Desktop-Linien 130,80 bis 2.140,00 EUR.
Die Produktseite `lexware.de/buchhaltungssoftware/` zeigt am 2026-08-28 nur noch die
Cloud, die Shop-URL leitet dorthin um, und der eigene Datenimport wirbt mit *„mit wenigen
Klicks"*. Wer die Erhoehung nicht will, wechselt zum billigeren Produkt **desselben
Konzerns**. Dasselbe Muster wie bei SAP ByDesign (Release 26.02) und SAP Build Apps
(`.mtar`-Konverter): Der Hersteller schliesst die Luecke, bevor ein Dritter sie sieht.

**(e) Die naheliegendste Restnische — den Wechsel weg von Lexware zu erleichtern — ist
bereits kostenlos.** sevdesk laesst die Migration ueber SyncFast *„komplett kostenlos"*
laufen und legt drei Gratismonate plus 50 % Rabatt obendrauf; desk4 nennt Lexware
namentlich als Quellsystem und verschenkt das Erstgespraech. Nach meinem Logbuch ist
das Saettigungsindikator (7): ein Wettbewerber mit dauerhaft kostenloser Stufe setzt den
Preisboden nicht niedrig, sondern auf null.

**(f) Und der wichtigste Punkt, weil er das Signal nicht widerlegt, sondern ersetzt:
Im selben Segment laeuft gleichzeitig ein Ereignis mit echtem Zwang — und es ist bereits
besetzt.** Mit Version 2026 tauscht Lexware die 32-Bit-Sybase-Datenbank gegen ein
64-Bit-PostgreSQL; Bestandskunden werden ab Mitte Juni 2026 schrittweise migriert,
*„mehr als 4.500 Kunden der pro- und premium-Produktlinien"* sind schon umgestellt, eine
verpflichtende Umstellung ist angekuendigt (sgb-it.de, abgerufen 2026-08-28). Dabei
enden die bisherigen direkten Datenbankzugriffe — genau das, worauf die
Add-on-Industrie aus Abschnitt 2, Schicht 5, aufgebaut ist. Fachhaendler warnen
ausdruecklich, dass Zusatzprogramme und eigene Schnittstellen *„nach der Migration
moeglicherweise nicht mehr wie erwartet funktionieren"*. **Die Co-Orga GmbH hat darauf
mit LX Connect bereits ein Produkt gebaut** (990–2.190 EUR/Jahr netto, Verfuegbarkeit
Herbst 2026), Explorer/LX und ODBC/LX bedienen dieselbe Aufgabe seit Jahren, und ein
quelloffenes Projekt liegt auf GitHub. Wer aus diesem Signal eine Idee baut, sollte
wissen: Der Schmerz liegt nicht beim Preis, sondern bei der Datenbank — und dort ist
mindestens ein Anbieter im deutschsprachigen Markt schon vor der Tuer.

**(g) Kein Gegenargument, sondern eine Korrektur zugunsten des Signals, damit sie nicht
verlorengeht:** Die Desktop-AGB des Herstellers geben ein Kuendigungsrecht **ohne
Prozentschwelle**. Ziffer I. 4.6: *„Wir sind berechtigt, den Preis einmal pro
Kalenderjahr in unserem billigen Ermessen zu aendern, um die Auswirkungen von
Aenderungen der mit unserem Dienst verbundenen Gesamtkosten widerzuspiegeln"*, mit
mindestens 30 Tagen Ankuendigung; der Kunde kann *„ohne Kuendigungsfrist und kostenlos
fruehestens zum Zeitpunkt der Preiserhoehung"* kuendigen, Frist drei Monate ab Zugang der
Aenderungsmitteilung (`agb.lexware.de/lexware-desktop`, abgerufen 2026-08-28). Der
Mindestvertrag laeuft sonst 12 Monate mit automatischer Verlaengerung um 12 Monate. Es
gibt also ein reales, datiertes Wechselfenster fuer den gesamten Bestand — nur eben
keinen Grund, es zu nutzen. **Das ist die Kernaussage dieses Laufs: das Fenster ist da,
das Motiv fehlt.**

## Offen geblieben

- **Die Zahl der OnPremise-Kunden.** Nicht ermittelt und mit den verfuegbaren Mitteln
  vermutlich nicht ermittelbar. Der Ideator darf den Korridor 250.000–300.000 nur als
  Groessenordnung verwenden, nicht als Rechengrundlage — er entsteht aus einer
  Subtraktion mit gemischten Einheiten (Unternehmen minus aktive Nutzer). Die einzige
  belegte Teilzahl ist „mehr als 4.500" bereits migrierte pro-/premium-Kunden, und das
  ist eine Untergrenze fuer eine Teilmenge.
- **Ob Lexware Office (Cloud) von der Erhoehung zum 01.09.2026 betroffen ist.** Keine
  Quelle sagt es ausdruecklich in die eine oder andere Richtung. Alle drei
  Fachhaendlermeldungen nennen nur die OnPremise-Linien; die Cloud-Preisseite zeigt am
  2026-08-28 unveraendert 7,90/12,90/21,90/32,90 EUR. Die kursierende Angabe „12,90 auf
  32,90 EUR" betrifft eine **Paketumstellung wegen der E-Rechnung**, nicht diese
  Preisanpassung — sie darf nicht als Beleg fuer eine Cloud-Erhoehung verwendet werden.
- **Eine Primaerquelle bei Haufe-Lexware.** Wie schon im Signal: nicht auffindbar. Alle
  Belege zur Erhoehung selbst stammen von Fachhaendlern, die Lizenzberatung verkaufen.
  Gegengeprueft habe ich sie ueber den **Herstellershop** (alte Preise, `shop.lexware.de`,
  Einzelproduktseiten) und ueber die **Preisliste von 2024** — beide bestaetigen die
  Ausgangswerte Cent-genau, womit die Differenztabelle in Abschnitt 3 belastbar ist. Die
  neuen Preise selbst beruhen weiterhin allein auf der Haendlerliste; ab dem 01.09.2026
  waeren sie im Herstellershop gegenpruefbar.
- **Die Prozentangabe der Erhoehung nennt keine der drei Fachhaendlerquellen.** Die
  Werte in Abschnitt 3 sind von mir aus alter und neuer Liste gerechnet, die Rechnung
  ist offengelegt.
- **Was die PostgreSQL-Umstellung die Kunden konkret kostet.** Lern-Ware beschreibt den
  Vorgang als *„simulierten Rechnerwechsel"* und nennt Supportsaetze (1,25 EUR netto je
  Telefonminute, 5,00 EUR netto je Kernanfrage per Mail), aber keine Stunden und keinen
  Projektpreis. Kein Fachhaendler nennt einen Festpreis fuer die Umstellung. Das waere
  die naechste Frage, wenn jemand die Faehrte aus Abschnitt 5 (f) aufnimmt.
- **Wie viele Bestandskunden bei der Erhoehung 2024 tatsaechlich gekuendigt haben.**
  Keine Quelle nennt eine Quote. Fuer die Bewertung ohne Belang: Der Preis von 2024 ist
  bis heute der Listenpreis, die Community hat in beiden Jahren nicht reagiert, und
  Lexware wiederholt den Vorgang unveraendert — was fuer sich genommen dagegen spricht,
  dass er 2024 teuer war.
- **`lexware-hausverwaltung.de` und `eservice.lexware.de` waren am 2026-08-28 nicht
  erreichbar** (DNS-Fehler bzw. abgelaufenes Zertifikat bei `lexware-warenwirtschaft.de`).
  Die verbreitete Angabe, ein Sonderkuendigungsrecht bestehe erst ab 10 % Erhoehung,
  stammt aus der AGB einer *anderen* Produktlinie und liess sich dort nicht im Wortlaut
  pruefen. Fuer die Desktop-Linien gilt der in Abschnitt 5 (g) zitierte Wortlaut **ohne**
  Schwelle.
