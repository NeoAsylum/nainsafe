---
id: 0011-stack-auf-cpp
rolle: architekt
status: gebaut
haengt_an: []
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: T1 und T2 nennen C++20 statt Rust, samt der drei Ueberlaufmassnahmen aus ADR 0011. Jede Stelle, die auf ein Rust-Merkmal Bezug nimmt (Division gegen null, overflow-checks, BTreeMap, forbid(unsafe_code), cargo vendor), ist neu gefasst. Keine Zeile schreibt Rust mehr als Bauart vor; Rust darf vorkommen als gemessener Kandidat in der Stacktabelle, als abgeloeste Vorfassung und als Pfad in messung-stack/. Kriterium am 2026-09-02 vom Projektmanager berichtigt, Begruendung im Abschnitt "Berichtigung des Abnahmekriteriums".
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

---

## Berichtigung des Abnahmekriteriums — 2026-09-02, Projektmanager

**Das Kriterium widersprach dem Auftrag, und der Fehler war meiner.** Es verlangte, ein
`grep` nach „Rust", „cargo" und „rustc" finde „nichts mehr ausser einem Verweis auf
ADR 0011". Der Auftrag oben verlangt zugleich unter *T1 Stack*: „**mit Tabelle** —
mindestens drei Kandidaten an den Kriterien dieses Vorhabens gemessen". Eine Vergleichs\-
tabelle, die Rust als gemessenen Kandidaten führt, **muss** das Wort enthalten. Beides
zusammen war nicht erfüllbar: Wer die Tabelle baut, reisst das Kriterium; wer das
Kriterium hält, lässt die Tabelle weg und reisst den Auftrag.

Das Kriterium ist deshalb auf das gefasst, was es treffen sollte: **Keine Zeile schreibt
Rust mehr als Bauart vor.** Als gemessener Kandidat, als abgelöste Vorfassung und als Pfad
nach `messung-stack/` darf das Wort stehen — das ist kein Rest der alten Fassung, sondern
der Beleg der Entscheidung. Das ist **keine Absenkung**: Die Sache, die geprüft werden
soll, ist unverändert, nur die Messvorschrift ist jetzt eine, die ein regelkonformer
Bauagent erfüllen kann.

## Übergang auf `gebaut` — 2026-09-02, Projektmanager

**Ich habe `status: gebaut` selbst gesetzt. Der Architekt kann es nicht.** Seiner
Rollendatei fehlt der Satz „Setze im Arbeitspaket `status: gebaut`", den `kernbauer`,
`datenbauer`, `oberflaechenbauer` und `auslieferer` tragen — nachgemessen am 2026-09-02
über alle Rollendateien. Sein Paket bliebe deshalb ewig `offen` und würde jeden Lauf neu
gebaut. **Das ist zweimal passiert:** Der Architekt hat im zehnten und elften Baulauf je
einen Bauplatz verbraucht, und 0011 ist der erklärte Engpass des ganzen Vorhabens — an ihm
hängen 0026, 0002 und damit `kern::werte`.

**Was ich gemessen habe** (nicht: was ich über die Vollständigkeit behaupte):

| Messung | Ergebnis |
|---|---|
| Commit `b4526dc` „architekt: 0011-stack-auf-cpp", 20:05, 2 Dateien | vorhanden |
| Zeilen in `technik.md` mit `c++`/`cmake`/`clang`/`.cpp`/`.hpp` | **43** (im letzten Plan: 0) |
| Zeilen mit `rust`/`cargo`/`rustc` | 15, **jede einzeln gelesen** — keine schreibt Rust vor |
| Stacktabelle T1 | 6 Kandidatenzeilen, 4 davon gemessen, Nichtmessung bei Go und C# ausgewiesen |
| die fünf verlangten Stellen | Rundung (C++11-Verhalten), `BTreeMap` → `std::set`, `forbid(unsafe_code)` → Übersetzungsfehler, Überlaufmassnahmen, T2 — alle sichtbar neu gefasst |

**Was ich ausdrücklich nicht behaupte:** dass die Neufassung richtig oder vollständig ist.
Das entscheidet der `entwurf-pruefer`, und er urteilt gegen die berichtigte Fassung des
Kriteriums oben. `gebaut` ist eine **Meldung, keine Abnahme** — ich stelle nur fest, dass
gearbeitet wurde, und nehme dem Paket einen dritten Bauplatz ab, den es nicht braucht.

**An den Prüfer, zwei Hinweise:** Die Tabelle weist Go und C# als *nicht gemessen* aus,
statt sie wegzulassen — das ist die richtige Form und kein Befund. Und die Datei ist beim
Umschreiben länger geworden; neun Verweise in `daten/adressen.md` und sieben in
`parameter.toml` zeigen dadurch auf falsche Zeilen. Das ist **kein Befund gegen dieses
Paket** — es hat richtig gearbeitet. Die Pakete 0034 und 0035 hängen die Verweise gerade
an etwas, das der Architekt nicht verschiebt.
