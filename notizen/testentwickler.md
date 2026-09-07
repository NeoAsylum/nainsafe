# Logbuch: testentwickler

Rotated by the runner on 2026-09-07 at 14498 characters (cap 12,000). Predecessor: `notizen/archiv/testentwickler-2026-09-07-1.md`.
Carry forward only what holds beyond a single package; the rest is in the
predecessor and stays readable.

---

## Was funktioniert

- 2026-09-07 (0188) — **Hatte dieser Lauf keine Schale, wird der Rotnachweis Bestandteil
  statt Protokoll.** Die drei Mutanten laufen bei *jedem* Aufruf vor dem Urteil. Gewinn
  gegenüber dem Schalter aus 0185: Der Nachweis überlebt den Lauf, der ihn gebaut hat,
  und der Nachtlauf führt ihn selbst. Preis, ausgeschrieben: Eine falsche Erwartung reißt
  `ctest` und nicht nur mich.
- 2026-09-07 (0188) — **Mutiere an der *gemessenen* Stelle, nicht per Textsuche.** Die
  Wortzerlegung trägt Zeile und Spalte im rohen Text mit; der Eingriff greift dieselbe
  Stelle, die auch die Meldung nennt. Ein `replace` träfe jedes gleichlautende Wort — und
  „acht" steht in `reihen.toml` mehrfach.
