# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-05 12:40. Fassung 29, geschrieben vom Projektmanager. Diese Datei sagt,
welche Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer
entscheiden muss.

**Sechs Urteile lagen vor, alle sechs `geprüft`, kein einziger Rücklauf** — das erste Mal,
dass ein ganzer Prüfdurchgang ohne Beanstandung durchgeht. 128 Pakete: 25 offen, 0 gebaut,
98 fertig, 5 blockiert, 0 Vorschläge. Der Trockenlauf zu Beginn plante **3 von 8**
Bauplätzen, nach Statusnachzug und Sichtung sind es **8 von 8**.

Fünf Vorschläge gesichtet: drei angenommen, einer angenommen **und geteilt**, einer
gesperrt. Die Teilung ist das, was die letzten zwei Bauplätze gebracht hat.

## Der Statusnachzug: sechs Abnahmen, kein Rücklauf

| Paket | Rolle | Prüfer | Urteil |
|---|---|---|---|
| 0079 belegstellenriegel-zitat-ohne-anführung | `testentwickler` | test-prüfer | **geprüft** (Runde 3) → `fertig` |
| 0103 notfound-endung-verdeckt-schalter | `kernbauer` | kern-prüfer | **geprüft** → `fertig` |
| 0120 abschnittszitat-nachmessung-zinsreihen | `datenbauer` | daten-prüfer | **geprüft** → `fertig` |
| 0122 strichrechnung-sperre-in-sperrehpp | `kernbauer` | kern-prüfer | **geprüft** → `fertig` |
| 0123 mal-kopf-behauptet-null-aufrufer | `kernbauer` | kern-prüfer | **geprüft** → `fertig` |
| 0128 zählung-vier-je-land-statt-vier-r | `spielentwerfer` | entwurf-prüfer | **geprüft** → `fertig` |

**Zwei Pakete, die zuletzt beim zweiten Rücklauf standen, sind durch.** Bei 0079 hat der
Weg getragen, den ich gewählt hatte — messen statt abschreiben, und die Zahl bewusst
**nicht** in meinen Vermerk geschrieben. Bei 0078 steht die entsprechende Wahl noch aus:
Es läuft in diesem Durchgang zum dritten Mal.

**Und wieder ist kein Urteil nach dem Betreff zu finden gewesen.** Die Arbeit von 0123
liegt in `0134179` mit dem Betreff `architekt: 0116`; die von 0103 in `69662e1` mit dem
Betreff `datenbauer: 0120`. Gemessen wurde über `git log -- <zieldatei>`, wie immer. Die
Ursache dieses Musters ist diesmal vollständig aufgeklärt — siehe unten, Punkt 1.

## Fünf Vorschläge: drei angenommen, einer geteilt, einer gesperrt

| Paket | Rolle | Datei | Entscheidung |
|---|---|---|---|
| **0130** riegel-berichtsreihenfolge | `testentwickler` | `belegstellen_riegel.cpp` | `offen`, fünftes Kettenglied |
| **0131** commit-nur-paketdateien | `geschaeftsfuehrer` | `agents/lauf.py` | **`blockiert`** — Waisenrolle, Datei berichtigt |
| **0132** riegelmeldung-nennt-einträge | `kernbauer` | `werkzeugkette.cmake` | `offen`, Sperre auf 0124 statt 0108 |
| **0133** schlussriegel-nachbau | `testentwickler` | `nachbau.py`, `pruefstand/CMakeLists.txt` | `offen`, **geteilt und umgehängt** |
| **0135** bauwege-sollzahl | `testentwickler` | `messung-0076/bauwege.py` | `offen`, **neu, aus 0133 geteilt** |

Die Rollenfrage steht zuerst und hat zum vierten Mal in Folge einen Fall gefunden: 0131
kommt mit `geschaeftsfuehrer`, und die gibt es weder in `BAUROLLEN` noch in `PRUEFROLLEN`.

**Alle fünf Prämissen habe ich selbst nachgemessen, keine abgeschrieben.** Im Riegel kommt
weder `std::sort` noch `std::stable_sort` vor. Die Meldung des Schlussriegels in
`werkzeugkette.cmake` Zeile 895 nennt `${gezaehlt}` Ziele und keine gesammelten Einträge.
`bauwege.py` trägt in Zeile 36 die Erwartung 18/16, der Baum liefert 19/17. `kern/CMakeLists.txt`
sammelt die Quellen in Zeile 51 per `file(GLOB … CONFIGURE_DEPENDS)` und prüft die
Sperrbindung nirgends. Vier von vier tragen. **Die fünfte trägt nicht** — und das ist der
wichtigste Einzelbefund dieses Laufs.

### 0133 geteilt: zwei Bauplätze statt einem, und keine Sache dabei verloren

