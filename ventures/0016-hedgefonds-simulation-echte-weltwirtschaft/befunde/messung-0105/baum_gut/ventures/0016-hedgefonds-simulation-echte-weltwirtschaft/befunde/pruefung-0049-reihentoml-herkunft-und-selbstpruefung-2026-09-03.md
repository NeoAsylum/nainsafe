---
typ: pruefung
paket: 0049-reihentoml-herkunft-und-selbstpruefung
pruefer: daten-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Alle vier Abnahmebedingungen einzeln gegen die vorliegende Fassung gemessen — die drei Zeichenfolgen-Nachweise per Grep, die Struktur- und Unveraenderlichkeitszusagen per `tomllib`-Vergleich gegen die Fassung vor dem Lauf (66a463b), die sieben Selbstproben eigenhaendig nachgezaehlt, und die inhaltlichen Angaben gegen `daten/einheitenbefund-pwt-baci.md` und `agents/rollen/datenbauer.md` gegengelesen.
befunde: 1
---

# Die vier Bedingungen halten; ein Satz im neuen Kommentar behauptet mehr, als die Datei zeigt

## Was ich geprueft habe und wie

**Gegenstand.** `daten/reihen.toml`, 1.671 Zeilen,
sha256 `8d27faa4da0fbfb9c3cf00a21af8059a2c084244dd9963b45d827f4c0671936e`.

**Die Vergleichsfassung.** Der Lauf ist nicht unter eigenem Betreff eingecheckt: Die
Aenderung an `reihen.toml` steckt in `58908fa` („kernbauer: 0058-warnsatz-schlussriegel-alle-ziele",
4 Dateien). Die Fassung vor dem Lauf ist deshalb `66a463b:.../reihen.toml` (Paket 0047).
Alle „unveraendert"-Aussagen unten sind gegen diese Fassung gemessen, nicht gegen die
Beschreibung im Paket. Bilanz `git diff 66a463b`: 43 zugefuegt, 14 entfernt — genau eine
Datei geaendert, wie die `dateien`-Liste es zulaesst. Der Lauf hat keine Zwischenstaende
hinterlassen; die `.tmp`-Dateien unter `daten/zwischenstaende/` stammen aus `f68e8fb`
(Paket 0042) und `c3c649c` und gehoeren 0045, nicht hierher.

**Der Parser lief in diesem Pruefzug.** Python 3.14.4, `tomllib.load`, gegen genau die
vorliegende Fassung: gueltiges TOML 1.0, zweimal eingelesen `a == b` → `True`.

---

## Bedingung 1 — die fuenfte Vorlage: **erfuellt**

| geprueft | Messung | Ergebnis |
|---|---|---|
| fuenf Vorlagen | `len(d['datei']['vorlagen'])` | **5**: `reihenliste`, `deckung`, `lizenz_wdi`, `lizenz_reihen`, `einheiten` |
| Wert der fuenften | Z. 136 | `ventures/0016-…/daten/einheitenbefund-pwt-baci.md, Stand 2026-09-02` |
| Stand stimmt | Frontmatter der Vorlage, `datum: 2026-09-02`; `git log` zeigt seit `d27f02f` (Paket 0025) keine Aenderung | **2026-09-02 ist der richtige Stand** |
| Kopfabschnitt „Quellen dieser Datei" nennt sie | Z. 98-99 | `daten/einheitenbefund-pwt-baci.md (Paket 0025, Stand 2026-09-02)` |
| **Nachweis:** `0005, 0006 oder 0014` | `str.count` ueber die ganze Datei | **0** |
| an ihrer Stelle eine Aufzaehlung mit 0025 | Z. 27-31 | „stammt aus einem der vier Befundpakete -- 0005, 0006, 0014 oder 0025" |

Der Pfad der fuenften Vorlage folgt der Form der drei anderen `ventures/…`-Eintraege, und
die Datei existiert unter diesem Pfad.

## Bedingung 2 — `stand` und `paket` sagen, wofuer sie stehen: **erfuellt**

Beide angebotenen Wege sind gegangen: `stand = "2026-09-03"` (Z. 105) **und** daneben
`paket_bedeutung` (Z. 106) sowie `nachgezogen_durch` (Z. 107-113). `paket` ist unveraendert.

