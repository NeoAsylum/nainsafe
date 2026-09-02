---
id: 0035-parameterdatei-belegstellen
rolle: datenbauer
status: vorschlag
haengt_an: [0009-parameterdatei-schluessel, 0028-parameterdatei-querverweis]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/parameter.toml]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Sieben Belegstellen in `parameter.toml` zeigen auf die falsche Zeile, eine auf eine Frage, die es nicht mehr gibt

Vorgabe: `befunde/pruefung-0009-parameterdatei-schluessel-runde3-2026-09-02.md`,
Nebenbefunde 1 und 2. **Paket 0009 ist bestanden**; dies ist kein Rücklauf und kein Befund
gegen seine Arbeit. Zum Zeitpunkt, an dem die Verweise geschrieben wurden, stimmte jeder —
nachgesehen an den historischen Fassungen.

## Der Befund

### (a) Vier Zitate, sieben Fundstellen, alle mit toter Zeilennummer

| in `parameter.toml` | Verweis | stand bei `f0cae94` | steht heute |
|---|---|---|---:|
| Zeile 673 | spiel.md Aktion 4 („Aufschlag, der mit der Sichtbarkeit … steigt") | 177–178 | 183–184 |
| Zeile 674 | spiel.md Kanal 4 („Aufschlag steigt mit Sichtbarkeit") | 524 | 530 |
| Zeile 675 | technik.md T5 Klasse 3 („±2 Mio %") | 124 | 241 |
| Zeilen 762, 806, 829, 848 | technik.md T5 Klasse 10 („höchstens ein Schritt je Runde" = eine Stufe) | 155–156 | 272–273 |

Ursache sind zwei Commits desselben Tages, beide **nach** dem Bau um 05:47: `e068e1a`
(„spielentwerfer", 19:13) an `spiel.md` und `b4526dc` („architekt: 0011-stack-auf-cpp",
20:05) an `technik.md`. Der Versatz ist je Datei einheitlich, aber zwischen den Dateien
verschieden — +6 in `spiel.md`, +117 in `technik.md`. Eine pauschale Addition über alle
sieben Fundstellen geht also daneben, und die nächste Änderung an einer der beiden Dateien
verschiebt sie erneut.

**Der Inhalt jedes Zitats ist weiterhin richtig** — alle vier wurden in der heutigen
Fassung im Wortlaut wiedergefunden. Falsch sind allein die Nummern.

### (b) Ein Verweis auf eine Frage, die aus dem Rückstand verschwunden ist

`parameter.toml` Zeile 22–25 sagt über die fünf geparkten Klasse-4-Schlüssel:

> Ob Klasse 4 ihren Deckel von 10.000 auch fuer einen Regler traegt, entscheidet nicht
> diese Datei, sondern eine Zeile in T5; **die Frage steht in `rueckstand.md` als Vorlage
> an den Geschaeftsfuehrer.**

Der letzte Halbsatz war richtig — bei `f0cae94` stand sie dort als Punkt 4 („Unverändert
offen"). In `rueckstand.md` Fassung 10 (`73bbab8`, 19:45) steht sie nicht mehr, und der
Abschnitt „Was der Geschäftsführer entscheiden lassen muss" nennt die Rohdaten
ausdrücklich als „jetzt der einzige Punkt". Wer dem Verweis folgt, findet nichts.

Das ist die teure Sorte: Die fünf Schlüssel sind **wegen** dieser Frage geparkt. Zeigt der
Verweis ins Leere, sieht der nächste Leser eine unbegründete Auslassung statt einer
bewusst offenen Stelle — und beantwortet sie womöglich selbst, was eine Abweichung von T5
ohne ADR wäre.

## Warum das ein eigenes Paket ist

**Es gehört keinem bestehenden.** 0009 hat sein Kriterium erfüllt und darf dafür nicht
zurückgerufen werden; die Ursache liegt in zwei Paketen, die an `spiel.md` und
`technik.md` arbeiten durften und richtig gearbeitet haben.

**Es darf nicht in 0028.** 0028 arbeitet an derselben Datei, aber seine Abnahme 3 lautet
„Keine zweite Änderung an der Datei. Der Prüfer legt `git diff` an; was hier nicht steht,
ist ein Rücklauf." Wer diese Arbeit dort hineinzieht, erzeugt genau den Rücklauf, den das
Kriterium androht. Deshalb ein eigenes Paket **nach** 0028 — beide beanspruchen
`parameter.toml`, sie dürfen nie gleichzeitig offen sein.

**Es ist die Bauartänderung, nicht das Nachziehen.** Die Nummern jetzt einmal zu
korrigieren hält bis zum nächsten Commit des Architekten, und 0011 läuft noch, 0026 hängt
daran. Wer nur addiert, schreibt die nächste Ungültigkeit selbst. Es ist derselbe Auftrag
wie in **`0034-belegstellen-ohne-zeilennummern`** für `daten/adressen.md`, nur in der
anderen Datei; die beiden kollidieren nicht. (Die Kennung 0034 ist doppelt vergeben —
`0034-reihentoml-baci-einheit-nachziehen` stammt aus einem parallelen Lauf. Meine 0035 war
bei der Wahl frei; kollidiert sie doch, räumt der Projektmanager auf.)

## Was zu tun ist

1. Ersetze jeden Verweis der Form „Zeile N" auf `spiel.md` oder `technik.md` durch einen,
   der ohne Zeilennummer trägt: **Tabellennummer beziehungsweise Abschnittsname** (T5
   Klasse 3, T5 Klasse 10, spiel.md Aktion 4, spiel.md Kanal 4) **plus das Zitat im
   Wortlaut**, an dem die Stelle wiederzufinden ist. Die Nummer darf zusätzlich
   stehenbleiben, wenn sie ein Abrufdatum trägt — tragend ist sie dann nicht mehr.
2. Ersetze in Zeile 22–25 den Halbsatz „die Frage steht in `rueckstand.md` als Vorlage an
   den Geschaeftsfuehrer" durch **die Frage selbst**, in einem Satz und an Ort und Stelle:
   Trägt T5 Klasse 4 („0 bis 10.000") ihren Deckel auch für einen Regler, oder nur für die
   Grösse, die er stellt? Dazu, dass sie offen ist und dass die fünf Schlüssel bis zu ihrer
   Beantwortung unverändert bleiben. **Verweis auf eine Punktnummer in `rueckstand.md`
   nicht erneuern** — die Datei wird je Lauf neu geschrieben und trägt keine stabile
   Nummerierung.

**Was du nicht tust:** Du fasst keinen der 50 Schlüssel an, keine Zahl, keine Schranke,
keine Klasse und keine Marke. Insbesondere **beantwortest du die Klasse-4-Frage nicht** und
rührst die fünf geparkten Schlüssel nicht an. Dies ist eine Änderung an Belegstellen und
an nichts sonst.

## Abnahme

1. **Kein Verweis der Datei nach `specs/` hängt mehr tragend an einer Zeilennummer.** Der
   Prüfer sucht jede der vier Fundstellen über Tabellennummer und Zitat in der heutigen
   Fassung von `spiel.md` und `technik.md` und findet jede, ohne zu zählen.
2. **Der Verweis auf `rueckstand.md` ist durch die Frage selbst ersetzt**, die Frage ist als
   offen benannt und **nicht beantwortet**, und die fünf Schlüssel `preisstoss`,
   `zustimmung_elastizitaet`, `nachahmer_wirkung`, `hebel_max`,
   `innerjahresausschlag_faktor` sind unverändert.
3. **Sonst hat sich nichts geändert.** Die drei Selbstproben liefern weiter 46, 4 und 50;
   die acht Bedingungen unter BEFUNDE Punkt 5 (a) stehen unverändert da; alle 50 Werte,
   Klassen und Schranken sind dieselben. Der Nachweis wird an der Datei geführt, **nicht**
   über `git diff --stat`: Der Commit dieses Vorhabens trägt regelmässig fremde Arbeit und
   einen fremden Betreff.

## Was ausdrücklich kein Befund ist

- **Die Gültigkeit der Datei als TOML.** `python3` ist den Rollen als Kommando gesperrt —
  in drei Prüfrunden nachgewiesen, zuletzt daran, dass auch `python3 --version` abgewiesen
  wird. Der Parser gehört in den Runner. Behaupte nicht, einer sei gelaufen.
- **Dass die fünf Klasse-4-Schlüssel weiter `>= 0` ohne obere Schranke tragen.** Das ist
  Gegenstand der offenen Frage und nicht dieses Pakets.

## Rückläufe

0.
