---
id: 0015-adressen-markierungssatz
rolle: datenbauer
status: offen
haengt_an: [0007-adressverzeichnis-310]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/adressen.md]
abnahme: Die Beschreibung der `*`-Markierung in der Spaltentabelle sagt dasselbe wie die tatsächlich angewandte Regel unter Befund 2 derselben Datei — in beiden Richtungen, und ohne eine Regel aufzustellen, die eine markierte Zeile der Tabelle widerlegt; die 310 Zeilen der Adresstabelle und alle vier Zählungen sind unverändert.
---

# Ein Satz in `daten/adressen.md`, der etwas anderes sagt als die Datei tut

Vorgabe: der Prüfbefund `pruefung-0007-adressverzeichnis-310-2026-09-02.md`, Befund 2.
Kein Rückgabegrund für 0007 — dessen Abnahmekriterium verlangt die Markierung, nicht
ihre Beschreibung, und die Markierung stimmt.

## Der Befund, in drei Sätzen

Die Spaltentabelle der Datei sagt über das Sternchen: *„Ein `*` heisst: die Adresse steht
in **keinem Dokument wörtlich**."* Angewandt ist eine andere Regel, und sie steht in
derselben Datei unter *Befund 2*: *„Die Marke sitzt an der **Neuheit**, nicht am
Zitat"* — markiert werden die erfundenen **Bestandteile**. Der Prüfer hat vier
unmarkierte Adressen nachgeschlagen, die in `specs/` null Treffer haben
(`land.US.sektor.1.wertschoepfung`, `land.US.aufsichtszaehler`, `handel.US.CN.1`,
`fonds.position.US.1`); nach dem wörtlichen Satz müssten sie eine Marke tragen.

Die angewandte Regel ist die brauchbare — die wörtliche Lesart würde rund 296 der 310
Zeilen markieren und nichts mehr unterscheiden. **Zu ändern ist der Satz, nicht die
Markierung.**

## Warum das nicht folgenlos ist

Der Satz ist schon abgewandert: `parameter.toml` aus Paket 0009 übernimmt ihn wörtlich
und verweist dabei auf das Adressverzeichnis. Dort **stimmt** er, weil Schlüsselnamen
keine Gebiets- und Sektorindizes tragen — derselbe Satz steht damit in zwei Dateien und
bedeutet zweierlei. Wer später prüft, ob eine Adressform belegt ist (die offene Frage
`gebiet.<G>.` gegen `land.<L>.` etwa), könnte aus dem fehlenden Sternchen schliessen,
`handel.US.CN.1` sei in `specs/` belegt. Es ist nicht.

## Was du tust

Bring die Beschreibung in der Spaltentabelle auf die Formulierung, die unter *Befund 2*
derselben Datei steht, und sag dort in einem Halbsatz, dass die Marke an den
Bestandteilen sitzt und nicht an der ganzen Zeichenkette. **Sonst nichts.**

`parameter.toml` fasst du **nicht** an: Dort ist der Satz richtig, und die Datei gehört
Paket 0009, das gerade beim Prüfer liegt.

## Rücklauf 1 — der Befund vom 2026-09-02

`befunde/pruefung-0015-adressen-markierungssatz-2026-09-02.md`, Urteil `zurueck`.
Abnahmepunkte 2 und 3 sind erfüllt und bleiben es; Punkt 1 nicht.

**Der erste Satz der neuen Zelle in Zeile 29 ist richtig und bleibt unangetastet** — „an
dieser Adresse ist ein Bestandteil neu erfunden — oder eine Zusammensetzung von
Bestandteilen, die in keinem Dokument gemeinsam vorkommt". Er klassifiziert alle 310
Zeilen korrekt und ist damit sogar vollständiger als der Einzeiler unter *Befund 2*.

**Falsch ist die zweite Hälfte**, der Geschwistersatz: *„Wer aus einer belegten Adresse
durch ein anderes Gebiet, einen anderen Sektor oder ein anderes Instrument eine
Geschwisteradresse bildet, erfindet keinen Bestandteil und bleibt unmarkiert."* Das ist
die **Umkehrung** dessen, was *Befund 2* sagt (dort: die unmarkierten sind Geschwister),
und zwei Zeilen derselben Tabelle widerlegen sie:

- Zeile 222, `restwelt.sektor.1.preis`\* — aus `land.DE.sektor.2.preis` (T17) durch
  anderes Gebiet und anderen Sektor gebildet, **und markiert**.
- Zeile 79, `land.US.instrument.regulierung.stand`\* — aus `land.BR.instrument.zoll.stand`
  (technik.md 513–514) durch anderes Gebiet und anderes Instrument gebildet, **und
  markiert**.

*Befund 2* weist die Regel an derselben Stelle ausdrücklich zurück, unter der Überschrift
„Warum `land.US.sektor.1.preis` unmarkiert ist und `restwelt.sektor.1.preis` markiert"
(Zeile 530–534).

**Umfang des Rücklaufs: ein Halbsatz in Zeile 29.** Er muss die Richtung von *Befund 2*
tragen — die unmarkierten sind Geschwister — oder die Restwelt-Ausnahme mitnennen, wie
*Befund 2* es tut. Die Adresstabelle, die vier Zählungen und der erste Satz der Zelle
bleiben unberührt.

## Abnahme

1. Die Spaltentabelle und der Abschnitt *Befund 2* sagen über die `*`-Markierung
   dasselbe, **und keine der beiden Stellen stellt eine Regel auf, die eine markierte
   Zeile der Adresstabelle zu einer unmarkierten erklärt.** Gegenprobe an den beiden
   Zeilen 79 und 222 (siehe Rücklauf 1), einzeln durchgerechnet.
2. Die vier unmarkierten Adressen aus dem Prüfbefund tragen weiterhin keine Marke, und
   die Datei erklärt, warum das richtig ist.
3. **Die Adresstabelle ist unverändert.** Die 310 Zeilen zwischen der Kopfzeile und dem
   Zählabschnitt sind zeichengleich zur Fassung vor diesem Rücklauf, und alle vier
   Zählungen (Zeilen, Gruppe, Herkunft, Klasse) gehen weiter auf. Der Nachweis wird an
   der Datei geführt, **nicht** über `git diff --stat`: Der Commit dieses Vorhabens trägt
   regelmässig fremde Arbeit und einen fremden Betreff, taugt also nicht als Beleg dafür,
   was dieses Paket angefasst hat.
4. `parameter.toml` bleibt unberührt — unverändert aus der ersten Runde.

## Rückläufe

1 (2026-09-02, Befund 1: Geschwisterregel umgedreht).
