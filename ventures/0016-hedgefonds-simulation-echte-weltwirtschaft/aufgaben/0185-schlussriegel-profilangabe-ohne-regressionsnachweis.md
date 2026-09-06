---
id: 0185-schlussriegel-profilangabe-ohne-regressionsnachweis
rolle: testentwickler
status: offen
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
