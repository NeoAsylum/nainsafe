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

- 2026-09-04 — **Eine Schwelle, deren Zahl sich nicht messen lässt, gehört nicht ins
  Messgerät.** 0073: Abstand-in-Zeichen gegen Satzgrenze — die echten Formen lagen 17
  und 47 Zeichen entfernt, jede Schranke darüber wäre geraten. Lässt eine Vorgabe zwei
  Mechaniken offen, beide an den echten Formen durchrechnen, bevor man wählt.
- 2026-09-04 — Gehört die `CMakeLists.txt` einem fremden Paket, ist die **Falltabelle im
  Programm** der Weg zu dauerhaften Fällen: vor der Arbeit laufen lassen, bei Abweichung
  mit Fehlercode abbrechen. Kein fremdes Gebiet, nicht vergessbar, eigener Grünzustand.
- 2026-09-04 — Liest ein Werkzeug seinen **eigenen** Quelltext, muss das Musterwort in
  den Testdaten maskiert sein (`Zeil\145`). Dann aber zuerst prüfen, dass jeder Fall
  überhaupt noch einen Treffer hergibt — sonst entschärft eine verrutschte Maskierung
  die Fälle still, und acht grüne Fälle messen nichts.
- 2026-09-04 — **Rotnachweis durch Wiederherstellen der alten Fassung** ordnet je Fall
  zu (0073: genau die vier fielen, die die Verbreiterung verlangt). Dazu einer je
  **Teilregel** — eine Grenze, deren Abschalten nichts ändert, ist Zierde.
- 2026-09-04, 2026-09-05 wieder — Die Entscheidung, die der Test misst, als **eigenen
  Aufruf** aus der Leseschleife herausziehen (`fund_ab`, `namensart`). Ein im Test
  nachgebauter Weg prüft zwei Fassungen gegeneinander, von denen nur eine läuft.
- 2026-09-04 — Wird eine Regel breiter, den Preis am **größten erreichbaren Korpus**
  messen statt sie sicher zu nennen. Mutation danach heraus, `grep` als Kontrolle.
- 2026-09-02 — Reihenfolge aus 0019 (CMakeLists, leeres `main`, Modul, dann Probe) trägt
  nur mit echtem `cmake`-Lauf nach Schritt 2. **Beide Bauwege einzeln prüfen** —
  `baulauf.py` ruft jede `CMakeLists.txt` auch allein; ein **neues Verzeichnis** braucht
  ein erneutes `cmake -S/-B`.
- 2026-09-02 — Die falsche Fassung als *zweiten Aufruf desselben Prüfprädikats* bauen —
  dann misst die Vorführung nachweislich denselben Maßstab.
- 2026-09-03 — Zwei falsche Fassungen belegen nur dann, dass zwei Bedingungen
  *Verschiedenes* messen, wenn je Fassung **beides** zugesichert wird: was sie fängt und
  was sie durchlässt; die Erwartung gehört in den Aufruf. — 2026-09-04 verschärft:
  mindestens die Hälfte der Fälle einer Tabelle mit **erwarteter Leermeldung**.
- 2026-09-03 — Einen Erwartungswert aus der Vorgabe **zweimal** abschreiben und die
  Abschriften zuerst gegeneinander prüfen. Ein falscher Maßstab läuft still grün.
- 2026-09-03 — Eine falsche Fassung lässt sich **herleiten** statt nachbauen
  (Familienstellen spiegeln), aber nur gegen von Hand nachgerechnete Festwerte.
- 2026-09-03 — Ein Anker aus Festwerten und eine Zählung messen Verschiedenes; die
  Zählung ist die schwächere (6/120 bleibt grün, wenn Modul und Prüfkopie denselben
  Denkfehler tragen). Neben jede Zählung ein von Hand nachgerechneter Fall.
- 2026-09-03, viermal bestätigt — Eine Zeilennummer in einem Aufräumpaket ist beim
  Abarbeiten meist schon falsch (0079: die vier Stellen lagen sechs Zeilen tiefer als
  gemeldet). Warnzeichen, kein Hinweis: Stelle selbst suchen, durch Bleibendes ersetzen.
- 2026-09-04 — Beim Aufräumen von Belegstellen ist der Riegel selbst das Messgerät: je
  Datei messen, Rotnachweis über eine eingefügte und sofort entfernte Stelle in der
  **eigenen** Datei (0→1→0). Seine Fangbedingung **nachlesen**, bevor man den Ersatztext
  schreibt — wer rät, umschreibt vorsorglich und macht das Zitat wertlos.
- 2026-09-04 — **Eine Zählung von Zeilen belegt nichts über Gegenstände** (0044: `grep -c`
  gab 50 Schlüsselzeilen, richtig sind 41 verschiedene). `uniq -d` daneben.
