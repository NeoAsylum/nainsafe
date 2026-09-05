---
typ: pruefung
paket: 0076-riegel-sammeln-notfound-je-quelle
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Beide Bedingungen ein drittes Mal in eigenen Baeumen gemessen -- Bedingung 1 mit eigener Instrumentierung an vier Musterfassungen, Bedingung 2 mit den 22 Wegwerf-Baeumen, dem Zeichenvergleich der vollstaendigen Konfigurationsausgabe auf drei Bauwegen in beiden Profilen und ctest; dazu der in Vorschlag 0103 empfohlene Bauweg gegen 0103s eigene Abnahme gefahren
befunde: 2
---

# Dritte Runde: Abnahme bestaetigt -- und der Weg, den die Nachfolgevorschlaege empfehlen, erfuellt ihre eigene Abnahme nicht

**Dies ist die dritte Pruefung dieses Pakets am selben Tag.** Die beiden ersten liegen
unter `befunde/pruefung-0076-...-2026-09-05.md` und `...-runde2-2026-09-05.md`, beide
`geprueft`, mit den Vorschlaegen 0103, 0104 und 0108. Ich habe sie gelesen -- sie
stammen von meiner eigenen Rolle -- und **jede Aussage in eigenen Baeumen neu gemessen**
statt sie zu uebernehmen. Sie halten.

Gegenstand dieser Runde ist damit das, was die beiden ersten hinterlassen haben: die
drei Vorschlaege, ihre empfohlenen Bauwege und ihre Ausschluesse. Dort liegen beide
neuen Befunde.

## Der Apparat

`werkzeugkette.cmake` ist seit `8d74aff` unveraendert (`git log -- .../werkzeugkette.cmake`;
`git log -S'^(.*-)?NOTFOUND$'` nennt denselben Commit), und der Arbeitsbaum ist an
dieser Datei sauber. Der gepruefte Stand ist also derselbe wie in Runde 2. CMake 4.2.3,
g++ 15.2.0.

Alle Baeume unter `$TMPDIR/kp76c`, **ausserhalb** des Repos (Rang 1 der Staffelung aus
der Abnahme); der Arbeitsbaum hat kein `build/` bekommen.

| Baum | Herkunft | Zweck |
|---|---|---|
| `nach` | `git archive HEAD` | der zu pruefende Stand |
| `vor` | Kopie von `nach`, **nur die Musterzeile** zurueckgedreht | isoliert die Aenderung |
| `proE` | Kopie von `nach`, `fabrik_riegel_sammeln` auf den in 0103 empfohlenen Weg | Befund 1 |
| `exaktbaum` | Kopie von `nach`, Nichtwert exakt statt als Endung | Gegenprobe zu Befund 1 |

`vor` entsteht aus `nach` und nicht aus einem Commit: Ein Commit-Vergleich schleppt
fremde Pakete mit, und dann belegt die Gegenprobe nicht mehr diese Aenderung. `diff -u`
zeigt genau eine geaenderte Zeile.

## Bedingung 1 -- erfuellt

Eigene Instrumentierung: zwei `message(STATUS ...)` vor `set(pauschal "")`, die
`eintraege`, `herkuenfte` und beide Laengen je Ziel ausgeben; sonst unveraendert.
Wegwerf-Baum mit genau einem `STATIC_LIBRARY`, einer Quelle, ohne jede
Quelleigenschaft.

| Lauf | Muster | `eintraege` | n / h |
|---|---|---|---|
| `nach` | `^(.*-)?NOTFOUND$` | 17, endet auf `-fwrapv;-fno-fast-math`, **kein** `NOTFOUND` | 17 / 17 |
| `vor` | `-NOTFOUND$` | 19, endet auf `-fno-fast-math;NOTFOUND;NOTFOUND` | 19 / 19 |
| `nach`, nur `^NOTFOUND$` | halbiert | 19, endet auf `zielflags-NOTFOUND;schnittstellenschalter-NOTFOUND` | 19 / 19 |
| `nach`, nur `-NOTFOUND$` | halbiert | 19, endet auf `NOTFOUND;NOTFOUND` | 19 / 19 |

Die von der Abnahme verlangte Gegenprobe am Stand davor ist damit erbracht.

**Die Sachaussage des Kommentars -- der erklaerte Gegenstand des Pakets -- ist durch die
zwei Halbierungen in beide Richtungen belegt**, und zwar an den `herkuenfte` und nicht
nur an den Werten: Faengt das Muster nur die blanke Form, kommen genau die zwei
**Ziel**abfragen durch (`COMPILE_FLAGS an z`, `INTERFACE_COMPILE_OPTIONS an z`), und sie
heissen `<variablenname>-NOTFOUND`. Faengt es nur die Strichform, kommen genau die zwei
**Quell**abfragen durch (`COMPILE_OPTIONS an .../z.cpp`, `COMPILE_FLAGS an .../z.cpp`),
und sie heissen blank `NOTFOUND`. Der Kommentar ordnet beide Formen richtig zu; keine
Haelfte des Musters ist ueberfluessig.

