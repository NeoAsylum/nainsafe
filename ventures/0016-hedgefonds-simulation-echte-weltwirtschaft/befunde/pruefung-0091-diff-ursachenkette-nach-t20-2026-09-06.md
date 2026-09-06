---
typ: pruefung
paket: 0091-diff-ursachenkette-nach-t20
pruefer: kern-pruefer
datum: 2026-09-06
urteil: geprueft
kriterium_geprueft: Selbst gebaut und selbst gefahren -- beide Saetze der Abnahme an der abgedruckten Ausgabe der vierten Abfrage nachgezaehlt, die tragende Aufloesungsregel mit zwei Mutanten gegen einen Kontrollbaum gehalten, die Zahlen von Hand nachgerechnet.
befunde: 0
---

# 0091 -- die Ursachenkette der Unterschiedsebene

## Der gepruefte Stand

Die sechs Paketdateien stammen saemtlich aus **`9449bda`**; zwischen diesem Commit und
dem Beginn meines Laufs hat kein Commit `kern/` beruehrt (`git log 9449bda..HEAD --
.../kern/` ist leer). Ihre md5 zu Beginn und am Ende meines Laufs, unveraendert:

| Datei | md5 |
|---|---|
| `kern/include/kern/verlauf.hpp` | `7e07686873e4dcfdde6359fe4fe6eeac` |
| `kern/src/verlauf.cpp` | `ef6ab4527a5ce27aeaa08a0e6b24709f` |
| `kern/test/verlauf_probe.cpp` | `8b06b2fd3fa6b147b4d06100703758c3` |
| `kern/include/kern/zustandsausgabe.hpp` | `354e92e3be24361a421cde95eccafae1` |
| `kern/src/zustandsausgabe.cpp` | `4d057577e1ac61fdf00f5bab22528a93` |
| `kern/test/zustandsausgabe_probe.cpp` | `b7d2616f2e1481f830a5ef8acceed6ed` |

Waehrend meines Laufs sind zwei fremde Commits dazugekommen (`8ff7cc4`
entwurf-pruefer/0141, `ebe9b4f` test-pruefer/0130). Keiner von beiden faellt in `kern/`;
die Tabelle oben gilt danach unveraendert.

Alle Messungen aus einem eigenen Baum: `git archive 9449bda` nach
`befunde/bau-pruefung-0091/v/`, samt `specs/` und `decisions/`, damit der
Belegstellenriegel nicht ausfaellt. Dort liegen auch alle Protokolle dieses Befundes.

## Was ich geprueft habe

### 1. Die Abnahme, Satz fuer Satz

**Satz 1** -- *je geaenderter Adresse nicht nur alt, neu und Differenz, sondern die
Ursachenkette aus T18, rueckwaerts aufgeloest bis zur ausloesenden Aktion oder
Gegenkraft, mit Verzoegerung und Beitrag je Glied.*

Selbst gefahren, nicht der Probe geglaubt: `./zustandsausgabe_probe` aus meinem Baum
druckt das Blatt vollstaendig ab (`befunde/bau-pruefung-0091/probe-ausgabe.txt`,
Zeilen 61-88). Fuenf geaenderte Adressen, je eine Wertzeile mit `alt`, `neu` und
`Differenz`, darunter je Glied `Runde`, Ursache, `Verzoegerung` und `Beitrag` in
Promille, zuletzt eine Zeile mit dem Ende und dem Rundenabstand. Auszug:

```
land.DE.sektor.2.kapitalstock  alt 4200000  neu 4260000  Differenz 60000  [K2 ...]
    Glied 1  Runde 3  Vortrag land.DE.instrument.zoll.stand  Verzoegerung 2  Beitrag 300 Promille
    Glied 2  Runde 1  Aktion 2  Verzoegerung 0  Beitrag 1000 Promille
    Ende nach 2 Glied(ern): ausloesende Aktion oder Gegenkraft (T20), Runde 1, 2 Runde(n) vor der Wirkung
```

**Satz 2** -- *nachgewiesen an einer Partie ueber mindestens drei Runden, in der eine
Aktion in Runde 1 eine Groesse in Runde 3 aendert: Die Kette nennt beide Glieder und die
Verzoegerung dazwischen, und eine Adresse ohne Ursache kommt nicht vor.*

Der Auszug oben ist genau dieser Fall: Glied 2 ist die Aktion der Runde 1, Glied 1 die
Wirkung in Runde 3, die Verzoegerung dazwischen steht mit `2` da und der Abstand `3 - 1`
ebenfalls. Die Partie laeuft ueber drei Runden durch `kern::schreiber` im Spielmodus mit
der zweiseitigen Maskenpruefung aus T38 an jedem Rundenende; die Kopfzeile des Blattes
zaehlt `3 Runde(n) mit 930 Glied(ern)`, also 3 x 310, was der Maske `spielmodus`
entspricht.

