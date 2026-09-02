---
typ: prozess
erfasst: 2026-08-30
auftrag: Leistungsnachweis gegenueber einem Kostentraeger
vorgang: Ein Betrieb erbringt eine vorab verordnete oder genehmigte Leistung an einer Person, laesst sich den Empfang je Termin quittieren und rechnet sie nicht bei dieser Person ab, sondern bei einem gesetzlichen Kostentraeger -- in einem vorgeschriebenen elektronischen Datensatz an eine Datenannahmestelle, mit nachtraeglichem Absetzungsrisiko bei Formfehlern
branchen:
  - name: Physiotherapie- und Heilmittelpraxen (Physiotherapie) | betriebe: 40.113 | quelle: signals/maerkte/2026-08-29-physiotherapiepraxen.md (GKV-Spitzenverband, bereinigter Bestand 30.04.2022)
  - name: Freiberufliche Hebammen | betriebe: 19.000 | quelle: signals/maerkte/2026-08-29-hebammen-und-geburtshaeuser.md (GKV-Spitzenverband, E-Magazin "90 Prozent" Ausgabe 43)
  - name: Ambulante Pflegedienste | betriebe: 15.549 | quelle: signals/maerkte/2026-08-29-ambulante-pflegedienste.md (Destatis Pflegestatistik, Jahresende 2023)
  - name: Ergotherapiepraxen | betriebe: 7.381 | quelle: listflix.de/statistik/ergotherapiepraxen, Stand 29.08.2026, Crawler-Datenbank, abgerufen 2026-08-30
  - name: Logopaedie- und Sprachtherapiepraxen | betriebe: 5.570 | quelle: listflix.de/statistik/logopaediepraxen, Crawler-Datenbank, abgerufen 2026-08-30 (konkurrierende Kassenzahl 9.000, siehe 2)
  - name: Podologiepraxen | betriebe: 3.503 | quelle: listflix.de/statistik/podologiepraxen, Stand Juni 2026, abgerufen 2026-08-30
  - name: Sanitaetshaeuser (Hilfsmittelerbringer) | betriebe: 3.437 | quelle: listflix.de/statistik/sanitaetshaeuser, Stand 22.07.2026, abgerufen 2026-08-30
  - name: Krankentransport-Unternehmen | betriebe: 1.364 | quelle: listflix.de/dienstleistung/.../krankentransporte, Stand Oktober 2025, abgerufen 2026-08-30
  - name: Rettungsdienste | betriebe: 726 | quelle: listflix.de/statistik/rettungsdienste, Stand Juni 2026, abgerufen 2026-08-30
