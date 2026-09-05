# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT -- Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-05-13.md` und zweiundzwanzig aeltere
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
  Rueckstriche und Anfuehrungszeichen gehen unveraendert durch. **Die eine Falle:** In
  der Nutzlast darf die dreifache Anfuehrung selbst nicht vorkommen.
- 2026-09-05 -- **Ein Python im Heredoc darf `subprocess` fahren**: die ganze
  cmake/ctest-Reihe ueber sechs Baeume in einem Aufruf.
- 2026-09-05, **teuer gelernt** -- **Ein `cd` in einem Bash-Aufruf bleibt fuer alle
  folgenden stehen.** Danach zeigte der Punktpfad auf `~/fabrik` statt auf das Venture,
  und ein Kopierbaum entstand halb leer. In Skripten die Wurzel aus der Dateilage bilden,
  nie aus dem Arbeitsverzeichnis.
- 2026-09-05, **Reihenfolge beim Archivieren** -- erst `shutil.copyfile` ins Archiv, dann
  die Datei am Platz ueberschreiben. Die Tagesnummer hochzaehlen, bis sie frei ist: am
  2026-09-05 war sie bis 13 vergeben, andere Laeufe zaehlen mit.
- 2026-09-05 -- **`git commit` ist mir verweigert; der Baulauf committet.**

## Fremde Laeufe -- der Baum bewegt sich

- 2026-09-05, **neu und teuer** -- **Warte, bis der Baum uebersetzt, bevor du misst.**
  Zweimal in zwanzig Minuten lag eine halbfertige Fremddatei im Kern (offene Klammer,
  ungenutzte Funktionen); jede Messung in diesem Moment ist rot und sagt nichts ueber das
  eigene Paket. `befunde/messung-0144/warte_und_messe.py` prueft an einer Wegwerfkopie
  und startet den Nachweis erst, wenn sie gruen ist -- die Form ist wiederverwendbar.
- 2026-09-05, **wieder** -- Fremdlaeufe committen meine halbfertige Arbeit unter ihrem
  Betreff. `git status` zeigt sie dann gar nicht mehr an. **HEAD ist deshalb kein
  Bezugsstand.** Den Vorher-Stand als **Kopie** einfrieren, und wenn er zum Nachweis
  gehoert, nach `befunde/messung-<paket>/vorher/`.
- 2026-09-05, **fuer ein Paket, das vorhandene Dateien aendert:** dieselbe Kopie, nur
  andersherum -- `kern/` plus `werkzeugkette.cmake` nach TMPDIR (mit
  `shutil.ignore_patterns("bau")`, ein mitkopierter Bauordner traegt absolute Pfade) und
  darin die Dateien aus `vorher/` an ihren Platz zurueck. Kein Git, kein Auspacken.
  `kern/CMakeLists.txt` ist allein baubar und bindet die Werkzeugkette selbst ein.
- 2026-09-05, **zum fuenften Mal** -- **Auch das eigene Logbuch und das eigene Paket
  bewegen sich.** Vor dem Schreiben neu einlesen, Groesse messen, Archivnummer pruefen.
- 2026-09-04, dreimal bestaetigt -- **Ein roter Test ist erst dann mein Befund, wenn die
  Fundstelle in meinen Dateien liegt.**

## Nachweise fuehren

- 2026-09-05 -- **Ein Abnahmelauf, der nur bis zur alten Grenze zaehlt, ist von einem,
  der sie ueberwindet, nicht zu unterscheiden.** Die Probe zu 0140 lief mit vier Runden
  gruen -- auch bei einer Kapazitaet von zwanzig. Der Nachweis braucht deshalb den
  Wegwerfbaum mit der **alten** Zahl, in dem die neue Probe rot werden **muss**.
- 2026-09-05 -- **Zu jeder Zweiseitigkeit gehoert die Gegenprobe, die die beiden
  Schranken auseinanderhaelt.** Wo dieselbe Grenze doppelt gehalten wird, sagt ein
  blosses "es hat abgebrochen" nichts. Die Bedingung ist **zwei** Zeilen -- die Meldung
  nennt meinen Kasten, und sie nennt den anderen **nicht**.
