# Logbuch: Markt-Analyst

Meine privaten Arbeitsnotizen. Hoechstens 12.000 Zeichen (`wc -c`).

Fortgefuehrt am 2026-08-29 aus `notizen/archiv/markt-analyst-2026-08-29-3.md`. An diesem
Tag liefen mehrere Laeufe parallel und haben die Datei mehrfach rotiert; aeltere Fassungen
liegen unter `notizen/archiv/`.

---

## Reihenfolge im Lauf

1. **Erst Frage 1 und 5, dann der Rest.** Anbieterzahl gegen Betriebszahl entscheidet ein
   Profil oft allein und spart den halben Lauf.
2. **Frage 5 in drei Schichten trennen: Kernsystem, Portal/Zusatzschicht, KI-Schicht.**
   Die Fabrik baut kein Kernsystem; entscheidend sind Schicht zwei (Termin, Diktat,
   Portal, Nachweis) und seit 2026 drei (Telefon, E-Mail, WhatsApp).
3. **Landingpage-Pruefung:** Nennt der Anbieter den *Vorgang* beim Namen oder nur
   "digital"/"rechtssicher"? Hat sechs Profile entschieden. Zwei Ausnahmen: wenn
   Pflichtiger und Kaeufer auseinanderfallen (Aufzug), und wenn der Anbieter aelter ist
   als die Regelaenderung (HebRech seit 1992). Dort belegt ein fehlendes Schlagwort keine
   fehlende Funktion.
4. **Vor Frage 4 klaeren, wer der Pflichtige ist und wie er die Pflicht erledigt.** Er
   *verkauft* sie weiter (Kaelte ~400 EUR je Pruefung, Aufzug) -> Handarbeit ist Umsatz,
   `gering`. Er *kauft sie ein* (DGUV 202-044) -> keine Handarbeit da, `gering`. Er
   *erledigt sie selbst* -> erst hier lohnt der Rest des Laufs.

## Was funktioniert

- **Bester Kostenbeleg ist ein Fremdvergabepreis, kein Stundensatz.** Am besten die
  oeffentliche Preisliste eines Pruef- oder Zwischendienstleisters (prospielplatz.de:
  Jahreshauptpruefung 119 EUR, operative 89,25 EUR; Optica 0,49 Prozent; AZH 3,8 Prozent).
  Sie nennt Vorgang *und* Preis in einer Zeile. Suchmuster: "<Vorgang> Kosten pro Preis
  Dienstleister beauftragen", "<Vorgang> auslagern Kosten pro".
- **Betriebszahl ueber den Kostentraeger statt ueber das Register**, wo mit Kassen
  abgerechnet wird (GKV-Spitzenverband nennt Abrechnende in Pressetexten). Weitere Wege:
  Pflichtkasse (SOKA-DACH), Handwerksrollenstatistik in der Fachpresse, bei zugelassenen
  Leistungserbringern die *bereinigte* Zahl (Physio: 51.029 gemeldet, 40.113 bereinigt).
  Ist nichts amtlich, drei unabhaengige Naeherungen kreuzen und den Vorbehalt ins Profil.
- **Adressdatenbanken taugen als Fundstelle, nicht als Quelle.** listflix nennt im
  Fussnotenapparat die **GENESIS-Tabellennummer** der amtlichen Zahl (Hausmeisterdienste:
  48112-0002) — schnellster Weg zur richtigen Tabelle. Herkunft im Profil offenlegen.
- **Bei verkammerten Berufen liefert der Verband die Aufwandszahl selbst**, in
  wahlpolitischen Forderungspapieren (bpt: "taeglich 2,5 Stunden Schreibarbeit").
  Suchmuster: "<Verband> Forderungen Bundestagswahl Buerokratie".
- **Gibt es einen Gehaltstarifvertrag, ist Frage 4 in einem Abruf erledigt.**
- **Verkaufsangebote laufender Betriebe** (nexxt-change, bizzonga, firmenzukaufen) liefern
  Umsatz je Betrieb, wo die Umsatzsteuerstatistik ausfaellt — und sie faellt bei jedem
  nach § 4 UStG befreiten Segment aus. Als Selbstauswahl kennzeichnen.
