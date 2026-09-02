---
typ: prozess
erfasst: 2026-08-30
auftrag: Ausgefallene Termine kurzfristig wiederbesetzen
vorgang: Ein fest vergebener, personengebundener Termin faellt binnen Stunden aus; der Betrieb muss die frei gewordene Zeitspanne aus einem Bestand wartender Kunden neu besetzen, sonst ist die Kapazitaet unwiederbringlich verloren
branchen:
  - name: Zahnarztpraxen Deutschland | betriebe: 37.423 | quelle: KZBV, Statistisches Jahrbuch 2025, Berichtsjahr 2024, kzbv.de bzw. gesundheitsmarkt.de, abgerufen 2026-08-30
  - name: Physiotherapiepraxen Deutschland | betriebe: 40.113 | quelle: signals/maerkte/2026-08-29-physiotherapiepraxen.md (GKV-Spitzenverband, Stand 30.04.2022)
  - name: Tierarztpraxen Deutschland | betriebe: 10.385 | quelle: signals/maerkte/2026-08-29-tierarztpraxen.md (Bundestieraerztekammer, Stand 31.12.2025)
  - name: Fahrschulen und selbstaendige Fahrlehrer, englischsprachiger Raum | betriebe: 76.537 | quelle: signals/maerkte/2026-08-30-fahrschulen-englischsprachiger-raum.md (IBISWorld/DIA/RSA/ABS)
vereinigung: 164.458 Betriebe -- und das ist eine Untergrenze; die Arztpraxen fehlen darin, weil keine belegte Gesamtzahl auffindbar war (siehe 2)
kern: Der Kalender meldet einen Ausfall, ein Bestand wartender Kunden mit hinterlegten Wunschzeiten wird danach durchsucht, die Passenden werden benachrichtigt, der Erste bucht die Luecke zurueck in denselben Kalender
schale: Wonach "passend" heisst (Behandlungsart, Behandler, Fahrweg zum Schueler), ueber welchen Kanal benachrichtigt wird und welche Absage- und Anzahlungsregel gilt
schale_groesser_als_kern: nein
horizontal_besetzt: ja
horizontal_werkzeug: Mindestens fuenf, alle mit eigener Landingpage genau zu diesem Vorgang -- Acuity Scheduling (Warteliste ab Standard, 27-34 USD im Monat), Square Appointments (Waitlist ab Plus, 49 USD), Fresha ("Intelligent Waitlist" mit Priorisierung nach Reihenfolge oder Kundenwert), Waitwhile (branchenneutrales Wartelistenprodukt, 0 / 31 / 55 USD), Doctolib (Algorithmus prueft alle 10 Minuten auf Absagen). Eine Funktion des Kerns, die keines von ihnen kann, habe ich nicht gefunden
vertikal_anbieter: mindestens 10 -- Arzt/Zahnarzt DE: Dr. Flex (digitale Nachrueckerliste, ab 39 EUR im Monat oder 3,99 EUR je nachbesetztem Termin), medatixx (Termin-Warteliste im Praxisverwaltungssystem), cituro; Dental US: Weave (ab 249 USD), Doctible EasyFill (ab 329 USD, wirbt mit 44 Prozent automatisch nachbesetzter Absagen), NexHealth (ab rund 350 USD), Solutionreach; Medizin US: DoctorConnect, CertifyHealth, Echo Booking; Fahrschulen: acht UK-Anbieter laut Marktprofil
erreichbar_ueber: ein gemeinsamer Suchkanal existiert und ist von den horizontalen Anbietern belegt -- Acuity und Square unterhalten je eine eigene Seite unter dem Stichwort "waitlist software"
suchwort: "waitlist software" / "fill last-minute cancellations", deutsch "Warteliste Termine nachbesetzen" / "digitale Nachrueckerliste" -- ueber alle Branchen dasselbe
preis_plausibel: 39 EUR je Kunde und Monat (Dr. Flex Grundpaket, deutscher Anbieter, der genau diesen Vorgang ueber sechs Fachrichtungen hinweg verkauft; die einzige veroeffentlichte Einzelpreisangabe fuer den Vorgang allein sind 3,99 EUR je erfolgreich nachbesetztem Termin)
kunden_erreichbar: 164 (ein Promille von 164.458) -- Promille, weil der gemeinsame Kanal zwar existiert, aber von Acuity, Square, Fresha und Doctolib mit eigenen Landingpages besetzt ist. Zum Vergleich das nicht zulaessige Prozent: 1.645
monatsumsatz: 6.396 EUR (Promille); 64.155 EUR bei einem Prozent
traegt_5000: knapp
befund: tot
---

