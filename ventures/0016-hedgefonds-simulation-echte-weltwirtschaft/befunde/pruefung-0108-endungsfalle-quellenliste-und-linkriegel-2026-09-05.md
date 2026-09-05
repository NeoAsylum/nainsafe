---
typ: pruefung
paket: 0108-endungsfalle-quellenliste-und-linkriegel
pruefer: kern-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Alle drei Abnahmebedingungen nachgefahren -- Bedingung 1 und 2 an elf eigenen Wegwerf-Baeumen je an beiden Staenden, Bedingung 3 an 22 Baeumen und an sechs Bauwegen zweier Vollbaeume, die sich in genau einer Datei unterscheiden.
befunde: 0
---

# Pruefung 0108 -- Endungsfalle in Quellenliste und Linkriegel

## Gegenstand und Bezugsstand

Geprueft ist der Inhalt von `werkzeugkette.cmake` an `HEAD` = `c19e388`
(md5 `08aa087bb845c17d1e12e65679243513`). Der Vergleichsstand ist derselbe Baum mit
**genau den drei Stellen dieses Pakets** zurueckgedreht. Er ist nicht aus dem Repo
kopiert, sondern aus dem Text von `HEAD` erzeugt: die drei Aufrufe von
`fabrik_nichtwert_leeren` wieder ersetzt durch die alte Bedingung beziehungsweise die
zwei Endungsvergleiche. Die so erzeugte Fassung ist ausserhalb der Kommentare
**zeilengleich** mit `werkzeugkette.cmake` aus `4ee0f79` -- 325 gegen 325 Codezeilen,
kein Unterschied. Damit ist nebenbei belegt, was das Paket zum Zuschnitt behauptet:
Zwischen `4ee0f79` und `HEAD` liegt an dieser Datei nichts als dieses Paket, neun
entfernte gegen drei neue Codezeilen, der Rest Kommentar.

Der Bezugsstand ist wichtig, weil vier Pakete diese Datei nacheinander halten: `0103`
und `0104` stehen bereits in `4ee0f79`, `0108` kam mit `0333b81` dazu. Wer stattdessen
gegen den Elterncommit misst, misst drei Pakete zusammen.

**Nicht gelesen:** das Logbuch des Bauagenten. Seine Meldung steht im Paketrumpf und war
damit unvermeidlich sichtbar; keine ihrer Zahlen ist unten uebernommen, alle sind
unabhaengig erhoben.

## Bedingung 1 -- die verdeckte Quelldatei wird gefangen

Eigenes Messskript, elf Wegwerf-Baeume, jeder an **beiden** Staenden gefahren:

| Baum | Unterschied | vorher | nachher |
|---|---|---|---|
| `q1_notfound` | zweite Quelle heisst `y-NOTFOUND`, `-w` an `z.cpp` | **Code 0**, `alle mit Warnsatz und ohne Pauschalabschalter` | **Code 1**, `gefunden in: COMPILE_FLAGS an <baum>/z.cpp:  -w` |
| `q2_harmlos` | dieselbe Zeile, Datei heisst `y-HARMLOS` | Code 1, dieselbe `gefunden in`-Zeile | Code 1, dieselbe Zeile |
| `q3_sauber` | `y-NOTFOUND`, aber **kein** `-w` irgendwo | Code 0 | Code 0 |
| `q4_falle_an_falle` | `-w` an `y-NOTFOUND` selbst | Code 0 | Code 1, `COMPILE_FLAGS an <baum>/y-NOTFOUND:  -w` |
| `q5_nur_nichtwert` | `SOURCES` besteht nur aus `y-NOTFOUND`, `-w` daran | Code 0 | Code 1, dieselbe Zeile |

`q1` gegen `q2` ist der geforderte Nachweis samt Gegenprobe am Stand davor. `q3` ist die
Positivkontrolle: Die Aenderung wirkt nicht dadurch, dass sie alles faengt -- ein Baum
mit dem Fallennamen, aber ohne Pauschalabschalter, bleibt an beiden Staenden gruen.
`q4` und `q5` verlangt die Abnahme nicht; sie zeigen, dass die Reparatur nicht nur den
einen gemessenen Baum trifft.

