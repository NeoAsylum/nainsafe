---
typ: pruefung
paket: 0132-riegelmeldung-nennt-gesammelte-eintraege
pruefer: kern-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Beide Bedingungen einzeln nachgefahren -- Bedingung 1 zweimal an demselben Wegwerf-Baum (unveraendert 17, mit geleertem fabrik_riegel_sammeln 0, beide Konfiguration Code 0 und wortgleich gruen), Bedingung 2 mit nachbau.py an beiden Staenden und mit bauwege.py ueber drei Bauwege in zwei Profilen.
befunde: 0
---

# Pruefung 0132 -- der Riegel nennt, wieviel er eingesammelt hat

## Was geprueft wurde, und woran

Gegenstand: werkzeugkette.cmake, md5 633f394ac4c9a260e4aba95d9018a018 zu Beginn
**und** am Ende dieses Laufs. Stand des Repos: 83faa06. Die Aenderung des Pakets liegt
in 5d5e2d6; ein git log auf die Datei nennt diesen Commit als den juengsten auf ihr,
und der Arbeitsbaum weicht nicht von ihm ab. Der Vorherstand ist also 5d5e2d6^, also
der Commit d80beae.

Der Commit 5d5e2d6 beruehrt drei Dateien: werkzeugkette.cmake (+47/-8), die Paketdatei
unter aufgaben/ (nur status offen -> gebaut) und das Logbuch des Bauagenten. Die
dateien-Liste des Pakets nennt genau eine Datei, und genau eine Baudatei ist geaendert.

Die drei Commits **nach** dem Paket (5bb5375, 9fd8c3f, 83faa06) fassen kein
CMakeLists.txt an und legen keine Datei unter kern/test/, pruefstand/test/, src/ oder
werkzeuge/ an -- mit git ls-tree an beiden Staenden nachgesehen, die Dateilisten sind
gleich. Der Zielbestand ist zwischen 5d5e2d6^ und 83faa06 unveraendert; der Vergleich
gegen 5d5e2d6^ isoliert dieses Paket.

Umgebung: CMake 4.2.3, g++ 15.2.0 (Ubuntu), WSL2. Nachweisort Rang 1 -- alle
Wegwerf-Baeume unter TMPDIR, kein Bauverzeichnis im Repo.

## Bedingung 1 -- ein stumpfer Riegel faellt an einer Zahl auf

**Erfuellt.**

Der Wegwerf-Baum ist p_positiv aus befunde/pruefung-0066/nachbau.py: ein Ziel, eine
Quelldatei, keine eigenen Schalter --

    add_library(z STATIC z.cpp)
    fabrik_warnsatz_anlegen(z)

Beide Laeufe gehen ueber **denselben** Baum unter
/tmp/claude-1000/nachbau0066-HEAD/p_positiv; getauscht wurde allein die daneben per
include eingebundene Kette.

