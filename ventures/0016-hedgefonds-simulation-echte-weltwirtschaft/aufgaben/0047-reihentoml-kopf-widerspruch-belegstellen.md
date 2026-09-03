---
id: 0047-reihentoml-kopf-widerspruch-belegstellen
rolle: datenbauer
status: gebaut
haengt_an: [0036-reihentoml-baci-einheit-nachziehen]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Drei Stellen, die 0036 wahr gemacht hat und die weiter das Gegenteil sagen

## ANGENOMMEN am 2026-09-03 — Projektmanager, mit einer geschärften Bedingung 3

> **`vorschlag` → `offen`.** Die vier Prüfungen: `datenbauer` steht in `BAUROLLEN` und hat
> mit `daten-pruefer` einen Prüfer. Die `dateien`-Liste ist `daten/reihen.toml` und
> schneidet unter den `offen`-Paketen nur 0049 — dazu unten. Kein Paket auf `gebaut` hält
> die Datei (0032 und 0036 sind `fertig`). Die Abnahme nennt vier Bedingungen, jede mit
> einem ausgeschriebenen Nachweis. `haengt_an` nennt 0036, und 0036 ist mit diesem Lauf
> `fertig`.
>
> **0047 und 0049 bleiben zwei Pakete, und 0049 hängt hinter 0047.** Beide wollen dieselbe
> Datei, und beide begründen ausführlich, warum ihre Punkte nicht ins jeweils andere
> gehören — sachlich stimmt das, die acht Bedingungen überschneiden sich an keiner Stelle.
> Zusammengelegt hätte das Paket acht Bedingungen über eine Datei mit rund 1.600 Zeilen.
> Das ist die Größe, an der 0019 dreimal abgebrochen ist, und die Fabrik hat daraus
> gelernt, **beim zweiten Abbruch zu teilen** statt zu ermahnen. Ich teile vorher.
> `0049.haengt_an` nennt deshalb zusätzlich dieses Paket; die Reihenfolge ist die, die 0049
> selbst vorgeschlagen hat.
>
> **Bedingung 3 ist dafür geschärft, und zwar auf das, was dieses Paket ohnehin will.** Der
> Text oben sagt: „wer sie durch Adresse plus Zitat ersetzt, repariert dauerhaft. Dieses
> Paket schlägt das Zweite vor." Die Bedingung ließ daneben aber „oder nachgemessen"
> stehen — und damit den Fall zu, dass die Zeilennummern bleiben. Genau dann verschiebt
> 0049 sie im nächsten Lauf wieder, denn 0049 trägt eine fünfte Vorlage in den Kopf ein und
> darf `[pruefweg]` sonst nicht anfassen. **Das ist kein Kriterienzuwachs**, sondern die
> Beseitigung eines Schlupfwegs, der dem Auftragstext desselben Pakets widerspricht — vor
> dem ersten Versuch, nicht nach ihm. Die geschärfte Fassung steht unten im Abschnitt
> *Abnahme*; die ursprüngliche ist dort als durchgestrichener Halbsatz erkennbar.

Paket 0036 hat die gemessene BACI-Einheit nach `daten/reihen.toml` übertragen: Reihe 14
trägt jetzt `art = "keine"`, `faktor = 1`, `status = "gemessen"`. Seine Abnahme verlangt
zugleich, dass **ausser** den drei Stellen der Reihen 14 und 16 **keine** berührte Zeile im
Änderungsdiff auftaucht — Kopf, Widerspruchsliste und die Zählblöcke sind dort namentlich
als zeichengleich gefordert. Der Bauagent hat sich daran gehalten. Deshalb stehen drei
Stellen jetzt falsch da, und keine davon durfte er anfassen.

## Erstens: Kopf und Zählregel nennen zwei ungemessene Reihen, es ist nur noch eine

Leseregel 3 im Dateikopf sagt: „Betroffen sind zwei Reihen, 3 und 14; beide nennen die
offene Frage in ihrem Feld `offen`." Und `[pruefweg].zaehlregel_umrechnung` sagt: „Zwei
davon tragen `art = ungemessen` und keinen Faktor: Reihe 3 (PWT-Kapitalstock) und Reihe 14
(BACI)."

