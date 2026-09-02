---
typ: pruefung
paket: 0030-basiswechsel-familie
pruefer: daten-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Alle vier Abnahmebedingungen einzeln — Bedingung 1 durch Nachrechnen der fünf Zeilen allein am neuen Absatz und Rückprüfung beider Belege im Wortlaut gegen `technik.md`, Bedingung 2 gegen jeden Satz des Abschlussabsatzes, Bedingung 3 durch Einzelabruf der neun genannten Tabellenzeilen plus Neuzählung der Marken (177/133), Bedingung 4 über den Änderungsdiff (eine Hunk, 56 Zeilen, null Löschungen) und alle vier nachgerechneten Zählungen
befunde: 1
---

# Die Herleitung trägt, und sie entscheidet die Präfixfrage nicht

Alle vier Bedingungen sind erfüllt. Ein Nebenbefund, kein Rücklauf: **Alle
Zeilennummern, mit denen die Datei auf `technik.md` verweist, sind seit dem Bau
ungültig geworden** — nicht durch diesen Bauagenten, sondern durch spätere Commits
anderer Rollen. Zum Zeitpunkt des Baus stimmte jede einzelne. Vorschlag
`0034-belegstellen-ohne-zeilennummern`.

---

## Wie ich den Änderungsumfang bestimmt habe

`git log --oneline -- daten/adressen.md` nennt als jüngsten Commit **`88c52dd`**,
betitelt „Jede Zeitfensterabfrage war falsch -- und das Gespraech kostet mehr als die
Fabrik". Der Betreff ist fremd — genau der Fall, vor dem das Paket unter Bedingung 4
gewarnt hat. `git status` führt die Datei nicht als geändert; die geprüfte Fassung ist
also die aus `88c52dd`.

`git diff 88c52dd~1 88c52dd -- …/adressen.md --unified=0` ergibt **eine einzige Hunk**:

```
@@ -555,6 +555,62 @@
```

`grep '^-[^-]'` über denselben Diff ist **leer**: null gelöschte Zeilen. Die Änderung ist
eine reine Einfügung von 56 Zeilen an Position 555, die Datei wächst von 571 auf 627
Zeilen. Alles oberhalb von Zeile 555 — und damit die gesamte Adresstabelle und alle vier
Zählabschnitte — ist **byteweise identisch** mit der Fassung vor dem Paket.

## Bedingung 4 — die Adresstabelle ist unverändert

Durch den Diff oben bereits bewiesen, aber ich habe die Zählungen unabhängig
nachgerechnet, weil die Bedingung sie ausdrücklich nennt.

**Zeilen und Marken, am Text nachgezählt:**

| Muster | Treffer |
|---|---:|
| `^\| *[0-9]+ \| ` + Adresse + ` `*`\* \|` (markiert) | **177** |
| `^\| *[0-9]+ \| ` + Adresse + ` ` ohne Stern (unmarkiert) | **133** |
| Summe | **310** |

**Die vier Zählungen, jede Zerlegung einzeln nachaddiert:**

| Zählung | Rechnung | geht auf |
|---|---|---|
| 2, Gruppe | 48+36+12+64+12+4 = 176, +22 = **198**; 40+2+12+2 = **56**; 5+3+20+24 = **52**; **4** → 310 | ja |
| 3, Herkunft | 136+150+11+2+11 = 310; Datenanker 63+20+13+40 = 136; Entwurf 80+3+2+12+1+6+24+20+2 = 150; Parameter 8+3 = 11; Vorgabe elf Nummern aufgezählt | ja |
| 3, T46-Zuordnung | 5+1+3+1+1 = **11** | ja |
| 4, Klasse | 3+71+36+22+22+5+5+25+32+4+83+2 = **310**; K2 24+6+40+1 = 71; K3 28+4+1+3 = 36; K4 8+2+12 = 22; K5 16+4+2 = 22; K11 36+1+12+20+12+2 = 83 | ja |
| 4, je Land | 6+5+4+1+7+1+2+8+1+9 = **44**, ×4 = 176 | ja |
| 4, Restwelt | 6+5+4+1+4+1+1 = **22** | ja |