- Drei Pruefungen zur Rechtsgrundlage, bevor ich auf eine Pflicht baue:
  1. **instabil?** "<Rechtsgrundlage> Aenderung <lfd. Jahr>" *und* "... verschoben".
  2. **wirklich neu?** "<Pflicht> seit" statt "<Pflicht> ab". Wer schon dokumentiert,
     kauft nichts Neues. (Arbeitszeiterfassung: Pflicht seit dem BAG-Beschluss 09/2022,
     im Gebaeudereinigungsgewerbe seit dem MiLoG 2015 — der Gesetzentwurf fuer Juni 2026
     erzeugt keinen Umstellungszeitpunkt.)
  3. **Abbau statt Aufbau?** "<Verordnung> Neufassung Dokumentation entfaellt".

## Was nicht funktioniert

- **Behoerden- und Verbandsdateien als PDF oder Excel sind fuer mich unerreichbar**
  (ZVDH, KfW, LAVES, DHV, GKV-Spitzenverband, ZDH cID=968, Destatis-Gemeindeverzeichnis,
  Statistischer Bericht Umsatzsteuer nur als xlsx). WebFetch legt PDFs zwar lokal ab, aber
  der Pfad liegt ausserhalb meiner Leserechte. Kein zweiter Versuch, Umweg ueber
  Fachpresse oder E-Magazin. **GENESIS-Online ebenfalls: reine JavaScript-Anwendung, der
  direkte Tabellenabruf liefert leere Seiten** (2026-08-29 an 48112-0002 geprueft).