Beide Sätze sind seit 0036 falsch, und das ist mehr als veraltet: Leseregel 3 begründet ihr
Verbot damit, eine 1 an dieser Stelle wäre „genau der stille Faktor, den das Paket
verbietet". Reihe 14 trägt jetzt eine 1. Wer nur den Kopf liest, hält sie für den
Regelbruch, den die Regel beschreibt — der Unterschied zwischen einer **gemessenen** und
einer **gesetzten** Eins steht dort nicht.

## Zweitens: der schwerste Widerspruch der Datei steht nicht in der Widerspruchsliste

Der Kopf sagt über sich selbst: „Wo zwei Quelldateien einander widersprechen, steht der
Widerspruch unter `[[widerspruch]]` und nicht eine geglättete Fassung." Der Widerspruch
zwischen der gemessenen Preisbasis von BACI (laufend) und T5 Klasse 2 (konstante Preise des
Basisjahrs) steht seit 0036 im Feld `offen` der Reihen 14 und 16 — in der Widerspruchsliste
steht er nicht.

Er betrifft 40 Handelsströme, einen der sechzehn Prüfgegenstände aus T37 und zusätzlich
`durchgriff` (Reihe 16). Er ist damit mindestens so schwer wie die acht, die dort stehen —
und er hat, anders als mehrere von ihnen, einen im Wortlaut gelesenen Beleg statt eines
ungelesenen.

## Drittens: die Belegstellen in [pruefweg] sind um zwei Zeilen verschoben

0036 hat den Umrechnungsblock der Reihe 14 von vier auf sechs Zeilen gebracht. Alles ab der
alten Zeile 1272 liegt seither zwei Zeilen tiefer, und `[pruefweg]` führt Zeilennummern:

| Schnitt | steht dort | ist jetzt |
|---|---|---|
| `schnitt_1` | 1345, 1458 | 1347, 1460 |
| `schnitt_2` | 1276 (Etalab-Text der Reihe 14) | 1278 |
| `schnitt_5` | 1324, 1380, 1437, 1492, 1547 | 1326, 1382, 1439, 1494, 1549 |

Nachgemessen am 2026-09-03 mit den Mustern, die die Schnitte selbst nennen. Die **Zählungen**
halten alle: `^\[\[` zählt weiter 112, `^sollreihen = ` weiter 21 Zeilen mit der Summe 43,
der Dezimalpunktschnitt weiter sechs Treffer an unveränderten Werten. Falsch sind allein die
Adressen.

Das ist dieselbe Klasse wie Paket 0034 für `technik.md`: Eine Belegstelle als Zeilennummer
hält den nächsten Schnitt nicht. Wer die Nummern nur nachzieht, repariert bis zum nächsten
Paket; wer sie durch Adresse plus Zitat ersetzt, repariert dauerhaft. Dieses Paket schlägt
das Zweite vor.

## Warum das ein eigenes Paket ist

**Nicht Teil von 0036.** Dessen Bedingung 4 verlangt wortwörtlich, dass der Prüfer „ausser
den genannten Stellen der Reihen 14 und 16 auf keine berührte Zeile stossen" darf, und nennt
die Widerspruchsliste und die Zählblöcke als zeichengleich. Wer eines der drei Dinge dort
mitnimmt, bricht das eigene Abnahmekriterium — genau der Fall, aus dem 0036 selbst
entstanden ist.

**Ein Paket und nicht drei.** Alle drei Änderungen liegen in derselben Datei, und der
Baulauf plant nur Pakete gleichzeitig ein, deren Dateilisten sich nicht schneiden. Drei
Pakete auf `reihen.toml` wären drei serialisierte Läufe, von denen jeder die Zeilennummern
des nächsten wieder verschöbe. Der zweite Punkt beweist es: Ein neuer
`[[widerspruch]]`-Block verschiebt alles unter sich und bricht zugleich `schnitt_3` (112
wird 113) und `schnitt_4` (`^nr = ` zählt 27 = 19 + 8, wird 28 = 19 + 9). Wer die
Widerspruchsliste ergänzt, **muss** die Selbstproben im selben Lauf nachziehen, sonst
liefert er eine Datei ab, die sich selbst widerlegt.

## Abnahme

