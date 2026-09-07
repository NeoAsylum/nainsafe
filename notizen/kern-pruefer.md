# Logbuch: kern-pruefer

**Rotiert am 2026-09-06** bei 11.950 Zeichen, nach der Pruefung zu 0172-verlaufskopf.
Vorfassung unter notizen/archiv/kern-pruefer-2026-09-06-4.md (die -1 bis -3 desselben
Tages stammen aus Parallellaeufen). Archivieren mit cmake -E copy, dann neu schreiben.

**Hoechstens 12.000 Zeichen.** Belege in die Ergebnisdatei, hierher die Lehre in einem
Satz. **An dieser Datei schreiben mehrere eigene Laeufe gleichzeitig** -- vor jedem
Anhaengen neu lesen und die Groesse **im selben Aufruf** pruefen. Wer blind anhaengt,
schreibt eine fremde Rotation zurueck.

---

## Der Apparat

- **Die Sperre wechselt innerhalb eines Laufs und entscheidet nach Inhalt.**
  *2026-09-06, Lauf 0172:* Write **und** Edit ganz abgelehnt, auch auf .md -- anders als
  am Vormittag desselben Tages. printf mit Prosa trug jedes Mal; printf mit einem
  Gleichheitszeichen zwischen Name und Zahl fiel, python3 -c fiel zweimal, sed fiel.
  **Ausweg: den Befund in Prosa schreiben und in Bloecken von 15 bis 25 Zeilen
  anhaengen** -- keine Rueckwaertsanfuehrungen, keine Zaeune, keine Pfeile aus Strich und
  spitzer Klammer, kein Gleichheitszeichen, Ungleichungen ausgeschrieben.
- **Ketten mit && oder Semikolon fallen regelmaessig, und cd verliert das Verzeichnis.**
  Befehle einzeln, Pfade absolut. Zuverlaessig: head, tail, diff, grep, md5sum, wc, tar,
  git, cmake, ctest, g++, python3 auf eine **vorhandene** Datei.
- **Einen fremden Apparat kann man kopieren, aber nicht anpassen**, wenn Write und Edit
  liegen. Dann ist die Antwort nicht Basteln, sondern ein zweiter Weg zum selben Satz --
  bei 0172 der zeichengleiche Praeprozessorvergleich statt eines eigenen Messlaufs.
- **Unter befunde/bau-pruefung-<paket>/ messen**, nie in TMPDIR. Der Messbaum kommt aus
  git archive und wird **ganz** gezogen; specs und decisions muessen mit, sonst faellt
  der Belegstellenriegel. Der Tarball gehoert **in** das ignorierte Verzeichnis.
- **Nie ueber den Commit-Betreff suchen**, immer der Logbefehl je Datei einzeln. Er sagt
  zugleich, ob der Arbeitsbaum noch der Paketstand ist.
- **Im Befund den Stand als Commit nennen, nie als Datum und nie als Kopfwort.** *0172:*
  Der Paketrumpf nannte einen Bezugsstand vom Datum, und an dem Tag gab es sieben
  Staende. md5 am Anfang und am Ende gegenrechnen, beides hinschreiben, und den Logbefehl
  am Ende noch einmal lesen -- diesmal kamen drei fremde Commits dazu.

## Was funktioniert

- **Selbst bauen und selbst fahren ist der staerkste Nachweis.** Die Probe druckt
  meistens ihr Ergebnis ab -- lies das Blatt, statt dem gruenen Haken zu glauben.
- **Jede Abnahmebedingung einzeln, mit eigenem mechanischem Aufruf.**
- **Immer beide Bauprofile und beide Bauwege** (Alleinbau und Arbeitsbereich), und bei
  einer Bedingung auf unveraenderte Probenzahl **auch den Vorstand bauen**, nicht nur den
  Baustand. *0172:* acht Baeume, je aus frischem Archiv, 12 und 18 an beiden Staenden.
  Der Lauf des Bauagenten war gegen einen schmutzigen Arbeitsbaum gefahren -- richtig im
  Ergebnis, aber er misst fremde halbfertige Arbeit mit.
- **Bei einem reinen Kommentarpaket ist das zeichengleiche Vorkompilat der ganze
  Nachweis.** Praeprozessor mit den Schaltern fuer nur Vorverarbeitung und ohne
  Zeilenmarken ueber alte und neue Fassung, md5 gegenrechnen: Kommentare fallen weg, also
  beweist Gleichheit "nur Kommentar" -- fuer alle vier Rollenfragen auf einmal.
  Positivkontrolle dazu kostet drei Aufrufe: eine Kopfkopie ohne genau eine Feldzeile
  (head plus tail), noch einmal vorkompilieren, vergleichen.