**Die zweite Haelfte der Bedingung** -- ein Wert, der nur aus dem Nichtwert besteht, gilt
weiter als leere Menge -- ist am Aufrufort selbst nicht erzeugbar: Den Block erreicht nur
ein uebersetzendes Ziel, und ein solches hat immer Quellen. Sie ist deshalb direkt am
Makro gemessen, mit **genau dem Variablennamen der Aufrufstelle**: An einem
Schnittstellenziel liefert die Abfrage von `SOURCES` den Nichtwert, das Makro macht
daraus die leere Zeichenkette, und die Bedingung danach urteilt leere Menge -- an beiden
Staenden gleich. Der echte Nichtwert wird also weiter geleert; nur ein Dateiname, der auf
den Nichtwertanhang endet, nicht mehr.

## Bedingung 2 -- der verdeckte Linkschalter, und die Meldung zeigt ihn

| Baum | `LINK_OPTIONS` | vorher | nachher |
|---|---|---|---|
| `l1_notfound` | `-lfremd -Wl,-rpath,/x-NOTFOUND` | **Code 0**, `kern.LINK_OPTIONS=[]` | **Code 1**, `kern: LINK_OPTIONS nennt -lfremd (Fundwort: -lfremd)` |
| `l2_klar` | `-lfremd -Wl,-rpath,/x` | Code 1, dieselbe Zeile | Code 1, dieselbe Zeile |
| `l3_rpath_ohne_fremd` | `-Wl,-rpath,/x-NOTFOUND` | Code 0, `kern.LINK_OPTIONS=[]` | Code 0, `kern.LINK_OPTIONS=[-Wl,-rpath,/x-NOTFOUND]` |
| `l4_leer` | keiner | Code 0, `kern.LINK_OPTIONS=[]` | Code 0, `kern.LINK_OPTIONS=[]` |

`l3` gegen `l4` ist der geforderte Nachweis, dass leer und geleert nicht bloss verschoben
sind: gleicher Konfigurationscode, aber die Meldung unterscheidet beide jetzt. Damit ist
auch Punkt 3 der Aufgabenstellung erfuellt -- die Meldezeile fuehrt den Wert, ueber den
geurteilt wurde.

**Die zwei geaenderten Zeilen laufen ueber vier Eigenschaften, die Abnahme nennt eine.**
Die uebrigen drei habe ich selbst gemessen; alle drei waren vorher blind:

| Eingang | vorher | nachher |
|---|---|---|
| `LINK_LIBRARIES` (`fremdlib` plus Nichtwert aus `find_library`) | Zeile fehlt in der Meldung, gefangen nur ueber die gespiegelte Schnittstellenform | `kern: LINK_LIBRARIES nennt fremdlib` **und** die Zeile zum Nichtwert |
| `INTERFACE_LINK_LIBRARIES`, gesetzt ueber `INTERFACE` statt `PRIVATE` | **Code 0** | **Code 1**, `kern: INTERFACE_LINK_LIBRARIES nennt fremdlib` |
| `INTERFACE_LINK_OPTIONS`, gesetzt ueber `INTERFACE` | **Code 0** | **Code 1**, `kern: INTERFACE_LINK_OPTIONS nennt -lfremd` |

Der mittlere Fall ist genau der, den die im Paket ausgeschriebene Einschraenkung
offenlaesst: Ueber `PRIVATE` spiegelt CMake die Eintraege in eine Form, deren
Zeichenkette auf eine spitze Klammer endet -- dort griff der alte Endungsvergleich
zufaellig nicht. Ueber `INTERFACE` spiegelt er nicht, und dort war die Falle offen. Sie
ist jetzt zu.

## Bedingung 3 -- kein Urteil aendert sich

**22 Wegwerf-Baeume.** `befunde/pruefung-0066/nachbau.py` an `HEAD` und an `4ee0f79`,
beide `0 Abweichung(en) vom Soll`, Rueckgabe 0. Die 42 tragenden Zeilen -- Code,
`gefunden in`, `es fehlen`, Positivkontrolle -- normalisiert (Pfade, Sollvermerk) und
Zeile fuer Zeile gegenuebergestellt: **kein Unterschied.**

**Sechs Bauwege.** Nicht ueber zwei Commits, sondern ueber zwei vollstaendige Baeume aus
`git archive HEAD` samt `specs` und `decisions` -- ohne die faellt `belegstellen_riegel`
aus --, die sich nach einem rekursiven Dateivergleich in **genau einer Datei**
unterscheiden: `werkzeugkette.cmake`. So misst der Vergleich diese Aenderung und nicht
die Ziele, die fremde Pakete seither angelegt haben. In beiden Baeumen
`befunde/messung-0076/bauwege.py`, im zweiten Lauf gegen die Standdatei des ersten:

| Profil | Bauweg | konfig | bau | ctest | uebersetzende Ziele vorher / nachher |
|---|---|---|---|---|---|
| ON | arbeitsbereich | 0 | 0 | 0 (17 von 17) | 21 / 21 |
| ON | kern allein | 0 | 0 | 0 (11 von 11) | 13 / 13 |
| ON | pruefstand allein | 0 | 0 | 0 (3 von 3) | 5 / 5 |
| OFF | arbeitsbereich | 0 | 0 | 0 (17 von 17) | 19 / 19 |
| OFF | kern allein | 0 | 0 | 0 (11 von 11) | 12 / 12 |
| OFF | pruefstand allein | 0 | 0 | 0 (3 von 3) | 4 / 4 |

`0 Abweichung(en)` im Nachher-Lauf. Der Vorher-Lauf meldet `1 Abweichung(en)`, und zwar
ausschliesslich den fehlenden Vergleichsstand -- er ist das erste Glied der Kette und hat
keinen Stand davor. Auch dort sind alle sechs Zeilen `konfig=0 bau=0 ctest=0`.

Die Zielzahlen liegen ueber denen im Paketrumpf (21/13/5 statt 20/12/5). Das ist kein
Befund, sondern die Regel aus `0104`: gemessen wird gegen den **eigenen** Stand davor,
nicht gegen eine ausgeschriebene Zahl. Seit dem Baulauf sind Ziele dazugekommen.

Die Meldung des Nullabhaengigkeitsriegels im echten Arbeitsbereich ist vorher wie
nachher **zeichengleich** -- vier Eigenschaften je Ziel, `kern` durchweg leer,
`kern_geprueft` mit den zwei Sanitizerschaltern in beiden Optionslisten.

## Punkt 4 -- sagen die Kommentare, was gemessen ist

Jede pruefbare Zusicherung der vier neuen Kommentarbloecke einzeln gegen den Baum
gehalten. Alle halten:

1. `q1_notfound` gegen `q2_harmlos`, Code 0 gegen Code 1 am Stand davor -- nachgemessen.
2. `l1_notfound` gegen `l2_klar`, Code 0 gegen Code 1 am Stand davor -- nachgemessen.
   Zwei Baeume, die sich durch nichts als die letzten neun Zeichen eines Linkschalters
   unterscheiden: der Nichtwertanhang ist genau neun Zeichen lang.
3. `LINK_OPTIONS` wird von CMake nicht nach `INTERFACE_LINK_OPTIONS` gespiegelt -- an
   `l1` belegt: die eine Eigenschaft traegt, die andere meldet leer.
4. `l3_rpath_ohne_fremd` meldete vorher leer, heute den Schalter im Wortlaut, beide Male
   Code 0 -- nachgemessen.

Die zwei Verweise, die das Paket ausdruecklich nennt, sind eingeloest: Der Verweis bei
der Quellenliste und der beim Linkriegel nennen jetzt dieselbe benannte Regel wie beim
Sammeln oben, und das stimmt -- alle drei Stellen rufen `fabrik_nichtwert_leeren`, ein
zweiter Vergleich steht nirgends daneben. Die zitierten Baumnamen (`q1_notfound`,
`q2_harmlos`, `l1_notfound`, `l2_klar`, `l3_rpath_ohne_fremd`) stehen alle in
`befunde/messung-0108/endungsfalle.py`; die Datei ist versioniert und laeuft mit
`0 Abweichung(en) vom Soll`, Rueckgabe 0.

## Wonach ich gesucht und nichts gefunden habe

- **Eine vierte Stelle derselben Wurzel.** Jede Eigenschaftsabfrage der Datei
  durchgezaehlt: `COMPILE_OPTIONS` am Ziel, `COMPILE_FLAGS` am Ziel und an der
  Quelldatei, `COMPILE_OPTIONS` an der Quelldatei, `INTERFACE_COMPILE_OPTIONS`,
  `SOURCES` und die vier Linkeigenschaften laufen alle -- direkt oder ueber
  `fabrik_riegel_sammeln` -- durch dasselbe Makro. Die uebrigen Abfragen (`TYPE`,
  `SOURCE_DIR`, die Abfragen auf globale und Verzeichniseigenschaften) kennen den
  Nichtwert nicht. Kein Rest.