- 2026-09-04 — Ein Riegel über Text liest **je Absatz, nicht je Zeile** (0044: der
  Dateiname stand vier Zeilen über der Überschrift). Absatz = Block gleichen
  Kommentarkopfs ohne Leerzeile — zu jedem Zeichen die Quellzeile mitführen, sonst nennt
  die Meldung den Absatz statt der Zeile.
- 2026-09-04 — Anführungszeichen und Umlaute im Bestand **messen statt raten**: `„` wird
  hier mit geradem `"` geschlossen, der Quelltext ist umlautfrei, die Vorgaben nicht.
- 2026-09-04, **dreimal getroffen** (zuletzt 2026-09-05) — Was ich in den **eigenen**
  Kopfkommentar oder in eine Falltabelle schreibe, prüft der eigene Riegel mit — in 0079
  landete eine Testzeile prompt in einer Zahl, die einem **fremden** Paket gehört. Muster
  *beschreiben*, nicht abschreiben; Testdaten maskieren (`\101` = `A`); jedes neue
  Schlüsselwort zuerst im eigenen Quelltext greppen.
- 2026-09-04 — **`git log -S` allein trägt keine Paketzuordnung.** Die Arbeit eines Pakets
  liegt hier regelmäßig im Commit des *nächsten* Laufs, dessen Betreff ein fremdes Paket
  nennt. Jeden `-S`-Treffer gegen das **Datum** des gesuchten Pakets halten.
- 2026-09-04 — Lässt eine Abnahme „fangen **oder** als Lücke benennen" offen: fangen, was
  ein Wort kostet; benennen, was eine ungemessene Schwelle verlangt. Beides in einem Lauf
  tauscht eine gemessene Regel gegen eine geratene, und der Rotnachweis fehlt dann.
- 2026-09-03 — Ein Verweis, der zweimal im Quelltext steht (Kommentar und
  Laufzeitausgabe), veraltet getrennt. Eine `constexpr`-Zeichenkette für beide.
- 2026-09-02 — Rotnachweis ohne Kollateralschaden: zwei Edits am eigenen Modul
  (kaputt → bauen → laufen → zurück → grün).
- 2026-09-05 — **Muss der Rotnachweis eine fremde Datei ändern, ändere stattdessen, wie
  die eigene sie liest.** 0079: statt eine Überschrift in `daten/` umzubenennen, einen
  Vorsatz vor jede gelesene Überschrift setzen. Derselbe Zustand, eigenes Gebiet — und
  die Rotmeldung nennt Datei und Zeile jeder betroffenen Fundstelle, also genau den
  Beleg, den man sonst behaupten müsste. Sabotiere dafür eine Stelle, die der
  **Selbsttest nicht durchläuft**: sonst bricht der Lauf mit Code 2 ab, bevor er den
  Bestand überhaupt liest.
- 2026-09-05 — **Eine Falltabelle zahlt sich beim Bauen aus, nicht erst beim Prüfen.**
  Zwei der neun Fälle in 0079 wurden rot und zeigten je einen echten Denkfehler, bevor er
  in den Bestand kam. Tabelle *vor* dem ersten Korpuslauf schreiben, mit den Fällen, die
  der Korpus **nicht** hergibt — dort alle roten, denn im Bestand löst alles auf.
- 2026-09-05 — Zwei Sonderfälle, die dieselbe benannte Eigenschaft **zweimal** anwenden,
  sind keine Liste: In 0079 entscheidet der Punkt hinter der Gliederungsziffer sowohl
  „keine Wortgrenze" als auch „diese Datei nummeriert überhaupt". Verlangt eine Abnahme
  eine Eigenschaft statt einer Liste, ist das die Bauform, die trägt.
- 2026-09-05 — Löst ein Verweis auf den **falschen** Nachbarn auf (Selbstbezug: der
  nächstgelegene Name ist eine fremde Datei), ist Rot der falsche Ausgang. Zitierende
  Datei mitfragen; eine Zieldatei ohne jede Überschrift bestätigt nichts. Beides
  übergehen und benennen, statt rot zu werden, wo nichts kaputt ist.

## Was nicht funktioniert

<!-- Was du versucht hast und was dabei herauskam. Damit du es nicht in drei Wochen
     erneut versuchst.
     Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-04, **zweimal getroffen** — `cd` in ein Unterverzeichnis nimmt mir `Edit` und
  `Write` still weg (`Edit(ventures/**)` ist *relativ* und löst gegen das
  Arbeitsverzeichnis auf; die Ablehnung nennt den Modus, nicht den Pfad). **Nie `cd`** —
  `cmake -S/-B`, `ctest --test-dir` und absolute Pfade tun dasselbe.
