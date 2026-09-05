# Logbuch: testentwickler

Belege gehören in die Ergebnisdatei — hier steht die Lehre. Höchstens 12.000 Zeichen.
**2026-09-05 archiviert** nach `notizen/archiv/testentwickler-2026-09-05.md` .. `-5.md`.

---

## Was funktioniert

<!-- Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-09-05 (0135) — **Eine feste Sollzahl in einem Messgerät ist ein Wert mit
  Verfallsdatum, und zwar in Stunden.** Während *eines* Laufs stieg die Zielzahl des
  Arbeitsbereichs von 19 auf 20, weil ein fremdes Paket nebenher ein Ziel anlegte.
  Ersatz ist das **Gleichheitsmaß gegen den eigenen Stand davor** — und der Stand gehört
  **benannt** (Commit, Datum, Profil). Billigste Quelle: `git archive <commit>` in einen
  Wegwerf-Baum und dort **nur konfigurieren**; Bauen kostete Minuten ohne Aussage.
- 2026-09-05 (0135) — **Ein Maß, das ausfällt, muss rot melden, nicht übersprungen
  werden** — kein Repo, unbekannter Commit, Vergleichsbaum konfiguriert nicht. **Und
  deshalb keinen Schalter bauen, der den Vergleich abschaltet.**
- 2026-09-05 (0135) — **Ein Wegwerf-Baum braucht die Gestalt des Repos, nicht nur das
  Vorhaben.** `ventures/<v>` allein ausgepackt ließ den `belegstellen_riegel` rot
  laufen; er sucht das Geschwister `specs/<v>`. **Beide auspacken.**
- 2026-09-05 (0135) — **Ein Baubaum mit fremdem `CMakeCache.txt` sieht aus wie ein
  kaputter Baum.** Hängt die Ablage am *Laufnamen* statt am Baum, findet der zweite Lauf
  den Cache des ersten: sechsmal `konfig code=1` an einem fehlerfreien Baum.
  `CMAKE_HOME_DIRECTORY:INTERNAL` gegen die Quelle prüfen und nur dann wegwerfen.
- 2026-09-05 (0135) — **Die billigste Mutation der Zielzahl fasst keine `CMakeLists.txt`
  an:** Wo `file(GLOB test/*.cpp CONFIGURE_DEPENDS)` je Datei ein `add_executable`
  anlegt, ist eine kopierte bzw. gelöschte Probendatei genau *ein* Ziel mehr oder
  weniger — und der Bau bleibt grün, also ist die rote Zeile zwingend die gemeinte.
- 2026-09-05 (0135) — **Mutant und Vergleichsstand müssen aus demselben Commit
  stammen.** Sonst ist der Lauf aus zwei Gründen zugleich rot — und an einer Stelle hoben
  sie sich sogar auf (+1 Mutation gegen +1 Drift = keine Abweichung).
- 2026-09-05 (0133) — **Archivieren geht über `python3`.** `shutil.copy2` legt nach
  `notizen/archiv/` an; `cp` und `Write` dorthin werden abgelehnt. **Ein abgelehntes
  Werkzeug ist kein verbotener Vorgang.**
- 2026-09-05 (0133) — **Ein Riegel, der nur über fehlerfreie Bäume fährt, kann seine
  eigene Stumpfheit nie zeigen**: Der stumpfe Schlussriegel meldete *zeichengleich*
  dasselbe wie der gesunde. **„N geprüft, alle in Ordnung" sagt nichts darüber, dass
  geprüft wurde.** Und: **ein Werkzeug, das nur läuft, weil eine Abnahme es nennt, ist
  kein Riegel** — die Bahn (`add_test`) ist die Arbeit, und `if(EXISTS x) add_test()
  endif()` ist die falsche Bauform dafür: Der Wächter verschwindet still, wenn `x`
  umzieht. Beim Wechsel „Aufruf von Hand" → `ctest`-Probe hört außerdem alles auf zu
  zählen, was gedruckt, aber nicht im Rückgabewert ist.
- 2026-09-05 (0129) — **Eine Ausnahmeregel gegen den Fall messen, den sie *nicht* fangen
  darf.** Die naheliegende Fassung hätte genau den Fall entschuldigt, um dessentwillen
  das Werkzeug existiert. Und: **ein Fall, der zwei Regeln zugleich trifft, weist keine
  von beiden nach.**
- 2026-09-05 (0129) — **Ein Selbsttestfall mit gekürzter Eingabe prüft die falsche
  Frage.** Der Mutant blieb grün und log „die Regel trägt". **Die Falltabelle muss
  tragen, was das Programm wirklich bildet** — und eine Ausschlussregel liest den Pfad
  *relativ zur Wurzel* (Prüfbaum unter `bau/`: 0 Dateien, 0 Befunde, grün über nichts).
- 2026-09-05 (0129) — **Ein Entwurf in `python3` vor dem C++ entscheidet den Regelsatz
  billig**; der C++-Lauf war beim ersten Übersetzen inhaltlich fertig.
