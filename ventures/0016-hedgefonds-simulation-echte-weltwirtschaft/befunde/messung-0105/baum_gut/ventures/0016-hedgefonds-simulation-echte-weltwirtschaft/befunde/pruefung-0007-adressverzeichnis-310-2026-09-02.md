---
typ: pruefung
paket: 0007-adressverzeichnis-310
pruefer: daten-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: alle vier Zaehlungen erneut mit grep gegen die Tabelle geschnitten (310 Zeilen / 310 eindeutige Adressen / 310 eindeutige Nummern; Gruppen 48+36+12+64+12+4+22 = 198, 40+2+12+2 = 56, 5+3+20+24 = 52, 4; Herkunft 136/150/11/2/11; Klassen 3+71+36+22+22+5+5+25+32+4+83+2 sowie 44 je spielbarem Land und 22 fuer die Restwelt), dazu zwei vom Kriterium nicht verlangte Pruefungen: die Startwertregel in beide Richtungen (149 leer = genau Datenanker+Parameter+Manifest, 161 gefuellt = Entwurf+Vorgabe) und jeder Startwert gegen die Skala seiner Klasse nach T5
befunde: 2
---

# Prüfung des Adressverzeichnisses gegen `0007-adressverzeichnis-310`

Nicht gelesen: `notizen/datenbauer.md`.

**Vorbemerkung zur Wiederholung.** `daten/adressen.md` ist seit der Prüfung vom
2026-09-01 unverändert (`git status` meldet die Datei nicht als geändert; letzter
Commit an ihr ist `572358e`). Die vier Zählungen sind deshalb eine Wiederholung und
gehen erneut auf. Den Schwerpunkt dieses Laufs habe ich auf Prüfungen gelegt, die das
Abnahmekriterium **nicht** verlangt — dort liegt Befund 1.

**Ergebnis: Das Abnahmekriterium ist erfüllt.** Die Zählungen sind gegen die Tabelle
geschnitten, nicht gegen den Abschnitt *Die vier Zählungen*, in dem der Bauagent seine
Summen selbst hinschreibt.

## Was ich wie geprüft habe

**1. 310 Zeilen, keine Adresse zweimal.** `grep -cP '^\| *[0-9]+ \| `'` → 310;
dieselben Zeilen durch `sort -u` über die Adressspalte → 310; über die Nummernspalte
→ 310. Doppelte und Nummernlücken sind damit beide ausgeschlossen.

**2. Nach Gruppe.** Die sechzehn Gruppenbezeichner tragen die Zeilennamen aus T15:
`je Sektor` 48, `Aggregat` 36, `politisch` 12, `Instrumente` 64, `Restdauern` 12,
`Buchhaltung` 4, `Restwelt` 22 → **198**; `Handel` 40, `Weltpreise` 2,
`Nachahmerzähler` 12, `Marktkorb` 2 → **56**; `Fonds, Aggregat` 5,
`Fonds, Überrendite` 3, `Positionssteckplätze` 20, `Beteiligungen` 24 → **52**;
`Partie` **4**. Die Zuordnung der Gruppen zu den vier Blöcken ist gegen T15 Zeile 462–482
gelegt, nicht aus der Summe erschlossen: T15 gibt je spielbarem Land 12+9+3+16+3+1 = 44
und der Restwelt 12+9+1 = 22.

Weil eine Gesamtsumme die Teilsummen nicht erzwingt, zusätzlich je Präfix geschnitten:
`land.US|CN|DE|BR` je **44**, `restwelt` **22**, `handel.<G>` je 8 (5 × 8 = 40, Diagonale
fehlt korrekt), `fonds.*` 5+3+12+4+4+24+12 = 64, `partie.*` 4, `welt.preis.*` 2,
`markt.*` 2.

**3. Nach Herkunft.** `Datenanker` 136, `Entwurf` 150, `Vorgabe` 11, `Parameter` 11,
`Manifest` 2 = 310, wie T45. Die beiden abschliessend aufgezählten Listen Zeile für
Zeile nachgesehen:

- Die **elf `Vorgabe`-Zeilen** (19, 44, 88, 132, 176, 193–198) decken T46 genau ab:
  fünf `basiswechsel`, `land.US.wechselkurs`, `restwelt.leitzins/staatsschuld/
  haushaltssaldo`, `restwelt.wechselkurs`, `restwelt.inflation`. Startwerte 10.000 bei
  den beiden Wechselkursen, 0 sonst — so steht es in T46.
- Die **elf `Parameter`-Zeilen** (22, 37, 66, 81, 110, 125, 154, 169, 255, 258, 309)
  entsprechen T45s `4 × 2 + Fondskasse + Anlegerbestand + Prüfsummenfeld`.
- Restwelt einzeln: 13 Anker, 3 `Entwurf`, 6 `Vorgabe` = 22, wie T45 Zeile 848.

**4. Nach Klasse.** Global 3/71/36/22/22/5/5/25/32/4/83/2 = 310, identisch mit der
Zerlegung in T49. Je spielbarem Land (US und BR einzeln geschnitten) 6/7/2/4/1/1/5/8/1/9
= 44, klassenweise identisch mit der Tabelle in T49 Zeile 192–204. Restwelt
6/4/4/1/1/5/1 = 22, identisch mit T49 Zeile 206–208.

**Zusätzlich, weil das Kriterium es nicht verlangt:**

- **Startwertregel in beide Richtungen.** 149 Zeilen enden auf `| — |`, und dieselben
  149 sind genau die mit Herkunft `Datenanker`, `Parameter` oder `Manifest`
  (136+11+2). 161 Zeilen tragen eine Zahl, und das sind genau die 150 `Entwurf` plus
  11 `Vorgabe`. Kein Ausreisser in einer der beiden Richtungen; 149 + 161 = 310.
- **Jeder Startwert gegen die Skala seiner Klasse (T5).** Es gibt nur zwei verschiedene
  Werte: 10.000 in Klasse 5 (17×) und Klasse 6 (2×) — beides Indizes mit „Startjahr =
  10.000" — und 0 in den Klassen 1, 3, 4, 9 und 11. Kein Prozentwert in einem
  Zehntausendstelfeld, kein Basispunktfeld mit einer Prozentzahl. Der teuerste Fehler
  meiner Rolle ist an dieser Stelle nicht eingetreten.
- **Klassen- und Gruppenzuordnung je Adresse**, nicht nur in der Summe: Ein
  vertauschtes Paar innerhalb desselben Landes hielte jede Summe ein. Die Nicht-Land-
  Blöcke (Zeilen 177–310) einzeln gelesen und gegen T5 gelegt — `markt.wert` 2,
  `markt.rendite` 3, `fonds.hebelstand/kasse/anlegerbestand` 1,
  `fonds.sichtbarkeit/marktanteil` 4, `ueberrendite` 3, Steckplätze 11,
  `beteiligung.*.anteil` 4 gegen `.restdauer` 11, `partie.jahrgang_id/
  parameter_pruefsumme` 12. Kein Fehlgriff. `fonds.position.waehrung.US` ist vorhanden,
  wie T16 es für den dauerhaft leeren Steckplatz verlangt.

## Befund 1 — Klasse 2 mischt laufende und konstante Preise (an den Projektmanager)

**Das ist kein Fehler dieses Pakets.** Das Verzeichnis gibt T15, T45 und T49 korrekt
wieder. Der Widerspruch steht in `technik.md` selbst, und er ist an dieser Tabelle zum
ersten Mal in einem Blick zu sehen, weil sie Klasse und Datenanker nebeneinanderstellt.

