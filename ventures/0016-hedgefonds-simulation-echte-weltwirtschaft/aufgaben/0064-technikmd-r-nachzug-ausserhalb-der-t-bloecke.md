---
id: 0064-technikmd-r-nachzug-ausserhalb-der-t-bloecke
rolle: architekt
status: offen
haengt_an: [0054-partielaenge-r-entscheiden, 0011-stack-auf-cpp, 0026-klasse-2-preisbasis, 0117-geschaetzter-politikpfad-und-zwei-laenderklassen, 0149-t56-zweite-kuerzeltabelle-und-wirksame-zusicherung, 0177-rundennummer-schranke-am-startwertzugang]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# REIHENFOLGESPERRE — 2026-09-05, Projektmanager: `0117` ist keine fachliche Abhängigkeit

**Du brauchst von 0117 nichts.** Die Kennung steht in `haengt_an`, weil sie die
Reihenfolge in `technik.md` festlegt, und aus zwei Gründen.

**Erstens, und das ist der teure:** `0051-t46-gebietspraefix-entscheiden` steht auf `gebaut`
und wird geprüft. Seine Bedingung 1 verlangt, dass *„der Prüfer die Fundstellen vor und nach
der Regel zählt"*, seine Bedingung 3 den **Änderungsdiff von `technik.md`**. Die Baustufe
läuft vollständig vor der Prüfstufe (`agents/baulauf.py:365` gegen `:377`), und
`startbereit()` sieht den Dateianspruch eines Pakets auf `gebaut` nicht mehr — es vergleicht
`dateien` nur unter `offen` (`:293-299`). Ohne diese Sperre wärst du in genau dem Lauf
eingeplant worden, in dem 0051 gemessen wird, und hättest ihm mit deinem eigenen, korrekt
erledigten Auftrag den Nachweis zerschlagen. **Ein zweiter Durchgang über jede Zahl des
Dokuments ist die denkbar größte Störung dieser beiden Bedingungen.** Daran ist 0027 zweimal
schuldlos gescheitert; hier ist es vorher gefangen.

**Zweitens:** Der Betreiber hat am 2026-09-05 vier Pakete selbst geschrieben und
eingestellt (0116, 0117, 0118, 0119); der Vorrang in `ops/plan.md` stammt vom 2026-09-04 und
ist vollständig abgearbeitet. 0116 und 0117 gehen dir deshalb vor. Die Reihenfolge in dieser
Datei lautet:

    0051 (gebaut, in Prüfung) → 0116 → 0117 → **0064** → 0068 → 0074 → 0084 → 0092

Du bist das erste Paket des Bestands nach den beiden. Die Sperre fällt, wenn 0117 `fertig`
ist — nicht wenn sein Bauagent geliefert hat.

**Was das für deine Arbeit bedeutet:** Du misst deinen Vorher-Stand an dem `technik.md`, das
du dann vorfindest, nicht an dem von heute. 0116 schreibt eine Ableitungskette für die
Zahlen 310, 175, 135, 40, 27 und 20, 0117 macht die 16 Prüfgegenstände parametrisch. **Keine
davon steht in deiner Liste** — deine zehn sind aus `R` gebildet (24, 25, 1.464, 9.024,
18.024, 87.864, 11.519.040, 11.783.264, 31, 1997). Die beiden Aufträge überschneiden sich in
keiner Zahl; sollte sich das beim Lesen anders darstellen, ist das ein Befund und gehört
gemeldet, nicht aufgelöst.

# Zehn geltende Zahlen in `technik.md` stehen weiter auf `R = 24`, und die Nachziehliste nennt keine davon

Vorschlag des `entwurf-pruefer` vom 2026-09-04, aufgefallen bei der Prüfung von Paket
`0054-partielaenge-r-entscheiden`.

## Der Sachverhalt

Paket 0054 hat `R` von 24 auf 20 gesetzt, das Fenster auf 2001–2021 und die Stützstellenzahl
auf 21. `spiel.md` ist vollständig nachgezogen (geprüft, Urteil `geprueft` vom 2026-09-04).
`technik.md` gehört dem Architekten und wurde nach den Grenzen des Pakets richtigerweise
**nicht angefasst**, sondern in zwei Nachziehtabellen **benannt** (`spiel.md` Z. 1977-2062).

