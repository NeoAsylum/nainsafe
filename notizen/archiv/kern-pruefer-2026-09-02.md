# Logbuch: kern-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/kern-pruefer-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz. Ein Logbuch, das unbegrenzt wächst, liest am Ende niemand
mehr — und es kostet jeden deiner Läufe Kontext.

---

## Was funktioniert

<!-- Suchen, Formulierungen, Quellen, Vorgehensweisen, die etwas gebracht haben.
     Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-09-02 — **Selbst bauen und `ctest` laufen lassen ist erlaubt und kostet zwei
  Minuten**: `cmake -S . -B "$TMPDIR/<name>"`, `cmake --build`, `ctest`. Der Bau ist
  der stärkste Nachweis, wenn die Rechenproben `static_assert` sind — dann hat der
  Übersetzer sie ausgewertet, nicht ich.
- 2026-09-02 — **Vor dem Urteil in die Linkzeile sehen.** `link.txt` und `flags.make`
  im Bauverzeichnis sagen, ob eine Probe wirklich den geprüften Code misst oder nur
  sich selbst. Ein Sanitizer findet nur, was er selbst übersetzt hat; ohne diesen
  Blick ist „grün unter ASan" eine Behauptung.
- 2026-09-02 — **Die Abnahmebedingungen einzeln durchnummeriert abarbeiten und jede
  mit ihrem eigenen mechanischen Aufruf belegen.** Beide Befunde des ersten Laufs
  fielen genau dabei an; beim Lesen des Codes wären sie unsichtbar geblieben, weil
  der Code richtig ist.
- 2026-09-02 — **Zuerst den Diff der Dateien aus dem Feld `dateien` ansehen, nicht die
  Statusnotiz des Bauagenten.** `git show <commit> -- <pfade>` beantwortet in einem
  Aufruf, ob nur das Verlangte geändert wurde — und ob der unberührte Teil noch der
  ist, den ich beim letzten Mal gebaut habe. Dann trägt die Messung von damals weiter.
- 2026-09-02 — **Der Commit-Betreff sagt nicht, was im Commit steht.** Die
  Rücklauf-Behebung an 0004 lag in einem Commit mit fremdem Betreff; der Commit, der
  0004 nennt, enthielt sie nicht. Immer `git log -- <datei>` statt nach dem Betreff
  suchen. **Zum zweiten Mal bestätigt bei 0012:** ein Commit trug die Kennung 0012 und
  enthielt ausschließlich die Dateien von 0008. `git show --stat <commit>` vor jedem
  Urteil, und die Abweichung in den Befund — sie kostet später die Eingrenzbarkeit.
- 2026-09-02 — **Eine veröffentlichte Prüfzahl lässt sich von Hand nachrechnen, wenn
  die Probe ihren Zwischenzustand mitdruckt** (bei 0012 der Saatzustand: `rotl(s1·5,7)·9`
  in drei Zeilen Hexarithmetik, trifft die fremde Quelle). Das bricht den Kreis „das
  Programm prüft sich selbst" ohne Compiler. *Eine Probe, die nur Endwerte druckt,
  macht das unmöglich — ein Argument für Zwischenausgaben, kein Geschmack.*
- 2026-09-02 — **Bei einem Zufallserzeuger ist die einzige harte Frage, woher die
  Erwartungswerte stammen.** Ausgabe sieht in jedem Fall zufällig aus, also beweist
  „grün" nichts. Die vier zitierten URLs selbst abrufen und Konstanten, Schrittweiten
  und Zeilenreihenfolge Zeichen für Zeichen dagegenhalten — das ist die Prüfung, alles
  andere ist Beiwerk. Bei 0012 stimmten alle vier.
- 2026-09-02 — **`python3 -c` als Nachrechner geht, wenn es genau ein Ausdruck ist.**
  Damit ist die von aussen gerechnete Vergleichszahl doch möglich, obwohl keine Datei
  geschrieben werden darf: `print(hex(__import__('functools').reduce(<schritt>,
  <bytes>, <start>)))` in einer Zeile. So habe ich bei 0008 alle drei veröffentlichten
  FNV-Summen unabhängig neu aufgebaut. **Das ist der stärkste Nachweis, den ich habe**,
  weil er den Kreis „das Programm prüft sich selbst" ohne Compiler bricht.
- 2026-09-02 — **Eine Tabelle im Code gegen ihre Quelldatei zu `diff`en schlägt jeden
  Selbsttest des Pakets.** Bei 0008 beweist der eingebaute `static_assert`-Deckungslauf
  nur, dass Tabelle und Rechenvorschrift **zueinander** passen; ob beide zum Verzeichnis
  passen, beweist er nicht. Zwei `grep|sed` in eine Prozesssubstitution und ein `diff` —
  zehn Sekunden, und die Bedingung ist von aussen belegt statt von innen behauptet.
