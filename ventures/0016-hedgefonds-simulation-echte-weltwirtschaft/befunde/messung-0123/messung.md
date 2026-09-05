---
typ: messung
paket: 0123-mal-kopf-behauptet-null-aufrufer
rolle: kernbauer
datum: 2026-09-05
bezugsstand: f6731fe (gemessen), nachgemessen auf 7a4183b
---

# Messung zu 0123 -- die Zahl der Aufrufer von `mal`

## Was gemessen wurde und womit

Zwei voneinander unabhaengige Verfahren auf demselben Baum, weil die Abnahme die
Zahl **selbst gemessen** verlangt und der Vorschlag sie bereits nennt. Wer eine
fremde Zahl bestaetigt findet, hat sie wiederholt; zwei Verfahren, die einander
nicht kennen, sind der billigste Ersatz fuer einen echten Riegel.

**Verfahren A** -- Mustervergleich ueber `kern/`, `pruefstand/` und `werkzeuge/`,
ausserhalb von `bau/` und `befunde/`, mit Wortgrenze vor dem Namen (faengt damit
weder `mal_geteilt` noch das Wortende von `normal`).

**Verfahren B** -- dasselbe, aber je Zeile zuerst der Zeilenkommentar entfernt, so
dass ein `mal(` in einem Kommentar nicht mitzaehlt.

## Das Ergebnis, beide Verfahren gleich

| Ort | Aufrufstellen | Art |
|---|---|---|
| `kern/src/werte.cpp` | 5 | echte Aufrufe -- die gezaehlten |
| `kern/test/festkomma_probe.cpp` | 13 | pruefen `mal`, nicht mitgezaehlt |
| `kern/include/kern/festkomma.hpp` | 1 | die Vereinbarung selbst, kein Aufruf |
| `pruefstand/`, `werkzeuge/` | 0 | -- |

Die fuenf stehen in fuenf verschiedenen Funktionen -- `tsd_in_cent`,
`lobbypunkte_aus_geld`, `positionswert_aus`, `korbbestand`, `fondsanteil` --, die
Zahl ist also als Aufrufstelle und als Aufrufer dieselbe.

## Dass die Zahl gemessen und nicht abgeschrieben ist

Der Zaehler wurde an einem im Speicher veraenderten Abzug von `werte.cpp` gefahren;
keine Datei des Baums wurde dafuer angefasst.

| Eingabe | Zaehlung |
|---|---|
| unveraendert | 5 |
| ein sechster Aufruf angehaengt | 6 |
| der erste Aufruf durch `return 0` ersetzt | 4 |
| ein `mal(` nur im Kommentar angehaengt | 5 |

Er folgt dem Baum in beide Richtungen und faellt nicht auf Kommentartext herein.

## Der Bezugsstand, und warum er nicht nachgezogen ist

Gemessen wurde auf `f6731fe`, mit `kern/` unveraendert gegen diesen Stand. Waehrend
des Laufs hat ein fremder Lauf committet; `HEAD` steht seither auf `7a4183b`.
`werte.cpp` ist zwischen beiden Staenden **unveraendert**, die Zaehlung dort
unveraendert 5 an denselben Stellen.

Im Kopf von `mal` steht deshalb weiter `f6731fe`. Das ist der Stand, auf dem die
Messung wirklich lief; `7a4183b` hineinzuschreiben waere genau die Sorte
uebernommener Zahl, die die Abnahme ausschliesst.

## Der Belegstellenriegel, vorher und nachher

Gegenprobe gegen den Einwand, der Kopf trage jetzt eine Belegstelle mehr. Gemessen
wurde mit der HEAD-Fassung der Datei am Platz und danach mit der neuen; die
Rueckgabe wurde auf Gleichheit geprueft.

| Zaehlwerk | vorher | nachher |
|---|---|---|
| Bedingung 1: Zeilenverweise / davon mit Dateinamen | 5 / 0 | 5 / 0 |
| Bedingung 2: Zitate / aufgeloest | 36 / 36 | 36 / 36 |
| davon ohne Anfuehrung | 14 | 14 |

## Uebersetzung und Tests

Beide Profile, gebaut nach `$TMPDIR` statt nach `bau/`, damit der Baulauf nicht
gestoert wird. Nach dem Fremdcommit noch einmal vollstaendig wiederholt:

| Profil | cmake | build | ctest |
|---|---|---|---|
| `FABRIK_SANITIZER=ON` | 0 | 0 | 14 von 14 gruen |
| `FABRIK_SANITIZER=OFF` | 0 | 0 | 14 von 14 gruen |

## Was diese Messung nicht zeigt

**Kein Test wird rot, wenn die Zahl im Kopf falsch wird.** Die Abnahme ist eine
Aussage ueber den Wortlaut eines Kommentars, und dafuer gibt es hier keinen Riegel;
eine Mutation, die das belegen koennte, existiert nicht. Genau daran ist der alte
Satz vier Pakete lang unbemerkt veraltet.

Was dagegen haelt, ist keine Pruefung, sondern die Form: Der Satz nennt Datum und
Stand, unter dem er gilt. Er kann veralten, aber er kann nicht mehr behaupten,
zeitlos zu sein.
