---
typ: recherche
signal: signals/market/2026-08-28-microsoft-365-preiserhoehung-juli-2026.md
erstellt: 2026-08-28
segmentgroesse: rund 197.000 Betriebe ab 10 Beschaeftigten mit Cloud-Office-Anwendungen (eigene Rechnung aus Destatis IKT 2025 x Unternehmensregister 2024, Obergrenze ueber alle Anbieter; der Microsoft-Anteil daran ist nicht ermittelbar)
anbieter_gefunden: 43 namentlich (11 deutschsprachige Lizenzoptimierer, 17 Systemhaeuser/Distributoren mit eigener Seite zu genau diesem Stichtag, 12 Lizenzmanagement-Werkzeuge, 3 kostenlose PowerShell-Werkzeuge, dazu Microsoft selbst)
preisspanne: 0,00 EUR (Cloumo-Gratisscan, AdminDroid-Gratistool, Microsofts eigene Nutzungsberichte, PowerShell-Skripte) bis 1.500 EUR einmalig (SMARTnetyx-Audit) bzw. 1.320,00 EUR im Monat (novaCapta-Lizenzstatusreport)
ampel: rot
---

# Microsoft hat die M365-Geschaeftspreise zum 01.07.2026 erhoeht — in Euro um 0,87 bis 1,30 EUR je Nutzer und Monat, und die daraus folgende Aufgabe (Lizenzen pruefen vor der Verlaengerung) wird in Deutschland bereits kostenlos erledigt

**Drei Vorbemerkungen, die den Rest der Recherche einordnen.**

**Erstens: Die Prozentsaetze des Signals stimmen, die Waehrung nicht.** Das Signal
nennt „6,00 auf 7,00 EUR" fuer Business Basic und „12,50 auf 14,00 EUR" fuer Business
Standard. Das sind die **US-Dollar-Listenpreise**. Die deutschen Euro-Listenpreise
liegen darunter und stehen am 2026-08-28 auf Microsofts eigener deutscher Seite:
Business Basic **6,07 EUR**, Business Standard **12,13 EUR**, Business Premium
**19,06 EUR** je Benutzer und Monat bei jaehrlicher Abrechnung, zzgl. MwSt.
(je `microsoft.com/de-de/microsoft-365/business/microsoft-365-business-basic`,
`.../microsoft-365-business-standard`, `.../microsoft-365-business-premium`, alle
abgerufen 2026-08-28). Vorher waren es laut hagel-it 5,20 EUR und 10,83 EUR
(`hagel-it.de/microsoft-365-insights/microsoft-365-preiserhoehung-2026`, abgerufen
2026-08-28). **Die tatsaechliche Erhoehung betraegt in Euro 0,87 EUR bzw. 1,30 EUR je
Nutzer und Monat** — nicht 1,00 bzw. 1,50 EUR. Auch die Angabe des Signals, Business
Premium bleibe „stabil bei 22 EUR", ist der Dollarpreis; in Euro sind es 19,06 EUR.

**Zweitens: Das Ereignis liegt in der Vergangenheit, das Sicherungsfenster ist zu.**
Die neuen Preise gelten seit dem 01.07.2026, also seit **58 Tagen**. Der letzte Tag,
an dem sich ein Kunde die alten Konditionen fuer ein weiteres Jahr sichern konnte, war
der **30.06.2026** (mt-computerservice, abgerufen 2026-08-28). Genau die
Handlungsempfehlung, die alle Anbieter seit Dezember 2025 verkauft haben, ist damit
nicht mehr ausfuehrbar.

**Drittens — und das ist der Teil, der dem Signal recht gibt:** Der Effekt ist trotzdem
nicht vorbei. Bestandskunden wandern erst **bei ihrer jeweiligen Vertragsverlaengerung**
auf den neuen Preis; das verteilt sich rollierend ueber die kommenden rund zehn Monate.
Eine Frist, die fuer jeden Kunden zu einem anderen Datum eintritt, ist kein Stichtag,
sondern ein Dauerzustand — und Dauerzustaende werden von Bestandsanbietern bedient,
nicht von Neueinsteigern. Die Recherche unten zeigt, dass das bereits geschehen ist.

## 1. Groesse des Segments

