---
typ: pruefung
paket: 0067-belegstellenriegel-abschnittszitate
pruefer: test-pruefer
datum: 2026-09-04
urteil: zurueck
kriterium_geprueft: Bedingungen 1 bis 3 eigenstaendig nachgemessen und erfuellt; Bedingung 4 faellt an Paket 0034 -- die als "gefangen" genannte Belegstelle stammt nicht von 0034, und die drei, die 0034 wirklich hinterlassen hat, faengt der Riegel nicht und nennt sie auch nicht.
befunde: 1
---

# Pruefung 0067 -- Belegstellenriegel, Abschnittszitate

Gemessen am Stand von Commit `a70af39`. Alle Zahlen unten stammen aus eigenen Laeufen,
nicht aus dem Nachweis des Bauagenten; wo sie uebereinstimmen, ist das ein Ergebnis und
keine Uebernahme.

**Nachweisort:** `$TMPDIR` ausserhalb des Repos. Kein Schreibvorgang unter `ventures/`,
`specs/` oder `bau/`; nichts zurueckzurollen. Der Riegel nimmt seine Vorgabenwurzel als
zweites Argument -- damit ist jede Sabotage an einer **Kopie** von `specs/` fuehrbar,
ohne die Vorgabe selbst anzufassen.

## Wie ich gemessen habe

Ein eigener Bau (`cmake -S werkzeuge/belegstellen -B $TMPDIR/riegel-bau`, `--build`,
`ctest -R belegstellen_riegel`) und daneben ein Pruefstand in `$TMPDIR`, der dieselbe
**unveraenderte** Quelle gegen praeparierte Kopien von `specs/` richtet. Fuer die Frage,
welche Zitate der Riegel tatsaechlich sieht, habe ich eine Abschrift der Quelle in
`$TMPDIR` um eine Zeile Ausgabe je aufgeloestem Zitat ergaenzt und die 21 Treffer
einzeln nachgeschlagen. Die Paketdatei selbst ist nicht angefasst worden.

---

## Bedingung 1 -- erfuellt

`ctest -R belegstellen_riegel` fuehrt **einen** Test dieses Namens; beide Bedingungen
melden darin. Die Wurzel kommt aus CMake und nicht aus dem Programm -- die Aufrufzeile
aus `ctest -V` lautet:

```
belegstellen_riegel "/home/adria/fabrik/ventures/0016-hedgefonds-simulation-echte-weltwirtschaft"
```

Im Uebersetzungsbericht des Baulaufs ist der Test auf beiden Bauwegen sichtbar:
`befunde/uebersetzung-2026-09-04.md` fuehrt ihn als `12/12 Test #12` (Arbeitsbereich)
und als `1/1 Test #1` (Alleinbau).

Die **Vorgabenwurzel** kommt nicht von CMake, sondern wird im Programm aus dem ersten
Argument abgeleitet. Das ist kein fest eingebauter Pfad -- jeder Bestandteil stammt aus
dem Argument -- und es ist die Folge davon, dass die `CMakeLists.txt` zu 0059 gehoert und
nicht in der Dateiliste von 0067 steht. Der Fall "Verzeichnis fehlt" faellt sicher aus,
nicht still gruen; nachgemessen mit einem erfundenen zweiten Argument:

```
belegstellen_riegel: ... ist kein Verzeichnis.
Dort werden die Vorgaben erwartet -- ohne sie liefe jedes Zitat in die Vorgaben als
"Ziel ausserhalb des Bestands" durch, und der Riegel meldete gruen ueber nichts.
***Failed
```

## Bedingung 2 -- erfuellt

Eigener Lauf auf dem heutigen Stand:

```
belegstellen_riegel, Bedingung 2 (Abschnittszitat): 37 Bauquellen und 11 Datendokumente
gelesen, 130 Dateien im Zielbestand; 21 Zitate der geprueften Form gefunden, 21 davon
aufgeloest, 5 Fundstellen uebergangen.
```

**21 und 21, erste Zahl nicht null.** Ich habe die 21 nicht gezaehlt, sondern einzeln
ausgeben lassen und nachgeschlagen; sie verteilen sich auf `parameter.toml` (2),
`daten/adressen.md` (1), `daten/reihen.toml` (7), `daten/einheitenbefund-pwt-baci.md` (1),
`kern/src/schritt.cpp` (1), `kern/include/kern/schritt.hpp` (1),
`kern/test/schranken_probe.cpp` (1), `belegstellen_riegel.cpp` (1),
`pruefstand/test/vorrat_verfahren_probe.cpp` (5) und `pruefstand/test/vorrat_probe.cpp` (1).

