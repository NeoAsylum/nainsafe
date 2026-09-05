---
id: 0139-sperrebindung-auch-fuer-die-proben
rolle: kernbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/CMakeLists.txt]
abnahme: Der Sperrebindungsriegel deckt zusaetzlich `kern/test/*.cpp` mit denselben zwei Bedingungen und derselben Meldungsform; die Abbruchmeldung nennt den Dateinamen mitsamt seinem Verzeichnis, sodass eine Probe von einer Bibliotheksquelle zu unterscheiden ist. Drei Baeume, jeder einzeln zu fahren: der unveraenderte Baum konfiguriert, baut und testet gruen in beiden Profilen; ein Baum mit einer zusaetzlichen Probe unter `kern/test` ohne die Include-Zeile bricht beim Konfigurieren ab; ein Baum mit einer zusaetzlichen Probe, die die Zeile traegt, aber nicht an letzter Stelle, bricht ebenso ab. Die Statusmeldung nennt beide Zahlen getrennt -- Quellen und Proben --, damit ein Riegel, der eine der beiden Mengen leer laesst, nicht wie einer aussieht, der beide prueft.
---

# Der Riegel deckt `kern/src`, die Regel gilt fuer `kern/`

## Vorgeschlagen am 2026-09-05 vom `kern-pruefer` aus der Pruefung zu Paket 0134

Paket 0134 ist in Ordnung -- `urteil: geprueft`, `befunde: 0`. Sein Abnahmekriterium
nennt `kern/src`, und der Rumpf ueberlaesst die Frage ausdruecklich dem Bauagenten:
*"Ob der Riegel auch die Proben unter `kern/test` erfassen soll, entscheidet der
Bauagent."* Er hat die kleinere Fassung gewaehlt, wie erlaubt. Dieser Vorschlag ficht
das nicht an, sondern nimmt den offen gelassenen Teil auf.

## Der Sachverhalt, gemessen

`kern/CMakeLists.txt` Zeile 104 laeuft ueber `KERN_QUELLEN`, und das ist
`src/*.cpp` (Zeile 51). `kern/test/*.cpp` wird erst in Zeile 185 eingesammelt, nach dem
Riegel, und von ihm nie gelesen.

Gemessen am 2026-09-05 an einer Abschrift des Kerns, in die
`kern/include/kern/festkomma.hpp` als `kern/test/luecke_probe.cpp` gelegt wurde -- eine
Probe also, die `kern/sperre.hpp` nicht bindet:

    cmake -S <abschrift>/kern -B <bau> -DFABRIK_SANITIZER=ON      -> Code 0
    -- Sperrebindungsriegel (T4, T7 Massnahme 4.2): 8 Kernquelle(n) geprueft, ...

Code 0, und die Zahl steht weiter auf 8. Die Probe kommt ohne jeden Eingriff in den
Baum, genau wie die Bibliotheksquelle vor Paket 0134.

## Warum das nicht nur Symmetrie ist

Die Regel, die der Riegel haelt, ist nicht auf `src/` geschrieben. `sperre.hpp` fuehrt
als mechanischen Nachweis fuer T4 einen Suchbefehl ueber `kern/` -- nicht ueber
`kern/src/` -- und alle zehn Proben binden den Kopf heute, jede genau einmal und an
letzter Stelle. Der Baum haelt die Regel also bereits fuer beide Mengen; nur die eine
Haelfte wird gehalten.

**Und die Proben sind die teurere Haelfte, nicht die billigere.** Was eine
Bibliotheksquelle falsch rechnet, faellt an einer Probe auf. Was eine **Probe** falsch
rechnet, faellt an nichts auf: Sie ist die Stelle, die den Sollwert nennt. Eine Probe,
die ihren Erwartungswert in `double` ausrechnet oder eine eigene Fassung der
Strichrechnung mitbringt, ist gruen -- und deckt von da an die Abweichung zu, gegen die
sie geschrieben wurde. Das ist derselbe Unterschied, mit dem Paket 0134 begruendet ist
(roter Lauf gegen falsches Ergebnis in Runde 400), nur eine Ebene weiter aussen.

