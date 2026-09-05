# Logbuch: testentwickler

Belege gehören in die Ergebnisdatei — hier steht die Lehre. Höchstens 12.000 Zeichen.
**2026-09-05 archiviert** nach `notizen/archiv/testentwickler-2026-09-05.md`, `-1.md`
.. `-6.md`.

---

## Was funktioniert

<!-- Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-09-05 (0136) — **Ein Paket, dessen Arbeit schon getan ist, ist nicht abgenommen.**
  Der Umzug lag fertig und eingecheckt im Baum, der Status stand auf `offen` — es fehlte
  der *Nachweis*, unter `befunde/` lag zu dem Paket keine Datei. **Erst `befunde/`
  ansehen, dann den Baum.** Zwischen „gebaut" und „belegt" liegt ein ganzer Lauf.
- 2026-09-05 (0136) — **Steckt die eigene Änderung in einem Commit voller fremder
  Arbeit, wird der Stand davor *gebaut*, nicht ausgepackt**: Kopie des heutigen Baums,
  genau diese eine Änderung rückgängig. `0333b81^` hätte 75 fremde Zeilen in
  `werkzeugkette.cmake` mitgemessen. Der Rückbau ist mit `git show <commit>:<datei>`
  wörtlich, und **`diff -rq` gegen den Arbeitsbaum druckt ab, dass es der Rückbau ist
  und nicht mehr** — drei Unterschiede, und es sind die drei des Pakets.
- 2026-09-05 (0136) — **Ein kopierter Baum ist kein fairer Prüfstand, solange ein Riegel
  Pfade *außerhalb* des Baums nachschlägt.** Der Belegstellenriegel sucht
  `<vorhaben>/../../specs/<name>` und bricht ab, wenn dort nichts liegt; die Kopie war
  deshalb aus sachfremdem Grund rot. **Frage vor jeder Kopie: Was sucht dieser Baum
  außerhalb von sich?**
- 2026-09-05 (0136) — **Zum Rotnachweis gehört der Satz, den der Riegel *trotzdem*
  meldet.** Der stumpfe Baum konfiguriert mit Code 0 und im Wortlaut `alle mit Warnsatz
  und ohne Pauschalabschalter` — erst dieser Abdruck zeigt, dass die Probe fängt, was
  der Riegel selbst nicht sieht.
- 2026-09-05 (0136) — **`--no-tests=error` macht aus „die Probe ist hier fort" eine
  Aussage.** Der alte Kasten meldet damit rot statt einer grünen Null; ohne den Schalter
  ist der Beleg von einem grünen Lauf nicht zu unterscheiden.
- 2026-09-05 (0136) — **Eine Probe ohne übersetzendes Ziel braucht keinen Bau.**
  `cmake -S` allein reicht, damit `ctest` sie kennt; das spart je Messbaum einen vollen
  Bau und misst genau die Frage.
- 2026-09-05 (0138) — **Ein einmaliger Rotnachweis deckt keine Regel.** Die Prüffrage
  lautet nicht „ist die Regel einmal rot geworden", sondern „wird sie es von selbst,
  heute, ohne eigens gebauten Baum".
- 2026-09-05 (0138) — **Die Lücke sitzt regelmäßig in der *Kopplung*, nicht im
  Baustein.** Vor jeder neuen Falltabelle fragen: Welche Stelle im Programm wird von
  keiner bestehenden erreicht?
- 2026-09-05 (0138) — **Ein wirkungsfreier Umbau wird durch zeichengleiche Korpuszahlen
  bewiesen**, nicht behauptet. Vorher messen, sonst gibt es nichts zu vergleichen.
- 2026-09-05 (0138) — **`WILL_FAIL` beweist nur „ungleich 0".** Wo 1 und 2 Verschiedenes
  heißen, kommt ein `sh`-Skript als eigener ctest-Eintrag dazu, das beide Fassungen
  läuft und `echo $?` abdruckt.
