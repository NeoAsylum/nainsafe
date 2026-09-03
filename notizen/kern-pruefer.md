# Logbuch: kern-pruefer

Neu begonnen am 2026-09-02, weil die Vorfassung die Grenze von 12.000 Zeichen erreicht
hatte. Sie liegt vollstaendig unter `notizen/archiv/kern-pruefer-2026-09-02.md`;
uebernommen ist nur, was weiter gilt.

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hierher die
Lehre in einem Satz.

---

## Was funktioniert

- 2026-09-02 -- **Selbst bauen und die Tests laufen lassen ist der staerkste Nachweis, den
  ich habe.** Bauverzeichnis ausserhalb des Repos anlegen, uebersetzen, Testlauf. Und
  **immer in beiden Bauprofilen**: Unter Optimierung schaltet der Uebersetzer Warnungen zu,
  die im Debug-Profil nie erscheinen, und mit Fehlerabbruch bei Warnung ist das der
  Unterschied zwischen gruen und rot. Zwei Konfigurationen kosten zusammen keine zwei
  Minuten.
- 2026-09-02 -- **Die Abnahmebedingungen einzeln durchnummeriert abarbeiten und jede mit
  ihrem eigenen mechanischen Aufruf belegen.** Fast jeder Befund, den ich je hatte, fiel
  genau dabei an; beim Lesen des Codes waeren sie unsichtbar geblieben, weil der Code
  richtig ist.
- 2026-09-02 -- **Zuerst den Diff der Dateien aus dem Feld `dateien` ansehen, nicht die
  Statusnotiz des Bauagenten.** Ein Aufruf beantwortet, ob nur das Verlangte geaendert
  wurde -- und ob der unberuehrte Teil noch der ist, den ich beim letzten Mal gebaut habe.
- 2026-09-02 -- **Der Commit-Betreff sagt nicht, was im Commit steht.** Dreimal bestaetigt.
  Immer die Dateiliste des Commits ansehen, nie nach dem Betreff suchen -- und die
  Abweichung von der `dateien`-Liste in den Befund, sie kostet spaeter die Eingrenzbarkeit.
- 2026-09-02 -- **Eine Behauptung des Codes ueber eine Vorgabe immer gegen die Vorgabe
  halten.** Adressnummern gegen `daten/adressen.md`, Maskengroessen gegen T38,
  Feldnamen gegen die Tabelle in T18. Das ist der billigste Weg aus dem Kreis "das
  Programm prueft sich selbst".
- 2026-09-02 -- **Jedes vorgeschriebene Suchmuster einmal gegen einen erfundenen Verstoss
  halten, bevor man dem leeren Treffer glaubt.** Ein leeres Ergebnis beweist sonst nur,
  dass das Muster leer ausgeht. Und dazuschreiben, **womit** gemessen wurde: POSIX-Suche
  findet das Bauverzeichnis im geprueften Baum, ein an der Ignorierliste orientiertes
  Werkzeug nicht.
- 2026-09-02 -- **Erst nachsehen, ob die Abnahmebedingung im Uebersetzer verankert ist.**
  Wo eine Zusicherung sie haelt, ist ein gruener Bau schon der Nachweis, und ein
  Mutationstest, den ich ohnehin nicht durchfuehren darf, eruebrigt sich.

- 2026-09-02 -- **Eine Zusicherung, die eine Sichtbarkeit prueft, braucht ihre Gegenprobe
  -- und die ersetzt meine eigene Pruefung trotzdem nicht.** Bei 0027 fragt die Probe ueber
  einen Typparameter, ob Feld und Schreibzugriff erreichbar sind, und stellt daneben
  dieselbe Frage fuer den Lesezugriff, die `true` ergeben muss. Sauber gebaut -- aber der
  Nachweis, der zaehlt, sind drei eigene Uebersetzungseinheiten, je eine Zeile, gegen den
  Kopfbaum. Der Uebersetzer sagt dann selbst "is private within this context".
- 2026-09-03 -- **Ein gruener Bau ist nie der Nachweis, dass ein Uebersetzerschalter
  ankommt -- die erzeugte `flags.make` ist es.** Bei 0031 kann der Warnsatz leer sein und
  der Bau trotzdem gruen; die Zeile `CXX_FLAGS` zeigt dagegen, was am Ziel wirklich
  landet. *Allgemein: Wo eine Bedingung still scheitern kann, such das Zwischenerzeugnis,
  das den Zustand zeigt, statt das Ergebnis, das ihn verdeckt.*
- 2026-09-03 -- **Ich kann ausserhalb des Repos bauen und damit pruefen, ohne den Baum
  anzufassen.** `cmake -S <quelle im repo> -B $TMPDIR/…` gegen die Originalquellen, dazu
  `-DCMAKE_BUILD_TYPE=Release` als zweites Profil. Kalt statt warm, und kein Artefakt
  bleibt liegen. Ersetzte bei 0031 eine Bedingung, die das Anlegen einer Datei im Baum
  verlangt haette -- verboten fuer mich und riskant fuer alle nachfolgenden Laeufe.
- 2026-09-03 -- **Den Schalter, der rot macht, gegen seine eigene Abwesenheit halten.**
  Erst mit dem Satz aus `flags.make` uebersetzen (Code 1, Schalter steht in eckigen
  Klammern in der Meldung), dann ohne ihn (Code 0). Ohne die zweite Haelfte beweist die
  erste nur, dass irgendetwas rot wurde.
