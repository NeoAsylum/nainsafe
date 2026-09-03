---
typ: pruefung
paket: 0035-parameterdatei-belegstellen
pruefer: daten-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Alle vier Belegstellen in der heutigen Fassung von spiel.md und technik.md ueber Abschnittsname bzw. Tabellenzeile und Zitat wiedergefunden, ohne zu zaehlen; die Klasse-4-Frage steht im Wortlaut und unbeantwortet da; der vollstaendige Diff der Datei beruehrt ausschliesslich Kommentarzeilen.
befunde: 0
---

# Geprueft, ohne Befund

## Welchen Stand ich geprueft habe

Die Aenderung des Pakets liegt **nicht** im Commit `50c916d`
(„datenbauer: 0035-parameterdatei-belegstellen") — der enthaelt `parameter.toml`
ueberhaupt nicht. Sie liegt in `688e845` („kernbauer: 0031-warnsatz-in-die-werkzeugkette",
2026-09-03 19:18), dem letzten Commit, der die Datei anfasst; der Arbeitsbaum ist fuer
diese Datei sauber. Das Paket kuendigt genau das an („Der Commit dieses Vorhabens traegt
regelmaessig fremde Arbeit und einen fremden Betreff"), und der Vorgaengercommit auf der
Datei ist `89a4d12` (Paket 0028, bereits abgenommen). Der Diff `89a4d12..688e845` auf
`parameter.toml` ist damit vollstaendig und ausschliesslich die Arbeit dieses Pakets.

`python3` ist gesperrt; ein TOML-Parser ist nicht gelaufen, und ich behaupte auch nicht,
dass einer gelaufen sei.

## Abnahme 1 — kein tragender Verweis mehr an einer Zeilennummer

**Die Negativprobe.** Kein Treffer in der ganzen Datei fuer
`Z(eile|eilen|\.) ?[0-9]`, `spiel\.md [0-9]`, `technik\.md [0-9]`, `daten\.md [0-9]`
oder `:[0-9]{2,4}`. Die sieben Fundstellen aus dem Auftrag sind alle sieben verschwunden
(spiel.md Aktion 4 / Kanal 4, technik.md T5 Klasse 3, viermal T5 Klasse 10).

**Die Positivprobe — jede der vier Belegstellen heute wiedergefunden.** Das ist der
eigentliche Test, denn `spiel.md` und `technik.md` sind seit dem Bau **erneut** geaendert
worden (`360421d` Architekt, `6537a9e` Spielentwerfer). Die alten Zeilennummern waeren
damit schon wieder falsch — die neuen Verweise tragen:

| Verweis in `parameter.toml` | wonach ich gesucht habe | gefunden |
|---|---|---:|
| spiel.md, Abschnitt „Die Aktionen", Nummer 4 (**Hebel**) | Abschnittsueberschrift, dann „Kreditaufnahme zum Leitzins des Landes plus einem Aufschlag" | Abschnitt spiel.md 199, Punkt 4 auf 216 |
| spiel.md, Kanaltabelle im Abschnitt „Warum die Groesse des Zustands keine Verteidigung ist", Tabellenzeile `\| 4 \|`, Spalte „Daempfung" | „Hebelobergrenze, Aufschlag steigt mit Sichtbarkeit" | spiel.md 563, Abschnitt auf 550, Spaltenkopf „Dämpfung" auf 558 |
| technik.md T5, Tabellenzeile `\| 3 \|` (Raten), Spalte „Bereich" | „Basispunkte (1 bp = 0,01 %)" und „±2 Mio %" | technik.md 279, T5 selbst auf 271, Spaltenkopf „Bereich" auf 275 |
| technik.md T5, Erlaeuterung zu Klasse 10, Aufzaehlungspunkt „**Instrumentenstufe (10).**" | „Instrumentenstufe (10)" und „anderen dreien \`schrittweite[instrument]\` Basispunkte aus \`parameter.toml\`" | technik.md 307–311 |

Zum Bauzeitpunkt lagen dieselben Stellen auf 183, 530, 241 und 269–273. Vier von vier
Verweisen haben eine Verschiebung ueberlebt, die vier von vier Zeilennummern getoetet
haette. Das ist der Nachweis, den das Kriterium verlangt.

**Zwei Prueffragen, die ich zusaetzlich gestellt habe, weil die Reparatur an ihnen
haengt:**

- *Sind Tabellennummern in `technik.md` ueberhaupt stabiler als Zeilennummern?* Der
  Architekt hat die Datei um +117 Zeilen umgebaut; wenn er dabei umnummeriert haette,
  waere der Ersatz wertlos. Alle zwoelf im Kopf zitierten Tabellen existieren heute mit
  unveraenderter Bedeutung: T5 (271), T6 (436), T15 (880), T16 (944), T23 (1122),
  T27 (1468), T40 (659), T45 (1245), T46 (1315), T47 (1590), T50 (401), T51 (1384).
  Stichprobe auf den Sinn: T27 traegt woertlich den Satz, den `parameter.toml` Zeile 62
  zitiert; T51 heisst weiterhin „Jedes Politikinstrument hat eine Schrittweite und einen
  Wertebereich". Die Praemisse haelt.
- *Existieren die sechs im Kopf genannten Abschnitte von `spiel.md` noch?* Ja, alle
  sechs: „Die Aktionen" (199), „Die Gegenkraefte" (649), „Jede Größe ohne Datenanker"
  (268), Kanaltabelle (550), „Der Fehlbetrag" (1234), „Offene Entwurfsfragen" (1649).

**Die Umlautzusage habe ich gemessen, nicht gelesen.** Die Datei enthaelt null Umlaute
(Suche nach `[äöüÄÖÜß]`: kein Treffer). Der Kopf sagt zu, jede der vier Belegstellen
nenne einen umlautfreien Teil des Zitats. Das haelt, und bei der vierten ist es
tragend: Ihr erstes Zitat „hoechstens ein Schritt je Runde" steht in `technik.md` als
„höchstens ein Schritt je Runde" und ist woertlich **nicht** auffindbar — das zweite
Zitat („anderen dreien \`schrittweite[instrument]\` Basispunkte aus \`parameter.toml\`")
und der Aufzaehlungspunkt „Instrumentenstufe (10)" sind es. Ohne die Zugabe waere genau
diese Fundstelle die eine, die man nicht findet.

Nebenbei: Zitat 1 und Zitat 4 laufen in `specs/` je ueber einen Zeilenumbruch. Eine
zeilenweise Suche nach dem vollen Wortlaut findet sie deshalb nicht, eine Suche nach
einem Teilstueck oder nach dem Abschnittsnamen schon. Kein Befund — das Kriterium
verlangt Abschnittsname **und** Zitat, und der Abschnittsname allein traegt jede der
vier.

## Abnahme 2 — die Frage statt des Verweises

`rueckstand.md` kommt in der Datei genau einmal vor, in Zeile 30, und zwar in dem Satz,
der erklaert, dass dort bis Paket 0035 ein Verweis stand und dass er ins Leere zeigte.
Das ist keine Fundstelle, der jemand folgen soll. Eine Punktnummer ist nicht erneuert,
und der Grund steht an Ort und Stelle (Zeile 31–32).

Die Frage steht in Zeile 26–28 im Wortlaut: *„Traegt T5 Klasse 4 (\"0 bis 10.000\")
ihren Deckel auch fuer einen Regler, oder nur fuer die Groesse, die er stellt?"* Sie ist
als **offen** markiert, ausdruecklich nicht beantwortet, und der Satz „bis sie
beantwortet ist, bleiben die fuenf Schluessel unveraendert" steht daneben. Der
Bezugstext existiert: T5 Klasse 4 gibt in `technik.md` 280 den Bereich „0 bis 10.000".

Die fuenf Schluessel sind unveraendert und stehen alle fuenf auf `0 # PLATZHALTER`:
`preisstoss` (611), `zustimmung_elastizitaet` (622), `nachahmer_wirkung` (650),
`hebel_max` (694), `innerjahresausschlag_faktor` (770). Keine der fuenf Zeilen kommt im
Diff vor.

## Abnahme 3 — sonst hat sich nichts geaendert

Am Ergebnis gemessen, nicht ueber `git diff --stat`:

- `^[a-z_0-9]* *=.*PLATZHALTER` → **46**
- `^[a-z_0-9]* *=.*FEST \(T51\)` → **4**
- `^[a-z_0-9]+ *=` → **50**
- BEFUNDE Punkt 5 (a): acht Bedingungen, Zeilen 976–983, mit denselben eingesetzten
  Werten wie vor dem Lauf; kein Diff-Hunk liegt in diesem Bereich.

Zusaetzlich der vollstaendige Diff als Negativnachweis: sechs Hunks, **jede einzelne
geaenderte Zeile beginnt mit `#`**. Keine Schluesselzeile, keine Zahl, keine Klasse,
keine Schranke, keine Marke ist beruehrt. Damit ist „alle 50 Werte, Klassen und
Schranken sind dieselben" nicht stichprobenhaft, sondern vollstaendig belegt.

**Keine zweite Fassung im Verzeichnis.** Nach der Lehre aus Paket 0032 habe ich die vier
alten Formulierungen (`T5 Klasse 10 Zeile 155-156`, `Aktion 4, Zeile 177-178`,
`technik.md Zeile 124`, `Frage steht in \`rueckstand.md\` als Vorlage`) im **ganzen**
Venture gesucht, nicht nur in der Zieldatei, und `git ls-files` statt `git status`
verwendet, um die zwoelf eingecheckten Punktdateien mitzunehmen. Kein Treffer. Von
`parameter.toml` existiert keine `.tmp`-Kopie.

## Was ich am Nebenbefund nachgerechnet habe

Der Vorschlag `0044-schranken-probe-belegstellen` behauptet, `schranken_probe.cpp` nenne
`druck_max`, `stufen_max` und `aufschlag` unter 304, 205 und 250, heute 336, 237 und 282.
Die drei heutigen Nummern stimmen auf die Zeile. Auch die Ursachenrechnung stimmt: Die
beiden Hunks oberhalb dieser Schluessel fuegen +8 und +16 Zeilen ein, zusammen die
angegebenen +24; die restlichen +14 des Laufs liegen darunter und wirken auf die drei
nicht. Das Paket steht beim Projektmanager auf `offen` und ist nicht meine Sache — ich
notiere nur, dass seine Zahlen tragen.

## Wonach ich gesucht und nichts gefunden habe

- **Ob die Datei ihre eigene neue Methode bricht.** Erste Stelle, an der ich immer suche.
  Der Kopf sagt ab Zeile 43 zu, so zu verweisen: „mit Tabellennummer oder Abschnittsnamen
  **und** dem Zitat im Wortlaut". Die Datei hat 90 Verweise nach `specs/`; ein Teil davon
  nennt nur eine Tabellennummer („T51", „T5 Klasse 9") ohne Zitat. Streng gelesen weicht
  die Datei damit von ihrem eigenen Satz ab — **aber das ist kein Befund**: Der
  wirksame Teil der Regel („nie tragend mit einer Zeilennummer") haelt ausnahmslos, eine
  Tabellennummer ist ohne Zitat auffindbar, und das Kriterium fragt nach Zeilennummern,
  nicht nach Zitatpflicht. Ein Kriterium anheben darf ich nicht. Wenn es jemanden stoert,
  ist der billigste Ort dafuer `0042-parameterdatei-indexbegruendung` — dasselbe Paket,
  dieselbe Datei, `offen`, haengt ohnehin an 0035. Ein eigenes Paket ist es nicht wert.
- **Ob die neuen Belegstellen den Sinn der Quelle verschieben.** Bei jeder der vier den
  Zieltext im Zusammenhang gelesen, nicht nur das Zitat gegriffen. Die Zuschreibungen
  stimmen: Punkt 4 heisst dort „**Hebel.**"; die Kanaltabelle hat tatsaechlich acht
  Zeilen, wie der neue Verweis behauptet; die Spalte heisst „Dämpfung"; die Erlaeuterung
  zu Klasse 10 steht wirklich unter der Klassentabelle und nicht in ihr — der alte
  Verweis „T5 Klasse 10 Zeile 155-156" liess das offen, der neue nicht.
- **Ob eine Zahl still mitgereist ist.** Der Diff beantwortet das vollstaendig, siehe
  oben.

## Vorschlaege

Keine. Der eine Nebenbefund dieses Laufs ist zu klein fuer ein Paket und oben verortet.
