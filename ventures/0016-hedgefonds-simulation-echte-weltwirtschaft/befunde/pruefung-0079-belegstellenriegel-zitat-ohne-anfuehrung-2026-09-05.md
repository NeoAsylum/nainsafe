---
typ: pruefung
paket: 0079-belegstellenriegel-zitat-ohne-anfuehrung
pruefer: test-pruefer
datum: 2026-09-05
urteil: zurueck
kriterium_geprueft: Vier der fuenf Bedingungen sind gemessen erfuellt -- die vier Stellen aus 0047 gehen aus wie verlangt, beide Ueberschriften werden ueber eine Korpuskopie rot, der Riegel ist gruen (14/14 im Bauweg des Vorhabens), und zehn Mutanten sterben an je einem eigenen Fall. Die fuenfte ist nicht erfuellt: die uebergangenen Fundstellen fallen nicht um zwei (10), sie steigen auf 58 -- und sie koennen auf diesem Korpus in keiner Fassung fallen.
befunde: 4
---

# Pruefung 0079 -- die Ueberschrift ohne Anfuehrung

Geprueft wurde der Arbeitsbaum; `git status` meldet `werkzeuge/` unveraendert, der Stand
an der Paketdatei ist also `HEAD` (`fb586db`).

**Die Arbeit dieses Pakets liegt in drei Commits, nicht in einem.** `fb586db` traegt nur
das letzte Drittel; die Klassifizierung selbst (`namensart`, `fuehrt_gliederungsziffer`,
`ZITATFAELLE`) steht in `a4850f7` unter dem Betreff des Datenbauerpakets 0078, die
Namensabgrenzung (`name_ohne_anfuehrung`, `ist_namensende`, `ist_namensanfang`) in
`61fa55b` unter dem des Kernbauerpakets 0076. Wer `git show fb586db` liest, sieht ein
Drittel und haelt es fuer das Ganze. Vorher-Stand des Quelltextes ist deshalb `dffb251`
(Stand nach 0073), Stand nach 0067 ist `f27dd39`; beide verhalten sich auf beiden unten
gemessenen Bestaenden Zeichen fuer Zeichen gleich.

## Aufbau

Fuenfzehn Fassungen in vier Wegwerf-Projekten unter `$TMPDIR`, je mit `add_executable`
und `add_test`, gestartet ueber `ctest -V`. Uebersetzt mit `g++ 15.2.0`, `-std=c++20`.
Der Korpus wurde nie im Repo angefasst: Wo eine Belegstelle kaputtgehen musste, lag eine
Kopie des Vorhabens (`git archive HEAD | tar -x`) daneben, und die Vorgabenwurzel zeigte
weiter auf die echte, unveraenderte `specs/`.

Vier Bestaende, und die Trennung ist noetig, weil zwei fremde Pakete (`0076`, `0078`)
zwischen Vorher-Stand und Auslieferung in `daten/reihen.toml` geschrieben haben:

| Fassung | Korpus `HEAD` | Korpus `489aafb` |
|---|---|---|
| `fb586db` (ausgeliefert) | 38 Zitate, 38 aufgeloest, **58** uebergangen, Code 0 | 35 / 35 / 53, Code 0 |
| `dffb251` (vor 0079) | 24 / 24 / **10**, Code 0 | 24 / 24 / **8**, Code 0 |
| `f27dd39` (Stand 0067) | 24 / 24 / **10**, Code 0 | 24 / 24 / **8**, Code 0 |

Die Differenz von zwei zwischen den beiden Korpusspalten ist dieses Paket selbst: Der
neue Kopfkommentar traegt zwei mit Sternchen ausgezeichnete Aufzaehlungspunkte, die der
Riegel in seinem eigenen Quelltext als Fundstellen ohne Dokumentnamen wiederfindet. Sie
zaehlen unter **jeder** Fassung mit und heben deshalb beide Seiten der Rechnung.

## Die fuenf Bedingungen der Abnahme, einzeln

**1. Der Riegel entscheidet je Fundstelle zwischen Nummer und Ueberschrift.** Erfuellt.
`namensart` wird je Fundstelle gerufen und gibt fuenf Arten zurueck; die Entscheidung
haengt an keiner Liste, sondern an drei benannten Eigenschaften (Wortpraefix, Punkt hinter
der Ziffer, Laenge des Kopfworts). Gegengeprueft am Diff `dffb251..HEAD`: keine der
bestehenden Listen und keine Schwelle wurde angefasst -- `SCHLUESSEL`, `KLAMMERN`,
`ENDUNGEN`, `GESPERRTE_ORDNER`, `UEBERSCHRIFT_HOECHSTENS`, `ZIFFERN_MINDESTENS` stehen
unveraendert, `NAMENSFAELLE` weiter bei acht Faellen, alle gruen.