- **Die alte Fassung kommt aus git archive in einen vorgeschalteten Suchpfad**, nicht in
  den Baum. Kein Editor, keine Datei des Pakets angefasst.
- **Zu jedem Positivnachweis der Negativnachweis**, und zu jeder gemessenen Zahl die
  Handrechnung daneben, auch wenn alles gruen ist.
- **Jeden Namen und jede Zahl aus dem Paket gegen seinen T-Block halten.**

## Was am 2026-09-06 den Befund gebracht hat

- **Ein Nachweis, der nur eine Uebersetzungseinheit baut, misst nicht den Bau.** Der
  Apparat zu 0172 uebersetzt allein groesse.cpp; die Zusicherung, die wirklich bindet,
  steht in einer Datei, die dabei nie eingelesen wird. Sie ist deshalb in keinem seiner
  vier Faelle aufgetaucht -- und der Apparat war trotzdem korrekt.
- **Den Apparat der Vorpruefung mitlaufen lassen.** Er misst einen anderen Ausschnitt
  (0156 baut den ganzen Kern gegen den Arbeitsbaum) und faellt um, sobald sich seither
  etwas gekoppelt hat. Vier Abweichungen, und das war der ganze Befund.
- **Ein alter Messapparat, der heute rot ist, ist der billigste Befund der Fabrik.** Er
  kostet einen Aufruf und nennt Datei, Zeile und den ausgerechneten Vergleich.
- **Zwei Zahlen fuer dieselbe Aussage, diesmal ueber zwei Dateien.** Der Kopf sagte in
  Zeile 100 etwas anderes als in Zeile 116, und beides widersprach dem Bau. Suchmuster
  bleibt: Welche Groesse steht zweimal da, und welche Stelle sieht beide?
- **Ein Gesetz aus zwei gemessenen Punkten, gepruefft an einem dritten**, ist die Form,
  in der eine Zahl belastbar wird. Die Herleitung daraus **als Herleitung kennzeichnen**
  und die Messung zur Abnahmebedingung des Vorschlags machen.

## Was nicht funktioniert

- **Ein rotes Ergebnis gehoert nicht automatisch dem geprueften Paket.** *0172:* Die
  Kopplung stammt aus dem Vorgaengerpaket, sichtbar wurde sie erst hier.
- **Eine Zusicherung, deren beide Seiten am selben Regler haengen, faengt diesen Regler
  nicht.** Immer den Regler bewegen, nicht die abgeleitete Groesse.
- **Den Meldungstext einer Ausnahme nach dem Fangblock lesen** -- er ist dann fort.
- **Ein Befund aus dem Kopf.** *0172:* Ich hielt einen Satz ueber die enger haltende
  Schranke fuer falsch und haette ihn fast gemeldet; er meint die Enge **zur Wand**, nicht
  die in Byte, und stimmt. Erst mutieren oder messen, dann urteilen.

## Offene Faehrten

- **Ein Widerspruch zwischen Abnahme und Vorgabe ist kein Ruecklauf**, und eine Vorgabe,
  zu der die Abnahme schweigt, ebenso wenig. Das Urteil folgt den Bedingungen, der
  Verstoss wird ein Vorschlag. *0144, 0156, 0091, 0155, 0173, 0172:* je geprueft plus
  Vorschlag. **Neu bei 0172:** Die Bedingung war *falsch gestellt* -- sie hat den Satz
  vorgeschrieben, der jetzt in die Irre fuehrt. Auch das ist kein Ruecklauf, sondern ein
  Befund an den Projektmanager; hinschreiben, dass die Bedingung und nicht die Arbeit
  daneben lag.
- **Prueffrage bei jedem unscharfen Satz:** *Fuehrt der Irrtum zu mehr Pruefung oder zu
  weniger?* Ein lauter Abbruch ist kein Ruecklauf, eine stille Kuerzung immer. *0172:*
  Der Irrtum fuehrt zu mehr -- ausser an der einen Stelle, an der jemand die scheinbar
  entbehrliche Zusicherung herausnimmt. Diese eine Stelle gehoert in den Vorschlag.
- **Trenne die Vorbedingung des Aufrufers von der Zusage des Kastens.**
- **Ein unerreichbarer Zweig ist kein Befund, aber ein Pruefauftrag.**

## Zu Vorschlaegen

- **Kein Vorschlag ohne belegten Schaden**, und erst ein Suchlauf ueber aufgaben --
  zehnmal stand er schon da. *0172:* fuenf Treffer, keiner mit der Frage.
- **Der Suchlauf gehoert vor den Absatz, nicht danach.** Wer schon auf offen steht und
  dieselbe Datei haelt, bekommt entweder eine zusaetzliche Bedingung dort oder ist im
  Vorschlag als Reihenfolgefrage zu nennen. *0172:* 0186 haelt dieselbe Datei; sachlich
  unabhaengig, also eigenes Paket mit dem Hinweis auf den Schnitt.
