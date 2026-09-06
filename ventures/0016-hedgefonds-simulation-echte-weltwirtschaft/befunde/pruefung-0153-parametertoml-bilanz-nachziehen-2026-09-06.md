---
typ: pruefung
paket: 0153-parametertoml-bilanz-nachziehen
pruefer: daten-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Alle fuenf Teilbedingungen an der Datei selbst nachgemessen -- die zwei vorgeschriebenen `grep -c`-Ausdruecke (47/4), die `tomllib`-Blattzaehlung gegen die Gruppensumme (51/51), Vollstaendigkeit und Laenge der Aufzaehlung unter BEFUNDE Punkt 1 (26, mit `regulierung_last`) und den ersetzten Vermerk im Kopf der Gruppe D.
befunde: 1
---

Geprueft am Stand `83faa06` (HEAD). Der Arbeitsbaum ist bytegleich mit dem
eingecheckten Blob (`git show HEAD:<pfad>` gegen die Datei, `==` auf den Bytes)
-- die Messungen unten gelten also fuer den versionierten Stand und nicht fuer
eine unversionierte Fassung. Baucommit des Pakets: `bfe7e13`, Bezugsstand
`b9bc00e` (Paket 0150).

## Was die Abnahme verlangt und was gemessen wurde

### 1. Die zwei vorgeschriebenen Ausdruecke gegen die Zahlen im Kopf

Beide Ausdruecke woertlich so aufgerufen, wie die Datei sie selbst vorschreibt
(Zeilen 169 und 170), an der Zieldatei:

```
grep -c '^[a-z_0-9]* *=.*PLATZHALTER'  -> 47
grep -c '^[a-z_0-9]* *=.*FEST (T51)'   -> 4
```

Im Kopf steht daneben `-> 47` und `-> 4` (Zeilen 169/170) sowie im Fliesstext
"Davon 47 Schluesselzeilen mit der Marke PLATZHALTER und 4 mit der Marke FEST
(T51)" (Zeile 165). **Uebereinstimmung.**

Nicht nur die Zahlen, sondern die **Partition** nachgerechnet, weil eine Summe
zwei kompensierende Fehler verdeckt:

| Probe | Ergebnis |
|---|---|
| Zeilen, auf die der Anker `^[a-z_0-9]* *=` ueberhaupt passt | 51 |
| davon mit Marke PLATZHALTER | 47 |
| davon mit Marke FEST (T51) | 4 |
| Schnitt beider Mengen | leer |
| Zeilen mit Anker, aber ohne beide Marken | keine |

Die 51 Ankerzeilen sind damit lueckenlos und ueberschneidungsfrei in 47 + 4
zerlegt. Der von der Datei behauptete Zusammenhang "47 + 4 = 51" (Zeile 172)
ist also nicht bloss arithmetisch richtig, sondern trifft dieselbe Menge.

### 2. Gruppensumme im Kopf gegen die Blattschluessel aus `tomllib`

`tomllib.load` auf die Datei, rekursiv bis zum Skalar gezaehlt (Listen
elementweise -- hier kommt keine vor): **51 Blattschluessel.** Im Kopf steht
"51 Schluessel" (Zeile 156). **Uebereinstimmung.**

Die Gruppentabelle darueber ist nicht nur in der Summe geprueft, sondern
zeilenweise -- eine richtige Summe aus falschen Summanden waere sonst
durchgegangen. Die Gruppengrenzen sind die `# GRUPPE`-Kopfzeilen der Datei
(Zeilen 244, 388, 541, 594, 807, 931); gezaehlt wurden die Ankerzeilen je
Bereich:

| Zeile im Kopf | steht dort | gezaehlt | Namen |
|---|---|---|---|
| Gruppe A, Tabelle in T27 | 10 | 10 | `stufenweite` ... `regulierung_stufen` |
| Gruppe A, Instrumente nach T51 | 12 | 12 | 4 x `schrittweite`/`instrument_min`/`instrument_max` |
| Gruppe B, Fliesstext in T27 | 12 | 12 | `schwelle_v` ... `regulierung_start` |
| Gruppe B2, "Verzoegerungen" | 4 | 4 | `verzoegerung_lobby` ... `regierungsdruck_dauer` |
| Gruppe C, "Elastizitaeten" | 12 | 12 | `abschreibungsrate` ... `innerjahresausschlag_faktor` |
| Gruppe D, nach Fassung 3 dazu | 1 | 1 | `regulierung_last` |
| **Summe** | **51** | **51** | |

