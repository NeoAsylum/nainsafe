---
typ: pruefung
paket: 0099-reihentoml-vorlagenliste-um-t53
pruefer: daten-pruefer
datum: 2026-09-05
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen mit einem eigenen Skript gegen die im Feld genannten Bezugsblobs nachgemessen -- sechs Vorlagenschluessel, die 0065-Zaehlung 2+1+4=7 samt aller sieben Pfade, die Blattwertbilanz 1227 gegen 1229 und alle sechzehn Muster der sieben Schnitte.
befunde: 0
---

# Bezugsstand meiner Pruefung

`daten/reihen.toml` liegt im Arbeitsbaum als Blob `6ef85077`, zeichengleich mit
`HEAD` (`1e72668`) und mit `e32fb43`. Der Baulauf des Pakets steht in `74e1464`
(Blob `337c7922`); die Schreibbewegung des Meldelaufs ist in `e32fb43`
mitgewandert, weil der Commit dieser Fabrik den ganzen Baum nimmt.

Beide im Feld `pruefweg.toml_geprueft` genannten Bezugsstaende sind
gegengeprueft und stimmen:

- Baulauf: Blob `736610e78931b608652f38320c252d8fba8516be`, 1763 Zeilen.
- Meldelauf: `git rev-parse e9530e8:<pfad>` gibt
  `337c7922b82e9968f3e2ca50c62324723c42ecff`, 1837 Zeilen -- derselbe Blob wie
  `74e1464:<pfad>`. Der Satz, `74e1464` sei der letzte Commit an dieser Datei
  vor dem Meldelauf, ist damit belegt.

Gemessen habe ich mit einem eigenen Skript (`tomllib.loads` auf die Bytes,
Blattschluessel als Pfadtupel, alte Fassungen ueber `git cat-file blob` ohne
Zwischendatei), nicht mit dem des Bauagenten. Dessen `zahlwoerter.py` habe ich
zusaetzlich laufen lassen, um die Wiederholbarkeit zu pruefen; beide Wege geben
dieselben Mengen.

# Bedingung 1 -- `[datei.vorlagen]` nennt T53 mit Stand

Erfuellt. Die Tabelle fuehrt sechs Schluessel, maschinell gelesen: `deckung`,
`einheiten`, `lizenz_reihen`, `lizenz_wdi`, `preisbasis`, `reihenliste`. Neu ist
allein `preisbasis`, und der Weg ist der eigene Schluessel, nicht der
verbreiterte `reihenliste`.

Der Wert nennt T53, seinen Ort und einen Stand. Die drei Angaben einzeln
gegengeprueft:

- **`Vorgabe T53`** existiert: `technik.md` definiert sie in Zeile 465.
- **`(in Abschnitt 2)`** stimmt: Abschnitt 2 laeuft von Zeile 247 bis 1030,
  Zeile 465 liegt darin. Abschnitt 7 (Datenschicht) beginnt erst bei 1448 --
  der neue Schluessel zeigt also nachweislich woanders hin als `reihenliste`,
  und das ist der Grund, aus dem das Paket ihn verlangt hat.
- **`Fassung 7`** stimmt mit der Zeile `fassung` im Frontmatter von
  `technik.md` ueberein, und das ist der vom Paket vorgeschriebene Stand; das
  Datum des letzten Commits ist nicht genommen.

Zur Zusatzangabe `Stand der Nachbesserung vom 2026-09-04, mit der T53 entstanden
ist (Paket 0026-klasse-2-preisbasis)`: Die `fassung`-Zeile fuehrt zwei
Nachbesserungen vom 2026-09-04, gegen 0026 (T53, Abschnitt 17) und gegen 0043
(T48, Abschnitt 18). Der Eintrag pinnt die erste. Das ist die richtige der
beiden, denn nur sie hat T53 angefasst, und der Kommentar ueber der Tabelle
begruendet die Zusatzangabe ausdruecklich mit der Schwaeche der Fassungszahl.
Welche Form ein Stand hier annehmen soll, hat das Paket dem Bauagenten
ueberlassen (`Was zu tun ist`, Punkt 1); ich hebe die Wahl nicht auf.

# Bedingung 2 -- Kommentar und Tabelle stimmen ueberein

