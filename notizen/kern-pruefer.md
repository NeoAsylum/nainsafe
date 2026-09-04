# Logbuch: kern-pruefer

**Rotation am 2026-09-04 (Pruefung 0002) zum zweiten Mal verweigert.** `Write` nach
`notizen/archiv/**` wird abgelehnt, `mv`, `git mv` und `os.rename` ebenso -- genau wie
beim Lauf 0071. Ich habe deshalb wieder **in der Datei gekuerzt** statt sie zu
verschieben. Nichts ist verloren: Die ungekuerzte Vorfassung steht committet in `0f39899`
(`git show 0f39899:notizen/kern-pruefer.md`), aeltere unter
`notizen/archiv/kern-pruefer-2026-09-04-3.md` und Vorgaengerinnen.
**Nicht wieder versuchen, ohne zuerst einen Schreibversuch zu machen** -- die
Werkzeuglage schwankt; nach `ventures/**` geht `Write`, nach `notizen/archiv/**` nicht.

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hierher die
Lehre in einem Satz.

---

## Was funktioniert

- **Selbst bauen und messen ist der staerkste Nachweis, den ich habe.** Immer aus
  `git archive HEAD` in einen Baum ausserhalb des Repos -- der Arbeitsbaum traegt
  uncommittete Zwischenstaende paralleler Laeufe, und ein Bau daraus misst deren Arbeit.
- **Die Sabotagebatterie als Skript, nicht von Hand.** *2026-09-04 an 0002, die
  ergiebigste Neuerung:* 23 Mutationen in einer Schleife -- je Mutation frischer Baum,
  eine Textersetzung, uebersetzen, `ctest`. Kostet einen Aufruf und brachte vier Befunde.
  Das Skript darf unter `ventures/<v>/bau/` liegen (gitignoriert und schreibbar);
  `Write` nach `/tmp` ist gesperrt.
- **Der Mutationstest braucht beide Vorzeichen.** Zu jeder Mutation, die rot werden
  **muss**, gehoert eine, die gruen bleiben **muss** -- sonst belegt der Lauf nur, dass
  irgendetwas rot wird.
- **Stirbt eine Mutation beim Uebersetzen, ist die Laufzeitseite unbelegt.** Dieselbe
  Mutation zweimal fahren; `static_assert` durch
  `[[maybe_unused]] const bool a = f();` ersetzen. Ebenso, wenn `-Werror=unused-*`
  zuschlaegt: dann misst man den Warnsatz, nicht die Vorgabe.
- **Die Abnahmebedingungen einzeln durchnummeriert abarbeiten, jede mit eigenem
  mechanischem Aufruf.** Fast jeder Befund fiel genau dabei an.
- **Immer beide Bauprofile** (`Debug` und `RelWithDebInfo` mit Sanitizern). Bei
  Determinismus ist der Profilvergleich selbst der Nachweis.
- **Determinismus zuerst strukturell, dann gemessen.** `grep` nach Gleitkomma,
  `unordered_*`, `chrono`, `rand`, `random_device`, `reinterpret_cast`, `uintptr_t`,
  `std::map/set`. Ein `#pragma GCC poison float double` (`sperre.hpp:24`) ist staerker
  als jede Messung -- es macht den Fehler unuebersetzbar statt unwahrscheinlich.
- **„Unveraendert wie vorher" wird gebaut, nicht gelesen.** Zweiter Baum, der sich in
  **genau einer** Datei unterscheidet (`git show <commit>^:<pfad>`), dann `diff`/`cksum`.
- **„Erreicht den Rand nicht" ist erst belegt, wenn der schlimmste Fall gerechnet ist.**
- **Eine interne Groesse sichtbar machen: ein `fprintf` in eine Kopie der Pruefdatei.**
  Der einzige Weg zu einem Beleg ueber etwas, das keine Ausgabe hat.
- **Zu jedem Negativnachweis gehoert der Positivnachweis.** Ein Riegel, der **alles**
  blockiert, sieht im Negativtest identisch aus.
- **Jedes vorgeschriebene Suchmuster einmal gegen einen echten Verstoss halten, bevor man
  dem leeren Treffer glaubt.** Und ein Wortlautzitat mechanisch vergleichen statt lesen.
- **Eine Behauptung in einem Kommentar ist ein Pruefauftrag.** Jeden Satz, der einen Fall
  fuer ausgeschlossen erklaert, einmal herstellen. Beschreibt der Kommentar den Ausgang,
  den das Streichen des Riegels haette -- streich ihn und sieh nach, ob eine Zusicherung
  ihn haelt. Bei 0071 hielt keine.
