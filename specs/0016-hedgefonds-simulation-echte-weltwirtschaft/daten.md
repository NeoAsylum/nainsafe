---
typ: daten
idee: 0016-hedgefonds-simulation-echte-weltwirtschaft
erstellt: 2026-08-31
quellen_geprueft: 13
quellen_brauchbar: 6
sperrfrage: geloest
empfehlung: Weltbank WDI (CC BY 4.0) als Kern, IWF-Statistikdaten fuer Zins, Wechselkurs und Staatsfinanzen, CEPII BACI (Etalab 2.0) fuer bilaterale Handelsstroeme, Penn World Table 11.0 (CC BY 4.0) fuer Produktivitaet und Preisniveaus
---

# Ja: Vier Quellen erlauben im Wortlaut, die Daten in ein verkauftes Produkt einzubetten und mitzuliefern -- und sie decken den Kern des Modells ab.

## The blocking question

**Solved.** The World Bank (CC BY 4.0), Penn World Table 11.0 (CC BY 4.0) and CEPII BACI
(Etalab Open Licence 2.0) expressly permit reproduction, redistribution and commercial
use; for its statistical data, the IMF in its literal wording permits selling. So no
workaround construction is needed: the game may contain the starting vintages and run
offline, and the fourth check axis from `agentenbau.md` stands open.

It hinges on two conditions that touch the design, not just the legal notice: all four
require attribution **and** the marking of changes -- and an economic model changes data
by construction (aggregation to twelve countries, conversion to integers). The notice
text must name that, not just the source.

What does **not** work is just as clear, and it was the idea's actual open question:
**UN Comtrade must not be shipped in raw form**, and neither may FRED, WTO and WITS. The
way out for the bilateral trade flows is CEPII BACI -- a cleaned version derived from
Comtrade, which stands under a free licence and, by Comtrade's own account, no longer
carries the Comtrade condition. That is the most important single find of this run.

**On the evidence:** `imf.org`, `oecd.org` and `fred.stlouisfed.org` rejected direct page
retrieval with HTTP 403, and `web.archive.org` is unreachable. Where a quotation below
comes from a verbatim search hit rather than from my own page retrieval, that is stated
alongside it. That is weaker evidence, and I mark it as such.

## Quellen einzeln

### 1. Weltbank -- World Development Indicators — **traegt**

**Lizenz im Wortlaut:** „The Creative Commons Attribution 4.0 (CC-BY 4.0) license […]
allows users to copy, modify and distribute data in any format for any purpose, including
commercial use. Users are only obligated to give appropriate credit (attribution) and
indicate if they have made any changes, including translations."
(`datacatalog.worldbank.org/public-licenses`, abgerufen 2026-08-31)

Ergaenzend, weil es die Weitergabe *in einem Produkt* ausdruecklich nennt: „you are free
to copy, distribute, adapt, display or include the data in other products for commercial
or noncommercial purposes at no cost"
(`data.worldbank.org/summary-terms-of-use`, abgerufen 2026-08-31).

Der Datensatz selbst nennt als Lizenz „Creative Commons Attribution 4.0"
(`datacatalog.worldbank.org/search/dataset/0037712/World-Development-Indicators`,
abgerufen 2026-08-31).

**Auflagen:** Namensnennung in der Form „The World Bank: Dataset name: Data source (if
known)", Kennzeichnung von Aenderungen, und die Namensnennungspflicht muss an jeden
weitergereicht werden, dem man die Daten weitergibt. Kein Copyleft, keine Registrierung,
kein Bulk-Verbot.

**Die Einschraenkung, und sie ist wichtig:** „Some datasets and indicators are provided by
third parties, and may not be redistributed or reused without the consent of the original
data provider, or may be subject to additional terms and conditions."
(ebd.) Die WDI sind eine **Sammlung**, nicht durchgehend eigenes Werk der Weltbank. Genau
die drei Reihen, die dieses Modell zusaetzlich braucht -- sektorale Beschaeftigung
(ILO-Schaetzung), Zollsaetze (aus WITS/TRAINS) und Teile der Preisreihen (IWF) --, sind
Kandidaten fuer diese Ausnahme. Zu tun: je Reihe das Feld „Source" im Indikatorendatensatz
lesen, bevor sie eingebettet wird. Siehe **Was unklar ist**.

