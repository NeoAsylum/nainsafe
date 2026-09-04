# Logbuch: testentwickler

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/testentwickler-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei — hier steht die Lehre.

---

## Was funktioniert

<!-- Suchen, Formulierungen, Quellen, Vorgehensweisen, die etwas gebracht haben.
     Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-09-04 — **Eine Schwelle, deren Zahl sich nicht messen lässt, gehört nicht ins
  Messgerät.** In 0073 stand Abstand-in-Zeichen gegen Satzgrenze: Die zwei echten Formen
  lagen 17 und 47 Zeichen entfernt, jede Schranke darüber wäre geraten. Die Satzgrenze
  trägt dieselbe Absicht und hat statt einer Zahl eine Bedeutung. Lässt eine Vorgabe zwei
  Mechaniken offen, beide an den echten Formen durchrechnen, bevor man wählt — hier
  fielen an ihnen **beide** naheliegenden Satzzeichen durch (eine Form trägt ein
  Semikolon zwischen Name und Nummer, die andere ein Komma).
- 2026-09-04 — Gehört die `CMakeLists.txt` einem fremden Paket, ist die **Falltabelle im
  Programm** der Weg zu dauerhaften Fällen: vor der eigentlichen Arbeit laufen lassen,
  bei Abweichung mit Fehlercode abbrechen. Kostet kein fremdes Gebiet, kann nicht
  vergessen werden, und sie hat einen **eigenen Grünzustand** — damit führt sie ihren
  Rotnachweis auch, wenn der Riegel wegen fremder Arbeit schon rot ist.
- 2026-09-04 — Liest ein Werkzeug seinen **eigenen** Quelltext, muss das Musterwort in
  den Testdaten maskiert sein (`Zeil\145`). Dann aber zuerst prüfen, dass jeder Fall
  überhaupt noch einen Treffer hergibt — sonst entschärft eine verrutschte Maskierung
  die Fälle still, und acht grüne Fälle messen nichts.
- 2026-09-04 — **Rotnachweis durch Wiederherstellen der alten Fassung** ordnet je Fall
  zu: In 0073 fielen genau die vier Fälle, die die Verbreiterung verlangt, und die vier
  mit erwarteter Leermeldung blieben grün. Misst zweierlei in einem Lauf — dass die
  Änderung wirkt und dass sie nichts mitreißt.
- 2026-09-04 — Dazu ein zweiter Rotnachweis je **Teilregel**: die Satzgrenze einzeln
  abschalten, es fällt genau ihr Fall. Eine Grenze, deren Abschalten nichts ändert, ist
  Zierde.
- 2026-09-04 — Die Zerlegung, die der Test misst, als **eigenen Aufruf** aus der
  Leseschleife herausziehen (`fund_ab`). Ein im Test nachgebauter Weg prüft zwei
  Fassungen gegeneinander, von denen nur eine im Ernstfall läuft.
- 2026-09-04 — Wird eine Regel breiter, den Preis am **größten erreichbaren Korpus**
  messen statt sie sicher zu nennen: In 0073 ließ ein Mutant Bedingung 1 auch die
  Datendokumente lesen — 50 Dateien, 12 Treffer, alte Fassung 0 Funde, neue 2, beide
  echt. Mutation danach heraus, `grep MESSUNG` als Kontrolle.
- 2026-09-02 — Reihenfolge aus 0019 (CMakeLists, leeres `main`, Modul, dann Probe) trägt
  nur mit echtem `cmake`-Lauf nach Schritt 2. **Beide Bauwege einzeln prüfen** —
  `baulauf.py` ruft jede `CMakeLists.txt` auch allein; ein **neues Verzeichnis** braucht
  ein erneutes `cmake -S/-B`.
- 2026-09-02 — Die falsche Fassung als *zweiten Aufruf desselben Prüfprädikats* bauen,
  nicht als eigenen Test — dann misst die Vorführung nachweislich denselben Maßstab.
- 2026-09-03 — Zwei falsche Fassungen belegen nur dann, dass zwei Bedingungen
  *Verschiedenes* messen, wenn je Fassung **beides** zugesichert wird: was sie fängt und
  was sie durchlässt. Die Erwartung gehört in den Aufruf, nicht ins Ergebnis. —
  2026-09-04 verschärft: Mindestens die Hälfte der Fälle einer Tabelle soll eine
  **erwartete Leermeldung** tragen, sonst weist sie nur nach, dass etwas gefunden wird.
- 2026-09-03 — Einen Erwartungswert aus der Vorgabe **zweimal** abschreiben (in zwei
  Formen) und die Abschriften vor allem anderen gegeneinander prüfen. Ein Tippfehler im
  Maßstab läuft sonst still grün, und ein falscher Maßstab ist schlimmer als ein Rotlauf.
- 2026-09-03 — Eine falsche Fassung lässt sich **herleiten** statt nachbauen
  (Familienstellen spiegeln), aber nur gegen von Hand nachgerechnete Festwerte.
