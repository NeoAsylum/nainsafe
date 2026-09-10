---
id: 0285-verlauf-probe-faehrt-mit-einem-pfadstand-der-ihre-lage-nicht-bewegt
rolle: kernbauer
status: offen
haengt_an: []
vermerk_annahme: "ANGENOMMEN 2026-09-10 (24. Lauf), `vorschlag` -> `offen`, Projektmanager, Schnitt unveraendert. Vorgeschlagen vom `kern-pruefer` aus Befund 1 seiner eigenen `0284`-Pruefung. **Vorrang 1 des 15. Plans: bis das steht, misst nichts im Bestand eine ganze Partie.** || **DIE VIER PRUEFUNGEN.** *Rolle* `kernbauer` steht in `baulauf.py:BAUROLLEN`. *Dateischnitt*: genau eine Datei, `kern/test/verlauf_probe.cpp`, und sie steht in **keiner** anderen Liste -- insbesondere **nicht** in den sieben Dateien von `0284`. Ihr lauft heute Nacht nebeneinander. *Abnahme*: vier Bedingungen, jede am Text und am Nachtbericht ablesbar. *Vorleistung*: **ich habe `haengt_an: [0284]` geleert, und das ist eine Entscheidung, keine Nachlaessigkeit.** `0284` steht auf `offen`, weil sein Ruecklauf eine Kommentarzeile in `werte.hpp:218` ist -- **der Code, den du brauchst, liegt seit dem 2026-09-09 im Baum**: `schritt_3_politik` schreibt. Haettest du auf `0284: fertig` gewartet, haette Vorrang 1 eine Nacht auf eine Kommentarzeile gewartet. Die Dateien sind disjunkt, also kann nichts kollidieren. || **WAS DU BAUST, IN EINEM SATZ.** `KONSTANTEN_DER_PROBE` (`:120`) ist nullinitialisiert, `ausgangslage` (`:284-285`) fuellt alle 310 Adressen mit `musterwert(platz)`. Seit `0284` schreibt Schritt 3 die Null in die zwoelf pfadgestuetzten Instrumentenstaende, sechs davon trugen `-10.000`, also bewegen sie sich -- und `politiklast` faellt ueber `schuld(l)` mit `staatsschuld` = `I64_MIN` fuer CN und BR in den Abbruch. **Du gibst der Probe einen Traeger, den ihr eigener Zustand mittraegt:** `pfadstand` haelt je Adresse genau das, was `ausgangslage` dort hinschreibt, gebaut aus dem `musterwert`, den die Datei schon hat -- **keine zweite Kopie der acht Muster.** || **DAS VORBILD STEHT IN `schritt_probe.cpp` UND STAMMT AUS `0284`:** `pfadstand_der_probe()` fuellt den Traeger ueber dieselben zwoelf Adressen aus `musterwert`, und der Kopf sagt warum. **Uebernimm die Form, nicht den Code** -- die beiden Dateien haben verschiedene `ausgangslage`-Bauer. || **WARUM DER TRAEGER UND NICHT DER ZUSTAND, damit du den anderen Weg nicht noch einmal aufmachst:** die vier `staatsschuld`-Adressen anzuheben, wie `0238` die zwoelf Wertschoepfungsadressen anhob, wuerde die Bewegung behalten und den **naechsten** Ueberlauf verstecken statt den jetzigen -- die Zolllinie liest `handelsvolumen` und `weltpreis`, und die tragen `I64_MAX` in derselben Lage. Der erklaerte Zweck dieser Datei ist *„der Verlauf und nicht die Rechnung einer Runde\"* (`:116`). **Ein Traeger, der nichts bewegt, ist die kleinere und die ehrliche Behauptung** -- und Bedingung 2 verlangt, dass der Kopf das hinschreibt. || **DIE FALLE IST BEDINGUNG 3.** Der billige Weg zu einem gruenen `verlauf_probe` ist, `PARTIERUNDEN` zu senken, die zwanzig Aufrufe bei `:330` anzuruehren oder `ausgangslage` nicht mehr alle 310 Adressen fuellen zu lassen. Dann laeuft die Probe durch und misst nichts -- *„eine Pruefung, deren Gegenstand sich nicht bewegen kann, ist gruen und wertlos\"* (`notizen/lehren.md`, 2026-09-06). **`PARTIERUNDEN` bleibt `PARTIELAENGE_HOECHSTENS`, die zwanzig Aufrufe bleiben, `ausgangslage` fuellt weiter alle 310.** Bedingung 4 verlangt den Bericht mit zwanzig Runden und 175 Verknuepfungen je Runde; eine Zahl darunter ist der Beleg, dass Bedingung 3 verletzt wurde. || **DU MACHST DIE MELDUNG NICHT LESBAR, UND DAS IST ABSICHT.** Dein Traeger laesst den Abbruch nicht auftreten; er macht ihn nicht auffindbar. Sobald der `daten`-Treiber echte Staende einspielt, bekommt der naechste Leser dieselben elf Worte ohne Adresse. **Das ist `0288`** (`politiklast` und `handelsvolumen` melden ihren Ort), es haengt hinter `0284` und ist ausdruecklich nicht deins. || **DU KANNST NICHTS AUSFUEHREN.** Keine Rolle hat `Bash` (`agents/lauf.py:NIE`); dein Beleg ist `befunde/uebersetzung-<datum>.md`, den der Runner fuer dich hinlegt. || **Sieben Spuren neben dir, und `0284` ist eine davon** -- es haelt `kern/`, du haeltst `kern/test/verlauf_probe.cpp`. Schreib in keine seiner sieben Dateien."
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/kern/test/verlauf_probe.cpp]
abnahme: "1. `verlauf_probe` is green again: `KONSTANTEN_DER_PROBE` (`verlauf_probe.cpp:120`) carries a `pfadstand` that holds, for each of the twelve path-anchored instrument stands, exactly the value `ausgangslage` writes to that address -- `musterwert(stelle_instrument(land, i, Stand))`. Built from the same `musterwert` the file already has, not from a second copy of the eight patterns. 2. The head comment at `:113-119` says why: the file measures the course of a game and not the arithmetic of one round, and a carrier that moved the stands would drag step 5 into `werte::schaden` on a state whose debt ratio is `I64_MIN`. 3. Nothing else changes: `PARTIERUNDEN` stays `PARTIELAENGE_HOECHSTENS`, the twenty calls at `:330` stay untouched, and `ausgangslage` keeps `musterwert` on all 310 addresses. 4. The build report shows `verlauf_probe` green with its twenty rounds and 175 links per round."
---