Dass Ungleichheit wirklich rot ist, ist keine Lesung: In jedem Rotlauf unten stehen die
Zahlen auseinander (21/18, 21/20) und der Test faellt.

Die **Null-Bremse** habe ich mit einem Mutanten geprueft, der `schluessellaenge` immer 0
liefern laesst -- also ein Muster, das nichts mehr trifft. Der Lauf meldet dann im
Wortlaut "kein einziges Abschnittszitat gefunden. Das ist ein Befund gegen das Muster
und keine bestandene Bedingung" und faellt. Sie greift; ohne sie waere das der
gefaehrlichste gruene Lauf ueberhaupt.

## Bedingung 3 -- erfuellt, und in der schaerferen Richtung nachgestellt

Der Nachweis des Bauagenten verdreht **das Zitat**. Das Arbeitspaket laesst beides zu;
die interessantere Richtung ist die andere, weil sie den Fall nachstellt, um den es
diesem Paket geht -- jemand benennt eine Ueberschrift in `specs/` um. Ich habe deshalb
in einer Kopie von `specs/` die Zeile `## Die Schleife` zu `## Die Hauptschleife`
gemacht und die unveraenderte Quelle darauf gerichtet. Ergebnis: drei Befunde, je mit
zitierender Datei und Zeile, Zieldatei und gesuchter Ueberschrift.

```
3 Abschnittszitat(e) finden ihre Ueberschrift nicht:

  zitierend: kern/src/schritt.cpp:122
  nachgeschlagen in: specs/spiel.md
  gesuchte Ueberschrift: Die Schleife

  zitierend: kern/include/kern/schritt.hpp:7
  zitierend: werkzeuge/belegstellen/belegstellen_riegel.cpp:32

belegstellen_riegel, Bedingung 2 (Abschnittszitat): ... 21 Zitate der geprueften Form
gefunden, 18 davon aufgeloest, 5 Fundstellen uebergangen.
```

Kontrolllauf gegen die **unveraenderte** Kopie: gruen, 21/21. Damit ist belegt, dass das
Rot von der Verdrehung kommt und nicht vom Umweg ueber die Kopie.

### Wo die Empfindlichkeit aufhoert -- sechs Sabotagen an derselben Ueberschrift

| Sabotage in der specs-Kopie | erwartet | gemessen |
|---|---|---|
| unveraendert (Kontrolle) | gruen | **gruen**, 21/21 |
| `## Die Schleife` zu `## Die Hauptschleife` | rot | **rot**, 3 Befunde |
| `## Die Schleife` zu `## DIE SCHLEIFE` | rot (Schreibung zaehlt laut Kopf) | **rot**, 3 Befunde |
| `## Die Schleife` zu `Die Schleife` (keine Ueberschrift mehr) | rot | **rot**, 3 Befunde |
| `## Die Schleife` zu `## Die Schleife.` | gruen (Schlusszeichen faellt laut Kopf weg) | **gruen**, 21/21 |
| `## Die Schleife` zu `##### Die Schleife` | gruen (eine oder mehrere Rauten) | **gruen**, 21/21 |

Die vier zugesagten Verhalten stimmen mit dem Kopfkommentar ueberein. Insbesondere ist
die Gross- und Kleinschreibung nicht nur behauptet, sondern faengt.

### Sind die Nachlaesse der Normierung tragend oder nur bequem?

Jede Lockerung im Vergleich ist ein Verdachtsfall: Sie kann eingebaut worden sein, damit
etwas gruen wird. Drei Mutanten in `$TMPDIR` schalten je eine ab und zaehlen, wie viele
der 21 dann fallen:

| abgeschaltet | Kopfkommentar sagt | gemessen |
|---|---|---|
| Ueberschriftsform `**Vorspann**` | "reihen.toml zitiert drei solche" | **3 von 21 fallen** |
| Schlusszeichen abschneiden | -- | **3 von 21 fallen** |
| Umlautumschrift | "eine Ueberschrift mit oe und ss" | **1 von 21 faellt** |

Keine der drei ist Zierat, und die zwei bezifferten Zusagen des Kopfkommentars treffen
auf die Stelle genau zu. Das ist der Gegenbeweis zu "Schwelle gesenkt, damit es gruen
wird".

---

## Bedingung 4 -- **nicht erfuellt.** Der Befund

Das Arbeitspaket sagt: Fuer jedes der sechs steht im Ergebnis, welche Belegstelle es
hinterlassen hat und eines von beidem -- der Riegel faengt sie, oder er faengt sie nicht
und dann steht dort die Form, an der er scheitert. **Eine ausgewiesene Luecke ist kein
Ruecklauf. Eine ungenannte ist einer.**

