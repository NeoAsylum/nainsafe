---
typ: messung
paket: 0083-belegstellenriegel-totes-ziel-statt-uebergangen
rolle: testentwickler
datum: 2026-09-05
gegenstand: Ruecklauf 1 von 3 -- die Ortsfrage wird am Ort entschieden statt am Namen
---

# Rot- und Gruennachweis gegen den Arbeitsbaum **mit** bestehendem `bau/`

Alle Laeufe unten gegen
`/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft` als
Vorhabenwurzel. Der Arbeitsbaum traegt ein bestehendes `bau/` mit
`bau/kp0010/quelle/` und `bau/kp0027r3/quelle/` -- den Abschriften des Quellbaums, an
denen der erste Anlauf gescheitert ist. Das ist der Baum, auf dem der Riegel im Betrieb
laeuft, und deshalb der Baum, auf dem gemessen wird.

Uebersetzt und gefahren ausserhalb des Vorhabens (`$TMPDIR`), ohne Eingriff in den
Arbeitsbaum. Die Vorher-Zahlen stammen aus derselben Sitzung mit dem Stand vor der
Aenderung, damit Programmunterschied und Korpusdrift getrennt bleiben.

## Die vier Laeufe, vorher gegen nachher

| # | Vorgabenwurzel | Zitate | aufgeloest | uebergangen | tote Ziele | Ausgang |
|---|---|---|---|---|---|---|
| 1 | echte `specs/` | 36 → **36** | 36 → **36** | 47 → **47** | 0 → **0** | gruen → **gruen** |
| 2 | Kopie ohne `spiel.md` | 21 → **36** | 21 → **21** | 62 → **47** | 0 → **15** | **gruen → rot** |
| 3 | `decisions/` (keine der vier) | 13 → 57 | 13 → 13 | 69 → 26 | 0 → 44 | rot → rot |
| 4 | vollstaendige Kopie der vier | 36 → 36 | 36 → 36 | 47 → 47 | 0 → 0 | gruen → gruen |

**Lauf 2 ist der Vorgang aus dem Abschnittstitel *Der gemessene Sachverhalt* des Pakets**
und der Grund des Ruecklaufs: eine Vorgabenkopie ohne `spiel.md`, dieselbe Vorhabenwurzel
mit `bau/`. Vorher gruen mit Code 0, jetzt **Code 1 und 15 tote Ziele** -- die Abnahme
verlangt mindestens 14. Vorher wanderten genau diese 15 Fundstellen unter die
uebergangenen und meldeten `Ziel in einem mit Absicht ungelesenen Ordner: spiel.md`,
weil der Name unter `bau/kp0010/quelle/specs/` einen Zwilling hat.

Lauf 3 war schon vorher rot, aber aus dem falschen Grund: Er fiel unter die Untergrenze
(13 < 16), nicht ueber die toten Ziele. Jetzt faellt er ueber beides.

Lauf 4 ist die Kontrolle gegen den Messaufbau selbst: dieselben vier Dateien an einem
anderen Ort ergeben Zeichen fuer Zeichen den Ausgang von Lauf 1. Ohne ihn koennte Lauf 2
auch am Kopieren liegen.

## Der Gruennachweis, als Mengenvergleich und nicht als Zahl

Die 47 uebergangenen Fundstellen aus Lauf 1 sind vorher und nachher als **Mehrfachmenge**
verglichen worden, nicht nur gezaehlt:

    nur vorher:   []
    nur endstand: []

Keine bisher uebergangene Fundstelle ist rot geworden, und keine ist hinzugekommen. Die
eine Fundstelle der Sorte, um die es geht, bleibt uebergangen und behaelt ihren Grund:

    parameter.toml:11  (Ziel in einem mit Absicht ungelesenen Ordner:
                        befunde/pruefung-0009-parameterdatei-schluessel-runde2-2026-09-02.md)

Sie bleibt es, weil sie ihren Ordner mitschreibt -- genau die Eigenschaft, an der die
neue Trennung haengt.

## Was sich geaendert hat

Die Ortsfrage ist zweiteilig geworden und wird am **Ort** entschieden:

1. Nennt der Verweis selbst einen ungelesenen Ordner als ganzen Pfadteil?
2. Liegt unter dem genannten Pfad dort auch eine Datei?

Beides zusammen heisst uebergangen, sonst tot. Eingesammelt werden dafuer die **Pfade**
unter `bau/` und `befunde/` statt der blossen Basisnamen; die gemeldete Zahl heisst
deshalb jetzt „Pfade in ungelesenen Ordnern" (am 2026-09-05 zwischen 2543 und 3520 --
der Baum waechst waehrend paralleler Laeufe).

**Die offene Entscheidung, und wie sie gefallen ist:** Ein Verweis, der seinen Ordner
nicht bei sich traegt, gilt als **tot**. Die strenge Richtung. Die nachsichtige haette
genau die Abdeckung gekostet, um derentwillen das Paket angelegt wurde -- jeder Name mit
einem Zwilling unter `bau/` waere wieder unfaengbar gewesen. Der Preis ist ein Zitat, das
seinen Vorsatz ergaenzen muss; er wird laut bezahlt, weil die Meldung den Namen nennt.
Ausgeschrieben im Kopfkommentar.

`aufgaben/` bleibt wie bisher **kein** ungelesener Ordner. Die Begruendung des ersten
Anlaufs traegt unveraendert: Ungelesen ist er nur als zitierende Menge, als Ziel steht er
im Bestand.

## Der Rotnachweis der Selbstpruefung -- fuenf Mutanten

Ein Test, der nie fehlschlaegt, prueft nichts. Mutiert wurde jeweils der **Rumpf** einer
Funktion, nie die Aufrufstelle -- sonst faellt sie aus dem Spiel und
`-Werror=unused-function` macht den Bau rot statt des Tests. Die Mutanten sind Kopien in
`$TMPDIR`; der Arbeitsbaum ist dabei nicht angefasst worden.

| Mutant | was er wegnimmt | gerissene Zielfaelle | Ausgang |
|---|---|---|---|
| m1 | die Ortsfrage (Teil 1) -- der Zustand vor dem Ruecklauf | 6, 7, 10, 12, 13 | Code 2 |
| m2 | die Dateifrage (Teil 2) | 4, 9, 11 | Code 2 |
| m3 | die Pfadgrenze im Endstueckvergleich | 11 | Code 2 |
| m4 | ganzer Pfadteil statt Teilwort | 10 | Code 2 |
| m5 | den Vorrang des Aufstiegs | **keine** | unveraendert |

Jeder der vier ersten reisst **andere** Faelle -- die vier Teilregeln messen also
Verschiedenes und sind nicht vier Namen fuer eine. m1 ist der Ruecklauf selbst: Er stellt
die Namensfrage wieder her, und der Selbsttest faengt ihn, bevor der Bestand gelesen ist.

**m5 reisst nichts, und das ist ein Befund gegen die Regel, nicht gegen den Test.** Der
Vorrang des Aufstiegs vor der Ortsfrage ist **nicht** gemessen und kann es nicht sein:
Ein eingesammelter Pfad beginnt nie mit einem Schraegstrich und traegt nie zwei Punkte,
also findet ein Name, der seinen Ort nach draussen ausspricht, dort nie eine Datei.
Beide Bedingungen koennen nicht zugleich zutreffen; die Reihenfolge ist Ordnung und keine
Regel. Der Satz steht ausgeschrieben beim letzten Fall der Tabelle im Quelltext, damit
niemand sie fuer gemessen haelt.

Dass die Untergrenze den Einbruch nicht faengt, hat der Ruecklauf zu Recht angemerkt und
bleibt so: Lauf 2 gibt 21 aufgeloeste Zitate, und 21 steht ueber 16. Gefangen wird der
Einbruch jetzt von der Zielseite. Die Untergrenze auf den Tagesstand zu ziehen hiesse
eine Schwelle zu pflegen, fuer die es einen Riegel gibt; die Rechnung steht bei
`AUFGELOEST_MINDESTENS`.

## Beide Bauwege

- allein (`cmake -S werkzeuge/belegstellen`): 1 von 1 Test bestanden;
- ueber den Arbeitsbereich (`cmake -S <vorhaben>`): Test 15 bestanden.

## Worauf ich unsicher bin

- Die Zahl der Pfade in ungelesenen Ordnern ist in einer Stunde von 2543 auf 3520
  gestiegen, ohne mein Zutun -- parallele Laeufe bauen und schreiben. Die lineare Suche
  darin laeuft nur fuer Namen, die die erste Frage schon bejaht haben, also einstellig oft
  je Lauf; sie bleibt trotzdem die Stelle, die mit dem Baum waechst.
- Ob `spiel.md` unter `bau/` liegt, entscheidet heute kein Zitat mehr -- aber der
  Zielbestand selbst wird weiterhin **ueber den Basisnamen** nachgeschlagen
  (`Zielbestand`, Paket 0067). Diese Haelfte habe ich nicht angefasst: Sie betrifft die
  gelesene Menge, in der ein Fund echt ist, und sie zu aendern hiesse die Aufloesung
  aller 36 Zitate umzubauen. Wenn der Projektmanager das anders sieht, ist es ein eigenes
  Paket.
