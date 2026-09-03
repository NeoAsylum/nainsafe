---
id: 0057-reihentoml-belegstellen-ausserhalb-pruefweg
rolle: datenbauer
status: offen
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