vereinigung: 96.643 Betriebe -- die Ausgangstabelle nannte 74.662 aus drei Branchen; sechs weitere machen denselben Vorgang. Mit Augenoptik und Hoerakustik rund 113.600, siehe 2
kern: Verordnung oder Genehmigung erfassen und auf Formalien pruefen, Leistungen je Empfaenger und Termin mit Unterschrift erfassen, gegen den geltenden Vertragspreis taxieren, den Monatsdatensatz je Kostentraeger im vorgeschriebenen Format an die Datenannahmestelle uebermitteln, Absetzungen und Korrekturlaeufe nachverfolgen, Belege aufbewahren
schale: Leistungspositionsnummern und Preise je Rahmenvertrag, Kasse und Bundesland, Formularmuster, Genehmigungs- und Fristregeln, Fachvokabular
schale_groesser_als_kern: nein -- aber die Schale ist keine einmalige Konfiguration, sondern eine laufende Pflegelast (siehe 3)
horizontal_besetzt: ja
horizontal_werkzeug: Die Abrechnungszentren sind das horizontale Werkzeug und bedienen exakt diese Vereinigung. opta data (>60.000 Kunden, 15 Mrd EUR Abrechnungsvolumen, Kundengruppen Pflege, Heilmittel, Hilfsmittel, Hebammen, Transport, Optik, Hoerakustik), azh/NOVENTI (>26.000 Abrechnungskunden), DMRZ (10.000+ Kunden, sechs Sparten auf einer Plattform), Optica, RZH. Eine Funktion des Kerns, die keiner von ihnen hat, habe ich nicht gefunden -- selbst die Pflege der Kostentraegerstammdaten und der Rahmenvertraege verkauft DMRZ als eigene Tarifstufe fuer 9,99 EUR im Monat
vertikal_anbieter: mindestens 51 -- Pflege 31 (MEDIFOX DAN, Vivendi PD, .snap, CuraSoft, myneva u. a.), Heilmittel 12 (THEORG, buchnerFLOW, thevea, Optica Viva, NOVENTI Ora, Henara, Hedi u. a.), Hebammen 8 (HebRech, Hebamio, miya, Heb-Office u. a.). Vier der zwoelf Heilmittelprodukte gehoeren den Abrechnungszentren selbst
erreichbar_ueber: ein gemeinsamer Suchkanal existiert -- und er ist besetzt: die Suche nach "§ 302 SGB V Abrechnung Software" (2026-08-30) lieferte die eigene Ratgeberseite des DMRZ unter den ersten Treffern; opta data, azh, Optica und RZH ranken je mit eigener Landingpage. Auch die Verbandsschiene ist besetzt, DMRZ wirbt offen mit Verbandskonditionen
suchwort: "Abrechnung mit den Krankenkassen" / "Abrechnungszentrum" / "§ 302 SGB V" -- branchenuebergreifend dieselbe Anfrage, weil es dieselbe Rechtsgrundlage ist
preis_plausibel: 60 EUR je Kunde und Monat (DMRZ-Grundgebuehr Basic 59,99 EUR; azh/NOVENTI Kassenabrechnung ab 96,80 EUR im Monat; Optica ab 1,28 Prozent vom Bruttobetrag; AZH-Hebammen 3,8 Prozent)
kunden_erreichbar: 97 (ein Promille von 96.643) -- Promille, weil der gemeinsame Kanal existiert, aber von den Abrechnungszentren besetzt ist. Zum Vergleich das nicht zulaessige Prozent: 966
monatsumsatz: 5.820 EUR (Promille); 57.960 EUR bei einem Prozent
traegt_5000: knapp -- rechnerisch 5.820 EUR Umsatz, nach laufenden Kosten rund 4.900 bis 5.200 EUR Marge, also auf der Schwelle. Die Groesse ist hier zum ersten Mal nicht der Engpass
befund: tot
---

# Neun Branchen mit 96.643 Betrieben rechnen ihre Leistung nach derselben Vorschrift bei einem Dritten ab -- und drei Abrechnungszentren halten zusammen rund 96.000 Kundenbeziehungen in genau dieser Vereinigung

## 1. Der Vorgang

Gemeint ist nicht "Abrechnung" und auch nicht "Leistungsnachweis" im weiten Sinn, sondern
dies:

> Ein Betrieb erbringt eine **vorab verordnete oder genehmigte** Leistung an einer Person,
> laesst sich den Empfang **je Termin quittieren** und rechnet sie **nicht bei dieser Person**
> ab, sondern bei einem gesetzlichen Kostentraeger -- in einem **vorgeschriebenen
> elektronischen Datensatz** an eine Datenannahmestelle, mit **nachtraeglichem
> Absetzungsrisiko** bei Formfehlern.

Fuenf Merkmale trennen ihn von allem, was ihm aehnelt. Ein Betrieb aus einer Branche, die
unten nicht steht, erkennt sich wieder, wenn alle fuenf zutreffen:

- **Ein Dritter zahlt.** Der Leistungsempfaenger unterschreibt, aber er zahlt nicht. Wer
  seinem Kunden eine Rechnung schickt, macht einen anderen Vorgang -- auch dann, wenn er
  monatlich einen Leistungsnachweis beilegt.
- **Der Anspruch ist vorher da, nicht nachher.** Eine Verordnung, ein Bescheid oder eine
  Genehmigung geht der Leistung voraus. Fehlt sie oder ist sie formal falsch, ist die
  bereits erbrachte Arbeit nicht abrechenbar.
- **Quittung je Einzelleistung.** Der Empfaenger bestaetigt Datum und Umfang, meist per
  Unterschrift, meist am Ort der Leistung.
- **Kein freies Rechnungsformat.** Uebermittelt wird ein gesetzlich definierter Datensatz
  an eine Datenannahmestelle: § 302 SGB V fuer die sonstigen Leistungserbringer, § 105
  SGB XI fuer die Pflegesachleistung. Die Rechtsgrundlage steht wortgleich fuer alle unten
  genannten Branchen (gesetze-im-internet.de und gkv-datenaustausch.de, abgerufen
  2026-08-30).
- **Absetzung statt Mahnung.** Bezahlt wird zunaechst, gekuerzt wird spaeter. Der Betrieb
  traegt das Risiko fuer Fehler, die er nicht selbst verursacht hat -- etwa fuer ein falsch
  ausgefuelltes Arztformular.