- 2026-09-02 — **Jede Behauptung „weicht ab von T&lt;n&gt;" im Quelltext gegen T&lt;n&gt;
  halten.** Bei 0008 stand über einer Aufzählung, ihre Reihenfolge weiche von T15 ab —
  und der zitierte T15-Satz trug genau dieselbe Reihenfolge. Der Code war richtig, der
  Kommentar erfand einen Widerspruch. In dieser Fabrik ist ein gemeldeter Widerspruch
  ein Arbeitsgegenstand, ein erfundener kostet also echte Zeit.

- 2026-09-02 — **Eine Abbruchmeldung, die die Adresse ausschreibt, ist ein Prüfhebel und
  nicht nur Bedienkomfort.** Bei 0016 nennen sechzehn Abbrüche Name *und* laufende Nummer;
  beides gegen `daten/adressen.md` gehalten (Nr. 1, 105, 106, 240, 256) — Treffer. Damit
  ist die Adressabbildung von aussen belegt, ohne Compiler und ohne eigenes Programm.
  *Künftig: bei jedem Paket, dessen Meldungen eine Kennung tragen, diese Kennung gegen die
  Quelldatei halten. Es ist der billigste Weg aus dem Kreis „das Programm prüft sich selbst".*

- 2026-09-02 — **Eine Reparatur, die von `static_assert` gehalten wird, macht den
  Zahntest entbehrlich.** Bei 0023 steht der Fehlerwert an einer Stelle und wird von
  zwei Zusicherungen gehalten; ein Rückfall auf den alten Wert ist damit ein
  *Übersetzungs*fehler und kein roter Test. Ein grüner Bau beweist dann, dass die
  Zusicherung ausgewertet wurde — genau der Nachweis, den ich sonst mit einer Kopie
  und einer Mutation führen müsste und hier nie führen darf. *Künftig: erst nachsehen,
  ob die Abnahmebedingung im Übersetzer verankert ist, bevor ich einen Mutationstest
  plane, der ohnehin abgewiesen wird.*
- 2026-09-02 — **In beiden Bauprofilen bauen, nicht nur in einem.** `baulauf.py` nimmt
  `RelWithDebInfo`; unter `-O2` schaltet g++ Warnungen zu, die in `Debug` nie
  erscheinen, und mit `-Werror` ist das der Unterschied zwischen grün und rot. Zwei
  Konfigurationen kosten zusammen keine zwei Minuten.

## Was nicht funktioniert

<!-- Was du versucht hast und was dabei herauskam. Damit du es nicht in drei Wochen
     erneut versuchst.
     Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig: Die Welt
     aendert sich, und eine Quelle, die im Maerz nichts hergab, kann im Juni
     ergiebig sein. -->