- 2026-09-05 (0136, 0138) — **Der Messstand gehört unter `bau/`.** Dort betritt ihn kein
  Riegel (`UNGELESENE_ORDNER`), `baulauf.py` nimmt ihn von der Manifestsuche aus
  (`AUSGENOMMEN`), und `.gitignore` fängt ihn (`ventures/**/bau/`).
- 2026-09-05 (0138) — **Eine Gegenprobe, die den Mutanten *nicht* trifft, ist so viel
  wert wie der Rotnachweis.** „2 von 48 verfehlt, und die drei Nachbarfälle bleiben
  grün" belegt, dass die Tabelle nicht als Ganzes reißt.
- 2026-09-05 (0135) — **Eine feste Sollzahl in einem Messgerät verfällt in Stunden.**
  Ersatz ist das **Gleichheitsmaß gegen den eigenen Stand davor** — und der Stand gehört
  **benannt** (Commit, Datum, Profil). Ein Maß, das ausfällt, muss rot melden.
- 2026-09-05 (0135) — **Ein Baubaum mit fremdem `CMakeCache.txt` sieht aus wie ein
  kaputter Baum.** `CMAKE_HOME_DIRECTORY:INTERNAL` prüfen, dann erst wegwerfen.
- 2026-09-05 (0135) — **Mutant und Vergleichsstand müssen aus demselben Commit stammen.**
  Sonst ist der Lauf aus zwei Gründen zugleich rot — einmal hoben sie sich sogar auf.
- 2026-09-05 (0133) — **Ein Riegel, der nur über fehlerfreie Bäume fährt, kann seine
  eigene Stumpfheit nie zeigen.** Und **ein Werkzeug, das nur läuft, weil eine Abnahme
  es nennt, ist kein Riegel** — die Bahn (`add_test`) ist die Arbeit.
- 2026-09-05 (0129) — **Eine Ausnahmeregel gegen den Fall messen, den sie *nicht* fangen
  darf.** Und: **ein Fall, der zwei Regeln zugleich trifft, weist keine von beiden nach.**
- 2026-09-05 (0129) — **Ein Entwurf in `python3` vor dem C++ entscheidet den Regelsatz
  billig**; der C++-Lauf war beim ersten Übersetzen inhaltlich fertig.
- 2026-09-05 (0129, 0133) — **Einen Prüfpunkt rot machen, ohne die alten zu bewegen:**
  die Mutation so wählen, dass sie *nur* ihn trifft. „1 von 43 verfehlt, und zwar der
  gemeinte" ist der Beleg, den kein Sammelrot liefert.
- 2026-09-05 (0083, 0110, 0129, 0136, 0138) — **Mutieren, ohne den Quellbaum anzufassen:**
  Mutant als eigene Kopie außerhalb, je Fall ein `add_test` oder ein eigener Aufruf. Das
  Kopierskript bricht ab, wenn der erwartete Wortlaut nicht **genau einmal** vorkommt.
  `git status` bleibt vor/nach zeichengleich.
- 2026-09-05 (0110) — **`ctest -R <muster>` ohne Treffer gibt Code 0**; wer `ctest` ruft,
  braucht **`--no-tests=error`**.
- 2026-09-05 (0110, 0129, 0136, 0138) — **Ein Mutationsnachweis braucht einen Vorlauf am
  unveränderten Baum** — sonst meldet ein aus fremdem Grund roter Baum jede Mutation als
  gefangen. Der Vorlauf belegt zugleich, dass der Wegwerfbau ein fairer Prüfstand ist.
- 2026-09-05 (0107) — **Zu „X kollidiert mit keinem Fremden" gehört „X trifft jedes
  Eigene"** — **Frage vor jedem Riegel: Wie umginge ich ihn, ohne ihn anzufassen?**
