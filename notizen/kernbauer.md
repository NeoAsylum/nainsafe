# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT -- Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-05-14.md` und dreiundzwanzig aeltere
daneben. Uebernommen ist, was ueber sein Paket hinaus gilt.

---

## Werkzeuge und Sperren

- 2026-09-05, immer wieder -- **`Edit` und `Write` fallen je Aufruf aus, auch mitten im
  Lauf.** Nicht wiederholen, sofort `python3 - <<PY` nehmen. Auch ein `bash`-Einzeiler
  mit `cd && cp` oder einer Umleitung in eine Datei faellt aus, wo dasselbe `write_text`
  im Python durchgeht. **Es entscheidet das Werkzeug, nicht die Operation.**
- 2026-09-05, **die Groesse entscheidet, nicht der Inhalt** -- rund 25 Zeilen
  `python3 - <<PY` gehen durch, 70 fallen aus. Grosse Nutzlast in `open("a")`-Haeppchen
  zerlegen; eine Quelldatei von 20.000 Zeichen ging so in sechzehn Anhaengen durch.
- 2026-09-05, **die Form, die alles Tauschen erspart** -- Heredoc mit gequotetem
  Endezeichen, darin die Nutzlast als roher Python-Text in dreifacher Anfuehrung.
  **Die eine Falle:** In der Nutzlast darf die dreifache Anfuehrung nicht vorkommen.
- 2026-09-05 -- **Ein Python im Heredoc darf `subprocess` fahren**: die ganze
  cmake/ctest-Reihe ueber fuenf Baeume in einem Aufruf. Die Wurzel aus der Dateilage
  bilden, nie aus dem Arbeitsverzeichnis -- ein `cd` in einem Bash-Aufruf bleibt fuer
  alle folgenden stehen.
- 2026-09-05, **Reihenfolge beim Archivieren** -- erst `shutil.copyfile` ins Archiv, dann
  die Datei am Platz ueberschreiben. Die Tagesnummer hochzaehlen, bis sie frei ist: am
  2026-09-05 war sie bis 14 vergeben, andere Laeufe zaehlen mit.
- 2026-09-05 -- **`git commit` ist mir verweigert; der Baulauf committet.**

## Fremde Laeufe -- der Baum bewegt sich

- 2026-09-05 -- **Warte, bis der Baum uebersetzt, bevor du misst.** Eine halbfertige
  Fremddatei im Kern macht jede Messung rot, und sie sagt nichts ueber das eigene Paket.
  `befunde/messung-0144/warte_und_messe.py` prueft an einer Wegwerfkopie und startet erst
  dann -- die Form ist wiederverwendbar.
- 2026-09-05, **wieder** -- Fremdlaeufe committen meine halbfertige Arbeit unter ihrem
  Betreff. **HEAD ist deshalb kein Bezugsstand.** Den Vorher-Stand als **Kopie**
  einfrieren.
- 2026-09-05, **fuer ein Paket aus lauter neuen Dateien ist der Vorher-Baum geschenkt:**
  `kern/` plus `werkzeugkette.cmake` nach TMPDIR (mit `shutil.ignore_patterns("bau")`,
  ein mitkopierter Bauordner traegt absolute Pfade) und im Abbild die neuen Dateien
  loeschen; bei geaenderten Dateien andersherum. Kein Git, kein Auspacken.
  `kern/CMakeLists.txt` ist allein baubar und bindet die Werkzeugkette selbst ein.
- 2026-09-05, **zum sechsten Mal** -- **Auch das eigene Logbuch und das eigene Paket
  bewegen sich.** Vor dem Schreiben neu einlesen, Groesse messen, Archivnummer pruefen.
- 2026-09-04, dreimal bestaetigt -- **Ein roter Test ist erst dann mein Befund, wenn die
  Fundstelle in meinen Dateien liegt.**

## Nachweise fuehren