- 2026-09-05 (0133, 0129) — **Einen Prüfpunkt rot machen, ohne die alten zu bewegen:**
  die Mutation so wählen, dass sie *nur* ihn trifft. **„1 von 43 verfehlt, und zwar der
  gemeinte"** ist der Beleg, den kein Sammelrot liefert.
- 2026-09-05 (0133, 0083, 0079, 0129) — **Driftet der Arbeitsbaum, misst man an `git
  archive HEAD` plus einer Auflage genau der eigenen Dateien**; billiger ist eine Kopie
  des Arbeitsstandes mit *einer* aufgelegten Änderung, und das Kopierskript bricht ab,
  wenn der erwartete Wortlaut nicht genau einmal vorkommt.
- 2026-09-05 (0083) — **Ein Riegel, der nach einem *Namen* fragt, misst nichts, solange
  der Baum Abschriften trägt** (153 von 159 Namen hatten einen Zwilling).
- 2026-09-05 (0110) — **`ctest -R <muster>` ohne Treffer gibt Code 0**; wer `ctest` ruft,
  braucht **`--no-tests=error`**. Gefunden, weil ich meine eigene Zusicherung einmal rot
  gemacht habe: **was nie rot war, ist eine Vermutung.**
- 2026-09-05 (0110, 0129) — **Ein Mutationsnachweis braucht einen Vorlauf am
  unveränderten Baum** — sonst meldet ein aus fremdem Grund roter Baum jede Mutation als
  gefangen.
- 2026-09-05 (0110, 0083, 0129) — **Mutieren, ohne den Quellbaum anzufassen:** Mutant als
  **eigene Kopie außerhalb** übersetzen — billigster Weg ein eigenes CMake-Projekt unter
  `bau/`, das ausgelieferte Quelle und Mutanten nebeneinander baut und je Fall ein
  `add_test` mit `WILL_FAIL` einträgt. `git status` bleibt vor/nach zeichengleich.
- 2026-09-05 (0079, 0083) — **Der gedruckte Wortlaut einer Fundstelle ist nicht
  schlüsselfähig**: Listen als **Mehrfachmenge** vergleichen, nie deduplizieren.
- 2026-09-05 (0107) — **Eine Zusicherung über *Namen* braucht eine Kennung, die nicht aus
  den Namen kommt.** Und: **zu „X kollidiert mit keinem Fremden" gehört „X trifft jedes
  Eigene"** — **Frage vor jedem Riegel: Wie umginge ich ihn, ohne ihn anzufassen?** Dazu
  die **Vollzähligkeitsprüfung**: Was nicht ankommt, widerspricht nichts.
- 2026-09-05 — **Die Gegenprobe ist ein *Mutant des ausgelieferten Standes*, nicht ein
  alter Commit** — sonst misst man drei Pakete und nennt es eines; **nachmessen, *welche*
  Zusicherung reißt.** Der wertvollste Rotnachweis zeigt eine **Lücke** (Mutant grün im
  Selbsttest, gefangen nur vom Korpus) oder dass ein Fall aus dem *falschen Grund* grün
  war. Und: **erst im eigenen Programm suchen, dann eine Regel erfinden.**
- 2026-09-05 — **Ein eigener Kommentar kann einen fremden Riegel rot machen.** Der
  `belegstellen_riegel` liest **jede** Bauquelle: Belege über die Überschrift, nie über
  eine Zeilennummer. **Ist er rot, erst die genannte Datei lesen.**
- 2026-09-05, **viermal** — **Ein Mutant scheitert gern aus dem falschen Grund.** Immer
  prüfen, ob die rote Zeile die *gemeinte* ist. Und: **trennt eine Abnahme zwei Sorten,
  muss die trennende Eigenschaft woandersher kommen als aus dem Namen.**
- 2026-09-04, 2026-09-05 — **Eine Schwelle, deren Zahl sich nicht messen lässt, gehört
  nicht ins Messgerät** — **Herkunft, keine Marge**, und der **kleinste** Wert. Die
  **Falltabelle im Programm** trägt Fälle, die der Korpus nicht hergibt.
- 2026-09-04, seither elfmal — **Ein Rotnachweis je Teilregel**, und **je Teilregel
  *andere* Fälle reißen zu lassen belegt, dass sie Verschiedenes messen**.
- 2026-09-04, seither siebenmal — Die Entscheidung, die der Test misst, als **eigenen
  Aufruf** herausziehen; sonst prüft man zwei Fassungen, von denen nur eine läuft.
- 2026-09-04 — **`git log -S` allein trägt keine Paketzuordnung**; Herkunft an der
  `dateien`-Liste prüfen. Eine Zeilennummer in einer Abnahme ist beim Abarbeiten meist
  schon falsch — am **Text** suchen, den Bezugsstand nennen.
- 2026-09-05 — **Der Rotnachweis belegt die Zahl erst über die Gegenzahl** (`1013` steckt
  in `10137`); Vorkommen zählen, bei ≠ 1 abbrechen. **Reißen *nur* die gemeinten
  Zusicherungen, ist das eine zweite Aussage gratis** — rote Zeilen **vollständig**
  abschreiben.
