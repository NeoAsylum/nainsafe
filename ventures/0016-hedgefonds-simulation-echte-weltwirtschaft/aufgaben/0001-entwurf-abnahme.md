---
id: 0001-entwurf-abnahme
rolle: spielentwerfer
status: fertig
haengt_an: []
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md, specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die fünf Bedingungen unten, alle fünf. Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Abnahmekriterium für den Entwurf

Der Entwurfsprüfer hat zweimal geschrieben, es gebe kein Arbeitspaket, und sich
ersatzweise ein eigenes Kriterium gegeben. Das ist der Grund, warum die Befundzahl von
acht auf zwölf gestiegen ist: **Ohne Kriterium findet eine Entwurfsprüfung beliebig
lange etwas**, weil jeder Entwurf beliebig genauer werden kann.

Hier steht, wann er fertig ist. Nicht „fehlerfrei" — **baubar**.

## Die fünf Bedingungen

1. **Jedes der vier Maße hat eine Rechenvorschrift, die ein Programmierer ohne
   Rückfrage umsetzen könnte.** Kein „strukturell verschieden", kein „geeignet
   gewählt". Eingabe, Rechenweg, Ausgabe, Schwelle.

2. **Jede Größe, die im Modell vorkommt, ist entweder auf eine Reihe aus `daten.md`
   zurückgeführt oder ausdrücklich als Modellkonstrukt gekennzeichnet** — mit der
   Regel, wie sie aus vorhandenen Größen entsteht. Eine undefinierte Größe ist ein
   Befund; eine als Konstrukt gekennzeichnete ist keiner.

3. **`spiel.md` und `technik.md` widersprechen sich in keiner Zahl.** Wo beide dieselbe
   Größe nennen, nennen sie denselben Wert.

4. **Der Rückvergleich ist durchführbar**: Startjahrgang belegt, Sollreihen für diesen
   Jahrgang vorhanden, Abnahmeregel vorhanden — ab welchem Abstand gilt er als
   bestanden.

5. **Jeder Befund der Vorrunde ist beantwortet** mit *behoben*, *anders gelöst* oder
   *widersprochen*.

## Was ausdrücklich kein Befund mehr ist

- Eine Zahl, die noch kalibriert werden muss, solange sie als kalibrierbar
  gekennzeichnet ist und in der Parameterdatei steht. **Balance wird gemessen, nicht
  entworfen** — dafür gibt es den Selbstspieler.
- Eine Regel, deren Wirkung erst im Lauf sichtbar wird. Dafür gibt es den Prüfstand.
- Genauigkeit, die über die fünf Bedingungen hinausgeht. Ein Entwurf, der alle fünf
  erfüllt, ist abzunehmen, **auch wenn sich weitere Verbesserungen denken lassen** —
  die gehören dann in Arbeitspakete, nicht in eine dritte Entwurfsrunde.

## Wenn es dreimal zurückgeht

Dieses Paket geht höchstens dreimal zurück. Danach ist nicht der Entwerfer das Problem,
sondern dieses Kriterium — dann `blockiert` und eine Meldung an den Geschäftsführer,
der es dem Betreiber vorlegt.

**Der Zähler steht bei 1, nicht bei 3.** Nachgetragen am 2026-09-01, damit die Zahl
nicht stillschweigend zurechtgebogen wird: Die Rückläufe der Runden 1 und 2 sind gegen
ein Kriterium ergangen, das der Prüfer sich selbst gegeben hatte, weil es dieses Paket
noch nicht gab — er hat das in beiden Befunden ausdrücklich vermerkt. Gegen *diese* fünf
Bedingungen ist bisher **einmal** geprüft worden, und die Befundzahl ist dabei von zwölf
auf drei gefallen.

Zwei weitere Rückläufe gegen dieses Kriterium sind erlaubt. Dann `blockiert`.

| Runde | Kriterium | Befunde | Urteil |
|---|---|---:|---|
| 1 | selbst gegeben | 8 | zurück |
| 2 | selbst gegeben | 12 | zurück |
| 3 | **dieses Paket** | 3 | zurück — Zähler 1 von 3 |

---

## Abgeschlossen am 2026-09-01 — vom Betreiber entschieden

Der Entwurf ist **fünfmal** zurückgegangen. Damit ist die Regel dieses Pakets gefallen:
*Danach ist nicht der Entwerfer das Problem, sondern dieses Kriterium.*

**Die Messung, die das belegt:**

| Runde | Befunde | `spiel.md` | `technik.md` |
|---|---:|---:|---:|
| 1 | 8 | 23 kB | — |
| 2 | 12 | 38 kB | 35 kB |
| 3 | 3 | | |
| 4 | 2 | 70 kB | 109 kB |
| 5 | *(leer)* | | |
| 6 | 2 | 94 kB | 148 kB |

Die Befunde stagnieren bei zwei, während die Dokumente sich vervierfacht haben. Jede
Runde schreibt der Entwerfer Material nach, und im neuen Material findet der Prüfer zwei
neue Lücken. Das terminiert nicht.

**Woran es lag — Bedingung 2 war falsch gestellt.** Sie verlangt, dass *jede* Größe in
Prosa zurückgeführt ist. Bei 242 kB Spezifikation ist das die Arbeit eines Compilers,
nicht eines Lesers: Undefinierte Symbole und Einheitenfehler findet `rustc` in fünf
Sekunden und vollständig, ein Prüfer in zwanzig Minuten und stichprobenweise. Der
Entwurf war zu Quelltext in Prosaform geworden, und Prosa lässt sich nicht typprüfen.

**Die beiden letzten Befunde sind echt und bleiben es.** Sie werden nicht weggewischt,
sondern zu Arbeitspaketen 0002 und 0003 — dort trifft sie ein Werkzeug, das sie
vollständig findet.

**Was daraus als Regel bleibt** (siehe `konzeptlauf.py:RUECKLAUF_MAX`): Ein Entwurf ist
fertig, wenn ein Bauagent anfangen kann — nicht, wenn kein Prüfer mehr etwas findet. Das
zweite Kriterium ist bei wachsenden Dokumenten nie erfüllt.