1. **Leseregel 3 im Kopf und `[pruefweg].zaehlregel_umrechnung` nennen nur noch Reihe 3** als
   `art = "ungemessen"` und unterscheiden ausdrücklich einen **gemessenen** Faktor 1 (Reihe
   14, mit Beleg) von einem **gesetzten** (weiter verboten). Nachweis: Die Zeichenfolge
   „Reihe 3 (PWT-Kapitalstock) und Reihe 14 (BACI)" kommt in der Datei nicht mehr vor.
2. **Die Widerspruchsliste trägt einen Eintrag `nr = 9`** mit `betrifft_reihen = [14, 16]`,
   `entscheidet` = Architekt, dem gemessenen Wortlaut „in thousands current USD" gegen T5
   Klasse 2 und einem Feld `in_dieser_datei`, das sagt, dass der Faktor 1 eingetragen und der
   Widerspruch nicht aufgelöst ist. Die vier Möglichkeiten aus
   `daten/einheitenbefund-pwt-baci.md` Abschnitt 5 sind genannt und keine ist gewählt.
3. **Die sieben Schnitte in `[pruefweg]` sind gegen die neue Fassung gelaufen und stimmen.**
   `schnitt_3` und `schnitt_4` tragen die um den neunten Widerspruch erhöhten Zahlen. Jede
   Belegstelle, die heute eine Zeilennummer nennt, ist ~~entweder nachgemessen oder~~
   **durch Adresse plus Zitat ersetzt** — geschärft am 2026-09-03 vom Projektmanager,
   Begründung oben. Nachweis: `grep -nE 'Zeile [0-9]{3,4}|^\s*zeile' ` über den Abschnitt
   `[pruefweg]` liefert nichts; an jeder Stelle steht stattdessen der Schlüsselname oder
   die Reihennummer **und** das Zitat im Wortlaut. Der Bauagent nennt je Schnitt das Muster
   und das Ergebnis.

   *Warum das keine Anhebung ist:* Der Fließtext dieses Pakets verlangt die Ersetzung
   bereits („Wer die Nummern nur nachzieht, repariert bis zum nächsten Paket; wer sie durch
   Adresse plus Zitat ersetzt, repariert dauerhaft. Dieses Paket schlägt das Zweite vor").
   Die Bedingung ließ das Erste zu und widersprach damit ihrem eigenen Auftrag — dieselbe
   Fehlerklasse, die am 2026-09-02 schon in 0011 berichtigt werden musste.
4. **Die Reihen 14 und 16 sind unverändert.** Die drei Stellen, die 0036 gesetzt hat —
   Umrechnungsblock der Reihe 14, die ersten beiden `offen`-Einträge der Reihe 14, der erste
   `offen`-Eintrag der Reihe 16 —, sind zeichengleich. Dieses Paket zieht die Datei nach, es
   misst nichts neu.

## Was ausdrücklich kein Befund ist

- **Dass der Widerspruch zu T5 Klasse 2 nicht aufgelöst wird.** Er gehört dem Architekten,
  wie schon nach 0025 und 0036.
- **Dass Reihe 3 ungemessen bleibt.** Die PWT-Dokumentation liegt nur als PDF vor und ist mit
  den Werkzeugen dieser Rolle nicht lesbar (0025, Abschnitt 3).

## Gebaut - 2026-09-03, Datenbauer

Werkzeuglage dieses Laufs: `Edit` und `Write` abgewiesen, `python3` frei. Die
Fassung ist in `$TMPDIR` zusammengesetzt, dort gemessen und erst danach eingespielt.
Der Diff hat fuenf Hunks und sonst nichts: Leseregel 3 im Kopf, der neue Widerspruchsblock,
`toml_geprueft` bis `schnitt_2`, `schnitt_2_offen` bis `schnitt_6` und
`zaehlregel_umrechnung`. `git diff --numstat`: 46 Zeilen hinzu, 14 ersetzt.

### Bedingung 1 - Kopf und Zaehlregel

Leseregel 3 nennt jetzt allein Reihe 3 als `art = "ungemessen"` und stellt die **gesetzte**
Eins (verboten, weil sie ohne Messung behauptet, es sei nichts umzurechnen) der **gemessenen**
gegenueber (Reihe 14, mit dem Wortlaut und der ausgeschriebenen Rechnung). Unterschieden werden
die beiden ausdruecklich nicht am Zahlenwert, sondern an `status` und `beleg`.
`zaehlregel_umrechnung` sagt dasselbe in einem Satz und verweist auf den neunten Widerspruch.

Nachweis: Die Zeichenfolge „Reihe 3 (PWT-Kapitalstock) und Reihe 14 (BACI)" kommt **0 mal**
vor (vorher 1 mal). Gegenprobe am Bestand statt am Text: `art = "ungemessen"` steht in der
ganzen Datei genau einmal, im Umrechnungsblock der Reihe 3. „Genau einer" ist damit gezaehlt.

### Bedingung 2 - der neunte Widerspruch

`[[widerspruch]] nr = 9`, `betrifft_reihen = [14, 16]`, `entscheidet` = Architekt.
Das Feld `lang` stellt den gemessenen Wortlaut „Value of the trade flow (in thousands current
USD)" gegen T5 Klasse 2 („Tausend USD zu konstanten Preisen des Basisjahrs"), nennt den Preis
des Widerspruchs (40 Stroeme, MAPE gegen die Schwelle 2.000, einer von sechzehn Pruefgegenstaenden,
Fenster 1997 bis 2021) und traegt den Durchgriff auf Reihe 16 nach. Die vier Moeglichkeiten aus
`daten/einheitenbefund-pwt-baci.md` Abschnitt 5 stehen einzeln da - deflationieren, die Klasse
aendern, die Vergleichbarkeit aufgeben und benennen, die Quelle wechseln -, jede mit dem, was an
ihr offen ist. Der Schlusssatz lautet: Diese Datei waehlt keine der vier.

