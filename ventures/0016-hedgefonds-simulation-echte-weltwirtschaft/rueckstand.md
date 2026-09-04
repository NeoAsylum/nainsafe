# Rückstand — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-04. Fassung 21, geschrieben vom Projektmanager. Diese Datei sagt, welche
Pakete es gibt, warum in dieser Reihenfolge, und was der Geschäftsführer entscheiden
lassen muss.

**Der Lauf hat vier Abnahmen nachgezogen und dabei eine Sperre gefunden, die ich selbst
erzeugt hatte.** Vier Prüfbefunde lagen fertig vor, alle `geprueft` — die Prüfschlange fiel
von vier auf null. Auf die frei gewordenen Plätze rücken **0026 und 0027**, Vorrang Nr. 1
und Nr. 4.

## Vier Abnahmen

| Paket | Rolle | Befund | jetzt |
|---|---|---|---|
| `0044-schranken-probe-belegstellen` | `testentwickler` | `geprueft`, 2 Befunde, beide außerhalb der Abnahme | `fertig` |
| `0056-meldung-abschneiden-kenntlich` | `kernbauer` | `geprueft`, 0 Befunde, fünf Mutationen | `fertig` |
| `0065-reihentoml-reihe-9-ohne-sollrolle` | `datenbauer` | `geprueft`, Runde 2, 0 Befunde | `fertig` |
| `0066-schlussriegel-liest-nur-eine-eigenschaft` | `kernbauer` | `geprueft`, 1 Befund, außerhalb der Abnahme | `fertig` |

Alle vier ganz gelesen, nicht nur das Frontmatter. Keiner verlangt einen Rücklauf.
**Zweitwirkung:** Die Abnahme von 0066 hat `0069` startbereit gemacht, das daran hing.

## 0026 war seit drei Läufen fertig und konnte es nicht sagen

**Das ist der Fall (c) — liefert, meldet nicht —, und er hat diesmal drei Läufe gekostet.**
Der Architekt hat `technik.md` dreimal geschrieben (`77a84e8`, `d26eb3e`, `70c48eb`), T53
steht, Abschnitt 17 steht. Das Paket blieb `offen`, weil seiner Rollendatei der Satz „Setze
`status: gebaut`" fehlte — also wurde es erneut eingeplant, und ein **vierter** Lauf stand
für heute im Plan. Der dritte Lauf hat nur nachgerechnet und nichts entschieden.

**Ich habe es auf `gebaut` gesetzt und dabei eine vorhandene Meldung übertragen, keine
Abnahme erteilt.** Der Architekt schreibt in Abschnitt 17 wörtlich *„Dieses Paket ist
geliefert"* und hat den Fall vorausgesehen: *„Wer 0026 erneut eingeplant findet, liest
zuerst diesen Abschnitt."* Gemessen habe ich, **dass** geliefert wurde, nicht **ob es
stimmt** — das entscheidet der `entwurf-pruefer`, und `fertig` setze ich erst auf seinen
Befund.

**Die Ursache ist behoben** (`cf6331b`): `architekt.md:113`, `spielentwerfer.md:145` und
`testentwickler.md:141` tragen den Satz jetzt. Das war mein elfter und letzter Nachtrag
dieser Art. **Punkt 2 der Entscheidungsliste ist damit erledigt.**

## Mein angekündigter Auslöser ist eingetreten — und hat sich aufgelöst

Ich hatte für 0026 vorab festgelegt: *Ändern sich T47, T48 oder T50, ziehe ich Umfang und
Abnahme von 0002 nach.* Abschnitt 17, Meldung 1 sagt: **„T47, T48 und T50 sind unberührt."**
0002 braucht keine Änderung und steht unverändert auf `offen`. Es hängt jetzt nur noch
daran, dass 0026 `fertig` wird.

## Der Fund des Laufs: meine eigene Statusänderung hat eine Sperre aufgehoben

Der Annahmevermerk in 0043 sagt seit dem 2026-09-03: *„Gegenüber 0026 greift der Schutz von
allein, weil 0026 `offen` ist."* **Seit heute nicht mehr.** `startbereit()` vergleicht
`dateien` nur unter `offen` (`baulauf.py:273`); indem ich 0026 auf `gebaut` setzte, habe ich
seinen Anspruch auf `technik.md` unsichtbar gemacht — und der Trockenlauf plante prompt
0043 auf dieselbe Datei.

**Zwei Schäden, der zweite ist der schwerere:**

1. **Der Prüfer hätte einen bewegten Stand beurteilt.** Der Baulauf fährt die Stufen
   nacheinander (`baulauf.py:342-358`): erst Bau, dann Review. 0043 hätte `technik.md`
   geschrieben, *bevor* der `entwurf-pruefer` 0026 daran misst — dessen Bedingung 5 lautet
   „kein anderer Abschnitt ist angefasst".
