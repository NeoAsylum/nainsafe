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

- 2026-09-07 (0212) — **Frag zuerst, wo die Zusicherung steht.** Alle vier, die sich mit
  `PARTIELAENGE_HOECHSTENS` bewegen, stehen in Köpfen. Ein `#include` von
  `kern/zustandsausgabe.hpp` plus `-fsyntax-only` erreicht damit jede — keine
  Objektdatei, keine Bibliothek, keine Probe, kein `cmake`. `messung-0156/schranke.py`
  fuhr für dieselbe Frage `copytree` des ganzen Kerns, `cmake` und `--build`, das mal
  zwei Profile mal vier Fälle. Steht die Zusicherung im Kopf, ist der Kernbau bezahlte
  Zeit ohne Gegenwert.
- 2026-09-07 (0212) — **Ohne den Warnsatz übersetzen, wenn Zusicherungen das Urteil
  fällen sollen.** Er trägt `-Werror`; darunter entscheidet die nächstbeste fremde
  Warnung über grün und rot, und die Messung sagt dann etwas anderes, als ihr Name
  behauptet.
- 2026-09-07 (0212) — **Welcher Riegel welche Endung liest, entscheidet die Sprache einer
  neuen Datei mit.** Nachgelesen: `bezeichner_riegel` liest nur Kopf und Quelle unter
  `kern/`, `zahlwort_riegel` genau `werte.hpp`, `belegstellen_riegel` auch `.py` — außer
  unter `bau` und `befunde`. Ein neues Skript unter `kern/` fällt also in **einen**
  Riegel. Dessen Bedingung 1 greift am Wort für eine Zeile plus zwei Ziffern, Bedingung 2
  an drei deutschen Schlüsselwörtern vor einem Zitat. Englisch geschrieben und ohne jede
  Zeilenangabe ist ein Skript beiden entzogen.
- 2026-09-07 (0212) — **Die Sprachregel aufgeteilt, nicht gewürfelt.** `kern/CMakeLists.txt`
  ist ein durchgehend deutsches Dokument und wird deutsch fortgesetzt; `wandschranke.py`
  ist neu, liegt weder unter `aufgaben/` noch unter `befunde/` und ist deshalb englisch.
  Die zitierten Zusicherungswortlaute bleiben deutsch — eine übersetzte Nadel fände
  nichts. Ich schreibe das hier hin, weil die Aufteilung wie eine Unachtsamkeit aussieht
  und keine ist; sie steht auch im Kopf des Skripts.
- 2026-09-07 (0147) — **Ein Rücklauf, dessen Befund „nie ausgeführt" lautet, wird nicht
  am Quelltext behoben, sondern an der `CMakeLists.txt`.** 0147 kam zurück, obwohl der
  Prüfer alle neun Mutanten statisch nachgezogen und **nichts** zu berichtigen gefunden
  hatte. Der ganze Rücklauf war eine fehlende `add_test`-Zeile. Ich habe am `.cpp` keine
  Zeile angefasst. **Regel:** Lies erst den Befund, dann die Datei — sonst „repariert"
  man einen Quelltext, gegen den nichts vorliegt, und der zweite Rücklauf kommt.
- 2026-09-07 (0147) — **Drei Rückgabewerte sind erst dann etwas wert, wenn der Aufrufer
  sie unterscheiden kann.** Der Stand gab vorher für „eine Nadel trifft nicht mehr" und
  für „der Riegel weicht ab" beides `1`. Jetzt: **2 = nicht gemessen**, **1 = Befund**.
  Für `ctest` ist beides rot — aber der Mensch, der den Bericht liest, sieht den
  Unterschied zwischen einem kaputten Messgerät und einem kaputten Gegenstand.
- 2026-09-07 (0147) — **Die Nadelprobe gehört vor die erste Übersetzung.** Alle neun
  `alt`-Wortlaute werden geprüft, bevor irgendetwas gebaut wird. Kostet eine Sekunde,
  spart elf Übersetzungen und einen falsch gelesenen Bericht. Der Umbau, der das trägt,
  ist derselbe wie bei 0199: `einmal_ersetzen` **wirft**, der oberste Rahmen macht 2
  daraus.
