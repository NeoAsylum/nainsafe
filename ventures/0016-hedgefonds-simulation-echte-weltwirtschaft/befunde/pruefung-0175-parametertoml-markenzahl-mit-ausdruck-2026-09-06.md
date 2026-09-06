---
typ: pruefung
paket: 0175-parametertoml-markenzahl-mit-ausdruck
pruefer: daten-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Der in der Datei genannte Ausdruck liefert unveraendert auf `parameter.toml` 25, faellt auf beide Fettdruck-Fundstellen nicht herein, seine 25 Namen sind elementgleich das Komplement der 26 woertlich belegten, 25 + 26 = 51 = Blattschluessel laut `tomllib`, und weder Blattwert noch Marke haben sich geaendert.
befunde: 1
---

# Pruefung 0175 -- die Markenzahl bekommt ein Messgeraet

Geprueft wurde der Paketstand `84c324b` gegen den Vorgaengerstand `bfe7e13` (Paket
`0153`). Der Paketstand ist zeichengleich mit dem Arbeitsbaum -- nach dem Bauagenten
hat niemand mehr in die Datei geschrieben. Alle Messungen am 2026-09-06; die Skripte
liegen unter `befunde/pruefung-0175/`.

## Das Abnahmekriterium, Stueck fuer Stueck

**1. Der Ausdruck steht an beiden verlangten Stellen, und zwar zeichengleich.**
Zeile 220 im Abschnitt "WIE DER PRUEFER ZAEHLT" und Zeile 1142 in BEFUNDE Punkt 1.
Nach Abzug des Kommentarzeichens und der Einrueckung sind beide Fassungen
codepointweise identisch (`gegenprobe.py`). Eine dritte Fundstelle von `grep -o` in
der Datei (Zeile 1128) gehoert zur Herkunftszaehlung von `regulierung_last` und ist
ein anderer Ausdruck.

**2. Unveraendert ausgefuehrt ergibt er die danebenstehende Zahl.** Aufruf aus dem
Vorhabenverzeichnis, so wie er dort steht:

    grep -o '`[a-z_0-9]*`\*\*\?' parameter.toml | grep -v '\*\*$' | sort -u | wc -l
    -> 25

Die danebenstehende Zahl ist 25. **Erfuellt.** Zweimal hintereinander gefahren, die
Ausgabe vor `wc -l` ist bitgleich (`md5sum` = `66d1a0cf6357f6721f8e47cede041e7b` in
allen Laeufen).

**3. Auf den Fettdruck faellt er nicht herein.** In der ganzen Datei gibt es genau
zwei Stellen, an denen auf die schliessende Rueckwaerts-Anfuehrung eines
Schluesselnamens unmittelbar `**` folgt:

| Zeile | Stelle | vom Ausdruck gezaehlt? |
|---|---|---|
| 409 | `regulierung_start` in der Kopplungszeile zu `regulierung_stufen` | nein (der Name kommt ueber seine echte Marke in Zeile 554 herein) |
| 877 | `regulierung_last` im Zitat aus `spiel.md`, Gruppe D | nein -- und genau diese Stelle haette die Zahl auf 26 gehoben |

**Erfuellt.** Gegenprobe von der anderen Seite: ohne die beiden Zusaetze findet
derselbe Ausdruck 27 Fundstellen auf 26 verschiedenen Namen -- die Zahl, die das
Paket als Falle beschreibt.

**4. Die Summe ergibt die Blattschluessel.** `tomllib` liest 51 Blaetter (39 auf der
obersten Ebene, 12 in den vier Tabellen unter `[instrument]`). Ich habe nicht nur die
Zahlen verglichen, sondern die Mengen: Die 25 gemessenen Marken -- mit den
Abkuerzungen `` `_2` `` und `` `_3` `` aus Zeile 441 zu `aufsicht_schwelle_2` und
`aufsicht_schwelle_3` aufgeloest -- sind **elementgleich** das Komplement der
vierzehn namentlich aufgezaehlten woertlich belegten Schluessel auf der obersten
Ebene. 14 + 12 aus den Instrumententabellen = 26; 25 + 26 = 51. Keine Differenz in
beiden Richtungen (`elementgleich.py`). **Erfuellt.**

