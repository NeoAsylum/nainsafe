---
typ: pruefung
paket: 0001-entwurf-abnahme
pruefer: entwurf-pruefer
datum: 2026-09-01
urteil: zurueck
kriterium_geprueft: die fuenf Bedingungen einzeln -- Rechenvorschrift je Mass (1), Herkunft jeder der 310 Adressen (2), Zahlengleichheit beider Dokumente (3), Durchfuehrbarkeit des Rueckvergleichs (4), Abarbeitung der drei Vorrundenbefunde (5); Bedingung 5 erfuellt, Bedingung 2 jetzt erfuellt, Bedingung 3 unveraendert gerissen, Bedingung 1 an einer Stelle gerissen, die T44 selbst sichtbar macht
befunde: 2
---

# Prüfung der vierten Fassung gegen `0001-entwurf-abnahme`

Zweite Prüfung gegen dieses Paket. Geurteilt wird gegen dessen fünf Bedingungen und gegen
nichts sonst; die Ausschlussliste habe ich aktiv gegen eigene Kandidaten angewandt (drei
sind daran gestorben, sie stehen unten unter *geprüft und nicht gezählt*).

**Ergebnis: Bedingung 2, 4 und 5 sind erfüllt. Bedingung 3 ist unverändert gerissen —
`spiel.md` ist seit der letzten Prüfung nicht angefasst worden. Bedingung 1 reißt an einer
Stelle, die T44 selbst offenlegt: Er brauchte eine Aggregationsregel für den fehlenden
Einfluss, hat sie für die Botgröße `B` geschrieben und für die Ergebnisgröße ausdrücklich
ausgeschlossen — die Ergebnisgröße hat sie nicht.**

Von den drei Vorrundenbefunden sind zwei sachlich behoben (T44, T23 Punkt 1 mit T45) und
gegen die Sache nachgeprüft, nicht gegen die Behauptung. Befund 1 dieser Runde ist der alte
Befund 3, unverändert. Befund 2 ist neu und liegt eine Ebene über dem alten Befund 1.

Nicht gelesen: `notizen/spielentwerfer.md`, `notizen/architekt.md`.

---

## Befund 1 — Bedingung 3 ist unverändert gerissen, und `spiel.md` wurde seit der letzten Prüfung nicht angefasst

**Bedingung 3.** Schwere: niedrig in der Sache, binär in der Bedingung.

Die beiden Sätze stehen heute so da:

- `spiel.md:438` — *„Es wird nie gerundet und nie gezogen: über **15 Runden** bekommt Art
  `i` genau `3·ai` Steckplätze, der Rest ist beschränkt."*
- `technik.md:840` — *„Für `k = 3` sind es **fünfzehn Runden** und `9·ai` von
  fünfundvierzig."*

**So erzeugt man den Widerspruch:** Man setzt in beiden Sätzen die Rundenzahl 15 ein und
liest ab, wie viele Steckplätze Art `i` bekommt. `spiel.md` sagt `3·ai`, `technik.md` sagt
`9·ai`. Beide Dokumente nennen dieselbe Größe und nennen verschiedene Werte; das ist
wörtlich der Fall, den Bedingung 3 ausschließt. Der Rechenweg ist unstrittig — ich habe das
Vorratsverfahren erneut für das Referenzprofil und für `(2,1,1,1,0)` von Hand gerechnet, der
Vektor schließt sich nach fünf Runden, und die Zahl des Architekten ist die richtige.

**Was sich seit der letzten Prüfung geändert hat, ist nur die Seite, die schon recht
hatte.** `technik.md` T43 trägt die Invariante jetzt in allgemeiner Form (`nach 5k Runden
3k·ai von 15k`), und T30 Prüfung 1 prüft `k = 1` und `k = 3`. Das ist eine saubere
Verhärtung gegen den Schaden — es beseitigt den Widerspruch aber nicht, sondern schreibt ihn
zum ersten Mal ausdrücklich hin.

