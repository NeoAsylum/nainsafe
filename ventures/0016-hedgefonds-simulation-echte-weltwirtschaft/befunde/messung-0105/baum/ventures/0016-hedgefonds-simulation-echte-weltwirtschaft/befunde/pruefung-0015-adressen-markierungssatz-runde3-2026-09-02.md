---
typ: pruefung
paket: 0015-adressen-markierungssatz
pruefer: daten-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Alle fünf genannten Gegenproben plus ein Vollabgleich der Markierungsregel gegen jede der 310 Tabellenzeilen und gegen jede wörtliche Adresse in `specs/`; die vier Zählungen an der Datei nachgezählt, die Tabellenzeilen als unverändert nachgewiesen.
befunde: 0
---

# Prüfung 0015, Runde 3 — die Markierungsregel trägt jetzt an der ganzen Tabelle

Geprüft wurde `daten/adressen.md` in der Fassung von HEAD (6b42df4). Die Änderung dieses
Rücklaufs steckt im Commit **e2383dd** mit fremdem Betreff („datenbauer:
0024-notenbanken-unter-reihe-2b"); der Commit mit dem Betreff „0015" (6b42df4) berührt die
Datei gar nicht. Der Betreff taugt hier nicht als Zuordnung, wie das Kriterium sagt.

## Punkt 1 — die beiden Stellen sagen dasselbe, und keine Regel entmarkiert eine Zeile

### a) Wortabgleich Zelle (Zeile 29) gegen *Befund 2* (Zeilen 504–556)

Sechs Aussagen, beide Stellen einzeln nachgelesen:

| Aussage | Zeile 29 | *Befund 2* |
|---|---|---|
| Marke = neuer Bestandteil **oder** undokumentierte Zusammensetzung | ja | Z. 515, 531–534 |
| unmarkiert = wörtlich belegt **plus** Geschwister (Richtung: unmarkiert ⇒ Geschwister) | ja | Z. 506–512 |
| Umkehrung gilt nicht: neuer Bestandteil ⇒ Geschwister markiert | ja (Nr. 180, Nr. 37) | Z. 531–535 |
| T46 zählt **elf** Adressen abschliessend, erzeugt keine unmarkierten Geschwister | ja | Z. 513, 539–544 |
| `wechselkurs` 63/107/151 markiert, `aufsichtszaehler` 23/111/155 nicht (T45 = Beispiel) | ja | Z. 548, 554–556 |
| eigener wörtlicher Beleg mit Index bleibt unberührt (`land.<L>.leitzins`) | ja | Z. 552–554 |

Keine Aussage der einen Stelle widerspricht der anderen. *Befund 2* führt zwei Punkte
weiter, die Zeile 29 nicht nennt (`land.<L>.haushaltssaldo` als zweites eigenbelegtes Paar;
„gemeint ist die Zeichenkette, nicht die Herkunftsspalte" für Nr. 192) — Zeile 29 verweist
dafür ausdrücklich dorthin („Die Bildungsregeln und die Gegenprobe an allen acht T46-Zeilen
stehen unter *Befund 2*"). Ergänzung ist kein Widerspruch.

Die drei Belegzitate der neuen Sätze am Quelltext nachgelesen und wörtlich bestätigt:
`technik.md` 874 („Die elf Adressen, deren Herkunft dieses Dokument ist, abschliessend"),
884 („Reihe 10 trägt drei Länder, die USA definitionsgemäß nicht"), 236/237
(`land.<L>.leitzins`, `land.<L>.haushaltssaldo` — mit Index, also alle vier Länder).

### b) Die fünf namentlich verlangten Gegenproben, einzeln durchgerechnet

- **Nr. 37 / Zeile 79** `land.US.instrument.regulierung.stand`\* — markiert. Elternadresse
  `land.BR.instrument.zoll.stand` (T17, `technik.md` 513–514). Eingesetzt ist die
  Instrumentenkennung `regulierung`; sie kommt in keiner wörtlichen Adresse in `specs/` vor
  (Vollsuche unten). Damit greift die Umkehrregel („Bestandteil selbst neu ⇒ markiert"),
  nicht die Geschwisterregel. Keine Stelle entmarkiert die Zeile. Gegenprobe intern: die
  drei belegten Instrumente (`…leitzins.stand` Nr. 25, `…zoll.stand` Nr. 29,
  `…haushalt.stand` Nr. 33) sind unmarkiert — dieselbe Regel, andere Seite.
- **Nr. 180 / Zeile 222** `restwelt.sektor.1.preis`\* — markiert. Gebildet aus
  `land.DE.sektor.2.preis` (T17). Zeile 29 nennt die Zeile ausdrücklich als markiert und
  qualifiziert den Grund („`restwelt.` **vor einem Sektorpfad**"), *Befund 2* Z. 531–534
  begründet ihn vollständig („T46 zeigt `restwelt.` nur mit Aggregatgrößen"). Kein
  Entmarkungspfad.
- **Nr. 63, 107, 151** `land.CN|DE|BR.wechselkurs`\* — markiert. Einziger wörtlicher Beleg
  der Familie ist `land.US.wechselkurs`, und der steht **nur** in `technik.md` 884, also in
  T46. Beide Stellen nennen die drei Zeilen namentlich als markiert. Geprüft, ob es einen
  zweiten, nicht-T46-Beleg gibt, aus dem eine Entmarkung folgen könnte: nein — Volltextsuche
  über `specs/` nach `land.<L>.wechselkurs`, `land.CN.wechselkurs`, `land.DE.wechselkurs`,
  `land.BR.wechselkurs` liefert null Treffer.

Zusätzlich wie verlangt: die **vier** `aufsichtszaehler`-Zeilen Nr. 23, 67, 111, 155 sind an
der Datei nachgesehen **alle unmarkiert** (Dateizeilen 65, 109, 153, 197); die drei
`wechselkurs`-Zeilen sind **alle markiert** (105, 149, 193). Nr. 67 ist die wörtlich belegte
(`technik.md` 817, T45-Spalte „Beispiel", Kategorie `Entwurf` mit 150 Adressen). Die
Elferliste aus T46 ist an beiden Stellen genannt.

### c) Vollabgleich statt Stichprobe

Weil beide bisherigen Rückläufe an einer sechsten, ungenannten Zeile hingen, habe ich diesmal
nicht nur die genannten Zeilen geprüft, sondern die Regel gegen **alle** wörtlichen Adressen
in `specs/` gelegt. Vollsuche über `specs/0016-…/` nach
`(land|restwelt|handel|welt|markt|fonds|partie|gebiet)\.…` ergibt genau diese wörtlichen
Adressen — mehr gibt es nicht:

- **nicht T46:** `land.<L>.leitzins`, `land.<L>.haushaltssaldo`,
  `land.<L>.instrument.leitzins.stand`, `land.<L>.instrument.haushalt.stand`,
  `land.<L>.instrument.<I>.druck` (712), `land.DE.sektor.2.preis`,
  `land.DE.sektor.2.wertschoepfung`, `land.BR.instrument.zoll.stand`, `land.CN.aufsichtszaehler`,
  `fonds.position.CN.1`, `handel.DE.CN.1`, `fonds.kasse`, `fonds.marktanteil`,
  `fonds.sichtbarkeit`, `markt.wert`, `markt.rendite`, `restwelt.basiswechsel` (820)
- **T46 (`technik.md` 883–887):** `gebiet.<G>.basiswechsel`, `land.US.wechselkurs`,
  `restwelt.leitzins`, `restwelt.staatsschuld`, `restwelt.haushaltssaldo`,
  `restwelt.wechselkurs`, `restwelt.inflation`, `restwelt.preisniveau`

Für jede dieser Adressen geprüft, welche Tabellenzeilen ihre Geschwister über Gebiets-,
Sektor- oder Instrumentenindex wären, und ob eine davon markiert ist. Ergebnis: **keine
markierte Zeile ist ein reines Indexgeschwister einer nicht-T46-Adresse.** Alle markierten
Familien haben einen benannten neuen Bestandteil oder eine undokumentierte Zusammensetzung —
`regulierung` (Instrumente), `RW` im Handel (Nr. 231–238, Bildungsregel Z. 521 „keine
Vorlage"), `welt.preis.<s>` (239–240, Z. 526), `restwelt.` vor Sektorpfad (177–191),
`gegendruck`/`restverzoegerung` (kein Beleg gegen `…druck` in 712), `nachahmer`/`beteiligung`
an der `<art>`-Stelle (241–252, 283–306), `waehrung`/`anleihe` an der Sektorstelle (275–282,
Z. 528) — und die `<art>`-Stelle ist keiner der drei Indizes, über die die Regel Geschwister
bildet.

## Punkt 2 — die vier Adressen aus dem Prüfbefund 0007

Alle vier an der Datei nachgesehen, alle vier **ohne Marke**, und für jede steht die
Begründung in der Datei:

| Nr. | Dateizeile | Adresse | Begründung in der Datei |
|---:|---:|---|---|
| 1 | 43 | `land.US.sektor.1.wertschoepfung` | *Befund 2* Z. 511–512, Bildungsregel Z. 522 (T45 `land.DE.sektor.2.wertschoepfung`) |
| 23 | 65 | `land.US.aufsichtszaehler` | Zeile 29 und *Befund 2* Z. 554–556 (T45 = Beispiel, keine abschliessende Liste) |
| 199 | 241 | `handel.US.CN.1` | Zeile 29 wörtlich (`handel.DE.CN.1` in T17) |
| 263 | 305 | `fonds.position.US.1` | Bildungsregel Z. 527 (T17 `fonds.position.CN.1`) |

## Punkt 3 — die Adresstabelle ist unverändert, die vier Zählungen gehen auf

**An der Datei gemessen**, wie das Kriterium verlangt (Zeilen 43–352, `Grep` auf das
Zeilenmuster; die Zeilenbereichs-Werkzeuge `sed`/`awk`/`wc` waren in diesem Lauf gesperrt,
Ersatz war der `Grep`-Zähler):

- **Zeilen:** 310 Tabellenzeilen, davon 177 mit `*` und 133 ohne — genau die Zahlen, die
  Zeile 29 („133 unmarkierten Zeilen") und *Befund 2* („177 … die übrigen 133") nennen.
- **Gruppe:** je Sektor 48 + Aggregat/politisch/Instrumente/Restdauern/Buchhaltung 128 +
  Restwelt 22 = **198**; Handel/Weltpreise/Nachahmer/Marktkorb = **56**; Fonds = **52**;
  Partie = **4**. Summe **310**.
- **Herkunft:** Datenanker 136, Entwurf 150, Parameter 11, Manifest 2, Vorgabe(T46) 11 = **310**.
- **Klasse:** K1 3, K2 71, K3 36, K4 22, K5 22, K6 5, K7 5, K8 25, K9 32, K10 4, K11 83,
  K12 2 = **310**. K4/K5, K6/K7 und K10/K11/K12 zusätzlich einzeln gezählt, nicht nur als
  Block.

Unabhängig davon bestätigt der Dateidiff (`git show e2383dd -- …/daten/adressen.md`, kein
`--stat`): genau drei Hunks, bei den Dateizeilen 29, 510 und 534 — alle **ausserhalb** des
Tabellenbereichs 43–352. Keine Tabellenzeile berührt.

## Punkt 4 — `parameter.toml`

`git log -- ventures/0016-…/parameter.toml` nennt als letzte Änderung **f0cae94**
(„datenbauer: 0009-parameterdatei-schluessel"). Der Commit dieses Rücklaufs (e2383dd) und der
Commit 6b42df4 berühren die Datei nicht; im Arbeitsverzeichnis ist sie sauber. Unberührt.

---

## Kein Rückgabegrund, aber eine Notiz an den Projektmanager

Die Regel trägt an allen 310 Zeilen — aber an **einer** Familie nur, wenn man zwei Sätze
kombiniert, die an verschiedenen Stellen stehen. Das ist dieselbe Bruchlinie wie in den
Rückläufen 1 und 2, und ich schreibe sie hin, damit sie nicht ein viertes Mal auftaucht:

`restwelt.basiswechsel` (Nr. 198) ist **unmarkiert**, die vier `land.<L>.basiswechsel`
(Nr. 44, 88, 132, 176) sind **markiert** — und die Zähltabelle der Datei selbst (Zeile 404)
ordnet **alle fünf** derselben T46-Zeile `gebiet.<G>.basiswechsel` zu. Nach dem Wortlaut
„ein Beleg, der in T46 steht, deckt nur die Adresse selbst" müssten damit auch Nr. 198
markiert sein; nach dem Wortlaut „T45 führt es als Beispiel" (`restwelt.basiswechsel` steht
wörtlich in `technik.md` 820, T45-Spalte „Beispiel") müssten umgekehrt Nr. 44/88/132/176
unmarkiert sein.

Auflösbar ist es, und zwar mit zwei Sätzen, die tatsächlich in der Datei stehen: „gemeint ist
die Zeichenkette und nicht die Herkunftsspalte" (*Befund 2* Z. 545) — `restwelt.basiswechsel`
steht wörtlich da, `land.US.basiswechsel` nirgends — und „Beispiel einer Kategorie von 150
Adressen **und nicht als abschliessende Liste**" (Zeile 29) — T45 Zeile 820 verweist für seine
Kategorie ausdrücklich auf die abschliessende Liste in T46, anders als Zeile 817. Beide Sätze
sind da, der Fall ist es nicht. **Das Kriterium ist damit erfüllt** (keine Stelle *stellt eine
Regel auf*, die eine markierte Zeile entmarkt), und ein Rücklauf brächte einen Halbsatz gegen
einen vierten Durchlauf.

Der Grund dahinter ist die schon zweimal gemeldete offene Frage `gebiet.<G>.` gegen
`land.<L>.`/`restwelt.`: Solange das Präfix ungeklärt ist, hat die basiswechsel-Familie keine
saubere Herleitung. Vorschlag: als Halbsatz in das Paket mitnehmen, das diese Frage entscheidet
(oder in ein 0007-Folgepaket), nicht als eigener Rücklauf auf 0015.