Fuenf der sechs sind sauber abgehakt; ich habe jede Zuordnung an der Messliste der 21
nachgeprueft und alle fuenf bestaetigt gefunden -- einschliesslich des Falls aus dem
Nachtrag (0044, `schranken_probe.cpp:429`, Dateiname vier Zeilen ueber der Ueberschrift:
wird durch die Absatzlesung wirklich gefangen) und der ausgewiesenen Luecke bei 0047.

**Bei 0034 stimmt es nicht.** Ergebnis und Kopfkommentar nennen als Belegstelle von 0034
das Kopffeld `quellen` in `daten/adressen.md` und urteilen "gefangen". Diese Belegstelle
gibt es, und sie wird gefangen (`daten/adressen.md:5` nach `specs/spiel.md`, Ueberschrift
"Der Zustand") -- aber **sie stammt nicht von 0034**:

```
git log --oneline -S(Abschnitt "Der Zustand") -- .../daten/adressen.md
a629f73 kernbauer: 0004-werkstattgeruest-festkomma      (2026-09-01)
```

Paket 0034 lief am 2026-09-03. Der Nachweis nennt `git log -S` als sein Verfahren; auf
diesen Wortlaut angewandt fuehrt es zwei Tage an 0034 vorbei.

**Was 0034 wirklich hinterlassen hat.** Sein eigener Commit `4bd7985` traegt nur
Logbuecher; die Arbeit an `adressen.md` liegt gebuendelt in `688e845` (2026-09-03). Dort
ersetzt 0034 an drei Stellen eine Zeilennummer durch einen Abschnittsnamen -- genau der
Vorgang, um dessentwillen dieser Riegel existiert:

1. `technik.md`, **T49**, im Absatz "Zwei Adresspaare tragen denselben Wert, und das
   braucht eine Regel statt eines Zufalls" (vorher: Zeile 236)
2. dieselbe Wendung ein zweites Mal, fuer `land.<L>.haushaltssaldo` (vorher: Zeile 236/237)
3. "die Ueberschrift der Tabelle sagt es selbst: T46 -- Die elf Adressen, deren Herkunft
   dieses Dokument ist, abschliessend" mit `technik.md` dahinter (vorher: Zeile 874)

Beide Ziele sind **Ueberschriften nach der Definition dieses Riegels selbst** -- fett
ausgezeichnete Vorspaenne, also die zweite der beiden Formen, die `ueberschrift_aus_zeile`
kennt:

```
specs/.../technik.md:407   **Zwei Adresspaare tragen denselben Wert, und das braucht eine Regel statt eines Zufalls.**
specs/.../technik.md:1527  **T46 - Die elf Adressen, deren Herkunft dieses Dokument ist, abschliessend.** Fassung 4
```

Der Riegel faengt keine der drei. Bei 1 und 2 heisst das Schluesselwort **Absatz**, und
`SCHLUESSEL` kennt nur Abschnitt, Ueberschrift und Ueberschrift mit Umlaut. Bei 3 steht
das Schluesselwort zwar da, aber nicht unmittelbar vor der Anfuehrung -- dazwischen
liegen fuenf Woerter, und `ueberschrift_hinter` ueberspringt nur Leerzeichen und einen
Gegenschraegstrich.

Entscheidend: Sie landen auch **nicht** unter den fuenf uebergangenen Fundstellen. Fuer
den Riegel sind sie kein Zitat, also zaehlt er sie nirgends. Das ist genau der
Unterschied zwischen einer ausgewiesenen und einer ungenannten Luecke.

### So erzeugt man den Fehler

1. Kopie von `specs/0016-hedgefonds-simulation-echte-weltwirtschaft/` nach `$TMPDIR`.
2. In der Kopie beide Ueberschriften umbenennen, also alle drei Zitate aus
   `adressen.md` toeten:
   - `**Zwei Adresspaare tragen denselben Wert, und das braucht eine Regel statt eines
     Zufalls.**` wird zu `**Zwei Adresspaare tragen zufaellig denselben Wert.**`
   - `**T46 - Die elf Adressen, deren Herkunft dieses Dokument ist, abschliessend.**`
     wird zu `**T46 - Die Vorgabeadressen.**`
3. Den unveraenderten Riegel darauf richten:
   `belegstellen_riegel <venture-wurzel> $TMPDIR/<kopie>`

Gemessen:

```
belegstellen_riegel, Bedingung 2 (Abschnittszitat): ... 21 Zitate der geprueften Form
gefunden, 21 davon aufgeloest, 5 Fundstellen uebergangen.
1/1 Test #1: messung ..........................   Passed
```

**Drei tote Verweise, Lauf gruen, Zaehlung unveraendert, kein Wort in der
Uebergangenliste.** Zum Vergleich derselbe Eingriff an einer Ueberschrift, die der
Riegel kennt (`## Die Schleife`): sofort rot mit drei benannten Befunden.

