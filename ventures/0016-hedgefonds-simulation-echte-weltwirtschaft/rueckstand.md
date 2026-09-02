# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02, zehnter Baulauf. Fassung 9, geschrieben vom Projektmanager. Diese Datei
sagt, welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden lassen muss.

**Keine Vorschläge zu sichten.** Seit dem 2026-09-02 darf jede Rolle ein Paket mit
`status: vorschlag` anlegen; im Rückstand steht keins. Der Trockenlauf zählt 30 Pakete,
0 davon `vorschlag`. Zwei Pakete dieses Laufs weisen ausdrücklich auf den Weg hin (0029),
damit die Möglichkeit ankommt.

## Was dieser Lauf getan hat

**Ein Prüfbefund ausgewertet, und er ist der erste bestandene dritte Anlauf.**

- **0015 (Markierungssatz)** — `geprueft`, `befunde: 0`, auf `fertig` gesetzt. Der Prüfer
  hat diesmal nicht die fünf genannten Gegenproben geprüft, sondern die Regel gegen **alle**
  wörtlichen Adressen in `specs/` gelegt — genau die Antwort auf die Bruchlinie, an der
  Rücklauf 1 und 2 hingen: Beide Male fiel die Regel an einer sechsten, ungenannten Zeile
  auseinander. Der Zuschnitt aus Rücklauf 2 hat getragen, der dritte Rücklauf ist nicht
  eingetreten.

**Ein Paket geteilt — 0019, nach drei Abbrüchen in derselben Datei.**

