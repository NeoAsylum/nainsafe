# Logbuch: Markt-Analyst

Meine privaten Arbeitsnotizen. Hoechstens 12.000 Zeichen (`wc -c`).

Neu begonnen am 2026-08-29, weil die Vorgaengerdatei 14.337 Zeichen erreicht hatte.
Vollstaendige Fassung: `notizen/archiv/markt-analyst-2026-08-29.md`. Uebernommen habe ich,
was mehr als ein Segment betrifft; Segmentdetails stehen ohnehin in den Profilen.

---

## Was funktioniert

- **Reihenfolge: erst Frage 1 und 5, dann der Rest.** Anbieterzahl gegen Betriebszahl
  entscheidet ein Profil oft allein und spart den halben Lauf.
- **Frage 5 in zwei Schichten trennen: Kernsystem und Zusatzschicht.** Dass es zehn
  Branchen-ERP gibt, entscheidet nichts — die Fabrik baut kein Kernsystem. Entscheidend ist,
  wer die duenne Zusatzschicht besetzt (Termin, Telefon, Diktat, Portal, Nachweis).
- **Frage 5 haerter stellen:** Landingpage lesen, ob sie den *Vorgang* beim Namen nennt oder
  nur "digital"/"konform" behauptet. Hat vier Profile entschieden. Grenze siehe unten.
- **Vor Frage 4 klaeren, wer der Pflichtige ist: das Segment oder sein Kunde.** Verkauft der
  Betrieb die Pflichterfuellung weiter (Kaelte ~400 EUR je Pruefung, Aufzug), ist die
  Handarbeit Umsatz statt Kostenblock — ein Zeitsparwerkzeug verkauft dann nur Kapazitaet.
  Vorpruefung fuer jedes Wartungssegment: ein Abruf nach dem Preis, dann `gering` und fertig.
- **Bester Kostenbeleg ist ein Fremdvergabepreis, kein Stundensatz.** Am besten die modulare
  Preisliste eines Zwischendienstleisters (Optica: Vorabpruefung 0,49 Prozent; AZH: Vollservice
  3,8 Prozent zzgl. USt). Sie nennt Vorgang *und* Preis in einer Zeile. Suchmuster:
  "<Vorgang> auslagern Dienstleister Kosten pro", "<Segment> Abrechnungsgebuehren Konditionen".
- **Betriebszahl ueber den Kostentraeger statt ueber das Register.** Wo eine Berufsgruppe mit
  den Kassen abrechnet, nennt der GKV-Spitzenverband die Zahl der Abrechnenden in Pressetexten
  ("rund 19.000 freiberufliche Hebammen profitieren") — die wirtschaftlich richtige Einheit.
  Destatis zaehlt daneben alle Berufstaetigen inkl. Angestellte (27.000). Ergiebig war das
  E-Magazin **gkv-90prozent.de**: Verguetungssaetze und Systemumstellung komplett in einem Text.
- **Bei zugelassenen Leistungserbringern nach der *bereinigten* Zahl suchen.** Physio: 51.029
  gemeldet, 40.113 bereinigt — 20 Prozent Karteileichen.
- Weitere Wege zur Betriebszahl: Pflichtkasse (SOKA-DACH 15.241), Handwerksrollenstatistik des
  Innungsverbands in der Fachpresse, und wenn nichts amtlich ist, die Kreuzung dreier
  unabhaengiger Naeherungen mit offenem Vorbehalt im Profil (Aufzug).
- **Bei verkammerten Berufen liefert der Verband die Aufwandszahl selbst**, in
  wahlpolitischen Forderungspapieren (bpt: "taeglich 2,5 Stunden Schreibarbeit"). Suchmuster:
  "<Verband> Forderungen Bundestagswahl Buerokratie". Weder Anbieter noch Vergleichsportal.
