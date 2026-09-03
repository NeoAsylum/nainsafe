---
paket: 0007-adressverzeichnis-310
rolle: datenbauer
stand: 2026-09-01
quellen: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md T5, T15, T16, T17, T22, T23, T27, T33, T45, T46, T47, T49, T51; specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md, Abschnitt "Der Zustand" und Tabelle "Jede Größe ohne Datenanker"]
---

# Die 310 Zustandsadressen, einzeln

Vierte unabhängige Zählung derselben Menge. T15 zerlegt sie nach Gruppen, T45 nach
Herkunft, T49 nach Skalenklasse; hier steht sie aufgezählt, damit die drei Zerlegungen
Zeile für Zeile gegeneinander laufen statt nur Summe gegen Summe.

**Die vier Zählungen gehen auf.** Ergebnis vorweg, damit der Prüfer weiss, wonach er
sucht: 310 Zeilen, keine Adresse zweimal; Gruppen `198 + 56 + 52 + 4`; Herkunft
`136 + 150 + 11 + 2 + 11`; Klassen `3 + 71 + 36 + 22 + 22 + 5 + 5 + 25 + 32 + 4 + 83 + 2`.
Die Nachrechnung steht unten unter *Die vier Zählungen*. Eine fehlende oder doppelte
Adresse ist beim Aufzählen nicht aufgetreten.

**Zwei Beobachtungen, die keine Summe reissen und trotzdem hierher gehören** — ein
Widerspruch zwischen zwei Vorgaben und eine Menge frei gebildeter Adressen —, stehen unter
*Befunde*.

## Wie die Tabelle zu lesen ist

| Spalte | Inhalt |
|---|---|
| # | laufende Nummer 1 … 310, nur zum Zählen |
| Adresse | nach T17. **Ein `*` heisst: an dieser Adresse ist ein Bestandteil neu erfunden — oder eine Zusammensetzung von Bestandteilen, die in keinem Dokument gemeinsam vorkommt.** Die Marke sitzt an den Bestandteilen, nicht an der ganzen Zeichenkette: Die 133 unmarkierten Zeilen sind wörtlich belegte Adressen und die daraus über die Gebiets-, Sektor- und Instrumentenindizes gebildeten Geschwister — `handel.US.CN.1` trägt deshalb keine Marke, obwohl genau diese Zeichenkette nirgends steht, denn `handel.DE.CN.1` steht in T17. Umgekehrt gilt der Satz nicht: Ist der eingesetzte Bestandteil selbst neu, trägt auch die Geschwisteradresse eine Marke — so bei `restwelt.` vor einem Sektorpfad (Nr. 180, gebildet aus `land.DE.sektor.2.preis`) und beim Instrument `regulierung` (Nr. 37, gebildet aus `land.BR.instrument.zoll.stand`). **Und ein Beleg, der in T46 steht, deckt nur die Adresse selbst: T46 zählt seine elf Vorgabeadressen abschliessend auf und erzeugt deshalb keine unmarkierten Geschwister.** Wer dort einen Index anders belegt, verlässt die Ausnahmeliste — die drei übrigen Länderwechselkurse (Nr. 63, 107, 151) tragen deshalb eine Marke, die drei übrigen Aufsichtszähler (Nr. 23, 111, 155) dagegen nicht, weil T45 `land.CN.aufsichtszaehler` als Beispiel einer Kategorie von 150 Adressen führt und nicht als abschliessende Liste. Eine Adresse mit eigenem wörtlichem Beleg bleibt davon unberührt: `land.<L>.leitzins` (Nr. 18, 62, 106, 150) steht mit Index in `technik.md`, **T49**, im Absatz „Zwei Adresspaare tragen denselben Wert, und das braucht eine Regel statt eines Zufalls“ — dort im Wortlaut: „`land.<L>.leitzins` und `land.<L>.instrument.leitzins.stand` sind dieselbe Größe“. Die Bildungsregeln und die Gegenprobe an allen acht T46-Zeilen stehen unter *Befund 2* |
| Gruppe | die Zeile der Tabelle in T15, aus der die Adresse stammt |
| Herkunft | einer der fünf Einträge aus T45. `*` an einem Schlüsselnamen heisst dasselbe wie an einer Adresse |
| K | Skalenklasse 1 … 12 nach T5, zugeordnet nach T49 |
| Startwert | nur wo die Herkunft `Entwurf` (spiel.md) oder `Vorgabe` (T46) ist; sonst `—`, weil der Wert dann aus Reihe, Parameterdatei oder Manifest kommt |

Feste Ordnung nach T9: Gebiete `US, CN, DE, BR, RW`; Sektoren `1` Landwirtschaft,
`2` Industrie, `3` Dienstleistungen; Instrumente `leitzins, zoll, haushalt, regulierung`.
Handelbar sind die Sektoren 1 und 2.

## Die 310 Adressen

