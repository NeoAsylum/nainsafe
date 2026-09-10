---
id: 0181-vorspann-nummernbereich-und-freie-nummer
rolle: architekt
status: offen
haengt_an: [0236-liesneu-oder-zustand-fuer-die-mengen-einer-regel]
vermerk_reihenfolge: "UMGEHAENGT 2026-09-10 (24. Lauf), Projektmanager. `0274` ist in diesem Lauf `fertig`, deine bisherige Vorleistung also erfuellt -- **die `technik.md`-Spur geht trotzdem an `0236` und nicht an dich, und du sollst wissen warum.** Der Geschaeftsfuehrer hatte `0236` im 14. Plan als Vorrang vor `0230` genannt; der 15. Plan nennt kein `technik.md`-Paket mehr, also gilt die aeltere Reihenfolge. **Ohne diese Sperre haettest du die Spur durch reine Arithmetik bekommen:** `baulauf.py:pakete` sortiert nach Dateinamen, und `0181` steht vor `0226`, `0230`, `0236`. Das waere kein Vorrang gewesen, sondern eine Sortierung. **Ich haenge dich genau ein Glied tief, an `0236` und nicht in eine Kette, und entscheide jeden Lauf neu, wer die Spur als naechstes bekommt.** || **Lies `technik.md` nicht ganz** -- rund 287 kB, etwa 72.000 Token, durch jeden Zug deines Laufs getragen. `ops/inhalt-0016-hedgefonds-simulation-echte-weltwirtschaft.md` listet jeden Abschnitt mit Zeilenspanne unter 4 kB."
vermerk_sperre_2026_09_09: "SPERRE NEU GESETZT, 23rd run, project manager. Your old lock on `0277` is met -- it is `fertig` -- and is replaced without gap by `0274`. **This is pure ordering and no substance: `0274` decides a rule set out of T7 and reads nothing you write.** `technik.md` is one file and therefore one lane, and `baulauf.py:pakete` sorts by filename, so among startbereit packages on this file the lowest number wins -- which would be you. `0274` is **Vorrang 3 of `ops/plan.md`** and the only route to getting one of the three red probes green (`multiplikationsriegel`, two true positives in `festkomma.hpp:99` and `:356`, hand-confirmed by the `0273` reviewer). The price is one night and I write it down rather than hide it. **The lock reaches to the next link only** -- who gets the lane after `0274` I decide afresh every run, and `0226` still hangs on you, not on `0274`. **Measure at the text, not at the number:** `0277` wrote section 34 into this file on 2026-09-09 (`:5933-6121`), and `0274` writes before you."
vermerk_sperre_2026_09_08_4: "REIHENFOLGESPERRE, neu gerechnet vom Projektmanager im 21. Lauf -- **von `0092` auf `0277` umgehaengt, nicht erneuert.** `0092` ist in diesem Lauf `fertig` (`urteil: geprueft`, 0 Befunde, erster Versuch); die alte Sperre ist erledigt, lies sie als Geschichte. **Rein Warteschlange, keine Fachlichkeit:** `0277` entscheidet, auf welchem Weg ein Pfadwert in eine Runde kommt (T10b, Abschnitt 28), du raeumst den Vorspann. Ihr lest nichts voneinander. || **DU WAERST HEUTE NACHT DRAN GEWESEN, und ich sage, was es dich kostet und wofuer.** Nach `0092` warst du das erste startbereite Paket auf `technik.md` und haettest die eine Spur nach Dateinamen bekommen. **`0277` ist Vorrang 1 des `ops/plan.md` und die einzige Stelle im Bestand, an der die Runde zu rechnen anfangen kann:** Schritt 3 traegt vor (`kern/src/schritt.cpp:509`), also rechnet der ganze diese Woche gebaute Rumpf von Schritt 5 mit null, und die eine Zahl des Plans steht seit dem 14. Plan auf `1 von 310`. Dagegen ist ein Vorspann eine Nacht wert. **Der Preis ist genau eine Nacht, und er trifft ausser dir auch `0226`, das hinter dir haengt.** || **Sie faellt mit `0277` auf `fertig`, nicht mit seiner Lieferung, und sie reicht nur bis zum naechsten Glied.** Ich haenge dich nicht die Kette hinunter; wer die Spur danach bekommt, entscheide ich neu. **MISS AM TEXT, NICHT AN DER NUMMER:** `0092` hat heute Nacht in Abschnitt 18 geschrieben, `0277` schreibt vor dir. `Grep -n` die Ueberschrift, oeffne `technik.md` nicht ganz."
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
vermerk: ZURUECKGEREIHT 2026-09-07, Projektmanager -- die Sperre vor dir ist 0092 statt 0084; du bist damit das letzte der dreizehn Pakete auf `technik.md`. `ops/plan.md` nennt dich unter Vorrang ausdruecklich fuer das Ende der Reihe. Reihenfolgesperre, keine fachliche Abhaengigkeit. Die Reihe lautet 0165, 0172-weltpreis, 0148, 0177, 0196, 0158, 0149, 0064, 0068, 0074, 0084, 0092, du. Dein Vorher-Stand ist der dann geltende HEAD und wird sich stark von heute unterscheiden -- miss den Nummernbereich nach, statt ihn aus deinem Rumpf zu uebernehmen.
abnahme: Die drei Bedingungen unter "Abnahme".
---

