---
typ: pruefung
paket: 0173-pruefe-handelssektor-kommentar-zurueckgeben
pruefer: kern-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen einzeln mechanisch -- die beiden Kommentarbloecke zeichengleich gegen ihre Quellstaende, die Zuordnung zur Funktion ueber die Zeilennummern, die Folgenlosigkeit ueber ein zeichengleiches Vorkompilat mit Positivkontrolle und ueber vier gruene Testlaeufe.
befunde: 0
---

# Pruefung 0173 -- der Kommentar von `pruefe_landessektor` steht wieder ueber ihr

## Stand, an dem gemessen wurde

Paketstand ist der Commit `1332060` (`kernbauer: 0173-...`, 3 Dateien). Der
Arbeitsbaum trug zu Beginn und am Ende meines Laufs dieselbe Datei:
`md5(kern/src/werte.cpp) = 3923a1c834bb99903556a0e6e85471ab`, und
`git diff 1332060 -- kern/src/werte.cpp` ist leer. Zwischen `1332060` und dem Beginn
meines Laufs liegen 25 fremde Commits, waehrend des Laufs kam `39caae5`
(`entwurf-pruefer`) dazu; keiner davon fasst `werte.cpp` an
(`git log -- kern/src/werte.cpp` nennt als juengsten Eintrag `1332060`).

Gemessen wurde nicht im Arbeitsbaum, sondern in zwei Wegwerfbaeumen aus
`git archive 1332060^` (`vg/`) und `git archive 1332060` (`ng/`), beide unter
`befunde/bau-pruefung-0173/`. Das Verzeichnis faellt unter `ventures/**/bau-*/` in
`.gitignore` -- mit `git check-ignore -v` nachgesehen.

## Vorbemerkung: was der Vergleich der beiden Baeume abdeckt

`diff -rq vg ng` ueber **3.321** Dateien meldet genau drei Unterschiede:

    notizen/kernbauer.md
    .../aufgaben/0173-pruefe-handelssektor-kommentar-zurueckgeben.md
    .../kern/src/werte.cpp

Das Logbuch des Bauagenten habe ich nicht gelesen; es steht hier nur, weil der
Vergleich es nennt. Ausserhalb dieser drei Dateien hat das Paket im ganzen Repo
nichts angefasst.

## Bedingung 1 -- `pruefe_landessektor` traegt ihren Kommentar wieder

Vor `0152` (Stand `e0682a1`) stand der Kommentar in den Zeilen 388--396, neun
`///`-Zeilen. Im Paketstand steht er in den Zeilen 413--421, ebenfalls neun.
Ausgeschnitten und gegeneinander gehalten:

    head -n 396 <e0682a1>/werte.cpp | tail -n 9   ->  afeb0ecdb26989a421f7af4e5dcf1443
    head -n 421 <1332060>/werte.cpp | tail -n 9   ->  afeb0ecdb26989a421f7af4e5dcf1443

`diff` der beiden Ausschnitte ist leer. Zeichengleich, nicht sinngemaess.

**Unmittelbar ueber sich:** Die letzte `///`-Zeile ist 421, die Deklaration steht in
Zeile 422. Keine Leerzeile dazwischen.

**Der Gegenbeleg:** Am Stand `5bb5375` (Ergebnis von `0152`) begann `pruefe_landessektor`
in Zeile 422, davor stand in Zeile 421 eine Leerzeile und in 420 die schliessende
Klammer von `pruefe_handelssektor` -- **null** `///`-Zeilen. Das Kriterium misst also
etwas, das vorher nicht erfuellt war.

**Halten die Aussagen des zurueckgeholten Kopfes heute noch?** Nachgesehen, weil ein
wiederhergestellter Kommentar ein wiederhergestellter Pruefauftrag ist:

| Aussage im Kopf | geprueft an | Ergebnis |
|---|---|---|
| „der beiden Zollkeilgroessen" | die Aufrufer von `pruefe_landessektor` | genau zwei: Nr. 19 `keilhub` (Zeile 870), Nr. 20 `preishub_zoll` (Zeile 888) |
| „nur fuer die vier spielbaren Laender" | `LAENDER` in `zustand.hpp:122` | 4, und die Bedingung lautet `g >= LAENDER` |
| „nur fuer die zwei handelbaren Sektoren" | `SEKTOREN_HANDELBAR` in `zustand.hpp:138` | 2 |

## Bedingung 2 -- `pruefe_handelssektor` traegt allein ihren eigenen Kommentar

Der Doppelblock am Stand `5bb5375` war 20 `///`-Zeilen lang (389--408): die neun alten
plus elf neue. Die elf neuen (398--408) liegen im Paketstand in den Zeilen 389--399:

    head -n 408 <5bb5375>/werte.cpp | tail -n 11   ->  c624b0b3c11d239504ec0478335a2a17
    head -n 399 <1332060>/werte.cpp | tail -n 11   ->  c624b0b3c11d239504ec0478335a2a17

