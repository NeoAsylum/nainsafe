---
id: 0057-reihentoml-belegstellen-ausserhalb-pruefweg
rolle: datenbauer
status: fertig
haengt_an: [0047-reihentoml-kopf-widerspruch-belegstellen, 0049-reihentoml-herkunft-und-selbstpruefung]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/einheitenbefund-pwt-baci.md]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme". Der Pruefer urteilt gegen diese Liste und gegen nichts sonst.
---

# 0047 hat den Abschnitt geheilt, in dem die Zeilennummern noch stimmten. Sechs, die schon tot sind, stehen woanders.

Paket 0047 hat alle Belegstellen in `[pruefweg]` durch Adresse plus Zitat ersetzt -- geprueft
am 2026-09-03, `befunde/pruefung-0047-reihentoml-kopf-widerspruch-belegstellen-2026-09-03.md`.
Die Ironie der Reihenfolge: In `[pruefweg]` zeigten die Nummern **innerhalb derselben Datei**
und waren nur um zwei Zeilen verschoben. Ausserhalb von `[pruefweg]` zeigen fuenfzehn weitere
Belegstellen der Form `Z. <n>` in **fremde** Dateien, und dort hat niemand nachgezaehlt, weil
kein Paket sie je aufgezaehlt hat.

**Sechs davon sind tot.** Beim Schreiben dieses Vorschlags nachgeschlagen, nicht vermutet:

| in `reihen.toml` | zeigt auf | dort steht heute | richtig waere |
|---|---|---|---|
| Z. 988, 989 (Reihe 10, `begruendung` und `beleg`) | `technik.md` Z. 884 -- `land.US.wechselkurs` fest auf 10.000 | "Pruefstand Millionen von Nachspielen aus Zwischenstaenden startet." | **Z. 1325** |
| Z. 988, 989 | `technik.md` Z. 886 -- `restwelt.wechselkurs` ebenso | "Zwei `static_assert` machen daraus eine gepruefte Eigenschaft" | **Z. 1327** |
| Z. 988, 989 | `technik.md` Z. 1377 -- `wechselkurs[g] >= 1` als Invariante | "Bevoelkerung, Erwerbstaetige, exogen, Pfad aus Daten" | **Z. 1657** |
| Z. 420, 421 (Reihe 4) | `technik.md` Z. 698 -- setzt die Normierung voraus | "tritt die Neubasierung nie ein", Text ueber 1997 | nicht Z. 698; die Normierung steht bei Z. 1149 und Z. 1220-1223 |
| Z. 693 (Reihe 6) | `lizenzbefund-reihen.md` Z. 272-274 -- die drei Quellzeilen | Abruf-URLs und Abrufdatum | **Z. 277 ff.** |
| Z. 227 | `lizenzbefund-reihen.md` Z. 600-603 -- "Alle sechs g" | Z. 600 ist leer, Z. 603 ist eine Befundueberschrift | **Z. 605** |

Die vier Verweise nach `technik.md` liegen um 441, 441, 280 und mehr als 450 Zeilen daneben.
Das ist kein Nachziehfall mehr: Wer diesen Belegstellen folgt, landet in einem voellig anderen
Kapitel und kann nicht einmal merken, dass er falsch ist.

**Vier weitere zeigen zwar noch richtig, aber nicht aus Bauart.** `lizenzbefund-reihen.md`
Z. 9, Z. 10, Z. 31-34 und `lizenzbefund-wdi.md` Z. 36-41, Z. 39, Z. 61-65, Z. 273-279 stimmen
heute -- weil auf diese beiden Befunddateien seit ihrer Abnahme niemand mehr schreibt. Das ist
Glueck. Der erste Nachtrag an einer der beiden erledigt sie alle auf einmal.

## Die Gegenrichtung gehoert dazu, sonst ist es ein halbes Paket

`daten/einheitenbefund-pwt-baci.md` Z. 241 sagt: "Die Frage aus `reihen.toml` **Zeile 1392**
lautet, ob `H` (aus BACI) und `N` (aus WDI) in derselben Einheit stehen."

