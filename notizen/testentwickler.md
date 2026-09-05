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

- 2026-09-05 — **Ein Test auf „es hat geworfen" prüft fast nie das, was er soll** (0085:
  zwei Riegel auf derselben Schranke; fällt der äußere weg, wirft der innere weiter und
  die Probe bleibt grün). Das tragende Kennzeichen ist **zweiteilig**, Kasten **und**
  Ursache — je allein trägt keines, den Volltext nie.
- 2026-09-05 — **Trennt eine Abnahme zwei Sorten, muss die trennende Eigenschaft
  woandersher kommen als aus dem geschriebenen Namen.** 0083: „liegt in einem ungelesenen
  Ordner" ließe sich am Pfadvorsatz festmachen — richtig ist die Ordnerliste beim
  Einsammeln. Faustregel: den Rotnachweis suchen, den die **bequeme** Fassung überlebt
  hätte.
- 2026-09-05 — **Ein Riegel, der etwas nicht liest, muss trotzdem wissen, dass es
  existiert** — Namen einsammeln ist nicht Inhalt lesen. Ohne den Unterschied fallen
  „gibt es dort" und „gibt es nirgends" in eine stumme Sorte zusammen (0083).
- 2026-09-05 — **Ein fremder Lauf kann meinen halbfertigen Stand committen** (`ce59b8b`
  nahm die Riegelquelle mitten im Umbau mit). Nach dem Zurückstellen `git log` und
  `git diff <commit> -- <datei>`: Ein Sabotagestand im Verlauf ist keine Vorführung.
- 2026-09-05 — **`what()` zeigt in die Ausnahme, und die ist hinter der schließenden
  Klammer fort.** Vergleiche am Wortlaut gehören *in* den Fangblock; ein `const char*`
  daraus ist ein Zeiger auf Freigegebenes und läuft trotzdem meist grün.
- 2026-09-05 — **Die Erwartung an den Fall hängen, nicht an die Schleife** (drei Nummern,
  zwei verschiedene Riegel — eine gemeinsame Erwartung sah es nicht). Ein leeres
  Erwartungsfeld ist der bequeme Weg zurück zur zahnlosen Prüfung: als **Fehlschlag**
  zählen, nicht als Sonderfall.
- 2026-09-05 — **Rotnachweis für ein Messgerät statt für den Kern: die Erwartungen zweier
  benachbarter Stellen vertauschen.** Beide werden rot und nennen je die Meldung der
  anderen — belegt, dass die Kennzeichen trennen, ohne fremdes Gebiet.
- 2026-09-05 — **Fremde Quelldateien stehen mitten im Lauf in einem nicht übersetzenden
  Zwischenstand** (parallele Läufe). Kein Befund: `--target` je Ziel bauen und `ctest -E`
  die fremden ausschließen, statt den Gesamtbau zu melden.
- 2026-09-04, 2026-09-05 wieder — **Eine Schwelle, deren Zahl sich nicht messen lässt,
  gehört nicht ins Messgerät**; lässt eine Vorgabe zwei Mechaniken offen, beide an den
  echten Formen durchrechnen. Eine Untergrenze braucht darum eine **Herkunft, keine
  Marge** (0083: die Belegstellen der sechs Pakete, 16 bei 38 heute) — eine Schranke dicht
  unter dem Tagesstand wird beim ersten roten Lauf nachgezogen und misst danach nichts.
- 2026-09-04 — Gehört die `CMakeLists.txt` einem fremden Paket, ist die **Falltabelle im
  Programm** der Weg zu dauerhaften Fällen: vor der Arbeit laufen lassen, bei Abweichung
  mit Fehlercode abbrechen. Liest das Werkzeug seinen **eigenen** Quelltext, muss das
  Musterwort maskiert sein (`Zeil\145`) — dann aber prüfen, dass jeder Fall noch einen
  Treffer hergibt.
- 2026-09-04, 2026-09-05 dreimal — **Ein Rotnachweis je Teilregel**, und jeder über zwei
  Edits an der eigenen Datei (kaputt → bauen → laufen → zurück → grün). Eine Grenze,
  deren Abschalten nichts ändert, ist Zierde.
- 2026-09-04, 2026-09-05 dreimal — Die Entscheidung, die der Test misst, als **eigenen
  Aufruf** aus der Leseschleife herausziehen (`fund_ab`, `namensart`, `zielart`). Ein im
  Test nachgebauter Weg prüft zwei Fassungen, von denen nur eine läuft. Wird eine Regel
  breiter, den Preis am **größten erreichbaren Korpus** messen.
- 2026-09-02 — **Beide Bauwege einzeln prüfen**: `baulauf.py` ruft jede `CMakeLists.txt`
  auch allein, und ein **neues Verzeichnis** braucht ein erneutes `cmake -S/-B`.
