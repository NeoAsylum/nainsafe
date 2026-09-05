# Nachweis zu Paket 0067 -- Belegstellenriegel, Abschnittszitate

Testentwickler, 2026-09-04. Gemessen an
`werkzeuge/belegstellen/belegstellen_riegel.cpp` in der Fassung dieses Laufs.

**Nachweisort.** Die Staffelung des Arbeitspakets ($TMPDIR, sonst `befunde/`) betrifft
einen Sabotagebaum ausserhalb des Repos. Ein solcher war hier nicht noetig: Der
Rotnachweis laeuft ueber zwei Bearbeitungen der **eigenen** Datei, beide zurueckgenommen,
und ist damit ohne fremdes Gebiet und ohne Kopie zu fuehren. Diese Datei haelt nur das
Protokoll.

## Bedingung 1 -- der Test laeuft und heisst weiter so

Ein Test, nicht zwei. Beide Bedingungen laufen in `ctest -R belegstellen_riegel`; der
Name ist unveraendert, damit keine frueheren Messungen unvergleichbar werden. Beide
Bauwege gemessen:

```
$ cmake -S <werkzeuge/belegstellen> -B <.../bau>
-- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
-- Configuring done (0.0s)
$ cmake --build <.../bau>
[100%] Built target belegstellen_riegel
$ ctest --test-dir <.../bau>
1/1 Test #1: belegstellen_riegel ..............   Passed    0.33 sec
100% tests passed, 0 tests failed out of 1
```

```
$ cmake -S <ventures/0016-...> -B <ventures/0016-.../bau>
-- Warnsatz-Schlussriegel: 16 uebersetzende Ziele geprueft, alle mit Warnsatz und ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in ihrer Schnittstelle.
$ ctest --test-dir <ventures/0016-.../bau>
12/12 Test #12: belegstellen_riegel ..............   Passed    0.33 sec
100% tests passed, 0 tests failed out of 12
```

`CMakeLists.txt` ist **nicht** angefasst worden -- sie gehoert Paket 0059 und steht nicht
in der Dateiliste von 0067. Die Wurzel der Vorgaben, die Bedingung 2 braucht, kommt
deshalb nicht als zweites Argument, sondern wird im Programm aus dem ersten abgeleitet
(Geschwisterverzeichnis `specs` mit demselben Vorhabensnamen). Ein zweites Argument wird
zusaetzlich angenommen, falls es spaeter jemand setzt. Kein Pfadbestandteil steht fest im
Programm; fehlt das abgeleitete Verzeichnis, bricht der Riegel mit Code 2 ab, statt jedes
Zitat in die Vorgaben als "uebergangen" durchzuwinken.

## Bedingung 2 -- die beiden Zahlen, auf dem heutigen Stand

```
belegstellen_riegel, Bedingung 1 (Zeilennummer in eine fremde Datei): 37 Bauquellen gelesen, 5 Zeilenverweise getroffen, davon 0 mit Dateinamen daneben.
belegstellen_riegel, Bedingung 2 (Abschnittszitat): 37 Bauquellen und 11 Datendokumente gelesen, 129 Dateien im Zielbestand; 21 Zitate der geprueften Form gefunden, 21 davon aufgeloest, 5 Fundstellen uebergangen.
```

Die Zahl des Zielbestands steht hier mit 129, weil der Lauf vor dem Vorschlag 0079
gemacht wurde; mit ihm sind es 130. Der Bestand zaehlt Dateien, nicht Zitate -- an den
beiden Zahlen darunter aendert er nichts, und beide Aufrufwege (abgeleitete und
uebergebene Vorgabenwurzel) liefern denselben Bestand.

**21 gefunden, 21 aufgeloest.** Die Zahlen sind gleich, also gruen. Waeren sie ungleich,
waere der Lauf rot -- das ist keine Zusicherung nebenbei, sondern die Verzweigung im
Programm: Jedes Zitat, dessen Ziel im Bestand steht, wird nachgeschlagen, und was seine
Ueberschrift nicht findet, ist ein Befund.

Die erste Zahl ist nicht null, und das war die eigentliche Gefahr: Ein Muster, das nichts
mehr trifft, meldete sonst gruen. Der Riegel bricht in dem Fall jetzt mit Code 2 ab.

