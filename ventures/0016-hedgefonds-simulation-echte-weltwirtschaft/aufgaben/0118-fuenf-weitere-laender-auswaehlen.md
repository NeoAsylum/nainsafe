---
id: 0118-fuenf-weitere-laender-auswaehlen
rolle: spielentwerfer
status: offen
haengt_an: [0117-geschaetzter-politikpfad-und-zwei-laenderklassen, 0119-welt-in-drei-schichten, 0128-zaehlung-vier-je-land-statt-vier-r]
dateien: [specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md]
abnahme: Die fünf Bedingungen im Abschnitt "Abnahme". Bedingung 3 rechnet auf der Steckplatzzahl, die nach 0119 gilt, gegen die 20 von heute — nicht auf den 45 aus der Ländergeometrie allein; siehe den Annahmevermerk.
---

# ANGENOMMEN — 2026-09-05, Projektmanager: `vorschlag` → `offen`, mit einer Berichtigung an Bedingung 3

Vier Prüfungen: **Rolle** `spielentwerfer` steht in `BAUROLLEN`, Prüfer ist der
`entwurf-pruefer`. **Dateischnitt** `spiel.md`, geteilt nur mit 0119, und das steht in
`haengt_an` — die Kette ist richtig. **Abhängigkeit** 0117 und 0119; über 0117 hängt dieses
Paket transitiv auch an 0116 und 0051. Es ist damit das **letzte** der vier Pakete des
Betreibers und läuft frühestens, wenn die drei anderen abgenommen sind. **Abnahme** fünf
Bedingungen — vier davon messbar wie sie dastehen, eine nicht. Die eine korrigiere ich.

## Bedingung 3 rechnet auf einer Zahl, die dieses Paket nicht mehr vorfindet

Bedingung 3 verlangt, *„wie viele der 45 Plätze ein Spieler über die volle Partielänge
erreichen kann"*. Die 45 sind die Steckplätze bei `L = 9` **aus der Ländergeometrie allein**.
Dieses Paket hängt aber an 0119, und 0119 führt die Börsenplätze ein und kommt auf **75**
handelbare Plätze. Es sagt das selbst und ausdrücklich:

> Der Betreiber hat am 2026-09-05 entschieden, dass die Steckplätze mitwachsen (Weg A in
> Paket 0118). Die Rechnung dazu gehört dorthin und muss **beide** Zuwächse tragen, nicht
> nur die 45 aus den Ländern.

**Beide Pakete stammen vom selben Tag und vom selben Autor; 0119 ist das jüngere und weiß
von diesem hier.** Es ist keine Meinungsverschiedenheit, sondern ein Halbsatz, der beim
Schreiben des zweiten Pakets im ersten stehen geblieben ist. Bliebe er stehen, hätte der
Bauagent die Wahl zwischen einer Zahl, die seine Bedingung nennt, und einer, die sein
Vorgängerpaket in dieselbe Datei geschrieben hat — und beide Antworten wären begründbar.
Genau diese Sorte Kriterium hat hier schon dreimal eine erbrachte Leistung durchfallen
lassen.

**Was ab jetzt gilt — die Bedingung, nicht der Wortlaut:** Bedingung 3 ist erfüllt, wenn die
Deckungsrechnung auf der Steckplatzzahl steht, die nach 0119 **tatsächlich in `spiel.md`
festgelegt ist**, gegen die 20 von heute gerechnet. Lies sie dort nach, statt eine Zahl aus
diesem Absatz zu übernehmen — 0119 wird vor dir gebaut und geprüft, und wenn sein Prüfer die
Größenordnung verschiebt, gilt seine. Alles andere an Bedingung 3 bleibt Wort für Wort:
gegen die 20 von heute, und **genau eine** empfohlene Stellschraube, falls die Deckung unter
das fällt, was die vier Maße tragen.

**Was ich nicht geändert habe:** Die Tabelle aus Bedingung 4 bleibt, wie sie ist. Ihre
`Zustand gesamt 740` ist die Ländersumme und richtig; die Gesamtzahl des Zustands nach den
drei Schichten ist 890 und gehört 0119. Schreib beim Übertragen dazu, welche der beiden
Zahlen die Tabelle meint — zwei unkommentierte Summen in einem Dokument sind der Anfang des
nächsten Zählfehlers.

**An den Betreiber:** Wenn du das anders willst — wenn die 45 gemeint waren und die
Börsenplätze nicht in die Deckungsrechnung gehören —, ist das eine Zeile hier, und sie
sticht diesen Vermerk.

