---
nr: 0008
titel: Unterhaltung wird Suchraum, Simulation der Zuschnitt — die Schwelle bleibt je Idee
datum: 2026-08-31
status: gueltig
ersetzt: null
ersetzt_durch: null
betrifft: [sensorik, ideen, bewertung]
---

# ADR 0008 — Unterhaltung als Suchraum

## Kontext

Nach der Auswertung, woran die meisten Ideen scheitern, hat der Betreiber zwei neue
Richtungen vorgeschlagen:

> Wie wäre es auch mit Spielen? Die lösen nicht direkt ein Problem. Alternativ kann man
> auch viele Services für Unternehmen oder Privatpersonen bündeln.

Beide zielen auf denselben Befund: **40 von 45 roten Recherchen sind daran gestorben,
dass ein Anbieter dasselbe Problem schon löst, in 40 Fällen mit einer kostenlosen
Stufe.** 8 von 8 Prozessprofilen stehen auf `horizontal_besetzt: ja`. Wer diesem Muster
entkommen will, muss entweder aus der Problemlösung heraus (Spiele) oder die Schwelle
anders schneiden (Bündel).

## Was die Zahlen sagen

**Unterhaltung allgemein — schlechter als der Weg, an dem wir scheitern.** Steam 2025:
über 19.000 Veröffentlichungen, **Median-Bruttoumsatz 249 $ im Jahr**, 66 Prozent unter
1.000 $, 47,5 Prozent unter 100 verkauften Exemplaren, 40 Prozent verdienen nicht einmal
die 100 $ Veröffentlichungsgebühr zurück. Nur 9,9 Prozent kommen über 50.000 $.

Unsere Schwelle sind 5.000 € Marge im Monat, also rund 60.000 € im Jahr; nach Valves
30 Prozent braucht es dafür etwa 93.000 $ Bruttoumsatz. **Das liegt oberhalb des 95.
Perzentils.**

**Simulation im Besonderen — deutlich besser, aber die Zahl ist gefiltert.** Simulatoren
stellen 9,76 Prozent des Steam-Umsatzes (vierthöchstes Genre). Fabrik- und
Automatisierungsspiele haben den höchsten Medianumsatz aller Indie-Genres, 200.000 bis
über 500.000 $ — **allerdings ausdrücklich für Titel mit mindestens 100 Bewertungen.**
Das ist nach Erfolg gefiltert und sagt nichts über die Titel, die diese Schwelle nie
erreichen. Belastbarer ist das Verhältnis von Bewertungen zu Verkäufen: 60–80× bei
Simulation und Strategie gegenüber 40–50× bei Action, also **mehr Umsatz je Einheit
Sichtbarkeit**.

**Bündel — eine Bindungsstrategie, keine Akquisestrategie.** Jedes belegte Beispiel ist
ein Platzhirsch, der bestehende Kunden weiter monetarisiert: Microsoft 365, HubSpot. Für
einen Neuzugang ohne Kunden ist ein Bündel strikt schlechter als ein Einzelwerkzeug,
weil es **kein Suchwort hat** — und `erreichbar` ist der hartnäckigste Killer dieser
Fabrik, dreimal wörtlich „kein gangbarer Weg gefunden".

## Entscheidung

**Erstens: Unterhaltung wird Suchraum, mit `zahlungsgrund: wunsch` als dritter
Kategorie.** Sie fehlte bisher; der Ideator konnte das Feld für ein Spiel gar nicht
ausfüllen. Sie ist die schwächste Kategorie und kostet die gesamte `zwang`-Dimension:
null von fünf Punkten, damit höchstens 20 statt 25 bei unveränderter Schwelle 15. Eine
Unterhaltungsidee muss in den übrigen vier Dimensionen nahezu voll punkten.

**Zweitens: Der Zuschnitt ist Simulation und Automation, nicht „Spiele".** Drei Segmente
stehen auf der Liste: Aufbau- und Wirtschaftssimulationen mit auslesbarem Zustand,
Automatisierungs- und Fabrikspiele, Management- und Betriebssimulationen.

Der Grund ist nicht der Umsatz, sondern die **Prüfbarkeit**. Bei Simulation *ist* der
Zustand eine Zahlentabelle — G8 ist von Bauart wegen erfüllt, und Balance,
Wirtschaftskreislauf, Verlauf und Lösbarkeit sind messbar. „Macht Spaß" ist es nicht.
Das ist der einzige Genrezuschnitt, in dem diese Fabrik ihr eigenes Produkt beurteilen
kann, und es ist genau der Fall, für den G8 ursprünglich geschrieben wurde.

