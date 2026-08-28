---
id: 0008-m365-lizenzabgleich-vor-verlaengerung
titel: Lizenzabgleich für Microsoft 365 vor der nächsten Vertragsverlängerung
status: entwurf
erstellt: 2026-08-28
geaendert: 2026-08-28
rolle: ideator

quelle: signals/market/2026-08-28-microsoft-365-preiserhoehung-juli-2026.md

segment: Betriebe mit etwa 25 bis 250 Microsoft-365-Arbeitsplätzen ohne eigene Lizenzverwaltung, bei denen die Lizenzen nebenbei von der Geschäftsführung oder einer IT-Teilzeitkraft verwaltet werden — Handwerk, Handel, Produktion, Ingenieur- und Planungsbüros. Betriebe aus Versicherung, Bausparen und Finanzdienstleistung gehören ausdrücklich nicht zum Segment.
problem: Zum 1. Juli 2026 sind die Listenpreise der Microsoft-365-Geschäftstarife gestiegen, Business Basic um rund 17 Prozent, Business Standard um rund 12 Prozent. Bestandskunden zahlen bis zur nächsten Vertragsverlängerung den alten Preis — die Erhöhung schlägt also gestaffelt und für jeden Betrieb an einem anderen Tag durch. Wer nicht weiß, welche seiner Lizenzen ungenutzt oder überdimensioniert sind, verlängert die alte Menge zum neuen Preis.
loesung: Ein Bericht, der die vorhandenen Lizenzen den tatsächlichen Nutzungsdaten des Mandanten gegenüberstellt und ungenutzte Konten sowie Herabstufungskandidaten mit dem Eurobetrag je Jahr benennt — der Betrieb entscheidet und bucht selbst, der Dienst greift nur lesend zu.
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

- „The following list price changes will go into effect on July 1, 2026." — Microsoft-365-Blog, „Advancing Microsoft 365: New capabilities and pricing update", 2025-12-04, abgerufen 2026-08-28, erfasst in `signals/market/2026-08-28-microsoft-365-preiserhoehung-juli-2026.md`
- Business Basic steigt laut Sekundärquelle um ca. 16,7 Prozent (6,00 auf 7,00 EUR), Business Standard um ca. 12 Prozent (12,50 auf 14,00 EUR), Frontline-Tarife um bis zu 43 Prozent; Business Premium bleibt zunächst bei 22 EUR. — mt-computerservice.de, KMU-Guide, wiedergegeben im Signal, abgerufen 2026-08-28. **Einschränkung:** Die Prozentsätze liegen im Originalbeitrag nur als Bildgrafik vor und sind nicht aus der Primärquelle bestätigt.
- „Bestandskunden bleiben laut Microsoft bis zur Vertragsverlaengerung auf dem alten Preis." — dasselbe Signal, abgerufen 2026-08-28. Das ist der eigentliche Kaufanlass: ein Termin je Kunde, verteilt über zwölf Monate.
- Das Signal stellt fest, dass sich kein dritter Anbieter als Umsteige-Nachfolger positioniert und die Reaktion stattdessen Zusatzwerkzeuge betrifft, ausdrücklich einschließlich Lizenzmanagement. — dasselbe Signal, abgerufen 2026-08-28
- **Vermutung, ungeprueft:** Dass in Betrieben dieser Größe nennenswert viele ungenutzte oder zu hoch lizenzierte Konten liegen (ausgeschiedene Mitarbeiter, Aushilfen mit Vollausstattung, doppelte Konten). Plausibel, aber in diesem Repo durch nichts belegt.
- **Vermutung, ungeprueft:** Dass die Nutzungsberichte von Microsoft die dafür nötige Aussagekraft haben und lesend ohne weitreichende Rechte abrufbar sind.

## Offene Fragen

