---
typ: pruefung
paket: 0020-wertebereichsschranken-je-runde
pruefer: test-pruefer
datum: 2026-09-02
urteil: geprueft
kriterium_geprueft: Alle fuenf Abnahmebedingungen einzeln nachgewiesen; die Empfindlichkeit der Probe mit 21 Mutanten gemessen, von denen jeder einzelne sie rot macht.
befunde: 1
---

# Die Schrankenprobe wird rot, wenn man die Schranken kaputtmacht

Geprueft ist `kern/test/schranken_probe.cpp` (1.042 Zeilen, ein Commit, `3208fdd`)
gegen die fuenf Bedingungen im Abschnitt *Abnahme* des Arbeitspakets — und gegen
nichts sonst.

## Der Ausgangsbefund reicht nicht

`ctest -R schranken` meldet `Passed`, und der Uebersetzungsbericht fuehrt
`schranken_probe` als Test #3. Das ist kein Nachweis: Eine Probe, die ihre eigene
Pruefung gegen ihre eigenen Erwartungen haelt, ist gruen, solange beides zusammen
falsch ist. Die Frage dieser Rolle ist die andere — **wird sie rot, wenn man die
gepruefte Sache kaputtmacht?** Deshalb steht die Mutationsmessung unten vor allem
anderen.

## Die Mutationsmessung: 21 Mutanten, 21 Tote

Uebersetzt wurde jeder Mutant frei stehend gegen `kern/include` und `kern/bau/libkern.a`;
Rueckgabewert `0` heisst bestanden, `1` heisst die Probe hat es gemerkt. Die Mutanten
entstanden aus dem unveraenderten Original ueber `string(REPLACE)`, jeder mit einer
Fehlerbremse, die abbricht, wenn das Muster nicht traf — sonst haette ein Tippfehler eine
unveraenderte Datei erzeugt und ihr Bestehen als Empfindlichkeit gezaehlt.

**Erstens, jede der zehn Sachen einzeln stummgeschaltet.** Am einzigen Engpass
(`Befund::melde`) schweigt genau eine Sache, gesteuert ueber `-DAUS=n`:

| `AUS` | Sache | Rueckgabewert |
|---:|---|---:|
| 99 | keine (Kontrolllauf, Bremse eingebaut aber wirkungslos) | **0** |
| 0…9 | Schranke 1…7, Gleichheit 1, Gleichheit 2, Sektoranteile | **je 1** |

Der Kontrolllauf ist der wichtige: Er zeigt, dass die eingebaute Bremse fuer sich
genommen nichts kaputtmacht. Alle zehn Sachen sind also **einzeln** belegt, nicht bloss
in Summe.

**Zweitens, Schwellen verschoben statt Pruefungen entfernt** — die Sorte Fehler, die
sich nicht durch eine fehlende Zeile verraet:

| # | Mutation | Rueckgabe |
|---|---|---:|
| m1 | Schranke 1: `< 1` → `< 0` (Kurs 0 durchgelassen) | 1 |
| m2 | Schranke 1: `< 1` → `< 2` (Kurs 1 faelschlich verworfen) | 1 |
| m3 | Schranke 5: `>= MARKT_WERT_MAX` → `>` (Rand 9,2e13 durchgelassen) | 1 |
| m4 | Schranke 7: `> ANTEIL_GANZ` → `> ANTEIL_GANZ + 1` | 1 |
| m5 | Sektoranteile: `ANTEIL_SCHLUPF` 1 → 2 (9.998 durchgelassen) | 1 |
| m6 | Schranke 6: `> g.druck_max` → `+ 1` | 1 |
| m7 | Schranke 4: `summe < 1` → `< 0` | 1 |
| m8 | Schranke 7: `betrag > stufen_max` → `+ 1` | 1 |
| m9 | Schranke 2 und 3: `<= 0` → `< 0` (Wert 0 durchgelassen) | 1 |

Beide Richtungen fallen auf, zu weit **und** zu eng — das ist der Beleg dafuer, dass die
Raender aus Bedingung 3 wirklich geprueft werden und nicht nur die Mitte.

**Drittens, die Adressmengen verfaelscht:**

| # | Mutation | Rueckgabe | gedruckt |
|---|---|---:|---|
| m10 | `.preisniveau` faellt aus Schranke 2 | 1 | `17 Adressen (Soll 22) ABWEICHUNG` |
| m11 | Schranke 7 nur noch Waehrungssteckplaetze | 1 | `16 Adressen (Soll 32) ABWEICHUNG` |

## Die fuenf Bedingungen einzeln

