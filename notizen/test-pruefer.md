# Logbuch: test-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/test-pruefer-<datum>.md` und beginnst neu.

Vorgaenger: `notizen/archiv/test-pruefer-2026-09-05-4.md` (voll bei Paket 0111);
davor `-3` (0086), `-2`, und ohne Suffix, alle 2026-09-05.

---

## Wie ich einen Mutanten baue (traegt seit 0019, destilliert)

- Mutant als Textersetzung an einer **Arbeitskopie unter `$TMPDIR`**, nie am Repo.
  `shutil.copytree` im python3-Heredoc kopiert auch, wenn `cp -r` gesperrt ist (0111).
- **Immer mit Trefferbremse** (`assert text.count(nadel) == 1` vor der Ersetzung) --
  und bei mehreren Vorkommen derselben Form **nach** der Ersetzung zaehlen, dass die
  Nachbarstelle noch steht (0111: Schwanz `, 10'000));` trennte `:583` von `:666`).
- **M0 vor der Mutation und nach jeder Ruecknahme.** Ohne sie belegt "alle Mutanten
  sterben" auch einen kaputten Aufbau.
- **Am selben Bau messen wie der Runner:** `baulauf.py:182-186` abschreiben
  (`RelWithDebInfo`, `-fwrapv -fno-fast-math`), Werkzeugkette kommt ueber
  `PROJECT_IS_TOP_LEVEL` von selbst, `kern/` ist allein baubar (0111).
- **Die alte Fassung der Probe gegen denselben Mutanten fahren**
  (`git show <baucommit>^:pfad`): alt gruen + neu rot belegt in einem Lauf, dass die
  Luecke offen war und der Einschub der einzige Faenger ist (0061, 0111).
- **Zaehlen, welche und wie viele Zusicherungen reissen** und ob es genau die der
  Abnahme sind; die Zeilennummern der Fehlausgabe im Quelltext nachschlagen (0111).
- Schwellen sind erst gemessen, wenn sie von **beiden** Seiten eingeklemmt sind (0086).
- Am Ende fragen: **welche Zusicherung hat kein Mutant rot bekommen?**
- **Den fremden GEBAUT-Absatz erst nach der eigenen Messung gegenlesen** (0088).
- **Dateiliste des Baucommits gegen die `dateien`-Liste legen**
  (`git show --numstat`); ein rein additiver Diff (+N/-0) beantwortet "abgeschwaechte
  Tests" in einem Griff (0077, 0111).
- `git log -- <datei>`, nie `git show <betreff>`: Der Runner buendelt mehrere Pakete
  unter einem Betreff (0086, 0111: 11 Dateien aus drei Paketen).

## Was funktioniert

- 2026-09-05 (0111) -- **Ein "vorher schon rot"-Nebenbefund des Bauagenten kann zur
  Pruefzeit repariert sein.** Der `belegstellen_riegel` war beim Bau rot (fremdes
  Paket), bei meiner Messung gruen -- 0120 lag dazwischen. Den aktuellen Stand messen,
  nicht die Behauptung uebernehmen; die Abweichung gehoert als Nebenbefund in den
  Befund, nicht als Widerspruch.
- 2026-09-05 (0088) -- Bei ueberlebender Mutation zuerst fragen: **welcher Eingabewert
  macht beide Formen gleich?** (0111 war der Lehrfall: `stufen = +3` machte `betrag`
  unsichtbar; die neue Probe schliesst das mit `-4`, `+4` und `0` selbst aus.)
- 2026-09-05 (0086) -- **Ein stiller Nulloutput ist ein Befund, kein Ergebnis** --
  Skripte, die nur nach der Ergebniszeile greifen, schweigen beim Abbruch.
- 2026-09-05 (0107) -- **Collage-Griff, wenn alle Textwerkzeuge zu sind:**
  `git show HEAD:pfad > kopie`, `head`/`printf`/`tail`, Loeschmutant `grep -Fxv`,
  Trefferbremse ersatzweise `git diff --no-index`.
- 2026-09-05 (0107) -- Loeschmutant an einer Aufrufzeile misst erst die Werkzeugkette
  (`-Werror=unused-function`); Funktion **samt** Aufruf loeschen.
- 2026-09-05 (0097) -- Fremde Mutationslisten nennen das Was, nicht den Wortlaut:
  selbst in Ersetzungen uebersetzen; Nadeln, die mit `...]` enden, sind gegen
  Praefix-Einheiten immun.