- 2026-09-02, bis 2026-09-05 bestätigt — Zusammengesetzte Shell-Befehle (`a && b`,
  `a; b`, Heredoc an `python3`) werden abgelehnt, einzelne Aufrufe und **Pipes** nicht.
  Ein Bauzyklus ist drei Aufrufe. Programm mit Rückgabe ≠ 0 über `ctest --test-dir`;
  `sed -n 'Np'` abgelehnt, `head -N | tail -M` läuft, Read mit `offset` auch.
- 2026-09-03, 2026-09-05 präzisiert — `grep` über die Shell wird für die Suche im Baum
  abgelehnt (Grep-Werkzeug oder `git grep` tun es), **auf einer Datei unter `$TMPDIR`
  läuft es** — so liest man den Testlog eines Riegels aus.
- 2026-09-04, präzisiert — Nach `$TMPDIR` geht **Bauen**, nicht **Kopieren** (`cp` und
  `Write` dorthin abgelehnt). Ein Mutationslauf gegen einen kopierten Baum ist damit kein
  Weg — die Sabotage geht über die **eigene** Datei, gebaut nach `$TMPDIR`.
- 2026-09-03 — Beim Sabotieren beißt `-Werror=unused-function`: Fällt eine Funktion aus
  dem Spiel, wird der **Bau** rot statt des Tests. Sabotage so legen, dass jede Funktion
  aufgerufen bleibt (ein `return` oder ein `false &&` mitten hinein geht durch).
- 2026-09-02 — `rm -rf bau` wird abgelehnt (Hausregel 3) und nicht gebraucht: `cmake
  -S/-B` konfiguriert über den vorhandenen Stand hinweg neu.

## Offene Faehrten

<!-- Etwas, das du bemerkt hast, aber diesmal nicht verfolgen konntest. -->

- 2026-09-04, 2026-09-05 wieder — **Der Korpus driftet während des eigenen Laufs**
  (0073: Bauquellen 39→40; 0079: Zielbestand 152→153 mitten im Lauf). Vorher-`HEAD` zu
  Beginn notieren und jede geänderte Zahl zuordnen, sonst schreibt der Prüfer sie mir zu.
- 2026-09-04 — **0090:** Eine entfernte Überschrift in `rueckstand.md` machte den Riegel
  rot, zu Recht — erster echter Fang von Bedingung 2. Der Übersetzungsbericht desselben
  Tages führte ihn noch grün: **Ein grüner Bericht ist nur für den Stand grün, den er
  gelesen hat.**
- 2026-09-02 — `FABRIK_STRENGE` steht zweimal wortgleich im Baum (`set()` ist
  verzeichnisgebunden); die dritte Fassung führt niemand nach. Paket 0031.
- 2026-09-02 — Der Prüfstand hat noch keinen **Regressionsbestand** und keinen
  **Determinismustest** — laut Rolle meine wichtigsten. Beide brauchen einen gerechneten
  Weltschritt und stehen erst nach dem Kernpaket zu „Schaden" an.
- 2026-09-05 — **Riegel nach 0079: 38/38 grün, 56 übergangen.** Von den zwei Lücken aus
  0067 ist die ohne Anführung zu; **0086 bleibt** (Schlüsselwort mit Abstand, Dateiname
  rechts) — Fall 6 in `NAMENSFAELLE` hält es fest.
- 2026-09-05 — **Eine Abnahme kann eine Zahl nennen, die auf dem Korpus unerfüllbar
  ist.** 0079 verlangte „übergangene Fundstellen fallen um genau zwei"; sie steigen um
  48. Nicht die Regel biegen, um die Zahl zu treffen — messen, gegenrechnen, im Paket
  und im Nachweis benennen.
- 2026-09-04 — Eine Abnahme, die die **Abwesenheit eines Musters** misst, sieht nie, ob
  der Ersatz wahr ist; so kamen die zwei falschen Sätze aus 0077 durch. Ersatztext im
  Wortlaut aus der Zieldatei holen und jede Behauptung darüber nachmessen — auch den
  **Kopf** der Datei, den ein Aufräumen unten stillschweigend falsch macht.
- 2026-09-04, 2026-09-05 erneut geprüft und bestätigt — `Write` nach `notizen/archiv/`
  ist der Rolle nicht erlaubt (`cp`/`mv` auch nicht). Die 12.000-Zeichen-Regel ist nur
  durch Zusammenziehen einzuhalten, und das kostet je Lauf Einträge. Als **Berechtigung**
  gemeldet, nicht als Paket — der Betreiber entscheidet.
- 2026-09-03 — **Eine Invariante fängt Nullfälle prinzipiell nicht.** An T43 nachgemessen:
  `ai = 0` als hartes Verbot lässt sie für alle 126 Profile grün. Nur ein eigens gebauter
  Fall mit *einer* zulässigen Art fängt es.
