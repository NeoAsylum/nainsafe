---
typ: pruefung
paket: 0103-notfound-endung-verdeckt-schalter
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Alle drei Abnahmebedingungen an eigenen Wegwerf-Baeumen nachgefahren, jede gegen den eingefrorenen Stand `69662e1^` gegengeprobt; dazu die vier Faelle, die die Abnahme nicht nennt.
befunde: 2
---

# Paket 0103 ist erfuellt

Gemessen mit CMake 4.2.3 und g++ 15.2.0 (die festgenagelte Version, `werkzeugkette.cmake:28`).

**Bezugsstand.** Der Arbeitsbaum ist fuer `werkzeugkette.cmake` deckungsgleich mit `HEAD`
(`git status` leer, 52.868 Bytes). Der Stand *vor* der Aenderung ist `69662e1^`, gefunden
ueber

    git log -S fabrik_nichtwert_leeren -- .../werkzeugkette.cmake

Der Commit `69662e1` traegt den Betreff `datenbauer: 0120-abschnittszitat-nachmessung-
zinsreihen` und hat mit 0103 nichts zu tun -- ein Fremdlauf hat die Aenderung
mitcommittet. Ich habe beide Fassungen byteweise nach `$TMPDIR` gezogen (49.961 / 52.868
Bytes) und **alle** Vorher-Zahlen gegen die eingefrorene Kopie gemessen, nicht gegen einen
bewegten `HEAD`.

**Nachweisort:** alles unter `$TMPDIR/p0103`, ausserhalb des Repos. Kein Wegwerf-Manifest
und kein `build/` im Arbeitsbaum.

**Nicht gelesen:** Ich habe die Abschnitte *Nachweis*, *Was ich nicht angefasst habe* und
*Worauf ich unsicher bin* im Paketrumpf erst nach Abschluss meiner eigenen Messungen
gegengelesen. Die Wegwerf-Baeume, die Vergleichsform und die vier Zusatzfaelle unten sind
eigene Wahl.

## Abnahmebedingung 1 -- der getarnte Schalter wird gefangen

Baum wortgleich aus dem Paketrumpf: `add_library(z STATIC z.cpp)`,
`fabrik_warnsatz_anlegen(z)`, dazu
`set_source_files_properties(z.cpp PROPERTIES COMPILE_FLAGS "-w -DPFAD=x-NOTFOUND")`,
Quelle `int f(double d){ int i = d; return i; }`.

| | Konfiguration | Meldung | Bau |
|---|---|---|---|
| **vorher** (`69662e1^`) | **Code 0** | `1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter` | Code 0, **null Diagnosen** |
| **nachher** | **Code 1** | `hebt den Satz wieder auf: -w` / `gefunden in: COMPILE_FLAGS an <baum>/z.cpp:  -w -DPFAD=x-NOTFOUND` | — |

Die Abnahme verlangt in `gefunden in` die Eigenschaft **und** das Wort `-w`. Die
Eigenschaft steht in der `gefunden in`-Zeile, das Wort in der Zeile darueber; als Eintrag
wird der ganze Wert genannt, weil `COMPILE_FLAGS` eine Zeichenkette und kein Listentyp ist.
Beides ist da, wenn auch auf zwei Zeilen verteilt.

**Die Gegenprobe ist gefahren, nicht uebernommen:** Am eingefrorenen Vorher-Stand baut
derselbe Baum gruen durch, waehrend `-w` auf der Uebersetzerzeile steht. Der stille Schaden
ist unabhaengig reproduziert.

**Zwei Kontrollen, damit das rote Ergebnis etwas belegt:**

- *Positivkontrolle:* dieselbe Quelle ohne jeden Abschalter -- Konfiguration Code 0, Bau
  **Code 1** mit `error: conversion from 'double' to 'int' ... [-Werror=float-conversion]`,
  vorher wie nachher. Ohne sie belegte kein gruener Bau oben etwas.
- *Gegen einen Riegel, der einfach alles faengt:* dieselbe Zeile ohne die Endung
  (`"-w -DPFAD=x"`) bricht **vorher wie nachher** mit Code 1 ab. Die Aenderung hat also
  nicht die Endung, sondern die Frage verschoben.

## Abnahmebedingung 2 -- kein Fehlalarm mehr, und keiner neu