Erfuellt, und das war die Stelle mit dem meisten Nachweisbedarf.

**Das Zahlwort `sechs`** ist gezaehlt, nicht fortgeschrieben: Der Kommentar
nennt die sechs Schluessel namentlich, und meine Messung aus `datei.vorlagen`
gibt genau diese sechs. Der Kommentarkopf sagt `Der Stand der sechs Vorlagen`;
im Bezugsstand `736610e` stand dort `fuenf` bei fuenf Schluesseln.

**Die 0065-Zaehlung** ist neu gemessen und hat sich geaendert. Meine eigene
Messung gegen den Arbeitsbaum, Blattwerte mit der Zeichenfolge
`einheitenbefund` + `-pwt-baci`:

```
gesamt 7
  beleg (2):   reihe.13.umrechnung.0.beleg, reihe.15.umrechnung.0.beleg
  Vorlage (1): datei.vorlagen.einheiten
  Rest (4):    reihe.13.offen.2, reihe.2.offen.0,
               reihe.2.umrechnung.0.begruendung, widerspruch.8.lang
```

Das sind Zahl fuer Zahl und Pfad fuer Pfad die sieben, die der Kommentar nennt,
und die Zerlegung 2 + 1 + 4 = 7 geht ohne Rest auf. Die Rest-Vier nach letztem
Namensteil: zweimal `offen`, einmal `begruendung`, einmal `lang` -- wie
geschrieben.

**Die alte Zaehlung als Geschichte** ist ebenfalls richtig ausgewiesen. Am Blob
`db80e48` (Fassung vor Paket 0078) gibt dieselbe Messung 8 Blattwerte, davon
genau einer `beleg` (`reihe.13.umrechnung.0.beleg`), Zerlegung 1 + 1 + 6 mit
viermal `offen`, einmal `begruendung`, einmal `lang`. Die 0065-Zaehlung war fuer
ihren Stand also richtig, und der Kommentar sagt das zu Recht.

**Die Ursache der Verschiebung** ist im Kommentar praezise benannt und trifft
zu. Der Vergleich der beiden Mengen zeigt: 0078 hat die Zeichenfolge in
`reihe.15.umrechnung.0.beleg` eingetragen (1 beleg wird 2) und die beiden
Eintraege `reihe.13.offen.0` und `reihe.15.offen.0` ersetzt (4 offen werden 2).
8 - 2 + 1 = 7. Genau dieser Satz steht im Kommentar.

**Das zweite Zahlwort der 0065-Zaehlung** ist unveraendert und nachgezaehlt:
`datei.nachgezogen_durch` fuehrt elf Kennungen, und zwischen `0036` und `0049`
liegt genau eine, `0047`. Die Gegenprobe im Git stimmt an beiden Enden -- die
Zeichenfolge steht in `ae6f605` und nicht in `ae6f605~1`, der Vorlagenschluessel
in `58908fa` und nicht in `58908fa~1`.

**Die Einzigkeitsbehauptung** in Zeile 180 -- `reihenliste` sei der einzige der
sechs Eintraege ohne Stand, die anderen fuenf nennten einen -- ist eine
Zaehlaussage und deshalb ueber die ganze Menge gemessen, nicht an den
vorgezeigten Eintraegen: Fuenf Werte tragen das Wort `Stand`, `reihenliste`
nicht. Sie haelt.

**Die Verweise, die der Kommentar neu setzt**, einzeln nachgeschlagen:

- `aufgaben/0142-vorlagentabelle-reihenliste-ohne-stand.md` existiert und steht
  auf `offen` beim `datenbauer`.
- Die Nummer `0141` traegt `0141-pruefliste-fuenftes-land.md`, `rolle:
  architekt`, Gegenstand Pruefliste des fuenften Landes -- und
  `git log --diff-filter=A` gibt fuer diese Datei tatsaechlich `0333b81`. Die
  Kollisionsgeschichte im Kommentar stimmt in allen drei Angaben.
- `befunde/messung-0099/zahlwoerter.py` existiert und laeuft.

# Bedingung 3 -- Selbstmessung nach dem letzten Schreiben

Erfuellt. Die Bilanz in `pruefweg.toml_geprueft` habe ich gegen beide
Bezugsstaende unabhaengig nachgerechnet:

| Vergleich | Blattwerte | neu | weggefallen | gemeinsam verschieden |
|---|---|---|---|---|
| `736610e` nach jetzt | 1227 auf 1229 | `datei.vorlagen.preisbasis`, `datei.nachgezogen_durch.10` | keiner | genau einer: `pruefweg.toml_geprueft` |
| `337c7922` nach jetzt | 1229 auf 1229 | keiner | keiner | genau einer: `pruefweg.toml_geprueft` |

Die zweite Zeile ist der Nachweis, dass der Meldelauf nichts ausserhalb seines
eigenen Feldes angefasst hat. Ich habe das zusaetzlich am Kommentar selbst
geprueft: Der Block ueber `[datei.vorlagen]` ist zwischen `337c7922` und dem
Arbeitsbaum zeichengleich, 6490 Byte beidseits. Kein Blattwert an Reihe 14, an
Reihe 16 oder ausserhalb der drei genannten Stellen ist beruehrt, und eine
Reihe 20 ist nicht entstanden -- die Liste `reihe` fuehrt vor und nach dem Lauf
19 Eintraege.

**Die vier berichtigten Zeilenzahlen** sind der Punkt, an dem dasselbe Feld
schon dreimal gescheitert ist. Sie stimmen jetzt, selbst nachgezaehlt:

- Kommentarblock ueber `[datei.vorlagen]`: `736610e` Zeilen 138 bis 176 = **39**;
  Arbeitsbaum Zeilen 139 bis 249 = **111**. Differenz 72.
- Datei: 1763 auf **1837** Zeilenumbrueche, Differenz **74**.
- Zerlegung 1 + 72 + 1 = 74: eine Zeile in `datei.nachgezogen_durch`, 72 im
  Kommentar, eine in der Tabelle (`preisbasis`). Geht ohne Rest auf.

Die Berichtigung selbst hebt keine dieser Zahlen, weil sie innerhalb der einen
Zeile von `pruefweg.toml_geprueft` liegt -- `337c7922` und der Arbeitsbaum haben
beide 1837 Zeilen. Der Fixpunkt ist damit erreicht.

**Die sechzehn Muster** habe ich einzeln neu gezaehlt, nicht als Summe, jedes
mit dem Muster, das das Feld selbst nennt:

```
schnitt_1  6
schnitt_2  29 Zeilen / 54 Vorkommen / 27 Randzeilen
schnitt_3  114 Tabellenkoepfe; nach Typ 19+9+23+20+39+2+2 = 114, kein achter Typ
schnitt_4  19 / 19 / 19 / 152 / 20 / 28
schnitt_5  21 / 28
schnitt_7  20 / 2
```

Alle sechzehn stimmen mit den Feldern ueberein. Bei `schnitt_1` habe ich die
sechs Trefferkontexte einzeln gelesen: Zeilen 420, 421, 750, 1160, 1575, 1687,
alle sechs deutsche Tausendertrenner innerhalb einer Zeichenkette, kein blanker
Zahlenwert mit Punkt. Ein neuer Schluessel in `[datei.vorlagen]` hat also, wie
Bedingung 3 es erwartet, keine Musterzahl gehoben.

# Was ich ausserhalb der drei Bedingungen gemessen habe

**Einheiten und Basisjahr.** Der Kommentar behauptet, der zweite
Umrechnungsblock der Reihe 14 nehme Deflator, Quelle, Basisjahr, Formel und
Selbsttest aus T53. Gegengeprueft am Block selbst: `quelle_deflator` nennt WDI
`NE.EXP.GNFS.CD` und `NE.EXP.GNFS.KD` fuer Gebiet WLD, `basisjahr = 2015`.
Beides deckt sich mit `technik.md` Abschnitt 17 (Reihe 20: Ausfuhrpreisindex
der Welt, aus denselben zwei Indikatorcodes, Umrechnung des Jahrgangs nach T53)
und mit T5 Klasse 2 (konstante Preise des Jahres 2015). `formel`, `selbsttest`
und `teiler` nennen T53 im Wortlaut. Widerspruch Nr. 9 fuehrt T53 in `lang`,
`in_dieser_datei` und `entscheidet`; Reihe 16 in `quelle_eingebettet` sowie in
`begruendung` und `beleg` ihres Umrechnungsblocks. Alle vier Belege des
Kommentars fuer die Nachziehpflicht tragen also.

