---
typ: prozess
erfasst: 2026-08-30
auftrag: Wiederkehrende Pruefung mit gesetzlicher Frist und Nachweispflicht
vorgang: Ein Betrieb prueft fremde Objekte in einem gesetzlich vorgegebenen Turnus, protokolliert je Pruefung Ergebnis, Datum und Prueferidentitaet, uebergibt den Nachweis dem pflichtigen Objektbetreiber und verwaltet die naechste Faelligkeit ueber seinen gesamten betreuten Objektbestand
branchen:
  - name: Brandschutz-Fachbetriebe (Feuerloescher-Instandhaltung) | betriebe: 5.236 | quelle: listflix.de/statistik/brandschutzunternehmen, Stand 26.08.2026, Crawler-Datenbank, abgerufen 2026-08-30
  - name: Kaelteanlagenbauerhandwerk (Dichtheitspruefung F-Gase) | betriebe: 3.214 | quelle: signals/maerkte/2026-08-29-kaelte-und-klimaanlagenwartung.md (BIV-Handwerksrolle, 31.12.2022)
  - name: Schaedlingsbekaempfungsbetriebe (Koederstellen-Monitoring) | betriebe: 1.074 | quelle: signals/maerkte/2026-08-29-schaedlingsbekaempfer.md (Destatis WZ 81.29.2, Berichtsjahr 2019)
  - name: Aufzugswartungsbetriebe (Wartungs- und Prueffristen BetrSichV) | betriebe: 841 | quelle: signals/maerkte/2026-08-29-aufzugswartung-und-pruefdienste.md (Listflix, 26.08.2026)
vereinigung: 10.365 Betriebe -- nicht 65.433. Vier der sechs Branchen aus der Ausgangstabelle machen den Vorgang nicht (Begruendung unter 2)
kern: Objektbestand mit je eigener Frist fuehren, Faelligkeit rechnen, vor Ort ein Protokoll erfassen, den Nachweis an den Pflichtigen uebergeben, ihn aufbewahren
schale: Pruefkatalog, Fristformel, Protokollformular, Fachvokabular und Aufbewahrungsfrist je Rechtsgrundlage
schale_groesser_als_kern: nein
horizontal_besetzt: ja
horizontal_werkzeug: Certado Suite (39/79/139 EUR im Monat, ausdruecklich fuer externe Pruefdienstleister, ein Arbeitsbereich je Kunde, nennt DGUV 112-198, DGUV 305-002 und BetrSichV §§ 3, 10, 14) und HOPPE Wartungsplaner (ueber 25 Jahre am Markt, eigene Pruefdienstleister-Seite, 5.800 Kunden, 195 EUR einmalig Einzelplatz). Dazu RISK-Project Servo, ROnDo Cloud, Vemas.PDL, MS Consulting. Eine Luecke, die diese Werkzeuge nicht koennten, habe ich nicht gefunden -- der Kern ist genau ihr Funktionsumfang
vertikal_anbieter: 23 -- Kaelte 3 (VDKF-LEC, KlimaCraft 60 EUR/Monat, CoolTool), Aufzug 6 (Mainteny rund 19 EUR/Nutzer/Monat, Paternoster, es2000, COSMO CONSULT, orderbase, shm), Schaedlinge 5 (PestScan, BORIS PCS, PestDesk, traplinked, KoederCheck), Spielplatz 9 (StraKo, Spektor 99 EUR/Monat, SpielDex 0-9,99 EUR/Monat, Punchbyte, ARCHIKART, Kasper, Gaja, SMART Kompakt, Spielplatzmobil)
erreichbar_ueber: ein gemeinsamer Suchkanal existiert -- und er ist besetzt: auf "Pruefdienstleister Software" und "Prueffristen verwalten" ranken Certado und Wartungsplaner mit eigenen Landingpages
suchwort: "Prueffristen Software" / "Software fuer Pruefdienstleister" -- branchenuebergreifend dieselbe Anfrage
preis_plausibel: 39 EUR je Kunde und Monat (Certado Starter bei jaehrlicher Abrechnung; liegt zwischen Mainteny 19 EUR/Nutzer und KlimaCraft 60 EUR/Lizenz, unter Spektor 99 EUR)
kunden_erreichbar: 10 (ein Promille von 10.365) -- Promille, weil kein *freier* Kanal existiert; der gemeinsame Suchkanal ist von den beiden horizontalen Anbietern belegt. Zum Vergleich das nicht zulaessige Prozent: 104
monatsumsatz: 390 EUR (Promille); 4.056 EUR selbst bei einem Prozent
traegt_5000: nein
befund: tot
---

