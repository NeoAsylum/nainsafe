---
typ: recherche
signal: signals/tech/2026-08-28-ozg-schnittstelle-gewerbeanmeldung.md
erstellt: 2026-08-28
segmentgroesse: 762.400 Gewerbeanmeldungen/Jahr (2025); rund 11.000 kommunale Gewerbeaemter
anbieter_gefunden: 16
preisspanne: 0 EUR (staatlich und mehrere private Angebote kostenlos) bis 487 EUR netto einmalig
ampel: rot
---

# Seit dem 4. Februar 2026 laeuft die Gewerbeanmeldung bundesweit ueber eine zentrale OZG-Schnittstelle auf Basis des WSP.NRW — die zugrunde liegende XGewerbe-Uebermittlung ist jedoch behoerdenintern und fuer Dritt-Software nicht zugaenglich.

## Vorbemerkung: die Kernfrage des Signals ist beantwortet

Das Signal liess offen, ob es sich um „eine maschinell ansprechbare API für Dritt-Software"
oder „nur um ein buergerorientiertes Webformular" handelt. Antwort: **es ist ein
Webformular vorne und ein behoerdeninterner Uebermittlungsstandard hinten.** Belege in
Abschnitt 5. Diese Annahme muss nicht mehr getragen werden.

## 1. Groesse des Segments

Zwei getrennte Segmente haengen an diesem Baustein.

**Gruender (Sender der Anzeige):**

| Kennzahl 2025 | Zahl |
|---|---|
| Gewerbeanmeldungen gesamt | rund 762.400 (+6,4 % ggue. 2024) |
| davon Neugruendungen von Gewerben | rund 640.500 (+7,7 %) |
| davon Neugruendungen „groesserer Betriebe" | rund 130.100 |
| Gewerbeabmeldungen gesamt | rund 612.900 (−1,0 %) |

Quelle: Statistisches Bundesamt, Pressemitteilung Nr. 074 vom 06.03.2026,
<https://www.destatis.de/DE/Presse/Pressemitteilungen/2026/03/PD26_074_52311.html>,
abgerufen 2026-08-28.

Der Rest zu 762.400 sind Betriebsuebernahmen, Umwandlungen und Zuzuege aus anderen
Meldebezirken — also keine Erstgruender.

Zur Rechtsform: „Mehr als 80 Prozent aller Unternehmensneugruendungen in Deutschland"
entfallen auf Einzelunternehmen. Quelle: Finanzverwaltung NRW, Pressemitteilung zur
Pilotphase „Schneller Gruenden",
<https://www.finanzverwaltung.nrw.de/uebersicht-rubrik-aktuelles-und-presse/pressemitteilungen/nordrhein-westfalen-startet-pilotphase>,
abgerufen 2026-08-28.

**Gewerbeaemter (Empfaenger):** rund 11.000 kommunale Gewerbeaemter (ad-hoc-news.de, 2026-02,
abgerufen 2026-08-28; identisch mit der Zahl im Signal).

## 2. Wer es heute bedient

**Staatlich, kostenlos — und genau auf diesem Baustein aufsetzend:**

- **WSP.NRW / Wirtschafts-Service-Portal.NRW**, Betreiber Land NRW, seit 2026-02-04
  bundesweit als EfA-Dienst. „Die zentrale Plattform in NRW, um ueber 80 Online-Dienste
  fuer Gewerbetreibende [...] digital abzuwickeln."
  <https://service.wirtschaft.nrw/de/wirtschafts-service-portal/>, abgerufen 2026-08-28.
- **Landesportale** mit eigenem Gewerbemeldeverfahren: service-bw (BW), BayernPortal,
  Amt24 (SN), ThAVEL (TH), Berlin.de, Hamburg. In NRW, Berlin, Hamburg und Bayern ist die
  elektronische Anmeldung laut Recherche bereits seit laengerem Standard.
- **Gruenderplattform** — Gemeinschaftsprojekt von **KfW**, BusinessPilot und Everest.
  Kombiniert Gewerbeanmeldung und steuerliche Erfassung in einer App: „Deine Angaben
  werden automatisch ueber die ELSTER-Schnittstelle ans Finanzamt uebermittelt und – je
  nach Bundesland – auch an das zustaendige Gewerbeamt." In Berlin seit Oktober 2025
  vollstaendig digital. <https://gruenderplattform.de/blog/digitale-gewerbeanmeldung-berlin>,
  abgerufen 2026-08-28. Nutzung kostenlos (Preis auf der Seite nicht genannt, KfW-finanziert).

**Privat, kostenlos (Leadgenerierung fuer Buchhaltung/Banking):**

