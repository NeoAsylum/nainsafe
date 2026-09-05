---
typ: pruefung
paket: 0135-bauwege-sollzahl-gegen-eigenen-stand
pruefer: test-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Beide Abnahmeseiten selbst gefahren -- unveraenderter Arbeitsbaum beide Profile 0 Abweichungen Rueckgabewert 0, eigener Wegwerf-Mutant (Mitglied entfernt, anderes Mittel als der Bauagent) meldet Zielzahl-Abweichung und Rueckgabewert 1
befunde: 0
---

# Pruefung 0135 -- `bauwege.py` misst gegen den eigenen Stand davor

Geprueft wurde ausschliesslich durch eigene Laeufe; das Protokoll des Bauagenten
(`befunde/messung-0135/protokoll.md`) habe ich erst **nach** den eigenen Messungen
gegengelesen. Alle Ablagen unter `$TMPDIR`, das Repo blieb unberuehrt.

## Wo die Aenderung liegt

Der Commit mit dem Paketbetreff (`a8e1ce5`) traegt nur Logbuchdateien. Die Arbeit
liegt gebuendelt unter fremden Betreffs -- bekanntes Runner-Verhalten:

- `497bcbc` ("testentwickler: 0083 ..."): `bauwege.py` +302/-43, die Neufassung.
- `cb3914c` ("testentwickler: 0133 ..."): `bauwege.py` +9/-3, Docstring-Messwert
  auf `497bcbc` nachgezogen.

Arbeitsbaum und `HEAD` sind an der Datei identisch (`git diff HEAD` leer). Die
Altfassung `497bcbc^` traegt in Zeile 36 exakt die im Paket genannte feste Sollzahl
`"arbeitsbereich": (WURZEL, 16, {"ON": 18, "OFF": 16})` -- nachgeschlagen, nicht
uebernommen. Ausser `bauwege.py` gehoert keine der Dateien in beiden Commits zur
`dateien`-Liste dieses Pakets; `werkzeugkette.cmake`, `nachbau.py` und der Riegel
sind vom 0135-Anteil unberuehrt.

## Bedingung 1 -- unveraenderter Arbeitsbaum, beide Profile

    cd ventures/0016-hedgefonds-simulation-echte-weltwirtschaft
    python3 befunde/messung-0076/bauwege.py pruefer0135
    Rueckgabewert: 0

Ein Aufruf faehrt beide Profile. Ergebnis: **0 Abweichung(en)**, alle sechs Bauwege
`konfig code=0`, `bau code=0`, `ctest code=0` (16/10/4 Proben je Weg). Zielzahlen
ON 20/12/5, OFF 18/11/4 -- identisch mit dem Vergleichsstand, den das Skript selbst
aus `HEAD` (`a8e1ce5`) per `git archive` gemessen hat, und identisch mit den Zahlen
im Protokoll des Bauagenten (dort an `497bcbc` und `e6710ee`; dazwischen liegen nur
Notiz- und Aufgaben-Commits). Der Stand ist in der Ausgabe benannt: `Stand davor:
git a8e1ce5 vom 2026-09-05 (...)` und am Ende `Verglichen gegen: ...`.

## Sollzahl-Bedingung

Im Code steht keine Sollzahl mehr (`WEGE` traegt nur noch Pfade). Die Zahlen im
Docstring tragen Bauweg, Profil, Datum und Stand (`Gemessen am 2026-09-05 am Stand
497bcbc`) samt dem Satz, dass es ein Messwert und keine Vorgabe ist -- die Form, die
die Abnahme verlangt.

## Bedingung 2 -- der Wegwerf-Baum, zweiseitig

Eigener Mutant, absichtlich mit **anderem Mittel** als die des Bauagenten (der
fuegte/entfernte Probendateien unter `pruefstand/test/`): Baum aus `HEAD` per
`git archive` nach `$TMPDIR/mutant0135`, dort in `CMakeLists.txt` das Mitglied
`werkzeuge/bezeichner` aus `FABRIK_MITGLIEDER` gestrichen (Trefferbremse: Nadel
`\n    werkzeuge/bezeichner)` genau 1x). Lauf gegen die `stand.json` aus Bedingung 1:

    python3 $TMPDIR/mutant0135/befunde/messung-0076/bauwege.py mutant0135 \
        --gegen-datei /tmp/claude-1000/bauwege0076-pruefer0135/stand.json
    Rueckgabewert: 1

    !! arbeitsbereich ... uebersetzende Ziele=19 (Stand davor 20) -- Zielzahl 19 != Stand davor 20   [ON]
    !! arbeitsbereich ... uebersetzende Ziele=17 (Stand davor 18) -- Zielzahl 17 != Stand davor 18   [OFF]
    4 Abweichung(en).

Die zwei weiteren Abweichungen sind `ctest code=8` im Arbeitsbereich (der
`belegstellen_riegel` bemerkt den Eingriff ebenfalls); `kern` und `pruefstand`
bleiben in beiden Profilen vollstaendig gruen. Die Zielzahl-Abweichungen stehen
unabhaengig davon -- das Skript hat den Fehler nicht umgedreht, es meldet ihn als
das, was er ist.

Zusaetzlich die Kernbehauptung "ein ausgefallenes Mass meldet nie gruen" gestochen:
derselbe Baum ohne Git-Repo, Vorgabe `--gegen HEAD`:

    Rueckgabewert: 1
    !! Vergleichsstand nicht zu bekommen: `git rev-parse --short HEAD` gab Code 128 ...

Der Ausfall zaehlt als Abweichung, Bau und `ctest` laufen trotzdem, kein Schalter
macht gruen. Deckt sich mit Nachweis 6 des Bauagenten (unbekannter Commit).

## Gegengelesen nach der Messung

Das Protokoll des Bauagenten stimmt in allen Zahlen mit meinen Laeufen ueberein und
deckt zusaetzlich `plus` (Ziel hinzugefuegt, 4 Abweichungen ausschliesslich aus dem
Gleichheitsmass), den `--gegen <commit>`-Weg mit Kreuzabgleich gegen die Messung des
kern-pruefers zu 0104, und einen Endstands-Wiederholungslauf.

## Randnotizen ohne Urteilswirkung

- `ctest --no-tests=error` stand nicht im Paket; der Bauagent weist es selbst aus.
  Es haertet (still-gruenes ctest ohne Proben wird rot), senkt nichts und liegt in
  der Paketdatei -- kein Befund. Die Anschlussfrage fuer `baulauf.py` traegt bereits
  Vorschlag 0127.
- Das Gleichheitsmass mit Vorgabe `HEAD` ist blind fuer ein Ziel, das im selben
  Commit schon enthalten ist -- gewollt (die Zahl darf wachsen); die scharfe Form
  ist das `vorher`/`nachher`-Paar ueber `--gegen-datei`, und genau die habe ich fuer
  Bedingung 2 benutzt.
- Ein Wegwerf-Baum ohne das Geschwister `specs/<vorhaben>` laesst den
  Belegstellenriegel rot laufen (so auch bei meinem Mutanten); das Protokoll haelt
  die Falle fest. Fuer die Abnahme unerheblich, weil die Zielzahl-Abweichung
  unabhaengig davon gemeldet wird.

## Wonach ich sonst gesucht habe

Abgeschwaechte Zusicherungen im Diff (die entfernte Sollzahl ist der Paketauftrag
aus 0104, keine Abschwaechung; sonst ist der Diff haertend), Sollzahlen ohne
Profil/Datum im ganzen Skript (keine), Schnitt der 0135-Arbeit mit fremden
`dateien`-Listen (keiner), Namenskollision bei Befunddateien (keine).
