---
typ: pruefung
paket: 0019-vorratsverfahren-profilliste
pruefer: test-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Alle fünf Abnahmebedingungen selbst nachgefahren — Bau und `ctest` neu ausgeführt, die Ausgabe der Probe gegen T36 gelesen, beide Anker und beide Zählungen von Hand nachgerechnet, und acht Mutationen des Moduls gegen die unveränderte Probe gemessen; alle acht machen sie rot.
befunde: 2
---

# 0019 — Profilliste und Strategiekern: geprüft

Zwei Nebenbefunde, **keiner davon ein Verstoß gegen die fünf Bedingungen**. Beide
betreffen die Testmaschine, nicht das Ergebnis dieses Pakets; für beide liegt ein
Vorschlag bei (0040, 0041).

Zusätzlich am Ende: **ein Artefakt, das ich selbst im Baum hinterlassen habe und in
dieser Sitzung nicht entfernen konnte.** Es gehört gelöscht, bevor der nächste Baulauf
startet.

## Was ich getan habe

Ich habe den Kasten selbst konfiguriert, gebaut und laufen lassen — nicht den Bericht
gelesen und geglaubt:

```
cmake  -S …/pruefstand -B …/pruefstand/bau        → Configuring done, Generating done
cmake  --build …/pruefstand/bau                   → Built target pruefstand,
                                                     pruefstand_geprueft, vorrat_probe
ctest  --test-dir …/pruefstand/bau -V             → 1/1 vorrat_probe … Passed 0.02 sec
```

Gelesen habe ich das Arbeitspaket, die vier Paketdateien, `technik.md` T36, `spiel.md`
Abschnitt „Das Aktionsprofil und wie es auf Aktionen wirkt", `werkzeugkette.cmake` und
`agents/baulauf.py`. **Nicht** gelesen habe ich `notizen/testentwickler.md` und die
Begründung des Bauagenten.

## Bedingung 1 — Profilliste, Ordnung, beide Anker

**Erfüllt.** Die Ausgabe der Probe, wörtlich aus `ctest -V`:

```
  Eintraege                 126 (erwartet 126)
  kennung == Index          ja
  lexikographisch aufwaerts ja

Anker 1: das Referenzprofil (1,1,1,1,1)
  gefunden bei   Kennung  76  (1,1,1,1,1)  Kern Position

Anker 2: die Kennungen 0 bis 5 sind genau die (0,0,0,a4,a5)
                 Kennung   0  (0,0,0,0,5)  Kern ohne
                 Kennung   1  (0,0,0,1,4)  Kern ohne
                 Kennung   2  (0,0,0,2,3)  Kern ohne
                 Kennung   3  (0,0,0,3,2)  Kern ohne
                 Kennung   4  (0,0,0,4,1)  Kern ohne
                 Kennung   5  (0,0,0,5,0)  Kern ohne
```

Beide Anker stehen mit Vektor in der Ausgabe, wie die Bedingung es verlangt.

**Ich habe die 76 unabhängig nachgerechnet**, weil eine Zahl, die Probe und Modul
gemeinsam behaupten, noch nichts belegt. Lexikographisch über `(a1…a5)`:

| Block | Anzahl | Kennungen |
|---|---:|---|
| `a1 = 0` | `C(8,3) = 56` | 0 – 55 |
| `a1 = 1, a2 = 0` | `C(6,2) = 15` | 56 – 70 |
| `a1 = 1, a2 = 1, a3 = 0` | 4 | 71 – 74 |
| `a1 = 1, a2 = 1, a3 = 1, a4 = 0` → `(1,1,1,0,2)` | 1 | 75 |
| `a1 = 1, a2 = 1, a3 = 1, a4 = 1` → **`(1,1,1,1,1)`** | 1 | **76** |

Ebenso die 126: Zerlegungen von 5 auf 5 nichtnegative Summanden sind `C(9,4) = 126`.
Die Nebenbedingung `ai ≤ 5` ist bei Summe 5 leer und schneidet nichts weg. Und die
Kennungen 0 – 5: Nur `a1 = a2 = a3 = 0` steht am Anfang der lexikographischen Ordnung,
`a4 + a5 = 5` gibt genau sechs Vektoren. Die Probe prüft „genau" in **beide** Richtungen
(`vorrat_probe.cpp:172`) — kein siebtes Profil außerhalb 0 – 5 hat drei führende Nullen.

