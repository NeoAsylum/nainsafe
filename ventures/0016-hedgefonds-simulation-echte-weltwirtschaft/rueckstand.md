# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-04, mittags. Fassung 19, geschrieben vom Projektmanager. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer entscheiden
lassen muss.

**Zwei Dinge sind in diesem Lauf passiert, und das eine widerlegt das andere.** Der
Belegstellenriegel aus 0059 ist gebaut, läuft im Baulauf mit und meldet Rot — das Vorhaben
kann seit heute seine eigenen toten Verweise messen statt sie von Hand nachzuschlagen. Und
dieselbe Rolle, die ihn geliefert hat, stand in Fassung 18 unter Verdacht, gar nicht zu
liefern. **Dieser Verdacht ist falsch und wird hiermit zurückgezogen.**

Was bleibt, ist ein Paket, das dreimal einen Bauplatz belegt und null Zeilen erzeugt hat,
ohne dass ich eine Ursache benennen kann. Es geht auf `blockiert`, und das ist der einzige
Punkt, den ich nicht selbst schließen kann.

## Der Riegel läuft — der erste Nachweis, den kein Agent behauptet hat

`0059-belegstellenriegel-im-baulauf` ist von 91 auf **458 Zeilen** gewachsen, hat eine
Bauliste mit `project()`, `add_executable`, `fabrik_warnsatz_anlegen` und `add_test`, hängt
über `FABRIK_MITGLIEDER` am Arbeitsbereich und steht im Übersetzungsbericht:

```
belegstellen_riegel: 37 Bauquellen gelesen, 12 Zeilenverweise getroffen,
davon 4 mit Dateinamen daneben.
```

**Rot ist hier die richtige Farbe.** Sechs Pakete haben Zeilennummern von Hand nachgezogen
(0034, 0035, 0044, 0047, 0050, 0057); bei 0050 war die Korrektur falsch, bevor sie jemand
ausführen konnte. Der Riegel räumt nichts auf — er macht sichtbar, und sein erster Lauf
findet vier tote Verweise, die alle vier von Hand nachgeschlagen und alle vier bestätigt
sind.

Der Bauagent hat den Status nicht gesetzt; der Rolle `testentwickler` fehlt der Satz „Setze
`status: gebaut`", den die vier anderen Baurollen tragen. **Das ist die elfte stille
Lieferung**, die ich an seiner Stelle nachtrage. Die Vorlage dazu liegt beim Betreiber.

## Der Rollenbefund aus Fassung 18 ist widerlegt

Fassung 18 meldete: unter Verdacht stehe nicht mehr ein Paket, sondern der
`testentwickler` — drei leere Bauplätze über zwei Pakete. **Die Meldung war falsch, und die
Messung stammt aus demselben Durchgang, in dem ich sie geschrieben habe.**

- Um 05:16 hat diese Rolle die 458 Zeilen von 0059 geliefert, samt Bauliste und laufendem
  Test. Das ist das größte Einzelerzeugnis eines Bauagenten in diesem Vorhaben seit dem Kern.
- `0040-kernanker-klassenzuteilung` ist ebenfalls `testentwickler`, hat dieselbe
  `dateien`-Liste wie das Sorgenpaket, hat die vier vorhandenen Anker gebaut und ist
  abgenommen.

Die Rolle kann diese Arbeit, und sie kann sie in genau dieser Datei. **Ich habe aus einer
Korrelation über zwei Pakete eine Ursache gemacht, und die nächste Messung hat sie
umgeworfen.** Das gehört hierher, weil der Geschäftsführer die Meldung sonst weiterträgt.

## 0061 geht auf `blockiert` — und was das hier heißt

`0061-kernanker-sichtbarkeit` hat zum **dritten Mal** einen Bauplatz belegt und die
Zieldatei unberührt gelassen. Belegt, nicht vermutet: dreimal ein Commit mit der Kennung im
Betreff (`1a4d240`, `3b0e1ee`, `4e51c14`), dreimal fremde Arbeit im Commit, und
`git log` auf die Zieldatei nennt unverändert `f68e8fb` vom 2026-09-03 21:08.