| # | Adresse | Gruppe | Herkunft | K | Startwert |
|---:|---|---|---|---:|---:|
| 1 | `land.US.sektor.1.wertschoepfung` | je Sektor | Datenanker(1 × 2) | 2 | — |
| 2 | `land.US.sektor.1.kapitalstock` | je Sektor | Datenanker(3 × 2) | 2 | — |
| 3 | `land.US.sektor.1.beschaeftigung` | je Sektor | Datenanker(7) | 8 | — |
| 4 | `land.US.sektor.1.preis` | je Sektor | Entwurf | 5 | 10.000 |
| 5 | `land.US.sektor.2.wertschoepfung` | je Sektor | Datenanker(1 × 2) | 2 | — |
| 6 | `land.US.sektor.2.kapitalstock` | je Sektor | Datenanker(3 × 2) | 2 | — |
| 7 | `land.US.sektor.2.beschaeftigung` | je Sektor | Datenanker(7) | 8 | — |
| 8 | `land.US.sektor.2.preis` | je Sektor | Entwurf | 5 | 10.000 |
| 9 | `land.US.sektor.3.wertschoepfung` | je Sektor | Datenanker(1 × 2) | 2 | — |
| 10 | `land.US.sektor.3.kapitalstock` | je Sektor | Datenanker(3 × 2) | 2 | — |
| 11 | `land.US.sektor.3.beschaeftigung` | je Sektor | Datenanker(7) | 8 | — |
| 12 | `land.US.sektor.3.preis` | je Sektor | Entwurf | 5 | 10.000 |
| 13 | `land.US.bevoelkerung`* | Aggregat | Datenanker(5) | 8 | — |
| 14 | `land.US.erwerbstaetige`* | Aggregat | Datenanker(6) | 8 | — |
| 15 | `land.US.produktivitaet`* | Aggregat | Datenanker(4) | 7 | — |
| 16 | `land.US.preisniveau`* | Aggregat | Datenanker(15) | 5 | — |
| 17 | `land.US.inflation`* | Aggregat | Datenanker(8) | 3 | — |
| 18 | `land.US.leitzins` | Aggregat | Datenanker(9) | 3 | — |
| 19 | `land.US.wechselkurs` | Aggregat | Vorgabe(T46) | 6 | 10.000 |
| 20 | `land.US.staatsschuld`* | Aggregat | Datenanker(11) | 3 | — |
| 21 | `land.US.haushaltssaldo` | Aggregat | Datenanker(12) | 3 | — |
| 22 | `land.US.zustimmung`* | politisch | Parameter(startzustimmung*) | 4 | — |
| 23 | `land.US.aufsichtszaehler` | politisch | Entwurf | 11 | 0 |
| 24 | `land.US.einfluss`* | politisch | Entwurf | 4 | 0 |
| 25 | `land.US.instrument.leitzins.stand` | Instrumente | Datenanker(9) | 3 | — |
| 26 | `land.US.instrument.leitzins.druck` | Instrumente | Entwurf | 9 | 0 |
| 27 | `land.US.instrument.leitzins.gegendruck`* | Instrumente | Entwurf | 9 | 0 |
| 28 | `land.US.instrument.leitzins.restverzoegerung`* | Instrumente | Entwurf | 11 | 0 |
| 29 | `land.US.instrument.zoll.stand` | Instrumente | Datenanker(13) | 3 | — |
| 30 | `land.US.instrument.zoll.druck` | Instrumente | Entwurf | 9 | 0 |
| 31 | `land.US.instrument.zoll.gegendruck`* | Instrumente | Entwurf | 9 | 0 |
| 32 | `land.US.instrument.zoll.restverzoegerung`* | Instrumente | Entwurf | 11 | 0 |
| 33 | `land.US.instrument.haushalt.stand` | Instrumente | Datenanker(12) | 3 | — |
| 34 | `land.US.instrument.haushalt.druck` | Instrumente | Entwurf | 9 | 0 |
| 35 | `land.US.instrument.haushalt.gegendruck`* | Instrumente | Entwurf | 9 | 0 |
| 36 | `land.US.instrument.haushalt.restverzoegerung`* | Instrumente | Entwurf | 11 | 0 |
| 37 | `land.US.instrument.regulierung.stand`* | Instrumente | Parameter(regulierung_start*) | 10 | — |
| 38 | `land.US.instrument.regulierung.druck`* | Instrumente | Entwurf | 9 | 0 |
| 39 | `land.US.instrument.regulierung.gegendruck`* | Instrumente | Entwurf | 9 | 0 |
| 40 | `land.US.instrument.regulierung.restverzoegerung`* | Instrumente | Entwurf | 11 | 0 |
| 41 | `land.US.marktverbot_rest`* | Restdauern | Entwurf | 11 | 0 |
| 42 | `land.US.lobbykosten_rest`* | Restdauern | Entwurf | 11 | 0 |
| 43 | `land.US.regierungsdruck_rest`* | Restdauern | Entwurf | 11 | 0 |
| 44 | `land.US.basiswechsel`* | Buchhaltung | Vorgabe(T46) | 11 | 0 |
| 45 | `land.CN.sektor.1.wertschoepfung` | je Sektor | Datenanker(1 × 2) | 2 | — |
| 46 | `land.CN.sektor.1.kapitalstock` | je Sektor | Datenanker(3 × 2) | 2 | — |
| 47 | `land.CN.sektor.1.beschaeftigung` | je Sektor | Datenanker(7) | 8 | — |
| 48 | `land.CN.sektor.1.preis` | je Sektor | Entwurf | 5 | 10.000 |
| 49 | `land.CN.sektor.2.wertschoepfung` | je Sektor | Datenanker(1 × 2) | 2 | — |
| 50 | `land.CN.sektor.2.kapitalstock` | je Sektor | Datenanker(3 × 2) | 2 | — |
| 51 | `land.CN.sektor.2.beschaeftigung` | je Sektor | Datenanker(7) | 8 | — |
| 52 | `land.CN.sektor.2.preis` | je Sektor | Entwurf | 5 | 10.000 |
| 53 | `land.CN.sektor.3.wertschoepfung` | je Sektor | Datenanker(1 × 2) | 2 | — |
| 54 | `land.CN.sektor.3.kapitalstock` | je Sektor | Datenanker(3 × 2) | 2 | — |
| 55 | `land.CN.sektor.3.beschaeftigung` | je Sektor | Datenanker(7) | 8 | — |
| 56 | `land.CN.sektor.3.preis` | je Sektor | Entwurf | 5 | 10.000 |
| 57 | `land.CN.bevoelkerung`* | Aggregat | Datenanker(5) | 8 | — |
| 58 | `land.CN.erwerbstaetige`* | Aggregat | Datenanker(6) | 8 | — |
| 59 | `land.CN.produktivitaet`* | Aggregat | Datenanker(4) | 7 | — |
| 60 | `land.CN.preisniveau`* | Aggregat | Datenanker(15) | 5 | — |
| 61 | `land.CN.inflation`* | Aggregat | Datenanker(8) | 3 | — |
| 62 | `land.CN.leitzins` | Aggregat | Datenanker(9) | 3 | — |
| 63 | `land.CN.wechselkurs`* | Aggregat | Datenanker(10) | 6 | — |
| 64 | `land.CN.staatsschuld`* | Aggregat | Datenanker(11) | 3 | — |
| 65 | `land.CN.haushaltssaldo` | Aggregat | Datenanker(12) | 3 | — |
| 66 | `land.CN.zustimmung`* | politisch | Parameter(startzustimmung*) | 4 | — |
| 67 | `land.CN.aufsichtszaehler` | politisch | Entwurf | 11 | 0 |
| 68 | `land.CN.einfluss`* | politisch | Entwurf | 4 | 0 |
| 69 | `land.CN.instrument.leitzins.stand` | Instrumente | Datenanker(9) | 3 | — |
| 70 | `land.CN.instrument.leitzins.druck` | Instrumente | Entwurf | 9 | 0 |
| 71 | `land.CN.instrument.leitzins.gegendruck`* | Instrumente | Entwurf | 9 | 0 |
| 72 | `land.CN.instrument.leitzins.restverzoegerung`* | Instrumente | Entwurf | 11 | 0 |
| 73 | `land.CN.instrument.zoll.stand` | Instrumente | Datenanker(13) | 3 | — |
| 74 | `land.CN.instrument.zoll.druck` | Instrumente | Entwurf | 9 | 0 |
| 75 | `land.CN.instrument.zoll.gegendruck`* | Instrumente | Entwurf | 9 | 0 |
| 76 | `land.CN.instrument.zoll.restverzoegerung`* | Instrumente | Entwurf | 11 | 0 |
| 77 | `land.CN.instrument.haushalt.stand` | Instrumente | Datenanker(12) | 3 | — |
| 78 | `land.CN.instrument.haushalt.druck` | Instrumente | Entwurf | 9 | 0 |
| 79 | `land.CN.instrument.haushalt.gegendruck`* | Instrumente | Entwurf | 9 | 0 |
| 80 | `land.CN.instrument.haushalt.restverzoegerung`* | Instrumente | Entwurf | 11 | 0 |
| 81 | `land.CN.instrument.regulierung.stand`* | Instrumente | Parameter(regulierung_start*) | 10 | — |
| 82 | `land.CN.instrument.regulierung.druck`* | Instrumente | Entwurf | 9 | 0 |
| 83 | `land.CN.instrument.regulierung.gegendruck`* | Instrumente | Entwurf | 9 | 0 |
| 84 | `land.CN.instrument.regulierung.restverzoegerung`* | Instrumente | Entwurf | 11 | 0 |
| 85 | `land.CN.marktverbot_rest`* | Restdauern | Entwurf | 11 | 0 |
| 86 | `land.CN.lobbykosten_rest`* | Restdauern | Entwurf | 11 | 0 |
| 87 | `land.CN.regierungsdruck_rest`* | Restdauern | Entwurf | 11 | 0 |
| 88 | `land.CN.basiswechsel`* | Buchhaltung | Vorgabe(T46) | 11 | 0 |
| 89 | `land.DE.sektor.1.wertschoepfung` | je Sektor | Datenanker(1 × 2) | 2 | — |
| 90 | `land.DE.sektor.1.kapitalstock` | je Sektor | Datenanker(3 × 2) | 2 | — |
| 91 | `land.DE.sektor.1.beschaeftigung` | je Sektor | Datenanker(7) | 8 | — |
| 92 | `land.DE.sektor.1.preis` | je Sektor | Entwurf | 5 | 10.000 |
| 93 | `land.DE.sektor.2.wertschoepfung` | je Sektor | Datenanker(1 × 2) | 2 | — |
| 94 | `land.DE.sektor.2.kapitalstock` | je Sektor | Datenanker(3 × 2) | 2 | — |
| 95 | `land.DE.sektor.2.beschaeftigung` | je Sektor | Datenanker(7) | 8 | — |
| 96 | `land.DE.sektor.2.preis` | je Sektor | Entwurf | 5 | 10.000 |
| 97 | `land.DE.sektor.3.wertschoepfung` | je Sektor | Datenanker(1 × 2) | 2 | — |
| 98 | `land.DE.sektor.3.kapitalstock` | je Sektor | Datenanker(3 × 2) | 2 | — |
| 99 | `land.DE.sektor.3.beschaeftigung` | je Sektor | Datenanker(7) | 8 | — |
| 100 | `land.DE.sektor.3.preis` | je Sektor | Entwurf | 5 | 10.000 |
| 101 | `land.DE.bevoelkerung`* | Aggregat | Datenanker(5) | 8 | — |
| 102 | `land.DE.erwerbstaetige`* | Aggregat | Datenanker(6) | 8 | — |
| 103 | `land.DE.produktivitaet`* | Aggregat | Datenanker(4) | 7 | — |
| 104 | `land.DE.preisniveau`* | Aggregat | Datenanker(15) | 5 | — |
| 105 | `land.DE.inflation`* | Aggregat | Datenanker(8) | 3 | — |
| 106 | `land.DE.leitzins` | Aggregat | Datenanker(9) | 3 | — |
| 107 | `land.DE.wechselkurs`* | Aggregat | Datenanker(10) | 6 | — |
| 108 | `land.DE.staatsschuld`* | Aggregat | Datenanker(11) | 3 | — |
| 109 | `land.DE.haushaltssaldo` | Aggregat | Datenanker(12) | 3 | — |
| 110 | `land.DE.zustimmung`* | politisch | Parameter(startzustimmung*) | 4 | — |
| 111 | `land.DE.aufsichtszaehler` | politisch | Entwurf | 11 | 0 |
| 112 | `land.DE.einfluss`* | politisch | Entwurf | 4 | 0 |
| 113 | `land.DE.instrument.leitzins.stand` | Instrumente | Datenanker(9) | 3 | — |
| 114 | `land.DE.instrument.leitzins.druck` | Instrumente | Entwurf | 9 | 0 |
| 115 | `land.DE.instrument.leitzins.gegendruck`* | Instrumente | Entwurf | 9 | 0 |
| 116 | `land.DE.instrument.leitzins.restverzoegerung`* | Instrumente | Entwurf | 11 | 0 |
| 117 | `land.DE.instrument.zoll.stand` | Instrumente | Datenanker(13) | 3 | — |
| 118 | `land.DE.instrument.zoll.druck` | Instrumente | Entwurf | 9 | 0 |
| 119 | `land.DE.instrument.zoll.gegendruck`* | Instrumente | Entwurf | 9 | 0 |
| 120 | `land.DE.instrument.zoll.restverzoegerung`* | Instrumente | Entwurf | 11 | 0 |
| 121 | `land.DE.instrument.haushalt.stand` | Instrumente | Datenanker(12) | 3 | — |
| 122 | `land.DE.instrument.haushalt.druck` | Instrumente | Entwurf | 9 | 0 |
| 123 | `land.DE.instrument.haushalt.gegendruck`* | Instrumente | Entwurf | 9 | 0 |
| 124 | `land.DE.instrument.haushalt.restverzoegerung`* | Instrumente | Entwurf | 11 | 0 |
| 125 | `land.DE.instrument.regulierung.stand`* | Instrumente | Parameter(regulierung_start*) | 10 | — |
| 126 | `land.DE.instrument.regulierung.druck`* | Instrumente | Entwurf | 9 | 0 |
| 127 | `land.DE.instrument.regulierung.gegendruck`* | Instrumente | Entwurf | 9 | 0 |
| 128 | `land.DE.instrument.regulierung.restverzoegerung`* | Instrumente | Entwurf | 11 | 0 |
| 129 | `land.DE.marktverbot_rest`* | Restdauern | Entwurf | 11 | 0 |
| 130 | `land.DE.lobbykosten_rest`* | Restdauern | Entwurf | 11 | 0 |
| 131 | `land.DE.regierungsdruck_rest`* | Restdauern | Entwurf | 11 | 0 |
| 132 | `land.DE.basiswechsel`* | Buchhaltung | Vorgabe(T46) | 11 | 0 |
| 133 | `land.BR.sektor.1.wertschoepfung` | je Sektor | Datenanker(1 × 2) | 2 | — |
| 134 | `land.BR.sektor.1.kapitalstock` | je Sektor | Datenanker(3 × 2) | 2 | — |
| 135 | `land.BR.sektor.1.beschaeftigung` | je Sektor | Datenanker(7) | 8 | — |
| 136 | `land.BR.sektor.1.preis` | je Sektor | Entwurf | 5 | 10.000 |
| 137 | `land.BR.sektor.2.wertschoepfung` | je Sektor | Datenanker(1 × 2) | 2 | — |
| 138 | `land.BR.sektor.2.kapitalstock` | je Sektor | Datenanker(3 × 2) | 2 | — |
| 139 | `land.BR.sektor.2.beschaeftigung` | je Sektor | Datenanker(7) | 8 | — |
| 140 | `land.BR.sektor.2.preis` | je Sektor | Entwurf | 5 | 10.000 |
| 141 | `land.BR.sektor.3.wertschoepfung` | je Sektor | Datenanker(1 × 2) | 2 | — |
| 142 | `land.BR.sektor.3.kapitalstock` | je Sektor | Datenanker(3 × 2) | 2 | — |
| 143 | `land.BR.sektor.3.beschaeftigung` | je Sektor | Datenanker(7) | 8 | — |
| 144 | `land.BR.sektor.3.preis` | je Sektor | Entwurf | 5 | 10.000 |
| 145 | `land.BR.bevoelkerung`* | Aggregat | Datenanker(5) | 8 | — |
| 146 | `land.BR.erwerbstaetige`* | Aggregat | Datenanker(6) | 8 | — |
| 147 | `land.BR.produktivitaet`* | Aggregat | Datenanker(4) | 7 | — |
| 148 | `land.BR.preisniveau`* | Aggregat | Datenanker(15) | 5 | — |
| 149 | `land.BR.inflation`* | Aggregat | Datenanker(8) | 3 | — |
| 150 | `land.BR.leitzins` | Aggregat | Datenanker(9) | 3 | — |
| 151 | `land.BR.wechselkurs`* | Aggregat | Datenanker(10) | 6 | — |
| 152 | `land.BR.staatsschuld`* | Aggregat | Datenanker(11) | 3 | — |
| 153 | `land.BR.haushaltssaldo` | Aggregat | Datenanker(12) | 3 | — |
| 154 | `land.BR.zustimmung`* | politisch | Parameter(startzustimmung*) | 4 | — |
| 155 | `land.BR.aufsichtszaehler` | politisch | Entwurf | 11 | 0 |
| 156 | `land.BR.einfluss`* | politisch | Entwurf | 4 | 0 |
| 157 | `land.BR.instrument.leitzins.stand` | Instrumente | Datenanker(9) | 3 | — |
| 158 | `land.BR.instrument.leitzins.druck` | Instrumente | Entwurf | 9 | 0 |
| 159 | `land.BR.instrument.leitzins.gegendruck`* | Instrumente | Entwurf | 9 | 0 |
| 160 | `land.BR.instrument.leitzins.restverzoegerung`* | Instrumente | Entwurf | 11 | 0 |
| 161 | `land.BR.instrument.zoll.stand` | Instrumente | Datenanker(13) | 3 | — |
| 162 | `land.BR.instrument.zoll.druck` | Instrumente | Entwurf | 9 | 0 |
| 163 | `land.BR.instrument.zoll.gegendruck`* | Instrumente | Entwurf | 9 | 0 |
| 164 | `land.BR.instrument.zoll.restverzoegerung`* | Instrumente | Entwurf | 11 | 0 |
| 165 | `land.BR.instrument.haushalt.stand` | Instrumente | Datenanker(12) | 3 | — |
| 166 | `land.BR.instrument.haushalt.druck` | Instrumente | Entwurf | 9 | 0 |
| 167 | `land.BR.instrument.haushalt.gegendruck`* | Instrumente | Entwurf | 9 | 0 |
| 168 | `land.BR.instrument.haushalt.restverzoegerung`* | Instrumente | Entwurf | 11 | 0 |
| 169 | `land.BR.instrument.regulierung.stand`* | Instrumente | Parameter(regulierung_start*) | 10 | — |
| 170 | `land.BR.instrument.regulierung.druck`* | Instrumente | Entwurf | 9 | 0 |
| 171 | `land.BR.instrument.regulierung.gegendruck`* | Instrumente | Entwurf | 9 | 0 |
| 172 | `land.BR.instrument.regulierung.restverzoegerung`* | Instrumente | Entwurf | 11 | 0 |
| 173 | `land.BR.marktverbot_rest`* | Restdauern | Entwurf | 11 | 0 |
| 174 | `land.BR.lobbykosten_rest`* | Restdauern | Entwurf | 11 | 0 |
| 175 | `land.BR.regierungsdruck_rest`* | Restdauern | Entwurf | 11 | 0 |
| 176 | `land.BR.basiswechsel`* | Buchhaltung | Vorgabe(T46) | 11 | 0 |
| 177 | `restwelt.sektor.1.wertschoepfung`* | Restwelt | Datenanker(1 × 2) | 2 | — |
| 178 | `restwelt.sektor.1.kapitalstock`* | Restwelt | Datenanker(3 × 2) | 2 | — |
| 179 | `restwelt.sektor.1.beschaeftigung`* | Restwelt | Datenanker(7) | 8 | — |
| 180 | `restwelt.sektor.1.preis`* | Restwelt | Entwurf | 5 | 10.000 |
| 181 | `restwelt.sektor.2.wertschoepfung`* | Restwelt | Datenanker(1 × 2) | 2 | — |
| 182 | `restwelt.sektor.2.kapitalstock`* | Restwelt | Datenanker(3 × 2) | 2 | — |
| 183 | `restwelt.sektor.2.beschaeftigung`* | Restwelt | Datenanker(7) | 8 | — |
| 184 | `restwelt.sektor.2.preis`* | Restwelt | Entwurf | 5 | 10.000 |
| 185 | `restwelt.sektor.3.wertschoepfung`* | Restwelt | Datenanker(1 × 2) | 2 | — |
| 186 | `restwelt.sektor.3.kapitalstock`* | Restwelt | Datenanker(3 × 2) | 2 | — |
| 187 | `restwelt.sektor.3.beschaeftigung`* | Restwelt | Datenanker(7) | 8 | — |
| 188 | `restwelt.sektor.3.preis`* | Restwelt | Entwurf | 5 | 10.000 |
| 189 | `restwelt.bevoelkerung`* | Restwelt | Datenanker(5) | 8 | — |
| 190 | `restwelt.erwerbstaetige`* | Restwelt | Datenanker(6) | 8 | — |
| 191 | `restwelt.produktivitaet`* | Restwelt | Datenanker(4) | 7 | — |
| 192 | `restwelt.preisniveau` | Restwelt | Datenanker(15) | 5 | — |
| 193 | `restwelt.inflation` | Restwelt | Vorgabe(T46) | 3 | 0 |
| 194 | `restwelt.leitzins` | Restwelt | Vorgabe(T46) | 3 | 0 |
| 195 | `restwelt.wechselkurs` | Restwelt | Vorgabe(T46) | 6 | 10.000 |
| 196 | `restwelt.staatsschuld` | Restwelt | Vorgabe(T46) | 3 | 0 |
| 197 | `restwelt.haushaltssaldo` | Restwelt | Vorgabe(T46) | 3 | 0 |
| 198 | `restwelt.basiswechsel` | Restwelt | Vorgabe(T46) | 11 | 0 |
| 199 | `handel.US.CN.1` | Handel | Datenanker(14) | 2 | — |
| 200 | `handel.US.CN.2` | Handel | Datenanker(14) | 2 | — |
| 201 | `handel.US.DE.1` | Handel | Datenanker(14) | 2 | — |
| 202 | `handel.US.DE.2` | Handel | Datenanker(14) | 2 | — |
| 203 | `handel.US.BR.1` | Handel | Datenanker(14) | 2 | — |
| 204 | `handel.US.BR.2` | Handel | Datenanker(14) | 2 | — |
| 205 | `handel.US.RW.1`* | Handel | Datenanker(14) | 2 | — |
| 206 | `handel.US.RW.2`* | Handel | Datenanker(14) | 2 | — |
| 207 | `handel.CN.US.1` | Handel | Datenanker(14) | 2 | — |
| 208 | `handel.CN.US.2` | Handel | Datenanker(14) | 2 | — |
| 209 | `handel.CN.DE.1` | Handel | Datenanker(14) | 2 | — |
| 210 | `handel.CN.DE.2` | Handel | Datenanker(14) | 2 | — |
| 211 | `handel.CN.BR.1` | Handel | Datenanker(14) | 2 | — |
| 212 | `handel.CN.BR.2` | Handel | Datenanker(14) | 2 | — |
| 213 | `handel.CN.RW.1`* | Handel | Datenanker(14) | 2 | — |
| 214 | `handel.CN.RW.2`* | Handel | Datenanker(14) | 2 | — |
| 215 | `handel.DE.US.1` | Handel | Datenanker(14) | 2 | — |
| 216 | `handel.DE.US.2` | Handel | Datenanker(14) | 2 | — |
| 217 | `handel.DE.CN.1` | Handel | Datenanker(14) | 2 | — |
| 218 | `handel.DE.CN.2` | Handel | Datenanker(14) | 2 | — |
| 219 | `handel.DE.BR.1` | Handel | Datenanker(14) | 2 | — |
| 220 | `handel.DE.BR.2` | Handel | Datenanker(14) | 2 | — |
| 221 | `handel.DE.RW.1`* | Handel | Datenanker(14) | 2 | — |
| 222 | `handel.DE.RW.2`* | Handel | Datenanker(14) | 2 | — |
| 223 | `handel.BR.US.1` | Handel | Datenanker(14) | 2 | — |
| 224 | `handel.BR.US.2` | Handel | Datenanker(14) | 2 | — |
| 225 | `handel.BR.CN.1` | Handel | Datenanker(14) | 2 | — |
| 226 | `handel.BR.CN.2` | Handel | Datenanker(14) | 2 | — |
| 227 | `handel.BR.DE.1` | Handel | Datenanker(14) | 2 | — |
| 228 | `handel.BR.DE.2` | Handel | Datenanker(14) | 2 | — |
| 229 | `handel.BR.RW.1`* | Handel | Datenanker(14) | 2 | — |
| 230 | `handel.BR.RW.2`* | Handel | Datenanker(14) | 2 | — |
| 231 | `handel.RW.US.1`* | Handel | Datenanker(14) | 2 | — |
| 232 | `handel.RW.US.2`* | Handel | Datenanker(14) | 2 | — |
| 233 | `handel.RW.CN.1`* | Handel | Datenanker(14) | 2 | — |
| 234 | `handel.RW.CN.2`* | Handel | Datenanker(14) | 2 | — |
| 235 | `handel.RW.DE.1`* | Handel | Datenanker(14) | 2 | — |
| 236 | `handel.RW.DE.2`* | Handel | Datenanker(14) | 2 | — |
| 237 | `handel.RW.BR.1`* | Handel | Datenanker(14) | 2 | — |
| 238 | `handel.RW.BR.2`* | Handel | Datenanker(14) | 2 | — |
| 239 | `welt.preis.1`* | Weltpreise | Entwurf | 5 | 10.000 |
| 240 | `welt.preis.2`* | Weltpreise | Entwurf | 5 | 10.000 |
| 241 | `fonds.nachahmer.US.1`* | Nachahmerzähler | Entwurf | 11 | 0 |
| 242 | `fonds.nachahmer.US.2`* | Nachahmerzähler | Entwurf | 11 | 0 |
| 243 | `fonds.nachahmer.US.3`* | Nachahmerzähler | Entwurf | 11 | 0 |
| 244 | `fonds.nachahmer.CN.1`* | Nachahmerzähler | Entwurf | 11 | 0 |
| 245 | `fonds.nachahmer.CN.2`* | Nachahmerzähler | Entwurf | 11 | 0 |
| 246 | `fonds.nachahmer.CN.3`* | Nachahmerzähler | Entwurf | 11 | 0 |
| 247 | `fonds.nachahmer.DE.1`* | Nachahmerzähler | Entwurf | 11 | 0 |
| 248 | `fonds.nachahmer.DE.2`* | Nachahmerzähler | Entwurf | 11 | 0 |
| 249 | `fonds.nachahmer.DE.3`* | Nachahmerzähler | Entwurf | 11 | 0 |
| 250 | `fonds.nachahmer.BR.1`* | Nachahmerzähler | Entwurf | 11 | 0 |
| 251 | `fonds.nachahmer.BR.2`* | Nachahmerzähler | Entwurf | 11 | 0 |
| 252 | `fonds.nachahmer.BR.3`* | Nachahmerzähler | Entwurf | 11 | 0 |
| 253 | `markt.wert` | Marktkorb | Manifest(marktkorb_start*) | 2 | — |
| 254 | `markt.rendite` | Marktkorb | Entwurf | 3 | 0 |
| 255 | `fonds.kasse` | Fonds, Aggregat | Parameter(startkapital) | 1 | — |
| 256 | `fonds.hebelstand`* | Fonds, Aggregat | Entwurf | 1 | 0 |
| 257 | `fonds.sichtbarkeit` | Fonds, Aggregat | Entwurf | 4 | 0 |
| 258 | `fonds.anlegerbestand`* | Fonds, Aggregat | Parameter(startkapital) | 1 | — |
| 259 | `fonds.marktanteil` | Fonds, Aggregat | Entwurf | 4 | 0 |
| 260 | `fonds.ueberrendite.1`* | Fonds, Überrendite | Entwurf | 3 | 0 |
| 261 | `fonds.ueberrendite.2`* | Fonds, Überrendite | Entwurf | 3 | 0 |
| 262 | `fonds.ueberrendite.3`* | Fonds, Überrendite | Entwurf | 3 | 0 |
| 263 | `fonds.position.US.1` | Positionssteckplätze | Entwurf | 11 | 0 |
| 264 | `fonds.position.US.2` | Positionssteckplätze | Entwurf | 11 | 0 |
| 265 | `fonds.position.US.3` | Positionssteckplätze | Entwurf | 11 | 0 |
| 266 | `fonds.position.CN.1` | Positionssteckplätze | Entwurf | 11 | 0 |
| 267 | `fonds.position.CN.2` | Positionssteckplätze | Entwurf | 11 | 0 |
| 268 | `fonds.position.CN.3` | Positionssteckplätze | Entwurf | 11 | 0 |
| 269 | `fonds.position.DE.1` | Positionssteckplätze | Entwurf | 11 | 0 |
| 270 | `fonds.position.DE.2` | Positionssteckplätze | Entwurf | 11 | 0 |
| 271 | `fonds.position.DE.3` | Positionssteckplätze | Entwurf | 11 | 0 |
| 272 | `fonds.position.BR.1` | Positionssteckplätze | Entwurf | 11 | 0 |
| 273 | `fonds.position.BR.2` | Positionssteckplätze | Entwurf | 11 | 0 |
| 274 | `fonds.position.BR.3` | Positionssteckplätze | Entwurf | 11 | 0 |
| 275 | `fonds.position.waehrung.US`* | Positionssteckplätze | Entwurf | 11 | 0 |
| 276 | `fonds.position.waehrung.CN`* | Positionssteckplätze | Entwurf | 11 | 0 |
| 277 | `fonds.position.waehrung.DE`* | Positionssteckplätze | Entwurf | 11 | 0 |
| 278 | `fonds.position.waehrung.BR`* | Positionssteckplätze | Entwurf | 11 | 0 |
| 279 | `fonds.position.anleihe.US`* | Positionssteckplätze | Entwurf | 11 | 0 |
| 280 | `fonds.position.anleihe.CN`* | Positionssteckplätze | Entwurf | 11 | 0 |
| 281 | `fonds.position.anleihe.DE`* | Positionssteckplätze | Entwurf | 11 | 0 |
| 282 | `fonds.position.anleihe.BR`* | Positionssteckplätze | Entwurf | 11 | 0 |
| 283 | `fonds.beteiligung.US.1.anteil`* | Beteiligungen | Entwurf | 4 | 0 |
| 284 | `fonds.beteiligung.US.1.restdauer`* | Beteiligungen | Entwurf | 11 | 0 |
| 285 | `fonds.beteiligung.US.2.anteil`* | Beteiligungen | Entwurf | 4 | 0 |
| 286 | `fonds.beteiligung.US.2.restdauer`* | Beteiligungen | Entwurf | 11 | 0 |
| 287 | `fonds.beteiligung.US.3.anteil`* | Beteiligungen | Entwurf | 4 | 0 |
| 288 | `fonds.beteiligung.US.3.restdauer`* | Beteiligungen | Entwurf | 11 | 0 |
| 289 | `fonds.beteiligung.CN.1.anteil`* | Beteiligungen | Entwurf | 4 | 0 |
| 290 | `fonds.beteiligung.CN.1.restdauer`* | Beteiligungen | Entwurf | 11 | 0 |
| 291 | `fonds.beteiligung.CN.2.anteil`* | Beteiligungen | Entwurf | 4 | 0 |
| 292 | `fonds.beteiligung.CN.2.restdauer`* | Beteiligungen | Entwurf | 11 | 0 |
| 293 | `fonds.beteiligung.CN.3.anteil`* | Beteiligungen | Entwurf | 4 | 0 |
| 294 | `fonds.beteiligung.CN.3.restdauer`* | Beteiligungen | Entwurf | 11 | 0 |
| 295 | `fonds.beteiligung.DE.1.anteil`* | Beteiligungen | Entwurf | 4 | 0 |
| 296 | `fonds.beteiligung.DE.1.restdauer`* | Beteiligungen | Entwurf | 11 | 0 |
| 297 | `fonds.beteiligung.DE.2.anteil`* | Beteiligungen | Entwurf | 4 | 0 |
| 298 | `fonds.beteiligung.DE.2.restdauer`* | Beteiligungen | Entwurf | 11 | 0 |
| 299 | `fonds.beteiligung.DE.3.anteil`* | Beteiligungen | Entwurf | 4 | 0 |
| 300 | `fonds.beteiligung.DE.3.restdauer`* | Beteiligungen | Entwurf | 11 | 0 |
| 301 | `fonds.beteiligung.BR.1.anteil`* | Beteiligungen | Entwurf | 4 | 0 |
| 302 | `fonds.beteiligung.BR.1.restdauer`* | Beteiligungen | Entwurf | 11 | 0 |
| 303 | `fonds.beteiligung.BR.2.anteil`* | Beteiligungen | Entwurf | 4 | 0 |
| 304 | `fonds.beteiligung.BR.2.restdauer`* | Beteiligungen | Entwurf | 11 | 0 |
| 305 | `fonds.beteiligung.BR.3.anteil`* | Beteiligungen | Entwurf | 4 | 0 |
| 306 | `fonds.beteiligung.BR.3.restdauer`* | Beteiligungen | Entwurf | 11 | 0 |
| 307 | `partie.runde`* | Partie | Entwurf | 11 | 0 |
| 308 | `partie.jahrgang_id`* | Partie | Manifest(jahrgang_id) | 12 | — |
| 309 | `partie.parameter_pruefsumme`* | Partie | Parameter(Prüfsumme des Satzes) | 12 | — |
| 310 | `partie.mandatsstand`* | Partie | Entwurf | 11 | 0 |

