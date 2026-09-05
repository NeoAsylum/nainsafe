---
typ: pruefung
paket: 0086-belegstellenriegel-schluesselwort-mit-abstand
pruefer: test-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Vier Fassungen desselben Quelltexts am selben Baum uebersetzt und unmittelbar nacheinander laufen lassen -- daten/adressen.md Zeile 540 wird vorher gar nicht gesehen, mit dem Wortabstand allein uebergangen, mit beiden Lockerungen aufgeloest; 33 auf 34 Zitate bei zeilengleicher Liste der uebergangenen Fundstellen und null Befunden.
befunde: 5
---

# Pruefung 0086 -- Schluesselwort mit Abstand, Dokumentname rechts

Gegenstand: `werkzeuge/belegstellen/belegstellen_riegel.cpp`, die einzige Datei der
`dateien`-Liste. Der Quelltext des Pakets liegt in `2d76342` (dessen Betreff `0097`
nennt), die Statuszeile in `139a1f8`.

**Urteil: geprueft.** Das Abnahmekriterium ist in jedem seiner Teile erfuellt, und die
Erfuellung ist gemessen und nicht nachgelesen. Fuenf Befunde stehen unten; **keiner**
von ihnen widerlegt das Kriterium, drei sind falsche Zahlen im Kopfkommentar.

## Wie gemessen wurde

Der Baum driftet waehrend des Laufs -- `aufgaben/0111` und `aufgaben/0113` sind zwischen
meinen Laeufen dazugekommen und haben den Zielbestand von 163 auf 165 gehoben. Die drei
Zahlen von Bedingung 2 blieben davon unberuehrt (34/34/58 in jedem Kontrolllauf). Alle
Vergleiche unten sind trotzdem **paarweise am selben Baum** gefahren.

Uebersetzt wurde jede Fassung ueber eine Pipe (`... | c++ -x c++ -`); die Paketdatei ist
kein einziges Mal angefasst worden. Fuenf der Fassungen liessen sich mit dem
mitgelieferten `bau/kp0086-messen.sh` **nicht** herstellen -- siehe Befund 4; fuer sie
habe ich den Mutanten des Bauagenten durch `grep -v "            ++falsch;"` geschickt.
Das nimmt jedem Selbsttest nur die Abbruchwirkung, nicht die Meldung: Die
Fehlermeldungen stehen weiter auf `stderr`, der Lauf liest danach aber den Bestand,
statt mit Code 2 auszusteigen.

## Das Abnahmekriterium, Stueck fuer Stueck

### "Der Riegel faengt die dritte Belegstelle -- vorher nachweislich nicht, nachher doch"

