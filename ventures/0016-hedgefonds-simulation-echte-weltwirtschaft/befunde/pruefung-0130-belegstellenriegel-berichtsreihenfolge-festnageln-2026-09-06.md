---
typ: pruefung
paket: 0130-belegstellenriegel-berichtsreihenfolge-festnageln
pruefer: test-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Beide Abnahmebedingungen unabhaengig nachgemessen -- zeichengleiche Ausgabe zweier eigener, inhaltsgleicher Bestandskopien auf ext4 und tmpfs samt rotem Zwilling der Vorfassung, und der neue Selbsttestfall mit vier eigenen Mutanten (drei Laufzeit, einer Uebersetzungszeit) rot gemacht.
befunde: 0
---

# Pruefung 0130: Berichtsreihenfolge des Belegstellenriegels

**Gegenstand.** Commit `751d01c` (2026-09-06), einzige Paketdatei
`werkzeuge/belegstellen/belegstellen_riegel.cpp` (+242/-10); daneben nur die
Paketdatei selbst und das Logbuch des Bauers -- die `dateien`-Liste ist eingehalten.
Der Arbeitsbaum traegt keinen Diff gegen HEAD auf der Datei. Die Vorfassung dieser
Pruefung ist `751d01c^` (= Blob `14eda9f`); der im Nachweis des Bauers genannte
Messstand `8903184` traegt **denselben** Blob, beide Messungen reden also ueber
dieselbe Vorfassung.

**Eigener Bau.** Alleinbau `cmake -S werkzeuge/belegstellen`, RelWithDebInfo,
g++ 15.2.0, CMake 4.2.3, Werkzeugkette ueber den `PROJECT_IS_TOP_LEVEL`-Block
(Warnsatz-Schlussriegel: 1 Ziel, 19 Schaltereintraege, `FABRIK_SANITIZER=ON`).
Vorfassung identisch gebaut aus einer Quellkopie mit `werkzeugkette.cmake` zwei
Ebenen hoeher. `ctest --no-tests=error` am eigenen Bau: 1/1 bestanden (7,1 s,
Lauf ueber den echten Arbeitsbaum). Der Arbeitsbereichsbau des Runners vom selben
Tag (`befunde/uebersetzung-2026-09-06.md`) meldet `ergebnis: ok` und fuehrt
`belegstellen_riegel` auf beiden Bauwegen als bestanden.

## Bedingung 1: zeichengleich ueber Dateisysteme, Zwilling rot

**Eigene Kopien, eigener Herstellungsweg** (unabhaengig vom Weg des Bauers):
`git archive HEAD` des Vorhabens und von `specs/`, entpackt nach
`bau/pruefer-0130/kopie-a` (ext4) und `$TMPDIR/pruefer-0130/kopie-b` (tmpfs),
je im Aufbau `<basis>/ventures/<id>/` + `<basis>/specs/<id>/`, damit die
Vorgabenwurzel wie im Betrieb abgeleitet wird. Inhaltsgleichheit nachgewiesen:
ordnungsunabhaengiger Fingerabdruck (sortierte SHA-256-Liste ueber alle Dateien)
`4c57e8f8bcba8f79...` auf **beiden** Kopien, je 2.863 Dateien.

| Lauf | stdout | stderr | Rueckgabe |
|---|---|---|---|
| neu ueber A (ext4) gegen neu ueber B (tmpfs) | **zeichengleich** (7.229 B) | zeichengleich (0 B) | 0 / 0 |
| alt ueber A gegen alt ueber B | **verschieden**: 95 von 124 Zeilen | zeichengleich (0 B) | 0 / 0 |

Erste Abweichung der Vorfassung: Zeile 18, `daten/adressen.md:637` gegen
`daten/reihen.toml:11` -- dasselbe Zeilenpaar, das der Beleg des Bauers nennt,
auf einem anders hergestellten Bestand. Der Zwilling haelt: Der Unterschied
existiert auf der Vorfassung und verschwindet mit der Aenderung, also misst der
gruene Vergleich die Ursache.