**Die fuenf uebergangenen Fundstellen, einzeln.** Sie sind der ausgeschriebene blinde
Fleck: Sie tragen ihr Ziel nicht bei sich und werden deshalb nicht bewertet -- aber sie
werden genannt, sonst sieht ein Riegel, der etwas still uebergeht, aus wie einer, der
prueft.

```
  parameter.toml:11  (Ziel ausserhalb des Bestands: befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md)
      gesucht war: WIE DER PRUEFER ZAEHLT
  daten/lizenzbefund-reihen.md:164  (kein Dokumentname im Absatz)
      gesucht war: Was Reihe 2 als Ganzes kostet
  daten/lizenzbefund-reihen.md:202  (kein Dokumentname im Absatz)
      gesucht war: Was Reihe 2 als Ganzes kostet
  daten/lizenzbefund-reihen.md:364  (naechstes Ziel ist eine Netzadresse: //raw.githubusercontent.com/etalab/licence-ouverte/master/LO.md)
      gesucht war: Droits de propriété intellectuelle
  kern/CMakeLists.txt:3  (kein Dokumentname im Absatz)
      gesucht war: [dependencies]
```

Nachgeschlagen sind alle fuenf, und keine ist ein Befund: Die erste ist ein Verweis auf
einen Abschnitt **derselben** Datei (`parameter.toml` traegt die Ueberschrift; der
naechstgelegene Dokumentname im Absatz ist ein Pruefbericht unter `befunde/`, und `befunde/`
wird nicht gelesen). Die zweite und dritte verweisen ebenfalls auf einen Abschnitt
derselben Datei. Die vierte zitiert eine franzoesische Lizenzseite, deren Netzadresse eine
Zeile darueber steht. Die fuenfte ist gar kein Abschnittsverweis, sondern eine
Rust-Manifestgruppe im Kommentar.

**Kein toter Verweis gefunden.** Das Arbeitspaket sagt, ein gefundener waere zu ersetzen
und nicht auszunehmen; es gab keinen zu ersetzen.

## Bedingung 3 -- der Rotnachweis

Verdreht wurde **das Zitat**, nicht die Zieldatei, und zwar das Zitat im Kopfkommentar des
Riegels selbst: `Die Schleife` -> `Die Schleifen`. Damit bleibt der Nachweis vollstaendig
in der einen Datei, die dieses Paket besitzt, und beruehrt kein fremdes Gebiet.

Gruen -> rot -> gruen, jeweils mit `cmake --build` dazwischen.

**Rot, im Wortlaut:**

```
$ ctest --test-dir <.../bau> --output-on-failure
1/1 Test #1: belegstellen_riegel ..............***Failed    0.34 sec

1 Abschnittszitat(e) finden ihre Ueberschrift nicht:

  zitierend: werkzeuge/belegstellen/belegstellen_riegel.cpp:32
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Die Schleifen

Entweder ist die Ueberschrift dort umbenannt worden -- dann wird das Zitat
nachgezogen --, oder sie stand nie so da. Beides wird berichtigt und nicht
ausgenommen. Die Schreibweise ist bis auf Umlautumschrift, Auszeichnung und
Leerraum wortgleich zu nehmen; Gross- und Kleinschreibung zaehlt.
belegstellen_riegel, Bedingung 2 (Abschnittszitat): 37 Bauquellen und 11 Datendokumente gelesen, 129 Dateien im Zielbestand; 21 Zitate der geprueften Form gefunden, 20 davon aufgeloest, 5 Fundstellen uebergangen.

0% tests passed, 1 tests failed out of 1
```

Die Meldung nennt die drei Angaben, die das Arbeitspaket verlangt: die zitierende Datei
mit Zeile, die Zieldatei und die gesuchte Ueberschrift. Und die Zaehlung zeigt den
Unterschied mit -- 21 gefunden, 20 aufgeloest.

**Zurueckgenommen und wieder gruen:**

```
$ ctest --test-dir <.../bau>
1/1 Test #1: belegstellen_riegel ..............   Passed    0.33 sec
100% tests passed, 0 tests failed out of 1
```

## Bedingung 4 -- die sechs Pakete, einzeln

