---
id: 0185-schlussriegel-profilangabe-ohne-regressionsnachweis
rolle: testentwickler
status: fertig
haengt_an: [0137-riegelmeldung-nennt-ihr-profil]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/pruefung-0066/nachbau.py]
vermerk: ANGENOMMEN 2026-09-06, Projektmanager -- `vorschlag` → `offen`, unveraendert. 0137 ist seit heute fertig, ich habe es in diesem Lauf abgenommen. `befunde/pruefung-0066/nachbau.py` fasst kein anderes offenes oder gebautes Paket an -- du bist die einzige Bahn, die dieser Lauf neu aufmacht, und stehst damit sofort startbereit. Hinweis zur Kennung: Es gibt in diesem Verzeichnis ein zweites `0185-*`, naemlich `0185-standschwaeche-paketkennung-je-commit`. Die Nummer ist doppelt, die `id` nicht -- der Baulauf liest die `id` aus dem Frontmatter und haelt euch sauber auseinander. Kein Umzug noetig, ihr habt nichts miteinander zu tun.
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# Die Profilangabe des Schlussriegels ist da und wird von nichts festgehalten

## Herkunft

Aus der Pruefung von Paket 0137 (2026-09-06, Rolle `kern-pruefer`). Alle Zahlen und
Aufrufe stehen in
`befunde/pruefung-0137-riegelmeldung-nennt-ihr-profil-2026-09-06.md`.

## Der Befund, gefahren und nicht vermutet

Paket 0137 hat die Meldung des Warnsatz-Schlussriegels ihr Profil nennen lassen. Sie tut
es, auf allen drei Bauwegen, und sie ist zweiseitig. **Keine Probe merkt, wenn sie es
wieder aufhoert.**

So ist es gemessen. Der Baum vor Paket 0137 ist selbst der Mutant -- in ihm fehlt die
Angabe, sonst ist er zeichengleich. Beide Baeume aus `git archive aa65c70`, im einen die
Fassung von `werkzeugkette.cmake` aus `5d5e2d6` darueber; `diff -rq` nennt genau diese
eine Datei.

    cmake -S <vorher>  -B <leer> -DFABRIK_SANITIZER=ON
    cmake --build <leer> -j 6
    ctest --test-dir <leer>
    -> 100% tests passed, 0 tests failed out of 18

Am Nachher-Baum steht dieselbe Zeile: `0 tests failed out of 18`. Achtzehn Proben, und
das Verschwinden der Angabe kippt keine einzige.

Der `schlussriegel_nachbau` ist die Probe, die es tun muesste, und er kann es nicht: Er
urteilt in `nachbau.py:184` allein ueber `code != 0` seiner 22 Wegwerf-Baeume und liest
vom Text nur `gefunden in`, `es fehlen:` und `kein einziges uebersetzendes`
(`nachbau.py:151-153`). Der Meldungstext des Riegels kommt darin nicht vor. Ausserhalb
davon wertet ihn nichts aus: `git grep Warnsatz-Schlussriegel` ueber die verwalteten
Dateien findet drei Treffer, alle drei in Kommentaren.

## Warum das mehr ist als eine unbewachte Zeichenkette

**Erstens traegt diese Zeile eine Regel.** Paket 0104 hat in derselben Datei
niedergelegt, dass eine Abnahme die Zielzahl nur gegen den vorhergehenden Stand
**desselben Profils** halten darf. 0137 ist die Einloesung: Ohne die Angabe ist das
Profil aus der Ausgabe nicht zu haben. Bricht die Angabe still, wird die Regel aus 0104
unhaltbar und *sieht gehalten aus* -- schlimmer als gar keine Angabe, weil der naechste
Leser 20 gegen 22 haelt, beide Zeilen `ON` lesen und ein Ziel sucht, das nie fehlte.
Genau diesen Weg beschreibt 0137 in seinem eigenen Rumpf als den teuren.