**Der Nachweis, dass hier kein Bauagent säumig war**, sondern eine Zuständigkeit:
`git log --name-only` zeigt für `specs/0016-…/spiel.md` als letzten Schreibzugriff
`7351bf1 spielentwerfer`, und dieser Commit liegt **vor** `67805e6`, der die Prüfung mit
Befund 3 abgelegt hat. Zwischen der Prüfung und heute hat allein `58c1c9a architekt`
geschrieben, und zwar nur `technik.md`. Der Architekt kann `spiel.md` nicht ändern; seine
Rolle verbietet es und die Werkzeuge dafür hat er nicht. Die Reparatur ist **ein Wort** —
`15 → fünf` oder `3·ai → 9·ai` — und sie gehört dem Spielentwerfer.

**Für den Projektmanager, nicht für den Bauagenten:** Das Paket steht auf
`rolle: spielentwerfer` und führt beide Dateien. Solange zu einem Rücklauf nur der Architekt
läuft, kann dieser Befund nicht geschlossen werden, und der Rücklaufzähler steigt an einer
Stelle, an der niemand einen Fehler gemacht hat. Das ist kein Grund, Bedingung 3 zu senken —
sie ist richtig gestellt —, sondern einer, den nächsten Lauf dem Spielentwerfer zu geben.

---

## Befund 2 — Die Ergebnisgröße sagt nicht, wie „fehlender Einfluss" über die Länder gerechnet wird, und alle drei Prüfstandsmaße rechnen mit ihr

**Bedingung 1.** Schwere: hoch. Derselbe Fehlertyp wie Befund 1 der Vorrunde, eine Ebene
darüber — dort fehlte die Vergleichsgröße des Bots, hier fehlt ein Teil der Größe, gegen die
die Maße selbst abnehmen.

Die Ergebnisgröße hat drei Zweige (`spiel.md:398-402`). Der mittlere lautet:

> `(R+1) × 1.000 + Fehlbetrag`, Fehlbetrag = fehlendes Vermögen plus **fehlender Einfluss**,
> je in Promille der eigenen Schwelle, je Teil bei 1.000 begrenzt

**Einfluss ist eine Größe je Land** (`spiel.md:210`, `238`; T15 führt ihn unter „politisch",
eine Adresse je spielbarem Land). Das Mandat verlangt ihn **über der Schwelle in mindestens
zwei Ländern** (`spiel.md:6`). „Fehlender Einfluss" ist also ein Wert je Land, und die Regel,
wie aus vier Werten einer wird, steht nirgends.

**So erzeugt man den Fehler, Schritt für Schritt:**

1. Man sucht die Aggregationsregel in `spiel.md`. Der Begriff kommt genau einmal vor, in
   Zeile 401. Sonst nirgends — `grep -n "Einfluss" spiel.md` gibt neun Treffer, keiner
   rechnet.
2. Man sucht sie in `technik.md`. **T34 lehnt sie ausdrücklich ab:** *„Die dreiteilige
   Tabelle steht dort und wird hier nicht wiederholt, nicht ausgelegt und nicht gedeckelt."*
   Was der Architektur zusteht, sind vier Punkte (Typ, Ordnung, Median, Bandprüfung); keiner
   davon rechnet den Fehlbetrag.
3. Man findet die Regel schließlich doch — aber für eine **andere** Größe. T44 braucht genau
   diese Aggregation für die Botbewertung und schreibt sie hin: *„`e(z)` = Summe über die
   zwei Länder mit dem höchsten Einfluss (Gleichstand nach `LandId`)"*. Und T36 stellt
   ebenso ausdrücklich fest, dass sie für die Ergebnisgröße **nicht** gilt: *„Das
   Profilergebnis `E(p)`, der Gewinnvergleich gegen `R × 1.000` und die Argminima `p*` und
   `q*` laufen ausschliesslich über die Ergebnisgröße aus `spiel.md`, nie über `B`."*
4. Der Programmierer steht damit vor derselben Frage, die T44 für den Bot beantwortet hat,
   und hat für das Partieergebnis keine Antwort.

**Warum das keine Kleinigkeit ist: drei naheliegende Lesarten geben drei verschiedene
Ergebnisse, und sie ordnen die Profile verschieden.** Zwei Partien, Schwelle `schwelle_e`
auf 1.000 normiert, Vermögensteil je 0:

| | Einfluss der vier Länder | Summe der zwei besten Fehlbeträge | schwächeres der zwei besten | Mittel der zwei besten |
|---|---|---:|---:|---:|
| Profil `p` | 1.000 / 0 / 0 / 0 | 1.000 (0 + 1.000) | 1.000 | 500 |
| Profil `q` | 500 / 480 / 0 / 0 | 1.000 (500 + 520, gekappt) | 520 | 510 |