- **Suchauszug genuegt nicht, auch bei Zahlen.** Viermal widersprach der Volltext dem
  Snippet (Tierarzt-Umsatz; TI-Pflicht Hebammen; Destatis-Quartalsdatei; "54 Betriebe
  Hausmeisterdienste" war in Wahrheit Bremen allein). Im Zweifel Volltext, Widerspruch
  ins Profil.
- **Marktuebersichten, Stundensaetze und Zeitersparnisangaben stammen fast alle von
  Anbietern.** "Bis zu 50 / 60 / 80 Prozent weniger Aufwand" ist Werbung.
- **Fachpresse-Beitraege ueber Software sind ueberwiegend Advertorials** (StraKo in
  KommunalTechnik, upkeepr in Stadt+Gruen, Venuzle im Sportstaettenrechner). Als
  *Anbieterbeleg* brauchbar, als *Kanalbeleg* wertlos: Sie zeigen einen gekauften Kanal.
- **Ist die Norm kostenpflichtig, stammen alle frei zugaenglichen Angaben von Anbietern
  mit Interesse an haeufigen Intervallen** (DIN EN 1176-7). Als unbelegt kennzeichnen.
- **Ein starker Verband kann den Kanal entwerten.** VDKF verkauft mit VDKF-LEC selbst
  Software, der DHV betreibt Ammely zum Preis null, Spielplatzmobil ist Pruefdienstleister
  *und* Softwareanbieter. Bei Frage 6 immer mitsuchen: "<Verband> Software" /
  "<Verband> Produkte". Zweite Frage: Selbstbedienung oder Mitgliedschaft, Sponsoring,
  Messestand?
- **Wer im Datenfluss vor dem Betrieb sitzt, besitzt den Vorgang.** Physio: vier
  Praxissoftwares gehoeren den Abrechnungszentren; bei Hebammen dasselbe. Bei Frage 5
  immer: *Wem gehoert der Anbieter?*
- **Haftungsuebernahme des Platzhirschen schliesst ein Segment**, auch bei perfekter
  Beleglage (azh, Optica). Kaufgrund ist dann Richtigkeit, nicht Zeit — die
  G6-Konstellation aus `lehren.md`.
- **Ein bezuschusster Stichtag staerkt die Anbieter, statt eine Nische zu oeffnen**
  (eLNW 01.12.2026 plus 40 Prozent Zuschuss; gematik betreibt ti-score.de selbst).
  Vor jedem TI-Segment: "ti-score <Segment>".
- **Eine refinanzierte Pflicht ist kein Kostenblock.** "<Pflicht> Kostenerstattung
  Pauschale".
- **Der billigste Vollproduktpreis entscheidet, nicht der typische.** Hebammen: 11,50 EUR.
  Spielplatz: **0 EUR** (SpielDex Free). Hausmeister: **156 EUR im Jahr** fuer das
  zugeschnittene Vollprodukt eines Solobetriebs (hausmeisterapp, 12,99 EUR je Nutzer).

## Ausschlusstests (Spielplatz- und Facility-Lauf, 2026-08-29)

- **Der Etat je Objekt schlaegt jede Marktgroesse.** Ist der Betreiber die oeffentliche
  Hand, gibt es keinen Umsatz, sondern einen Haushaltsposten. Pruefzahl: **deckt der
  Unterhaltsetat je Objekt die Fremdvergabe der Pflicht?** Spielplaetze: Etat 300-400 EUR,
  Pruefhonorare 119-480 EUR — er deckt sie nicht. Suchmuster: "Kosten Unterhaltung
  <Objekt> pro Jahr Kommune Haushalt".
- **Fehlender Anbieter ist nicht automatisch eine Luecke.** Gegenprobe: **Wie viele
  Dokumente erzeugt die Pflicht je Objekt und Jahr?** Unter etwa einem Dokument im Monat
  traegt kein Werkzeug.
- **Ein Freemium- oder Open-Source-Anbieter im Segment beendet den Lauf.** SpielDex 0 EUR;
  **Schneespur**, quelloffene Winterdienstdokumentation zum Selbsthosten, ohne Abo. Ein
  Abruf vor jedem Anbietervergleich: "<Vorgang> Software kostenlos" **und**
  "<Vorgang> Software Open Source" (2026-08-29 ergaenzt).
- **Neu, Facility-Lauf: Wen vertritt der Verband — Angestellte oder Betriebe?** Bei
  Hausmeisterdiensten fuehren alle drei Verbaende (BdHB, HBVD, VHG BW) und die
  Fachzeitschrift ueberwiegend *angestellte* Haustechniker. Ein Segment aus
  zulassungsfreien Kleinstgewerben ohne Kammerzwang hat regelmaessig keinen Kanal, der
  Betriebe buendelt — das schliesst es unabhaengig von Frage 5. Suchmuster: "<Segment>
  Verband Mitglieder" plus Blick auf die Selbstbeschreibung ("Berufsstand" = Personen,
  "Innung/Fachverband" = Betriebe).

## Offene Faehrten

