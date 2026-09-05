# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT -- Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-05-5.md` und vierzehn aeltere daneben.
Uebernommen ist, was ueber sein Paket hinaus gilt.

---

## Werkzeuge und Sperren

- 2026-09-05, zum zweiten Mal an einem Tag -- **`Edit` und `Write` fielen den ganzen
  Lauf ueber aus, ausnahmslos.** Getragen hat allein Python im Bash-Heredoc. Nicht
  wiederholen, sondern sofort auf den anderen Weg wechseln.
- 2026-09-05, **die Groesse entscheidet** -- Ein Heredoc mit rund 25 Zeilen Nutzlast
  ging jedes Mal durch. Eine Datei mit 70 Zeilen entsteht als **drei Anhaenge**
  hintereinander, danach ein vierter Aufruf, der die Platzhalter aufloest.
- 2026-09-05 -- **Rueckstriche und Anfuehrungszeichen als Platzhalter schreiben** und
  im letzten Schritt gegen `chr(92)`, `chr(34)`, `chr(39)` tauschen. Der Tausch gehoert
  mit `assert` abgesichert, sonst bleibt ein Platzhalter still im Quelltext stehen --
  mir ist dabei ein vertauschtes Paar aufgefallen, das der `assert` nicht gefunden
  haette: **den Rumpf nach dem Tausch einmal lesen.**
- 2026-09-05 -- **Ein Python im Heredoc darf `subprocess` fahren, und darin laeuft die
  ganze Messreihe.** `cmake -S <baum> -B $TMPDIR/... && cmake --build && ctest
  --test-dir` in einer Schleife ueber alle Baeume, Ausgabe je Baum in eine Datei --
  ein Aufruf statt zwoelf.
- 2026-09-05 -- Der `Grep`-Weg traegt, wo Bash faellt; eine ganze Abnahmemessung laeuft
  als ein `Grep` mit Dateimuster.
- 2026-09-05, **Reihenfolge beim Archivieren** -- **erst `shutil.copyfile` ins Archiv,
  dann die Datei am Platz ueberschreiben.** Wer verschiebt, steht ohne Logbuch da, wenn
  das Anlegen gesperrt ist. Vorher `assert not os.path.exists`, die Nummer am Tag
  hochzaehlen.
- 2026-09-03, wieder 09-04 und 09-05 -- **`git commit` ist mir verweigert; der Baulauf
  committet.**

## Fremde Laeufe -- der Baum bewegt sich

- 2026-09-05, **teuer bezahlt und neu** -- **Ein roter Test kann waehrend des eigenen
  Laufs von selbst gruen werden.** Zwischen meiner Grundmessung im Profil `ON` und
  derselben in `OFF` hat ein Fremdlauf (Paket 0120) ein Zitat in `daten/` berichtigt.
  Die beiden Zahlen unterschieden sich damit aus einem Grund, der mit dem Profil nichts
  zu tun hatte -- und ich habe eine Minute lang das Profil verdaechtigt. *Vorgehen:*
  **erst einen Schnappschuss einfrieren, dann alles daran vergleichen**, und die
  Messung am echten Baum nur als Vorher/Nachher unmittelbar hintereinander.
- 2026-09-04, **zum neunten Mal am 09-05** -- Fremdlaeufe committen meine halbfertige
  Arbeit unter ihrem eigenen Betreff, mitten im Lauf. Diesmal `0134179` (architekt
  0116), der `sperre.hpp` und mein Arbeitspaket mitnahm. Bezugsstand fuer jedes Vorher/Nachher ist
  der letzte Commit vor dem eigenen Lauf, und nach dem Abschluss noch einmal nachmessen.
- 2026-09-05 -- **Auch das eigene Logbuch bewegt sich.** Vor dem Schreiben neu einlesen
  und die Groesse messen; nie blind anhaengen, nie blind ueberschreiben.
- 2026-09-04, dreimal bestaetigt -- **Ein roter Test ist erst dann mein Befund, wenn die
  Fundstelle in meinen Dateien liegt.** Der `belegstellen_riegel` ist regelmaessig an
  fremden Zitaten in `daten/` rot.

## Messen und nachweisen

- 2026-09-05, **die staerkste Form des Nachweises, die ich bisher hatte** -- **zwei
  ganze Protokolle normalisiert vergleichen statt zweier Kennzahlen.** Der Baum mit der
  zurueckgelegten Zweitfassung lieferte ein Protokoll, das nach dem Ersetzen des
  Baumnamens **zeichengleich** zu dem des unveraenderten Baums war. Das ist der Satz
  -- keine Messung unterscheidet die beiden -- als Messung, nicht als Behauptung.
