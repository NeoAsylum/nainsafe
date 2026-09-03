---
id: 0049-vorratsprobe-belegstellen
rolle: testentwickler
status: vorschlag
haengt_an: [0029-vorratsverfahren-invariante]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/pruefstand/test/vorrat_verfahren_probe.cpp]
abnahme: Die zwei Bedingungen im Abschnitt "Abnahme".
---

# Vier Belegstellen in `vorrat_verfahren_probe.cpp` zeigen auf die falsche Zeile in `spiel.md`, eine davon druckt der Test aus

> **Nummernkollision, bitte umhängen.** Während dieses Laufs ist parallel
> `0049-reihentoml-herkunft-und-selbstpruefung.md` entstanden; beim Anlegen war 0048 die
> höchste Nummer. Ich habe die Datei nicht selbst umbenannt, weil `mv` in dieser Sitzung
> gesperrt war. Der Inhalt hängt an keiner Nummer — `0050` ist frei.

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

## Rückläufe

0.
