---
typ: pruefung
paket: 0136-schlussriegel-nachbau-in-eigenes-mitglied
pruefer: test-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Beide Abnahmebedingungen selbst gemessen -- sechs Bauwege in beiden Profilen gruen mit gleicher Probenzahl im Arbeitsbereich und genau eins weniger im Pruefstand, dazu eigener Mutant am neuen Ort rot mit denselben 15 Kippfaellen.
befunde: 0
---

# Pruefung 0136: Der Waechter sitzt im neuen Kasten und beisst dort noch

Geprueft am Arbeitsbaum vom 2026-09-05 (juengster Commit `c19e388`). Alle Zahlen unten
sind eigene Messungen, nicht aus dem Nachweis des Bauagenten uebernommen; der Nachweis
wurde erst **nach** der eigenen Messung gegengelesen (Abgleich am Ende).

## Messaufbau

Drei Baeume unter `bau/pruefer0136/` (gitignoriert, von `baulauf.py` ausgenommen), je
mit `ventures/<id>/` und `specs/<id>/` in Repostruktur:

- **neu** = Kopie des heutigen Arbeitsbaums (ohne `bau/`-Verzeichnisse).
- **alt** = dieselbe Kopie, allein die drei Paketdateien auf den Stand `0333b81^`
  zurueckgesetzt: `CMakeLists.txt` und `pruefstand/CMakeLists.txt` woertlich per
  `git show 0333b81^:<pfad>`, `werkzeuge/schlussriegel/` entfernt. Dass das genau der
  Rueckbau des Pakets ist, belegt `git diff 0333b81^ 0333b81` auf diese Dateien: Der
  Sammelcommit aendert an beiden **nur** den Waechterblock bzw. Kopfabsatz und
  `FABRIK_MITGLIEDER` -- die fremde Paketarbeit in `0333b81` (u. a.
  `werkzeugkette.cmake`) liegt in anderen Dateien und ist in beiden Baeumen identisch.
- **mut** = neu, mit **eigener** Mutation: die Sammelbedingung in
  `fabrik_riegel_sammeln` invertiert (`if(NOT "${${listenname}}" STREQUAL "")` ->
  `if("${${listenname}}" STREQUAL "")`, Trefferbremse 1x). Absichtlich nicht die
  Mutation des Nachweises (`if(FALSE)`), damit die Kippmenge unabhaengig bestaetigt wird.

Gebaut wie der Runner (`RelWithDebInfo`, `-fwrapv -fno-fast-math`), beide Profile
`FABRIK_SANITIZER=ON/OFF`, je Bauweg `cmake -S`, `cmake --build --parallel`,
`ctest --output-on-failure`.

## Bedingung 1 -- Bauwege, Urteile, Probenzahlen (alles selbst gezaehlt)

| Bauweg | Profil | alt: konfig/bau/ctest, Proben | neu: konfig/bau/ctest, Proben |
|---|---|---|---|
| Arbeitsbereich | ON | 0/0/0, **17** | 0/0/0, **17** |
| Arbeitsbereich | OFF | 0/0/0, **17** | 0/0/0, **17** |
| kern | ON | 0/0/0, 11 | 0/0/0, 11 |
| kern | OFF | 0/0/0, 11 | 0/0/0, 11 |
| pruefstand | ON | 0/0/0, **4** | 0/0/0, **3** |
| pruefstand | OFF | 0/0/0, **4** | 0/0/0, **3** |
| werkzeuge/schlussriegel allein | ON | -- | 0/0/0, 1 |
| werkzeuge/schlussriegel allein | OFF | -- | 0/0/0, 1 |

Probenzahl per Regex `Test\s+#\d+:` gezaehlt und gegen die Bilanzzeile `out of N`
gegengeprueft (Lehre aus Pruefung 0129); beide Zaehlungen stimmen ueberall ueberein.
Der Arbeitsbereich haelt seine Zahl, der Pruefstand faellt um genau eins, `kern` als
unbeteiligter Zeuge bleibt gleich -- die Abnahme Wort fuer Wort.

**Ortsprobe alter Ort:** `ctest --test-dir <pruefstand-bau> -R schlussriegel_nachbau
--no-tests=error` findet die Probe im Alt-Baum (`1/1 Passed`) und meldet im Neu-Baum
`No tests were found!!!` (Code 8). Die Probe ist umgezogen, nicht verdoppelt.

## Bedingung 2 -- der Rotnachweis am neuen Ort, mit eigenem Mutanten

- **Unveraenderter Baum, Alleinbau `werkzeuge/schlussriegel`:** `schlussriegel_nachbau`
  gruen (`1/1 Passed`, beide Profile).
