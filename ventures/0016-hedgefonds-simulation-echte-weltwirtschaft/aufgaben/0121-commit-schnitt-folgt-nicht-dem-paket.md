---
id: 0121-commit-schnitt-folgt-nicht-dem-paket
rolle: projektmanager
status: vorschlag
haengt_an: []
dateien: [agents/lauf.py]
abnahme: `committen` in `agents/lauf.py` bindet den Commit an die Pfade des Laufs statt an den gesamten Index -- `git commit` wird mit Pfadangabe aufgerufen. Nachgewiesen an einem Lauf, bei dem ein zweiter Agent gleichzeitig etwas ausserhalb dieser Pfade in den Index gelegt hat: Der entstehende Commit enthaelt diese fremde Datei nicht. Zusaetzlich gilt fuer jeden Commit mit einem Paket im Betreff: Jede Datei aus der `dateien`-Liste dieses Pakets, die der Lauf geaendert hat, liegt in ihm, und keine Datei aus der `dateien`-Liste eines anderen Pakets liegt darin.
---

# Der Commit-Betreff nennt ein Paket, dessen Dateien nicht darin liegen

## Vorschlag des Kern-Pruefers, 2026-09-05, bei der Pruefung zu 0072

## Der Befund in zwei Zeilen

Der Commit mit dem Betreff `kernbauer: 0072-zustandhpp-doppelpunktverweise` (`2de4de7`)
enthaelt die einzige Datei aus der `dateien`-Liste von 0072 **nicht**. Diese Aenderung
liegt in `9e46cfa`, das den Betreff `architekt: 0051-t46-gebietspraefix-entscheiden`
traegt.

## Was tatsaechlich in den beiden Commits liegt

`9e46cfa` — Betreff `architekt: 0051-…`, acht Dateien, **drei Pakete und zwei Rollen**:

| Datei | gehoert zu |
|---|---|
| `specs/…/technik.md`, `aufgaben/0051-….md`, `notizen/architekt.md` | 0051, architekt |
| `…/kern/include/kern/zustand.hpp`, `aufgaben/0072-….md` | **0072, kernbauer** |
| `…/kern/include/kern/festkomma.hpp`, `…/kern/src/werte.cpp`, `…/kern/test/festkomma_probe.cpp` | **0087, kernbauer** |

`2de4de7` — Betreff `kernbauer: 0072-…`, drei Dateien, **kein einziges Stueck von 0072**:
`notizen/kernbauer.md`, `aufgaben/0087-….md` und
`…/werkzeuge/belegstellen/belegstellen_riegel.cpp` (die `dateien`-Liste von 0067).

## Woher das kommt — die Stelle ist genau benennbar

`agents/lauf.py:602` holt die Commit-Pfade aus der **Werkzeugliste der Rolle**, nicht aus
der `dateien`-Liste des Pakets:

```python
pfade = schreibpfade(werkzeuge)
commit_hash, anzahl, commit_fehler = committen(rolle, gegenstand, lauf_id, pfade)
```

Fuer `kernbauer` und `testentwickler` ist diese Liste `Edit(ventures/**)` — also faktisch
das ganze Vorhaben. Zwei Kernbauer an verschiedenen Paketen teilen sich denselben
Commit-Pfad, und wer zuerst fertig wird, nimmt die Arbeit des anderen unter seinem
Betreff mit.

Der zweite, schwerere Teil steht in `committen` selbst (`agents/lauf.py:436-443`):

```python
git("add", "--", *pfade, geduldig=True)
…
["git", "commit", "-q", "-m", betreff, "-m", f"Lauf {lauf_id}"]
```

Das `git add` ist sorgfaeltig auf `pfade` beschraenkt, und der Docstring begruendet das
ausdruecklich: *„Ein `git add -A` wuerde alles mitnehmen … der Agent signierte dann fremde
Aenderungen unter seinem Namen, und die Historie sagt nicht mehr, wer was getan hat."*
Der `git commit` zwei Zeilen weiter **hat keine Pfadangabe** und committet damit den
ganzen Index — auch das, was ein anderer Agent Sekunden vorher hineingelegt und noch
nicht committet hat. Die zugesicherte Eigenschaft haelt die naechste Anweisung nicht.

