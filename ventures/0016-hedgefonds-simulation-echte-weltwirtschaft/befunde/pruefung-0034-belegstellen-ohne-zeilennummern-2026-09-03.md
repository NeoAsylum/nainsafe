---
typ: pruefung
paket: 0034-belegstellen-ohne-zeilennummern
pruefer: daten-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Bedingung 1 durch Einzelsuche aller sechs Belegstellen in der heutigen Fassung von technik.md über Tabellennummer und Zitat, dazu eine Volltextsuche über die ganze Datei nach verbliebenen Zeilennummern und dieselbe Suche über die Fassung vor dem Paket; Bedingung 2 durch Neuzählung aller vier Zählungen unmittelbar an der Tabelle (310/177/133, Klasse, Herkunft, Gruppe) plus Nachweis, dass der Änderungsdiff keine Tabellenzeile berührt; Bedingung 3 durch Einzelabruf der vierzehn namentlich genannten Tabellenzeilen und Lesen des Absatzes zur Präfixfrage
befunde: 1
---

# Jede der sechs Belegstellen ist ohne Zählen wiederauffindbar, und die Probe aufs Exempel lief noch am selben Tag

Alle drei Bedingungen sind erfüllt. Der Befund liegt **ausserhalb** des Pakets und ist kein
Rücklauf: Die Präfixfrage ist jetzt in drei Dokumenten als offen benannt und in keinem
verzeichnet, während der Kern sie in Code bereits beantwortet hat. Vorschlag
`0049-t46-gebietspraefix-entscheiden`.

---

## Wie ich den Änderungsumfang bestimmt habe