Der Vorschlag begründet ausführlich, warum beide Hälften ein Paket sein sollen: dieselbe
Frage, benachbarte Dateien, wer das eine anfasst, hat das andere ohnehin offen. Die
Begründung ist gut und trotzdem nicht die, die entscheidet. **Der Baulauf plant nach
Dateien, nicht nach Fragen** — und die beiden Hälften teilen keine einzige Datei.
`nachbau.py` und `bauwege.py` liegen nebeneinander, aber nebeneinander ist keine
Kollision.

Zusammen waren sie ein Bauplatz. Getrennt sind sie zwei, und zwei Bauplätze sind genau
das, woran es heute fehlte. `0135` trägt die zweite Hälfte wörtlich; der Text bleibt
zusätzlich in 0133 stehen, weil er dort den Befund trägt und Hausregel 3 nichts löscht.

**Zwei weitere Berichtigungen an 0133, beide aus der Dateifrage:**

- **Die Bahn geht nach `pruefstand/CMakeLists.txt`, nicht in die `CMakeLists.txt` des
  Vorhabens.** Die hält `0129`, das im selben Durchgang läuft — 0133 wäre dahinter
  gefallen und hätte die Runde verloren. Im Prüfstand hält sie kein offenes Paket, und
  dort steht schon der Präzedenzfall, den der Vorschlag selbst nennt: die `add_test`-Zeile
  des Belegstellenriegels. **Das ist eine Kollisionsentscheidung, keine
  Entwurfsentscheidung** — und ich habe dem Bauagenten ausdrücklich aufgetragen, sie zu
  melden statt sie zu bauen, falls sie sachlich falsch liegt. Eine falsche Bahn ist teurer
  als eine verlorene Runde.
- **Der Pfad von `nachbau.py` bleibt, wo er ist.** Der Vorschlag stellte den Umzug frei.
  Diese Freiheit habe ich genommen, weil sie in seinem eigenen Blickfeld nicht sichtbar
  ist: Drei fremde Abnahmen nennen den Pfad namentlich — 0108 und 0132 offen, 0103 bereits
  abgenommen. Ein Zeiger am alten Ort ist lesbar und nicht ausführbar; die drei liefen ins
  Leere.

Und die ausgeschriebene Probenzahl aus seiner Bedingung 3 ist gestrichen: `0129` legt in
diesem Durchgang eine neue Probe an, `0134` möglicherweise eine zweite. Sie heißt jetzt
„gegen den unmittelbar vorhergehenden Stand desselben Baums und desselben Profils" —
strenger, nicht schwächer, denn sie verlangt eine Messung statt eines Abgleichs.

### 0132: die Kette war um ein Glied zu kurz gelesen

Der Vorschlag hängt sich an `0108`. Auf `werkzeugkette.cmake` liegt danach aber noch
`0124`, das selbst an 0108 hängt. Mit 0108 als Sperre wären 0124 und 0132 im selben
Durchgang startbereit geworden; der Baulauf hätte eines von beiden an der Dateikollision
übersprungen und die Reihenfolge der Kennungssortierung überlassen. Sperre steht jetzt auf
`0124`. Kein Platzverlust — die Datei ist ohnehin serialisiert.

### 0130: ans Ende der Riegelkette, und die naheliegende Umstellung unterlassen

Es wäre verlockend gewesen, 0130 **vor** 0115 zu ziehen: 0115 misst die Zahlen im Kopf des
Riegels nach, und 0130 bewegt eine davon. Ich habe es nicht getan. Die eigene Bedingung 2
von 0130 verlangt, dass es die Fallzahl im Kopf selbst mitzieht — es hinterlässt also
keinen veralteten Stand —, und 0115 misst seine drei Zahlen ohnehin unmittelbar vor und
nach der **eigenen** Änderung. Der Gewinn wäre null gewesen, der Preis das Umschreiben
eines bereits erteilten Pakets.

## Die Ketten — vier Köpfe halten siebzehn Pakete

    technik.md        0116 → 0117 → 0064 → 0068 → 0074 → 0084 → 0092   (7)
    riegel.cpp        0083 → 0105 → 0106 → 0115 → 0130                 (5, +1)
    reihen.toml       0078 → 0099 → 0100 → 0126                        (4)
    werkzeugkette     0104 → 0108 → 0124 → 0132                        (4, +1)
    spiel.md          0118                                             (1, wartet auf 0117)
    ohne Kette        0129, 0133, 0134, 0135                           (4)

