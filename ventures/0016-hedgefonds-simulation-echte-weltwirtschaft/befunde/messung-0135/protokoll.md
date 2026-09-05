# Nachweis zu Paket 0135 -- `bauwege.py` misst gegen den eigenen Stand davor

Rolle: `testentwickler`. Gemessen am 2026-09-05, alles aus WSL heraus, Ablagen unter
`$TMPDIR` (`/tmp/claude-1000/`) und damit ausserhalb des Repos -- erste Stufe der
Staffelung aus 0066 / 0076 / 0103.

Geaenderte Datei: `befunde/messung-0076/bauwege.py`, sonst keine. `werkzeugkette.cmake`,
`nachbau.py`, der Riegel und seine Meldung sind unberuehrt; kein Ziel im Baum wurde
angelegt oder entfernt.

## Was geaendert ist

Die feste Erwartung im Quelltext ist fort. Sie lautete

    "arbeitsbereich": (WURZEL, 16, {"ON": 18, "OFF": 16}),

und lieferte am unveraenderten Baum `2 Abweichung(en)` und Rueckgabewert 1. An ihre
Stelle tritt das Gleichheitsmass aus der Entscheidung des Projektmanagers in Paket 0104:
**dieselbe Zahl wie am Stand davor, je Bauweg und je Profil.** Woher der Stand davor
kommt, ist ein Argument und keine Annahme:

* `--gegen <commit>`, Vorgabe `HEAD` -- der Vergleichsstand wird selbst gemessen. Das
  Skript packt den Vorhabensbaum mit `git archive` aus dem Commit unter `$TMPDIR` aus
  und konfiguriert dort dieselben drei Wege in denselben zwei Profilen. Gebaut und
  geprueft wird der Vergleichsstand nicht; gezaehlt wird beim Konfigurieren.
* `--gegen-datei <pfad>` -- die `stand.json`, die jeder Lauf am Ende schreibt. Das ist
  das Paar `vorher` / `nachher`, das der Kopf des Skripts seit 0076 verspricht und das
  bis heute nur die Ablage benannt hat.

**Ein nicht erreichbarer Vergleichsstand ist eine Abweichung, kein uebersprungener
Punkt** (Nachweis 5 unten). Einen Schalter, der den Vergleich abschaltet, gibt es nicht.

Zwei kleinere Aenderungen an derselben Datei, beide innerhalb des Pakets und beide
gegen dieselbe Fehlerklasse:

* `bauplatz_raeumen()` wirft einen Baubaum weg, dessen `CMakeCache.txt` auf eine andere
  Quelle zeigt. Ohne das meldete ein zweiter Lauf unter demselben Ablagenamen an einem
  anderen Baum sechsmal `konfig code=1` -- gemessen beim Bau dieser Fassung: 16
  Abweichungen an einem fehlerfreien Baum. Das saehe aus wie ein kaputter Baum und
  waere keiner.
* `ctest` laeuft mit `--no-tests=error`. Ohne den Schalter gibt `ctest` Code 0 zurueck,
  wenn es gar keine Probe gefunden hat. **Diese Aenderung stand nicht im Paket** und
  aendert an keinem der sechs Bauwege heute etwas (16 / 10 / 4 Proben, alle > 0); sie
  steht hier ausgeschrieben, damit der Pruefer sie nicht suchen muss.

Die Zahlen, die im Kopf des Skripts stehen bleiben, tragen jetzt Bauweg, Profil, Datum
und Stand -- so wie 0104 es verlangt.

## Nachweis 1 -- Abnahmebedingung 1: unveraenderter Arbeitsbaum, beide Profile

    python3 /home/adria/fabrik/ventures/0016-.../befunde/messung-0076/bauwege.py g-abnahme-bedingung-1
    Rueckgabewert: 0

