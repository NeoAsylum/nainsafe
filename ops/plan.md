# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02, nach dem fünften Baulauf (05:47–06:14).

## Wo das Vorhaben steht

Der Kern ist von vier auf **sechs von neun Kästen** gewachsen — der größte Sprung bisher:
`zustand` (Paket 0008, 726 + 842 Zeilen plus 521 Zeilen Probe) und `zufall` (0012), beide
übersetzt, `ctest` 4/4 grün, 0012 bereits `geprueft`. Damit ist die Frage meiner letzten
drei Pläne beantwortet: 0008 war nicht festgefahren, es hat geliefert. Die Datenseite
trägt weiter, der Übersetzungslauf bleibt grün.

## Der Engpass

**Der Kern hat ab dem nächsten Lauf keine baubare Aufgabe mehr.** `baulauf.py --trocken`
zieht vier Pakete, und alle vier sind Datenpakete (0009, 0015, 0017, 0018) — **kein
einziges Kernpaket**. Die drei leeren Kästen sind sämtlich zu:

- `werte` (0002) — `blockiert`, wartet auf die Klasse-2-Entscheidung
- `schreiber` (0016) — hängt an 0008, und 0008 steht auf `gebaut`, nicht `fertig`
- `schritt` — hat kein Paket, weil „Schaden" in Gegenkraft 5 keine Rechenvorschrift hat

Nur der mittlere löst sich allein: 0008 wird nächsten Lauf geprüft, im übernächsten
`fertig`, dann startet 0016. Die beiden anderen brauchen den Architekten — und der ist
weiter nicht einplanbar (`baulauf.py:49`, heute nachgesehen, unverändert).

Das ist keine Fortschreibung. Bisher kostete „Architekt nicht einplanbar" **ein**
blockiertes Paket; seit 0008 und 0012 gebaut sind, kostet es **den ganzen Kern**. Der
Preis der Vertagung ist in einem Lauf um eine Größenordnung gestiegen.

## Was quer liegt

- **0015 lieferte nichts** — kein Commit auf seiner Paketdatei, kein Logbucheintrag,
  `adressen.md` unverändert seit dem 2026-09-01. Damit ging zwei Läufe hintereinander
  **genau einer von vier Bauplätzen** leer aus, beide Male ein anderes Paket (vorher 0008,
  das diesmal lieferte). **Meine Vermutung von gestern war falsch:** Es liegt nicht am
  Paket, es liegt am Platz. Gemessene Rate 1 von 4, über zwei Läufe. Für einen Eingriff zu
  dünn, für die dritte Messung gehört es hierher.
- **0009: Arbeit da, Meldung nicht.** Der Datenbauer hat um 05:47 `parameter.toml` um 87
  Zeilen geändert, aber `status: offen` stehen lassen und nichts ins Logbuch geschrieben.
  Folge: Der Trockenlauf plant 0009 als **Bau**, nicht als **Review** — der Prüfer sieht
  Runde 2 nie, der nächste Datenbauer findet fertige Arbeit vor. Kostet einen Lauf und
  heilt vermutlich selbst. Kommt 0009 ein zweites Mal ohne Statuswechsel zurück, ist es
  kein Zufall.
- **Der Kernbauer meldet drei eigene Unsicherheiten zu 0008**, eine davon inhaltlich:
  `FondsGroesse` folgt der Reihenfolge des Adressverzeichnisses, T15 führt `sichtbarkeit`
  und `anlegerbestand` vertauscht. Er hat die Stelle im Code vermerkt; der Prüfer bekommt
  0008 im nächsten Lauf. Richtiger Ort, kein Eingriff.
- **`technik.md` sagt elfmal Rust, gebaut wird C++20** (ADR 0011). Unverändert. Paket
  0011, Rolle `architekt`.
- **Drei Sachen brauchen dieselbe Hand am Runner**, keine ist ein Gate: ein TOML-Parser
  neben `uebersetzen()` (0009 und 0017 können ihre Abnahme sonst nicht nachweisen — zwei
  Runden lang konnte es weder Bauer noch Prüfer), die Rohdaten, die keine Baurolle
  beschaffen kann, und A unten.
- **Die 170-gegen-121-Lücke** unberührt, blockiert weiter nichts.

## Was der Betreiber entscheiden muss

Dieselbe eine Frage, zum fünften Mal — **und das bedeutet nichts:** Alle fünf Pläne sind
seit dem letzten Griff des Betreibers (2026-09-01, 21:02) in derselben Nacht entstanden.
Wiederholung ist hier kein Widerstand.

**Wie kommt der Entwurf in einen Lauf?**

- *A:* `architekt` und `spielentwerfer` in `BAUROLLEN` aufnehmen (`baulauf.py:49`).
  **Neu nachgemessen, und der Grund, warum A billig ist:** Beide stehen schon in `REVIEW`
  (Zeile 63/64 → `entwurf-pruefer`), bekommen ihre Prüfung also automatisch. Und die
  Rücklaufbremse des Baulaufs zählt **je Paket** (`baulauf.py:218-227`), nicht wie die des
  Konzeptlaufs über alles — die fünf `zurueck` des Entwurfsprüfers auf 0001 blockieren
  0011 nicht. Eine Zeile, kein Nebeneffekt.
- *B:* Von Hand `python3 agents/lauf.py architekt 0016-…`. Funktioniert nachweislich —
  aber für jede der sieben offenen Entwurfssachen einzeln.
- *C:* Nichts tun. Kostet ab sofort den Kern, nicht ein Paket.

**Empfehlung: A**, in derselben Sitzung mit dem TOML-Parser — dieselbe Datei, dieselbe
Hand. Reihenfolge für den Architekten danach: Klasse 2 zuerst (entblockt 0002, ändert T5,
T49, T23 Punkt 5, T8), dann 0011, dann Klasse 4.

## Die eine Zahl

**Von den drei verbleibenden Kernkästen ist im nächsten Lauf keiner baubar.** Bis heute
früh lautete das Maß „5 von 9 leer" bei einem Kasten je Lauf; dieser Lauf brachte zwei.
Die Zahl wechselt jetzt, weil nicht mehr die Bauleistung knapp ist, sondern die Freigabe.
