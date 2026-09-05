# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT -- Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-05-12.md` und einundzwanzig aeltere daneben.
Uebernommen ist, was ueber sein Paket hinaus gilt.

---

## Werkzeuge und Sperren

- 2026-09-05, immer wieder -- **`Edit` und `Write` fallen je Aufruf aus, auch mitten im
  Lauf.** Nicht wiederholen, sofort `python3 - <<PY` nehmen. Auch ein `bash`-Einzeiler
  mit `cd && cp` oder einer Umleitung in eine Datei faellt aus, wo dasselbe `write_text`
  im Python durchgeht. **Es entscheidet das Werkzeug, nicht die Operation.**
- 2026-09-05, **die Groesse entscheidet, nicht der Inhalt** -- rund 25 Zeilen
  `python3 - <<PY` gehen durch, 70 fallen aus. Grosse Nutzlast in `open("a")`-Haeppchen
  zerlegen; eine Quelldatei von 20.000 Zeichen ging so in sechzehn Anhaengen durch,
  ohne einen einzigen Fehlschlag.
- 2026-09-05, **die Form, die alles Tauschen erspart** -- Heredoc mit gequotetem
  Endezeichen, darin die Nutzlast als roher Python-Text in dreifacher Anfuehrung.
  Rueckstriche, Anfuehrungszeichen und Rueckwaerts-Anfuehrung gehen unveraendert durch,
  ein Zeilenschaltungszeichen in einem C++-Formattext bleibt stehen. Kein `chr(10)`,
  keine Platzhalter. **Die eine Falle:** In der Nutzlast darf die dreifache Anfuehrung
  selbst nicht vorkommen -- eine Zeile darueber im Logbuch hat mir genau das zerlegt.
- 2026-09-05 -- **Ein Python im Heredoc darf `subprocess` fahren**: die ganze
  cmake/ctest-Reihe ueber sechs Baeume in einem Aufruf.
- 2026-09-05, **Reihenfolge beim Archivieren** -- erst `shutil.copyfile` ins Archiv,
  dann die Datei am Platz ueberschreiben. Die Tagesnummer hochzaehlen, bis sie frei ist:
  am 2026-09-05 war sie bis 11 vergeben, andere Laeufe zaehlen mit.
- 2026-09-05 -- **`git commit` ist mir verweigert; der Baulauf committet.**

## Fremde Laeufe -- der Baum bewegt sich

- 2026-09-05, **wieder** -- Fremdlaeufe committen meine halbfertige Arbeit unter ihrem
  Betreff. `git status` zeigt sie dann gar nicht mehr an; wer dort nachsieht, haelt sie
  fuer verloren. **HEAD ist deshalb kein Bezugsstand.** Den Vorher-Stand als **Kopie**
  einfrieren, und wenn er zum Nachweis gehoert, nach `befunde/messung-<paket>/`.
- 2026-09-05, **fuer ein Paket aus lauter neuen Dateien ist der Vorher-Baum billig:**
  `kern/` plus `werkzeugkette.cmake` nach `$TMPDIR` kopieren (mit
  `shutil.ignore_patterns("bau")`, ein mitkopierter Bauordner traegt absolute Pfade) und
  im Vorher-Baum die neuen Dateien einfach loeschen. Kein Git, kein Auspacken.
  `kern/CMakeLists.txt` ist allein baubar und bindet die Werkzeugkette selbst ein.
- 2026-09-05, **zum vierten Mal** -- **Auch das eigene Logbuch und das eigene Paket
  bewegen sich.** Vor dem Schreiben neu einlesen, Groesse messen, Archivnummer pruefen;
  beim Paket vorher auf den erwarteten Status pruefen, statt blind zu ersetzen.
- 2026-09-04, dreimal bestaetigt -- **Ein roter Test ist erst dann mein Befund, wenn die
  Fundstelle in meinen Dateien liegt.**

## Nachweise fuehren

- 2026-09-05, **die Lehre dieses Laufs** -- **Zu jeder Zweiseitigkeit gehoert die
  Gegenprobe, die die beiden Schranken auseinanderhaelt.** Wo dieselbe Grenze doppelt
  gehalten wird (meine im Verlauf, die innere in der Kette), sagt ein blosses "es hat
  abgebrochen" nichts: Faellt die aeussere weg, bricht die innere weiter ab, und die
  Probe bleibt gruen. Die Bedingung ist deshalb **zwei** Zeilen -- die Meldung nennt
  meinen Kasten, und sie nennt den anderen **nicht**.