Zum zweiten Halbsatz zaehlt das Blatt selbst: `5 von 310 Adressen geaendert.` und
`5 davon mit Ursachenkette, 0 ohne.` **Der Negativnachweis dazu steht daneben** und ist
der Grund, warum die Null etwas heisst: Dasselbe Blatt mit einem Verlauf, dem die Runde 3
fast ganz fehlt, meldet `1 davon mit Ursachenkette, 4 ohne` und schreibt zu jeder der
vier die Zeile `ohne Ursachensatz in Runde 3` (`probe-ausgabe.txt`, Zeilen 89-104).

Die *zweite* Kette des Blattes (`land.DE.sektor.2.preis`, drei Glieder ueber
`Instrument`) belegt, dass die Aufloesung nicht nur einen Sprung schafft; die dritte
(`land.DE.instrument.zoll.stand`, dreimal `Vortrag` auf sich selbst) ist genau der Fall,
an dem eine ausgerechnete Ursachenrunde stillstuende.

### 2. Ist es wirklich deterministisch?

- **Kein Gleitkomma.** `src/verlauf.cpp` und `src/zustandsausgabe.cpp` binden beide
  `kern/sperre.hpp` als letzten `#include`; der Sperrebindungsriegel beim Konfigurieren
  bestaetigt es fuer 10 Kernquellen und 12 Proben. Eigener Suchlauf ueber beide Quellen
  und den Kopf nach `double`, `float`, `unordered`, `std::map`, `std::set`, `time`,
  `clock`, `rand`, `reinterpret_cast`, `uintptr`, `sort(`: **kein Treffer**.
- **Keine streuende Menge.** `platz_der_runde`, `gliedplatz_von`, `schritt_zurueck` und
  `Verlauf::glieder` laufen samt und sonders als aufsteigende bzw. absteigende
  Zaehlschleife ueber `std::array` fester Groesse. Keine Adresse und keine Zeit geht ins
  Ergebnis ein.
- **Profilvergleich, die staerkste Form.** `zustandsausgabe_probe` und `verlauf_probe`
  aus `Debug` (mit UB- und Adresssanitizer, `-O0`) gegen `Release` (`-O2`):
  `diff` beider vollstaendiger Ausgaben ist **leer** -- 108 bzw. 61 Zeilen, zeichengleich
  (`diff-zustandsausgabe.txt`, `diff-verlauf.txt`, beide 0 Zeilen). Beide Proben drucken
  Ergebnisse ab und brechen nicht still ab; der Vergleich prueft also etwas.

### 3. Sind die Rueckkopplungen begrenzt?

Die Aufloesung ist die eine Schleife, die dieses Paket dazulegt, und sie endet ohne
Laengenschranke: Jeder Schritt geht auf einen echt frueheren Platz -- erst innerhalb der
Kette (`--gliedplatz`), dann in eine frueher aufgenommene Runde --, und die Zahl der
Plaetze ist mit `RUNDEN_KAPAZITAET` x `GLIEDER_JE_RUNDE` = 26 x 310 endlich. Nachgefahren
am Quelltext von `schritt_zurueck`; kein Zweig laesst den Platz stehen oder vorwaerts
gehen.

Die drei Schranken daneben:

- **Je Runde** (310) und **ueber die Partie** (26): beide brechen hart ab, beide
  zweiseitig belegt in `verlauf-debug.txt`, Bedingung 2 und 3 -- an der Grenze gruen,
  eines darueber der Abbruch im Wortlaut, danach der Behaelter unveraendert.
- **Der Puffer der vierten Abfrage.** Der Kopf sagt einen Abbruch zu, wenn er nicht
  reicht. Das war die einzige Zusage dieses Pakets, zu der es keine Probe gibt, und ich
  habe sie deshalb selbst gemessen: In einer Abschrift des Kerns habe ich
  `KETTENBLATT_ZEICHEN` von 1.667.329 auf 342 Zeichen heruntergesetzt -- **eine Zeile,
  nur die Rechnung, sonst nichts** -- und die unveraenderte Probe gefahren. Ergebnis
  (`m3-lauf.txt`):

  ```
  kern::zustandsausgabe::diff_mit_kette -- der Puffer hat nicht gereicht; ausgegangen
  ist er bei land.DE.sektor.2.kapitalstock (Nr. 94). Eine gekuerzte Kette waere eine
  Luege gegenueber dem Kaeufer (T19).
  ```

  Der Abbruch kommt, und er nennt die Adresse. **Keine stille Kuerzung.** Danach die
  Abschrift zurueckgesetzt und gegen die Paketdatei gedifft -- leer.

