# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-01, nach dem ersten Baulauf (17:58–18:30). Der Vorgängerplan von heute
Mittag ist damit überholt; seine zwei offenen Fragen stehen unten unverändert.

## Wo das Vorhaben steht

Die Datenseite bewegt sich, die Codeseite steht: Von vier gestarteten Paketen liegen zwei
Befunde vor (0005 Lizenz, 0007 Adressverzeichnis — letzteres schon mit `urteil: geprueft`),
0006 hat gemessen, aber seinen Status nicht gewechselt, und das einzige Codepaket 0004 hat
nichts hinterlassen. Das Vorhaben weiß seit heute zwei Dinge, die es gestern nicht wusste:
**Reihe 13 (Zollniveau) ist lizenzrechtlich gesperrt** — damit tritt T26 Fall 1 ein, zwei
statt drei verankerte Instrumente im Rückvergleich — und **der Prüfjahrgang 1997–2021
trägt nicht**: R = 19 statt 24, und die Leitzinsreihe für Deutschland und China hat in der
vorgesehenen Quelle keinen einzigen Wert. Beide Antworten fallen gegen den Entwurf aus,
keine kippt ihn — genau dafür waren die zwei Datenpakete vorgezogen worden.

## Der Engpass

**Paket 0004 — Werkstattgerüst und Festkomma.** Nicht mehr 0002: 0002 hängt an 0008, 0008
hängt an 0004 und 0007, 0004 hängt an nichts. Die ganze Codeseite steht dahinter.

Sein erster Versuch hat **keine Spur hinterlassen** — keine `Cargo.toml`, keine `.rs`-Datei,
kein Eintrag in `notizen/kernbauer.md` (unverändert die Vorlage), Status weiter `offen`.
Was es gibt, ist ein Commit unter seinem Namen (`a629f73 kernbauer: 0004-…​ (2 Dateien)`),
der ausschließlich Dateien des Datenbauers enthält: Jeder Bauagent committet ganz
`ventures/`, also signiert der leere Lauf fremde Arbeit. Warum er leer blieb, steht im
Journal (`state.db`), nicht im Repo — `ops/auslastung.md` ist vom 2026-08-30 und schweigt
dazu; `python3 agents/auslastung.py` beantwortet es für null Tokens.

Und die Terminfolge, falls 0004 heute Nacht gelingt: Prüfer im selben Lauf, `fertig` erst
zu Beginn des nächsten, dann 0008, dann 0002. **Drei Baulaufe, wenn nichts zurückkommt.**

## Was quer liegt

- **0006 hat gemessen und steht trotzdem auf `offen`.** Der Befund ist da und erfüllt sein
  Abnahmekriterium (ein Wert für R, die erzwingenden Reihen benannt). Folge des fehlenden
  Statuswechsels: Heute Nacht plant `startbereit()` das Paket erneut ein — rund vierzig
  Abrufe ein zweites Mal —, und ein Prüfer sieht es nie, weil Review `gebaut` verlangt.
  Billigster Weg: Der Projektmanager setzt es zu Beginn des nächsten Laufs auf `gebaut`.
- **Das Ergebnis von 0006 verlangt den Spielentwerfer, und der läuft im Baulauf nicht.**
  T24 lässt für eine leere Reihe nur zwei Auswege — streichen oder Quelle ersetzen —, und
  beide gehören ihm. Dieselbe Rolle schuldet nach `rueckstand.md` auch die Rechenvorschrift
  für „Schaden" in Gegenkraft 5. Zwei offene Entwurfsfragen, eine Rolle, kein Lauf.
- **Diese Entscheidung berührt bereits abgenommene Arbeit.** `daten/adressen.md` führt
  30 Leitzins-Adressen. Fällt Reihe 9, ändert sich das Verzeichnis, das gerade geprüft
  wurde. Heute kostet das eine Nacharbeit; sobald 0008 die 310 Felder getippt hat, zwei.
- **0005 ist `gebaut` und hat keinen Prüfbefund.** Der Baulauf plant für jedes gebaute
  Paket einen Prüfer seines Gewerks ein; entstanden ist nur `pruefung-0007-…`. Nebeneffekt
  derselben Gleichzeitigkeit: Drei Datenbauer teilen ein Logbuch, und die Lehren aus 0006
  — vor allem der neue IWF-Zugang über `api.imf.org` — stehen nicht darin, nur im Befund.
