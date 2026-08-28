---
id: 0007-marktplatz-csv-in-buchhaltungsformat
titel: Monatsabschluss aus den CSV-Exporten mehrerer Marktplätze
status: entwurf
erstellt: 2026-08-28
geaendert: 2026-08-28
rolle: ideator

quelle: signals/pain/2026-08-28-etsy-verkaeufer-csv-buchhaltung-manuell.md

segment: Verkäufer in Deutschland, die parallel auf zwei oder mehr Marktplätzen (Etsy, Amazon, eBay) anbieten, ihre Einnahmenüberschussrechnung selbst erstellen oder ihrem Steuerberater die Zahlen zuliefern und keine Warenwirtschaft betreiben — typisch Handmade- und Kleinserienverkäufer im nebenberuflichen bis kleingewerblichen Bereich.
problem: Jede Plattform exportiert ein eigenes CSV-Format, und keines davon trennt Umsatz, Plattformgebühren, Werbung, Versand, Verpackung und Rücksendungen so, wie die Buchhaltung sie braucht. Der Verkäufer sitzt deshalb Monat für Monat mit Excel und Taschenrechner davor — wörtlich belegt, samt der Selbsthilfe, sich irgendwann eine eigene Vorlage mit Skript zu bauen.
loesung: Der Verkäufer lädt die Rohexporte seiner Plattformen hoch und bekommt eine einzige normalisierte Monatsdatei zurück, in der jede Zeile einer Buchungsart zugeordnet ist und die sich in gängige Buchhaltungen einlesen lässt — reine Umformung, keine steuerliche Aussage.
zahlungsgrund: nutzen

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

- „die Daten zu formatieren war muehsam, jede Plattform hatte ihre Eigenheiten" — Nutzer „MatildaHomeShop", community.etsy.com, Thread „CSV Excel Buchhaltung Finanzbuchhaltung Ads Bestellungen", abgerufen 2026-08-28, erfasst in `signals/pain/2026-08-28-etsy-verkaeufer-csv-buchhaltung-manuell.md`
- „saß ich Monat fuer Monat mit Excel, Taschenrechner und einer ordentlichen Portion Frust." — derselbe Nutzer, dieselbe Quelle, abgerufen 2026-08-28
- Die Selbsthilfe war eine eigene Excel-Vorlage samt „kleinem Script", die „Herstellungskosten, Verpackung, Versand und Plattformgebuehren" aufschlüsselt. Das ist die genaue Funktionsbeschreibung des Produkts, aus dem Mund eines Betroffenen. — dieselbe Quelle, abgerufen 2026-08-28
- Das Thema taucht in derselben Community wiederholt auf: weitere Threads zu CSV-Importproblemen, ein kommerzieller CSV-Konverter, den jemand aus diesem Anlass gebaut und verkauft hat, sowie eine Umfrage zur passenden Buchhaltungssoftware. Wiederholung in einer Community ist der stärkere Beleg als der Einzelbeitrag. — dieselbe Quelle, abgerufen 2026-08-28
- Gegenbeleg, ausdrücklich: Der zitierte Verkäufer hat sein Problem selbst gelöst und nutzt inzwischen ELSTER direkt statt eines Steuerberaters. Als Käufer fällt er aus. — dieselbe Quelle, abgerufen 2026-08-28
- **Vermutung, ungeprueft:** Größe der Gruppe, die das Problem noch hat. Das Signal markiert sie selbst als unbekannt.

## Offene Fragen

- **Besetzung, entscheidend:** Der kommerzielle CSV-Konverter aus dem Nachbar-Thread ist zu finden und zu bewerten, ebenso die etablierten Marktplatz-Buchhaltungsdienste. Deckt einer davon den Zuschnitt „mehrere Plattformen, kleine Mengen, kein Abo im dreistelligen Bereich" bereits ab, ist die Idee erledigt. Diese Frage geht allen anderen vor.
- **G4, und hier liegt der Unterschied zu Idee 0004:** Dort war das Segment über seine Heterogenität definiert — jeder Kunde eine andere Altsoftware, also kundenspezifische Feldzuordnung als Kern des Produkts. Hier ist die Formatvielfalt plattformseitig und für alle Kunden identisch: drei bis fünf Exportformate bedienen jeden Verkäufer. Der Pflegeaufwand skaliert mit der Zahl der Plattformen, nicht mit der Kundenzahl. Zu prüfen bleibt, wie oft die Plattformen ihre Exportformate ändern und wie schnell ein Bruch auffällt und behoben werden muss — bricht das Format am Monatsanfang, will jeder Kunde gleichzeitig etwas.
- **G5, sauber zu halten:** Die Zuordnung „Werbekosten sind Betriebsausgabe" ist eine steuerliche Aussage. Der Entwurf schuldet deshalb ausschließlich die Umformung und Gruppierung nach den Bezeichnungen der Plattform, nicht die Kontierung. Hält diese Trennung im Verkauf, oder will der Kunde genau die fertige EÜR? An dieser Stelle sind die Ideen 0001 und 0002 gestorben.
- **Sonderfälle, die die Umformung nichttrivial machen:** Rücksendungen über den Monatswechsel, Gutschriften, Fremdwährungsumsätze, Auszahlungen, die nicht auf die Summe der Bestellungen passen, und die Frage, ob Umsatzsteuer je Zeile ausgewiesen ist. Zu klären ist, ob sich das ohne Wertung lösen lässt oder ob genau hier die Kontierung anfängt.
- **G7:** Zielgruppe sind nebenberufliche Verkäufer, die typischerweise zwischen 5 und 20 Euro im Monat für Werkzeuge ausgeben. Was trägt das nach Steuern, und wie viele Kunden braucht es? Zu rechnen ist auch ein Jahrespreis, weil der Schmerz zur Steuererklärung am größten ist.
- Erreichbarkeit ohne Kaltakquise: Die Community, aus der das Signal stammt, ist der naheliegende Kanal — zugleich einer, in dem Eigenwerbung schlecht ankommt. Zu klären ist, welcher Weg dorthin zulässig und tragfähig ist.
- **Vollständigkeit statt Formatierung:** Der eigentlich wertvolle Teil könnte der Abgleich sein, ob die Plattformauszahlung zur Summe der Bestellungen passt. Ob das ein eigener Zuschnitt ist oder eine Funktion dieses hier, ist offen.

## Warum jetzt

Die ehrliche Antwort ist unbequem: An diesem Problem hat sich seit Jahren wenig geändert, und genau das ist ein Warnzeichen. Was sich geändert hat, ist die Zahl der Verkäufer, die auf mehr als einer Plattform gleichzeitig anbieten — das Signal beschreibt Etsy, Amazon und eBay bei derselben Person, und erst diese Mehrfachpräsenz macht aus „ein Export einlesen" das Problem „drei unvereinbare Exporte zusammenführen". Ein Verkäufer auf einer einzigen Plattform hätte diesen Schmerz nicht.

Zweitens ist der Bau eines solchen Umformers heute eine Frage von Tagen statt von Wochen, weil die Formaterkennung und die Zuordnung neuer Spaltennamen sich modellgestützt erledigen lassen. Das senkt die Schwelle für einen Betrieb mit zwei Stunden pro Woche — es senkt sie allerdings für jeden anderen genauso, weshalb die Besetzungsfrage oben die erste ist.
