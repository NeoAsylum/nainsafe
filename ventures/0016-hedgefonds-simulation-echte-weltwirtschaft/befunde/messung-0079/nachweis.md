# Messung zu Paket 0079 -- die Ueberschrift ohne Anfuehrung

Datum: 2026-09-05. Rolle: testentwickler. Geaenderte Datei: genau eine,
`werkzeuge/belegstellen/belegstellen_riegel.cpp`.

**Vorher-Stand.** `HEAD` beim Beginn dieses Laufs: `489aafb`. Das ist der Stand nach
0073, wie das Arbeitspaket es verlangt -- nicht der Stand vom Tag der Zuschneidung.

## Was gemessen wurde -- Uebersetzer und Testlauf im Wortlaut

Gebaut mit dem Alleinbauweg (`cmake -S werkzeuge/belegstellen -B <bau>`), also mit
`werkzeugkette.cmake` und damit mit `-std=c++20 -fwrapv -Werror` und
`-fsanitize=undefined,address`. Kein Gleitkommatyp im Quelltext (`grep` auf `float`,
`double`, `long double`: null Treffer).

```
belegstellen_riegel, Selbsttest: 8 Faelle zur Suche nach links und 9 zur Form
ohne Anfuehrung, alle wie erwartet.
belegstellen_riegel, Bedingung 1 (Zeilennummer in eine fremde Datei): 42 Bauquellen
gelesen, 5 Zeilenverweise getroffen, davon 0 mit Dateinamen daneben.
belegstellen_riegel, Bedingung 2 (Abschnittszitat): 42 Bauquellen und 11
Datendokumente gelesen, 153 Dateien im Zielbestand; 38 Zitate der geprueften Form
gefunden, 38 davon aufgeloest, 56 Fundstellen uebergangen.
Davon ohne Anfuehrung: 14 Zitate; weitere 40 Fundstellen ohne Anfuehrung nennen in
ihrem Absatz keinen Dokumentnamen und sind deshalb keine Zitate.

Kein Verweis zeigt mit einer Zeilennummer in eine fremde Datei, und jedes der
38 Abschnittszitate findet seine Ueberschrift.

100% tests passed, 0 tests failed out of 1
```

Gegen den Stand von 0067 (`24 Zitate, 24 aufgeloest, 8 uebergangen`) also:
**+14 Zitate, +14 aufgeloest, +48 uebergangene Fundstellen.**

## Die vier Stellen aus Paket 0047, einzeln abgehakt

Alle vier tragen die Form `<datei>, <Schluesselwort> <Name>` in `daten/reihen.toml`.
Die Zeilennummern sind die des Laufs und stehen hier als Messwert, nicht als Verweis.

| Stelle | Name | Urteil des Riegels |
|---|---|---|
| `reihen.toml:172`, Feld `reihenliste` | Sieben | uebergangen, *Gliederungsziffer statt Ueberschrift* |
| `reihen.toml:253`, Feld `beleg` unter `zaehlung.lizenz` | Fuenf | uebergangen, *Gliederungsziffer statt Ueberschrift* |
| `reihen.toml:1746`, Feld `schnitt_2_offen` | die Reihe mit ihrer Nummer | nachgeschlagen in `daten/lizenzbefund-reihen.md`, **aufgeloest** |
| `reihen.toml:1746`, Feld `schnitt_2_offen` | die Aufzaehlung der zwei Buchstabenreihen | nachgeschlagen in `daten/lizenzbefund-reihen.md`, **aufgeloest** |

Die zwei Nummern stehen im Lauf oben namentlich in der Aufzaehlung der uebergangenen
Fundstellen. Die zwei Namen stehen dort **nicht** -- sie sind Zitate und aufgeloest.

## Der Rotnachweis fuer die zweite Gruppe

Gefuehrt ueber die **eigene** Datei und ohne eine fremde anzufassen: `lies_ueberschriften`
bekam einen Vorsatz vor jede gelesene Ueberschrift -- das ist genau der Fall
"jemand hat die Ueberschrift umbenannt", nur an einer Stelle, die zu diesem Paket
gehoert. Danach zurueckgestellt und neu gebaut.

Der Lauf mit dem Vorsatz meldet unter anderem:

```
  zitierend: daten/reihen.toml:1746
  nachgeschlagen in: daten/lizenzbefund-reihen.md
  gesuchte Ueberschrift: Reihe 1

  zitierend: daten/reihen.toml:1746
  nachgeschlagen in: daten/lizenzbefund-reihen.md
  gesuchte Ueberschrift: 2b und 2c
```