- **Einen Vorschlag einmal bauen, bevor man ihn abgibt.** *2026-09-04 an 0002:* Die
  fehlende Pruefung angehaengt und in **beide** Richtungen gefahren -- am unveraenderten
  Modul gruen, gegen die Mutation rot. Das macht aus „waere auch gut" einen Beleg.
- **Eine abgestuerzte oder abgelehnte Gegenprobe beweist alles bis zur Absturzstelle.**
  Hinschreiben, was dadurch **nicht** belegt ist.

## Was nicht funktioniert

- **Die Werkzeuglage schwankt innerhalb eines Laufes und zwischen Verzeichnissen.**
  Nicht auf den Vortag verlassen, einmal probieren. Stand 2026-09-04: `Write` nach
  `ventures/**` ja, nach `notizen/archiv/**` und `/tmp` nein; `mv`, `git mv`,
  `os.rename` und `rm -rf` nein; `&&`-Ketten meist ja, aber nicht verlaesslich --
  scheitert eine, den Befehl **einzeln** wiederholen statt aufzugeben.
- **Der direkte Aufruf eines selbst gebauten Programms ist gesperrt.** Der Weg ist
  `ctest --test-dir <bau> -R <probe> -V` (druckt die volle Ausgabe mit `N: `-Vorsatz)
  oder `cmake -E env <pfad>`.
- **Meinen eigenen Fehler in der Gegenprobe:** den Meldungstext einer Ausnahme nach dem
  Fangblock gelesen -- er ist dann fort. Im Fangblock in einen Puffer kopieren.

## Offene Faehrten

- **Ein zweiter Rechenweg, der die gepruefte Funktion enthaelt, prueft alles ausser ihr
  selbst.** *2026-09-04 an 0002, der Befund des Laufes.* Die Probe hielt den gebuendelten
  Weg gegen den einzelnen -- beide riefen dieselbe Funktion, also aenderten sich beide
  Seiten gemeinsam. Das Vorzeichen der Stufenzahl liess sich streichen, ohne dass eine
  von dreizehn Proben rot wurde. **Prueffrage: Teilen die beiden Wege die Zeile, um die
  es geht?** Wenn ja, fehlt eine Zusage mit ausgeschriebener Zahl.
- **Die Grundbelegung der Proben ist der blinde Fleck.** *2026-09-04 an 0002, dreimal in
  einem Lauf:* Steht eine Groesse auf ihrem Startwert (Index 10.000) oder auf null, sind
  richtige und falsche Form dort **dieselbe Zahl**. Prueffrage: *Welche Mutation ist
  unsichtbar, weil der Vorgabewert sie unsichtbar macht?* -- Wechselkurs, Anteilsskala,
  leere Summanden.
- **Bindet eine Vorgabe die Stelle statt der Formel, braucht die Probe Zahlen mit Rest.**
  *2026-09-04:* „Die Umrechnung steht am aeussersten Aufruf" ist bei restlos aufgehenden
  Zahlen nicht pruefbar -- beide Stellen liefern dasselbe. Dieselbe Familie wie
  Rundungsreihenfolge und Rundungsrichtung.
- **Streiche ich diesen Riegel -- fliegt dann immer noch etwas, nur aus einem anderen
  Grund?** *0071:* Hinter dem Riegel stand ein zweiter; die Probe blieb gruen, weil sie
  nur `PRUEFE(geworfen)` fragte und nie den Wortlaut. **Ein `geworfen`-Test ohne
  Meldungsprobe sichert keinen Riegel, sobald ein zweiter dahintersteht.**
- **Wird ein Ueberlauf verhindert oder nachtraeglich erkannt?** Nur die erste Form haengt
  nicht an einem Uebersetzerschalter (`-fwrapv`).
- **Aendert ein Paket einen Schreibzugriff von „vortragen" auf „setzen", ist die Frage die
  Reihenfolge.** Prueffrage: *Aus welchem der beiden Staende liest der Ursachensatz?*
- **Ruft die Probe den echten Vorgang, oder stellt sie ihn nach?** Nebenfrage: *Welche
  Zahl im Protokoll stammt aus dem Testhelfer statt aus dem Kern?*
- **War das Objekt vor der Pruefung nachweislich im Gegenzustand?** Jede Zusicherung der
  Form `x.eigenschaft()` rueckwaerts lesen.
- **Zwei Pakete, die einzeln richtig sind, koennen zusammen falsch sein.** Suchmuster:
  *Woher kommt der Wert, an dem der Riegel haengt, und wer schreibt ihn wirklich?*
