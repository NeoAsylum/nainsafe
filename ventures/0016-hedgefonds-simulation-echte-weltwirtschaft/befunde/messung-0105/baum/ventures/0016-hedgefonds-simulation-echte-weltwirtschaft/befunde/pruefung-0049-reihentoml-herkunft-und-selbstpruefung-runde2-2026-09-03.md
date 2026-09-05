---
typ: pruefung
paket: 0049-reihentoml-herkunft-und-selbstpruefung
pruefer: daten-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Zweiter, unabhaengiger Durchgang gegen dieselbe Fassung (sha256 8d27faa4…). Alle vier Bedingungen einzeln nachgemessen — die drei Zeichenfolgen-Nachweise per Grep, Struktur und Unveraenderlichkeit per eigenem `tomllib`-Vergleich gegen die Fassung vor dem Lauf (66a463b), die sieben Selbstproben eigenhaendig nachgezaehlt, die Herkunftsangabe gegen den Pruefbefund zu 0036, die Vorlagenangabe gegen das Frontmatter und die git-Historie von `einheitenbefund-pwt-baci.md`, `nachgezogen_durch` gegen die Diffs aller sechs Commits, die je `reihen.toml` angefasst haben.
befunde: 1
---

# Zweiter Durchgang, dasselbe Ergebnis: die vier Bedingungen halten. Ein Kommentarsatz traegt zwei Zahlen, die die Datei nicht stuetzt

## Vorbemerkung: dies ist ein Wiederholungslauf

Zu diesem Paket liegt bereits
`befunde/pruefung-0049-reihentoml-herkunft-und-selbstpruefung-2026-09-03.md` vor, Urteil
`geprueft`. Ich habe sie **nicht als Quelle benutzt**, sondern jede Bedingung neu gemessen;
gelesen habe ich sie erst danach. Wo ich zum selben Ergebnis komme, sage ich das, statt es
als neuen Fund auszugeben. Ein Punkt ist hinzugekommen (Befund 1, zweiter Teil).

## Gegenstand und Vergleichsfassung

**Datei.** `daten/reihen.toml`, 1.671 Zeilen, 99.808 Byte,
sha256 `8d27faa4da0fbfb9c3cf00a21af8059a2c084244dd9963b45d827f4c0671936e`.

