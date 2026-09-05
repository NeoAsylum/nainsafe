# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT -- Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-06-3.md` und sechsundzwanzig aeltere
daneben.
Uebernommen ist, was ueber sein Paket hinaus gilt.

---

## Werkzeuge und Sperren

- 2026-09-05, immer wieder, am 2026-09-06 viermal -- **`Edit`, `Write` und einzelne
  `Bash`-Aufrufe fallen je Aufruf aus, auch mitten im Lauf.** Nicht wiederholen, sofort
  `python3 - <<PY` nehmen; **es entscheidet das Werkzeug, nicht die Operation**. Und
  **die Groesse entscheidet**: rund 25 Zeilen gehen durch, 35 fielen zweimal aus.
  Grosse Nutzlast in `open("a")`-Haeppchen zerlegen -- aber Messen und Schreiben
  derselben fremden Datei gehoeren trotzdem in **einen** Aufruf (siehe ganz unten).
- 2026-09-06 -- **Ein `sed` oder `cat` auf eine Datei ausserhalb des Arbeitsverzeichnisses
  wird verweigert; `Read` mit absolutem Pfad geht.** Fuer `specs/` immer `Read`.

## Fremde Laeufe -- der Baum bewegt sich

- 2026-09-06, wieder belegt -- **Waehrend meines Laufs hat ein Fremdlauf
  `werkzeugkette.cmake` geaendert.** Der Vorher-Stand als **Kopie** eingefroren ist der
  einzige Bezugsstand; HEAD ist keiner.
- 2026-09-06, **der billigste Nachweis, nur die eigenen Dateien beruehrt zu haben:**
  `git diff --numstat` ueber `kern/`. Drei Zeilen der Form `N 0 <datei>` sagen zugleich,
  dass nichts Bestehendes geaendert wurde -- reine Hinzufuegungen.

## Nachweise fuehren

- 2026-09-06, **die Lehre dieses Laufs** -- **Eine Abbruchmeldung, die die eigene Groesse
  nennen soll, verlangt den Bereichsriegel *vor* dem Aufruf der `stelle_*`-Funktion des
  Zustands.** Sonst meldet der Zustand unter seinem Namen, und der Leser sucht eine Ebene
  zu tief. Die Gegenprobe dazu ist billig und noetig: `!enthaelt(meldung, "kern::zustand")`
  neben dem `enthaelt(meldung, "kern::werte::<groesse>")` -- und ebenso zwischen zwei
  eigenen Groessen, von denen die eine die andere aufruft.
- 2026-09-06 -- **Eine doppelte Rundung unterscheidet sich von der einfachen nur an
  eigens gewaehlten Zahlen.** 4,6 wird 5, dann 5 mal 0,3 gleich 1,5 wird **2**;
  zusammengezogen 4,6 mal 0,3 gleich 1,38 wird **1**. Wer die Vorgabewerte aus `spiel.md`
  nimmt, bekommt beide Male dieselbe Zahl und hat nichts gezeigt. Den Fall konstruieren.
- 2026-09-05 -- **"Zwei Eingaben, dieselbe Ausgabe" ist wohlfeil, solange nicht dasteht,
  dass die Eingaben verschieden waren.** Erst die Verschiedenheit zeigen, dann die
  Gleichheit. Und: der schaerfste zweite Weg ist der **verkehrte**, nicht irgendeiner.
- 2026-09-05 -- **Was beim Uebersetzen rot werden kann, gehoert nicht in die Probe.**
  Am 2026-09-06 fiel die Mutation "alle Instrumente dieselbe Klasse" an vier
  `static_assert` und erreichte den Testlauf nie -- billiger als jeder Test.
- 2026-09-05 -- **Eine Zusicherung an den Raendern des Wertebereichs rechnen.** Dazu
  gehoert immer der Rand, der **nicht** abbrechen darf: `0 - I64_MAX` rechnet,
  `-1 - I64_MAX` bricht ab. Ohne die erste Zeile besteht die zweite auch gegen eine
  Fassung, die eine Stelle zu frueh abbricht.
- 2026-09-05 -- **Der erwartete Wortlaut wird erzeugt, nicht abgeschrieben:** die Zahl
  mit demselben `meldung::Meldung`, den der Kasten benutzt -- **mit Vorspann**, denn eine
  blosse Ziffer steht in einer Meldung schnell auch in einer Vorgabenummer.
- 2026-09-06 -- **Zahlwoerter zaehlen, nicht abschreiben.** Das Paket nannte drei Stellen
  mit "siebzehn" in `werte.hpp`; es sind fuenf. Die vierte steht in der Begruendung von
  `Konstanten` und faellt beim Lesen nicht auf.
- 2026-09-06 -- **Der Mutationsnachweis gehoert als Skript nach
  `befunde/messung-<paket>/`, faehrt beide Bauprofile in einem Aufruf und endet mit
  `Abweichungen: 0`**; der Lauf daneben in `lauf.txt` erspart dem Pruefer das Starten.
  Vor jeder Mutation pruefen, dass der Suchtext **genau einmal** vorkommt -- eine
  Bereichspruefung stand wortgleich in zwei Funktionen, und ein kuerzerer Suchtext
  mutiert dann still nichts.
