---
typ: markt
erfasst: 2026-08-30
auftrag: Tierarztpraxen im englischsprachigen Raum
suchraum: englischsprachig
segment: Tierarztpraxen und Kleintierkliniken in USA, UK, Kanada und Australien (companion animal practices)
betriebe: rund 43.500 konservativ (USA >30.000 laut AVMA, abgerufen 2026-08-30; UK 3.586 PSS-akkreditierte Premises, RCVS Facts 2024; Kanada 6.080, Statistics Canada Juni 2022; Australien 3.793, IBISWorld/AVA 2025). Obergrenze rund 72.000, wenn man fuer die USA die 58.350 Businesses von IBISWorld 2026 statt der AVMA-Praxiszahl nimmt
umsatz_je_betrieb: rund 1,12 bis 1,28 Mio USD je US-Standort (eigene Rechnung: IBISWorld 74,5 Mrd USD 2026 / 58.350 Businesses; Ankura 66 Mrd USD 2023 / 58.968 Locations), das entspricht rund 970.000 bis 1,10 Mio EUR bei 1 EUR = 1,159 USD
handarbeit: Dokumentation der Behandlung
kosten_der_handarbeit: 2,5 bis 4 Stunden je Tierarzt und 10-Stunden-Tag; bewertet mit dem BLS-Medianlohn 130.100 USD (Veterinarians, Mai 2025) rund 32.500 bis 52.000 USD je Tierarzt und Jahr, eigene Rechnung
anbieter_zugeschnitten: ueber 30 (mindestens 8 Cloud-PIMS, mindestens 12 KI-Diktatanbieter, mindestens 6 KI-Telefonanbieter, mindestens 4 reine Betaeubungsmittelbuecher, dazu OpenVPMS als Open Source)
anbieter_generisch: mindestens 8 (generische KI-Telefonbots mit Tierarzt-Landingpage: Phonely, Goodcall, AgentZap, Smith.ai, Nextiva XBert, Callbird, Aira, FrontDesk)
erreichbar_ueber: VMX Orlando (27.000 Besucher, 700+ Aussteller, NAVC 2026), ezyVet-Partnerprogramm mit oeffentlicher API, VIN mit ueber 115.000 Mitgliedern (Februar 2026), Vergleichsportale wie vetsoftwarehub.com und vetgeni.com
suchwort: "best veterinary AI scribe 2026", "veterinary practice management software comparison", "AI receptionist for vet clinics"
preis_plausibel: 85 EUR (99 USD je Tierarzt und Monat, Jahrestarif VetRec — der guenstigste Preis eines etablierten Vollanbieters der Zusatzschicht)
kunden_erreichbar: 44 (ein Promille von 43.500)
monatsumsatz: 3.740 EUR
traegt_5000: knapp
potenzial: gering
---

# Ein Segment von rund 43.500 Praxen mit belegter, teurer Handarbeit, offenem Kanal und hoher Zahlungsbereitschaft — in dem jede einzelne wiederkehrende Handarbeit bereits von zugeschnittenen Anbietern besetzt ist, bis hinunter zum Betaeubungsmittelbuch fuer 149 USD im Jahr.

## 1. Groesse

Die Frage hat vier Teilantworten, und sie widersprechen sich je nach Zaehlweise um den
Faktor zwei.

| Raum | Zahl | Quelle, abgerufen 2026-08-30 |
|---|---|---|
| USA, Praxen | "more than 30.000 veterinary practices" | AVMA, zitiert nach co.vet/post/veterinarian-facts |
| USA, Businesses | 58.350 (2026, +2,2 % zu 2025) | IBISWorld, Number of Businesses, Veterinary Services US |
| USA, Standorte | 53.574 Enterprises mit 58.968 Locations (2023) | Ankura, U.S. Veterinary Services Industry Snapshot |
| UK, akkreditierte Premises | 3.586 (2024) | RCVS Facts 2024 |
| UK, Businesses | 3.524 (2025) | IBISWorld UK |
| Kanada | 6.080 Veterinary-Services-Betriebe (Juni 2022) | Statistics Canada |
| Australien | 3.793 (2025) | IBISWorld Australia, deckungsgleich mit AVA-Angabe |

