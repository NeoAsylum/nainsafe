---
id: 0009-haushaltsturnus-monatsabrechnung
titel: Monatsrechnung aus den tatsächlich gefahrenen Haushaltsterminen
status: entwurf
erstellt: 2026-08-28
geaendert: 2026-08-28
rolle: ideator

quelle: signals/modelle/2026-08-28-vertikale-software-privathaushalts-reinigungsfirmen.md

segment: Inhabergeführte Reinigungsfirmen in Deutschland mit einer bis zehn Reinigungskräften, die überwiegend Privathaushalte im festen Turnus reinigen (wöchentlich oder vierzehntägig) und ihre Kunden selbst gewonnen haben, also nicht über Helpling, ExtraSauber oder Book a Tiger vermittelt sind. Auffindbar über die Innungen des Gebäudereiniger-Handwerks und über Betriebe, die auf ihrer eigenen Seite Privathaushalte ansprechen.
problem: Abgerechnet wird nicht ein fester Monatsbetrag, sondern was im Monat tatsächlich stattgefunden hat — vier oder fünf Termine je nach Kalender, abzüglich abgesagter und zuzüglich nachgeholter Einsätze, bei vielen kleinen Beträgen gegen viele Privatpersonen. Die deutsche Branchensoftware für dieses Gewerk ist auf das Objekt und den gewerblichen Auftraggeber zugeschnitten, die Buchhaltungsschicht auf den gleichbleibenden Abobetrag.
loesung: Ein Dienst, der je Haushalt Turnus und Preis führt, daraus die Solltermine des Monats erzeugt, Absagen und Nachholtermine mitnimmt und am Monatsende die Rechnungen genau über die stattgefundenen Einsätze stellt — mit dem vom Betrieb selbst gesetzten Arbeitskostenanteil getrennt ausgewiesen.
zahlungsgrund: nutzen

ablehnungsgrund: null

score:
  zwang: null
  erreichbar: null
  ruhe: null
  marge: null
  genehmigung: null
---

## Belege

- Ein deutschsprachiges Produkt der Kategorie „maid service software" existiert nach 19 Suchen über zwei Recherchen nicht — auch nicht in Österreich oder der Schweiz. Die Kategorie selbst existiert auf Deutsch: `capterra.com.de/directory/10062/maid-service/software` führt unter „Haushaltsservice Software" 48 Produkte, **kein einziges aus DACH**. — `research/2026-08-28-vertikale-software-privathaushalts-reinigungsfirmen.md`, Abschnitt 2f, abgerufen 2026-08-28
- Die deutschen Kleinbetriebs-Anbieter adressieren die Größenklasse ausdrücklich, aber mit Objektlogik: Meisterwerk benennt auf seiner Reinigungsfirmen-Seite „1–3 Mitarbeiter", „4–10 Mitarbeiter" mit dem „größten Mehrwert" und „ab 10 Mitarbeitern: Springer-System". Was diese Produkte nicht abbilden, ist die Privatkundenbeziehung. — `blog.meisterwerk.app/gewerke/reinigungsfirma`, abgerufen 2026-08-28, über dieselbe Recherche, Abschnitt 2c
- Im Kleinbetriebssegment dieses Gewerks wird für Software nachweislich bezahlt: MFR ab 29 EUR, Meisterwerk ab 49 EUR inkl. drei Nutzern, OfficeOn ab 49,99 EUR, HERO ab 59 EUR. Meisterwerk nennt selbst einen Marktkorridor von „zwischen 15 und 50 Euro pro Mitarbeitenden". — dieselbe Recherche, Abschnitte 2c und 3, abgerufen 2026-08-28
- Der Betriebsbestand wächst: Gebäudereinigung auf Rang zwei der Betriebsbestände der Anlage B1 (Statista, Berichtsjahr 2024), Anlage B1 insgesamt +1,5 % im 1. Halbjahr 2025 (`zdh-statistik.de`), allein in Baden-Württemberg 1.371 neue Gebäudereiniger-Betriebe 2025 (HANDWERK BW). — dieselbe Recherche, Abschnitt 1, alle abgerufen 2026-08-28
- Das Vorbild ist seit dem 02.01.2017 nicht weiter internationalisiert und unterstützt ausschließlich Englisch; Deutschland, Sprachen und Währungen kommen auf seiner Internationalisierungsseite nicht vor. Ein Markteintritt ist weder angekündigt noch vorbereitet. — `zenmaid.com/for-international-maid-services/` und `connecteam.com/reviews/zenmaid/`, abgerufen 2026-08-28, über dieselbe Recherche, Abschnitt 2g
- Das Segment ist **nicht bezifferbar**. Belegbar sind nur Hüllzahlen: 34.824 Betriebe im Gebäudereiniger-Handwerk (2024), davon rund 80 % unter 500.000 EUR Jahresumsatz. Keine Statistik trennt nach Kundenart; die einschlägige BMBFSFJ-Studie war auch im zweiten Anlauf nicht auswertbar. Die Recherche verbietet ausdrücklich, aus diesen Zahlen eine Zielgruppengröße zu machen. — dieselbe Recherche, Abschnitte 1 und 5c
- **Vermutung, ungeprueft:** Dass die Abrechnung nach stattgefundenen statt nach vereinbarten Terminen der Punkt ist, an dem die vorhandene Buchhaltungsschicht (Lexware Office, sevdesk, orgamax — alle mit eigener Reinigungsfirmen-Landingpage) nicht mehr trägt. Die Recherche stellt fest, dass diese Anbieter „Rechnung, Aborechnung, Kundenstamm, teils Terminkalender" zu Buchhaltungspreisen liefern; ob deren Aborechnung mit schwankender Terminzahl umgeht, ist nicht geprüft.
- **Vermutung, ungeprueft:** § 35a EStG verlangt für den Steuerabzug haushaltsnaher Dienstleistungen eine Rechnung und unbare Zahlung, und abziehbar sind nur die Arbeitskosten. Daraus wäre ein Grund abzuleiten, warum der Privathaushalt eine Rechnung mit getrenntem Arbeitskostenanteil verlangt. Im Repo liegt dazu **keine Recherche**, und ich habe den Gesetzestext nicht gegen eine Primärquelle geprüft.

