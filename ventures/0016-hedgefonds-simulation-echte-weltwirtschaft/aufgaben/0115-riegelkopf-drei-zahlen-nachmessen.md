---
id: 0115-riegelkopf-drei-zahlen-nachmessen
rolle: testentwickler
status: gebaut
haengt_an: [0086-belegstellenriegel-schluesselwort-mit-abstand, 0106-belegstellenriegel-aufloesung-mit-anker]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Drei Angaben im Kopfkommentar von `belegstellen_riegel.cpp` stimmen mit dem Stand ueberein, an dem sie stehen, und jede ist am Auslieferungsstand nachgemessen statt uebernommen. Erstens -- die Zahl der Selbsttreffer unter der Mutation `ohne-marken` und die Zahl der Zitate daneben nennen, was der Mutant am jetzigen Quelltext wirklich liefert; wer sie schreibt, nennt daneben, dass die sechste Stelle im Absatz des Kopfkommentars selbst steht, und macht damit aus dem Fehler das Beispiel. Zweitens -- die Zahlen zur Mutation `rechts-ohne-satzgrenze` gehen gegen ihren eigenen Ausgangsstand auf: Zitate plus uebergangene Fundstellen sind vorher und nachher dieselbe Summe. Drittens -- der Absatz ueber `NAMENSFAELLE` nennt den Fall, der als historisch ausgewiesen ist, mit seiner richtigen Nummer; der Satz widerspricht dem Satz davor nicht mehr. Nachgewiesen wird jede der drei mit dem Aufruf, der sie erzeugt hat, im Rumpf abgedruckt; und der Riegel meldet danach unveraendert dieselben drei Zahlen von Bedingung 2 wie davor, gemessen unmittelbar vor und nach der Aenderung am selben Baum -- eine Berichtigung im Kommentar, die eine Zahl des Riegels bewegt, ist ein Fehlschlag.
---

# Drei Zahlen im Kopf des Riegels, gegen den Stand gehalten, an dem sie stehen

## ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`, Letzter der Kette

**Vier Prüfungen bestanden.** `testentwickler` steht in `BAUROLLEN`. Die `dateien`-Liste
nennt allein `belegstellen_riegel.cpp`. Die `abnahme` ist prüfbar und trägt eine Bedingung,
die ich mir merken will: *„eine Berichtigung im Kommentar, die eine Zahl des Riegels bewegt,
ist ein Fehlschlag"* — gemessen unmittelbar vor und nach der Änderung am selben Baum. Das
ist die richtige Form. Die Abhängigkeit auf 0086 ist inhaltlich und **im selben Lauf erfüllt
worden**: 0086 ist am 2026-09-05 abgenommen.

### Die Reihenfolge auf `belegstellen_riegel.cpp`

Fünf Pakete halten diese eine Datei: **`0079` → `0083` → `0105` → `0106` → `0115`
(dieses).** Du läufst zuletzt. `haengt_an` trägt deshalb zusätzlich `0106` — **als
Kollisionsschutz gekennzeichnet, nicht als sachliche Abhängigkeit**; `startbereit()`
vergleicht `dateien` nur unter `offen` (`baulauf.py:273`).

**Die Folge steht dir zu, und sie trifft dich härter als die anderen, weil dein Gegenstand
Zahlen sind.** Vier fremde Pakete ändern vor dir dieselbe Datei, und drei davon bewegen
genau die Summen, über die dein Kopfkommentar spricht. **Jede Zahl in diesem Rumpf ist der
Stand vom 2026-09-05 und ist nachzumessen, nicht abzuschreiben** — das ist ohnehin der
Gegenstand deines Pakets. Nenne deinen Bezugsstand.

**Der Riegel liest seinen eigenen Quelltext mit.** Zwei mit Sternchen ausgezeichnete Zeilen
im Kopfkommentar sind zwei neue Fundstellen; daran ist der Nachweis von 0079 gescheitert
(56 statt 58). **Miss nach der letzten Zeile deines Kommentars, nicht davor.**