`herkuenfte` hatte in jedem Lauf dieselbe Laenge wie `eintraege`.

## Bedingung 2 -- in der Sache erfuellt, an der Zahlenklausel nicht erfuellbar

**Die 22 Wegwerf-Baeume**, `befunde/pruefung-0066/nachbau.py` je einmal aus `nach` und
aus `vor` gefahren, in getrennte Ablagen: 47 gegen 47 Zeilen, **alle 40 Markenzeilen**
(`code=`, `gefunden in`, `es fehlen`) paarweise zeichengleich, beide
`0 Abweichung(en) vom Soll`. Positivkontrolle `p_positiv`: Bau Code 2, eine Diagnose --
gruen heisst hier also wirklich gruen. Der einzige Restunterschied im Rohtext ist ein
Abschneideartefakt von `nachbau.py` (150 Zeichen) an unterschiedlich langen Ablagepfaden.

**Zeichenvergleich der vollstaendigen Konfigurationsausgabe**, `vor` gegen `nach`, auf
allen drei Bauwegen in beiden Profilen -- sechs Vergleiche, nach Normalisierung von
Pfaden und Zeitangaben je **null** Unterschiede (16/16, 11/11, 11/11 Zeilen). Das ist
der staerkere Nachweis als die 22 Baeume, weil er den Nullabhaengigkeitsriegel und die
Mitgliedsmeldungen mitnimmt.

**Die drei Bauwege am Stand `nach`**, mit den Schaltern des Runners (`baulauf.py:162`):

| Profil | Arbeitsbereich | `kern` allein | `pruefstand` allein |
|---|---|---|---|
| `FABRIK_SANITIZER=ON` | 18 Ziele | 12 Ziele | 5 Ziele |
| `FABRIK_SANITIZER=OFF` | 16 Ziele | 11 Ziele | 4 Ziele |

Alle sechs: Konfiguration 0, Bau 0, `ctest` 0 -- 14 / 10 / 3 Proben, 100 % bestanden.

**Die Zahlen 16 / 10 / 5 trifft kein Profil**, und `vor` und `nach` sind darin
identisch: Die Zeile entscheidet, ob ein *Eintrag* eingesammelt wird, nicht ob ein
*Ziel* gezaehlt wird. Die Klausel war unerfuellbar, bevor das Paket begonnen hat --
Befund an den Projektmanager, kein `zurueck` und kein Anlass, die Bedingung zu senken.
Sie wird bereits von Vorschlag 0104 getragen, dessen Zahlen ich unabhaengig bestaetige;
ich lege keinen zweiten daneben.

## Befund 1 -- der in 0103 empfohlene Bauweg erfuellt 0103s eigene Abnahmebedingung 1 nicht

Vorschlag 0103 nennt unter *Was zu tun ist*: "Der naheliegende Weg ist, je Listeneintrag
statt ueber die zusammengefuegte Zeichenkette zu entscheiden -- die Schleife darunter
laeuft ohnehin ueber die Eintraege." Vorschlag 0108 uebernimmt denselben Satz fuer seine
Stellen.

Diesen Weg gebaut -- `fabrik_riegel_sammeln` als `foreach` mit dem Test **je Eintrag**,
sonst nichts geaendert -- und gegen 0103s eigene Abnahmebedingung 1 gefahren. Deren Baum
steht im Vorschlag woertlich:

```cmake
add_library(z STATIC z.cpp)
fabrik_warnsatz_anlegen(z)
set_source_files_properties(z.cpp PROPERTIES COMPILE_FLAGS "-w -DPFAD=x-NOTFOUND")
```

| Fassung von `fabrik_riegel_sammeln` | Ergebnis |
|---|---|
| `HEAD` | Code 0 -- der von 0103 gemeldete Fehler |
| **je Listeneintrag (der empfohlene Weg)** | **Code 0 -- unveraendert** |
| Nichtwert exakt statt als Endung | Code 1, `gefunden in: COMPILE_FLAGS an .../z.cpp:  -w` |

Der Kontrollbaum mit `COMPILE_FLAGS "-w -DPFAD=x"` -- also nur ohne die Endung -- bricht
in **allen drei** Fassungen mit Code 1 ab. Die Positivkontrolle steht also, und der
Unterschied haengt allein an der Endung.

**Die Ursache, mit eigener Instrumentierung nachgesehen:**

| Fassung | `eintraege` | letzter Eintrag |
|---|---|---|
| je Listeneintrag | 17 | `-fno-fast-math` -- das `-w` ist fort |
| Nichtwert exakt | 18 | `-w -DPFAD=x-NOTFOUND` -- `separate_arguments` findet daraus `-w` |

