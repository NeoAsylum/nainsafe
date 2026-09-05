# Mutationsstand zur Pruefung von 0056, 2026-09-04

Fuenf Aenderungen an `kern/include/kern/meldung.hpp`, jede allein in einer eigenen Kopie
des Baumes ausserhalb des Repos. Sie belegen, dass `meldung_probe` die Zusagen der
Abnahme wirklich misst und nicht nur nennt.

Wer sie nachbaut: `kern/` und `werkzeugkette.cmake` nach `$TMPDIR` kopieren (nicht das
`bau/`-Verzeichnis), dort die Ersetzung machen, `cmake -S kern -B bau`,
`cmake --build bau --target meldung_probe`, dann `cmake -E env bau/meldung_probe`.
Der direkte Aufruf des gebauten Programms ist gesperrt, der Umweg ueber `cmake -E env`
nicht.

| Kuerzel | vorher | nachher | erwartet | gemessen |
|---|---|---|---|---|
| M1 | `abgeschnitten_ = true;` in `text()` | entfernt | rot | Uebersetzung rot, `meldung_probe.cpp:339` |
| M2 | `marke_setzen();` in `text()` | entfernt | rot | Uebersetzung rot, `meldung_probe.cpp:339` |
| M3 | `return abgeschnitten_;` | `return laenge_ >= MELDUNG_ZEICHEN_MAX;` | rot | Laufcode 1, Zeilen 285 und 294 |
| M4 | `MARKE[] = "[...]"` | `MARKE[] = "~~~"` | **gruen** | Laufcode 0, Protokoll `"-~~~"` |
| M5 | `PUFFER_ZEICHEN = 512` | `PUFFER_ZEICHEN = 300` | **gruen** | Laufcode 0, Protokoll `299` statt `511` |

M4 und M5 muessen gruen bleiben -- sie pruefen die andere Richtung: dass die Probe keine
Grenze abschreibt, sondern aus `MARKE`, `MARKE_ZEICHEN` und `MELDUNG_ZEICHEN_MAX`
herleitet. Eine Mutation, die nur rot machen kann, belegt nur die Haelfte.

## M1b und M2b -- dieselben Mutationen ohne die Zusicherungen

M1 und M2 sterben schon beim Uebersetzen an

```cpp
static_assert(zur_uebersetzungszeit_gekuerzt(),
              "eine gekuerzte Meldung meldet es und endet auf der Marke");
static_assert(zur_uebersetzungszeit_vollstaendig(),
              "eine kurze Meldung meldet kein Abschneiden");
```

Das ist ein gutes Ergebnis, verdeckt aber, ob die **Laufzeitpruefungen** ebenfalls
greifen. Fuer M1b und M2b werden diese beiden Zeilen in `meldung_probe.cpp` durch

```cpp
[[maybe_unused]] const bool a1 = zur_uebersetzungszeit_gekuerzt();
[[maybe_unused]] const bool a2 = zur_uebersetzungszeit_vollstaendig();
```

ersetzt -- die Funktionen bleiben benutzt, der Abbruch faellt weg.

```
M1b (kein Merker):   Zeilen 187, 215, 239, 301   -- alle vier Positivpruefungen
M2b (keine Marke):   Zeilen 199, 216, 254, 261, 302
                     und im Protokoll: Zahl am Pufferende abgeschnitten zu "-92233"
```

Die letzte Zeile ist der eigentliche Nachweis fuer Abnahmebedingung 2: Ohne die Marke
steht dort wieder die wohlgeformte, um vierzehn Ziffern gekuerzte Zahl.

## Der Vergleich gegen den Stand vor 0056

Fuer Abnahmebedingung 3 braucht es keine Mutation, sondern einen zweiten Baum, der sich
in **genau einer** Datei unterscheidet:

```
git show 849abc3^:ventures/0016-.../kern/include/kern/meldung.hpp > <baum2>/kern/include/kern/meldung.hpp
```

`meldung_probe.cpp` muss dort geloescht werden -- die neue Probe uebersetzt gegen den
alten Kopf nicht. `schreiber_probe` und `schritt_probe` bauen und laufen; ihre Ausgaben
sind gegen den neuen Stand byteidentisch (`cksum 3000347287 3280` und
`565531488 1448`).

Achtung beim Suchen des Vorzustandes: Der Kopf steckt in `849abc3`
(„datenbauer: 0065-reihentoml-reihe-9-ohne-sollrolle"), nicht in `8fff575`
(„kernbauer: 0056"). Ueber den Commit-Betreff findet man ihn nicht, ueber
`git log -S 'abgeschnitten_'` sofort.