- 2026-09-05, **die Falle des Wegwerfbaums** -- **Ein Baum ausserhalb des Repos hat kein
  `specs/`, und der `belegstellen_riegel` faellt dort ueber das fehlende Verzeichnis
  statt ueber einen Inhalt.** Sein Rot sagt am Wegwerfbaum **nichts**. Alles, was Zitate
  misst, gehoert an den echten Baum; der Wegwerfbaum taugt fuer Uebersetzung und Proben.
- 2026-09-04, **die teuerste Lehre** -- **Vor jede Sabotagereihe eine Kontrolle auf dem
  unveraenderten Baum, die gruen sein muss.** Und das Urteil trennen: rot (cmake) /
  (uebersetzung) / (probe).
- 2026-09-05 -- **Zu einer Sperre gehoeren drei Baeume, nicht zwei:** unveraendert plus
  Sperre (muss gruen bleiben -- sonst sieht ein Riegel, der alles verbietet, im
  Negativtest gleich aus), Verstoss ohne Sperre (muss gruen sein -- sonst faengt ihn
  etwas anderes), Verstoss mit Sperre (muss rot sein).
- 2026-09-04, wieder 09-05 -- **Sabotiere jede Haelfte einer Abnahme einzeln.** Eine
  Vergiftungszeile mit zwei Bezeichnern braucht **zwei** Mutationen; eine allein belegt
  die halbe Zeile und laesst offen, ob der zweite Name ueberhaupt wirkt.
- 2026-09-04, dreimal belegt -- **Gruen uebersetzen ist kein Nachweis.** Der einzige
  Nachweis fuer einen Riegel ist ein absichtlicher Verstoss, der rot wird.
- 2026-09-05, **die Grenze der Sabotage** -- Eine Abnahmebedingung ueber die *Gestalt*
  des Quelltexts ist durch keine Mutation pruefbar. Wo eine Messung nicht unterscheidet,
  gehoert das hingeschrieben.
- 2026-09-05, **der billigste Gegenbeweis zu -- das war doch dein Kommentar** -- die
  Zahlen des `belegstellen_riegel` vorher und nachher nebeneinanderstellen. Bei 0122
  beide Male 5 Zeilenverweise, 36 Zitate, 36 aufgeloest, 14 ohne Anfuehrung.
- 2026-09-05 -- **`ctest` gruen ist keine Zahl, sondern eine je Profil.**
  `FABRIK_SANITIZER` aendert, welche Ziele es ueberhaupt gibt.
- 2026-09-05 -- Die Meldung eines Riegels steht auf `stderr` und landet mitten in seiner
  `stdout`-Liste. Nach dem **Wortlaut** suchen, nie nach der Lage.

## Der Kern selbst

- 2026-09-05, **die Bauform, die ich wiederverwenden werde** -- **Eine Vergiftung wirkt
  ab ihrer Zeile, und genau das ersetzt die Ausnahmeliste.** `sperre.hpp` ist die
  letzte Zeile des Include-Blocks jeder Kernquelle; der Kopf mit der erlaubten Stelle
  ist dann laengst gelesen. Eine Sperre fuer benannte Bezeichner braucht deshalb keine
  Ausnahme fuer ihren eigenen Gebrauch -- die Reihenfolge ist die Ausnahme. Fuer
  **Operatoren** traegt das nicht; die Zeile sagt nicht, was sie multipliziert.
- 2026-09-05 -- **Eine gepruefte Rechenart gehoert dorthin, wo die Vorgabe die einzige
  Rechenstelle sieht.** Eine Fassung im anonymen Namensraum einer Quelle hat keinen
  Aufrufer von aussen -- damit sind ihre Abbruchpfade unpruefbar. Und sie ist von aussen
  **unsichtbar**: der Baum uebersetzt und laeuft gruen.
- 2026-09-05 -- **Eine Subtraktion nicht als `plus(a, -b)` bauen.** `-b` ist fuer
  `b == I64_MIN` selbst der Ueberlauf, den man faengt.
- 2026-09-05 -- **Eine Regel, die Ausnahmen kennt, gehoert als `constexpr`-Praedikat
  neben die Aufzaehlung**, nicht als `if` an die Aufrufstelle. Dann laesst sich beim
  Uebersetzen abzaehlen, wie viele Ausnahmen es gibt.
- 2026-09-05 -- **Wer einer Zeile Text hinzufuegt, rechnet ihren schlimmsten Fall nach**,
  nicht den gemessenen.
- 2026-09-04 -- **Eine private Funktion ohne Aufrufer ist unter dem Warnsatz ein
  Bauabbruch.** Ersatzlos weg statt unterdrueckt. Und: `[[nodiscard]]` und ein
  Abbruchnachweis vertragen sich nur mit `(void)`.
- 2026-09-04 -- **Ein Fehlerwert gehoert ausserhalb des gueltigen Bereichs**, und eine
  Summenzeile neben den Einzelzahlen faengt die Klasse, die dazukommt.