**Drittens: G7 bleibt bei 5.000 € je Idee.** Der Betreiber hat die Portfolio-Fassung
ausdrücklich abgelehnt. Ein Spiel muss allein tragen.

Für Unterhaltung heißt das etwas anderes als für ein Abo: Ein Spiel wird **einmal**
gekauft. 5.000 € im Monat sind dort nicht 900 zahlende Kunden, sondern **dauerhaft 900
Verkäufe im Monat** — oder ein wiederkehrendes Modell (Erweiterungen, Saison, Betrieb
als Dienst). Der Plattformanteil von 30 Prozent gehört in die Rechnung.

## Was abgelehnt wurde, und was das kostet

Die **Portfolio-Fassung** — G7 gilt für die Summe, ein einzelnes Werkzeug muss nur
250–500 € tragen — wurde erwogen und verworfen. Sie hätte die Grenze getroffen, an der
die meisten Ideen sterben: Vier von fünfzehn starben an G7, und Idee 0011 scheiterte
daran, dass 40 € × 50 Kunden bei 72 auffindbaren Betrieben 70 Prozent Marktanteil
bedeutet hätten — bei 15 Kunden wären es 20 Prozent gewesen.

Der Preis der Ablehnung ist benannt und bleibt gültig: **Die Klasse kleiner, unbesetzter
Nischen bleibt ausgeschlossen**, und das sind die meisten unbesetzten Märkte, die diese
Fabrik gefunden hat. Der Grund dagegen ist ebenso gültig: Zwanzig kleine Erfolge sind
nicht offensichtlich leichter als ein mittlerer — es wären zwanzig Kanäle, zwanzig
Rechtstexte, zwanzig Supportpostfächer und zwanzig Gratiskonkurrenten, und zwei Stunden
pro Woche müssten die Ausnahmen aus zwanzig Produkten abdecken.

Das **Bündel als ein Abo** wird nicht weiterverfolgt: Es ist eine Strategie für
Bestandskunden und verschlechtert genau die Dimension, an der hier am häufigsten
gestorben wird.

## Was ausdrücklich nicht gelockert wird

Für Unterhaltung gilt **keine** Sonderregel. Nicht bei G7, nicht bei der Punktschwelle,
nicht bei den drei Einzelsperren. Ein Spiel, das die 5.000 € nicht vorrechnen kann, wird
abgelehnt wie jede andere Idee. Der Median von 249 $ ist der Grund, diese Härte zu
behalten, nicht sie aufzuweichen.

Zwei Grenzen sind bei Unterhaltung besonders zu prüfen, weil sie leicht übersehen werden:

- **G4 und G3 über die Sichtbarkeit.** Steam-Sichtbarkeit hängt an Wunschlisten vor dem
  Start, und die entstehen durch Community-Arbeit. Wie viel davon menschliche Zeit ist,
  entscheidet die Idee — nicht das Spiel selbst.
- **G4 über die Inhalte.** Ein Genre, das laufend neue Inhalte verlangt, reißt die zwei
  Stunden, es sei denn, die Inhalte entstehen aus Regeln statt aus Handarbeit. Das ist
  bei Simulation der Normalfall und bei Erzählspielen nie.

## Quellen

- Gamalytic/GameDiscoverCo zu Steam 2025: <https://gamedevreports.substack.com/p/gamalytic-67-of-games-on-steam-earned>
- Indie-Umsatzverteilung, Median und Spitzenperzentile: <https://www.steampageanalyzer.com/blog/indie-game-revenue-data>
- Umsatzverteilung nach Genre: <https://games.gg/news/steam-revenue-distribution-by-genre/>
- Anteil Action/RPG am Steam-Umsatz: <https://gameworldobserver.com/2025/07/01/analytics-three-quarters-of-game-revenue-on-steam-comes-from-action-and-rpgs>
- Bündelstrategien: <https://www.getmonetizely.com/articles/what-is-subscription-stacking-the-ultimate-guide-to-saas-bundle-strategies>

Alle abgerufen am 2026-08-31. Diese Zahlen sind der Ausgangspunkt, nicht das Ergebnis —
die drei Marktprofile erheben sie mit eigenen Belegen neu.
