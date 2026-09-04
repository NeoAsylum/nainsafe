---
id: 0071-rundennummer-in-den-zustand
rolle: kernbauer
status: offen
haengt_an: [0033-schritt-rundengeruest-weltlauf]
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

---

## ANGENOMMEN — 2026-09-04, Projektmanager: `vorschlag` → `offen`, **`0027` aus `haengt_an` gestrichen**

Die vier Prüfungen meiner Rolle:

- **Rolle:** `kernbauer` steht in `BAUROLLEN` (`baulauf.py:59`) und hat mit `kern-pruefer`
  einen Prüfer. ✓
- **Dateischnitt:** `kern/src/schritt.cpp`, `kern/include/kern/schritt.hpp` und
  `kern/test/schritt_probe.cpp` beanspruchen sonst nur **0033** und **0038**, beide
  `fertig`. Nachgesehen habe ich auch die Pakete auf `gebaut`, weil der Kollisionsschutz
  sie nicht sieht (`startbereit()` vergleicht `dateien` nur unter `offen`,
  `baulauf.py:270-281`): auf `gebaut` steht nach diesem Lauf **0052** (`festkomma.*`) und
  **0059** (`werkzeuge/belegstellen/*`, Wurzel-`CMakeLists.txt`). Keines hält eine deiner
  drei Dateien. ✓
- **Abnahme:** prüfbar, und in der richtigen Form — sie nennt eine ausgeführte Beobachtung
  (0 → 1 → 2 über zwei Runden) statt eines Wortlauts, den du abschreiben sollst. ✓
- **Abhängigkeit:** 0033 ist `fertig`. Das Paket ist sofort startbereit. ✓

**Warum ich `0027-zustand-schreibweg-schliessen` aus `haengt_an` gestrichen habe.** Der
Vorschlag hat es aus Sorgfalt hineingeschrieben, aber es wäre ein Deadlock gewesen, und
zwar von der Sorte, die man erst nach dem Zuschnitt sieht: Mit diesem Lauf wandert
**Bedingung 3 von 0027 hierher**. Beide Richtungen zugleich — 0071 wartet auf 0027, und
0027 kann seine Bedingung 3 nur durch 0071 belegen — wären zwei Pakete, die sich
gegenseitig festhalten, bis eines von beiden auf `blockiert` geht. Die Abhängigkeit war
außerdem nie eine des Inhalts: Der Riegel, gegen den deine Probe misst, ist **gebaut** und
zweimal geprüft (Bedingungen 1, 2, 4 und 5 von 0027 sind belegt). Was an 0027 offen ist,
ist ein Kommentar in `zustand.hpp` — daran hängt keine Zeile deiner Arbeit, und eure
Dateilisten schneiden sich nicht.

**Damit trägst du eine Bedingung, die ein anderes Paket abgegeben hat, und das steht auch
dort.** Die Verlegung ist in 0027 im Abschnitt „ZWEITER RÜCKLAUF" begründet; der Prüfer von
0027 hat beide Wege ausdrücklich mir überlassen und diesen Vorschlag als den zweiten
benannt. Wenn du an der Sache scheiterst, ist das ein Befund gegen die Verlegung und gehört
gemeldet — nicht still zurück nach 0027 geschoben.

**Zwei Dinge, die dich sonst deine Abnahme kosten:**

1. **Du widerrufst eine abgenommene Bedingung eines fertigen Pakets.** Bedingung 6 von 0033
   verlangt die *unveränderte* Prüfsumme über eine Runde, und `schritt_probe.cpp:286-291`
   sichert das heute feldweise. Deine Abnahme ersetzt sie durch „genau eine der 310 Größen
   ändert sich". Das ist zulässig, weil `schritt.hpp` die Eigenschaft selbst „auf Widerruf"
   ausweist — aber es ist zulässig **nur, wenn du beide Prüfsummen im Wortlaut nennst** und
   die Stelle in `schritt.hpp` mitziehst, die das alte Versprechen gibt. Ein stiller
   Widerruf ist ein Rücklauf.
2. **Der Randfall Vorrundennummer gleich `I64_MAX` minus eins** in `probe_runden` läuft
   heute durch. Mit der Setzung trägt der Zustand danach `I64_MAX`, und die nächste Runde
   bricht am vorhandenen Riegel ab. Der Vorschlag sagt richtig: Das ist so gewollt und
   gehört gezeigt, nicht umgangen.

**Was ich nicht entscheide:** ob Schritt 1 der richtige Ort für die Setzung ist. Der
Vorschlag und der Prüfer von 0027 kommen unabhängig auf dieselbe Stelle; findest du eine
bessere, ist das ein Befund gegen den Vorschlag und kein Rücklauf gegen dich — dann nennst
du sie und begründest sie.

## Rückläufe

0.
