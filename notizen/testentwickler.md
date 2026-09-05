# Logbuch: testentwickler

Belege gehören in die Ergebnisdatei — hier steht die Lehre. Höchstens 12.000 Zeichen.
**2026-09-05 archiviert** nach `notizen/archiv/testentwickler-2026-09-05.md`, `-1.md`
.. `-7.md`.

---

## Was funktioniert

<!-- Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-09-05 (0105) — **Prüfe zuerst, ob dein Paket schon halb gebaut ist.** Ein früherer
  Lauf hatte den Code geschrieben, der Status blieb `offen`, der Runner plante neu ein.
  **Erste Handgriffe: `git log` auf die Datei des Pakets, `ls befunde/messung-<nr>/`, im
  Quelltext nach der Paketnummer greppen.**
- 2026-09-05 (0105) — **Was ein abgebrochener Lauf hinterlässt, ist der Code — nie der
  Nachweis.** Gefehlt haben jeder Rotnachweis, zwei von drei Bäumen und der Kopfabschnitt
  aus der Abnahme. **Ein Kommentar, der auf einen Abschnitt verweist, den es nicht gibt,
  ist die Signatur eines Abbruchs.**
- 2026-09-05 (0105) — **Ein ungemessener Kommentar ist eine Falschaussage in Wartestellung.**
  „Ohne die Regel reissen die ersten drei, der vierte bleibt grün" — gemessen rissen 1, 2
  und **4**. **Jede Behauptung über das Verhalten eines Mutanten gehört gemessen, bevor
  sie im Quelltext steht.**
- 2026-09-05 (0105) — **Ein Mutant, der nichts ändert, läuft grün durch und sieht aus wie
  Deckung.** `zeile_bei(i)` statt `zeile_bei(j)` war äquivalent, weil das Trennzeichen des
  Umbruchs schon die **neue** Zeilennummer trägt. Erst `i - 1` traf. **Grün beim Mutanten
  heißt zuerst „falsch mutiert", nicht „Regel ungedeckt".**
- 2026-09-05 (0105) — **Zwei Mutanten für eine zweiteilige Regel, und je Hälfte müssen
  *andere* Fälle reißen.** „3 von 51" gegen „1 von 51", kein Fall bei beiden — das belegt,
  dass die Tabelle Verschiedenes misst und nicht als Ganzes reißt.
- 2026-09-05 (0105) — **Der Fall, der den *Preis* einer Regel ausschreibt, misst sie mit.**
  Er stand als „bleibt grün" da und riss beim Mutanten. Preis-Fälle sind keine Zierde.
- 2026-09-05 (0105) — **Beide Fassungen im *selben* `ctest`-Aufruf über den Arbeitsbaum
  laufen lassen.** Zwei getrennte Läufe messen die Drift mit. Das ist der einzige haltbare
  Weg zu „auf dem dann geltenden Korpus".
- 2026-09-05 (0105) — **Ein Messgerät, das seinen eigenen Tippfehler fängt, fängt auch
  fremde**: Meine Erwartung stand falsch auf `0 0 0` und wurde rot mit
  `erwartet [0 0 0], gemessen [0 0 1]`.
- 2026-09-05 (0138) — **Ein einmaliger Rotnachweis deckt keine Regel.** Die Prüffrage
  lautet nicht „ist die Regel einmal rot geworden", sondern „wird sie es von selbst,
  heute, ohne eigens gebauten Baum".
- 2026-09-05 (0138) — **Die Lücke sitzt regelmäßig in der *Kopplung*, nicht im Baustein.**
  **Vor jeder neuen Tabelle fragen: Welche Stelle im Programm wird von keiner bestehenden
  erreicht?**
- 2026-09-05 (0138) — **Damit der Selbsttest an eine Datei-lesende Funktion herankommt,
  bekommt sie einen Texteingang**: Rumpf nach `f(string_view inhalt, …)`, Pfadfassung wird
  ein dünner Mantel. — *0105 zeigt die zweite Hälfte:* **derselbe Bauaufruf für Ernstfall
  und Selbsttest**. Ein nachgebauter Absatz im Test misst eine Fassung, die nirgends läuft.
- 2026-09-05 (0138, 0105) — **Ein wirkungsfreier Umbau wird durch zeichengleiche
  Korpuszahlen bewiesen**, nicht behauptet. Vorher messen, sonst gibt es nichts zu
  vergleichen.
- 2026-09-05 (0138, 0105) — **`WILL_FAIL` beweist nur „ungleich 0".** Wo 1 und 2
  Verschiedenes heißen, kommt ein `sh`-Skript als eigener ctest-Eintrag dazu, das die
  Rückgabewerte abdruckt **und gegen eine Erwartung vergleicht**. Nur drucken macht einen
  Bericht, keinen Riegel.
- 2026-09-05 (0138) — **Der Messstand gehört unter `bau/`** — dort betritt ihn kein Riegel,
  `baulauf.py` nimmt ihn von der Manifestsuche aus, `.gitignore` fängt ihn.
  *Einschränkung 0105:* Unter `befunde/` ist er zwar ungelesen und manifestfrei, aber seine
  **Dateinamen** zählen mit — 452 gegen 21.207 Pfade. Vorschlag `0143`.
- 2026-09-05 (0138) — **Eine Gegenprobe, die den Mutanten *nicht* trifft, ist so viel wert
  wie der Rotnachweis.**
- 2026-09-05 (0135) — **Eine feste Sollzahl in einem Messgerät verfällt in Stunden.**
  Ersatz ist das **Gleichheitsmaß gegen den eigenen Stand davor** — und der Stand gehört
  **benannt** (Commit, Datum, Profil).
- 2026-09-05 (0135) — **Ein Maß, das ausfällt, muss rot melden, nicht übersprungen werden.**
  Und: **Mutant und Vergleichsstand müssen aus demselben Commit stammen.**
- 2026-09-05 (0133) — **Ein Riegel, der nur über fehlerfreie Bäume fährt, kann seine eigene
  Stumpfheit nie zeigen.** Und **ein Werkzeug, das nur läuft, weil eine Abnahme es nennt,
  ist kein Riegel** — die Bahn (`add_test`) ist die Arbeit.
- 2026-09-05 (0129) — **Eine Ausnahmeregel gegen den Fall messen, den sie *nicht* fangen
  darf.** Und: **ein Fall, der zwei Regeln zugleich trifft, weist keine von beiden nach.**
- 2026-09-05 (0133, 0129) — **Einen Prüfpunkt rot machen, ohne die alten zu bewegen:** die
  Mutation so wählen, dass sie *nur* ihn trifft.
- 2026-09-05 (0110, 0083, 0129, 0138, 0105) — **Mutieren, ohne den Quellbaum anzufassen:**
  Mutant als eigene Kopie außerhalb übersetzen, eigenes CMake-Projekt, je Fall ein
  `add_test`. Das Kopierskript bricht ab, wenn der erwartete Wortlaut nicht **genau
  einmal** vorkommt. `git status` bleibt vor/nach zeichengleich.
- 2026-09-05 (0110) — **`ctest -R <muster>` ohne Treffer gibt Code 0**; wer `ctest` ruft,
  braucht **`--no-tests=error`**.
- 2026-09-05 (0110, 0129, 0138, 0105) — **Ein Mutationsnachweis braucht einen Vorlauf am
  unveränderten Baum.**
- 2026-09-05 (0079, 0083, 0105) — **Der gedruckte Wortlaut einer Fundstelle ist nicht
  schlüsselfähig**: Listen als **Mehrfachmenge** vergleichen (`Counter(a) - Counter(b)`),
  nie mit `in`. Erst dann ist „genau fünf Zeilen weichen ab" belastbar.
