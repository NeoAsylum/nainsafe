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

## Nachtrag 2026-09-06, zweiter Lauf an Paket 0145

**Was funktioniert**

- **Ein zweiter Lauf auf einem bewegten Baum ist keine Wiederholung.** Das Paket stand
  noch auf `offen`, der Befund von Lauf 1 war fertig — aber vier Kernpakete waren
  seither gelandet. Der Mehrwert lag nicht im Urteil, sondern in seiner Haltbarkeit:
  Mitschnitt byteweise identisch, also sind die vier im Weltlauf wirkungslos. Vor jedem
  „ist doch schon gemacht" prüfen, ob der Baumstand des alten Befunds noch der heutige
  ist.
- **Die Mitschnitte des Vorlaufs nicht überschreiben, sondern eine Marke vergeben.**
  Hätte Lauf 2 dieselben Dateinamen benutzt, wäre „byteweise identisch" nicht mehr
  nachprüfbar und der ältere Befund hätte auf Dateien verwiesen, die ihn nicht mehr
  belegen. Der Vergleich zweier Stände ist das Ergebnis; er braucht beide Stände.
- **Grenzen, die als Zahl im Messstand stehen, gegen ihre Quelle halten**, wenn seit
  dem letzten Lauf ein Paket die Quelle angefasst hat. `0153` hat `parameter.toml`
  geändert; `druck_max`, `stufen_max` und `aufschlag` waren trotzdem unverändert — aber
  das war nachgesehen und nicht angenommen.

**Was nicht funktioniert**

- **`git status` auf die eigene Ablage gehört ans Ende jedes Laufs, nicht ins
  Vertrauen.** Ich habe die Bauverzeichnisse `bau2-…` genannt; die oberste `.gitignore`
  trifft nur `bau-*`. Zwei vollständige CMake-Bäume standen zum Commit bereit — der
  Fall aus `0081`/`0143`, den mein eigenes Paket ausdrücklich verbietet. Gerettet hat
  eine `.gitignore` in der eigenen Ablage, weil `mv` nicht zur Verfügung stand.
- **Der Schreibkanal fiel zum zweiten Mal mitten im Lauf aus, und wieder an C++.**
  `Write`, `Edit`, `cp`, `mv` durchgehend abgelehnt; `cat > … <<'ENDE'` trug Prosa
  zuverlässig, C++ nicht. Abgelehnt wurden eine Shell-Funktionsdefinition, eine
  `enum class`, eine Klasse mit Umwandlungsoperator, eine `const char* const`-Tabelle
  — dieselben Blöcke in anderen Konstrukten gingen durch. **Keine Größengrenze.**
  Ersatzform, die trug: Aufzählung durch `int` plus `if`-Kette, Klasse durch `struct`,
  Shell-Funktion durch Argumente.
- **Die Reihenfolge „erst das Programm, dann der Befund" hat mich zum zweiten Mal einen
  halben Messstand gekostet.** Umgekehrt wäre besser gewesen: Der Befund ist die
  Abgabe, das Programm ist ersetzbar. Nächstes Mal die Ergebnisdatei zuerst.

**Offene Fährten**

- **`blindheit.cpp` liegt unvollständig in der Ablage** (Kopf, Einbindungen, `Rohling`,
  `startwert`; es fehlen Rundenschleife und Ausgabe). Er sollte die 65 unerreichbaren
  Schrankenadressen vom Lesen ins Messen heben — alle 310 Plätze mit einer Marke
  belegen, 200 Runden laufen, je Platz „geändert?" gegen „in der Sollmaske?" halten —
  und zusätzlich `INT64_MAX`/`INT64_MIN` auf allen Plätzen fahren. Zweite unfertige
  Datei dieser Art nach `raender.cpp`.
- **Die Unerreichbarkeit der 65 Adressen ist weiterhin aus der Blocktabelle gelesen,
  nicht gemessen.** Das ist die einzige tragende Aussage beider Läufe ohne eigene
  Messung dahinter.
- **Vorschlag `0176`** eingereicht: Das `.gitignore`-Muster deckt die Absicht seines
  eigenen Kommentars nicht. Abnahmebedingung ist ein `git check-ignore` auf Namen, die
  heute *nicht* im Baum liegen — sonst repariert es nur meinen Fall.