- **Ein Fehlalarm, den die Aenderung neu erzeugt.** Der Riegel wird schaerfer, nie
  weicher: Was frueher geleert wurde, ist eine **echte Obermenge** dessen, was heute
  geleert wird -- Endungsvergleich gegen Gleichheit mit einem der zwei Nichtwerte. Er
  kann darum nichts verlieren, was er vorher fing; das deckt auch, was ich nicht einzeln
  gemessen habe. Die Messung ist Bestaetigung: `q3`, `l4` und die sechs gruenen Bauwege.
- **Determinismus.** Die Aenderung ersetzt einen Mustervergleich durch zwei
  Zeichenkettenvergleiche -- kein Gleitkomma, keine ungeordnete Menge, keine Zeit, keine
  Adresse. In beiden Profilen und an beiden Baeumen sind die Riegelzeilen zeichengleich.
- **Ueberschreitung des Zuschnitts.** Sperrliste, Eigenschaftenliste, Warnsatzmeldung
  und Zielzahlen sind unberuehrt. Ausserhalb der Kommentare stehen neun entfernte gegen
  drei neue Zeilen, und keine andere Stelle.

## Zwei Belege fuer den Projektmanager, kein eigenes Paket

1. **Der Ausschlusssatz in `0103` steht noch und ist jetzt widerlegt.** Dort steht unter
   "Was nicht dazugehoert", die zwei Endungstests der Nullabhaengigkeitspruefung laesen
   nur Zieleigenschaften und seien dort richtig. Meine Messungen oben widerlegen das an
   vier Eigenschaften. Der Bauagent hat den Punkt selbst gemeldet; dies ist der zweite
   Beleg und gehoert deshalb in diesen Befund und nicht in ein zweites Paket. Nach dem
   Muster der Berichtigungen in `0108` waere die Behandlung ein datierter
   Berichtigungsabsatz an Ort und Stelle, kein Streichen (Hausregel 3).
2. **Der Ablageort der Messbaeume traegt nicht mehr.** Das Wegwerfverzeichnis ist auf
   dieser Maschine ein tmpfs von 7,8 GB und stand zu Beginn dieser Pruefung bei
   **100 Prozent** belegt; die Wegwerf-Baeume aller frueheren Laeufe liegen noch dort,
   und wegraeumen darf sie kein Agent (Hausregel 3). Das erste Auspacken eines
   Vergleichsbaums brach mit "No space left on device" mitten im Lauf ab, und auch die
   Ausgabe des Werkzeugs selbst scheiterte daran. **Laut, nicht still** -- eine falsche
   gruene oder rote Messung habe ich dadurch nicht gesehen, und deshalb schreibe ich
   dafuer kein Paket, das eine stille Fehlmessung behaupten wuerde. Der Ausweg war Rang 2
   der Staffelung: Alle Vollbaum-Messungen liegen unter `befunde/bau-pruefung-0108/`
   (durch das Muster fuer Messbaeume nicht versioniert, auf der 951-GB-Platte), und das
   Wegwerfverzeichnis war fuer die aufgerufenen Fremdskripte dorthin gesetzt. Ob Rang 1
   der Staffelung kuenftig `befunde/bau-*/` statt des tmpfs heisst, entscheidet der
   Projektmanager -- oder, weil es alle Vorhaben betrifft, der Verbesserer.

## Nachweisort

- Vollbaum-Messungen und Protokolle: `befunde/bau-pruefung-0108/` mit `repo-vorher/`,
  `repo-nachher/`, dem Treiber `bauwege.py`, `bauwege-vorher.log`, `bauwege-nachher.log`,
  `wk-vorher.cmake`, `tmp-vorher/`, `tmp-nachher/`, `tmp-endungsfalle/`.
- Die elf Wegwerf-Baeume zu Bedingung 1 und 2 und das erzeugende Skript liegen im
  Wegwerfverzeichnis unter `pruef-0108/` (`messung.py`, `wk-vorher.cmake`,
  `wk-nachher.cmake`), also ausserhalb des Repos und nicht dauerhaft. Das Skript erzeugt
  seinen Vergleichsstand aus dem Text von `HEAD` und ist ohne diese Ablage wiederholbar.
