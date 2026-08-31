---
id: 0004-xrechnung-aus-warenwirtschaft-export
titel: XRechnung aus dem Export einer nicht mehr gepflegten Branchensoftware
status: entwurf
erstellt: 2026-08-28
geaendert: 2026-08-28
rolle: wiedervorlage

quelle: signals/regulation/2026-08-27-e-rechnung-ausstellungspflicht-stufen.md

segment: Inländische Unternehmen mit Vorjahresumsatz über 800.000 Euro, die ihre Ausgangsrechnungen in einer älteren Branchen- oder Warenwirtschaftssoftware erzeugen, für die der Hersteller kein EN-16931-Update angekündigt hat (typisch: Werkstatt-, Labor-, Entsorgungs- und Werkstattsoftware kleiner Anbieter), und die aus dieser Software einen strukturierten Rechnungsexport als CSV oder XML ziehen können.
problem: Ab dem 1. Januar 2027 müssen diese Unternehmen E-Rechnungen im Format EN 16931 ausstellen. Ihre Rechnungen entstehen aber in einer Software, die dieses Format nicht kann und deren Hersteller es absehbar nicht nachrüstet. Ein Wechsel der Branchensoftware ist teuer und trifft den gesamten Betriebsablauf, nicht nur die Rechnungsstellung.
loesung: Ein Dienst, der den strukturierten Rechnungsexport der bestehenden Software entgegennimmt und daraus valide XRechnung- oder ZUGFeRD-Dateien erzeugt, ohne dass die Branchensoftware angefasst wird.
zahlungsgrund: zwang

ablehnungsgrund: null
ablehnungsgrund_alt: "G4 — das Segment ist ueber seine Heterogenitaet definiert: Gemeinsam ist den Kunden ausschliesslich, dass jeder eine andere, nicht mehr gepflegte Branchensoftware mit einem anderen Exportformat einsetzt. Kundenspezifische Feldzuordnung ist damit nicht ein Anlaufproblem, sondern der Kern des Produkts. Jeder Neukunde bringt eine eigene Zuordnung samt Sonderfaellen (Steuersaetze, Skonto, Reverse Charge, Kleinbetragsrechnung, auslaendische Kaeufer), die bei jeder Aenderung des Altsystem-Exports nachgezogen werden muss. Der Aufwand skaliert mit der Kundenzahl statt mit dem Rechnungsvolumen — genau die Pruefrage von G4. Der Ideator benennt diesen Punkt selbst als den, an dem die Idee vermutlich kippt. Verschaerfend: die Umwandlung ist monatlich terminkritisch; ein fehlgeschlagener Export blockiert die Rechnungsstellung des Kunden und erzwingt eine Reaktion am selben Tag, was zusaetzlich G3 beruehrt. Unsicherheit, widerlegbar: ein Nachweis, dass mindestens fuenf Branchensoftwares aus diesem Segment ein gemeinsames, vollstaendiges Exportformat liefern, das ohne kundenspezifische Zuordnung verarbeitbar ist, widerlegt die Ablehnung. Auch dann bliebe G7 offen — ein Preis im Centbereich je Rechnung traegt nach Steuern kein Nebengewerbe, und ein Grundpreis je Kunde ist bisher nur eine Ueberlegung."
wiedervorlage: "2026-08-31 -- G4 wurde geaendert: Arbeit, die ein Agent taeglich tun kann, zaehlt nicht mehr gegen die zwei Stunden. Die alte Ablehnung stuetzt sich genau darauf."

score:
  zwang: null
  erreichbar: null
  ruhe: null
  marge: null
  genehmigung: null
  summe: null
---

> **Wiedervorlage am 2026-08-31, nicht vom Ideator, sondern wegen einer Regelaenderung.**
>
> Die Ablehnung vom 2026-08-28 lautete auf G4 und stuetzte sich darauf, dass die
> kundenspezifische Feldzuordnung „nicht ein Anlaufproblem, sondern der Kern des
> Produkts" sei und der Aufwand mit der Kundenzahl statt mit dem Rechnungsvolumen
> skaliere. Das war unter der damaligen Fassung von G4 richtig.
>
> **G4 fragt seit dem 2026-08-31 nicht mehr, ob Arbeit mit der Kundenzahl waechst,
> sondern wer sie tut.** Eine Feldzuordnung aus einem Beispielexport herzuleiten und sie
> nachzufuehren, wenn das Altsystem sein Format aendert, ist Agentenarbeit. Damit faellt
> die tragende Haelfte der alten Begruendung weg.
>
> **Die andere Haelfte faellt nicht weg**, und sie ist zu pruefen: „die Umwandlung ist
> monatlich terminkritisch; ein fehlgeschlagener Export blockiert die Rechnungsstellung
> des Kunden und erzwingt eine Reaktion am selben Tag". Das beruehrt G3 und — seit
> derselben Aenderung — G6: Ein Agent, der unbeaufsichtigt im Rechnungslauf eines Kunden
> handelt, verwandelt Aufwand in Haftung. Pruefe beide einzeln.
>
> Die alte Begruendung steht vollstaendig in `ablehnungsgrund_alt`. Faellt dein Urteil
> wieder auf Ablehnung, ist das ein gueltiges Ergebnis — die Regelaenderung ist ein
> Grund zur erneuten Pruefung, keiner zur Annahme.

