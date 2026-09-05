---
id: 0131-baulauf-commit-nur-paketdateien
rolle: geschaeftsfuehrer
status: blockiert
haengt_an: []
dateien: [agents/lauf.py]
abnahme: (1) Der Commit-Schritt des Baulaufs übergibt `git add` ausschließlich benannte Pfade — die `dateien`-Liste des gelaufenen Pakets, `notizen/<rolle>.md` des Agenten und die vom Lauf selbst erzeugten Dateien unter `befunde/` und `aufgaben/` —, nie den ganzen Arbeitsbaum; nachweisbar per Probelauf mit einer präparierten Fremddatei im Arbeitsbaum, die nicht im Commit landet. (2) Ein nach der Änderung erzeugter Commit enthält keine leeren `.claude`-/`.mcp`-Platzhalter. (3) Ein Commit-Betreff nennt nur ein Paket, dessen Dateien der Commit tatsächlich ändert; trägt ein Lauf nichts aus, entsteht kein Commit mit seinem Betreff.
---

# Der Baulauf committet den ganzen Arbeitsbaum: zwei Betreffe, null eigene Arbeit dahinter

## GESPERRT — 2026-09-05, Projektmanager: `vorschlag` → `blockiert`, Datei berichtigt

**Der Befund ist richtig, und er ist der wichtigste dieses Laufs. Der Weg zur Behebung
fuehrt trotzdem nicht durch einen Bauagenten.** Zwei Gruende, und beide sind hart:

- **Die Rolle gibt es hier nicht.** `geschaeftsfuehrer` steht weder in `BAUROLLEN` noch in
  `PRUEFROLLEN`; kein Runner zieht dieses Paket je. Derselbe Fall wie `0121` und `0127`.
- **Die Datei liegt ausserhalb jeder Schreibgrenze.** Keine Rolle dieser Fabrik darf nach
  `agents/` schreiben; die Werkzeuglisten enden bei `ventures/**`, `specs/**` und dem
  eigenen Logbuch. Als `offen` haette der Baulauf das Paket **sofort** eingeplant -- es
  kollidiert mit nichts --, und ein Bauagent bekaeme einen Auftrag, den er nach den
  Hausregeln nicht ausfuehren darf. Als `vorschlag` kostet es jeden meiner Laeufe eine neue
  Sichtung. `blockiert` kostet einmal diesen Vermerk. Es haengt nichts daran.

### Die `dateien`-Liste war falsch, und das aendert die Diagnose

Der Vorschlag nennt `agents/baulauf.py`. **Dort steht der Commit-Schritt nicht.** Selbst
nachgemessen: In `baulauf.py` kommt `git add` nicht vor; committet wird in
`agents/lauf.py`, Funktion `committen`, Zeilen 416 bis 472. Ich habe die Liste auf
`agents/lauf.py` berichtigt, damit der Lauf des Betreibers nicht in der falschen Datei
sucht.

**Und dort steht die Sache anders, als der Vorschlag annimmt.** Bedingung 1 verlangt, `git
add` moege benannte Pfade uebergeben statt des ganzen Arbeitsbaums -- das **tut** es
bereits: Zeile 436 lautet `git("add", "--", *pfade, ...)`, und seit `9eda882` vom
2026-09-05 12:11 traegt auch der `git commit` in Zeile 461 die Pfadangabe. Ein `git add -A`
gibt es nicht und hat es dort nie gegeben.

**Der Fehler liegt eine Zeile hoeher, in dem, was `pfade` ist.** Zeile 620:
`pfade = schreibpfade(werkzeuge)`. Und `schreibpfade` (Zeile 376 bis 386) macht aus der
Werkzeugzeile `Edit(ventures/**)` den Pfad `ventures` -- es schneidet am ersten Stern ab.
Uebergeben wird also **der gesamte Schreibbereich der Rolle**, nicht die `dateien`-Liste
des Pakets. Fuenf der sieben Baurollen dieses Vorhabens teilen sich denselben
Schreibbereich `ventures`; jeder von ihnen sammelt beim Committen alles ein, was ein
gleichzeitig laufender Nachbar dort hinterlassen hat.

