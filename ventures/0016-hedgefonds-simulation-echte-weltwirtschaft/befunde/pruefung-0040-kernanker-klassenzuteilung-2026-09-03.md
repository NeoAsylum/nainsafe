---
typ: pruefung
paket: 0040-kernanker-klassenzuteilung
pruefer: test-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Alle vier Abnahmebedingungen einzeln nachgefahren — die vier Ankerkennungen und alle acht erwarteten Klassen unabhängig aus T36 nachgerechnet statt aus der Probe gelesen, `grep 'anteile['` über die Datei ausgeführt, Bau und `ctest` selbst wiederholt, und sechs Mutationen des Moduls gegen die unveränderte Probe gemessen; vier machen sie rot, zwei nicht.
befunde: 2
---

# 0040 — Kernanker: geprüft

Beide Befunde sind **Nebenbefunde und kein Verstoß gegen die vier Bedingungen**. Für
den ersten liegt ein Vorschlag bei (0060), der zweite ist Buchhaltung.

## Was ich getan habe

Gelesen: das Arbeitspaket, `pruefstand/test/vorrat_kernanker_probe.cpp`,
`pruefstand/src/vorrat.cpp`, `pruefstand/include/pruefstand/vorrat.hpp`,
`pruefstand/CMakeLists.txt`, `werkzeugkette.cmake`, `technik.md` T36 im Wortlaut und
`befunde/uebersetzung-2026-09-03.md`. **Nicht gelesen:** `notizen/testentwickler.md`
und die Begründung des Bauagenten.

Gebaut und gelaufen ist alles außerhalb des Vorhabensbaums (`$TMPDIR`), damit diese
Prüfung keine Datei des Pakets anfasst:

```
cmake -S …/pruefstand -B $TMPDIR/…/bau  → Warnsatz-Schlussriegel: 5 Ziele, alle mit Satz
cmake --build $TMPDIR/…/bau             → Built target vorrat_kernanker_probe
ctest --test-dir $TMPDIR/…/bau          → 1/3 vorrat_kernanker_probe … Passed 0.01 sec
```

## Der Regressionsbestand — die Frage, die vor allen anderen kommt

Die vier Anker sind der ganze Wert dieses Pakets. Wären sie aus einem Lauf des Moduls
übernommen, prüfte die Probe nur, dass sich nichts ändert. **Ich habe sie deshalb nicht
gegen das Modul geprüft, sondern die Profilliste selbst nachgezählt** — vier
aufsteigende Schleifen über `(a1…a5)` mit Summe 5, unabhängig von `vorrat.cpp`:

| Kennung | nachgezählt | in der Probe | erwarteter Kern nach T36 | in der Probe |
|---:|---|---|---|---|
| 20 | `(0,0,5,0,0)` | `(0,0,5,0,0)` | max bei Index 2 → `LOBBY` | `LOBBY` |
| 44 | `(0,2,2,1,0)` | `(0,2,2,1,0)` | 2 gegen 2, kleinere → `BETEILIGUNG` | `BETEILIGUNG` |
| 60 | `(1,0,0,4,0)` | `(1,0,0,4,0)` | Hebel 4 zählt nicht → `POSITION` | `POSITION` |
| 76 | `(1,1,1,1,1)` | `(1,1,1,1,1)` | Dreifachgleichstand → `POSITION` | `POSITION` |

Die Liste ist als `L == sorted(L)` nachgeprüft, 126 Vektoren. Kennung 76 als
Referenzprofil deckt sich mit dem Festwert aus T36 selbst.

Dasselbe für die zweite Ankerspalte `kern_bei_abweichung`, die die Probe für die
Vorführung braucht: `LOBBY`, `LOBBY`, `POSITION`, `LOBBY` — alle vier von Hand aus
„Gleichstand an die größere Kennung" hergeleitet und deckungsgleich.

## Bedingung 1 — vier Anker als Festwerte, einzeln geprüft, in der Ausgabe

**Erfüllt.** Die Anker stehen als `constexpr std::array<Anker, 4>` (Z. 119–128), je
Anker prüft die Probe beide Hälften einzeln (Z. 333 Vektor, Z. 339 Klasse). Die Ausgabe,
wörtlich:

```
  Kennung  44  (0,2,2,1,0)  gefunden Beteiligung  erwartet Beteiligung  Gleichstand …
```

Kennung, Vektor, gefundene und erwartete Klasse in einer Zeile — für alle vier Anker in
allen drei Prüfungen.

## Bedingung 2 — kein zweites `strategiekern`

**Erfüllt.** `grep -n 'anteile\['` über die Datei liefert genau zwei Zeilen:

```
156:  static_cast<long long>(anker.anteile[i]));            → Ausgabe
288:  Profil{anteile[2], anteile[1], anteile[0], …};        → Spiegelung
```

Keine der beiden vergleicht zwei Anteile gegeneinander; der Gleichstandsbrecher kommt
im Testcode nirgends vor. Die acht erwarteten Klassen sind Aufzählungswerte in der
Ankertabelle, kein Rechenergebnis.

