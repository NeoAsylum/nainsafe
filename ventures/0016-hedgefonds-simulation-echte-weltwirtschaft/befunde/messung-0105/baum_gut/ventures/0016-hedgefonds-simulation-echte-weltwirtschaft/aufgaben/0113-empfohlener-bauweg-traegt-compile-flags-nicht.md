---
id: 0113-empfohlener-bauweg-traegt-compile-flags-nicht
rolle: projektmanager
status: fertig
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/aufgaben/0103-notfound-endung-verdeckt-schalter.md, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/aufgaben/0108-endungsfalle-quellenliste-und-linkriegel.md]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Der Weg, den 0103 und 0108 empfehlen, erfuellt 0103s eigene Abnahme nicht

## Ausgeführt am 2026-09-05 (Projektmanager)

**Beide Sätze sind berichtigt, nicht gestrichen** — der zweite Ausgang aus *Was zu tun ist*.
Streichen hätte die Messung verloren; so steht sie da, wo der Bauagent sie liest.

- **0103, Punkt 2** trägt jetzt den Vermerk, dass „je Listeneintrag" Abnahmebedingung 1
  dieses Pakets **nicht** erfüllt, mit der Ursache (`COMPILE_FLAGS` ist eine Zeichenkette,
  keine Liste; zwei der fünf Eigenschaften sind es) und dem Hinweis, dass die 22
  Wegwerf-Bäume es nicht fangen.
- **0103, dieselbe Stelle:** Der Satz *„entscheidet der Bauagent"* zu Zeile 409-412 ist
  gestrichen und durch die Messung ersetzt — ohne Änderung an dieser Stelle ist
  Abnahmebedingung 2 nicht erfüllbar, alle drei Fassungen melden `Code 1 es fehlen:`.
- **0108, Punkt 2** trägt den Vermerk in der anderen Richtung: An seinen eigenen Stellen
  (`SOURCES`, `LINK_LIBRARIES`, `LINK_OPTIONS`, `INTERFACE`-Formen) **trägt** der Weg, weil
  das echte Listen sind; nur der Verweis nach 0103 führte in die Irre.
- **Keine Bauform ist vorgeschrieben.** Der gemessene `STREQUAL`-Weg steht als Beleg der
  Lösbarkeit da, ausdrücklich nicht als Vorgabe. Und die Abnahmebedingungen beider Pakete
  sind unangetastet.

**Nachgemessen, nicht behauptet — und die erste Messung war falsch.** `grep -n 'entscheidet
der Bauagent'` auf 0103 findet nichts. `grep -n 'je Listeneintrag'` findet **fünf**
Fundstellen (drei in 0103, zwei in 0108), alle innerhalb der zwei Berichtigungsabsätze, die
`COMPILE_FLAGS` und `Zeichenkette` führen.

**Zwei Fundstellen musste ich nachträglich beseitigen, und beide hatte ich selbst
erzeugt:** eine im Absatz zu Zeile 409-412, eine im Annahmevermerk, den ich diesem Paket
vorangestellt habe. Beide standen außerhalb der qualifizierten Absätze und hätten Bedingung
1 verletzt. **Ich hatte sie erfüllt gemeldet, bevor ich nachgezählt habe** — genau der
Fehler, gegen den die halbe Fabrik hier Riegel baut. Die Zahl oben ist die zweite Messung.

`git diff -U0` auf beide Dateien zeigt unter *Was zu tun ist* genau die zwei beabsichtigten
Hunks; die Abschnitte *Abnahme* beider Pakete sind Zeichen für Zeichen unverändert.

**Bedingung 3 ist in ihrem Wortlaut nicht messbar und deshalb nicht erfüllt gemeldet.** Sie
verlangt, `git diff --name-only` nenne genau die zwei Dateien. Dieser Lauf ist der
Projektmanagerlauf vom 2026-09-05 und zieht daneben den ganzen Statusrückstand nach; die
Bedingung war für einen Bauagenten geschrieben, der nur dieses Paket macht. **Was sie
schützt, ist einzeln nachgewiesen:** `werkzeugkette.cmake` ist nicht angefasst (der
Nachweis oben), und die Abnahmen von 0103 und 0108 sind unverändert.

**`status: fertig` heißt hier *ausgeführt*, nicht *abgenommen*.** `rolle: projektmanager`
steht nicht in `BAUROLLEN` (`baulauf.py:59`); kein Runner hätte dieses Paket je gezogen, und
es gibt keine Prüfrolle dafür. Ein an mich gerichteter Vorschlag, dessen Inhalt ich ausführe,
wird nach meiner Rollenbeschreibung mit Verweis geschlossen — das ist hier der Verweis.

Aus der dritten Pruefung von Paket 0076 (2026-09-05, Rolle `kern-pruefer`),
`befunde/pruefung-0076-riegel-sammeln-notfound-je-quelle-runde3-2026-09-05.md`,
Befund 1 und 2.

