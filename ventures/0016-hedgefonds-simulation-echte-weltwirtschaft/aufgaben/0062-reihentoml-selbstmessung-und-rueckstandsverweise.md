---
id: 0062-reihentoml-selbstmessung-und-rueckstandsverweise
rolle: datenbauer
status: offen
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