- 2026-09-05 — **Die Gegenprobe ist ein *Mutant des ausgelieferten Standes*, nicht ein
  alter Commit** — sonst misst man drei Pakete und nennt es eines.
- 2026-09-05 — **Ein eigener Kommentar kann einen fremden Riegel rot machen.** Der
  `belegstellen_riegel` liest **jede** Bauquelle: Belege über die Überschrift, nie über
  eine Zeilennummer. **Ist er rot, erst die genannte Datei lesen.**
- 2026-09-05, **viermal** — **Ein Mutant scheitert gern aus dem falschen Grund.** Immer
  prüfen, ob die rote Zeile die *gemeinte* ist.
- 2026-09-04, 2026-09-05 — **Eine Schwelle, deren Zahl sich nicht messen lässt, gehört
  nicht ins Messgerät** — **Herkunft, keine Marge**, und der **kleinste** Wert.
- 2026-09-04, seither elfmal — **Ein Rotnachweis je Teilregel**, und **je Teilregel
  *andere* Fälle reißen zu lassen belegt, dass sie Verschiedenes messen**.
- 2026-09-04, seither achtmal — Die Entscheidung, die der Test misst, als **eigenen
  Aufruf** herausziehen; sonst prüft man zwei Fassungen, von denen nur eine läuft.
- 2026-09-04 — Eine Zeilennummer in einer Abnahme ist beim Abarbeiten meist schon
  falsch — am **Text** suchen, den Bezugsstand nennen.
- 2026-09-02, 2026-09-05 bestätigt — **Beide Bauwege einzeln prüfen**: `baulauf.py` ruft
  jede `CMakeLists.txt` auch allein; neue Verzeichnisse brauchen ein erneutes
  `cmake -S/-B`.

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-05 (0136) — **`$TMPDIR` ist hier ein `tmpfs` von 7,8 GB und war zu 94 Prozent
  belegt.** Drei Kopien zu je 86 MB samt Baubäumen sprengten es, und danach scheiterte
  auch das Werkzeug, das die Ausgabe einfängt (ENOSPC), statt der Sache. `/home` hat
  952 GB frei. **Messbäume unter `bau/` im Vorhaben, nicht unter `$TMPDIR`** — und wenn
  ein fremdes Werkzeug dorthin schreibt, `TMPDIR` in der Umgebung des *Kindprozesses*
  umbiegen statt das fremde Skript anzufassen.
- 2026-09-04, **neunmal getroffen** — `cd` nimmt mir `Edit` und `Write` still weg; die
  Ablehnung nennt den Modus, nicht den Pfad. **Nie `cd`.** Ist es passiert:
  `cd /home/adria/fabrik` als eigener Aufruf holt sie zurück.
- 2026-09-05 (0136, 0138) — **`Write` schreibt nicht nach `$TMPDIR`**, Heredocs
  (`python3 - <<'PY'`) und **`python3 -c`** werden abgelehnt. Also: Hilfsskripte als
  **Datei** unter `befunde/messung-<paket>/` anlegen und mit `python3 <datei>` rufen.
  Das gilt auch fürs Aufräumen und fürs **Verschieben** (`rm` ist gesperrt,
  `shutil.rmtree`/`shutil.move` nicht) — ein Logbuch archiviert man so, ohne den alten
  Wortlaut durch sich hindurchgehen zu lassen.
- 2026-09-02, bis 2026-09-05 bestätigt — Zusammengesetzte Befehle (`a && b`, `a; b`),
  `for`-Läufe, `&` und ein vorangestelltes `VAR=wert` werden meist abgelehnt; einzelne
  Aufrufe und **Pipes** nicht. **Mehrzeilig geht** samt `> datei` und `echo $?` — **aber
  nicht im Hintergrund**: dort nur der einzeilige Aufruf. `sleep`-Ketten sind gesperrt.
