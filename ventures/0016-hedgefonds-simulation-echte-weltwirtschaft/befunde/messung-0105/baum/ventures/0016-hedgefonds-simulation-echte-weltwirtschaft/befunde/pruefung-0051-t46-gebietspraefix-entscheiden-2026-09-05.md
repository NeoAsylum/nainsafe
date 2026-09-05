---
typ: pruefung
paket: 0051-t46-gebietspraefix-entscheiden
pruefer: entwurf-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Alle drei Abnahmebedingungen einzeln nachgewiesen — Fundstellen selbst gezaehlt (17/8/2, Vorher-Spalte arithmetisch am Paketdiff), beide Folgen an den Fremddateien selbst nachgesehen, T46-Tabelle im Gesamtdiff unberuehrt und Adressmenge 310 belegt.
befunde: 0
---

# Pruefung 0051 — T46-Gebietspraefix entschieden

**Vorbemerkung zur Blindpruefung:** Das Paket enthaelt einen Bearbeitungsvermerk des
Architekten mit eigenen Zaehlungen. Ich habe keine seiner Zahlen uebernommen, sondern
jede selbst erhoben — eigene `grep -o`-Zaehlungen am Arbeitsbaum, eigener Diff ueber die
Paketspanne, eigene Stichproben an `daten/adressen.md` und `kern/src/zustand.cpp`.

Die Paketarbeit an `specs/0016-…/technik.md` liegt in drei Commits (`ce59b8b`,
`a127600`, `9e46cfa`); der Dateistand davor ist der von `dffb251` (`git log --oneline --
specs/…/technik.md` zeigt keine fremden Commits dazwischen). Der Gesamtdiff
`git diff -U0 dffb251 9e46cfa -- specs/…/technik.md` hat genau vier Hunks: T17b neu
(104 Zeilen nach Z. 1183), je zwei Zeilen in T39 (Z. 1334) und T28 (Z. 1857) —
Kurzform `gebiet.sektor.preis` durch `gebiet.<G>.sektor.<s>.preis` mit Verweis auf T17b
ersetzt — und acht neue Zeilen **nach** der T46-Tabelle (Z. 1658 ff.). Gegen diesen Diff
und den Arbeitsbaum ist geprueft.

## Bedingung 1 — Festlegung an benannter Stelle, jede Fundstelle aufgeloest: erfuellt