# Ein Betrieb prueft fremde Objekte im Pflichtturnus und fuehrt den Nachweis -- das machen nach ehrlicher Zaehlung 10.365 Betriebe und nicht 65.433, und zwei branchenuebergreifende Werkzeuge bedienen sie bereits

## 1. Der Vorgang

Gemeint ist nicht "Dokumentation" und auch nicht "wiederkehrende Pruefung" im weiten Sinn,
sondern dies:

> Ein Betrieb prueft **fremde** Objekte in einem **gesetzlich** vorgegebenen Turnus,
> protokolliert je Pruefung Ergebnis, Datum und Prueferidentitaet, uebergibt den Nachweis
> dem pflichtigen Objektbetreiber und verwaltet die naechste Faelligkeit ueber seinen
> gesamten betreuten Objektbestand.

Drei Merkmale trennen ihn von allem, was ihm aehnelt:

- **Fremdes Objekt.** Der Betrieb prueft nicht seine eigenen Arbeitsmittel, sondern die
  seines Kunden. Wer nur die eigene Leiter und den eigenen Gabelstapler pruefen laesst,
  macht einen anderen Vorgang -- er ist Pflichtiger, nicht Pruefer.
- **Gesetzliche Frist.** Der Turnus steht in einer Verordnung, einem Zulassungsbescheid
  oder einer technischen Regel, nicht in einem Vertrag. Er ist rechnerisch bestimmbar,
  meist aus einer Objekteigenschaft (CO2-Aequivalent der Fuellmenge, Anlagenart,
  Loeschmittel).
- **Nachweis mit Vorlagepflicht.** Das Protokoll ist aufzubewahren und auf Verlangen einer
  Behoerde oder eines Auditors vorzulegen.

**Die Rollentrennung ist der wichtigste Teil der Definition.** Bei jedem einzelnen dieser
Vorgaenge stehen zwei Parteien: der **Pflichtige** (Anlagenbetreiber, Arbeitgeber, Kommune)
und der **Pruefer** (Fachbetrieb, ZUeS, Sachkundiger). Beide beruehren dasselbe Protokoll,
aber sie haben gegenlaeufige Interessen: Fuer den Pflichtigen ist die Pruefung eine
Ausgabe, fuer den Pruefer eine Rechnung. Ein Werkzeug kann nicht beiden dieselbe Sache
verkaufen. Dieses Profil schneidet auf der **Prueferseite**; Abschnitt 2 begruendet, warum.

## 2. Wer ihn macht

**Die Ausgangstabelle dieser Rolle nennt sechs Branchen und 65.433 Betriebe. Vier davon
machen den Vorgang nicht.** Das ist der erste Befund des Profils, und er stammt aus den
`handarbeit`-Feldern selbst, nicht aus neuer Recherche.

| Branche | Betriebe | `handarbeit` laut Profil | zaehlt mit? |
|---|---:|---|---|
| Brandschutz-Fachbetriebe | 5.236 | (kein Profil, neu erhoben) | **ja** |
| Kaelteanlagenbauer | 3.214 | Dichtheitspruefung und Anlagenlogbuch | **ja** |
| Schaedlingsbekaempfer | 1.074 | Koederstellen- und Monitoringdokumentation | **ja** |
| Aufzugswartung | 841 | Wartungs- und Prueffristen je Anlage | **ja** |
| Facility-Dienstleister | 34.288 | monatlicher Leistungsnachweis je Objekt | nein |
| Dachdecker | 15.241 | Asbestanzeige je Baustelle | nein |
| Spielplatz-/Sportanlagenbetreiber | 10.775 Gemeinden | wiederkehrende Spielplatzkontrolle dokumentieren | nein |
| **Vereinigung** | **10.365** | | |

**Warum die drei herausfallen:**