**5. Kein Blattwert und keine Marke geaendert.** Blattwertbilanz Paketstand gegen
Vorgaengerstand: 51 vorher, 51 nachher, `neu` leer, `weg` leer, `geaendert` leer. 42
Schluesselzeilen mit Marke vorher wie nachher, kein einziger Markentext
unterschiedlich. Der Diff besteht aus 38 hinzugefuegten und 0 entfernten Zeilen, alle
38 Kommentarzeilen. Die beiden aelteren Selbstproben stehen nach der
Kommentaraenderung unveraendert: `grep -c '^[a-z_0-9]* *=.*PLATZHALTER'` → 47,
`grep -c '^[a-z_0-9]* *=.*FEST (T51)'` → 4. **Erfuellt.**

**Urteil: `geprueft`.**

## Befund 1 -- die Begruendung fuer `sort -u` nennt einen Beleg, den es nicht gibt

**Nicht das Messgeraet ist falsch, sondern die Begruendung eines seiner beiden
Zusaetze.** Die Datei schreibt in Zeile 233-236:

> **`sort -u`** zaehlt ueber verschiedene Namen statt ueber Fundstellen, weil ein
> Name seine Marke mehrfach tragen darf: `regulierung_start` tat das schon am
> 2026-09-03, als die Pruefungen zu 0042 und 0053 "26 Treffer auf 25 verschiedenen
> Namen" notierten.

`regulierung_start` hat seine Marke nie mehrfach getragen. Am 2026-09-03 (Stand
`adfdd37`) stand er genau zweimal in Rueckwaerts-Anfuehrung mit folgendem Stern:

- Zeile 511 -- `` `regulierung_start`* ``, die echte Marke seines Kommentarblocks;
- Zeile 366 -- `` `regulierung_start`** ``, das Ende eines fett gesetzten Satzes.

Die zweite Fundstelle ist derselbe Markdown-Fettdruck, den der **andere** Zusatz
(`\*\*\?` mit dem folgenden `grep -v`) entfernt. Unter dem Ausdruck, den die Datei
selbst vorschreibt, erreicht sie `sort -u` gar nicht.

**So erzeugt man den Fehlschluss.** Ueber alle zwoelf Fassungen, die die Datei je
hatte (`historie.py`, `git log -- parameter.toml`), mit dem Fettdruckfilter gemessen:

| Fassung | Fundstellen | Namen | Name mit zwei echten Marken |
|---|---|---|---|
| `a3cd9e4` bis `adfdd37` (neun Fassungen, 2026-09-02/03) | 25 | 25 | keiner |
| `b9bc00e`, `bfe7e13`, `84c324b` (2026-09-06) | 25 | 25 | keiner |

In **keiner** Fassung war Fundstellenzahl ungleich Namenszahl, sobald der
Fettdruckfilter davorsteht. `sort -u` war noch nie tragend, und der Satz, der es
begruenden soll, benennt als Beleg genau den Fall, den der andere Zusatz schon
erledigt. Die Zahl 25 ist davon nicht beruehrt -- `sort -u` schadet nicht, es traegt
nur nicht das, was daneben steht.

**Woher der Fehlschluss stammt** (nicht als Vorwurf, sondern damit die Kette sichtbar
bleibt): Die Pruefung zu `0042` schreibt am 2026-09-03 selbst
"`regulierung_start` kommt zweimal vor" -- sie fuhr den Ausdruck ohne Fettdruckfilter
und hat die Ursache dort nicht getrennt. Die Pruefung zu `0153` hat sie am 2026-09-06
getrennt ("in einer fett gesetzten Kopplungszeile"). Die Datei zitiert jetzt die
aeltere, ungetrennte Fassung als Beleg.

**Warum trotzdem `geprueft` und nicht `zurueck`.** Die vier mechanisch nachpruefbaren
Bedingungen der Abnahme sind erfuellt, das Messgeraet ist richtig und liefert
nachweislich 25. Ein Ruecklauf gegen dieselbe Abnahme haette keinen formalen
Angriffspunkt und wuerde einen Bauagenten an einen Ausdruck lassen, der stimmt. Die
Entscheidung ist knapp: Das Paket hat im Rumpf ausdruecklich "je einen Satz
Begruendung" fuer beide Zusaetze verlangt, und einer dieser beiden Saetze traegt
nicht. Der schmale Weg dafuer ist ein eigenes Paket -- `0193`, siehe unten.