- **Besetzung, entscheidend:** Lizenzoptimierung für Microsoft 365 ist ein bekanntes Feld mit internationalen Anbietern und mit Werkzeugen, die Systemhäuser ihren Kunden ohnehin mitliefern. Wie viele Anbieter bedienen genau die Größenklasse 25 bis 250 Plätze, zu welchem Preis, und gibt es bereits einen „Vergleich 2026"? Dieser Sättigungsindikator hat in `research/` bisher jedes Mal angeschlagen. Erste und wichtigste Frage.
- **Liefert Microsoft es selbst?** Das Muster aus den bisherigen Recherchen lautet: Wo die zuständige Stelle das Werkzeug kostenlos beistellt, bleibt nur der Komfortaufschlag. Das Microsoft-365-Administrationszentrum enthält bereits Nutzungsberichte und Empfehlungen. Zu klären ist, was davon ein Betrieb ohne IT-Abteilung tatsächlich vorfindet und ob der Unterschied „Zahlen vorhanden" zu „Eurobetrag benannt" den Preis trägt.
- **G2, ausdrücklich zu prüfen und nicht zu überspringen:** Beruht diese Idee auf Kenntnissen, die es nur im Hauptjob gibt? Der Ideator hält sie für allgemein zugänglich — die Preisänderung ist öffentlich angekündigt, die Schnittstelle ist dokumentiert, und jeder mit IT-Ausbildung käme darauf. Weil G2 aber die Grenze ist, deren Verletzung harmlos aussieht, gehört diese Frage vor allen Wirtschaftlichkeitsfragen beantwortet.
- **G4:** Jeder neue Kunde muss einmal eine lesende Freigabe für seinen Mandanten erteilen. Läuft das als Selbstbedienung durch, oder braucht jeder Betrieb eine Begleitung dabei — und was passiert, wenn eine Freigabe abläuft oder Microsoft die Schnittstelle ändert? Skaliert die Einrichtung mit der Kundenzahl, greift G4.
- **G6:** Eine Herabstufung, die eine tatsächlich genutzte Funktion entfernt, stört den Betrieb des Kunden. Der Entwurf hält deshalb Entscheidung und Ausführung beim Kunden und gibt nur einen Bericht aus. Ob das im Verkauf durchzuhalten ist oder der Kunde die Umsetzung mitkaufen will, ist offen — im zweiten Fall entstünde synchrone Arbeit an fremden Systemen und die Idee kippt an G3.
- **Datenschutz:** Nutzungsdaten je Konto sind personenbezogene Daten der Beschäftigten des Kunden. Zu klären ist, ob eine Auswertung ohne Personenbezug (nur Lizenz, Aktivität ja/nein, keine Inhalte) ausreicht und was an Auftragsverarbeitung nötig wird.
- **G7:** Was ist ein Betrieb mit 60 Plätzen für einen jährlichen Bericht zu zahlen bereit, wenn er damit vier ungenutzte Lizenzen findet? Vier Business-Standard-Lizenzen sind rund 670 Euro im Jahr. Der Preis muss deutlich darunter liegen und trotzdem nach Steuern tragen — und die Ersparnis ist einmalig, während der Preis wiederkehren soll. Das ist die härteste Rechnung dieser Idee.
- Erreichbarkeit ohne Kaltakquise ist ungeklärt. Der naheliegende Kanal wären IT-Systemhäuser als Partner — die aber genau dieses Ergebnis lieber selbst verkaufen.

## Warum jetzt

Der Anlass hat ein Datum und eine Mechanik. Vor einem Jahr gab es keinen Grund, die Lizenzmenge anzufassen: Der Preis war seit Jahren stabil, und eine ungenutzte Lizenz kostete wenig genug, um sie zu ignorieren. Seit dem 1. Juli 2026 steigt sie im zweistelligen Prozentbereich, und weil Bestandskunden erst zur Verlängerung umgestellt werden, entsteht der Anlass nicht einmalig, sondern über die kommenden zwölf Monate verteilt bei jedem Betrieb an seinem eigenen Vertragstermin. Ein Werkzeug, das genau dort einen Eurobetrag liefert, trifft ein Fenster, das es 2025 nicht gab und das 2028 wieder zu ist.

Ehrlich dagegen: Lizenzoptimierung ist ein alter Gedanke, und wenn sich zeigt, dass sie in dieser Größenklasse längst mitgeliefert wird, ist das neue Fenster nur ein neuer Anlass für ein besetztes Angebot.
