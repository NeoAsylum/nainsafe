---
typ: pruefung
paket: 0063-sperrliste-je-wort-statt-je-eintrag
pruefer: kern-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Alle drei Abnahmebedingungen einzeln nachgefahren -- jede Rotmeldung gegen den Stand vor der Aenderung gegengeprobt, die Unveraendertheit ueber einen sha256-gleichen Bytevergleich aller 45 erzeugten Schalterzeilen des Arbeitsbereichs.
befunde: 0
---

# Pruefung 0063 -- Sperrliste je Wort statt je Eintrag

Geaendert ist `werkzeugkette.cmake`, Zeilen 311-366: der zweite Durchgang von
`fabrik_schlussriegel` zerlegt jeden Eintrag von `COMPILE_OPTIONS` vor dem Abgleich in
Woerter und nennt den Eintrag zusaetzlich zum getroffenen Wort. Der erste Durchgang
(`luecke`) ist unberuehrt, die Sperrliste `pauschalmuster` ebenfalls.

**Der Commit-Betreff luegt zum siebten Mal.** `b1ce529 kernbauer: 0063-...` traegt nur
`notizen/kernbauer.md`. Die Aenderung selbst steht in `3b0e1ee` mit dem Betreff
`testentwickler: 0061-kernanker-sichtbarkeit`; `cff60c2` hat danach noch eine Leerzeile
angehaengt. Der Vorzustand fuer jede Gegenprobe ist deshalb
`1a4d240:.../werkzeugkette.cmake` -- der Stand nach 0060, maschinell bestimmt ueber
`git log -S 'separate_arguments(worte'`.

Alle Messungen am 2026-09-04, cmake 4.2.3, g++ 15.2.0, in `$TMPDIR/p0063` ausserhalb des
Repos (Nachweisort Rang 1). Wegwerf-Quelle in jedem Baum, wie in 0060:
`int f(double d){ int i = d; return i; }`.

## Positivkontrolle vorweg

Ohne Abschalter ist diese Quelle rot -- an beiden Staenden gleich:

```
kein zusaetzlicher Schalter   Bau CODE=2
   z.cpp:1:26: error: conversion from 'double' to 'int' may change value
                     [-Werror=float-conversion]
```

Erst dadurch heisst "0 Diagnosen" in den Gegenproben unten *der Abschalter hat gewirkt*
und nicht *hier war ohnehin nichts zu melden*.

## Bedingung 1 -- `SHELL:` wird gefangen: erfuellt

```
target_compile_options(z PRIVATE "SHELL:-Wno-error -w")

nachher   Konfiguration CODE=1
          | hebt den Satz wieder auf: -Wno-error -w
          | im Eintrag:               SHELL:-Wno-error -w
vorher    Konfiguration CODE=0
          | -- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft,
          |    alle mit Warnsatz und ohne Pauschalabschalter.
          Bau CODE=0, 0 Diagnosen
          CXX_FLAGS = ... -fwrapv -fno-fast-math -Wno-error -w
```

Die Schalterzeile ist der dritte, von meinen Laeufen unabhaengige Zeuge: Der Abschalter
stand nicht nur in der Beschreibung, er kam beim Uebersetzer an.

## Bedingung 2 -- der Generatorausdruck ebenso: erfuellt

```
"$<1:-w>"                    nachher CODE=1  | hebt den Satz wieder auf: -w
                                             | im Eintrag: $<1:-w>
                             vorher  CODE=0, Bau CODE=0, 0 Diagnosen, CXX_FLAGS ... -w
"$<$<CONFIG:Release>:-w>"    nachher CODE=1  | hebt den Satz wieder auf: -w
                                             | im Eintrag: $<$<CONFIG:Release>:-w>
                             vorher  CODE=0, Bau CODE=0, 0 Diagnosen, CXX_FLAGS ... -w
```

Konfiguriert wurde in `Release`, damit die Bedingung des zweiten Ausdrucks ueberhaupt
greift; sonst haette der stille Bau auch ohne Luecke stillgestanden.

## Bedingung 3 -- nichts wird ueber-scharf: erfuellt

**Der einzeln unterdrueckte Schalter.** `-Wno-conversion` an einem Ziel mit Satz:
Konfiguration CODE=0, Bau CODE=0 -- vorher wie nachher wortgleich.

**Die drei Bauwege**, konfiguriert mit genau den Schaltern des Runners
(`baulauf.py:162-164`: `-DCMAKE_BUILD_TYPE=RelWithDebInfo`,
`-DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math`):

| Bauweg | vorher | nachher |
|---|---|---|
| Arbeitsbereich | CODE=0, **15** | CODE=0, **15** |
| `kern` allein | CODE=0, **10** | CODE=0, **10** |
| `pruefstand` allein | CODE=0, **5** | CODE=0, **5** |

**15 / 10 / 5.** 15 >= 10 + 5, die Differenz ist null -- es gibt kein Mitglied aus
`FABRIK_MITGLIEDER` zu nennen. Der Arbeitsbereich meldet `daten`, `schnittstelle`,
`konsole`, `oberflaeche` und `werkzeuge/aufbereitung` als noch nicht gebaut, es bleiben
`kern` und `pruefstand`. Unabhaengiger Zeuge fuer die 15: Der erzeugte Baum enthaelt
genau 15 `flags.make` mit einer `CXX_FLAGS`-Zeile.