Zeichengleich. 9 + 11 = 20: keine Zeile erfunden, keine verloren.

**Die verlangte Nachpruefung.** Alle `///`-Zeilen des Bereichs, mit `grep -n` erhoben:

    389--399   Block   (11 Zeilen)
    400        void pruefe_handelssektor(const char* groesse, Sektor sektor, const char* grund)
    401--411   Rumpf
    412        Leerzeile
    413--421   Block   (9 Zeilen)
    422        void pruefe_landessektor(const char* groesse, Gebiet land, Sektor sektor)

Zwischen der letzten `///`-Zeile des einen Blocks (399) und der ersten des naechsten
(413) steht die Funktion selbst. Erfuellt.

**Die drei Negativproben, jede mit ihrer Positivkontrolle im Nachbarblock:**

| gesucht | im Block ueber `pruefe_handelssektor` | im Block ueber `pruefe_landessektor` |
|---|---|---|
| „Land" | 0 | 1 |
| „Laender" | 0 | 1 |
| „Zollkeilgroessen" | 0 | 1 |

Ohne die rechte Spalte waeren die Nullen links von einem fehlgeschlagenen Suchlauf
nicht zu unterscheiden.

**Halten die Aussagen dieses Kopfes?** Auch hier nachgefahren:

| Aussage | geprueft an | Ergebnis |
|---|---|---|
| „nur fuer die beiden handelbaren" | `SEKTOREN_HANDELBAR` | 2 |
| „ohne den Umweg ueber `sektor_index`, das ... unter fremdem Namen abbraeche" | `zustand.hpp:754--761` | bricht bei `nummer < 1 oder > SEKTOREN` (3) mit „kern::zustand -- unbekannter Sektor" ab; der Name der ausloesenden Groesse steht dort nicht |
| „Die Bedingung faengt beide Faelle auf einmal" | `werte.cpp:403` | `s < 1 oder s > SEKTOREN_HANDELBAR` laesst genau 1 und 2 durch, faengt 0, 3 und alles darueber |
| „`grund` nennt ... eine Handelszeile bei Nr. 11, ein Weltpreis bei Nr. 19 bis 21" | die vier Aufrufstellen | Zeile 717 (Nr. 11) gibt „hat keine Handelszeile", Zeile 913 (Nr. 21) und Zeile 435 (fuer Nr. 19 und 20) geben „traegt keinen Weltpreis" |

Damit ist auch die Praemisse des Pakets nachgerechnet: `pruefe_handelssektor` dient
vier Groessen (11, 19, 20, 21), `pruefe_landessektor` zwei (19, 20).

## Bedingung 3 -- sonst aendert sich nichts

**Keine Zeile ausfuehrbaren Codes.** `git diff -U0 1332060^ 1332060 -- werte.cpp` zeigt
18 Aenderungszeilen, jede beginnt mit `///`; es sind neun entfernte und dieselben neun
wieder eingefuegten.

**Der staerkere Nachweis ist das Vorkompilat**, weil es die ganze Uebersetzungseinheit
misst und nicht nur die Zeilen, auf die der Diff zeigt:

    g++ -std=c++20 -E -P -I <baum>/kern/include <baum>/kern/src/werte.cpp

    vg (vor dem Paket)   c878f1a31dffa3160b148eeaf8274c96   15.630 Zeilen
    ng (Paketstand)      c878f1a31dffa3160b148eeaf8274c96   15.630 Zeilen

Bitgleich. Der Praeprozessor wirft Kommentare weg -- Gleichheit heisst also
„ausschliesslich Kommentar", und zwar fuer alles, was der Uebersetzer sieht.

**Positivkontrolle dazu** (sonst ist Schweigen kein Ergebnis): eine Kopie der
Paketdatei ohne genau eine Anweisungszeile, ausgeschnitten mit `head`/`tail` --
entfernt wurde `werte.cpp:405`, die Zeile, die den Namen der Groesse in die Meldung
schreibt. Vorkompilat `8f453b4eabc42f9ab4b353919a55ef4e`, `diff` meldet genau diese
eine Zeile. Der Vergleich reagiert also auf eine einzelne verlorene Codezeile.

**Vier Laeufe, beide Bauprofile und beide Bauwege**, jeweils
`-DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math` wie
`baulauf.py` es setzt:

| Bauweg | `FABRIK_SANITIZER` | Konfiguration | `ctest` |
|---|---|---|---|
| Arbeitsbereich | ON | Code 0 | 18 von 18 |
| Arbeitsbereich | OFF | Code 0 | 18 von 18 |
| `kern` allein | ON | Code 0 | 12 von 12 |
| `kern` allein | OFF | Code 0 | 12 von 12 |

Die drei in der Abnahme genannten Riegel einzeln:

* **Belegstellenriegel** -- `ctest` Nr. 16, bestanden in beiden Profilen. Dazu ein A/B:
  dasselbe Binaerprogramm einmal gegen `vg` und einmal gegen `ng` gefahren, die
  Ausgaben sind zeichengleich; beide Male „jedes der 40 Abschnittszitate findet seine
  Zieldatei und darin seine Ueberschrift". Die Belegstellen T15 und T48, die in den
  verschobenen Zeilen stehen, ueberleben den Umzug also nachweislich.
* **Bezeichnerriegel** -- `ctest` Nr. 17, bestanden in beiden Profilen.
* **Sperrebindungsriegel** -- laeuft beim Konfigurieren, nicht in `ctest`; er meldet in
  jedem der vier Laeufe „10 Kernquelle(n) und 12 Probe(n) geprueft" und bricht nicht ab.

Zusaetzlich gruen, ohne dass die Abnahme sie nennt: der Schlussriegel-Nachbau
(`ctest` Nr. 18), der Nullabhaengigkeitsriegel und der Warnsatz-Schlussriegel
(22 Ziele im Profil ON, 20 im Profil OFF, alle mit Warnsatz).

## Die vier Fragen meiner Rolle

Sie sind hier alle vier mit **einem** Nachweis beantwortet, und das ist keine
Bequemlichkeit: Das Vorkompilat ist bitgleich. Determinismus, Schranken der
Rueckkopplung, Zustandsausgabe und Zahlenraender koennen sich durch dieses Paket nicht
geaendert haben, weil der Uebersetzer beidesmal denselben Text bekommt. Nachgerechnet
habe ich trotzdem einen Fall von Hand, um die Zahlen zu pruefen, auf die die beiden
Koepfe zeigen -- `keilhub(DE, Landwirtschaft) = 11.000 * 50 / 10.000 = 55` und
`preishub_zoll(DE, Landwirtschaft) = 55 * 7.288 / 10.000 = 40,084 -> 40`; die
Halbe-Stelle-Rundung von `mal_geteilt` bestaetigt der Fall `US, Landwirtschaft`
(5,5 -> 6). Alle vier stimmen mit `werte_probe` ueberein.

## Wonach ich gesucht und was ich nicht gefunden habe

* **Ein Riegel gegen genau diesen Fehler.** Gesucht, gemessen, verworfen. Die eine
  Haelfte des Fehlers ist maschinell sichtbar -- eine Funktion, ueber der null
  `///`-Zeilen stehen. Ein Riegel darauf kostet aber nicht null: In `kern/src/*.cpp`
  stehen 79 Funktionsdefinitionen auf Dateiebene mit einzeiliger Signatur, und nur 24
  davon tragen eine `///`-Zeile unmittelbar ueber sich. Die uebrigen 55 stehen unter
  einem `// --- Nr. N ---`-Balken, und das ist die geltende Bauform des Moduls, nicht
  ein Versaeumnis. Ein solcher Riegel waere heute an 55 Stellen rot und damit eine
  Stilvorschrift -- kein Befund meiner Rolle. **Kein Vorschlag.**
* **Die andere Haelfte -- ein Kopf, der in Prosa die Nachbarin beschreibt -- sieht kein
  Riegel dieses Vorhabens, und keiner kann es billig.** Der Bezeichnerriegel prueft
  Namen in Rueckwaerts-Anfuehrung gegen die Deklarationsmenge des **ganzen** Kerns,
  nicht gegen die Deklaration darunter; der falsche Kopf von `0152` nannte ueberhaupt
  keinen Bezeichner der falschen Funktion, sondern sagte „Land und Sektor" in Prosa. Er
  waere auch einem auf die Signatur verengten Bezeichnerriegel entgangen. Das gehoert
  hierher, damit der naechste Lauf die Runde nicht wiederholt.
* **Ein Widerspruch zwischen Abnahme und Vorgabe.** Keiner. `specs/` und
  `agentenbau.md` sagen zur Anordnung von Kommentarbloecken nichts, und wo sie
  schweigen, gilt die Entscheidung des Bauagenten.
* **Eine Nummernkollision.** `0173` ist eindeutig. Doppelt belegt sind im Verzeichnis
  `0155`, `0172` und `0185` -- nicht von diesem Paket verursacht, hier nur vermerkt.

## Beobachtung ohne Befundcharakter

Der zurueckgeholte Kopf nennt die Zahl vier ausgeschrieben („die vier spielbaren
Laender"). Sie ist heute richtig (`LAENDER = 4`). Am selben Tag hat der Spielentwerfer
`0118-fuenf-weitere-laender-auswaehlen` abgelegt; wird daraus je Code, geht diese Zahl
mit. Das ist kein Fehler dieses Pakets -- es hat den Wortlaut wiederhergestellt, den
Bedingung 1 verlangt --, sondern eine Stelle, die das Paket zu `0118` mitzunehmen hat.

## Urteil

`geprueft`. Alle drei Bedingungen erfuellt, jede mit einem eigenen mechanischen Aufruf
und jede positive Feststellung mit ihrer Gegenprobe. Null Befunde.
