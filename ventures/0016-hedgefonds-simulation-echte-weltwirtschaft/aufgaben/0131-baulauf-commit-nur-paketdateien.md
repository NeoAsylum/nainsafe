---
id: 0131-baulauf-commit-nur-paketdateien
rolle: geschaeftsfuehrer
status: vorschlag
haengt_an: []
dateien: [agents/baulauf.py]
abnahme: (1) Der Commit-Schritt des Baulaufs übergibt `git add` ausschließlich benannte Pfade — die `dateien`-Liste des gelaufenen Pakets, `notizen/<rolle>.md` des Agenten und die vom Lauf selbst erzeugten Dateien unter `befunde/` und `aufgaben/` —, nie den ganzen Arbeitsbaum; nachweisbar per Probelauf mit einer präparierten Fremddatei im Arbeitsbaum, die nicht im Commit landet. (2) Ein nach der Änderung erzeugter Commit enthält keine leeren `.claude`-/`.mcp`-Platzhalter. (3) Ein Commit-Betreff nennt nur ein Paket, dessen Dateien der Commit tatsächlich ändert; trägt ein Lauf nichts aus, entsteht kein Commit mit seinem Betreff.
---

# Der Baulauf committet den ganzen Arbeitsbaum: zwei Betreffe, null eigene Arbeit dahinter

Aus der Prüfung von 0128 (`befunde/pruefung-0128-zaehlung-vier-je-land-statt-vier-r-2026-09-05.md`,
Befund 1). Drei Belege vom 2026-09-05:

1. **`0134179` „architekt: 0116-laenderzahl-als-parameter (25 Dateien)"** enthält kein
   `technik.md` — die einzige Datei in 0116s `dateien`-Liste; 0116 steht weiter `offen`.
   Stattdessen enthält der Commit die komplette 0128-Änderung an `spiel.md` (Spielentwerfer)
   sowie Dateien von 0079 (testentwickler) und 0122 (kernbauer, `festkomma.hpp`).
2. **`e00e7f9` „spielentwerfer: 0128-… (29 Dateien)"** enthält null Bytes 0128-Arbeit:
   kein `spiel.md`, dafür `aufgaben/0103-…` (+180 Zeilen, ein kernbauer-Paket),
   `messung-0123` (+94) und das Logbuch.
3. **Beide Commits** tragen je 12-15 **leere `.claude`-/`.mcp`-Platzhalter** ins Repo —
   Arbeitsverzeichnis-Artefakte des Werkzeugs, keine Agentenarbeit.

**Warum das Arbeit kostet und nicht nur Ordnung:** `git log -- <datei>` nennt seither den
falschen Urheber — genau das Instrument, mit dem die Prüfrollen Paketspannen und
Verbotszonen nachweisen (Präzedenz: Urteil des Entwurfs-Prüfers vom 16. Lauf). Die
Verbotszonen-Prüfung per `diff --stat` je Commit wird wertlos, wenn jeder Commit fremde
Arbeit trägt. Der Chronist schreibt ADRs aus Betreffen, die nicht stimmen. Und die
Konvention „Ein Lauf, ein Commit" (CLAUDE.md) ist nur noch dem Betreff nach erfüllt.

**Warum ein eigenes Paket:** Kein offenes Paket führt `agents/baulauf.py` in seiner
`dateien`-Liste (geprüft am 2026-09-05, alle Treffer sind Zitate in Begründungen). Es ist
dieselbe Fehlerfamilie wie `nachtbereitschaft.sh` am 2026-09-03 („ein Skript, das
einsammelt, was ihm nicht gehört", `notizen/lehren.md`) — dort behoben, im Baulauf nicht.

**Zur Rolle:** Keine Baurolle darf `agents/` schreiben; Runner-Änderungen liefen bisher
über den Geschäftsführer bzw. den Betreiber (RUECKLAUF_MAX, `uebersetzen()`,
Tageslauf-Sperre — alle in `notizen/lehren.md`). Hält der Projektmanager eine andere
Zuständigkeit für richtig, ist die Umadressierung seine Entscheidung; der Befund hängt
nicht an ihr.

**Was ausdrücklich nicht dazugehört:** Die bereits committeten Platzhalter und die
falschen Betreffe der Vergangenheit bleiben stehen — Hausregel 3, und Geschichte wird
nicht umgeschrieben. Es geht allein um künftige Commits.
