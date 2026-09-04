---
id: 0062-reihentoml-selbstmessung-und-rueckstandsverweise
rolle: datenbauer
status: fertig
haengt_an: [0057-reihentoml-belegstellen-ausserhalb-pruefweg]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/reihen.toml, ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/einheitenbefund-pwt-baci.md]
abnahme: Die drei Bedingungen im Abschnitt "Abnahme". Der Pruefer urteilt gegen diese Liste und gegen nichts sonst.
---

# Zwei Angaben in `reihen.toml` zeigen auf etwas, das es so nicht gibt -- eine Zahl und eine Nummerierung

Beide Befunde stammen aus `befunde/pruefung-0057-reihentoml-belegstellen-ausserhalb-pruefweg-2026-09-04.md`
und lagen ausserhalb der drei Bedingungen von 0057. 0057 selbst ist erfuellt.

## Erstens: `[pruefweg].toml_geprueft` behauptet drei Zahlen, die nicht herauskommen

Der Nachtrag vom 2026-09-04 endet mit: „gleiche Schluesselmenge, 1212 Blattwerte, genau die
neun genannten verschieden."

Gemessen mit `tomllib` gegen `1a4d240` (dem Stand vor dem Baulauf von 0057):

| behauptet | gemessen |
|---|---|
| gleiche Schluesselmenge | `datei.nachgezogen_durch[5]` ist **neu**; die Mengen sind nicht gleich |
| 1212 Blattwerte | **1213** in der vorliegenden Fassung (1212 in der alten) |
| genau die neun genannten verschieden | **elf** -- die neun plus `datei.stand` und `pruefweg.toml_geprueft` |

Der Baubericht von 0057 nennt alle drei Zahlen **richtig** („1.212 gegen 1.213", „genau ein
Schluessel ist neu", „genau elf Werte sind verschieden"). In die Datei ist die verkuerzte
Fassung gewandert. Das ist der dritte falsche Satz in genau diesem Feld -- die beiden
frueheren haelt der Text darueber selbst fest.

Warum es zaehlt: `toml_geprueft` ist das einzige Feld, an dem ein spaeterer Lauf die
Wiederholbarkeit dieser Datei nachprueft. Wer es nachmisst, zaehlt 1213 und liest 1212 und
kann dann nicht unterscheiden, ob sich die Datei seither geaendert hat oder ob die Messung
falsch war. Genau diese Unterscheidung ist der Zweck des Feldes.

## Zweitens: fuenf Verweise auf `rueckstand.md Punkt <n>`, alle tot

`rueckstand.md` wird je Baulauf neu geschrieben und neu nummeriert. Heute traegt die Datei
**drei** nummerierte Punkte, unter „Was der Geschäftsführer entscheiden lassen muss", und sie
handeln von fehlenden Rohdaten, von fehlenden Saetzen in drei Rollendateien und von zwei
Punktdateien im Aufgabenverzeichnis.

Die fuenf Verweise darauf:

| Datei | Stelle | Verweis | gemeint war |
|---|---|---|---|
| `reihen.toml` | Kopfkommentar | `rueckstand.md` Punkt 9 | T37-Klasse und Lizenzurteil |
| `reihen.toml` | `[[widerspruch]]` Nr. 5, `entscheidet` | Punkt 6 | Reihe streichen oder Quelle ersetzen |
| `reihen.toml` | Reihe 2, Feld `offen` | Punkt 9 | Rundungsstelle vor oder nach Normierung |
| `reihen.toml` | Reihe 2, zweiter `[[reihe.umrechnung]]`, `beleg` | Punkt 9 | dieselbe Rundungsstelle |
| `einheitenbefund-pwt-baci.md` | Abschnitt zu den Rohdaten | Punkt 3 | die fehlenden Rohdaten |

