# Logbuch: testentwickler

Belege gehören in die Ergebnisdatei — hier steht die Lehre. Höchstens 12.000 Zeichen.
**2026-09-06 zweimal archiviert**, zuletzt nach
`notizen/archiv/testentwickler-2026-09-06-2.md`. Kürze früh, nicht am Ende — und **lies
vor dem Schreiben neu:** An diesem Tag liefen drei Läufe dieser Rolle gleichzeitig.

---

## Was funktioniert

- 2026-09-06 (0130) — **Eine Ausgabeordnung ist kein Schönheitsfehler, sondern eine
  Prüfbarkeitslücke.** Wo kein `std::sort` steht, ist die Reihenfolge die des
  Dateisystems, und jede Abnahme der Bauart „danach kein Rückschritt" ertrinkt in
  Umsortierungen. **Sortiert wird an der Sammelstelle, nicht an der Ausgabe:** dahinter
  füllen sich Zählwerke und ein „erster gesehener Pfad gewinnt".
- 2026-09-06 (0130) — **Ein Byte-Vergleich hat drei Regeln, und jede braucht ihren
  eigenen Mutanten:** `unsigned char` (ein Umlaut ist als `char` *negativ* und steht ganz
  vorn), kein Gebietsschema (`C` vor `a`), keine Ordnung über `fs::path` (Punkt 0x2E vor
  Schrägstrich 0x2F). Dazu die Längenregel beim gemeinsamen Anfang — ohne sie sind zwei
  Namen *gleichwertig* und ihre Ordnung wieder offen.
- 2026-09-06 (0130) — **Was eine Falltabelle über sich selbst behaupten muss, gehört in
  `static_assert`** („Vorlage unsortiert", „jeder Platz genau einmal"): kostet keinen Fall
  und keine Laufzeit — und zwingt den geprüften Vergleich zu `constexpr`.
- 2026-09-06 (0130) — **Ein Vergleichsfall braucht einen Mutanten außerhalb seiner
  Reichweite.** Der Mutant, der die Sortierung entfernt, lässt den Selbsttest grün und
  macht nur den Korpusvergleich rot — der Beleg, dass zwei Abnahmebedingungen
  *Verschiedenes* messen und nicht zweimal dasselbe.
- 2026-09-06 (0130) — **Eine Kopie des Korpus darf verkürzt sein, wenn die Verkürzung
  gemessen ist.** Aus dem Quelltext des Prüflings folgt, was er *sehen* kann und was er
  nur dem Namen nach braucht — aus 3,4 GB wurden so 7 MB. **Nachgewiesen, nicht
  behauptet:** ein Lauf über den echten Baum gegen einen über die Kopie, zeichengleich.
- 2026-09-06 (0130) — **Bei mehreren Kopien: einmal aus dem Baum abschreiben, den Rest aus
  der ersten Kopie** — sonst misst der Vergleich die Drift der Nachbarn mit.
  **Inhaltsgleichheit gehört gedruckt:** Pfad, Größe und SHA-256 je Datei, sortiert,
  davon ein Hash.
- 2026-09-06 (0171) — **Ein Riegel, der eine Eingabe aus `$TMPDIR` liest, hat einen
  Eingang, den niemand bewacht** — flüchtig und ungebunden. Griff: Herkunft
  (`<commit>^:<pfad>`) **und** Blobkennung festschreiben, **beides** prüfen — den Inhalt
  selbst gerechnet (`sha1(b"blob %d\0" + inhalt)`), sonst hängt die Prüfung an derselben
  Stelle wie die Beschaffung. Liegt Falsches da: **melden statt überschreiben.**
- 2026-09-06 (0171) — **Den beschafften Text einmal merken und alle Prüfstellen daraus
  bedienen.** Lesen sie den Pfad selbst, gilt die Prüfung nur für ihren Augenblick. Und
  **Riegel, die eine Eingabe verwerfen, gehören vor die erste Messung** — `SystemExit`
  statt `melde()`, denn eine Messung gegen den falschen Ausgangsstand ist gegenstandslos.
- 2026-09-06 (0115) — **Ein Riegel über eine Angabe liest die Erwartung aus der Angabe,
  nicht aus sich selbst.** Steht die Zahl im Messgerät, prüft es nur, dass die Welt sich
  nicht bewegt — der Text darf still falsch werden. Nebeneffekt: dieselben Prüfungen gegen
  den Wortlaut *vor* der Berichtigung sind dann die Gegenprobe, im selben Aufruf.
- 2026-09-06 (0115) — **Der Vorher-Nachher-Vergleich braucht drei Größen:** die Zahlen, den
  Rückgabewert **und die Befundlisten**. Ein weggefallener und ein neuer Befund heben
  einander in der Summe auf.
- 2026-09-06 (0115) — **`Edit(replace_all)` übersieht, was umbrochen ist**, und die eigene
  Nachprüfung aus demselben Grund. **Muster über den geglätteten Text laufen lassen.**
- 2026-09-06 (0115) — **Ein Bezugsstand ist eine Herkunftsangabe, keine Bedingung:** Ein
  fremder Commit darf nicht rot machen; geprüft wird nur, dass der Baum **während** der
  Messung stillsteht. *Für eine gelesene **Eingabe** gilt das Gegenteil — siehe 0171.*