`COMPILE_FLAGS` ist eine **Zeichenkette mit Leerzeichen, keine CMake-Liste**. Gemessen
an einem Ziel mit `"-a -b"` in jeder der vier Kombinationen:

```
ziel.COMPILE_FLAGS=[-a -b]     n=1     quelle.COMPILE_FLAGS=[-a -b]     n=1
ziel.COMPILE_OPTIONS=[-a;-b]   n=2     quelle.COMPILE_OPTIONS=[-a;-b]   n=2
```

Von den fuenf eingesammelten Eigenschaften sind damit **zwei Zeichenketten**
(`COMPILE_FLAGS` am Ziel und an der Quelldatei) und drei Listen. Bei den zwei
Zeichenketten ist "je Listeneintrag" wortgleich dasselbe wie "ueber die zusammengefuegte
Zeichenkette" -- der ganze Wert ist der eine Eintrag. Und genau auf einer dieser zwei
Stellen ist 0103s Abnahmebedingung 1 gebaut.

**Abnahmebedingung 3 faengt es nicht.** Die 22 Wegwerf-Baeume aus `nachbau.py`, gegen
den empfohlenen Weg gefahren: alle 40 Markenzeilen zeichengleich mit `HEAD`,
`0 Abweichung(en) vom Soll`, Positivkontrolle rot. Kein einziger der 22 Faelle setzt
einen Nichtwert in eine Zeichenketteneigenschaft; `e4_zweiworte` kommt am naechsten
(`COMPILE_FLAGS "-O0 -w"`) und traegt keine Endung.

**Was daraus folgt und was nicht.** Es ist kein Fehler in 0076 -- die Wirkung liegt ganz
in einem noch nicht gebauten Vorschlag. Aber ein Bauagent, der die Empfehlung befolgt,
faellt an Abnahme 1 durch, und das kostet einen der drei Rueckläufe aus
`RUECKLAUF_MAX`. Der Satz steht in **zwei** Vorschlaegen.

**Der Gegenentwurf ist gemessen und keine Vorgabe.** Der Nichtwert exakt statt als
Endung -- `STREQUAL "NOTFOUND"` oder `STREQUAL "${listenname}-NOTFOUND"`, also genau die
beiden Formen, die die Halbierungen oben belegen -- erfuellt 0103s Abnahme 1, laesst alle
22 Wegwerf-Baeume zeichengleich (`0 Abweichung(en)`) und konfiguriert den Arbeitsbereich
auf allen drei Bauwegen in beiden Profilen mit Code 0 und denselben Zielzahlen 18/12/5
und 16/11/4. Er koppelt allerdings den Variablennamen an die Aufrufstelle; alle fuenf
Aufrufe sind heute konsistent, und wer sie entkoppelt, faellt auf das heutige Verhalten
zurueck, nicht darunter. Der Bauagent darf es anders machen -- der Punkt ist, dass der
empfohlene Weg es nicht tut.

## Befund 2 -- die Wahl, die 0103 dem Bauagenten laesst, hat seine eigene Abnahme 2 schon getroffen

0103 schreibt: "Ob Zeile 409-412 dieselbe Behandlung bekommt oder ihre Sonderbehandlung
ganz verliert, entscheidet der Bauagent." Gemessen an den beiden Baeumen, die 0103s
Abnahmebedingung 2 woertlich nennt, jeweils mit **unveraenderter** Zeile 409-412:

| Baum | 0103 verlangt | `HEAD` | je Listeneintrag | Nichtwert exakt |
|---|---|---|---|---|
| `target_compile_options(z PRIVATE -DPFAD=x-NOTFOUND)` | Code 0 | Code 1, `es fehlen: ...` | Code 1, `es fehlen: ...` | Code 1, `es fehlen: ...` |
| `target_compile_options(z PRIVATE -w -DPFAD=x-NOTFOUND)` | Code 1, `gefunden in: COMPILE_OPTIONS an z` | Code 1, `es fehlen: ...` | Code 1, `es fehlen: ...` | Code 1, `es fehlen: ...` |

Keine Aenderung an `fabrik_riegel_sammeln` allein erreicht die zweite Bedingung:
`if(NOT schalter)` leert `schalter`, bevor der Satzvergleich laeuft, also meldet der
Riegel in allen drei Fassungen die fehlenden 17 Schalter statt den gefundenen
Pauschalabschalter. Ein dritter Ausgang -- Zeile 409-412 stehen lassen -- existiert
nicht. Das ist die harmlosere Haelfte, kostet aber denselben Rueckläufer, wenn der
Bauagent die Freiheit beim Wort nimmt.

## Die vier Fragen meiner Rolle

