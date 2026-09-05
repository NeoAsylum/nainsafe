---
typ: pruefung
paket: 0029-vorratsverfahren-invariante
pruefer: test-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Alle fünf Abnahmebedingungen einzeln nachgerechnet, dazu 18 absichtlich kaputte Fassungen des Moduls gegen die unveränderte Probe übersetzt — jede einzelne wird rot, beide Kontrollläufe bleiben grün.
befunde: 0
---

# Die Probe zu 0029 wird rot, wenn man die Sache kaputtmacht — achtzehnmal nachgewiesen

## Was ich gelesen habe und was nicht

Gelesen: das Arbeitspaket, `pruefstand/include/pruefstand/vorrat.hpp` (Paket 0019,
unveränderlich), `src/vorrat_verfahren.cpp` und `test/vorrat_verfahren_probe.cpp`
vollständig, `spiel.md` Zeile 1286–1320, `technik.md` T43 und T30 Prüfung 1,
`pruefstand/CMakeLists.txt`, `befunde/uebersetzung-2026-09-03.md`.

**Nicht gelesen: `notizen/testentwickler.md`.** Wer die Begründung liest, übernimmt sie
und prüft dann die Absicht statt das Ergebnis.

## Der Mutationsstand

Liegt unter `befunde/pruefung-0029/` und fasst keine Datei des Pakets an: `file(READ)`
liest, `string(REPLACE)` ändert die Kopie im Speicher, `file(WRITE)` legt sie im
Bauverzeichnis ab. Je Mutant wird die **unveränderte** Probe des Pakets gegen ein
absichtlich kaputtes `vorrat_verfahren.cpp` übersetzt; der Testeintrag trägt
`WILL_FAIL TRUE`. Damit heisst „ctest grün" hier: *Die Kontrollfassung besteht, und
jeder Mutant wird gefangen.*

`befunde/` ist der einzige Verzeichnisname, den `agents/baulauf.py:116` beim Suchen der
Manifeste überspringt — deshalb steht der Stand dort und nirgends sonst.

```
20/20 Tests passed  (2 Kontrollen + 18 Mutanten)
```

| Mutant | veränderte Regel | Zusicherungen, die reissen |
|---|---|---:|
| `kontrolle_unveraendert` | — (Urschrift) | **0, besteht** |
| `kontrolle_wirkungslos` | nur ein Kommentar | **0, besteht** |
| `mut01_gleichstand_groessere` | Gleichstand an die grössere Kennung | 3 |
| `mut02_vorrat_abgeschnitten` | `vi` bei null abgeschnitten | 10 |
| `mut03_zuwachs_nur_zulaessig` | Rundenanfang nur für zulässige Arten | 2 |
| `mut04_leerer_platz_verrechnet` | leerer Steckplatz verrechnet doch | **1** |
| `mut05_ai_null_verboten` | `ai = 0` als hartes Verbot | 4 |
| `mut06_kennung_nullbasiert` | Folge trägt den Index statt der Kennung | 12 |
| `mut07_zwei_steckplaetze` | zwei Steckplätze statt drei | 15 |
| `mut08_kosten_sechs` | `vi -= 6` statt `-= 5` | 9 |
| `mut09_zuwachs_vier` | `vi += 4·ai` statt `+= 3·ai` | 8 |
| `mut10_leer_nicht_gezaehlt` | `leer_geblieben` zählt nicht | **1** |
| `mut11_schranke_ausschliessend` | Schranke schliesst die Grenze aus | **1** |
| `mut12_nur_fuenf_runden` | Lauf nach fünf Runden gekappt | 3 |
| `mut13_kleinstes_gewinnt` | kleinstes `vi` gewinnt | 9 |
| `mut14_start_nicht_null` | Vorrat startet bei 1 statt 0 | 8 |
| `mut15_verengung_je_platz` | Zulässigkeit je Steckplatz verengt (T32-Arbeit) | 9 |
| `mut16_abweichung_verschluckt` | `spiele` reicht die `Abweichung` nicht durch | 5 |
| `mut17_kein_leerer_platz` | `waehle` fällt auf Art 1 zurück statt `KEINE_ART` | 8 |
| `mut18_schranke_ohne_negativ` | Schranke prüft negative Rundenzahl nicht | **1** |