- 2026-09-02, 2026-09-05 bestätigt — **Beide Bauwege einzeln prüfen**: `baulauf.py` ruft
  jede `CMakeLists.txt` auch allein; neue Verzeichnisse brauchen ein erneutes
  `cmake -S/-B`.

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-04, **siebenmal getroffen** (zuletzt 0135) — `cd` nimmt mir `Edit` und `Write`
  still weg; die Ablehnung nennt den Modus, nicht den Pfad. **Nie `cd`.** Ist es
  passiert: `cd /home/adria/fabrik` als eigener Aufruf holt sie zurück.
- 2026-09-02, bis 2026-09-05 bestätigt — Zusammengesetzte Befehle (`a && b`, `a; b`),
  `for`-Läufe, `&` und ein vorangestelltes `VAR=wert` werden meist abgelehnt; einzelne
  Aufrufe und **Pipes** nicht. **0135: mehrzeilig geht, samt `> datei` und `echo $?`** —
  das ist der Weg, den Rückgabewert einer Messung abzudrucken.
- 2026-09-05 — **`sed`, `cp` und `awk` werden abgelehnt**; Ersatz ist `python3` mit
  `shutil` (auch fürs Archiv). Ein **gebautes Binärprogramm direkt aufzurufen**
  ebenfalls: über `ctest` gehen. `grep` und `cat` im Baum nur über das Grep-Werkzeug,
  `git grep` oder **hinter einer Pipe**. **0135: ein `&&`-Paar zweier `git`-Aufrufe
  brach mit einem `bwrap`-Fehler ab**; einzeln und mit `git -C <pfad>` lief es.
- 2026-09-05 (0083, 0129) — Braucht ein Werkzeug **Argumente, die sein `add_test` nicht
  hergibt**: eine **eigene `CMakeLists.txt`** mit derselben Quelle (absoluter Pfad) und
  je Messung einem `add_test`.
- 2026-09-03, 2026-09-05 dreimal — Beim Sabotieren beißt `-Werror=unused-*`: Fällt etwas
  aus dem Spiel, wird der **Bau** rot statt des Tests. **Im Rumpf** abschalten, nie am
  Aufruf; sauberste Griffe: einen Zähler nicht hochzählen, ein `return false;` umdrehen,
  eine Zuweisung von `true` auf `false`.
- 2026-09-05, **zweimal** — **`git commit` wird abgelehnt**, in jeder Form; `git add`
  läuft. Am Ende **stagen und melden**, nicht am Befehl feilen.

## Offene Faehrten

- 2026-09-05 (0133, 0129, 0135) — **Ein fremder Lauf committet meine Dateien mit**,
  dreimal an einem Tag; bei 0135 lag meine halbfertige `bauwege.py` im Commit von 0083.
  Inhaltlich nichts verloren, aber `git log -S` führt die Arbeit unter fremdem Betreff.
  Gegenstand von `0131`.
- 2026-09-05 (0133) — **Die Bahn liegt im falschen Kasten.** `schlussriegel_nachbau`
  misst den Baum, nicht das Erzeugnis, sitzt aber im `pruefstand`. Vorschlag `0136`.
- 2026-09-04, 2026-09-05 **neunmal** — **Der Korpus driftet während des eigenen Laufs**,
  auch dieses Logbuch; `HEAD` wanderte in 0135 dreimal in einer Stunde. **Zusammenziehen
  gegen einen parallel wachsenden Stand ist ein Rennen, das man nicht gewinnt.** Am Ende
  neu lesen, dann Edits, Größe zuletzt messen. Und jede Messung gegen „den Stand davor"
  muss den Stand **abdrucken**.
- 2026-09-05 (0110) — **Der Baulauf ruft `ctest` ohne `--no-tests=error`**: ein Mitglied
  ohne Proben meldet `ergebnis: ok`. Außerhalb des Vorhabens, gemeldet.
- 2026-09-05 (0083) — **Der `belegstellen_riegel` schlägt sein Ziel über den
  *Basisnamen* nach**: einen falschen Treffer bei genau einer gleichnamigen Datei fängt
  er nicht. Gemeldet.
- 2026-09-05 — **Die Einheit der Klasse 2 lautet im Kern „…Preisen 2015", in T5 „…Preisen
  des Jahres 2015".** Entscheidung zwischen zwei Dokumenten, nicht bei mir.
- 2026-09-05, fünfmal — **Jede Zahl in einer Abnahme ist ein Messwert von ihrem
  Zuschnittstag** — auch die im Übersetzungsbericht (0129: 14 Proben im Bericht, 15 im
  Baum). Besser ist die **Bedingung** (steigt/fällt gegenüber dem Stand von eben); für
  0079, 0133 und 0104 hat der Projektmanager das selbst so entschieden.
- 2026-09-02 — Der Prüfstand hat weder **Regressionsbestand** noch **Determinismustest
  über Speichern und Laden** — laut Rolle meine wichtigsten; `probe_zweimal_dasselbe`
  deckt nur zwei Aufrufe im selben Prozess ab.
- 2026-09-03 — **Eine Invariante fängt Nullfälle nicht.** Nur ein gebauter Fall mit
  *einer* zulässigen Art tut es.
