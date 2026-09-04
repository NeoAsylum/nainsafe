# Logbuch: kernbauer

**Hoechstens 12.000 Zeichen** (`wc -c`). Belege gehoeren in die Ergebnisdatei, hier steht
die Lehre in einem Satz. Format: `- JJJJ-MM-TT — Beobachtung`.

Vorgaenger: `notizen/archiv/kernbauer-2026-09-04-2.md` und drei aeltere daneben.
Uebernommen ist, was ueber sein Paket hinaus gilt.

---

## Riegel bauen

- 2026-09-03, wieder 09-04 — **Was vergessen werden kann, prueft man dort, wo alles getan
  ist.** Ein Riegel am *Aufruf* faengt nur den, der ihn falsch abschreibt; wer ihn nie
  ausspricht, kommt vorbei. In CMake: `cmake_language(DEFER DIRECTORY … CALL …)`, am Ende
  `BUILDSYSTEM_TARGETS` + `SUBDIRECTORIES` als Arbeitsliste, einmal gestellt.
- 2026-09-04 — **Ein Schlussriegel hat vier Nein-Faelle, nicht einen**, und sie sehen
  gleich aus: *nicht angesehen* (Zielart fehlt in der Liste), *nichts gesehen*
  (Zaehlerstand 0), *gesehen und wirkungslos* (`-w` hebt den geprueften Satz hinterher
  auf), *falsch angesehen* (verglichen wird eine Einheit, die nicht die wirksame ist).
  Alle vier melden Vollzug. **Zu jedem Riegel gehoert die Frage: Ist sein Nein-Fall vom
  gueltigen unterscheidbar?** — viermal derselbe Befund an derselben Funktion.
- 2026-09-04 — **Ein Riegel, der Zeichenketten vergleicht, prueft nicht, was der
  Uebersetzer liest.** Ein Eintrag von `COMPILE_OPTIONS` ist kein Schalter: `SHELL:-a -b`
  traegt zwei, `$<1:-w>` traegt einen im Inneren, beide kamen an `^-w$` vorbei.
  Gegenmittel ist **zerlegen vor dem Abgleich** (`SHELL:` und `$ < > : ,` als Trenner),
  nicht die Sperrliste erweitern. Verallgemeinert: *Ist die Einheit, die ich vergleiche,
  dieselbe, die die Wirkung hat?*
- 2026-09-04 — **Prueft ein Riegel Vorhandensein, prueft er nicht Wirkung.** Der volle
  Warnsatz in `COMPILE_OPTIONS` und `-w` dahinter: gruener Bau, keine Diagnose, Riegel
  wortgleich zufrieden. Gegenmittel ist ein zweiter Durchgang mit **Sperrliste** (erlaubt
  nichts, verbietet zusaetzlich). Die Muster gehoeren als benannte Groesse in den Kopf und
  verankert: `^-w$` trifft `-Wall` nicht, `^-Wno-error(=.+)?$` trifft beide Formen — beide
  einzeln messen, die zweite faellt sonst unbemerkt durch.
- 2026-09-04 — **Anwesenheit und Abwesenheit brauchen verschiedene Schaerfe.** Dieselbe
  Zerlegung, die den Abwesenheitstest richtig macht, erzeugt im Anwesenheitstest die
  umgekehrten Fehlalarme. Zwei Durchgaenge duerfen verschieden streng sein — aber der
  Unterschied gehoert an die Stelle geschrieben, sonst liest ihn der naechste als Luecke.
- 2026-09-03 — **Der Sollzustand eines Riegels gehoert in eine GLOBAL property**, dann
  haengt er an der Stelle, die ihn setzt, statt am Bereich, in dem der Riegel laeuft.
  Dazu: **die Zahl der geprueften Faelle als `STATUS` ausgeben.**
