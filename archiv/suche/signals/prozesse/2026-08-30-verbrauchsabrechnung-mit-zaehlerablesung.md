---
typ: prozess
erfasst: 2026-08-30
auftrag: Wiederkehrende Verbrauchsabrechnung mit Zaehlerablesung
vorgang: Ein Betreiber bezieht Strom, Wasser oder Waerme ueber einen Hauptanschluss, misst den Verbrauch je Nutzungseinheit mit einem eigenen Unterzaehler, liest ihn zu Periodenbeginn und -ende ab, verteilt die Gesamtkosten nach diesen Staenden und stellt jedem Nutzer eine Einzelabrechnung mit Verrechnung der Vorauszahlung
branchen:
  - name: Private Vermieter (Haushalte, ueberwiegend ein bis zwei Einheiten) | betriebe: 5.500.000 | quelle: IW-Vermieterreport 2026, wiedergegeben iwd.de vom 19.06.2026, abgerufen 2026-08-30
  - name: Hausverwaltungen fuer Wohnungseigentum und Mietverwaltung | betriebe: 24.600 | quelle: signals/maerkte/2026-08-29-hausverwaltungen-fuer-wohnungseigentum.md (Destatis PM Nr. 370, Berichtsjahr 2017)
  - name: Kleingartenvereine | betriebe: 13.000 | quelle: Bundesverband der Kleingartenvereine Deutschlands, "Zahlen und Fakten", knapp 13.000 Vereine mit 867.092 Kleingaerten, abgerufen 2026-08-30
  - name: Campingplaetze mit Dauer- und Saisoncampern | betriebe: 3.150 | quelle: signals/maerkte/2026-08-29-campingplaetze-und-ferienparks.md (Destatis 45412-0024)
vereinigung: 5.540.750 -- davon 5.500.000 private Vermieter und 40.750 Betriebe. Yachthaefen, Wohnheime und Gewerbehoefe machen den Vorgang ebenfalls, haben aber keine belastbare Betriebszahl und bleiben draussen
kern: Zaehlerstand Ende minus Zaehlerstand Anfang, mal Preis je Einheit, minus Vorauszahlung, je Nutzer auf ein Blatt
schale: Verteilungszwang und Formvorschrift bei Wohnraum (HeizkostenV, § 556 BGB), Saeulensteuerung mit Prepaid und Zutritt bei Camping und Marina, Vereinsumlage mit Schwundverteilung beim Kleingarten -- und dort sitzt jeweils der gesamte Kaufgrund
schale_groesser_als_kern: ja
horizontal_besetzt: ja
horizontal_werkzeug: Tabellenkalkulation loest den Kern vollstaendig -- er ist eine Subtraktion und eine Multiplikation. Was Excel nicht kann, ist nirgends der Kern, sondern die Schale: die Fernablesbarkeit nach § 5 Abs. 2 HeizkostenV (Hardware, seit 01.12.2021 Pflicht bei Neuinstallation), die monatliche Verbrauchsinformation nach § 6a HeizkostenV (seit 01.01.2022) und die Formstrenge, deren Verletzung dem Nutzer nach § 12 HeizkostenV ein Kuerzungsrecht von 15 Prozent gibt. Genau diese Schale ist bei Wohnraum an fuenf Messdienstleister ausgelagert, die 84 Prozent des Marktes halten
vertikal_anbieter: mindestens 30 -- Wohnraum 17 in einem einzigen Vergleich (trusted.de "17 Tools", darunter objego, hellohousing, vermietet.de, immocloud, Win-CASA, immoware24, Nebenkosten EASY, Casameta, eTASK), Wohnheim 2 (immocloud, tl1), Camping und Marina 5 (Camping-Strom, edelboxx, direst, fernauslese.de, ICY Marina Management), Kleingarten 5 (Laubenmeister, SEWOBE, Gartenbund.de, kleingarten-kassierer.de, Vereins-Meyer), dazu die Messdienstleister ista, Techem, Minol, Brunata, KALO als Vollservice
erreichbar_ueber: kein gemeinsamer Kanal -- vier Branchen, vier verschiedene Suchanfragen, jede davon mit eigenem Vergleichsportal und eigener Anbieterriege
suchwort: je Branche verschieden -- "Nebenkostenabrechnung Software" (Vermieter), "Stromabrechnung Campingplatz" (Camping), "Kleingartenverein Software Wasserabrechnung" (Verein), "Energieverbrauchsabrechnung Zaehlerstandserfassung" (Gewerbe)
preis_plausibel: 8,90 EUR je Kunde und Monat (objego: Zusatzpaket Verwaltung 7,95 EUR im Monat plus Zusatzpaket Nebenkosten 0,95 EUR je Mieteinheit und Monat, objego.de/preise, abgerufen 2026-08-30). Der Vorgang allein kostet dort 0,95 EUR je Einheit; die Grundstufe ist dauerhaft kostenlos. Gegenanker Fremdvergabe: 52 bis 97 EUR brutto je Wohneinheit und Jahr fuer den vollen Messdienst inklusive Geraeten (RITTERWALD, abgerufen 2026-08-30), also 4,33 bis 8,08 EUR je Einheit und Monat
kunden_erreichbar: 5.541 (ein Promille von 5.540.750) -- Promille, weil kein gemeinsamer Kanal existiert und jeder einzelne Branchenkanal von den vorhandenen Anbietern samt Vergleichsportal belegt ist. Zum Vergleich das nicht zulaessige Prozent: 55.408
monatsumsatz: 49.315 EUR (Promille); 493.131 EUR bei einem Prozent
traegt_5000: ja
befund: tot
---

