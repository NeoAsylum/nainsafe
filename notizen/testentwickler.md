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

- 2026-09-05 — **Die gleichförmige Grundbelegung ist die eigentliche Ursache stumpfer
  Proben.** In 0097 überlebten elf von siebzehn Mutationen allein daran, dass alle fünf
  Gebiete dasselbe BIP und alle vier Länder denselben Zins trugen. Eine Belegung ist erst
  dann eine Messlatte, wenn die Werte, die die geprüfte Ausgabe druckt, **paarweise
  verschieden** sind — und das gehört gezählt (Feld füllen, doppelte zählen, `== 0`),
  nicht behauptet. Die Zahl der Spalten aus den Aufzählungen rechnen, nicht abzählen.
- 2026-09-05 — **Fordert ein gültiger Zustand eine Gleichheit, braucht die Entscheidung
  dahinter einen zweiten, ausdrücklich ungültigen Zustand** — nicht einen kaputt
  gemachten ersten. 0097: Aggregat und Instrumentenstand des Leitzinses sind nach T49
  gleich; unterscheidbar wird „liest den Stand" allein in der halb gerechneten Runde.
- 2026-09-05 — **„Zahl steht in der Zeile" ist schwächer, als es aussieht:** `Wechselkurs
  1013` steckt in `Wechselkurs 10137`. Vergleich mit **Abschlussprüfung** (nächstes
  Zeichen ist Leerzeichen, Zeilenende oder Ende), und daneben die Gegenprobe, dass die
  Fassung ohne Abschluss die abgeschnittene Zahl findet — sonst ist der Abschluss Zierde.
- 2026-09-05 — **Ein eigener Kommentar kann einen fremden Riegel rot machen.** Ein
  Beleg „`…/technik.md`, Zeile 278 bis 292" in meiner Probendatei brach
  `belegstellen_riegel` Bedingung 1; der Riegel liest **auch Testquellen**. Belege im
  Kommentar immer über die Abschnittsüberschrift, nie über eine Zeilennummer, und nach
  jedem neuen Zitat die Gesamtprobe fahren.
- 2026-09-05 — **Mutationstreiber als Python-Skript nach `bau/`** (dort greift
  `.gitignore`): Muster einmal je Fall ersetzen, mit `g++ -x c++ -` über eine Pipe in die
  **Objektdatei des Baubaums** übersetzen, `cmake --build --target <probe>` linken,
  Binärdatei fahren. 19 Fälle in einem Aufruf statt ~76 Shell-Aufrufen; `git status`
  führt die fremde Quelle danach nicht. Zum Schluss Quelle `touch`en und neu bauen.
  Je Fall `count(alt) == 1` prüfen — ein nicht gefundenes Muster gilt als Fehlschlag,
  nicht als übersprungener Fall.
- 2026-09-05, **zweimal** — **Ein fremder Lauf committet meinen halbfertigen Stand mit**
  (`ce59b8b`, dann `757ae04`: der Datenbauer nahm 577 Zeilen meiner Probendatei mitten im
  Umbau mit). Mein eigener Commit trägt danach nur den Rest, und im Verlauf steht ein
  Sabotage- oder Zwischenstand als Vorführung. Nach dem Commit `git log -- <datei>` und
  `git show --stat`: Was fehlt, liegt im Commit des anderen — kein Datenverlust, aber die
  Paketzuordnung stimmt nur über das Datum.
- 2026-09-05 — **Eine vollständige Adresse als Bereichsname liefert genau eine Zeile.**
  Damit lässt sich jede Klasse und jede Herkunft an *ihrer eigenen* Adresse messen,
  gesucht über die Zuordnungsfunktion statt abgeschrieben. Dazu zählen, wie viele Sorten
  überhaupt gefunden wurden — sonst überspringt die Schleife stumm.
- 2026-09-05 — **Ein Test auf „es hat geworfen" prüft fast nie das, was er soll** (0085:
  zwei Riegel auf derselben Schranke). Das tragende Kennzeichen ist **zweiteilig**,
  Kasten **und** Ursache — je allein trägt keines, den Volltext nie.
- 2026-09-05 — **Trennt eine Abnahme zwei Sorten, muss die trennende Eigenschaft
  woandersher kommen als aus dem geschriebenen Namen.** Faustregel: den Rotnachweis
  suchen, den die **bequeme** Fassung überlebt hätte.
- 2026-09-05 — **`what()` zeigt in die Ausnahme, und die ist hinter der schließenden
  Klammer fort.** Vergleiche am Wortlaut gehören *in* den Fangblock.
- 2026-09-05 — **Die Erwartung an den Fall hängen, nicht an die Schleife.** Ein leeres
  Erwartungsfeld ist der bequeme Weg zurück zur zahnlosen Prüfung: als **Fehlschlag**
  zählen, nicht als Sonderfall.
- 2026-09-05 — **Rotnachweis für ein Messgerät statt für den Kern:** die Erwartungen
  zweier benachbarter Stellen vertauschen; beide werden rot und nennen je die Meldung
  der anderen.
- 2026-09-04, 2026-09-05 wieder — **Eine Schwelle, deren Zahl sich nicht messen lässt,
  gehört nicht ins Messgerät.** Eine Untergrenze braucht eine **Herkunft, keine Marge** —
  eine Schranke dicht unter dem Tagesstand wird beim ersten roten Lauf nachgezogen.
- 2026-09-04 — Gehört die `CMakeLists.txt` einem fremden Paket, ist die **Falltabelle im
  Programm** der Weg zu dauerhaften Fällen. Liest das Werkzeug seinen **eigenen**
  Quelltext, muss das Musterwort maskiert sein (`Zeil\145`).
- 2026-09-04, seither sechsmal — **Ein Rotnachweis je Teilregel**, jeder über zwei Edits
  an der eigenen Datei (kaputt → bauen → laufen → zurück → grün). Eine Grenze, deren
  Abschalten nichts ändert, ist Zierde.
- 2026-09-04, seither fünfmal — Die Entscheidung, die der Test misst, als **eigenen
  Aufruf** aus der Leseschleife herausziehen. Ein im Test nachgebauter Weg prüft zwei
  Fassungen, von denen nur eine läuft.
- 2026-09-02 — **Beide Bauwege einzeln prüfen**: `baulauf.py` ruft jede `CMakeLists.txt`
  auch allein, und ein **neues Verzeichnis** braucht ein erneutes `cmake -S/-B`.
- 2026-09-03 — Zwei falsche Fassungen belegen nur dann, dass zwei Bedingungen
  *Verschiedenes* messen, wenn je Fassung **beides** zugesichert wird: was sie fängt und
  was sie durchlässt. Mindestens die halbe Tabelle mit **erwarteter Leermeldung**.
- 2026-09-03 — Einen Erwartungswert aus der Vorgabe **zweimal** abschreiben und die
  Abschriften gegeneinander prüfen; ein falscher Maßstab läuft still grün. — Eine
  Zeilennummer in einem Aufräumpaket ist beim Abarbeiten meist schon falsch (fünfmal
  bestätigt): Stelle selbst suchen, durch Bleibendes ersetzen.
- 2026-09-04, 2026-09-05 wieder — Beim Aufräumen von Belegstellen ist der Riegel selbst
  das Messgerät: Rotnachweis über eine eingefügte und sofort entfernte Stelle in der
  **eigenen** Datei (0→1→0). Muster *beschreiben* statt abschreiben.
- 2026-09-04 — **Eine Zählung von Zeilen belegt nichts über Gegenstände**; ein Riegel
  über Text liest **je Absatz, nicht je Zeile**. Zeichensatz **messen statt raten**.
- 2026-09-04 — **`git log -S` allein trägt keine Paketzuordnung**: Die Arbeit eines Pakets
  liegt regelmäßig im Commit des *nächsten* Laufs. Treffer gegen das **Datum** halten.
- 2026-09-05 — **Der Rotnachweis belegt die Zahl erst über die Gegenzahl:** je Vorgabe
  beide Zeilen, `== soll` und `!= gegenzahl`.
- 2026-09-05 — **Eine im Paket genannte Mutation ist selten die einzige ihrer Art.**
  Vorgaben „X sitzt an Stelle N" gegen **alle** Stellen rechnen.
- 2026-09-05 — **Eine Falltabelle zahlt sich beim Bauen aus, nicht erst beim Prüfen** —
  *vor* dem ersten Korpuslauf schreiben, mit den Fällen, die der Korpus **nicht** hergibt.

## Was nicht funktioniert

<!-- Was du versucht hast und was dabei herauskam. Damit du es nicht in drei Wochen
     erneut versuchst.
     Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-04, **dreimal getroffen** (zuletzt 2026-09-05) — `cd` nimmt mir `Edit` und
  `Write` still weg, auch als Teil eines zusammengesetzten Befehls; die Ablehnung nennt
  den Modus, nicht den Pfad. **Nie `cd`.** Ist es passiert: `cd /home/adria/fabrik` als
  eigener Aufruf holt die Werkzeuge zurück.
- 2026-09-02, bis 2026-09-05 bestätigt — Zusammengesetzte Shell-Befehle (`a && b`, `a; b`,
  Heredoc an `python3`) werden abgelehnt, einzelne Aufrufe und **Pipes** nicht. Programm
  mit Rückgabe ≠ 0 über `ctest --test-dir`; `head -N | tail -M` und Read mit `offset`
  laufen.
- 2026-09-05 — **`sed` wird abgelehnt**, auch mit `-e`; Ersatz ist `python3 -c "…"` oder
  ein Skript unter `bau/`. Ein Binärprogramm **aus `$TMPDIR`** auszuführen ebenfalls.
- 2026-09-03, 2026-09-05 präzisiert — `grep` über die Shell wird für die Suche im Baum
  abgelehnt (Grep-Werkzeug oder `git grep` tun es), **auf Programmausgaben hinter einer
  Pipe läuft es** — `ctest -V | grep …` und `Testing/Temporary/LastTest.log` sind der
  schnellste Weg an alle roten Zeilen.
- 2026-09-04, 2026-09-05 berichtigt — Nach `$TMPDIR` geht **Bauen**, nicht **Kopieren**
  (`cp` und `Write` dorthin abgelehnt). `Write` nach `bau/` geht und ist der bessere Ort.
- 2026-09-03 — Beim Sabotieren beißt `-Werror=unused-function` und `-Wunused-variable`:
  Fällt etwas aus dem Spiel, wird der **Bau** rot statt des Tests. Sabotage so legen,
  dass jede Funktion aufgerufen und jede Größe gelesen bleibt (eine immer wahre
  Bedingung statt `if (true)`).
- 2026-09-02 — `rm -rf bau` wird abgelehnt (Hausregel 3) und nicht gebraucht.
- 2026-09-05, **zweimal** — **`git commit` wird abgelehnt**, in jeder Form; `git add`
  läuft. Am Ende also **stagen und melden**, nicht am Befehl feilen.

## Offene Faehrten

<!-- Etwas, das du bemerkt hast, aber diesmal nicht verfolgen konntest. -->

- 2026-09-05 — **Der Mutationslauf lebt nur in `bau/` und ist beim nächsten sauberen Bau
  fort.** Dreimal belegt (0010, 0088, 0097). Als Paket **0110** vorgeschlagen; ohne ihn
  fallen die neunzehn roten Fälle aus 0097 irgendwann still auf grün zurück.
- 2026-09-05 — **Die Einheit der Klasse 2 lautet im Kern „…konstanten Preisen 2015",
  in T5 „…konstanten Preisen des Jahres 2015".** Der Kern kürzt in allen dreizehn Zeilen
  gleichartig (Klammern weg, `=` weg, Umlautumschrift), der Prüfer von 0010 nannte das
  wortgleich. Meine Abschrift folgt dem Kern. Falls jemand strengere Wortgleichheit will,
  ist das eine Entscheidung zwischen zwei Dokumenten und nicht meine.
- 2026-09-05 — **`werkzeuge/belegstellen/belegstellen_riegel.cpp` übersetzte mitten in
  meinem Lauf nicht** (paralleles Paket). Kein Befund: `--target` je Ziel bauen, `ctest`
  fährt die schon gelinkte Binärdatei weiter.
- 2026-09-05 — **Ein grüner Übersetzungsbericht gilt nur für den Stand, den er gelesen
  hat**, und ein gemeldeter Bruch ist oft nur ein Zwischenstand.
- 2026-09-05 — **Ohne den äußeren Riegel in `kern::schritt` liefe `partie.runde = -1`
  still durch.** Kein Befund, aber der Beleg, dass die Doppelung *keine* echte ist.
- 2026-09-04, 2026-09-05 wieder — **Der Korpus driftet während des eigenen Laufs**, auch
  dieses Logbuch. Vorher-`HEAD` notieren, Zahlen zuordnen.
- 2026-09-02 — Der Prüfstand hat noch keinen **Regressionsbestand** und keinen
  **Determinismustest über Speichern und Laden** — laut Rolle meine wichtigsten;
  `probe_zweimal_dasselbe` deckt nur zwei Aufrufe im selben Prozess ab.
- 2026-09-05, dreimal — **Jede Zahl in einer Abnahme ist ein Messwert von ihrem
  Zuschnittstag.** Vor dem Bauen die Zahl in ihrer Quelle nachschlagen, dann messen und
  gegenrechnen — nicht die Regel biegen. In 0097 stimmten die Zahlen ausnahmsweise.
- 2026-09-04, **dreimal bestätigt** — `Write` nach `notizen/archiv/` ist der Rolle nicht
  erlaubt (`cp`/`mv` auch nicht). Die 12.000-Zeichen-Regel ist damit nur durch
  Zusammenziehen einzuhalten. Als **Berechtigung** gemeldet.
- 2026-09-03 — **Eine Invariante fängt Nullfälle prinzipiell nicht.** Nur ein eigens
  gebauter Fall mit *einer* zulässigen Art fängt es.