# Fünf weitere Länder — welche, warum, und in welcher Klasse

**Anweisung des Betreibers, 2026-09-05:** *„Lass uns insofern direkt 5 weitere Länder
einplanen."* Aus vier werden neun.

Das **widerspricht einer festgehaltenen Entscheidung.** `spiel.md`, *Was bewusst fehlt*:
„Zwölf Länder vervierfachen die Rückkopplungswege ohne ein Maß zu verbessern." Neun liegt
zwischen den vier des Entwurfs und den zwölf der Idee. Der Betreiber hat die Zahlen
unten gesehen und entschieden; deine Aufgabe ist die Ausführung, nicht die Revision.
**Widersprich nicht, sondern gestalte.**

## Was neun Länder kosten

Gerechnet aus den Konstanten in `kern/zustand.hpp`; die Formel reproduziert für `L = 4`
exakt die heutigen 310.

| Block | L=4 | L=9 | |
|---|---:|---:|---|
| Länder (44 je Land) | 176 | 396 | 2,2× |
| Handel `G·(G−1)·2` | 40 | **180** | **4,5×** |
| Nachahmer | 12 | 27 | 2,2× |
| Positionssteckplätze | 20 | **45** | 2,2× |
| Beteiligungen | 24 | 54 | 2,2× |
| fest (Restwelt, Fonds, Markt, Partie …) | 38 | 38 | 1,0× |
| **Zustand gesamt** | **310** | **740** | **2,4×** |

Und je nach Klassenwahl aus 0117:

| | alle neun als Rückvergleichsland | fünf als Spielland |
|---|---:|---:|
| Sollreihen | 62 | **27** |
| Prüfgegenstände | 36 | **16** |
| Datenreihen zu beschaffen | 5 × 19 | 5 × 19 |
| Lizenzstellen zusätzlich | 10 | 10 |

**Die Klassentrennung spart Daten und Prüfaufwand, keine Adressen.** Der Zustand wächst
in beiden Fällen auf 740.

## Die Entwurfsfrage, die das aufwirft

**Die Positionssteckplätze wachsen von 20 auf 45 — und das ist kein Geometriefall.**

`spiel.md` begründet die Knappheit als Quelle der Entscheidungsdichte: bis zu **drei**
Aktionen je Runde, und *„wer alles tun kann, wählt nicht"*. Bei 20 Plätzen und drei
Aktionen ist die Wahl eng; bei 45 ist sie es nicht mehr im selben Maß. Der Zustand
kommentiert die Zwanzig ausdrücklich als feste Größe: *„Es gibt keine Liste, in die etwas
aufgenommen oder aus der etwas entfernt würde."*

**Der Betreiber hat am 2026-09-05 Weg A gewählt: die Steckplätze wachsen mit `L`,
von 20 auf 45.** Die Wahl steht nicht mehr offen. Was offen ist, ist die Folge daraus,
und sie ist deine Aufgabe:

> Drei Aktionen je Runde auf 45 Plätzen sind ein anderes Spiel als drei auf 20.
> **Sag, wie die Entscheidungsdichte erhalten bleibt.**

`spiel.md` nennt die Knappheit unter *Die härteste Vorgabe* als Quelle der
Entscheidungsdichte — *„wer alles tun kann, wählt nicht"*. Bei 45 Plätzen und
unveränderten drei Aktionen sinkt der Anteil des Spielfelds, den ein Spieler je Runde
berühren kann, von 15 auf 7 Prozent. Das kann richtig sein: Ein grösseres Brett bei
gleicher Zugzahl macht die Wahl **wichtiger**, nicht beliebiger. Es kann aber auch
bedeuten, dass eine Partie über R Runden das Feld nicht mehr abdeckt.

**Rechne es aus, statt es zu behaupten.** Wie viele der 45 Plätze kann ein Spieler über
die volle Partielänge überhaupt erreichen, und wie verhält sich das zu den 20 von heute?
Fällt die Deckung unter das, was die vier Masse tragen, benenne die Stellschraube, die
du empfiehlst — Aktionszahl, Partielänge oder Zusammenfassung von Plätzen — **und
empfiehl genau eine.** Der Betreiber entscheidet, du legst vor.

Verworfen ist damit **B** (gedeckelte Steckplätze mit Auswahlmechanik); die Begründung
für die Verwerfung ist die Entscheidung des Betreibers, nicht eine fachliche, und das
gehört so hingeschrieben.

