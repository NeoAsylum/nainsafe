# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-11. Abgedeckt: seit dem Plan vom 2026-09-10.

## Wo das Vorhaben steht

**Der Engpass des letzten Plans ist in einer Nacht gefallen, und zwei weitere Mitglieder
dazu.** `daten` ist gebaut (0297, heute `geprueft`), `schnittstelle` ebenfalls (0301), und
`kern/aktion` ist neu (0300, `geprueft`); der Nachtbericht fährt jetzt **zwölf Manifeste
statt zehn**, und von den zehn Mitgliedern stehen **drei** als „noch nicht gebaut" statt
fünf: `konsole`, `oberflaeche`, `werkzeuge/aufbereitung`
(`befunde/uebersetzung-2026-09-11.md:20-22`). Nicht fertig sind 28 Pakete: 8 offen,
10 gebaut (davon 7 heute `geprueft`, eines `zurueck`), 5 Vorschläge, 5 blockiert; drei rote
Riegel. Geld bindet nicht.

## Der Engpass

**`werkzeuge/aufbereitung` ist nicht gebaut, und kein Paket im Bestand baut es.**

Dieselbe Negation wie gestern, ein Glied weiter unten. 0297 hat den Ladeweg absichtlich
ausgelassen und gesagt warum: *„`jahrgang-<jahr>.bin` schreibt `werkzeuge/aufbereitung`
(T23), und dieses Mitglied ist nicht gebaut. Ein Paket, das ein Format liest, das noch
niemand schreibt, ist entweder blockiert oder erfindet das Format nebenbei"*
(`aufgaben/0297-der-daten-treiber-fuellt-den-pfadtraeger.md:38-40`). Es gibt also seit
heute einen Jahrgangsträger, aber keine Datei, die ihn füllt: `daten` lässt sich nur von
Hand bestücken, und ohne Jahrgangsdatei kein `weltlauf`. **Ich habe `dateien:` über alle
Pakete 0290–0310 gelesen — `aufbereitung`, `konsole` und `oberflaeche` kommen dort nur im
Fließtext vor, in keinem einzigen `dateien:`-Feld.**

## Was quer liegt

- **Eine Runde und ihre Stützstelle stehen in `technik.md` zweimal verschieden, ein Jahr
  auseinander.** Der Daten-Prüfer hat es beim Abnehmen von 0297 gefunden und als Vorschlag
  `0303-eine-runde-und-ihre-stuetzstelle-stehen-zweimal-verschieden` hingelegt. Was es
  kostet, wenn es offen bleibt, steht dort in eigenen Worten: *„One year of offset on every
  reported policy series in the `weltlauf` … it looks like a sluggish reaction and is an
  index shift"* — und es wird dann **dreimal getrennt entschieden**, in
  `werkzeuge/aufbereitung`, in `schnittstelle` und im Backtester. 0297 ist trotzdem
  `geprueft`, weil seine Abnahme eine der beiden Lesarten ausdrücklich nennt: **gebaut ist
  eine Lesart, entschieden ist keine.**
- **Drei rote Riegel, und zwei davon sind Absicht.** `zahlwort_messung` ist der eigene
  Beleg von 0286 (*„`:2074-2088` appears in the report exactly when the riegel is red"*,
  `pruefung-0286-…-2026-09-11.md:63`), `multiplikationsriegel` der von 0290. Wem
  `belegstellen_wortabstand` gehört, habe ich **nicht** festgestellt — das ist eine offene
  Frage und keine Entwarnung.
- **Die Nummernvergabe: behoben und in derselben Nacht wieder da.** Der Projektmanager hat
  die fünf 0293 umnummeriert (0294, 0295, 0296) und die alten Dateien als Stummel mit
  `dateien: []` stehen lassen — richtig nach Regel 3. Gleichzeitig sind **drei neue Pakete
  0303** entstanden. Behoben ist die Folge, nicht die Ursache; ein `Grep` auf eine Nummer
  trifft jetzt echte Pakete und Stummel gemischt.
- **`0289` kam heute `zurueck`** — ein Kriterium zitiert eine überholte Fassung
  (`kennzeichen_riegel.cpp:1526-1529`). Der Paketstatus steht noch auf `gebaut`.
- **`ops/auslastung.md` ist vom 2026-09-07** und damit vier Tage alt. Die Kostenseite, die
  du liest, misst eine andere Woche als dieser Plan.
