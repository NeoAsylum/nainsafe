# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-02, nach dem sechsten Baulauf (06:39–07:24).

## Wo das Vorhaben steht

**Der Betreiber hat um 06:39 eingegriffen und den Engpass der letzten fünf Pläne
aufgemacht** (`953bbf5`): `architekt` und `spielentwerfer` stehen jetzt in `BAUROLLEN`,
dazu `einrichtung/rollen-pruefen.py` gegen die Wiederholung derselben Fehlerklasse. Der
Trockenlauf zieht damit zum ersten Mal ein Architektenpaket (0011). Der Lauf selbst hat
alle vier Bauplätze gefüllt — 0009, 0015, 0017, 0018 stehen auf `gebaut`, kein leerer
Bauplatz —, und 0008 wie 0017 haben `urteil: geprueft`, werden im nächsten Lauf also
`fertig`. Damit fallen `werte` (0002) und `schreiber` (0016) beide von selbst frei.

## Der Engpass

**`schritt` hat kein Arbeitspaket, und nach dem nächsten Lauf ist es der einzige leere
Kernkasten.** Der Grund steht seit dem 2026-09-02 im Logbuch des Projektmanagers
(Zeile 109): „Schaden" in Gegenkraft 5 (`technik.md` Abschnitt 12) hat keine
Rechenvorschrift. `grep -l schritt.hpp aufgaben/*.md` findet genau ein Paket — 0004, das
Werkstattgerüst, und das hat nur den Zweizeiler-Stub angelegt.

Die geöffnete Tür ändert daran nichts: Der Architekt ist jetzt einplanbar, sein
Rückstand enthält aber genau ein Paket (0011, Stackwechsel). Eine Frage ohne Paket zieht
kein Lauf — das ist derselbe Mechanismus wie gestern, nur eine Ebene höher: gestern
fehlte der Rolle der Runner, heute fehlt der Rolle die Aufgabe.

`schritt` ist die Runde. Ohne sie rechnet der Kern nie, gleich wie viele Datenpakete
durchgehen.

## Was quer liegt

- **Der Ausfall ist vom Bau- auf den Prüfplatz gewandert.** Alle vier Bauplätze
  lieferten; von vier Prüfungen sind zwei leer: 0015 hat **keine** Befunddatei und
  keinen Logbucheintrag, 0009 Runde 3 ist eine **0-Byte-Datei** (07:18). Das ist die
  dritte Messung meiner Fährte — das Muster „ein Platz je Lauf geht leer aus" gilt
  weiter, aber die Sorte Platz hat gewechselt und die Rate ist auf 2 von 4 gestiegen.
- **0009 steht bei zwei von drei Rückläufen.** Runde 1 und 2 `zurueck`, Runde 3 leer
  (zählt nicht mit, `rueckläufe()` liest `urteil`). Ein weiteres `zurueck`, und
  `baulauf.py:295` erklärt das Paket für festgefahren — dann fällt `parameter.toml` aus
  dem Betrieb und mit ihr die Schlüssel aus T27/T51. Einziges Paket in dieser Lage.
- **Der Trockenlauf zeigt weniger, als der Lauf tut.** Er plant zwei Baupakete; im echten
  Lauf hebt der Projektmanager erst 0008 und 0017 auf `fertig` (`baulauf.py:302`), lädt
  neu (306) — dann kommen 0016 und 0020 dazu. Wer nur den Trockenlauf liest,
  unterschätzt den nächsten Lauf um zwei Pakete. Korrektur an meiner eigenen Messmethode.
- **0003 (Einheiten) ist eine Betreiberfrage, keine Bausache.** Das Paket sagt es selbst:
  „entschieden wird es vom Betreiber, per ADR gegen T5 oder gar nicht." Blockiert derzeit
  nichts, gehört aber nicht als Rückstand gezählt.
- **`technik.md` sagt elfmal Rust, gebaut wird C++20** — erstmals beauftragbar, 0011 wird
  im nächsten Lauf gezogen. Erste Sache dieser Liste, die von selbst verschwindet.
- **`ops/kontingent.md` ist vom 2026-08-30** und kennt keinen einzigen Baulauf. Die
  aktuelle Zahl (162 von 400 $) steht nur in der Commit-Botschaft des Betreibers.
- **Vierter Fall der Fehlerklasse aus `953bbf5`, und diesmal in `CLAUDE.md` selbst:** Die
  Regel „Logbuch bei 12.000 Zeichen nach `notizen/archiv/` verschieben" kann keine Rolle
  ausführen — `mv`, `cp` und `Write` dorthin sind allen verwehrt. Mein Logbuch ist heute
  darauf gelaufen, der daten-pruefer meldet es seit dem 2026-09-02 (Zeile 130). Ich habe
  neu begonnen und auf `git show 9cb86d9:` verwiesen; nichts ist verloren, aber die Regel
  steht wieder an einer Stelle, die der Ablauf nicht erreicht. Kein Gate, keine Eile.

## Was der Betreiber entscheiden muss

Die Frage der letzten fünf Pläne ist beantwortet. Neu, und sie ist kleiner:

**Wer schreibt die Rechenvorschrift für „Schaden"?**

- *A:* Der Projektmanager legt ein Architektenpaket dafür an — Zerlegen ist seine Rolle,
  und er hat die Frage bereits im Logbuch, nur als Fährte statt als Paket. Kostet nichts
  und greift mit dem nächsten Lauf.
- *B:* Der Betreiber entscheidet sie selbst per ADR, wie bei 0003 vorgesehen.
- *C:* Nichts tun. Dann steht der Kern nach dem übernächsten Lauf wieder ohne Kernarbeit
  da — diesmal ohne dass eine Zeile im Runner hilft.

**Empfehlung: A, und ausdrücklich nicht B.** Das ist eine Entwurfsfrage aus `technik.md`,
kein Gate: kein Geld, kein Recht, keine Außenwirkung. Der Betreiber wird erst gebraucht,
wenn der Architekt meldet, der Entwurf gebe es nicht her. Falls dieser Plan überhaupt
einen Griff braucht, ist es ein Satz an den Projektmanager: *Für `schritt` fehlt ein
Paket.*

## Die eine Zahl

**Sechs von neun Kernkästen tragen Code — unverändert seit dem letzten Plan.** Dieser
Lauf hat keinen Kasten dazugebracht, und das war vorhergesagt: Es war kein Kernbauer
eingeplant, weil kein Kernpaket startbereit war. Die Vorhersage hat gehalten, die
Ursache ist behoben. Ab dem nächsten Lauf wird wieder Bauleistung gemessen, nicht
Freigabe.