## Die vier Zählungen

### 1. 310 Zeilen, keine Adresse zweimal

Die laufende Nummer endet auf 310. Doppelte sind ausgeschlossen, weil jede Adresse aus
einem Gebiets-, Sektor-, Instrumenten- oder Steckplatzindex besteht und jede Kombination
genau einmal aufgeschrieben ist; die vier Blöcke haben verschiedene Präfixe
(`land.`, `restwelt.`, `handel.`, `welt.`, `markt.`, `fonds.`, `partie.`), können sich
also nicht überschneiden.

### 2. Nach Gruppe: 198 + 56 + 52 + 4 = 310

| Gruppe (T15) | Zeilen | Nummern |
|---|---:|---|
| je Sektor | 48 | 4 × 12 |
| Aggregat | 36 | 4 × 9 |
| politisch | 12 | 4 × 3 |
| Instrumente | 64 | 4 × 16 |
| Restdauern | 12 | 4 × 3 |
| Buchhaltung | 4 | 4 × 1 |
| Restwelt | 22 | 177–198 |
| **Gebiete** | **198** | `4 × 44 + 22` |
| Handel | 40 | 199–238 |
| Weltpreise | 2 | 239–240 |
| Nachahmerzähler | 12 | 241–252 |
| Marktkorb | 2 | 253–254 |
| **Welt** | **56** | `40 + 2 + 12 + 2` |
| Fonds, Aggregat | 5 | 255–259 |
| Fonds, Überrendite | 3 | 260–262 |
| Positionssteckplätze | 20 | 263–282 |
| Beteiligungen | 24 | 283–306 |
| **Fonds** | **52** | `5 + 3 + 20 + 24` |
| **Partie** | **4** | 307–310 |
| **Summe** | **310** | |

