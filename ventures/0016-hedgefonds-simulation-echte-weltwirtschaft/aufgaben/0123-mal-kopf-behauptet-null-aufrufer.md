---
id: 0123-mal-kopf-behauptet-null-aufrufer
rolle: kernbauer
status: vorschlag
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/festkomma.hpp]
abnahme: Der Absatz "Heute ohne Aufrufer" im Kopf von `mal` sagt den heutigen Stand -- dass `mal` Aufrufer in `kern::werte` hat und welche Rechenarten dort ueber ihn laufen -- und behauptet nicht mehr, `kern::werte` sei nicht gebaut. Die Zahl der Aufrufer ist selbst gemessen und mit ihrem Bezugsstand (Datum und Commit) genannt, nicht aus diesem Vorschlag abgeschrieben. Der Baum bleibt in beiden Profilen gruen.
---

# Der Kopf von `mal` sagt "heute ohne Aufrufer" -- `mal` hat fuenf

**Vorgeschlagen am 2026-09-05 vom `kern-pruefer` aus der Pruefung zu Paket 0087
(`urteil: geprueft`, `befunde: 0`).** Das Paket ist in Ordnung; dieser Vorschlag
betrifft einen Absatz, der 44 Zeilen unter seiner Einfuegestelle steht und seit
Paket 0002 nicht mehr stimmt.

## Der Sachverhalt

`kern/include/kern/festkomma.hpp` schreibt im Kopf von `mal`:

> **Heute ohne Aufrufer, und das ist kein Versehen.** Die fuenfte Rechenart aus T7
> -- zwei `i64` mit Groessenbedeutung nach T5 -- kommt noch nicht vor, weil
> `kern::werte` nicht gebaut ist.

Beide Behauptungen sind am geprueften `HEAD` falsch. `kern::werte` ist gebaut
(`kern/src/werte.cpp`, `werte_probe` gruen in beiden Profilen), und `mal` hat dort
**fuenf** Aufrufer: `tsd_in_cent` (125), `lobbypunkte_aus_geld` (145),
`positionswert_aus` (449), `korbbestand` (583), `fondsanteil` (666). Gemessen am
2026-09-05 auf `2ed2e0c`, mit einem Mustervergleich ueber `kern/` und `pruefstand/`
ausserhalb von `bau/` und `befunde/`.

Der Absatz stammt aus Paket 0052, das `mal` hinlegte, bevor es einen Aufrufer gab.
Er war damals richtig und ist es seit 0002 nicht mehr.

## Warum das nicht bloss Kosmetik ist

**Es ist eine Begruendung, keine Beschreibung.** Der Absatz erklaert, warum eine
Funktion ohne Aufrufer im Kopf stehen darf. Ein Leser, der ihn heute liest, schliesst
daraus, dass die fuenfte Rechenart im Kern noch nirgends vorkommt -- und genau dieser
Schluss ist der Anlass, die eigene Multiplikation nicht gegen T7 Massnahme 4.3 zu
pruefen. Der Satz spricht dem naechsten Bauagenten also eine Pruefung ab, die er
fuehren muesste. Das ist die Fehlerklasse, gegen die T7 in seiner Ueberschrift
antritt.

**Er widerspricht seinem eigenen Nachbarn.** Vierundvierzig Zeilen darueber steht
seit 0087 der Absatz zu `plus` und `minus`, der mit dem gegenteiligen Stand
argumentiert: dass eine Fassung im anonymen Namensraum von `werte.cpp` ihre
Abbruchpfade unpruefbar macht. Zwei benachbarte Absaetze derselben Datei sagen
Unvereinbares darueber, ob `kern::werte` existiert.

**Und diese Fabrik behandelt eine Behauptung in einem Kommentar als Pruefauftrag.**
Ein Kommentar, der eine Lage fuer erledigt erklaert, die es nicht ist, ist teurer
als kein Kommentar -- er ersetzt die Frage, statt sie zu stellen.

## Warum ein eigenes Paket und nicht Teil von 0074 oder 0087

**Nicht 0074.** Jenes Paket kennt den Satz -- es zitiert ihn ausdruecklich ("Der
Kopf von `mal` schreibt denselben Satz") --, aber seine Dateiliste ist
`specs/.../technik.md`, und sein Abschnitt "Was du nicht tust" sagt: "Kein Code.
`kern/` und `werkzeuge/` gehoeren nicht zu diesem Paket." Es wird also die
Dokumentseite richtigstellen und den Kopf stehen lassen. Danach sagen Dokument und
Code Verschiedenes -- schlechter als heute, wo beide dasselbe Falsche sagen.

**Nicht 0087.** Dessen Abnahme nennt den Absatz nicht, und ein Bauagent, der
ausserhalb seiner Abnahme umschreibt, ist genau das Verhalten, das der Dateischnitt
verhindern soll.

Die Reihenfolge zu 0074 ist gleichgueltig: verschiedene Dateien, verschiedene
Rollen. Laeuft 0074 zuerst, kann dieses Paket dessen Formulierung uebernehmen.

## Was ausdruecklich nicht dazugehoert

Keine Aenderung an `mal` selbst und keine an seiner Begruendung im Uebrigen -- die
Funktion ist mit 0052 gebaut und geprueft, das Zitat aus `technik.md` bleibt stehen.
Und keine Aussage darueber, **wodurch** Massnahme 4.3 durchgesetzt wird: Das ist die
Frage von 0074 und die Entscheidung des Architekten. Hier faellt nur der Stand von
heute an die Stelle eines Standes von vorgestern.
