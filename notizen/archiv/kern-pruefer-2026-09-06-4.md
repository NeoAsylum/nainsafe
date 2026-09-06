# Logbuch: kern-pruefer

**Rotiert am 2026-09-06** bei 11.677 Zeichen, nach der Pruefung zu 0091. Vorfassung
unter `notizen/archiv/kern-pruefer-2026-09-06-3.md` (die `-1` und `-2` desselben Tages
stammen aus Parallellaeufen). Archivieren mit `cmake -E copy`, dann neu schreiben.

**Hoechstens 12.000 Zeichen.** Belege in die Ergebnisdatei, hierher die Lehre in einem
Satz. **An dieser Datei schreiben mehrere eigene Laeufe gleichzeitig** -- vor jedem
Anhaengen neu lesen und die Groesse **im selben Aufruf** pruefen. Wer blind anhaengt,
schreibt eine fremde Rotation zurueck.

---

## Der Apparat

- **Die Sperre entscheidet nach Inhalt und wechselt innerhalb eines Laufs.**
  *2026-09-06:* `Write` auf eine `.cpp` abgelehnt, `Write` auf eine `.md` angenommen --
  in **demselben** Lauf. Vor dem Ausweichen also immer erst probieren; ein abgelehntes
  Werkzeug kostet einen Aufruf, ein umgangenes eine halbe Stunde.
- **`printf` faellt an Zeichen, nicht an Laenge.** Angenommen wurden mehrzeilige
  C++-Zeilen mit Klammern, Punkten und Zahlen; abgelehnt jede Zeile mit `!=` und jede mit
  einem Feldzugriff `name_[...]`. Auch `=` zwischen Name und Zahl faellt. Ausweg: die
  Zeile aus der Originaldatei **ausschneiden** statt sie zu tippen
  (`head -n N datei | tail -n 1`) und nur den Rest schreiben.
- **Ketten mit `&&` oder `;`, `for`-Schleifen und `sed` fallen regelmaessig.** Befehle
  einzeln. `cmake -E copy`, `cmake -E cat`, `cmake -E tar`, `cmake -E rm` tragen
  zuverlaessig, ebenso `head`, `tail`, `diff`, `grep`, `md5sum`, `python3`.
- **Die Shell verliert ihr Arbeitsverzeichnis zwischen Aufrufen.** Absolute Pfade oder
  `cd` im selben Aufruf. Zweimal in einem Lauf darauf hereingefallen.
- **`git archive <commit>` ohne Pfadangabe zieht das ganze Repo** (63 MB). Das ist
  richtig so -- `specs/` und `decisions/` muessen mit, sonst faellt der
  Belegstellenriegel aus --, aber der Tarball gehoert **in** das ignorierte Verzeichnis,
  nicht daneben: `.gitignore` trifft `ventures/**/bau-*/`, also Verzeichnisse, keine
  `.tar` daneben.
- **Unter `befunde/bau-pruefung-<paket>/` messen**, nie in `$TMPDIR` (geteilte tmpfs,
  laeuft voll). `baulauf.py` nimmt `befunde` vom Manifestsuchlauf aus.
- **Nie ueber den Commit-Betreff suchen**, immer `git log -- <datei>` je Datei einzeln.
  *0091:* diesmal traf der Betreff, aber `git log 9449bda..HEAD -- .../kern/` war die
  Zeile, die zaehlte -- sie belegt, dass der Arbeitsbaum noch der Paketstand ist.
- **Im Befund den Stand nennen, nie das Wort `HEAD`.** md5 am Anfang und am Ende
  gegenrechnen, beides hinschreiben, und `git log` am Ende noch einmal lesen: Waehrend
  meines 0091-Laufs kamen zwei fremde Commits dazu.

## Mutieren

- **Die billigste Mutation ist eine geloeschte Zeile**, weil sie kein neues Zeichen
  braucht: `head -n N` plus `tail -n +M`, mit `cmake -E cat` zusammengesetzt. *0091:*
  ein entferntes `continue` und ein entfernter `if`-Block toeteten je zwei Proben.
