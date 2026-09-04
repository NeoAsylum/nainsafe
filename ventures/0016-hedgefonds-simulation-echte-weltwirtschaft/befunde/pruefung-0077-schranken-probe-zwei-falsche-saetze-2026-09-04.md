---
typ: pruefung
paket: 0077-schranken-probe-zwei-falsche-saetze
pruefer: test-pruefer
datum: 2026-09-04
urteil: geprueft
kriterium_geprueft: Alle drei Bedingungen selbst nachgemessen -- die vier Muster mit ihren Trefferzahlen, die 12 in `parameter.toml`, eigener Neubau samt `ctest`; dazu beide Ersatzsaetze gegen `parameter.toml` nachgeschlagen, ein Mutationsstand mit vier Faellen (Kontrolle gruen, drei Mutanten tot, darunter der auf die geschuetzte Konstante) und ein Maschinencodevergleich alt/neu, der zeigt, dass keine Zusicherung angefasst wurde.
befunde: 1
---

# 0077: Abnahme erfuellt. Beide Ersatzsaetze sind nachgeschlagen und tragen.

## Vorbemerkung: was dieses Paket pruefbar macht, und was nicht

Das Paket aendert ausschliesslich Kommentartext. Damit zerfaellt die Pruefung in zwei
Fragen, die verschiedene Nachweise brauchen:

1. **Steht der neue Text da, und ist er wahr?** Das ist die eigentliche Sache. 0044 hat
   seine Abnahme erfuellt und trotzdem einen falschen Satz hinterlassen, weil die
   Bedingung nur die *Abwesenheit eines Musters* mass. Ich messe deshalb den **Ersatz**
   gegen `parameter.toml`, nicht gegen den Paketrumpf.
2. **Ist unterwegs eine Zusicherung verlorengegangen?** Kommentaraenderungen sind der
   bequemste Ort, um still eine Schwelle mitzunehmen. Dagegen hilft kein Lesen, sondern
   ein Vergleich des erzeugten Maschinencodes.

## Bedingung 1 -- der Kopfsatz verspricht keine Zeilennummer mehr

Muster `Schluesselname und Zeile` ueber `kern/test/schranken_probe.cpp`: **kein Treffer.**
Muster `Zeile 0-9 (Ziffer hinter dem Wort)` ueber dieselbe Datei: **kein Treffer.**

**Der Rotnachweis dazu, damit die beiden Nullen etwas heissen:** Beide Muster gegen die
Fassung *vor* dem Baucommit gelegt (`git show 113d91b^:.../schranken_probe.cpp`) --
`Schluesselname und Zeile` **1 Treffer**, `Jeder Schluessel der Datei steht genau einmal`
**1 Treffer**. Die Bedingungen unterscheiden also den kaputten vom heilen Stand; sie sind
nicht bloss zwei Muster, die nirgends vorkommen.

**Und der Ersatz traegt.** Der Satz lautet heute "Schluesselname und die zitierte
Schluesselzeile stehen bei jedem". Beides steht bei jedem der drei Schluessel -- der Name
im Feldkommentar und noch einmal im Belegblock, die Schluesselzeile als Zitat darunter.
Nachgeschlagen gegen `parameter.toml`:

| Schluessel | Zeile heute | Wortlaut | Zitat in der Probe |
|---|---:|---|---|
| `stufen_max` | 254 | Wert 1, Marke PLATZHALTER | Zitat mit Ausrichtungsleerzeichen |
| `aufschlag` | 299 | Wert 51, Marke PLATZHALTER | Zitat mit Ausrichtungsleerzeichen |
| `druck_max` | 353 | Wert 1, Marke PLATZHALTER | Zitat mit Ausrichtungsleerzeichen |

Schluessel, Zuweisung, Wert und die Marke PLATZHALTER stimmen dreimal ueberein; die
Zitate tragen zusaetzliche Leerzeichen zur Spaltenausrichtung. Das ist kein Befund -- die
Abnahme verlangt kein zeichengleiches Zitat, und die Ausrichtung stammt aus 0044. Ich
nenne es, weil eine kuenftige Bedingung, die Zitate *im Wortlaut* nachschlaegt (der
Gedanke aus dem Abschnitt an den Projektmanager), hier ueber Leerzeichen stolpern wuerde.