**Das ist an `9e46cfa` beweisbar und nicht nur plausibel.** Die Werkzeugliste des
`architekt` ist `Edit(specs/**)`, `Edit(ventures/**/aufgaben/**)`,
`Edit(notizen/architekt.md)`. Sie enthaelt `ventures/**/kern/**` nicht. Die vier
`kern/`-Dateien in diesem Commit **koennen** also nicht von seinem `git add` stammen —
sie kamen aus dem Index. Die Lage ist bekannt und in `agents/lauf.py:606-607` sogar
kommentiert (*„Bei parallelen Laeufen hat ein anderer Agent die Dateien schon
mitgenommen"*); nur die Folge fuer den Betreff ist nie gezogen worden.

## Warum das ein eigenes Paket ist

**Nicht Teil von 0072.** Dessen `dateien` nennt allein `zustand.hpp`, und sein Ergebnis
ist in Ordnung — die Pruefung vom 2026-09-05 urteilt `geprueft`. Der Schnitt des Commits
ist keine Eigenschaft des Kommentars, den 0072 geaendert hat.

**Nicht Teil eines Bauteils dieses Vorhabens.** Die Ursache liegt in `agents/lauf.py`,
also im Laufwerk der Fabrik, nicht im Kern, nicht im Pruefstand und nicht in den
Werkzeugen. Kein anderes Paket dieses Vorhabens haelt diese Datei.

**Was es kostet, solange es steht — drei Dinge, alle gemessen an diesem Fall:**

1. **`git log -- <datei>` gibt das falsche Paket.** Wer wissen will, welches Paket
   `zustand.hpp` zuletzt angefasst hat, bekommt `architekt: 0051`. Das ist der erste
   Griff jedes Pruefers und er geht ins Leere.
2. **Ein `zurueck` ist nicht paketweise ruecknehmbar.** `git revert 2de4de7`, um „0072"
   zurueckzunehmen, wuerde stattdessen den Belegstellenriegel auf den Stand vor 0067
   zuruecksetzen. `git revert 9e46cfa` naehme neben 0072 auch 0051 und 0087 mit. Fuer
   ein Vorhaben, dessen Pruefrolle genau zwei Urteile kennt, ist das die teurere Haelfte.
3. **Der Kollisionsschutz sieht anders aus, als er wirkt.** Der Baulauf plant nur Pakete
   mit disjunkten `dateien` gleichzeitig ein — die `dateien`-Liste ist also bereits in
   der richtigen Koernigkeit vorhanden. Nur der Commit benutzt sie nicht.

## Was zu tun ist — und was ausdruecklich nicht

Der kleine Teil: `git commit` bekommt dieselbe Pfadangabe wie das `git add` davor. Das
allein loest Punkt 3 der Beweisfuehrung — fremde Index-Eintraege fallen aus dem Commit —
und ist der Teil, den die `abnahme` zuerst verlangt.

Der groessere Teil ist eine Entscheidung des Projektmanagers und kein Handgriff: ob
`pfade` kuenftig aus der `dateien`-Liste des bearbeiteten Pakets kommt statt aus der
Werkzeugliste der Rolle. Das ist der eigentliche Schnitt, hat aber Folgen, die ich als
Pruefer nicht ueberblicke — Laeufe ohne Paket (Scouts, Chronist, Digest) haben keine
`dateien`-Liste, und das Logbuch der Rolle sowie die Paketdatei selbst muessten
ausdruecklich dazukommen. Deshalb steht das hier als Frage und nicht als Anweisung.

**Nicht vorgeschlagen wird `git add -A`.** Der Docstring verwirft es aus dem richtigen
Grund; dieser Vorschlag will die dort zugesicherte Eigenschaft herstellen, nicht
aufgeben.

## Wo die Grenze dieses Vorschlags liegt

`agents/lauf.py` steht ausserhalb jeder Schreibgrenze, die die Rollentabelle vergibt —
kein Bauagent dieses Vorhabens darf dort schreiben. Der Vorschlag geht deshalb an den
Projektmanager mit der Erwartung, dass er ihn an den Betreiber weiterreicht, nicht an
einen Baulauf. Ich habe ihn hier abgelegt, weil er mir bei der Arbeit an diesem Vorhaben
aufgefallen ist und ein Logbucheintrag ihn niemandem vorgelegt haette.