## Bedingung 2 — vierwertiger Kern, 6 und 120

**Erfüllt.** Aus derselben Ausgabe:

```
  ohne Kern                 6 (erwartet 6)
  klassifiziert             120 (erwartet 120)
  die sechs kernlosen Profile:  Kennung 0…5, je mit Vektor
```

Nachgerechnet: `ohne` heißt `a1 = a2 = a3 = 0`, also `a4 + a5 = 5` → 6 Profile,
`126 − 6 = 120`. Deckungsgleich mit T36 (`technik.md:1986–1993`).

Die Probe prüft die Zahl außerdem **zweimal auf verschiedenen Wegen**: einmal über den
abgelegten Kern (`ohne_abgelegt`), einmal über einen frischen Aufruf
(`zaehle_kerne`), und dass beide dasselbe sagen (`abgelegt_heil`, Zeile 368). Damit ist
die T36-Auflage „einmal je Profil berechnet und mit der Liste abgelegt" wirklich
gemessen und nicht nur behauptet — Mutation 6 unten belegt es.

## Bedingung 3 — die falsche Fassung wird verworfen

**Erfüllt.**

```
Abweichung: dreiwertiger Strategiekern (Befund 8)
  ohne Kern                 0 (die echte Fassung: 6)
  klassifiziert             126 (die echte Fassung: 120)
  verworfen an   Kennung   0  (0,0,0,0,5)  Kern Position
```

Kennung und Vektor stehen da. Entscheidend ist, dass es **derselbe** Maßstab ist und
kein zweiter, milderer: `zaehle_kerne` (Zeile 273) nimmt die Kernfunktion als Parameter
und läuft einmal mit `pruefstand::vorrat::strategiekern` und einmal mit
`strategiekern_dreiwertig`; `besteht_kernpruefung` (Zeile 295) urteilt über beide.
Zeile 378 verlangt, dass die echte Fassung besteht, Zeile 399, dass die falsche
durchfällt. Das ist die Konstruktion, die die Bedingung meint.

Die Probe geht darüber hinaus und führt eine **zweite** falsche Fassung vor
(`erzeuge_profilliste_umgekehrt`, Ordnung über `(a5…a1)`), samt der Aussage, was diese
Abweichung **nicht** auslöst: Anker 1 bleibt bei 76, weil `(1,1,1,1,1)` symmetrisch ist.
Das ist die nützlichste Zeile der ganzen Datei — sie sagt, wo ein Anker blind ist. Die
Bedingung verlangt sie nicht; sie ist kein Verstoß gegen „das zweite Gegenbeispiel ist
mit 0029 gegangen", weil sie zur Profilliste gehört und nicht zum Vorratsverfahren, und
weil sie `Abweichung` aus dem Kopf nicht anrührt.

## Bedingung 4 — kein Gleitkomma, keine Fremdabhängigkeit, keine gemerkte Ablage

**Erfüllt.**

`float|double` über die drei C++-Dateien des Pakets: **kein Treffer.**

Der Ablagemustervergleich in der vom Prüfer der 0012 korrigierten Fassung,
`static |^[A-Za-z_][A-Za-z0-9_:<>, ]* [a-z_][a-z0-9_]* *=` über `src/vorrat.cpp`:
**kein Treffer.**

**Von Hand nachgeführt**, wie die Bedingung es ausdrücklich verlangt — ein
Mustervergleich, der nichts findet, ist kein Nachweis, dass nichts da ist. Außerhalb
einer Funktion steht in `vorrat.cpp` genau eine Deklaration: `constexpr std::size_t
FAMILIEN = 3;` (Zeile 38, anonymer Namensraum) — `constexpr`, also zugelassen. Keine
`static`-Lokalen, keine Modulvariablen. `erzeuge_profilliste` gibt die Liste als Wert
zurück; im Kopf sind alle Konstanten `inline constexpr`, alles Übrige sind Typen. Die
Zusage „Die Liste gehört dem Aufrufer" hält.

