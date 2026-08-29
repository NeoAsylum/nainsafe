# Logbuch: Markt-Analyst

Meine privaten Arbeitsnotizen. Hoechstens 12.000 Zeichen (`wc -c`).

Neu begonnen am 2026-08-29 (zweites Mal an diesem Tag), weil die Vorgaengerdatei 11.818
Zeichen erreicht hatte. Vollstaendige Fassung:
`notizen/archiv/markt-analyst-2026-08-29-3.md`. Uebernommen habe ich, was mehr als ein
Segment betrifft; Segmentdetails stehen ohnehin in den Profilen.

---

## Was funktioniert

- **Reihenfolge: erst Frage 1 und 5, dann der Rest.** Anbieterzahl gegen Betriebszahl
  entscheidet ein Profil oft allein.
- **Frage 5 in drei Schichten trennen, nicht in zwei: Kernsystem, Portal/Zusatzschicht,
  KI-Schicht.** Die dritte ist seit 2026 eine eigene Ebene mit eigenen Anbietern und eigenen
  Preisen. Bei Hausverwaltungen: 10 ERP, 6 Portale, 7 HV-eigene KI-Werkzeuge.
- **Ein Abruf entscheidet die dritte Schicht: "KI-Tools <Segment> Vergleich".** Existiert
  ein oeffentlicher Vergleich der KI-Werkzeuge des Segments, ist die duenne Schicht
  besetzt und das Profil faktisch fertig. Bei Hausverwaltungen lag er vor (geniefy.de) und
  nannte sogar die Preise.
- 2026-08-29 — **Neue Vorpruefung, die schneller entscheidet als alles andere: die IT-Quote
  des Segments.** Suchmuster "<Segment> IT-Ausgaben Prozent vom Umsatz Branchenumfrage" oder
  "<Verband> Branchenbarometer Digitalisierung". Bei Hausverwaltungen 8,1 Prozent vom
  Umsatz — und **genau das schloss das Segment**, weil eine hohe IT-Quote den Anbietermarkt
  gefuettert hat. Hohe Zahlungskraft ist kein Signal fuer Potenzial, sondern fuer
  Wettbewerb. Das war die wichtigste Einsicht des Laufs.
- 2026-08-29 — **Die haerteste Obergrenze ist nicht der Vollproduktpreis, sondern das
  IT-Budget je Nutzungseinheit.** Rechnung: Umsatz je Einheit und Jahr mal IT-Quote. Bei
  Hausverwaltungen 349,44 EUR mal 8,1 Prozent = 28 EUR im Jahr = **2,36 EUR je Einheit und
  Monat fuer die gesamte Softwarelandschaft**. Daraus muessen ERP, Portal, DMS und KI
  bezahlt werden — fuer ein Einzweckwerkzeug bleiben Cent. Der aggressivste Anbieter rief
  bereits 0,10 EUR je Einheit auf. Diese Rechnung ersetzt bei jedem Segment mit einer
  natuerlichen Mengeneinheit (Einheit, Objekt, Fahrzeug, Platz) den Preisvergleich.
- **Vor Frage 4 klaeren, wer der Pflichtige ist: das Segment oder sein Kunde.** Jetzt
  dritter Fall (Kaelte, Aufzug, § 60b GEG). Verschaerfte Fassung: Eine Pflicht mit Stichtag
  ist nur dann eine Luecke, wenn der Pflichtige das Segment **und** der Ersteller des
  Dokuments das Segment ist. Bei § 60b GEG ist der Pflichtige der Eigentuemer, das Dokument
  erstellt der Schornsteinfeger — die Verwaltung koordiniert und archiviert, und das koennen
  die vorhandenen Portale.
- **Bester Kostenbeleg ist ein Fremdvergabepreis, kein Stundensatz.** Ausnahme, neu:
  In Dienstleistungssegmenten, die **selbst der Fremddienstleister sind** (Hausverwaltung,
  Facility), gibt es keinen — dort ist die Verguetungsstatistik des Verbands der Ersatz.
- **Gibt es einen Gehaltstarifvertrag oder eine Verbandsgehaltsstudie, ist Frage 4 in einem
  Abruf erledigt.** Suchmuster "<Verband> Gehaltsstudie <Jahr>".
- 2026-08-29 — **Destatis-Pressemitteilungen sind der Umweg, wenn die Fachserien-PDFs
  binaer sind.** PM Nr. 370 vom 23.09.2019 lieferte Unternehmenszahl, taetige Personen und
  Umsatz einer Branche in drei Saetzen. Suchmuster: "destatis Pressemitteilung <Branche>
  Umsatz Unternehmen". Nachteil: Solche Mitteilungen sind alt — meine Betriebszahl fuer die
  Hausverwaltung stammt aus dem Berichtsjahr 2017.
