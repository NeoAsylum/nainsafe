---
id: 0017-reihenliste-maschinenlesbar
rolle: datenbauer
status: gebaut
haengt_an: [0006-deckung-pruefjahrgang-1997, 0014-lizenzpruefung-restliche-reihen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
abnahme: Die sechs Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Die Reihenliste, maschinenlesbar — die Eingabetabelle des Jahrgangsbaus

Vorgaben: `technik.md` T23 Punkt 2 und 8, T37, T25, T26, T24, T40, die Reihenliste in
Abschnitt 7 („Die Reihenliste, die `spiel.md` vom Architekten verlangt"); dazu `daten.md`
für die Quellen.

**Was du baust, ist eine Datei, keine Prosa.** Die Reihenliste steht heute an drei Orten
in Fließtext — als Tabelle in `technik.md`, als Deckungsbefund in
`daten/deckungsbefund-1997.md` (Paket 0006) und als zwei Lizenzbefunde in
`daten/lizenzbefund-wdi.md` und `daten/lizenzbefund-reihen.md` (Pakete 0005 und 0014).
`werkzeuge/aufbereitung` liest sie nach T23 und kann Fließtext nicht lesen. Solange sie
dreimal in Prosa steht, laufen die drei Fassungen auseinander, und der Fehler fällt beim
Jahrgangsbau auf — also spät.

## Warum jetzt und nicht früher

Weil die drei Befunde jetzt vorliegen und vorher nicht. Eine Reihenliste, die vor 0005,
0006 und 0014 entsteht, schreibt die Spalte „Verdacht" fort — und der Prüfbefund zu 0005
hat gezeigt, dass „Verdacht" keine Messung ist, sondern eine Vermutung, die dreimal
falsch war. **Du überträgst gemessene Urteile, keine Vermutungen.** Steht in einer der
Quelldateien noch ein Verdacht ohne Urteil, überträgst du ihn als `unklar` und schreibst
daneben, welche Frage offen ist.

`haengt_an` nennt 0006 und 0014, weil beide Befunde in Feldern dieser Datei landen. 0005
ist `fertig` und liegt vor.

## Was hineingehört

Je Reihe der Reihenliste — **die Nummern 1 bis 19, alle**, auch die vier ohne
Datenanker — ein Eintrag mit:

1. **Nummer und Bezeichnung**, wörtlich aus der Tabelle in Abschnitt 7.
2. **Indikatorcode oder Quellkennung** und die Quelle nach `daten.md`. Wo die Tabelle
   zwei Quellen nennt („WDI / PWT", „IWF IFS / WDI"), steht hin, **welche eingebettet
   wird** und welche die Rückfallquelle ist — der Deckungsbefund hat das für Reihe 9, 10
   und 11 gemessen; für die übrigen steht die Entscheidung aus, und dann trägst du beide
   ein und markierst die Wahl als offen.
3. **Dimension und Modelleinheit**, wörtlich aus der Tabelle. Die Spalte „Dimension" ist
   zu lesen, wie sie dasteht: Zeile 8 trägt **4**, nicht 4 + RW; die Zeilen 9, 11 und 12
   tragen 4, Zeile 10 trägt 3. An dieser Lesart hängt T46.
4. **Der Umrechnungsfaktor in die Modelleinheit**, je Reihe ausgeschrieben. Ein stiller
   Faktor ist der Fehlertyp, der ein Modell plausibel aussehen lässt und trotzdem falsch
   macht. Wo keine Umrechnung nötig ist, steht `1` und nicht nichts.

   **Die zweite Runde des Prüfbefunds zu 0006 hat vier Reihen benannt, und zwei davon sind
   die, die niemand mehr aufmacht.** Reihe 9 und Reihe 11 verlangen `bp`, ihre Quellen
   liefern Prozent — je Faktor 100; die stehen inzwischen im Deckungsbefund. Reihe 2 und
   Reihe 10 stehen dort **nicht**, und der Prüfer hat seine eigene Runde-1-Aussage dazu
   ausdrücklich zurückgenommen:

   - **Reihe 2** ist der grössere Posten, 12 der 31 Sollreihen. Quelleneinheit ist
     „% of GDP" — am 2026-09-02 an
     `api.worldbank.org/v2/indicator/NV.AGR.TOTL.ZS?format=json` nachgemessen, `sourceNote`
     wörtlich: „This indicator is expressed as a percentage of Gross Domestic Product
     (GDP)". Modelleinheit ist Zehntausendstel, also Faktor **100** — und dazu ein zweiter
     Schritt, den kein Faktor abdeckt: **auf 10.000 normiert**. Die drei WDI-Anteile
     summieren sich nicht auf 100 (der Rest sind Nettogütersteuern), die Normierung ist
     also kein Rundungsdetail, sondern verschiebt jeden der zwölf Werte. `technik.md`
     Z. 698 rechnet danach
     `wertschoepfung[g][s] = mal_geteilt(bip_start[g], sektoranteil[g][s], 10.000)` und
     setzt die Normierung voraus.
   - **Reihe 10** stand nie da. Was der Deckungsbefund zu Reihe 10 schreibt, ist der
     Einheiten*bruch* DEM→EUR 1999 und die Verkettung mit 1,95583 — eine andere Frage. Die
     Modelleinheit ist ein Index mit Basis 10.000: `technik.md` Z. 884 setzt
     `land.US.wechselkurs` fest auf **10.000** als Numéraire, Z. 886 dasselbe für
     `restwelt.wechselkurs`, Z. 1377 macht `wechselkurs[g] ≥ 1` zur Invariante. Aus
     1,73405583 DEM/USD wird also **17.341**, nicht 1,73 — ein Faktor 10.000.

   **Die Reihenfolge von Rundung und Normierung entscheidest du nicht.** Ob bei Reihe 2 vor
   oder nach der Normierung gerundet wird, ist eine Entwurfsfrage mit Folgen für den
   Determinismus; sie steht in `rueckstand.md` als Punkt an den Geschäftsführer. Trag den
   Faktor 100 und die Normierung als **zwei getrennte Schritte** ein und markier die
   Rundungsstelle als offen — genau so, wie du es bei jeder anderen offenen Frage tust.
5. **Die Rolle** — `start`, `soll`, `politikpfad`, `exogen`, `konstante`, `endogen` — und
   für die 31 Sollreihen die **Klassifikation nach T37**: `frei` (23, dazu der
   Handelsblock), `gesetzt` (Leitzins, 4), `abgeleitet` (Staatsschuldenquote, 4). T23
   Punkt 2 verlangt sie ausdrücklich je Reihe.
6. **`exogen_ab` und `verkettet_ab`** als Jahreszahl (T23 Punkt 8), auch wo sie leer
   sind. Zwei stehen fest und sind zu übernehmen: Der Leitzins für Deutschland trägt
   `exogen_ab = 1999` (Euroraum), die Wechselkursreihe `verkettet_ab = 1999` (mit dem
   unwiderruflichen Umrechnungskurs). Die Umrechnung in eine Runde nach T40 gehört **nicht**
   in diese Datei — sie hängt am Jahrgang, und R ist eine Größe des Jahrgangs.
7. **Das Lizenzurteil** aus 0005 und 0014 — `frei` | `gesperrt` | `unklar` —, dazu das
   wörtliche Feld „Source", die Abruf-URL und das Abrufdatum, aus denen es stammt. Bei
   jedem Urteil ausser `frei` die Folge nach T26.
8. **Die Deckung im Prüfjahrgang** aus 0006: erstes und letztes verfügbares Jahr je Land
   und die Zahl der Stützstellen. Reissende Reihen tragen das Urteil, das der Befund für
   sie ausweist; **du füllst nichts** (T24) und entscheidest nichts.

## Was du nicht tust

- **Du entscheidest keine Reihe ab und wählst kein Fenster.** Die beiden Auswege aus T24
  — Reihe streichen oder Fenster kürzen — stehen dem Spielentwerfer zu. Deine Datei
  bildet den gemessenen Stand ab, samt der zwei Reihen ohne jede Deckung.
- **Du lädst nichts herunter und bettest keine Datenzeile ein.** Diese Datei beschreibt
  Reihen, sie enthält keine Werte.
- **Du misst nicht nach.** Die Messung ist in 0005, 0006 und 0014 gelaufen und geprüft.
  Findest du einen Widerspruch zwischen zwei Quelldateien, überträgst du ihn **als
  Widerspruch** und meldest ihn in deinem Logbuch — du löst ihn nicht auf. Ein
  Zusammenzug, der zwei Aussagen glättet, ist genau der Fehler, an dem 0006 zurückging.
- **Du rührst den Code nicht an.** Das Einlesen dieser Datei baut der Jahrgangsbau.

## Abnahme

1. **Alle 19 Reihen stehen in der Datei**, mit Nummer und Bezeichnung wörtlich aus der
   Tabelle in Abschnitt 7. Der Prüfer legt die Tabelle daneben und zählt ab. `NV.IND.MANF.ZS`
   kommt nicht vor — `spiel.md` verwendet es nicht.
2. **Die 31 Sollreihen tragen ihre T37-Klasse**, und die Zählung geht auf: `frei` 23
   (Zeilen 1, 2, 8, 10 mit 4 + 12 + 4 + 3), `gesetzt` 4 (Reihe 9), `abgeleitet` 4
   (Reihe 11), Summe 31; der Handelsblock steht als eigener Block mit 40 Strömen und der
   Klasse `frei`. Eine Sollreihe ohne Klasse und eine Nicht-Sollreihe mit Klasse sind
   beides Befunde.
3. **Jede Reihe trägt einen Umrechnungsfaktor**, auch wenn er 1 ist. Vier Reihen sind
   namentlich zu prüfen, weil für sie gemessen ist, was dort stehen muss:
   - **Reihe 9** und **Reihe 11**: `100`, Begründung „Quelle in Prozent, Modelleinheit bp".
   - **Reihe 2**: `100` **und** ein zweiter, getrennt ausgewiesener Schritt „auf 10.000
     normiert", mit der Angabe, dass die Rundungsstelle offen ist. Ein Eintrag, der nur
     `100` führt, ist ein Befund — die drei Anteile summieren sich nicht auf 100, und die
     Normierung verschiebt jeden der zwölf Werte.
   - **Reihe 10**: `10.000`, Begründung „Numéraire-Index, `land.US.wechselkurs` fest auf
     10.000" (`technik.md` Z. 884). Ein Eintrag mit `1` ist ein Befund.

   Der Prüfer legt `technik.md` Abschnitt 7 Spalte „Modelleinheit" neben die Datei und
   vergleicht je Reihe; für die vier genannten gegen die Zahlen oben.
4. **`exogen_ab` und `verkettet_ab` stehen bei jeder Reihe als Feld**, leer oder mit
   Jahreszahl; der deutsche Leitzins trägt 1999, die Wechselkursreihe trägt 1999. Keine
   Rundenzahl in dieser Datei.
5. **Jedes Lizenzurteil ist auf eine der drei Befunddateien zurückführbar**, mit Feld
   „Source", URL und Abrufdatum. Der Prüfer greift zwei Urteile heraus und prüft sie gegen
   die Quelldatei; weicht eines ab, ist das ein Befund. Kein Urteil ohne Beleg, keine
   Reihe ohne Urteil.
6. **Die Datei ist gültiges TOML**, ohne Dezimalpunkt in einem Zahlenwert (T4) und ohne
   doppelten Schlüssel. Die Form ist deine Entscheidung — `specs/` schreibt für diese
   Datei kein Format vor, T23 verlangt nur, dass der Jahrgangsbau sie liest, und
   `parameter.toml` aus Paket 0009 setzt TOML im selben Vorhaben bereits voraus.

## Was ausdrücklich kein Befund ist

- **Die Gliederung der Datei** — ein Tabellenfeld je Reihe oder eine Tabelle je Quelle:
  `specs/` schweigt dazu, also ist die Entscheidung des Bauagenten gültig, solange die
  sechs Bedingungen halten.
- **Dass die Datei Reihen führt, die keine Sollreihe sind.** T23 Punkt 2 verlangt die
  Sollreihen; die übrigen stehen hier, weil der Jahrgangsbau auch Startwerte, Politikpfade
  und exogene Pfade zieht (T23 Punkt 1, 3, 4) und dieselbe Tabelle braucht.

## Rückläufe

0.