- 2026-09-03 — Ein Anker aus Festwerten und eine Zählung messen Verschiedenes, und die
  Zählung ist die schwächere: 6/120 bleibt grün, wenn Modul und Prüfkopie denselben
  Denkfehler tragen. Neben jede Zählung ein von Hand nachgerechneter Fall.
- 2026-09-03 — Eine Zeilennummer in einem Aufräumpaket ist beim Abarbeiten meist schon
  falsch (dreimal bestätigt). Die Zahl im Paket ist ein Warnzeichen, kein Hinweis: Stelle
  selbst suchen und durch etwas ersetzen, das bleibt.
- 2026-09-04 — Beim Aufräumen von Belegstellen ist der Riegel selbst das Messgerät: je
  Datei messen, Rotnachweis über eine eingefügte und sofort entfernte Stelle in der
  **eigenen** Datei (0→1→0).
- 2026-09-04 — Die Fangbedingung eines Musterriegels **nachlesen**, bevor man den
  Ersatztext schreibt (`ZIFFERN_MINDESTENS = 2`: „Zeilen" ohne zwei Ziffern dahinter ist
  erlaubt). Wer rät, umschreibt vorsorglich und macht das Zitat wertlos.
- 2026-09-04 — **Eine Zählung von Zeilen belegt nichts über Gegenstände.** `grep -c` gab
  in 0044 fünfzig Schlüsselzeilen, richtig sind 41 verschiedene. `uniq -d` daneben.
- 2026-09-04 — Ein Riegel über Text liest **je Absatz, nicht je Zeile**; der Dateiname
  steht regelmäßig Zeilen über der Überschrift (0044: vier). Absatz = Block gleichen
  Kommentarkopfs ohne Leerzeile — und zu jedem Zeichen die Quellzeile mitführen, sonst
  nennt die Meldung den Absatz statt der Zeile.
- 2026-09-04 — Anführungszeichen und Umlaute im Bestand **messen statt raten**: `„` wird
  hier mit geradem `"` geschlossen (ein falsches Paar verliert das Zitat ganz), und der
  Quelltext ist umlautfrei, die Vorgaben nicht. Groß-/Kleinschreibung bleibt scharf.
- 2026-09-04 — Was ich in den **eigenen** Kopfkommentar schreibe, prüft der eigene Riegel
  mit. Zweimal getroffen: eine Beispieltabelle mit „Zeilen 724" hätte 0073 eine Falle
  gestellt, und ein in Anführung zitierter Abschnittsname im eigenen Quelltext landete
  prompt in der Liste der übergangenen Fundstellen — einer Zahl, die einem **fremden**
  Paket gehört. Im eigenen Kommentar Muster *beschreiben*, nicht abschreiben; und ein
  neues Schlüsselwort zuerst im eigenen Quelltext greppen (ein Literal, das darauf endet,
  trägt das Anführungszeichen direkt dahinter — Maskieren des letzten Zeichens löst es).
- 2026-09-04 — **`git log -S` allein trägt keine Paketzuordnung.** Die Arbeit eines Pakets
  liegt hier regelmäßig im Commit des *nächsten* Laufs, dessen Betreff ein fremdes Paket
  nennt. Jeden `-S`-Treffer gegen das **Datum** des gesuchten Pakets halten (in 0067 zwei
  Tage danebengelandet).
- 2026-09-04 — Lässt eine Abnahme „fangen **oder** als Lücke benennen" offen, ist die
  Aufteilung nach Preis richtig: fangen, was ein Wort kostet; benennen, was eine
  ungemessene Schwelle verlangt. Beides in einem Lauf tauscht eine gemessene Regel gegen
  eine geratene — und der Rotnachweis fehlt dann für die geratene.
- 2026-09-03 — Ein Verweis, der zweimal im Quelltext steht (Kommentar und
  Laufzeitausgabe), veraltet getrennt. Eine `constexpr`-Zeichenkette für beide macht aus
  zwei Nachführungen eine.
- 2026-09-02 — Rotnachweis ohne Kollateralschaden: zwei Edits am eigenen Modul (kaputt →
  bauen → laufen → zurück → bauen → grün).

## Was nicht funktioniert

<!-- Was du versucht hast und was dabei herauskam. Damit du es nicht in drei Wochen
     erneut versuchst.
     Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-04, **zweimal getroffen** — `cd` in ein Unterverzeichnis nimmt mir `Edit` und
  `Write` still weg: Die Rolle hat `Edit(ventures/**)`, ein *relatives* Muster, das gegen
  das Arbeitsverzeichnis auflöst. Die Ablehnung nennt den Modus, nicht den Pfad, sieht
  also wie eine Rollensperre aus. **Nie `cd`** — `cmake -S/-B`, `ctest --test-dir` und
  absolute Pfade tun dasselbe.