Die Abweichung ist **hergeleitet statt nachgebaut**: Sie spiegelt `(a1,a2,a3)` zu
`(a3,a2,a1)`, ruft das Modul und spiegelt die Klasse zurück. Ich habe die Herleitung
selbst nachvollzogen — Index `j` der gespiegelten Stellen ist Index `2-j` der
ursprünglichen, aus dem kleinsten wird der größte — und sie trägt. Sie ist damit **nicht
unabhängig vom Modul**, und das wäre ein Einwand, wenn es die Probe grün halten könnte.
Kann es nicht: Mutation M1 unten kippt die Abweichung zur richtigen Regel, und die
Probe fällt trotzdem — an den handgeschriebenen Festwerten von Z. 406. Nebeneffekt der
Bauart: Die Probe nagelt `strategiekern` an **sieben** verschiedenen Profilen fest, den
vier Ankern und den drei Spiegelbildern `(5,0,0,0,0)`, `(2,2,0,1,0)`, `(0,0,1,4,0)`.

## Bedingung 3 — die Probe wird rot, wenn die Zuteilung kippt

**Erfüllt, und das ist die Bedingung, an der ich am längsten gemessen habe.** Ich habe
sechs Mutationen des Moduls gegen die **unveränderte** Probe gebaut:

| Mutation von `strategiekern` bzw. der Liste | fehlgeschlagene Zusicherungen |
|---|---:|
| M1 Gleichstand an die größere Kennung (`>` → `>=`) | **13** |
| M2 Position und Lobby vertauscht | **15** |
| M3 Hebel geht mit ein (`FAMILIEN = 4`) | **7** |
| M4 `OHNE`-Abfrage entfernt (dreiwertiger Kern) | **0 — grün** |
| M5 Ordnung der Profilliste gekippt (`a4` absteigend) | **6** |
| M6 Sichtbarkeit zählt statt Hebel | **0 — grün** |

M1 ist genau die Mutation, die die Probe aus 0019 nur an einer einzigen Zeile fing.
Hier stirbt sie dreizehnfach, und die Vorführung nennt den ersten Anker selbst:

```
  zuerst gefangen an:
  faellt auf bei Kennung  44  (0,2,2,1,0)  gefunden Lobby  erwartet Beteiligung
```

Die Erwartung des Pakets — 44 und 76 weichen ab, 20 und 60 nicht — steht als Zusicherung
(Z. 455–461) und in der Ausgabe („von 4 Ankern fangen die Abweichung: 2", dann beide
Durchgelassenen namentlich). M5 belegt, dass auch die Vektorhälfte nicht schmückt.

**M4 ist kein Befund:** Kein Anker ist ein Profil ohne Familienaktion, die Frage steht in
keiner der vier Bedingungen, und die Probe aus 0019 fängt sie — gemessen, sie wird rot
an „genau 6 Profile tragen den Kern ohne". **M6 ist Nebenbefund 1.**

## Bedingung 4 — der Übersetzungslauf führt sie aus

**Erfüllt.** `befunde/uebersetzung-2026-09-03.md` führt unter
`ctest --test-dir …/pruefstand/bau` den Eintrag
`1/3 Test #1: vorrat_kernanker_probe … Passed 0.01 sec`, im Arbeitsbereichsbau als
Test #9 von 11. Ich habe denselben Lauf selbst wiederholt (oben).

Die vier Nebenbedingungen dazu, nachgesehen statt geglaubt: kein `float`, kein `double`,
keine Dezimalzahl; die Einbindungen sind `<array>`, `<cstddef>`, `<cstdio>` und der
eigene Kopf, sonst nichts; außerhalb einer Funktion steht genau ein veränderlicher Wert,
`int fehlgeschlagen = 0`, die Ankertabelle ist `constexpr`.

Zusätzlich mit dem vollen Warnsatz aus `werkzeugkette.cmake` (15 Schalter, `-Werror`)
plus `-fsanitize=undefined,address -fno-sanitize-recover=all` übersetzt und laufen
lassen: Rückgabe 0, Standardfehlerausgabe leer.

## Abgeschwächte Tests

**Keine gefunden.** Die Datei hat genau einen Stand in der Versionsgeschichte — angelegt
und seither nicht angefasst. Keine Schwelle gesenkt, keine Zusicherung entfernt, kein
Test übersprungen. Dass jede Zusicherung wirkt, ist nicht aus dem Code geschlossen,
sondern gemessen: `main` gibt unter M1 Rückgabe 1 und 13 benannte Zeilen aus.

## Nebenbefund 1 — T36 nennt zwei ausgeschlossene Arten, die Anker nageln eine fest

T36 sagt „Hebel **und Sichtbarkeit** gehen nicht ein". Kennung 60 nagelt den Hebel fest:
`a4 = 4` ist der größte Anteil des Profils und darf nicht gewinnen. Für die Sichtbarkeit
gibt es kein Gegenstück — in den Ankern 20, 44 und 60 ist `a5 = 0`, und in 76 ist
`a5 = 1` und damit im Gleichstand mit allem anderen.