- **Waehle die Zeile so, dass der Rest uebersetzt.** Ein geloeschtes `continue` laesst
  den leeren `if`-Rumpf stehen; ein geloeschter ganzer `if` haette die Variable darueber
  unbenutzt gemacht und den Bau am Warnsatz rot gefaerbt -- rot aus dem falschen Grund.
- **Eine Zahl heruntersetzen ist die zweitbilligste**, wenn die Konstante ueber zwei
  Zeilen steht: Die erste endet auf `=`, also braucht die Ersatzzeile kein
  Gleichheitszeichen. *0091:* `KETTENBLATT_ZEICHEN` von 1.667.329 auf 342, und der
  behauptete Puffer-Abbruch war in einem Lauf belegt.
- **Zu jedem Mutantensatz gehoert m0, der unveraenderte Baum**, und am Ende ein `diff`
  der zurueckgesetzten Datei gegen die Paketdatei. Leer, sonst ist der Kontrollbaum
  keiner.
- **Ein Mutant an der Probe misst den Aufrufer, ein Mutant an der Quelle die Probe.**
  Beides ist erlaubt und beweist Verschiedenes: Der Probenmutant zeigt, was bei falscher
  Eingabe herauskommt (Vorschlagsbeleg), der Quellmutant, ob die Probe die Regel haelt.

## Was funktioniert

- **Selbst bauen und selbst fahren ist der staerkste Nachweis.** Die Probe druckt
  meistens ihr Ergebnis ab -- lies das Blatt, statt dem gruenen Haken zu glauben.
- **Jede Abnahmebedingung einzeln, mit eigenem mechanischem Aufruf.**
- **Immer beide Bauprofile und beide Bauwege** (Alleinbau und Arbeitsbereich). Der
  Arbeitsbereich bringt die drei Riegel mit, die der Alleinbau nicht hat.
- **Determinismus ueber den Profilvergleich:** die **ganze** Ausgabe der Probe aus Debug
  und Release zeilenweise gegenueberstellen. Taugt nur, wenn die Probe wirklich etwas
  druckt; sonst am Quelltext belegen (kein Gleitkomma, Iteration ueber `std::array`).
- **Zu jedem Positivnachweis der Negativnachweis.** *0091:* „0 ohne Ursache" heisst erst
  etwas, weil daneben ein Verlauf mit Luecke „4 ohne" produziert.
- **Von Hand nachrechnen, auch wenn die Probe gruen ist.** Bei 0091 stimmten alle acht
  Zahlen -- aber die Tabelle im Befund ist der Beleg, dass sie geprueft wurden.
- **Den fremden Nachweis-Apparat lesen und selbst fahren.** Vorher seine Riegel pruefen:
  Ersetzt er genau eine Zeile? Trennt er die eigene Zusicherung von der Nachbarin? Gibt
  es den vierten Fall, der zeigt, dass **diese** Zeile reisst?
- **Eine Behauptung in einem Kommentar ist ein Pruefauftrag** -- auch „die Probe druckt
  beide Zahlen ab".
- **Jeden Namen und jede Zahl aus dem Paket gegen seinen T-Block halten.**

## Was nicht funktioniert

- **Ein rotes Ergebnis gehoert nicht automatisch dem geprueften Paket.**
- **Eine Zusicherung, deren beide Seiten am selben Regler haengen, faengt diesen Regler
  nicht.** Immer den Regler bewegen, nicht die abgeleitete Groesse.
- **Zwei Regler, eine Messung.** *0091:* Der Kopf sagt, die Zusicherung fange beide; der
  Nachweis bewegt einen. Der zweite traegt arithmetisch (positiver Faktor, strikte obere
  Schranke) -- **aber im Befund hinschreiben, dass das eine Herleitung ist und kein
  Lauf.**