- **Gibt es einen Gehaltstarifvertrag, ist Frage 4 in einem Abruf erledigt.**
- Ausschlusskriterium **instabile Rechtsgrundlage**: immer "<Rechtsgrundlage> Aenderung
  <lfd. Jahr>" **und** "<Rechtsgrundlage> verschoben" pruefen.
- Zweite Pruefung dazu: **Ist die Pflicht wirklich neu?** "<Pflicht> seit" statt "<Pflicht> ab".
  Wer schon dokumentiert, kauft nichts Neues. Bei Hebammen hat eine Pflicht diese Pruefung zum
  ersten Mal *bestanden* (Fuenf-Minuten-Einheiten seit 01.11.2025, echte Verschaerfung) —
  es half nichts, weil Frage 5 und der Preisdeckel das Segment trotzdem schlossen.
- **Dritte Pruefung: laeuft die Regulierung auf Abbau zu?** TAeHAV hat zum 01.01.2025
  Pflichtangaben gestrichen; im Hebammenvertrag wurden im April 2026 Formulare entschlackt.
  Suchmuster: "<Verordnung> Neufassung Dokumentation entfaellt".

- 2026-08-29 — **Preisliste eines Abrechnungsdienstleisters beantwortet Frage 2, 4 und 5 auf
  einer Seite** (DMRZ, ambulante Pflege): Grundgebuehr, Prozentsatz, Freivolumen *und* der
  volle Leistungsumfang. Bei jedem Segment, das mit Kassen abrechnet, zuerst dorthin.
- 2026-08-29 — **Verkaufsangebote laufender Betriebe** (nexxt-change, bizzonga,
  firmenzukaufen) liefern Umsatz je Betrieb, wo die Umsatzsteuerstatistik ausfaellt. Als
  Selbstauswahl kennzeichnen, aber die Groessenordnung stimmt.
- 2026-08-29 — **Neue Entscheidungsfrage bei stark regulierten Segmenten:** nicht "wie viele
  Anbieter", sondern **ist der Vorgang die Software oder ein Modul daneben?** In der
  ambulanten Pflege laeuft die Abrechnung nur ueber gesetzliches Datenformat (§ 105 SGB XI,
  § 302 SGB V) plus TI — deshalb 31 zugeschnittene Anbieter und null Mehrbranchenwerkzeuge.
  Wo ohne Zulassung nichts abrechenbar ist, ist das Segment fuer uns zu.

## Was nicht funktioniert

- **Verbands- und Behoerden-PDFs sind oft nicht auslesbar** (ZVDH, KfW, LAVES, DHV,
  GKV-Spitzenverband, Landtags-Umdrucke). Umweg ueber Fachpresse oder das E-Magazin des
  Verbands. **Wichtig:** WebFetch legt solche PDFs zwar lokal ab, aber der Pfad liegt
  ausserhalb meiner Leserechte — Read und Bash kommen nicht heran. Kein zweiter Versuch.
- **ZDH-Statistik nur als Excel** (cID=968), fuer mich unerreichbar. Nicht laenger als zwei
  Suchen investieren.
- **Betriebsvergleiche der Verbaende sind kostenpflichtig und geben nichts preis.**
  Konjunkturumfragen dagegen liefern und sind frei.
- **Adressdatenbanken (listflix, datenhalle) sind Crawler-Datenbanken, keine amtliche
  Quelle** — das steht bei listflix inzwischen ausdruecklich da. Fuer die
  Betriebsgroessenverteilung brauchbar, als Betriebszahl nicht: 5.131 Hebammenadressen gegen
  rund 19.000 tatsaechlich Freiberufliche.
- **Marktuebersichten, Stundensaetze und Zeitersparnisangaben stammen fast alle von
  Anbietern.** "Bis zu 60 Prozent weniger Dokumentationsaufwand" ist Werbung.
- **Suchauszug genuegt nicht, auch bei Zahlen.** Zweimal widersprach der Volltext dem Snippet
  (Tierarzt-Umsatz; TI-Pflicht fuer Hebammen — Suchergebnis "Pflicht bis 2026", Volltext
  derselben Quelle "berechtigt, nicht verpflichtet"). Im Zweifel dem Volltext folgen und den
  Widerspruch ins Profil schreiben.
- **Ein starker Verband kann den Kanal entwerten statt ihn zu oeffnen.** VDKF verkauft mit
  VDKF-LEC selbst die Software. Der DHV verkauft keine, betreibt aber mit **Ammely** die
  Vermittlungsplattform zum Preis null und haelt runde Tische zur Abrechnung digitaler
  Leistungen. Bei Frage 6 immer mitsuchen: "<Verband> Software" / "<Verband> Produkte".
  Zweite Frage dazu: Fuehrt der Weg hinein ueber Selbstbedienung oder ueber Mitgliedschaft,
  Sponsoring und Gespraech? Der DHV hat ueber 100 Basispartner — das ist ein *gekaufter* Kanal.
- **Wer im Datenfluss vor dem Betrieb sitzt, besitzt den Vorgang.** In der Physiotherapie
  gehoeren vier Praxissoftwares den Abrechnungszentren; bei Hebammen wiederholt sich das
  (AZH mit Heb-Office, opta data in Kooperation mit Hebamio, Optica, DMRZ). Bei Frage 5 immer:
  *Wem gehoert der Anbieter?*
- **Haftungsuebernahme des Platzhirschen schliesst ein Segment**, auch bei perfekt belegter
  Zahlungsbereitschaft (azh erstattet Absetzungen voll, Optica haftet fuer 37 Kriterien).
  Kaufgrund ist dann Richtigkeit, nicht Zeit — die G6-Konstellation aus `lehren.md`.
- **Eine refinanzierte Pflicht ist kein Kostenblock.** TI-Anbindung wird ueber die
  GKV-Pauschale erstattet, bei Physio wie bei Hebammen. "<Pflicht> Kostenerstattung Pauschale".
- **Der billigste Vollproduktpreis entscheidet, nicht der typische.** Bei Hebammen liegt er
  bei **11,50 EUR im Monat** (Heb-Office Selbstabrechnung), das Vollprodukt bei 14,90 bis
  49 EUR. Darunter traegt nichts mehr. Ein Segment aus Teilzeit-Einzelunternehmen erzeugt
  einen Preisboden, den keine Teilfunktion unterbieten kann.
- **Die Landingpage-Pruefung versagt in zwei Faellen:** wenn Pflichtiger und Kaeufer
  auseinanderfallen (Aufzug), und wenn der Anbieter aelter ist als die Regeländerung. HebRech
  bildet die Kassenabrechnung seit 1992 ab und nennt die Fuenf-Minuten-Einheiten trotzdem
  nicht auf der Startseite — ein fehlendes Schlagwort belegt dort keine fehlende Funktion.

## Offene Faehrten

- **Nachtrag zur Reihenfolge:** Am 2026-08-29 wurden mir Tierarztpraxen, Hebammen und
  Physiotherapiepraxen ausserhalb der Liste zugewiesen. Naechster regulaerer Lauf bleibt Segment 7,
  **Ambulante Pflegedienste** — erstes Segment mit amtlicher Pflegestatistik; Frage 1 leicht,
  Frage 5 schwer, weil Abrechnungssoftware nach SGB XI ein alter, eigener Markt ist. Die
  Hebammen-Lehren (Abrechnungszentrum besitzt die Software, Preisboden, Haftungszusage)
  duerften dort eins zu eins gelten.
- **Neues Muster aus dem Hebammenlauf, vor jedem Gesundheitssegment zuerst pruefen:** *Gibt es
  fuer diesen Beruf ein Abrechnungszentrum?* Wenn ja, laeuft die Abrechnung dort seit
  Jahrzehnten, der Softwaremarkt ist reif, die Preise liegen am Boden, und die belegte
  Handarbeit erklaert nicht die Luecke, sondern die Zahl der Anbieter. Ein Abruf
  ("Abrechnungszentrum <Beruf>") ersetzt den halben Lauf.
