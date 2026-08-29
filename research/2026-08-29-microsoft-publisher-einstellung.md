---
typ: recherche
signal: signals/market/2026-08-29-microsoft-publisher-einstellung.md
erstellt: 2026-08-29
segmentgroesse: nicht ermittelbar (weder Microsoft noch Fachpresse noch Verbaende nennen eine Zahl fuer Publisher-Nutzer in Deutschland; Microsoft begruendet die Einstellung selbst mit "zu geringer Nutzung", ohne Zahl)
anbieter_gefunden: 16 namentlich (1 Hersteller mit kostenlosem Massenkonvertierungs-Skript, 5 kostenlose Werkzeuge, 4 kostenpflichtige Konverter, 1 deutscher Dienstleister mit Festpreis fuer genau die Kernzielgruppe, 5 deutschsprachige Ratgeber-/Lizenzanbieter)
preisspanne: 0,00 EUR (Microsoft-Skript, LibreOffice Draw, Scribus, Affinity, Canva Gratis) bis 200,00 EUR je Dokument (GemeindebriefDruckerei, bis 12 Seiten); dazwischen 39,00 USD einmalig (Univik) und 12,00 EUR/Monat (Canva Pro)
ampel: rot
---

# Microsoft entzieht M365-Abonnenten am 01.10.2026 den Publisher — aber der Hersteller
# liefert das Massenkonvertierungs-Skript selbst und kostenlos, drei freie Programme
# lesen `.pub` ohne Publisher, und die Kernzielgruppe hat in Deutschland bereits einen
# Dienstleister mit Festpreis

**Die im Signal offen gelassene Frage lautete: „ob die betroffene Gruppe eher eine
Migrationshilfe braucht (Massenkonvertierung bestehender .pub-Dateien) statt eines neuen
Layout-Werkzeugs selbst." Die Antwort ist belegt und negativ.** Genau diese
Massenkonvertierung stellt Microsoft auf derselben Support-Seite bereit, die das Signal
zitiert: *„The sample PowerShell script can be used as a reference for how to individually
or bulk export Publisher files to PDF or other export formats"*
(`support.microsoft.com/en-us/publisher/microsoft-publisher-will-no-longer-be-supported-after-october-2026`,
abgerufen 2026-08-29). Dasselbe Skript existiert daneben frei auf GitHub
(`github.com/garethjmsaunders/batch-convert-publisher-to-pdf`, abgerufen 2026-08-29):
Wurzelordner waehlen, alle Unterordner nach `.pub` durchsuchen, jede Datei oeffnen,
als PDF danebenlegen.

**Zwei Zeitpunkte, die den ganzen Fall entscheiden.** Das Hersteller-Skript setzt eine
laufende Publisher-Installation voraus — es taugt also nur *vor* dem 01.10.2026. Genau
das ist auch die einzige Restnische, die dieses Signal traegt: Konvertierung *nach* dem
Stichtag, ohne Publisher. Sie ist besetzt (Abschnitt 2), teils zum Preis null, und der
Stichtag liegt **33 Tage** entfernt.

## 1. Groesse des Segments

**Nicht ermittelbar, und diesmal ist das kein Rechercheluecken-Befund, sondern die
Aussage des Herstellers selbst.**

Microsoft begruendet die Einstellung damit, *„regelmaessig zu ueberpruefen, welche
Funktionen seiner Produkte Abonnenten verwenden und wie haeufig dies geschehe"* —
Publisher werde *„immer weniger genutzt"*, es gebe *„stetig rueckläufige Nutzerzahlen"*
(ComputerBase, 10.08.2026,
`computerbase.de/news/apps/zu-geringe-nutzung-microsoft-stellt-publisher-zum-1-oktober-2026-ein.98779/`,
abgerufen 2026-08-29). Eine Zahl nennt Microsoft nicht, und keine der geprueften
deutschsprachigen Quellen (ComputerBase, windowsarea.de, ghacks.de, boerse-express)
nennt eine. Die englischsprachigen Meldungen sprechen von *„hundreds of thousands"*
bzw. „Millionen" weltweit — beides ohne Grundlage und ohne Deutschlandbezug.

**Was sich statt einer Zahl belegen laesst, sind drei Obergrenzen:**

1. **Nur Windows.** Microsofts eigene Produktseite:
   *„Microsoft Publisher ist nur fuer den PC verfuegbar"*
   (`microsoft.com/de-de/microsoft-365/publisher`, abgerufen 2026-08-29). Kein Mac,
   keine Web-Version, keine mobile App.