**1 — Vollstaendigkeit.** Zehn Sachen, in `enum class Sache` einzeln benannt und mit
ihrer Nummer aus der T30-Untertabelle bezeichnet. Gegen `technik.md` Zeile 1375–1386
gelegt: sieben Schranken, zwei Gleichheiten, Sektoranteile. Keine fehlt, keine
zusaetzliche ist erfunden.

**2 — Die Adresszahlen.** Die Probe zaehlt nicht ab, sondern laeuft ueber alle 310
Plaetze und entscheidet am Namen aus `index_zu_adresse` — die Zahl kommt also aus dem
Verzeichnis, wie die Bedingung es verlangt. Gedruckt und gegen `daten/adressen.md`
nachgerechnet:

| Schranke | gedruckt | Klasse in `adressen.md` |
|---|---:|---|
| 1 Wechselkurs | 5 | K 6 = 5 (Nr. 19, 63, 107, 151, 195) |
| 2 Nominalindizes | 22 | K 5 = 22 (`4×4 + 4` Restwelt `+ 2` Weltpreise) |
| 3 Produktivitaet | 5 | K 7 = 5 |
| 4 Leitzinsstand | 4 | Nr. 25, 69, 113, 157 |
| 5 `markt.wert` | 1 | Nr. 253 |
| 6 Druck/Gegendruck | 32 | K 9 = 32 (`4 × 8`) |
| 7 Anteil + Stufe | 12 + 20 | 12 `…anteil` + Nr. 263–282 |
| Gleichheiten | je 4 Paare | Nr. 18/25, 62/69, 106/113, 150/157 bzw. 21/33 … |
| Sektoranteile | 5 Gebiete | je drei `.sektor.<s>.wertschoepfung` |

Die Klassengrenzen habe ich am Namensmuster einzeln nachgeprueft, weil eine gleich
grosse, aber falsche Menge von der Zaehlung allein nicht auffiele. Zwei Stellen, an
denen das haette schiefgehen koennen, gehen auf: `welt.preis.<s>` endet nicht auf
`.preis` und wird darum getrennt eingesammelt statt doppelt; und `.gegendruck` endet
nicht auf `.druck` (davor steht ein `n`, kein Punkt), wird also nicht zweimal gezaehlt.
Beide Male stimmt die Summe nur, weil die Unterscheidung stimmt.

**3 — Jede Sache einmal rot, und keine andere mit.** Die Probe vergleicht eine Bitmaske
ueber die zehn Sachen gegen die erwartete; im Lauf erscheinen die Masken 1, 2, 4, 8, 16,
32, 64, 128, 256, 512 — jede mit genau einem gesetzten Bit. Die drei namentlich
verlangten Raender sind da und stehen richtig herum: `wechselkurs = 1` besteht /
`= 0` faellt; `fondsanteil = 10.000` besteht / `10.001` faellt; `markt.wert = 9,2e13 − 1`
besteht / `= 9,2e13` faellt.

Sauber geloest ist der Fall, der sich hier leicht selbst betruegt: Bei Schranke 4 werden
Instrumentenstand und gleichnamiges Aggregat **zusammen** gesetzt, sonst risse dieselbe
Aenderung zugleich Gleichheit 1, und die Maske sagte nicht mehr, welche der beiden
gefunden wurde.

