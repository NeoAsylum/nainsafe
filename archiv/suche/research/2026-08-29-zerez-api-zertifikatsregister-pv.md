---
typ: recherche
signal: signals/tech/2026-08-29-zerez-api-zertifikatsregister-pv.md
erstellt: 2026-08-29
segmentgroesse: 866 Stromnetzbetreiber (2024) als kaufende Gruppe; 9.219 PV-Installateure als Nutzergruppe; Zahl der in ZEREZ registrierten Einheiten, Hersteller und Nutzer nicht ermittelbar
anbieter_gefunden: 23 namentlich (18 aus der BDEW-Anbieterliste Netzanschlussportale, Seite 1; dazu ITC AG; dazu vier Dienstleister der Installateurseite) — vier davon mit belegter, fertiger ZEREZ-Anbindung
preisspanne: 0 EUR (ZEREZ selbst, gesetzlich unentgeltlich) bis 9.900 EUR einmalig plus 3.000 EUR/Jahr (ebsygon-Netzanschlussportal); auf der Installateurseite 299-593,81 EUR je Netzanmeldung als Dienstleistung
ampel: rot
---

# ZEREZ hat seit 17.04.2026 eine API — der Registerbetreiber liefert sie gesetzlich unentgeltlich, vier deutsche Portalanbieter haben die automatische Zertifikatsprüfung bereits eingebaut, und die Bundesnetzagentur zieht den Massenabruf gerade selbst in das Marktstammdatenregister.

## Vorbemerkung: Das Signal ist richtig, aber es beschreibt einen Baustein, dessen Nutzer schon versorgt sind

