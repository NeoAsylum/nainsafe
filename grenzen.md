# Grenzen

Sieben Ausschlusskriterien. Der Fit-Filter prüft jede Idee gegen alle sieben.
**Ein einziger Treffer bedeutet `abgelehnt`** — es gibt keine Abwägung, keine Ausnahme
und keine Idee, die gut genug wäre, um eine dieser Grenzen wert zu sein.

Jede Ablehnung wird im Frontmatter der Idee begründet (`ablehnungsgrund`), damit dieselbe
Idee nicht in sechs Wochen erneut auftaucht.

---

## G1 — Wettbewerb zum Arbeitgeber

Ausgeschlossen ist alles, was in den Markt des Arbeitgebers fällt: Versicherung,
Bausparen, Finanzdienstleistung — samt der IT, die diese Branchen bedient.

Das gilt auch für scheinbar neutrale Werkzeuge, wenn die Zielgruppe überwiegend aus
diesen Branchen kommt. Ein Dokumentenwerkzeug für Versicherungsmakler ist ein
Versicherungsprodukt.

## G2 — Wissen aus dem Hauptjob

Ausgeschlossen ist alles, was auf Kenntnissen beruht, die nur der Hauptjob verschafft:
interne Störungsmuster, Lieferantenbeziehungen, Prozesswissen, Werkzeugbewertungen,
Kontakte.

Das ist die gefährlichste Grenze, weil ihre Verletzung harmlos aussieht. Prüffrage:
*Käme ein Außenstehender mit derselben Ausbildung, aber ohne diesen Arbeitsplatz auf
diese Idee — und könnte er sie umsetzen?* Nein heißt abgelehnt.

## G3 — Synchrone Kundenkommunikation

Ausgeschlossen ist alles, was Telefonate, Termine, Workshops, Vor-Ort-Einsätze oder
zugesagte Reaktionszeiten unter 24 Stunden erfordert.

Ein Agent kann kein Gespräch führen. Jede Idee, deren Wertversprechen an einem Menschen
zur Verfügung hängt, verletzt das Zeitbudget — unabhängig davon, wie gut sie sonst ist.
Das schließt Beratung, Agenturleistung und Individualentwicklung praktisch vollständig aus.

## G4 — Betriebsaufwand über zwei Stunden pro Woche

Ausgeschlossen ist alles, dessen laufender Betrieb im eingeschwungenen Zustand mehr als
zwei Stunden pro Woche kostet. Manuelle Freigaben, händische Datenpflege, wachsender
Supportaufwand pro Kunde.

Prüffrage: *Was passiert bei 100 Kunden statt 10?* Skaliert der Aufwand mit der Kundenzahl,
ist es abgelehnt.

## G5 — Erlaubnispflicht

Ausgeschlossen ist alles, was eine berufsrechtliche Erlaubnis erfordert oder in deren
Nähe gerät: Rechtsdienstleistung (RDG), Steuerberatung (StBerG), Finanz- und
Versicherungsvermittlung, Heilkunde, Arbeitsvermittlung, Inkasso.

Die Grenze verläuft früher als vermutet: Ein Werkzeug, das eine rechtliche Bewertung
*ausgibt*, kann bereits Rechtsdienstleistung sein — auch wenn ein Modell sie erzeugt hat.
Werkzeuge, die Informationen aufbereiten und die Bewertung dem Nutzer überlassen, sind
in Ordnung.

## G6 — Unbegrenzte oder unversicherbare Haftung

Ausgeschlossen ist alles, wo ein Fehler des Systems einen Schaden verursacht, der die
Einnahmen um Größenordnungen übersteigt: Fristberechnung, Finanztransaktionen,
Sicherheitsfreigaben, Medizin, alles mit Personenschaden.

Faustregel: Wenn eine Berufshaftpflicht für diese Tätigkeit nötig oder teuer wäre,
ist die Idee zu groß für ein Nebengewerbe.

## G7 — Marge trägt die Kosten nicht

Ausgeschlossen ist alles, dessen Deckungsbeitrag die variablen Kosten — vor allem
API-Tokens — nicht deutlich übersteigt, oder erst bei unrealistischer Stückzahl.

Gerechnet wird **nach Steuern**: Der Gewinn stapelt sich auf das Hauptgehalt und wird mit
dem Grenzsteuersatz belastet. Aus 1.000 € Gewinn werden grob 560 €. Eine Idee, die
brutto knapp trägt, trägt netto nicht.

## G8 — Zustand nicht textuell inspizierbar

Das Unternehmen stellt niemanden ein: keinen Redakteur, keinen Tester, keinen Designer.
Wer die Arbeit macht, prüft sie auch — und das sind Agenten.

