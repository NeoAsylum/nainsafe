---
typ: pruefung
paket: 0133-schlussriegel-nachbau-laeuft-nirgends
pruefer: test-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Beide Abnahmebedingungen mit eigener Mutation und eigenen Vorher/Nachher-Zaehlungen an aus git ausgepackten Baeumen unter $TMPDIR nachgemessen, dazu beide Zusatz-Rotnachweise des Bauagenten unabhaengig wiederholt.
befunde: 0
---

# Pruefung 0133 -- der Waechter des Schlussriegels

Geprueft am 2026-09-05 an Baeumen aus `git archive` unter `$TMPDIR/pruef0133/`,
Stand `a8e1ce5` (HEAD). Die Paketdateien an HEAD sind zeichengleich mit dem Diff in
`4ee0f79`; der Diff ist rein additiv bzw. haertend (neue Probe, `FATAL_ERROR`-Riegel,
Rueckgabewert um `positiv_stumpf` verschaerft) -- keine Schwelle gesenkt, keine
Zusicherung entfernt, keiner der 22 Faelle angefasst. Werkzeuge: CMake 4.2.3, g++,
python3.

## Bedingung 1 -- ein stumpfer Schlussriegel wird ohne Zutun rot: erfuellt

**Mit einer eigenen Mutation gemessen, nicht mit der des Nachweises.** Der Bauagent
ersetzte die Sammelbedingung durch `if(FALSE)`; ich habe sie stattdessen invertiert
(`if(NOT "${${listenname}}" STREQUAL "")` → `if("${${listenname}}" STREQUAL "")`,
Trefferbremse: genau 1 Vorkommen, Nachbarstelle in `fabrik_nichtwert_leeren`
unversehrt). Baum C = HEAD + diese eine Zeile, nicht eingecheckt.

- C konfiguriert selbst **gruen** (`pruefstand`, `FABRIK_SANITIZER=ON`, Code 0) --
  der Riegel meldet Vollzug ueber einen Baum, den er nicht mehr prueft. Genau die
  Luecke, gegen die das Paket geschrieben ist.
- `ctest --test-dir bau-C-pruefstand-on -R schlussriegel_nachbau` → **Failed**,
  `15 Abweichung(en) vom Soll`, Exit ueber ctest sichtbar. Gekippt sind exakt die
  15 Faelle, die am Sammler haengen; `r1_ohnesatz` und `r5_nurschnittstelle` bleiben
  rot (andere Pruefpfade), die vier Soll-0-Faelle und `p_positiv` bleiben gruen.
  Zwei unabhaengig gewaehlte Mutationen, identische Kippmenge -- die Zahl 15 des
  Nachweises ist damit bestaetigt, nicht uebernommen.
- Gegenprobe am unveraenderten Baum A: derselbe gezielte Aufruf **Passed** (0,42 s
  warm; kalt 4,26 s im vollen Lauf).

## Bedingung 2 -- kein Urteil aendert sich: erfuellt

**Handaufruf:** `python3 A/befunde/pruefung-0066/nachbau.py` ohne Umgebungsvariable →
Ablage unveraendert `/tmp/claude-1000/nachbau0066-HEAD`, Ausgabe
`0 Abweichung(en) vom Soll`, `Positivkontrolle p_positiv: bau code=2, 1 Fehler`
(rot, `-Werror=float-conversion`), **Exitcode 0**. 0103/0108 sehen keinen Unterschied.

**Drei Bauwege, beide Profile, vorher und nachher selbst gemessen.** Vorher = Baum B:
HEAD mit `pruefstand/CMakeLists.txt` der Fassung `4ee0f79^` -- also derselbe Baum,
allein um den Paketbeitrag zurueckgedreht. Nachher = Baum A (HEAD). Probenzahl per
`ctest -N`, Namen verglichen:

| Weg | Profil | vorher | nachher | Zuwachs |
|---|---|---|---|---|
| arbeitsbereich | ON  | 15 | 16 | `schlussriegel_nachbau` |
| arbeitsbereich | OFF | 15 | 16 | `schlussriegel_nachbau` |
| kern           | ON  | 10 | 10 | -- |
| kern           | OFF | 10 | 10 | -- |
| pruefstand     | ON  | 3  | 4  | `schlussriegel_nachbau` |
| pruefstand     | OFF | 3  | 4  | `schlussriegel_nachbau` |

Der Zuwachs ist per Namensliste genau die neue Probe und sonst nichts. Die Zahlen
liegen um eins ueber denen des Nachweises (14/3 → 15/4), weil `0129` seit dessen
Bezugsstand `8a2c381` den `bezeichner_riegel` angelegt hat -- an beiden Staenden
konsistent, kein Widerspruch.

Alle 18 Codes am Nachher-Stand einzeln abgefragt: Konfigurations-, Bau- und
`ctest`-Code **0 auf allen sechs Wegen** (Arbeitsbereich 16/16, kern 10/10,
pruefstand 4/4 Proben bestanden, je ON und OFF).

## Die zwei Zusatznachweise des GEBAUT-Absatzes, unabhaengig wiederholt

- **`positiv_stumpf` zaehlt wirklich in den Rueckgabewert.** Baum D = HEAD, allein
  `-Werror` aus `FABRIK_STRENGE` entfernt: alle 22 Urteile unveraendert,
  `0 Abweichung(en) vom Soll`, `p_positiv: bau code=0` mit dem Warnhinweis
  `!! erwartet war ein roter Bau` -- **Exitcode 1**. Die alte Fassung haette hier 0
  zurueckgegeben; genau der Fall, den `ctest` sonst nie saehe.
- **Die Bahn verschwindet nicht still.** Baum E = HEAD ohne
  `befunde/pruefung-0066/nachbau.py`: Konfiguration **Code 1**,
  `CMake Error at CMakeLists.txt:136`, Meldung nennt den fehlenden Pfad.

Zudem laeuft die Probe im echten Baulauf nach, nicht nur in meinem Aufbau:
`befunde/uebersetzung-2026-09-05.md` fuehrt `schlussriegel_nachbau` als `Passed` im
Arbeitsbereichs- (14/16) und im Pruefstandslauf (4/4).

## Wonach ich sonst gesucht habe (ohne Fund)

Abgeschwaechte Tests (Diff beider Dateien rein additiv/haertend; `git log` je Datei:
kein weiterer Commit nach `4ee0f79`); Rekursion der Probe (die 22 Wegwerf-Baeume
binden nur `werkzeugkette.cmake` ein, kein `ctest` im Inneren); Kollision der
Ablagen (`NACHBAU_ABLAGE` liegt je Baubaum, geprueft an zwei parallelen Bauten);
`8a2c381` ist nachweislich `4ee0f79^`, der Bezugsstand des Nachweises stimmt also.

## Randnotizen ohne Urteilswirkung

1. Der `belegstellen_riegel` faellt an jedem ausgepackten Baum zunaechst rot, weil er
   die Vorgaben unter `<Baum>/../../specs/<Baumname>` erwartet -- Messartefakt, kein
   Baumfehler; nach Bereitstellen der specs alles gruen. Der Bauagent hat denselben
   Griff dokumentiert; das ist jetzt der zweite Nachweis in Folge, der diesen Absatz
   braucht.
2. Die zwei Paketdateien liegen im fremden Commit `4ee0f79` (Betreff datenbauer 0078)
   -- vom Bauagenten selbst gemeldet, Gegenstand von `0131`. Kein neuer Befund.