Jeder Mutant trägt eine Fehlerbremse: Trifft das Suchmuster nichts, bricht `cmake` mit
`FATAL_ERROR` ab. Ohne sie erzeugte ein Tippfehler eine unveränderte Datei, die brav
besteht — und ich zählte ihr Bestehen als Empfindlichkeit der Probe. Der zweite
Kontrolllauf (`kontrolle_wirkungslos`, ein geänderter Kommentar) zeigt, dass nicht schon
mein Eingriff selbst alles kaputtmacht.

## Die fünf Bedingungen, einzeln

**1 — Invariante für alle 126 Profile, `k = 1` und `k = 3`.** Erfüllt. `pruefe_invariante`
(Z. 172–207) prüft je Profil drei Dinge gegen eine **getrennt hingeschriebene** Erwartung
`3·k·ai`: Endvorrat null, `gezaehlt[i] == 3k·ai`, `leer_geblieben == 0`. Beide `k` haben
eine eigene Zusicherung (Z. 435 und 437), der Lauf meldet `126 von 126 heil` für beide.
Die 126 Profile kommen aus `erzeuge_profilliste()` (Z. 380), werden also geholt und nicht
zweitgerechnet.

*Der Nachweis, dass die zweite Hälfte trägt:* `mut12_nur_fuenf_runden` kappt den Lauf nach
fünf Runden. Er reisst **genau drei Zusicherungen, und alle drei sind der `k = 3`-Teil**
(Z. 438, 451, 366) — Z. 436 (`k = 1`) bleibt grün. Eine Probe, die nur `k = 1` prüfte,
liesse diesen Mutanten durch. Das ist der Fehler, der laut T43 dreimal Befund war, und
er wird gefangen.

**2 — Referenzfolge zeichengleich, und der Erwartungswert stammt nicht aus dem Programm.**
Erfüllt und nachgeschlagen. `spiel.md` Zeile 1318 f. lautet: *„Zur Probe das
Referenzprofil: Runden 1 bis 5 vergeben die Arten 1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,5
und stehen danach wieder auf `(0,0,0,0,0)`"*. `REFERENZFOLGE` (Z. 136) ist damit Zeichen
für Zeichen gleich, einschliesslich der Trenner. Der Endvorrat `(0,0,0,0,0)` ist ebenfalls
festgeschrieben (Z. 468) und nicht aus dem Lauf übernommen.

Die zweite Abschrift als Tabelle (Z. 140) wird in Prüfung 2a gegen die erste gelegt, bevor
sie Massstab wird. Ich habe den Massstab zusätzlich von Hand nachgerechnet — Runde 1 `1,2,3`
mit `v = (3,3,3,3,3)`, Runde 2 `4,5,1` mit `v = (1,1,1,6,6)`, bis Runde 5 auf
`(0,0,0,0,0)`; er stimmt.

**3 — Beide falschen Fassungen, und je *welche* Bedingung sie fängt und welche sie
durchlässt.** Erfüllt. Der Lauf druckt für `GLEICHSTAND_NACH_GROESSERER_KENNUNG`:
Bedingung 1 `besteht` bei `k = 1` **und** `k = 3` (126 von 126), Bedingung 2 `GEFANGEN`
in Runde 1, gelaufene Folge `5,4,3 | 2,1,5 | 4,3,2 | 1,5,4 | 3,2,1`. Für
`VORRAT_BEI_NULL_ABGESCHNITTEN`: Bedingung 1 `GEFANGEN` (5 von 126 heil, kippt zuerst bei
Kennung 1, Profil `(0,0,0,1,4)`, Endvorrat `(0,0,0,3,1)` statt null, ab Runde 1),
Bedingung 2 `besteht`. Beide Urteile sind zugesichert (Z. 363–368), nicht nur gedruckt —
und sie benutzen **dieselben** Prädikate wie die echten Prüfungen, nicht mildere.

*Der Nachweis, dass die Vorführung kein Theater ist:* `mut16_abweichung_verschluckt` lässt
`spiele` die `Abweichung` fallen, sodass beide falschen Fassungen wie die echte laufen.
Er reisst fünf Zusicherungen. Die Vorführung misst also an einem wirklich veränderten
Verfahren.