# Einen ausgefallenen Termin binnen Stunden neu besetzen -- 164.458 belegte Betriebe machen das, und es ist in jedem Kalenderprodukt bereits eine Haken-Funktion

Dies ist das erste Profil dieser Rolle, in dem die **Rechnung die Schwelle traegt und der
Befund trotzdem `tot` lautet**. Die beiden Felder widersprechen sich nicht: Die
Vereinigung ist gross genug, aber der Vorgang ist kein Produkt, sondern eine Funktion in
einem Kalender, den man nicht besitzt. Abschnitt 7 rechnet das aus, Abschnitt "Die Luecke"
begruendet es.

## 1. Der Vorgang

> Ein fest vergebener, **personengebundener** Termin faellt **binnen Stunden** aus; der
> Betrieb muss die frei gewordene Zeitspanne aus einem **Bestand wartender Kunden** neu
> besetzen, sonst ist die Kapazitaet unwiederbringlich verloren.

Drei Merkmale trennen ihn von allem, was ihm aehnelt. Sie sind die Pruefliste fuer
Abschnitt 2:

- **Verderbliche Kapazitaet.** Der leere Stuhl, das leere Auto, die leere Liege um 14 Uhr
  ist um 15 Uhr nicht nachholbar. Wer stattdessen einen Auftragsbestand abarbeitet,
  verschiebt nur -- er verliert nichts.
- **Personengebunden und zeitgebunden.** Der Termin gehoert einem bestimmten Behandler
  oder Fahrlehrer zu einer bestimmten Stunde. Ein austauschbarer Slot bei austauschbarem
  Personal ist ein Auslastungsproblem, kein Wiederbesetzungsproblem.
- **Nachfrageueberhang.** Es gibt einen Bestand von Kunden, die genau diese Stunde haben
  wollen. Ohne ihn ist nichts nachzubesetzen, und die Aufgabe verwandelt sich in Werbung.

**Das dritte Merkmal ist das strengste**, und es ist der Grund, warum die Vereinigung in
Abschnitt 2 kleiner ausfaellt, als der Vorgang zunaechst vermuten laesst. Belegt ist der
Ueberhang fuer die Facharztseite: In der GKV-Versichertenbefragung 2025 warten **25 Prozent
der Befragten laenger als 30 Tage** auf einen Facharzttermin (GKV-Spitzenverband,
Befragung von 3.520 Versicherten vom 21.02. bis 25.03.2025, abgerufen 2026-08-30).

## 2. Wer ihn macht

| Branche | Land | Betriebe | verderblich? | personengebunden? | Ueberhang? | zaehlt? |
|---|---|---:|---|---|---|---|
| Zahnarztpraxen | DE | 37.423 | ja | ja | ja | **ja** |
| Physiotherapiepraxen | DE | 40.113 | ja | ja | ja | **ja** |
| Tierarztpraxen | DE | 10.385 | ja | ja | ja | **ja** |
| Fahrschulen | US/UK/IE/AU | 76.537 | ja | ja | ja | **ja** |
| **Vereinigung** | | **164.458** | | | | |
| Arztpraxen | DE | keine Zahl | ja | ja | ja | nicht gezaehlt |
| Friseursalons | DE | 80.118 | ja | teils | **nein** | nein |
| Ambulante Pflegedienste | DE | 15.549 | nein | ja | **nein** | nein |
| SHK-, Elektro-, Dachdeckerbetriebe | DE | 108.000 | **nein** | nein | nein | nein |
| Campingplaetze, Ferienwohnungen | DE | 3.200 | ja | **nein** | teils | nein |

