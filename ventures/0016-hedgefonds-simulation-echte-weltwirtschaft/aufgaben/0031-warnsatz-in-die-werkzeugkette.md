---
id: 0031-warnsatz-in-die-werkzeugkette
rolle: kernbauer
status: vorschlag
haengt_an: [0019-vorratsverfahren-profilliste]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/CMakeLists.txt]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme".
---

# `FABRIK_STRENGE` gehört in die Werkzeugkette, nicht in jeden Kasten

Vorschlag aus dem Bau von Paket 0019 (2026-09-02, Rolle `testentwickler`).

## Der Befund

`FABRIK_STRENGE` — der Warnsatz mit `-Werror`, gegen den jede Zeile dieses Vorhabens
übersetzt wird — steht seit heute **zweimal wortgleich** im Baum:
`kern/CMakeLists.txt` und `pruefstand/CMakeLists.txt`. Ich habe ihn abgeschrieben, weil
`set()` in CMake verzeichnisgebunden ist: Was `kern/` setzt, sieht ein Geschwister-
verzeichnis nicht. `FABRIK_UEBERLAUF_SCHALTER` und `FABRIK_SANITIZER_SCHALTER` haben
dieses Problem nicht — sie stehen in `werkzeugkette.cmake`, die auf oberster Ebene
eingebunden wird und deshalb nach unten durchreicht.

T13 nennt **sieben** Mitglieder. Fünf davon haben noch keine `CMakeLists.txt`. Wird die
Duplizierung nicht aufgelöst, steht der Satz am Ende siebenmal da — und die siebte
Fassung ist die, die niemand nachführt, wenn ein Schalter dazukommt.

**Das ist keine Kosmetik, sondern eine Diagnoselücke.** Die drei Überlaufmaßnahmen aus
ADR 0011 sind nur so viel wert wie die Warnschalter, unter denen sie laufen. Ein Kasten,
dessen Warnsatz beim Abschreiben eine Zeile verloren hat, übersetzt grün und prüft
weniger — und der Übersetzungsbericht sagt in beiden Fällen `ergebnis: ok`. Genau die
Fehlerklasse, gegen die dieses Vorhaben `-Werror` überhaupt setzt.

## Warum das ein eigenes Paket ist und nicht Teil von 0019

`werkzeugkette.cmake` gehört **keinem Paket**. Sie stand nicht in meiner `dateien`-Liste,
und die Regel ist eindeutig: Schreib nichts außerhalb deines Zielverzeichnisses, auch wenn
du dort einen Fehler siehst. Hätte ich sie angefasst, hätte ich die Serialisierung
umgangen, die der Projektmanager über die `dateien`-Listen herstellt — und die Änderung
berührt `kern/CMakeLists.txt`, an der andere Kernpakete arbeiten.

Es ist auch nicht Teil eines der offenen Kernpakete: Die Änderung ist nur dann sinnvoll,
wenn sie **beide** vorhandenen Kästen zugleich umstellt. Ein Kernpaket, das nur `kern/`
umstellte, ließe den Prüfstand mit der Kopie zurück und machte den Zustand schlechter
statt besser.

Es hängt an 0019, weil es dessen Ergebnis voraussetzt: Vor heute gab es nur eine Fassung,
und die Duplizierung war keine.

## Was zu tun ist

1. `set(FABRIK_STRENGE …)` aus `kern/CMakeLists.txt` nach `werkzeugkette.cmake` verschieben
   — samt der beiden Begründungsabsätze, die heute darüberstehen (der `-Wpedantic`-Absatz
   gehört fachlich ohnehin dorthin, wo `__int128` begründet ist).
2. In `kern/CMakeLists.txt` und `pruefstand/CMakeLists.txt` die lokalen `set()`-Blöcke
   streichen. Die `target_compile_options`-Zeilen bleiben unverändert.
3. Der Verweis in `kern/CMakeLists.txt` auf „siehe `kern/CMakeLists.txt`" in
   `werkzeugkette.cmake` (Zeile 24) zeigt dann auf sich selbst und muss mitgehen.

**Was nicht dazugehört:** die Werte selbst ändern, `-Wpedantic` doch aufnehmen, ein
zweites Bauprofil einführen. Das wären eigene Entscheidungen mit eigener Begründung.

## Abnahme

1. `grep -rn 'set(FABRIK_STRENGE'` über das Vorhaben liefert **genau eine** Zeile, und sie
   steht in `werkzeugkette.cmake`.
2. Der Übersetzungsbericht des Tages zeigt beide Kästen gebaut und **alle** Tests `Passed`
   — auch über den Alleinbau-Weg, den `baulauf.py` geht (`cmake -S kern -B kern/bau` und
   `cmake -S pruefstand -B pruefstand/bau` je einzeln). Das ist die Bedingung, an der die
   Verschiebung scheitern kann: Beim Alleinbau wird `werkzeugkette.cmake` erst im
   `PROJECT_IS_TOP_LEVEL`-Block eingebunden, und die `set()`-Reihenfolge muss davor liegen.
3. Der Warnsatz ist **wortgleich** zu dem von heute — kein Schalter fällt bei der
   Verschiebung weg. Nachweis: `git diff` zeigt an den drei Dateien zusammen nur
   Verschiebung und Streichung, keine geänderte Zeile innerhalb des Satzes.
4. Ein absichtlich eingebauter Verstoß (etwa eine ungenutzte Variable in `kern/src/`) macht
   **beide** Kästen rot. Sonst ist nicht gezeigt, dass der verschobene Satz noch greift.

## Rückläufe

0.

---

**Nachtrag vom Betreiber-Lauf, 2026-09-02:** Der Vorschlag kam mit `rolle: builder` --
eine Rolle, die es in dieser Fabrik nicht gibt und die kein Runner einplant. Die
Waisenpruefung in `rollen-pruefen.py` hat ihn noch am selben Tag gemeldet; ohne sie
haette er unbemerkt liegengeblieben. Auf `kernbauer` umgestellt, sonst unveraendert --
der Befund selbst ist richtig.