**Zweitens sieht der Bericht den Fehler von Bauart wegen nicht.** Der Baulauf faehrt nur
`FABRIK_SANITIZER=ON`; in `befunde/uebersetzung-2026-09-06.md` tragen alle sechs
Meldungen dieses Riegels `=ON (wahr)`. Eine fest verdrahtete Angabe `ON (wahr)` waere in
jedem Bericht, den diese Fabrik erzeugt, von der richtigen nicht zu unterscheiden. Der
zweite Wert wird ueberhaupt nur von `bauwege.py` gefahren, und das haengt an keinem
`ctest` und keinem Baulauf -- es laeuft, wenn jemand es von Hand ruft.

**Drittens ist das dieselbe Luecke, die diese Fabrik hier schon einmal geschlossen hat.**
Der Kopf von `werkzeuge/schlussriegel/CMakeLists.txt` sagt es fuer den Riegel selbst:
„Ein Riegel, der nur ueber fehlerfreie Baeume faehrt, kann Fehlalarm zeigen und sonst
nichts -- seine eigene Stumpfheit sieht er nie." Dafuer gibt es seit 0133 den Nachbau.
Fuer die Angabe, die der Riegel ueber sich selbst macht, gibt es ihn nicht.

## Warum ein eigenes Paket

**Keine Abnahmebedingung nennt es.** Bedingung 1 von 0137 verlangt, die Zweiseitigkeit in
jenem Lauf zu *zeigen*, und sie ist gezeigt. Bewacht wird sie nirgends, und ein
Prueferbefund, der einem abgeschlossenen Paket nachtraeglich eine dritte Bedingung
anhaengt, verschiebt dessen Abnahmegrenze -- die Bauart, gegen die sich 0104 entschieden
hat und die 0137 in seinem eigenen Rumpf ablehnt.

**Kein Folgepaket zieht es nach.** Durchgesehen: 0133, 0135 und 0136 halten die beiden
Messskripte und sind alle `fertig`. 0115, 0166 und 0171 klingen benachbart, betreffen
aber den Kopfkommentar von `belegstellen_riegel.cpp` und ein Messskript dazu, nicht den
Schlussriegel. Kein offenes und kein vorgeschlagenes Paket haelt
`befunde/pruefung-0066/nachbau.py`.

**Und es gehoert nicht in dieselbe Datei wie 0137.** Der Riegel ist richtig; was fehlt,
ist die Probe darueber. Das ist die Rolle `testentwickler` und eine andere Datei --
`werkzeugkette.cmake` wird hier nicht angefasst, die Kette der vier Pakete darauf
(0108 → 0124 → 0132 → 0137) waechst also nicht um ein fuenftes Glied.

## Warum in `nachbau.py` und nicht in `bauwege.py`

Beide waeren technisch moeglich, und `bauwege.py` faehrt ohnehin schon beide Profile.
Es haengt aber an keiner Abnahme -- ein Waechter dort liefe nur, wenn ihn jemand ruft,
und das ist genau der Zustand, gegen den 0133 geschrieben war. `nachbau.py` haengt seit
0136 als `schlussriegel_nachbau` in `ctest` und laeuft bei jeder Abnahme mit. Der Preis
ist gemessen und klein: Das Skript kostet heute 4,2 Sekunden kalt fuer 22 Baeume; die
neue Bedingung braucht zwei zusaetzliche Konfigurationen eines einzigen Baums, kein
Uebersetzen und kein Binden.

## Abnahme

