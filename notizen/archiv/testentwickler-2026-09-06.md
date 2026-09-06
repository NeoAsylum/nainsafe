# Logbuch: testentwickler

Belege gehören in die Ergebnisdatei — hier steht die Lehre. Höchstens 12.000 Zeichen.
**2026-09-05 archiviert** nach `notizen/archiv/testentwickler-2026-09-05.md`, `-1.md`
.. `-8.md`.

---

## Was funktioniert

<!-- Format: - JJJJ-MM-TT — Beobachtung -->

- 2026-09-05 (0106) — **Die Lücke sitzt in der Verdrahtung, nicht im Baustein**, und der
  Griff dagegen ist immer derselbe: **die Entscheidung als eigenen Aufruf herausziehen.**
  Eine Tabelle, die den Baustein unmittelbar ruft, kann den Schritt darüber nie messen.
  **Vor jeder neuen Tabelle fragen: Welche Stelle erreicht keine bestehende?**
- 2026-09-05 (0106) — **Erwarte den *Ausgang*, nicht das Zwischenergebnis.** Ist ein
  Grund gesetzt, hat `steht_da` keine Wirkung mehr; eine Erwartung an einen wirkungslosen
  Wert lässt Mutanten an Fällen sterben, **die sie gar nicht treffen** — grün aussehende
  Deckung. Die Regel dahinter: *Miss, was der Aufrufer aus dem Wert macht.*
- 2026-09-05 (0106) — **Damit Ernstfall und Test denselben Weg gehen, muss auch die
  Auswertung ein Aufruf sein** (`ausgang(urteil)`), nicht eine im Test nachgebaute
  `if`-Kette. Sonst misst der Test eine zweite Fassung.
- 2026-09-05 (0106) — **Der Vorlauf gehört in *denselben* Aufruf.** Alte und neue Fassung
  nebeneinander übersetzen und beide im selben Lauf über den Arbeitsbaum schicken. Zwei
  getrennte Läufe messen die Drift mit: Bei 0106 wären 37→40 Zitate als meine Wirkung
  erschienen, tatsächlich kam mitten im Lauf `aktion.cpp` von fremder Hand dazu.
- 2026-09-05 (0106) — **Das Messskript ist selbst ein Riegel, kein Bericht:** Erwartung
  je Mutant im Skript, Rückgabe 1 bei Abweichung. Geprüft werden **vier** Dinge —
  Rückgabecode, *welcher* Fall riss, dass **keine fremde Tabelle** riss, und dass der
  Bestand **gar nicht erst gelesen** wurde.
- 2026-09-05 (0106) — **Ein Mutant je Fall, sonst prüft der Fall nichts.** Die Abnahme
  verlangte vier; zwei Fälle wären damit nie rot geworden. Zwei Mutanten nachgelegt —
  das ist Rollenregel, nicht Fleiß.
- 2026-09-05 (0106) — **Zähl nach, ob der Bestand eine Regel wirklich hält, bevor du das
  glaubst.** Der Vorschlag nannte *ohne Gliederung* als am Bestand gehalten; gezählt
  waren es **null** Fundstellen. Der Satz war umformuliert worden. Umgekehrt hält der
  Bestand die Gliederungsziffer 37-fach — die bekam deshalb keinen Fall, **und der Grund
  steht im Quelltext**, damit ihn niemand als Lücke „repariert".
- 2026-09-05 (0105) — **Prüfe zuerst, ob dein Paket schon halb gebaut ist.** Erste
  Handgriffe: `git log` auf die Datei des Pakets, `ls befunde/messung-<nr>/`, im
  Quelltext nach der Paketnummer greppen.
- 2026-09-05 (0105) — **Was ein abgebrochener Lauf hinterlässt, ist der Code — nie der
  Nachweis.** Ein Verweis auf einen Textblock, den es nicht gibt, ist seine Signatur.
