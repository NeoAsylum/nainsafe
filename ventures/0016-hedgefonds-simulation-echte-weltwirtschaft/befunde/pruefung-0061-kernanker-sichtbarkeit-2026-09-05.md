---
typ: pruefung
paket: 0061-kernanker-sichtbarkeit
pruefer: test-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Alle drei Abnahmebedingungen mit eigenem Bau nachgemessen, dazu vier selbstgebaute Modulmutanten und der Rotnachweis der blossen Tabellenerweiterung -- jede Messung unten mit Aufruf und Ausgabe.
befunde: 0
---

# Pruefung 0061 -- der fuenfte Anker haelt, und zwar gemessen

Gegenstand ist `pruefstand/test/vorrat_kernanker_probe.cpp` im Stand `f7d9822`
(2026-09-05 11:36, einziger Commit an der Datei seit `f68e8fb`). Alle Messungen sind
eigene Uebersetzungen ausserhalb des Repos (`$TMPDIR`, Textersetzung mit Trefferbremse,
keine Paketdatei angefasst), mit den Schaltern des Runners aus
`pruefstand/bau/CMakeFiles/vorrat_kernanker_probe.dir/flags.make` (`-std=c++20 -Werror
-fsanitize=undefined,address` usw.).

## Die Frage meiner Rolle zuerst: Wird die Probe rot, wenn man die Sache kaputtmacht?

Vier Mutanten des Moduls `src/vorrat.cpp`, je gegen die **unveraenderte** Probe:

| Mutation | Ergebnis | wo es reisst |
|---|---|---|
| M0, Kontrolle ohne Eingriff | `bestanden -- 0 fehlgeschlagen` | -- |
| A: Familie `{a1,a2,a3,a5}`, Sichtbarkeit zaehlt mit | `GESCHEITERT -- 4` | alle vier an **Kennung 56**, Zeilen 355/361/387/396 |
| B: Familie `{a1,a2,a3,a4}`, Hebel zaehlt mit | `GESCHEITERT -- 4` | alle vier an **Kennung 60** |
| C: `>=` statt `>`, Gleichstand an die groessere Kennung | `GESCHEITERT -- 13` | Kennungen 44 und 76, Pruefungen 1-3 samt Zaehl- und Indexzusicherungen (u. a. Zeilen 476, 485) |

Mutant A ist genau die Luecke, gegen die das Paket geschrieben ist; er stirbt
ausschliesslich am neuen Anker. Mutant B belegt, dass der Einschub den Altanker aus
0040 nicht entschaerft hat. Die Trefferbremse (`assert count == 1`) lief bei jeder
Ersetzung.

**Die Gegenprobe, dass die Luecke vor dem Paket wirklich offen war:** Die alte
Vier-Anker-Fassung der Probe aus `f68e8fb` gegen denselben Mutanten A uebersetzt --
`bestanden -- 0 Pruefung(en) fehlgeschlagen`, Exit 0. Der fuenfte Anker ist also der
**einzige** Faenger dieser Mutation, und die Behauptung des Pakets ist keine
Vermutung.

## Abnahme, Bedingung fuer Bedingung

**1. Fuenfter Anker als Festwert, einzeln geprueft.** Erfuellt. `ANKER` traegt
`{56, Profil{1,0,0,0,4}, POSITION, POSITION, ...}` als `constexpr`-Festwert an dritter
Stelle (Zeile 137); die Kennung 56 habe ich unabhaengig nachgezaehlt (`a1 = 0` umfasst
`C(8,3) = 56` Vektoren, also ist 56 der erste mit `a1 = 1`, und dessen Rest ist
`(0,0,0,4)`; Familie `(1,0,0)`, kein Gleichstand, groesster Anteil an Index 0 →
POSITION). Die Ausgabe des M0-Laufs nennt zu Kennung 56 Vektor, gefundene und
erwartete Klasse in **allen drei** Pruefungen. Kein zweites `strategiekern`: Die
einzigen Aufrufe gehen an `pruefstand::vorrat::strategiekern` (Zeilen 262 und 304),
eine zweite Fassung des Verfahrens gibt es nicht. `grep -n 'anteile\['` liefert genau
zwei Fundstellen -- Zeile 171 (Druck in `schreibe_anker`) und Zeile 303 (Spiegelung) --,
kein Vergleich zweier Anteile gegeneinander; beide unveraendert aus 0040.

