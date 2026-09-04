---
typ: pruefung
paket: 0044-schranken-probe-belegstellen
pruefer: test-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Beide Bedingungen selbst nachgemessen -- die zwei greps aus Bedingung 1 mit den geforderten Trefferzahlen, Bedingung 2 durch eigenen Neubau samt ctest und durch den Diff auf die Konstante; dazu ein Rotnachweis, der zeigt, dass das Gruen des Belegstellenriegels ueber dieser Datei gemessen und nicht blind ist.
befunde: 2
---

# 0044: Abnahme erfuellt. Zwei Saetze in derselben Datei sind trotzdem falsch, einer davon neu.

## Was ich geprueft habe, und wie

### Bedingung 1, erste Haelfte -- `Zeile [0-9]` liefert nichts mehr

Muster `Zeile [0-9]` ueber `kern/test/schranken_probe.cpp`: **kein Treffer.** Vorher
sechs -- nachgeschlagen im Diff des Baucommits `9bb7492`, nicht im Paket abgeschrieben.

### Bedingung 1, zweite Haelfte -- die drei Schluessel sind ueber den Namen auffindbar

Muster `^druck_max|^stufen_max|^aufschlag` ueber `parameter.toml`: **genau drei
Treffer**, je einer:

| Schluessel | Zeile heute | Wortlaut |
|---|---:|---|
| `stufen_max` | 254 | `stufen_max = 1  # PLATZHALTER` |
| `aufschlag` | 299 | `aufschlag = 51  # PLATZHALTER` |
| `druck_max` | 353 | `druck_max = 1  # PLATZHALTER` |

Die Nummern stehen hier, weil dieser Befund kein Beleg ist, sondern ein Protokoll --
in der Quelldatei stehen sie zu Recht nicht mehr. Der Nachtrag des Projektmanagers
hatte 254/299/353 vorhergesagt; sie stimmen.

### Bedingung 2, erste Haelfte -- `GRENZEN_BAUZEITPUNKT{1, 1, 51}`

Unveraendert. Der Diff von `9bb7492` fasst die Zeile nicht an; sie steht heute
wortgleich in `schranken_probe.cpp:433`. Zaehlung der Zusicherungen vor und nach dem
Commit (`PRUEFE(`, `ROT(`, `GRUEN(`): **64 gegen 64** -- keine entfernt, keine
abgeschwaecht, keine uebersprungen. Der Commit hat drei Dateien beruehrt: die Quelldatei,
die Aufgabendatei und das Logbuch des Bauagenten; nichts ausserhalb der `dateien`-Liste.

### Bedingung 2, zweite Haelfte -- `schranken_probe` weiter bestanden

Nicht aus dem Uebersetzungsbefund uebernommen, sondern selbst gebaut: frische
Konfiguration von `kern/` in `$TMPDIR`, `cmake --build --target schranken_probe`,
`ctest -R schranken_probe -V` -> **Passed**, alle Rot- und Gruenproben in der Ausgabe.
Zusaetzlich `ctest` ueber den Arbeitsbereich `bau/`: **12/12 Passed**, darunter
`schranken_probe` als Test 4 und `belegstellen_riegel` als Test 12. Der
Uebersetzungsbefund `befunde/uebersetzung-2026-09-04.md` fuehrt dasselbe (Zeile 79 und
154 dort).

Der gedruckte Block traegt keine Nummer mehr und bleibt buendig:

```
Grenzen aus parameter.toml (Argumente, kein Dateizugriff, T2):
  druck_max  = 1  # PLATZHALTER
  stufen_max = 1  # PLATZHALTER
  aufschlag  = 51  # PLATZHALTER
```

### Der Rotnachweis: ist das Gruen des Riegels gemessen?

Ein Riegel, der nichts findet, und ein Riegel, der nichts finden *kann*, geben dieselbe
Null aus. Ich habe die beiden auseinandergezogen -- Aufbau in
`befunde/pruefung-0044/`, ein CMake-Stand, der **denselben, unveraenderten**
`belegstellen_riegel.cpp` per absolutem Pfad uebersetzt (keine Abschrift: eine Abschrift
misst sich selbst) und ueber zwei winzige Wurzeln laufen laesst:

- `alt/` -- der Kommentar- und Ausgabeblock im Wortlaut **vor** 0044,
- `neu/` -- derselbe Block im Wortlaut **nach** 0044.

| Lauf | Ergebnis |
|---|---|
| `riegel_alt` | **3 Befunde**, `probe_alt.cpp:8/9/10 -> parameter.toml` (`WILL_FAIL`, also gruen gemeldet) |
| `riegel_neu` | **0 Treffer**, "Kein Verweis zeigt mit einer Zeilennummer in eine fremde Datei" |

