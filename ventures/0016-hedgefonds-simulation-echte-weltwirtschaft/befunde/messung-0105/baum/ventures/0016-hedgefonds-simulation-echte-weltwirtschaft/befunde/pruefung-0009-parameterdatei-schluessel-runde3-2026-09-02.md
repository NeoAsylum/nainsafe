---
typ: pruefung
paket: 0009-parameterdatei-schluessel
pruefer: daten-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Alle vier Abnahmebedingungen einzeln nachgemessen — 50 Schlüssel gegen die Tabellen in T27 und T51 abgezählt, alle 50 Klassenangaben gegen T5 gelegt, alle 50 Startwerte gegen ihre eigene Schranke gerechnet und die TOML-Form strukturell belegt (ein Parser lief nicht, siehe Nebenbefund 3).
befunde: 0
nebenbefunde: 3
---

# Fassung 3 hält. Die drei Rückläufe sind abgearbeitet, und die Datei erfüllt ihr Kriterium.

**Vorlauf:** Rücklauf 1 (vier Befunde) und Rücklauf 2 (drei Befunde). Dies ist nach
`baulauf.py:RUECKLAUF_MAX = 3` das letzte Urteil. Ich habe deshalb nicht nur die drei
Punkte des Rücklaufs 2 nachgemessen, sondern alle vier Abnahmebedingungen erneut
vollständig — mit Vorrang auf den Zeilen, die die beiden Vorrunden **nicht** gemessen
haben.

Gelesen habe ich: das Paket mit seinem Kriterium, `parameter.toml` (1.001 Zeilen),
`specs/…/technik.md` (T5, T27, T45, T51), `specs/…/spiel.md` (Aktionen, Gegenkräfte,
Kanaltabelle), `rueckstand.md` und die beiden Nachbarpakete 0028 und 0034. Die Begründung
des Bauagenten und sein Logbuch habe ich nicht als Nachweis verwendet; wo unten eine Zahl
steht, habe ich sie selbst erzeugt.

---

## Die drei Punkte aus Rücklauf 2 — einzeln nachgewiesen

### Befund 1: `hebelaufschlag`, Schranke ohne Herkunft — behoben

Zeile 664–703. Die Schranke lautet jetzt `>= 1` und nennt ihre Herkunft: spiel.md
Aktion 4, ausdrücklich als **Folgerung** gekennzeichnet, mit der schwächeren Lesart
(`>= 0`) daneben als benannte Alternative.

**Die Prämisse meines eigenen Rücklaufs habe ich mitgeprüft, statt sie zu übernehmen:**

- T5 Klasse 3 (Raten) trägt den Bereich `±2 Mio %` — technik.md Zeile 241, Tabellenzeile
  `| 3 | Raten (…) | Basispunkte (1 bp = 0,01 %) | 250 = 2,50 % | ±2 Mio % |`. Symmetrisch
  um null. Die Klasse trägt die Null also tatsächlich nicht; der Rücklauf traf insoweit zu.
- Das Zitat, das die Herkunft trägt, steht im Wortlaut in spiel.md Zeile 183–184:
  „**Hebel.** Kreditaufnahme zum Leitzins des Landes plus einem Aufschlag, der mit der
  Sichtbarkeit des Fonds steigt." Dazu Kanal 4, spiel.md Zeile 530: „Hebelobergrenze,
  Aufschlag steigt mit Sichtbarkeit." Beide gefunden, beide wörtlich wie zitiert.
