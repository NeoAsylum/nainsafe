---
typ: pruefung
paket: 0137-riegelmeldung-nennt-ihr-profil
pruefer: kern-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Zwoelf eigene Konfigurationen in zwei selbst hergestellten Baeumen, die sich in nichts als `werkzeugkette.cmake` unterscheiden, dazu Bau und `ctest` in beiden Profilen und ein Lauf des fremden Messwerkzeugs `bauwege.py` gegen den genannten Bezugsstand.
befunde: 0
---

# Beide Bedingungen erfuellt; ein Vorschlag zur Regressionssicherung daneben

## Woran gemessen wurde

**Geprueft am Stand `aa65c70`**, gewachsen waehrend des Laufs auf `8ff7cc4`
(`entwurf-pruefer`, `notizen/` und ein Befund -- keine Datei dieses Pakets). Die
Paketdatei traegt am Anfang und am Ende dieses Laufs dieselbe Pruefsumme:

    390f60e12e3991df04b36b6ce66fc78b  werkzeugkette.cmake

**Der Vorher-Stand ist selbst hergestellt, nicht zitiert.** Zwei Baeume, beide aus
`git archive aa65c70` samt `specs` und `decisions`; in den einen ist die Fassung von
`werkzeugkette.cmake` aus `5d5e2d6` (Paket 0132) darueber ausgepackt. `diff -rq` ueber
beide Baeume nennt genau eine abweichende Datei:

    Files .../vorher/.../werkzeugkette.cmake and .../nachher/.../werkzeugkette.cmake differ

    390f60e12e3991df04b36b6ce66fc78b  nachher/werkzeugkette.cmake
    633f394ac4c9a260e4aba95d9018a018  vorher/werkzeugkette.cmake

Der Vergleich ist damit eine Isolierung: Zwischen dem Baucommit `d8eb90a` und `aa65c70`
liegen zehn Commits, davon zwei in `kern`/`pruefstand`/`werkzeuge` (`751d01c`, `9449bda`).
Gegen den Baucommit selbst zu vergleichen haette deren Ziele mit hineingezogen.

**Der Bezugsstand des Pakets ist nachgeschlagen und stimmt.** `b2829c8` existiert, ist
der direkte Elter von `d8eb90a` (`git log -1 --format=%P d8eb90a`), und
`werkzeugkette.cmake` steht dort in der Fassung `5d5e2d6` -- also genau der, die ich als
Vorher-Fassung benutzt habe. Werkzeugkette: cmake 4.2.3, g++ 15.2.0 (die in
`FABRIK_UEBERSETZER_GEPRUEFT` festgenagelte Version, also ohne die Abweichungswarnung).

## Bedingung 1 -- das Profil ist aus der Ausgabe allein erkennbar

Sechs getrennte, leere Baubaeume am Nachher-Stand, je Bauweg paarweise gegenuebergestellt.
Aufrufform:

    cmake -S <baum>[/kern|/pruefstand] -B <leerer baubaum> -DFABRIK_SANITIZER=<ON|OFF>

**Arbeitsbereich** -- die beiden Ausgaben unterscheiden sich in zwei Zeilen, die zweite
nennt Schalter und Wert:

    < -- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 22 uebersetzende Ziele geprueft, ...
    > -- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=OFF (falsch): 20 uebersetzende Ziele geprueft, ...

**Kern allein** -- ebenso:

    < -- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 14 uebersetzende Ziele geprueft, ...
    > -- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=OFF (falsch): 13 uebersetzende Ziele geprueft, ...

**Pruefstand allein** -- der Fall, den die Bedingung namentlich verlangt. Das Paar
unterscheidet sich in genau einer Zeile ausser der Pfadzeile, und diese Zeile nennt den
Schalter:

    < -- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=ON (wahr): 5 uebersetzende Ziele geprueft, ...
    > -- Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=OFF (falsch): 4 uebersetzende Ziele geprueft, ...

**Der Negativnachweis dazu, am selben Aufruf am Vorher-Stand** -- das Paar des Alleinbaus
des Pruefstands unterscheidet sich dort in nichts als zwei Ziffern, kein Wort nennt den
Schalter:

    < -- Warnsatz-Schlussriegel: 5 uebersetzende Ziele geprueft, ... 89 Schaltereintraege.
    > -- Warnsatz-Schlussriegel: 4 uebersetzende Ziele geprueft, ... 68 Schaltereintraege.