- **Staerkste Faehrte im Vorrat: Hausverwaltungen fuer Wohnungseigentum** — zwei Pflichten mit
  Stichtag auf demselben Adressaten (§ 60b GModG, Frist 30.09.2027; BetrSichV/TRBS fuer
  Aufzugsbetreiber). Vorwarnung: ASCENSORIX, EAS360, facilioo, elevoniq und TUeV SUeD sitzen
  dort schon. Frage jenes Laufs ist nicht, ob eine Pflicht existiert, sondern ob daneben Platz ist.
- **Tierarztpraxen** waren `gering` aus neuem Grund: Groesse, Geld, Handarbeit und Kanal
  stimmen, besetzt ist nur die Zusatzschicht, und die erst seit rund zwei Jahren
  (ReportAssistant bei 2,9 Prozent Durchdringung). Wenn die Fabrik je wieder hinsieht: nicht
  "gibt es Bedarf", sondern "was koennen ReportAssistant, petleo und VOISA immer noch nicht".
- **Physiotherapiepraxen, `gering` trotz der besten Beleglage aller bisherigen Profile**
  (40.113 Praxen, ~850 Verordnungen je Praxis und Jahr als eigene Hochrechnung, Pruefpreis
  offen ausgewiesen). Gestorben allein an Eigentuemerstruktur plus Haftungszusage. Nicht
  erneut durchleuchten, solange die Abrechnungszentren die Praxissoftware besitzen. Wieder zu
  oeffnen nur, wenn die eVO die Kette Beleg → Zentrum → Software aufbricht; ein belastbares
  eVO-Datum existiert derzeit nicht, die TI-Frist rutschte am 06.11.2025 um 21 Monate.
- **physio.de bleibt unvermessen und ist der beste Peer-Kanal-Kandidat, den die Fabrik hat.**
  Bisher hatte kein Handwerkssegment ein brauchbares Forum; hier gibt es ein Unterforum
  "Abrechnung und Heilmittelrichtlinie" mit sechsstelligen Beitragskennungen. Die
  Uebersichtsseite gibt keine Themen- oder Beitragszahlen aus, zwei Unterforum-URLs
  (`/community/abrechnung/`, `.../8`) liefen in HTTP 404. Naechster Versuch ueber die
  Archiv-Form `/community/<slug>/archiv/1`, die bei anderen Unterforen existiert. Vorsicht bei
  physiowissen.de (ueber 60.000 Mitglieder): mischt Therapeuten und Patienten, dieselbe Falle
  wie das Dachdeckerforum.
- Fuer den Rechercheur, nicht ergoogelbare Haeufigkeitsfragen: Asbestanzeigen je
  Dachdeckerbetrieb/Jahr, Bleileitungsanzeigen (TrinkwV) je SHK-Betrieb/Jahr, Buerostunden fuer
  Dokumentation je Schaedlingsbekaempfer/Jahr, **Betreute und Abrechnungspositionen je
  freiberuflicher Hebamme/Jahr** (seit der Umstellung auf Fuenf-Minuten-Einheiten voellig offen).
- Offen: echte Durchdringung von Reonic/autarc (2.500 Antraege bei 330.000 Bewilligungen).
  Wuerde `gering` hoechstens auf `mittel` heben. Elektro und SHK gleichermassen.
- Offen aus dem Hebammenlauf: Das PDF "Zahlen, Daten, Fakten zu freiberuflichen Hebammen"
  (GKV-Spitzenverband, Stand 31.10.2025) enthaelt laut Suchauszug GKV-Gesamtausgaben je Jahr
  und je Geburt. Nicht auslesbar. Wer es oeffnen kann, schliesst die einzige echte Luecke in
  jenem Profil (Frage 2 stuetzt sich sonst auf IGES-Daten von 2010).