**Warum die fuenf herausfallen:**

- **Arztpraxen (nicht gezaehlt, obwohl der Vorgang passt).** Der Vorgang trifft hier am
  staerksten zu -- Dr. Flex, Doctolib und medatixx verkaufen ihn genau diesen Praxen. Aber
  **keine der geprueften Quellen nennt eine Gesamtzahl der Arztpraxen**: Die
  Destatis-Pressemitteilung zur Kostenstruktur 2024 (PD26_262 vom Juli 2026, abgerufen
  2026-08-30) nennt nur 854.000 EUR Durchschnittseinnahmen je Praxis und weist ausdruecklich
  darauf hin, dass aus einer Stichprobe von hoechstens 7 Prozent hochgerechnet wird; die
  KBV-Gesundheitsdaten zeigen die Praxiszahl nur in interaktiven Grafiken. Nach der Regel
  "im Zweifel weglassen" bleibt sie draussen. **Die Vereinigung ist damit um eine
  Groessenordnung von 70.000 bis 100.000 Betrieben zu klein angegeben** -- was das Urteil
  nicht dreht, weil es an Frage 4 haengt.
- **Friseursalons (80.118, Handwerksrolle Ende 2025, Zentralverband des Deutschen
  Friseurhandwerks, abgerufen 2026-08-30).** Zwei der drei Merkmale sind erfuellt, das
  dritte nicht: Der durchschnittliche Salon hat freie Kapazitaet, nicht zu wenig. Der
  Betriebsbestand sinkt, die Branche wirbt um Kunden. Der Ueberhang existiert beim
  einzelnen gefragten Stylisten, nicht in der Branche -- und Branchen zaehlt dieses Profil,
  nicht Einzelfaelle. **Gegenbeleg, der dagegen spricht:** Acuity nennt Friseure und
  Massagetherapeuten als ersten Anwendungsfall seiner Warteliste, Fresha zielt mit der
  "Intelligent Waitlist" ausdruecklich auf Salons. Die Anbieter zaehlen sie also mit. Ich
  lasse sie weg und mache die Vereinigung damit kleiner, nicht groesser.
- **Ambulante Pflegedienste (15.549).** Der Ausfall wird nicht durch einen anderen Kunden
  ersetzt, sondern die Leistung wird nachgeholt oder faellt aus; bezahlt wird vom
  Kostentraeger nach erbrachter Leistung. Was dort taeglich anfaellt, ist **Ausfallplanung
  von Personal auf einer festen Tour**, nicht Wiederbesetzung durch einen wartenden
  Kunden. Anderer Vorgang.
- **SHK, Elektro, Dachdecker (rund 108.000).** Hier fehlt das erste Merkmal. Sagt ein
  Kunde ab, faehrt die Kolonne den naechsten Auftrag aus dem Bestand -- die Kapazitaet ist
  nicht verderblich, sondern nur umgeplant. Deshalb heisst das Werkzeug dort auch
  Plantafel und nicht Warteliste.
- **Campingplaetze und Ferienwohnungen (3.200).** Eine stornierte Uebernachtung ist
  verderblich, aber nicht personengebunden, und der "Bestand Wartender" ist der offene
  Markt ueber Buchungsportale. Das ist Revenue-Management, ein eigener Vorgang mit eigener
  Werkzeugkategorie.

## 3. Kern und Schale

**Kern, in allen vier Branchen identisch -- fuenf Schritte:**

1. Der Kalender erkennt, dass ein besetzter Slot frei geworden ist.
2. Ein Bestand wartender Kunden mit hinterlegten Wunschzeiten und Wunschleistungen wird
   danach durchsucht.