**Eine Zahl fuer „deutsche Betriebe mit Microsoft 365 Business Basic oder Standard"
existiert nicht.** Microsoft veroeffentlicht keine Laender- oder Tarifaufschluesselung;
weder die deutschsprachige Fachpresse noch einer der 17 gefundenen Systemhaus-Beitraege
nennt eine. Auch der Anteil des indirekten Vertriebs (CSP) am deutschen M365-Bestand ist
nicht publiziert.

**Was es gibt, ist eine amtliche Obergrenze — und die ist diesmal ungewoehnlich gut.**
Das Statistische Bundesamt erhebt jaehrlich die IKT-Nutzung in Unternehmen ab 10
Beschaeftigten. Erhebung 2025, Stand 24.11.2025
(`destatis.de/DE/Themen/Branchen-Unternehmen/Unternehmen/IKT-in-Unternehmen-IKT-Branche/Tabellen/iktu-06-cloud-computing.html`
und Pressemitteilung Nr. 416 vom 24.11.2025, beide abgerufen 2026-08-28):

| | insgesamt | 10-49 | 50-249 | 250+ |
|---|---|---|---|---|
| Bezug kostenpflichtiger Cloud-Dienste | 54 % | 51 % | 65 % | 86 % |
| davon: Office-Anwendungen | 68 % | 66 % | 72 % | 80 % |
| davon: E-Mail | 76 % | 76 % | 75 % | 77 % |

Kombiniert mit dem Unternehmensregister (Berichtsjahr 2024, Stand 01.12.2025:
429.318 rechtliche Einheiten mit 10-49, 84.701 mit 50-249, 18.632 mit 250+
Beschaeftigten):

> 429.318 × 0,51 × 0,66 = 144.508
> 84.701 × 0,65 × 0,72 = 39.640
> 18.632 × 0,86 × 0,80 = 12.819
> **Summe rund 197.000 Betriebe**

**Vier Vorbehalte.** (a) Das ist Cloud-Office **aller** Anbieter, inklusive Google
Workspace, Zoho, Nextcloud, openDesk — der Microsoft-Anteil ist nicht ermittelbar.
(b) Die beiden Prozentsaetze werden hier multipliziert, obwohl Destatis sie als getrennte
Merkmale ausweist; das ist zulaessig, weil die zweite Zeile ausdruecklich „von den
Cloud-Nutzern" meint, aber es bleibt eine Verkettung zweier Stichprobenwerte.
(c) Betriebe mit **unter 10 Beschaeftigten** (3.011.214 laut Unternehmensregister) sind
in der Destatis-Erhebung gar nicht enthalten. Sie nutzen M365 ebenfalls, sind aber
nirgends gezaehlt. (d) Berichtsjahre 2024 und 2025 werden hier gemischt.

**Verwertbar ist der Befund, nicht die Nachkommastelle: Das Segment ist gross — sechsstellig
— und damit ausdruecklich *nicht* der Grund fuer die rote Ampel.** Der Grund steht in
Abschnitt 5.

**Die zweite, wichtigere Groesse ist die Mehrbelastung je Betrieb**, und die ist klein.
Bei Business Standard (+1,30 EUR je Nutzer und Monat):

| Nutzer | Mehrkosten pro Jahr |
|---|---|
| 5 | 78,00 EUR |
| 10 | 156,00 EUR |
| 30 | 468,00 EUR |
| 50 | 780,00 EUR |

Die 468 EUR fuer 30 Nutzer nennt hagel-it unabhaengig als Beispielrechnung — das ist der
gesamte Schmerz, den das Signal beschreibt, fuer einen typischen Zielkunden dieser Fabrik.
Bei Business Basic (+0,87 EUR) sind es 313,20 EUR bei 30 Nutzern.

**Ausnahme, die groesser aussieht:** Die Frontline-Tarife steigen deutlich staerker
(F3 laut Fachpresse von 8 auf 10 EUR, F1 „rund +33 %", Spitzenwerte „bis zu +43 %";
mt-computerservice und boerse-express, beide abgerufen 2026-08-28). Frontline-Lizenzen
kauft aber, wer Schichtpersonal in Handel, Logistik oder Produktion hat — Betriebe mit
Einkauf, IT-Leitung und Rahmenvertrag. Nach den Erfahrungen frueherer Laeufe ist das
kein Segment fuer ein Nebengewerbe.

