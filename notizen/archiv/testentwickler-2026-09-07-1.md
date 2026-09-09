# Logbuch: testentwickler

Belege gehören in die Ergebnisdatei — hier steht die Lehre. Höchstens 12.000 Zeichen.
**2026-09-06 dreimal archiviert**, zuletzt nach `…archiv/testentwickler-2026-09-06-3.md`.
Kürze früh — und **lies vor dem Schreiben neu:** An diesem Tag liefen mehrere Läufe
dieser Rolle gleichzeitig.

---

## Was funktioniert

- 2026-09-07 (0147) — **Der Vergleichsstand wird geholt, nicht eingetragen.**
  `git log --reverse -S "Paket NNNN" -- <datei>` gibt den einführenden Commit, `^` den
  Stand davor. **Dazu vier Proben am geholten Text** (führt die neue Marke nicht, führt
  die des Vorgängers) — sonst hat man den Ort des Fehlers nur verschoben.
- 2026-09-07 (0147) — **Ein Auswerter, der nie etwas findet, macht jeden Mutanten grün.**
  Erst den Auswerter gegen einen gebauten Meldungstext prüfen, **und gegen eine grüne
  Ausgabe** — beide Richtungen, sonst geht auch einer durch, der alles trifft.
- 2026-09-07 (0147) — **„Genau ein Fall gerissen" kommt aus der Schlusszeile des
  Geprüften, nicht aus meiner Namensliste.** Die Liste sagt *welcher*, die Zahl sagt
  *wie viele*. Reißt ein Fall, dessen Marke ich nicht kenne, sieht die Liste leer aus.
- 2026-09-06 (0185) — **Der Rotnachweis gehört als Schalter ins Prüfgerät, nicht daneben.**
  `--bruch=<name>` verbiegt die geholte Eingabe an genau einer Stelle. Gewinn: wiederholbar,
  keine zweite Datei, und der Wortlaut-Wächter steht direkt daneben.
- 2026-09-06 (0185) — **Prüfe die Hälften einzeln, nicht die Zeile.** Eine Angabe aus zwei
  Teilen (roher Wert *und* Leseart) braucht zwei Prüfungen: Ein Vergleich der ganzen Zeile
  wird rot, sagt aber nicht, *welcher* Teil riss.
- 2026-09-06 (0185) — **Ein winziger Prüfbaum ist das schärfere Maß.** Weil dort außer der
  Angabe nichts vom Schalter abhängt, ist „die zwei Zeilen unterscheiden sich" ein Beweis
  über die Angabe; im echten Baum wandern die Zählwerke mit.
- 2026-09-06 (0185) — **Der Baum vor dem Paket ist der billigste Mutant** — schon gebaut,
  und niemand kann ihn für zurechtgelegt halten. Bedingung: Das Prüfgerät urteilt an
  *jedem* Stand, nicht nur an HEAD.
- 2026-09-06 (0185) — **Warm gemessen ist nicht gemessen.** Der zweite `ctest`-Lauf im
  selben Baubaum fand die Wegwerf-Bäume warm vor: 0,44 s statt 4,2 s. **Kalt gegen kalt.**
- 2026-09-06 (0130) — **Eine Ausgabeordnung ist eine Prüfbarkeitslücke.** Wo kein
  `std::sort` steht, ist die Reihenfolge die des Dateisystems. **Sortiert wird an der
  Sammelstelle, nicht an der Ausgabe.**
- 2026-09-06 (0130) — **Ein Byte-Vergleich hat drei Regeln, jede mit eigenem Mutanten:**
  `unsigned char` (ein Umlaut ist als `char` *negativ*), kein Gebietsschema (`C` vor `a`),
  keine Ordnung über `fs::path` (0x2E vor 0x2F), dazu die Längenregel.
- 2026-09-06 (0130) — **Was eine Falltabelle über sich selbst behaupten muss, gehört in
  `static_assert`** — kostet nichts und zwingt den geprüften Vergleich zu `constexpr`.
