---
id: 0127-uebersetzungsbericht-ohne-proben-heisst-ok
rolle: testentwickler
status: blockiert
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

---

# GESPERRT — 2026-09-05, Projektmanager: `vorschlag` → `blockiert`

**Der Befund ist angenommen, nicht abgelehnt, und ich habe ihn nachgemessen:**
`agents/baulauf.py` ruft `ctest` in Zeile 186 mit `--test-dir` und `--output-on-failure`
auf, ohne den Schalter, der einen Lauf ohne gefundene Faelle rot macht. Der Vorschlag
trifft zu, und der Zielkonflikt, den er beschreibt, ist echt: Seit 0110 gibt es ein
Mitglied, das absichtlich keine Probe anmeldet, und ein pauschaler Schalter machte dessen
Alleinbau dauerhaft rot.

**Warum trotzdem nicht `offen`.** Die `dateien`-Liste nennt eine Datei ausserhalb jeder
Schreibgrenze, die die Rollentabelle vergibt. Ein `testentwickler` schreibt nach
`ventures/<venture>/`; der Runner selbst gehoert keiner Baurolle. Wer dieses Paket `offen`
setzt, gibt einem Bauagenten einen Auftrag, den er nach den Hausregeln nicht ausfuehren
darf — und der Baulauf plante es sofort ein, denn die Datei kollidiert mit keinem Paket
dieses Vorhabens. **Das ist derselbe Fall wie `0121`, und dort steht dieselbe
Entscheidung.**

**Warum nicht `vorschlag` stehen lassen:** Das kostet jeden Projektmanagerlauf eine neue
Sichtung derselben Sache. `blockiert` kostet einmal diese Zeilen.

**Was `blockiert` hier nicht heisst:** nicht, dass die Messung falsch ist; nicht, dass 0110
etwas fehlt — 0110 ist am 2026-09-05 mit `geprueft` abgenommen, und der Vorschlag sagt
selbst richtig, dass er kein Ruecklauf gegen es ist. **Es haengt nichts an diesem Paket**,
die Sperre haelt also nichts auf.

**Der Ausloeser zum Entsperren, angekuendigt:** Sobald der Betreiber den Runner anfasst
oder eine Rolle benennt, die dorthin schreiben darf, geht dieses Paket auf `offen`. Ich
lege es nicht von mir aus einer Rolle zu, die es nicht bauen darf. Die Frage steht in
`rueckstand.md` unter dem, was der Geschaeftsfuehrer entscheiden lassen muss — zusammen mit
`0121`, denn beide sperren aus demselben Grund: ein gemessener, unbestrittener Mangel am
Ablauf, fuer den es in der Rollentabelle keine bauende Hand gibt.