1. **Die Probe wird rot, wenn die Angabe bricht -- und zwar an beiden Haelften einzeln.**
   `nachbau.py` konfiguriert einen seiner Baeume zusaetzlich in beiden Profilen und
   prueft die Zeile des Schlussriegels: Sie nennt den Schalter mit dem Wert, mit dem
   konfiguriert wurde, und die beiden Zeilen unterscheiden sich. Der Rotnachweis ist
   ausgefuehrt und abgedruckt, dreimal an drei verschiedenen Bruechen einer
   untergeschobenen Fassung von `werkzeugkette.cmake`: Wahrheitswort fest verdrahtet;
   roher Wert fest verdrahtet; Angabe ganz entfernt. Jeder der drei Laeufe endet mit
   Rueckgabewert ungleich 0, und die Meldung nennt, **welche** Haelfte riss. Die
   untergeschobene Fassung entsteht aus dem Baum, nicht von Hand -- `kette_holen` nimmt
   dafuer schon einen Commit entgegen.
2. **Am unveraenderten Baum aendert sich kein Urteil.** `python3
   befunde/pruefung-0066/nachbau.py` meldet weiterhin `0 Abweichung(en)`, eine gruene
   Positivkontrolle und Rueckgabewert 0; `ctest` meldet in beiden Profilen dieselbe Zahl
   bestandener Proben wie davor, gemessen am selben Baum unmittelbar vor und nach der
   Aenderung, und der Bezugsstand wird genannt. Die Laufzeit von `schlussriegel_nachbau`
   wird vor und nach der Aenderung gemessen und beide Werte hingeschrieben; die
   Zeitgrenze von 600 Sekunden in `werkzeuge/schlussriegel/CMakeLists.txt` bleibt
   unberuehrt.

**Was nicht dazugehoert:** die Meldung selbst anfassen -- sie ist richtig; die 22 Baeume
in beiden Profilen fahren, was die Laufzeit ohne Erkenntnisgewinn verdoppelte; eine
Zielzahl in der Abnahme ausschreiben (Regel aus 0104); `bauwege.py` mit anfassen.

---

# Ergebnis, 2026-09-06

Geaendert ist genau eine Datei, `befunde/pruefung-0066/nachbau.py`.
`werkzeugkette.cmake`, `bauwege.py` und `werkzeuge/schlussriegel/CMakeLists.txt` sind
unberuehrt.

## Was dazugekommen ist

**Die Pruefung.** `profilangabe_pruefen()` konfiguriert **einen** Baum -- `p_positiv`,
den es ohnehin schon gibt -- ein zweites und drittes Mal, mit `-DFABRIK_SANITIZER=ON`
und `=OFF`, in je eine eigene Bauablage neben der bestehenden. Uebersetzt wird dabei
nichts; die Zeile faellt beim Konfigurieren.

Geprueft werden die **zwei Haelften einzeln**, nicht die Zeile als ganze: der rohe Wert
(`FABRIK_SANITIZER=(\S*)`) gegen das, womit konfiguriert wurde, und das Wahrheitswort
(`\((wahr|falsch)\)`) gegen das, was daraus folgt. Eine Zeile als ganze zu vergleichen
sagt einem Leser nicht, **welche** der beiden riss -- und genau das verlangt die Abnahme.

Dazu die dritte Bedingung, dass die beiden Angaben sich unterscheiden. Verglichen wird
der Zeilenkopf bis zum Doppelpunkt statt der ganzen Zeile, und das ist hier das
schaerfere Mass: In diesem winzigen Baum steht kein Sanitizerziel, die drei Zahlen
dahinter sind unter ON und OFF also ohnehin dieselben (`1 / 0 / 17`). Unterscheiden sich
die Zeilen, dann **nur** durch die Angabe.

**Der Rotnachweis als Schalter, nicht als Handgriff.** `--bruch=<name>` laesst
`kette_holen` die geholte Fassung an genau einer Stelle austauschen und alles andere
laufen wie sonst. Die drei Brueche stehen als Wortlaut-Paare in `BRUECHE`; trifft ein
Wortlaut nicht **genau einmal**, bricht der Lauf ab, bevor er misst. Die untergeschobene
Fassung entsteht damit aus dem Baum und nicht von Hand -- wie die Abnahme es verlangt.
Ein Bruch bekommt seine eigene Ablage (`nachbau0066-HEAD-bruch-<name>`), damit er einem
gruenen Lauf daneben nicht in die Bauablagen faehrt. **Ohne** `--bruch` ist der Pfad
zeichengleich der von vorher; die zwei Abnahmen, die ihn nennen (0103, 0108), sehen ihn
unveraendert.