Ermittelt ist die Belegstelle jedes Pakets aus dem Aenderungsverlauf seiner eigenen Datei
(`git log -S` auf den jeweiligen Wortlaut), nicht aus dem heutigen Text geraten. Genannt
wird sie hier ueber den Wortlaut, nicht ueber eine Zeilennummer.

| Paket | Datei | Form der Belegstelle | Ergebnis |
|---|---|---|---|
| 0034 | `daten/adressen.md` | drei Stellen, alle nach `technik.md`: zweimal Schluesselwort *Absatz* mit unmittelbar folgender Anfuehrung, einmal Schluesselwort mit fuenf Woertern Abstand und dem Dateinamen **rechts** vom Zitat | **zwei gefangen, eine nicht** -- siehe *Ruecklauf 1* unten. Die Zeile lautete bis zum Ruecklauf falsch (Kopffeld `quellen`, das aus Paket 0004 stammt) |
| 0035 | `parameter.toml` | zwei Zitate in der Herkunftsbegruendung zu `hebelaufschlag`; beim zweiten steht der Dateiname eine Zeile hoeher | **gefangen**, beide |
| 0044 | `kern/test/schranken_probe.cpp` | Ueberschrift in Akzenten, Dateiname **vier Zeilen** darueber | **gefangen** |
| 0047 | `daten/reihen.toml` | Ueberschrift **ohne Anfuehrung**, viermal | **nicht gefangen** |
| 0050 | `pruefstand/test/vorrat_verfahren_probe.cpp` | fuenf Zitate derselben Ueberschrift, eines davon mit maskierten Anfuehrungszeichen in einer Zeichenkette | **gefangen**, alle fuenf |
| 0057 | `daten/reihen.toml`, `daten/einheitenbefund-pwt-baci.md` | dreimal die geklammerte Form, die dieses Paket eingefuehrt hat; einmal gemischte Anfuehrung (tief geoeffnet, gerade geschlossen) | **gefangen**, alle vier |

### 0044 -- der Fall aus dem Nachtrag des Projektmanagers

Der Nachtrag stellt fest, dass der Riegel je Zeile saehe und 0044 deshalb uebergehen
wuerde. Er tut es nicht mehr: Bedingung 2 liest **je Absatz**. Ein Absatz ist ein
zusammenhaengender Block gleichartiger Zeilen -- derselbe Kommentarkopf, keine Leerzeile
dazwischen -- zu einer Zeichenkette zusammengezogen, mit einer Zuordnung von jedem Zeichen
zu seiner Quellzeile, damit die Meldung trotzdem eine Zeile nennt.

Damit findet der Riegel `parameter.toml` vier Zeilen ueber der Ueberschrift und schlaegt
dort `GRUPPE A -- die elf Zeilen der Tabelle in T27` nach. Gemessen, nicht behauptet: Die
Belegstelle steht in der Liste der 21 aufgeloesten.

Die Absatzlesung ist auch der Grund, warum 0035 vollstaendig faellt: Sein zweites Zitat
traegt seinen Dateinamen ebenfalls eine Zeile hoeher.

### 0047 -- die ausgewiesene Luecke

`daten/reihen.toml` traegt seit Paket 0047 viermal die Form `<datei>, Abschnitt <Name>`
**ohne jede Anfuehrung**:

```
daten/lizenzbefund-reihen.md, Abschnitt 5
daten/lizenzbefund-reihen.md, Abschnitt 3
lizenzbefund-reihen.md, Abschnitt Reihe 1
lizenzbefund-reihen.md, Abschnitt 2b und 2c
```

Der Riegel faengt sie nicht, und **sie bleibt ungeschuetzt**. Das ist keine Nachlaessigkeit,
sondern die Grenze, hinter der eine eigene Entscheidung mit eigenem Nachweis anfaengt:
Ohne Anfuehrung ist nicht bestimmt, wo der Name aufhoert. Liest man bis zum naechsten
Satzzeichen, sind eine Nummer ("5", "3") und eine Ueberschrift ("Reihe 1") dieselbe
Gestalt, und der Riegel muesste raten, welche von beiden gemeint ist. Raet er zu scharf,
wird er rot, wo nichts kaputt ist; raet er zu vorsichtig, prueft er wieder nichts.

Das ist als Paket 0079 vorgeschlagen (`aufgaben/0079-belegstellenriegel-zitat-ohne-anfuehrung.md`,
`status: vorschlag`).