**Die Rollentrennung, die das vorige Profil zur offenen Faehrte erklaert hat, faellt hier
anders aus** und macht den Vorgang staerker, nicht schwaecher: Beim Pruefnachweis war die
Pflicht fuer den Pruefer eine Rechnungsposition und damit keine Last. Hier ist sie fuer
alle neun Branchen reine Buerozeit, die gegenueber dem Kostentraeger **nicht abrechenbar**
ist -- das Hebammenprofil sagt das woertlich. Es gibt in diesem Vorgang keine Seite, fuer
die er Umsatz waere. Das ist der beste Kaufgrund, den die Fabrik bisher vermessen hat.

## 2. Wer ihn macht

**Die Ausgangstabelle nennt drei Branchen und 74.662 Betriebe. Sie war zu klein, nicht zu
gross** -- das Gegenteil des Befunds beim Pruefnachweis. Der Grund steht im Gesetz: § 302
SGB V nennt die Betroffenen selbst und nennt sie branchenuebergreifend ("Hilfsmittel,
Heilmittel, haeusliche Krankenpflege, Haushaltshilfe, Krankentransport, Hebammen").

| Branche | Betriebe | Quelle | zaehlt mit? |
|---|---:|---|---|
| Physiotherapiepraxen | 40.113 | GKV-SV 30.04.2022, Profil | **ja** |
| Freiberufliche Hebammen | 19.000 | GKV-SV, Profil | **ja** |
| Ambulante Pflegedienste | 15.549 | Destatis 2023, Profil | **ja** |
| Ergotherapiepraxen | 7.381 | listflix 29.08.2026 | **ja** |
| Logopaedie/Sprachtherapie | 5.570 | listflix | **ja** |
| Podologiepraxen | 3.503 | listflix Juni 2026 | **ja** |
| Sanitaetshaeuser | 3.437 | listflix 22.07.2026 | **ja** |
| Krankentransport | 1.364 | listflix Okt 2025 | **ja** |
| Rettungsdienste | 726 | listflix Juni 2026 | **ja** |
| **Vereinigung** | **96.643** | | |
| Augenoptik | rund 10.700 | ZVA-Branchenbericht 2025/2026 | mit Vorbehalt |
| Hoerakustik | rund 6.300 | biha | mit Vorbehalt |
| Facility-Dienstleister | 34.288 | Destatis 2022, Profil | nein |
| Aerzte, Zahnaerzte | -- | -- | nein |
| Apotheken | -- | -- | nein |

**Warum die sechs neuen Branchen dazugehoeren:** Ergotherapie, Logopaedie und Podologie
sind Heilmittelerbringer nach § 124 SGB V wie die Physiotherapie -- dieselbe Verordnung,
derselbe Heilmittelkatalog, derselbe Absetzungskatalog, dieselbe Datenlieferung nach
§ 302. Sanitaetshaeuser, Krankentransport und Rettungsdienste stehen im Gesetzestext
selbst. Alle sechs werden von denselben Abrechnungszentren bedient, was Abschnitt 4 zeigt
-- und das ist der praktische Beweis dafuer, dass der Vorgang derselbe ist: Ein
Dienstleister, der ihn fuer neun Branchen auf einer Plattform abwickelt, koennte das nicht,
wenn es neun Vorgaenge waeren.

**Warum drei mit Vorbehalt oder gar nicht zaehlen:**

- **Augenoptik (10.700) und Hoerakustik (6.300).** Beide rechnen Hilfsmittel nach § 302
  SGB V ab und stehen in den Kundenlisten von DMRZ und opta data. Zwei Gruende fuer den
  Vorbehalt: Die ZVA-Zahl zaehlt **Betriebsstaetten**, nicht Unternehmen, und beide Gewerke
  sind stark filialisiert -- die Zahl der Kaufentscheider ist deutlich kleiner. Ausserdem
  ist die Kassenabrechnung dort ein Nebenstrom neben dem freien Verkauf, waehrend sie in
  den neun gezaehlten Branchen der Haupterloesweg ist. Ich fuehre sie an, rechne aber ohne
  sie.
- **Facility-Dienstleister (34.288).** Das vorige Prozessprofil hat sie beim Pruefnachweis
  herausgenommen und hierher verwiesen. **Sie gehoeren auch hierher nicht.** Ihr monatlicher
  Leistungsnachweis geht an den **Auftraggeber**, der ihn bezahlt -- kein Dritter, keine
  Verordnung, kein vorgeschriebener Datensatz, keine Absetzung, sondern eine Rechnung mit
  Anlage. Vier der fuenf Merkmale aus Abschnitt 1 fehlen. Damit hat die Ausgangstabelle
  dieser Rolle die 34.288 zweimal falsch zugeordnet, und der Verweis des Vorgaengerprofils
  war die zweite Fehlzuordnung. **Der Vorgang "vertraglicher Leistungsnachweis an den
  Auftraggeber" existiert, ist aber ein eigener und steht in keiner Vorgangsliste.**
- **Aerzte und Zahnaerzte.** Sie rechnen ueber die Kassenaerztliche Vereinigung nach § 295
  SGB V ab, quartalsweise, im Datensatz KVDT, und ihr Honorar wird aus einem gedeckelten
  Topf **verteilt** statt je Rechnung erstattet. Kein Verordnungsdurchlauf, andere Norm,
  anderes Format, andere Logik. Sie wuerden die Vereinigung mehr als verdoppeln -- und
  gehoeren nicht hinein.
- **Apotheken.** § 300 SGB V statt § 302, eigene Apothekenrechenzentren. Nah dran, aber eine
  andere Vorschrift mit eigenem Verfahren; nach der Regel "im Zweifel weglassen" draussen.

**Vorbehalt zur Summe:** Die drei grossen Zahlen (Physio, Hebammen, Pflege) stammen aus
amtlichen oder amtsnahen Quellen, sind aber zwei bis vier Jahre alt. Die sechs kleineren
stammen saemtlich aus derselben gecrawlten Adressdatenbank und zaehlen Webauftritte, nicht
Zulassungen; fuer die Logopaedie kursiert mit 9.000 zugelassenen Praxen eine deutlich
hoehere Kassenzahl. Die Summe ist eine Groessenordnung. Sie ist eher zu klein als zu gross
-- und am Urteil aendert das nichts, weil es nicht an der Groesse haengt.

## 3. Kern und Schale

**Der Kern ist gross und in allen neun Branchen identisch:**

1. Verordnung, Bescheid oder Genehmigung erfassen und auf Formalien pruefen, **bevor**
   behandelt wird.
2. Leistungen je Empfaenger und Termin erfassen, mit Datum, Position und Unterschrift.
3. Positionen gegen den geltenden Vertragspreis taxieren.
4. Den Sammeldatensatz je Kostentraeger im vorgeschriebenen Format erzeugen und an die
   richtige Datenannahmestelle senden.
5. Zahlungseingang, Absetzungen und Korrekturlaeufe nachverfolgen.
6. Belege aufbewahren und auf Verlangen vorlegen.

**Die Schale ist kleiner:** Positionsnummern und Preise je Rahmenvertrag, Kasse und
Bundesland, Formularmuster, Genehmigungs- und Fristregeln, Vokabular.

Damit lautet die Antwort formal wie beim Pruefnachweis: `schale_groesser_als_kern: nein`.
**Aber der Unterschied zum Pruefnachweis ist der eigentliche Ertrag dieses Abschnitts, und
er entscheidet den Fall:**

> Beim Pruefnachweis war die Schale eine **Konfiguration** -- ein Pruefkatalog, eine
> Fristformel, ein Protokolllayout. Einmal gesetzt, steht sie jahrelang.
>
> Hier ist die Schale ein **Abonnement**. Rahmenvertraege werden regional zwischen
> Landesverbaenden und Kassen neu verhandelt, Preislisten aendern sich unterjaehrig,
> Schluesselverzeichnisse und Korrekturverfahren werden fortgeschrieben. Wer diese Schale
> nicht **jede Woche** pflegt, liefert falsch taxierte Datensaetze.

Wie teuer diese Pflege ist, laesst sich beziffern, weil jemand sie einzeln verkauft: DMRZ
fuehrt "Kostentraegermanagement mit automatischer Datenpflege" und "Rahmenvertraege
hinterlegt" als Bestandteil seiner Tarifstufe Silber -- **9,99 EUR im Monat** (dmrz.de/preise,
abgerufen 2026-08-30). Das ist der Preis, zu dem der Markt die einzige laufende
Pflegeleistung dieses Vorgangs bereits handelt.