**Inhalt:** ueber 200 Laender und Gebiete, ueber 1.500 Indikatoren, 1960 bis 2025,
jaehrliche Auflösung, jaehrliche Aktualisierung (ebd.). Deckt BIP, Bevoelkerung,
Inflation, Handelsvolumen, Wertschoepfung nach grober Sektorgliederung.

**Urteil:** Kern des Produkts. Beste Kombination aus Lizenz, Breite und Laenge.

### 2. IWF -- WEO, IFS, DOTS — **traegt, mit einer Auflage zum Nachlesen**

**Lizenz im Wortlaut:** „Users may download, extract, copy, create derivative works,
publish, distribute, and sell Data obtained from IMF Sites, including for commercial
purposes." (`imf.org/en/about/copyright-and-terms`) — **Beleghinweis:** Der direkte Abruf
der Seite wurde am 2026-08-31 mit HTTP 403 abgewiesen; der Satz ist ueber eine
Wortlaut-Suche nach genau dieser Zeichenkette belegt, nicht ueber einen eigenen
Seitenabruf. Vor dem Bau im Volltext nachzulesen.

**Auflagen** (aus derselben Quelle): Die Daten muessen bei Weitergabe unveraendert und
korrekt mit dem IWF als Quelle erscheinen; wer die Daten **materiell transformiert**, muss
das ausdruecklich angeben; und: „If IMF Data is sold by Users as a standalone product,
sellers must inform purchasers that the Data is available free of charge from the IMF."

**Beide Lesarten dieser letzten Klausel, weil sie mehrdeutig ist:** (a) Ein Spiel ist kein
„standalone product" aus IWF-Daten, sondern eine Simulation, in der die Daten Startwerte
sind -- dann entfaellt der Hinweis. (b) Der Kaeufer erhaelt die Daten mitgeliefert und
bezahlt dafuer -- dann greift der Hinweis. Die Klausel kostet einen Satz im Impressum;
ich waehle keine Lesart, sondern empfehle, den Satz zu schreiben. Er ist billiger als die
Frage.

**Inhalt:** WEO liefert Staatsschuld und Haushaltssaldo in Prozent des BIP fuer nahezu
alle Mitgliedslaender, halbjaehrlich aktualisiert und **rueckwirkend revidiert**; IFS
liefert Leitzinsen, Geldmengen und Wechselkurse in monatlicher und quartalsweiser
Auflösung; DOTS liefert bilaterale Handelsaggregate (Land gegen Land, ohne Warengliederung)
in Monats- und Quartalsauflösung. Genau die drei Groessen, die den WDI fehlen oder in
denen sie Luecken haben.

**Urteil:** Zweite tragende Saeule, unentbehrlich fuer Zins, Wechselkurs und
Staatsfinanzen. Die Revisionspraxis ist ein Entwurfsproblem, kein Lizenzproblem: Wer die
vierte Pruefachse gegen WEO-Reihen fahren will, muss den Abrufstand einfrieren, sonst
aendert sich der Sollwert des Regressionstests unter dem Test weg.

### 3. CEPII -- BACI und Gravity — **traegt, und loest den Comtrade-Knoten**

**Lizenz im Wortlaut:** „BACI is distributed under the Etalab Open Licence 2.0, which
means that any use is authorized, provided the source is mentionned."
(`cepii.fr/DATA_DOWNLOAD/baci/doc/FAQ_BACI.html`, abgerufen 2026-08-31; Tippfehler im
Original)