```
Gemessener Baum: /home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft
Stand davor: git 497bcbc vom 2026-09-05 ("testentwickler: 0083-belegstellenriegel-totes-ziel-statt-uebergangen (6 Dateien)"), ausgepackt nach /tmp/claude-1000/bauwege0076-g-abnahme-bedingung-1/vergleichsstand-497bcbc
   FABRIK_SANITIZER=OFF   arbeitsbereich=18  kern=11  pruefstand=4
   FABRIK_SANITIZER=ON    arbeitsbereich=20  kern=12  pruefstand=5

=== Profil sanitizer-an (FABRIK_SANITIZER=ON) ===
   arbeitsbereich   konfig code=0  uebersetzende Ziele=20 (Stand davor 20)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 16
   kern             konfig code=0  uebersetzende Ziele=12 (Stand davor 12)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 10
   pruefstand       konfig code=0  uebersetzende Ziele=5 (Stand davor 5)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 4
=== Profil sanitizer-aus (FABRIK_SANITIZER=OFF) ===
   arbeitsbereich   konfig code=0  uebersetzende Ziele=18 (Stand davor 18)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 16
   kern             konfig code=0  uebersetzende Ziele=11 (Stand davor 11)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 10
   pruefstand       konfig code=0  uebersetzende Ziele=4 (Stand davor 4)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 4

Verglichen gegen: git 497bcbc vom 2026-09-05 ("testentwickler: 0083-belegstellenriegel-totes-ziel-statt-uebergangen (6 Dateien)"), ausgepackt nach /tmp/claude-1000/bauwege0076-g-abnahme-bedingung-1/vergleichsstand-497bcbc
Eigener Stand fuer den naechsten Lauf: /tmp/claude-1000/bauwege0076-g-abnahme-bedingung-1/stand.json
0 Abweichung(en). Ablage: /tmp/claude-1000/bauwege0076-g-abnahme-bedingung-1
```

Zum Vergleich der Endstand der alten Fassung, gemessen zu Beginn desselben Laufs
(`vorher-0135`, Stand `3840367`): `!! arbeitsbereich ... uebersetzende Ziele=19
(gemessen 18, Abnahme nennt 16)` und `!! arbeitsbereich ... uebersetzende Ziele=17
(gemessen 16, ...)`, zusammen `2 Abweichung(en)`, Rueckgabewert 1.

## Nachweise 2 bis 4 -- Abnahmebedingung 2: der Wegwerf-Baum, zweiseitig

Drei Baeume aus **demselben** Commit `497bcbc`, ausgepackt nach
`/tmp/claude-1000/w0135b/<variante>/` mitsamt `specs/0016-...` -- ohne das Geschwister
`specs/` findet der Belegstellenriegel seine Vorgaben nicht und wird aus einem Grund
rot, der nichts mit der Messung zu tun hat. Alle drei laufen gegen dieselbe
`stand.json` aus Nachweis 1.

| Variante | Eingriff am Baum | Abweichungen | Rueckgabewert |
|---|---|---|---|
| `gleich` | keiner | **0** | **0** |
| `plus` | `pruefstand/test/wegwerf_probe.cpp` dazu (Kopie von `vorrat_probe.cpp`) | **4** | **1** |
| `minus` | `pruefstand/test/vorrat_kernanker_probe.cpp` entfernt | **4** | **1** |

Der Eingriff ist je eine Datei unter `pruefstand/test/`; das `file(GLOB ...
CONFIGURE_DEPENDS)` dort legt je Probendatei ein eigenes `add_executable` an, also
genau ein uebersetzendes Ziel -- ohne dass an einer `CMakeLists.txt` etwas geaendert
werden muesste.

Die roten Zeilen im Wortlaut, `plus`:

```
=== Profil sanitizer-an (FABRIK_SANITIZER=ON) ===
!! arbeitsbereich   konfig code=0  uebersetzende Ziele=21 (Stand davor 20)  -- Zielzahl 21 != Stand davor 20
!! pruefstand       konfig code=0  uebersetzende Ziele=6 (Stand davor 5)  -- Zielzahl 6 != Stand davor 5
=== Profil sanitizer-aus (FABRIK_SANITIZER=OFF) ===
!! arbeitsbereich   konfig code=0  uebersetzende Ziele=19 (Stand davor 18)  -- Zielzahl 19 != Stand davor 18
!! pruefstand       konfig code=0  uebersetzende Ziele=5 (Stand davor 4)  -- Zielzahl 5 != Stand davor 4
4 Abweichung(en). Ablage: /tmp/claude-1000/bauwege0076-i-plus-497bcbc
```

und `minus`:

```
=== Profil sanitizer-an (FABRIK_SANITIZER=ON) ===
!! arbeitsbereich   konfig code=0  uebersetzende Ziele=19 (Stand davor 20)  -- Zielzahl 19 != Stand davor 20
!! pruefstand       konfig code=0  uebersetzende Ziele=4 (Stand davor 5)  -- Zielzahl 4 != Stand davor 5
=== Profil sanitizer-aus (FABRIK_SANITIZER=OFF) ===
!! arbeitsbereich   konfig code=0  uebersetzende Ziele=17 (Stand davor 18)  -- Zielzahl 17 != Stand davor 18
!! pruefstand       konfig code=0  uebersetzende Ziele=3 (Stand davor 4)  -- Zielzahl 3 != Stand davor 4
4 Abweichung(en). Ablage: /tmp/claude-1000/bauwege0076-j-minus-497bcbc
```

**Es reisst genau das Gemeinte, und sonst nichts.** In beiden Mutanten sind alle sechs
`konfig code=0`, alle sechs `bau code=0` und alle sechs `ctest code=0`; `kern` bleibt in
beiden Profilen gruen, weil der Eingriff ihn nicht beruehrt. Die vier Abweichungen
stammen ausschliesslich aus dem Gleichheitsmass -- an `arbeitsbereich` und an
`pruefstand`, in beiden Profilen, also an genau den vier Stellen, an denen die eine
Datei zaehlt.

## Nachweis 5 -- der Weg ueber `git archive` faengt es auch

Bedingung 2 verlangt einen Wegwerf-Baum. Der Vergleichsstand kann aber auch aus einem
Commit kommen, und dieser Weg braucht seinen eigenen roten Nachweis -- er ist die
Vorgabe und laeuft damit oefter als der andere.

    python3 .../bauwege.py e-arbeitsbaum-gegen-dffb251 --gegen dffb251

```
Stand davor: git dffb251 vom 2026-09-04 ("architekt: 0043-t48-groessen-gegenkraft-5 (40 Dateien)"), ausgepackt nach /tmp/claude-1000/bauwege0076-e-arbeitsbaum-gegen-dffb251/vergleichsstand-dffb251
   FABRIK_SANITIZER=OFF   arbeitsbereich=15  kern=10  pruefstand=4
   FABRIK_SANITIZER=ON    arbeitsbereich=17  kern=11  pruefstand=5
!! arbeitsbereich   konfig code=0  uebersetzende Ziele=20 (Stand davor 17)  -- Zielzahl 20 != Stand davor 17
!! kern             konfig code=0  uebersetzende Ziele=12 (Stand davor 11)  -- Zielzahl 12 != Stand davor 11
   pruefstand       konfig code=0  uebersetzende Ziele=5 (Stand davor 5)
!! arbeitsbereich   konfig code=0  uebersetzende Ziele=18 (Stand davor 15)  -- Zielzahl 18 != Stand davor 15
!! kern             konfig code=0  uebersetzende Ziele=11 (Stand davor 10)  -- Zielzahl 11 != Stand davor 10
   pruefstand       konfig code=0  uebersetzende Ziele=4 (Stand davor 4)
4 Abweichung(en).
```

Der Vergleichsstand `15 / 10 / 4` und `17 / 11 / 5` deckt sich mit dem, was der
`kern-pruefer` am 2026-09-05 fuer `dffb251` gemessen hat (`17 / 11 / 5` unter `ON`,
`15 / 10 / 4` unter `OFF`, Rumpf von Paket 0104). Zwei Wege, dieselbe Zahl.

## Nachweis 6 -- ohne Vergleichsstand meldet es rot, nicht gruen

    python3 .../bauwege.py f-ohne-vergleichsstand --gegen kein-solcher-commit

```
!! Vergleichsstand nicht zu bekommen: `git rev-parse --short kein-solcher-commit` gab Code 128: fatal: Needed a single revision
   Ohne ihn faellt das Gleichheitsmass ueber die Zielzahlen aus. Das zaehlt als Abweichung;
   ein ausgefallenes Mass, das gruen meldet, ist der Fehler, gegen den dieses Skript steht.
...
   arbeitsbereich   konfig code=0  uebersetzende Ziele=20 (kein Stand davor)
...
Verglichen gegen: nichts -- s. o.
1 Abweichung(en). Ablage: /tmp/claude-1000/bauwege0076-f-ohne-vergleichsstand
```