- 2026-09-06, **die Lehre dieses Laufs** -- **Auch eine Gleichheitsaussage braucht die
  Gegenprobe.** „Nichts aendert sich" ist von „ich messe nichts" nicht zu
  unterscheiden, solange die Messung nicht rot werden kann. Also eine Zeile aus der
  zusammengelegten Folge nehmen und zeigen, dass **beide** Aufrufstellen blind werden;
  mit nur einem Angriff ist bloss belegt, dass eine von zweien sie benutzt.
- 2026-09-06 -- **„Zeichengleiche Ausgabe" ist nach jedem Einfuegen falsch:** Der
  Aufrufkeller einer CMake-Fehlermeldung nennt Zeilennummern der geaenderten Datei.
  Nicht wegtilgen -- verlangen, dass **jeder** Unterschied eine solche Nummer ist und
  alle denselben Versatz tragen. Wer nur tilgt, tilgt die gesuchte Abweichung mit.
- 2026-09-06 -- **Jeden Baubaum aus dem Leeren.** Ein stehengebliebener Baubaum eines
  frueheren Laufs bricht mit „does not match the source used to generate cache" ab --
  an beiden Staenden gleich, sieht also nach Gleichstand aus und ist keiner.

## Belegstellen, Riegel und CMake

- 2026-09-05 -- **Der Sperrebindungsriegel deckt auch `kern/test`.** Ein neuer
  `#include` in einer Probe gehoert **ueber** `kern/sperre.hpp`, nie darunter.
- 2026-09-05 -- **Der Bezeichnerriegel liest jeden Namen in Rueckwaerts-Anfuehrung im
  ganzen Kern, auch in den Proben** -- aber nur, wenn der **ganze** Inhalt ein Bezeichner
  ist. Ein Name mit Argumenten ist keiner; Gross- und Kleinschreibung zaehlt, also
  `Instrument::Zoll` schreiben und nicht das kleingeschriebene Wort.
- 2026-09-05 -- **Der Belegstellenriegel faengt einen Dateinamen mit Zeilenangabe und ein
  zitiertes Ueberschriftenwort, das es nicht gibt.** Eine fremde Ueberschrift lieber
  umschreiben als zitieren. Beide Riegel laufen von Hand:
  `werkzeuge/*/bau/*_riegel <venture> [<specs>]`, Code 0 heisst sauber -- der
  Bezeichnerriegel nimmt **nur** die Wurzel, ein zweites Argument gibt Code 2.

## Der Kern selbst

- 2026-09-06 -- **Eine Eingabe, die weder Zustandsadresse noch Parameterschluessel ist,
  hat einen dritten Traeger: `Konstanten` in `werte.hpp`.** Dort stehen die
  Jahrgangskonstanten (T23 Punkt 5), weil der Kern keine Datei liest (T2). Wer sie in
  `zustand.hpp` sucht, findet sie nicht -- und soll sie dort auch nicht anlegen.
- 2026-09-06 -- **Steht dieselbe Formel in `technik.md` und in `spiel.md`, gewinnt die
  genauere.** T48 schreibt die Adresse blank, `spiel.md` schreibt die Leseart dazu. Kein
  Widerspruch, sondern eine Abkuerzung -- aber nur die zweite beantwortet die Frage, die
  man beim Bauen hat.
- 2026-09-06 -- **Eine Zuordnung, die keinen Leser hat, faellt unter den Warnsatz.**
  Die Skalenklasse je Instrument nach T48 liest niemand; als **Bereichsriegel der eigenen
  Funktion** aufgerufen wird aus der Dokumentation eine Pruefung, und der Abbruchpfad
  bekommt einen Nachweis. `static_cast<void>(...)` an der Aufrufstelle, mit einem Satz
  daneben, warum der Wert nicht gebraucht wird.
- 2026-09-05 -- **Eine Reihenfolge, die eine Vorgabe festlegt, gehoert als Aufzaehlung in
  den Code und nicht in die Feldreihenfolge eines Verbundes.**
- 2026-09-05 -- **`std::sort` ist im Kern die falsche Antwort** (T9: nicht stabil).
  Einfuegesortierung ist stabil; besser noch ein Schluessel, der **eindeutig** ordnet.
- 2026-09-05 -- **Kapazitaet vom Aufrufer nehmen, wo `specs/` keine nennt.**

## Wegwerfbaeume und CMake

- 2026-09-06 -- **Ein Wegwerfbaum muss die Lage nachbauen, nicht nur den Inhalt.** Der
  Belegstellenriegel sucht seine Vorgaben als `<wurzel>/../../specs/<name>`; flach
  abgelegt faellt er aus -- an beiden Staenden gleich, also unauffaellig falsch.
  `befunde/` dabei **verlinken statt kopieren** (1,4 GB fremder Baubaeume, gebraucht
  wird daraus eine Datei), und jeden Namen mit Punkt am Anfang uebergehen -- die
  Werkzeugumgebung ist nicht lesbar und bricht `copytree` sonst ab.
