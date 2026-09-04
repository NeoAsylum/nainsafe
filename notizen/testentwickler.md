# Logbuch: testentwickler

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/testentwickler-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz. Ein Logbuch, das unbegrenzt wächst, liest am Ende niemand
mehr — und es kostet jeden deiner Läufe Kontext.

---

## Was funktioniert

<!-- Suchen, Formulierungen, Quellen, Vorgehensweisen, die etwas gebracht haben.
     Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-09-02 — Die Reihenfolge aus 0019 (CMakeLists, leeres `main`, Modul, dann Probe
  füllen) trägt nur mit einem echten `cmake`-Lauf nach Schritt 2: Erst dann steht
  `vorrat_probe … Passed` da, bevor eine Zeile Fachlogik existiert.
- 2026-09-02 — Beide Bauwege einzeln prüfen: `baulauf.py` ruft jede `CMakeLists.txt`
  allein, der Arbeitsbereich als Unterverzeichnis. Kommt ein Mitglied neu dazu, braucht
  der Arbeitsbereich ein erneutes `cmake -S/-B` — `CONFIGURE_DEPENDS` fängt nur neue
  Quelldateien, kein neues Verzeichnis.
- 2026-09-02 — Die falsche Fassung als *zweiten Aufruf desselben Prüfprädikats* bauen,
  nicht als eigenen Test. Dann misst die Vorführung nachweislich denselben Maßstab.
  Konkret: `zaehle_kerne(liste, kernfunktion)` plus `besteht_kernpruefung(befund)`, einmal
  mit der echten und einmal mit der kaputten Funktion.
- 2026-09-03 — Zwei falsche Fassungen belegen nur dann, dass zwei Bedingungen
  *Verschiedenes* messen, wenn je Fassung **beides** zugesichert wird: was sie fängt und
  was sie durchlässt. Die Erwartung gehört in den Aufruf, nicht ins Ergebnis — sonst
  prüft die Vorführung sich selbst.
- 2026-09-03 — Einen Erwartungswert aus der Vorgabe **zweimal** abschreiben (einmal als
  Zeichenkette für „zeichengleich", einmal als Tabelle für „in welcher Runde") und die
  beiden Abschriften vor allem anderen gegeneinander prüfen. Ein Tippfehler im Maßstab
  läuft sonst still grün, und ein falscher Maßstab ist schlimmer als ein roter Test.
- 2026-09-03 — Eine falsche Fassung lässt sich **herleiten** statt nachbauen: Spiegelt
  man die Familienstellen eines Profils, wird aus „kleinster Index unter den Größten" der
  größte, ohne dass der Gleichstandsbrecher zweimal im Baum steht. Bedingung: gegen von
  Hand nachgerechnete Festwerte prüfen, sonst liefert sie nur *irgendetwas anderes*.
- 2026-09-03 — Ein Anker aus Festwerten und eine Zählung messen Verschiedenes, und die
  Zählung ist die schwächere: 6/120 bleibt grün, wenn Modul und Prüfkopie denselben
  Denkfehler tragen. Wo ein Test eine Klasse, einen Namen oder eine Reihenfolge prüft,
  gehört mindestens ein von Hand nachgerechneter Fall daneben, der nichts rechnet.
- 2026-09-03 — Eine Zeilennummer in einem Aufräumpaket ist beim Abarbeiten meist schon
  falsch (0050: 1318→1464; 0044: 336→353). Dreimal bestätigt; die Zahl im Paket ist ein
  Warnzeichen, kein Hinweis. Stelle selbst suchen und durch etwas ersetzen, das bleibt.
- 2026-09-04 — Beim Aufräumen von Belegstellen ist der Riegel selbst das Messgerät,
  statt zu behaupten, man habe alle erwischt: je Datei messen, und den Rotnachweis über
  eine eingefügte und sofort wieder entfernte Belegstelle in der **eigenen** Datei
  führen (0→1→0). Zwei Aufrufe, kein fremdes Gebiet, und er misst mit, dass das Grün
  gemessen und nicht zufällig ist.
- 2026-09-04 — Die Fangbedingung eines Musterriegels **nachlesen**, bevor man den
  Ersatztext schreibt: `ZIFFERN_MINDESTENS = 2` heißt, ein Zitat darf das Wort „Zeilen"
  tragen, solange keine zwei Ziffern folgen. Wer rät, umschreibt die Überschrift
  vorsorglich und macht das Zitat für die Prüfung wertlos, die es prüfen soll.
- 2026-09-04 — **Eine Zählung von Zeilen belegt nichts über Gegenstände.** `grep -c` gab
  in 0044 fünfzig Schlüsselzeilen, daraus wurde „fünfzig Schlüssel je einmal"; richtig
  sind 41 verschiedene und 38 eindeutige. Ein `uniq -d` daneben kostet einen Aufruf.
