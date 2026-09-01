# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-01, geschrieben vom Projektmanager. Erster Lauf dieser Rolle im Bau.
Diese Datei sagt, **welche Pakete es gibt, warum in dieser Reihenfolge, und was der
Geschäftsführer entscheiden lassen muss**. Die Pakete selbst stehen in `aufgaben/`.

## Was für jedes Paket gilt — es gibt keinen Übersetzer

**Kein Agent dieser Fabrik hat eine Shell.** `agents/lauf.py` gibt jeder Rolle genau die
Werkzeuge aus ihrem Frontmatter; Kernbauer, Datenbauer und sämtliche Prüfer haben
`Read`, `Glob`, `Grep`, `WebSearch`, `WebFetch` und `Edit(ventures/**)` — und `NIE` in
`lauf.py` sperrt Bash zusätzlich als zweite Linie. Nachgesehen am 2026-09-01 in allen
31 Rollendateien: **`Bash` kommt in keiner einzigen Werkzeugliste vor.**

Daraus folgen drei Dinge, und sie gelten für jedes Paket dieses Vorhabens:

1. **Niemand kann `cargo build` oder `cargo test` ausführen.** Ein Abnahmekriterium
   „übersetzt fehlerfrei" oder „Tests laufen grün" wäre von keinem Prüfer nachprüfbar
   und damit kein Kriterium, sondern eine Behauptung. Solche Kriterien stehen deshalb in
   keinem Paket.
2. **Jedes Abnahmekriterium ist mit `Read`, `Grep` und Kopfrechnen prüfbar.** Das ist
   enger als üblich und trifft sich gut mit `technik.md`: T4 (`grep -rn 'f32\|f64' kern/`
   ist leer), T48 (`grep -n 'pub fn' kern/src/werte.rs` gegen die Tabelle der siebzehn),
   T50 (`grep -rn 'tsd_in_cent' kern/` hat genau drei Treffer) und T13 (die
   Kastenrichtung steht in den `[dependencies]` der `Cargo.toml`) sind vom Architekten
   bereits als mechanische Nachweise gebaut. Sie funktionieren ohne Übersetzer.
3. **Der Bauagent schreibt Code, den nie jemand übersetzt hat, bevor der Betreiber es
   tut.** Das gehört in jedes Paket als Auflage: keine Abkürzung, die nur der Übersetzer
   finden würde — jede Signatur ausgeschrieben, jeder Aufruf gegen die Signatur gelesen,
   die er trifft.

**Was der Betreiber entscheiden muss:** Ob ein Übersetzungslauf in den Nachtlauf gehört.
Er kostet null Tokens und wäre ein Skript neben `auslastung.py` — `cargo test` im
Venture-Verzeichnis, Ausgabe nach `ventures/<venture>/befunde/uebersetzung-<datum>.md`.
Ohne ihn ist der erste Übersetzungsfehler des Vorhabens erst dann sichtbar, wenn ein
Mensch ihn sucht, und bis dahin bauen Agenten auf ungeprüftem Code weiter. Ich melde das
und entscheide es nicht: Es ändert `agents/`, und dort schreibe ich nicht.

## Die Reihenfolge und warum sie so ist

Der Kastenschnitt aus T13 ist zugleich der Kollisionsschnitt (Abschnitt 13 von
`technik.md` sagt es ausdrücklich). Daraus:

```
0004 Gerüst+Festkomma ─┬─> 0008 Zustand ──> 0002 Werte ──> (Schreiber, Weltschritt …)
                       │        ^
0007 Adressverzeichnis ─────────┘
0005 WDI-Lizenz         (frei)
0006 Deckung 1997       (frei)   ──> setzt R, kann das Vorhaben kippen
0009 parameter.toml     (frei)
```

**Vier Pakete sind sofort startbereit** — 0004, 0005, 0006, 0007 —, ein fünftes (0009)
wartet nur auf einen freien Platz. `baulauf.py:GLEICHZEITIG` ist 4; damit läuft kein
Bauagent leer, und keine zwei Pakete treffen sich in einer Datei.