- 2026-09-07 (0147) — **`Path(__file__).parents[n]` statt `/home/adria/fabrik`.** Der
  Messstand trug einen fest eingebauten Pfad — genau das, was das Paket in seinen
  *Grenzen* verbietet und was der Riegel selbst für seine Wurzel begründet. Ein Stand mit
  eingebautem Pfad läuft auf einem Rechner; einer aus dem eigenen Ort läuft überall und
  sagt, wenn die Ablage nicht stimmt.
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
- 2026-09-07 (0213) — **Eine Empfindlichkeitsprobe zählt nicht, sie vergleicht je
  Fundstelle.** `rot_nachher > rot_vorher` sättigt, sobald der Gegenstand **eine**
  Fundstelle hat: Eine schon rote kann nicht röter werden, und ausgerechnet der Fall, für
  den die Sorte gebaut ist, meldet dann „taub". Ersetzt durch den Vergleich von
  (`art`, `genannt`, `gezaehlt`, `ergebnis`) je Fundstelle, vorher gegen nachher. **Die
  Regel allgemein: Der Zeuge einer Mutationsprobe ist die bewegte Aussage an der Stelle,
  nicht die Anzahl der Stellen.** Jede Probe dieser Fabrik, die über ihren Gegenstand
  summiert, trägt denselben Fehler, sobald der Gegenstand klein wird.
- 2026-09-07 (0213) — **Zwei Weisen, wie sich Bewegung im Urteil zeigt, und man braucht
  beide:** `ergebnis == Rot || ergebnis != vorher.ergebnis`. Die erste deckt „war rot,
  bleibt rot, aber gegen eine um eins höhere Zählung", die zweite „war rot, wird grün".
  Nur eine von beiden zu verlangen, tauscht die Sättigung gegen eine andere.
- 2026-09-07 (0213) — **Ordnungszahlen taugen nicht als Zeuge.** Der Mutant *erhöht* die
  Zählung, und `zahl <= gezaehlt` wird davon nur grüner. Die Probe zählt deshalb allein
  die Kardinalzahlen und sagt es (eigener Rückgabegrund), statt still über sie hinwegzugehen.
- 2026-09-07 (0213) — **Die zu verstellende Stelle bekommt einen Namen.**
  `constexpr Sorte SORTE_DER_PROBE = Sorte::Deklarationen;` — eine Zeile, die `messen.py`
  mit `einmal_ersetzen` eindeutig trifft. Vorher steckte die Sorte als Wort in drei
  Bedingungen und ließ sich nicht in einem Griff verstellen. **Ein Riegel, dessen
  Rotnachweis geführt werden soll, braucht eine Stelle, an der man ihn packen kann.**
- 2026-09-07 (0213) — **Teil B kommt an die Empfindlichkeitsprobe nicht heran**, und das
  ist keine Lücke im Skript, sondern Bauart: Die Probe läuft *nach* dem Selbsttest, also
  endet jeder Mutant, der eine Tabelle reißt, mit 2, bevor sie dran ist. Deshalb **Teil
  C** — Mutanten der *Probe* statt der Zählung, die alle fünf Tabellen grün lassen. Für
  jede Prüfstufe hinter einer anderen gilt dasselbe: Sie braucht eigene Mutanten.

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
- 2026-09-07 (0212) — **`ctest` zeigt die Ausgabe einer grünen Probe nicht.**
  `baulauf.py` ruft `--output-on-failure`. Was `wandschranke` an Wänden, Prüfsummen und
  Sekunden druckt, steht im Nachtbericht also **nur, wenn sie rot ist** — genau im
  richtigen Fall, aber wer die gemessenen Zahlen einer grünen Nacht sucht, findet sie
  dort nicht. Kein Fehler des Eintrags; die Stellschraube läge in `baulauf.py`, und die
  gehört keiner Baurolle.

## Offene Fährten

- 2026-09-07 (0212, neu) — **Die gemessene Grenze gehört in den Kopf von `verlauf.hpp`,
  und zwar aus dem ersten Nachtlauf.** Der Kopf weist heute 138/139 ausdrücklich als
  *gerechnet* aus. Sagt `wandschranke` dasselbe, ist das eine Zeile Berichtigung; sagt es
  etwas anderes, druckt der Eintrag die bisektierte Grenze aus, und dann ist es dieselbe
  eine Zeile. Beides ist ein Folgepaket für den Kernbauer — `verlauf.hpp` gehört 0195 und
  stand nicht in meiner Dateiliste.
- 2026-09-07 (0212) — **Antwort auf die Fährte unten (0188/0147):** 0212 nimmt
  `bezeichner_riegel` und `pruefstand` **nicht** mit. Es baut die Gegenprobe für eine
  Schranke, nicht für einen Riegel; die beiden bleiben ohne Rotnachweis. Wer den
  Vorschlag schreibt, kann 0212 also nicht als erledigt dagegenhalten.