Beide werden also wirklich nachgeschlagen, und beide werden rot, wenn ihr Ziel
umbenannt wird -- die zweite auch dann, obwohl ihr Name mit einer Ziffer beginnt.
Nach dem Zuruecknehmen: wieder gruen, dieselben Zahlen wie oben.

**Zweiter Rotnachweis, dieselbe Sache am kleinen Maszstab.** In `ist_wortpraefix`
wurde die Wortgrenze abgeschaltet (nur noch Gleichheit). Dann fallen die Faelle 1 und 3
in `ZITATFAELLE` mit `die Art ist 4, erwartet war 0` -- der Riegel bricht mit Code 2 ab,
bevor er den Bestand liest. Auch das zurueckgestellt.

## Die Selbsttesttabelle, und warum sie noetig ist

Auf dem heutigen Korpus loest **jedes** Zitat ohne Anfuehrung auf. Der Bestand kann
deshalb nur zeigen, dass der Riegel gruen wird, nie dass er rot werden kann. Die neun
Faelle in `ZITATFAELLE` halten die Gegenprobe fest; vier von ihnen haben eine Erwartung,
die **nicht** "aufgeloest" lautet, und zwei erwarten ausdruecklich einen Befund.

Zwei der neun sind waehrend dieses Laufs rot geworden und haben je einen echten Fehler
gezeigt, bevor er in den Bestand kam:

* Fall 4 (die Aufzaehlung, umbenannt) fiel als *Ziffer* statt als *Befund* aus. Das war
  die Restluecke der ersten Fassung: Ein Name, der mit einer Ziffer beginnt, sah nach
  einer Nummer aus, auch wenn die Zieldatei gar nicht mit ihr nummeriert. Behoben durch
  `fuehrt_gliederungsziffer`.
* Fall 7 (der Verweis auf einen eigenen Abschnitt) fiel als *Befund* aus. Ursache: Der
  naechstgelegene Dokumentname im Absatz ist eine fremde Datei. Behoben, indem bei der
  Ziffer auch die zitierende Datei gefragt wird.

## Was ausdruecklich nicht erreicht ist

**Die Abnahme verlangt, die Zahl der uebergangenen Fundstellen falle "um genau zwei".
Das ist auf diesem Korpus nicht erfuellbar, und zwar in beide Richtungen.**

Der Grund ist gemessen: Das Arbeitspaket sagt, `reihen.toml` trage die Form
"viermal". Sie steht dort oefter. Gezaehlt am Lauf oben: **48** neu uebergangene
Fundstellen ueber den ganzen Bestand (56 minus die 8 aus 0067), davon **33** allein in
`reihen.toml`; dazu 14 aufgeloeste Zitate der neuen Form. Wer jede Gliederungsziffer
uebergeht und namentlich nennt -- und genau das verlangt die Abnahme fuer die zwei
Nummern aus 0047 --, bekommt zwangslaeufig mehr als zwei zusaetzliche Zeilen; wer
weniger bekaeme, uebersaehe welche.

Ein Fallen der Zahl waere ausserdem nur moeglich, wenn dieses Paket bestehende
uebergangene Fundstellen aufloeste. Von den acht aus 0067 traegt keine einzige die Form
ohne Anfuehrung -- sie haengen an fehlenden Dokumentnamen, an einer Netzadresse und an
einem Ziel unter `befunde/`. Keine von ihnen kann dieses Paket beruehren.

Die Zahl ist deshalb nicht getroffen worden, und sie ist auch nicht durch eine
Abschwaechung des Riegels getroffen worden. Der Satz davor -- zwei Nummern uebergangen
und gezaehlt, zwei Ueberschriften nachgeschlagen und aufgeloest, je mit Rotnachweis --
ist erfuellt. Der Widerspruch gehoert dem Projektmanager.

## Drei benannte Grenzen

Sie stehen im Kopf des Riegels ausgeschrieben und hier nur als Liste, damit der Pruefer
sie nicht suchen muss: Kleinschreibung hinter dem Schluesselwort (kein Zitat, nicht
gezaehlt in der Aufzaehlung, aber in einer eigenen Zahl), fehlender Dokumentname
(dasselbe), und ein einzelner Buchstabe als Name (uebergangen und namentlich genannt).