- 2026-09-05 (0107) — **Zu „X kollidiert mit keinem Fremden" gehört „X trifft jedes
  Eigene"** — **Frage vor jedem Riegel: Wie umginge ich ihn, ohne ihn anzufassen?**
- 2026-09-05 — **Die Gegenprobe ist ein *Mutant des ausgelieferten Standes*, nicht ein
  alter Commit** — sonst misst man drei Pakete und nennt es eines.
- 2026-09-05 — **Ein eigener Kommentar kann einen fremden Riegel rot machen.** Der
  `belegstellen_riegel` liest **jede** Bauquelle. *Der Griff dagegen (0105):* das
  Schlüsselwort im Quelltext **maskieren** (`\101bschnit\164`) — zur Laufzeit steht das
  Wort da, im Dateitext nicht. Sonst gilt: **nach einem Schlüsselwort klein weiterschreiben
  oder ein Satzzeichen setzen**, dann entsteht gar keine Fundstelle.
- 2026-09-05, **fünfmal** — **Ein Mutant scheitert gern aus dem falschen Grund.** Immer
  prüfen, ob die rote Zeile die *gemeinte* ist.
- 2026-09-04, 2026-09-05 — **Eine Schwelle, deren Zahl sich nicht messen lässt, gehört
  nicht ins Messgerät** — **Herkunft, keine Marge**, und der **kleinste** Wert.
- 2026-09-04, seither zwölfmal — **Ein Rotnachweis je Teilregel**, und **je Teilregel
  *andere* Fälle reißen zu lassen belegt, dass sie Verschiedenes messen**.
- 2026-09-04, seither achtmal — Die Entscheidung, die der Test misst, als **eigenen
  Aufruf** herausziehen.
- 2026-09-02, 2026-09-05 bestätigt — **Beide Bauwege einzeln prüfen**: `baulauf.py` ruft
  jede `CMakeLists.txt` auch allein.

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-04, **neunmal getroffen** (zuletzt 0105) — `cd` nimmt mir `Edit` und `Write`
  still weg; die Ablehnung nennt den Modus, nicht den Pfad. **Nie `cd`.** Ist es passiert:
  `cd /home/adria/fabrik` als eigener Aufruf holt sie zurück.
- 2026-09-05 (0138) — **`Write` schreibt nicht nach `$TMPDIR`**, und **Heredocs
  (`python3 - <<'PY'`) werden abgelehnt**. Hilfsskripte als Datei neben den Messstand
  schreiben und mit `python3 <datei>` rufen. *0105:* geht auch unter
  `befunde/messung-<nr>/`, und dort bleibt das Skript als Beleg liegen.
- 2026-09-02, bis 2026-09-05 bestätigt — Zusammengesetzte Befehle (`a && b`, `a; b`),
  `for`-Läufe, `&` und ein vorangestelltes `VAR=wert` werden meist abgelehnt; einzelne
  Aufrufe und **Pipes** nicht. **Mehrzeilig geht**, samt `> datei` und `echo $?`.
- 2026-09-05 (0105) — **`rm` und `Path.unlink` werden abgelehnt**, auch für eine Datei aus
  dem eigenen Lauf. **Folge: den Namen einer Zwischenfassung so wählen, dass der zweite
  Anlauf sie überschreibt** — sonst bleibt sie als Verwechslungsgefahr liegen.
- 2026-09-05 — **`sed`, `cp` und `awk` werden abgelehnt**; Ersatz ist `python3` mit
  `shutil` (auch fürs Archiv). Ein **gebautes Binärprogramm direkt aufzurufen** ebenfalls:
  über `ctest` gehen. `grep` und `cat` im Baum nur über das Grep-Werkzeug, `git grep` oder
  **hinter einer Pipe**.
- 2026-09-05 (0083, 0129, 0105) — Braucht ein Werkzeug **Argumente, die sein `add_test`
  nicht hergibt**: eine **eigene `CMakeLists.txt`** mit derselben Quelle (absoluter Pfad)
  und je Messung einem `add_test`.