Der Tech-Scout hat den Sachverhalt korrekt erfasst: Es gibt die API, sie ist seit dem
17.04.2026 verfügbar, und sie erlaubt den seriellen statt einzelnen Abruf. Die drei
Fragen, die er offengelassen hat („kostenpflichtig? Rate Limits? für alle
Spannungsebenen?"), beantworte ich unten — die erste eindeutig, die zweite und dritte
nicht.

Wichtiger ist die Frage, die im Signal gar nicht steht: **Wer wartet auf diese
Automatisierung, und wartet er noch?** Die Antwort ist dreifach besetzt — vom
Registerbetreiber selbst, von der Bundesnetzagentur und von den Anbietern der
Netzanschlussportale.

## 1. Groesse des Segments

**Die kaufende Gruppe sind die Netzbetreiber, und sie ist zählbar:**

| Größe | Wert | Quelle, abgerufen 2026-08-29 |
|---|---|---|
| Stromnetzbetreiber DE | **866** (Jahr 2024) | energie-und-management.de, Statistik des Tages vom 26.08.2025, nach Statista: „Im Jahr 2024 wurden in Deutschland insgesamt 866 Stromnetzbetreiber gezählt." (`energie-und-management.de/nachrichten/technik/detail/anzahl-der-stromnetzbetreiber-in-deutschland-330311`) |
| dieselbe Zahl, Vorjahr | 866 (Jahr 2023), Quelle BNetzA/Bundeskartellamt | ebd., Artikel vom 29.01.2024 (`.../anzahl-der-stromnetzbetreiber-in-deutschland-207790`) |
| Verteilnetzbetreiber Strom, Verbandsangabe | rund 830 | BDEW, Suchzusammenfassung — **nicht auf der Quellseite gegengeprüft, deshalb nur als Größenordnung** |
| Übertragungsnetzbetreiber | 4 (Amprion, 50Hertz, TenneT, TransnetBW) | ebd. |

**Die Nutzergruppe auf der anderen Seite des Antrags** (Planer, Errichter, Betreiber)
darf ZEREZ ausdrücklich ohne Registrierung einsehen. Ihre Größe habe ich aus dem
eigenen Repo übernommen: **9.219 Photovoltaikinstallateure** (Adressbestand Listflix,
Stand 27.08.2026, siehe `research/2026-08-28-pvsol-kauflizenz-abkuendigung.md` — als
Adressbestand gekennzeichnet, keine amtliche Marktzahl), davon 98,1 % Klein-, Kleinst-
oder Einzelbetriebe. Mengengerüst der Anträge: 863.000 PV-Anlagen mit 16,347 GW brutto
gingen 2025 in Betrieb (Marktstammdatenregister, zitiert nach pv-magazine 08.01.2026,
übernommen aus derselben Datei).

**Nicht ermittelbar:** wie viele Einheiten, Zertifikate, Hersteller und registrierte
Nutzer ZEREZ heute führt, und wie viele Netzbetreiber die API tatsächlich nutzen. Weder
FGW e.V. noch VKU, BDEW, BNetzA oder die Fachpresse nennen eine dieser Zahlen; die
Pressemitteilungen zum Registerbetrieb (01.02.2025, 17.04.2026, 01.06.2026) enthalten
keine einzige Mengenangabe. Nach der Regel aus meinem Logbuch ist das Fehlen nach zehn
Quellen der Befund, keine Suchlücke.

## 2. Wer es heute bedient

### 2a. Der Registerbetreiber selbst — und er darf gar nichts anderes tun

**ZEREZ wird von der FGW e.V. (Fördergesellschaft Windenergie und andere Dezentrale
Energien) betrieben**, im Auftrag und auf gesetzlicher Grundlage: § 49d EnWG, die
NELEV-Änderungsverordnung und die 2. NELEV-ÄndVO (VKU,
`vku.de/themen/infrastruktur-und-dienstleistungen/artikel/zerez/`, abgerufen 2026-08-29).

§ 49d EnWG legt drei Dinge fest, die für jede Produktidee auf diesem Baustein
entscheidend sind (`gesetze-im-internet.de/enwg_2005/__49d.html`, abgerufen 2026-08-29):

- Es ist „ein zentrales, über das Internet **öffentlich zugängliches** elektronisches
  Register".
- Der Betreiber ist „zu einer **diskriminierungsfreien Behandlung sämtlicher Nutzer und
  Nutzergruppen** des Registers verpflichtet".
- „Die **Erzielung von Gewinnen oder Überschüssen** durch den Betrieb des Registers **ist
  ihm untersagt**." Die Kosten erstatten die Übertragungsnetzbetreiber als
  Gesamtschuldner.

Entsprechend die FGW-FAQ (`shop.wind-fgw.de/zerez-faq/`, abgerufen 2026-08-29):
„**Nein — ZEREZ ist aufgrund der Vorgaben der Neuregelung durch die
NELEV-Änderungsverordnung kostenlos.** Es entstehen keine Gebühren für die Registrierung
und Nutzung der grundlegenden Funktionen des Registers." Und: „Nein — Eine Anmeldung ist
nicht erforderlich, um das Register einzusehen."

Damit ist die erste offene Frage des Signals beantwortet: **die API kostet nichts, und
sie darf auch künftig nichts kosten.**

Der Betreiber baut das Register außerdem selbst weiter aus, in Vier-Monats-Schritten:
API und Datenzugriffssteuerung am 17.04.2026 (die Belegstelle des Signals), und zum
**01.06.2026** die Aufnahme von Zertifikaten mit netzbildenden Eigenschaften für den
Momentanreservemarkt nach VDE-FNN-Hinweis Version 2.1 (Windkraft-Journal, 09.06.2026,
`windkraft-journal.de/2026/06/09/neuerung-zerez-erweitert-netzbildende-eigenschaften-fuer-den-momentanreservemarkt/224898`,
abgerufen 2026-08-29).

### 2b. Die Bundesnetzagentur zieht den Massenabruf gerade selbst ins MaStR

Das ist der Fund, der über den Einzelfall hinausgeht. Die BNetzA betreibt seit dem
10.10.2025 ein **Konzeptpapier „Verknüpfung MaStR und ZEREZ"**, dazu einen Branchendialog
mit Stellungnahmeverfahren und Workshop am **20.11.2025**
(`bundesnetzagentur.de/DE/Fachthemen/ElektrizitaetundGas/Monitoringberichte/Marktstammdatenregister/Branchendialog/artikel.html`,
abgerufen 2026-08-29; das Konzeptpapier selbst unter
`bundesnetzagentur.de/Konzeptpapier.pdf`). Die Behörde sieht in der Verknüpfung einen
„erheblichen Beitrag" zu ihren Zielen.

Inhaltlich, so weit belastbar: Die ZEREZ-IDs werden im MaStR als **Katalog** geführt und
**einmal täglich über einen von ZEREZ bereitgestellten Webdienst** abgerufen; nur diese
IDs sind bei der Registrierung verwendbar, womit ihre Gültigkeit schon bei der Eingabe
feststeht. Für Netzbetreiber ist eine **Massenbearbeitung über Webdienst und
Schnittstelle** vorgesehen.

**Warnung zur Belastbarkeit dieses Absatzes:** Beide BNetzA-PDFs (Konzeptpapier und
Branchendialog-Präsentation) sind für mich technisch nicht lesbar — sie liegen als
komprimierte Binärdaten vor, wie schon bei allen bisherigen Behörden-PDFs in diesem Repo.
Der Inhalt stammt daher aus Suchzusammenfassungen dieser Dokumente, nicht aus dem
Wortlaut. Eine in derselben Zusammenfassung genannte Zeitschiene („Inkrafttreten
01.04.2026, Umsetzung bis 01.10.2026") **verwende ich bewusst nicht**, weil ich sie nicht
gegenprüfen konnte. Der Umstand, dass die Verknüpfung betrieben wird, ist über die
HTML-Seite der BNetzA belegt; die Termine sind es nicht.

### 2c. Die Netzanschlussportale — der Kanal ist besetzt, und der BDEW führt Buch

Der BDEW betreibt eine **„Anbieterliste: Dienstleister für den Aufbau von
Netzanschlussportalen für Stromverteilnetzbetreiber"**
(`bdew.de/energie/anbieterliste-netzanschlussportal/`, Seite veröffentlicht 12.03.2026,
abgerufen 2026-08-29). Wörtlich: „Eine Aktualisierung der Liste erfolgt **wöchentlich**",
die Aufnahme steht allen Unternehmen offen, der BDEW prüft weder Dienstleister noch
Qualität. Ältere Fassungen unter `250311_` und `250820_` belegen, dass die Liste seit
mindestens März 2025 fortgeschrieben wird.

Aus der PDF-Fassung vom 12.03.2026 (`bdew.de/media/documents/260312_Anbieterliste_Netzanschlussportale.pdf`)
war die erste Seite lesbar. Sie nennt allein bis zum Buchstaben G **18 Anbieter**:
adesso, Asseco BERIT, atrios, BBH Solutions, BPC (NAP Suite), Bittner & Krull, BTC, CRP,
DEM, die netzwerkpartner (Netzanschluss-Portal), E.ON (ONE), ebsygon, einfachNETZ, eins
und null, epilot, ESN, GIS Consult, GIPS Projekt. Die Liste läuft danach weiter; der Rest
war nicht extrahierbar. Nach meinem Logbuch ist ein **Verzeichnis der Anbieter, geführt
vom Branchenverband und wöchentlich aktualisiert**, der stärkste Sättigungsindikator, den
es gibt (Indikator 13).

**Vier Anbieter haben die ZEREZ-Prüfung nachweislich fertig eingebaut:**

| Anbieter | Wortlaut zur ZEREZ-Anbindung | Preis | Quelle, abgerufen 2026-08-29 |
|---|---|---|---|
| **ebsygon GmbH** | „Das Netzanschlussportal ist direkt mit dem zentralen ZEREZ-Register verknüpft." / „Gültige Wechselrichter-Zertifikate werden **automatisch übernommen — ohne manuelles Hochladen**." / Funktionsliste: „Automatische Schnittstelle zu ZEREZ" | **9.900 EUR einmalig, 3.000 EUR/Jahr Betrieb** | `ebsygon.com/produkte/digitales-netzanschlussbegehren/` |
| **die netzwerkpartner** (Verbund von rund 140 Stadtwerken, seit 2000) | „Über eine Schnittstelle ruft das System die Zertifikatsdaten **mittels ZEREZ-ID live ab** und zeigt sie dem Installateur an." / „**Die Gültigkeit wird sofort geprüft**, so dass der Prüfaufwand und die Konsistenzprüfung zwischen hochgeladenem Zertifikat und den zugehörigen Daten für den Sachbearbeiter komplett entfällt." / Einheitenzertifikate E.4 und E.6 für Wechselrichter | einmalige Lizenz- und Implementierungskosten plus jährliche Wartung/Support/Hosting, Zahlen nur auf Anfrage; **„27 Partner nutzen bereits das Einspeiser-Portal"** (u. a. Regionetz, Bonn-Netz, Stadtwerke Düren) | `dienetzwerkpartner.com/website/einspeiser-portal` |
| **ITC AG** (PowerCommerce Netz) | „Für Erzeugungsanlagen lassen sich Register- und Nachweisinformationen prozessseitig berücksichtigen — z. B. ZEREZ (Zertifikate/IDs)"; Nennung der Pflicht ab 01.02.2025 | nicht veröffentlicht, nur Demo-Anfrage | `itc-ag.com/itc-powercommerce-netz.html` |
| **einfachNETZ** (Gemeinschaftsunternehmen TransnetBW + adesso, modulare SaaS-Plattform „von der Antragserfassung über die technische Prüfung bis zur finalen Herstellung des Anschlusses") | ZEREZ-Verknüpfung in der Suchzusammenfassung genannt, auf der Produktseite selbst **nicht gegenprüfbar** (JS-gerendert, Abruf liefert nur den Seitentitel) | Preis „individuell nach Zahl der Netzanschlusspunkte" | `adesso.de/de/news/blog/einfachnetz-...jsp` (09.02.2026), `einfachnetz.de/verteilnetzbetreiber` |

Ein fünfter, **GIPS (Hehner Reus Systems GmbH)**, verkauft ein Einspeiserportal ohne
ZEREZ-Bezug für **ab 5.900 EUR einmalig plus ab 100 EUR monatlich** (Hosting, Lizenzen,
Support inklusive) — `gipsprojekt.de/einspeiserportal`. Ein sechster, **CRP**, verkauft
ausschließlich die Anbindung solcher Portale an SAP, Schleupen, Wilken, SIV-kVASy und
Doxis (`crp.de/aktuelles/netzanschlussportal-effiziente-integration-fuer-eure-systeme`)
— es gibt also bereits einen Markt für die Schnittstelle *zwischen* den Systemen.

### 2d. Die Installateurseite ist ebenfalls besetzt — von vier Dienstleistern

- **Reonic** automatisiert die Netzanmeldung „von der technischen Vorprüfung bis zur
  Fertigmeldung und Zählerwechselterminierung" inklusive MaStR-Registrierung,
  Zeitersparnis laut Anbieter „bis zu 12 Stunden pro Projekt"
  (`reonic.com/de-de/blog/pv-wärmepumpe-netzanmeldung/`, Beitrag vom 01.12.2025).
  **ZEREZ wird dort nicht erwähnt.**
- **NetzPilot** (The CodeCave GmbH, Bielefeld) — „automatisiert die Netzanschlussmeldung
  für PV-Installateure", vollständiger Antrag binnen 24 Stunden, bis zu 20 Stunden
  Ersparnis bei 10 Anlagen im Monat. **Steht am 2026-08-29 ausdrücklich in der
  BETA-Phase mit limitierter Verfügbarkeit**, kein Preis (`netz-pilot.com`).
- **ZackZack Services** — Netzanmeldung und MaStR in einem Workflow, Festpreis
  (`zackzackservices.de`).
- **pv-anlagen-anmelden.de** — Netzanmeldung, MaStR-Registrierung, Zählerwechsel und
  Fertigmeldung zum **Festpreis 399 EUR bis 30 kWp** (369 EUR ab 10 Anlagen, 339 EUR ab
  20, 299 EUR ab 30), **593,81 EUR über 30 kWp**; Zielgruppe ausdrücklich auch
  „Installateure".

### 2e. Und die Hardwareseite verschenkt die Suche, wie in jedem hardwarenahen Markt

Großhändler und Hersteller erklären die ZEREZ-ID-Suche kostenlos und in vier Schritten:
Memodo („Du kannst ZEREZ ohne Anmeldung und Benutzerkonto kostenlos nutzen",
`memodo.de/m/zerez/`), BayWa r.e. Solar Distribution, Fronius (Zertifikate & Datenblätter
für Installateure), Solis (eigener Service-Center-Artikel „Wie finde ich unsere Solis
Wechselrichter in der Zerez Datenbank?"), dazu Wattkraft, Metergrid, cubos, ennergy,
energie-experten und ein englischsprachiger 33-Fragen-Ratgeber (xpert.digital). Der
Informationslayer ist damit vielfach auf null bepreist — dasselbe Muster wie bei BAYROL,
ExtraSauber, SMA und K2 Base in den vorangegangenen Läufen.

## 3. Was heute dafuer gezahlt wird

**Für das Register selbst: 0 EUR, und zwar von Gesetzes wegen** (§ 49d EnWG,
NELEV-ÄndVO; FGW-FAQ im Wortlaut oben). Die Kosten des Registerbetriebs tragen die
Übertragungsnetzbetreiber.

**Für die Software drumherum, auf der Netzbetreiberseite** — das ist die belegte
Zahlungsbereitschaft dieses Segments:

- ebsygon: **9.900 EUR einmalig + 3.000 EUR/Jahr**
- GIPS: **ab 5.900 EUR einmalig + ab 100 EUR/Monat** (= ab 1.200 EUR/Jahr)
- die netzwerkpartner, ITC, einfachNETZ, SPIE/Mettenmeier (am-suite.de): kein
  veröffentlichter Preis, teils erst nach Workshop oder Demo — nach meinem Logbuch der
  Normalfall bei deutscher Fachsoftware

**Der Nutzen, mit dem der Kanal wirbt:** „**200 € Ersparnis pro Einspeise-Antrag
möglich**" (die netzwerkpartner). Achtung bei der Verwendung dieser Zahl: Sie bezieht
sich auf den **gesamten** digitalisierten Antragsprozess, nicht auf die
ZEREZ-Zertifikatsprüfung allein. Wie viel davon auf den ZEREZ-Teil entfällt, sagt keine
Quelle.

**Auf der Installateurseite** wird die *ganze* Netzanmeldung als Dienstleistung gekauft:
**299–399 EUR je Anlage bis 30 kWp, 593,81 EUR darüber**. Das ist der einzige
öffentlich bepreiste Vorgang, in dem die ZEREZ-Prüfung überhaupt als Teilschritt
vorkommt — und der Preis gilt für alles außer ihr.

## 4. Die heutige Notloesung

**Für den Installateur: die freie Suche auf zerez.net, ohne Anmeldung.** Der Ablauf steht
bei Memodo in vier Schritten: zerez.net aufrufen, „Einheiten und Zertifikate" anklicken,
nach Komponente oder Hersteller suchen, „Kopierst du die Identifikationsnummer aus der
Spalte ‚ZEREZ ID'". Kosten: 0 EUR.

**Und darüber hinaus muss er gar nichts prüfen.** Nach der Verfahrenslogik trägt er nur
die ZEREZ-ID in den Netzanschlussantrag ein; **die Daten holt sich der Netzbetreiber**
(VKU: „Verteilnetzbetreiber können alle erforderlichen Werte und Parameter für die
Bearbeitung von Netzanschlussanfragen mühelos über ZEREZ abrufen"). Die im Signal
beschriebene „Massenprüfung" ist also gar keine Aufgabe der zahlenden Mehrheit
(9.219 Betriebe), sondern der 866 Netzbetreiber — und dort steckt sie in der
Antragsbearbeitung, die vier Anbieter bereits automatisiert verkaufen.

**Für den Netzbetreiber ohne Portal: manuelle Einzelabfrage über die Weboberfläche.**
Wie lange eine solche Abfrage dauert, nennt **keine** der 25 gesichteten Quellen — weder
FGW, VKU, BDEW noch einer der Portalanbieter. Nach der Regel aus meinem Logbuch („eine
Notlösung, die 20 Minuten im Monat kostet, wird nie ersetzt") fehlt damit genau die Zahl,
die die Dringlichkeit belegen müsste. Was sich sagen lässt: Es ist eine Suche nach einer
ID in einer Weboberfläche, einmal je Antrag.

**Der Schmerz, der in der Praxis tatsächlich auftritt, ist ein anderer und liegt beim
Hersteller:** fehlende oder falsch eingetragene Einträge. Einzelne Hersteller,
insbesondere von Mikrowechselrichtern, haben ihre Produkte noch nicht vollständig
registriert; ohne Eintrag darf die Anlage nicht in Betrieb gehen. Der einzige
Community-Thread, den ich dazu gefunden habe (Victron Community, „ZEREZ: neue
Zulassungsdatenbank", 12.–23.01.2025, **drei Beiträge**), beschreibt genau das: Victron-
Zertifikate standen fälschlich auf „abgelaufen", der Hersteller meldete elf Tage später
„Die Zertifikate sind jetzt alle als ‚gültig' markiert". Drei Beiträge, in elf Tagen vom
Hersteller erledigt — nach meinem Kommentarzahl-Test ist das kein Markt, sondern ein
Datenpflegevorgang beim Eintragspflichtigen.

## 5. Was dagegen spricht

Fünf Gründe. Der erste und der zweite sind strukturell und gelten für **jede** Idee auf
diesem Baustein, nicht nur für die vom Scout genannte.

**(1) Das Gesetz verbietet, dass hier ein bezahlter Zugang entsteht.** § 49d EnWG:
öffentlich zugängliches Register, **diskriminierungsfreie Behandlung sämtlicher Nutzer
und Nutzergruppen**, **Gewinnerzielung untersagt**, Kosten bei den
Übertragungsnetzbetreibern. Ein Dritter, dessen Wert im Zugang zu diesen Daten läge,
konkurriert gegen einen Betreiber, der gesetzlich verpflichtet ist, ihn gratis zu
gewähren — und der jede Zugangslücke, die er heute noch hat, aus derselben Verpflichtung
heraus selbst schließen muss. Das ist die härteste Form des Musters „Behörde stellt das
Formular", das in diesem Repo schon zehn Signale beendet hat: nicht Kulanz, sondern
Rechtspflicht.

**(2) Der Registerbetreiber liefert die Automatisierung selbst, und der Staat baut sie
gerade in ein zweites Register ein.** Die API ist die Belegstelle des Signals — sie
stammt vom Betreiber, nicht von einem Dritten. Vier Monate später kam die nächste
Erweiterung (netzbildende Eigenschaften, 01.06.2026). Parallel verknüpft die
Bundesnetzagentur MaStR und ZEREZ, ruft die ZEREZ-IDs täglich per Webdienst ab und stellt
den Netzbetreibern Massenbearbeitung über Webdienst und Schnittstelle bereit. Wer einen
Massenabgleich verkaufen will, verkauft gegen zwei Register, die sich gerade selbst
zusammenschalten.

**(3) Auf der Netzbetreiberseite bedienen mindestens vier deutsche Anbieter genau dieses
Segment mit genau dieser Aufgabe.** ebsygon („Gültige Wechselrichter-Zertifikate werden
automatisch übernommen — ohne manuelles Hochladen", 9.900 EUR + 3.000 EUR/Jahr), die
netzwerkpartner („ruft die Zertifikatsdaten mittels ZEREZ-ID live ab", „Die Gültigkeit
wird sofort geprüft", 27 Netzbetreiber im Einsatz), ITC AG und einfachNETZ. Das ist der
belegte Ausschlussgrund, den die Ampeldefinition für `rot` verlangt — kein „ähnliches
Werkzeug", sondern derselbe Kunde, dieselbe Aufgabe, dieselbe Schnittstelle. Darüber
liegt eine vom Branchenverband geführte, **wöchentlich** aktualisierte Anbieterliste mit
mindestens 18 weiteren Namen.

**(4) Die Aufgabe fällt beim Einzelnen zu selten an, um ein Abo zu tragen — und beim
Vielfachnutzer ist sie Teil eines Systems, das er schon hat.** Der Installateur braucht
die ID einmal je Anlage und findet sie in einer freien Suche, auf der Herstellerseite
oder beim Großhändler; er muss die Gültigkeit gar nicht prüfen. Der Netzbetreiber prüft
sie in Serie — aber innerhalb seiner Antragsbearbeitung, und die kauft er als
Portallösung, nicht als Einzelwerkzeug. Es gibt keine dritte Gruppe dazwischen.

**(5) Die kaufende Gruppe ist regulierte Infrastruktur mit Einkauf und
Lieferantenprüfung.** 866 Netzbetreiber, Portalpreise im vier- bis fünfstelligen Bereich,
Beschaffung über BDEW-Listen, Referenzkunden und Tagesworkshops (SPIE/Mettenmeier). Nach
der Lehre aus dem MiCAR- und dem ByDesign-Lauf ist ein solcher Kunde für einen
nebenberuflichen Einzelanbieter praktisch unerreichbar — unabhängig von der
Produktqualität.

**Ein sechster Punkt, schwächer, aber in dieselbe Richtung:** Es gibt keinen Aufschrei.
Kein Beschwerde-Thread mit nennenswerter Beteiligung, kein Berater mit
ZEREZ-Landingpage, kein „ZEREZ-Checker" von irgendjemandem — ich habe deutsch und
englisch gesucht, auch absichtlich schlecht formuliert („ZEREZ Tool Checker kostenlos
Zertifikat prüfen Wechselrichter Liste Solarteur App"). Gefunden habe ich ausschließlich
Ratgeber, Herstellerhinweise und die Portalanbieter. Wo kein Dritter das Problem bewirbt,
war keines.

## Was das Signal wert bleibt

Drei Dinge, die ein späterer Lauf verwenden kann:

- **Die Preisdecke der Netzbetreiber-Portalsoftware ist jetzt dokumentiert:** 5.900 bis
  9.900 EUR einmalig, 1.200 bis 3.000 EUR im Jahr, dazu 200 EUR behaupteter Nutzen je
  Antrag. Wer je etwas für Stromnetzbetreiber rechnet, hat hier die Größenordnung.
- **Die Preisdecke der Installateurseite ebenfalls:** 299–399 EUR je Netzanmeldung bis
  30 kWp als vollständige Dienstleistung, mit Mengenrabatt ab zehn Anlagen.
- **Ein neuer, sehr billiger Anbieter-Sättigungstest für alles Energiewirtschaftliche:**
  der BDEW führt öffentliche, wöchentlich aktualisierte Anbieterlisten je Aufgabe —
  Netzanschlussportale, Redispatch-2.0-Dienstleister, Power-Quality-Monitoring. Ein
  Abruf von `bdew.de/energie/anbieterliste-<thema>/` erledigt Frage 2 vollständig.

## Offen geblieben

- **Ob die API heute wirklich allen registrierten Nutzern offensteht.** Hier
  widersprechen sich zwei Quellen desselben Hauses, beide am 2026-08-29 direkt abgerufen:
  Die Pressemitteilung vom 17.04.2026 sagt, die Schnittstelle stehe „allen registrierten
  Nutzerinnen und Nutzern" zur Verfügung; die FGW-FAQ sagt „Ja, es gibt eine digitale
  Schnittstelle zum ZEREZ. **Aktuell ist diese nur für Netzbetreiber verfügbar.**" Die FAQ
  trägt kein Datum. Welche der beiden gilt, ist ohne Registrierung nicht klärbar. **Beide
  Lesarten sprechen gegen die Idee**, nur mit verschiedenen Begründungen: Gilt die FAQ,
  ist ein Dritter vom Zugang ausgeschlossen; gilt die Pressemitteilung, hat jeder
  Netzbetreiber den Zugang selbst und braucht niemanden dafür.
- **Rate Limits und der Umfang der freigegebenen Daten.** Die zweite und dritte offene
  Frage des Signals bleiben offen. Keine Quelle nennt Mengenbegrenzungen. Zum Umfang gibt
  es einen wichtigen Hinweis: Hersteller mit der Rolle „Datenzugriffsverwalter" geben
  Einheitenparameter und Dokumente **gezielt für einzelne Nutzer oder Nutzergruppen
  frei** und können die Freigabe wieder entziehen. Ein Dritter sähe über die API also
  nicht das Register, sondern nur das, was Hersteller ihm einzeln freigegeben haben — für
  ein Produkt, das Vollständigkeit verspricht, ist das ein struktureller Riegel. Belegt
  ist die Freigabemechanik, nicht ihre Wirkung auf einen Nicht-Netzbetreiber.
- **Die Termine der MaStR-ZEREZ-Verknüpfung.** Konzeptpapier und
  Branchendialog-Präsentation der BNetzA sind PDF und für mich nicht lesbar (dritter
  Behörden-PDF-Fehlschlag in Folge). Dass die Verknüpfung läuft, ist über die HTML-Seite
  belegt; ab wann sie greift, nicht. Eine kursierende Zeitschiene („01.04.2026 /
  01.10.2026") habe ich bewusst nicht übernommen.
- **Jede Mengenangabe zum Register.** Einträge, Zertifikate, Hersteller, registrierte
  Nutzer, API-Nutzer: keine Zahl in keiner Quelle. Auf eine solche Zahl darf sich niemand
  berufen.
- **Der Zeitaufwand einer manuellen ZEREZ-Abfrage.** Nicht beziffert, von niemandem. Das
  ist die einzige Zahl, die die Ampel theoretisch bewegen könnte — sie müsste allerdings
  absurd hoch ausfallen, um die Gründe (1) bis (5) aufzuwiegen, und sie beträfe eine
  Aufgabe, die vier Anbieter bereits verkaufen.
- **Nicht geprüft:** ob es jenseits von PV und Wind eine Nutzergruppe des Registers gibt,
  die niemand bedient (Zertifizierungsstellen, Anlagenzertifizierer nach VDE-AR-N 4110,
  Sachverständige). Diese Recherche folgt dem Signal und betrachtet den
  Netzanschlussprozess für dezentrale Erzeugungsanlagen.