**2. Der Kopfkommentar begruendet an einer benannten Eigenschaft.** Erfuellt. Genannt ist
der Punkt hinter der Gliederungsziffer, und er traegt beide Haelften der Entscheidung im
Quelltext: `ist_wortpraefix` laesst ihn nicht als Wortgrenze gelten,
`fuehrt_gliederungsziffer` nimmt ihn als Nachweis, dass die Datei nummeriert. Beide
Haelften sterben an je einem eigenen Mutanten (Tafel unten).

**3. Die vier Stellen aus Paket 0047.** Erfuellt, mit Rotnachweis fuer die zweite Gruppe.
Die zwei Nummern stehen uebergangen und namentlich in der Aufzaehlung -- `reihen.toml`
Feld `beleg` unter `[zaehlung.lizenz]` (*Gliederungsziffer statt Ueberschrift: 5*) und
Feld `bestritten_durch` (*: 3*). Die zwei Ueberschriften stehen dort **nicht**; sie sind
Zitate und aufgeloest, beide aus dem Feld `schnitt_2_offen`.

Der Rotnachweis, gefuehrt auf der Kopie und je einzeln zurueckgenommen:

* Ueberschrift `Reihe 1 — BIP` in `daten/lizenzbefund-reihen.md` zu `Reihe 1a — BIP`
  umbenannt -> Code 1, `1 Abschnittszitat(e) finden ihre Ueberschrift nicht`, zitierend
  `daten/reihen.toml` Feld `schnitt_2_offen`, gesucht `Reihe 1`.
* Ueberschrift `2b und 2c — ...` zu `2b, 2c und 2d — ...` umbenannt -> dieselbe Meldung,
  gesucht `2b und 2c`.

Beide Male blieb die Zahl der uebergangenen Fundstellen bei 58: Die umbenannte
Ueberschrift **faellt nicht in die uebergangenen zurueck**, auch die nicht, deren Name mit
einer Ziffer beginnt. Das ist die Zusicherung, an der das Paket haengt, und sie haelt.

**4. Gruen auf dem geltenden Korpus.** Erfuellt. Code 0 im Alleinlauf; im Bauweg des
Vorhabens (frische Konfiguration ausserhalb des Repos, `werkzeugkette.cmake` mit
`-Werror` und `-fsanitize=undefined,address`) `100% tests passed, 0 tests failed out of
14`, darunter `belegstellen_riegel`.

**5. Die uebergangenen Fundstellen fallen um genau zwei.** **Nicht erfuellt.** Sie fallen
nicht, sie steigen -- von 10 auf 58 auf dem geltenden Korpus, von 8 auf 53 auf dem
Vorher-Korpus. Siehe Befund 1.

## Befund 1 -- die fuenfte Bedingung ist nicht erfuellt und nicht erfuellbar

**Wie man es nachstellt.** Die Fassung `f27dd39` gegen denselben Baum richten wie die
ausgelieferte. Sie meldet 8 uebergangene Fundstellen (Korpus `489aafb`) bzw. 10 (Korpus
`HEAD`), die ausgelieferte 53 bzw. 58.

**Warum keine Fassung dieses Pakets die Zahl haette senken koennen** -- gemessen, nicht
uebernommen: Ich habe die acht uebergangenen Fundstellen des Standes von 0067 einzeln
gelesen. Sechs tragen den Grund *kein Dokumentname im Absatz*, eine *naechstes Ziel ist
eine Netzadresse*, eine *Ziel ausserhalb des Bestands*. **Keine einzige traegt die Form
ohne Anfuehrung.** Ein Fallen der Zahl setzte voraus, dass dieses Paket bestehende
uebergangene Fundstellen aufloest; es kann keine von ihnen beruehren. Alle acht stehen
denn auch unveraendert in den 58 wieder.

Die Bedingung ist damit **falsch gestellt** und nicht verfehlt: Sie unterstellt, die vier
Stellen aus 0047 seien im Stand von 0067 bereits als uebergangen gezaehlt worden, und
zwei von ihnen fielen durch das Aufloesen heraus. Gezaehlt wurden sie dort nicht -- ohne
Anfuehrung fand der Riegel sie ueberhaupt nicht, und was er nicht findet, zaehlt er auch
nicht als uebergangen. Wer die zwei Nummern uebergeht und namentlich nennt, wie dieselbe
Abnahme es im Satz davor verlangt, erhoeht die Zahl zwangslaeufig.

**Das ist eine Sache des Projektmanagers, nicht des Bauagenten.** Ich senke kein
Kriterium und stelle keines um; das Paket kann so aber nicht auf `geprueft` gehen. Was
neu zu schneiden waere: eine Zahl, die den Zuwachs misst statt eines Rueckgangs -- etwa
*keine der acht uebergangenen Fundstellen aus 0067 verschwindet, und jede neu
hinzukommende traegt einen der drei neuen Gruende*. Beides ist heute erfuellt und
nachgemessen.

