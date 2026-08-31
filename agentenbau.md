# Agentenbau — was diese Fabrik bauen kann

`grenzen.md` sagt, was das Unternehmen verkaufen darf. Diese Datei sagt, was die Fabrik
**herstellen** kann. Beides fällt nicht zusammen: Es gibt tragfähige Produkte, die
niemand hier bauen könnte, weil ihre Qualität an etwas hängt, das kein Agent beurteilt.

Geschrieben am 2026-08-31 für den Suchraum Unterhaltung (ADR 0008). Die Kriterien gelten
aber für jedes Produkt — bei Software mit Zwang beantworten sie sich meist von selbst,
bei einem Spiel entscheiden sie alles.

## Die Ausgangslage, nüchtern

Die Fabrik hat keine Tester, keine Spieler, keine Community und zwei Stunden Betreuung
pro Woche. Sie hat dafür beliebig viele Agenten, die beliebig oft laufen können.

Daraus folgt eine einzige, harte Regel, aus der alles andere abgeleitet ist:

> **Was tausendmal automatisch geprüft werden kann, ist unsere Stärke.
> Was einmal von einem Menschen beurteilt werden muss, ist unsere Grenze.**

## Die sechs Fragen

**1. Kann ein Bot es spielen?** Die wichtigste Frage, und sie entscheidet fast allein.

Ein Spiel mit diskreten Aktionen, das zug- oder taktbasiert läuft, kann ein Agent über
eine Schnittstelle spielen — und damit millionenfach. Ein Spiel, das Reflexe, Zielen,
Timing oder Fingerfertigkeit verlangt, kann er nicht spielen; dann braucht das Testen
einen Menschen, und den gibt es nicht.

Alles Weitere hängt hieran: Balance, Fortschritt, Wirtschaftskreislauf und Lösbarkeit
prüft man, indem man spielt. Wer nicht spielen kann, kann nichts davon messen.

**2. Ist der Zustand die Wahrheit — oder ist es das Bild?** G8 verlangt, dass der Zustand
textuell abrufbar ist. Für den Bau ist die Anforderung schärfer: **Das Spiel muss ohne
Darstellung vollständig spielbar sein.** Die Grafik ist eine reine Sicht auf ein Modell,
das die Sicht nie etwas fragt. Sobald Wahrheit im Rendering entsteht — Kollision nach
Pixeln, Balance nach Gefühl —, ist das Produkt für diese Fabrik unzugänglich.

**3. Ist es deterministisch und reproduzierbar?** Derselbe Startwert plus dieselbe
Aktionsfolge muss dasselbe Ergebnis liefern, heute und in drei Monaten.

Das ist die härteste technische Anforderung und die am leichtesten zu übersehende. Ohne
sie gibt es keinen Regressionstest, und ohne Regressionstest kann ein Agent ein Spiel
nicht **verbessern**, sondern nur **verändern** — er sieht nie, ob eine Änderung etwas
kaputt gemacht hat. Ausgeschlossen ist damit alles mit Echtzeitphysik oder
Gleitkomma-Drift zwischen Plattformen.

**4. Ist die Qualität eine Zahl?** Ein Agent kann messen:

| messbar | wie |
|---|---|
| Balance | Gibt es eine dominante Strategie? Selbstspiel über viele Partien |
| Fortschritt | Steigt die Schwierigkeit stetig oder springt sie? |
| Wirtschaftskreislauf | Konvergiert er, läuft er weg, blockiert er? |
| Lösbarkeit | Ist das erzeugte Level lösbar, eindeutig, in wie vielen Zügen? |
| Sackgassen | Kann ein Spieler in einen unlösbaren Zustand geraten? |

Er kann **nicht** messen, ob etwas Spaß macht, schön aussieht, sich gut anfühlt oder
verständlich erklärt ist.

Daraus folgt der eigentliche Zuschnitt: **Das Genre muss eines sein, in dem der Spaß die
Balance *ist*.** In einem Optimierungsspiel ist das Vergnügen das Optimierungsproblem
selbst — wer die Balance misst, misst das Produkt. In einem Erzählspiel liegt das
Vergnügen woanders, und dann misst man am Produkt vorbei.

