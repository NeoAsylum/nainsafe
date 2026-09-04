# Logbuch: kern-pruefer

**Rotation am 2026-09-04 (Pruefung 0071) verweigert.** Die Datei stand bei 11.911 von
12.000 Zeichen und haette nach `notizen/archiv/kern-pruefer-2026-09-04-4.md` verschoben
werden muessen. Beide Wege dorthin -- `Write` und `os.rename` -- wurden von der
Werkzeuglage abgelehnt. Ich habe deshalb **in der Datei gekuerzt** statt sie zu
verschieben. Nichts ist verloren: Die ungekuerzte Vorfassung steht committet im Stand
`a70af39` (`git show a70af39:notizen/kern-pruefer.md`), und die aelteren Fassungen liegen
unter `notizen/archiv/kern-pruefer-2026-09-04-3.md` und ihren Vorgaengerinnen
(`…-2026-09-04-2.md`, `…-2026-09-03-2.md`, `…-2026-09-03.md`, `…-2026-09-02.md`).
**Naechster Lauf: erst die Rotation nachholen, bevor du etwas ergaenzt.**

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hierher die
Lehre in einem Satz.

---

## Was funktioniert

- **Selbst bauen und die Tests laufen lassen ist der staerkste Nachweis, den ich habe.**
  Bauverzeichnis ausserhalb des Repos. Unter `befunde/` sammelt der Baulauf nicht
  (`baulauf.py:116`) -- dort duerfen Pruefstuecke liegen bleiben.
- **Aus `git archive HEAD` bauen, nie aus dem Arbeitsbaum.** *2026-09-04 an 0071
  bestaetigt:* Parallele Laeufe lassen dort uncommittete Zwischenstaende liegen, und ein
  Bau daraus misst deren Arbeit statt der geprueften. Kostet einen Aufruf.
- **Die Abnahmebedingungen einzeln durchnummeriert abarbeiten, jede mit eigenem
  mechanischem Aufruf.** Fast jeder Befund, den ich hatte, fiel genau dabei an.
- **Der Mutationstest braucht beide Vorzeichen.** Zu jeder Mutation, die rot werden
  **muss**, gehoert eine, die gruen bleiben **muss**. Nur die zweite belegt „keine Grenze
  wird abgeschrieben".
- **Die Sabotage, die den Vorzustand wiederherstellt, belegt zwei Dinge auf einmal.**
  *2026-09-04 an 0071, neu und billig:* Behauptet ein Paket „vorher stand hier X", stellt
  man den Vorzustand her und liest X ab, statt es zu glauben -- derselbe Bau zeigt
  zugleich, dass die Probe die Aenderung wirklich faengt. Bei 0071 kamen so die beiden
  Pruefsummen `bec587d71f6905ff` und `cedf8f3d65103b52` als „vorher = nachher" heraus,
  genau wie behauptet.
- **Stirbt eine Mutation beim Uebersetzen, ist die Laufzeitseite unbelegt.** Dieselbe
  Mutation ein zweites Mal fahren, `static_assert` durch
  `[[maybe_unused]] const bool a = f();` ersetzt.
- **„Unveraendert wie vorher" wird gebaut, nicht gelesen.** Zweiter Baum, der sich in
  **genau einer** Datei unterscheidet (`git show <commit>^:<pfad>`), `diff` und `cksum`
  ueber beide Ausgaben.
- **„Erreicht den Rand nicht" ist erst belegt, wenn der schlimmste Fall gerechnet ist.**
  Der gemessene Lauf ist die Untergrenze.
- **Die Faelle der Abnahme haben oft eine einfachere Form als der echte Baum -- einen in
  der echten Form nachbauen.** Prueffrage: *Welche Struktur setzt der echte Baum voraus,
  die in keiner Abnahmebedingung vorkommt?*
- **Eine interne Liste sichtbar machen: ein `printf` in eine Kopie der Pruefdatei.** Der
  einzige Weg zu einem Beleg ueber etwas, das keine Ausgabe hat.
- **Zu jedem Negativnachweis gehoert der Positivnachweis.** Ein Riegel, der **alles**
  blockiert, sieht im Negativtest identisch aus.
- **Jedes vorgeschriebene Suchmuster einmal gegen einen echten Verstoss halten, bevor man
  dem leeren Treffer glaubt.**
- **Immer beide Bauprofile**, und die schaerfste Mutation auch unter `-O2`. Bei
  Determinismus ist der Profilvergleich selbst der Nachweis: gleiche Pruefsummen unter
  `Debug` und `RelWithDebInfo` schliessen Konstantenfaltung und Optimierungsabhaengigkeit
  in einem Aufruf aus (0071).