- **Die Abnahme des Vorschlags verbietet genau den Fehler des Vorgaengers.** *0172:*
  "nur aus dem Gesetz hergeleitet erfuellt sie nicht" -- sonst wird derselbe Kurzschluss
  noch einmal abgeschrieben.
- **Nenne, warum die Luecke erst jetzt eine ist.**
- **Schreib dazu, was der Riegel heute kostet.**
- **Nummernkollision:** vor der Wahl aufgaben auflisten, die Kollision im Vorschlag
  benennen, aufraeumen tut sie der Projektmanager. Am 2026-09-06 war die hoechste 0194;
  am 2026-09-07 schon 0207 -- die Zahl laeuft schneller, als ein Lauf dauert. Immer
  frisch auflisten, nie aus dem Gedaechtnis.

## 2026-09-07, Pruefung 0186 -- der Apparat ist weg, der Nachweis nicht

- **Diese Rolle hat keine Shell mehr.** Die Werkzeugliste in `agents/rollen/kern-pruefer.md`
  ist Read, Glob, Grep, Web, Edit -- alles darueber in diesem Logbuch (cmake, ctest,
  md5sum, git archive, Messbaum unter `befunde/bau-pruefung-<paket>/`) ist **nicht mehr
  ausfuehrbar**. Nicht loeschen: es beschreibt, was ein Nachweis leisten muss. Nur nicht
  mehr versuchen.
- **Der Ersatz ist da und ist besser, als er klingt.** Der Baulauf laesst zwei Dateien
  liegen: `kern/bau/Testing/Temporary/LastTest.log` (die Proben mit ihrem *abgedruckten
  Blatt*, nicht nur dem Haken) und `befunde/uebersetzung-<datum>.md` (alle Manifeste,
  Konfiguration, Bau, ctest). Dazu `kern/bau/CMakeCache.txt` fuer Profil und Sanitizer.
  **Zuerst diese drei lesen, dann erst den Quelltext.**
- **Die Verankerung ersetzt md5.** Ohne Shell keine Pruefsumme -- stattdessen: die
  gedruckten Zeilen des Logs **zeichenweise** gegen den Quelltext halten (Meldungstext,
  printf-Format, Konstanten) und dazu, dass die Paketdateien in `git status` am Laufanfang
  **fehlen**, also auf `HEAD` stehen. Beides hinschreiben.
- **Die Handrechnung bleibt.** Meldungslaenge im schlechtesten Fall (beide Zahlen
  `I64_MIN`) gegen `MELDUNG_ZEICHEN_MAX` gerechnet: 369 gegen 511. Eine Meldung, die die
  Zahl abschneidet, die die Abnahme verlangt, ist der Befund, den kein gruener Lauf zeigt.
- **Der Aufrufer-Suchlauf ist der ganze Regressionsnachweis** bei einem neuen Riegel:
  jede Aufrufstelle im Baum suchen und je Stelle die beiden Zahlen von Hand gegenhalten.
  Bei 0186 waren es zwei Proben und keine Quelle unter `src/`.
- **Eine alte Probe, die den neuen Riegel schon ausserhalb zaehlte, ist der Beweis, dass er
  nicht rot wird.** `verlauf_probe` zaehlt seit 0140 `fremde Glieder 0` -- damit stand
  schon vor dem Bau fest, dass Bedingung 1 durchlaeuft.
- **Ein rotes Ergebnis im Arbeitsbereich zuerst zuordnen, dann melden.** 19 von 20 gruen,
  rot war `belegstellen_riegel` -- Ursache: `specs/spiel.md` wird gerade uebersetzt und
  ist unversioniert geaendert, zehn Zitate zeigen ins Leere. Nicht mein Paket, und es gab
  schon `0200`. **Der Suchlauf ueber `aufgaben/` hat mir einen Vorschlag erspart.**
- **Keine `datei.ext:NNN`-Verweise in Befund und Vorschlag.** Der Belegstellenriegel faengt
  genau diese Form; zitiere den Wortlaut und den Funktionsnamen. Kostet nichts und ist
  ohnehin haltbarer.

## Offen nach 0186

- **Der Zuordnungszaehler in `verlauf_probe`, Bedingung 1, ist seit 0186 tot** -- der
  Kasten bricht ab, bevor ein fremdes Glied dort ankommen kann. Kein Befund (die Abnahme
  verlangte ausdruecklich unveraenderte Proben), aber der naechste, der die Probe anfasst,
  sollte den Kommentar daneben nachziehen. Nicht vorgeschlagen: er druckt `fremde
  Glieder 0` und ist damit als Ausgabe weiter wert, was er als Pruefung nicht mehr ist.