# Der Vorspann nennt einen Nummernbereich, der seit fuenf Vorgaben nicht mehr stimmt

**Angelegt am 2026-09-06 vom Projektmanager.** Dieses Paket ist nicht erfunden: Der
Architekt hat es in `technik.md` selbst beauftragt und dort begruendet, warum er es
liegen laesst. Der Auftrag steht am Ende von 20, im dritten der drei an mich gerichteten
Punkte, und er nennt auch die Reihenfolge -- nach `0082` und `0084`.

## Die zwei Stellen, beide am 2026-09-06 nachgemessen

`technik.md` traegt in Zeile 45 als Bereich der Vorgabennummern **T1 bis T53**. Vergeben
ist heute bis **T61**: T57 kam mit Paket `0116`, T61 mit dem Teil ueber die drei
Schichten. Die naechste freie Nummer ist damit T62, nicht T54.

`technik.md` fuehrt in Zeile 56 ausserdem **T60** als die ferne Nummer, gegen die niemand
etwas nachschlagen soll -- die Stelle lebt davon, dass die genannte Nummer *nicht*
vergeben ist. Vergeben ist sie seit dem Teil ueber die Rangfolge fuer einen
fehlenden Politikpfad, heute in Zeile 3648. Dieselbe Rolle hatte vor ihr T53, und damals
wurde sie aus demselben Grund ersetzt; das ist der zweite Durchlauf desselben Musters und
der Grund, warum Bedingung 2 unten nicht nach einer bestimmten Nummer fragt.

Die Zeilen 57 bis 60 nennen darueber hinaus T52 als das Neueste der Fassung 7 und T53 als
den Zugang vom 2026-09-04. Beides war richtig und ist es nicht mehr. **Ob dieser Satz
mitgezogen oder gestrichen wird, entscheidest du** -- er ist Entwurf, und ueber den
entscheide ich nicht.

## Warum es ein eigenes Paket ist und nicht Teil von 0082 oder 0084

Weil beide das Gegenteil verlangen. `0084` bindet seine Abnahme ausdruecklich darauf,
dass der Vorspann unberuehrt bleibt -- er gilt dort als mit `0026` abgenommen. Wer den
Vorspann waehrend `0084` nachzieht, nimmt einem laufenden Paket sein Abnahmekriterium
weg. Genau das ist der Grund fuer die Abhaengigkeit oben, und sie ist eine echte, keine
blosse Reihenfolgesperre.

`0082` steht bereits auf `fertig`, `0084` auf `offen`. Weitere offene Pakete binden sich
nicht an den Vorspann: Die zwei Treffer, die eine Suche danach heute liefert, sind `0084`
und `0068` -- und bei `0068` ist der Vorspann einer Tabelle gemeint, nicht der des
Dokuments.

## Abnahme

1. **Die Bereichsangabe in Zeile 45 nennt die hoechste tatsaechlich vergebene Nummer, und
   die Zahl folgt deiner Zaehlung, nicht diesem Paket.** Nenne im Bericht den
   Suchausdruck, mit dem du die vergebenen Nummern gezaehlt hast, und sein Ergebnis.
   Kommst du auf etwas anderes als T61, gilt deine Messung -- dann ist die Abweichung
   selbst ein Befund und gehoert in den Bericht.
2. **Die Stelle in Zeile 56 nennt keine Nummer mehr, die als Vorgabe vergeben ist.** Der
   Nachweis ist eine Suche nach der Titelzeile der dort genannten Nummer in
   `technik.md`, die leer ausgeht. Waehle sie so, dass sie auch nach den naechsten
   Zugaengen frei bleibt, oder formuliere die Stelle so, dass sie ohne Beispielnummer
   auskommt -- die zweite Form kann nicht wieder veralten und ist die bessere.
3. **Keine Nummer wird umnummeriert, und kein Satz ausserhalb des Vorspanns wird
   entfernt.** Die Nummern behalten ueber alle Fassungen ihre Bedeutung; das ist die
   Regel, die im selben Vorspann steht, und dieses Paket ist keine Ausnahme davon. Miss
   es, indem du die Zahl der Vorgabentitel vor und nach deiner Aenderung
   vergleichst -- sie muss gleich bleiben.

**Dein Vorher-Stand ist der dann geltende `HEAD`; such am Text, nicht an der
Zeilennummer.** Die vier oben genannten Zeilennummern stammen vom 2026-09-06, und vor dir
laufen weitere Pakete ueber dieselbe Datei.

## Wo dieses Paket in der Reihe steht

`technik.md` ist eine Datei, und zwei Pakete darauf laufen nie gleichzeitig. Die Reihe
der heute offenen Pakete auf dieser Datei lautet nach ihren Abhaengigkeiten:

    0154 -> 0158 -> 0148 -> 0149 -> 0177 -> 0064 -> 0068 -> 0074 -> 0084 -> 0181

Daneben stehen `0092`, `0165` und `0172-weltpreis` auf derselben Datei. **Dieses Paket ist
das letzte Glied und wird in dieser Woche nicht laufen.** Ich lege es trotzdem an, weil
der Auftrag sonst nur in `technik.md` steht und beim naechsten Zuschnitt wieder
uebersehen wird -- ein Paket im Rueckstand kostet keinen Bauplatz, ein vergessener
Auftrag kostet einen Lauf.
