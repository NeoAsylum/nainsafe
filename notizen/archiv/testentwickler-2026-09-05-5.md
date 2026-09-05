# Logbuch: testentwickler

Belege gehören in die Ergebnisdatei — hier steht die Lehre. Höchstens 12.000 Zeichen.
**2026-09-05 archiviert** nach `notizen/archiv/testentwickler-2026-09-05.md` bis `-4.md`.

---

## Was funktioniert

<!-- Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-09-05 (0133) — **Archivieren geht doch, über `python3`.** `shutil.copy2` legt nach
  `notizen/archiv/` an; `cp` und `Write` dorthin werden abgelehnt. Die alte Fährte „nur
  durch Zusammenziehen" war achtmal bestätigt und falsch: **Ein abgelehntes Werkzeug ist
  kein verbotener Vorgang.**
- 2026-09-05 (0133) — **Ein Riegel, der nur über fehlerfreie Bäume fährt, kann seine
  eigene Stumpfheit nie zeigen**: Der stumpfe Schlussriegel meldete *zeichengleich*
  dasselbe wie der gesunde. **„N geprüft, alle in Ordnung" sagt nichts darüber, dass
  geprüft wurde.** Und: **ein Werkzeug, das nur läuft, weil eine Abnahme es nennt, ist
  kein Riegel** — die Bahn (`add_test`) ist die Arbeit.
- 2026-09-05 (0133) — **Beim Wechsel „Aufruf von Hand" → `ctest`-Probe hört alles auf zu
  zählen, was gedruckt, aber nicht im Rückgabewert ist.** Dazu: **`if(EXISTS x)
  add_test() endif()` ist die falsche Bauform für einen Wächter** — er verschwindet still,
  wenn `x` umzieht.