**Kein Erkennungsverhalten geaendert**, nachgemessen statt geglaubt: Die
Zeilen-Multimengen der Ausgaben von alt und neu ueber dieselbe Kopie sind --
ausser der laengeren Selbsttest-Kopfmeldung -- **identisch** (0 Zeilen nur in
neu, 0 nur in alt); es aendert sich allein die Ordnung. Rueckgabewert beidseitig 0.
Beide Wurzeln laufen durch die sortierende Fassung: `sammle_dateien` wird in
`main` fuer die Vorhabenwurzel (Zeile 3703) und die Vorgabenwurzel (Zeile 3710)
gerufen.

## Bedingung 2: der Fall im Selbsttest, rot gemacht mit eigenen Mutanten

Die Kopfmeldung des Riegels nennt die neue Tabelle und ihre Zahl: `... und 8 zur
Ausgabeordnung, alle wie erwartet` (gesamt 65 Faelle statt vorher 57; die
Vorfassung druckt die Kategorie nicht). Vier **eigene** Mutanten, jeder am
ausgelieferten Stand, jede Ersetzung mit Trefferbremse (genau 1 Fundstelle):

| Mutant (eigene Wahl) | Ausgang | reisst an |
|---|---|---|
| Bytevergleich umgedreht (`return r < l`) | Code 2 | allen 8 Ordnungsfaellen, keiner fremden Tabelle |
| `ordne_kurznamen` wirkungslos (`if (false) std::sort` im Selbsttestweg) | Code 2 | 5 Ordnungsfaellen -- die absichtlich unsortierte Vorlage traegt |
| Sortierung an der Sammelstelle wirkungslos (`if (false) std::sort` in `sammle_dateien`) | Code 0, Selbsttest gruen | **keinem Fall** -- dafuer A gegen B wieder verschieden |
| `ORDNUNGSFAELLE` nach Platz sortiert hingeschrieben | Bau bricht ab | `static_assert(ordnungsvorlage_ist_ungeordnet(), ...)`, Zeile 1378 |

Der vierte belegt, dass die Uebersetzungszeit-Sperre gegen eine schon sortierte
Vorlage wirklich feuert; der dritte bestaetigt unabhaengig, was der Bauer selbst
offengelegt hat: Die Sammelstellen-Sortierung sieht kein Fall der Tabelle, sie
wird allein vom Dateisystemvergleich der Bedingung 1 gefangen. Meine Kippmengen
decken sich mit denen des Nachweises (dort mit anderen Ersetzungen: alle 8 /
2 / 2 / keiner) -- die Zahlen haengen an der Eigenschaft, nicht am Messgeraet.

## Wonach ich sonst gesucht habe

Abgeschwaechte Tests: Der Diff enthaelt nur Zufuegungen; keine Schwelle gesenkt,
keine Zusicherung entfernt, alle sechs alten Falltabellen unangetastet (die
Multimengen-Gleichheit oben deckt auch die Berichtsinhalte). Fremder Nachweis
(`befunde/messung-0130/lauf-2026-09-06.txt`, `messen.py`) erst **nach** der
eigenen Messung gegengelesen: konsistent, Herstellungsweg der drei Kopien im
Skript nachvollziehbar, Messkopien am Repo-Wurzelrand (`.messung-0130-ext4*`)
aufgeraeumt. Eigene Baubaeume und Kopien nach der Messung entfernt; Protokolle
liegen unter `werkzeuge/belegstellen/bau/pruefer-0130/`.

**Nebenbemerkung, kein Mangel an 0130:** Die Sammelstellen-Sortierung hat nach
der Abnahme keinen **dauerhaft** mitlaufenden Rotnachweis -- der Mutant dazu
bleibt am Selbsttest gruen, und der Dateisystemvergleich war eine einmalige
Messung. Dieselbe Familie wie beim Bezeichnerriegel (0129 -> 0138). Vorschlag
dazu: `aufgaben/0182-sammelstellen-sortierung-dauerhaft-gedeckt.md`.