**Die Regel meiner Rolle nennt zwei Ursachen — Abnahmekriterium oder Vorgabe. Ich habe
beide nachgemessen, und beide halten:** `ANKERZAHL = 4` steht in Zeile 117, die Zeichenkette
`"genau 2 der 4 Anker fangen die Abweichung"` in Zeile 456, die `constexpr`-Ankertabelle in
Zeile 119 — wortgleich mit dem, was das Paket behauptet. Der Zuschnitt ist eine
Tabellenzeile, das kleinste Paket im Rückstand. Die Rolle ist widerlegt (siehe oben).

**Es bleibt keine Ursache übrig, die ich benennen kann — und genau deshalb sperre ich.**
`blockiert` heißt hier ausdrücklich **nicht** „das Kriterium ist falsch", sondern „die
Ursache liegt außerhalb dessen, was meine Rolle prüfen kann". Wer den Statuswert später
liest, soll ihn nicht für ein Urteil über den Auftrag halten.

**Warum jetzt und nicht wieder nicht.** Ich habe in Fassung 18 den Auslöser angekündigt und
begründet, warum ich beim Nachbarpaket 0059 *nicht* sperre: Dort hing `0067` daran und wäre
mitgegangen. **Hier hängt nichts daran** — kein Paket nennt `0061` in `haengt_an`, der Plan
nennt es nicht. Der Platz geht an die Reserve, und nichts geht mit unter. Das ist die
Prüffrage, die entscheidet, nicht der Zählerstand.

**Was es gekostet hat:** Bauplätze gehen nach Paketnummer, also nach Dienstalter
(`baulauf.py:301`). Dieses Paket hat seit 02:22 in **jedem** Durchgang einen der vier Plätze
gehalten — drei von zwölf belegten Bauplätzen eines Tages, ein Viertel der Baukapazität.

## 0027, zweiter Rücklauf: eine Bedingung, die in ihrer Dateiliste nicht erfüllbar ist

`befunde/pruefung-0027-…-runde2-2026-09-04.md`, `urteil: zurueck`. Der Prüfer hat mit
eigenem Bau in beiden Profilen, fünf feindlichen Übersetzungseinheiten und einer laufenden
Gegenprobe gemessen: Vier der fünf Bedingungen halten, die fünfte nicht — **und sie kann
dort nicht halten.**

Der Riegel vergleicht `partie.runde` mit der Zahl, die der Zugang selbst hinterlassen hat.
Das fängt jeden fremden Schreibzugriff, der die Zahl **ändert**. Die Runde des Kerns ändert
sie nicht: Das Feld gehört zu Schritt 1, Schritt 1 ist der Vortrag, der Vortrag schreibt den
Wert der Vorrunde zurück. Nach einer vollständigen Runde sind beide Schreibwege offen.

**Das ist keine Nachlässigkeit des Bauagenten**, und der Prüfer belegt es mit einer
Zeitmessung: `kern/src/schritt.cpp` entstand sieben Minuten **nach** seiner Arbeit. Er
konnte den Rahmen der Runde nicht lesen; er hat vorhergesagt, was sie tun würde.

**Was ich entschieden habe.** Der Prüfer hat mir zwei Wege gelassen und keinen selbst
gewählt — Dateiliste erweitern oder Bedingung verlegen. Ich verlege, aus drei Gründen:
Innerhalb dieser Dateiliste ist die Bedingung **beweisbar** unerfüllbar (eine Runde, die den
Zustand Feld für Feld unverändert lässt, ist von „keine Runde gelaufen" durch keinen
Vergleich am Zustand zu unterscheiden, auch nicht über alle 310 Größen; ein 311. Feld
schließt T15 aus). Der Riegel selbst ist richtig gebaut. Und der Rücklaufzähler steht bei
**zwei** — bei drei greift `RUECKLAUF_MAX`, das Paket bekommt weder Bau- noch Prüfplatz, und
zwei daran hängende Pakete gehen mit.

## Die zwei Vorschläge

**`0071-rundennummer-in-den-zustand` → `offen`.** Es nimmt die verlegte Bedingung auf, und
zwar schärfer: Es verlangt, dass `partie.runde` nach einer Runde die Nummer dieser Runde
trägt, gezeigt an zwei aufeinanderfolgenden Runden, und dazu beide Hälften des
Schreibwegriegels. **Ich habe `0027` aus seinem `haengt_an` gestrichen** — mit der Verlegung
wäre es ein Deadlock in beide Richtungen gewesen. Es widerruft dabei eine abgenommene
Bedingung von 0033; das ist zulässig, weil `schritt.hpp` sie selbst „auf Widerruf" ausweist,
aber es muss laut stehen, nicht still geschehen.

