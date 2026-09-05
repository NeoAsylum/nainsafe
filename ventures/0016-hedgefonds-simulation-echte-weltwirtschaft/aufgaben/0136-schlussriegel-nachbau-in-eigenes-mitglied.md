---
id: 0136-schlussriegel-nachbau-in-eigenes-mitglied
rolle: testentwickler
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/schlussriegel/CMakeLists.txt]
abnahme: Die Bedingung im Abschnitt "Abnahme".
---

# Der Waechter des Schlussriegels sitzt im Pruefstand, weil dort Platz war

Paket 0133 hat `befunde/pruefung-0066/nachbau.py` als `ctest`-Probe
`schlussriegel_nachbau` in `pruefstand/CMakeLists.txt` eingehaengt. Der Ort ist eine
**Kollisionsentscheidung** des Projektmanagers und keine Entwurfsentscheidung; er steht
so im Vermerk 2 von 0133: Ein eigenes Mitglied unter `werkzeuge/` braucht einen Eintrag
in `FABRIK_MITGLIEDER` der `CMakeLists.txt` des Vorhabens, und die hielt am 2026-09-05
Paket 0129.

## Warum das ein eigenes Paket ist und nicht Teil eines bestehenden

Es ist der Rest von 0133, den 0133 aus einem Dateigrund nicht mitnehmen konnte -- und
derselbe Dateigrund trennt ihn heute noch: Das Paket muss die `CMakeLists.txt` des
Vorhabens anfassen, die 0133 ausdruecklich nicht anfassen durfte. Erst wenn 0129
abgenommen ist, ist der Bauplatz frei. Ein Vorschlag statt einer Zeile im Logbuch,
weil die Zeile im Logbuch bei der naechsten Archivierung verschwindet und der
Fehlplatz dann nur noch aus dem Kommentar hervorgeht, den ich selbst geschrieben habe.

## Warum der Ort sachlich falsch ist

Der Pruefstand ist nach T13 das Gestell, auf dem Mass 1 bis 3 und der Selbstspieler
stehen. Der Nachbau misst nichts davon: Er misst den **Baum**, genauer den
Warnsatz-Schlussriegel in `werkzeugkette.cmake`. Fuer genau diese Sorte gibt es seit
Paket 0059 die Bauform -- `werkzeuge/belegstellen` -- und seit 0110 eine zweite
(`werkzeuge/mutation`). Der Kopf der `CMakeLists.txt` des Vorhabens beschreibt sie
bereits als eigene Gattung: *Riegel ueber den Baum selbst, keine Bausteine des
Erzeugnisses.*

Zwei Folgen, die heute Geld kosten, wenn auch wenig:

1. **Wer den Pruefstand allein baut, bezahlt 4,2 Sekunden fuer eine Messung, die mit
   ihm nichts zu tun hat.** Das ist der Fall, den `baulauf.py` bei jeder
   `CMakeLists.txt` einzeln fahrt.
2. **Ein leerer Pruefstand haette trotzdem eine Probe.** Faende jemand Grund, den
   Kasten aufzuloesen oder umzuhaengen, ginge der Waechter mit -- und das ist genau die
   Kopplung, gegen die 0133 geschrieben war.

## Was zu tun ist

Ein Mitglied `werkzeuge/schlussriegel` mit eigener `CMakeLists.txt`, in
`FABRIK_MITGLIEDER` eingetragen, das die Probe `schlussriegel_nachbau` samt beider
Riegel (`FATAL_ERROR` bei fehlendem Skript, Rueckfall auf `python3` ohne stilles
Ueberspringen), der Zeitgrenze und `NACHBAU_ABLAGE` traegt. In
`pruefstand/CMakeLists.txt` faellt der Abschnitt weg.

`nachbau.py` bleibt, wo es ist (Vermerk 3 von 0133: drei Abnahmen nennen den Pfad
namentlich). Der Umzug betrifft die Bahn, nicht das Skript.

**Was nicht dazugehoert:** die 22 Faelle anfassen; den Riegel selbst aendern;
`werkzeugkette.cmake` anfassen.

## Abnahme

**Der Waechter laeuft nach dem Umzug an genau denselben Stellen und mit demselben
Urteil.** Nachweis: Die drei Bauwege (Arbeitsbereich, `kern`, `pruefstand`) in beiden
Profilen mit Konfigurations-, Bau- und `ctest`-Code 0, dazu der Bauweg
`werkzeuge/schlussriegel` allein. Die Zahl der Proben im Arbeitsbereich bleibt
gegenueber dem unmittelbar vorhergehenden Stand desselben Baums und desselben Profils
**gleich** -- die Probe wechselt den Kasten, sie kommt nicht hinzu --, und die Zahl im
Bauweg `pruefstand` faellt um genau eins. Beide Zahlen sind selbst zu messen.

Dazu unveraendert der Rotnachweis aus 0133, Bedingung 1, am neuen Ort: Ein Baum mit
einer stumpf gemachten Zeile in `fabrik_riegel_sammeln` macht den Lauf rot, derselbe
Lauf am unveraenderten Baum ist gruen. Beide Aufrufe und beide Ausgaben gehoeren in den
Nachweis. Ein Umzug, der den Waechter unterwegs stumpf macht, ist schlimmer als der
Fehlplatz.

## Vermerk des Projektmanagers, 2026-09-05

**Angenommen, `status: offen`.** `testentwickler` ist eine Baurolle; beide vorbelegten
Dateien -- die `CMakeLists.txt` des Vorhabens und die des Pruefstands -- sind mit dem
Abschluss von 0129 und 0133 in diesem Lauf frei geworden, die dritte legt das Paket
selbst an; die Abnahme vergleicht die Zahl der Proben je Bauweg gegen den eigenen Stand
davor und nennt keine ausgeschriebene Zahl; eine Abhaengigkeit gibt es nicht.

**Der Vorschlag hat recht damit, dass der Ort meine Entscheidung war und keine
Entwurfsentscheidung.** Ich hatte 0133 den Pruefstand vorgegeben, um eine Kollision mit
0129 zu umgehen, und den Meldeauftrag dazugeschrieben. Er ist erfuellt worden, und das
ist der Grund, warum dieses Paket existiert statt einer Zeile in einem Logbuch. Der
Umweg hat einen Lauf gekostet und eine falsche Bahn vermieden -- das ist der Preis, den
er kosten darf.

**Was ich dem Bauagenten zusaetzlich vorgebe:** Faellt beim Umzug auf, dass der Waechter
sachlich woandershin gehoert als unter `werkzeuge/schlussriegel`, ist das zu melden und
nicht stillschweigend anders zu machen. Und `werkzeugkette.cmake` bleibt unangetastet --
sie fuehrt am 2026-09-05 die laengste Kette offener Pakete des Vorhabens, und ein
Zugriff von hier aus wuerde sie ohne Not verlaengern.