## 4. Das horizontale Werkzeug

**Es gibt eines, es ist nicht Excel, und es ist selbst nach dem Vorgang geschnitten statt
nach der Branche.** Das ist der Fall, vor dem die dritte Zeile der Befundtabelle warnt --
nur nicht mit einem grossen Anbieter, sondern mit fuenfen.

| Anbieter | belegte Groesse | bediente Branchen |
|---|---|---|
| **opta data** | **ueber 60.000 Kunden**, 3.300 Mitarbeitende, 15 Mrd EUR Abrechnungsvolumen im Jahr | Pflege, Heilmittel (Physio, Ergo, Logo, Podo), Hilfsmittel, **Hebammen**, Transport- und Rettungsdienste, Optik, Hoerakustik |
| **azh / NOVENTI** | **ueber 26.000 Abrechnungskunden**, davon rund 4.500 mit Praxissoftware; nach der ARZ-Darmstadt-Uebernahme war von rund 50 Prozent Marktanteil die Rede | Heilmittel, Pflege, Hilfsmittel, Hebammen |
| **DMRZ** | **10.000+ Kunden** | sechs Sparten auf einer Plattform: Pflege, Krankentransport, Heilmittel, Hilfsmittel, Selektivvertraege, Rehasport |
| **Optica** | keine Kundenzahl veroeffentlicht | Heilmittel, Pflege, Hebammen |
| **RZH** | keine Kundenzahl veroeffentlicht | Heilmittel |