**Warum die Luecke keinen Zwischenweg bekommen hat.** Naheliegend waere gewesen, die vier
Stellen in `reihen.toml` in Anfuehrung zu setzen. Das ist fremdes Gebiet -- die Datei steht
nicht in der Dateiliste dieses Pakets --, und es waere auch der falsche Weg: Der Riegel
soll die Form fangen, die dasteht, nicht die Form vorschreiben, die er schon kann.

## Zwei Entscheidungen, die das Arbeitspaket offen gelassen hat

**Der Umfang des Quellbaums.** Bedingung 2 liest die Bauquellen **und** die
Datendokumente (`parameter.toml`, `daten/**.md`, `daten/**.toml`) -- vier der sechs Pakete
haben ihre Ueberschriften dort hinterlassen. Der Ausschluss dieser Dateien bei Bedingung 1
bleibt unveraendert und gilt weiter; er war mit laufender Aufraeumarbeit begruendet, und
Bedingung 2 verlangt keine, sondern nur ein Nachschlagen. Ausgenommen bleiben `befunde/`
und `aufgaben/` als **zitierende** Dateien -- beide beschreiben einen Stand zu einem
Zeitpunkt, und sie nachzufuehren faelschte sie. Die Vorgaben unter `specs/` werden
**gelesen, aber nur nachgeschlagen**: Ein Befund darin liesse sich in diesem Paket nicht
beheben, denn das Aufraeumen in `specs/` ist ihm ausdruecklich verboten, und ein Riegel,
dessen Rot niemand beheben darf, ist keiner.

**Wie streng "genau diese Ueberschrift" gemeint ist.** Ausgeschrieben im Kopfkommentar.
Umlaute werden umschrieben, Auszeichnung und Leerraum fallen weg, Gross- und
Kleinschreibung **nicht**. Die Umlautumschrift ist keine Nachsicht, sondern die Lage, und
sie ist an einem echten Fall belegt: `parameter.toml` zitiert aus `spiel.md` die
Ueberschrift zur Groesse des Zustands. Der Quelltext dieses Vorhabens ist umlautfrei, die
Vorgabe nicht -- das Ziel traegt dort ein `ö` und ein `ß`, das Zitat schreibt sie um. Ohne
die Umschrift waere dieses Zitat der erste rote Befund gewesen, und zwar zu Unrecht.

Als Ueberschriftszeile zaehlt auch ein **fett ausgezeichneter Vorspann**, nicht nur eine
Rautenzeile. Auch das ist an echten Faellen belegt und keine Bequemlichkeit: Die drei
Zitate aus `reihen.toml` zeigen auf solche Vorspaenne (`**Zur Einheit:**` in
`deckungsbefund-1997.md`, `**Was dafuer zu tun ist -- Namensnennung, konkret.**` in
`specs/.../daten.md`). Ohne die zweite Form waere Bedingung 2 fuer zwei Pakete leer.

## Worauf ich unsicher bin

**Der Zielbestand haengt an einem Basisnamen.** Zwei gleichnamige Dateien in
verschiedenen Ordnern loesen nicht auf; der Riegel raet nicht, sondern zaehlt die
Fundstelle als uebergangen und nennt sie. Heute tritt der Fall nicht ein (130 Dateien im
Bestand, kein Name doppelt ausserhalb der gesperrten Ordner). Er tritt ein, sobald jemand
eine zweite `daten.md` anlegt -- und dann faellt eine Pruefung still weg, statt rot zu
werden. Die Zahl der uebergangenen Fundstellen zeigt es an, aber nur, wer sie liest.

**Der naechstgelegene Verweis gewinnt, und darueber hinaus wird nicht gesucht.** Diese
Regel ist gemessen und nicht gewaehlt: Ohne sie band der Riegel das franzoesische Zitat in
`lizenzbefund-reihen.md` an `specs/daten.md` und wurde zu Unrecht rot. Sie kostet aber
etwas: Steht zwischen einem Dateinamen und der Ueberschrift zufaellig ein zweiter
Dokumentname, der nichts mit dem Zitat zu tun hat, geht die Fundstelle als uebergangen
durch. Dieser Fall kommt heute in keiner der 26 Fundstellen vor.

