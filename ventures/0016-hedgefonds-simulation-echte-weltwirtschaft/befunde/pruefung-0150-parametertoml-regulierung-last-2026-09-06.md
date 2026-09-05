---
typ: pruefung
paket: 0150-parametertoml-regulierung-last
pruefer: daten-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Alle sechs Teilbedingungen der Abnahme einzeln nachgerechnet -- eine Zuweisungszeile (907, von tomllib als Wurzelschluessel bestaetigt), Formelzitat zeichengleich mit technik.md 2165 nach Abzug der Kommentarmarke, Klasse 3 wortgleich belegt, Kommentarkopf mit allen fuenf Bestandteilen der Nachbarschluessel, PLATZHALTER wie lobbykosten, und git diff --numstat 120/0 rein additiv.
befunde: 2
---

# Pruefung 0150 -- `regulierung_last` in `parameter.toml`

Bezugsstand: `b9bc00e58e38ba82cf86751a8d6add42f7e7c845`, der Paketcommit; er enthaelt die
geaenderte Datei diesmal wirklich. `git log b9bc00e..HEAD -- .../parameter.toml` ist leer
und `git status --porcelain` auf die Datei ebenfalls -- der gepruefte Stand ist der
committete.

## Das Abnahmekriterium, Bedingung fuer Bedingung

**1. Genau eine Zuweisungszeile.** Erfuellt.

```
Zuweisungszeilen: [(907, 'regulierung_last = 0  # PLATZHALTER')]
Vorkommen des Wortes gesamt: 9   (8 davon im Kommentar)
```

Nicht an der Trefferzahl geprueft, sondern am Parser: `tomllib.load` und ein Gang ueber alle
Blattwerte finden den Schluessel genau einmal, und zwar auf der **Wurzelebene**
(`toplevel regulierung_last: True`, Wert `0`; die Suche ueber alle Untertabellen liefert
denselben und keinen zweiten Fund). Damit ist die Aussage des Kommentars, ein blanker
Schluessel hinter `[instrument.regulierung]` waere still zu
`instrument.regulierung.regulierung_last` geworden, nicht nur behauptet, sondern an der
Gegenprobe erledigt.

**2. Formel zeichengleich mit `technik.md` Zeile 2165.** Erfuellt. Zitatzeile und Zielzeile
nebeneinander, nach Abzug von `#` und Einrueckung:

```
kand : 'schaden(l, regulierung) = mal_geteilt(bip(l),    hub(l, regulierung) . regulierung_last, 10.000)'
ziel : 'schaden(l, regulierung) = mal_geteilt(bip(l),    hub(l, regulierung) . regulierung_last, 10.000)'
kand == ziel  ->  True
```

(Der Mittelpunkt steht hier als `.`, verglichen wurde das Original.) Der Vergleich haelt
einschliesslich der vier Fuellzeichen hinter `bip(l),`. Die Zeilennummer ist am
**historischen und am heutigen** Blob geprueft, weil zwischen Paketcommit und heute ein
Architektenlauf 360 Zeilen in `technik.md` eingefuegt hat (`565259c`): In
`b9bc00e:technik.md` wie in `HEAD:technik.md` liegt die Formel auf 2165, der Klassenabsatz
auf 2172, die T27-Tabelle auf 2212. Der Verweis ist also nicht nur heute richtig, er hat den
Versatz ueberlebt.

**3. Klassenangabe wortgleich `Klasse 3`.** Erfuellt -- aber **nicht** an der Fundstelle,
die das Kriterium nennt. Siehe Befund 1.

**4. Kommentarkopf wie die Nachbarschluessel.** Erfuellt. Gegen `lobbykosten` (315),
`gegenlobby_satz` (342), `druck_max` (353) und `hebelaufschlag` (761) gelegt; alle fuenf
geforderten Bestandteile sind da:

| gefordert | im Block |
|---|---|
| Klasse nach T5 | `Klasse 3 (Raten, Basispunkte)`, spaeter T5-Zeile `\| 3 \|`, Spalte Bereich |
| Formel mit T-Verweis | T48, Formelblock, Zitat im Wortlaut |
| Schranke mit Begruendung | `Schranke: >= 0.` mit Herleitung aus der Zielklasse statt aus der eigenen |
| `Kalibriert:` | Selbstspieler, mit Beleg aus `spiel.md` |
| `Scheitert daran:` beide Richtungen | "Bei 0 ..." und "Zu gross ..." |