### 4. Ist die Zustandsausgabe vollstaendig?

Die Prueffrage lautet, ob sich aus der Ausgabe allein erkennen laesst, ob richtig
gerechnet wurde. Fuer die vierte Abfrage ja, und zwar an drei Stellen:

- Die Wertzeile ist **zeichengleich** mit der der dritten Ebene. Das ist keine Aussage
  ueber den Quelltext, sondern eine ueber die Ausgabe: Die Probe stellt beide Blaetter
  je Adresse nebeneinander, und ich habe die fuenf Zeilen im abgedruckten Blatt gegen
  `diff` gegengelesen.
- Das Ziel jedes Gliedes ist aus dem Vorgaengerglied ablesbar, weil `Vortrag` und
  `Instrument` ihre Adresse ausgeschrieben nennen. `Aktion`, `Gegenkraft`, `Jahrgang`
  und `Marktraeumung` nennen keine -- dort endet die Kette, und die Schlusszeile sagt
  welches der fuenf Enden es war.
- Die Schlusszeile zaehlt, was der zweite Satz der Abnahme ausschliessen will, statt es
  besichtigen zu lassen.

Dass die Kettenzeile `alt` und `neu` der Zwischenglieder nicht mitfuehrt, ist **kein
Befund**: T20 nennt fuer die Kette woertlich `Verzögerung und Beitrag je Glied`, und die
Abnahme wiederholt genau diese zwei.

### 5. Halten die Zahlen die Raender?

Von Hand nachgerechnet, jede gegen die gedruckte Zahl:

| Groesse | Rechnung | gedruckt |
|---|---|---|
| `sizeof(Verlauf)` | 26 x 17.368 + 26 x 8 + 8 | 451.784 |
| `KETTENZEILEN_JE_ADRESSE` | 26 + 1 | 27 |
| `KETTENBLATT_ZEICHEN` | (310 x 28 + 4) x 192 + 1 | 1.667.329 |
| `sizeof(Kettenblatt)` | 1.667.329 auf 8 gerundet + 8 + 8 + 1, auf 8 gerundet | 1.667.360 |
| Anteil am Stapel | 100 x 1.667.360 / 8.388.608 | 19 Prozent |
| Glieder im Verlauf | 3 x 310 | 930 |
| Differenzen | 4.260.000-4.200.000; 10.420-10.000; 500-380; 4.200-0; 3-0 | 60000, 420, 120, 4200, 3 |
| Rundenabstand | 3 - 1 | 2 |

Der Kopf behauptet ueber sich selbst, `zustandsausgabe_probe` drucke Puffergroesse und
Stapel ab. Nachgefahren: tut sie, Zeile 59 der Ausgabe. Ueberlauf ist an beiden neuen
Rechenstellen (`spaetestens`, der Rundenabstand) auf `i128` gehoben, wie ADR 0011
Massnahme 3 es verlangt; eine Division kommt in beiden Dateien nicht vor, also auch keine
durch null.

**Die neue Zusicherung selbst nachgemessen**, statt den Bericht daneben zu lesen: Ich
habe `befunde/messung-0091/nachweis.py` gelesen und selbst gefahren. Seine Riegel taugen
-- `ersetze_einmal` besteht auf genau einem Vorkommen, der Wortlautvergleich haelt die
eigene Zusicherung gegen die des Verlaufs auseinander, und der vierte Fall belegt, dass
die Zeile es ist, die reisst. Mein Lauf: `Abweichungen: 0`, gruen bei 139
(8.333.569 Byte), rot bei 140 (8.393.089 Byte), gruen bei 140 ohne die Zusicherung. Beide
Puffergroessen habe ich aus der Formel gegengerechnet und komme auf dieselben Zahlen.

*Was daran eine Herleitung ist und kein Lauf:* Der Kopf sagt, die Zusicherung fange
**beide** Regler, die die linke Seite bewegen. Gefahren ist nur der eine
(`KETTENZEILEN_JE_ADRESSE`). Fuer den anderen (`ZEILE_ZEICHEN`) steht er in
`KETTENBLATT_ZEICHEN` als Faktor mit positivem Vorzeichen, die Groesse waechst also auch
mit ihm streng, und die Zusicherung ist eine strikte obere Schranke -- die Aussage traegt
arithmetisch, gemessen ist sie nicht.

### 6. Mutation -- haelt die Probe die tragende Regel fest?