**Auflagen:** Quellenangabe („BACI und das CEPII nennen, moeglichst mit Link auf die
Webseite", ebd.). Die Etalab Open Licence 2.0 ist mit CC BY 4.0 vertraeglich und kennt
kein Copyleft und kein Bulk-Verbot.

**Inhalt:** bilaterale Handelsstroeme Land-Land-Produkt in HS-Nomenklatur, jaehrlich,
geografische Abdeckung wie Comtrade, jaehrliche Aktualisierung ab Januar; das jeweils
letzte Jahr wird noch revidiert (ebd.).

**Warum das der Fund ist:** BACI ist aus UN Comtrade abgeleitet, und Comtrade selbst
schreibt zu abgeleiteten Bestaenden: „Transformed data from UN Comtrade is no longer
subject to copyright restrictions" und nennt als qualifizierende Transformationen
ausdruecklich „calculating new indicators" und „performing geographic and other
aggregations" (`uncomtrade.org/docs/faqs-on-use-and-re-dissemination/`, abgerufen
2026-08-31). BACI ist genau das: harmonisiert, gespiegelt, bereinigt. Damit ist die
Sorge der Idee („untersagt eine davon die Weitergabe im Bulk, muss der Kern auf
Weltbank-Aggregate zurueckgeschnitten werden") gegenstandslos -- der Aussenhandelsteil
darf in seiner feinen Form gebaut werden.

**Urteil:** Empfohlen fuer bilaterale Stroeme. Auf zwoelf Laender und sechs Sektoren
aggregiert bleibt ohnehin nur ein Bruchteil des Datensatzes uebrig.

### 4. Penn World Table 11.0 — **traegt**

**Lizenz im Wortlaut:** „Creative Commons Attribution 4.0 International License", mit der
vorgeschriebenen Zitierung „Feenstra, Robert C., Robert Inklaar and Marcel P. Timmer
(2015), 'The Next Generation of the Penn World Table' American Economic Review, 105(10),
3150-3182" (`rug.nl/ggdc/productivity/pwt/`, abgerufen 2026-08-31).

**Auflagen:** Namensnennung samt der genannten Literaturangabe, Kennzeichnung von
Aenderungen. Kein Copyleft.

**Inhalt:** 185 Laender, **1950 bis 2023**, jaehrlich; kaufkraftbereinigte Niveaus von
Output, Kapitalstock, Arbeitseinsatz, Produktivitaet und Preisniveaus. Version 11.0
veroeffentlicht am 2025-10-07.

**Urteil:** Empfohlen als Ergaenzung. Zwei Dinge kann sie, die WDI und IWF nicht koennen:
Sie reicht bis 1950 zurueck (mehr waehlbare Startjahrgaenge, also mehr verkaufbarer
Inhalt nach dem Erweiterungsmodell der Idee) und liefert **Produktivitaet und Preisniveaus
im Laendervergleich** -- die Groessen, aus denen ein Handelsmodell komparative Vorteile
ueberhaupt erst bilden kann.

### 5. Destatis — **traegt, ist hier aber entbehrlich**

**Lizenz im Wortlaut:** „Data licence Germany – attribution – version 2.0"; die Daten
duerfen „be copied, printed, presented, altered, processed and transmitted to third
parties", „be merged with own data and with the data of others and be combined to form new
and independent datasets" und „be integrated in internal and external business processes,
products and applications" (`govdata.de/dl-de/by-2-0`, abgerufen 2026-08-31; Fassung des
Lizenztextes, auf den Destatis verweist). Gewerbliche und nichtgewerbliche Nutzung sind
gleichgestellt.

**Auflagen:** Quellenvermerk mit Name des Bereitstellers, dem Zusatz „Data licence Germany
– attribution – Version 2.0" oder „dl-de/by-2-0" und einem Verweis auf den Datensatz
(URI); Aenderungen sind im Quellenvermerk zu kennzeichnen (ebd.).
Destatis selbst: „© Statistisches Bundesamt (Destatis), 2026. Data licence Germany -
attribution - version 2.0" (`destatis.de/EN/Service/Legal-Notice/_node.html`, abgerufen
2026-08-31).

**Inhalt:** Deutschland, tief gegliedert, ueberwiegend jaehrlich und quartalsweise.

**Urteil:** Lizenzseitig einwandfrei, aber ein Zwoelf-Laender-Modell braucht **eine**
Datenbasis mit einheitlicher Abgrenzung, keine zwoelf nationalen. Nur heranziehen, falls
Deutschland als Detailfall ausgebaut wird.

### 6. Our World in Data — **traegt formal, bringt aber nichts Eigenes**

**Lizenz im Wortlaut:** CC BY; „You do not need permission from us, and we do not sign
copyright release forms, provided that you cite us appropriately."
(`ourworldindata.org/faqs`, abgerufen 2026-08-31)

**Die Einschraenkung ist der ganze Punkt:** „Most of the data on Our World in Data comes
from third-party providers (such as the WHO, UN, and World Bank) and is subject to the
license terms of those providers. You should always check their license before reusing or
republishing the data." (ebd.)