Die stumpfe Fassung ist der geleerte Makrorumpf: head -n 309 und tail -n +322 ueber die
geprueften Datei, aneinandergehaengt, sodass die Zeile mit macro(fabrik_riegel_sammeln
unmittelbar auf endmacro() trifft. Sie ist nicht eingecheckt (md5 f137ecea..., nur unter
TMPDIR) und sie ist der schaerfere der beiden von der Abnahme zugelassenen Wege: ein
return() im Makro haette den ganzen Riegel verlassen und gar keine Meldung erzeugt.

    cmake -S .../p_positiv -B .../p_positiv/build-scharf      Rueckgabe 0
    -- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz und
       ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in
       ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten:
       17 Schaltereintraege.

    cmake -S .../p_positiv -B .../p_positiv/build-stumpf2     Rueckgabe 0
    -- Warnsatz-Schlussriegel: 1 uebersetzende Ziele geprueft, alle mit Warnsatz und
       ohne Pauschalabschalter; dazu 0 Schnittstellenziele ohne Pauschalabschalter in
       ihrer Schnittstelle. Eingesammelt und gegen die Pauschalmuster gehalten:
       0 Schaltereintraege.

Beide Konfiguration Code 0, beide melden "alle mit Warnsatz und ohne
Pauschalabschalter", beide Zahlen abgedruckt: **17 gegen 0**. Ausser der neuen Zahl
unterscheidet die zwei Zeilen kein Zeichen.

**Die Positivkontrolle zur stumpfen Fassung gehoert dazu**, sonst zeigt die 0 nur, dass
irgendetwas anders ist. Derselbe Tausch am Baum r2_privatw -- gleiches Manifest plus
target_compile_options(z PRIVATE -w):

    scharf:  Konfiguration Code 1, Zeile "gefunden in: COMPILE_OPTIONS an z:  -w",
             dazu "Aus 18 eingesammelten Schaltereintraegen stammt dieser Befund."
    stumpf:  Rueckgabe 0, wortgleich dieselbe gruene Zeile wie p_positiv oben,
             mit "0 Schaltereintraege."

Das ist der Fall, gegen den das Paket geschrieben ist, hergestellt statt behauptet: Ein
Baum mit -w auf der Uebersetzerzeile konfiguriert unter der stumpfen Fassung gruen und
zeichengleich wie ein sauberer -- **bis auf die neue Zahl.**

## Bedingung 2 -- kein Urteil aendert sich

**Erfuellt**, in beiden Haelften.

**a) nachbau.py, 22 Wegwerf-Baeume, an beiden Staenden gefahren.**

    python3 befunde/pruefung-0066/nachbau.py             -> 0 Abweichung(en) vom Soll
    python3 befunde/pruefung-0066/nachbau.py 5d5e2d6^    -> 0 Abweichung(en) vom Soll

Ein diff ueber die zwei Ausgaben zeigt ausser der Kopfzeile (Stand, Bytezahl) und dem
Ablagepfad in den Dateinamen **keinen Unterschied**. Alle 22 Konfigurationscodes gleich,
die Positivkontrolle p_positiv baut an beiden Staenden rot mit demselben
-Werror=float-conversion.

Der Wortlaut ist zusaetzlich unverkuerzt gegengelesen, weil nachbau.py seine Zeilen bei
150 Zeichen abschneidet. Ein diff ueber die vollen konfig.log:

* r1_ohnesatz: die Zeile "es fehlen: -Wall ... -fwrapv -fno-fast-math" ist
  **zeichengleich**. Neu ist allein ein Absatz danach ("Eingesammelt hat der Riegel auf
  diesem Lauf 0 Schaltereintraege ...").
* r2_privatw: die Zeile "gefunden in:              COMPILE_OPTIONS an z:  -w" ist
  **zeichengleich**. Neu ist allein der Absatz "Aus 18 eingesammelten
  Schaltereintraegen ...".

Die uebrigen Unterschiede sind die Zeilennummern in der CMake-Fehlerkopfzeile und der
Ablagepfad.

**b) Die drei Bauwege in beiden Profilen.** Aufruf:
python3 befunde/messung-0076/bauwege.py kp0132 --gegen 5d5e2d6^ -- Rueckgabe 0,
0 Abweichung(en).

| Profil | Bauweg | konfig | bau | ctest | Zielzahl | Stand davor |
|---|---|---|---|---|---|---|
| ON  | Arbeitsbereich | 0 | 0 | 0 (18/18) | 22 | 22 |
| ON  | kern allein    | 0 | 0 | 0 (12/12) | 14 | 14 |
| ON  | pruefstand     | 0 | 0 | 0 (3/3)   | 5  | 5  |
| OFF | Arbeitsbereich | 0 | 0 | 0 (18/18) | 20 | 20 |
| OFF | kern allein    | 0 | 0 | 0 (12/12) | 13 | 13 |
| OFF | pruefstand     | 0 | 0 | 0 (3/3)   | 4  | 4  |

Verglichen wurde je Profil gegen den eigenen Stand davor (d80beae, ausgepackt und
konfiguriert), nicht gegen einen Sollwert -- die Form aus 0104. Im Arbeitsbereich laeuft
dabei schlussriegel_nachbau als Probe Nr. 18 mit und ist gruen: Der Waechter des Riegels
prueft die neue Fassung also von selbst mit.

## Die zweite, unabhaengige Zaehlung

Eine Riegelzahl, die nur sich selbst bezeugt, ist keine. Alle Werte sind gegen eine
Handrechnung gehalten. Der Warnsatz umfasst 17 Schalter (abgelesen an der Zeile
"es fehlen" von r1_ohnesatz), die Sanitizerschalter sind zwei.

