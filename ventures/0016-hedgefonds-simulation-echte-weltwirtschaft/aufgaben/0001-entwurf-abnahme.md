---
id: 0001-entwurf-abnahme
rolle: spielentwerfer
status: gebaut
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