## Abnahme, Bedingung 1 -- der Rotnachweis, dreimal

Alle Laeufe gegen HEAD, Wortlaut gekuerzt auf die neue Zeile. Der Rueckgabewert steht
jeweils darunter.

**a) Wahrheitswort fest verdrahtet** (`set(profilwort "falsch")` → `"wahr"`):

```
$ python3 befunde/pruefung-0066/nachbau.py --bruch=wahrheitswort
   -DON  -- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 1 uebersetzende ...
   -DOFF -- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=OFF (wahr): 1 uebersetzende ...
     !! Haelfte 'Wahrheitswort' unter -DFABRIK_SANITIZER=OFF: die Zeile nennt 'wahr', erwartet ist 'falsch'
0 Abweichung(en) vom Soll.
RC=1
```

**b) Roher Wert fest verdrahtet** (`FABRIK_SANITIZER=${FABRIK_SANITIZER}` → `=ON`):

```
$ python3 befunde/pruefung-0066/nachbau.py --bruch=rohwert
   -DON  -- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 1 uebersetzende ...
   -DOFF -- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (falsch): 1 uebersetzende ...
     !! Haelfte 'roher Wert' unter -DFABRIK_SANITIZER=OFF: die Zeile nennt 'ON', konfiguriert wurde 'OFF'
RC=1
```

**c) Angabe ganz entfernt** (der Wortlaut von vor 0137):

```
$ python3 befunde/pruefung-0066/nachbau.py --bruch=ohne
   -DON  -- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz ...
   -DOFF -- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz ...
     !! Haelfte 'roher Wert' unter -DFABRIK_SANITIZER=ON: die Zeile nennt nichts, konfiguriert wurde 'ON'
     !! Haelfte 'Wahrheitswort' unter -DFABRIK_SANITIZER=ON: die Zeile nennt nichts, erwartet ist 'wahr'
     !! Haelfte 'roher Wert' unter -DFABRIK_SANITIZER=OFF: die Zeile nennt nichts, konfiguriert wurde 'OFF'
     !! Haelfte 'Wahrheitswort' unter -DFABRIK_SANITIZER=OFF: die Zeile nennt nichts, erwartet ist 'falsch'
     !! Beide Haelften zusammen: ON und OFF melden zeichengleich '-- Warnsatz-Schlussriegel' -- die Angabe haengt nicht am Schalter
RC=1
```

Jeder der drei nennt die gerissene Haelfte namentlich; (c) nennt beide und zusaetzlich
die Gleichheit der Zeilen. **Und alle drei melden `0 Abweichung(en) vom Soll`** -- die 22
Baeume bleiben gruen. Das ist der Befund aus 0185 noch einmal gefahren, jetzt mit einer
Probe daneben, die ihn faengt.

**d) Ein vierter, den niemand gebaut hat.** Der Stand vor 0137 traegt die Angabe nicht,
also macht ihn die neue Bedingung ohne jeden Bruch rot:

```
$ python3 befunde/pruefung-0066/nachbau.py 5d5e2d6
   -DOFF -- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, ...
     !! (vier Haelften-Meldungen wie unter c, dazu die Gleichheit)
     (Der Stand 5d5e2d6 liegt vor Paket 0137 oder hat die Angabe sonst nicht. Das ist
      eine Aussage ueber ihn, nicht ueber HEAD.)
RC=1
```