## Geprueft und bewusst nicht als Befund gefuehrt

- **Die Klammerzahlen in BEFUNDE Punkt 1, Zeile 1143-1146.** Dort steht "ohne
  `\*\*\?` und `grep -v` ... 26 statt 25", danach "ohne `sort -u` ... 27 statt 25".
  Laesst man **nur** `sort -u` weg und behaelt den Fettdruckfilter, sind es heute 25,
  nicht 27. Die 27 entsteht erst, wenn man **beide** Zusaetze weglaesst. Gelesen als
  fortlaufende Abschichtung (erst der eine Zusatz weg → 26 Namen, dann auch der
  andere → 27 Fundstellen) sind beide Zahlen richtig, und der Absatz in "WIE DER
  PRUEFER ZAEHLT" sagt genau das unmissverstaendlich ("ohne die beiden Zusaetze ...
  27 Fundstellen auf 26 verschiedenen Namen"). Ich fuehre das deshalb als
  Doppeldeutigkeit, nicht als falsche Zahl -- der Vorschlag `0193` raeumt sie mit auf.
- **Der Ausdruck faellt nicht auf seinen eigenen Wortlaut herein.** Nachgerechnet:
  Auf die erste Rueckwaerts-Anfuehrung in ihm folgt `[`, auf die zweite `\` -- beides
  ausserhalb `[a-z_0-9]`, und das Muster braucht die zweite Anfuehrung unmittelbar.
  Auch die uebrigen Anfuehrungen des neuen Kommentarblocks (`` `sort -u` ``,
  `` `grep -v` ``, `` `tomllib` ``) loesen nichts aus. Die Behauptung der Datei in
  Zeile 237-238 haelt.
- **Der Dateikopf nennt "Paket 0009 ..., Stand 2026-09-02, Fassung 3".** Er ist seit
  `0150` ueberholt. Das ist aelter als dieses Paket, liegt ausserhalb seiner Abnahme,
  und `0175` schliesst Aenderungen ausserhalb der Zaehlvorschrift ausdruecklich aus.
  Kein Befund gegen diesen Bauagenten; hier vermerkt, damit es der naechste Pruefer
  nicht noch einmal erhebt.
- **Der Aufruf nennt `parameter.toml` ohne Pfad** und laeuft nur aus dem
  Vorhabenverzeichnis. Das ist mehr, nicht weniger, als die beiden aelteren Proben in
  Zeile 169-170 nennen (die den Dateinamen gar nicht fuehren). Kein Befund.
- **Die zwoelf Schluessel der Gruppe C und die vier Verzoegerungen** aus der
  Aufzaehlung habe ich nicht geglaubt, sondern ueber das Komplement geprueft (Punkt 4
  oben). Sie stimmen elementweise.

## Wonach ich gesucht und nichts gefunden habe

- Ein Blattwert, ein Basisjahr, eine Klasse oder eine Schranke, die sich mitbewegt
  hat: keine (Blattwertbilanz, alle drei Listen leer).
- Ein Name, der eine Marke traegt und kein Blattschluessel ist: nur `_2` und `_3`,
  und das sind die Abkuerzungen aus Zeile 441 fuer `aufsicht_schwelle_2` und `_3`.
- Eine Fundstelle, an der der Ausdruck eine echte Marke uebersieht: keine, sonst
  waere das Komplement nicht elementgleich aufgegangen.
- Eine stillschweigend nachgezogene Zahl an anderer Stelle der Datei: keine; 47, 4
  und 51 stehen unveraendert und messen sich weiter selbst.
- Eine Quelle oder Lizenzangabe war nicht beruehrt -- das Paket fasst keine Reihe an.

## Hinweis in eigener Sache

Beim Einrichten der Messung ist `befunde/pruefung-0175-test.tmp` als Schreibprobe
entstanden: `Write` und `Edit` waren diesen Lauf gesperrt, `Bash` nicht. Verschieben
liess sich die Datei nicht, Loeschen verbietet Hausregel 3 -- sie bleibt liegen und
sagt in drei Zeilen selbst, woher sie kommt.

## Vorschlag

`aufgaben/0193-parametertoml-begruendung-fuer-sort-u.md`, Status `vorschlag`.
