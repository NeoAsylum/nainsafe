---
id: 0009-parameterdatei-schluessel
rolle: datenbauer
status: gebaut
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml]
abnahme: Jeder in T27 und T51 genannte Schlüssel steht in der Datei, mit Skalenklasse nach T5, Wertebereich, Herkunft der Schranke und einem Startwert innerhalb der Schranken; kein Schlüssel ohne Klasse, keine Klasse ohne Schlüssel im Text.
---

# `parameter.toml` — die Schlüssel, nicht die Zahlen

T27: „Die Kalibrierdatei liegt ausserhalb des Codes, und jeder Schlüssel trägt eine
Skalenklasse." Ein Parameterschlüssel ohne Klasse ist derselbe Fehler wie eine Adresse
ohne Klasse — und es ist derselbe Fehler, an dem Befund 2 der Runde 6 hing.

**Die Zahlen sind nicht dein Auftrag.** `spiel.md` sagt es und `technik.md` Abschnitt 12
wiederholt es: Die Werte werden vom Selbstspieler *gesucht*, nicht entworfen. Was du
lieferst, ist die Form — jeder Schlüssel, seine Einheit, seine Schranken und die Stelle,
an der die Schranke steht. Der Startwert ist ein Platzhalter innerhalb der Schranken und
als solcher gekennzeichnet.

Vorher lesen: `technik.md` T5, T27, T50, T51, T47.

## Was hineingehört

1. **Die elf Schlüssel aus der Tabelle in T27**, jeder mit Klasse und Bedeutung:
   `stufenweite`, `stufen_max`, `ausstiegsabschlag`, `zwangsabschlag`, `aufschlag`,
   `lobbykosten`, `beteiligungsrabatt`, `gegenlobby_satz`, `druck_max`,
   `regulierung_stufen`, sowie `schrittweite[i]`, `instrument_min[i]`,
   `instrument_max[i]` je Instrument.
2. **Die übrigen Kalibriergrößen, die T27 im Fliesstext aufzählt:** Mandatsschwelle
   (`schwelle_v`, `schwelle_e`), drei Aufsichtsschwellen, Nachahmergeschwindigkeit,
   Anlegerabzugsanteil, Startkapital, Startzustimmung, Startstand der
   Finanzmarktregulierung, Verzögerungen, Elastizitäten.
3. **Je Schlüssel die Schranke und ihre Quelle**, wo `specs/` eine nennt — nicht
   erfunden, sondern zitiert:
   - `lobbykosten ≥ 1` (T50), `1 ≤ beteiligungsrabatt ≤ 10.000` (T50),
   - `stufenweite ≥ 1` und ganzzahlig (T47), Klasse 4 und **kein Geldbetrag** (T5),
   - `aufschlag ≥ aufschlag_min` mit `aufschlag_min = 1 − min(leitzins_pfad)`
     (T51, T23 Punkt 5) — die Zahl selbst kommt aus dem Jahrgang und steht hier als
     Verweis, nicht als Wert,
   - `instrument_min[leitzins] ≥ 1 − aufschlag` (T51) — die eine Stelle des Modells, an
     der ein Kurs unendlich würde,
   - Wertebereiche der vier Instrumente aus der Tabelle in T51.
4. **Ein Kommentar je Schlüssel, der sagt, wer ihn kalibriert und woran er scheitert.**
   Für `startkapital` und `stufenweite` gehört die Bedingung aus T47 dazu: Eine Stufe
   auf dem grössten der sechzehn Startmarktwerte muss bezahlbar sein, und erreichbare
   Stufenzahlen müssen die Aufsichtsschwellen erreichen. Beides zugleich ist nicht
   garantiert; die beiden Zahlen dafür weist der Jahrgangsbau im Manifest aus.

## Abnahme

1. Jeder in T27 und T51 genannte Schlüssel steht in der Datei. Der Prüfer legt die
   beiden Tabellen daneben und zählt ab.
2. **Kein Schlüssel ohne Skalenklasse.** Das ist die Vorgabe aus T27 und der eigentliche
   Zweck des Pakets.
3. Jeder Startwert liegt innerhalb der eigenen Schranke, und jede Schranke nennt die
   Vorgabe, aus der sie stammt.
4. Die Datei ist gültiges TOML und trägt keinen Wert, der eine Kalibrierung vorwegnimmt,
   ohne als Platzhalter gekennzeichnet zu sein.

## Grenzen

- Du **entwirfst keine Zahl.** Wo du einen Platzhalter brauchst, schreib ihn hin und
  markier ihn. Ein Wert, der wie eine Kalibrierung aussieht und keine ist, kostet den
  Selbstspieler einen Lauf.
- Du **rührst den Code nicht an.** Das Einlesen in eine Struktur mit benannten Feldern
  (T27, T9) ist ein späteres Paket im Kasten `daten`.

## Rückläufe

0.

## Status

**2026-09-02, Projektmanager: `offen` → `gebaut`.** `parameter.toml` liegt mit 763
Zeilen vor und trägt im Kopf dieses Paket mit Stand 2026-09-02; der Datenbauer hat den
Status nicht gesetzt. Nachgezogen, damit der Daten-Prüfer das Paket sieht. Keine
Abnahme — ob jeder Schlüssel aus T27 und T51 mit Klasse, Wertebereich, Herkunft der
Schranke und einem Startwert innerhalb der Schranken dasteht, misst der Prüfer.