**Urteil:** Kein eigenstaendiger Weg. Wer hier Wirtschaftsdaten holt, holt in Wahrheit
Weltbank- oder IWF-Daten und muss deren Bedingungen ohnehin pruefen -- dann gleich direkt.
Brauchbar allenfalls als Fundstelle, nicht als Lieferant.

### 7. Eurostat — **nur fuer EU- und EFTA-Laender**

**Lizenz im Wortlaut:** „Reuse of statistical data, metadata, publications, and other
dissemination tools published on this website for commercial or non-commercial purposes is
authorised provided the source is acknowledged."
(`ec.europa.eu/eurostat/en/help/copyright-notice`, abgerufen 2026-08-31)

**Auflagen:** Quellenangabe in der Form „Source: [DOI number of the Eurostat dataset],
[access date]" (ebd.).

**Die Ausnahmen entscheiden hier, und sie treffen genau diesen Zuschnitt.** Von der
gewerblichen Weiterverwendung ausgenommen und nur nichtgewerblich nutzbar sind unter
anderem: Daten fuer Nicht-EU/EFTA-Laender (die Seite nennt USA, Japan und China als
Beispiele), Handelsdaten mit Liechtenstein und der Schweiz als Meldeland, oesterreichische
Handelsdaten auf achtstelliger KN-Ebene sowie Ko-Publikationen mit fremdem Urheberrecht
(ebd.).

**Urteil:** Fuer ein Weltmodell mit zwoelf Laendern die falsche Quelle -- die grossen
Nicht-EU-Volkswirtschaften, ohne die das Produkt sinnlos waere, faellt sie gerade aus.
Verwendbar bliebe sie nur fuer die EU-Laender des Modells, und dort haben WDI und IWF
dieselben Groessen ohne Sonderregel. **Nicht einplanen.** Das ist der Fall, vor dem der
Auftrag warnt: perfekt aussehende Lizenz, Luecke in der halben Welt.

### 8. OECD — **ungeklaert, nicht einplanen**

**Lizenz, Wortlaut soweit belegbar:** Standardlizenz fuer Inhalte ab dem 2024-07-01 ist
CC BY 4.0; fuer aeltere Inhalte gelten die OECD-Nutzungsbedingungen, die erlauben, Inhalte
„for commercial and non-commercial purposes without seeking authorisation from the OECD"
zu nutzen, zu kopieren und zu verbreiten, bei Zitierung in der Form „[OECD (year), Title,
URL]". Bearbeitungen verlangen zusaetzlich einen Distanzierungshinweis („This is an
adaptation of an original work by the OECD…").
(`oecd.org/en/about/terms-conditions.html` und
`oecd.org/en/about/oecd-open-by-default-policy.html`) — **Beleghinweis:** Beide Seiten
haben den direkten Abruf am 2026-08-31 mit HTTP 403 abgewiesen; die Formulierungen stammen
aus Suchtreffern, nicht aus einem eigenen Seitenabruf.

**Die Mehrdeutigkeit, und deshalb faellt die Quelle vorerst aus:** Die zitierte
Erlaubnisklausel spricht durchgaengig von **„written content"** -- Publikationen und
Texten. Ob statistische Datenbanken darunter fallen, geht aus dem, was ich belegen konnte,
nicht hervor. Zwei Lesarten: (a) Die Pressemitteilung vom Juli 2024 spricht ausdruecklich
davon, dass „OECD data, publications and analysis" frei zugaenglich werden -- dann sind
Daten mitgemeint. (b) Die Terms unterscheiden „written content" von Daten, und fuer Daten
gilt etwas anderes, das ich nicht gefunden habe. Nach der Regel dieser Rolle gilt eine
Quelle ohne Lizenzzitat im Wortlaut als ungeprueft, nicht als erlaubt.

**Urteil:** Ungeprueft. Nicht in den Entwurf aufnehmen. Falls der Architekt sektorale
Tiefe braucht, die nur die OECD hat (STAN, Input-Output-Tabellen), ist das ein eigener,
kleiner Klaerungsauftrag -- kein Grund, den Kern daran zu haengen.

