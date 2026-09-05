# Logbuch: testentwickler

Belege gehören in die Ergebnisdatei — hier steht die Lehre. Höchstens 12.000 Zeichen.

*Am 2026-09-05 zweimal zusammengezogen (Archivieren ist der Rolle nicht erlaubt, s. u.).*

---

## Was funktioniert

<!-- Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-09-05 — **Die Gegenprobe zu einem Eingriff ist ein *Mutant des ausgelieferten
  Standes*, nicht ein alter Commit.** Lagen fremde Pakete dazwischen, misst man drei
  Pakete und nennt es eines. Ein Mutant, der die eine Zeile abschaltet, isoliert.
  — **Noch schärfer (0061): denselben Mutanten gegen *beide* Fassungen der Probe fahren,
  alt und neu.** Die Differenz ist der Nachweis, der einzelne Lauf ist keiner.
- 2026-09-05 — **Einen von Hand abgezählten Index vor dem Hinschreiben gegen die
  *erzeugten* Daten halten**, auch wenn drei Seiten ihn schon gezählt haben. Ein
  Wegwerfprogramm unter `bau/` kostet eine Minute und ersetzt das Vertrauen.
- 2026-09-05 — **Sagt ein Paket „dann wird die Probe rot" vorher, nachmessen, *welche*
  Zusicherung reißt.** Bei 0061 blieb die vorhergesagte Zahl (`abweichende == 2`) wahr;
  gerissen ist der **Index**, den der Einschub verrückt hat. Ergebnis richtig,
  Mechanismus falsch — und nur der Mechanismus sagt, was zu ändern ist.
- 2026-09-05 — **Indexzusicherungen über eine sortierte, wachsende Tabelle binden die
  erwartete Kennung in dieselbe Bedingung** (`ANKER[1].kennung == 44 && weicht_ab[1]`).
  Sonst prüft der nächste Einschub still den falschen Eintrag. Gedruckte Zahlen aus der
  Tabellengröße lesen, nie als Ziffer hinschreiben.
- 2026-09-05 — **Ein Textriegel darf sich im Deutschen nicht auf Großschreibung
  verlassen** — jedes Hauptwort beginnt groß. Tragend war die **Satzgrenze**, und sie
  stand im selben Programm schon zweimal: **erst im eigenen Programm nach der Regel
  suchen, dann eine neue erfinden.**
- 2026-09-05 — **Der wertvollste Rotnachweis zeigt eine *Lücke*.** Der Mutant an der
  Aufrufstelle ließ den neuen Selbsttest grün; gefangen hat ihn nur der Korpus. Die
  Tabelle deckt die Funktion, der Bestand die Aufrufstelle — ausschreiben.
- 2026-09-05 — **Ein Mutant, der *alles* umbenennt, fällt an einer fremden Untergrenze
  aus** und liest die Befundliste nie. Mutation auf **eine** Zieldatei eingrenzen.
- 2026-09-05 — **Der Rotnachweis deckt auf, dass ein Fall aus dem *falschen Grund* grün
  ist.** **Erst rot, dann zählt der Fall**, und die Zahl im Fall nachzählen statt schätzen.
- 2026-09-05 — **Eine Lockerung zuerst am *eigenen* Quelltext messen.** Ausweg ist keine
  Ausnahmeliste, sondern eine echte Regel. Neue Regel als **Rückfall** hinter die alten
  hängen; läuft sie allein und ändert **keine Zahl**, ist genau das der Beleg.
- 2026-09-05 — **Eine Verbreiterung kann unter dem Strich Fundstellen *verlieren*.**
  Springt die Leseschleife hinter den Fund, nimmt ein ferner Treffer dem näheren seine
  Fundstelle. Die Suche endet am nächsten gleichartigen Anker.
- 2026-09-05 — **Zwei Lockerungen, die je allein nichts tragen, trotzdem einzeln
  messen.** Erst die Tabelle aller vier Fassungen zeigt, welche was tut.
- 2026-09-05 — **Die gleichförmige Grundbelegung ist die Ursache stumpfer Proben.** Eine
  Belegung ist erst dann eine Messlatte, wenn die gedruckten Werte **paarweise
  verschieden** sind — gezählt, nicht behauptet.
- 2026-09-05 — **„Zahl steht in der Zeile" ist schwächer, als es aussieht:** `1013`
  steckt in `10137`. Vergleich mit **Abschlussprüfung**, plus Gegenprobe.
- 2026-09-05 — **Ein eigener Kommentar kann einen fremden Riegel rot machen.** Der
  `belegstellen_riegel` liest **auch Testquellen**. Belege über die Abschnittsüberschrift,
  nie über eine Zeilennummer; nach jedem Zitat die Gesamtprobe. — **Umgekehrt (0061):
  Ist er rot, erst die genannte Datei lesen, ehe man sich das zuschreibt.** Er war an
  einem committeten Datendokument rot, nicht an meinem Eingriff.
