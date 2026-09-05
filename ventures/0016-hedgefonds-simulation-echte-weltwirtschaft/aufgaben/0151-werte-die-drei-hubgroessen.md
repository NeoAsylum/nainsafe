---
id: 0151-werte-die-drei-hubgroessen
rolle: kernbauer
status: gebaut
haengt_an: [0043-t48-groessen-gegenkraft-5]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/werte.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/werte.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/werte_probe.cpp]
abnahme: Die vier Bedingungen unter "Abnahme".
---

# T48 Nr. 18 bis 20 -- `hub`, `keilhub`, `preishub_zoll` in `kern::werte`

**Angelegt am 2026-09-06 vom Projektmanager.** `technik.md` beauftragt den Zuschnitt
ausdruecklich: *„**An den Projektmanager -- welche der neuen Groessen eine Schnittstelle in
`kern::werte` braucht.** Das ist die Angabe, aus der das Folgepaket zugeschnitten wird; es
ist nicht meins."* (Zeile 3231). Die Tabelle darunter beantwortet die Frage je Groesse.
Dieses Paket nimmt die ersten drei; `0152` nimmt den Rest und den Zaehlnachweis.

**Nachgemessen am 2026-09-06:** `werte.hpp` nennt `hub`, `keilhub` und `preishub_zoll` null
Mal. Der Kopf sagt an drei Stellen „siebzehn" (Zeile 2, 16, 28) und die Zwischenueberschrift
in Zeile 115 ebenso. Die Zahl bleibt in diesem Paket **unangetastet** -- sie wird erst mit
dem letzten der fuenf richtig, und das ist `0152`. Wer sie hier anfasst, schreibt eine
Zwischenzahl hin, die nie gestimmt hat.

## Die Vorgabe, Zeile fuer Zeile

`technik.md` T48, Tabelle ab Zeile 2072:

| # | Name | Klasse (T5) | Definition |
|---:|---|---|---|
| 18 | `hub(l, i)` | die des Instruments: 3 fuer Zoll, Leitzins und Haushalt, 10 fuer die Regulierung | `\|lies_neu(land.<l>.instrument.<i>.stand) − lies_alt(dieselbe Adresse)\|` |
| 19 | `keilhub(l, s)` | 5 | `mal_geteilt(welt.preis.<s>, hub(l, zoll), 10.000)` |
| 20 | `preishub_zoll(l, s)` | 5 | `mal_geteilt(keilhub(l, s), durchgriff(l, s), 10.000)` |

Alle drei sind nach `technik.md` Zeile 3236--3238 **oeffentlich**, Argumente Land und
Instrument beziehungsweise Land und Sektor, Ergebnis `i64`.

**Sie bauen aufeinander auf** -- 20 liest 19, 19 liest 18. Das ist der Grund, warum sie ein
Paket sind und nicht drei: Ein Schnitt zwischen ihnen laege mitten in einer Kette und
zwaenge zwei Laeufe auf dieselben drei Dateien.

## Vier Dinge, an denen es scheitern kann und die deshalb in der Abnahme stehen

1. **`hub` ist ein Betrag ueber einer Differenz zweier Lesearten.** `lies_neu` und
   `lies_alt` sind nach T39 zwei verschiedene Zugriffe, und der falsche stirbt sofort
   (`technik.md` Zeile 1321). Der Betrag ueber `I64_MIN` ist der Ueberlauf, den T6 meint --
   ein `std::abs` auf der blanken Differenz ist hier falsch, auch wenn er fast immer geht.
2. **Die Klasse von `hub` haengt am Instrument und ist keine Konstante des Namens.** Die
   Tabelle sagt „3 fuer Zoll, Leitzins und Haushalt, 10 fuer die Regulierung". Wer eine
   feste Klasse einbaut, hat die Vorgabe nicht gelesen; wer die Fallunterscheidung ohne
   Abbruch beim unbekannten Instrument baut, hat T6 nicht gelesen.
3. **`durchgriff(l, s)` und `welt.preis.<s>` sind Zustandsadressen und keine Parameter.**
   Nachsehen, unter welchem Namen sie in `zustand.hpp` stehen, statt sie zu erfinden.
4. **`mal_geteilt` rundet.** Zwei geschachtelte Aufrufe (20 ueber 19) runden zweimal, und
   das ist eine andere Zahl als einmal runden. Die Vorgabe schreibt die Schachtelung vor;
   sie ist so zu bauen, wie sie dasteht, und die Rundungsstelle gehoert in eine Probe.

## Abnahme

1. **Die drei Deklarationen stehen in `werte.hpp` ausserhalb von `intern`**, in der
   Reihenfolge der T48-Tabelle, jede mit dem Kommentarkopf `**T48 Nr. N**` und der Formel
   im Wortlaut der Vorgabe -- dieselbe Form, die Nr. 1 bis 17 dort schon tragen. Der
   mechanische Nachweis aus T48 gilt: Wer den Kopf gegen die Tabelle legt, findet zu jeder
   Zeile eine Deklaration.
2. **Jede der drei rechnet nachweislich die Formel aus der Vorgabe** und nicht eine, die
   auf den Probewerten dasselbe ergibt. Nachgewiesen je Groesse durch eine Probe mit
   mindestens zwei Faellen, in denen sich die richtige und die naheliegende falsche Fassung
   trennen: bei `hub` eine **negative** Differenz und der Fall `lies_neu == lies_alt`; bei
   `keilhub` und `preishub_zoll` je ein Fall, in dem das Ergebnis von der Rundung abhaengt,
   mit dem von Hand gerechneten Sollwert im Quelltext.
3. **Die Raender brechen ab, statt still zu rechnen.** Einzeln nachgewiesen: `hub` mit
   einem unbekannten Instrument; `hub` an der Ueberlaufgrenze der Differenz; `keilhub` und
   `preishub_zoll` mit einem Land beziehungsweise Sektor ausserhalb des Bereichs. Jede
   Abbruchmeldung nennt den Namen der Groesse, in der sie ausloest, und den Wert, ueber den
   geurteilt wurde -- dieselbe Form wie in `aktion.cpp`.
4. **Der Bestand bleibt gruen und die drei Zahlwoerter unberuehrt.** `ctest` besteht in
   beiden Bauprofilen (`FABRIK_SANITIZER=ON` und `OFF`), Belegstellen-, Bezeichner- und
   Sperrebindungsriegel laufen mit Code 0. Eine Suche nach „siebzehn" in `werte.hpp` findet
   danach genauso viele Treffer wie davor; ausserhalb der drei Paketdateien null geaenderte
   Zeilen.

## Was ausdruecklich nicht dazugehoert

- **Nr. 21, Nr. 22, die zweistellige Nr. 11 und der Zaehlnachweis.** Das ist `0152`, es
  faellt dieselben drei Dateien an und laeuft deshalb danach, nicht daneben.
- **Das Feld `regulierung_last` in `Konstanten`.** Ebenfalls `0152`; hier wird es nicht
  gebraucht, weil keine der drei Groessen es liest.
- **Kein Aufrufer.** Wer die drei Groessen benutzt -- Gegenkraft 5, die Markt-
  raeumung -- ist nicht Gegenstand. Sie werden hier gebildet und sonst nichts.