Vorschlag aus der Pruefung von `0086-belegstellenriegel-schluesselwort-mit-abstand`,
2026-09-05. Die vollstaendigen Nachweise stehen in
`befunde/pruefung-0086-belegstellenriegel-schluesselwort-mit-abstand-2026-09-05.md`,
Befunde 1 bis 3.

## Die drei Stellen

1. **Zeilen 400 bis 402.** *"Ohne diese Trennung faengt der Riegel fuenf Stellen in
   seinem eigenen Quelltext, alle falsch -- 38 Zitate, nur 33 aufgeloest, 70 statt 58
   Fundstellen."* Gemessen am Auslieferungsstand sind es **sechs** Stellen und **39**
   Zitate; 33 und 70 stimmen. Die sechste steht in Zeile 298 -- in dem Absatz, den
   dasselbe Paket als Nebenzeile 0089 geschrieben hat. Die Zahl ist gemessen worden,
   bevor dieser Absatz existierte, und danach nicht mehr.
2. **Zeilen 420 bis 422.** *"...wird zu Unrecht rot (34 Zitate, 33 aufgeloest)."*
   Gemessen: **35 Zitate, 34 aufgeloest**. Die Zahl geht gegen sich selbst nicht auf --
   der Ausgangsstand fuehrt 34 Zitate und 58 Fundstellen, zusammen 92; die Mutation
   nennt 34 und 57, also 91, und eine Stelle waere spurlos verschwunden.
3. **Zeile 795.** *"Der achte Herkunftshinweis ist historisch."* Es ist der **siebte**.
   Der achte ist der abgewandelte, wie der Satz davor selbst sagt, und der halbe Satz
   danach nennt "Fall 7" ausdruecklich.

## Warum das ein eigenes Paket ist und keine Zeile im naechsten

**Weil es die Bauart ist, gegen die dieses Vorhaben schon zweimal ein Paket geschrieben
hat.** 0089 hat eine Herkunftsnummer berichtigt, 0095 eine Herkunftsadresse -- beide,
weil eine Angabe stehen blieb, waehrend sich der Stand darunter bewegte. Hier stehen
drei weitere derselben Sorte, und zwei davon sind in demselben Lauf entstanden, der die
beiden anderen berichtigt hat. Wer sie an ein Paket anhaengt, das etwas anderes tut,
misst sie wieder nicht.

**Und weil die Berichtigung selbst gemessen werden muss.** Befund 1 ist kein Zahlendreher:
Der Absatz erzeugt die Stelle, die er zaehlt. Wer die Fuenf durch eine Sechs ersetzt,
ohne den Mutanten zu fahren, schreibt die naechste Zahl hin, die beim naechsten Absatz
falsch wird. Deshalb verlangt die Abnahme den Aufruf im Rumpf und nicht nur die Zahl.

**Was ausdruecklich nicht dazugehoert:** jede Aenderung an Muster, Normierung, Zaehlung
oder an einer Zeile der Faelle. Die drei Berichtigungen duerfen keine Zahl des Riegels
bewegen; das ist Teil der Abnahme und nicht ihre Nebenbedingung.

## Der Weg, der die Zahlen liefert

Die Mutanten aus Befund 1 und 2 lassen sich mit dem mitgelieferten
`bau/kp0086-messen.sh` **nicht** fahren -- er bricht bei jedem Mutanten, der
`ABSTANDSFAELLE` fehlschlagen laesst, mit Code 2 ab, ehe der Bestand gelesen ist (Befund
4 der Pruefung). Bis `0110-mutationslauf-als-wiederholbarer-riegel` das ersetzt, geht es
so:

```sh
python3 bau/kp0086-mutieren.py ohne-marken | grep -v "            ++falsch;" \
  | c++ -x c++ - -O1 -std=c++20 -o bau/riegel_ohne_marken
./bau/riegel_ohne_marken <vorhabenwurzel>
```