# Zaehlerstand minus Zaehlerstand mal Preis -- das machen 5,5 Millionen private Vermieter und 40.750 Betriebe, und es ist die erste Vereinigung dieser Fabrik, deren Rechnung traegt und die trotzdem tot ist

## 1. Der Vorgang

> Ein Betreiber bezieht Strom, Wasser oder Waerme ueber **einen** Hauptanschluss, misst den
> Verbrauch je Nutzungseinheit mit einem **eigenen Unterzaehler**, liest ihn zu
> Periodenbeginn und -ende ab, verteilt die Gesamtkosten nach diesen Staenden und stellt
> jedem Nutzer eine Einzelabrechnung mit Verrechnung der Vorauszahlung.

Drei Merkmale trennen ihn von dem, was ihm aehnelt:

- **Ein Hauptanschluss, mehrere Nutzer.** Wo jeder Nutzer einen eigenen Vertrag mit dem
  Versorger hat, entsteht der Vorgang gar nicht -- dann rechnet der Versorger ab. Der
  Vorgang lebt genau davon, dass der Betreiber zwischen Versorger und Nutzer steht.
- **Gemessen, nicht geschaetzt.** Die Verteilung folgt einem abgelesenen Zaehlerstand,
  nicht einer Flaeche oder einer Kopfzahl. Wer nur nach Quadratmetern umlegt, macht einen
  anderen, einfacheren Vorgang.
- **Turnus mit Vorauszahlung.** Es wird periodisch abgerechnet und gegen eine geleistete
  Vorauszahlung verrechnet, nicht je Einzelfall in Rechnung gestellt.

**Der Vorgang wird auf der Seite dessen geschnitten, der abrechnet**, nicht auf der des
Zahlenden. Das ist dieselbe Rollentrennung, die schon beim Pruefnachweis entschieden hat:
Fuer den Vermieter, den Platzbetreiber und den Vereinskassierer ist die Abrechnung Arbeit,
fuer den Mieter, den Dauercamper und den Pachtnehmer ist sie eine Zahlungsaufforderung. Ein
Werkzeug kann nicht beiden dieselbe Sache verkaufen.

