---
id: 0060-schlussriegel-blinde-flecken
rolle: kernbauer
status: vorschlag
haengt_an: [0058-warnsatz-schlussriegel-alle-ziele]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# Der Schlussriegel schweigt an zwei Stellen, an denen er reden muesste

Aus der Pruefung von Paket 0058 (2026-09-03, Rolle `kern-pruefer`). Messungen in
`befunde/pruefung-0058-warnsatz-schlussriegel-alle-ziele-2026-09-03.md`.

Paket 0058 ist **erfuellt** — alle drei Abnahmebedingungen nachgefahren, nichts daran
verletzt. Was hier steht, sind zwei Luecken **ausserhalb** seiner Abnahme, und die erste
davon geht auf meinen eigenen Vorschlag zurueck, nicht auf den Bauagenten.

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

## Warum das ein eigenes Paket ist

Beide Luecken liegen in `fabrik_schlussriegel`, also in der Funktion, die 0058 gerade
angelegt hat — aber keine von beiden ist eine seiner drei Abnahmebedingungen, und
Bedingung 1 nennt die vier Arten abschliessend. Ein Bauagent, der sie nebenbei erweitert
haette, waere aus seiner Abnahme herausgelaufen.

Beide zusammen in **einem** Paket, nicht in zweien: Sie aendern dieselbe Funktion in
derselben Datei, ihre `dateien`-Listen waeren identisch, und der Baulauf muesste sie
ohnehin serialisieren. Zwei Pakete kosten hier einen Lauf und bringen nichts.

## Was zu tun ist

Die Bauform steht frei. Ein Weg, den ich am 2026-09-03 gebaut und gemessen habe — zwei
Aenderungen, zusammen sechs Zeilen:

1. `MODULE_LIBRARY` in die Artenliste (`set(arten …)`).
2. Vor der Erfolgsmeldung ein `if(gezaehlt EQUAL 0)` mit `FATAL_ERROR`.

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

**Nachweisort:** dieselbe Staffelung wie in 0046 und 0058 — zuerst `$TMPDIR` ausserhalb
des Repos, sonst unterhalb von `befunde/` (`baulauf.py:116` sammelt dort keine Manifeste
ein), sonst ausgewiesene Nichtmessung mit Begruendung am Text der Aenderung. Am
2026-09-03 kam ich mit Rang 1 aus.
