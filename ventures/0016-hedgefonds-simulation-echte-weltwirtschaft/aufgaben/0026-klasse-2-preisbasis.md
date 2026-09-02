---
id: 0026-klasse-2-preisbasis
rolle: architekt
status: offen
haengt_an: [0011-stack-auf-cpp, 0025-quelleneinheit-pwt-baci]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/technik.md]
abnahme: Die fünf Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Klasse 2 misst zweierlei, und das blockiert zwei Pakete

Vorgaben: `technik.md` T5 (Skalenklassen), T42 (Maßstab des Rückvergleichs), T47, T48,
T50, dazu `daten/einheitenbefund-pwt-baci.md` aus Paket 0025 als gemessene Grundlage.

**Dies ist das Paket, das Paket 0002 entblockt.** 0002 (`kern::werte`, Fondsbewertung)
steht seit dem 2026-09-02 auf `blockiert`, und sein Entblockungssatz lautet wörtlich:
*„eine Entscheidung des Architekten zur Klasse-2-Frage, schriftlich in `technik.md` oder
in einem ADR."* Über 0002 hängt 0010 (Zustandsausgabe) mit daran. Es ist damit die
längste blockierte Kette des Vorhabens.

## Der Widerspruch

T5 gibt Klasse 2 (volkswirtschaftliche Beträge) als *„Tausend USD zu konstanten Preisen
des Basisjahrs"* (`technik.md` Zeile 123), und T39/Basiswechsel stützt sich ausdrücklich
darauf: *„Die volkswirtschaftlichen Beträge stehen nach T5 Klasse 2 zu konstanten Preisen
des Basisjahrs, sind also real und laufen nicht mit"* (Zeile 349–350).

In derselben Klasse liegen die **40 bilateralen Handelsströme** aus CEPII BACI. Ob BACI
laufende oder konstante Preise meldet, ist bis zum 2026-09-02 ungemessen gewesen; Paket
0025 misst es. Meldet es laufende Preise, dann misst **Maß 4** an dieser Stelle Inflation
statt Modellgüte, und `durchgriff` (Reihe 16) teilt zwei verschieden basierte Größen.

## Warum das dir gehört und nicht dem Bauagenten

T5 ist deine Tabelle. Ein Kernbauer, der die Klasse einer Größe selbst festlegt, entwirft;
und `kern::werte` hat nach T47 Punkt 3 fünf Leser — Nacharbeit dort ist die teuerste im
ganzen Kern. Deshalb steht 0002 blockiert und wartet, statt gegen eine Vorgabe gebaut zu
werden, von der zwei Prüfbefunde und der Plan sagen, dass sie an dieser Stelle nicht
trägt.

## Was du entscheidest

Was Klasse 2 für eine Reihe bedeutet, die in laufenden Preisen ankommt. `specs/` lässt
mindestens drei Wege offen, und keiner ist hier vorgewählt:

- die Reihe wird mit einem benannten Deflator auf das Basisjahr gebracht,
- die Reihe wechselt die Klasse oder bekommt eine eigene,
- Maß 4 wird an dieser Stelle eingeschränkt und sagt, was es dann nicht mehr misst.

Der Preis jedes Weges gehört dazu, und zwar in Rechenschritten je Weltschritt und in
zusätzlichen Sollreihen — nicht als Einschätzung. **Ein Argument ist kein Vergleich**
(ADR 0010): Die Wege stehen nebeneinander, du wählst einen und schreibst hin, was der
gewählte kostet und was die anderen gekostet hätten.

## Was du nicht tust

- **Du füllst keine Lücke, die `spiel.md` gehört.** Die Höhe des Schadens in Gegenkraft 5
  ist Sache des Spielentwerfers (Paket 0021), nicht deine.
- **Du schreibst keinen Code** und keine Abnahme für ein Bauteil.
- **Du glättest nicht.** Lässt sich die Entscheidung ohne eine Zahl nicht treffen, die
  auch 0025 nicht gemessen hat, dann steht das so da, mit der Zahl, dem Adressaten und der
  Folge — und die Entscheidung bleibt offen. Eine getroffene Entscheidung auf einer
  geratenen Grundlage ist hier teurer als eine offene.

## Abnahme

1. **T5 sagt für Klasse 2, welche Preisbasis gilt**, und der Satz ist mit dem
   Basiswechsel-Abschnitt (Zeile 344–356) verträglich — beide Stellen sagen dasselbe, oder
   die zweite ist mitgeändert.
2. **Für jede Reihe, die in Klasse 2 liegt und nicht in der geltenden Preisbasis ankommt,
   steht daneben, was mit ihr geschieht** — Deflator (mit Namen und Quelle),
   Klassenwechsel oder Einschränkung von Maß 4 — **oder** eine ausgewiesene
   Nichtentscheidung mit der offenen Frage und ihrem Adressaten. Die 40 Handelsströme aus
   BACI sind namentlich behandelt; welche Reihen betroffen sind, steht in
   `daten/einheitenbefund-pwt-baci.md` und `daten/reihen.toml`.
3. **Die Wege stehen als Vergleich da, nicht als Begründung des gewählten.** Mindestens
   zwei Alternativen mit ihrem Preis, und der Grund für die Wahl.
4. **Die Folge für Paket 0002 ist ausgeschrieben:** Der Text sagt ausdrücklich, ob T47,
   T48 und T50 unberührt bleiben. Bleiben sie es, kann 0002 unverändert wieder auf `offen`;
   ändern sie sich, benennt der Text die geänderten Stellen einzeln, damit der
   Projektmanager Umfang und Abnahme von 0002 nachziehen kann.
5. **Kein anderer Abschnitt von `technik.md` ist angefasst** ausser den unter 1, 2 und 4
   genannten und dem Befundabarbeitungsabschnitt am Ende. Die offenen Fragen aus
   `rueckstand.md` Punkt 6 und 7 (Wohnort der Zustandsausgabe, Rundung bei Reihe 2, das
   `frei` in der Spalte „Rolle") gehören **nicht** in dieses Paket — sie werden das nächste
   Architektenpaket, weil `technik.md` die Kollisionseinheit ist und ein Lauf ein Paket
   trägt.

## Was ausdrücklich kein Befund ist

- **Welchen der drei Wege du wählst.** Der Prüfer urteilt darüber nicht; er urteilt
  darüber, ob der Vergleich, der Preis und die Folge für 0002 dastehen.
- **Dass die Entscheidung offen bleibt**, wenn Bedingung 2 (b) greift — sofern die
  fehlende Zahl und ihr Adressat benannt sind.

## Rückläufe

0.