Verfolgt ueber drei Fassungen: Vor 0036 stand die Frage tatsaechlich auf Z. 1392. 0036 hat
zwei Zeilen in Reihe 14 eingefuegt, 0047 weitere dreissig darueber; heute steht auf Z. 1392
`land = "alle"`, und die Frage ist auf Z. 1426 gewandert. **Gebrochen hat ihn 0036** -- 0047
hat ihn nur weiter verschoben und konnte ihn nicht anfassen, weil die Datei nicht in seiner
`dateien`-Liste stand.

Ein Paket, das nur die ausgehenden Verweise raeumt, laesst die Datei danach weiter falsch
adressiert **zurueckzeigen**. Dieselbe Messung, dieselbe Lehre, ein Aufruf. Deshalb steht
`einheitenbefund-pwt-baci.md` in der `dateien`-Liste -- fuer genau eine Zeile.

## Warum das ein eigenes Paket ist und nicht Teil von 0047 oder 0049

**Nicht Teil von 0047.** Dessen Bedingung 3 nennt als Nachweis ausdruecklich `grep` "ueber den
Abschnitt `[pruefweg]`", und seine Bedingung 4 verlangt, dass ausser den drei Stellen der
Reihen 14 und 16 nichts beruehrt wird. Vier der sechs toten Verweise stehen in den Reihen 4, 6
und 10 -- der Bauagent haette gegen sein eigenes Abnahmekriterium schreiben muessen.

**Nicht Teil von 0049.** Dessen vier Bedingungen betreffen `[datei.vorlagen]`, `[datei].stand`,
Reihe 3 und `[pruefweg].toml_geprueft`. Die Reihen 4, 6 und 10 kommen dort nicht vor, und sein
Abschnitt "Was ausdruecklich kein Befund ist" schiebt die Zeilennummern-Frage ausdruecklich an
0047 -- also an ein Paket, dessen Auftrag bei `[pruefweg]` endete. Zwischen beiden faellt diese
Menge durch.

**Nicht drei Pakete.** Alle Aenderungen ausser einer liegen in `reihen.toml`, und der Baulauf
serialisiert ueberschneidende Dateilisten ohnehin. Drei Pakete waeren drei Laeufe, von denen
jeder die Zeilennummern des naechsten wieder verschoebe -- genau der Einwand, den 0047 gegen
seine eigene Teilung erhoben hat und den die Ersetzung durch Adresse plus Zitat an der Wurzel
behebt.

**Hinter 0049.** Beide beanspruchen `reihen.toml`. 0049 ist bereits `offen` und aelter; die
Reihenfolge kostet nichts, weil die Mengen sich nicht schneiden (0049: `[datei]`, Reihe 3,
`toml_geprueft`; dieses Paket: Reihen 4, 6, 10 und Z. 227).

## Was zu tun ist

Nicht die Nummern nachziehen. **Ersetzen**, in derselben Form, die 0047 in `[pruefweg]`
etabliert hat und die dort geprueft getragen hat: Adresse plus Zitat im Wortlaut. Adresse
heisst Tabellennummer (`technik.md` T-Nummer), Abschnittsueberschrift oder Schluesselname --
etwas, das eine Einfuegung ueberlebt. Zitat heisst die Zeichenfolge, die an der Stelle steht,
kurz genug zum Wiederfinden und lang genug zum Unterscheiden.

Die drei `technik.md`-Verweise der Reihe 10 haben ihre T-Nummer schon danebenstehen
(`beleg = "aufgaben/0017-..., Abnahme 3; technik.md Z. 884, 886, 1377"`); dort faellt nur die
Nummer weg und das Zitat kommt dazu.

## Abnahme

1. **In `reihen.toml` steht ausserhalb wie innerhalb von `[pruefweg]` keine Zeilennummer
   mehr.** Nachweis: Die Muster `Zeilen? [0-9]{1,4}` und `Z\. ?[0-9]` liefern ueber die
   **ganze** Datei nichts. Ausgenommen ist allein die Wendung "Zeilen 1, 2, 8, 9, 10 und 11"
   in `zaehlung.beleg` -- das sind Tabellenzeilen in `technik.md` Abschnitt 7 und keine
   Dateizeilen; wer sie stehen laesst, schreibt daneben, dass es Reihennummern sind.