**Das Kernversprechen darf trotzdem der visuelle Eindruck sein.** Die Grenze verläuft
nicht zwischen visuell und textlich, sondern dazwischen, ob der **Zustand** des Systems
exakt und übersichtlich als Text abrufbar ist. Ein Agent muss die Simulation lesen
können, nicht ansehen.

Drei Ebenen müssen vorhanden sein — fehlt eine, ist die Idee ausgeschlossen:

| Ebene | Was sie liefert | Beispiel Städtebauspiel |
|---|---|---|
| **Übersicht** | Gesamtzustand aggregiert, in einem Blick erfassbar | 14 Bezirke, 8.200 Einwohner, Wasser 91 %, Verkehr 1,4 |
| **Detail** | ein Objekt vollständig, mit allen Eigenschaften | Bezirk 7: Lage, Gebäude, Bewohner, Anschlüsse, Auslastung |
| **Veränderung** | Diff zwischen zwei Zeitpunkten | seit gestern +30 Einwohner, −8 % Wasser, 2 Gebäude neu |

Ausgeschlossen ist damit, was seinen Zustand **nur im Rendering** hat: ein Produkt ohne
auslesbares Datenmodell, eines dessen Wahrheit im Bild entsteht, oder eines dessen
vollständige Zustandsausgabe so groß wäre, dass ein Agent sie nicht in einem Lauf
erfassen kann. Das Letzte ist eine Frage der Aggregation, nicht der Größe des Systems.

**Gestaltung wird zyklisch entschieden, nicht laufend.** Wie etwas aussieht, legt der
Betreiber in seltenen Design-Zyklen fest; danach gilt es als Vorgabe. Jede Idee muss
benennen, **wie oft** so eine Entscheidung nötig wäre: quartalsweise ist tragbar,
wöchentlich reißt das Zeitbudget und fällt schon unter G4.

Prüffragen, alle drei müssen mit Ja beantwortbar sein:

1. **Kann ein Agent aus der Textausgabe erkennen, ob das System richtig arbeitet?**
   Nicht „ob es lief" — ob das Ergebnis *stimmt*.
2. **Ließe sich ein Fehler aus Zustand, Logs und Daten diagnostizieren**, ohne dass
   jemand auf einen Bildschirm schaut?
3. **Kann ein Agent eine Änderung bauen und ihre Wirkung am Zustand nachweisen** — vorher
   gegen nachher, ohne menschliche Sichtprüfung?

Für die Konzeption folgt daraus eine harte Vorgabe: **Datenmodell und Darstellung
getrennt, Zustandsausgabe als erstklassige Schnittstelle.** Nicht als Debug-Zugabe,
sondern als das, worüber die Fabrik ihr eigenes Produkt überhaupt kennt.

Ein Spiel ist zulässig, wenn es über Text, Zahlen oder Zustände gespielt wird — dann
sind Balance und Verlauf messbar. Es ist ausgeschlossen, wenn sein Reiz an Grafik,
Animation oder Bedienungsgefühl hängt.

## G9 — Braucht Personal

Ausgeschlossen ist alles, was ohne angestellte oder beauftragte Menschen nicht läuft:
Redaktion, Support-Schicht, Vertriebsteam, Handwerker vor Ort, Übersetzer, Moderatoren.
Auch Freelancer und Agenturen zählen dazu — der Betreiber will keine Personalführung,
und Personalführung fängt beim ersten Auftrag an.

**Was ausdrücklich erlaubt ist:** eine Plattform, auf der *andere* Menschen einander
beauftragen. Der Betreiber stellt dann niemanden ein; er stellt den Marktplatz. Solange
Vermittlung, Abwicklung und Streitfälle maschinell laufen, ist das keine Verletzung —
sondern eine der wenigen Formen, in denen menschliche Arbeit im Modell vorkommen darf.

---

## Bewertung der Überlebenden

Ideen, die alle neun Grenzen passieren, werden in fünf Dimensionen bewertet (je 0–5):

| Dimension | Frage |
|---|---|
| `zwang` | Muss der Kunde, oder wäre es nur nett? Pflicht schlägt Nutzen. |
| `erreichbar` | Kommt man ohne Kaltakquise an die Zielgruppe? |
| `ruhe` | Läuft es zwei Wochen ohne jeden Eingriff? |
| `marge` | Trägt der Preis die Kosten nach Steuern deutlich? |
| `genehmigung` | Würde der Arbeitgeber das ohne Rückfrage genehmigen? |

Maximal 25 Punkte. Unter 15 wird nicht zur Vorlage. Bei `genehmigung` unter 3 wird
unabhängig von der Gesamtpunktzahl nicht weitergearbeitet.