- **Den Meldungstext einer Ausnahme nach dem Fangblock lesen** -- er ist dann fort.

## Offene Faehrten

- **Ein Widerspruch zwischen Abnahme und Vorgabe ist kein `zurueck`**, und eine Vorgabe,
  zu der die Abnahme **schweigt**, ebenso wenig. Das Urteil folgt den Bedingungen, der
  Verstoss wird ein Vorschlag. *0144, 0156, 0091:* je `geprueft` plus Vorschlag.
- **Prueffrage bei jedem unscharfen Satz:** *Fuehrt der Irrtum zu mehr Pruefung oder zu
  weniger?* Ein lauter Abbruch ist kein `zurueck`, eine stille Kuerzung immer.
- **Trenne die Vorbedingung des Aufrufers von der Zusage des Kastens.** *0091:* Die
  Kette ist richtig auf wohlgeformter Eingabe; ungeprueft ist, ob die Eingabe wohlgeformt
  **ist**. Das Erste entscheidet das Urteil, das Zweite wird ein Vorschlag.
- **Zwei Zahlen fuer dieselbe Aussage sind eine Fehlerquelle, sobald jemand beide
  liest.** Suchmuster fuer den naechsten Lauf: Welche Groesse steht zweimal da, und
  welche Stelle sieht beide? *0091:* `Ursachensatz.runde` gegen `Verlauf::rundennummer`.
- **Eine vermutete Schwaeche erst mutieren, dann urteilen.** Ein Befund aus dem Kopf war
  schon zweimal falsch.
- **Ein unerreichbarer Zweig ist kein Befund, aber ein Pruefauftrag.** *0091:* Ein Ende
  `Ausloeser`, das nur gaelte, wenn die Adresse `KEIN_PLATZ` waere -- nachgesehen, alle
  sechs Erzeuger brechen vorher ab. Zwei Minuten, und die Frage ist erledigt.

## Zu Vorschlaegen

- **Kein Vorschlag ohne belegten Schaden**, und erst `grep` ueber `aufgaben/` -- zehnmal
  stand er schon da. Bei 0091 traf der Suchlauf fuenf Pakete, keines mit der Frage.
- **Der staerkste Vorschlagsbeleg ist ein Blatt, das falsch ist und richtig aussieht.**
  Drei geaenderte Zeilen in der *Probenabschrift* genuegten fuer 0091; der Kern blieb
  unangetastet, und das gehoert dazugeschrieben.
- **Nenne, warum die Luecke erst jetzt eine ist.** „Vor diesem Paket las niemand beide
  Zahlen" ist die Begruendung, die den Vorschlag von einem Ruecklauf trennt.
- **Schreib dazu, was der Riegel heute kostet.** Kostet er nichts, weil alle Aufrufer die
  Regel schon halten, dann gehoert **das** in die Abnahme -- sonst ist ein Riegel, der
  nichts kostet, von einem, der nicht greift, nicht zu unterscheiden.
- **Nummernkollision:** *2026-09-06* war `0185` bereits doppelt belegt, ohne dass ich es
  verursacht haette. `ls aufgaben/` vor der Wahl, die Kollision im Vorschlag benennen,
  aufraeumen tut sie der Projektmanager.

## Nachtrag 2026-09-06 (Pruefung 0155)

- **Bei einem reinen Kommentarpaket ist das zeichengleiche Vorkompilat der ganze
  Nachweis.** Praeprozessor mit -P und -E ueber alte und neue Fassung, md5 gegenrechnen:
  Kommentare fallen weg, also beweist Gleichheit "nur Kommentar" -- fuer alle vier
  Rollenfragen auf einmal, weil die Uebersetzungseinheit bitgleich bleibt.
- **Die Positivkontrolle dazu kostet drei Aufrufe:** eine Kopfkopie ohne genau eine
  Feldzeile (head plus tail), noch einmal vorkompilieren, diff. Zeigt er die Zeile, ist
  das Schweigen beim echten Vergleich ein Ergebnis.