- **Facility-Dienstleister (34.288).** Der monatliche Leistungsnachweis je Objekt ist ein
  *vertraglicher* Nachweis gegenueber dem Auftraggeber, damit dieser die Kosten umlegen
  kann -- keine gesetzliche Prueffrist, kein Prueflingsbestand, keine Vorlagepflicht
  gegenueber einer Behoerde. Der teuerste Teil ist laut Profil die Aufteilung
  umlagefaehig/nicht umlagefaehig; die hat mit einer Pruefung nichts zu tun. Das ist ein
  anderer Vorgang und gehoert in ein anderes Prozessprofil (Leistungsnachweis gegen einen
  Kostentraeger).
- **Dachdecker (15.241).** Die Asbestanzeige faellt **je Baustelle** an, sieben Tage vor
  Beginn, an die Behoerde am Ort des Objekts. Sie ist ein einmaliger Vorgang je
  Bauvorhaben, kein Turnus, und sie erzeugt keinen Prueflingsbestand mit
  Wiedervorlagedatum. Sie gehoert in die Vorgangsliste unter "Behoerdenmeldung je Vorgang
  mit Formular und Frist" -- wo sie in `quellen.yml` auch steht.
- **Spielplatz- und Sportanlagenbetreiber (10.775 Gemeinden, 61.031 Kitas).** Hier stimmt
  der Vorgang inhaltlich, aber die Rolle ist die falsche: Gemeinden und Kita-Traeger sind
  **Pflichtige**, nicht Pruefer, und sie kaufen die Erledigung nach eigenem Profil bei
  einem Pruefdienstleister ein (119 EUR je Hauptpruefung). Ausserdem sind es keine
  Betriebe -- eine Gemeinde ist kein Softwarekunde derselben Art. Die
  *Spielplatz-Pruefdienstleister* wuerden dazugehoeren, aber fuer sie habe ich keine
  Betriebszahl gefunden und lasse sie deshalb weg.

**Bleiben 10.365 Betriebe.** Alle vier pruefen fremde Objekte im gesetzlichen Turnus:

- **Brandschutz-Fachbetriebe:** Feuerloescher-Instandhaltung, Hoechstfrist **zwei Jahre**
  nach ASR A2.2 in Verbindung mit DIN 14406-4, dazu die CO2-Druckpruefung alle zehn Jahre;
  ausschliesslich durch sachkundige Fachbetriebe (mehrere uebereinstimmende
  Fachbetriebsseiten, u. a. brandschutzfinder.de und cws.com, abgerufen 2026-08-30).
- **Kaelteanlagenbauer:** Dichtheitspruefung nach F-Gase-VO, jaehrlich/halbjaehrlich/
  vierteljaehrlich je nach CO2-Aequivalent, Anlagenlogbuch **fuenf Jahre** aufzubewahren.
- **Schaedlingsbekaempfer:** Monitoringkontrollen in den Abstaenden des
  Zulassungsbescheids, bei Dauerbekoederung hoechstens vierwoechig, Berichte fuer
  HACCP-/IFS-/BRC-Audits des Kunden.
- **Aufzugswartung:** 2 bis 4 Wartungstermine je Anlage und Jahr plus jaehrlich eine
  Pruefung (Haupt-/Zwischenpruefung nach BetrSichV), grob 250 Anlagen je Betrieb.

**Vorbehalt zur Summe:** Zwei der vier Zahlen (Brandschutz 5.236, Aufzug 841) stammen aus
derselben gecrawlten Adressdatenbank und sind nicht amtlich; die Schaedlingszahl ist sieben
Jahre alt, die Kaeltezahl vier. Die Summe ist eine Groessenordnung, keine Erhebung. Sie
aendert am Urteil nichts -- selbst eine Verdopplung auf rund 21.000 traegt die Rechnung in
Abschnitt 7 nicht.

## 3. Kern und Schale

Hier faellt das Profil ungewoehnlich aus: **Die Schale ist klein.** Das ist normalerweise
das positive Signal -- hier ist es der Grund, warum die Sache schon erledigt ist.

**Kern, in allen vier Branchen identisch:**