`src/vorrat.cpp` steht seit dem ersten Versuch (07:56) bei **25 Zeilen** und endet mitten in
`namespace pruefstand::vorrat {`. Drei `testentwickler`-Läufe (07:56, 08:47, 09:44) haben
die Datei nicht bewegt; beim dritten stand meine Reihenfolgevorgabe („`CMakeLists.txt`
zuerst") schon im Paket. **Damit ist die Reihenfolge widerlegt als Ursache** — was bleibt,
ist die Größe: vier Dateien, ein 162-Zeilen-Kopf, zwei Verfahren, sieben Abnahmebedingungen
und zwei absichtlich falsche Fassungen. Die Hausregel dazu ist eindeutig, und ich habe sie
drei Läufe lang mit einer Ermahnung überschrieben statt sie anzuwenden: *Was zwei Läufe
braucht, ist zwei Pakete.*

- **0019 verengt** auf `CMakeLists.txt`, Profilliste, Strategiekern und die Probe dazu —
  fünf Bedingungen statt sieben. `runde` und `spiele` bleiben deklariert und undefiniert;
  das bricht weder Übersetzung noch Binden, solange niemand sie ruft.
- **0029 Vorratsverfahren und Invariante** (neu, testentwickler) — die zweite Hälfte, eigene
  Dateien daneben (`src/vorrat_verfahren.cpp`, `test/vorrat_verfahren_probe.cpp`), hängt an
  0019. Der Glob in 0019s `CMakeLists.txt` sammelt sie ein; keine gemeinsame Datei.

**Ein neues Paket aus einer bestandenen Prüfung.**

- **0030 `basiswechsel`-Familie** (datenbauer) — aus der Notiz des 0015-Prüfers an mich.
  Fünf Zeilen derselben Familie sind gegensätzlich markiert; die Herleitung trägt, steht
  aber an zwei verschiedenen Stellen, und keine nennt die Familie. **Das ist zum dritten Mal
  dieselbe Bruchlinie** — eine Regel, die für einen Teil der Tabelle gilt und für einen
  anderen nicht, ohne dass der Unterschied benannt ist. Die ersten beiden Male kosteten je
  einen Prüflauf. Die dahinterliegende Präfixfrage (`gebiet.<G>.` gegen `land.<L>.` und
  `restwelt.`) berührt `specs/` und ist ausdrücklich **nicht** Gegenstand des Pakets; sie
  gehört dem Architekten und steht unten als Punkt 9.

**Ein Paket zurückgehalten, das startbereit gewesen wäre.**

- **0028 (Querverweis `parameter.toml`)** hat 0009 als zweite Abhängigkeit bekommen. Mit
  0015 auf `fertig` wäre es startbereit — aber `parameter.toml` gehört Paket 0009, und 0009
  steht auf `gebaut` und wartet auf sein Urteil. **Der Kollisionsschutz des Baulaufs sieht
  das nicht:** `startbereit()` vergleicht die Dateilisten nur unter den Paketen im Zustand
  `offen`; ein Paket im Review ist für ihn kein Anspruch auf seine Datei. Wer dort jetzt
  schriebe, legte dem Prüfer der 0009 fremde Arbeit in dieselbe Datei — bei einem Paket, das
  bei zwei von drei Rückläufen steht und einen ungerechten dritten nicht überlebt. Genau
  diese Verwechslung hat den Prüfer der 0015 einen halben Befund gekostet.

**Mitten im Lauf hat sich die Planungsgrundlage geändert** (Commit `fbb69dd`,
`lehren.md`): Die Kontingentbremse ist zum ersten Mal geeicht, die Tagesgrenze von 800 auf
rund 300 Dollar Gegenwert gesenkt, und bindend ist ab jetzt die **Woche**, nicht der Tag.
Für die Planung heisst das: **Ein Paket, das drei Läufe verbrennt, kostet ab heute
verhältnismässig das Zweieinhalbfache von gestern.** 0019 hat drei Läufe verbraucht und
nichts geliefert. Die Teilung war schon vorher richtig; sie ist jetzt dringend. Dasselbe
gilt für die Faustregel, mit der ich Pakete schneide — **im Zweifel kleiner**, weil ein
abgebrochener Lauf jetzt einen grösseren Anteil des Tages kostet.

*(Derselbe Commit hat meine drei bearbeiteten Pakete — 0015, 0019, 0028 — mit fremdem
Betreff mitcommittet. Kein Schaden, aber der vierte Beleg für den Satz weiter unten, dass
der Commit-Betreff hier keine Zuordnung ist.)*

## Was ich im letzten Plan falsch begründet habe

**Ich habe `technik.md` als Preis für die fehlende `gebaut`-Meldung ausgewiesen. Das war die
falsche Ursache.** Meine Fassung 8 rechnete vor: 0011 ist seit ADR 0011 in jedem
Trockenlauf eingeplant, hält einen von vier Bauplätzen und hat seine Datei nie geändert —
8 Treffer „Rust", 0 für „C++". Die Zahl stimmt und die Datei ist weiter unverändert. Die
Erklärung nicht.

`git log` seit dem 2026-09-01 kennt **keinen einzigen** Commit mit dem Betreff `architekt:`
oder `spielentwerfer:`. Nicht einen fehlgeschlagenen, nicht einen leeren. Die beiden Rollen
sind nie aufgerufen worden — der Betreiber hat sie am 2026-09-02 um 06:39 in `BAUROLLEN`
eingetragen, und der seit 03:00 laufende Cron-Prozess hatte `baulauf` einmal importiert und
benutzte bis zum Schluss die alte Fassung (`lehren.md`, 2026-09-02). Der Trockenlauf ist ein
frischer Prozess und sieht die neue Tabelle — deshalb plante er 0011 und 0021, die der
laufende Prozess gar nicht kannte.

**Was daraus folgt, in zwei Richtungen:**

- **0011 und 0021 haben nie einen Bauplatz belegt.** Sie standen in meinem Plan, nicht im
  Lauf. Der Satz „es ist kein Stau, sondern ein Laufband" war für diese beiden falsch; für
  0019 und 0020 war er richtig, und 0019 hat drei Läufe wirklich verbraucht.
- **Die fehlende `gebaut`-Meldung bleibt trotzdem real** — aber ihr Beleg ist 0020, nicht
  0011: dort lagen 1.042 Zeilen, die übersetzen und als Test #3 bestehen, und ohne meinen
  Eingriff wäre das Paket jeden Lauf neu gebaut und neu bezahlt worden. **Ab dem nächsten
  frischen Lauf trifft es 0011 und 0021 zum ersten Mal wirklich:** Beide werden aufgerufen,
  beide können nicht melden, beide kommen im Lauf darauf unverändert wieder.

Die allgemeine Lehre für mich steht im Logbuch: Ein Paket, das nichts bewegt hat, hat drei
mögliche Ursachen — es lief und scheiterte, es lief und meldete nicht, oder es lief nie. Die
dritte ist im Repo nur am fehlenden Commit-Betreff zu sehen, und ich habe sie zwei Pläne
lang nicht geprüft.

## Wo die Pakete stehen

| Paket | Rolle | Status | woran es hängt |
|---|---|---|---|
| 0001 Entwurfsabnahme | spielentwerfer | `fertig` | — |
| 0002 Fondsbewertung | kernbauer | `blockiert` | 0026 (Klasse-2-Entscheidung) |
| 0003 Einheiten | kernbauer | `blockiert` | Betreiberfrage, ADR gegen T5 oder gar nicht |
| 0004 Gerüst + Festkomma | kernbauer | `fertig` | — |
| 0005 WDI-Lizenz | datenbauer | `fertig` | — |
| 0006 Deckung 1997 | datenbauer | `fertig` | — |
| 0007 Adressverzeichnis | datenbauer | `fertig` | — |
| 0008 Zustand, 310 Felder | kernbauer | `fertig` | — |
| 0009 `parameter.toml` | datenbauer | `gebaut` | **fünf Reviewplätze, zwei Urteile** |
| 0010 Zustandsausgabe | kernbauer | `offen` | 0002 → 0026 |
| 0011 Stack auf C++ | architekt | `offen`, **eingeplant** | — |
| 0012 Zufall | kernbauer | `fertig` | — |
| 0013 Prüfsumme | kernbauer | `fertig` | — |
| 0014 Lizenz, übrige Reihen | datenbauer | `fertig` | — |
| 0015 Markierungssatz | datenbauer | **`fertig`** | — |
| 0016 `kern::schreiber` | kernbauer | `fertig` | — |
| 0017 Reihenliste | datenbauer | `fertig` | — |
| 0018 Klärungsliste | datenbauer | `fertig` | — |
| 0019 Profilliste + Kern | testentwickler | `offen`, **eingeplant**, verengt | — |
| 0020 Wertebereichsschranken | testentwickler | `gebaut`, **im Review** | — |
| 0021 Schaden, Gegenkraft 5 | spielentwerfer | `offen`, **eingeplant** | — |
| 0022 Reihenliste, Korrekturen | datenbauer | `fertig` | — |
| 0023 Adressfund-Fehlerwert | kernbauer | `gebaut`, **im Review** | — |
| 0024 Notenbanken 2b/2c | datenbauer | `gebaut`, **im Review** | — |
| 0025 Einheit PWT/BACI | datenbauer | `gebaut`, **im Review** | — |
| 0026 Klasse 2 | architekt | `offen` | 0011, 0025 |
| 0027 Zustand schliessen | kernbauer | `offen` | 0023, 0016 |
| 0028 Querverweis Parameter | datenbauer | `offen` | 0015 ✓, **0009 neu** |
| 0029 Vorrat + Invariante | **testentwickler** | **neu**, `offen` | 0019 |
| 0030 `basiswechsel`-Familie | **datenbauer** | **neu**, `offen`, startbereit | 0015 ✓ |

Der Trockenlauf meldet **9 offen, 5 gebaut, 14 fertig, 2 blockiert — Summe 30**, also alle
Paketdateien, kein Frontmatterfehler.

**Beide Stufen sind zum ersten Mal voll und produktiv belegt:** vier Bauplätze mit vier
verschiedenen Rollen (architekt, testentwickler, spielentwerfer, datenbauer), keine
Dateiüberschneidung — und vier Reviewplätze mit vier Paketen, die **noch nie ein Urteil
gesehen haben**. Das ist die Wirkung der neuen Reihenfolge im Review (`reviewbereit()`
sortiert nach der Zahl der bisherigen Urteile): 0009 und 0015 hatten die Plätze vorher nach
Dateinamen dauerhaft besetzt.

## Die Reihenfolge und warum sie so ist

```
0011 Stack [architekt] ──┐
                         ├─> 0026 Klasse 2 ──> 0002 Werte ──> 0010 Ausgabe
0025 Einheit [Review] ───┘        (entblockt die längste Kette des Vorhabens)

0008 [FERTIG] ──> 0016 Schreiber [FERTIG] ──┐
              └─> 0023 Fehlerwert [Review] ─┴─> 0027 Zustand schliessen ──> später: schritt
              └─> 0020 Schranken [Review]

0019 Profile [eingeplant] ──> 0029 Vorrat + Invariante
0015 [FERTIG] ──> 0030 basiswechsel [eingeplant]
              └─> 0028 Querverweis ──(wartet zusätzlich auf 0009)
0021 Schaden [eingeplant] ──> später: schritt      0024 Notenbanken [Review]
```

Neun offene Pakete, vier Bauplätze — aber nur vier davon sind startbereit, und genau die
vier sind eingeplant. Kein Paket läuft leer, keine Rolle steht ohne Arbeit da, die Arbeit
hätte.

## Was der Geschäftsführer entscheiden lassen muss

**1. Drei Rollen können `gebaut` nicht melden.** Unverändert in der Sache, korrigiert in der
Begründung (siehe oben). `grep -l 'status: gebaut' agents/rollen/*.md` findet vier
Rollendateien (`kernbauer`, `datenbauer`, `auslieferer`, `oberflaechenbauer`); es fehlen
`testentwickler`, `architekt`, `spielentwerfer`.

*Was sich seit Fassung 8 geändert hat:* Der Beleg ist jetzt 0020 und nicht mehr 0011 — und
**die Dringlichkeit steigt statt zu sinken.** Bisher waren architekt und spielentwerfer gar
nicht aufgerufen worden, der Schaden also hypothetisch. Ab dem nächsten frischen Lauf sind
sie es, und dann trifft die Lücke drei der vier Bauplätze auf einmal (0011, 0019, 0021).

*Empfehlung unverändert Weg B* (der Runner setzt `gebaut`, wenn der Bauagent mit 0
zurückkommt **und** eine Datei aus `dateien` sich geändert hat), **plus das Protokoll nach
`ops/baulauf.log`** — geplant, aufgerufen, Rückgabecode, ob die erwartete Datei entstand.
Das Protokoll hätte meinen Fehlschluss über 0011 in einer Zeile beantwortet, statt dass er
zwei Pläne lang stand. Weg B trifft auch den Fall 0011: Ein Paket, das nichts geschrieben
hat, bliebe zu Recht `offen`. **Kein Gate.**

**2. Prüfbefunde werden beschädigt abgelegt.** Unverändert:
`pruefung-0009-…-runde3-2026-09-02.md` ist 0 Byte, `pruefung-0022-…-2026-09-02.md` bricht
nach 17 Zeilen ab und nennt `befunde: 3` — die drei sind verloren und stehen auch nicht in
Git. **Nebenwirkung auf die Konvergenzbremse:** `rueckläufe()` liest das Feld `urteil`; eine
leere Datei trägt keines, ein verlorener Lauf zählt also nicht. 0009 steht deshalb bei zwei
von drei Rückläufen, obwohl es fünf Reviewplätze verbraucht hat. Kein Gate.

**3. Ein TOML-Parser gehört in den Runner.** Unverändert, viermal gemessen über zwei Pakete:
`python3` mit `tomllib` wird in dieser Umgebung abgewiesen, dem Datenbauer wie dem Prüfer.
Abnahme 4 von 0009 und Bedingung 6 von 0017 verlangen gültiges TOML, beide sind bis heute
nur strukturell belegt. Drei Zeilen neben `uebersetzen()`. Kein Gate.

**4. Klasse 2 misst zweierlei — laufende und konstante Preise.** Unverändert die schwerste
offene Sache, Weg steht: **0025 misst, 0026 entscheidet, 0002 wird frei.** 0025 ist seit
diesem Lauf im Review; der Weg ist zum ersten Mal in Bewegung.

**5. Klasse 4 — trägt sie ihren Deckel auch für Regler?** Unverändert offen; fünf
Klasse-4-Schlüssel in `parameter.toml` tragen `>= 0` ohne obere Schranke, obwohl T5 der
Klasse 0 bis 10.000 gibt.

**6. Reihe 9 und R = 19.** Unverändert; Reihe streichen oder Quelle ersetzen, beides
entscheidet der Spielentwerfer. Die drei Varianten sind durchgerechnet, keine reisst
`R ≤ 26`.

**7. Wo die Zustandsausgabe wohnt, und woher sie zwei Spalten nimmt.** Unverändert: 0010
legt die drei Ebenen in `kern`, T13 gibt sie `schnittstelle`; die Abnahme von 0010 verlangt
je Adresse Wert, Skalenklasse *und* Herkunft, während der Kern die beiden letzten nicht
trägt.

**8. Wandert das Vorratsverfahren später aus `pruefstand` heraus?** Unverändert, blockiert
nichts. Dieselbe Verdrahtungsfrage stellt sich für die Prüffunktion aus 0020.

**9. `gebiet.<G>.` gegen `land.<L>.` und `restwelt.` — neu als eigener Punkt.** Zweimal aus
0015-Prüfungen gemeldet, jetzt zum dritten Mal. Solange das Präfix ungeklärt ist, hat die
`basiswechsel`-Familie keine saubere Herleitung; 0030 schreibt die Auflösung hin, **ohne**
die Frage zu beantworten, weil sie `technik.md` berührt. Sie ist damit die dritte offene
Architektenfrage in derselben Datei — nach 0026 (Klasse 2) und Punkt 7. **Alle drei liegen
in `technik.md`, und `technik.md` trägt genau einen Bauplatz gleichzeitig:** Die
Architektenschlange ist die eigentliche Reihenfolgefrage des Vorhabens, nicht die einzelne
Frage darin. Reihenfolge, wie ich sie plane: 0011 (Stack), dann 0026 (Klasse 2, entblockt
0002 und damit `schritt`), dann Punkt 7, dann dieser Punkt. Wer das anders sieht, sagt es
im Vorrang.

## Was quer liegt, aber keine Entscheidung braucht

**Der Vorrang fehlt.** `ops/plan.md` hat in der Fassung vom neunten Lauf keinen Abschnitt
*Vorrang* — meine Rollendatei sagt, er stehe dort mit höchstens fünf Kennungen, und ich
soll mich daran halten oder begründen, warum nicht. Ich habe deshalb nach Startbereitschaft
und Kollisionsfreiheit geplant. Das ist keine Beschwerde: Die vier eingeplanten Pakete sind
die einzigen vier startbereiten, ein Vorrang hätte an diesem Lauf nichts geändert. Ab dem
nächsten wird es anders, sobald der Review Pakete freigibt.

**Der Commit-Betreff ist für dieses Vorhaben keine Zuordnung.** Erneut belegt, diesmal vom
Prüfer statt von mir: Die Arbeit an 0015 lag in Commit `e2383dd` mit dem Betreff
„datenbauer: 0024-notenbanken-unter-reihe-2b"; der Commit mit dem Betreff „0015" berührt die
Datei gar nicht. Zwei Abnahmekriterien schreiben den Nachweis an der Datei inzwischen
ausdrücklich vor.

**Die `.tmp`-Dateien liegen weiter im Repo**, zwei davon in `aufgaben/` (`.kopf.tmp`,
`.paket.tmp`, beide mit `status: gebaut` im Kopf). Unschädlich, weil `startbereit()` über
`glob("*.md")` läuft und sie nicht sieht — die Summe 30 des Trockenlaufs geht ohne sie auf.
Gemeldet, weil es dasselbe Muster ist wie Punkt 2: Zwischenstände, die den Weg ins Repo
finden.

**Die Rohdaten hat niemand.** Unverändert: `daten/` enthält Textbefunde und keine Datenzeile,
deshalb hat der Jahrgangsbau 1997 weiter kein Paket. Kein Gate: `daten.md` sagt für alle vier
tragenden Quellen ausdrücklich keine Registrierung und kein Abonnement. Dieselbe Hand am
Runner wie Punkt 3.

**Fünf Rollen haben kein Paket, und das ist weiter richtig.** `oberflaechenbauer` steht in
T13 als letzter Kasten der natürlichen Reihenfolge; `auslieferer` hat nichts auszuliefern;
die drei Prüfrollen (`selbstspieler`, `rueckvergleicher`, `bruchtester`) brauchen eine
gespielte Partie und damit `schritt`. Allen fünf fehlt eine Voraussetzung **nachweisbar**.

**`kernbauer` hat gerade kein startbereites Paket, und auch das ist richtig:** 0002 und 0003
sind blockiert, 0010 hängt an 0002, und 0027 wartet auf 0023, das dieselben drei
`zustand`-Dateien hält. 0023 ist in diesem Lauf im Review — geht es durch, hat der Kern
wieder Arbeit.

## Die eine Zahl

**Sieben von neun Kernkästen tragen Code, den vierten Lauf in Folge unverändert — und der
Prüfstand hat noch keinen einzigen Test.** `ctest` meldet für `pruefstand` weiter „No tests
were found!!!" bei `ergebnis: ok`. 0019 ist der Weg dorthin und deshalb geteilt worden; die
Bedingung, an der es dreimal vorbeigelaufen ist, ist ab jetzt seine letzte und wichtigste:
**ein Test mit Namen und `Passed` im Übersetzungsbericht.**
