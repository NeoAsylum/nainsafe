---
typ: messung
paket: 0110-mutationslauf-als-wiederholbarer-riegel
rolle: testentwickler
datum: 2026-09-05
bezugsstand: bf0519b
geaenderte_dateien: [werkzeuge/mutation/CMakeLists.txt, werkzeuge/mutation/mutationslauf.cpp, werkzeuge/mutation/katalog.md, CMakeLists.txt]
---

# Der Mutationslauf laeuft jetzt auf Zuruf

Neu sind drei Dateien unter `werkzeuge/mutation`; an der `CMakeLists.txt` des
Arbeitsbereichs ist ein Mitglied dazugekommen und der Kommentar darueber nachgezogen.
Keine fremde Datei ist angefasst worden.

## Bedingung 1 -- das Ziel, sein Urteil und der unberuehrte Arbeitsbaum

`cmake --build <baubaum> --target mutationslauf` liest `werkzeuge/mutation/katalog.md`,
faehrt jeden dort verzeichneten Fall und gibt Code 0 zurueck. Der letzte Lauf am Stand
oben:

```
mutationslauf, Selbsttest des Kataloglesers: 11 Faelle, 9 Fehlerarten, alle vertreten -- wie erwartet.
mutationslauf: 19 Fall/Faelle im Katalog, 19 gewaehlt.
mutationslauf, Vorlauf: 1 Probe(n) am unveraenderten Baum -- gruen.

  ok      M15  erreicht rot, erwartet rot
            FEHLGESCHLAGEN Zeile 870:   [K7 Realindex, Index, Startjahr 10.000, nie neu basiert]
  ...
  ok      Z02  erreicht rot, erwartet rot
            FEHLGESCHLAGEN Zeile 1266: enthaelt(ohne_unterschied.fertig(), "Unterschied (Ebene 3 von 3, T20) ...")
mutationslauf, Nachlauf: 1 Probe(n) am unveraenderten Baum -- gruen.
mutationslauf: 19 von 19 Faellen wie erwartet.
```

**Der unberuehrte Arbeitsbaum ist gemessen und nicht behauptet.** `git status --porcelain`
ueber das Vorhaben vor dem Lauf und danach, Zeichen fuer Zeichen verglichen: kein
Unterschied. Der Lauf schreibt ausschliesslich unter `<baubaum>/mutationslauf` -- je Fall
eine mutierte Wegwerfquelle und ein Protokoll --, und der Baubaum ist ignoriert.

Der Weg dorthin ist der Grund, warum keine Quelldatei angefasst wird: Der mutierte Text
geht als eigene Datei an den Uebersetzer, dessen Ausgabe die Objektdatei im Baubaum
ueberschreibt. Zurueck geht es ueber den Zeitstempel der echten Quelle -- Inhalt
unveraendert, also sieht `git` nichts -- und einen erneuten Bau des Ziels. Das geschieht
nach **jedem** Fall, nicht erst am Ende: Sobald ein Katalog zwei Quelldateien nennt,
liefe sonst ein Fall auf dem Mutanten eines anderen.

Die Uebersetzerschalter werden aus der Schalterdatei gelesen, die CMake je Ziel im
Baubaum anlegt, und nicht abgeschrieben. Der Wegwerftreiber von Paket 0097 trug sie als
Literal und waere nach der naechsten Aenderung an der Werkzeugkette lautlos falsch
geworden.

## Bedingung 2 -- die neunzehn Faelle

Der Katalog traegt beim Anlegen genau die neunzehn Faelle, die Paket 0097 gefahren hat:
`M15` bis `M21`, `N02` bis `N11` -- die siebzehn aus dem ersten Befund der Pruefung zu
Paket 0010 -- und dazu `Z01` und `Z02`, die beiden uebrigen Kopfzeilen. Jeder erwartet
`rot`, und jeder erreicht `rot`.

Zu jedem Fall steht in der Zusammenfassung die **erste rote Zusicherung im Wortlaut**.
Das ist kein Zierrat: Mein Logbuch nennt dreimal den Fall, dass ein Mutant aus einem
anderen Grund scheitert als dem gesuchten und die Probe trotzdem rot aussieht. Die neunzehn
Zeilen oben lassen sich Fall fuer Fall gegen die gemeinte Stelle halten -- `M18` reisst an
der Klasseneinheit, `M20` am Zinsfeld der halb gerechneten Belegung, `N10` an der
Einheitentabelle selbst.

**Ein Muster, das nicht genau einmal vorkommt, ist ein Fehlschlag.** Nachgestellt: ein
zwanzigster Fall mit einem Suchtext, den es in der Quelle nicht gibt.

```
  FEHLER  XX8  erreicht (keines), erwartet rot
            das Suchmuster kommt 0-mal vor, nicht genau einmal
mutationslauf: 19 von 20 Faellen wie erwartet.
```

Der Fall ist danach wieder entfernt worden.

## Bedingung 3 -- der Rotnachweis

Eingefuegt wurde ein Fall `XX9`, der `gruen` erwartet, wo `rot` richtig ist -- die
Einheit der Klasse 13 verstellt, dieselbe Sorte Mutation wie `N10`.

```
  FEHLER  XX9  erreicht rot, erwartet gruen
mutationslauf: 19 von 20 Faellen wie erwartet.
gmake: *** [Makefile:382: mutationslauf] Error 2
```

Nach dem Entfernen des Falls ist der Lauf wieder gruen, Code 0. Der Katalog nach dem
Entfernen enthaelt weder `XX8` noch `XX9` noch eine Spur davon; nachgezaehlt.