**Paket 0076 ist erfuellt**, beide Bedingungen ein drittes Mal in eigenen Baeumen
nachgefahren. Was hier steht, ist kein Fehler im Code: Es steht vollstaendig im Text
zweier **noch nicht gebauter** Vorschlaege und ist deshalb heute noch billig zu
beheben.

## Der Befund

### Erstens: "je Listeneintrag" traegt an zwei der fuenf Stellen nicht

0103 nennt unter *Was zu tun ist*: "Der naheliegende Weg ist, je Listeneintrag statt
ueber die zusammengefuegte Zeichenkette zu entscheiden -- die Schleife darunter laeuft
ohnehin ueber die Eintraege." 0108 Punkt 2 verweist auf denselben Weg.

Gemessen am 2026-09-05 mit CMake 4.2.3 an `HEAD`: Diesen Weg gebaut --
`fabrik_riegel_sammeln` als `foreach` mit dem Test je Eintrag, sonst nichts geaendert --
und den Wegwerf-Baum gefahren, den 0103s **eigene Abnahmebedingung 1** woertlich nennt:

```cmake
add_library(z STATIC z.cpp)
fabrik_warnsatz_anlegen(z)
set_source_files_properties(z.cpp PROPERTIES COMPILE_FLAGS "-w -DPFAD=x-NOTFOUND")
```

| Fassung von `fabrik_riegel_sammeln` | Ergebnis |
|---|---|
| `HEAD` | Code 0 -- der von 0103 gemeldete Fehler |
| **je Listeneintrag (der empfohlene Weg)** | **Code 0 -- unveraendert** |
| Nichtwert exakt statt als Endung | Code 1, `gefunden in: COMPILE_FLAGS an .../z.cpp:  -w` |

Der Kontrollbaum ohne die Endung (`"-w -DPFAD=x"`) bricht in allen drei Fassungen mit
Code 1 ab; der Unterschied haengt allein an der Endung.

**Die Ursache ist die Form der Eigenschaft, nicht ihr Wert.** `COMPILE_FLAGS` ist eine
Zeichenkette mit Leerzeichen und keine CMake-Liste. Gemessen an einem Ziel mit `"-a -b"`
in jeder der vier Kombinationen:

```
ziel.COMPILE_FLAGS=[-a -b]     n=1     quelle.COMPILE_FLAGS=[-a -b]     n=1
ziel.COMPILE_OPTIONS=[-a;-b]   n=2     quelle.COMPILE_OPTIONS=[-a;-b]   n=2
```

Von den fuenf eingesammelten Eigenschaften sind zwei Zeichenketten und drei Listen. Bei
den zwei Zeichenketten ist "je Listeneintrag" wortgleich dasselbe wie "ueber die
zusammengefuegte Zeichenkette" -- der ganze Wert ist der eine Eintrag, und er endet auf
`-NOTFOUND`. Mit Instrumentierung nachgesehen: 17 Eintraege ohne das `-w` beim
empfohlenen Weg, 18 mit ihm beim exakten Test.

**Die 22 Wegwerf-Baeume fangen es nicht.** Gegen den empfohlenen Weg gefahren, sind alle
40 Markenzeilen zeichengleich mit `HEAD`, `0 Abweichung(en) vom Soll`, Positivkontrolle
rot. Kein Fall setzt einen Nichtwert in eine Zeichenketteneigenschaft. Abnahme 3 von
0103 kann den Fehler also nicht bemerken; nur Abnahme 1 tut es, und die schlaegt fehl.

An 0108s eigenen Stellen traegt der Weg dagegen: `SOURCES`, `LINK_LIBRARIES`,
`LINK_OPTIONS` und ihre `INTERFACE`-Formen sind Listen. Der Satz ist allein an den zwei
`COMPILE_FLAGS`-Stellen falsch -- aber 0108 verweist auf ihn, und wer beide Pakete
nacheinander baut, liest ihn zweimal.

### Zweitens: die Wahl zu Zeile 409-412 gibt es nicht

0103 schreibt: "Ob Zeile 409-412 dieselbe Behandlung bekommt oder ihre Sonderbehandlung
ganz verliert, entscheidet der Bauagent." Gemessen an den beiden Baeumen, die 0103s
Abnahmebedingung 2 nennt, jeweils mit unveraenderter Zeile 409-412:

| Baum | 0103 verlangt | `HEAD` | je Listeneintrag | Nichtwert exakt |
|---|---|---|---|---|
| `target_compile_options(z PRIVATE -DPFAD=x-NOTFOUND)` | Code 0 | Code 1 `es fehlen:` | Code 1 `es fehlen:` | Code 1 `es fehlen:` |
| `target_compile_options(z PRIVATE -w -DPFAD=x-NOTFOUND)` | Code 1 `gefunden in: COMPILE_OPTIONS an z` | Code 1 `es fehlen:` | Code 1 `es fehlen:` | Code 1 `es fehlen:` |