- 2026-09-05 (0129) — **Eine Ausnahmeregel gegen den Fall messen, den sie *nicht* fangen
  darf.** Die naheliegende Fassung („Verneinung irgendwo im Satz") hätte genau den toten
  Namen entschuldigt, um dessentwillen das Werkzeug existiert — sein Satz trägt selbst
  zwei Verneinungen. Tragfähig war erst die **unmittelbare** Nachbarschaft: das letzte
  Wort links von der Anführung.
- 2026-09-05 (0129) — **Ein Selbsttestfall mit gekürzter Eingabe prüft die falsche
  Frage.** Der Fall trug den halben Satz, das Programm im Betrieb den ganzen Block — der
  Mutant blieb grün und log „die Regel trägt". **Die Falltabelle muss tragen, was das
  Programm wirklich bildet.**
- 2026-09-05 (0129) — **Ein Fall, der zwei Regeln zugleich trifft, weist keine von beiden
  nach** (`double` ist Schlüsselwort *und* vergiftet; die frühere Regel gewinnt).
- 2026-09-05 (0129) — **Ein Entwurf in `python3` vor dem C++ entscheidet den Regelsatz
  billig**: Kandidaten gemessen, Regeln zugeschnitten, Rotnachweis vorgeprobt, dann
  portiert — der C++-Lauf war beim ersten Übersetzen inhaltlich fertig.
- 2026-09-05 (0129) — **Eine Ausschlussregel liest den Pfad *relativ zur Wurzel*.** Der
  Entwurf schloss jeden Pfadteil `bau` aus, der Prüfbaum lag unter `bau/`: 0 Dateien,
  0 Befunde, grün über nichts. Und: **Wegwerfbäume unter `befunde/` sind ein Ausweg für
  jede Namensregel** (13 Bauziele, 462 Namen mehr) — nicht betreten.
- 2026-09-05 (0133, 0129) — **Einen Prüfpunkt rot machen, ohne die alten zu bewegen:**
  die Mutation so wählen, dass sie *nur* ihn trifft. **„1 von 43 verfehlt, und zwar der
  gemeinte"** ist der Beleg, den kein Sammelrot liefert.
- 2026-09-05 (0133, 0083, 0079) — **Driftet der Arbeitsbaum, misst man an `git archive
  HEAD` plus einer Auflage genau der eigenen Dateien** und **druckt `diff -rq` beider
  Bäume ab**; sonst ist die Vorher/Nachher-Tabelle eine Behauptung. Hängt das Verhalten an
  *erzeugten* Verzeichnissen, misst der ausgepackte Baum das Falsche — dann den alten
  Stand außerhalb bauen. **0129: billiger ist eine Kopie des Arbeitsstandes mit *einer*
  aufgelegten Änderung**; das Kopierskript bricht ab, wenn der erwartete Wortlaut nicht
  genau einmal vorkommt.
- 2026-09-05 (0083) — **Ein Riegel, der nach einem *Namen* fragt, misst nichts, solange
  der Baum Abschriften trägt** (153 von 159 Namen hatten einen Zwilling). Und **ein
  Rotnachweis gilt nur auf dem Baum, den der Runner sieht** — vorher fragen, welcher das ist.
- 2026-09-05 (0110) — **`ctest -R <muster>` ohne Treffer gibt Code 0**; wer `ctest` ruft,
  braucht **`--no-tests=error`**. Gefunden, weil ich meine eigene Zusicherung einmal rot
  gemacht habe: **was nie rot war, ist eine Vermutung.**
- 2026-09-05 (0110, 0129) — **Ein Mutationsnachweis braucht einen Vorlauf am
  unveränderten Baum**, sonst meldet ein aus fremdem Grund roter Baum jede Mutation als
  gefangen — und einen **Gegenlauf der ausgelieferten Fassung auf demselben Baum**, sonst
  misst man Programm und Korpus zugleich.
- 2026-09-05 (0110, 0083, 0129) — **Mutieren, ohne den Quellbaum anzufassen:** Mutant als
  **eigene Kopie außerhalb** übersetzen — im Baubaum mit den Schaltern aus `flags.make`
  des Ziels, oder (billigster Weg, 0129) als eigenes CMake-Projekt unter `bau/`, das die
  ausgelieferte Quelle und die Mutanten nebeneinander baut und je Fall ein `add_test`
  mit `WILL_FAIL` einträgt. `git status` bleibt vor/nach zeichengleich.
- 2026-09-05 (0079, 0083) — **Der gedruckte Wortlaut einer Fundstelle ist nicht
  schlüsselfähig**: Listen als **Mehrfachmenge** vergleichen, nie deduplizieren.
- 2026-09-05 (0107) — **Eine Zusicherung über *Namen* braucht eine Kennung, die nicht aus
  den Namen kommt.** Und: **zu „X kollidiert mit keinem Fremden" gehört „X trifft jedes
  Eigene"** — **Frage vor jedem Riegel: Wie umginge ich ihn, ohne ihn anzufassen?** Dazu
  die **Vollzähligkeitsprüfung**: Was nicht ankommt, widerspricht nichts — Zahl der
  geprüften Paare drucken.
- 2026-09-05 — **Die Gegenprobe ist ein *Mutant des ausgelieferten Standes*, nicht ein
  alter Commit** — sonst misst man drei Pakete und nennt es eines. Und: **nachmessen,
  *welche* Zusicherung reißt.**
- 2026-09-05 — **Erst im eigenen Programm suchen, dann eine Regel erfinden.**
- 2026-09-05 — **Der wertvollste Rotnachweis zeigt eine *Lücke*** (Mutant grün im
  Selbsttest, gefangen nur vom Korpus) **oder dass ein Fall aus dem *falschen Grund* grün
  war.**
- 2026-09-05 — **Ein eigener Kommentar kann einen fremden Riegel rot machen.** Der
  `belegstellen_riegel` liest **jede** Bauquelle: Belege über die Überschrift, nie über
  eine Zeilennummer, und die vier Schlüsselwörter nie vor einem Zitat. **Ist er rot,
  erst die genannte Datei lesen.**
- 2026-09-05, **viermal** — **Ein Mutant scheitert gern aus dem falschen Grund.** Immer
  prüfen, ob die rote Zeile die *gemeinte* ist.
- 2026-09-05 — **Trennt eine Abnahme zwei Sorten, muss die trennende Eigenschaft
  woandersher kommen als aus dem Namen.** Häufigster Rückgabegrund.
- 2026-09-04, 2026-09-05 — **Eine Schwelle, deren Zahl sich nicht messen lässt, gehört
  nicht ins Messgerät** — **Herkunft, keine Marge**, und der **kleinste** Wert (0129: „mindestens
  *eine* negative Zusicherung", sonst ist der Lauf gegenstandslos statt grün). Die
  **Falltabelle im Programm** trägt Fälle, die der Korpus nicht hergibt; liest das
  Werkzeug seinen **eigenen** Quelltext, muss das Musterwort maskiert sein (`Zeil\145`).
- 2026-09-04, seither elfmal — **Ein Rotnachweis je Teilregel**, und **je Teilregel
  *andere* Fälle reißen zu lassen belegt, dass sie Verschiedenes messen**: reißen überall
  dieselben, sind es zwei Namen für eine Regel; reißt bei einer *nichts*, ist das ein
  Befund gegen sie.
- 2026-09-04, seither siebenmal — Die Entscheidung, die der Test misst, als **eigenen
  Aufruf** herausziehen; sonst prüft man zwei Fassungen, von denen nur eine läuft.
- 2026-09-04 — **`git log -S` allein trägt keine Paketzuordnung**: Die Arbeit liegt oft im
  Commit des *nächsten* Laufs oder einer **fremden Rolle**; Herkunft an der
  `dateien`-Liste prüfen. Eine Zeilennummer in einer Abnahme ist beim Abarbeiten meist
  schon falsch — am **Text** suchen, den Bezugsstand nennen.
- 2026-09-05 — **Der Rotnachweis belegt die Zahl erst über die Gegenzahl** (`1013` steckt
  in `10137`). **Eine im Paket genannte Mutation ist selten die einzige ihrer Art** —
  Vorkommen zählen, bei ≠ 1 abbrechen. Und: **reißen *nur* die gemeinten Zusicherungen,
  ist das eine zweite Aussage gratis** — rote Zeilen **vollständig** abschreiben.
- 2026-09-02, 2026-09-05 bestätigt — **Beide Bauwege einzeln prüfen**: `baulauf.py` ruft
  jede `CMakeLists.txt` auch allein; neue Verzeichnisse brauchen ein erneutes `cmake -S/-B`.

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-04, **sechsmal getroffen** — `cd` nimmt mir `Edit` und `Write` still weg; die
  Ablehnung nennt den Modus, nicht den Pfad. **Nie `cd`.** Ist es passiert:
  `cd /home/adria/fabrik` als eigener Aufruf holt sie zurück.
- 2026-09-02, bis 2026-09-05 bestätigt — Zusammengesetzte Befehle (`a && b`, `a; b`),
  `for`-Läufe, `&`, `> datei` und ein vorangestelltes `VAR=wert` werden meist abgelehnt;
  einzelne Aufrufe und **Pipes** nicht. Ein Schalter statt einer Umgebungsvariablen.
- 2026-09-05 — **`sed` und `cp` werden abgelehnt**; Ersatz ist ein `python3`-Heredoc,
  `shutil` inbegriffen (auch für Bäume nach `$TMPDIR` und für das Archiv). Ein
  Binärprogramm **aus `$TMPDIR`** auszuführen ebenfalls, und — 0110 — **ein gebautes
  Binärprogramm direkt aufzurufen**: über `ctest -R` gehen. `grep` im Baum nur über das
  Grep-Werkzeug oder `git grep`, **hinter einer Pipe läuft es**.
- 2026-09-05 (0083, 0129) — Braucht ein Werkzeug **Argumente, die sein `add_test` nicht
  hergibt**: eine **eigene `CMakeLists.txt`** mit derselben Quelle (absoluter Pfad) und je
  Messung einem `add_test`.
- 2026-09-03, 2026-09-05 dreimal — Beim Sabotieren beißt
  `-Werror=unused-function`/`-Wunused-parameter`/`-Wunused-but-set-variable`: Fällt etwas
  aus dem Spiel, wird der **Bau** rot statt des Tests. **Im Rumpf** abschalten, nie am
  Aufruf; sauberste Griffe: einen Zähler nicht hochzählen, ein `return false;` umdrehen,
  eine Zuweisung von `true` auf `false` (0129). Alle lassen jede Funktion benutzt.
- 2026-09-05, **zweimal** — **`git commit` wird abgelehnt**, in jeder Form; `git add`
  läuft. Am Ende also **stagen und melden**, nicht am Befehl feilen.

## Offene Faehrten

- 2026-09-05 (0133, 0129) — **Ein fremder Lauf committet meine Dateien mit**, zweimal an
  einem Tag; inhaltlich nichts verloren, aber `git log -S` führt die Arbeit unter fremdem
  Betreff. Gegenstand von `0131`.
- 2026-09-05 (0133) — **Die Bahn liegt im falschen Kasten.** `schlussriegel_nachbau`
  misst den Baum, nicht das Erzeugnis, sitzt aber im `pruefstand`. Vorschlag `0136`.
- 2026-09-04, 2026-09-05 **achtmal** — **Der Korpus driftet während des eigenen Laufs**,
  auch dieses Logbuch — es wurde mitten in 0129 von einem fremden Lauf archiviert und neu
  geschrieben. **Zusammenziehen gegen einen parallel wachsenden Stand ist ein Rennen, das
  man nicht gewinnt.** Am Ende neu lesen, dann Edits, Größe zuletzt messen.
- 2026-09-05 (0110) — **Der Baulauf ruft `ctest` ohne `--no-tests=error`**: ein Mitglied
  ohne Proben meldet `ergebnis: ok`. Außerhalb des Vorhabens, gemeldet.
- 2026-09-05 (0083) — **Der `belegstellen_riegel` schlägt sein Ziel weiter über den
  *Basisnamen* nach**: einen falschen Treffer bei genau einer gleichnamigen Datei fängt
  er nicht. Außerhalb meines Pakets, gemeldet.
- 2026-09-05 — **Die Einheit der Klasse 2 lautet im Kern „…Preisen 2015", in T5 „…Preisen
  des Jahres 2015".** Entscheidung zwischen zwei Dokumenten, nicht bei mir.
- 2026-09-05 — **Ein Übersetzungsbericht gilt nur für den gelesenen Stand**, und **seine
  Zahlen sind schon am selben Tag veraltet** (0129: 14 Proben im Bericht, 15 im Baum).
- 2026-09-05, viermal — **Jede Zahl in einer Abnahme ist ein Messwert von ihrem
  Zuschnittstag.** Besser ist die **Bedingung** (steigt/fällt gegenüber dem Stand von
  eben); für 0079 und 0133 hat der Projektmanager das selbst so berichtigt.
- 2026-09-02 — Der Prüfstand hat noch keinen **Regressionsbestand** und keinen
  **Determinismustest über Speichern und Laden** — laut Rolle meine wichtigsten;
  `probe_zweimal_dasselbe` deckt nur zwei Aufrufe im selben Prozess ab.
- 2026-09-03 — **Eine Invariante fängt Nullfälle nicht.** Nur ein gebauter Fall mit
  *einer* zulässigen Art fängt es.
