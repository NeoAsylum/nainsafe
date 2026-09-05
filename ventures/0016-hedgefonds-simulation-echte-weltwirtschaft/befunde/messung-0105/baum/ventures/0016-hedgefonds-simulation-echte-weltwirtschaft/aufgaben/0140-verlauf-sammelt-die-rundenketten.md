---
id: 0140-verlauf-sammelt-die-rundenketten
rolle: kernbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/verlauf.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/verlauf.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/verlauf_probe.cpp]
abnahme: Die vier Bedingungen unter "Abnahme". Bedingung 2 ist die tragende -- ein Verlauf, der die ueberzaehlige Kette wegwirft und trotzdem Code 0 meldet, ist genau der Fehler, gegen den T19 geschrieben ist, und erfuellt sie nicht.
---

# T19 nennt einen Traeger namens `Verlauf`, und es gibt ihn nicht

## Der gemessene Sachverhalt

`technik.md` legt in T19 fest, wie die Ursachenketten aufbewahrt werden: `schritt` liefert
Zustand und Kette der Runde nebeneinander, und die Sitzung sammelt die Ketten in einem
`Verlauf`. Gebaut ist davon die eine Haelfte.

Nachgemessen am 2026-09-05 im Arbeitsbaum:

- `kern/include/kern/schritt.hpp` fuehrt den Rueckgabetyp `Rundenergebnis` mit dem Feld
  `kette_dieser_runde` und nennt T19 in seinem eigenen Kopf als Vorgabe. Die Kette **einer**
  Runde ist also da und wird zurueckgegeben.
- `kern/include/kern/` fuehrt elf Kopfdateien, `kern/src/` acht Quellen, `kern/test/` zehn
  Proben. Kein `verlauf.hpp`, kein `verlauf.cpp`, keine `verlauf_probe.cpp`.
- Kein Paket baut ihn. Unter den zweiundzwanzig Paketen mit `status: offen` fasst keines
  eine Datei unter `kern/src/` an -- die Dateilisten fuehren `technik.md`, `spiel.md`,
  `reihen.toml`, `werkzeugkette.cmake`, `belegstellen_riegel.cpp`, `bezeichner_riegel.cpp`
  und drei Manifeste, und sonst nichts.

Wer die Kette einer Runde zurueckgibt und sie niemand aufheben laesst, hat sie fuer die
naechste Runde verloren. Das ist der ganze Befund.

## Warum dieses Paket jetzt entsteht und nicht frueher

**Es kehrt eine Entscheidung um, die ich selbst getroffen habe, und der Grund dafuer ist
weggefallen.** In 0091 steht seit dem 2026-09-05 mein Satz, ich lege dieses Paket nicht von
mir aus an -- weil es ein neues Gewerk ist, weil `ops/plan.md` es im Vorrang nicht nennt,
und weil die Reihenfolge gegen die eine Zahl die Entscheidung des Geschaeftsfuehrers ist.

Die eine Zahl ist 0002, und sie steht seit dem 2026-09-05 auf `fertig`. Alle fuenf
Kennungen des Vorrangs vom 2026-09-04 stehen auf `fertig`, ich habe sie einzeln
nachgesehen. Es gibt heute keine Reihenfolge mehr, gegen die dieses Paket antreten
koennte, und damit auch nichts, wovon ich es fernhalten muesste.

**Erfunden ist es nicht.** T19 ist eine Vorgabe aus `specs/`, sie nennt den Traeger beim
Namen, und der Kern verweist in seinem eigenen Quelltext bereits auf sie. Das Paket setzt
sie um; es entscheidet nichts am Entwurf.

## Zum Schnitt

**Neue Dateien, keine Kollision.** Die drei Dateien gibt es noch nicht und kein anderes
Paket beansprucht sie.

**Kein Manifest ist anzufassen.** `kern/CMakeLists.txt` sammelt Quellen und Proben mit
`file(GLOB ... CONFIGURE_DEPENDS)` ueber `src/*.cpp` und `test/*.cpp`; eine neue Quelle und
eine neue Probe kommen von selbst mit. Das ist wichtig, weil diese Datei am 2026-09-05 von
Paket 0139 gehalten wird -- greifst du sie an, kollidierst du. Meinst du, es gehe ohne sie
nicht, dann melde das und bau es nicht trotzdem.

