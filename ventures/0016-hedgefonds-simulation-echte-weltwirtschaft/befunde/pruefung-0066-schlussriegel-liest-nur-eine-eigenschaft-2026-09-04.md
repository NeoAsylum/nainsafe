---
typ: pruefung
paket: 0066-schlussriegel-liest-nur-eine-eigenschaft
pruefer: kern-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen einzeln nachgefahren -- vier Umgehungswege je zweimal gebaut (Stand vorher Code 0 mit stillem Bau, Stand nachher Code ungleich 0 mit Nennung von Schalter und Eigenschaft), dazu Positivkontrolle, zwei Ueberschaerfe-Proben, die drei Bauwege mit 16/10/5, Bytevergleich aller 16 erzeugten CXX_FLAGS und ctest in beiden Profilen.
befunde: 1
---

# Der Riegel liest jetzt fuenf Eigenschaften, und alle vier Wege sind zu

## Womit gemessen wurde

Ort: `$TMPDIR/p0066` (Rang 1 der Staffelung, ausserhalb des Repos). Der Nachbau steht
unter `befunde/pruefung-0066/`.

Zwei Staende derselben Datei, beide als `include()` in Wegwerf-Baeume gehaengt:

| Stand | Herkunft | Bytes |
|---|---|---|
| vorher | `git show 8fff575^:…/werkzeugkette.cmake` | 25.700 |
| nachher | Arbeitsbaum, bytegleich mit `HEAD` (sha256 `f0771be9e4cd1310…`) | 34.597 |

**Der Commit-Betreff luegt, zehntes Mal.** Die Aenderung dieses Pakets liegt in
`8fff575 kernbauer: 0056-meldung-abschneiden-kenntlich (5 Dateien)`; der Commit
`80b5412` mit dem Namen dieses Pakets traegt nur `notizen/kernbauer.md`. Gefunden
ueber `git log -- <datei>`, nicht ueber den Betreff.

Wegwerf-Quelle ueberall dieselbe wie im Paket: `int f(double d){ int i = d; return i; }`.
Uebersetzer g++ 15.2.0, CMake 4.2.3.

## Bedingung 1 -- die Zielweise wird gefangen

| Baum | Konfig | Meldung |
|---|---|---|
| nachher, `set_target_properties(z PROPERTIES COMPILE_FLAGS "-w")` | **Code 1** | `hebt den Satz wieder auf: -w` / `gefunden in: COMPILE_FLAGS an z:  -w` |
| vorher, dieselbe Datei | Code 0 | `1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter.` |
| vorher, danach `cmake --build` | Code 0 | **0 Diagnosen** |

Der Schalter wird genannt, und die Herkunftszeile nennt zusaetzlich die Eigenschaft.

**Positivkontrolle:** derselbe Baum ohne den Abschalter, gebaut: **Code 2**, eine
Diagnose, im Wortlaut
`z.cpp:1:26: error: conversion from 'double' to 'int' may change value [-Werror=float-conversion]`.
Damit ist belegt, dass der stille Bau der Zeile darueber wirklich vom `-w` kommt und
nicht davon, dass die Quelle harmlos waere.

## Bedingung 2 -- Quelldatei und Schnittstellenziel ebenso

| Fall | nachher | vorher | vorher gebaut |
|---|---|---|---|
| `set_source_files_properties(z.cpp PROPERTIES COMPILE_FLAGS "-w")` | **Code 1**, `gefunden in: COMPILE_FLAGS an …/z.cpp:  -w` | Code 0, `1 … alle mit Warnsatz und ohne Pauschalabschalter.` | Code 0, 0 Diagnosen |
| `add_library(iface INTERFACE)` + `target_compile_options(iface INTERFACE -w)` + `target_link_libraries(z PRIVATE iface)` | **Code 1**, `iface (INTERFACE_LIBRARY) …` / `gefunden in: INTERFACE_COMPILE_OPTIONS an iface:  -w` | Code 0, dieselbe Meldung | Code 0, 0 Diagnosen |

Der Schnittstellenfall wird an `iface` gemeldet, nicht am Verbraucher `z` -- genau die
Abgrenzung aus *„Was nicht dazugehoert"*.

Ueber die Bedingung hinaus mitgemessen, weil der Befundabschnitt des Pakets sie in
Klammern nennt: `set_source_files_properties(z.cpp PROPERTIES COMPILE_OPTIONS "-w")`
-- nachher Code 1 (`COMPILE_OPTIONS an …/z.cpp`), vorher Code 0 und Bau Code 0 mit
0 Diagnosen.

## Bedingung 3 -- nichts wird ueber-scharf

**a) `-Wno-conversion` an einem Ziel mit Satz:** Konfig Code 0,
`1 uebersetzende Ziele geprueft … ; dazu 0 Schnittstellenziele …`, Bau Code 0.