- **Lexware**, „Steuerlicher Erfassungsbogen", kostenloser Service mit direkter
  ELSTER-Uebermittlung, <https://www.steuerlicher-erfassungsbogen.de/>, abgerufen 2026-08-28.
- **sevdesk**, **Qonto**, **Finom**, **Taxfix**, **Norman Finance** — Ratgeber und
  Ausfuellhilfen als Content-Marketing, ohne eigene Gebuehr.

**Privat, kostenpflichtig:**

- **firma.de**, Paket „Classic" **399 EUR netto** einmalig (enthaelt „Preparation of your
  trade registration (Gewerbeanmeldung)" und „Timely preparation of your tax office
  questionnaire"), Paket „All-In" **487 EUR netto** (zusaetzlich Buchhaltungseinrichtung,
  88 EUR Anteil). <https://www.firma.de/en/soleproprietorship-set-up/>, abgerufen 2026-08-28.
- **beglaubigt.de** — API-Gruendung, aber ausdruecklich nur „Gruendungen von GmbHs und UGs
  per API"; Einzelunternehmen und Gewerbeanmeldung sind nicht enthalten. Zielkunden:
  „Plattformbetreiber, Kanzleien, Banken, Company Builder und SaaS-Anbieter". Kein Preis
  veroeffentlicht, Early-Access-Liste.
  <https://beglaubigt.de/blog/pressemitteilung-digitale-gruendung-per-api>, abgerufen 2026-08-28.

**Empfaengerseite (kommunale Fachverfahren) — besetzter Markt:**

AKDB **OK.GEWERBE**, **VOIS|GESO**, EDV Ermtraud **geve|5 / geve|Online** (inkl. eigenem
„Erweitertem OSCI/DVDV-Transportmodul"), DZBW **KM-Gewerbe**, **HSH**, **MoKomm**.
Quellen: <https://www.akdb.de/loesungen/okbuergerservice/okgewerbe/>,
<https://edv-ermtraud.de/produkte/gewerbeverwaltung-online-webmodule/geve-online/>,
<https://www.mokomm.de/xgewerbeordnung/>, alle abgerufen 2026-08-28. Preise nicht oeffentlich.

**Datenseite (Verwertung der Anmeldungen):**

**Address-Base** und **Address Publisher** verkaufen Neugruender-Adressen. Address-Base:
„bis 1.000 Stueck 0,35 €", „ab 1.000 Stueck 0,30 €", „ab 5.000 Stueck 0,26 €",
„ab 10.000 Stueck 0,20 €"; Angabe der Grundgesamtheit: „In Deutschland gibt es ueber
10.000 Neugruendungen pro Monat."
<https://www.address-base.de/Adressen-von-Neugruendungen:_:905.html>, abgerufen 2026-08-28.

## 3. Was heute dafuer gezahlt wird

| Position | Betrag | Quelle (alle abgerufen 2026-08-28) |
|---|---|---|
| Amtsgebuehr Gewerbeanmeldung | 15–65 EUR, kommunal festgelegt | gewerbeanmeldung.de, firma.de |
| Berlin online / Papier | 15 EUR / 26 EUR | berlin.de FAQ |
| Hamburg / Muenchen / Stuttgart | 20 / 47 / 54 EUR | gewerbeanmeldung.de |
| Gruendungsservice Einzelunternehmen | 399–487 EUR netto einmalig | firma.de |
| Neugruender-Adressdatensatz | 0,20–0,35 EUR | Address-Base |
| Fragebogen steuerliche Erfassung | 0 EUR (Lexware, Gruenderplattform, ELSTER) | steuerlicher-erfassungsbogen.de |

Zahlungsbereitschaft existiert also, aber sie sitzt fast vollstaendig in der Amtsgebuehr
(15–65 EUR, geht an die Kommune) und in einem einzigen erkennbaren Premiumsegment
(firma.de, 399 EUR netto — dort aber gebuendelt mit persoenlichem Berater und
Telefonsupport, beides fuer diese Fabrik nach G3 ausgeschlossen).

Gegenlaeufig und wichtig: Behoerden und Ratgeberportale **warnen aktiv** vor
kostenpflichtigen Dritten in genau diesem Vorgang. „Diese Angebote sind keine staatlichen
Stellen, sondern kostenpflichtige Dienstleister, die haeufig deutlich ueberhoehte Gebuehren
fuer Leistungen verlangen. In vielen Faellen beschraenkt sich der Service darauf, das
Anmeldeformular auszufuellen und an das Gewerbeamt weiterzuleiten." (gewerbeanmeldung.de,
abgerufen 2026-08-28)

## 4. Die heutige Notloesung

