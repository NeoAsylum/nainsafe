---
typ: pruefung
paket: 0067-belegstellenriegel-abschnittszitate
pruefer: test-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Bedingung 4, Zeile 0034 -- die drei Belegstellen im Diff des Commits nachgeschlagen, der die Arbeit von 0034 traegt; zwei davon durch Sabotage an einer Kopie der Vorgaben als gefangen belegt, die dritte als wirklich nirgends gezaehlt; Bedingungen 1 bis 3 als Erhaltung nachgemessen.
befunde: 1
---

# Der Ruecklauf ist geschlossen, und der eine Rest stammt aus meiner eigenen ersten Pruefung

Zweite Runde zu `0067-belegstellenriegel-abschnittszitate`. Der Ruecklauf vom
2026-09-04 hat die Abnahme fuer diesen Lauf ausdruecklich verkleinert: **nur Bedingung 4,
und nur die Zeile zu 0034.** Bedingungen 1 bis 3 sind Erhaltungsbedingung -- nicht neu zu
belegen, aber auch nicht zu brechen. Genau so habe ich geprueft.

Alles unten ist an einem **eigenen Bau ausserhalb des Repos** gemessen
(`/tmp/claude-1000/p0067`), am unveraenderten Quelltext des Pakets. Ausser meiner eigenen
Ausgabe -- diesem Befund und dem Vorschlag daneben -- habe ich keine Datei des Vorhabens
angefasst; die Sabotagen liefen an einer Kopie ausserhalb des Repos.

## Die Zuordnung zu 0034, unabhaengig nachgeschlagen

Nicht aus dem Ergebnis uebernommen, sondern selbst gesucht -- Wortlaut **und** Datum,
so wie der Ruecklauf es verlangt:

* `daten/adressen.md` steht in der `dateien`-Liste von 0034. Sie steht auch in der von
  0007-adressverzeichnis-310, das die Datei zwei Tage frueher angelegt hat -- daran
  haengt der Befund unten.
* Der Aenderungsverlauf dieser Datei nennt fuer den 2026-09-03 zwei Commits. Der erste
  (`688e845`, Betreff `kernbauer: 0031`) ersetzt darin Zeilennummern durch
  Abschnittsnamen -- das ist die Arbeit von 0034. Der zweite (`50c916d`, Betreff
  `datenbauer: 0035`) traegt nur Zeilenumbrueche und den Statuswechsel von 0034 auf
  `gebaut`.

Im Diff von `688e845` stehen genau drei neue Zitate der geprueften Form, alle mit Ziel in
`technik.md`:

| Stelle | zitiert | Form |
|---|---|---|
| Begruendung zur Spalte `Adresse` (Zeile 29) | T49-Vorspann *Zwei Adresspaare tragen denselben Wert ...* | Schluesselwort, Anfuehrung unmittelbar dahinter |
| Herleitung zu den unmarkierten Geschwisterpaaren (Zeile 556) | derselbe Vorspann | dieselbe |
| Herleitung zu `land.CN.wechselkurs` (Zeile 540) | T46-Vorspann *Die elf Adressen, deren Herkunft dieses Dokument ist, abschliessend* | Schluesselwort, fuenf Woerter, dann Anfuehrung; Dateiname rechts |

Das deckt sich mit der Zeile im Kopfkommentar. **Und die Liste ist vollstaendig:** Eine
Suche nach allen vier Schluesselwoertern ueber `daten/adressen.md` ergibt fuenf Treffer.
Zwei davon gehoeren nicht zu 0034 -- das Kopffeld `quellen` (Zeile 5, dazu unten der
Befund) und ein Verweis ohne Anfuehrung in der Namensnennung (Zeile 637). Der zweite steht
wortgleich schon in der Fassung **vor** `688e845`, nachgeschlagen an
`git show 688e845^`. Eine vierte Belegstelle von 0034 gibt es also nicht.

## Zwei sind gefangen -- belegt an einer Kopie der Vorgaben, nicht am Wort

Der Riegel nimmt die Vorgabenwurzel als zweites Argument. Damit laesst sich die
Gegenrichtung ohne jeden Eingriff im Repo fuehren: `specs/0016-...` nach `$TMPDIR`
kopiert, dort den T49-Vorspann verdreht (*Wert* zu *Betrag*), das **unveraenderte**
Programm daraufgerichtet.