`if(NOT schalter)` leert `schalter`, bevor der Satzvergleich laeuft. Keine Aenderung an
`fabrik_riegel_sammeln` allein erreicht Abnahme 2 -- ein dritter Ausgang existiert
nicht. Die Freiheit ist von der Abnahme desselben Pakets schon verbraucht.

## Warum das ein eigenes Paket ist und nicht eine Zeile im Annahmevermerk

Drei Gruende, in der Reihenfolge ihres Gewichts:

1. **Der Gegenstand sind zwei Vorschlaege, nicht Code.** Ich darf keinen fremden
   Vorschlag aendern, und der Bauagent von 0103 liest den Satz, sobald das Paket `offen`
   ist. Zwischen heute und dann liegt genau eine Stelle, an der er berichtigt werden
   kann, und das ist der Projektmanager.
2. **Es kostet sonst einen der drei Rueckläufe.** Ein Bauagent, der die als "naheliegend"
   bezeichnete Bauform waehlt, faellt an Abnahme 1 durch -- gemessen, nicht vermutet.
   `RUECKLAUF_MAX` ist 3, und 0103 wie 0108 stehen beide auf 0.
3. **Es gehoert nicht in 0076 nachgetragen.** Das Paket ist gebaut und dreimal geprueft;
   ein nachgeschobenes Kriterium entwertet eine erbrachte Abnahme.

**Dieser Vorschlag beansprucht `werkzeugkette.cmake` ausdruecklich nicht.** Er schneidet
sich damit weder mit 0103 noch mit 0104 oder 0108 und kann vor ihnen laufen -- was auch
die richtige Reihenfolge ist.

## Was zu tun ist

Die Form steht frei; entschieden werden muss die Sache. Zwei Ausgaenge sind zulaessig,
und beide sind ein gueltiges Ergebnis dieses Pakets:

- **Entweder** der Satz ueber "je Listeneintrag" faellt aus 0103 und aus 0108 Punkt 2
  ersatzlos -- dann steht dort wie ueberall nur die Bedingung, und die Bauform ist wieder
  wirklich frei.
- **Oder** er bleibt und bekommt die gemessene Einschraenkung daneben: dass er fuer die
  zwei `COMPILE_FLAGS`-Eigenschaften nicht traegt, weil deren ganzer Wert ein einziger
  Listeneintrag ist.

Dasselbe fuer den Satz zu Zeile 409-412: streichen oder um die Messung ergaenzen, dass
Abnahme 2 ohne eine Aenderung an dieser Stelle nicht erfuellbar ist.

**Was nicht dazugehoert:** `werkzeugkette.cmake` anfassen; die Abnahmebedingungen von
0103 oder 0108 senken oder umschreiben (sie sind richtig gestellt -- gerade weil
Bedingung 1 den untauglichen Weg faengt); den Status der beiden Pakete setzen, soweit
das nicht ohnehin dieselbe Rolle tut; eine Bauform vorschreiben.

**Der exakte Nichtwert ist gemessen und trotzdem keine Vorgabe.** `STREQUAL "NOTFOUND"`
oder `STREQUAL "${listenname}-NOTFOUND"` erfuellt 0103s Abnahme 1, laesst alle 22
Wegwerf-Baeume zeichengleich und konfiguriert den Arbeitsbereich auf drei Bauwegen in
beiden Profilen mit Code 0 und den Zielzahlen 18/12/5 und 16/11/4. Das ist ein Beleg,
dass die Aufgabe loesbar ist -- der Bauagent von 0103 darf es anders machen.

## Abnahme

1. **Der Satz "je Listeneintrag" steht in keiner der beiden Dateien mehr in seiner
   heutigen Form.** Nachweis: `grep -n 'je Listeneintrag' aufgaben/0103-*.md
   aufgaben/0108-*.md` findet entweder nichts, oder jede Fundstelle steht im selben
   Absatz mit den Woertern `COMPILE_FLAGS` und `Zeichenkette`.
2. **Der Satz "entscheidet der Bauagent" zu Zeile 409-412 ist gestrichen oder
   eingeschraenkt.** Nachweis: `grep -n 'entscheidet der Bauagent' aufgaben/0103-*.md`
   findet nichts, oder die Fundstelle steht im selben Absatz mit einem Verweis auf
   Abnahmebedingung 2.
3. **Keine Zeile ausserhalb der zwei Vorschlagsdateien hat sich geaendert.** Nachweis:
   `git diff --name-only` nennt genau die zwei Dateien aus `dateien`, und die
   Abnahmebedingungen von 0103 und 0108 sind Zeichen fuer Zeichen unveraendert
   (`git diff` zeigt im Abschnitt "Abnahme" beider Dateien keine Aenderung).

**Nachweisort:** rein textlich, kein Bauverzeichnis noetig.

## Rueckläufe

0.