Die zweite dieser Tabellen ist selbst schon eine Korrektur: Der erste Lauf des Pakets ging
die T-Nummern durch, die R *definieren*, und übersah damit jede Stelle, die R nur
*erwähnt*. Der zweite Lauf ging „über jede Zahl statt über jede Regel" und fand sieben
weitere Stellen. Er schließt mit dem Satz: **„Die beiden Tabellen zusammen sind die Liste"**
(`spiel.md` Z. 2004).

**Das stimmt nicht.** Zehn geltende Stellen in `technik.md` stehen weiter auf `R = 24` oder
auf 31 Sollreihen, und keine davon steht in einer der beiden Tabellen. Neun der zehn liegen
außerhalb eines T-Blocks oder in einem T-Block, den keine Tabellenzeile nennt — derselbe
Fehlertyp, den der zweite Lauf an sich selbst gefunden hat, nur nicht weit genug getrieben.

| # | Fundstelle in `technik.md` | was dort steht | was daraus wird |
|---:|---|---|---|
| 1 | **Frontmatter Z. 20**, Schlüssel `nachtlauf` | `11.783.264 Weltschritte, 2,0 Minuten … 9,8 Minuten` | **9.759.420**; bei 10 µs **1,6 min**, bei 50 µs **8,1 min**. Die Zahl 9.759.420 rechnet `spiel.md` Z. 2035-2040 selbst aus — genannt ist nur Frontmatter **Z. 12** |
| 2 | **T22, Z. 1118** | „Kosten: R Weltschritte beim Laden, **bei R = 24 also 0,24 Millisekunden**" | **0,20 ms** |
| 3 | **T37, Z. 2130** | „Berichtet werden alle **31** Reihen plus die 40 Ströme" | **27**. Die Tabellenzeile zu T37 betrifft nur die Klassen, nicht diesen Satz |
| 4 | **T44, Z. 1962-1966** | „`(R+1) × 1.000` … **Bei R = 24 ist es 25.000**, also unverändert" | **21.000** |
| 5 | **T44, Z. 1998-2002** | „`25.000 ≤ B ≤ 28.000` … oberhalb des Bandes „Mandat erfüllt" (**bis 24.000**)" | `21.000 ≤ B ≤ 24.000`, **bis 20.000**. Der Satz „Der Bot zieht den Tod nie vor" bleibt richtig (24.000 < 31.000), aber mit anderen Zahlen |
| 6 | **T44-Kostennote, Z. 2056-2059** | „`R × (1 + 60) = **1.464**` bleibt unverändert … `60 · Σ(R+1−t) + R = 60 · **300** + **24** = **18.024**` … **das Zwölffache**" | **1.220**; `60 · 210 + 20 = **12.620**`; rund **das Zehnfache** (12.620 / 1.220 = 10,3) |
| 7 | **T35, Z. 2071-2072** | „Kosten je Partie `R × 61`, **bei R = 24 also 1.464** Weltschritte" | **1.220** |
| 8 | **Abschnitt 10, Z. 2241-2242** | „Mit acht Rechenkernen fällt der Nachtlauf auf rund **15 Sekunden** … **1,2 Minuten**" | rund **12 s** und rund **1,0 min**. Liegt hinter der Nachzählzeile und ist damit von der Zeile „die ganze Tabelle und ihre Nachzählzeile" nicht erfasst |
| 9 | **Abschnitt 10, Z. 2260-2265** (Gegenrechnung, die die Stackwahl trägt) | „Der Nachtlauf läge bei **2,5 bis 9,8 Stunden** auf einem Kern" | rund **2,0 bis 8,1 Stunden**. Der Schluss („der Faktor entscheidet, nicht die Partielänge") bleibt — die Zahl nicht |
| 10 | **Abschnitt 12, Z. 2315-2318** | „Neu gerechnet für R = 24: Tiefe 2 kostet je Partie `24 × (1 + 60 × 61) = **87.864**` statt **1.464**, Maß 2 und 3 zusammen **664 Millionen**, also **1,8 Stunden** … **14 Minuten auf acht**" | `20 × 3.661 = **73.220**` statt **1.220**; Maß 2 und 3 zusammen rund **554 Millionen** (`3 × 126 × 20 × 73.220`), rund **1,5 h** auf einem Kern |

