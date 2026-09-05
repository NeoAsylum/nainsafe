---
typ: pruefung
paket: 0104-zielzahlen-je-profil-statt-tripel
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Die drei Bauwege in beiden Profilen konfiguriert -- an drei Staenden, jede Zahl zweimal unabhaengig erhoben (Riegelmeldung und CMake-File-API) -- und jede Behauptung des neuen Kommentars einzeln gegen den Baum gehalten; keine der Zahlen widerspricht ihm, das Verfahren steht am Ort der Zahl.
befunde: 1
---

# Pruefung 0104: der Kommentar haelt, und die Meldung darunter kennt ihr Profil nicht

Gegenstand ist allein **Bedingung 2**. Bedingung 1 ist am 2026-09-05 vom Projektmanager
erledigt; die `abnahme`-Zeile im Frontmatter des Pakets ist entsprechend verengt.

## Wie gemessen wurde

Alle Messungen aus `git archive` in frische Baeume unterhalb von `$TMPDIR`, ausserhalb des
Repos, mit `specs` und `decisions` (ohne sie faellt `belegstellen_riegel` aus und man haelt
die eigene Ablage fuer einen Befund). Je Bauweg und Profil ein eigener, leerer Baubaum --
kein wiederverwendeter CMake-Cache. Schalter wie im Runner:

    cmake -S <weg> -B <bau> -DCMAKE_BUILD_TYPE=RelWithDebInfo \
          "-DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math" -DFABRIK_SANITIZER=<ON|OFF>

Drei Staende, drei Bauwege, zwei Profile, alle 18 Konfigurationen mit **Code 0**:

| Stand | Profil | Arbeitsbereich | `kern` allein | `pruefstand` allein |
|---|---|---|---|---|
| `8a2c381` (Bezugsstand des Kommentars) | ON | 19 | 12 | 5 |
| `8a2c381` | OFF | 17 | 11 | 4 |
| `a8e1ce5` (HEAD am 2026-09-05) | ON | 20 | 12 | 5 |
| `a8e1ce5` | OFF | 18 | 11 | 4 |
| `3bc9e9b` (letzter Commit des 2026-09-04) | ON | 18 | 12 | 5 |
| `3bc9e9b` | OFF | 16 | 11 | 4 |

**Jede dieser Zahlen ist zweimal unabhaengig erhoben.** Einmal aus der Meldung des
Warnsatz-Schlussriegels, einmal aus der **CMake-File-API** (`codemodel-v2`, gezaehlt sind
alle Ziele ausser `INTERFACE_LIBRARY` und `UTILITY`) -- also aus CMakes eigener Zielliste,
die den Riegel nicht kennt. **In allen 18 Faellen stimmen beide ueberein.** Das ist zugleich
die Gegenprobe darauf, dass der Riegel die richtige Menge zaehlt und nicht irgendeine.

## Bedingung 2, Teil 1: Widerspricht der Kommentar einer Messung?

Jede Zusicherung des neuen Kommentars einzeln, in der Reihenfolge, in der sie dasteht:

**a) „Gemessen am 2026-09-05 am Stand `8a2c381` ... ON 19 / 12 / 5, OFF 17 / 11 / 4."**
Zutreffend, alle sechs. Nicht abgeschrieben, sondern in frischen Baeumen nachgestellt und
mit der zweiten Methode bestaetigt.

**b) „`kern_geprueft` und `pruefstand_geprueft` entstehen nur unter `FABRIK_SANITIZER=ON`."**
Zutreffend, und zwar **namentlich**, nicht nur der Zahl nach. Die Zielmengen aus der
File-API, ON gegen OFF, unterscheiden sich an `8a2c381` in genau diesen beiden Namen:

    Arbeitsbereich ON \ OFF = {kern_geprueft, pruefstand_geprueft}   (19 - 17 = 2)
    kern allein    ON \ OFF = {kern_geprueft}                        (12 - 11 = 1)
    pruefstand     ON \ OFF = {pruefstand_geprueft}                  ( 5 -  4 = 1)

Strukturell gedeckt: beide Ziele stehen in `kern/CMakeLists.txt` bzw.
`pruefstand/CMakeLists.txt` innerhalb eines `if(FABRIK_SANITIZER)`, im `else()`-Zweig
entsteht kein Ziel, sondern nur `FABRIK_PROBEN_BIBLIOTHEK` zeigt woanders hin.

**c) „Ein einzelnes Tripel kann hoechstens fuer eines der beiden Profile gelten."**
Folgt aus b): Die Differenz ist 2 / 1 / 1 und damit auf keinem Bauweg null.

