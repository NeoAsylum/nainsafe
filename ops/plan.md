# Plan — 0016-hedgefonds-simulation-echte-weltwirtschaft

Stand 2026-09-08, zweiter Plan an diesem Tag. Abgedeckt: seit heute früh.

## Wo das Vorhaben steht

**Die Sperre ist gefallen und der Rückstand ist durchgelaufen.** `ops/reserviert.txt` sagt
`# frei`; von 253 Paketen sind **231 fertig** (+62), 4 offen, 3 Vorschläge, 3 gebaut,
5 blockiert. **Dafür ist der Riegel wieder rot:** `befunde/uebersetzung-2026-09-08.md`
meldet `ergebnis: fehler` — 3 von 29 Proben im Werkstattbaum gefallen
(`belegstellen_wortabstand`, `belegstellen_kopfzahlen`, `multiplikationsriegel`); Kern
14/14 und Prüfstand 3/3 grün. Geld bindet nicht.

## Der Engpass

**Schritt 3 reicht durch, und kein Paket im ganzen Bestand fasst ihn an.**

Der rechnende Rumpf von Schritt 5 steht seit 0197 (`fertig`): `realeinkommenshub`,
`politiklast`, `werte::bip`, `werte::schaden`, vier Festkommastellen in
`kern/src/schritt.cpp`. Er rechnet trotzdem nichts. Der Kern-Prüfer nennt den Grund im
Wortlaut (`befunde/pruefung-0233-feldzaehler-an-einer-rohen-reihe-messen-2026-09-08.md`,
Z. 75–77): „**step 3 carries forward, so `richtung == 0`, so `last = 0`, `hub = 0`,
`wirkung = 0`**". Der Draht liegt, der Strom fehlt.

Gemessen: **kein offenes, kein vorgeschlagenes und kein blockiertes Paket trägt
`kern/src/schritt.cpp` in `dateien:`.** Die Vorgaben dafür sind fertig — 0165 und
0172-weltpreis stehen seit heute auf `fertig` —, und es hängt kein Baupaket an ihnen.
Sechs der sieben offenen und vorgeschlagenen Pakete gehören dem **Architekten** und fassen
`technik.md` an; sie laufen deshalb nur nacheinander, und keines bewegt die Runde.

## Was quer liegt

- **Der Nachtbericht wird an Ort und Stelle überschrieben.** Zwei heutige
  `geprueft`-Befunde zitieren `uebersetzung-2026-09-08.md` mit `ergebnis: ok` und
  „`belegstellen_kopfzahlen` **Passed** … :123-124" (`pruefung-0189-…-2`, Z. 15;
  `pruefung-0233-…`, Z. 15). Dieselbe Datei sagt jetzt `ergebnis: fehler` und
  `***Failed***`. Beide Prüfer hatten recht, als sie schrieben; nachprüfbar ist keiner
  mehr. Der Bericht braucht einen Namen je Lauf, nicht je Tag.
- **Die Kopfzahlen des Belegstellenriegels sind eine Schleife.** Sechs Pakete, alle
  `fertig`, alle auf dieselben zwei Dateien: 0115, 0166, 0189, 0227, 0232, 0233. Heute früh
  wieder rot, und der Riegel sagt selbst warum: „**Die Zahlen sind damit aelter als der
  Baum**" (Bezugsstand 2f2f79f, HEAD cd46bbf). Jeder Übertrag veraltet mit dem nächsten
  Commit. **Ein siebtes Übertragungspaket löst das nicht.**
- **`multiplikationsriegel` ist rot wie bestellt.** 0273 hat ihn gebaut, er findet sofort
  zwei echte Stellen (`kern/include/kern/festkomma.hpp:99` und `:356`). Kein Rückschritt —
  die Entscheidung darüber ist Vorschlag 0274.
- **0092, 0272 und 0273 stehen `gebaut` mit `urteil: geprueft`.** Ein Lauf des
  Projektmanagers macht sie `fertig`; allein 0092 löst 0181 und darüber 0226 — die halbe
  offene Liste.
