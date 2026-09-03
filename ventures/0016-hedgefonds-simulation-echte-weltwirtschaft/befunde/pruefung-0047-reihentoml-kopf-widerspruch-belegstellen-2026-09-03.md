---
typ: pruefung
paket: 0047-reihentoml-kopf-widerspruch-belegstellen
pruefer: daten-pruefer
datum: 2026-09-03
urteil: geprueft
kriterium_geprueft: Alle vier Bedingungen einzeln nachgemessen -- die Zeichenfolge gegriffen, die sieben Schnitte selbst gelaufen, die zwoelf ersetzten Zitate als Teilzeichenkette an ihrer Adresse wiedergefunden und die Vorfassung der Datei geparst gegen die neue gelegt.
befunde: 3
---

# Die vier Bedingungen halten. Drei Befunde liegen daneben, keiner davon traegt einen Ruecklauf.

Geprueft gegen `aufgaben/0047-reihentoml-kopf-widerspruch-belegstellen.md`, Abschnitt
*Abnahme*, und gegen nichts sonst. Werkzeuglage dieses Laufs: `python3` ueber Heredoc frei,
`Grep` frei, `grep` im Bash-Aufruf abgewiesen. Alle Zahlen unten sind in diesem Lauf am
2026-09-03 selbst erzeugt, keine ist aus dem Paket uebernommen.

Vergleichsfassung fuer die Negativbedingung: `66a463b~1`, gezogen mit `git show` und mit
`tomllib` geparst.

## Bedingung 1 -- Kopf und Zaehlregel nennen nur noch Reihe 3

**Erfuellt.**

| geprueft | Aufruf | Ergebnis |
|---|---|---|
| Zeichenfolge "Reihe 3 (PWT-Kapitalstock) und Reihe 14 (BACI)" | Grep ueber `daten/reihen.toml` | **0 Treffer** |
| Bestandsprobe statt Textprobe | Grep `ungemessen`, dann `tomllib` | `art = "ungemessen"` steht **genau einmal**, Z. 514 |
| welche Reihe das ist | `tomllib`, Schleife ueber alle 19 Reihen und ihre Umrechnungsbloecke | **Reihe 3, "Kapitalstock"** -- keine zweite |

Die Textprobe allein zeigt nur, dass ein Satz weg ist. Die Bestandsprobe zeigt, dass die neue
Aussage stimmt: Es gibt tatsaechlich nur noch einen ungemessenen Block, und er gehoert Reihe 3.

