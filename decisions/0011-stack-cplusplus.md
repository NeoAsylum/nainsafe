---
nr: 0011
titel: Der Kern wird in C++ gebaut — und der Überlauf wird zur geprüften Eigenschaft
datum: 2026-09-01
status: gueltig
ersetzt: null
ersetzt_durch: null
aendert: 0010-stack-kern-und-oberflaeche
betrifft: [technik, bau]
---

# ADR 0011 — C++ statt Rust

## Kontext

ADR 0010 hat den Kern auf Rust festgelegt, mit der Begründung, dort lasse sich
Determinismus **vom Werkzeug** erzwingen. Zwei Dinge haben diese Begründung seither
entwertet, beide vom Betreiber:

**Erstens die Spielstandfrage.** Die plattformübergreifende Reproduzierbarkeit war keine
Eigenschaft des Spiels, sondern eine Folge davon, dass `technik.md` den Spielstand als
*Startwert plus Aktionsfolge* speichert. Speichert man den Zustand — 310 `int64`, 2,5 kB
—, fällt die Anforderung weg. Was bleibt, braucht nur eine Maschine: Regressionstests,
Selbstspiel und Rückvergleich laufen alle im eigenen Nachtlauf.

**Zweitens die Messung.** Vier Agenten, dieselbe Aufgabe, vier Sprachen
(`ventures/0016-.../messung-stack/`):

| Sprache | übersetzt | Zeilen | ns/Schritt | Prüfsumme |
|---|---|---:|---:|---:|
| Java | erster Anlauf | 106 | 316 | 1163237642073673 |
| Rust | erster Anlauf | 78 | 494 | 1163237642073673 |
| C++ | erster Anlauf | 82 | 947 | 1163237642073673 |
| Python | — | 82 | 50.383 | 1163237642073673 |

Alle vier trafen dieselbe Rechenvorschrift beim ersten Anlauf, einschließlich Rundung
auf halbe Beträge von null weg bei negativen Werten. **Für diese Domäne gibt es keinen
messbaren Unterschied in der Agentenzuverlässigkeit.** Python ist an der Geschwindigkeit
gescheitert und damit draußen; zwischen den drei übersetzten Sprachen ist die
Geschwindigkeit gleichgültig (11,8 Mio. Schritte sind überall Sekunden).

## Entscheidung

**Der Kern wird in C++ gebaut.** Vom Betreiber entschieden. Beide Gegenpunkte waren
genannt und sind seine Sache: C++ war in der Messung dreimal langsamer als Java, und
vorzeichenbehafteter Ganzzahlüberlauf ist im Sprachkern undefiniertes Verhalten.

Was für C++ spricht, in seinen Worten und in den Zahlen: Es ist die Sprache der
Spieleentwicklung, mit dem größten Bestand an Spielcode überhaupt — und die Messung
zeigt, dass der Agent sie beim ersten Anlauf fehlerfrei getroffen hat.

Zur Geschwindigkeit: Die 947 ns sind **eine** Umsetzung, nicht die Sprache. Der Agent
hat einen langsamen Weg für den 128-Bit-Zwischenwert gewählt; mit `__int128` ist C++
regelmäßig gleichauf mit oder schneller als Rust. Der Wert ist ein Hinweis auf eine
Umsetzung, kein Urteil über den Stack.

## Der Überlauf wird zur geprüften Eigenschaft

Der eine echte Einwand bleibt, und er wird nicht weggeredet, sondern behandelt. In
Rust hätte `overflow-checks = true` ihn erschlagen; in C++ braucht es drei Maßnahmen
statt einer. Alle drei sind mechanisch und gehören in die Bauvorgabe:

1. **`-fwrapv`** im Freigabe- und im Testprofil. Damit ist vorzeichenbehafteter Überlauf
   **definiert** als Umbruch im Zweierkomplement, und der Optimierer darf ihn nicht mehr
   als „kann nicht vorkommen" auslegen. Das ist die eigentliche Gefahr: nicht der
   Überlauf selbst, sondern was ein Compiler aus seiner Unmöglichkeit folgert.
2. **`-fsanitize=undefined,address`** im Testprofil, und der Prüfstand läuft darüber.
   Ein Überlauf, der trotz `-fwrapv` unbeabsichtigt ist, wird damit im Nachtlauf laut
   statt still.
3. **`__int128` für jeden Zwischenwert** einer Multiplikation-Division, nie ein
   nachträglicher Test auf Überlauf. Das ist ohnehin die Vorgabe aus `technik.md`.

Dazu unverändert aus dem alten Entwurf: **kein Gleitkommatyp im Kern.** Das ist in C++
genauso mit einem `grep` nachweisbar wie in Rust — `float`, `double`, `long double`. Die
Sperre ist eine Prüfregel statt eines Sprachmerkmals, aber sie prüft dasselbe.

**Was C++ nicht bekommt und Rust gehabt hätte:** Speichersicherheit. In einer Fabrik ohne
menschliche Codedurchsicht ist das eine eigene Fehlerklasse — sie zeigt sich beim Käufer,
nicht im Übersetzungslauf. Der Adressen-Sanitizer im Testprofil und der Bruchtester sind
die Gegenmaßnahmen; sie decken Pfade ab, nicht alle Fälle. Das ist der Preis der
Entscheidung, und er steht hier, damit er später nicht überrascht.

## Folgen

- `technik.md` T1 und T2 sind auf Rust geschrieben. Sie werden **nicht von Hand
  überschrieben**, sondern über ein Arbeitspaket vom Architekten neu gefasst — samt der
  Rundungsstelle, die auf Rusts Division gegen null Bezug nimmt (T-Abschnitt zur
  Rundung).
- `baulauf.py:uebersetzen()` ruft nicht mehr `cargo`, sondern erkennt die Bauart am
  Projekt: `CMakeLists.txt`, `Cargo.toml` oder blanke Quelldateien. Der Runner wird damit
  sprachunabhängig, was er von Anfang an hätte sein sollen.
- Die Bauagenten nennen ab sofort C++ und die drei Überlaufmaßnahmen.
- Rust bleibt installiert; die Messung unter `messung-stack/` bleibt liegen. Wer die
  Entscheidung in drei Monaten anzweifelt, findet dort Zahlen statt Meinungen.

## Was unverändert bleibt

Die Oberfläche ist weiter vertagt (ADR 0010). Der Kern muss ohne sie vollständig
spielbar sein; damit ist sie austauschbar, und die Sprachwahl des Kerns bindet sie
nicht.