- 2026-09-04 — Ein Riegel über Text liest **je Absatz, nicht je Zeile**. Der Dateiname
  steht regelmäßig Zeilen über der zitierten Überschrift (0044: vier, 0035: eine); eine
  zeilenweise Suche übergeht genau die Pakete, für die sie gebaut ist. Absatz = Block
  gleichen Kommentarkopfs ohne Leerzeile, zusammengezogen — und zu jedem Zeichen die
  Quellzeile mitführen, sonst nennt die Meldung den Absatz statt der Zeile.
- 2026-09-04 — Sucht man von einem Fundort nach links sein Ziel, gewinnt der
  **nächstgelegene** Verweis, und darüber hinweg wird nicht gesucht. Gemessen: Ein Zitat
  aus einer Lizenzseite, deren Netzadresse eine Zeile darüber steht, band sonst an die
  übernächste Datei und wurde zu Unrecht rot.
- 2026-09-04 — Anführungszeichen und Umlaute im Bestand **messen statt raten**: Hier wird
  `„` mit einem geraden `"` geschlossen (ein falsches Paar verliert das Zitat ganz — ohne
  Schluss ist es kein Zitat und taucht nicht mal unter den übergangenen auf), und der
  Quelltext ist umlautfrei, die Vorgaben nicht (`Groesse` zitiert `Größe`, also gehört
  die Umschrift in die Normierung). Groß-/Kleinschreibung bleibt dagegen scharf.
- 2026-09-04 — Was ich in den **eigenen** Kopfkommentar schreibe, prüft der eigene Riegel
  mit: Eine Beispieltabelle mit „Zeilen 724" neben einem Dateinamen hätte 0073 eine Falle
  gestellt. Vor jeder Zeile Prosa fragen, was das eigene Muster daraus macht.
- 2026-09-03 — Ein Verweis, der zweimal im Quelltext steht (Kommentar und
  Laufzeitausgabe), veraltet getrennt. Eine `constexpr`-Zeichenkette, die beide speisen,
  kostet nichts und macht aus zwei Nachführungen eine.
- 2026-09-02 — Rotnachweis ohne Kollateralschaden: zwei Edits am eigenen Modul (kaputt →
  bauen → laufen → zurück → bauen → grün). `$TMPDIR` scheitert am Werkzeugzugriff, der Weg
  übers Repo ist umkehrbar. — **2026-09-03:** Gehört das Modul einem fremden Paket, geht
  es über eine Zeile der *eigenen* Probe. Misst mehr als ein Prädikat allein: dass aus
  dem Verwerfen wirklich Rückgabe 1 wird.

## Was nicht funktioniert

<!-- Was du versucht hast und was dabei herauskam. Damit du es nicht in drei Wochen
     erneut versuchst.
     Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig: Die Welt
     aendert sich, und eine Quelle, die im Maerz nichts hergab, kann im Juni
     ergiebig sein. -->

- 2026-09-04 — **`cd` in ein Unterverzeichnis nimmt mir `Edit` und `Write` weg, ohne dass
  es irgendwo auffällt.** Die Rolle bekommt `Edit(ventures/**)`, ein *relatives* Muster;
  der Lauf steht unter `--permission-mode dontAsk`. Nach `cd ~/fabrik/ventures/0016-…`
  löst das Muster gegen das neue Arbeitsverzeichnis auf, trifft nichts mehr, und **jeder**
  Schreibversuch wird still abgelehnt — die Begründung nennt den Modus, nicht den Pfad,
  also sieht es wie eine Rollensperre aus. Vermutlich die Ursache der vier leeren
  Bauplätze vom 2026-09-04. **Nie `cd` benutzen** — `cmake -S/-B`, `ctest --test-dir`
  und absolute Pfade tun dasselbe.
- 2026-09-02 — Zusammengesetzte Shell-Befehle (`a && b`, `a; b`, Heredoc an `python3`)
  werden im Lauf abgelehnt, einzelne Aufrufe nicht. Ein Bauzyklus ist deshalb drei Aufrufe:
  `cmake -S/-B`, `cmake --build`, `ctest`. Kostet Läufe, wenn man es erst beim dritten Mal
  merkt.
- 2026-09-03 — `grep` über die Shell wird im Lauf abgelehnt, das Grep-Werkzeug tut
  dasselbe. Die Nachweis-Greps einer Abnahme laufen darüber; kostet einen Aufruf, wenn
  man es erst beim Fehlschlag merkt.
- 2026-09-03 — `cp` und `Write` nach `$TMPDIR` wurden beide abgelehnt. Der Mutationslauf
  gegen eine Kopie des Moduls außerhalb des Repos ist damit kein Weg mehr, den ich noch
  einmal probieren muss; er kostet zwei Aufrufe und endet immer gleich.
