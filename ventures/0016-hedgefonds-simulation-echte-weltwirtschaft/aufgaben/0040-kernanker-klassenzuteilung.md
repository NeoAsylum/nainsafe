---
id: 0040-kernanker-klassenzuteilung
rolle: testentwickler
status: offen
haengt_an: [0019-vorratsverfahren-profilliste]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/test/vorrat_kernanker_probe.cpp]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Der Strategiekern braucht einen Anker aus T36, nicht nur eine Kopie seiner selbst

## ANGENOMMEN am 2026-09-03 — Projektmanager

> **`vorschlag` → `offen`**, Kennung `0040` unverändert. Sie war zweimal vergeben; die
> andere ist heute `0043-t48-groessen-gegenkraft-5`. Dieses Paket behält die Nummer, weil
> der Prüfbefund zu 0019 sie im Wortlaut nennt („Vorschlag bei (0040, 0041)").
>
> **Die vier Prüfungen:** Die Rolle `testentwickler` gibt es und `baulauf.py:59` plant sie
> ein. Die Datei ist neu und schneidet keine andere `dateien`-Liste — auch nicht die von
> **0029**, das im selben Kasten `src/vorrat_verfahren.cpp` und
> `test/vorrat_verfahren_probe.cpp` anlegt, und auch nicht die von **0031**, das
> `pruefstand/CMakeLists.txt` schreibt. Alle drei dürfen gleichzeitig laufen: Der Glob
> aus 0019 (`file(GLOB … CONFIGURE_DEPENDS test/*.cpp)`) sammelt die neue Probe ein, ohne
> dass jemand das Manifest anfassen muss. Die Abnahme nennt vier Bedingungen, davon eine
> mit vier von Hand nachgerechneten Festwerten. Und 0019 ist seit heute `fertig`.
>
> **Warum das kein Rücklauf gegen 0019 ist, und warum ich das hier hinschreibe:** Die
> Frage, *welche* Klasse ein Profil trägt, stand in keiner der fünf Abnahmebedingungen
> von 0019. Wer sie nachträglich dort hineinliest, hebt ein bestandenes Kriterium an —
> die Fehlerklasse, die mein Logbuch als „ein Kriterium, das einem anderen Paket gehört"
> führt.

Vorgabe: `technik.md` T36, Absatz „Strategiekern, vierwertig" — **„Aktionsart mit dem
größten Anteil unter `{1 Position, 2 Beteiligung, 3 Lobby}`, Gleichstand nach kleinerer
Kennung; Hebel und Sichtbarkeit gehen nicht ein."** Dazu T4 (kein Gleitkomma) und T13.

## Warum das ein eigenes Paket ist

**Es ist kein Rücklauf zu 0019.** Die fünf Abnahmebedingungen der 0019 verlangen die
Zahlen 126, 76, 0 – 5, 6 und 120; alle fünf sind gegen Festwerte aus T36 verankert und
alle fünf sind erfüllt (Befund `pruefung-0019-…-2026-09-02.md`, Urteil `geprueft`). Die
Frage, **welche** Klasse ein klassifiziertes Profil trägt, steht dort nicht — sie ist
keine gesenkte Bedingung, sondern eine, die nie gestellt wurde. Ein Rücklauf würde 0019
gegen ein Kriterium messen, das es nicht hatte.

**Es ist auch kein Teil von 0029.** Das baut das Vorratsverfahren nach T43 und rührt den
Strategiekern nicht an.

**Und es kollidiert mit nichts.** Die Datei ist neu. Der Glob des Kastens
(`file(GLOB … CONFIGURE_DEPENDS test/*.cpp)`) sammelt sie ein und gibt ihr ein eigenes
Ziel und ein eigenes `add_test` — genau der Kollisionsschutz, für den die
`CMakeLists.txt` aus 0019 so gebaut ist. Keine bestehende Datei wird angefasst.

## Der Befund, gemessen

Die Probe aus 0019 prüft die Klassenzuteilung des Moduls an **genau einer** Stelle,
`vorrat_probe.cpp:427`:

```cpp
if (hat_familienaktion(eintrag.anteile)
    && strategiekern_dreiwertig(eintrag.anteile) != eintrag.kern) {
    einig_auf_120 = false;
}
```

`strategiekern_dreiwertig` ist nach dem eigenen Kommentar der Probe (Zeile 240–244)
„**wortgleich** zu `pruefstand::vorrat::strategiekern`, ohne die Abfrage auf den leeren
Kern" — eine Kopie desselben Verfahrens im selben Kopf geschrieben, kein unabhängiger
Maßstab.

Nachgemessen mit acht Mutationen gegen die unveränderte Probe: Zwei Mutationen sterben
an **nur dieser einen** Zeile.

| Mutation von `strategiekern` | fehlgeschlagene Zusicherungen |
|---|---|
| Gleichstand an die größere Kennung (`>` → `>=`) | **1**, Zeile 427 |
| Position und Lobby vertauscht | **1**, Zeile 427 |

Keine Zusicherung nennt einen erwarteten Klassennamen für ein Profil des Moduls.
Zeile 337 prüft `liste[76].anteile`, nicht `liste[76].kern`. „Kern Position" steht in
der Ausgabe — gedruckt, nicht geprüft.

**Die Folge, konkret:** Stünde „bei Gleichstand die kleinere Kennung" in Modul *und*
Kopie gleich falsch, liefe die Probe grün und in der Ausgabe stünde
`Kennung 76 (1,1,1,1,1) Kern Lobby`. Der Gleichstand ist kein Randfall — das
Referenzprofil ist selbst ein Dreifachgleichstand, und über T36 hängt die Abnahme von
Maß 2 an der Klasse.

**Das Modul ist heute richtig.** Der Prüfer hat den fehlenden Maßstab einmal gebaut und
laufen lassen; alle vier Anker unten stimmen. Es geht nicht darum, einen Fehler zu
beheben, sondern darum, dass der nächste Eingriff in `strategiekern` auffällt.

## Was du baust

Eine Probe `test/vorrat_kernanker_probe.cpp` mit einem `main`, das 0 zurückgibt, wenn
alle Anker stimmen, und sonst 1. Sie ruft `erzeuge_profilliste` und `strategiekern` —
**nicht** `runde`, `spiele` oder `Abweichung`, solange 0029 nicht gelaufen ist.

Die vier Anker sind von Hand abgezählt und je einzeln nachgerechnet. Sie stehen hier
mit ihrer Kennung, damit die Probe nicht suchen muss:

| Kennung | Vektor | erwarteter Kern | was er festnagelt |
|---:|---|---|---|
| 20 | `(0,0,5,0,0)` | `LOBBY` | die Zuteilung ohne Gleichstand — Index 2 → Kennung 3 |
| 44 | `(0,2,2,1,0)` | `BETEILIGUNG` | Gleichstand Beteiligung(2) gegen Lobby(3) → die **kleinere** |
| 60 | `(1,0,0,4,0)` | `POSITION` | Hebel ist mit 4 der größte Anteil und geht **nicht** ein |
| 76 | `(1,1,1,1,1)` | `POSITION` | Dreifachgleichstand → die kleinste Kennung |

Prüfe je Anker **beides**: dass `liste[k].anteile` der Vektor ist und dass
`liste[k].kern` die Klasse ist. Nur die zweite Hälfte ist neu, aber ohne die erste
prüfst du die Klasse eines Profils, das du nicht identifiziert hast.

**Was du nicht baust:** eine zweite Fassung von `strategiekern` in der Probe. Genau das
ist der Befund. Die erwarteten Klassennamen stehen als Festwerte im Testcode, abgeleitet
aus T36 und von Hand nachgerechnet — nicht aus einer Rechnung.

## Abnahme

1. **Die vier Anker stehen als Festwerte im Testcode und werden einzeln geprüft**, je
   mit Vektor und Klasse. Die Ausgabe nennt zu jedem Anker Kennung, Vektor, gefundene
   und erwartete Klasse.
2. **Kein zweites `strategiekern` in der Probe.** Die erwartete Klasse ist ein
   hingeschriebener Aufzählungswert, kein Rechenergebnis. `grep -c 'anteile\[' ` über
   deine Datei zeigt keinen Vergleich zweier Anteile gegeneinander.
3. **Die Probe wird rot, wenn die Zuteilung kippt.** Führe eine benannte Abweichung vor
   — eine testeigene Funktion, die den Gleichstand an die größere Kennung gibt — und
   weise nach, dass dieselbe Ankerprüfung sie **verwirft**, mit Kennung und Vektor des
   ersten Ankers, an dem es auffällt. Erwartet: Kennung 44 und Kennung 76 weichen ab,
   Kennung 20 und 60 nicht. Dass zwei der vier Anker die Abweichung **nicht** fangen,
   gehört in die Ausgabe — ein Test muss auch sagen, was er durchlässt.
4. **Der Übersetzungslauf führt sie wirklich aus.** In `befunde/uebersetzung-<datum>.md`
   steht unter `ctest --test-dir …/pruefstand/bau` ein Test `vorrat_kernanker_probe` mit
   `Passed`. Kein Gleitkomma, keine Fremdabhängigkeit, keine veränderliche Ablage
   außerhalb einer Funktion außer dem Fehlerzähler, wie in allen Proben des Vorhabens.

## Rückläufe

0.