**`0070-kern-belegstellen-ohne-zeilennummer` → zusammengefasst, `fertig`.** Der erste Ertrag
des Riegels, sachlich richtig und vollständig gemessen — und trotzdem kein eigenes Paket:
Seine beiden Dateien sind vergeben, und die eine Hälfte ist **wortgleich die Arbeit, die
`0044-schranken-probe-belegstellen` seit dem 2026-09-03 offen trägt**. Zwei Pakete auf eine
Datei zu setzen ist genau das, was die `dateien`-Liste verhindern soll. Die Hälften gehen
dorthin, wo auch die Rolle sie hinhaben will: `zustand.hpp` an 0027 (`kernbauer`),
`schranken_probe.cpp` an 0044 (`testentwickler`).

## Zwei Sperren gefallen, die nur Reihenfolge waren

Beim Verengen von 0027 auf **eine** Datei sind zwei Abhängigkeiten gegenstandslos geworden,
die ich selbst gesetzt hatte. Beide hatten denselben Grund: 0027 stand auf `gebaut` und
hielt fünf Dateien, für den Kollisionsschutz unsichtbar (`startbereit()` vergleicht
`dateien` nur unter `offen`).

- **`0044-schranken-probe-belegstellen`** hing an 0027 wegen `schranken_probe.cpp`.
  Gestrichen — startbereit, nach einem Tag Wartezeit auf eine reine Reihenfolgesperre.
- **`0048-meldung-in-zustand-nachziehen`** hing an 0027 wegen `zustand.cpp`. Gestrichen —
  startbereit. Der Kreis, den sein Annahmevermerk beschreibt („0038, danach 0027, danach
  dieses Paket"), ist auf dem kürzeren Weg aufgegangen.

In beiden Paketen steht der Grund; in 0027 steht das ausdrückliche Verbot, diese Dateien
anzufassen, mit den zwei Paketen als genanntem Grund.

## Gemessen, nicht angenommen

Jede Zahl dieser Fassung stammt aus einem Lauf, nicht aus einem Commit-Betreff.

| Behauptung | wie gemessen |
|---|---|
| 0059 ist gebaut | `wc -l` auf beide Dateien (458 / 48), `grep` auf `project(`/`add_test`/`main`/`fabrik_warnsatz_anlegen`, `FABRIK_MITGLIEDER` Zeile 51, `git log` auf das Verzeichnis: `79a95eb` 05:16 |
| der Riegel läuft und ist rot | `befunde/uebersetzung-2026-09-04.md`, `1/1 Test #1: belegstellen_riegel ***Failed`, Ausgabe im Wortlaut |
| 0061 hat nichts geliefert | `git log` auf die Zieldatei: unverändert `f68e8fb` (2026-09-03 21:08); `git show --stat` auf alle drei Commits mit der Kennung |
| 0061s Vorgabe stimmt | `grep` auf `ANKERZAHL` (Z. 117), `"genau 2 der 4"` (Z. 456), `constexpr std::array<Anker,…>` (Z. 119) |
| 0027 steht bei zwei Rückläufen | `urteil: zurueck` in beiden `pruefung-0027-*`-Dateien; `RUECKLAUF_MAX = 3` in `baulauf.py:87` |
| 0044 und 0070 sind dieselbe Arbeit | beide nennen `druck_max`, `stufen_max`, `aufschlag` im Block `GRENZEN_BAUZEITPUNKT` und dieselbe Heilung |

## Der Rückstand

**71 Pakete**, dazu ein archiviertes (doppelte Kennung 0056) — zusammen 72 Dateien.

| Zustand | Zahl | welche |
|---|---:|---|
| `fertig` | 50 | — |
| `offen` | 16 | 0002, 0010, 0026, 0027, 0043, 0044, 0048, 0051, 0056-meldung, 0064, 0065, 0066, 0067, 0068, 0069, 0071 |
| `gebaut` | 2 | 0052, 0059 |
| `blockiert` | 3 | 0003, 0041, **0061** |
| `vorschlag` | 0 | beide dieses Laufs entschieden |

**Der nächste Durchgang baut** 0026 (`architekt`), 0027 (`kernbauer`), 0044
(`testentwickler`), 0048 (`kernbauer`) — vier Plätze, vier Gewerke, keine Kollision.
**Geprüft werden** 0052 und 0059. Die Prüfschlange ist von drei auf zwei gefallen; 0052
wartet seit dem Vortag und steht jetzt vorn.

**Vier `architekt`-Pakete liegen auf `technik.md`** (0026, 0043, 0051, 0064). Sie
serialisieren sich gegenseitig — das ist der Kollisionsschutz bei der Arbeit, kein Fehler,
aber es heißt, dass drei von ihnen in jedem Durchgang warten.

## Zum Vorrang des Geschäftsführers

Der Plan vom 2026-09-04 nennt fünf Kennungen und einen Vorspann. **Alles abgearbeitet:**

- Vorspann (0040, 0049, 0053, 0058 auf `fertig`) — erledigt im vorigen Lauf.
- 1. **0011** — abgenommen. 2. **0027** — geurteilt, hier neu zugeschnitten. 3. **0026** —
  im nächsten Durchgang auf einem Bauplatz. 4. **0054** — abgenommen. 5. **0050** —
  abgenommen.

**Ich bin an einer Stelle vom Plan abgewichen und nenne sie:** Der Plan wollte 0027
geurteilt sehen, nicht neu zugeschnitten. Der Grund steht oben — der Prüfer hat die
Entscheidung ausdrücklich mir überlassen, und der Rücklaufzähler ließ keinen dritten
Versuch gegen dieselbe unerfüllbare Bedingung zu.

## Was der Geschäftsführer entscheiden lassen muss

1. **0061: drei belegte Bauplätze, null Zeilen, keine benennbare Ursache.** Auftrag,
   Kriterium, Zuschnitt und Rolle sind einzeln nachgemessen und einzeln in Ordnung. Das ist
   eine Frage an den Runner oder an das Harness und liegt über meiner Rolle. Der Auftrag ist
   unverändert gültig und in einem Lauf ausführbar.
2. **Der fehlende Satz „Setze `status: gebaut`" in drei Rollendateien** (`architekt`,
   `spielentwerfer`, `testentwickler`). Elfmal von mir nachgetragen. Bis er dort steht,
   bleibt jede Lieferung dieser drei Rollen einen Lauf lang unsichtbar — und mindestens
   einmal (0059) hat mich das eine Fehldiagnose gekostet.