1. Ein Bestand von Prueflingen, jeder einem Kunden und einem Objekt zugeordnet.
2. Je Pruefling eine Frist, gerechnet aus einer Objekteigenschaft.
3. Eine Faelligkeitsliste, die den Aussendienst des naechsten Monats erzeugt.
4. Eine mobile Erfassung vor Ort: Haken, Befund, Foto, Unterschrift, Prueferkennung.
5. Ein PDF-Nachweis, der an den Pflichtigen geht.
6. Aufbewahrung und Wiedervorlage.

**Schale, je Branche verschieden:** der Pruefkatalog (was abgehakt wird), die Fristformel
(woraus der Turnus folgt), das Protokolllayout, das Vokabular und die Aufbewahrungsfrist.

Alle fuenf Schalenteile sind **Stammdaten, keine Programmlogik**. Ein Pruefkatalog ist eine
Liste, eine Fristformel eine Zahl mal einen Intervalltyp, ein Protokoll eine Vorlage. Genau
deshalb lautet die Antwort auf Frage 3 zwar "Schale kleiner als Kern" -- aber daraus folgt
nicht, dass hier etwas zu bauen waere. Es folgt das Gegenteil: **Wenn der branchenneutrale
Kern so gross ist, hat ihn jemand gebaut.** Abschnitt 4 nennt ihn.

## 4. Das horizontale Werkzeug

**Es gibt eines, und es zielt nicht auf "Wartung allgemein", sondern namentlich auf
Pruefdienstleister.**

**Certado Suite** (certado.io, abgerufen 2026-08-30) fuehrt eine eigene Seite
*Software fuer Pruefdienstleister* mit den Zielgruppen "PSAgA-Sachkundige, externe
Pruefdienstleister, Arbeitsschutz-Berater" und den Branchen "Bau, Logistik, Feuerwehr,
Industrie, Hilfsorganisation, Hoehenarbeit". Namentlich genannt werden DGUV Regel 112-198
fuer die Prueffristen, DGUV Grundsatz 305-002 fuer das Protokollformat und BetrSichV
§§ 3, 10, 14. Der Mandantenschnitt ist exakt der aus Abschnitt 3: **ein Arbeitsbereich je
Kunde**, damit ein Dienstleister mehrere Kunden mit je eigenem Bestand und eigenen Fristen
fuehren kann. Preise offen ausgewiesen: **39 EUR im Monat** (1 Arbeitsbereich, 1
Prueferzugang), **79 EUR** (5/2), **139 EUR** (15/3), Enterprise auf Anfrage, alle mit
unbegrenzten Betriebsmitteln, mobiler App und PDF-Pruefprotokollen. Gemeinnuetzige
Organisationen 22,95 EUR je Arbeitsbereich.

**HOPPE Wartungsplaner** (wartungsplaner.de, abgerufen 2026-08-30) fuehrt ebenfalls eine
eigene Prueferdienstleister-Seite: "Pruef- und Dokumentationssoftware fuer
Pruefdienstleister", "kann in allen Branchen und Betriebsgroessen eingesetzt werden", ueber
25 Jahre am Markt. Eigenangabe **5.800 Kunden, 39.000 Anwender, 14 Laender**; Einzelplatz
**195 EUR netto einmalig**, Netzwerkzusatz 395 EUR (belegt in
`research/2026-08-30-wartungsintervalle-maschinen-excel-selbstbau.md`, abgerufen
2026-08-30). Das Aufzugsprofil hat den Wartungsplaner bereits als Mehrbranchen-Werkzeug
gefunden, das "namentlich mit der Erinnerung an die Aufzugspruefung wirbt" -- also mit der
Schale einer der vier Branchen.

**Vier weitere aus derselben Suche** (2026-08-30): RISK-Project *Servo* (Wartung und
Pruefwesen), ROnDo Cloud (Betriebssicherheitsdaten, Prueffristenueberwachung ueber
Kundenbestaende), Vemas.PDL (Plattform fuer Pruefdienstleister von Kundenverwaltung ueber
Technikereinsatzplanung bis Abrechnung), MS Consulting (ERP fuer Pruefdienstleister).