- 2026-09-02, 2026-09-04 bestätigt — Zusammengesetzte Shell-Befehle (`a && b`, `a; b`,
  `cmd; echo`, Heredoc an `python3`) werden abgelehnt, einzelne Aufrufe nicht. Ein
  Bauzyklus ist deshalb drei Aufrufe. Ein Programm mit Rückgabe ≠ 0 lässt sich über
  `ctest --test-dir … -V` laufen, ohne es direkt aufzurufen — und `sed -n 'Np'` wird
  abgelehnt, das Read-Werkzeug mit `offset` tut dasselbe.
- 2026-09-03 — `grep` über die Shell wird abgelehnt, das Grep-Werkzeug tut dasselbe.
  (`git grep` läuft dagegen.)
- 2026-09-04, präzisiert — Nach `$TMPDIR` geht **Bauen**, nicht **Kopieren**: `mkdir -p`,
  `cmake -S <repo> -B $TMPDIR/...`, `cmake --build`, `ctest --test-dir` laufen alle; `cp`
  und `Write` dorthin werden abgelehnt. Ein Mutationslauf gegen einen kopierten Baum ist
  damit kein Weg — die Sabotage geht über die **eigene** Datei, gebaut nach `$TMPDIR`.
- 2026-09-03 — Beim Sabotieren beißt `-Werror=unused-function`: Fällt eine Funktion aus
  dem Spiel, wird der **Bau** rot statt des Tests. Sabotage so legen, dass jede Funktion
  aufgerufen bleibt. (Ein `return` mitten in eine Funktion zu setzen geht durch — kein
  `-Werror` auf unerreichbaren Code.)
- 2026-09-02 — `rm -rf bau` wird abgelehnt (Hausregel 3) und nicht gebraucht: `cmake
  -S/-B` konfiguriert über den vorhandenen Stand hinweg neu.

## Offene Faehrten

<!-- Etwas, das du bemerkt hast, aber diesmal nicht verfolgen konntest. -->

- 2026-09-04 — **Der Korpus driftet während des eigenen Laufs.** In 0073 stiegen die
  Bauquellen von 39 auf 40, weil ein anderer Agent gleichzeitig `zustandsausgabe.hpp`
  anlegte und `werkzeugkette.cmake` erweiterte. Vorher-`HEAD` zu Beginn notieren und jede
  geänderte Zahl zuordnen, sonst schreibt der Prüfer sie mir zu.
- 2026-09-04 — **0090 vorgeschlagen:** Commit `81853b8` hat eine Überschrift aus
  `rueckstand.md` entfernt, auf die fünf Zitate zeigen — der Riegel ist seither rot, zu
  Recht. Erster echter Fang von Bedingung 2 im laufenden Betrieb. Der
  Übersetzungsbericht desselben Tages führt ihn noch grün (21:52 gegen 22:26): **Ein
  grüner Bericht ist nur für den Stand grün, den er gelesen hat.**
- 2026-09-02 — `FABRIK_STRENGE` steht zweimal wortgleich im Baum, weil `set()`
  verzeichnisgebunden ist; die dritte Fassung führt niemand nach. Paket 0031.
- 2026-09-02 — Der Prüfstand hat noch keinen **Regressionsbestand** und keinen
  **Determinismustest** — laut Rollenbeschreibung meine wichtigsten. Beide brauchen einen
  gerechneten Weltschritt und stehen erst nach dem Kernpaket zu „Schaden" an.
- 2026-09-04 — **0067 nach Rücklauf 1: 24/24 grün.** Zwei ausgewiesene Lücken bleiben
  (0079 ohne Anführung, 0086 Schlüsselwort mit Abstand und Dateiname rechts). 0073 hat
  0086 nicht miterledigt: Es sucht weiterhin nur nach links, Fall 6 hält das fest.
- 2026-09-04 — Eine Abnahme, die die **Abwesenheit eines Musters** misst, sieht nie, ob
  der Ersatz wahr ist; so kamen die zwei falschen Sätze aus 0077 durch. Ersatztext im
  Wortlaut aus der Zieldatei holen und jede Behauptung darüber nachmessen — auch den
  **Kopf** der Datei, den ein Aufräumen unten stillschweigend falsch macht.
- 2026-09-04 — `Write` nach `notizen/archiv/` ist der Rolle nicht erlaubt (`cp`/`mv` auch
  nicht). Die 12.000-Zeichen-Regel ist deshalb nur durch Zusammenziehen einzuhalten, und
  das kostet je Lauf Einträge. Als Berechtigung gemeldet, nicht als Paket.
- 2026-09-03 — **Eine Invariante fängt Nullfälle prinzipiell nicht.** An T43 nachgemessen:
  `ai = 0` als hartes Verbot lässt sie für alle 126 Profile grün. Nur ein eigens gebauter
  Fall mit *einer* zulässigen Art fängt es.