Eine Abweichung, die ich geprueft und fuer richtig halte: Die **Summenbedingung** der
Sektoranteile wird nicht aus einem Zustand heraus rot, sondern an `anteile_ok` direkt
(1.428 + 1.428 + 7.142 = 9.998, wie eine abschneidende statt rundende Bildung sie
liefert). Die Begruendung im Code traegt: Bei der vorgeschriebenen Bildung liegt der
Rundungsfehler dreier Quotienten unter 3/2, die Summe also zwingend in 9.999…10.001, und
ein Zustand kann sie darum gar nicht reissen. Bewacht wird die *Bildungsregel*, und genau
dort wird sie rot — Mutant m5 belegt es. Die zweite Haelfte der Bedingung („kein Anteil
ausserhalb 0…10.000") wird sehr wohl aus einem Zustand heraus rot. Ein
`ANTEIL_SCHLUPF = 0` waere hier kein schaerferer, sondern ein falscher Test: Drei gleich
grosse Sektoren ergeben 3.333 × 3 = 9.999.

**4 — Begruendung im Code bei Schranke 1 und 5.** Beide vorhanden, ueber der jeweiligen
Pruefung, je vier bis sechs Zeilen, und beide nennen den Punkt aus `technik.md`
Zeile 1388–1391: der negative Kurs, der still jedes Vorzeichen dreht, und der Marktkorb,
der erst tief in `tsd_in_cent` abstuerzt.

**5 — Kein Gleitkomma, kein Dateizugriff, keine Fremdabhaengigkeit.** Beide vorgegebenen
Suchmuster laufen leer: `float|double` — nichts; `fstream|ifstream|fopen|std::filesystem`
— nichts. Eingebunden sind vier Standardkoepfe und `kern/sperre.hpp`, das Gleitkomma zum
Uebersetzungsfehler macht. Die drei Grenzen stehen als Argument in `Grenzen` und nennen
ihren Schluessel; die drei Fundstellen habe ich nachgeschlagen und sie stimmen auf die
Zeile:

| Behauptung im Code | `parameter.toml` |
|---|---|
| Zeile 205 `stufen_max = 1 # PLATZHALTER` | Zeile 205, `stufen_max = 1  # PLATZHALTER` |
| Zeile 250 `aufschlag = 51 # PLATZHALTER` | Zeile 250, `aufschlag = 51  # PLATZHALTER` |
| Zeile 304 `druck_max = 1 # PLATZHALTER` | Zeile 304, `druck_max = 1  # PLATZHALTER` |

## Wonach ich sonst gesucht und was ich nicht gefunden habe

**Abgeschwaechte Tests.** `git log` auf die Datei zeigt genau einen Commit; es gibt keine
Fassung, in der eine Schwelle gesenkt, eine Zusicherung entfernt oder ein Fall
uebersprungen worden waere. Der einzige Toleranzwert der Datei (`ANTEIL_SCHLUPF = 1`) ist
ausgerechnet und nicht eingestellt — m5 zeigt, dass er bei 2 auffliegt.

**Regressionsbestand und Determinismustest** sind T30 Pruefung 3 und 4 und nicht
Gegenstand dieses Pakets; hier ist nichts gespeichert und nichts nachgerechnet.

**Die vier ausgelassenen Sachen aus T30 Pruefung 2** (Handelsbilanzsumme,
Staatsschuldfortschreibung, Fondsvermoegen nach T47, Ergebnisbaender nach T34) fehlen
zu Recht — das Arbeitspaket nimmt sie ausdruecklich aus, weil Weltschritt, Paket 0002
und eine gespielte Partie fehlen. Ein Platzhalter waere hier schlechter als eine Luecke.
Kein Platzhalter ist da.

**Der Nullzustand** wird geprueft und reisst fuenf der zehn Sachen (Maske 535). Die Probe
sagt das hin und faellt nicht darauf herein, ihn fuer einen Startzustand zu halten.

## Nebenbefund — kein Ruecklaufgrund, aber gehoert notiert

**Die Anteilsrechnung kann abbrechen statt zu melden.** `anteile_aus_zustand` sichert die
Summe zweifach (`summe <= 0` und `summe > I64_MAX`), nicht aber den Quotienten:
`mal_geteilt(wert, 10.000, summe)` bricht nach T7 hart ab, wenn das Ergebnis nicht mehr in
`i64` passt.

Erzeugt so — drei Wertschoepfungen eines Gebiets auf `1e15`, `−999999999999999`, `0`
gesetzt, Summe also `1`, womit beide Wachen danebengreifen:

```
Rueckgabewert: 134
terminate called after throwing an instance of 'std::domain_error'
  what():  mal_geteilt: Ergebnis ausserhalb von i64 (T7)
```

Das ist kein stiller Fehler — der Abbruch ist laut und T7-konform. Aber die Meldung zeigt
auf `festkomma`, nicht auf die Sektoranteile, und das ist genau das Muster, das T30 bei
Schranke 5 beim Namen nennt: „stuerzt ab, aber an einer Stelle, an der niemand die
Ursache sucht". Der Autor hat es fuer `markt.wert` gesehen und im eigenen Rechenweg
stehen lassen.

**Warum trotzdem kein Ruecklauf und kein eigenes Paket:** Die Abnahme verlangt es nicht,
und der Fall ist im heutigen Zuschnitt unerreichbar — die Probe setzt ihre Zustaende
selbst. Er wird erst scharf, wenn die Pruefung aus der Probe heraus in ein aufrufbares
Modul wandert und der Bruchtester sie in T30 Pruefung 5 und 6 ueber 10.000 Partien ruft.
Genau diese Verschiebung steht schon als Frage in `rueckstand.md`. Dort gehoert die
dritte Wache hin, nicht in ein eigenes Paket — ein Vorschlag ueber drei Zeilen, die im
selben Zug ohnehin angefasst werden, kostet den Projektmanager mehr als er bringt.

## Urteil

`geprueft`. Alle fuenf Abnahmebedingungen sind erfuellt, jede mit Nachweis. Die Probe
haelt der Frage stand, an der die meisten Pruefstaende scheitern: Sie wird rot, wenn man
die Sache kaputtmacht — und zwar in beide Richtungen und bei jeder der zehn einzeln.
