---
id: 0004-werkstattgeruest-festkomma
rolle: kernbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/Cargo.toml, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/rust-toolchain.toml, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/Cargo.toml, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/lib.rs, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/festkomma.rs]
abnahme: Die sieben Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Werkstattgerüst und Festkomma

Das erste Paket mit Code. Es legt den Arbeitsraum an, in den alle folgenden Pakete
schreiben, und baut die eine Sache, an der jede Zahl des Modells hängt: die Rundung.

Vorher lesen: `ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/rueckstand.md`,
Abschnitt *Es gibt keinen Übersetzer*. Dein Code wird von niemandem übersetzt, bevor der
Betreiber es tut.

## Was du baust

**Vorgaben:** `technik.md` T1, T2, T3, T4, T6, T7, T9, T13, T29.

1. **Werkstatt.** `Cargo.toml` als Arbeitsbereich mit den Mitgliedern aus T13 —
   `kern`, `daten`, `schnittstelle`, `konsole`, `pruefstand`, `oberflaeche`,
   `werkzeuge/aufbereitung`. Nur `kern` bekommt in diesem Paket ein Verzeichnis; die
   übrigen legt jeweils ihr eigenes Paket an. `rust-toolchain.toml` nagelt die Version
   fest (T1). Das Freigabeprofil trägt `overflow-checks = true` (T7).
2. **`kern/Cargo.toml`** — **null Fremdabhängigkeiten** (T2). Der Abschnitt
   `[dependencies]` ist leer und bleibt es.
3. **`kern/src/lib.rs`** — `#![forbid(unsafe_code)]` (T2), `#![deny(clippy::float_arithmetic)]`
   (T4), und die Moduldeklarationen für den ganzen Kern:
   `festkomma`, `zustand`, `werte`, `schreiber`, `zufall`, `pruefsumme`, `schritt`.
4. **Platzhalterdateien für die sechs Module, die du nicht baust.** Je eine Datei mit
   einer Zeile: `//! Platzhalter. Gebaut in Paket <Kennung>.` Das ist keine
   Entwurfsentscheidung, sondern Kollisionsvermeidung: Nur so kann jedes spätere Paket
   genau eine Datei besitzen, ohne dass zwei Bauagenten gleichzeitig `lib.rs` anfassen.
   Trag die Kennung ein, wo du sie kennst — `zustand` gehört 0008, `werte` gehört 0002;
   für die übrigen schreib `noch kein Paket`.
5. **`kern/src/festkomma.rs`** — die Rechenregeln, ausgeschrieben:
   - `teile_gerundet(zaehler, nenner) -> i64`, Rundung **auf halbe Beträge vom Null
     weg** (T6). Nenner null ist ein harter Fehler, kein Rückgabewert.
   - `mal_geteilt(a, b, c) -> i64` über `i128` (T6, T47): erst multiplizieren, dann
     teilen, dieselbe Rundungsregel.
   - Ganzzahlige Potenz und Wurzel über Newton auf `i128` (T29).
   - Kein `/` auf Zustandsgrößen ausserhalb dieser Datei — hier ist die einzige Stelle,
     an der geteilt wird.

## Abnahme

Sieben Bedingungen, alle mit `Read` und `Grep` prüfbar:

1. Die fünf Dateien aus `dateien` existieren, dazu die sechs Platzhalter.
2. `grep -rn 'f32\|f64\|as f' kern/` liefert **nichts** (T4).
3. `grep -n 'dependencies' -A5 kern/Cargo.toml` zeigt einen leeren Abschnitt (T2).
4. `lib.rs` trägt `forbid(unsafe_code)` und deklariert genau die sieben Module; für
   jedes existiert eine Datei.
5. `teile_gerundet` rundet **vom Null weg**, und die Datei enthält Tests, die das für
   alle vier Vorzeichenkombinationen mit ausgeschriebenen Erwartungswerten belegen.
   Der Prüfer rechnet mindestens `teile_gerundet(7, 2) = 4`, `teile_gerundet(-7, 2) = -4`,
   `teile_gerundet(5, 2) = 3` und `teile_gerundet(-5, 2) = -3` von Hand nach.
6. `mal_geteilt` rechnet nachweislich über `i128`: Ein Test mit `a = 21_000_000_000`,
   `b = 20`, `c = 10_000` steht in der Datei und nennt `42_000_000` als Erwartungswert —
   dieselbe Zahlenprobe, die T47 führt. Ein zweiter Test überschreitet mit dem Produkt
   `a · b` den `i64`-Bereich und liefert trotzdem das richtige Ergebnis.
7. Der Nenner null bricht ab, und die Datei sagt an der Stelle, **warum** (T6): ein
   stiller Ersatzwert wäre eine Zahl, die keine Prüfung bemerkt.

## Was ausdrücklich kein Befund ist

Benennung, Dateiaufteilung innerhalb der Vorgaben, Umfang der Kommentare. Und: dass die
sechs Platzhalter leer sind — das ist der Auftrag, nicht ein Versäumnis.

## Rückläufe

0.
