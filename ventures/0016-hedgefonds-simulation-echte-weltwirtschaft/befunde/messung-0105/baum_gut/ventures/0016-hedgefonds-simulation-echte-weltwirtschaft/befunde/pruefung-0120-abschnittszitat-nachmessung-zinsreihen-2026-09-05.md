---
typ: pruefung
paket: 0120-abschnittszitat-nachmessung-zinsreihen
pruefer: daten-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Beide Bedingungen selbst nachgefahren -- ein selbst uebersetzter Riegel, zwei Laeufe auf demselben Baum, die sich in genau einer Zeile unterscheiden, plus der Uebersetzungsbericht des Tages.
befunde: 1
---

# Die Berichtigung traegt, und sie traegt aus dem richtigen Grund

Ich habe nicht die Meldung des Bauagenten nachgelesen, sondern die Messung selbst
gefahren: eigener Uebersetzungsvorgang des Riegels, eigener Vorher-Lauf auf einer
Vollkopie des Vorhabens, eigener Nachher-Lauf. Die Zahlen unten stammen aus meinen
Ausgabedateien, nicht aus dem Paketvermerk.

## Was ich gemessen habe

| Groesse | Wert |
|---|---|
| Baum | `38ab29f`; `git status --porcelain` ueber dem Vorhaben nennt allein den erzeugten Uebersetzungsbericht |
| Blob der Nachmessung im Arbeitsbaum | `3c097db4e1385217b506825d3bea88cf99499969` |
| Blob desselben Pfades bei `a6c55e0` (Vorher) | `214f9cd97ac0edf5f870e9f52a0f2935f4914c46` |
| Messgeraet | `werkzeuge/belegstellen/belegstellen_riegel.cpp` aus dem Arbeitsbaum, von mir uebersetzt mit `g++ -std=c++20 -O1 -fwrapv`, **ein** Binaerprogramm fuer alle vier Laeufe |
| Vorgabenwurzel | als zweites Argument gesetzt auf `specs/0016-hedgefonds-simulation-echte-weltwirtschaft` |

**Wie ich den Vorher-Zustand hergestellt habe, ohne eine Paketdatei anzufassen.** Ich habe
das Vorhaben vollstaendig nach `$TMPDIR` kopiert und allein in der Kopie die
Frontmatter-Zeile auf den Blob `214f9cd` zurueckgesetzt. Beide Laeufe der entscheidenden
Gegenueberstellung liefen auf **derselben** Kopie und unterscheiden sich in genau einer
Zeile; jede Zahlendifferenz gehoert damit dieser Zeile. Der Arbeitsbaum selbst blieb
unberuehrt -- ich habe den Blob der Kopie vor und nach jedem Ruecksetzen nachgerechnet, er
war jedes Mal exakt `214f9cd` bzw. `3c097db`.

## Bedingung 1 -- eigene Fundstelle weg, kein Rueckschritt

Vier Laeufe, davon die beiden mittleren die Gegenueberstellung auf der Kopie:

| | Vorher (Kopie, `214f9cd`) | Nachher (Kopie, `3c097db`) | Nachher (Arbeitsbaum) |
|---|---|---|---|
| Zitate der geprueften Form | 36 | 36 | 36 |
| davon aufgeloest | 35 | **36** | **36** |
| ohne auffindbare Gliederungszeile | **1** | **0** | **0** |
| Rueckgabewert | 1 | 0 | 0 |
| Bauquellen / Datendokumente / Zielbestand / ungelesene Namen | 44 / 13 / 184 / 433 | 44 / 13 / 184 / 433 | 44 / 13 / 184 / 433 |
| uebergangene Fundstellen | 47 | 47 | 47 |
| Bedingung 1 des Riegels | 5 Zeilenverweise, 0 mit Dateinamen daneben | ebenso | ebenso |

Der Vorher-Lauf meldete auf `stderr` genau eine Stelle, und es war die des Pakets:

```
1 Abschnittszitat(e) finden ihre Ueberschrift nicht:

  zitierend: daten/nachmessung-zinsreihen-2026-09-05.md:6
  nachgeschlagen in: daten/deckungsbefund-1997.md
```

Der Nachher-Lauf auf derselben Kopie schrieb nichts nach `stderr` (0 Bytes) und schloss
mit: „Kein Verweis zeigt mit einer Zeilennummer in eine fremde Datei, und jedes der 36
Abschnittszitate findet seine Zieldatei und darin seine Ueberschrift."

Der vollstaendige Zeilenvergleich der beiden `stdout`-Ausgaben derselben Kopie besteht aus
**einer** geaenderten Zaehlzeile (35 → 36 aufgeloest) und den drei angehaengten
Schlusszeilen. Die Liste der 47 uebergangenen Fundstellen ist zwischen den beiden Laeufen
zeichengleich. Die Berichtigung hat also kein Zitat verdeckt, keines neu erzeugt und
keines aus der Bewertung geschoben -- sie hat genau eines aufgeloest.

Damit ist beides erfuellt: Die Fundstelle verschwindet, und die Zahl der Zitate ohne
Gliederungszeile steigt nicht, sondern faellt von 1 auf 0.

## Bedingung 2 -- der Uebersetzungsbericht

