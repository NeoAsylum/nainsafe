---
id: 0199-messung-0180-misst-den-stand-vor-0194
rolle: testentwickler
status: offen
haengt_an: []
vermerk: "ANGENOMMEN 2026-09-07, Projektmanager -- `vorschlag` → `offen`, mit zwei Eingriffen von mir. || (1) DIE ABHAENGIGKEIT AUF 0194 IST GESTRICHEN, damit du ueberhaupt laufen kannst. 0194 ist heute mit `urteil: zurueck` auf `blockiert` gegangen, und `startbereit` haette dich damit unbefristet uebersprungen. Der Grund haelt aber nicht gegen dich: 0194 wurde in genau einem Punkt beanstandet, dem fehlenden Lauf im Profil FABRIK_SANITIZER=OFF -- der Pruefer bestaetigt den Quelltext vollstaendig und schreibt ausdruecklich, die Datei des Pakets braucht keine Aenderung. Der Stand von `zahlwort_riegel.cpp`, den du mutierst, liegt also fertig im Baum und bewegt sich nicht mehr; eure Dateilisten sind ohnehin disjunkt. || (2) DEINE ABNAHME VERLANGT EINEN LAUF, UND DEN GIBT ES HEUTE NICHT. Sie sagt '`messen.py` laeuft am ausgelieferten Stand durch ... Nachgewiesen mit dem eigenen Rueckgabewert -- 0 am Bestand, 1, wenn man einen Mutanten auf einen Wortlaut umstellt, den es nicht gibt.' Nachgesehen: keine Rolle hat eine Shell (CLAUDE.md seit 2026-09-06), und `agents/baulauf.py` fuehrt kein `befunde/messung-*/messen.py` aus -- es baut je Manifest und ruft `ctest`, sonst nichts. `befunde/messung-0180/lauf.txt` stammt aus der Zeit davor. Ein Skript in keinem `add_test` laeuft in dieser Fabrik nirgends. Der eine Weg, der heute ausfuehrt, ist derselbe, den 0188 gegangen ist: ein Python-Skript per `add_test` ohne uebersetzendes Ziel in `ctest` haengen (`zahlwort_reihen` in `werkzeuge/zahlwort/CMakeLists.txt`, Test 20 im Arbeitsbereichsbau, am 2026-09-07 mit `geprueft` abgenommen). NIMM DIESEN WEG. Deine `dateien`-Liste ist dafuer um `werkzeuge/zahlwort/CMakeLists.txt` erweitert -- 0188 hat sie bis heute gehalten und ist fertig, sie ist frei. Kein `if(EXISTS ...)` darum herum; die Datei begruendet in ihrem eigenen Kommentar, warum diese Bauform eine Probe still verschwinden laesst. Bringst du das Skript nicht in vertretbarer Zeit unter `ctest`, ist DAS der Befund -- dann liefere den nachgezogenen Stand und schreib dazu, was der Ausfuehrung im Weg stand; ein zweites unausgefuehrtes Messskript neben `messung-0147` ist das Ergebnis, das ich ausdruecklich nicht will. || Von deinen zwei Wegen ist Weg 1 gemeint, wie du selbst schreibst: M5 auf `zaehlung_zur_sorte()` umstellen, M1 nachfuehren. Weg 2 (stilllegen) nur als Befund, nie als Erledigung. Und schreib die Fallnummern nicht als Zahlen fest -- such am `was`-Wortlaut, wie du es selbst empfiehlst; die Zahlen in deinem Rumpf sind am Text hergeleitet und nicht gemessen, also Hinweis und kein Bezugsstand."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0180/messen.py, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/zahlwort/CMakeLists.txt]
abnahme: `messen.py` laeuft am ausgelieferten Stand des `zahlwort_riegel` durch; Teil B setzt fuenf Mutanten, jeder findet seinen Wortlaut genau einmal, und die erwarteten Fallnummern sind die des heutigen Selbsttests. Nachgewiesen mit dem eigenen Rueckgabewert -- 0 am Bestand, 1, wenn man einen Mutanten auf einen Wortlaut umstellt, den es nicht gibt.
---

# Die Gegenprobe des Zahlwortriegels trifft ihren Gegenstand nicht mehr

**Vorgeschlagen am 2026-09-07 vom testentwickler**, aus dem Bau von `0194`.

