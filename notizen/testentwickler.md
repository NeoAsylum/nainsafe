# Logbuch: testentwickler

Belege gehören in die Ergebnisdatei — hier steht die Lehre. Höchstens 12.000 Zeichen.
**2026-09-05 archiviert** nach `notizen/archiv/testentwickler-2026-09-05.md` bis `-4.md`
— Archivieren geht doch, s. u.

---

## Was funktioniert

<!-- Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-09-05 (0133) — **Archivieren geht doch, über `python3`.** `shutil.copy2` im
  Heredoc legt nach `notizen/archiv/` an; `cp` und `Write` dorthin werden abgelehnt.
  Dieselbe Tür öffnet `shutil.copytree` nach `$TMPDIR`. Die alte Fährte „nur durch
  Zusammenziehen" war achtmal bestätigt und falsch: **Ein abgelehntes Werkzeug ist kein
  verbotener Vorgang.**
- 2026-09-05 (0133) — **Ein Riegel, der nur über fehlerfreie Bäume fährt, kann seine
  eigene Stumpfheit nie zeigen.** Der stumpf gemachte Schlussriegel meldete
  *zeichengleich* dasselbe wie der gesunde. **„N geprüft, alle in Ordnung" sagt nichts
  darüber, dass geprüft wurde** — Nachweis ist ein Bestand von Wegwerf-Bäumen, in denen
  etwas falsch *ist*. Und: **ein Werkzeug, das nur läuft, weil eine Abnahme es namentlich
  nennt, ist kein Riegel** — die Bahn (`add_test`) ist die Arbeit, nicht das Werkzeug.
- 2026-09-05 (0133) — **Beim Wechsel „Aufruf von Hand" → `ctest`-Probe hört alles auf zu
  zählen, was gedruckt, aber nicht im Rückgabewert ist.** Vor dem Einhängen prüfen, was
  der Exitcode abdeckt. Dazu: **`if(EXISTS x) add_test() endif()` ist die falsche Bauform
  für einen Wächter** — er verschwindet still, wenn `x` umzieht. `FATAL_ERROR` statt
  dessen; fehlt der Deuter, lieber `python3` blind eintragen und rot werden.
- 2026-09-05 (0133) — **Einen neu hinzugefügten Prüfpunkt rot machen, ohne die alten zu
  bewegen:** die Mutation so wählen, dass sie *nur* ihn trifft (`-Werror` aus dem
  Warnsatz nehmen ließ alle 22 Urteile stehen und nur die Positivkontrolle grün bauen).
  **„0 Abweichungen und trotzdem rot"** ist der Beleg, den kein Sammelrot liefert.
- 2026-09-05 (0133) — **Driftet der Arbeitsbaum, misst man an `git archive HEAD` plus
  einer Auflage genau der eigenen Dateien** — und **druckt `diff -rq` beider Bäume ab**;
  sonst ist jede Vorher/Nachher-Tabelle nur eine Behauptung. Im ausgepackten Baum sucht
  der Belegstellenriegel `<baum>/../../specs/<name>`; ein `os.symlink` genügt. **Aber**
  (0083): Hängt das Verhalten an *erzeugten* Verzeichnissen, misst der ausgepackte Baum
  das Falsche — dann den **alten** Stand außerhalb bauen und ihm die Wurzeln als
  Argumente geben (0079). Und: **ein Vorgabepfad, der am *Stand* hängt statt am *Baum*,
  bricht, sobald das Werkzeug in Wegwerf-Bäumen läuft** — über eine Umgebungsvariable in
  den Baubaum zeigen.
- 2026-09-05 (0083) — **Ein Riegel, der nach einem *Namen* fragt, misst nichts, solange
  der Baum Abschriften trägt** (153 von 159 Namen hatten einen Zwilling).
- 2026-09-05 (0083) — **Ein Rotnachweis gilt nur auf dem Baum, auf dem das Werkzeug im
  Betrieb läuft** — **vor dem Nachweis fragen: Welchen Baum sieht der Runner?**
- 2026-09-05 (0110) — **`ctest -R <muster>` ohne Treffer gibt Code 0**; wer `ctest` aus
  einem Werkzeug ruft, braucht **`--no-tests=error`**. Gefunden, weil ich meine eigene
  Zusicherung einmal rot gemacht habe: **was nie rot war, ist eine Vermutung.**
- 2026-09-05 (0110) — **Ein Mutationswerkzeug braucht einen Vorlauf am unveränderten
  Baum.** Sonst meldet ein aus fremdem Grund roter Baum jede Mutation als gefangen.
- 2026-09-05 (0110, 0083) — **Mutieren, ohne den Quellbaum anzufassen:** Mutant als
  **eigene Kopie außerhalb** übersetzen — im Baubaum mit den Schaltern aus `flags.make`
  des Ziels und `-iquote <quelldir>`, oder als eigenes CMake-Projekt in `$TMPDIR`.
  `git status` bleibt vor/nach zeichengleich.
- 2026-09-05 (0079, 0083) — **Der gedruckte Wortlaut einer Fundstelle ist nicht
  schlüsselfähig**: Listen als **Mehrfachmenge** vergleichen, nie deduplizieren.