`befunde/uebersetzung-2026-09-05.md` traegt `ergebnis: ok`. Der Arbeitsbereichs-`ctest`
steht auf `14/14`, „100% tests passed, 0 tests failed out of 14", und `Test #14:
belegstellen_riegel` ist `Passed`. Dieselbe Kopfzeile `ergebnis: ok` steht auch in der
eingecheckten Fassung bei `38ab29f`; die Aenderung im Arbeitsbaum betrifft ausschliesslich
die Uebersetzungs- und Testprotokolle unterhalb von Zeile 34, also den erzeugten Rumpf, und
nicht das Urteil. Ein neuer Fremdfehler ist nicht dazwischengekommen, der Vorbehalt greift
nicht.

## Was ich ausser den Zahlen gesucht habe

**Ob die Bedingung durch Nachgeben statt durch Berichtigen erfuellt wurde.** Drei Wege
waeren offen gewesen, alle drei sind ausgeschlossen:

- *Zieldatei passend gemacht.* `daten/deckungsbefund-1997.md` ist zuletzt in `74f5cb0`
  geaendert worden, lange vor diesem Paket. Die zitierte Gliederungszeile stand also schon
  da; sie wurde nicht fuer das Zitat erfunden.
- *Riegel gelockert.* Mein Vorher-Lauf benutzt den Riegelquelltext aus **dem heutigen
  Baum** und meldet die Fundstelle trotzdem. Ein Riegel, der diesen Fall noch findet, hat
  ihn nicht ausgenommen. Auch keine Ausnahmeliste ist beruehrt.
- *Mehr als die eine Zeile geaendert.* Der Unterschied zwischen `a6c55e0` und `07cc49b` an
  dieser Datei ist genau eine Zeile des Frontmatters, sonst nichts.

**Ob die Berichtigung inhaltlich auf den richtigen Abschnitt zeigt** -- die Frage, die eine
reine Riegelmessung nicht beantwortet. Sie tut es: Die Nachmessung widerlegt fuer Reihe 9
die Aussage „DEU, Reihe vorhanden? nein, 0 Stuetzstellen"; diese Tabellenzeile steht in
`deckungsbefund-1997.md:169` und damit innerhalb des Abschnitts, dessen Gliederungszeile
bei Zeile 138 beginnt und den die berichtigte Zeile 6 jetzt nennt. Der zuvor zitierte
Wortlaut war der erste Satz des Fliesstexts desselben Abschnitts -- gemeint war also von
Anfang an dieser Abschnitt, und die Berichtigung aendert keine Aussage.

**Ob die Schreibweise die Regel des Riegels einhaelt.** Die Zeile nennt den Titel ohne die
Auszeichnungssternchen des Originals. Der Riegel nimmt den Wortlaut ausdruecklich „bis auf
Umlautumschrift, Auszeichnung und Leerraum" -- er loest das Zitat auf, also ist es
eingehalten. Ein Geschmacksbefund waere das ohnehin nicht.

**Wonach ich noch gesucht und nichts gefunden habe:** ein zweites, gleichgeformtes
Abschnittszitat in derselben Datei, das derselbe Fehler treffen wuerde (die Nachmessung
fuehrt nur dieses eine); ein deckungsgleiches Paket, das denselben Gegenstand ein zweites
Mal einplant (`0125-nachmessung-zinsreihen-zitiert-keine-gliederungszeile` steht bereits
auf `zurueckgezogen`).

**Was ich nicht geprueft habe:** die 47 uebergangenen Fundstellen. Sie sind der
ausgeschriebene blinde Fleck des Riegels, in allen Laeufen gleich, und liegen ausserhalb
dieses Pakets.

## Ein Befund ausserhalb des Pakets: die Reihenfolge des Berichts haengt am Dateisystem

Das Urteil beruehrt es nicht, aber es ist mir bei genau dieser Pruefung im Weg gestanden,
und deshalb steht es hier statt nur im Logbuch.

Mein Nachher-Lauf auf dem **Arbeitsbaum** und mein Nachher-Lauf auf der **Kopie** nennen
dieselben sieben Kennzahlen und dieselben 47 uebergangenen Fundstellen -- aber in
verschiedener Reihenfolge. Der Grund steht im Quelltext: Die Dateisammlung laeuft ueber
`fs::directory_iterator` mit eigener Arbeitsliste, und nirgends im Programm wird sortiert
(`std::sort` kommt nicht vor). Die Ausgabereihenfolge ist damit die Auflistungsreihenfolge
des jeweiligen Dateisystems -- auf derselben Kopie zweimal gleich, zwischen zwei Baeumen
verschieden.

Die Folge ist nicht falsch, sondern unvergleichbar: Ein Zeilenvergleich zweier Riegellaeufe
ist nur brauchbar, solange beide auf demselben Dateisystem laufen. Genau das verlangt
Bedingung 1 dieses Pakets aber der Sache nach von jedem Pruefer, der -- wie ich -- den
Vorher-Zustand ausserhalb des Arbeitsbaums herstellt, statt eine fremde Datei
zurueckzuschreiben. Ich habe es umgangen, indem ich beide Laeufe auf dieselbe Kopie legte;
der naechste Pruefer wird denselben Umweg wieder erfinden muessen. Vorschlag
`0130-belegstellenriegel-berichtsreihenfolge-festnageln` liegt unter `aufgaben/`.
