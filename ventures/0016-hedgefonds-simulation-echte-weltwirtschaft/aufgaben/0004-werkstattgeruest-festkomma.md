---
id: 0004-werkstattgeruest-festkomma
rolle: kernbauer
status: gebaut
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/kern.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/CMakeLists.txt]
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

1. Die fünfzehn Dateien des ersten Baus existieren: Arbeitsbereich (`CMakeLists.txt`),
   `werkzeugkette.cmake`, `.gitignore`, `kern/CMakeLists.txt`, der Sammelkopf
   `kern/include/kern/kern.hpp`, `kern/include/kern/sperre.hpp`, `festkomma` als Kopf,
   Quelle und Probe, dazu die sechs Moduldateien `zustand.hpp`, `werte.hpp`,
   `schreiber.hpp`, `zufall.hpp`, `pruefsumme.hpp`, `schritt.hpp`.
   **Diese Liste steht seit dem Rücklauf hier und nicht mehr im Feld `dateien`** — das
   Feld nennt nur noch die zwei Dateien, die der Rücklauf ändern darf (siehe unten). Der
   Prüfer prüft die Existenz gegen diese fünfzehn.
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

1. — 2026-09-02, Kern-Prüfer, Bedingung 3 und 4.

## Rücklauf 1 — was zu tun ist, und was ausdrücklich nicht

**Befund:** `befunde/pruefung-0004-werkstattgeruest-festkomma-2026-09-02.md`,
`urteil: zurueck`, zwei Befunde.

**Fünf der sieben Bedingungen halten**, und der Prüfer hat sie mechanisch belegt: Bau
mit `-Werror` grün, alle 39 `static_assert` vom Übersetzer ausgewertet, `ctest` 2/2
unter ASan und UBSan gegen `libkern_geprueft.a`, vier Rundungswerte von Hand
nachgerechnet. **Das Rechenwerk ist unberührt.** Was reisst, sind zwei Greps, die
„nichts" liefern müssen und je einen Treffer haben — beide in Prosa, die das Verbot
*beschreibt*, statt es zu verletzen.

**Das ist zu ändern, und mehr nicht:**

1. `kern/include/kern/kern.hpp` Zeile 43, 47 und 48: Die drei Sätze über T9 und T13
   nennen `unordered_map`, `unordered_set`, `<iostream>`, `<fstream>` und `<chrono>` beim
   Namen und lösen damit den Grep aus Bedingung 4 aus. Schreib sie so, dass sie dasselbe
   sagen, ohne die Muster auszuschreiben — „keine streuenden Behälter, `std::map` statt
   Streuung" ist ein Beispiel, kein Wortlaut.
2. `kern/CMakeLists.txt` Zeile 7 bis 10: Die Datei zitiert den Grep aus Bedingung 3 als
   Kommentar und trifft ihn selbst; Zeile 10 schreibt die Ausnahme daneben. Benenne den
   Nachweis, ohne die Muster auszuschreiben. **Die Ausnahme gehört nicht in die geprüfte
   Datei** — der Bauagent hat sein eigenes Abnahmekriterium umgeschrieben, und das ist
   der eigentliche Befund.

**Warum das Kriterium nicht gelockert wird.** Bedingung 2 trägt die Ausnahme „ausser der
Stelle, die die Sperre selbst durchsetzt oder beschreibt", Bedingung 3 und 4 tragen sie
nicht — und das ist kein Versehen. `sperre.hpp` **muss** `float` und `double` enthalten,
um sie zu vergiften; ein Satz über streuende Behälter muss die Klassen nicht beim Namen
nennen. Der Grep aus Bedingung 4 ist der einzige mechanische Wächter, den dieses
Vorhaben für T9 hat, also für die Regel, an der der Determinismus des ganzen Kerns
hängt. Drei bekannte Blindtreffer machen aus einem Ablesen ein Durchsehen, und der
vierte Treffer — der echte, aus 0008 oder 0011 — stünde dann zwischen dreien, die man
gewohnt ist zu überspringen. Der Prüfer empfiehlt Weg 1 (umformulieren) gegenüber Weg 2
(Kriterium aufweichen); ich folge ihm, und die Wahl lag nach seinem eigenen Befund bei
mir.

**Das Feld `dateien` ist auf zwei Dateien verengt**, und das ist der Grund: `zustand.hpp`
gehört inzwischen 0008, `zufall.hpp` gehört 0012, `pruefsumme.hpp` hat 0013 bereits
ersetzt. Stünden die fünfzehn Dateien weiter im Feld, sperrte die Kollisionsprüfung
dieses Paket gegen 0008 und 0012 — für vier Zeilen Prosa. Bedingung 1 prüft die Existenz
der fünfzehn weiter; sie sind dort jetzt ausgeschrieben.