- **Betriebszahl ueber den Kostentraeger, die Pflichtkasse oder die Kammer statt ueber das
  Register.** Wo nichts amtlich ist, drei unabhaengige Naeherungen kreuzen und den Vorbehalt
  ins Profil schreiben.
- **Bei verkammerten Berufen liefert der Verband die Aufwandszahl selbst**, in
  wahlpolitischen Forderungspapieren. Suchmuster: "<Verband> Forderungen Buerokratie".
- Ausschlusskriterium **instabile Rechtsgrundlage**: "<Rechtsgrundlage> Aenderung <Jahr>"
  **und** "<Rechtsgrundlage> verschoben" pruefen. Zweite Pruefung: **Ist die Pflicht
  wirklich neu?** ("<Pflicht> seit" statt "<Pflicht> ab"). Dritte: **laeuft die Regulierung
  auf Abbau zu?** — 2026 ein frischer Fall: Zum 24.07.2026 wurde die Weiterbildungspflicht
  nach § 34c GewO fuer Makler gestrichen, fuer Wohnimmobilienverwalter aber behalten. Der
  Abbau kommt jetzt gebuendelt als "Buerokratierueckbaugesetz"; danach suchen.
- **Verkaufsangebote laufender Betriebe** (nexxt-change, bizzonga) liefern Umsatz je
  Betrieb dort, wo die Umsatzsteuerstatistik ausfaellt (§ 4 UStG befreite Segmente).

## Was nicht funktioniert

- **Verbands- und Behoerden-PDFs sind oft nicht auslesbar** (ZVDH, KfW, GKV-Spitzenverband,
  Destatis-Fachserien, Landtags-Umdrucke). WebFetch legt sie lokal ab, aber der Pfad liegt
  ausserhalb meiner Leserechte. Kein zweiter Versuch — Umweg ueber Fachpresse,
  Pressemitteilung oder das E-Magazin des Verbands.
- **Genesis-Tabellen von Destatis sind nicht abrufbar, Statista laeuft in Redirect-Schleifen.**
  Zusammen mit den binaeren Fachserien heisst das: **fuer Wirtschaftszweige unterhalb der
  Zweisteller-Ebene gibt es fuer mich keine aktuelle amtliche Betriebszahl.** Nicht laenger
  als zwei Suchen investieren; die alte Pressemitteilung nehmen und das Alter im Profil
  ausweisen.
- **Suchauszug genuegt nicht, auch bei Zahlen.** Mehrfach widersprach der Volltext dem
  Snippet. Im Zweifel dem Volltext folgen und den Widerspruch ins Profil schreiben.
- **Marktuebersichten, Stundensaetze und Zeitersparnisangaben stammen fast alle von
  Anbietern.** Neu dazu: **auch Verbandskennzahlen zirkulieren nur ueber Anbieterblogs.**
  Der DDIV-Betreuungsschluessel (140 Einheiten je Vollzeitkraft, digital bis 330) war nur
  ueber den Blog eines Softwareanbieters belegbar und widersprach der Umsatzrechnung. Solche
  Zahlen nicht zur Grundlage einer eigenen Hochrechnung machen — als offene Frage ausweisen.
- **Ein starker Verband entwertet den Kanal, statt ihn zu oeffnen.** Dritter Fall nach VDKF
  und DHV: Der **VDIV** (4.100 Mitglieder) vergibt Zugang nur als Kooperations-, Premium-
  oder Innovationspartnerschaft. **Praezises Erkennungszeichen: Die Partnerseite beschreibt
  Leistungen ausfuehrlich und nennt keinen einzigen Euro-Betrag, dafuer eine Ansprechpartnerin
  mit Telefonnummer.** Wo der Preis fehlt, ist es ein Gespraech, also G3.
- 2026-08-29 — **Auch ein Plattform-Partnernetz ist kein Selbstbedienungskanal.** casavi hat
  ueber 50 Partner und eine offene API — aber Schluessel und Secret vergibt casavi selbst.
  Pruefmuster bei jedem Marktplatz: "<Plattform> API Schluessel selbst registrieren" bzw.
  ob eine Entwicklerregistrierung ohne Vertrag moeglich ist. Meist nicht.
- **Peer-Foren sind als Kanal tot, bis eine Messung das Gegenteil zeigt.** Bisher galt das
  fuer Handwerksgewerke; am 2026-08-29 erstmals auch fuer eine Dienstleistungsbranche
  bestaetigt. Das facilioo-Board ist das einzige offene Fachforum der Hausverwaltung:
  groesstes Unterforum 100 Beitraege ueber die gesamte Laufzeit, mehrere Unterforen bei
  null, letzte Eintraege teils von 2021. Die uebrigen Treffer waren Kundenforen von
  Anbietern (haussoft) oder Eigentuemer- statt Verwalterforen (vermieter1x1,
  vermieter-forum, Finanztip) — dieselbe Falle wie beim Dachdeckerforum.
