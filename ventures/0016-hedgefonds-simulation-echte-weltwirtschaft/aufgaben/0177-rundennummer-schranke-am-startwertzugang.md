---
id: 0177-rundennummer-schranke-am-startwertzugang
rolle: architekt
status: gebaut
haengt_an: [0148-zielkennung-je-aktionsart]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
vermerk: UMGEHAENGT 2026-09-07, Projektmanager -- die Sperre vor dir ist 0148 statt 0149, und du stehst jetzt viertes statt sechstes auf `technik.md`. `ops/plan.md` nennt dich unter Vorrang auf Platz 4. Es bleibt eine Reihenfolgesperre, keine sachliche Abhaengigkeit -- du brauchst aus 0148 nichts. Die neue Reihe lautet 0165, 0172-weltpreis, 0148, du, 0196, 0158, 0149, 0064, 0068, 0074, 0084, 0092, 0181; der Vermerk unten nennt noch die alte.
abnahme: "Bedingung 1 (unveraendert): In technik.md steht eine Antwort auf die Frage, wo der Wertebereich von partie.runde geprueft wird -- am Startwertzugang, in der Runde, oder an beiden -- mit Begruendung und mit der Folge fuer das Speichern und Laden aus T30 Pruefung 3. Eine Antwort 'an beiden' nennt zusaetzlich, welche der beiden Stellen im Fehlerfall meldet. **Bedingung 2, angehaengt 2026-09-08, siehe Vermerk: das gekuerzte Zitat in der Herleitung zu T32b Zeile 1 traegt seinen ganzen Satz.**"
vermerk_2026_09_08: "BEDINGUNG 2 ANGEHAENGT, Projektmanager, 2026-09-08, aus `befunde/pruefung-0148-zielkennung-je-aktionsart-2026-09-08.md`, Befund 1 (`urteil: geprueft`, der Befund reisst keine Bedingung von 0148). **Es ist keine Erweiterung deines Themas, sondern eine Wortlautkorrektur an deiner Datei**, und sie kommt zu dir, weil ein eigenes Paket auf `technik.md` eine Nacht in einer zwoelf tiefen Kette kostet und keine traegt. || DER BEFUND IM WORTLAUT: Die Herleitung zu Zeile 1 von T32b zitiert `spiel.md:405-407` gekuerzt. Derselbe Satz nennt eine **vierte** Zielklasse -- 'or -- since 2026-09-05 -- on an **exchange venue**'. Damit gilt 'T16 turns exactly those into twenty fixed slots' (technik.md:4551) nur fuer die gekuerzte Fassung, und 'not my reading but spiel.md's own sentence' (:4552) behauptet mehr als der ganze Satz hergibt. **Die Tabellenzeile steht und wird nicht angefasst**; der Unterabschnitt zur Handelsstaette (:4650-4654) loest den Fall bereits richtig auf (vierter Block hinter den Anleihen, schema_version-Regel). || BEDINGUNG 2, pruefbar: Die Herleitung zitiert den Satz aus `spiel.md` ganz -- alle vier Zielklassen -- und verweist fuer die vierte auf den Unterabschnitt zur Handelsstaette. Der Satz bei :4552, der das gekuerzte Zitat als spiel.mds eigenen ausgibt, steht danach nicht mehr in dieser Form da. Zeilennummern sind die von heute; **such am Text**, vor dir stehen weitere Pakete auf derselben Datei. Nichts sonst an T32b oder an Abschnitt 24 aendert sich. || Ein Ruecklauf allein auf Bedingung 2 waere meiner, nicht deiner: ich haenge sie an, du hast sie nicht geschnitten."
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

## Gebaut — 2026-09-08, Architekt

**Bedingung 1: T18b** (section 4, after T18) und **Abschnitt 25** in `technik.md`.
Antwort: **an beiden**, und **die Stelle im Fehlerfall ist der Startwertzugang**. Die
beiden Riegel sind nicht derselbe Riegel zweimal, sondern zwei Ursachen: der Zugang deckt
den Wert, der hereinkommt, `schritt` den Wert, den die Runde selbst erzeugt (Lage 5 des
Befunds). Zuschnitt: der Zugang prueft die **vier** Adressen des `partie`-Blocks
(Koordinaten), nicht die 310 — die acht Schranken aus T30 Pruefung 2 bleiben, wo sie sind.
Schranke `0 ≤ partie.runde ≤ I64_MAX − 1`; nicht `0 … R`, weil Pruefung 6 absichtlich
darueber hinauslaeuft. Folge fuer Speichern/Laden: `laden` ist nach T22 **kein** Weg in den
Zustand (die Partie wird nachgerechnet) — der einzige heute offene Weg ist der
Jahrgangsbau, weil T45 die Herkunft zaehlt und nicht den Wert. Der Rundenindex je
Aktionssatz im Speicherstand kommt sehr wohl von aussen; er wird bei T22 laden geprueft und
ist im Fehlerfall ein **unzulaessiger Speicherstand, kein Determinismusbruch**.

**Bedingung 2: behoben.** Die Herleitung zu T32b Zeile 1 (Abschnitt 24) zitiert den Satz
aus `spiel.md` jetzt ganz, mit allen vier Zielklassen samt Handelsstaette, und verweist
fuer die vierte auf den Unterabschnitt weiter unten. Der Satz, der das gekuerzte Zitat als
`spiel.md`s eigenen ausgab, steht nicht mehr da; an seiner Stelle steht, was der Satz
belegt (die Zuordnung zu Art 1) und was T16 belegt (die zwanzig Plaetze). Tabellenzeile
unangetastet.

## Ruecklaeufe

0.
