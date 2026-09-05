---
id: 0134-sperrebindung-jeder-kernquelle
rolle: kernbauer
status: fertig
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/CMakeLists.txt]
abnahme: Das Konfigurieren des Kerns bricht ab, sobald eine Quelle unter `kern/src` den Kopf `kern/sperre.hpp` nicht bindet oder ihn nicht als letzten `#include` bindet; die Abbruchmeldung nennt den Dateinamen und sagt, welche der beiden Bedingungen verletzt ist. Drei Baeume, jeder einzeln zu fahren: der unveraenderte Baum konfiguriert und laeuft in beiden Profilen gruen; ein Baum mit einer zusaetzlichen Quelle ohne die Include-Zeile bricht beim Konfigurieren ab; ein Baum mit einer zusaetzlichen Quelle, die die Zeile traegt, aber nicht an letzter Stelle, bricht ebenso ab. Der erste Baum ist nicht wegzulassen -- ein Riegel, der alles verbietet, sieht im Negativtest identisch aus.
---

# Beide Rechensperren des Kerns haengen an einer Regel, die nichts haelt

## GEBAUT -- 2026-09-05, kernbauer

Der Riegel steht in `kern/CMakeLists.txt` zwischen dem Quellensammler und
`add_library(kern ...)`. 99 Zeilen hinzugefuegt, 0 entfernt -- die alte Datei ist Zeile
fuer Zeile erhalten, verglichen gegen eine Kopie des Standes vor dem Lauf und nicht
gegen `HEAD` (ein Fremdlauf hat die Aenderung unter Commit `3840367` mitgenommen).

Nachweis: `befunde/messung-0134/` -- `bindungsriegel.py` faehrt die Baeume,
`lauf-2026-09-05.txt` ist die Ausgabe im Wortlaut (Exitcode 0, 0 Abweichungen),
`nachweis.md` ordnet sie den Abnahmebedingungen zu. Kurz:

- **Baum 1** unveraendert mit Riegel: `kern` allein und Arbeitsbereich, je
  `FABRIK_SANITIZER=ON` und `OFF` -- vier Laeufe, alle Schritte Code 0.
- **Baum 3** Quelle ohne die Zeile: `cmake -S` Code 1, Meldung nennt Datei und Bedingung.
- **Baum 5** Zeile nicht zuletzt: `cmake -S` Code 1, Meldung nennt Datei, die andere
  Bedingung und den tatsaechlichen Schluss.
- **Baum 2 und 4** dieselben Verstoesse ohne Riegel: beide gruen. Ohne sie wirkte die
  Aenderung womoeglich dadurch, dass sie alles faengt.
- **Baum 6 und 7** Include-Zeile aus einer *vorhandenen* Quelle entfernt, danach nur
  `cmake --build`: ohne `CMAKE_CONFIGURE_DEPENDS` gruen, mit ihm Abbruch.

Entschieden und im Kommentar begruendet: Der Riegel deckt `kern/src`, nicht
`kern/test` -- die kleinere Fassung, die die Abnahme verlangt. Ein zweites Vorkommen
des Kopfes weiter oben faengt er nicht ab; `#pragma once` macht es folgenlos, und die
Reihenfolgebedingung haelt trotzdem.

## ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`, ohne Sperre

**Vier Pruefungen bestanden.** `kernbauer` steht in `BAUROLLEN`, der Runner plant sie ein.
Die `dateien`-Liste nennt eine einzige Datei, und kein offenes Paket haelt sie -- selbst
nachgemessen ueber die `dateien`-Listen aller Pakete, nicht aus dem Vorschlag uebernommen.
Die `abnahme` ist pruefbar, nennt drei einzeln zu fahrende Baeume und keinen
ausgeschriebenen Zahlwert. `haengt_an` bleibt leer, also laeuft es sofort.

**Die Praemisse habe ich selbst nachgemessen und nicht abgeschrieben:** `kern/CMakeLists.txt`
liest die Kernquellen in Zeile 51 mit `file(GLOB ... CONFIGURE_DEPENDS src/*.cpp)` ein und
uebergibt sie in Zeile 54 und 72 unveraendert an beide Bibliotheken. Eine Pruefung auf die
Bindung von `kern/sperre.hpp` steht nirgends in der Datei. Der geschilderte Weg in die
Bibliothek ist damit offen, wie beschrieben.

**Der Positivbaum ist die tragende Bedingung, nicht das Beiwerk.** Ein Riegel, der alles
verbietet, besteht beide Negativbaeume und faellt nur am ersten auf. Wer ihn weglaesst, hat
nichts nachgewiesen.

**Vorgeschlagen am 2026-09-05 vom `kern-pruefer` aus der Pruefung zu Paket 0122
(`urteil: geprueft`, `befunde: 0`).** Das Paket ist in Ordnung. Dieser Vorschlag
betrifft die Voraussetzung, auf die es sich stuetzt.

## Der Sachverhalt

`sperre.hpp` wirkt ab der Zeile, an der es eingebunden wird, bis zum Ende der
Uebersetzungseinheit. Daraus folgt die Einbauregel: Der Kopf ist der **letzte**
`#include` jeder Kernquelle. Der Kopftext nennt sie seit 0122 ausdruecklich den ganzen
Trick, und das ist nicht uebertrieben -- sie ist der Grund, warum die Sperre ohne
Ausnahmeliste auskommt. `festkomma.hpp` darf die vergifteten Bausteine benutzen, weil
es fertig gelesen ist, bevor die Vergiftung gilt.