**Und die Kategorie selbst ist vermessen.** Capterra Deutschland fuehrt in der Kategorie
CMMS **sieben Seiten zu je 25 Produkten, also bis zu 175** (abgerufen 2026-08-30); GetApp
Deutschland listet rund 100 Wartungswerkzeuge **mit Gratis-Version**. Die Schwelle aus
`notizen/lehren.md` liegt bei 50 Produkten und beendet den Lauf.

**Was das horizontale Werkzeug nicht kann, konnte ich nicht benennen.** Das ist der
ehrliche Befund und zugleich der entscheidende. Ich habe den Kern aus Abschnitt 3
Punkt fuer Punkt gegen Certado gehalten: Prueflingsbestand je Kunde, Fristrechnung,
Faelligkeitswarnung, mobile Erfassung mit Prueferkennung, PDF-Protokoll, Archiv -- alle
sechs sind ausgewiesene Funktionen. Der einzige Rest waere die *branchenspezifische
Fristformel* (CO2-Aequivalent bei Kaelte, Zulassungsbescheid bei Bioziden). Das ist eine
Stammdatenzeile, keine Produktluecke, und es ist genau der Teil, den die vertikalen
Anbieter aus Abschnitt 5 bereits mitliefern.

## 5. Die vertikalen Anbieter

**23 Stueck auf 10.365 Betriebe** -- und anders als es die Rollenbeschreibung als
Fundmuster erwartet, ist das hier **kein** Beweis fuer eine unbesetzte Vereinigung. Es ist
Beweis dafuer, dass der Vorgang zweimal geloest wurde: einmal je Branche und einmal quer.

| Branche | Anbieter | belegter Preis |
|---|---|---|
| Kaelte | VDKF-LEC (Verbandssoftware), KlimaCraft, CoolTool | KlimaCraft 60 EUR/Lizenz/Monat |
| Aufzug | Mainteny, Paternoster, es2000, COSMO CONSULT, orderbase, shm | Mainteny rund 19 EUR/Nutzer/Monat |
| Schaedlinge | PestScan, BORIS PCS, PestDesk, traplinked, KoederCheck | keiner veroeffentlicht Preise |
| Spielplatz | StraKo, Spektor, SpielDex, Punchbyte, ARCHIKART, Kasper, Gaja, SMART Kompakt, Spielplatzmobil | Spektor 99 EUR/Monat, SpielDex 0-9,99 EUR/Monat |

Die Frage der Rolle lautet: *Warum kann keiner von ihnen die Vereinigung heben?* Die
ehrliche Antwort ist: **Sie muessen es nicht, weil Certado und der Wartungsplaner sie
bereits heben.** Damit ist das Warnsignal aus der Rollenbeschreibung eingetreten -- ich
habe keinen Grund gefunden, warum die Vereinigung unbesetzt bliebe, und der Grund war,
dass sie es nicht ist.

Zwei Nebenbefunde, die unabhaengig davon schon schwer wiegen:

- **Der Verband ist in einer der vier Branchen selbst der Anbieter.** VDKF-LEC ist das
  Erzeugnis des Kaelteverbands, in dem ein Drittel des Gewerks organisiert ist. Das ist
  das Muster aus `notizen/lehren.md` (2026-08-30) in der schaerferen Form: Der Kanaleigner
  ist der Wettbewerber.
- **Der Preisboden liegt bei null.** SpielDex hat eine dauerhaft kostenlose Stufe,
  GetApp listet rund 100 Wartungswerkzeuge mit Gratis-Version, und HOPPE nimmt fuer eine
  Dauerlizenz 195 EUR einmalig -- rechnerisch unter 2 EUR im Monat ueber zehn Jahre.

## 6. Der gemeinsame Kanal

**Ein Kanal ueber die vier Branchen hinweg existiert -- und das ist hier die schlechte
Nachricht.**

Das gemeinsame Suchwort ist "Software fuer Pruefdienstleister" beziehungsweise
"Prueffristen verwalten". Es ist tatsaechlich branchenuebergreifend dasselbe: Meine Suche
danach (2026-08-30) hat **keine einzige** branchenspezifische Seite zurueckgegeben,
sondern sechs branchenneutrale Anbieter. Certado und Wartungsplaner unterhalten dafuer
je eine eigene Landingpage. Nach der Regel aus Frage 6 waere ein gemeinsames Suchwort das
Kriterium, das aus der Vereinigung erst einen Markt macht -- **hier beweist es, dass der
Markt existiert und dass zwei Anbieter ihn bereits bedienen.**

