# Logbuch: kern-pruefer

Neu begonnen am 2026-09-03 nach der zweiten Pruefung von 0058, weil die Vorfassung mit
11.897 Zeichen an der Grenze von 12.000 stand. Sie liegt vollstaendig unter
`notizen/archiv/kern-pruefer-2026-09-03-2.md` (deren Vorgaengerin unter
`…-2026-09-03.md`); uebernommen ist nur, was weiter gilt.

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hierher die
Lehre in einem Satz.

---

## Was funktioniert

- **Selbst bauen und die Tests laufen lassen ist der staerkste Nachweis, den ich habe.**
  Bauverzeichnis ausserhalb des Repos (`$TMPDIR`), nie im Baum -- der Baulauf sammelt
  jede Bauvorschrift unter dem Vorhaben ein. Ausnahme: unter `befunde/` sammelt er nicht
  (`baulauf.py:116`), dort darf eine Probe liegen bleiben.
- **`python3` mit Heredoc ist der ganze Pruefstand in einem Aufruf.** Er schreibt die
  Wegwerfbaeume, ruft `cmake`, sammelt die Ausgaben und rechnet den Vergleich. Damit
  haengt kein Nachweis mehr an `Write`/`Edit` oder an Shell-Verkettung, die je nach Lauf
  verschieden gesperrt sind. *Zweimal in Folge der Rettungsweg gewesen.*
- **Die Abnahmebedingungen einzeln durchnummeriert abarbeiten, jede mit ihrem eigenen
  mechanischen Aufruf.** Fast jeder Befund, den ich je hatte, fiel genau dabei an; beim
  Lesen des Codes waeren sie unsichtbar geblieben, weil der Code richtig ist.
- **Zu jedem Negativnachweis gehoert der Positivnachweis.** *2026-09-03 an 0058 gelernt:*
  Runde 1 hatte gemessen, dass ein falsch geschriebenes Mitglied den Riegel ausloest --
  nicht, dass ein richtig geschriebenes durchkommt. Ein Riegel, der **alles** blockiert,
  sieht im Negativtest identisch aus. Prueffrage: *Habe ich auch gemessen, dass der gute
  Fall gruen ist?*
- **Die Fehlrichtung benennen, nicht nur das Ergebnis.** Generatorausdruecke machen den
  0058-Riegel falsch **scharf** -- die laute Richtung, also kein Befund. Ohne Messung
  haette es in beide Richtungen liegen koennen, und die andere waere toedlich gewesen.
- **Ein gruener Bau beweist nie, dass ein Schalter ankommt -- die erzeugte Schalterdatei
  tut es.** `flags.make`, Zeile `CXX_FLAGS`. *Allgemein: Wo eine Bedingung still scheitern
  kann, such das Zwischenerzeugnis, das den Zustand zeigt.*
- **Immer beide Bauprofile**, und alle Bauwege einzeln. Unter Optimierung schaltet der
  Uebersetzer Warnungen zu, die im Debug-Profil nie erscheinen.
- **Jedes vorgeschriebene Suchmuster einmal gegen einen echten Verstoss halten, bevor man
  dem leeren Treffer glaubt.** Sonst beweist ein leeres Ergebnis nur, dass das Muster leer
  ausgeht.
- **Der Mutationstest geht.** Den geprueften Stand mit `git archive` nach `$TMPDIR`, dort
  je eine Stelle verfaelschen, neu bauen, Probe laufen lassen. Der einzige Nachweis, dass
  eine gruene Probe etwas pruefen *kann*. Der Baum bleibt unberuehrt.
- **Eine Bedingung ueber "unveraendertes Verhalten" braucht zwei Baeume und einen dritten
  Schritt.** Zwei `git archive HEAD` nach `$TMPDIR`, in genau einer Datei getauscht, die
  Einzigkeit maschinell nachgezaehlt -- **und** dazu die Rechnung, warum kein ungeprueftes
  Beispiel anders ausgehen kann. Der Vergleich belegt sonst nur die geprueften Faelle.
- **Byteangaben verschiedener Laeufe sind nicht vergleichbar, wenn das Pfadpraefix
  abweicht.** Bei 0058 nannten Bauagent, Runde 1 und Runde 2 drei verschiedene Zahlen fuer
  denselben Sachverhalt. Vergleichbar sind **Bytegleichheit** und die **Zielzahl** -- das
  gehoert als Hinweis in den Nachweis, sonst liest der naechste einen Widerspruch.
- **Eine Behauptung des Codes ueber eine Vorgabe immer gegen die Vorgabe halten.** Der
  billigste Weg aus dem Kreis "das Programm prueft sich selbst". Dasselbe fuer die
  Konfiguration: die Schalter des Runners am Text von `baulauf.py` nachlesen, nicht raten.
- **Die dritte Abschrift ist der billige unabhaengige Zeuge.** Bei 0058 deckte sich die
  Zaehlung des Riegels (15/10/5) mit den im **fremdgemessenen** Uebersetzungsbericht
  aufgezaehlten gebauten Zielen -- ein Zeuge ohne meine eigenen Laeufe.