### 9. UNCTAD / UNCTADstat — **widerspruechlich, nicht einplanen**

**Zwei Aussagen, die sich beissen.** Auf der Copyright-Seite selbst steht die
UN-Standardklausel: „None of the materials provided on this web site may be used,
reproduced or transmitted, in whole or in part, in any form or by any means, electronic or
mechanical, including photocopying, recording or the use of any information storage and
retrieval system" ohne schriftliche Erlaubnis
(`unctadstat.unctad.org/EN/Copyright.html`, abgerufen 2026-08-31); dieselbe Seite verweist
zugleich auf eine Creative-Commons-Nutzungsbedingung, und das UNCTAD Data Hub gibt
CC BY 3.0 IGO an mit der Aussage, Daten duerften frei kopiert und weiterverbreitet werden,
sofern das Data Hub als Quelle genannt wird.

**Urteil:** Beide Lesarten stehen nebeneinander auf derselben Seite; ich waehle keine.
Solange das nicht aufgeloest ist, gilt die Quelle als ungeprueft. Sie wird auch nicht
gebraucht -- was UNCTAD an Handelsdaten liefert, deckt BACI unter klarer Lizenz ab.

### 10. UN Comtrade — **negativ fuer Rohdaten**

**Lizenz im Wortlaut:** „any copying, automated browsing or downloading, redistribution,
publication, or commercial exploitation of any material contained on or otherwise made
available to you on United Nations COMTRADE is strictly prohibited without the prior
written permission" (`comtrade.un.org/licenseagreement.html`, Abschnitt 5 „Usage",
abgerufen 2026-08-31).

**Die neuere Praxis daneben, weil sie milder klingt und es doch nicht ist:** Wer Original-
daten an Nicht-Abonnenten weitergibt und dabei 100.000 Datensaetze ueberschreitet, „must
pay the 'license to distribute' fee" **zusaetzlich** zu einem aktiven Premium-Abonnement;
und ausdruecklich: „There is no distinction between profit and non-profit when it comes to
re-dissemination." (`uncomtrade.org/docs/faqs-on-use-and-re-dissemination/`, abgerufen
2026-08-31).

**Urteil:** Fuer eingebettete Rohdaten **negativ** -- ein laufendes Abonnement plus Gebuehr
verstiesse gegen Hausregel 1 und waere bei einem Produkt zu 24,99 EUR ohnehin unsinnig.
Der Ausweg ist die transformierte Fassung (CEPII BACI, Nr. 3), die Comtrade selbst
freigibt. Comtrade bleibt damit **mittelbar** die Grundlage des Aussenhandelsteils, ohne
dass seine Bedingungen das Produkt beruehren.

### 11. FRED (Federal Reserve Bank of St. Louis) — **negativ**

**Lizenz im Wortlaut, soweit belegbar:** Reihen mit Copyright-Vermerk gehoeren Dritten;
vor jeder Nutzung ueber den persoenlichen Gebrauch hinaus ist die Erlaubnis des
Rechteinhabers einzuholen, und die gewerbliche Weiterverbreitung urheberrechtlich
geschuetzter Reihen ist ohne Zustimmung des Rechteinhabers nicht erlaubt; Nutzer duerfen
Schutzrechtsvermerke nicht entfernen oder veraendern
(`fred.stlouisfed.org/legal` und `fred.stlouisfed.org/docs/api/terms_of_use.html`) —
**Beleghinweis:** Der direkte Abruf beider Seiten wurde am 2026-08-31 mit HTTP 403
abgewiesen; die Bedingungen stammen aus Suchtreffern.

**Urteil:** **Negativ fuer das Einbetten.** FRED ist ein Aggregator: Der Lizenzstatus
haengt an der einzelnen Reihe, nicht an FRED, und muss je Reihe geklaert werden -- genau
die Arbeit, die kein Agent tragen sollte und die bei jeder Datenaktualisierung neu
anfiele. US-Groessen liefern WDI und IWF unter klarer Lizenz.

### 12. WTO — **negativ**

**Lizenz im Wortlaut:** „Unrestricted official WTO documents and legal texts are free for
public use"; sonstige Materialien duerfen nichtgewerblich genutzt werden, wenn die WTO
genannt und informiert wird; „Commercial use of materials from the website requires written
permission from the WTO." Eine Creative-Commons-Lizenz wird nicht angeboten.
(`wto.org/english/info_e/copyrights_permissions_e.htm`, abgerufen 2026-08-31)

