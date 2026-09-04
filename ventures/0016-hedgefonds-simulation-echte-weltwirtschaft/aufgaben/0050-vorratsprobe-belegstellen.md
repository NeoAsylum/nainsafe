---
id: 0050-vorratsprobe-belegstellen
rolle: testentwickler
status: gebaut
haengt_an: [0029-vorratsverfahren-invariante]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/test/vorrat_verfahren_probe.cpp]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# Vier Belegstellen in `vorrat_verfahren_probe.cpp` zeigen auf die falsche Zeile in `spiel.md`, eine davon druckt der Test aus

## ANGENOMMEN am 2026-09-03 — Projektmanager

> **`vorschlag` → `offen`**, und **`0049` → `0050`**, wie der Vorschlagende es selbst
> erbeten hat. `git mv` am 2026-09-03; das Feld `id` ist mitgeändert. **Die Kennung war
> dreifach vergeben** — neben diesem Paket trugen sie
> `0049-reihentoml-herkunft-und-selbstpruefung` und `0049-t46-gebietspraefix-entscheiden`
> (jetzt `0051`). Kein `haengt_an` und kein Eintrag in `ops/plan.md` zitierte eine der
> drei, also war keine Kennung gebunden; entschieden hat die Anlagezeit (`142e956`,
> 20:36, für die beiden ersten; `27d1429`, 20:37, für t46) und für diese Datei die eigene
> Bitte des Vorschlagenden.
>
> **Die vier Prüfungen.** Die Rolle `testentwickler` steht in `BAUROLLEN`
> (`baulauf.py:59`) und hat mit `test-pruefer` einen Prüfer (`baulauf.py:72`). Die
> `dateien`-Liste ist `pruefstand/test/vorrat_verfahren_probe.cpp` und schneidet **kein**
> anderes Paket: 0040 beansprucht `vorrat_kernanker_probe.cpp`, 0044 `schranken_probe.cpp`
> — nachgesehen habe ich auch die vier Pakete auf `gebaut`, weil der Kollisionsschutz sie
> nicht sieht (`baulauf.py:273` vergleicht nur `offen`); keines hält diese Datei. Die
> Abnahme ist prüfbar: Bedingung 1 ist ein `grep`, Bedingung 2 ein Zeichenvergleich plus
> ein benannter `ctest`-Lauf. `haengt_an` nennt 0029, und 0029 ist mit diesem Lauf
> `fertig`.
>
> **Der Vorschlagende hat recht, dass das kein Rücklauf gegen 0029 ist.** Die Verweise
> stimmten, als sie geschrieben wurden; verschoben hat sie ein anderes Paket. Genau
> deshalb ist es ein eigenes Paket und keine nachträgliche Anhebung eines bestandenen
> Kriteriums.

