---
nr: 0003
titel: Der Zustand muss textuell inspizierbar sein, nicht das Produkt textuell
datum: 2026-08-28
status: gueltig
ersetzt: 0002-agentenpruefbarkeit
ersetzt_durch: null
betrifft: [ideen, architektur, betrieb]
---

# ADR 0003 — Zustand textuell inspizierbar

## Kontext

ADR 0002 hat die Grenze an der falschen Stelle gezogen. Dort stand: Der Wert des
Produkts dürfe nicht im Aussehen liegen. Das schließt Produktklassen aus, die sehr wohl
betreibbar wären, und es trifft nicht den eigentlichen Punkt.

Der Betreiber hat korrigiert: Das Kernversprechen **darf** der visuelle Eindruck sein.
Entscheidend ist etwas anderes — ob die Logik dahinter und alle Zustände sich exakt und
übersichtlich als Text darstellen lassen.

Das Beispiel, an dem sich das entscheidet: Ein Städtebauspiel wie Cities Skylines wäre
zulässig, wenn jedes Objekt und jeder Status exakt textuell repräsentiert ist. Ein Agent
muss dann nie ein Bild ansehen, um zu beurteilen, ob die Simulation stimmt — er liest den
Zustand.

## Entscheidung

**G8 heißt jetzt: Zustand nicht textuell inspizierbar.**

Zulässig ist jedes Produkt — auch ein visuelles —, dessen vollständiger Zustand über eine
textuelle Schnittstelle abrufbar ist. Drei Ebenen müssen vorhanden sein:

1. **Übersicht** — der Gesamtzustand aggregiert, wenige Zeilen, in einem Blick erfassbar.
2. **Detail** — jedes einzelne Objekt vollständig, mit allen Eigenschaften und Beziehungen.
3. **Veränderung** — was sich zwischen zwei Zeitpunkten geändert hat, als Diff.

Ausgeschlossen ist, was diese drei Ebenen nicht liefern kann: ein Produkt, dessen Zustand
nur im Rendering existiert, dessen Datenmodell nicht auslesbar ist, oder dessen
Zustandsausgabe so umfangreich wäre, dass sie ein Agent nicht in einem Lauf erfassen kann.

**Gestaltung wird zyklisch entschieden, nicht laufend.** Der visuelle Eindruck darf das
Kernversprechen sein; er wird dann in seltenen Design-Zyklen vom Betreiber festgelegt und
gilt danach als Vorgabe. Was eine Idee benennen muss: **wie oft** eine solche Entscheidung
nötig wäre. Quartalsweise ist tragbar, wöchentlich reißt das Zeitbudget und fällt unter G4.

G9 (kein Personal) bleibt unverändert.

## Begründung

Die Trennlinie liegt zwischen **Gestaltung** und **Qualitätssicherung**, nicht zwischen
visuell und textlich.

Gestaltung fällt selten an, ist eine Entscheidung und passt in ein Gate — genau die
Betriebsform, für die diese Fabrik gebaut ist. Qualitätssicherung fällt bei jedem
Erzeugnis an, jeden Tag, und muss deshalb maschinell laufen.

Ein Agent kann eine Simulation nicht am Bildschirm beurteilen. Er kann sie beurteilen,
wenn er liest: *Bezirk 7, 412 Einwohner, Wasserversorgung 96 %, Verkehrsauslastung 1,4,
seit gestern +30 Einwohner und −8 % Wasser.* Damit findet er Fehler, prüft Balance und
entwickelt weiter — ohne je ein Bild zu sehen.

Die Anforderung ist damit keine an die Produktkategorie, sondern **an die Architektur**:
Das Datenmodell muss vom Rendering getrennt und vollständig auslesbar sein. Das ist
ohnehin gute Praxis; hier wird es zur Bedingung.

## Verworfene Alternativen

- **Die alte Fassung aus ADR 0002** — verworfen, weil sie zu grob war. Sie hätte ein
  Städtebauspiel, ein Kartenwerkzeug oder eine Visualisierungsplattform ausgeschlossen,
  obwohl alle drei mit sauber getrenntem Datenmodell betreibbar wären.
- **Visuelle Prüfung durch Modelle mit Bildverständnis als tragende Säule** — bleibt
  verworfen. Für eine Gestaltungsentscheidung im Zyklus reicht es; als tägliche
  Qualitätssicherung nicht.
- **Zustandsausgabe erst bei Bedarf nachrüsten** — verworfen. Wer sie nicht von Anfang an
  einplant, baut ein Produkt, dessen Wahrheit im Rendering steckt. Das lässt sich später
  nur durch Umbau des Datenmodells beheben.

## Folgen

- Produktklassen, die ADR 0002 ausgeschlossen hatte, sind wieder zulässig: Spiele mit
  Grafik, Karten- und Visualisierungswerkzeuge, alles Gestalterische mit sauberem
  Datenmodell.
- Jede Idee muss künftig benennen, **wie ihr Zustand als Text aussieht** — Übersicht,
  Detail, Diff. Fällt dazu nichts ein, ist sie unbrauchbar.
- Für die Konzeptionsebene entsteht eine harte Architekturvorgabe: Datenmodell und
  Darstellung getrennt, Zustandsausgabe als erstklassige Schnittstelle, nicht als
  Debug-Zugabe.
- Der Umfang wird zum Kriterium: Ein Zustand, dessen vollständige Ausgabe den Kontext
  eines Agenten sprengt, ist nicht inspizierbar. Es braucht Aggregation.
- Die beiden vorliegenden Modell-Signale bleiben zulässig, jetzt aus einem anderen Grund:
  Terminplanung und Wartungsdokumentation sind ohnehin Datenmodelle.