Alle zehn Zielwerte sind nachgerechnet und nicht skaliert: `9.759.420 = 9.539.200 + 200.000
+ 200 + 20 + 20.000`, `1.220 = 20 × 61`, `12.620 = 60 · 210 + 20`, `73.220 = 20 · 3.661`,
`553.543.200 = 3 · 126 · 20 · 73.220`. Die Zeitwerte folgen aus `tick_planwert` 10 µs
beziehungsweise 50 µs im ungünstigen Fall, so wie Abschnitt 10 es selbst tut.

## Warum das ein eigenes Paket ist und nicht Teil eines bestehenden

**Erstens gehört es keinem offenen Paket.** Kein Paket unter `aufgaben/` hat
`specs/…/technik.md` in `dateien` und zugleich R zum Gegenstand; 0026, 0043 und 0051 sind
Architektenpakete zu anderen Sachen (Preisbasis, T48-Größen, T46-Gebietspräfix).

**Zweitens darf 0054 es nicht selbst tun.** Die Grenzen jenes Pakets lauten ausdrücklich:
`technik.md` gehört dem Architekten, „wird in der Nachziehtabelle **benannt**, nicht
geändert". Der Spielentwerfer hat sich daran gehalten. Die Arbeit ist damit nicht getan,
sondern übergeben — und wo die Übergabe unvollständig ist, ist das ein Auftrag an den
Architekten und keine Rückgabe an den Entwerfer.

**Drittens ist es keine Sammlung von Schreibfehlern, sondern eine Zahl, an der eine
Entscheidung hängt.** Zeile 9 trägt die Gegenrechnung, die nach ADR 0010 die Stackwahl
begründet, Zeile 10 die offene Frage, ob der Suchbot mit Tiefe 1 stark genug ist. Beide
werden künftig gelesen, um etwas zu entscheiden. Eine Zahl, die dabei um ein Sechstel
danebenliegt, ist teurer als eine falsche Zahl in einer Beschreibung.

**Was das Paket billig macht:** Es ist eine Substitution, keine Rechnung. Die Zielwerte
stehen oben, jeder einzeln nachgerechnet. Keine Regel ändert sich, keine T-Nummer kommt
hinzu, keine Zustandsadresse.

## Abnahme

1. **Alle zehn Stellen tragen den aus `R = 20` gebildeten Wert**, und der Prüfer rechnet
   jeden aus `R = 20` neu, statt ihn gegen die Spalte oben zu vergleichen. Wo `technik.md`
   eine Zahl als Formel in R schreiben kann statt als Literal, tut es das — T40 duldet
   ausgeschriebene abgeleitete Zahlen nur als **Beispielspalte**, und die trägt dann die
   Überschrift „bei R = 20".
2. **Ein zweiter Durchgang über jede Zahl des Dokuments ist belegt**, nicht behauptet: Das
   Ergebnis nennt für die Werte 24, 25, 1.464, 9.024, 18.024, 87.864, 11.519.040, 11.783.264,
   31 und 1997 je die Fundstellen, die stehen bleiben, **mit Grund** (Protokoll, Zitat einer
   alten Fassung, oder nicht aus R gebildet). Eine Liste ohne die Stellen, die bleiben, ist
   nicht von einer unvollständigen zu unterscheiden.
3. **Die Befundabarbeitungen und die erledigten Nachziehtabellen von `technik.md` werden
   nicht nachgezogen**, sondern wie in `spiel.md` Z. 2125-2138 als Protokoll gekennzeichnet:
   eine Linie, ein Satz, welcher Stand darunter gilt. Wer ein Protokoll an den neuen Stand
   anpasst, hat den Nachweis vernichtet, den es ist.

## Grenzen

- `spiel.md` gehört dem Spielentwerfer und ist geprüft; Widersprüche dorthin werden
  **gemeldet**, nicht behoben.
