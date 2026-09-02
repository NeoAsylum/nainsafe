# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02, nach dem neunten Baulauf (09:40–10:10, Läufe 262–270).

## Wo das Vorhaben steht

Der Kern übersetzt, sechs von sechs Prüfläufen bestehen — unverändert. Von 28 Paketen
(zwei neue) sind 13 `fertig`, 6 `gebaut`, 7 `offen`, 2 `blockiert`. **Sieben von neun
Kernkästen tragen Code — den dritten Lauf in Folge unverändert:** `werte` und `schritt`
haben je zwei Zeilen, eine Spielrunde ist nie gerechnet worden.

Zum ersten Mal sind 0024 und 0025 gebaut worden — die zwei Pakete, die drei Pläne lang
„kommen nie dran" hießen. Das ist keine Besserung: Die Bauschlange ist leerer geworden.

## Der Engpass

**Der Review gibt ein Urteil je vier Plätze zurück — und alles, was noch baubar wäre,
wartet auf ein Urteil.**

Lauf 9 hatte vier Reviewplätze und **eine** Urteilsdatei:

- **0023** (kern-pruefer): kein Commit. Journalnummer 267 fehlt in der Folge 262–270.
- **0009** (Lauf 270): committet nur sein eigenes Logbuch. Fünfter Reviewplatz, dritter
  ohne Urteil.
- **0020** (Lauf 269): committet den Befund zu **0015** und den Übersetzungsbericht.
  Ein `pruefung-0020-*` gibt es nicht.
- **0015** (Lauf 268): committet nur sein Logbuch — sein eigener Befund (`geprueft`,
  0 Befunde) wurde vom parallel laufenden 0020-Prüfer mitgenommen.

Vier Pakete stehen damit auf `gebaut` **ohne jedes Urteil**: 0020, 0023, 0024, 0025.
Daran hängt der Rest: 0027 wartet auf 0023, 0026 auf 0025 (und auf 0011), 0002 auf 0026,
0010 auf 0002.

**Warum es sich nicht selbst korrigiert:** `rueckläufe()` (`baulauf.py:236`) zählt nur
Dateien mit `urteil: zurueck`. Ein Prüfer, der nichts schreibt, zählt nicht. 0009 steht
deshalb nach fünf Reviewplätzen weiter bei zwei von drei Rückläufen, ist Erster in der
nach Dateinamen sortierten Liste `[:4]` — und belegt Platz 1 auf Dauer. Die
Konvergenzbremse greift bei genau der Sorte Paket nicht, für die sie gebaut wurde.

## Was quer liegt

- **Der Trockenlauf plant für Lauf 10 nur noch drei Baupakete: 0011, 0019, 0021.** Zwei
  davon gehören Architekt und Spielentwerfer, die zum dritten Mal in Folge nicht
  aufgerufen wurden — Lauf 9 baute {0015, 0019, 0024, 0025}, geplant war
  {0011, 0015, 0019, 0021}. Der Projektmanager hat 0011/0021 nicht angefasst,
  `rueckläufe` ist für beide 0, `befunde/` enthält keine ihrer Prüfungen. **Damit hat der
  nächste Lauf einen einzigen wirksamen Bauplatz** — 0019.
- **0019 hat im vierten Bauversuch keine eigene Datei geschrieben.**
  `pruefstand/CMakeLists.txt` 14 Byte, `test/vorrat_probe.cpp` 15 Byte, beide unverändert
  seit 07:54; der Commit zu Lauf 263 enthält ausschließlich fremde Dateien. Die
  geschärfte Reihenfolgevorgabe des Projektmanagers hat nichts bewegt.
- **Gebautes und Vorgabe laufen auseinander.** `specs/technik.md` ist seit dem
  2026-09-01 09:17 unverändert: 6 Zeilen nennen Rust, keine nennt C++, 2 nennen
  `cargo`/`rustc` — während der Kern vollständig in C++ steht (ADR 0011). Jedes
  Kernpaket bezahlt die Übersetzung erneut, und ein Prüfer, der `specs/` gegen den Code
  hält, misst gegen den falschen Text.
- Unverändert: `pruefstand` kann nicht durchfallen („No tests were found!!!", Code 0);
  ein TOML-Parser fehlt im Runner; 14 `.tmp`-Dateien liegen committet im Repo.

## Was der Betreiber entscheiden muss

Dieselbe Frage wie in meinen letzten beiden Plänen — **sie ist nicht abgelehnt, sondern
ungelesen.** Der letzte Commit des Betreibers ist von 06:39, meine Pläne von 07:32, 08:25
und 09:25 kamen danach. Kein Gate: kein Geld, kein Recht, keine Außenwirkung. Aber kein
Agent darf `baulauf.py` oder `agents/rollen/*.md` anfassen.

**Empfehlung unverändert B, jetzt mit zwei Gründen statt einem:** `baulauf.py` setzt
`gebaut` selbst, wenn der Bauagent mit 0 zurückkommt **und** eine Datei aus `dateien`
sich geändert hat — **plus die Zeilen, die jeden Lauf nach `ops/baulauf.log` schreiben**
(geplant, aufgerufen, Rückgabecode, ob die erwartete Datei entstand).

Das Protokoll ist inzwischen die wichtigere Hälfte. Es beantwortet beide offenen Fragen
auf einmal: warum 0011 und 0021 nicht starten, und wie oft ein Paket einen Prüfer ohne
Urteil verbraucht. Ohne es steht der ungeklärte Satz zum vierten Mal im nächsten Plan.

*Alternative A* — den `gebaut`-Satz in die drei fehlenden Rollendateien kopieren — löst
den Testentwickler und rührt weder den Review-Engpass noch den Aufruf an.

## Die eine Zahl

**Sieben von neun Kernkästen tragen Code — der dritte Lauf in Folge unverändert.**
Es fehlen `werte` und `schritt`. `schritt` ist die Spielrunde; sein Entwurfspaket (0021)
ist seit drei Läufen eingeplant und nie gestartet.