3. Die Passenden werden benachrichtigt, per SMS oder E-Mail.
4. Eine Vergaberegel entscheidet: der Erste, der Hoechstwertige, oder alle zugleich.
5. Die Buchung geht **zurueck in denselben Kalender**, aus dem der Ausfall kam.

**Schale, je Branche verschieden:** was "passend" bedeutet (Behandlungsart und Behandler
in der Praxis, Fahrweg und Ausbildungsstand beim Fahrschueler), der Benachrichtigungskanal
und die Absage- oder Anzahlungsregel. Auch hier sind das **Stammdaten, keine
Programmlogik** -- eine Matching-Regel und eine Textvorlage.

Damit lautet die Antwort formal "Schale kleiner als Kern". Nach der Lehre aus dem ersten
Profil dieser Rolle ist das **kein** Fundsignal, sondern das Gegenteil: Ist der
branchenneutrale Kern gross, hat ihn jemand gebaut. Abschnitt 4 nennt fuenf.

Und Schritt 5 ist der eigentliche Befund dieses Profils. Er lautet nicht "in einen
Kalender", sondern **"zurueck in denselben Kalender"**. Der Vorgang beginnt und endet im
Terminbuch. Wer ihn allein anbietet, braucht Lese- **und Schreibzugriff** auf ein System,
das ihm nicht gehoert und dessen Hersteller dieselbe Funktion beilegt.

## 4. Das horizontale Werkzeug

**Es gibt nicht eines, sondern mindestens fuenf, und alle fuehren eine eigene Seite genau
zu diesem Vorgang.** Alle abgerufen 2026-08-30:

| Werkzeug | Was es tut | Preis |
|---|---|---|
| **Acuity Scheduling** | Kunde traegt sich auf der Buchungsseite in die Warteliste ein und waehlt Wunschzeiten; wird ein passender Termin frei, kommt eine SMS mit Sofortbuchung. Der Betrieb legt fest, wie kurzfristig noch vergeben wird | 34 USD monatlich, 27 USD jaehrlich (Tarif Standard; Warteliste ab Standard, SMS noetig) |
| **Square Appointments** | Warteliste, Selbsteintrag ueber die Buchungsseite, automatische Benachrichtigung bei Luecke, Sperre gegen Mehrfachbenachrichtigung binnen sechs Stunden | ab Tarif Plus, 49 USD je Standort; nicht im Gratistarif |
| **Fresha** | "Intelligent Waitlist": gleicht freie Slots mit Wartenden nach Leistung und Mitarbeiter ab; Vergabe wahlweise Erster in der Reihe, Hoechstwertiger oder alle zugleich | je buchbarem Mitarbeiter, monatlich kuendbar |
| **Waitwhile** | branchenneutrales Wartelistenprodukt mit Terminbuchung, SMS-Benachrichtigung | **0** / 31 / 55 USD |
| **Doctolib** | Algorithmus prueft den Kalender **alle 10 Minuten** auf Absagen und mailt den ersten acht Wartenden; Praxis kann Offline-Patienten selbst eintragen | Praxistarif, nicht oeffentlich |

**Was die horizontalen Werkzeuge nicht koennen, konnte ich nicht benennen.** Ich habe die
fuenf Kernschritte aus Abschnitt 3 einzeln gegen Acuity und Fresha gehalten:
Selbsteintrag mit Wunschzeit, Ausfallerkennung, Matching, Benachrichtigung,
Vergaberegel, Rueckbuchung -- alle sechs sind ausgewiesene Funktionen, die Vergaberegel
bei Fresha sogar in drei Varianten.

**Der entscheidende Punkt ist aber nicht, dass es diese Werkzeuge gibt, sondern wie sie
den Vorgang verkaufen: als Haken in einem Tarif, nicht als Produkt.** Acuity legt die
Warteliste dem Standardtarif bei, Square dem Plus-Tarif, Doctolib der Praxisplattform,
medatixx dem Praxisverwaltungssystem. Damit ist der Preis fuer den Vorgang **allein** die
Differenz zweier Tarifstufen -- und im Fall von Waitwhile und dem Fresha-Modell null.
Nach der Preisdeckel-Lehre aus `notizen/lehren.md` ist das der haerteste denkbare Boden:
nicht ein billiger Wettbewerber, sondern gar kein separater Preis.