Damit ist die Null gemessen: derselbe Riegel, derselbe Text vorher und nachher,
3 -> 0. Der echte Riegellauf ueber die Vorhabenwurzel meldet unveraendert
**37 Bauquellen, 5 Zeilenverweise, davon 0 mit Dateinamen daneben** -- meine Probe
liegt unter `befunde/` und ist ihm unsichtbar (`GESPERRTE_ORDNER = {"bau", "befunde"}`);
dieselbe Filterung schuetzt auch `baulauf.py` (`"befunde" not in m.parts`), der Stand
wird also nie zum Manifest des offiziellen Berichts.

Nebenbefund aus demselben Lauf, gegen mich selbst: Der erste Durchgang von `riegel_neu`
wurde rot -- an der **Ueberschrift meiner eigenen Probedatei**, die den Fundort mit
Zeilennummern nannte. Der Riegel arbeitet.

### Wonach ich sonst gesucht habe

- **Abgeschwaechte Schwellen, entfernte Zusicherungen, uebersprungene Tests:** keine,
  siehe die Zaehlung 64/64 und den Diff.
- **Eine Zahl aus dem Paket eingetragen** (das ausdrueckliche Verbot des Nachtrags):
  nein. Weder 336/237/282 noch 254/299/353 stehen in der Datei.
- **Der Anker auf seine Eindeutigkeit:** `# GRUPPE A -- die elf Zeilen der Tabelle in
  T27` kommt in `parameter.toml` **genau einmal** vor (Zeile 228); `# GRUPPE A,
  Fortsetzung ...` weiter unten ist ein anderer Wortlaut und kollidiert nicht. Alle drei
  Schluessel liegen zwischen dieser Ueberschrift und der naechsten. Der Verweis traegt.
- **Fremde Abschriften der alten Ausgabe**, die durch die geaenderten `fprintf` brechen
  koennten: keine. Die alten Zeilen mit `Zeile 304` finden sich nur noch unter
  `befunde/` (Protokolle) und in den Aufgabendateien -- nirgends in einer Erwartung.

## Befund 1 -- der Kopf der Datei verspricht eine Zeile, die es nicht mehr gibt (neu durch 0044)

`kern/test/schranken_probe.cpp:47`:

> `//! einsetzt, sind die des Bauzeitpunkts; Schluesselname und Zeile stehen bei jedem.`

Der Satz war vor 0044 **wahr** -- bei jedem der drei stand Schluesselname *und*
Zeilennummer. Er ist durch diese Aenderung falsch geworden: Es steht jetzt nur noch der
Schluesselname da, und das ist der ganze Zweck des Pakets.

**Wie man den Fehler sieht:** Zeile 47 lesen, dann Zeile 430--432 lesen. Der Kopf sagt
"Schluesselname und Zeile", der Block nennt Schluesselname und Zitat.

**Warum kein Werkzeug das gefangen hat, und das ist der eigentliche Punkt:** Der Satz
enthaelt das Wort, aber keine Ziffer. Damit laeuft er durch Abnahmebedingung 1
(`Zeile [0-9]`) und durch den Riegel (`ZIFFERN_MINDESTENS = 2`) hindurch. Beide messen
ein *Muster*, nicht die *Wahrheit* einer Aussage ueber die eigene Datei.

## Befund 2 -- die neue Begruendung behauptet etwas ueber `parameter.toml`, das nicht stimmt

`kern/test/schranken_probe.cpp:424`:

> `/// Jeder Schluessel der Datei steht genau einmal am Zeilenanfang, `grep -n`

**Das ist falsch.** In `parameter.toml` stehen drei Schluessel je **viermal** am
Zeilenanfang -- je einmal unter den vier `[instrument.*]`-Tabellen:

| Schluessel | Zeilen |
|---|---|
| `schrittweite` | 877, 900, 917, 940 |
| `instrument_min` | 878, 901, 918, 941 |
| `instrument_max` | 879, 902, 919, 942 |

Von 50 Schluesselzeilen entfallen damit 12 auf 3 mehrfach vergebene Namen; eindeutig am
Zeilenanfang stehen 38 der 41 verschiedenen Schluessel.

**Wie man den Fehler erzeugt:** Den Satz beim Wort nehmen und das Verfahren, das er
empfiehlt, auf `instrument_max` anwenden -- `grep -n '^instrument_max' parameter.toml`
liefert vier Treffer und damit keine Antwort auf die Frage, welche Zeile gemeint ist.

**Fuer die drei Schluessel dieses Pakets stimmt das Verfahren** -- ich habe es oben
nachgemessen, je genau ein Treffer. Falsch ist nur die Verallgemeinerung. Sie stammt
nicht vom Bauagenten allein: Derselbe Satz steht im Rumpf des Arbeitspakets
("weil jeder der fuenfzig Schluessel genau einmal am Zeilenanfang steht"), samt einer
Selbstprobe, die **Zeilen** zaehlt (`grep -c` -> 50) und daraus auf **Schluessel**
schliesst. Der Bauagent hat eine ungeprueft uebernommene Behauptung in die Quelle
geschrieben; das ist die Bauart, gegen die dieses Paket angetreten ist.

## Warum das trotzdem `geprueft` ist

Beide Abnahmebedingungen sind erfuellt, und ich habe beide selbst nachgemessen statt
sie zu uebernehmen. Meine Rolle senkt kein Kriterium und erfindet auch keines: Ein
Ruecklauf waere hier ein Urteil ueber etwas, das im Kriterium nicht steht.

**Das Kriterium ist aber zu eng gestellt, und das ist mein Befund an den
Projektmanager.** Bedingung 1 misst die Abwesenheit eines Musters. Sie kann nicht
feststellen, ob das, was an die Stelle der Nummer getreten ist, wahr ist -- und genau
dort sind beide Befunde entstanden. Ein Kriterium fuer diese Paketsorte muesste den
**Ersatz** pruefen, nicht nur das Verschwinden der Nummer. Die Arbeit dazu steht in
Vorschlag `0075-schranken-probe-zwei-falsche-saetze`.

## Eine Messung fuer das schon offene Paket 0067, statt eines zweiten Vorschlags

`0067-belegstellenriegel-abschnittszitate` (`offen`) will Ueberschriftszitate
nachschlagen und nennt 0044 ausdruecklich als eines der sechs Pakete, die davon leben.
**In der heute beschriebenen Form faenge es das Zitat aus 0044 nicht:** 0067 sucht die
Form `<datei>, Abschnitt "<ueberschrift>"`. In `schranken_probe.cpp:426` steht statt
dessen `... stehen unter der Ueberschrift \`# GRUPPE A -- ...\``, und der Dateiname
`parameter.toml` steht eine Zeile hoeher, nicht daneben -- dieselbe Grenze, die der
Riegel im Kopf ausschreibt ("Er sieht je Zeile, nicht je Absatz").

Das Zitat ist heute richtig, ich habe es oben nachgeschlagen. Die Messung sagt nur: Der
Schutz, den 0067 verspricht, greift bei genau dem Paket nicht, das es als Beispiel
nennt. Ob 0067 seine Abnahme dafuer erweitert, entscheidet der Projektmanager -- ich
lege keinen zweiten Vorschlag daneben, weil das Paket offen ist und die Sache dort
hingehoert.

## Der Aufbau bleibt liegen

`befunde/pruefung-0044/` (`CMakeLists.txt`, `alt/probe_alt.cpp`, `neu/probe_neu.cpp`).
Wiederholbar mit `cmake -S <dort> -B <dort>/bau && cmake --build <dort>/bau && ctest
--test-dir <dort>/bau`. `bau/` ist in `.gitignore`, es bleiben drei Textdateien im Repo.
Hausregel 3: nicht geloescht.

## Was ich nicht geprueft habe

Ob `GRENZEN_BAUZEITPUNKT` als Ganzes eine tragende Zusicherung ist. Gelesen habe ich es:
`aufschlag` traegt -- die Rotprobe zu Schranke 4 setzt die Festwerte `-50` und `-51`
gegen die 51, eine Verschiebung auf 52 machte die Rotprobe gruen und den Test rot. Die
Proben zu Schranke 6 und 7 rechnen dagegen mit `g.druck_max` und `g.stufen_max`
**symbolisch** (`randfall.lege(druck, g.druck_max)` gegen
`zuviel.lege(druck, g.druck_max + 1)`): Wandert einer dieser beiden Werte, wandern Rot-
und Gruenprobe mit, und die Probe bliebe gruen. "Unveraendert" ist fuer zwei der drei
Werte also eine Lesepruefung -- ich habe sie deshalb am Diff gefuehrt und nicht am Test.

Das ist **kein Befund gegen 0044**: Die Bauart stammt aus 0020, und sie ist vertretbar,
weil die drei Werte `# PLATZHALTER` tragen und kalibriert werden -- eine Probe, die die
Zahl festnagelt, braeche bei jeder Kalibrierung. Ich nenne es, weil ein spaeterer Leser
sonst aus "schranken_probe besteht" schliesst, die Konstante sei bewacht. Sie ist es zu
einem Drittel. Den Mutationsnachweis dafuer (drei Mutanten plus Kontrolle) konnte ich
nicht mehr aufsetzen -- in dieser Sitzung waren `cp` und weitere Schreibvorgaenge
gesperrt, nachdem der erste Stand stand; die Aussage oben ist gelesen, nicht gemessen,
und als solche gekennzeichnet.

## Rueckstand

0.
