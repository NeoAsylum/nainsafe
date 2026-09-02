---
id: 0002-fondsbewertung-definieren
rolle: kernbauer
status: blockiert
haengt_an: [0008-kern-zustand-310-felder]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/include/kern/werte.hpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/werte.cpp, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/werte_probe.cpp]
abnahme: Die öffentliche Schnittstelle von kern::werte ist Name für Name die Tabelle der siebzehn Größen aus T48; die drei Skalenübergänge aus T50 sind privat und haben genau die dort genannten Aufruforte; ein Test rechnet die Zahlenprobe aus T47 nach und nennt 4.200.000.000.000 Cent.
---

# `kern::werte` — die siebzehn abgeleiteten Größen

**Neu gefasst am 2026-09-01. Der alte Wortlaut steht unten und ist überholt** — er sagt
„Der Entwurf gibt es nicht her; entscheide es". Seit `spiel.md` Fassung 5 und
`technik.md` T47/T48/T50 gibt der Entwurf es her: alle sieben Bewertungsfunktionen, die
Skalengrenze, die Reihenfolge der Rundungen und eine durchgerechnete Zahlenprobe. Ein
Kernbauer, der noch selbst entschiede, wiche von `specs/` ab — was seine eigene Rolle
verbietet.

Vorher lesen: `technik.md` T47, T48, T50, T5, T13, T33, T39; ADR 0011.

**Nachgezogen am 2026-09-02, Projektmanager:** C++20 statt Rust (ADR 0011) — das Modul
sind die drei Dateien im Feld `dateien`, „öffentlich" heisst „im Kopf `werte.hpp`
deklariert", „privat" heisst „nur in `werte.cpp`, ohne Deklaration im Kopf". Und
`haengt_an` nennt nur noch 0008: 0004 ist gebaut und übersetzt grün, die Werte hängen am
`Zustand` und nicht am Gerüst.

## Was du baust

Das Modul `kern::werte`, und sein Schnitt ist eine **Vorgabe und keine Geschmacksfrage**
(T13): Dort und nur dort stehen die abgeleiteten Größen aus T48 und die drei
Skalenübergänge aus T50.

1. **Die siebzehn Funktionen aus der Tabelle in T48**, in genau dieser Menge — `wert`,
   `korbwert`, `anleihewert`, `waehrungswert`, `markt`, `stufenwert`, `marktkorb`,
   `korbbestand`, `bip`, `schuld`, `handelsvolumen`, `anleihekurs`, `landespreis`,
   `fondsanteil`, `positionswert`, `beteiligung_wert`, `fondsvermoegen`. Die Formeln
   stehen ausgeschrieben in T47 und T48; schreib sie ab, statt sie neu zu bilden.
2. **`tsd_in_cent`, `lobbypunkte_aus_geld`, `lobbypunkte_aus_schaden` als private
   Funktionen** dieses Moduls (T50). `cent_in_tsd` gibt es nicht — sie hat keinen
   Aufrufer, und eine Umrechnung ohne Aufrufer ist eine stehende Einladung.
3. **Vier Vorgaben, die das Ergebnis ändern und deshalb wörtlich zu nehmen sind:**
   - Die Reihenfolge der Rundungen: verbindlich ist `stufen(p) · stufenwert(p)`, nicht
     die genauere zweite Form. Wer sie will, braucht einen ADR (T47).
   - `positionswert` bricht bei `stufen(p) = 0` ab, **bevor** `markt(p)` gerechnet wird.
   - `korbwert(l, s)` wird je Aufruf von `fondsvermoegen` **einmal** in ein Feld von
     zwölf gerechnet und daraus gelesen — nicht um Zeit zu sparen, sondern damit „eine
     Bewertung, nicht zwei" eine Eigenschaft des Codes ist und nicht ein Satz.
   - Beide Summen laufen über die Indexordnung aus T9, nie über eine Menge.
4. **`handelsvolumen(l)` liest beide Richtungen je Paar**, und die Zuordnung des dichten
   Gegenüber-Index zum Gebietsindex steht als **benannte Tabelle**, nicht als Rechnung
   auf Indizes (T48).
5. **Die zwei Wertebereichsschranken** (T47): `wechselkurs[g] ≥ 1` als Invariante — ein
   negativer Nenner drehte das Vorzeichen jeder Bewertung, ohne dass etwas abbräche —,
   und `tsd_in_cent` als die einzige Stelle, an der ein `i64` überlaufen kann.

## Abnahme

1. Die Deklarationen in `kern/include/kern/werte.hpp` sind **genau die siebzehn Namen
   aus T48**, keiner mehr und keiner weniger. Das ist der mechanische Nachweis, den T13
   und T48 ausdrücklich für dieses Modul vorsehen — in Rust wäre es
   `grep -n 'pub fn' werte.rs`, in C++ ist es der Kopf, weil dort und nur dort steht,
   was das Modul nach aussen anbietet.
2. `grep -rn 'tsd_in_cent\|lobbypunkte_aus' kern/` liefert Treffer **nur in dieser
   Datei** (T50). `tsd_in_cent` hat genau die zwei Aufruforte aus T50: den äussersten
   Aufruf von `positionswert` und den von `beteiligung_wert`.
