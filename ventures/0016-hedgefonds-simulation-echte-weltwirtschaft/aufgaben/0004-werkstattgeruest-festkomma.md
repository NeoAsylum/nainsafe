---
id: 0004-werkstattgeruest-festkomma
rolle: kernbauer
status: gebaut
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeugkette.cmake, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/.gitignore, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/kern.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/sperre.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/festkomma.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/festkomma.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/festkomma_probe.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zustand.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/werte.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schreiber.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/zufall.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/pruefsumme.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/schritt.hpp]
abnahme: Die sieben Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Werkstattgerüst und Festkomma

Das erste Paket mit Code. Es legt den Arbeitsraum an, in den alle folgenden Pakete
schreiben, und baut die eine Sache, an der jede Zahl des Modells hängt: die Rundung.

## Änderung am 2026-09-02 — die Sprache, nicht die Aufgabe

Dieses Paket war gegen Rust geschrieben. **ADR 0011 vom 2026-09-01 legt den Kern auf
C++20 fest**, und der Bauagent hat richtig gegen den ADR gebaut und damit gegen den
Wortlaut seines eigenen Pakets. Der Projektmanager zieht deshalb nach: dieselben
Vorgaben (`technik.md` T1, T2, T3, T4, T6, T7, T9, T13, T29, T47), dieselben sieben
Bedingungen, andere Dateinamen und andere mechanische Nachweise. Der alte Wortlaut steht
in `git show a3cd9e4^:ventures/.../aufgaben/0004-werkstattgeruest-festkomma.md`.

**`technik.md` sagt an zehn Stellen weiter Rust.** Das ist bekannt und gehört Paket
0011; bis dahin gilt für den Bau der ADR, nicht der Vorgabentext. Diese Abnahme prüft
die *Sache* jeder Vorgabe, nicht ihre Rust-Fassung.

**Zweite Änderung: Es gibt einen Übersetzer.** `baulauf.py` übersetzt seit dem
2026-09-02 und legt das Urteil nach `befunde/uebersetzung-<datum>.md`. Der Satz „Dein
Code wird von niemandem übersetzt" gilt nicht mehr; ein Abnahmekriterium darf sich auf
`ctest` stützen. Für dieses Paket ändert das nichts — seine sieben Bedingungen waren
schon vorher mit `Read` und `Grep` prüfbar und bleiben es.

## Was du baust

**Vorgaben:** `technik.md` T1, T2, T3, T4, T6, T7, T9, T13, T29; ADR 0011.

1. **Werkstatt.** Ein Arbeitsbereich mit den Mitgliedern aus T13 — `kern`, `daten`,
   `schnittstelle`, `konsole`, `pruefstand`, `oberflaeche`, `werkzeuge/aufbereitung`.
   Nur `kern` bekommt in diesem Paket ein Verzeichnis; die übrigen legt jeweils ihr
   eigenes Paket an. Die Werkzeugkette nagelt Übersetzer und Sprachfassung fest (T1).
   Jedes Profil trägt `-fwrapv`, das Testprofil zusätzlich
   `-fsanitize=undefined,address` (ADR 0011, Maßnahmen 1 und 2, an der Stelle von Rusts
   `overflow-checks = true` aus T7).
2. **`kern/CMakeLists.txt`** — **null Fremdabhängigkeiten** (T2). Der Kern holt nichts
   herein und linkt nichts dazu; die Standardbibliothek ist keine Fremdabhängigkeit.
3. **Der Sammelkopf `kern/include/kern/kern.hpp`** — die sieben Module des Kerns
   aufgezählt (`festkomma`, `zustand`, `werte`, `schreiber`, `zufall`, `pruefsumme`,
   `schritt`) und die Regeln, die für alle gelten: keine Gleitkommazahl (T4), keine
   streuenden Behälter (T9), weder Bildschirm noch Datei noch Uhr (T13).
4. **Platzhalterdateien für die sechs Module, die du nicht baust.** Je eine Datei mit
   einer Zeile. Das ist keine Entwurfsentscheidung, sondern Kollisionsvermeidung: Nur so
   besitzt jedes spätere Paket genau eine Datei. Trag die Kennung ein, wo du sie kennst —
   `zustand` gehört 0008, `werte` gehört 0002, `zufall` gehört 0012, `pruefsumme`
   gehört 0013.