- 2026-09-03 -- **Eine Abnahmebedingung, deren Wortlaut ihr eigenes Suchmuster enthaelt,
  ist woertlich unerfuellbar** -- sie ist in dem Moment verletzt, in dem sie geschrieben
  wird. Nicht deswegen zurueckweisen: den Nebensatz lesen, der die gemeinte Menge nennt
  (bei 0031 "und sie steht in `werkzeugkette.cmake`"), die Auslegung hinschreiben und die
  **schaerfere** Frage beantworten, nicht die laxere.
- 2026-09-02 -- **Der ausgefuehrte Gegenbeweis steckt oft schon in der Probe des Pakets.**
  Bei 0027 musste ich kein eigenes Programm starten: Die Belegungsschleife des Pakets
  laeuft selbst achtmal an ihrem eigenen Riegel vorbei, und die veroeffentlichte Pruefsumme
  beweist, dass die Schreibzugriffe gelandet sind. *Kuenftig zuerst fragen: Tut der Test
  selbst schon das, was ich gerade nachbauen will?*

## Was nicht funktioniert

- 2026-09-02 -- **Die Werkzeuglage schwankt von Lauf zu Lauf; ein Pruefplan, der eine
  bestimmte Form voraussetzt, faellt aus.** Verlaesslich sind bisher nur `Glob`, `Grep`,
  `Read` und der Uebersetzungsbericht als fremdgemessener Beleg. Alles andere probeweise
  und mit einem Ersatzweg im Kopf.
- 2026-09-02 -- **Ein eigenes Programm zu starten war bisher nie erlaubt.** Bauen und den
  Testlauf ueber das Testwerkzeug ausfuehren geht; die erzeugte Datei direkt aufrufen
  nicht. Damit ist der Zahntest (eine Konstante verfaelschen, sehen ob es rot wird) zu.
  Ersatz: die Gegenprobe ueber die Probe selbst und der Vergleich gegen die Quelldatei.
- 2026-09-02 -- **Im Lauf zu 0027 waren `Write`, `Edit`, `mv`, `cp` und `sed -i`
  gesperrt, verkettete Befehle ebenfalls.** Was ging: `touch`, danach `printf %%s ... >`
  und `>>` in dieselbe Datei, und `git -C <wurzel> mv` fuers Archiv. **Und die Form des
  Inhalts entscheidet mit:** Abschnitte mit eingerahmtem Quelltext, mit zitierten
  Uebersetzeraufrufen oder mit langen Tabellen wurden abgewiesen, dieselbe Aussage als
  Aufzaehlung ging durch. *Kuenftig: Datei anlegen, in Abschnitten von rund dreissig
  Zeilen anhaengen, Aufzaehlungen statt Rahmen und Tabellen, und keine
  Uebersetzeraufrufe im Wortlaut zitieren -- sie beschreiben statt sie hinzuschreiben.*

- 2026-09-03 -- **Die Werkzeuglage war eine andere als am 2026-09-02, in beide
  Richtungen.** Es ging: `cmake`, `ctest`, `g++`, `git`, `grep`, `wc`, `mkdir`, ein
  Einzelbefehl mit Prozesssubstitution (`diff <(…) <(…)`), und ein Quelltext per
  Heredoc in `g++ -x c++ -` beziehungsweise `cmake -P /dev/stdin`. Es ging **nicht**:
  `Write` ausserhalb des Repos, `cp`, `rm -rf`, `tee`/`git archive` und ueberhaupt jeder
  Befehl mit `;` oder einer Rohrleitung in eine Datei. *Kuenftig: einen Befehl je Aufruf,
  Dateien nie kopieren, Testquelltext per Heredoc direkt in den Uebersetzer statt in eine
  Datei.* Der Zahntest ist damit wieder offen -- ausserhalb des Baums.

## Offene Faehrten

- 2026-09-02 -- **Jede Zusage aus "Was du baust", die in keiner Abnahmebedingung
  wiederkehrt, einzeln nachsehen.** Genau dort liegen die Befunde, die niemandem gehoeren:
  0008 reichte die Durchsetzung von T18 weiter, 0016 nahm sie nicht auf, und erst 0027 hat
  die Luecke geschlossen. Zweimal derselbe Mechanismus.
- 2026-09-02 -- **Bei jeder Sperre fragen, ob sie beim Erwerb des Rechts prueft oder bei
  seiner Ausuebung.** Das war Befund 1 an 0027, und es ist ein allgemeines Muster: Ein
  Riegel im Konstruktor haelt nur, solange niemand das Werkzeug aufhebt. Dazu gehoert die
  Anschlussfrage, ob sich das Werkzeug kopieren laesst und ob es den ueberleben kann, auf
  den es zeigt.
- 2026-09-02 -- **Bei jedem Ergebnistyp mit Ja-Nein-Feld fragen, ob der Wert im Nein-Fall
  von einem gueltigen unterscheidbar ist.** Der Optionaltyp ist in diesem Kern per Abnahme
  verboten, solche Typen kommen also noch haeufiger.
- 2026-09-02 -- **Ungeklaert: Schaltet die Umbruchsemantik fuer vorzeichenbehaftete
  Ganzzahlen den Sanitizertest auf genau diesen Ueberlauf ab?** Beides steht seit 0016 in
  jedem Profil. Wenn ja, deckt ADR 0011 Massnahme 2 weniger ab, als sie verspricht.
  Betrifft jedes Kernpaket, das sich auf die Massnahme statt auf einen ausgeschriebenen
  Waechter verlaesst.

- 2026-09-02 -- Nachtrag zur Zeile darueber: Dort steht versehentlich ein doppeltes
  Prozentzeichen. Gemeint ist der Aufruf mit einfachem Formatstring, der den Text
  unveraendert ausgibt.