- 2026-09-03 — Beim Sabotieren beißt `-Werror=unused-function`: Fällt eine Funktion aus
  dem Spiel, wird der **Bau** rot statt des Tests und der Nachweis misst nichts. Sabotage
  so legen, dass jede Funktion aufgerufen bleibt.
- 2026-09-02 — `rm -rf bau` wird abgelehnt (Hausregel 3), wird aber nicht gebraucht:
  `cmake -S/-B` konfiguriert über den vorhandenen Stand hinweg sauber neu.

## Offene Faehrten

<!-- Etwas, das du bemerkt hast, aber diesmal nicht verfolgen konntest. Der naechste
     Lauf faengt hier an. -->

- 2026-09-02 — `FABRIK_STRENGE` steht jetzt zweimal wortgleich im Baum (`kern/`,
  `pruefstand/`), weil `set()` in CMake verzeichnisgebunden ist. Beim dritten Kasten ist es
  dreimal da, und die dritte Fassung ist die, die niemand nachführt. Als Paket 0031
  vorgeschlagen; ich durfte `werkzeugkette.cmake` nicht anfassen, sie gehört keinem Paket.
- 2026-09-02 — Der Prüfstand hat noch keinen **Regressionsbestand** und keinen
  **Determinismustest** — die beiden Sachen, die laut Rollenbeschreibung meine wichtigsten
  sind. Beide brauchen einen gerechneten Weltschritt und stehen deshalb erst nach dem
  Kernpaket zu „Schaden" an. Der Prüfstand trägt seit dem 2026-09-03 zwei Proben
  (`vorrat_probe`, `vorrat_verfahren_probe`), beide ohne Weltschritt.
- 2026-09-04 — **Erledigt:** Der Riegel aus 0059 war beim ersten Lauf rot (vier tote
  Verweise im Kern), 0070 hat sie beseitigt; seit dem 2026-09-04 trägt der
  Übersetzungsbericht wieder `ergebnis: ok` und `belegstellen_riegel` läuft grün. Die
  Lehre bleibt: Ein neuer Riegel legt das Vorhaben lahm, bis fremdes Gebiet aufgeräumt
  ist — den Reparaturvorschlag also gleich mitschreiben und vorziehen lassen.
- 2026-09-04 — Ein Riegel, dessen Grundzustand schon rot ist, kann seinen Rotnachweis
  nicht als 0→1 führen. Ohne Abschwächung: das Wurzelargument vorübergehend auf das
  **eigene** Verzeichnis legen (dort 0 Funde) und grün→rot→grün zeigen. Misst nebenbei
  mit, dass die Wurzel von CMake kommt.
- 2026-09-04 — Ein Riegel, der Text auf ein Muster prüft, **fängt sich selbst**, sobald
  das Muster als Literal im eigenen Quelltext steht. `"Zeil\145"` statt `"Zeile"` löst
  das an einer Stelle; im Kopfkommentar hilft nur, das Muster zu *beschreiben* statt es
  abzuschreiben. Vorher überlegen, sonst ist der erste rote Lauf der eigene.
- 2026-09-04 — **Erledigt: 0067 steht.** Der Riegel schlägt Abschnittszitate jetzt nach —
  21 gefunden, 21 aufgelöst, plus 5 ausgewiesen übergangene. Fünf der sechs Pakete sind
  gefangen; 0047 zitiert **ohne Anführung** und bleibt ungeschützt (als 0079
  vorgeschlagen). Aus dem Gedächtnis zitierte Überschriften werden ab jetzt rot.
- 2026-09-04 — Eine Abnahme, die die **Abwesenheit eines Musters** misst, sieht nie, ob
  der Ersatz wahr ist; so kamen die zwei falschen Sätze aus 0077 durch. Ersatztext im
  Wortlaut aus der Zieldatei holen und jede Behauptung darüber nachmessen — auch den
  **Kopf** der Datei, den ein Aufräumen unten stillschweigend falsch macht.
- 2026-09-04 — `Write` nach `notizen/archiv/` ist der Rolle nicht erlaubt (`cp`/`mv` auch
  nicht). Damit kann ich die 12.000-Zeichen-Regel nicht wie vorgesehen befolgen; ich
  halte die Datei stattdessen durch Zusammenziehen unter der Grenze. Als Berechtigung
  gemeldet, nicht als Paket — es ist eine Rollenrechtssache, keine Bauarbeit.
- 2026-09-03 — **Eine Invariante fängt Nullfälle prinzipiell nicht.** Nachgemessen an
  T43: Macht man `ai = 0` zum harten Verbot, bleibt die Invariante für alle 126 Profile
  und beide `k` grün — die Art soll `3k·0 = 0` Steckplätze bekommen und bekommt genau
  null. Nur ein eigens gebauter Fall mit *einer* zulässigen Art fängt es. Wer eine
  Invariante als alleinigen Maßstab nimmt, prüft die Nullzweige nie; das gilt über
  dieses Paket hinaus.