**2. Zaehlungen nachgezogen.** Erfuellt. Der M0-Lauf druckt `von 5 Ankern fangen die
Abweichung: 2`, die Zusicherung lautet `genau 2 der 5` (Zeile 476), und die Liste der
Durchgelassenen nennt drei Kennungen: 20, 56, 60. Der Rotnachweis ist selbst gefahren:
alte Fassung plus **nur** Tabellenzeile 56 und `ANKERZAHL = 5`, Zusicherungen
unveraendert → `GESCHEITERT -- 1 Pruefung(en) fehlgeschlagen`, gerissen an "gefangen
wird sie von Kennung 44 und Kennung 76". Das bestaetigt unabhaengig auch die
Berichtigung im GEBAUT-Eintrag: Rot wird der **Index** (`weicht_ab[3]` zeigt nach dem
Einschub auf 60 statt 76), nicht die Zahl 2 -- `abweichende == 2` blieb in meiner
Messung gruen.

**3. Der Uebersetzungslauf fuehrt sie aus.** Erfuellt. `befunde/uebersetzung-2026-09-05.md`
zeigt unter `ctest --test-dir .../pruefstand/bau`: `1/3 Test #1: vorrat_kernanker_probe
... Passed`, 3/3 gruen; `CMakeLists.txt` traegt das `add_test` (Zeile 90). Kein
Gleitkomma (`grep -E 'float|double'` leer), keine Fremdabhaengigkeit (Includes:
`<array>`, `<cstddef>`, `<cstdio>`, eigenes Modul), und die einzige veraenderliche
Ablage ausserhalb einer Funktion ist der Fehlerzaehler `int fehlgeschlagen` (Zeile 72)
-- der ausdruecklich erlaubte.

## Abgeschwaechte Tests: gesucht, nichts gefunden

`git diff f68e8fb f7d9822 -- .../vorrat_kernanker_probe.cpp` vollstaendig gelesen:
keine entfernte Zusicherung, keine gesenkte Schwelle, kein Ueberspringen. Alle
Aenderungen sind der Einschub, nachgezogene Zaehlungen (`4` → `ANKERZAHL` in beiden
Druckzeilen) und **zusaetzliche** Bindungen. Der Commit `f7d9822` traegt daneben sechs
fremde Dateien (bekannte Buendelverschiebung des Runners, u. a. Arbeit zu 0094/0107);
an der Zieldatei ist ausschliesslich die Paketarbeit.

## Die Haertung, zu der der Bauagent Unsicherheit angemeldet hat

Die Kennungsbindung in den beiden Indexzusicherungen (Zeilen 483-491) ist zulaessig
und bleibt: Sie senkt keine Schwelle, sie haengt eine zusaetzliche daneben, und mein
Rotnachweis zu Bedingung 2 zeigt, dass genau diese Zusicherungsform den
Einschub-Fall faengt. Die Vorgaben schweigen dazu, also gilt die Entscheidung des
Bauagenten.

## Ausserhalb des Pakets, nachgeprueft statt uebernommen

Der rote `belegstellen_riegel` im Arbeitsbereichs-`ctest` (13/14) gehoert nicht zu
diesem Paket: Sein bewerteter Fehler ist das Abschnittszitat
`daten/nachmessung-zinsreihen-2026-09-05.md:6` → `daten/deckungsbefund-1997.md`
("Die Reihenliste nennt IWF IFS" ist dort Fliesstext in Zeile 140, kein Titel), die
zitierende Datei stammt aus `a6c55e0` (Betreiber, 2026-09-05 **09:38**) -- zwei
Stunden **vor** dem Baucommit (11:36), und `f7d9822` fasst keine `daten/`-Datei an.
Die Fundstelle `vorrat_kernanker_probe.cpp:3` in der Riegelausgabe steht in der mit
Begruendung **uebergangenen** Liste ("kein Dokumentname im Absatz"), nicht im Fehler.
Kein Paket traegt die Berichtigung bisher; der Vorschlag dazu ist
`aufgaben/0120-abschnittszitat-nachmessung-zinsreihen.md` aus diesem Lauf.

## Wonach ich sonst gesucht und nichts gefunden habe

Regelabdeckung des T36-Satzes an dieser Probe: groesster Anteil ohne Gleichstand (20),
Gleichstand an die kleinere Kennung (44, 76), Hebel geht nicht ein (60), Sichtbarkeit
geht nicht ein (56) -- damit ist jede Teilaussage des Satzes einzeln verankert. Der
Fall "alle drei null → ohne" gehoert laut Kopf der Probe zu Paket 0019 und wird dort
ueber die Zaehlung der sechs kernlosen Kennungen 0-5 gefangen; keine Luecke dieses
Pakets.
