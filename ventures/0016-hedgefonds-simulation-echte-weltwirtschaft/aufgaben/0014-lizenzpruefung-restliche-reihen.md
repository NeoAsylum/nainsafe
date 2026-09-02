---
id: 0014-lizenzpruefung-restliche-reihen
rolle: datenbauer
status: gebaut
haengt_an: [0005-wdi-drittanbieter-ausnahme]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/lizenzbefund-reihen.md]
abnahme: Für jeden geprüften Indikatorcode steht im Befund das wörtliche Feld "Source", die Abruf-URL, das Abrufdatum und ein Urteil frei|gesperrt|unklar mit Begründung; bei jedem Urteil ausser "frei" steht die Folge nach T26 daneben und die Zahl der Sollreihen, die daran hängen. Für jede Reihe ohne WDI-Quelle steht, ob die Lizenz ihrer Quelle einen Drittanbietervorbehalt enthält, mit wörtlichem Satz und Fundstelle.
---

# Die Spalte „Verdacht" ist keine Messung — jetzt wird der Rest gemessen

Vorgaben: `technik.md` T26, die Reihenliste in Abschnitt 7 von `technik.md`,
`specs/0016-…/daten.md`. Vorbild ist Paket 0005, das genau dieselbe Frage für vier
Reihen beantwortet hat; **lies zuerst `daten/lizenzbefund-wdi.md` und arbeite in
derselben Form weiter.**

## Woher dieses Paket kommt

Aus dem Prüfbefund zu 0005 vom 2026-09-02, Befund 1. Der Daten-Prüfer hat drei Reihen
stichprobenweise nachgemessen, die die Reihenliste mit „Verdacht: nein" führt, und alle
drei nennen im Feld `Source` einen Drittanbieter:

| Reihe | Code | „Verdacht" laut Reihenliste | „Source" nennt tatsächlich |
|---|---|---|---|
| 1 (BIP, 4 Sollreihen) | `NY.GDP.MKTP.KD` | nein | OECD National Accounts, nationale Ämter, WB staff |
| 2 (12 Sollreihen) | `NV.AGR.TOTL.ZS` | nein | OECD, nationale Ämter/Notenbanken, WB staff estimates |
| 6 (exogener Pfad) | `SL.TLF.TOTL.IN` | nein | ILO (`estimates based on external database`), UN, WB staff |

Das ist dieselbe Bauart, wegen der Reihe 13 in 0005 **gesperrt** wurde. Die Spalte
„Verdacht" in `technik.md` ist also keine Messung, sondern eine Vermutung — und **Reihe 2
trägt mit 12 von 31 Sollreihen mehr als die vier Reihen aus 0005 zusammen.** Sie ist
zugleich der Ersatzweg, mit dem T26 den Ausfall von Reihe 7 auffangen soll; fällt sie
auch, fällt der Ersatzweg mit.

## Was du prüfst

**Erstens, und das ist der Kern: jeden Indikatorcode mit WDI-Quelle, den 0005 nicht
schon gemessen hat.** Das sind nach der Reihenliste die Reihen 1, 2 (drei Codes), 5 und
6; welche Codes das genau sind, steht teils in der Reihenliste, teils musst du sie im
Indikatorverzeichnis der Weltbank nachschlagen. Methode wie in 0005: das Feld `Source`
des Indikatorendatensatzes **wörtlich** abrufen, über beide Endpunkte, mit URL und
Abrufdatum.

**Zweitens, und billiger: die Reihen ohne WDI-Quelle** — 3, 4 und 15 (PWT), 9 (IWF IFS),
11 und 12 (IWF WEO), 14 (CEPII BACI). Dort gibt es kein Feld `Source`, und die Frage
lautet anders: Enthält die Lizenz der Quelle einen Vorbehalt für fremde Inhalte, wie ihn
die Weltbank für die Drittanbieter-Ausnahme führt? `daten.md` zitiert alle vier Lizenzen
im Wortlaut (Nr. 2, 3, 4). **Prüf, ob dort ein solcher Vorbehalt steht**, und zitiere den
Satz oder halte fest, dass keiner da ist. Nur wenn `daten.md` die Frage offenlässt,
rufst du die Quelle selbst auf — höchstens ein Abruf je Quelle.

**Drittens, aus Befund 2 desselben Prüflaufs:** Der ILO-Vorbehalt lautet „Databases and
datasets … **produced prior to** 3 May 2023 do not automatically benefit from a Creative
Commons licence." Der Befund zu 0005 hat das Datum der **Erzeugung** mit dem des
**Abrufs durch die Weltbank** gleichgesetzt (`date accessed: January 17, 2026`). Halte
fest, welches Datum der Satz meint und ob die Frage aus dem Wortlaut überhaupt zu
beantworten ist. Sie trifft Reihe 6 und Reihe 7 gleichermassen.

## Was in den Befund gehört

Je geprüftem Code eine Zeile mit: Reihe, Code, Feld `Source` wörtlich, Abruf-URL,
Abrufdatum, Urteil `frei | gesperrt | unklar` mit Begründung. Bei jedem Urteil ausser
`frei` zusätzlich:

- **die Folge nach T26** — was ändert sich am Programm (nichts) und was am Jahrgang;
- **die Zahl der Sollreihen, die an diesem Code hängen.** Das ist die Zahl, an der der
  Betreiber später sieht, was ein Urteil kostet: Reihe 2 trägt 12, Reihe 1 vier, Reihe 6
  keine (exogener Pfad, kein Soll).

Am Ende eine Zusammenfassung in drei Zeilen: wie viele der 31 Sollreihen nach dieser
Prüfung `frei` sind, wie viele `unklar`, wie viele `gesperrt`. Und, weil T37 daran hängt:
ob der Rückvergleich mit dem, was übrig bleibt, noch 16 Prüfgegenstände hat.

## Grenzen

- Du gibst **keinen Rechtsrat.** Du liest, was die Quelle über sich selbst sagt, und
  zitierst es. Die Bewertung „nutzbar" trifft der Betreiber.
- Du lädst **nichts herunter** und bettest nichts ein. Dieses Paket erzeugt genau eine
  Textdatei.
- Du **änderst die Reihenliste nicht.** Sie steht in `technik.md` und gehört dem
  Architekten. Dass ihre Spalte „Verdacht" nicht hält, ist dein Befund — die Korrektur
  ist es nicht.
- Du **prüfst nicht die Deckung.** Ob eine Reihe 25 Stützstellen trägt, ist Paket 0006.

## Rückläufe

0.