**Der eigene Kopfkommentar traegt ein echtes Zitat.** Es ist Absicht -- so laesst sich der
Rotnachweis ohne fremde Datei fuehren, und die eigene Datei ist damit selbst geprueft.
Es heisst aber auch: Wer den Abschnitt in `spiel.md` umbenennt, macht diesen Riegel rot.
Das ist der Zweck, kann aber ueberraschen.

---

# Ruecklauf 1 -- 2026-09-04, zweiter Lauf des Testentwicklers

Der Ruecklauf betrifft **nur Bedingung 4 und nur die Zeile zu 0034**; Bedingungen 1 bis 3
sind vom Pruefer eigenstaendig nachgemessen und bleiben Erhaltungsbedingung. Alles unten
ist an diesem Lauf gemessen, nicht aus dem Befund uebernommen.

## Was 0034 wirklich hinterlassen hat -- an der Datumsprobe

Der Befund des Pruefers stimmt: Das Kopffeld `quellen` in `daten/adressen.md` ist eine
echte und gefangene Belegstelle, aber sie stammt aus Paket 0004 vom 2026-09-01. Selbst
nachgeschlagen, diesmal mit der Datumsprobe statt mit `git log -S` allein:

```
$ git show 688e845 --stat
    kernbauer: 0031-warnsatz-in-die-werkzeugkette (6 Dateien)
    Date: Thu Sep 3 19:18:38 2026
 .../daten/adressen.md | 63 ++-
```

Der Commit traegt den Namen von 0031 und enthaelt die Arbeit von 0034 -- genau das Muster,
vor dem der Ruecklauf warnt. Im Diff dieses Commits ersetzt 0034 in `adressen.md` drei
Zeilennummern durch Abschnittsnamen, alle drei mit Ziel in `technik.md`:

| # | Stelle in `adressen.md` | Zitierte Ueberschrift in `technik.md` | Form |
|---|---|---|---|
| 1 | Begruendung zur Spalte `Adresse` | T49-Vorspann *Zwei Adresspaare tragen denselben Wert, und das braucht eine Regel statt eines Zufalls* | Schluesselwort *Absatz*, Anfuehrung unmittelbar dahinter |
| 2 | Herleitung zu den unmarkierten Geschwisterpaaren | derselbe Vorspann | dieselbe |
| 3 | Herleitung zu `land.CN.wechselkurs` | T46-Vorspann *Die elf Adressen, deren Herkunft dieses Dokument ist, abschliessend* | Schluesselwort, dann fuenf Woerter, dann Anfuehrung; Dateiname **rechts** vom Zitat |

Beide Ziele existieren als Vorspann-Ueberschrift im Sinne dieses Riegels; nachgeschlagen
im heutigen `technik.md`.

## Entscheidung: zwei fangen, eine benennen

Das Arbeitspaket laesst beides zu. Gewaehlt ist die Aufteilung, weil die beiden Formen
verschieden teuer sind -- die erste kostet ein Wort, die zweite eine Entscheidung mit
eigenem Nachweis.

### Gefangen: das Schluesselwort fuer einen Textblock

`SCHLUESSEL` kannte nur die Woerter fuer *Abschnitt* und *Ueberschrift*. Aufgenommen ist
das Wort fuer einen Textblock, in derselben Maskierung wie die anderen drei, damit der
Riegel sich nicht an seiner eigenen Konstante faengt. Gemessen, unmittelbar vorher und
nachher, ohne weitere Aenderung:

```
vorher:   21 Zitate der geprueften Form gefunden, 21 davon aufgeloest, 5 uebergangen
nachher:  23 Zitate der geprueften Form gefunden, 23 davon aufgeloest, 8 uebergangen
```

Die zwei neuen Zitate sind die Stellen 1 und 2 der Tabelle oben. Dass es genau diese sind
und nicht zwei andere, ist unabhaengig belegt -- siehe die Mutantenmessung weiter unten,
in der beide namentlich fallen (`daten/adressen.md:29`, `daten/adressen.md:556`).