Ein Merkmal, das der Vorgang **branchenuebergreifend** hat und das ihn interessant
aussehen laesst: Wer Verbrauch gegen Entgelt abrechnet, braucht nach MessEG und MessEV ein
geeichtes Messgeraet -- elektronische Stromzaehler acht Jahre, Ferraris-Zaehler sechzehn,
danach Wechsel oder Nacheichung; ein nicht geeichter Zaehler macht die Abrechnung
angreifbar (mietrecht.org und enpal.de zur Eichpflicht bei Zwischenzaehlern, beide
abgerufen 2026-08-30). Diese Pflicht gilt fuer den Vermieter genauso wie fuer den
Campingplatz und den Kleingartenverein. Sie ist der einzige wirklich gemeinsame Zwang --
und sie betrifft die *Geraete*, nicht die Abrechnung. Sie gehoert damit in den
Pruefnachweis-Vorgang, der am 2026-08-30 bereits als `tot` geschlossen wurde.

## 2. Wer ihn macht

| Gruppe | Zahl | Quelle | zaehlt mit? |
|---|---:|---|---|
| Private Vermieter (Haushalte) | 5.500.000 | IW-Vermieterreport 2026, iwd.de 19.06.2026 | **ja** |
| Hausverwaltungen | 24.600 | Destatis PM 370, Berichtsjahr 2017 (Profil) | **ja** |
| Kleingartenvereine | 13.000 | BKD "Zahlen und Fakten" | **ja** |
| Campingplaetze | 3.150 | Destatis 45412-0024 (Profil) | **ja** |
| Yachthaefen und Marinas | keine Zahl | marinas.info nennt 430, WVW nur Liegeplaetze | nein |
| Studentenwohnheime, Gewerbehoefe | keine Zahl | — | nein |
| **Vereinigung** | **5.540.750** | | |

**Die Vereinigung wird von einer einzigen Gruppe dominiert, und es ist die, die in der
Ausgangstabelle dieser Rolle gar nicht vorkam.** Dort standen Campingplaetze und
Hausverwaltungen, zusammen 27.800. Die eigentliche Antwort auf "wer macht diesen Vorgang
alles von Hand" sind aber **private Vermieter**: mehr als 5,5 Millionen in Deutschland,
58 Prozent davon mit genau einem Mietobjekt, weitere 19 Prozent mit zweien; zusammen
vermieten sie fast zwei Drittel des Mietwohnungsbestands (IW-Vermieterreport 2026 fuer die
Deutschland.Immobilien AG, Befragung Februar 2026, wiedergegeben iwd.de am 19.06.2026,
abgerufen 2026-08-30). Sie sind seit dem 2026-08-29 ueberhaupt erst zaehlbar -- vorher war
B2C ausgeschlossen.

Die drei kleineren Gruppen machen denselben Vorgang unter anderem Recht:

- **Hausverwaltungen** rechnen ihn im Auftrag ab, fuer 24.600 Betriebe mit einem
  IT-Budget von 2,36 EUR je Einheit und Monat fuer die *gesamte* Softwarelandschaft.
- **Kleingartenvereine** verteilen Wasser und Strom je Parzelle, einschliesslich der
  Schwundmenge zwischen Hauptzaehler und Summe der Unterzaehler. 13.000 Vereine mit
  867.092 Gaerten unter dem BKD (abgerufen 2026-08-30).
- **Campingplaetze** rechnen Dauercampern Strom und Wasser je Parzelle ab; rund 45 Prozent
  der Stellplaetze sind dauerbelegt.

**Nicht mitgezaehlt**, obwohl der Vorgang stimmt: Yachthaefen (keine amtliche Betriebszahl;
Verzeichnisse nennen 430 bis 447, der Wirtschaftsverband Wassersport nur Liegeplaetze --
25.000 in Berlin, rund 150.000 zwischen Elbe und Ostsee, abgerufen 2026-08-30),
Studentenwohnheime, Gewerbehoefe und Ateliervermieter. Alle drei sind klein gegenueber
5,5 Millionen und wuerden am Ergebnis nichts aendern.