### 3. Nach Herkunft: 136 + 150 + 11 + 2 + 11 = 310

| Eintrag | Zeilen | Zerlegung |
|---|---:|---|
| `Datenanker` | 136 | `3 × 21` (CN, DE, BR) `+ 20` (US, Wechselkurs fällt in die Vorgabe) `+ 13` (Restwelt) `+ 40` (Handel) `= 83 + 13 + 40` |
| `Entwurf` | 150 | `4 × 20 + 3 + 2 + 12 + 1 + 6 + 24 + 20 + 2` |
| `Parameter` | 11 | `4 × 2 + 3` |
| `Manifest` | 2 | 253, 308 |
| `Vorgabe` | 11 | 19, 44, 88, 132, 176, 193, 194, 195, 196, 197, 198 |
| **Summe** | **310** | |

**Die elf `Vorgabe`-Zeilen gegen T46, einzeln:**

| T46-Zeile | Zahl | hier |
|---|---:|---|
| `gebiet.<G>.basiswechsel`, alle fünf Gebiete | 5 | 44, 88, 132, 176, 198 |
| `land.US.wechselkurs` | 1 | 19 |
| `restwelt.leitzins`, `restwelt.staatsschuld`, `restwelt.haushaltssaldo` | 3 | 194, 196, 197 |
| `restwelt.wechselkurs` | 1 | 195 |
| `restwelt.inflation` | 1 | 193 |
| **Summe** | **11** | |