**5. `PLATZHALTER` wie `lobbykosten`.** Erfuellt, zeichengenau bis auf den Wert:
`lobbykosten = 1  # PLATZHALTER` gegen `regulierung_last = 0  # PLATZHALTER`, zwei
Leerzeichen vor dem `#`. Der Wert `0` folgt Regel A des Dateikopfs -- Platzhalter ist die
untere Schranke. Die Datei zaehlt ihn mit ihrem eigenen vorgeschriebenen Ausdruck mit:

```
grep -c '^[a-z_0-9]* *=.*PLATZHALTER'  -> 47
grep -c '^[a-z_0-9]* *=.*FEST (T51)'   ->  4
```

**6. Ausserhalb des Blocks null geaenderte, null entfernte Zeilen.** Erfuellt.
`git diff --numstat b9bc00e~1 b9bc00e -- .../parameter.toml` gibt `120  0`, und der Diff hat
genau einen Hunk (`@@ -787,6 +787,126 @@`), ist also rein additiv. Es gibt keine Ersetzung,
die sich als Paar aus Loeschung und Einfuegung tarnen koennte.

## Was ich ausserdem nachgerechnet habe -- und was davon haelt

Das Paket verbietet Kalibrierung und Code; der ganze Inhalt des Blocks ist damit Beleg. Ich
habe **jede** Aussage gegen ihre Quelle gelegt. Alle halten:

| Aussage im Block | geprueft an | Ergebnis |
|---|---|---|
| "Klasse 3, Basispunkte des BIP je Regulierungsstufe" woertlich in technik.md | `technik.md` 2172 | woertlich, ja |
| umlautfreier Suchanker "(Klasse 3, Basispunkte des BIP je" | Volltextsuche | trifft |
| "zehn Fundstellen, technik.md sechs, spiel.md vier" | Zaehlung in vier specs-Dateien | technik.md 6 (2165, 2172, 2173, 2212, 3243, 3259), spiel.md 4 auf 3 Zeilen, daten.md 0, zielbild.md 0 -- **stimmt** |
| keine davon nennt eine obere Schranke | alle zehn Fundstellen gelesen | keine nennt eine |
| spiel.md-Zitat "neuer Schluessel ... kalibriert wie `gegenlobby_satz`" | `spiel.md` 2606 | woertlich, umlautbereinigt |
| Klassenspalte "10 x 3" | `spiel.md` 1338, dritte Spalte | woertlich |
| "Sein Wert wird kalibriert, nicht entworfen; im Weltlauf ..." unter "Offene Entwurfsfragen" | `spiel.md` 2400-2401; letzte Ueberschrift davor ist 2330 `## Offene Entwurfsfragen` | trifft |
| T5 Klasse 3 Bereich "+-2 Mio %", symmetrisch um null | `technik.md` 282 | stimmt |
| "Dieselbe Lage wie bei `hebelaufschlag`" | `parameter.toml` 731-735 | derselbe Satz, dieselbe Herleitung |
| T5 Klasse 9 "0 ... `druck_max`" | `technik.md` 288 | stimmt |
| `hub(l, i)` ist ein Betrag, T48 Nr. 18 | `technik.md` 2091 | Betragsstriche um `lies_neu - lies_alt`, Klasse 10 fuer die Regulierung |
| `bip(l)` ist eine Summe von Wertschoepfungen, T48 Nr. 9 | `technik.md` 2082 | Summe ueber die 3 Sektoren |
| T50 Uebergang 3 `lobbypunkte_aus_schaden(tsd) = mal_geteilt(tsd, gegenlobby_satz, 10.000)` | `technik.md` 426 | zeichengleich; Zeile "3, volkswirtschaftlich (2) -> Lobbydruck (9)" |
| einziges Instrument, das Gegenkraft 1 ohne Zutun des Fonds gegen ihn bewegt | `spiel.md` 1228-1229 | "Bei der ersten bewegt sich das Instrument Finanzmarktregulierung gegen den Fonds, unabhaengig von dessen Lobbybudget" |
| `mal(a, b)` mit i128 und `intern::nach_i64`, T7 Massnahme 3 | `technik.md` 773-778 | woertlich; `mal_geteilt` ebenso nach T6, 667-670 |
| kommt in keiner der acht Bedingungen aus BEFUNDE 5a vor | `parameter.toml` 1113-1120 | acht Zeilen, keine nennt ihn; seine Schranke nennt keinen zweiten Schluessel |