**Vorbehalt zur grossen Zahl:** Nicht jeder der 5,5 Millionen Vermieter fuehrt Unterzaehler.
Wo der Mieter einen eigenen Stromvertrag hat -- der Normalfall -- entfaellt der Vorgang
fuer Strom und bleibt nur fuer Wasser und Waerme. Und wo eine Zentralheizung vorhanden ist,
ist er nach § 4 HeizkostenV zwar Pflicht, wird aber fast durchgaengig an einen
Messdienstleister vergeben (Abschnitt 4). Die 5,5 Millionen sind die Obergrenze derer, die
den Vorgang haben, nicht derer, die ihn selbst machen.

## 3. Kern und Schale

Hier faellt das Profil genau andersherum aus als das vom selben Tag zum Pruefnachweis --
und mit demselben Ergebnis.

**Der Kern, in allen vier Gruppen identisch:**

1. Ein Bestand von Zaehlern, jeder einer Einheit zugeordnet.
2. Zwei Staende je Periode, Anfang und Ende.
3. Die Differenz mal einen Preis je Verbrauchseinheit.
4. Abzug der Vorauszahlung, ein Blatt je Nutzer.

**Das ist eine Subtraktion und eine Multiplikation.** Der gemeinsame Kern dieses Vorgangs
ist arithmetisch trivial -- und damit ist Frage 3 schon entschieden. Alles, wofuer jemand
Geld ausgibt, sitzt in der Schale, und die Schale ist je Gruppe eine andere:

| Gruppe | Schale | Umfang |
|---|---|---|
| Wohnraum | HeizkostenV: Verteilung zu 50 bis 70 Prozent nach Verbrauch (§ 6), fernablesbare Geraete seit 01.12.2021 (§ 5 Abs. 2), monatliche Verbrauchsinformation seit 01.01.2022 (§ 6a), Kuerzungsrecht des Nutzers von 15 Prozent bei Verstoss (§ 12); dazu § 556 Abs. 3 BGB mit Zwoelfmonatsfrist | eine ganze Verordnung |
| Camping, Marina | Saeulensteuerung, Prepaid-Guthaben, Zutritt, Check-in, Fernauslese ueber Funk | Hardware |
| Kleingarten | Vereinsumlage, Schwundverteilung zwischen Haupt- und Unterzaehlern, Beitragsbescheid | Vereinsrecht |
| Gewerbe | frei verhandelte Umlageschluessel, Haupt- und Unterzaehlerbaeume ueber mehrere Ebenen | Vertrag |

Der Volltext der HeizkostenV (gesetze-im-internet.de, abgerufen 2026-08-30) bestaetigt den
Befund unmittelbar: § 2 stellt die Verordnung sogar ausdruecklich ueber abweichende
vertragliche Vereinbarungen. Wer Wohnraum abrechnet, hat keine Wahl; wer einen
Campingplatz abrechnet, hat gar keine Verordnung.

**Antwort auf Frage 3: Die Schale ist groesser als der Kern, und zwar deutlich.** Damit
sind es nach der Regel aus `quellen.yml` vier Vorgaenge mit einem gemeinsamen Oberbegriff,
kein Markt. Die Abschnitte 4 bis 6 zeigen, dass der Markt genau so gebaut ist, wie es
daraus folgt.

## 4. Das horizontale Werkzeug

**Es gibt eines, es kostet nichts, und es reicht: die Tabellenkalkulation.** Der Kern aus
Abschnitt 3 ist eine Differenz mal einen Preis -- die Aufgabe, fuer die Excel erfunden
wurde. Nach der Regel aus meinem Auftrag zaehlt "Excel ist unbequem" nicht; ich muss
benennen, was Excel **nicht** kann. Die ehrliche Antwort lautet: **beim Kern nichts, bei
der Schale alles** -- und die Schale gehoert je Branche jemand anderem.

