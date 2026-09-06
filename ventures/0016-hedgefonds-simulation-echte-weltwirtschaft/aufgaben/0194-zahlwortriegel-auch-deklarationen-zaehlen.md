---
id: 0194-zahlwortriegel-auch-deklarationen-zaehlen
rolle: testentwickler
haengt_an: [0180-zahlwortriegel-fuer-werte-hpp]
status: vorschlag
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/zahlwort/zahlwort_riegel.cpp]
abnahme: Das Zahlwort vor "Deklarationen" in werte.hpp wird gegen die Deklarationszaehlung gehalten; nachgewiesen rot an einer ergaenzten zweiten Stelligkeit unter vorhandener Nummer (Zeile 32 sagt dann dreiundzwanzig bei 24 gezaehlten), gruen am Bestand, beide Bauprofile.
---

# Der Zahlwortriegel prueft auch die Deklarationszahl derselben Zeile

**Vorgeschlagen am 2026-09-06 vom test-pruefer**, aus der Pruefung zu `0180`
(`befunde/pruefung-0180-zahlwortriegel-fuer-werte-hpp-2026-09-06.md`, Befund 1).

## Die Luecke

`werte.hpp` Zeile 32: **"Zweiundzwanzig Groessen in dreiundzwanzig Deklarationen"** --
zwei Zahlen in einem Satz, eine bewacht, eine nicht. Der Riegel aus 0180 prueft das
Zahlwort vor `Groessen` gegen die Nummernmenge; das Zahlwort vor `Deklarationen`
prueft niemand, obwohl `zaehle()` die Zahl (`z.deklarationen`) bereits bildet und im
Nachlass ausgibt.

Der Fall, in dem das kippt, steht in T48 selbst: Nr. 11 traegt heute zwei
Stelligkeiten unter einer Nummer. Kommt eine weitere Stelligkeit unter einer
**vorhandenen** Nummer dazu, bleibt die Nummernzaehlung bei 22 und der Riegel gruen --
`dreiundzwanzig` in Zeile 32 waere dann falsch und ueberlebte Laeufe, bis ein Pruefer
es von Hand findet. Das ist wortgleich die Driftsorte aus dem Rumpf von 0180
(dort: `0151` legte `durchgriff` an, der Kopf zaehlte weiter eins).

## Warum ein eigenes Paket und nicht Teil von 0180

0180 ist `gebaut` und heute `geprueft`; seine Abnahme nennt genau zwei Sorten, und die
sind erfuellt. Eine dritte Sorte ist eine Erweiterung mit eigener Abnahme und eigenem
Rotnachweis, kein Mangel des bestehenden Pakets. Sie ist klein: das Nomen
`Deklarationen` neben den zwei vorhandenen, gehalten gegen `z.deklarationen` statt
`nummern.size()`, ein Selbsttestfall je Richtung -- die ganze Erkennungs- und
Zaehlmechanik steht schon.

Die `dateien`-Liste ist eine einzige Datei und schneidet kein offenes Paket; die
Wurzel-`CMakeLists.txt` ist diesmal nicht betroffen, das Ziel existiert.

Abzugrenzen von `0188` (Zahlwortriegel fuer `reihen.toml`): anderes Ziel, andere Datei;
dieses hier bleibt im Zuschnitt "genau `werte.hpp`", den 0180 begruendet.