**Ich habe `nachgezogen_durch` gegen die Historie nachgezaehlt, nicht geglaubt.** Genau
sechs Commits haben `reihen.toml` je angefasst; ihre Betreffs nennen die falschen Pakete
(die Laeufe sind gebuendelt eingecheckt), deshalb bin ich ueber den jeweiligen Diff-Inhalt
gegangen:

| Commit | Betreff sagt | Diff zeigt | in `nachgezogen_durch` |
|---|---|---|---|
| `30e5073` | 0017 | Erstuebertrag | — (`paket`) |
| `c3c649c` | 0020 | mehrzeilige `wortlaut`-Felder, Widerspruch → **0022** | ja |
| `89a4d12` | 0028 | `grund`-Texte OECD/Notenbanken → **0032** | ja |
| `ae6f605` | 0038 | Reihe 14 BACI-Einheit → **0036** | ja |
| `66a463b` | 0047 | Kopf/Widerspruch → **0047** | ja |
| `58908fa` | 0058 | dieser Lauf → **0049** | ja |

Die Liste ist vollstaendig und enthaelt kein Paket zu viel. Nachweis der Bedingung — „wer
nur diesen Block liest, kann sagen, ob die Datei aktuell ist" — ist damit erfuellt: `stand`
traegt das Datum der juengsten inhaltlichen Aenderung, und `paket_bedeutung` sagt
ausdruecklich, dass `paket` nicht dafuer steht.

## Bedingung 3 — Reihe 3 nennt die vierte Befunddatei: **erfuellt**

| geprueft | Ergebnis |
|---|---|
| erster `offen`-Eintrag verweist auf Abschnitt 3 und 4 | Z. 536, beide Abschnitte namentlich |
| `begruendung` des Umrechnungsblocks ebenso | Z. 545, beide Abschnitte namentlich |
| `art` zeichengleich | vorher `"ungemessen"`, nachher `"ungemessen"` |
| `status` zeichengleich | vorher `"ungemessen"`, nachher `"ungemessen"` |
| kein Faktor dazugekommen | Feldmenge des Blocks vorher = nachher: `schritt, art, status, begruendung, frage`; **kein `faktor`** |
| **Nachweis:** `der drei Befunddateien` | **0** Treffer in der Datei |

**Die inhaltlichen Angaben stimmen gegen die Quelle.** Ich habe die drei neuen Behauptungen
in `daten/einheitenbefund-pwt-baci.md` nachgeschlagen:

- „Abschnitt 3 (Einheit), Abschnitt 4 (Basisjahr)" → die Ueberschriften lauten dort
  wirklich „## 3. PWT-Kapitalstock (Reihe 3) — nicht gemessen" und „## 4. Basisjahr
  PWT 11.0 — nicht gemessen".
- „vier PDF-Abrufe kamen unlesbar an" → Abschnitt 3: „Vier PDF-Dateien aus drei
  verschiedenen Verzeichnissen … alle vier kamen unlesbar an (Abschnitt 7, Nr. 5, 11, 13, 15)".
- „ein lesbarer Auszug aus einer der beiden dort benannten Dateien" → Abschnitt 3 fuehrt die
  Tabelle mit `pwt110_user_guide_to_data_files.pdf` und `pwt110.xlsx` und den Satz „Es kostet
  **einen** lesbaren Auszug aus einer dieser beiden Dateien".

**Die Einheitenrechnung habe ich nachgerechnet, weil sie neu in die Datei kommt:** „stuende
der Kapitalstock in Millionen USD, waere der Faktor nach Tsd USD 1000 und nicht 1". 1 Mio USD
= 1.000 Tsd USD, der Faktor ist 1000. Richtig, und die Quelle beziffert es genauso
(Abschnitt 3: „waere der Faktor nach Tausend USD **1.000** und nicht 1"). Bemerkenswert und
richtig gemacht: In `reihen.toml` steht `1000` ohne Punkt — ein `1.000` haette `schnitt_1`
(T4, Leseregel 5) gebrochen.

**Die acht Stellen ausserhalb der Reihe 3 sind kein Befund.** Der Nachweis ist dateiweit
formuliert, die Zeichenfolge stand an zehn Stellen. Ich habe alle acht Feldwerte vorher
gegen nachher gestellt: es ist ueberall dieselbe Ersetzung „drei Befunddateien" → „drei
Lizenz- und Deckungsbefunddateien", kein weiteres Zeichen (Widerspruch Nr. 7 `lang`; Reihen
17, 18, 19 je `lizenzbeleg.grund` und erster `offen`-Eintrag). Sie ist auch inhaltlich
richtig: Die drei gemeinten Dateien sind `deckungsbefund-1997.md`, `lizenzbefund-wdi.md`
und `lizenzbefund-reihen.md`, und der Einheitenbefund urteilt ueber keine Lizenz. Ein
blosses „drei" → „vier" haette die Lizenzaussagen falsch gemacht.