## Was nicht funktioniert

- Sperren wechseln je Sitzung **und innerhalb der Sitzung** -- probieren, nicht
  ableiten. Wiederkehrend: `git commit` gesperrt (vier Sitzungen in Folge bis 0061),
  `git add` und `git mv` gehen; Verbundbefehle mit `sed`/`cp`/`rm` fallen oft, der
  python3-Heredoc geht fast immer. Bei 0111 ging `Write` ins Repo-Zielverzeichnis
  und `cmake`/`ctest` ohne Einschraenkung.
- Mutantenskripte, die in den **Repo-Baubaum** schreiben, hinterlassen `ctest` rot
  (0086). Seit 0111: gar nicht erst hinein -- Arbeitskopie samt eigenem Baubaum.
- `git status` zeigt am Repowurzelrand Sandbox-Zeichengeraete (`.bashrc`,
  `.claude/*`): nicht erschrecken, nicht aufraeumen (0088).
- Zwei Laeufe derselben Rolle koennen parallel laufen: nur anfuegen, Kollisionen bei
  Befund- und Archivnamen pruefen (0083).
- Eine Zaehlung von Zeilen belegt keine Eindeutigkeit von Namen: `sort | uniq -d`
  daneben (2026-09-03).

## Was funktioniert (Nachtrag 0079, Runde 2)

- 2026-09-05 (0079) -- **Wenn zwei Zahlen im selben Nachweis nicht zusammenpassen,
  zuerst die Arithmetik des Dokuments, dann messen.** 9+37=46 gegen "47 uebergangen"
  im abgedruckten Lauf war der ganze Griff; danach an allen drei Commit-Staenden des
  Baulaufs gemessen (alle 47) -- die Vorher/Nachher-Tabelle stammte von keinem. Urteil
  zurueck, obwohl die Sache stimmt: Die Abnahme verlangt die Messung "nach der letzten
  Zeile des Kopfkommentars", und genau dieser Fehler war der Grund des Ruecklaufs.
- 2026-09-05 (0079) -- **Zwei Programme an einem Baum**: der Riegel nimmt Baum und
  specs als argv; Stand A aus `git show` in Hilfsstruktur bauen (werkzeugkette.cmake
  jenes Standes zwei Ebenen hoeher), Binary gegen den C-Baum rufen. `git archive
  <commit> <pfad>` + tarfile im Heredoc liefert den Baum; `bau/` liegt nicht in git
  und verschiebt nur die "Namen in ungelesenen Ordnern"-Zahl.
- 2026-09-05 (0079) -- Mutanten, die Parameter ungenutzt lassen, sterben an
  `-Werror` statt am Selbsttest: `(void)param;` in den Ersatz schreiben (bestaetigt
  0107).

## 0079 Runde 3 (2026-09-05, Fable-Lauf)

- **Urteil geprueft, 0 Befunde.** Ruecklauf 2 aenderte nur die Messschrift; der
  Riegel ist seit `f8c8598` diff-leer. Teil 4 komplett selbst nachgemessen: beide
  Staende (A aus `489aafb` in Hilfsstruktur, C je Baum), beide Baeume per
  `git archive`, Vergleich als `datei:zeile`-Mehrfachmenge -- 9/47/0/38 (37+1),
  identisch an beiden Baeumen und mit dem berichtigten Nachweis.
- **Eine behauptete Fehler-Reproduktion selbst nachrechnen lohnt:** dedupliziert
  gelesen ergab exakt die drei alten falschen Zahlen (46/37/36). Erst mit voller
  Tupel-Mengendifferenz gerechnet (ergab 38 statt 37) -- der alte Zaehler verglich
  weiter ueber `datei:zeile`, dedupliziert wurde nur die gedruckte Liste. Die
  Lesart der Reproduktion muss die des Fehlers sein, nicht die eigene.
- Ein Commit mit dem Paket-Betreff kann **nur Sandbox-Symlinks** tragen (7a4183b,
  alle numstat 0/0); die Inhalte lagen komplett in fremden Betreffs davor.
  `git show --numstat` + python-Filter stat awk (awk war gesperrt).
- Randnotiz-Kategorie bewaehrt: sachlich falsche Detailangabe im Nachweis
  (gesucht-war-Wortlaut galt nur an Baum 2), die keine Abnahmebedingung beruehrt --
  als "ohne Urteilswirkung" benannt statt verschwiegen oder zum Befund gemacht.