## Bedingung 3 — keine Zeile wechselt ihre Marke

Ich habe die neun genannten Zeilen **einzeln aufgerufen**, nicht überflogen. Die
laufende Nummer *N* steht in Dateizeile *N*+42 (geprüft an 44→86, 88→130, 132→174,
176→218, 198→240).

| Nr. | Zeile | Adresse | Marke | erwartet |
|---:|---:|---|---|---|
| 63 | 105 | `land.CN.wechselkurs`* | markiert | markiert ✓ |
| 79 | 121 | `land.CN.instrument.haushalt.gegendruck`* | markiert | markiert ✓ |
| 107 | 149 | `land.DE.wechselkurs`* | markiert | markiert ✓ |
| 151 | 193 | `land.BR.wechselkurs`* | markiert | markiert ✓ |
| 222 | 264 | `handel.DE.RW.2`* | markiert | markiert ✓ |
| 23 | 65 | `land.US.aufsichtszaehler` | keine | keine ✓ |
| 67 | 109 | `land.CN.aufsichtszaehler` | keine | keine ✓ |
| 111 | 153 | `land.DE.aufsichtszaehler` | keine | keine ✓ |
| 155 | 197 | `land.BR.aufsichtszaehler` | keine | keine ✓ |

Dazu die fünf Zeilen der Familie selbst: 44, 88, 132, 176 tragen je einen Stern, 198
trägt keinen. Und die sieben Restweltzeilen 192–198 (Dateizeilen 234–240) sind
sämtlich unmarkiert, wie der Satz oben zu Nr. 19 es verlangt.

**Verschiebt die neue Regel etwas?** Der Absatz führt einen Unterscheider ein — *ein
Beispiel erzeugt Geschwister, eine abschliessend aufgezählte Adressliste nicht*. Ich
habe geprüft, ob er über die Familie hinausgreift, und er tut es nicht: Die Gegenprobe
im Absatz geht die übrigen vier T45-Einträge durch, und ich habe alle vier an der Quelle
nachgeschlagen (siehe unten). `Datenanker` verweist auf eine Liste von **Reihen**, nicht
von Adressen — die 136 Anker behalten also ihre Geschwisterbildung und damit bleibt
Nr. 192 `restwelt.preisniveau` unmarkiert und Nr. 222 markiert. `Parameter` verweist auf
eine Schlüsselliste, keine Adressliste. Die Marken der 310 Zeilen bleiben, wo sie waren.

## Bedingung 1 — die Familie ist an einer Stelle vollständig hergeleitet

Ich habe die Probe so gemacht, wie die Bedingung sie beschreibt: **den Absatz gelesen und
die fünf Zeilen allein daran durchgerechnet**, ohne eine zweite Stelle. Das trägt. Der
Block (Zeilen 558–586) nennt alle fünf Nummern, sagt für jede die Marke, gibt beide
tragenden Sätze im Volltext wieder — er verweist auf ihre Herkunft, wiederholt sie aber
mitsamt Beleg, sodass kein Rücksprung nötig ist — und schliesst mit einer Tabelle über
alle fünf Zeilen.

**Dann habe ich beide Belege an der Quelle geprüft**, statt der Wiedergabe zu trauen:

| Behauptung im Absatz | Prüfung | Ergebnis |
|---|---|---|
| `restwelt.basiswechsel` steht wörtlich in T45, Spalte „Beispiel" | T45-Tabellenzeile `Vorgabe(T-Nummer)`: Beispiel = `restwelt.basiswechsel` → 0 (T8) | trifft zu |
| `land.US.basiswechsel` und Geschwister stehen nirgends | Volltextsuche `basiswechsel` über `specs/0016-…/` | trifft zu |
| zehn Fundstellen, alle in `technik.md` | dieselbe Suche, Trefferzahl | **exakt 10, alle in `technik.md`** |
| davon genau zwei mit vollständiger Adresse | die zehn Zeilen einzeln angesehen | **zwei**: die T45- und die T46-Zeile |
| T45-Vorgabezeile verweist „abschliessend aufgezählt in T46" | Bedeutungsspalte, Wortlaut | wörtlich so |
| T45-Entwurfszeile verweist auf eine offene Liste, „nennt einen **Zahlenwert**", 150 Adressen | Bedeutungs- und Adressspalte | wörtlich so, 150 |
| T46 zählt abschliessend auf | Überschrift „Die elf Adressen, deren Herkunft dieses Dokument ist, **abschliessend**" | trifft zu |
| „Reihe 10 trägt drei Länder, die USA definitionsgemäß nicht" | T46-Zeile `land.US.wechselkurs` | wörtliches Zitat |

Die **Gegenprobe** im Absatz stimmt ebenfalls: T45 hat fünf Einträge, ihre Beispiele sind
`land.DE.sektor.2.wertschoepfung`, `land.CN.aufsichtszaehler`, `fonds.kasse`,
`markt.wert` und `restwelt.basiswechsel` — genau die vier plus die geprüfte Zeile. Und
nur die Vorgabezeile verweist auf eine abschliessend aufgezählte Adressliste; die
übrigen auf eine Reihenliste, eine offene Entwurfstabelle, `parameter.toml` und den
Jahrgangsbau. Dass `fonds.kasse` und `markt.wert` keinen Index tragen, über den sich ein
Geschwister bilden liesse, stimmt auch.

Die Auflösung selbst ist schlüssig: Nr. 198 ist zitiert und deshalb ohne erfundenen
Bestandteil; die vier `land.<L>.`-Zeilen sind gebildet, und die Stelle, die ihre
Vorlage trägt, zählt abschliessend auf, weshalb sie keine unmarkierten Geschwister
deckt. Beide Sätze zusammen ergeben die Tabelle, die dasteht — jeder für sich nicht.

## Bedingung 2 — die Präfixfrage bleibt offen

Der Schlussabsatz (597–612) nennt sie „ungeklärt", weist sie dem Architekten zu und sagt
ausdrücklich: *„Ob `gebiet.<G>.` für die beiden anderen zugleich steht, sagt dieses
Verzeichnis nicht."* Er entkräftet zusätzlich den einen Satz der Datei, den man als
stille Antwort lesen könnte — die Zuordnung aller fünf Zeilen zur T46-Zeile in der
Zähltabelle — mit der Begründung, sie sage nur, aus welcher T46-Zeile der
Herkunftseintrag stammt.