**Nicht gruen gemacht worden.** Der Riegel ist fuer diese Zahl nicht abgeschwaecht: keine
Schwelle gesenkt, keine Zusicherung entfernt, kein Fall uebersprungen (Bedingung 1 oben),
und die 24 Zitate der alten Form stehen unveraendert in den 38.

## Befund 2 -- eine richtige Belegstelle am Zeilenende wird rot

Die neue Form liest den Namen bis zum naechsten Satzzeichen, und gesucht wird **je
Absatz**. Steht die Belegstelle am Zeilenende ohne Satzzeichen, laeuft der Name in die
naechste Zeile weiter und findet sich nirgends wieder -- der Riegel wird rot an einer
Stelle, an der nichts kaputt ist. Genau davor warnt der Rumpf des Arbeitspakets; im
Kopfkommentar steht diese Grenze nicht unter den drei ausgeschriebenen.

**Wie man ihn erzeugt.** In eine gelesene Datei des Vorhabens -- `rueckstand.md` genuegt
-- diese zwei Zeilen schreiben, deren Zitat richtig ist und deren Ziel die Ueberschrift
wirklich traegt:

```
Der Wortlaut steht in `daten/lizenzbefund-reihen.md`, Abschnitt Reihe 1
und wird dort nicht bestritten.
```

Der Riegel meldet daraufhin Code 1 und `gesuchte Ueberschrift: Reihe 1 und wird dort
nicht bestritten`. Auf einer Kopie ausgefuehrt und zurueckgenommen.

Dass die Form vorkommt, ist keine Erfindung: Richtet man den ausgelieferten Riegel auf
die Wurzel des Repos, kommen gegenueber der Vorfassung fuenf Befunde dazu, und **alle
fuenf** sind von dieser Art -- Zitate in `aufgaben/`-Dateien, deren Name ueber den
Zeilenumbruch in die naechste Zeile laeuft. Im Pruefweg des Vorhabens liegen sie heute
ausserhalb, weil `aufgaben/` dort ausgenommen ist; in `daten/` oder `rueckstand.md` waere
dieselbe Zeile ein roter Lauf. Vorschlag 0105 daneben.

## Befund 3 -- zwei Regeln ohne eigenen Anker

Die neun Faelle in `ZITATFAELLE` sind echt: Sie tragen Wortlaute des Bestands, ihre
Herkunftsangaben liessen sich einzeln nachschlagen (`schnitt_2_offen`, `beleg` unter
`[zaehlung.lizenz]`, `bestritten_durch`, `einheitenbefund-pwt-baci.md`, `rueckstand.md`),
und keiner ist aus dem aktuellen Lauf uebernommen -- vier erwarten etwas anderes als
"aufgeloest", zwei ausdruecklich einen Befund. Zehn Mutanten sterben an ihnen. Zwei
Wirkungsketten haelt aber kein Fall:

**3a. Der Aufloesungsschritt selbst.** Ersetzt man in `pruefe_zitate` im Zweig ohne
Anfuehrung die Zuweisung `steht_da = art == Namensart::Ueberschrift` durch `steht_da =
true`, bleibt der Selbsttest vollstaendig gruen (17 von 17) **und** der Riegel meldet auf
einer Kopie mit umbenannter Ueberschrift `Reihe 1a` weiter Code 0. Der Mutant ueberlebt
alles. Die neun Faelle pruefen `namensart` und `name_ohne_anfuehrung` einzeln, nicht die
Stelle, an der aus einer Art ein Befund wird. Derselbe Mutant im Zweig **mit** Anfuehrung
ueberlebt ebenfalls -- die Luecke ist also nicht mit diesem Paket entstanden, sondern mit
0067; dieses Paket verdoppelt sie. Vorschlag 0106 daneben.

**3b. Die Regel *einzelnes Zeichen*.** Sie hat als einzige der fuenf Arten keinen Fall in
`ZITATFAELLE`. Schaltet man sie ab, wird der Riegel rot -- aber erst am Bestand, an einer
einzigen Stelle in `rueckstand.md`. Ein Bestand ist ein wandernder Anker: Wird dieser eine
Satz umformuliert, ist die Regel unbemerkt ungeprueft. Das ist die kleinere Haelfte von
Vorschlag 0106.

## Befund 4 -- der Wortlaut im Nachweis ist auf dem ausgelieferten Stand nicht reproduzierbar

`befunde/messung-0079/nachweis.md` gibt den Testlauf im Wortlaut wieder und nennt darin
**56** uebergangene Fundstellen. Der ausgelieferte Stand meldet **58** -- zweimal
gemessen, im Repo und auf der Kopie.

