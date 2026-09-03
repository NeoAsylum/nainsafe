---
id: 0060-schlussriegel-blinde-flecken
rolle: kernbauer
status: vorschlag
haengt_an: [0058-warnsatz-schlussriegel-alle-ziele]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Der Schlussriegel schweigt an drei Stellen, an denen er reden muesste

Aus den zwei Pruefungen von Paket 0058 (2026-09-03, Rolle `kern-pruefer`). Messungen in
`befunde/pruefung-0058-warnsatz-schlussriegel-alle-ziele-2026-09-03.md` (Befund 1 und 2)
und `…-runde2-2026-09-03.md` (Befund 3).

Paket 0058 ist **erfuellt** — alle drei Abnahmebedingungen zweimal unabhaengig
nachgefahren, nichts daran verletzt. Was hier steht, sind drei Luecken **ausserhalb**
seiner Abnahme, und die erste davon geht auf meinen eigenen Vorschlag zurueck, nicht auf
den Bauagenten.

Alle drei sind dieselbe Frage in drei Gestalten: **Ist der Nein-Fall vom gueltigen
unterscheidbar?** Befund 1 — ein uebersetzendes Ziel, das der Riegel nicht ansieht.
Befund 2 — ein Riegel, der nichts gesehen hat, meldet Erfolg. Befund 3 — ein Ziel, das den
Satz traegt und ihn zugleich abgeschaltet hat.

## Befund 1: `MODULE_LIBRARY` entkommt vollstaendig

Der Riegel prueft vier Zielarten: `STATIC_LIBRARY`, `SHARED_LIBRARY`, `OBJECT_LIBRARY`,
`EXECUTABLE`. `MODULE_LIBRARY` uebersetzt ebenfalls Quelldateien, steht aber nicht
darunter. Gemessen an einem Baum mit genau einem solchen Ziel:

```
-- Warnsatz-Schlussriegel: 0 uebersetzende Ziele geprueft, alle mit Warnsatz.
CODE=0        als_modul  CXX_FLAGS = -std=c++20 -fPIC
```

Kein einziger Warnschalter, kein `-Werror`, kein `-fwrapv` — und der Riegel meldet
Vollzug. Das ist exakt die Fehlerklasse, gegen die 0058 geschrieben wurde, nur eine
Zielart weiter.

**Das ist ausdruecklich kein Ruecklauf gegen 0058.** Die Artenliste steht woertlich im
Vorschlag 0058, den ich selbst geschrieben habe; der Bauagent hat sie befolgt und die
Auslassung im Nachweis ausgewiesen. Der Fehler liegt in meiner Liste.

## Befund 2: ein Zaehlerstand von null liest sich als Erfolg

Bei null gesehenen Zielen meldet der Riegel `0 uebersetzende Ziele geprueft, alle mit
Warnsatz` und endet mit Code 0. Der Kommentar bei Zeile 306 begruendet die Zahl gerade
damit, „der Riegel hat geprueft" von „der Riegel hat nichts gesehen" unterscheidbar zu
machen — die Zahl steht auch da, aber der Satz daneben behauptet das Gegenteil, und im
Uebersetzungsbericht steht die leere Zeile an derselben Stelle wie die gruene.

Heute schadet es nicht (15 / 10 / 5). Es schadet an dem Tag, an dem eine Umbenennung,
ein verschobener `include` oder ein `DEFER`, das nicht mehr greift, den Riegel leer laufen
laesst: Dann steht `0 … alle mit Warnsatz` im Bericht, `ergebnis: ok`, und niemand sieht
es. Dieselbe Frage wie bei 0038: **Ist der Nein-Wert von einem gueltigen unterscheidbar?**

## Befund 3: der Satz laesst sich anhaengen und im selben Atemzug abschalten

*Nachgetragen am 2026-09-03 aus der zweiten Pruefrunde zu 0058
(`befunde/pruefung-0058-warnsatz-schlussriegel-alle-ziele-runde2-2026-09-03.md`), solange
dieses Paket noch auf `status: vorschlag` stand. Die Bedingungen 1 und 2 sind unveraendert;
hinzugekommen ist Bedingung 3.*

Der Riegel prueft, ob die Schalter **dastehen**, nicht ob sie **wirken**. Ein Ziel, das
`fabrik_warnsatz_anlegen` ordentlich ruft und danach `-Wno-error` oder `-w` anhaengt, hat
den vollen Satz in `COMPILE_OPTIONS` und uebersetzt trotzdem ohne jede Diagnose. Gemessen
an zweimal derselben Quelle, `int f(double d){ int i = d; return i; }`:

```
nur fabrik_warnsatz_anlegen(z)   Riegel: 1 … alle mit Warnsatz   BAUCODE=2
                                 error: conversion from 'double' to 'int' [-Werror=float-conversion]
dasselbe + -Wno-error -w         Riegel: 1 … alle mit Warnsatz   BAUCODE=0, Diagnosen=keine
```

Der Riegel sagt in beiden Faellen wortgleich dasselbe. Der zweite Fall ist der
wahrscheinliche: Ein Bauagent, der auf eine Warnung stoesst, die er nicht loesen kann,
haengt `-Wno-error` an. Das ist der billigste Ausweg, und er sieht harmlos aus, **weil**
der Riegel Vollzug meldet.

