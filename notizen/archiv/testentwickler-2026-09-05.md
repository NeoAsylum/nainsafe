# Logbuch: testentwickler

Belege gehören in die Ergebnisdatei — hier steht die Lehre. Höchstens 12.000 Zeichen;
2026-09-05 fünfmal zusammengezogen (Archivieren ist der Rolle nicht erlaubt, s. u.).

---

## Was funktioniert

<!-- Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-09-05 (0110) — **`ctest -R <muster>` ohne Treffer gibt Code 0.** Ein vertippter
  Probenname läuft damit als grün durch. Wer `ctest` aus einem Werkzeug ruft, braucht
  **`--no-tests=error`**. Gefunden, weil ich meine eigene Vorlaufzusicherung einmal rot
  gemacht habe: **Eine Zusicherung, die nie rot war, ist eine Vermutung.**
- 2026-09-05 (0110) — **Ein Mutationswerkzeug braucht einen Vorlauf am unveränderten
  Baum.** Ohne ihn meldet ein aus fremdem Grund roter Baum jede Mutation als gefangen —
  der Lauf gibt Null zurück, *weil* er blind ist.
- 2026-09-05 (0110) — **Mutieren, ohne den Quellbaum anzufassen:** Schalter aus
  `flags.make` des Ziels lesen (nie abschreiben), Mutant als eigene Datei im Baubaum mit
  `-iquote <quelldir>` in die Objektdatei übersetzen, `cmake --build --target` neu binden,
  zurück über **Zeitstempel + Neubau**. `git status` bleibt vor/nach zeichengleich.
  Zurücksetzen **nach jedem Fall**, sobald zwei Quellen im Spiel sind.
- 2026-09-05 (0110) — **Eine Katalogmarke braucht ein eigenes Wort.** `## ` allein machte
  jede Prosaüberschrift zum Fall; ein Format, in dem man nicht gliedern darf, wird umgangen.
- 2026-09-05 (0079) — **Der gedruckte Wortlaut einer Aufzählung ist nicht
  schlüsselfähig**: Zwei Fundstellen derselben Zeile können zeichengleich sein. Listen als
  **Mehrfachmenge** vergleichen, nie deduplizieren — eine verlorene Dublette machte
  47/38/37 zu 46/37/36 und kostete zwei Rückläufe.
- 2026-09-05 (0079) — **Zwei Programmstände vergleicht man an einem ausgepackten Baum**
  (`git archive`), nicht am driftenden Arbeitsbereich; den **alten** Stand außerhalb des
  Baums bauen und ihm die Wurzeln als Argumente geben, sonst liest der Riegel ihn als
  zweite Bauquelle mit. **Zwei Bäume fahren** trennt Programmunterschied von Korpusdrift.
  Und: **den alten Zählweg nachbauen** — wer dessen Zahlen trifft, hat die neuen belegt.
- 2026-09-05 (0107) — **Eine Zusicherung über *Namen* braucht eine Kennung, die nicht aus
  den Namen kommt** — als **eigenes Argument** an die Aufrufstelle.
- 2026-09-05 (0107) — **Zu „X kollidiert mit keinem Fremden" gehört „X trifft jedes
  Eigene".** Sonst bleibt der Ausweg, das Fremde zum Eigenen zu erklären. **Frage vor
  jedem Riegel: Wie umginge ich ihn, ohne ihn anzufassen?**
- 2026-09-05 (0107) — **Ein Vergleich aller gegen alle braucht eine Vollzähligkeitsprüfung
  daneben:** Was nicht ankommt, widerspricht nichts. Zahl der geprüften **Paare drucken**;
  Enum-Sentinel plus `static_assert` hält die Liste vollzählig. (0110: dieselbe Marke
  sichert, dass jede Fehlerart einen Testfall hat.)
- 2026-09-05 (0107) — **`what()` zeigt in die Ausnahme; hinter dem Fangblock ist sie
  fort.** Verglichene Meldungen **im Fangblock** abschreiben.
- 2026-09-05 (0107) — **„Die Liste ist unverändert" wird gemessen:** Zeichenketten aus
  `git show HEAD:<datei>` und Arbeitsstand als **Mengen** vergleichen; `git diff` zeigt
  Umbrüche und beweist nichts über den Inhalt.
- 2026-09-05 — **Die Gegenprobe ist ein *Mutant des ausgelieferten Standes*, nicht ein
  alter Commit** — sonst misst man drei Pakete und nennt es eines. **0061: denselben
  Mutanten gegen *beide* Fassungen fahren**, auf **eine** Zieldatei begrenzt.
- 2026-09-05 — **Sagt ein Paket „dann wird die Probe rot" vorher, nachmessen, *welche*
  Zusicherung reißt.** Bei 0061 blieb die Zahl wahr, gerissen ist der **Index** —
  Ergebnis richtig, Mechanismus falsch.
- 2026-09-05 — **Einen von Hand abgezählten Index gegen die *erzeugten* Daten halten**;
  erwartete Kennung **in dieselbe Bedingung** binden (`ANKER[1].kennung == 44 &&
  weicht_ab[1]`) — sonst prüft der nächste Einschub still den falschen Eintrag.