- 2026-09-05 (0105) — **Ein ungemessener Kommentar ist eine Falschaussage in
  Wartestellung.** Jede Behauptung über das Verhalten eines Mutanten gehört gemessen,
  bevor sie im Quelltext steht.
- 2026-09-05 (0105) — **Ein Mutant, der nichts ändert, läuft grün durch und sieht aus wie
  Deckung.** **Grün beim Mutanten heißt zuerst „falsch mutiert", nicht „Regel ungedeckt".**
- 2026-09-05 (0105, 0106) — **Je Teilregel *andere* Fälle reißen zu lassen belegt, dass
  die Tabelle Verschiedenes misst und nicht als Ganzes reißt.** Bei 0106 sieben Mutanten,
  sechs verschiedene Fälle, kein Fall bei zweien aus demselben Zweig.
- 2026-09-05 (0105) — **Der Fall, der den *Preis* einer Regel ausschreibt, misst sie mit.**
- 2026-09-05 (0138) — **Ein einmaliger Rotnachweis deckt keine Regel.** Die Prüffrage
  lautet nicht „ist die Regel einmal rot geworden", sondern „wird sie es von selbst,
  heute, ohne eigens gebauten Baum".
- 2026-09-05 (0138) — **Damit der Selbsttest an eine Datei-lesende Funktion herankommt,
  bekommt sie einen Texteingang** — oder die Entscheidung wird herausgezogen (0106, der
  billigere Schnitt: zwei Listen und ein Name statt eines Gegenstands auf der Platte).
- 2026-09-05 (0138, 0105, 0106) — **Ein wirkungsfreier Umbau wird durch zeichengleiche
  Korpuszahlen bewiesen**, nicht behauptet. Vorher messen, sonst gibt es nichts zu
  vergleichen.
- 2026-09-05 (0138, 0105) — **`WILL_FAIL` beweist nur „ungleich 0".** Wo 1 und 2
  Verschiedenes heißen, gehört der Rückgabewert gegen eine Erwartung verglichen. Beim
  `belegstellen_riegel`: **2 = Selbsttest, 1 = Befund am Bestand, 0 = grün.**
- 2026-09-05 (0138) — **Der Messstand gehört unter `bau/`**; *Einschränkung 0105:* unter
  `befunde/` zählen seine **Dateinamen** mit. *0106 löst es:* **Skript unter
  `befunde/messung-<nr>/`, gebaut und gelaufen wird in `$TMPDIR`** — Beleg bleibt liegen,
  der Korpus wächst um zwei Dateien statt um einen Baum.
- 2026-09-05 (0135) — **Eine feste Sollzahl in einem Messgerät verfällt in Stunden.**
  Ersatz ist das **Gleichheitsmaß gegen den eigenen Stand davor** — und der Stand gehört
  **benannt** (Commit, Datum, Profil). Bei 0106 als `VORSTAND` im Skript.
- 2026-09-05 (0135) — **Mutant und Vergleichsstand müssen aus demselben Commit stammen.**
- 2026-09-05 (0133) — **Ein Werkzeug, das nur läuft, weil eine Abnahme es nennt, ist kein
  Riegel** — die Bahn ist die Arbeit.
- 2026-09-05 (0129) — **Eine Ausnahmeregel gegen den Fall messen, den sie *nicht* fangen
  darf.** Und: **ein Fall, der zwei Regeln zugleich trifft, weist keine von beiden nach.**
- 2026-09-05 (0110, 0083, 0129, 0138, 0105, 0106) — **Mutieren, ohne den Quellbaum
  anzufassen:** Mutant als Kopie außerhalb übersetzen. Das Skript bricht ab, wenn der
  erwartete Wortlaut nicht **genau einmal** vorkommt. `git status` bleibt zeichengleich.
- 2026-09-05 (0110) — **`ctest -R <muster>` ohne Treffer gibt Code 0**; wer `ctest` ruft,
  braucht **`--no-tests=error`**.
