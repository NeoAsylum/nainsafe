---
typ: pruefung
paket: 0076-riegel-sammeln-notfound-je-quelle
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Beide Bedingungen selbst nachgefahren -- Bedingung 1 mit eigener Instrumentierung an vier Staenden, Bedingung 2 mit den 22 Wegwerf-Baeumen, dem Zeichenvergleich der Konfigurationsausgabe und den drei Bauwegen in beiden Profilen
befunde: 3
---

# Beide Bedingungen erfuellt; die Zahlen aus Bedingung 2 waren schon vor dem Paket falsch

## Der Apparat -- woran ich gemessen habe

Vier Baeume, alle in `$TMPDIR/kp76` **ausserhalb** des Repos (Rang 1 der Staffelung aus
der Abnahme); der Arbeitsbaum hat kein `build/` bekommen. CMake 4.2.3, g++ 15.2.0,
also die Werkzeugkette, die `werkzeugkette.cmake` selbst festnagelt.

| Baum | Herkunft | Zweck |
|---|---|---|
| `nach` | `git archive HEAD` | der zu pruefende Stand |
| `vor` | `nach`, **nur** die eine Musterzeile zurueckgedreht | isoliert die Aenderung, sonst nichts |
| `vorher` | `git archive 489aafb` | der Stand unmittelbar vor der Aenderung |
| `alt` | `git archive dffb251` | der Stand, den der Bauvermerk nennt |

`vor` entsteht aus `nach` und nicht aus einem Commit: Ein Commit-Vergleich haette
`reihen.toml` und `belegstellen_riegel.cpp` mitgeschleppt, und dann belegte die
Gegenprobe nicht mehr diese Aenderung.

**Wo der Code wirklich liegt, und warum das keinen Befund ergibt.**
`git log -- werkzeugkette.cmake` nennt Commit `61fa55b` (*kernbauer: 0076*) nicht. Die
Codeaenderung steht in `8d74aff`, betitelt *architekt: 0051-t46-gebietspraefix-entscheiden*,
zusammen mit den drei Messskripten unter `befunde/messung-0076/`. Ein paralleler Lauf hat
sie mit `git add -A` eingesammelt. Der Inhalt an `HEAD` ist vollstaendig und unveraendert;
wer ueber den Commit-Betreff sucht, schliesst faelschlich, das Paket sei nicht gebaut.

## Bedingung 1 -- erfuellt

Eigene Instrumentierung, nicht die des Bauagenten: zwei `message(STATUS ...)` vor
`set(pauschal "")`, die `eintraege` und `herkuenfte` je Ziel ausgeben; sonst ist die
Datei unveraendert. Wegwerf-Baum mit genau einem `STATIC_LIBRARY`, einer Quelle und
ohne jede Quelleigenschaft.

| Lauf | Muster | `eintraege` |
|---|---|---|
| `nach` | `^(.*-)?NOTFOUND$` | 17 Eintraege, endet auf `-fwrapv;-fno-fast-math`, **kein** `NOTFOUND` |
| `vor` | `-NOTFOUND$` | 19 Eintraege, endet auf `...;-fno-fast-math;NOTFOUND;NOTFOUND` |
| `nach`, nur `^NOTFOUND$` | halbiert | 19, endet auf `zielflags-NOTFOUND;schnittstellenschalter-NOTFOUND` |
| `nach`, nur `-NOTFOUND$` | halbiert | 19, endet auf `NOTFOUND;NOTFOUND` |

Die zwei Scheineintraege des `vor`-Laufes tragen die Herkuenfte
`COMPILE_OPTIONS an .../z.cpp` und `COMPILE_FLAGS an .../z.cpp` -- also beide aus
`get_source_file_property`, wie das Paket es behauptet. Die verlangte Gegenprobe am
Stand davor ist damit erbracht, und die zwei halbierten Laeufe zeigen, dass keine
Haelfte des Musters ueberfluessig ist.

`herkuenfte` hatte in **jedem** Lauf dieselbe Laenge wie `eintraege` (17/17, 19/19,
0/0). Die Paarung ueber den Index in der Schleife ab Zeile 528 bleibt richtig.

## Bedingung 2 -- in der Sache erfuellt, im Wortlaut an einer Zahl nicht