Kontrollbaum `m0`: Abschrift des Kerns, unveraendert, 12 von 12 Proben gruen. Beide
Mutanten je eine reine Zeilenloeschung an `src/verlauf.cpp`, gegen denselben Baum, danach
zurueckgesetzt und gediffft (leer).

| Mutant | Aenderung | Ergebnis |
|---|---|---|
| m0 | keine | 12/12 gruen |
| m1 | das `continue` der Verzoegerungsschranke entfernt (die Suche ignoriert `runde - verzoegerung`) | **rot**: `verlauf_probe` und `zustandsausgabe_probe` |
| m2 | den Schritt **innerhalb** der Kette entfernt (`schritt_zurueck` springt immer in die Vorrunde) | **rot**: `verlauf_probe` und `zustandsausgabe_probe` |

Die eine Regel, an der dieses Paket haette scheitern koennen -- rueckwaerts **suchen**
statt die Ursachenrunde auszurechnen --, ist damit von zwei Seiten festgenagelt und nicht
nur behauptet.

### 7. Beide Bauwege, beide Profile

- Alleinbau `kern/`, `Debug` mit Sanitizern: 12 von 12 gruen.
- Alleinbau `kern/`, `Release`: gebaut, Proben zeichengleich zum Debug-Lauf.
- Arbeitsbereich (das ganze Vorhaben), `Debug`: **18 von 18 gruen**, darunter
  `belegstellen_riegel`, `bezeichner_riegel` und `schlussriegel_nachbau`. Null Warnungen
  in beiden Bauprotokollen.

## Wonach ich gesucht und nichts gefunden habe

Damit diese Pruefung von einer, die nicht stattfand, unterscheidbar ist:

- **Eine Ursache, die auf `zustand::KEIN_PLATZ` zeigt und trotzdem als `Ausloeser`
  ausgewiesen wird.** `ziel_der_ursache` gibt fuer `Vortrag` und `Instrument` das Ende
  `Ausloeser` mit, obwohl es dort nicht gelten soll. Nachgesehen: `Ursache::vortrag`
  bricht ueber `FELDER` ab, `Ursache::instrument` prueft Land und Instrument, und
  `KEIN_PLATZ` ist `FELDER`. Der Zweig ist unerreichbar; kein Befund.
- **Eine Kette, die nicht endet.** Jeder Schritt geht echt zurueck; siehe 3.
- **Eine Zeile laenger als `ZEILE_ZEICHEN`.** Die laengste Kettenzeile misst bei
  realistischen Rundennummern rund 140 von 192 Zeichen. Der Puffer ist ohnehin eine
  Gesamtschranke und keine je Zeile, und sein Ueberlauf bricht ab (siehe 3).
- **Ein Widerspruch zwischen der Abnahme und T20.** Der Auftrag zitiert T20 woertlich;
  ich habe beide nebeneinandergelegt und keine Stelle gefunden, an der der Auftrag
  weniger verlangt.
- **Ein Ende, das die Abnahme verletzt.** Die Kette von `partie.runde` endet nicht auf
  einer Aktion, sondern auf `kein frueherer Schreibzugriff im Verlauf`. Das ist keine
  Verletzung: Die Abnahme schliesst eine Adresse **ohne Ursache** aus, und diese hat
  drei Glieder. Eine Aktion, bis zu der aufzuloesen waere, gibt es fuer diese Groesse
  nicht.

## Urteil

**`geprueft`.** Beide Saetze der Abnahme sind an der abgedruckten Ausgabe belegt, die
tragende Aufloesungsregel ist mutationsgehaertet, die Zahlen halten von Hand, und die
einzige Zusage ohne Probe -- der Abbruch bei vollem Puffer -- habe ich selbst gemessen
und bestaetigt gefunden.

## Ein Vorschlag daneben, und warum er kein `zurueck` ist

`0186-verlauf-glied-mit-fremder-rundennummer.md`. Die Aufloesung setzt voraus, dass
`Ursachensatz.runde` mit der Rundennummer uebereinstimmt, unter der die Kette im Verlauf
steht -- sie rechnet `spaetestens` aus dem einen und vergleicht gegen das andere.
Niemand prueft das. Gemessen habe ich, was dann herauskommt: eine Kette, die vorwaerts
durch die Zeit laeuft (`Glied 1 Runde 2`, `Glied 2 Runde 3`, `Glied 3 Runde 1`), ohne
Abbruch, ohne Marke, mit unveraendertem `5 davon mit Ursachenkette, 0 ohne` darunter.

Das ist kein `zurueck`: Die Abnahme schweigt zu fehlgeleiteter Eingabe, und auf einem
wohlgeformten Verlauf ist sie erfuellt. Die Begruendung steht im Vorschlag.
