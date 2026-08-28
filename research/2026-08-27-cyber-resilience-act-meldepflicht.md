---
typ: recherche
signal: signals/regulation/2026-08-27-cyber-resilience-act-meldepflicht.md
erstellt: 2026-08-28
segmentgroesse: nicht ermittelbar (Obergrenze 352.527 rechtliche Einheiten in DE, tatsaechlich meldende Gruppe zweistellig bis dreistellig je Jahr EU-weit)
anbieter_gefunden: 17 kommerzielle, dazu 8 dedizierte Fachportale und 6 kostenlose institutionelle Angebote
preisspanne: 0-49 EUR/Monat im Selbstbedienungssegment, darueber ausschliesslich "auf Anfrage"
ampel: rot
---

# Ab 11.09.2026 muessen Hersteller aktiv ausgenutzte Schwachstellen binnen 24 Stunden an ENISA und das koordinierende CSIRT melden — ein Ereignis, das 2025 weltweit 245-mal eintrat und dessen Meldung ueber ein kostenloses EU-Webformular laeuft.

## 1. Groesse des Segments

**Nicht ermittelbar, und der Grund ist selbst der Befund.** Die Meldepflicht nach Art. 14 CRA trifft
formal jeden Hersteller, der ein Produkt mit digitalen Elementen in der EU in Verkehr bringt — ohne
Schwellenwert, ohne Branchenzuschnitt, ohne Register. Es gibt keine Zulassung, an der man abzaehlen
koennte, und keine amtliche Statistik, die „Hersteller von Produkten mit digitalen Elementen" als
Merkmal fuehrt.

**Obergrenze aus dem Unternehmensregister** (Destatis, Berichtsjahr 2024, Stand 1. Dezember 2025,
abgerufen 2026-08-28 — wortwoertliche Tabellenwiedergabe):

| Abschnitt | insgesamt | 0–10 | 10–50 | 50–250 | 250+ |
|---|---|---|---|---|---|
| C Verarbeitendes Gewerbe | 209.815 | 140.992 | 47.713 | 16.442 | 4.668 |
| J Information und Kommunikation | 142.712 | 124.056 | 13.991 | 3.863 | 802 |

