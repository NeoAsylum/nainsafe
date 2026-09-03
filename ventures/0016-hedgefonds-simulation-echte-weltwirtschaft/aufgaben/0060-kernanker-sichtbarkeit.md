---
id: 0060-kernanker-sichtbarkeit
rolle: testentwickler
status: vorschlag
haengt_an: [0040-kernanker-klassenzuteilung]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/test/vorrat_kernanker_probe.cpp]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# T36 schliesst zwei Arten aus, die Anker nageln eine davon fest

Vorgabe: `technik.md` T36, Absatz „Strategiekern, vierwertig" — **„Hebel und
Sichtbarkeit gehen nicht ein."** Zwei Arten, ein Satz.

Paket 0040 hat vier Anker eingebaut, und einer davon nagelt den **Hebel** fest:
Kennung 60, `(1,0,0,4,0)` — `a4 = 4` ist der grösste Anteil des ganzen Profils und darf
den Kern trotzdem nicht bestimmen. Für die **Sichtbarkeit** gibt es kein Gegenstück.
In den Ankern 20, 44 und 60 ist `a5 = 0`; in Anker 76 ist `a5 = 1` und damit im
Gleichstand mit allem anderen. Kein Anker stellt die Frage, ob `a5` gewinnen darf.

## Der Befund, gemessen

Nicht vermutet, sondern gebaut. Eine Mutation des Moduls, die die Familie auf
`{a1, a2, a3, a5}` setzt — Sichtbarkeit zählt mit, Hebel nicht mehr —, laeuft gegen die
**unveraenderte** Probe aus 0040 vollstaendig gruen durch:

```
bestanden -- 0 Pruefung(en) fehlgeschlagen
```

Alle vier Anker bestehen, weil keiner sie unterscheidet: 20 `(0,0,5,0,0)`, 44
`(0,2,2,1,0)` und 60 `(1,0,0,4,0)` haben `a5 = 0`, und 76 `(1,1,1,1,1)` faellt beim
Dreifachgleichstand auf denselben kleinsten Index. Zum Vergleich: Vier andere
Mutationen desselben Moduls machen die Probe mit 6 bis 15 fehlgeschlagenen Zusicherungen
rot. Die Luecke ist keine Schwaeche der Probe im Ganzen, sondern genau eine fehlende
Zeile in ihrer Ankertabelle.

Gefangen wird die Mutation heute allein von `vorrat_probe.cpp` (Paket 0019), und dort
nur ueber die **Zaehlung**: „genau 6 Profile tragen den Kern ohne" reisst, weil unter
der Mutation nur noch `(0,0,0,5,0)` kernlos ist. Das ist ein Nachweis, der keine Klasse
benennt — also derselbe Zustand, gegen den 0040 ueberhaupt geschrieben wurde, eine Art
weiter geschoben.

## Warum das ein eigenes Paket ist

**Es ist kein Ruecklauf gegen 0040.** Die vier Anker hat das Paket 0040 selbst
vorgegeben, mit Kennung, Vektor und Klasse; der Bauagent hat genau sie eingebaut, und
alle vier stimmen. Die Frage, ob `a5` gewinnen darf, steht in keiner der vier
Abnahmebedingungen — sie ist keine gesenkte Bedingung, sondern eine, die nie gestellt
wurde. Wer 0040 daran misst, hebt ein bestandenes Kriterium nachtraeglich an.

**Es ist auch kein Ruecklauf gegen 0019.** Dessen fuenf Bedingungen nennen die Zahlen
126, 76, 0–5, 6 und 120, alle fuenf erfuellt. Welche Art in den Kern eingeht, steht dort
nicht.

**Und es ist zu klein zum Warten.** Eine Zeile in der `constexpr`-Tabelle, kein neuer
Aufbau, keine neue Datei. Der Aufwand liegt im Nachrechnen des Ankers, und das ist unten
schon getan.

## Was du baust

Einen fuenften Anker in `ANKER`, an derselben Stelle und in derselben Form wie die
anderen vier. `ANKERZAHL` geht von 4 auf 5; alles andere in der Datei ist ueber
`ANKERZAHL` geschrieben und braucht keine Aenderung.

| Kennung | Vektor | erwarteter Kern | bei Abweichung | was er festnagelt |
|---:|---|---|---|---|
| 56 | `(1,0,0,0,4)` | `POSITION` | `POSITION` | Sichtbarkeit ist mit 4 der groesste Anteil und geht **nicht** ein |

Beide Klassen sind von Hand nachgerechnet: Die Familie ist `(1,0,0)`, der groesste
Anteil steht bei Index 0, es gibt keinen Gleichstand — also `POSITION`, und der
Gleichstandsbrecher kommt nicht zum Zug, gleich in welche Richtung er zeigt. Die
Kennung ist abgezaehlt: `a1 = 0` umfasst die Kennungen 0..55 (`C(8,3) = 56`), also ist
56 der erste Vektor mit `a1 = 1`, und das ist `(1,0,0,0,4)`.

Der Anker ist das Gegenstueck zu 60 und steht sinnvollerweise davor — 56 vor 60 haelt
die Tabelle nach Kennung aufsteigend.

## Abnahme

1. **Der fuenfte Anker steht als Festwert und wird einzeln geprueft**, mit Vektor und
   Klasse wie die vier anderen, und die Ausgabe nennt zu ihm Kennung, Vektor, gefundene
   und erwartete Klasse. Kein zweites `strategiekern` — die Bedingung 2 aus 0040 gilt
   unveraendert weiter, und `grep -c 'anteile\['` zeigt weiter keinen Vergleich zweier
   Anteile gegeneinander.
2. **Die Zaehlungen der Vorfuehrung sind nachgezogen und stimmen wieder.** Die
   Abweichung „Gleichstand an die groessere Kennung" wird von 44 und 76 gefangen und
   von 20, **56** und 60 durchgelassen: aus „genau 2 der 4" wird „genau 2 der 5", und
   die Liste der Durchgelassenen nennt drei Kennungen. Wer nur die Tabelle erweitert
   und die Zahl 2-von-4 stehen laesst, macht die Probe rot — das ist beabsichtigt und
   der Grund, warum diese Bedingung hier steht.
3. **Der Uebersetzungslauf fuehrt sie aus.** In `befunde/uebersetzung-<datum>.md` steht
   unter `ctest --test-dir …/pruefstand/bau` ein Test `vorrat_kernanker_probe` mit
   `Passed`. Kein Gleitkomma, keine Fremdabhaengigkeit, keine veraenderliche Ablage
   ausserhalb einer Funktion ausser dem Fehlerzaehler.

## Hinweis an den Projektmanager

Die `dateien`-Liste ist dieselbe wie die von 0040. Beide duerfen deshalb **nicht**
gleichzeitig geplant werden; 0040 ist seit dem 2026-09-03 `gebaut` und heute geprueft,
also ist der Weg frei.

## Rückläufe

0.
