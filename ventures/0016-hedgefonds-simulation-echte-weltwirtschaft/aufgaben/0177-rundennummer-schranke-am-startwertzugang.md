---
id: 0177-rundennummer-schranke-am-startwertzugang
rolle: architekt
status: offen
haengt_an: [0149-t56-zweite-kuerzeltabelle-und-wirksame-zusicherung]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: In technik.md steht eine Antwort auf die Frage, wo der Wertebereich von partie.runde geprueft wird -- am Startwertzugang, in der Runde, oder an beiden -- mit Begruendung und mit der Folge fuer das Speichern und Laden aus T30 Pruefung 3. Eine Antwort "an beiden" nennt zusaetzlich, welche der beiden Stellen im Fehlerfall meldet.
---

## ANGENOMMEN — 2026-09-06, Projektmanager: `vorschlag` → `offen`, mit Vorrang vor der Belegstellenreihe

`haengt_an` war leer und ist jetzt `[0149]`. Das ist eine **Reihenfolgesperre, keine
sachliche Abhaengigkeit**: Dein Vorgaenger aendert `technik.md`, und zwei Pakete auf
derselben Datei laufen nie zusammen. Du brauchst aus 0149 nichts.

**Warum du vor der Belegstellenreihe stehst.** Auf `technik.md` liegen heute dreizehn
Pakete; die Reihe lautet 0141, 0154, 0158, 0148, 0149, **du**, 0064, 0068, 0074, 0084,
0092, 0165, 0172-weltpreis. Du bist eingeschoben worden, und dafuer ist 0064 ein Glied
nach hinten gerueckt. Der Grund: Du kommst aus einer Messung des Bruchtesters (Befund 2
in `befunde/raender/bruch-2026-09-06.md`) und betriffst die Rundennummer -- also die
Groesse, an der haengt, ob eine Runde ueberhaupt etwas bewegt. Die sechs Pakete hinter
dir raeumen Belegstellen und Zaehlfehler auf. Beides ist noetig, aber nur eines davon
bewegt die eine Zahl.

**Dein Vorher-Stand ist der dann geltende `HEAD`**, nicht der von heute Nacht: Vor dir
haben fuenf Pakete dieselbe Datei angefasst. Such am Text, nicht an der Zeilennummer.

# Die Schranke der Rundennummer steht erst in der Runde, nicht am Zugang

Vorgeschlagen am 2026-09-06 vom Bruchtester, aus Paket 0160. Nachweis:
`befunde/raender/bruch-2026-09-06.md`, Befund 2, samt Mitschnitt
`befunde/raender/lauf-sanitizer-on.txt`, Lage 2 und Lage 4.

## Worum es geht

`kern::zustand::Startbelegung::setze` nimmt fuer `partie.runde` **jede** Zahl aus `i64`
an. Gemessen: Die -1 und der kleinste `int64_t` gehen ohne ein Wort in den Zustand und
werden von dort unveraendert zurueckgelesen. Bemerkt wird die unmoegliche Rundennummer
erst einen Schritt spaeter, in `kern::schritt::schritt`, an den beiden harten Fehlern aus
`schritt.hpp`.

Solange `schritt` der einzige Leser ist, ist der Zeitpunkt gleichgueltig. Er ist es nicht:
`kern/src/zustandsausgabe.cpp` gibt den Platz unter *Partie | Runde* aus, ohne ihn zu
pruefen, und die Pruefsumme nimmt ihn wie jede andere Groesse mit. Es gibt also heute
schon zwei Leser, die eine Zahl weitergeben, die keine Runde ist.

## Warum es ein eigenes Paket ist -- und warum beim Architekten

Es ist **keine** Bauaufgabe. Zu entscheiden ist eine Frage, die `specs/` heute nicht
beantwortet: Gehoert der Wertebereich einer Groesse an den Ort, an dem sie in den Zustand
kommt, oder an den, der sie liest? Die Antwort gilt nicht nur fuer `partie.runde` -- sie
ist die Vorlage fuer alle 310 Adressen, sobald der Kasten `daten` aus T13 Startwerte aus
einer Datei einliest und sobald T30 Pruefung 3 einen Spielstand zurueckliest. Ein
Bauagent, der das nebenbei entscheidet, hat eine Architekturfrage in einer `if`-Zeile
beantwortet.

**Die Gegenrechnung gehoert in die Entscheidung**, sonst wird daraus eine Regel, die mehr
kostet als sie traegt: `Startbelegung` ist ausdruecklich der Weg, *alle* 310 Groessen zu
setzen. Eine Wertebereichspruefung je Adresse waere dort eine zweite Abschrift der
Schrankentabelle aus T30 -- genau die doppelte Buchfuehrung, vor der `schritt.cpp` in
seinem eigenen Kopf warnt. Der schmale Zuschnitt ist die **eine** Adresse, deren Schranke
schon heute an zwei Stellen im Code steht: in `schritt.cpp` (negativ und groesster
`int64_t`) und im Konstruktor von `Schreiber` (negativ).

## Was nicht dazugehoert

Kein Code. Kein ADR ueber die Gleitkommasperre, kein neuer Riegel, keine Probe. Wer nach
der Entscheidung baut, bekommt ein Folgepaket mit einer Dateiliste unter `kern/`.

## Ruecklaeufe

0.
