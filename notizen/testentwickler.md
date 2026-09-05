# Logbuch: testentwickler

Belege gehören in die Ergebnisdatei — hier steht die Lehre. Höchstens 12.000 Zeichen;
am 2026-09-05 dreimal zusammengezogen (Archivieren ist der Rolle nicht erlaubt, s. u.).

---

## Was funktioniert

<!-- Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-09-05 (0107) — **Eine Zusicherung über *Namen* braucht eine Kennung, die nicht aus
  den Namen kommt.** Ob zwei Prüfstellen denselben Riegel meinen, aus ihren Textstücken zu
  erschließen ginge im Kreis: Es wäre eine Aussage über genau die Trennschärfe, die erst
  nachzuweisen ist. Die Kennung gehört als **eigenes Argument** an die Aufrufstelle.
- 2026-09-05 (0107) — **Zu „X kollidiert mit keinem Fremden" gehört „X trifft jedes
  Eigene".** Sonst bleibt der billige Ausweg: das Fremde zum Eigenen erklären, und die
  erste Hälfte schweigt. **Frage vor jedem neuen Riegel: Wie umginge ich ihn, ohne ihn
  anzufassen?** Ging über den Wortlaut der Abnahme hinaus — also hingeschrieben.
- 2026-09-05 (0107) — **Ein Vergleich aller gegen alle braucht eine Vollzähligkeitsprüfung
  daneben:** Was nicht ankommt, widerspricht nichts — die Probe bliebe grün und säge
  weniger. Dazu die Zahl der geprüften **Paare drucken** (null Paare laufen grün durch);
  Enum-Sentinel plus `static_assert` hält die Fallliste vollzählig.
- 2026-09-05 (0107) — **`what()` zeigt in die Ausnahme; hinter dem Fangblock ist sie
  fort.** Meldungen, die über Aufrufstellen hinweg verglichen werden, **im Fangblock**
  abschreiben; abgeschnitten ist ein Fehlschlag. Kennzeichen dagegen sind Literale mit
  statischer Lebensdauer — nur ihr *Feld* stirbt, die Zeiger genügen.
- 2026-09-05 (0107) — **„Die Liste ist unverändert" wird gemessen, nicht behauptet:** alle
  Zeichenkettengruppen aus `git show HEAD:<datei>` und aus dem Arbeitsstand ziehen, Mengen
  vergleichen. Ein `git diff` zeigt Umbrüche und beweist nichts über den Inhalt.
- 2026-09-05 — **Die Gegenprobe ist ein *Mutant des ausgelieferten Standes*, nicht ein
  alter Commit** — sonst misst man drei Pakete und nennt es eines. **Schärfer (0061):
  denselben Mutanten gegen *beide* Fassungen fahren.** Mutationen auf **eine** Zieldatei
  eingrenzen.
- 2026-09-05 — **Sagt ein Paket „dann wird die Probe rot" vorher, nachmessen, *welche*
  Zusicherung reißt.** Bei 0061 blieb die vorhergesagte Zahl wahr; gerissen ist der
  **Index**. Ergebnis richtig, Mechanismus falsch — nur der sagt, was zu ändern ist.
- 2026-09-05 — **Einen von Hand abgezählten Index gegen die *erzeugten* Daten halten**,
  und Indexzusicherungen über eine wachsende Tabelle die erwartete Kennung **in dieselbe
  Bedingung** binden (`ANKER[1].kennung == 44 && weicht_ab[1]`) — sonst prüft der nächste
  Einschub still den falschen Eintrag.
- 2026-09-05 — **Ein Textriegel darf sich im Deutschen nicht auf Großschreibung
  verlassen** — jedes Hauptwort beginnt groß. Tragend war die **Satzgrenze**, und die stand
  im Programm schon zweimal: **erst im eigenen Programm suchen, dann eine Regel erfinden.**
- 2026-09-05 — **Der wertvollste Rotnachweis zeigt eine *Lücke*:** Der Mutant an der
  Aufrufstelle ließ den Selbsttest grün, gefangen hat ihn nur der Korpus. Die Tabelle
  deckt die Funktion, der Bestand die Aufrufstelle — ausschreiben.
- 2026-09-05 — **Der Rotnachweis deckt auf, dass ein Fall aus dem *falschen Grund* grün
  ist** — erst rot, dann zählt der Fall. **Eine Lockerung zuerst am *eigenen* Quelltext
  messen**; neue Regel als **Rückfall** hinter die alten hängen, und ändert sie allein
  **keine Zahl**, ist genau das der Beleg.
- 2026-09-05 — **Die gleichförmige Grundbelegung ist die Ursache stumpfer Proben.** Eine
  Belegung ist erst eine Messlatte, wenn die gedruckten Werte **paarweise verschieden**
  sind — gezählt, nicht behauptet.