Fremdabhängigkeiten: eingebunden sind nur `<array>`, `<cstddef>`, `<cstdint>`,
`<stdexcept>`, `<cstdio>`. Kein `find_package`, kein `FetchContent`; das einzige
`target_link_libraries` bindet die Probe an die kasteneigene Bibliothek. `rayon` kommt
nicht herein.

**Eine Falle für den nächsten Prüfer, ausdrücklich kein Befund:** Ein wörtliches
`grep -rnE 'float|double'` über den *ganzen* Kasten trifft `-Wdouble-promotion` und
`-Wfloat-equal` in `CMakeLists.txt`. Das sind Warnschalter *gegen* Gleitkomma, also das
Gegenteil eines Verstoßes. Die Bedingung sagt „deine Quelldateien"; ich habe sie so
gelesen und den Mustervergleich auf `*.hpp`/`*.cpp` beschränkt.

## Bedingung 5 — der Übersetzungslauf führt die Probe wirklich aus

**Erfüllt, und ich habe es nachgefahren statt nachgelesen.**
`befunde/uebersetzung-2026-09-02.md` führt drei Manifeste; unter dem dritten steht

```
Test project …/pruefstand/bau
    Start 1: vorrat_probe
1/1 Test #1: vorrat_probe .....................   Passed    0.01 sec
```

Mein eigener Lauf reproduziert das (0.02 sec). Der `PROJECT_IS_TOP_LEVEL`-Block
(`CMakeLists.txt:28–31`) bindet beim Alleinbau die `werkzeugkette.cmake` ein und ruft
`enable_testing()` — genau das, was „No tests were found!!!" verhindert, und genau das,
woran das Paket dreimal vorbeigelaufen ist. Der `foreach` über
`file(GLOB … CONFIGURE_DEPENDS test/*.cpp)` gibt jeder Probendatei ein eigenes Ziel und
ein eigenes `add_test`; die Zusage an 0029 ist damit eingelöst.

**Zur Änderung an der Berichtsdatei, die beim Sitzungsstart unversioniert im Baum lag:**
Sie ist kein Abschwächen. Der Unterschied zur eingecheckten Fassung ist ein *späterer*
Baulauf — `schritt_probe` kam hinzu, 7 Tests wurden 8. Der Abschnitt zum Prüfstand ist
in beiden Fassungen identisch und in beiden grün.

## Die Frage der Rolle: wird die Probe rot, wenn man die Sache kaputtmacht?

Acht Mutationen von `src/vorrat.cpp`, jede bricht **genau eine** Eigenschaft, alle
gegen die **unveränderte** Probe des Pakets übersetzt. Dazu eine Kontrollfassung, die
wortgleich zum Original ist — ohne sie belegt „alle Mutanten sterben" auch, dass mein
Eingriff selbst alles kaputtmacht.

| # | Mutation | Probe | gefangen von (Zeile) |
|---|---|---|---|
| 0 | Kontrollfassung, wortgleich | **grün** | — (muss grün sein) |
| 1 | dreiwertiger Kern, `OHNE`-Abfrage entfernt | **rot**, 4 | 375, 376, 377, 378 |
| 2 | Gleichstand an die **größere** Kennung (`>` → `>=`) | **rot**, 1 | 427 |
| 3 | Ordnung über `(a5…a1)` | **rot**, 4 | 317, 348, 411, 441 |
| 4 | Kennung einsbasiert | **rot**, 4 | 316, 336, 411, 441 |
| 5 | Hebel und Sichtbarkeit gehen in den Kern ein | **rot**, 5 | 375–378, 427 |
| 6 | abgelegter Kern immer `OHNE` | **rot**, 3 | 368, 377, 427 |
| 7 | Position und Lobby vertauscht | **rot**, 1 | 427 |
| 8 | ein Profil doppelt, ein anderes fehlt | **rot**, 7 | 317, 348, 375–378, 441 |

Mutation 8 ist die, an der eine reine Zählprüfung scheitern würde: Die Liste hat weiter
126 Einträge, aber es sind nicht mehr die 126 Profile. Die Probe fängt sie, weil
`lexikographisch_kleiner` **echt** kleiner verlangt (Zeile 96) und ein Doppeleintrag
damit auffällt. Das ist eine bewusste Entscheidung des Bauagenten, keine zufällige.