## Ein dritter Rotnachweis, den die Abnahme nicht verlangt -- und der einen Fehler fand

Der Vorlauf ist die Zusicherung, ohne die das ganze Werkzeug nichts misst: Ein aus
fremdem Grund roter Baum meldete jede Mutation als gefangen, und der Lauf gaebe Null
zurueck, waehrend er blind ist. Eine Zusicherung, die nie rot geworden ist, ist eine
Vermutung -- also habe ich sie rot gemacht: ein Fall, dessen `probe` auf einen Namen
zeigt, den es nicht gibt.

**Der Vorlauf meldete gruen.** Zwei Proben gezaehlt, beide gruen, und die Mutation lief
danach ganz normal.

Die Ursache ist nicht mein Riegel, sondern der Aufruf darunter: `ctest -R <muster>` gibt
mit einem Muster, auf das kein Fall passt, **Code 0** zurueck. Ein vertippter Probenname
waere damit still durchgelaufen, und im Vorlauf haette er genau die Zusicherung
ausgehebelt, um derentwillen er existiert. Behoben mit `--no-tests=error`; danach:

```
  Vorlauf: die Probe probe_die_es_nicht_gibt ist rot (Code 8).
mutationslauf, Vorlauf: 2 Probe(n) am unveraenderten Baum -- NICHT GRUEN.
Der Vorlauf ist nicht gruen. Ohne ihn misst kein Fall etwas: ...
```

Kein Fall wird in diesem Zustand gefahren; der Lauf endet mit Code 1.

## Der Selbsttest des Kataloglesers

Der Katalog im Baum nennt neunzehn gueltige Faelle und keinen einzigen ungueltigen. Die
Haelfte des Lesers -- alles, was einen Fehler meldet -- liefe damit nie. Eine Tabelle im
Programm faehrt deshalb elf Kataloge, die der Bestand nicht hergibt, und prueft drei
Dinge: die Zahl der gelesenen Faelle, den erwarteten Fehler (und bei den gueltigen
Katalogen, dass **keiner** kommt) und -- ueber eine Zaehlmarke am Ende der
Fehlerartenliste -- dass jede der neun Arten von mindestens einem Fall ausgeloest wird.
Wer eine Art ergaenzt und den Fall vergisst, hat eine Meldung gebaut, die nie erscheint;
das faellt jetzt beim naechsten Lauf auf.

Dazu ein Fall auf den **Rohtext** der Textbloecke. Verloere der Leser fuehrende
Leerzeichen, faende sich kein Muster dieses Katalogs im Quelltext wieder, und *jeder*
Fall meldete die Musterzahl null -- der teuerste denkbare Fehler, weil er nach einem
Befund ueber den Kern aussaehe.

## Die Zielzahlen, je Profil

Nicht als Bedingung, sondern damit der naechste Lauf die Bewegung zuordnen kann.
Bezugsstand `bf0519b`.

| Profil | uebersetzende Ziele vorher | nachher | angemeldete Proben vorher | nachher |
|---|---|---|---|---|
| Arbeitsbereich, RelWithDebInfo | 18 | 19 | 14 | 14 |
| `werkzeuge/mutation` allein | -- (Verzeichnis gab es nicht) | 1 | -- | 0 |

Die Probenzahl bleibt, wo sie war: `mutationslauf` ist ein Ziel und kein `add_test`. Das
ist die Entscheidung des Projektmanagers vom 2026-09-05 im Rumpf dieses Pakets.

Der Belegstellenriegel hat sich mitbewegt und ist gruen: 42 auf 44 gelesene Bauquellen,
179 auf 181 Dateien im Zielbestand, 402 auf 423 Namen in ungelesenen Ordnern. Die Zahl
der Zitate bleibt bei 36, alle 36 aufgeloest -- meine drei Dateien tragen keinen Verweis
der geprueften Form und keine Zeilenangabe in eine fremde Datei.

Der ganze Arbeitsbereich: **14 von 14 Proben gruen.**

## Was der Katalog beim Anlegen noch nicht ist

Er deckt genau ein Modul ab, weil genau ein Modul bisher von Hand mutiert wurde. Die
vier Mutationen aus Paket 0088 gehoeren dazu, sobald jemand sie nachfaehrt; das ist ein
eigener Zuschnitt und keine Zeile hier. Was dieses Paket liefert, ist der Ort, an dem so
etwas ab jetzt bleibt.

## Worauf ich unsicher bin

**Der Alleinbau dieses Verzeichnisses meldet `No tests were found!!!` und Code 0.** Das
ist gewollt -- der Riegel dieses Verzeichnisses heisst `mutationslauf` und wird gerufen
statt angemeldet -- und steht im Manifest ausgeschrieben, damit ein Pruefer die Zeile
nicht fuer den Fehler vom 2026-09-04 haelt. Ich halte es trotzdem fuer die schwaechste
Stelle des Pakets: Ein Ziel, das niemand ruft, faellt nicht auf.

**Und der Befund darunter reicht weiter als dieses Paket:** Der Baulauf ruft `ctest`
ohne `--no-tests=error`. Ein Mitglied, dessen Proben allesamt verschwinden, meldet damit
`ergebnis: ok` -- dieselbe Fehlerklasse, die ich oben im eigenen Vorlauf gemessen habe.
Der Aufruf steht ausserhalb dieses Vorhabens; ich melde ihn und fasse ihn nicht an.
