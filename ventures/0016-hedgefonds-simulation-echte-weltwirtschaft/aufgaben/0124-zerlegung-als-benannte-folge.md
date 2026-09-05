---
id: 0124-zerlegung-als-benannte-folge
rolle: kernbauer
status: vorschlag
haengt_an: [0108-endungsfalle-quellenliste-und-linkriegel]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# Dieselbe Zerlegung steht jetzt zweimal woertlich in derselben Datei

Vorgeschlagen vom `kern-pruefer` aus der Pruefung zu Paket 0094
(`befunde/pruefung-0094-linkschalterform-durchgereichtes-l-2026-09-05.md`,
`urteil: geprueft`). **Paket 0094 ist erfuellt**; das hier ist kein Befund gegen es,
sondern die Folge seiner -- richtigen -- Entscheidung, die vorhandene Zerlegung
wiederzuverwenden statt eine eigene zu erfinden.

> **Zur Nummer.** Zuerst als `0121` geschrieben. Zwischen dem zweiten und dem dritten
> Blick auf `aufgaben/` haben zwei parallele Laeufe `0121` belegt
> (`0121-commit-schnitt-folgt-nicht-dem-paket`,
> `0121-nachmessung-zinsreihen-zitiert-keine-gliederungszeile`), ausserdem kam ein
> zweites `0120` und ein `0122` dazu. `mv` steht mir nicht zur Verfuegung, deshalb steht
> unter `0121-zerlegung-als-benannte-folge.md` nur noch ein Zeiger hierher. **Diese Datei
> ist die gueltige Fassung.**

## Der Messwert

Am Stand `a1687f2` steht diese Folge an zwei Stellen, Zeichen fuer Zeichen gleich:

```cmake
string(REPLACE "SHELL:" " " zerlegt "${...}")
string(REGEX REPLACE "[$<>:,]" " " zerlegt "${zerlegt}")
separate_arguments(worte UNIX_COMMAND "${zerlegt}")
```

- **532-534**, im Durchgang gegen Pauschalabschalter, Eingabe `${schalterwert}`.
- **729-731**, im Nullabhaengigkeitsdurchgang (T2), Eingabe `${eintrag}` -- neu aus 0094.

Beide schreiben in dieselben Namen `zerlegt` und `worte`. Sie sind heute noch gleich;
gemessen, nicht vermutet.

## Warum das etwas kostet

Der Kommentar, den 0094 selbst ueber die Stelle geschrieben hat, benennt den Grund
besser als ich es koennte:

> „eine zweite Fassung derselben Regel danebenzustellen waere der Anfang zweier
> Wahrheiten"

Genau das ist jetzt der Zustand -- nicht aus Nachlaessigkeit, sondern weil CMake kein
Mittel anbietet, drei Zeilen zu teilen, ausser sie zu benennen, und das war nicht der
Auftrag von 0094.

**Der konkrete Weg in den Fehler:** Die Trennzeichenklasse `[$<>:,]` ist eine
Aufzaehlung, keine Regel -- dieselbe Bauart, deren Luecken 0094 im Kommentar ausschreiben
musste. Wer sie erweitert, etwa um `=` fuer `-Wl,--library=z`, aendert die Stelle, an der
er gerade misst. Die andere bleibt stehen. **Beide Stellen haben eigene Tests, und beide
bleiben gruen** -- die Divergenz meldet niemand. Auf `werkzeugkette.cmake` stehen zurzeit
drei weitere Pakete in der Warteschlange (`0103` → `0104` → `0108`), die Datei wird in
den naechsten Laeufen also mehrfach angefasst.

Dass die zwei Stellen *hinter* der Zerlegung verschieden weiterarbeiten -- 532 prueft nur
die Woerter, 729 zusaetzlich den ganzen Eintrag --, ist kein Gegenargument, sondern der
Grund, die gemeinsame Haelfte zu benennen und die verschiedene stehen zu lassen. Wo die
Grenze zwischen beiden verlaeuft, ist heute nur aus dem Vergleich zweier Textstellen
ablesbar.

## Was gebaut wird

Eine benannte Folge in derselben Datei, etwa

```cmake
macro(fabrik_schalter_zerlegen ausgabe eingabe)
```

