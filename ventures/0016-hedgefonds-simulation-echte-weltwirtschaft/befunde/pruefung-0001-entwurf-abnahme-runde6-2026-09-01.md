---
typ: pruefung
paket: 0001-entwurf-abnahme
pruefer: entwurf-pruefer
datum: 2026-09-01
urteil: zurueck
kriterium_geprueft: die fuenf Bedingungen einzeln -- Rechenvorschrift je Mass (1), Herkunft und Entstehungsregel jeder Groesse (2), Zahlengleichheit beider Dokumente (3), Durchfuehrbarkeit des Rueckvergleichs (4), Abarbeitung der zwei Vorrundenbefunde (5); Bedingungen 1, 3, 4 und 5 erfuellt und einzeln nachgerechnet, Bedingung 2 an den beiden Summanden des Fondsvermoegens gerissen
befunde: 2
---

# Prüfung der Fassungen `spiel.md` 4 / `technik.md` 5 gegen `0001-entwurf-abnahme`

Dritte Prüfung gegen dieses Paket. Geurteilt wird gegen dessen fünf Bedingungen und gegen
nichts sonst; die Ausschlussliste habe ich aktiv gegen eigene Kandidaten angewandt (drei
sind daran gestorben, sie stehen unten unter *geprüft und nicht gezählt*).

**Ergebnis: Bedingung 1, 3, 4 und 5 sind erfüllt — beide Befunde der Vorrunde sind
sachlich behoben, und ich habe sie gegen die Sache nachgeprüft, nicht gegen die Behauptung.
Bedingung 2 reißt an einer Stelle, die diese Fassung selbst geöffnet hat: `T47` schreibt
das Fondsvermögen erstmals als Formel hin, und beide Summanden dieser Formel —
`positionswert(p)` und `korbwert(l, s)` — sind in keinem der drei Dokumente gerechnet. Die
eine Rechenvorschrift, die daran hängt, mischt zwei Skalen, deren Mischung `T5` vier Zeilen
weiter oben ausdrücklich zum Fehler erklärt.**

Der Fehlertyp ist derselbe wie in den Runden 3, 4 und 5, eine Ebene tiefer: eine Größe, die
*benannt*, aber nicht *gerechnet* wird — und wieder wird sie erst sichtbar, weil ein Agent
sie zum ersten Mal in eine Formel geschrieben hat.

Nicht gelesen: `notizen/spielentwerfer.md`, `notizen/architekt.md`.

---

## Befund 1 — `positionswert(p)` und `korbwert(l, s)` haben keine Entstehungsregel, und an ihnen hängt alles

**Bedingung 2.** Schwere: hoch.

`technik.md` T47 (Zeilen 861–869) ist die verbindliche Fassung des Fondsvermögens:

```
beteiligung_wert(l, s) = mal_geteilt(mal_geteilt(korbwert(l, s), anteil[l][s], 10.000),
                                     10.000 − ausstiegsabschlag, 10.000)

fondsvermoegen(z) = kasse
                  + Σ über die 20 Steckplätze  positionswert(p)
                  + Σ über die 12 Land×Sektor  beteiligung_wert(l, s)
                  − hebelstand
```

`kasse`, `anteil[l][s]` und `hebelstand` sind Zustandsadressen aus T15 und tragen nach T45
einen Herkunftseintrag. `ausstiegsabschlag` ist ein Parameterschlüssel (T27). **Die beiden
übrigen Namen sind nirgends definiert.**

**So erzeugt man den Fehler, Schritt für Schritt:**

1. `grep -n "positionswert" technik.md spiel.md daten.md` gibt **genau einen** Treffer:
   `technik.md:866`, die Verwendung selbst. Keine Formel, keine Tabellenzeile, kein
   Parameterschlüssel.
2. `grep -n "korbwert" …` gibt zwei Treffer, beide in T47: die Verwendung (862) und den Satz
   „`korbwert(l, s)` ist der Modellmarktwert desselben Land×Sektor-Korbs, den auch der
   Marktkorb aus Punkt 1 dieses Abschnitts verwendet" (871–873). Das ist eine
   Gleichsetzung, keine Rechenvorschrift.
