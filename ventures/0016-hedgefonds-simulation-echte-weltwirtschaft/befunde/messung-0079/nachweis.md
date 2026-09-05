# Messung zu Paket 0079 -- die Ueberschrift ohne Anfuehrung

Datum: 2026-09-05, Ruecklauf 1, **Abschnitt "Die zwei Bedingungen der neuen Abnahme"
neu gemessen in Ruecklauf 2**. Rolle: testentwickler. Geaenderte Datei: genau eine,
`werkzeuge/belegstellen/belegstellen_riegel.cpp` -- die einzige aus der `dateien`-Liste.
**In Ruecklauf 2 ist an ihr nichts geaendert worden**; berichtigt ist allein diese
Messschrift.

**Diese Datei ersetzt die Fassung vom selben Tag vollstaendig.** Sie war an einer Stelle
falsch, und der Projektmanager hat sie zu Recht beanstandet: Der abgedruckte Testlauf
nannte 56 uebergangene Fundstellen, der ausgelieferte Stand meldete 58. Gemessen worden
war, bevor der Kopfkommentar fertig war -- der Riegel liest seinen eigenen Quelltext mit,
und zwei neue Zeilen darin sind zwei neue Fundstellen. **Die Regel fuer diese Datei
lautet seither: nach der letzten Zeile des Kopfkommentars noch einmal messen.** Genau so
ist der Lauf unten entstanden.

**Und ein zweites Mal war sie falsch, an derselben Sorte Zahl.** Der Vergleich A gegen C
weiter unten nannte 46 uebergangene Fundstellen, 37 neue, 36 Gliederungsziffern -- der
abgedruckte Lauf im selben Dokument nannte 47. Der Pruefer hat den Widerspruch gefunden
(`befunde/pruefung-0079-belegstellenriegel-zitat-ohne-anfuehrung-runde2-2026-09-05.md`).
Die drei Zahlen sind unten berichtigt, der Zaehlfehler ist reproduziert und benannt, und
der Vergleich ist neu gefahren -- an **zwei** Baeumen, damit er nicht wieder an einem
einzelnen haengt.

## Die Bezugsstaende, damit jede Zahl eine Herkunft hat

Alle Laeufe unten sind **hintereinander weg am selben Baum** gefahren, dem
Arbeitsbereich vom 2026-09-05 nach Commit `609c538`. Das ist keine Umstaendlichkeit: Der
Korpus dieses Vorhabens driftet waehrend eines Laufs, und eine Zahl gegen eine frueher
notierte gerechnet ist wertlos.

| Marke | Stand des Riegels | wozu |
|---|---|---|
| **A** | `489aafb` -- der Stand nach 0067 und 0073 | der Bezugsstand des Pakets |
| **B** | `fb586db` -- die erste Fassung dieses Pakets | nur zur Geschichte; sie traegt 0083 und 0086 noch nicht |
| **C** | der Arbeitsbereich, ausgeliefert als `f8c8598` und seither unveraendert | **der ausgelieferte Stand** |
| **M1** | C, an der Aufrufstelle ohne die Satzgrenze | die saubere Gegenprobe zu C |

**B taugt nicht als Vergleich fuer den Eingriff dieses Ruecklaufs**, und das gehoert
gesagt, statt es unter den Tisch fallen zu lassen: Zwischen B und C liegen die Pakete
0083 und 0086, die denselben Riegel anfassen. Wer C gegen B rechnet, misst drei Pakete
und nennt es eines. Die Gegenprobe zur Satzgrenze ist deshalb **M1** -- derselbe Stand,
dieselbe Zeile, nur ohne die Schranke.

**Der Vergleich A gegen C ist in Ruecklauf 2 an zwei ausgepackten Baeumen neu gefahren**,
nicht am Arbeitsbereich. Der Grund steht in der offenen Faehrte, an der dieses Paket
schon einmal gescheitert ist: Der Arbeitsbereich driftet waehrend des eigenen Laufs, und
`bau/` liegt nicht in git. Ein ausgepackter Baum ist eine Zahl, die der Pruefer
nachfahren kann.

| Marke | Baum | wie hergestellt |
|---|---|---|
| **Baum 1** | `f8c8598` -- der Baum des Baucommits von Ruecklauf 1 | `git archive f8c8598 ventures/0016-... specs/0016-...` |
| **Baum 2** | `fabbf2f` -- `HEAD` beim Beginn dieses Laufs | `git archive fabbf2f ventures/0016-... specs/0016-...` |

Beide Programme laufen an beiden Baeumen. **A liegt dabei ausserhalb des gemessenen
Baums** und bekommt Wurzel und Vorgabenwurzel als die zwei Argumente, die `CMakeLists.txt`
dem Stand C setzt. Das ist keine Bequemlichkeit, sondern notwendig: Der Riegel liest
**seinen eigenen Quelltext** als Bauquelle mit: Legte man A neben C in den Baum, waere der
Baum nicht mehr derselbe, und der Vergleich maesse sich selbst.

## Der ausgelieferte Lauf, im Wortlaut

Gebaut mit dem Alleinbauweg (`cmake -S werkzeuge/belegstellen -B <bau>`), also mit
`werkzeugkette.cmake` und damit mit `-std=c++20 -fwrapv -Werror` und
`-fsanitize=undefined,address`. Kein Gleitkommatyp im Quelltext (`float`, `double`,
`long double`: null Treffer).

```
belegstellen_riegel, Selbsttest: 8 Faelle zur Suche nach links, 9 zur Form
ohne Anfuehrung, 8 zur Ortsfrage, 8 zum Wortabstand samt Suche nach rechts
und 5 zur Satzgrenze nach links, alle wie erwartet.
belegstellen_riegel, Bedingung 1 (Zeilennummer in eine fremde Datei): 42 Bauquellen
gelesen, 5 Zeilenverweise getroffen, davon 0 mit Dateinamen daneben.
belegstellen_riegel, Bedingung 2 (Abschnittszitat): 42 Bauquellen und 11
Datendokumente gelesen, 166 Dateien im Zielbestand, 380 Namen in ungelesenen
Ordnern; 35 Zitate der geprueften Form gefunden, 35 davon aufgeloest (Untergrenze
16), 47 Fundstellen uebergangen.
Davon ohne Anfuehrung: 14 Zitate; weitere 54 Fundstellen ohne Anfuehrung nennen in
ihrem Absatz keinen Dokumentnamen und sind deshalb keine Zitate.

[98 Zeilen Aufzaehlung der uebergangenen Fundstellen]

Kein Verweis zeigt mit einer Zeilennummer in eine fremde Datei, und jedes der
35 Abschnittszitate findet seine Zieldatei und darin seine Ueberschrift.

100% tests passed, 0 tests failed out of 1
```

**Eine der Zahlen ist nicht stabil, und das ist keine Schwaeche des Laufs, sondern eine
Eigenschaft des Riegels:** *380 Namen in ungelesenen Ordnern* zaehlt, was zur Laufzeit
unter `bau/` und `befunde/` liegt. Ein frisch geraeumter Baum nennt dort weniger, ein
Baum mit Messdateien mehr. Die Zahl geht in keine der drei gemessenen Groessen ein -- sie
entscheidet nur, ob ein Ziel als *ungelesen* oder als *tot* gilt, und keine der
Fundstellen unten haengt daran.

Gemessen ist das und nicht behauptet: Waehrend dieses Laufs sind zwei fremde Commits
(`2de4de7`, `5133001`) in den Baum gekommen. **Alle drei gemessenen Zahlen und alle
Mutantenurteile unten sind danach unveraendert** -- 35 Zitate, 35 aufgeloest, 47
uebergangen, Rueckgabewert 0. Bewegt hat sich allein diese eine, von 379 auf 380.

**Nachgefahren in Ruecklauf 2**, weil ein Lauf, den man nicht wiederholen kann, kein
Nachweis ist. An **Baum 1** meldet der ausgelieferte Stand zeichengleich dieselben Zahlen
wie oben: 42 Bauquellen, 11 Datendokumente, 166 Dateien im Zielbestand, 35 Zitate, 35
aufgeloest, **47 uebergangen**, Rueckgabewert 0. Nur *Namen in ungelesenen Ordnern* steht
bei 286 statt 380 -- `bau/` liegt nicht in git und fehlt im ausgepackten Baum. Dass der
Lauf trotzdem gruen bleibt und dieselben 47 nennt, ist der Beleg dafuer, dass keine
Fundstelle an dieser Zahl haengt. An **Baum 2** ist der Korpus weitergedriftet (44
Bauquellen, 13 Datendokumente, 184 im Zielbestand, 303 Namen): 36 Zitate, 36 aufgeloest,
**wieder 47 uebergangen**, Rueckgabewert 0. Der Riegel bleibt also auch auf dem heute
geltenden Korpus gruen.

## Der Befund dieses Ruecklaufs: der Riegel war rot, und zwar an seiner eigenen Lockerung

Beim ersten Messen dieses Laufs meldete der ausgelieferte Stand **einen Befund**:

```
1 Abschnittszitat(e) finden ihre Ueberschrift nicht:

  zitierend: rueckstand.md:131
  nachgeschlagen in: werkzeugkette.cmake
  gesuchte Ueberschrift: Rechtfertigung und sechs zusaetzliche Baulaeufe gekostet
                         und nichts gesichert
```

Der Satz dort lautet sinngemaess, die Zahl habe *einen Absatz Rechtfertigung und sechs
zusaetzliche Baulaeufe gekostet*. Das Schluesselwort steht da, der Name dahinter beginnt
gross -- im Deutschen tut das jedes Hauptwort --, und der naechstgelegene Dokumentname im
Absatz stand **zwei Saetze weiter oben** und handelte von etwas anderem. Der Riegel schlug
einen halben Nebensatz als Ueberschrift nach.

**Das ist ein Fehler dieses Pakets und nicht des Textes.** `rueckstand.md` steht in keiner
Dateiliste, und wer die Datei umschreibt, damit der Riegel gruen wird, hat den Riegel
geprueft und nicht die Datei -- derselbe Satz, mit dem der Rumpf dieses Pakets es fuer
`reihen.toml` schon ablehnt. Die drei im Kopf ausgeschriebenen Grenzen der Form ohne
Anfuehrung genuegen nicht; die Kleinschreibungsgrenze traegt im Deutschen weniger, als sie
zu tragen scheint.

### Die Regel dagegen ist keine neue

**Ein Verweis und sein Ziel stehen im selben Satz.** Bedingung 1 sucht so nach links
(`satzanfang_vor`, im Kopf begruendet), Paket 0086 sucht so nach rechts
(`satzende_nach`). Fuer die Form **ohne** Anfuehrung gilt sie jetzt auch nach links. Der
Grund steht im Kopf schon seit der ersten Fassung und wird nur zu Ende gedacht: Die
Anfuehrung ist die Ankuendigung "hier wird zitiert"; fehlt sie, ist der Dokumentname die
einzige, die bleibt -- und eine Ankuendigung zwei Saetze weiter oben kuendigt nichts an.

Fuer die Form **mit** Anfuehrung aendert sich nichts. Sie sucht weiter ueber den ganzen
Absatz, weil der von Paket 0067 gemessene Fall (`schranken_probe.cpp`, Dateiname vier
Zeilen ueber der Ueberschrift) es verlangt.

### Was die Schranke kostet -- C gegen M1, derselbe Stand, derselbe Baum

|  | M1, ohne Schranke | C, mit Schranke |
|---|---|---|
| Zitate | 36 | **35** |
| davon aufgeloest | 35 | **35** |
| uebergangene Fundstellen | 56 | **47** |
| Fundstellen ohne Dokumentnamen | 44 | **54** |
| Befunde | **1** (falsch) | **0** |
| Rueckgabewert | 1 | **0** |

**Kein einziges aufgeloestes Zitat geht verloren** -- 35 bleiben 35. Was faellt, ist der
falsche Befund und neun uebergangene Fundstellen. Alle neun sind Gliederungsziffern und
trugen ohnehin keinen Wortlaut; sie verschwinden nicht, sondern wechseln die Zahl:
44 + 9 + 1 = 54. Es sind acht Stellen in `daten/einheitenbefund-pwt-baci.md` (Zeilen 77,
105, 127, 306, 315, 366, 371, 374) und eine in `daten/reihen.toml` (Zeile 611); an allen
neun stand der Dokumentname im Satz davor, die Bindung war also von Anfang an die
falsche.

**Der Riegel ist dafuer nicht abgeschwaecht worden.** Verengt wurde allein die Lockerung,
die dieses Paket selbst eingefuehrt hat, und zwar mit der Regel, die im selben Programm
schon zweimal steht. Die Richtung des Fehlers ist die gewollte und dieselbe wie bei
`satzanfang_vor`: Zu streng laesst eine Stelle als "ohne Ziel" durch, zu nachsichtig
bindet sie an die falsche Datei.

### Drei Rotnachweise fuer die Schranke

Jeder Mutant ist am ausgelieferten Stand gebaut, jeweils eine Aenderung, danach
zurueckgestellt.

| Mutant | was er abschaltet | Ergebnis |
|---|---|---|
| **M1** | die Schranke an der Aufrufstelle | Selbsttest gruen, **Bestand rot**: `rueckstand.md:131`, Code 1 |
| **M2** | `suchuntergrenze` gibt immer 0 | **`SATZFAELLE` 1 und 4 rot**, Code 2 |
| **M3** | `suchuntergrenze` gibt immer den Satzanfang | **`SATZFAELLE` 3 rot**, Code 2 |