**Urteil:** **Negativ.** Schriftliche Genehmigung ist kein Weg, den ein Agentenlauf gehen
darf (Hausregel 2). Damit ist die naheliegendste Zollquelle geschlossen -- siehe die Luecke
unten.

### 13. WITS (World Bank Integrated Trade Solution) — **negativ**

**Lizenz im Wortlaut:** WITS reicht die Auflagen seiner Lieferanten durch. Zu UN Comtrade:
Daten „may not be re-disseminated in any form without written permission of the United
Nations Statistics Division (UNSD)". Zur WTO-Datenbank: „re-dissemination by third parties
… must be approved by the WTO Secretariat prior to such re-dissemination", und
Veroeffentlichungen duerfen nicht feiner als die sechsstellige HS-Ebene sein. Fuer
UNCTAD TRAINS gilt eine eigene Nutzungsbedingung.
(`wits.worldbank.org/WITS/wits/registration/PrintTermsAndCondition.htm`, abgerufen
2026-08-31)

**Urteil:** **Negativ.** Dass WITS unter dem Dach der Weltbank laeuft, uebertraegt die
CC-BY-Lizenz der Weltbank nicht auf fremde Bestaende. Wichtig fuer die naechste Stufe:
Weltbank-Herkunft ist **kein** Freibrief; die Lizenz haengt am Datensatz, nicht am
Absender.

## Der Vorschlag

**Vier Quellen, arbeitsteilig:**

| Rolle im Modell | Quelle | Lizenz |
|---|---|---|
| BIP, Bevoelkerung, Inflation, Handelsvolumen, grobe Sektorstruktur | Weltbank WDI | CC BY 4.0 |
| Leitzins, Wechselkurs, Staatsschuld, Haushaltssaldo, Handelsaggregate | IWF (IFS, WEO, DOTS) | eigene Bedingungen, gewerblicher Verkauf erlaubt |
| bilaterale Handelsstroeme nach Ware | CEPII BACI | Etalab Open Licence 2.0 |
| Produktivitaet, Kapitalstock, Preisniveaus, Startjahrgaenge ab 1950 | Penn World Table 11.0 | CC BY 4.0 |

**Was dafuer zu tun ist -- Namensnennung, konkret.** Alle vier Lizenzen verlangen sie, und
drei von vier verlangen zusaetzlich die Kennzeichnung von Aenderungen. Ein Aggregieren auf
zwoelf Laender und sechs Sektoren und ein Umrechnen in Ganzzahlen ist eine Aenderung.
Deshalb an drei Stellen:

1. **Datei `LIZENZEN.md` neben der ausgelieferten Datendatei**, mit je Quelle: Name,
   Lizenzbezeichnung, Link auf den Lizenztext, Link auf den Datensatz, Abrufdatum des
   verwendeten Standes und die vorgeschriebene Zitierung (bei PWT die Feenstra-Inklaar-
   Timmer-Angabe im Wortlaut).
2. **Im Spiel selbst, auf einer Seite „Datenquellen"**, erreichbar aus dem Hauptmenue --
   nicht nur in einer Textdatei, weil ein Kaeufer die Zuordnung dort sucht, wo er die
   Zahlen sieht.
3. **Ein Satz zur Bearbeitung**, sinngemaess: *Die Ausgangsdaten wurden auf zwoelf Laender
   und sechs Sektoren aggregiert und fuer die Simulation in ganzzahlige Einheiten
   umgerechnet. Die Quellen verantworten diese Bearbeitung nicht.* Fuer die OECD-Fassung
   dieses Hinweises gaebe es einen vorgeschriebenen Wortlaut -- fuer die vier gewaehlten
   Quellen nicht, der Sinn genuegt.

**Dazu der IWF-Satz**, wegen der mehrdeutigen Klausel oben: *Die verwendeten
IWF-Statistikdaten sind beim IWF kostenfrei erhaeltlich.* Ein Satz, der eine offene Frage
schliesst, ist billiger als die Frage.