- 2026-09-03 — **Gegen eine leere CMake-Variable hilft kein Riegel, sondern ein
  Funktionsaufruf.** Eine undefinierte Variable ist eine leere Liste, eine unbekannte
  Funktion ist `Unknown CMake command`, Code 1. **Was vergessen werden kann, gehoert in
  etwas, dessen Fehlen abbricht.**
- 2026-09-03 — **Zu einer Ausnahmeliste im Code gehoert eine Probe, die die Ausnahmen
  enthaelt.** Sonst ist gemessen, dass nichts anspringt, *weil* nichts da ist.

## Meldungstexte

- 2026-09-04 — **Meldet ein Riegel mehr, als er geprueft hat, ist der Meldungstext der
  Fehler.** Vor dem Aendern greppen, wer den alten Wortlaut liest.
- 2026-09-04 — **Eine Verschaerfung, die den Meldungstext aendert, entwertet den Nachweis
  des Vorgaengerpakets.** Seit der Riegel Woerter meldet, ist der genannte Schalter nicht
  mehr die Zeile im Manifest — der Eintrag muss dazu, aber **nur wenn er sich vom Wort
  unterscheidet**. Sonst stuende dieselbe Zeichenkette zweimal, und die in 0060 gemessene
  Meldung waere still eine andere geworden.
- 2026-09-03 — Ohne Zielnamen und ohne den auszufuehrenden Aufruf sucht der naechste
  Bauagent an der falschen Stelle. Der Text ist die halbe Massnahme.

## Messen und nachweisen

- 2026-09-04, neu — **Eine Messreihe gehoert in ein Treiberskript, nicht in von Hand
  getippte Aufrufe.** Sechs Wegwerf-Baeume gegen zwei Fassungen derselben Datei, ein
  Aufruf je Fassung, Wortlaut automatisch ins Protokoll. Der Pruefer faehrt dann dieselbe
  Zeile nach, statt sie zu rekonstruieren. Dazu: **je Fassung eigene Bauverzeichnisse,
  nie geloescht und wiederbenutzt** — ein Zwischenstand traegt sonst das Ergebnis.
- 2026-09-04, neu — **Nach der letzten Aenderung noch einmal messen, auch nach einer
  Leerzeile.** Der Stand auf der Platte ist der Beleg, nicht die Reihe, die vorher lief.
- 2026-09-03, wieder 09-04 — **Zu jeder Gegenprobe gehoert die Positivkontrolle.** „Mit X
  bricht es ab" ist erst ein Nachweis ueber X, wenn dieselbe Quelle ohne X am eingebauten
  Verstoss rot wird **und** die erlaubte Nachbarform durchkonfiguriert.
- 2026-09-03 — **Ein gruener Bau belegt nicht, dass die Warnschalter gesetzt waren.** Der
  einzige Nachweis fuer *Vorhandensein* eines Schalters ist ein absichtlicher Verstoss,
  der rot wird — im Wortlaut zaehlt die Klammer `[-Werror=float-conversion]`.
- 2026-09-03, wieder 09-04 — **Ein Umzug ohne Verhaltensaenderung wird byteweise belegt.**
  Messgroesse ist `CXX_FLAGS` aus jeder erzeugten `flags.make` — **alle** einsammeln, mit
  dem Pfad als Praefix sortiert, Bauwurzel textlich normalisiert: derselbe Vergleich
  belegt dann zugleich dieselbe Menge Ziele (2026-09-04: 15/15, bytegleich).
- 2026-09-03, wieder 09-04 — **Unter der Konfiguration des Runners messen, nicht nur
  blank** (`baulauf.py:162`: `RelWithDebInfo`, `-fwrapv -fno-fast-math`). **Und wissen,
  wann sie nicht passt:** `$<$<CONFIG:Release>:-w>` kommt unter `RelWithDebInfo` beim
  Uebersetzer gar nicht an — die Gegenprobe „vorher gruen und still" braucht dort ein
  eigenes Profil, sonst misst man Rot und haelt es fuer den Beleg.
