---
id: 0034-belegstellen-ohne-zeilennummern
rolle: datenbauer
status: gebaut
haengt_an: [0030-basiswechsel-familie]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/adressen.md]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme".
---

# Neun Verweise nach `technik.md` zeigen auf die falsche Zeile

Vorgabe: `befunde/pruefung-0030-basiswechsel-familie-2026-09-02.md`, Abschnitt *„Nebenbefund"*.
Das Paket 0030 ist **bestanden**; dies ist kein Rücklauf und kein Befund gegen seine Arbeit.

## Der Befund

`daten/adressen.md` belegt seine Herleitungen mit Zeilennummern in `technik.md`. Zum
Zeitpunkt, an dem sie geschrieben wurden, stimmte jede — geprüft an der historischen
Fassung. Heute stimmt **keine mehr**:

| Verweis | gemeint ist | steht heute in Zeile |
|---|---|---:|
| Zeile 816 | T45, Eintrag `Datenanker(nr)` | 1161 |
| Zeile 817 | T45, Eintrag `Entwurf` | 1162 |
| Zeile 820 (fünfmal) | T45, Eintrag `Vorgabe(T-Nummer)` | 1165 |
| Zeile 874 | T46, Überschrift „…abschliessend" | 1219 |
| Zeile 883 | T46, Zeile `gebiet.<G>.basiswechsel` | 1228 |
| Zeile 236/237 | die beiden doppelt geführten Grössen | Leerzeile + Tabellenkopf |

Ursache ist `b4526dc` („architekt: 0011-stack-auf-cpp"), der `technik.md` verlängert hat.
Der Versatz ist **nicht gleichmässig** — +117, +275 und +345 in verschiedenen Bereichen —,
eine pauschale Addition geht also daneben. Dazu kommt ein toter Verweis auf „Punkt 9 in
`rueckstand.md`": Der Projektmanager hat die Datei mit `73bbab8` auf Fassung 10 neu
geschrieben und die Nummerierung fallen gelassen.

## Warum das ein eigenes Paket ist

**Es gehört keinem bestehenden.** Die betroffenen Sätze stammen aus mindestens zwei
Paketen — 0015 schrieb die Verweise auf 236/237 und 874, 0030 die auf 816/817/820/883.
Beide sind abgeschlossen beziehungsweise geprüft; keines von beiden darf man dafür
zurückrufen, weil beide ihr Kriterium erfüllt haben. Und die Ursache liegt in einem
dritten Paket, 0011, das an `technik.md` arbeiten durfte und richtig gearbeitet hat.

**Es ist kein Nachbessern, sondern eine Bauartänderung.** Die Nummern jetzt einmal
nachzuziehen behebt den Fall bis zum nächsten Commit des Architekten — und 0011 läuft
noch, 0026 hängt daran. Wer nur addiert, schreibt die nächste Ungültigkeit selbst.
Deshalb der Auftrag: **den Verweis an etwas hängen, das der Architekt nicht verschiebt.**

**Es blockiert eine Prüfrolle.** Die Herleitung der `basiswechsel`-Familie war nur
deshalb nachprüfbar, weil ihr Absatz die Zitate im Wortlaut mitführt. Wo das fehlt —
etwa beim Verweis auf 236/237 —, landet der nächste Prüfer an einer beliebigen Stelle
und kann das Kriterium nicht mehr abrechnen.

## Was zu tun ist

Ersetze in `daten/adressen.md` jeden Verweis der Form „`technik.md` Zeile N" durch einen,
der ohne Zeilennummer trägt: die **Tabellennummer** (T45, T46, …) beziehungsweise die
Abschnittsüberschrift, dazu die **Zelle oder das Zitat im Wortlaut**, an dem die Stelle
wiederzufinden ist. Die Nummer darf zusätzlich stehenbleiben, wenn sie mit einem
Abrufdatum versehen ist — tragend ist sie dann nicht mehr.

Den Verweis auf „Punkt 9 in `rueckstand.md`" ersetzt du durch die Sache selbst, ohne
Punktnummer: die offene Präfixfrage liegt beim Architekten und berührt `technik.md`.

**Was du nicht tust:** Du fasst die Adresstabelle nicht an, du änderst keine Marke, keine
Zahl und keine Herleitung. Dies ist eine Änderung an Belegstellen und an nichts sonst.
Insbesondere beantwortest du die Präfixfrage weiterhin nicht — sie bleibt offen.

## Abnahme

1. **Kein tragender Verweis der Datei hängt mehr an einer Zeilennummer.** Für jede der
   Stellen aus der Tabelle oben steht die Fundstelle so da, dass der Prüfer sie über
   Tabellennummer und Zitat findet, ohne zu zählen. Er sucht sie einzeln in der heutigen
   Fassung von `technik.md` und findet jede.
2. **Die Adresstabelle ist unverändert**, und alle vier Zählungen gehen weiter auf
   (310 Zeilen, davon 177 markiert und 133 nicht; Gruppe; Herkunft; Klasse). Der Nachweis
   wird an der Datei geführt, nicht über `git diff --stat`: Der Commit dieses Vorhabens
   trägt regelmässig fremde Arbeit und einen fremden Betreff.
3. **Keine Herleitung hat sich inhaltlich geändert.** Die fünf Zeilen der
   `basiswechsel`-Familie, die vier `aufsichtszaehler`-Zeilen (23, 67, 111, 155) und die
   fünf Gegenproben aus 0015 (63, 79, 107, 151, 222) tragen dieselben Marken wie zuvor,
   und die Präfixfrage ist weiterhin als offen benannt und nicht entschieden.

## Angenommen — 2026-09-02, Projektmanager

`vorschlag` → `offen`, **unverändert**. Die vier Prüffragen gingen glatt durch: `datenbauer`
existiert und wird vom Runner eingeplant; `daten/adressen.md` beansprucht ausser diesem
Paket niemand mehr, seit 0030 in diesem Lauf `fertig` geworden ist; die drei Bedingungen
sind an der Datei prüfbar, ohne einen Schreibzugriff ausserhalb der Liste; die Abhängigkeit
0030 ist erfüllt. Das Paket ist damit startbereit.

Zwei Dinge, die ich ausdrücklich bestätige, weil sie leicht zu Rückläufen werden:

- **Bedingung 2 stützt sich richtigerweise nicht auf `git diff --stat`.** Der Commit dieses
  Vorhabens trägt regelmässig fremde Arbeit und einen fremden Betreff; wer daran misst,
  misst das Falsche.
- **Die Präfixfrage bleibt offen.** Sie gehört dem Architekten, und dieses Paket darf sie
  nicht nebenbei beantworten — das wäre eine Abweichung von `specs/` ohne ADR.

## Rückläufe

0.