## Offene Fragen

- **Besetzung, entscheidend und vor allem anderen zu klären:** Rechnen Lexware Office, sevdesk oder orgamax eine wiederkehrende Leistung mit schwankender Terminzahl ab, oder nur einen festen Abobetrag? Der ganze Zuschnitt lebt davon, dass genau hier eine Lücke ist. Ist sie es nicht, ist die Idee erledigt — und zwar gegen einen Wettbewerber, der einstellige bis niedrig zweistellige Monatsbeträge nimmt.
- **Die offene Frage der Recherche, die die Idee kippt:** Verwaltet ExtraSauber UNLIMITED auch selbst gewonnene, nicht vermittelte Kunden? Fünf öffentliche Quellen plus AGB geben keine Antwort; klärbar nur durch Anmeldung oder Anruf. Fällt es positiv aus, bedient ExtraSauber dasselbe Segment mit derselben Aufgabe zum Softwarepreis null, und das Segment ist besetzt.
- **G7, der Preisboden:** Vier Terminbuchungssysteme mit dauerhaft kostenloser Stufe und deutschsprachiger Reinigungs-Landingpage (SuperSaaS, EasyWeek, SimplyBook.me, Setmore), dazu ExtraSauber ohne Softwaregebühr. Die Decke liegt bei 49 EUR (Meisterwerk) bzw. rund 35 EUR ARPU beim Vorbild. Trägt ein Preis in diesem Korridor nach Steuern ein Nebengewerbe, wenn die Zielgruppengröße unbekannt ist?
- **G7, zweite Seite:** Die Recherche beziffert den Verwaltungsanteil im Stundenverrechnungssatz auf 2,6 % (Beispielkalkulation `1a-reinigungsberatung.de`, Tarifstand April 2025) bis 8 % (CleanCalc). Bei einem kleinen Betrieb ist das ein einstelliger bis niedrig zweistelliger Eurobetrag im Monat — **darunter liegt jedes Abo, über das hier gesprochen wird**. Der Nutzen muss also aus etwas anderem kommen als aus gesparter Verwaltungszeit: aus Rechnungen, die sonst vergessen werden. Ob das vorkommt, ist unbelegt.
- **G5:** Der getrennte Ausweis der Arbeitskosten ist der Betrag, den der Betrieb selbst gesetzt hat, und der Dienst trifft keine Aussage darüber, ob der Abzug beim Haushalt zulässig ist. Reicht diese Trennung, oder ist bereits die Ausgabe eines als steuerlich relevant bezeichneten Betrags eine Hilfeleistung in Steuersachen? An genau dieser Verwechslung von Umformung und Wertung ist Idee 0007 gestorben. Im Zweifel muss der Begriff „§ 35a" im Produkt gar nicht vorkommen.
- **G3, die Norm der Kategorie:** CleanManager wirbt mit „persönlichen Softwareeinführungen", ExtraSauber mit „regelmäßigem Coaching", Meisterwerk nennt „E-Mail- & Telefon-Support und die Einführung" ausdrücklich als immer inklusive. Kauft dieses Segment ein Werkzeug ohne synchrone Einführung überhaupt? Daran sind die Ideen 0006 und 0008 gestorben, dort an der Einrichtungsseite.
- **G4:** Bringt jeder Betrieb eigene Turnus-Sonderfälle mit (Feiertage, Urlaub des Haushalts, Sommerpause, wechselnde Wochentage)? Wenn diese Regeln je Kunde gepflegt werden müssen statt aus einer Handvoll Muster zu kommen, skaliert der Aufwand mit der Kundenzahl — die Konstellation, an der Idee 0004 gestorben ist.
- **Erreichbarkeit ohne Kaltakquise:** Innungen des Gebäudereiniger-Handwerks, Gründungsleitfäden wie `fixklar.de`, Fachforen. Ob es ein Forum dieses Gewerks mit lebendiger Kleinbetriebs-Diskussion gibt, ist nicht geprüft.

## Zustand als Text

- **Übersicht:** `42 Haushalte, 168 Solltermine im August, 161 gefahren, 5 abgesagt, 2 offen; 39 Rechnungen erzeugt, 3 Haushalte ohne Zahlungseingang seit 21 Tagen.`
- **Detail:** Ein Haushalt vollständig — Turnus, Wochentag, Preis je Einsatz, Arbeitskostenanteil, Zahlungsweg, die letzten zwölf Einsätze mit Datum, Dauer und ausführender Kraft, offene Posten.
- **Veränderung:** Diff zwischen zwei Monatsabschlüssen — `+2 Haushalte, −1 gekündigt, 7 Termine mehr als im Vormonat, Umsatz +214 EUR, eine Rechnung storniert`.

Der Kern des Produkts ist eine Tabelle, kein Bild. Eine Gestaltungsentscheidung des Betreibers wäre bei der Rechnungsvorlage nötig — einmalig und danach höchstens jährlich, wenn sich Pflichtangaben ändern.

## Warum jetzt

Zwei Änderungen, beide belegt und beide aus 2025/2026. Erstens der Branchenmindestlohn von 15,00 EUR in Lohngruppe 1 ab dem 01.01.2026: Er verteuert die legal kalkulierte Stunde gegen die 15 bis 25 EUR bar, die in über vier Millionen Haushalten gezahlt werden, und lässt einem Betrieb weniger Spielraum für vergessene oder falsch gestellte Rechnungen. Zweitens wächst der Betriebsbestand des Gewerks messbar, während das amerikanische Vorbild seit 2017 nicht weiter internationalisiert wurde und kein deutsches Startup dieser Nische eine Finanzierungsrunde 2025 oder 2026 gezeigt hat. Es gibt hier also gerade keinen frisch finanzierten Marktführer, der die Lücke schließt — anders als im Handwerks-Stundenzettel-Lauf.

Ehrlich dagegen zu halten ist: Das Problem ist alt, und die Lücke ist schmal. Sie besteht nicht darin, dass es keine Software gäbe, sondern darin, dass die vorhandene deutsche Software das Objekt kennt und den Haushalt nicht. Trägt dieser Unterschied nicht, trägt die Idee nicht.
