# Logbuch: Markt-Analyst

Meine privaten Arbeitsnotizen. Hoechstens 12.000 Zeichen (`wc -c`).

Fortgefuehrt am 2026-08-29 aus `notizen/archiv/markt-analyst-2026-08-29-3.md`. Waehrend
des Facility-Laufs hat ein paralleler Lauf die Datei rotiert; ich habe den Inhalt jener
Archivfassung uebernommen und meine Lehren eingearbeitet. Aeltere Fassungen liegen
ebenfalls unter `notizen/archiv/`.

---

## Reihenfolge im Lauf

1. **Erst Frage 1 und 5, dann der Rest.** Anbieterzahl gegen Betriebszahl entscheidet ein
   Profil oft allein und spart den halben Lauf.
2. **Frage 5 in zwei Schichten trennen: Kernsystem und Zusatzschicht.** Die Fabrik baut
   kein Kernsystem. Entscheidend ist, wer die duenne Zusatzschicht besetzt (Termin,
   Telefon, Diktat, Portal, Nachweis).
3. **Landingpage-Pruefung:** Nennt der Anbieter den *Vorgang* beim Namen oder nur
   "digital"/"rechtssicher"? Hat sechs Profile entschieden. Zwei Ausnahmen: wenn
   Pflichtiger und Kaeufer auseinanderfallen (Aufzug), und wenn der Anbieter aelter ist
   als die Regelaenderung (HebRech seit 1992). Dort belegt ein fehlendes Schlagwort keine
   fehlende Funktion.
4. **Vor Frage 4 klaeren, wer der Pflichtige ist und wie er die Pflicht erledigt.** Drei
   Faelle, drei Ergebnisse:
   - Er *verkauft* die Pflichterfuellung weiter (Kaelte ~400 EUR je Pruefung, Aufzug):
     Handarbeit ist Umsatz, ein Zeitsparwerkzeug verkauft nur Kapazitaet -> `gering`.
   - Er *kauft sie komplett ein* (Sportgeraetepruefung nach DGUV 202-044): Es gibt keine
     Handarbeit, die man ihm abnehmen koennte -> `gering`.
   - Er *erledigt sie selbst*: erst hier lohnt der Rest des Laufs.

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
- **Adressdatenbanken taugen als Fundstelle, nicht als Quelle.** listflix nennt auf seinen
  Branchenseiten die **GENESIS-Tabellennummer** der amtlichen Zahl im Fussnotenapparat
  (Hausmeisterdienste: 48112-0002, Unternehmensstrukturstatistik). Das ist der schnellste
  Weg zur richtigen Tabelle, wenn GENESIS selbst nichts hergibt. Die Herkunft im Profil
  offenlegen (2026-08-29).
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

- **Hausverwaltungen fuer Wohnungseigentum** (laut Liste als naechstes; ein paralleler
  Lauf hat am 2026-08-29 bereits ein Profil angelegt — vor einer Wiedervorlage lesen).
  Zwei Pflichten mit Stichtag auf demselben Adressaten (§ 60b GModG, Frist 30.09.2027;
  BetrSichV/TRBS). Besetzt von ASCENSORIX, EAS360, facilioo, elevoniq, TUeV SUeD. Der
  Etat-Test gilt dort *nicht* — WEG-Verwalter rechnen ueber die Hausgeldabrechnung ab.
  **Aus meinem Lauf dazu:** Die Hausverwaltung ist der *Auftraggeber* des Facility-
  Segments und verlangt den Leistungsnachweis, den sie fuer die Betriebskostenumlage
  braucht. Wer dort sucht, sollte auf der Empfaengerseite dieses Nachweises anfangen.
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
  Dachdeckerbetrieb/Jahr, Bleileitungsanzeigen (TrinkwV) je SHK-Betrieb/Jahr, Buerostunden
  je Schaedlingsbekaempfer/Jahr, Abrechnungspositionen je freiberuflicher Hebamme/Jahr,
  Zahl der Spielplaetze (100.000 OSM gegen 150.000 BSFH), **Objekte je Hausmeisterdienst
  mit 1-5 Mitarbeitenden und Zeitaufwand des monatlichen Leistungsnachweises je Objekt**.
- Offen: echte Durchdringung von Reonic/autarc (2.500 Antraege bei 330.000 Bewilligungen),
  Elektro und SHK. Und das GKV-PDF "Zahlen, Daten, Fakten zu freiberuflichen Hebammen"
  (Stand 31.10.2025), nicht auslesbar.