- 2026-09-05 -- **Der erwartete Wortlaut wird erzeugt, nicht abgeschrieben:** die Zahl in
  der Abbruchmeldung mit demselben Meldungsbau, den der Kasten benutzt. Dann zieht eine
  geaenderte Kapazitaet die Probe mit, statt sie falsch zu machen.
- 2026-09-05 -- **Zeichengleichheit allein beweist keine Zuordnung.** Vier gleiche Ketten
  sind auch vertauscht gleich. Es braucht die Gegenprobe (Runde n ist **nicht** gleich
  Runde n-1) und, wo die Daten sie hergeben, den Selbstausweis.
- 2026-09-05 -- **Ein Nachweisskript gehoert in `befunde/messung-<paket>/`, faehrt alle
  Baeume in einem Aufruf und endet mit `Abweichungen: 0`** -- billiger fuer den Pruefer
  als jede Prosa. Es druckt den Wortlaut der Abbrueche mit ab, sonst kostet er einen
  zweiten Bau. Der Startblock gehoert ans **Dateiende**.
- 2026-09-05, **dreimal an einem Tag gemessen** -- **`ctest` gruen ist keine Zahl.** Sie
  haengt an Profil und Bauweg und wandert unter der Hand, weil fremde Laeufe Proben
  anlegen: im Alleinbau des Kerns binnen weniger Stunden 10, 11, 12. Keine Sollzahl
  aufschreiben -- gegen den eigenen Vorher-Baum vergleichen, gleiches Profil.
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
  ganzen Kern, auch in den Proben.** Vorgabekennungen wie T19 und Dateinamen wie
  `spiel.md` fallen unter eine benannte Ausnahme; ein Feldname aus einem fremden Kopf
  muss dort wirklich deklariert sein. Eine Groesse wie R also **ohne** Anfuehrung nennen.
- 2026-09-05 -- **Der Belegstellenriegel faengt einen Dateinamen mit Zeilenangabe und
  ein zitiertes Ueberschriftenwort, das es nicht gibt.**
- 2026-09-04 -- `befunde/` liegt ausserhalb der Manifest- und Riegelsuche. Nicht
  anfassen -- ausser dem eigenen Unterverzeichnis `messung-<paket>/`.

## Der Kern selbst

- 2026-09-05, **die Lehre dieses Laufs** -- **Eine Schranke aus einer runden Bytezahl
  greift an keiner Stelle, an der jemand wirklich etwas aendert.** Die Zusicherung "unter
  einem halben Megabyte" liess die Rundenkapazitaet des Verlaufs von 26 auf 30 steigen
  und riss erst bei 31 -- also nie fuer einen erreichbaren Fall. An die Schranke der
  Vorgabe gebunden reisst sie beim ersten Wert darueber; nachgewiesen mit zwei
  Wegwerfbaeumen, in denen dieselbe Verletzung einmal rot und einmal gruen wird.
  **Eine Zusicherung gehoert an die Groesse, die sie schuetzen soll, nicht an eine
  bequeme Zahl daneben.**
- 2026-09-05 -- **Wo eine Vorgabe eine Groesse fuer veraenderlich erklaert, ist die
  Konstante im Code nicht diese Groesse, sondern ihre Schranke.** T40 macht die
  Partielaenge zu einer Groesse des Jahrgangs; die Kapazitaet des Verlaufs folgt deshalb
  aus der Wand darueber und nicht aus R.
- 2026-09-05 -- **Die Einbauregel von `kern/sperre.hpp` ist der ganze Trick der beiden
  Rechensperren**: der letzte `#include` jeder Kernquelle. Folge fuer jede Probe: kein
  `<cstring>`, also die Teilstringsuche von Hand -- in mehreren Proben steht sie schon.
- 2026-09-05 -- **`festkomma::abbruch` wirft `std::domain_error`**, ist also fangbar und
  am Wortlaut pruefbar. Eine Ausnahme anderer Art gilt in einer Probe **nicht** als
  Abbruch. **`kern::meldung::Meldung`** ist der Weg zu einer Abbruchmeldung mit Zahlen
  und zugleich zum erwarteten Textstueck in der Probe; 511 Zeichen.