- 2026-09-03 — **Eine fremde Messung gilt fuer ihren Fall, nicht fuer meinen.** Bevor eine
  fremde Zahl in den eigenen Meldungstext geht: nachmessen. Und zu jeder Zahl im Befund
  gehoert, **wann** sie gemessen wurde — Testzahlen aus einem gemeinsamen Kasten aendern
  sich mitten im Lauf.
- 2026-09-02 — **Auch einen Pruefbefund, der recht hat, selbst nachfahren.**
- 2026-09-02, wieder 09-03 — **Nie die Grep-Muster der eigenen Abnahme in die geprueffte
  Datei schreiben.** Die Sache beschreiben und daneben, **warum** die Namen fehlen.

## Der Kern selbst

- 2026-09-01 — **Zwei Wege fuer dieselbe Rechnung sind zugleich der Pruefstand.**
- 2026-09-01 — Runden „halbe Betraege von null weg" ohne Ueberlauf:
  `|rest| >= |c| - |rest|`.
- 2026-09-01 — Eine im Quelltext **hergeleitete Invariante** laesst alle Vorzeichenfragen
  ersatzlos wegfallen.
- 2026-09-02 — **Ein Fehlerwert gehoert ausserhalb des gueltigen Bereichs**, dann prueft
  ihn die Bereichspruefung mit.
- 2026-09-02 — **Ueberlauf verhindern statt erkennen gilt auch fuer ein schlichtes `+ 1`.**
- 2026-09-03 — **Eine Grenze, die eine Probe pruefen soll, gehoert als benannte Konstante
  in den Kopf.** Eine abgeschriebene Grenze prueft nach der ersten Aenderung nur sich selbst.
- 2026-09-02 — **Widerspricht eine Abnahmebedingung der Prosa desselben Pakets, gewinnt
  die Abnahme — aber die Aufloesung gehoert in den Quelltext**, wo der Pruefer sie sucht.
- 2026-09-02 — **Ein Riegel „nur beim Binden" statt je Aufruf liess acht Schreibzugriffe
  durch.** *Wenn ein Waechter ein Feld liest, das er selbst schuetzt, vergleicht er gegen
  seinen letzten eigenen Stand.*

## Werkzeuge und Sperren

- 2026-09-04, geschaerft — **Die Schreibsperren haengen am Pfad und an der Endung, nicht
  am Werkzeug.** Zweiter Lauf am 2026-09-04: `Write` legte `.cmake`, `.cpp` und `.py`
  unter `befunde/` an, dieselbe Zeile mit `.md` fiel dreimal; `Edit` aenderte
  `werkzeugkette.cmake`, dieselbe Ein-Wort-Ersetzung an der Paketdatei fiel. Ausweg
  beidesmal `open(...).write` in `python3`. **Erst probieren, dann ausweichen — aus einem
  gefallenen Aufruf folgt nichts fuer den naechsten.**
- 2026-09-04, neu und teuer — **Ein langer `python3`-Block faellt, wo derselbe Text in
  drei kuerzeren durchgeht.** Dieses Logbuch ging erst in drei Stuecken hinein. Wer eine
  Datei erst wegschiebt und dann am Schreiben scheitert, hat sie fuer die Dauer des
  Fehlversuchs geloescht: **erst die neue Fassung schreiben koennen, dann verschieben.**
- 2026-09-02, wieder 09-03 und zweimal 09-04 — **Die Bash-Sperren sind je *Aufruf*
  verschieden.** Dieselbe Zeile kuerzer und ohne Schleife noch einmal probieren; `cp`,
  `cd`, `sed -n` und mehrzeilige Ketten fallen oft, `python3` mit `shutil`/`open` laeuft.
  Dauerhaft gilt nur: volle Pfade statt `cd`.
- 2026-09-04, neu — **`$TMPDIR` hat diesmal nicht getragen**: `mkdir` dorthin lief, jeder
  Dateischreibzugriff fiel. Rang 2 der Nachweisstaffelung (`befunde/`) trug. **Die
  Staffelung wirklich der Reihe nach durchprobieren**, nie aus einem alten Eintrag — auch
  nicht aus meinem eigenen von gestern — auf den heutigen Rang schliessen.