- **Die Prämisse „kein Agent hat eine Shell" hält nicht.** `rueckstand.md` leitet daraus
  jedes Abnahmekriterium des Vorhabens ab. Der Datenprüfer hat am selben Tag
  `grep | sort | uniq -c`-Pipelines ausgeführt und notiert, was ihm verweigert wurde (`cd`,
  Heredoc, `python3 -c`). Die Folgerung — Abnahme muss mit `Read` und `Grep` prüfbar sein —
  bleibt richtig, ihre Begründung nicht, und ob ein Übersetzungslauf möglich wäre, ist
  damit ungemessen statt beantwortet.
- **Unbeantwortet aus dem Vormittagsplan:** Rücklaufgrenze im Bau (Empfehlung B) und der
  Auslöser für die 170-gegen-121-Lücke (Empfehlung: erster bestandener Rückvergleich). Der
  Projektmanager führt den Zähler „Rückläufe" seit heute in jedem Paket mit; die Grenze
  selbst gibt es nicht.

## Was der Betreiber entscheiden muss

**1. Wer entscheidet über Reihe 9 und R?** Reihe 13 braucht keine Entscheidung — T26 nennt
den Fall und die Folge. Reihe 9 braucht eine, und ohne sie ist R nach dem Wortlaut der
Spezifikation überhaupt nicht messbar.

- *A:* Den Spielentwerfer einmal von Hand laufen lassen
  (`python3 agents/lauf.py spielentwerfer 0016-hedgefonds-simulation-echte-weltwirtschaft`),
  mit beiden offenen Fragen zugleich — Reihe 9 samt R und „Schaden". Er ändert `specs/`,
  was `spiel.md` für genau diesen Fall selbst vorsieht: „Misst der Jahrgangsbau ein engeres
  Fenster, ist R zu ersetzen und sonst nichts."
- *B:* Selbst entscheiden. Der Befund legt die Zahlen nebeneinander: Reihe 9 streichen →
  27 Sollreihen, R = 20; Quelle ergänzen → R = 19. Kostet zehn Minuten Lesen, keinen Lauf,
  löst „Schaden" aber nicht mit.
- *C:* Vertagen bis zum Jahrgangsbau. Heute billig, teuer ab dem Moment, in dem 0008 die
  310 Felder getippt hat.

**Empfehlung: A.** Es sind seine zwei Fragen, ein Lauf erledigt beide, und die Entscheidung
kostet Sie nur den Start, nicht das Lesen. Zwei Wochen später ist sie dreimal so teuer.

**2. Soll ein leerer Lauf sichtbar werden?** Heute sind zwei Aufträge ohne Ergebnis
geblieben (0004 und der Prüfer zu 0005), und beide fallen durch jede Zählung — nach der
0-Byte-Prüfung der Runde 5 der dritte Fall desselben Musters.

- *A:* Nichts tun. Das Paket wird ohnehin neu eingeplant — nur unbemerkt beliebig oft.
- *B:* `baulauf.py` meldet am Ende jeder Phase, welche Aufträge ohne Datei endeten, und
  schreibt es in diesen Plan. `lauf.py` kennt die Zahl schon (`frisch_geschrieben`).
- *C:* Zusätzlich zählen: zweiter leerer Lauf → `blockiert`. Das ist die Rücklaufgrenze aus
  dem Vormittagsplan, erweitert auf den leeren Lauf.

**Empfehlung: B jetzt, C gemeinsam mit der noch offenen Rücklaufgrenze.** Ein Lauf, der
nichts hinterlässt, ist teurer als einer, der etwas Falsches hinterlässt: Der zweite wird
geprüft.

## Die eine Zahl

**0 Zeilen Code — unverändert seit dem Vormittagsplan**, nach einem Baulauf mit vier
Bauagenten. Sie ersetzt sich erst, wenn der Kern rechnet, durch die Abnahme des
Rückvergleichs: **16 Prüfgegenstände, höchstens 2 dürfen reißen** (T37).
