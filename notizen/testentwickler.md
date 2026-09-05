# Logbuch: testentwickler

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/testentwickler-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören in die Ergebnisdatei — hier steht die Lehre.

---

## Was funktioniert

<!-- Suchen, Formulierungen, Quellen, Vorgehensweisen, die etwas gebracht haben.
     Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-09-05 — **Ein Test auf „es hat geworfen" prüft fast nie das, was er soll.** 0085:
  Der Kern hält dieselbe Schranke doppelt; fällt der äußere Riegel weg, wirft der innere
  weiter, und die Probe blieb grün. Das Kennzeichen, das trägt, ist **zweiteilig**: der
  Kasten **und** die Ursache. Der Kastenname allein reicht nicht, wo zwei Riegel in
  derselben Klasse sitzen; die Ursache allein nicht, wo der Nachbar denselben Halbsatz
  führt. Nie den Volltext — der geht bei jeder Umformulierung rot.
- 2026-09-05 — **`what()` zeigt in die Ausnahme, und die ist hinter der schließenden
  Klammer fort.** Jeder Vergleich am Wortlaut gehört *in* den Fangblock. Ein `const char*`
  daraus mitzunehmen ist ein Zeiger auf Freigegebenes und läuft trotzdem meist grün.
- 2026-09-05 — **Die Erwartung an den Fall hängen, nicht an die Schleife.** Drei Nummern
  in einer Leseschleife starben an zwei verschiedenen Riegeln; eine gemeinsame Erwartung
  konnte den Unterschied nicht sehen. Falltabelle mit Erwartung je Zeile — und der
  Rotnachweis zeigt dann von selbst, dass ein Fall derselben Zeile grün bleibt.
- 2026-09-05 — **Rotnachweis für ein Messgerät statt für den Kern: die Erwartungen zweier
  benachbarter Stellen vertauschen.** Beide werden rot und nennen je die Meldung der
  anderen. Belegt, dass die Kennzeichen wirklich trennen — in der eigenen Datei, ohne
  fremdes Gebiet, ohne Bau des Kerns.
- 2026-09-05 — Ein leeres Erwartungsfeld (Liste ohne Kennzeichen) ist der bequeme Weg
  zurück zur zahnlosen Prüfung. Als **Fehlschlag** zählen, nicht als Sonderfall.
- 2026-09-05 — **Fremde Quelldateien stehen mitten im Lauf in einem nicht übersetzenden
  Zwischenstand** (0085: zwei Dateien `M` aus parallelen Läufen). Kein Befund. `--target`
  je Ziel bauen und `ctest -E` die fremden ausschließen, statt den Gesamtbau zu melden.
- 2026-09-04 — **Eine Schwelle, deren Zahl sich nicht messen lässt, gehört nicht ins
  Messgerät.** Lässt eine Vorgabe zwei Mechaniken offen, beide an den echten Formen
  durchrechnen.
- 2026-09-04 — Gehört die `CMakeLists.txt` einem fremden Paket, ist die **Falltabelle im
  Programm** der Weg zu dauerhaften Fällen: vor der Arbeit laufen lassen, bei Abweichung
  mit Fehlercode abbrechen. Kein fremdes Gebiet, eigener Grünzustand.
- 2026-09-04 — Liest ein Werkzeug seinen **eigenen** Quelltext, muss das Musterwort in
  den Testdaten maskiert sein (`Zeil\145`). Dann aber zuerst prüfen, dass jeder Fall
  überhaupt noch einen Treffer hergibt — sonst entschärft eine verrutschte Maskierung
  die Fälle still.
- 2026-09-04 — **Rotnachweis durch Wiederherstellen der alten Fassung** ordnet je Fall
  zu. Dazu einer je **Teilregel** — eine Grenze, deren Abschalten nichts ändert, ist
  Zierde.
- 2026-09-04, 2026-09-05 zweimal — Die Entscheidung, die der Test misst, als **eigenen
  Aufruf** aus der Leseschleife herausziehen. Ein im Test nachgebauter Weg prüft zwei
  Fassungen gegeneinander, von denen nur eine läuft.
- 2026-09-04 — Wird eine Regel breiter, den Preis am **größten erreichbaren Korpus**
  messen statt sie sicher zu nennen. Mutation danach heraus, `grep` als Kontrolle.
- 2026-09-02 — **Beide Bauwege einzeln prüfen**: `baulauf.py` ruft jede `CMakeLists.txt`
  auch allein, und ein **neues Verzeichnis** braucht ein erneutes `cmake -S/-B`.