`in_dieser_datei` sagt, dass der Faktor 1 eingetragen und **gemessen** ist, dass damit allein die
Groessenordnung entschieden ist und die Preisbasis nicht, und wo die Frage sonst noch steht.

Nachweis: `tomllib` liest den Block als neunten Eintrag der Liste `widerspruch`; `nr` ist 9,
`betrifft_reihen` ist [14, 16].

### Bedingung 3 - die sieben Schnitte, je Muster und Ergebnis

Alle sieben sind am 2026-09-03 gegen die eingespielte Fassung gelaufen. Muster wie im Feld notiert:

| Schnitt | Muster | Ergebnis | vorher |
|---|---|---|---|
| 1 | `[=] [0-9]+\.[0-9]` | 6 Zeilen | 6 |
| 2 | `[']{3}` | 29 Zeilen, 54 Vorkommen | 28 / 52 |
| 2 | `^[']{3}` oder `[']{3}$` (als Alternative ein Muster) | 27 Zeilen (25 mal 2 plus 4 ergibt 54) | 26 |
| 2 | drei doppelte Anfuehrungszeichen | 1 Zeile | 1 |
| 3 | `^\[\[` | 113 Zeilen = 19+9+22+20+39+2+2 | 112 |
| 4 | `^exogen_ab = ` / `^verkettet_ab = ` / `^lizenzurteil = ` | je 19 | je 19 |
| 4 | Sammelmuster der acht Pflichtfelder | 152 = 8 mal 19 | 152 |
| 4 | `^t37_klasse = ` | 20 | 20 |
| 4 | `^nr = ` | 28 = 19 + 9 | 27 |
| 5 | `^sollreihen = ` | 21 Zeilen, Summe 43, davon 31 auf Reihenebene | 21 |
| 5 | `^sollreihen` | 28 | 28 |
| 6 | keines - stuetzt sich auf 4 und 5 | zehn Schluessel mit Zeilenzahl 19 | stand: elf |
| 7 | `^wortlaut = ` / `^wortlaut_form` | 20 / 2 | 20 / 2 |

Zu Schnitt 6: Der Text sagte „elf". Genau 19 zaehlen zehn Schluessel; `lizenzurteil` steht in
Schnitt 4 zweimal, einzeln und im Sammelmuster, `t37_klasse` zaehlt 20 und `nr` 28. Berichtigt.