- Lesart *Summe*: `E(p) = E(q) = 26.000` → **Gleichstand**, entschieden durch die
  Profilkennung.
- Lesart *schwächeres der zwei besten*: `E(p) = 26.000`, `E(q) = 25.520` → **`q` gewinnt**.
- Lesart *Mittel*: `E(p) = 25.500`, `E(q) = 25.510` → **`p` gewinnt**.

Dieselben zwei Läufe, drei verschiedene Sieger. Das trifft die Maße unmittelbar:

- **Maß 3** wählt `p*` als Profil mit kleinstem `Efrüh` und `q*` als Profil mit kleinstem
  `Espät` (`spiel.md:546`). Erreicht in einem Fenster kein Profil das Mandat — der plausible
  Fall für das Frühfenster, in dem der Fonds acht Runden hat —, entscheidet **allein** der
  Fehlbetrag, welches Profil das Argminimum ist. Die Verschiebung `Σ|p*i − q*i|/5` nimmt nur
  Werte im Raster 0,4 an, die Schwelle liegt bei 0,4: Ein anderes Argminimum kippt die
  Abnahme in einem Schritt.
- **Maß 2**, zweiter Teil: `max(Ek) ≤ 1,25 × min(Ek)` über die drei Klassenbestwerte
  (`spiel.md:522`). Ein Klassenbestwert im Band „überlebt" geht mit seinem Fehlbetrag in
  diesen Quotienten ein.
- **Maß 1** zählt den Anteil der 30 Ergebnisse, die um **mehr als 1.000 Milli-Runden** vom
  Median abweichen (`spiel.md:472`). Das Band „überlebt" ist 2.000 Milli-Runden breit, die
  Schwelle liegt bei 1.000 — die Lesart entscheidet also mit, ob eine Runde als
  entscheidungsdicht zählt.

**Warum das eine Entwurfsentscheidung ist und keine Bauentscheidung:** Die drei Lesarten
sind nicht verschieden genau, sondern verschieden *gemeint*. Die Summe bestraft ein
einseitiges Portfolio härter, das Mittel belohnt Breite, das schwächere der zwei besten
misst genau den Abstand zum Mandat. Welche gilt, sagt, was ein knapp gescheiterter Fonds
wert ist — das ist die Frage, die die Ergebnisskala stellt, und sie gehört dem
Spielentwerfer. Wählt der Bauagent, misst Maß 2 und Maß 3 seine Wahl mit; das ist wörtlich
der Fall, den Bedingung 1 ausschließt.

**Der Ausweg ist nicht meiner, und er ist kurz.** Ein Halbsatz in Zeile 401, der die
Aggregation benennt. Nimmt `spiel.md` die Regel aus T44 (Summe über die zwei Länder mit dem
höchsten Einfluss, Gleichstand nach `LandId`), steht sie ohnehin schon geschrieben, beide
Dokumente rechnen dieselbe Größe gleich, und der Kappungsunterschied zwischen `B` und der
Ergebnisgröße bleibt der einzige — er ist in T44 begründet und ausdrücklich kein Befund.

---

## Wonach ich gesucht und was ich nicht gefunden habe

Geordnet nach den fünf Bedingungen, damit diese Prüfung von einer, die nicht stattfand,
unterscheidbar ist.

**Bedingung 1.**
*Maß 1 und Maß 4* — unverändert seit der Vorrunde, dort einzeln durchgegangen und
vollständig befunden (T35 für die Ziehregel, T42 für MAPE, Ratenfehler, Richtungstreue
samt der beiden Fälle `soll = 0` und Neubasierung). Diff nicht berührt. **Kein Befund.**
*Maß 2 und 3* — die Lücke der Vorrunde ist zu. T44 ist eine Rechenvorschrift und keine
Absichtserklärung: Eingabe (Zwischenzustand nach einem Weltschritt), Rechenweg (drei Zweige,
`v` und `e` als Promillefehlbeträge), Ausgabe (`i64`), Auswahlregel (kleinstes `B`,
Gleichstand lexikographisch über die Aktionskennungen aus T32, dann Kandidatenindex `c`).
Ich habe die Eigenschaften nachgerechnet, statt sie zu übernehmen:
`v ≤ 1.000` bei lebendem Fonds und `e ≤ 2.000` geben `25.000 ≤ B ≤ 28.000`; das Todesband
beginnt bei `30.000 + 1.000 = 31.000`, das Mandatsband endet bei `24.000` — die drei Bänder
sind disjunkt, und der Bot zieht den Tod nie vor. Die Kostenaussage stimmt: `B` kostet
zwanzig Ganzzahloperationen gegen 7.500 je Weltschritt (`technik.md:1097`), also drei
Promille, und `R × (1 + 60) = 1.464` bleibt stehen; das verworfene Nachspiel kostete
`60 · 300 + 24 = 18.024`, das 12,3-fache. **Der einzige offene Punkt ist Befund 2 — und er
liegt nicht in `B`, sondern in der Größe, gegen die die Maße abnehmen.**