Ein Weg, gemessen wie die beiden anderen: nach der Luecken-Schleife ein zweiter Durchgang
ueber `COMPILE_OPTIONS`, der auf eine kleine Sperrliste trifft -- `-w`, `-Wno-error` und
`-Wno-error=*`. Wer eine Warnung wirklich nicht loesen kann, unterdrueckt sie einzeln
(`-Wno-conversion` an genau einem Ziel) und begruendet das; ein Pauschalabschalter ist
etwas anderes. Die Sperrliste ist **keine** Ausnahmeliste im Sinne des Verbots oben: Sie
erlaubt nichts, sie verbietet zusaetzlich.

## Warum das ein eigenes Paket ist

Alle drei Luecken liegen in `fabrik_schlussriegel`, also in der Funktion, die 0058 gerade
angelegt hat — aber keine von ihnen ist eine seiner drei Abnahmebedingungen. Bedingung 1
nennt die vier Arten abschliessend und spricht woertlich von einem Ziel „ohne Warnsatz";
ein Ziel mit `-Wno-error` hat ihn. Ein Bauagent, der das nebenbei erweitert haette, waere
aus seiner Abnahme herausgelaufen.

Alle drei zusammen in **einem** Paket, nicht in dreien: Sie aendern dieselbe Funktion in
derselben Datei, ihre `dateien`-Listen waeren identisch, und der Baulauf muesste sie
ohnehin serialisieren. Drei Pakete kosten hier zwei Laeufe und bringen nichts.

## Was zu tun ist

Die Bauform steht frei. Ein Weg, dessen erste zwei Schritte ich am 2026-09-03 gebaut und
gemessen habe — drei Aenderungen, zusammen rund ein Dutzend Zeilen:

1. `MODULE_LIBRARY` in die Artenliste (`set(arten …)`).
2. Vor der Erfolgsmeldung ein `if(gezaehlt EQUAL 0)` mit `FATAL_ERROR`.
3. Eine Sperrliste gegen Pauschalabschalter, gepruefte je Ziel (Befund 3).

Gemessen mit dieser Fassung:

```
probe-modul     als_modul (MODULE_LIBRARY) … Abhilfe: fabrik_warnsatz_anlegen(als_modul)  -> CODE=1
Arbeitsbereich  Warnsatz-Schlussriegel: 15 uebersetzende Ziele geprueft, alle mit Warnsatz -> CODE=0
kern allein     Warnsatz-Schlussriegel: 10 uebersetzende Ziele geprueft, alle mit Warnsatz -> CODE=0
```

Der Nullriegel wird also an keinem heutigen Bauweg falsch scharf.

**Zu bedenken beim Nullriegel:** Er darf nur dort greifen, wo ueberhaupt ein Ziel erwartet
wird. Ein reines Datenverzeichnis ohne `add_library` waere ein Fehlalarm. Heute bindet nur
ein Baum mit Zielen die Kette ein; wird das je anders, gehoert die Ausnahme begruendet und
nicht stillschweigend eingebaut.

**Was nicht dazugehoert:** die Werte des Warnsatzes aendern, `-Wpedantic` aufnehmen, eine
Ausnahmeliste einfuehren, `CMAKE_CXX_EXTENSIONS` in die Pruefung ziehen (eigener Befund,
eigenes Paket), oder die Sanitizer aufnehmen.

## Abnahme

1. **Ein `MODULE_LIBRARY` ohne Warnsatz bricht die Konfiguration ab.** Nachweis: ein
   Wegwerf-Baum mit `add_library(x MODULE …)` und ohne `fabrik_warnsatz_anlegen`, der die
   Kette einbindet, endet mit Code ungleich 0, und die Meldung nennt `x (MODULE_LIBRARY)`.
   Daneben, am Stand **vor** der Aenderung gemessen, dieselbe Datei mit Code 0 und
   `0 uebersetzende Ziele geprueft` — ohne diese Gegenprobe belegt die erste Haelfte nur,
   dass irgendetwas rot wurde.
2. **Ein Riegel, der nichts sieht, bricht ab, und die heutigen Bauwege bleiben gruen.**
   Nachweis beides: ein Wegwerf-Baum, der die Kette einbindet und **kein** uebersetzendes
   Ziel hat, endet mit Code ungleich 0; **und** alle drei Bauwege (Arbeitsbereich, `kern`
   allein, `pruefstand` allein) konfigurieren weiter mit Code 0 und melden 15 / 10 / 5.
   Dazu der Bytevergleich aller erzeugten `CXX_FLAGS` vorher gegen nachher wie in 0058
   Bedingung 2 — 30 Ziele, bytegleich. Nicht „der Bau ist gruen".

3. **Ein Ziel mit Warnsatz und Pauschalabschalter bricht die Konfiguration ab.** Nachweis:
   ein Wegwerf-Baum mit `fabrik_warnsatz_anlegen(z)` und danach
   `target_compile_options(z PRIVATE -Wno-error -w)` endet mit Code ungleich 0, und die
   Meldung nennt den Schalter, an dem es liegt. Daneben, am Stand **vor** der Aenderung
   gemessen, dieselbe Datei mit Code 0 und `1 … alle mit Warnsatz`. Und die Gegenrichtung,
   weil sonst nur gemessen ist, dass irgendetwas rot wurde: dasselbe Ziel mit einer
   **einzeln** unterdrueckten Warnung (`-Wno-conversion`) konfiguriert weiter mit Code 0.
   Die drei heutigen Bauwege bleiben bei 15 / 10 / 5.

**Nachweisort:** dieselbe Staffelung wie in 0046 und 0058 — zuerst `$TMPDIR` ausserhalb
des Repos, sonst unterhalb von `befunde/` (`baulauf.py:116` sammelt dort keine Manifeste
ein), sonst ausgewiesene Nichtmessung mit Begruendung am Text der Aenderung. Am
2026-09-03 kam ich mit Rang 1 aus.