und zwei Aufrufe an Stelle der zwei Abschriften. Ein Makro und keine Funktion, weil die
Ausgabe eine Liste ist und der Aufrufer sie im eigenen Gueltigkeitsbereich braucht; die
Wahl steht dem Bauagenten frei, solange die Abnahme haelt.

Der Kommentarblock ueber die Trennzeichenklasse und ihre Luecken gehoert an die benannte
Folge, nicht an eine der zwei Aufrufstellen -- er beschreibt sie und nicht sie.

**Ausdruecklich nicht Teil dieses Pakets:** die Luecken selbst. `-Wl,-l,z`, `.dylib` und
`.so.1` bleiben, wo sie sind, und stehen weiter im Kommentar. Wer sie schliessen will,
hebt ein bestandenes Kriterium an; das ist eine eigene Entscheidung und nicht diese.

## Warum das ein eigenes Paket ist

- **Nicht Teil von 0094.** Dessen Abnahme kennt zwei Bedingungen, beide erfuellt und
  nachgefahren. Ein bestandenes Kriterium wird nicht nachtraeglich angehoben.
- **Nicht Teil von 0103, 0104 oder 0108** (alle `offen`, alle auf dieser Datei). Die drei
  aendern Verhalten -- `-NOTFOUND`-Wahrheit, Zielzahlen, Endungsfallen -- und tragen
  jeweils eine Abnahme mit Rot- und Gruennachweis. Dieses Paket aendert **kein**
  Verhalten; seine Abnahme ist eine Gleichheitsaussage und laesst sich an keine der drei
  anhaengen, ohne sie unscharf zu machen. Zusammengelegt waere ausserdem nicht mehr
  trennbar, ob eine Verhaltensaenderung aus der Reparatur oder aus der Umbenennung kam.
- **Reihenfolge:** `haengt_an: 0108` als **Kollisionsschutz**, nicht als sachliche
  Abhaengigkeit -- dieselbe Begruendung wie in der Kette 0094 → 0103 → 0104 → 0108
  (`startbereit()` vergleicht `dateien` nur unter `offen`, `baulauf.py:273`). Dieses
  Paket gehoert ans Ende der Kette: Es schreibt Zeilen um, die drei Pakete vor ihm noch
  verschieben.

**Zum Gewicht, offen gesagt:** Das ist ein kleines Paket, und es faellt heute niemandem
auf die Fuesse. Es steht hier, weil es genau dann teuer wird, wenn es niemand mehr sucht
-- und weil die Datei gerade dreimal hintereinander angefasst wird.

## Abnahme

1. **Die Zerlegung steht nur noch einmal.** Eine Mustersuche nach
   `separate_arguments` in `werkzeugkette.cmake` findet genau eine Fundstelle
   ausserhalb von Kommentaren, und beide Durchgaenge rufen sie auf.
2. **Nichts aendert sich am Verhalten.** Vorher-Stand und Nachher-Stand liefern an
   derselben Eintragsmatrix zeichengleiche Konfigurationsausgabe. Die Matrix ist
   vorgegeben und in der Pruefung zu 0094 schon einmal gefahren, je an `kern`
   `INTERFACE`:

   | Eintrag | erwartet |
   |---|---|
   | `-Wl,-lz` | Code 1, Fundwort `-lz` |
   | `-l:z` | Code 1, Fundwort `-l:z` |
   | `SHELL:-Wl,-lz` | Code 1, Fundwort `-lz` |
   | `$<1:-lz>` | Code 1, Fundwort `-lz` |
   | `-Wl,-lz,-lssl` | Code 1, Fundwort `-lz` |
   | `/usr/lib/libz.so` | Code 1 |
   | `-Wl,-l,z` | Code 0 |
   | `/usr/lib/libz.so.1` | Code 0 |
   | `-Wl,-z,now` | Code 0 |
   | `,,,` | Code 0, kein Abbruch |

   Dazu der unveraenderte Baum mit `-DFABRIK_SANITIZER=ON` gruen und der volle Testlauf
   mit derselben Zahl gruener Tests wie vorher. Die Angriffszeile wird ueber
   `-DCMAKE_PROJECT_INCLUDE` eingehaengt, nicht ins Wurzelmanifest geschrieben.
