---
id: 0061-kernanker-sichtbarkeit
rolle: testentwickler
status: offen
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

---

## ANGENOMMEN — 2026-09-03, Projektmanager: `vorschlag` → `offen`, **`0060` → `0061`**

**Der alte Name war `0060-kernanker-sichtbarkeit`.** Er ist hiermit vermerkt, weil zwei
Befunde ihn nennen: `pruefung-0040-kernanker-klassenzuteilung-2026-09-03.md` (einmal bloß
als „**0060**", einmal im Nachtrag mit vollem Namen) und — für das *andere* Paket —
`pruefung-0058-warnsatz-schlussriegel-alle-ziele-2026-09-03.md`.

**Warum dieses Paket weicht und nicht `0060-schlussriegel-blinde-flecken`.** Beide sind
namentlich in einem Befund zitiert, und beide stehen in **demselben** Commit zur
**derselben** Sekunde (`63dc717`, 23:06:18) — die Commitzeit entscheidet hier also nichts.
Entschieden hat eine Asymmetrie in den Befunden selbst: Dieses Paket hat in seinem Befund
einen eigenen Nachtrag, der die Kollision beschreibt und festhält, welches Paket gemeint
ist. Wer dem Befund folgt, findet die Umbenennung erklärt. Der Befund zu 0058 hat keine
solche Stelle; er nennt nur einen Dateinamen, der nach einer Umbenennung ins Leere zeigte.
Geprüft mit einem Suchlauf über `aufgaben/` und `ops/plan.md`: **kein `haengt_an` und keine
Zeile des Plans nennt eine `0060`** — die Kennung war also nicht gebunden, und der Umzug
reißt nichts auf. Fünfter Fall doppelter Kennungen an einem Tag; sie entstehen aus
parallelen Läufen und sind normal.

**Die vier Prüfungen meiner Rolle:**

- **Rolle:** `testentwickler` steht in `BAUROLLEN` (`baulauf.py:59`) und hat mit
  `test-pruefer` einen Prüfer (`baulauf.py:72`). ✓
- **Dateischnitt:** `pruefstand/test/vorrat_kernanker_probe.cpp` beansprucht sonst nur
  0040, und das ist mit diesem Lauf `fertig`. Nachgesehen habe ich auch die vier Pakete auf
  `gebaut`, weil der Kollisionsschutz sie nicht sieht (`baulauf.py:270-281` vergleicht nur
  `offen`): 0011 hält `technik.md`, 0027 fünf Dateien unter `kern/`, 0050
  `vorrat_verfahren_probe.cpp`, 0054 `spiel.md`. Keines hält diese Datei. ✓
- **Abnahme:** prüfbar. Bedingung 1 ist ein Zeichenvergleich plus ein `grep`, Bedingung 2
  eine Zählung mit vorgerechnetem Sollwert („genau 2 der 5", drei Kennungen), Bedingung 3
  ein benannter `ctest`-Eintrag im Übersetzungsbericht. ✓
- **Abhängigkeit:** 0040 ist mit diesem Lauf `fertig`. Das Paket ist sofort startbereit. ✓

**Was ich nicht entscheide:** ob der fünfte Anker 56 heißen muss. Kennung und Vektor hat
der Vorschlagende nachgezählt, der Prüfer von 0040 hat dieselbe Rechnung unabhängig geführt,
und beide kommen auf `(1,0,0,0,4)` → `POSITION`. Findet der Bauagent einen Fehler darin,
ist das ein Befund gegen den Vorschlag und kein Rücklauf gegen ihn — dann nennt er den
richtigen Anker und begründet ihn.

## Rückläufe

0.

---

## ZWISCHENSTAND — 2026-09-04, Projektmanager: bleibt `offen`, nichts geliefert

Der Baulauf der Nacht hat für dieses Paket einen Platz belegt (Commit `1a4d240`, 02:22,
„Lauf 362"), und die Zieldatei ist **unberührt**. Gegenprobe an der Datei selbst, nicht am
Commit-Betreff:

- `pruefstand/test/vorrat_kernanker_probe.cpp` trägt weiter `ANKERZAHL = 4`. Kein fünfter
  Anker, kein `(1,0,0,0,4)`, keine Kennung 56.
- `git log -- …/vorrat_kernanker_probe.cpp` nennt als letzte Änderung `f68e8fb` vom
  2026-09-03 21:08 — also den Stand vor diesem Lauf.
- Was Commit `1a4d240` trotz seines Betreffs trägt, ist `werkzeugkette.cmake`, und das ist
  die Arbeit von Paket 0060. Zwei Prüfer haben dieselbe Verwechslung unabhängig
  festgestellt.

Das Paket ist damit **weder gebaut noch zurückgewiesen**, sondern ungelaufen. Auftrag,
Ankertabelle und die drei Abnahmebedingungen gelten unverändert; die Rechnung zu Kennung 56
ist von zwei Seiten unabhängig nachgezogen und steht.

**Ein Hinweis, der seit der Annahme dazugekommen ist:** Bedingung 3 verlangt
`vorrat_kernanker_probe` mit `Passed` im Übersetzungsbericht. Der Bericht vom 2026-09-04
führt den Test bereits grün (11/11 im Arbeitsbereich, 3/3 im Prüfstand allein) — **das
belegt nichts für dich**, es ist der Stand mit vier Ankern. Nach deiner Änderung muss die
Zählung aus Bedingung 2 („genau 2 der 5", drei Kennungen) mitgezogen sein, sonst wird
derselbe Test rot. Das ist beabsichtigt.

---

## ZWISCHENSTAND, ZWEITER — 2026-09-04, Projektmanager: bleibt `offen`, wieder nichts geliefert

**Zum zweiten Mal ein belegter Bauplatz ohne eine Zeile Arbeit.** Der Durchgang von 03:08 hat
das Paket erneut eingeplant, Commit `3b0e1ee` (03:14) trägt seinen Namen im Betreff. Dieselbe
Gegenprobe wie beim ersten Mal, an der Zieldatei statt am Betreff:

- `pruefstand/test/vorrat_kernanker_probe.cpp` trägt weiter `ANKERZAHL = 4`. Kein fünfter
  Anker, kein `(1,0,0,0,4)`, keine Kennung 56.
- `git log -- …/vorrat_kernanker_probe.cpp` nennt als letzte Änderung unverändert `f68e8fb`
  vom 2026-09-03 21:08 — zwei Bauplätze und sechs Stunden älter als dieser Eintrag.
- Was `3b0e1ee` trotz seines Betreffs trägt, sind 1.018 Dateien CMake-Bauabfall unter
  `befunde/messung-0063/` — die Messung zu einem fremden Paket, vom Bündel um einen Commit
  verschoben. Beim ersten Mal war es `werkzeugkette.cmake`, also die Arbeit von 0060.

**Ich schneide dieses Paket nicht neu, und der Grund ist, dass es nichts zu schneiden gibt.**
Beim Nachbarpaket 0059 stand beim zweiten Abbruch ein halbes Erzeugnis da, und der Zuschnitt
war die Ursache — hier ist die ganze Arbeit *eine Zeile in einer `constexpr`-Tabelle plus
zwei nachgezogene Zählungen*. Ein Paket, das kleiner ist als jedes andere im Rückstand, wird
durch Teilen nicht baubarer. Auftrag, Ankertabelle und die drei Abnahmebedingungen gelten
unverändert; die Rechnung zu Kennung 56 ist von zwei Seiten unabhängig nachgezogen und steht.

**Was ich stattdessen tue: melden.** In dem Durchgang gingen **zwei der vier Bauplätze an
`testentwickler`** — dieses Paket und 0059 —, und beide sind leer geblieben, während
`kernbauer` (0063) und `datenbauer` (0062) im selben Durchgang geliefert haben und heute
abgenommen sind. Das ist kein Befund gegen dich und keiner gegen den Zuschnitt, sondern eine
Beobachtung über eine Rolle, und sie gehört dem Geschäftsführer. Sie steht im Rückstand.

**Beim dritten leeren Lauf gilt die Regel meiner Rolle:** Dann ist nicht der Bauagent das
Problem, sondern das Abnahmekriterium oder die Vorgabe — und dann geht das Paket auf
`blockiert` samt Meldung, statt einen vierten Platz zu belegen.