**T17b** (Z. 1184–1286) legt fest: Der Adressbaum hat keinen Knoten `gebiet`;
`gebiet.<G>.` ist eine Sammelschreibweise, die zu `land.US.`/`land.CN.`/`land.DE.`/
`land.BR.` (4 × 44 = 176 Adressen) und `restwelt.` (22) aufloest. Begruendung: vier
Gruende, jeder einzeln nachgesehen — Grund 2 zitiert T45 korrekt (Z. 1589 fuehrt
woertlich „`restwelt.basiswechsel` → 0 (T8)"), Grund 4 rechnet die Gegenrichtung auf
198 von 310 umzubenennende Adressen, was mit dem Blockschnitt in `daten/adressen.md`
uebereinstimmt (Laenderbloecke 1–176 zu je 44, Restwelt 177–198).

**Zaehlung nachher, selbst erhoben** (`grep -o` auf den Arbeitsbaum, Muster als fester
Text): `gebiet.` **17**, `gebiet.<G>.` **8**, `gebiet.<g>.` **2** — identisch mit der
Tabelle in T17b. Alle 17 einzeln kategorisiert:

| Kategorie | Zeilen | Anzahl |
|---|---|---:|
| Platzhalter in T17b selbst | 1184, 1241, 1242, 1243, 1244 | 5 |
| Platzhalter in T46 | 1652 (Tabellenzeile), 1658 (Verweisabsatz) | 2 |
| Platzhalter in T39 / T28 / T48 | 1334 / 1857 / 2086 | 3 |
| Gegenbeispiele, alle in T17b | 1185, 1188, 1194, 1214, 1217, 1218, 1249 | 7 |

Keine unaufgeloeste Stelle, keine Ausnahme. Die Ortsangaben der Fundstellentabelle
stimmen: Z. 1334 liegt in T39 (Abschnitt 1321–1336), Z. 1857 in T28 (1841–1872),
Z. 2086 in T48.

**Zaehlung vorher, arithmetisch am Diff statt am alten Stand** (`git show <hash>^` steht
meinem Werkzeugsatz nicht zur Verfuegung): Der Paketdiff fuegt 15 Treffer der losesten
Form hinzu und entfernt 2, also vorher 17 − 15 + 2 = **4**; bei `<G>` 8 − 7 = **1**, bei
`<g>` 2 − 1 = **1**. Das ist genau die Vorher-Spalte der Tabelle in T17b.

**Die Selbstbezugs-Zusicherung haelt:** Die Zaehltabelle schreibt ihre Muster mit
geschuetztem Punkt (`gebiet\.`), den `grep -oF 'gebiet.'` nicht trifft; kein Treffer
liegt im Zaehlabsatz selbst.

## Bedingung 2 — Beide Folgen beim Namen, kein „vermutlich": erfuellt

Das Wort „vermutlich" kommt in T17b nur einmal vor, als verneintes Zitat („kein
‚vermutlich'"). Beide Folgen selbst nachgesehen:

1. **`daten/adressen.md`:** Die fuenf `basiswechsel`-Zeilen stehen bereits in der
   aufgeloesten Schreibweise mit den laufenden Nummern **44, 88, 132, 176, 198**
   (Dateizeilen 86, 130, 174, 218, 240) — genau wie T17b behauptet („passend,
   unveraendert"). Die Datei ist in keinem der drei Paketcommits enthalten.
2. **`kern/src/zustand.cpp`:** `gebietspraefix()` (Z. 496–505) haengt fuer `gebiet <
   LAENDER` die Kette `land.` + Kuerzel + `.` an, sonst `restwelt.`; der Kommentar
   darueber (Z. 495) sagt es woertlich. „Passend" stimmt, die Datei ist in keinem der
   drei Commits enthalten.

Stichprobe zur 15er-Liste der Sektorpreise: Nr. 4 = `land.US.sektor.1.preis`,
Nr. 188 = `restwelt.sektor.3.preis` — beide tragen einen Sektorpreis, wie T17b abzaehlt.

## Bedingung 3 — Adressmenge 310, T46 unveraendert: erfuellt

Die letzte laufende Nummer in `daten/adressen.md` ist **310** (`partie.mandatsstand`),
und die 310-Summe in `technik.md` (Z. 1630) liegt ausserhalb aller vier Diff-Hunks.
Die T46-Tabelle (Z. 1650–1656, fuenf Datenzeilen mit 5 + 1 + 3 + 1 + 1 = **elf
Adressen**) wird von keinem Hunk beruehrt — keine Zeile faellt weg, keine kommt hinzu;
der neue Absatz beginnt erst nach der Tabelle (Z. 1658).

## Wonach ich sonst gesucht habe, ohne Befund

- **Vollstaendigkeitsbehauptung von T17b** („erscheint in keinem Protokoll, keiner
  Kette, keiner Testvorlage, keiner Oberflaeche"): `grep -r '"gebiet\.'` und
  `grep -rl 'gebiet\.'` ueber `kern/`, `werkzeuge/` und alle `*.cpp/*.hpp/*.toml/*.json`
  des Ventures (ohne `bau/`-Kopien) — **null Treffer**. Die Behauptung haelt.
- **Platzhalter-Konvention** („folgt der Regel fuer `land.<L>.` gegen `land.<l>.`"):
  beide Formen existieren im Dokument (8 bzw. 10 Fundstellen); die Konvention ist real
  benutzt, nicht behauptet.
- **Widerspruch T45/T46/T17b:** Z. 1589 (T45-Beispiel) und die T46-Aufloesung nennen
  dieselbe Adresse `restwelt.basiswechsel` — konsistent.
- **Verbotszone des Pakets** („`daten/adressen.md` nicht anfassen, kein Code"): in den
  `diff --stat` aller drei Commits kommt weder `daten/adressen.md` noch
  `kern/src/zustand.cpp` vor.

## Nebenbemerkung ausserhalb der Abnahme, kein Befund gegen das Paket

Die drei Commits tragen saemtlich den Betreff `architekt: 0051-…`, buendeln aber
erkennbar Arbeit anderer Gewerke und Pakete (u. a. `notizen/testentwickler.md`,
`kern/test/werte_probe.cpp`, `kern/src/werte.cpp`, `festkomma.hpp`, Pakete 0072, 0085,
0088). Fuer diese Pruefung war das folgenlos — der Netto-Diff von `technik.md` ueber die
Paketspanne enthaelt nur 0051-Arbeit —, aber „Ein Lauf, ein Commit" ist damit im
Commitbetreff nicht mehr ablesbar; wer spaeter nach Paket 0085 sucht, findet dessen
Nachweis unter einem 0051-Betreff. Das ist Runner-Verhalten, kein Fehler des
Bauagenten; ich lege kein Paket dafuer an, weil der Projektmanager das Commitverhalten
des Baulaufs kennt und beurteilen kann, ob es Absicht ist.