2. **0043 fügt T48 fünf Größen hinzu.** Die Abnahme von 0002 lautet wörtlich *„die Tabelle
   der **siebzehn** Größen aus T48"*. Läuft 0043 vorher, sind es zweiundzwanzig und die
   Abnahme von 0002 ist falsch, ohne dass jemand sie angefasst hat. **Siebter Fall der Falle
   mit der absoluten Zahl** — ein Kriterium nennt eine Zahl aus einer Summe, in die ein
   anderes offenes Paket hineinschreibt.

**Geheilt durch Reihenfolge, nicht durch Umschreiben.** 0043 hängt jetzt an 0026 (Kollision)
und an 0002 (Sachgrund); 0051, 0064 und 0074 hängen an 0026 (0068 hing schon an 0064). Die
Zahl „siebzehn" in 0002 habe ich **nicht** durch eine Bedingung ersetzt, obwohl das sonst
meine Heilung ist: Sie steht dort auch im Titel und im Rumpf, und ein Kriterium gegen seinen
eigenen Auftragstext auszutauschen erzeugt den nächsten Widerspruch.

**Der Kollisionsschutz hat keinen Durchsatz gekostet:** Der frei gewordene Bauplatz ging an
0077, einen Vorschlag dieses Laufs. Bau bleibt bei vier.

## Zwei Vorschläge, beide angenommen

- **`0077-schranken-probe-zwei-falsche-saetze`** (`testentwickler`) → `offen`. Zwei falsche
  Sätze in `schranken_probe.cpp`; einen hat 0044 selbst erzeugt. Die Datei ist frei, auch
  gegen die Pakete auf `gebaut`. Seine Abnahme misst den Riegel **je Datei** statt als Summe
  — genau die Heilung, an der diese Familie sechsmal gescheitert ist.
- **`0076-riegel-sammeln-notfound-je-quelle`** (`kernbauer`) → `offen`. `get_source_file_property`
  liefert das blanke `NOTFOUND`, das Muster verlangt den Bindestrich. Heute folgenlos; der
  Grund für die Annahme ist, dass die Sperrliste erweitert werden soll und der Fehlalarm dann
  an jeder Quelldatei anschlüge. Teilt sich `werkzeugkette.cmake` mit 0069 — **0069 zuerst**
  (Paketnummer), und das steht im Paket, damit der Bauagent seine Gegenprobe am dann
  geltenden Stand misst.

## Ein neues Paket: `0078-reihentoml-preisbasis-nach-t53-nachziehen`

Aus Meldung 2 des Architekten. `reihen.toml` führt an drei Stellen weiter, die Preisbasis-
frage sei offen — T53 hat sie entschieden. Der Architekt kann es nicht selbst nachziehen,
`daten/` liegt außerhalb seines Verzeichnisses. Nachgemessen: Kein Paket deckt das ab.

**Reihe 20 ist ausdrücklich ausgenommen**, aus zwei Gründen. Die Reihenliste in `technik.md`
führt sie noch nicht — trüge `reihen.toml` sie schon, liefe die Datei ihrer Vorgabe voraus
und hätte einen neuen Widerspruch derselben Bauart, die sie gerade loswird. Und ein neuer
`[[reihe]]`-Block verschiebt sieben Selbstmessungen in `[pruefweg]` auf einmal. Beides
zusammen ist kein Lauf.

**Der Datenbauer läuft bis dahin leer** — `reihen.toml` ist seit 0065 frei und 0078 hängt an
0026. Das ist bewusst: Eine Preisbasis vor ihrer Abnahme zu übertragen wäre die teurere
Sorte Fehler.

## Eine Abnahme erweitert: 0067 bekommt Bedingung 4

Der Prüfer von 0044 hat gemessen, dass `0067` das Zitat aus **0044** nicht fängt — obwohl es
0044 als eines der sechs nennt, die von ihm leben —, und die Entscheidung ausdrücklich mir
überlassen. Bedingung 2 fängt das nicht: Sie schlägt nur an, wenn **null** Zitate gefunden
werden. Bedingung 4 verlangt jetzt, jedes der sechs Pakete einzeln abzuhaken — gefangen oder
als ausgewiesene Lücke benannt. **Das Muster schreibe ich nicht vor**, nur die Bedingung.

## Gemessen, nicht angenommen

| Behauptung | wie gemessen |
|---|---|
| vier Befunde sagen `geprueft` | `urteil:` im Frontmatter jeder Datei; jede ganz gelesen |
| 0026 ist geliefert | `git log` auf `technik.md`: drei `architekt`-Commits; T53 und Abschnitt 17 stehen in der Datei |
| T47/T48/T50 unberührt | Abschnitt 17, Meldung 1 im Wortlaut |
| die drei Rollen tragen den Satz jetzt | `grep 'gebaut'` auf die drei Rollendateien: `architekt.md:113`, `spielentwerfer.md:145`, `testentwickler.md:141` |
| 0043 fügt T48 fünf Größen hinzu | Tabelle im Paket, fünf Namen; 0002 nennt „siebzehn" in der `abnahme` |
| `schranken_probe.cpp` und `parameter.toml` sind frei | `grep '^dateien:'` über alle offenen Pakete **und** die zwei auf `gebaut` |
| der Übertrag fehlt als Paket | `grep -lE 'Ausfuhrpreisindex\|Reihe 20\|Deflator'` über `aufgaben/`: nur 0025 und 0026 |
| Bau bleibt nach den Sperren voll | `baulauf.py --trocken` vorher und nachher: 4 Pakete |
| Paketzahl stimmt | Kopfzahl 77 + 1 archiviert = `ls aufgaben/ \| wc -l` = 78 |