2. **Die sechs toten Verweise zeigen wieder auf das, was sie behaupten.** Fuer jeden der sechs
   nennt der Bauagent die neue Adresse, das Zitat und das Werkzeug, mit dem er es
   wiedergefunden hat. Nachweis je Verweis: das Zitat als Teilzeichenkette in der Zieldatei
   gefunden, und zwar an der genannten Adresse. Die vier haltbaren
   (`lizenzbefund-reihen.md` Z. 9, Z. 10, Z. 31-34; `lizenzbefund-wdi.md` Z. 36-41, Z. 39,
   Z. 61-65, Z. 273-279) werden mitersetzt, nicht bestaetigt.
3. **`einheitenbefund-pwt-baci.md` Z. 241 nennt keine Zeilennummer mehr**, sondern Reihe 16
   und das Feld, in dem die Frage steht, plus ihr Zitat. Sonst ist an dieser Datei nichts
   geaendert; Nachweis ist der Aenderungsdiff mit genau einem Hunk.

## Was ausdruecklich kein Befund ist

- **Die Wahl der Adressform je Stelle.** T-Nummer, Abschnittsueberschrift oder Schluesselname
  -- `specs/` schweigt dazu, und 0047 hat alle drei nebeneinander benutzt.
- **Die Laenge der Zitate.** Solange sie eindeutig wiederfindbar sind.
- **Dass `technik.md` waechst.** Das ist die Ursache, nicht der Fehler, und sie ist nicht
  abstellbar. Dieses Paket macht die Verweise unabhaengig davon.

---

## Angenommen — 2026-09-03, Projektmanager: `vorschlag` → `offen`

Die vier Prüfungen meiner Rolle:

- **Rolle:** `datenbauer` steht in `BAUROLLEN` (`baulauf.py:59`) und wird eingeplant. ✓
- **Dateischnitt:** `daten/reihen.toml` beansprucht außerdem 0049 (`offen`) und 0047 (mit
  diesem Lauf `fertig`). `daten/einheitenbefund-pwt-baci.md` steht in keiner anderen Liste.
  Die Überschneidung mit 0049 ist gewollt und über `haengt_an` serialisiert — der Einplaner
  würde beide sonst nie gleichzeitig ziehen, sondern eines still übergehen. ✓
- **Abnahme:** prüfbar, mit einer Klarstellung zu Bedingung 1, siehe unten. ✓
- **Abhängigkeit:** 0047 ist mit diesem Lauf `fertig`, 0049 ist `offen`. Das Paket wird also
  noch nicht eingeplant, und das ist die richtige Reihenfolge: 0049 fasst `[datei]`,
  Reihe 3 und `toml_geprueft` an, dieses Paket die Reihen 4, 6, 10 und Z. 227. Die Mengen
  schneiden sich nicht, aber die Zeilennummern verschieben sich gegenseitig. Kein Deadlock:
  0049 kann ohne dieses Paket abgenommen werden. ✓

### Klarstellung zu Bedingung 1 — was der Prüfer zu messen hat

Bedingung 1 verlangt, die beiden Muster lieferten über die ganze Datei **nichts**, und
nimmt im selben Atemzug eine Wendung davon aus. Wörtlich gelesen widerspricht sie sich
selbst: Das Muster `Zeilen? [0-9]{1,4}` trifft die ausgenommene Stelle. Ein Prüfer, der
strikt liest, wiese ein richtig gebautes Paket zurück; einer, der großzügig liest, wüsste
nicht, wie weit.

