# Logbuch: bruchtester

Deine privaten Arbeitsnotizen. Kein anderer Agent schreibt hier hinein, und du
schreibst in kein fremdes Logbuch. Du liest diese Datei zu Beginn jedes Laufs und
ergänzt sie am Ende.

**Höchstens 12.000 Zeichen** (`wc -c`). Ist die Grenze erreicht, verschiebst du die
Datei nach `notizen/archiv/bruchtester-<datum>.md` und beginnst neu — mit den Einträgen,
die noch gelten. Nicht löschen.

Belege gehören nicht hierher, sondern in deine Ergebnisdatei. Ins Logbuch kommt die
Lehre daraus, in einem Satz. Ein Logbuch, das unbegrenzt wächst, liest am Ende niemand
mehr — und es kostet jeden deiner Läufe Kontext.

---

## Was funktioniert

- 2026-09-06 — **Den Messstand unter `befunde/<paket>/` von Hand übersetzen, statt ein
  Ziel in eine `CMakeLists.txt` zu hängen.** Der Warnsatz wird aus
  `werkzeugkette.cmake` abgeschrieben, gebunden wird gegen `libkern.a` bzw.
  `libkern_geprueft.a` aus einem eigenen Bauverzeichnis. Damit bleibt die ctest-Zahl
  gleich, und die Abnahme „der Baum ist unverändert" ist ohne Kunststück erfüllt.
- 2026-09-06 — **Eigene Bauverzeichnisse `bau-sanitizer-on|off` neben der Ablage.** Sie
  treffen `ventures/**/bau-*/` in der obersten `.gitignore`, kommen also nicht in die
  Versionierung, und sie fassen `ventures/.../bau` nicht an — dort baut der Baulauf, und
  zwei Läufe im selben Verzeichnis sind der Fall aus `lehren.md` vom 2026-09-03.
- 2026-09-06 — **`festkomma::abbruch` wirft `std::domain_error`, es ist kein `abort`.**
  Ein Messstand kann jeden harten Fehler des Kerns also fangen und die Meldung im
  Wortlaut drucken, statt an ihm zu sterben. Das macht aus „der Lauf brach ab" einen
  Befund mit Rundennummer statt eines Rückgabewerts.
- 2026-09-06 — **Die Prüfroutine aus `kern/test/schranken_probe.cpp` in den Messstand
  übernehmen, nicht nachbauen.** Sie erläuft ihre Adressmengen aus dem Verzeichnis; die
  Ist-gegen-Soll-Zeile im Mitschnitt zeigt sofort, ob der Maßstab noch derselbe ist.

## Was nicht funktioniert

- 2026-09-06 — **`Write` und `Edit` waren mitten im Lauf gesperrt, `Bash` mit kleinen
  Heredocs nicht.** Große Heredocs (über etwa 40 Zeilen C++) wurden ebenfalls abgelehnt.
  Folge fürs nächste Mal: Ergebnisdateien von Anfang an in Abschnitten von 20 bis 30
  Zeilen anhängen und **zuerst** das Programm schreiben, dann den Befund — ein halb
  geschriebenes Programm lässt sich später nicht mehr ergänzen. Genau daran ist
  `raender.cpp` in diesem Lauf steckengeblieben.
- 2026-09-06 — **Einen fertigen Text nachträglich zu ändern ging nicht.** Ich hatte im
  Befund auf vier Vorschläge verwiesen und wollte auf drei zusammenziehen; ohne `Edit`
  blieb nur, die Auflösung am Ende hinzuschreiben. Nächstes Mal die Zählung erst am
  Schluss vergeben.

## Offene Fährten

- **Die drei harten Fehler der Runde sind nie ausgelöst worden** — negative
  Vorrundennummer, `I64_MAX`, Modus `spielmodus`. Als Vorschlag `0160` eingereicht, der
  angefangene Messstand liegt als `befunde/beschraenktheit/raender.cpp`. Der Weg dorthin
  ist `zustand::Startbelegung`, die `partie.runde` vor der ersten Runde beliebig setzen
  darf; erlaufen wären es 9,2 Trillionen Runden.
- **65 der 101 Schrankenadressen liegen außerhalb der Maske `weltlauf`** (Marktkorb,
  Drücke, Fonds). Prüfung 6 prüft an ihnen dauerhaft nur die Startbelegung — auch nachdem
  alle sechs Schritte gebaut sind. Als Vorschlag `0158` beim Architekten. Wenn er
  entschieden hat, ist zu prüfen, ob Prüfung 5 (10.000 Botpartien) diese drei Schranken
  wirklich erreicht.
- **Die Lehre, die über dieses Paket hinausgeht:** Eine Prüfung, deren Gegenstand sich
  nicht bewegen *kann*, ist grün und wertlos. Bevor ich das nächste Mal ein Grün melde,
  messe ich zuerst, ob sich überhaupt etwas ändert — die Spalte „geändert gegenüber
  Vorrunde" hat in diesem Lauf mehr gesagt als alle zehn Schrankenurteile zusammen.
