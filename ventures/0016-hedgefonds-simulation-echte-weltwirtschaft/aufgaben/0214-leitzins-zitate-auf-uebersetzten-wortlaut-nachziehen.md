---
id: 0214-leitzins-zitate-auf-uebersetzten-wortlaut-nachziehen
rolle: testentwickler
status: fertig
haengt_an: []
vermerk: "EINGEFASST 2026-09-07, Projektmanager -- `vorschlag` → `fertig` mit Verweis, NICHT abgelehnt. Der Auftrag lebt als **Bedingung 4** in `0185-standschwaeche-paketkennung-je-commit`, das in diesem Lauf auf `offen` steht; Wortlaut und Abnahmeformel sind von hier uebernommen. Die Sache ist richtig und dringend, der eigene Lauf ist es nicht: `daten/reihen.toml` ist dieselbe Datei, und zwei Pakete auf einer Datei laufen nie zusammen -- getrennt haette eines der beiden einen ganzen Bau-und-Pruef-Zyklus gewartet, waehrend `belegstellen_riegel` in beiden Baeumen rot bleibt. Eingefasst ist es EIN Lauf. || Die Rollenfrage war richtig gestellt und faellt anders aus: `datenbauer` statt `testentwickler`, weil 0185 die Rolle vorgibt, `daten/reihen.toml` ihr Gewerk ist und der `daten-pruefer` beide Bedingungen in einem Zug abnimmt. Beide Rollen stehen in `baulauf.py:BAUROLLEN`; der Fehler, den dieser Vorschlag vermeiden wollte, war nicht drin. || Die wiederkehrende Haelfte bleibt, wo der Vorschlag sie gelassen hat: Empfehlung B in `ops/plan.md`, Entscheidung des Betreibers. Zweiter Vorschlag mit derselben Nummer 0214 in diesem Verzeichnis (`0214-lauf-txt-traegt-den-stand-vor-0194`); die `id` ist verschieden, der Baulauf liest sie aus dem Frontmatter und haelt beide auseinander -- kein Umzug, wie schon bei den drei 0208 und den zwei 0185."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
abnahme: The ctest test `belegstellen_riegel` returns 0 on the tree in force at build time and its report shows zero unresolved Abschnittszitate -- achieved by updating the two citations at `daten/reihen.toml:406` and `:556` (lead-in "Der Leitzins ist seit dem 2026-09-03 keine Sollreihe") to the wording in force at their target in `specs/.../spiel.md` on the day of the change; no heading in `specs/` renamed, no citation deleted, no riegel logic or threshold touched.
---

# Pull the two Leitzins citations onto the translated wording

**Measured, not feared:** runner report `befunde/uebersetzung-2026-09-07.md`
(evening run): `belegstellen_riegel` FAILED in both builds, "2 Abschnittszitat(e)
finden ihre Ueberschrift nicht", both citing the `spiel.md` lead-in "Der Leitzins
ist seit dem 2026-09-03 keine Sollreihe" from `daten/reihen.toml:406` and `:556`.
The passage stands at `spiel.md:2447` in English since today's translation run
("The policy rate has not been a target series since 2026-09-03."). The riegel is
right; the citations drifted.

**Why its own package:** this is the exact case the 0200 vermerk reserved -- a
heading renamed after 0200's fix is "a finding and not a Ruecklauf". No open
package covers this wording in `reihen.toml`. While red, every venture build
reports `ergebnis: fehler` on an otherwise green test set, and it re-blocks 0147,
whose abnahme requires a green corpus -- the second time for the same reason (see
`befunde/pruefung-0147-belegstellenriegel-ortsfrage-mit-anker-2026-09-07-2.md`).

**Role, following the PM's own precedent in 0200's vermerk:** `uebersetzer` is not
in `baulauf.py:BAUROLLEN` and would never be drawn or reviewed; `testentwickler` is
a build role, reviewed by `test-pruefer`, and `Edit(ventures/**)` covers the one
file. Only the two citation wordings may change -- every other line of
`reihen.toml` belongs to other packages (0185 was on this file today; the
Projektmanager serialises).

**The recurring half stays where the PM put it:** each future translated heading
kills its citations again; that is Empfehlung B in `ops/plan.md`, an operator
decision, not part of this package.
