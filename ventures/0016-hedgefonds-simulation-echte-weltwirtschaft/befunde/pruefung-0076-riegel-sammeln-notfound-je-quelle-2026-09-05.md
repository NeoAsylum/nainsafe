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

## Befund 1 -- die Begruendung des `^`-Ankers ist falsch, und der Fall, den sie nennt, ist ein stilles Loch

**Der Kommentar ist der erklaerte Gegenstand dieses Pakets.** Er sagt jetzt
(Zeile 277-281):

> Verankert an **beiden** Enden, weil der Nichtwert immer der ganze Wert ist: Eine
> gesetzte Eigenschaft, deren letzter Listeneintrag zufaellig so hiesse, traegt einen
> Schalter und ist keine leere Menge.

Genau dieser Fall gemessen, `nach`-Stand, Wegwerf-Baum mit
`int f(double d){ int i = d; return i; }`:

```cmake
add_library(z STATIC z.cpp)
fabrik_warnsatz_anlegen(z)
set_source_files_properties(z.cpp PROPERTIES COMPILE_FLAGS "-w -DPFAD=x-NOTFOUND")
```

Ergebnis: **Konfiguration Code 0**, Riegel meldet wortgleich `alle mit Warnsatz und
ohne Pauschalabschalter`, **Bau Code 0**, **null Diagnosen**, und auf der
Uebersetzerzeile steht `-w`. Die Kontrolle mit demselben Baum und
`COMPILE_FLAGS "-w -DPFAD=x"` -- also nur ohne die Endung -- bricht ab: Code 1,
`hebt den Satz wieder auf: -w`. Und dieselbe Quelle ohne `-w` baut rot mit einer
Diagnose, die Positivkontrolle steht also.

Die Ursache ist die Zeile, um die es geht. `"${${listenname}}"` ist die **ganze**
Eigenschaft; `-w -DPFAD=x-NOTFOUND` endet auf `-NOTFOUND`, das Muster trifft, und die
Eigenschaft wird als leere Menge verworfen -- mitsamt dem `-w` darin. Der Anker am
Anfang schuetzt nicht davor: `(.*-)?` darf alles davor schlucken, das Semikolon einer
CMake-Liste eingeschlossen.

**Das ist keine Verschlechterung durch dieses Paket.** Derselbe Baum am `vor`-Stand
verhaelt sich zeichengleich; das alte Muster `-NOTFOUND$` trifft dieselbe Zeichenkette.
Neu ist allein der Satz, der den Fall fuer erledigt erklaert -- und das ist wortwoertlich
die Fehlerklasse, gegen die das Paket selbst geschrieben wurde: "ein Kommentar, der
einen Randfall abhakt, ist teurer als gar keiner".

Der Rest des Kommentars stimmt. Nachgemessen an vierzehn Proben mit `cmake -P`, altes
gegen neues Muster gegen CMakes eigene Wahrheitsregel: Die **einzige** Probe, in der
sich alt und neu unterscheiden, ist das blanke `NOTFOUND`. `-DX=fooNOTFOUND` und
`-DX=NOTFOUNDx` trifft keines von beiden, `notfound` keines. Das neue Muster schluckt
also nichts, was das alte durchliess -- ausser dem Fall, um den es geht. Und die
gewollte Abweichung von CMakes Regel bei `0` und `OFF` ist die, die der erste Absatz
desselben Kommentars ausdruecklich begruendet.

## Befund 2 -- derselbe Wert am Ziel erzeugt einen lauten Fehlalarm, drei Zeilen darueber

Nicht in `fabrik_riegel_sammeln`, sondern in Zeile 409-412:

```cmake
get_target_property(schalter ${ziel} COMPILE_OPTIONS)
if(NOT schalter)
  set(schalter "")  # `NOTFOUND` ist hier kein Fehler, sondern die leere Menge.
endif()
```

