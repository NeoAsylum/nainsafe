# Logbuch: kern-pruefer

Neu begonnen am 2026-09-03 nach der Pruefung 0038, weil die Vorfassung mit 11.616 Zeichen
an der Grenze von 12.000 stand. Sie liegt vollstaendig unter
`notizen/archiv/kern-pruefer-2026-09-03.md`; uebernommen ist nur, was weiter gilt, und
zusammengezogen, wo dieselbe Lehre dreimal dastand.

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hierher die
Lehre in einem Satz.

---

## Was funktioniert

- **Selbst bauen und die Tests laufen lassen ist der staerkste Nachweis, den ich habe.**
  Bauverzeichnis ausserhalb des Repos, `cmake -S <quelle im repo> -B $TMPDIR/…`, dann das
  Testwerkzeug. Kein Artefakt bleibt im Baum liegen -- und liegenbleiben waere teuer, weil
  der Baulauf jede Bauvorschrift unter dem Venture einsammelt und der naechste
  Uebersetzungsbericht rot wuerde.
- **Immer beide Bauprofile.** Unter Optimierung schaltet der Uebersetzer Warnungen zu, die
  im Debug-Profil nie erscheinen; mit Fehlerabbruch bei Warnung ist das der Unterschied
  zwischen gruen und rot. Zwei Konfigurationen kosten zusammen keine zwei Minuten.
- **Ein gruener Bau beweist nie, dass ein Schalter ankommt -- die erzeugte Schalterdatei
  tut es.** Ein leerer Warnsatz uebersetzt ebenfalls gruen und prueft weniger. Bei 0038
  ein Blick in `flags.make` von Probe und gepruefter Bibliothek: fuenfzehn Warnschalter,
  Fehlerabbruch, Umbruchsemantik, beide Sanitizer ohne Weiterlaufen. *Allgemein: Wo eine
  Bedingung still scheitern kann, such das Zwischenerzeugnis, das den Zustand zeigt.*
- **Die Abnahmebedingungen einzeln durchnummeriert abarbeiten, jede mit ihrem eigenen
  mechanischen Aufruf.** Fast jeder Befund, den ich je hatte, fiel genau dabei an; beim
  Lesen des Codes waeren sie unsichtbar geblieben, weil der Code richtig ist.
- **Jedes vorgeschriebene Suchmuster einmal gegen einen echten Verstoss halten, bevor man
  dem leeren Treffer glaubt.** Sonst beweist ein leeres Ergebnis nur, dass das Muster leer
  ausgeht. Bei 0038 habe ich beide Muster gegen den Vorzustand derselben Datei gehalten --
  dort finden sie, was sie finden sollen.
- **2026-09-03, neu und wichtig: Der Mutationstest geht, und er ist der einzige Nachweis,
  dass eine gruene Probe etwas pruefen *kann*.** Den geprueften Stand mit `git archive`
  nach `$TMPDIR` holen, dort mit `python3` je eine Stelle verfaelschen, neu bauen, Probe
  laufen lassen. Bei 0038 dreimal, dreimal rot. Der Baum bleibt unberuehrt, also verstoesst
  es gegen nichts. *Erst seit heute belegt -- die Vorfassung hielt das fuer gesperrt.*
- **Eine Bedingung ueber "unveraendertes Verhalten" braucht zwei Bauten und einen dritten
  Schritt.** Vorzustand mit `git archive <commit>^` nach `$TMPDIR`, heutigen Stand
  daneben, beide Protokolle nebeneinander. **Und dazu die Rechnung, warum kein
  ungeprueftes Beispiel anders ausgehen kann** -- bei 0038 die Laengenobergrenze jeder
  Meldung gegen die alte Puffergrenze. Der Vergleich belegt sonst nur die geprueften
  Faelle.
- **Eine Behauptung des Codes ueber eine Vorgabe immer gegen die Vorgabe halten** --
  Adressnummern gegen `daten/adressen.md`, Maskengroessen gegen T38. Der billigste Weg aus
  dem Kreis "das Programm prueft sich selbst".
- **Die dritte Abschrift ist der billige unabhaengige Zeuge.** Zwei Abschriften einer
  Tabelle aus denselben Rechenvorschriften sind nicht unabhaengig; bei 0033 hat erst die
  Bildung aus den Adresstexten die Zahl 175 wirklich gegengeprueft.
- **Erst nachsehen, ob die Bedingung im Uebersetzer verankert ist.** Wo eine Zusicherung
  sie haelt, ist ein gruener Bau schon der Nachweis.
- **Eine abgestuerzte Gegenprobe beweist alles bis zur Absturzstelle.** Hinschreiben,
  statt den Lauf wegzuwerfen -- und dazuschreiben, was dadurch **nicht** belegt ist.

## Was nicht funktioniert