Damit ist auch die Zahlenangabe im neuen Kommentar unabhaengig bestaetigt: Sie behauptet
fuer `b2829c8` „5 gegen 4 Ziele, 89 gegen 68 Schaltereintraege". Ich habe `b2829c8` dafuer
eigens ausgepackt und den Alleinbau des Pruefstands dort in beiden Profilen konfiguriert;
die vier Zahlen kommen genau so heraus.

**Zweiseitigkeit, gemessen ueber die Leseart und nicht nur ueber ON/OFF.** Der Kommentar
behauptet, gelesen werde mit demselben `if()`, mit dem `kern/CMakeLists.txt:201` und
`pruefstand/CMakeLists.txt:68` ueber ihre Sanitizerziele entscheiden. Drei weitere
Konfigurationen des Kern-Alleinbaus mit abweichenden Schreibweisen:

| Aufruf | Meldung | Nullabhaengigkeitsriegel | Ziele |
|---|---|---|---|
| `-DFABRIK_SANITIZER=1` | `=1 (wahr)` | 2 Ziele, `kern_geprueft` da | 14 |
| `-DFABRIK_SANITIZER=0` | `=0 (falsch)` | 1 Ziel | 13 |
| `-DFABRIK_SANITIZER=` | `= (falsch)` | 1 Ziel | 13 |

Das Wahrheitswort stimmt in allen drei Faellen mit dem ueberein, was der Baum wirklich
angelegt hat. Die dritte Zeile ist der Randfall, den der Kommentar selbst nennt: Der rohe
Wert allein saehe wie ein drittes Profil aus, das Wahrheitswort ordnet ihn richtig zu.
Beide Haelften der Angabe tragen also je etwas, das die andere nicht traegt.

## Bedingung 2 -- kein Urteil aendert sich

**Alle zwoelf Konfigurationen mit Code 0** (sechs je Stand; jede Ausgabe endet mit
`Build files have been written to`).

**Die Zahl der uebersetzenden Ziele, je Profil gegen den eigenen Stand davor** -- gleicher
Baum, gleicher Schalter, einmal mit und einmal ohne die Aenderung. Kein Sollwert
ausgeschrieben, sondern beide Seiten gemessen:

| Bauweg | Profil | vorher | nachher |
|---|---|---|---|
| Arbeitsbereich | ON | 22 | 22 |
| Arbeitsbereich | OFF | 20 | 20 |
| Kern allein | ON | 14 | 14 |
| Kern allein | OFF | 13 | 13 |
| Pruefstand allein | ON | 5 | 5 |
| Pruefstand allein | OFF | 4 | 4 |

Die dritte Zahl ebenso unveraendert (388/340, 242/221, 89/68).

**Die Meldungen der uebrigen Riegel bleiben im Wortlaut unveraendert.** Alle sechs
Gegenueberstellungen vorher/nachher am selben Bauweg und Profil zeigen genau zwei
abweichende Zeilen: die Riegelzeile und die Pfadzeile des Baubaums. Sperrebindungsriegel,
Nullabhaengigkeitsriegel und die Meldungen ueber uebersprungene Mitglieder sind
zeichengleich.

**Bau und `ctest` in beiden Profilen mit Code 0:** Arbeitsbereich, je frisch gebaut,
`100% tests passed, 0 tests failed out of 18` unter ON wie unter OFF.

**Unabhaengiger zweiter Durchgang mit dem Werkzeug der Fabrik.** Ich habe zusaetzlich
`befunde/messung-0076/bauwege.py` selbst gefahren -- es ist das Skript, das Paket 0135 fuer
genau diese Frage hergerichtet hat, und es misst den Vergleichsstand selbst, statt ihn zu
uebernehmen:

    python3 befunde/messung-0076/bauwege.py pruefung0137 --gegen b2829c8

    Stand davor: git b2829c8 vom 2026-09-06 ...
       FABRIK_SANITIZER=OFF   arbeitsbereich=20  kern=13  pruefstand=4
       FABRIK_SANITIZER=ON    arbeitsbereich=22  kern=14  pruefstand=5
    ...
    0 Abweichung(en).

Sechs Konfigurationen, sechs Bauten, sechs `ctest`-Laeufe (18, 12 und 3 Proben je Bauweg),
alle Code 0, alle sechs Zielzahlen gleich dem Bezugsstand. Nebenbefund mit Belegwert: Der
Anker `ZIELZAHL = re.compile(r"(\d+) uebersetzende Ziele")` in jenem Skript trifft die neue
Meldung weiterhin genau einmal -- die Umformulierung hat das Messgeraet nicht mehrdeutig
gemacht.