Bei Wohnraum kann Excel drei Dinge nicht, und alle drei stehen in der HeizkostenV:

- **Fernablesbarkeit (§ 5 Abs. 2).** Seit dem 01.12.2021 duerfen nur noch fernablesbare
  Ausstattungen neu installiert werden, seit dem 01.12.2022 nur solche, die sich an ein
  Smart-Meter-Gateway anbinden lassen. Das ist Hardware, kein Rechenblatt.
- **Monatliche Verbrauchsinformation (§ 6a).** Seit dem 01.01.2022 ist dem Nutzer monatlich
  eine Verbrauchsinformation mit Vergleichswerten zu geben. Zwoelf Mitteilungen im Jahr
  statt einer Abrechnung -- das erledigt niemand von Hand.
- **Die Rechtsfolge (§ 12).** Wer nicht verbrauchsabhaengig abrechnet, muss eine Kuerzung
  von 15 Prozent hinnehmen, wer die Fernablesbarkeit versaeumt, drei Prozent.

**Und genau deshalb ist der Wohnbereich nicht bei Excel gelandet, sondern beim
Vollservice.** Fuenf Messdienstleister kontrollieren 84 Prozent dieses Marktes; ista und
Techem wurden 2017/2018 fuer 4,5 bzw. 4,6 Milliarden Euro an Finanzinvestoren verkauft
(RITTERWALD Unternehmensberatung, "Bewegung im Messdienst-Markt", abgerufen 2026-08-30).
Sie stellen die Geraete, lesen fern ab, erzeugen die monatliche Information und liefern die
fertige Abrechnung -- fuer **52 bis 97 EUR brutto je Wohneinheit und Jahr**, je nach
Losgroesse und Technik. Der Vorgang ist auf der groessten Teilmenge der Vereinigung nicht
Handarbeit, sondern eine ausgelagerte Dienstleistung mit einem Milliardenmarkt dahinter.

Auf der branchenneutralen Softwareebene ist ebenfalls besetzt: eTASK bildet "komplexe
Zaehlerstrukturen mit Haupt- und Unterzaehlern" ab und legt nach Verbrauch, Mietflaeche
oder festem Unterverteiler um; ab-data rechnet Verbrauchsentgelte fuer
Versorgungsunternehmen und Kommunen ab; waterloo Meter und die WAVE Suite fuehren eigene
Zaehlermanagement-Module; softguide fuehrt "Zaehlermanagement" als eigene
Softwarefunktionskategorie (alle abgerufen 2026-08-30).

## 5. Die vertikalen Anbieter

Mindestens dreissig, und sie verteilen sich exakt entlang der Schalen aus Abschnitt 3.

| Gruppe | Anbieter | belegter Preis |
|---|---|---|
| Wohnraum, privat | objego, hellohousing, vermietet.de, immocloud, Casameta, Nebenkosten EASY | objego 7,95 EUR/Monat plus 0,95 EUR je Einheit; **Grundstufe dauerhaft 0 EUR**; hellohousing mit kostenloser Version |
| Wohnraum, gewerblich | Win-CASA, immoware24, eTASK, DOMUS, Haufe PowerHaus | IT-Budget der Verwaltungen: 2,36 EUR je Einheit und Monat fuer alles zusammen |
| Wohnheim | immocloud, tl1 Wohnheimverwaltung | nicht oeffentlich |
| Camping, Marina | Camping-Strom (12 PMS-Schnittstellen, ueber 150 Plaetze in 9 Laendern), edelboxx, direst, fernauslese.de, ICY Marina Management | keiner veroeffentlicht Preise |
| Kleingarten | **Laubenmeister ("Keine Lizenzgebuehr. Keine Einrichtungsgebuehr.", spendenfinanziert)**, SEWOBE, Gartenbund.de, kleingarten-kassierer.de, Vereins-Meyer | 0 EUR |
| Vollservice Wohnraum | ista, Techem, Minol, Brunata, KALO | 52-97 EUR je Wohneinheit und Jahr |

