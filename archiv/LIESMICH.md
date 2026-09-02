# Archiv

Was hier liegt, ist **nicht geloescht** — Hausregel 3, und aus einem praktischen Grund:
Die Ablehnungsbegruendungen, Marktprofile und Recherchen sind der Beleg hinter den
Entscheidungen 0004 bis 0011. Wer in drei Monaten wissen will, warum die Schwelle bei
5.000 EUR steht, warum der Suchraum geoeffnet wurde oder warum die Prozessachse
existiert, findet die Zahlen hier und nicht in den ADRs.

Aufgeraeumt am 2026-09-02, als die Fabrik von der Suche in den Bau ueberging.

## `suche/`

| Ordner | Inhalt |
|---|---|
| `signals/` | 81 Rohbeobachtungen: 27 Marktprofile, 8 Prozessprofile, dazu Regulierung, Schmerz, Markt, Modelle, Technik |
| `research/` | 49 Recherchen mit Quelle und Abrufdatum — davon 45 `rot` |
| `ideas/` | 15 verworfene Ideen mit Angriffsordnern, dazu die beiden Eichideen 9001 und 9002 |

Die Eichideen sind der einzige Teil, der noch gebraucht werden koennte: Wer `grenzen.md`
aendert, prueft sie gegen 9001 und 9002 (`einrichtung/eichen.sh`, ADR 0006). Dafuer
muessen sie zurueck nach `ideas/`.

## `agents/archiv/` und `einrichtung/archiv/`

Die Runner und Anzeigeskripte der Suche: `sensorlauf`, `marktlauf`, `prozesslauf`,
`angriffslauf`, `weg`, `entscheiden`, `stand`, dazu `marktprofile.sh`,
`bestenliste.sh`, `warum-leer.sh`. Und unter `agents/rollen/archiv/` die dreizehn
Rollen der Bewertungskette.

## Zurueckholen

Die Suche wieder aufzunehmen heisst: `nachtlauf.py:FOKUS` auf `None`, die Ordner
zurueckschieben, die Rollen aus `agents/rollen/archiv/` zurueck. `quellen.yml` ist
absichtlich **nicht** archiviert — es steht im Hauptverzeichnis und haelt weiterhin
44 Segmente und acht Vorgaenge bereit.