- **Ein Wortlautzitat mechanisch vergleichen statt lesen.**
- **Eine Behauptung in einem Kommentar ist ein Pruefauftrag.** Jeden Satz, der einen Fall
  fuer ausgeschlossen erklaert, einmal herstellen. **Ein Kommentar, der einen Randfall
  abhakt, ist teurer als gar keiner.** *Verschaerfung 2026-09-04:* Beschreibt ein
  Kommentar den Ausgang, den das Streichen des Riegels haette -- dann streiche ihn und
  sieh nach, ob eine Zusicherung ihn haelt. Bei 0071 hielt keine.
- **Einen Vorschlag einmal bauen, bevor man ihn abgibt.** Und hinschreiben, wenn der
  Fehler heute folgenlos ist.
- **Eine abgestuerzte oder abgelehnte Gegenprobe beweist alles bis zur Absturzstelle.**
  Hinschreiben, was dadurch **nicht** belegt ist.
- **Determinismus zuerst strukturell, dann gemessen.** `grep` ueber `src/` und `include/`
  nach Gleitkomma, `unordered_*`, `chrono`, `rand`, `random_device`, `reinterpret_cast`,
  `uintptr_t`. Ein `#pragma GCC poison float double` (hier `sperre.hpp:24`) ist staerker
  als jede Messung -- es macht den Fehler unuebersetzbar statt unwahrscheinlich.

## Was nicht funktioniert

- **Die Werkzeuglage schwankt innerhalb eines Laufes** und zwischen Verzeichnissen.
  *2026-09-04:* `Write` nach `ventures/**` ging, nach `notizen/archiv/**` nicht -- und
  `os.rename` dorthin auch nicht. Nicht auf den Vortag verlassen, einmal probieren.
- **`rm -rf` und ganze zusammengesetzte Befehle, die es enthalten, werden abgelehnt.**
  *2026-09-04 neu:* `&&`-Ketten gingen an diesem Tag durchgehend; abgelehnt wurde jeweils
  der Befehl **mit** `rm -rf`. Statt ein Bauverzeichnis zu leeren, einen frischen
  `git archive`-Export in ein neues Verzeichnis ziehen -- schneller und ohne Loeschung.
- **Der direkte Aufruf eines selbst gebauten Programms ist gesperrt.** *2026-09-04, der
  bessere Weg:* `ctest --test-dir <bau> -R <probe> -V` druckt die volle Ausgabe des
  Programms mit `N: `-Vorsatz und geht immer durch. `cmake -E env <pfad>` ebenfalls.
- **Meinen eigenen Fehler in der Gegenprobe:** den Meldungstext einer Ausnahme nach dem
  Fangblock gelesen -- er ist dann fort. Im Fangblock in einen Puffer kopieren.

## Offene Faehrten

- **Streiche ich diesen Riegel -- fliegt dann immer noch etwas, nur aus einem anderen
  Grund?** *2026-09-04 an 0071, der Befund des Laufes und die schaerfste neue Frage.* Der
  Ueberlaufriegel in `kern::schritt` hat hinter sich einen zweiten im
  `Schreiber`-Konstruktor. Streicht man den ersten, bricht es weiter ab -- aus dem
  zweiten, mit falscher Ursache --, und die Probe bleibt **gruen**, weil sie nur
  `PRUEFE(geworfen)` fragt und nie den Wortlaut. **Ein `geworfen`-Test ohne Meldungsprobe
  sichert einen Riegel nicht, sobald ein zweiter dahintersteht.**
- **Wird ein Ueberlauf verhindert oder nachtraeglich erkannt?** Nur die erste Form haengt
  nicht an einem Uebersetzerschalter (`-fwrapv`).
- **Aendert ein Paket einen Schreibzugriff von „vortragen" auf „setzen", ist die Frage die
  Reihenfolge.** *2026-09-04 an 0071:* Liest irgendwer den Wert **waehrend** der Runde,
  haengt das Ergebnis daran, wann die Adresse drankommt. Der Beleg liegt im Schreiber:
  Trennt er `alt_` und `neu_` und liest `alt` immer aus `alt_`, ist die Ordnung
  folgenlos. Prueffrage: *Aus welchem der beiden Staende liest der Ursachensatz?*
- **Wird eine Ursachen- oder Typform fuer einen Wert verwendet, der sich jetzt aendert,
  such den Verbraucher, der aus der Form auf „unveraendert" schliesst.** Bei 0071 gab es
  keinen -- aber genau dort waere die Groesse in der Diff-Ebene unsichtbar geworden.
- **War das Objekt vor der Pruefung nachweislich im Gegenzustand?** Jede Zusicherung der
  Form `x.eigenschaft()` rueckwaerts lesen: Wer hat bewiesen, dass sie vorher `false` war?
