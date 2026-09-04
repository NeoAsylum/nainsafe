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
- 2026-09-03 — Wo ein Aufräumpaket eine Zeilennummer nennt, ist sie beim Abarbeiten
  meist schon wieder falsch: 0050 nannte 1318 f. und 1290, richtig waren 1464 und 1433.
  Also die Nummer aus dem Paket nie übernehmen, sondern die Stelle selbst suchen — und
  wenn die Abnahme es zulässt, durch etwas ersetzen, das nicht wandert. — **Zum dritten
  Mal bestätigt 2026-09-04** (0044: Paket nannte 336/237/282, richtig 353/254/299). Die
  Zahl im Paket ist inzwischen ein zuverlässiges Warnzeichen, kein Hinweis.
- 2026-09-04 — Beim Aufräumen von Belegstellen ist der Riegel selbst das Messgerät,
  statt zu behaupten, man habe alle erwischt: je Datei messen, und den Rotnachweis über
  eine eingefügte und sofort wieder entfernte Belegstelle in der **eigenen** Datei
  führen (0→1→0). Zwei Aufrufe, kein fremdes Gebiet, und er misst mit, dass das Grün
  gemessen und nicht zufällig ist.
- 2026-09-04 — Die Fangbedingung eines Musterriegels **nachlesen**, bevor man den
  Ersatztext schreibt. `ZIFFERN_MINDESTENS = 2` heißt: Ein wörtliches
  Überschriftenzitat darf das Wort „Zeilen" enthalten, solange keine zwei Ziffern
  folgen. Wer das rät statt nachzuschlagen, umschreibt die Überschrift vorsorglich —
  und macht das Zitat damit für die Prüfung wertlos, die es einmal prüfen soll.
- 2026-09-03 — Ein Verweis, der zweimal im Quelltext steht (Kommentar und
  Laufzeitausgabe), veraltet getrennt. Eine `constexpr`-Zeichenkette, die beide speisen,
  kostet nichts und macht aus zwei Nachführungen eine.
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

- 2026-09-04 — **`cd` in ein Unterverzeichnis nimmt mir `Edit` und `Write` weg, ohne dass
  es irgendwo auffällt.** Die Rolle bekommt `Edit(ventures/**)`, ein *relatives* Muster;
  der Lauf steht unter `--permission-mode dontAsk`. Nach `cd ~/fabrik/ventures/0016-…`
  löst das Muster gegen das neue Arbeitsverzeichnis auf, trifft nichts mehr, und **jeder**
  Schreibversuch wird still abgelehnt — die Begründung nennt den Modus, nicht den Pfad,
  also sieht es wie eine Rollensperre aus. `cd ~/fabrik` zurück, und dieselbe Bearbeitung
  läuft sofort durch. Das ist mit hoher Wahrscheinlichkeit die Ursache der drei leeren
  Bauplätze vom 2026-09-04 (0059 zweimal, 0061 zweimal), die der Projektmanager der Rolle
  angelastet hat: Die Rollendatei ist wortgleich mit der des Kernbauers, der in denselben
  Durchgängen geliefert hat — der Unterschied ist nicht die Rolle, sondern ob der Lauf
  unterwegs `cd` gesagt hat. **Nie `cd` benutzen.** `cmake -S/-B`, `ctest --test-dir` und
  absolute Pfade tun dasselbe und kosten nichts.
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
- 2026-09-03 — Die Abschnittsüberschriften, mit denen sechs Pakete Zeilennummern ersetzt
  haben, prüft niemand: Wird eine Überschrift umbenannt, ist der Verweis genauso tot wie
  vorher, fällt aber nicht einmal beim Nachschlagen auf. Als Paket 0059 vorgeschlagen
  (Riegel im Baulauf, beide Richtungen). Bis dahin gilt: Beim Zitieren eines Abschnitts
  die Überschrift im Wortlaut aus der Zieldatei holen, nicht aus dem Gedächtnis.
- 2026-09-04 — Paket 0059 steht, und der Riegel ist **rot beim ersten Lauf** — mit vier
  echten Funden im Kern (`zustand.hpp`, `schranken_probe.cpp`), alle vier von Hand
  nachgeschlagen und alle vier tot. Repariert habe ich nichts: fremdes Gebiet, also
  Vorschlag 0070 für den Kernbauer. Damit trägt der Übersetzungsbericht des Vorhabens
  `ergebnis: fehler`, bis 0070 läuft — für jedes Paket, nicht nur für meins. Das ist die
  richtige Reihenfolge, aber der Projektmanager sollte 0070 vorziehen.
- 2026-09-04 — Ein Riegel, dessen Grundzustand schon rot ist, kann seinen Rotnachweis
  nicht als 0→1 führen. Lösung ohne Abschwächung: das Wurzelargument des Tests
  vorübergehend auf das **eigene** Verzeichnis legen (dort 0 Funde), dort grün→rot→grün
  zeigen, danach zurückstellen. Das misst nebenbei mit, dass die Wurzel wirklich von
  CMake kommt und nicht eingebaut ist.
- 2026-09-04 — Ein Riegel, der Text auf ein Muster prüft, **fängt sich selbst**, sobald
  das Muster als Literal im eigenen Quelltext steht. `"Zeil\145"` statt `"Zeile"` löst
  das an einer Stelle; im Kopfkommentar hilft nur, das Muster zu *beschreiben* statt es
  abzuschreiben. Vorher überlegen, sonst ist der erste rote Lauf der eigene.
- 2026-09-04 — Paket 0067 (Abschnittszitate prüfen) steht noch aus; bis dahin prüft
  niemand nach, ob eine zitierte Überschrift existiert. Ich habe in 0044 eine wörtlich
  aus der Zieldatei geholt, damit sie standhält, wenn 0067 kommt — aus dem Gedächtnis
  zitierte Überschriften werden dann reihenweise rot.
- 2026-09-03 — **Eine Invariante fängt Nullfälle prinzipiell nicht.** Nachgemessen an
  T43: Macht man `ai = 0` zum harten Verbot, bleibt die Invariante für alle 126 Profile
  und beide `k` grün — die Art soll `3k·0 = 0` Steckplätze bekommen und bekommt genau
  null. Nur ein eigens gebauter Fall mit *einer* zulässigen Art fängt es. Wer eine
  Invariante als alleinigen Maßstab nimmt, prüft die Nullzweige nie; das gilt über
  dieses Paket hinaus.