3. `grep -n 'cent_in_tsd' kern/` liefert nichts.
4. **Die Zahlenprobe aus T47 steht als Test in der Datei, mit ausgeschriebenem
   Erwartungswert:** Korb `21_000_000_000` Tausend USD, `anteil = 20`,
   `ausstiegsabschlag = 0` ergibt innen `42_000_000` Tausend USD und nach `tsd_in_cent`
   **`4_200_000_000_000` Cent**. Der Prüfer rechnet sie von Hand nach.
5. Jede der siebzehn Formeln stimmt Zeichen für Zeichen mit T47 beziehungsweise T48
   überein. Weicht eine ab, ist das ein Befund, auch wenn sie richtiger wäre.
6. Kein Gleitkomma (T4), keine Fremdabhängigkeit (T2), keine Division ausser über
   `festkomma` (T6).

## Warum das der Engpass ist

`fondsvermoegen` hat fünf Leser (T47 Punkt 3): Abrechnung, Mandatsprüfung, Todesart 1,
Invariantentest und `v(z)` in T44. Über `v(z)` hängen Maß 1, 2 und 3 daran, über
denselben Marktkorb zusätzlich Gegenkraft 3. Solange dieses Modul fehlt, ist Schritt 6
der Schleife nicht schreibbar.

## Rückläufe

0.

## Status

**2026-09-02, Projektmanager: `offen` → `blockiert`.** Nicht wegen eines Fehlers im
Paket, sondern weil seine Vorgabe an genau der Stelle in Revision ist, die es abschreiben
soll.

**Der Sachverhalt** (Prüfbefund zu 0007 vom 2026-09-02, Befund 1; `ops/plan.md` vom
2026-09-02): T5 nennt Klasse 2 „Tausend USD zu **konstanten** Preisen des Basisjahrs". In
Klasse 2 liegen die 40 Handelsströme aus CEPII BACI — und BACI führt „thousands
**current** USD". Im selben Topf liegen die Wertschöpfungen aus Reihe 1 in konstanten
Preisen. Eine Deflationierung steht nirgends, und T50 zählt die Skalenübergänge
abschliessend auf; ein Preisbasiswechsel ist keiner davon.

**Warum das gerade dieses Paket trifft.** Abnahme 5 verlangt, dass jede der siebzehn
Formeln „Zeichen für Zeichen" mit T47 beziehungsweise T48 übereinstimmt, und Punkt 2
verlangt die drei Skalenübergänge aus T50. Die Auflösung der Klasse-2-Frage ändert nach
`ops/plan.md` T5, T49, T23 Punkt 5 und T8 — und wenn sie einen vierten Skalenübergang
braucht, ändert sie T50. Dann ändert sich mit ihr das Abnahmekriterium dieses Pakets,
nachdem es gebaut wurde. `fondsvermoegen` hat fünf Leser (T47 Punkt 3); Nacharbeit an
diesem Modul ist die teuerste im ganzen Kern.

**Ich löse den Widerspruch nicht auf** — Entwurf ist nicht meine Rolle, und der
Geschäftsführer hat die Frage in `ops/plan.md` bereits vorgelegt. Was ich tue, ist, kein
Bauwerk gegen eine Vorgabe einzuplanen, von der zwei Prüfbefunde und ein Plan sagen, dass
sie an dieser Stelle falsch ist.

**Was das Paket entblockt:** eine Entscheidung des Architekten zur Klasse-2-Frage,
schriftlich in `technik.md` oder in einem ADR. Danach `blockiert` → `offen`, ohne
Änderung an Umfang oder Abnahme, sofern T47, T48 und T50 unberührt bleiben — ändern sie
sich, ziehe ich Punkt 1 bis 3 und Abnahme 4 nach.

**Der kritische Pfad steht dadurch nicht still.** Nach 0008 ist der `Schreiber`
(0016-schreiber-ursachenkette, T18/T38/T39) der nächste Kernkasten; er hängt am `Zustand`
und nicht an den Werten. 0010 (Zustandsausgabe) hängt an diesem Paket und bleibt
mittelbar mit blockiert; das ist unvermeidbar und war schon vorher der Fall, weil es auf
0002 wartet.

---

## Der Wortlaut bis zum 2026-09-01

Aufbewahrt, weil die Ablehnungsbegründung wertvoller ist als der Speicherplatz
(Hausregel 3) — und weil er zeigt, wie schnell ein Paket veraltet, das zwischen zwei
Entwurfsfassungen geschrieben wurde.

> Aus Befund 1 der sechsten Entwurfsprüfung, Schwere hoch: `positionswert(p)` und
> `korbwert(l, s)` haben keine Entstehungsregel, und an ihnen hängt alles. […]
> **Was du entscheidest:** Wie ein Korb und eine Position bewertet werden — aus
> Weltpreis, Landespreis, Menge und Anteil. Der Entwurf gibt es nicht her; entscheide
> es, schreib die Regel in den Code und in einen Kommentar, und nenne die Einheit
> ausdrücklich. **Kein weiterer Prosaentwurf.**

Was seither geschah: Der Spielentwerfer hat in Fassung 5 alle sieben Namen gebildet, der
Architekt sie in T47 aufgenommen, in T48 abschliessend aufgezählt und die Skalengrenze
in T50 an einen Ort gebunden. Der Befund ist damit auf der Entwurfsseite behoben — was
bleibt, ist Bauarbeit, und das ist dieses Paket.