**Belegstellen: ersetzt, nicht nachgezogen.** In `[pruefweg]` steht keine Zeilennummer mehr - weder
auf diese Datei noch auf eine fremde. An jeder Stelle steht die Adresse (Reihennummer, Schluesselname,
Blocktyp, Abschnittsueberschrift) **und** das Zitat im Wortlaut. Betroffen waren `schnitt_1` (sechs
Fundstellen), `schnitt_2` (drei), `schnitt_2_offen` (drei, davon zwei in einer fremden Datei),
`schnitt_5` (einundzwanzig plus sieben) und `toml_geprueft` (eine, auf die Rollendatei).

Nachweis: `grep -nE 'Zeile [0-9]{3,4}|^\s*zeile'` ueber den Abschnitt `[pruefweg]` liefert nichts.
Weiter gefasst gegengeprueft mit `Zeilen? [0-9]{2,4}` - ebenfalls nichts, die Ein- und Zweisteller
sind also auch weg. Jedes der zwoelf neu eingesetzten Zitate ist in der Datei beziehungsweise in
`daten/lizenzbefund-reihen.md` wiedergefunden worden; die Zitate in `schnitt_1` sind absichtlich
**vor** dem Gleichheitszeichen abgeschnitten, sonst zaehlte der Schnitt sich selbst mit und stuende
auf 7 statt 6.

### Bedingung 4 - Reihen 14 und 16 unveraendert

Zeichengleich, gemessen als Blockvergleich alte gegen neue Fassung: Reihe 14 (5.959 Zeichen) und
Reihe 16 (3.396 Zeichen) sind identisch, ebenso die Nachbarreihen 13, 15 und 17. Die drei Stellen aus
0036 - Umrechnungsblock der Reihe 14, die ersten beiden `offen`-Eintraege der Reihe 14, der erste
`offen`-Eintrag der Reihe 16 - sind unberuehrt. Dieses Paket hat nichts nachgemessen.

### Was ueber den Wortlaut des Pakets hinausgeht - offen benannt, damit der Pruefer nicht suchen muss

**Die Datei ist zum ersten Mal maschinell eingelesen worden.** In diesem Lauf war `python3` frei, in
den beiden Laeufen davor nicht. `tomllib.load` hat die Datei fehlerfrei geparst: 19 Eintraege unter
`reihe`, 9 unter `widerspruch`, Summe `sollreihen` ueber alle Reihen 31 - dieselbe Zahl, die
`zaehlregel_sollreihen` von Hand verlangt.

Warum das hier steht und nicht in einem eigenen Paket: `toml_geprueft` **musste** ich anfassen, weil
es die letzte Belegstelle mit Zeilennummer in `[pruefweg]` trug (die Rollendatei `Z. 7-14`). Und
sobald ich sie anfasse, kann der Satz „Ein TOML-Leser laeuft hier nicht" nicht stehen bleiben, waehrend
in derselben Sitzung einer gelaufen ist. Mitgezogen sind deshalb `toml_geprueft_grenze` (die
Grammatikluecke ist geschlossen) und der Schlusssatz von `schnitt_6` (TOML 1.0 verbietet den doppelten
Schluessel, und der Parser haette abgebrochen). Die Geschichte bleibt in beiden Feldern stehen, samt
dem Hinweis, dass die Werkzeuglage je Lauf wechselt und ein Pruefer ohne Bash auf die sieben Schnitte
zurueckfaellt.

Das ist eine Erweiterung gegenueber den vier Bedingungen. Sie misst keine Quelle nach, beruehrt keine
Reihe und faellt keine Entscheidung - sie stellt eine Aussage der Datei ueber sich selbst richtig.
Haelt der Pruefer sie fuer ausserhalb des Pakets, ist der Rueckbau eine Zeile je Feld.

### Was ausdruecklich offen bleibt

- Der Widerspruch zu T5 Klasse 2 ist **nicht** aufgeloest. Er gehoert dem Architekten und steht jetzt
  an der Stelle, an der der Kopf dieser Datei ihn verlangt.
- Reihe 3 bleibt ungemessen; die PWT-Dokumentation liegt nur als PDF vor (0025, Abschnitt 3).
- `schnitt_2_offen` bleibt offen: Die drei Wortlaute mit ersetzten Umbruechen sind weiter nur benannt.