**Die Feststellung.** T5 definiert Klasse 2 als „Tausend USD **zu konstanten Preisen des
Basisjahrs**" (Zeile 123). In Klasse 2 stehen nach T49 unter anderem die 40
Handelsströme; alle 40 tragen im Verzeichnis `Datenanker(14)`. Reihe 14 ist nach der
Reihenliste (Zeile 1005) **CEPII BACI**. BACI führt den Wert in *laufenden* Preisen:
„Value of the trade flow (in thousands current USD)"
(`cepii.fr/DATA_DOWNLOAD/baci/doc/DescriptionBACI.html`, abgerufen 2026-09-02).
`daten.md` nennt zu BACI Lizenz, Inhalt und Aktualisierung, aber keine Preisbasis
(Zeile 110–136). Im selben Klasse-2-Topf liegen die Wertschöpfungen mit
`Datenanker(1 × 2)`; Reihe 1 heisst ausdrücklich „BIP, **konstante Preise**".

Eine Deflationierung von Reihe 14 steht nirgends. T23 Punkt 9, die einzige Aufbereitung
der Reihe, ist die Konkordanz HS92 → Modellsektor. T50 zählt die Skalenübergänge
abschliessend auf; ein Preisbasiswechsel ist keiner davon.

**Wie man den Fehler erzeugt.** `durchgriff`, eine der vierzehn Jahrgangskonstanten,
wird in T23 Punkt 5 so gebildet (Zeile 736–741):

```
durchgriff = teile_gerundet(10.000 · H, H + N)
```

mit `H` = Aus- plus Einfuhr des Sektors im Startjahr **aus BACI** und `N` = seine
Wertschöpfung **aus WDI**. Im Nenner werden ein Betrag in laufenden Preisen des
Startjahrs und ein Betrag in konstanten Preisen des Basisjahrs addiert. Das stürzt
nicht ab, verlässt den Wertebereich 0 … 10.000 nicht und bleibt per Konstruktion
plausibel — genau die Sorte Fehler, die ein Modell falsch macht, ohne dass es auffällt.
Beziffern lässt er sich: Der Prüfjahrgang beginnt 1997, die konstanten WDI-Reihen liegen
auf einem deutlich späteren Basisjahr. `N` ist damit gegenüber `H` um den
Preisniveauunterschied zwischen 1997 und dem Basisjahr aufgebläht, und `durchgriff`
fällt systematisch zu klein aus — für jedes Gebiet und jeden handelbaren Sektor, also
in allen zehn Werten gleichgerichtet.

**Die zweite Stelle.** Reihe 14 ist nach der Reihenliste „Start + Sollblock (frei)",
also Teil des Rückvergleichs. Ein Modell, dessen Handelsströme als reale Grössen laufen,
wird dann gegen eine nominale Sollreihe gehalten und muss über 1997–2021 eine
Preisentwicklung nachbilden, die es nicht führt. Mass 4 misst dann Inflation statt
Modellgüte.

**Was ich nicht entscheide:** ob Reihe 14 deflationiert wird, ob Klasse 2 aufgeteilt
wird oder ob T5 seine Formulierung ändert. Nur dass zwei Dokumente hier nicht dasselbe
messen. Beachtenswert: T8 stützt sich ausdrücklich darauf, dass Klasse 2 real ist —
„sind also real und laufen nicht mit" (Zeile 350) —, und begründet damit, dass eine
Neubasierung genau fünf Adressen je Gebiet anfasst.

## Befund 2 — die Datei beschreibt ihre eigene `*`-Markierung falsch

Zeile 29 sagt: „Ein `*` heisst: die Adresse steht in **keinem Dokument wörtlich**". Das
trifft auf die Markierung nicht zu. Nachgeprüft mit `grep -rc` über `specs/0016-…/`:

| Adresse | unmarkiert | Treffer in `specs/` |
|---|---|---:|
| `land.US.sektor.1.wertschoepfung` | ja | **0** |
| `land.US.aufsichtszaehler` | ja | **0** |
| `handel.US.CN.1` | ja | **0** |
| `fonds.position.US.1` | ja | **0** |
| `land.CN.aufsichtszaehler` | ja | 1 |
| `restwelt.preisniveau` | ja | 1 |

