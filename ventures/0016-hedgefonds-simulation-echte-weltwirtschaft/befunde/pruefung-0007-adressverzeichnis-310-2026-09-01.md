---
typ: pruefung
paket: 0007-adressverzeichnis-310
pruefer: daten-pruefer
datum: 2026-09-01
urteil: geprueft
kriterium_geprueft: alle vier Zaehlungen mit grep gegen die Tabelle selbst nachgerechnet statt gegen die Zusammenfassung -- 310 Zeilen ohne doppelte Adresse, Gruppen 48/36/12/64/12/4/22/40/2/12/2/5/3/20/24/4 = 198+56+52+4, Herkunft 136/150/11/2/11 einschliesslich der elf Vorgabe- und elf Parameterzeilen Zeile fuer Zeile gegen T46 und T45, Klassen 3/71/36/22/22/5/5/25/32/4/83/2 global und 44 je spielbarem Land sowie 22 fuer die Restwelt; zusaetzlich jeder Datenanker gegen Dimension und Modelleinheit seiner Reihe
befunde: 2
---

# Prüfung des Adressverzeichnisses gegen `0007-adressverzeichnis-310`

Nicht gelesen: `notizen/datenbauer.md`.

**Ergebnis: Das Abnahmekriterium ist erfüllt, und zwar an der Tabelle nachgerechnet, nicht
an der Zusammenfassung.** Alle vier Zählungen gehen auf, die elf `Vorgabe`- und die elf
`Parameter`-Zeilen sind einzeln gegen T46 und T45 wiedergefunden, und die 136 Datenanker
verteilen sich exakt so auf die Reihennummern, wie es die Spalte „Dimension" der
Reihenliste zulässt. Der teuerste Fehler meiner Rolle — ein stiller Einheitenfehler — ist
nicht eingetreten: Jede Skalenklasse passt zur Modelleinheit ihrer Reihe, einschliesslich
der Falle, vor der T5 ausdrücklich warnt (Produktivität in Klasse 7, nicht 5).

Die zwei Befunde betreffen **nicht** die Zählungen, sondern *Befund 1 der geprüften Datei
selbst*. Er stützt sich auf eine Textstelle, die im selben Satz für gestrichen erklärt
wird — und die Datei wendet dieselbe Stelle an einer zweiten Adressgruppe genau
umgekehrt an. Keiner der beiden ändert eine Adresse, eine Gruppe, eine Herkunft oder eine
Klasse; beide sind Sache des Projektmanagers, nicht des Bauagenten.

---

## Wie ich das Kriterium geprüft habe

Alle Aufrufe gegen
`ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/adressen.md`, im
Folgenden als `<datei>` abgekürzt. Jeder ist wiederholbar; ich habe die Spalten aus der
Tabelle selbst geschnitten und nirgends die Abschnitte *Die vier Zählungen* gelesen, um
die Zahl zu bekommen.

### 1. 310 Zeilen, keine Adresse zweimal

