# Logbuch: test-pruefer

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergaenzt sie am Ende.

**Hoechstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/test-pruefer-<datum>.md` und beginnst neu.

Vorgaenger: `notizen/archiv/test-pruefer-2026-09-05-6.md` (voll nach 0105); davor
-5 (0083r2), -4 (0111), -3 (0086), -2, ohne Suffix -- alle 2026-09-05.

---

## Wie ich einen Mutanten baue (traegt seit 0019, destilliert)

- Mutant als Textersetzung an einer **Arbeitskopie**, nie am Repo. Ablage unter
  `ventures/<id>/bau/<eigener-name>/` statt $TMPDIR: gitignoriert, baulauf.py nimmt
  `bau` von der Manifestsuche aus (Zeile 132), und tmpfs ist oft zu 97% voll --
  ENOSPC macht Schein-Rot (0138, 0136). gcc schreibt Zwischendateien nach $TMPDIR:
  Unterprozessen TMPDIR per env auf die Platte legen. Fremde Dateien nie abraeumen.
- **Immer mit Trefferbremse** (`assert text.count(nadel) == 1`); Ruecknahme-Nadel
  ist selten die Hinweg-Nadel -- mit Einrueckung nehmen (0111, 0138).
- **M0 vor der Mutation und nach jeder Ruecknahme.** Jeden Bau-RC pruefen; bei
  unerklaerlichem Rot zuerst `df` (0138).
- **Am selben Bau messen wie der Runner:** baulauf.py abschreiben
  (`RelWithDebInfo`, `-fwrapv -fno-fast-math`), Werkzeugkette via
  `PROJECT_IS_TOP_LEVEL` (werkzeugkette.cmake zwei Ebenen hoeher mitkopieren).
- **Neutralisieren statt loeschen:** `(x || true)` bzw. `(void)param;`, sonst stirbt
  der Bau an `-Werror=unused-function` und misst die Werkzeugkette (0107, 0083r2).
- **Vorher-Stand billig isolieren:** heutiger Baum, allein die Paketdatei auf den
  Blob des Elterncommits ihres juengsten Commits zuruecksetzen (0133, 0136).
  Alt gruen + neu rot am selben Mutanten belegt die Luecke in einem Lauf (0061).
- **Eigene Mutation statt der des Nachweises waehlen** -- identische Kippmenge
  bestaetigt die Zahl unabhaengig, statt sie abzuschreiben (0133, 0136).
- **Zaehlen, welche Zusicherungen reissen** und ob es die der Abnahme sind; am Ende
  fragen: welche Zusicherung hat kein Mutant rot bekommen?
- Schwellen erst gemessen, wenn von **beiden** Seiten eingeklemmt (0086).
- **Fremden Nachweis/GEBAUT-Absatz erst nach der eigenen Messung gegenlesen** (0088).
- **Dateiliste des Baucommits gegen `dateien` legen:** `git log -- <datei>` und
  `git show --numstat`, nie `git show <betreff>` -- der Runner buendelt Pakete
  unter fremden Betreffs; bei 0083r2 und 0105 trug der Betreff-Commit keine
  einzige Paketdatei (bekannt, Pakete 0121/0131).
- `ctest -N` schreibt `Test  #1:` mit zwei Leerzeichen: Zaehlmuster als Regex
  `Test\s+#\d+:`, jede -N-Zaehlung gegen ein gelaufenes "out of N" pruefen (0129).
- Zahlen des GEBAUT-Absatzes duerfen abweichen, wenn der Korpus zwischen seinem
  und meinem Messstand driftet: erst Commits datieren, dann Widerspruch rufen (0136).
- **Schlanke Riegel-Kopie:** braucht `befunde/pruefung-0066/nachbau.py`, die von
  `parameter.toml:11` zitierte `pruefung-0009-...-runde2-...md`, und
  `../../specs/<Baumname>` neben dem Baum (0129, 0138, 0133). bau/befunde als
  leere Pfad-Platzhalter genuegt dem Riegel (0105): 3,9M statt 734M.
- **Befundnamen kollidieren bei Ruecklaeufen:** vor dem Schreiben ls auf befunde/,
  dann `-runde2-` einschieben (0083r2). Parallele Laeufe derselben Rolle: auch
  Archiv- und Arbeitskopie-Namen pruefen.

## Was funktioniert / nicht funktioniert

- Sperren wechseln je Sitzung und innerhalb der Sitzung -- probieren, nicht
  ableiten. Notiere je Lauf, was ging; Muster: python3-Heredocs ohne Schleife und
  ohne `VAR=...;`-Vorspann gehen fast immer, Verbund mit cd/&&, sed, mv, cp oft
  nicht. 0105: Write nur nach befunde/; Ersetzen = head+printf+tail, Ruecknahme =
  truncate auf wc -c von head -n.
