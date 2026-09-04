---
id: 0071-rundennummer-in-den-zustand
rolle: kernbauer
status: vorschlag
haengt_an: [0033-schritt-rundengeruest-weltlauf, 0027-zustand-schreibweg-schliessen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/schritt.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schritt.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schritt_probe.cpp]
abnahme: Nach einer Runde im Modus weltlauf traegt `partie.runde` im Rueckgabezustand die Nummer dieser Runde, also Vorrundennummer plus eins. Die Probe zeigt es an zwei aufeinanderfolgenden Runden (0 auf 1 auf 2) und zeigt zusaetzlich, dass ein vor der ersten Runde gebundener `zustand::Startbelegung` danach beim naechsten Schreibzugriff abbricht und ein neuer sich nicht mehr binden laesst. Bedingung 6 von 0033 -- unveraenderte Pruefsumme ueber eine Runde -- wird dabei ausdruecklich ersetzt: Die neue Fassung verlangt, dass sich **genau eine** der 310 Groessen aendert, naemlich `partie.runde`, und nennt die beiden Pruefsummen vorher und nachher im Wortlaut.
---

# Die Rundennummer gehoert in den Zustand, nicht nur in die Kette

Befund: `befunde/pruefung-0027-zustand-schreibweg-schliessen-runde2-2026-09-04.md`,
Befund 1. **Lies ihn im Wortlaut**, dort steht die ausgefuehrte Reproduktion.

## Was heute geschieht

`kern::schritt` rechnet die Nummer dieser Runde aus (Vorrundennummer plus eins,
`schritt.cpp:577`) und gibt sie dem Schreiber mit. In den **Zustand** kommt sie nicht:
`partie.runde` gehoert zu Schritt 1 (`schritt.cpp:268`), Schritt 1 ist der Vortrag
(`:406`), und der Vortrag schreibt den Wert der Vorrunde zurueck
(`schreiber.cpp:256-262`). Nach einer Runde steht dort also dieselbe Zahl wie davor.

Gemessen, nicht gelesen -- eine Runde im Modus `weltlauf` auf einem frischen Zustand:

```
nach einer echten Runde: partie.runde = 0, Kette 175 Glieder, vor_der_ersten_runde = ja
```

## Warum das ein eigenes Paket ist

**Nicht Teil von 0027.** Dessen `dateien`-Liste nennt `zustand.hpp`, `zustand.cpp` und drei
Proben; `schritt.cpp` steht in keiner. Und es ist dort auch nicht loesbar: Der Riegel des
Startwertzugangs kennt nur den Zustand, und eine Runde, die ihn Feld fuer Feld unveraendert
laesst, ist von "keine Runde gelaufen" durch keinen Vergleich am Zustand zu unterscheiden --
auch nicht durch einen ueber alle 310 Groessen. Ein 311. Feld schliesst T15 aus.

**Nicht Teil von 0033.** Das Paket ist `geprueft` und `fertig`, und sein Vortragen ist von
seiner eigenen Bedingung 6 gefordert. Der Pruefer von 0033 hat die Sache am 2026-09-03
gesehen und richtig als keinen Befund gewertet ("Die Runde zaehlt nicht hoch ... Ich halte
es fest, damit niemand eine Rundenschleife auf den heutigen Rahmen setzt"). Genau das ist
inzwischen geschehen: 0027 hat seinen Riegel darauf gesetzt.

**Es ist also der Nachzug, den 0033 selbst angekuendigt hat** -- `schritt.hpp` weist zwei
Eigenschaften ausdruecklich als "auf Widerruf" aus, darunter die unveraenderte Pruefsumme.
Dieses Paket widerruft die erste von beiden.

## Was zu bauen ist

Schritt 1 setzt `partie.runde` auf die Nummer dieser Runde, statt sie vorzutragen. Die
beiden anderen Adressen des Schritts (Jahrgangskennung, Parameterpruefsumme) bleiben
Vortrag. Die Form entscheidet der Bauagent.

**Was dabei nachzuziehen ist, weil es sonst rot wird oder still falsch bleibt:**

1. **Bedingung 6 von 0033** und die beiden Stellen in `schritt.hpp`, die die unveraenderte
   Pruefsumme versprechen. Die Probe rechnet heute mit ihr (`schritt_probe.cpp:286-291`,
   feldweise Gleichheit).
2. **Der Fall Vorrundennummer gleich `I64_MAX` minus eins** in `probe_runden`. Er laeuft
   heute durch; mit der Setzung traegt der Zustand danach `I64_MAX`, und die naechste Runde
   bricht am vorhandenen Riegel ab. Das ist richtig so und gehoert gezeigt.
3. **Die Aussage von 0027 zurueckholen.** Erst mit diesem Paket wird aus Bedingung 3 von
   0027 eine Eigenschaft des gebauten Systems statt eine der Testhelfer. Die Probe dieses
   Pakets zeigt deshalb beide Haelften: alter Zugang bricht ab, neuer bindet nicht mehr.

**Nicht anfassen:** die Reihenfolge der sechs Schritte, die Zuordnungstafel, die Sollmasken,
den Schreiber, die Ursachenkette und `kern::zustand`. Die Aenderung betrifft **einen**
Schreibzugriff und die Proben, die seine bisherige Wirkung festhalten.

## Was ausdruecklich kein Befund ist

Dass die Kette schon heute die richtige Nummer traegt. Sie tut es, und das bleibt so; das
Paket bringt die Zahl nur zusaetzlich dorthin, wo der naechste Leser des Zustands sie
sucht.