**1. Determinismus.** Strukturell: kein Gleitkomma, keine ungeordnete Menge, kein
Zeitwert, keine Adresse, kein Zufall -- `list(APPEND)`, `list(GET)` und
`foreach(... IN LISTS ...)` in Reihenfolge, der Abstieg eine Arbeitsliste mit
`list(POP_FRONT)` ueber `BUILDSYSTEM_TARGETS` und `SUBDIRECTORIES` in
Deklarationsreihenfolge. Gemessen: den Arbeitsbereich je Profil **zweimal aus dem
Nichts** konfiguriert -- 16 gegen 16 Zeilen, null Unterschiede in beiden Profilen. Dazu
der Profilvergleich `vor`/`nach` oben, ebenfalls null.

**2. Rueckkopplungen.** Keine Schleife wirkt auf sich selbst zurueck: Das Makro liest
Eigenschaften und schreibt in zwei Listen, die erst am Ende ausgewertet werden. Die
Groesse, die eine Schranke braucht, ist die **Paarung** der beiden Listen -- in jedem
Lauf mitgemessen, immer gleich lang. Die Richtung der Aenderung ist die, in der ein
Riegel stumpf wird (sie sammelt *weniger*); Befund 1 ist genau davon der Ernstfall, und
deshalb steht zu jedem Negativnachweis oben eine Positivkontrolle, die rot wird.

**3. Zustandsausgabe.** Auf die Prueffrage "laesst sich aus der Ausgabe allein erkennen,
ob richtig gerechnet wurde" lautet die Antwort weiter **nein**, und Befund 1 ist der
teuerste Beleg dafuer: Der Riegel meldet die Zahl der Ziele, nicht die Zahl der
gesammelten und der als Nichtwert verworfenen Eintraege. Die Tabelle "17 gegen 18
Eintraege", an der der Unterschied zwischen einem tragfaehigen und einem untauglichen
Bauweg haengt, war nur mit eingeschobenen `message()` zu bekommen -- zum vierten Mal in
drei Pruefungen dieses Pakets. Ich mache daraus keinen eigenen Vorschlag: 0076
schliesst "die Meldung umbauen" aus, und der Punkt traegt bereits die Begruendung von
0101 und 0103.

**4. Raender.** Die Randlage dieser Runde ist die **Form** der Eigenschaft und nicht ihr
Wert: Zeichenkette gegen Liste, mit `list(LENGTH)` an allen vier Kombinationen
nachgemessen (oben). Ueberlauf, Division und Rundung gibt es hier nicht; die einzige
Arithmetik ist `math(EXPR lfd "${lfd} + 1")` ueber eine Listenlaenge, durch
`eintragszahl` beschraenkt.

## Wonach ich noch gesucht und nichts gefunden habe

- **Ob eine sechste Stelle dieselbe Frage stellt.** Nein. Alle `if(NOT ...)` der Datei
  ueber einem gelesenen Eigenschaftswert sind die fuenf bekannten (282/283, 410, 488,
  661, 682); die uebrigen pruefen `TARGET`, `IS_ABSOLUTE`, `IN_LIST`, `STREQUAL` oder
  eine globale Eigenschaft, die diese Datei selbst setzt. Alle fuenf sind heute von 0103
  und 0108 zusammen abgedeckt.
- **Ob der empfohlene Weg an den Stellen von 0108 traegt.** Ja. `SOURCES`,
  `LINK_LIBRARIES`, `LINK_OPTIONS` und ihre `INTERFACE`-Formen sind Listen und keine
  Zeichenketten -- dort ist "je Listeneintrag" wirklich je Eintrag. Der Satz ist allein
  an den zwei `COMPILE_FLAGS`-Stellen falsch, und 0108 verweist auf ihn.
- **Ob der Bauagent die Luecke schon selbst gemeldet hat.** Nein --
  `grep 'je Listeneintrag'` ueber `aufgaben/` nennt allein 0103 und 0108, also die zwei
  Vorschlaege meiner eigenen Rolle.
- **Ob das rote `ergebnis: fehler` in `befunde/uebersetzung-2026-09-05.md` diesem Paket
  gehoert.** Nein -- in meinem sauberen Export sind beide Profile auf allen drei
  Bauwegen gruen, Konfiguration, Bau und `ctest` je Code 0.
- **Benennung, Aufbau, Zeilenumbruch der Bedingung.** Kein Befund; `specs/` schweigt.

## Vorschlag

- `0113-empfohlener-bauweg-traegt-compile-flags-nicht.md` -- beide Befunde,
  `rolle: projektmanager`.

Er aendert **nur Text in zwei Vorschlagsdateien** und beansprucht `werkzeugkette.cmake`
ausdruecklich nicht; er schneidet sich damit weder mit 0103 noch mit 0104 oder 0108 und
kann vor ihnen laufen. Das ist auch die richtige Reihenfolge: Der Befund gehoert vor die
Annahme von 0103, nicht hinter sie.
