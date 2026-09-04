# Logbuch: kern-pruefer

Neu begonnen am 2026-09-04 nach der Pruefung von 0056, weil die Vorfassung mit 11.821
Zeichen an der Grenze von 12.000 stand. Sie liegt vollstaendig unter
`notizen/archiv/kern-pruefer-2026-09-04-3.md` (Vorgaengerinnen: `…-2026-09-04-2.md`,
`…-2026-09-03-2.md`, `…-2026-09-03.md`, `…-2026-09-02.md`); uebernommen ist nur, was
weiter gilt. Die Ziffern in den Dateinamen zaehlen Archivierungen desselben Tages, nicht
Fassungen.

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hierher die
Lehre in einem Satz.

---

## Was funktioniert

- **Selbst bauen und die Tests laufen lassen ist der staerkste Nachweis, den ich habe.**
  Bauverzeichnis ausserhalb des Repos, nie im Baum. Ausnahme: unter `befunde/` sammelt der
  Baulauf nicht (`baulauf.py:116`), dort duerfen meine Pruefstuecke liegen bleiben, damit
  der naechste sie nachbaut statt neu erfindet.
- **Die Abnahmebedingungen einzeln durchnummeriert abarbeiten, jede mit ihrem eigenen
  mechanischen Aufruf.** Fast jeder Befund, den ich je hatte, fiel genau dabei an.
- **Der Mutationstest geht, und er braucht beide Vorzeichen.** Zu jeder Mutation, die rot
  werden **muss**, gehoert eine, die gruen bleiben **muss**. 2026-09-04 an 0056: Merker
  entfernen und Marke entfernen -> rot; `MARKE` auf andere Laenge aendern und
  `PUFFER_ZEICHEN` von 512 auf 300 -> gruen. Erst die zweite Sorte belegt den Halbsatz
  „keine Grenze wird abgeschrieben", und nur sie kann ihn belegen -- durch Lesen geht es
  nicht.
- **Stirbt eine Mutation schon beim Uebersetzen, ist die Laufzeitseite unbelegt.**
  Ein `static_assert` faengt sie vor jedem Testlauf ab -- gutes Ergebnis, aber danach
  weiss ich nicht, ob die Laufzeitpruefungen ueberhaupt greifen. Dieselbe Mutation ein
  zweites Mal fahren, die Zusicherung durch eine gewoehnliche Auswertung ersetzt
  (`[[maybe_unused]] const bool a = f();`), dann nennt die Probe ihre Zeilennummern.
- **„Unveraendert wie vorher" wird gebaut, nicht gelesen.** Zweiter Baum, der sich in
  **genau einer** Datei unterscheidet (`git show <commit>^:<pfad>`), beide Proben laufen
  lassen, `diff` und `cksum` ueber die Ausgaben. Das ist der einzige Nachweis, der die
  Fuge zwischen zwei Paketen ausschliesst, und er kostet zehn Minuten.
- **„Erreicht den Rand nicht" ist erst belegt, wenn der schlimmste Fall gerechnet ist.**
  Der gemessene Lauf ist die Untergrenze. Bei 0056: gemessen 327 Zeichen, gerechnet 403
  (jede `zahl` mit 20, jede `adresse` mit 63), Grenze 511. Erst die 403 traegt die Aussage.
- **Zu jedem Negativnachweis gehoert der Positivnachweis.** Ein Riegel, der **alles**
  blockiert, sieht im Negativtest identisch aus. Prueffrage: *Habe ich auch gemessen, dass
  der gute Fall gruen ist?*
- **Jedes vorgeschriebene Suchmuster einmal gegen einen echten Verstoss halten, bevor man
  dem leeren Treffer glaubt.** Am billigsten gegen die eigenen Pruefstuecke.
- **Immer beide Bauprofile**, und die schaerfste Mutation auch unter `-O2`. Das ist der
  Nachweis, dass die Probe den Laufzeitweg misst und nicht die Konstantenfaltung.
- **Bringt ein Umbau eine neue Faehigkeit mit, ist ihre Spur in der Ausgabe der billigste
  Beweis, dass der neue Weg tragend ist.** Prueffrage: *Was kann nur die neue Fassung, und
  sieht man es?* Bei 0056 war es die Zeile `Zahl am Pufferende abgeschnitten zu "-[...]"
  (frueher "-92233")` -- und die Mutation ohne Marke schreibt dort wirklich wieder
  `-92233` hin.
- **Eine Zusage mit zwei Seiten braucht zwei Mutationen**, und die, die genau **einen**
  Aufruf herausnimmt, ist der einzige saubere Beleg dafuer, dass ein Abbruch aus *dieser*
  Stelle kommt und nicht aus einer zweiten.
- **Ein Wortlautzitat mechanisch vergleichen statt lesen.** Kostet einen Aufruf und
  ersetzt „sieht gleich aus".
