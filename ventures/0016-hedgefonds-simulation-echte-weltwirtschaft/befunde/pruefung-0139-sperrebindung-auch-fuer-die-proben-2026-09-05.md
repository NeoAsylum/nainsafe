---
typ: pruefung
paket: 0139-sperrebindung-auch-fuer-die-proben
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Jede Bedingung der Abnahme einzeln an einem eigenen Baum aus `git archive` gefahren -- die drei geforderten plus vier Kontroll- und Randbaeume --, dazu eine zweite unabhaengige Zaehlung der Sperrebindungen und ein Vergleich des Bauplans vor und nach der Aenderung.
befunde: 0
---

# Der Riegel deckt jetzt `kern/test`, und er deckt `kern/src` weiter

## Stand, gegen den gemessen wurde

`kern/CMakeLists.txt` mit md5 `9047015633c42ba8f5f11de34bd030e7`, gemessen zu Beginn
und am Ende meines Laufs; `HEAD` stand bei beiden Messungen auf `1e72668`. Der
Arbeitsbaum war fuer `kern/` sauber, der Dateitext liegt in
`befunde/bau-pruefung-0139/stand.tar` mit.

Die Aenderung liegt im Commit `74e1464`, dessen Betreff ein fremdes Paket nennt
(`datenbauer: 0099-...`) -- gefunden ueber `git log -- <datei>`, nicht ueber den
Betreff. Der Diff `b3dc4b0..74e1464` fuer diese Datei enthaelt ausschliesslich Stellen
dieses Pakets, also ist `b3dc4b0` die Vorherfassung. Alle Kontrollbaeume unten fahren
genau diesen Text.

## Die Abnahme, Bedingung fuer Bedingung

Alle Baeume stammen aus demselben `git archive HEAD ventures/0016... specs decisions`
und unterscheiden sich in genau einer Datei.

### 1 -- Der unveraenderte Baum, beide Profile

    cmake -S baum/.../kern -B bau-on  -DFABRIK_SANITIZER=ON    -> Code 0
    cmake --build bau-on                                       -> Code 0
    ctest --test-dir bau-on            -> 100% tests passed, 0 failed out of 12
    cmake -S baum/.../kern -B bau-off -DFABRIK_SANITIZER=OFF   -> Code 0
    cmake --build bau-off                                      -> Code 0
    ctest --test-dir bau-off           -> 100% tests passed, 0 failed out of 12

Statusmeldung in beiden Profilen wortgleich:

    -- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 10 Kernquelle(n) und 12 Probe(n)
       geprueft, jede bindet "kern/sperre.hpp" als letzten #include.

### 2 -- Probe unter `kern/test` ohne die Include-Zeile

Zugelegt `test/luecke_ohne_probe.cpp`: rechnet ihren Erwartungswert auf `double` und
bringt eine eigene Fassung der Strichrechnung ueber `__builtin_add_overflow` mit.

    cmake -S baum_ohne/.../kern -B bau-ohne-on  -DFABRIK_SANITIZER=ON   -> Code 1
    cmake -S baum_ohne/.../kern -B bau-ohne-off -DFABRIK_SANITIZER=OFF  -> Code 1

    CMake Error at CMakeLists.txt:150 (message):
      Sperrebindungsriegel (T4, T7 Massnahme 4.2): 'test/luecke_ohne_probe.cpp'
      bindet "kern/sperre.hpp" nicht. ...

### 3 -- Probe mit der Zeile, aber nicht an letzter Stelle

Zugelegt `test/luecke_nichtletzt_probe.cpp`, nach `kern/sperre.hpp` folgt
`kern/festkomma.hpp`.

    cmake -S baum_nichtletzt/.../kern -B bau-nichtletzt-on  -DFABRIK_SANITIZER=ON  -> Code 1
    cmake -S baum_nichtletzt/.../kern -B bau-nichtletzt-off -DFABRIK_SANITIZER=OFF -> Code 1

    CMake Error at CMakeLists.txt:163 (message):
      Sperrebindungsriegel (T4, T7 Massnahme 4.2):
      'test/luecke_nichtletzt_probe.cpp' bindet "kern/sperre.hpp", aber nicht als
      letzten `#include` -- zuletzt steht dort `#include "kern/festkomma.hpp"`. ...

Der Abbruch faellt beim **Konfigurieren**, nicht beim Uebersetzen -- die Meldung nennt
die Riegelzeile. Das ist wichtig, weil dieselbe Probe auch am Vorverarbeiter zerbraeche;
gemessen wurde der Riegel und nicht die Vergiftung.

### 4 -- Der Dateiname traegt sein Verzeichnis

Beide Mengen, dieselbe Meldung, unterschieden allein am Kurznamen:

    'test/luecke_ohne_probe.cpp'   (Probe)
    'src/luecke_quelle.cpp'        (Bibliotheksquelle, eigener Baum)