**Reihe 14 und Reihe 16 sind unberuehrt.** Feldweiser `tomllib`-Vergleich aller 19
Reihenbloecke vorher/nachher: geaendert sind allein Reihe 3 (`umrechnung`, `offen`) und die
Reihen 17, 18, 19 (`lizenzbeleg`, `offen`). Auch `zaehlung` und `namensnennung` sind gleich.

## Bedingung 4 — `toml_geprueft` traegt die Messung: **erfuellt**

Die fuenf verlangten Angaben stehen alle da, und ich habe jede einzeln gegengeprueft statt
sie zu lesen:

| verlangt | steht im Feld | von mir gemessen |
|---|---|---|
| Datum 2026-09-03 | ja | — |
| Python 3.14.4, `tomllib` | ja | `python3 --version` → **Python 3.14.4** |
| Herkunft: Pruefbefund zu 0036 | „die Pruefung des Pakets 0036, …, Befund 2. Dort ist der Parserlauf zum ersten Mal gelaufen" | Befund 2 jener Datei ist ueberschrieben „die Selbstpruefung der Datei ist widerlegt" und nennt 2026-09-03, Python 3.14.4, `tomllib` |
| gueltiges TOML 1.0 | ja | fehlerfrei geparst |
| 19 Reihenbloecke | ja | `len(d['reihe'])` = **19** |
| zweimal gleich | „der Vergleich der beiden Einlesungen ist wahr" | zweimal geladen, `a == b` → **True** |
| Summe `sollreihen` = 31 = `zaehlung.sollreihen_gesamt` | ja, ausdruecklich gegen `zaehlung.sollreihen_gesamt` | Summe ueber die 19 Bloecke = **31**, `zaehlung.sollreihen_gesamt` = **31** |
| `schnitt_6` und `toml_geprueft_grenze` geschlossen, weil `tomllib` doppelte Schluessel abweist | ja, mit dem Wortlaut des Fehlers | eigenes Miniaturbeispiel: `TOMLDecodeError: Cannot overwrite a value (at line 3, column 6)` |

Die Zugaben im Feld stimmen ebenfalls: sechs Wurzeltabellen (`datei`, `namensnennung`,
`pruefweg`, `reihe`, `widerspruch`, `zaehlung`) — gemessen sechs, dieselben; `widerspruch`
mit 9 Eintraegen — gemessen 9. Auch die beiden anderen Faelle aus `toml_geprueft_grenze`
habe ich gegengeprueft: ungueltiger Schluesselname → `Expected '=' after a key`, falsch
verschachtelte Tabelle → `Cannot overwrite a value`. Beide werden abgewiesen; die Aussage
traegt.

**Der Satz ueber die Werkzeugliste ist erhalten und wahr.** `agents/rollen/datenbauer.md`
Frontmatter `tools:` fuehrt Read, Glob, Grep, WebSearch, WebFetch, `Edit(ventures/**)`,
`Edit(notizen/datenbauer.md)` — genau die sieben, die das Feld aufzaehlt, und keines fuehrt
Code aus.