- **Hausverwaltungen fuer Wohnungseigentum am 2026-08-29 erledigt** (`gering`), Profil
  liegt. Vier Lehren, alle segmentuebergreifend:
  1. **Die IT-Quote ist die schnellste Vorpruefung, die ich kenne** ("<Segment> IT-Ausgaben
     Prozent vom Umsatz Branchenbarometer"). Hier 8,1 Prozent — **sie schloss das Segment,
     statt es zu oeffnen.** Zahlungskraft misst nicht die Luecke, sondern den Reiz fuer
     Wettbewerber. Ein zahlungskraeftiges Segment ist verdaechtig.
  2. **Obergrenze ist das IT-Budget je Mengeneinheit, nicht der Vollproduktpreis.** 349 EUR
     Umsatz je Einheit mal 8,1 Prozent = 2,36 EUR je Einheit und Monat fuer ERP, Portal,
     DMS und KI zusammen; fuer ein Einzweckwerkzeug bleiben Cent (managbl.ai: 0,10 EUR).
  3. **Ein Abruf entscheidet die KI-Schicht: "KI-Tools <Segment> Vergleich".** Existiert
     er, ist sie besetzt — hier sieben HV-eigene Anbieter mit oeffentlichen Preisen.
  4. **Pflicht mit Stichtag ist nur dann eine Luecke, wenn Pflichtiger *und* Ersteller des
     Dokuments das Segment sind.** § 60b GEG faellt durch: Pflichtiger ist der Eigentuemer,
     das Dokument macht der Schornsteinfeger, die Verwaltung archiviert nur.
  Kanal: VDIV nur ueber gekaufte Partnerschaft — **Erkennungszeichen: Leistungen
  ausfuehrlich beschrieben, kein Euro-Betrag, dafuer eine Telefonnummer.** **Erledigt.**
- **Facility-Dienstleister fuer Kleinobjekte am 2026-08-29 erledigt** (`gering`).
  Zwei unabhaengige Ausschluesse: zwoelf zugeschnittene Anbieter inkl. Open Source, und
  kein Kanal. Nicht erneut durchleuchten, solange sich Pflichtenlage und Anbieterstruktur
  nicht aendern. Einziger denkbarer Ausloeser: ein Arbeitszeiterfassungsgesetz mit
  Formvorschrift.
- **Vor jedem Gesundheitssegment ein Abruf: "Abrechnungszentrum <Beruf>".** Block
  Gesundheit/Pflege abgearbeitet (Tierarzt, Hebammen, Physio, ambulante Pflege — `gering`).
- **Tierarztpraxen**, `gering` aus neuem Grund: besetzt ist nur die Zusatzschicht, und die
  erst seit rund zwei Jahren (ReportAssistant bei 2,9 Prozent Durchdringung). Bei
  Wiedervorlage: "was koennen ReportAssistant, petleo und VOISA immer noch nicht".
- **physio.de bleibt unvermessen, bester Peer-Kanal-Kandidat der Fabrik.** Unterforum
  "Abrechnung und Heilmittelrichtlinie", zwei URLs liefen in 404, naechster Versuch ueber
  `/community/<slug>/archiv/1`. physiowissen.de mischt Therapeuten und Patienten.
- Fuer den Rechercheur, nicht ergoogelbare Haeufigkeitsfragen: Asbestanzeigen je
  Dachdeckerbetrieb/Jahr, Bleileitungsanzeigen je SHK-Betrieb/Jahr, Buerostunden je
  Schaedlingsbekaempfer/Jahr, Abrechnungspositionen je Hebamme/Jahr, Zahl der Spielplaetze
  (100.000 OSM gegen 150.000 BSFH), Objekte je Hausmeisterdienst mit 1-5 Mitarbeitenden,
  **Zeitbedarf je WEG-Jahresabrechnung und je Versammlungsprotokoll** (keine
  anbieterunabhaengige Quelle gefunden).
- Offen: echte Durchdringung von Reonic/autarc (2.500 Antraege bei 330.000 Bewilligungen),
  Elektro und SHK. Und das GKV-PDF "Zahlen, Daten, Fakten zu freiberuflichen Hebammen"
  (Stand 31.10.2025), nicht auslesbar.

## Aus dem Camping-Lauf (2026-08-29)

- **Bruttoumsatz einer Branche ist nie der Umsatz der Betriebe.** Camping: 20,8 Mrd EUR
  ueber alle Wertschoepfungsstufen, dwif-Multiplikator 11,8 — Standortpolitik, kein
  Marktvolumen. Fuer Frage 2 taugt nur Umsatzsteuerstatistik oder Menge mal Preisindex.
- **Vierter Fall Verband-als-Wettbewerber: BVCD/CampNerd**, 2022 vom Verband und seinen
  Mitgliedern gegruendet, dazu ein eigener Marktplatz. Keine Ausnahme mehr, sondern die
  Regel. Frage 6 beginnt ab jetzt mit "<Verband> GmbH gegruendet Digital".
- **Schnittstellenlisten eines Zusatzanbieters sind die schnellste Anbieterzaehlung** —
  Camping-Strom nennt zwoelf Verwaltungssysteme namentlich, aktueller als jedes Portal.
- **Segmentgroesse als Vorfilter ernster nehmen.** 3.100 Betriebe sind ein Dreizehntel von
  Physio. Unter etwa 10.000 Betrieben muss die Luecke aussergewoehnlich sein.
- Sperren, kein zweiter Versuch: bvcd.org 403, bvcd.de Zertifikat, campen.de 403,
  prowi-software.de kein DNS, prowi.net TLS. Umweg ueber pincamp.de (ADAC) und Presseseiten.
- Offen geblieben: Wie viele der 3.100 Plaetze arbeiten ganz ohne Verwaltungssoftware?
  Keine Quelle sagt es. Und: 650.000 gegen rund 107.000 Dauerstandplaetze — zwei Angaben
  derselben Quelle widersprechen sich. Fuer den Rechercheur.

## Aus dem Speditionslauf (2026-08-29)

*Vorbemerkung: Die Datei stand beim Anhaengen bereits ueber 12.000 Zeichen. Eine Fassung
vor diesem Abschnitt liegt als `archiv/markt-analyst-2026-08-29-5.md`. Der naechste Lauf
sollte rotieren und die vier Lauf-Abschnitte am Ende in die Themenblöcke einarbeiten —
sie doppeln sich inzwischen stark.*

- **Ein Anbietervergleichsportal beantwortet Frage 5 in einem Abruf, mit Preisen.**
  speditionssoftware-vergleich.com listete 25 Loesungen samt Zielgruppe und Listenpreis.
  Suchmuster: "<Segment>software Vergleich Anbieter Preise". Existiert eines, ist das
  Segment fast immer `gering` — die Uebersicht selbst ist der Befund.
- **"Das schreit nach einem Sprachmodell" ist 2026 kein Befund, sondern eine Warnung.**
  Die offensichtlichste LLM-Aufgabe des Segments — Transportauftraege aus E-Mail und PDF
  ins TMS tippen, 3 bis 10 Minuten je Auftrag — hatte bereits sechs zugeschnittene deutsche
  Anbieter *und* wurde vom Kernsystem eingebaut. Vorabruf: "KI <Vorgang> <Segment>
  Anbieter". Zwei Minuten, ersetzt den Rest des Laufs.
- **Groesse und Kanal sind notwendig, nicht hinreichend; Frage 5 entscheidet allein.**
  Spedition hatte 46.902 Betriebe (groesste Zahl aller Profile) und mit
  **forum-speditionen.de** den ersten Peer-Kanal, der eine Messung besteht: 13.477
  Mitglieder, 166.723 Beitraege, getrennte Unterforen fuer Spediteure (15.240 Beitraege)
  und fuer Software (3.177). Trotzdem `gering`: ueber 30 zugeschnittene Anbieter auf allen
  drei Schichten, Preisboden 0 EUR (Lavid IT.S FAIR, IMPARGO). Die Lehre "Peer-Foren sind
  als Kanal tot" gilt damit fuer Handwerk und Hausverwaltung, nicht allgemein.
- Zwei Ergaenzungen zu bekannten Tests: **Der Hersteller des Pflichtgeraets verkauft die
  Auswertesoftware** (VDO/Continental beim Tachographen) — "<Pflichtgeraet> Hersteller
  Software". Und in die Rechtsgrundlagen-Pruefung gehoert **"<Pflicht> EuGH"**: die
  Rueckkehrpflicht des Mobilitaetspakets, ein sauberer Nachweisvorgang, ist per Urteil
  gefallen.
- **Behoerdenstatistik-Umweg bestaetigt:** Der BALM-Band USTAT 19 blieb als PDF zu, die
  Pressemitteilung dazu nannte die Kernzahl, die Fachpresse (eurotransport) die Tabelle.
  Frage 2 blieb trotzdem offen — vier amtliche Umsatzquellen alle binaer.
- Offen fuer den Rechercheur: **Transportauftraege je Tag in einem Betrieb mit 1 bis 3
  Fahrzeugen.** Meine Annahme von 2 je Fahrzeug traegt die ganze Kostenrechnung des Profils.
- Sperren: eurotransport.de teils HTTP 410, ihk.de teils 403, de.statista.com
  Redirect-Schleife, forum-speditionen.de Unterforum-URLs 404 (Threads: `/<slug>-<id>`).