**Die Differenz ist erklaerbar, nicht widerspruechlich:** Die AVMA-Zahl meint
Praxisstandorte mit Personal, die IBISWorld-Zahl zaehlt jedes Gewerbe mit, also auch
mobile Einzeltieraerzte und Nebentaetigkeiten. Ich rechne mit der konservativen Summe
**43.500** (30.000 + 3.600 + 6.100 + 3.800) und nenne 72.000 als Obergrenze. Irland und
Neuseeland habe ich nicht recherchiert; beide liegen unter 1.000 und aendern die
Groessenordnung nicht.

**Das ist die groesste Segmentzahl, die dieses Repo bisher enthaelt** — mehr als das
Vierfache der 10.385 deutschen Tierarztpraxen aus dem Profil vom 2026-08-29 und knapp das
Doppelte der 46.902 Speditionen. Der Hebel des Sprachraums funktioniert also genau so, wie
`quellen.yml` ihn beschreibt. Frage 1 ist damit erledigt, und zwar positiv.

## 2. Zahlungskraft

Der US-Markt fuer Veterinary Services liegt bei **74,5 Mrd USD im Jahr 2026** (IBISWorld,
NAICS 541940, abgerufen 2026-08-30), Ankura nennt fuer 2023 **66 Mrd USD** mit einer
Gewinnmarge von **14,4 Prozent**. Geteilt durch die Standortzahl ergibt das je Standort
**1,12 bis 1,28 Mio USD Jahresumsatz** (eigene Rechnung). Bei 1 EUR = 1,159 USD
(tradingeconomics, 2026-08-29) sind das rund **970.000 bis 1,10 Mio EUR** — gut das
Doppelte bis Dreifache einer deutschen Praxis (326.000 bis 580.000 EUR).

**Die IT-Quote habe ich nicht gefunden**, und das ist die groesste Luecke dieses Profils.
Der VMG/AAHA Chart of Accounts ist der Branchenstandard fuer genau diese Auswertung, aber
die Zahlen liegen hinter der VMG-Mitgliedschaft (myvmg.com, abgerufen 2026-08-30). Nach
meiner Lehre vom Hausverwaltungslauf waere die Quote die schnellste Vorpruefung gewesen.

**Was stattdessen die Zahlungsbereitschaft belegt, ist der Preis der bestehenden Systeme,
und der ist hoch:** ezyVet ab **260,50 USD je Nutzer und Monat**, Shepherd ab **299 USD je
Tierarzt und Monat**, Vetspire ab **349 USD je DVM und Monat**, Digitail rund **300 USD im
Monat**; Cornerstone und Covetrus Pulse veroeffentlichen keine Preise (Provet-Vergleich
und vetsoftwarehub, beide abgerufen 2026-08-30). Eine Praxis mit drei Tieraerzten zahlt
also rund 900 USD im Monat allein fuer das Kernsystem. **Zahlungsbereitschaft ist in
diesem Segment nachweislich vorhanden und liegt um den Faktor fuenf bis zehn ueber allem,
was ich in deutschen Segmenten gemessen habe.**

## 3. Wiederkehrende Handarbeit

Der teuerste wiederkehrende Vorgang ist die **Behandlungsdokumentation**, und er ist
besser belegt als in fast jedem anderen Segment — allerdings mit einem Vorbehalt, den ich
gleich nenne.

- **2,5 bis 3,5 Stunden je 10-Stunden-Schicht** allein fuer die Aktenfuehrung, 25 bis 40
  Prozent der Arbeitszeit fuer Dokumentation und Verwaltung insgesamt (mehrfach zitiert,
  u. a. woovet und pawfectnotes, abgerufen 2026-08-30).