Von den drei zusaetzlich uebergangenen Fundstellen war **eine ein Selbsttreffer dieses
Riegels**: Die Meldung `kein Dokumentname im Absatz` stand als Zeichenkettenliteral im
Quelltext, also mit einem Anfuehrungszeichen unmittelbar hinter dem neuen Schluesselwort.
Der Riegel las das als Zitat und suchte eine Ueberschrift namens
`; } else if (netzadresse) { grund =`. Behoben durch dieselbe Maskierung wie in
`SCHLUESSEL`, mit Begruendung an der Stelle. Die zwei uebrigen sind echt und bleiben:

* `daten/einheitenbefund-pwt-baci.md`, Kopffeld `befund_an_betreiber` -- verweist auf einen
  Textblock **derselben** Datei, traegt also keinen Dokumentnamen. Nachgeschlagen: Der
  Vorspann existiert dort. Kein verkappter toter Verweis.
* `pruefstand/test/vorrat_kernanker_probe.cpp`, Kopfkommentar -- nennt als Ziel nur `T36`
  und keinen Dokumentnamen. Nachgeschlagen: Der Wortlaut steht in `technik.md`, dort
  allerdings als Aufzaehlungspunkt (`- **...**`) und damit **nicht** als Ueberschriftszeile
  im Sinne dieses Riegels. Heute folgenlos, weil die Fundstelle ohnehin uebergangen wird;
  traegt jemand dort einen Dateinamen nach, wird der Riegel zu Unrecht rot. Ausgeschrieben,
  weil es sonst niemand merkt.

### Benannt statt gefangen: Schluesselwort nicht unmittelbar vor der Anfuehrung

Stelle 3 hat zwei voneinander unabhaengige Hindernisse, und wer nur eines loest, faengt sie
immer noch nicht:

1. Zwischen Schluesselwort und Anfuehrung stehen fuenf Woerter. `ueberschrift_hinter`
   ueberspringt dort nur Leerzeichen und einen Gegenschraegstrich.
2. Der Dokumentname steht **rechts** vom Zitat, in der Klammer dahinter. `naechster_verweis`
   sucht nur nach links.

Beides zu lockern ist derselbe Fall wie bei 0047: Wer beliebig viele Woerter zulaesst,
bindet jede Anfuehrung eines Satzes an das naechstgelegene Schluesselwort und wird rot, wo
nichts kaputt ist; wer zusaetzlich nach rechts sucht, muss entscheiden, welcher der beiden
Nachbarn gewinnt, und hat dafuer heute kein Mass. Die Form steht deshalb im Kopfkommentar
ausgeschrieben und liegt als Paket 0086 daneben
(`aufgaben/0086-belegstellenriegel-schluesselwort-mit-abstand.md`, `status: vorschlag`).

**Sie bleibt ungeschuetzt, und sie bleibt auch ungezaehlt** -- fuer den Riegel ist sie kein
Zitat, also erscheint sie weder in den Befunden noch in der Uebergangenliste. Das ist die
unangenehme Haelfte dieser Auskunft und der Grund, warum sie hier steht.

## Der Rotnachweis fuer das neue Schluesselwort

Gefuehrt an der **eigenen** Datei, ohne fremdes Gebiet und ohne Kopie: Der Kopfkommentar
traegt seit diesem Lauf ein zweites echtes Zitat, diesmal mit dem neuen Schluesselwort und
mit Ziel im T49-Vorspann. Ein Wort darin verdreht (*Zwei* zu *Drei*), gebaut, gelaufen:

```
1: 1 Abschnittszitat(e) finden ihre Ueberschrift nicht:
1:
1:   zitierend: werkzeuge/belegstellen/belegstellen_riegel.cpp:39
1:   nachgeschlagen in: specs/technik.md
1:   gesuchte Ueberschrift: Drei Adresspaare tragen denselben Wert, und das braucht eine Regel statt eines Zufalls
1/1 Test #1: belegstellen_riegel ..............***Failed    1.08 sec
0% tests passed, 1 tests failed out of 1
```

Die Meldung nennt zitierende Datei mit Zeile, Zieldatei und gesuchte Ueberschrift.
Zuruecknahme des einen Wortes, neu gebaut, wieder gruen -- der Endstand unten.

Die andere Richtung (Ueberschrift in `specs/` verdrehen statt Zitat) ist hier nicht
gefuehrt: `cp` in ein Verzeichnis ausserhalb des Repos ist dieser Rolle nicht erlaubt, und
`specs/` selbst darf dieses Paket nicht anfassen. Sie ist auch nicht offen -- der Pruefer
hat sie am unveraenderten Programm mit einer Kopie von `specs/` gefuehrt, und beide
Richtungen laufen durch denselben Vergleich.