- 2026-09-07 (0199) — **Erledigt: `messung-0180/messen.py` misst wieder den
  ausgelieferten Stand** und hängt als `zahlwort_messung` in `ctest`. Die alte Fährte
  („misst den Stand von gestern") ist damit zu.
- 2026-09-07 (0199 → **0213 erledigt**) — Die Sättigung der Empfindlichkeitsprobe ist
  behoben, A2 erwartet jetzt Code 1 mit fünf Abweichungen, und Teil C führt den
  Rotnachweis der neuen Probe. Beleg ist der nächste Nachtlauf.
- 2026-09-07 (0188, **halb erledigt** durch 0147) — `belegstellen_riegel` hat jetzt eine
  lebende Gegenprobe (`belegstellen_messung`, neun Mutanten). Offen bleiben
  `bezeichner_riegel` und `pruefstand`. Bevor ich dafür einen Vorschlag schreibe: 0171
  („Messskript 0115 anbinden") und 0212 („Wandschranke als ctest-Eintrag") liegen schon
  auf derselben Krankheit — erst prüfen, ob die beiden es mitnehmen, sonst kostet der
  Vorschlag den Projektmanager einen Lauf umsonst.
- 2026-09-07 (0188, weiter offen) — Derselbe Kopf trägt weitere selbstmessende Zahlen,
  die kein Paket hält: „2 + 1 + 5 = 8", „fuehrt sechs Schluessel", „nennen alle **sechs**
  einen Stand", „Zwei plus drei ergibt fuenf".
- 2026-09-07 (0199) — **`befunde/` ist kein toter Ordner mehr**, und das hat einen Preis:
  `messen.py` und `messung-0099/zahlwoerter.py` werden jetzt von zwei `CMakeLists.txt`
  aus als Probe gefahren. Wer dort etwas verschiebt, reißt den Bau. Ob Beweisstücke unter
  `befunde/` oder unter `werkzeuge/` gehören, entscheidet nicht dieses Paket — aber es
  sind jetzt zwei.

## Worauf ich unsicher bin

**0212.** Drei Dinge, alle bewusst.

*Erstens, dasselbe wie immer:* **nichts übersetzt, nichts gelaufen.** Alle drei
Erwartungen sind am Text hergeleitet. Nachgerechnet: Bei Wand 138 misst das Kettenblatt
nach dem Gesetz des Kopfes 8.333.600 Byte und bei 139 8.393.120 gegen `STAPEL_JE_FADEN` =
8.388.608 — Fall A grün, Fall B rot. Dass in Fall B **nur** die Kettenblattzusicherung
reißt und keine der drei aus `verlauf.hpp`, habe ich einzeln nachgerechnet: `sizeof(Verlauf)`
liegt dort bei rund 2,4 MB, also weit unter dem Stapel, und die T40-Zusicherung ist
konstruktionsbedingt wahr. Das prüft der Eintrag aber selbst nach, an drei Wortlauten.
**Der Beleg ist der nächste Nachtlauf, nicht dieser Absatz.**

*Zweitens, die Stelle, an der ich am ehesten falsch verstanden werde:* Die Abnahme sagt
„compiles the core twice", und ich übersetze **eine Übersetzungseinheit** je Fall statt
den Kern. Das ist keine gesenkte Schwelle, sondern Auflage 3 des Projektmanagers („Bau
nur, was die Zusicherungen auslöst"): Alle vier Zusicherungen stehen in Köpfen, ein
Kernbau erreicht keine einzige mehr davon und kostet je Nacht zweimal ein Vielfaches.
Wer das anders sieht, ändert eine Zeile in `compile_unit`. Es ist meine Entscheidung und
nicht die der Abnahme.

*Drittens, ausdrücklich nicht gemessen:* die `TIMEOUT 300` und die Laufzeit der drei
Übersetzungen. Der rote Pfad bisektiert zusätzlich bis Wand 4096 — dort sind die Typen
über 200 MB groß, und mit solchen Wänden hat noch nie jemand übersetzt. Bricht der
Eintrag ausgerechnet dort ab, ist die Bisektionsobergrenze die Ursache und nicht die
Schranke.

**0147.** Zwei Dinge.

*Erstens, dasselbe wie immer:* **nichts gelaufen, dieser Lauf hatte keine Shell.** Ich habe
die Messung *eingehängt*, nicht *gefahren*. Der Beleg ist `belegstellen_messung` im
nächsten Nachtlauf. Zwei Stellen können dort rot werden, ohne dass am Riegel etwas falsch
ist: die `TIMEOUT 600` (geschätzt aus `zahlwort_messung` = 13,5 s für sechs Übersetzungen
von 1.800 Zeilen bei `-O1`; hier elf von 4.050 Zeilen bei `-O2`, also grob 100–150 s — die
Schranke sollte reichen, ist aber nicht gemessen), und `hole_vorstand`, das den
Vergleichsstand über `git log -S "Paket 0147"` holt. Beide melden sich mit **2**, nicht
mit 1 — daran ist ein Fehlschlag dieser Sorte im Bericht zu erkennen.

*Zweitens, die Kosten, weil sie niemandem auffallen sollen:* Die Probe hängt in
`werkzeuge/belegstellen/CMakeLists.txt` und läuft damit **zweimal je Baulauf** — einmal
im Arbeitsbereich, einmal im Alleinbau, so wie `belegstellen_riegel` selbst zweimal im
Bericht steht. Bei geschätzten 100–150 s sind das 200–300 s zusätzlich pro Nacht auf
einem 900-s-Kontingent für den ganzen `ctest`-Aufruf. Ich halte das für vertretbar, weil
die Alternative eine Probe ist, die niemand fährt. Fällt es dem Betrieb zu teuer, ist die
Stellschraube `-O2` → `-O1` im Messstand und nicht das Löschen der Probe.

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

**0199, nachträglich aufgelöst am 2026-09-07:** Die Sorge um **Fall A3** war unbegründet.
`befunde/uebersetzung-2026-09-07.md` zeigt `zahlwort_messung … Passed 13.50 sec` — also
ist A3 mit Code 1 durchgelaufen, und der Stand `b2829c8` trägt sehr wohl eine
Kardinalbehauptung der Sorte 3, die grün steht. Damit ist auch die neue Probe für A3
sicher: Was unter dem Zählvergleich rot wurde, wird es unter dem Fundstellenvergleich
erst recht. **Lehre:** Eine im Logbuch festgehaltene Unsicherheit wird vom nächsten
Bericht beantwortet — der Bericht ist zu Beginn des Laufs zu lesen, nicht die eigene alte
Vermutung fortzuschreiben.

**0213.** Vier Dinge.

*Erstens, wie immer:* **Dieser Lauf hatte keine Schale.** Nichts übersetzt, nichts
gelaufen. Vier Läufe in Folge (0188, 0194, 0199, 0213) ohne `Bash` — ich behandle das
inzwischen als den Normalfall und nicht als Ausnahme.

*Zweitens, die Erwartung, an der ich am ehesten falsch liege:* die **fünf Befundzeilen
von A2**, im Wortlaut und in der Reihenfolge. Hergeleitet, nicht gemessen: die vier
Zahlwörter vor „Groessen" stehen in `werte.hpp` an den Zeilen 2, 16, 32 und 157, das vor
„Deklarationen" an Zeile 32; die Reihenfolge ist die der Blöcke und innerhalb eines
Blocks die der Wörter, weshalb Zeile 32 zweimal hintereinander steht — erst Groessen,
dann Deklarationen. **Die eine Stelle, an der ein Tippfehler den ganzen Fall reißt:**
Zeile 32 beginnt den Block, also lautet das Wort dort `Zweiundzwanzig` mit großem Z, die
anderen drei mit kleinem. Reißt A2 im Nachtlauf mit „Befunde weichen ab", ist das die
erste Vermutung.

*Drittens, eine Bedingung ohne eigenen Rotnachweis:* die Prüfung, dass der Mutant die
**Fundstellenmenge der Sorte 3 nicht verändert**. Teil C belegt die beiden Hälften
danach (C1 = Zählung gefolgt, C2 = im Urteil gezeigt), diese nicht. Sie steht auf
derselben Stufe wie die vorhandenen Mutantenwächter (Nummernmenge, Mängelliste), die
auch keinen haben — bewusst so gelassen und nicht verschwiegen.

*Viertens, ein Preis:* Teil C sind **zwei weitere Übersetzungen**, also acht statt sechs.
13,5 s gemessen für sechs, geschätzt rund 18 s für acht, gegen `TIMEOUT 600` — reichlich
Luft. Der Kommentar in `werkzeuge/zahlwort/CMakeLists.txt` sagt aber weiter „fuenf
Mutanten" und „Sechs Uebersetzungen"; die Datei steht nicht in meiner Dateiliste, also
bleibt sie stehen. Kein eigener Vorschlag wert — wer als Nächstes die dortige `TIMEOUT`
durch den gemessenen Wert ersetzt, zieht die zwei Zahlen mit.
