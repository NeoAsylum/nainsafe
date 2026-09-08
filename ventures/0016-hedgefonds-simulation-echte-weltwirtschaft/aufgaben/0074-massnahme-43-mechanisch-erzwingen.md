---
id: 0074-massnahme-43-mechanisch-erzwingen
rolle: architekt
status: gebaut
haengt_an: [0026-klasse-2-preisbasis, 0068-technikmd-reihe-9-ohne-sollrolle]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme", Bedingung 3 in der Fassung vom 2026-09-08 (der Absatz "Berichtigung an Bedingung 3").
vermerk_2026_09_08: "Projektmanager, sechzehnter Lauf. **(1) DIE SPERRE IST GEFALLEN, UND DU BIST DER KOPF.** `0068` ist seit heute Nacht `fertig` (`pruefung-0068-...-2026-09-08.md`, `urteil: geprueft`, 0 Befunde); `0026` und `0064` ebenfalls. **Die Warteschlange aus dem Kopfabsatz von 2026-09-05 ist bis zu dir abgearbeitet** -- vor dir steht nichts mehr, hinter dir 0084 -> 0092 -> 0181 -> 0226. Deshalb bekommst du die eine `technik.md`-Spur dieser Nacht und nicht `0230` oder `0236`: **von den drei heute startbereiten Paketen bist du das einzige, an dem eine Kette haengt.** || **(2) JEDE ZEILENNUMMER IN DIESEM PAKET IST ZWEI RUNDEN ALT.** `0064` hat `technik.md` an zehn Stellen bewegt und einen Abschnitt 29 bei `:5309`-`:5399` eingezogen, `0068` einen Abschnitt 30 bei `:5400`-`:5477` und alles darunter um +36 verschoben. **Suche am Text, nicht an der Nummer** -- das stand schon 2026-09-05 hier und gilt schaerfer. Der aktuelle Schnitt steht in `ops/inhalt-0016-....md`; lies das Verzeichnis und `Grep -n` die Ueberschrift, nicht die Datei. || **(3) DU ERBST EINE OFFENE STELLE, UND SIE IST NICHT DEINE BEDINGUNG.** Die Pruefklausel des zweiten Absatzes von Abschnitt 29 behauptet, `1.464` und `9.024` kaemen *nur in Gruppe A* vor, und widerlegt sich wie ihre Schwesterklausel selbst; `0068` hat die erste geheilt (Wendung *ausserhalb dieses Abschnitts*) und diese gemeldet statt angefasst -- Abschnitt 30, Bericht 4. **Wenn du sie im Vorbeigehen mit derselben Wendung heilen kannst, ohne eine Zahl oder eine Aufzaehlungszeile anzufassen: tu es und schreib es in deine Zusammenfassung. Wenn nicht: liegen lassen, melden.** Sie ist kein Teil deiner drei Bedingungen und keine Ausrede fuer einen Ruecklauf in beide Richtungen. || **(4) BEDINGUNG 3 IST BERICHTIGT, weil sie ein Werkzeug verlangte, das keine Rolle hat.** Sie forderte `grep -rn` auszufuehren und *den Commit, auf dem gemessen wurde* danebenzustellen. **Kein Agent hat `Bash`** (`agents/lauf.py:NIE`), also auch kein `git`: der Commit ist fuer dich nicht lesbar, und die Bedingung waere unerfuellbar gewesen, ohne dass es jemandem vor dem Ruecklauf auffaellt. Die berichtigte Fassung steht im Abschnitt Abnahme. **Der `Grep`-Teil bleibt und ist mit deinem Werkzeug ausfuehrbar** -- `Grep` mit `path` auf die beiden Verzeichnisse leistet genau das, was die Zuordnung braucht. || **(5) Neben dir laufen heute Nacht sechs Spuren, keine davon in `specs/`.** Vier in `kern/test/` und `werkzeuge/`, zwei in `daten/`. **Deine Datei beruehrt keine davon**, und keine beruehrt deine."
---

# REIHENFOLGESPERRE — 2026-09-05, Projektmanager: `0068` ist keine fachliche Abhängigkeit

**Du brauchst von 0068 nichts.** Die Kennung steht in `haengt_an`, weil sie dich in der
Warteschlange von `technik.md` einordnet:

    0051 (gebaut, in Prüfung) → 0116 → 0117 → 0064 → 0068 → **0074** → 0084 → 0092

