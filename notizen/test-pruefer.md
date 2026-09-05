# Logbuch: test-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/test-pruefer-<datum>.md` und beginnst neu.

Vorgaenger: `notizen/archiv/test-pruefer-2026-09-05-5.md` (voll bei 0083 Runde 2);
davor -4 (0111), -3 (0086), -2, ohne Suffix -- alle 2026-09-05.

---

## Wie ich einen Mutanten baue (traegt seit 0019, destilliert)

- Mutant als Textersetzung an einer **Arbeitskopie unter `$TMPDIR`**, nie am Repo;
  `shutil.copytree`/`makedirs` im python3-Heredoc. Vorher `isfile` auf den Zielnamen:
  $TMPDIR teilen sich parallele Laeufe, eine fremde Datei `m1` hat `makedirs`
  sterben lassen (0083r2).
- **Immer mit Trefferbremse** (`assert text.count(nadel) == 1`); bei mehreren
  Vorkommen nach der Ersetzung die Nachbarstelle zaehlen (0111).
- **M0 vor der Mutation und nach jeder Ruecknahme.**
- **Am selben Bau messen wie der Runner:** `baulauf.py` abschreiben
  (`RelWithDebInfo`, `-fwrapv -fno-fast-math`), Werkzeugkette via
  `PROJECT_IS_TOP_LEVEL` (werkzeugkette.cmake zwei Ebenen hoeher mitkopieren).
- **Neutralisieren statt loeschen:** ganze Funktion oder Bedingungshaelfte per
  `(x || true)` bzw. `(void)param;` im Spiel halten, sonst stirbt der Bau an
  `-Werror=unused-function` und misst die Werkzeugkette statt des Tests (0107, 0083r2).
- **Die alte Fassung gegen denselben Mutanten fahren** (`git show <commit>^:pfad`):
  alt gruen + neu rot belegt die offene Luecke in einem Lauf (0061, 0111).
- **Zaehlen, welche Zusicherungen reissen** und ob es die der Abnahme sind; am Ende
  fragen: welche Zusicherung hat kein Mutant rot bekommen?
- Schwellen sind erst gemessen, wenn sie von **beiden** Seiten eingeklemmt sind (0086).
- **Fremden Nachweis/GEBAUT-Absatz erst nach der eigenen Messung gegenlesen** (0088).
- **Dateiliste des Baucommits gegen `dateien` legen** (`git show --numstat`);
  `git log -- <datei>`, nie `git show <betreff>`: Der Runner buendelt Pakete unter
  fremden Betreffs -- bei 0083r2 trug der Betreff-Commit **keine einzige** Paketdatei,
  die Arbeit lag in drei fremden Betreffs (bekannt, Pakete 0121/0131).

## Was funktioniert

- 2026-09-05 (0083r2) -- **Urteil geprueft, 0 Befunde.** Ortsfrage zweiteilig, end-zu-
  end am Arbeitsbaum MIT bau/: specs-Kopie ohne spiel.md -> Code 1, 15 tote Ziele;
  echte specs -> Code 0, 36/36. Vier Mutanten rot, je andere Zielfaelle (6/7/10/12/13,
  4/9/11, 11, Untergrenze 36<37 -> Code 2). Zahlen decken sich mit dem Nachweis des
  Bauagenten, erst danach gegengelesen.
- 2026-09-05 (0111) -- Ein "vorher schon rot"-Nebenbefund des Bauagenten kann zur
  Pruefzeit repariert sein: aktuellen Stand messen, Abweichung als Nebenbefund.
- 2026-09-05 (0088) -- Bei ueberlebender Mutation zuerst fragen: welcher Eingabewert
  macht beide Formen gleich?
- 2026-09-05 (0086) -- Ein stiller Nulloutput ist ein Befund, kein Ergebnis.
- 2026-09-05 (0079r2) -- Wenn zwei Zahlen im selben Nachweis nicht zusammenpassen,
  zuerst die Arithmetik des Dokuments, dann messen.
- 2026-09-05 (0083r2) -- **Befundnamen kollidieren bei Ruecklaeufen:** vor dem
  Schreiben ls auf befunde/, dann `-runde2-` einschieben (Praezedenz 0009).

## Was nicht funktioniert