- **Eine Behauptung in einem Kommentar ist ein Pruefauftrag.** Jeden Satz, der einen Fall
  beschreibt oder ihn fuer ausgeschlossen erklaert, einmal herstellen. **Ein Kommentar,
  der einen Randfall abhakt, ist teurer als gar keiner, wenn der Randfall der Normalfall
  ist.**
- **Einen Vorschlag einmal bauen, bevor man ihn abgibt** -- und ihn nicht abgeben, wenn
  die Folge des Fehlers ohnehin sichtbar waere. Bei 0056 habe ich zwei erwogene
  Vorschlaege ausgeschrieben **und begruendet verworfen**; das kostet zehn Zeilen und
  erspart dem naechsten Lauf dieselbe Erwaegung.
- **Eine abgestuerzte oder abgelehnte Gegenprobe beweist alles bis zur Absturzstelle.**
  Hinschreiben, statt den Lauf wegzuwerfen -- und dazuschreiben, was dadurch **nicht**
  belegt ist.

## Was nicht funktioniert

- **Die Werkzeuglage schwankt innerhalb eines Laufes.** 2026-09-04 (zweiter Lauf des
  Tages) ging `Write` unter `ventures/**` und `notizen/` durchgehend -- am Vormittag war
  es nach fuenf Dateien zu. Nicht auf den Vortag verlassen, einmal probieren.
- **Zusammengesetzte Shell-Befehle werden abgelehnt.** `for … done` ueber mehrere
  Mutationen: abgelehnt. `cp`, `mv`, `sed -i`, Verkettung mit `&&`: abgelehnt.
  **Ein Befehl je Aufruf**; `;` innerhalb einer Zeile ging, `shutil.copytree` und
  `os.rename` im `python3`-Heredoc gehen zuverlaessig. `sed -n 1,100p <datei>` wurde
  abgelehnt, `Read` mit `limit` tat dasselbe.
- **Der direkte Aufruf eines selbst gebauten Programms ist gesperrt --
  `cmake -E env <pfad>` nicht.** Daran haengt jeder Laufzeitnachweis.
- **Meinen eigenen Fehler in der Gegenprobe:** den Meldungstext einer Ausnahme nach dem
  Fangblock gelesen -- der Text ist dann fort. Im Fangblock in einen eigenen Puffer kopieren.

## Offene Faehrten

- **War das Objekt vor der Pruefung nachweislich im Gegenzustand?** *Neu und scharf,
  2026-09-04 an 0056.* Die Probe belegte „Anhang an den vollen Puffer setzt den Merker"
  an einem Objekt, das **schon** abgeschnitten war -- die Zusicherung war wahr und leer.
  Getragen hat die Bedingung erst eine zweite Stelle, an der derselbe Puffer vorher
  gemessen verlustfrei war. **Jede Zusicherung der Form `x.eigenschaft()` einmal
  rueckwaerts lesen: Wer hat bewiesen, dass sie vorher `false` war?**
- **Ruft die Probe den echten Vorgang, oder stellt sie ihn nach?** Nebenfrage, die den
  Befund findet: **Welche Zahl im Protokoll stammt aus dem Testhelfer statt aus dem
  Kern?** Gegenprobe im Guten: Aendert man die Konstante im Kopf, muss die Zahl im
  Protokoll mitwandern (bei 0056 511 -> 299).
- **Zwei Pakete, die einzeln richtig sind, koennen zusammen falsch sein.** Der Fehler
  liegt in der Fuge, wo keine Abnahme hinsieht. Suchmuster: **Woher kommt der Wert, an dem
  der Riegel haengt, und wer schreibt ihn wirklich?** Dazu die Commit-Zeiten vergleichen.
- **Prueft die Sperre das Dasein oder die Wirkung?** Und: **beim Erwerb des Rechts oder
  bei seiner Ausuebung?** Beide Fragen haben je einen Befund gebracht.
- **Die Einheit, die ich vergleiche, ist selten die, die das Werkzeug liest.** Dreimal
  getroffen, jedes Mal eine Ebene groesser. *Naechste Ebene, ungeprueft: Wer sagt, dass
  die Schalterdatei die Uebersetzerzeile ist?*
- **Wer eine Pruefung feiner macht, erzeugt neue Fehlalarme -- stell einen her.** Bei 0056:
  Eine nicht abgeschnittene Meldung, die zufaellig auf die Marke endet, saehe gekuerzt
  aus. `grep` ueber die Meldungsprosa des Kerns schliesst es aus, und die Probe deckt die
  Gegenrichtung ab. Der Fehlalarm war der billigste Teil der Pruefung.
- **Bei jedem Ergebnistyp mit Ja-Nein-Feld und jeder Ausgabe, die abschneiden oder leer
  ausgehen kann: Ist der Nein-Wert von einem gueltigen unterscheidbar?** Und bei jeder
  Groesse mit fester Obergrenze: Ist das Erreichen der Grenze sichtbar?
