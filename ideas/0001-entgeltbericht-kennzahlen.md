---
id: 0001-entgeltbericht-kennzahlen
titel: Kennzahlengenerator für den Entgelttransparenzbericht
status: abgelehnt
erstellt: 2026-08-27
geaendert: 2026-08-27
rolle: fit-filter

quelle: signals/regulation/2026-08-27-entgelttransparenz-berichtspflicht.md

segment: Arbeitgeber in Deutschland mit 150 bis 249 Beschäftigten ohne eigene Personalcontrolling-Stelle, die die Löhne über eine Standardsoftware (DATEV Lohn und Gehalt, Lexware, Sage) abrechnen und deren Personalabteilung aus ein bis drei Personen besteht.
problem: Diese Arbeitgeber müssen erstmals zum 7. Juni 2027 einen Bericht über das geschlechtsspezifische Entgeltgefälle vorlegen. Die dafür nötigen Kennzahlen entstehen nicht in der Lohnbuchhaltung, sondern müssen aus dem Lohndatenbestand über Gruppen gleicher und gleichwertiger Arbeit gebildet werden.
loesung: Ein Webdienst, der einen pseudonymisierten Lohndatenexport entgegennimmt und daraus die berichtspflichtigen Entgeltkennzahlen sowie einen ausfüllbaren Berichtsentwurf erzeugt.
zahlungsgrund: zwang

ablehnungsgrund: "G5 — der berichtspflichtige Kennzahlensatz setzt die Einstufung in Gruppen gleicher und gleichwertiger Arbeit voraus. Das ist Subsumtion eines Einzelfalls unter eine Rechtsnorm, keine Rechenaufgabe. Bleibt die Einstufung beim Kunden, bleibt vom Produkt ein Taschenrechner ohne Zahlungsgrund; uebernimmt der Dienst sie, gibt er eine rechtliche Bewertung aus und faellt unter G5. Verschaerfend: am 2026-08-27 existiert kein deutsches Umsetzungsgesetz und kein Referentenentwurf, die zu erzeugenden Kennzahlen sind also nicht bekannt. Unsicherheit, widerlegbar: wenn ein verabschiedetes Umsetzungsgesetz die Kennzahlen abschliessend und ohne Wertungsspielraum definiert und die Gruppenbildung mechanisch aus Lohnartendaten ableitbar ist, ist die Idee erneut vorzulegen."

score:
  zwang: null
  erreichbar: null
  ruhe: null
  marge: null
  genehmigung: null
  summe: null
---

## Belege

- Arbeitgeber mit 150 bis 249 Beschäftigten müssen erstmals zum 7. Juni 2027 berichten, danach alle drei Jahre; ab 250 Beschäftigten jährlich, ebenfalls erstmals zum 7. Juni 2027. Berichtsgegenstand ist das geschlechtsspezifische Entgeltgefälle im Betrieb. — mgp-rechtsanwalt.de, abgerufen 2026-08-27, erfasst in `signals/regulation/2026-08-27-entgelttransparenz-berichtspflicht.md`
- Die EU-Umsetzungsfrist (7. Juni 2026) ist verstrichen, ohne dass ein deutsches Umsetzungsgesetz vorliegt; laut Quelle wird es für Anfang 2027 erwartet, ein Referentenentwurf fehlte zum Abrufdatum. — dieselbe Quelle, abgerufen 2026-08-27
- **Vermutung, ungeprüft:** Dass in der Größenklasse 150 bis 249 weder Personal noch Werkzeug für diese Auswertung vorhanden ist, ist nicht belegt. Es folgt nur aus der Annahme, dass Personalcontrolling als eigene Stelle erst oberhalb dieser Größe üblich wird.
- **Vermutung, ungeprüft:** Dass die Lohnabrechnungssoftware die Kennzahlen bis 2027 nicht selbst liefert. Genau das ist das größte Risiko der Idee — siehe offene Fragen.

## Offene Fragen

- Liefern DATEV, Lexware oder Sage die Berichtskennzahlen bereits als Modul oder haben sie es angekündigt? Wenn ja, ist die Idee erledigt, bevor sie beginnt.
- Welche Kennzahlen genau verlangt Art. 9 der Richtlinie 2023/970, und wie viele davon sind ohne die Einstufung in „Gruppen gleichwertiger Arbeit" berechenbar? Diese Einstufung ist eine Wertung des Arbeitgebers, keine Rechenaufgabe — sie muss beim Kunden bleiben, sonst kippt die Idee in Beratung.
- Wie viele Arbeitgeber in Deutschland fallen in das Band 150 bis 249 Beschäftigte? Die Zahl entscheidet über die Marktgröße und ist aus der Unternehmensstatistik ableitbar.
- Lässt sich der Datenimport so gestalten, dass keine Klarnamen und keine Einzelgehälter das Haus des Kunden verlassen? Lohndaten sind der heikelste Datenbestand eines Betriebs; ohne eine überzeugende Antwort ist die Idee unverkäuflich, unabhängig von der Rechtslage.
- Wird die Erstellung eines gesetzlich vorgeschriebenen Berichts als Rechtsdienstleistung gewertet, wenn das Werkzeug rechnet und der Arbeitgeber unterschreibt? Vermutlich nicht, aber die Grenze G5 verläuft laut `grenzen.md` früher als vermutet.
- Über welchen Kanal erreicht man diese Arbeitgeber ohne Kaltakquise? Steuerberater und Lohnbüros wären Multiplikatoren, aber die haben ein eigenes Interesse an der Leistung.

## Warum jetzt

Die Berichtspflicht ist neu und ihr erster Stichtag liegt zehn Monate in der Zukunft. Entscheidend ist aber die Reihenfolge: Das deutsche Umsetzungsgesetz wird erst für Anfang 2027 erwartet, der erste Bericht ist zum 7. Juni 2027 fällig. Zwischen Gesetz und Frist liegen damit nur wenige Monate. Große Anbieter von Personalsoftware bauen erfahrungsgemäß erst gegen den verabschiedeten Gesetzestext, was ihnen dasselbe kurze Fenster lässt. Vor einem Jahr gab es weder die verstrichene Umsetzungsfrist noch einen konkreten Stichtag, gegen den ein Arbeitgeber hätte planen können.