**Jeder einzelne Summand stimmt**, nicht nur ihre Summe. Gruppe D enthaelt
tatsaechlich genau einen Schluessel (`regulierung_last`, Zeile 927) -- der Satz
"bis heute der einzige Schluessel der Gruppe D" (Zeile 159) haelt.

Die Ordinalangabe daneben haelt ebenfalls: "Die sechste Zeile ist am 2026-09-06
dazugekommen" (Zeile 158) -- die Gruppentabelle hat sechs Datenzeilen (149-154),
und Gruppe D ist die sechste. Das war bei `0150` die Stelle, an der eine
Ordinalangabe danebenlag (Befund 3 meiner Pruefung vom 2026-09-06); hier nicht.

### 3. Die Aufzaehlung unter BEFUNDE Punkt 1

- **Enthaelt `regulierung_last`?** Ja, Zeile 1092, zwischen `startkapital` und
  dem Verweis auf die Instrumententabellen.
- **Stimmt die genannte Zahl mit der Laenge der Aufzaehlung?** Der Text sagt
  "diese 26" (Zeile 1089) und rechnet es selbst vor: "Vierzehn einzeln genannte
  und zwoelf aus den Instrumententabellen, zusammen 26" (Zeilen 1094/1095).
  Nachgezaehlt: einzeln genannt sind `stufenweite`, `stufen_max`,
  `ausstiegsabschlag`, `zwangsabschlag`, `aufschlag`, `lobbykosten`,
  `beteiligungsrabatt`, `gegenlobby_satz`, `druck_max`, `regulierung_stufen`,
  `schwelle_v`, `schwelle_e`, `startkapital`, `regulierung_last` = **14**; dazu
  die zwoelf Instrumentenschluessel = **26**. **Uebereinstimmung.**
- **Gegenprobe auf den Zaehler.** Der Punkt sagt "25 der 51 Namen sind
  gebildet". Die Datei definiert "gebildet" selbst als `*`-Marke hinter dem
  Schluesselnamen im Kommentar (Zeile 183). Gezaehlt: **genau 25 Marken**
  (Zeile 414 dreimal, dann 437, 449, 461, 470, 501, 527, 553, 564, 573, 582,
  611, 622, 632, 646, 657, 673, 685, 703, 717, 729, 779, 789). Diese Menge ist
  elementgleich mit der Aufzaehlung "Gebildet sind die uebrigen 25"
  (Zeilen 1106-1110), gelesen als 2 + 3 + 1 + 3 + 4 + 12. `regulierung_last`
  traegt **keine** Marke -- wie Zeile 1098 behauptet.
- **25 + 26 = 51**, beide Teilmengen disjunkt, zusammen die 51 Blattschluessel.
  Die Selbstaussage in Zeile 1096 haelt.

### 4. Der Vermerk im Kopf der Gruppe D -- ersetzt, nicht geloescht