Die Frage der Rolle lautet: *Warum kann keiner von ihnen die Vereinigung heben?* Anders als
beim Pruefnachweis, wo die Antwort "sie muessen nicht, ein Horizontaler tut es schon"
lautete, ist sie hier: **Es gibt nichts zu heben.** Wer edelboxx den Kern wegnimmt, laesst
eine Stromsaeule mit Funkmodul stehen; wer objego den Kern wegnimmt, laesst eine
HeizkostenV-konforme Abrechnungsvorlage stehen; wer Laubenmeister den Kern wegnimmt, laesst
einen Vereinsbeitragsbescheid stehen. Der gemeinsame Teil ist das, was keiner von ihnen
verkauft, weil er nichts wert ist.

**Zwei Anbieter haben die Vereinigung ausserdem bereits dort gehoben, wo sie ueberhaupt
tragfaehig ist:** edelboxx bedient Yachthaefen, Campingplaetze und Wohnmobilstellplaetze aus
einem Produkt (edelboxx.de/loesungen/yachthafen-marina, abgerufen 2026-08-30), direst
ebenso. Die Schale "Saeule mit Prepaid und Zutritt" ist ueber drei Betriebsarten hinweg
dieselbe -- und genau diese Untermenge ist besetzt.

**Der Preisboden liegt bei null, dreifach belegt:** objego Basics kostenlos, hellohousing mit
kostenloser Version, Laubenmeister dauerhaft und vollstaendig kostenlos. Das ist derselbe
Befund wie im Campingprofil (Camping.care ab 0 EUR bei 1.400 Plaetzen) und dieselbe Lehre
wie aus dem englischsprachigen Raum -- nur ohne Zahlungsstrom als Erklaerung. Hier ist die
Null schlicht der Preis einer Subtraktion.

## 6. Der gemeinsame Kanal

**Es gibt keinen.** Das ist der zweite harte Befund und er bestaetigt Abschnitt 3.

Ich habe die vier Gruppen einzeln gesucht (alle 2026-08-30), und keine einzige Suche hat
einen Treffer aus einer anderen Gruppe zurueckgegeben:

| Suchanfrage | was zurueckkam |
|---|---|
| "Nebenkostenabrechnung Software" | Vergleichsportale mit 17 bzw. 10 Produkten (trusted.de, softwareabc24.de), alle Wohnraum |
| "Stromabrechnung Campingplatz" | Camping-Strom, edelboxx, fernauslese.de, direst -- alle Hardware plus Software |
| "Kleingartenverein Software Wasserabrechnung" | Laubenmeister, SEWOBE, Gartenbund, kleingarten-kassierer |
| "Energieverbrauchsabrechnung Zaehlerstandserfassung" | eTASK, ab-data, waterloo -- Gewerbe und Versorger |

Das ist der Gegentest zum Pruefnachweis-Profil, wo eine einzige Anfrage sechs
branchenneutrale Anbieter zurueckgab. Hier ist das Suchwort je Branche ein anderes -- und
nach der Regel aus Frage 6 heisst das, dass der Vorgang vermutlich doch nicht derselbe ist.
Er ist es im Kern; nur sucht niemand nach dem Kern.

Der Kanal fuer die grosse Gruppe waere ausserdem ein B2C-Kanal: 5,5 Millionen private
Vermieter, die einmal im Jahr eine Abrechnung brauchen. Er existiert und ist benennbar --
und er ist von einem Anbieter besetzt, der zum Aareon-Umfeld gehoert, mit einer dauerhaft
kostenlosen Grundstufe und zwei oeffentlichen Vergleichsportalen davor.