## Bedingung 2 -- die falsche Verallgemeinerung ist weg, und die neue ist nachgemessen

Muster `Jeder Schluessel der Datei steht genau einmal` ueber `schranken_probe.cpp`: **kein
Treffer.** Die geforderte Vertraeglichkeit des Ersatzsatzes mit der Zaehlung
`^schrittweite|^instrument_min|^instrument_max` ueber `parameter.toml`: **12** -- die Zahl
aus dem Annahmevermerk stimmt und ist heute vorgefunden, nicht uebernommen.

Der Ersatzsatz macht vier nachschlagbare Behauptungen. Ich habe alle vier einzeln gegen
`parameter.toml` gemessen, nicht gegen den Paketrumpf -- genau das war die Ursache des
Fehlers, den dieses Paket berichtigt:

| Behauptung im neuen Text | gemessen | Befund |
|---|---|---|
| Diese drei Schluessel stehen je genau einmal am Zeilenanfang | `^druck_max|^stufen_max|^aufschlag` liefert 3 Treffer, Zeilen 254/299/353 | stimmt |
| Die vier `instrument.*`-Tabellen | 4 Treffer: 876 `leitzins`, 899 `zoll`, 916 `haushalt`, 939 `regulierung` | stimmt |
| `schrittweite`, `instrument_min`, `instrument_max` je viermal am Zeilenanfang | 12 Treffer, gleichmaessig 4 plus 4 plus 4 | stimmt |
| Alle drei stehen unter der Ueberschrift GRUPPE A, die elf Zeilen der Tabelle in T27 | Ueberschrift auf Zeile 228, naechste Gruppenueberschrift auf 372; 254/299/353 liegen dazwischen; Wortlaut zeichengleich | stimmt |

**Was der Bauagent richtig unterlassen hat:** Der Paketrumpf nennt 50 Schluesselzeilen,
41 verschiedene Schluessel, 38 eindeutige und drei Zeilennummerntripel. Keine dieser
Zahlen ist in die Quelle gewandert. Der neue Text kommt mit vier und viermal aus -- den
beiden Zahlen, die ich selbst nachzaehlen kann, ohne dem Paket zu glauben. Das ist die
Lehre aus 0044 angewandt statt zitiert.

## Bedingung 3 -- Konstante, Zusicherungen, Test, Riegel

**Die Konstante `GRENZEN_BAUZEITPUNKT` mit 1, 1, 51:** unveraendert, steht heute in
`schranken_probe.cpp:437`. Der Diff des Baucommits `113d91b` fasst die Zeile nicht an.

**Zusicherungen:** `PRUEFE(`, `ROT(` und `GRUEN(` zusammen **64** Vorkommen auf 64
verschiedenen Zeilen -- die geforderte Zahl. Keine entfernt, keine hinzugefuegt.

**`schranken_probe` besteht:** nicht dem Uebersetzungsbefund geglaubt, sondern selbst neu
gebaut. `cmake -S . -B ...` und `cmake --build`, dann `ctest -R schranken_probe` mit dem
Ergebnis `Passed`. Der ganze Kasten dazu: **12 von 12 Tests gruen.**

**`belegstellen_riegel`, je Datei gemessen:** Den Riegel selbst gebaut und ueber die
Vorhabenwurzel laufen lassen. Ergebnis `Passed`, und die ausfuehrliche Ausgabe nennt jede
uebergangene Fundstelle beim Namen: fuenf Stueck, in `parameter.toml`, dreimal in
`daten/lizenzbefund-reihen.md` und in `kern/CMakeLists.txt`. **Keine davon liegt in
`kern/test/schranken_probe.cpp`.** Fuer diese Datei also null Befunde und null uebergangene
Stellen -- je Datei belegt, nicht aus einer Summe geschlossen.

## Wird es rot, wenn man die Sache kaputtmacht?

