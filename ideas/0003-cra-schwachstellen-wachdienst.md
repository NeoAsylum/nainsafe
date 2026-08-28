---
id: 0003-cra-schwachstellen-wachdienst
titel: Wachdienst für Fremdkomponenten in Produkten mit digitalen Elementen
status: entwurf
erstellt: 2026-08-28
geaendert: 2026-08-28
rolle: ideator

quelle: signals/regulation/2026-08-27-cyber-resilience-act-meldepflicht.md

segment: Hersteller vernetzter Geräte und Maschinen mit eigener Firmware, 20 bis 250 Mitarbeiter, Sitz in Deutschland, die ihre Produkte selbst in der EU in Verkehr bringen und keine eigene Produkt-Security-Stelle (kein PSIRT, kein eigenes CERT) haben. Konkret auffindbar über Aussteller der Hannover Messe und der SPS Nürnberg mit eigenem Typenschild.
problem: Ab dem 11. September 2026 läuft bei einer aktiv ausgenutzten Schwachstelle eine Frist von 24 Stunden bis zur Frühwarnung und 72 Stunden bis zum Hauptbericht — gerechnet ab Kenntnis. Diese Hersteller verbauen fremde Komponenten (Betriebssysteme, Bibliotheken, Funkmodule) in Produkten, die jahrelang im Feld stehen, und erfahren von einer Schwachstelle in diesen Komponenten heute zufällig oder über den Kunden. Ohne Kenntnis läuft keine Frist, aber es läuft auch keine Meldung.
loesung: Ein Dienst, der die vom Hersteller einmal hinterlegte Komponentenliste (SBOM) täglich gegen öffentliche Schwachstellenverzeichnisse abgleicht und bei einem Treffer eine datierte Benachrichtigung mit Komponente, Version, Fundstelle und Zeitstempel versendet.
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

- Ab dem 11. September 2026 müssen Hersteller von Produkten mit digitalen Elementen aktiv ausgenutzte Schwachstellen und schwerwiegende Sicherheitsvorfälle melden: Frühwarnung binnen 24 Stunden, detaillierter Bericht binnen 72 Stunden ab Kenntnis. — it-administrator.de, abgerufen 2026-08-27, erfasst in `signals/regulation/2026-08-27-cyber-resilience-act-meldepflicht.md`
- Die übrigen, umfassenderen Produktanforderungen des Cyber Resilience Act gelten erst ab dem 11. Dezember 2027. Die Meldepflicht greift also isoliert und deutlich früher, auch für Bestandsprodukte. — dieselbe Quelle, abgerufen 2026-08-27
- **Vermutung, ungeprüft:** Dass Hersteller dieser Größenklasse keine laufende Beobachtung ihrer verbauten Fremdkomponenten betreiben. Das folgt nur aus der Annahme, dass ein PSIRT erst oberhalb dieser Größe üblich ist, und ist nicht erhoben.
- **Vermutung, ungeprüft:** Dass die einschlägigen Schwachstellenverzeichnisse (NVD, CISA KEV, die europäische EUVD) maschinell, kostenfrei und mit ausreichender Aktualität abrufbar sind. Ohne diese Voraussetzung gibt es das Produkt nicht — siehe offene Fragen.
- **Vermutung, ungeprüft:** Dass diese Hersteller überhaupt eine SBOM ihrer Produkte besitzen. Besitzen sie keine, ist das Erstellen der Liste der eigentliche Aufwand und liegt beim Kunden.

## Offene Fragen

- Sind NVD, CISA KEV und die EUVD maschinell, kostenfrei und ohne Lizenzbeschränkung für einen kommerziellen Weiterverkauf der Auswertung nutzbar? Das ist die Existenzfrage der Idee und vor allem anderen zu klären.
- Welche Behörde ist in Deutschland die Meldestelle, und läuft die Meldung über die zentrale ENISA-Plattform? Das Signal lässt das offen. Die Antwort ändert die Idee nicht, entscheidet aber, ob der Dienst später einen ausfüllbaren Meldeentwurf beilegen kann.
- Wie viele deutsche Hersteller fallen in das Band 20 bis 250 Mitarbeiter mit eigenem in Verkehr gebrachten Produkt? Die Zahl entscheidet über die Marktgröße.
- Wie verhält sich der Dienst zu den kostenlosen Werkzeugen, die dasselbe Abgleichproblem für Quellcode-Abhängigkeiten lösen (Dependency-Track, Dependabot)? Das ist das größte Risiko der Idee. Die Vermutung ist, dass diese Werkzeuge auf Software-Repositories zielen und nicht auf Firmware-Stände von Geräten, die seit sechs Jahren beim Kunden stehen — geprüft ist das nicht.
- **Haftung, entscheidend:** Was passiert, wenn der Dienst einen Treffer übersieht und der Hersteller deshalb die 24-Stunden-Frist reißt? Die Meldepflicht bleibt beim Hersteller, und der Dienst ist ausdrücklich eine zusätzliche Beobachtung, keine Übernahme der Pflicht. Ob diese Abgrenzung vertraglich trägt oder ob G6 greift, ist offen und muss vor jeder weiteren Arbeit beantwortet werden.
- Zahlt dieses Segment für eine Benachrichtigung, die in den meisten Monaten leer ausfällt? Ein Wachdienst verkauft Abwesenheit von Ereignissen, und das ist ein bekannt schwieriger Verkauf.
- Ist die SBOM des Kunden ein Geschäftsgeheimnis, dessen Hinterlegung bei einem Dritten er ablehnt? Die Liste verbauter Komponenten verrät den Aufbau des Produkts.

## Warum jetzt

Der Stichtag 11. September 2026 liegt vierzehn Tage in der Zukunft, und er ist von den übrigen Pflichten des Cyber Resilience Act abgekoppelt: Die aufwendigen Produktanforderungen kommen erst am 11. Dezember 2027, die Meldepflicht gilt vorher und auch für Produkte, die längst im Feld stehen. Damit entsteht für gut fünfzehn Monate eine Lage, in der ein Hersteller melden muss, ohne dass er die dafür nötige Beobachtung schon aufgebaut hätte — vor einem Jahr gab es weder die Pflicht noch einen Anlass, die verbauten Komponenten überhaupt zu listen. Die großen Anbieter von Produkt-Security-Werkzeugen bedienen erfahrungsgemäß zuerst die Hersteller mit eigenem PSIRT, weil dort das Budget sitzt.