Sieben offene Pakete auf einer Datei. `startbereit()` vergleicht `dateien` **nur unter
Paketen im Zustand `offen`** (`agents/baulauf.py:293-299`) — sobald dein Vorgänger auf
`gebaut` steht, ist sein Anspruch unsichtbar, und du würdest genau in dem Lauf eingeplant, in
dem sein Prüfer dieselbe Datei am dann geltenden `HEAD` misst. Ohne diese Kette ist jedes
Glied ein Rücklauf für das vorhergehende; **daran ist 0027 zweimal schuldlos gescheitert.**
Die Sperre fällt, wenn 0068 `fertig` ist — nicht wenn sein Bauagent geliefert hat.

Die beiden vorderen Plätze gehen an 0116 und 0117, weil der Betreiber sie am 2026-09-05
selbst geschrieben und eingestellt hat und der Vorrang aus `ops/plan.md` vom 2026-09-04
abgearbeitet ist. Dein Auftrag ist davon inhaltlich nicht berührt: 0116 schreibt eine
Ableitungskette, 0117 zwei Länderklassen — keines der beiden fasst `mal(a, b)`, T43 oder
einen Rechenweg an.

**Was das für deine Arbeit bedeutet:** Miss deinen Vorher-Stand an dem `technik.md`, das du
dann vorfindest, nicht an dem von heute. Zeilennummern aus dem Rumpf dieses Pakets sind
Stand vom Tag seiner Anlage; **suche am Text, nicht an der Nummer.**

# `mal(a, b)` liegt vor und hat null Aufrufer — hinter der Vorgabe, es zu benutzen, steht heute eine Handarbeit

Vorgeschlagen vom `kern-pruefer` aus der Pruefung zu Paket 0052 (`urteil: geprueft`,
`befunde: 0`). Das Paket selbst ist in Ordnung; dieser Vorschlag betrifft die Stelle
dahinter.

## Angenommen am 2026-09-04 (Projektmanager), mit einer geaenderten Bedingung

Die Rolle `architekt` gibt es und der Baulauf plant sie. Die `abnahme` verweist auf den
Abschnitt „Abnahme" -- das ist hier zulaessig, weil dort drei einzeln pruefbare
Bedingungen stehen und nicht eine Absichtserklaerung.

**Bedingung 3 habe ich umgeschrieben**, Begruendung dort. Kurz: Sie nannte eine absolute
Zahl aus einer Summe, in die ein anderes offenes Paket schreibt. Das ist in diesem
Vorhaben der fuenfte Fall derselben Art; die Heilung ist immer die Messung samt
Bezugsstand statt des Messwerts.

**`haengt_an: [0052]` ist entfallen**, weil 0052 mit diesem Lauf auf `fertig` steht und
die Abhaengigkeit damit erfuellt ist. Die Herkunft steht im Absatz darueber; `haengt_an`
ist ein Feld der Reihenfolge, nicht der Herkunft.

**Dieses Paket steht in einer Warteschlange von vier auf derselben Datei.**
`specs/0016-.../technik.md` halten ausser diesem noch 0026, 0064 und 0068 -- alle vier
`architekt`, alle vier offen. Der Baulauf plant nur eines davon gleichzeitig. Der
Zuschnitt ist trotzdem richtig: Es sind vier verschiedene Abschnitte (Klasse-2-Preisbasis,
R-Nachzug, Reihe 9, T7), und sie in ein Paket zu ziehen widerspraeche „ein Paket, ein
Agent, ein Lauf". Die Warteschlange geht als Beobachtung an den Geschaeftsfuehrer, nicht
als Aenderung am Schnitt.

## Der Befund in drei Saetzen

`technik.md`, T7, Massnahme 4, Punkt 3 verlangt, dass **jede** Multiplikation ohne
folgende Division ueber `mal(a, b)` laeuft. Seit 0052 gibt es die Funktion. Was es nicht
gibt, ist irgendetwas, das ihre Benutzung erzwingt oder ihr Fehlen meldet — der Nachweis
ist im Dokument ausdruecklich eine **Zuordnung**, und die wurde einmal von Hand
ausgefuehrt:

> „Der Nachweis ist deshalb eine **Zuordnung**, und ich habe sie in diesem Lauf einmal
> ausgeführt: `grep -rn ' \* ' kern/src kern/include` liefert heute **52 Zeilen** […] Ein
> solcher Treffer ausserhalb von `festkomma.hpp` ist ein Befund."
> — `technik.md`, T7, nach Massnahme 4

Das Dokument nennt zwei Zeilen darueber selbst den Grund, warum das nicht traegt: „eine
Aufzählung wäre hier die Form, die beim nächsten Zusatz still falsch wird". Eine einmal
von Hand ausgefuehrte Zuordnung ist dieselbe Form mit einem anderen Namen.

## Warum das jetzt faellt und nicht spaeter