Die tatsächlich angewandte Regel steht in derselben Datei unter Befund 2, Zeile 530–534
(„Die Marke sitzt an der **Neuheit**, nicht am Zitat") und ist die brauchbare: Sie
markiert die erfundenen *Bestandteile*. Die wörtliche Lesart würde rund 296 der 310
Zeilen markieren und nichts mehr unterscheiden. Der Fehler ist also die Beschreibung in
Zeile 29, nicht die Markierung.

**Warum das nicht folgenlos ist.** Der Satz ist bereits abgewandert: `parameter.toml`
aus Paket 0009 übernimmt ihn wörtlich („Der Name steht in keinem Dokument woertlich …
Dieselbe Kennzeichnung wie im Adressverzeichnis aus Paket 0007", Zeile 84–88). Dort
stimmt er, weil Schlüsselnamen keine Gebiets- und Sektorindizes tragen. Damit steht
derselbe Satz in zwei Dateien und bedeutet zweierlei. Wer später prüft, ob eine
Adressform belegt ist — etwa bei der offenen Frage `gebiet.<G>.` gegen `land.<L>.` —,
könnte aus dem fehlenden `*` schliessen, `handel.US.CN.1` sei in `specs/` belegt. Es
ist nicht. Behebung ist eine Zeile: Zeile 29 auf die Formulierung aus Zeile 530 bringen.

## Wonach ich gesucht und nichts gefunden habe

- **Stillschweigende Interpolation und verdeckte Lücken:** Das Verzeichnis führt keine
  Messwerte, nur Verweise auf Reihennummern. Kein gefüllter Wert, der als erhoben
  auftreten könnte.
- **Lizenz:** Die Datei zitiert keine Quelle und keinen Wert aus einer Quelle, verweist
  nur über `Datenanker(nr)` auf die Reihenliste. Die Namensnennung gehört nach der
  Auflage des Datenkurators ins Produkt; das ist hier korrekt so vermerkt und nicht als
  Notiz behandelt.
- **Parameterschlüssel gegen Paket 0009:** `startzustimmung` und `regulierung_start`
  wurden in 0007 gebildet und markiert. `parameter.toml` führt beide unter genau diesen
  Namen, und `startkapital` trägt dort wie hier zwei Adressen. Kein Auseinanderlaufen
  zwischen den beiden Paketen.
- **Reproduzierbarkeit:** Die Datei trägt `stand: 2026-09-01` im Frontmatter. Alle
  Zählungen oben sind aus `grep`-Pipelines entstanden und wiederholbar.
- **Der `*`-Zählwert 177** (Befund 2 der Datei) stimmt: `grep -cP` → 177, Gegenprobe
  133 unmarkiert, 177 + 133 = 310.

## Nicht in meinem Prüfumfang, weiter offen

- **`gebiet.<G>.basiswechsel` gegen `land.<L>.` / `restwelt.`** — T46 schreibt die
  Adresse mit einem `gebiet.`-Präfix, das kein anderes Dokument je benutzt; T45 nennt im
  selben Zusammenhang `restwelt.basiswechsel`. Das Verzeichnis wählt die `land.`/
  `restwelt.`-Form und markiert die vier Länderzeilen. Folgenlos für die Zählung,
  entscheidungsreif, sobald jemand die 310 Felder tippt oder das Manifest schreibt.
- **Der Faktor 10.000 bei `Datenanker(1 × 2)`** — Reihe 1 (Tsd USD) mal Reihe 2
  (Zehntausendstel) ergibt nur mit einer Division durch 10.000 wieder Tsd USD. Sie steht
  in T23 Punkt 1 und liegt in der Aufbereitung, also ausserhalb der drei Skalenübergänge
  aus T50 — T50 lässt sie zu Recht aus. Prüfbar erst an dem Paket, das die Aufbereitung
  baut.