5. **`kern/src/festkomma.cpp`** samt Kopfdatei — die Rechenregeln, ausgeschrieben:
   - `teile_gerundet(zaehler, nenner) -> int64_t`, Rundung **auf halbe Beträge vom Null
     weg** (T6). Nenner null ist ein harter Fehler, kein Rückgabewert.
   - `mal_geteilt(a, b, c) -> int64_t` über `__int128` (T6, T47, ADR 0011 Maßnahme 3):
     erst multiplizieren, dann teilen, dieselbe Rundungsregel.
   - Ganzzahlige Potenz und Wurzel über Newton auf `__int128` (T29).
   - Kein `/` auf Zustandsgrößen ausserhalb dieser Datei — hier ist die einzige Stelle,
     an der geteilt wird.

**Wird dieses Paket wiedereröffnet:** Eine Moduldatei fasst du nur an, solange sie noch
der Platzhalter ist. Steht dort Code, gehört sie einem anderen Paket, und du meldest den
Konflikt, statt ihn zu überschreiben.

## Abnahme

Sieben Bedingungen, alle mit `Read` und `Grep` prüfbar. Wo eine Bedingung früher einen
Rust-Namen nannte, steht jetzt die Sache; der ADR-Verweis sagt, woher die Ersetzung
kommt.

1. Die Dateien aus `dateien` existieren: Arbeitsbereich, Werkzeugkette,
   `kern/CMakeLists.txt`, Sammelkopf, `festkomma` als Kopf und Quelle mit Probe, dazu
   die sechs Platzhalter.
2. **Keine Gleitkommazahl im Kern** (T4). `grep -rnE 'float|double|f32|f64' kern/`
   liefert nichts ausser der Stelle, die die Sperre selbst durchsetzt oder beschreibt.
3. **Null Fremdabhängigkeiten** (T2): In `kern/CMakeLists.txt` findet
   `grep -nE 'find_package|FetchContent|ExternalProject|add_subdirectory'` nichts, und
   der Kern linkt keine fremde Bibliothek dazu.
4. Der Sammelkopf zählt genau die sieben Module auf, und für jedes existiert eine Datei.
   Ausserdem `grep -rnE '<iostream>|<fstream>|<chrono>|unordered_map|unordered_set' kern/`
   → nichts (T13, T9).
5. `teile_gerundet` rundet **vom Null weg**, und die Probe belegt das für alle vier
   Vorzeichenkombinationen mit ausgeschriebenen Erwartungswerten. Der Prüfer rechnet
   mindestens `teile_gerundet(7, 2) = 4`, `teile_gerundet(-7, 2) = -4`,
   `teile_gerundet(5, 2) = 3` und `teile_gerundet(-5, 2) = -3` von Hand nach.
6. `mal_geteilt` rechnet nachweislich über `__int128`: Eine Probe mit
   `a = 21 000 000 000`, `b = 20`, `c = 10 000` steht in der Datei und nennt
   `42 000 000` als Erwartungswert — dieselbe Zahlenprobe, die T47 führt. Eine zweite
   überschreitet mit dem Produkt `a · b` den `int64_t`-Bereich und liefert trotzdem das
   richtige Ergebnis.
7. Der Nenner null bricht ab, und die Datei sagt an der Stelle, **warum** (T6): ein
   stiller Ersatzwert wäre eine Zahl, die keine Prüfung bemerkt. Ebenso bricht ein
   Ergebnis ab, das nicht mehr in `int64_t` passt (T7 in der Fassung von ADR 0011:
   `-fwrapv` macht den Umbruch definiert, erlaubt ist er damit nicht).

## Was ausdrücklich kein Befund ist

Benennung, Dateiaufteilung innerhalb der Vorgaben, Umfang der Kommentare. Und: dass die
sechs Platzhalter leer sind — das ist der Auftrag, nicht ein Versäumnis.

## Rückläufe

0.

## Status

**2026-09-02, Projektmanager: `offen` → `gebaut`.** Der Kernbauer hat am 2026-09-02
gebaut (Commit `a3cd9e4`, 619 Zeilen C++) und den Status nicht gesetzt. Ich ziehe ihn
nach, weil die Meldung „gebaut" eine Tatsache über vorhandene Dateien ist und keine
Abnahme: Die Dateien existieren, und `befunde/uebersetzung-2026-09-02.md` zeigt
`cmake`, `cmake --build` und `ctest` grün. **Das ist ausdrücklich keine Abnahme** — die
sieben Bedingungen oben hat noch niemand geprüft. `fertig` setze ich erst mit einem
Befund des Kern-Prüfers.
