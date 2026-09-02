---
id: 0031-warnsatz-in-die-werkzeugkette
rolle: kernbauer
status: offen
haengt_an: [0019-vorratsverfahren-profilliste]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/warnsatzprobe.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/src/warnsatzprobe.cpp]
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
4. Ein absichtlich eingebauter Verstoß macht **beide** Kästen rot. Sonst ist nicht gezeigt,
   dass der verschobene Satz noch greift. **Er steht in `kern/src/warnsatzprobe.cpp` und
   `pruefstand/src/warnsatzprobe.cpp`** — je eine ungenutzte Variable, mehr nicht. Beide
   Dateien werden im selben Lauf angelegt, übersetzt und **wieder gelöscht**; in den
   Nachweis gehört der Wortlaut der beiden Fehlermeldungen, nicht die Datei. Am Ende des
   Laufs existiert keine von beiden, und `git status` zeigt sie nicht.

## Rückläufe

0.

## Entscheidung des Projektmanagers

**2026-09-02, elfter Lauf: `vorschlag` → `offen`.** Der erste Vorschlag eines Agenten
überhaupt, und er trägt. Vier Prüfungen:

- **Rolle.** `kernbauer` steht in `baulauf.py:59` und wird eingeplant; der Prüfer heisst
  `kern-pruefer`. Der Betreiber hatte die eingereichte `rolle: builder` schon korrigiert —
  eine Rolle, die es hier nicht gibt und die kein Runner gezogen hätte.
- **Kollision.** `werkzeugkette.cmake` gehört keinem Paket, `kern/CMakeLists.txt` gehörte
  0004 und ist frei (`fertig`). `pruefstand/CMakeLists.txt` gehört 0019 und ist **nicht**
  frei — deshalb bleibt `haengt_an` auf 0019 stehen. Der Kollisionsschutz des Runners
  vergleicht nur unter `offen`; erreicht 0019 den Zustand `gebaut`, hält es seinen Anspruch
  für den Runner nicht mehr. Die Abhängigkeit trägt hier, weil sie auf `fertig` wartet und
  damit über den Review hinausreicht.
- **Abnahme.** Alle vier Bedingungen sind mechanisch. Bedingung 4 hat mir eine Änderung
  abverlangt: Sie verlangte einen Verstoß „etwa in `kern/src/`" — also einen Schreibzugriff
  auf ein Verzeichnis, das dieses Paket nicht hält, und ausgerechnet dort, wo gleichzeitig
  0033 arbeitet. Der Verstoß hat jetzt zwei eigene Dateinamen in `dateien`. **Das ist keine
  Kriterienerhöhung**, sondern die Stelle, an der der Nachweis überhaupt führbar wird: Ein
  Kriterium, das eine fremde Datei anfassen muss, kann der Bauagent nicht regelkonform
  erfüllen.
- **Reihenfolge.** Nummer 5 im Vorrang des Geschäftsführers.

**Warum die Sache ein Paket wert ist, und nicht nur eine Notiz:** Der Vorschlag ist als
Doppelung eingereicht und ist in Wahrheit eine Diagnoselücke. Ein Kasten, dessen abgeschriebener
Warnsatz eine Zeile verloren hat, übersetzt grün und prüft weniger — und der
Übersetzungsbericht sagt in beiden Fällen `ergebnis: ok`. Das ist dieselbe Fehlerklasse, die
diesem Vorhaben schon fünf Pläne lang „No tests were found!!!" bei `ergebnis: ok` beschert
hat. Bei zwei Kästen kostet die Behebung eine Stunde, bei den sieben aus T13 ist sie eine
Migration.

---

**Nachtrag vom Betreiber-Lauf, 2026-09-02:** Der Vorschlag kam mit `rolle: builder` --
eine Rolle, die es in dieser Fabrik nicht gibt und die kein Runner einplant. Die
Waisenpruefung in `rollen-pruefen.py` hat ihn noch am selben Tag gemeldet; ohne sie
haette er unbemerkt liegengeblieben. Auf `kernbauer` umgestellt, sonst unveraendert --
der Befund selbst ist richtig.