**b) `add_library(x INTERFACE)` ohne jeden Schalter:** Konfig Code 0, **nicht** als
„Warnsatz fehlt" gemeldet, gezaehlt als `1 Schnittstellenziele`, waehrend die erste
Zahl bei `1 uebersetzende Ziele` bleibt. Die beiden Zaehler sind getrennt.

**c) Die drei Bauwege** (`-DCMAKE_BUILD_TYPE=RelWithDebInfo`,
`-DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math`, wie `baulauf.py`):

| Weg | vorher | nachher |
|---|---|---|
| Arbeitsbereich | Code 0, 16 | Code 0, **16** + 0 Schnittstellenziele |
| `kern` allein | Code 0, 10 | Code 0, **10** + 0 |
| `pruefstand` allein | Code 0, 5 | Code 0, **5** + 0 |

16 ≥ 10 + 5. Die Differenz von **einem** traegt `werkzeuge/belegstellen` -- so nennt es
der Bauagent im Kommentar, und das habe ich zweimal unabhaengig nachgesehen:

1. Die 16 `flags.make` des Arbeitsbereichs verteilen sich auf `kern/` (10),
   `pruefstand/` (5) und `werkzeuge/belegstellen/` (1, Ziel `belegstellen_riegel`).
2. `befunde/uebersetzung-2026-09-04.md` baut `werkzeuge/belegstellen` zusaetzlich
   allein und meldet dort `1 uebersetzende Ziele geprueft`.

**d) Bytevergleich der erzeugten Schalterzeilen**, Arbeitsbereich vorher gegen nachher,
alle 16 `flags.make`, Baumwurzel und Bauverzeichnis textlich normalisiert:

```
zeilen vorher/nachher: 16 16
sha256 vorher:  8af25eabeacc187a7d200e72054a0677e3c3ff44822b666c14d3c97d64dd227b
sha256 nachher: 8af25eabeacc187a7d200e72054a0677e3c3ff44822b666c14d3c97d64dd227b
bytegleich: True | bytes: 6298
```

Der Umbau haengt also keinen Schalter an und nimmt keinen weg.

**e) Bau und `ctest`, beide Profile**, Arbeitsbereich nachher:

| Profil | Konfig | Bau | Diagnosen | ctest |
|---|---|---|---|---|
| RelWithDebInfo | 0 | 0 | 0 | **12/12**, Code 0 |
| Debug | 0 | 0 | 0 | **12/12**, Code 0 |

## Wonach ich ausserdem gesucht habe

Weil eine feinere Pruefung neue Fehlalarme erzeugt und weil der Umbau die alten
Zusagen tragen muss, habe ich vierzehn weitere Baeume gegen den Stand *nachher*
gefahren. Keiner hat ein falsches Urteil ergeben:

**Alte Zusagen halten weiter** (Regression aus 0058/0060/0063):

| Baum | erwartet | gemessen |
|---|---|---|
| Ziel ohne `fabrik_warnsatz_anlegen` | „es fehlen: …" | Code 1, ganzer Satz gelistet |
| `target_compile_options(z PRIVATE -w)` | gefangen | Code 1, `COMPILE_OPTIONS an z` |
| `target_compile_options(z PRIVATE "SHELL:-Wno-error -w")` | gefangen | Code 1, Eintrag im Wortlaut genannt |
| Baum aus lauter Schnittstellenzielen | Nullfall bricht ab | Code 1, `kein einziges uebersetzendes Ziel` |

Der letzte ist der wichtigste: Der neue zweite Zaehler haette den Nullriegel saettigen
koennen. Er tut es nicht -- `gezaehlt` bleibt 0.

**Neue Wege, die ich zu finden versucht habe** -- alle gefangen:

| Baum | gemessen |
|---|---|
| `add_compile_options(-w)` vor `add_library` | Code 1 (`COMPILE_OPTIONS an z` -- die Verzeichniseigenschaft erbt ins Ziel) |
| `set_property(DIRECTORY APPEND PROPERTY COMPILE_OPTIONS -w)` | Code 1, ebenso |
| `COMPILE_FLAGS "-O0 -w"` (zwei Woerter in einem Eintrag) | Code 1, ganzer Eintrag genannt |
| `-w` an der **zweiten** von zwei Quellen | Code 1, `COMPILE_FLAGS an …/y.cpp` |
| `-Wno-error=conversion` an der Quelldatei | Code 1 |
| `$<1:-w>` an der Quelldatei | Code 1, Eintrag `$<1:-w>` genannt |
| Ziel im **Unterverzeichnis**, Quelle in `sub/src/`, Riegel per `DEFER` oben | Code 1 |
| Quelle per `target_sources` aus einem Unterverzeichnis, `-w` per `set_source_files_properties(… TARGET_DIRECTORY z …)` | Code 1 |