Die Verbandsschiene ist demgegenueber genau das, wovor die Rollenbeschreibung warnt: VDKF
(Kaelte), VmA und VFA-Interlift (Aufzug), DSV und VRS (Schaedlinge), bvbf (Brandschutz) --
sechs Verbaende fuer vier Branchen. Das sind sechs Vertriebsprobleme, nicht ein Kanal, und
einer davon verkauft das Konkurrenzprodukt.

## 7. Die Rechnung

**Preis.** Der belegte Anker ist Certado Starter mit **39 EUR im Monat** bei jaehrlicher
Abrechnung -- ein branchenneutrales Vollprodukt fuer genau diesen Vorgang. Er liegt
plausibel zwischen den vertikalen Belegen (Mainteny 19 EUR je Nutzer, KlimaCraft 60 EUR je
Lizenz, Spektor 99 EUR). Nach der Preisdeckel-Regel aus `notizen/lehren.md` muesste ein
neues Werkzeug *darunter* liegen; ich rechne trotzdem mit dem vollen Ankerpreis, um das
Ergebnis nicht zugunsten des Urteils zu verschieben.

**Kundenzahl.** Ein Promille von 10.365 sind **10 Betriebe**. Das Prozent ist nach G7 nur
zulaessig, wenn ein Kanal belegt ist. Der gemeinsame Suchkanal *existiert*, ist aber von
Certado und dem Wartungsplaner besetzt -- ein besetzter Kanal ist kein belegter Kanal. Ich
rechne beides und schreibe beide Zahlen hin:

| Annahme | Kunden | Monatsumsatz |
|---|---:|---:|
| Promille (regelkonform) | 10 | **390 EUR** |
| Prozent (nicht zulaessig, zur Kontrolle) | 104 | **4.056 EUR** |

**Ergebnis: `traegt_5000: nein`, und zwar unter beiden Annahmen.** Selbst die optimistische
Rechnung, die G7 hier gar nicht erlaubt, bleibt unter der Schwelle. Um 5.000 EUR zu
erreichen, braeuchte es 128 Kunden zu 39 EUR -- 1,2 Prozent eines Marktes, in dem ein
Anbieter seit ueber 25 Jahren sitzt und 5.800 Kunden hat.

**Gegenprobe mit der Ausgangszahl:** Selbst wenn man die 65.433 aus der Ausgangstabelle
gelten liesse, ergaebe das Promille 65 Kunden und 2.535 EUR im Monat -- ebenfalls unter der
Schwelle. Die Korrektur aus Abschnitt 2 verschaerft das Urteil, sie traegt es nicht.

## Die Luecke

**Es klafft keine, und der Grund liegt praezise zwischen Frage 3 und Frage 4.**

Vier Branchen mit zusammen 10.365 Betrieben pruefen fremde Objekte im gesetzlichen Turnus
und fuehren denselben Nachweis. Ihr gemeinsamer Kern ist gross und ihre branchenspezifische
Schale klein -- sie besteht aus Stammdaten, nicht aus Logik. Genau deshalb ist die
Vereinigung nicht unbesetzt geblieben: **Certado bedient sie seit Jahren mit einem
Mandantenmodell, das den Vorgang exakt abbildet (ein Arbeitsbereich je Kunde, Fristformel
je Prueflingstyp, DGUV-Protokollformat, 39 EUR im Monat), und HOPPE tut dasselbe seit ueber
25 Jahren fuer 5.800 Kunden zu 195 EUR einmalig.** Daneben stehen 23 vertikale Anbieter,
die dieselben Betriebe je Branche bedienen, und eine Capterra-Kategorie mit bis zu 175
Produkten, von denen rund hundert eine Gratis-Version haben.

Das ist die **erste** Zeile der Befundtabelle, nicht die vierte: Ein gutes horizontales
Werkzeug loest den Vorgang, damit ist er bedient und der Preisboden steht.

Zwei Beobachtungen daneben, die kein Produkt tragen, aber den naechsten Lauf sparen:

1. **Wer den Vorgang macht, verkauft ihn.** In drei der vier Branchen ist die Pruefung
   nicht die Last des Betriebs, sondern seine Rechnungsposition: 400 EUR je
   Dichtheitspruefung, 400 EUR je ZUeS-Pruefung und 1.000-4.000 EUR je Wartungsvertrag,
   7-18 EUR je Feuerloescher. Wer diesen Betrieben Buerozeit spart, spart ihnen keine
   Kosten, sondern schafft Kapazitaet -- ein schwaecherer Kaufgrund. Das Kaelte- und das
   Aufzugsprofil haben das je einzeln festgestellt; ueber den Vorgang hinweg ist es kein
   Zufall, sondern die Struktur: **Wo eine gesetzliche Pflicht Fachkunde verlangt, entsteht
   ein Dienstleister, der sie verkauft -- und fuer den ist der Vorgang nie eine Last.**
2. **Die Pflichtigenseite ist die groessere Vereinigung und die noch dichter besetzte.**
   Formal betroffen ist ueber die BetrSichV praktisch jeder Arbeitgeber mit Arbeitsmitteln;
   die Recherche vom 2026-08-30 hat genau dort gemessen und "rot" vergeben. Wer den Vorgang
   von dieser Seite aufmacht, landet in derselben CMMS-Kategorie mit 175 Produkten.

**Fuer die Fabrik heisst das:** Dieser Vorgang ist geprueft und geschlossen, auf beiden
Seiten. Ein spaeterer Lauf braucht ihn nicht erneut zu durchleuchten, solange Certado zu
39 EUR und der Wartungsplaner zu 195 EUR existieren.

## Was unklar ist

- **Die Vereinigung 10.365 steht auf gemischten Belegen.** Brandschutz (5.236) und Aufzug
  (841) stammen aus derselben gecrawlten Adressdatenbank, Schaedlinge (1.074) aus einer
  amtlichen Zahl von 2019, Kaelte (3.214) aus der Handwerksrolle 2022. Keine der vier ist
  aktuell und amtlich zugleich. Fuer das Urteil folgenlos, weil auch eine Verdopplung die
  Rechnung nicht dreht.
- **Fuer Spielplatz-Pruefdienstleister habe ich keine Betriebszahl gefunden.** Sie machen
  den Vorgang (prospielplatz, Spielplatzmobil, spielplatz-sicherheit.com), gehoeren also in
  die Vereinigung -- ich lasse sie nach der Regel "im Zweifel weglassen" heraus. Ebenso
  fehlen mir Zahlen fuer DGUV-V3-Pruefdienstleister, Torpruefer, Regalpruefer und
  Trinkwasser-Probenehmer; sie machen denselben Vorgang, und keine dieser Gruppen wird
  amtlich als Wirtschaftszweig gezaehlt. **Die Vereinigung ist also eher zu klein
  angegeben** -- was das Urteil abschwaechen wuerde, wenn es nicht ohnehin an Frage 4
  haengt.
- **Der Preis der fuenf Schaedlingsanbieter ist nirgends oeffentlich**, ebenso der von
  sieben der neun Spielplatzanbieter und von HOPPE ausserhalb der Einzelplatzlizenz. Der
  Preisanker steht damit auf Certado, KlimaCraft, Mainteny, Spektor und SpielDex.
- **Certados Kundenzahl ist unbekannt.** Ich weiss, dass das Produkt existiert, was es
  kostet und was es kann -- nicht, wie viele Pruefdienstleister es nutzen. Bei einem
  Urteil "tot" ist das die Zahl, die es kippen koennte: Ein Produkt mit zehn Kunden bedient
  die Vereinigung nicht wirklich. Der Wartungsplaner mit belegten 5.800 Kunden faengt
  diesen Zweifel allerdings auf.
- **Die Brandschutzbranche hat kein Marktprofil.** Ich habe sie neu erhoben und nur die
  Betriebszahl, die Prueffrist und den Pruefpreis belegt -- nicht die Anbieterlage speziell
  fuer Brandschutz-Fachbetriebe. Wer sie als eigenes Segment aufmachen will, faengt dort
  an; nach diesem Profil lohnt es sich nicht.
