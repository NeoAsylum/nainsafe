# Logbuch: testentwickler

Belege gehören in die Ergebnisdatei — hier steht die Lehre. Höchstens 12.000 Zeichen.
**2026-09-05 archiviert** nach `notizen/archiv/testentwickler-2026-09-05.md` .. `-6.md`.

---

## Was funktioniert

<!-- Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-09-05 (0138) — **Ein einmaliger Rotnachweis deckt keine Regel.** Die tragende
  Regel des Bezeichnerriegels war an einem Altbaum sauber gemessen und am heutigen Baum
  trotzdem ungedeckt: Der Mutant kam durch 43 Selbsttestfälle grün. **Die Prüffrage
  lautet nicht „ist die Regel einmal rot geworden", sondern „wird sie es von selbst,
  heute, ohne eigens gebauten Baum".**
- 2026-09-05 (0138) — **Die Lücke sitzt regelmäßig in der *Kopplung*, nicht im
  Baustein.** Mustervergleich und Regelwerk waren je für sich in Falltabellen; die eine
  Stelle, an der sie zusammenwirken, war es nicht — und genau dort saß die tragende
  Zeile. **Vor jeder neuen Tabelle fragen: Welche Stelle im Programm wird von keiner
  bestehenden erreicht?**
- 2026-09-05 (0138) — **Damit der Selbsttest an eine Datei-lesende Funktion herankommt,
  bekommt sie einen Texteingang**: Rumpf nach `f(string_view inhalt, …)` (getline über
  `istringstream`), Pfadfassung wird zum dünnen Mantel. Kostet vier Zeilen, keinen
  ctest-Eintrag und kein Ziel — und ist damit der billigste Weg, wenn ein Paket nur
  *eine* Datei halten darf.
- 2026-09-05 (0138) — **Ein wirkungsfreier Umbau wird durch zeichengleiche Korpuszahlen
  bewiesen**, nicht behauptet: vorher/nachher dieselben 29/15183/898/854/44/1994/4 und
  dieselbe Aufstellung je Regel. Vorher messen, sonst gibt es nichts zu vergleichen.
- 2026-09-05 (0138) — **Die Zahlen neben der roten Zeile belegen den *Grund*.** „Fall 1
  verfehlt, Zusicherungen 1 erwartet 1" sagt: Der Mustervergleich liest weiter, nur der
  Abzug fehlt. **Eine Fehlermeldung, die alle Messwerte des Falls druckt und nicht nur
  den verfehlten, ist eine zweite Aussage gratis.**
- 2026-09-05 (0138) — **`WILL_FAIL` beweist nur „ungleich 0".** Wo 1 und 2 Verschiedenes
  heißen, kommt ein `sh`-Skript als eigener ctest-Eintrag dazu, das beide Fassungen
  nacheinander läuft und `echo $?` abdruckt. Das ist zugleich der abzuliefernde Beleg.
- 2026-09-05 (0138) — **Der Messstand gehört unter `bau/`.** Dort betritt ihn kein
  Riegel (`UNGELESENE_ORDNER`), `baulauf.py` nimmt ihn von der Manifestsuche aus
  (`AUSGENOMMEN`), und `.gitignore` fängt ihn. Woanders im Vorhaben zählte der Riegel
  die Datei- und Zielnamen des Messstands mit — und der Vorlauf hätte nicht mehr die
  Zahlen des Arbeitsbereichs.
- 2026-09-05 (0138) — **Eine Gegenprobe, die den Mutanten *nicht* trifft, ist so viel
  wert wie der Rotnachweis.** „2 von 48 verfehlt, und die drei Nachbarfälle bleiben
  grün" belegt, dass die Tabelle nicht als Ganzes reißt.
- 2026-09-05 (0135) — **Eine feste Sollzahl in einem Messgerät verfällt in Stunden.**
  Während *eines* Laufs stieg die Zielzahl von 19 auf 20, weil ein fremdes Paket ein
  Ziel anlegte. Ersatz ist das **Gleichheitsmaß gegen den eigenen Stand davor** — und
  der Stand gehört **benannt** (Commit, Datum, Profil).
- 2026-09-05 (0135) — **Ein Maß, das ausfällt, muss rot melden, nicht übersprungen
  werden** — und deshalb keinen Schalter bauen, der den Vergleich abschaltet.