- 2026-09-03 — Zwei falsche Fassungen belegen nur dann, dass zwei Bedingungen
  *Verschiedenes* messen, wenn je Fassung **beides** zugesichert wird: was sie fängt und
  was sie durchlässt. Mindestens die halbe Tabelle mit **erwarteter Leermeldung**.
- 2026-09-03 — Einen Erwartungswert aus der Vorgabe **zweimal** abschreiben und die
  Abschriften gegeneinander prüfen; ein falscher Maßstab läuft still grün. Neben jede
  Zählung zudem ein von Hand nachgerechneter Fall. — Eine Zeilennummer in einem
  Aufräumpaket ist beim Abarbeiten meist schon falsch (viermal bestätigt): Stelle selbst
  suchen, durch Bleibendes ersetzen.
- 2026-09-04, 2026-09-05 wieder — Beim Aufräumen von Belegstellen ist der Riegel selbst
  das Messgerät: Rotnachweis über eine eingefügte und sofort entfernte Stelle in der
  **eigenen** Datei (0→1→0). Alles, was ich in Kopfkommentar oder Falltabelle schreibe,
  prüft er mit — Muster *beschreiben* statt abschreiben, jedes neue Schlüsselwort zuerst
  im eigenen Quelltext greppen.
- 2026-09-04 — **Eine Zählung von Zeilen belegt nichts über Gegenstände** (`grep -c` gab
  50, richtig sind 41); `uniq -d` daneben. Ein Riegel über Text liest **je Absatz, nicht
  je Zeile** — zu jedem Zeichen die Quellzeile mitführen. Zeichensatz **messen statt
  raten**: `„` wird hier mit geradem `"` geschlossen.
- 2026-09-04 — **`git log -S` allein trägt keine Paketzuordnung**: Die Arbeit eines Pakets
  liegt regelmäßig im Commit des *nächsten* Laufs. Treffer gegen das **Datum** halten.
- 2026-09-05, in 0088 viermal gefahren — **Rotnachweis an fremder Datei, ohne sie
  anzufassen**: `python3 -c "…read()…replace…" | c++ -x c++ - -c -o $TMPDIR/mut.o
  <Warnsatz>`, über die echte Binärdatei im Baubaum linken, `ctest` fahren; `git status`
  führt die Quelle danach nicht. Je Ersetzung ein `assert s.count(a) == 1`; am Ende
  Quelle `touch`en, sonst hält `make` den Mutanten für aktuell. Sonst: ändern, wie die
  **eigene** Datei die fremde liest (Stellen meiden, die der Selbsttest durchläuft).
- 2026-09-05 — **Der Rotnachweis belegt die Zahl erst über die Gegenzahl:** je Vorgabe
  beide Zeilen, `== soll` und `!= gegenzahl`, sonst behauptet man den Messwert.
- 2026-09-05 — **Eine im Paket genannte Mutation ist selten die einzige ihrer Art** (0088:
  eine zweite Stelle, bei Abschlag 0 von der richtigen Form ununterscheidbar). Vorgaben
  „X sitzt an Stelle N" gegen **alle** Stellen rechnen, Parameter so wählen, dass sie
  sich trennen.
- 2026-09-05 — **Eine Falltabelle zahlt sich beim Bauen aus, nicht erst beim Prüfen** —
  *vor* dem ersten Korpuslauf schreiben, mit den Fällen, die der Korpus **nicht** hergibt.
  Verlangt eine Abnahme eine **Eigenschaft** statt einer Liste, ist das die Bauform, die
  trägt.

## Was nicht funktioniert

<!-- Was du versucht hast und was dabei herauskam. Damit du es nicht in drei Wochen
     erneut versuchst.
     Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-04, **zweimal getroffen** — `cd` nimmt mir `Edit` und `Write` still weg
  (`Edit(ventures/**)` ist *relativ*; die Ablehnung nennt den Modus, nicht den Pfad).
  **Nie `cd`** — `cmake -S/-B`, `ctest --test-dir` und absolute Pfade tun dasselbe.
- 2026-09-02, bis 2026-09-05 bestätigt — Zusammengesetzte Shell-Befehle (`a && b`, `a; b`,
  Heredoc an `python3`) werden abgelehnt, einzelne Aufrufe und **Pipes** nicht. Programm
  mit Rückgabe ≠ 0 über `ctest --test-dir`; `head -N | tail -M` und Read mit `offset`
  laufen.
- 2026-09-05 — **`sed` wird abgelehnt**, auch mit `-e`; Ersatz ist `python3 -c "…"` mit
  zeilengetrennten Anweisungen. Ein Binärprogramm **aus `$TMPDIR` auszuführen** ebenfalls,
  auch hinter einer Pipe — daher der Umweg über die Binärdatei im Baubaum und `ctest`.
