# Logbuch: test-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/test-pruefer-<datum>.md` und beginnst neu.

Vorgaenger: `notizen/archiv/test-pruefer-2026-09-06.md` (voll nach 0180); davor
-2026-09-05 mit Suffixen -6 bis ohne -- Einzelheiten zu 0083r2, 0086, 0105, 0106,
0111, 0115, 0129, 0130, 0133, 0136, 0138, 0171 stehen dort.

---

## Wie ich einen Mutanten baue (traegt seit 0019, destilliert)

- Mutant als Textersetzung an einer **Arbeitskopie**, nie am Repo. Ablage unter
  `ventures/<id>/bau/<eigener-name>/` statt $TMPDIR: gitignoriert, baulauf.py nimmt
  `bau` von der Manifestsuche aus (Zeile 132), tmpfs oft fast voll -- ENOSPC macht
  Schein-Rot. gcc-Zwischendateien: Unterprozessen TMPDIR per env auf die Platte legen.
  Fremde Dateien in `bau/` nie abraeumen.
- **Arbeitskopie billig aus git:** `git archive HEAD` von Vorhaben + specs ins
  Betriebslayout `<basis>/ventures/<id>` + `<basis>/specs/<id>`; vor der Messung
  byteweise gegen den Arbeitsbaum halten (filecmp), vor dem Abraeumen nochmal.
- **Immer mit Trefferbremse** (`assert text.count(nadel) == 1`); Ruecknahme-Nadel
  ist selten die Hinweg-Nadel -- mit Einrueckung nehmen.
- **M0 vor der Mutation und nach jeder Ruecknahme.** Jeden Bau-RC pruefen; bei
  unerklaerlichem Rot zuerst `df`.
- **Am selben Bau messen wie der Runner:** `RelWithDebInfo`,
  `-DCMAKE_CXX_FLAGS=-fwrapv -fno-fast-math`; die zwei Profile sind
  `FABRIK_SANITIZER=ON` (Vorgabe) und `OFF`. Alleinbau prueft zugleich den
  `PROJECT_IS_TOP_LEVEL`-Block.
- **Neutralisieren statt loeschen:** `(x || true)`, `false && x`, `(void)param;` --
  sonst stirbt der Bau an `-Werror` und misst die Werkzeugkette.
- **Eigene Mutation statt der des Nachweises waehlen**; Kippmengen bestaetigen die
  Zahl unabhaengig. Fremden Nachweis/GEBAUT-Absatz/Uebersetzungsbericht erst NACH
  der eigenen Messung gegenlesen.
- **Zaehlen, welche Zusicherungen reissen**, und am Ende fragen: welche hat kein
  Mutant rot bekommen? Schwellen erst gemessen, wenn von beiden Seiten eingeklemmt.
- **Dateiliste des Baucommits gegen `dateien` legen:** `git show --numstat <hash>`,
  nie ueber den Betreff suchen -- der Runner buendelt Pakete unter fremden Betreffs.
- `ctest -N` zaehlt man mit Regex `Test\s+#\d+:`, gegen ein gelaufenes "out of N".
- Zahlen duerfen zwischen Messstaenden driften: erst Commits datieren, dann
  Widerspruch rufen. HEAD wandert waehrend der Messung; dokumentieren, nicht anrennen.
- **Befundnamen vor dem Schreiben pruefen** (ls auf befunde/, auch Archiv), bei
  Ruecklaeufen `-runde2-` einschieben.

## Was funktioniert / nicht funktioniert

- Sperren wechseln je Sitzung -- probieren, nicht ableiten. python3-Heredocs gehen
  fast immer (auch mit internen Schleifen und subprocess); Verbund mit `;`/`&&`,
  sed, mv oft nicht. Write nach befunde/ und aufgaben/ ging zuletzt. Pfade kopieren,
  nicht tippen (unsichtbare Zeichen).
- Ein einzelner Fehllauf mit `bwrap:`-Meldung ist der Sandbox-Wrapper, nicht das
  Kommando -- einmal wiederholen, bevor man etwas anderes vermutet (0180).