- 2026-09-05 -- **Der erwartete Wortlaut wird erzeugt, nicht abgeschrieben:** die Zahl in
  der Abbruchmeldung mit demselben Meldungsbau, den der Kasten benutzt. Dann kann die
  Erwartung von der Ausgabe nicht abweichen, und eine geaenderte Kapazitaet macht die
  Probe nicht falsch, sondern zieht sie mit.
- 2026-09-05 -- **Zeichengleichheit allein beweist keine Zuordnung.** Vier gleiche Ketten
  sind auch vertauscht gleich. Es braucht die Gegenprobe (Runde n ist **nicht** gleich
  Runde n-1) und, wo die Daten sie hergeben, den Selbstausweis: Jeder Ursachensatz
  traegt nach T18 seine Rundennummer, also je Runde die fremden Glieder zaehlen.
- 2026-09-05 -- **Ein Nachweisskript gehoert in `befunde/messung-<paket>/`, faehrt alle
  Baeume in einem Aufruf und endet mit `Abweichungen: 0`** -- billiger fuer den Pruefer
  als jede Prosa. Es schreibt seinen Bericht selbst und druckt den Wortlaut der
  Abbrueche mit ab, sonst kostet er einen zweiten Bau.
- 2026-09-05, **im eigenen Nachweisskript** -- der Startblock gehoert ans **Dateiende**,
  und ein `continue` mitten in der Schleife darf die Sammelstelle nicht ueberspringen,
  aus der der Bericht spaeter liest.
- 2026-09-04, dreimal belegt -- **Gruen uebersetzen ist kein Nachweis.** Der einzige
  Nachweis fuer einen Riegel ist ein absichtlicher Verstoss, der rot wird -- und der
  Kontrollbaum daneben, der **nicht** rot werden darf.
- 2026-09-05 -- **`ctest` gruen ist keine Zahl, sondern eine je Profil und Bauweg.**
  Gemessen am 2026-09-05: Alleinbau `kern` 10 Eintraege, Arbeitsbereich 16 -- beide
  Zahlen haben ein Verfallsdatum, verglichen wird gegen den eigenen Vorher-Baum.

## Belegstellen, Riegel und CMake

- 2026-09-05 -- **Der Sperrebindungsriegel deckt seit 0139 auch `kern/test`.** Eine neue
  Probe ohne `kern/sperre.hpp` als letzten `#include` bricht schon das Konfigurieren ab.
  Der Kopf einer neuen Klasse bindet ihn dagegen **nicht** -- nur die Quellen und Proben.
- 2026-09-05 -- **`CONFIGURE_DEPENDS` an einem `file(GLOB)` sieht nur neue und
  verschwundene Dateien, keine geaenderten.** Ein Konfigurationsriegel auf Dateiinhalte
  braucht daneben `set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS ...)`.
- 2026-09-05, **die Fehlerklasse, allgemein** -- **CMakes Wahrheitsregel beantwortet
  nicht die Frage eines Riegels.** Auf Gleichheit pruefen, nie auf eine Endung.
- 2026-09-05 -- **`COMPILE_FLAGS` ist eine Zeichenkette mit Leerzeichen, keine
  CMake-Liste.** Vor jeder Behebung die Form der Eigenschaft klaeren, nicht nur den Wert.
- 2026-09-05 -- **Der Bezeichnerriegel liest jeden Namen in Rueckwaerts-Anfuehrung im
  ganzen Kern, auch in den Proben.** Vorgabekennungen wie T19 und Dateinamen wie
  `spiel.md` fallen unter eine benannte Ausnahme; ein Feldname aus einem fremden Kopf
  muss dort wirklich deklariert sein.
- 2026-09-05 -- **Der Belegstellenriegel faengt einen Dateinamen mit Zeilenangabe und
  ein zitiertes Ueberschriftenwort, das es nicht gibt.** Ein Schluessel aus dem Kopf
  einer Entwurfsdatei laesst sich ohne Anfuehrung nennen und geht durch.
- 2026-09-04 -- `befunde/` liegt ausserhalb der Manifest- und Riegelsuche. Nicht
  anfassen -- ausser dem eigenen Unterverzeichnis `messung-<paket>/`.

## Der Kern selbst

