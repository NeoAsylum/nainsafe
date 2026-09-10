# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-10. Abgedeckt: seit dem Plan vom 2026-09-09.

## Wo das Vorhaben steht

**Der Kern ist wieder ganz grün und rechnet.** 0285 hat `verlauf_probe` repariert — 14 von
14 Proben, eine ganze Partie über 26 Runden läuft durch —, und 0284 ist damit vollständig
abgenommen. **Der Engpass des letzten Plans ist beantwortet:** 0291 hat die Marke
nachgemessen (40-mal `Kalibriert: Selbstspieler`, nicht 47) und jedem der vierzig Schlüssel
einen Weg zugewiesen; zwanzig sind ohne Programmlauf erreichbar, zwanzig hängen an einem
Betreiberlauf. 278 Pakete: 248 fertig, 7 offen, 8 gebaut (7 davon heute `geprueft`),
6 Vorschläge, 5 blockiert; Werkstattbaum 4 von 29 rot (gestern 6). Geld bindet nicht.

## Der Engpass

**`daten` ist nicht gebaut, und kein Paket im Bestand baut es.**

Fünf der zehn Mitglieder stehen im Nachtbericht als „noch nicht gebaut": `daten`,
`schnittstelle`, `konsole`, `oberflaeche`, `werkzeuge/aufbereitung`
(`befunde/uebersetzung-2026-09-10.md:20-24`). Seit 0284 schreibt Schritt 3 den `pfadstand`
in die Adressen — **befüllt wird er von niemandem.** Der Prüfer schreibt es selbst hin:
„For whoever builds the `daten` driver" (`pruefung-0284-…-2026-09-10.md:76`). Ohne `daten`
kein Jahrgang, ohne Jahrgang kein `weltlauf`, ohne `weltlauf` keiner der zwanzig
Gate-Schlüssel — und die sechs Schlüssel, die 0291 dem `datenbauer` „am Jahrgang" zuweist,
haben keinen Jahrgangsbau, in den sie fallen könnten. **Ich habe den ganzen Rückstand
danach durchsucht: kein Paket, weder offen noch Vorschlag, nennt eines der fünf
Mitglieder.**

## Was quer liegt

- **Die Nummernvergabe ist gebrochen: fünf Pakete heißen 0293.** Zwischen 0257 und 0293
  tragen sechs Nummern je mehr als ein Paket, elf Dateien auf sechs Nummern; am 2026-09-08
  war es eine Kollision. Die Ursache ist mechanisch — Vorschläge entstehen nachts parallel,
  jeder Prüfer nimmt die höchste Nummer plus eins. Behoben wird das vom Projektmanager bei
  der Annahme, durch Umnummerieren; sonst ist `haengt_an:` bald nicht mehr auflösbar.
- **Drei Pakete auf einer Datei.** 0292 und `0293-die-verteilung-nennt-zahlen` fassen beide
  `multiplikationsriegel.cpp` an, dazu das gebaute 0290.
- **Mein schärfster Satz von heute stimmt nicht.** 0291 nennt „Weg 5a ist leer" sein
  wichtigstes Ergebnis und richtet es ausdrücklich an mich; `parameter.toml:708-710` und
  `:718-720` sagen von zwei der vierzig Schlüssel das Gegenteil in eigenen Worten. Der Satz
  gehört in meinen Bericht an dich, also muss er vorher stimmen — das ist
  `0293-weg-5a-is-not-empty`.
- **Berichtigung an mir selbst:** `PARTIERUNDEN` ist 26 und nicht 20 (`verlauf.hpp:208`);
  der 15. Plan trug in `:98-104` dieselbe falsche Zwanzig.
- **`multiplikationsriegel` rot ist kein Schaden, sondern Absicht.** 0290 verlangte den
  roten Lauf, und der Riegel nennt eine echte Stelle (`festkomma.hpp:99`). Von den vier
  Roten gehören zwei zu 0286 (offen), eines hierher, eines zum Messstand 0166.
- **Sieben Pakete stehen `gebaut` mit `urteil: geprueft`** (0282, 0283, 0284, 0285, 0287,
  0290, 0291); gestern waren es drei. 0236 kam als einziges `zurueck`.

## Was der Betreiber entscheiden muss

**Dieselbe Frage wie am 2026-09-07, -08 und -09: `0208-baulauf-faehrt-beide-profile`,
vierter Plan.** Kein Agent darf `agents/**` schreiben (`agents/lauf.py:NIE`), also kannst
nur du es. Keine Geldfrage; der Preis ist Maschinenzeit — ein zweiter `cmake`/`ctest`-Gang
je Manifest mit `-DFABRIK_SANITIZER=OFF`, zehn Manifeste, nachts.

- **A — so lassen.** Jede Abnahme mit der Formel „in beiden Bauprofilen" bleibt
  unerfüllbar; sie hat 0194 auf `blockiert` gekostet.
- **B — du fährst die Änderung selbst ein.** Vorbild ist Paket 0131.

**Empfehlung B, unverändert.**

**Und eine Vorwarnung, damit sie dich nicht überrascht:** 0291 hat ein Gate ausgerechnet,
das noch nicht ansteht. Zwanzig der vierzig Schlüssel brauchen einen Suchlauf — nach
`spiel.md:3428-3434` rund **26,5 Stunden auf einem Kern, 3,3 auf acht**, zerlegt in fünf
entkoppelte Gruppen. **Heute ist es nicht entscheidbar**, weil das Programm, das dabei
liefe, nicht existiert. Ich lege es dir vor, wenn `daten` steht.

## Vorrang

1. **Ein Paket für den `daten`-Treiber** — *neu anzulegen*, Rolle `datenbauer`. Der
   Engpass; alles andere in dieser Liste ist Instandhaltung.
2. **Die sieben geprüften Pakete auf `fertig`** — ein Lauf des Projektmanagers, und im
   selben Lauf die fünf 0293 umnummerieren.
3. **`0293-weg-5a-is-not-empty-and-the-multi-line-marks-are-four`** — zwei Absätze in einem
   Abschnitt, den 0291 heute geschrieben hat; danach stimmt, was dir vorgelegt wird.
4. **0286**, gebaut als **Messung, nicht als Übertragung** — holt zwei der vier Roten
   zurück; genau der Zug, der 0278 grün gemacht hat.
5. **0288** — das einzige offene Paket auf `kern/src/`: die zwei Summen, die Schritt 5
   jetzt erreicht, melden ihren Ort nicht.

**Nicht einplanen:** 0208 (Betreiber, siehe oben). **Rücklauf offen:** 0236.

## Die eine Zahl

**28 zu 3.** Von den zweiundfünfzig Paketen mit den Nummern 0251 bis 0293 schreiben 19
einen Riegel unter `werkzeuge/` und 9 eine Probe unter `kern/test/` — **28 am
Prüfapparat.** Drei schreiben `kern/src/`: 0260, 0284, 0288.

Die alte Zahl — wie viele der 310 Adressen eine Runde bewegt — bleibt **nicht messbar**,
und der 0285-Prüfer hat gesagt warum: `ctest` druckt die Ausgabe einer Probe nur, wenn sie
fällt. Der Satz des Portfolio-Managers vom 2026-09-06 hält deshalb in schärferer Fassung:
die Fabrik baut den Prüfapparat einer Simulation, deren Hälfte nicht gebaut ist.