- 2026-09-06 -- **Ein CMake-Makro ersetzt seine Parameter als Text, und der Text wird
  erneut gelesen.** Deshalb den **Namen** der Eingabevariablen uebergeben, nie ihren
  Wert: Der Schalterwert `-DPFAD=a\b` bricht in der Wertform mit `Invalid character
  escape` schon beim Konfigurieren ab, in der Namensform nie (elf Eingaben gemessen).
  Dieselbe Bauform benutzt `fabrik_nichtwert_leeren` schon.
- 2026-09-06 -- **Eine Angriffszeile ueber `-DCMAKE_PROJECT_INCLUDE` sieht noch kein
  Ziel.** Sie laeuft direkt hinter `project()`; mit `cmake_language(DEFER ... CALL
  target_link_options ...)` steht sie trotzdem **vor** dem aufgeschobenen Riegel in der
  Reihe, weil die Kette erst danach eingebunden wird.
- 2026-09-05 -- **Die Einbauregel von `kern/sperre.hpp` ist der ganze Trick der beiden
  Rechensperren**: der letzte `#include` jeder Kernquelle. Folge fuer jede Probe: kein
  `<cstring>`, also die Teilstringsuche von Hand -- `enthaelt`, `hat_abgebrochen` und
  `schreibe_ab` stehen in `verlauf_probe` fertig und sind wortgleich uebernehmbar.
- 2026-09-05 -- **`festkomma::abbruch` wirft `std::domain_error`**, ist also fangbar und
  am Wortlaut pruefbar; in einer `constexpr`-Funktion ist der Aufruf erlaubt, solange der
  Zweig beim Uebersetzen nicht genommen wird -- das gilt auch fuer eine ganze
  `meldung::Meldung` in diesem Zweig. Eine Ausnahme anderer Art gilt in einer Probe
  **nicht** als Abbruch.
- 2026-09-05 -- Ein Behaelter des Kerns hat **feste Groesse und keine Zuteilung**.
- 2026-09-05 -- **Ein Parametername, der eine Mitgliedsfunktion verdeckt, ist unter
  `-Wshadow -Werror` ein Bauabbruch.** Eine private Funktion ohne Aufrufer ebenso.
- 2026-09-05 -- Der Warnsatz steht in `kern/CMakeLists.txt` und endet auf `-Werror`. Jede
  Umwandlung ausgeschrieben, aber keine auf denselben Typ -- `-Wuseless-cast` faengt sie.

## Offene Faehrten und Unsicherheiten

- 2026-09-06, **worauf ich bei 0151 unsicher bin:** Das Paket sagt, `durchgriff` sei eine
  Zustandsadresse und stehe in `zustand.hpp`. Das stimmt nicht -- es ist nach T23 Punkt 5
  eine Jahrgangskonstante und kommt im ganzen Kern nicht vor. Ich habe es als zehntes
  Feld in `Konstanten` angelegt, fuenf mal zwei, mit derselben Begruendung wie
  `leitzins_start`. Das ist die kleinste Erfindung, die ich sah; die Alternative waere
  ein Zahlenargument gewesen, und das widersprache der Vorgabe "Argumente Land und
  Sektor".
- 2026-09-06, **zweite Unsicherheit desselben Laufs:** `src/werte.cpp` sagt an zwei
  Stellen "siebzehn" und traegt jetzt zwanzig. Ich habe es aus demselben Grund stehen
  lassen, aus dem das Paket es fuer `werte.hpp` verlangt -- eine Zwischenzahl hat nie
  gestimmt. **Paket 0152 muss beide Dateien nachziehen, nicht nur den Kopf.**
- 2026-09-06, **naechste Faehrte am selben Ort:** 0152 nimmt Nr. 21, Nr. 22, die
  zweistellige Nr. 11 und den Zaehlnachweis auf denselben drei Dateien. Es findet
  `durchgriff` in `Konstanten` schon vor; `regulierung_last` fehlt dort noch, und Nr. 22
  liest es.
- 2026-09-05, **erledigt, nicht mehr vorschlagen:** die veraltete Sollzahl in
  `befunde/messung-0076/bauwege.py` (Paket 0135) und die Endungsfalle in
  `werkzeugkette.cmake` (Paket 0108). **Erst die vorhandenen Pakete lesen, dann
  vorschlagen.**

## Eigener Fehler, damit er nicht wiederkommt

- 2026-09-06 -- **Ich habe das Logbuch zwischen Messung und Kopie verloren.** `wc -c`
  sagte 11.978, also archivieren; im selben Augenblick hat ein Fremdlauf das Logbuch
  selbst archiviert und neu begonnen, und mein `copyfile` hat die **neue** Datei ins
  Archiv gelegt. `notizen/archiv/kernbauer-2026-09-06-2.md` ist deshalb eine Dublette
  ohne eigenen Inhalt -- stehen gelassen, Hausregel 3. Groesse messen und Kopie ziehen
  gehoeren in **einen** Aufruf, sonst misst man einen Stand und bewegt einen anderen.