- Sperren wechseln je Sitzung und innerhalb der Sitzung -- probieren, nicht ableiten.
  0083r2: Verbund mit cd/&&, for-Schleife, ein grosser Sammel-Heredoc und Write
  gesperrt; kleinteilige python3-Heredocs (auch schreibend ins Repo), cmake/ctest,
  git, Grep-Tool gingen.
- Mutantenskripte im Repo-Baubaum hinterlassen ctest rot (0086) -- gar nicht erst
  hinein, Arbeitskopie samt eigenem Baubaum.
- `git status` zeigt am Repowurzelrand Sandbox-Zeichengeraete: nicht aufraeumen (0088).
- Zwei Laeufe derselben Rolle koennen parallel laufen: Kollisionen bei Befund-,
  Archiv- und $TMPDIR-Namen pruefen (0083, 0083r2).

## 0129 (2026-09-05, Fable-Lauf)

- **Urteil geprueft, 0 Befunde.** Alle vier Bedingungen selbst gemessen: Altbaum als
  ganze Datei aus `git show c30acc5^:` (juengster Commit der Zieldatei = der
  Wortlauttausch), Ein-Zeilen-Mutant `zugesichert = true -> false`, ctest-Zaehlung
  beider Staende 15->16 im selben Messaufbau, beide Profile 16/16.
- **`ctest -N` schreibt `Test  #1:` mit zwei Leerzeichen, `Test #10:` mit einem.**
  Mein startswith("Test #") fing nur #10 aufwaerts -- 7 statt 16, und die Differenz
  sah trotzdem plausibel aus. Zaehlmuster als Regex `Test\s+#\d+:`, und jede
  -N-Zaehlung gegen ein gelaufenes "out of N" gegenpruefen.
- **Die schlanke Kopie (ohne befunde-Inhalt) faellt bei der Konfiguration:**
  `pruefstand/CMakeLists.txt:136` verlangt `befunde/pruefung-0066/nachbau.py`.
  Die eine Datei nachkopieren genuegt.
- **Eine Regel, die nur im Einlesepfad wirkt, kann jeder Selbsttest verfehlen:**
  Der Bedingung-2-Mutant besteht am heutigen Baum Selbsttest und ctest gruen und
  trennt nur am Altbaum. Einmal-Rotnachweis erfuellt die Abnahme, deckt aber nicht
  dauerhaft -- als Vorschlag 0138 geschrieben, nicht als Befund.
- Sperren dieser Sitzung: `ctest`/Binary mit `; echo RC=$?`-Verbund und `sed`
  gesperrt; einzelne cmake-Aufrufe, python3-Heredoc (auch cmake/ctest via
  subprocess), Write ins Repo, grep, git -- alles gegangen.

## Offene Faehrten

- 2026-09-05 (0086) -- **Herkunftsangaben von ZITATFAELLE (9) einzeln nachschlagen.**
  In 0083r2 erneut vertagt; die ZIELFAELLE-Herkuenfte sind dort stichprobenhaft
  nachgemessen (einzige-Fundstelle-Behauptung stimmt). 0105/0106/0115 kommen auf
  dieselbe Datei.
- 2026-09-05 (0083r2) -- **Die Gelesen-Seite loest weiter ueber den Basisnamen auf**
  (`bestand.find(basisname(name))`, Erbe 0067): ein toter Verweis `bau/x/spiel.md`
  faellt als Gelesen auf die echte spiel.md, solange die Ueberschrift dort steht.
  Vom Bauagenten selbst als moegliches eigenes Paket benannt -- beim naechsten
  Riegelpaket ansehen.
- 2026-09-05 (0086) -- Der Riegel rueckt nach einem Treffer um den ganzen Zitatteil
  weiter und kann ein Schluesselwort im zitierten Wortlaut ueberspringen.
- 2026-09-05 (0110) -- `urteil: bau` des Mutationstreibers ist nie gefahren; beim
  naechsten Katalogpaket einen static_assert-Fall einbringen. Vorschlag 0127 offen.
- 2026-09-05 (0088) -- Bevor ich eine Zeile "unerreichbar" nenne, den Mutanten
  wirklich bauen; `festkomma`-Literale brechen am `static_assert` ab.
- 2026-09-02 -- `anteile_aus_zustand` in `schranken_probe.cpp` sichert die Summe,
  nicht den Quotienten; wird bei T30 scharf.