Der Gruender fuellt zwei Formulare getrennt aus: die Gewerbeanzeige (Landesportal, seit
2026-02-04 alternativ WSP.NRW, oder Papier am Amt) und danach den Fragebogen zur
steuerlichen Erfassung, der seit dem 01.01.2021 elektronisch ueber ELSTER abzugeben ist
(Frist: ein Monat). Die Notloesung ist also **doppelte Dateneingabe** in zwei Systemen.

Kosten der Notloesung: 15–65 EUR Amtsgebuehr plus geschaetzt ein bis zwei Stunden
Eigenarbeit — **Schaetzung, keine Quelle.** Entscheidend ist nicht die Hoehe, sondern die
Frequenz: Es ist ein **Einmalvorgang pro Gruender**. Es gibt keinen wiederkehrenden
Schmerz, den man abonnieren koennte.

Und genau diese Notloesung wird gerade staatlich abgeschafft, siehe 5c.

## 5. Was dagegen spricht

**a) Der XGewerbe-Standard ist keine offene API. Er ist behoerdenintern — nachweislich.**

Der Standard regelt ausschliesslich die Weiterleitung *nach* der Anzeige, vom Gewerbeamt
an die nach § 14 Abs. 8 GewO empfangsberechtigten Stellen (IHK, Handwerkskammer, Finanzamt,
Statistisches Landesamt, DGUV, Immissionsschutz, Registergericht u. a.).
<https://xgewerbeordnung.de/der-standard> und
<https://www.gesetze-im-internet.de/gewo/__14.html>, abgerufen 2026-08-28.

Der Transport laeuft ueber OSCI-Transport mit Adressierung ueber das **DVDV** (Deutsches
Verwaltungsdiensteverzeichnis): „Empfaenger elektronischer Gewerbemeldungen muessen einen
entsprechenden Dienst anbieten und im DVDV eingetragen sein; Sender greifen lesend auf das
DVDV zu." (DVDV-Eintragskonzept XGewerbeanzeige, xrepository.de, abgerufen 2026-08-28)

Und das DVDV ist ein **nicht-oeffentlicher Verzeichnisdienst, dessen Nutzung auf Stellen
der oeffentlichen Verwaltung beschraenkt ist** (ITZBund,
<https://www.itzbund.de/DE/itloesungen/standardloesungen/dvdv/dvdv.html>, abgerufen
2026-08-28). Ein privates Nebengewerbe kann hier weder Sender noch Empfaenger sein.

**b) Der einzige offene Pfad — FIT-Connect — traegt fuer diesen Fall nicht.**

FIT-Connect (FITKO) ist grundsaetzlich auch Privaten zugaenglich und kostenlos: „Die
Registrierung von Verwaltungssystemen und Onlinediensten sowie die Nutzung von FIT-Connect
als technische Infrastrukturkomponente sind daher kostenlos." Ein Onlinedienst (Sender) ist
definiert als „das technische System, das eine Einreichung ueber die Submission API vornimmt
(z. B. ein Online-Antragsservice oder Unternehmensystem)"; eine Beschraenkung auf Behoerden
steht nicht in den Nutzungsbedingungen. <https://docs.fitko.de/fit-connect/docs/faq/> und
<https://docs.fitko.de/fit-connect/docs/details/terms-of-use-prod/>, abgerufen 2026-08-28.

Aber: Senden setzt einen **Zustellpunkt** voraus, den die empfangende Behoerde betreibt, und
die Berechtigung wird ueber OAuth-Scopes je Zustellpunkt vergeben — der offene Scope
`send:region:DE` gilt ausdruecklich nur in der Testumgebung
(<https://docs.fitko.de/fit-connect/docs/getting-started/account/>, abgerufen 2026-08-28).
Fuer 11.000 Gewerbeaemter einzeln Zustellpunkte und Freigaben zu beschaffen, ist bei zwei
Stunden pro Woche kein gangbarer Weg. Einen dokumentierten FIT-Connect-Zustellpunkt fuer
Gewerbeanzeigen habe ich nicht gefunden (siehe „Offen geblieben").

**c) Der Staat baut die einzige verbliebene Luecke gerade selbst — kostenlos und in diesem Jahr.**

Die Luecke „zwei Formulare statt einem" wird geschlossen:

- **Ab 01.06.2026**: Pilot „Schneller Gruenden" in Mannheim und acht weiteren Staedten —
  „Gewerbeanmeldung und steuerliche Registrierung erstmals in einem digitalen Antrag";
  Traeger sind das **Bundesministerium fuer Digitales und Staatsmodernisierung** und der
  **DigitalService des Bundes**.
  <https://www.it-boltwise.de/schneller-gruenden-neun-staedte-starten-digitales-portal-fuer-gewerbe-und-steuern.html>,
  abgerufen 2026-08-28.
- **Ab Juli 2026**: NRW-Pilotphase Kombiantrag am Finanzamt Aachen-Stadt und allen
  Duesseldorfer Finanzaemtern. Wirtschaftsministerin Neubaur: „Der neue Kombiantrag macht
  aus zwei Antraegen einen und vereinfacht die steuerliche Registrierung deutlich."
  (Finanzverwaltung NRW, abgerufen 2026-08-28)
- Bereits heute kostenlos verfuegbar: Gruenderplattform (KfW) mit ELSTER-Anbindung und
  kombiniertem Fragebogen, Lexware mit direkter ELSTER-Uebermittlung.

**d) Einmalvorgang ohne Wiederkehr.** 762.400 Anmeldungen pro Jahr klingen gross, sind aber
762.400 einmalige Transaktionen. Kein Bestandsgeschaeft, keine Abo-Basis; jeder Verkauf muss
neu bezahlt werden — gegen firma.de, Qonto, Finom und ein KfW-finanziertes Gratisangebot,
die alle im selben Suchergebnis stehen.

