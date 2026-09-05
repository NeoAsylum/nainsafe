---
typ: pruefung
paket: 0052-festkomma-mal-mit-waechter
pruefer: kern-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen einzeln mechanisch gemessen -- Suchmuster und Wortlautvergleich gegen technik.md fuer 1, vier Mutationen des eigenen Nachbaus fuer 2, eigener Bau und Lauf in beiden Profilen fuer 3.
befunde: 0
---

# 0052 -- `mal(a, b)` mit Waechter

Geprueft am eigenen Nachbau unter `/tmp/claude-1000/p0052` (Kopie von `kern/` plus
`werkzeugkette.cmake`, Bauverzeichnis ausserhalb des Repos). Der Kern wurde nicht
angefasst.

## Bedingung 1 -- genau eine Zeile, Rueckkehr ueber den Waechter, Zitat ohne Zeilennummer

**Das vorgeschriebene Suchmuster, im Wortlaut ausgefuehrt:**

```
$ grep -n "i64 mal(" kern/include/kern/festkomma.hpp
200:constexpr i64 mal(i64 a, i64 b)
```

Genau eine Zeile. Der Rumpf hat zwei Anweisungen, und die zweite ist
`return intern::nach_i64(produkt, "mal: Ergebnis ausserhalb von i64 (T7)");`. Damit
gibt es in `mal` keinen zweiten Weg hinaus: Was nicht ueber 4.1 geht, gibt es nicht.

**Das Zitat ist wortgleich, nicht sinngemaess.** Ich habe den Block aus dem Kopf
(`/// > „Auch eine Multiplikation …führt.“`) gegen `technik.md`, T7, Massnahme 4,
Punkt 3 gelegt, nach Normalisierung von Fettmarken, Gedankenstrich und
Anfuehrungszeichen: **identisch**, Zeichen fuer Zeichen. Der Kommentar nennt die
Fundstelle als „`technik.md`, Anforderung **T7**, Massnahme 4, Punkt 3“ -- Tabellennummer
und Punkt, keine Zeilenangabe.

**Keine Zeilennummer, und das Suchmuster ist geeicht.** Muster
`[A-Za-z_./-]+\.(md|hpp|cpp|txt|cmake|toml):[0-9]+` gegen beide Paketdateien: null
Treffer. Dasselbe Muster gegen `notizen/kern-pruefer.md` und `notizen/lehren.md`: vier
Treffer (`baulauf.py:116`, `schritt_probe.cpp:291`, `lauf.py:434-436`,
`architekt.md:7-14`). Der leere Treffer ist also ein Messwert und kein stummes Muster.

## Bedingung 2 -- der Abbruchfall ist gemessen

**Die beiden Werte, von Hand nachgerechnet** (Bedingung 2 verlangt sie im Befund):

| Groesse | Wert | Verhaeltnis zu `I64_MAX` = 9.223.372.036.854.775.807 |
|---|---|---|
| `MAL_FAKTOR_PASST` = `wurzel(I64_MAX, 2)` | 3.037.000.499 | -- |
| `MAL_PRODUKT_PASST` = 3.037.000.499² | **9.223.372.030.926.249.001** | passt, 5.928.526.806 darunter |
| `MAL_FAKTOR_BRICHT_AB` | 3.037.000.500 | -- |
| dessen Quadrat | **9.223.372.037.000.250.000** | 145.474.193 darueber |

Nachrechnung: 3.037.000.500² = 3.037.000.000² + 2·3.037.000.000·500 + 500² =
9.223.369·10¹² + 3.037.000.000.000 + 250.000 = 9.223.372.037.000.250.000. Davon
2·3.037.000.499 + 1 = 6.074.000.999 abgezogen ergibt 9.223.372.030.926.249.001. Der
Uebersetzer hat dieselbe Zahl unabhaengig genannt (siehe Mutation 4).

**Vier Mutationen des Nachbaus, je eine Zeile geaendert.** Die Kontrolle davor ist
gruen (`festkomma_probe … Passed`, Ausgabe `kern::festkomma -- alle Proben bestanden.`),
sonst waere keiner der roten Laeufe eine Aussage.