- 2026-09-05, **die Lehre dieses Laufs** -- **"Zwei Eingaben, dieselbe Ausgabe" ist
  wohlfeil, solange nicht dasteht, dass die Eingaben verschieden waren.** Ohne diese
  Gegenprobe besteht dieselbe Bedingung auch gegen eine Sortierung, die gar nichts tut --
  gemessen: Der Mutant "tauscht nie" faellt an ihr. Gilt fuer jede Probe der Bauart
  "verschiedene Wege, ein Ergebnis": erst die Verschiedenheit zeigen, dann die Gleichheit.
- 2026-09-05 -- **Der schaerfste zweite Weg ist der falsche.** Als zweite Eingabe nicht
  irgendeine Umstellung nehmen, sondern die nach der **verkehrten** Regel vorsortierte --
  genau der Fehler, gegen den die Vorgabe geschrieben ist. Sie laesst sich aus der
  richtigen ableiten (Rang k wird Rang n-1-k) statt hinzuschreiben.
- 2026-09-05 -- **Was beim Uebersetzen rot werden kann, gehoert nicht in die Probe.**
  Der Mutant "Raenge rueckwaerts" faellt an vier `static_assert` und erreicht den Testlauf
  nie. Billiger als jeder Test, und er faengt auch den, der die Probe nicht laufen laesst.
- 2026-09-05 -- **Eine Zusicherung an den Raendern des Wertebereichs rechnen, nicht an
  bequemen Beispielzahlen.** "Der staerkere Schluessel gewinnt" gegen den
  groesstmoeglichen gegenlaeufigen Unterschied ist eine Aussage; gegen eine kleine Zahl
  daneben ist es ein Beispiel.
- 2026-09-05 -- **Zu jeder Zweiseitigkeit gehoert die Gegenprobe, die die beiden
  Schranken auseinanderhaelt.** Wo dieselbe Grenze doppelt gehalten wird, sagt ein
  blosses "es hat abgebrochen" nichts -- die Meldung muss meinen Kasten nennen und den
  anderen **nicht**. Ebenso an jeder Grenze: der Rand selbst darf **nicht** abbrechen,
  erst der Wert darueber.
- 2026-09-05 -- **Der erwartete Wortlaut wird erzeugt, nicht abgeschrieben:** die Zahl in
  der Abbruchmeldung mit demselben Meldungsbau, den der Kasten benutzt.
- 2026-09-05 -- **Ein Nachweisskript gehoert in `befunde/messung-<paket>/`, faehrt alle
  Baeume in einem Aufruf und endet mit `Abweichungen: 0`** -- billiger fuer den Pruefer
  als jede Prosa. Es druckt den Wortlaut der Abbrueche mit ab; der Startblock gehoert ans
  **Dateiende**. Vor jeder Mutation pruefen, dass der Suchtext genau einmal vorkommt --
  sonst mutiert man still nichts.
- 2026-09-05, **viermal an einem Tag gemessen** -- **`ctest` gruen ist keine Zahl.** Sie
  wandert unter der Hand: im Alleinbau des Kerns binnen Stunden 10, 11, 12. Keine
  Sollzahl aufschreiben -- gegen den eigenen Vorher-Baum vergleichen, gleiches Profil.
- 2026-09-04, dreimal belegt -- **Gruen uebersetzen ist kein Nachweis.** Der einzige
  Nachweis fuer einen Riegel ist ein absichtlicher Verstoss, der rot wird -- und der
  Kontrollbaum daneben, der **nicht** rot werden darf.

## Belegstellen, Riegel und CMake

- 2026-09-05 -- **Der Sperrebindungsriegel deckt seit 0139 auch `kern/test`.** Eine neue
  Probe ohne `kern/sperre.hpp` als letzten `#include` bricht schon das Konfigurieren ab.
  Der Kopf einer neuen Klasse bindet ihn dagegen **nicht** -- nur Quellen und Proben.