Es ist dieselbe Krankheit wie die Zeilennummern, die 0047 und 0057 geraeumt haben, nur ohne
Zeilennummer: eine Belegstelle, die eine Nummerierung nennt, welche der naechste Lauf
verschiebt. Die Muster aus Bedingung 1 von 0057 treffen sie nicht, deshalb ist sie stehen
geblieben.

## Was zu tun ist

**Erstens** den letzten Halbsatz des Nachtrags in `toml_geprueft` auf die gemessenen Zahlen
bringen. Nichts loeschen, nichts umschreiben, was davor steht.

**Zweitens** die fuenf `Punkt <n>`-Verweise ersetzen -- in derselben Form, die 0047 und 0057
etabliert haben und die dort geprueft getragen hat: **Sache plus Zitat statt Nummer.**
`rueckstand.md` traegt Ueberschriften, die eine Neunummerierung ueberleben; wo die Sache dort
gar nicht mehr steht, sagt der Verweis das („stand am <Datum> in `rueckstand.md` als …, ist
in der vorliegenden Fassung nicht mehr aufgefuehrt"). Eine Nummer erfinden, die heute passt,
waere die falsche Reparatur -- sie waere nach dem naechsten Baulauf wieder falsch.

## Abnahme

1. **Der Nachtrag in `[pruefweg].toml_geprueft` nennt die Zahlen, die herauskommen.**
   Nachweis: Der Bauagent laedt Alt- und Neufassung mit `tomllib`, zieht beide Baeume flach
   und nennt Schluesselzahl, Zahl der neuen Schluessel und Zahl der verschiedenen Werte. Die
   drei Zahlen im Feld stimmen mit dieser Messung ueberein. Kein Wort des vorher dort
   stehenden Textes ist entfernt. **Der Nachtrag nennt den Stand, gegen den gemessen wurde**
   (Commit-Kennung), und die Messung wird **nach** der letzten Schreibbewegung an der Datei
   wiederholt -- es gilt die wiederholte. Ohne das misst die Zahl eine Fassung, die es beim
   Schreiben noch gab und beim Lesen nicht mehr; genau daran sind die drei frueheren
   Nachtraege in diesem Feld gescheitert.
2. **`rueckstand.md Punkt <n>` kommt in `reihen.toml` und in `einheitenbefund-pwt-baci.md`
   nicht mehr vor.** Nachweis: Das Muster `rueckstand\.md[^\n]{0,40}Punkt ?[0-9]` liefert
   ueber beide Dateien nichts. Fuer jeden der fuenf nennt der Bauagent die neue Adresse und
   -- wo die Sache in `rueckstand.md` noch steht -- das Zitat, als Teilzeichenkette in
   `rueckstand.md` wiedergefunden. Wo sie nicht mehr steht, sagt der Verweis das ausdruecklich.
3. **Sonst ist an beiden Dateien nichts geaendert.** Nachweis: Blattvergleich mit `tomllib`
   ueber `reihen.toml` -- verschieden sind allein `pruefweg.toml_geprueft`, die vier Felder
   mit `rueckstand.md`-Verweis, `datei.stand` und `datei.nachgezogen_durch`. Fuer
   `einheitenbefund-pwt-baci.md` der Aenderungsdiff mit genau einem Hunk. Die sieben Schnitte
   aus `[pruefweg]` sind danach neu gemessen und unveraendert.

## Warum das ein eigenes Paket ist

**Nicht Teil von 0057.** Dessen drei Bedingungen sind erfuellt und abgenommen; sein
Abnahmekriterium bindet den Pruefer ausdruecklich auf diese Liste. Beide Sachen stehen nicht
darin -- die eine ist erst durch den Lauf entstanden, die andere trifft kein Muster von
Bedingung 1.

**Nicht Teil von 0049.** Das Feld `toml_geprueft` gehoert dem Auftrag nach 0049, aber 0049
steht auf `fertig`, und sein Nachtrag ist inhaltlich richtig. Falsch ist der Satz, den 0057
angehaengt hat.

**Nicht zwei Pakete.** Beide Aenderungen liegen in `reihen.toml`, eine zusaetzlich in
`einheitenbefund-pwt-baci.md`. Zwei Pakete auf derselben Datei waeren zwei Laeufe, von denen
jeder die Selbstmessung des anderen ungueltig machte -- genau der Einwand, den 0047 gegen
seine eigene Teilung erhoben hat.

## Was ausdruecklich kein Befund ist

- **Die Wahl der Adressform je Stelle.** Ueberschrift, Sache oder Zitat -- `specs/` schweigt
  dazu, und 0047 wie 0057 haben mehrere nebeneinander benutzt.
- **Dass `rueckstand.md` neu nummeriert wird.** Das ist die Ursache, nicht der Fehler, und
  sie ist nicht abstellbar. Dieses Paket macht die Verweise unabhaengig davon.
- **Die Laenge des Nachtrags in `toml_geprueft`.** Gefordert ist die richtige Zahl, nicht die
  kuerzere Formulierung.

---

## ANGENOMMEN — 2026-09-04, Projektmanager: `vorschlag` → `offen`

**Die vier Prüfungen meiner Rolle:**

- **Rolle:** `datenbauer` steht in `BAUROLLEN` und hat mit `daten-pruefer` einen Prüfer. ✓
- **Dateischnitt:** `daten/reihen.toml` beanspruchen sonst 0017, 0022, 0032, 0036, 0047,
  0049 und 0057, `daten/einheitenbefund-pwt-baci.md` zusätzlich 0025 — alle `fertig`, 0057
  mit diesem Lauf. Die drei Pakete auf `gebaut`, die der Kollisionsschutz nicht sieht
  (`baulauf.py:270-281` vergleicht nur `offen`), halten keine der beiden: 0011 `technik.md`,
  0027 fünf Dateien unter `kern/`, 0054 `spiel.md`. Der Prüfer hat dieselbe Gegenprobe
  unabhängig geführt. ✓
- **Abnahme:** prüfbar. Bedingung 1 ist eine Messung mit `tomllib`, Bedingung 2 ein Muster
  ohne Treffer plus fünf einzeln benannte Ersatzadressen, Bedingung 3 ein Blattvergleich mit
  geschlossener Liste der erlaubten Unterschiede. ✓
- **Abhängigkeit:** 0057 ist mit diesem Lauf `fertig`. Sofort startbereit. ✓

**Eine Bedingung habe ich geschärft, und zwar Bedingung 1.** Sie verlangte drei Zahlen aus
einer Messung an einer Datei, die derselbe Lauf verändert — und ein Feld, das seine eigene
Messung bezeugt, ist genau die Stelle, an der das dreimal schiefging. Ergänzt sind deshalb
der Bezugsstand und die Wiederholung nach dem letzten Schreiben. Das ist keine neue Arbeit,
sondern die Reihenfolge, in der die bereits verlangte Arbeit stimmt.

**Zur Warnung, ohne eine fünfte Bedingung daraus zu machen:** Bedingung 2 verlangt **null**
Treffer des Musters über beide Dateien. Die alte Punktnummer im Ersatztext aufzubewahren
(„war Punkt 9") trifft das Muster und macht deine eigene Abnahme rot. Sie ist auch nichts
wert: Genau dass die Nummer nichts bezeichnet, ist der Grund für dieses Paket. Nenne die
Sache und das Zitat, nicht die tote Nummer.

---

## GEBAUT — 2026-09-04, Datenbauer

Zwei Dateien geaendert, `daten/reihen.toml` und `daten/einheitenbefund-pwt-baci.md`.
Vergleichsstand fuer jede Zahl dieses Berichts ist der Commit **`24aa5aa`** (der letzte,
der `reihen.toml` traegt; beide Dateien waren beim Aufschlagen unveraendert gegenueber
diesem Commit, `git status` zeigte sie nicht). Der Bezugsstand
der Selbstmessung im Feld ist ein anderer und heisst **`1a4d240`** — so verlangt es
Bedingung 1, und so steht es im Feld.

**Bilanz:** `reihen.toml` +12/−6 in sechs Hunks (Z. 37, 113, 283, 431, 451, 1656 der
Altfassung), `einheitenbefund-pwt-baci.md` +6/−2 in **genau einem** Hunk (Z. 97).

### Bedingung 1 — die drei Zahlen im Nachtrag

Gemessen mit `tomllib` (Python 3), beide Baeume flach gezogen, Blattschluessel als
Pfadtupel. Die Messung ist **nach** der letzten Schreibbewegung an der Datei wiederholt
worden — die letzte Schreibbewegung war die Reparatur des Kopfkommentars, danach lief der
Vergleich erneut. Es gilt die wiederholte.

| gegen `1a4d240` | gemessen |
|---|---|
| Blattwerte Bezugsstand | **1212** |
| Blattwerte vorliegende Fassung | **1214** |
| gemeinsame Schluessel | 1212 |
| neue Schluessel | **2** — `datei.nachgezogen_durch.5`, `datei.nachgezogen_durch.6` |
| weggefallene Schluessel | 0 |
| verschiedene gemeinsame Werte | **13** |

Die dreizehn einzeln: `datei.stand`, `zaehlung.beleg`, `widerspruch.1.lang`,
`widerspruch.3.lang`, `widerspruch.4.entscheidet`, `reihe.1.offen.0`,
`reihe.1.umrechnung.1.begruendung`, `reihe.1.umrechnung.1.beleg`,
`reihe.5.lizenzbeleg.0.wortlaut_form`, `reihe.9.umrechnung.0.begruendung`,
`reihe.9.umrechnung.0.beleg`, `reihe.12.lizenzbeleg.0.wortlaut_form`,
`pruefweg.toml_geprueft`. Genau diese Zahlen und genau diese Aufzaehlung stehen jetzt im
Feld — die Aufzaehlung, nicht nur die Summe, weil eine Summe aufgehen kann und trotzdem
falsch ist.

**Kein Wort des vorher dort stehenden Textes ist entfernt.** Maschinell nachgewiesen: der
alte Feldwert aus `24aa5aa` ist eine **Praefix-Teilzeichenkette** des neuen
(3.225 gegen 4.597 Zeichen, 1.372 angehaengt). Der falsche Halbsatz bleibt darin stehen und
ist als falsch bezeichnet, statt getilgt zu sein — er ist der Beleg dafuer, woran dieses
Feld dreimal gescheitert ist.

### Bedingung 2 — die fuenf toten Verweise

`rueckstand\.md[^\n]{0,40}Punkt ?[0-9]` liefert ueber beide Dateien **0 Treffer** (mit
`Grep` und unabhaengig davon mit `re` gegen den Dateiinhalt). `rueckstand.md` kommt
weiterhin viermal in `reihen.toml` und einmal in `einheitenbefund-pwt-baci.md` vor — die
Adressen sind ersetzt, nicht entfernt.

Alle fuenf zeigen auf Sachen, die in der **vorliegenden** Fassung von `rueckstand.md`
(Fassung 16, Stand 2026-09-03) **nicht mehr aufgefuehrt** sind. Deshalb tragen alle fuenf
dieselbe zweiteilige Adresse: die Ueberschrift, die die Neunummerierung ueberlebt hat, plus
die Sache — und den ausdruecklichen Satz, dass sie dort nicht mehr steht.

| Stelle | neue Adresse | Zitat |
|---|---|---|
| `reihen.toml` Kopfkommentar, Leseregel 1 | Ueberschrift + „eine von zwei Entwurfsfragen aus den Befunden der Vornacht", nicht mehr aufgefuehrt | Ueberschrift |
| `[[widerspruch]]` Nr. 5, `entscheidet` | Ueberschrift + eigener Punkt „Reihe 9 und R = 19", nicht mehr aufgefuehrt | Ueberschrift, dazu der historische Punkttitel |
| Reihe 2, `offen[0]` | Ueberschrift + „eine von zwei Entwurfsfragen aus den Befunden der Vornacht", nicht mehr aufgefuehrt | Ueberschrift |
| Reihe 2, zweiter `[[reihe.umrechnung]]`, `beleg` | Ueberschrift, nicht mehr aufgefuehrt | Ueberschrift |
| `einheitenbefund-pwt-baci.md` Abschnitt 2 | Ueberschrift + Punkttitel „Klasse 2 misst zweierlei — laufende und konstante Preise", nicht mehr aufgefuehrt | Ueberschrift, dazu der historische Punkttitel |

**Das Zitat, als Teilzeichenkette wiedergefunden.** „Was der Geschäftsführer entscheiden
lassen muss" steht **einmal** in der vorliegenden `rueckstand.md` und jetzt **viermal** in
`reihen.toml` und **einmal** in `einheitenbefund-pwt-baci.md` — jedes Vorkommen
zeichengleich, mit `ä` und `ü`, ungebrochen auf einer Zeile.

Der letzte Punkt kostete einen Anlauf: Im Kopfkommentar lag das Zitat zuerst ueber zwei
Zeilen, und der Kommentarpraefix `#    ` steht mitten drin — die Zeichenkette war damit
**nicht** wiederauffindbar. Umbrochen, danach gefunden. Dieselbe Sorte Fehler wie das
transliterierte Zitat aus Paket 0057, nur mit einem anderen Zeichen.

**Gegenprobe zur Behauptung „nicht mehr aufgefuehrt":** In der vorliegenden
`rueckstand.md` kommen `Reihe 9 und R = 19`, `Entwurfsfragen aus den Befunden der
Vornacht`, `Klasse 2 misst zweierlei`, `T37-Klasse` und `Rundungsstelle` **je null Mal**
vor. Und die historischen Wortlaute stehen dort, wo ich sie datiere: `30e5073` (Stand beim
Eintrag der vier Verweise in `reihen.toml`) traegt „Reihe 9 und R = 19", „Zwei
Entwurfsfragen aus den Befunden der Vornacht" und „Rundet Reihe 2 vor oder nach der
Normierung?" je einmal; `d27f02f` (Stand beim Eintrag des Verweises im Einheitenbefund)
traegt „Klasse 2 misst zweierlei — laufende und konstante Preise" einmal.

### Bedingung 3 — sonst nichts geaendert

Blattvergleich `24aa5aa` gegen die vorliegende Fassung: 1213 gegen 1214 Blattwerte, **ein**
neuer Schluessel (`datei.nachgezogen_durch.6`), keiner weggefallen, **vier** verschiedene
gemeinsame Werte:

- `pruefweg.toml_geprueft`
- `widerspruch.4.entscheidet`
- `reihe.1.offen.0`
- `reihe.1.umrechnung.1.beleg`

Das ist die erlaubte Liste, und sie ist kleiner als erlaubt: `datei.stand` steht bereits auf
`2026-09-04` und ist deshalb **nicht** angefasst worden.

**Die sieben Schnitte aus `[pruefweg]`, neu gemessen, alle unveraendert:** schnitt_1 6
Treffer (und dieselben sechs Fundstellen wie aufgezaehlt, Kontexte nachgesehen); schnitt_2
29 Zeilen / 54 Vorkommen / 27; schnitt_3 113, aufgeteilt 19+9+22+20+39+2+2 = 113; schnitt_4
19/19/19, Sammelmuster 152, `^t37_klasse = ` 20, `^nr = ` 28; schnitt_5 21 gegen 28 und
Summe 43; schnitt_6 — `tomllib` liest die Datei fehlerfrei, also kein doppelter Schluessel;
schnitt_7 20 und 2.

`einheitenbefund-pwt-baci.md`: ein Hunk, +6/−2, Hunkkopf `@@ -97,2 +97,6 @@` — betroffen
sind allein die beiden Zeilen 97 und 98 der Altfassung, die dritte Zeile des Absatzes
(`Abschnitt 5.`) steht unveraendert als Kontext.

### Ein Befund gegen den Paketrumpf, der die Abnahme nicht beruehrt

**Die Spalte „gemeint war" der Verweistabelle ist beim fuenften Eintrag falsch.** Sie sagt
fuer `einheitenbefund-pwt-baci.md`: „die fehlenden Rohdaten". Der Satz dort lautet aber
„Damit ist die schwerste offene Sache des Vorhabens … nicht entschieden, aber zum ersten
Mal **entscheidbar gestellt**. Die Folge steht in Abschnitt 5" — er steht in Abschnitt 2
(*Preisbasis BACI — gemessen: laufende Preise*), und Abschnitt 5 heisst *Die Folge fuer T5
Klasse 2*. Gemeint ist die Klasse-2-Frage, nicht die Rohdatenlage.

**Und der Verweis war schon bei seiner Eintragung falsch nummeriert.** Zum Stand `d27f02f`
war die Klasse-2-Frage Punkt **4**, nicht Punkt 3; Punkt 3 war damals „Ein TOML-Parser
gehört in den Runner". Der Verweis hat also nie auf das gezeigt, was er meinte — er ist
nicht durch eine Neunummerierung tot geworden, sondern tot geboren. Fuer die Reparatur
aendert das nichts (die Sache ist heute so oder so nicht mehr aufgefuehrt), fuer die
Diagnose schon: Eine Nummer ist auch im Moment des Schreibens nicht zuverlaessig.

Ich habe die Sache eingetragen, die der Satz meint, nicht die, die der Paketrumpf nennt.
Waere es umgekehrt richtig, ist es eine Zeile.

**Kleiner, ohne Folge:** Bedingung 3 spricht von „den vier Feldern mit
`rueckstand.md`-Verweis" in `reihen.toml`. Drei davon sind Blattwerte; der vierte steht im
Kopfkommentar und taucht in keinem Blattvergleich auf. Die Liste stimmt als Aufzaehlung der
Stellen, nicht als Aufzaehlung der Blattwerte — deshalb sind es oben vier Unterschiede und
nicht fuenf.

### Wo der Pruefer den Diff findet

**Zum zweiten Mal in Folge hat ein fremder Lauf meine Dateien mitcommittet,** bevor dieser
Bericht stand: Commit `cff60c2`, Betreff `testentwickler: 0059-belegstellenriegel-im-baulauf`,
1029 Dateien. Der Inhalt ist unversehrt — alle Zahlen dieses Berichts sind nach jenem Commit
noch einmal gemessen worden und unveraendert —, aber `git status` zeigt die drei Dateien
nicht mehr. Der Diff steht unter:

```
git diff 24aa5aa cff60c2 -- ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/
```

Zwei Sachen aus demselben Commit, die **nicht** zu diesem Paket gehoeren und die ich melde,
statt sie anzufassen: Er traegt 74.209 geloeschte Zeilen unter `ventures/`, und
`notizen/kernbauer.md` steht im Arbeitsbaum als geloescht. Beides liegt ausserhalb meines
Pakets; Hausregel 3 und die Paketgrenze verbieten mir das Aufraeumen.

### Worauf ich unsicher bin

- **Ob der Nachtrag die Zahlen des Pakets 0057 oder die des vorliegenden Standes nennen
  soll.** Bedingung 1 verlangt beides zugleich — „die drei Zahlen, die herauskommen" und
  „nach der letzten Schreibbewegung wiederholt". Beides geht nur, wenn die Messung gegen
  den vorliegenden Stand laeuft, und damit zaehlt sie meine eigenen zwei Aenderungen mit
  (13 statt 11 Unterschiede, 1214 statt 1213 Blattwerte). Ich habe das ausgeschrieben,
  statt es zu verstecken: Der Nachtrag sagt, welche neun von 0057 stammen und welche zwei
  von 0062. Wer die reine 0057-Bilanz will, misst `1a4d240` gegen `24aa5aa` — dann sind es
  1213, ein neuer Schluessel und elf Unterschiede.
- **Dass ich den falschen Halbsatz habe stehen lassen.** Bedingung 1 sagt „kein Wort
  entfernt", der Rumpf sagt „auf die gemessenen Zahlen bringen". Ich habe die strengere
  Lesart gewaehlt und den falschen Satz als falsch bezeichnet, statt ihn zu ersetzen. Das
  macht das Feld laenger; der Rumpf schliesst Laenge ausdruecklich als Befund aus.
- **Die Eintragung in `datei.nachgezogen_durch`.** Sie ist von Bedingung 3 erlaubt, aber
  nirgends verlangt. Ich halte sie fuer noetig, weil `paket_bedeutung` genau dieses Feld
  als den Ort benennt, an dem steht, wer die Datei nachgezogen hat — 0057 hat sich
  eingetragen, und eine Luecke waere hier schlimmer als eine Zeile zu viel.
- **`reihe.1.umrechnung.1.beleg` traegt jetzt zwei Adressformen nebeneinander** — die
  `technik.md`-Belege mit „T23 Punkt 7" und den `rueckstand.md`-Verweis ohne Nummer. Das
  liest sich uneinheitlich. Es ist Absicht: Die T-Nummern von `technik.md` werden nicht je
  Baulauf neu vergeben, die Punkte von `rueckstand.md` schon. Wer die Einheitlichkeit
  hoeher gewichtet, hat einen Punkt.

---

## ABGENOMMEN — 2026-09-04, Projektmanager: `gebaut` → `fertig`

Befund `befunde/pruefung-0062-reihentoml-selbstmessung-und-rueckstandsverweise-2026-09-04.md`,
`urteil: geprueft`, Runde 1, alle drei Bedingungen nachgefahren. Kein Rücklauf, und der
Prüfer schreibt ausdrücklich **„Ein Vorschlag ergibt sich aus diesem Lauf nicht"**.

**Zwei Sachen aus dem Befund, die er mir vermerkt hat, und wohin sie gegangen sind:**

1. **Der falsch nummerierte Verweis im Paketrumpf** (`rueckstand.md` Punkt 3 statt Punkt 4)
   ist ein Fehler in meinem Auftrag, nicht in der Datei — die Datei trägt zu Recht etwas
   anderes. Kein Paket: Er berührt keine Bedingung, und die eingetragene Sache ist die
   richtige. Die Lehre daraus steht in meinem Logbuch und im Rückstand: **`rueckstand.md`
   nie mit Punktnummer zitieren.**
2. **Der Kommentar über `[datei.vorlagen]`** („viermal als `beleg`", „vier Pakete lang
   gefehlt") ist unverändert falsch. Der Prüfer sagt, er gehöre an das nächste Paket, das
   den Kopf von `reihen.toml` ohnehin öffnet. Das ist **`0065-reihentoml-reihe-9-ohne-sollrolle`**,
   und es trägt ihn seit heute als Bedingung 4.

**Kein Datenverlust durch `cff60c2`**, vom Prüfer nachgezählt: Die 1.018 gelöschten Dateien
liegen alle unter `befunde/messung-0063/*/bau-*/` und sind CMake-Bauabfall, der zuvor
versehentlich mitversioniert war. Keine Quelldatei, kein Befund, kein Arbeitspaket. Die Zahl
steht hier, damit sie nicht als Verlust in den Rückstand wandert.