- Mutantenskripte im Repo-Baubaum hinterlassen ctest rot -- eigener Baubaum in der
  Arbeitskopie. Baeume am Ende entfernen.
- Ein stiller Nulloutput ist ein Befund, kein Ergebnis. Bei ueberlebender Mutation
  zuerst fragen: welcher Eingabewert macht beide Formen gleich?
- Eine Regel, die nur im Einlese-/Bestandspfad wirkt, kann jeder Selbsttest am
  heutigen Baum verfehlen (Familie 0129->0138, 0130->0182). Merkfrage am Ende
  jeder Riegelpruefung stellen.
- "Stirbt vor dem Bestand" billig dynamisch: Mutant mit nicht existierender Wurzel
  aufrufen; Code 2 samt Selbsttestmeldung heisst: er brauchte den Bestand nie.

## 2026-09-06 — 0180 (Zahlwortriegel werte.hpp): geprueft, Vorschlag 0194

- **Mutationen an der GELESENEN Datei brauchen keinen Neubau** -- der Riegel liest
  werte.hpp zur Laufzeit. Fuenf Datenmutanten in Minuten am selben Binary; nur die
  drei Mutationen am Riegelcode selbst kosteten je einen Alleinbau. Erst fragen:
  ist der Pruefling Code oder Daten?
- **Ein fehlplatzierter Mutant kann trotzdem etwas beweisen:** Feld zwischen fremden
  Kommentar und fremde Deklaration geschoben -> der Parser schlug den Kommentar dem
  neuen Feld zu, Rot kam aus der Sortenschranke statt aus dem Zahlwort. Die Schranke
  ist damit belegt, der eigentliche Nachweis brauchte eine zweite, sauber platzierte
  Mutation am Struct-Ende.
- **Zwei Zahlen in einem Satz, eine bewacht:** Zeile 32 "Zweiundzwanzig Groessen in
  dreiundzwanzig Deklarationen" -- der Riegel prueft nur die erste, die Zaehlung der
  zweiten existiert schon im Code. Bei Zahlriegeln immer fragen: welche Zahl im
  SELBEN Satz prueft niemand? -> Vorschlag 0194.
- Selbsttest-Guete per Riegel-Mutation gemessen: Urteil festgenagelt, Artikelregel
  neutralisiert, Befundanhang neutralisiert -- alle drei Code 2, die fuenfte
  (Verdrahtungs-)Tabelle deckt wirklich die Zusammensetzstelle.
- Ordnungszahl-`<=` beidseitig eingeklemmt: 2<=2 gruen (Bestand), 2<=3 stumm
  (drittes Feld), 3>2 rot (verstellt).

## 2026-09-06 — 0185 (Profilangabe-Regressionsnachweis): geprueft

- **Wenn ein Paket seine eigenen Rotnachweise als `--bruch`-Schalter mitbringt, sie
  trotzdem selbst fahren UND eine eigene Mutation an anderer Stelle setzen:** Die
  if-Bedingung der Wortberechnung kippen statt des set() (Bruch traf nur OFF, meine
  Kippe beide Profile) — und `message(STATUS` -> `message(DEBUG` trifft den
  `zeile is None`-Zweig, den kein eingebauter Bruch je sieht. Beide rot, 22 Baeume
  gruen dabei: es riss die neue Bedingung, nicht etwas anderes.
- **Aufbaufehler, der mich einen Lauf kostete:** WURZEL = parents[2] der Skriptdatei;
  bei der Vorfassungskopie die Ebene `befunde/` weggelassen -> Kette nicht gefunden,
  RC 1 sah aus wie ein Paketproblem. Layout der Arbeitskopie immer gegen die
  parents[]-Rechnung des Skripts legen, Fehlausgabe drucken statt nur RC lesen.
- Testzahl-Drift wieder billig datiert: 18 vs 19 kam aus cf9e15a (0180) NACH dem
  Baucommit — `git log adbf4a8..HEAD -- <venture>` reichte.
