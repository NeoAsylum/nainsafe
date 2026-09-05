---
typ: pruefung
paket: 0055-zollzeile-vergleichszahl-zustand-b
pruefer: entwurf-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen einzeln — Bedingung 1 durch Abgleich jeder im Absatz verwendeten Größe gegen ihre Tabellenzeile, Bedingung 2 durch eigenes Nachrechnen der sechs Zeilen auf zwei verschiedenen Rundungswegen, Bedingung 3 an der Datei und zusätzlich am dateibezogenen Diff (vier Hunks, keiner berührt die geschützten Zahlen).
befunde: 0
---

# Prüfung 0055 — die Vergleichszahl gehört jetzt zu dem Zustand, über dem sie steht

Gegenstand: `specs/0016-hedgefonds-simulation-echte-weltwirtschaft/spiel.md`, Abschnitt
**Zwei Zustände, zwei Zahlen** (Zeilen 1068–1128 der heutigen Fassung).

Das Paket ließ die Wahl zwischen Weg A und Weg B. Gebaut ist **Weg A**: Die Zahl
`32.850.000` ist im Absatz durch `8.472.000` ersetzt, und die Tabelle trägt die
Eingabezeile nach, die dafür fehlte. Geprüft wird das Ergebnis gegen die drei
Bedingungen, nicht die Wahl.

## Bedingung 1 — keine Größe für Zustand B, die die Tabelle ihm nicht gibt

**Erfüllt.** Ich habe den Absatz ab „Zustand B ist die Abnahme" (Zeile 1097) neben die
Tabelle gelegt und **jede** darin vorkommende Größe einzeln gegen ihre Zeile gehalten:

| im Absatz verwendet | Tabellenzeile | Spalte Zustand B |
|---|---|---|
| `11.000` / `10.400` | `lies_neu(welt.preis.1)` / `(welt.preis.2)` (Z. 1077) | „dieselben" |
| `380` (in `10.000 + 380`) | `…instrument.zoll.stand` (Z. 1078) | `380 → 380 bp` |
| `10.000` (als `preis_alt`) | `lies_alt(…sektor.1.preis)` / `(…sektor.2.preis)` (Z. 1079) | „dieselben" |
| `7.288` / `5.464` | `durchgriff(DE,1)` / `(DE,2)` (Z. 1076) | „dieselben" |
| `40.000.000` / `100.000.000` | `handelsvolumen(DE,1)` / `(DE,2)` (Z. 1075) | „dieselben" |

Die Prüfstelle, die das Paket ausdrücklich nennt: Der Absatz rechnet mit `40.000.000`
und `100.000.000`, zusammen `1,4·10^8` — also mit dem Wert der Zeile darüber. Ein
Handelsvolumen von `1,5·10^9` kommt in der ganzen Datei nur noch **einmal** vor
(Zeile 2232, in der Befundabarbeitung) und dort in dem Satz, der es als Größe eines
fremden Zustands ausweist: *„Die Zahl selbst ist richtig, nur für einen anderen
Zustand."* Das ist der Fall, den Bedingung 2 ausdrücklich freistellt.

Die Eingabezeile `preis_alt = 10.000` ist nicht nur eingetragen, sondern belegt: Der
Abschnitt *Was für die Preisbildung gelten muss* schreibt in Zeile 272–273 „In Runde 1
ist es der Startwert des Jahrgangs (Index 10.000)". Zwei Stellen der Datei, die sich
nicht kennen, nennen denselben Wert.

## Bedingung 2 — die Vergleichszahl ist nachrechenbar