## 5. Die vertikalen Anbieter

Mindestens zehn, und sie sind hier **kein** positives Signal, sondern der Beleg, dass der
Vorgang auf beiden Achsen zugleich besetzt ist. Alle abgerufen 2026-08-30:

| Branche | Anbieter | belegter Preis |
|---|---|---|
| Arzt-/Zahnarztpraxen DE | **Dr. Flex** "digitale Nachrueckerliste" | **ab 39 EUR im Monat**; im Starterpaket **3,99 EUR je erfolgreich nachbesetztem Termin**, im Flatpaket enthalten |
| Praxen DE | medatixx (Termin-Warteliste mit Prioritaet direkt im PVS), cituro | im Systempreis enthalten |
| Dental US | Doctible **EasyFill** | ab 329 USD; Eigenangabe: 44 Prozent aller Absagen automatisch nachbesetzt |
| Dental US | Weave | ab 249 USD |
| Dental US | NexHealth | ab rund 350 USD je Standort |
| Medizin US | DoctorConnect, CertifyHealth, Echo Booking ("AI Waitlist Fill & Cancellation Backfill") | nicht veroeffentlicht |
| Fahrschulen UK/US | acht bzw. sechs zugeschnittene Anbieter, drei davon zum Preis null | 0 bis 26 GBP |

Die Frage der Rolle lautet: *Warum kann keiner von ihnen die Vereinigung heben?* Die
ehrliche Antwort ist dieselbe wie im ersten Profil dieser Rolle: **Sie muessen nicht --
Acuity, Square, Fresha und Waitwhile heben sie bereits.** Und Dr. Flex ist selbst schon
kein Branchenanbieter mehr, sondern ein halbhorizontaler: Die Produktseite nennt
Zahnmedizin, Kieferorthopaedie, Implantologie, Orthopaedie, Frauenheilkunde und
Allgemeinmedizin nebeneinander -- also sechs Segmente unter einem Kern, exakt der
Zuschnitt, den diese Rolle sucht, sechs Jahre zu spaet.

## 6. Der gemeinsame Kanal

**Es gibt ein branchenuebergreifendes Suchwort, und das ist hier die schlechte Nachricht.**

Englisch heisst es "waitlist software" oder "fill last-minute cancellations", deutsch
"Warteliste Termine nachbesetzen" beziehungsweise "digitale Nachrueckerliste". Es ist
tatsaechlich ueber die Branchen hinweg dasselbe -- was Frage 6 an sich positiv beantwortet.