Im Wortlaut:

```
M2: Selbsttest Satzgrenze 1: gebunden erwartet war kein Dateiname,
                             gefunden wurde werkzeugkette.cmake.
    Selbsttest Satzgrenze 4: gebunden erwartet war kein Dateiname,
                             gefunden wurde spiel.md.
M3: Selbsttest Satzgrenze 3: gebunden erwartet war schranken_probe.cpp,
                             gefunden wurde keiner.
```

**M1 ist der wichtigste der drei, weil er zeigt, was die Tabelle *nicht* deckt.**
`SATZFAELLE` misst `suchuntergrenze`; wer an der Aufrufstelle die Null von Hand einsetzt,
laesst den Selbsttest gruen. Gefangen wird das vom Bestand, und heute faengt er es
wirklich. Beides zusammen deckt die Regel, keines allein -- und das steht so auch im Kopf
des Riegels, damit niemand die Tabelle fuer mehr haelt, als sie ist.

## Die vier Stellen aus Paket 0047, einzeln abgehakt

Genannt ueber Feld und Wortlaut; die Zeilennummern sind Messwerte vom 2026-09-05 und
stehen nur zur Auffindbarkeit dabei.

| Stelle | zitierter Name | Urteil des Riegels |
|---|---|---|
| `reihen.toml`, Feld `beleg` unter `zaehlung.lizenz` (Z. 259) | `5` | **uebergangen**, *Gliederungsziffer statt Ueberschrift: 5*, namentlich genannt |
| `reihen.toml`, Feld `beleg` unter den Reihen Nr. 3 und Nr. 4 (Z. 302, 309) | `3` | **uebergangen**, *Gliederungsziffer statt Ueberschrift: 3*, namentlich genannt |
| `reihen.toml`, Feld `schnitt_2_offen` (Z. 1752) | `Reihe 1` | nachgeschlagen in `daten/lizenzbefund-reihen.md`, **aufgeloest** |
| `reihen.toml`, Feld `schnitt_2_offen` (Z. 1752) | `2b und 2c` | nachgeschlagen in `daten/lizenzbefund-reihen.md`, **aufgeloest** |

Die zwei Nummern stehen im Lauf oben namentlich in der Aufzaehlung der uebergangenen
Fundstellen, die zwei Namen stehen dort **nicht** -- sie sind Zitate und aufgeloest.

**Rotnachweis fuer die zweite Gruppe.** Gefuehrt ueber die eigene Datei und ohne eine
fremde anzufassen: `lies_ueberschriften` bekam einen Vorsatz vor jede Ueberschrift, die
sie aus `lizenzbefund-reihen.md` liest -- das ist genau der Fall "jemand hat die
Ueberschrift umbenannt". Der Lauf meldet dann:

```
  zitierend: daten/reihen.toml:1752
  nachgeschlagen in: daten/lizenzbefund-reihen.md
  gesuchte Ueberschrift: Reihe 1

  zitierend: daten/reihen.toml:1752
  nachgeschlagen in: daten/lizenzbefund-reihen.md
  gesuchte Ueberschrift: 2b und 2c
```

Rueckgabewert 1. Beide werden also wirklich nachgeschlagen, und beide werden rot, wenn
ihr Ziel umbenannt wird -- die zweite auch dann, obwohl ihr Name mit einer Ziffer beginnt.
Nach dem Zuruecknehmen: wieder gruen, dieselben Zahlen wie oben.

Dass die Mutation **auf eine Datei eingegrenzt** ist, hat einen gemessenen Grund: Wer
jede Ueberschrift jeder Zieldatei umbenennt, faellt vorher an der Untergrenze aus Paket
0083 (`0 aufgeloeste Zitate, Untergrenze 16`, Code 2) und liest die Befundliste nie.

## Die zwei Bedingungen der neuen Abnahme, gemessen

Beide am selben Baum, A gegen C -- **in Ruecklauf 2 neu gefahren, und zwar an beiden
Baeumen.** Das Ergebnis ist an beiden dasselbe, Eintrag fuer Eintrag:

| Baum | A | C | verschwunden | neu | davon *Gliederungsziffer* | davon *Zieldatei fuehrt keine Ueberschrift* |
|---|---|---|---|---|---|---|
| **1** (`f8c8598`) | 9 | **47** | **0** | **38** | **37** | **1** |
| **2** (`fabbf2f`) | 9 | **47** | **0** | **38** | **37** | **1** |