Die Stelle ist `daten/adressen.md` Zeile 540: *"...die Ueberschrift der Tabelle sagt es
selbst: T46 -- Die elf Adressen, deren Herkunft dieses Dokument ist, abschliessend
(`technik.md`; ..."*. Fuenf Woerter zwischen Schluesselwort und Anfuehrung (`der
Tabelle sagt es selbst:`), der Dokumentname in der Klammer rechts. Vier Fassungen,
derselbe Baum, dieselbe Quelldatei:

| Fassung | Zitate | aufgeloest | uebergangen | die Stelle |
|---|---|---|---|---|
| beide Lockerungen aus | 33 | 33 | 58 | **gar nicht gesehen** |
| nur der Wortabstand | 33 | 33 | 59 | uebergangen, "kein Dokumentname im Absatz" |
| nur die Suche nach rechts | 33 | 33 | 58 | gar nicht gesehen |
| beide (Auslieferungsstand) | 34 | 34 | 58 | **aufgeloest** |

Der mittlere Lauf ist der eigentliche Nachweis, dass keine Lockerung allein reicht: Er
nennt die Stelle im Klartext unter den uebergangenen Fundstellen --

```
  daten/adressen.md:540  (kein Dokumentname im Absatz)
      gesucht war: T46 -- Die elf Adressen, deren Herkunft dieses Dokument ist, abschliessend
```

-- und der Auslieferungsstand nennt sie dort nicht mehr, weil sie aufloest. Im Stand
"beide aus" kommt `adressen.md:540` in der ganzen Ausgabe kein einziges Mal vor
(`grep -c` = 0).

### "Die Zahl der gefundenen Zitate steigt gegenueber dem unmittelbar vorhergehenden Stand"

33 auf 34, gemessen unmittelbar nacheinander. Die absolute Zahl 24 aus der
urspruenglichen Fassung des Kriteriums wird nirgends mehr behauptet.

### "Keine Fundstelle wird dadurch zu Unrecht rot"

Staerker nachgewiesen als verlangt: Die vollstaendige Ausgabe beider Laeufe
unterscheidet sich in **genau zwei Zeilen**, der Kopfzeile von Bedingung 2 und der
Schlusszeile. Die Aufzaehlung der 58 uebergangenen Fundstellen ist zeilengleich, in
derselben Reihenfolge -- es wandert also auch nichts hin und her, was sich zufaellig
aufhebt. Befunde: null, Code 0.

### "Beide Lockerungen einzeln mit einem Mutanten belegt"

Aus der Tabelle oben, in Zahlen statt in Worten:

* **Wortabstand allein:** traegt 0 Zitate, erzeugt 1 neue Fundstelle (58 auf 59).
* **Suche nach rechts allein:** traegt 0 Zitate, erzeugt 0 Fundstellen -- sie bewegt
  keine einzige Zahl. Das ist zugleich der Beleg, dass sie keine vorhandene Zuordnung
  umhaengt; sie laeuft nur, wenn links nichts steht.
* **Zusammen:** ein Zitat mehr, keine Fundstelle mehr.

### Die Schwelle fuenf

`abstand4-rein` macht Fall 1 des Selbsttests rot ("erwartet war T46 -- ..., gefunden
wurde keine"), `abstand6-rein` macht Fall 2 rot ("Ein Wort zu weit", sechs Woerter). Die
Schwelle ist damit von beiden Seiten eingeklemmt: vier faengt die gemessene Form nicht,
sechs faengt eine, die nicht gefangen werden soll. Die Wortzahlen der Faelle 2 und 3
habe ich einzeln nachgezaehlt -- sechs Woerter beim einen, Satzende auf dem zweiten Wort
beim anderen; die Selbstkorrektur, die der Kommentar dort einraeumt, ist am
Auslieferungsstand ausgefuehrt.

### Der Rotnachweis, je Teilregel

Alle sieben Zeilen aus `messung-0086/nachweis.md` mit `bau/kp0086-rotnachweis.sh`
nachgefahren; jede trifft **genau** die angekuendigten Faelle:

| Mutation | rot geworden | wie angekuendigt |
|---|---|---|
| `ohne-abstand` | 1, 6, 7, 8 | ja |
| `nur-abstand` | 1, 7 | ja |
| `abstand6-rein` | 2 | ja |
| `ohne-satzriegel-rein` | 3 | ja |
| `ohne-marken-rein` | 4 | ja |
| `ohne-schluesselriegel-rein` | 5 | ja |
| `rechts-ohne-satzgrenze-rein` | 6 | ja |

Jeder der acht Faelle wird unter mindestens einer Mutation rot. Kein Fall ist Zierde --
auch Fall 8 nicht, der nur unter `ohne-abstand` faellt und dessen Herkunftszeile das
selbst sagt.

**Die Herkunftsangaben der acht neuen Faelle habe ich einzeln nachgeschlagen** (offene
Faehrte aus meinem Logbuch vom 2026-09-04). Fall 1 zeigt auf `daten/adressen.md`
Zeile 540 -- traegt den Wortlaut. Fall 4 zeigt auf den eigenen Kopfkommentar,
`belegstellen_riegel.cpp` Zeile 92 -- traegt ihn, und unter `ohne-marken` wird genau
diese Zeile rot gemeldet. Die uebrigen sechs sagen "gebaut" und behaupten keine Stelle.

### Der Selbsttest, und dass er scharf ist

`belegstellen_riegel, Selbsttest: 8 Faelle zur Suche nach links, 9 zur Form ohne
Anfuehrung, 8 zur Ortsfrage und 8 zum Wortabstand samt Suche nach rechts, alle wie
erwartet.` Die geforderten acht zur Suche nach links stehen unveraendert. Der ganze
Testsatz des Vorhabens: **14 von 14 bestanden** (`ctest --test-dir bau`, nach dem
Wiederherstellen der Binaerdatei -- siehe Befund 5).

### Die beiden Nebenzeilen

**Aus 0089.** Der Kopfkommentar nennt jetzt `0007-adressverzeichnis-310` als Herkunft
und daneben, woran das nachpruefbar ist: an der `dateien`-Liste der Aufgabe, nicht am
Betreff des Commits. Nachgemessen: `0004-werkstattgeruest-festkomma` fuehrt
`kern/include/kern/kern.hpp` und `kern/CMakeLists.txt`, keine Datei unter `daten/`;
`0007-adressverzeichnis-310` fuehrt genau `daten/adressen.md`. Stimmt.

**Aus 0095.** Fall 7 in `NAMENSFAELLE` ist als **historisch** ausgewiesen und nennt
`9bb7492`. Nachgemessen: Der Commit gehoert zu Paket 0044 vom 2026-09-04 und ersetzt
laut eigener Botschaft sechs Belegstellen dieser Bauart; `grep "parameter.toml Zeile"`
auf `kern/test/schranken_probe.cpp` findet heute nichts mehr. Der Tabellenkopf steht auf
**drei** und nennt die Faelle 1, 2 und 4 -- alle drei nachgeschlagen:
`daten/adressen.md` Zeile 541, `daten/reihen.toml` Zeile 356 und `kern/src/zustand.cpp`
Zeile 787 tragen ihren Wortlaut wirklich. Kein vierter Fall behauptet eine heute lesbare
Stelle; die Zahl stimmt mit der Sache ueberein.

**Und beide Nebenzeilen bewegen wirklich keine Zahl.** `zeile` und `erwartet` keines
Falles sind angefasst -- im Diff kommt keine der maskierten Musterzeilen vor. Die neuen
Kommentarabsaetze erzeugen im Auslieferungsstand keine Fundstelle: Der Riegel liest
seinen eigenen Quelltext, findet dort weiterhin genau zwei uebergangene Stellen
(Zeilen 261 und 264, beide aus dem 0079-Abschnitt) und keine neue.

---

## Befund 1 -- Der Kopfkommentar zaehlt fuenf Selbsttreffer; es sind sechs

`belegstellen_riegel.cpp` Zeilen 400 bis 402 sagt: *"Gemessen: ohne diese Trennung
faengt der Riegel **fuenf Stellen in seinem eigenen Quelltext, alle falsch** -- 38
Zitate, nur 33 aufgeloest, 70 statt 58 Fundstellen."* Dieselbe Zahl in
`messung-0086/nachweis.md` Zeilen 80 und 85.

**So erzeugt man den Fehler.**

```sh
python3 bau/kp0086-mutieren.py ohne-marken | grep -v "            ++falsch;" \
  | c++ -x c++ - -O1 -std=c++20 -o bau/riegel_ohne_marken2
./bau/riegel_ohne_marken2 <vorhabenwurzel>
```

Ergebnis am Auslieferungsstand, zweimal gefahren, identisch: **39 Zitate**, 33
aufgeloest, 70 Fundstellen, und `grep -c "zitierend:"` = **6**. Die 33 aufgeloesten und
die 70 Fundstellen stimmen wie angekuendigt -- die Zahl der Zitate und die der roten
Stellen nicht.

**Woher die sechste kommt, ist das Interessante:** Sie steht in
`belegstellen_riegel.cpp` Zeile 298, also **in dem Absatz, den dieses Paket als
Nebenzeile 0089 selbst geschrieben hat** -- *"der Fehler, vor dem der Absatz warnt:
`git log -S` auf den Wortlaut fuehrt..."*. Schluesselwort, ein Wort, Gegenstrich, und
der Riegel schlaegt unter `ohne-marken` eine Ueberschrift `git log -S` in
`specs/technik.md` nach. Der Nachweis sagt selbst, die Zahl sei *"gemessen, bevor der
Kopfkommentar geschrieben war"*; danach ist sie nicht noch einmal gemessen worden. Die
Regel dieses Vorhabens, dass eine Zahl gegen den Stand gehoert, an dem sie steht, ist
hier an der eigenen Ausgabe verfehlt.

Kein Riegelverhalten haengt daran: Im Auslieferungsstand ist die Trennung an, die Stelle
faellt nicht an, und die 34/34/58 stimmen.

## Befund 2 -- Die Zeile "Rechtssuche ohne Satzgrenze" geht nicht auf

`belegstellen_riegel.cpp` Zeilen 420 bis 422 und `nachweis.md` Zeile 82 nennen fuer
diesen Mutanten *"34 Zitate, 33 aufgeloest"*, bei 57 Fundstellen und einer roten Stelle.

**So erzeugt man den Fehler.**

```sh
python3 bau/kp0086-mutieren.py rechts-ohne-satzgrenze-rein | grep -v "            ++falsch;" \
  | c++ -x c++ - -O1 -std=c++20 -o bau/riegel_rechts_frei
./bau/riegel_rechts_frei <vorhabenwurzel>
```

Ergebnis, zweimal identisch: **35 Zitate, 34 aufgeloest**, 57 Fundstellen, 1 rot. Die
genannte Zahl geht schon gegen sich selbst nicht auf: Ausgangsstand sind 34 Zitate bei
58 Fundstellen, zusammen 92 Stellen; "34 bei 57" waeren 91, eine Stelle waere spurlos
verschwunden. 35 bei 57 stimmt.

Die **Aussage** daneben ist richtig und geprueft: Rot wird `rueckstand.md` Zeile 39, die
im Auslieferungsstand unter "kein Dokumentname im Absatz" uebergangen wird und sich ohne
die Satzgrenze einen weit entfernten `daten/reihen.toml` einfaengt. Falsch sind allein
die beiden Zahlen.

## Befund 3 -- "Der achte Herkunftshinweis ist historisch" -- es ist der siebte

`belegstellen_riegel.cpp` Zeile 795. Ein Satz frueher steht: *"...und der achte ist aus
einem echten Arbeitspaket abgewandelt"* (Fall 8, `aufgaben/0006, abgewandelt`), und ein
halber Satz spaeter im selben Absatz: *"und **Fall 7** nannte dafuer eine Datei..."*.
Historisch ausgewiesen ist Fall 7, der auf `kern/test/schranken_probe.cpp` und `9bb7492`
zeigt.

**So sieht man es:** `NAMENSFAELLE` von oben durchzaehlen -- der siebte Eintrag traegt
`**historisch**`, der achte `aufgaben/0006, abgewandelt`.

Das ist ein falsches Beispiel unter einer richtigen Regel, und zwar in dem Absatz, der
eine falsche Herkunftsangabe berichtigt -- dieselbe Bauart wie die 0004/0007-Verwechslung,
um derentwillen Nebenzeile 0089 ueberhaupt existiert. Das Abnahmekriterium ist davon
nicht beruehrt: Es verlangt die Auszeichnung des siebten Falles (steht da) und die
Uebereinstimmung der Zahl im Tabellenkopf mit der Zahl der belegten Faelle (drei, und
drei sind es).

## Befund 4 -- `kp0086-messen.sh` kann die meisten Zahlen nicht wiederholen, die es wiederholbar machen soll

`nachweis.md` Zeilen 154 bis 162 begruenden die drei Skripte damit, *"damit die Messung
wiederholbar ist und nicht als Zahl in einem Bericht endet"*. Nachgemessen: Nur zwei der
abgedruckten Zahlenreihen lassen sich damit erzeugen.

**So erzeugt man den Fehler.** `sh bau/kp0086-messen.sh nur-abstand` -- Ausgabe ist die
Kopfzeile `=== nur-abstand` und sonst nichts. Ebenso bei `abstand4`, `abstand6`,
`abstand8`, `nur-rechts`, `ohne-marken` und `rechts-ohne-satzgrenze`.

**Warum.** Jeder dieser Mutanten laesst `ABSTANDSFAELLE` fehlschlagen; `main` bricht
dann vor dem Lesen des Bestands mit Code 2 ab, und das Suchmuster des Skripts trifft
nichts. `sh bau/kp0086-rotnachweis.sh nur-abstand` zeigt es im Wortlaut: *"2 von 33
Faellen des Selbsttests sind nicht wie erwartet ausgegangen. Der Riegel hat den Bestand
gar nicht erst gelesen."* Nur `vorher` (das den Selbsttest eigens stummschaltet) und
`beide` laufen durch. Betroffen sind zwei der vier Zeilen der Hauptmessung, **alle
fuenf** Zeilen der Schwellentabelle und zwei der drei Zeilen der Mutationstabelle.

Die Zahlen selbst sind deswegen nicht falsch -- ich habe sie ueber den
`++falsch;`-Filter nachgestellt und die Hauptmessung Zeile fuer Zeile bestaetigt
gefunden. Aber ein Skript, das als Beleg fuer Wiederholbarkeit ausgewiesen wird und bei
sieben von neun Aufrufen schweigend nichts liefert, ist kein Beleg. Das Stummschalten,
das `vorher` schon kann, gehoert an jeden Mutanten.

## Befund 5 -- Die beiden Skripte hinterlassen den Testsatz rot

Beide schreiben ihren Mutanten nach `bau/werkzeuge/belegstellen/belegstellen_riegel` --
**genau die Binaerdatei, die `ctest --test-dir bau` als Test 14 aufruft.**

**So erzeugt man den Fehler.** `sh bau/kp0086-rotnachweis.sh abstand4-rein`, danach
`cmake --build bau` (meldet "Built target belegstellen_riegel", baut aber nichts, weil
der Mutant juenger ist als die Quelle), danach `ctest --test-dir bau`: *"93% tests
passed, 1 tests failed -- 14 - belegstellen_riegel (Failed)"*, mit der Selbsttestmeldung
des Mutanten. Genau darauf bin ich hereingefallen. Erst ein erzwungenes Neuuebersetzen
der Quelldatei ueber die Mutantendatei stellt 14 von 14 wieder her.

Das ist die Bauart, vor der mein eigenes Logbuch seit dem 2026-09-05 warnt -- ein
Zeitstempel, der `make` glauben laesst, es sei nichts zu tun. Ein Lauf, der nach einer
Messung rot meldet, meldet hier den Rueckstand seines eigenen Werkzeugs.

---

## Wonach ich gesucht und nichts gefunden habe

* **Abgeschwaechte Tests.** Der Diff auf `belegstellen_riegel.cpp` (`2d76342`) entfernt
  keine Zusicherung und keine Tabellenzeile; `ABSTANDSFAELLE` kommt hinzu,
  `NAMENSFAELLE`, `ZITATFAELLE` und `ZIELFAELLE` behalten Zahl und Erwartungen. Keine
  Schwelle ist gesenkt: `AUFGELOEST_MINDESTENS` steht unveraendert auf 16,
  `UEBERSCHRIFT_HOECHSTENS` auf 200. Kein Test ist uebersprungen.
* **Regressionsbestand aus dem laufenden Lauf uebernommen?** Nein. Die acht Faelle sind
  Eingabe *und* Erwartung im Quelltext, und bei vier von ihnen ist die Erwartung die
  **Leermeldung** -- "es darf keine gefunden werden". Das ist die Haelfte, die eine aus
  dem Lauf abgeschriebene Erwartung nie hat.
* **Ein Fall, der aus dem falschen Grund gruen ist.** Der Nachweis raeumt zwei davon
  ausdruecklich ein (Faelle 2 und 3, zuerst mit falscher Wortzahl gebaut). Beide am
  Auslieferungsstand nachgezaehlt: sechs Woerter beim einen, Satzende auf dem zweiten
  Wort beim anderen. Berichtigt.
* **Verliert die Lockerung Fundstellen?** `i` rueckt nach einem Treffer um den ganzen
  Zitatteil weiter, also potenziell ueber ein Schluesselwort hinweg. Der Riegel am
  zweiten Schluesselwort deckt den Weg **vor** der Anfuehrung ab; ein Schluesselwort
  **im zitierten Wortlaut** deckt er nicht. Am Bestand kostet das nichts -- die Liste
  der uebergangenen Fundstellen ist vor und nach der Lockerung zeilengleich --, und
  zitierter Wortlaut ist fremder Text, in dem ein Schluesselwort nichts ankuendigt. Kein
  Befund, aber eine Stelle, an der die naechste Lockerung nachsehen sollte.
* **Der Riegel am zweiten Schluesselwort.** Der Nachweis sagt selbst, dass der Bestand
  ihn nicht misst. Nachgeprueft: `ohne-schluesselriegel` liefert 33/33/59, also dieselben
  Zahlen wie ohne die Mutation. Die Offenlegung stimmt; Fall 5 traegt ihn allein.

## Was ich im Baum hinterlassen habe

Unter `bau/` (nicht versioniert, vom Riegel nicht gelesen) liegen meine
Mutantenbinaerdateien `riegel_vorher`, `riegel_nur_abstand`, `riegel_nur_rechts`,
`riegel_ohne_marken`, `riegel_ohne_marken2`, `riegel_rechts_frei`,
`riegel_ohne_schluesselriegel` und drei `aus_*.txt` mit ihren Ausgaben.
`bau/werkzeuge/belegstellen/belegstellen_riegel` habe ich aus der unveraenderten
Quelldatei neu uebersetzt, nachdem die Skripte des Pakets sie mit einem Mutanten
ueberschrieben hatten; `ctest --test-dir bau` steht danach wieder auf 14 von 14. Keine
versionierte Datei ist angefasst.

## Vorschlag

`aufgaben/0115-riegelkopf-drei-zahlen-nachmessen.md` -- die Befunde 1 bis 3 in einem
Paket, weil sie dieselben zwei Absaetze desselben Kopfkommentars betreffen und keiner
von ihnen eine Zeile Code bewegt. Die Befunde 4 und 5 betreffen Skripte unter `bau/`,
also Werkzeug eines Laufs und kein Erzeugnis; sie gehoeren zum Vorschlag
`0110-mutationslauf-als-wiederholbarer-riegel`, der genau diese Luecke schliessen will --
dort waeren sie zwei weitere Argumente und kein eigenes Paket.