## 2. Wer es heute bedient

**Dicht besetzt, in fuenf Schichten. Ich habe deutsch und englisch gesucht, ueber
Preis-, Lizenz-, Optimierungs-, Audit-, Wechsel- und Werkzeugformulierungen sowie
absichtlich laienhaft („zahlen wir zu viel fuer Microsoft", „zu viele Office Lizenzen
kleine Firma wer hilft"). Jede Suche brachte neue Namen. Keine brachte eine Luecke.**

**Schicht 1 — Microsoft selbst, und zwar mit genau den Funktionen, die ein Produkt
verkaufen muesste.** Im Microsoft-365-Admin-Center liegen die Nutzungsberichte
(`Berichte > Nutzung`, filterbar nach „Letztes Aktivitaetsdatum") sowie unter
`Abrechnung > Lizenzen` die Spalte „Verfuegbare Lizenzen"; Microsoft beschreibt den
Zweck selbst als *„see who uses a service to the fullest extent and who barely uses it
and might not need a Microsoft 365 license"*
(`learn.microsoft.com/en-us/microsoft-365/admin/activity-reports/activity-reports`,
abgerufen 2026-08-28). Dazu die Kostenverwaltung im Admin-Center
(`learn.microsoft.com/en-us/microsoft-365/commerce/use-cost-mgmt`) und
**Verlaengerungserinnerungen per E-Mail 90, 60 und 30 Tage vor Ablauf** — der zweite
naheliegende Produktansatz („erinnere mich vor der Verlaengerung") ist damit
herstellerseitig erledigt.

**Schicht 2 — deutschsprachige Anbieter, die genau die Signalaufgabe als Leistung
fuehren (11 namentlich):** **Cloumo GmbH** (Moenchengladbach, Bueros in Duesseldorf,
Koeln, Muenchen, Berlin), **SAVECALL**, **LessLicense**, **Smartcloudoptimizer**,
**SMARTnetyx**, **mxp**, **CodeKlar**, **MARTINSFELD**, **Schoenfelder EDV**,
**novaCapta**, dazu **Dialogis Sentinel** fuer MSPs. Alle ueber Suchtreffer oder direkt
belegt, 2026-08-28.

Der wichtigste davon ist Cloumo, und zwar wegen des Preises — siehe Abschnitt 5 (a).

**Schicht 3 — Systemhaeuser, Distributoren und Carrier mit eigener Seite zu genau
diesem Stichtag (17 namentlich):** busitec, ACP Gruppe, amexus, hagel-it, IT-ZU,
mt-computerservice, CCS365, H5M, InSys AG, Netzleiter, **Telekom Geschaeftskunden**,
dazu aus der Schweiz Boss Info und redIT, aus Oesterreich RCC, sowie die Distributoren
**ADN** und **ALSO** und die Plattform **AppDirect** — deren Beitrag heisst woertlich
*„lock in current rates by June 30 and help customers optimize their Microsoft
solutions"*. Der Kanal hat das Signal also nicht nur aufgegriffen, sondern es
**bereits als Verkaufsanlass abgearbeitet**, sechs Monate bevor der Markt-Scout es
erfasst hat.

**Schicht 4 — Lizenzmanagement- und SaaS-Management-Werkzeuge (12 namentlich):**
CoreView, ManageEngine ADManager Plus, ManageEngine M365 Manager Plus, Matrix42,
ServiceNow SAM, Syskit, AdminDroid, 365tune (Austin/Texas, 500-2.500 USD im Monat),
Thalian, BetterCloud, Substly, Keepit. Die Capterra-Kategorie **„SaaS-Management"**
(`capterra.com.de/directory/31639/saas-management/software`, abgerufen 2026-08-28) hat
3 Seiten zu je 25 Produkten, also **rund 75 Produkte**.

**Schicht 5 — kostenlose Werkzeuge (3 namentlich, plus Cloumo aus Schicht 2):**
AdminDroids **„free Microsoft 365 license cost optimization tool"** (PowerShell, acht
Berichte: lizenzierte inaktive Nutzer, gesperrte Konten, unnoetig lizenzierte Shared
Mailboxes, nicht zugewiesene Lizenzen, nie angemeldete Nutzer, lizenzierte Gastnutzer,
Nutzer je Lizenzart, monatliche Gesamtkosten — inklusive „estimated cost savings",
`blog.admindroid.com/free-microsoft-365-license-cost-optimization-tool-using-powershell/`,
abgerufen 2026-08-28), die fertigen Skripte von `o365reports.com` und `m365corner.com`,
sowie die Anleitung von Schoenfelder EDV, die dasselbe mit Bordmitteln zeigt.

## 3. Was heute dafuer gezahlt wird

**Fuer die Lizenzen selbst** (Microsoft, deutsche Preisseiten, alle abgerufen
2026-08-28, je Benutzer und Monat, zzgl. MwSt.):

| Tarif | Jahresabo | Monatsabo | vorher (Jahresabo) |
|---|---|---|---|
| Microsoft 365 Business Basic | 6,07 € | 7,28 € | 5,20 € |
| Microsoft 365 Business Standard | 12,13 € | 14,56 € | 10,83 € |
| Microsoft 365 Business Premium | 19,06 € | 22,87 € | unveraendert |
| Microsoft 365 Apps for Business | 11,00 € | — | — |
| Business Basic EWR (ohne Teams) | 4,67 € | — | — |
| Business Standard + Copilot Business | 20,36 € | — | — |
| Business Premium + Copilot Business | 27,73 € | — | — |

*Die Vorher-Werte stammen von hagel-it, nicht von Microsoft; Microsoft weist alte Preise
nicht aus.* Die Copilot-Buendel sind **zusaetzliche** SKUs, kein Ersatz: Business
Standard und Premium bleiben einzeln bestellbar, was ich auf beiden Produktseiten
direkt geprueft habe. Die Buendel wurden zum 01.07.2026 aus einer Aktion in dauerhafte
Abonnements ueberfuehrt (23,50 USD bzw. 32 USD).

**Fuer die Loesung des Signalproblems — also fuer die Lizenzpruefung selbst:**

- **Cloumo, „M365 Security & Lizenz-Scan": 0,00 EUR.** Woertlich: *„€0 – Einmalige
  Analyse, unverbindlich – garantiert 0 €, keine Folgekosten."* Read-only ueber die
  Microsoft Graph API, ohne Agent und ohne Installation, Ergebnis in *„unter 15 Minuten"*,
  Kosten-, Sicherheits- und Compliance-Check in einem Durchlauf; die Seite nennt
  *„936 € durchschnittliches monatliches Einsparpotenzial"* je analysiertem Tenant
  (`cloumo.com/m365-scan/`, abgerufen 2026-08-28). Die laufende Ueberwachung danach ist
  ein Managed-Security-Paket zum „Festpreis – Preis auf Anfrage"; die regulaere
  M365-Betreuung kostet *„ab 39 €/Nutzer"*.
- **SAVECALL: erfolgsabhaengig.** Analyse ueber „50+ Datenpunkte", Lesezugriff auf das
  Admin Center, 7-10 Werktage. Preismodell: liegt die Ersparnis unter dem Paketpreis,
  zahlt der Kunde nur die tatsaechliche Ersparnis; wird nichts gefunden, *„Keine
  Rechnung"* (`savecall.de/microsoft-365-lizenzoptimierung/`, abgerufen 2026-08-28).
- **SMARTnetyx: 500-1.500 EUR einmalig** je Audit, Zielgruppe ausdruecklich KMU mit
  50-200 Beschaeftigten; Beispiel: 60 Nutzer von 10.000-11.500 EUR auf 6.900-8.200 EUR
  im Jahr (`smartnetyx.de/de/work/m365-lizenzoptimierung`, abgerufen 2026-08-28).
- **LessLicense: 0,00 EUR fuer den Einstieg** — *„30 Min Beratung. Konkrete Einsparungen.
  Kostenlos."*, dazu 27 kostenlose Leitfaeden (`lesslicense.de/wissen`, abgerufen
  2026-08-28).
- **novaCapta: 1.320,00 EUR im Monat** fuer monatliche Lizenzstatusreports (nur ueber
  die Suchzusammenfassung belegt, deshalb als Fachpresseangabe gekennzeichnet).
- **365tune: 500-2.500 USD im Monat**, Beispiel 500 Nutzer rund 1.200 USD im Monat —
  US-Anbieter, englischsprachig, Zielgruppe *„enterprise-scale environments"*
  (`365tune.com/insights/microsoft-365-audit-tool/`, abgerufen 2026-08-28).

**Die Rechnung, die den Markt erklaert.** Ein Betrieb mit 30 Business-Standard-Nutzern
traegt durch die Preiserhoehung **468 EUR im Jahr** mehr. Ein einmaliges Audit dafuer
kostet bei SMARTnetyx 500-1.500 EUR, bei Cloumo 0 EUR. **Der Betrag, den die Erhoehung
freisetzt, liegt unterhalb des Preises eines einzigen bezahlten Audits — und der
guenstigste Wettbewerber verlangt gar nichts.**

## 4. Die heutige Notloesung

**Sie heisst: weiterzahlen — und ihr Preis ist bekannt und niedrig.**

Der Aufpreis betraegt fuer den typischen Kleinbetrieb 78 bis 468 EUR im Jahr, verteilt
auf zwoelf Monatsrechnungen von einem Anbieter, dessen Rechnung ohnehin automatisch
abgebucht wird. Das ist keine Zahl, die eine Beschaffungsentscheidung ausloest. Nach
meinem Logbuch gilt: **Eine Notloesung, die weniger kostet als der Aufwand, sie zu
ersetzen, wird nicht ersetzt** — und hier kostet sie im Median rund 20 EUR im Monat.

**Die zweite Notloesung ist die Excel-Liste plus das Admin Center.** Der Weg dahin ist
oeffentlich dokumentiert und ohne Werkzeug gangbar: `Berichte > Nutzung > Microsoft 365
Aktivitaet`, nach „Letztes Aktivitaetsdatum" filtern, Nutzer mit 30+ Tagen Inaktivitaet
exportieren. Wer mehr will, nimmt das AdminDroid-Gratisskript oder eines der
PowerShell-Skripte von o365reports.

**Die dritte ist das Systemhaus, das ohnehin im Vertrag steht.** Praktisch jeder deutsche
KMU-Tenant wird ueber einen CSP-Partner abgerechnet, nicht direkt bei Microsoft. Fuer
diesen Partner ist die Lizenzpruefung kein Produkt, sondern Vertriebsvorbereitung fuer
die Verlaengerung — genau deshalb ist sie in Schicht 2 und 3 so haeufig kostenlos.

**Was die Notloesung wirklich kostet — die einzige Zahl, die sie teuer aussehen laesst,
und ihre Herkunft:** Mehrere Anbieter nennen uebereinstimmend, dass **10-30 % der
gebuchten Lizenzen** in KMU ungenutzt sind (SMARTnetyx: *„70% der KMUs, die ich audite,
zahlen fuer Microsoft 365 Lizenzen, die ihre Mitarbeiter gar nicht nutzen"*; Cloumo:
936 EUR monatliches Einsparpotenzial je Tenant; Fachbeitraege nennen „15-25 %" unter
Berufung auf Microsoft-Telemetrie). **Diese Zahlen stammen ausnahmslos von Anbietern,
die ein Audit verkaufen wollen; keine hat eine unabhaengige Primaerquelle, und ich habe
keine gefunden.** Sie sind als Marketingangabe zu lesen — bemerkenswert ist an ihnen
nicht die Hoehe, sondern dass elf deutschsprachige Anbieter sie gleichzeitig bewerben.
Ein Schmerz, um den elf Anbieter werben, ist kein unentdeckter Schmerz.

## 5. Was dagegen spricht

**(a) Ein deutscher Anbieter erledigt genau diese Aufgabe fuer genau dieses Segment
kostenlos, technisch genau so, wie ein Produkt es taete.** Cloumo GmbH, Moenchengladbach:
Lizenz- und Kostenscan read-only ueber die Microsoft Graph API, ohne Agent, Ergebnis in
unter 15 Minuten, mit beziffertem Einsparpotenzial — *„garantiert 0 €, keine
Folgekosten"*. Das ist nicht „ein aehnliches Werkzeug", sondern dieselbe Aufgabe, im
deutschsprachigen Markt, zum Preis null. **Das allein traegt die rote Ampel nach der
Definition dieser Rolle.**

**(b) Der Preisboden ist null, und zwar mehrfach unabhaengig.** Neben Cloumo: Microsofts
eigene Nutzungs- und Lizenzberichte im Admin Center, AdminDroids kostenloses
Optimierungswerkzeug mit acht Berichten und Einsparrechnung, zwei oeffentliche
PowerShell-Skriptsammlungen, LessLicense mit kostenloser Erstberatung — und SAVECALL,
das die Leistung **erfolgsabhaengig ohne Grundgebuehr** anbietet („keine Ersparnis, keine
Rechnung"). Gegen ein Angebot, das im schlechtesten Fall nichts kostet, gibt es kein
Preisargument.

**(c) Die freigesetzte Summe ist kleiner als der Preis der Loesung.** 468 EUR im Jahr
Mehrkosten bei 30 Nutzern gegen 500-1.500 EUR fuer ein einmaliges Audit. Ein
Abo-Produkt muesste deutlich darunter liegen und traefe dabei auf die Gratiskonkurrenz
aus (a) und (b). Nach G7 der `grenzen.md` ist ausserdem netto zu rechnen: Von einem
Jahresbeitrag, der ueberhaupt in dieses Fenster passt, bleibt nach Grenzsteuersatz rund
die Haelfte.

**(d) Der Kanal hat das Signal bereits abgearbeitet, und zwar vor acht Monaten.**
17 Systemhaeuser, Distributoren und Carrier mit fertiger Seite zu genau diesem Stichtag,
gefunden in einer Handvoll Suchen — darunter die Telekom, ACP, ALSO, ADN und AppDirect.
Die Ankuendigung stammt vom 04.12.2025; die Beitraege stammen aus dem ersten Halbjahr
2026. Der Markt-Scout hat das Signal am 2026-08-28 erfasst, also **fast neun Monate nach
der Ankuendigung und knapp zwei Monate nach Inkrafttreten**.

**(e) Der einzige echte Termin ist verstrichen.** Wer die alten Preise fuer ein weiteres
Jahr sichern wollte, musste bis zum 30.06.2026 verlaengern. Diese Handlungsempfehlung —
die zentrale Botschaft saemtlicher 17 Anbieterbeitraege — ist nicht mehr ausfuehrbar.
Was bleibt, ist die rollierende Verlaengerungswelle, also ein Zustand ohne Stichtag.
Nach der Lehre aus dem Project-Online- und dem ByDesign-Lauf traegt ein Marktsignal nur
im Fenster von etwa 12-24 Monaten Restfrist; hier ist die Frist bereits abgelaufen und
der Rest ist fristlos.

**(f) Die Praemisse „zurueckgelassene Nutzergruppe" trifft nicht zu.** Bei einer
Abkuendigung gibt es eine Gruppe, deren Werkzeug verschwindet. Hier verschwindet nichts:
Alle Tarife bleiben bestellbar, Business Standard und Premium auch ohne Copilot-Buendel,
die Funktionen wachsen sogar. Das Signal selbst raeumt ein, dass sich kein dritter
Anbieter als Umsteige-Nachfolger positioniert — die Erklaerung dafuer ist nicht eine
Marktluecke, sondern dass es nichts zu ersetzen gibt. Ein Preisanstieg von 0,87 EUR je
Nutzer und Monat loest keine Migration einer Kollaborationsplattform aus, an der E-Mail,
Dateiablage, Telefonie und Geraeteverwaltung haengen.

**(g) Das Ausweichen ist ebenfalls besetzt, und ebenfalls gratis.** Die freien
Alternativen sind aus dem Office-2021-Lauf vom selben Tag bereits dokumentiert:
LibreOffice, SoftMaker FreeOffice (ausdruecklich auch kommerziell kostenlos),
OnlyOffice Community, Collabora Community und **openDesk** des bundeseigenen ZenDiS.
Fachpresse berichtet, dass KMU auf Open-Source- und DSGVO-Alternativen ausweichen
(`it-boltwise.de`, abgerufen 2026-08-28) — die Migration dorthin ist aber ein
Projekt mit Praesenzanteil, also nach G3 und G4 unerreichbar.

**(h) Der Auftragsgegenstand ist Beratung, nicht Software.** Bei SAVECALL: 30-minuetiger
Kickoff-Call, dann 7-10 Werktage Analyse, dann ein priorisierter Massnahmenplan. Bei
SMARTnetyx: ein Audit mit persoenlicher Auswertung. Bei allen Systemhaeusern: ein
Gespraech vor der Verlaengerung. Der automatisierbare Teil — den Tenant auslesen — ist
der billigste Teil der Kette und deshalb der, den alle verschenken; der bezahlte Teil
ist die Entscheidung, welcher Mitarbeiter welchen Tarif braucht, und die verlangt
Kenntnis der Rollen im Kundenbetrieb.

**(i) Und die Aufgabe waechst nicht, sie schrumpft.** Ein Tenant wird einmal
aufgeraeumt; danach ist der Wert eines Werkzeugs eine jaehrliche Wiederholung mit
abnehmendem Ertrag. Nach dem ersten ruhigen Jahr wird es gekuendigt — dieselbe Struktur
wie beim CRA-Meldewerkzeug: eine Versicherung ohne Schadensfall.

## Offen geblieben

- **Der Microsoft-Anteil am deutschen Cloud-Office-Bestand.** Die 197.000 Betriebe in
  Abschnitt 1 umfassen alle Anbieter. Wie viele davon M365-Geschaeftstarife nutzen, ist
  nicht publiziert — weder von Microsoft noch von Bitkom noch von Destatis. Der
  Bitkom Cloud Report 2026 nennt 86 % Cloud-Nutzung, aber ohne Produktaufschluesselung.
- **Betriebe unter 10 Beschaeftigten.** Destatis erhebt sie in der IKT-Statistik nicht.
  Sie sind zahlenmaessig die groesste Gruppe (3.011.214) und wirtschaftlich die
  schwaechste: Bei fuenf Nutzern betraegt die Mehrbelastung 78 EUR im Jahr. Fuer diese
  Gruppe habe ich keinen einzigen Anbieter mit einem Selbstbedienungsprodukt gefunden —
  aber auch keinen Hinweis darauf, dass sie fuer irgendetwas zahlen wuerde.
- **Der CSP-Anteil.** Wie viele deutsche KMU ihre Lizenzen ueber einen Partner statt
  direkt bei Microsoft beziehen, ist nicht veroeffentlicht. Die Annahme in Abschnitt 4
  („praktisch jeder"), stuetzt sich nur darauf, dass alle 17 gefundenen Systemhaeuser
  als CSP-Partner auftreten — das ist ein Indiz, kein Beleg.
- **Die 10-30-Prozent-Verschwendungsquote.** Von elf Anbietern behauptet, von keinem
  belegt. Ich habe keine unabhaengige Erhebung dazu gefunden. **Der Ideator darf diese
  Zahl nicht verwenden.**
- **Die exakten Prozentsaetze der Microsoft-Ankuendigung.** Sie liegen im Originalpost
  vom 04.12.2025 nur als Bildgrafik vor; der Fliesstext gibt allein den Satz *„The
  following list price changes will go into effect on July 1, 2026"* und den Hinweis
  auf globale Geltung mit lokalen Marktanpassungen her. Die deutschen Euro-Preise habe
  ich stattdessen direkt auf Microsofts Produktseiten geprueft — die sind belastbarer
  als jede Prozentangabe.
- **Preise fuer die Managed-Varianten.** Cloumos laufende Ueberwachung und SAVECALLs
  Paketpreis stehen beide unter „auf Anfrage". Die Preisspanne im Frontmatter betrifft
  deshalb nur die einmalige Analyse.
- **Neu bestaetigt gehend (fuers Logbuch):** `microsoft.com/de-de/microsoft-365/business/microsoft-365-business-<tarif>`
  (Einzelproduktseiten geben Jahres- **und** Monatspreis, die Vergleichsseite nur den
  Jahrespreis der Copilot-Buendel), `destatis.de/.../IKT-in-Unternehmen-IKT-Branche/Tabellen/`
  und `destatis.de/DE/Presse/Pressemitteilungen/2025/11/PD25_416_52911.html`,
  `cloumo.com`, `savecall.de`, `smartnetyx.de`, `lesslicense.de`, `smartcloudoptimizer.com`,
  `365tune.com`, `blog.admindroid.com`, `hagel-it.de`, `mt-computerservice.de`,
  `busitec.de`, `capterra.com.de/directory/31639/...`. Microsofts Blogpost vom
  04.12.2025 laedt, gibt die Preisgrafik aber nicht her.