## Gegenprobe: haengen die zwei neuen Zitate wirklich am Vorspann-Fall?

Ein Mutant, der die Vorspann-Form der Ueberschriftserkennung abschaltet (die beiden
Sternchen im Vergleich durch ein Zeichen ersetzt, das nirgends vorkommt -- so bleibt jede
Funktion aufgerufen und der Warnsatz schlaegt nicht zu):

```
6 Abschnittszitat(e) finden ihre Ueberschrift nicht:
  zitierend: daten/adressen.md:29
  zitierend: daten/adressen.md:556
  zitierend: daten/reihen.toml:265
  zitierend: daten/reihen.toml:992
  zitierend: daten/reihen.toml:1178
  zitierend: werkzeuge/belegstellen/belegstellen_riegel.cpp:39
... 24 Zitate der geprueften Form gefunden, 18 davon aufgeloest
```

Sechs von 24 fallen, und die ersten beiden sind genau die Stellen 1 und 2 aus der Tabelle
oben. Damit ist zweierlei belegt: dass die neu gefangenen Zitate die von 0034 sind, und
dass die Vorspann-Form kein Zierat ist. Mutant zurueckgenommen.

## Endstand

```
$ cmake --build <ventures/0016-.../bau>
$ ctest --test-dir <ventures/0016-.../bau>
12/12 Test #12: belegstellen_riegel ..............   Passed    0.35 sec
100% tests passed, 0 tests failed out of 12

belegstellen_riegel, Bedingung 1 (Zeilennummer in eine fremde Datei): 37 Bauquellen
gelesen, 5 Zeilenverweise getroffen, davon 0 mit Dateinamen daneben.
belegstellen_riegel, Bedingung 2 (Abschnittszitat): 37 Bauquellen und 11 Datendokumente
gelesen, 135 Dateien im Zielbestand; 24 Zitate der geprueften Form gefunden, 24 davon
aufgeloest, 7 Fundstellen uebergangen.
```

**24 und 24, erste Zahl nicht null.** Bedingung 2 haelt. Der Alleinbau
(`cmake -S werkzeuge/belegstellen`) ist ebenfalls gruen, 1/1.

## Die sechs Pakete, Stand nach diesem Lauf

| Paket | Ergebnis |
|---|---|
| 0034 | zwei von drei Belegstellen **gefangen**, die dritte **ausgewiesene Luecke** (Schluesselwort mit Abstand, Dateiname rechts) -- Paket 0086 |
| 0035 | **gefangen**, beide |
| 0044 | **gefangen** |
| 0047 | **ausgewiesene Luecke** (Ueberschrift ohne Anfuehrung) -- Paket 0079 |
| 0050 | **gefangen**, alle fuenf |
| 0057 | **gefangen**, alle vier |

## Worauf ich in diesem Lauf unsicher bin

**Ob die Aufteilung bei 0034 die richtige ist.** Der Ruecklauf laesst beide Wege zu, und
ich habe den billigeren gefangen und den teureren benannt. Wer findet, ein Paket sei erst
fertig, wenn alle drei Stellen fangen, hat einen Standpunkt -- ich halte dagegen, dass die
dritte Form dieselbe Sorte Entscheidung ist wie 0047, und 0047 ist als Luecke bestaetigt
worden.

**Die Zaehlung ist von 21 auf 24 gestiegen, und drei davon sind neu hinzugekommene
Uebergangene.** Wer die Zahlen zwischen den beiden Laeufen vergleicht, vergleicht keine
gleichen Groessen. Das steht hier, damit niemand aus 21 gegen 24 einen Fehler liest.

**Der Kopfkommentar traegt jetzt zwei echte Zitate statt einem.** Jedes ist ein Rothebel,
und jedes ist auch eine Stelle, an der ein fremdes Aufraeumen in `specs/` diesen Riegel rot
macht. Das ist gewollt; es verdoppelt aber die Angriffsflaeche dafuer, und beim dritten
sollte jemand fragen, ob das noch Nachweis ist oder schon Sammeln.