**Gemessen, nicht vermutet:** M6 setzt die Familie auf `{a1, a2, a3, a5}` statt
`{a1, a2, a3}` — Sichtbarkeit zählt, Hebel nicht. Alle vier Anker bleiben grün, beide
Ankerprüfungen bestehen, die Abweichung wird weiter korrekt verworfen. Die Probe läuft
vollständig durch: `0 Pruefung(en) fehlgeschlagen`.

Gefangen wird M6 heute allein von 0019, und dort nur über die **Zählung** — „genau 6
Profile tragen den Kern ohne" reißt —, also über einen Nachweis, der keine Klasse
benennt. Genau die Lücke, gegen die dieses Paket geschrieben wurde, eine Art weiter.

**Das ist kein Rücklauf.** Die vier Anker hat das Paket selbst vorgegeben, mit Vektor
und Klasse; der Bauagent hat sie eingebaut und alle vier stimmen. Wer 0040 an einem
fünften Anker misst, hebt ein Kriterium nachträglich an. Der Vorschlag liegt bei
**0060** — ein Anker Kennung 56, `(1,0,0,0,4)`, erwartet `POSITION`. Kennung und Vektor
sind nachgezählt.

## Nebenbefund 2 — die Datei steht im Commit einer anderen Rolle

`pruefstand/test/vorrat_kernanker_probe.cpp` wurde nicht mit
`0149679 testentwickler: 0040-kernanker-klassenzuteilung` committet, sondern mit
`f68e8fb datenbauer: 0042-parameterdatei-indexbegruendung (22 Dateien)`. Der
0040-Commit enthält zwei Dateien, und die Zieldatei ist keine davon.

Ohne Folge für dieses Urteil — die Datei ist da, sie ist die richtige, sie läuft. Aber
„ein Lauf, ein Commit" trägt nur, solange der Betreff sagt, was drin ist; hier wandert
fremde Arbeit in einen Commit und wäre über `git log --oneline -- <datei>` der falschen
Rolle zugeordnet. Ein Befund über den Runner, nicht über das Paket, und deshalb kein
eigenes Paket, sondern eine Meldung an den Projektmanager. Es ist die Familie „eine
Regel an einer Stelle, die der Ablauf nicht so erreicht, wie gedacht" aus `lehren.md`.

## Wonach ich gesucht und nichts gefunden habe

- Ein Anker, dessen erwartete Klasse aus einer Rechnung fällt statt dazustehen.
- Eine Zusicherung, die immer wahr ist — jede geprüfte ist von mindestens einer
  Mutation rot gemacht worden.
- Eine gesenkte Schwelle in der Versionsgeschichte der Datei.
- Ein Aufruf von `runde`, `spiele` oder `Abweichung`, den das Paket vor 0029 verboten
  hat: keiner. Die Probe ruft aus dem Modul nur `erzeuge_profilliste` und
  `strategiekern`.
- Determinismus über Speichern und Laden: entfällt hier. Die Probe ist reine
  Ganzzahlrechnung ohne Ablage und ohne Ein- oder Ausgabe außer ihrem Bericht.

## Nachtrag zur Nummer 0060 — Kollision, gesehen und nicht selbst aufgeräumt

Als ich den Vorschlag angelegt hatte, war `0059` die höchste vergebene Nummer. Beim
Zurücklesen stand daneben ein zweites, ebenfalls noch nicht eingecheckt:
`0060-schlussriegel-blinde-flecken.md`, Rolle `kernbauer`, aus der Prüfung von 0058
desselben Tages. Zwei Läufe haben dieselbe freie Nummer gleichzeitig gegriffen.

Beide Vorschläge stehen, keiner ist überschrieben, und die `dateien`-Listen schneiden
sich nicht (`werkzeugkette.cmake` gegen `vorrat_kernanker_probe.cpp`). Umbenannt habe
ich nichts: Der andere Vorschlag gehört mir nicht, und meinen zu löschen verbietet
Hausregel 3. Aufräumen tut das der Projektmanager — hier steht es nur, damit er es
nicht selbst suchen muss. Gemeint ist in diesem Befund durchgehend
`0060-kernanker-sichtbarkeit`.

## Nachtrag zu Nebenbefund 2 — derselbe Fall, an dieser Prüfung selbst beobachtet

Während ich schrieb, ist er ein zweites Mal eingetreten, diesmal mit meiner eigenen
Ausgabe: Dieser Befund und der Vorschlag `0060-kernanker-sichtbarkeit` stehen im Commit
`63dc717 kern-pruefer: 0058-warnsatz-schlussriegel-alle-ziele (4 Dateien)`. Ich habe
nichts committet.

Damit ist Nebenbefund 2 kein Einzelfall aus der Versionsgeschichte, sondern ein
laufendes Verhalten: Ein Runner, der `git add -A` sieht, nimmt mit, was gerade
danebenliegt — und bei mehreren gleichzeitigen Läufen ist das die Arbeit eines anderen.
`git log --oneline -- <datei>` nennt danach die falsche Rolle, und zwar für **beide**
Läufe. Das ist die Familie aus `lehren.md` vom 2026-09-03 („ein Skript hieß
Bereitschaft und veröffentlichte den ganzen Arbeitsbereich"), eine Ebene weiter, und
gehört dem Projektmanager gemeldet.