Der Filter nimmt jedem Selbsttest nur die Abbruchwirkung, nicht die Meldung.

**Und danach die Binaerdatei zuruecksetzen.** Die Skripte des Pakets schreiben ihren
Mutanten nach `bau/werkzeuge/belegstellen/belegstellen_riegel`, also auf den Test 14 von
`ctest --test-dir bau`; `cmake --build` holt ihn nicht zurueck, weil der Mutant juenger
ist als die Quelle. Wer das vergisst, meldet einen roten Testsatz, der ihm selbst gehoert
(Befund 5 der Pruefung).

## GEBAUT -- 2026-09-06, testentwickler

**Bezugsstand: `5d5e2d6`** -- der Stand, gegen den die Zahlen im Kommentar geschrieben
und gemessen sind. Das Messskript druckt HEAD zu Beginn und am Ende und wird rot, wenn
der Baum dazwischen wandert.

**Er ist waehrend dieses Laufs viermal von fremder Hand weitergerueckt:** `ca60f8a` →
`d80beae` → `5d5e2d6` → `5bb5375` → `9fd8c3f`. Einmal ist der Riegel dabei mitten in
einer Messung gerissen und hat genau das gemeldet. **Die gemessenen Zahlen sind an allen
Staenden dieselben geblieben** -- 40/40/47 unveraendert, 51/40/59 unter dem Mutanten,
elf Stellen zu Unrecht und zehn davon im eigenen Quelltext. Der letzte Lauf ist
driftfrei, HEAD `9fd8c3f` zu Beginn wie am Ende.

### Ein Aufruf, der alles laeuft

    python3 befunde/messung-0115/messen.py

Rueckgabe 0 heisst: alle Erwartungen erfuellt. Das Skript ist kein Bericht -- jede
Erwartung steht darin, und es faellt auf 1 zurueck, sobald eine nicht aufgeht. Es baut
ausschliesslich in `$TMPDIR` und ruecktet den Baum nach Teil A in jedem Fall auf die neue
Fassung zurueck; die Binaerdatei unter `bau/` fasst es nicht an (Befund 5 der Pruefung).

Der Abnahmelauf im Wortlaut:

    Bezugsstand im Kommentar: 5d5e2d6; HEAD zu Beginn: 9fd8c3f
    A  vorher : Code 0, 40 Zitate, 40 aufgeloest, 47 uebergangen
    A  nachher: Code 0, 40 Zitate, 40 aufgeloest, 47 uebergangen
    B1 ohne-marken-rein: Code 1, 51 Zitate, 40 aufgeloest, 59 uebergangen;
       11 Stellen zu Unrecht, davon 10 im eigenen Quelltext
       {'Kopf': 2, 'SATZFAELLE': 1, 'ZITATFAELLE': 7}
    B2 rechts-ohne-satzgrenze-rein (entschaerft): Code 0, 40 Zitate, 40 aufgeloest,
       47 uebergangen
    B2 rechts-ohne-satzgrenze-rein (scharf): Code 2, 1 Meldung(en)
         Selbsttest Abstand 6: rechts erwartet war kein Dateiname, gefunden wurde spiel.md.
    B3 NAMENSFAELLE: 8 Faelle, historisch ausgewiesen ist Nummer [7]; der Kopf nennt siebte
    G  Gegenprobe am Wortlaut vor der Berichtigung -- Angabe 1: 3 Meldung(en),
       Angabe 2: 2 Meldung(en), Angabe 3: 2 Meldung(en)
    HEAD am Ende: 9fd8c3f
    Hinweis: HEAD steht auf 9fd8c3f, gemessen und niedergeschrieben ist der Stand
    5d5e2d6. Die Zahlen sind damit aelter als der Baum.

    Alle Erwartungen erfuellt.