`git diff bfe7e13~1 bfe7e13` zeigt an dieser Stelle (jetzt Zeilen 824-840) den
Austausch des alten Absatzes gegen einen neuen, der den erreichten Stand nennt
("Der Kopf dieser Datei ist nachgezogen") **und** den Weg dorthin behaelt
("Was 0150 hier hinterliess und 0153 berichtigt hat, damit der Weg
nachvollziehbar bleibt: ... nannte 50 Schluessel ... BEFUNDE Punkt 1 '25 der 50
Namen'"). Der Verweis auf das noch offene Paket ist weg, die Information nicht
-- genau das verlangt die Abnahme und Hausregel 3. **Erfuellt.**

## Was ausserhalb der Abnahme geprueft wurde

**Die Ausschluesse des Pakets halten.** `regulierung_last = 0  # PLATZHALTER`
(Zeile 927) -- keine Kalibrierung. Der Block aus `0150` ist ausser dem Vermerk
unberuehrt (der Diff hat dort genau einen Hunk). Die Klasse-4-Frage im Kopf ist
nicht angefasst.

**Die historische Aussage, die dieses Paket neu formuliert hat, am historischen
Blob nachgemessen** statt geglaubt. Zeile 178/179 sagt jetzt, der unverankerte
Aufruf habe "47 und 5 statt der damals richtigen 46 und 4" geliefert. Gemessen
an `b9bc00e~1` (Stand vor `0150`) mit denselben zwei Ausdruecken, einmal mit und
einmal ohne Zeilenanker: verankert 46 und 4, unverankert 47 und 5, 50
Blattschluessel. **Stimmt.** Dieselbe Messung an `f0cae94` und `f0cae94~1`
zeigt, dass der Unterschied genau mit dem Einzug jenes Kommentarblocks entsteht.
Der Zusatz "der damals richtigen" ist damit belegt und nicht bloss plausibel --
und er ist noetig, weil die heute richtige Zahl 47 zufaellig die damals falsche
ist.

**Der Zusatz zur Belegdichte, den der Bauagent von sich aus mitgeliefert hat**
(Zeilen 1099-1103): "an zehn Stellen ... technik.md sechs, spiel.md vier ...
`grep -c` ... liefert fuer spiel.md deshalb 3 statt 4, weil eine Zeile den Namen
zweimal traegt". Nachgemessen in `specs/0016-.../`: `grep -o` liefert technik.md
6, spiel.md 4, `daten.md` und `zielbild.md` je 0; `grep -c` liefert fuer spiel.md
3. Die doppelt tragende Zeile ist spiel.md 1338 (Schadenstabelle,
`regulierung_last` in Spalte 2 und in Spalte 5). **Alle vier Teilaussagen
stimmen**, einschliesslich der Begruendung fuer die Abweichung beider Zaehlweisen.

**Kein stehengebliebener alter Stand.** Alle Vorkommen von 46 und 50 in der
Datei durchgesehen (Zeilen 161, 178, 212, 830, 831, 1105): jedes ist als
historisch gekennzeichnet ("bis dahin", "nannte", "stand hier"). Die uebrigen
Treffer sind andere Groessen (`aufschlag = 51` bp, `instrument_min = -50` bp,
"25 Runden"). Ausserhalb der Datei nennt kein lebendes Dokument des Vorhabens
eine Schluesselzahl: Die Treffer auf "50 Schluessel" liegen samtlich in alten
Arbeitspaketen, alten Pruefbefunden und Messbaeumen unter `befunde/`.

**Die beiden Riegel, die `parameter.toml` lesen, laufen gruen.**

- `belegstellen_riegel`: Selbsttest 57 Faelle wie erwartet; Bedingung 1 "5
  Zeilenverweise getroffen, davon 0 mit Dateinamen daneben"; Bedingung 2 "40
  Zitate der geprueften Form gefunden, 40 davon aufgeloest". Der neue Absatz
  dieses Pakets taucht dort als bewusst uebergangene Fundstelle auf
  (`parameter.toml:829`, "kein Dokumentname im Absatz", gesucht war
  `WIE DER PRUEFER ZAEHLT`) -- das ist der ausgeschriebene blinde Fleck des
  Riegels und kein Verstoss: Das Zitat zielt auf eine Ueberschrift **derselben**
  Datei (Zeile 147), und die gibt es.
- `bezeichner_riegel`: gruen, "Alle 1003 genannten Namen loesen auf". Seine
  Nebenbestandszahl "47 Schluessel der Kalibrierdatei" ist kein Widerspruch zu
  den 51 Blattschluesseln, sondern eine **Namensmenge**: 42 verschiedene
  Schluesselnamen -- die zwoelf Instrumentenschluessel tragen nur drei
  verschiedene Namen -- plus die fuenf Tabellennamen `instrument`, `leitzins`,
  `zoll`, `haushalt`, `regulierung`. Gerechnet, nicht fest eingetragen; der
  Riegel zieht also von selbst mit.

## Wonach gesucht und was nicht gefunden wurde

Damit diese Pruefung von einer nicht stattgefundenen unterscheidbar bleibt:

- **Einheiten und Basisjahre:** nichts zu pruefen. Die Datei traegt laut ihrem
  eigenen Kopf (Zeile 236) keinen Datenanker und keine Zahl aus einer externen
  Quelle; `0153` hat keinen Wert und keine Klassenangabe angefasst. Die
  Klassenangabe zu `regulierung_last` (Klasse 3, Basispunkte des BIP je
  Regulierungsstufe) stammt aus `0150` und ist dort geprueft.
- **Luecken:** keine Interpolation, keine Reihe, keine Zeitachse in dieser Datei.
- **Lizenz:** keine Quelle, keine Namensnennung -- die Datei sagt das selbst und
  verweist auf das Manifest des Jahrgangs (T23).
- **Reproduzierbarkeit:** zweimal dasselbe Ergebnis aus denselben Bytes, und die
  Selbstmessung ist ein **Fixpunkt**: Kein Zaehlausdruck der Datei trifft eine
  Kommentarzeile (`^`-Anker gegen `#` am Zeilenanfang), und `tomllib` sieht
  Kommentare ohnehin nicht. Genau die Falle, an der `0099` gescheitert ist, ist
  hier konstruktiv geschlossen -- und die Datei schreibt den Grund selbst hin
  (Zeilen 173-176).
- **Aufbau und Wortwahl:** kein Befund. Dass der Kommentarblock zu
  `regulierung_last` (ab Zeile 843) nicht wie alle anderen mit dem
  Schluesselnamen in Rueckwaerts-Anfuehrung beginnt, ist Stil, stammt aus `0150`
  und verletzt keine Vorgabe.

## Befund 1 -- die einzige Bilanzzahl der Datei ohne vorgeschriebenen Ausdruck

**Kein Ruecklaufgrund.** Die Abnahme verlangt fuer die Aufzaehlung unter BEFUNDE
Punkt 1 ausdruecklich nur, dass sie `regulierung_last` enthaelt und dass ihre
Zahl mit ihrer Laenge uebereinstimmt -- beides ist erfuellt. Ein Ruecklauf gegen
denselben Auftrag erzeugte keine bessere Datei.

**Die Beobachtung.** Dieses Paket existiert, weil drei Zahlen im Kopf beim Einzug
eines Schluessels stillschweigend falsch geworden sind. Fuer zwei davon schreibt
die Datei seit `0009` einen Ausdruck vor, mit dem man sie nachmisst; die
Gruppensumme ist seit `0153` an `tomllib` gebunden. **Fuer die Zahl 25 -- "25 der
51 Namen sind gebildet" -- gibt es keinen.** Sie ist die einzige Bilanzzahl der
Datei, die nur durch Abzaehlen einer Prosa-Aufzaehlung zu pruefen ist, und sie
ist genau die Sorte Zahl, die bei `0150` mitgewandert waere, wenn
`regulierung_last` eine `*`-Marke gebraucht haette.

**Warum das nicht trivial ist.** Der naheliegende Ausdruck ist falsch. Sucht man
nach dem Schluesselnamen in Rueckwaerts-Anfuehrung mit folgendem Stern, findet
man **27 Fundstellen mit 26 verschiedenen Namen** statt der 25 Marken. Der Grund
ist an beiden ueberzaehligen Stellen derselbe: Der Fettdruck von Markdown
benutzt dasselbe Zeichen wie die Marke dieser Datei, und wo ein fett gesetzter
Name auf eine Rueckwaerts-Anfuehrung endet, stehen beide Zeichen unmittelbar
nebeneinander.

- Zeile 850: `regulierung_last` im Zitat aus `spiel.md`, von `0150` fett
  gesetzt. **Diese Stelle verfaelscht die Zahl**, weil der Name sonst nirgends
  eine Marke traegt -- aus 25 wuerden 26.
- Zeile 382: `regulierung_start` in einer fett gesetzten Kopplungszeile. Sie
  hebt nur die Trefferzahl, nicht die Namenszahl, weil dieser Name in Zeile 527
  ohnehin eine echte Marke traegt. Diese Stelle ist alt und bekannt: Die
  Pruefungen zu `0042` und `0053` notieren am 2026-09-03 woertlich "26 Treffer
  auf 25 verschiedenen Namen" und nennen dieselbe Ursache (damals Zeile 366 und
  511). Neu ist allein Zeile 850 -- und sie ist die erste, die auch die
  Namenszahl verschiebt.