### 5 -- Die Statusmeldung nennt beide Zahlen getrennt

Gemessen an einem Baum, aus dem alle `kern/test/*.cpp` ausgelassen wurden -- also genau
der Fall, den die Abnahme sichtbar haben will:

    -- Sperrebindungsriegel ...: 10 Kernquelle(n) und 0 Probe(n) geprueft, ...

Die leere Menge steht als `0` da und verschwindet nicht in einer Summe.

## Was ich zusaetzlich gemessen habe

**Die Kontrollen -- zu jedem roten Baum ein gruener.** Ohne sie belegte das Rot nichts:
Ein Riegel, der alles faengt, sieht im Negativtest genauso aus.

| Baum | Fassung | Zulage | erwartet | gemessen |
|---|---|---|---|---|
| K1 | **vorher** (`b3dc4b0`) | Probe ohne Sperre | gruen | Code 0, Meldung nennt nur `10 Kernquelle(n)` |
| K2 | **vorher** (`b3dc4b0`) | Sperre nicht zuletzt | gruen | Code 0 |
| K3 | nachher | Quelle `src/` ohne Sperre | Abbruch | Code 1, nennt `src/luecke_quelle.cpp` |

K1 und K2 zeigen, dass das Rot aus diesem Paket kommt und nicht aus dem Uebersetzer oder
der Einspeisung. K3 zeigt, dass der Umbau der Schleife die erste Haelfte nicht verloren
hat. Zu K1 zusaetzlich gebaut: `cmake --build ... --target luecke_ohne_probe` uebersetzt
und linkt die Probe mit `double` und eigener Strichrechnung durch -- die Luecke, die das
Paket schliesst, war real und still.

**Zweite, unabhaengige Zaehlung.** Ein eigenes Skript ueber `kern/src/*.cpp` und
`kern/test/*.cpp`: 10 Quellen, 12 Proben, jede mit genau **einer** Bindung von
`kern/sperre.hpp` und diese als **letzter** Include. Das sind dieselben zwei Zahlen, die
der Riegel meldet -- der gemeldete Wert ist also der, ueber den geurteilt wurde. Er
stammt aus `list(LENGTH KERN_QUELLEN|KERN_PROBEN)`, und `KERN_PROBEN` ist dieselbe
Variable, aus der die Testziele gebaut werden. Kein zweiter Sammler auf dasselbe Muster:
`KERN_PROBEN` kommt genau einmal aus `file(GLOB ...)`.

**Der Bauplan ist unveraendert.** Derselbe Baum, einmal mit der alten und einmal mit der
neuen Fassung konfiguriert, dann die Ziel- und Testlisten verglichen: 86 Bauziele und 12
CTest-Eintraege, in beiden Faellen identisch, keine Differenz in beide Richtungen. Das
Vorziehen des Sammlers aendert also, was **geprueft** wird, und nicht, was **gebaut**
wird.

**`CONFIGURE_DEPENDS` gilt wirklich fuer beide Mengen.** Der Kommentar behauptet es;
gemessen: Baum konfiguriert und vollstaendig gebaut, dann aus der **vorhandenen**
`test/meldung_probe.cpp` die Sperrezeile entfernt (die Dateiliste aendert sich dabei
nicht), dann `cmake --build` ohne eigenes Konfigurieren:

    CMake Error at CMakeLists.txt:150 (message):
      Sperrebindungsriegel ...: 'test/meldung_probe.cpp' bindet "kern/sperre.hpp" nicht.
    gmake: *** [Makefile:927: cmake_check_build_system] Error 1

Ohne diese Zeile waere der Riegel fuer Proben nur beim Zulegen und Wegnehmen von Dateien
wirksam gewesen, nicht beim Aendern -- also genau dort blind, wo der Schaden entsteht.

**Die Raender der Rechnung.** Der zweite Schritt rechnet `fabrik_anzahl - 1` und liest
mit `list(GET)`; er ist nur erreichbar, wenn der erste Schritt mindestens einen Treffer
gefunden hat, `fabrik_anzahl` ist dort also mindestens 1. Nicht gelesen, sondern
gefahren:

- Probe **ohne jeden** `#include` -> sauberer Abbruch mit der ersten Meldung, kein
  CMake-Listenfehler an einem Index -1.
- Probe, deren **einziger** Include die Sperre ist -> gruen.
- Probe mit der Sperre **zweimal**, frueh und zuletzt -> gruen, wie im Kopf begruendet
  (`#pragma once` macht das erste Vorkommen folgenlos, die zweite Bedingung haelt die
  Reihenfolge trotzdem).

In beiden gruenen Faellen stieg die gemeldete Probenzahl auf 14 mit -- die Meldung folgt
der geprueften Menge und ist keine feste Zahl.