**e) Reputationslage.** Der Vorgang ist bereits mit dem Ruf des unserioesen Zwischenhaendlers
belastet (Zitat in Abschnitt 3). Ein neues kostenpflichtiges Angebot startet gegen eine
aktive, behoerdlich unterstuetzte Warnung.

**f) Naehe zu G5.** Der werthaltige Teil ist nicht das Weiterleiten, sondern das Ausfuellen
des Fragebogens zur steuerlichen Erfassung: Kleinunternehmerregelung ja/nein,
Gewinnschaetzung, Ist- oder Soll-Versteuerung. Das sind Einzelfallwertungen im Sinne des
StBerG. Nur ein Werkzeug, das rein informiert und die Entscheidung dem Nutzer laesst, bliebe
diesseits der Grenze — und ist damit funktionsgleich mit dem, was Lexware und die
Gruenderplattform bereits gratis anbieten.

**g) Empfaengerseite ist oeffentliches Vergabegeschaeft.** AKDB, VOIS, EDV Ermtraud und DZBW
bedienen die 11.000 Gewerbeaemter seit Jahren; Marktzugang laeuft ueber kommunale Vergabe.

## Offen geblieben

- **Wie viele Kommunen tatsaechlich angebunden sind.** Keine Zahl gefunden. Die
  Nachnutzungs-Neuigkeitenseite des WSP.NRW
  (`service.wirtschaft.nrw/hilfe/efa/nachnutzung/neuigkeiten/`) liefert am 2026-08-28
  **HTTP 404**. Die Aussage „bundesweit" ist damit belegt als Angebot, nicht als Abdeckung.
- **Die im Signal genannte Pflicht „ab 2028" liess sich nicht belegen.** Weder die GewAnzV
  (<https://www.gesetze-im-internet.de/gewanzv_2014/>) noch die gesichteten
  Pressemitteilungen nennen diese Frist; die WebFetch-Pruefung des ad-hoc-news-Artikels
  ergab ausdruecklich „keine Informationen ueber ein Verpflichtungsdatum". **Der Ideator
  darf sich auf 2028 nicht verlassen.**
- **Ob es einen FIT-Connect-Zustellpunkt fuer Gewerbeanzeigen gibt** und unter welchen
  Bedingungen eine Behoerde einen privaten Sender freigeben wuerde. Die
  Governance-Dokumentation dazu war nicht auffindbar; die technische Doku beschreibt nur
  die Scope-Mechanik.
- **Preise der kommunalen Fachverfahren** (OK.GEWERBE, geve|5, VOIS|GESO, KM-Gewerbe) sind
  nicht oeffentlich. Die Groesse des Empfaengermarktes ist damit nicht bezifferbar.
- **Die acht weiteren Staedte** des Pilots „Schneller Gruenden" werden in der gesichteten
  Quelle nicht genannt — nur Mannheim.
- **Umsatz- oder Kundenzahlen** von firma.de, Gruenderplattform oder den Adressanbietern:
  keine gefunden. Die Preise stehen, die Mengen nicht.
- **Eine Zahl aus dem Ausgangsartikel ist unbelegt:** ad-hoc-news.de behauptet, typische
  Fehler bei ELSTER-Angaben kosteten „durchschnittlich 2.400 Euro im ersten Jahr". Weder
  Methode noch Primaerquelle genannt; die Seite ist ein Nachrichtenaggregator. **Nicht
  verwenden.**
