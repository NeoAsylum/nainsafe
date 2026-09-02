---
typ: recherche
signal: signals/market/2026-08-28-sap-build-apps-abkuendigung.md
erstellt: 2026-08-28
segmentgroesse: nicht ermittelbar (weder SAP noch Dritte veroeffentlichen eine Kunden- oder App-Zahl; als Groessenordnungsproxy nur DSAG-Investitionsreport 2026, n=198 DACH-Unternehmen)
anbieter_gefunden: 17 (davon SAP selbst mit einem eigenen Migrationswerkzeug)
preisspanne: 9,42 GBP je Nutzer und Monat (SAP UK, oeffentliche G-Cloud-14-Preisliste); Neuaufbau ueber Freelancer 720-1.400 EUR je Tag
ampel: rot
---

# SAP kuendigt Build Apps zum 23.03.2026 als eigenstaendiges Produkt ab; Bestandskunden laufen bis Vertragsende weiter, und SAP hat inzwischen selbst ein Migrationswerkzeug nachgeliefert

**Der Kern dieses Laufs steht vorweg, weil er die Belegstelle des Signals ueberholt:**
Das Signal stuetzt sich darauf, dass es „keinen direkten Migrationspfad" gebe und Oberflaechen
„manuell in andere UI-Technologien ueberfuehrt" werden muessten. Das war zum Zeitpunkt der
Abkuendigung richtig und ist es nicht mehr. SAP hat ein Werkzeug veroeffentlicht, das
`.mtar`-Archive von Build-Apps-Frontends in SAPUI5- oder React-Projekte konvertiert; angefordert
wird es ueber ein Support-Ticket der Komponente **CA-LCA-ACP**. Genau die Luecke, die ein
Dritter haette fuellen koennen, hat der Hersteller selbst geschlossen — dasselbe Muster wie
beim ByDesign-Lauf (Release 26.02, E-Rechnung).

## 1. Groesse des Segments

**Nicht ermittelbar, und diesmal gibt es nicht einmal widerspruechliche Schaetzungen.**

Bei SAP Business ByDesign kursierten wenigstens drei einander widersprechende Weltzahlen. Zu
SAP Build Apps nennt **keine** der ausgewerteten Quellen eine Kunden-, Nutzer- oder App-Zahl —
weder SAP noch die sechs Beratungshaeuser, die zur Abkuendigung publiziert haben (Mission Mobile,
ORBIS, Rewion, Simplifier, On Device Solutions, itsfullofstars; alle abgerufen 2026-08-28). Auch
die Herkunftsseite AppGyver gibt nichts her: Die SAP-Pressemitteilung zur Uebernahme 2021 nennt
nur „18 employees" und keinen Nutzerbestand (automation.com bzw. news.sap.com/africa,
`news.sap.com/africa/2021/02/sap-acquires-no-code-development-pioneer-appgyver/`, abgerufen
2026-08-28).

**Der einzige qualifizierte Hinweis auf die Groesse ist ein Negativbefund, und er ist deutlich.**
Tobias Hofmann, langjaehriger SAP-Blogger, schreibt am Tag der Abkuendigung: *„I don't know anyone
who went all-in on SAP Build Apps"*, er sei ihm *„only for POCs or high-level evaluations — never
for a real-world app"* begegnet, und fragt offen, ob der Kundenbestand so klein sei, dass *„only
a handful of people are affected"* (itsfullofstars.de, `itsfullofstars.de/2026/03/rip-appgyver/`,
abgerufen 2026-08-28). Dieselbe Beobachtung, nur hoeflicher formuliert, steht bei ORBIS und
Mission Mobile: Build Apps sei „fuer einfache, klar umrissene Anwendungsszenarien" geeignet
gewesen, waehrend Teams fuer alles Anspruchsvollere ohnehin bei den etablierten SAP-Technologien
geblieben seien (abgerufen 2026-08-28).

**Verschaerfend: ein Teil des Bestands hat nie gezahlt.** Es gab durchgehend eine kostenlose
Stufe — erst die AppGyver Community Edition, ab Juni 2024 als „SAP Build Apps free edition"
weitergefuehrt (SAP Community, `community.sap.com/t5/application-development-and-automation-blog-posts/sap-build-apps-commercial-update-amp-free-edition/ba-p/13738928`,
ueber Suchtreffer, Seite selbst nicht abrufbar; abgerufen 2026-08-28). Der britische
G-Cloud-Eintrag von SAP fuehrt den kostenlosen Zugang ausdruecklich als „Free trial: Yes — For
development only". Wer eine Zahl „Build-Apps-Nutzer" faende, duerfte sie also nicht mit
„Build-Apps-Kunden" gleichsetzen.