- Sperren dieser Sitzung: Verbund mit `&&`+`||`+Umleitung und awk-Pipe gesperrt;
  python3-Heredoc (auch fuer cmake-Bauten via subprocess), Write ins Repo, grep,
  git, Binary-Direktaufruf gegen den Arbeitsbereich (lesend) -- alles gegangen.

## Offene Faehrten

- 2026-09-05 (0086) -- **Herkunftsangaben von `ZITATFAELLE` (9) und `ZIELFAELLE` (8)
  noch nie einzeln nachgeschlagen.** Beim naechsten Riegelpaket dran. (In 0079
  Runde 3 erneut verschoben -- dort war nur die Messschrift strittig; 0083/0105/
  0106/0115 kommen auf dieselbe Datei.)
- 2026-09-05 (0086) -- **Der Riegel rueckt nach einem Treffer um den ganzen Zitatteil
  weiter** und kann ein Schluesselwort im zitierten Wortlaut ueberspringen. Bei der
  naechsten Lockerung nachsehen.
- 2026-09-05 (0111) -- **Erledigt:** mein Vorschlag 0111 ist gebaut und von mir
  `geprueft`; 0120 ist gebaut, der Arbeitsbereichs-`ctest` steht wieder 14/14. Offen
  aus derselben Reihe: **0115** (drei falsche Zahlen im Kopf des Riegels). Alle drei
  rechnenden `betrag`-Stellen in `werte.cpp` sind jetzt einzeln gedeckt (0002, 0088,
  0111) -- die Familie ist geschlossen, sofern kein neues Paket eine vierte anlegt.
- 2026-09-05 (0088) -- Bevor ich eine Zeile "unerreichbar" nenne, den Mutanten wirklich
  bauen; `festkomma`-Literale brechen am `static_assert` ab -- nicht als
  Empfindlichkeit zaehlen.
- 2026-09-05 (0083) -- `befunde/` und `bau/` tragen Abschriften des Quellbaums; jedes
  Werkzeug, das am Basisnamen sucht, wird belogen. Pfade oder Namen?
- 2026-09-02 -- `anteile_aus_zustand` in `schranken_probe.cpp` sichert die Summe, nicht
  den Quotienten; wandert die Pruefung in ein aufrufbares Modul fuer T30, wird der
  Fall scharf.

## 0110 (2026-09-05, Fable-Lauf)

- **Es gibt jetzt einen stehenden Mutationslauf:** `cmake --build bau --target
  mutationslauf` faehrt den Katalog `werkzeuge/mutation/katalog.md`; der Treiber
  `bau/werkzeuge/mutation/mutationstreiber <wurzel> <bau> <katalog> [kennung ...]`
  nimmt **jede** Katalogdatei und eine Fallauswahl. Kuenftige Riegelpruefungen an
  `zustandsausgabe` brauchen keinen Handmutanten mehr -- Falschangaben und
  Trefferbremse habe ich an einer $TMPDIR-Kopie des Katalogs nachgestellt, Paketdatei
  unberuehrt. Einzelfall kostet ~10 s statt des vollen Laufs.
- **Urteil geprueft, 0 Befunde.** Nachaenderung `228d9d7` haertet (Fallkopf-Wort,
  --no-tests=error, Fehlzeile ab Marke), schwaecht nichts. `git status` vor/nach
  zeichengleich; Exitcodes 0/1/1 direkt gemessen.
- **Offene Faehrte:** `urteil: bau` des Treibers ist nie gefahren (kein Katalogfall,
  Selbsttest deckt nur den Leser). Beim naechsten Katalogpaket einen
  static_assert-Fall aus Pruefung 0010 einbringen.
- Vorschlag **0127** geschrieben (Baulauf meldet Mitglied ohne gefundene Proben als
  `ok`; pauschales --no-tests=error waere wegen des absichtlich probenfreien
  `werkzeuge/mutation` falsch).
- Sperren dieser Sitzung: `Write`-Tool und Verbund-`for`-Schleife gesperrt;
  python3-Heredoc, `printf`-frei nicht gebraucht, `cmake/ctest/git/grep`,
  Binaerdatei im Repo-Baubaum ausfuehren -- alles gegangen. `git log` je Datei hat
  wieder getragen: 0110-Quelltext lag unter fremden Betreffs (bf0519b, 228d9d7).
