---
id: 0105-belegstellenriegel-name-am-zeilenende
rolle: testentwickler
status: vorschlag
haengt_an: [0079-belegstellenriegel-zitat-ohne-anfuehrung]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp]
abnahme: Eine richtige Belegstelle der Form ohne Anfuehrung, die am Zeilenende steht und deren Satz in der naechsten Zeile weiterlaeuft, macht den Riegel nicht mehr rot. Entschieden wird an einer benannten Eigenschaft, nicht an einer Liste, und die Entscheidung steht im Kopfkommentar unter den ausgeschriebenen Grenzen. Nachgewiesen mit drei Nachweisen an einer Kopie des Vorhabens: erstens rot vorher und gruen nachher an der zwei Zeilen langen Stelle aus dem Rumpf unten; zweitens weiterhin rot, wenn dieselbe Stelle eine Ueberschrift nennt, die es nicht gibt (die Lockerung darf keine tote Belegstelle durchlassen); drittens unveraendert 38 Zitate, 38 aufgeloest auf dem dann geltenden Korpus -- keines der heute aufgeloesten Zitate faellt dadurch weg oder in die uebergangenen Fundstellen.
---

# Der Name laeuft ueber den Zeilenumbruch weiter -- und wird rot, wo nichts kaputt ist

Vorschlag des Test-Pruefers vom 2026-09-05, gemessen bei der Pruefung von 0079
(`befunde/pruefung-0079-belegstellenriegel-zitat-ohne-anfuehrung-2026-09-05.md`,
Befund 2).

## Der Fehler, Schritt fuer Schritt

Bedingung 2 sucht **je Absatz**, und ein Absatz ist ein Block gleichartiger Zeilen zu
einer Zeichenkette zusammengezogen. Das ist richtig und seit 0067 begruendet: Ein
Dateiname steht regelmaessig Zeilen ueber seinem Zitat. Fuer die Form **mit** Anfuehrung
ist das folgenlos, weil das schliessende Anfuehrungszeichen den Namen begrenzt. Fuer die
Form **ohne** Anfuehrung, die es seit 0079 gibt, endet der Name erst am naechsten
Satzzeichen -- und wo am Zeilenende keines steht, laeuft er in die naechste Zeile hinein.

In eine gelesene Datei des Vorhabens geschrieben (`rueckstand.md` genuegt):

```
Der Wortlaut steht in `daten/lizenzbefund-reihen.md`, Abschnitt Reihe 1
und wird dort nicht bestritten.
```

Das Zitat ist richtig, die Ueberschrift `Reihe 1 — BIP, konstante Preise — unklar` steht
in der Zieldatei. Der Riegel meldet trotzdem Code 1 und
`gesuchte Ueberschrift: Reihe 1 und wird dort nicht bestritten`.

## Warum das ein eigenes Paket ist

**Es ist eine Entscheidung mit eigenem Nachweis, keine Nachbesserung.** Der Zeilenumbruch
ist die Grenze, die 0079 nicht getroffen hat, und beide naheliegenden Wege haben einen
Preis, der gemessen gehoert:

* *Der Name endet am Zeilenumbruch.* Billig und scharf -- kostet aber die ueber zwei
  Zeilen umgebrochene Ueberschrift, und genau die will die Normierung ausdruecklich
  einfangen ("damit eine ueber zwei Zeilen umgebrochene Ueberschrift dieselbe ist wie eine
  einzeilige"). Wieviel das kostet, ist zaehlbar und heute nicht gezaehlt.
* *Der Name wird gekuerzt, solange er nicht aufgeht.* Faengt beide Faelle, macht aber aus
  dem Vergleich eine Suche und schwaecht die Zusicherung: Je kuerzer der gepruefte
  Anfang, desto mehr Umbenennungen ueberleben. Dann braucht es eine Untergrenze, und eine
  geratene Untergrenze in einem Messgeraet ist genau das, was der Kopfkommentar bei der
  Suche nach links schon einmal verworfen hat.

Das gehoert nicht in ein Paket, das etwas anderes abnimmt -- und in 0079 gehoerte es
nicht hinein, weil dessen Abnahme fuenf Bedingungen traegt und den Zeilenumbruch in keiner
nennt.

**Es ist nicht gedacht, sondern gefunden.** Richtet man den ausgelieferten Riegel auf die
Wurzel des Repos, kommen gegenueber der Vorfassung fuenf Befunde dazu, und alle fuenf sind
von dieser Art. Sie liegen heute in `aufgaben/`-Dateien und damit ausserhalb des
Pruefwegs; in `daten/` oder in `rueckstand.md` waere jede von ihnen ein roter Lauf. Der
naechste Bauagent, der eine Belegstelle in Fliesstext schreibt und dabei umbricht,
erzeugt sie.

## Was ausdruecklich kein Befund ist

* **Dass 0079 diese Grenze nicht getroffen hat.** Sie war in seiner Abnahme nicht genannt.
* **Die drei Grenzen, die im Kopfkommentar schon stehen** (Kleinschreibung, fehlender
  Dokumentname, einzelnes Zeichen). Sie sind ausgewiesen und gemessen.

## Grenzen

* Nur `belegstellen_riegel.cpp`. Dieselbe Datei wie 0083, 0086 und 0106 -- gleichzeitig
  geht nicht.
* Kein Aufraeumen in `daten/`, keins in `specs/`, und keine Zeile Fliesstext umformuliert,
  damit der Riegel gruen wird. Wer die Prosa umschreibt, hat den Riegel geprueft und nicht
  die Prosa.
* Keine Gleitkommazahl, keine Fremdabhaengigkeit, kein fest eingebauter Pfad.
