---
typ: pruefung
paket: 0050-vorratsprobe-belegstellen
pruefer: test-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Bedingung 1 als `grep` mit Exitcode 1 plus Nachschlagen der neuen Belegstelle in `spiel.md`; Bedingung 2 als Zeichenvergleich der drei Werte gegen den Vorgaengerstand, benannter `ctest`-Lauf und ein Mutationsstand, der belegt, dass die drei Werte wirklich der Massstab sind.
befunde: 0
---

# 0050: beide Bedingungen erfuellt, und der Massstab haelt der Mutation stand

## Bedingung 1 — keine Zeilennummer mehr, und der Ersatz zeigt auf etwas Echtes

**Der Wortlaut der Abnahme, gelaufen:**

```
$ grep -nE 'Zeile [0-9]{3,4}' pruefstand/test/vorrat_verfahren_probe.cpp
$ echo $?
1
```

Kein Treffer. Weil ein leerer `grep` auch dadurch entsteht, dass jemand die Nummer nur
anders schreibt, habe ich breiter gesucht — `Zeil|Z\. [0-9]|zeile|[0-9]{3,4} f\.` — und
alle zehn Treffer nachgesehen: Sie betreffen ausnahmslos die Zeilennummer der
**eigenen** Datei (`FEHLGESCHLAGEN Zeile %d`, `int zeile`) oder sagen ausdruecklich, dass
hier *keine* Zeilennummer mehr steht. Kein Verweis nach `spiel.md` traegt noch eine Zahl.

**Der Ersatz ist nachgeschlagen, nicht geglaubt.** Der neue Beleg lautet an allen vier
Stellen `spiel.md`, Abschnitt „Das Aktionsprofil und wie es auf Aktionen wirkt". In
`specs/0016-…/spiel.md`:

| gesucht | gefunden |
|---|---:|
| `### Das Aktionsprofil und wie es auf Aktionen wirkt` | Z. 1436, **einmal** in der Datei |
| naechste Ueberschrift danach (`### Maß 1`) | Z. 1480 |
| `Zur Probe das Referenzprofil: … 1,2,3 \| 4,5,1 \| …` | Z. 1471 f. |
| `Das **Referenzprofil** ist (1,1,1,1,1)` | Z. 1440 |

Beide belegten Stellen liegen also **innerhalb** des genannten Abschnitts, und die
Ueberschrift kommt in `spiel.md` nur ein einziges Mal vor — der Verweis loest eindeutig
auf. Der abgeschriebene Satz im Kommentar (Z. 126–128 der Probe) stimmt mit Z. 1471 f.
ueberein.

**Die Laufzeitausgabe** nennt denselben Abschnitt, gemessen am laufenden Programm:

```
  gelaufen                   1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,5
  Wortlaut aus spiel.md      1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,5
  nachzulesen in             spiel.md, Abschnitt "Das Aktionsprofil und wie es auf Aktionen wirkt"
```

**Die Nummer ist seit dem Bau schon wieder gewandert** — das vierte Mal. Nachgeschlagen
an `Zur Probe das Referenzprofil` in der jeweiligen Fassung:

| Stand | Zeile |
|---|---:|
| `688e845` (die Probe entsteht) | 1043 |
| `6537a9e` (Zustand, den 0050 beschrieb) | 1318 |
| `7aa76e0` (der Bau dieses Pakets) | 1464 |
| `7d8ab26` (heute) | **1471** |

Haette das Paket die Nummern nachgezogen statt sie zu ersetzen, waere seine Korrektur
heute wieder falsch. Der Abschnittsverweis stimmt ueber alle vier Staende.

## Bedingung 2 — der Wortlaut unangetastet, und der Lauf gruen

**Zeichenvergleich gegen den unmittelbaren Vorgaengerstand `50c916d`:**

| Wert | vorher | nachher |
|---|---|---|
| `REFERENZFOLGE` | `"1,2,3 \| 4,5,1 \| 2,3,4 \| 5,1,2 \| 3,4,5"` | identisch |
| `REFERENZTABELLE` | `{1,2,3} {4,5,1} {2,3,4} {5,1,2} {3,4,5}` | identisch |
| `REFERENZPROFIL` | `Profil{1, 1, 1, 1, 1}` | identisch |

Der vollstaendige Diff des Pakets (`git show 7aa76e0 -- …/vorrat_verfahren_probe.cpp`)
beruehrt keine dieser Zeilen; er besteht aus Kommentartext, der neuen Konstanten
`BELEGSTELLE` und einem zusaetzlichen `fprintf`.

**Keine Zusicherung ist verschwunden.** `grep -cE '^ *pruefe\('` liefert **25** bei
`50c916d` und **25** heute. Das Paket hat weder eine Pruefung entfernt noch eine
Schwelle verstellt noch einen Test uebersprungen.

**Der Lauf:**

```
$ cmake -S pruefstand -B $TMPDIR/p0050 && cmake --build $TMPDIR/p0050
$ ctest -R vorrat_verfahren_probe
1/1 Test #3: vorrat_verfahren_probe ...........   Passed    0.02 sec
100% tests passed, 0 tests failed out of 1
```

