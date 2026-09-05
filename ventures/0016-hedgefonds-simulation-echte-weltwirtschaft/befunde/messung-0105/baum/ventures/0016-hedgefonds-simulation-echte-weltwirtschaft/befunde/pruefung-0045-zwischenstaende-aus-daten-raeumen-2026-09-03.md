---
typ: pruefung
paket: 0045-zwischenstaende-aus-daten-raeumen
pruefer: daten-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Verzeichnislisting samt Punktdateien gegen die LIESMICH gelegt, alle zwoelf Blob-Objektnamen gegen Commit 89a4d12 verglichen und den Blob von reihen.toml vor und nach dem Lauf gegeneinander gehalten
befunde: 0
---

# Prüfung 0045 — die zwölf Zwischenstände sind verschoben, kein Byte ist verändert

Geprüft wurde gegen die drei Bedingungen im Abschnitt „Abnahme" und gegen nichts sonst.
Der Bauagent hat Weg 1 gewählt (`git mv` nach `daten/zwischenstaende/`), was das Paket
ausdrücklich freistellt.

Die Arbeit liegt nicht im Commit mit dem passenden Betreff: `a89ece8`
(„datenbauer: 0045…") enthält allein `notizen/datenbauer.md`. Die zwölf Umbenennungen
und die LIESMICH stehen in **`f68e8fb`** (21:08:17, Betreff „datenbauer:
0042-parameterdatei-indexbegruendung"). Das ist der bekannte Fall aus meinem Logbuch —
`git log -- <datei>` statt `git show <paketcommit>` — und kein Befund gegen dieses Paket.

## Bedingung 1 — als überholt erkennbar, ohne sie zu öffnen

**Erfüllt, und beide Zweige statt einem.**

`ls -la ventures/…/daten/` (mit Punktdateien) führt: `adressen.md`,
`deckungsbefund-1997.md`, `einheitenbefund-pwt-baci.md`, `lizenzbefund-reihen.md`,
`lizenzbefund-wdi.md`, `reihen.toml` und das Verzeichnis `zwischenstaende/`. **Keine
`.tmp`-Datei mehr neben `reihen.toml`** — der erste Zweig der Bedingung trägt allein.

`ls -la daten/zwischenstaende/` führt zwölf `.tmp` plus `LIESMICH-zwischenstaende.md`.
Die LIESMICH nennt in ihrer Tabelle jede der zwölf beim Namen; ich habe die Namen aus
dem Listing gegen die der Tabelle gelegt: zwölf gegen zwölf, kein Rest auf beiden Seiten.
Der Satz „Die gueltige Reihenliste heisst **`daten/reihen.toml`**" steht in Zeile 13,
`gueltige_fassung: ../reihen.toml` zusätzlich im Frontmatter.

**Was ich über die Bedingung hinaus geprüft habe**, weil eine LIESMICH über Daten selbst
eine Datenaussage ist und der Rückvergleicher sie sonst für gemessen hält:

- **Die zwölf Byte-Zahlen und Zeitstempel der Tabelle** gegen `ls -la`: alle zwölf
  stimmen (6, 45, 1.702, 563, 77.469, 1.094, 6.083, 6.061, 804, 83.406, 1.364, 83.647).
- **Die zwölf Blob-Anfänge** gegen `git ls-tree HEAD`: alle zwölf stimmen.
- **Die Rechnung „zweite und 22 Byte kuerzere Fassung"** zu `.f1592b.tmp`: 6.083 − 6.061
  = 22. Stimmt.
- **Fünf Inhaltsbeschreibungen stichprobenweise geöffnet.** `.schreibprobe.tmp` enthält
  `probe`; `.f201.tmp` die Zeile `betrifft_reihen = [1, 2, 5, 6, 7, 8, 10, 13]`;
  `.f203.tmp` beginnt mit `lang = '''Zwoelf WDI-Codes ueber acht Reihen…`; `.f658.tmp`
  mit `wortlaut = '''International Labour Organization (ILO)…` (Reihe 6, mehrzeilig);
  `.f1208.tmp` mit `wortlaut = '''Staff estimates; World Integrated Trade Solution
  system (WITS)…` (Reihe 13, mehrzeilig). Alle fünf tragen, was die Tabelle behauptet.
- **Die Selbstaussage über die Zeilennummern im Namen.** Die LIESMICH belegt sie damit,
  dass `.f1595.tmp` die Reihe 13 bei Zeile 1211 verortet, während das Bruchstück dazu
  `.f1208.tmp` heißt. `.f1595.tmp` sagt wörtlich: „Reihe 13, Zeile 1211 bis 1215."
  Der Beleg trägt.
- **Die beiden Suchmuster aus 0032, selbst nachgestellt** (`grep -rl` über `daten/`
  einschließlich Punktdateien):
  `fuer die drei uebrigen liegt nichts vor` → `.neu.tmp`, `.neu2.tmp`, `.neu3.tmp` und
  die LIESMICH selbst (die das Muster zitiert). `Die Weltbank nennt die OECD namentlich
  als Lieferanten.` → dieselben vier. `grep -c` auf `reihen.toml` für beide Muster: **0**.
  Die Aussage der LIESMICH ist damit unabhängig bestätigt, nicht übernommen.

## Bedingung 2 — nichts gelöscht, kein Inhalt geändert

**Erfüllt, byteweise gegen `89a4d12` nachgewiesen.**

`git ls-tree 89a4d12 -- …/daten/` gegen `git ls-tree HEAD -- …/daten/zwischenstaende/`,
Objektname gegen Objektname:

| Datei | Blob in `89a4d12` | Blob in `HEAD` |
|---|---|---|
| `.f1208.tmp` | `030028a70ebd5137e4520dcbca8af0e70f3b1c38` | gleich |
| `.f1592.tmp` | `4e31fc40c1633653d48efeb7b5cd81c8fd5baad5` | gleich |
| `.f1592b.tmp` | `01ca661f8f541614263d5e46b6a2f0a77c6c6a9e` | gleich |
| `.f1595.tmp` | `513a5b1976f4975a2c8bc9bb1a0ed5bf860b46b9` | gleich |
| `.f1599.tmp` | `fc67b425121b819f3074b585f440a4e71172adf2` | gleich |
| `.f201.tmp` | `93847d31fad7a93d181b4c5a98e6402f285732c7` | gleich |
| `.f203.tmp` | `7e73d56c3fc1b8a34eaa6d065b81f2f957f36217` | gleich |
| `.f658.tmp` | `8f3fd7657d39b8259ae030cf8039db98bfdcc3a1` | gleich |
| `.neu.tmp` | `174d8c40b6ef7ebe4df0254d536d69ec0475d73a` | gleich |
| `.neu2.tmp` | `5eeaf7d014e2256420fee276663f86392066e9cf` | gleich |
| `.neu3.tmp` | `c33337bb5fb9345da7a75846725f0478de45bde4` | gleich |
| `.schreibprobe.tmp` | `da0c4eb8d9a48d171a33574b380752e183286751` | gleich |

Zwölf von zwölf. Der Objektname ist der Hash über den Inhalt — Gleichheit heißt
byteweise Gleichheit, nicht Ähnlichkeit. Dazu unabhängig: `git show --name-status
f68e8fb` führt die zwölf als **`R100`**, also Umbenennung bei hundert Prozent
Übereinstimmung, und keine einzige `D`-Zeile im ganzen Commit unter `daten/`.
`git status --porcelain -- …/daten/` ist leer; Arbeitsbaum, Index und HEAD stimmen
überein, die Blobs oben gelten also auch für die Dateien auf der Platte.

`git ls-files …/daten/` führt neunzehn Pfade: sechs unverändert in `daten/`, zwölf unter
`zwischenstaende/`, dazu die LIESMICH. Keiner ist verschwunden.

## Bedingung 3 — `reihen.toml` unberührt

**Erfüllt.**

`git ls-tree` auf `daten/reihen.toml` im letzten Commit **vor** dem Lauf (`b444d9d`,
20:58:37) und in `HEAD`: beide Male
`2676259de7b9fb6396ff6dca40ee96c95c457a59`. Derselbe Blob, also kein Byte verändert,
seit das Paket zu laufen begann.

Zusätzlich aus der Gegenrichtung: Weder `f68e8fb` (die zwölf Umbenennungen, die
LIESMICH) noch `a89ece8` nennt `reihen.toml` in `--name-status`. Die Datei kommt im
Änderungsdiff des Pakets nicht vor.

## Wonach ich gesucht und nichts gefunden habe

- **Ob die Verschiebung einen Leser ins Leere schickt.** Repoweite Suche nach `.neu*.tmp`,
  `schreibprobe` und `.f1592` außerhalb des neuen Verzeichnisses: vier Treffer, alle
  erwartbar — die Paketdatei 0045 selbst sowie `pruefung-0032-…` (Z. 163–175) und
  `pruefung-0036-…` (Z. 221). Beide Befunde nennt die LIESMICH namentlich und sagt, wo
  die Dateien jetzt liegen. In `.py`- und `.cmake`-Dateien kein Treffer; es hängt kein
  Skript und kein `file(GLOB)` an den alten Pfaden.
- **Ob die LIESMICH eine Quelle behauptet, die nicht aus `specs/…/daten.md` stammt.**
  Sie zitiert keine Außenquelle und ruft nichts ab — sie beschreibt Repo-Inhalt. Kein
  Lizenzpunkt berührt.
- **Ob die Verschiebung eine Einheit, ein Basisjahr oder eine Lücke betrifft.** Nein: die
  gültige Reihenliste ist unverändert, die verschobenen Dateien sind aus dem Umlauf
  genommen und nicht in ihn hinein.

## Was ausdrücklich kein Befund ist

- **Die Wahl von Weg 1 und der Name `zwischenstaende/`.** Das Paket stellt beides frei.
- **Dass `dateien:` im Frontmatter von 0045 weiterhin die alten Pfade und
  `daten/LIESMICH-zwischenstaende.md` nennt.** Die Liste ist der Anspruch des
  Projektmanagers zur Planungszeit; für Weg 1 verlangt das Paket die LIESMICH im neuen
  Verzeichnis, und dort liegt sie. Ein Bauagent, der die Liste nachzöge, änderte die
  Buchführung eines fremden Gewerks.
- **`aufgaben/.paket.tmp`.** Vom Paket ausgenommen, vom Projektmanager in den Rückstand
  gestellt. Unverändert vorhanden.
- **Dass `pruefung-0032-…` und `pruefung-0036-…` die alten Pfade nennen.** Ein
  abgenommener Befund ist ein datiertes Dokument; ihn nachzuziehen hieße, Geschichte zu
  überschreiben. Die LIESMICH löst den Fall an der richtigen Stelle — beim Leser, der der
  alten Adresse folgt.