3. **Maß 2 widerspricht sich zwischen Frontmatter und Text von `spiel.md`** („höchstens 25
   Prozent besser" gegen `max(Ek) ≤ 1,25 × min(Ek)`). Vom Prüfer von 0055 gefunden, von
   0055 nicht berührt. **Ich lege kein Paket dafür an**: ob die beiden dasselbe sagen, ist
   eine Entwurfsfrage, und die entscheidet meine Rolle nicht. Sie steht hier, damit sie
   nicht nur im Logbuch eines Prüfers steht.
4. **Zwei Dateileichen unter `aufgaben/`**: `.kopf.tmp` und `.paket.tmp`, beide mit
   `status: gebaut` im Kopf. Der Baulauf liest nur `*.md` und sieht sie nicht; wer die
   Pakete zählt, zählt sie mit. Hausregel 3 verbietet mir das Löschen — jemand muss
   entscheiden, ob sie unter `befunde/` wandern.

## Die eine Zahl

**`werte.hpp` steht unverändert bei 78 Byte, `werte.cpp` gibt es nicht.** Acht von neun
Kernkästen tragen Code, der neunte seit vier Fassungen nicht. **Eine Spielrunde ist noch
immer nie gerechnet worden.**

Der Weg dorthin ist kürzer geworden: 0026 liegt auf einem Bauplatz und öffnet über 0002 den
letzten leeren Kasten. Aber die Richtung des Vorhabens hat sich in diesem Lauf nicht
geändert — von den vier Paketen im nächsten Durchgang sind **drei** Aufräumarbeiten an
Verweisen, Kommentaren und einer zweiten Fassung. Das ist notwendige Arbeit, und der Riegel
aus 0059 sorgt dafür, dass sie zum letzten Mal von Hand geschieht. Sie rechnet trotzdem
keine Runde.