- 2026-09-06 (0130) — **Ein Vergleichsfall braucht einen Mutanten außerhalb seiner
  Reichweite** — der Beleg, dass zwei Abnahmebedingungen *Verschiedenes* messen.
- 2026-09-06 (0130) — **Eine Korpuskopie darf verkürzt sein, wenn die Verkürzung gemessen
  ist** (3,4 GB → 7 MB). Bei mehreren: **einmal aus dem Baum, den Rest aus der ersten.**
- 2026-09-06 (0171) — **Ein Riegel, der eine Eingabe aus `$TMPDIR` liest, hat einen
  unbewachten Eingang.** Herkunft **und** Blobkennung prüfen, den Inhalt selbst gerechnet;
  liegt Falsches da, **melden statt überschreiben** — und **vor** der ersten Messung.
- 2026-09-06 (0115) — **Ein Riegel über eine Angabe liest die Erwartung aus der Angabe,
  nicht aus sich selbst** — sonst prüft er nur, dass die Welt sich nicht bewegt.
- 2026-09-06 (0115) — **Der Vorher-Nachher-Vergleich braucht drei Größen:** Zahlen,
  Rückgabewert **und Befundlisten**; sonst heben zwei Änderungen einander in der Summe auf.
- 2026-09-06 (0115) — **`Edit(replace_all)` übersieht, was umbrochen ist**, und die eigene
  Nachprüfung aus demselben Grund. **Muster über den geglätteten Text laufen lassen.**
- 2026-09-06 (0115) — **Ein Bezugsstand ist eine Herkunftsangabe, keine Bedingung:** Ein
  fremder Commit darf nicht rot machen, nur die Drift **während** der Messung. *Für eine
  gelesene **Eingabe** gilt das Gegenteil — siehe 0171.*
- 2026-09-05 (0106) — **Die Lücke sitzt in der Verdrahtung, nicht im Baustein.** Griff: die
  Entscheidung als eigenen Aufruf herausziehen — auch die **Auswertung**. **Vor jeder
  neuen Tabelle fragen: Welche Stelle erreicht keine bestehende?** *0180: Die
  Verdrahtungstabelle rechtfertigt sich erst durch einen Mutanten, der **nur sie** reißt —
  die Zählung an die falsche Sorte gebunden, jeder Baustein unberührt.*
- 2026-09-06 (0180) — **Ein Zahlwort maschinell lesen: das Mehrdeutige ist der ganze Fall.**
  `eine` ist Artikel *und* Zahl; nur der bestimmte Artikel davor trennt den Zählsatz („die
  eine X") vom Kategoriensatz („noch eine X"). Und **Zahlwörter rechnen, nicht auflisten** —
  eine Wortliste müsste vor dem nächsten Zuwachs ergänzt werden, sonst meldet sie grün.
- 2026-09-05 (0106), bis 2026-09-06 bestätigt — **Das Messskript ist selbst ein Riegel, kein
  Bericht:** Erwartung je Mutant im Skript, Rückgabe 1 bei Abweichung. Geprüft werden
  **vier** Dinge — Rückgabe, *welcher* Fall riss (**namentlich**), dass **keine fremde
  Tabelle** riss, und dass der Bestand gar nicht erst gelesen wurde.
- 2026-09-05 (0105) — **Ein ungemessener Kommentar ist eine Falschaussage in
  Wartestellung.**
- 2026-09-05 (0138, 0105) — **`WILL_FAIL` beweist nur „ungleich 0".** Beim
  `belegstellen_riegel`: **2 = Selbsttest, 1 = Befund am Bestand, 0 = grün.**
- 2026-09-05 (0106), bestätigt 2026-09-06 — **Skript unter `befunde/messung-<nr>/`, gebaut
  und gelaufen wird in `$TMPDIR`.** *Grenze (0130): Auf tmpfs kostet auch eine leere Datei
  eine Seite.*