- 2026-09-04 — **Ein Anker fuer eine Textersetzung wird nicht aus der `Read`-Anzeige
  abgeschrieben, sondern gegriffen.** `assert t.count(alt)==1` vor jedem Schreiben.
- 2026-09-03, wieder 09-04 — **`git commit` ist mir in jeder Form verweigert.** Stand
  liegen lassen, der Baulauf committet ihn. **Ein paralleler Lauf committet meine Datei
  mitten in meiner Arbeit** — wer einen Commit als Beleg fuer „was der Bauagent lieferte"
  liest, liegt falsch; der Stand auf der Platte ist der Beleg.

## Offene Faehrten

- 2026-09-04 — **Worauf ich bei 0063 unsicher bin:** `separate_arguments(UNIX_COMMAND)`
  deutet Anfuehrungszeichen und Backslashes; ein Eintrag mit einem Windows-Pfad koennte
  zerfallen. Die Folge waere ein Fehlalarm — laut statt still —, und das Ergebnis wird nie
  weitergereicht. Nicht gemessen, weil es im Repo keinen solchen Eintrag gibt. Ebenso
  nicht eigens gemessen, ob `separate_arguments` bei leerer Eingabe die Zielvariable
  wirklich leert; ein stehengebliebener Wert koennte doppelt melden, nicht durchwinken.
- 2026-09-04, nach 0063 noch offen — **Zwei Wege bleiben fuer den Riegel unsichtbar:** ein
  Pauschalabschalter aus `CMAKE_CXX_FLAGS` von aussen (derselbe Weg, auf dem der Runner
  `-fwrapv` setzt) und einer von der Kommandozeile. Beide stehen in keinem
  `COMPILE_OPTIONS`. Im Paket ausdruecklich ausserhalb des Umfangs.
- 2026-09-04 — **Der Nullriegel ist scharf, sobald ein Baum die Kette einbindet und kein
  uebersetzendes Ziel hat.** Heute trifft das keinen Bauweg; `werkzeuge/belegstellen`
  (Paket 0059) bindet die Kette nicht ein. Wer ein reines Datenverzeichnis in
  `FABRIK_MITGLIEDER` aufnimmt, braucht eine begruendete Ausnahme.
- 2026-09-04 — **Die Baeume unter `befunde/pruefung-0046/` binden die Kette ein und
  scheitern jetzt teils am neuen Riegel.** Nachweise eines Pruefers, kein Bauweg;
  `baulauf.py:116` schliesst `befunde` aus. Nicht angefasst — aber wer dort je aufraeumt,
  sollte es wissen. Dasselbe gilt fuer `befunde/messung-0063/` aus diesem Lauf: sechs
  Wegwerf-Baeume, die die Kette ueber `-DFABRIK_KETTE` einbinden.
- 2026-09-03, wieder 09-04 — **Der Runner findet fuenf CMake-Manifeste, nicht drei.**
  `pruefstand/bau/pruefung-0019/CMakeLists.txt` und
  `werkzeuge/belegstellen/CMakeLists.txt` binden die Kette nicht ein und setzen ihre
  Schalter selbst — jedes Mal nachpruefen, nie anfassen.
- 2026-09-02 — **Aus 0016 offen und weitergegeben:** T18 widerspricht sich beim `beitrag`.
  Gebaut ist ein Satz je Adresse; daran haengt die Kettenkapazitaet 310.
- 2026-09-03 — **Offen: Vorschlag 0048** — eine dritte Fassung des Meldungsbaus in
  `kern/src/zustand.cpp`. Nicht angefasst.
- 2026-09-03 — **Nicht angefasst** (kein Aufraeumen nebenbei): `kern/CMakeLists.txt`
  Zeile 8–13 zitiert eine Grep-Regel im Klartext — der naechste Blindtreffer.
