---
linse: wettbewerb
idee: 0005-zettelfoto-in-stundenzeile
datum: 2026-08-28
urteil: widerlegt
schwerster_einwand: Die Zettelerkennung ist als Produktkategorie international besetzt und bei 0,06 USD je Beleg commoditisiert, waehrend im deutschen Handwerk ein finanziertes Vertikal-Startup denselben Schmerz mit derselben Einsicht angreift — das „Warum jetzt" der Idee beschreibt kein offenes Fenster, sondern eines, das andere seit Jahren bedienen.
---

## Der Einwand

Die Idee steht und faellt mit der offenen Frage aus Zeile 38: Bieten die vorhandenen
Anbieter bereits eine Zettel-Fotoerfassung an? Die Antwort ist gestaffelt, und jede
Stufe trifft die Idee an einer anderen Stelle.

**Stufe 1 — die Technik ist Massenware, nicht neu.** „Timesheet OCR" ist im Englischen
eine ausgereifte Produktkategorie mit Vergleichstests. `imagetotable.ai` vergleicht
sieben Anbieter (ImageToTable, [Affinda](https://www.affinda.com/documents/timesheet/),
Parseur, Nanonets, Docsumo, Rossum, AWS Textract) und misst ausdruecklich
Handyfotos handschriftlicher Baustellen-Stundenzettel: „AI vision models handle phone
photos well — including angled shots, uneven lighting, and lower resolution",
85–95 % Feldgenauigkeit bei lesbarer Handschrift.
[timesheetocr.com](https://www.timesheetocr.com/) verkauft exakt den Zuschnitt der Idee —
Foto rein, Excel/CSV/JSON raus, Import in Lohnsysteme, Confidence-Scoring fuer unsichere
Felder — ab 29 USD im Monat.

Damit ist das „Warum jetzt" (Zeile 48) widerlegt. Nicht die Tatsachenbehauptung: Dass
multimodale Modelle das koennen, stimmt. Widerlegt ist der *Wettbewerbsschluss* daraus.
Ein Fenster, zu dem es 2026 bereits Vergleichslisten gibt, ist kein Fenster. Es ist ein
Markt, in den man als Letzter eintritt.

**Stufe 2 — der Preisanker steht schon.** ImageToTable verlangt 9 USD im Monat fuer 150
Dokumente, rund 0,06 USD je Beleg; AWS Textract 0,015 USD je Seite. Die Idee rechnet in
Zeile 41 mit rund 200 Zetteln je Betrieb und Monat. Ein Betrieb, der vergleicht — und
diese Betriebe vergleichen, sie kennen laut Segmentbeschreibung bereits die Apps —
findet einen funktionierenden Generalisten fuer den Gegenwert von zwei Stunden
Bueroarbeit im Jahr. Die Zahlungsbereitschaft wird zusaetzlich von oben gedeckelt:
plancraft, Craftnote oder HERO kosten eine aehnliche Groessenordnung und liefern
Auftragsverwaltung, Rechnung und Zeiterfassung mit. Eine reine Abtipphilfe muss sich
preislich zwischen einen 9-Dollar-Generalisten und eine Vollsoftware quetschen. Dort ist
kein Raum fuer eine Marge, die nach Steuern zwei Wochenstunden traegt.

**Stufe 3 — im deutschen Handwerk sitzt bereits jemand auf der Einsicht.**
[Valoon GmbH](https://valoon.chat/en/funktionen/digital_timesheet) (Dortmund und
Karlsruhe) laesst Mitarbeiter Stundenzettel **im WhatsApp-Chat** ausfuellen — ohne
App-Installation, ohne Schulung. Das ist derselbe Ausgangsbefund wie in der Idee („der
Zettel gewinnt, weil er schneller ist als jede App"), nur konsequenter zu Ende gedacht:
Valoon beseitigt den Grund fuer den Zettel, statt den Zettel zu verarbeiten. Und sie
liefern genau das, was die Idee als Alleinstellung plant — „Exporte in
firmenspezifischen Layouts" an DATEV, dazu REST-API zu ERP- und Bausoftware. Das
Unternehmen ist kein Bastelprojekt: Landessieger OUT OF THE BOX.NRW 2025, Sonderpreis
NRW.Global Business, Messestand auf „Zukunft Handwerk", Mitglied im BDBau, zwei
Standorte. Gegen einen Wettbewerber mit Vertrieb, Messebudget und Verbandsnetzwerk
antreten zu wollen, ist die Definition von „zu gross fuer einen Nebenerwerb".

**Stufe 4 — der Nachbau kostet die Etablierten fast nichts.** Ich habe im deutschen
Handwerksmarkt tatsaechlich keinen Anbieter gefunden, der Papierzettel *fotografiert
einliest*. Das ist aber, wie es die Rollenanweisung verlangt, kein Freibrief, sondern
das lauteste Warnsignal des ganzen Laufs. Ein Dutzend Anbieter (plancraft, Craftnote,
openHandwerk, HERO, meisterwerk, 123erfasst, STREIT Zeit+, WinWorker, smartzeit,
digiholz, Labelwin, MeinHandwerker) kennt den Schmerz woertlich — openHandwerk bewirbt
ihn im eigenen Blog als „Abtippen und Pruefen der einzelnen Eintraege". Sie haben sich
alle fuer das Ersetzen des Papiers entschieden, nicht fuer das Lesen. Entweder irren
sich zwoelf Anbieter mit weit mehr Kundengespraechen gleichzeitig — oder das Lesen des
Zettels ist strategisch das schlechtere Geschaeft, weil es eine Bruecke in einen
Arbeitsablauf baut, den der Kunde gerade verlaesst.

Und wenn einer von ihnen es doch will, ist es ein Bildschirm plus ein API-Aufruf.
[natif.ai](https://natif.ai/ocr-and-htr/) aus Saarbruecken verkauft
Handschriftenerkennung (HTR) mit selbst definierbaren Extraktionsfeldern, DSGVO- und
Schrems-II-konform, von der Stange; Kodak Alaris und Workist bedienen dasselbe Feld.
Die Idee ist damit lehrbuchhaft „eine Funktion in fremder Software" — und zwar eine
besonders attraktive, weil sie als *Migrationshilfe* im Verkaufstrichter wirkt: „Schreibt
weiter auf Papier, wir lesen die Zettel, und wenn ihr soweit seid, tippt ihr direkt."
Ein Anbieter, der Abonnements verkauft, verschenkt so etwas im Onboarding. Ein
Nebenerwerb, der davon leben muss, kann dagegen nicht bepreisen.

**Zum Zeitpunkt.** Das Fenster schliesst nicht an einem Stichtag — die Begruendung der
Idee ist ausdruecklich technischer, nicht regulatorischer Natur (Zeile 48). Das ist
schlechter, nicht besser: Ein Stichtag waere ein Termin, den man bedienen kann. Eine
commoditisierte Faehigkeit ohne Stichtag hat gar kein Fenster, sondern nur einen
Rueckstand, der jede Woche waechst, in der Valoon Messen besucht und wir zwei Stunden
haben.

## Was ihn entkraeften wuerde

Ich lasse mich umstimmen, wenn eines davon nachgewiesen wird:

1. **Der Formatgraben traegt.** Nachweis, dass drei bis fuenf konkrete Zielsysteme
   (etwa Labelwin, STREIT, WinWorker, DATEV Lohn) ein dokumentiertes, stabiles
   Importformat haben, das *einmal* gebaut und nicht je Kunde gepflegt werden muss.
   Genau daran ist Idee 0004 gestorben; Valoon loest es mit „firmenspezifischen
   Layouts", also mit Personal. Ohne diesen Nachweis skaliert der Aufwand mit der
   Kundenzahl und die Idee ist ein zweites Mal dieselbe Falle.
2. **Ein Zielsystem-Hersteller will zuliefern statt nachbauen.** Eine schriftliche
   Aussage eines Handwerkersoftware-Anbieters, dass er eine Zettelerkennung *nicht*
   selbst plant und einen Zulieferer nehmen wuerde. Das kehrt Stufe 4 um und macht aus
   dem gefaehrlichsten Wettbewerber einen Kanal.
3. **Belegte Zahlungsbereitschaft ueber dem Generalistenpreis.** Drei Betriebe des
   Zielsegments, die schriftlich einen Monatspreis nennen, der deutlich ueber den
   9 bis 29 USD der Generalisten liegt — und zwar *nachdem* ihnen ImageToTable und
   Valoon gezeigt wurden. Ein Preis, der ohne Kenntnis der Alternativen genannt wird,
   zaehlt nicht.

Punkt 3 ist der billigste und sollte vor allen anderen kommen. Faellt er, ist die Idee
unabhaengig von jeder Technikfrage erledigt.

## Quellen

Alle Recherchen am 2026-08-28.

**Gefundene Anbieter, direkt:**
- [timesheetocr.com](https://www.timesheetocr.com/) — Foto handschriftlicher
  Stundenzettel zu Excel/CSV/JSON, Lohnsystem-Integration, 29 USD/Monat fuer 100 Seiten,
  90–97 % angegebene Genauigkeit. Deutsche Sprachunterstuetzung nicht ausgewiesen.
- [imagetotable.ai, Vergleich 2026](https://imagetotable.ai/blog/best-timesheet-extraction-tools-2026)
  — sieben Anbieter, 9 USD/Monat fuer 150 Dokumente (0,06 USD je Beleg), 85–95 %
  Feldgenauigkeit bei Handschrift, ausdruecklich Handyfotos.
- [Affinda Timesheet](https://www.affinda.com/documents/timesheet/), Parseur, Nanonets
  (~0,30 USD je Block), Docsumo, Rossum, AWS Textract (~0,015 USD je Seite) — ebenda.
- [Valoon GmbH, digitaler Stundenzettel](https://valoon.chat/en/funktionen/digital_timesheet)
  — WhatsApp ohne App-Installation, DATEV-Export in firmenspezifischen Layouts,
  REST-API, Zielbranchen Bau/Handwerk/FM.
- [Valoon im Startup-Atlas](https://www.startup-atlas.de/company/valoon) und
  [Zukunft Handwerk](https://www.zukunfthandwerk.com/de/entdecken/beitraege/whatsapp-wird-zum-digitalen-bautagebuch-besuchen-sie-uns-am-valoon-stand)
  — Standorte Dortmund/Karlsruhe, Landessieger OUT OF THE BOX.NRW 2025, Messepraesenz.
- [natif.ai OCR & HTR](https://natif.ai/ocr-and-htr/) — deutsche
  Handschriftenerkennung mit eigenen Extraktionsfeldern, DSGVO/Schrems II; macht den
  Nachbau durch Etablierte billig.
- [Kodak Alaris, handschriftlich ausgefuellte Dokumente](https://posteingang-automatisieren.alarisworld.com/handschriftlich-ausgefuellte-dokumente/),
  [Workist OCR-Vergleich 2026](https://www.workist.com/blog/ki-ocr-software-anbieter-vergleich-2026)
  — dasselbe Feld, Unternehmensmarkt.

**Anbieter, die den Zettel ersetzen statt lesen** (Beleg fuer die strategische
Entscheidung der Etablierten):
[plancraft](https://plancraft.com/de-de/funktionen/zeiterfassung-handwerk),
[HERO](https://hero-software.de/features/zeiterfassung-app/stundenzettel),
[openHandwerk](https://openhandwerk.de/blog/stundenzettel-digitalisieren-wie-handwerksbetriebe-mit-digitaler-zeiterfassung-den-papierkram-besiegen/)
(benennt den Abtipp-Schmerz woertlich),
[meisterwerk](https://www.meisterwerk.app/mobile-zeiterfassung-handwerk),
[123erfasst](https://123erfasst.de/zeiterfassung-handwerk/),
[STREIT Zeit+](https://www.streit-software.de/handwerkersoftware/apps/mobile-zeiterfassung),
[WinWorker](https://www.winworker.de/produkte/mobile-zeiterfassung/),
[smartzeit](http://www.smartzeit.de/zeiterfassung-handwerk/),
[digiholz](https://digiholz.de/zeiterfassung-elektronische-stundenzettel),
[Labelwin](https://www.label-software.de/labelwin/zeiterfassung-lohn),
[MeinHandwerker](https://mein-handwerker-app.de/),
[craftivo](https://www.craftivo.app/funktionen).

**Substitut aus anderer Richtung:**
[ki-spezial.systems](https://ki-spezial.systems/ki-handwerk.html) — Sprache-zu-Text fuer
Aufmass, Maengel, Material im Handwerk. Greift denselben Schmerz (nicht tippen wollen)
ohne Papier an. Einstieg laut Anbieter „im niedrigen vierstelligen Bereich", also
Projektgeschaeft, kein Produkt.

**Ergebnislose Suchen** (dokumentiert, weil das Fehlen selbst der Befund ist):
- „Stundenzettel abfotografieren App Handschrift automatisch erfassen Handwerk"
- „Handwerkersoftware Stundenzettel fotografieren KI erkennen Papier bleibt Import DATEV Lohn"
- „Stundenzettel OR Rapportzettel abfotografieren Handschrift KI auslesen Anbieter Handwerk Baustelle Deutschland"
- „Craftnote plancraft openHandwerk KI Dokumentenerkennung Foto scannen Funktion neu 2026"

Kein deutscher Handwerks-Anbieter mit Foto-Erkennung von Papierzetteln gefunden. Bei
einer Technik, die international bei 0,06 USD je Beleg liegt, ist die wahrscheinlichere
Erklaerung fuer diese Luecke, dass die Nische nicht zahlt — nicht, dass sie uebersehen
wurde.