Gehalten wird diese Regel von nichts. Im Kopf steht ein Suchbefehl als Nachweis, und
ein Suchbefehl in einem Kommentar laeuft nur, wenn ihn jemand liest und tippt.

## Gemessen, nicht behauptet

Ein Baum aus dem geprueften `HEAD` bekommt eine neue Datei `kern/src/luecke.cpp`. Sie
bindet `kern/sperre.hpp` **nicht** und enthaelt beides, was der Kern verbietet: eine
Rechnung auf `double` (gegen T4) und eine eigene Fassung der Strichrechnung mit
`__builtin_add_overflow` (gegen T7 Massnahme 4.2).

Ergebnis: Der Quellensammler des Kerns liest sie auf, sie wird in `kern` **und** in
`kern_geprueft` uebersetzt, und der Lauf ist gruen -- jede Probe bestanden, Profil
`ON`. Beide Sperren greifen an ihr nicht, weil sie fuer diese Uebersetzungseinheit
schlicht nicht existieren.

Der Sammler ist dabei kein Nebenumstand, sondern die halbe Ursache: Er liest die
Quellen ein, statt sie aufzuzaehlen, und das mit Nachschau bei jedem Bau. Eine neue
Kernquelle kommt also ohne jeden Eingriff in eine Bauliste in die Bibliothek -- was
gewollt ist, damit kein spaeteres Paket die Bauliste anfassen muss. Der Preis ist, dass
auch eine Quelle **ohne** die Sperre ohne jeden Eingriff hineinkommt.

## Warum das jetzt faellt und nicht spaeter

Bis zum 2026-09-05 hing an der Regel **eine** Vorgabe, T4. Seit 0122 haengen **zwei**
daran, T4 und T7 Massnahme 4.2. Die Kosten eines Verstosses sind bei der zweiten
hoeher: Gleitkomma im Kern faellt frueher oder spaeter an einer abweichenden Zahl auf,
eine zweite Fassung der Strichrechnung dagegen rechnet meistens richtig -- und bricht
im Ueberlauffall unter `-fwrapv` **still** um, statt abzubrechen. Das ist der
Unterschied zwischen einem roten Lauf und einem falschen Ergebnis in Runde 400, und
0122 fuehrt ihn in seiner eigenen Begruendung als Grund an, warum es die Sperre gibt.

Heute ist der billige Tag: Alle Quellen unter `kern/src` und alle Proben unter
`kern/test` halten die Regel bereits, jede bindet den Kopf genau einmal und an letzter
Stelle. Der Riegel wird also sofort gruen und muss nichts aufraeumen. Nach der ersten
Quelle, die die Regel bricht, ist es Nachfuehrung -- derselbe Verlauf, den die
Belegstellen (0059 nach sechs Paketen Handnachfuehrung) und der Warnsatz (0046, 0058,
0060) im Repo schon vorgezeichnet haben.

## Die Bauform

Eine Pruefschleife beim Konfigurieren, in derselben Datei, in der die Quellen
eingesammelt werden -- also unmittelbar neben der Stelle, die das Problem erzeugt. Fuer
jede eingesammelte Quelle: Datei lesen, die Include-Zeilen heraussuchen, pruefen, dass
die Zeile mit `kern/sperre.hpp` genau einmal vorkommt und die letzte davon ist.
Andernfalls abbrechen und den Dateinamen nennen.

Zwei Gruende, warum die Pruefung dorthin gehoert und nicht in den Belegstellenriegel:
Sie braucht keine Uebersetzung und kein eigenes Binaerprogramm, und sie schlaegt zu,
**bevor** gebaut wird statt danach. Dazu ein praktischer: Auf
`werkzeuge/belegstellen/belegstellen_riegel.cpp` liegen heute sieben offene Pakete, auf
`kern/CMakeLists.txt` keines.

Ob der Riegel auch die Proben unter `kern/test` erfassen soll, entscheidet der
Bauagent. Sie halten die Regel heute ebenso, und die Abnahme verlangt sie nicht -- ein
Riegel, der nur die Bibliotheksquellen deckt, ist die kleinere und ausreichende
Fassung. Wer beide nimmt, nimmt mehr, aber nicht weniger.

## Warum ein eigenes Paket

Nicht Teil von 0122: Dessen Dateiliste nennt genau eine Datei, `kern/sperre.hpp`, und
sein Abnahmekriterium ist erfuellt. Die Luecke liegt in `kern/CMakeLists.txt` und ist
aelter als das Paket -- sie stammt aus der Zeit von T4 und war bis zum 2026-09-05
billiger.

Nicht Teil von 0074: Das ist ein Architektenpaket auf `technik.md` mit dem
ausdruecklichen Satz, dass kein Code entsteht, und es behandelt Massnahme 4.3, die
Operatorfrage. Hier geht es um keine Rechenart, sondern um die Bindung eines Kopfes.

Nicht Teil eines Belegstellenpakets: Die Regel ist keine Belegstelle. Sie ist eine
Bedingung an die Uebersetzungseinheit, und ihr Bruch ist kein toter Verweis, sondern
eine ausgeschaltete Sperre.

## Was ausdruecklich nicht dazugehoert

Keine Erweiterung der vergifteten Bezeichnerliste, kein Anfassen von `sperre.hpp`,
keine Sperre fuer Operatoren. Der Riegel prueft, **dass** der Kopf gebunden ist, und
sagt nichts darueber, **was** er sperrt.
