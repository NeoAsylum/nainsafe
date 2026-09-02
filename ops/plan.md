# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02, nach dem siebten Baulauf (07:45–08:16).

## Wo das Vorhaben steht

Der Kern übersetzt und fünf Prüfläufe bestehen (`befunde/uebersetzung-2026-09-02.md`,
Code 0). **Sieben von neun Kernkästen tragen Code**, `schreiber` ist in diesem Lauf
dazugekommen. Leer bleiben `werte` (2 Zeilen, hängt an der Klasse-2-Entscheidung) und
`schritt` (2 Zeilen) — es ist noch nie eine Spielrunde gerechnet worden.

## Der Engpass

**Fünf der sieben Baurollen setzen kein `status: gebaut` — die Anweisung dazu steht nur
in zwei Rollendateien.** `grep -n gebaut agents/rollen/*.md`: nur `kernbauer.md:83` und
`datenbauer.md:85` tragen den Satz. `testentwickler`, `architekt`, `spielentwerfer`,
`oberflaechenbauer` und `auslieferer` haben ihn nicht.

Zwei Folgen, beide heute eingetreten:

1. `startbereit()` zieht nur `offen` — ein Testentwicklerpaket wird also **jeden Lauf neu
   gebaut und neu bezahlt**. 0019 und 0020 sind heute gelaufen (Commits 07:56 und 08:02,
   ~600 Zeilen) und stehen beide weiter auf `offen`. Der Trockenlauf plant sie erneut.
2. Der Review zieht nur `gebaut` — ein solches Paket erreicht **nie** seinen Prüfer.
   `notizen/test-pruefer.md` (1.252 Zeichen) und `notizen/testentwickler.md` (1.256) sind
   unverändert `VORLAGE.md` (1.242). Beide Rollen haben noch nie geschrieben.

Das trifft auch 0021 („Schaden", spielentwerfer) — das Paket, das den letzten Engpass
lösen soll. Selbst wenn es läuft, bleibt es `offen` und der Entwurfsprüfer sieht es nicht.
**Fünfter Fall der Fehlerklasse aus `953bbf5`:** eine Regel an einer Stelle, die der
Ablauf nicht erreicht.

## Was quer liegt

- **Der Lauf hat etwas anderes gebaut, als jede Messung vorhergesagt hat.** Vorhergesagt
  {0011, 0016, 0019, 0020} — vom Trockenlauf um 07:32 und vom Projektmanager selbst
  (`rueckstand.md` Punkt 2). Gebaut wurde {0016, 0019, 0020, **0022**}. Ich kann die
  Abweichung nicht auflösen: **der Baulauf schreibt kein Protokoll.** `ops/` kennt
  `nachtlauf.log`, `sensorlauf.log`, `wochenlauf.log` — keinen Baulauf. Jede Zahl in
  diesem Bericht ist aus `git` und Dateizeiten rekonstruiert.
- **Architekt und Spielentwerfer sind seit 06:39 einplanbar und haben null Bytes
  geliefert.** `specs/` hat seit dem 2026-09-01 keinen Commit, beide Logbücher keinen
  Eintrag vom 2026-09-02. `einrichtung/rollen-pruefen.py` meldet „keine Befunde" — die
  Verdrahtung stimmt also, die Arbeit fehlt trotzdem. Meine Vorhersage im letzten Plan
  („zieht zum ersten Mal ein Architektenpaket") war falsch.
- **Auch ein Bauplatz ging leer aus, nicht nur Prüfplätze.** 0020 hat als einzige Datei
  `kern/test/schranken_probe.cpp` — die Datei existiert nicht. 0019 hat Kopf und Quelle,
  aber `vorrat_probe.cpp` ist 15 Byte und taucht in den fünf Prüfläufen nicht auf.
- **Vierte Messung der Fährte, Rate unverändert: 2 von 4 Prüfplätzen leer.** 0015
  `zurueck` ✓, 0018 `geprueft` ✓, **0016 ohne Befunddatei**, **0009 ohne vierte Runde**.
- **0009 steht weiter bei zwei von drei Rückläufen** und hat jetzt zwei Läufe hintereinander
  keine Prüfung bekommen. Ein weiteres `zurueck` macht es festgefahren (`baulauf.py:295`).
- **14 `.tmp`-Dateien liegen im Repo**, darunter `daten/.neu3.tmp` mit 1.608 Zeilen. Die
  Bauagenten behelfen sich mit Zwischendateien, und der Runner committet den ganzen
  Schreibpfad. Kein Gate, wächst aber.
- Unverändert aus `rueckstand.md`: TOML-Parser fehlt im Runner (viermal gemessen),
  Klasse 2 misst laufende gegen konstante Preise, die Rohdaten hat niemand.

## Was der Betreiber entscheiden muss

**Wie kommt ein Paket der fünf übrigen Baurollen auf `gebaut`?** Kein Gate — kein Geld,
kein Recht, keine Außenwirkung. Aber kein Agent darf `agents/rollen/*.md` oder
`baulauf.py` anfassen, es braucht also seine Hand.

- *A:* Den Satz aus `kernbauer.md:83` in die fünf anderen Rollendateien kopieren.
  Fünf Stellen für eine Regel — genau die Bauart, die diese Woche fünfmal gescheitert ist.
- *B:* `baulauf.py` setzt `gebaut` selbst, wenn der Bauagent mit 0 zurückkommt **und** die
  Dateien aus `dateien` sich geändert haben. Eine Stelle, deterministisch, und es prüft
  sich mit: 0020 hat nichts geschrieben und bliebe zu Recht `offen`, während es unter A
  fälschlich `gebaut` gemeldet hätte.
- *C:* Nichts tun. Dann zahlt jeder Lauf 0019 und 0020 erneut, 0011 und 0021 kommen nie
  durch, und `schritt` bekommt kein Paket.

**Empfehlung: B.** Es ist dieselbe Lehre wie beim Compiler am 2026-09-01 — was
deterministisch entscheidbar ist, gehört in den Runner, nicht in eine Rollendatei.
Zwei Zeilen dazu, die den Baulauf nach `ops/baulauf.log` schreiben, kosten nichts und
hätten die Abweichung oben beantwortet.

## Die eine Zahl

**Sieben von neun Kernkästen tragen Code (vorher sechs).** Der Zuwachs ist echt
(`kern/src/schreiber.cpp`, 388 Zeilen, übersetzt und geprüft). Die beiden fehlenden sind
`werte` und `schritt` — und `schritt` ist die Runde. Solange sie zwei Zeilen hat, rechnet
das Spiel nicht, gleich wie viele Pakete durchgehen.