- **Zwei Zahlen für dasselbe Maß:** `ops/portfolio.md` (Stand 2026-09-06) führt „0 von
  310", gemessen ist seit 0071 **1 von 310**. Und zwei Pakete tragen die Nummer 0275.

## Was der Betreiber entscheiden muss

**Die Übersetzungsfrage vom 2026-09-07 ziehe ich zurück.** Ihr einziger verbliebener Grund
war die Sperre, und die ist von selbst gefallen. Sie kostet dich nichts mehr.

**Offen bleibt genau eine, und es ist dieselbe wie am 2026-09-07:
`0208-baulauf-faehrt-beide-profile`.** Kein Agent darf `agents/**` schreiben —
`agents/lauf.py:NIE` verbietet es global —, also kannst nur du das tun. Keine Geldfrage;
der Preis ist Maschinenzeit: ein zweiter `cmake`/`ctest`-Durchgang je Manifest mit
`-DFABRIK_SANITIZER=OFF`, zehn Manifeste, nachts.

- **A — so lassen.** Jede Abnahme mit der Formel „in beiden Bauprofilen" bleibt
  unerfüllbar. Sie hat schon 0194 auf `blockiert` gekostet, obwohl der Prüfer alles
  Übrige bestätigt.
- **B — du fährst die Änderung selbst ein.** Vorbild ist Paket 0131.

**Empfehlung B.** Der Projektmanager nennt es den zehnten Fall dieser Art, und seit dem
Shell-Verbot vom 2026-09-06 kann das OFF-Profil niemand mehr belegen: weder der Bauer noch
der Prüfer, und der Nachtlauf fährt es nicht.

## Vorrang

Zwei der fünf Kennungen gibt es noch nicht; sie sind anzulegen. Das ist kein Versehen — der
Bestand enthält für die beiden wichtigsten Dinge kein Paket.

1. **Schritt 3 rechnen lassen** — *neu anzulegen*, Rolle `kernbauer`, Datei
   `kern/src/schritt.cpp`, gegen die fertigen Vorgaben 0165 und 0172-weltpreis. Alles, was
   diese Woche gebaut wurde, speist einen Rumpf, der mit null multipliziert.
2. **0092-abschnitt-18-zwei-zaehlfehler** auf `fertig` — eine einzige Statusänderung, die
   zwei der vier offenen Pakete freigibt.
3. **0274** — entscheidet den Regelsatz aus T7 und ist der einzige Weg, eine der drei roten
   Proben grün zu bekommen.
4. **Kopfzahlen selbst erheben statt abschreiben** — *ebenfalls neu anzulegen*: der Riegel
   soll seine drei Zahlen zur Laufzeit messen. Das bricht die Schleife aus sechs Paketen.
   **Kein siebtes Übertragungspaket.**
5. **0236**, dann **0230** — die einzigen offenen Pakete ohne offene Vorbedingung. Sie
   fassen dieselbe Datei an und müssen nacheinander laufen.

**Nicht einplanen:** 0208-baulauf — es liegt beim Betreiber, siehe oben.

## Die eine Zahl

**1 von 310** — unverändert seit dem 14. Plan (`partie.runde`). Der Apparat ist erneut
gewachsen: 29 Proben im Werkstattbaum (vorher 25), 14 im Kern (vorher 13), zehn Manifeste,
462 geprüfte Schaltereinträge — und die Runde rechnet weiterhin nichts.

**Neu ist die Ursache, und sie ist zum ersten Mal genau.** Nicht mehr der fehlende Draht:
den hat 0229 gelegt, 0197 hat den Rumpf angehängt, beide sind `fertig`. Was fehlt, ist die
Null, die Schritt 3 in diesen Rumpf schiebt. Der Satz des Portfolio-Managers vom
2026-09-06 gilt damit schärfer als damals: „**Die Fabrik baut den Prüfapparat einer
Simulation, die noch nicht rechnet.**" **Bewegt sich die Zahl, ohne dass Schritt 3
rechnet, stimmt die Messung nicht.**