**Als Obergrenzenproxy verwendbar, mehr nicht** (DSAG-Investitionsreport 2026, Erhebung
08.12.2025 bis 21.01.2026, **198 befragte Personen**, je eine je Mitgliedsunternehmen, nur CIOs
und IT-Leitungen; `impulsant.dsag.de/formate/pressemeldung/dsag-investitionsreport-2026-unternehmen-investieren-gezielter-ki-etabliert-sich-cloud-auf-dem-prufstand/`,
abgerufen und auf der Quellseite gegengeprueft 2026-08-28):

| Angabe | 2026 | 2024 |
|---|---|---|
| Hohe/mittlere Investitionen in SAP BTP | 39 % | 33 % |
| davon Bereich Anwendungsentwicklung und Automatisierung | 27 % | 17 % |

Das sind Investitionsabsichten zur **gesamten** BTP, nicht zu Build Apps. Verwertbar ist daran
vor allem die Groessenstruktur der Stichprobe: **40 % der befragten Unternehmen haben 500 bis
2.499 Beschaeftigte, 28 % mehr als 5.000.** Das ist die Kundenschicht, um die es hier geht.

Als schwacher Aktivitaetsindikator, ausdruecklich keine Kundenzahl: SAP Build hat auf G2
**98 Bewertungen** (4,3 von 5) und bei Gartner Peer Insights **39 Bewertungen** (4,5), beides
fuer das gesamte Build-Portfolio, nicht fuer Build Apps allein (abgerufen 2026-08-28).

## 2. Wer es heute bedient

