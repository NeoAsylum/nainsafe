# Nachweis zu Paket 0137 -- die Riegelmeldung nennt ihr Profil

- **Bezugsstand (vor):** `b2829c8c55cecde4ac1453511e1de7b56e4426c7`, einmal gelesen und
  hier ueberall zitiert. Der Zweig bewegt sich waehrend eines Laufs; eine zweite Lesung
  waere ein zweiter Stand.
- **Geaenderte Datei:** `werkzeugkette.cmake`, sonst keine.
- **Erzeugt von:** `nachweis.py` in diesem Verzeichnis, ein Aufruf ohne Argumente.
  Der Lauf im Wortlaut steht in `lauf.txt`, Rueckgabecode 0, Schlusszeile
  `Abweichungen: 0`.

## Womit gemessen wurde

Zwei Wegwerfbaeume, nicht der Arbeitsbaum. `vor` kommt aus `git archive` des oben
genannten Standes, `nach` ist dessen Kopie mit der einen geaenderten Datei darueber;
`diff -rq` ueber beide nennt genau diese eine Datei. Der Grund steht im Kopf des Skripts:
Der Arbeitsbaum traegt die halbfertige Arbeit fremder Parallellaeufe, und ein
Vorher-Nachher-Vergleich darauf misst den Fremdlauf statt die Aenderung.

Jeder der zwoelf Baubaeume wird vor dem Konfigurieren geleert und neu angelegt. Ein
stehengebliebener Baum bricht mit "does not match the source used to generate cache" ab
-- an beiden Staenden gleich, sieht also nach Gleichstand aus und ist keiner.

`specs/` liegt in beiden Baeumen neben `ventures/`. Der Belegstellenriegel sucht seine
Vorgaben als `<venture>/../../specs/<name>`; flach abgelegt faellt er aus, und zwar an
beiden Staenden gleich.

## Was die Aenderung ist

Die Meldung des Warnsatz-Schlussriegels lautet jetzt

    Warnsatz-Schlussriegel im Profil FABRIK_SANITIZER=<wert> (<leseart>): <n> uebersetzende Ziele geprueft, ...

statt

    Warnsatz-Schlussriegel: <n> uebersetzende Ziele geprueft, ...

Beide Haelften stehen da, und jede faengt etwas anderes: der rohe Wert, weil nur er sich
gegen die Kommandozeile abgleichen laesst, die im Uebersetzungsbericht auf die ersten
beiden Worte gekuerzt ist; die Leseart als Wahrheitswert, weil `=1` und `=ON` dasselbe
Profil meinen und verschieden dastehen. Gelesen wird mit demselben `if()`, mit dem
`kern/CMakeLists.txt` und `pruefstand/CMakeLists.txt` ueber ihre Sanitizerziele
entscheiden -- also nicht mit einer zweiten Auslegung desselben Schalters.

**Was die Angabe nicht sagt:** dass in diesem Baum Sanitizerziele stehen. Sie nennt den
Schalter, unter dem gezaehlt wurde, nicht das Ergebnis seiner Wirkung.

## Bedingung 1 -- das Profil ist aus der Ausgabe allein erkennbar

Sechs Konfigurationen je Stand, drei Bauwege mal zwei Profile. Verglichen wird je Bauweg
das Paar ON gegen OFF; gesucht ist eine Zeile, die `FABRIK_SANITIZER=` samt Wert nennt
und in den beiden Laeufen **verschieden** lautet.

    Stand   Bauweg               solche Zeile vorhanden und verschieden
    vor     arbeitsbereich       nein
    vor     kern-allein          nein
    vor     pruefstand-allein    nein
    nach    arbeitsbereich       ja
    nach    kern-allein          ja
    nach    pruefstand-allein    ja

Das ist die zweiseitige Haelfte: Am Stand davor findet das Suchmuster auf **keinem** der
drei Wege etwas -- auch dort nicht, wo der Nullabhaengigkeitsriegel `kern_geprueft`
mitzaehlt und das Profil dadurch zufaellig erschliessbar war. Jene Zeile nennt den
Schalter nicht, sie nennt ein Ziel. Am Stand danach steht die Zeile auf allen drei Wegen
und sagt im einen Lauf etwas anderes als im anderen. Der Wortlaut aller zwoelf Zeilen
steht in `lauf.txt`.

**Das Paar des Alleinbaus des Pruefstands** ist der Fall, um den das Paket geschrieben
ist. Vorher unterschieden sich seine beiden Ausgaben in nichts als zwei Ziffern -- 5
gegen 4 uebersetzende Ziele und 89 gegen 68 Schaltereintraege --, und kein Wort nannte
den Schalter. Nachher unterscheiden sie sich zusaetzlich in
`FABRIK_SANITIZER=ON (wahr)` gegen `FABRIK_SANITIZER=OFF (falsch)`.

## Bedingung 2 -- kein Urteil aendert sich

Alle zwoelf Konfigurationen mit Code 0. Je Bauweg und Profil der Vergleich vor gegen
nach -- gleicher Baum, gleicher Schalter, einmal mit und einmal ohne die Aenderung.
Eingeebnet werden vorher der Pfad des Baubaums und die gemessene Dauer; beides ist
zwischen zwei Laeufen ohnehin verschieden und sagt nichts ueber die Aenderung.

In allen sechs Faellen aendert sich **genau eine** Zeile, und es ist die des
Warnsatz-Schlussriegels. Kein anderer Riegel aendert seinen Wortlaut.

Die drei Zahlen dieser Zeile bleiben je Profil dieselben. Sie stehen hier als Vergleich
gegen den eigenen Stand davor und nicht als Sollwert -- die Begruendung dafuer steht in
Paket 0104 und im Kommentar ueber der Meldung; ausgeschrieben in einer `abnahme` waere
sie unzulaessig.

    Bauweg               Profil   Ziele / Schnittstellen / Schaltereintraege
    arbeitsbereich       ON       22 / 0 / 388   vor wie nach
    arbeitsbereich       OFF      20 / 0 / 340   vor wie nach
    kern-allein          ON       14 / 0 / 242   vor wie nach
    kern-allein          OFF      13 / 0 / 221   vor wie nach
    pruefstand-allein    ON        5 / 0 /  89   vor wie nach
    pruefstand-allein    OFF       4 / 0 /  68   vor wie nach

Bau und Proben im Arbeitsbereich des Standes `nach`, beide Profile:

    Profil ON    cmake --build Code 0   ctest Code 0   100% tests passed, 0 tests failed out of 18
    Profil OFF   cmake --build Code 0   ctest Code 0   100% tests passed, 0 tests failed out of 18

## Was nicht angefasst wurde

Die Zahlen selbst und ihre Zaehlweise, der Vorgabewert des Schalters (`ON`, unveraendert
in Zeile 62 der `werkzeugkette.cmake`) und die zweite Zahl aus Paket 0132, die bereits im
Baum steht.

Kein Skript im Vorhaben liest den Wortlaut dieser Meldung. Nachgesehen wurde in
`befunde/pruefung-0066/nachbau.py` -- der Waechter des Schlussriegels sucht
"gefunden in", "es fehlen:" und "kein einziges uebersetzendes" -- und mit einer Suche
nach `uebersetzende Ziele geprueft` und `Warnsatz-Schlussriegel` ueber alle `.py`,
`.cpp`, `.cmake` und `CMakeLists.txt` des Vorhabens. Ausserhalb der Bauablagen und der
alten Messungen trifft sie nur die Stelle selbst und zwei Kommentare.