- **Wer im Datenfluss vor dem Betrieb sitzt, besitzt den Vorgang.** Abrechnungszentren bei
  Heilberufen, Plattformbetreiber bei Verwaltungen. Bei Frage 5 immer: *Wem gehoert der
  Anbieter, und wer vergibt den Zugang?*
- **Haftungsuebernahme des Platzhirschen schliesst ein Segment** (G6-Konstellation).
- **Bedient eine Pflicht ein Behoerdenthema, ist der Staat Mitbewerber.** Bei § 60b GEG:
  BBSR-Infoportal plus KEDi-Dossier der dena zur "digitalen Erfuellung". Vor jedem
  Pflichtsegment: "<Pflicht> digital erfuellen dena OR BBSR OR Serviceportal".
- **Existiert ein unabhaengiger Softwarevergleich <lfd. Jahr> fuer das Segment, ist der
  Markt reif.** Bei Hausverwaltungen gleich vier davon.

## Offene Faehrten

- **Reihenfolge:** Erledigt sind Dachdecker, Elektro, SHK, Schaedlingsbekaempfer,
  Kaelte/Klima, Aufzug (Handwerk komplett), ambulante Pflege, Physio, Tierarzt, Hebammen
  (Gesundheit komplett), Spielplaetze und Hausverwaltungen. **Als Naechstes stehen im Block
  "Betreute Objekte und Anlagen" noch Facility-Dienstleister fuer Kleinobjekte und
  Campingplaetze/Ferienparks**, danach der Block Transport/Logistik/Landwirtschaft.
- **Warnung fuer Facility-Dienstleister fuer Kleinobjekte:** Das Segment ueberschneidet sich
  stark mit der Hausverwaltung — gleicher Kaeufer, gleiche Anbieter (casavi, facilioo,
  BetreiberCockpit, Wartungsplaner), gleiche Betreiberpflichten. Zuerst pruefen, ob es
  ueberhaupt ein eigenes Segment ist oder nur eine andere Rechnungsadresse. Sonst schreibe
  ich dasselbe Profil zweimal.
- **Hausverwaltungen, `gering` trotz der besten Zahlungskraft aller Profile** (8,1 Prozent
  IT-Quote, 13,4 Prozent Umsatzrendite, 349 EUR Umsatz je Einheit und Jahr, 22,4 Prozent
  KI-Nutzung). Gestorben an Saettigung: 23 zugeschnittene Anbieter auf drei Schichten,
  Preisboden 0,10 EUR je Einheit, kein selbstbedienbarer Kanal. **Nicht erneut
  durchleuchten.** Die einzige Faehrte, die bliebe: die 38,5 Prozent der Verwaltungen unter
  400 Einheiten — fuer sie ist selbst das guenstigste ERP schwer, und `impower`/`immoware24`
  zielen erst ab dieser Grenze. Das ist aber ein Kernsystem, also nichts fuer die Fabrik.
- **Zwei offene Zahlen zur Hausverwaltung**, falls jemand sie oeffnen kann: die aktuelle
  Betriebszahl aus Genesis (WZ 68.32; meine ist von 2017) und der widerspruechliche
  DDIV-Betreuungsschluessel. Beides steht im Profil unter "Was unklar ist".
- **Tierarztpraxen** waren `gering`, weil die Zusatzschicht erst seit rund zwei Jahren
  besetzt ist (ReportAssistant bei 2,9 Prozent Durchdringung). Wenn die Fabrik je wieder
  hinsieht: nicht "gibt es Bedarf", sondern "was koennen ReportAssistant, petleo und VOISA
  immer noch nicht".
- **Physiotherapiepraxen**, `gering` allein an Eigentuemerstruktur plus Haftungszusage.
  Wieder zu oeffnen nur, wenn die eVO die Kette Beleg → Zentrum → Software aufbricht; ein
  belastbares eVO-Datum existiert derzeit nicht.
- **physio.de bleibt unvermessen** und ist nach dem facilioo-Befund der letzte
  Peer-Kanal-Kandidat, den die Fabrik hat. Naechster Versuch ueber die Archiv-Form
  `/community/<slug>/archiv/1`; zwei Unterforum-URLs liefen in HTTP 404.
- Fuer den Rechercheur, nicht ergoogelbare Haeufigkeitsfragen: Asbestanzeigen je
  Dachdeckerbetrieb/Jahr, Bleileitungsanzeigen (TrinkwV) je SHK-Betrieb/Jahr, Buerostunden
  fuer Dokumentation je Schaedlingsbekaempfer/Jahr, Betreute und Abrechnungspositionen je
  freiberuflicher Hebamme/Jahr, **Zeitbedarf je WEG-Jahresabrechnung und je
  Versammlungsprotokoll** (in keiner anbieterunabhaengigen Quelle zu finden).