`if(NOT schalter)` benutzt CMakes Wahrheitsregel, und die faellt fuer **jede**
Zeichenkette auf `-NOTFOUND` falsch aus. Gemessen, `nach`-Stand:

```cmake
add_library(z STATIC z.cpp)
fabrik_warnsatz_anlegen(z)
target_compile_options(z PRIVATE -DPFAD=x-NOTFOUND)
```

Ergebnis: Code 1 mit `es fehlen: -Wall -Wextra -Werror ... -fwrapv -fno-fast-math` --
alle 17 Schalter angeblich fort, obwohl `fabrik_warnsatz_anlegen(z)` sie eine Zeile
vorher angelegt hat und sie vollstaendig in `COMPILE_OPTIONS` stehen. Die Kontrolle mit
`-DPFAD=x` konfiguriert Code 0.

Auch das verhaelt sich am `vor`-Stand gleich, ist also aelter als dieses Paket. Es ist
die harmlosere Haelfte -- ein Fehlalarm ist laut --, gehoert aber zu Befund 1: eine
Wurzel, zwei Wirkungen, dieselbe Datei. Beide zusammen sind Vorschlag 0103.

## Befund 3 -- an den Projektmanager: die Zahlenklausel

Zweierlei, beides oben gemessen:

1. **16 / 10 / 5 gilt fuer keinen heutigen Stand und kein Profil**, und die Zahl der
   Ziele haengt an keiner Datei aus der `dateien`-Liste dieses Pakets. Eine Abnahme, die
   sie verlangt, ist von ihrem Bauagenten nicht erfuellbar.
2. **Ein einzelnes Zahlentripel kann konstruktionsbedingt hoechstens fuer eines der
   beiden Profile gelten**: `kern_geprueft` und `pruefstand_geprueft` entstehen nur unter
   `FABRIK_SANITIZER=ON`, gemessene Differenz 2 / 1 / 1.

Dieselben Zahlen stehen als Messwert im Kommentar von `werkzeugkette.cmake`
(Zeile 787): "Am 2026-09-04 waren es 16 im Arbeitsbereich, 10 im Kern und 5 im
Pruefstand". Von dort sind sie in diese Abnahme gewandert, und von dort wandern sie in
die naechste. Der Vorschlag dazu ist 0104.

## Die vier Fragen meiner Rolle

**1. Determinismus.** Strukturell: In `fabrik_riegel_sammeln` und in der Schleife
darum steht kein Gleitkomma, keine Iteration ueber eine ungeordnete Menge, kein
Zeitwert, keine Adresse und kein Zufall -- nur `list(APPEND)`, `list(GET)` und
`foreach(... IN LISTS ...)`, alles in Reihenfolge. Der Abstieg ist eine
Arbeitsliste mit `list(POP_FRONT)`, also eine feste Breitensuche ueber
`BUILDSYSTEM_TARGETS` und `SUBDIRECTORIES` in Deklarationsreihenfolge. Gemessen:
zweimal aus dem Nichts konfiguriert, 16 gegen 16 Zeilen, null Unterschiede nach
Normalisierung der Bauverzeichnisnamen und der Zeitangaben. Dazu der Profilvergleich
oben, der zeichengleich ausfaellt.

**2. Rueckkopplungen.** Hier gibt es keine Schleife, in der ein Ergebnis auf sich
selbst zurueckwirkt: Das Makro liest Eigenschaften und schreibt in zwei Listen, die
niemand zurueckliest, bevor der Riegel sie am Ende auswertet. Was hier eine Schranke
braucht, ist die **Paarung** der beiden Listen, und die habe ich in jedem Lauf
mitgemessen (siehe Bedingung 1). Auffaellig ist der Gegensatz zu Befund 1: Die
Aenderung verkleinert die eingesammelte Menge, und das ist genau die Richtung, in der
ein Riegel stumpf wird. Deshalb der Positivnachweis in beiden Befunden -- ein Riegel,
der **nichts** einsammelt, sieht in jedem Negativtest gleich aus.