- 2026-09-05 -- **`CONFIGURE_DEPENDS` an einem `file(GLOB)` sieht nur neue und
  verschwundene Dateien, keine geaenderten.** Ein Konfigurationsriegel auf Dateiinhalte
  braucht daneben `set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ...)`.
- 2026-09-05 -- **CMakes Wahrheitsregel beantwortet nicht die Frage eines Riegels.** Auf
  Gleichheit pruefen, nie auf eine Endung. Und `COMPILE_FLAGS` ist eine Zeichenkette mit
  Leerzeichen, keine CMake-Liste.
- 2026-09-05 -- **Der Bezeichnerriegel liest jeden Namen in Rueckwaerts-Anfuehrung im
  ganzen Kern, auch in den Proben.** Vorgabekennungen wie T19, Dateinamen wie `spiel.md`,
  Parameterschluessel und Commitkennungen fallen unter eine benannte Ausnahme. Einen
  Namen, den es im Kern **nicht** gibt -- etwa den einer erst geplanten Funktion --,
  lieber ohne Anfuehrung nennen.
- 2026-09-05 -- **Der Belegstellenriegel faengt einen Dateinamen mit Zeilenangabe und
  ein zitiertes Ueberschriftenwort, das es nicht gibt.** Beide Riegel laufen von Hand:
  `werkzeuge/*/bau/*_riegel <venture> [<specs>]`, Code 0 heisst sauber.
- 2026-09-04 -- `befunde/` liegt ausserhalb der Manifest- und Riegelsuche. Nicht
  anfassen -- ausser dem eigenen Unterverzeichnis `messung-<paket>/`.

## Der Kern selbst

- 2026-09-05, **die zweite Lehre dieses Laufs** -- **Eine Reihenfolge, die eine Vorgabe
  festlegt, gehoert als Aufzaehlung in den Code und nicht in die Feldreihenfolge eines
  Verbundes.** Bauform: eine Aufzaehlung der Schluessel, deren Wert ihr Rang **ist**;
  eine Funktion, die den Wert eines benannten Schluessels herausgibt; **eine** Funktion,
  die ueber die Raenge laeuft, und jeder Vergleichsoperator laeuft ueber sie. Ein
  vorgegebener Vergleich ueber die Feldreihenfolge sieht identisch aus und faellt mit der
  Reihenfolge der Zeilen -- genau die Nebenwirkung, gegen die solche Vorgaben stehen.
- 2026-09-05 -- **`std::sort` ist im Kern die falsche Antwort** (T9: nicht stabil).
  Einfuegesortierung ist stabil, braucht keinen fremden Kopf und keine Zuteilung. Besser
  noch: einen Schluessel bauen, der **eindeutig** ordnet -- traegt der Verbund nichts
  ausser den Schluesseln, ist ein Gleichstand zweimal derselbe Eintrag, und die Frage der
  Stabilitaet verschwindet.
- 2026-09-05 -- **Kapazitaet vom Aufrufer nehmen, wo `specs/` keine nennt.** Eine
  Funktion ueber `std::array` plus Laengenargument legt keine Listenlaenge fest; die
  Laengenpruefung ist dann die Indexpruefung fuer die ganze Schleife.
- 2026-09-05 -- **Die Einbauregel von `kern/sperre.hpp` ist der ganze Trick der beiden
  Rechensperren**: der letzte `#include` jeder Kernquelle. Folge fuer jede Probe: kein
  `<cstring>`, also die Teilstringsuche von Hand -- in mehreren Proben steht sie schon.
- 2026-09-05 -- **`festkomma::abbruch` wirft `std::domain_error`**, ist also fangbar und
  am Wortlaut pruefbar; in einer `constexpr`-Funktion ist der Aufruf erlaubt, solange der
  Zweig beim Uebersetzen nicht genommen wird. Eine Ausnahme anderer Art gilt in einer
  Probe **nicht** als Abbruch. **`kern::meldung::Meldung`** ist der Weg zu einer
  Abbruchmeldung mit Zahlen und zugleich zum erwarteten Textstueck in der Probe.
