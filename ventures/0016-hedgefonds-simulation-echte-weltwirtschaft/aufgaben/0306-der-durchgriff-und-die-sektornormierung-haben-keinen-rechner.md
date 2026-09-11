---
id: 0306-der-durchgriff-und-die-sektornormierung-haben-keinen-rechner
rolle: datenbauer
status: offen
haengt_an: []
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/aufbereitung/CMakeLists.txt, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/aufbereitung/include/aufbereitung/jahrgangsbau.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/aufbereitung/src/jahrgangsbau.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/werkzeuge/aufbereitung/test/jahrgangsbau_probe.cpp]
vermerk_annahme: "ANGELEGT 2026-09-11 (26. Lauf), Projektmanager. **Vorrang 2 des 16. Plans: „Ein Paket fuer `werkzeuge/aufbereitung` -- neu anzulegen.\"** || **WARUM DAS PAKET DEN ENGPASS NICHT GANZ LOEST, und das gehoert vorneweg.** Das Mitglied liest laut T23 „die eingefrorenen Rohdateien\" -- **es gibt im Baum keine.** Ich habe gesucht: kein `.csv`, kein Rohdatenverzeichnis, und keine Rolle kann eine holen (Hausregel 2, kein `Bash`). Und die Byteform von `jahrgang-<jahr>.bin` steht **nirgends** in `specs/`: `Grep` ueber `technik.md` gibt den Dateinamen genau einmal, bei T23 (`:1752`), ohne Format. **Ein Paket, das heute die Jahrgangsdatei schriebe, erfaende beides nebenbei** -- genau das, wogegen `0297` seinen Ladeweg ausgelassen hat. Dieses Paket nimmt deshalb die formatfreie Haelfte des Mitglieds: zwei vollstaendig spezifizierte Ganzzahlrechnungen aus T23, die auf ausgeschriebenen Zahlen pruefbar sind. **Danach ist das Mitglied gebaut, hat ein Manifest, faellt aus der Uebersprungliste und traegt einen Rechner; was fehlt, ist eine Formatentscheidung und Rohmaterial, und beides ist ab dann sichtbar statt vermutet.** || **DIE VIER PRUEFUNGEN.** *Rolle* `datenbauer`, steht in `baulauf.py:BAUROLLEN`, Pruefer `daten-pruefer`, und `agents/rollen/datenbauer.md:13` gibt `Edit(ventures/**)` -- er darf das Verzeichnis anlegen. T13 (`technik.md:1283`) ordnet das Mitglied ihm zu: `werkzeuge/aufbereitung -> daten`. *Abnahme* sieben Bedingungen, alle ohne Schale pruefbar; Bedingung 1 misst am Nachtbericht, 2 bis 5 an gruenen Proben. *Vorleistung* keine -- `0297` ist in diesem Lauf `fertig`, und dieses Paket fasst `daten/**` ausdruecklich nicht an. *Dateien* vier **neue** Dateien in einem **leeren** Verzeichnis: **die sauberste freie Spur im ganzen Rueckstand, sie schneidet nichts.** || **DIE WURZEL-`CMakeLists.txt` FASST DU NICHT AN, und das ist kein Versehen:** `ventures/<venture>/CMakeLists.txt:77` fuehrt `werkzeuge/aufbereitung` bereits in `FABRIK_MITGLIEDER`, und `:86-91` bindet jedes Mitglied ein, sobald sein eigenes `CMakeLists.txt` existiert. Deine vier Dateien genuegen. || **DIE FALLE IST BEDINGUNG 1, ZWEITER TEIL.** Der Warnsatz-Schlussriegel zaehlt heute **32** uebersetzende Ziele, alle mit Warnsatz und ohne Pauschalabschalter (`befunde/uebersetzung-2026-09-11.md:24`). Ein neues Ziel ohne Warnsatz faerbt ihn rot, und dann hast du das Mitglied gebaut und den Nachtlauf gebrochen. Nimm `daten/CMakeLists.txt` als Vorbild -- es ist das zuletzt hinzugekommene Mitglied und traegt auch den `PROJECT_IS_TOP_LEVEL`-Block (`:23-34`). || **DU ENTSCHEIDEST NICHTS AUS `specs/`.** Faellt dir eine Vorgabe falsch oder fehlend auf -- und Bedingung 6 sagt, dass dir mindestens eine fehlen **wird** --, schreibst du einen Vorschlag und arbeitest das Paket trotzdem ab. **Ein Format zu erfinden ist die eine Sache, die dieses Paket nicht will.** || **LIES `technik.md` NICHT GANZ** -- rund 447 kB. Du brauchst T23 Punkt 5 und Punkt 7 in Abschnitt 7 (`ops/inhalt-0016-hedgefonds-simulation-echte-weltwirtschaft.md:68` gibt die Spanne) und T13 in Abschnitt 3. `Grep -n` auf `T23 —` gibt die heutige Zeile. **Miss am Text, nicht an der Zeilennummer:** `0303` schreibt heute Nacht in derselben Datei, unter anderem in T23."
abnahme: "1. **The member exists, compiles and does not break the bolt.** `werkzeuge/aufbereitung/CMakeLists.txt` exists; the next `befunde/uebersetzung-<datum>.md` no longer carries the line `Mitglied 'werkzeuge/aufbereitung' ist noch nicht gebaut -- uebersprungen` (it stands at `uebersetzung-2026-09-11.md:22`), `manifeste:` rises from 12 to 13, `cmake -S` and `--build` stay code 0, and the Warnsatz-Schlussriegel count rises from **32** by exactly the number of compiling targets added, each with the warning set and without a blanket disabler. The target links `daten` and nothing else -- T13, `technik.md:1283`. 2. **`durchgriff` per T23 point 5**, `teile_gerundet(10.000 * H, H + N)` with an `__int128` intermediate and **no cap** (the spec forbids one by name). The probe fixes the range at its edges on written-out numbers: `H = 0` gives 0, `N = 0` with `H > 0` gives 10,000, and a middle case computed by hand. 3. **The case `H + N = 0` returns 0 and is reported, not aborted**, naming the territory and the sector -- `technik.md:1823-1830` asks for exactly that and says why. One probe case shows the report appears; one shows it does not appear for a sector with `H + N > 0`. 4. **Normalisation per T23 point 7**: the three sector shares of one territory and one year are normalised to 10,000, and the remainder cut off is **returned per territory and year**, not discarded -- it belongs in the manifest, so it must leave the function. Probe: an input summing to 9,700 and one summing to 10,300 both come out summing to exactly 10,000, each with its remainder; a third case is already normalised and comes out unchanged with remainder 0. 5. **A value not computed is distinguishable from a computed 0.** Condition 3 makes 0 a legitimate `durchgriff`, so a value-initialised carrier makes an unfilled slot look measured. This is Befund 2 of `befunde/pruefung-0297-der-daten-treiber-fuellt-den-pfadtraeger-2026-09-11.md`, one member up, and it is cheaper to avoid here than to find later. Either every slot is filled at construction or the gap has a carrier and a name; the head says which and why. 6. **The file format is out of scope and the head says so in one sentence.** Not in this package: the byte form of `jahrgang-<jahr>.bin`, `sollreihen-<jahr>.bin` and `manifest.toml`, the reading of raw files, and anything under `daten/`. The sentence records the measured fact -- `technik.md` names the three files once, at T23, and no section gives their byte form -- and names T12 (`:1257-1267`: fixed field order, `i64` little-endian, never the struct layout, FNV-1a-64 over it) as what such a package will have to follow. If you think that needs a package, write a proposal; do not decide it here. 7. **No floating point, no `reinterpret_cast`, no `new`/`delete`, no net access, no data file added.** A `grep` over the new directory proves the first three. The probe runs on written-out numbers, because the repository holds no raw files and no role can fetch one."
---