# `verlauf_probe` needs a carrier its own state agrees with

## What breaks, measured on 2026-09-09

Package `0284` made `schritt_3_politik` write `Konstanten::pfadstand` into the three
path-anchored instrument stands of every playable country. `verlauf_probe` runs twenty
rounds with a **value-initialised** carrier (`verlauf_probe.cpp:120`) over a state that
carries `musterwert` on all 310 addresses. Those two no longer agree:

- Instrument stands sit at `44l + 24 + 4i`. Modulo the eight patterns that is `0` or
  `-10.000`; six of the twelve path stands carry `-10.000`.
- Step 3 now writes `0` there, so six stands move in round 1.
- `politiklast` therefore calls `werte::schaden` for them. The policy-rate line is
  `mal_geteilt(schuld(l), hub, 10.000)` with `schuld(l) = mal_geteilt(bip(l),
  staatsschuld(l), 10.000)`.
- `staatsschuld` sits at `44l + 19`; for CN (`63`) and BR (`151`) that is pattern index 7,
  the smallest `int64_t`. `bip` is `30.000` there (`WERTSCHOEPFUNG_DER_PROBE` on twelve
  addresses). `mal_geteilt(30.000, I64_MIN, 10.000)` leaves `i64` and aborts in
  `kern::festkomma` -- and CN and BR are exactly the two countries whose policy rate moves.

The probe has no `try` around `probe_partie`, so the abort ends the run.

## Why this is a package and not part of `0284`

`verlauf_probe.cpp` is not in the `dateien` of `0284`; that list is where the build run
serialises claims, and a builder who writes outside it is the case that list exists
against. The fix is also not a line of `0284`'s scope: it changes what a **foreign**
probe's carrier holds, and the reason has to be written into that file's head, not into
`schritt_probe`'s.

## Why the carrier and not the state

Two ways out, and the other one is worse. Lifting the four `staatsschuld` addresses the
way package `0238` lifted the twelve value-added ones would keep the movement and hide the
next overflow instead of the current one -- the tariff line reads `handelsvolumen` and
`weltpreis`, which carry `I64_MAX` in the same layout. This file's stated purpose is "der
Verlauf und nicht die Rechnung einer Runde" (`:116`); a carrier that moves nothing is the
smaller claim and the honest one.

## The precedent, so the shape is not invented twice

`schritt_probe.cpp` did exactly this in package `0284`: `pfadstand_der_probe()` fills the
carrier from `musterwert` over the same twelve addresses, and the head says why. Copy the
shape, not the code -- the two files have different `ausgangslage` builders.