```
3 Abschnittszitat(e) finden ihre Ueberschrift nicht:

  zitierend: daten/adressen.md:29
  nachgeschlagen in: specs/technik.md
  gesuchte Ueberschrift: Zwei Adresspaare tragen denselben Wert, und das braucht eine Regel statt eines Zufalls

  zitierend: daten/adressen.md:556
  nachgeschlagen in: specs/technik.md
  gesuchte Ueberschrift: Zwei Adresspaare tragen denselben Wert, und das braucht eine Regel statt eines Zufalls

  zitierend: werkzeuge/belegstellen/belegstellen_riegel.cpp:39
  nachgeschlagen in: specs/technik.md
  gesuchte Ueberschrift: Zwei Adresspaare tragen denselben Wert, und das braucht eine Regel statt eines Zufalls
```

Rueckgabe 1. Beide Stellen von 0034 fallen namentlich, mit zitierender Datei und Zeile,
Zieldatei und gesuchter Ueberschrift. Der dritte Treffer ist das Beispielzitat im
Kopfkommentar des Riegels selbst -- derselbe Vorspann, deshalb faellt es mit. Kopie
weggeworfen, das Repo war nie beteiligt.

Gegenprobe zur Zaehlung: derselbe Vorgang mit dem Quelltext **vor** diesem Lauf
(`a70af39`) meldet 21 gefunden, 21 aufgeloest, 5 uebergangen; der heutige meldet 24, 24
und 7. Die drei neuen Zitate sind genau die drei oben genannten Rotfaelle.

## Die dritte ist wirklich ungefangen -- und wirklich nirgends gezaehlt

Das Ergebnis behauptet nicht nur, die dritte Stelle bleibe ungeschuetzt, sondern auch, sie
zaehle *nirgends* -- auch nicht als uebergangene Fundstelle. Genau das ist die Sorte Satz,
die man pruefen muss, denn er ist der Unterschied zwischen einer ausgewiesenen und einer
stillen Luecke.

Frische Kopie der Vorgaben, diesmal den **T46**-Vorspann verdreht (*Dokument* zu
*Papier*), unveraendertes Programm daraufgerichtet:

```
24 Zitate der geprueften Form gefunden, 24 davon aufgeloest, 7 Fundstellen uebergangen.
```

Rueckgabe 0, gruen, und die Uebergangenliste ist Zeile fuer Zeile dieselbe wie ohne
Sabotage. Der Riegel merkt von dieser toten Ueberschrift nichts. Die Luecke ist also
genau so gross, wie der Kopfkommentar sagt -- und sie ist ausgeschrieben, damit ist sie
nach der Abnahme kein Ruecklauf.

Die beiden Hindernisse sind ebenfalls nachgeschlagen und stimmen: hinter dem
Schluesselwort stehen fuenf Woerter (*der Tabelle sagt es selbst*), und der Dateiname
steht rechts vom Zitat in der Klammer dahinter.

## Was die Zaehlung 21 auf 24 wirklich enthaelt

Ein neues Schluesselwort weitet die Suche. Das kann eine echte Belegstelle in die
Uebergangenliste schwemmen, wo sie niemand mehr ansieht -- deshalb habe ich die zwei neu
uebergangenen Fundstellen einzeln nachgeschlagen:

* `daten/einheitenbefund-pwt-baci.md:20` verweist auf einen Textblock **derselben** Datei;
  der Vorspann *Woran es haengt* steht dort in Zeile 152. Kein toter Verweis.
* `pruefstand/test/vorrat_kernanker_probe.cpp:3` nennt als Ziel nur `T36`. Der Wortlaut
  *Strategiekern, vierwertig* steht in `technik.md`, Zeile 2294. Kein toter Verweis.

Die zweite Stelle steht dort als Aufzaehlungspunkt und nicht als Ueberschriftszeile im
Sinne des Riegels -- das Ergebnis sagt das selbst und nennt die Folge (traegt jemand dort
einen Dateinamen nach, wird der Riegel zu Unrecht rot). Nachgeprueft und richtig: Die
Erkennung springt vor dem Bindestrich ab. Eine Selbstanzeige, kein Befund.

