# Die Agenten

Eine Rolle ist eine Datei unter [rollen/](rollen/). Ihr Frontmatter legt Modell,
Zeitgrenze und **Werkzeuge** fest, ihr Rumpf ist der Auftrag. Neue Rollen brauchen keinen
Code — nur eine neue Markdown-Datei.

## Warum die Werkzeugliste wichtiger ist als der Prompt

Die Schreibrechte aus [../CLAUDE.md](../CLAUDE.md) stehen nicht nur im Auftragstext,
sondern in `tools:`. Der Regel-Scout bekommt `Edit(signals/regulation/**)` — und damit
schlicht kein Werkzeug, mit dem er eine Idee anlegen könnte. Ein Prompt ist eine Bitte;
eine fehlende Berechtigung ist ein Riegel.

> **`Edit(...)`, niemals `Write(...)`.** Claude Code prüft Dateirechte allein gegen
> `Edit()`- und `Read()`-Regeln. Eine `Write()`-Pfadregel wird angenommen und nie
> ausgewertet — sie sieht wie eine Berechtigung aus und ist keine. Im Modus `dontAsk`
> führt das dazu, dass die Rolle recherchiert, Tokens verbraucht und am Ende nichts
> speichern kann. `Edit()` deckt alle eingebauten Werkzeuge ab, die Dateien ändern,
> das Anlegen neuer Dateien eingeschlossen. Dasselbe gilt für `Read()` statt `Glob()`.

Zusätzlich verbietet [lauf.py](lauf.py) global, was kein Agent je darf: `git push`,
`gh`, `curl`, `wget`, `rm`, `pip install`. Das sind die harten Regeln 1 und 2 aus
CLAUDE.md, in Code gegossen.

## Bedienung

```sh
python agents/lauf.py regel-scout             # ein einzelner Lauf
python agents/lauf.py advocatus-betrieb 0042  # eine Rolle auf einen Gegenstand
python agents/nachtlauf.py --trocken          # zeigt die Kette, ohne Tokens zu verbrauchen
python agents/nachtlauf.py                    # der Herzschlag
python agents/wochenlauf.py                   # der Vorstand, sonntags früh
python agents/auslastung.py                   # nur die Zahlen, kostet nichts
```

Jeder Lauf schreibt eine Zeile ins Journal (`state.db`) und committet, was er
hinterlassen hat. Findet ein Agent nichts, gibt es keinen Commit und das Ergebnis
lautet `leer` — das ist ein gültiges und häufiges Ergebnis, kein Fehler.

**Vor dem ersten Scheduler-Eintrag** einmal `python agents/nachtlauf.py` von Hand
laufen lassen und ansehen, was dabei herauskommt. Der erste Lauf zeigt, ob die
Auftragstexte taugen — und er verbraucht Tokens.

## Die zwei Takte

**Nachts** — die Fabrik:

```
regel-scout ──> ideator ──> fit-filter ──> advocatus ×3 je Kandidat
 (sonnet)       (opus)      (opus)         (opus, drei Linsen)
 sammelt        verdichtet  lehnt ab       greift an
```

Die ersten drei laufen immer, auch wenn der vorherige nichts fand — es kann
unverarbeitetes Material aus früheren Nächten liegen. Die Angriffe werden erst *danach*
bestimmt, weil der Fit-Filter im selben Lauf neue Kandidaten erzeugt haben kann.
Gedeckelt auf zwei Ideen pro Nacht: drei Linsen mal viele Kandidaten wären sonst schnell
ein zweistelliger Lauf, dessen Ergebnis ohnehin niemand liest.

**Sonntags früh** — der Vorstand:

```
auslastung.py ──> portfolio-manager ──> digest-redakteur
 (Skript)          (opus)             (opus)
 0 Tokens          wertet aus, tötet  eine Seite
```

Ist das WIP-Limit erreicht, schrumpft die Nachtkette auf den Scout — neue Kandidaten
wären dann Ballast, weil ohnehin nichts hochgestuft werden kann.

## Die drei Linsen

Statt drei identischer Skeptiker greifen drei verschiedene an. Redundanz findet
dieselben Fehler dreimal; Verschiedenheit findet drei verschiedene:

| Linse | Fragt | Tötet meist an |
|---|---|---|
| `nachfrage` | Existiert der Schmerz, und zahlt jemand dafür? | Ärger ohne Zahlungsbereitschaft |
| `wettbewerb` | Warum macht das nicht längst jemand? | etabliertem Anbieter, zu engem Zeitfenster |
| `betrieb` | Was passiert bei 100 Kunden und im Urlaub? | Aufwand, der mit der Kundenzahl wächst |

Jede Linse fällt ein Urteil (`widerlegt` / `haelt` / `unklar`) und benennt den schwersten
Einwand. **Zwei von drei `widerlegt` töten die Idee** — der Portfolio-Manager überstimmt
diese Mehrheit nicht. Alle drei schreiben im Zweifel `widerlegt`: Eine zu Unrecht
verworfene Idee kostet fast nichts, eine zu Unrecht durchgewinkte kostet Wochen.

## Zeitplanung

Die Fabrik läuft in WSL2 — siehe [../EINRICHTUNG.md](../EINRICHTUNG.md). Dort gilt cron:

```cron
0 3 * * * cd ~/fabrik && /usr/bin/python3 agents/nachtlauf.py >> ops/nachtlauf.log 2>&1
```

Auf einem späteren VPS ist es dieselbe Zeile mit anderem Pfad — das ist der Grund für
WSL2 statt nativem Windows.

Cron startet Prozesse in einer kargen Umgebung. Wenn ein Lauf mit „claude nicht im PATH"
abbricht, den vollen Pfad eintragen (`which claude`).

## Journal lesen

```sh
# Die letzten Läufe
sqlite3 state.db "SELECT gestartet, rolle, ergebnis, tokens_in+tokens_out AS tok
                  FROM lauf ORDER BY id DESC LIMIT 15;"

# Tokenverbrauch je Rolle, letzte sieben Tage
sqlite3 state.db "SELECT rolle, count(*) AS laeufe, sum(tokens_in+tokens_out) AS tok
                  FROM lauf WHERE gestartet > date('now','-7 days')
                  GROUP BY rolle ORDER BY tok DESC;"

# Läuft eine Rolle regelmäßig leer? Dann taugt ihr Auftrag oder ihre Quelle nicht.
sqlite3 state.db "SELECT rolle, ergebnis, count(*) FROM lauf GROUP BY rolle, ergebnis;"
```

## Eine neue Rolle anlegen

1. `rollen/<name>.md` anlegen, Frontmatter mit `modell`, `timeout`, `tools`.
2. `tools` so eng wie möglich fassen — ein Zielverzeichnis, nicht `Write`.
3. Den Auftrag so schreiben, dass ein leeres Ergebnis ausdrücklich erlaubt ist.
4. Die Rolle in [../CLAUDE.md](../CLAUDE.md) in die Rollentabelle eintragen.
5. Einmal einzeln laufen lassen, bevor sie in eine Kette kommt.

## Was noch fehlt

Die Konzeptionsebene: Architekt, Ökonom, Compliance-Prüfer, Vertriebsplaner,
Urlaubstester, Antrags-Vorbereiter und Konzept-Judge. Sie lohnen erst, wenn eine Idee
Gate 1 passiert hat — vorher gäbe es nichts zu konzipieren.