Der richtige Ausdruck muss also den Fall ausschliessen, in dem dem Stern ein
zweiter folgt, **und** ueber verschiedene Namen zaehlen statt ueber Treffer --
beides zusammen ergibt die 25. Wer die 25 kuenftig ohne diese zwei Zusaetze
nachmisst, bekommt eine falsche Zahl bestaetigt, in genau der Datei, die sich
sonst durchgehend selbst misst.

Vorschlag dazu abgelegt:
`aufgaben/0175-parametertoml-markenzahl-mit-ausdruck.md` (`status: vorschlag`).

## Kein zweiter Vorschlag

Zwei Stellen habe ich geprueft und bewusst **nicht** zu einem Befund gemacht:

1. Der Zeilenverweis "dort Zeile 2165, abgerufen 2026-09-06" (Zeile 854) zeigt
   in `technik.md`. Er stammt aus `0150`, steht in meinem Befund zu jenem Paket
   und ist dort gemeldet; er gehoert nicht zweimal in den Rueckstand.
2. Der Anker `^[a-z_0-9]* *=` laesst den Namensteil formal auch leer und traefe
   eine Zeile, die mit `=` beginnt. In TOML gibt es eine solche Zeile nicht, und
   die Datei enthaelt keine; die gemessene Partition ist exakt. Ein Paket dafuer
   waere Aufwand ohne Fehler dahinter.