**Die Ueberlaufrechnung habe ich selbst gerechnet, nicht nachgelesen.** Behauptet ist, der
`i64`-Bereich werde erst bei `hub . regulierung_last` ueber rund `4,4*10^12` verlassen. Mit
`bip = 2,1*10^10` (T5 Klasse 2, Beispielzeile 281) ist das Ergebnis
`2,1*10^10 * X / 10^4 = 2,1*10^6 * X`; die `i64`-Grenze `9,223*10^18` reisst bei
`X > 4,392*10^12`. Die Zahl stimmt, und die Folgerung traegt: T6 setzt hier keine stille
Obergrenze, weil `mal` und `mal_geteilt` am Waechter abbrechen statt umzubrechen.

**Die Selbstbilanz des Blocks habe ich am Parser nachgezaehlt**, weil ein selbstmessendes
Feld nach meiner Erfahrung als letztes faellt. Behauptet: "51 Schluessel, 47 PLATZHALTER,
4 FEST; gebildet bleiben 25, woertlich zitiert steigen von 25 auf 26." Gemessen: `tomllib`
findet **51** Blattwerte, 39 auf der Wurzel und 12 in den vier Instrumententabellen -- das
sind die `4 x 3` des Kopfes --, die beiden vorgeschriebenen Ausdruecke geben **47** und
**4**. Die Aufzaehlung unter BEFUNDE Punkt 1 nennt 13 woertliche Einzelnamen plus 12
Instrumentenschluessel, also 25 woertlich und 25 gebildet; da `regulierung_last` an zehn
Stellen woertlich in `specs/` steht, ist "keine `*`-Marke" richtig und die neue Aufteilung
26 zu 25. **Alle fuenf Zahlen stimmen.**

Dass Dateikopf und BEFUNDE Punkt 1 weiterhin 50/46/4 und "25 der 50" sagen, ist kein Befund
gegen dieses Paket: Die Abnahme verbietet jede Aenderung ausserhalb des Blocks. Der Block
sagt die Ueberholung selbst an, nennt die drei richtigen Zahlen und verweist auf
`aufgaben/0153-parametertoml-bilanz-nachziehen.md`. Dieses Paket steht auf
`status: vorschlag`, also nicht auf `offen`, und seine Abnahme ist mechanisch -- dieselben
zwei Zaehlausdruecke, die Gruppensumme gegen `tomllib`, `regulierung_last` in der
Aufzaehlung. Ich lege deshalb **keinen eigenen Vorschlag** dazu ab; er waere ein Duplikat.

## Wonach ich gesucht und was ich bewusst nicht gefuehrt habe

- **Umlaute.** Der Dateikopf verlangt Umlautfreiheit auch in Zitaten. Zeichenzaehlung ueber
  den neuen Block: kein Umlaut und kein Eszett, nur der Mittelpunkt (6x), das
  Multiplikationszeichen (1x) und das Plusminus (1x) -- genau die drei Sonderzeichen, die
  die uebrige Datei auch fuehrt.
- **Tragende Zeilennummern.** Der Kopf verbietet sie (Paket 0035) und erlaubt sie
  zusaetzlich mit Abrufdatum. Der Block nennt eine einzige ("dort Zeile 2165, abgerufen
  2026-09-06"), und sie steht neben Tabellennummer, Abschnittszitat und dem Wortlaut der
  Formel. Regel eingehalten.
- **Lizenz und Namensnennung.** Nichts zu pruefen, und das ist belegt statt angenommen: Die
  Datei traegt keinen Datenanker (Kopf, Zeile 220), der Block fuehrt keine externe Zahl ein,
  `daten.md` und `zielbild.md` nennen `regulierung_last` null Mal.
- **Luecken und stille Interpolation.** Keine Reihe, kein Jahr, keine Interpolation -- der
  Block fuehrt einen Kalibrierschluessel ein, keine Messung.
- **Wiederholbarkeit.** `tomllib` liest die Datei zweimal zum selben Ergebnis; der Wert ist
  eine TOML-Ganzzahl (`0`, nicht `0.0`), nach dem eigenen Kopfabschnitt "LESEART DER WERTE"
  also ein `i64` und kein Gleitkommawert.
- **Nicht gefuehrt: die Wahl der Gruppe D.** Ob der Schluessel eine eigene Gruppe verdient
  oder in Gruppe A gehoert, entscheidet `specs/` nicht. Wo `specs/` schweigt, gilt die
  Entscheidung des Bauagenten; sie ist hier zudem begruendet und ihre Folge fuer die
  Kopfzahlen benannt.
- **Nicht gefuehrt: die Laenge.** 118 Kommentarzeilen fuer einen Schluessel sind viel, aber
  `hebelaufschlag` liegt bei 48 und traegt dieselbe Bauart. Das ist Geschmack.

## Befunde

### Befund 1 -- Das Abnahmekriterium nennt die falsche Fundstelle. An den Projektmanager.

Die Abnahme verlangt: *"die Klassenangabe im Kommentar ist wortgleich mit der in
`technik.md` Zeile 2212 (`Klasse 3`)"*, und die Herkunftstabelle im Rumpf sagt dasselbe
(*"Klasse 3 | `technik.md` Zeile 2212, Tabelle der Klassen"*).

So erzeugt man den Fehler -- Zeile 2212 aufschlagen:

```
| `regulierung_last`, `druck_max`, `stufenweite`, `aufschlag` | Parameterschluessel, T27 |
```

Die Zeichenfolge `Klasse 3` steht dort **nicht**. Die Zeile ist auch keine "Tabelle der
Klassen", sondern die Herkunftstabelle aus T48, die den Schluessel als Parameterschluessel
nach T27 einordnet. Die Klasse steht sieben Zeilen unter der Formel, auf `technik.md` 2172:
*"`regulierung_last` ist der Parameterschluessel aus T27 (Klasse 3, Basispunkte des BIP je
Regulierungsstufe)"*.