- **Damit es niemand „repariert":** `R = 20` (`spiel.md:11`) und `PARTIELAENGE_HOECHSTENS
  = 26` (`verlauf.hpp:208`) widersprechen sich **nicht**. Das erste ist die Partielänge,
  das zweite die Kapazitätswand aus T40, und die bricht erst bei 139
  (`kern/messung/wandschranke.py:11-13`).

## Was der Betreiber entscheiden muss

**Dieselbe Frage wie am 2026-09-07, -08, -09 und -10: `0208-baulauf-faehrt-beide-profile`,
fünfter Plan.** Kein Agent darf `agents/**` schreiben (`agents/lauf.py:NIE`), also kannst
nur du es. Keine Geldfrage; der Preis ist Maschinenzeit — ein zweiter `cmake`/`ctest`-Gang
je Manifest mit `-DFABRIK_SANITIZER=OFF`, **jetzt zwölf Manifeste statt zehn**, nachts.

- **A — so lassen.** Jede Abnahme mit der Formel „in beiden Bauprofilen" bleibt
  unerfüllbar; sie hat 0194 auf `blockiert` gekostet.
- **B — du fährst die Änderung selbst ein.** Vorbild ist Paket 0131.

**Empfehlung B, unverändert.** Dass ich dieselbe Frage zum fünften Mal stelle, ist selbst
eine Meldung: willst du sie nicht, sag A, und ich nehme sie aus dem Plan.

**Das Suchlauf-Gate ist näher, aber noch nicht fällig.** Zwanzig der vierzig Schlüssel
brauchen einen Suchlauf — nach `spiel.md:3428-3434` rund **26,5 Stunden auf einem Kern,
3,3 auf acht**. Zwischen heute und dieser Frage stehen noch zwei Mitglieder:
`werkzeuge/aufbereitung` (die Jahrgangsdatei) und `konsole` (der Läufer). Ich lege es dir
vor, wenn beide stehen.

## Vorrang

1. **`0303-eine-runde-und-ihre-stuetzstelle-stehen-zweimal-verschieden`** — ein
   Architektenlauf auf `technik.md`, und er muss **vor** Nummer 2 laufen: sonst entscheidet
   `werkzeuge/aufbereitung` den Jahresversatz nebenbei und zum dritten Mal.
2. **Ein Paket für `werkzeuge/aufbereitung`** — *neu anzulegen*. Der Engpass; es schreibt
   die Jahrgangsdatei, die 0297 bewusst ausgelassen hat.
3. **Die sieben geprüften Pakete auf `fertig`, `0289` auf `zurueck`** — ein Lauf des
   Projektmanagers, und im selben Lauf die drei 0303 umnummerieren.
4. **`0302-was-eine-aktion-an-kasse-zieht-steht-nirgends`** — hängt an 0300, und das ist
   seit heute `geprueft`: die Kette läuft, wenn sie jetzt weitergeführt wird.
5. **`0299-the-four-sums-left-in-werte-still-report-no-place`** — offen, `kern/src/`,
   führt 0288 zu Ende.

**Nicht einplanen:** 0208 (Betreiber, siehe oben). **Vorgemerkt, aber nicht in den fünf:**
`0310-die-vierzig-marken-nennen-ihren-weg` — zwanzig Kommentare in `parameter.toml` sagen
„Kalibriert: Selbstspieler" über Schlüssel, die in Wahrheit an einem Gate hängen.

## Die eine Zahl

**6 von 13.** Von den dreizehn Paketen mit den Nummern 0294 bis 0310 schreiben **sechs**
Produktivquelltext: 0297 (`daten/src`), 0301 (`schnittstelle/src`), 0300 und 0302
(`kern/src/aktion`), 0299 und `0303-die-einstellige-handelssumme` (`kern/src/werte`). Vier
schreiben den Prüfapparat, drei `specs/` oder `parameter.toml`.

Dieselbe Zahl lautete im letzten Plan **3 von 52**. Das ist die Umkehr, auf die diese
Fabrik seit Wochen wartet — und sie ist eine Nacht alt; eine Nacht ist keine Reihe. Der
Satz, hier werde der Prüfapparat einer Simulation gebaut, deren Hälfte fehlt, gilt seit
heute schwächer: es fehlen drei von zehn Mitgliedern, nicht fünf.