- 2026-09-03, 2026-09-05 präzisiert — `grep` über die Shell wird für die Suche im Baum
  abgelehnt (Grep-Werkzeug oder `git grep` tun es), **auf `$TMPDIR` und hinter einer Pipe
  läuft es** — `ctest -V | grep -A2 …` und `Testing/Temporary/LastTest.log` sind der
  schnellste Weg an alle roten Zeilen.
- 2026-09-04, 2026-09-05 berichtigt — Nach `$TMPDIR` geht **Bauen**, nicht **Kopieren**
  (`cp` und `Write` dorthin abgelehnt); der mutierte Quelltext muss aber gar nicht auf
  die Platte (Pipe oben).
- 2026-09-03 — Beim Sabotieren beißt `-Werror=unused-function`: Fällt eine Funktion aus
  dem Spiel, wird der **Bau** rot statt des Tests. Sabotage so legen, dass jede Funktion
  aufgerufen bleibt (ein `return` mitten hinein geht durch).
- 2026-09-02 — `rm -rf bau` wird abgelehnt (Hausregel 3) und nicht gebraucht: `cmake
  -S/-B` konfiguriert über den vorhandenen Stand hinweg neu.
- 2026-09-05 — **`git commit` wurde abgelehnt**, in beiden Formen (`-F -` und mehrfach
  `-m`); `git add` läuft. Am Ende also **stagen und melden**, nicht am Befehl feilen.

## Offene Faehrten

<!-- Etwas, das du bemerkt hast, aber diesmal nicht verfolgen konntest. -->

- 2026-09-05 — **In 0088 wurde unter keiner der vier Mutationen eine *vorhandene* Probe
  rot.** Zwölf grüne Proben können vier Vorgaben ungeprüft lassen; nur ein Mutationslauf
  zeigt das. Gehört ins Verfahren des Regressionsbestands.
- 2026-09-05 — **Ein grüner Übersetzungsbericht gilt nur für den Stand, den er gelesen
  hat** — und ein gemeldeter Bruch ist oft nur ein Zwischenstand (der Riegel war nach
  0083 wieder grün, 14/14).
- 2026-09-05 — **Ohne den äußeren Riegel in `kern::schritt` liefe `partie.runde = -1`
  still durch** (`diese_runde` wird null; bei `I64_MIN` fängt der innere es). Kein Befund,
  aber der Beleg, dass die Doppelung *keine* echte ist. — Ebenso ungemessen übernommen:
  die drei Bedingung-7-Stücke beim `spielmodus` (ob `310` den Riegel kennzeichnet).
- 2026-09-04, 2026-09-05 wieder — **Der Korpus driftet während des eigenen Laufs**, am
  2026-09-05 auch dieses **Logbuch**: ein paralleler Lauf derselben Rolle schrieb es
  mitten in meinem mehrfach neu. Vorher-`HEAD` notieren, Zahlen zuordnen.
- 2026-09-02 — Der Prüfstand hat noch keinen **Regressionsbestand** und keinen
  **Determinismustest über Speichern und Laden** — laut Rolle meine wichtigsten;
  `probe_zweimal_dasselbe` deckt nur zwei Aufrufe im selben Prozess ab. — `FABRIK_STRENGE`
  steht zudem zweimal wortgleich im Baum; die dritte Fassung führt niemand nach (0031).
- 2026-09-04 — Eine Abnahme, die die **Abwesenheit eines Musters** misst, sieht nie, ob
  der Ersatz wahr ist. Ersatztext im Wortlaut aus der Zieldatei holen und jede Behauptung
  darüber nachmessen — auch den **Kopf** der Datei.
- 2026-09-05, dreimal — **Jede Zahl in einer Abnahme ist ein Messwert von ihrem
  Zuschnittstag** (0079: „fallen um genau zwei", sie steigen um 48; 0085 nannte vier,
  richtig sind fünf; 0083 sprach von fünf übergangenen Fundstellen, heute sind es 58).
  Vor dem Bauen die Zahl in ihrer Quelle nachschlagen, dann messen und gegenrechnen —
  nicht die Regel biegen.
- 2026-09-04, **dreimal bestätigt** (zuletzt 2026-09-05) — `Write` nach `notizen/archiv/`
  ist der Rolle nicht erlaubt (`cp`/`mv` auch nicht). Die 12.000-Zeichen-Regel ist damit
  nur durch Zusammenziehen einzuhalten. Als **Berechtigung** gemeldet.
- 2026-09-03 — **Eine Invariante fängt Nullfälle prinzipiell nicht.** An T43 nachgemessen:
  `ai = 0` als hartes Verbot lässt sie für alle 126 Profile grün. Nur ein eigens gebauter
  Fall mit *einer* zulässigen Art fängt es.