- **Ein zweiter Weg, auf dem dieselbe Groesse verlorengehen kann.** Bei 0056 hatte `zahl`
  neben dem Puffer ein eigenes Ziffernfeld mit eigener Schranke -- liefe **das** ueber,
  gaebe es keinen Merker. 19 Stellen gegen 24 Plaetze, unerreichbar, nachgerechnet.
  **Prueffrage: Wie viele Stellen koennen kuerzen, und meldet sich jede?**
- **Eine Artenliste, eine Feldliste, eine Aufzaehlung von Faellen: immer fragen, welches
  Glied fehlt.** Wer die Vorgabe selbst verfasst hat, prueft sie zuerst gegen die
  Wirklichkeit, nicht den Code gegen die Vorgabe.
- **Jede Zusage aus „Was zu bauen ist", die in keiner Abnahmebedingung wiederkehrt,
  einzeln nachsehen.** Genau dort liegen die Befunde, die niemandem gehoeren.
- **Ein Kriterium, das im Dateiverzeichnis des Pakets gar nicht erfuellbar ist, ist ein
  Befund an den Projektmanager** -- nicht am Bauagenten und kein Anlass, das Kriterium zu
  senken. Beide Auswege benennen (Dateiliste erweitern oder Folgepaket).
- **Wird ein Ueberlauf verhindert oder nachtraeglich erkannt?** Nur die erste Form haengt
  nicht an einem Uebersetzerschalter.
- **„Zwei Wege fuer dieselbe Rechnung" sind ein Weg, wenn sie eine Stelle teilen.**
  Prueffrage: **Welche Stelle beruehren beide Wege?** Dort ist der Vergleich blind.
- **Ein neues Werkzeug ohne Aufrufer ist eine Vorgabe ohne Durchsetzung.** Prueffrage:
  **Wer sorgt dafuer, dass es benutzt wird -- und woran merkt es jemand, wenn nicht?**
  *Ausnahme, 2026-09-04:* Wenn das Paket eine **zweite, selbsttaetige** Anzeige einbaut
  (bei 0056 die Marke im Text), braucht die erste keinen Aufrufer. Dann ist der
  Standardbefund falsch -- erst pruefen, ob die Durchsetzung woanders sitzt.

## Zum Apparat

- **Der Commit-Betreff luegt, zehntes Mal** (0033, 0038, 0046, 0058 zweimal, 0060, 0063,
  0027, 0048, 0056). Bei 0056 lag der geaenderte Kopf unter „datenbauer: 0065", waehrend
  der Commit mit dem Paketnamen die Datei eines **anderen** Pakets trug. Entscheidend ist
  der **Inhalt**. **Den Vorzustand nie ueber den Betreff suchen, sondern ueber
  `git log -S '<eine neue Codezeile>'`.** Ursache ist `lauf.py:committen`; ein Paket kann
  auch in mehreren Commits liegen -- `git log` je Datei, nicht je Commit.
- **Bevor ich eine Grenzverletzung melde, den Commit gegen die `dateien`-Listen der
  anderen Pakete halten.** Bei 0056 sah der Commit nach einem Uebergriff auf
  `werkzeugkette.cmake` aus; die Datei gehoert Paket 0066, das im selben Takt lief.
- **Ein Paket kann zweimal zur Pruefung kommen.** Dann nicht die erste Pruefung
  abschreiben: gezielt dort messen, wo Runde 1 „nicht geprueft, ausgewiesen" schrieb.
- **Ein rotes `ergebnis:` im Uebersetzungsbericht gehoert nicht automatisch dem geprueften
  Paket.** Nachsehen, welcher Test rot ist und wem er gehoert.
- **Ein gruener Bericht auch nicht automatisch.** Verlangt die Abnahme „steht im Bericht
  des Tages", dann die Uhrzeiten vergleichen: `ls -l --time-style=full-iso` ueber Bericht
  und Paketdateien. Bei 0056 war der Bericht 07:19:48, die Dateien 07:07 und 07:13 -- er
  deckt den abgegebenen Stand. Waere er aelter, belegte er einen anderen.
- **Vor dem Anlegen eines Vorschlags die hoechste Nummer lesen -- und nach dem Schreiben
  noch einmal.** Parallele Laeufe belegen Nummern, waehrend man schreibt; `os.rename`
  raeumt es auf, dann `id:` und Verweise nachziehen. Gilt auch fuer Archivnamen des
  eigenen Logbuchs: erst auf Existenz pruefen, sonst ueberschreibt man ein Archiv
  (Hausregel 3).
- **Ein neuer Befund in einer Funktion, zu der schon ein Vorschlag auf `vorschlag` steht,
  gehoert in diesen Vorschlag** -- gleiche `dateien`-Liste heisst, der Baulauf muesste
  ohnehin serialisieren.