Quellen: optadata.de und Wikipedia "Opta data Gruppe", dmrz.de sowie dmrz.de/preise,
alle abgerufen 2026-08-30; azh-Zahlen aus `signals/maerkte/2026-08-29-physiotherapiepraxen.md`.

**Die Rechnung, die den Lauf beendet:** 60.000 plus 26.000 plus 10.000 sind rund **96.000
Kundenbeziehungen** in einer Vereinigung von **96.643 Betrieben**. Die Zahlen sind nicht
sauber addierbar -- opta data zaehlt Deutschland und Oesterreich und mehrere Produktlinien,
ein Betrieb kann bei einem Haus abrechnen und beim anderen Software kaufen, und die
Kundengruppen der drei ueberschneiden sich. Als Groessenordnung ist die Aussage trotzdem
eindeutig: **Diese Vereinigung ist nicht unbesetzt, sie ist annaehernd vollstaendig
bedient.**

**Was das horizontale Werkzeug nicht kann, konnte ich nicht benennen.** Ich habe die sechs
Kernpunkte aus Abschnitt 3 einzeln gegen DMRZ gehalten: Verordnungserfassung mit
Plausibilitaetspruefung, mobile Leistungserfassung mit digitaler Unterschrift (ab Advanced,
119,99 EUR), Taxierung, Datenlieferung nach § 302 und § 105, Korrekturverfahren,
Kostentraegerstammdaten mit automatischer Pflege, Archiv -- alle sechs sind ausgewiesene
Funktionen. Bei Optica ist die Vorabpruefung sogar in **37 Einzelkriterien** zerlegt und
wird **mit Haftungsuebernahme** verkauft.

**Der Preisboden steht entsprechend tief.** DMRZ bewirbt die Abrechnung mit **0,5 Prozent
der Rechnungssumme** (dmrz.de/ueber-uns/presse, abgerufen 2026-08-30); die Servicepakete
darueber kosten 3,99 bis 24,99 EUR im Monat. Fuer eine Hebamme mit 24.000 EUR Jahresumsatz
sind 0,5 Prozent **rund 10 EUR im Monat** -- fuer den gesamten Vorgang, einschliesslich der
Stammdatenpflege aus Abschnitt 3.

## 5. Die vertikalen Anbieter

**Mindestens 51, und sie sind hier kein positives Signal, sondern die zweite Besetzung.**

| Branche | Anbieter | belegter Preis |
|---|---:|---|
| Pflege | 31 zugeschnittene Produkte (MEDIFOX DAN, Vivendi PD, .snap, CuraSoft, myneva u. a.) | 149-350 EUR/Monat |
| Heilmittel | 12 (THEORG, buchnerFLOW, thevea, Optica Viva, NOVENTI Ora, Henara, Hedi, iPrax u. a.) | 30-80 EUR/Nutzer/Monat |
| Hebammen | 8 (HebRech, Hebamio, miya, Heb-Office, HEB-Control u. a.) | 11,50-49 EUR/Monat |