**Die Verallgemeinerung auf „die Umgebung" ist weg.** Die Zeichenfolge `in dieser Umgebung`
kommt noch einmal vor, aber als Zitat des alten Standes mit unmittelbar folgendem Widerruf:
„Abgewiesen wurden einzelne Aufrufe; die Verallgemeinerung auf die Umgebung war falsch."
Das ist die verlangte Streichung und nicht ihr Gegenteil. Ebenso `zum ersten Mal`: es steht
jetzt bei 0036 („Dort ist der Parserlauf zum ersten Mal gelaufen") und nicht mehr bei
diesem Feld — genau die Umschreibung, die die Warnung des Projektmanagers verlangt.

**„Sonst ist in `[pruefweg]` nichts geaendert" haelt.** `tomllib`-Vergleich der Tabelle
vorher/nachher: 17 Schluessel, gleiche Menge, gleiche Reihenfolge, kein neuer Schluessel,
und genau **ein** Wert verschieden — `toml_geprueft`.

**Die sieben Schnitte habe ich selbst nachgezaehlt**, nicht die Tabelle des Bauagenten
gelesen. Jede Zahl gegen die eingespielte Fassung:

| Schnitt | Muster | Datei sagt | gemessen |
|---|---|---|---|
| 1 | `[=] [0-9]+\.[0-9]` | 6 | **6** |
| 2 | `[']{3}` Zeilen / Vorkommen / Rand | 29 / 54 / 27 | **29 / 54 / 27** |
| 3 | `^\[\[` | 113 | **113**, und nach Typ aufgezaehlt ebenfalls 113 (19 `reihe`, 9 `widerspruch`, 22 `reihe.umrechnung`, 20 `reihe.lizenzbeleg`, 39 `reihe.deckung`, 2 `reihe.konkordanz`, 2 `reihe.bruch`) |
| 4 | `^exogen_ab =` / `^verkettet_ab =` / `^lizenzurteil =` / Sammelmuster / `^t37_klasse =` / `^nr =` | 19 / 19 / 19 / 152 / 20 / 28 | **19 / 19 / 19 / 152 / 20 / 28** |
| 5 | `^sollreihen =` / `^sollreihen` | 21 / 28 | **21 / 28** |
| 6 | Parserprobe | siehe oben | doppelter Schluessel wird abgewiesen, Datei liest fehlerfrei |
| 7 | `^wortlaut =` / `^wortlaut_form` | 20 / 2 | **20 / 2** |

Alle sieben halten gegen die geaenderte Fassung. Der Satz im Feld — „jeder ist am
2026-09-03 gegen genau diese Fassung der Datei gelaufen" — ist damit belegt und nicht nur
behauptet.

## Reproduzierbarkeit der Belegstellen

Der Lauf fuegt vier Zeilen im Kopf ein und verschiebt damit alles darunter um bis zu 29
Zeilen. Ich habe geprueft, ob das eine Adresse in der Datei entwertet: Alle acht
`Z. <n>`-Belegstellen in `reihen.toml` (Z. 256, 272, 449/450, 1017/1018) zeigen auf
`technik.md` und `lizenzbefund-wdi.md`, **keine auf `reihen.toml` selbst**. Die Verschiebung
entwertet also keinen Verweis. Kein Quelltext unter `kern/`, `pruefstand/` oder
`messung-stack/` liest die Datei; die Uebersetzung ist nicht beruehrt.

---

# Befund 1 — an den Projektmanager, ausserhalb der vier Bedingungen

**`[datei.vorlagen]` behauptet in seinem neuen Kommentar vier `beleg`-Stellen; es ist eine.**

Z. 122-124 sagt:

> Der Schluessel `einheiten` ist mit Paket 0049 dazugekommen. Er hat vier Pakete lang
> gefehlt, obwohl der Einheitenbefund **seit Paket 0036 viermal als `beleg` in dieser Datei
> steht** …

**So erzeugt man den Fehler:** `grep -c "^beleg = .*einheitenbefund-pwt-baci" reihen.toml`
→ **1** (Z. 1334, der Umrechnungsblock der Reihe 14). Der Einheitenbefund kommt insgesamt an
elf Stellen vor, davon vier in Reihenbloecken (Z. 1321, 1322, 1334, 1455) — aber Z. 1321,
1322 und 1455 sind Fliesstexteintraege in `offen`-Listen, nicht das Feld `beleg`.

**Warum das nicht Wortklauberei ist.** Die Datei setzt Schluesselnamen durchgehend in
Backticks, und drei Zeilen ueber dieser Stelle steht im selben Kopf: „traegt seine Herkunft
im Feld `beleg`". Wer dem Kommentar folgt und `^beleg` sucht, findet eine Stelle und haelt
den Kommentar fuer falsch — obwohl die Sache, die er sagen will, stimmt: Die Vorlage war
vierfach in der Datei benutzt und stand trotzdem nicht in der Liste, gegen die nachgezogen
wird. Der Satz ist an genau der Stelle ungenau, an der dieses Paket Ungenauigkeit
abgeschafft hat. Richtig waere „viermal als Beleg" ohne Backticks oder „an vier Stellen".

Die Behauptung ist aus dem Paketrumpf uebernommen (Abschnitt „Erstens", „viermal als
`beleg` in ihr steht (Z. 1260, 1261, 1273, 1394)"), sie entsteht also nicht im Baulauf. Der
Fehler steht jetzt aber in der Datei und nicht mehr nur im Paket.

**Ich schlage dafuer kein eigenes Paket vor.** Eine Ersetzung von zwei Backticks
rechtfertigt keinen Lauf, und ich habe nichts gefunden, was mit ihr zusammen zu erledigen
waere: Paket 0057 ist hinter diesem eingereiht und fasst dieselbe Datei an, aber an anderer
Stelle (Reihen 4, 6, 10 und Z. 227), nicht den Kopfkommentar. Die richtige Behandlung ist,
die Zeile dem naechsten Paket mitzugeben, das den Kopf von `reihen.toml` ohnehin oeffnet.
Bleibt sie stehen, kostet sie einen spaeteren Leser eine Suche und sonst nichts.

---

## Wonach ich gesucht und **nichts** gefunden habe

Damit diese Pruefung von einer, die nicht stattfand, unterscheidbar bleibt:

- **Stiller Einheitenfehler.** Die einzige neue Einheitenaussage ist der Faktor 1000 bei
  Reihe 3; nachgerechnet und gegen die Quelle gestellt, siehe oben. Kein Faktor ist
  dazugekommen, `art = "ungemessen"` steht weiter ohne Zahl. Die gemessene Eins der Reihe 14
  ist unberuehrt.
- **Basisjahr- und Preisbasisvermischung.** Der Lauf trifft keine Aussage ueber die
  Preisbasis; der Widerspruch Nr. 9 (BACI laufend gegen T5 Klasse 2) steht unveraendert und
  ungeloest da, wie das Paket es verlangt.
- **Stillschweigende Interpolation oder verdeckte Lueckenschliessung.** Nichts dergleichen:
  Der Lauf fuegt Verweise hinzu und keine Werte. `zaehlung` ist bitgleich, `sollreihen`
  summiert unveraendert auf 31.
- **Lizenz.** Keine neue Quelle. Die fuenfte Vorlage ist `einheitenbefund-pwt-baci.md`, die
  aus Paket 0025 stammt und in `specs/…/daten.md` verankert ist; die Namensnennung
  (`[namensnennung]`) ist unveraendert.
- **Ein Nachweis, der die Bedingung nur formal erfuellt.** Ich habe fuer alle drei
  Zeichenfolgen-Nachweise geprueft, ob die Ersetzung die Aussage rettet oder nur das Muster
  entfernt. Bei „drei Befunddateien" war das der kritische Punkt (acht Lizenzstellen), und
  die gewaehlte Ersetzung ist inhaltlich richtig.
- **Verlorene Zusagen im umgeschriebenen `toml_geprueft`.** Weggefallen ist gegenueber der
  alten Fassung die Angabe „viermal ueber zwei Pakete abgewiesen". Sie ist von Bedingung 4
  nicht verlangt, und die Sache, die sie trug — dass ein Lauf ohne ausfuehrbares Werkzeug
  auf die sieben Schnitte zurueckfaellt — steht weiterhin in `toml_geprueft_grenze` und
  `schnitt_6`. Kein Befund.
- **Zwischenstaende aus diesem Lauf.** Keine. Der Commit fuehrt vier Dateien, davon eine im
  `dateien`-Anspruch dieses Pakets; die `.tmp`-Dateien unter `daten/zwischenstaende/` sind
  aelter (Pakete 0042 und 0020) und gehoeren 0045.