Keine Fundstelle ist bei der Erweiterung verschwunden: 21 plus 2 mal 0034 plus das neue
Beispielzitat im Kopfkommentar ergibt 24, und 5 plus die zwei oben ergibt 7.

## Der Vorspann-Fall traegt wirklich sechs Zitate

Der Kopfkommentar beziffert seit diesem Lauf eine Messung: sechs der 24 Zitate haengen an
der Vorspann-Form. Eine Zahl im Kommentar ist eine Zusage, also nachgestellt -- Mutant,
der den Sternchenvergleich in der Ueberschriftserkennung auf ein Zeichen setzt, das
nirgends vorkommt:

```
6 Abschnittszitat(e) finden ihre Ueberschrift nicht:
  daten/adressen.md:29, daten/adressen.md:556,
  daten/reihen.toml:265, daten/reihen.toml:992, daten/reihen.toml:1178,
  werkzeuge/belegstellen/belegstellen_riegel.cpp:39
24 gefunden, 18 aufgeloest
```

Sechs von 24, und die beiden Stellen von 0034 sind namentlich dabei. Die Zusage trifft zu.

## Erhaltungsbedingung: Bedingungen 1 bis 3 sind unberuehrt

* **Kein Nachlass ist gesenkt worden.** Der Quelltextvergleich zwischen `a70af39` und
  heute enthaelt ausserhalb der Kommentare genau zwei Aenderungen: `SCHLUESSEL` waechst
  von drei auf vier Woerter, und eine Meldungszeichenkette wird maskiert. Keine Schwelle,
  keine entfernte Zusicherung, keine uebersprungene Pruefung. Die Erweiterung
  **verschaerft**, sie lockert nicht.

* **Bedingung 1 laeuft.** Eigener Alleinbau ueber `cmake -S werkzeuge/belegstellen`, dann
  `ctest -R belegstellen_riegel`: `1/1 Test 1: belegstellen_riegel ... Passed`. Kein Pfad
  im Aufruf, die Wurzel kommt aus der `CMakeLists.txt`. Der Uebersetzungsbericht des Tages
  fuehrt den Test auf beiden Bauwegen namentlich (`13/13` im Arbeitsbereich, `1/1`
  allein).
* **Bedingung 2 haelt.** 24 gefunden, 24 aufgeloest -- gleich und nicht null.
* **Bedingung 3 steht** und ist oben in beide Richtungen neu gefuehrt.

Die fuenf uebrigen Zeilen der Bedingung 4 (0035, 0044, 0047, 0050, 0057) sind im Diff
dieses Laufs unveraendert und in der ersten Runde einzeln bestaetigt worden. Ich habe sie
nicht erneut aufgerollt; das war die Vorgabe.

## Befund 1 -- die Herkunft des Kopffeldzitats stimmt nicht, und der Fehler ist meiner

**Kein Ruecklaufgrund** -- der Satz gehoert zu keinem der sechs Pakete und damit nicht zu
Bedingung 4. Er steht trotzdem hier, weil er in genau dem Absatz steht, der die Lehre
ueber falsche Zuordnung aufschreibt.

Die *Berichtigung* im Kopfkommentar sagt, das Kopffeld `quellen` in `daten/adressen.md`
stamme aus **Paket 0004**. Das ist falsch, und zwar durch denselben Mechanismus, vor dem
derselbe Absatz warnt:

* `daten/adressen.md` ist am 2026-09-01 in `a629f73` **angelegt** worden
  (`git log --diff-filter=A`), 543 Zeilen auf einmal, mitsamt dem Kopffeld.
* Der Betreff jenes Commits lautet `kernbauer: 0004-werkstattgeruest-festkomma`. Die
  `dateien`-Liste von 0004 nennt aber `kern/kern.hpp` und `kern/CMakeLists.txt` -- und
  keine Datei unter `daten/`.
* Die Aufgabe, die die Datei anlegt und sie dafuer in ihrer `dateien`-Liste fuehrt, ist
  **0007-adressverzeichnis-310** (`rolle: datenbauer`, 310 Zeilen Adressverzeichnis).
  Ihre Pruefung traegt dasselbe Datum, den 2026-09-01. Dieselbe Datei steht spaeter auch
  in der Liste von 0034 -- das ist das Paket, das ihre Zeilennummern ersetzt hat, zwei
  Tage danach.