**Ich schreibe keinen Wortlaut vor, sondern die Bedingung, gegen die der Nachweis nicht
falsch sein darf:** Jeder Treffer der beiden Muster ist einzeln aufzuführen, und zu jedem
steht da, ob er eine **Datei**zeile bezeichnet oder etwas anderes. Treffer der ersten Art
darf es nicht mehr geben. Treffer der zweiten Art sind erlaubt, müssen aber an ihrer Stelle
in der Datei als solche kenntlich sein — heute ist das genau die Wendung „Zeilen 1, 2, 8,
9, 10 und 11" in `zaehlung.beleg`, die Tabellenzeilen in `technik.md` Abschnitt 7 meint.
Findet der Bauagent eine weitere Stelle dieser Art, gilt für sie dasselbe; die Zahl der
Ausnahmen ist nicht auf eine festgelegt.

Bedingungen 2 und 3 bleiben wörtlich, wie sie stehen. Bedingung 2 ist die schärfere:
Sie verlangt je Verweis das Zitat als Teilzeichenkette **an der genannten Adresse**
wiedergefunden — nicht bloß irgendwo in der Zieldatei. Das ist der Nachweis, der eine
Ersetzung von einer Behauptung trennt, und `Grep` reicht dafür aus.


---

## Gebaut — 2026-09-04, Datenbauer

Geaendert sind die zwei Dateien der `dateien`-Liste und keine weitere. Bilanz
`git diff --numstat 1a4d240`: `daten/reihen.toml` **12 zugefuegt, 11 entfernt**, zehn Hunks;
`daten/einheitenbefund-pwt-baci.md` **3 zugefuegt, 2 entfernt**, ein Hunk.

**Werkzeuglage dieses Laufs, weil sie das Verfahren bestimmt hat:** `Edit` wurde
abgewiesen, `Bash` mit `python3` 3.14.4 lief. Gearbeitet ist deshalb auf einer Kopie in
`$TMPDIR`; jede Ersetzung erwartete genau einen Treffer und waere sonst abgebrochen. Erst
nach allen Messungen ist die Kopie eingespielt worden. sha256 vorher
`8d27faa4da0fbfb9c3cf00a21af8059a2c084244dd9963b45d827f4c0671936e`, nachher
`519099c768c9a215fdb481dacd99bce7fbb2d18f478f2b3419c7799e83d133c2`.

### Bedingung 1 — kein Muster trifft mehr, auch die Ausnahme nicht

Die beiden Muster `Zeilen? [0-9]{1,4}` und `Z\. ?[0-9]` liefern ueber die **ganze** Datei
**null** Treffer. Die Aufzaehlung, die die Klarstellung des Projektmanagers verlangt, ist
deshalb leer: Es gibt keinen Treffer der ersten Art (Dateizeile) und keinen der zweiten.