**Was ausdruecklich nicht noetig ist:** keine Registrierung, kein Abonnement, keine
Rueckfrage, keine Gebuehr -- also keine Gate-Vorlage nach Hausregel 1 fuer die Daten. Die
einzige bekannte Ausgabe des Vorhabens bleibt die Steam-Direct-Gebuehr aus der Idee.

**Und eine Konstruktionsauflage, die aus den Lizenzen folgt:** Der ausgelieferte
Datenstand muss **eingefroren und mit Abrufdatum versehen** sein. Nicht wegen der Lizenz,
sondern wegen der vierten Pruefachse: Der IWF revidiert WEO-Reihen rueckwirkend, BACI
revidiert das jeweils letzte Jahr, die Weltbank aktualisiert jaehrlich. Ein
Regressionstest gegen eine Sollreihe, die sich unter ihm veraendert, ist keiner. Der
jaehrliche Datenaktualisierungslauf aus der Rechnung der Idee erzeugt damit einen neuen,
eigenstaendig versionierten Jahrgang -- nicht ein Ueberschreiben des alten.

## Was das Modell braucht und was fehlt

Die Idee nennt zwoelf Laender, sechs Sektoren, Quartalsrunden und fuenf
Politikinstrumente. Danach geordnet:

**Belegt verfuegbar unter tragfaehiger Lizenz:**

| Groesse | Quelle | Auflösung |
|---|---|---|
| BIP je Land | WDI (ab 1960), PWT (ab 1950) | jaehrlich |
| Bevoelkerung, Erwerbstaetige | WDI, PWT | jaehrlich |
| Inflation / Verbraucherpreise | WDI, IWF IFS | jaehrlich / monatlich |
| Leitzins, Geldmenge, Wechselkurs | IWF IFS | monatlich, quartalsweise |
| Staatsschuld, Haushaltssaldo | IWF WEO | jaehrlich |
| Handelsvolumen gesamt | WDI | jaehrlich |
| bilaterale Handelsstroeme, Land-Land | IWF DOTS | quartalsweise |
| bilaterale Handelsstroeme nach Ware | CEPII BACI | jaehrlich |
| Produktivitaet, Kapitalstock, Preisniveau | PWT 11.0 (185 Laender, 1950-2023) | jaehrlich |

**Vier Luecken. Jede ist eine Entwurfsvorgabe fuer den Spielentwerfer, keine Randnotiz:**

1. **Sechs Sektoren gibt es nicht unter freier Lizenz.** WDI liefert die grobe Gliederung
   -- Landwirtschaft, Industrie, verarbeitendes Gewerbe, Dienstleistungen, also vier
   Positionen, davon eine als Teilmenge einer anderen. Feinere Gliederungen liegen bei
   OECD (ungeklaert, Nr. 8) und Eurostat (fuer Nicht-EU-Laender gesperrt, Nr. 7).
   **Vorgabe:** Entweder die Sektorzahl auf das absenken, was WDI hergibt (praktisch vier),
   oder die feineren Sektoren als **Modellkonstrukt** fuehren, das aus den groben
   aufgeteilt wird -- dann bezieht sich die vierte Pruefachse nur auf die aggregierte
   Ebene, und das gehoert offen gesagt.
2. **Sektorale Preise fehlen ganz.** Weder WDI noch PWT liefern sektorale Preisindizes im
   Laendervergleich. PWT liefert Preisniveaus je Land insgesamt. **Vorgabe:** Sektorpreise
   sind eine endogene Modellgroesse ohne Startwert aus Daten und **ohne Sollreihe** --
   der Rueckvergleich kann sie nicht pruefen.
3. **Zoelle -- das Instrument, um das sich das Spiel dreht -- sind die schwaechste
   Stelle.** Die drei ueblichen Quellen (WTO, WITS, UNCTAD TRAINS) sind allesamt gesperrt
   oder ungeklaert. WDI fuehrt einen aggregierten angewandten Zollsatz je Land, der aber
   erkennbar aus WITS abgeleitet ist und damit unter die Drittanbieter-Ausnahme fallen
   koennte. **Vorgabe:** Wenn nur ein Zollsatz je Land verfuegbar ist statt je Land und
   Sektor, dann ist das Instrument „Zoll auf Sektor 3" ein Modellkonstrukt ohne
   Datenanker. Das ist spielbar, aber es ist etwas anderes als die uebrigen Groessen, und
   der Entwurf sollte es nicht so aussehen lassen, als sei es dasselbe.