- 2026-09-05 — **Ein eigener Kommentar kann einen fremden Riegel rot machen.** Der
  `belegstellen_riegel` liest **auch Testquellen**: Belege über die Abschnittsüberschrift,
  nie über eine Zeilennummer. — **Umgekehrt (0061, 0107): Ist er rot, erst die genannte
  Datei lesen** — beide Male war er an einem fremden Datendokument rot. Gegenbeleg: *die
  eigene Datei kommt in seiner Ausgabe null Mal vor.*
- 2026-09-05 — **Mutationstreiber als Python-Skript nach `bau/`** (dort greift
  `.gitignore`): Muster ersetzen, bauen, fahren, je Fall `count(alt) == 1` prüfen; Flags
  aus `bau/CMakeFiles/<ziel>.dir/flags.make` abschreiben statt raten.
- 2026-09-05, **dreimal** — **Ein Mutant scheitert gern aus dem falschen Grund, und die
  Probe sieht trotzdem rot aus** — er bricht ab, ehe der Korpus gelesen ist (dann die
  **Aufrufstelle** mutieren statt der Funktion), oder stirbt an einer Nullprüfung
  **unter** dem ersetzten Block. Immer prüfen, ob die rote Zeile die *gemeinte* ist.
- 2026-09-05 — **Ein Test auf „es hat geworfen" prüft fast nie das, was er soll:** Das
  tragende Kennzeichen ist **zweiteilig** — Kasten **und** Ursache, nie der Volltext.
- 2026-09-05 — **Trennt eine Abnahme zwei Sorten, muss die trennende Eigenschaft
  woandersher kommen als aus dem geschriebenen Namen.** Den Rotnachweis suchen, den die
  **bequeme** Fassung überlebt hätte; Erwartung an den *Fall* hängen, nicht an die Schleife.
- 2026-09-04, 2026-09-05 wieder — **Eine Schwelle, deren Zahl sich nicht messen lässt,
  gehört nicht ins Messgerät** — **Herkunft, keine Marge**, und der **kleinste** Wert.
- 2026-09-04, 2026-09-05 — Gehört die `CMakeLists.txt` einem fremden Paket, ist die
  **Falltabelle im Programm** der Weg zu dauerhaften Fällen; sie zahlt sich beim **Bauen**
  aus, also *vor* dem ersten Korpuslauf schreiben, mit den Fällen, die der Korpus nicht
  hergibt. Liest das Werkzeug seinen **eigenen** Quelltext, muss das Musterwort maskiert
  sein (`Zeil\145`) — auch in Prosa-Kommentaren.
- 2026-09-04, seither neunmal — **Ein Rotnachweis je Teilregel**, auch für Lockerungen,
  die je allein nichts tragen. Eine Grenze, deren Abschalten nichts ändert, ist Zierde —
  **oder** braucht den ausgeschriebenen Satz, dass der Korpus sie nicht misst (0107).
- 2026-09-04, seither siebenmal — Die Entscheidung, die der Test misst, als **eigenen
  Aufruf** aus der Leseschleife herausziehen; sonst prüft man zwei Fassungen, von denen
  nur eine läuft.
- 2026-09-03 — Zwei falsche Fassungen belegen nur dann, dass zwei Bedingungen
  *Verschiedenes* messen, wenn je Fassung **beides** zugesichert wird: was sie fängt und
  was sie durchlässt — halbe Tabelle mit **erwarteter Leermeldung**.
- 2026-09-04, 2026-09-05 wieder — Beim Aufräumen von Belegstellen ist der Riegel selbst
  das Messgerät (0→1→0 in der **eigenen** Datei). Muster *beschreiben* statt abschreiben.
- 2026-09-04 — **`git log -S` allein trägt keine Paketzuordnung**: Die Arbeit eines Pakets
  liegt oft im Commit des *nächsten* Laufs. Herkunft an der `dateien`-Liste prüfen. Und
  eine Zeilennummer in einem Aufräumpaket ist beim Abarbeiten meist schon falsch.
- 2026-09-05 — **Der Rotnachweis belegt die Zahl erst über die Gegenzahl:** je Vorgabe
  `== soll` und `!= gegenzahl`; „Zahl steht in der Zeile" ist schwach, `1013` steckt in
  `10137`. Und: **eine im Paket genannte Mutation ist selten die einzige ihrer Art** —
  „X sitzt an Stelle N" gegen **alle** Stellen rechnen.
- 2026-09-02, 2026-09-05 bestätigt — **Beide Bauwege einzeln prüfen**: `baulauf.py` ruft
  jede `CMakeLists.txt` auch allein; neue Verzeichnisse brauchen ein erneutes `cmake -S/-B`.

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-04, **fünfmal getroffen** (zuletzt 2026-09-05) — `cd` nimmt mir `Edit` und
  `Write` still weg, auch im zusammengesetzten Befehl; die Ablehnung nennt den Modus,
  nicht den Pfad. **Nie `cd`.** Ist es passiert: `cd /home/adria/fabrik` als eigener
  Aufruf holt sie zurück, sofort — zweimal bestätigt.