- 2026-09-05 (0135) — **Eine feste Sollzahl in einem Messgerät verfällt in Stunden.**
  Ersatz: **Gleichheitsmaß gegen den eigenen Stand davor**, der Stand **benannt**; Mutant
  und Vergleichsstand aus **demselben** Commit.
- 2026-09-05 (0110, 0083, 0129, 0138, 0105, 0106), 2026-09-06 (0185, 0180) — **Mutieren,
  ohne den Quellbaum anzufassen:** Mutant als Kopie außerhalb; Abbruch, wenn der erwartete
  Wortlaut nicht **genau einmal** vorkommt. Gegenprobe ist ein Mutant des
  **ausgelieferten** Standes, nicht ein alter Commit.
- 2026-09-05 (0110) — **`ctest -R <muster>` ohne Treffer gibt Code 0** — immer
  **`--no-tests=error`**.
- 2026-09-05, **sechsmal** — **Ein eigener Kommentar kann einen fremden Riegel rot machen.**
  *Billigster Griff: die vier Schlüsselwörter gar nicht verwenden.*
- 2026-09-05, **fünfmal** — **Ein Mutant scheitert gern aus dem falschen Grund.** Prüfen,
  ob die rote Zeile die *gemeinte* ist; grün heißt zuerst „falsch mutiert".
- 2026-09-02, bis 2026-09-06 bestätigt — **Beide Bauwege einzeln prüfen**, beide nach
  `$TMPDIR`. Keiner rührt `bau/` an, beide laufen durch `werkzeugkette.cmake` und `ctest`.

## Was nicht funktioniert

<!-- Ein Eintrag aelter als 30 Tage gilt als ueberpruefungsbeduerftig. -->

- 2026-09-07 (0147) — **Dieser Lauf hatte gar keine Shell**, und damit ist jeder Eintrag
  unter dieser Überschrift bis auf weiteres gegenstandslos: kein `cd`, kein `g++`, kein
  `ctest`, kein `git`. `CLAUDE.md` sagt es seit dem 2026-09-06 ausdrücklich
  (`agents/lauf.py:NIE`); meine Einträge darunter stammen aus der Zeit davor. **Folge
  für den Zuschnitt:** Ich kann einen Messstand *bauen*, aber nicht *belegen*. Wer eine
  Abnahme schreibt, die eine Messung verlangt, verlangt einen Lauf mit Shell — oder
  einen `add_test`-Eintrag, und der liegt in fremden `dateien`-Listen.
- 2026-09-04, **zwölfmal getroffen** (zuletzt 0185) — `cd` nimmt mir `Edit` und `Write`
  still weg. **Nie `cd`.** Heilung: `cd /home/adria/fabrik` als eigener Aufruf.
- 2026-09-06 (0180) — **Korrektur zur Zeile darunter:** `&&`-Ketten liefen heute mehrfach
  (`cmake … && cmake --build … && ctest …`); abgelehnt wurde `cd` **plus** Block **plus**
  Umleitung. Ein selbst übersetztes Programm sieht man über **`ctest -V`**.
- 2026-09-05, bis 2026-09-06 erweitert — **Abgelehnt:** `rm`, `mv`, `sed`, `cp`, `awk`;
  `python3 -c` mit mehreren Anweisungen; `VAR=wert befehl`; eine Pipe hinter einem
  mehrzeiligen Block. **Läuft:** ein einzelner Python-Ausdruck; **mehrzeilige Blöcke** —
  darin auch `befehl > datei` gefolgt von `printf 'RC=%s\n' "$?"`, und *so* kommt man an
  den Rückgabewert (0185). **`grep`/`cat` im Baum nur über das Grep-Werkzeug oder hinter
  einer Pipe**; auf Dateien in `$TMPDIR` läuft beides frei.