Das ist **eine bewusste Aenderung am Verhalten alter Aufrufe** und im Kopf des Skripts
festgehalten: Die Sollspalte der 22 Baeume zaehlt weiterhin nur an HEAD, die Profilangabe
zaehlt an jedem Stand. Begruendung: Die 22 Urteile duerfen sich mit dem Baum aendern, die
Angabe ist entweder da oder nicht. Wer `nachbau.py 8fff575^` faehrt, bekommt seit heute
1 statt 0 -- mit einer Zeile, die sagt, worueber geurteilt wurde.

**Der Waechter ueber den Bruechen selbst**, denn ein Bruch, der nichts trifft, laesst die
Probe gruen und sieht wie ein Beweis aus:

```
$ python3 befunde/pruefung-0066/nachbau.py 5d5e2d6 --bruch=ohne
Bruch 'ohne': der erwartete Wortlaut kommt 0-mal vor, erwartet ist genau einmal. Die
Kette hat sich geaendert -- der Bruch waere keiner, und ein gruener Lauf belegte nichts.
RC=1
```

Er schlaegt zu, **bevor** ein Baum angelegt ist. Ein unbekannter Name ebenso:
`Unbekannter Bruch 'tippfehler'. Bekannt: ohne, rohwert, wahrheitswort` (RC=1).

## Abnahme, Bedingung 2 -- am unveraenderten Baum aendert sich kein Urteil

**Bezugsstand:** HEAD `6456047` zu Beginn der Messung, `885449e` am Ende. Der Baum ist
waehrenddessen gewandert (zwei fremde Laeufe, `0172` und `0170`), aber
`git log 6456047..885449e -- werkzeugkette.cmake befunde/pruefung-0066/nachbau.py
werkzeuge/schlussriegel/CMakeLists.txt` ist **leer** -- keine der gemessenen Dateien war
darunter. Ausserdem uneingecheckt im Baum: die Arbeit dreier gleichzeitiger Laeufe
(`reihen.toml`, `verlauf.hpp`, `belegstellen_riegel.cpp`, `messung-0172-verlaufskopf/`).

**Der Aufruf von Hand:**

```
$ python3 befunde/pruefung-0066/nachbau.py
   -DON  -- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): ...
   -DOFF -- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=OFF (falsch): ...
     beide Haelften nennen das konfigurierte Profil, und die beiden Angaben unterscheiden sich.

0 Abweichung(en) vom Soll.
RC=0
```

Die Positivkontrolle bleibt gruen (`bau code=2, 1 Fehler`, der erwartete
`-Werror=float-conversion`).

**`ctest`, derselbe Baubaum unmittelbar vor und nach der Aenderung**, beide Profile:

| Baubaum | vorher | nachher |
|---|---|---|
| `-DFABRIK_SANITIZER=ON` | `100% tests passed, 0 tests failed out of 18` | dasselbe |
| `-DFABRIK_SANITIZER=OFF` | `100% tests passed, 0 tests failed out of 18` | dasselbe |

**Laufzeit von `schlussriegel_nachbau`.** Die Zahlen aus der Tabelle oben taugen dafuer
nicht: Der zweite Lauf im selben Baubaum findet die Bauablagen der 22 Baeume warm vor und
misst 0,44 s statt 4,2 s -- er wuerde meine Zusatzkosten nicht bloss klein, sondern
negativ aussehen lassen. Gemessen ist darum kalt gegen kalt, je ein frisch
konfigurierter Baubaum je Profil, am selben Tag auf derselben Maschine:

| | vorher (kalt) | nachher (kalt) |
|---|---|---|
| `-DFABRIK_SANITIZER=ON` | 4,24 s | 4,64 s |
| `-DFABRIK_SANITIZER=OFF` | 4,22 s | 4,76 s |

Rund **+0,4 s** -- die zwei zusaetzlichen Konfigurationen eines Baums mit einer
Quelldatei, wie im Paketrumpf veranschlagt. Die Zeitgrenze `TIMEOUT 600` in
`werkzeuge/schlussriegel/CMakeLists.txt` ist unberuehrt und bleibt das
Hundertzwanzigfache des gemessenen Werts.