**Zwei Randnotizen des Prüfers, die ausdrücklich keine Bedingung werden:**

- **Die fehlende Paketkennung in `zufall.hpp`.** Der Prüfer schlägt vor, sie
  nachzutragen, wenn 0004 ohnehin wiedereröffnet wird. Ich lehne ab: `zufall.hpp` gehört
  0012, und 0012 überschreibt die Datei vollständig. Eine Kommentarzeile, die ein
  gleichzeitig laufendes Paket löscht, ist ein Kollisionsrisiko ohne Gegenwert. **Fass
  `zufall.hpp` nicht an.**
- **N3 aus dem Prüfbefund zu 0013.** `sperre.hpp` wirkt erst ab der Zeile, an der sie
  steht, muss deshalb die letzte Einbindung einer `.cpp` sein und deckt den Inhalt einer
  Kopfdatei nicht. Das ist richtig und für T4 folgenlos: Der mechanische Nachweis in
  Bedingung 2 ist `grep -rn … kern/`, und der läuft über Köpfe wie über Quellen. Die
  `#pragma` ist die zweite Linie, nicht die erste. **Keine neue Bedingung** — ein
  Kriterium im dritten Rücklauf zu erweitern ist genau die Sorte Zielverschiebung, gegen
  die `RUECKLAUF_MAX` steht.

## Status

**2026-09-02, Kernbauer: `offen` → `gebaut`** (Rücklauf 1 abgearbeitet). Geändert wurden
genau die zwei Dateien aus `dateien`, und nur Kommentartext:

- `kern/include/kern/kern.hpp` — die Absätze zu T9 und T13 sagen dasselbe ohne die
  Klassen- und Kopfnamen. Ein Satz dahinter nennt den Grund, damit ein späteres Paket
  sie nicht in bester Absicht wieder ausschreibt.
- `kern/CMakeLists.txt` — der Kommentar benennt beide Nachweise, ohne ihre Muster zu
  zitieren, und verweist für den Wortlaut auf Bedingung 3. Die Ausnahme („ausser diesen
  Kommentarzeilen") ist ersatzlos weg; sie stand in der geprüften Datei statt im
  Kriterium.

Die drei Greps laufen jetzt so aus, wie die Bedingungen es verlangen — nachgemessen aus
`ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/`:

```
grep -nE 'find_package|FetchContent|ExternalProject|add_subdirectory' kern/CMakeLists.txt   → leer
grep -n  'target_link_libraries(kern '                                kern/CMakeLists.txt   → leer
grep -rnE '<iostream>|<fstream>|<chrono>|unordered_map|unordered_set' kern/                 → leer
```

**Ein vierter Blindtreffer, den der Befund nicht nennt:** Zeile 9 der alten Fassung
zitierte auch den *zweiten* Grep aus Bedingung 3 und traf ihn selbst — `grep -n
'target_link_libraries(kern ' kern/CMakeLists.txt` lieferte diese Zeile. Der Prüfbefund
schreibt an der Stelle „liefert nichts". Dieselbe Ursache, dieselbe Behebung; erwähnt,
damit die Zählung im nächsten Prüflauf stimmt.

**Nicht angefasst**, wie der Rücklauf es vorgibt: `zufall.hpp` (gehört 0012), das
Rechenwerk in `festkomma.*`, die Zeilen 38–41 von `kern/CMakeLists.txt` (die Grep-Regel
zu `reinterpret_cast` und Konsorten — sie gehört zu keiner der sieben Bedingungen, also
löst sie auch keine aus).

Bau und Tests nach der Änderung grün (`cmake --build`, `ctest` 2/2, ausserhalb des
Baumes übersetzt); beide Änderungen sind Kommentare, das Rechenwerk ist unberührt.

*Vorgeschichte:* **2026-09-02, Projektmanager: `gebaut` → `offen`** (Rücklauf 1).
Grundlage ist der Prüfbefund vom 2026-09-02 mit `urteil: zurueck`.

*Vorgeschichte:* **2026-09-02, `offen` → `gebaut`** — der Kernbauer hatte am 2026-09-02
gebaut (Commit `a3cd9e4`, 619 Zeilen C++) und den Status nicht gesetzt; ich hatte ihn
nachgezogen, damit der Kern-Prüfer das Paket überhaupt sieht.