Die gedruckte Folge lautet `1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,5`, und sie ist die
**gerechnete**, nicht das Literal: Die Probe druckt beide untereinander (`gelaufen`
gegen `Wortlaut aus spiel.md`, siehe oben), und sie stimmen ueberein. Die uebrigen zwei
Proben des Kastens laufen mit (`vorrat_probe`, `vorrat_kernanker_probe`) — 3 von 3 gruen.

## Wird der Test rot, wenn man die Sache kaputtmacht?

Bedingung 2 sichert drei Werte „Zeichen fuer Zeichen". Dass sie unveraendert sind, zeigt
der Diff. Dass ihre Unversehrtheit **etwas bedeutet**, zeigt er nicht — waeren sie
Zierat, waere das Kriterium eines ueber nichts. Also gemessen, mit einem Stand, der die
**unveraenderte** Probe des Pakets je einmal gegen eine verstellte Fassung genau dieser
Werte uebersetzt und das Urteil umdreht (`WILL_FAIL TRUE`). Der Stand liegt unter
`befunde/pruefung-0050-mutationsstand/CMakeLists.txt` und fasst keine Datei des Pakets an.

| Mutant | Eingriff | erwartet | Ergebnis |
|---|---|---|---|
| M0 | keiner (Kontrolle) | gruen | **gruen** |
| M1 | `REFERENZFOLGE` letzte Ziffer `5` → `4` | rot | **rot, 4 Zusicherungen** |
| M2 | `REFERENZTABELLE` Runde 3 `{2,3,4}` → `{2,3,5}` | rot | **rot, 4 Zusicherungen** |
| M3 | `REFERENZPROFIL` `{1,1,1,1,1}` → `{2,1,1,1,0}` | rot | **rot, 3 Zusicherungen** |
| M4 | `BELEGSTELLE` → `GIBT-ES-NICHT.md` | gruen | **gruen, 0 Zusicherungen** |

`ctest`: 5 von 5 bestanden, also Kontrolle gruen und jede der drei Mutationen gefangen.
M1 stirbt unter anderem an Pruefung 2a (`die beiden Abschriften aus spiel.md stimmen
ueberein`, Z. 418) — die Zeichenkette ist wirklich der Massstab und nicht die Ausgabe der
Probe selbst. In den Stand eingebaut ist eine Fehlerbremse: Findet `string(FIND)` das
Suchmuster nicht, bricht CMake ab, statt eine unveraenderte Datei brav bestehen zu lassen.

## M4 ist kein Befund gegen dieses Paket — aber der Messwert, den 0059 braucht

Die neue Belegstelle wird **gedruckt, nicht geprueft**. Der Mutant M4 setzt sie auf eine
Datei, die es nicht gibt, und die Probe bleibt gruen und meldet:

```
  nachzulesen in             GIBT-ES-NICHT.md, Abschnitt "Das Aktionsprofil und wie es auf Aktionen wirkt"
```

Das ist **keine Verfehlung der Abnahme**: Bedingung 1 verlangt genau die
Abschnittsueberschrift an Stelle der Nummer, und die steht da und loest richtig auf. Es
ist die ehrliche Grenze dessen, was das Paket erkauft hat — der Verweis *driftet* nicht
mehr still bei Einfuegungen oberhalb (heute schon 7 Zeilen wert), aber er *verrottet*
weiterhin still, wenn jemand die Ueberschrift umbenennt.

Ein eigenes Paket schreibe ich dafuer **nicht**: `0059-belegstellenriegel-im-baulauf`
steht seit dem 2026-09-04 auf `offen` und deckt den Fall in seiner Abnahmebedingung 3
ausdruecklich ab („fuer Bedingung 2 eine verdrehte Ueberschrift"). M4 ist der
Rotnachweis-Vorgriff darauf, mit Zahl: **null** Zusicherungen fangen heute eine falsche
Belegstelle.

## Wonach ich gesucht und nichts gefunden habe

- **Abgeschwaechte Tests** — Zusicherungszahl vorher/nachher gleich (25/25), keine
  Schwelle im Diff, kein `WILL_FAIL`, kein `DISABLED`, kein auskommentierter `pruefe(`.
- **Umschriebene Zeilennummern**, die dem `grep` der Abnahme ausweichen (`Z. 1043`,
  `Zeilen 1043`, `1043 f.`) — keine.
- **Ein Beleg, der ins Leere zeigt** — Ueberschrift, Referenzfolge und Referenzprofil
  einzeln in `spiel.md` nachgeschlagen, alle drei vorhanden, Ueberschrift eindeutig.
- **Schreiben ausserhalb der `dateien`-Liste.** Der Commit `7aa76e0` traegt fuenf Dateien;
  `werkzeugkette.cmake` und der Statuswechsel in `0058-…` gehoeren nachweislich zu Paket
  0058 (`rolle: kernbauer`, `dateien: […/werkzeugkette.cmake]`), das im selben Baulauf
  lief. `notizen/testentwickler.md` ist das Logbuch, `0059-…` ein erlaubter Vorschlag.
  Kein Uebergriff.
- **Regressionen im Kasten** — alle drei Proben des `pruefstand` gruen.

Nicht geprueft habe ich die Aussage im Kommentar, das Vorratsverfahren selbst sei richtig:
Das ist Paket 0029 und dort geprueft (`pruefung-0029-…-2026-09-03.md`). Dieses Paket hat
am Verfahren nichts geaendert.