## Was ausserdem geprueft wurde

- **Determinismus der Meldung.** Sie haengt an einer Cache-Variablen, an keiner Zeit, an
  keiner Adresse, an keinem Gleitkomma. Nachgefahren: dieselbe Quelle ein zweites Mal in
  einen frischen Baubaum konfiguriert -- die ganze Ausgabe ist zeichengleich bis auf die
  Pfadzeile.
- **Die Behauptung des Kommentars ueber die Leseart** ist am Quelltext gegengelesen:
  `kern/CMakeLists.txt:201` und `pruefstand/CMakeLists.txt:68` benutzen wortgleich
  `if(FABRIK_SANITIZER)`. Es gibt keine zweite Auslegung, die abweichen koennte.
- **Kein Verbraucher der Meldung ist gebrochen.** `git grep Warnsatz-Schlussriegel` ueber
  die verwalteten Dateien findet drei Treffer, alle in Kommentaren; kein Skript und keine
  Probe wertet den Meldungstext aus. `nachbau.py` urteilt allein ueber Rueckgabewerte.
- **Die vier Ausschluesse aus „Was nicht dazugehoert" sind eingehalten.** Der Diff besteht
  aus einem Hunk: ein Kommentarblock, ein `if`/`else` fuer `profilwort`, zwei geaenderte
  Zeilen der Meldung. Zaehlweise, Vorgabewert (`option(... ON)`, Zeile 62) und die zweite
  Zahl aus 0132 sind unberuehrt; die Abnahme schreibt keine Zielzahl aus.
- **Der echte Bericht sieht heute anders aus.** In `befunde/uebersetzung-2026-09-06.md`
  tragen alle sechs Meldungen dieses Riegels ihr Profil -- genau die sechs, von denen das
  Paket sagte, keine einzige nenne es.

Gesucht habe ich ausserdem nach dem, was ein `zurueck` getragen haette und nicht da war:
eine Zeile, die in beiden Profilen dasselbe meldet; ein Wahrheitswort, das der
tatsaechlichen Zielanlage widerspricht; eine verschobene oder verlorene Zahl; eine
Riegelmeldung, die ihren Wortlaut nebenbei geaendert hat; ein Bauweg, auf dem die Zeile
fehlt.

## Kein Befund, aber eine gemessene Luecke -- Vorschlag `0185`

Die Angabe ist richtig und sie ist auf allen drei Bauwegen da. **Nichts haelt sie dort
fest.** Ich habe das nicht vermutet, sondern gefahren: Der Vorher-Baum ist der Mutant, in
dem das Profil fehlt. Gebaut und `ctest` gefahren, Profil ON --

    100% tests passed, 0 tests failed out of 18

-- dieselbe Zeile wie am Nachher-Baum. Achtzehn Proben, und keine merkt den Unterschied.
Dazu kommt, dass der Uebersetzungsbericht nur `FABRIK_SANITIZER=ON` faehrt: Eine fest
verdrahtete Angabe `ON (wahr)` waere in jedem Bericht, den diese Fabrik erzeugt, von der
richtigen nicht zu unterscheiden. Der Vorschlag steht unter
`aufgaben/0185-schlussriegel-profilangabe-ohne-regressionsnachweis.md`.

**Die Abnahme senke ich damit nicht und erhoehe sie nicht.** Bedingung 1 verlangt, die
Zweiseitigkeit in diesem Lauf zu *zeigen*; das ist geschehen. Sie zu *bewachen* verlangt
sie nicht, und ein Prueferbefund, der ihr das nachtraeglich anhaengt, verschoebe die
Abnahmegrenze eines abgeschlossenen Pakets -- genau die Bauart, gegen die sich 0104
entschieden hat und die dieses Paket in seinem eigenen Rumpf ablehnt.

## Nummernkollision moeglich

`0185` ist frei gewaehlt oberhalb der hoechsten vorhandenen Nummer (`0181`). Am 2026-09-06
haben zwei Prueferlaeufe im selben Zeitfenster dieselbe Nummer belegt; laeuft parallel ein
weiterer, raeumt der Projektmanager auf.

## Ablage

Alle Baeume, Baubaeume und Protokolle liegen unter
`befunde/bau-pruefung-0137/` (nicht versioniert, `ventures/**/bau-*/` steht in
`.gitignore`): `vorher/`, `nachher/`, `bezug/`, die zwoelf `log-*.txt`, die
Bau- und `ctest`-Protokolle und `bauwege-lauf.txt`.