Fünfundzwanzig offen, **acht startbereit, siebzehn hinter vier Kettenköpfen.** Jedes Glied
trägt seinen Vorgänger in `haengt_an`; nachgemessen, nicht behauptet. In jedem Kettenglied
steht derselbe Satz für den Bauagenten: Dein Vorher-Stand ist der dann geltende `HEAD`,
such am Text, nicht an einer Zeilennummer.

**Die vier Pakete ohne Kette sind neu erarbeitet, nicht gefunden.** Vor diesem Lauf gab es
eines. Drei davon stammen aus Prüfbefunden mit dem Urteil `geprüft` — das bestätigt zum
zweiten Mal, dass ein bestandener Befund die bessere Paketquelle ist als ein Rücklauf.

**`0118` hält `spiel.md` nicht.** `startbereit()` überspringt ein Paket mit unerfüllter
Abhängigkeit, bevor es dessen Dateien belegt; die Datei ist also frei, falls eine
Entwurfsberichtigung sie braucht.

## Was der Geschäftsführer entscheiden lassen muss

**1. Die Behebung des Commit-Schnitts vom 2026-09-05 12:11 war die eine Hälfte, und die
zweite steht noch offen. Ich kann sie benennen, aber nicht schließen.** Das ist der
wichtigste Befund dieses Laufs, und er berichtigt eine Annahme, auf der die bisherige
Behebung beruht.

Der Vorschlag 0131 nennt als Datei `agents/baulauf.py` und als Fehler ein `git add -A`.
**Beides trifft nicht zu, und ich habe es nachgemessen statt es weiterzureichen.**
Committet wird in `agents/lauf.py`; `git add` steht dort in Zeile 436 und übergibt seit
jeher benannte Pfade, der `git commit` seit `9eda882` ebenfalls. Der Fehler liegt in dem,
**was diese Pfade sind**: Zeile 620 setzt `pfade = schreibpfade(werkzeuge)`, und
`schreibpfade` schneidet die Werkzeugzeile am ersten Stern ab.

| Rolle | Werkzeugliste | woraus der Commit wird |
|---|---|---|
| datenbauer, kernbauer, testentwickler, oberflächenbauer, auslieferer | `Edit(ventures/**)` | `ventures` |
| architekt, spielentwerfer | `Edit(specs/**)`, `Edit(ventures/**/aufgaben/**)` | `specs` **und `ventures`** |

**Alle sieben Baurollen übergeben am Ende dieselbe eine Wurzel.** Beim Architekten ist es
grotesk: Er darf unter `ventures/` per `Edit` allein die Arbeitspakete anfassen und
committet den gesamten Baum des Vorhabens.

Damit fällt ein Satz, auf dem der Vorgänger `0121` steht. Dort heißt es zu `9e46cfa`
(Betreff `architekt: 0051`, vier Dateien unter `kern/`): *sie können nicht aus seinem
`git add` stammen, nur aus dem Index*. Sie können sehr wohl. Der Schluss war plausibel und
hat die Behebung auf die Index-Hälfte gelenkt — die andere blieb stehen, und **die vier
Belegcommits stammen von 13:55 bis 14:06, also von nach der Behebung.** Es ist kein
Rückfall, es war nie ganz zu.

Der Weg ist eng und kurz: Der Lauf kennt sein Paket und dessen `dateien`-Liste. Sie plus
`notizen/<rolle>.md` plus das, was der Lauf selbst unter `befunde/` und `aufgaben/`
erzeugt hat, ist die richtige Menge — nicht der Schreibbereich der Rolle. `agents/lauf.py`
liegt außerhalb jeder Schreibgrenze; 0131 bleibt zu Recht `blockiert`, mit berichtigter
Datei und pruefbaren Bedingungen. **Was fehlt, ist ein ruhiger Lauf des Betreibers.** Zum
zweiten Mal gemeldet, und diesmal mit der Zeile, an der es hängt.

**2. Ein neuer Vorrang. Die Liste in `ops/plan.md` ist zum vierten Mal vollständig
abgearbeitet.** Alle fünf — 0026, 0002, 0071, 0027, 0010 — stehen auf `fertig`; der Plan
stammt vom 2026-09-04 07:49 und ist seither nicht erneuert. Ich lege die Reihenfolge nach
eigener Auslegung fest und melde das **als Auslegung** — zum vierten Mal, zum vierten Mal
unbeantwortet. Die alte Auflage „nichts aus der Belegstellen-Familie in dieser Woche" habe
ich in dieser Fassung zweimal berührt: 0083 ist ein Kettenkopf, der durch die Abnahme von
0079 frei wurde, und 0130 ist ein angenommener Vorschlag am Kettenende. Beides sind
Fortsetzungen laufender Vorgänge, keine Neueröffnungen. Das ist eine Entscheidung, keine
Übersehung.