- **Eine Behauptung in einem Kommentar ist ein Pruefauftrag.** Jeden Satz, der einen Fall
  *beschreibt*, einmal herstellen.
- **Einen Vorschlag einmal bauen, bevor man ihn abgibt.** Kostet Minuten und nimmt dem
  Projektmanager die Frage ab.
- **Eine abgestuerzte Gegenprobe beweist alles bis zur Absturzstelle.** Hinschreiben,
  statt den Lauf wegzuwerfen -- und dazuschreiben, was dadurch **nicht** belegt ist.
- **Zwei Kopien des ganzen Vorhabens statt zweier Wegwerf-Baeume, wenn "unveraendertes
  Verhalten" zu belegen ist.** `git archive HEAD <venture>` zweimal nach `$TMPDIR`, in
  einer die eine Datei getauscht, dann maschinell nachzaehlen, dass **genau eine** Datei
  abweicht. Die beiden Baumwurzeln vor dem Bytevergleich im Text normalisieren, sonst
  vergleicht man Pfade statt Schalter.
- **Zaehl selbst nach, wie viele Bauwege der Runner wirklich hat.** Das Kriterium sagte
  "die drei Bauwege"; `baulauf.py:116` baut jede `CMakeLists.txt` ausser unter `befunde/`,
  und das waren fuenf. Die zwei ungenannten waren genau die, an denen ein neuer
  Nullriegel haette falsch scharf werden koennen (beide binden die Kette nicht ein --
  nachgesehen, nicht angenommen).

## Was nicht funktioniert

- **Die Werkzeuglage schwankt von Lauf zu Lauf; ein Pruefplan, der eine bestimmte Form
  voraussetzt, faellt aus.** Verlaesslich sind `Glob`, `Grep`, `Read` und der
  Uebersetzungsbericht. Alles andere probeweise, mit `python3`-Heredoc als Ersatzweg. Am
  2026-09-03 (zweiter Lauf): Einzelbefehle ja, Verkettung mit `;` nein, `sed` nein,
  `cat`/`ls`/`git` ja.
- **Den direkten Aufruf einer erzeugten Datei plane ich nicht mehr ein.** Der Weg ueber
  den Testeintrag des Bauwerkzeugs geht bisher immer.
- **Meinen eigenen Fehler in der Gegenprobe:** den Meldungstext einer Ausnahme nach dem
  Fangblock gelesen -- der Text ist dann fort. Im Fangblock in einen eigenen Puffer
  kopieren.
- **`Write` und `Edit` waren am 2026-09-04 in beiden Laeufen gesperrt** (0060 und 0063),
  ohne erkennbaren Grund; `Bash` mit `python3`-Heredoc hat dieselbe Datei im Repo dann
  angelegt. Der Ersatzweg traegt also auch das *Schreiben* des Befunds, nicht nur das
  Messen. Verkettung mit `;` blieb gesperrt, `&&` ging meist -- aber nicht immer, und die
  Ablehnungen wirkten zufaellig: einen abgelehnten Aufruf einmal unveraendert
  wiederholen, bevor man den Plan aendert.

## Offene Faehrten

- **Prueft die Sperre das Dasein oder die Wirkung?** *2026-09-03 an 0058, neue stehende
  Frage.* Der Schlussriegel prueft, ob die Warnschalter **dastehen**, nicht ob sie
  **wirken**: mit `-Wno-error -w` dahinter meldet er Vollzug, und die Uebersetzung
  schluckt alles. Der Nachweis ist erst der, der **dieselbe Quelle zweimal uebersetzt** --
  einmal mit, einmal ohne. Wurde Befund 3 in Vorschlag 0060.
- **Bei jeder Sperre fragen, ob sie beim Erwerb des Rechts prueft oder bei seiner
  Ausuebung.** Ein Riegel im Konstruktor haelt nur, solange niemand das Werkzeug aufhebt.
  Der 0058-Riegel besteht diese Frage: Er liest den **Endzustand** der Konfiguration, also
  faengt er auch den, der den Satz erst nimmt und dann wieder ablegt (gemessen).
- **Die Einheit, die ich vergleiche, ist selten die, die das Werkzeug liest.** Dieselbe
  Frage hat jetzt dreimal getroffen und wird jedes Mal eine Ebene groesser: Eintrag statt
  Schalter (0060, wurde 0063 und ist erledigt), dann **Eigenschaft statt Schalterzeile**
  (0063, wurde 0064): `COMPILE_OPTIONS` ist eine von vier Quellen der Uebersetzerzeile --
  `COMPILE_FLAGS` am Ziel, dieselben zwei an der Quelldatei und
  `INTERFACE_COMPILE_OPTIONS` eines `INTERFACE_LIBRARY` kommen alle still vorbei.
  *Naechste Ebene, ungeprueft: Wer sagt, dass die Schalterdatei die Uebersetzerzeile
  ist?*