**Erfüllt.** Ich habe alle sechs Zeilen selbst gerechnet, mit `mal_geteilt` und der
Rundungsregel aus T6 (`technik.md` Zeile 639–641: „Rundung **auf halbe Beträge von null
weg**" — der Abschnitt zitiert sie korrekt):

```
11.000 · 10.380 = 114.180.000  → /10.000 = 11.418,0      → 11.418   (exakt, keine Rundung)
 1.418 ·  7.288 =  10.334.384  → /10.000 =  1.033,4384   →  1.033
40.000.000 · 1.033 / 10.000                              =  4.132.000
10.400 · 10.380 = 107.952.000  → /10.000 = 10.795,2      → 10.795
   795 ·  5.464 =   4.343.880  → /10.000 =    434,388    →    434
100.000.000 · 434 / 10.000                               =  4.340.000
                                                   Summe =  8.472.000
```

Jede Zahl des Blocks stimmt, einschließlich der Nebenrechnung: `795,2 · 5.464 =
4.344.972,8`, geteilt `434,49728 → 434` — genau die Ziffernfolge, die dort steht. Ein
Rundungsgleichstand tritt nirgends auf (`,4384`, `,2`, `,388`, `,49728`), die Halbregel
von T6 entscheidet hier also gar nichts.

**Gegenprobe auf dem zweiten Rundungsweg.** Zeile 1041 sagt, die alte Zeile habe „einmal
in den gespeicherten Sektorpreis und einmal in den Schaden" gerundet — der Block rundet
stattdessen zwischen Weltpreis und Schaden. Ich habe deshalb auch über die
Preisbildungsregel (Zeile 266) gerechnet, also über den gespeicherten `preis_neu`:

```
Sektor 1: (11.418 · 7.288 + 10.000 · 2.712)/10.000 = 110.334.384/10.000 = 11.033,4384 → 11.033
          |11.033 − 10.000| = 1.033                                        (identisch)
Sektor 2: (10.795 · 5.464 + 10.000 · 4.536)/10.000 = 104.343.880/10.000 = 10.434,388  → 10.434
          |10.434 − 10.000| =   434                                        (identisch)
Sektor 2, mit ungerundetem 10.795,2:              104.344.972,8/10.000 = 10.434,49728 → 10.434
```

Alle drei Wege führen auf `1.033` und `434` und damit auf **8.472.000**. Die Aussage des
Abschnitts, die Rundung entscheide hier nichts, trägt also weiter als er selbst behauptet.

Die Herleitung ist außerdem formtreu: Die Identität in Zeile 939
(`preis_neu − preis_alt = durchgriff/10.000 · (wmz − preis_alt)`) folgt durch Einsetzen
aus der Preisbildungsregel in Zeile 266, und `Beitrag = handelsvolumen · preishub /
10.000` ist die Zollzeile aus Zeile 919 mit `preishub` statt `preishub_zoll` — also
genau die Vorfassung, die Zeile 911 beschreibt.

Der Vergleichssatz **mehr als das Neunzehnfache** stimmt: `8.472.000 / 440.000 = 19,25…`,
und `19 · 440.000 = 8.360.000 < 8.472.000`.

## Bedingung 3 — sonst hat sich nichts geändert

**Erfüllt.** An der Datei geführt, wie das Paket es verlangt:

- Die sieben Größen von Zustand A stehen unverändert in Tabelle und Nachrechnung —
  `55`, `52` (Z. 1081), `40`, `28` (Z. 1082), `160.000`, `280.000` (Z. 1083), `440.000`
  (Z. 1084). Ich habe sie zusätzlich nachgerechnet: `11.000·50/10.000 = 55`;
  `10.400·50/10.000 = 52`; `7.288·55/10.000 = 40,084 → 40`; `5.464·52/10.000 = 28,4128 →
  28`; `160.000 + 280.000 = 440.000`.
- `schaden(DE, zoll)` für Zustand B steht weiter auf **0** (Z. 1084), und die Begründung
  darüber („für jeden Weltpreis, jede Preisträgheit und jedes Handelsvolumen") ist
  unangetastet.
- Die Entscheidung für Weg 1 und ihre Maß-2-Begründung (Z. 966–1002, Grund 1 mit
  `max(Ek) ≤ 1,25 × min(Ek)`) sind wortgleich.
- Die Zahl `106` kommt an keiner neuen Stelle vor: sieben Fundzeilen vorher, sieben
  nachher (Z. 43, 1249, 1262, 1263, 2105, 2122, 2296), keine davon im Diff.
- Die zweite Fundstelle von `32.850.000` in der Ursachenkette (jetzt Z. 986) ist
  unverändert.

**Zusätzlich, weil es billiger ist als jedes Stichprobenargument:** Der dateibezogene
Diff `7d8ab26 → 84a472a -- spiel.md` besteht aus **vier** Hunks — Änderungsvermerk im
Kopf, die eine neue Tabellenzeile, der ersetzte Absatz samt Erläuterung der neuen Zeile,
und der Abschnitt *Befundabarbeitung* am Ende. Keiner berührt eine der oben geschützten
Zahlen. Das ist kein `--stat`-Argument: Der Commit trägt genau diese eine Datei, und
`git log -- spiel.md` nennt danach keinen weiteren; die Arbeitskopie ist sauber.

Die Grenzen des Pakets sind eingehalten: `technik.md` und `daten/adressen.md` sind nicht
im Commit, es ist keine Kalibrierzahl und keine Zustandsadresse hinzugekommen.

## Wonach ich gesucht habe, ohne dass es ein Befund wurde

Damit erkennbar bleibt, wo diese Prüfung hingesehen hat:

1. **Ob der Absatz eine weitere fremde Größe trägt.** Nicht nur die vom Paket genannte
   Handelsvolumenzeile, sondern jede der fünf Eingaben einzeln gegen die Tabelle — siehe
   die Tabelle unter Bedingung 1. Auch der Satz „Beide Zustände unterscheiden sich in
   **genau einer** Größe" ist gegengezählt: Von den fünf Eingabezeilen tragen vier
   „dieselben", eine den Zollstand.
2. **Ob die neue Tabellenzeile eine Zahl erfindet.** `10.000` ist über die
   Preisträgheitsregel (Z. 272–273) unabhängig belegt, nicht bloß aus dem Paket
   übernommen.
3. **Ob ein anderer Rundungsweg eine andere Zahl ergibt.** Drei Wege gerechnet, alle
   `8.472.000` — siehe Bedingung 2.
4. **Ob die Vorfassungsformel richtig rekonstruiert ist.** Gegen Z. 266, Z. 939 und die
   Zollzeile in Z. 919 geprüft, nicht gegen die Beschreibung im Paket.
5. **Ob `32.850.000` irgendwo unbeschriftet weiterlebt.** Zwei Fundstellen vorher, drei
   nachher; die zwei neuen stehen in der Befundabarbeitung und benennen beide den
   fremden Zustand ausdrücklich.
6. **Der Änderungsvermerk im Kopf sagt „Betroffen ist ein Absatz"**, während der Diff
   einen Absatz, eine Tabellenzeile, eine Erläuterung und einen Abschnitt enthält. Kein
   Befund: Derselbe Satz zählt Tabellenzeile und Abarbeitung ausdrücklich mit, die
   Erläuterung gehört zur nachgetragenen Zeile, und keine der drei Bedingungen handelt
   vom Kopfvermerk. Ich notiere es, damit sichtbar ist, dass die Stelle geprüft wurde.
7. **Die zwei Herleitungen der 106** (`112 + 4 + 4 − 8 − 8 + 2` in Z. 1262 und
   `112 + 8 − 16 + 2` in Z. 2296) sind nachgerechnet, beide ergeben 106 und beide sind
   von diesem Paket nicht angefasst. Kein Befund.

## Was diese Prüfung ausdrücklich nicht sagt

Sie sagt nichts darüber, ob die Zollzeile in der Sache richtig ist — das war Gegenstand
von 0039 und ist dort `geprueft`. Sie sagt auch nichts über Maß 4 und die Kalibrierzahlen;
beides ist am Entwurf nicht entscheidbar.

**Kein Vorschlag für ein neues Arbeitspaket** aus diesem Lauf. Die eine Beobachtung, die
über das Paket hinausgeht — Maß 2 nennt im Frontmatter „höchstens 25 Prozent besser" und
in Z. 976 `max(Ek) ≤ 1,25 × min(Ek)` —, ist von 0055 nicht berührt und steht seit dem
2026-09-03 als offene Fährte in meinem Logbuch; sie gehört in ein Paket, das Maß 2
anfasst, nicht in dieses.