**5. Entsteht Inhalt aus Regeln oder aus Handarbeit?** Zweihundert handgeschriebene
Aufträge sind ein Inhaltslaufband und reißen G4. Ein Generator plus ein Prüfer, der jedes
Erzeugnis gegen Lösbarkeit und Schwierigkeit abnimmt, ist Agentenarbeit und läuft
täglich. Der Unterschied entscheidet, ob das Spiel nach dem Start weiterlebt oder
einfriert.

**6. Wie oft muss jemand über Gestaltung entscheiden?** G8 sagt: zyklisch, nicht laufend.
Quartalsweise ist tragbar, wöchentlich reißt das Zeitbudget. Ein Spiel, dessen Reiz an
laufend neuer Gestaltung hängt, ist hier nicht baubar — unabhängig davon, wie gut es wäre.

## Was danach übrig bleibt

**Geeignet:**

- **Automatisierungs- und Fabrikspiele.** Der Zustand ist ein Graph aus Maschinen und
  Stoffflüssen, die Qualität ist Durchsatz, Engpassstruktur und Takt des Technologiebaums
  — alles Zahlen. Ein Bot spielt es, Inhalt entsteht aus Rezepten und Regeln. Zugleich das
  Genre mit dem höchsten belegten Medianumsatz unter den Indie-Genres. Die stärkste
  Übereinstimmung von Baubarkeit und Markt.
- **Logistik- und Wirtschaftssimulation.** Lieferketten, Preise, Routen. Dieselben
  Eigenschaften, etwas näher an der Optimierung als am Aufbau.
- **Simulation der echten Weltwirtschaft.** Der stärkste Fall, weil als einziger die
  vierte Prüfachse offensteht: Echte Daten machen den Rückvergleich möglich. Zustand ist
  von Bauart wegen eine Zahlentabelle, Inhalt entsteht aus Datentabellen statt aus
  Handarbeit. Der wunde Punkt ist Kriterium 3 — ein Modell mit tausenden rückgekoppelten
  Größen wird leicht chaotisch, und dann trägt kein Regressionstest mehr. Ganzzahl- statt
  Gleitkommaarithmetik und begrenzte Rückkopplungen sind hier keine Feinheit, sondern
  Voraussetzung.
- **Programmier- und Optimierungspuzzle.** Lösbarkeit ist beweisbar, Schwierigkeit exakt
  messbar (Zuglänge, Befehlszahl, Durchsatz). Von allen Genres das agentenfreundlichste —
  und das mit dem kleinsten Markt. Der Zielkonflikt ist hier am schärfsten.
- **Kolonie- und Betriebssimulation**, sofern systemisch statt erzählt: Überlebt die
  Kolonie unter Regelsatz X? ist eine Zahl.

**Ungeeignet:**

- **Erzählspiele.** Die Qualität ist Prosa und Tempo, beides unmessbar.
- **Alles in Echtzeit mit Reflex, Zielen oder Timing.** Kein Bot, kein Test, kein
  Determinismus.
- **Überlebens- und Erkundungsspiele**, deren Reiz die Entdeckung ist: Der Inhalt ist
  beim ersten Kontakt verbraucht und lässt sich nicht regressiv prüfen.
- **Städtebauspiele nach Art von Cities Skylines** — und das ist der unbequeme Fall,
  weil er den Anlass dieser Fabrik bildet. Die *Simulation* darunter ist ideal für uns:
  Bezirke, Anschlüsse, Auslastung, alles Zahlen. Das *Produkt* ist es nicht. Ein
  erheblicher Teil seines Reizes besteht darin, die Stadt anzusehen — also genau in dem,
  was hier niemand beurteilen kann. Die agentenfähige Fassung ist die, in der die Zahlen
  der Punkt sind und die Ansicht eine Zugabe.

## Die ehrliche Grenze

**Ein Agent kann beweisen, dass ein Spiel nicht kaputt ist. Er kann nicht beweisen, dass
es sich zu spielen lohnt.** Zwischen „nicht kaputt" und „lohnt sich" liegt der Abstand,
an dem die meisten der über 19.000 Steam-Veröffentlichungen eines Jahres sterben.