Bau und `ctest` laufen weiter durch -- sie sind ohne Vergleichsstand weiter
aussagekraeftig. Nur das Gleichheitsmass faellt aus, und genau dafuer steht die eine
Abweichung.

## Was der Lauf nebenbei gemessen hat

**Die Zahl ist waehrend dieses Laufs zweimal gewandert.** Zu Beginn (Stand `3840367`)
meldete der Arbeitsbereich 19 unter `ON` und 17 unter `OFF`; am Ende (Stand `497bcbc`)
20 und 18. Dazwischen liegt Paket 0083, das ein uebersetzendes Ziel angelegt hat. Eine
feste Zahl im Quelltext waere innerhalb einer knappen Stunde und ohne Zutun dieses
Pakets falsch geworden -- das Gleichheitsmass hat beide Male gestimmt. Das ist der
Beleg fuer die Entscheidung aus 0104, gemessen und nicht argumentiert.

**Der Belegstellenriegel braucht das Geschwister `specs/<vorhaben>`.** Ein Wegwerf-Baum,
der nur `ventures/<vorhaben>` enthaelt, laesst ihn mit
`'.../specs/gleich' ist kein Verzeichnis` rot laufen. Kein Befund gegen den Riegel --
seine Meldung sagt genau, was fehlt --, aber eine Falle fuer jeden, der kuenftig einen
Wegwerf-Baum ohne die Repo-Gestalt aufsetzt. Hier festgehalten, weil es zwei Laeufe
gekostet hat.

## Endstand -- derselbe Lauf noch einmal, nach allen Schreibvorgaengen

Nachweis 1 lief vor dem Schreiben dieser Datei. Weil der Belegstellenriegel jede
Bauquelle liest und eine neue Datei unter `befunde/` ihn haette treffen koennen, ist
Bedingung 1 danach noch einmal gefahren -- mit dem geaenderten Kopf des Skripts, dieser
Protokolldatei und dem Paketstatus `gebaut` im Baum:

    python3 .../bauwege.py z-endstand
    Rueckgabewert: 0

```
Stand davor: git e6710ee vom 2026-09-05 ("kernbauer: 0134-sperrebindung-jeder-kernquelle (34 Dateien)"), ausgepackt nach /tmp/claude-1000/bauwege0076-z-endstand/vergleichsstand-e6710ee
   FABRIK_SANITIZER=OFF   arbeitsbereich=18  kern=11  pruefstand=4
   FABRIK_SANITIZER=ON    arbeitsbereich=20  kern=12  pruefstand=5

=== Profil sanitizer-an (FABRIK_SANITIZER=ON) ===
   arbeitsbereich   konfig code=0  uebersetzende Ziele=20 (Stand davor 20)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 16
   kern             konfig code=0  uebersetzende Ziele=12 (Stand davor 12)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 10
   pruefstand       konfig code=0  uebersetzende Ziele=5 (Stand davor 5)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 4
=== Profil sanitizer-aus (FABRIK_SANITIZER=OFF) ===
   arbeitsbereich   konfig code=0  uebersetzende Ziele=18 (Stand davor 18)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 16
   kern             konfig code=0  uebersetzende Ziele=11 (Stand davor 11)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 10
   pruefstand       konfig code=0  uebersetzende Ziele=4 (Stand davor 4)
      bau code=0
      ctest code=0  100% tests passed, 0 tests failed out of 4

0 Abweichung(en). Ablage: /tmp/claude-1000/bauwege0076-z-endstand
```

`HEAD` ist zwischen Nachweis 1 und diesem Lauf ein drittes Mal gewandert (`3840367` →
`b3dc4b0` → `497bcbc` → `e6710ee`), die sechs Zahlen sind seit `497bcbc` gleich
geblieben. Der Vergleichsstand ist jedes Mal der dann geltende `HEAD` -- eine feste Zahl
haette in dieser Datei schon wieder nachgezogen werden muessen.

## Wozu dieses Paket ausdruecklich nichts sagt

Ob `baulauf.py` seinerseits `ctest --no-tests=error` setzen sollte. Der Befund steht
seit 0110 im Logbuch des Testentwicklers und ist ausserhalb dieses Vorhabens.