## Wonach die fünf zu wählen sind

Dieselbe Regel wie bei den ersten vier: **strukturelle Verschiedenheit, nicht Bedeutung.**
Vier Kopien wären vier Kopien. Die heutigen vier decken großer Binnenmarkt mit Leitwährung
(US), Industrie mit gemanagtem Kurs (CN), Exportüberschuss ohne Zinshebel (DE),
Agrarexport mit volatiler Währung (BR).

Benenne für jedes neue Land die **Eigenschaft, die noch keines trägt** — Kandidatenfelder,
nicht Vorgaben: Rohstoffexporteur mit Währungsbindung, Finanzplatz ohne eigene Industrie,
Wirtschaft unter Kapitalverkehrskontrollen, Land in einer Zollunion, Schuldnerland unter
IWF-Programm.

**Die Datenlage ist Mitentscheider, nicht Nachgedanke.** `daten/nachmessung-zinsreihen-2026-09-05.md`
zeigt, wie unterschiedlich die Deckung ausfällt: Die USA tragen die Anleiherendite von
1953 bis 2021, Deutschland nur bis 2017, China trägt im ganzen Fenster keine einzige
jährliche Zinsreihe. Ein Land, dessen Reihen fehlen, ist damit nicht ausgeschlossen — es
wird ein **Spielland** nach 0117. Sag für jedes der fünf, welche Klasse du erwartest und
woran das hängt.

**Was nicht dazugehört:** Daten beschaffen, Lizenzen prüfen, `technik.md` ändern, den Kern
anfassen. Die Adressarithmetik ist 0116, die Klassen sind 0117.

## Abnahme

1. **Fünf Länder sind namentlich benannt**, jedes mit der strukturellen Eigenschaft, die
   noch keines der vier heutigen trägt, in einem Satz je Land.
2. **Jedem ist eine Klasse zugeordnet** (Rückvergleichsland oder Spielland) mit der
   Bedingung, unter der es die Klasse wechseln würde.
3. **Die Folge aus Weg A ist gerechnet, nicht behauptet.** Der Abschnitt nennt, wie
   viele der 45 Plätze ein Spieler über die volle Partielänge erreichen kann, gegen die
   20 von heute gerechnet, und benennt genau eine empfohlene Stellschraube, falls die
   Deckung unter das fällt, was die vier Masse tragen.
4. **Die Tabelle oben steht in `spiel.md`** mit den Werten für `L = 9`, und der Abschnitt
   *Was bewusst fehlt* ist auf die neue Zahl nachgezogen — die alte Aussage über zwölf
   Länder bleibt stehen und wird nicht gelöscht, sondern eingeordnet.
5. **`git diff` zeigt Änderungen ausschließlich in `spiel.md`.** Keine Zahl in
   `technik.md`, `reihen.toml` oder im Kern wird angefasst; die 310 bleiben stehen, bis
   0116 die Ableitungskette geschrieben hat.

## Reihenfolgesperre auf 0128 — Kollisionsschutz, keine sachliche Abhängigkeit

**Ergänzt am 2026-09-05 vom Projektmanager.** `0128` berichtigt zwei Sätze in derselben
Datei: die Zählung der verworfenen 195-Länder-Welt nennt den Buchstaben der Partielänge,
wo die Zahl der Rückvergleichsländer gemeint ist. Beides sind Ein-Satz-Änderungen, beides
steht in `spiel.md`.

**Was du von dort brauchst: nichts** — außer einem ruhigen Dateistand. Die Sperre steht
im Frontmatter, damit zwei Läufe nicht gleichzeitig auf dieselbe Datei schreiben; sie ist
kein fachliches Vorher. **Sie kostet dich keinen Bauplatz:** Dieses Paket wartet ohnehin
auf 0117, und 0128 ist bis dahin längst durch.

**Was sie dir erspart:** 0128 räumt genau das Symbol weg, aus dem Bedingung 3 hier ihre
Ländergeometrie ableitet. Läuft es danach, rechnest du auf einer Stelle, die schon
berichtigt ist — statt den Fehler in deine eigene Rechnung zu übernehmen.

**Dein Vorher-Stand** ist der dann geltende `HEAD`. Such am Text, nicht an einer
Zeilennummer: `spiel.md` ist heute schon durch 0119 gewandert und wandert durch 0128 ein
zweites Mal.

## Rückläufe

0.
