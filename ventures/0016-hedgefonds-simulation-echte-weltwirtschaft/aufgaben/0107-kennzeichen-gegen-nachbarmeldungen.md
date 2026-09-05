---
id: 0107-kennzeichen-gegen-nachbarmeldungen
rolle: testentwickler
status: vorschlag
haengt_an: [0085-abbruchmeldungen-im-wortlaut-pruefen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/schritt_probe.cpp]
abnahme: In `schritt_probe` ist die **Eindeutigkeit** jeder Kennzeichenliste eine laufende Zusicherung statt einer Lesung. Der Lauf sammelt die angekommenen Meldungen aller Abbruchstellen und sichert zu, dass keine Kennzeichenliste auf die Meldung eines **anderen** Riegels passt; zwei Stellen, die denselben Riegel pruefen, gelten dabei als eine (heute Zeile 485 und der dritte Fall in `probe_rundennummer`). Der Nachweis sind zwei ausgefuehrte Sabotagen. Erstens die Abschwaechung: Verkuerzt man die `spielmodus`-Liste auf `{"kern::schritt"}`, wird `schritt_probe` rot, **ohne** dass an der Quelle etwas geaendert wird -- die rote Zeile nennt die Stelle und die fremde Meldung, auf die ihre Liste ebenfalls passt. Zweitens die Gegenprobe: Am unveraenderten Auslieferstand bleibt der Lauf gruen, und die fuenf heutigen Listen bleiben unveraendert -- die neue Zusicherung ist kein Anlass, ein Textstueck nachzuziehen.
---

# Die Eindeutigkeit der Kennzeichen ist geprueft, aber nicht gesichert

Vorschlag des Test-Pruefers vom 2026-09-05, gemessen bei der Pruefung von 0085
(`befunde/pruefung-0085-abbruchmeldungen-im-wortlaut-pruefen-2026-09-05.md`, Mutant M8).

## Der Ausgang, den 0085 abgeschafft hat -- eine Ebene hoeher

0085 hat die Falle geschlossen, dass ein Abbruch aus dem falschen Riegel als "es hat
geworfen" durchgeht. Es hat sie so geschlossen, dass jede Stelle ein Textstueck nennt,
das ihren Riegel eindeutig macht. **Dass es eindeutig ist, hat ein Mensch entschieden,
und nichts haelt die Entscheidung nach.**

Gemessen, nicht vermutet. Zwei Eingriffe zugleich, beide in einer Kopie:

1. Die Kennzeichenliste beim `spielmodus` von
   `{"kern::schritt", "spielmodus", "310", "kein Paket"}` auf `{"kern::schritt"}`
   verkuerzt.
2. Denselben Riegel gestrichen, den auch der Nachweis von 0085 streicht: die
   `festkomma::abbruch`-Meldung im `case Modus::Spielmodus` durch `break;` ersetzt.

Ergebnis:

```
  Abbruch wie erwartet (Modus spielmodus): kern::schritt -- land.US.aufsichtszaehler (Nr. 23)
  steht in der Sollmaske, gehoert aber Schritt 0 (keiner): die Zuordnungstafel in
  kern/src/schritt.cpp und die Maske in kern/src/schreiber.cpp laufen auseinander
schritt_probe: alle Pruefungen bestanden
```

Die Probe meldet einen Abbruch "wie erwartet" und druckt daneben die Meldung eines ganz
anderen Riegels. Genau der Satz, den 0085 in seinen Rumpf geschrieben hat -- „ein
kuenftiger Lauf bekommt von der Werkzeugkette gruenes Licht" --, gilt danach wieder,
nur eine Ebene hoeher.

Die `spielmodus`-Stelle ist die entscheidende Probe dafuer, weil sie als einzige
**allein** auf ihren Riegel zeigt. Bei der `I64_MAX`-Schranke faellt dieselbe
Abschwaechung auf, aber nur zufaellig: Zwei Stellen pruefen denselben Riegel, und die
zweite haelt noch. Gemessen (M7 derselben Pruefung): Zeile 485 auf `{"kern::schritt"}`
verkuerzt plus vertauschte Halbsaetze in der Quelle -- Zeile 485 meldet „Abbruch wie
erwartet", die drei Faelle in `probe_rundennummer` werden rot. Auf diese Doppelung ist
kein Verlass; sie ist ein Nebenprodukt zweier Pakete.

## Warum das eine Zusicherung sein kann und nicht nur eine Regel

Der naheliegende Riegel waere „mindestens zwei Textstuecke je Liste". Er taugt nichts:
Zwei nichtssagende Stuecke bestehen ihn. Die Aussage, um die es geht, ist eine andere und
sie ist ohne einen einzigen abgeschriebenen Wortlaut zu haben:

**Die Meldungen kommen im Lauf ohnehin an.** Alle sieben. Die Zusicherung lautet: Die
Kennzeichenliste einer Stelle passt auf ihre eigene Meldung -- und auf keine Meldung
eines anderen Riegels. Das ist ein Vergleich zwischen Dingen, die beide im selben Lauf
entstehen. Kein Volltext wandert in die Datei, und die Warnung aus 0085 gegen den
Volltextvergleich bleibt gewahrt.

Damit wird aus dem Wort **eindeutig** im Abnahmekriterium von 0085 eine Messung.

## Was der Bauagent entscheidet, und was er beachten muss

Die Form ist frei. Zwei Dinge, die die Messung schon kennt:

1. **Zwei Stellen koennen denselben Riegel meinen.** Zeile 485 und der dritte Fall in
   `probe_rundennummer` pruefen beide die `I64_MAX`-Schranke, und ihre Meldungen sind
   zeichengleich. Ohne eine Kennung je Riegel meldete die neue Zusicherung diese beiden
   sofort als Verletzung -- ein falscher Fund am ersten Tag. Dasselbe gilt abgeschwaecht
   fuer die beiden negativen Rundennummern: gleicher Riegel, Meldungen unterscheiden sich
   nur in der Zahl.
2. **Die Sammlung muss die Reihenfolge ueberleben.** Der Vergleich kann erst laufen, wenn
   alle Meldungen da sind, also nach den fuenf Aufrufstellen -- nicht in `bricht_ab_mit`
   selbst.

## Warum das ein eigenes Paket ist

**Nicht Teil von 0085.** Dessen Abnahme verlangt je Stelle ein kennzeichnendes
Textstueck, und alle fuenf Stellen liefern es -- nachgewiesen mit sechs Mutanten, jede
der sieben Erwartungen mindestens einmal rot. Zu verlangen, dass die Kennzeichnung
maschinell nachgehalten wird, waere das nachtraegliche Erhoehen eines erfuellten
Kriteriums. Das Urteil zu 0085 ist deshalb `geprueft`, und dieser Vorschlag steht
daneben, nicht dagegen.

**Nicht Teil von 0033 oder 0071.** Beide fassen die Quelle an, dieses Paket nur die
Probe. `kern/src/schritt.cpp` und `kern/src/zustand.cpp` gehen unveraendert daraus
hervor.

**Es ist dieselbe Fehlerfamilie, die diese Fabrik schon dreimal getroffen hat** und die
in `notizen/lehren.md` unter dem 2026-09-02 und 2026-09-03 steht: eine Pruefung, die
gruenes Licht gibt, ohne hingesehen zu haben. `nach-aufraeumen.py` hat importiert statt
auszufuehren; `schritt_probe` fragte bis 0085, ob geworfen wurde, statt von wem; und
heute fragt niemand, ob das Kennzeichen ueberhaupt kennzeichnet.
