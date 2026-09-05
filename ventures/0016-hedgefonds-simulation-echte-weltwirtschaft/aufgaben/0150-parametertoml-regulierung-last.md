---
id: 0150-parametertoml-regulierung-last
rolle: datenbauer
status: fertig
haengt_an: [0043-t48-groessen-gegenkraft-5]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml]
abnahme: `parameter.toml` traegt den Schluessel `regulierung_last` mit demselben Kommentarkopf, den die Nachbarschluessel tragen -- Klasse nach T5, die Formel, in der er vorkommt, mit T-Verweis, die Schranke mit Begruendung, die Zeile `Kalibriert:` und die Zeile `Scheitert daran:` in beide Richtungen. Der Wert traegt die Marke `PLATZHALTER` wie `lobbykosten`, solange niemand kalibriert hat. Mechanisch nachpruefbar: Eine Suche nach `regulierung_last` in `parameter.toml` findet genau eine Zuweisungszeile; die Klassenangabe im Kommentar ist wortgleich mit der in `technik.md` Zeile 2212 (`Klasse 3`); die im Kommentar zitierte Formel ist zeichengleich mit `technik.md` Zeile 2165. Ausserhalb des neuen Blocks null geaenderte und null entfernte Zeilen.
---

## ABGENOMMEN — 2026-09-06, Projektmanager: `gebaut` → `fertig`

Befund `befunde/pruefung-0150-parametertoml-regulierung-last-2026-09-06.md`,
`urteil: geprueft`. Der Datenbauer hat im selben Lauf **0153** vorgeschlagen, weil die
Bilanzzahlen im Kopf der Datei ausserhalb des neuen Blocks stehen und die hiesige Abnahme
sie darum nicht anfassen durfte. Das ist richtig geschnitten; 0153 steht seit heute auf
`offen` und hat `parameter.toml` danach für sich allein.

# `regulierung_last` fehlt in `parameter.toml`

**Angelegt am 2026-09-06 vom Projektmanager**, nicht erfunden: `technik.md` beauftragt
dieses Paket zweimal ausdruecklich und nennt dabei die Rolle.

- **Zeile 3243**, Tabelle „An den Projektmanager -- welche der neuen Groessen eine
  Schnittstelle in `kern::werte` braucht": *„`regulierung_last` | **nein** --
  Parameterschluessel nach T27. Er gehoert in `parameter.toml` (Datenbauer) und in die
  Struktur `Konstanten` in `werte.hpp`, wo `gegenlobby_satz` und `lobbykosten` schon
  stehen"*.
- **Zeile 3259**, dritter der drei Nachziehpunkte: *„**`regulierung_last` fehlt in
  `parameter.toml`.** Folgepaket des Datenbauers, im Auftrag dieses Pakets schon benannt
  und hier nicht angefasst."*

Dasselbe steht im Rumpf von `0043-t48-groessen-gegenkraft-5`: *„`regulierung_last` als
neuer Schluessel in T27, Klasse 3, Basispunkte des BIP je Regulierungsstufe, kalibriert wie
`gegenlobby_satz` (`spiel.md` Zeile 1470). In `parameter.toml` fehlt er noch; das ist ein
Folgepaket des Datenbauers und nicht dieses."*

**Nachgemessen am 2026-09-06:** `regulierung_last` kommt in `parameter.toml` null Mal vor.
In `technik.md` kommt er vier Mal vor -- Zeile 2165 (die Formel), 2172 (die Erlaeuterung),
2212 (die Klassenzuordnung) und 3243/3259 (die zwei Auftraege oben). Die Vorgabeseite ist
also vollstaendig; es fehlt allein der Eintrag in der Datei.

## Woher jede Angabe des Kommentarkopfs kommt

Rate nichts davon. Jede Zeile hat eine Quelle, und sie gehoert mit T-Nummer in den
Kommentar:

| Angabe | Quelle |
|---|---|
| Klasse 3 | `technik.md` Zeile 2212, Tabelle der Klassen |
| Einheit „Basispunkte des BIP je Regulierungsstufe" | `technik.md` Zeile 2172 |
| Die Formel | `technik.md` Zeile 2165: `schaden(l, regulierung) = mal_geteilt(bip(l), hub(l, regulierung) · regulierung_last, 10.000)` |
| Kalibriert von wem | wie `gegenlobby_satz` -- der Selbstspieler; siehe dessen Block in derselben Datei |

## Die Schranke

**Sie ist herzuleiten und nicht zu setzen.** `gegenlobby_satz` ist der naechste Verwandte
und traegt `Schranke: >= 0` mit der Begruendung, `specs/` nenne keine obere Schranke und
das Ergebnis sei durch `druck_max` wirksam begrenzt. Fuer `regulierung_last` gilt die
untere Schranke aus demselben Grund; **ob es eine obere gibt, ist nachzusehen und nicht
anzunehmen** -- der Faktor steht in einem `mal_geteilt` mit Zaehler `bip(l) · hub(l,
regulierung) · regulierung_last`, und `hub` fuer die Regulierung geht nach T48 Zeile 2091
bis 10. Findet sich in `specs/` keine obere Schranke, gehoert genau dieser Satz in den
Kommentar, so wie er bei `gegenlobby_satz` dasteht -- eine erfundene Obergrenze waere
schlimmer als eine benannte Luecke.

**Ist die Ueberlaufgrenze aus T6 hier beruehrt, melde das, statt eine Zahl zu waehlen, die
sie zufaellig einhaelt.** Das waere ein Befund an den Architekten und keine
Datenentscheidung.

## Was ausdruecklich nicht dazugehoert

- **Kein Code.** Das Feld `regulierung_last` in der Struktur `Konstanten` in `werte.hpp`
  ist Kernbauer-Arbeit und liegt in `0152`. Diese beiden Pakete fassen verschiedene
  Dateien an und laufen absichtlich nebeneinander.
- **Keine Kalibrierung.** Der Wert bleibt `PLATZHALTER`. Eine Zahl, die wie eine
  Kalibrierung aussieht, ohne dass jemand gerechnet hat, ist die teuerste Sorte Eintrag in
  dieser Datei.
- **Kein Anfassen eines bestehenden Schluessels.**