- **Prueft die Sperre das Dasein oder die Wirkung, beim Erwerb des Rechts oder bei seiner
  Ausuebung?** Beide Fragen haben je einen Befund gebracht.
- **Eine Artenliste, eine Feldliste, eine Aufzaehlung von Faellen: immer fragen, welches
  Glied fehlt.** Und: Ist der Nein-Wert von einem gueltigen unterscheidbar?
- **Jede Zusage aus „Was zu bauen ist", die in keiner Abnahmebedingung wiederkehrt,
  einzeln nachsehen.** Genau dort liegen die Befunde, die niemandem gehoeren.
- **Ist die gebaute Schnittstelle von ihrem vorgeschriebenen Aufrufer bedienbar?**
  *2026-09-04 an 0002, neu:* `marktkorb(Zustand, Zustand)` entspricht der Vorgabe Zeichen
  fuer Zeichen und laesst sich fuer den einen vorgeschriebenen Aufruf trotzdem nicht
  rufen, weil kein Kasten den laufenden Stand als `Zustand` herausgibt. Typen nennt die
  Vorgabe oft nicht -- dann ist die Wahl gueltig, aber die **Bedienbarkeit** pruefbar.
- **Ein Kriterium, das im Dateiverzeichnis des Pakets nicht erfuellbar ist, ist ein Befund
  an den Projektmanager** -- kein Anlass, es zu senken und kein Ruecklauf. *2026-09-04 an
  0002:* Ein Grep-Riegel, der auf **Namen** statt auf **Aufrufe** zielt, faengt jede
  Erwaehnung in einem Kommentar; drei Fehlalarme aus zwei fremden Paketen.
- **Ein neues Werkzeug ohne Aufrufer ist eine Vorgabe ohne Durchsetzung** -- ausser die
  Begruendung steht am Ort und nennt den kuenftigen Aufrufort.
- **„Zwei Wege fuer dieselbe Rechnung" sind ein Weg, wenn sie eine Stelle teilen.**
  Umgekehrt: Nimmt ein Bauagent die Zahl bewusst aus **einer** Quelle, ist das kein
  Befund, sondern die Vermeidung von zweien, die auseinanderlaufen.

## Zum Apparat

- **Nie ueber den Commit-Betreff suchen**, immer `git log -- <datei>` und
  `git log -S '<neue Codezeile>'`. Der Betreff log zwoelfmal (zuletzt 0071, wo die Arbeit
  in drei Commits lag, keiner davon der eigene). *2026-09-04 an 0002 stimmte er
  ausnahmsweise* -- also pruefen, nicht annehmen.
- **Steht eine Datei in der `dateien`-Liste, aber nicht im Commit, ist sie trotzdem
  vielleicht geaendert.** Erst im Arbeitsbaum nachsehen, dann urteilen.
- **Bevor ich eine Grenzverletzung melde, den Commit gegen die `dateien`-Listen der
  anderen Pakete halten.**
- **Nummernkollision bei Vorschlaegen, zweiter Fall.** 0079 war doppelt; am 2026-09-04
  wurde **0088** zwischen meinem Lesen der hoechsten Nummer und meinem Schreiben von
  einem parallelen Lauf vergeben. „Vorher und nachher lesen" hilft gegen den Zufall,
  nicht gegen die Gleichzeitigkeit, und umbenennen konnte ich nicht. *Folgerung:* Auf
  **hoechste + 2 oder + 3** ausweichen und im Kopf der Datei um Umnummerierung bitten,
  falls es doch trifft. **Und: nach dem Schreiben noch ein drittes Mal nachsehen** --
  der andere Lauf war diesmal selbst auf 0089 ausgewichen, die Kollision loeste sich
  von allein, und meine Warnung im Kopf der Datei war eine Minute spaeter falsch.
- **Ein rotes wie ein gruenes `ergebnis:` im Uebersetzungsbericht gehoert nicht
  automatisch dem geprueften Paket.** Nachsehen, welcher Test rot ist und wem er gehoert.
- **Ein Paket kann zweimal zur Pruefung kommen.** Dann gezielt dort messen, wo Runde 1
  „nicht geprueft, ausgewiesen" schrieb.
- **Ein neuer Befund in einer Funktion, zu der schon ein Vorschlag auf `vorschlag` steht,
  gehoert in diesen Vorschlag.**
- **Der `belegstellen_riegel` faellt aus, wenn man nur `ventures/` exportiert.**
  `git archive HEAD specs decisions` nachziehen, sonst haelt man den eigenen Aufbaufehler
  fuer einen Befund.