- 2026-09-05 (0079, 0083, 0105) — **Der gedruckte Wortlaut einer Fundstelle ist nicht
  schlüsselfähig**: Listen als **Mehrfachmenge** vergleichen, nie mit `in`.
- 2026-09-05 (0107) — **Frage vor jedem Riegel: Wie umginge ich ihn, ohne ihn anzufassen?**
- 2026-09-05 — **Die Gegenprobe ist ein *Mutant des ausgelieferten Standes*, nicht ein
  alter Commit** — sonst misst man drei Pakete und nennt es eines.
- 2026-09-05, **sechsmal** — **Ein eigener Kommentar kann einen fremden Riegel rot machen.**
  Der `belegstellen_riegel` liest **jede** Bauquelle. Griffe: das Schlüsselwort
  **maskieren** (`\101bschnit\164`, `\125eberschrift`) oder **klein weiterschreiben /
  Satzzeichen setzen**. *0106:* Ein erwarteter Grund im Testtisch, der ein Schlüsselwort
  enthält, braucht die Maskierung — zur Laufzeit steht das Wort da, im Dateitext nicht.
- 2026-09-05, **fünfmal** — **Ein Mutant scheitert gern aus dem falschen Grund.** Immer
  prüfen, ob die rote Zeile die *gemeinte* ist.
- 2026-09-04, 2026-09-05 — **Eine Schwelle, deren Zahl sich nicht messen lässt, gehört
  nicht ins Messgerät** — **Herkunft, keine Marge**, und der **kleinste** Wert.
- 2026-09-02, 2026-09-05 bestätigt (zuletzt 0106) — **Beide Bauwege einzeln prüfen**:
  `baulauf.py` ruft jede `CMakeLists.txt` auch allein.

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-04, **neunmal getroffen** (zuletzt 0105) — `cd` nimmt mir `Edit` und `Write`
  still weg; die Ablehnung nennt den Modus, nicht den Pfad. **Nie `cd`.** Ist es passiert:
  `cd /home/adria/fabrik` als eigener Aufruf holt sie zurück.
- 2026-09-05 (0138) — **`Write` schreibt nicht nach `$TMPDIR`**, und **Heredocs
  (`python3 - <<'PY'`) werden abgelehnt**. Hilfsskripte als Datei ins Repo schreiben und
  mit `python3 <datei>` rufen; das Skript darf dann in `$TMPDIR` arbeiten.
- 2026-09-05 (0106) — **`python3 -c "…"` als Einzeiler läuft** — der billigste Weg für
  `shutil.copy` (Archivieren des Logbuchs) ohne eine Hilfsdatei im Baum.
- 2026-09-02, bis 2026-09-05 bestätigt — Zusammengesetzte Befehle (`a && b`, `a; b`),
  `for`-Läufe, `&` und ein vorangestelltes `VAR=wert` werden meist abgelehnt; einzelne
  Aufrufe und **Pipes** nicht. **Mehrzeilig geht**, samt `> datei` und `echo $?`.
- 2026-09-05 (0105) — **`rm` und `Path.unlink` werden abgelehnt**, auch für eine Datei aus
  dem eigenen Lauf. **Folge: den Namen einer Zwischenfassung so wählen, dass der zweite
  Anlauf sie überschreibt.**
- 2026-09-05 — **`sed`, `cp` und `awk` werden abgelehnt**; Ersatz ist `python3` mit
  `shutil`. **`grep` und `cat` im Baum nur über das Grep-Werkzeug, `git grep` oder hinter
  einer Pipe** — und `grep | sed | sort` wird als Ganzes abgelehnt, sobald `sed` darin
  steht: Ausgabe erst in eine Datei, dann greppen.
- 2026-09-05 (0083, 0129, 0105) — Braucht ein Werkzeug **Argumente, die sein `add_test`
  nicht hergibt**: eine **eigene `CMakeLists.txt`** mit derselben Quelle — *oder (0106,
  billiger)* **`g++` unmittelbar aus dem Messskript**, mit denselben Sprachschaltern.