| Baum | vorher | nachher |
|---|---|---|
| `target_compile_options(z PRIVATE -DPFAD=x-NOTFOUND)` | Code 1, `es fehlen: -Wall … -fno-fast-math` (alle 17) | **Code 0** |
| `target_compile_options(z PRIVATE -w -DPFAD=x-NOTFOUND)` | Code 1, aber `es fehlen: …` | **Code 1**, `gefunden in: COMPILE_OPTIONS an z:  -w` |

Die zweite Zeile ist die tragende, und der Konfigurationscode allein unterscheidet sie
nicht: vorher rot aus dem **falschen** Grund (Fehlalarm, alle 17 Schalter angeblich fort),
nachher rot aus dem **richtigen**. Ich habe deshalb den Meldungstext verglichen, nicht den
Code.

Beim ersten Baum zusaetzlich geprueft, dass der gruene Riegel nicht Blindheit ist: Der Bau
bricht danach weiterhin mit `-Werror=float-conversion` ab.

## Abnahmebedingung 3 -- kein Urteil aendert sich

**22 Wegwerf-Baeume** (`befunde/pruefung-0066/nachbau.py`), **kalt** gefahren -- die
Ablagen vorher geloescht, damit kein wiederverwendeter CMake-Cache eine Aenderung
verdeckt:

| Stand | Exit | Ergebnis | Positivkontrolle |
|---|---|---|---|
| `HEAD` | 0 | `0 Abweichung(en) vom Soll` | `p_positiv` baut rot, 1 Fehler |
| `69662e1^` | 0 | `0 Abweichung(en) vom Soll` | ebenso |

Zusaetzlich **maschinell** verglichen statt nach Augenschein: beide Ausgaben normalisiert
(Ablagepfade, Soll-Vermerk) und Zeile fuer Zeile gegenuebergestellt -- **44 Zeilen, 0
Unterschiede**. Der einzige Unterschied vor der Normalisierung ist die Kopfzeile, die
Stand und Byte-Zahl nennt.

**Drei Bauwege in beiden Profilen** (`befunde/messung-0076/bauwege.py`). Den Vorher-Stand
habe ich als vollstaendigen Baum aus `git archive HEAD <venture> specs decisions`
hergestellt und darin **allein** `werkzeugkette.cmake` auf `69662e1^` zurueckgedreht:

| uebersetzende Ziele | `SANITIZER=ON` | `OFF` |
|---|---|---|
| Arbeitsbereich | 19 / 19 | 17 / 17 |
| `kern` allein | 12 / 12 | 11 / 11 |
| `pruefstand` allein | 5 / 5 | 4 / 4 |

(vorher / nachher). Konfiguration, Bau und `ctest` je **Code 0** in allen sechs Laeufen,
14 / 10 / 3 Tests gruen. Die Zahlen sind gegen den **eigenen** Stand davor verglichen, wie
die Abnahme es verlangt, nicht gegen einen festen Sollwert.

`bauwege.py` meldet in **beiden** Laeufen `2 Abweichung(en)` und Exitcode 1. Das ist eine
gealterte Sollzahl im Skript (es erwartet 18/16, gemessen sind 19/17) und **vorher wie
nachher dieselbe** -- also kein Urteil, das sich aendert. Dazu Befund 2.

*Ein eigener Fehlgriff, damit ihn niemand fuer einen Befund haelt:* Mein erster
Vorher-Baum enthielt nur das Venture-Verzeichnis; darin fiel `belegstellen_riegel` mit
`'…/specs/0016-…' ist kein Verzeichnis` aus. Nach Ergaenzung von `specs` und `decisions`
war er gruen. Das war meine Ablage, nicht der Baum.

## Was ich ausserdem gesucht habe -- und was dabei herauskam

**Die tragende Annahme des neuen Makros, direkt gemessen.** Der Kommentar behauptet zwei
Schreibweisen des Nichtwerts. An einem Ziel ohne jede Eigenschaft:

    a=[a-NOTFOUND]  e=[e-NOTFOUND]  quellopt=[NOTFOUND]  quellflags=[NOTFOUND]

`get_target_property` setzt `<variablenname>-NOTFOUND`, `get_source_file_property` das
blanke `NOTFOUND`. Genau die zwei Faelle, die `fabrik_nichtwert_leeren` vergleicht. Die
Behauptung im Kommentar traegt.