| # | Aenderung an `mal` | Ergebnis |
|---|---|---|
| 1 | `intern::nach_i64(produkt, …)` → `static_cast<i64>(produkt)` | rot, 3 Fehler: `KEIN ABBRUCH` Zeile 185, 187, 189 |
| 2 | Waechter nur gegen `I64_MAX`, keine untere Grenze | rot, **genau 1** Fehler: `KEIN ABBRUCH` Zeile 187 |
| 3 | `return a * b;` statt `i128`-Zwischenwert | rot, 3 Fehler: Zeile 185, 187, 189 |
| 4 | Produkt um 1 erhoeht | **Uebersetzungsfehler** Zeile 60 und 62, „the comparison reduces to (9223372030926249002 == 9223372030926249001)“ |

Was die vier zusammen belegen:

- **Mutation 1** ist der Nachweis fuer „**denselben Abbruchweg wie 4.1**“. Genommen wird
  genau der Aufruf von `intern::nach_i64` heraus und sonst nichts -- und genau die drei
  Abbruchproben fallen. Der gefangene `std::domain_error` kommt also aus dem Waechter aus
  4.1 und nicht aus einer zweiten Stelle.
- **Mutation 2** zeigt, dass die untere Grenze eigenstaendig gemessen ist: Bei einem
  einseitigen Waechter faellt ausschliesslich Zeile 187, der negative Fall. Die Zusage der
  Probe („ein Waechter, der nur die obere Grenze kennt, waere die Haelfte“) ist damit
  gemessen und nicht behauptet.
- **Mutation 3** stellt genau die Luecke wieder her, die Massnahme 4.3 schliesst: blanke
  `i64`-Multiplikation, unter `-fwrapv` still umgebrochen. Die Probe faengt sie.
- **Mutation 4** zeigt, dass der `static_assert`-Block der Probe wirklich rechnet, und der
  Uebersetzer nennt dabei den Sollwert 9.223.372.030.926.249.001 -- dieselbe Zahl wie
  meine Handrechnung oben, aus einer anderen Quelle.

**Der Laufzeitweg wird auch unter Optimierung wirklich gegangen.** Mutation 1 noch einmal
mit `-O2 -g -DNDEBUG` (die Schalter, die `werkzeugkette.cmake` fuer den Runner nennt):
wieder rot. `undurchsichtig()` haelt also stand, die Probe misst nicht die
Konstantenfaltung des Uebersetzers.

**Der positive Gegennachweis steht in der Probe selbst**, nicht nur in meiner Kontrolle:
Zeile 167-173 belegt, dass `mal` das groesste passende Produkt in beiden Vorzeichen
zurueckgibt, dazu `mal(I64_MAX, 1)`, `mal(I64_MIN, 1)` und `mal(0, I64_MIN)`. Ein
Waechter, der alles blockiert, waere daran rot.

## Bedingung 3 -- namentlich gruen, die uebrigen Proben ebenfalls

`befunde/uebersetzung-2026-09-04.md` fuehrt `festkomma_probe` in allen drei
Testabschnitten des Kerns namentlich als `Passed` (Arbeitsbereich 1/12, Kern allein 1/8),
`Linking CXX executable festkomma_probe` steht in beiden Bauabschnitten -- also ein
wirkliches Ziel und kein Platzhalter. Die Datei ist um 06:26:56 entstanden, die beiden
Paketdateien um 05:11 und 05:15; der Bericht ist juenger als der Bau.

**Nachgemessen statt geglaubt:** eigener Bau, beide Profile.

- Debug: 8 von 8 Kernproben `Passed`.
- `-O2 -g -DNDEBUG`: 8 von 8 `Passed`, keine zusaetzliche Warnung. (Unter Optimierung
  schaltet g++ Warnungen zu, die im Debug-Profil nie erscheinen -- hier keine.)

Das Testprofil war dabei aktiv: `kern_geprueft` wird gebaut, die Probe linkt sie, also
lief alles unter `-fsanitize=undefined,address` (ADR 0011, Massnahme 2).

## Die vier Fragen meiner Rolle

1. **Determinismus.** Kein Gleitkomma in beiden Dateien (Muster
   `\b(float|double|long double)\b`: null Treffer), keine ungeordnete Menge, kein
   Zeit- oder Adresswert. Der Abbruch traegt einen Zeichenkettenliteral als Grund
   (`festkomma.cpp:22-28`), keine Adresse. `mal` ist eine reine Ganzzahlfunktion.
2. **Rueckkopplungen.** Keine -- `mal` hat keinen Zustand und keine Schleife.
3. **Zustandsausgabe.** `mal` schreibt keinen Zustand. Die Ausgabe der Probe nennt bei
   jedem Fehlschlag Zeilennummer und Ausdruck; das hat in allen vier Mutationen
   gereicht, um den fallenden Fall zu benennen.