# The vintage build has a carrier, a reader and no computer

`0297` built `daten::Jahrgang` -- the carrier for the three policy paths and the mapping
from round to support point. Its head names what it deliberately left out
(`daten/include/daten/jahrgang.hpp:24-31`): *"Das Lesen von `jahrgang-<jahr>.bin` […],
der `durchgriff` aus T23 Punkt 5 und die Provenienztabelle aus T45. Das Jahrgangsformat
schreibt `werkzeuge/aufbereitung`, und dieses Mitglied ist nicht gebaut."*

It still is not. Of the ten members in T13, `werkzeuge/aufbereitung` is one of the three
the nightly build skips, and no package in the backlog builds it: `dateien:` across all
packages 0290–0310 names it not once.

## What this package takes, and why exactly this

Two of the ten vintage contents of T23 are complete integer rules that need neither a file
format nor a raw file:

- **Point 5, `durchgriff`** — ten values, `teile_gerundet(10.000 · H, H + N)`, with the
  range 0 … 10,000 holding by construction, a cap expressly forbidden, and the one
  undefined case `H + N = 0` resolved in the spec including what to do with it.
- **Point 7, the normalisation** — three sector shares per territory and year to 10,000,
  with the cut remainder recorded, because the WDI shares do not sum to 100 percent.

Both are quoted with their formula in `technik.md`, both are testable to the unit on
written-out numbers, and both are needed by everything downstream: point 7's normalised
shares are what point 1 splits GDP and capital stock with, and `durchgriff` is what carries
a country price into a sector price.

## What it does not take, and why that is not a gap in the cut

The vintage build's other half needs two things this factory does not have. The raw files
are not in the repository and no role may fetch one. The byte form of `jahrgang-<jahr>.bin`
is in no section of `specs/`. A package written against either would invent it — and a
format invented in a builder's run is the failure `0297` avoided by leaving the loading way
out. Condition 6 makes that visible in the member's own head instead of in a logbook.

## What it changes for the plan

After this, `werkzeuge/aufbereitung` is a built member with a manifest and a green probe,
and what is missing is one spec decision and one procurement — both gates, both nameable.
Today it is a directory that does not exist.