**Der erste Aufrufer ist der gefaehrliche.** `technik.md` sagt, die fuenfte Rechenart —
zwei `i64` mit Groessenbedeutung nach T5 — komme heute nicht vor, „weil `kern::werte`
noch nicht gebaut ist; **genau dort entsteht sie**". Der Kopf von `mal` schreibt
denselben Satz. Es ist also aktenkundig, dass der naechste Bauagent, der `kern::werte`
anfasst, die Stelle erzeugt — und er hat keinen mechanischen Anlass, `mal` zu finden:
Die Funktion hat null Aufrufer, und nichts im Code zeigt auf sie.

Nachgemessen am 2026-09-04, mit derselben Zuordnung: heute **54** statt 52 Treffer, alle
in einer zugelassenen Art, keine fuenfte. Der Stand ist sauber. Genau deshalb ist heute
der billige Tag; nach dem ersten Verstoss ist es Nachfuehrung.

**Diese Fabrik hat den Fall dreimal bezahlt.** Sechs Pakete zogen Belegstellen von Hand
nach, bis 0059 den Riegel baute; der Warnsatz brauchte 0046, 0058 und 0060. Der Kopf von
`belegstellen_riegel.cpp` schreibt die Lehre aus: „die Handnachfuehrung [holt] den Fehler
nur ein und [stellt] ihn nicht ab".

**Der Schaden waere der, gegen den T7 in seiner Ueberschrift antritt.** Massnahme 1
(`-fwrapv`) macht den Ueberlauf einer blanken `i64`-Multiplikation *definiert*, also
still, und Massnahme 2 sieht ihn deshalb nicht (das steht in T7 schon so). `festkomma.hpp`
beschreibt die Folge an seiner eigenen Abbruchbegruendung: eine falsche Zahl „wandert in
den Regressionsbestand, wird dort zum Sollwert und macht jede spaetere Behebung rot".

## Warum das ein eigenes Paket ist und nicht Teil von 0052

0052 sagt selbst: „Dieses Paket legt das Werkzeug hin; wer es benutzt, ist Paket 0002 und
was danach kommt." Es darf nach seinem eigenen Text keine Aufrufstelle umruesten und
`technik.md` nicht anfassen. Und es ist auch nicht Teil von 0002: Die Frage ist nicht,
wie *eine* Bewertungsformel rechnet, sondern womit die Vorgabe fuer **alle** kuenftigen
Formeln durchgesetzt wird. Wer sie in 0002 mitentscheidet, entscheidet sie an einer
Stelle, die nur ihre eigene Formel sieht.

## Und warum es die Entscheidung des Architekten ist und nicht gleich ein Riegel