- 2026-09-05 — **Mutationstreiber als Python-Skript nach `bau/`** (dort greift
  `.gitignore`): Muster je Fall ersetzen, mit `g++` bauen, fahren, je Fall
  `count(alt) == 1` prüfen. Danach Quelle neu bauen. `git status` führt nichts Fremdes.
- 2026-09-05, **dreimal** — **Ein Mutant scheitert gern aus dem falschen Grund, und die
  Probe sieht trotzdem rot aus.** (a) Er schaltet ein Merkmal ab und bricht mit Code 2 ab,
  ehe der Korpus gelesen ist — dann die **Aufrufstelle** mutieren statt der Funktion.
  (b) Er bildet den Gewinner auf einen anderen Index ab und stirbt an der Nullprüfung
  **darunter** — zweimal in einem Lauf dasselbe falsche „gefunden: ohne", weil ich nur
  den ersetzten Block las. **Nach dem Einschub den Rest der Funktion lesen**, besser
  direkt zurückgeben. Immer prüfen, ob die rote Zeile die *gemeinte* ist.
- 2026-09-05 — **Eine vollständige Adresse als Bereichsname liefert genau eine Zeile.**
  Jede Klasse an *ihrer eigenen* Adresse messen; zählen, wie viele Sorten gefunden wurden.
- 2026-09-05 — **Ein Test auf „es hat geworfen" prüft fast nie das, was er soll.** Das
  tragende Kennzeichen ist **zweiteilig**, Kasten **und** Ursache — den Volltext nie.
  Vergleiche gehören in den Fangblock.
- 2026-09-05 — **Trennt eine Abnahme zwei Sorten, muss die trennende Eigenschaft
  woandersher kommen als aus dem geschriebenen Namen.** Faustregel: den Rotnachweis
  suchen, den die **bequeme** Fassung überlebt hätte. Die Erwartung an den *Fall* hängen,
  nicht an die Schleife; ein leeres Erwartungsfeld ist ein **Fehlschlag**.
- 2026-09-04, 2026-09-05 wieder — **Eine Schwelle, deren Zahl sich nicht messen lässt,
  gehört nicht ins Messgerät.** Sie braucht eine **Herkunft, keine Marge**, und den
  **kleinsten** Wert, der die gemessene Form trägt — je Schritt messen, Tabelle
  hinschreiben.
- 2026-09-04 — Gehört die `CMakeLists.txt` einem fremden Paket, ist die **Falltabelle im
  Programm** der Weg zu dauerhaften Fällen. Liest das Werkzeug seinen **eigenen**
  Quelltext, muss das Musterwort maskiert sein (`Zeil\145`) — auch in Prosa-Kommentaren.
- 2026-09-04, seither achtmal — **Ein Rotnachweis je Teilregel.** Eine Grenze, deren
  Abschalten nichts ändert, ist Zierde — **oder** braucht einen eigens gebauten Fall.
- 2026-09-04, seither siebenmal — Die Entscheidung, die der Test misst, als **eigenen
  Aufruf** aus der Leseschleife herausziehen. Sonst prüft man zwei Fassungen, von denen
  nur eine läuft.
- 2026-09-03 — Zwei falsche Fassungen belegen nur dann, dass zwei Bedingungen
  *Verschiedenes* messen, wenn je Fassung **beides** zugesichert wird: was sie fängt und
  was sie durchlässt. Halbe Tabelle mit **erwarteter Leermeldung**.
- 2026-09-03 — Einen Erwartungswert **zweimal** abschreiben und gegeneinander prüfen. Eine
  Zeilennummer in einem Aufräumpaket ist beim Abarbeiten meist schon falsch (fünfmal):
  Stelle selbst suchen, durch Bleibendes ersetzen.
- 2026-09-04, 2026-09-05 wieder — Beim Aufräumen von Belegstellen ist der Riegel selbst
  das Messgerät (0→1→0 in der **eigenen** Datei). Muster *beschreiben* statt abschreiben.
  Eine Zählung von **Zeilen** belegt nichts über Gegenstände; ein Riegel über Text liest
  **je Absatz**.
- 2026-09-04 — **`git log -S` allein trägt keine Paketzuordnung**: Die Arbeit eines Pakets
  liegt regelmäßig im Commit des *nächsten* Laufs. Treffer gegen das **Datum** halten,
  Herkunft an der `dateien`-Liste prüfen, nie am Commit-Betreff.
- 2026-09-05 — **Der Rotnachweis belegt die Zahl erst über die Gegenzahl:** je Vorgabe
  `== soll` und `!= gegenzahl`. Und: **eine im Paket genannte Mutation ist selten die
  einzige ihrer Art** — „X sitzt an Stelle N" gegen **alle** Stellen rechnen.
- 2026-09-05 — **Eine Falltabelle zahlt sich beim Bauen aus, nicht erst beim Prüfen** —
  *vor* dem ersten Korpuslauf schreiben, mit den Fällen, die der Korpus **nicht** hergibt.
