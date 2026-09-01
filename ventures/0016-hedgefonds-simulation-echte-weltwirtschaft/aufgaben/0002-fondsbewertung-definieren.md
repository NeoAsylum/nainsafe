---
id: 0002-fondsbewertung-definieren
rolle: kernbauer
status: offen
haengt_an: [0004-werkstattgeruest-festkomma, 0008-kern-zustand-310-felder]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/src/werte.rs]
abnahme: Die öffentliche Schnittstelle von kern::werte ist Name für Name die Tabelle der siebzehn Größen aus T48; die drei Skalenübergänge aus T50 sind privat und haben genau die dort genannten Aufruforte; ein Test rechnet die Zahlenprobe aus T47 nach und nennt 4.200.000.000.000 Cent.
---

# `kern::werte` — die siebzehn abgeleiteten Größen

**Neu gefasst am 2026-09-01. Der alte Wortlaut steht unten und ist überholt** — er sagt
„Der Entwurf gibt es nicht her; entscheide es". Seit `spiel.md` Fassung 5 und
`technik.md` T47/T48/T50 gibt der Entwurf es her: alle sieben Bewertungsfunktionen, die
Skalengrenze, die Reihenfolge der Rundungen und eine durchgerechnete Zahlenprobe. Ein
Kernbauer, der noch selbst entschiede, wiche von `specs/` ab — was seine eigene Rolle
verbietet.

Vorher lesen: `technik.md` T47, T48, T50, T5, T13, T33, T39; `rueckstand.md`, Abschnitt
*Es gibt keinen Übersetzer*.

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

1. `grep -n 'pub fn' kern/src/werte.rs` liefert **genau die siebzehn Namen aus T48**,
   keinen mehr und keinen weniger. Das ist der mechanische Nachweis, den T13 und T48
   ausdrücklich für dieses Modul vorsehen.
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
