---
id: 0012-zufall-abgeleitete-stroeme
rolle: kernbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zufall.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/zufall.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/zufall_probe.cpp]
abnahme: Die fünf Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# `kern::zufall` — jeder Strom wird abgeleitet, keiner fortgeschrieben

Vorgaben: `technik.md` T11, dazu T2 (keine Fremdabhängigkeit), T4 (kein Gleitkomma),
T9 (feste Reihenfolge), T38 (Modus). ADR 0011 für die Sprache.

Das Modul steht am Anfang der Kette, weil es **von nichts abhängt**: Es kennt weder den
`Zustand` noch die abgeleiteten Größen, sondern nur sechs Ganzzahlen. Deshalb kann es
gebaut werden, während 0004 beim Kern-Prüfer liegt und 0008 den Zustand baut.

## Warum die Bauart wichtiger ist als der Erzeuger

T11 sagt beides, und der zweite Satz ist der teurere:

> Jeder Strom wird **abgeleitet**, nicht fortgeschrieben.

Ein fortlaufender Strom hat die Eigenschaft, dass **eine** neue Ziehung irgendwo alle
späteren verschiebt und damit den ganzen Regressionsbestand rot macht, ohne dass sich
inhaltlich etwas geändert hätte. Daran hängt später der Unterschied zwischen
„verbessern" und „verändern". Ein Modul mit einem gespeicherten Zustandswort wäre also
nicht eine andere Umsetzung derselben Sache, sondern die falsche Sache.

## Was du baust

1. **Die Ableitung.** Genau die Signatur aus T11, sechs Ganzzahlen:

   ```
   strom = splitmix64(wurzelstartwert, jahrgang_id, parameter_pruefsumme,
                      zweck_id, runde, index)
   ```

   SplitMix64 zur Ableitung, xoshiro256\*\* zur Erzeugung. **Selbst geschrieben, kein
   fremder Kasten** (T2) — ein Versionssprung eines fremden Zufallskastens würde jede
   gespeicherte Partie entwerten.
2. **`zweck_id` als benannte Aufzählung** mit den vier Werten aus T11:
   `JAHRGANGSSTREUUNG`, `ZUFALLSBOT`, `BUENDELZIEHUNG`, `SUCHBOT_KANDIDATEN`. T11 sagt
   ausdrücklich: „wird nie über eine Zahl geschrieben". Ein Aufruf mit einer nackten
   Zahl an dieser Stelle darf gar nicht erst übersetzen.
3. **Ganzzahlige Ausgabe.** Der Erzeuger liefert 64 Bit. Wer eine Zahl in einem Bereich
   braucht, bekommt sie über eine benannte Funktion mit ganzzahliger Restrechnung —
   **kein** Umweg über einen Gleitkommawert in `[0,1)`, das ist genau der Weg, den T4
   sperrt und den `sperre.hpp` zum Übersetzungsfehler macht.
4. **Kein gespeicherter Zustand im Modul.** Keine globale Variable, kein `static`, das
   sich zwischen zwei Aufrufen ändert. Zwei Aufrufe mit denselben sechs Zahlen liefern
   denselben Strom, auch in umgekehrter Reihenfolge aufgerufen.

**Was du nicht baust:** die Regel, wann gezogen wird. T38 sagt, dass im Modus
`weltlauf` kein einziger Strom gezogen wird — das ist eine Eigenschaft der Aufrufer und
gehört zu `schritt` und zum Prüfstand, nicht hierher. Schreib den Satz in den Kopf der
Datei, damit der nächste Leser ihn findet, und bau keine Modusprüfung ein.

## Abnahme

1. **Die Ableitung hat genau die sechs Argumente aus T11**, in dieser Bedeutung, und das
   Modul hält zwischen zwei Aufrufen nichts fest: `grep -nE 'static |^\s*[A-Za-z_]+ [a-z_]+ =' `
   über `zufall.cpp` zeigt keine veränderliche Ablage ausserhalb einer Funktion.
2. **`zweck_id` ist eine Aufzählung mit genau den vier Namen aus T11**, und eine nackte
   Zahl an dieser Stelle ist ein Übersetzungsfehler, keine Konvention.
3. **Die Erwartungswerte der Probe stammen aus einer unabhängigen Quelle.** In der Datei
   steht zu jedem Vektor die Herkunft mit URL und Abrufdatum — Referenzimplementierung
   von SplitMix64 beziehungsweise xoshiro256\*\* oder ein veröffentlichter Testvektor.
   **Ein Erwartungswert, den der eigene Code erzeugt hat, ist kein Nachweis, sondern
   eine Wiederholung**; genau daran scheitert die Bedingung, wenn die Herkunft fehlt.
   Der Prüfer ruft die genannte Quelle auf und vergleicht.
4. **Die Ableitungseigenschaft ist belegt, nicht behauptet.** Die Probe zeigt mit
   ausgeschriebenen Werten: gleiche sechs Zahlen → gleicher Strom; ein um eins erhöhter
   `index` → anderer Strom; und — der eigentliche Punkt — der Strom zu `index = 7` ist
   derselbe, ob vorher zu `index = 1 … 6` gezogen wurde oder nicht.
5. **Kein Gleitkomma, keine Fremdabhängigkeit** (T4, T2):
   `grep -rnE 'float|double' kern/src/zufall.cpp kern/include/kern/zufall.hpp` liefert
   nichts, und die Datei bindet nichts ein, was nicht Standardbibliothek ist.

Der Übersetzungslauf (`befunde/uebersetzung-<datum>.md`) ist für die Bedingungen 3 und 4
der zweite Nachweis: Stimmen die Erwartungswerte nicht, ist `ctest` rot. Der Prüfer
urteilt trotzdem gegen die Liste — grün heisst „die Zahlen passen zueinander", nicht
„die Zahlen sind die richtigen".

## Was ausdrücklich kein Befund ist

Die Aufteilung auf Kopf und Quelle, die Benennung der Hilfsfunktionen, ob die
Bereichsfunktion `in_bereich` oder `zwischen` heisst. `specs/` schweigt dazu.

## Rückläufe

0.