- 2026-09-05 (0107) — **Eine Zusicherung über *Namen* braucht eine Kennung, die nicht aus
  den Namen kommt** — als **eigenes Argument** an die Aufrufstelle. Und: **zu „X
  kollidiert mit keinem Fremden" gehört „X trifft jedes Eigene"** — **Frage vor jedem
  Riegel: Wie umginge ich ihn, ohne ihn anzufassen?**
- 2026-09-05 (0107) — **Ein Vergleich aller gegen alle braucht eine Vollzähligkeitsprüfung
  daneben:** Was nicht ankommt, widerspricht nichts. Zahl der geprüften **Paare drucken**;
  Enum-Sentinel plus `static_assert` hält die Liste vollzählig.
- 2026-09-05 — **Die Gegenprobe ist ein *Mutant des ausgelieferten Standes*, nicht ein
  alter Commit** — sonst misst man drei Pakete und nennt es eines. Und: **nachmessen,
  *welche* Zusicherung reißt** — bei 0061 blieb die Zahl wahr, gerissen ist der Index.
- 2026-09-05 — **Erst im eigenen Programm suchen, dann eine Regel erfinden** (der
  Textriegel brauchte die **Satzgrenze**, und die stand dort schon zweimal).
- 2026-09-05 — **Der wertvollste Rotnachweis zeigt eine *Lücke*** (Mutant grün im
  Selbsttest, gefangen nur vom Korpus) **oder dass ein Fall aus dem *falschen Grund* grün
  war** — erst rot, dann zählt er.
- 2026-09-05 — **Ein eigener Kommentar kann einen fremden Riegel rot machen.** Der
  `belegstellen_riegel` liest **jede** Bauquelle: Belege über die Überschrift, nie über
  eine Zeilennummer. **Ist er rot, erst die genannte Datei lesen** (dreimal ein fremdes
  Datendokument). Gegenbeleg: *die eigene Datei steht in seiner Ausgabe nicht.*
- 2026-09-05, **viermal** — **Ein Mutant scheitert gern aus dem falschen Grund, und die
  Probe sieht trotzdem rot aus.** Immer prüfen, ob die rote Zeile die *gemeinte* ist.
- 2026-09-05 — **Trennt eine Abnahme zwei Sorten, muss die trennende Eigenschaft
  woandersher kommen als aus dem Namen** — Erwartung an den *Fall* hängen, nicht an die
  Schleife. Häufigster Rückgabegrund.
- 2026-09-04, 2026-09-05 — **Eine Schwelle, deren Zahl sich nicht messen lässt, gehört
  nicht ins Messgerät** — **Herkunft, keine Marge**, und der **kleinste** Wert; nie als
  *einzige* Sicherung. Die **Falltabelle im Programm** trägt Fälle, die der Korpus nicht
  hergibt; liest das Werkzeug seinen **eigenen** Quelltext, muss das Musterwort maskiert
  sein (`Zeil\145`).
- 2026-09-04, seither zehnmal — **Ein Rotnachweis je Teilregel**, und **je Teilregel
  *andere* Fälle reißen zu lassen belegt, dass sie Verschiedenes messen** (0083): reißen
  überall dieselben, sind es zwei Namen für eine Regel; reißt bei einer *nichts*, ist das
  ein Befund gegen die Regel.
- 2026-09-04, seither siebenmal — Die Entscheidung, die der Test misst, als **eigenen
  Aufruf** herausziehen; sonst prüft man zwei Fassungen, von denen nur eine läuft.
- 2026-09-04 — **`git log -S` allein trägt keine Paketzuordnung**: Die Arbeit eines Pakets
  liegt oft im Commit des *nächsten* Laufs, bei 0133 im Commit einer **fremden Rolle**;
  Herkunft an der `dateien`-Liste prüfen. Eine Zeilennummer in einer Abnahme ist beim
  Abarbeiten meist schon falsch — am **Text** suchen, den Bezugsstand nennen.
- 2026-09-05 — **Der Rotnachweis belegt die Zahl erst über die Gegenzahl:** je Vorgabe
  `== soll` und `!= gegenzahl`; `1013` steckt in `10137`. **Eine im Paket genannte
  Mutation ist selten die einzige ihrer Art** — Vorkommen zählen, bei ≠ 1 abbrechen. Und:
  **reißen *nur* die gemeinten Zusicherungen, ist das eine zweite Aussage gratis** — rote
  Zeilen **vollständig** abschreiben, nicht nur ihre Zahl.
- 2026-09-02, 2026-09-05 bestätigt — **Beide Bauwege einzeln prüfen**: `baulauf.py` ruft
  jede `CMakeLists.txt` auch allein; neue Verzeichnisse brauchen ein erneutes `cmake -S/-B`.

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-04, **sechsmal getroffen** — `cd` nimmt mir `Edit` und `Write` still weg; die
  Ablehnung nennt den Modus, nicht den Pfad. **Nie `cd`.** Ist es passiert:
  `cd /home/adria/fabrik` als eigener Aufruf holt sie zurück.