## 7. Die Rechnung

**Preis.** Belegter Anker ist objego: Zusatzpaket Verwaltung **7,95 EUR im Monat** plus
Zusatzpaket Nebenkosten **0,95 EUR je Mieteinheit und Monat**, Grundstufe kostenlos,
zwoelf Monate Mindestlaufzeit (objego.de/preise, abgerufen 2026-08-30). Fuer einen
Vermieter mit einer Einheit sind das **8,90 EUR im Monat** fuer das Vollprodukt -- und
**0,95 EUR** fuer den Vorgang allein, um den es hier geht. Ich rechne mit 8,90 EUR, dem
hoeheren der beiden Werte, um das Ergebnis nicht zugunsten des Urteils zu verschieben.

**Kundenzahl.** Ein Promille von 5.540.750 sind 5.541. Das Prozent ist nach G7 nicht
zulaessig: Ein gemeinsamer Kanal existiert nicht, und jeder einzelne Branchenkanal ist
belegt -- mit Anbietern, Vergleichsportalen und im Wohnbereich zusaetzlich mit fuenf
Messdienstleistern, die 84 Prozent halten.

| Annahme | Kunden | Monatsumsatz |
|---|---:|---:|
| Promille (regelkonform) | 5.541 | **49.315 EUR** |
| Prozent (nicht zulaessig, zur Kontrolle) | 55.408 | 493.131 EUR |

**Ergebnis: `traegt_5000: ja` -- zum ersten Mal in dieser Rolle, und es aendert nichts.**

Der Vorbehalt gehoert dazu, weil er die Zahl relativiert: Das Promille ist in G7 als
*vorsichtiger* Wert gedacht, geeicht an Segmenten mit fuenfstelliger Betriebszahl. Auf
einen B2C-Markt mit 5,5 Millionen angewandt bedeutet es **5.541 zahlende Abonnenten**, und
das ist fuer einen Nebenerwerb keine vorsichtige Annahme, sondern ein Erfolg, den in diesem
Markt bisher nur Anbieter mit Konzernanbindung erreicht haben. Wer die Zahl ernst nimmt,
muesste ausserdem die Umsatzsteuer und das Verbraucherrecht aus G7 gegenrechnen. Die
Rechnung ist hier nicht das Argument -- weder fuer noch gegen.

## Die Luecke

**Es klafft keine, und diesmal liegt der Grund allein zwischen Frage 3 und Frage 4.**

5,5 Millionen private Vermieter, 24.600 Hausverwaltungen, 13.000 Kleingartenvereine und
3.150 Campingplaetze fuehren denselben Rechenschritt aus: Zaehlerstand minus Zaehlerstand,
mal Preis, minus Vorauszahlung. Das ist der groesste Vorgang, den diese Rolle bisher
gezaehlt hat -- und der duennste. Er besteht aus zwei Rechenoperationen, und eine
Tabellenkalkulation erledigt sie vollstaendig.

Alles, wofuer in diesem Markt Geld fliesst, sitzt in der Schale und gehoert dort bereits
jemandem:

- **Wohnraum:** eine ganze Verordnung mit Verteilungszwang, Geraetepflicht, monatlicher
  Informationspflicht und einem Kuerzungsrecht von 15 Prozent -- ausgelagert an fuenf
  Messdienstleister mit 84 Prozent Marktanteil zu 52 bis 97 EUR je Wohneinheit und Jahr,
  daneben mindestens 17 Softwareprodukte mit zwei oeffentlichen Vergleichsportalen und einer
  dauerhaft kostenlosen Grundstufe.
- **Camping und Marina:** eine Stromsaeule mit Fernauslese, Prepaid und Zutritt -- Hardware,
  bedient von fuenf Anbietern, von denen zwei bereits ueber drei Betriebsarten hinweg
  verkaufen.