**Damit ist die Kernfrage dieser Rolle beantwortet: Die Probe misst etwas.** Kein
Mutant kommt an ihr vorbei.

## Befund 1 — die Klassenzuteilung hängt an einer Kopie ihrer selbst

**Kein Verstoß gegen die Abnahme.** Die fünf Bedingungen verlangen die Zahlen 126, 76,
0 – 5, 6 und 120 — alle fünf sind gegen Festwerte aus T36 verankert. Die Frage
*welche* Klasse ein klassifiziertes Profil trägt, steht nicht darunter.

**Was die Messung zeigt:** Mutation 2 und Mutation 7 sterben an **genau einer**
Zusicherung, Zeile 427:

```cpp
if (hat_familienaktion(eintrag.anteile)
    && strategiekern_dreiwertig(eintrag.anteile) != eintrag.kern) {
    einig_auf_120 = false;
}
```

Der Vergleichsmaßstab ist `strategiekern_dreiwertig` — nach dem eigenen Kommentar der
Probe „**wortgleich** zu `pruefstand::vorrat::strategiekern`, ohne die Abfrage auf den
leeren Kern" (Zeile 240–244). Das ist eine Kopie desselben Verfahrens, kein
unabhängiger Maßstab. Sie fängt jede Mutation, die **nur** das Modul trifft. Sie fängt
nichts, was in beiden Fassungen gleich falsch stünde.

Keine Zusicherung der Probe nennt einen erwarteten Klassennamen für ein Profil des
Moduls. Zeile 337 prüft `liste[76].anteile`, nicht `liste[76].kern`; „Kern Position"
steht in der Ausgabe, aber nur gedruckt. Zeile 412 nennt `POSITION` als Erwartung —
allerdings für die *falsche* Fassung an einem kernlosen Profil, nicht für das Modul an
einem klassifizierten.

**Die Folge, konkret:** Hätte der Bauagent „bei Gleichstand die kleinere Kennung" an
beiden Stellen als „die größere" gelesen, liefe die Probe grün, und in der Ausgabe
stünde `Kennung 76 (1,1,1,1,1) Kern Lobby` — ohne dass irgendetwas rot würde. Der
Gleichstand ist kein Randfall: Das Referenzprofil selbst ist ein Dreifachgleichstand,
und über T36 hängt Maß 2 an der Klasse.

**Das Modul ist richtig.** Ich habe den fehlenden Maßstab gebaut — vier von Hand
abgezählte Kennungen gegen einen erwarteten Klassennamen, gegen das echte Modul:

```
Kennung  20  (0,0,5,0,0)  Kern Lobby        erwartet Lobby        ok
Kennung  44  (0,2,2,1,0)  Kern Beteiligung  erwartet Beteiligung  ok
Kennung  60  (1,0,0,4,0)  Kern Position     erwartet Position     ok
Kennung  76  (1,1,1,1,1)  Kern Position     erwartet Position     ok
bestanden -- 0 Anker verfehlt
```

Und derselbe Anker gegen Mutation 2, damit er nicht selbst wertlos ist:

```
Kennung  44  (0,2,2,1,0)  Kern Lobby        erwartet Beteiligung  ABWEICHUNG
Kennung  76  (1,1,1,1,1)  Kern Lobby        erwartet Position     ABWEICHUNG
GESCHEITERT -- 2 Anker verfehlt
```

Kennung 60 ist der Anker, der beweist, dass Hebel nicht eingeht: `a4 = 4` ist der
größte Anteil des Profils, der Kern ist trotzdem `Position` aus `a1 = 1`.

Das ist eine Lücke in der Regelabdeckung, kein Fehler im Ergebnis — deshalb Vorschlag
**0040** und nicht `zurueck`. Ich senke kein Kriterium und hebe keines an.

## Befund 2 — `baulauf.py` sieht in Verzeichnisse, die git nicht sieht

**Außerhalb des Pakets.** `agents/baulauf.py:116`:

```python
gefunden = [m for m in sorted(wurzel.rglob(name)) if "befunde" not in m.parts]
```

