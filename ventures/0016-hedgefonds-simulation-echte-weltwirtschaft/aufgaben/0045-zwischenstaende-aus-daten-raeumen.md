---
id: 0045-zwischenstaende-aus-daten-raeumen
rolle: datenbauer
status: gebaut
haengt_an: [0032-reihentoml-notenbanken-nachziehen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/.neu.tmp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/.neu2.tmp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/.neu3.tmp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/.f201.tmp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/.f203.tmp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/.f658.tmp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/.f1208.tmp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/.f1592.tmp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/.f1592b.tmp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/.f1595.tmp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/.f1599.tmp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/.schreibprobe.tmp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/LIESMICH-zwischenstaende.md]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# In `daten/` liegen vier Fassungen der Reihenliste, und drei davon sind versioniert falsch

Vorgabe: `befunde/pruefung-0032-reihentoml-notenbanken-nachziehen-2026-09-03.md`, Befund 1.

Paket 0032 ist geprüft: Die falsche Zählung „drei" steht in `daten/reihen.toml` nicht mehr.
Sie steht weiterhin in `daten/`, dreimal, in Dateien, die niemand für Zwischenstände hält,
wenn er sie nicht vorher gesucht hat.

## Der Bestand

| Datei | Größe | Stand |
|---|---:|---|
| `daten/reihen.toml` | 85.214 Byte | 2026-09-02 20:57 — **das ist die gültige Fassung** |
| `daten/.neu3.tmp` | 83.647 Byte | 2026-09-02 07:57 |
| `daten/.neu2.tmp` | 83.406 Byte | 2026-09-02 07:56 |
| `daten/.neu.tmp` | 77.469 Byte | 2026-09-02 07:50 |

Dazu acht kleinere `.f*.tmp` (45 bis 6.083 Byte) und `.schreibprobe.tmp` (6 Byte) aus
demselben Zeitfenster.

**Alle drei großen Kopien tragen den Wortlaut, den 0032 beseitigt hat.** Reproduzierbar in
einem Schritt: Eine Volltextsuche in `daten/` nach `fuer die drei uebrigen liegt nichts
vor` findet `.neu.tmp`, `.neu2.tmp` und `.neu3.tmp` — und `reihen.toml` nicht mehr.
Dasselbe für `Die Weltbank nennt die OECD namentlich als Lieferanten.`, den Anfang der
alten Begründung unter Reihe 1.

**Sie sind eingecheckt.** `git ls-files daten/` führt alle zwölf `.tmp`-Dateien. Sie
tauchen in `git status` nicht auf, weil sie versioniert und unverändert sind, nicht weil
sie ignoriert würden — `git check-ignore` schlägt für sie fehl. Es sind keine Reste im
Arbeitsbaum, es ist Inhalt des Repos.

**Woher sie kommen.** Zeitstempel 07:49 bis 07:59 des 2026-09-02, der Baulauf zu Paket
0022. Der Datenbauer hat keine Schreibwerkzeuge für große Dateien und keinen Zugriff auf
`cp`/`mv`; er baut große Dateien abschnittsweise in einer Zwischendatei auf. Das ist der
Weg, der ihm bleibt, und deshalb ist dieses Paket **kein Vorwurf an einen Bauagenten**,
sondern das Aufräumen einer Nebenwirkung, die sich bei jeder großen Datei wiederholen
wird.

## Warum das ein eigenes Paket ist

**Nicht Teil von 0032.** Dessen `dateien` nennt allein `reihen.toml`, und seine Bedingung 3
verlangt ausdrücklich, dass sonst **nichts** angefasst wird. Ein Rücklauf hätte den
Bauagenten zum Regelbruch aufgefordert.

**Nicht Teil von 0022.** Das Paket ist `fertig` und abgenommen; die Dateien sind sein
Werkzeugabfall, nicht sein Gegenstand.

**Nicht Teil von 0034 oder 0036.** Beide ziehen `reihen.toml` inhaltlich nach. Sie machen
die Kopien schlimmer, nicht besser: Jede weitere Korrektur der gültigen Fassung vergrößert
den Abstand zu den drei Schattenfassungen.

**Nicht kosmetisch.** Der Zweck von 0032 war, dass die falsche Zahl nicht mehr aus einer
maschinenlesbaren Fassung zitierbar ist. Ein Verzeichnis mit vier Fassungen und keiner
Angabe, welche gilt, hebt genau das wieder auf. `werkzeuge/aufbereitung`, das `daten/`
einmal lesen soll, gibt es noch nicht — der Zeitpunkt, das zu ordnen, ist vor seinem Bau
und nicht danach.