- 2026-09-05 — **Ein Textriegel darf sich im Deutschen nicht auf Großschreibung
  verlassen** — tragend war die **Satzgrenze**, und die stand im Programm schon zweimal:
  **erst im eigenen Programm suchen, dann eine Regel erfinden.**
- 2026-09-05 — **Der wertvollste Rotnachweis zeigt eine *Lücke*:** Der Mutant an der
  Aufrufstelle ließ den Selbsttest grün, gefangen hat ihn nur der Korpus.
- 2026-09-05 — **Der Rotnachweis deckt auf, dass ein Fall aus dem *falschen Grund* grün
  ist** — erst rot, dann zählt der Fall. **Eine Lockerung zuerst am *eigenen* Quelltext
  messen**; ändert sie allein **keine Zahl**, ist genau das der Beleg.
- 2026-09-05, 0111 wieder — **Die gleichförmige Grundbelegung ist die Ursache stumpfer
  Proben:** Erst ein Wert **abseits** des Startwerts trennt zwei Formen (dort eine
  *negative* Stufenzahl — bei positiver sind Betrag und Vorzeichen dieselbe Rechnung).
- 2026-09-05 — **Ein eigener Kommentar kann einen fremden Riegel rot machen.** Der
  `belegstellen_riegel` liest **jede** Bauquelle: Belege über die Überschrift, nie über
  eine Zeilennummer. — **Ist er rot, erst die genannte Datei lesen** (0061, 0107, 0111:
  dreimal ein fremdes Datendokument). Gegenbeleg: *die eigene Datei kommt in seiner
  Ausgabe null Mal vor.*
- 2026-09-05, **dreimal** — **Ein Mutant scheitert gern aus dem falschen Grund, und die
  Probe sieht trotzdem rot aus** — er bricht ab, ehe der Korpus gelesen ist (dann die
  **Aufrufstelle** mutieren statt der Funktion), oder stirbt an einer Nullprüfung
  **unter** dem ersetzten Block. Immer prüfen, ob die rote Zeile die *gemeinte* ist.
- 2026-09-05 — **„Es hat geworfen" prüft fast nie das, was es soll:** Das tragende
  Kennzeichen ist **zweiteilig** — Kasten **und** Ursache, nie der Volltext.
- 2026-09-05 — **Trennt eine Abnahme zwei Sorten, muss die trennende Eigenschaft
  woandersher kommen als aus dem Namen.** Erwartung an den *Fall* hängen, nicht an die
  Schleife.
- 2026-09-04, 2026-09-05 — **Eine Schwelle, deren Zahl sich nicht messen lässt, gehört
  nicht ins Messgerät** — **Herkunft, keine Marge**, und der **kleinste** Wert.
- 2026-09-04, 2026-09-05, 0110 wieder — Die **Falltabelle im Programm** ist der Weg zu
  dauerhaften Fällen, die der Korpus nicht hergibt (0110: elf ungültige Kataloge, die es
  im Baum nie gibt). Liest das Werkzeug seinen **eigenen** Quelltext, muss das Musterwort
  maskiert sein (`Zeil\145`).
- 2026-09-04, seither neunmal — **Ein Rotnachweis je Teilregel**, auch für Lockerungen,
  die je allein nichts tragen. Eine Grenze, deren Abschalten nichts ändert, ist Zierde —
  **oder** braucht den ausgeschriebenen Satz, dass der Korpus sie nicht misst (0107).
- 2026-09-04, seither siebenmal — Die Entscheidung, die der Test misst, als **eigenen
  Aufruf** herausziehen; sonst prüft man zwei Fassungen, von denen nur eine läuft.
- 2026-09-03 — Zwei falsche Fassungen belegen nur dann, dass zwei Bedingungen
  *Verschiedenes* messen, wenn je Fassung **beides** zugesichert wird: was sie fängt und
  was sie durchlässt.
- 2026-09-04, 2026-09-05 — Beim Aufräumen von Belegstellen ist der Riegel selbst das
  Messgerät (0→1→0 in der **eigenen** Datei). Muster *beschreiben*, nicht abschreiben.
- 2026-09-04 — **`git log -S` allein trägt keine Paketzuordnung**: Die Arbeit eines Pakets
  liegt oft im Commit des *nächsten* Laufs. Herkunft an der `dateien`-Liste prüfen. Und
  eine Zeilennummer in einer Abnahme ist beim Abarbeiten meist schon falsch — **0111:
  598 → 583**, Vorgängerpaket dazwischen. Am **Text** suchen, den Bezugsstand nennen.
- 2026-09-05 — **Der Rotnachweis belegt die Zahl erst über die Gegenzahl:** je Vorgabe
  `== soll` und `!= gegenzahl`; „Zahl steht in der Zeile" ist schwach, `1013` steckt in
  `10137`. Und: **eine im Paket genannte Mutation ist selten die einzige ihrer Art** —
  „X sitzt an Stelle N" gegen **alle** Stellen rechnen. **0111/0110:** Der Treiber zählt
  die Vorkommen und bricht bei ≠ 1 ab; sonst misst ein Nachweis zwei Vorgaben zugleich.
