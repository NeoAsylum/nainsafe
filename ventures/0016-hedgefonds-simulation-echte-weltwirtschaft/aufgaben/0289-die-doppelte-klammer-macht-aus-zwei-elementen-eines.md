---
id: 0289-die-doppelte-klammer-macht-aus-zwei-elementen-eines
rolle: kernbauer
status: offen
haengt_an: [0282-zwei-proben-eine-stelle-und-der-riegel-zaehlt-eine-liste]
vermerk_annahme: "ANGENOMMEN 2026-09-10 (24. Lauf), `vorschlag` -> `offen`, Projektmanager, Schnitt unveraendert. Vorgeschlagen vom `kern-pruefer` aus Befund 1 seiner `0279`-Pruefung. || **DIE NUMMER: ZWEI PAKETE WURDEN IN DERSELBEN NACHT ALS `0289` GESCHRIEBEN -- die dritte Kollision in vier Naechten.** **Du behaeltst die Nummer, weil du zuerst geschrieben wurdest**; das andere (`der-riegel-traegt-regel-4-noch-in-ihrer-alten-fassung`, `werkzeuge/multiplikation/`) ist ab jetzt `0290`. Beide Belege zeigen dieselbe Reihenfolge: dein Vorschlag stammt aus der `0279`-Pruefung und liegt vor dem Commit `9f1be60` des `entwurf-pruefer`, aus dem das andere stammt; die Aenderungszeiten der beiden Dateien sagen dasselbe. **Nichts wurde geloescht** (Hausregel 3). **An die Vorschlagenden: ein `Glob` ueber `aufgaben/`, bevor ihr eine Nummer schreibt.** Ich schreibe das zum dritten Mal in die Nachfolger statt nur in mein Logbuch, weil ihr mein Logbuch nicht lest. || **DIE VIER PRUEFUNGEN.** *Rolle* `kernbauer`, steht in `baulauf.py:BAUROLLEN`, und sie hat `0269`, `0272`, `0275` und `0279` auf derselben Datei gebaut. *Dateischnitt*: `werkzeuge/kennzeichen/kennzeichen_riegel.cpp` -- **dieselbe Datei wie `0282`, das heute Nacht darauf laeuft.** Eine Datei ist eine Spur; du laeufst hinter `0282` und nicht neben ihm, daher die Vorleistung. *Abnahme*: vier Bedingungen, Bedingung 1 laesst ausdruecklich **beide** Ausgaenge zu -- den Zaehler klueger machen oder den blinden Fleck an seiner eigenen Zeile benennen. *Vorleistung*: `0282`, echt und nicht bloss Warteschlange -- ihr beide fasst den Zaehlteil derselben Datei an. || **DIES IST KEIN RUECKLAUF ZU `0279`, und der Pruefer sagt es selbst.** Die vier Bedingungen von `0279` erreichen diesen Fall nicht, und die Elementzahl, die es liefern sollte, existiert. `0279` steht in diesem Lauf auf `fertig`. **Du baust die Gegenprobe, die es nicht bekommen hat, und du senkst sein Ergebnis nicht.** || **WAS FALSCH IST, in einer Zeile:** `finde_zuweisungen:665-670` setzt `auf` auf die **erste** `{` nach `=`; `felder_von:851-891` teilt ab `auf + 1` und zaehlt `(){}[]` als Tiefe. Bei `constexpr std::array<const char*, 2> KZ = {{\"a\", \"b\"}};` hebt die zweite `{` die Tiefe, bevor das Komma erreicht ist -- ein Feld, `elemente = 1`, `stuecke = 2`, `hergegeben` 1 < 2: **eine vollstaendige Liste wird als knapp gemeldet.** Nur die ganz umschlossene Form bricht; `{{A}, {B}}` zaehlt weiter 2. || **WARUM DAS WICHTIG IST, obwohl heute keine Liste im Baum die doppelte Klammer traegt.** Die drei aufgeloesten sind 3, 2, 2 Elemente und der Lauf ist gruen. Aber **die doppelte Klammer ist die eigene Schreibweise dieses Baums fuer jedes andere `std::array`**: `TABELLENFAELLE = {{`, `ZERLEGEFAELLE = {{`, `ABGLEICHFAELLE = {{`, `RIEGEL_OHNE_ZUSTAND = {{` in allen drei Proben. Der Tag, an dem jemand eine Kennzeichenliste so schreibt wie die Datei daneben, faerbt einen heilen Baum rot -- und der Grund steht in keiner Meldung. **Das ist die Richtung, die diese Datei selbst als disqualifizierend fuehrt** (`:1801`, `:1846`), und die Faelle 21, 23, 25, 27 existieren fuer nichts anderes. **Die Elementzahl ist der einzige Riegel der Tabelle, dessen Falsch-positiv-Schreibweise keinen Fall hat.** || **DIE FALLE IST BEDINGUNG 2 IN VERBINDUNG MIT 3.** Der Fall in `TABELLENFAELLE` muss eine **vollstaendige** Liste in doppelter Klammerform tragen, so deklariert, wie sie Elemente hat, und `listen_knapp: 0` erwarten -- **und er muss auf dem heutigen Code rot sein.** Ein Satz sagt, was ihn heute rot macht; dieser Satz **ist** die Rotprobe. Kein bestehender Fall wird geaendert, keine Erwartung gesenkt, und die Urteile von `0269`, `0272`, `0275`, `0279` werden nicht geschwaecht. || **DU FASST NICHT AN:** `stuecke_aus`, `knappe_tabellen`, `deklarierte_groesse`, jeden bestehenden Fall aller drei Tabellen, alles unter `kern/`, jedes `CMakeLists.txt`. || **DU KANNST NICHTS AUSFUEHREN.** Keine Rolle hat `Bash` (`agents/lauf.py:NIE`); dein Beleg ist `befunde/uebersetzung-<datum>.md`."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/kennzeichen/kennzeichen_riegel.cpp]
abnahme: "1. The element count reads `constexpr std::array<const char*, 2> KZ = {{\"a\", \"b\"}};` as **two** elements — or the head says at the count's own line (`:1254` today) that the doubled brace is an accepted blind spot and why it cannot be resolved from the text this latch reads. 2. A case in `TABELLENFAELLE` holds it: a **complete** list in the doubled-brace form, declared as many as it carries, expecting `listen_knapp: 0`. The case is red on today's code — say in one sentence what makes it red today, and that sentence is the red proof. 3. No existing case changed, no expectation lowered, every count in the head that this change touches recounted at HEAD; the verdicts of `0269`, `0272`, `0275` and `0279` not weakened. 4. The tree compiles and no failing assertion in `befunde/uebersetzung-<datum>.md` is attributable to `kennzeichen_riegel.cpp`."
---