Der Abstand lässt sich verkleinern, nicht schließen. Drei Maße sind im Selbstspiel
berechenbar und kommen dem „lohnt sich" näher als alles andere:

- **Entscheidungsdichte** — wie viele der möglichen Aktionen ändern das Ergebnis
  überhaupt? Ein Spiel, in dem neun von zehn Zügen gleichgültig sind, ist langweilig, und
  das ist ausrechenbar.
- **Strategievielfalt** — gewinnt mehr als ein Weg? Konvergiert das Selbstspiel auf genau
  eine dominante Linie, ist das Spiel gelöst und damit tot.
- **Verschiebung des Optimums** — ändert sich die beste Strategie im Verlauf? Wenn ja,
  gibt es einen Spannungsbogen; wenn nein, ist es ein Laufband.

### Die vierte Prüfachse: die Wirklichkeit als Orakel

Für eine Simulation, die **die echte Welt** modelliert, gibt es eine Prüfmöglichkeit, die
kein anderes Spielgenre hat und die stärker ist als alle drei oben: **Man lädt echte
Daten für ein Startjahr, lässt das Modell vorwärts laufen und vergleicht mit dem, was
tatsächlich passiert ist.**

Damit wird „verhält es sich plausibel" — bei einer Wirtschaftssimulation ein erheblicher
Teil des „lohnt sich zu spielen" — zu einem **automatisierten Regressionstest**. Genau
die Frage, von der oben steht, ein Agent könne sie nicht beantworten, wird hier
beantwortbar. Das ist der Grund, eine erfundene Welt *nicht* zu wählen, wo die echte
möglich ist: Eine erfundene Welt hat kein Orakel.

Zwei Bedingungen hängen daran, und beide gehören vor den ersten Entwurf geprüft:

- **Die Lizenz muss gewerbliche Weiterverbreitung erlauben.** Ein Spiel mit eingebetteten
  Daten verbreitet sie mit. In Frage kommen Weltbank, Eurostat, OECD, IWF, UN Comtrade,
  Destatis, Our World in Data — die Bedingungen unterscheiden sich erheblich, manche
  erlauben nur nichtgewerbliche Nutzung oder untersagen die Weitergabe im Bulk. **Das ist
  eine Recherchefrage, keine Annahme**, und sie entscheidet, ob das Modell überhaupt
  ausgeliefert werden darf.
- **Echte Institutionen ja, echte lebende Personen nein.** Länder, Behörden, Notenbanken
  und Politikinstrumente zu modellieren ist üblich und unproblematisch — Democracy 4 und
  Victoria 3 tun genau das. Namentlich benannte lebende Personen in Verbindung mit
  Korruptionsmechanik sind etwas anderes und gehören nicht ins Produkt.

Und die Grenze des Orakels gehört dazu, damit niemand mehr aus ihm herausliest, als
drinsteckt: Der Rückvergleich prüft die **Dynamik der Maschine** über den historischen
Zeitraum. Er sagt nichts darüber, ob das Modell auch dann plausibel bleibt, wenn der
Spieler etwas tut, das nie jemand getan hat — und das ist der eigentliche Spielinhalt.
Das Orakel deckt die Physik ab, nicht den Ast, den der Spieler betritt.

Diese drei — und im Fall einer Weltsimulation vier — sind der eigentliche Grund, warum
„agent first" hier mehr sein kann als eine Notlösung: Ein Agentenschwarm kann eine Balance millionenfach durchspielen, was kein
kleines Studio kann. **Das gehört deshalb in den Entwurf und nicht in die Nachbereitung
— ein Spiel, an dem sich diese drei Zahlen nicht berechnen lassen, verschenkt den
einzigen Vorteil, den diese Fabrik hat.**

## Was das für eine Idee heißt

Eine Unterhaltungsidee, die hier durchkommen soll, beantwortet die sechs Fragen im
Abschnitt **Belege** mit Ja — und nennt im Abschnitt **Rechnung**, wie die drei Maße
oben in diesem konkreten Spiel berechnet würden. Kann sie das nicht, ist sie
möglicherweise ein gutes Spiel, aber keines für diese Fabrik.