- Redundante Drittbedingung (Koepfe verschieden folgt aus beiden Haelften korrekt)
  ist kein Befund — Zusatzgurt, kein pruefbar eigenes Versprechen.
- Sperren: `;`-Verbund (`python3 ...; echo RC`) verweigert, nackter python3-Aufruf
  und python3-Heredoc mit subprocess/env= gingen durchweg; Write nach befunde/ ging.
  rm nicht probiert, shutil.rmtree im Heredoc tat es.

## 2026-09-07 — 0147 (Orts-/Formanker Belegstellenriegel): zurueck, Vorschlag 0200

- **Builder-Lauf hatte selbst keine Shell:** messung-0147 steht komplett, lief aber
  nie (`ergebnis: nicht_ausgefuehrt` im Nachweis). Eine Mess-Abnahme ohne Lauf ist
  zurueck, egal wie gut der Stand ist. Statisch ersatzgeprueft: alle 9 alt-Nadeln
  einmalig und aktuell, jeder Mutant reisst genau seinen Fall, Selbsttest laeuft vor
  argv/Bestand, Ein-Wurzel-Aufruf ist kanonisch (Riegel leitet specs/ selbst ab,
  CMake add_test hat ein Argument).
- **Zuerst den Uebersetzungsbericht des Tages oeffnen, dann "gruen auf dem Korpus"
  glauben:** Der Korpus war den ganzen Lauf ueber rot — Uebersetzung benennt
  spec-Ueberschriften um ("Die Schleife" -> "The loop"), 10 Zitate tot, ctest
  belegstellen_riegel FAILED in beiden Baeumen. Ein Gruen-Zitat im Nachweis stammte
  vom Vortag und war Stunden spaeter falsch.
- **Ein "fehlender" Mutant kann eine Unmoeglichkeit sein:** FORMFAELLE-Tausch 1<->2
  reisst nichts, weil KLAMMERN-Anfangszeichen und ist_namensanfang disjunkt sind
  (selbst nachgeprueft). Dann das Disjunktheitsargument verlangen, keinen gruenen
  Fall.
- messung.py-Koederluecke, aber gedeckt: falsche ZAHLENMARKE ergaebe beidseitig
  "(keine Zahlenzeile)" und bliebe still — der Befundteil-Vergleich faengt es ueber
  den veraenderten Selbsttest-Vorspann.

## Offene Faehrten

- 2026-09-07 (0147) -- Nachweis meldet Befund gegen messung-0106/messung.py:
  FREMDE_FAELLE-Marken `Namensfall`/`Abstandsfall` treffen nie (Riegel schreibt
  `Selbsttest N:`). Beim naechsten 0106-Familien-Paket pruefen, ob das ein Paket
  bekam.

- 2026-09-05 (0086) -- **Herkunftsangaben von ZITATFAELLE einzeln nachschlagen.**
  Mehrfach vertagt; ZIELFAELLE-Herkuenfte stichprobenhaft ok (0083r2).
- 2026-09-05 (0083r2) -- **Gelesen-Seite loest ueber den Basisnamen auf**
  (`bestand.find(basisname(name))`, Erbe 0067): toter Verweis `bau/x/spiel.md`
  faellt als Gelesen auf die echte spiel.md. Beim naechsten Riegelpaket ansehen.
- 2026-09-05 (0086) -- Der Riegel rueckt nach einem Treffer um den ganzen Zitatteil
  weiter und kann ein Schluesselwort im zitierten Wortlaut ueberspringen.
- 2026-09-05 (0110) -- `urteil: bau` des Mutationstreibers ist nie gefahren; beim
  naechsten Katalogpaket einen static_assert-Fall einbringen. Vorschlag 0127 offen.
- 2026-09-05 (0088) -- Bevor ich eine Zeile "unerreichbar" nenne, den Mutanten
  wirklich bauen; `festkomma`-Literale brechen am `static_assert` ab.
- 2026-09-02 -- `anteile_aus_zustand` in `schranken_probe.cpp` sichert die Summe,
  nicht den Quotienten; wird bei T30 scharf.