**Zuerst und wichtigster: SAP selbst.** Nach der Abkuendigung hat SAP im eigenen Community-Blog
ein Migrationswerkzeug veroeffentlicht („Migration tool for your SAP Build Apps frontend web
applications", `community.sap.com/t5/technology-blog-posts-by-sap/migration-tool-for-your-sap-build-apps-frontend-web-applications/ba-p/14368805`).
Beschreibung woertlich aus den Suchtreffern und aus On Device Solutions (beide abgerufen
2026-08-28):

- Eingabe: das exportierte, proprietaere `.mtar`-Archiv der Anwendung.
- Verarbeitung: *„SAP processes the provided .mtar archives using SAP internal tooling, which
  securely reads proprietary SAP Build Apps configurations and generates best-effort transformed
  output in either SAPUI5 or React format."* SAP nennt ausdruecklich *„AI-assisted tooling"*.
- Anforderung: ueber ein Support-Ticket der Komponente **CA-LCA-ACP**.
- Erklaerter Zweck: bisher habe Migration bedeutet, *„essentially rebuilding your entire
  application from scratch"* — genau das solle entfallen.

Fuer natives Mobile lautet die Empfehlung „Rebuild in SAP Build SKU – MDK", fuer die
Backend-Daten der Visual Cloud Functions bleibt es beim CSV-Export und -Import.

**Beratungshaeuser mit veroeffentlichtem Angebot zur Abkuendigung** (alle abgerufen 2026-08-28):
Mission Mobile (`mission-mobile.de/app-entwicklung/sap-build-apps-abgekuendigt/`, bewirbt eine
„App Factory" mit Festpreis-App-Entwicklung, dazu Webinare und E-Books), ORBIS Group
(`orbis-group.com/de-de/blog/prozesse/prozessuebergreifend/abkuendigung-sap-build-apps/`,
Beitrag vom 29.04.2026, vier Leistungsbausteine: technisches Assessment, Zielarchitektur,
Migrationskonzept, Enablement), Rewion (`rewion.com/was-die-abkuendigung-von-sap-build-apps-fuer-sie-bedeutet/`,
Portfolio-Inventarisierung, Zielarchitektur, Pilotmigrationen), On Device Solutions
(`ondevicesolutions.com/sap-build-apps-deprecation/`), LeverX, Axxis Consulting, Amista, ososoft,
Claranet (`claranet.com/de/sap-services/sap-fiori`, „Consulting in a Box" mit Festpreisen),
Inwerken AG, ROOS IT, GAMBIT Consulting, tycom, Sotatek, sowie das Publikationsnetz
rz10/erlebe-software/mind-forms/compamind, das die Abkuendigung in seinem Newsletter „Perspektive
SAP IT — Maerz 2026" aufgegriffen hat.

**Anbieter, die auf Abwerbung umgestellt haben:** Simplifier AG mit einer eigenen
Migrations-Landingpage („SAP Build Apps wird eingestellt: Warum jetzt der richtige Zeitpunkt fuer
die Migration ist", deutsch und englisch — *„Bestehende Apps koennen strukturiert auf Simplifier
migriert werden"*), Neptune Software (`neptune-software.com`, wirbt mit „alternative to SAP Build
… lower TCO", laeuft im SAP-System ohne BTP), Mendix.

**Und der Markt darum herum ist ein Vergleichsmarkt.** Mission Mobile fuehrt „Die Top 20
Low-Code-Plattformen 2026 im Vergleich" mit zwanzig namentlich gelisteten Plattformen
(Simplifier, Neptune, SAP Build Apps, Power Apps, Mendix, OutSystems, Appian, ServiceNow, Visual
LANSA, Creatio, Kintone, Newgen, Oracle APEX, Pega, Quickbase, Betty Blocks, AppSheet, Zoho
Creator, Agile Point, Lightning App Builder; abgerufen 2026-08-28). Das ist
Saettigungsindikator (9) aus meinem Logbuch in Reinform: ein Thema mit fertigen
Anbietervergleichen hat keinen unbedienten Informationslayer.

**17 namentlich benannte Dienstleister und Plattformen in acht Suchlaeufen, deutsch und
englisch** — und die entscheidende Stelle, die automatisierbare Konvertierung, ist vom Hersteller
selbst besetzt.

## 3. Was heute dafuer gezahlt wird

**Belegt und auf der Quellseite gegengeprueft:** SAP (UK) Limited fuehrt SAP Build Apps im
britischen G-Cloud-14-Rahmenvertrag mit **9,42 GBP je Nutzer und Monat** („£9.42 to £9.42 a user
a month"), Free trial „For development only", Education pricing verfuegbar
(`applytosupply.digitalmarketplace.service.gov.uk/g-cloud/services/503685835927707`, abgerufen
2026-08-28). Das ist die einzige oeffentliche, herstellereigene Preisangabe, die ich finden
konnte.

*Nicht verwertbar, weil ungeprueft:* Das zugehoerige Preis-PDF desselben Rahmenvertrags soll
laut Suchzusammenfassung eine Staffel je App und Jahr enthalten (2.059,65 GBP bei 1-10 Apps bis
159,85 GBP bei 5.000 Apps). Das PDF war fuer mich nicht lesbar; nach meiner eigenen Regel
verwende ich die Zahlen nicht und fuehre sie hier nur, damit ein spaeterer Lauf sie nicht fuer
neu haelt.

**Der Zugang laeuft ohnehin nicht ueber diesen Einzelpreis, sondern ueber den BTP-Vertrag.**
Build Apps wird ueber Capacity Units in einem der drei BTP-Modelle bezogen — CPEA, BTPEA oder
Pay-as-you-go; „1 CU entspricht in der Regel 1 EUR" (cubeserv,
`cubeserv.com/de/blogserie-teil-2-lizenzierung-kosten-cpea-btpea-und-pay-as-you-go/`, abgerufen
2026-08-28). Abgerechnet werden „active users", definiert als Personen, die im Kalendermonat auf
Build Apps oder eine damit gebaute Anwendung zugreifen.

**Was der Wechsel kostet, ist ein Personen-, kein Lizenzpreis.** Fuer den Neuaufbau in
SAPUI5/Fiori nennt der deutsche Freelancer-Markt **rund 930 EUR je Tag** im Mittel, Spanne
**720 EUR** fuer Einsteiger bis **ueber 1.400 EUR** fuer Senior-Spezialisten in
Transformationsprojekten (sap-gehalt.de bzw. my-xperts.com, `sap-gehalt.de/ratgeber/sap-freelancer-tagessatz/`,
abgerufen 2026-08-28; als Marktueberblick gekennzeichnet, nicht als Einzelvertrag). Festpreise
fuer App-Entwicklung bewerben Mission Mobile und Claranet, veroeffentlichen aber keine Betraege.

## 4. Die heutige Notloesung

**Sie heisst „weiterlaufen lassen", und sie ist von SAP ausdruecklich gedeckt.** Uebereinstimmend
in allen Quellen (abgerufen 2026-08-28): Bestandskunden behalten *„full access to SAP Build Apps
for the duration of your current contract"*, unabhaengig davon, ob BTPEA, PAYG, CPEA oder
Subscription; *„SAP will honor all existing commitments, including SLAs and maintenance"*. **Ein
Wartungsende ist nicht angekuendigt.** Das ist derselbe Befund wie bei ByDesign und beantwortet
die erste Frage meiner Anbieter-Ausstiegs-Reihe: Abkuendigung als eigenstaendiges Produkt, aber
kein Enddatum, also keine Frist und kein Zwang.

**Danach, in dieser Reihenfolge:**

1. Konvertierung ueber das SAP-Werkzeug (Ticket CA-LCA-ACP), Ergebnis SAPUI5 oder React.
2. Nacharbeit im gewohnten Werkzeugkasten — SAP Business Application Studio, Build Code, CAP,
   Fiori Elements, ABAP Cloud.
3. Backend-Daten der Visual Cloud Functions per CSV-Export und -Import in ein CAP-Projekt. Was
   dabei **nicht** mitkommt, benennen Rewion und Mission Mobile sauber: „Beziehungen zwischen
   Entitaeten, Metadaten, Berechtigungsstrukturen".
4. Mobile Anwendungen: Neubau im Mobile Development Kit.

**Und die Nacharbeit schrumpft gerade von selbst.** In der SAP-Community steht seit Kurzem
„From SAP Build Apps to Pro-Code SAPUI5 Vibe Coded with UI5 MCP Server"
(`community.sap.com/t5/tooling-sap-build-blog-posts/.../ba-p/14370733`, ueber Suchtreffer,
abgerufen 2026-08-28) mit der Aussage, KI-Werkzeuge mit den passenden MCP-Servern koennten den
Aufwand eines UI-Neuaufbaus drastisch verdichten. Der teuerste verbliebene Handgriff wird also
gerade von zwei Seiten billiger: SAP automatisiert die Konvertierung, KI-Assistenz den Rest.

**Was die Notloesung kostet, traegt kein Externer neu ein.** Jeder Betroffene hat per Definition
einen BTP-Vertrag, SAP-Support und in aller Regel ein Systemhaus. Die Arbeit faellt dort an, wo
sie ohnehin verrechnet wird.

## 5. Was dagegen spricht

**Erstens: Die tragende Annahme des Signals gilt nicht mehr.** „Kein automatisierter
Migrationspfad" war der ganze Anlass. SAP hat nach der Abkuendigung ein Konvertierungswerkzeug
nachgeliefert, das genau diesen Schritt automatisiert, und liefert es ueber den Support-Kanal
aus. Was uebrig bleibt, ist nach ORBIS ausdruecklich die Entscheidung, *„ob eine Migration
sinnvoll oder ein kontrollierter Neuaufbau die bessere Option"* ist — eine Bewertung im
Einzelfall, also Beratung, nicht Software.

**Zweitens: Der proprietaere Teil ist strukturell nicht nachbaubar.** Das Eingabeformat ist ein
`.mtar`-Archiv mit *„proprietary SAP Build Apps configurations"*, das *„SAP internal tooling"*
liest. Selbst wenn niemand das Werkzeug gebaut haette, waere der Hersteller der einzige, der es
zuverlaessig bauen kann. Und er hat es getan.

**Drittens: Es gibt keine Frist.** Kein Wartungsende, voller Support und SLA bis Vertragsende,
und die Vertragsenden liegen individuell verstreut. Alle bisherigen roten Laeufe dieser Fabrik
starben am fehlenden Vollzug einer Pflicht; hier fehlt wieder die Pflicht selbst. Ein Anlass ohne
Stichtag erzeugt Beratungsgespraeche, keine Abos.

**Viertens: Die Zielgruppe ist ein IT-Beschaffungsapparat.** Wer Build Apps produktiv betreibt,
hat einen BTP-Rahmenvertrag (CPEA/BTPEA/PAYG), SAP-Support mit Komponentenzugriff und meist ein
Systemhaus. Die DSAG-Stichprobe zeigt die Groessenordnung: 40 % der befragten Unternehmen
500-2.499 Beschaeftigte, 28 % ueber 5.000. Dieselbe Absage wie beim KStTG- und beim
ByDesign-Lauf: wo der Kunde eine Beschaffungsabteilung hat, kauft er nicht beim Nebengewerbe.

**Fuenftens: Das Segment ist womoeglich winzig, und niemand kann das Gegenteil belegen.** Kein
Beteiligter — nicht SAP, nicht sechs Beratungshaeuser, nicht die Wettbewerber, die abwerben
wollen — nennt eine Zahl. Der einzige, der sich festlegt, sagt „handful". Dazu kam ueber Jahre
eine kostenlose Stufe, die POC- und Lernnutzung angezogen hat. Eine Ampel auf gruen zu setzen,
wuerde hier fuenf Angriffslaeufe auf eine Zielgruppe binden, deren Existenz unbelegt ist.

**Sechstens: Der Auftragsgegenstand ist ein Projekt.** Portfolio-Inventarisierung,
Zielarchitektur, Pilotmigration, Enablement — so beschreiben ORBIS und Rewion die Arbeit
uebereinstimmend. Bei 720 bis 1.400 EUR Tagessatz und mehreren Anwendungen je Kunde ist das ein
Beratungsmandat mit Haftung und Terminzusagen. Zwei Stunden pro Woche reichen dafuer nicht, und
zwei Stunden pro Woche sind die haerteste Randbedingung dieses Repos.

**Siebtens: Sechzehn Wettbewerber waren schneller.** Sechs Beratungshaeuser haben binnen fuenf
Wochen nach der Abkuendigung publiziert (ORBIS am 29.04.2026), zwei Plattformanbieter
(Simplifier, Neptune) betreiben fertige Abwerbe-Landingpages, und der Zielmarkt selbst wird von
einem „Top 20"-Vergleich abgedeckt.

## Offen geblieben

- **Wie viele Unternehmen SAP Build Apps produktiv einsetzen — in Deutschland oder weltweit.**
  Nicht ermittelbar, und zwar staerker als bei ByDesign: dort gab es wenigstens drei
  widersprechende Weltzahlen, hier gibt es gar keine. Der Ideator darf keine Zahl unterstellen.
  Der Negativbefund selbst ist die Antwort.
- **Der SAP-Originalwortlaut war fuer mich nicht direkt lesbar.** `help.sap.com/docs/build-apps/service-guide/sap-build-apps-path-forward`
  liefert nur den Seitentitel (JavaScript-Rendering), `community.sap.com` und
  `discovery-center.cloud.sap` antworten mit HTTP 403 — dasselbe Hindernis wie im ByDesign-Lauf.
  **Anders als dort existieren die SAP-Primaerdokumente aber nachweislich** (SAP Help Portal,
  zwei von SAP verfasste Community-Beitraege); die Zitate oben stammen aus Suchtreffern und aus
  On Device Solutions, die woertlich aus ihnen zitieren. Wer den Wortlaut braucht, muss die
  Seiten mit einem Browser oeffnen.
- **Ob das Migrationswerkzeug etwas kostet.** Die Anforderung ueber ein Support-Ticket
  (CA-LCA-ACP) spricht dafuer, dass es im laufenden Support enthalten ist; bestaetigt habe ich
  das nicht. Sollte es kostenpflichtig sein, aendert das an der Lage wenig — der Anbieter waere
  weiterhin SAP.
- **Ein Datumswiderspruch.** Die Rewion-Seite nennt in meiner Auswertung den **30.09.2026** als
  Einstellungsdatum und den 30.09.2024 als Ende des Community-Edition-Supports; alle anderen
  Quellen und SAP selbst nennen den **23.03.2026**. Ich habe den Widerspruch nicht aufloesen
  koennen und halte 23.03.2026 fuer richtig, weil SAP-eigene Dokumente und vier unabhaengige
  Quellen ihn tragen. Das Community-Edition-Datum liess sich nicht bestaetigen; belegt ist nur
  die Umbenennung in „SAP Build Apps free edition" um Juni 2024.
- **Die Preisstaffel je App und Jahr aus dem G-Cloud-PDF** (angeblich 2.059,65 bis 159,85 GBP).
  PDF nicht lesbar, Zahlen nicht gegengeprueft, deshalb nicht verwendet.
- **Wie gut das SAP-Werkzeug tatsaechlich konvertiert.** SAP schreibt selbst „best-effort". Ein
  Erfahrungsbericht eines Kunden war am 2026-08-28 nicht auffindbar. Selbst wenn das Ergebnis
  schlecht waere, aendert das die Ampel nicht: die Nacharbeit ist Entwicklungsarbeit im
  SAP-Werkzeugkasten, nicht ein Produkt, das ein Dritter verkaufen koennte.