**d) „Die Zahl ist eine Summe ueber die Manifeste der Mitglieder; jedes neue Ziel hebt
sie, ohne dass an dieser Datei etwas geschehen waere."** Direkt belegt, nicht nur plausibel:
Zwischen `8a2c381` und `a8e1ce5` sind die **325 Codezeilen** von `werkzeugkette.cmake`
byteweise dieselben, und der Arbeitsbereich steigt trotzdem von 19 auf 20 (ON) und von 17
auf 18 (OFF). Ursache ist `werkzeuge/bezeichner`, das erst danach in `FABRIK_MITGLIEDER`
kam. Der Kommentar beschreibt damit ein Verhalten, das sich zwischen seinem Bezugsstand
und heute **tatsaechlich gezeigt hat**.

**e) „Die Differenz des Arbeitsbereichs zur Summe der beiden Alleinbauten ist an diesem
Stand in beiden Profilen 2: `werkzeuge/belegstellen` und `werkzeuge/mutation`."**
Zutreffend, ebenfalls namentlich. An `8a2c381` ist die Zielmenge des Arbeitsbereichs minus
die der beiden Alleinbauten in beiden Profilen genau `{belegstellen_riegel,
mutationstreiber}`; die uebrigen fuenf Mitglieder aus `FABRIK_MITGLIEDER` sind an diesem
Stand nicht gebaut und melden sich als „uebersprungen". Rechnung: 12 + 5 + 2 = 19 (ON),
11 + 4 + 2 = 17 (OFF).

**f) „Am 2026-09-04 war sie noch 1 -- `werkzeuge/mutation` kam erst danach dazu."**
Zutreffend, eigens nachgemessen: Am letzten Commit des 2026-09-04 (`3bc9e9b`, 23:30) ist
die Differenz in **beiden** Profilen 1 (18 − 12 − 5 und 16 − 11 − 4). Sowohl
`werkzeuge/mutation/CMakeLists.txt` als auch sein Eintrag in `FABRIK_MITGLIEDER` stammen
aus `bf0519b` vom 2026-09-05; `werkzeuge/belegstellen` ist seit `d28523c` vom 2026-09-04
da. Genau ein zusaetzliches Mitglied, genau Differenz 1.

**g) „ein Sturz von 15 auf 3 -- die beiden Zahlen sind erfunden und keine Messung."**
Als Nichtmessung gekennzeichnet. Damit kann keine Messung ihr widersprechen, und das ist
die schaerfere Fassung derselben Regel, nicht ihre Umgehung.

**h) „Genau das ist der Abnahme von Paket 0076 widerfahren."** Zutreffend; dessen
Bedingung 2 traegt die drei Zahlen woertlich, und `werkzeugkette.cmake` allein kann sie
nicht bewegen.

**Ergebnis: kein Widerspruch.** Dass die Zahlen des Arbeitsbereichs an `HEAD` heute um
eins hoeher stehen als im Kommentar, ist keiner -- der Kommentar nennt Stand, Datum,
Profil und Bauweg, und sagt selbst dazu, dass der Wert ein Verfallsdatum hat. Er ist damit
sein eigener Beleg: **derselbe Kommentar waere unter der alten Bauart schon wieder falsch.**

## Bedingung 2, Teil 2: Steht das Verfahren, und steht es am richtigen Ort?

Ja. Der Satz zum Gleichheitsmass steht in `werkzeugkette.cmake` unmittelbar ueber dem
`message(STATUS ...)`, das `${gezaehlt}` ausgibt (Zeilen 894–932 ueber Zeile 933) -- also
am Ort der Zahl selbst, wo die naechste Abnahme ihn liest, und nicht nur im Paket.

Wortlaut gegen den Beschluss im Paketrumpf gehalten, Halbsatz fuer Halbsatz: gleich in
Inhalt und Reichweite. Eine Abweichung ist da und zeigt in die sichere Richtung -- der
Beschluss sagt „auch wenn sie heute stimmt", der Kommentar „auch wenn sie am Tag des
Schreibens stimmt". Ein Kommentar wird spaeter gelesen als er geschrieben wird; „heute"
haette dort seinen Bezug verloren. Kein Befund.

Beide Haelften der Begruendung sind eingebaut und nicht nur benannt: Profilabhaengigkeit
(b) und wachsender Baum (d).

## Was ich sonst geprueft habe -- und nichts gefunden

- **Reiner Kommentar?** Ja. 47 geaenderte Zeilen im Diff `8a2c381..HEAD`, davon **null**
  ausserhalb eines `#`; die 325 Codezeilen sind vorher und nachher byteweise identisch.
  Der Bauagent hatte laut Paket nur diese Datei, und er hat an ihr nur Kommentar bewegt.