**Warum zwei Datenpakete vor jedem Kernpaket stehen**, obwohl der Kern der Engpass ist:
`technik.md` Abschnitt 13 nennt genau diese zwei als vorzuziehen, „weil sie
Entwurfsrisiko tragen und nicht Bauaufwand". 0006 kann das Vorhaben kippen (T24: 25
Stützstellen ohne Füllung sind eine Behauptung), 0005 halbiert im schlechten Fall den
Beleg des Rückvergleichs (T26, `spiel.md` *Offene Entwurfsfragen*, „zu prüfen, bevor
gebaut wird"). Beide klären sich gegen Daten, kosten je einen Lauf und blockieren
niemanden.

## Was ich nachgezogen habe

- **0001-entwurf-abnahme** stand schon auf `fertig`, vom Betreiber gesetzt. Unverändert.
- **0002-fondsbewertung-definieren** war überholt, bevor ein Agent es angefasst hat. Es
  sagt „Der Entwurf gibt es nicht her; entscheide es" — seit `spiel.md` Fassung 5 und
  `technik.md` T47/T48 gibt der Entwurf es her, vollständig und mit Zahlenprobe. Ein
  Kernbauer, der dem alten Wortlaut folgte, würde von `specs/` abweichen, was seine
  eigene Rolle verbietet. Inhalt ersetzt, Kennung und alter Wortlaut bleiben in der
  Datei.
- **0003-einheit-beteiligung** steht auf `blockiert`. Sein Abnahmekriterium verlangt
  Wrappertypen je Größenklasse („Jede Geldgröße trägt ihre Einheit im Typ"); T5 sagt
  „Der Typ ist überall `i64`, die Bedeutung steht in dieser Tabelle und nirgends
  sonst". Das Paket und die Vorgabe können nicht beide gelten. Der Zweck des Pakets —
  diese Fehlerklasse für immer schließen — ist in der Zwischenzeit anders erfüllt
  worden: T49 ordnet jeder der 310 Adressen genau eine Skalenklasse zu, T50 gibt den
  drei Skalenübergängen je einen Namen und genau einen Aufrufort, beides mit
  mechanischem Nachweis. Die Arbeit daran ist 0007 und 0002. **Meldung an den
  Geschäftsführer, nicht an einen Bauagenten**: Wenn der Betreiber die Wrappertypen
  trotzdem will, ist das ein ADR gegen T5 und nicht ein Arbeitspaket.

## Was blockiert bleibt und wem es gehört

- **„Schaden" in Gegenkraft 5 hat keine Rechenvorschrift.** `technik.md` Abschnitt 12,
  Beobachtung 3, meldet es selbst: `spiel.md` sagt, das Gegenbudget wachse „proportional
  zum erlittenen Schaden"; welche Zahl das ist, steht nirgends. T50 legt nur die Einheit
  fest. Das ist derselbe Fehlertyp wie Befund 1 der Runde 6 — wählt der Bauagent, misst
  Maß 2 seine Wahl. **Ich lege dafür kein Paket an**, weil es keines gibt: Es gehört dem
  Spielentwerfer, und der läuft im Baulauf nicht mehr. Solange es offen ist, ist
  Gegenkraft 5 nicht baubar. Das trifft den Kern erst in einigen Wochen; bis dahin
  braucht es eine Entscheidung des Betreibers, ob der Spielentwerfer für diese eine
  Frage noch einmal läuft.
- **Der Planwert von 10 µs je Weltschritt** ist ungemessen und bleibt es, bis es einen
  Kern *und* einen Übersetzungslauf gibt. `technik.md` nennt ihn selbst die einzige
  Zahl, die eine Prüfung im Bau umwerfen kann.

## Rücklaufgrenze im Bau

`ops/plan.md` vom 2026-09-01 stellt dem Betreiber die Frage und empfiehlt B: nach dem
**zweiten** `zurueck` steht ein Paket auf `blockiert`. Ich führe den Zähler ab sofort in
jedem Paket unter *Rückläufe* mit, damit die Entscheidung, wann immer sie fällt, eine
Zahl vorfindet und nicht eine Rekonstruktion aus Befunddateien. Das ist billig und
nimmt nichts vorweg — die Grenze selbst setze ich nicht, solange sie nicht entschieden
ist.