4. **Regierungszustimmung**, die Groesse, ueber die die Wirkungskette der Idee laeuft
   („Realeinkommen -0,4% -> Zustimmung Regierung -1,2"), hat unter den geprueften Quellen
   **keine** Entsprechung. Sie ist eine reine Modellgroesse. Das ist zulaessig -- aber sie
   liegt damit ausserhalb dessen, was die vierte Pruefachse pruefen kann, und das ist
   genau die Grenze, die `agentenbau.md` beschreibt.

**Und eine Auflösungsluecke, die den Spielentwurf direkt trifft:** Die Idee rechnet in
**Quartalsrunden**. Quartalsweise oder feiner liegen nur Zins, Wechselkurs und
DOTS-Handelsstroeme vor; BIP, Bevoelkerung, Sektorstruktur, Produktivitaet und Zoll sind
**jaehrlich**. Die Sollreihen der vierten Pruefachse sind damit ueberwiegend jaehrlich.
Zwei Wege, beide zu entscheiden, nicht von mir: Jahresrunden statt Quartalsrunden -- dann
passt der Rueckvergleich exakt, aber 60 Runden werden 60 Jahre. Oder Quartalsrunden mit
Rueckvergleich nur auf Jahresenden -- dann bleiben drei von vier Runden ungeprueft.
`agentenbau.md` verlangt die Masse im Entwurf, nicht in der Nachbereitung; das gehoert
dazu.

## Was unklar ist

- **Welche WDI-Reihen unter die Drittanbieter-Ausnahme fallen.** Die Weltbank-Lizenz ist
  eindeutig, die Reichweite ihrer Ausnahme nicht. Betroffen sind vermutlich die
  ILO-modellierte Beschaeftigung nach Sektor, der aus WITS abgeleitete Zollsatz und
  IWF-gestuetzte Preisreihen. **Zu tun vor dem Bau, nicht vor der Bewertung:** je
  einzubettender Reihe das Feld „Source" im Indikatorendatensatz lesen. Das sind
  ueberschaubar viele Reihen, sobald der Spielentwerfer sie benannt hat -- deshalb ist es
  seine Vorarbeit, nicht meine.
- **Der IWF-Wortlaut ist nur ueber eine Wortlaut-Suche belegt**, weil `imf.org` den Abruf
  mit HTTP 403 abweist. Dasselbe gilt fuer OECD und FRED. Der IWF-Satz ist der einzige
  davon, auf dem der Vorschlag ruht -- er gehoert vor dem Bau aus dem Volltext bestaetigt,
  etwa aus einem anderen Netz oder durch den Betreiber.
- **Ob die IWF-Klausel zum „standalone product" auf ein Spiel zutrifft.** Beide Lesarten
  stehen oben. Ich empfehle den Hinweissatz, weil er die Frage schliesst, statt sie zu
  entscheiden. Kein Rechtsrat.
- **OECD: „written content" oder auch Daten?** Ungeloest, siehe Nr. 8. Nur relevant, falls
  sektorale Tiefe jenseits der WDI-Gliederung gebraucht wird.
- **UNCTADstat widerspricht sich auf der eigenen Copyright-Seite.** Ungeloest, siehe Nr. 9.
  Fuer den Vorschlag ohne Folgen.
- **Die Frage nach den Personendaten stellt sich bei keiner der vier Quellen** -- es sind
  durchweg Laenderaggregate. Die Auflage aus `agentenbau.md` („echte Institutionen ja,
  echte lebende Personen nein") beruehrt damit nicht die Datenwahl, sondern nur, was das
  Spiel an Namen erfindet. Das ist Sache des Spielentwerfers und des Compliance-Pruefers.
- **Nicht geprueft, weil nicht beauftragt und nicht gebraucht:** Weltbank WITS-Alternativen
  fuer Zolldaten (etwa MacMap des ITC), V-Dem oder aehnliche Politikdatensaetze fuer die
  Zustimmungsgroesse. Beides waere ein kleiner Zusatzauftrag, falls der Spielentwerfer die
  Luecken 3 und 4 nicht als Modellkonstrukt fuehren will.