Woertlich genommen ist das Kriterium damit unerfuellbar -- an 2212 kann nichts wortgleich
sein. Ich senke es nicht und lese es auch nicht um; ich melde, dass seine Voraussetzung
falsch ist. **Der Sache nach ist es erfuellt:** `Klasse 3` steht wortgleich im Kommentar und
ist an 2172 belegbar, und der Bauagent hat genau diese Stelle benutzt und mit umlautfreiem
Suchanker zitiert, ohne sich auf die falsche Nummer zu stuetzen. Ein Ruecklauf gegen
denselben Auftrag ergaebe keine bessere Datei, sondern dieselbe.

Fuer kuenftige Pakete: Eine Fundstellenangabe in einer Abnahme gehoert vor dem Anlegen
einmal aufgeschlagen. Diese hier hat nichts gekostet, weil der Bauagent sie stillschweigend
umgangen hat -- beim naechsten Mal kann sie einen Ruecklauf kosten, der gegen eine falsche
Zeile gefuehrt wird.

### Befund 2 -- "vierte Zeile des Formelblocks" ist mehrdeutig. Nicht ruecklaufwuerdig.

Der Block schreibt: *"technik.md T48, vierte Zeile des Formelblocks unter 'aus Gegenkraft 5
und dem Zollkeil, in Rechenreihenfolge'"*.

So erzeugt man den Fehler: den Block aufschlagen, den dieser Satz benennt. Er beginnt mit
der Zaunzeile 2153 und endet auf 2166; die erste Formel darin ist `hub(l, i)` auf 2154.
Zaehlt man die Formeln des Blocks, ist `schaden(l, regulierung)` die **achte**, nicht die
vierte. Vier ist sie nur innerhalb der vier `schaden`-Zeilen 2162-2165 -- und die sind nicht
der Block, den der Satz benennt. Der einleitende Satz auf 2151 spricht ausserdem von "den
fuenf", was zu keiner der beiden Zaehlungen passt.

Warum das trotzdem kein `zurueck` ist: Die Angabe ist nicht tragend. Tragend sind nach der
Regel des Dateikopfs die Abschnittsangabe (T48), das woertliche Zitat der Zwischenzeile und
die zeichengleich uebernommene Formel -- und die findet sich im ganzen Dokument genau
einmal. Wer sucht, findet die richtige Zeile; die Ordinalzahl fuehrt niemanden in die Irre,
sie beschreibt nur ungenau.

**Kein eigener Vorschlag von mir.** Der vorliegende Vorschlag
`0153-parametertoml-bilanz-nachziehen` fasst denselben Block an -- seine Abnahme sagt zu,
den Vermerk im Kopf der Gruppe D durch den erreichten Stand zu ersetzen. Ein zweites Paket
fuer ein Wort zwanzig Zeilen daneben waere Verschnitt. Vorschlag an den Projektmanager: die
Ordinalzahl beim Einplanen von 0153 in dessen Abnahme aufnehmen, etwa "die Formelzeile ist
ohne Ordinalzahl oder mit der richtigen bezeichnet".

## Urteil

`geprueft`. Alle sechs Teilbedingungen der Abnahme sind erfuellt; die eine, deren Fundstelle
das Kriterium falsch angibt, ist der Sache nach an der richtigen Stelle belegt. Von den zwei
Befunden richtet sich einer an den Projektmanager -- fehlerhafte Abnahme -- und einer an ein
bereits vorgeschlagenes Folgepaket. Keiner liegt beim Bauagenten.
