# Die Agenten

Eine Rolle ist eine Datei unter [rollen/](rollen/). Ihr Frontmatter legt Modell,
Zeitgrenze und **Werkzeuge** fest, ihr Rumpf ist der Auftrag. Neue Rollen brauchen keinen
Code — nur eine neue Markdown-Datei.

## Warum die Werkzeugliste wichtiger ist als der Prompt

Die Schreibrechte aus [../CLAUDE.md](../CLAUDE.md) stehen nicht nur im Auftragstext,
sondern in `tools:`. Der Regel-Scout bekommt `Write(signals/regulation/**)` — und damit
schlicht kein Werkzeug, mit dem er eine Idee anlegen könnte. Ein Prompt ist eine Bitte;
eine fehlende Berechtigung ist ein Riegel.

Zusätzlich verbietet [lauf.py](lauf.py) global, was kein Agent je darf: `git push`,
`gh`, `curl`, `wget`, `rm`, `pip install`. Das sind die harten Regeln 1 und 2 aus
CLAUDE.md, in Code gegossen.

## Bedienung

```sh
python agents/lauf.py regel-scout          # ein einzelner Lauf
python agents/lauf.py ideator              # eine Rolle gezielt
python agents/nachtlauf.py --trocken       # zeigt die Kette, ohne Tokens zu verbrauchen
python agents/nachtlauf.py                 # der echte Herzschlag
```

Jeder Lauf schreibt eine Zeile ins Journal (`state.db`) und committet, was er
hinterlassen hat. Findet ein Agent nichts, gibt es keinen Commit und das Ergebnis
lautet `leer` — das ist ein gültiges und häufiges Ergebnis, kein Fehler.

**Vor dem ersten Scheduler-Eintrag** einmal `python agents/nachtlauf.py` von Hand
laufen lassen und ansehen, was dabei herauskommt. Der erste Lauf zeigt, ob die
Auftragstexte taugen — und er verbraucht Tokens.

## Die Kette

```
regel-scout  ──>  ideator  ──>  fit-filter
 (sonnet)         (opus)         (opus)
 sammelt          verdichtet     lehnt ab oder bewertet
```

Jeder Schritt läuft auch, wenn der vorherige nichts fand: Es kann unverarbeitetes
Material aus früheren Nächten liegen. Ist das WIP-Limit erreicht, schrumpft die Kette
auf den Scout — neue Kandidaten wären dann nur Ballast.

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

Portfolio-Manager, Digest-Redakteur und Kostenwächter — die Wochenebene. Erst wenn der
Nachtlauf ein paar Tage stabil läuft und tatsächlich Kandidaten erzeugt, lohnt sich der
Vorstand. Vorher gäbe es nichts zu verwalten.