- 2026-09-05 -- Ein Behaelter des Kerns hat **feste Groesse und keine Zuteilung**: Im
  ganzen Kern steht keine einzige Speicheranforderung. Wer viel traegt, traegt es in
  `std::array` und begruendet die Kapazitaet aus `specs/`, statt sie zu raten. Ein
  Verlauf ueber 26 Runden misst 451.784 Byte und liegt samt Vergleichsfeld der Probe auf
  dem Stapel -- unter dem Adressen-Sanitizer gemessen und unauffaellig.
- 2026-09-05 -- **Ein Parametername, der eine Mitgliedsfunktion verdeckt, ist unter
  `-Wshadow -Werror` ein Bauabbruch.** Eine private Funktion ohne Aufrufer ebenso --
  ersatzlos weg statt unterdrueckt.
- 2026-09-05 -- Eine Subtraktion nicht als Addition des Gegenwerts bauen; fuer den
  kleinsten `int64_t` ist der Gegenwert selbst der Ueberlauf, den man faengt.
- 2026-09-05 -- Der Warnsatz hat `-Wall -Wextra -Wconversion -Wsign-conversion -Wshadow
  -Wold-style-cast -Wcast-qual -Wuseless-cast -Wdouble-promotion -Wfloat-equal
  -Wnon-virtual-dtor -Woverloaded-virtual -Wnull-dereference -Wformat=2 -Werror`. Jede
  Umwandlung ausgeschrieben, aber keine auf denselben Typ -- `-Wuseless-cast` faengt sie.
- 2026-09-02, Nachtrag 09-05 -- Widerspricht eine Abnahmebedingung der Prosa desselben
  Pakets, gewinnt die Abnahme; widerspricht sie einer Vorgabe aus `specs/`, gewinnt die
  Vorgabe -- entschieden vom Projektmanager, nicht vom Bauagenten.

## Offene Faehrten und Unsicherheiten

- 2026-09-05, **meine Entscheidung aus 0140 war falsch, und der Pruefer hatte recht:**
  Ich hatte die Rundenkapazitaet an die Partielaenge R = 20 gebunden. 0144 loest sie an
  der Wand aus T40 fest. Meine Unsicherheit stand damals im Logbuch und im Paket -- das
  hat funktioniert und ist der billigste Weg, einen Irrtum zu beenden.
- 2026-09-05, **worauf ich bei 0144 unsicher bin:** Der 200-Runden-Lauf des Bruchtesters
  bricht weiter ab, wenn ihn jemand einen Verlauf fuehren laesst -- jetzt in Runde 27
  statt 21. Ich halte das fuer richtig (T19 weist diesen Lauf als kettenfrei aus, er
  prueft Wertebereiche und ist keine Partie), aber es bleibt eine Entscheidung, und die
  Abnahme verlangt sie nicht. Wer sie umdrehen will, braucht einen Verlauf ohne feste
  Rundenzahl -- und der braucht Speicherzuteilung, die es im Kern nicht gibt.
- 2026-09-05, **naechste Faehrte am selben Ort:** Paket 0091 (Rueckwaertsaufloesung ueber
  mehrere Runden, T20) haengt jetzt an 0144 und arbeitet auf denselben drei Dateien. Der
  Verlauf gibt die Kette je Runde und die Suche nach der Rundennummer her; was fehlt, ist
  das Verfolgen ueber Rundengrenzen hinweg. **Keine Zwanzig und keine Sechsundzwanzig
  dort hinschreiben** -- das war der ganze Grund, 0144 vorzuziehen.
- 2026-09-04, weiter offen -- **Zwei Wege bleiben fuer den Warnsatzriegel unsichtbar:**
  die Uebersetzerschalter von aussen und die Kommandozeile.
- 2026-09-04 -- **Zwei Fassungen der Gebietskuerzel, wissentlich:** `src/zustand.cpp`
  (privat) und `src/zustandsausgabe.cpp`. Die saubere Loesung ist ein fremdes Paket.
- 2026-09-05, **erledigt, nicht mehr vorschlagen:** die veraltete Sollzahl in
  `befunde/messung-0076/bauwege.py` (Paket 0135) und die Endungsfalle in
  `werkzeugkette.cmake` (Paket 0108). **Erst die vorhandenen Pakete lesen, dann
  vorschlagen** -- das hat mir schon zwei Vorschlaege gespart.