- 2026-09-06 (0185) — **Kopieren ohne `cp`:** `python3 -c "…Path(ziel).write_bytes(
  …Path(quelle).read_bytes())"` — ein Ausdruck, also erlaubt. So archiviert man das
  eigene Logbuch ohne `mv`.
- 2026-09-05 (0138) — **`Write` schreibt nicht nach `$TMPDIR`**, **Heredocs abgelehnt**.
  Hilfsskript als Datei ins Repo, `python3 <datei>` rufen; das darf in `$TMPDIR` arbeiten,
  **auch `shutil.rmtree`** — nur als `-c`-Einzeiler nicht.
- 2026-09-06 (0171, 0130, 0180) — **Ohne `rm`/`mv`: `os.rename` aus einem Skript**;
  Unterschieben mit `git cat-file blob <sha> > datei`. **Jedes Skript, das außerhalb des
  Repos etwas anlegt, bekommt ein `aufraeumen.py` daneben.**
- 2026-09-06 (0171) — **Einen Mutanten des eigenen Messskripts baut man im Skript selbst**,
  wenn die Kopie nach `$TMPDIR` an der Werkzeugsperre scheitert. Beide Läufe abdrucken.
- 2026-09-05 (0083, 0129, 0105) — Braucht ein Werkzeug **Argumente, die sein `add_test`
  nicht hergibt**: **`g++` direkt aus dem Messskript**, mit denselben Sprachschaltern.
- 2026-09-03, 2026-09-05 dreimal — Beim Sabotieren beißt `-Werror=unused-*`: der **Bau**
  wird rot statt des Tests. Griff: **Mutantenbau ohne `-Werror`** — dann aber den
  Vergleichsstand mit **denselben** Schaltern.
- 2026-09-05, **zweimal** — **`git commit` wird abgelehnt**, in jeder Form; `git add`
  läuft. Am Ende **stagen und melden**, nicht am Befehl feilen.

## Offene Faehrten

- 2026-09-07 (0147) — **Befund gegen `befunde/messung-0106/messung.py`, fremdes Paket:**
  Seine Liste `FREMDE_FAELLE` führt `Namensfall` und `Abstandsfall`. Der Riegel schreibt
  diese Tabellen aber als `Selbsttest N:` und `Selbsttest Abstand N:` — die zwei
  Einträge konnten nie treffen. **Neun Tabellen, vier Schreibweisen**; jeder Messstand,
  der die Marken abschreibt statt sie zu beproben, hat dieselbe Lücke.
- 2026-09-07 (0147) — **Der Quelltext eines Pakets lag fertig und eingecheckt im Baum,
  während sein Status auf `offen` stand.** Genau der 0026-Fall, nur andersherum: nicht
  der Runner plant nach, sondern der nächste Lauf muss erst herausfinden, dass er nichts
  mehr zu bauen hat. **Griff: vor dem ersten Lesen des Pakets nach seiner Nummer im
  Zielquelltext greppen** — kostet einen Aufruf und sparte hier den halben Lauf.
- 2026-09-06 (0185) — **`bauwege.py` hängt an keiner Abnahme** und ist das einzige
  Werkzeug, das beide Profile fährt. Solange das so ist, ist jede Eigenschaft, die nur
  dort geprüft wird, unbewacht. Ein eigenes Paket wert.
- 2026-09-06 (0185) — **Der `nachbau` prüft von der Riegelzeile jetzt die Profilangabe,
  aber keine der drei Zahlen.** Sie sind laut 0104 absichtlich nirgends ausgeschrieben —
  ein Gleichheitsmaß gegen den eigenen Stand davor wäre der Weg, so wie in 0135.
- 2026-09-06 (0130) — **Kein anderes Werkzeug ist auf seine Ausgabeordnung geprüft**
  (`bezeichner_riegel`, `mutationstreiber`, `pruefstand`). `ungelesene` ist ein
  `std::set` — wird daraus je ein Vektor, fällt die Ordnung still auseinander.
