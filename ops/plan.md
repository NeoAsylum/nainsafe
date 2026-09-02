# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02, nach dem achten Baulauf (08:42–09:16, Läufe 252–260).

## Wo das Vorhaben steht

Der Kern übersetzt, und **sechs von sechs Prüfläufen bestehen** — einer mehr als gestern,
`schranken_probe` aus Paket 0020 ist echt und läuft (`befunde/uebersetzung-2026-09-02.md`).
Von 26 Paketen sind 11 `fertig`, 5 `gebaut`, 8 `offen`, 2 `blockiert`. **Sieben von neun
Kernkästen tragen Code — unverändert:** `werte` und `schritt` haben je zwei Zeilen, es ist
weiterhin nie eine Spielrunde gerechnet worden.

## Der Engpass

**Architekt und Spielentwerfer stehen in `BAUROLLEN`, werden aber vom echten Lauf nicht
aufgerufen.** Nicht „laufen und liefern nichts" — sie laufen nicht.

Der Beweis steht in den Commit-Bodies. Jeder Lauf trägt seine Journalnummer; Lauf 8 ist
**252–260 ohne Lücke**: 252 Projektmanager, 253–256 Bau (0020, 0019, 0015, 0023),
257–260 Review, 261 dieser Bericht. Kein aufgerufener Agent fehlt in der Liste.
Der Trockenlauf plante um 08:42 aber {**0011**, 0015, 0019, 0020}.

Dieselbe Rechnung für Lauf 7: geplant {**0011**, 0016, 0019, 0020}, gebaut
{0016, 0019, 0020, 0022}. **Beide Läufe gehen exakt auf, wenn man 0011 (architekt) und
0021 (spielentwerfer) aus der Trockenlaufliste streicht und von unten auffüllt.**
Zweimal unabhängig bestätigt.

Wo es passiert, weiß ich nicht. Der einzige Filter, den der echte Pfad hat und der
Trockenlauf (`baulauf.py:267`) nicht, ist `baulauf.py:307–308` — aber `befunde/` enthält
keine einzige Datei `pruefung-0011-*` oder `pruefung-0021-*`, also gibt `rueckläufe()`
für beide 0 zurück und erklärt nichts. **Weiter komme ich nicht, weil `baulauf.py` kein
Protokoll schreibt.** Das ist der zweite Plan in Folge, der den Lauf aus `git` rekonstruiert.

Was es kostet: `specs/` ist seit dem 2026-09-01 09:17 unverändert. Damit steht
0011 → 0026 → 0002 → 0010 — die längste Kette des Vorhabens — und 0021 → `schritt`.

## Was quer liegt

- **Korrektur an meinem letzten Plan:** Der `gebaut`-Satz fehlt in **drei** Rollendateien,
  nicht in fünf (`auslieferer.md:110` und `oberflaechenbauer.md:81` haben ihn). Es fehlen
  `testentwickler`, `architekt`, `spielentwerfer`. Der Projektmanager hat das selbst
  gefunden (`rueckstand.md`, Punkt 1) und kommt auf dieselbe Empfehlung.
- **0019 ist dreimal gebaut worden und hat noch nichts geliefert.** Seine zwei
  entscheidenden Dateien sind Rümpfe: `pruefstand/CMakeLists.txt` 14 Byte,
  `pruefstand/test/vorrat_probe.cpp` 15 Byte. Der Commit zu Lauf 254 enthält **keine**
  seiner vier Dateien, nur die parallele Arbeit von 0015 und 0023.
- **Der dritte CMake-Bausatz kann nicht durchfallen.** `pruefstand/bau` meldet
  „No tests were found!!!" und `ctest` gibt Code 0 zurück — der Übersetzungsbefund, den
  die Fabrik als Grundwahrheit behandelt, sagt dort `ok`, egal was drinsteht.
- **0009 und 0015 stehen beide bei zwei von drei Rückläufen** (`baulauf.py:295`). 0015 hat
  seinen zweiten heute bekommen. 0009 hatte einen Reviewplatz (Lauf 257), der nur das
  Logbuch des Prüfers geändert hat — dritte Prüfung ohne Urteilsdatei.
- **0024 und 0025 sind baubar und kommen nie dran.** 0025 hängt an nichts.
  `startbereit(...)[:4]` nimmt die ersten vier nach Dateinamen, und 0019/0020 halten zwei
  Plätze dauerhaft.
- Besser als gestern: **kein leerer Platz mehr.** Lauf 7 hatte zwei Läufe ohne Commit
  (248, 249), Lauf 8 keinen. Die Fährte „leerer Platz" ist damit nicht mehr die Zahl,
  sondern der Inhalt — siehe 0019.
- Unverändert: `.tmp`-Dateien im Repo, Klasse 2 misst laufende gegen konstante Preise,
  die Rohdaten hat niemand.

## Was der Betreiber entscheiden muss

**Wie kommen die zwei Entwurfsrollen auf einen Bauplatz, und wie meldet ein fertiges Paket
`gebaut`?** Kein Gate — kein Geld, kein Recht, keine Außenwirkung. Aber kein Agent darf
`baulauf.py` oder `agents/rollen/*.md` anfassen.

- *A:* Den `gebaut`-Satz in die drei fehlenden Rollendateien kopieren. Löst den
  Testentwickler, rührt den Engpass **nicht an** — Architekt und Spielentwerfer werden
  gar nicht erst aufgerufen.
- *B:* `baulauf.py` setzt `gebaut` selbst, wenn der Bauagent mit 0 zurückkommt **und** die
  Dateien aus `dateien` sich geändert haben — **plus zwei Zeilen, die den Lauf nach
  `ops/baulauf.log` schreiben.** B prüft sich mit: 0019 hat keine seiner Dateien
  geschrieben und bliebe zu Recht `offen`, während A es fälschlich gemeldet hätte.
- *C:* Nichts tun. Dann halten 0011, 0019, 0020, 0021 alle vier Plätze auf Dauer, `schritt`
  bekommt keinen Entwurf, und jeder Lauf bezahlt 0019 und 0020 erneut.

**Empfehlung: B — und davon das Protokoll zuerst.** Der `gebaut`-Teil ist die billigere
Hälfte; die teurere ist, dass ich zum zweiten Mal nicht sagen kann, warum eine eingeplante
Rolle nicht startet. Ohne `ops/baulauf.log` steht derselbe ungeklärte Satz im nächsten Plan
ein drittes Mal.

## Die eine Zahl

**Sieben von neun Kernkästen tragen Code — zum zweiten Lauf in Folge unverändert.**
Ein voller Baulauf hat die Zahl nicht bewegt. Die fehlenden sind `werte` und `schritt`;
`schritt` ist die Spielrunde, und die Rolle, die sie entwerfen müsste, ist seit drei
Läufen nicht aufgerufen worden.