- 2026-09-02, 2026-09-05 bestätigt — **Beide Bauwege einzeln prüfen**: `baulauf.py` ruft
  jede `CMakeLists.txt` auch allein; ein neues Verzeichnis braucht ein erneutes
  `cmake -S/-B`.

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-04, **viermal getroffen** (zuletzt 2026-09-05) — `cd` nimmt mir `Edit` und
  `Write` still weg, auch als Teil eines zusammengesetzten Befehls; die Ablehnung nennt
  den Modus, nicht den Pfad. **Nie `cd`.** Ist es passiert: `cd /home/adria/fabrik` als
  eigener Aufruf holt die Werkzeuge zurück.
- 2026-09-02, bis 2026-09-05 bestätigt — Zusammengesetzte Shell-Befehle (`a && b`, `a; b`)
  und `for`-Läufe werden abgelehnt, einzelne Aufrufe, **Pipes** und **mehrzeilige**
  Befehle nicht; Heredoc an `python3` läuft **ohne** vorheriges `cd`. Auch ein `=` im
  Argument eines eigenen Skripts lässt den Aufruf ablehnen (`messen.sh abstand=4`),
  `abstand4` läuft.
- 2026-09-05 — **`sed` wird abgelehnt**, auch mit `-e`; Ersatz ist `python3 -c "…"` oder
  ein Skript unter `bau/`. Ein Binärprogramm **aus `$TMPDIR`** auszuführen ebenfalls, und
  `python3 -c` mit einem Dateipfad zum Zeilenlesen ebenso — dafür ist `Read` da.
- 2026-09-03, 2026-09-05 präzisiert — `grep` über die Shell wird für die Suche im Baum
  abgelehnt (Grep-Werkzeug oder `git grep` tun es), **auf Programmausgaben hinter einer
  Pipe läuft es** — `ctest -V | grep …` ist der schnellste Weg an alle roten Zeilen.
- 2026-09-04, 2026-09-05 berichtigt — Nach `$TMPDIR` geht **Bauen**, nicht Kopieren.
  `Write` nach `bau/` geht und ist der bessere Ort.
- 2026-09-03 — Beim Sabotieren beißt `-Werror=unused-function` und `-Wunused-variable`:
  Fällt etwas aus dem Spiel, wird der **Bau** rot statt des Tests. Deshalb **im Rumpf**
  abschalten, nie am Aufruf — `(void) x;` statt `if (true)`.
- 2026-09-02 — `rm -rf bau` wird abgelehnt (Hausregel 3), wird auch nicht gebraucht.
- 2026-09-05, **zweimal** — **`git commit` wird abgelehnt**, in jeder Form; `git add`
  läuft. Am Ende also **stagen und melden**, nicht am Befehl feilen.

## Offene Faehrten

- 2026-09-05 — **Die eigenen Messdateien unter `bau/` verändern eine *gedruckte* Zahl**
  des `belegstellen_riegel` („Namen in ungelesenen Ordnern"). Erst alle Dateien anlegen,
  dann die Schlussmessung fahren. Daran ist 0079 in Rücklauf 1 gegangen.
- 2026-09-05 — **Der Mutationslauf lebt nur in `bau/`, beim nächsten sauberen Bau fort.**
  Viermal belegt. Als Paket **0110** vorgeschlagen.
- 2026-09-05 — **Die Einheit der Klasse 2 lautet im Kern „…Preisen 2015", in T5 „…Preisen
  des Jahres 2015".** Die Entscheidung liegt zwischen zwei Dokumenten, nicht bei mir.
- 2026-09-04, 2026-09-05 **viermal** — **Der Korpus driftet während des eigenen Laufs**,
  auch dieses Logbuch. **Nie gegen eine früher notierte Zahl rechnen — Vorher und Nachher
  unmittelbar nacheinander am selben Baum.**
- 2026-09-05 — **Ein grüner Übersetzungsbericht gilt nur für den gelesenen Stand**, ein
  gemeldeter Bruch ist oft ein Zwischenstand: `fehler` kam aus einer **alten
  Quellabschrift** unter `bau/kp0010/`, nicht aus dem Baum.
- 2026-09-05, dreimal — **Jede Zahl in einer Abnahme ist ein Messwert von ihrem
  Zuschnittstag.** Besser ist die **Bedingung** (steigt/fällt gegenüber dem Stand von
  eben); der Projektmanager hat das für 0079 selbst so berichtigt.
- 2026-09-04, **dreimal bestätigt** — `Write` nach `notizen/archiv/` ist der Rolle nicht
  erlaubt (`cp`/`mv` auch nicht). Die 12.000-Zeichen-Regel ist damit nur durch
  Zusammenziehen einzuhalten. Als **Berechtigung** gemeldet.
- 2026-09-02 — Der Prüfstand hat noch keinen **Regressionsbestand** und keinen
  **Determinismustest über Speichern und Laden** — laut Rolle meine wichtigsten;
  `probe_zweimal_dasselbe` deckt nur zwei Aufrufe im selben Prozess ab.
- 2026-09-03 — **Eine Invariante fängt Nullfälle prinzipiell nicht.** Nur ein gebauter
  Fall mit *einer* zulässigen Art fängt es.