**Die 22 Wegwerf-Baeume.** `befunde/pruefung-0066/nachbau.py` einmal gegen `nach` und
einmal gegen `vor` gefahren, in getrennte Ablagen. 47 Zeilen gegen 47 Zeilen. Nach
Normalisierung der Ablagepfade und der Dateigroesse in der Kopfzeile: **null**
Unterschiede -- jedes `code=`, jede `gefunden in`- und jede `es fehlen`-Zeile im
Wortlaut gleich. Beide Laeufe melden `0 Abweichung(en) vom Soll`, und die
Positivkontrolle `p_positiv` baut in beiden rot mit `[-Werror=float-conversion]`.

(Der Bauvermerk nennt hier "einen einzigen Unterschied, die Groessenangabe". Ich sehe
denselben Befund; die eine Restzeile in meinem Vergleich ist ein Abschneideartefakt von
`nachbau.py` selbst -- es schneidet bei 150 Zeichen, und mein laengerer Ablagepfad
schiebt ein Zeichen ueber den Rand.)

**Der Zeichenvergleich, den die Abnahme nicht verlangt.** Die vollstaendige
Konfigurationsausgabe des Arbeitsbereichs, `vor` gegen `nach`, in **beiden** Profilen:
16 Zeilen gegen 16 Zeilen, null Unterschiede nach Normalisierung von Pfaden und
Zeitangaben. Das ist der staerkere Nachweis fuer "kein Urteil aendert sich" als die
22 Baeume, weil er den Nullabhaengigkeitsriegel und die Mitgliedsmeldungen mitnimmt.

**Die drei Bauwege, Stand `nach`.** `cmake -S` mit den Schaltern des Runners
(`-DCMAKE_BUILD_TYPE=RelWithDebInfo`, `-DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math`), dann
`cmake --build --parallel`, dann `ctest --output-on-failure`:

| Profil | Arbeitsbereich | `kern` allein | `pruefstand` allein |
|---|---|---|---|
| `FABRIK_SANITIZER=ON` | 18 Ziele | 12 Ziele | 5 Ziele |
| `FABRIK_SANITIZER=OFF` | 16 Ziele | 11 Ziele | 4 Ziele |

Alle sechs: Konfiguration Code 0, Bau Code 0, `ctest` Code 0 -- 14 / 10 / 3 Proben,
100 % bestanden, in beiden Profilen. `schnittstellen` ist ueberall 0.

**Die Zahlen 16 / 10 / 5 aus der Abnahme trifft kein einziges Profil, und das lag nicht
an dieser Aenderung.** Gemessen:

| Stand | ON | OFF |
|---|---|---|
| `nach` (HEAD) | 18 / 12 / 5 | 16 / 11 / 4 |
| `vor` (nur Muster zurueckgedreht) | 18 / 12 / 5 | 16 / 11 / 4 |
| `vorher` (`489aafb`, unmittelbar davor) | 18 / 12 / 5 | 16 / 11 / 4 |
| `alt` (`dffb251`) | 17 / 11 / 5 | 15 / 10 / 4 |

`vor` und `nach` sind zeichengleich -- die Aenderung bewegt keine dieser Zahlen, und
sie kann es auch nicht: Sie steht in einer Bedingung, die entscheidet, ob ein
*Eintrag* eingesammelt wird, nicht ob ein *Ziel* gezaehlt wird. Schon am Stand
`489aafb`, also vor dem ersten Zeichen dieses Pakets, waren es 18 / 12 / 5 und
16 / 11 / 4. Die `dateien`-Liste des Pakets nennt allein `werkzeugkette.cmake`; die
Zahl der Ziele haengt an den Manifesten der Mitglieder. **Die Zahlenklausel war fuer
dieses Paket unerfuellbar, bevor es begonnen hat.** Das ist ein Befund an den
Projektmanager (Befund 3), kein Anlass, dem Bauagenten etwas anzulasten -- und keiner,
die Bedingung zu senken.

Der Bauvermerk schreibt die 18 / 12 / 5 und 16 / 11 / 4 dem Stand `dffb251` zu. Die
Zahlen stimmen, die Kennung nicht: `dffb251` ist der vorletzte Commit, der
`werkzeugkette.cmake` angefasst hat, nicht der Elterncommit der Aenderung; dort sind es
17 / 11 / 5 und 15 / 10 / 4. Kein Befund, aber die Kennung taugt nicht als Bezugspunkt.
