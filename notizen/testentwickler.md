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

- 2026-09-02 — Die vom Paket 0019 vorgeschriebene Reihenfolge (CMakeLists, dann leeres
  `main`, dann Modul, dann Probe füllen) trägt, aber nur mit einem echten `cmake`-Lauf
  nach Schritt 2. Ohne den ist „im Bericht sichtbar" eine Behauptung; mit ihm steht
  `vorrat_probe … Passed` da, bevor eine einzige Zeile Fachlogik existiert.
- 2026-09-02 — Beide Bauwege einzeln prüfen. `baulauf.py` ruft jede `CMakeLists.txt`
  allein auf, der Arbeitsbereich ruft sie als Unterverzeichnis. Der Arbeitsbereich
  braucht ein erneutes `cmake -S/-B`, wenn ein Mitglied neu dazukommt: Die
  `EXISTS`-Abfrage in der Wurzel gilt zur Konfigurationszeit, und `CONFIGURE_DEPENDS`
  fängt nur neue Quelldateien, kein neues Verzeichnis.
- 2026-09-02 — Die falsche Fassung als *zweiten Aufruf desselben Prüfprädikats* bauen,
  nicht als eigenen Test. Dann misst die Vorführung nachweislich denselben Maßstab.
  Konkret: `zaehle_kerne(liste, kernfunktion)` plus `besteht_kernpruefung(befund)`, einmal
  mit der echten und einmal mit der kaputten Funktion.
- 2026-09-03 — Zwei falsche Fassungen belegen nur dann, dass zwei Bedingungen
  *Verschiedenes* messen, wenn je Fassung **beides** zugesichert wird: welche Bedingung
  sie fängt und welche sie durchlässt. Die Erwartung gehört in den Aufruf
  (`fuehre_abweichung_vor(..., invariante_soll, folge_soll)`), nicht ins Ergebnis —
  sonst prüft die Vorführung sich selbst.
- 2026-09-03 — Einen Erwartungswert aus der Vorgabe **zweimal** abschreiben (einmal als
  Zeichenkette für „zeichengleich", einmal als Tabelle für „in welcher Runde") und die
  beiden Abschriften vor allem anderen gegeneinander prüfen. Ein Tippfehler im Maßstab
  läuft sonst still grün, und ein falscher Maßstab ist schlimmer als ein roter Test.
- 2026-09-03 — Eine falsche Fassung lässt sich **herleiten** statt nachbauen. Spiegelt man
  die drei Familienstellen eines Profils, wird aus „kleinster Index unter den Größten" der
  größte — also aus dem Gleichstand an die kleinere Kennung der an die größere, ohne dass
  der Gleichstandsbrecher ein zweites Mal im Baum steht. Bedingung: Die Herleitung wird
  gegen von Hand nachgerechnete Festwerte geprüft, sonst belegt sie nur, dass sie
  *irgendetwas anderes* liefert.
- 2026-09-03 — Ein Anker aus Festwerten und eine Zählung messen Verschiedenes, und die
  Zählung ist die schwächere: 6/120 bleibt grün, wenn Modul und Prüfkopie denselben
  Denkfehler tragen. Wo ein Test eine Klasse, einen Namen oder eine Reihenfolge prüft,
  gehört mindestens ein von Hand nachgerechneter Fall daneben, der nichts rechnet.
- 2026-09-02 — Rotnachweis ohne Kollateralschaden geht mit zwei Edits am eigenen Modul
  (kaputt → bauen → laufen → zurück → bauen → grün). Ein Sabotagelauf in `$TMPDIR` scheitert
  hier am Werkzeugzugriff; der Weg über das Repo ist umkehrbar und im Ergebnis derselbe.
  — **Ergänzung 2026-09-03:** Gehört das Modul einem fremden Paket, geht es auch ohne es:
  eine Zeile in der *eigenen* Probe auf die falsche Zuteilung umlegen, bauen, laufen,
  zurück. Das misst sogar mehr als ein Prädikat allein — dass aus dem Verwerfen wirklich
  Rückgabe 1 wird, statt nur eine Zusicherung mit umgedrehtem Vorzeichen.

## Was nicht funktioniert

<!-- Was du versucht hast und was dabei herauskam. Damit du es nicht in drei Wochen
     erneut versuchst.
     Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig: Die Welt
     aendert sich, und eine Quelle, die im Maerz nichts hergab, kann im Juni
     ergiebig sein. -->

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
- 2026-09-03 — Beim Sabotieren beißt `-Werror=unused-function`: Fällt durch die Sabotage
  eine Funktion aus dem Spiel, wird der **Bau** rot statt des Tests, und der Nachweis
  misst nichts. Die Sabotage so legen, dass jede Funktion aufgerufen bleibt — oder eine
  Vorwärtsdeklaration danebenstellen und mit zurücknehmen.
- 2026-09-02 — `rm -rf bau` wird abgelehnt (Hausregel 3). Ein Bauverzeichnis muss nicht neu
  angelegt werden: `cmake -S/-B` über den vorhandenen Stand hinweg konfiguriert sauber neu,
  auch wenn der alte Cache aus einer Platzhalterfassung stammt.

- 2026-09-02 — Paket 0019 ist grün, und zwar nachgemessen auf **beiden** Bauwegen:
  `pruefstand/bau` allein (1/1 `vorrat_probe … Passed`) und über den Arbeitsbereich
  (7/7, `vorrat_probe` als siebter). Beide Anker rechnen von Hand nach: 56 Profile mit
  `a1=0` (C(8,3)), +15 für `a2=0`, +4 für `a3=0`, +1 für `a4=0` ⇒ `(1,1,1,1,1)` bei 76.

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
- 2026-09-03 — **Eine Invariante fängt Nullfälle prinzipiell nicht.** Nachgemessen an
  T43: Macht man `ai = 0` zum harten Verbot, bleibt die Invariante für alle 126 Profile
  und beide `k` grün — die Art soll `3k·0 = 0` Steckplätze bekommen und bekommt genau
  null. Nur ein eigens gebauter Fall mit *einer* zulässigen Art fängt es. Wer eine
  Invariante als alleinigen Maßstab nimmt, prüft die Nullzweige nie; das gilt über
  dieses Paket hinaus.
