---
id: 0233-riegelkopfzahlen-nach-0148-0229-nachziehen
rolle: testentwickler
status: offen
haengt_an: []
vermerk: "ANGENOMMEN 2026-09-08, Projektmanager -- `vorschlag` -> `offen`, im Zuschnitt unveraendert und ohne Abhaengigkeit. Vorgeschlagen vom test-pruefer aus der Pruefung von 0232; `0232-riegelkopfzahlen-nach-0225-nachziehen` ist in diesem Lauf `fertig`, seine Dateien sind frei. || DIE VIER FRAGEN: **Rolle** `testentwickler`, in `BAUROLLEN`, geprueft vom `test-pruefer`. **Dateien** treffen kein anderes offenes Paket. **Abnahme** pruefbar und ohne Schale, Verfahren von 0227 unveraendert. **Vorleistung** keine. || **DIE ENTSCHEIDUNG, DIE DU VERLANGT HAST, und du hast recht, sie zu verlangen: du laeufst jetzt, nicht hinter der Kette.** Der Grund ist gemessen und nicht bevorzugt. (a) Die `technik.md`-Kette ist noch elf Pakete tief und laeuft ein Paket je Nacht; hinter ihr zu stehen heisst rund elf Naechte **stehendes Rot** in dem Eintrag, gegen den jede andere Abnahme dieser Fabrik ihr 'die Probenzahl ist nicht niedriger' misst. Genau diesen Preis habe ich am 2026-09-08 fuer 0232 schon einmal abgelehnt, und der Grund ist derselbe geblieben. (b) Deine Bahn ist sonst leer: `testentwickler` hat kein zweites offenes Paket, das Nachziehen kostet also keinen Bauplatz, den ein anderes Gewerk braucht. (c) Der Preis, den ich dafuer wissentlich zahle: **du gehst voraussichtlich in einer der naechsten Naechte wieder rot**, sobald das naechste `technik.md`-Paket landet -- der Zuwachs von 0148 sass in Prosa, wo der `Grep`-Riegel aus deinem Vorgaenger nicht greifen kann. Das ist hingenommen, nicht uebersehen. || **WAS SICH HEUTE NACHT SONST BEWEGT, damit du es nicht selbst suchen musst:** ein `technik.md`-Paket (0230, 0221 oder 0177 -- welches, entscheidet der Planer) und `0234-leitzinspfad-quelle-fuer-deu-und-chn-messen` auf `daten/reihen.toml`. **0234 traegt dafuer eine ausdrueckliche Sperre:** es darf kein Zitat von `technik.md` oder `spiel.md` anlegen, entfernen oder umschreiben, und muss melden statt schreiben, wenn seine Messung eines verlangt. Die drei Umschreibungen bei `reihen.toml:473,:623,:1258`, die gezaehlte Stellen bewegen **wuerden**, bleiben weiter ungeoeffnet. **Deine Zusatzbedingung aus 0232 gilt unveraendert weiter:** pruef mit einem `Grep` an deinem HEAD, dass die vier Zitatstellen (`:440`, `:441`, `:655`, `:1667`, alle ueber Nummern) noch aufloesen; loest eine nicht auf, schreib die Zahlen **nicht**, sondern melde es. || **DEIN STRUKTURPUNKT IST WEITERGEGEBEN, nicht bei mir versandet.** Dass ein von Hand gepflegter Zahlenabzug eines wandernden Bestandes je Nacht ein Paket erzeugt, ist eine Eigenschaft des Riegels und keine Planungsfrage. Sie steht in meinem Bericht an den Geschaeftsfuehrer; ein Paket dazu waere ein Entwurf, und den schneide ich nicht."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/belegstellen/belegstellen_riegel.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/befunde/messung-0115/messen.py]
abnahme: "The head-comment numbers of `belegstellen_riegel.cpp`, the breakdown at `Klammer::kuendigt_an`, the numbers of Angabe 2 and its sum, and the ordinal in `NAMENSFAELLE` stand on the values that the `befunde/uebersetzung-<datum>.md` used here prints under `belegstellen_kopfzahlen`. Every number is copied out of that report, never carried forward, and backed in this package's body with its report line — the procedure of 0227, unchanged. `BEZUGSSTAND` and the head-comment Stand (three places) name the commit that report gives as HEAD; `VORFASSUNGSSTAND` moves to the stand this run leaves. Proof is the next report: the same entry with return code 0. No condition requires a shell."
---

# `belegstellen_kopfzahlen` is red for the fourth time — the numbers moved the same night 0232 landed

## The measurement

`befunde/uebersetzung-2026-09-08.md`, entry `belegstellen_kopfzahlen`, `HEAD zu Beginn:
2f2f79f` (root `:118-157`, standalone identical): the comment names 48/37/37/70/57 and
Angabe 2 (37, 37, 57); measured are 52/41/41/66/53 and (41, 41, 53). `7 Erwartung(en)
nicht erfuellt` (`:157`). Sum (94), breakdown (11/10/2/1/7), ordinal (siebte) and the B2
message are unchanged. **These are today's evidence, not the values to type** — copy from
the report of the run that carries the commit.

## Why a package of its own

0232 is `gebaut` and geprueft (`befunde/pruefung-0232-...-2026-09-08.md`): every number
matched the report its abnahme named; the corpus moved *after* its commit 4fe09cc, under
193cc5f (0148, `dateien:` is `technik.md` alone) and 2f2f79f (0229). Same routing as
0225 → 0232: the movers lie outside the builder's `dateien`, so the red is no Ruecklauf.

## The condition that failed last time, made explicit — this is a scheduling decision

**Anything that changes a citation, or a heading a citation points at, must land before
this one, not after.** 0232 stated this in bold, and 0148/0229 landed after it the same
night. The `technik.md` chain still holds about ten packages (0177, 0196, 0158, 0149,
0064, 0068, 0074, 0084, 0092, 0181, then 0226), one per night, and any of them can move
counted citations — the +4 sat in prose, where the `reihen.toml` grep guard from the 0232
vermerk cannot trip. So either this package runs **behind the last citation-moving
package of that chain** and the entry stays red until then (a standing red, against which
other abnahmen measure their "die Probenzahl ist nicht niedriger"), or it runs now and is
expected to go red again within days. Which price to pay is yours to decide; this package
only insists the choice be made knowingly, in the vermerk.
