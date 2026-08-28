---
id: 0005-zettelfoto-in-stundenzeile
titel: Foto des handschriftlichen Stundenzettels wird zur importierbaren Zeile
status: kandidat
erstellt: 2026-08-28
geaendert: 2026-08-28
rolle: fit-filter

quelle: signals/pain/2026-08-28-stundenzettel-abendliche-uebertragung.md

segment: Elektro- und verwandte Bau-Handwerksbetriebe mit etwa 3 bis 20 gewerblichen Mitarbeitern, die auf der Baustelle weiterhin auf Papier notieren und die Zettel abends in Excel oder eine vorhandene Handwerkersoftware abtippen — also ausdrücklich Betriebe, die eine Erfassungs-App bereits kennen und trotzdem beim Zettel geblieben sind.
problem: Der Zettel gewinnt auf der Baustelle, weil er schneller ist als jede App; bezahlt wird das abends durch manuelles Übertragen und Kontrollieren, und dabei gehen regelmäßig Stunden und Materialpositionen verloren. Beides ist im Forum wörtlich belegt.
loesung: Der Mitarbeiter fotografiert den Zettel mit dem Telefon; der Dienst liest Datum, Mitarbeiter, Auftrag, Stunden und Materialpositionen aus und liefert eine Datei zum Import in das System, das der Betrieb ohnehin nutzt — das Papier bleibt, nur das Abtippen entfällt.
zahlungsgrund: nutzen

ablehnungsgrund: null

score:
  zwang: 2
  erreichbar: 2
  ruhe: 4
  marge: 3
  genehmigung: 5
  summe: 16
---

## Belege

- „Kleinere Notizen und Stundenzettel werden oft noch handschriftlich erfasst, da es vor Ort am schnellsten geht." — Nutzer „Mask", elektromeisterforum.de, Thread „Wie erfasst ihr Material und Stunden auf der Baustelle? Zettel, Excel, App?", abgerufen 2026-08-28, erfasst in `signals/pain/2026-08-28-stundenzettel-abendliche-uebertragung.md`
- „Am meisten nervt das manuelle Nachtragen von Kleinigkeiten und die Kontrolle, ob wirklich alles erfasst wurde. Da können schnell Stunden oder Materialpositionen vergessen werden." — derselbe Nutzer, dieselbe Quelle, abgerufen 2026-08-28
- „Der Zettel gewinnt, weil er am schnellsten ist – und der Preis wird abends bezahlt: übertragen, kontrollieren, und trotzdem die Sorge, ob nach einem stressigen Tag wirklich alles drin ist." — Nutzer „MaterialMeister", dieselbe Quelle, abgerufen 2026-08-28
- Der Markt für Handwerker-Apps ist laut Signal „sichtbar dicht" (Craftnote, openHandwerk werden genannt). Das Signal lässt ausdrücklich offen, ob das Teilproblem damit gelöst ist oder ob die Betriebe gerade wegen dieser Apps beim Zettel bleiben. — dieselbe Quelle, abgerufen 2026-08-28
- **Vermutung, ungeprueft:** Dass ein multimodales Modell handschriftliche Stundenzettel ohne betriebsspezifisches Anlernen brauchbar liest. Keine Recherche vorhanden, keine Erkennungsquote gemessen.
- **Vermutung, ungeprueft:** Betriebsgröße, Branche und Zahlungsbereitschaft der zitierten Nutzer. Das Forumsprofil gibt sie nicht her; das Segment oben ist gesetzt, nicht belegt.

## Offene Fragen

- **Besetzung, entscheidend:** Bieten Craftnote, openHandwerk, ToolTime, 1Tool oder ein anderer der vorhandenen Anbieter bereits eine Zettel-Fotoerfassung an? Der ganze Zuschnitt lebt davon, dass die vorhandenen Apps den Zettel *ersetzen* wollen und deshalb auf der Baustelle verlieren, statt ihn zu *verarbeiten*. Ist das nicht so, ist die Idee erledigt. Das ist vor allem anderen zu klären.
- Wie hoch ist die Erkennungsquote bei echter Baustellenhandschrift, verschmutztem Papier und schräg fotografierten Zetteln — und was passiert bei einem unsicheren Feld? Der Entwurf sieht vor, unsichere Felder zu markieren und dem Betrieb zur Korrektur vorzulegen, nicht zu raten. Wie viele Felder das je Zettel sind, entscheidet über die Idee.
- **G4, der Punkt, an dem die Idee vermutlich kippt:** Bringt jeder Betrieb sein eigenes Zettelformular mit? Wenn ja, ist die Feldzuordnung kundenspezifisch und der Aufwand skaliert mit der Kundenzahl — genau die Konstellation, an der Idee 0004 gestorben ist. Zu prüfen ist, ob eine formularunabhängige Erkennung („finde Datum, Name, Stundenzahl, Materialzeilen, egal wo sie stehen") ohne Zuordnung je Kunde auskommt.
- **G7:** Was kostet ein Zettel an Modell-Tokens, und was ist ein Betrieb je Monat zu zahlen bereit? Bei zehn Mitarbeitern und zwanzig Arbeitstagen sind das rund 200 Zettel im Monat. Ein Preis je Zettel im Centbereich trägt nach Steuern nichts; zu rechnen ist mit einem Monatspreis je Betrieb.
- **G6:** Ein falsch gelesener Stundenwert wandert in Lohn und Rechnung. Der Entwurf legt die Freigabe bewusst beim Betrieb — der Dienst schlägt vor, der Betrieb bucht. Hält das im Verkauf, oder will der Kunde genau die Abnahme der Kontrolle kaufen? An dieser Stelle sind bereits die Ideen 0001 und 0002 gescheitert, dort an G5.
- Über welchen Kanal erreicht man diese Betriebe ohne Kaltakquise? Denkbar sind Fachforen, Innungen und die Hersteller der Zielsysteme, denen ein Zulieferer von Importdateien nichts wegnimmt.
- Ist die Ausgabe zusätzlich als Nachweis nach dem Arbeitszeitrecht brauchbar, oder ist genau das der Punkt, an dem aus einer Abtipphilfe eine Haftungsfrage wird? Nicht recherchiert.

## Warum jetzt

Handschriftenerkennung ohne betriebsspezifisches Training ist neu. Bis vor kurzem hätte dieselbe Idee ein trainiertes OCR-Modell und ein Anlernen je Formular verlangt — also genau den kundenspezifischen Aufwand, den ein Zwei-Stunden-Betrieb nicht tragen kann. Erst multimodale Modelle lesen ein schräg fotografiertes, handbeschriebenes Blatt ohne Vorlage, und der Preis dafür liegt je Bild im Centbereich. Das ist die Änderung, und sie ist technischer, nicht regulatorischer Natur.

Ehrlich dagegen zu halten ist: Das Problem selbst ist alt, der App-Markt ist besetzt, und die Betriebe kennen die Angebote. Neu ist allein der Zuschnitt, das Papier stehen zu lassen statt es zu ersetzen. Trägt dieser Zuschnitt nicht, trägt die Idee nicht.