- **Kleingarten:** Vereinsumlage und Schwundverteilung -- fuenf Anbieter, der bekannteste
  dauerhaft kostenlos und spendenfinanziert.

**Das ist die erste Zeile der Befundtabelle in ihrer reinsten Form**, und sie ist hier
strenger als beim Pruefnachweis: Dort war der Kern gross und deshalb von einem Horizontalen
besetzt. Hier ist der Kern so klein, dass ihn niemand besetzen musste -- er faellt beim
Benutzen der Schale von selbst ab. Beide Enden sind tot, und dazwischen liegt der Fund, den
diese Rolle sucht: ein Kern, der gross genug ist, um Arbeit abzunehmen, und eine Schale, die
klein genug ist, um konfigurierbar zu bleiben, ohne dass jemand den Kern bereits gebaut hat.

**Fuer die Fabrik heisst das:** Dieser Vorgang ist geprueft und geschlossen, auf allen vier
Teilmengen. Ein spaeterer Lauf braucht ihn nicht erneut zu durchleuchten, solange objego
eine kostenlose Grundstufe hat, Laubenmeister ganz kostenlos ist und die HeizkostenV die
Fernablesbarkeit vorschreibt.

Eine Beobachtung daneben, die kein Produkt traegt, aber die naechste Rechnung praeziser
macht: **Die Ausgangstabelle dieser Rolle hat bei diesem Vorgang um den Faktor 200
danebengelegen** -- 27.800 statt 5.540.750. Nicht weil sie falsch gezaehlt haette, sondern
weil sie nur Marktprofile kannte, und Marktprofile kennen nur Betriebe. Beim naechsten
Vorgang der Liste lohnt die Frage zuerst: *Gibt es zu diesem Vorgang eine Endkundengruppe,
die ihn in derselben Form macht?* Sie ist regelmaessig um Groessenordnungen groesser als die
Betriebsseite -- und regelmaessig die mit dem Preisboden null.

## Was unklar ist

- **Die 5,5 Millionen sind eine Obergrenze, keine Zahl der Handarbeitenden.** Wie viele
  private Vermieter tatsaechlich Unterzaehler selbst ablesen und abrechnen, statt einen
  Messdienst zu beauftragen oder gar keinen Zaehler zu haben, sagt keine der gefundenen
  Quellen. Die Zahl stammt zudem aus einem Vermieterreport im Auftrag eines
  Immobilienunternehmens, nicht aus einer amtlichen Erhebung.
- **Die Betriebszahl der Hausverwaltungen ist neun Jahre alt** (Berichtsjahr 2017) und die
  der Kleingartenvereine eine Verbandsangabe ohne Stichtag. Beide sind gegenueber 5,5
  Millionen so klein, dass es folgenlos bleibt.
- **Fuer Yachthaefen gibt es keine Betriebszahl.** Der Wirtschaftsverband Wassersport nennt
  nur Liegeplaetze, Verzeichnisse nennen 430 bis 447 Haefen. Sie machen den Vorgang und
  gehoeren in die Vereinigung; nach der Regel "im Zweifel weglassen" bleiben sie draussen.
- **Keiner der fuenf Camping- und Marina-Anbieter veroeffentlicht Preise**, ebenso wenig
  die Wohnheimanbieter. Der Preisanker steht damit vollstaendig auf der Vermieterseite
  (objego) und auf dem Messdienst-Vollservice (RITTERWALD).
- **Die trusted.de-Liste mit 17 Produkten konnte ich nicht am Original pruefen** -- die
  Seite antwortet mit HTTP 403. Die Zahl steht im Seitentitel des Suchtreffers; die
  Zweitquelle softwareabc24.de nennt unabhaengig davon zehn Produkte in derselben
  Kategorie. Fuer das Urteil folgenlos: Schon zehn Produkte mit oeffentlichem Vergleich
  reichen nach `notizen/lehren.md` als Zeichen eines reifen Marktes.