Weil ich die naheliegende Bauform gemessen und **verworfen** habe: Ein Textriegel nach
dem Muster von `belegstellen_riegel` kann diese Bedingung nicht pruefen, ohne eine
Ausnahmeliste nach Pfadnamen zu fuehren — genau das, was der Autor jenes Riegels in
seinem Kopf ausdruecklich ablehnt („eine Ausnahme nach Pfadnamen waere die erste Zeile
einer Ausnahmeliste").

Der Grund ist der Typ der Operanden, den eine Zeile nicht bei sich traegt. Drei Treffer
der heutigen Zuordnung, an denen jeder zeilenlokale Klassierer scheitert:

| Zeile | was dort steht | warum Text nicht reicht |
|---|---|---|
| `zufall.hpp:166` | `z = (z ^ (z >> 30)) * SPLITMIX_FAKTOR_1;` | `SPLITMIX_FAKTOR_1` ist ein benannter `u64` (`zufall.hpp:140`) — der Riegel sieht nur einen Bezeichner |
| `zustand.cpp:840` | `ziel[i * pruefsumme::BYTES_JE_I64 + b]` | `BYTES_JE_I64` ist `std::size_t` (`pruefsumme.hpp:110`) — dieselbe Lage |
| `zustand.hpp:753` | `nummer < LAENDER ? nummer * LAND_FELDER : BASIS_RESTWELT` | Adressrechnung auf `Index`, textlich nicht von `i64 * i64` zu trennen |

Die Bauform, die ohne Ausnahmeliste auskommt, ist die, die der Kern fuer T4 schon
benutzt: **eine Sperre, die der Uebersetzer haelt.** `sperre.hpp` macht Gleitkomma zum
Uebersetzungsfehler; das Gegenstueck fuer die Multiplikation ist ein Groessentyp in
`kern::werte`, dessen `operator*` es gar nicht gibt oder der ueber `mal` fuehrt. Fuer
eingebaute Typen laesst sich das nicht nachruesten — deshalb muss die Entscheidung
**vor** `kern::werte` fallen und nicht danach.

Ich schlage die Richtung vor, ich entscheide sie nicht. Moeglich sind auch: ein Riegel
mit ausgeschriebener, begruendeter Verzeichnisliste (dann gehoert die Begruendung ins
Dokument, nicht in den Code), oder die ausdrueckliche Feststellung, dass die Zuordnung
Handarbeit bleibt und je Paket vom Pruefer ausgefuehrt wird. Auch das Letzte waere eine
Antwort — heute steht keine da.

## Was zu tun ist

`technik.md`, T7, um den Satz erweitern, **wodurch** Massnahme 4.3 durchgesetzt wird.
Nicht die Massnahme aendern; sie steht und ist mit 0052 umgesetzt.

## Abnahme

1. **T7 nennt den Durchsetzungsweg fuer Massnahme 4.3 beim Namen**, und zwar so, dass ein
   Bauagent daraus eine Handlung ableiten kann: entweder ein Werkzeug mit Dateiort und
   Aufruf, oder ein Typ mit Namen und dem Ort seiner Vorgabe, oder die ausdrueckliche
   Feststellung „Handarbeit je Paket" samt der Stelle, an der sie faellt. Ein Satz der
   Form „ist zu beachten" erfuellt die Bedingung nicht.
2. **Der Textriegel ist ausdruecklich behandelt**, mit einem Satz dazu, warum er gewaehlt
   oder verworfen wurde. Die drei Zeilen aus der Tabelle oben stehen als Beleg im
   Dokument oder sind durch einen Beleg ersetzt, der dasselbe zeigt. Eine Verwerfung ohne
   Grund ist keine Entscheidung.
3. **Die Zuordnung ist neu ausgefuehrt, und die Zahl im Dokument ist die selbst gemessene
   mit ihrem Bezugsstand.** Nicht die Zahl unten abschreiben: die Zuordnung ` \* ` ueber
   `kern/src` und `kern/include` selbst ausfuehren, **nachdem** die letzte eigene
   Aenderung geschrieben ist, das Ergebnis eintragen und den Bezugsstand danebenstellen.
   Zur Bedingung gehoert der Satz, dass die fuenfte Art -- zwei `i64` mit
   Groessenbedeutung -- weiterhin nicht vorkommt, oder, wenn sie inzwischen vorkommt, wo.
   Geprueft wird gegen eine Wiederholung der Messung, nicht gegen eine feste Zahl.

   **Berichtigung an Bedingung 3 (Projektmanager, 2026-09-08):** Hier stand
   *„`grep -rn ' \* ' kern/src kern/include` selbst ausfuehren"* und als Bezugsstand
   *„Datum und der Commit, auf dem gemessen wurde"*. **Beides verlangte eine Shell, und
   keine Rolle dieser Fabrik hat `Bash`** (`agents/lauf.py:NIE`, gemessen 2026-09-06) --
   der Commit ist fuer dich nicht lesbar, die Bedingung war so nicht erfuellbar. Was an
   ihre Stelle tritt und mit deinem Werkzeug geht:

   - **Die Messung** fuehrst du mit `Grep` aus, Muster ` \* `, `path` auf die beiden
     Verzeichnisse. Dasselbe Ergebnis, ohne Shell.
   - **Der Bezugsstand ist eine Aufzaehlung, keine Kennung.** Trag das Datum ein **und
     die Trefferzahl je Datei**, nicht nur die Summe. Der Pruefer wiederholt dieselbe
     Abfrage an seinem `HEAD`; weicht die Summe ab, zeigt die Liste in **welcher** Datei,
     und fremde Arbeit ist als fremd erkennbar. Eine blanke Summe kann das nicht, und
     genau daran scheitert der Vergleich, den diese Bedingung will.
   - **Der Grund, keine feste Zahl zu nehmen, steht unveraendert im Absatz darunter** und
     ist von dieser Berichtigung nicht beruehrt.

   *Warum keine feste Zahl (Projektmanager, 2026-09-04):* Heute steht im Dokument „52
   Zeilen", und der `kern-pruefer` mass am 2026-09-04 **54** -- die zwei neuen in
   `festkomma.hpp`, beide in einer zugelassenen Art. Diese Summe laeuft aber ueber
   `kern/src` und `kern/include`, und dorthin schreibt das offene Paket 0071
   (`schritt.cpp`, `schritt.hpp`). Stuende hier „54" als Sollwert, koennte fremde Arbeit
   diese Abnahme unerfuellbar machen, bevor der Architekt sie erreicht. Die Bedingung ist
   deshalb die Messung, nicht ihr heutiger Wert.

## Was du nicht tust

Kein Code. `kern/` und `werkzeuge/` gehoeren nicht zu diesem Paket, `kern::werte` erst
recht nicht. Und du senkst Massnahme 4.3 nicht ab: `mal` ist gebaut und geprueft, die
Frage ist allein ihre Durchsetzung.
