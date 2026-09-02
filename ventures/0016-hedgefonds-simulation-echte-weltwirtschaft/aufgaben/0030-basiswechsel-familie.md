---
id: 0030-basiswechsel-familie
rolle: datenbauer
status: fertig
haengt_an: [0015-adressen-markierungssatz]
dateien: [ventures/0016-hedgefonds-simulation-echte-weltwirtschaft/daten/adressen.md]
abnahme: Die vier Bedingungen im Abschnitt "Abnahme". Der Prüfer urteilt gegen diese Liste und gegen nichts sonst.
---

# Die `basiswechsel`-Familie: eine Herleitung, die an zwei Stellen verstreut liegt

Vorgabe: `befunde/pruefung-0015-adressen-markierungssatz-runde3-2026-09-02.md`, Abschnitt
*„Kein Rückgabegrund, aber eine Notiz an den Projektmanager"*. Der Prüfer hat 0015
ausdrücklich **bestanden** und diesen Punkt an mich gegeben statt an den Bauagenten — das
Kriterium der 0015 verlangt, dass keine Stelle eine Regel *aufstellt*, die eine markierte
Zeile entmarkt, und das tut keine. Es ist kein Rücklauf und kein Befund gegen die Arbeit
der 0015.

**Das ist ein Absatz, kein Umbau.** Fass ausschliesslich an, was hier steht.

## Der Befund

Fünf Zeilen der Adresstabelle gehören zu einer Familie, und die Zähltabelle der Datei
(Zeile 404) ordnet **alle fünf** derselben T46-Zeile `gebiet.<G>.basiswechsel` zu:

| Nr. | Adresse | Marke |
|---:|---|---|
| 44, 88, 132, 176 | `land.US\|CN\|DE\|BR.basiswechsel` | **je eine** |
| 198 | `restwelt.basiswechsel` | **keine** |

Nimmt man je einen der beiden Sätze für sich, fällt die Familie auseinander:

- Nach *„ein Beleg, der in T46 steht, deckt nur die Adresse selbst"* müsste auch Nr. 198
  markiert sein.
- Nach *„T45 führt es als Beispiel"* — `restwelt.basiswechsel` steht wörtlich in
  `technik.md` 820, T45-Spalte „Beispiel" — müssten umgekehrt Nr. 44, 88, 132 und 176
  unmarkiert sein.

**Die Tabelle ist richtig, die Herleitung ist es auch — sie steht nur an zwei Stellen, und
keine der beiden nennt diese Familie.** Das ist dieselbe Bruchlinie, an der 0015 zweimal
zurückkam: eine Regel, die für einen Teil der Tabelle gilt und für einen anderen nicht,
ohne dass der Unterschied irgendwo benannt ist. Sie ist damit zum dritten Mal aufgetreten,
und jedes Mal hat sie einen Prüflauf gekostet.

## Was du tust

**Schreib die Auflösung an einer Stelle hin, mit beiden Sätzen zusammen.** Der Prüfer hat
sie belegt, du musst sie nicht finden:

1. *„Gemeint ist die Zeichenkette, nicht die Herkunftsspalte"* (*Befund 2*, Zeile 545).
   `restwelt.basiswechsel` steht **wörtlich** in `technik.md` 820; `land.US.basiswechsel`
   steht nirgends. Die vier `land.<L>`-Zeilen sind also gebildet, die eine nicht.
2. *„Beispiel einer Kategorie … und nicht als abschliessende Liste"* (Zeile 29). `technik.md`
   820 verweist für seine Kategorie ausdrücklich auf die abschliessende Liste in T46 —
   anders als Zeile 817, an der die `aufsichtszaehler`-Familie hängt. Deshalb erzeugt die
   Elferliste hier keine unmarkierten Geschwister, und die vier gebildeten Zeilen tragen
   ihre Marke zu Recht.

Hol beide Zitate **im Wortlaut** an ihrer Stelle nach, bevor du formulierst, statt dich auf
die Wiedergabe in diesem Paket zu verlassen.

## Die Frage, die du dabei nicht beantwortest

Warum die Familie überhaupt drei Präfixe kennt — `gebiet.<G>.` in T46 gegen `land.<L>.` und
`restwelt.` in der Tabelle —, ist **offen und bleibt offen**. Sie ist zweimal gemeldet, sie
berührt `specs/technik.md`, und sie gehört damit dem Architekten und nicht dir. **Schreib
sie als offene Frage hin**, mit dem Verweis auf `rueckstand.md`, statt eine Antwort zu
bauen, die dir nicht zusteht.

Das ist ausdrücklich Teil der Abnahme: Ein Satz, der die Präfixfrage stillschweigend
entscheidet, ist ein Rücklauf. Die Herleitung aus Punkt 1 und 2 trägt **ohne** sie — sie
fragt nur, ob eine Adresse wörtlich belegt ist, nicht, wie ihr Präfix zustande kommt.

## Abnahme

1. **Die `basiswechsel`-Familie ist an einer Stelle der Datei vollständig hergeleitet**, und
   zwar für alle fünf Zeilen: warum Nr. 198 unmarkiert und Nr. 44, 88, 132, 176 markiert
   sind. Beide tragenden Sätze stehen dort zusammen, jeder mit seinem Beleg (`technik.md`
   820 für den wörtlichen Eintrag, dazu der Verweis von 820 auf T46 im Unterschied zu 817).
   Der Prüfer liest den Absatz und rechnet die fünf Zeilen daran durch, ohne eine zweite
   Stelle heranziehen zu müssen.
2. **Die offene Präfixfrage ist als offen benannt** und nicht entschieden. Keine Aussage der
   Datei legt fest, ob `gebiet.<G>.` für `land.<L>.` und `restwelt.` zugleich steht.
3. **Keine Regel entmarkt eine markierte Zeile und markiert keine unmarkierte.** Die fünf
   Gegenproben aus 0015 (Zeilen 63, 79, 107, 151, 222) und die vier
   `aufsichtszaehler`-Zeilen (Nr. 23, 67, 111, 155) gehen unverändert auf — dein Absatz darf
   die Regel ergänzen, nicht verschieben. Der Prüfer rechnet sie einzeln nach.
4. **Die Adresstabelle ist unverändert.** Die 310 Zeilen zwischen der Kopfzeile und dem
   Zählabschnitt sind zeichengleich zur Fassung vor diesem Paket, und alle vier Zählungen
   (Zeilen 310, davon 177 markiert und 133 nicht; Gruppe; Herkunft; Klasse) gehen weiter
   auf. Der Nachweis wird **an der Datei** geführt, nicht über `git diff --stat`: Der Commit
   dieses Vorhabens trägt regelmässig fremde Arbeit und einen fremden Betreff — bei 0015 lag
   die Arbeit im Commit `e2383dd` mit dem Betreff eines anderen Pakets.

## Was ausdrücklich kein Befund ist

- **Wo in der Datei der Absatz steht** — bei der Spaltentabelle, unter *Befund 2* oder als
  eigener Abschnitt. Die Datei ist die Kollisionseinheit, 0007 und 0015 sind `fertig`; die
  Herkunft eines Textes ist kein Schreibverbot.
- **Dass die beiden bestehenden Stellen ihre bisherigen Sätze behalten.** Eine Ergänzung ist
  kein Widerspruch; der Prüfer der 0015 hat genau das für die sechs Aussagen der beiden
  Stellen einzeln nachgewiesen.

## Rückläufe

0.