4. **Raender.** Ueberlauf oben und unten gemessen (s. o.), `I64_MIN · -1` als der eine
   Fall, in dem ein Produkt zweier gueltiger `i64` genau `2^63` ist, ebenfalls.
   Division kommt nicht vor, also kein Nenner null. Der `i128`-Zwischenwert kann selbst
   nicht ueberlaufen: |a·b| ≤ 2^126 ≈ 8,5·10^37 gegen `I128_MAX` ≈ 1,7·10^38 -- das
   Argument steht im Kopf und stimmt.

## Was ich ausdruecklich **nicht** belegt habe

- **`mal_geteilt` ist kein unabhaengiger Zeuge.** Die Probe stellt `mal(a, b)` gegen
  `mal_geteilt(a, b, 1)`. Beide bilden dasselbe `static_cast<i128>(a) * static_cast<i128>(b)`
  und kehren durch dieselbe `intern::nach_i64` zurueck; ein Fehler *in* `nach_i64` waere
  fuer diesen Vergleich unsichtbar. Der Sollwert haengt deshalb an meiner Handrechnung
  oben und an der Zahl, die der Uebersetzer in Mutation 4 selbst genannt hat -- nicht an
  diesem Vergleich.
- **`erwarte_abbruch` liest den Meldungstext nicht.** Es faengt `std::domain_error` und
  verwirft den Grund. Dass der Abbruch aus 4.1 stammt, folgt bei mir aus Mutation 1 und
  aus dem Rumpf von `mal`, nicht aus der Probe allein. Das ist die Bauart des Helfers aus
  Paket 0004 und keine Entscheidung dieses Pakets.
- **Die Zahl „52 Zeilen“ in `technik.md`, T7**, stimmt heute nicht mehr: Dieselbe
  Zuordnung liefert jetzt **54**. Die beiden neuen Zeilen sind die `i128`-Multiplikation
  in `mal` und eine Kommentarzeile, beide innerhalb `festkomma.hpp`, also in einer
  zugelassenen Art. Ich habe die Zuordnung selbst ausgefuehrt: alle 54 Treffer fallen in
  Adressrechnung auf `Index`/`std::size_t`, vorzeichenlose Rechnung in `zufall.hpp` und
  `pruefsumme.hpp`, `i128` innerhalb `festkomma.hpp`, Fliesstext oder einen
  `static_assert` ueber Ganzzahlliteralen (`schritt.cpp:370`, vom Projektmanager bei der
  Abnahme von 0011 ausdruecklich als „kein Auftrag“ eingeordnet). **Eine fuenfte Art --
  zwei `i64` mit Groessenbedeutung -- kommt heute nicht vor.** Die Zahl im Dokument ist
  ein Messwert vom Tag der Messung und gehoert dem Architekten; sie ist kein Befund an
  0052.

## Zwei Nicht-Befunde, damit sie niemand nachher sucht

- **Das Paket liegt in zwei Commits** (`6bea52a`, Betreff „testentwickler: 0059…“, und
  `8465fda`, Betreff „kernbauer: 0052…“). Der erste bringt den Code, der zweite raeumt
  die Schreibbloecke weg und legt die Gegenprobe des Bauagenten ab. Beide Paketdateien
  sind seit `6bea52a` unveraendert; die einzige Aenderung an
  `aufgaben/0052-…md` ist `status: offen` → `gebaut`, also die Meldung des Runners und
  keine Verschiebung des Kriteriums.
- **Die abgelegte Gegenprobe unter `befunde/messung-0052/` ist inert.** Sie enthaelt
  seit `8465fda` eine eigene `CMakeLists.txt`; `baulauf.py:116` schliesst jeden Pfad mit
  `befunde` aus der Manifestsuche aus, und der Bericht des Tages nennt weiterhin
  `manifeste: 5`. Der Belegstellenriegel laesst `befunde` ebenfalls aus. Ich habe die
  Datei `messung-0052/nachweis.md` **nicht** gelesen -- sie traegt die Begruendung des
  Bauagenten.

## Vorgeschlagene Arbeit

`aufgaben/0074-massnahme-43-mechanisch-erzwingen.md`, `status: vorschlag`. Kurz: `mal`
liegt vor und hat null Aufrufer; die Vorgabe, die seine Benutzung verlangt, hat heute
kein Werkzeug hinter sich, sondern eine von Hand ausgefuehrte Zuordnung. Begruendung im
Paket.