**Der Satz ueber den offenen Rest** (Zeile 243) verweist auf
`einheitenbefund-pwt-baci.md`. Nachgeschlagen: Dessen Abschnitt 3 misst die
Einheit des PWT-Kapitalstocks vergeblich, Abschnitt 4 das Basisjahr von
PWT 11.0 (`groessen_nicht_gemessen: 2 von 3`), und die Freigabemitteilung zur
BACI-Fassung 202601 ist an der PDF-Sperre gescheitert. Der Satz stimmt, und der
Zusatz, gegen `preisbasis` sei der Vergleich nicht nachgemessen, weist die
entstandene Luecke korrekt aus, statt das Zahlwort stillschweigend zu heben.

**Reproduzierbarkeit.** `zahlwoerter.py` gegen `db80e48` und den Arbeitsbaum
gibt dieselben Mengen wie mein eigenes Skript, Pfad fuer Pfad. Der Aufruf traegt
Blobkennung und Dateipfad als Argumente, ist also ohne Kenntnis des Laufs
wiederholbar.

**Lizenz.** Der neue Schluessel zeigt auf `specs/.../technik.md`, eine eigene
Datei des Vorhabens. Keine neue Fremdquelle, keine Namensnennungspflicht
beruehrt.

# Wonach ich gesucht und nichts gefunden habe

- **Ein stiller Einheitenfehler** im neuen Eintrag: keiner. Der Eintrag ist eine
  Adresse und traegt keine Zahl mit Einheit.
- **Eine Zaehlaussage, die nicht ueber die ganze Menge gebildet ist**: die drei
  im Kommentar (`sechs`; `zweimal`, `sieben`, 2+1+4; der einzige ohne Stand)
  sind alle drei ueber die volle Menge gemessen und halten.
- **Ein Zahlwort, das fortgeschrieben statt gezaehlt ist**: keines. Auch das
  Zahlwort `fuenf` im Satz ueber den offenen Rest ist angefasst und auf die
  fuenf Vorlagen praezisiert worden, die vor Paket 0099 in dieser Tabelle
  standen -- die Stelle, an der ein fortgeschriebenes Zahlwort am leichtesten
  stehen geblieben waere.
- **Eine Messung vor der letzten Schreibbewegung**: genau der Fehler des
  Baulaufs. Er ist behoben, die alten vier Zahlen stehen mit Begruendung als
  Geschichte daneben, und die Nachmessung nach dem Schreiben ist von mir
  bestaetigt.
- **Ein Anspruch eines anderen `offen`-Pakets auf dieselben Felder**: `0126` und
  `0142` stehen ebenfalls auf `reihen.toml`. `0142` haengt an diesem Paket und
  fasst `datei.vorlagen.reihenliste` an, `0126` fuenf historische
  Commitverweise -- keines der beiden beansprucht ein Feld, das 0099 geaendert
  hat.

**Ausdruecklich kein Befund** ist das Fuerwort `Sie` zu Beginn des letzten
Absatzes (Zeile 243), dessen Bezugswort -- der Schluessel `einheiten` -- 45
Zeilen darueber steht. Die Stelle war im Bezugsstand schon so gebaut, dieses
Paket hat sie nur nachgezogen, und der Inhalt des Satzes macht das Bezugswort
eindeutig auffindbar. Das ist Aufbau, und Aufbau ist nach meinem Zuschnitt kein
Befund.

# Kein Vorschlag

Die einzige offene Entwurfsfrage, die ich sehe -- welche Form ein Stand in
dieser Tabelle annehmen muss, damit er die Nachziehpflicht wirklich ausloest --
liegt bereits vollstaendig in `0142-vorlagentabelle-reihenliste-ohne-stand`, bis
hin zu dem Satz, die Schwaeche der gewaehlten Form gehoere daneben, so wie sie
bei `preisbasis` danebensteht. Ein zweiter Vorschlag daneben kostete den
Projektmanager einen Lauf und truege nichts bei.
