# Messung zu Paket 0139 -- der Sperrebindungsriegel deckt auch `kern/test`

Ein Aufruf, sieben Baeume, am Ende eine Zahl:

    cd ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0139
    python3 sperrebindung.py        # -> "Abweichungen: 0", Rueckgabe 0

Gefahren am 2026-09-05, Ausgabe im Wortlaut in `lauf.txt`.

## Was hier liegt

- `cmakelists-vorher.txt` / `cmakelists-nachher.txt` -- die beiden Fassungen von
  `kern/CMakeLists.txt` als **Kopie**, nicht als Git-Verweis: Ein Fremdlauf, der
  waehrend der Messung committet, verschiebt `HEAD`, die Kopie nicht.
- `proben/` -- drei Wegwerfdateien mit je einem absichtlichen Verstoss. Sie liegen
  hier und nie in `kern/`; das Skript legt sie in eine Abschrift unter `$TMPDIR`.
- `sperrebindung.py`, `lauf.txt` -- Messung und ihr Protokoll.

## Die sieben Baeume und warum es sieben sind

Die Abnahme nennt drei. Zu jedem Baum, der **neu** rot wird, gehoert aber einer, der
**nicht** rot werden darf -- sonst wirkte die Aenderung womoeglich dadurch, dass sie
alles faengt. Bei zwei Bedingungen sind das fuenf, plus das zweite Profil und die
Gegenprobe auf der Seite der Bibliotheksquellen.

| Baum | Fassung | Zulage | erwartet | gemessen |
|---|---|---|---|---|
| B1 | nachher | keine | gruen, Testprofil | Code 0, 10/10 Proben, `8 Kernquelle(n) und 10 Probe(n)` |
| B2 | nachher | keine | gruen, Freigabeprofil | Code 0, 10/10 Proben, dieselbe Meldung |
| B3 | **vorher** | Probe ohne Sperre | **gruen** (Kontrolle) | Code 0, 11/11 Proben |
| B4 | nachher | Probe ohne Sperre | Abbruch beim Konfigurieren | Code 1, nennt `test/luecke_ohne_sperre_probe.cpp` |
| B5 | **vorher** | Sperre nicht zuletzt | **gruen** (Kontrolle) | Code 0, 11/11 Proben |
| B6 | nachher | Sperre nicht zuletzt | Abbruch beim Konfigurieren | Code 1, nennt `test/luecke_reihenfolge_probe.cpp` |
| B7 | nachher | Quelle ohne Sperre | Abbruch beim Konfigurieren | Code 1, nennt `src/luecke_quelle.cpp` |

B4 gegen B3 und B6 gegen B5 sind die eigentlichen Beweise: Derselbe Verstoss, derselbe
Uebersetzer, nur die eine geaenderte Datei dazwischen. B7 belegt, dass der Umbau der
Schleife die erste Haelfte nicht verloren hat.

**Kein Baum wird aus dem falschen Grund rot.** Die Probe zu B5/B6 bindet nach
`kern/sperre.hpp` einen **bereits gebundenen** Kopf; `#pragma once` macht die Zeile
folgenlos, der Vorverarbeiter liest keinen vergifteten Bezeichner nach. Ein frischer
Standardkopf zerbraeche an der Vergiftung, und der Kontrollbaum B5 waere rot, ohne
dass der Riegel etwas damit zu tun haette.

## Keine Sollzahl im Skript

`8` und `10` stehen oben als Messung mit Datum, nicht als Bedingung. Das Skript
vergleicht die beiden gemeldeten Zahlen gegen die Dateien **desselben Baums** und
verlangt zusaetzlich, dass keine der beiden Mengen leer ist. Es bleibt damit richtig,
wenn das naechste Kernpaket eine Quelle oder eine Probe dazulegt.

Dass die alte Fassung die Probenzahl **nicht** meldet, prueft das Skript bei B3 und B5
mit: Sonst liefe eine Kontrolle unbemerkt gegen den neuen Riegel und belegte nichts.