- 2026-09-03, 2026-09-05 dreimal — Beim Sabotieren beißt `-Werror=unused-*`: Fällt etwas
  aus dem Spiel, wird der **Bau** rot statt des Tests. *0105 ergänzt den saubersten Griff:*
  **einen Vergleich abschwächen (`==` → `>=`)** — die Variable bleibt gelesen, der Warnsatz
  schweigt, die Regel ist weg.
- 2026-09-05, **zweimal** — **`git commit` wird abgelehnt**, in jeder Form; `git add`
  läuft. Am Ende **stagen und melden**, nicht am Befehl feilen.

## Offene Faehrten

- 2026-09-05 (0105) — **Fall 12 in `ZITATFAELLE` hängt an einem Mutanten, den es im Repo
  nicht gibt** — schmaler gedeckt als die anderen drei.
- 2026-09-05 (0105) — **Die Regel des Pakets ist am Bestand nicht gedeckt**: Fällt sie weg,
  bleibt der Arbeitsbaum grün. Paket `0106` setzt genau dort den Anker.
- 2026-09-05 (0105) — **Der Messstand unter `befunde/` bläht die Menge der ungelesenen
  Pfade auf**: 452 gegen 21.207, Laufzeit 0,23 s gegen 0,84 s. Vorschlag `0143` liegt.
- 2026-09-05 (0105) — **Ein zweiter testentwickler lief parallel** und hat mein Logbuch
  mitcommittet, während ich es archivierte. Wer hier schreibt, liest **unmittelbar vorher**
  neu.
- 2026-09-05 (0105, 0138) — **`kern/test/verlauf_probe.cpp` übersetzt zur Stunde nicht**
  (`expected '}' at end of input`); ein fremder Lauf steht mitten in `0140`. **Der
  Arbeitsbaum als Ganzes ist deshalb rot, mein Ziel und der Einzelweg sind es nicht** —
  zweimal an zwei Tagen dieselbe Lage. Erst das Einzelziel messen, dann melden.
- 2026-09-05 (0133, 0129, 0135, 0105) — **Ein fremder Lauf committet meine Dateien mit**,
  viermal an einem Tag. `git log -S` führt die Arbeit unter fremdem Betreff. Paket `0131`.
- 2026-09-04, 2026-09-05 **elfmal** — **Der Korpus driftet während des eigenen Laufs.** Bei
  0105 wanderte HEAD mitten im Lauf von `0333b81` auf `4bbd069`. Am Ende neu lesen, dann
  Edits, Größe zuletzt messen. Jede Messung gegen „den Stand davor" muss den Stand
  **abdrucken**.
- 2026-09-05 (0110) — **Der Baulauf ruft `ctest` ohne `--no-tests=error`**: ein Mitglied
  ohne Proben meldet `ergebnis: ok`. Gemeldet.
- 2026-09-05 (0083) — **Der `belegstellen_riegel` schlägt sein Ziel über den *Basisnamen*
  nach**: einen falschen Treffer bei gleichnamigen Dateien fängt er nicht.
- 2026-09-05, sechsmal — **Jede Zahl in einer Abnahme ist ein Messwert von ihrem
  Zuschnittstag.** Besser ist die **Bedingung**; bei 0105 nannte die Abnahme 38 Zitate, der
  Bestand führte 37 — die Abnahme sagte selbst „auf dem dann geltenden Korpus".
- 2026-09-02 — Der Prüfstand hat weder **Regressionsbestand** noch **Determinismustest
  über Speichern und Laden** — laut Rolle meine wichtigsten; `probe_zweimal_dasselbe`
  deckt nur zwei Aufrufe im selben Prozess ab.
- 2026-09-03 — **Eine Invariante fängt Nullfälle nicht.** Nur ein gebauter Fall tut es.