## Belege

- Ab dem 1. Januar 2027 müssen inländische Unternehmen mit einem Vorjahresumsatz (2026) über 800.000 Euro E-Rechnungen im EN-16931-Format ausstellen; ab dem 1. Januar 2028 gilt die Pflicht für alle nicht privilegierten inländischen B2B-Umsätze. — e-rechnungen.org, abgerufen 2026-08-27, erfasst in `signals/regulation/2026-08-27-e-rechnung-ausstellungspflicht-stufen.md`
- Seit dem 1. Januar 2025 müssen alle inländischen Unternehmen E-Rechnungen bereits empfangen können; die Empfangsseite ist also nicht das offene Problem, die Ausstellungsseite schon. — dieselbe Quelle, abgerufen 2026-08-27
- Kleinunternehmer nach § 19 UStG bleiben von der Ausstellungspflicht befreit. Sie gehören damit nicht zum Segment. — dieselbe Quelle, abgerufen 2026-08-27
- **Vermutung, ungeprüft und zentral:** Dass es eine nennenswerte Zahl von Unternehmen über 800.000 Euro Umsatz gibt, deren Branchensoftware bis 2027 kein EN-16931-Update erhält. Beobachtbar wäre das durch Sichtung der Produktankündigungen kleiner Branchensoftwarehäuser — bisher nicht erhoben. Fällt diese Vermutung, fällt die Idee.
- **Vermutung, ungeprüft:** Dass diese Software überhaupt einen strukturierten Export liefert, der Rechnungspositionen, Steuersätze und Käuferdaten vollständig enthält. Ohne diesen Export müsste aus PDF gelesen werden, und davon ist wegen der Fehlerfolgen abzusehen.

## Offene Fragen

- **Besetzung, entscheidend:** Wie viele Anbieter lösen genau diese Konvertierung bereits, und zu welchem Preis? Der Markt für E-Rechnungserzeugung ist dicht besetzt, und der Validator der KoSIT ist quelloffen und kostenfrei. Die Idee lebt einzig davon, dass die vorhandenen Angebote einen Wechsel der Rechnungssoftware verlangen statt die bestehende stehen zu lassen. Ist das nicht so, ist die Idee erledigt.
- Trägt der Preis pro Rechnung die Kosten nach Steuern? Bei einem Kunden mit 200 Rechnungen im Monat und einem Preis im Centbereich pro Rechnung entsteht kein Deckungsbeitrag, der ein Nebengewerbe rechtfertigt. Zu prüfen ist ein Grundpreis je Kunde statt einer Mengenabrechnung.
- Wie viele verschiedene Exportformate entstehen bei zehn Kunden aus zehn Branchensoftwares, und wie viel Aufwand kostet jedes neue? Skaliert der Aufwand mit der Kundenzahl, greift G4. Das ist der Punkt, an dem die Idee vermutlich kippt, und er ist vor allem anderen zu klären.
- **Haftung:** Eine falsch konvertierte Rechnung ist ein umsatzsteuerliches Problem des Kunden, kein rein technisches. Wie weit reicht die Verantwortung des Konverters bei einem Rundungs- oder Steuersatzfehler, und ist das versicherbar? Ohne Antwort ist G6 offen.
- Ist die Ausgabe einer formal validen Rechnungsdatei eine Aussage über die steuerliche Richtigkeit der Rechnung? Die Idee ist bewusst als reine Formatumwandlung ohne inhaltliche Prüfung formuliert; ob sich das im Verkauf durchhalten lässt, ist offen, weil der Kunde die Aussage „meine Rechnung ist rechtskonform" kaufen möchte. An genau dieser Stelle sind die Ideen 0001 und 0002 gescheitert.
- Über welchen Kanal erreicht man diese Unternehmen ohne Kaltakquise? Denkbar wären die Hersteller der Branchensoftware selbst als Partner, weil ihnen die Umwandlung ein Update erspart, das sie nicht bauen wollen.

## Warum jetzt

Der 1. Januar 2027 liegt vier Monate in der Zukunft, und die Stufung des Gesetzes erzeugt das Fenster: Bis Ende 2026 traf die Pflicht niemanden auf der Ausstellungsseite, ab 2028 trifft sie alle. Dazwischen liegt ein Jahr, in dem ausgerechnet die umsatzstärkeren Unternehmen als erste liefern müssen — das sind die, die eine gewachsene Branchensoftware im Einsatz haben und sie nicht kurzfristig ersetzen können. Vor einem Jahr war die Ausstellungspflicht angekündigt, aber ohne Stichtag, gegen den ein Betrieb hätte planen müssen. Zugleich ist ehrlich zu sagen: Das Thema E-Rechnung selbst ist alt und besetzt. Neu ist nur der Zuschnitt auf Betriebe, deren Software zurückbleibt — und ob dieser Zuschnitt trägt, ist die erste offene Frage oben.