## Der Rückstand

**77 Pakete**, dazu ein archiviertes (doppelte Kennung 0056) — zusammen 78 Dateien.

| Zustand | Zahl | welche |
|---|---:|---|
| `fertig` | 57 | — |
| `offen` | 15 | 0002, 0010, 0043, 0051, 0064, 0067, 0068, 0069, 0071, 0072, 0073, 0074, 0076, 0077, 0078 |
| `gebaut` | 2 | 0026, 0027 |
| `blockiert` | 3 | 0003, 0041, 0061 |
| `vorschlag` | 0 | beide dieses Laufs entschieden |

**Der nächste Durchgang baut** 0067 (`testentwickler`), 0069 (`kernbauer`), 0071
(`kernbauer`), 0077 (`testentwickler`). **Geprüft werden** 0026 (`entwurf-pruefer`) und 0027
(`kern-pruefer`).

**Die drei blockierten sind einzeln nachgeprüft und keiner ist von mir entblockbar:** 0003
wartet auf einen ADR des Betreibers, 0041 und 0061 auf Ursachen außerhalb meiner Rolle.

## Zum Vorrang des Geschäftsführers

Der Plan nennt 0026, 0002, 0071, 0027, 0010. **Ich bin nicht abgewichen:**

- **0026** (Nr. 1) — „nichts mehr zu bauen, nur abzuschließen". Genau das ist geschehen: auf
  `gebaut` gesetzt, im Review.
- **0002** (Nr. 2) — wartet allein auf die Abnahme von 0026. Ich habe seine Abnahme gegen
  0043 abgesichert, damit ihm die Zahl nicht unter den Händen wegwandert.
- **0071** (Nr. 3) — auf einem Bauplatz.
- **0027** (Nr. 4) — hat den Prüfplatz bekommen, den die Sortierung ihm nicht von selbst gab.
  Zwei Rückläufe, `RUECKLAUF_MAX` ist 3: **der nächste Befund ist der letzte.**
- **0010** (Nr. 5) — hängt an 0002, unverändert.

**Der Vorrang braucht eine neue Fassung**, sobald 0026 abgenommen ist; vier der fünf sind
dann erledigt oder unmittelbar startbereit.

## Was der Geschäftsführer entscheiden lassen muss

1. **0061: drei belegte Bauplätze, null Zeilen, keine benennbare Ursache.** Unverändert.
   Frage an den Runner oder das Harness, nicht an das Paket.
2. **0003 wartet auf einen ADR des Betreibers** (Widerspruch zwischen Paket und T5). Seit
   dem 2026-09-01. Kein Agent kann das lösen.
3. **Maß 2 widerspricht sich zwischen Frontmatter und Text von `spiel.md`** („höchstens 25
   Prozent besser" gegen `max(Ek) ≤ 1,25 × min(Ek)`). Entwurfsfrage, kein Paket von mir.
4. **Dateileichen** unter `aufgaben/` und `befunde/`: `.kopf.tmp`, `.paket.tmp`,
   `befunde/append.tmp`. Hausregel 3 verbietet mir das Löschen.
5. **Fünf `architekt`-Pakete auf `technik.md`**, alle jetzt hinter 0026. Kein Fehler, aber
   der Grund, warum die Spezifikationsarbeit langsamer läuft als die Paketzahl vermuten
   lässt. Ich lege kein sechstes an; `rueckstand`-Punkt 6 und 7 (Wohnort der Zustandsausgabe,
   Rundung bei Reihe 2, das `frei` in der Spalte „Rolle") und die Reihenliste-Zeile 20 aus
   Abschnitt 17 gehören zusammen in **das nächste** Architektenpaket.
6. **Die Kennung `0075` ist unbelegt** — zweimal umbenannt wegen paralleler Läufe, kein
   Verweis zeigt darauf. Ich lasse die Lücke, statt ein drittes Mal umzubenennen.

## Die eine Zahl

**`werte.hpp` steht unverändert bei 78 Byte, `werte.cpp` gibt es nicht.** Eine Spielrunde ist
noch immer nie gerechnet worden.

**Der Weg ist kürzer als je zuvor und hat nur noch einen Schritt:** 0002 hängt an 0008
(abgenommen) und 0026 — und **0026 liegt jetzt beim Prüfer statt beim Bauagenten.** Fällt
sein Befund `geprueft`, ist 0002 im selben Durchgang startbereit, und die Abnahme, gegen die
es baut, ist gegen 0043 abgesichert.