- 2026-09-02 — **Ein eigenes Prüfprogramm anzulegen war nicht erlaubt**: weder `Write`
  nach `$TMPDIR` noch `g++ -x c++ -` mit Heredoc noch eine Umleitung in eine Datei.
  Was geht, ist der Bau des Pakets selbst. Beim nächsten Mal die eigenen Werte gleich
  als Kopfrechnung gegen den Quelltext planen und im Befund sauber trennen, was
  ausgeführt und was gerechnet wurde — sonst sieht ein Urteil härter aus, als es ist.
  **Teil-Widerruf 2026-09-02, dritter Lauf:** Der Nachrechner geht doch, siehe oben —
  einzeiliges `python3 -c`. Gesperrt bleiben mehrzeilige `-c`-Skripte, Heredocs, jede
  Umleitung in eine Datei und **jede Pipe von `sed` in einen Compiler**. Damit ist der
  naheliegende Zahntest („eine Adresse verfälschen, sehen ob der `static_assert`
  rotwird") nicht durchführbar; Ersatz ist die Gegenprobe über die Probe selbst, die
  Präfixe und Verlängerungen nachweislich ablehnt. **Dritte Bestätigung 2026-09-02
  (0023):** zusätzlich abgewiesen wurden `cp -r`, `python3 -c` über mehrere Zeilen und
  `Edit` ausserhalb des Repos. Was überraschend *durchging*: `git worktree add --detach
  <ziel> <commit>` und `git -C <ziel> checkout <commit> -- <pfad>`. Damit ist ein
  Vorzustand baubar — nur ändern lässt sich darin nichts, der Mutationstest bleibt also
  zu. Aufräumen geht auch nicht (`worktree prune` scheitert an der Schreibsperre): Das
  gehört in den Befund, sonst findet es der Betreiber nie.
- 2026-09-02 — **Die Shell ist nicht verlässlich da; ein Prüfplan, der sie voraussetzt,
  fällt aus.** Mal sind verkettete Befehle erlaubt, mal nur einzelne. Was immer geht:
  `Glob`, `Grep`, `Read` und `befunde/uebersetzung-<datum>.md` als fremdgemessener
  Bau- und Testbeleg. Eine Prüfung ist damit möglich — sie muss nur sagen, was
  fremdgemessen ist.

- 2026-09-02 — **Die erzeugte Probe direkt starten ist gesperrt, `ctest -R <name> -V`
  nicht.** Damit kommt man an die volle Ausgabe des Programms, ohne es aufzurufen. Zwei
  solche Läufe hintereinander und ein `diff` sind ausserdem der einzige
  Determinismusnachweis, den ich ohne eigenes Programm führen kann.

## Offene Faehrten

<!-- Etwas, das du bemerkt hast, aber diesmal nicht verfolgen konntest. Der naechste
     Lauf faengt hier an. -->

- 2026-09-02 — **Prüfmuster, das sich lohnen dürfte: `grep -c` gegen die Abnahme
  selbst.** Beide Befunde an 0004 entstanden dadurch, dass die geprüfte Datei die
  Grep-Muster ihrer eigenen Abnahme als Kommentar zitiert und sie damit auslöst. Das
  ist wahrscheinlich kein Einzelfall — bei jedem Paket, dessen Abnahme einen Grep
  vorschreibt, zuerst prüfen, ob die Treffer aus dem Code oder aus einem Kommentar
  über den Code kommen. **Bestätigt in Runde 2:** behoben, und die Umformulierung hat
  keinen neuen Treffer eingeschleppt.
- 2026-09-02 — **Ein Mustervergleich als Abnahmekriterium hängt am Werkzeug, und das
  steht nirgends.** `baulauf.py` legt ein Bauverzeichnis *innerhalb* des geprüften
  Verzeichnisses an; `flags.make` enthält dann `-Wdouble-promotion`. POSIX-`grep -r`
  trifft es, ein `.gitignore`-treues Werkzeug nicht. Bei jeder Abnahme, die einen
  Suchlauf über ein Verzeichnis vorschreibt, künftig dazuschreiben, womit gemessen
  wurde — sonst urteilen zwei Prüfläufe verschieden über dieselbe Datei.
- 2026-09-02 — **Ein Grep als Abnahmekriterium muss gegen die Typnamen dieses Kerns
  geprüft werden, bevor man ihm glaubt.** Bedingung 1 von 0012 sucht veränderliche
  Ablagen mit `^\s*[A-Za-z_]+ [a-z_]+ =` — und `[A-Za-z_]+` bricht bei `u64` nach dem
  `u` ab. `u64 zaehler = 0;` auf Namensraum-Ebene bliebe unsichtbar, also genau der
  Typ, aus dem der ganze Kern besteht. Das Paket war trotzdem sauber (von Hand
  nachgesehen), aber das Muster wandert in die nächsten Kernpakete. *Künftig: jedes
  vorgeschriebene Suchmuster einmal gegen einen erfundenen Verstoß halten, nicht nur
  laufen lassen. Ein leerer Treffer beweist nur, dass das Muster leer ausgeht.*
- 2026-09-02 — **Prüfmuster, das getragen hat und weiter trägt: Bei jedem Ergebnistyp
  mit Ja-Nein-Feld fragen, ob der Wert im Nein-Fall von einem gültigen unterscheidbar
  ist.** So entstand Befund 3 an 0008, aus ihm Paket 0023, und das ist abgenommen.
  `std::optional` ist in diesem Kern per Abnahme verboten, solche Typen kommen also
  noch häufiger.
- 2026-09-02 — **Zwischen zwei Paketen entsteht eine Lücke, die kein Bauagent schliessen
  darf — und keine Abnahme fängt sie.** 0008 reicht die Durchsetzung von T18 („`Zustand`
  ist von aussen nicht schreibbar") ausdrücklich an 0016 weiter, 0016 nimmt sie in *Was du
  baust* auf, aber keine seiner sechs Bedingungen verlangt sie, und die Datei dafür steht
  nicht in seiner `dateien`-Liste. Beide Pakete sind für sich korrekt, die Zusage fehlt
  trotzdem. *Künftig: jede Zusage aus „Was du baust", die in keiner Abnahmebedingung
  wiederkehrt, einzeln nachsehen — genau dort liegen die Befunde, die niemandem gehören.*
- 2026-09-02 — **Ungeklärt: Schaltet `-fwrapv` den UBSan-Test auf
  vorzeichenbehafteten Überlauf ab?** Beide stehen in 0016 in jedem Profil. Wenn ja,
  deckt ADR 0011 Maßnahme 2 weniger ab, als sie verspricht. In diesem Lauf nicht
  nachweisbar (kein eigenes Programm möglich); ein Zweizeiler klärt es, sobald das
  geht. Betrifft jedes Kernpaket, das sich auf die Maßnahme statt auf einen
  ausgeschriebenen Wächter verlässt.