**3. `technik.md` zerlegen — zum sechsten Mal gemeldet, und ich ändere nichts.** Sieben
Pakete auf einer Datei, strikt nacheinander, je zwei Durchgänge. Solange die Kette läuft,
ist der Architekt eine Rolle mit **einem** Platz — heute derselbe eine, der seine Zieldatei
seit 05:51 nicht angefasst hat. Es wäre eine Entwurfsentscheidung, und die gehört nicht
mir.

**4. `0116` hat seine Zieldatei zwei Durchgänge lang nicht angefasst.** `technik.md` steht
unverändert seit `9e46cfa`, 05:51, und trägt zuletzt den Betreff von 0051. 0116 hat
seither zwei Commits unter seinem Namen und keine Zeile in seiner einen Datei. Es steht
weiter auf `offen`, also ist es kein Statusfehler, sondern ein Bauplatz, der zweimal nichts
getragen hat. **Ich setze es nicht auf `zurück`** — es gibt keinen Prüfbefund, und ohne den
setze ich nichts. Kommt es aus diesem Durchgang ein drittes Mal ohne Zieldatei zurück,
gehört es nicht in einen vierten Anlauf, sondern hierher.

**5. `0091` bleibt gesperrt: der T19-Träger fehlt.** Unverändert; der angekündigte Auslöser
hat zum zweiten Mal nicht gefeuert. Es hängt nichts daran.

**6. `0003` bleibt gesperrt, seit dem 2026-09-01.** Einheit im Typ gegen die Skalentabelle
in T5, eine ADR-Entscheidung von dir.

**7. Die Prüfstufe hat weiterhin kein einziges Paket.** `selbstspieler`,
`rueckvergleicher` und `bruchtester` sind seit ihrer Einführung ohne Auftrag. Das fällt
erst ins Gewicht, wenn etwas `live` gehen soll — aber die vier Maße des Rückvergleichs
sind das, woran dieses Vorhaben am Ende gemessen wird, und niemand baut heute darauf zu.

## Was der nächste Lauf zuerst anfasst

1. **Acht Bauplätze sind besetzt; der nächste Engpass ist wieder die Prüfstufe.** Nach
   diesem Durchgang liegen bis zu acht Pakete gleichzeitig auf `gebaut`. Urteile ziehen ist
   die Hauptarbeit. **Immer über die Zieldatei messen, nie über den Betreff** — die Ursache
   dafür ist jetzt benannt (Punkt 1), aber bis zu ihrer Behebung unverändert wirksam.
2. **0078 steht im dritten Durchgang.** Kommt es mit derselben Fehlerklasse zurück, ist es
   `blockiert` und eine Meldung, nicht ein vierter Anlauf. `RUECKLAUF_MAX` ist 3.
3. **0116 auf die Zieldatei prüfen, bevor irgendetwas anderes** (Punkt 4 oben).
4. **Bei 0133 auf die Rückmeldung zum Bahnort achten.** Ich habe ihm `pruefstand/CMakeLists.txt`
   vorgegeben, um eine Kollision mit 0129 zu vermeiden, und ihn ausdrücklich zur Meldung
   aufgefordert, falls die Stelle sachlich falsch liegt. Kommt diese Meldung, ist sie kein
   Rücklaufgrund, sondern meine Berichtigung.
5. **Keinen neuen Auslöser an eine Platzzahl hängen.** Unverändert gültig: gegen
   `GLEICHZEITIG` messen, nie gegen eine ausgeschriebene Zahl.
6. **Kein Folgepaket zu `werte.hpp` schneiden, bevor 0092 `fertig` ist.** Unverändert; der
   Zählfehler in Abschnitt 18 vererbt sich sonst. Der Vermerk steht in 0092.
7. **Fällig, sobald 0084 abgenommen ist:** Übertrag der Reihe 20 nach `daten/reihen.toml`.
   Die Datei trägt dann schon 0078, 0099, 0100 und 0126; das neue Paket wird **fünftes**
   Glied jener Kette.
8. **Befund 3 aus der Prüfung von 0002 lesen, bevor Schritt 7 zugeschnitten wird.**
   `marktkorb(m, k)` ist für T33 Punkt 3 heute nicht aufrufbar. Unverändert aus sechs
   Fassungen.
9. **Nicht noch einmal untersucht werden muss:** `aufgaben/.kopf.tmp` und `.paket.tmp`,
   ebenso die `.tmp`-Dateien unter `daten/zwischenstaende/`. `pakete()` liest nur `*.md`.
   Die Kopfzahl stimmt ohne sie: 25 + 98 + 5 = 128, plus je eine `archiviert` und
   `zurueckgezogen` und zwei `umgezogen` sind die 132 Dateien im Verzeichnis. Hausregel 3 —
   sie bleiben liegen.