Nur ranken darauf keine unbesetzten Seiten. Acuity betreibt unter
`acuityscheduling.com/learn/fill-slots-with-waitlist-software` eine eigene Landingpage,
Square unter `squareup.com/appointments/features/waitlist-software` ebenfalls. Dazu kommt
eine ganze Schicht Vergleichsinhalte fremder Anbieter, die dasselbe Wort besetzen
(certifyhealth, doctorconnect, ustechautomations mit je eigenen Ratgebern "Backfill 70
Prozent der Absagen").

Das ist dasselbe Muster wie beim Pruefnachweis: **Der gemeinsame Kanal existiert und
beweist, dass der Markt existiert -- er beweist zugleich, dass er bedient wird.**

## 7. Die Rechnung

**Preis.** Der belegte Anker ist **Dr. Flex mit 39 EUR im Monat**. Er ist der beste
verfuegbare, weil Dr. Flex den Vorgang ueber sechs Fachrichtungen hinweg verkauft und
seinen Preis veroeffentlicht. Die einzige Preisangabe fuer den Vorgang **allein** stammt
ebenfalls von dort: 3,99 EUR je erfolgreich nachbesetztem Termin -- bei zehn
nachbesetzten Terminen im Monat also rund 40 EUR, was den Ankerpreis unabhaengig
bestaetigt. Die US-Vertikalen (249 bis 350 USD) verkaufen komplette
Patientenkommunikation und taugen als Anker nicht.

**Kundenzahl.** Ein Promille von 164.458 sind **164 Betriebe**. Das Prozent waere nach G7
nur bei einem belegten *und erreichbaren* Kanal zulaessig; der Kanal aus Abschnitt 6 ist
belegt, aber von vier horizontalen Anbietern besetzt. Besetzt ist nicht erreichbar.

| Annahme | Kunden | Monatsumsatz |
|---|---:|---:|
| Promille (regelkonform) | 164 | **6.396 EUR** |
| Prozent (nicht zulaessig, zur Kontrolle) | 1.645 | 64.155 EUR |

**`traegt_5000: knapp` -- und diese Zahl ist der ehrlichste Teil des Profils, weil sie
das Urteil nicht stuetzt.** Zum ersten Mal traegt die Rechnung: 164 Kunden zu 39 EUR sind
6.396 EUR im Monat, die Schwelle liegt bei 129 Kunden, also 0,78 Promille. Die zweite
Achse tut also genau das, wofuer es sie gibt -- vier Branchen, die einzeln nie 5.000 EUR
tragen wuerden, tragen sie zusammen.

**Sie traegt nur unter einer Annahme, die nicht haltbar ist: dass man 39 EUR fuer diesen
Vorgang verlangen kann.** Die 39 EUR sind der Preis einer *Plattform*, die Terminbuchung,
Erinnerungen, Anamnese und Warteliste zugleich enthaelt. Wer nur die Warteliste verkauft,
tritt gegen einen Preisboden von null an (Waitwhile Gratistarif, Fresha, jeder
Standardtarif von Acuity aufwaerts) und muss nach der Preisdeckel-Lehre deutlich unter
dem Vollprodukt liegen. Bei 10 EUR sind es 1.640 EUR im Monat, bei 5 EUR 820 EUR.

Dazu ein Posten, den kein anderes Profil dieser Rolle hatte: **Jede Benachrichtigung
kostet Geld.** Der Vorgang funktioniert nur, wenn er sendet -- Acuity setzt aktivierte SMS
voraus. Bei acht benachrichtigten Wartenden je Ausfall und mehreren Ausfaellen je Woche
ist der Versand ein laufender Stueckkostenblock. Dass Dr. Flex und Doctolib per E-Mail
statt per SMS benachrichtigen, ist vermutlich genau deshalb so.

## Die Luecke

**Es klafft keine, und der Grund ist diesmal ein anderer als beim Pruefnachweis.**

Beim Pruefnachweis war die Vereinigung zu klein und obendrein besetzt. Hier ist die
Vereinigung gross -- 164.458 belegte Betriebe, tatsaechlich eher 250.000 mit den nicht
zaehlbaren Arztpraxen -- und die Rechnung traegt. Der Vorgang scheitert an seiner
**Bauart**, an Schritt 5 des Kerns:

> Die Buchung geht zurueck in denselben Kalender, aus dem der Ausfall kam.

Damit ist der Vorgang kein Produkt, sondern eine **Funktion des Terminkalenders**. Wer ihn
allein anbietet, muss den Ausfall in einem fremden System lesen und die Buchung in dasselbe
fremde System zurueckschreiben -- und der Eigentuemer dieses Systems ist zugleich der
Wettbewerber, der die Funktion beilegt. Acuity legt sie dem Standardtarif bei, Square dem
Plus-Tarif, Doctolib der Praxisplattform, medatixx sogar dem Praxisverwaltungssystem, und
Waitwhile verschenkt sie in einem Gratistarif. Das ist die **erste Zeile der
Befundtabelle**: Ein gutes horizontales Werkzeug loest den Vorgang, der Preisboden steht,
und er steht bei null.

Der einzige Rest ist die Schale, und die traegt nichts: Das Fahrschulprofil hat sie
benannt -- der Anrufer will nicht irgendeinen Termin, sondern *die Stunde am Dienstag um
14 Uhr, zwoelf Minuten von seiner Adresse*. Fahrwegabstand ist eine Matching-Regel, also
eine Stammdatenzeile, und die acht UK-Fahrschulanbieter liefern sie bereits mit, drei
davon zum Preis null.

**Zwei Beobachtungen fuer die Fabrik, die ueber diesen Vorgang hinausgehen:**

1. **Ein Vorgang, der in einem fremden Kalender beginnt und endet, ist fuer diese Fabrik
   strukturell verschlossen** -- unabhaengig von Groesse und Preis. Das ist ein Kriterium,
   das sich vor jeder Zaehlung pruefen laesst und einen ganzen Profillauf spart. Es steht
   neben, nicht anstelle der Frage nach dem horizontalen Werkzeug: Hier haetten *beide*
   Pruefungen dasselbe Urteil ergeben, aber die Bauartpruefung waere in zwei Minuten
   fertig gewesen.
2. **`traegt_5000` und `befund` sind zwei verschiedene Fragen, und dieses Profil ist der
   erste Fall, in dem sie auseinanderfallen.** Die zweite Achse funktioniert -- vier
   Segmente mit `potenzial: gering` ergeben zusammen eine tragende Rechnung. Dass sie
   trotzdem nichts hergeben, liegt nicht an der Groesse. Das ist ein Beleg **fuer** ADR
   0005 und gegen die Vermutung, die Vereinigungsrechnung sei nur eine Methode, kleine
   Maerkte gross zu reden.

## Was unklar ist

- **Die Arztpraxen fehlen in der Vereinigung**, obwohl sie der groesste und passendste
  Teil waeren. Weder Destatis noch die KBV veroeffentlichen eine frei abrufbare
  Gesamtzahl der Praxen; Destatis rechnet aus einer Stichprobe von hoechstens 7 Prozent
  hoch, die KBV zeigt die Zahl nur in interaktiven Grafiken. **Wer diese Zahl findet,
  hebt jede kuenftige Vereinigung im Gesundheitswesen.** Sie haette das Urteil hier nicht
  gedreht.
- **Die Physiotherapiezahl ist vier Jahre alt** (Stand 30.04.2022) und im Ursprungsprofil
  selbst umstritten -- konkurrierende Angaben reichen von 31.478 bis 50.888.
- **Der Nachfrageueberhang ist nur fuer die Facharztseite belegt** (GKV-Befragung 2025,
  25 Prozent ueber 30 Tage Wartezeit). Fuer Zahnarzt-, Physio- und Tierarztpraxen habe ich
  ihn angenommen, nicht gemessen; fuer Fahrschulen stuetzt er sich auf die Ausfallquote
  von 10 Prozent aus einer Anbieterrechnung. **Faellt der Ueberhang in einer dieser
  Branchen weg, faellt sie aus der Vereinigung** -- das Urteil haengt daran nicht, die
  Zahl schon.
- **Fresha veroeffentlicht keinen Stueckpreis**, sondern rechnet je buchbarem Mitarbeiter
  ab; Doctolib, medatixx und die drei US-Medizinanbieter nennen gar keine Preise. Der
  Preisanker steht damit auf Dr. Flex, Acuity, Square, Waitwhile und den drei
  Dental-Anbietern.
- **Ich habe die Warteliste in keinem der fuenf horizontalen Werkzeuge benutzt**, sondern
  Herstellerseiten und Hilfeartikel gelesen. Wie gut das Matching tatsaechlich ist -- etwa
  ob Acuity mehrere Wunschzeitfenster je Kunde kann --, ist damit nicht geprueft. Bei
  einem Urteil `tot` waere das die Stelle, an der es kippen koennte; die Zahl der
  unabhaengigen Anbieter mit derselben Funktion faengt den Zweifel jedoch auf.
