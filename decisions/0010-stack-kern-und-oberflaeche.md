---
nr: 0010
titel: Der Stack zerfällt in zwei Entscheidungen — Kern jetzt, Oberfläche später
datum: 2026-09-01
status: gueltig
ersetzt: null
ersetzt_durch: null
betrifft: [technik, bau]
---

# ADR 0010 — Kern in Rust, Oberfläche offen

## Kontext

Der Betreiber: *„Wieso würden wir Rust implementieren? Können wir erstmal nach dem
korrekten Tech Stack suchen?"*

Die Frage ist berechtigt, und zwar aus einem präziseren Grund als „Rust ist ungewöhnlich":
**Der Stack wurde nie entschieden, er wurde gewählt.** Der Architekt hat in `technik.md`
T1 drei Sätze zur Begründung geschrieben — gute Sätze —, aber er hat *für* Rust
argumentiert, nicht *unter* Alternativen. Go, C#, C++, Zig und TypeScript kommen im
ganzen Dokument nicht als Kandidaten vor.

Zusätzlich hat er den einen Einwand, der die Wahl kippen könnte, eingeräumt und dann
weggetauscht, ohne ihn zu messen: *„Ein Bauagent braucht mehr Anläufe bis zum grünen
Übersetzungslauf."*

## Was die Prüfung ergeben hat

**Der Einwand trägt nicht — jedenfalls nicht für diese Domäne.**

| Befund | Wert |
|---|---|
| Rust, Übersetzungserfolg bei Sprachportierung (GPT-4) | 99,5 %, höchster Wert aller geprüften Sprachen |
| Rust-API-Aufgaben, Pass@1 (Claude 3.7 Sonnet) | 65,3 % |
| Kryptografischer Rust-Code, Übersetzungserfolg | 23,3 % |

Der niedrige Wert stammt aus Kryptografie, der schwersten Rust-Domäne. Unser Kern ist
das Gegenteil: Ganzzahlarithmetik, feste Datenstrukturen, kein `async`, keine
Lebenszeit-Generik, `#![forbid(unsafe_code)]`. Das ist der einfache Teil der Sprache.

Dazu kommt ein Umstand, der seit dem 2026-09-01 gilt und den der Architekt noch nicht
kennen konnte: **Der Compiler läuft jetzt im Runner.** Damit ist der Nacharbeitsaufwand
begrenzt und messbar statt geraten — der Agent bekommt den Fehler und behebt ihn. Eine
strengere Sprache wird dadurch billiger, nicht teurer: Ihre Fehler treten mechanisch zu
Tage statt in einem Lauf, den niemand nachvollzieht.

## Entscheidung

**Der Stack ist zwei Entscheidungen, nicht eine.**

### Kern: Rust, jetzt entschieden

Der Ausschlag gibt nicht Geschwindigkeit und nicht Geschmack, sondern Kriterium 3 aus
`agentenbau.md` — Determinismus, ohne den kein Agent das Produkt je **verbessern**
kann, sondern nur **verändern**.

**Rust ist die einzige verbreitete Sprache, in der sich Determinismus vom Werkzeug
erzwingen lässt statt von der Sorgfalt des nächsten Agenten.** Ein Kern-Kasten ohne
jeden Gleitkommatyp ist mit einem `grep` nachweisbar; `overflow-checks = true` gilt auch
im Freigabeprofil; `BTreeMap` statt streuender Mengen macht die Iterationsreihenfolge
zur Eigenschaft des Typs.

Die Alternativen, an derselben Frage gemessen:

| Stack | Determinismus erzwingbar | 11,8 Mio. Schritte/Nacht | Einzelprogramm |
|---|---|---|---|
| **Rust** | **ja, vom Typsystem** | Minuten | ja |
| Go | nein — `float64` nicht verbietbar, Kartenreihenfolge absichtlich gestreut | Minuten | ja |
| C# | nein — nur durch Disziplin | Minuten | mit Laufzeit |
| C++ | teilweise — keine Sperre gegen Gleitkomma | Minuten | ja |
| TypeScript | nein — Gleitkomma überall | Stunden | 200 MB |
| Python | nein | **Stunden** | nein |

Go wäre der stärkste Gegenkandidat — Agenten schreiben es sehr zuverlässig, es
übersetzt zu einem Einzelprogramm. Es scheitert an derselben Stelle wie alle anderen:
Man kann `float64` nicht verbieten, und die Kartenreihenfolge ist absichtlich zufällig.
Determinismus wäre dann eine Regel, an die sich jeder Agent halten müsste — und **die
ganze Prämisse dieser Fabrik lautet, dass geprüft wird, was sich prüfen lässt, statt
sich auf Sorgfalt zu verlassen.**

### Oberfläche: offen, später zu entscheiden

`technik.md` nennt im Frontmatter `egui/eframe`. **Diese Festlegung wird zurückgenommen
und vertagt** — nicht weil egui falsch wäre, sondern weil sie jetzt nicht getroffen
werden muss und später besser zu treffen ist.

Möglich ist das, weil die Architektur es ohnehin verlangt: *Das Spiel muss ohne
Darstellung vollständig spielbar sein, das Modell fragt die Sicht nie etwas.* Damit ist
die Oberfläche austauschbar, solange der Kern steht.

Zwei Kandidaten, wenn es soweit ist:

- **egui im selben Kasten** — eine Sprache, eine Werkzeugkette, ein Programm. Die
  einfachste Auslieferung.
- **Godot** — 8 bis 10 Prozent aller neuen Steam-Spiele, beste 2D- und
  Oberflächenpipeline der drei großen Engines, keine Lizenzgebühren, Steam-Anbindung
  gelöst. Preis: eine zweite Sprache und eine zweite Werkzeugkette. **Für den Kern fällt
  es aus** — seine Physik rechnet durchgehend in Gleitkomma und ist für deterministische
  Simulation ausdrücklich ungeeignet. Als reine Sicht auf einen fremden Kern ist das
  gleichgültig.

Die Entscheidung fällt, wenn der Kern spielbar ist und der Selbstspieler läuft — dann
ist auch bekannt, was die Oberfläche zeigen muss.

## Folgen

- Kein Umbau. Der Kern bleibt, wie `technik.md` ihn beschreibt.
- Die Oberflächenfestlegung in `technik.md` gilt als vertagt; ein Arbeitspaket dafür
  entsteht erst, wenn der Kern spielbar ist.
- **Was hier fehlte und künftig nicht fehlen soll:** Die Rolle des Architekten verlangt
  bisher nur *„wähle keinen exotischen Stack"* und zwei Sätze Begründung. Das erzeugt
  ein Argument, keinen Vergleich. Sie verlangt ab sofort eine Tabelle mit mindestens
  drei Kandidaten, gemessen an den Kriterien des Vorhabens — und die Frage, welche
  Festlegung sich **vertagen** lässt.

## Quellen

- Übersetzungserfolg nach Sprache: <https://arxiv.org/pdf/2405.11514>
- Rust-Pass@1 und API-Aufgaben: <https://arxiv.org/pdf/2503.16922>
- Kryptografischer Rust-Code: <https://arxiv.org/pdf/2604.27001>
- Godot-Anteil an Steam-Veröffentlichungen: <https://www.strayspark.studio/blog/godot-vs-unity-vs-unreal-2026>
- Godot und deterministische Simulation: <https://school.gdquest.com/glossary/deterministic_simulation>

Alle abgerufen am 2026-09-01.