```
grep -cP '^\| *[0-9]+ \| `' <datei>                        → 310
grep -oP '^\| *[0-9]+ \| `\K[^`]+' <datei> | sort | uniq -d → leer
grep -oP '^\| *\K[0-9]+(?= \| `)' <datei> | sort -n | uniq -d → leer
```

310 Tabellenzeilen, 310 verschiedene Adressen, 310 verschiedene laufende Nummern. **Erfüllt.**

### 2. Nach Gruppe: 198 + 56 + 52 + 4

Dritte Spalte geschnitten und gezählt:

```
grep -P '^\| *[0-9]+ \| `' <datei> | grep -oP '^\|[^|]*\|[^|]*\| *\K[^|]*?(?= *\|)' | sort | uniq -c
```

| Gruppe | gezählt | T15 |
|---|---:|---:|
| je Sektor | 48 | 4 × 12 |
| Aggregat | 36 | 4 × 9 |
| politisch | 12 | 4 × 3 |
| Instrumente | 64 | 4 × 16 |
| Restdauern | 12 | 4 × 3 |
| Buchhaltung | 4 | 4 × 1 |
| Restwelt | 22 | 22 |
| **Gebiete** | **198** | `4 × 44 + 22` |
| Handel | 40 | 40 |
| Weltpreise | 2 | 2 |
| Nachahmerzähler | 12 | 12 |
| Marktkorb | 2 | 2 |
| **Welt** | **56** | `40 + 2 + 12 + 2` |
| Fonds, Aggregat | 5 | 5 |
| Fonds, Überrendite | 3 | 3 |
| Positionssteckplätze | 20 | 20 |
| Beteiligungen | 24 | 24 |
| **Fonds** | **52** | `5 + 3 + 20 + 24` |
| **Partie** | **4** | 4 |

Sechzehn Gruppen, keine unbenannte, keine übrige. **Erfüllt.**

### 3. Nach Herkunft: 136 + 150 + 11 + 2 + 11

```
grep -P '^\| *[0-9]+ \| `' <datei> | grep -oP '^\|[^|]*\|[^|]*\|[^|]*\| *\K[A-Za-zä]+' | sort | uniq -c
→ 136 Datenanker · 150 Entwurf · 2 Manifest · 11 Parameter · 11 Vorgabe
```

**Die elf `Vorgabe`-Zeilen gegen T46, einzeln.** Ausgelesen mit
`grep -nP '^\| *[0-9]+ \| \`[^\`]*\`\*? \| [^|]*\| *Vorgabe' <datei>`; Startwert jeweils
mitgeprüft, weil T46 ihn vorschreibt:

| T46 verlangt | Startwert nach T46 | in `<datei>` | Startwert dort |
|---|---:|---|---:|
| `gebiet.<G>.basiswechsel`, fünf Gebiete | 0 | 44, 88, 132, 176, 198 | 0, 0, 0, 0, 0 |
| `land.US.wechselkurs` | 10.000 | 19 | 10.000 |
| `restwelt.leitzins` | 0 | 194 | 0 |
| `restwelt.staatsschuld` | 0 | 196 | 0 |
| `restwelt.haushaltssaldo` | 0 | 197 | 0 |
| `restwelt.wechselkurs` | 10.000 | 195 | 10.000 |
| `restwelt.inflation` | 0 | 193 | 0 |

Elf Adressen, elf Zeilen, elf übereinstimmende Startwerte. Keine zwölfte, keine fehlende.

**Die elf `Parameter`- und zwei `Manifest`-Zeilen gegen T45.** T45 zerlegt `Parameter` in
`4 × 2 + Fondskasse + Anlegerbestand + Prüfsummenfeld` und `Manifest` in
`markt.wert + Jahrgangskennung`. Gefunden: 4 × `zustimmung` (22, 66, 110, 154), 4 ×
`instrument.regulierung.stand` (37, 81, 125, 169), `fonds.kasse` (255),
`fonds.anlegerbestand` (258), `partie.parameter_pruefsumme` (309) — elf, Zerlegung
deckungsgleich. `Manifest`: `markt.wert` (253), `partie.jahrgang_id` (308) — zwei,
deckungsgleich.

**Die Herkunft je Gebiet gegen die Zerlegung in T45**, weil die Summe 136 auch aufginge,
wenn zwei Gebiete sich gegenseitig ausglichen:

| Gebiet | gezählt | T45 verlangt |
|---|---|---|
| US | 20 Anker, 20 Entwurf, 2 Parameter, 2 Vorgabe | 20 Anker (Wechselkurs fällt an die Vorgabe), sonst wie die anderen |
| CN | 21, 20, 2, 1 | `21 / 20 / 2 / 1` |
| DE, BR | wie CN (aus der Gesamtsumme) | ebd. |
| Restwelt | 13 Anker, 3 Entwurf, 6 Vorgabe | „13 Anker, 3 `Entwurf` und 6 Vorgaben" |

`20 + 3 × 21 + 13 + 40 = 136`. **Erfüllt.**

**Startwertspalte.** Das Arbeitspaket verlangt einen Startwert genau dort, wo die Herkunft
`Entwurf` oder `Vorgabe` ist. `grep -cP '… Entwurf *\|[^|]*\| *— *\|' <datei>` → **0**
Entwurfzeilen ohne Startwert; alle 149 Zeilen mit `Datenanker`, `Parameter` oder
`Manifest` tragen `—`. Die Werte selbst decken sich Zeile für Zeile mit der Tabelle „Jede
Größe ohne Datenanker" in `spiel.md` (15 Sektorpreise und 2 Weltpreise auf Index 10.000,
alles Übrige auf 0) — dass die Indexklassen 5 und 6 auf 10.000 starten und nicht auf 0,
ist genau die Stelle, an der ein Einheitenfehler unsichtbar bliebe, und sie stimmt.

### 4. Nach Klasse: 3 + 71 + 36 + 22 + 22 + 5 + 5 + 25 + 32 + 4 + 83 + 2

```
grep -P '^\| *[0-9]+ \| `' <datei> | grep -oP '^\|[^|]*\|[^|]*\|[^|]*\|[^|]*\| *\K[0-9]+' | sort -n | uniq -c
```

| K | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 |
|---|--:|--:|--:|--:|--:|--:|--:|--:|--:|--:|--:|--:|
| gezählt | 3 | 71 | 36 | 22 | 22 | 5 | 5 | 25 | 32 | 4 | 83 | 2 |
| T49 | 3 | 71 | 36 | 22 | 22 | 5 | 5 | 25 | 32 | 4 | 83 | 2 |

Zwölf Klassen, jede Zeile trägt genau eine (die Spalte ist in allen 310 Zeilen mit einer
Zahl belegt, sonst wäre der Schnitt nicht auf 310 gekommen).

**Je spielbarem Land und für die Restwelt**, einzeln geschnitten, weil auch das die
Gesamtsumme nicht erzwingt:

| Gebiet | K2 | K3 | K4 | K5 | K6 | K7 | K8 | K9 | K10 | K11 | Summe |
|---|--:|--:|--:|--:|--:|--:|--:|--:|--:|--:|--:|
| US | 6 | 7 | 2 | 4 | 1 | 1 | 5 | 8 | 1 | 9 | **44** |
| CN | 6 | 7 | 2 | 4 | 1 | 1 | 5 | 8 | 1 | 9 | **44** |
| DE + BR | 12 | 14 | 4 | 8 | 2 | 2 | 10 | 16 | 2 | 18 | **88** |
| Restwelt | 6 | 4 | — | 4 | 1 | 1 | 5 | — | — | 1 | **22** |

Deckungsgleich mit der Tabelle „Je spielbarem Land" in T49 (`6 + 5 + 4 + 1 + 7 + 1 + 2 +
8 + 1 + 9 = 44`) und mit deren Restweltzeile. **Erfüllt.**

### 5. Die Einheitenprobe — jeder Datenanker gegen Dimension und Modelleinheit seiner Reihe

Das prüft keine der vier Zählungen, und es ist die Stelle, an der meine Rolle
erfahrungsgemäß etwas findet. `grep -oP 'Datenanker\(\K[^)]+' <datei> | sort | uniq -c`
gegen die Reihenliste in `technik.md` Abschnitt 7:

| Reihe | gezählt | Dimension laut Liste | Modelleinheit | zugewiesene Klasse | passt |
|---|--:|---|---|--:|---|
| 1 × 2 | 15 | (4+RW) × 3 = 15 | Tsd USD × Zehntausendstel | 2 | ja |
| 3 × 2 | 15 | (4+RW) × 3 = 15 | Tsd USD × Zehntausendstel | 2 | ja |
| 4 Produktivität | 5 | 4 + RW | Index (real) | **7** | ja |
| 5 Bevölkerung | 5 | 4 + RW | Personen | 8 | ja |
| 6 Erwerbstätige | 5 | 4 + RW | Personen | 8 | ja |
| 7 Beschäftigung | 15 | (4+RW) × 3 | Personen | 8 | ja |
| 8 Verbraucherpreise | 4 | **4** | bp Jahresrate | 3 | ja |
| 9 Leitzins | 8 | **4**, zwei Adressen je Land | bp | 3 | ja |
| 10 Wechselkurs | 3 | **3** | Index | 6 | ja |
| 11 Staatsschuld | 4 | **4** | bp | 3 | ja |
| 12 Haushaltssaldo | 8 | **4**, zwei Adressen je Land | bp | 3 | ja |
| 13 Zoll | 4 | **4** | bp | 3 | ja |
| 14 Handel | 40 | 5 × 4 × 2 | Tsd USD | 2 | ja |
| 15 Preisniveau | 5 | 4 + RW | Index (nominal) | 5 | ja |

Summe 136. Drei Punkte, die ich einzeln nachgesehen habe, weil sie die klassischen
stillen Fehler sind:

- **Produktivität steht in Klasse 7, nicht in Klasse 5.** T5 nennt genau diesen Fall als
  Grund für die Trennung: Ein brasilianischer Basiswechsel nach T8 teilt die nominalen
  Größen durch 1.000 und senkte eine Produktivität in Klasse 5 um drei Größenordnungen.
  Die Zuordnung ist richtig, und sie ist die einzige der 310, bei der ein falscher Wert
  das Modell plausibel gelassen und trotzdem verdorben hätte.
- **Reihe 9 und Reihe 12 tragen je acht Adressen bei Dimension 4.** Das ist kein doppelter
  Herkunftseintrag, sondern das in T49 beschriebene Adresspaar (`land.<L>.leitzins` /
  `…instrument.leitzins.stand`, ebenso beim Haushaltssaldo) — ein Eintrag auf zwei
  Adressen. T45 verbietet zwei Einträge auf einer Adresse, nicht diesen Fall.
- **`Datenanker(3 × 2)` ist keine Erfindung.** T23 Punkt 1 schreibt die Formel
  `kapitalstock[g][s] = mal_geteilt(kapitalstock_start[g], sektoranteil[g][s], 10.000)` und
  den Eintragsnamen wörtlich hin.

Die elf Adressen, die keine Reihe deckt, sind exakt die elf aus T46 — die Dimensionen
`4` statt `4 + RW` bei den Reihen 8, 9, 11, 12 und `3` bei Reihe 10 lassen genau den
US-Wechselkurs und die fünf Restweltaggregate übrig, dazu die fünf Neubasierungszähler.
Das ist der Kreuztest zwischen Reihenliste und Verzeichnis, und er geht ohne Rest auf.

### 6. Lücken, Lizenz, Reproduzierbarkeit

- **Lücken:** Das Verzeichnis enthält keine Reihenwerte, nur Reihennummern. Es kann daher
  nichts stillschweigend interpolieren; T24 ist hier nicht anwendbar. Geprüft, indem ich
  die Startwertspalte gegen die Herkunftsspalte gehalten habe — kein Startwert steht auf
  einer Zeile, deren Wert aus einer Reihe kommt.
- **Lizenz:** Keine Quelle im Verzeichnis, die nicht über `Datenanker(nr)` auf die
  Reihenliste zeigt; alle vierzehn benutzten Nummern stehen dort und damit in
  `daten.md`. Keine vierzehnte Quelle eingeschleust, keine Reihe zitiert, die es in der
  Liste nicht gibt. Die Auflage, dass die Namensnennung ins Produkt gehört, ist im
  Abschnitt *Namensnennung der Datenquellen* korrekt weitergereicht und nicht als
  erledigt ausgegeben.
- **Reproduzierbarkeit:** Frontmatter trägt `stand: 2026-09-01`. Jede der vier Zählungen
  ist aus der Datei selbst mit einem Aufruf herstellbar; ich habe sie zweimal laufen
  lassen und identische Zahlen bekommen. Die Datei nennt für ihren Befund 2 selbst einen
  Aufruf mit dem Ergebnis 177 — nachgerechnet mit
  `grep -cP '^\| *[0-9]+ \| \`[^\`]+\`\* \|' <datei>` → **177**. Die Zahl reproduziert.

---

## Befund 1 — die geprüfte Datei erklärt eine gestrichene Textstelle zur Vorgabe

**Schwere: mittel.** Betrifft nicht das Abnahmekriterium, sondern das, was der
Projektmanager aus der Datei als nächstes Paket ableitet.

Befund 1 der geprüften Datei lautet, `technik.md` T23 Punkt 1 schreibe die Adresse der
Restverzögerung als `…​.rest`, T15/T38/T45 nennten dieselbe Größe „Restverzögerung", und
weil T17 jede Adresse zum Teil der Schnittstellenversion mache, brauche „wer `rest` will"
einen ADR.

**So erzeugt man den Fehler.** Die Stelle im Wortlaut, `technik.md` Zeilen 710–715:

> **Die Vorgabetabelle der Fassung 4 an dieser Stelle ist gestrichen, und das ist kein
> Rückzug, sondern die Vermeidung eines Abbruchs.** Sie führte
> `land.<L>.instrument.<I>.druck` und `…​.rest` mit Startwert 0, je 16 Adressen, weil
> `spiel.md` sie damals nicht führte. […] Ihre Herkunft ist ab sofort `Entwurf`.

Der Satz steht im Imperfekt und beschreibt eine Tabelle, die im vorangehenden Halbsatz
für **gestrichen** erklärt wird. Und es ist die einzige Fundstelle im ganzen Spec-Bestand:

```
grep -rn '`[a-z.<>I]*\.druck`\|instrument\.[a-zA-Z<>]*\.druck\|\.gegendruck' specs/0016-…/
→ genau ein Treffer: technik.md:712
```

Damit ist Befund 1 als Zeichenfund richtig und als Schluss falsch. Es gibt keine **zwei**
Vorgaben, die denselben Adressteil verschieden schreiben — es gibt eine gestrichene und
sonst keine. Kein lebender Text schreibt den letzten Bestandteil dieser Adressen
überhaupt hin; `restverzoegerung` ist deshalb eine frei gebildete Adresse wie 176 andere
und **kein Konflikt, der eine Entscheidung erzwingt.**

**Warum das zählt:** So wie der Befund dasteht, führt er auf ein Paket „ADR über
`rest` gegen `restverzoegerung`", das gegen eine Vorgabe entscheiden würde, die es nicht
mehr gibt. Der Aufwand ist klein, die Falschmeldung im Bestand ist es nicht — der nächste
Leser hat dieselbe Stelle noch einmal zu prüfen.

Zu korrigieren ist die *Begründung* in der Datei, nicht die Adresse: `restverzoegerung`
bleibt so oder so richtig.

## Befund 2 — dieselbe gestrichene Stelle wird an `druck` genau umgekehrt angewandt

**Schwere: gering.** Folgt aus Befund 1 und ist der Nachweis, dass er kein Wortklauben ist.

Die Datei markiert eine Adresse mit `*`, wenn sie „in keinem Dokument wörtlich" steht.
Danach sind markiert:

| Adressgruppe | Zeilen | markiert | einzige literale Fundstelle |
|---|--:|---|---|
| `…instrument.<i>.stand` | 16 | nein | T17 (`land.BR.instrument.zoll.stand`), **lebend** |
| `…instrument.<i>.druck` | 16 | **nein** | technik.md:712, **gestrichen** |
| `…instrument.<i>.gegendruck` | 16 | ja | keine |
| `…instrument.<i>.restverzoegerung` | 16 | ja | keine |

`druck` bleibt unmarkiert, weil die Datei Zeile 712 als Beleg akzeptiert; im selben Atemzug
verwirft ihr Befund 1 dieselbe Zeile als Vorgabe. Beides zugleich geht nicht. Entweder
zählt die Stelle — dann ist `restverzoegerung` tatsächlich eine Umbenennung und Befund 1
ist ein echter Konflikt —, oder sie zählt nicht — dann sind die 16 `druck`-Zeilen
ebenfalls gebildet und die Zahl 177 müsste 193 lauten.

**So erzeugt man ihn:** die vier Zeilen 67–70 der Datei nebeneinanderlegen (`stand`
unmarkiert, `druck` unmarkiert, `gegendruck`\*, `restverzoegerung`\*) und für jede den
obigen `grep` über `specs/` laufen lassen. Für `stand` kommt ein lebender Treffer, für
`druck` derselbe gestrichene wie für `rest`, für die beiden anderen keiner.

**Warum es das Urteil nicht kippt:** Die Marke ist ein Hinweis für mich, keine Spalte des
Abnahmekriteriums. Sie hat ihren Zweck erfüllt — ich habe die gebildeten Adressen
gefunden, und zwar auch die falsch unmarkierten. Adresse, Gruppe (`Instrumente`), Herkunft
(`Entwurf`) und Klasse (9) der sechzehn Zeilen sind unabhängig davon richtig, und keine
der vier Summen hängt an der Marke.

---

## Geprüft und nicht gezählt

Damit sichtbar ist, wo ich hingesehen habe, ohne etwas zu finden:

- **Doppelte Adressen über Präfixgrenzen** (`land.US.leitzins` gegen
  `land.US.instrument.leitzins.stand`): keine Kollision, `sort | uniq -d` leer über alle
  310. Die Behauptung der Datei, verschiedene Präfixe schlössen Überschneidung aus,
  stimmt zwar, ist aber kein Beweis — der `uniq -d` ist einer.
- **Handelsblock auf Selbstpaare** (`handel.US.US.1`): kommt nicht vor, 40 Zeilen über
  5 × 4 Gebietspaare × 2 handelbare Sektoren.
- **Steckplatz Währung USA**, den T16 dauerhaft leer lässt: als Adresse vorhanden
  (Zeile 275), wie T16 es verlangt — die Adresse existiert, die Möglichkeit nicht.
- **`landespreis`**: hat nach T15 und T39 bewusst keine Zeile und hat auch keine.
  `grep -c landespreis <datei>` → 0. Das war eine Kandidatenstelle, weil ein
  Bauagent hier leicht eine 311. Adresse erzeugt hätte.
- **Klasse 12 und Arithmetikverbot**: `partie.jahrgang_id` und
  `partie.parameter_pruefsumme` sind die einzigen zwei Zeilen in Klasse 12 und tragen
  keinen Startwert, sondern `Manifest` beziehungsweise `Parameter` — richtig, ein
  Startwert 0 wäre hier nach T5 ein Bitmuster mit Größenbedeutung gewesen.
- **Positions- und Beteiligungssektoren**: drei Sektoren, nicht zwei. Sah zunächst nach
  einem Fehler aus, weil nur die Sektoren 1 und 2 handelbar sind — T15 führt beide Gruppen
  aber ausdrücklich über 12 Land×Sektor. Kein Befund.
- **Der Widerspruch zwischen `gebiet.<G>.basiswechsel` (T46) und `land.<L>.basiswechsel`
  (Datei)**: Die Datei bildet vier `land.`-Adressen und eine `restwelt.`-Adresse und
  markiert die vier. T46 selbst benutzt in seiner Grundspalte `restwelt.`-Präfixe, T45 das
  Beispiel `restwelt.basiswechsel`; ein durchgehendes `gebiet.`-Präfix gibt es in keinem
  Dokument. Die Bildung ist damit die einzige, die zu beiden lebenden Stellen passt — kein
  Befund, aber der Grund, warum ich Befund 1 überhaupt nachgegangen bin.

## Was ich dem Projektmanager empfehle

Ein Paket, klein, an den Datenbauer: die Begründung von Befund 1 der Datei auf den
Wortlaut von `technik.md` Zeile 710 korrigieren und die Markierung der 16 `druck`-Zeilen
nach derselben Regel nachziehen wie bei `gegendruck`. Das ändert eine Textpassage und
sechzehn Sternchen, keine Adresse und keine Summe. **Kein ADR erforderlich** — genau das
ist der Punkt von Befund 1.
