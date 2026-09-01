# Agentenfabrik

Gedächtnis und Werkstatt eines nebenberuflichen IT-Unternehmens, das von Agenten
betrieben wird. Der Betreiber entscheidet an den Gates; dazwischen arbeitet die Maschine
allein.

**Dies ist die laufende Fabrik** (`~/fabrik` in WSL2, seit dem 2026-08-27). Sie
committet selbst. Die Kopie unter Windows ist Ausgangspunkt und Sicherung, nicht der
Betrieb — Änderungen dort wirken erst, wenn sie übertragen werden (`git bundle`, weil
`/mnt/c` in der Distro abgeklemmt ist).

## Was gerade gebaut wird

Seit dem 2026-08-31 sucht die Fabrik nicht mehr, sie baut **eine** Sache:
`0016-hedgefonds-simulation-echte-weltwirtschaft` — eine rundenbasierte Simulation der
echten Weltwirtschaft, in der der Spieler ein Hedgefonds ist und über Positionen,
Beteiligungen und Einflussnahme Regulierung verschiebt.

Der Schalter ist `agents/nachtlauf.py:FOKUS`. Steht dort `None`, nimmt die Fabrik die
Suche wieder auf — nichts daran ist gelöscht, `quellen.yml` hat weiterhin 44 Segmente
und acht Vorgänge, und die dreizehn Rollen der Bewertungskette liegen unter
`agents/rollen/archiv/`.

## Die Regeln, in dieser Reihenfolge zu lesen

| Datei | sagt |
|---|---|
| `CLAUDE.md` | die Hausregeln — vier harte Regeln, Rollentabelle, Statusmodell |
| `grenzen.md` | was das Unternehmen **verkaufen** darf: neun Grenzen, 5.000 € Schwelle |
| `agentenbau.md` | was die Fabrik **herstellen** kann: sechs Baubarkeitsfragen |
| `quellen.yml` | wo gesucht wird, wenn gesucht wird |
| `decisions/` | warum es so ist, wie es ist — neun ADRs |
| `notizen/lehren.md` | was schiefging und was daraus folgt |

Kein Agent darf diese Dateien ändern; die Werkzeuge dafür bekommt er nicht
(`agents/lauf.py:NIE`).

## Der Fluss

```
Sensorik ─> Ideen ─[Gate 1]─> Entwurf ─[Gate 2]─> Bau ─[Gate 3]─> Betrieb ─[Gate 4]
```

Nur der Betreiber setzt einen Status über ein Gate hinweg. **Kein Agent deployt,
versendet, gibt Geld aus oder löscht.** Keine Rolle hat eine Shell — eine Shell umgeht
jede `Edit()`-Sperre, das ist am 2026-08-30 nachgemessen worden. Werkzeugausgaben, die
ein Agent braucht, erzeugt stattdessen der Runner und legt sie als Datei hin.

## Die Läufe

```
03:00 täglich    agents/tageslauf.py    fährt den Nachtlauf, bis das Tagesbudget steht
09:00 täglich    agents/sensorlauf.py   ruht im Fokusmodus
07:00 sonntags   agents/wochenlauf.py   Portfolio, Verbesserung, Digest
alle 30 min      agents/dashboard.py    ops/dashboard.html
```

`nachtlauf.py` entscheidet selbst, was ansteht: eine Entwurfsrunde, solange der Entwurf
nicht abgenommen ist — sonst `baulauf.py`, der **Arbeitspakete statt Rollen** fährt.
Zwei Pakete derselben Rolle laufen gleichzeitig, zwei Pakete mit überlappender
Dateiliste nie.

Nach jeder Baustufe ruft der Runner den Compiler; sein Urteil liegt unter
`ventures/<id>/befunde/uebersetzung-<datum>.md`. Es ist die einzige Stimme in dieser
Fabrik, die nicht von einem Modell kommt.

## Von Hand

```sh
bash    einrichtung/pruefen.sh          # 17 Bedingungen für den unbeaufsichtigten Lauf
python3 einrichtung/rollen-pruefen.py   # jede Rollendatei gegen die Hausregeln
bash    einrichtung/eichen.sh           # nach jeder Änderung an grenzen.md
python3 agents/kontingent.py            # Verbrauch je Rolle
python3 agents/weg.py                   # wo Ideen sterben
```

## Was hier liegt

| Pfad | Inhalt |
|---|---|
| `agents/` | Runner und Rollendateien; `agents/rollen/archiv/` ist stillgelegt |
| `signals/` | Rohbeobachtungen, Markt- und Prozessprofile |
| `research/` | Recherchen mit Quelle und Abrufdatum |
| `ideas/` | Ideen mit Status; 9001 und 9002 sind Eichideen, kein Bestand |
| `specs/` | der Entwurf des laufenden Vorhabens |
| `ventures/` | der Bau: `aufgaben/`, `befunde/`, Quelltext |
| `gates/` | die Entscheidungen des Betreibers |
| `ops/` | Berichte für den Betreiber, allen voran `ops/plan.md` |
| `notizen/` | ein Logbuch je Rolle, dazu `lehren.md` für alle |
| `einrichtung/` | Prüfungen und Berichte; `einrichtung/archiv/` ist Einmaliges |
| `schema/state.sql` | Schema der Zustandsdatenbank |

`state.db` liegt außerhalb der Versionierung — reproduzierbar aus Schema und
Frontmattern, und sie würde bei jedem Lauf Konflikte erzeugen.

## Der Stand, in Zahlen

Zum 2026-09-01: **31 aktive Rollen**, 13 archivierte. 27 Marktprofile, 8 Prozessprofile,
49 Recherchen, 16 Ideen — davon **eine** in Arbeit, der Rest abgelehnt oder widerlegt.

Das ist kein Fehler, sondern der Zweck: Die Fabrik hat fünfzehn Produkte verhindert, die
niemand gekauft hätte. Was sie noch nicht hat, ist eine Zeile ausgelieferten Code — der
erste Baulauf war am 2026-09-01, und er hinterließ Markdown statt Rust. Woran das lag
und was dagegen eingebaut wurde, steht in `notizen/lehren.md`.
