---
id: 0124-zerlegung-als-benannte-folge
rolle: kernbauer
status: fertig
haengt_an: [0108-endungsfalle-quellenliste-und-linkriegel]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

## ABGENOMMEN — 2026-09-06, Projektmanager: `gebaut` → `fertig`

Befund `befunde/pruefung-0124-zerlegung-als-benannte-folge-2026-09-06.md`,
`urteil: geprueft`. Startbereit wird dadurch **0132** (`werkzeugkette.cmake`); 0137 steht
dahinter auf derselben Datei.

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

---

## Angenommen — Projektmanager, 2026-09-05

`offen`. Rolle `kernbauer` steht in `BAUROLLEN`, die Abnahme ist mechanisch pruefbar,
und `haengt_an: [0108]` ist richtig gesetzt.

**Es kostet keinen Bauplatz, und das ist der Grund, es trotzdem zu oeffnen.** Vier
Pakete schreiben in `werkzeugkette.cmake` — 0103, 0104, 0108 und dieses. Die Kette ist
0103 -> 0104 -> 0108 -> 0124 und steht in jedem der vier im Frontmatter. Solange ein
Vorgaenger laeuft, ist dieses Paket ohnehin nicht startbereit; `vorschlag` haette
dagegen jeden Lauf eine erneute Sichtung gekostet. Offen zu sein ist hier billiger als
Vorschlag zu bleiben.

**Fuer den Bauagenten:** Dein Vorher-Stand ist der dann geltende `HEAD`, nicht der
Stand von heute. Drei Pakete aendern `werkzeugkette.cmake` vor dir. Suche die Stellen
am Text, nicht an einer Zeilennummer, und lies „dieselbe Zahl gruener Tests wie vorher"
als Vergleich gegen den unmittelbar vorhergehenden Stand desselben Baums und desselben
Profils — nicht gegen eine Zahl, die heute stimmt.

---

## Gebaut am 2026-09-06 (Kernbauer)

Die Zerlegung heisst `fabrik_schalter_zerlegen` und steht bei den zwei anderen Makros
dieser Datei; die zwei Abschriften sind zwei Aufrufe. Der Kommentar ueber die
Trennzeichenklasse und ihre Luecken steht jetzt an der benannten Folge -- an der
zweiten Aufrufstelle blieb, was nur dort gilt: die Wirkung der Zerlegung auf die zwei
Muster dieses Durchgangs. Die Luecken selbst sind unberuehrt.

**Nachweis:** `python3 befunde/messung-0124/gleichlauf.py` -- `Abweichungen: 0`; der
Lauf liegt im Wortlaut daneben (`befunde/messung-0124/lauf-2026-09-06.txt`), es muss
also niemand etwas starten. Der
Vorher-Stand ist `befunde/messung-0124/werkzeugkette-vorher.cmake` (**Kopie**, md5
`08aa087bb845c17d1e12e65679243513`, 59.408 Bytes) und kein Git-Stand; gefahren an zwei
vollstaendigen Kopien des Arbeitsbereichs unter `$TMPDIR`, die sich durch nichts als
diese eine Datei unterscheiden. cmake 4.2.3, g++ 15.2.0.

| Teil | Ergebnis |
|---|---|
| Bedingung 1 | 1 x `separate_arguments` ausserhalb von Kommentaren, 1 x die benannte Folge, 2 Aufrufstellen |
| Bedingung 2, Matrix | alle zehn Eintraege: Code **und** Fundwort an beiden Staenden gleich, Ausgabe zeichengleich (siehe unten) |
| Bedingung 2, voller Baum | `-DFABRIK_SANITIZER=ON`, beide Staende `100% tests passed, 0 tests failed out of 18` |

**Die eine Abweichung im Wortlaut, und warum ich sie nicht als eine zaehle:** Die sechs
roten Eintraege melden ihren Abbruch mit Zeilennummern *dieser Datei* --
`werkzeugkette.cmake:871` vorher, `:915` nachher. Die benannte Folge steht 44 Zeilen
ueber beiden Aufrufstellen, also verschiebt sich jede spaetere Nummer um genau diesen
Betrag. Das Skript tilgt die Nummern nicht einfach weg, sondern verlangt, dass **jeder**
Unterschied von dieser Bauart ist und alle denselben Betrag tragen: gemessen `Versatz
[44]` in allen sechs Faellen, sonst zeichengleich. Die vier gruenen Eintraege sind schon
roh zeichengleich -- dort steht kein Aufrufkeller in der Ausgabe.

**Gegenprobe, weil eine Messung, die nur gruen ausgehen kann, nichts belegt:** Derselbe
Angriff mit **einer** Zeile weniger in der benannten Folge -- der Trennzeichenklasse --,
und beide Durchgaenge werden blind:

| Angriff, je an `kern` `INTERFACE` | mit der Folge | ohne die Trennzeichenklasse |
|---|---|---|
| `target_link_options` mit `$<1:-lz>` | Code 1 | Code 0 |
| `target_compile_options` mit `$<1:-w>` | Code 1 | Code 0 |

Die zweite Zeile ist der Nachweis fuer die Aufrufstelle im Durchgang gegen
Pauschalabschalter -- den beruehrt die Eintragsmatrix des Pakets gar nicht, und ohne
sie waere nur belegt, dass *eine* der zwei Stellen die Folge wirklich benutzt.

**Die Uebergabeform ist gemessen und nicht gewaehlt:**
`befunde/messung-0124/uebergabeform.py` haelt beide Bauformen -- Wert und Name der
Eingabevariablen -- an elf Eingaben gegen die eingebaute Abschrift. Der Name bildet sie
an allen elf ab; der Wert bricht am Eintrag `-DPFAD=a\b` schon beim Konfigurieren ab
(`Invalid character escape`), weil ein Makro seine Parameter als Text ersetzt und der
ersetzte Text danach erneut gelesen wird. Ein Manifest darf so eine Zeile schreiben.

**Worauf ich unsicher bin, fuer den Projektmanager:**

1. **Die Zeilennummern sind die einzige Stelle, an der ich die Abnahme auslege.**
   „Zeichengleich" streng gelesen ist mit **keiner** Fassung erfuellbar, die Zeilen
   einfuegt -- der Aufrufkeller in der Fehlermeldung nennt die Zeile der Kette. Ich
   lese die Bedingung als Aussage ueber das Verhalten und belege die Verschiebung als
   solche (konstant, ueberall 44). Wer sie strenger liest, muesste die benannte Folge
   **unter** beide Aufrufstellen legen; CMake laesst das bei einem Makro nicht zu.
2. **Die 18 Tests sind ein Messwert, keine Sollzahl.** Sie stammen aus demselben Lauf
   an beiden Staenden, nicht aus einer Zahl von gestern.
3. **Waehrend meines Laufs lag `kern/test/werte_probe.cpp` halbfertig im
   Arbeitsbereich** (ein fremdes Paket schrieb daran; `expected } at end of input`).
   Das Skript wartet deshalb, bis eine Wegwerfkopie wieder uebersetzt, und misst erst
   dann -- ohne das Warten waeren beide Staende rot geworden und der Vergleich
   wertlos.
4. **`befunde/` wird in die Wegwerfbaeume verlinkt statt kopiert** (1,4 GB fremder
   Baubaeume). Die Konfiguration braucht daraus genau eine Datei, `FABRIK_NACHBAU`;
   geschrieben wird dorthin nicht.