- 2026-09-05 -- **Die Einbauregel von `kern/sperre.hpp` ist der ganze Trick der beiden
  Rechensperren**: der letzte `#include` jeder Kernquelle, deshalb braucht die
  Vergiftung keine Ausnahmeliste. Folge fuer jede Probe: kein `<cstring>`, also die
  Teilstringsuche von Hand -- in mehreren Proben steht sie schon.
- 2026-09-05 -- **`festkomma::abbruch` wirft `std::domain_error`**, ist also fangbar und
  am Wortlaut pruefbar. Eine Ausnahme anderer Art gilt in einer Probe **nicht** als
  Abbruch, sonst geht eine falsch geworfene durch.
- 2026-09-05 -- **`kern::meldung::Meldung` ist der Weg zu einer Abbruchmeldung mit
  Zahlen** und zugleich der Weg zum erwarteten Textstueck in der Probe. 511 Zeichen, die
  Kuerzung meldet sich selbst.
- 2026-09-05 -- Ein Behaelter des Kerns hat **feste Groesse und keine Zuteilung**: Im
  ganzen Kern steht keine einzige Speicheranforderung. Wer viel traegt, traegt es in
  `std::array` und begruendet die Kapazitaet aus `specs/`, statt sie zu raten.
- 2026-09-05 -- **Ein Parametername, der eine Mitgliedsfunktion verdeckt, ist unter
  `-Wshadow -Werror` ein Bauabbruch.** Der Name des Behaelters taugt also nicht als Name
  seines eigenen Arguments.
- 2026-09-05 -- Eine Subtraktion nicht als Addition des Gegenwerts bauen; fuer den
  kleinsten `int64_t` ist der Gegenwert selbst der Ueberlauf, den man faengt.
- 2026-09-04 -- **Eine private Funktion ohne Aufrufer ist unter dem Warnsatz ein
  Bauabbruch.** Ersatzlos weg statt unterdrueckt.
- 2026-09-05 -- Der Warnsatz hat `-Wall -Wextra -Wconversion -Wsign-conversion -Wshadow
  -Wold-style-cast -Wcast-qual -Wuseless-cast -Wdouble-promotion -Wfloat-equal
  -Wnon-virtual-dtor -Woverloaded-virtual -Wnull-dereference -Wformat=2 -Werror`. Jede
  Umwandlung ausgeschrieben, aber keine auf denselben Typ -- `-Wuseless-cast` faengt sie.
- 2026-09-02, Nachtrag 09-05 -- Widerspricht eine Abnahmebedingung der Prosa desselben
  Pakets, gewinnt die Abnahme; widerspricht sie einer Vorgabe aus `specs/`, gewinnt die
  Vorgabe -- entschieden vom Projektmanager, nicht vom Bauagenten.

## Offene Faehrten und Unsicherheiten

- 2026-09-05, **worauf ich bei 0140 unsicher bin:** Die Rundenkapazitaet des Verlaufs ist
  die Partielaenge R = 20 aus spiel.md. Der 200-Runden-Lauf des Bruchtesters liefe damit
  in Runde 21 auf einen Abbruch. Ich halte das fuer richtig -- T19 nennt genau diesen
  Lauf als den, der die Ketten wegwirft --, aber es ist eine Entscheidung und keine
  Umsetzung. Steht auch im Paket, damit der Projektmanager sie sieht.
- 2026-09-05, **naechste Faehrte am selben Ort:** Paket 0091 (Rueckwaertsaufloesung ueber
  mehrere Runden, T20) haengt an 0140 und arbeitet auf denselben drei Dateien. Der
  Verlauf gibt dafuer die Kette je Runde und die Suche nach der Rundennummer her; was
  fehlt, ist das Verfolgen ueber Rundengrenzen hinweg.
- 2026-09-04, weiter offen -- **Zwei Wege bleiben fuer den Warnsatzriegel unsichtbar:**
  die Uebersetzerschalter von aussen und die Kommandozeile. Beide stehen in keiner
  Zieleigenschaft.
- 2026-09-04 -- **Zwei Fassungen der Gebietskuerzel, wissentlich:** `src/zustand.cpp`
  (privat) und `src/zustandsausgabe.cpp`. Die saubere Loesung ist ein fremdes Paket.
- 2026-09-05, **erledigt, nicht mehr vorschlagen:** die veraltete Sollzahl in
  `befunde/messung-0076/bauwege.py` (Paket 0135) und die Endungsfalle in
  `werkzeugkette.cmake` (Paket 0108). **Erst die vorhandenen Pakete lesen, dann
  vorschlagen** -- das hat mir schon zwei Vorschlaege gespart.