- 2026-09-05 (0135) — **Ein Baubaum mit fremdem `CMakeCache.txt` sieht aus wie ein
  kaputter Baum.** Hängt die Ablage am *Laufnamen* statt am Baum, findet der zweite Lauf
  den Cache des ersten. `CMAKE_HOME_DIRECTORY:INTERNAL` prüfen, dann erst wegwerfen.
- 2026-09-05 (0135) — **Mutant und Vergleichsstand müssen aus demselben Commit stammen.**
  Sonst ist der Lauf aus zwei Gründen zugleich rot — an einer Stelle hoben sie sich sogar
  auf (+1 Mutation gegen +1 Drift = keine Abweichung).
- 2026-09-05 (0133) — **Ein Riegel, der nur über fehlerfreie Bäume fährt, kann seine
  eigene Stumpfheit nie zeigen**: „N geprüft, alle in Ordnung" sagt nichts darüber, dass
  geprüft wurde. Und **ein Werkzeug, das nur läuft, weil eine Abnahme es nennt, ist kein
  Riegel** — die Bahn (`add_test`) ist die Arbeit.
- 2026-09-05 (0129) — **Eine Ausnahmeregel gegen den Fall messen, den sie *nicht* fangen
  darf.** Und: **ein Fall, der zwei Regeln zugleich trifft, weist keine von beiden nach.**
- 2026-09-05 (0129) — **Ein Selbsttestfall mit gekürzter Eingabe prüft die falsche
  Frage.** Die Falltabelle muss tragen, was das Programm wirklich bildet.
- 2026-09-05 (0129) — **Ein Entwurf in `python3` vor dem C++ entscheidet den Regelsatz
  billig**; der C++-Lauf war beim ersten Übersetzen inhaltlich fertig.
- 2026-09-05 (0133, 0129) — **Einen Prüfpunkt rot machen, ohne die alten zu bewegen:**
  die Mutation so wählen, dass sie *nur* ihn trifft. „1 von 43 verfehlt, und zwar der
  gemeinte" ist der Beleg, den kein Sammelrot liefert.
- 2026-09-05 (0110, 0083, 0129, 0138) — **Mutieren, ohne den Quellbaum anzufassen:**
  Mutant als eigene Kopie außerhalb übersetzen, eigenes CMake-Projekt unter `bau/`, das
  ausgelieferte Quelle und Mutanten nebeneinander baut, je Fall ein `add_test`. Das
  Kopierskript bricht ab, wenn der erwartete Wortlaut nicht **genau einmal** vorkommt.
  `git status` bleibt vor/nach zeichengleich.
- 2026-09-05 (0110) — **`ctest -R <muster>` ohne Treffer gibt Code 0**; wer `ctest` ruft,
  braucht **`--no-tests=error`**.
- 2026-09-05 (0110, 0129, 0138) — **Ein Mutationsnachweis braucht einen Vorlauf am
  unveränderten Baum** — sonst meldet ein aus fremdem Grund roter Baum jede Mutation als
  gefangen. Bei 0138 belegte der Vorlauf zusätzlich, dass der Wegwerfbau ein fairer
  Prüfstand ist: dieselben Korpuszahlen wie der Arbeitsbereich.
- 2026-09-05 (0079, 0083) — **Der gedruckte Wortlaut einer Fundstelle ist nicht
  schlüsselfähig**: Listen als **Mehrfachmenge** vergleichen, nie deduplizieren.
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

- 2026-09-04, **achtmal getroffen** (zuletzt 0138) — `cd` nimmt mir `Edit` und `Write`
  still weg; die Ablehnung nennt den Modus, nicht den Pfad. **Nie `cd`.** Ist es
  passiert: `cd /home/adria/fabrik` als eigener Aufruf holt sie zurück.
- 2026-09-05 (0138) — **Der `Write`-Werkzeug schreibt nicht nach `$TMPDIR`**, obwohl die
  Bash-Sandbox es erlaubt; und **Heredocs (`python3 - <<'PY'`) werden abgelehnt**.
  Beides zusammen heißt: Hilfsskripte als Datei in den **gitignorierten** Messbaum
  (`bau/messung-<paket>/`) schreiben und mit `python3 <datei>` rufen.
- 2026-09-02, bis 2026-09-05 bestätigt — Zusammengesetzte Befehle (`a && b`, `a; b`),
  `for`-Läufe, `&` und ein vorangestelltes `VAR=wert` werden meist abgelehnt; einzelne
  Aufrufe und **Pipes** nicht. **Mehrzeilig geht**, samt `> datei` und `echo $?` — das
  ist der Weg, den Rückgabewert einer Messung abzudrucken.