**4 — Leerer Steckplatz und die Gegenprobe zu `ai = 0`.** Erfüllt, beide Hälften.
4a (Z. 525–570) setzt einen Vorrat, der *nicht* bei null anfängt (`7,-2,0,4,-9`), und ein
Profil mit Nullen und Nicht-Nullen — „Zeichen für Zeichen der vom Rundenanfang" ist damit
eine Aussage über fünf verschiedene Zahlen. Die Erwartung wird getrennt hingeschrieben
und nicht von `runde` geholt. Geprüft: alle drei Plätze `LEER`, Vektor unverändert
gegenüber dem Rundenanfang, `leer_geblieben == 12` über vier Runden, null vergebene
Plätze. 4b (Z. 574–597) stellt Art 2 mit `a2 = 0` allein zur Wahl gegen Art 1 mit `v1 = 15`
und verlangt alle drei Steckplätze für Art 2.

*Der Nachweis, dass 4b unentbehrlich ist:* `mut05_ai_null_verboten` macht `ai = 0` zum
harten Verbot. **Bedingung 1 bleibt dabei für alle 126 Profile und beide `k` grün** — ich
habe es laufen lassen, Z. 436 und 438 melden nichts. Das ist kein Zufall: Eine Art mit
`ai = 0` soll `3k·0 = 0` Plätze bekommen, und genau null bekommt sie auch, wenn man sie
verbietet. Die Invariante kann diesen Fehler prinzipiell nicht fangen; ohne 4b wäre der
Satz aus `spiel.md` in diesem Kasten ungeprüft.

**5 — Kein Gleitkomma, keine Fremdabhängigkeit, keine gemerkte Ablage.** Erfüllt.
`float|double` über beide Dateien: keine Treffer. Der vom Paket vorgeschriebene
Mustervergleich auf veränderliche Ablage über `vorrat_verfahren.cpp`: keine Treffer.

**Von Hand nachgeführt, wie das Paket es verlangt** — ein Mustervergleich, der nichts
findet, ist kein Nachweis, dass nichts da ist: Ich habe alle 213 Zeilen der Quelle
durchgesehen. Die **einzige** Deklaration ausserhalb einer Funktion ist
`constexpr std::size_t KEINE_ART = ARTEN;` (Z. 71) — `constexpr`, also nach der Abnahme
ausdrücklich zugelassen, und vom vorgeschriebenen Muster tatsächlich nicht gefunden, weil
der Name grossgeschrieben ist. Kein `static`, keine weitere Ablage. Eingebunden werden
`<array>`, `<cstddef>`, `<cstdint>` (über den Kopf) und `<stdexcept>` — nichts Fremdes;
`pruefstand/CMakeLists.txt` linkt nichts.

**Der zweite Nachweis.** `befunde/uebersetzung-2026-09-03.md` führt
`vorrat_verfahren_probe` namentlich und `Passed`, in beiden Bauwegen (10/10 im
Arbeitsbereich, 2/2 im Alleinbau). Ich habe den Lauf zusätzlich selbst angestossen und die
Ausgabe gelesen, nicht nur den Rückgabewert.

## Wonach ich gesucht und was ich nicht gefunden habe

**Abgeschwächte Zusicherungen in der Versionsgeschichte.** Beide Dateien haben zwei
Commits am 2026-09-03 (`688e845`, `50c916d`). Der Unterschied dazwischen ist
`+78 / −0`: acht Kommentarzeilen im Modul und die drei Zusicherungen zur Schranke von
`spiele` in der Probe. **Keine Zeile entfernt, keine Schwelle verschoben, kein Test
übersprungen.** Es gibt kein `#if 0`, kein auskommentiertes `pruefe(`, keinen
Frühausstieg vor dem Ende von `main`.

**Erwartungswerte, die der eigene Code erzeugt hat.** Keiner. Jeder Sollwert kommt aus
`spiel.md`/T43 (`3k·ai`, `(0,0,0,0,0)`, die Referenzfolge, 15 bzw. 45 Steckplätze) oder
wird im Test getrennt gerechnet (4a). `erste_vorratsabweichung` (Z. 307) vergleicht das
Modul gegen sich selbst — sie ist aber **reine Diagnoseausgabe** und trägt keine
Zusicherung; das habe ich eigens nachgesehen.

**Regeln ohne eigenen Anker.** Ich habe die acht Wirkungsketten aus `spiel.md` Z. 1296–1312
einzeln durchgezählt und für jede einen Mutanten gebaut. Jede wird gefangen. Drei sterben
an **genau einer** Zusicherung — das ist der Fingerzeig aus meinem Logbuch auf die dünne
Stelle, und hier ist er in allen drei Fällen sachlich begründet und kein Mangel:

- `mut04` (leerer Platz verrechnet doch) stirbt allein an Z. 557. Bei durchgehender
  Zulässigkeit bleibt nie ein Platz leer, also kann Bedingung 1 und 2 der Fehler nicht
  auffallen — genau deshalb verlangt die Abnahme 4a eigens.
- `mut10` (`leer_geblieben` zählt nicht) stirbt allein an Z. 564. Das Feld ist Buchhaltung
  mit einer beobachtbaren Stelle.
- `mut11`/`mut18` (Schranke) sterben an Z. 645 bzw. 644. Die Schranke steht nicht in der
  Abnahme; sie ist eine Zusage des Kopfes, und sie ist geprüft.

**Zusicherungen, die überhaupt nicht rot werden können.** Drei, und keine davon schwächt
eine der fünf Bedingungen:

- Z. 403 (die beiden Abschriften gegeneinander) vergleicht zwei Konstanten im Testcode.
  Sie *soll* von keiner Änderung am Modul abhängen — sie prüft den Massstab, nicht das
  Programm. Richtig so.
- Z. 643 (`spiele wirft über RUNDEN_HOECHSTENS`) lässt sich nicht isoliert rot bekommen:
  Jede Fassung, die 91 Runden annimmt, schreibt hinter das Ende von `Laufergebnis::folge`.
  Die Zusicherung ist der Zeuge ihrer eigenen Wache. Die Gegenrichtung ist über `mut11`
  belegt, die negative Seite über `mut18`.
- Z. 369 (`pruefe(!invariante_soll || !folge_soll, …)`) hängt allein an den beiden
  Literalen im Aufruf und ist für beide Aufrufstellen wahr — sie kann durch keine
  Codeänderung fallen. Sie bewacht eine **künftige Änderung der Aufrufstelle**
  (jemand, der `(true, true)` einträgt und damit behauptet, keine Bedingung fange die
  Fassung). Das ist ein zulässiger Zweck, und die drei Zusicherungen daneben
  (Z. 364/366/368) sind über `mut16` nachweislich tragend. **Kein Befund**, aber die
  Stelle sei benannt.

## Nebenbefund (kein Befund gegen dieses Paket)

Die Probe belegt dreimal mit einer Zeilennummer: `spiel.md` Zeile 1043 f. (Z. 25, 126, 463)
und Zeile 1015 (Z. 148). **Beide stimmten, als sie geschrieben wurden** — in `688e845`
stand die Referenzfolge in Zeile 1044 und das Referenzprofil in Zeile 1015; ich habe die
historische Fassung nachgeschlagen. `6537a9e` („spielentwerfer: 0039") hat `spiel.md` dann
am selben Tag verlängert, seitdem sind es Zeile 1318 f. und 1290. Eine der drei Stellen
wird zur Laufzeit **ausgedruckt** (Z. 463), zeigt also im Bericht auf die falsche Zeile.

Das ist dieselbe Bauart wie in den Paketen 0034, 0035 und 0044 und **kein Mangel der
Arbeit des Bauagenten**. Weil es eine Datei betrifft, die kein bestehendes Paket
beansprucht, ist daraus Vorschlag `0049-vorratsprobe-belegstellen` geworden — mit einer
Nummernkollision, die im Vorschlag selbst oben vermerkt ist: Parallel zu diesem Lauf ist
`0049-reihentoml-herkunft-und-selbstpruefung` entstanden, und `mv` war in dieser Sitzung
gesperrt. `0050` ist frei.

## Was ausdrücklich kein Befund ist

Dateiname, Benennung der Hilfsfunktionen, Ausgabeformat jenseits der genannten Zahlen,
und dass die beiden `Abweichung`-Fälle über Verzweigungen statt getrennter Hilfsfunktionen
gebaut sind. `specs/` schweigt dazu, also gilt die Entscheidung des Bauagenten.

## Urteil

`geprueft`. Alle fünf Abnahmebedingungen sind erfüllt und einzeln nachgewiesen. Die Probe
ist keine, die nur bestätigt, dass sich nichts ändert: Achtzehn absichtlich kaputte
Fassungen des Moduls werden alle gefangen, beide Kontrollläufe bleiben grün, und die drei
Stellen, an denen die Abnahme eine besondere Empfindlichkeit verlangt hat — `k = 3` neben
`k = 1`, die beiden falschen Fassungen gegeneinander, `ai = 0` gegen die Invariante —
tragen nachweislich und nicht nur dem Anschein nach.
