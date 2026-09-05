---
id: 0127-uebersetzungsbericht-ohne-proben-heisst-ok
rolle: testentwickler
status: vorschlag
haengt_an: []
dateien: [agents/baulauf.py]
abnahme: Ein Mitglied, dessen Alleinbau-`ctest` keinen einzigen Fall findet, erscheint im Uebersetzungsbericht nicht mehr als `ergebnis: ok`, sondern als eigener, benannter Zustand (etwa `ergebnis: ohne-proben`) -- ausser das Mitglied erklaert seine Probenfreiheit ausdruecklich (eine Markerdatei oder eine Liste im Runner, die Entscheidung liegt beim Betreiber). `werkzeuge/mutation` und ein Mitglied mit vertipptem Probennamen liefern danach nachweisbar verschiedene Berichtzeilen.
---

# Warum das ein eigenes Paket ist

Beim Bau von Paket 0110 wurde gemessen (und im Paketbericht gemeldet, aber nirgends
als Paket festgehalten): `ctest` gibt ohne einen einzigen gefundenen Fall Code 0
zurueck. `agents/baulauf.py:186` ruft `ctest` ohne `--no-tests=error` auf; ein
Mitglied, dessen Proben aus irgendeinem Grund nicht angemeldet wurden, steht damit im
Uebersetzungsbericht als `ok`. Genau diese Zeile hat am 2026-09-04 beim
Belegstellenriegel einen echten Fehler verdeckt (`No project() command is present`,
Bericht trotzdem `ok`) -- die Familie "gruener Bericht ueber nichts" steht in
`notizen/lehren.md` mehrfach.

Es ist kein Teil von 0110: Das Werkzeug dort hat den Schalter fuer sich selbst gesetzt
(`--no-tests=error` im Treiber); offen ist allein der Runner.

**Der Zielkonflikt, der die Abnahme oben formt:** Ein pauschales `--no-tests=error` im
Baulauf waere falsch. Seit 0110 gibt es mit `werkzeuge/mutation` ein Mitglied, das
**absichtlich** keine Probe anmeldet (Entscheidung des Projektmanagers vom 2026-09-05:
`ctest` bleibt frei vom Mutationslauf); der pauschale Schalter machte dessen Alleinbau
dauerhaft rot. Der Bericht muss also drei Zustaende unterscheiden koennen: Proben
gruen, Proben rot, keine Proben gefunden -- und nur der letzte braucht die
Ausnahmeerklaerung.

**Zur Rollenfrage:** `dateien` nennt `agents/baulauf.py`, und dorthin schreibt keine
Baurolle. Ob das eine Runneraenderung des Betreibers wird wie die Faelle in
`notizen/lehren.md` vom 2026-09-01, entscheidet der Projektmanager bzw. der Betreiber;
der Vorschlag haelt nur fest, *was* fehlt und *woran* man die Behebung misst, damit
die Meldung aus dem 0110-Bericht nicht verlorengeht.