Die Frage der Rolle lautet: *Warum kann keiner von ihnen die Vereinigung heben?* Die
ehrliche Antwort ist dieselbe wie im vorigen Profil, nur schaerfer: **Sie muessen es nicht,
weil die Abrechnungszentren sie bereits heben -- und weil vier der zwoelf Heilmittelprodukte
den Abrechnungszentren gehoeren.** thevea gehoert opta data, Optica Viva gehoert Optica,
NOVENTI Ora gehoert NOVENTI, Hedi haengt am RZH. Die vertikale und die horizontale Ebene
sind hier nicht zwei Lager, sondern zwei Vertriebswege desselben Hauses.

Damit ist das Warnsignal aus der Rollenbeschreibung eingetreten: Ich habe keinen Grund
gefunden, warum die Vereinigung unbesetzt bliebe -- der Grund war, dass sie es nicht ist.

**Und der Kaufgrund ist der falsche.** azh erstattet bei einer durchgerutschten Absetzung
"den vollen Betrag", Optica uebernimmt die Haftung fuer die definierten Kriterien. Wer in
diesem Markt antritt, konkurriert nicht mit einer Funktion, sondern mit einer Garantie --
und verkauft damit Richtigkeit statt Zeitersparnis. Das ist die Konstellation, an der nach
`notizen/lehren.md` (2026-08-29) bereits zwei Kandidaten dieser Fabrik gestorben sind.

## 6. Der gemeinsame Kanal

**Er existiert, er ist ungewoehnlich sauber -- und er ist besetzt.**