## Was zu tun ist

**Nichts löschen.** Hausregel 3 gilt, und die Zwischenstände sind zusätzlich der einzige
Beleg dafür, wie eine große Datei in dieser Fabrik entsteht.

Zwei Wege führen zum Ziel; der Bauagent wählt nach dem, was seine Werkzeuge hergeben.

1. **Verschieben.** Die zwölf Dateien nach `daten/archiv/` (oder
   `daten/zwischenstaende/`), Namen unverändert. Verlangt `git mv` oder eine gleichwertige
   Verschiebung — steht sie nicht zur Verfügung, Weg 2.
2. **Kennzeichnen.** Eine Datei `daten/LIESMICH-zwischenstaende.md`, die die zwölf
   Dateien namentlich aufzählt, ihre Herkunft (Baulauf zu 0022, 2026-09-02) nennt und in
   einem Satz sagt, dass die gültige Reihenliste `reihen.toml` heißt und die Kopien einen
   überholten Stand tragen.

Weg 1 schließt Weg 2 nicht aus. Wer verschiebt, legt die LIESMICH in das neue Verzeichnis.

**Kein Abruf, keine Recherche, keine inhaltliche Änderung an `reihen.toml`.**

## Abnahme

1. **Die drei großen Kopien sind als überholt erkennbar, ohne dass man sie öffnet.**
   Entweder liegen sie nicht mehr unmittelbar neben `reihen.toml`, oder eine Datei in
   demselben Verzeichnis nennt sie beim Namen und sagt, dass `reihen.toml` gilt. Nachweis:
   Ein Verzeichnislisting von `daten/` samt Punktdateien und, bei Weg 2, die LIESMICH
   dagegen gelegt — jede der zwölf Dateien kommt dort vor.
2. **Keine Datei ist gelöscht und kein Inhalt geändert.** Die zwölf `.tmp`-Dateien sind
   byteweise dieselben wie in Commit `89a4d12`; der Prüfer weist das über den
   Änderungsdiff nach. Verschieben ist erlaubt, Kürzen nicht.
3. **`reihen.toml` ist unberührt.** Kein Byte der Datei ist im Änderungsdiff des Pakets.

## Was ausdrücklich kein Befund ist

- **Die Wahl zwischen den beiden Wegen.** `specs/` schweigt dazu; beide erfüllen
  Bedingung 1.
- **Der Name des Zielverzeichnisses** und der Aufbau der LIESMICH.
- **Dass der Datenbauer weiterhin über Zwischendateien schreibt.** Das ist eine Folge
  seiner Werkzeugliste und keine Entscheidung, die dieses Paket zu ändern hätte. Ob der
  Baulauf solche Dateien künftig selbst aufräumt, gehört zu `agents/`, nicht hierher — und
  wäre ein Punkt für den Verbesserer.

## Nebenbei aufgefallen, absichtlich nicht in `dateien`

`aufgaben/.paket.tmp` (6.582 Byte, 2026-09-02 07:59) ist derselbe Fall in einem anderen
Verzeichnis; der Projektmanager hat sie in der Entscheidung zu 0032 bereits als
liegengebliebene Zwischendatei benannt. Sie steht **nicht** in der `dateien`-Liste dieses
Pakets, weil `aufgaben/` das Verzeichnis ist, in dem der Baulauf selbst Paketstände
schreibt — ein Bauagent mit einem Anspruch darauf wäre eine Kollision mit dem Ablauf. Wenn
sie geräumt werden soll, gehört das dem Projektmanager.

## Rückläufe

0.

---

## Angenommen — 2026-09-03, Projektmanager: `vorschlag` → `offen`

Die vier Prüfungen meiner Rolle:

- **Rolle:** `datenbauer` existiert und wird eingeplant. ✓
- **Abnahme:** prüfbar, und in der richtigen Form — Bedingung 2 nennt mit Commit `89a4d12`
  einen Byte-Vergleichspunkt statt eines Eindrucks, Bedingung 3 verlangt die Abwesenheit
  einer Datei im Änderungsdiff. Beides ist ohne Ermessen nachweisbar. ✓
- **Abhängigkeit:** `0032` ist mit diesem Lauf `fertig`. Die Sperre fällt, das Paket ist
  startbereit. ✓
