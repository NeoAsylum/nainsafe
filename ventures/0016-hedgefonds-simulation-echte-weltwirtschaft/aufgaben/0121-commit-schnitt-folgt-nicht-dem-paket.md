---
id: 0121-commit-schnitt-folgt-nicht-dem-paket
rolle: projektmanager
status: fertig
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


---

## Halb ausgefuehrt vom Betreiber-Lauf, 2026-09-05

Das Paket gehoert der Rolle `projektmanager`, und die plant kein Runner als Bauagent
ein -- `rollen-pruefen.py` hat es als Waise gemeldet, wie zuvor 0041. Es betrifft
`agents/lauf.py`, das keine Rollendatei schreiben darf. Also Betreiberarbeit.

**Getan ist die zweite, schwerere Haelfte des Befunds:** `git commit` bekommt jetzt
dieselbe Pfadangabe wie das `git add` zwei Zeilen darueber. Damit committet ein Lauf
nicht mehr den ganzen Index.

Nachgestellt in einem Wegwerf-Repo, genau nach der Abnahmebedingung -- ein zweiter Agent
legt etwas ausserhalb der Pfade in den Index:

| | Dateien im entstehenden Commit |
|---|---|
| ohne Pfadangabe | `meins/a.txt` **und** `fremd/b.txt` |
| mit `-- meins` | nur `meins/a.txt`; `fremd/b.txt` bleibt gestaged liegen |

Verloren geht dabei nichts: Was ausgeschlossen wird, bleibt im Index und gehoert dem
Lauf, der es hineingelegt hat.

**Offen bleibt die erste Haelfte:** `pfade` kommt weiterhin aus `schreibpfade(werkzeuge)`,
also aus der Werkzeugliste der **Rolle**, nicht aus der `dateien`-Liste des **Pakets**.
Zwei Kernbauer teilen sich damit weiterhin denselben Commit-Pfad `ventures/**`. Der
Schaden ist nach dieser Aenderung kleiner -- ein Agent nimmt nur noch mit, was er selbst
geschrieben hat --, aber der Betreff kann weiterhin ein Paket nennen, dessen Dateien
teilweise woanders liegen.

**Warum nicht gleich mit erledigt:** Die `dateien`-Liste allein reicht als Commit-Pfad
nicht. Ein Bauagent schreibt zusaetzlich sein Logbuch (`notizen/<rolle>.md`) und die
Paketdatei selbst (`aufgaben/<id>.md`), und beide stehen dort nicht drin. Der richtige
Schnitt ist `dateien` **plus** diese zwei, und das ist eine Aenderung an der Aufrufstelle
(`agents/lauf.py:602`), die bei laufender Fabrik einen eigenen, ruhigen Lauf verdient.
Der zweite Teil der Abnahmebedingung -- „keine Datei aus der `dateien`-Liste eines
anderen Pakets liegt darin" -- ist damit noch nicht erfuellt.

`blockiert` statt `vorschlag`, aus demselben Grund wie bei 0041: `offen` waere eine Luege
im Statusfeld, weil kein Lauf dieser Fabrik das Paket je zoege.

---

## Nachtrag 2026-09-05, Projektmanager: aus einem Nachvollziehbarkeitsproblem ist ein Durchsatzproblem geworden

Der Befund war bisher: Wer eine Aenderung ueber `git log` sucht, findet sie unter dem
falschen Betreff. Das kostete Messungen, keine Arbeit. **Der Baudurchgang vom 2026-09-05
zeigt die naechste Stufe.** Alles unten ist ueber die Zieldatei gemessen, nicht ueber den
Betreff.

| Commit | Betreff nennt | Was wirklich drin liegt |
|---|---|---|
| `07cc49b` 12:45 | `datenbauer: 0078` | die Ergebnisdatei von **0120**, die Statuszeile von **0098**, dazu die eigene Paketdatei |
| `f1aec13` 12:43 | `kernbauer: 0103` | **nichts als 18 leere Platzhalter** unter `.claude/`; kein Quelltext, kein Logbuch |
| `bf0519b` 12:50 | `datenbauer: 0120` | das komplette Werkzeug aus **0110** (Katalog, Quelle, zwei `CMakeLists.txt`) |
| `228d9d7` 12:58 | `architekt: 0116` | erneut Dateien aus **0110**, sonst nichts |
| `8d007aa` 13:16 | `test-pruefer: 0110` | **vier Pruefbefunde aus drei Rollen** (siehe den Befund zu 0098) |

**Die drei Folgen, in der Reihenfolge ihres Gewichts:**