- **6,2 Stunden je Woche Dokumentation nach Feierabend**, Umfrage des Veterinary
  Information Network 2024 (zitiert, Primaerquelle nicht offen zugaenglich).
- **62 Prozent** der Befragten sagen, Verwaltungsarbeit stoere die klinische Arbeit "often"
  oder "almost always"; **91 Prozent** nennen Aktenfuehrung als den Bereich, in dem KI
  wirksam hilft (CoVet, Q1 2026, 120+ Befragte, co.vet, abgerufen 2026-08-30).
- Europaeischer Gegencheck: Die **FVE-Umfrage zur Verwaltungslast** (August 2024 bis Januar
  2025) fand, dass **64 Prozent** eine Verdopplung der Verwaltungsarbeit melden und
  niemand einen Rueckgang; teuerster Einzelposten ist **Verschreibung und Abgabe von
  Medikamenten mit bis zu ueber 10 Stunden je Woche** (fve.org, abgerufen 2026-08-30).

**Der Vorbehalt:** Von diesen Quellen sind die CoVet-Umfrage (KI-Diktatanbieter), woovet,
pawfectnotes, happydoc und charthound **Anbieter im selben Markt**. Nach meiner eigenen
Lehre ist das Werbung, nicht Messung. Belastbar bleiben die VIN-Umfrage und die
FVE-Umfrage — letztere mit nur **75 Teilnehmern** und aus Europa, nicht aus dem
Zielsprachraum. **Die Groessenordnung ist plausibel und mehrfach genannt, die Praezision
ist es nicht.**

Zweiter, davon unabhaengiger Vorgang: das **Betaeubungsmittelbuch**. In den USA
DEA-pflichtig mit Anforderungen in allen 50 Staaten, in UK der Controlled Drugs Register.
Das ist der Vorgang, der auf dem Papier am ehesten wie eine Nische aussieht — siehe Frage 5.

## 4. Was sie heute kostet

Die belastbarste Zahl kommt hier nicht von einem Verband, sondern vom **Bureau of Labor
Statistics** (Occupational Outlook Handbook, Stand **Mai 2025**, abgerufen 2026-08-30):

| Rolle | Medianlohn im Jahr |
|---|---|
| Veterinarians | **130.100 USD** (unterste 10 %: 73.920, oberste 10 %: 215.700) |
| Veterinary Technologists and Technicians | **47.380 USD** (unterste 10 %: 35.710, oberste 10 %: 63.180) |

Bei 2.080 Jahresstunden entspricht der Tierarzt-Median **62,55 USD je Stunde** (eigene
Rechnung). Die 2,5 bis 4 Stunden Dokumentation je Tag ergeben bei 220 Arbeitstagen
**550 bis 880 Stunden im Jahr**, bewertet also **34.400 bis 55.000 USD je Tierarzt und
Jahr** — rund **30.000 bis 47.500 EUR**. Selbst wenn man die Arbeit zum Tarif einer
Fachangestellten bewertet (22,78 USD je Stunde), bleiben **12.500 bis 20.000 USD**.

**Das ist die hoechste Handarbeitskostenzahl in diesem Repo**, und sie ist die Obergrenze,
gegen die ein Werkzeugpreis anzutreten haette. Sie erklaert zugleich, warum ein
KI-Diktatdienst fuer 1.200 USD im Jahr in diesem Segment ohne Weiteres verkaufbar ist —
und warum entsprechend viele Anbieter da sind.

## 5. Wer es heute bedient

**Hier endet das Profil.** Ich trenne wie immer in drei Schichten, und in diesem Segment
ist jede einzelne besetzt — mit zugeschnittenen, nicht mit generischen Anbietern.