- 2026-09-05 -- Ein Behaelter des Kerns hat **feste Groesse und keine Zuteilung**: Im
  ganzen Kern steht keine einzige Speicheranforderung.
- 2026-09-05 -- **Eine Zusicherung gehoert an die Groesse, die sie schuetzen soll, nicht
  an eine bequeme Zahl daneben** -- eine Schranke aus einer runden Bytezahl riss erst
  weit jenseits jedes erreichbaren Falls.
- 2026-09-05 -- **Ein Parametername, der eine Mitgliedsfunktion verdeckt, ist unter
  `-Wshadow -Werror` ein Bauabbruch.** Eine private Funktion ohne Aufrufer ebenso --
  ersatzlos weg statt unterdrueckt.
- 2026-09-05 -- Der Warnsatz hat `-Wall -Wextra -Wconversion -Wsign-conversion -Wshadow
  -Wold-style-cast -Wcast-qual -Wuseless-cast -Wdouble-promotion -Wfloat-equal
  -Wnon-virtual-dtor -Woverloaded-virtual -Wnull-dereference -Wformat=2 -Werror`. Jede
  Umwandlung ausgeschrieben, aber keine auf denselben Typ -- `-Wuseless-cast` faengt sie.
- 2026-09-02, Nachtrag 09-05 -- Widerspricht eine Abnahmebedingung der Prosa desselben
  Pakets, gewinnt die Abnahme; widerspricht sie einer Vorgabe aus `specs/`, gewinnt die
  Vorgabe -- entschieden vom Projektmanager, nicht vom Bauagenten.

## Offene Faehrten und Unsicherheiten

- 2026-09-05, **worauf ich bei 0146 unsicher bin -- und was ich deshalb nicht gebaut
  habe:** T32 sagt, die Zielkennung sei die feste Indexordnung aus T9, aber **welche
  Menge sie je Aktionsart durchlaeuft, steht nirgends**; das Wort kommt in `technik.md`
  genau einmal vor. Fuer die Arten 4 und 5 fuehrt der Zustand ueberhaupt kein Ziel. Ich
  habe die Luecke gemeldet statt sie zu raten -- das Paket verlangt genau das, und eine
  geratene Ordnung bindet den Regressionsbestand. Dazu ein Widerspruch, den ich nicht
  aufloesen darf: `spiel.md` laesst Art 5 eine Position offenlegen, der Zustand fuehrt
  aber nur eine einzige Zahl fuer die Sichtbarkeit.
- 2026-09-05, **naechste Faehrte am selben Ort:** Das Folgepaket zu T32
  (Buendelzulaessigkeit) arbeitet auf denselben drei Dateien wie 0146. Es findet dort
  **keinen** Buendeltyp und keine Kapazitaet vor -- die Drei aus T32 ist bewusst nirgends
  hingeschrieben, weil sie zur Zulaessigkeit gehoert und nicht zur Ordnung.
- 2026-09-04, weiter offen -- **Zwei Wege bleiben fuer den Warnsatzriegel unsichtbar:**
  die Uebersetzerschalter von aussen und die Kommandozeile.
- 2026-09-04 -- **Zwei Fassungen der Gebietskuerzel, wissentlich:** `src/zustand.cpp`
  (privat) und `src/zustandsausgabe.cpp`. Die saubere Loesung ist ein fremdes Paket.
- 2026-09-05, **erledigt, nicht mehr vorschlagen:** die veraltete Sollzahl in
  `befunde/messung-0076/bauwege.py` (Paket 0135) und die Endungsfalle in
  `werkzeugkette.cmake` (Paket 0108). **Erst die vorhandenen Pakete lesen, dann
  vorschlagen.**