### Was das Urteil nicht ist

Kein Vorwurf, dass der Riegel diese Formen fangen **muesste**. Bedingung 4 laesst
ausdruecklich offen, ob eine Form gefangen oder als Luecke ausgewiesen wird; das Muster
ist die Entscheidung des Bauagenten und bleibt es. Der Ruecklauf haengt allein daran,
dass die Aussage zu 0034 "gefangen" lautet, waehrend die drei Belegstellen dieses Pakets
ungeschuetzt **und ungenannt** sind. Zwei Zeilen im Kopfkommentar, die diese beiden
Formen so benennen wie die von 0047 benannt ist, wuerden die Bedingung erfuellen -- die
Alternative, sie zu fangen, ebenfalls. Beides liegt in `belegstellen_riegel.cpp`, also
innerhalb der Dateiliste dieses Pakets; ein neues Paket braucht es dafuer nicht.

---

## Wonach ich sonst gesucht und nichts gefunden habe

- **Abgeschwaechte Zusicherungen in der Versionsgeschichte.** Der Diff von `a70af39`
  nimmt genau eine Zeile Ausgabe heraus (eine Diagnose ohne Zusicherung) und erweitert
  `KLAMMERN` von 8 auf 11 Paare. Eine zusaetzliche Klammerform kann nur mehr Zitate
  finden, nie weniger -- das ist eine Verschaerfung. Keine gesenkte Schwelle, keine
  gestrichene Pruefung, kein uebersprungener Fall.
- **`UEBERSCHRIFT_HOECHSTENS = 200` als bequeme Schranke.** Kein Zitat im Bestand liegt
  in ihrer Naehe; sie schneidet heute nichts weg.
- **Die fuenf uebergangenen Fundstellen.** Alle fuenf einzeln nachgeschlagen; keine ist
  ein verkappter toter Verweis. `parameter.toml:11` und `lizenzbefund-reihen.md:164/202`
  zeigen auf einen Abschnitt derselben Datei, `:364` auf eine franzoesische Lizenzseite,
  `kern/CMakeLists.txt:3` ist eine Rust-Manifestgruppe und gar kein Abschnittsverweis.
- **Der Regressionsbestand.** Es gibt keinen -- der Riegel misst gegen den Baum, nicht
  gegen gespeicherte Erwartungswerte. Damit entfaellt die Frage nach uebernommenen
  Sollwerten: Es gibt keinen Wert, der aus einem frueheren Lauf stammen koennte.
- **Determinismus.** Mehrere Laeufe derselben Fassung auf demselben Baum liefern
  zeichengleiche Ausgabe. Die Dateireihenfolge kommt aus einer eigenen Arbeitsliste, nicht
  aus der Verzeichnisreihenfolge des Dateisystems.

## Zwei ausgewiesene Luecken, die ich bestaetige (kein Befund)

- **0047, Ueberschrift ohne Anfuehrung.** Im Kopfkommentar benannt, mit Form und
  Begruendung, und als Vorschlag 0079 danebengelegt. Genau so ist es gemeint.
- **Ziel ausserhalb des Bestands.** Verschwindet eine Zieldatei, wandern ihre Zitate aus
  der Zaehlung in die Uebergangenliste und der Lauf bleibt gruen. Gemessen: Nimmt man
  `spiel.md` aus der Vorgabenkopie, faellt die Abdeckung von 21 auf 9 und der Test
  besteht weiter. Das ist im Kopfkommentar ausgeschrieben und deshalb kein Ruecklauf --
  aber die Ausschreibung steht in einer Ausgabe, die `ctest` bei Gruen nicht zeigt. Dazu
  liegt Vorschlag 0083 daneben.

## Anmerkungen an den Projektmanager, ausserhalb meines Urteils

- **Nummernkollision.** `aufgaben/` traegt zweimal die 0079:
  `0079-belegstellenriegel-zitat-ohne-anfuehrung.md` (aus diesem Baulauf) und
  `0079-zustandhpp-rundennummer-nachziehen.md` (aus Lauf 416).
- **Commit-Buendelung erschwert die Zuordnung.** Der Ruecklauf oben entsteht an einer
  Zuordnung, die das Repo selbst schwer macht: Die Arbeit eines Pakets liegt regelmaessig
  im Commit des **naechsten** Laufs, und der traegt den Namen des anderen Pakets.
  `git log -S` auf einen Wortlaut ist deshalb nur zusammen mit dem Datum belastbar. Wer
  kuenftig eine Bedingung wie die vierte stellt, sollte das dazusagen -- der Bauagent hat
  das richtige Werkzeug genommen und ist trotzdem an der falschen Stelle gelandet.
