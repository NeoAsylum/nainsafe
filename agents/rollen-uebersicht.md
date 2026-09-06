# Rollenuebersicht der Zielorganisation

Aus CLAUDE.md ausgelagert am 2026-09-06. Ein Agent braucht diese Tabelle nicht --
er braucht seine eigene Rollendatei, die spezifischer ist. Hier steht sie fuer den
Betreiber und fuer Rollen, die ueber die Organisation als Ganzes nachdenken.

---

## Dein Arbeitsvertrag als Agent

Du hast **eine** Rolle pro Lauf. Deine Rolle bestimmt, welche Verzeichnisse du lesen und
in welches du schreiben darfst. Schreibe niemals außerhalb deines Zielverzeichnisses,
auch wenn du dort einen Fehler siehst — melde ihn stattdessen in deinem eigenen Output.

Die Tabelle beschreibt die **Zielorganisation**. Gebaut sind die Suchphase (bis
Digest-Redakteur) und seit dem 2026-08-31 die **Konzeptionsphase** — neun Rollen, die
`agents/konzeptlauf.py` nach Gate 1 in sechs Stufen abarbeitet. Die Bau- und
Betriebsrollen ab Builder entstehen, wenn eine Idee Gate 2 passiert hat. Eine Rolle ohne
Datei unter `agents/rollen/` gibt es nicht — der Name in Klammern ist der Dateiname, wo
er abweicht.

| Rolle | liest | schreibt | Grenze |
|---|---|---|---|
| Pain-Scout | `quellen.yml` | `Edit(signals/pain/**)` | bewertet nicht |
| Markt-Scout | `quellen.yml` | `Edit(signals/market/**)` | kopiert keine fremden Inhalte |
| Regel-Scout | `quellen.yml` | `Edit(signals/regulation/**)` | bewertet die Rechtslage nicht |
| Tech-Scout | `quellen.yml` | `Edit(signals/tech/**)` | schlägt keine Ideen vor |
| Modell-Scout | `quellen.yml` | `Edit(signals/modelle/**)` | kopiert nichts Geschütztes, nur das Modell |
| Markt-Analyst | `quellen.yml` | `Edit(signals/maerkte/**)` | schlägt kein Produkt vor, endet bei der Lücke |
| Prozess-Analyst | `quellen.yml`, `signals/maerkte/` | `Edit(signals/prozesse/**)` | zählt eine Branche nur mit, wenn der Vorgang derselbe ist |
| Rechercheur | ein Signal, `research/` | `research/` | erfindet keine Zahlen |
| Ideator | `signals/`, `research/` | `ideas/` (Status `entwurf`) | hebt den Status nie über `entwurf` |
| Fit-Filter | `ideas/`, `grenzen.md` | Status `kandidat`\|`abgelehnt` | hebt keine Grenze auf |
| Advocatus, Linse Nachfrage | `ideas/<id>.md` | `ideas/<id>.angriffe/nachfrage.md` | sieht die anderen Linsen nicht |
| Advocatus, Linse Wettbewerb | `ideas/<id>.md` | `ideas/<id>.angriffe/wettbewerb.md` | sieht die anderen Linsen nicht |
| Advocatus, Linse Betrieb | `ideas/<id>.md` | `ideas/<id>.angriffe/betrieb.md` | sieht die anderen Linsen nicht |
| Advocatus, Linse Recht | `ideas/<id>.md` | `ideas/<id>.angriffe/recht.md` | gibt keinen Rechtsrat, markiert Risiken |
| Advocatus, Linse Vertrieb | `ideas/<id>.md` | `ideas/<id>.angriffe/vertrieb.md` | sieht die anderen Linsen nicht |
| Anwalt der Idee (`anwalt`) | `ideas/<id>.angriffe/*` | `ideas/<id>.angriffe/anwalt.md` | verteidigt mit Weg und Preis, nie mit Absicht |
| Portfolio-Manager | `ideas/`, `ventures/` | `ops/portfolio.md`, `gates/` | stoppt nichts selbst, höchstens eine Vorlage |
| Chronist | `git log`, `gates/` | `decisions/` | ändert keine alten ADRs |
| Digest-Redakteur | `ops/` | `ops/digest/<kw>.md` | nie länger als eine Seite |
| Spielentwerfer | `ideas/<id>.md`, `agentenbau.md`, `specs/<id>/daten.md` | `specs/<id>/spiel.md` | entwirft die kleinste Fassung, an der die vier Maße laufen |
| Datenkurator | `ideas/<id>.md`, `agentenbau.md` | `specs/<id>/daten.md` | keine Quelle ohne Lizenzzitat, gibt keinen Rechtsrat |
| Architekt | `specs/<id>/spiel.md`, `daten.md` | `specs/<id>/technik.md` | wählt keinen exotischen Stack, schreibt keinen Code |
| Ökonom | `specs/<id>/technik.md` | `specs/<id>/rechnung.md` | rundet nie zugunsten der Idee |
| Compliance-Prüfer | `specs/<id>/` | `specs/<id>/pflichten.md` | gibt keinen Rechtsrat, nur Flags |
| Vertriebsplaner | `research/`, `specs/<id>/` | `specs/<id>/vertrieb.md` | plant keine Kaltakquise |
| Urlaubstester | `specs/<id>/` | `specs/<id>/ausfall.md` | nimmt keinen Eingriff an |
| Antrags-Vorbereiter | `specs/<id>/*` | `specs/<id>/antrag.md` | beschönigt den Umfang nicht |
| Konzept-Judge | `specs/<id>/*` | `gates/<id>-g2.md` | glättet keine Widersprüche |
| Builder | `specs/<id>/` | `ventures/<id>/` | weicht nicht ohne ADR ab |
| Bruchtester | `ventures/<id>/` | `ventures/<id>/befunde/` | repariert nichts selbst |
| Sicherheitsprüfer | `ventures/<id>/` | `ventures/<id>/sicherheit.md` | gibt nichts ohne Nachweis frei |
| Release-Vorbereiter | `ventures/<id>/` | `gates/<id>-g3.md` | deployt nicht |
| Wächter | Logs, Metriken | `ops/stoerungen/` | startet keine Dienste neu |
| Support-Triage | Postfach | `ops/support/entwuerfe/` | versendet nicht |
| Metrik-Analyst | Nutzungsdaten | `ops/metriken.md` | exportiert keine Personendaten |
| Beleg-Sammler | Belege, Zahlungen | `ops/buchhaltung/` | ersetzt den Steuerberater nicht |
| Verbesserer | `ops/*`, `notizen/`, `weg.py` | `ops/verbesserung.md` | genau ein Vorschlag pro Woche, ändert nichts selbst |

**Keine Rollen, sondern Skripte:** Was sich deterministisch beantworten lässt, macht kein
Agent. `agents/auslastung.py` erzeugt `ops/auslastung.md` aus dem Journal, `agents/repo.py`
beantwortet Fragen nach Status und Angriffen. Beides kostet null Tokens und gibt immer
dieselbe Antwort. Wenn du als Agent eine Zahl aus dem Journal brauchst, lies die fertige
Datei, statt selbst zu zählen.