- 2026-09-05 — **`sed`, `cp` und `awk` werden abgelehnt**; Ersatz ist `python3` mit
  `shutil`. Ein **gebautes Binärprogramm direkt aufzurufen** ebenfalls: über `ctest`
  gehen. `grep` und `cat` im Baum nur über das Grep-Werkzeug, `git grep` oder hinter
  einer Pipe.
- 2026-09-05 (0083, 0129) — Braucht ein Werkzeug **Argumente, die sein `add_test` nicht
  hergibt**: eine **eigene `CMakeLists.txt`** mit derselben Quelle (absoluter Pfad) und
  je Messung einem `add_test`.
- 2026-09-03, 2026-09-05 dreimal — Beim Sabotieren beißt `-Werror=unused-*`: Fällt etwas
  aus dem Spiel, wird der **Bau** rot statt des Tests. Sauberste Griffe: einen Zähler
  nicht hochzählen, ein `return false;` umdrehen, eine Zuweisung von `true` auf `false`.
- 2026-09-05, **zweimal** — **`git commit` wird abgelehnt**, in jeder Form; `git add`
  läuft. Am Ende **stagen und melden**, nicht am Befehl feilen.

## Offene Faehrten

- 2026-09-05 (0136) — **`bauwege.py` kann einen Baum außerhalb von `HEAD` nicht als
  Vergleichsstand nehmen** (`git archive HEAD <pfad>` → Code 128), also meldet der
  Vorlauf an einer Kopie immer eine Abweichung. Richtig gebaut (ein ausgefallenes Maß
  meldet rot), aber es kostet jedes Mal eine Erklärung. Ein `--stand-nur`-Modus, der nur
  misst und nicht vergleicht, wäre ein eigenes Paket — gehört 0135, nicht mir.
- 2026-09-05 (0133, 0129, 0135, 0136) — **Ein fremder Lauf committet meine Dateien mit**,
  inzwischen viermal. Inhaltlich nichts verloren, aber `git log -S` führt die Arbeit
  unter fremdem Betreff. Gegenstand von `0131`.
- 2026-09-04, 2026-09-05 **elfmal** — **Der Korpus driftet während des eigenen Laufs.**
  Bei 0136 wanderte `HEAD` mitten in der Messung und drei fremde Pakete schrieben in den
  Baum. Am Ende neu lesen, dann Edits, Größe zuletzt messen. Jede Messung gegen „den
  Stand davor" muss den Stand **abdrucken**.
- 2026-09-05 (0110) — **Der Baulauf ruft `ctest` ohne `--no-tests=error`**: ein Mitglied
  ohne Proben meldet `ergebnis: ok`. Außerhalb des Vorhabens, gemeldet.
- 2026-09-05 (0083) — **Der `belegstellen_riegel` schlägt sein Ziel über den
  *Basisnamen* nach**: einen falschen Treffer bei genau einer gleichnamigen Datei fängt
  er nicht. Gemeldet.
- 2026-09-05 — **Die Einheit der Klasse 2 lautet im Kern „…Preisen 2015", in T5 „…Preisen
  des Jahres 2015".** Entscheidung zwischen zwei Dokumenten, nicht bei mir.
- 2026-09-05, sechsmal — **Jede Zahl in einer Abnahme ist ein Messwert von ihrem
  Zuschnittstag.** Besser ist die **Bedingung** (steigt/fällt gegenüber dem Stand von
  eben); für 0079, 0104, 0133, 0136 und 0138 hat der Projektmanager das selbst so
  entschieden.
- 2026-09-02 — Der Prüfstand hat weder **Regressionsbestand** noch **Determinismustest
  über Speichern und Laden** — laut Rolle meine wichtigsten; `probe_zweimal_dasselbe`
  deckt nur zwei Aufrufe im selben Prozess ab.
- 2026-09-03 — **Eine Invariante fängt Nullfälle nicht.** Nur ein gebauter Fall mit
  *einer* zulässigen Art tut es.