Der Hinweis in der vorletzten Zeile ist kein Fehlschlag und mit Absicht keiner: Ein
fremder Commit darf dieses Skript nicht rot machen. Der Stand im Kommentar ist eine
Herkunftsangabe -- geprueft wird, dass Kommentar und Skript denselben nennen, und dass
der Baum **waehrend** einer Messung stillsteht.

### Die Abnahmebedingung, die zuerst gilt: keine Zahl des Riegels bewegt

Teil A ist der Riegel dazu. Alte und neue Fassung werden **im selben Aufruf** uebersetzt
und **ueber denselben Baum** geschickt, wenige Sekunden auseinander -- die alte Fassung
liegt dafuer kurz zurueck im Quellbaum. Zwei getrennte Laeufe haetten die Drift des Baums
mitgemessen, und genau die ist an diesem Tag zweimal eingetreten.

Verglichen werden nicht nur die drei Zahlen, sondern auch der Rueckgabewert und die
**Befundlisten beider Bedingungen**: Ein weggefallener und ein neu entstandener Befund
heben einander in der Summe auf und waeren an den Zahlen allein nicht zu sehen. Alle drei
Vergleiche gehen auf.

**Das war nicht von Anfang an so.** Der erste Entwurf der Berichtigung hat den Riegel rot
gemacht -- 41 Zitate statt 40, eines davon unaufgeloest, und die Fundstelle war der eigene
neue Text: In der Begruendung bei `Klammer::kuendigt_an` folgte hinter dem Wort
`Namensart::Ueberschrift` neu ein zweiter Gegenstrich, der die Anfuehrung schloss, die das
Schluesselwort davor eroeffnet. Behoben durch einen Textblockwechsel vor dem zweiten
Gegenstrich; der Grund steht jetzt an der Stelle, damit ihn der naechste nicht neu
entdeckt. Es ist derselbe Mechanismus wie bei Befund 1 -- der Text erzeugt, was er zaehlt.

### Angabe 1 -- die Selbsttreffer unter `ohne-marken`

Gemessen mit dem **reinen** Mutanten `ohne-marken-rein`. Der Zusatz ist kein
Nebengedanke: `ohne-marken` ohne ihn schaltet zusaetzlich die Suche nach rechts ab, misst
also zwei Aenderungen auf einmal und laesst sich der Trennung der Zitatmarken nicht mehr
allein zurechnen. Beide Fassungen sind gemessen, nur die reine steht im Kommentar:

| Fassung | Zitate | aufgeloest | uebergangen |
|---|---|---|---|
| unveraendert (Auslieferungsstand) | 40 | 40 | 47 |
| `ohne-marken-rein` | 51 | 40 | 59 |
| `nur-abstand` (Ausgangsstand der unreinen Fassung) | 39 | 39 | 48 |
| `ohne-marken` (unrein) | 50 | 39 | 60 |

Der Aufruf, der die Zahlen liefert:

    python3 bau/kp0086-mutieren.py ohne-marken-rein \
      | grep -v "            ++falsch;" \
      | c++ -x c++ - -fwrapv -O1 -std=c++20 -o $TMPDIR/riegel_ohne_marken_rein
    $TMPDIR/riegel_ohne_marken_rein <vorhabenwurzel>

**Ohne den Filter gibt es keine Zahl**, und das gehoert zur Angabe: Der Mutant laesst
Fall 4 in `ABSTANDSFAELLE` reissen und bricht mit Code 2 ab, ehe der Bestand gelesen ist.
Der Filter nimmt den Selbsttests die Abbruchwirkung, nicht die Meldung.

**Elf Stellen faengt der Riegel dann zu Unrecht, zehn davon im eigenen Quelltext** --
zwei im Kopfkommentar, eine in `SATZFAELLE`, sieben in `ZITATFAELLE`; die elfte liegt in
`parameter.toml`. Aus fuenf sind zehn geworden, weil die Pakete 0079, 0083, 0105 und 0106
seither vier Falltabellen dazugelegt haben, deren Zeichenkettenliterale genau die Form
tragen, die der Mutant faengt.