**Bedingung 2 — jetzt erfüllt, und ich habe es nachgezählt statt geglaubt.** Die 32 Adressen
aus dem Vorrundenbefund haben einen Startwert: `land.<L>.instrument.<I>.druck` und `…​.rest`,
je `4 × 4 = 16`, beide 0, in `technik.md` T23 Punkt 1 als Tabelle mit der
Entstehungsbegründung. Die Zahl 16 statt 20 stimmt — T15 gibt der Restwelt ausdrücklich
keine Instrumente. Damit trägt jede der 310 Adressen entweder einen Datenanker (19 Reihen),
einen Eintrag der Tabelle „Jede Größe ohne Datenanker" in `spiel.md`, einen
Parameterschlüssel oder eine Vorgabe aus T23. Die Abgleichliste der Vorrunde habe ich nicht
wiederholt, weil an ihr nichts geändert wurde; die neue Zeile habe ich gegen T15 und gegen
die Entstehungsregel in Schritt 3 geprüft. **Kein Befund.**

**Bedingung 3.** Alle Zahlen des Diffs nachgerechnet: `60 · Σ(25−t) + 24 = 60 · 300 + 24 =
18.024` und `18.024 / 1.464 = 12,3` („das Zwölffache"); `24 × (1 + 60 × 61) = 87.864`, mal
`7.560` Partien = `664.251.840` („664 Millionen"), beim Planwert 10 µs 1,85 Stunden auf einem
Kern und 13,8 Minuten auf acht, im ungünstigen Fall (50 µs, dieselben 50 µs, die den
Nachtlauf von 2,0 auf 9,8 Minuten heben) 1,15 Stunden auf acht — alle vier Angaben tragen.
`20 / 7.500 = 2,7 ‰`. Unverändert und stichprobenweise nachgeprüft: `R = 24`, Sollmaske
`175 + 135 = 310`, Nachtlauf `11.519.040 + 240.000 + 200 + 24 + 24.000 = 11.783.264`,
`3.689.280 = 126 × 20 × 1.464`. **Nur die eine Zahl aus Befund 1 weicht ab.**

**Bedingung 4.** Vom Diff nicht berührt — kein Wort an T22, T23 Punkte 2 und 8, T24, T26,
T37 oder T42. Der Startjahrgang 1997–2021 mit 25 Stützstellen und `R = 24` ist in der
Vorrunde durch meinen **eigenen** Weltbank-Abruf belegt worden
(`api.worldbank.org/v2/country/USA/indicator/NV.IND.TOTL.ZS?date=1994:2024`, 2026-09-01:
Werte 1997–2021, `null` davor und danach). Diesen Abruf habe ich heute **nicht** wiederholt,
weil sich weder die Reihe noch das Fenster noch die Abnahmeregel geändert haben; die
Abnahmeregel steht unverändert mit Zahl (16 Prüfgegenstände, höchstens zwei dürfen reißen).
**Bedingung erfüllt.**

**Bedingung 5.** Alle drei Vorrundenbefunde sind beantwortet, je mit einer der drei
zulässigen Antworten: Befund 1 *behoben* (T44), Befund 2 *behoben* (T23 Punkt 1 und T45),
Befund 3 *anders gelöst* (allgemeine Invariante in T43 plus Einheitstest für `k = 1` und
`k = 3`). Keiner übersprungen, keiner mit *widersprochen*. Die ersten beiden habe ich gegen
die Sache nachgeprüft, nicht gegen die Behauptung — siehe oben. **Bedingung erfüllt.**
Dass Befund 3 trotz zulässiger Antwort als Befund 1 dieser Runde wiederkehrt, ist kein
Widerspruch: Bedingung 5 fragt nach der Antwort, Bedingung 3 nach dem Zustand der Dokumente.

## Geprüft und nicht gezählt

Damit die Grenze sichtbar bleibt und der nächste Lauf nicht dieselben drei Kandidaten neu
aufwirft.

- **Beide Reparaturen stehen im falschen Dokument — und das ist nach diesem Kriterium kein
  Befund.** Die Zielgröße des Suchbots steht in `technik.md` T44 statt in `spiel.md`, die
  zwei Startwertzeilen in T23 Punkt 1 statt in der Tabelle, die von sich sagt, sie führe
  „alle übrigen, abschließend" (`spiel.md:228`). Ich hatte mir beides für diesen Lauf
  ausdrücklich vorgemerkt. Die fünf Bedingungen fragen nach der Rechenvorschrift und nach
  der Herkunft, nicht nach dem Ort; und beide Stellen sagen selbst, dass eine Fassung des
  Spielentwerfers sie sticht. Ein Widerspruch **in einer Zahl** entsteht nicht, weil die
  Tabelle für die 32 Adressen keinen anderen Wert nennt, sondern gar keinen.
- **Zählen die zwölf Beteiligungen zum Fondsvermögen?** `technik.md` Abschnitt 12 meldet die
  Frage neu, und sie ist berechtigt: Ist die Antwort nein, kann Klasse 2 die erste
  Abnahmehälfte von Maß 2 nicht bestehen. Ich zähle sie trotzdem nicht, und der Grund ist
  nachprüfbar statt großzügig: T15 führt „Positionssteckplätze" (20) und „Beteiligungen"
  (24) als zwei benannte Gruppen, `spiel.md:250` schreibt „Kasse + bewertete **Positionen** −
  Hebel", und damit hat ein Programmierer eine bestimmte Lesart, ohne zu fragen. Die Folge
  für Klasse 2 ist eine Wirkung, die im Lauf sichtbar wird — dafür gibt es nach der
  Ausschlussliste den Prüfstand. **Läuft der Spielentwerfer ohnehin (Befund 1 und 2), kostet
  der klarstellende Halbsatz nichts und schließt die Frage mit.**
- **T45 verlangt für alle 310 Adressen einen Herkunftseintrag, und für sechs gibt es keinen
  zulässigen.** Die vier zulässigen Eintragsarten sind Datenanker, Entwurfstabelle,
  Parameterschlüssel und `Vorgabe(T-Nummer)` — Letztere „derzeit allein T23 Punkt 1".
  Die zwei Weltpreisadressen (T15, eigene Gruppe, nicht die 15 Sektorpreise) und die vier
  Partiefelder (Runde, Jahrgangskennung, Parametersatz-Prüfsumme, Mandatsstand) fallen unter
  keine davon; nach dem Wortlaut bräche der Jahrgangsbau ab. Das ist **keine** der fünf
  Bedingungen — die Größen selbst sind definiert (Weltpreis über die Markträumung in
  Schritt 4, die Partiefelder sind Buchführung) —, deshalb kein Befund. Für den
  Projektmanager: eine Zeile in T45 oder T23, kein eigener Lauf.

## Was ich nicht geprüft habe

- **Ob die Schwellen von Maß 4 mit endogener Produktivität erreichbar sind.** Unverändert
  das größte ungemessene Risiko; nur der Rückvergleicher am laufenden Kern kann es sagen.
- **Den Planwert von 10 Mikrosekunden je Weltschritt.** Es gibt keinen Kern, also keine
  Messung. `technik.md` sagt das selbst und nennt die Folge.
- **Die Drittanbieter-Ausnahme der WDI und die IFS-Leitzinsreihen für China und Brasilien.**
  Hängen am Jahrgang, nicht am Entwurf; `imf.org` weist den Abruf weiter mit HTTP 403 ab.
- **Die Zahlenwerte sämtlicher Schwellen und Elastizitäten**, einschließlich der beiden
  Mandatsschwellen, auf die T44 zugreift. Sie stehen nach T27 in `parameter.toml` und werden
  gemessen, nicht entworfen.