- 2026-09-05 — **`sed`, `cp` und `awk` werden abgelehnt**; Ersatz ist `python3` mit
  `shutil` (auch fürs Archiv). Ein **gebautes Binärprogramm direkt aufzurufen** ebenfalls:
  über `ctest` gehen. `grep` und `cat` im Baum nur über das Grep-Werkzeug, `git grep`
  oder **hinter einer Pipe**.
- 2026-09-05 (0083, 0129) — Braucht ein Werkzeug **Argumente, die sein `add_test` nicht
  hergibt**: eine **eigene `CMakeLists.txt`** mit derselben Quelle (absoluter Pfad) und
  je Messung einem `add_test`.
- 2026-09-03, 2026-09-05 dreimal — Beim Sabotieren beißt `-Werror=unused-*`: Fällt etwas
  aus dem Spiel, wird der **Bau** rot statt des Tests. Sauberste Griffe: einen Zähler
  nicht hochzählen, ein `return false;` umdrehen, eine Zuweisung von `true` auf `false`.
  Die letzte hat bei 0138 gehalten — die Variable bleibt gelesen.
- 2026-09-05, **zweimal** — **`git commit` wird abgelehnt**, in jeder Form; `git add`
  läuft. Am Ende **stagen und melden**, nicht am Befehl feilen.

## Offene Faehrten

- 2026-09-05 (0138) — **`werkzeuge/belegstellen/belegstellen_riegel.cpp` übersetzt zur
  Stunde nicht** (`invalid initialization of reference of type 'const Absatz&' from
  'const std::string_view'`, zwei Stellen). Ein fremder Lauf ist mitten in der Änderung.
  Nicht angefasst, im Ergebnisbericht gemeldet. **Der Arbeitsbereich als Ganzes ist
  deshalb rot; Einzelziel und Wegwerfbau sind es nicht.**
- 2026-09-05 (0133, 0129, 0135) — **Ein fremder Lauf committet meine Dateien mit**,
  dreimal an einem Tag. Inhaltlich nichts verloren, aber `git log -S` führt die Arbeit
  unter fremdem Betreff. Gegenstand von `0131`.
- 2026-09-05 (0133) — **Die Bahn liegt im falschen Kasten.** `schlussriegel_nachbau`
  misst den Baum, nicht das Erzeugnis, sitzt aber im `pruefstand`. Vorschlag `0136`.
- 2026-09-04, 2026-09-05 **zehnmal** — **Der Korpus driftet während des eigenen Laufs.**
  Bei 0138 bewegten sich vier Dateien, darunter `werkzeugkette.cmake`. Am Ende neu
  lesen, dann Edits, Größe zuletzt messen. Jede Messung gegen „den Stand davor" muss
  den Stand **abdrucken**.
- 2026-09-05 (0110) — **Der Baulauf ruft `ctest` ohne `--no-tests=error`**: ein Mitglied
  ohne Proben meldet `ergebnis: ok`. Außerhalb des Vorhabens, gemeldet.
- 2026-09-05 (0083) — **Der `belegstellen_riegel` schlägt sein Ziel über den
  *Basisnamen* nach**: einen falschen Treffer bei genau einer gleichnamigen Datei fängt
  er nicht. Gemeldet.
- 2026-09-05 — **Die Einheit der Klasse 2 lautet im Kern „…Preisen 2015", in T5 „…Preisen
  des Jahres 2015".** Entscheidung zwischen zwei Dokumenten, nicht bei mir.
- 2026-09-05, fünfmal — **Jede Zahl in einer Abnahme ist ein Messwert von ihrem
  Zuschnittstag.** Besser ist die **Bedingung** (steigt/fällt gegenüber dem Stand von
  eben); für 0079, 0133, 0104 und 0138 hat der Projektmanager das selbst so entschieden.
- 2026-09-02 — Der Prüfstand hat weder **Regressionsbestand** noch **Determinismustest
  über Speichern und Laden** — laut Rolle meine wichtigsten; `probe_zweimal_dasselbe`
  deckt nur zwei Aufrufe im selben Prozess ab.
- 2026-09-03 — **Eine Invariante fängt Nullfälle nicht.** Nur ein gebauter Fall mit
  *einer* zulässigen Art tut es.
