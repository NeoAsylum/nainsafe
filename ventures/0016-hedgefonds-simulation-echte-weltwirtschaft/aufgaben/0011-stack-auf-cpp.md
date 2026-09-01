---
id: 0011-stack-auf-cpp
rolle: architekt
status: offen
haengt_an: []
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: T1 und T2 nennen C++20 statt Rust, samt der drei Ueberlaufmassnahmen aus ADR 0011. Jede Stelle, die auf ein Rust-Merkmal Bezug nimmt (Division gegen null, overflow-checks, BTreeMap, forbid(unsafe_code), cargo vendor), ist neu gefasst. Ein grep nach "Rust", "cargo" und "rustc" in technik.md findet nichts mehr ausser einem Verweis auf ADR 0011.
---

# Der Stack wird auf C++ umgeschrieben

Der Betreiber hat am 2026-09-01 C++ entschieden (ADR 0011). `technik.md` ist auf Rust
geschrieben — T1, T2 und mehrere Stellen der Arithmetik.

**Der Inhalt bleibt.** Zustandsaufbau, 310 Adressen, dreizehn Skalenklassen, Formeln,
Herkunftseintraege, Jahrgangskonstanten — nichts davon haengt an einer Sprache. Nur die
Bauart wird ausgetauscht.

## Was ausdruecklich neu zu fassen ist

- **T1 Stack.** C++20, `g++`, Bau ueber CMake. Und diesmal **mit Tabelle** — mindestens
  drei Kandidaten an den Kriterien dieses Vorhabens gemessen, wie es deine Rolle seit
  dem 2026-09-01 verlangt. Die Zahlen liegen vor: `ventures/0016-.../messung-stack/`.
- **T2 Abhaengigkeiten.** `#![forbid(unsafe_code)]` gibt es nicht in C++. Was tritt an
  seine Stelle? Der Kern bleibt ohne Fremdbibliothek — sag, wie das erzwungen wird.
- **Die drei Ueberlaufmassnahmen** aus ADR 0011: `-fwrapv`, Sanitizer im Testprofil,
  `__int128` fuer jeden Zwischenwert.
- **Die Rundungsstelle.** Sie begruendet die Rundung mit Rusts Divisionsverhalten. C++
  schneidet seit C++11 ebenfalls gegen null ab — die Regel bleibt, die Begruendung
  aendert sich.
- **Reihenfolge statt `BTreeMap`.** Determinismus verlangt feste Iterationsreihenfolge;
  nenn das C++-Aequivalent und sag, was verboten ist.

## Was du nicht tust

Kein neuer Entwurf, keine neue Fassung des ganzen Dokuments. **Nur die Stellen, die an
der Sprache haengen.** Das Dokument hat sechs Fassungen und 148 kB hinter sich; eine
siebte Rundumerneuerung ist ausdruecklich nicht gewollt.