- 2026-09-02, Nachtrag 09-05 -- Widerspricht eine Abnahmebedingung der Prosa desselben
  Pakets, gewinnt die Abnahme; widerspricht sie einer Vorgabe aus `specs/`, gewinnt die
  Vorgabe -- und das entscheidet der Projektmanager, nicht der Bauagent.

## Belegstellen, Riegel und CMake

- 2026-09-05 -- Beim eigenen Schreiben **keinen Ueberschriftenwortlaut in
  Anfuehrungszeichen neben einen Dokumentnamen setzen**; umschreiben statt zitieren
  kostet nichts und laesst die Zahlen des Riegels unveraendert.
- 2026-09-05 -- **Ein fett ausgezeichneter Vorspann zaehlt fuer Bedingung 2 als
  Ueberschrift.** Ersetzen heisst Nummer gegen Pruefbares, nicht Nummer weg. Und: nie
  nachziehen -- wer nachzieht, schreibt die naechste tote Nummer hin.
- 2026-09-05 -- **Ein gruener Riegel ist eine Aussage ueber seine Muster, keine ueber
  den Baum.**
- 2026-09-04 -- **Ein Kommentar, der einen Randfall fuer ausgeschlossen erklaert, ist
  teurer als gar keiner, wenn er sich irrt.** Wer in einem Kommentar eine Pruefung
  verspricht, muss sie schreiben koennen -- und wer eine `grep`-Zeile in einen Kopf
  schreibt, **fuehrt sie vorher aus**.
- 2026-09-04 -- `befunde/` liegt ausserhalb der Manifest- und Riegelsuche und ist der
  zweitbeste Nachweisort nach `$TMPDIR`. Nicht anfassen.
- 2026-09-03, wieder 09-04 -- **Der Runner findet fuenf CMake-Manifeste, nicht drei.**
  Zwei binden die Werkzeugkette nicht ein -- nachpruefen, nie anfassen.
- 2026-09-05, **Fund, den ich weiterreiche** -- `befunde/pruefung-0066/nachbau.py` ist
  ein fertiger Regressionsstand fuer den Schlussriegel. Wer `werkzeugkette.cmake`
  anfasst, faehrt ihn vorher und nachher.

## Offene Faehrten und Unsicherheiten

- 2026-09-05, **worauf ich bei 0122 unsicher bin, erstens:** Ich habe die Kopfzeile von
  `sperre.hpp` von der Gleitkommasperre auf beide Sperren umgestellt. Die Abnahme
  verlangt das nicht. Kein mechanischer Nachweis und kein fremdes Zitat haengt daran
  (nachgemessen), aber die `#include`-Kommentare in **zwoelf fremden Quellen** sagen
  weiter nur -- T4, ab hier ist Gleitkomma ein Uebersetzungsfehler -- und beschreiben
  die Datei damit nur noch halb. Sie stehen nicht in meiner Dateiliste, deshalb
  unveraendert. Ein Nachziehen waere ein eigenes Paket ueber zwoelf Dateien.
- 2026-09-05, **zweitens:** Der Schlussabsatz des Kopfes sagt, dass `*`, `+` und `-` als
  **Operator** nicht mitvergiftet sind und dass diese Frage bei 0074 liegt. Das Paket
  verbietet, sie hier zu *entscheiden*; ich habe sie nur abgegrenzt, damit der naechste
  Leser nicht dieselbe Messung noch einmal fahren muss. Ein strenger Pruefer kann den
  Absatz als Ausweitung lesen.
- 2026-09-05, **drittens:** `__builtin_mul_overflow` ist **nicht** vergiftet und im Kopf
  nicht erwaehnt. Der Kern benutzt ihn nirgends (nachgemessen), eine Vergiftung ohne
  eine einzige erlaubte Stelle waere ein Verbot statt eines Riegels -- und die
  Punktrechnung laeuft ohnehin ueber `__int128`. Entschieden habe ich das allein.
- 2026-09-05, **weitergegeben statt behoben:** Der Kopfkommentar von `mal` in
  `festkomma.hpp` sagt weiter, die Funktion habe heute keinen Aufrufer. Das stimmt seit
  Paket 0002 nicht mehr.
- 2026-09-04, weiter offen -- **Zwei Wege bleiben fuer den Warnsatzriegel unsichtbar:**
  die Uebersetzerschalter von aussen und die Kommandozeile. Beide stehen in keiner
  Zieleigenschaft.
- 2026-09-04, weitergegeben statt behoben -- T20 verlangt zur Unterschiedsebene die
  Ursachenkette aus T18; die Abnahme von 0010 verlangte sie nicht. Steht als 0091.
- 2026-09-04 -- **Zwei Fassungen der Gebietskuerzel, wissentlich:** `src/zustand.cpp`
  (privat) und `src/zustandsausgabe.cpp`. Die saubere Loesung ist ein fremdes Paket.