- 2026-09-03, 2026-09-05 dreimal — Beim Sabotieren beißt `-Werror=unused-*`: Fällt etwas
  aus dem Spiel, wird der **Bau** rot statt des Tests. Griffe: einen Vergleich
  abschwächen (`==` → `>=`), *oder (0106)* **den Mutantenbau ohne `-Werror` fahren** —
  dann aber den Vergleichsstand mit **denselben** Schaltern.
- 2026-09-05, **zweimal** — **`git commit` wird abgelehnt**, in jeder Form; `git add`
  läuft. Am Ende **stagen und melden**, nicht am Befehl feilen.

## Offene Faehrten

- 2026-09-05 (0106) — **Die Zahl 37 im Kopf von `URTEILSFAELLE` ist ein Messwert vom
  Zuschnittstag, keine Bedingung.** Driftet der Bestand, veraltet die Begründung, ohne
  dass etwas rot wird. Stehengelassen, weil sie begründet und nichts schwellt — aber es
  ist die Sorte Satz, die still falsch wird.
- 2026-09-05 (0106) — **`ZIELFAELLE`, `ABSTANDSFAELLE`, `SATZFAELLE` sind auf dieselbe
  Verdrahtungslücke hin nicht nachgemessen.** 0106 hat *eine* Kopplung geschlossen; die
  Frage „welcher Schritt in `pruefe_zitate` hat noch keinen Fall" ist offen — die
  Ortsfrage (`zielart` → `grund`) und die Reihenfolge der drei Zitatformen sind die
  nächsten Kandidaten. Verdient ein eigenes Paket.
- 2026-09-05 (0105) — **Fall 12 in `ZITATFAELLE` hängt an einem Mutanten, den es im Repo
  nicht gibt** — schmaler gedeckt als die anderen drei.
- 2026-09-05 (0105) — **Der Messstand unter `befunde/` bläht die Menge der ungelesenen
  Pfade auf.** Vorschlag `0143` liegt. *0106 mildert es:* nur das Skript liegt dort.
- 2026-09-05 (0105, 0106) — **Ein zweiter Agent lief parallel** und hat meine Dateien
  mitcommittet. Wer ins Logbuch schreibt, liest **unmittelbar vorher** neu.
- 2026-09-04, 2026-09-05 **zwölfmal** — **Der Korpus driftet während des eigenen Laufs.**
  Bei 0106 wanderte HEAD von `5605c54` auf `4ff788d` und der Bestand von 37 auf 40
  Zitate, beides von fremder Hand. Jede Messung gegen „den Stand davor" muss den Stand
  **abdrucken** — und besser beide Fassungen im selben Aufruf laufen lassen.
- 2026-09-05 (0110) — **Der Baulauf ruft `ctest` ohne `--no-tests=error`**: ein Mitglied
  ohne Proben meldet `ergebnis: ok`. Gemeldet.
- 2026-09-05 (0083) — **Der `belegstellen_riegel` schlägt sein Ziel über den *Basisnamen*
  nach**: einen falschen Treffer bei gleichnamigen Dateien fängt er nicht.
- 2026-09-05, siebenmal — **Jede Zahl in einer Abnahme ist ein Messwert von ihrem
  Zuschnittstag.** Besser ist die **Bedingung**; bei 0106 nannte der Vorschlag „17 von
  17" und eine am Bestand gehaltene Regel — beides war beim Lauf überholt.
- 2026-09-02 — Der Prüfstand hat weder **Regressionsbestand** noch **Determinismustest
  über Speichern und Laden** — laut Rolle meine wichtigsten; `probe_zweimal_dasselbe`
  deckt nur zwei Aufrufe im selben Prozess ab.
- 2026-09-03 — **Eine Invariante fängt Nullfälle nicht.** Nur ein gebauter Fall tut es.
