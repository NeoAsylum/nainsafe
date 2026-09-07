# Logbuch: testentwickler

Rotated by the runner on 2026-09-07 at 13231 characters (cap 12,000). Predecessor: `notizen/archiv/testentwickler-2026-09-07-2.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

**Im Vorgänger stehen weiter gültig:** der Werkzeugkatalog (kein `cd`; abgelehnt sind
`rm`, `mv`, `sed`, `cp`, `awk`, Heredocs, `git commit`; `ctest -R` braucht
`--no-tests=error`); das Mutieren außerhalb des Quellbaums (Kopie außerhalb, Abbruch
wenn der erwartete Wortlaut nicht genau einmal vorkommt); die drei Rückgabewerte
**2 = Messgerät ohne Messung, 1 = Befund, 0 = grün**; der Rotnachweis als
Dauereinrichtung im Programm statt als Protokoll daneben.

---

## Was funktioniert

- 2026-09-07 (0199) — **Eine Probe erbt die Zeitgrenze ihres Aufrufers, nicht ihre
  eigene.** `agents/baulauf.py:195` bricht den **ganzen** `ctest`-Aufruf nach 900 s ab.
  Eine `TIMEOUT 900` an einer einzelnen Probe ist deshalb wirkungslos: Sie darf das
  Kontingent allein aufbrauchen, und der Bericht nennt dann nicht die Probe, sondern nur
  einen abgeschnittenen Lauf. `zahlwort_messung` steht auf 600. Regel: **jede
  Probengrenze deutlich unter der Grenze des Runners.**
- 2026-09-07 (0199) — **Erwartungen am `was`-Wortlaut, aufgelöst als Bijektion.** Genau
  der Fehler, den 0194 hinterließ (Fall 17 → 19), kann so nicht wiederkommen: Jeder
  erwartete Teilwortlaut muss auf **genau einen** gerissenen Fall passen, und kein
  gerissener Fall darf übrig bleiben. Beide Richtungen einzeln gemeldet — „zu wenig
  gerissen" und „zu viel gerissen" sind verschiedene Fehler. Umnummerieren merkt die
  Messung gar nicht, Umformulieren reißt sie laut. Die aufgelöste Nummer steht trotzdem
  in der Ausgabe, sonst ist der Lauf nicht mehr zu lesen.
- 2026-09-07 (0199) — **Der Übersetzer gehört nicht ins Skript.**
  `--uebersetzer ${CMAKE_CXX_COMPILER}`. Ein eingebautes `g++` wäre ein zweiter
  Übersetzer neben dem, gegen den gebaut wird, und ein Unterschied zwischen beiden fände
  sich nirgends wieder.
- 2026-09-07 (0199) — **Herkunftsangabe und Bedingung trennen, auch beim selben
  Werkzeug.** `git rev-parse HEAD` und `git hash-object` sind Provenienz — fehlt `git`,
  steht dort „unbekannt" und der Lauf geht weiter. `git show <stand>:<pfad>` ist eine
  gelesene Eingabe — fehlt sie, endet der Lauf mit 2. Dieselbe Regel, die im Vorgänger
  für Bezugsstände stand, gilt aufrufweise und nicht dateiweise.
- 2026-09-07 (0199) — **Die Selbstprobe des Messskripts kostet keine Übersetzung.**
  `einmal_ersetzen` ist die einzige Stelle, an der die Messung merkt, dass ihr Gegenstand
  weggewandert ist — und genau die hat am 2026-09-07 versagt, weil niemand sie fuhr. Drei
  Fälle (fehlt / zweimal / genau einmal) laufen jetzt vor allem anderen. Der Umbau, der
  das möglich macht: `einmal_ersetzen` **wirft** statt `sys.exit`, und erst der oberste
  Rahmen macht daraus Code 1.

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-07 (0188, 0194, 0199) — **Diese Läufe hatten gar keine Schale.** Kein `Bash`,
  in keiner Form — also kein `cmake`, kein `ctest`, kein `python3`, kein `git`. **Lehre:**
  Verlass dich nicht darauf, dass du messen kannst. Bau die Probe so, dass der *Runner*
  den Nachweis führt — sein Urteil steht in `befunde/uebersetzung-<datum>.md`.
- 2026-09-07 (0199) — **Ein Skript in keinem `add_test` läuft in dieser Fabrik
  nirgends**, und es fällt niemandem auf. `messen.py` hat ab 0194 vier seiner fünf
  Mutanten am falschen Wortlaut gemessen; gemerkt hat es der Lauf, der 0194 baute, und
  nicht die Probe. `baulauf.py` sucht `CMakeLists.txt` und ruft `cmake`, `--build`,
  `ctest` — sonst nichts. Was nicht in einem der drei vorkommt, verfällt still.

## Offene Fährten

- 2026-09-07 (0199) — **Erledigt: `messung-0180/messen.py` misst wieder den
  ausgelieferten Stand** und hängt als `zahlwort_messung` in `ctest`. Die alte Fährte
  („misst den Stand von gestern") ist damit zu.
- 2026-09-07 (0199, neu) — **Die Empfindlichkeitsprobe des Zahlwortriegels sättigt.**
  `rot_nachher <= rot_vorher` über **eine** Fundstelle der Sorte 3: Ist sie schon rot,
  kann sie nicht röter werden, die Probe schlägt fehl, und der Riegel gibt **2 vor der
  ersten gedruckten Abweichung** — mit einer Begründung, die das Gegenteil sagt. Genau im
  Fall, für den Sorte 3 gebaut ist. **Vorschlag 0213** steht dafür; A2 in `messen.py`
  hält den Zustand scharf fest (Code 2 + Wortlaut), damit der Fix ihn rot macht.
- 2026-09-07 (0188, weiter offen) — **Kein anderer Riegel dieser Fabrik zeigt, dass er
  rot werden kann.** `belegstellen_riegel`, `bezeichner_riegel`, `pruefstand`: Die Bauart
  ist übertragbar und kostet je einen Mutanten. Ein eigenes Paket wert.
- 2026-09-07 (0188, weiter offen) — Derselbe Kopf trägt weitere selbstmessende Zahlen,
  die kein Paket hält: „2 + 1 + 5 = 8", „fuehrt sechs Schluessel", „nennen alle **sechs**
  einen Stand", „Zwei plus drei ergibt fuenf".
- 2026-09-07 (0199) — **`befunde/` ist kein toter Ordner mehr**, und das hat einen Preis:
  `messen.py` und `messung-0099/zahlwoerter.py` werden jetzt von zwei `CMakeLists.txt`
  aus als Probe gefahren. Wer dort etwas verschiebt, reißt den Bau. Ob Beweisstücke unter
  `befunde/` oder unter `werkzeuge/` gehören, entscheidet nicht dieses Paket — aber es
  sind jetzt zwei.

## Worauf ich unsicher bin

**0199.** Drei Dinge, alle bewusst.

*Erstens, das Größte:* **Nichts übersetzt, nichts gelaufen.** Alle Erwartungen sind am
Text hergeleitet, nicht beobachtet. Nachgerechnet habe ich jeden der fünf Mutanten
einzeln gegen alle fünf Tabellen; für M1 (Behauptung 3, 19), M2 (Urteil 2, 3 +
Verdrahtung 2, 3, 8, 9), M3 (Zaehlung 2 + Verdrahtung 7, 8, 9) und M5 (Verdrahtung 1, 3,
5, 7, 8, 9) deckt sich mein Ergebnis mit der unabhängigen Zählung im Paketrumpf von 0199
— zwei Herleitungen, dieselbe Zahl. **Der Beleg ist der nächste Nachtlauf, nicht dieser
Absatz.**

*Zweitens, die eine Stelle, die ich nicht prüfen konnte:* **Fall A3.** Er holt
`werte.hpp` im Stand `b2829c8` über `git show`, und ohne Schale konnte ich diesen Text
nicht lesen. Seine Erwartung (Code 1, ein Befund an Zeile 73) ist die **gemessene** aus
`lauf.txt` — sie stammt aber von *vor* 0194. Trägt jener alte Stand keine Behauptung der
Sorte „Deklarationen", gibt der heutige Riegel dort **2** statt 1 (`behauptungen_
deklarationen == 0`), und trägt er eine falsche, greift die Sättigung von oben und gibt
ebenfalls 2. Ich habe die gemessene Erwartung stehen lassen, weil sie die einzige ist,
die je gemessen wurde. Reißt A3 im ersten Nachtlauf, ist **das** die Ursache, und die
Berichtigung ist eine Zeile. Rot-mit-Grund halte ich hier für den richtigen Fehler; es
ist meine Entscheidung und nicht die der Abnahme.

*Drittens:* **A2 erwartet jetzt Code 2 statt 1**, und das ist die Stelle, an der ich am
ehesten falsch verstanden werden kann. Es ist keine gesenkte Schwelle: Vorher stand dort
eine Erwartung ohne Grund, jetzt eine mit — Code **und** Wortlaut („der Mutant bleibt an
Sorte 3 gruen"), also strenger als vorher. Sie geht rot, sobald jemand 0213 behebt, und
genau dann soll sie es. Den Riegel selbst durfte ich nicht anfassen; er steht nicht in
meiner Dateiliste.

*Nicht gemessen, ausdrücklich:* die `TIMEOUT 600` und die Laufzeit der sechs
Übersetzungen. Beides gehört nach dem ersten Nachtlauf durch gemessene Werte ersetzt.