Dass die Drift zwischen den beiden Baeumen die drei Zahlen des Vergleichs *nicht*
bewegt, obwohl sie die Zitatzahl von 35 auf 36 hebt, ist der Grund, beide zu fahren:
Die Bedingung redet ueber den Unterschied zweier Programme, nicht ueber den Korpus.

Verglichen wird ueber `datei:zeile` als **Mehrfachmenge**, nicht als Menge. Warum das
kein Formalismus ist, steht unter b).

### a) Keine uebergangene Fundstelle des Standes von 0067 verschwindet

Der Stand A meldet **9** uebergangene Fundstellen. Alle neun stehen auch in C:

| Fundstelle | Grund in A | in C |
|---|---|---|
| `daten/einheitenbefund-pwt-baci.md:20` | kein Dokumentname im Absatz | ja |
| `daten/lizenzbefund-reihen.md:164` | kein Dokumentname im Absatz | ja |
| `daten/lizenzbefund-reihen.md:202` | kein Dokumentname im Absatz | ja |
| `daten/lizenzbefund-reihen.md:364` | naechstes Ziel ist eine Netzadresse | ja |
| `kern/CMakeLists.txt:3` | kein Dokumentname im Absatz | ja |
| `parameter.toml:11` | Ziel ausserhalb des Bestands | ja |
| `pruefstand/test/vorrat_kernanker_probe.cpp:3` | kein Dokumentname im Absatz | ja |
| `werkzeuge/belegstellen/belegstellen_riegel.cpp:262` | kein Dokumentname im Absatz | ja |
| `werkzeuge/belegstellen/belegstellen_riegel.cpp:265` | kein Dokumentname im Absatz | ja |

**Verschwunden: null.** Der Grund ist derselbe, den der Pruefer schon genannt hat, und er
ist hier nachgerechnet: Keine der neun traegt die Form ohne Anfuehrung, dieses Paket kann
sie also gar nicht beruehren. Zwei von ihnen (`belegstellen_riegel.cpp:262` und `:265`)
sind Zeilen aus dem Kopfkommentar dieses Pakets und in A nur deshalb schon da, weil A auf
**dem heutigen Baum** gefahren ist -- der Stand von 0067 selbst kannte sie nicht. Das ist
kein Fehler der Messung, sondern ihr Sinn: Verglichen werden zwei Programme an einem
Baum, nicht zwei Baeume.

### b) Jede neu hinzugekommene traegt einen Grund dieses Pakets

C meldet **46** uebergangene Fundstellen, davon **37 neu** gegenueber A:

| Anzahl | Grund | eingefuehrt von |
|---|---|---|
| 36 | *Gliederungsziffer statt Ueberschrift* | Paket 0079 (`namensart`, `Namensart::Ziffer`) |
| 1 | *Zieldatei fuehrt keine Ueberschrift* | Paket 0079 (`namensart`, `Namensart::Ohne_Gliederung`) |

Andere Gruende kommen unter den neuen nicht vor. Beide sind Ergebnisse derselben
Funktion, die dieses Paket eingefuehrt hat; keiner von ihnen existiert im Stand A.

## Was der Pruefer schon bestaetigt hat und hier nur wiederholt wird

Aus `befunde/pruefung-0079-...-2026-09-05.md`: die vier Stellen aus 0047 gehen aus wie
verlangt, beide Ueberschriften werden ueber eine Korpuskopie rot, zehn Mutanten sterben
an je einem eigenen Fall, und keines der 24 Zitate der alten Form ist verloren. Die
Zahlen oben sind neu gefahren; das Urteil ist dasselbe.

## Was in diesem Lauf offen bleibt

* **Der Preis der Schranke ist eine Entscheidung und keine Rechnung.** Steht der
  Dokumentname im Satz **vor** dem Schluesselwort, bleibt die Fundstelle ohne Ziel --
  gezaehlt, aber nicht bewertet. Auf dem heutigen Korpus kostet das neun Gliederungsziffern
  und kein Zitat. Waechst dort einmal ein echtes Zitat dieser Bauart, faengt der Riegel es
  nicht. Fall 4 in `SATZFAELLE` haelt genau diesen Preis fest, damit er nicht still ist.
* **Die Pakete 0105 und 0106** sind vom Projektmanager als eigene Pakete angenommen und in
  diesem Lauf nicht angefasst.
* **Eine Zahl im Kopfkommentar ist berichtigt worden:** "die groesste der *fuenf* Gruppen"
  hiess seit Paket 0083 richtig "der *sechs* Gruppen". Es sind sechs Sorten, und die Liste
  drei Absaetze darueber nennt sie auch so.