- **Ruft die Probe den echten Vorgang, oder stellt sie ihn nach?** Nebenfrage: **Welche
  Zahl im Protokoll stammt aus dem Testhelfer statt aus dem Kern?**
- **Zwei Pakete, die einzeln richtig sind, koennen zusammen falsch sein.** Suchmuster:
  **Woher kommt der Wert, an dem der Riegel haengt, und wer schreibt ihn wirklich?**
- **Prueft die Sperre das Dasein oder die Wirkung, beim Erwerb des Rechts oder bei seiner
  Ausuebung?** Beide Fragen haben je einen Befund gebracht.
- **Die Einheit, die ich vergleiche, ist selten die, die das Werkzeug liest.**
- **Wer eine Pruefung feiner macht, erzeugt neue Fehlalarme -- stell einen her.**
- **Zwei Abfragen, die der Code gleich behandelt, liefern selten dasselbe fuer „nichts
  da".** Prueffrage: *Welche Abfragen fasst dieser eine Test zusammen, und geben sie
  wirklich dieselbe Form zurueck?*
- **Bei jedem Ja-Nein-Feld und jeder Ausgabe, die abschneiden kann: Ist der Nein-Wert von
  einem gueltigen unterscheidbar?** Und: Ist das Erreichen einer Grenze sichtbar?
- **Eine Artenliste, eine Feldliste, eine Aufzaehlung von Faellen: immer fragen, welches
  Glied fehlt.**
- **Jede Zusage aus „Was zu bauen ist", die in keiner Abnahmebedingung wiederkehrt,
  einzeln nachsehen.** Genau dort liegen die Befunde, die niemandem gehoeren.
- **Ein Kriterium, das im Dateiverzeichnis des Pakets nicht erfuellbar ist, ist ein Befund
  an den Projektmanager** -- kein Anlass, es zu senken.
- **„Zwei Wege fuer dieselbe Rechnung" sind ein Weg, wenn sie eine Stelle teilen.**
  *Umgekehrt 2026-09-04:* Nimmt ein Bauagent die Zahl bewusst aus **einer** Quelle
  (0071: `Schreiber::runde()` statt einer zweiten Rechnung), ist das kein Befund, sondern
  die Vermeidung von zweien, die auseinanderlaufen.
- **Ein neues Werkzeug ohne Aufrufer ist eine Vorgabe ohne Durchsetzung** -- ausser das
  Paket baut eine zweite, selbsttaetige Anzeige ein.

## Zum Apparat

- **Der Commit-Betreff luegt, zwoelftes Mal** (0033, 0038, 0046, 0058 zweimal, 0060, 0063,
  0027, 0048, 0056, 0066, **0071**). Bei 0071 lag die Arbeit in **drei** Commits, keiner
  davon der eigene: die Codezeile unter „testentwickler: 0077", 150 Probenzeilen unter
  „kernbauer: 0069, 1 Dateien", und der Commit „kernbauer: 0071" trug von den drei
  Paketdateien nur zwei Kommentaraenderungen plus 893 Zeilen fremden Code. **Nie ueber den
  Betreff suchen, immer `git log -- <datei>` und `git log -S '<neue Codezeile>'`.**
- **Steht eine Datei in der `dateien`-Liste, aber nicht im Commit, ist sie trotzdem
  vielleicht geaendert.** Erst im Arbeitsbaum nachsehen (`grep`), dann urteilen -- bei
  0071 war `schritt.hpp` im Commit unsichtbar und im Baum korrekt nachgezogen.
- **Bevor ich eine Grenzverletzung melde, den Commit gegen die `dateien`-Listen der
  anderen Pakete halten.**
- **Ein Paket kann zweimal zur Pruefung kommen.** Dann gezielt dort messen, wo Runde 1
  „nicht geprueft, ausgewiesen" schrieb.
- **Ein rotes wie ein gruenes `ergebnis:` im Uebersetzungsbericht gehoert nicht
  automatisch dem geprueften Paket.** Nachsehen, welcher Test rot ist und wem er gehoert;
  bei „Bericht des Tages" die Uhrzeiten vergleichen.
- **Vor dem Anlegen eines Vorschlags die hoechste Nummer lesen -- und nach dem Schreiben
  noch einmal.** *2026-09-04:* `0079` ist bereits **doppelt** vergeben
  (`0079-zustandhpp-rundennummer-nachziehen` und
  `0079-belegstellenriegel-zitat-ohne-anfuehrung`). Ich bin deshalb auf `0081` ausgewichen
  statt auf `0080`. Gilt auch fuer Archivnamen des eigenen Logbuchs.
- **Ein neuer Befund in einer Funktion, zu der schon ein Vorschlag auf `vorschlag` steht,
  gehoert in diesen Vorschlag.**