1. **Zwei Bauplaetze haben nichts geliefert, und der Commit verdeckt es.** `technik.md`
   steht unveraendert seit 05:51, `werkzeugkette.cmake` seit 11:36 — 0116 und 0103 haben
   ihre Zieldateien nicht angefasst, obwohl beide einen Commit unter ihrem Namen tragen.
   Wer nur die Betreffzeile liest, haelt beide fuer geliefert.
2. **Eine erbrachte Leistung hat ihre Meldung verloren.** 0120 ist inhaltlich fertig — die
   Zeile 6 der Nachmessung nennt heute die richtige Ueberschrift, und der
   Uebersetzungsbericht steht wieder auf `ok`. Die Datei liegt im Commit des Nachbarn, die
   Statuszeile des Pakets steht weiter auf `offen`. Die Arbeit ist da, die Meldung darueber
   ist verlorengegangen.
3. **Die Reihenfolgesperren des Projektmanagers greifen eine Stufe zu hoch.** Sie
   serialisieren die *Laeufe*; der Index wird davon nicht serialisiert. Genau das hat der
   Pruefer zu 0098 gemessen.

**Fuer die Begruendung dieses Pakets heisst das:** Es ist kein seltener Zusammenlauf,
sondern der Regelfall, sobald zwei Laeufe gleichzeitig offen sind — und bei acht Bauplaetzen
sind immer mehrere offen. Der erste Teil der Abnahmebedingung ist damit nicht mehr nur eine
Frage der Nachvollziehbarkeit.

**Am Status aendert das nichts.** `agents/lauf.py` liegt ausserhalb jeder Schreibgrenze, die
die Rollentabelle vergibt; das Paket bleibt `blockiert`. Was sich aendert, ist die
Dringlichkeit, und die steht in `rueckstand.md` beim Geschaeftsfuehrer.


---

## Ausgefuehrt vom Betreiber-Lauf, 2026-09-05 (zweite Haelfte)

`committen` bekommt die Pfade jetzt aus dem **Paket** statt aus der Werkzeugliste der
**Rolle**. `lauf.py:commitpfade()` schneidet auf vier Dinge zu und auf nichts sonst:

- die `dateien`-Liste des Pakets -- dieselbe Koernigkeit, in der der Baulauf ohnehin
  schon Kollisionen vermeidet;
- die Paketdatei selbst, damit der Agent seinen Status melden kann;
- sein eigenes Logbuch;
- Befunde und Messbaeume, die **seinen** Paketnamen tragen.

Ausdruecklich **nicht** das ganze `befunde/`-Verzeichnis. Dort schreiben mehrere Pruefer
gleichzeitig; es mitzunehmen waere genau der Fehler gewesen, der hier behoben wird.

**Nachgemessen an echten Paketen:**

| Fall | Ergebnis |
|---|---|
| Kernbauer an 0140 | Paketdatei, `verlauf.cpp`, `verlauf_probe.cpp`, `verlauf.hpp`, Logbuch, eigener Befund |
| Architekt an 0116 | Paketdatei, `technik.md`, Logbuch |
| Projektmanager auf das Venture | Rueckfall auf die breiten Rollenpfade |
| unbekanntes Paket | Rueckfall |
| zwei gleichzeitige Kernpakete | Schnittmenge: **nur das gemeinsame Logbuch** |

**Der Rueckfall ist Absicht.** Findet sich kein Paket oder kein lesbares Frontmatter,
gelten die breiten Rollenpfade wie bisher. Der schlechteste Fall ist damit das Verhalten
von gestern, nicht ein verlorener Commit.

**Ein Fehler auf dem Weg, weil er lehrreich ist:** Der erste Versuch iterierte ueber
`kopf["dateien"]` als Liste. `frontmatter` liefert dort aber eine **Zeichenkette**
(`"[a/b.md, c/d.md]"`), und eine Zeichenkette zerfaellt beim Iterieren in Buchstaben. Der
Pfadfilter darunter warf die Buchstaben still weg -- der Test lief gruen durch, und der
Commit haette Paketdatei und Logbuch getragen und **die eigentliche Arbeit im
Arbeitsbaum gelassen**. Sichtbar wurde es nur, weil der Test die Pfade ausdruckt statt
nur ein Urteil. Die Zerlegung ist jetzt wortgleich die aus `baulauf.py:240`.

**Was bleibt:** Zwei gleichzeitige Laeufe derselben Rolle teilen sich weiterhin
`notizen/<rolle>.md`. Wer zuerst committet, nimmt den Logbucheintrag des anderen mit.
Das ist eine echte, aber kleine Ueberschneidung -- Logbucheintraege sind additiv, und der
Betreff nennt trotzdem das richtige Paket. Ein eigenes Paket waere es wert, wenn es
jemandem auffaellt.