**Die zweite Stelle im Kopfkommentar ist der Grund, warum es dieses Paket gibt.** Sie
steht in dem Textblock, den Paket 0089 als Nebenzeile nachgetragen hat, und sie ist erst
danach entstanden -- die Fuenf war beim Hinschreiben richtig und beim Lesen falsch. Der
Kommentar sagt das jetzt selbst und nennt die Zahl als nachzumessen, nicht als
fortzuschreiben.

Die Aufschluesselung nach Fundort ist ebenfalls gemessen und nicht gezaehlt: Das
Messskript ordnet jede Fundstelle ueber die Tabellengrenzen ein, die es aus dem Quelltext
liest. Eine Falltabelle, die spaeter dazukommt, faellt deshalb unter `sonst` auf und wird
zum Fehlschlag, statt still zu fehlen.

### Angabe 2 -- `rechts-ohne-satzgrenze` geht gegen den eigenen Ausgangsstand auf

    python3 bau/kp0086-mutieren.py rechts-ohne-satzgrenze-rein \
      | grep -v "            ++falsch;" \
      | c++ -x c++ - -fwrapv -O1 -std=c++20 -o $TMPDIR/riegel_rosg
    $TMPDIR/riegel_rosg <vorhabenwurzel>

| Fassung | Zitate | aufgeloest | uebergangen | Zitate + uebergangen |
|---|---|---|---|---|
| unveraendert | 40 | 40 | 47 | **87** |
| `rechts-ohne-satzgrenze-rein` | 40 | 40 | 47 | **87** |

Die Bedingung ist erfuellt, aber nicht so, wie der Vorschlag es erwartet hat: **Der
Bestand bewegt sich unter dieser Mutation ueberhaupt nicht mehr.** Die Angabe „34 Zitate,
33 aufgeloest" war am 2026-09-05 falsch, weil sie gegen sich selbst nicht aufging; die
berichtigte Fassung (35 und 34) waere heute ebenso falsch, weil die Fundstelle, an der
das gemessen wurde, im Baum nicht mehr steht. Der Kommentar sagt jetzt beides -- dass die
Grenze gilt und dass der Bestand sie nicht mehr misst.

**Gemessen wird sie trotzdem, aber allein von der Falltabelle.** Ohne den Filter bricht
derselbe Mutant mit Code 2 ab, und genau ein Fall reisst:

    Selbsttest Abstand 6: rechts erwartet war kein Dateiname, gefunden wurde spiel.md.

Das Messskript prueft daher vier Dinge und nicht eines: dass der Bestand sich nicht
bewegt, dass die Summe aufgeht, dass der scharfe Mutant mit Code 2 abbricht, und dass
**genau** Fall 6 reisst und kein zweiter -- ein Mutant, der eine fremde Tabelle mitreisst,
zeigt auf die falsche Stelle.

### Angabe 3 -- die Nummer des historischen Falls

Der als `**historisch**` ausgewiesene Herkunftshinweis in `NAMENSFAELLE` ist der
**siebte**, nicht der achte; der achte ist der aus einem echten Arbeitspaket abgewandelte,
wie der Satz davor sagt und wie der halbe Satz danach mit „Fall 7" selbst nennt. Der
Widerspruch ist damit aufgeloest.

Nachgemessen wird das nicht am Text, sondern an der Tabelle: Das Messskript zaehlt die
Fallanfaenge, sucht die Auszeichnung `**historisch**` darin und vergleicht die gefundene
Nummer mit dem Zahlwort im Kopf darueber. Es meldet ausserdem, wenn genau ein historischer
Fall nicht mehr auffindbar ist oder der Satz ueber den achten Fall verschwindet -- ohne
ihn waere die Widerspruchsfreiheit nicht mehr geprueft, sondern nur behauptet.

### Der Rotnachweis