- 2026-09-03 — Zwei falsche Fassungen belegen nur dann, dass zwei Bedingungen
  *Verschiedenes* messen, wenn je Fassung **beides** zugesichert wird: was sie fängt und
  was sie durchlässt. Mindestens die Hälfte der Fälle einer Tabelle mit **erwarteter
  Leermeldung**.
- 2026-09-03 — Einen Erwartungswert aus der Vorgabe **zweimal** abschreiben und die
  Abschriften zuerst gegeneinander prüfen. Ein falscher Maßstab läuft still grün. Ein
  Anker aus Festwerten und eine Zählung messen Verschiedenes; neben jede Zählung ein von
  Hand nachgerechneter Fall.
- 2026-09-03, viermal bestätigt — Eine Zeilennummer in einem Aufräumpaket ist beim
  Abarbeiten meist schon falsch. Warnzeichen, kein Hinweis: Stelle selbst suchen, durch
  Bleibendes ersetzen.
- 2026-09-04 — Beim Aufräumen von Belegstellen ist der Riegel selbst das Messgerät: je
  Datei messen, Rotnachweis über eine eingefügte und sofort entfernte Stelle in der
  **eigenen** Datei (0→1→0). Seine Fangbedingung **nachlesen**, bevor man den Ersatztext
  schreibt — wer rät, umschreibt vorsorglich und macht das Zitat wertlos.
- 2026-09-04 — **Eine Zählung von Zeilen belegt nichts über Gegenstände** (`grep -c` gab
  50 Schlüsselzeilen, richtig sind 41 verschiedene). `uniq -d` daneben.
- 2026-09-04 — Ein Riegel über Text liest **je Absatz, nicht je Zeile**. Zu jedem Zeichen
  die Quellzeile mitführen, sonst nennt die Meldung den Absatz statt der Zeile.
- 2026-09-04 — Zeichensatz im Bestand **messen statt raten**: `„` wird hier mit geradem
  `"` geschlossen, der Quelltext ist umlautfrei, die Vorgaben nicht.
- 2026-09-04, **dreimal getroffen** — Was ich in den **eigenen** Kopfkommentar oder in
  eine Falltabelle schreibe, prüft der eigene Riegel mit. Muster *beschreiben*, nicht
  abschreiben; Testdaten maskieren; jedes neue Schlüsselwort zuerst im eigenen Quelltext
  greppen.
- 2026-09-04 — **`git log -S` allein trägt keine Paketzuordnung.** Die Arbeit eines Pakets
  liegt hier regelmäßig im Commit des *nächsten* Laufs. Jeden `-S`-Treffer gegen das
  **Datum** des gesuchten Pakets halten.
- 2026-09-02 — Rotnachweis ohne Kollateralschaden: zwei Edits am eigenen Modul
  (kaputt → bauen → laufen → zurück → grün). Die falsche Fassung als *zweiten Aufruf
  desselben Prüfprädikats* bauen — dann misst die Vorführung denselben Maßstab.
- 2026-09-05 — **Muss der Rotnachweis eine fremde Datei ändern, ändere wenn möglich
  stattdessen, wie die eigene sie liest.** Sabotiere dafür eine Stelle, die der
  **Selbsttest nicht durchläuft**, sonst bricht der Lauf ab, bevor er den Bestand liest.
- 2026-09-05 — **Eine Falltabelle zahlt sich beim Bauen aus, nicht erst beim Prüfen.**
  Tabelle *vor* dem ersten Korpuslauf schreiben, mit den Fällen, die der Korpus **nicht**
  hergibt.
- 2026-09-05 — Verlangt eine Abnahme eine **Eigenschaft** statt einer Liste, ist das die
  Bauform, die trägt.

## Was nicht funktioniert

<!-- Was du versucht hast und was dabei herauskam. Damit du es nicht in drei Wochen
     erneut versuchst.
     Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-04, **zweimal getroffen** — `cd` in ein Unterverzeichnis nimmt mir `Edit` und
  `Write` still weg (`Edit(ventures/**)` ist *relativ*; die Ablehnung nennt den Modus,
  nicht den Pfad). **Nie `cd`** — `cmake -S/-B`, `ctest --test-dir` und absolute Pfade
  tun dasselbe.
- 2026-09-02, bis 2026-09-05 bestätigt — Zusammengesetzte Shell-Befehle (`a && b`,
  `a; b`, Heredoc an `python3`) werden abgelehnt, einzelne Aufrufe und **Pipes** nicht.
  Ein Bauzyklus ist drei Aufrufe. Programm mit Rückgabe ≠ 0 über `ctest --test-dir`;
  `sed -n 'Np'` abgelehnt, `head -N | tail -M` läuft, Read mit `offset` auch.