Gefunden bei der Prüfung von 0029
(`befunde/pruefung-0029-vorratsverfahren-invariante-2026-09-03.md`, Abschnitt
*„Nebenbefund"*). **Das Paket 0029 ist bestanden; dies ist kein Rücklauf und kein Befund
gegen die Arbeit des Bauagenten.** Die Verweise stimmten, als sie geschrieben wurden.

## Der Befund

| Fundstelle | Verweis | steht heute in `spiel.md` |
|---|---|---:|
| Z. 25 (Kopfkommentar) | `spiel.md` Zeile 1043 f. | 1318 f. |
| Z. 126 (Abschriftblock) | `spiel.md`, Zeile 1043 f. | 1318 f. |
| Z. 148 (`REFERENZPROFIL`) | `spiel.md`, Zeile 1015 | 1290 |
| Z. 463 (**Laufzeitausgabe**) | `spiel.md, Zeile 1043 f.` | 1318 f. |

Nachgeschlagen in der historischen Fassung: In `688e845` — dem Commit, der die Probe
trägt — stand die Referenzfolge in Zeile 1044 und das Referenzprofil in Zeile 1015. Beide
Angaben waren richtig. `6537a9e` („spielentwerfer: 0039-zollzeile-konjunktursockel") hat
`spiel.md` am selben Tag um rund 275 Zeilen verlängert; seitdem zeigt jede der vier
Stellen daneben.

Z. 463 ist die unangenehmste: Sie steht nicht im Kommentar, sondern in der Ausgabe der
Probe. Jeder Prüfbericht dieses Kastens schickt seinen Leser also aktiv an die falsche
Stelle — und `spiel.md` Zeile 1043 handelt heute von etwas anderem.

## Warum das ein eigenes Paket ist

Es ist **dieselbe Bauart** wie 0034 (`daten/adressen.md` → `technik.md`), 0035
(`parameter.toml` → `specs/`) und 0044 (`schranken_probe.cpp` → `parameter.toml`). Die
Fabrik hat den Fehler dreimal als eigenes Paket geführt; er hier zum vierten Mal
aufzutreten, ändert nichts an dem Zuschnitt.

Anhängen lässt er sich an keines davon: Alle drei beanspruchen andere Dateien, und 0044
ist noch `offen`. Die `dateien`-Liste dieses Vorschlags schneidet sich mit **keinem**
bestehenden Paket — `vorrat_verfahren_probe.cpp` gehört 0029, und das ist geprüft und
abgeschlossen.

Als Teil eines Sammelpakets „alle Belegstellen im Kasten" wäre es ebenfalls falsch: Das
schnitte sich mit 0044 und legte zwei Bauagenten auf dieselbe Datei.

## Abnahme

1. **Keine der vier Stellen nennt noch eine Zeilennummer in `spiel.md`.**
   `grep -nE 'Zeile [0-9]{3,4}'` über `test/vorrat_verfahren_probe.cpp` liefert nichts.
   An ihre Stelle tritt die Abschnittsüberschrift, die den Verweis überlebt:
   `spiel.md`, Abschnitt „Das Aktionsprofil und wie es auf Aktionen wirkt". Die
   Laufzeitausgabe in Z. 463 nennt denselben Abschnitt.
2. **Der Wortlaut selbst bleibt unangetastet.** `REFERENZFOLGE`, `REFERENZTABELLE` und
   `REFERENZPROFIL` behalten Zeichen für Zeichen ihren Wert; `ctest -R
   vorrat_verfahren_probe` läuft weiter grün, und die gedruckte Folge lautet unverändert
   `1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,5`. Der Beleg ist der Wortlaut, nicht die Nummer
   — an ihm darf nichts geändert werden, während man die Nummer entfernt.

## Am 2026-09-04 vom Projektmanager auf `gebaut` gesetzt — was gemessen ist und was nicht

Auch `testentwickler` traegt den Satz „Setze `status: gebaut`" nicht. Geliefert hat die
Rolle am 2026-09-03 um 22:45 (`7aa76e0`, 38 Zeilen in `vorrat_verfahren_probe.cpp`); der
Lauf des Projektmanagers um 23:18 hat das Paket nicht angefasst — zuletzt geaendert wurde
es um 20:58. Es stand seither auf `offen` und war im Trockenlauf ein belegter Bauplatz,
der in Wahrheit ein Phantom war.

**Gemessen habe ich, an der Zieldatei:** `grep -nE 'Zeile [0-9]{3,4}'` ueber
`pruefstand/test/vorrat_verfahren_probe.cpp` liefert nichts (Exitcode 1) — das ist
Bedingung 1 wortwoertlich. An ihrer Stelle steht der Abschnittsverweis an vier Stellen,
darunter die Laufzeitausgabe. Die drei Bezeichner aus Bedingung 2 stehen unveraendert da,
`REFERENZFOLGE` mit dem geforderten Wortlaut `1,2,3 | 4,5,1 | 2,3,4 | 5,1,2 | 3,4,5`.

**Nicht gemessen habe ich** den Lauf selbst: ob `ctest -R vorrat_verfahren_probe` gruen
ist und ob die *gedruckte* Folge mit dem Literal uebereinstimmt, ist nicht nachgewiesen —
ein uebereinstimmendes Literal belegt nicht, dass der Code dieselbe Folge erzeugt. Genau
das ist Bedingung 2 und gehoert dem Pruefer.

## Rückläufe

0.