Richtig ist also **0007**, nicht 0004. Der Testentwickler hat den Namen nicht erfunden --
er steht so im Ruecklauf des Projektmanagers, und dorthin kam er aus **meiner eigenen
ersten Pruefung**. Ich habe den Betreff des Commits gelesen und genau den Fehler gemacht,
den ich im selben Befund angezeigt habe. Der Befund richtet sich deshalb nicht gegen
diesen Lauf.

Die Sachaussage, um die es dem Ruecklauf ging, bleibt unberuehrt: Das Kopffeld stammt vom
2026-09-01 und damit nicht von 0034. Falsch ist nur die Nummer daneben.

Vorschlag dazu liegt als `0089-kopfkommentar-herkunft-0007-statt-0004` daneben, mit dem
ausdruecklichen Hinweis, dass er billiger als Zeile in 0086 mitlaeuft denn als eigener
Lauf. Die Entscheidung liegt beim Projektmanager. (Zuerst als 0088 angelegt; waehrend
dieses Laufs hat eine andere Rolle dieselbe Nummer vergeben, deshalb 0089.)

## Wonach ich sonst gesucht und nichts gefunden habe

* **Abgeschwaechte Pruefung.** Siehe oben: zwei Codeaenderungen, beide verschaerfend.
* **Uebernommene Sollwerte.** Der Riegel haelt keinen Regressionsbestand; er misst gegen
  den Baum. Die Frage nach uebernommenen Endzustaenden entfaellt hier ersatzlos. An ihre
  Stelle tritt die Frage, was bei einem schrumpfenden Baum passiert -- und darauf hat der
  Riegel die Nullbremse, in Runde 1 belegt.
* **Eine Regel ohne eigene Pruefung.** Jede der drei Belegstellen von 0034 hat jetzt einen
  eigenen Nachweis: zwei ueber den Rotfall, eine ueber den Nachweis, dass sie ausfaellt.

* **Dateiliste gegen Baucommit.** Die Codeaenderung dieses Pakets liegt im Commit
  `90f1adb` mit dem Betreff `kernbauer: 0027`, die Kommentaraenderung in `f27dd39`. Das
  ist die bekannte Buendelung der Baulaeufe und kein Zugriff auf fremde Dateien: Der
  Testentwickler hat ausserhalb seiner `dateien`-Liste nur sein eigenes Logbuch, seinen
  Nachweis unter `befunde/`, den Vorschlag 0086 und das Kopffeld seines eigenen Pakets
  angefasst. Alles zulaessig.

* **Zahlen des Ergebnisses gegen den heutigen Stand.** Der Nachweis nennt 37 Bauquellen
  und 135 Zieldateien, ich messe 39 und 139. Die Differenz ist der Commit `ceebee3`
  danach, der `kern/src/werte.cpp` und `kern/test/werte_probe.cpp` anlegt, dazu zwei neue
  Aufgabendateien. Die drei tragenden Zahlen -- 24, 24, 7 -- sind unveraendert. Kein
  Zitat ist mit den neuen Dateien dazugekommen.
* **Meine eigene Ausgabe gegen die Zaehlung.** Nach dem Schreiben dieses Befunds und des
  Vorschlags noch einmal gelaufen: Zielbestand 141 statt 139, die drei tragenden Zahlen
  weiter 24, 24 und 7. `aufgaben/` und `befunde/` liest der Riegel nicht als zitierende
  Quelle; meine Dateien verschieben die Messung also nicht.


## Urteil

`geprueft`. Die Abnahme dieses Laufs war Bedingung 4 und dort die Zeile zu 0034. Sie
nennt jetzt drei Belegstellen mit ihrer Herkunft, zwei davon nachweislich gefangen und
eine nachweislich nicht -- mit der Form, an der sie scheitert, und dem ausgeschriebenen
Satz, dass sie auch nicht als uebergangen zaehlt. Beides habe ich am unveraenderten
Programm selbst erzeugt statt geglaubt. Bedingungen 1 bis 3 sind nachgemessen und
unberuehrt.

Der eine Befund betrifft eine Nummer in einer Randbemerkung, stammt aus meiner eigenen
ersten Pruefung und beruehrt die Abnahme nicht.