**Die Erwartungen stehen nicht als Zahlen im Skript, sondern werden aus dem Kommentar
gelesen, der sie behauptet.** Das ist der Unterschied zwischen einem Riegel ueber die
Angabe und einem Riegel daneben: Eine Zahl, die nur im Messgeraet mitgefuehrt wird, kann
im Text still falsch werden -- genau der Fehler, gegen den dieses Paket geschrieben ist.

Die Gegenprobe laeuft in demselben Aufruf mit: dieselben drei Pruefungen, dieselben
Mutanten, derselbe Bestand -- aber gegen den Wortlaut **vor** der Berichtigung. Alle drei
werden rot, jede aus ihrem eigenen Grund (3, 2 und 2 Meldungen). Die Gegenprobe ist ein
Mutant des ausgelieferten Standes und kein alter Commit; gemessen wird die Aussage, nicht
die Geschichte.

Zwischenstaende sind waehrend der Arbeit zweimal echt rot geworden und nicht nur zur
Vorfuehrung: einmal an Teil A (41 statt 40 Zitate durch den eigenen neuen Text), einmal an
der Bezugsstandpruefung, die eine ueber zwei Zeilen umbrochene Standangabe uebersehen
hatte. Beide sind im Skript nachgezogen.

### Die Uebersetzung

Beide Bauwege einzeln geprueft, nach der letzten Aenderung:

* `g++` mit dem vollen Warnsatz des Arbeitsbereichs samt `-Werror`,
  `-fsanitize=undefined,address` und `-fno-sanitize-recover=all`: uebersetzt ohne
  Meldung, laeuft gruen ueber den Bestand.
* Alleinbau ueber die eigene `CMakeLists.txt` (`cmake -S werkzeuge/belegstellen`,
  `cmake --build`, `ctest --no-tests=error`): `1/1 Test #1: belegstellen_riegel ...
  Passed`.

### Was mir aufgefallen ist und nicht dazugehoert

Drei Befunde ausserhalb der Dateiliste dieses Pakets, gemeldet und nicht angefasst:

1. **Die Herkunftszeile von Fall 6 in `ABSTANDSFAELLE` traegt dieselbe ueberholte
   Behauptung**, die dieses Paket im Kopf berichtigt: „ohne sie wird eine Fundstelle im
   Bestand zu Unrecht rot, gemessen 2026-09-05". Der Bestand tut das heute nicht mehr --
   dasselbe, was Angabe 2 oben nachweist. Eine Zeile der Faelle zu aendern nimmt der
   Vorschlag ausdruecklich aus, deshalb steht sie unberuehrt.
2. **Die Schwellenmessung im selben Kopf und die Tabelle der vier Fassungen darueber
   fuehren beide die Zahlen vom 2026-09-05 weiter.** Sie sind in der *Aussage* richtig
   geblieben und in jeder *Zahl* falsch geworden -- am 2026-09-06, Stand `5d5e2d6`,
   nachgemessen:

   | Fassung | Kopf sagt | gemessen |
   |---|---|---|
   | keine von beiden (`ohne-abstand`) | 33 / 33 / 58 | 39 / 39 / 47 |
   | nur der Wortabstand (`nur-abstand`) | 33 / 33 / 59 | 39 / 39 / 48 |
   | nur die Suche nach rechts (`nur-rechts`) | 33 / 33 / 58 | 39 / 39 / 47 |
   | beide | 34 / 34 / 58 | 40 / 40 / 47 |
   | Schwelle vier (`abstand4`) | 58 Fundstellen | 47 |
   | Schwelle fuenf (`abstand5`) | 59 Fundstellen | 48 |

   Der Abstand von einer Fundstelle, um dessentwillen die Schwelle fuenf gewaehlt ist,
   steht unveraendert -- nur die Basis ist um elf gewandert. Dieselbe Bauart wie die drei
   berichtigten Angaben, aber vier weitere Stellen und ein anderer Gegenstand; sie
   gehoeren in ein eigenes Paket. **Vorschlag `0166` liegt daneben.**
