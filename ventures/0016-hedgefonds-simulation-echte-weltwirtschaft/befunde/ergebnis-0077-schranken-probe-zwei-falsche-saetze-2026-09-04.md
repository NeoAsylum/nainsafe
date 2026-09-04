---
typ: ergebnis
paket: 0077-schranken-probe-zwei-falsche-saetze
rolle: testentwickler
datum: 2026-09-04
---

# Zwei Saetze berichtigt, beide Zahlen des Pakets vorher selbst nachgemessen

Geaendert wurde ausschliesslich Kommentartext in
`kern/test/schranken_probe.cpp`. Kein Wert, keine Zusicherung, keine Zeilennummer
eingetragen.

## Was das Paket behauptet und was ich vorgefunden habe

Alle Zahlen des Pakets selbst nachgemessen, keine uebernommen:

| Messung | Paket | vorgefunden 2026-09-04 |
|---|---|---|
| `^schrittweite\|^instrument_min\|^instrument_max` in `parameter.toml` | 12 | **12** (877–879, 900–902, 917–919, 940–942) |
| `^druck_max\|^stufen_max\|^aufschlag` | je 1 | **je 1** (353, 254, 299) |
| `[instrument.*]`-Tabellen | 4 | **4** (876, 899, 916, 939) |
| Schluesselzeilen gesamt (`^[a-z_0-9]+ *=`) | 50 | **50**, davon 41 verschiedene, 38 eindeutige |
| Zusicherungen vor der Aenderung | 64 | **64** |

Bemerkenswert, weil es dreimal andersherum war: **Die beiden Zeilennummern des
Pakets (47 und 424) waren richtig.** Gesucht habe ich trotzdem ueber den Wortlaut.

Ueberschrift `# GRUPPE A -- die elf Zeilen der Tabelle in T27` existiert in
`parameter.toml` im Wortlaut (Zeilenanfang). Das Zitat in `schranken_probe.cpp`
bleibt damit auch dann stehen, wenn 0067 den Abgleich nachtraegt.

## Satz 1

vorher: `... sind die des Bauzeitpunkts; Schluesselname und Zeile stehen bei jedem.`
nachher: `... sind die des Bauzeitpunkts; Schluesselname und die zitierte
Schluesselzeile stehen bei jedem.`

Das ist, was unten tatsaechlich steht.

## Satz 2

vorher: `Jeder Schluessel der Datei steht genau einmal am Zeilenanfang, grep -n
'^druck_max' parameter.toml findet ihn ohne zu zaehlen.`

nachher: die Aussage auf die drei Schluessel eingeschraenkt **und** die Ausnahme
benannt -- die vier `[instrument.*]`-Tabellen wiederholen ihre Schluessel, die drei
stehen je viermal am Zeilenanfang, wer einen anderen Schluessel so sucht, sieht erst
nach, ob er eindeutig ist. Das Paket liess beide Wege zu und nannte den zweiten den
ehrlicheren; beide zusammen kosten drei Zeilen und bewahren den naechsten Leser vor
demselben Trugschluss.

## Abnahme

1. `Schluesselname und Zeile` -> **kein Treffer**. `Zeile [0-9]` -> **kein Treffer**
   (unveraendert).
2. `Jeder Schluessel der Datei steht genau einmal` -> **kein Treffer**. Der Satz an
   seiner Stelle ist mit den gemessenen 12 vereinbar: Er nennt genau diese drei
   Schluessel, ihre vier Fundstellen und die vier Tabellen, aus denen sie kommen.
3. `GRENZEN_BAUZEITPUNKT{1, 1, 51}` unveraendert. Zusicherungen weiterhin **64**
   (`grep -c 'PRUEFE(\|ROT(\|GRUEN('` liefert 65 Treffer inklusive der Zeile des
   Festwerts selbst; 64 sind Zusicherungen). `ctest`: **12/12 bestanden**,
   `schranken_probe` darunter. `belegstellen_riegel` ueber `kern/test`:
   *8 Bauquellen gelesen, 0 Zeilenverweise getroffen* -- null Befunde in dieser Datei.

## Rotnachweis: die Abnahme misst, sie laeuft nicht nur

Beide Messgeraete der Bedingung 1 einmal rot gezeigt, in der **eigenen** Datei, ohne
fremdes Gebiet:

- eingefuegt: `//! ROTNACHWEIS -- parameter.toml, Zeile 353. ...`
- `belegstellen_riegel`: `1 Verweis(e) ... schranken_probe.cpp:52 -> parameter.toml`
- `grep 'Zeile [0-9]'`: 1 Treffer
- entfernt, beide wieder bei 0 (0 -> 1 -> 0), `ctest` danach 12/12.

## Was ich nicht getan habe

`parameter.toml` nicht angefasst -- sie steht nicht in meiner `dateien`-Liste. Die
Doppelvergabe der drei Instrumentenschluessel ist dort auch kein Fehler, sondern die
uebliche TOML-Form; falsch war allein die Aussage darueber im Kommentar.