2. **Nur in den teureren Plaenen.** Publisher war nie in Business Basic oder in den
   Web-Only-Plaenen enthalten.
3. **Die Einstellung erfolgt wegen Nichtnutzung.** Ein Hersteller entfernt keine
   Funktion, deren Nutzung er messen kann und die genutzt wird.

**Der Ideator darf hier keine Segmentzahl ansetzen — es gibt keine, auch keine
widerspruechliche.** Nach der Regel aus dem Rollenauftrag („ein Markt, den niemand
zaehlt, ist meist keiner") ist bereits das ein Befund; hier verschaerft ihn, dass der
Einzige, der zaehlen *kann*, das Ergebnis als Einstellungsgrund nennt.

## 2. Wer es heute bedient

**Dicht besetzt, in fuenf Schichten. Gesucht deutsch und englisch, ueber Produkt-,
Migrations-, Konverter-, Alternativ- und Laienformulierungen. Jede Suche brachte neue
Namen, keine brachte eine Luecke.**

**Schicht 1 — Microsoft selbst, mit Werkzeug und Ersatzprodukten.** Das
PowerShell-Beispielskript zur Einzel- und Massenkonvertierung (siehe oben); die
Empfehlung *„Convert existing Publisher files to PDF or Word format before October 1,
2026"*; und als Ersatz Word (Newsletter, Umschlaege, Etiketten, Visitenkarten, Kalender),
PowerPoint (Poster, Banner, Broschueren) sowie **Microsoft Designer** als KI-gestuetztes
Vorlagenwerkzeug (Support-Seite und ComputerBase, beide abgerufen 2026-08-29).

**Schicht 2 — freie Programme, die `.pub` ohne Publisher lesen (3 namentlich).**
**LibreOffice Draw** oeffnet `.pub` ueber die Open-Source-Bibliothek **libmspub**
(`cgit.freedesktop.org/libreoffice/libmspub`, abgerufen 2026-08-29), ebenso **Scribus**;
dazu **PublishMedia**. Alle drei exportieren nach PDF. Kosten: null.

**Schicht 3 — kostenpflichtige Konverter (4 namentlich).**
- **Univik PUB Converter** (Univik Inc., Collingwood/Ontario und Delhi): *„$39"* als
  *„One-Time Licence"* mit *„unlimited conversions"*, ausdruecklich *„No subscription,
  no recurring fee"*, Stapelverarbeitung von *„hundreds of PUB files"* mit
  *„roughly 1,500 files per hour"*, auch per Kommandozeile, Ausgabe nach PDF, Word, JPG,
  PNG, TIFF — **ohne installierten Publisher**
  (`univik.com/file/converter/pub.html`, abgerufen 2026-08-29).
- **Markzware** mit drei Produkten: **MarkzPortal** (browserbasiert, `.pub` → IDML fuer
  InDesign, Affinity, QuarkXPress), **DesignMarkz** (*„Microsoft Publisher-Dateien in
  bearbeitbare Canva-Designs konvertieren"*) und **OmniMarkz/OmniMarkz SE** (Desktop,
  macOS/Windows, mit Dateiinventar). Preise nennt Markzware oeffentlich nicht, nur
  Shop und Kontakt (`de.markzware.com/workflow-tips/...`, abgerufen 2026-08-29).
- **freepdfconvert.com** mit einem Cloud-Konverter, der *„even if you have never had
  Publisher installed"* arbeitet.
- **online-umwandeln.de** als deutschsprachiger Online-Konverter fuer das PUB-Format.

**Schicht 4 — und dies ist der schaerfste Befund: Die im Signal genannte Kernzielgruppe
hat in Deutschland bereits einen Dienstleister mit veroeffentlichtem Festpreis.**
Die **GemeindebriefDruckerei** (Druckerei fuer Gemeindebriefe, also genau die
Kirchengemeinden, Vereine und Ehrenamtlichen des Signals) betreibt eine Hilfeseite zur
Publisher-Ablösung, empfiehlt Affinity Publisher als Nachfolger, liefert Anleitung und
Vorlagen — und bietet die Umstellung als Auftrag an: *„Wir uebernehmen die technische
Arbeit fuer Sie"*, **„Kosten: 200 € fuer bis zu 12 Seiten. Jede weitere 12 Seiten:
+ 45 €"**, Lieferzeit bis zu vier Wochen
(`helfer.gemeindebriefdruckerei.de/microsoft-publisher-pdf-in-affinity-publisher-oeffnen/`
und `/fragen/publisher-datei-uebertragen-zu-affinity-publisher/`, abgerufen 2026-08-29).

**Schicht 5 — deutschsprachige Ratgeber, Systemhaeuser und Lizenzhaendler mit fertiger
Seite zu genau diesem Stichtag (5 namentlich):** Ulrich B. Boddenberg IT-Consultancy
(sechsstufiger Migrationsleitfaden, veroeffentlicht 22.12.2025, kostenlos,
`boddenberg.de`), Lizenzsofort (*„Microsoft Publisher eingestellt: Alternativen 2026"*,
30.06.2026), directlicenz (*„Microsoft Publisher endet 2026: Was sind die
Alternativen?"*), teamsoft.de (Publisher fuer Schulen und Bildung), tecnoloblog.de
(Alternativen-Leitfaden). Alle abgerufen bzw. ueber Suchtreffer belegt 2026-08-29.
Dazu die Fachpresse mit Anleitungen: ghacks.de (25.06.2026, *„PUB-Dateien jetzt
sichern"*), windowslatest (11.02.2026), windowsarea.de (04/2026).

**Der Saettigungsindikator aus dem Logbuch trifft zu:** Die Beratungsleistung wird
verschenkt. Boddenberg, die Fachpresse und die Lizenzhaendler liefern den vollstaendigen
Migrationsleitfaden gratis; Microsoft liefert das Werkzeug gratis dazu.

## 3. Was heute dafuer gezahlt wird

**Fuer das Layoutwerkzeug selbst: nichts Zusaetzliches, und kuenftig noch weniger.**
Publisher war im Abonnement enthalten; niemand hat je separat dafuer gezahlt. Der
naheliegende Nachfolger ist heute **kostenlos**: Canva hat Affinity (Designer, Photo,
Publisher, frueher zusammen ueber 250 EUR) im **Oktober/November 2025** in die neue App
**Affinity Studio** ueberfuehrt und dauerhaft gratis gestellt — *„Free forever"*,
Kerndesignfunktionen vollstaendig freigeschaltet, nur die KI-Funktionen jenseits eines
Grundmasses erfordern ein Canva-Abo (Canva-Newsroom *„Why we made Affinity free, and how
we'll keep it that way"* — Direktabruf 403; belegt ueber borncity.com vom 06.11.2025 und
clickomania.ch vom 13.11.2025, beide abgerufen 2026-08-29, als Fachpresse gekennzeichnet).

**Was tatsaechlich fliesst, sind drei Betraege:**

| Posten | Preis | Quelle (abgerufen 2026-08-29) |
|---|---|---|
| Canva Gratis (Vorlagen, 5 GB Speicher) | **0,00 €** | giga.de, finom.co |
| Canva Pro | **12,00 €/Monat** bzw. 110,00 €/Jahr | giga.de, danielgaiswinkler.com |
| Canva Pro fuer gemeinnuetzige Vereine | **0,00 €** (Antrag ueber Goodstack, Freistellungsbescheid + Vereinsregisterauszug) | canva.com/nonprofits ueber dealdoktor.de, mein-deal.com |
| Univik PUB Converter, Stapelbetrieb ohne Publisher | **39,00 USD** einmalig, unbegrenzt | univik.com |
| GemeindebriefDruckerei, Umstellung als Auftrag | **200,00 €** bis 12 Seiten, **+45,00 €** je weitere 12 | gemeindebriefdruckerei.de |
| Markzware MarkzPortal / DesignMarkz / OmniMarkz | nicht veroeffentlicht | de.markzware.com |

**Die einzige belegte, fliessende Zahlungsbereitschaft in diesem Signal sind die 200 EUR
der GemeindebriefDruckerei** — und sie fliesst bereits, an einen Anbieter, der die
Zielgruppe seit Jahren als Druckkunden hat. Der zweite Betrag, 39 USD einmalig fuer
unbegrenzte Stapelkonvertierung, ist der Preisdeckel fuer jedes reine Softwareprodukt in
dieser Nische.

## 4. Die heutige Notloesung

**Sie heisst „PDF exportieren und die Sache vergessen", und Microsoft empfiehlt sie
selbst.** Der Weg steht auf der Support-Seite: `Datei > Speichern unter > PDF` fuer die
Ansicht, `Datei > Exportieren` bzw. der Umweg PDF → Word fuer die Weiterbearbeitung,
wobei Microsoft ausdruecklich einraeumt: *„layout may vary from the original"*.
Kosten: null, Zeitbedarf: Minuten, bei mehreren hundert Dateien das Skript.

**Die zweite Notloesung ist das Neuanlegen.** Ein Gemeindebrief, ein Vereinsflyer, eine
Speisekarte wird ohnehin jaehrlich oder halbjaehrlich neu gemacht. Die Vorlage in Canva,
Word oder Affinity **einmal** neu zu bauen kostet einen Abend und loest das Problem
dauerhaft — waehrend jede Konvertierung ein Ergebnis liefert, das nachgearbeitet werden
muss. Genau darauf laeuft die Empfehlung der GemeindebriefDruckerei hinaus: nicht die
Datei konvertieren, sondern das Layout in Affinity neu aufsetzen.

**Ein wichtiger technischer Befund zur Notloesung, der eine Behauptung aus der ersten
Suchrunde korrigiert:** Affinity Publisher kann `.pub` **nicht** direkt oeffnen. Das
PUB-Format hat keine veroeffentlichte Spezifikation, und keine Drittanwendung liest es
vollstaendig; der praktikable Weg ist PDF-Export aus Publisher und anschliessendes
Oeffnen in Affinity, oder der Umweg ueber IDML per MarkzPortal (Affinity-Forum,
markzware.de, univik.com, ueliraz.ch — alle abgerufen 2026-08-29). Fuer den Ideator hat
das zwei Folgen: Erstens ist die naheliegende Produktidee „`.pub` → bearbeitbares
Zielformat" technisch anspruchsvoller, als sie klingt. Zweitens ist die einzige
verfuegbare Grundlage dafuer die freie Bibliothek libmspub — **auf der LibreOffice und
Scribus bereits gratis aufsetzen.**

## 5. Was dagegen spricht

**(a) Der Hersteller liefert genau das Werkzeug, nach dem das Signal fragt, kostenlos.**
Das PowerShell-Beispielskript zur Massenkonvertierung steht auf derselben Seite, die das
Signal als Quelle nennt; ein zweites, ausgereifteres liegt frei auf GitHub. Damit ist
die einzige im Signal formulierte Produkthypothese („Migrationshilfe statt Layoutwerkzeug")
vor dem ersten Entwurf erledigt. Das ist dieselbe Konstellation wie beim SAP-Build-Apps-
und beim PV*SOL-Lauf: **die plausibelste Produktidee eines Abkuendigungssignals ist
regelmaessig die, die der Hersteller selbst geschlossen hat.**

**(b) Der Preisboden ist null, gleich vierfach.** LibreOffice Draw und Scribus lesen
`.pub` ueber libmspub; Affinity Studio ist seit November 2025 dauerhaft kostenlos;
Canva hat eine Gratisstufe und schenkt gemeinnuetzigen Vereinen — also einem Kernteil
der Zielgruppe — die Vollversion; Microsoft Designer liegt im Abo. Gegen vier freie
Angebote traegt kein Preisargument.

**(c) 33 Tage, und danach gibt es keinen zweiten Jahrgang.** Stichtag 01.10.2026
(M365-Abonnenten) bzw. 13.10.2026 (Office LTSC 2021). Ideator, Fit-Filter, fuenf
Angriffslaeufe, Spezifikation, Bau und erster Vertriebskontakt muessten in unter fuenf
Wochen durchlaufen — bei zwei Stunden pro Woche sind das **rund zehn Arbeitsstunden**.
Und anders als bei einer wiederkehrenden Pflicht ist das Thema danach weg: Wer bis
Oktober konvertiert hat, konvertiert nie wieder; wer es nicht getan hat, hat die Dateien
aufgegeben.

**(d) Die Kernzielgruppe ist im deutschsprachigen Markt namentlich bedient, mit
Festpreis.** Die GemeindebriefDruckerei nimmt 200 EUR bis 12 Seiten fuer genau die
Umstellung, die dieses Signal beschreibt, bei genau der Zielgruppe (Kirchengemeinden,
Vereine), mit einem Vertriebskanal, den die Fabrik nicht hat: bestehende Druckkunden.
Das erfuellt den roten Ausschlussgrund des Rollenauftrags woertlich — ein Anbieter im
deutschsprachigen Markt, der genau dieses Segment mit genau dieser Aufgabe bedient.

**(e) Der Auftragsgegenstand ist Nacharbeit, nicht Software.** Weil `.pub` keine
veroeffentlichte Spezifikation hat, liefert jede Konvertierung ein Ergebnis, das
jemand ansehen und korrigieren muss — Microsoft sagt es selbst (*„layout may vary"*),
und die GemeindebriefDruckerei kalkuliert vier Wochen Lieferzeit fuer zwoelf Seiten.
Ein Produkt, dessen Ergebnis immer Handarbeit nach sich zieht, verkauft Stunden, nicht
Lizenzen — dieselbe Absage wie beim Office-2021- und beim Project-Online-Lauf.

**(f) Der Stapelkonverter ohne Publisher existiert und kostet 39 USD einmalig.** Univik
deckt die einzige Restnische (Konvertierung nach dem Stichtag, ohne Installation)
vollstaendig ab: Ordnerweise, 1.500 Dateien je Stunde, Kommandozeile, fuenf
Ausgabeformate, unbegrenzt, ohne Abo. Darunter passt kein Produkt, das den Betriebsaufwand
nach G4 noch traegt.

**(g) Das Segment schrumpft seit Jahren, und das ist der Einstellungsgrund.** Microsoft
misst die Nutzung und entfernt das Produkt deswegen. Eine Kohorte, die ein Hersteller
mit vollem Messzugriff als zu klein bezeichnet, ist kein Zielmarkt fuer einen
Nebenerwerb.

## Offen geblieben

- **Jede Zahl zur Segmentgroesse.** Nicht ermittelt und mit den verfuegbaren Mitteln
  vermutlich nicht ermittelbar: Microsoft veroeffentlicht keine Nutzungszahlen, die
  deutschsprachige Fachpresse nennt keine, es gibt keine Intra2net-artige Erhebung zu
  Publisher. **Der Ideator darf hier keine Zahl ansetzen, auch keine gerundete.**
- **Ein Widerspruch auf Microsofts eigenen Seiten, den ich nicht aufloesen konnte.**
  Die deutsche Produktseite `microsoft.com/de-de/microsoft-365/publisher` sagt am
  2026-08-29 woertlich: *„Publisher wird ab Oktober 2026 nicht mehr weiterentwickelt.
  Microsoft wird die Verfuegbarkeit, Funktionalitaet und Sicherheit von Publisher auch
  nach dem Laufzeitende weiterhin gewaehrleisten."* Die englische Support-Seite sagt das
  Gegenteil: *„Microsoft 365 subscribers will not be able to access Publisher."* Ich
  halte die deutsche Fassung fuer eine veraltete oder fehlerhafte Uebersetzung und
  stuetze mich auf die englische Support-Seite, die auch ComputerBase, ghacks und
  windowslatest uebereinstimmend wiedergeben. **Belegt ist der Widerspruch, nicht seine
  Aufloesung.**
- **Markzware-Preise.** Nicht veroeffentlicht; Shop und Kontaktformular, kein Tarif auf
  der Ratgeberseite. Der Vergleichspreis in Abschnitt 3 stuetzt sich deshalb auf Univik.
- **Wie viele `.pub`-Dateien ein typischer Betroffener wirklich hat.** Die Microsoft-Q&A
  enthaelt einen Beitrag mit *„thousands of Publisher files ... 20 years of work"* — ein
  Einzelfall, keine Verteilung. Ob die Regel eher „drei Dateien" oder „dreihundert"
  lautet, entscheidet, ob die Notloesung „neu anlegen" traegt; ich konnte es nicht
  belegen.
- **Blockierte Quellen (fuers Logbuch):** `canva.com/newsroom/...` (403),
  `canva.com/de_de/preise/` (403). Die Affinity-Gratisstellung und die Canva-Preise sind
  deshalb nur ueber deutschsprachige Fachpresse belegt, nicht ueber die Primaerquelle.
- **Eine Falschangabe aus der ersten Suchrunde, die ich korrigiert habe und die dem
  Ideator sonst untergekommen waere:** Mehrere Ratgeberseiten behaupten, Affinity
  Publisher 2 koenne `.pub` importieren. Das Affinity-Forum und drei weitere Quellen
  widersprechen: Es gibt keinen nativen `.pub`-Import, der Weg fuehrt ueber PDF oder IDML.