**Die elf `Parameter`-Zeilen, einzeln:**

| Adresse | Schlüssel | Zeile |
|---|---|---:|
| `land.<L>.zustimmung`, vier Länder | `startzustimmung`* | 22, 66, 110, 154 |
| `land.<L>.instrument.regulierung.stand`, vier Länder | `regulierung_start`* | 37, 81, 125, 169 |
| `fonds.kasse` | `startkapital` (so in T45) | 255 |
| `fonds.anlegerbestand` | `startkapital` (spiel.md, Zeile „Fondskasse, Anlegerbestand") | 258 |
| `partie.parameter_pruefsumme` | Prüfsumme des Satzes selbst (T45 „Prüfsummenfeld") | 309 |
| **Summe** | | **11** |

Die Zerlegung der 150 `Entwurf`-Zeilen entspricht der Aufzählung in T45 Zeile für Zeile:
`4 × 20` je spielbarem Land (3 Sektorpreise, Aufsichtszähler, Einfluss, 12 Druck-,
Gegendruck- und Restverzögerungsfelder, 3 Restdauern), `3` Restwelt-Sektorpreise,
`2` Weltpreise, `12` Nachahmer, `1` `markt.rendite`, `6` Fondsaggregate (Hebelstand,
Sichtbarkeit, Marktanteil, 3 Überrenditen — Kasse und Anlegerbestand sind `Parameter`),
`24` Beteiligungen, `20` Positionen, `2` (`partie.runde`, `partie.mandatsstand`).

### 4. Nach Klasse: 3 + 71 + 36 + 22 + 22 + 5 + 5 + 25 + 32 + 4 + 83 + 2 = 310

| K | Zeilen | Zerlegung |
|---:|---:|---|
| 1 | 3 | `fonds.kasse`, `fonds.hebelstand`, `fonds.anlegerbestand` |
| 2 | 71 | `4 × 6 + 6` (Restwelt) `+ 40` (Handel) `+ markt.wert` |
| 3 | 36 | `4 × 7 + 4` (Restwelt) `+ markt.rendite + 3` Überrenditen |
| 4 | 22 | `4 × 2 +` Sichtbarkeit `+` Marktanteil `+ 12` Beteiligungsanteile |
| 5 | 22 | `4 × 4 + 4` (Restwelt) `+ 2` Weltpreise |
| 6 | 5 | 4 Länderwechselkurse `+ restwelt.wechselkurs` |
| 7 | 5 | 4 Produktivitäten `+ restwelt.produktivitaet` |
| 8 | 25 | `4 × 5 + 5` (Restwelt) |
| 9 | 32 | `4 × 8` (je Land 4 Drücke, 4 Gegendrücke) |
| 10 | 4 | 4 × `instrument.regulierung.stand` |
| 11 | 83 | `4 × 9 + 1` (`restwelt.basiswechsel`) `+ 12` Nachahmer `+ 20` Stufen `+ 12` Beteiligungsrestdauern `+ partie.runde + partie.mandatsstand` |
| 12 | 2 | `partie.jahrgang_id`, `partie.parameter_pruefsumme` |
| **Summe** | **310** | |

**Je spielbarem Land, 6 + 5 + 4 + 1 + 7 + 1 + 2 + 8 + 1 + 9 = 44** (Zeilen 1–44 für die
USA, danach je 44):

| K | Zahl | welche |
|---:|---:|---|
| 2 | 6 | 3 Wertschöpfungen, 3 Kapitalstöcke |
| 8 | 5 | 3 Sektorbeschäftigungen, Bevölkerung, Erwerbstätige |
| 5 | 4 | 3 Sektorpreise, Preisniveau |
| 7 | 1 | Produktivität |
| 3 | 7 | Inflation, Leitzins, Staatsschuld, Haushaltssaldo, 3 Instrumentenstände (leitzins, zoll, haushalt) |
| 6 | 1 | Wechselkurs |
| 4 | 2 | Zustimmung, Einfluss |
| 9 | 8 | 4 Drücke, 4 Gegendrücke |
| 10 | 1 | Stand der Finanzmarktregulierung |
| 11 | 9 | Aufsichtszähler, 4 Restverzögerungen, 3 Restdauern, `basiswechsel` |
| **Summe** | **44** | |

**Die Restwelt, 22:** 6 (K 2), 5 (K 8), 4 (K 5), 1 (K 7), 4 (K 3), 1 (K 6), 1 (K 11) — wie
T49. Keine Instrumente, keine Zustimmung, kein Aufsichtszähler, kein Einfluss, keine
Restdauern.

## Die beiden Fälle aus dem Arbeitspaket

**Doppelt geführte Werte.** `land.<L>.leitzins` (18, 62, 106, 150) und
`land.<L>.instrument.leitzins.stand` (25, 69, 113, 157) stehen beide in der Tabelle, ebenso
`land.<L>.haushaltssaldo` (21, 65, 109, 153) und `land.<L>.instrument.haushalt.stand`
(33, 77, 121, 165). Beide Paare tragen denselben Herkunftseintrag, weil beide aus derselben
Reihe verankert werden — 9 für den Leitzins, 12 für den Haushaltssaldo. Das ist kein
zweiter Eintrag auf einer Adresse, sondern ein Eintrag auf zwei Adressen, und T45 verbietet
nur das erste. Die Schreibregel steht in T49 und ist hier nicht wiederholt.

**Scheinbar zwei Herkunftseinträge.** `markt.wert` (253) trägt `Manifest`, nicht `Entwurf`,
obwohl er in der Tabelle „Jede Größe ohne Datenanker" steht: Die Zeile dort schreibt keine
Zahl hin, sondern verweist auf den Startkorb zu Startpreisen, den der Jahrgangsbau rechnet
und im Manifest ausweist (T33 Punkt 2). Nach der Vorrangregel in T45 ist der Eintrag die
Stelle, die den Wert bestimmt. Dieselbe Regel trifft `land.<L>.zustimmung`,
`land.<L>.instrument.regulierung.stand`, `fonds.kasse`, `fonds.anlegerbestand` (alle
`Parameter`) und `partie.jahrgang_id` (`Manifest`).

## Befunde

Keine der vier Summen reisst. Was auffiel, sind zwei andere Dinge.

### Befund 1 — zwei Vorgaben schreiben denselben Adressteil verschieden

`technik.md` T23 Punkt 1 schreibt die Adresse der Restverzögerung als
`land.<L>.instrument.<I>.druck` **und** `…​.rest`; der letzte Bestandteil ist dort
literal `rest`. T15, T38 und T45 nennen dieselbe Größe durchgehend **Restverzögerung**, und
T23 selbst spricht im nächsten Satz von den „Druck- und Restverzögerungsadressen".

In diesem Verzeichnis steht `restverzoegerung` (Zeilen 28, 32, 36, 40 und je 4 weitere pro
Land). Grund: Es ist der Name, den vier Stellen tragen, gegen eine, und `rest` allein wäre
neben den drei Restdauerzählern (`marktverbot_rest`, `lobbykosten_rest`,
`regierungsdruck_rest`) mehrdeutig. **Das ist keine Entscheidung, die mir zusteht** — T17
macht jede Adresse zum Teil der Schnittstellenversion. Ich melde es; wer `rest` will,
braucht nach T17 einen ADR, und dann ist es eine Zeile in dieser Tabelle.

### Befund 2 — 177 der 310 Adressen sind gebildet, nicht zitiert

Nachzuzählen mit `grep -c '^| [0-9]* | `[^`]*`\* |' adressen.md` → 177; die übrigen 133
gehen auf eine wörtlich geschriebene Adresse zurück, nämlich die Beispiele aus T17, die
Beispiele aus T45, die elf aus T46, `markt.wert`, `markt.rendite`, `fonds.marktanteil`,
`fonds.sichtbarkeit`, `fonds.kasse`, das Leitzins- und das Haushaltspaar — und die daraus
über die Gebiets-, Sektor- und Instrumentenindizes gebildeten Geschwister, die deshalb
nicht markiert sind: Wo `land.DE.sektor.2.wertschoepfung` dasteht, ist
`land.BR.sektor.1.wertschoepfung` keine Wahl, sondern derselbe Index anders belegt.
**Ausgenommen sind die Adressen, deren Beleg in T46 steht**; warum, steht unter der Bildungsregeltabelle.

**Markiert ist alles, wo ein Bestandteil neu erfunden ist.** Die Bildungsregeln, damit der
Prüfer sie einzeln nachrechnen kann:

| Was | Muster | belegt durch |
|---|---|---|
| Gebietspräfix | `land.<L>.` für die vier spielbaren, `restwelt.` für die Restwelt | T17, T46 (`restwelt.leitzins`) |
| Restwelt im Handel | Gebietskennung `RW` | keine Vorlage; die Restwelt braucht in `handel.<G>.<H>.<s>` eine Kennung, und `restwelt` an dieser Stelle bräche das dreiteilige Muster aus T17 |
| Sektorgrößen | `.sektor.<s>.<groesse>` | T17 (`land.DE.sektor.2.preis`), T45 (`…wertschoepfung`) |
| Aggregatgrößen | `land.<L>.<groesse>` ohne Zwischenstufe | T46 (`restwelt.inflation`, `restwelt.preisniveau`), T45 (`land.CN.aufsichtszaehler`) |
| Instrumente | `land.<L>.instrument.<i>.<feld>` | T17, T23 Punkt 1 |
| Instrumentenkennung der Finanzmarktregulierung | `regulierung` | analog zu `leitzins`, `zoll`, `haushalt`; gestützt auf `regulierung_stufen` in T27 |
| Weltpreise | `welt.preis.<s>` | keine Vorlage; zweiteilig gewählt, weil kein Gebiet daran hängt |
| Nachahmer, Positionen, Beteiligungen | `fonds.<art>.<L>.<s>…` | T17 (`fonds.position.CN.1`); T15 führt alle drei unter „Der Fonds" |
| Steckplätze Währung und Anleihe | `fonds.position.waehrung.<L>`, `fonds.position.anleihe.<L>` | T16 (12 Land×Sektor, 4 Währung, 4 Anleihe); `waehrung`/`anleihe` an der Sektorstelle, weil dort sonst ein Index stünde, den es nicht gibt |
| Partie | `partie.<feld>` | T15; die Feldnamen `jahrgang_id` und `parameter_pruefsumme` aus T22 |

**Warum `land.US.sektor.1.preis` unmarkiert ist und `restwelt.sektor.1.preis` markiert.**
Die Marke sitzt an der Neuheit, nicht am Zitat: Beim Land sind Präfix und Sektorpfad
zusammen in T17 zu sehen, bei der Restwelt kommen die beiden Bestandteile in keinem
Dokument gemeinsam vor — T46 zeigt `restwelt.` nur mit Aggregatgrößen. Wer die Marke
enger oder weiter setzen will, ändert damit keine Adresse, sondern nur die Zahl 177.

**Warum `land.CN.wechselkurs` markiert ist und `land.DE.aufsichtszaehler` nicht.** Beide sind
Geschwister einer einzigen wörtlich belegten Adresse über den Gebietsindex; der Unterschied
liegt in der Stelle, die den Beleg trägt. T46 zählt seine elf Vorgabeadressen
**abschliessend** auf — die Überschrift der Tabelle sagt es selbst: „T46 — Die elf Adressen,
deren Herkunft dieses Dokument ist, abschliessend“ (`technik.md`; am 2026-09-03 Zeile 1219,
die Nummer ist nicht tragend) — und sagt zu `land.US.wechselkurs` sogar, warum
die drei anderen Länder nicht dazugehören („Reihe 10 trägt drei Länder, die USA
definitionsgemäß nicht"). **Ein Beleg, der in T46 steht, deckt deshalb nur die Adresse
selbst** — wer dort einen Index anders belegt, verlässt die Ausnahmeliste und bildet eine neue
Adresse. Das betrifft alle acht unmarkierten Zeilen, die ihren Beleg dort haben: Nr. 19
`land.US.wechselkurs` und die sieben Restweltzeilen 192 bis 198. Gemeint ist die Zeichenkette
und nicht die Herkunftsspalte — `restwelt.preisniveau` (192) steht in der Begründung zu
`restwelt.inflation` und trägt trotzdem `Datenanker(15)`. Ihre Ländergeschwister sind
deshalb markiert: die drei Wechselkurse (63, 107, 151), `land.<L>.preisniveau`
(16, 60, 104, 148), `land.<L>.inflation` (17, 61, 105, 149), `land.<L>.staatsschuld`
(20, 64, 108, 152) und die vier `land.<L>.basiswechsel` (44, 88, 132, 176), bei denen
zusätzlich der Präfix `gebiet.<G>.` in `land.<L>.` umgeschrieben ist. Zwei Geschwisterpaare
bleiben unmarkiert, und zwar nicht als Ausnahme: `land.<L>.leitzins` (18, 62, 106, 150) und
`land.<L>.haushaltssaldo` (21, 65, 109, 153) stehen mit Index in `technik.md` unter **T49**,
im Absatz „Zwei Adresspaare tragen denselben Wert, und das braucht eine Regel statt eines
Zufalls“ — im Wortlaut „`land.<L>.leitzins` und `land.<L>.instrument.leitzins.stand` sind
dieselbe Größe, ebenso `land.<L>.haushaltssaldo` und `land.<L>.instrument.haushalt.stand`“
(am 2026-09-03 Zeile 352 bis 354; die Nummern sind nicht tragend) —, und beziehen ihren Beleg
gar nicht aus T46. `land.CN.aufsichtszaehler` schliesslich steht
in T45 als **Beispiel** einer Kategorie von 150 Adressen und nicht als abschliessende Liste;
die drei übrigen Aufsichtszähler (23, 111, 155) bleiben deshalb unmarkiert.

**Die `basiswechsel`-Familie, alle fünf Zeilen an einer Stelle.** Sie ist der Fall, in dem
die beiden vorstehenden Sätze zusammen gelesen werden müssen — einzeln genommen ergibt jeder
für sich das falsche Ergebnis. `restwelt.basiswechsel` (198) ist **unmarkiert**, die vier
`land.<L>.basiswechsel` (44, 88, 132, 176) sind **markiert**, und die Zähltabelle oben
(*Die elf `Vorgabe`-Zeilen gegen T46*) ordnet alle fünf derselben T46-Zeile
`gebiet.<G>.basiswechsel` zu.

*Erstens, gemeint ist die Zeichenkette und nicht die Herkunftsspalte* (Satz oben zu Nr. 192).
Von den fünf Zeichenketten steht genau **eine** wörtlich in `specs/`: `restwelt.basiswechsel`
in `technik.md`, **T45**, Zeile `Vorgabe(T-Nummer)`, Spalte „Beispiel“ — die Zelle lautet
„`restwelt.basiswechsel` → 0 (T8)“. `land.US.basiswechsel` und seine drei Geschwister stehen
nirgends
— Volltextsuche über `specs/0016-…/` nach `basiswechsel` ergibt zehn Fundstellen, alle in
`technik.md`, davon genau zwei mit vollständiger Adresse: die eben genannte T45-Zelle und die
T46-Zeile, die mit „`gebiet.<G>.basiswechsel`, alle fünf Gebiete“ beginnt (am 2026-09-03
Zeile 1165 und 1228; die Nummern sind nicht tragend). Nr. 198 ist damit zitiert, die vier
anderen sind gebildet. Dass
alle fünf in der Herkunftsspalte `Vorgabe(T46)` tragen, ändert daran nichts; ebenso wenig wie
bei `restwelt.preisniveau` (192), das `Datenanker(15)` trägt.

*Zweitens, ein Beispiel erzeugt Geschwister, eine abschliessende Liste nicht* (Satz oben zu
`land.CN.aufsichtszaehler`). Die T45-Zeile `Vorgabe(T-Nummer)` steht in der Spalte
„Beispiel“, ist also dieselbe Bauart wie die T45-Zeile `Entwurf` — mit einem Unterschied in
der Bedeutungsspalte, und der entscheidet: `Vorgabe(T-Nummer)` verweist für seine Kategorie
ausdrücklich auf die abschliessende Liste („dieses Dokument, abschliessend aufgezählt in
**T46**“), `Entwurf` auf eine offene („die Tabelle ‚Jede Größe ohne Datenanker‘ in `spiel.md`
nennt einen **Zahlenwert**“, 150 Adressen). Das Beispiel der Zeile `Vorgabe(T-Nummer)` steht
folglich für die elf Zeilen aus T46 und für keine zwölfte; es erzeugt
keine unmarkierten Geschwister, und die vier gebildeten Zeilen tragen ihre Marke zu Recht.

| Adresse | Nr. | wörtlich in `specs/` | Fundstelle | Marke |
|---|---|---|---|---|
| `land.<L>.basiswechsel` | 44, 88, 132, 176 | nein | — | **je eine** |
| `restwelt.basiswechsel` | 198 | ja | `technik.md`, T45, Zeile `Vorgabe(T-Nummer)`, Spalte „Beispiel“: „`restwelt.basiswechsel` → 0 (T8)“ | keine |

**Gegenprobe, damit der Satz zur Zeile `Vorgabe(T-Nummer)` nichts anderes bewegt.** T45 hat
fünf Einträge — `Datenanker(nr)`, `Entwurf`, `Parameter(schluessel)`, `Manifest(feld)` und
`Vorgabe(T-Nummer)` —, und nur `Vorgabe(T-Nummer)` verweist für seine Kategorie auf eine
abschliessend aufgezählte **Adressliste**: `Datenanker(nr)` nennt „eine Reihe der Reihenliste
weiter unten“ — eine Liste von Reihen, keine von Adressen —, `Entwurf` die Entwurfstabelle in
`spiel.md` mit 150 Adressen, `Parameter(schluessel)` „`parameter.toml` nach T27“ und
`Manifest(feld)` das „vom Jahrgangsbau gerechnet und im Manifest ausgewiesen“. Die Beispiele
der übrigen vier
(`land.DE.sektor.2.wertschoepfung`, `land.CN.aufsichtszaehler`, `fonds.kasse`, `markt.wert`)
behalten damit die Lesart, die sie oben schon haben; die letzten beiden tragen ohnehin keinen
Index, über den sich ein Geschwister bilden liesse.

**Was hier offen bleibt und hier nicht entschieden wird.** Warum die Familie drei Präfixe
kennt — `gebiet.<G>.` in T46 gegen `land.<L>.` und `restwelt.` in dieser Tabelle —, ist
ungeklärt. Ob `gebiet.<G>.` für die beiden anderen zugleich steht, sagt dieses Verzeichnis
nicht; die Frage berührt `technik.md` und liegt beim Architekten. Sie ist hier ausdrücklich
**offen** und wird von diesem Verzeichnis nicht entschieden. Auch die Zuordnung
aller fünf Zeilen zur T46-Zeile `gebiet.<G>.basiswechsel` oben unter *Die elf `Vorgabe`-Zeilen
gegen T46* ist keine Antwort darauf: Sie sagt, aus welcher T46-Zeile der Herkunftseintrag
stammt, und nicht, dass ein Präfix für ein anderes steht. **Die Herleitung
oben hängt nicht daran**, denn sie fragt nur, ob eine Zeichenkette wörtlich belegt ist und ob
die belegende Stelle abschliessend aufzählt — nicht, wie ein Präfix zustande kommt. Beide
denkbaren Antworten ergeben dieselben Marken: Steht `gebiet.<G>.` für alle fünf Gebiete, sind
die vier `land.<L>.`-Zeilen anders belegte Indizes einer T46-Adresse und deshalb markiert
(Satz oben zu Nr. 19); steht es nicht dafür, sind sie ohne Vorlage gebildet und ebenfalls
markiert. Nr. 198 bleibt in beiden Fällen unmarkiert: Ihre Zeichenkette steht wörtlich in der
T45-Zeile `Vorgabe(T-Nummer)`, Spalte „Beispiel“ — und deckte T46 sie zusätzlich ab, so deckt
ein T46-Beleg die Adresse selbst, nur
eben keine Geschwister.

**Zwei Parameterschlüssel sind ebenfalls gebildet** und mit `*` markiert:
`startzustimmung` und `regulierung_start`. T27 nennt beide Größen („Startzustimmung",
„Startstand der Finanzmarktregulierung"), aber keinen Schlüsselnamen. Das gehört in Paket
**0009-parameterdatei-schluessel** und nicht hierher; weicht der dortige Name ab, sind es
zwei Zellen in dieser Tabelle und keine Adressänderung. Dasselbe gilt für
`marktkorb_start` (Zeile 253), das T33 nur als „im Manifest ausgewiesen" beschreibt.

## Namensnennung der Datenquellen

Die Herkunftsspalte verweist über `Datenanker(nr)` auf die Reihenliste in `technik.md`
Abschnitt 7. Die dort genannten Quellen und ihre Lizenzbedingungen stehen in
`specs/0016-hedgefonds-simulation-echte-weltwirtschaft/daten.md`; die Namensnennung gehört
nach der Auflage des Datenkurators ins Produkt und nicht in dieses Verzeichnis. Dieses
Dokument enthält keine Daten aus diesen Quellen, nur Verweise auf ihre Reihennummern.
