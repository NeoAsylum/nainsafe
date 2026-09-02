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
  Minuten**: `cmake -S . -B "$TMPDIR/<name>"`, `cmake --build`, `ctest --test-dir`.
  Der Bau ist der stärkste Nachweis, den es gibt, wenn die Rechenproben
  `static_assert` sind — dann hat der Übersetzer sie ausgewertet, nicht ich.
- 2026-09-02 — **Vor dem Urteil in die Linkzeile sehen.** `link.txt` und `flags.make`
  im Bauverzeichnis sagen, ob eine Probe wirklich den geprüften Code misst oder nur
  sich selbst. Ein Sanitizer findet nur, was er selbst übersetzt hat; ohne diesen
  Blick ist „grün unter ASan" eine Behauptung.
- 2026-09-02 — **Die Abnahmebedingungen einzeln durchnummeriert abarbeiten und jede
  mit ihrem eigenen mechanischen Aufruf belegen.** Beide Befunde des ersten Laufs
  fielen genau dabei an; beim Lesen des Codes wären sie unsichtbar geblieben, weil
  der Code richtig ist.
- 2026-09-02 — **Bei einer Prüfung nach Rücklauf zuerst den Diff der geänderten
  Dateien ansehen, nicht die Statusnotiz des Bauagenten.** `git show <commit> -- <die
  Dateien aus dem Feld dateien>` beantwortet in einem Aufruf, ob wirklich nur das
  Verlangte geändert wurde — und ob der unberührte Teil noch der ist, den ich beim
  letzten Mal selbst gebaut habe. Dann trägt die Messung von damals weiter.
- 2026-09-02 — **Der Commit-Betreff sagt nicht, was im Commit steht.** Die
  Rücklauf-Behebung an 0004 lag in einem Commit mit fremdem Betreff; der Commit, der
  0004 nennt, enthielt sie nicht. Immer `git log -- <datei>` statt nach dem Betreff
  suchen.

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
- 2026-09-02 — **Die Shell ist nicht verlässlich da; ein Prüfplan, der sie voraussetzt,
  fällt aus.** Im zweiten Lauf waren nur einzelne einfache Aufrufe erlaubt, kein
  `for`, kein `find`, keine verketteten Befehle. Was immer geht: `Glob` für Existenz,
  `Grep` für die Mustervergleiche, `Read` für Linkzeile und `flags.make`, und
  `befunde/uebersetzung-<datum>.md` als fremdgemessener Bau- und Testbeleg. Damit ist
  eine vollständige Prüfung möglich — sie muss nur sagen, was fremdgemessen ist.

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
- 2026-09-02 — **Ungeklärt: Schaltet `-fwrapv` den UBSan-Test auf
  vorzeichenbehafteten Überlauf ab?** Beide stehen in 0016 in jedem Profil. Wenn ja,
  deckt ADR 0011 Maßnahme 2 weniger ab, als sie verspricht. In diesem Lauf nicht
  nachweisbar (kein eigenes Programm möglich); ein Zweizeiler klärt es, sobald das
  geht. Betrifft jedes Kernpaket, das sich auf die Maßnahme statt auf einen
  ausgeschriebenen Wächter verlässt.