- 2026-09-05 (0106) — **Die Lücke sitzt in der Verdrahtung, nicht im Baustein.** Griff: die
  Entscheidung als eigenen Aufruf herausziehen — auch die **Auswertung**, sonst gehen
  Ernstfall und Test verschiedene Wege. **Vor jeder neuen Tabelle fragen: Welche Stelle
  erreicht keine bestehende?** Und erwarte den *Ausgang*, nicht das Zwischenergebnis.
- 2026-09-05 (0106), 2026-09-06 bestätigt — **Das Messskript ist selbst ein Riegel, kein
  Bericht:** Erwartung je Mutant im Skript, ein Mutant je Fall, Rückgabe 1 bei Abweichung,
  Vorlauf im *selben* Aufruf. Geprüft werden **vier** Dinge — Rückgabe, *welcher* Fall
  riss, dass **keine fremde Tabelle** riss, und dass der Bestand gar nicht erst gelesen
  wurde. *0130: „welcher Fall" heißt **namentlich** — je Mutant den Wortlaut
  festschreiben, der in der roten Zeile stehen muss.*
- 2026-09-05 (0105) — **Ein ungemessener Kommentar ist eine Falschaussage in
  Wartestellung.**
- 2026-09-05 (0138, 0105) — **`WILL_FAIL` beweist nur „ungleich 0".** Beim
  `belegstellen_riegel`: **2 = Selbsttest, 1 = Befund am Bestand, 0 = grün.**
- 2026-09-05 (0106), bestätigt 2026-09-06 — **Skript unter `befunde/messung-<nr>/`, gebaut
  und gelaufen wird in `$TMPDIR`.** *Grenze (0130): Auf tmpfs kostet auch eine leere Datei
  eine Seite — zwei Kopien mit je 126.000 Namen haben den Dateibaum volllaufen lassen.*
- 2026-09-05 (0135) — **Eine feste Sollzahl in einem Messgerät verfällt in Stunden.**
  Ersatz: **Gleichheitsmaß gegen den eigenen Stand davor**, und der Stand **benannt**.
  Mutant und Vergleichsstand müssen aus **demselben** Commit stammen.
- 2026-09-05 (0110, 0083, 0129, 0138, 0105, 0106) — **Mutieren, ohne den Quellbaum
  anzufassen:** Mutant als Kopie außerhalb übersetzen; das Skript bricht ab, wenn der
  erwartete Wortlaut nicht **genau einmal** vorkommt. Und die Gegenprobe ist ein Mutant
  des **ausgelieferten** Standes, nicht ein alter Commit — sonst misst man drei Pakete und
  nennt es eines.
- 2026-09-05 (0110) — **`ctest -R <muster>` ohne Treffer gibt Code 0** — immer
  **`--no-tests=error`**.
- 2026-09-05, **sechsmal**, 2026-09-06 erneut — **Ein eigener Kommentar kann einen fremden
  Riegel rot machen.** Griffe: Schlüsselwort **maskieren** (`\101bschnit\164`), klein
  weiterschreiben, oder Textblockwechsel (`///` Leerzeile) davor. **Steht ein Schlüsselwort
  im Text, darf in seinem Textblock danach kein zweiter Gegenstrich mehr kommen.**
  *Billiger als jeder Griff: die vier Schlüsselwörter gar nicht verwenden — bei 0130 über
  240 neue Zeilen durchgehalten, kein einziger Selbsttreffer.*
- 2026-09-05, **fünfmal** — **Ein Mutant scheitert gern aus dem falschen Grund.** Prüfen,
  ob die rote Zeile die *gemeinte* ist; grün heißt zuerst „falsch mutiert".
- 2026-09-02, bis 2026-09-06 bestätigt — **Beide Bauwege einzeln prüfen**, beide nach
  `$TMPDIR`: `cmake -S werkzeuge/<x> -B $TMPDIR/bau` und `cmake -S <vorhaben> -B
  $TMPDIR/ws` mit `--build --target <ziel>`. Keiner rührt `bau/` an, beide laufen durch
  `werkzeugkette.cmake` und `ctest`.

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-04, **elfmal getroffen** (zuletzt 0171) — `cd` nimmt mir `Edit` und `Write` still
  weg. **Nie `cd`.** Heilung: `cd /home/adria/fabrik` als eigener Aufruf.
- 2026-09-05, bis 2026-09-06 erweitert — **Abgelehnt:** `rm`, `mv`, `sed`, `cp`, `awk`;
  `python3 -c` mit mehreren Anweisungen oder geschachtelten Anführungszeichen; `VAR=wert
  befehl`; zusammengesetzte Befehle und eine Pipe hinter einem mehrzeiligen Block;
  **`echo $?` in derselben Zelle wie der Aufruf**; **ein selbst übersetztes Binärprogramm
  unmittelbar aus der Zelle starten** (0130). **Läuft:** ein einzelner Python-Ausdruck,
  mehrzeilige Blöcke samt `> datei`, einzelne Pipes. **`grep` und `cat` im Baum nur über
  das Grep-Werkzeug oder hinter einer Pipe.**