Die sechs Bauwege, Zahl je aus dem eigenen konfig.log:

    OFF  pruefstand       68  --  4 mal 17
    OFF  kern            221  -- 13 mal 17
    OFF  Arbeitsbereich  340  -- 20 mal 17
    ON   pruefstand       89  --  3 mal 17, plus 17 fuer pruefstand,
                                  plus 21 fuer pruefstand_geprueft
    ON   kern            242  -- 12 mal 17, plus 17 fuer kern,
                                  plus 21 fuer kern_geprueft
    ON   Arbeitsbereich  388  -- 242 plus 89 plus dreimal 19

Die 21 der beiden geprueft-Ziele sind 17 Warnsatz plus zwei Sanitizerschalter in
COMPILE_OPTIONS plus dieselben zwei in INTERFACE_COMPILE_OPTIONS -- die Zeilen mit
PUBLIC in kern/CMakeLists.txt Zeile 206 und pruefstand/CMakeLists.txt Zeile 73. Die
dreimal 19 sind belegstellen_riegel, bezeichner_riegel und mutationstreiber, die ihre
zwei Sanitizerschalter PRIVATE bekommen; deshalb liegt der Arbeitsbereich um 6 ueber
der Summe der beiden Alleinbauten. **Alle sechs Zahlen gehen ohne Rest auf.**

Dazu die 21 Wegwerf-Baeume, an denen die Meldung eine Zahl nennt -- jede von Hand
nachgerechnet, jede getroffen:

    p_positiv 17                 c2_leereiface 17 (leere Schnittstelle traegt nichts)
    c1_wnoconv 18                e7_ifacegut 18 (17 plus 1 aus der Schnittstelle)
    e6_targetobjects 34          zwei Ziele mit Satz; TARGET_OBJECTS traegt nichts bei
    r4_staticpublic 19           18 aus COMPILE_OPTIONS, 1 aus INTERFACE_COMPILE_OPTIONS
    e4_zweiworte 18              "-O0 -w" ist EIN Eintrag, nicht zwei Woerter
    r3_shellform 18              "SHELL:-Wno-error -w" ebenso
    r1_ohnesatz 0                kein Warnsatz, keine Eigenschaft
    a1, b1, b1b, b2, e1, e2, e5, e8, e10, f1, x_unterbaum  je 18

Der 22. Baum, r5_nurschnittstelle, nennt keine Zahl; er faellt vorher in den Abbruch
"kein einziges uebersetzendes Ziel unter ..." (Zeile 998). Das ist kein Loch: Jener
Abbruch beantwortet die Frage, ob der Riegel etwas gesehen hat, bereits mit einem lauten
Nein und mit Code 1.

## Wonach ich sonst gesucht habe

* **Zaehlt er das Eingesammelte und nicht die Zugriffe?** Ja. Die Summierung haengt an
  list(LENGTH eintraege eintragszahl) in Zeile 653 und 657, also an der Liste, und sie
  steht vor der Musterschleife, nicht in ihr. Belegt an e4_zweiworte und r3_shellform:
  Beide Eintraege zerfallen beim Abgleich in zwei Woerter, gezaehlt wird trotzdem eins.
* **Zaehlt er ausserhalb des Makros?** Ja -- der Kommentar behauptet es, die Messung mit
  dem geleerten Makro belegt es: Der Zaehler ueberlebt und meldet 0. Im Makro waere er
  mit verschwunden.
* **Faellt ein Ziel aus der Zaehlung?** Nein. Die Liste wird je Ziel vor der
  Fallunterscheidung geleert, die Laenge nach dem Einsammeln der Schnittstelle genommen;
  alle fuenf Eigenschaften laufen ein, auch bei einem INTERFACE_LIBRARY. Belegt an
  b2_iface (18) und c2_leereiface (17).

* **Determinismus.** Kein Gleitkomma, keine Iteration ueber eine ungeordnete Menge, kein
  Zeit- oder Adresswert: Die Zahl ist eine Summe von Listenlaengen und darum von der
  Reihenfolge unabhaengig. Nachgemessen statt geschlossen -- drei unabhaengige
  Konfigurationen des Arbeitsbereichs im Profil ON melden dreimal 388 Schaltereintraege,
  Zeichen fuer Zeichen dieselbe Zeile.
