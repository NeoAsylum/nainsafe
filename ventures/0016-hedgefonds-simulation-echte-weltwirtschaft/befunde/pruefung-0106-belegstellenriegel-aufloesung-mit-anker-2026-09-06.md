---
typ: pruefung
paket: 0106-belegstellenriegel-aufloesung-mit-anker
pruefer: test-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Sieben eigene Mutanten auf Kopien gebaut, jeder stirbt mit Code 2 am Selbsttest ohne Bestandslesen; alt/neu am heutigen Baum zeichengleiche Zahlenzeile; derselbe fatale Mutant rutscht auf der Vorfassung mit Code 0 durch.
befunde: 0
---

# Pruefung 0106: Aufloesungsschritt mit Anker

**Gegenstand:** Commit `e34ab659` (Betreff „kernbauer: 0144…" — der Runner buendelt;
die Dateiliste des Commits traegt fuer 0106 genau `belegstellen_riegel.cpp`,
`befunde/messung-0106/` und die Paketdatei, deckungsgleich mit `dateien`).
**Bezugsstand:** Der im Paket genannte `5605c54` ist blobgleich mit dem Elternstand
von `e34ab659` auf dieser Datei (nachgeprueft mit `git show <rev>:<pfad>` und `diff`);
die Angabe ist inhaltlich korrekt, auch wenn der letzte Commit, der die Datei selbst
anfasste, `4bbd069` heisst.

**Messstand:** eigener Quellbaum unter `bau/test-pruefer-0106/` (Arbeitsbaum-Fassung
== HEAD, nachgeprueft), uebersetzt wie der Runner (`cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo
-DCMAKE_CXX_FLAGS="-fwrapv -fno-fast-math"`, Werkzeugkette per `PROJECT_IS_TOP_LEVEL`).
Aufruf je `belegstellen_riegel <venture-wurzel>`. Alle Mutanten sind **eigene**
Textersetzungen mit Trefferbremse (Nadel genau 1x), nicht die des Bauer-Nachweises;
das Protokoll `befunde/messung-0106/protokoll.txt` habe ich erst nach der eigenen
Messung gegengelesen.

## Abnahme, Punkt fuer Punkt

**1. `steht_da` durch Konstante ersetzt, beide Zweige, je einzeln → Code 2.**

| Mutant (eigene Ersetzung) | Rueckgabe | gerissen | Bestand gelesen |
|---|---|---|---|
| `urteil.steht_da = art == Namensart::Ueberschrift;` → `= true;` (Zweig ohne Anfuehrung) | 2 | Urteilsfall 2 | nein |
| dieselbe Zeile → `= false;` | 2 | Urteilsfall 1 | nein |
| `urteil.steht_da = liste[u] == gesucht;` → `= true;` (Zweig mit Anfuehrung) | 2 | Urteilsfall 4 | nein |
| dieselbe Zeile → `= false;` (Kuer, Fall 3) | 2 | Urteilsfall 3 | nein |

**2. Art *einzelnes Zeichen* entfaellt → Code 2**, in beiden Lesarten:
`} else if (art == Namensart::Einzelzeichen) {` → `} else if (false && …) {` in
`beurteile_zitat` (reisst Urteilsfall 5) und `return Namensart::Einzelzeichen;` →
`return Namensart::Ueberschrift;` in `namensart` (reisst ebenfalls Fall 5). Dazu als
Kuer *ohne Gliederung* neutralisiert → Fall 6 reisst. Damit ist **jeder der sechs
`URTEILSFAELLE` mindestens einmal rot gemessen** — keine Zusicherung der neuen
Tabelle blieb ohne roten Nachweis.

**3. „…bevor der Bestand gelesen wird":** Bei jedem Mutanten fehlt in stdout jede
`Bedingung 1/2`-Zeile („Bestand gelesen: nein" oben), und der Aufruf mit einem
**nicht existierenden Wurzelpfad** liefert dieselbe Rueckgabe 2 samt
Selbsttestmeldung — der Bestand wird fuer das Sterben nicht gebraucht. Im Quelltext
laeuft `selbsttest_urteil()` in `main` vor der Argumentauswertung
(`belegstellen_riegel.cpp:3364` ff.).

**4. Riegel bleibt gruen, dieselben Zahlen:** Alt- (`5605c54`) und Neufassung
nebeneinander uebersetzt und **unmittelbar nacheinander** ueber denselben Arbeitsbaum
(2026-09-06) gefahren: beide Rueckgabe 0, Zahlenzeile zeichengleich — *53 Bauquellen
und 13 Datendokumente, 215 Dateien im Zielbestand, 63597 Pfade in ungelesenen Ordnern,
40 Zitate, 40 aufgeloest (Untergrenze 16), 47 uebergangen*. Die Abweichung zu den
Zahlen des GEBAUT-Absatzes (208/46) und des Bauer-Protokolls (209/46) ist Korpusdrift
seit dem 2026-09-05 22:30, kein Widerspruch: massgeblich ist der zeitgleiche
alt/neu-Vergleich, und der ist bei beiden Messstaenden zeichengleich.

**5. Faelle steigen, keine Erwartung geaendert:** Selbsttest 51 → 57 (8/13/**6**/17/8/5);
die fuenf alten Tabellen melden unveraendert 8/13/17/8/5. Der Diff von `e34ab659` auf
die Datei loescht nur den verschobenen Urteilsblock, die beiden Summenzeilen in `main`
und drei Kopfkommentarzeilen — keine Fallzeile, keine Schwelle (Untergrenze 16 in
beiden Fassungen), keine Zusicherung.

## Die Gegenprobe, die das Paket traegt

Derselbe fatale Mutant (`steht_da = true` im Zweig ohne Anfuehrung) auf der
**Vorfassung** `5605c54`: Rueckgabe **0**, Bestand gelesen, 40 von 40 „aufgeloest" —
er rutscht durch alles durch. Auf der neuen Fassung stirbt er am Selbsttest, bevor
irgendetwas gelesen wird. Alt gruen + neu rot am selben Mutanten, in einem Lauf: Die
Luecke, um derentwillen das Paket existiert, war real und ist zu.

## Wonach ich sonst gesucht habe (ohne Befund)

* **Abgeschwaechte Tests:** keine gesenkte Schwelle, keine entfernte Zusicherung,
  kein uebersprungener Test im Diff.
* **Verhaltensgleichheit der Verschiebung:** `grund = urteil.grund`
  (`belegstellen_riegel.cpp:3314`) kann keinen frueher gesetzten Grund ueberschreiben —
  die Vorpruefungen (Netzadresse, Ziel ausserhalb, mehrdeutig, …) setzen `grund` in
  exklusiven `else if`-Zweigen, der Urteilsblock liegt im letzten `else`.
* **Nebenwirkung am Bestand:** Die Uebergangen-Liste des heutigen Laufs traegt keinen
  einzigen Fund mit dem Grund „einzelnes Zeichen" oder „Zieldatei fuehrt keine
  Ueberschrift" — die Behauptung des Pakets, diese Regeln haengen nur noch an den
  neuen Selbsttestfaellen, stimmt am 2026-09-06 weiterhin.

**Randnotizen ohne Befundstatus:** Der GEBAUT-Absatz zaehlt „34 geloeschte Zeilen",
`--numstat` zaehlt 37 — die drei weiteren sind Kopfkommentarzeilen, keine Erwartungen.
Und „5605c54, der letzte Commit auf der Datei" ist woertlich schief (s. o.), blobgleich
aber folgenlos.