`git log --oneline -- daten/adressen.md` nennt als jüngste Commits **`50c916d`** („datenbauer:
0035-parameterdatei-belegstellen") und davor **`688e845`** („kernbauer:
0031-warnsatz-in-die-werkzeugkette"). Der Commit mit dem passenden Betreff, `4bd7985`
(„datenbauer: 0034-belegstellen-ohne-zeilennummern"), enthält **zwei Logbuchdateien und
sonst nichts**. Genau der Fall, vor dem das Paket unter Bedingung 2 gewarnt hat — gemessen
statt angenommen.

Die inhaltliche Arbeit steht in `688e845`, der reine Zeilenumbruch in `50c916d`.
Vergleichsbasis ist deshalb `688e845^`. Ein `diff` gegen die heutige Fassung ergibt **acht
Hunks, 77 berührte Zeilen**, an genau zwei Stellen der Datei:

```
29c29
540c540,542   553,555c555,561   567,572c573,581   575,581c584,591
586c596       588,594c598,607   600,602c613,615   610,612c623,625
```

Zeile 29 ist die Legendenzeile, alles übrige liegt ab Zeile 540 im Abschnitt *Befund 2*.
**Die Adresstabelle (Zeilen 43 bis 352) und alle vier Zählabschnitte (354 bis 450) kommen im
Diff nicht vor.**

## Bedingung 1 — kein tragender Verweis hängt mehr an einer Zeilennummer

Ich habe jede der sechs Stellen aus der Pakettabelle **einzeln** in der heutigen Fassung von
`technik.md` gesucht, über Tabellennummer und Zitat, ohne zu zählen. Jede war zu finden:

| Verweis im Paket | so steht er heute in `adressen.md` | heute in `technik.md` |
|---|---|---:|
| Zeile 816 | T45, Zeile `Datenanker(nr)`, Zitat „eine Reihe der Reihenliste weiter unten" | 1257 |
| Zeile 817 | T45, Zeile `Entwurf`, Zitat „die Tabelle ‚Jede Größe ohne Datenanker' in `spiel.md` nennt einen **Zahlenwert**" | 1258 |
| Zeile 820 (fünfmal) | T45, Zeile `Vorgabe(T-Nummer)`, Spalte „Beispiel", Zelle „`restwelt.basiswechsel` → 0 (T8)" | 1261 |
| Zeile 874 | T46, Überschrift im Wortlaut „T46 — Die elf Adressen, deren Herkunft dieses Dokument ist, abschliessend" | 1315 |
| Zeile 883 | T46-Zeile, die mit „`gebiet.<G>.basiswechsel`, alle fünf Gebiete" beginnt | 1324 |
| Zeile 236/237 | T49, Absatz „Zwei Adresspaare tragen denselben Wert, und das braucht eine Regel statt eines Zufalls", Zitat „`land.<L>.leitzins` und `land.<L>.instrument.leitzins.stand` sind dieselbe Größe, ebenso `land.<L>.haushaltssaldo` und `land.<L>.instrument.haushalt.stand`" | 390 bis 392 |

Zwei weitere Nummern, die das Paket nicht aufzählte, sind mitgegangen: die alten 818 und 819
heissen jetzt `Parameter(schluessel)` („`parameter.toml` nach T27", 1259) und
`Manifest(feld)` („vom Jahrgangsbau gerechnet und im Manifest ausgewiesen", 1260). Auch das
Zitat, mit dem der T46-Absatz weiterarbeitet — „Reihe 10 trägt drei Länder, die USA
definitionsgemäß nicht" —, steht heute in 1325.

**Der tote Verweis auf „Punkt 9 in `rueckstand.md`" ist weg** und durch die Sache selbst
ersetzt: „die Frage berührt `technik.md` und liegt beim Architekten. Sie ist hier
ausdrücklich **offen**". Ohne Punktnummer, wie verlangt.

**Gegenprobe über die ganze Datei, nicht nur über die vorgezeigten Stellen.** Eine Suche nach
Zeilennummernmustern findet in der heutigen Fassung noch **drei** Treffer, die auf
`technik.md` zeigen — Zeilen 541, 559 und 579 —, und alle drei tragen ein Abrufdatum und den
Zusatz „die Nummer(n) ist/sind nicht tragend". Das ist der vom Paket ausdrücklich zugelassene
Fall. Die übrigen Treffer (447, 497, 632) sind Zeilennummern **dieser** Tabelle („Zeilen
1 bis 44", „Zeile 253") und keine Fundstellen in `specs/`.

Dieselbe Suche über die Fassung vor dem Paket nennt **sechzehn** Verweise (Zeilen 29, 540,
553/554, 567, 569, 575 bis 592, 611). Keiner davon ist übrig geblieben.

**Die datierten Nummern waren am genannten Tag richtig.** Ich habe `technik.md` aus
`688e845` gezogen und nachgesehen: T46-Überschrift 1219, T49-Absatz 352, T46-Zeile
`gebiet.<G>.basiswechsel` 1228, T45-Zeile `Vorgabe(T-Nummer)` 1165 — genau die vier
Zahlen, die mit Datum in der Datei stehen. Heute sind es 1315, 390, 1324 und 1261, weil
`360421d` („architekt: 0011-stack-auf-cpp", 20:18) dazwischenkam. **Der Fall, den das Paket
verhindern sollte, ist drei Stunden nach dem Bau erneut eingetreten — und die Datei hat ihn
diesmal überstanden.** Das ist der belastbarste Nachweis für Bedingung 1, den es geben kann.

**Eine Zahl, die kein Verweis ist und trotzdem mit `technik.md` altert**, habe ich
mitgemessen: „Volltextsuche über `specs/0016-…/` nach `basiswechsel` ergibt zehn
Fundstellen, alle in `technik.md`, davon genau zwei mit vollständiger Adresse". Heute
nachgezählt: zehn Treffer (287, 358, 702, 910, 913, 1026, 1261, 1287, 1324, 2161), alle in
`technik.md`, genau zwei mit vollständiger Adresse (1261, 1324). Der Satz hält.

## Bedingung 2 — die Adresstabelle ist unverändert, die vier Zählungen gehen auf

Der Nachweis ist an der Datei geführt, nicht über `git diff --stat`. Gezählt in der heutigen
Fassung, unmittelbar an den Tabellenzeilen:

- **310 Zeilen.** Alle Tabellenzeilen mit laufender Nummer und Adresse: 310.
- **177 markiert, 133 nicht.** Dieselben Zeilen, gefiltert auf die Marke: 177; Gegenprobe
  ohne Marke: 133. Summe 310, und beide Zahlen sind die aus Zeile 29.
- **Klasse:** 1 zu 3, 2 zu 71, 3 zu 36, 4 zu 22, 5 zu 22, 6 zu 5, 7 zu 5, 8 zu 25, 9 zu 32,
  10 zu 4, 11 zu 83, 12 zu 2. Zeichengleich mit der Angabe im Vorspann, Summe 310.
- **Herkunft:** Datenanker 136, Entwurf 150, Parameter 11, Manifest 2, Vorgabe 11.
  Zeichengleich mit `136 + 150 + 11 + 2 + 11`, Summe 310.
- **Gruppe:** 198 + 56 + 52 + 4 = 310, und die Teilsummen gehen einzeln auf:
  je Gebiet 48, 36, 12, 64, 12 und 4 ergeben 176, also viermal 44; dazu 22 Restwelt: 198.
  Welt: 40, 2, 12 und 2 ergeben 56. Fonds: 5, 3, 20 und 24 ergeben 52. Partie: 4.

Dazu der Änderungsdiff als zweiter, unabhängiger Beleg: Keine der acht Hunks liegt im Bereich
43 bis 450. Tabelle und Zählungen sind byteweise dieselben wie vor dem Paket — sie konnten
sich also gar nicht bewegen, und sie haben es auch nicht.

## Bedingung 3 — keine Herleitung hat sich inhaltlich geändert

Die vierzehn namentlich genannten Zeilen einzeln gezogen:

| Nr. | Adresse | Marke |
|---:|---|---|
| 44, 88, 132, 176 | `land.<L>.basiswechsel` | **je eine** |
| 198 | `restwelt.basiswechsel` | keine |
| 23, 67, 111, 155 | `land.<L>.aufsichtszaehler` | keine |
| 63, 107, 151 | `land.<L>.wechselkurs` | **je eine** |
| 79 | `land.CN.instrument.haushalt.gegendruck` | **eine** |
| 222 | `handel.DE.RW.2` | **eine** |

Alle wie vor dem Paket, und alle vierzehn Zeilen liegen ausserhalb jeder Hunk des
Änderungsdiffs.

**Die Präfixfrage ist weiterhin offen und nicht entschieden.** Der Absatz *Was hier offen
bleibt und hier nicht entschieden wird* sagt es zweimal ausdrücklich, nennt beide denkbaren
Antworten und zeigt, dass beide dieselben Marken ergeben. Eine Antwort steht nirgends in der
Datei; ich habe über das ganze Verzeichnis nach Präfix, praefix und `gebiet.<G>.` gesucht.

## Wonach ich sonst gesucht und was ich nicht gefunden habe

- **Eine übersehene Belegstelle** ausserhalb des Abschnitts *Befund 2*. Die Volltextsuche
  über die alte Fassung nennt sechzehn Stellen; alle sechzehn sind ersetzt.
- **Eine datierte Nummer, die schon am Tag des Schreibens falsch war.** Gegen den Blob aus
  `688e845` geprüft — alle vier stimmten.
- **Eine Schattenfassung in `daten/`**, die den alten Wortlaut weiterführt. Das ist die Lehre
  aus meiner Prüfung zu 0032: `git ls-files daten/` führt zwölf `.tmp`-Dateien, die in
  `git status` nie auftauchen. Ich habe sie und das ganze Venture nach „Zeile 820", „Zeile
  874", „Zeile 236" und „Punkt 9 in" durchsucht. Treffer gibt es nur noch in `befunde/`
  (historische Prüfprotokolle, mit Datum, richtig so) und im Paket selbst — **keine zweite
  Fassung von `adressen.md`**.
- **Eine still mitgenommene Änderung an Marke, Zahl oder Herleitung.** Der Diff berührt
  ausserhalb von Zeile 29 nur Prosa des Abschnitts *Befund 2*.

## Was ausdrücklich kein Befund ist

- **Der Umbruch in `50c916d`.** Er verschiebt Wörter zwischen Zeilen und ändert kein Zeichen
  des Textes. `specs/` schweigt zur Zeilenbreite.
- **Dass der Verweis auf `rueckstand.md` ersatzlos entfallen ist.** Das Paket hat es so
  verlangt. Was daraus folgt, steht unten als Befund und nicht hier.
- **Der Halbsatz „steht mit Index" in Zeile 29 und 555.** Das dort angeführte Zitat aus T49
  schreibt `land.<L>.leitzins` mit Platzhalter, nicht mit Index — die Formulierung ist also
  ungenauer, als sie klingt. Sie stammt wörtlich aus Paket 0015, sie stand vor diesem Paket
  genauso da, und Bedingung 3 verlangt ausdrücklich, dass keine Herleitung angefasst wird.
  Der Bauagent hat richtig gehandelt, indem er sie stehen liess. Ich hebe daran kein
  Kriterium an und melde es nur, damit der nächste Prüfer nicht darüber stolpert: Die alte
  Zeilennummer hat die Ungenauigkeit verdeckt, der neue Verweis macht sie sichtbar. Das ist
  eine Wirkung des Pakets und keine Nebenwirkung.

## Befund 1 — die Präfixfrage hat keinen Ort mehr, und der Kern hat sie schon beantwortet

**Ausserhalb des Pakets. Kein Rücklauf, keine Änderung am Urteil oben.**

Der Verweis „Punkt 9 in `rueckstand.md`" war die letzte Stelle, an der die offene
Präfixfrage verzeichnet war. Er musste weg — er zeigte ins Leere, weil `rueckstand.md` je
Baulauf neu geschrieben wird. Nach dem Paket gilt:

