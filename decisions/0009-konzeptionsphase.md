---
nr: 0009
titel: Die Konzeptionsphase — neun Rollen in sechs Stufen, die Sperrfrage zuerst
datum: 2026-08-31
status: gueltig
ersetzt: null
ersetzt_durch: null
betrifft: [organisation, konzeption]
---

# ADR 0009 — Die Konzeptionsphase

## Kontext

Der Betreiber hat entschieden, die Hedgefonds-Weltwirtschaftssimulation zu verfolgen
(Idee `0016`). Damit erreicht die Fabrik zum ersten Mal die Phase hinter Gate 1.

Bis dahin existierte sie nur als Tabellenzeilen in `CLAUDE.md`: `specs/` und `gates/`
waren leer, achtzehn Rollen der Ziel­organisation hatten keine Datei. Die Tabelle war
außerdem für ein **Software­produkt für Unternehmen** entworfen — für ein Spiel fehlen
zwei Rollen, und zwei weitere haben eine andere Aufgabe als gedacht.

## Entscheidung

**Neun Rollen, sechs Stufen, eine Abhängigkeitskette.** Gefahren von
`agents/konzeptlauf.py`, nicht vom Nachtlauf: Die Phase läuft auf Zuruf nach Gate 1, nicht
täglich.

| Stufe | Rolle(n) | Ergebnis |
|---|---|---|
| 1 Daten | **Datenkurator** (neu) | `daten.md` |
| 2 Entwurf | **Spielentwerfer** (neu) | `spiel.md` |
| 3 Technik | Architekt | `technik.md` |
| 4 Prüfung | Ökonom, Vertriebsplaner, Compliance-Prüfer, Urlaubstester (parallel) | `rechnung.md`, `vertrieb.md`, `pflichten.md`, `ausfall.md` |
| 5 Antrag | Antrags-Vorbereiter | `antrag.md` |
| 6 Gate 2 | Konzept-Judge | `gates/<id>-g2.md` |

**Zwei Rollen sind neu**, weil ein Spiel etwas braucht, das ein Geschäftswerkzeug nicht
braucht:

- **Der Spielentwerfer** legt fest, *was gespielt wird* — Schleife, Aktionen,
  Siegbedingung, und die Gegenkräfte gegen die Rückkopplung, die dieses Genre tötet. Das
  ist nicht die Aufgabe des Architekten, der festlegt, *wie* gebaut wird.
- **Der Datenkurator** klärt, ob es Wirtschaftsdaten gibt, die in ein verkauftes Produkt
  eingebettet werden dürfen.

## Warum die Reihenfolge so ist

**Stufe 1 läuft allein und zuerst, und das ist der wichtigste Teil dieser
Entscheidung.** Die Lizenzfrage ist binär und billig: Erlaubt keine Quelle die
gewerbliche Weiterverbreitung, fällt die vierte Prüfachse aus `agentenbau.md` weg — und
damit der ganze Grund, die echte Welt statt einer erfundenen zu nehmen. Dann ist jede
weitere Konzeptionsarbeit verschwendet.

`konzeptlauf.py` hält deshalb nach Stufe 1 an, wenn `daten.md` die Sperrfrage mit
`negativ` beantwortet, und legt die Entscheidung dem Betreiber vor: erfundene Welt,
Daten beim Start laden, oder einstellen. Kosten des Abbruchs: rund fünf Dollar statt
fünfzig.

Die übrigen Stufen folgen ihren Abhängigkeiten: Der Spielentwerfer kann nichts
verwenden, was es nicht gibt. Der Architekt braucht den Entwurf. Ökonom,
Vertriebsplaner, Compliance-Prüfer und Urlaubstester brauchen Entwurf und Technik, aber
nicht einander — sie laufen parallel. Der Antrag braucht die Stundenzahl aus
`ausfall.md`. Der Judge braucht alles.

## Was der Judge tun soll, und was nicht

Vier Rollen rechnen in Stufe 4 unabhängig voneinander, und **sie werden sich
widersprechen**. Der Ökonom rechnet mit einer Verkaufszahl — trägt der Vertriebsplaner
sie? Der Spielentwerfer verlangt Größen — hat der Datenkurator sie belegt? Der Architekt
nennt Rechenkosten — stehen sie in der Rechnung?

Diese Widersprüche sind der eigentliche Ertrag der Phase. Der Judge glättet keinen
einzigen; er legt sie auf eine Seite und empfiehlt. Entschieden wird an Gate 2, und Gate
2 ist ein Mensch.

## Was noch nicht gebaut ist, und warum nicht

Die Bau- und Betriebsrollen — Builder, Bruchtester, Sicherheitsprüfer,
Release-Vorbereiter, Wächter, Support-Triage, Metrik-Analyst, Beleg-Sammler — entstehen
erst nach Gate 2. Der Grund ist die Erfahrung dieser Fabrik mit Rollen, die nie laufen:
Der Portfolio-Manager hat zwei Sensoren als ertraglos nachgewiesen, und der Verbesserer
hat drei Dateien gefunden, die einen Rechercheschritt versprachen, den das Statusmodell
gar nicht enthielt.

Eine Rolle, die nichts tut, ist kein Platzhalter, sondern eine falsche Zusage.

**Ausdrücklich noch nicht gebaut, obwohl sie für dieses Produkt zentral sind:** die
Rollen für den **Selbstspiel-Prüfstand** — Balance-Prüfer und Rückvergleich gegen echte
Zeitreihen. Sie gehören in die Bauphase, weil man einen Entwurf nicht selbst spielen
kann. Der Spielentwerfer muss aber schon jetzt hinschreiben, *wie* die vier Maße aus
`agentenbau.md` in diesem konkreten Spiel berechnet würden; ohne diese Angabe ist sein
Entwurf unvollständig.