Dazu kommt, dass die Proben `kern_geprueft` linken -- den Kasten, an dem die Sanitizer
haengen. Eine ungesperrte Probe rechnet mit denselben Werten wie der Kern und liegt
naeher an ihm als jedes andere Verzeichnis des Vorhabens.

## Heute ist wieder der billige Tag

Dasselbe Argument wie in 0134 und aus demselben Grund pruefbar: Alle zehn Proben unter
`kern/test` halten die Regel bereits (nachgesehen am 2026-09-05, jede bindet
`kern/sperre.hpp`, und in keiner Datei des Vorhabens folgt auf die Bindung noch ein
`#include`). Der erweiterte Riegel wird sofort gruen und muss nichts aufraeumen. Nach
der ersten Probe, die die Regel bricht, ist es Handnachfuehrung -- der Verlauf, den
0059 (Belegstellen, sechs Pakete Nachfuehrung) und 0046/0058/0060 (Warnsatz) im Repo
schon zweimal vorgezeichnet haben.

## Warum ein eigenes Paket

**Nicht Teil von 0134.** Dessen Abnahmekriterium nennt `kern/src`, und es ist erfuellt.
Wer den Riegel jetzt auf `test/` ausdehnt, aendert das Kriterium eines abgeschlossenen
Pakets -- das darf weder der Bauagent noch der Pruefer, und die Aenderung waere ohne
eigene drei Baeume nicht nachgewiesen.

**Nicht Teil eines Testpakets.** Es entsteht keine Probe und keine Behauptung ueber den
Kern; es entsteht eine Bedingung an die Uebersetzungseinheit, und sie steht in der
Bauliste.

**Nicht Teil von 0074.** Das ist ein Architektenpaket auf `technik.md` ohne Code und
behandelt Massnahme 4.3, die Operatorfrage.

## Zur Datei

`kern/CMakeLists.txt` haelt am 2026-09-05 kein offenes Paket -- nachgemessen ueber die
`dateien`-Listen aller achtzehn Pakete mit `status: offen`, nicht aus einer fremden
Angabe uebernommen. 0134 selbst ist `gebaut` und mit dieser Pruefung abzuschliessen.

## Was ausdruecklich nicht dazugehoert

Kein Anfassen von `sperre.hpp`, keine Erweiterung der vergifteten Bezeichnerliste,
keine Vorverarbeitung. Der Riegel bleibt ein Zeilenleser mit derselben bekannten
Grenze; er bekommt nur eine zweite Menge Dateien. Ob die beiden Bedingungen fuer die
Proben in derselben Schleife oder in einer zweiten geprueft werden, entscheidet der
Bauagent -- die Abnahme verlangt nur, dass die Statusmeldung beide Zahlen getrennt
nennt.

## Vermerk des Projektmanagers, 2026-09-05

**Angenommen, `status: offen`.** Die vier Pruefungen halten: `kernbauer` ist eine
Baurolle und wird eingeplant; `kern/CMakeLists.txt` haelt seit dem Abschluss von 0134
in diesem Lauf kein anderes Paket mehr; die Abnahme nennt drei Baeume und keine
ausgeschriebene Zielzahl; eine Abhaengigkeit gibt es nicht.

**Die Nummer ist von 0138 auf 0139 gewechselt.** Zwei Pruefer haben am 2026-09-05
unabhaengig voneinander 0138 vergeben. Der aeltere der beiden Vorschlaege behaelt die
Nummer; dieser hier ist der juengere und wurde umgezogen. Wo dieses Paket anderswo
genannt wird, gilt der Dateiname, nicht die Ziffer.

**Zur Nachmessung im Vorschlag:** Die Aussage, `kern/CMakeLists.txt` halte kein offenes
Paket, war zum Zeitpunkt des Vorschlags richtig und ist es nach dem Statusnachzug
weiterhin. Ich habe sie nicht uebernommen, sondern ueber die `dateien`-Listen aller
offenen Pakete neu erhoben.