**Schicht 1 — Praxismanagementsysteme (PIMS), ausschliesslich Tiermedizin.** Mindestens
acht mit oeffentlicher Marktpraesenz: **ezyVet** (IDEXX), **Cornerstone** (IDEXX),
**AVImark**, **Covetrus Pulse**, **Shepherd**, **Digitail**, **Provet Cloud**,
**Vetspire**, dazu **Hippo Manager**, **Instinct**, **VETport**, **Vetter**. Der Markt
teilt sich sauber in serverbasierte Altsysteme (AVImark, Cornerstone) und Cloud-Systeme
(Provet-Vergleich, abgerufen 2026-08-30). **Und es gibt Open Source: OpenVPMS**, eine
Non-Profit-Organisation mit vollem Praxissystem, dazu **VetGeo** als kostenloses
Cloud-Produkt und **Ababu** als weiteres freies System (openvpms.org, geeksmint,
tech2geek, alle abgerufen 2026-08-30).

**Schicht 2 und 3 — KI-Diktat.** Das ist die Schicht, in der eine Zwei-Stunden-Woche
theoretisch bauen koennte. Ein Vergleichsportal zaehlt hier **zwoelf Werkzeuge zwischen 40
und 450 USD im Monat** (vetsoftwarehub, "Veterinary AI Scribe Pricing 2026", abgerufen
2026-08-30). Namentlich belegt:

| Anbieter | Preis je Monat |
|---|---|
| Scribenote | **kostenlos** oder 99 USD |
| Talkatoo | ab 40 USD (SOAP Notes, Jahrestarif), Ultimate 116 USD |
| VetGeni | 50 USD |
| ScribbleVet | 40 bis 200 USD, Volltarif 150 USD jaehrlich / 200 USD monatlich |
| CoVet AI | ab 99 USD |
| VetRec | 99 USD jaehrlich / 150 USD monatlich |
| HappyDoc | ab 119 USD |
| Otto Scribe | 0,80 USD am Tag, also rund 24 USD |
| PetDesk Scribe | im Paket enthalten |
| PawfectNotes, VetDoze, Chart Hound, whiskr.ai, Squako | eigene Vergleichsseiten, Preise nicht einheitlich |

Quellen: vetgeni.com, vetsoftwarehub.com, otto.vet, pawfectnotes.com, alle abgerufen
2026-08-30.