Die letzten beiden waren mir die wichtigsten: Alle vier Faelle der Abnahme spielen in
**einem** Verzeichnis, im echten Baum steht dagegen kein einziges Ziel im obersten.
Das `TARGET_DIRECTORY`, das der Kommentar an Zeile 430 „Pflicht und keine Feinheit"
nennt, traegt -- nachgemessen, nicht geglaubt.

**Kein Fehlalarm ausgeloest:**

| Baum | gemessen |
|---|---|
| `INTERFACE`-Bibliothek mit `-Wno-conversion`, gelinkt | Code 0 |
| `add_library(z STATIC $<TARGET_OBJECTS:obj>)` | Code 0, kein Absturz an der Genex-Quelle |

Doppelmeldung geprueft und in Ordnung: `target_compile_options(z PUBLIC -w)` an einer
`STATIC`-Bibliothek erzeugt zwei `gefunden in`-Zeilen (`COMPILE_OPTIONS` und
`INTERFACE_COMPILE_OPTIONS` desselben Ziels). Das ist eine Fundstelle mehr, kein Ziel
mehr -- der Bericht bleibt richtig.

## Der eine Befund -- ausserhalb der Abnahme

**`fabrik_riegel_sammeln` filtert `NOTFOUND` an zwei von fuenf Sammelstellen nicht.**

Der Kommentar an Zeile 253--256 begruendet die Bedingung damit, sie fange „das
`-NOTFOUND`, das `get_*_property` fuer eine ungesetzte Eigenschaft liefert". Das gilt
fuer `get_target_property`, nicht fuer `get_source_file_property`. Gemessen:

```
-- ziel-COMPILE_FLAGS=[a-NOTFOUND]        get_target_property
-- quelle-COMPILE_FLAGS=[NOTFOUND]        get_source_file_property
-- quelle-COMPILE_OPTIONS=[NOTFOUND]      get_source_file_property
-- ziel-INTERFACE=[e-NOTFOUND]            get_target_property
```

Der Test `MATCHES "-NOTFOUND$"` verlangt den Bindestrich und trifft das blanke
`NOTFOUND` deshalb nicht. Mit einer instrumentierten Kopie der Datei (eine `message()`
vor `set(pauschal "")`, nichts sonst) an einem sauberen Ziel mit genau einer Quelle:

```
MESS z: eintraege=[…;-fwrapv;-fno-fast-math;NOTFOUND;NOTFOUND]
        herkuenfte=[…;COMPILE_OPTIONS an z;COMPILE_OPTIONS an z]
```

Je Quelldatei ohne Quelleigenschaften laufen zwei Scheineintraege in `eintraege` --
im Arbeitsbereich also zweimal je Uebersetzungseinheit.

**Was daraus heute folgt: nichts.** `NOTFOUND` trifft weder `^-w$` noch
`^-Wno-error(=.+)?$`, es entsteht kein Fehlalarm und keine Luecke. Beide Listen wachsen
im Gleichschritt, die Paarung Eintrag/Herkunft bleibt richtig. **Das Urteil bleibt
deshalb `geprueft`.**

Warum es trotzdem ein Paket wert ist, steht in
`aufgaben/0075-riegel-sammeln-notfound-je-quelle.md`. Kurz: Der Waechter existiert
genau dafuer, Nichtwerte draussen zu halten, und an den zwei Stellen, an denen der
Nichtwert der **Normalfall** ist, haelt er nicht -- waehrend ein Kommentar daneben das
Gegenteil behauptet. Ein Kommentar, der einen Randfall abhakt, ist teurer als gar
keiner, wenn der Randfall der Normalfall ist.

## Was ich nicht geprueft habe

- **`CMAKE_CXX_FLAGS` von aussen und die Kommandozeile.** Vom Paket ausdruecklich
  ausgeschlossen.
- **Ob die Sperrliste vollstaendig ist.** Ebenfalls ausgeschlossen; sie steht
  unveraendert.
- **Den vierten Bauweg des Runners** (`pruefstand/bau/pruefung-0019/CMakeLists.txt`,
  ein liegengebliebenes Bauverzeichnis, das `baulauf.py` als fuenftes Manifest
  mitnimmt). Er bindet die Werkzeugkette nicht ein, meldet keine Riegelzeile und ist
  aelter als dieses Paket.
- **Einen Regressionstest fuer den Riegel selbst.** Es gibt keinen: Wer morgen das
  `TARGET_DIRECTORY` aus Zeile 435 streicht, bekommt von keinem Lauf ein rotes
  Ergebnis, weil im echten Baum nirgends ein `-w` steht. Das ist kein Befund an diesem
  Paket -- seine `dateien`-Liste enthaelt nur `werkzeugkette.cmake`, eine Probe waere
  darin nicht unterzubringen --, aber es ist der Grund, warum die vierzehn Baeume oben
  im Nachbau unter `befunde/pruefung-0066/` liegen bleiben.