* **Raender.** CMake rechnet in math(EXPR) 64-bittig; die groesste hier auftretende Zahl
  ist 388. Der Nullfall ist erreicht (r1_ohnesatz) und in der Meldung ausdruecklich
  gegen ein Fehllesen abgesichert. Keine Division, keine Rundung, kein Aufsummieren
  ueber Runden.

* **Wird ein fremder Leser gestoert?** Nein. bauwege.py liest die Zielzahl ueber das
  Muster "(Ziffern) uebersetzende Ziele"; die neue Zahl steht hinter einem eigenen
  Satzanfang und erzeugt kein zweites Vorkommen -- waere es anders, waere die Lesung
  mehrdeutig geworden, und sechs Bauwege zeigen, dass sie es nicht ist. nachbau.py
  filtert auf "gefunden in", "es fehlen:" und "kein einziges uebersetzendes"; keiner der
  drei neuen Absaetze trifft eines dieser Muster. Ein grep ueber agents/, einrichtung/
  und werkzeuge/ findet keinen weiteren Leser der Riegelmeldung.
* **Die verbotenen Stellen.** Sperrliste, die Bedingungen aus 0103 und 0108, die Menge
  der gesammelten Eigenschaften und der Wortlaut der Zeilen "gefunden in" und
  "es fehlen" sind im Diff unberuehrt; der letzte Punkt zusaetzlich am konfig.log
  zeichenweise belegt.

**Die Grenze der Zahl, gefunden und ausdruecklich kein Befund:** Im echten Baum traegt
keine Quelldatei und keine Schnittstelle eigene Schalter -- alle 388 Eintraege stammen
aus COMPILE_OPTIONS der Ziele. Wer allein die beiden Quelldatei-Aufrufe (Zeile 634 und
637) oder die Schnittstellenzeile (646) stumpf machte, aendert die Zahl **nicht**, und
genau dort lagen die Luecken von 0076 und 0108.

Das ist keine Abweichung von der Abnahme: Sie verlangt die Eintraege, die
fabrik_riegel_sammeln einsammelt, und die zaehlt der Zaehler vollstaendig. Ein eigenes
Paket schlage ich dafuer **nicht** vor, weil der Schaden nicht belegt ist --
schlussriegel_nachbau haengt seit 0133 als ctest-Probe im Arbeitsbereich und faehrt
b1_quellflags, b1b_quellopt, f1_targetdir und x_unterbaum, also genau diese Arme, bei
jeder Abnahme mit; in diesem Lauf ist sie gruen. Die Stelle gehoert trotzdem benannt,
damit der naechste Leser die Zahl nicht fuer mehr haelt, als sie ist.

## Nachweisdateien

Alle unter /tmp/claude-1000/ und nicht eingecheckt (Rang 1 des Nachweisorts):

    kp0132/kette-vorher.cmake    e23e1972f8060080b1da7525a190cfc6   Stand 5d5e2d6^
    kp0132/kette-nachher.cmake   633f394ac4c9a260e4aba95d9018a018   Arbeitsbaum
    kp0132/kette-stumpf.cmake    f137ecea44d1d2eb03a5885b1af66bea   Makrorumpf leer
    kp0132/nachbau-vorher.txt, kp0132/nachbau-nachher.txt
    kp0132/krit1-scharf-p_positiv.txt, krit1-stumpf2.txt, krit1-stumpf-r2.txt
    kp0132/bauwege-kp0132.txt, kp0132/wdh-an-1.txt, kp0132/wdh-an-2.txt
    bauwege0076-kp0132/ (sechs konfig-, bau- und ctest-Protokolle)
    nachbau0066-HEAD/ und nachbau0066-5d5e2d6v/ (je 22 konfig.log)

## Urteil

geprueft. Beide Abnahmebedingungen sind erfuellt, jede mit einem eigenen mechanischen
Aufruf, und die Zahl haelt einer unabhaengigen Handrechnung an 27 Messpunkten stand.
Null Befunde, null Vorschlaege.