**Alle fuenf eingesammelten Eigenschaften, nicht nur die zwei der Abnahme.** Die Abnahme
nennt `COMPILE_FLAGS` an der Quelldatei und `COMPILE_OPTIONS` am Ziel. Ich habe die
uebrigen drei nachgezogen, je mit `-w` neben der Endung:

| Eigenschaft | vorher | nachher |
|---|---|---|
| `COMPILE_FLAGS` am Ziel | Code 0, gruener Bau, **0 Diagnosen** | Code 1, `COMPILE_FLAGS an z` |
| `COMPILE_OPTIONS` an der Quelldatei | Code 0, gruener Bau, **0 Diagnosen** | Code 1, `COMPILE_OPTIONS an <baum>/z.cpp` |
| `INTERFACE_COMPILE_OPTIONS` an einem `INTERFACE_LIBRARY` | Code 0, gruener Bau, **0 Diagnosen** | Code 1, `INTERFACE_COMPILE_OPTIONS an i` |
| `PUBLIC` an einer `STATIC`-Bibliothek | Code 1 (Fehlalarm) | Code 1, beide Herkuenfte genannt |

**Drei weitere stille Faelle**, die das Paket nicht aufzaehlt und die es miterledigt. Der
laengste Variablenname (`schnittstellenschalter`) belegt nebenbei, dass die
Namenseinsetzung des Makros auch dort greift.

**Und die Gegenrichtung -- kein neuer Fehlalarm.** Dieselben drei Eigenschaften je mit
`-DPFAD=x-NOTFOUND` **ohne** `-w`: alle drei Code 0, vorher wie nachher. Der Riegel ist
schaerfer geworden, nicht lauter.

**Raender.** Vier Faelle, alle vorher wie nachher zeichengleich, keiner ein Rueckschritt:
echter Wert `NOTFOUND` (gilt weiter als leer -- unveraendert, und kein Uebersetzerschalter),
echter Wert `zielflags-NOTFOUND`, `NOTFOUND` neben `-w` (wird gefangen, beide Staende),
leere Zeichenkette.

**Determinismus.** Derselbe Baum zweimal frisch konfiguriert: Ausgabe nach
Pfadnormalisierung byte-gleich (SHA-256 `30a55166…` beidemal). Die Aenderung ist ein
Zeichenkettenvergleich ohne Gleitkomma, ohne ungeordnete Menge, ohne Zeit- oder
Adressbezug. Staerker noch: 22 Baeume und sechs Baukonfigurationen liefern ueber zwei
Staende und zwei Profile hinweg wortgleich dasselbe.

**Strukturell, weil eine Messung das nicht abdecken kann.** Die alte Bedingung verwarf
jeden Wert, auf den `^(.*-)?NOTFOUND$` passte; die neue verwirft nur noch zwei exakte
Werte. Die neue Menge der verworfenen Werte ist eine **echte Teilmenge** der alten -- der
Riegel kann dadurch nichts verlieren, was er vorher fing. Das deckt auch die Faelle ab,
die ich nicht gemessen habe.

**Reihenfolge im Makro nachgesehen.** `fabrik_nichtwert_leeren` schreibt in den
Gueltigkeitsbereich des Aufrufers, leert also `schalter`, `zielflags`, `quellopt`,
`quellflags` und `schnittstellenschalter`. `schalter` wird in Zeile 458 normalisiert und
erst danach in Zeile 472 (`IN_LIST`) und Zeile 528 gelesen -- die Reihenfolge stimmt. Die
uebrigen vier werden nach dem Sammeln nicht mehr gelesen; `quellopt`/`quellflags` werden
je Schleifendurchlauf neu gesetzt. Der zweite Aufruf auf `schalter` (458, dann 528) ist
folgenlos, weil das Makro idempotent ist.

**Punkt 3 aus *Was zu tun ist*** (nicht Teil der drei Abnahmebedingungen, aber verlangt):
Der Satz *„Eine gesetzte Eigenschaft, deren letzter Listeneintrag zufaellig so hiesse,
traegt einen Schalter und ist keine leere Menge"* -- die Behauptung, die der alte Anker
nicht einloeste -- ist **fort**. Der neue Kommentar nennt Messdatum, CMake-Version, Baum
und Ergebnis; ich habe seine beiden tragenden Messungen oben nachgefahren, beide stimmen.

## Befund 1 -- die Meldung des Riegels zeigt seine eigene Schaerfe nicht