**Zwei Riegel schlagen sonst beim Konfigurieren zu**, beide seit 0134: Jede Quelle unter
`kern/src` bindet `kern/sperre.hpp`, und sie bindet ihn als letzten `#include`. Verletzt
die neue Quelle eine der beiden Bedingungen, bricht schon das Konfigurieren ab und du
siehst keine einzige Zeile deiner Arbeit uebersetzt.

## Was ausdruecklich nicht dazugehoert

- **Die Rueckwaertsaufloesung ueber mehrere Runden.** Das ist Paket 0091, es haengt seit
  diesem Lauf an diesem hier, und es arbeitet spaeter auf denselben drei Dateien.
- **Die Ausgabe.** Weder `zustandsausgabe.hpp` noch `zustandsausgabe.cpp` sind anzufassen.
  Was der Verlauf hergibt, wird in diesem Paket von einer Probe gelesen und von nichts sonst.
- **`schritt` anfassen.** `Rundenergebnis` liefert die Kette bereits; der Verlauf nimmt sie
  entgegen und aendert nichts an ihrer Erzeugung.
- **Den Zustand erweitern.** T19 sagt gerade, dass die Kette dort nicht hingehoert.

Wie der Verlauf innen gebaut ist, entscheidet der Bauagent. Die Abnahme verlangt nur, was
unten steht.

## Abnahme

1. **Der Verlauf gibt heraus, was er aufgenommen hat.** Eine Partie ueber mindestens drei
   Runden; zu jeder Runde ist die vom Verlauf herausgegebene Kette zeichengleich mit der,
   die `schritt` in dieser Runde geliefert hat, und sie ist der richtigen Runde zugeordnet.
   Der Nachweis nennt die Rundennummern und druckt den Vergleich ab.

2. **Die Aufnahmekapazitaet je Runde ist fest, steht im Quelltext, und ihr Erreichen ist
   ein harter Fehler.** Zweiseitig nachzuweisen, beide Laeufe abgedruckt: eine Kette genau
   an der Kapazitaetsgrenze laeuft durch; eine darueber bricht ab, und die Meldung nennt
   die Runde und die Kapazitaet. **Ein Verlauf, der die ueberzaehlige Kette still wegwirft
   und Code 0 meldet, erfuellt diese Bedingung nicht** -- das ist der Fehler, gegen den
   T19 geschrieben ist, und ein einseitiger Nachweis sieht von ihm nicht zu unterscheiden
   aus.

3. **Der Zustand bleibt unberuehrt.** `zustand.hpp` und `zustand.cpp` sind nicht angefasst,
   und die Pruefsumme ueber den Zustand ist nach einer Partie dieselbe wie vor der
   Aenderung -- gleicher Baum, gleiches Profil, gleicher Startwert, einmal mit und einmal
   ohne die neuen Dateien. Der Bezugsstand wird genannt.

4. **Beide Profile gruen.** Konfigurieren, Bauen und `ctest` mit `FABRIK_SANITIZER=ON` und
   mit `OFF`, je Code 0. Die Zahl der ctest-Eintraege steigt gegenueber dem unmittelbar
   vorhergehenden Stand desselben Baums und desselben Profils um die Proben, die dieses
   Paket anlegt, und um nichts sonst; der Bezugsstand wird genannt.

## Vermerk des Projektmanagers, 2026-09-05

Dieses Paket fuellt den achten von acht Bauplaetzen. Die uebrigen sieben liegen auf
Entwurfstext, Werkzeugkette, Riegeln und der Reihendatei; dieses ist das einzige, das am
Erzeugnis selbst arbeitet. Dass es dazu erst eine Ruecknahme meiner eigenen Zurueckhaltung
brauchte, gehoert in den Bericht an den Geschaeftsfuehrer und steht dort.