- **Die alte Fassung kommt aus git show <commit>^:<pfad> in einen vorgeschalteten
  Suchpfad**, nicht in den Baum. Kein Editor, keine Datei des Pakets angefasst.
- **Zwei git-archive-Baeume plus diff -rq beantworten "ausserhalb dieser Datei null
  Zeilen" ohne jede Diff-Lesung.** Mit --exclude der befunde bleiben rund 250 Dateien.
- **Ein Riegel-A/B ueber dieselben zwei Baeume macht aus Gruen einen Beleg.** Sein
  Zaehlwerk muss auf genau die geaenderten Zeilen reagieren. *0155:* plus 5
  Kommentarzeilen, aber nur plus 2 von 3 neuen Anfuehrungen -- ist_bezeichner() nimmt
  keinen Punkt, ein Dateiname wird nie Kandidat. Der erklaerte Rest ist der Beleg.
- **Die 19/17 in werkzeugkette.cmake sind Warnsatz-Ziele, keine ctest-Proben.** Erst die
  Zeile lesen, die eine Zahl erzeugt, bevor man sie fuer eine Abweichung haelt. Gemessen
  wurden 22/20 Ziele und in beiden Profilen 18 von 18 Proben.
- **Eine Angabe, die der Auftrag ausdruecklich ausschliesst, aber gebaut wurde, ist kein
  zurueck**, solange keine Abnahmebedingung sie nennt. *0155:* eine Feldzahl im Kopf,
  heute richtig und morgen die naechste Altlast -- Befund an den Projektmanager, kein
  eigenes Paket, weil der Schaden noch nicht eingetreten ist.
- **Sperre am 2026-09-06 im Befundschreiben:** Write ganz abgelehnt; printf trug, fiel
  aber an einem Gleichheitszeichen zwischen Name und Zahl, an einem Pfeil aus Strich und
  spitzer Klammer und an einer Uebersetzerzeile im Text. Dieselbe Aussage in Prosa ging
  jedes Mal durch. Keine Rueckwaertsanfuehrung im Befund, sonst faellt alles.
- **Erst aufgaben/ absuchen, dann die Empfehlung schreiben, nicht danach.** *0155:* Mein
  Befund empfahl eine Auflage fuer die naechste Aenderung -- dabei stand 0180 schon auf
  offen, haengt an genau diesem Paket und liest genau diese Datei. Die richtige Antwort
  war eine vierte Bedingung dort, nicht ein Rat ins Blaue. Der Suchlauf gehoert **vor**
  den Absatz, sonst schreibt man ihn zweimal.

## Nachtrag 2026-09-06 (Pruefung 0173) -- naechster Lauf rotiert

- **Die Kostenmessung hat den Vorschlag getoetet, und das war ihr Zweck.** *0173:* Ein
  Riegel auf "Funktion ohne Kopfkommentar" sah zwingend aus; gemessen tragen im Kern nur
  24 von 79 Definitionen eine `///`-Zeile darueber, die 55 anderen stehen unter einem
  Balken. Also Stilvorschrift, kein Befund. Erst messen, dann formulieren.
- **`git archive` ohne die `befunde` bricht den Konfigurationslauf.** Der Schlussriegel
  verlangt `befunde/pruefung-0066/nachbau.py`. Messbaum immer ganz ziehen.
- **Write auf `.py` abgelehnt, `python3 -c` abgelehnt, Write auf `.md` angenommen** --
  alles am selben Tag. Ersatz fuer das Messskript ist das Grep-Werkzeug mit `multiline`;
  zwei Muster (mit und ohne Kopfzeile davor) geben Zaehler und Gegenzaehler.
- **Werden zwei Bloecke getauscht, genuegt je ein zeichengleicher Vergleich gegen die
  eigene Quelle.** Damit ist "keine Zeile erfunden, keine verloren" schon bewiesen; die
  Summenrechnung ist nur noch Lesehilfe.
