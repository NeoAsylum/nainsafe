# Agentenfabrik

Gedächtnis und Werkstatt eines nebenberuflichen IT-Unternehmens, das von Agenten
betrieben wird. Der Betreiber entscheidet an vier Stellen; dazwischen arbeitet die
Maschine allein.

> **Diese Kopie ist nicht die laufende Fabrik.** Produktiv läuft sie seit dem
> 2026-08-27 in WSL2 unter `~/fabrik`; dort entstehen die Commits. Dieses Verzeichnis
> ist Ausgangspunkt und Sicherung — Änderungen hier wirken sich nicht auf die Fabrik
> aus, bis sie übertragen werden. Wege dorthin: `\\wsl$\Ubuntu\home\<name>\fabrik` im
> Explorer, oder `wsl -d Ubuntu -- bash -lc "cd ~/fabrik && …"`. Übertragen von hier
> nach dort per `git bundle`, weil `/mnt/c` in der Distro abgeklemmt ist.

Die Regeln, an die sich jeder Agent hält, stehen in [CLAUDE.md](CLAUDE.md).
Die Ausschlusskriterien für Ideen stehen in [grenzen.md](grenzen.md).

## Aufbau

| Pfad | Inhalt |
|---|---|
| `signals/` | Rohsignale der Sensorik — je Datei ein Signal, mit Quelle und Datum |
| `ideas/` | Eine Datei je Idee, Status im Frontmatter, Historie im Diff |
| `research/` | Belegte Recherche mit Quellenangabe und Abrufdatum |
| `specs/` | Konzepte einer Idee in `erkundung` — Technik, Rechnung, Pflichten, Vertrieb, Ausfall, Antrag |
| `ventures/` | Aktive Vorhaben mit Code, je ein Unterverzeichnis |
| `ops/` | Betriebsprotokolle, Kosten, Metriken, Digest, Buchhaltung |
| `decisions/` | Entscheidungsprotokolle (ADR) — gegen Amnesie und Ideenschleifen |
| `gates/` | Offene Entscheidungsvorlagen für den Betreiber |
| `vorlagen/` | Vorlagen für Ideen, ADRs und Gate-Vorlagen |
| `schema/state.sql` | Schema der Zustandsdatenbank |
| `quellen.yml` | Quellen der Sensorik — wird vom Betreiber gepflegt, nicht von Agenten |

## Der Fluss

```
Sensorik ─> Ideenfindung ─[Gate 1]─> Portfolio ─> Konzeption ─[Gate 2]─> Bau ─[Gate 3]─> Betrieb ─[Gate 4]
```

| Gate | Frage | Aufwand |
|---|---|---|
| 1 | Lohnt die Ausarbeitung? | ~5 min, sonntags |
| 2 | Genehmigungsfähig, tragfähig, gewollt? | ~30 min |
| 3 | Geht online, nimmt Geld | ~30 min |
| 4 | Skalieren, halten oder einstellen | ~45 min je Quartal |

Nur der Betreiber setzt einen Status über ein Gate hinweg. Kein Agent deployt, versendet,
gibt Geld aus oder löscht.

## Zustandsdatenbank anlegen

```sh
sqlite3 state.db < schema/state.sql
```

`state.db` liegt bewusst außerhalb der Versionierung — sie ist aus dem Schema und den
Frontmattern reproduzierbar und würde sonst bei jedem Lauf Konflikte erzeugen.

## Stand

Stufe 1 der Startsequenz ist angelegt: Verzeichnisse, Hausregeln, Grenzen, Vorlagen,
Schema. Als Nächstes folgt der erste Nachtlauf — ein Scout und ein Ideator, die den
Herzschlag der Fabrik erzeugen.