Das gemeinsame Suchwort ist keine Umschreibung, sondern eine Paragrafennummer: **§ 302
SGB V**. Neun Branchen googeln dieselbe Vorschrift, weil es dieselbe Vorschrift ist. Der
Beleg kostete einen Abruf: Meine erste Suche dieses Laufs nach "§ 302 SGB V sonstige
Leistungserbringer Abrechnung Software" (2026-08-30) lieferte unter den ersten Treffern die
**eigene Ratgeberseite des DMRZ** ("Als Leistungserbringer elektronisch abrechnen -- per
Datenaustausch") -- zwischen dem Gesetzestext und der Wikipedia-Seite. Der Anbieter sitzt
auf dem Gesetzeswort.

Die zweite Kanalschiene, die Verbaende, ist ebenfalls besetzt und dieses Mal ganz offen:
DMRZ bewirbt **Verbandskonditionen** fuer Pflege und Heilmittel, opta data ist ueber das
DRK-Einkaufsportal gelistet, und in der ambulanten Pflege vermarktet die
bpa-Servicegesellschaft Software an ueber 14.000 Mitgliedseinrichtungen. Nach der Lehre vom
2026-08-30 ist das der schlimmere Fall: Der Kanaleigner ist der Vertriebsweg des
Wettbewerbers.

**Der Kanal beweist hier also genau das, was er beim Pruefnachweis bewies:** dass der Markt
existiert und dass ihn jemand bedient. Ein gemeinsames Suchwort macht die Vereinigung erst
zum Markt -- und dieser Markt hat schon Bewohner.

## 7. Die Rechnung

**Preis.** Belegte Anker fuer genau diesen Vorgang:

| Anker | Preis |
|---|---|
| DMRZ Basic, Kassenabrechnung Pflege | 59,99 EUR/Monat + 0,8 % oberhalb 10.000 EUR |
| azh/NOVENTI, Kassenabrechnung Heilmittel | ab 96,80 EUR/Monat |
| Optica, Gesamtgebuehr | ab 1,28 % vom Bruttobetrag |
| AZH, Hebammen-Vollservice | 3,8 % vom Rechnungsbetrag |
| DMRZ, beworbener Satz | 0,5 % der Rechnungssumme |

Ich rechne mit **60 EUR im Monat** -- dem unteren der beiden Festpreisanker. Das ist die
konservative Wahl: Der prozentuale Weg ergibt fuer kleine Betriebe deutlich weniger (rund
10 EUR fuer eine Hebamme), fuer grosse deutlich mehr (rund 850 EUR fuer einen Pflegedienst
mit 1,7 Mio EUR Umsatz).

**Kundenzahl.** Ein Promille von 96.643 sind **97 Betriebe**, ein Prozent **966**. Nach der
Tabelle in G7 gilt das Promille: Der gemeinsame Kanal ist belegt, aber nicht frei -- die
Abrechnungszentren ranken auf dem Suchwort und besitzen die Verbandsschiene.

| Annahme | Kunden | Monatsumsatz |
|---|---:|---:|
| **Promille (regelkonform)** | 97 | **5.820 EUR** |
| Prozent (nicht zulaessig) | 966 | 57.960 EUR |

**Ergebnis: `traegt_5000: knapp`.** Und das ist ein Novum in dieser Fabrik: **Zum ersten Mal
scheitert ein Vorgang nicht an der Groesse.** 5.820 EUR sind Umsatz, nicht Marge; nach
Hosting, Zahlungsabwicklung und laufenden Kosten bleiben grob 4.900 bis 5.200 EUR. Die
Schwelle aus G7 wird gestreift, nicht ueberschritten.

**Die Zahl ist trotzdem wertlos, und das gehoert in dieselbe Rechnung:** Die
Promille-Annahme unterstellt 97 freie Betriebe. In einer Vereinigung von 96.643, in der drei
Haeuser rund 96.000 Kundenbeziehungen halten, ist "frei" die falsche Beschreibung. Wer hier
97 Kunden gewinnen will, gewinnt sie **von opta data, azh oder DMRZ** -- gegen einen
Preisboden von 10 EUR im Monat und gegen eine Haftungszusage.

## Die Luecke

**Es klafft keine, und der Befund faellt schaerfer aus als beim Pruefnachweis -- weil hier
alles andere stimmt.**

Neun Branchen mit 96.643 Betrieben erledigen denselben Vorgang nach derselben Vorschrift.
Der Kern ist gross, die Schale klein, die Handarbeit ist echter Kostenblock statt Umsatz,
der Zwang ist gesetzlich, und der gemeinsame Kanal ist keine Umschreibung, sondern eine
Paragrafennummer, die alle neun googeln. Das sind saemtliche Vorbedingungen, die diese
Rolle sucht, zum ersten Mal gleichzeitig erfuellt.

**Und genau deshalb ist die Vereinigung nicht unbesetzt geblieben.** § 302 SGB V hat den
Vorgang 1989 branchenuebergreifend definiert, und die Antwort darauf ist eine ganze
Industrie: opta data mit ueber 60.000 Kunden und 15 Mrd EUR Abrechnungsvolumen, azh/NOVENTI
mit ueber 26.000 Abrechnungskunden, DMRZ mit 10.000+ auf sechs Sparten, dazu Optica und
RZH. Sie sind nach dem **Vorgang** geschnitten, nicht nach der Branche -- also genau so, wie
diese Rolle zu suchen gelernt hat. Daneben stehen 51 vertikale Produkte, von denen vier den
Abrechnungszentren selbst gehoeren.

Das ist die **erste** Zeile der Befundtabelle: Ein gutes horizontales Werkzeug loest den
Vorgang, damit ist er bedient und der Preisboden steht -- hier bei 0,5 Prozent der
Rechnungssumme, fuer eine Hebamme rund zehn Euro im Monat.

Drei Beobachtungen daneben, die kein Produkt tragen, aber die naechsten Laeufe sparen:

1. **Wer im Geldfluss sitzt, gewinnt den Vorgang.** Beim Pruefnachweis hiess der Befund "wer
   den Vorgang macht, verkauft ihn". Hier lautet er anders und ist allgemeiner: Das
   Abrechnungszentrum bekommt den Beleg ohnehin, es kann die Pruefung ohne Grenzaufwand
   danebenlegen, es kennt den Zahlungseingang und kann deshalb Haftung uebernehmen -- und es
   kassiert prozentual, waechst also mit dem Kunden mit. Ein externes Werkzeug muesste
   denselben Beleg ein zweites Mal erfassen und koennte fuer nichts geradestehen.
   **Verallgemeinert: Steht am Ende eines Vorgangs eine Zahlung, gehoert der Vorgang dem,
   der die Zahlung abwickelt.** Das ist die vierte Variante von "die Behoerde ist der
   Wettbewerber" und die bisher haerteste.
2. **Eine Stammdatenschale ist nur dann harmlos, wenn sie einmal gesetzt wird.** Beim
   Pruefnachweis war sie eine Konfiguration, hier ist sie eine woechentliche Pflegelast aus
   regionalen Rahmenvertraegen und fortgeschriebenen Schluesselverzeichnissen. Frage 3
   sollte deshalb nicht nur nach der **Groesse** der Schale fragen, sondern nach ihrer
   **Haltbarkeit**: Eine Schale, die gepflegt werden muss, ist bei zwei Wochenstunden
   Betriebszeit ein eigenes Ausschlusskriterium -- und derjenige, der sie heute pflegt,
   verkauft sie fuer 9,99 EUR im Monat.
3. **Der Zutritt ist technisch verriegelt.** Wer nach § 302 liefern will, braucht ein
   Institutionskennzeichen, ein bestandenes Testverfahren bei den Datenannahmestellen und
   seit dem 01.07.2025 in der Pflege die Anbindung an die Telematikinfrastruktur; ab
   01.12.2026 ist der elektronische Leistungsnachweis dort verpflichtend, ab 01.10.2027 ist
   KIM alleiniger Weg. Das ist keine Grenze aus `grenzen.md` und nicht mein Urteil -- aber
   es erklaert, warum in diesem Vorgang keine generischen Werkzeuge auftauchen und warum
   die fuenf Haeuser, die drin sind, drin bleiben.

**Fuer die Fabrik heisst das:** Dieser Vorgang ist geprueft und geschlossen, fuer alle neun
Branchen zugleich. Ein spaeterer Lauf braucht weder ihn noch eines der drei Marktprofile
erneut zu durchleuchten, solange opta data, azh und DMRZ existieren. Was er hinterlaesst,
ist die **Gegenprobe zur Ausgangsthese dieser Rolle**: Die Vereinigung war hier real, gross
und ueber einen einzigen Kanal erreichbar -- und trotzdem gab es nichts zu holen, weil
derselbe Gedanke vor Jahrzehnten jemand anderem gekommen ist, dem der Gesetzgeber die
Vorlage geliefert hat.

## Was unklar ist

- **Sechs der neun Betriebszahlen stammen aus einer gecrawlten Adressdatenbank** (Ergo,
  Logo, Podo, Sanitaetshaeuser, Krankentransport, Rettungsdienste) und zaehlen Webauftritte,
  nicht Zulassungen. Fuer die Logopaedie kursiert mit 9.000 zugelassenen Praxen eine um zwei
  Drittel hoehere Kassenzahl, fuer die Ergotherapie sogar eine Angabe von 18.000 bis 20.000.
  **Die Vereinigung ist damit eher zu klein als zu gross angegeben** -- was das Urteil nicht
  dreht, weil es an Frage 4 haengt. Die belastbare Gesamtzahl waere das Verzeichnis der
  ARGE·IK; es ist nur kostenpflichtig zu bekommen, also ein Gate.
- **Der GKV-Spitzenverband fuehrt mit dem Heilmittelleistungserbringerverzeichnis (HLV) eine
  amtliche Liste aller zugelassenen Heilmittelpraxen**, veroeffentlicht auf
  gkv-spitzenverband.de. Ich habe die Suchmaske gefunden, aber keine ausgewiesene
  Gesamtzahl je Heilmittelbereich. Wer sie auslesen kann, ersetzt vier der sechs
  Crawler-Zahlen durch amtliche.
- **Die Kundenzahlen der drei grossen Haeuser sind Eigenangaben und nicht ueberschneidungsfrei.**
  opta datas "ueber 60.000" umfasst Deutschland und Oesterreich sowie mehrere Produktlinien;
  azh zaehlt Abrechnungskunden, DMRZ zaehlt Kunden. Die Aussage "die Vereinigung ist
  annaehernd vollstaendig bedient" ist eine Groessenordnung, keine Erhebung -- sie ist
  allerdings die einzige Zahl, die das Urteil kippen koennte, und sie kippt es in beide
  Richtungen erst bei einer Halbierung.
- **Optica und RZH veroeffentlichen keine Kundenzahl.** Ihr Anteil an der Vereinigung ist
  unbekannt und in den 96.000 nicht enthalten.
- **Facility-Dienstleister sind jetzt zweimal aussortiert**, beim Pruefnachweis und hier.
  Ihr Vorgang -- vertraglicher Leistungsnachweis an den Auftraggeber mit Umlagefaehigkeit --
  ist damit belegt vorhanden, 34.288 Betriebe gross und **in keiner Vorgangsliste**. Ich darf
  `quellen.yml` nicht aendern; der Hinweis gehoert dem Betreiber.
- **Die Betriebszahlen fuer Augenoptik und Hoerakustik zaehlen Betriebsstaetten
  beziehungsweise Betriebe, nicht Kaufentscheider.** Beide Gewerke sind stark filialisiert
  (KIND, Amplifon, Fielmann). Wer sie in eine Vereinigung aufnimmt, braucht eine
  Unternehmenszahl, keine Standortzahl.