**Der Lauf steckt nicht unter eigenem Betreff.** Die Aenderung an `reihen.toml` liegt in
`58908fa` („kernbauer: 0058…", 4 Dateien); der Commit `b1a156e` mit dem Betreff dieses
Pakets enthaelt nur `notizen/datenbauer.md`. Die Fassung vor dem Lauf ist deshalb
`66a463b:…/reihen.toml` (Paket 0047), und **jede „unveraendert"-Aussage unten ist gegen
diese Fassung gemessen**, nicht gegen die Beschreibung im Paket. `git diff 66a463b 58908fa`:
43 zugefuegt, 14 entfernt, genau eine Datei — die, die `dateien` erlaubt. Kein fremdes
Verzeichnis beruehrt, keine neuen Zwischenstaende unter `daten/`.

**Werkzeuglage dieses Pruefzugs.** `python3` lief fuer zwei Aufrufe und wurde danach
abgewiesen; die Strukturmessungen unten stammen aus den beiden durchgegangenen Aufrufen,
die Zaehlungen der sieben Schnitte aus dem Werkzeug Grep. Das ist genau der Wechsel, den
`toml_geprueft` beschreibt — er ist hier eingetreten und aendert an keinem Ergebnis etwas.

**Der Parser lief in diesem Pruefzug gegen genau diese Fassung.** Python 3.14.4,
`tomllib.load`: gueltiges TOML 1.0; zweimal eingelesen `a == b` → **True**; sechs
Wurzeltabellen (`datei`, `namensnennung`, `pruefweg`, `reihe`, `widerspruch`, `zaehlung`);
`len(reihe)` = **19**; `len(widerspruch)` = **9**; Summe `sollreihen` ueber die 19
Reihenbloecke = **31** = `zaehlung.sollreihen_gesamt` = **31**.

---

## Bedingung 1 — die fuenfte Vorlage: **erfuellt**

| verlangt | Messung | Ergebnis |
|---|---|---|
| fuenf Vorlagen | `list(d['datei']['vorlagen'])` | **5**: `reihenliste`, `deckung`, `lizenz_wdi`, `lizenz_reihen`, `einheiten` |
| darunter `einheitenbefund-pwt-baci.md` | Z. 136 | `ventures/0016-…/daten/einheitenbefund-pwt-baci.md, Stand 2026-09-02` |
| **mit dem Stand 2026-09-02** | Frontmatter der Vorlage: `datum: 2026-09-02`; `git log --all` auf die Datei: **genau ein** Commit, `d27f02f` (Paket 0025) | Stand stimmt, die Vorlage ist seit ihrer Anlage unveraendert |
| Kopf „Quellen dieser Datei" nennt sie | Z. 98-99 | `daten/einheitenbefund-pwt-baci.md (Paket 0025, Stand 2026-09-02)` |
| **Nachweis:** `0005, 0006 oder 0014` | `grep -c` | **0** |
| an ihrer Stelle Aufzaehlung mit 0025 | Z. 27-31 | „einem der vier Befundpakete -- 0005, 0006, 0014 oder 0025" |

Die Datei existiert unter dem angegebenen Pfad, und der Pfad folgt der Form der drei
anderen `ventures/…`-Eintraege. Auch die Zaehlwoerter im Fliesstext sind mitgezogen: „Der
Stand der **fuenf** Vorlagen" (Z. 118), „der **vierten** Befunddatei" (Z. 31). Ein Grep auf
`vier Vorlagen|drei Vorlagen` findet **0** Treffer — es ist keine alte Zahl stehengeblieben.

## Bedingung 2 — `stand` und `paket` sagen, wofuer sie stehen: **erfuellt**

Beide angebotenen Wege sind gegangen, die Bedingung verlangt nur einen. `stand = "2026-09-03"`
(Z. 105) ist das Datum der juengsten inhaltlichen Aenderung; daneben stehen `paket_bedeutung`
(Z. 106) und `nachgezogen_durch` (Z. 107-113). `paket` ist zeichengleich unveraendert.

**`nachgezogen_durch` habe ich gegen die Historie nachgezaehlt, nicht gegen das Paket.**
Genau sechs Commits haben `reihen.toml` je angefasst. Ihre Betreffs nennen durchweg das
falsche Paket — die Laeufe sind gebuendelt eingecheckt —, also bin ich ueber den Diff-Inhalt
gegangen:

| Commit | Betreff sagt | Diff zeigt | in der Liste |
|---|---|---|---|
| `30e5073` | 0017 | Erstuebertrag | — (steht in `paket`) |
| `c3c649c` | 0020 | mehrzeilige `wortlaut`-Felder, Widerspruch Nr. 2; derselbe Commit bearbeitet `aufgaben/0022-…md` → **0022** | ja |
| `89a4d12` | 0028 | `grund`-Texte Reihe 1/2a/2b, OECD und Notenbanken → **0032** | ja |
| `ae6f605` | 0038 | vier neue Zeilen mit `einheitenbefund-pwt-baci` → **0036** | ja |
| `66a463b` | 0047 | Kopf, Widerspruch, Belegstellen → **0047** | ja |
| `58908fa` | 0058 | dieser Lauf → **0049** | ja |

Die Liste ist vollstaendig und nennt kein Paket zu viel; alle fuenf Kennungen haben eine
Datei unter `aufgaben/`. Der Nachweis — „wer nur diesen Block liest, kann sagen, ob die
Datei aktuell ist" — ist damit erfuellt, weil `paket_bedeutung` ausdruecklich sagt, dass
`paket` nicht dafuer steht.

## Bedingung 3 — Reihe 3 nennt die vierte Befunddatei: **erfuellt**

| verlangt | Ergebnis |
|---|---|
| erster `offen`-Eintrag nennt Abschnitt 3 **und** 4 | Z. 536, beide namentlich, mit Gegenstand („Einheit der Kapitalstockreihe", „Basisjahr PWT 11.0") |
| `begruendung` des Umrechnungsblocks ebenso | Z. 545, beide namentlich |
| `art` zeichengleich | Z. 543 `art = "ungemessen"` — im Diff eine Kontextzeile, also unberuehrt |
| `status` zeichengleich | Z. 544 `status = "ungemessen"` — ebenso Kontextzeile |
| **kein Faktor kommt dazu** | Der Umrechnungsblock der Reihe 3 fuehrt `schritt, art, status, begruendung, frage`; im Diff ist genau eine Zeile des Blocks geaendert (`begruendung`), keine hinzugefuegt. **Kein `faktor`.** |
| **Nachweis:** `der drei Befunddateien` | **0** Treffer (vorher: **10**) |

**Die inhaltlichen Angaben stimmen gegen die Quelle** — ich habe jede in
`daten/einheitenbefund-pwt-baci.md` nachgeschlagen:

- Ueberschriften: „## 3. PWT-Kapitalstock (Reihe 3) — nicht gemessen" (Z. 101) und
  „## 4. Basisjahr PWT 11.0 — nicht gemessen" (Z. 169). Die Abschnittsnummern stimmen.
- „vier PDF-Abrufe kamen unlesbar an" → Abschnitt 3, Z. 149-151: „Vier PDF-Dateien aus drei
  verschiedenen Verzeichnissen sind in diesem Lauf abgerufen worden, und alle vier kamen
  unlesbar an".
- „ein lesbarer Auszug aus einer der beiden dort benannten Dateien" → Abschnitt 3, Z. 165:
  „Es kostet **einen** lesbaren Auszug aus einer dieser beiden Dateien"; die Tabelle Z. 162-163
  nennt `pwt110_user_guide_to_data_files.pdf` und `pwt110.xlsx`.

**Die neue Einheitenaussage habe ich nachgerechnet, weil sie neu in die Datei kommt.**
„stuende der Kapitalstock in Millionen USD, waere der Faktor nach Tsd USD 1000 und nicht 1":
1 Mio USD = 1.000 Tsd USD, der Faktor ist 1000. Richtig, und die Quelle beziffert es genauso
(Abschnitt 3, Z. 139-140). In `reihen.toml` steht `1000` ohne Tausenderpunkt — mit Punkt
haette der Satz `schnitt_1` (T4, Leseregel 5) gebrochen.

**Die acht Stellen ausserhalb der Reihe 3 sind kein Befund.** Der Nachweis ist dateiweit
formuliert, und die Zeichenfolge stand an zehn grepbaren Stellen (plus einer elften, die
ueber zwei Zeilen umbricht: Leseregel 3, Z. 45-46). Der Diff zeigt zwei verschiedene
Ersetzungen, und beide sind richtig:

- Wo es um **Einheiten** geht (Leseregel 3, Reihe 3 zweimal), ist „drei" → „vier" gesetzt —
  der Einheitenbefund gehoert dort dazu.
- Wo es um **Lizenzen** geht (Widerspruch Nr. 7 zweimal, Reihen 17/18/19 je zweimal, also
  acht Stellen), ist „drei Befunddateien" → „drei Lizenz- und Deckungsbefunddateien" gesetzt,
  sonst kein Zeichen. Ein blosses „vier" haette diese Aussagen falsch gemacht: gemeint sind
  `deckungsbefund-1997.md`, `lizenzbefund-wdi.md` und `lizenzbefund-reihen.md`, und der
  Einheitenbefund urteilt ueber keine Lizenz.

Das ist die kleinste Aenderung, die den dateiweiten Nachweis erfuellt, ohne eine Aussage zu
verfaelschen — geprueft, ob die Ersetzung die Aussage **rettet** oder nur das Muster entfernt.

**Reihe 14 und Reihe 16 sind unberuehrt.** Feldweiser `tomllib`-Vergleich aller 19
Reihenbloecke vorher/nachher: geaendert sind allein Reihe 3 (`offen`, `umrechnung`) und die
Reihen 17, 18, 19 (`offen`, `lizenzbeleg`). `zaehlung` und `namensnennung` sind identisch,
unter `widerspruch` ist allein Nr. 7 geaendert.

**Die Leseregel bleibt wahr.** Sie sagt, betroffen sei „noch eine einzige Reihe". Grep auf
`art = "ungemessen"` ueber die ganze Datei: **eine** Fundstelle (Z. 543, Reihe 3). Es gibt
keine zweite ungemessene Stelle, auf die der neue Absatz „`ungemessen` heisst vergeblich
gemessen, nicht unversucht" unzutreffend durchschlagen koennte.

## Bedingung 4 — `toml_geprueft` traegt die Messung statt der Behauptung: **erfuellt**

Die fuenf verlangten Angaben stehen alle da. Ich habe jede **einzeln gegengemessen**, statt
sie zu lesen:

| verlangt | steht im Feld | von mir gemessen |
|---|---|---|
| Datum 2026-09-03 | ja | — |
| Python 3.14.4, `tomllib` | ja | `python3 --version` → **Python 3.14.4** |
| **Herkunft: der Pruefbefund zu 0036** | „die Pruefung des Pakets 0036, `befunde/pruefung-0036-…-2026-09-03.md`, Befund 2. Dort ist der Parserlauf zum ersten Mal gelaufen" | Befund 2 jener Datei (Z. 165 ff.) traegt genau diesen Lauf: 2026-09-03, Python 3.14.4, `tomllib`, 19 Bloecke, `a == b` wahr, Summe 31 gegen `zaehlung.sollreihen_gesamt`, `schnitt_6` geschlossen. **Die Zuschreibung stimmt jetzt**; das „zum ersten Mal" aus 0047 steht nur noch dort, wo es hingehoert |
| gueltiges TOML 1.0 | ja | fehlerfrei geparst |
| 19 Reihenbloecke | ja | `len(d['reihe'])` = **19** |
| zweimal eingelesen dasselbe | ja | zweimal geladen, `a == b` → **True** |
| Summe `sollreihen` = 31 = `zaehlung.sollreihen_gesamt` | ja, ausdruecklich gegen `zaehlung.sollreihen_gesamt` | **31** und **31** |
| `schnitt_6` und `toml_geprueft_grenze` geschlossen, weil `tomllib` doppelte Schluessel abweist | ja, mit dem Fehlerwortlaut | im Pruefbefund zu 0036 an einem Miniaturbeispiel belegt: `TOMLDecodeError: Cannot overwrite a value` |

**Der Satz ueber die Werkzeugliste ist erhalten und wahr.** `agents/rollen/datenbauer.md`,
Frontmatter `tools:` — Read, Glob, Grep, WebSearch, WebFetch, `Edit(ventures/**)`,
`Edit(notizen/datenbauer.md)`. Genau die sieben, die das Feld aufzaehlt; keines fuehrt Code
aus.

**Die Verallgemeinerung auf „die Umgebung" ist gefallen.** `in dieser Umgebung` kommt noch
einmal vor — als Zitat des alten Standes mit unmittelbar folgendem Widerruf: „Abgewiesen
wurden einzelne Aufrufe; die Verallgemeinerung auf die Umgebung war falsch." Die Datei
behauptet es also nicht mehr, sondern nimmt es zurueck. Das ist die verlangte Streichung.

**Die Zugabe im Feld ist keine Bedingungsverletzung, sondern die Rettung der Bedingung.**
Das Feld sagt zusaetzlich, die Messung von 0036 habe der Fassung **vor** 0047 und 0049
gegolten und sei gegen die vorliegende Fassung wiederholt worden. Die erste Haelfte stimmt
nachpruefbar: der Pruefzug zu 0036 lief gegen `ae6f605`, der Bau von 0047 ist `66a463b` und
damit spaeter. Die zweite Haelfte habe ich nicht geglaubt, sondern **selbst nachgeholt** —
mein eigener Parserlauf oben lief gegen genau diese Fassung (sha256 `8d27faa4…`) und liefert
dasselbe Ergebnis. Die Zusage im Feld ist damit unabhaengig von der Frage belegt, wer sie
zuerst gemacht hat. Bedingung 4 sagt „genannt sind" und nicht „genannt ist ausschliesslich";
ein Feld, das ein Ergebnis gegen eine verschwundene Fassung meldet, waere derselbe Fehler in
kleinerer Form gewesen.

**„Sonst ist in `[pruefweg]` nichts geaendert" haelt.** `tomllib`-Vergleich der Tabelle
vorher/nachher: **17 Schluessel, gleiche Menge, gleiche Reihenfolge**, und genau **ein** Wert
verschieden — `toml_geprueft`. Die sieben Schnitte und `toml_geprueft_grenze` sind
zeichengleich.

**Die sieben Schnitte habe ich selbst nachgezaehlt**, nicht die Tabelle des Bauagenten
gelesen — jedes Muster mit Grep gegen die eingespielte Fassung:

| Schnitt | Muster | Datei sagt | gemessen |
|---|---|---|---|
| 1 | `[=] [0-9]+\.[0-9]` | 6 | **6** |
| 2 | `[']{3}` Zeilen / Vorkommen / `^[']{3}\|[']{3}$` | 29 / 54 / 27 | **29 / 54 / 27** |
| 3 | `^\[\[` | 113 | **113** |
| 4 | `^exogen_ab =` / `^verkettet_ab =` / `^lizenzurteil =` / Sammelmuster / `^t37_klasse =` / `^nr =` | 19 / 19 / 19 / 152 / 20 / 28 | **19 / 19 / 19 / 152 / 20 / 28** |
| 5 | `^sollreihen =` / `^sollreihen` | 21 / 28 | **21 / 28** |
| 6 | Parserprobe | siehe oben | Datei liest fehlerfrei, doppelter Schluessel wird abgewiesen |
| 7 | `^wortlaut =` / `^wortlaut_form` | 20 / 2 | **20 / 2** |

Alle sieben halten gegen die geaenderte Fassung. Der Satz im Feld — „jeder ist am 2026-09-03
gegen genau diese Fassung der Datei gelaufen" — ist damit belegt und nicht nur behauptet.

---

# Befund 1 — an den Projektmanager, ausserhalb der vier Bedingungen

**Der neue Kommentar ueber `[datei.vorlagen]` (Z. 122-124) traegt zwei Zahlen, und die Datei
stuetzt keine von beiden.**

Der Satz lautet:

> Der Schluessel `einheiten` ist mit Paket 0049 dazugekommen. Er hat **vier Pakete lang**
> gefehlt, obwohl der Einheitenbefund seit Paket 0036 **viermal als `beleg`** in dieser Datei
> steht -- eine Vorlage, die hier nicht steht, wird nie nachgezogen.

**Erstens: „viermal als `beleg`" — es ist eine `beleg`-Stelle.**
So erzeugt man den Fehler: `grep -n "^beleg = " reihen.toml` liefert 34 Zeilen; genau
**eine** davon nennt den Einheitenbefund (Z. 1334, Umrechnungsblock der Reihe 14). Der
Einheitenbefund kommt insgesamt elfmal vor (Z. 31, 53, 98, 136, 312, 536, 545, 1321, 1322,
1334, 1455); die vier, die der Satz meint, sind die vier Zeilen, die Paket 0036 eingefuegt
hat (`git show ae6f605 -- …/reihen.toml | grep "^+" | grep -c einheitenbefund-pwt-baci` →
**4**) — aber drei davon sind Fliesstexteintraege in `offen`-Listen, kein Feld `beleg`.
Das ist keine Wortklauberei: Die Datei setzt Schluesselnamen durchgehend in Backticks, und
vier Zeilen darueber, im selben Kopf, steht „traegt seine Herkunft im Feld `beleg`". Wer dem
Kommentar folgt und `^beleg` sucht, findet eine Stelle. Richtig waere „an vier Stellen" oder
„viermal als Beleg" ohne Backticks.

**Zweitens: „vier Pakete lang gefehlt" geht bei keiner Zaehlweise auf.** Die Vorlage
existiert seit Paket 0025 (`d27f02f`). Danach haben drei Pakete `reihen.toml` geaendert,
ohne sie in `[datei.vorlagen]` einzutragen — 0032, 0036, 0047 —, und 0049 hat sie
eingetragen. Zaehlt man erst ab der ersten Benutzung, die der Satz selbst nennt („seit Paket
0036"), sind es **zwei** (0036, 0047). Auf vier kommt nur, wer das Paket mitzaehlt, das die
Luecke schliesst. Die Zahl ist erkennbar aus der Vier des ersten Satzteils abgeschrieben:
vier Fundstellen sind zu vier Paketen geworden.

**Woher es kommt.** Der erste Teil steht schon im Paketrumpf („viermal als `beleg` in ihr
steht (Z. 1260, 1261, 1273, 1394)"), er entsteht also nicht im Baulauf; der zweite Teil ist
im Baulauf dazugekommen. Beides steht jetzt in der Datei und nicht mehr nur im Paket — an
genau der Stelle, an der dieses Paket Ungenauigkeit abgeschafft hat.

**Ich schlage dafuer kein eigenes Paket vor.** Zwei Backticks und ein Zahlwort
rechtfertigen keinen Lauf, und es gibt nichts, was mit ihnen zusammen zu erledigen waere:
Paket 0057 fasst dieselbe Datei an, aber die Reihen 4, 6, 10 und Z. 227, nicht den
Kopfkommentar. Die richtige Behandlung ist, die drei Zeilen dem naechsten Paket mitzugeben,
das den Kopf von `reihen.toml` ohnehin oeffnet. Bleiben sie stehen, kosten sie einen
spaeteren Leser eine Suche und sonst nichts.

*Der erste Teil dieses Befunds ist schon im ersten Pruefzug zu 0049 gemeldet worden; ich
bestaetige ihn unabhaengig. Der zweite Teil ist neu.*

---

## Wonach ich gesucht und **nichts** gefunden habe

Damit diese Pruefung von einer, die nicht stattfand, unterscheidbar bleibt:

- **Stiller Einheitenfehler.** Die einzige neue Einheitenaussage ist der Faktor 1000 bei
  Reihe 3; nachgerechnet (1 Mio USD = 1.000 Tsd USD) und gegen Abschnitt 3 der Quelle
  gestellt. Er steht als Groessenordnung des Risikos da, **nicht als Faktor** — der
  Umrechnungsblock traegt weiterhin kein `faktor`-Feld. Die gemessene Eins der Reihe 14 ist
  unberuehrt.
- **Basisjahr und Preisbasis vermischt.** Nein. Der Lauf trifft keine Aussage ueber die
  Preisbasis; Widerspruch Nr. 9 (BACI laufend gegen T5 Klasse 2) steht unveraendert und
  ungeloest, wie das Paket es verlangt. Der neue Text haelt Einheit (Abschnitt 3) und
  Basisjahr (Abschnitt 4) getrennt, so wie die Quelle es tut.
- **Stillschweigende Interpolation oder verdeckte Lueckenschliessung.** Keine. Der Lauf
  fuegt Verweise hinzu und keine Werte. `zaehlung` ist bitgleich, `sollreihen` summiert
  unveraendert auf 31, und die einzige ungemessene Stelle der Datei bleibt ungemessen und
  ist es jetzt sichtbarer als vorher.
- **Eine Luecke, die durch den neuen Verweis kleiner *aussieht*, als sie ist.** Geprueft:
  Reihe 3 fuehrt weiterhin `codes = []` und `code_herkunft = "nirgends festgeschrieben"`,
  und ihr `offen` nennt „Kein Indikatorcode festgeschrieben" — die Vorfrage aus Abschnitt 3
  der Quelle (welche Kapitalstockreihe ueberhaupt, eine Entscheidung des Architekten) ist
  also nicht verlorengegangen, obwohl der neue Text die Schliessungsbedingung auf „einen
  lesbaren Auszug" verkuerzt. Kein Befund.
- **Lizenz.** Keine neue Quelle, kein neues Lizenzurteil. Die fuenfte Vorlage ist eine
  hauseigene Befunddatei aus Paket 0025; `[namensnennung]` ist bitgleich, ebenso alle
  `wortlaut`-, `url`- und `abrufdatum`-Felder (Reihe 14 und 16 unberuehrt, die Reihen 17-19
  nur im Fliesstext von `grund` und `offen`).
- **Ein Nachweis, der die Bedingung nur formal erfuellt.** Fuer alle drei
  Zeichenfolgen-Nachweise geprueft, ob die Ersetzung die Aussage traegt oder nur das Muster
  entfernt. Kritisch war „drei Befunddateien" mit seinen acht Lizenzstellen; die gewaehlte
  Zweiteilung ist inhaltlich richtig (siehe Bedingung 3).
- **Zurueckgelassene Zusagen im umgeschriebenen `toml_geprueft`.** Weggefallen ist gegenueber
  der alten Fassung allein „viermal ueber zwei Pakete abgewiesen". Bedingung 4 verlangt sie
  nicht, und die Sache, die sie trug — dass ein Lauf ohne ausfuehrbares Werkzeug auf die
  sieben Schnitte zurueckfaellt — steht weiter in `toml_geprueft_grenze` und `schnitt_6`.
  Kein Befund.
- **Belegstellen, die die Einfuegung entwertet.** Der Lauf verschiebt alles unter Z. 100 um
  bis zu 29 Zeilen. Beide Richtungen geprueft: keine `Z. <n>`-Adresse in `reihen.toml` zeigt
  auf `reihen.toml` selbst (alle zeigen auf `technik.md` und `lizenzbefund-wdi.md`), und
  kein Quelltext unter `kern/`, `pruefstand/` oder `messung-stack/` liest die Datei ein
  (Grep ueber `*.cpp|*.hpp|*.h|*.cmake|*.txt|*.py`: kein Treffer). Die Uebersetzung ist von
  der Aenderung nicht beruehrt. Die Adressen **aus** den Paketrumpfen und den Befunden zu
  0036 und 0047 **in** die Datei hinein sind dagegen gewandert — das ist bekannt und gehoert
  Paket 0057.
- **Fremde Dateien im Baulauf.** Keine. `58908fa` fuehrt vier Dateien; die drei anderen
  (`notizen/kernbauer.md`, `aufgaben/0058-…md`, und die „Gebaut"-Ergaenzung in
  `aufgaben/0049-…md`) gehoeren dem mitgebuendelten Lauf beziehungsweise dem Paket selbst.
  Kein Zwischenstand unter `daten/` ist neu.