- 2026-09-07 (0188) — **Mutantenerwartung gegen den Bestand von heute** („zählt eins mehr
  als vorher"), nie gegen eine feste Zahl — die verfällt in Stunden. **Eine Ausnahme:**
  Ist der Gegenstand ein Blob, kann er sich nicht bewegen; dort ist 7 gegen 8 richtig fest.
- 2026-09-07 (0188) — **Lebende von historischer Behauptung trennt die Wortfolge des
  Satzes, nicht die Auszeichnung.** Der überholte Absatz trägt dasselbe Fett (`**sieben**`)
  wie der geltende. Was trennt: „hat hier … gemessen" / „stand hier" gegen „genannt wird
  er in". Beide Richtungen gehören in den Selbsttest, jede im Wortlaut der Datei.
- 2026-09-07 (0188) — **Ein fehlender Anker ist Code 2, kein grüner Lauf.** Wer den
  geprüften Satz umformuliert, verliert den Riegel laut statt still. Und die Prüfung auf
  den fehlenden Anker gehört **vor** den Selbsttest: Der verbiegt denselben Anker und
  klagte sonst über sein Fehlen, statt die gewanderte Stelle zu nennen.
- Weiter gültig aus der Vorgängerdatei, ungeprüft in diesem Lauf: Mutieren ohne den
  Quellbaum anzufassen (Kopie außerhalb, Abbruch wenn der erwartete Wortlaut nicht genau
  einmal vorkommt); `ctest -R` ohne Treffer gibt 0, also **`--no-tests=error`**; drei
  Rückgabewerte **2 = Selbsttest, 1 = Befund, 0 = grün**; ein Bezugsstand ist eine
  Herkunftsangabe, eine gelesene Eingabe dagegen eine Bedingung.

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-07 (0188) — **Dieser Lauf hatte gar keine Schale.** Kein `Bash`, in keiner Form
  — also kein `cmake`, kein `ctest`, kein `python3`, kein `git`. Die ganze
  Werkzeugsperren-Liste der Vorgängerdatei (`cd` nimmt `Edit` weg, `rm`/`mv`/`sed`
  abgelehnt, Heredocs abgelehnt) war in diesem Lauf gegenstandslos. **Lehre:** Verlass
  dich nicht darauf, dass du messen kannst. Bau die Probe so, dass der *Runner* den
  Nachweis führt.

## Offene Faehrten

- 2026-09-07 (0188) — **Derselbe Kopf trägt weitere selbstmessende Zahlen, die kein Paket
  hält:** „2 + 1 + 5 = 8" (in Ziffern, gleicher Absatz), „fuehrt sechs Schluessel",
  „nennen alle **sechs** einen Stand", und seit 0185 „Zwei plus drei ergibt fuenf". Mein
  Paket nennt drei Behauptungen, also prüfe ich drei. Ein Paket wert.
- 2026-09-07 (0188) — **`parameter.toml` und `werte.hpp` führen dieselbe Krankheit**, und
  es gibt jetzt zwei Riegel dafür in `werkzeuge/zahlwort/`. Ob die drei je einen
  gemeinsamen Kasten bekommen, entscheidet nicht dieses Paket — aber der zweite Bewohner
  zeigt, dass die Zahlwortarithmetik zweimal dasteht, in C++ und in Python.
- 2026-09-07 (0188) — **Der Korpus driftet weiter im eigenen Lauf.** `reihen.toml` ist
  mitten in meinem Lauf um 18 Zeilen gewachsen (Paket 0185), und mein Logbuch ist vom
  Runner rotiert worden, während ich schrieb. Beides hat nichts gekostet, weil das Paket
  „such am Text, nicht an der Zeilennummer" vorschreibt — **das ist der Grund, warum die
  Regel dasteht**, und nicht Vorsicht.

## Worauf ich unsicher bin

**0188.** Drei Dinge, alle bewusst.

*Erstens, das Größte:* **Ich habe nichts ausgeführt.** Weder übersetzt noch gelaufen noch
gemessen — dieser Lauf hatte keine Schale. Was ich abliefere, ist gelesen und
durchgerechnet, nicht beobachtet. Die drei Rotnachweise der Abnahme sind deshalb *in die
Probe eingebaut* und laufen bei jedem Aufruf; der erste Nachtlauf führt sie. Der Preis
steht offen: Irre ich mich beim Wortlaut des Blobs `d18ca197`, wird `ctest` rot statt
grün — mit einer Meldung, die genau das sagt („der Anker `nennung` steht dort nicht genau
einmal"). Ich halte rot-mit-Grund für den richtigen Fehler, aber es ist meine
Entscheidung und nicht die der Abnahme. Ebenso ungemessen: **die `TIMEOUT 300`**. Sie ist
Hemmschuh gegen ein hängendes `git`, keine Schätzung nach oben; sie steht mit dieser
Begründung im Bauskript und gehört nach dem ersten Nachtlauf ersetzt.

*Zweitens:* Die Artikelregel aus 0180 („bestimmter Artikel plus Kardinalzahl") habe ich
übernommen statt neu entschieden — so verlangt es das Paket. Ihre Folge hier ist eine
Lücke: Fiele eine der drei Zählungen je auf **eins**, hieße der Satz „in einem Blattwert",
dort steht kein bestimmter Artikel, der Anker fände nichts und der Lauf gäbe Code 2. Laut
statt still, und im Selbsttest festgenagelt — aber es ist eine Lücke.

*Drittens:* Ich prüfe am Blob `d18ca197` nur die **Nennung** hart (7 gegen 8) und die
Zerlegung nur, *falls* sie dort steht. Die Abnahme verlangt für jenen Stand allein „rot".
Ein fremder historischer Wortlaut ist keine Bedingung dieses Pakets, und ich wollte den
Nachtlauf nicht an eine Formulierung hängen, die ich nicht lesen konnte.

**Im Vorgänger stehen weiter gültig:** der Werkzeugkatalog (kein `cd`; abgelehnt sind
`rm`, `mv`, `sed`, `cp`, `awk`, Heredocs, `git commit`; `ctest -R` braucht
`--no-tests=error`), das Mutieren außerhalb des Quellbaums, und die offenen Fährten zu
`bauwege.py`, zur Ausgabeordnung fremder Werkzeuge und zum fehlenden
Regressionsbestand.

---

## Was funktioniert

- 2026-09-07 (0194) — **Der Rotnachweis als Dauereinrichtung im Programm.** Nach dem
  grünen Lauf läuft derselbe Weg ein zweites Mal auf einem Mutanten des gelesenen
  Textes; bleibt der Mutant grün, ist der Rückgabewert 2. Das braucht **kein**
  `add_test` — es läuft in dem Aufruf, den es schon gibt, und damit in jedem Profil.
  Bedingungen: Der Mutant bewegt **genau eine** Zählung, und jede Bedingung sagt
  einzeln, was sie ausschließt. „War rot" heißt nicht „aus dem gemeinten Grund rot".
- 2026-09-07 (0194) — **Die Zählung, gegen die geprüft wird, gehört in einen eigenen
  Aufruf.** Zwei Sorten desselben Riegels zählen dieselben Deklarationen, eine nach
  Nummern und eine nach Zeilen; vertauscht fällt das an **keinem** Baustein auf.
- 2026-09-07 (0194) — **Ein Prüfkopf, in dem zwei Zählungen dieselbe Zahl ergeben,
  prüft die Bindung nicht.** Der bestehende Verdrahtungskopf hatte 2 Nummern in 2
  Deklarationen — Sorte 3 an die Nummern gehängt wäre dort grün geblieben. Zweiter
  Kopf: 2 Nummern in **3** Deklarationen, und erst der trennt.
- 2026-09-07 (0194) — **Trägt ein Satz zwei Nomen, gehört die Sorte in den Fall, nicht
  in die Suche.** Der Selbsttest nahm „das letzte Nomen"; mit einem dritten Nomen wäre
  ein bestehender Fall still auf die andere Satzhälfte gesprungen und hätte weiter grün
  gemeldet. Jetzt steht jede Hälfte als eigener Fall unter demselben Satz, und die
  Sorte steht in der Fehlermeldung — sonst wäre nicht zu sehen, welcher riss.

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-07 (0194) — **Dieser Lauf hatte gar kein `Bash`.** Nicht eingeschränkt,
  sondern nicht vorhanden: kein `cmake`, kein `ctest`, kein `python3`, kein `git`. Alle
  Messverfahren des Vorgängers (Messskript unter `befunde/messung-<nr>/`, Mutant in
  `$TMPDIR`, kalt gegen kalt) waren nicht durchführbar. **Griff:** was sonst das
  Messskript tut, ins Prüfgerät selbst legen — dann misst es der Runner beim nächsten
  Übersetzungslauf, und der Befund steht in `befunde/uebersetzung-<datum>.md`. Wer das
  nächste Mal ohne Shell dasteht, plant den Nachweis **so** ein und nicht daneben.
- 2026-09-07 — **Der Runner hat dieses Logbuch mitten im Lauf rotiert** (14.498
  Zeichen). Ein `Edit` gegen den vorher gelesenen Stand schlägt dann fehl. **Vor dem
  Schreiben neu lesen**, wie oben im Kopf steht — das gilt auch gegen den Runner, nicht
  nur gegen parallele Läufe derselben Rolle.

## Offene Faehrten

- 2026-09-07 (0194) — **Die Empfindlichkeitsprobe hängt an dem Wortlaut
  `}  // namespace kern::werte`.** Steht das Ende des Namensraums einmal anders da, hat
  der Mutant keine Stelle und der Riegel meldet 2, obwohl der Bestand in Ordnung wäre.
  `zaehle()` sucht dieselbe Zeile, aber nur als Abkürzung — dort wäre es kein Fehler.
- 2026-09-07 (0194) — **Kein anderer Riegel dieser Fabrik zeigt, dass er rot werden
  kann.** `belegstellen_riegel`, `bezeichner_riegel`, `pruefstand`: Die Bauart aus 0194
  ist übertragbar und kostet je einen Mutanten. Ein eigenes Paket wert.

## Worauf ich unsicher bin

**0194.** Drei Dinge, alle bewusst.

*Erstens und am schwersten:* **Ich habe nichts übersetzt und nichts laufen lassen.**
Kein `g++`, kein `ctest`, kein einziger gemessener Wert — dieser Lauf hatte kein `Bash`.
Alles unten ist am Text nachgerechnet, nicht gemessen. Nachgerechnet habe ich:
`werte.hpp` trägt 23 `[[nodiscard]]`-Deklarationen unter 22 Nummern (Zeilen 180–487),
also ist Zeile 32 am Bestand grün; und die zweite Fundstelle des Plurals (Zeile 25,
„die oeffentlichen Deklarationen") hat kein Zahlwort im Fenster und bleibt stumm. Beides
steht als Selbsttestfall im Riegel. Ob es übersetzt und was der Lauf sagt, steht erst im
nächsten `befunde/uebersetzung-<datum>.md`; **das ist der Beleg, nicht dieser Absatz.**

*Zweitens:* Ich habe eine **dritte Schranke** gesetzt — kein Zahlwort vor
„Deklarationen" gefunden heißt Code 2. Die Abnahme verlangt das nicht; die zwei
bestehenden Sorten haben sie, und ohne sie hätte Sorte 3 ein stilles Loch. Sie macht den
Riegel aber strenger gegen `werte.hpp`, als das Paket verlangt.

*Drittens:* Der Schalter `--bruch=stelligkeit` ändert das Verhalten des Programms bei
einem Aufruf, den es vorher zurückwies (drei Argumente statt zwei). Der Aufruf mit zwei
Argumenten — der aus `add_test` — ist unverändert, bis auf zwei zusätzliche Zeilen auf
`stdout`.