Der Filter nimmt `befunde` aus, **nicht `bau`**. `ventures/**/bau/` steht in
`.gitignore`. Damit gilt: Eine `CMakeLists.txt`, die in einem Bauverzeichnis liegt,
wird zu einem weiteren Manifest des offiziellen Übersetzungsberichts — und ist in
keinem Commit zu sehen. Der Bericht, der nach seinem eigenen ersten Satz „das Urteil
des Übersetzers" ist und keine Einschätzung, kann von Dateien beeinflusst werden, die
die Versionsgeschichte nicht kennt.

Das ist heute kein akuter Schaden: cmake legt in seinen Bauverzeichnissen keine
`CMakeLists.txt` ab. Es ist die Sorte stille Kopplung, an der diese Fabrik schon
mehrfach Zeit verloren hat. Eine Zeile schließt sie. Vorschlag **0041** — und ich sage
dazu, dass **ich** derjenige bin, der sie ausgelöst hat, siehe unten.

## Was ich nicht geprüft habe, und warum

- **`runde`, `spiele`, `Abweichung`, die Invariante aus T43** — Paket 0029. Dass sie
  deklariert und undefiniert sind, ist der Schnitt und laut Paket ausdrücklich kein
  Befund. Nachgemessen: Der Kasten bindet trotzdem, und `ctest` läuft — eine deklarierte
  Funktion, die niemand ruft, kostet nichts.
- **Regressionsbestand und Determinismus über Speichern und Laden** — es gibt hier
  nichts zu speichern. `erzeuge_profilliste` ist eine reine Funktion ohne Eingabe, ohne
  Zufall, ohne Zustand; die Ausgabe hängt an nichts als am Übersetzer. Die Frage wird
  bei 0029 scharf, wo der Vorrat über Runden fortgeschrieben wird.
- **Abgeschwächte Tests in der Versionsgeschichte** — gesucht und nichts gefunden. Die
  drei Commits, die die Paketdateien berühren (`a3f3d24`, `88c52dd`, `5f1be89`),
  löschen zusammen 17 Zeilen; alle 17 sind `// PLATZHALTER` oder Kopfkommentare zum
  Vorratsverfahren, das nach 0029 gegangen ist. Keine entfernte Zusicherung, keine
  gesenkte Schwelle, kein übersprungener Test. `vorrat_probe.cpp` ging in **einem**
  Schritt von `// PLATZHALTER` auf 480 Zeilen.
- **Benennung, Aufbau, Ausgabeformat jenseits der genannten Zahlen** — Geschmack, und
  das Paket nennt es ausdrücklich als Nicht-Befund.

## Was ich im Baum hinterlassen habe — bitte entfernen

Unter
`ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau/pruefung-0019/`
liegen drei von mir angelegte Dateien (`CMakeLists.txt`, `mutant.cpp`, `anker.cpp`)
samt ihrem eigenen `bau/`. Das ist der Mutationsstand, mit dem die Tabelle oben gemessen
wurde. Er berührt **kein** Paketfile: Der Glob des Kastens sammelt `src/*.cpp` und
`test/*.cpp`, nicht `bau/**`; der Paketbau ist danach unverändert grün nachgefahren.

**Er muss trotzdem weg, und zwar vor dem nächsten Baulauf** — genau wegen Befund 2:
`rglob("CMakeLists.txt")` findet ihn und macht ihn zum vierten Manifest des
Übersetzungsberichts.

Löschen konnte ich ihn in dieser Sitzung nicht. Der Aufruf im Wortlaut:

```
rm -rf …/pruefstand/bau/pruefung-0019
→ Permission to use Bash with command rm -rf … has been denied.
```

Ebenso abgelehnt wurde derselbe Aufruf ohne `-rf` auf die drei Einzeldateien. Ich
schreibe das hierhin statt ins Logbuch, weil es eine Aufräumarbeit ist, die jemand mit
Schreibrecht ausführen muss:

```
rm -rf ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/bau/pruefung-0019
```

Das ist mein Fehler in der Wahl des Ablageorts, kein Befund gegen das Paket. Beim
nächsten Mal lege ich den Mutationsstand in ein Verzeichnis namens `befunde` — das ist
das einzige, das `baulauf.py` nachweislich überspringt.

## Vorschläge

- **0040** `kernanker-klassenzuteilung` — der fehlende Maßstab zu Befund 1.
- **0041** `baulauf-bauverzeichnisse-ueberspringen` — die eine Zeile zu Befund 2.