Summe 352.527. Das ist eine **reine Obergrenze und keine Segmentgroesse**: Sie enthaelt Baeckereien
mit Maschinenpark ebenso wenig wie IT-Dienstleister ohne eigenes Produkt korrekt abgegrenzt sind, und
sie enthaelt umgekehrt nicht die vernetzten Produkte aus Abschnitt C-fremden Branchen. Quelle:
[Destatis Unternehmensregister, Beschaeftigtengroessenklassen WZ08](https://www.destatis.de/DE/Themen/Branchen-Unternehmen/Unternehmen/Unternehmensregister/Tabellen/unternehmen-beschaeftigtengroessenklassen-wz08.html)

**Die Zahl, auf die es ankommt, ist eine andere und viel kleiner:** wie viele Hersteller pro Jahr
tatsaechlich einen Meldefall haben. Meldepflichtig ist nur eine *aktiv ausgenutzte* Schwachstelle
(Art. 3 Nr. 42 CRA: „zuverlaessige Nachweise, dass ein boeswilliger Akteur sie ohne Zustimmung des
Systemeigentuemers ausgenutzt hat") oder ein *schwerwiegender* Sicherheitsvorfall. Der beste
verfuegbare Naeherungswert dafuer ist der KEV-Katalog der US-Behoerde CISA — das einzige oeffentlich
gepflegte Verzeichnis aktiv ausgenutzter Schwachstellen:

- Bestand Ende 2025: **1.484 Eintraege** (seit 2021 kumuliert)
- Neuaufnahmen im Jahr 2025: **245**, weltweit, ueber alle Hersteller
- Die fuenf meistbetroffenen Hersteller 2025: Microsoft (39), Apple (9), Cisco (8), Fortinet (8),
  Google Chromium (7)

Quelle: [security-insider.de, 16.01.2026](https://www.security-insider.de/cisa-katalog-bekannte-ausgenutzte-sicherheitsluecken-highlights-2025-a-88e7c79dc2bd279d438a9359de8f2bbc/),
abgerufen 2026-08-28.

Der KEV-Katalog ist enger gefasst als Art. 14 CRA (er erfasst nur, was CISA aufnimmt, und Vorfaelle
gar nicht), taugt also nur als Groessenordnung. Aber die Groessenordnung ist eindeutig: **Das
meldepflichtige Ereignis konzentriert sich fast vollstaendig auf global vertriebene Produkte grosser
Anbieter.** Ein deutscher Maschinenbauer mit vierzig Mitarbeitern erlebt es statistisch nie. Ein
Produkt, das fuer den Ernstfall bereitsteht, wird von einer Zielgruppe gekauft, die den Ernstfall
erwartet — und diese Zielgruppe ist dreistellig, nicht sechsstellig.

## 2. Wer es heute bedient

Reichlich, in drei Schichten.

**Kostenlos und institutionell — die dichteste Gratis-Front seit dem EUDR-Lauf:**

| Anbieter | Angebot | Kosten |
|---|---|---|
| ENISA | Single Reporting Platform (der gesetzliche Meldekanal selbst), Factsheet, FAQ, drei Nutzeranleitungen (Registrierung, Meldungseinreichung, Schnittstellenfunktionen, zuletzt 14.08.2026), Webinar zwei Wochen vor Inbetriebnahme | 0 EUR |
| EU-Kommission | Commission Guidance zum CRA (Meldepflichten in Abschnitt 9.1), FAQ-Dokument | 0 EUR |
| BSI | TR-03183 Teil 1–3 (Teil 2 SBOM, Teil 3 Schwachstellenmeldeverfahren), drei CRA-Flyer, „Management Blitzlicht CRA", Normungs-Dashboard, Helpdesk | 0 EUR |
| CRAIG (ASBL belg. Rechts, gegr. 18.03.2026) | Scope-Check-Werkzeug, Knowledge Repository mit Vorlagen, TARA-Methoden, SDLC-Richtlinien, lokale Chapter Boeblingen und Stuttgart | Einzelmitgliedschaft 0 EUR |
| Eclipse ORC Working Group | CRA-FAQ und Ressourcenplattform (`cra.orcwg.org`, CRA Hub auf GitHub) | quelloffen |
| VDMA | Regulierungscockpit-Factsheets, Handlungsanleitung Lieferantenselbstauskunft CRA, FAQ (2. Auflage), **CRA Vulnerability Handling Guideline**, Arbeitskreis CRA, Webinare | Mitgliederleistung |
| cyberresilienceact.eu (i46 s.r.o.) | Klassifizierungstool, Compliance-Matrix, **Reporting-Guide**, Support-Planner, State-of-Play-Seite | alle 0 EUR |

Dazu verpflichtet **Art. 33 CRA die Mitgliedstaaten selbst**, Sensibilisierungs- und
Schulungsmassnahmen zu organisieren, „einen speziellen Kommunikationskanal fuer Kleinst- und
Kleinunternehmen" einzurichten und bei Konformitaetsbewertungen zu unterstuetzen; Abs. 3 verpflichtet
die Kommission zu Leitlinien fuer KMU, Abs. 5 erlaubt KMU vereinfachte technische Dokumentation.
([Art. 33 CRA im Wortlaut, enobyte.com](https://enobyte.com/de/legal/cra/33/), abgerufen 2026-08-28)

**Kommerziell, mit Produkt:** ONEKEY (Duesseldorf, Compliance Wizard, Digital Cyber Twins mit
24/7-Ueberwachung), itemis SECURE (Sponsor von CRAIG), Kunnus/Think Ahead (SBOM, CVE-Monitoring,
Meldeprozesse), CompliantDesk (buendelt NIS2, DSGVO, ISO 27001), CRAToolkit (Reporting Wizard, SBOM
Analyzer, AI Copilot), CRA Evidence (Fristenueberwachung, SRP-Onboarding), heyData, Greenbone
(OpenVAS-Linie, kein dediziertes CRA-Meldewerkzeug), cybervize, Secuvise/cyber-regulierung.de.

**Beratung und Pruefung:** TÜV SÜD, Deloitte, ADVISORI, syracom, admeritia, docufy, BOS, IHK
Muenchen / Koeln / Rhein-Neckar, Swiss Infosec.

**Eigene Fachportale zu genau dieser einen Verordnung:** cyberresilienceact.eu,
european-cyber-resilience-act.com, cyber-resilience-act.de, cyber-resilience-act.net,
cyber-regulierung.de, cra-berater.de, sbom-management.de, enobyte.com/legal/cra. Acht Domains fuer
eine Verordnung — dieselbe Signatur wie bei der EUDR (fuenf Portale) und der E-Rechnung (zwei
Fachdomains plus Anbieterverband). Wo ein Thema eigene Magazine hat, ist der Informationslayer nicht
knapp, sondern Ueberangebot.

**Kostenlose Betroffenheitschecks als Lead-Magnet** bieten mindestens sechs davon an: CRAIG
(Scope Check), CompliantDesk („CRA Fast-Check"), Kunnus („kostenloser CRA-Compliance-Check"),
heyData („CRA-CHECK"), CRA Evidence (Anwendbarkeitspruefung, Rollenquiz), d.works
(„Bin ich vom CRA betroffen?"). Genau die Einstiegsfrage, die ein bezahltes Werkzeug verkaufen
muesste, ist sechsfach umsonst besetzt.

## 3. Was heute dafuer gezahlt wird

**Im Selbstbedienungssegment: null bis 49 EUR im Monat.** CRAToolkit nennt als einziger Anbieter
oeffentliche Preise (abgerufen 2026-08-28, woertlich):

- Free: „EUR 0 forever"
- Pro: „EUR 49 /month"
- Founding Member: „EUR 29 /month — 🔒 Locked forever, price never increases", „Only 20 slots"

CRA Evidence fuehrt drei rollenbasierte Plaene (Manufacturer, Importer, Distributor) mit je zwei
Stufen, beide als „Custom" ausgewiesen, plus 14 Tage Test ohne Kreditkarte. ONEKEY, itemis, Kunnus,
CompliantDesk, heyData, Greenbone: keine oeffentlichen Preise, ausschliesslich „Demo buchen" bzw.
„Produktanfrage" — das erwartete Bild fuer B2B (im Logbuch mehrfach bestaetigt: 24 von 31 bei NIS2).

**Ein Aufwandswert fuer den Gesamt-CRA existiert, aber nicht fuer die Meldepflicht.** Die
Folgenabschaetzung der Kommission (SWD(2022) 282) beziffert die aggregierten Befolgungskosten
EU-weit auf **rund 29 Mrd. EUR**, denen eine erwartete Schadensreduktion von 180 bis 290 Mrd. EUR
jaehrlich gegenuebersteht. Diese Summe deckt Sicherheitsanforderungen, Konformitaetsbewertung,
Dokumentation *und* Meldepflichten zusammen ab — auf die Meldung allein laesst sie sich nicht
aufteilen. Das EUR-Lex-Original war nicht abrufbar (leere Antwort, wie im Logbuch vermerkt), die
Zahl stammt aus zitierender Fachpresse und ist damit ein Korridorwert, kein Primaerbeleg.

**Nicht verwendet:** Eine Suchzusammenfassung nannte „150.000–400.000 EUR fuer fuenf Produkte ohne
IEC-62443-Basis ueber 18 Monate". Beim Abruf der genannten Quelle (kunnus.tech) stand die Zahl dort
nicht. Nach der Regel aus dem CSRD-Lauf faellt sie damit aus.

## 4. Die heutige Notloesung

**Fuer die grosse Mehrheit: gar nichts, und das bleibt richtig.** Wer nie eine aktiv ausgenutzte
Schwachstelle hat, meldet nie. Die Notloesung besteht darin, den Fall abzuwarten und im Ernstfall
das ENISA-Webformular auszufuellen — kostenlos, ohne API, ohne Gebuehr. ENISA hat am 03.08.2026
klargestellt, dass die CSIRT-Validierung der Registrierung **keine Voraussetzung** fuer die
Pflichterfuellung ist; ein nicht verifiziertes Konto darf bis zu zehn Meldungen einreichen. Der
gesamte Vorbereitungsaufwand, den cyberresilienceact.eu auflistet, sind sechs Schritte: EU-Login
anlegen, Produkt klassifizieren, zustaendiges CSIRT bestimmen, Meldetexte vorbereiten,
Verantwortlichkeit ausserhalb der Buerozeiten festlegen, Fristen verstehen. Ein Nachmittag, einmal.

**Fuer die Firmen, bei denen der Fall realistisch ist: ein PSIRT oder Incident-Response-Prozess, den
sie bereits haben.** Wer NIS2-, DORA- oder ISO-27001-pflichtig ist, betreibt die Meldemaschinerie
seit Jahren; ein ISMS nach ISO 27001 deckt nach Anbieterangabe rund 70–80 % der Anforderungen beider
Regelwerke ab. Die CRA-Meldung ersetzt die NIS2- oder DSGVO-Meldung nicht und wird nicht von ihr
ersetzt — es kommt ein dritter Kanal hinzu, aber der Prozess dahinter ist derselbe und existiert.

**Der einzige echte neue Aufwand ist Rufbereitschaft.** Die 24-Stunden-Frist laeuft ab Kenntnis,
auch nachts und am Wochenende, und die Bewertung „ist das aktiv ausgenutzt?" muss ein Mensch mit
Produktkenntnis treffen. Das ist eine Personalfrage, keine Softwarefrage.

**Was die Zielgruppe selbst sagt:** ENISAs KMU-Umfrage (194 Organisationen aus 31 Laendern,
veroeffentlicht 13.07.2026) — 66 % hatten vom CRA gehoert; 142 der Befragten betonten den Bedarf an
**finanzieller** Unterstuetzung; ueber 70 % wuenschten sich Vorlagen fuer technische Dokumentation und
sichere Entwicklung; „Incident response and product life cycle management is the weakest area
overall, particularly for microcompanies". Eine Gruppe, deren meistgenannter Wunsch Geld ist und
deren zweiter Gratisvorlagen sind, ist kein Abomarkt.

## 5. Was dagegen spricht

**a) Die Frist ist in vierzehn Tagen.** Erfasst am 2026-08-27, Stichtag 2026-09-11. Selbst wenn
alles andere guenstig laege, waere kein Produkt rechtzeitig da. Zum siebten Lauf in Folge waere die
Fristpruefung beim Regel-Scout billiger gewesen als dieser Lauf.

**b) Es gibt bis zum 11.12.2027 keine Sanktion.** Art. 71 Abs. 2 CRA im Wortlaut: „Diese Verordnung
gilt ab dem 11. Dezember 2027. Artikel 14 gilt jedoch ab dem 11. September 2026, und Kapitel IV
(Artikel 35 bis 51) gilt ab dem 11. Juni 2026." Art. 64 (Sanktionen) gehoert zu keiner der beiden
Ausnahmen — die Meldepflicht steht 15 Monate lang ohne eigene Bussgeldnorm da.
([Art. 71](https://enobyte.com/de/legal/cra/71/), [Art. 64](https://enobyte.com/de/legal/cra/64/),
[itmr-legal.de zur Meldepflicht](https://itmr-legal.de/blog/cra-meldepflicht-art-14), alle abgerufen
2026-08-28)

**c) Und danach ist gerade die Zielgruppe dieser Fabrik ausgenommen.** Art. 64 Abs. 10 nimmt
Kleinstunternehmen und KMU ausdruecklich von Geldbussen fuer Fristverstoesse nach „Artikel 14
Absatz 2 Buchstabe a" und „Artikel 14 Absatz 4 Buchstabe a" aus — also genau fuer die 24-Stunden-
Fruehwarnung, die den ganzen Zeitdruck erzeugt. Verwalter quelloffener Software sind „bei jedem
Verstoss" ausgenommen. Der Zwang, den ein Produkt verkaufen wuerde, existiert fuer kleine Hersteller
rechtlich nicht.

**d) Der Meldekanal ist ein kostenloses Formular ohne Schnittstelle.** Die ENISA-SRP hat zum
Stand 14.08.2026 keine API und keine veroeffentlichte URL. Ohne API gibt es nichts zu integrieren —
ein Drittwerkzeug kann die Meldung nicht absetzen, nur den Text vorbereiten. Genau das tun der
kostenlose Reporting-Guide von cyberresilienceact.eu und die drei ENISA-Anleitungen bereits.

**e) Die Kernleistung waere eine Sicherheitsbewertung unter 24-Stunden-Frist — und damit gegen
mindestens drei Grenzen.** Wer entscheidet, ob eine Schwachstelle „aktiv ausgenutzt" oder ein
Vorfall „schwerwiegend" ist, faellt eine Bewertung, an der eine Frist mit spaeterem Bussgeldrisiko
von bis zu 15 Mio. EUR oder 2,5 % des Weltumsatzes haengt (Art. 64 Abs. 2). Das ist G6
(Fristberechnung, Sicherheitsfreigaben) im Kern; eine Zusage, binnen 24 Stunden zu reagieren,
verletzt G3 unmittelbar; und die Bereitschaft ausserhalb der Buerozeiten waere G9. Ein reines
Vorlagen- und Erinnerungswerkzeug ohne Bewertung umgeht das — aber genau dieses Werkzeug gibt es
mehrfach umsonst (siehe d).

**f) Das Ereignis tritt zu selten ein, um ein Abo zu tragen.** 245 KEV-Neuaufnahmen 2025 weltweit,
davon 71 auf die fuenf groessten Anbieter. Ein Werkzeug, das fuer einen Fall bereitsteht, der beim
Kunden statistisch nie eintritt, ist ein Versicherungsprodukt ohne Versicherungslizenz — es wird nach
dem ersten Jahr ohne Vorfall gekuendigt. Die Loesungen mit tragfaehigem Umsatz in diesem Feld
verkaufen nicht die Meldung, sondern das laufende Schwachstellen-Monitoring davor (ONEKEY, Greenbone,
Kunnus) — und das ist ein besetzter, kapitalintensiver Scanner-Markt.

**g) Der Adressat ist selbst ein Technikunternehmen.** Hersteller von Produkten mit digitalen
Elementen haben Entwickler, oft ein Sicherheitsteam, fast immer einen Verband mit Gratis-Leitfaden
(VDMA-Vulnerability-Handling-Guideline) und ab 2027 ohnehin ein Konformitaetsprojekt mit externer
Begleitung. Das ist nach der Erfahrung aus dem Data-Act-Lauf die am schwersten zu beliefernde
Zielgruppe fuer ein IT-Compliance-Werkzeug eines Nebengewerbes.

**h) Das eigentliche Geld liegt woanders und ist unerreichbar.** Der wirtschaftlich interessante
Teil des CRA ist die Vollkonformitaet ab 11.12.2027: Konformitaetsbewertung, technische
Dokumentation, CE-Kennzeichnung, SBOM. ONEKEY weist darauf hin, dass fuer „rund 90 Prozent aller
vernetzten Produkte" eine Selbsterklaerung genuegt — der Rest geht ueber notifizierte Stellen, deren
Kapitel IV seit 11.06.2026 gilt. Das ist Pruef- und Beratungsgeschaeft (TÜV SÜD, Deloitte, ADVISORI),
kein Lizenzgeschaeft, und fuer ein Nebengewerbe mit zwei Stunden pro Woche unerreichbar.

## Offen geblieben

- **Eine belastbare Segmentzahl fuer „Hersteller von Produkten mit digitalen Elementen in
  Deutschland" gibt es nicht** und wird es nicht geben: kein Register, keine Zulassung, kein
  amtliches Merkmal. Die Destatis-Obergrenze von 352.527 rechtlichen Einheiten ist als Nenner
  unbrauchbar. Der Ideator darf sich auf keine Zahl in diesem Feld stuetzen.
- **Die Folgenabschaetzung der Kommission (SWD(2022) 282) konnte ich nicht im Original lesen** —
  EUR-Lex lieferte erneut eine leere Antwort, das PDF ist nach bisheriger Erfahrung nicht
  auswertbar. Die 29 Mrd. EUR stammen aus zitierender Fachpresse; eine Aufteilung auf Meldepflicht
  gegen Produktanforderungen, und damit ein Aufwandswert *pro Unternehmen und Jahr*, fehlt.
- **Wie viele CRA-Meldungen es tatsaechlich geben wird, weiss niemand.** Der KEV-Katalog ist eine
  Naeherung mit anderem Zuschnitt (US-Behoerdenauswahl, keine Vorfaelle). ENISA veroeffentlicht
  bisher keine erwarteten Meldezahlen. Eine Suchzusammenfassung nannte „99,5 Prozent aller
  veroeffentlichten Schwachstellen werden nie aktiv ausgenutzt"; auf der angegebenen Quellseite war
  die Zahl nicht auffindbar (Redirect auf guardian360.net), sie ist deshalb hier **nicht** verwendet.
- **Die SRP war zum Abrufdatum noch nicht live** (Stand 14.08.2026: keine URL, keine API, keine
  Liste der koordinierenden CSIRTs). Ob ENISA spaeter eine API nachliefert, ist die einzige
  Entwicklung, die dieses Feld technisch oeffnen wuerde — und selbst dann blieben die Gruende a, c,
  e, f und g bestehen.
- **Preise der etablierten Anbieter (ONEKEY, itemis, Kunnus, CompliantDesk) sind nicht oeffentlich.**
  Der belegte Preisboden von 0 EUR (CRAToolkit Free) reicht fuer die Ampel aus; eine Aussage ueber
  die Obergrenze der Zahlungsbereitschaft im Meldesegment ist damit nicht moeglich.
- **Nicht geprueft:** ob das deutsche CRA-Durchfuehrungsgesetz existiert oder welche Behoerde als
  Marktueberwachung benannt wird. Fuer die Ampel ohne Belang, weil Art. 64 ohnehin erst ab
  11.12.2027 greift — fuer einen spaeteren Lauf zum *Konformitaets*teil des CRA waere es der erste
  Abruf.