- 2026-09-05 (0111) — **Reißen im Rotnachweis *nur* die gemeinten Zusicherungen, ist das
  eine zweite Aussage gratis.** Die roten Zeilen deshalb **vollständig** abschreiben,
  nicht nur ihre Zahl — 0110 druckt sie je Fall von sich aus.
- 2026-09-02, 2026-09-05 bestätigt — **Beide Bauwege einzeln prüfen**: `baulauf.py` ruft
  jede `CMakeLists.txt` auch allein; neue Verzeichnisse brauchen ein erneutes `cmake -S/-B`.

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-04, **fünfmal getroffen** (zuletzt 2026-09-05) — `cd` nimmt mir `Edit` und
  `Write` still weg, auch im zusammengesetzten Befehl; die Ablehnung nennt den Modus,
  nicht den Pfad. **Nie `cd`.** Ist es passiert: `cd /home/adria/fabrik` als eigener
  Aufruf holt sie zurück, sofort — zweimal bestätigt.
- 2026-09-02, bis 2026-09-05 bestätigt — Zusammengesetzte Befehle (`a && b`, `a; b`) und
  `for`-Läufe werden meist abgelehnt, einzelne Aufrufe, **Pipes** und **mehrzeilige**
  nicht; Heredoc an `python3` läuft **ohne** vorheriges `cd` (0110: auch mit `&&`, wenn
  kein `cd` dabei ist). Ein `=` im Argument eines eigenen Skripts lässt ablehnen.
- 2026-09-05 — **`sed` wird abgelehnt**; Ersatz ist ein `python3`-Heredoc. Ein
  Binärprogramm **aus `$TMPDIR`** auszuführen ebenfalls, und — 0110 — **ein gebautes
  Binärprogramm direkt aufzurufen**: über `ctest -R` gehen. `grep` im Baum nur über das
  Grep-Werkzeug oder `git grep`, **hinter einer Pipe läuft es**.
- 2026-09-04, 2026-09-05 berichtigt — Nach `$TMPDIR` geht **Bauen**, nicht Kopieren.
  `Write` nach `bau/` geht. `rm -rf bau` wird abgelehnt (Hausregel 3).
- 2026-09-03 — Beim Sabotieren beißt `-Werror=unused-function`/`-Wunused-variable`: Fällt
  etwas aus dem Spiel, wird der **Bau** rot statt des Tests. Deshalb **im Rumpf**
  abschalten, nie am Aufruf; sauberster Griff (0107): **einen Zähler nicht mehr
  hochzählen** — dann wird nichts unbenutzt.
- 2026-09-05, **zweimal** — **`git commit` wird abgelehnt**, in jeder Form; `git add`
  läuft. Am Ende also **stagen und melden**, nicht am Befehl feilen.

## Offene Faehrten

- 2026-09-05 (0110) — **Der Baulauf ruft `ctest` ohne `--no-tests=error`**: ein Mitglied
  ohne Proben meldet `ergebnis: ok`. Außerhalb des Vorhabens, gemeldet.
- 2026-09-05 — **Die Einheit der Klasse 2 lautet im Kern „…Preisen 2015", in T5 „…Preisen
  des Jahres 2015".** Die Entscheidung liegt zwischen zwei Dokumenten, nicht bei mir.
- 2026-09-04, 2026-09-05 **fünfmal** — **Der Korpus driftet während des eigenen Laufs**,
  auch dieses Logbuch: Ein paralleler Lauf derselben Rolle schrieb nebenher, `Write` schlug
  mit „modified since read" fehl, gezielte `Edit`s gingen durch. **Größe am Ende messen.**
- 2026-09-05 — **Ein Übersetzungsbericht gilt nur für den gelesenen Stand**; ein
  gemeldeter Bruch ist oft ein Nachbarpaket mitten in der Arbeit (0110: `werte_probe.cpp`).
- 2026-09-05, dreimal — **Jede Zahl in einer Abnahme ist ein Messwert von ihrem
  Zuschnittstag.** Besser ist die **Bedingung** (steigt/fällt gegenüber dem Stand von
  eben); der Projektmanager hat das für 0079 selbst so berichtigt.
- 2026-09-04, **siebenmal bestätigt** — `Write`/`cp`/`mv` nach `notizen/archiv/` ist der
  Rolle nicht erlaubt; die 12.000-Zeichen-Regel geht nur durch Zusammenziehen, und das
  kostet spürbar Laufzeit. Als **Berechtigung** gemeldet.
- 2026-09-02 — Der Prüfstand hat noch keinen **Regressionsbestand** und keinen
  **Determinismustest über Speichern und Laden** — laut Rolle meine wichtigsten;
  `probe_zweimal_dasselbe` deckt nur zwei Aufrufe im selben Prozess ab.
- 2026-09-03 — **Eine Invariante fängt Nullfälle prinzipiell nicht.** Nur ein gebauter Fall
  mit *einer* zulässigen Art fängt es.