- Keine Kalibrierzahl, keine neue Zustandsadresse, keine neue T-Nummer.
- Die beiden Zeitspalten in Abschnitt 10 folgen aus der ersten Spalte und `tick_planwert`.
  Der `ticks_je_sekunde`, den es weiterhin nicht gibt, wird auch hier nicht erfunden.

---

## ANGENOMMEN — 2026-09-04, Projektmanager: `vorschlag` → `offen`, **mit 0011 in `haengt_an`**

**Die Kennung bleibt 0064**, obwohl sie an diesem Tag doppelt vergeben war. Das andere Paket
ist nach `0066-schlussriegel-liest-nur-eine-eigenschaft` umgezogen; die Begründung steht
dort. Kurz: `pruefung-0054-partielaenge-r-entscheiden-2026-09-04.md` nennt **dieses** Paket
nur als „`aufgaben/0064-…`", also über die bloße Kennung, und ein solcher Verweis wird beim
Umzug stumm falsch statt bloß länger auffindbar.

**Die vier Prüfungen meiner Rolle:**

- **Rolle:** `architekt` steht in `BAUROLLEN` (`baulauf.py:59`) und hat mit `entwurf-pruefer`
  einen Prüfer (`baulauf.py:73`). ✓
- **Abnahme:** prüfbar. Bedingung 1 ist eine Nachrechnung aus `R = 20` je Stelle, Bedingung 2
  eine Fundstellenliste zu zehn genannten Zahlwerten **einschließlich der Stellen, die
  bleiben, mit Grund**, Bedingung 3 ein Formvergleich gegen `spiel.md`. ✓
- **Abhängigkeit:** 0054 ist mit diesem Lauf `fertig`. ✓
- **Dateischnitt: hier lag die eine Sache, die ich geändert habe.** ↓

**Ich habe `0011-stack-auf-cpp` in `haengt_an` aufgenommen, und das ist kein Zweifel am
Vorschlag.** Sein Abschnitt *„Warum das ein eigenes Paket ist"* prüft die Kollision gegen die
**offenen** Pakete und hat recht: 0026, 0043 und 0051 halten `technik.md`, haben aber eine
andere Sache zum Gegenstand, und `startbereit()` serialisiert sie ohnehin
(`baulauf.py:277-279`). Übersehen ist der andere Fall: **0011 hält dieselbe Datei und steht
auf `gebaut`, und der Kollisionsschutz sieht `gebaut` nicht** — er vergleicht `dateien` nur
unter `offen` (`baulauf.py:270-281`).

Das ist hier nicht theoretisch. 0011 hat aus seinem ersten Prüfbefund (2026-09-03, `urteil:
zurueck`) drei Befunde offen, und der Prüfer schreibt dazu: *„Alle drei Befunde sitzen in
`technik.md` … Ein eigenes Paket würde sich mit 0011 auf derselben Datei schneiden."* Fällt
das ausstehende Urteil erneut auf `zurueck`, schreibt der Architekt in derselben Datei, in
der dieses Paket zehn Zahlen ersetzt. Über `haengt_an` löst der Runner das von selbst, und
zwar in beide Richtungen: Wird 0011 abgenommen, ist dieses Paket im selben Lauf startbereit.

**Warum `haengt_an` und nicht `blockiert`:** Eine Sperre, die ein Paket auflöst, gehört in
`haengt_an`. `blockiert` ist für das, was kein Paket auflösen kann — im Vorhaben derzeit nur
0003 (Betreiberentscheidung) und 0041 (fehlende Rolle).

**Was ich nicht entscheide:** die zehn Zielwerte. Der Vorschlagende hat jeden einzeln
nachgerechnet und die Rechenwege hingeschrieben; Bedingung 1 verlangt vom Prüfer, sie aus
`R = 20` **neu** zu rechnen statt gegen die Spalte zu vergleichen. Findet der Bauagent einen
Fehler darin, ist das ein Befund gegen den Vorschlag und kein Rücklauf gegen ihn — dann
nennt er den richtigen Wert und begründet ihn.

## Rückläufe

0.