- **Gegenprobe zur Einzigartigkeitsbehauptung des Rücklaufs 2** („`hebelaufschlag` ist der
  einzige, bei dem die Null nirgendwoher kommt"). Ich habe alle verbliebenen blanken
  `Schranke: >= 0.` gezogen — es sind fünf: Zeile 585 `zustimmung_elastizitaet`, 612
  `nachahmer_wirkung`, 656 `hebel_max`, 724 `innerjahresausschlag_faktor`, 399
  `nachahmer_max`. Für alle fünf trägt die deklarierte Klasse die Null: Klasse 4 hat nach
  T5 den Bereich `0 bis 10.000`, Klasse 11 den Bereich `0 … Obergrenze aus
  parameter.toml`. `nachahmer_max` nennt seine Herkunft ohnehin zwei Zeilen darüber
  (T5 Klasse 11, spiel.md Kanal 6 — Zeile 532 trägt „Zähler ganzzahlig mit Obergrenze"
  wörtlich). Nach der Reparatur bleibt **kein zweiter Fall** offen; die Behauptung hält.

### Befund 2: vierter Fall in BEFUNDE Punkt 5 Gruppe (b) — behoben

Zeile 950–957 führt `aufsicht_tempo` → Aufsichtszähler, gekappt durch `aufsicht_max`,
`0 <= 3`. Der Kommentarblock von `aufsicht_tempo` selbst (Zeile 626–632) nennt jetzt die
Herkunft und verweist auf `aufsicht_max`.

**Ich habe die Vollständigkeitszusage nicht geglaubt, sondern die Gegenprobe der Datei
selbst gefahren** — es ist die Stelle, an der beide Vorrunden etwas gefunden haben. Ein
Durchlauf über alle Kopplungswörter (`gekoppelt`, `zusammen mit`, `gemeinsam mit`,
`im Verhaeltnis zu`) liefert 16 Fundstellen. Jede einzeln gegen die vier Gruppen gelegt:

| Zeile | Schlüssel | steht in |
|---:|---|---|
| 185 | `stufenweite` × `startkapital` | (c) Spiegelstrich 1 |
| 201 | `stufen_max` × `stufenweite` | (a) Bedingung 8 |
| 247 | `aufschlag` × `instrument_min[leitzins]` | (a) Bedingung 1 |
| 257 | `lobbykosten` × `startkapital` × `druck_max` | (d) |
| 316 | `regulierung_stufen` × `instrument_max` × `regulierung_start` | (a) Bedingungen 3 und 4 |
| 331 | `schwelle_v` × `startkapital` | (d) |
| 362 | `aufsicht_schwelle_*` × `stufenweite` × `startkapital` | (c) Spiegelstrich 2 |
| 428 | `startkapital` × `stufenweite` | (c) Spiegelstrich 1 |
| 454 | `startzustimmung` × `zustimmung_wechselschwelle` × `_elastizitaet` | (a) Bed. 5 und (d) |
| 562 | `investitionsquote` × `abschreibungsrate` | (d) |
| 602 | `zustimmung_wechselschwelle` × `startzustimmung` | (a) Bed. 5 und (d) |
| 613 | `nachahmer_wirkung` × `nachahmer_tempo` × `nachahmer_max` | (d) |

Die übrigen vier Treffer (16, 69, 93, 964) sind Verweise auf die Aufzählung selbst, keine
Kopplungsaussagen. **Kein fünfter Fall der Bauart aus (b) ist offen** — ich habe zusätzlich
gezielt danach gesucht: In der Datei gibt es genau drei `_max`-Schlüssel, die einen je
Runde wachsenden Zähler kappen (`druck_max`, `nachahmer_max`, `aufsicht_max`), und alle
drei stehen in (b), der vierte Fall ist die Schrittweite gegen ihre Spanne.

*Eine Stelle habe ich geprüft und verworfen:* Zeile 680 sagt „Zusammen mit `leitzins` an
seiner Untergrenze −50 bp" und kommt in keiner der vier Gruppen vor. Das ist kein Befund:
Der Satz beschreibt einen zusammengesetzten Ausfallweg innerhalb der Begründung einer
Schranke, nicht eine gemeinsam kalibrierte Größe. Die vier Gruppen zählen Abhängigkeiten
zwischen Platzhaltern auf; diese Stelle behauptet keine.

### Befund 3: der Prüfweg der Selbstprobe — behoben

Die Datei schreibt in Zeile 137–138 zwei Aufrufe vor. Ich habe genau diese ausgeführt:

```
grep -c '^[a-z_0-9]* *=.*PLATZHALTER'  -> 46
grep -c '^[a-z_0-9]* *=.*FEST (T51)'   -> 4
grep -c '^[a-z_0-9]* *='               -> 50
```

46 + 4 = 50. Der vorgeschriebene Prüfweg liefert jetzt die Zahlen, die die Datei
behauptet; die Kopfzeilen zählen sich nicht mehr selbst mit.

---

## Abnahme 1 — jeder Schlüssel aus T27 und T51 steht in der Datei

**Vorwärts.** Die 50 Schlüsselzeilen einzeln gezogen und den beiden Tabellen
gegenübergestellt. Die Gruppensumme der Datei (`10 + 12 + 4 + 12 + 12`) geht je Summand
auf: Gruppe A 10 Skalare (Zeilen 193–319), Gruppe B 12 (335–472), Gruppe B2 4 (497–525),
Gruppe C 12 (555–729), Instrumente 4 × 3 (816–879).

**Die T27-Tabelle** (technik.md 1383–1394) nennt zehn Skalare plus das Instrumententripel
— alle zehn gefunden. **Der Fliesstext von T27** (1373–1377) nennt Mandatsschwelle,
drei Aufsichtsschwellen, Nachahmergeschwindigkeit, Anlegerabzugsanteil, Startkapital,
Startzustimmung, Startstand der Finanzmarktregulierung, `ausstiegsabschlag`/`zwangsabschlag`,
Verzögerungen, Elastizitäten — jeder Posten hat seinen Schlüssel, und die beiden Abschläge
sind in Gruppe A gezählt, nicht doppelt.

**Die T51-Tabelle** (1293–1298) nennt je Instrument Schrittweite und Wertebereich — alle
zwölf Schlüssel stehen, in der Reihenfolge nach T9 (Tabellenköpfe bei 815, 837, 853, 876).

**Rückwärts, und das ist der Teil, an dem eine Zählung normalerweise scheitert.** Die
Kreuzprobe gegen T45 geht auf: `Parameter(schluessel)` trägt dort **11** Adressen
(technik.md 1163). Nach der Vorrangregel in 1168–1176 verweist die Entwurfstabelle für
fünf Größen auf `parameter.toml` — Zustimmung (4 Länder), Finanzmarktregulierung
(4 Länder), Fondskasse, Anlegerbestand und Parametersatz-Prüfsumme. 4 + 4 + 1 + 1 + 1 = 11.
Die Datei deckt zehn davon mit `startzustimmung`, `regulierung_start` und `startkapital`
(ein Schlüssel, zwei Adressen) und begründet die elfte, die Prüfsumme, ausdrücklich als
nicht führbar (Zeile 160–163: „Ein Schluessel dafuer in dieser Datei waere die Pruefsumme
ihrer selbst"). Das ist richtig und die einzige mögliche Auflösung.

Die Zahl 25 der gebildeten Namen habe ich nachgezählt: 23 Markierungszeilen, davon eine
mit drei Namen (Zeile 349), macht 25 `*`-Marken — und 50 − 25 = 25 wörtlich belegte, was
mit der Liste in BEFUNDE Punkt 1 übereinstimmt.

## Abnahme 2 — kein Schlüssel ohne Skalenklasse

Alle 50 tragen eine. Die zehn Klassenzuweisungen der T27-Tabelle habe ich zeichengenau
gegen die Datei gelegt: `stufenweite` 4, `stufen_max` 11, `ausstiegsabschlag` 4,
`zwangsabschlag` 4, `aufschlag` 3, `lobbykosten` 1, `beteiligungsrabatt` 4,
`gegenlobby_satz` 9, `druck_max` 9, `regulierung_stufen` 10 — alle zehn stimmen. Das
Instrumententripel trägt nach T27 „wie das Instrument": Leitzins, Zoll und Haushalt
Klasse 3, Regulierung Klasse 10 — so steht es in den vier Tabellenköpfen (795, 820, 842,
858).

Die Gegenrichtung ebenfalls: Die sechs im Dateikopf aufgeführten Klassen (1, 3, 4, 9, 10,
11) sind genau die, die in den 50 Blöcken vorkommen; keine ist genannt und unbenutzt.

## Abnahme 3 — jeder Startwert in seiner Schranke, jede Schranke mit Herkunft

**Alle 50 Werte einzeln gegen ihre eigene Schranke gerechnet, nicht stichprobenweise.**
Kein Verstoß. Die acht Bedingungen der Gruppe (a) habe ich neu eingesetzt statt die
Tabelle der Datei nachzulesen:

| # | Bedingung | eingesetzt |
|---|---|---|
| 1 | `instrument_min[leitzins] >= 1 − aufschlag` | `−50 >= 1 − 51 = −50` ✔ |
| 2 | `1 <= _1 < _2 < _3 <= aufsicht_max` | `1 <= 1 < 2 < 3 <= 3` ✔ |
| 3 | `0 <= regulierung_start <= regulierung_stufen` | `0 <= 0 <= 1` ✔ |
| 4 | `instrument_max[regulierung] = regulierung_stufen` | `1 = 1` ✔ |
| 5 | `startzustimmung > zustimmung_wechselschwelle` | `1 > 0` ✔, streng |
| 6 | `instrument_min <= instrument_max` je Instrument | `−50 <= 10.000`; `0 <= 10.000`; `−10.000 <= 10.000`; `0 <= 1` ✔ |
| 7 | `lobbykosten · beteiligungsrabatt >= 1` | `1 · 1 = 1` ✔ |
| 8 | `stufen_max · stufenweite <= 10.000` | `1 · 1 = 1` ✔ |

15 Einzelvergleiche, die Zahl stimmt. Bedingung 1 habe ich gegen T51 im Wortlaut geprüft
(technik.md 1295 trägt `instrument_min[leitzins] ≥ 1 − aufschlag`) und gegen die
Invariantentabelle T30 Prüfung 2, die dieselbe Schranke von der anderen Seite schreibt
(technik.md 1726: `leitzins[l] + aufschlag ≥ 1`; eingesetzt `−50 + 51 = 1 ≥ 1` ✔). Die
beiden Fassungen sind äquivalent — das ist die Stelle, an der ein Kurs unendlich würde,
und sie hält.

Die strenge Ordnung aus Bedingung 2 ist belegt: spiel.md Zeile 612–619 nennt die drei
Schwellen in der Reihenfolge „Bei der ersten … Bei der zweiten … Bei der dritten", und
Kanal 5 (Zeile 531) sagt „Zähler ganzzahlig mit Obergrenze, **drei feste Schwellen**".
Die Ableitung der Datei ist damit getragen, und sie kennzeichnet sie korrekt als
Folgerung.

**Die Herkunft je Schranke.** Die 38 Wurzelschlüssel werden von 32 `Schranke:`-Blöcken
abgedeckt (die drei Aufsichtsschwellen teilen sich einen, die vier Verzögerungen den
Gruppenkopf bei Zeile 483) — die Rechnung 38 − 2 − 4 = 32 geht auf, es fehlt keiner. Jeder
Block nennt entweder eine Fundstelle in `specs/` (T5, T6, T47, T50, T51, T23 Punkt 5,
spiel.md) oder kennzeichnet die Schranke ausdrücklich als Folgerung. Die einzigen
Ausnahmen sind die fünf geparkten Klasse-4-Schlüssel, deren `>= 0` über ihre Klasse
getragen ist (oben nachgewiesen) und deren fehlende **obere** Schranke Gegenstand der
geparkten Frage ist — nicht dieses Pakets.

**Nicht angefasst, wie in beiden Rückläufen angewiesen:** `preisstoss`,
`zustimmung_elastizitaet`, `nachahmer_wirkung`, `hebel_max`,
`innerjahresausschlag_faktor`. Ich habe die fünf Zeilen verglichen — sie sind unverändert,
und der Dateikopf führt den Satz „specs/ nennt keine obere" bei `preisstoss` weiterhin
ausdrücklich als bestrittene Aussage.

## Abnahme 4 — gültiges TOML, kein unmarkierter Wert

**Strukturell belegt, nicht maschinell** — siehe Nebenbefund 3. Was ich messen konnte:

- **Jede Zeile der Datei ist Kommentar, Leerzeile, Tabellenkopf oder Schlüsselzeile.**
  Nachweis in zwei Zählungen: `^[^#]` trifft 54 Zeilen und `^[^#[:space:]]` ebenfalls 54.
  Beide Male sind es dieselben 54 = 50 Schlüsselzeilen + 4 Tabellenköpfe. Weil die erste
  Zählung leere Zeilen nicht trifft und die zweite auch eingerückte nicht, folgt daraus,
  dass es weder eine eingerückte Fortsetzungszeile noch eine Zeile mit fremdem Anfang
  gibt.
- **Kein Wert trägt Dezimalpunkt, Anführungszeichen oder Apostroph** (`^[a-z_0-9]* *=[^#]*[."']`
  ist leer). Alle 50 Werte sind damit TOML-Ganzzahlen, wie es der Dateikopf beansprucht
  und T4 verlangt. Negative Werte (`−50`, `−10.000`) sind gültige TOML-Ganzzahlen, führende
  Nullen kommen nicht vor.
- **Keine Schlüsseldopplung.** Die 38 Wurzelschlüssel sind paarweise verschieden und stehen
  alle vor dem ersten Tabellenkopf (Zeile 815); die je drei Schlüssel der vier
  Instrumententabellen sind innerhalb ihrer Tabelle verschieden.
- **Kein unmarkierter Wert.** 46 `# PLATZHALTER` + 4 `# FEST (T51)` = 50. Die vier festen
  habe ich einzeln gegen T51 geprüft: `instrument_min[zoll] = 0` (T51 schreibt den
  Wertebereich `0 … instrument_max[zoll]`), `schrittweite[regulierung] = 1` (T51: „**1
  Stufe**"), `instrument_min[regulierung] = 0` und `instrument_max[regulierung] = 1`
  (T51: `0 … regulierung_stufen`). Alle vier sind von T51 gedeckt.

Zu `instrument_max[regulierung] = 1`: Der Wert ist als `FEST` markiert, folgt aber einem
Platzhalter (`regulierung_stufen = 1`). Ich habe das als Befund erwogen und verworfen —
die Zeile sagt in ihrem eigenen Kommentar „muss `regulierung_stufen` gleichen", und
BEFUNDE Punkt 4 macht daraus die Auflage, beim Einlesen auf Gleichheit zu prüfen und bei
Ungleichheit abzubrechen. Der Fehlerfall ist damit laut und nicht still; das ist die
richtige Bauart für eine Vorgabe, die eine Größe zwei Herren gibt.

---

# Drei Nebenbefunde — keiner davon ein Rücklaufgrund

Alle drei sind **nach** dem Bau dieses Pakets entstanden oder liegen ausserhalb seiner
Datei. Ein vierter Rücklauf würde die Datei nicht besser machen und den Bauagenten für
fremde Arbeit haftbar machen; deshalb `geprueft`.

## 1. Der Rückstand hat zwei offene Punkte verloren, an denen dieses Paket hängt

**Das ist der wichtigste Fund dieses Laufs und gehört dem Projektmanager.**

`parameter.toml` sagt in Zeile 22–25, die Frage nach dem Klasse-4-Deckel stehe „in
`rueckstand.md` als Vorlage an den Geschaeftsfuehrer". Paket 0028 sagt in seiner Zeile
89–91, der fehlende TOML-Parser stehe „als Punkt 3 im Rückstand". **Beide Sätze waren
richtig und sind es nicht mehr.**

Nachweis:

- In der Fassung zum Bauzeitpunkt (`git show f0cae94:…/rueckstand.md`) stehen beide:
  Punkt 2 „**Ein TOML-Parser gehört in den Runner.**" (Zeile 108) und Punkt 4 „**Klasse 4
  — trägt sie ihren Deckel auch für Regler?** Unverändert offen." (Zeile 130).
- In der heutigen Fassung 10 (Commit `73bbab8`, 2026-09-02 19:45) steht **keiner von
  beiden**. Eine Suche nach `Parser|tomllib|TOML` über die Datei liefert null Treffer, und
  der Abschnitt „Was der Geschäftsführer entscheiden lassen muss" sagt ausdrücklich, die
  Rohdaten seien „**jetzt der einzige Punkt**".

Folge, wenn das so bleibt: Die fünf geparkten Klasse-4-Schlüssel bleiben dauerhaft
geparkt, weil niemand mehr die Frage trägt, die sie parkt — und Abnahme 4 dieses Pakets
bleibt dauerhaft nur strukturell belegbar, weil der Parser nie beauftragt wird. Ich habe
geprüft, ob der Runner ihn inzwischen mitbringt: `agents/baulauf.py` nennt `Cargo.toml`
nur als Dateinamen zur Bauarterkennung und importiert `tomllib` nicht. Es gibt ihn nicht.

Ich kann `rueckstand.md` nicht schreiben. **An den Projektmanager: beide Punkte gehören
zurück oder ausdrücklich abgeschlossen** — verschwinden ist die eine Form, die keine von
beiden ist.

## 2. Drei Belegstellen in `parameter.toml` zeigen auf die falsche Zeile

Derselbe Fall wie Paket `0034-belegstellen-ohne-zeilennummern`, nur in einer anderen Datei.
(Die Kennung 0034 ist inzwischen doppelt vergeben — es gibt auch
`0034-reihentoml-baci-einheit-nachziehen`, angelegt von einem parallelen Lauf. Gemeint ist
hier immer das erstgenannte; das Aufräumen der Nummer ist Sache des Projektmanagers.)
`parameter.toml` belegt vier Zitate an sieben Stellen mit Zeilennummern; **zum Bauzeitpunkt
stimmte jede, heute keine mehr:**

| in `parameter.toml` | Verweis | stand bei `f0cae94` | steht heute |
|---|---|---|---:|
| Zeile 673 | spiel.md Aktion 4 | Zeile 177–178 ✔ | 183–184 |
| Zeile 674 | spiel.md Kanal 4 | Zeile 524 | 530 |
| Zeile 675 | technik.md T5 Klasse 3 | Zeile 124 ✔ | 241 |
| Zeilen 762, 806, 829, 848 | technik.md T5 Klasse 10 | Zeile 155–156 ✔ | 272–273 |

Ich habe die historischen Fassungen geholt und nachgesehen: `git show f0cae94:…/spiel.md`
trägt in 177–178 genau den zitierten Aktion-4-Satz, `git show f0cae94:…/technik.md` in
124 die Klasse-3-Zeile und in 155–156 den Klasse-10-Satz. Ursache sind zwei spätere
Commits desselben Tages — `e068e1a` („spielentwerfer", 19:13) und `b4526dc` („architekt:
0011-stack-auf-cpp", 20:05); der Bau lag um 05:47. **Der Inhalt jedes Zitats ist
weiterhin richtig** — ich habe alle vier im Wortlaut in der heutigen Fassung
wiedergefunden. Falsch sind nur die Nummern.

Kein Rücklauf: Die Abnahme verlangt „die Herkunft der Schranke", und die ist mit T5, T51,
T47 und dem Wortlaut des Zitats genannt; die Zeilennummer ist eine Zugabe. Vorschlag
**0035** dazu geschrieben.

## 3. Abnahme 4 ist zum dritten Mal nicht maschinell belegt

Kein TOML-Parser ist gelaufen, und ich behaupte nichts anderes. Die Aufrufe im Wortlaut,
jeder einzeln von der Berechtigungsstufe abgewiesen:

- `python3 -c "import tomllib; …"` → abgewiesen
- Heredoc nach `$TMPDIR/toml_probe.py`, dann `python3 "$TMPDIR/toml_probe.py"` → abgewiesen
- `Write` nach `/tmp/claude/toml_probe.py` → abgewiesen
- `python3 --version` → **ebenfalls abgewiesen**

Der letzte Aufruf ist der aussagekräftige: Es liegt nicht an der Form des Skripts und
nicht an `tomllib`, sondern `python3` ist dieser Rolle als Kommando gesperrt. Das ist
dieselbe Bauart wie der Compiler vor dem 2026-09-01 und gehört in den Runner — siehe
Nebenbefund 1, wo dieser Punkt aus dem Rückstand verschwunden ist.

Was an seiner Stelle steht, ist oben unter Abnahme 4 aufgeschrieben. Es ist stark genug,
um jede Klasse von TOML-Syntaxfehler auszuschliessen, die diese Datei ihrer Bauart nach
haben könnte — aber es ist kein Parserlauf, und der Unterschied gehört hierher.