**Schicht 3 — KI-Telefon und Empfang.** Ein KI-Empfang fuer eine Tierarztpraxis kostet
2026 **79 bis 600 USD im Monat** (vetsoftwarehub, "AI Receptionist for Veterinary Clinics
2026 Guide"). Zugeschnitten: **Otto** (Client Communication ab rund 350 USD je Praxis),
**PetDesk**, **Vetstoria**, **Mango** (119 USD Telefon / 219 USD mit KI / 419 USD
Vollpaket), **AgentZap** (ab 109 USD), **The CallTaker**, **ServiceAgent**,
**Vet Receptionists**. Generisch mit Tierarzt-Landingpage: Phonely, Goodcall (ab 79 USD),
Smith.ai, Nextiva XBert, Callbird, Aira, FrontDesk, Voksha.

**Der entscheidende Befund liegt eine Ebene tiefer.** Ich habe zur Gegenprobe den
schmalsten denkbaren Einzelvorgang geprueft, das **Betaeubungsmittelbuch**. Auch er hat
**vier zugeschnittene Anbieter**: **VetSnap**, **CS Logbook** (ab **149 USD im Jahr**, also
12 USD im Monat, mit unveraenderlichem Audit-Log, rollenbasierten Rechten, AES-256 und
US-Datenresidenz), **Pawprints Vetlogs** und **MyCUBEX** (cslogbook.com, go.vetsnap.com,
pawprintsvetlogs.com, cubex.com, alle abgerufen 2026-08-30).

**Wenn selbst das Betaeubungsmittelbuch vier Anbieter, Preistransparenz und eine eigene
Review-Seite auf einem Branchen-Vergleichsportal hat, gibt es in diesem Segment keine
unbesetzte Einzelfunktion mehr.** Das ist die Kernaussage dieses Profils.

**Es gibt sogar eine eigene Vergleichsportal-Industrie.** vetsoftwarehub.com,
vetgeni.com, ownerexchange.com, tailwerks.com, co.vet und layer3labs.io betreiben
Kategorieseiten fuer Tierarztsoftware mit Preisvergleich, Jahreszahl im Titel und
Produktreviews. Nach meiner Lehre aus dem Speditionslauf ist die Uebersicht selbst der
Befund: Existiert ein Anbietervergleichsportal, ist das Segment fast immer `gering`. Hier
existieren sechs davon.

**Ausgelassen wegen G1:** Die Abwicklung von Tierkrankenversicherungs-Anspruechen ist in
UK und zunehmend in den USA ein erheblicher Handarbeitsblock der Praxen. Sie faellt als
zugehoerige IT einer Versicherung unter G1 und ist deshalb nicht recherchiert.

## 6. Wie man sie erreicht

Der Kanal ist der beste, den dieses Repo bisher gesehen hat — und er hilft trotzdem nicht.

- **VMX (Veterinary Meeting & Expo)**, Orlando, NAVC: **ueber 27.000 Besucher, davon
  20.000+ Fachleute, 700+ Aussteller** in der Ausgabe 2026 (navc.com, abgerufen
  2026-08-30). Zum Vergleich: der deutsche bpt-Kongress hat 3.400 Besucher.
- **VIN (Veterinary Information Network)**: **ueber 115.000 Mitglieder weltweit**, Stand
  Februar 2026 (vin.com). Der groesste vermessene Peer-Kanal in diesem Repo — groesser als
  forum-speditionen.de um den Faktor acht.
- **ezyVet-Partnerprogramm mit oeffentlicher API.** ezyVet unterscheidet ausdruecklich
  zwischen privater und **kommerzieller** API-Integration und betreibt ein
  Partnerverzeichnis nach Kategorie und Land, unter anderem fuer Controlled Drugs,
  Appointments, Client Management und Inventory (ezyvet.com/become-a-partner, abgerufen
  2026-08-30). **Das ist ein echtes App-Verzeichnis, kein Adressverzeichnis** — genau der
  Kanaltyp, den `CLAUDE.md` verlangt.
- **Suche.** Die Zielgruppe sucht nachweislich aktiv: "best veterinary AI scribe 2026",
  "veterinary practice management software comparison 2026", "AI receptionist for vet
  clinics". Jedes dieser Suchwoerter liefert sechs bis zehn kommerzielle Vergleichsseiten
  auf der ersten Seite.

**Warum das nicht hilft:** Derselbe Beleg, der die Suchabsicht nachweist, beweist die
Saettigung des Kanals. Auf jedes dieser Suchwoerter ranken bereits Portale, deren
Geschaeftsmodell das Ranking *ist*. Ein nebenberufliches Projekt mit zwei Wochenstunden
kann in diesem Umfeld weder SEO noch einen Messestand bei 700 Ausstellern bestreiten. Und
das ezyVet-Partnerverzeichnis fuehrt, wie das bpt-Tool im deutschen Profil, auf eine Liste,
auf der man erst einmal stehen muss.

## 7. Die Rechnung

**Preis, belegt am Vollprodukt der Zusatzschicht:** Der guenstigste Volltarif eines
etablierten KI-Diktatanbieters ist **99 USD je Tierarzt und Monat** (VetRec, Jahrestarif)
= **85 EUR** bei 1 EUR = 1,159 USD. Nach der Lehre "Der Preis des Vollprodukts deckelt
jede Teilfunktion" muesste eine Einzelfunktion darunter liegen; ich rechne trotzdem mit
den vollen 85 EUR, um dem Segment die guenstigste Annahme zu geben.

**Kundenzahl:** 43.500 Praxen.

    ein Promille:   44 Kunden  ×  85 EUR  =    3.740 EUR im Monat
    ein Prozent:   435 Kunden  ×  85 EUR  =   36.975 EUR im Monat

**`traegt_5000: knapp`.** Bei der pessimistischen Durchdringung fehlen 1.260 EUR zur
Schwelle — und das ist Umsatz, nicht Marge. Bei einem Prozent traegt das Segment die
Schwelle um mehr als das Siebenfache.

**Das ist das erste Segment in diesem Repo, das an der Groesse nicht klar scheitert.** Die
Rechnung geht auf, sobald man mehr als ein Promille erreicht, und bei einem Preis von 150
statt 85 EUR — durchaus marktueblich — genuegen schon 34 Kunden. Der Sprachraum-Hebel aus
`quellen.yml` funktioniert also nachweislich: Dasselbe Produkt, das in Deutschland an der
Menge gescheitert waere, scheitert hier nicht daran.

**Es scheitert an Frage 5.** Nach der Regel gilt `gering` bei "gut bedient", unabhaengig
von der Rechnung — und dieses Segment ist nicht gut bedient, sondern uebersaettigt.

## Die Luecke

**Es klafft keine, und diesmal nicht knapp.**

Fuenf der sieben Fragen fallen ungewoehnlich guenstig aus. Das Segment ist mit rund 43.500
Praxen **das groesste im Repo**. Die Zahlungskraft ist mit rund 1 Mio EUR Umsatz je
Standort und PIMS-Preisen von 260 bis 349 USD je Nutzer und Monat **die hoechste im Repo**.
Die Handarbeit ist mehrfach belegt, die Kosten mit BLS-Medianloehnen sauber bezifferbar
(30.000 bis 47.500 EUR je Tierarzt und Jahr). Der Kanal ist mit VMX (27.000 Besucher), VIN
(115.000 Mitglieder) und einem oeffentlichen API-Partnerprogramm **der beste im Repo**.

Und genau deshalb ist nichts frei. **Die Attraktivitaet des Segments ist die Ursache seiner
Besetzung, nicht ein Gegenargument dazu.** Das ist dieselbe Lehre, die ich beim
Hausverwaltungslauf gezogen habe — ein zahlungskraeftiges Segment ist verdaechtig —, hier
aber in ihrer schaerfsten Form: Wo eine belegte Handarbeit 40.000 EUR im Jahr kostet und
43.500 Betriebe sie haben, sind bereits dreissig Anbieter, sechs Vergleichsportale und ein
Preisboden von null.

Drei Ausschluesse, die unabhaengig voneinander schon allein tragen:

1. **Der Preisboden ist null.** OpenVPMS (Open Source, Non-Profit) und VetGeo im
   Kernsystem, **Scribenote mit kostenlosem Tarif** im KI-Diktat. Nach meiner Lehre vom
   Spielplatzlauf beendet ein Freemium- oder Open-Source-Anbieter im Segment den Lauf.
2. **Die schmalste denkbare Nische ist besetzt und kostet 12 USD im Monat.** Das
   Betaeubungsmittelbuch — ein Einzelvorgang mit Bundespflicht in allen 50 Staaten — hat
   vier zugeschnittene Anbieter, und CS Logbook liefert dafuer bereits unveraenderliche
   Audit-Logs, rollenbasierte Rechte und AES-256 zu **149 USD im Jahr**. Wenn hier kein
   Platz ist, ist nirgends Platz.
3. **Der einzige dokumentierte Funktionsmangel liegt im Kernsystem und ist nicht
   herausloesbar.** Rezensenten bemaengeln an ezyVet, dass sich Positionen nicht direkt aus
   einem Kostenvoranschlag verbuchen lassen ("no usable path to post charges directly off
   an estimate", vetsoftwarehub, abgerufen 2026-08-30). Das ist eine echte, seit Jahren
   beklagte Luecke — aber sie sitzt mitten im Buchungskern eines PIMS. Die Fabrik baut kein
   Kernsystem.

**Fuer den Ideator heisst das: Aus diesem Profil ist keine Idee abzuleiten.** Der Wert
liegt in zwei uebertragbaren Befunden. Erstens: **Der Sprachraum-Hebel funktioniert
rechnerisch** — die Schwelle aus G7 ist in einem englischsprachigen B2B-Segment mit einem
Promille Durchdringung fast erreichbar und mit einem Prozent muehelos. Zweitens: **Er
funktioniert nur dort, wo die Anbieterdichte nicht mit der Marktgroesse mitgewachsen ist.**
In der Tiermedizin ist sie es, und zwar deutlicher als in jedem deutschen Segment. Die
Suche nach dem naechsten englischsprachigen Segment sollte deshalb mit Frage 5 *beginnen*:
Ein Abruf auf "<Segment> software comparison 2026" entscheidet, ob der Rest des Laufs
lohnt.

## Was unklar ist

- **Die IT-Quote fehlt.** Der VMG/AAHA Chart of Accounts ist der Branchenstandard und
  haette Software als Anteil vom Umsatz genannt; die Daten liegen hinter der
  VMG-Mitgliedschaft. Ohne sie ist meine Obergrenze fuer den Preis am Vollproduktpreis
  belegt statt am Budget.
- **Die Zeitangaben zur Dokumentation stammen ueberwiegend von Anbietern.** Belastbar sind
  nur die VIN-Umfrage 2024 (6,2 Stunden je Woche nach Feierabend, Primaerquelle nicht
  offen) und die FVE-Umfrage 2025 — letztere mit nur **75 Teilnehmern und aus Europa**.
  Eine anbieterunabhaengige US-Messung habe ich nicht gefunden.
- **Der US-Standortzahl fehlt die amtliche Bestaetigung.** Die Census-CBP-Zahl fuer NAICS
  541940 (in Suchauszuegen mit 34.296 fuer 2023 genannt) konnte ich nicht im Original
  belegen: Die Census-API verlangt einen Schluessel, data.census.gov ist eine
  JavaScript-Anwendung. Ich habe die Zahl deshalb **nicht** verwendet und mit der
  AVMA-Angabe ">30.000" gerechnet.
- **Die RCVS-Gesamtzahl registrierter Premises fehlt.** Belegt sind nur die 3.586
  PSS-akkreditierten Praxen; PSS ist freiwillig, die tatsaechliche Zahl liegt hoeher. Der
  Bericht "RCVS Facts 2024" liegt als PDF vor und war nicht auslesbar.
- **Die kanadische Zahl ist von Juni 2022** und damit vier Jahre alt.
- **Marktanteile und Durchdringung der Zusatzschicht sind vollstaendig unbekannt.** Kein
  einziger der zwoelf KI-Diktatanbieter nennt Kundenzahlen — anders als im deutschen Markt,
  wo ReportAssistant ueber 300 Praxen ausweist. Ob dieser Markt bei 3 oder bei 40 Prozent
  Durchdringung steht, ist offen. **Das ist das einzige Gegenargument zu `gering`**, und
  es ist schwaecher als im deutschen Profil, weil hier dreissig statt drei Anbieter um
  dieselbe Durchdringung konkurrieren.
- **Der Merchant-of-Record-Aufwand ist nicht beziffert.** G7 nennt Umsatzsteuer im
  Zielland als Preis der Oeffnung; US-Sales-Tax-Nexus, UK-VAT und GST in AU/CA waeren zu
  klaeren, bevor eine englischsprachige Idee gerechnet wird. Fuer den Oekonomen.
- **Reddit war nicht abrufbar** (Claude Code blockt www.reddit.com). r/veterinary und
  r/VetTech bleiben unvermessen; angesichts von VIN mit 115.000 Mitgliedern aendert das am
  Kanalbefund nichts.