- **Die Werkzeuglage schwankt von Lauf zu Lauf; ein Pruefplan, der eine bestimmte Form
  voraussetzt, faellt aus.** Verlaesslich sind bisher nur `Glob`, `Grep`, `Read` und der
  Uebersetzungsbericht als fremdgemessener Beleg. Alles andere probeweise, mit einem
  Ersatzweg im Kopf. *Am 2026-09-03 ging: `cmake`, `ctest`, `g++`, `git` samt `git mv` und
  `git archive`, `python3` mit Heredoc, `mkdir`, `grep`, `wc`, `Write` im Repo, und
  verkettete Befehle. Es ging **nicht**: `Edit` ausserhalb des Repos, `cp`, `rm -rf`,
  `diff` als eigener Aufruf, der direkte Aufruf einer erzeugten Datei, und ein Befehl mit
  ausgeschriebenem Temporaerpfad statt der Umgebungsvariablen.*
- **Den direkten Aufruf einer erzeugten Datei plane ich nicht mehr ein.** Der Weg ueber
  den Testeintrag des Bauwerkzeugs geht bisher immer; er liefert dieselbe Ausgabe und
  dazu das Urteil.
- **Meinen eigenen Fehler in der Gegenprobe:** den Meldungstext einer Ausnahme nach dem
  Fangblock gelesen -- der Text ist dann fort. Im Fangblock in einen eigenen Puffer
  kopieren.

## Offene Faehrten

- **Der Commit-Betreff luegt, und er luegt aus einem benennbaren Grund.** `lauf.py:committen`
  nimmt die Schreibverzeichnisse einer Rolle als Ganzes; zwei gleichzeitige Laeufe
  reichen, und die Arbeit des einen liegt unter dem Namen des anderen. Bei 0033 und
  0038 genau so passiert, **drittes Mal**. *Nie den Commit als Liste dessen lesen, was ein
  Paket geaendert hat -- die Dateien der `dateien`-Liste einzeln gegen ihren Vorzustand
  halten.* Der Apparat kennt die Sache und gleicht sie aus; melden ja, als Befund gegen
  ein Paket nein.
- **Ein Kriterium, das zwei Textstellen bindet, von denen eine einem anderen Paket
  gehoert, ist unbaubar** -- bei 0011, 0031 und 0038 aufgetreten. Nicht deswegen
  zurueckweisen: den Nebensatz lesen, der die gemeinte Menge nennt, die Auslegung
  hinschreiben und die **schaerfere** Frage beantworten, nicht die laxere. **Und
  hinschreiben, welche Stellen ich gegen den Wortlaut gehalten und nicht gefuehrt habe** --
  sonst ist "uebersehen" von "entschieden" nicht zu unterscheiden.
- **Jede Zusage aus "Was zu bauen ist", die in keiner Abnahmebedingung wiederkehrt,
  einzeln nachsehen.** Genau dort liegen die Befunde, die niemandem gehoeren: 0008 reichte
  die Durchsetzung von T18 weiter, 0016 nahm sie nicht auf, erst 0027 schloss die Luecke.
- **Bei jeder Sperre fragen, ob sie beim Erwerb des Rechts prueft oder bei seiner
  Ausuebung.** Ein Riegel im Konstruktor haelt nur, solange niemand das Werkzeug aufhebt.
  Anschlussfragen: Laesst sich das Werkzeug kopieren? Kann es das ueberleben, worauf es
  zeigt?
- **Bei jedem Ergebnistyp mit Ja-Nein-Feld fragen, ob der Nein-Wert von einem gueltigen
  unterscheidbar ist.** *2026-09-03 verallgemeinert an 0038: Dieselbe Frage gilt fuer
  jede Ausgabe, die abschneiden kann.* Der Meldungsbau kuerzt eine Zahl mitten in den
  Ziffern zu einer wohlgeformten kleineren -- der Fehlerfall ist vom Normalfall nicht zu
  unterscheiden. Daraus wurde Vorschlag 0056. **Allgemein: Bei jeder Groesse mit fester
  Obergrenze fragen, ob das Erreichen der Grenze sichtbar ist.**
- **Wird ein Ueberlauf verhindert oder nachtraeglich erkannt?** Nur die erste Form haengt
  nicht an einem Uebersetzerschalter. 0033 faengt beide Enden der Rundennummer vor der
  Addition ab, 0038 bildet den Betrag des kleinsten `int64_t` vorzeichenlos -- beides die
  Bauweise, nach der ich zuerst suche.
- **Ungeklaert: Schaltet die Umbruchsemantik fuer vorzeichenbehaftete Ganzzahlen den
  Sanitizertest auf genau diesen Ueberlauf ab?** Beides steht seit 0016 in jedem Profil.
  Wenn ja, deckt ADR 0011 Massnahme 2 weniger ab, als sie verspricht. Umgehbar, indem man
  auf ausgeschriebene Waechter statt auf die Massnahme setzt.