**Die geforderte Unterscheidung steht an beiden Stellen, und sie haengt nicht am Zahlenwert.**
Leseregel 3 im Kopf trennt die **gesetzte** Eins ("behauptet, es sei nichts umzurechnen, ohne
dass jemand die Quelleneinheit gelesen hat" -- weiter verboten) von der **gemessenen**
(Reihe 14, mit Wortlaut und ausgeschriebener Rechnung) und sagt ausdruecklich,
auseinanderzuhalten seien sie "**nicht am Zahlenwert**, sondern an den Feldern `status` und
`beleg`". `[pruefweg].zaehlregel_umrechnung` sagt dasselbe in einem Satz und verweist auf
`[[widerspruch]]` Nr. 9. Die Trennung ueber `status`/`beleg` ist die einzige, die ein Werkzeug
nachvollziehen kann; ueber den Zahlenwert waere sie nicht pruefbar.

## Bedingung 2 -- der neunte Widerspruch

**Erfuellt.** Die Stuecke einzeln geprueft, nicht als Ganzes:

| verlangt | gemessen | wie |
|---|---|---|
| Eintrag `nr = 9` | neunter Eintrag der Liste `widerspruch` | `tomllib`: Liste hat 9 Eintraege, `[8]['nr']` ist 9 |
| `betrifft_reihen = [14, 16]` | `[14, 16]` | `tomllib` |
| `entscheidet` = Architekt | "Architekt -- ein Deflatorschritt in der Umrechnung der Reihe 14 oder eine Festlegung in T5 Klasse 2 beziehungsweise T23" | `tomllib` |
| gemessener Wortlaut "in thousands current USD" | im Feld `lang` und zeichengleich in `begruendung` des Umrechnungsblocks der Reihe 14 ("Value of the trade flow (in thousands current USD)") | Teilzeichenkettenprobe |
| dagegen T5 Klasse 2 | "Tausend USD zu konstanten Preisen des Basisjahrs" | **`specs/.../technik.md` Z. 278 im Wortlaut gegengelesen**; dieselbe Tabellenzeile fuehrt "Handelsstrom" namentlich, wie der Eintrag behauptet |
| Feld `in_dieser_datei` | vorhanden; sagt Faktor 1 eingetragen und **gemessen**, allein die Groessenordnung entschieden, Preisbasis nicht aufgeloest, nennt die beiden `offen`-Stellen | `tomllib`, Schluessel `betrifft_reihen, entscheidet, in_dieser_datei, kurz, lang, nr` |
| vier Moeglichkeiten aus `einheitenbefund-pwt-baci.md` Abschnitt 5, keine gewaehlt | alle vier, je mit dem, was an ihnen offen ist; Schlusssatz "Diese Datei waehlt keine der vier." | Abschnitt 5 der Befunddatei danebengelegt, Punkt fuer Punkt |

**Die uebernommenen Sachbehauptungen habe ich nicht uebernommen, sondern gelegt.** Ein Befund
wird falsch, ohne dass ihn jemand anfasst:

- "T37 fuehrt den Handelsblock unter den sechzehn Pruefgegenstaenden" -- `technik.md`
  Z. 2114-2126: Tabelle mit Summe **16**, Zeile "Handelsblock | 1 | 40 Stroeme". Haelt.
- "T42 rechnet ueber jeden einzelnen den MAPE gegen die Schwelle 2.000 (also 20 Prozent)" --
  `technik.md` Z. 2137: Niveaureihen, ausdruecklich "40 Handelsstroeme", Schwelle
  "**2.000 (= 20 %)**". Haelt. Dass T37 die 40 Einzelwerte danach zum **Median** zusammenzieht,
  ist T37s Sache und nicht das, was der Satz behauptet.
- "Fenster 1997 bis 2021" -- Pruefjahrgang laut `technik.md` Z. 12 und Z. 1354. Haelt.
- "Reihe 14 traegt 40 Handelsstroeme" -- `handelsblock_stroeme = 40` in der Datei selbst.
- **Die Richtungsaussage nachgerechnet statt nachgelesen:** "unter der Annahme steigender
  Preise faellt `durchgriff` fuer Jahre nach 2015 zu hoch und davor zu niedrig aus".
  `durchgriff = H/N`, `H` nominal, `N` in konstanten Preisen von 2015 (Reihe 1,
  `NY.GDP.MKTP.KD`, "constant 2015 US$"). Fuer t nach 2015 ist der nominale Zaehler groesser
  als der reale, der Quotient also zu hoch; fuer t vor 2015 kleiner, also zu niedrig. Stimmt
  in beide Richtungen.

## Bedingung 3 -- die sieben Schnitte und die Belegstellen

**Erfuellt.** Ich habe die sieben Schnitte **selbst laufen lassen**, mit den Mustern, die die
Felder nennen, gegen die eingespielte Fassung. Alle vierzehn Zahlen stimmen mit dem ueberein,
was in der Datei steht:

| Schnitt | Muster | von mir gemessen | in der Datei |
|---|---|---:|---:|
| 1 | `[=] [0-9]+\.[0-9]` | 6 | 6 |
| 2 | drei Apostrophe, Zeilen / Vorkommen | 29 / 54 | 29 / 54 |
| 2 | am Zeilenanfang oder Zeilenende | 27 | 27 |
| 2 | drei doppelte Anfuehrungszeichen | 1 | 1 |
| 3 | `^\[\[` | 113 | 113 |
| 3 | nach Typ | 19+9+22+20+39+2+2 = 113 | dieselbe Aufzaehlung |
| 4 | `^exogen_ab = ` / `^verkettet_ab = ` / `^lizenzurteil = ` | 19 / 19 / 19 | je 19 |
| 4 | Sammelmuster der acht Pflichtfelder | 152 | 152 |
| 4 | `^t37_klasse = ` | 20 | 20 |
| 4 | `^nr = ` | 28 | 28 |
| 5 | `^sollreihen = ` Zeilen / Summe | 21 / 43 | 21 / 43 |
| 5 | `^sollreihen` | 28 | 28 |
| 7 | `^wortlaut = ` / `^wortlaut_form` | 20 / 2 | 20 / 2 |

Die beiden erhoehten Zahlen aus der Bedingung sind da und richtig: `schnitt_3` auf 113 mit
**9 mal widerspruch**, `schnitt_4` auf `^nr = ` **28 = 19 + 9**.

**Die Zerlegungen einzeln nachgerechnet, nicht nur die Summen.** `schnitt_5` sagt, 19 der 21
stuenden auf Reihenebene, davon dreizehn Nullen und sechs Werte "bei den Reihen 1, 2, 8, 9,
10 und 11". `tomllib` ueber die Reihenebene liefert genau (1,4) (2,12) (8,4) (9,4) (10,3)
(11,4), Summe **31**; die beiden restlichen sind die Untertabellenwerte 4 und 8, und
31 + 12 = 43. Die sieben Summenschluessel, die `schnitt_5` neu namentlich aufzaehlt statt
ueber Zeilennummern, stehen so in `[zaehlung]` (vier) und `[zaehlung.lizenz]` (drei) --
geprueft ueber die Schluesselnamen des geparsten Baums.

**Zu `schnitt_6`, wo die Datei sich selbst berichtigt hat:** Der alte Text sagte "elf
Schluessel". Nachgezaehlt sind es zehn -- `schnitt_4` fuehrt `lizenzurteil` zweimal, einzeln
und im Sammelmuster, und `t37_klasse` (20) und `nr` (28) zaehlen nicht 19. Die berichtigte
Zahl **zehn** ist richtig. Kein Kriterienzuwachs, sondern genau das, was Bedingung 3 verlangt:
dass der Schnitt gegen die neue Fassung stimmt.

### Die Belegstellen -- ersetzt, und die Ersetzungen tragen

Nachweis der Bedingung, mit ihrem eigenen Muster und mit zwei schaerferen:

- `Zeile [0-9]{3,4}` oder `^\s*zeile` ueber `[pruefweg]` (Z. 1625-1642): **0 Treffer**.
- Weiter gefasst, `Zeilen? [0-9]{1,4}`: **0 Treffer** -- die Ein- und Zweisteller sind auch weg.
- Haerteste Fassung: **jede** drei- bis vierstellige Zahl im Abschnitt aufgelistet und einzeln
  angesehen. Uebrig bleiben ausschliesslich Datumsangaben, Zaehlergebnisse (113, 112, 152),
  Paketkennungen (0017, 0022, 0036) und deutsche Tausendertrenner (10.000, 1.000). Keine
  Adresse.

**Und dann die Probe, die der Nachweis nicht verlangt: taugen die Ersetzungen?** Eine
Zeilennummer durch eine Adresse zu ersetzen, die nicht traegt, waere schlimmer als die
Zeilennummer. Ich habe alle zwoelf Zitate als Teilzeichenkette gesucht -- jedes wurde an
seiner genannten Adresse gefunden:

| Ort | Zitat (Anfang) | gefunden |
|---|---|---|
| `schnitt_1`, sechs Fundstellen | "Faktor 10.000 auf den Rohkurs gegen T5 Klasse 6"; "Das Arbeitspaket gibt fuer Reihe 10 den Faktor 10.000 vor"; "T5 Klasse 7 (Realindizes): Index, Startjahr"; "Der Faktor 10.000 auf den Rohkurs steht gegen T5 Klasse 6"; "T5 Klasse 5 (Nominalindizes, darunter Preisniveau): Index, Startjahr"; "Kein Fremdbestand, keine Quelleneinheit, also keine Umrechnung" | alle sechs, je genau einmal ausser dem Zitat selbst |
| `schnitt_2` | "Il est garanti au" (Etalab, Reihe 14) -- Z. 1310, die einzige Zeile mit drei doppelten Anfuehrungszeichen; "International Labour Organization (ILO), type: estimates based on external database;" (Reihe 6, drei Zeilen); "Staff estimates;" bis "Consolidated Tariff Schedules (CTS), World Trade Organization (WTO)" (Reihe 13, fuenf Zeilen) | alle |
| `schnitt_2_offen`, in die **fremde** Datei | `lizenzbefund-reihen.md`, Abschnitt Reihe 1 bzw. Abschnitt 2b und 2c, je "der Block unter der Zwischenzeile Feld `Source` im Wortlaut" | beide Zwischenzeilen existieren, beide Bloecke fuehren die Quelle in **drei** Zeilen, und der Zusatz "bei beiden Codes zeichengleich dasselbe" steht dort woertlich |
| `toml_geprueft`, in die **Rollendatei** | "Der Schluessel `tools` nennt Read, Glob, Grep, WebSearch, WebFetch, Edit(ventures/**) und Edit(notizen/datenbauer.md)" | `agents/rollen/datenbauer.md` Frontmatter: exakt diese sieben, in dieser Reihenfolge. Die abgeloeste Angabe "Z. 7-14" war zur Bauzeit richtig -- die Ersetzung ist keine Korrektur, sondern eine Haltbarmachung |

Dass die Zitate in `schnitt_1` **vor** dem Gleichheitszeichen abgeschnitten sind, ist kein
Schoenheitsfehler, sondern notwendig: mit Gleichheitszeichen stuende der Schnitt auf 7 statt 6
und widerlegte sich selbst. Nachgerechnet.

Eine einzige Stelle liest sich zweideutig: `schnitt_2_offen` zitiert "National Statistical
Offices (NSOs)**,**", die Quelle (Z. 437) hat dort ein Semikolon. Das Komma ist die Zaesur des
deutschen Satzes vor "gegen lizenzbefund-reihen.md"; der Wortlaut bis "(NSOs)" ist
zeichengleich vorhanden, und die Adresse (Reihe 2b und 2c, Feld `wortlaut`) ist eindeutig.
**Kein Befund** -- Zeichensetzung um ein nicht ausgezeichnetes Zitat herum ist Geschmack, und
`specs/` schweigt dazu.

## Bedingung 4 -- Reihen 14 und 16 unveraendert

**Erfuellt, und staerker als verlangt.** Ich habe nicht die drei genannten Stellen angesehen,
sondern die Vorfassung und die neue Fassung geparst und Block gegen Block gelegt:

- **Geaenderte Reihen: keine.** Alle 19 Reihenbaeume sind identisch, nicht nur 14 und 16.
- `widerspruch` 1 bis 8: identisch. Der neunte ist angehaengt, nicht eingeschoben.
- `[zaehlung]`, `[datei]`, `[namensnennung]`: identisch.
- Geaendert in `[pruefweg]`: `toml_geprueft`, `toml_geprueft_grenze`, `schnitt_1` bis
  `schnitt_6` ohne `schnitt_2_wahl`, `zaehlregel_umrechnung`. Sonst nichts.

Der Aenderungsdiff bestaetigt es auf Zeichenebene: drei Hunks, bei Z. 41, Z. 276 und Z. 1623.
Reihe 14 (ab Z. 1280) und Reihe 16 liegen in keinem davon. Die drei Stellen aus 0036 --
Umrechnungsblock der Reihe 14 mit `art = "keine"`, `faktor = 1`, `status = "gemessen"`, die
ersten beiden `offen`-Eintraege der Reihe 14, der erste der Reihe 16 -- stehen unberuehrt.
**Es ist nichts neu gemessen worden.**

## Die Erweiterung, die der Bauagent selbst benannt hat

`toml_geprueft` musste angefasst werden -- es trug die letzte Zeilennummer in `[pruefweg]`.
Dass danach `toml_geprueft_grenze` und der Schlusssatz von `schnitt_6` nicht stehen bleiben
konnten, folgt zwingend: Beide behaupteten eine Luecke, die derselbe Absatz gerade als
geschlossen ausweist. **Kein Ruecklaufgrund** -- die Erweiterung misst keine Quelle nach,
beruehrt keine Reihe und faellt keine Entscheidung.

**Den Parserlauf habe ich unabhaengig wiederholt**, weil eine Aussage der Datei ueber sich
selbst sonst unbelegt bliebe: `tomllib.load` gegen die eingespielte Fassung laeuft fehlerfrei,
die Wurzel fuehrt die sechs genannten Tabellen, `reihe` hat 19 Eintraege, `widerspruch` 9, und
die Summe `sollreihen` ueber die Reihenebene ist 31. Alles, was dort steht, trifft zu.