- **Mutant, derselbe Aufruf:** `***Failed`, Ausgabe `15 Abweichung(en) vom Soll` --
  gekippt sind exakt a1_zielflags, b1_quellflags, b1b_quellopt, b2_iface,
  e10_genexquelle, e1_addcompileopt, e2_dirprop, e4_zweiworte, e5_zweitequelle,
  e8_wnoerrorquelle, r2_privatw, r3_shellform, r4_staticpublic, f1_targetdir,
  x_unterbaum. Das ist dieselbe Kippmenge wie bei meiner Pruefung zu 0133 und im
  Nachweis des Bauagenten -- erreicht mit einer **anderen** Mutation, was die Zahl
  unabhaengig bestaetigt. r1_ohnesatz und r5_nurschnittstelle bleiben rot-wie-gesollt
  (urteilen am Sammler vorbei): Das Rot kommt aus der stumpfen Zeile, nicht aus einem
  kaputten Baum.
- **Der Mutant ist fuer die Konfiguration unsichtbar:** `cmake -S` auf den
  Arbeitsbereich des Mutanten liefert Code 0 **mit** der Vollzugsmeldung `alle mit
  Warnsatz und ohne Pauschalabschalter`. Gefangen wird er allein vom Waechter -- genau
  der Zweck des Pakets.

**Zusatz, ueber die Abnahme hinaus:** Der `FATAL_ERROR`-Riegel des neuen Kastens greift.
`nachbau.py` beiseitegelegt, `cmake -S werkzeuge/schlussriegel` -> Konfiguration bricht
mit Code 1 und der Meldung `Der Regressionsnachweis des Schlussriegels fehlt` ab
(`CMakeLists.txt:87`). Kein stilles Verschwinden bei verschobenem Skript.

## Wonach sonst gesucht wurde

- **Abgeschwaechte Zusicherungen:** keine. Der umgezogene Block traegt unveraendert
  `FATAL_ERROR` bei fehlendem Skript, den `python3`-Rueckfall ohne stilles
  Ueberspringen, `TIMEOUT 600` und `NACHBAU_ABLAGE` im Baubaum. Die Abnahme folgt der
  Vergleichsregel des Projektmanagers (keine ausgeschriebene Zahl) -- nichts gesenkt.
- **Verweise auf den alten Ort:** repo-weit nach `schlussriegel_nachbau` gesucht. In
  lebendem Bauzeug zeigt nichts mehr auf den Pruefstand; der Kommentar dort ist ein
  bewusster Wegweiser zum neuen Ort. Einzige Ausnahme siehe Nebenbefund.
- **Erzwungene Zahlen:** Die Ziel-/Probenzahlen in `werkzeugkette.cmake` (Zeilen
  973-985) sind datierte Kommentare, keine Pruefungen -- der Umzug verletzt dort nichts.
- **Alleinbau-Eigenheit:** Der neue Kasten bindet die Werkzeugkette beim Alleinbau nicht
  ein; gemessen druckt er dort folgerichtig keine Riegelmeldung und konfiguriert
  trotzdem Code 0 -- der dokumentierte "kein uebersetzendes Ziel"-Abbruch der Kette wird
  so gar nicht erst beruehrt, und der Waechter misst die Kette als Datei weiter.

## Abgleich mit dem Nachweis des Bauagenten (erst nach eigener Messung gelesen)

Sein Stand war `74e1464`; dort 16 Proben Arbeitsbereich / 10 kern. Meine 17/11 sind kein
Widerspruch: Paket 0140 (`c19e388`, Verlaufs-Probe im Kern) landete **nach** seiner
Messung. Pruefstand 4 -> 3, Kippmenge 15/22, Ortsprobe und Konfigurationsmeldung decken
sich woertlich.

## Randnotizen

- **Nebenbefund ohne Paketvorschlag:** Der Docstring von
  `befunde/pruefung-0066/nachbau.py` (Zeile 19-21) sagt noch, die Probe haenge in
  `pruefstand/CMakeLists.txt`. Die Datei war dem Paket ausdruecklich entzogen
  (`nachbau.py` nicht in `dateien`), der Bauagent durfte sie nicht anfassen -- kein
  Befund gegen 0136. Eine Zeile fuers naechste Paket, das `nachbau.py` ohnehin anfasst;
  der alte Ort traegt bereits einen Wegweiser, darum kein eigenes Paket.
- **Messstoerung, offengelegt:** Der erste Messdurchgang wurde zur Haelfte von einem
  vollen `/tmp/claude-1000` zerstoert -- `gcc` legt Assembler-Zwischendateien in
  `$TMPDIR` ab, die betroffenen Bauwege starben an ENOSPC, und der erste
  Alleinbau-Lauf des Waechters zeigte dadurch 5 Schein-Abweichungen (ENOSPC kippte
  genau die soll-0-Wegwerfbaeume). Alle betroffenen Bauwege wurden mit `TMPDIR` auf
  der Platte frisch gebaut und neu gemessen; nur diese Wiederholung zaehlt oben.
  Messskripte und Rohprotokolle liegen unter `bau/pruefer0136/` (`messung.py`,
  `messung2.py`, `fatalprobe.py`, `protokoll*.txt`, `ergebnis*.json`); die drei
  Messbaeume selbst sind nach der Messung entfernt, die Skripte bauen sie erneut auf.