3. Man folgt der Gleichsetzung nach T33 Punkt 1: *„Der Marktkorb umfasst die 12
   Land×Sektor-Körbe und die 4 Staatsanleihen, jeweils zu Modellmarktwerten."* Punkt 3
   verlangt, den **Mengenkorb** der Vorrunde zu den Preisen dieser Runde zu bewerten. Damit
   ist die Bauart `Menge × Preis` vorgegeben — **welche Menge**, steht nirgends. Kandidaten
   im Zustand wären Kapitalstock oder Wertschöpfung; T15 nennt beide, keine ist gewählt.
4. Man sucht in `daten.md`: `grep -n -i "korb\|marktwert\|kapitalisierung"` gibt einen
   Treffer, und der handelt von HS92-Warenpositionen. Keine Reihe trägt eine
   Marktkapitalisierung.
5. Für die **vier Anleihe-Steckplätze** gibt es nicht einmal einen Preis, an dem eine
   Bewertung ansetzen könnte: T15 führt je Land `leitzins` und `staatsschuld`, aber keinen
   Anleihekurs. Für die vier Währungssteckplätze ist es der Wechselkurs, für die zwölf
   Land×Sektor-Steckplätze der Sektorpreis — beides plausibel, beides ungeschrieben.

**Warum das keine Kleinigkeit ist.** `fondsvermoegen` ist nach T47 Punkt 3 die Größe, die
fünf Stellen lesen: die Abrechnung (Schritt 6), die Mandatsprüfung, Todesart 1, den
Invariantentest aus T30 Prüfung 2 und `v(z)` in T44. Über `v(z)` hängt die Ergebnisgröße
daran, über die Ergebnisgröße Maß 1, Maß 2 und Maß 3. Dieselbe Lücke trifft zusätzlich
`markt.wert` und `markt.rendite` und damit Gegenkraft 3, denn der Marktkorb bewertet
dieselben zwölf Körbe. Ein Programmierer kann Schritt 6 der Schleife nicht schreiben.