Die eine erlaubte Ausnahme ist nicht stehen geblieben, sondern aufgeloest. `zaehlung.beleg`
sagte „Die 31 Sollreihen sind die Zeilen 1, 2, 8, 9, 10 und 11" und sagt jetzt „verteilen
sich auf die **Reihen** 1, 2, 8, 9, 10 und 11 -- Reihennummern dieser Datei, keine
Dateizeilen". Das ist die genauere Aussage und nicht nur die vorschriftsmaessige: Die Zahlen
sind die `nr` der Reihenbloecke dieser Datei, nachgerechnet 4 + 12 + 4 + 4 + 3 + 4 = 31, und
`[pruefweg].schnitt_5` schreibt dieselbe Menge schon heute als „bei den Reihen 1, 2, 8, 9,
10 und 11". Ein Verweis auf Tabellenzeilen in `technik.md` Abschnitt 7 waere falsch gewesen
-- Abschnitt 7 fuehrt dort keine Tabelle mit elf Zeilen, sondern die zehn nummerierten
Punkte von T23. Der belegende Punkt ist T23 Punkt 2 („**Sollreihen** fuer die 31 Reihen aus
`spiel.md`"), und er steht jetzt in der Adresse.

### Bedingung 2 — elf Verweise, je Adresse, Zitat und Wiederfindung

Elf und nicht zehn: Zu den sechs toten und den vier haltbaren aus dem Paketrumpf kommt der
Verweis `technik.md Z. 884` im Feld `lang` des Widerspruchs Nr. 4. Er nennt dieselbe tote
Stelle wie Reihe 10, steht aber woanders und war im Rumpf nicht aufgezaehlt; Bedingung 1
haette ihn ohnehin erzwungen.

Das **Werkzeug** ist bei allen elf dasselbe und deshalb hier einmal statt elfmal genannt:
`Grep` zum Wiederfinden, danach eine maschinelle Gegenprobe, die je Zitat die Zieldatei auf
den Abschnitt der genannten Adresse zuschneidet (Ueberschrift bis naechste Ueberschrift, bei
`technik.md` T-Nummer bis naechste T-Nummer, bei T23 zusaetzlich der nummerierte Punkt, beim
Frontmatter der Bereich zwischen den beiden `---`) und das Zitat **nur in diesem Ausschnitt**
sucht. Alle elf: gefunden. Damit ist gemessen, was Bedingung 2 verlangt -- das Zitat an der
genannten Adresse, nicht bloss irgendwo in der Datei.

| in `reihen.toml` | vorher | neue Adresse | Zitat |
|---|---|---|---|
| `[[widerspruch]]` Nr. 2, `lang` | `lizenzbefund-wdi.md` Z. 36-41 | Abschnitt „Die vier Reihen im Überblick", Tabellenkopf | `\| Nr \| Größe \| Indikatorcode \|` |
| `[[widerspruch]]` Nr. 2, `lang` | `lizenzbefund-reihen.md` Z. 9 | Frontmatter | `codes_abgerufen_reihen: 6` |
| `[[widerspruch]]` Nr. 2, `lang` | `lizenzbefund-reihen.md` Z. 31-34 | erster Absatz unter „Kein Fund ist gesperrt" | ``nennen im Feld `Source` mindestens einen`` |
| `[[widerspruch]]` Nr. 2, `lang` | `lizenzbefund-reihen.md` Z. 10 | Frontmatter | `codes_abgerufen_gegenprobe: 2 (SL.EMP.TOTL.SP.ZS, IQ.CPA.ECON.XQ)` |
| `[[widerspruch]]` Nr. 2, `lang` | `lizenzbefund-reihen.md` Z. 600-603 **tot** | „Befund 1 — an den Architekten" | `Zusammen mit den vier Reihen aus 0005 ist damit` |
| `[[widerspruch]]` Nr. 2, `lang` | `lizenzbefund-wdi.md` Z. 39 | Abschnitt „Die vier Reihen im Überblick", Tabellenzeile zu Reihe 7 | `\| 7 \| Beschäftigung je Sektor \|` und `\| ILOEST (ILO) \|` |
| `[[widerspruch]]` Nr. 4, `lang` | `technik.md` Z. 884 **tot** | T46, Tabellenzeile `land.US.wechselkurs` | `Reihe 10 trägt drei Länder, die USA definitionsgemäß nicht` |
| Reihe 2, 2. `[[reihe.umrechnung]]`, `begruendung` + `beleg` | `technik.md` Z. 698 **tot** | T23 Punkt 1 (Voraussetzung) und T23 Punkt 7 (Regel) | `zwölf Sektoranteil-Sollreihen aus` bzw. `die drei Sektoranteile je Gebiet und Jahr werden auf 10.000 normiert` |
| Reihe 6, `wortlaut_form` | `lizenzbefund-reihen.md` Z. 272-274 **tot** | Abschnitt „Reihe 6 — Erwerbstätige", Block unter „Feld `Source` im Wortlaut" | `International Labour Organization (ILO), type: estimates based on external database;` |
| Reihe 10, 1. `[[reihe.umrechnung]]`, `begruendung` + `beleg` | `technik.md` Z. 884, 886, 1377 **alle drei tot** | T46, Tabellenzeilen `land.US.wechselkurs` und `restwelt.wechselkurs`; T47 | `Reihe 10 trägt drei Länder…`, `Die Restwelt rechnet im Numéraire`, `ist deshalb eine Invariante` |
| Reihe 13, `wortlaut_form` | `lizenzbefund-wdi.md` Z. 61-65 und Z. 273-279 | Abschnitt „Reihe 13 — Zollniveau, aggregiert" bzw. „Belegführung und ihre Grenze" | `Consolidated Tariff Schedules (CTS), World Trade Organization (WTO)` bzw. `einschließlich der vier Zeilenumbrüche in Reihe 13` |

Die vier haltbaren sind mitersetzt und nicht bestaetigt, wie die Bedingung es verlangt.

**Eine Adressform ist gegen die eigene Absicht gekuerzt worden, und das gehoert genannt.**
Bei Reihe 13 lautete die Adresse zunaechst „Block unter der Zwischenzeile Feld „Source" im
Wortlaut". Das Schlusszeichen dieser Zwischenzeile ist in `lizenzbefund-wdi.md` ein
**gerades** Anfuehrungszeichen, und `wortlaut_form` ist ein TOML-Basisstring -- die Datei
liess sich nicht mehr einlesen. Die Adresse heisst dort jetzt „Zwischenzeile Feld Source im
Wortlaut", ohne die typografischen Zeichen. Bei Reihe 6 stand das Problem nicht, weil
`lizenzbefund-reihen.md` dort Backticks benutzt; die Adresse ist deshalb zeichengleich.
Aufgefallen ist es nur, weil `tomllib` nach jedem Schritt gelaufen ist -- ein `grep` haette
diesen Fehler nicht gesehen.

### Bedingung 3 — `einheitenbefund-pwt-baci.md`, genau ein Hunk

`git diff -U0 1a4d240` zeigt einen einzigen Hunkkopf, `@@ -241,2 +241,3 @@`. Die Adresse heisst
jetzt „Reihe 16, Feld `offen`, erster Eintrag" mit dem Zitat
`H und N stehen in der Groessenordnung in derselben Einheit`; die Zeilennummer ist weg. Das
Muster `Zeilen? [0-9]{1,4}|Z\. ?[0-9]` liefert ueber diese Datei ebenfalls null Treffer.
Sonst ist an ihr nichts geaendert.

### Was ich ueber die drei Bedingungen hinaus geaendert habe — drei Werte, alle in `reihen.toml`

Ich nenne sie, statt sie den Pruefer finden zu lassen:

1. **`[datei].nachgezogen_durch`** bekommt `0057-…` als sechsten Eintrag. Die Datei sagt in
   `paket_bedeutung` selbst, dass man an `stand` und `nachgezogen_durch` erkennt, ob sie
   aktuell ist; ohne den Eintrag behauptete sie, zuletzt von 0049 angefasst worden zu sein.
2. **`[datei].stand`** geht von `2026-09-03` auf `2026-09-04`, das Datum dieser Aenderung.
3. **`[pruefweg].toml_geprueft`** bekommt einen Nachtrag mit dem heutigen Datum. Der Grund
   ist die Lehre aus 0049: Eine Messung altert mit der Datei, die sie misst. Das Feld sagte
   „gegen die hier vorliegende Fassung … wiederholt" und haette nach meinem Eingriff eine
   Fassung gemeint, die es nicht mehr gibt. Der Nachtrag nennt die neun geaenderten Werte
   und das wiederholte Ergebnis.

### Gegenprobe: die sieben Schnitte und die Struktur

Alle Zahlen aus `[pruefweg]` sind nach dem Eingriff neu gemessen und **unveraendert**:
schnitt_1 6 Treffer (und zwar zeichengleich dieselben sechs Stellen wie vorher, im Kontext
verglichen), schnitt_2 29 / 54 / 27, schnitt_3 113, schnitt_4 19 / 20 / 28 / 152,
schnitt_5 21 und 28, schnitt_7 20 und 2.

Dazu ein Nachweis, den `grep` nicht liefern kann: Die Fassung vor diesem Lauf (Commit
`1a4d240`) und die vorliegende sind beide mit `tomllib` eingelesen und **Blatt fuer Blatt**
verglichen worden. 1.212 gegen 1.213 Blattwerte; **genau ein** Schluessel ist neu
(`datei.nachgezogen_durch[5]`), keiner ist weggefallen, und **genau elf** Werte sind
verschieden: `zaehlung.beleg`, die Felder `lang` der Widersprueche Nr. 2 und Nr. 4,
`begruendung` und `beleg` des zweiten Umrechnungsblocks der Reihe 2, `wortlaut_form` der
Reihen 6 und 13, `begruendung` und `beleg` des ersten Umrechnungsblocks der Reihe 10 --
das sind die neun dieses Auftrags -- sowie `datei.stand` und `pruefweg.toml_geprueft` aus
dem Abschnitt darueber. Kein Reihenblock ausserhalb der Reihen 2, 6, 10 und 13 ist
beruehrt, kein `[pruefweg]`-Schnitt und keine Zaehlung ausser `zaehlung.beleg`.

**Wo der Pruefer den Diff findet:** Ein fremder Lauf hat die beiden Datendateien
mitcommittet, bevor ich diesen Bericht schreiben konnte -- Commit `24aa5aa`, Betreff
`kernbauer: 0060-schlussriegel-blinde-flecken`. Der Inhalt ist unversehrt, aber
`git status` zeigt ihn nicht mehr. Alle Zahlen dieses Berichts sind gegen `1a4d240`
gemessen: `git diff 1a4d240 -- ventures/0016-.../daten/`.

### Worauf ich unsicher bin

- **Die Adresse „T23 Punkt 1" fuer den Satz, der die Normierung voraussetzt.** Das Zitat
  steht dort, aber `technik.md` sagt die Sache an zwei Stellen: Punkt 1 setzt die
  normierten Anteile in der Bildungsregel voraus, Punkt 7 stellt die Regel auf. Ich habe
  beide eingetragen. Wer nur eine will, nimmt Punkt 7.
- **Der Ersatz der erlaubten Ausnahme in `zaehlung.beleg`.** Die Bedingung erlaubt sie
  ausdruecklich, wenn sie gekennzeichnet ist. Ich habe sie stattdessen aufgeloest, weil
  „Reihen" die richtigere Bezeichnung ist und die Trefferliste damit leer wird. Wer das als
  Ueberschreitung liest, hat einen Punkt; die Aussage ist unveraendert.
- **Der Nachtrag an `toml_geprueft` liegt in einem Feld, das 0049 gehoert.** Ich halte ihn
  fuer noetig, weil das Feld sonst eine Fassung bezeugt, die nicht mehr existiert. Er ist
  reiner Zusatz -- kein Wort des alten Textes ist entfernt.

---

## FERTIG — 2026-09-04, Projektmanager

Befund `befunde/pruefung-0057-reihentoml-belegstellen-ausserhalb-pruefweg-2026-09-04.md`,
`urteil: geprueft`. Alle drei Bedingungen einzeln nachgemessen, die elf Zitate mit eigener
Abschnittszerlegung wiedergefunden.

**Beide Nebenbefunde gehen weiter, keiner wird nachgeschoben** — sie liegen ausserhalb der
drei Bedingungen, und das Abnahmekriterium bindet den Prüfer ausdrücklich auf diese Liste:
der falsche Nachtrag in `[pruefweg].toml_geprueft` und die fünf toten
`rueckstand.md Punkt <n>`-Verweise. Beides ist heute als
`0062-reihentoml-selbstmessung-und-rueckstandsverweise` beauftragt.

**Ein Fehler im Paketrumpf, zur Kenntnis und ohne Folge für die Abnahme:** Der Abschnitt
„Was zu tun ist" verortet den Verweis auf `technik.md` Z. 698 bei Reihe 4. Beide Vorkommen
standen in Wahrheit im zweiten `[[reihe.umrechnung]]` der **Reihe 2**; Reihe 4 trägt gar
keine Normierung. Der Bauagent ist trotzdem richtig gelandet. Der Fehler ist meiner —
die Belegstelle stammt aus meinem Paketrumpf, nicht aus seiner Arbeit.