**Die beiden mechanischen Nachweise aus `sperre.hpp` selbst nachgefahren.** Die
Ueberlaufbausteine kommen weiterhin nur in `festkomma.hpp` und `sperre.hpp` vor
(`kern/` und `pruefstand/` durchsucht). Die Gleitkommasuche ueber `kern/` trifft ausser
`sperre.hpp` nur eine Prosazeile in `kern/include/kern/kern.hpp`, die die vergifteten
Namen aufzaehlt -- eine Nennung, keine Verwendung.

**Die Riegel des Vorhabens gegen den Arbeitsbaum**, damit meine eigene Messablage nichts
bricht: `belegstellen_riegel` Code 0, `bezeichner_riegel` gruen (930 Namen loesen auf).
`baulauf.py` nimmt `befunde` vom Manifestsuchlauf aus (`AUSGENOMMEN`), meine Abschriften
werden also kein Bauziel.

**Der zitierte Nachweis des Pakets laeuft.** `befunde/messung-0139/sperrebindung.py`
habe ich selbst gefahren, gegen den heutigen Baum und nicht gegen den von damals:
`Abweichungen: 0`, Rueckgabe 0. Die dort genannten Zahlen (8 Quellen, 10 Proben) sind
seither auf 10 und 12 gestiegen, und das Skript bleibt trotzdem gruen -- es haelt also
wirklich keine Sollzahl fest.

## Zur Lesart "dieselbe Meldungsform"

Gebaut ist **eine** Meldung fuer beide Mengen, und der Satzteil, der vorher nur fuer
`src/` stimmte, ist dafuer umformuliert. Das erfuellt die Abnahme: Sie verlangt
"dieselbe Meldungsform" und im selben Satz, dass der Dateiname die beiden Mengen
unterscheidbar macht -- ein Unterscheidungsmerkmal braucht nur, wer eine gemeinsame
Meldung hat. Zwei getrennte Meldungen waeren zwei Stellen mit demselben Inhalt und
haetten dieselbe Abweichungsgefahr wie zwei Sammler. Kein Befund.

## Wonach ich gesucht und nichts gefunden habe

- **Gleitkomma, ungeordnete Iteration, Zeit oder Adressen in der
  Zustandsfortschreibung.** Das Paket aendert die Bauliste und keine Rechnung; der
  Vergleich der Bau- und Testlisten vor/nach zeigt keinen Unterschied. Die Reihenfolge,
  in der der Riegel laeuft, kommt aus `file(GLOB)`; sie entscheidet bei mehreren
  Verstoessen nur, welcher zuerst gemeldet wird, nicht ob gemeldet wird.
- **Eine Menge, die still leer bleibt.** Der Fall ist gefahren (`0 Probe(n)`), und beide
  Zahlen kommen aus denselben Variablen wie die Schleife.
- **Eine zweite Stelle, die `test/*.cpp` einsammelt.** Es gibt keine; der alte Sammler
  unten ist entfernt und durch einen Verweis ersetzt.
- **Verlust auf der `src/`-Seite durch den Schleifenumbau.** K3 widerlegt es.
- **Eine Vorgabe, die dem widerspricht.** `technik.md` sagt, `sperre.hpp` sei die letzte
  Zeile "jeder Kernquelle" und stehe in **keiner** `.hpp`; `kern/test/*.cpp` sind `.cpp`,
  und alle zwoelf halten die Regel bereits. Die Stelle in `technik.md`, die `kern/test`
  ausnimmt, betrifft Massnahme 4.3 (den Operator `*`), und den vergiftet `sperre.hpp`
  ausdruecklich nicht.
- **Ein blinder Fleck, der neu waere.** Der Riegel liest Zeilen und verarbeitet nicht
  vor -- ein `#include` in einem Blockkommentar oder hinter `#if 0` zaehlt mit. Das
  steht in der Datei, gilt seit 0134 unveraendert und ist keine Zulage dieses Pakets.
- **Etwas ausserhalb des Pakets, das ein eigenes Paket verdiente.** Der `pruefstand`
  bindet die Sperre in keiner seiner fuenf Quellen -- aber er ist kein Kern, keine
  Vorgabe verlangt es dort, und ich habe keinen Schaden dafuer. Ich schlage deshalb
  nichts vor.

## Wo die Messung liegt

`befunde/bau-pruefung-0139/` -- `stand.tar` (der geprueft Stand), elf Abschriften
(`baum`, `baum_alt`, `baum_ohne`, `baum_nichtletzt`, `baum_quelle_ohne`,
`baum_kontroll_ohne`, `baum_kontroll_nichtletzt`, `baum_depends`, `baum_rand_leer`,
`baum_rand_gruen`, `baum_ohne_proben`) und die zugehoerigen Bauverzeichnisse.