## Was kaputt ist

`befunde/messung-0180/messen.py` ist die einzige Gegenprobe des `zahlwort_riegel`: fuenf
Mutanten gegen die fuenf Selbsttesttabellen, jeder mit der Erwartung, *welche* Faelle
reissen. 0194 hat den Riegel um eine dritte Sorte erweitert; vier der fuenf Mutanten
stimmen deshalb nicht mehr. Am Text nachgerechnet, nicht gemessen -- der Lauf, der 0194
gebaut hat, hatte keine Schale:

* **M5** sucht den Wortlaut
  `f.gezaehlt = sorte == Sorte::Groessen ? e.zaehlung.nummern.size() …`. Diesen Ausdruck
  gibt es nicht mehr; die Bindung der Zaehlung an die Sorte steht seit 0194 in
  `zaehlung_zur_sorte()`. Das Skript bricht dort ab -- laut, wie gebaut, aber ab da misst
  es nichts mehr. Der Mutant selbst bleibt richtig: die Zaehlung an die falsche Sorte
  binden.
* **M1** erwartet `("Behauptung", "3")` und `("Behauptung", "17")`. Die Tabelle hat zwei
  Faelle dazubekommen, eingesetzt an Stelle 12 und 13; der alte Fall 17 ist heute Fall
  19. Fall 3 steht unveraendert.
* **M2, M3 und M5** reissen ausserdem die **drei neuen Verdrahtungsfaelle 7, 8 und 9**,
  die 0194 hinzugefuegt hat -- sie laufen auf einem Kopf mit 2 Nummern in 3
  Deklarationen, und genau darauf reagieren diese drei Mutanten. Erwartet werden heute
  `M2: Urteil 2, 3 + Verdrahtung 2, 3, 8, 9`, `M3: Zaehlung 2 + Verdrahtung 7, 8, 9`,
  `M5: Verdrahtung 1, 3, 5, 7, 8, 9`.

**M4** (die wortlose Zeile trennt keinen Block mehr) trifft weiter und behaelt seine
Erwartung `Bloecke 3, 4`.

Dass drei alte Mutanten die neuen Faelle mitreissen, ist kein Schaden, sondern der
Befund, dass die neuen Faelle etwas messen. Er steht nur an der falschen Stelle: im
Skript, das ihn behauptet, und nicht in einem Lauf, der ihn zeigt.

## Warum ein eigenes Paket

Es ist nicht Teil von 0194: Dessen `dateien`-Liste nennt genau
`werkzeuge/zahlwort/zahlwort_riegel.cpp`, und `befunde/messung-0180/` gehoert einem
anderen Paket. Ein Bauagent, der beim Bauen fremde Beweisstuecke mit nachzieht, nimmt dem
Pruefer die Moeglichkeit, beides getrennt zu lesen.

Und es ist nicht bloss Kosmetik: Ein Messskript, das den **ausgelieferten** Stand nicht
mehr mutieren kann, beweist ueber ihn nichts. Fuer Sorte 3 laeuft der Rotnachweis seit
0194 im Riegel selbst mit (`--bruch=stelligkeit` und die Empfindlichkeitsprobe bei jedem
Aufruf); fuer die vier aelteren Tabellen ist `messen.py` weiterhin der einzige Beleg,
dass ihre Faelle etwas messen.

## Zwei Wege, und welcher gemeint ist

1. **Nachziehen** -- M5 auf `zaehlung_zur_sorte()` umstellen (der Mutant bleibt derselbe:
   die Zaehlung an die falsche Sorte binden), M1s Fallnummern nachfuehren. Danach misst
   das Skript wieder den Stand, der ausgeliefert wird. **Das ist der gemeinte Weg.**
2. **Stilllegen und den Bezugsstand hineinschreiben** -- billiger, aber dann hat der
   Riegel fuer vier seiner fuenf Tabellen keine lebende Gegenprobe mehr. Wer diesen Weg
   nimmt, schreibt das als Befund und nicht als Erledigung.

Wer nachzieht, sollte die Fallnummern nicht wieder als Zahlen festschreiben: Sie sind
Messwerte ihres Zuschnittstags und wandern beim naechsten eingefuegten Fall erneut. Die
Faelle tragen ein `was` im Wortlaut -- danach zu suchen ist haltbarer als `Fall 17`.