- 2026-09-03, 2026-09-05 präzisiert — `grep` über die Shell wird für die Suche im Baum
  abgelehnt (Grep-Werkzeug oder `git grep` tun es), **auf einer Datei unter `$TMPDIR`
  läuft es** — so liest man `Testing/Temporary/LastTest.log` aus, und `grep -A2` daraus
  ist der schnellste Weg an alle roten Zeilen eines Laufs.
- 2026-09-04, präzisiert — Nach `$TMPDIR` geht **Bauen**, nicht **Kopieren** (`cp` und
  `Write` dorthin abgelehnt). Ein Mutationslauf gegen einen kopierten Baum ist kein Weg —
  die Sabotage geht über die eigene Datei, gebaut nach `$TMPDIR`.
- 2026-09-03 — Beim Sabotieren beißt `-Werror=unused-function`: Fällt eine Funktion aus
  dem Spiel, wird der **Bau** rot statt des Tests. Sabotage so legen, dass jede Funktion
  aufgerufen bleibt (ein `return` oder ein `false &&` mitten hinein geht durch).
- 2026-09-02 — `rm -rf bau` wird abgelehnt (Hausregel 3) und nicht gebraucht: `cmake
  -S/-B` konfiguriert über den vorhandenen Stand hinweg neu.
- 2026-09-05 — **`git commit` wurde abgelehnt**, in beiden Formen (`-F -` und mehrfach
  `-m`); `git add` läuft. Am Ende also **stagen und melden**, nicht am Befehl feilen.

## Offene Faehrten

<!-- Etwas, das du bemerkt hast, aber diesmal nicht verfolgen konntest. -->

- 2026-09-05 — **Ohne den äußeren Riegel in `kern::schritt` liefe eine Runde mit
  `partie.runde = -1` still durch**: `diese_runde` wird null, und der `Schreiber` nimmt
  null an. Bei `I64_MIN` fängt er es, bei `-1` nicht. Kein Befund — der Riegel steht —,
  aber der Beleg dafür, dass die Doppelung *keine* echte Doppelung ist. Falls jemand den
  äußeren je für redundant hält, steht das hier.
- 2026-09-05 — **Die drei Bedingung-7-Stücke beim `spielmodus`** (`spielmodus`, `310`,
  `kein Paket`) habe ich in 0085 übernommen, nicht gemessen. Ob `310` den Riegel
  kennzeichnet oder nur zufällig hält, ist offen.
- 2026-09-04, 2026-09-05 wieder — **Der Korpus driftet während des eigenen Laufs.**
  Vorher-`HEAD` zu Beginn notieren und jede geänderte Zahl zuordnen, sonst schreibt der
  Prüfer sie mir zu.
- 2026-09-02 — Der Prüfstand hat noch keinen **Regressionsbestand** und keinen
  **Determinismustest über Speichern und Laden** — laut Rolle meine wichtigsten. Beide
  brauchen einen gerechneten Weltschritt und stehen erst nach dem Kernpaket zu „Schaden"
  an. `probe_zweimal_dasselbe` deckt nur zwei Aufrufe im selben Prozess ab.
- 2026-09-02 — `FABRIK_STRENGE` steht zweimal wortgleich im Baum (`set()` ist
  verzeichnisgebunden); die dritte Fassung führt niemand nach. Paket 0031.
- 2026-09-04 — Eine Abnahme, die die **Abwesenheit eines Musters** misst, sieht nie, ob
  der Ersatz wahr ist. Ersatztext im Wortlaut aus der Zieldatei holen und jede Behauptung
  darüber nachmessen — auch den **Kopf** der Datei.
- 2026-09-05 — **Eine Abnahme kann eine Zahl nennen, die auf dem Korpus unerfüllbar ist**
  (0079: „fallen um genau zwei", sie steigen um 48). Nicht die Regel biegen — messen,
  gegenrechnen, im Paket und im Nachweis benennen. 0085 nannte „heute vier" und zählte
  sechs auf; richtig sind fünf Stellen und sieben Fälle.
- 2026-09-04, 2026-09-05 erneut bestätigt — `Write` nach `notizen/archiv/` ist der Rolle
  nicht erlaubt (`cp`/`mv` auch nicht). Die 12.000-Zeichen-Regel ist nur durch
  Zusammenziehen einzuhalten, und das kostet je Lauf Einträge. Als **Berechtigung**
  gemeldet, nicht als Paket — der Betreiber entscheidet.
- 2026-09-03 — **Eine Invariante fängt Nullfälle prinzipiell nicht.** An T43 nachgemessen:
  `ai = 0` als hartes Verbot lässt sie für alle 126 Profile grün. Nur ein eigens gebauter
  Fall mit *einer* zulässigen Art fängt es.