**Der Bytevergleich.** Zweimal `git archive HEAD <venture>` nach `$TMPDIR`, in einer
Kopie allein `werkzeugkette.cmake` durch den Stand `1a4d240` ersetzt. `diff -rq` ueber
beide Baeume: **genau eine** abweichende Datei. Beide konfiguriert, dann alle
`CXX_FLAGS`-, `CXX_DEFINES`- und `CXX_INCLUDES`-Zeilen aller `flags.make` eingesammelt,
Baumwurzel und Bauverzeichnis textlich normalisiert:

```
45 Zeilen vorher, 45 nachher, bytegleich
sha256 beide: e3d9b02bc1eff12d1088117ddb289d28ffa8fb8ee009f634c8a905c6d3a5981c
```

**Bau und Proben.** Arbeitsbereich, Stand nachher: `cmake --build --parallel` CODE=0 mit
0 Diagnosen, `ctest` CODE=0, 11 von 11 Proben bestanden. Dasselbe im zweiten Profil
(`Debug`): Riegel 15, Bau CODE=0, 0 Diagnosen, 11 von 11.

**Die vier Schalter, die der Kommentar als harmlos behauptet** (Zeilen 324-326), einzeln
gemessen, alle Konfiguration CODE=0 und vorher wie nachher gleich: `-Wall` (steht in
jedem Fall im Satz), `-Wno-conversion`, `-fsanitize=undefined,address`,
`-fno-sanitize-recover=all`. Dazu zwei, die die Zerlegung haetten zerschlagen koennen und
es nicht tun: `SHELL:-Wno-conversion -Wall` und
`$<$<COMPILE_LANGUAGE:CXX>:-Wno-conversion>`, beide CODE=0.

**Was 0060 schon fing, faengt es weiter.** `-w` und `-Wno-error=conversion` je an einem
Ziel: CODE=1, vorher wie nachher mit demselben Meldungstext. Bei beiden ist das Wort mit
dem Eintrag identisch, und die Zeile `im Eintrag:` bleibt richtigerweise weg -- die
Bedingung in Zeile 363 traegt.

## Was die Aenderung ueber ihre Abnahme hinaus faengt

Nicht gefordert, aber gemessen und gruen: `$<IF:$<CONFIG:Debug>,-w,-Wall>` (CODE=1) und
`add_compile_options(-w)` auf Verzeichnisebene vor dem Ziel (CODE=1). Bei gemischten
Eintraegen -- `-w "$<1:-Wno-error>"` -- nennt die Meldung beide Woerter *und* beide
Eintraege:

```
hebt den Satz wieder auf: -w -Wno-error
im Eintrag:               -w $<1:-Wno-error>
```

Am Stand vorher nannte derselbe Fall nur `-w`, der zweite Abschalter blieb ungenannt.

## Gemessene Grenzen, die keine Befunde sind

- **`-Wa,-w` loest jetzt einen Fehlalarm aus** (CODE=1). Das Komma ist Trenner, `-w` wird
  als eigenes Wort gefunden, obwohl der Schalter nur den Assembler betrifft und `-Werror`
  unangetastet laesst. Kein Befund: Der Schalter kommt in diesem Vorhaben nirgends vor,
  das Paket nennt den Fehlalarm als bewusst in Kauf genommenen Preis, und er ist **laut**
  -- die stille Richtung waere die toedliche.
- **Ein Schalter, dessen Wert ` -w ` in Anfuehrungszeichen enthaelt**, loest keinen
  Fehlalarm aus: `-DCMD="g++ -w"` konfiguriert CODE=0, und der Bau wird korrekt rot.
  `separate_arguments(... UNIX_COMMAND)` fasst den Anfuehrungsblock zu einem Wort.
- **Die beiden Bauwege, die die Abnahme nicht nennt**, sind unberuehrt:
  `werkzeuge/belegstellen` (CODE=0, vorher wie nachher) und
  `pruefstand/bau/pruefung-0019` binden `werkzeugkette.cmake` nicht ein, der Riegel
  laeuft dort gar nicht.

## Was ich nicht geprueft habe

- Den Weg ueber `CMAKE_CXX_FLAGS` von aussen und ueber die Kommandozeile. Beide stehen im
  Paket ausdruecklich unter "Was nicht dazugehoert".
- Den ersten Durchgang (`luecke`) auf Generatorausdruecke -- ebenfalls ausgenommen, und
  der Quelltext begruendet die Ausnahme in Zeile 328-332 richtig: Dort wird Anwesenheit
  geprueft, ein Irrtum faellt also nach rot.
- Windows- oder Nicht-GNU-Werkzeugketten. `werkzeugkette.cmake` schliesst sie ab Zeile 30
  selbst aus.

## Vorschlag aus diesem Lauf

`aufgaben/0064-schlussriegel-liest-nur-eine-eigenschaft.md`, `status: vorschlag`. Drei
gemessene Wege, auf denen `-w` beim Uebersetzer ankommt und der Riegel gruen meldet --
alle drei ausserhalb von `COMPILE_OPTIONS` des Ziels und damit ausserhalb der Frage, die
0063 beantwortet.