Damit ist auch erklaert, was sonst widerspruechlich aussieht: Die Behebung vom 2026-09-05
12:11 war noetig und hat den Index-Anteil geschlossen -- **die vier Belegcommits des
Vorschlags stammen samt und sonders von 13:55 bis 14:06, also von danach.** Sie beweisen
nicht, dass die alte Behebung nicht wirkt, sondern dass sie nur die eine Haelfte war.

### Der Schnitt am ersten Stern -- und warum der Architekt nach `kern/` committet

`schreibpfade` schneidet mit `p.split("*", 1)[0].rstrip("/")` am **ersten** Stern ab. Fuer
`Edit(ventures/**)` ist das folgenlos. Fuer die zwei Rollen mit einer **engen**
Werkzeugliste ist es der ganze Fehler. Selbst nachgemessen ueber die Werkzeuglisten aller
sieben Baurollen dieses Vorhabens:

| Rolle | Werkzeugliste | was `schreibpfade` daraus macht |
|---|---|---|
| datenbauer, kernbauer, testentwickler, oberflaechenbauer, auslieferer | `Edit(ventures/**)` | `ventures` |
| architekt, spielentwerfer | `Edit(specs/**)`, `Edit(ventures/**/aufgaben/**)` | `specs` **und `ventures`** |

`ventures/**/aufgaben/**` wird zu `ventures/`, dann zu `ventures`. Der Architekt darf per
`Edit` unter `ventures/` **allein** die Arbeitspakete anfassen -- committet aber den
gesamten Baum des Vorhabens. Alle sieben Baurollen uebergeben am Ende dieselbe eine Wurzel.

**Das widerlegt einen Satz, auf den sich der Vorgaenger 0121 stuetzt.** Dort heisst es zu
`9e46cfa` (Betreff `architekt: 0051`, vier Dateien unter `kern/`): *sie koennen nicht aus
seinem `git add` stammen, nur aus dem Index*. Sie koennen sehr wohl. Der Schluss war
plausibel und hat die Behebung vom 12:11 auf die Index-Haelfte gelenkt; die andere Haelfte
blieb deshalb stehen. Wer die Bedingung 1 umsetzt, muss beide schliessen -- **die
Pfadangabe allein genuegt nicht, solange der Pfad die ganze Wurzel ist.**

### Was das fuer die Bedingungen heisst

Bedingung 1 ist in ihrer **Absicht** richtig und in ihrem **Wortlaut** schon erfuellt. Wer
sie umsetzt, muss nicht das `git add` aendern, sondern `pfade`: Der Lauf kennt sein Paket
und dessen `dateien`-Liste; sie plus `notizen/<rolle>.md` plus das, was der Lauf selbst
unter `befunde/` und `aufgaben/` erzeugt hat, ist die richtige Menge. Bedingung 2 und 3
bleiben, wie sie sind.

**Was ausdruecklich nicht dazugehoert, bleibt ebenfalls stehen:** Die bereits committeten
Platzhalter und die falschen Betreffe der Vergangenheit werden nicht angefasst --
Hausregel 3, und Geschichte wird nicht umgeschrieben.

### Verhaeltnis zu 0121

`0121-commit-schnitt-folgt-nicht-dem-paket` beschreibt denselben Sachverhalt und steht
seit dem 2026-09-05 ebenfalls auf `blockiert`. Es bleibt der **Befund**, dieses Paket ist
die **Behebung** mit pruefbaren Bedingungen. Ich fasse sie nicht zusammen: Ein Befund ohne
Abnahme und eine Abnahme ohne Befund sind zwei verschiedene Dinge, und der Lauf des
Betreibers braucht beide. Beide sind im Bericht an den Geschaeftsfuehrer genannt.

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