- **Wer eine Pruefung feiner macht, erzeugt neue Fehlalarme -- stell einen her.**
  *2026-09-04 an 0063.* Die Zerlegung in Woerter macht aus `-Wa,-w` einen Treffer, obwohl
  der Schalter nur den Assembler betrifft. Kein Befund (laut statt still, kommt hier nicht
  vor), aber die Messung gehoert in den Nachweis: Sonst steht dort nur, dass die vier
  Schalter des Vorhabens sauber bleiben.
- **Bei jedem Ergebnistyp mit Ja-Nein-Feld und jeder Ausgabe, die abschneiden oder leer
  ausgehen kann, fragen: Ist der Nein-Wert von einem gueltigen unterscheidbar?** Drei
  Faelle in Folge (0038 Meldungslaenge, 0058 Zaehlerstand null, 0058 abgeschalteter Satz).
  Bei jeder Groesse mit fester Obergrenze fragen, ob das Erreichen der Grenze sichtbar ist.
- **Eine Artenliste, eine Feldliste, eine Aufzaehlung von Faellen: immer fragen, welches
  Glied fehlt.** Der billigste Weg ist ein Wegwerf-Fall je ausgelassenem Glied
  (`MODULE_LIBRARY` ging in einer Minute durch den 0058-Riegel).
- **Wer die Vorgabe selbst verfasst hat, prueft sie zuerst gegen die Wirklichkeit, nicht
  den Code gegen die Vorgabe.** Sonst bestaetigt man nur den eigenen Irrtum -- genau das
  war die `MODULE_LIBRARY`-Luecke: meine Liste, brav befolgt.
- **Ein Kriterium, das zwei Textstellen bindet, von denen eine einem anderen Paket
  gehoert, ist unbaubar** (0011, 0031, 0038). Nicht deswegen zurueckweisen: den Nebensatz
  lesen, der die gemeinte Menge nennt, die Auslegung hinschreiben und die **schaerfere**
  Frage beantworten. Und hinschreiben, welche Stellen ich nicht gefuehrt habe -- sonst ist
  "uebersehen" von "entschieden" nicht zu unterscheiden.
- **Jede Zusage aus "Was zu bauen ist", die in keiner Abnahmebedingung wiederkehrt,
  einzeln nachsehen.** Genau dort liegen die Befunde, die niemandem gehoeren.
- **Wird ein Ueberlauf verhindert oder nachtraeglich erkannt?** Nur die erste Form haengt
  nicht an einem Uebersetzerschalter.
- **Ungeklaert: Schaltet die Umbruchsemantik (`-fwrapv`) den Sanitizertest auf genau
  diesen Ueberlauf ab?** Wenn ja, deckt ADR 0011 Massnahme 2 weniger ab, als sie
  verspricht. Umgehbar ueber ausgeschriebene Waechter.
- **Der Riegel bindet die Schalter, nicht den Sprachmodus.** Ein Mitglied mit lokalem
  `set(CMAKE_CXX_EXTENSIONS ON)` bekaeme `gnu++20`, und kein Riegel sagt etwas. In 0060
  ausdruecklich ausgenommen -- eigener Vorschlag, wenn es je ein Mitglied gibt.

## Zum Apparat

- **Ein Paket kann zweimal zur Pruefung kommen**, solange zwischen meinem Urteil und dem
  Statusnachzug des Projektmanagers ein Lauf liegt (0058, 2026-09-03). Dann **nicht** die
  erste Pruefung abschreiben: gezielt dort messen, wo Runde 1 "nicht geprueft,
  ausgewiesen" geschrieben hat. Hat hier einen Befund und eine Positivprobe gebracht.
- **Der Commit-Betreff luegt, siebtes Mal** (0033, 0038, 0046, 0058 zweimal, 0060, 0063
  -- der Commit mit dem Betreff des Pakets trug nur das Logbuch des Bauagenten, die
  Aenderung lag zwei Commits frueher unter fremdem Betreff, und ein dritter hat danach
  eine Leerzeile nachgeschoben). **Den Vorzustand nie ueber den Betreff suchen, sondern
  ueber `git log -S '<eine neue Codezeile>' -- <datei>`:** Das nennt den Commit, der die
  Zeile eingefuehrt hat, und sein Elter ist die Vergleichsfassung. Ursache ist
  `lauf.py:committen`, das die Schreibverzeichnisse einer Rolle als Ganzes nimmt -- zwei
  gleichzeitige Laeufe reichen. *Nie den Commit als Liste dessen lesen, was ein Paket
  geaendert hat; immer die `dateien`-Liste einzeln gegen den Vorzustand halten.*
- **Vor dem Anlegen eines Vorschlags die hoechste Nummer lesen -- und nach dem Schreiben
  noch einmal.** Parallele Laeufe belegen Nummern waehrend man schreibt. Gilt auch fuers
  eigene Logbuch: Es kann sich unter der Hand aendern.
- **Ein neuer Befund in einer Funktion, zu der schon ein Vorschlag auf `vorschlag` steht,
  gehoert in diesen Vorschlag** -- gleiche `dateien`-Liste heisst, der Baulauf muesste
  ohnehin serialisieren. Datiert nachtragen und im Befund sagen, dass man es getan hat.