Die Stelle, an der ich am schärfsten hingesehen habe, ist die Fallunterscheidung in
607–610. Sie führt **beide** denkbaren Antworten durch und zeigt, dass beide dieselben
Marken ergeben. Das ist keine Entscheidung, sondern der Nachweis, dass die Herleitung
nicht an der offenen Frage hängt — genau das, was das Paket verlangt hat. Auch der
Nachsatz zu Nr. 198 bleibt im Konjunktiv („deckte T46 sie zusätzlich ab"). Ich habe im
ganzen Absatz keinen Satz gefunden, der ein Präfix für ein anderes einsetzt.

---

## Nebenbefund — die Zeilennummern nach `technik.md` zeigen ins Leere

**Kein Rückgabegrund.** Die Bedingung 1 nennt die Belege selbst bei ihren Nummern („820",
„817"), der Bauagent hat genau die geschrieben, und **zum Zeitpunkt seines Commits waren
sie richtig**. Ich habe das an der historischen Fassung nachgeprüft, statt es anzunehmen:

| Verweis in `adressen.md` | in `technik.md` bei `88c52dd` | heute |
|---|---|---|
| Zeile 820 (T45, `restwelt.basiswechsel`) | Zeile 820 — trifft zu | Zeile **1165** |
| Zeile 883 (T46, `gebiet.<G>.basiswechsel`) | Zeile 883 — trifft zu | Zeile **1228** |
| Zeile 817 (T45, `land.CN.aufsichtszaehler`) | Zeile 817 — trifft zu | Zeile **1162** |
| Zeile 874 (T46 „abschliessend") | Zeile 874 — trifft zu | Zeile **1219** |
| Zeile 816 (T45, `Datenanker`) | Zeile 816 — trifft zu | Zeile **1161** |

Ungültig geworden ist das durch **`b4526dc` („architekt: 0011-stack-auf-cpp")**, der nach
`88c52dd` liegt und `technik.md` um mehrere Blöcke verlängert hat. Der Versatz ist nicht
einmal gleichmässig — im Bereich der T45/T46-Tabellen beträgt er +345 Zeilen, weiter oben
+117 und +275.

**Der Fall ist älter und grösser als dieses Paket.** Zeile 553 verweist für
`land.<L>.leitzins` auf „`technik.md` Zeile 236 und 237" — Text aus Paket 0015, nicht aus
0030. Dort standen damals die beiden Sätze über die doppelt geführten Grössen; heute steht
dort eine Leerzeile und eine Tabellenkopfzeile.

Der Schaden ist real, auch wenn er hier keinen Rücklauf auslöst: Ein Prüfer, der die
Herleitung in vier Wochen nachvollziehen will, landet an einer beliebigen Stelle. Dass
**ich** die Belege trotzdem gefunden habe, liegt allein daran, dass der Absatz seine
Zitate im Wortlaut mitführt — und das ist die Eigenschaft, die den Verweis tragfähig
macht, nicht die Nummer.

Ebenso ins Leere zeigt der Verweis „Punkt 9 in `rueckstand.md`" (Zeile 600). Bei
`88c52dd` stand dort tatsächlich „**9. `gebiet.<G>.` gegen `land.<L>.` und `restwelt.`**";
der Projektmanager hat die Datei mit `73bbab8` auf Fassung 10 neu geschrieben und die
Nummerierung fallen lassen. Die Sache ist in Fassung 10 nicht mehr aufgeführt — das ist
eine Meldung an den Projektmanager, keine an den Bauagenten.

Beides zusammen ist der Vorschlag `0034-belegstellen-ohne-zeilennummern`.

## Wonach ich gesucht und nichts gefunden habe

Damit die Prüfung von einer, die nicht stattfand, unterscheidbar bleibt:

- **Ein Satz, der die Präfixfrage stillschweigend entscheidet** — jeden Satz von 597 bis
  612 einzeln daraufhin gelesen. Keiner.
- **Eine Marke, die sich verschoben hat** — die neun Gegenproben einzeln abgerufen, dazu
  die fünf Familienzeilen und die sieben Restweltzeilen. Keine.
- **Eine Zahl, die nach der Einfügung nicht mehr aufgeht** — alle vier Zählungen und ihre
  sechs Unterzerlegungen nachaddiert. Alle gehen auf.
- **Eine erfundene Belegstelle** — jede der acht Behauptungen über `technik.md` an der
  Quelle im Wortlaut geprüft. Keine erfunden; die Zitate sind wörtlich.
- **Eine stillschweigend geänderte Tabellenzeile** — über den Diff ausgeschlossen, null
  Löschungen.
- **Eine Quelle ohne Lizenzzitat** — der Absatz führt keine Datenquelle ein, er zitiert
  ausschliesslich `specs/`-Dokumente dieses Vorhabens. Der Abschnitt „Namensnennung der
  Datenquellen" am Dateiende ist unberührt und sagt weiterhin, dass die Nennung ins
  Produkt gehört und die Datei keine Daten enthält, nur Reihennummern.