- **Ist die alte Zahl wirklich fort?** `16 / 10 / 5` kommt in `werkzeugkette.cmake` nicht
  mehr vor. Im Verzeichnis `aufgaben/` steht sie nur noch in 0076 (abgenommen, wird laut
  Beschluss nicht nachtraeglich umgeschrieben) und in 0104 selbst, dort als Geschichte.
- **Traegt noch eine offene Abnahme eine ausgeschriebene Zielzahl?** Nein. Gesucht wurde
  ueber alle `abnahme`-Zeilen nach „N uebersetzende", „Zahlen N" und dem Tripelmuster
  `N / N / N`. Einziger Treffer ist 0068, und der zaehlt Reihen, nicht Bauziele. Das
  Messwerkzeug `befunde/messung-0076/bauwege.py`, das eine feste Sollzahl trug, ist durch
  Paket 0135 bereits erledigt (`status: gebaut`). Die Entscheidung wirkt sich also aus:
  0132 zitiert sie in seiner eigenen Abnahme bereits als Begruendung dafuer, je Profil
  gegen den eigenen Stand davor zu vergleichen.
- **Ist die Zahl ueberhaupt reproduzierbar?** Ja. Gleicher Stand und gleiches Profil
  ergeben in getrennten Wegwerf-Baeumen dieselbe Zahl, und die Zahl deckt sich mit CMakes
  eigener Zielliste. Sie haengt an nichts Zufaelligem, an keiner Reihenfolge und an keinem
  Pfad -- nur an Stand und Profil, also an genau den beiden Groessen, die der Kommentar
  jetzt verlangt mitzunennen.

## Befund 1 -- an den Projektmanager, nicht an das Paket

**Die Meldung, ueber der die neue Regel steht, nennt ihr Profil nicht.** Der Kommentar
sagt jetzt: eine Zahl ohne ihr Profil ist keine Messung, sondern eine Behauptung -- und
verlangt von jeder kuenftigen Abnahme den Vergleich „je Profil". Die Zeile darunter gibt
die Zahl aus und sagt nirgends, aus welchem Profil sie stammt.

So erzeugt man den Fehler:

1. `cmake -S <baum>/pruefstand -B <bau1> ... -DFABRIK_SANITIZER=ON`
2. `cmake -S <baum>/pruefstand -B <bau2> ... -DFABRIK_SANITIZER=OFF`
3. Die beiden Konfigurationsausgaben nebeneinanderlegen.

Sie sind **zeichengleich bis auf eine Ziffer**: `5 uebersetzende Ziele geprueft` gegen
`4 uebersetzende Ziele geprueft`. Kein Wort nennt `FABRIK_SANITIZER`, keine Zeile nennt
`pruefstand_geprueft`. Wer nur den Bericht hat, kann das Gleichheitsmass auf diesem Bauweg
**nicht anwenden**: Ein Wechsel des Profils und ein verlorengegangenes Ziel sehen darin
identisch aus -- und der Vorgabewert des Schalters steht in derselben Datei, laesst sich
also mit einer Zeile umlegen.

Der Arbeitsbereich und der Alleinbau des Kerns kommen heute mit einem Zufall davon: Dort
zaehlt der Nullabhaengigkeitsriegel `kern_geprueft` in seiner eigenen Meldung mit auf, und
daran ist das Profil abzulesen. Der Alleinbau des Pruefstands hat diese Zeile nicht -- er
ist einer der drei Bauwege, die jede Abnahme dieses Riegels fuehrt. Im echten
Uebersetzungsbericht (`befunde/uebersetzung-2026-09-05.md`) stehen sechs solche Zeilen,
und keine einzige nennt ihr Profil; die Ueberschrift ist auf `cmake -S` gekuerzt, die
Schalter stehen dort also auch nicht.

**Kein Ruecklaufgrund.** Das Paket schliesst „die Meldung des Riegels umbauen" ausdruecklich
aus, und die Aenderung durfte nur Kommentar sein. Der Befund entsteht erst dadurch, dass
dieses Paket die Regel aufstellt, an der die Meldung nun gemessen werden kann -- er ist die
Folge einer richtigen Aenderung, nicht ihr Fehler.

**Vorschlag geschrieben:** `aufgaben/0137-riegelmeldung-nennt-ihr-profil.md`,
`status: vorschlag`, mit `haengt_an: [0132-riegelmeldung-nennt-gesammelte-eintraege]` als
Kollisionsschutz -- 0132 ist heute das letzte offene Paket der Kette auf dieser Datei
(0094 → 0103 → 0104 → 0108 → 0124 → 0132). Sollte die Nummer inzwischen vergeben sein,
gilt der Dateiname, nicht die Ziffer.