Zwei getrennte Nachweise, weil die beiden Fragen oben verschiedene Antworten brauchen.

### Der Maschinencodevergleich -- es wurde keine Zusicherung angefasst

Alte und neue Fassung mit denselben Schaltern nach Assembler uebersetzt und verglichen
(`c++ -std -Wall -Wextra -Werror -fwrapv -O1 -I .../kern/include -S`, dann `diff`).

**Jeder einzelne Unterschied ist entweder die `.file`-Zeile oder ein Zeilennummernwert aus
`__LINE__`, und jeder dieser Werte ist um genau 4 verschoben** -- so viele Zeilen ist der
Kommentar gewachsen. Zaehlung der Unterschiede, die *nicht* dieser Form sind: **0.** Kein
Befehl, keine Konstante, kein Sprung hat sich geaendert. Damit ist mechanisch
ausgeschlossen, was bei einer Kommentaraenderung am ehesten zu befuerchten waere: eine
gesenkte Schwelle, eine entfernte Zusicherung, ein stillgelegter Fall.

### Der Mutationsstand -- die geschuetzten Sachen haben Zaehne

Der Maschinencodevergleich zeigt nur, dass sich nichts geaendert hat. Er sagt nicht, ob das
Unveraenderte etwas wert ist. Bedingung 3 schuetzt eine Konstante als unveraendert -- also
habe ich gefragt, ob diese Unversehrtheit ueberhaupt etwas bedeutet.

Vier Faelle in einem `ctest`-Aufruf, die Mutanten mit `cmake -P` erzeugt (mit Fehlerbremse
gegen ein nicht treffendes Suchmuster), gegen die **unveraenderte** `libkern_geprueft.a`
gelinkt. Kein Schreibvorgang unter `ventures/`, nichts zurueckzurollen:

| Fall | Eingriff | Erwartung | Ergebnis |
|---|---|---|---|
| M0 | keiner (Kontrolle) | gruen | **gruen**, Rueckgabe 0 |
| M1 | Schranke 1: Vergleich kleiner 1 auf kleiner minus 999999 aufgeweitet | rot | **rot** -- 2 Proben fehlgeschlagen, beide `wechselkurs`-Rotfaelle blieben gruen |
| M2 | `GRENZEN_BAUZEITPUNKT` von 1, 1, 51 auf 1, 1, 50 | rot | **rot** -- FEHLGESCHLAGEN Zeile 949, der Gruenfall leitzins minus 50 plus aufschlag 51 ergibt 1 |
| M3 | Rundungsschlupf von plusminus `ANTEIL_SCHLUPF` auf plusminus 5000 aufgeweitet | rot | **rot** -- FEHLGESCHLAGEN Zeile 1085, `!anteile_ok(abgeschnitten)` |

**M0 ist der wichtigste Fall**, denn ohne ihn belegte "alle Mutanten sterben" auch, dass
mein Aufbau selbst kaputt ist. Er ist gruen, der Massstab traegt also.

**M2 ist die Antwort auf Bedingung 3.** Die 51 ist kein Zierat: Die Probe haelt einen
Gruenfall, der einen Leitzins von minus 50 genau auf die Grenze setzt, weil minus 50 plus
51 gerade 1 ergibt. Ein Nachziehen der Konstante um eins macht die Probe rot. Bedingung 3
schuetzt damit etwas, das sich wehrt -- anders als eine Zahl, die nur im Kommentar steht.

**M3 misst die Richtung, die man am leichtesten uebersieht:** nicht eine entfernte
Pruefung, sondern eine *aufgeweitete* Schwelle. Auch sie stirbt, weil die Probe einen Fall
haelt, der eine abschneidend gebildete Anteilssumme von 9.998 ausdruecklich als falsch
erwartet.

## Was ich gesucht und nicht gefunden habe

- **Eine abgeschwaechte Zusicherung in der Versionsgeschichte.** Der Diff des Baucommits
  beruehrt an dieser Datei nur Kommentarzeilen; der Maschinencodevergleich bestaetigt das
  unabhaengig vom Lesen.
