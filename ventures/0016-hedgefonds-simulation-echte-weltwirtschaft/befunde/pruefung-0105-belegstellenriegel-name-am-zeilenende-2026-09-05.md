---
typ: pruefung
paket: 0105-belegstellenriegel-name-am-zeilenende
pruefer: test-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: alle drei Nachweise der Abnahme unabhaengig nachgemessen (eigene Kopie, eigener Bau beider Fassungen, eigene Ein-Zeilen-Mutanten), dazu die Regelform am Code und im Kopfkommentar
befunde: 0
---

# Pruefung 0105 -- der Name endet an seiner Zeile

## Messaufbau

Eigene Arbeitskopie unter `$TMPDIR/tp0105-fable/baum/` (ventures + specs; unter
`bau/` und `befunde/` nur leere Platzhalter gleichen Pfads -- der Riegel sammelt
dort allein Pfade ein, `sammle_dateien` liest keinen Inhalt). Beide Fassungen im
selben Aufbau gebaut (`g++ -std=c++20 -O2 -fwrapv`): **neu** = Arbeitsbaum
(HEAD `94f7a88`), **alt** = `git show 0333b81^:.../belegstellen_riegel.cpp`
(Stand `851c401`, unmittelbar vor dem 0105-Eingriff). Der Eingriff selbst liegt
nicht im Betreff-Commit `8bfae3b` (der traegt keine Zeile der Zieldatei), sondern
in `0333b81` (Code + 4 Zitatfaelle), `74e1464` (Kopfabschnitt), `1f763e9` und
`4bbd069` (Mutantennachweis-Kommentar) -- alle vier Aenderungen an der Zieldatei
sind dem Paketzweck zuzuordnen, die `dateien`-Liste ist eingehalten.

## Nachweis 1 -- rot vorher, gruen nachher

Die zwei Zeilen aus dem Paketrumpf an die Kopie von `rueckstand.md` angehaengt
(`... Abschnitt Reihe 1\nund wird dort nicht bestritten.`; die Ueberschrift
`## Reihe 1 — BIP, konstante Preise — **unklar**` steht in der Zieldatei,
Zeile 86).

* alt: **Code 1**, Meldung `gesuchte Ueberschrift: Reihe 1 und wird dort nicht
  bestritten` -- exakt das beschriebene Fehlerbild.
* neu: **Code 0**, und die Stelle wird nicht etwa uebergangen, sondern zaehlt
  als zusaetzliches aufgeloestes Zitat (38/38 statt 37/37; ohne Anfuehrung
  15 -> 16). Uebergangene unveraendert 47.

## Nachweis 2 -- keine tote Belegstelle kommt durch

Dieselbe Stelle mit `Reihe 1b` (keine Ueberschrift der Zieldatei beginnt so):
alt **Code 1**, neu **Code 1**, und die Meldung der neuen Fassung nennt den
**gekuerzten** Namen `Reihe 1b` statt des halben Nebensatzes.

## Nachweis 3 -- der Bestand verliert nichts

Alt und neu auf der unveraenderten Kopie (heutiger Korpus): beide **Code 0,
37 Zitate, 37 aufgeloest, 47 uebergangen**. `diff` beider Ausgaben: nur die
Selbsttest-Zaehlzeile (9 -> 13 Faelle) und die `gesucht war`-Wortlaute dreier
Gliederungsziffer-Fundstellen, bei denen alt ueber den Umbruch hinauslas
(`17 specs/0016-.../daten.md Quellen und Lizenzen ...` -> `17`). Kategorie und
Anzahl jeder uebergangenen Fundstelle gleich; kein aufgeloestes Zitat faellt weg
oder wandert. (Kopfkommentar und Bauagent nennen 36/36 -- das war der
eingefrorene Bezugsstand `456aefa`, `befunde/messung-0105/bezugsstand.txt`; der
Korpus ist seither um ein Zitat gewachsen. Die Abnahme sagt "auf dem dann
geltenden Korpus", die Vorher/Nachher-Gleichheit ist das Kriterium und sie gilt.)

## Regelform und Deckung

* **Benannte Eigenschaft statt Liste:** entschieden wird in
  `name_ohne_anfuehrung` am Vergleich `absatz.zeile_bei(ende) == heimatzeile`
  (Zeile 2271/2274), Heimatzeile = Zeile des ersten Namenszeichens; keine
  Fallliste. Der Kopf traegt die Regel als vierte der ausgeschriebenen Grenzen
  und in einem eigenen Abschnitt samt Preis. Testpfad und Ernstfall teilen sich
  `haenge_zeile_an` (Selbsttest baut den Absatz ueber `absatz_aus_fall`, keine
  nachgebaute Zusammenziehung).
* **Eigene Mutanten, nicht die des Nachweises:** (a) Zeilengrenze neutralisiert
  (`true || ...`): Selbsttest **Code 2, 3 von 51** reissen (Zitatfaelle 10, 11,
  13 -- Grundfall, tote Ueberschrift, Preisfall). (b) Heimatzeile vom letzten
  Schluesselwortzeichen (`zeile_bei(i - 1)`): **Code 2, 1 von 51** (Zitatfall 12,
  leere Namensspalte). Beide Kippmengen decken sich mit der Behauptung im Kopf;
  kein Fall reisst bei beiden, zusammen decken die vier Faelle beide Haelften
  der Regel dauerhaft -- der Bestand selbst wuerde den Rueckbau heute nicht
  fangen (M0 ist auf beiden Fassungen gruen), die Tabelle faengt ihn bei jedem
  Aufruf.
* **Keine Abschwaechung:** Untergrenze unveraendert (16), kein bestehender
  Selbsttestfall geaendert oder entfernt (Diff `851c401..HEAD` der Zieldatei
  vollstaendig gelesen); die 47 Faelle der vier anderen Tabellen bleiben in
  allen Laeufen gruen.

Erst nach diesen Messungen gegengelesen: `befunde/messung-0105/mitschnitt.txt`
(11 ctest-Faelle, alle Passed) -- deckt sich in jeder vergleichbaren Zahl.

## Wonach sonst gesucht, ohne Befund

Bindung der Grenze an die Namens- statt Schluesselwortzeile (Zitatfall 12 und
Mutant b messen genau das); Verhalten der Form **mit** Anfuehrung (unveraendert,
`ueberschrift_hinter` fragt `zeile_bei` nicht -- der Preisfall 13 belegt die
gewollte Richtung fuer die Form ohne); Ruecklaufkollisionen im Befundnamen
(keine vorhanden). Waehrend der Pruefung schrieb ein paralleler Lauf unter
`befunde/bau-pruefung-0108/` in den Arbeitsbaum; fuer die Messung folgenlos,
weil beide Fassungen auf derselben eingefrorenen Kopie liefen.