**Kein Mangel dieses Pakets; es senkt das Urteil nicht.** Der Paketrumpf nennt die Luecke
selbst und schliesst sie ausdruecklich aus. Ich melde sie, weil ich sie diesmal **gemessen**
habe, statt sie zu vermuten.

Am Stand `69662e1^` melden vier verschiedene Baeume -- `b1` der Abnahme und meine drei
Zusatzfaelle -- **wortgleich dieselbe** Zeile:

    1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter

In allen vier Faellen erreichte `-w` den Uebersetzer und der Bau lief mit **null
Diagnosen** durch. Die Ausgabe eines stumpfen Riegels ist von der eines scharfen nicht zu
unterscheiden: Sie nennt die Zahl der **Ziele**, nie die Zahl der gesammelten oder
verworfenen Eintraege. Beide Nachweise zu 0076 und beide zu diesem Paket brauchten dafuer
eine eingeschobene `message()`.

Vorschlag geschrieben: `0132-riegelmeldung-nennt-gesammelte-eintraege` (`status: vorschlag`).

## Befund 2 -- die zwei Messwerkzeuge des Riegels sind nicht verlaesslich

**Ebenfalls ausserhalb dieses Pakets** und ausserhalb seiner `dateien`-Liste.

*Erstens:* `befunde/messung-0076/bauwege.py` meldet auf einem **fehlerfreien** Baum
`2 Abweichung(en)` und Exitcode 1, in beiden Profilen -- eine feste Sollzahl 18/16, die
der Baum auf 19/17 ueberholt hat. Ich habe das an zwei Staenden gemessen; die Meldung ist
in beiden dieselbe. Die Abnahme von 0103 **und** die von 0108 verlangen einen Lauf dieses
Skripts. Ein Messwerkzeug, das immer rot meldet, kostet jeden Bauagenten und jeden Pruefer
einen Absatz Erklaerung -- und gewoehnt beide daran, die Zahl zu ueberspringen. Das ist
dieselbe Fehlerklasse, gegen die die ganze Kette 0076/0103/0104/0108 geschrieben ist: eine
Zahl, die etwas anderes behauptet, als sie misst.

*Zweitens:* `befunde/pruefung-0066/nachbau.py` ist der **einzige** Regressionsnachweis des
Schlussriegels -- im echten Baum steht nirgends ein `-w`, also wird nichts rot, wenn jemand
den Riegel stumpf macht. Es haengt in keinem `add_test` und laeuft in keiner automatischen
Bahn; es lief in diesem Lauf nur, weil die Abnahme es namentlich nennt. Gemessen: **4,5
Sekunden kalt** fuer alle 22 Baeume. Der Belegstellenriegel haengt als `add_test` in
`ctest` (`pruefstand/CMakeLists.txt:90`); der Mutationslauf tut es bewusst nicht, weil er
Minuten kostet (0110). 4,5 Sekunden liegen auf der billigen Seite dieser Grenze.

Vorschlag geschrieben: `0133-schlussriegel-nachbau-laeuft-nirgends`
(`status: vorschlag`).

## Wonach ich gesucht und nichts gefunden habe

- **Ob die Aenderung etwas verliert, was der Riegel vorher fing** -- strukturell
  ausgeschlossen (Teilmengenargument oben) und an 22 Baeumen bestaetigt.
- **Ob ein neuer Fehlalarm entsteht** -- drei Eigenschaften mit harmloser Endung, alle
  gruen; sechs Baukonfigurationen des echten Baums, alle Code 0.
- **Geschwister derselben Ursache im Modul.** Sechs weitere Wahrheitsproben auf
  Eigenschaften geprueft: Zeile 379 und 681 (globale Eigenschaften mit festen Listen,
  kein Nichtwert moeglich), 425/629 (Verzeichniseigenschaften, nur in `foreach`), 427 und
  532 (`TYPE`/`SOURCE_DIR`, immer gesetzt). Bleibt Zeile 534 (`if(NOT quellen)`) samt dem
  Kommentar `# wie oben`, der durch dieses Paket seinen Verweis verliert -- **beides hat
  Paket 0108 (`offen`) bereits mit denselben zwei Baeumen und in seinem Punkt 4.** Kein
  eigener Vorschlag; ein zweites Paket waere ein Doppel.
- **Die zwei `-NOTFOUND$`-Tests der Nullabhaengigkeitspruefung** (heute Zeile 707 und 770)
  sind unberuehrt, wie das Paket es verlangt -- nachgesehen, nicht angenommen.