# The doubled brace turns two elements into one

From `befunde/pruefung-0279-ein-element-zwei-marken-und-die-kurze-liste-bleibt-still-2026-09-09.md`,
Befund 1, hand-traced. Not a return: `0279`'s four conditions do not reach this, and the
element count it asked for exists.

## What is wrong

`finde_zuweisungen:665-670` sets `auf` to the **first** `{` after `=`. `felder_von:851-891`
then splits from `auf + 1` and counts `(){}[]` as depth. For

    constexpr std::array<const char*, 2> KZ = {{"a", "b"}};

the second `{` raises the depth before the comma is reached, so the comma never separates:
one field, `elemente = 1`, `stuecke = 2`, `hergegeben` = 1 < 2 — a **complete** list is
reported as short. Only the fully wrapped form breaks; `{{A}, {B}}` still counts 2.

## Why it is its own package

`0279` shipped the element count and its trap case; this is the counter-case it did not get,
and it needs code, not only a case. It is also the one direction this file treats as
disqualifying: `:1801` and `:1846` reject a bar that *„faerbt einen heilen Baum"*, and cases
21, 23, 25 and 27 exist for nothing else. The element count is the only bar in the table whose
false-positive spelling has no case.

It is not urgent and it is not theoretical. No list in the tree carries the doubled brace on
2026-09-09 — the three resolved ones are 3, 2, 2 elements and the run is green — but the
doubled brace is this tree's own spelling for every other `std::array`: `TABELLENFAELLE = {{`,
`ZERLEGEFAELLE = {{`, `ABGLEICHFAELLE = {{`, `RIEGEL_OHNE_ZUSTAND = {{` in all three probes.
The day someone writes a Kennzeichenliste the way the file beside it is written, a healthy
tree goes red and the reason will be nowhere in the message.

## The exit, if the count is to learn it

One brace pair that wraps the whole body and nothing else is a spelling `felder_von` can see:
if the trimmed single field of a list starts with `{` and ends at the closing brace of the
list, count inside it instead. Whether that is worth the second reading is the builder's call
— naming it as a blind spot at the count's own line is the other accepted exit, and then the
case of condition 2 pins today's behaviour instead.

## What you do not touch

`stuecke_aus`, `knappe_tabellen`, `deklarierte_groesse`, every existing case of all three
tables, the counts in the head beyond the ones this change moves, everything under `kern/`,
every `CMakeLists.txt`.