**Warum es eine Entwurfsentscheidung ist und keine Bauentscheidung.** Ob der Wert eines
Land×Sektor-Korbs am Kapitalstock oder an der Wertschöpfung hängt, entscheidet, wie stark
der Fonds gegenüber der Welt ist, wie groß ein Anteil in Zehntausendsteln überhaupt sein
kann und wie hart der Preisstoß aus Aktion 1 zurückschlägt („umso stärker, je größer sein
Anteil an diesem Markt ist", `spiel.md:166`). Wählt der Bauagent, misst Maß 2 seine Wahl —
wörtlich der Fall, den Bedingung 1 ausschließt und den T44 für die Botzielgröße gerade
geschlossen hat.

**Nachweis, dass die Lücke unbemerkt ist:** `technik.md` Abschnitt 12 listet fünf offene
Punkte und zwei Beobachtungen an `spiel.md`. Die Bewertung von Positionen und Körben steht
in keinem davon. Die Frage ist nicht offengehalten, sondern übersehen — und T45s
Abzählschritt findet sie nicht, weil sie **keine Zustandsadresse** ist. Die 310 gehen
weiterhin auf; ich habe sie in diesem Lauf von Hand nachgezählt (siehe unten).

---

## Befund 2 — `beteiligung_wert` liefert Tausend USD und wird als US-Cent verbucht; T5 nennt genau diese Mischung einen Fehler

**Bedingung 2.** Schwere: hoch. Unabhängig von Befund 1 und nach dessen Behebung nicht
miterledigt.

Drei Sätze dieser Fassung, die nicht gleichzeitig gelten können:

- `technik.md:108` (**neu in dieser Fassung**) — Fondsgeld, Einheit **US-Cent**, und die
  Aufzählung führt seit heute ausdrücklich den **Beteiligungswert**.
- `technik.md:109` — volkswirtschaftliche Beträge, Einheit **Tausend USD**, und die
  Aufzählung führt den **Marktkorbwert**.
- `technik.md:871–873` — `korbwert(l, s)` ist derselbe Wert, den der Marktkorb verwendet,
  *„eine Bewertung, nicht zwei"*.

**So erzeugt man den Fehler:**

1. `beteiligung_wert` besteht aus zwei `mal_geteilt`-Aufrufen mit den Anteilen
   `anteil[l][s]` und `10.000 − ausstiegsabschlag`, beide durch 10.000. Anteile sind
   einheitenlos; die Formel ist also **skalenerhaltend**. Was hineingeht, kommt heraus.
2. Nach Satz drei geht `korbwert` in Tausend USD hinein. Nach Satz eins muss US-Cent
   herauskommen. Zwischen beiden liegt nach T5 Zeile 129–133 der Faktor **100.000**, und
   derselbe Absatz sagt: *„er wird an genau einer Stelle überschritten: `cent_in_tsd` und
   `tsd_in_cent` … jede andere Vermischung ist ein Fehler."* In der Formel steht kein
   `tsd_in_cent`.
3. Zahlenprobe mit den Beispielen aus T5 selbst. Startkapital 4.200.000.000 Cent
   = 42 Mio USD; ein Korb in der Größenordnung des T5-Beispiels 21.000.000.000 (Tsd USD
   = 21 Bio USD). Der Fonds kauft für sein ganzes Kapital, also `anteil = 20`
   (0,2 % in Zehntausendsteln), `ausstiegsabschlag = 0`:
   `21.000.000.000 · 20 / 10.000 = 42.000.000`. Verbucht als Cent sind das **420.000 USD**
   für einen Einsatz von **42.000.000 USD**.
4. Die Folge ist nicht ein schiefer Wert, sondern ein Partieende: T47 Punkt 1 legt fest,
   dass „die Kasse beim Einstieg den vollen Korbanteil abgibt". Die Kasse fällt um
   4.200.000.000, das Beteiligungsvermögen steigt um 42.000.000, `fondsvermoegen` wird
   negativ — und nach `spiel.md:292` und T33 greift **Todesart 1 in derselben Runde**.
   Jede Partie, in der Aktion 2 nennenswert gespielt wird, endet an ihr.

**Warum das Maß 2 unmittelbar trifft:** Klasse 2 ist die Beteiligungsklasse. T44
(Zeilen 1104–1109) argumentiert, sie könne seit `spiel.md` Fassung 4 Gewinner stellen, weil
Aktion 2 über das Fondsvermögen auf `v` wirke „wie Aktion 1, nur illiquide". Mit der Formel,
wie sie dasteht, wirkt sie nicht wie Aktion 1, sondern wie Selbstmord. Die erste
Abnahmehälfte von Maß 2 — alle drei Kerne stellen einen Gewinner — kann nicht bestehen,
und zwar **von Bauart wegen und unabhängig von jeder Kalibrierung**. Genau diesen Fall hat
der Spielentwerfer als Grund genannt, die Beteiligungen überhaupt ins Fondsvermögen
aufzunehmen; die Formel nimmt die Wirkung wieder zurück.

**Warum es kein Balancebefund ist und die Ausschlussliste nicht greift.** Es gibt hier
keine kalibrierbare Zahl: `ausstiegsabschlag` und `anteil` können jeden zulässigen Wert
annehmen, der Faktor 100.000 bleibt. Es ist auch keine Wirkung, die erst im Lauf sichtbar
wird — sie ist aus zwei Tabellenzeilen und einer Formel ablesbar, ohne dass eine Zeile Code
existiert.

**Der Ausweg ist nicht meiner und ist kurz**, aber es ist eine Wahl zwischen zwei Wegen,
und beide berühren T47s eigenen Satz „eine Bewertung, nicht zwei": entweder
`tsd_in_cent(...)` um den äußeren Aufruf, oder `korbwert` in Cent führen — dann ist es aber
nicht mehr derselbe Wert wie im Marktkorb, und die Gleichsetzung in T47 muss anders
formuliert werden. Welcher Weg, gehört dem Architekten.

---

## Wonach ich gesucht und was ich nicht gefunden habe

Geordnet nach den fünf Bedingungen, damit diese Prüfung von einer, die nicht stattfand,
unterscheidbar ist.

**Bedingung 1 — erfüllt, und der Vorrundenbefund ist zu.** Die Aggregationsregel für den
fehlenden Einfluss steht jetzt in `spiel.md:446–456` als Formel: Summe über die zwei Länder
mit dem höchsten Einfluss, Gleichstand nach `LandId`, je `teile_gerundet(max(0, schwelle_e −
einfluss[land]) · 1.000, schwelle_e)`. Damit haben die drei Lesarten, die ich in der
Vorrunde an zwei erfundenen Partien zu drei verschiedenen Siegern durchgerechnet hatte,
genau eine Auflösung. Die Schranken habe ich nachgerechnet statt übernommen: `einfluss`
liegt nach `technik.md:111` in 0…10.000 (dem Spieler als 0…100 gezeigt, Zeile 121 —
dieselbe Skala wie `schwelle_e`, also ist jeder Summand ≤ 1.000 unabhängig von der Einheit),
daraus `e ≤ 2.000`; `fondsvermoegen > 0` im Band „überlebt", daraus `v ≤ 1.000`; zusammen
`v + e ≤ 3.000`. Maß 1, 2 und 4 sind vom Diff nicht berührt und in den Vorrunden einzeln
durchgegangen; die Kostenzeilen habe ich stichprobenweise nachgerechnet (Maß 1:
`30 · 24·25/2 + 24 = 9.024`, mal 50 = 451.200; Maß 2: 126 Profile, 6 ohne Kern, 120
klassifiziert). **Kein Befund** — Befund 1 und 2 dieser Runde liegen unterhalb der Maße, in
einer Größe, mit der sie rechnen.

**Bedingung 2 — gerissen, siehe oben; die Adressebene selbst ist dagegen sauber, und das
habe ich abgezählt statt geglaubt.** T45 behauptet eine Aufteilung der 310 Adressen in
136 Datenanker, 150 Entwurf, 11 Parameter, 2 Manifest, 11 Vorgabe. Ich habe beide Zerlegungen
gegeneinander gerechnet:

- je spielbarem Land 21 + 20 + 2 + 1 = **44**, wie T15; für die USA fällt der Wechselkurs
  vom Anker in die Vorgabe, also `3 × 21 + 20 = 83` Anker;
- Restwelt 13 + 3 + 6 = **22**, wie T15 (die fünf Vorgaben des Aggregatblocks plus
  `basiswechsel`);
- Anker `83 + 13 + 40 = 136`; Entwurf `4×20 + 3 + 2 + 12 + 1 + 6 + 24 + 20 + 2 = 150`;
  Parameter `4×2 + 3 = 11`; Manifest 2; Vorgabe nach T46 `5 + 1 + 3 + 1 + 1 = 11`.
  Summe **310**, gleich der Zerlegung aus T15 (`198 + 56 + 52 + 4`).

Die Entwurfstabelle in `spiel.md:235–259` liefert für alle 150 `Entwurf`-Adressen einen
Zahlenwert; die 32 Druck- und Restverzögerungsadressen aus dem Vorrundenbefund stehen dort
jetzt, und die Doppelführung mit T23 Punkt 1 ist aufgelöst (`technik.md:510–523`). Die
Vorrangregel in T45 („der Eintrag ist die Stelle, die den Wert *bestimmt*") schließt den
Fall zweier Einträge sauber. **Auf der Adressebene kein Befund.** Beide Befunde oben liegen
außerhalb der 310, und genau deshalb findet der Abzählschritt sie nicht.

**Bedingung 3 — erfüllt, alle Zahlen des Diffs nachgerechnet.** Der Vorrundenbefund zur
Steckplatzzahl ist zu: `spiel.md:525–528` trägt jetzt die allgemeine Form aus T43 (`nach 5k
Runden 3k·ai von 15k`, mit `k = 1` und `k = 3` ausgeschrieben), wörtlich gleich
`technik.md:997–1002`. Die Bandänderung ist in beiden Dokumenten vollständig nachgeführt:
Band „überlebt" 25.000…28.000 (`spiel.md:443` / `technik.md:167`), obere Lücke
28.001…30.999 (`spiel.md:489` / `technik.md:943`), Kappungsunterschied zu `B` entfallen
(`spiel.md:479–482` / `technik.md:1071–1079`), Fondsvermögen einschließlich Beteiligungen
(`spiel.md:276` / `technik.md:12`, T30 Prüfung 2, T44 `v(z)`, T47). Selbst nachgerechnet:
`(26+1)·1.000 + 3.000 = 30.000`, Todesband ab 31.000, also 999 Milli-Runden Luft und
`R ≤ 26` scharf; bei `R = 27` fielen beide Enden auf 31.000 zusammen. Ebenso
`24 × 61 = 1.464`, `24 × (1 + 60·61) = 87.864`, `87.864 × 7.560 = 664.251.840`
(1,85 h auf einem Kern, 13,8 min auf acht beim Planwert, 1,15 h auf acht bei 50 µs),
`60 · 300 + 24 = 18.024` und `18.024 / 1.464 = 12,3`, Nachtlauf
`11.519.040 + 240.000 + 200 + 24 + 24.000 = 11.783.264` (2,0 bzw. 9,8 Minuten),
`310 × 8 = 2.480` Byte, Drittel `⌊24/3⌋ = 8` und `⌊48/3⌋ = 16`. **Keine Abweichung.**

**Bedingung 4 — erfüllt, und ich habe die Messung wiederholt statt sie zu zitieren.**
Eigener Abruf am 2026-09-01:
`api.worldbank.org/v2/country/USA/indicator/NV.IND.TOTL.ZS?date=1994:2024` — Werte für
1997 bis 2021, `null` für 1994–1996 und 2022–2024. Das sind 25 Stützstellen und `R = 24`,
wie im Frontmatter beider Dokumente. Die Abnahmeregel steht unverändert mit Zahl
(`spiel.md:704–728`, T37: 16 Prüfgegenstände, bestanden bei höchstens zwei gerissenen),
die Schwellen ebenso (MAPE 20 %, 300 bp, Richtungstreue 0,6). Vom Diff nicht berührt.

**Bedingung 5 — erfüllt.** Beide Befunde der Vorrunde sind beantwortet, je mit einer der
drei zulässigen Antworten: Befund 1 *behoben* (`spiel.md:525–528`), Befund 2 *behoben*, in
der Aggregation wie vorgeschlagen und in der Kappung ausdrücklich *anders gelöst* — sie ist
gestrichen statt übernommen, mit Begründung und mit den beiden Folgezahlen, die der
Architekt nachgeführt hat. Beide habe ich gegen die Sache nachgeprüft, nicht gegen die
Behauptung. Die leere Datei `pruefung-0001-entwurf-abnahme-runde5-2026-09-01.md` (0 Byte,
Commit `adb3b55`) enthält keinen Befund; es gibt aus ihr nichts abzuarbeiten.

## Geprüft und nicht gezählt

Damit die Grenze sichtbar bleibt und der nächste Lauf dieselben Kandidaten nicht neu
aufwirft.

- **Die Kostenaussage zu `B` ist seit T47 zu klein, und das ist kein Befund.**
  `technik.md:1130` nennt „rund zwanzig Ganzzahloperationen", zählt aber nur `v` und `e`
  selbst; `v(z)` ruft `fondsvermoegen(z)`, und das sind seit T47 zwanzig Positions- und
  zwölf Beteiligungsbewertungen mit je zwei `i128`-`mal_geteilt`. Realistisch sind einige
  Dutzend bis gut hundert Operationen, also rund ein Prozent statt drei Promille eines
  Weltschritts. Keine der fünf Bedingungen fragt danach: `spiel.md` nennt die Zahl nicht
  (also nicht Bedingung 3), sie ist keine Rechenvorschrift eines Maßes und keine Größe des
  Modells. Der Planwert von 10 µs hat Bandbreite bis 30 und die Reserve rechnet mit 50 —
  die Aussage von Abschnitt 10 trägt weiter. **Für den Projektmanager: eine Zeile, kein
  Lauf.**
- **`markt.wert` in Runde 1 trägt den Herkunftseintrag `Manifest`, obwohl die
  Entwurfstabelle ihn nennt.** Nach dem Wortlaut der Tabelle wären es zwei Einträge; T45s
  Vorrangregel löst das ausdrücklich auf („ein Verweis ist kein zweiter Eintrag"). Ich hatte
  es als Kandidaten für Bedingung 2 notiert und lasse es fallen — die Regel steht
  geschrieben und ist auf alle sechs Verweiszeilen gleich angewandt.
- **`spiel.md` sagt `einfluss` liege „in 0 … 100", `technik.md` speichert ihn in
  Zehntausendsteln.** Das sieht nach Bedingung 3 aus und ist keine: `technik.md:121`
  benennt die Umrechnung ausdrücklich und schreibt sie der Sicht zu, und die Schranke
  `e ≤ 2.000` gilt in beiden Einheiten, weil `schwelle_e` in derselben steht wie
  `einfluss`. Eine erklärte Skalenkonvention ist kein Widerspruch in einer Zahl.

## Was ich nicht geprüft habe

- **Ob die Schwellen von Maß 4 mit endogener Produktivität erreichbar sind.** Unverändert
  das größte ungemessene Risiko; nur der Rückvergleicher am laufenden Kern kann es sagen.
- **Den Planwert von 10 Mikrosekunden je Weltschritt.** Es gibt keinen Kern, also keine
  Messung. `technik.md` sagt das selbst und nennt die Folge.
- **Die IFS-Leitzinsreihen für China und Brasilien.** Hängen am Jahrgang, nicht am Entwurf;
  `imf.org` weist den Abruf mit HTTP 403 ab.
- **Die Zahlenwerte sämtlicher Schwellen und Elastizitäten**, einschließlich
  `ausstiegsabschlag`, `zwangsabschlag` und der Stufenweite einer Position. Sie stehen nach
  T27 in `parameter.toml` und werden gemessen, nicht entworfen. *Der Faktor 100.000 aus
  Befund 2 ist keine von ihnen* — er verschwindet für keinen zulässigen Parameterwert.

## Für den Projektmanager, nicht für den Bauagenten

Zwei Punkte zur Ablaufsteuerung, die ich melde und nicht entscheide.

1. **Der Rücklaufzähler steht mit diesem Urteil bei 3 von 3.** Die Tabelle im Arbeitspaket
   endet bei Runde 3 und ist seither nicht nachgeführt worden. Gegen *dieses* Kriterium
   geurteilt wurde in Runde 3 (3 Befunde), Runde 4 (2 Befunde) und heute (2 Befunde); die
   Runden 1 und 2 liefen gegen ein selbstgegebenes Kriterium und zählen nach dem Wortlaut
   des Pakets nicht mit, Runde 5 hat kein Urteil abgelegt (leere Datei). Damit ist die im
   Paket vorgesehene Grenze erreicht. **Ich senke das Kriterium nicht und halte es für
   richtig gestellt** — die beiden Befunde sind wörtlich Bedingung 2 und nicht „Genauigkeit,
   die über die fünf Bedingungen hinausgeht". Ob daraus `blockiert` und eine Meldung an den Geschäftsführer folgt oder
   ein vierter Rücklauf, ist deine Entscheidung, nicht meine.
2. **Die beiden Befunde treffen zwei Gewerke.** Befund 1 verlangt eine Modellentscheidung
   (woran hängt der Wert eines Land×Sektor-Korbs, und was ist eine Positionsstufe wert) und
   gehört dem Spielentwerfer; Befund 2 ist eine Skalenfrage und gehört dem Architekten. Nach
   der Erfahrung der Runde 4 — ein Rücklauf, zu dem nur ein Gewerk lief, konnte den Befund
   des anderen nicht schließen — sollten beide laufen, und der Spielentwerfer zuerst.