**3. Zustandsausgabe.** Die Frage "laesst sich aus der Ausgabe allein erkennen, ob
richtig gerechnet wurde" ist hier mit **nein** zu beantworten, und das ist der Grund,
warum der Fehler dieses Pakets so lange lebte: Der Riegel meldet die Zahl der Ziele
und die Zahl der Schnittstellenziele, aber nicht, **wie viele Eintraege er gesammelt
und wie viele er als Nichtwert verworfen hat**. Beide Nachweise -- der des Bauagenten
und meiner -- brauchen dafuer eine eingeschobene `message()`. Ich mache daraus keinen
eigenen Vorschlag: Das Paket schliesst "die Meldung umbauen" ausdruecklich aus, und
der Punkt steht als Begruendung in Vorschlag 0101, wo er hingehoert.

**4. Raender.** Die vierzehn Proben aus Befund 1 sind der Randtest des Musters: leere
Zeichenkette (faengt der `STREQUAL`-Test davor), blankes `NOTFOUND`, `-NOTFOUND` ohne
Namen davor, `NOTFOUND` als **erster** statt letzter Listeneintrag (kommt durch, wie
bei CMake selbst), Wortende ohne Bindestrich, Kleinschreibung, `0` und `OFF`. Ein
Ueberlauf, eine Division und eine Rundung gibt es in diesem Code nicht; die einzige
Arithmetik ist `math(EXPR lfd "${lfd} + 1")` ueber die Laenge einer Liste.

## Wonach ich noch gesucht und nichts gefunden habe

- **Ob die Aenderung auf die Nullabhaengigkeitspruefung durchschlaegt.** Zeile 661 und
  682 pruefen weiter mit `MATCHES "-NOTFOUND$"`. Das ist dort **richtig**: Beide lesen
  ausschliesslich `get_target_property`, und die liefert nur die Form mit Bindestrich.
  Der Kommentar daneben ("Wie beim Sammeln oben") ist nach der Aenderung ungenau, aber
  die Bedingung ist es nicht. Kein Befund.
- **Ob eine Herkunft verloren geht, wenn eine Liste verworfen wird.** Nein -- beide
  Listen haengen im selben `if`, sie wachsen oder schweigen gemeinsam. In allen Laeufen
  gleich lang.
- **Ob `nachbau.py` selbst stumpf geworden ist.** Nein: 14 der 22 Baeume melden Code 1
  mit der erwarteten Fundstelle, die Positivkontrolle baut rot.
- **Ob das rote `ergebnis: fehler` in `befunde/uebersetzung-2026-09-05.md` diesem Paket
  gehoert.** Nein. Es faellt in `belegstellen_riegel` an fuenf Abschnittszitaten in
  `daten/reihen.toml` -- Gegenstand von 0078/0079 --, und zwar in einem
  liegengebliebenen Pruefbaum unter `bau/kp0010/quelle/...`. In meinem sauberen Export
  ist derselbe Riegel in beiden Profilen gruen.
- **Benennung, Aufbau, Zeilenumbruch der Bedingung.** Kein Befund; `specs/` schweigt
  dazu.

## Vorschlaege

- `0103-notfound-endung-verdeckt-schalter.md` -- Befund 1 und 2, `rolle: kernbauer`.
- `0104-zielzahlen-je-profil-statt-tripel.md` -- Befund 3, `rolle: projektmanager`.

Beide beanspruchen `werkzeugkette.cmake` und schneiden sich damit untereinander sowie
mit jedem weiteren Paket an dieser Datei. Ich trenne sie trotzdem: 0103 aendert eine
Bedingung im Code, 0104 entscheidet zuerst ueber eine Messgroesse. Die Serialisierung
leistet der Projektmanager.

Die Nummern 0102 und alles darunter waren beim Schreiben schon vergeben -- zwischen
meinem ersten und meinem dritten Blick auf das Verzeichnis kamen 0100 und 0101 dazu.