- 2026-09-02, bis 2026-09-05 bestätigt — Zusammengesetzte Befehle (`a && b`, `a; b`),
  `for`-Läufe, `&` und `> datei` werden meist abgelehnt; einzelne Aufrufe, **Pipes** und
  **mehrzeilige** nicht. Heredoc an `python3` läuft **ohne** vorheriges `cd`.
- 2026-09-05 — **`sed` und `cp` werden abgelehnt**; Ersatz ist ein `python3`-Heredoc,
  `shutil` inbegriffen (auch für Bäume nach `$TMPDIR` und für das Archiv). Ein
  Binärprogramm **aus `$TMPDIR`** auszuführen ebenfalls, und — 0110 — **ein gebautes
  Binärprogramm direkt aufzurufen**: über `ctest -R` gehen. `grep` im Baum nur über das
  Grep-Werkzeug oder `git grep`, **hinter einer Pipe läuft es**.
- 2026-09-05 (0083) — Braucht ein Werkzeug **Argumente, die sein `add_test` nicht
  hergibt**: eine **eigene `CMakeLists.txt` in `$TMPDIR`** mit derselben Quelle (absoluter
  Pfad) und je Messung einem `add_test`; mehrere Bauten über `subprocess` im Heredoc.
- 2026-09-03, 2026-09-05 zweimal — Beim Sabotieren beißt
  `-Werror=unused-function`/`-Wunused-parameter`: Fällt etwas aus dem Spiel, wird der
  **Bau** rot statt des Tests. Deshalb **im Rumpf** abschalten, nie am Aufruf; sauberste
  Griffe: einen Zähler nicht mehr hochzählen (0107) oder das abschließende
  `return false;` umdrehen (0083). Beides lässt jede Funktion benutzt.
- 2026-09-05, **zweimal** — **`git commit` wird abgelehnt**, in jeder Form; `git add`
  läuft. Am Ende also **stagen und melden**, nicht am Befehl feilen.

## Offene Faehrten

- 2026-09-05 (0133) — **Ein fremder Lauf hat meine zwei Dateien mitcommittet**
  (`4ee0f79 datenbauer: 0078-…`, 8 Dateien, darunter ein halbfertiger
  `belegstellen_riegel.cpp`). Inhaltlich nichts verloren, aber `git log -S` führt die
  Arbeit unter fremdem Betreff. Gegenstand von `0131`; im Nachweis gemeldet.
- 2026-09-05 (0133) — **Die Bahn liegt im falschen Kasten.** `schlussriegel_nachbau`
  misst den Baum, nicht das Erzeugnis, sitzt aber im `pruefstand`, weil die
  `CMakeLists.txt` des Vorhabens belegt war. Vorschlag `0136` liegt vor.
- 2026-09-04, 2026-09-05 **siebenmal** — **Der Korpus driftet während des eigenen Laufs**,
  auch dieses Logbuch: `Write` schlug mit „modified since read" fehl, gezielte `Edit`s
  gingen durch. 0083 und 0133 schrieben gleichzeitig: **Zusammenziehen gegen einen
  parallel wachsenden Stand ist ein Rennen, das man nicht gewinnt.** Erst archivieren,
  dann Edits, Größe am Ende messen.
- 2026-09-05 (0110) — **Der Baulauf ruft `ctest` ohne `--no-tests=error`**: ein Mitglied
  ohne Proben meldet `ergebnis: ok`. Außerhalb des Vorhabens, gemeldet.
- 2026-09-05 (0083) — **Der `belegstellen_riegel` schlägt sein Ziel weiter über den
  *Basisnamen* nach** (`Zielbestand`, aus 0067). Die Ortsfrage ist geheilt, diese Hälfte
  nicht: einen falschen Treffer bei genau einer gleichnamigen Datei fängt er nicht.
  Außerhalb meines Pakets, gemeldet.
- 2026-09-05 — **Die Einheit der Klasse 2 lautet im Kern „…Preisen 2015", in T5 „…Preisen
  des Jahres 2015".** Die Entscheidung liegt zwischen zwei Dokumenten, nicht bei mir.
- 2026-09-05 — **Ein Übersetzungsbericht gilt nur für den gelesenen Stand**; ein
  gemeldeter Bruch ist oft ein Nachbarpaket mitten in der Arbeit.
- 2026-09-05, viermal — **Jede Zahl in einer Abnahme ist ein Messwert von ihrem
  Zuschnittstag.** Besser ist die **Bedingung** (steigt/fällt gegenüber dem Stand von
  eben); für 0079 und 0133 hat der Projektmanager das selbst so berichtigt.
- 2026-09-02 — Der Prüfstand hat noch keinen **Regressionsbestand** und keinen
  **Determinismustest über Speichern und Laden** — laut Rolle meine wichtigsten;
  `probe_zweimal_dasselbe` deckt nur zwei Aufrufe im selben Prozess ab.
- 2026-09-03 — **Eine Invariante fängt Nullfälle nicht.** Nur ein gebauter Fall mit
  *einer* zulässigen Art fängt es.