**Wie man die Differenz nachweist:** In einer Kopie die zwei Aufzaehlungspunkte wieder
herausnehmen, die dieses Paket dem Kopfkommentar hinzugefuegt hat (*Gliederungsziffer
statt Ueberschrift* und *einzelnes Zeichen statt Ueberschrift*). Der unveraenderte Riegel
meldet dann genau 56. Die Messung wurde also gemacht, bevor der Kopfkommentar fertig war,
und nicht wiederholt, nachdem er es war -- der Riegel liest seinen eigenen Quelltext mit,
und zwei mit Sternchen ausgezeichnete Zeilen darin sind zwei neue Fundstellen.

Sachlich aendert das nichts: Die Zahl 8 fuer den Stand von 0067 stimmt auf dem damaligen
Korpus, und die Differenz +48 ist in beiden Rechnungen dieselbe (8 -> 56 wie 10 -> 58).
Falsch ist nur, was als Wortlaut eines Laufs dasteht. Fuer den naechsten Lauf auf dieser
Datei gilt: nach der letzten Zeile des Kopfkommentars noch einmal messen.

## Wonach ich sonst gesucht und was ich nicht gefunden habe

* **Abgeschwaechte Faelle.** Keine. Diff `dffb251..HEAD` beruehrt keinen bestehenden Fall
  ausser einer Maskierung: Im siebten `NAMENSFALL` steht das `A` von "Abschnitt" jetzt als
  `\101`, damit der Fall nicht seine eigene Fundstelle wird. Zur Laufzeit ist der String
  unveraendert (Oktalfolge, gefolgt von `b`), der Selbsttest meldet weiter acht Faelle. Die
  Stelle waere ohnehin nur eine *uebergangene* geworden, kein verdecktes Rot.
* **Verlorene Zitate der alten Form.** Keine: 24 vorher, 38 - 14 = 24 nachher, auf beiden
  Bestaenden.
* **Ein zu weiter Nachlass.** Der Zusatz, bei der Ziffer auch die zitierende Datei zu
  fragen, haengt an genau **einer** Stelle des Bestands: Schaltet man ihn ab (und den
  Selbsttest, damit der Lauf den Bestand erreicht), faellt eine einzige Fundstelle heraus
  und wird ein Befund -- `daten/einheitenbefund-pwt-baci.md`, Verweis auf einen eigenen
  Abschnitt. Der Nachlass ist damit weder unnoetig (er traegt etwas) noch breit (er
  verdeckt nichts anderes).
* **Falsche Aufloesungen.** Auf dem Repobaum loesen unter der neuen Form 12 Zitate mehr
  auf als unter der alten; die fuenf zusaetzlichen Befunde sind die aus Befund 2. Ein
  Zitat, das faelschlich als aufgeloest durchginge, habe ich nicht gefunden.
* **Die Dateiliste.** `fb586db` fasst ausser der Paketdatei nur das eigene Logbuch, die
  Aufgabendatei und den Nachweis an. Kein fremdes Gebiet.

## Die Mutantentafel

Alle gegen den ausgelieferten Stand, je eine Textersetzung auf einer Kopie mit
Fehlerbremse. M0 ist die Kontrolle ohne Eingriff.

| Mutant | Eingriff | Ausgang |
|---|---|---|
| M0 | keiner | gruen, 38/38/58 |
| M1 | die zitierende Datei bei der Ziffer nicht mehr fragen | Zitatfall 7, Code 2 |
| M2 | der Punkt gilt als Wortgrenze | Zitatfall 5, Code 2 |
| M3 | `fuehrt_gliederungsziffer` immer wahr | Zitatfall 4, Code 2 |
| M4 | `fuehrt_gliederungsziffer` immer falsch | Zitatfaelle 6 und 7, Code 2 |
| M5 | ein Name darf klein anfangen | Zitatfall 9, Code 2 |
| M6 | das Komma beendet den Namen nicht mehr | Zitatfaelle 1, 2, 3, 4, 6, Code 2 |
| M7 | Zieldatei ohne Ueberschrift nicht mehr erkannt | Zitatfall 8, Code 2 |
| M8 | die Art *einzelnes Zeichen* entfaellt | gruener Selbsttest, **rot erst am Bestand** |
| M9 | `name_ohne_anfuehrung` findet nichts mehr | 8 von 9 Zitatfaellen, Code 2 |
| M10 | im Zweig ohne Anfuehrung `steht_da = true` | **ueberlebt alles, auch bei kaputter Ueberschrift** |
| M11 | im Zweig mit Anfuehrung `steht_da = true` | **ueberlebt** (Luecke aus 0067) |

Jede Zusicherung der neuen Faelle ist einmal rot gewesen; kein Fall ist Zierde. Die zwei
Ueberlebenden stehen in Befund 3.