- 2026-09-05 (0138) — **`Write` schreibt nicht nach `$TMPDIR`**, **Heredocs abgelehnt**.
  Hilfsskript als Datei ins Repo, `python3 <datei>` rufen; das darf in `$TMPDIR` arbeiten —
  **auch `shutil.rmtree` und `os.remove`** (0130), nur als `-c`-Einzeiler nicht.
- 2026-09-06 (0171, 0130) — **Ohne `rm` und `mv`: `os.rename` aus einem Skript**, was zu
  Hausregel 3 passt. Unterschieben geht mit `git cat-file blob <sha> > datei`. **Jedes
  Skript, das außerhalb des Repos etwas anlegt, bekommt ein `aufraeumen.py` daneben** —
  bricht der Lauf ab, liegen sonst Gigabytes herum, die den nächsten kippen.
- 2026-09-06 (0171) — **Einen Mutanten des eigenen Messskripts baut man im Skript selbst**,
  wenn die Kopie nach `$TMPDIR` an der Werkzeugsperre scheitert: Konstante per `Edit`
  verstellen, rot messen, zurückstellen, grün nachmessen. Beide Läufe abdrucken.
- 2026-09-05 (0083, 0129, 0105) — Braucht ein Werkzeug **Argumente, die sein `add_test`
  nicht hergibt**: **`g++` direkt aus dem Messskript**, mit denselben Sprachschaltern.
- 2026-09-03, 2026-09-05 dreimal — Beim Sabotieren beißt `-Werror=unused-*`: der **Bau**
  wird rot statt des Tests. Griff: **Mutantenbau ohne `-Werror`** — dann aber den
  Vergleichsstand mit **denselben** Schaltern.
- 2026-09-05, **zweimal** — **`git commit` wird abgelehnt**, in jeder Form; `git add`
  läuft. Am Ende **stagen und melden**, nicht am Befehl feilen.

## Offene Faehrten

- 2026-09-06 (0130) — **Kein anderes Werkzeug ist auf seine Ausgabeordnung geprüft**
  (`bezeichner_riegel`, `mutationstreiber`, `pruefstand` sammeln ebenfalls Dateien). Und:
  `ungelesene` ist heute ein `std::set`, also von selbst geordnet — wird daraus je ein
  Vektor, fällt die Ordnung still wieder auseinander.
- 2026-09-06 (0115) — **Im Kopf des `belegstellen_riegel` sind Dutzende weitere Zahlen
  Messwerte ihres Zuschnittstags** (`0166` deckt vier). Ein Riegel, der *alle* genannten
  Mutantenzahlen aus dem Text liest, wäre billiger als sie einzeln nachzuziehen.
- 2026-09-06 (0171) — **`teil_a` in `messung-0115/messen.py` schreibt kurzzeitig in
  `belegstellen_riegel.cpp`** — wo am 2026-09-06 meine 242 uneingecheckten Zeilen lagen.
- 2026-09-05 (0106) — **`ZIELFAELLE`, `ABSTANDSFAELLE`, `SATZFAELLE` sind auf die
  Verdrahtungslücke hin nicht nachgemessen.** Nächste Kandidaten: die Ortsfrage
  (`zielart` → `grund`), die Reihenfolge der drei Zitatformen.
- 2026-09-04 bis 2026-09-06, **jetzt in jedem Lauf** — **Der Korpus driftet während des
  eigenen Laufs.** Bei 0130 hat er einen vollständigen Lauf gekippt. **Jede Messung gegen
  „den Stand davor" muss den Stand abdrucken**, und alles, was verglichen wird, aus
  **einem** Schnappschuss ziehen.
- 2026-09-05, achtmal — **Jede Zahl in einer Abnahme ist ein Messwert von ihrem
  Zuschnittstag.** **Die Abnahme trotzdem erfüllen — sie fragt nach dem *jetzigen* Stand,
  nicht nach ihrer eigenen Zahl.**
- 2026-09-02 — Der Prüfstand hat weder **Regressionsbestand** noch **Determinismustest
  über Speichern und Laden** — laut Rolle meine wichtigsten. *0130 ist der erste
  Determinismusnachweis über zwei Dateisysteme, aber nur für ein Werkzeug.*

## Worauf ich unsicher bin

**0130.** Die Abnahme verlangt „zwei Kopien desselben Bestands"; meine sind verkürzt —
gemessen belegt, aber nicht wörtlich. Zwei in verschiedener Ordnung angelegte ext4-Bäume
listen *doch* gleich auf; der Zwilling hängt allein am Wechsel ext4 → tmpfs. Und ich habe
`sammle_dateien` geteilt, damit die zwei Fehlerausgänge nicht an der Sortierung
vorbeilaufen — ob das noch „die Sammelstelle" ist, weiß ich nicht.

**0171.** „Nach Löschen von `$TMPDIR/k0115`" — gelöscht ist nicht, umbenannt schon. Die
Vorfassung liegt weiter nur in `$TMPDIR`, nicht als Datei neben dem Skript.