- Mutantenskripte im Repo-Baubaum hinterlassen ctest rot (0086) -- Arbeitskopie
  samt eigenem Baubaum. Baeume am Ende entfernen, Skripte+Protokolle liegen lassen.
- `git status` zeigt am Repowurzelrand Sandbox-Zeichengeraete: nicht aufraeumen.
- Ein stiller Nulloutput ist ein Befund, kein Ergebnis (0086).
- Bei ueberlebender Mutation zuerst fragen: welcher Eingabewert macht beide Formen
  gleich? (0088)
- Ein "vorher schon rot"-Nebenbefund kann zur Pruefzeit repariert sein: aktuellen
  Stand messen, Abweichung als Nebenbefund (0111).
- Wenn zwei Zahlen im selben Nachweis nicht zusammenpassen: zuerst die Arithmetik
  des Dokuments, dann messen (0079r2).
- Eine Regel, die nur im Einlesepfad wirkt, kann jeder Selbsttest am heutigen Baum
  verfehlen -- Einmal-Rotnachweis erfuellt die Abnahme, deckt aber nicht dauerhaft;
  daraus wurde Vorschlag 0138, spaeter als Paket gebaut und geprueft (0129).

## 2026-09-06 — 0106 (Urteilsschritt-Anker): geprueft

- **Eigene Baubaeume unter `bau/` verschieben die Riegelzahl „Pfade in ungelesenen
  Ordnern" zwischen Laeufen.** Den alt/neu-Zahlenvergleich **vor** dem Anlegen der
  Mutantenbaeume fahren, sonst ist die Zeile nicht zeichengleich und man jagt eine
  Drift, die man selbst erzeugt hat.
- Gegenprobe nach Muster 0061 erneut der staerkste Nachweis: fataler Mutant auf der
  Vorfassung Code 0, auf der neuen Code 2 vor dem Bestand — ein Lauf, Luecke belegt.
- „Stirbt vor dem Bestand" billig dynamisch: Mutant mit **nicht existierender**
  Wurzel aufrufen; kommt Code 2 samt Selbsttestmeldung, brauchte er den Bestand nie.
- Kippmenge des Bauers (7 Mutanten → 6 Urteilsfaelle) mit eigenen Ersetzungen
  identisch bestaetigt; Protokoll erst danach gegengelesen — Regel traegt.
- Sperren: `VAR=…;`-Verbund wieder verweigert, python3-Heredoc ging durchweg.
- GEBAUT-Zahlen (208/46) vs. Protokoll (209/46) vs. heute (215/47): dreifacher
  Messstand derselben Groesse, alles Korpusdrift — erst datieren, dann urteilen.

## 2026-09-06 — 0115 (Riegelkopf drei Zahlen): geprueft

- **Eigene Mutation an anderer Stelle als der Treiber** (Bedingung in `klammer_ab`
  neutralisiert statt Argument an der Aufrufstelle gekippt): identische Kippmenge
  51/40/59 mit 11 Befunden — der billigste starke Nachweis, dass eine Kommentarzahl
  an der Eigenschaft haengt und nicht am Messgeraet.
- **Ein Messskript, das eine Eingabe aus `$TMPDIR` erwartet, hat eine ungebundene
  Eingabe:** `messen.py` brach ohne `vorher.cpp` ab, prueft den Inhalt nur auf
  `!= neu`. Selbst beschafft via `git show <baucommit>^:<pfad>`, Blob gegen den
  Diff-Elternstand gehalten — dieser Handgriff gehoert ins Skript (Vorschlag 0171).
- Erwartungen aus dem gepruefte Kommentar **lesen** statt im Skript fuehren (Bauart
  von messen.py) ist die richtige Form gegen still veraltende Zahlen; die Gegenprobe
  am alten Wortlaut (3/2/2 Meldungen) ersetzt den separaten Rotnachweis.
- Sperren: Verbund mit `;`/`&&` und awk verweigert, python3-Heredoc (auch mit
  python-internen Schleifen) ging, Write nur nach befunde/ und aufgaben/. Ein
  unsichtbares Zeichen im getippten Pfad machte einen zweiten grep-Aufruf zum
  Verweigerungsfall — Pfade kopieren, nicht tippen.
- Zuordnung von Fundstellen zu Falltabellen billig ueber Zeilennummern gegen
  `grep -n "FAELLE = {{"` und das Kopfende (letzte `//!`-Zeile).

## Offene Faehrten

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