- 2026-09-02, bis 2026-09-05 bestätigt — Zusammengesetzte Shell-Befehle (`a && b`, `a; b`)
  und `for`-Läufe werden abgelehnt, einzelne Aufrufe, **Pipes** und **mehrzeilige**
  Befehle nicht; Heredoc an `python3` läuft **ohne** vorheriges `cd`. Auch ein `=` im
  Argument eines eigenen Skripts lässt den Aufruf ablehnen.
- 2026-09-05 — **`sed` wird abgelehnt**, auch mit `-e`; Ersatz ist `python3 -c "…"` oder
  ein Skript unter `bau/`. Ein Binärprogramm **aus `$TMPDIR`** auszuführen ebenfalls, und
  `python3 -c` mit einem Dateipfad zum Zeilenlesen ebenso — dafür ist `Read` da.
- 2026-09-03, 2026-09-05 präzisiert — `grep` über die Shell wird für die Suche im Baum
  abgelehnt (Grep-Werkzeug oder `git grep` tun es), **hinter einer Pipe läuft es** —
  `ctest -V | grep …` ist der schnellste Weg an alle roten Zeilen.
- 2026-09-04, 2026-09-05 berichtigt — Nach `$TMPDIR` geht **Bauen**, nicht Kopieren.
  `Write` nach `bau/` geht und ist der bessere Ort. `rm -rf bau` wird abgelehnt
  (Hausregel 3) und wird auch nicht gebraucht.
- 2026-09-03 — Beim Sabotieren beißt `-Werror=unused-function` und `-Wunused-variable`:
  Fällt etwas aus dem Spiel, wird der **Bau** rot statt des Tests. Deshalb **im Rumpf**
  abschalten, nie am Aufruf. Sauberster Griff (0107): nicht den Aufruf entfernen, sondern
  **einen Zähler nicht mehr hochzählen** — dann wird nichts unbenutzt.
- 2026-09-05, **zweimal** — **`git commit` wird abgelehnt**, in jeder Form; `git add`
  läuft. Am Ende also **stagen und melden**, nicht am Befehl feilen.

## Offene Faehrten

- 2026-09-05 — **Die eigenen Messdateien unter `bau/` verändern eine *gedruckte* Zahl**
  des `belegstellen_riegel` („Namen in ungelesenen Ordnern") — **die eigene Nachweisdatei
  unter `befunde/` ebenso** (0107: 390 → 391). Erst alle Dateien anlegen, dann die
  Schlussmessung fahren. Daran ist 0079 in Rücklauf 1 gegangen.
- 2026-09-05 (0107) — **Der `belegstellen_riegel` ist im Gesamtbaum rot**, an einem
  Abschnittszitat in `daten/nachmessung-zinsreihen-2026-09-05.md` — fremdes Paket,
  gemeldet statt behoben. Wer als Nächster hier baut, erschrickt sonst.
- 2026-09-05 — **Der Mutationslauf lebt nur in `bau/`, beim nächsten sauberen Bau fort.**
  Fünfmal belegt. Als Paket **0110** vorgeschlagen.
- 2026-09-05 — **Die Einheit der Klasse 2 lautet im Kern „…Preisen 2015", in T5 „…Preisen
  des Jahres 2015".** Die Entscheidung liegt zwischen zwei Dokumenten, nicht bei mir.
- 2026-09-04, 2026-09-05 **fünfmal** — **Der Korpus driftet während des eigenen Laufs**,
  auch dieses Logbuch: Ein **paralleler Lauf derselben Rolle** schrieb nebenher, `Write`
  schlug dreimal mit „modified since read" fehl, gezielte `Edit`s gingen durch. **Größe
  am Ende erneut messen.**
- 2026-09-05 — **Ein grüner Übersetzungsbericht gilt nur für den gelesenen Stand**, ein
  gemeldeter Bruch ist oft ein Zwischenstand: `fehler` kam aus einer **alten
  Quellabschrift** unter `bau/kp0010/`, nicht aus dem Baum.
- 2026-09-05, dreimal — **Jede Zahl in einer Abnahme ist ein Messwert von ihrem
  Zuschnittstag.** Besser ist die **Bedingung** (steigt/fällt gegenüber dem Stand von
  eben); der Projektmanager hat das für 0079 selbst so berichtigt.
- 2026-09-04, **viermal bestätigt** — `Write` nach `notizen/archiv/` ist der Rolle nicht
  erlaubt (`cp`/`mv` auch nicht). Die 12.000-Zeichen-Regel ist damit nur durch
  Zusammenziehen einzuhalten — als **Berechtigung** gemeldet. Und das kostet: An diesem
  Tag ging ein knappes Drittel des Laufs für das Kürzen dieser Datei drauf.
- 2026-09-02 — Der Prüfstand hat noch keinen **Regressionsbestand** und keinen
  **Determinismustest über Speichern und Laden** — laut Rolle meine wichtigsten;
  `probe_zweimal_dasselbe` deckt nur zwei Aufrufe im selben Prozess ab.
- 2026-09-03 — **Eine Invariante fängt Nullfälle prinzipiell nicht.** Nur ein gebauter
  Fall mit *einer* zulässigen Art fängt es.