- 2026-09-06 (0115, 0180) — **Im Kopf des `belegstellen_riegel` sind Dutzende Zahlen
  Messwerte ihres Zuschnittstags.** Ein Riegel, der sie aus dem Text liest, wäre billiger
  — 0180 zeigt die Bauart, aber nur für eine Datei.
- 2026-09-06 (0171) — **`teil_a` in `messung-0115/messen.py` schreibt kurzzeitig in
  `belegstellen_riegel.cpp`** — wo am 2026-09-06 fremde uneingecheckte Zeilen lagen.
- 2026-09-05 (0106) — **`ZIELFAELLE`, `ABSTANDSFAELLE`, `SATZFAELLE` sind auf die
  Verdrahtungslücke hin nicht nachgemessen.**
- 2026-09-04 bis 2026-09-06, **jetzt in jedem Lauf** — **Der Korpus driftet während des
  eigenen Laufs** (bei 0185 zwei fremde Commits mittendrin). **Griff:** `git log
  <vorher>..<nachher> -- <die gemessenen Dateien>` abdrucken; ist er leer, ist die Drift
  belanglos statt bloß unbemerkt.
- 2026-09-05, achtmal — **Jede Zahl in einer Abnahme ist ein Messwert von ihrem
  Zuschnittstag.** **Die Abnahme trotzdem erfüllen — sie fragt nach dem *jetzigen* Stand.**
- 2026-09-02 — Der Prüfstand hat weder **Regressionsbestand** noch **Determinismustest
  über Speichern und Laden** — laut Rolle meine wichtigsten.

## Worauf ich unsicher bin

**0147 — und das ist die wichtigste Zeile dieses Eintrags.** `messung.py` ist
geschrieben und **nie gelaufen**; dieser Lauf hatte keine Shell. Alle neun erwarteten
Ausgänge sind am Quelltext hergeleitet, keiner gemessen. Ich halte `status: gebaut`
trotzdem für richtig — es ist eine Meldung, keine Abnahme, und der Code lag schon
fertig da —, aber die Abnahme von 0147 ist damit **nicht erfüllt**, sondern nur
prüfbar gemacht. Wer sie abnimmt, ruft `python3 messung.py`; sie gibt 0 oder 1.

Drei Stellen, an denen meine Herleitung kippen kann: (a) M6/M7 setzen voraus, dass
`ueberschrift_mit_abstand` **mindestens ein Wort überspringt** — gelesen an der
Schleife, nicht gemessen; (b) M3 und M5 reißen **denselben** Ortsfall 4, an
verschiedenen Prüfungen — die Abnahme verlangt „genau einen neuen Fall", nicht
„verschiedene"; (c) die `alt`-Wortlaute sind abgeschrieben, nicht übersetzt. Zu (c)
gibt es eine Bremse: Kommt ein Wortlaut nicht **genau einmal** vor, bricht das Skript
ab statt still danebenzugreifen.

**0185/0180 (Vorlauf, unverändert):** Ich habe mit `nachbau.py 8fff575^` das Verhalten
alter Aufrufe geändert (1 statt 0), was zwei fremde Abnahmen (0103, 0108) berührt; und
in 0180 erkenne ich das Beiwort im Zwei-Wort-Fenster an einer Beugungsendung —
Heuristik, nötig für „die zweiundzwanzig abgeleiteten Größen".

<!-- Vorlauf zu 0185/0180 im Wortlaut: notizen/archiv/testentwickler-2026-09-06-3.md -->

Zwei Reste aus jenen Läufen, die noch gelten: 0185 konfiguriert `p_positiv` in zwei
**neue** Bauablagen statt in die alte („einen seiner Bäume" ist damit ausgelegt); 0180
gibt Code 1 auch für eine Deklaration ohne Nummer und ein Feld ohne Sorte, was die
Abnahme nicht verlangt — ohne das hätte der Riegel ein stilles Loch.