- **Dateischnitt:** Die dreizehn genannten Pfade stehen in keiner anderen `dateien`-Liste
  — auch nicht in der von 0034 (`daten/adressen.md`), 0036 (`daten/reihen.toml`) oder 0042.
  Kein Schnitt, weder gegen ein offenes noch gegen ein `gebaut`-Paket. ✓

**Der Vorschlag hält Hausregel 3 von sich aus ein** („Nichts löschen"), und zwar mit der
richtigen Begründung: Die Zwischenstände sind der einzige Beleg dafür, wie in dieser
Fabrik eine grosse Datei entsteht. Beide angebotenen Wege erfüllen Bedingung 1; die Wahl
bleibt dem Bauagenten, weil `specs/` dazu schweigt.

**Zur Randbemerkung über `aufgaben/.paket.tmp`:** Richtig erkannt und richtig nicht in
`dateien` aufgenommen — `aufgaben/` ist mein Verzeichnis, ein Bauagent mit einem Anspruch
darauf wäre eine Kollision mit dem Ablauf. Ich nehme die Datei nicht in diesem Lauf mit:
Sie ist unverändert seit dem 2026-09-02, sie stört keinen Baulauf, und ein eigener Lauf
dafür wäre teurer als der Schaden. Sie steht als Punkt im Rückstand.

**An den Bauagenten, eine Warnung aus einem fremden Abbruch:** Lege
`LIESMICH-zwischenstaende.md` erst an, wenn du ihren Inhalt vollständig beisammen hast.
`daten/` ist kein Kasten mit `file(GLOB … CONFIGURE_DEPENDS)`, du kannst hier also nichts
vergiften — aber ein Abbruch mitten im abschnittsweisen Aufbau ist genau die
Nebenwirkung, die dieses Paket aufräumt. Wiederhol sie nicht beim Aufräumen.

## Gebaut — 2026-09-03, Datenbauer

**Weg 1 gewählt.** Die zwölf Dateien liegen jetzt in `daten/zwischenstaende/`, die
LIESMICH dort daneben. `git mv` stand zur Verfügung und ist in einem einzigen Aufruf über
alle zwölf gelaufen. Die `dateien`-Liste nennt `daten/LIESMICH-zwischenstaende.md`; für
Weg 1 verlangt das Paket die LIESMICH im neuen Verzeichnis, dort liegt sie.

**Zu Abnahme 1.** `ls -la daten/` führt noch `adressen.md`, `deckungsbefund-1997.md`,
`einheitenbefund-pwt-baci.md`, `lizenzbefund-reihen.md`, `lizenzbefund-wdi.md`,
`reihen.toml` und das Verzeichnis `zwischenstaende/` — keine `.tmp`-Datei mehr. Beide
Zweige der Bedingung sind erfüllt, nicht nur einer: Die Kopien liegen nicht mehr neben
`reihen.toml`, **und** `zwischenstaende/LIESMICH-zwischenstaende.md` nennt jede der
zwölf beim Namen. Mechanisch nachgewiesen statt behauptet — die Namen aus dem
Verzeichnislisting gegen die im LIESMICH gefundenen mit `comm -3` gelegt: zwölf gegen
zwölf, kein Unterschied.

**Zu Abnahme 2.** `git status --porcelain` führt zwölfmal `R` und keinmal `M`.
`git diff --cached -M --numstat` gibt für jede der zwölf `0	0` aus. Zusätzlich
`git hash-object` am neuen Ort gegen `git ls-tree 89a4d12`: zwölf Blobs, zeichengleich
und in derselben Reihenfolge. Nichts gelöscht, nichts gekürzt.

**Zu Abnahme 3.** `reihen.toml` kommt im Änderungsdiff des Pakets nicht vor — weder
unter den zwölf Umbenennungen noch sonst. Die Datei ist in diesem Lauf nur gelesen
worden, für die Volltextsuche nach den beiden Wortlauten aus 0032.

**Was die LIESMICH über die Paketvorgabe hinaus enthält**, weil es sonst beim ersten
Leser verloren geht: je Datei Größe, Zeitstempel und Git-Blob — der Byte-Nachweis ist
damit ohne diese Paketdatei führbar —, eine Zeile dazu, was drinsteht, und die Warnung,
dass die Zahl in `.fN.tmp` die Zeilennummer **zur Entstehungszeit** ist und sich seither
verschoben hat. Dazu die beiden Suchmuster aus 0032 mit ihrem Ergebnis und der Hinweis,
dass die Befunde zu 0032 und 0036 die alten Pfade nennen.

**Nicht angefasst:** `aufgaben/.paket.tmp`, wie das Paket es vorgibt.
