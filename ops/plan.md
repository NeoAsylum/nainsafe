# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02, nach dem zweiten Baulauf (03:13–03:31). Der Plan vom 2026-09-01 ist
damit überholt; was aus ihm offen blieb, steht unten.

## Wo das Vorhaben steht

Das Vorhaben hat Code, und der Code übersetzt: 619 Zeilen C++ im Kern, dazu `cmake`,
`cmake --build` und `ctest` alle drei grün (`befunde/uebersetzung-2026-09-02.md`,
maschinell erzeugt — kein Modell hat das behauptet). Damit ist die Prämisse widerlegt,
auf der `rueckstand.md` **jedes** Abnahmekriterium dieses Vorhabens aufbaut: „Es gibt
keinen Übersetzer." Beide Datenpakete sind seit heute Nacht geprüft (0005 und 0007, je
`urteil: geprueft` mit zwei Befunden), und der Stack steht auf C++ (ADR 0011).

## Der Engpass

**Vier von fünf Agentenläufen dieser Nacht haben ihre Schlussarbeit nicht getan.** Der
Kernbauer hat 619 Zeilen geschrieben und danach weder den Status seines Pakets auf
`gebaut` gesetzt noch sein Logbuch ergänzt (`grep -c 2026-09-02 notizen/kernbauer.md`
→ 0). Dasselbe beim Datenbauer — `parameter.toml` liegt mit 763 Zeilen da und trägt im
Kopf Paket 0009 vom 2026-09-02, Status weiter `offen`. Und beim Projektmanager, der als
Erster läuft und gar nichts geschrieben hat. Nur der Daten-Prüfer ist bis zum Ende
gekommen.

Das ist **kein leerer Lauf** — die Arbeit ist da und sie ist gut. Es ist ein
abgeschnittener, und der Unterschied ist teuer: `ops/auslastung.md` zählt solche Läufe
als „ergiebig". Die Spalte „leer" ist gegen dieses Muster blind.

Vier Folgen, alle jetzt wirksam:

- **Der erste Code des Vorhabens wird nie geprüft.** Review verlangt `gebaut`, 0004 steht
  auf `offen`. `notizen/kern-pruefer.md` ist noch Zeichen für Zeichen die Vorlage — die
  Rolle hat in diesem Vorhaben nie gelaufen.
- **0008 und 0002 bleiben blockiert.** Beide hängen an 0004, und 0004 ist formal offen.
- **0006 wurde ein zweites Mal eingeplant** und hat wieder nichts hinterlassen; sein
  Befund ist unverändert vom 2026-09-01, sein Commit trägt fremde Dateien.
- **0007 müsste `fertig` sein.** Der Prüfbefund vom 2026-09-01 trägt `geprueft`, und den
  Status setzt allein der Projektmanager.

## Was quer liegt

- **`specs/` sagt Rust, gebaut wird C++.** `technik.md` nennt Rust an zehn Stellen. Paket
  0011 fasst T1/T2 neu — Rolle `architekt`, und `BAUROLLEN` in `baulauf.py` kennt
  `architekt` nicht. **Kein Baulauf kann dieses Paket einplanen.** Es liegt, bis es von
  Hand läuft.
- **Dieselbe Lücke in den Paketen selbst.** 0002, 0003, 0008 und 0010 nennen im Feld
  `dateien` `.rs`-Dateien; 0004s Abnahme prüft `lib.rs` auf `forbid(unsafe_code)`. Der
  Kernbauer hat richtig gegen ADR 0011 gebaut und damit gegen sein eigenes Paket. Ein
  Kern-Prüfer, der „gegen diese Liste und gegen nichts sonst" urteilt, müsste 0004 an
  einem Dateinamen scheitern lassen.
- **Zwei Entwurfsfragen aus dem letzten Plan sind unbeantwortet:** Reihe 9 samt R, und die
  Rechenvorschrift für „Schaden" (Gegenkraft 5). Beide gehören dem Spielentwerfer, der
  wie der Architekt im Baulauf nicht vorkommt. `spiel.md` ist seit dem 2026-09-01
  unverändert.
- **0003 steht seit dem 2026-09-01 auf `blockiert`**, niemand hat es angefasst. Der
  Sachbefund dahinter ist behoben (T47/T50); überholt ist nur der Wortlaut des Pakets.
- **Erledigt und hiermit vom Tisch:** Übersetzungslauf (läuft, grün) und Rücklaufgrenze
  (`RUECKLAUF_MAX = 3`). Beide waren offene Fragen des letzten Plans.

## Was der Betreiber entscheiden muss

**1. Wie kommen die drei Entwurfsaufgaben in einen Lauf?** Architekt und Spielentwerfer
stehen in `REVIEW`, aber nicht in `BAUROLLEN`. Daran hängen: der Stackwechsel in
`technik.md` (0011), Reihe 9 mit R, und „Schaden".

- *A:* `BAUROLLEN` um `architekt` und `spielentwerfer` erweitern — eine Zeile in
  `baulauf.py`. Ab dem nächsten Lauf planen Entwurfspakete sich selbst ein.
- *B:* Von Hand starten, drei Läufe:
  `python3 agents/lauf.py architekt 0016-hedgefonds-simulation-echte-weltwirtschaft`,
  zweimal dasselbe mit `spielentwerfer`.
- *C:* Vertagen. Kostet ab sofort jeden Baulauf, denn 0011 ist die Voraussetzung dafür,
  dass die Abnahmekriterien der Codepakete auf den gebauten Code überhaupt passen.

**Empfehlung: A, und 0011 als erstes.** Die Rollen sind entworfen, ihre Prüfer sind schon
zugeordnet — dass der Baulauf sie nicht kennt, ist eine Lücke im Skript, keine Absicht.
B löst dieselbe Sache dreimal und lässt die Lücke stehen.

**2. Soll der Statuswechsel dem Agenten aus der Hand genommen werden?** Heute Nacht haben
ihn alle drei Bauagenten vergessen, im Baulauf davor einer von dreien.

- *A:* Nichts tun, der Projektmanager zieht nach. Er ist heute Nacht selbst leer gelaufen.
- *B:* `baulauf.py` setzt nach der Bauphase mechanisch `gebaut`, wenn die im Feld
  `dateien` genannten Dateien existieren und nicht leer sind. Null Tokens, immer dieselbe
  Antwort — dieselbe Bauart wie `auslastung.py`.
- *C:* Zusätzlich melden, welcher Lauf ohne Statuswechsel endete. Das ist das Gegenstück
  zur Spalte „leer", die dieses Muster nicht sieht.

**Empfehlung: B und C — aber nach 0011, nicht davor.** B liest das Feld `dateien`, und
genau dieses Feld nennt in fünf Paketen noch Rust-Namen. Heute gezogen, setzt B keinen
einzigen Status und sähe dabei aus, als funktioniere es.

## Die eine Zahl

**6 von 9 Kernkästen sind leer.** Inhalt haben `festkomma`, `kern` und `sperre`;
`pruefsumme`, `schreiber`, `schritt`, `werte`, `zufall` und `zustand` sind
Zwei-Zeilen-Platzhalter. Auftragsgemäß — aber sie sind der Weg zum ersten Weltschritt.
Abgelöst wird diese Zahl vom Rückvergleich: 16 Prüfgegenstände, höchstens 2 dürfen
reißen (T37).
