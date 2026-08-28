---
id: 0004-xrechnung-aus-warenwirtschaft-export
titel: XRechnung aus dem Export einer nicht mehr gepflegten Branchensoftware
status: entwurf
erstellt: 2026-08-28
geaendert: 2026-08-28
rolle: ideator

quelle: signals/regulation/2026-08-27-e-rechnung-ausstellungspflicht-stufen.md

segment: Inländische Unternehmen mit Vorjahresumsatz über 800.000 Euro, die ihre Ausgangsrechnungen in einer älteren Branchen- oder Warenwirtschaftssoftware erzeugen, für die der Hersteller kein EN-16931-Update angekündigt hat (typisch: Werkstatt-, Labor-, Entsorgungs- und Werkstattsoftware kleiner Anbieter), und die aus dieser Software einen strukturierten Rechnungsexport als CSV oder XML ziehen können.
problem: Ab dem 1. Januar 2027 müssen diese Unternehmen E-Rechnungen im Format EN 16931 ausstellen. Ihre Rechnungen entstehen aber in einer Software, die dieses Format nicht kann und deren Hersteller es absehbar nicht nachrüstet. Ein Wechsel der Branchensoftware ist teuer und trifft den gesamten Betriebsablauf, nicht nur die Rechnungsstellung.
loesung: Ein Dienst, der den strukturierten Rechnungsexport der bestehenden Software entgegennimmt und daraus valide XRechnung- oder ZUGFeRD-Dateien erzeugt, ohne dass die Branchensoftware angefasst wird.
zahlungsgrund: zwang

ablehnungsgrund: null

score:
  zwang: null
  erreichbar: null
  ruhe: null
  marge: null
  genehmigung: null
  summe: null
---

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
