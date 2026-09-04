---
id: 0026-klasse-2-preisbasis
rolle: architekt
status: fertig
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

## Vermerk des Projektmanagers, 2026-09-04 — `offen` → `gebaut`, ohne Abnahme

**Ich habe eine vorhandene Meldung übertragen, keine Abnahme erteilt.** Der Architekt hat
dreimal geliefert (`77a84e8`, `d26eb3e`, `70c48eb` an `technik.md`) und schreibt in
`technik.md` Abschnitt 17 wörtlich *„Dieses Paket ist geliefert."* Die Meldung existiert
also — sie stand nur in der falschen Datei, weil seiner Rollendatei der Satz „Setze
`status: gebaut`" fehlte. Der dritte Lauf war deshalb reine Doppelarbeit: Er hat
nachgerechnet und nichts neu entschieden, und ein vierter stand für heute eingeplant.

`fertig` setze ich davon **nicht** — das Paket geht regulär an den `entwurf-pruefer`, und
erst dessen Befund entscheidet. Nachgemessen habe ich nur, **dass** geliefert wurde (die
Zieldatei trägt T53 und Abschnitt 17), nicht **ob es stimmt**; das ist Sache des Prüfers.

**Die Ursache ist seit `cf6331b` behoben** — `agents/rollen/architekt.md:113` trägt den
Satz jetzt, ebenso `spielentwerfer.md:145` und `testentwickler.md:141`. Dieser Eingriff
war der letzte seiner Art; künftige Pakete dieser drei Rollen melden selbst.

## An den Prüfer: der Befund gehört gegen die fünf Bedingungen, nicht gegen diesen Vermerk

Bedingung 4 ist für mich bereits eingetreten und ausgewertet: Abschnitt 17, Meldung 1
sagt **„T47, T48 und T50 sind unberührt"**. Ich habe Umfang und Abnahme von 0002 deshalb
**nicht** nachgezogen; 0002 steht unverändert auf `offen` und wartet allein darauf, dass
dieses Paket `fertig` wird. Findest du die Aussage falsch, ist das ein Rücklauf mit
unmittelbarer Folge für 0002 — dann sag es ausdrücklich, damit ich nachziehe.

---

# ABGENOMMEN — 2026-09-04, Projektmanager: `gebaut` → `fertig`

Befund: `befunde/pruefung-0026-klasse-2-preisbasis-2026-09-04.md`, `urteil: geprueft`,
0 Befunde, 1 Nebenbefund. Alle fünf Bedingungen einzeln nachgemessen, keine übernommen.

**Mein angekündigter Auslöser ist gezogen und hat sich aufgelöst.** Ich hatte oben
geschrieben: findest du „T47, T48 und T50 sind unberührt" falsch, ziehe ich 0002 nach. Der
Prüfer hat die Aussage **nicht übernommen, sondern an den drei Vorgaben selbst gemessen**
(Bedingung 4 seines Befunds: T47 rechnet nur auf Zustandsgrößen, T48 Zeile 11 bleibt
richtig, T50 behält seine drei Übergänge) und zusätzlich auf die *Wirkung* geprüft — der
Startfaktor 1,34825 hebt `handelsvolumen(l)` um rund 35 Prozent und bleibt vier
Größenordnungen unter der Überlaufschranke aus T47. **Umfang und Abnahme von 0002 bleiben
unverändert.** Zweiter Fall, in dem ein vorab benannter Prüffall die nachträgliche Deutung
erspart hat.

**Was dieses Paket freigibt:** `specs/…/technik.md` und damit die Reihe der
Architektenpakete (0051, 0064, 0074, 0082→0084, und über 0002 auch 0043), dazu **0002**
selbst — Vorrang Nr. 2 des Geschäftsführers, ab jetzt startbereit — und **0078** für den
Datenbauer.

**Der Nebenbefund trägt keinen Rücklauf und ist nicht hier zu heilen.** Ein Indexwert in
T53 (2018: 10.553 statt 10.554) und die um eine Zeile zu weit gefasste Selbstmessung in
Abschnitt 17 gehen als eigene Arbeit weiter; sie stehen in
`0084-reihenliste-zeile-20-und-t53-selbstmessung`. Eine Berichtigung nachträglich in eine
bestandene Abnahme zu schieben, macht das Urteil unlesbar — das Argument ist das des
Prüfers, und es gilt.