- **Eine uebersprungene oder auskommentierte Probe.** 64 gegen 64, und `ctest` fuehrt
  `schranken_probe` als einzelnen Test.
- **Eine Zahl, die der Bauagent aus dem Paketrumpf abgeschrieben hat.** Keine der drei
  Zaehlungen und keines der Zeilennummerntripel aus dem Vorschlag steht in der Quelle.
- **Eine neu eingetragene Zeilennummer.** Das Ziffernmuster ist leer; Punkt 3 des
  Auftrags ist eingehalten.
- **Ein Ersatzsatz, der beim Nachschlagen nicht traegt.** Vier Behauptungen, vier einzeln
  gemessen, vier bestaetigt.

## Befund ausserhalb des Pakets: der Baucommit traegt 322 fremde Dateien

Nicht gegen dieses Paket -- die Abnahme ist erfuellt und die Quelldatei sauber. Aber es
ist mir bei der Arbeit an dieser Datei begegnet und gehoert damit hierher.

Commit `113d91b` traegt den Betreff `testentwickler: 0077-... (8 Dateien)` und aendert
**329 Dateien**. Von der `dateien`-Liste des Pakets stammt genau eine. Der Rest:

- **322 Dateien unter `befunde/messung-0069/`** -- ein von Hand angelegter Messbaum aus
  Paket 0069. Davon sind 182 CMake-Bauabfall und **zwei uebersetzte Binaerdateien**
  (`CompilerIdCXX/a.out`, `CMakeDetermineCompilerABI_CXX.bin`).
- **drei Quelldateien aus Paket 0071** (`kern/include/kern/schritt.hpp`,
  `kern/src/schritt.cpp`, `kern/test/schritt_probe.cpp`), das erst zwoelf Minuten spaeter
  unter `2b9fafc` seinen eigenen Commit bekam.

**Warum das diese Paketfamilie besonders trifft:** Der Messbaum enthaelt eine volle
Abschrift des Quellbaums. `befunde/messung-0069/baum/kern/test/schranken_probe.cpp:425`
traegt heute noch **wortgleich den Satz, den 0077 gerade entfernt hat**. Wer den naechsten
Beleg mit einem Suchlauf ueber das Vorhaben prueft -- die Arbeitsweise, auf der die sechs
Pakete dieser Familie beruhen --, findet ihn und haelt ihn fuer die Quelle. Dasselbe gilt
fuer `befunde/messung-0052/gegenprobe/.../schranken_probe.cpp:47` und den Satz aus
Bedingung 1.

Der `belegstellen_riegel` ist davon nicht betroffen, er ueberspringt `befunde/`
nachweislich (37 Bauquellen gelesen); der Mensch und der naechste Agent tun es nicht.

Es ist der dritte Fall derselben Sorte: 1.018 Dateien unter `befunde/messung-0063/` wurden
schon einmal von Hand zurueckgenommen (dokumentiert in 0059 und 0061). Heute stehen wieder
**370 Dateien unter `befunde/messung-*` im Index, 178 davon Bauabfall.** Die `.gitignore`
des Vorhabens kennt genau einen Eintrag, `bau/` -- und die Messbaeume heissen `bau-basis/`
und aehnlich.

Daraus habe ich **`aufgaben/0081-messbaeume-aus-der-versionierung.md`** als
`status: vorschlag` geschrieben. Warum ein eigenes Paket und nicht ein Ruecklauf auf 0077:
Der Bauagent von 0077 hat den Messbaum nicht angelegt, er stand beim Committen im
Arbeitsbereich. Die Ursache liegt im Runner und in der `.gitignore`, nicht in diesem Paket
-- ein Ruecklauf traefe den Falschen und beliesse die Ursache.

## Urteil

`geprueft`. Alle drei Abnahmebedingungen erfuellt, jede selbst nachgemessen. Beide
Ersatzsaetze sind gegen `parameter.toml` nachgeschlagen und wahr. Die Aenderung hat
nachweislich keine Zeile ausfuehrbaren Codes beruehrt, und die Sachen, die Bedingung 3
schuetzt, halten einem Mutationsstand stand.
